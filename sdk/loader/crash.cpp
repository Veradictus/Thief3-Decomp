// Crash reporter: a vectored exception handler that logs the first few faults
// (location, registers, code addresses on the stack) and then always defers
// to whatever handler would have run without it (see crash.hpp).
#include "crash.hpp"

#include "log.hpp"
#include "mods.hpp"

#include <intrin.h>

#include <atomic>
#include <cstdint>
#include <cstdio>

namespace t3sdk::crash {
namespace {

constexpr int kMaxReports = 32;
constexpr uintptr_t kGameBase = 0x10900000;

uintptr_t g_sdkBegin = 0;
uintptr_t g_sdkEnd = 0;
uintptr_t g_gameEnd = 0;
std::atomic<int> g_reports{0};
uintptr_t g_reported[kMaxReports] = {};

uintptr_t ImageEnd(uintptr_t base) {
    auto nt = reinterpret_cast<const IMAGE_NT_HEADERS*>(base + reinterpret_cast<const IMAGE_DOS_HEADER*>(base)->e_lfanew);
    return base + nt->OptionalHeader.SizeOfImage;
}

// "T3Main.exe+0x123", "dinput8.dll+0x45", "<mod>+0x67" or the raw address.
// No loader calls: they can deadlock while the faulting thread holds the loader lock.
void Describe(uintptr_t address, char* out, size_t size) {
    if (address >= kGameBase && address < g_gameEnd) {
        snprintf(out, size, "T3Main.exe+0x%X (%08X)", unsigned(address - kGameBase), unsigned(address));
    } else if (address >= g_sdkBegin && address < g_sdkEnd) {
        snprintf(out, size, "T3SDK+0x%X", unsigned(address - g_sdkBegin));
    } else if (const char* mod = mods::NameAt(reinterpret_cast<const void*>(address))) {
        snprintf(out, size, "mod %s (%08X)", mod, unsigned(address));
    } else {
        snprintf(out, size, "%08X", unsigned(address));
    }
}

bool Interesting(DWORD code) {
    switch (code) {
    case EXCEPTION_ACCESS_VIOLATION:
    case EXCEPTION_ILLEGAL_INSTRUCTION:
    case EXCEPTION_PRIV_INSTRUCTION:
    case EXCEPTION_INT_DIVIDE_BY_ZERO:
    case EXCEPTION_ARRAY_BOUNDS_EXCEEDED:
        return true;
    default:
        return false;
    }
}

LONG CALLBACK Handler(EXCEPTION_POINTERS* info) {
    const EXCEPTION_RECORD* record = info->ExceptionRecord;
    if (!Interesting(record->ExceptionCode)) {
        return EXCEPTION_CONTINUE_SEARCH;
    }
    auto address = reinterpret_cast<uintptr_t>(record->ExceptionAddress);
    int slot = g_reports.load();
    for (int i = 0; i < slot && i < kMaxReports; ++i) {
        if (g_reported[i] == address) {
            return EXCEPTION_CONTINUE_SEARCH;  // already reported
        }
    }
    slot = g_reports.fetch_add(1);
    if (slot >= kMaxReports) {
        return EXCEPTION_CONTINUE_SEARCH;
    }
    g_reported[slot] = address;

    char where[96];
    Describe(address, where, sizeof(where));
    const CONTEXT* c = info->ContextRecord;
    if (record->ExceptionCode == EXCEPTION_ACCESS_VIOLATION && record->NumberParameters >= 2) {
        const char* op = record->ExceptionInformation[0] == 0 ? "reading" : record->ExceptionInformation[0] == 1
                                                                                ? "writing"
                                                                                : "executing";
        T3_LOG("first-chance fault 0x%08lX at %s: %s %08X (thread %lu)", record->ExceptionCode, where, op,
               unsigned(record->ExceptionInformation[1]), GetCurrentThreadId());
    } else {
        T3_LOG("first-chance fault 0x%08lX at %s (thread %lu)", record->ExceptionCode, where, GetCurrentThreadId());
    }
    T3_LOG("  eax=%08lX ebx=%08lX ecx=%08lX edx=%08lX esi=%08lX edi=%08lX ebp=%08lX esp=%08lX", c->Eax, c->Ebx,
           c->Ecx, c->Edx, c->Esi, c->Edi, c->Ebp, c->Esp);
    // Code addresses on the stack approximate the call chain (frame pointers are omitted).
    char line[512];
    int n = snprintf(line, sizeof(line), "  stack:");
    auto stack = reinterpret_cast<const uintptr_t*>(c->Esp);
    auto stackBase = reinterpret_cast<const uintptr_t*>(__readfsdword(0x04));  // NT_TIB::StackBase
    int found = 0;
    for (int i = 0; i < 256 && stack + i < stackBase && found < 10 && n < int(sizeof(line)) - 40; ++i) {
        uintptr_t value = stack[i];
        bool code = (value >= kGameBase && value < g_gameEnd) || (value >= g_sdkBegin && value < g_sdkEnd) ||
                    mods::NameAt(reinterpret_cast<const void*>(value));
        if (code) {
            char text[96];
            Describe(value, text, sizeof(text));
            n += snprintf(line + n, sizeof(line) - n, " %s", text);
            ++found;
        }
    }
    T3_LOG("%s", line);
    return EXCEPTION_CONTINUE_SEARCH;
}

}  // namespace

void Install(HMODULE self) {
    g_sdkBegin = reinterpret_cast<uintptr_t>(self);
    g_sdkEnd = ImageEnd(g_sdkBegin);
    g_gameEnd = ImageEnd(kGameBase);
    AddVectoredExceptionHandler(1, &Handler);
}

}  // namespace t3sdk::crash
