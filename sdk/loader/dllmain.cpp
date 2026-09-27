// dinput8.dll proxy. T3Main.exe imports DirectInput8Create from dinput8.dll and
// Windows looks for that DLL in the game's System/ folder first, so this DLL is
// loaded into the game before its entry point runs. It forwards the real
// dinput8 exports and starts the SDK.
//
// DllMain runs under the loader lock, where loading libraries and most other
// work is unsafe. So DllMain only patches a jump over the first bytes of the
// exe's entry point; when the game starts executing, the jump runs the SDK's
// start-up on the main thread, puts the original bytes back, and continues
// into the game.

#include "sdk.hpp"

#include <windows.h>

#include <cstdint>
#include <cstring>

namespace {

HMODULE g_self = nullptr;
uintptr_t g_entry = 0;
uint8_t g_entryBytes[5];

// The real dinput8.dll, loaded from the system directory by full path: a bare
// LoadLibraryW(L"dinput8.dll") would follow the same search order that found
// this proxy in System/ and could load this DLL again instead of the real one.
HMODULE RealDinput8() {
    static HMODULE module = [] {
        wchar_t path[MAX_PATH];
        UINT n = GetSystemDirectoryW(path, MAX_PATH);
        wcscpy_s(path + n, MAX_PATH - n, L"\\dinput8.dll");
        return LoadLibraryW(path);
    }();
    return module;
}

FARPROC Real(const char* name) {
    HMODULE module = RealDinput8();
    return module ? GetProcAddress(module, name) : nullptr;
}

// Overwrites `size` bytes of code at `address`. FlushInstructionCache matters
// here: without it, a core that already fetched the old bytes could keep
// executing them after this returns.
void WriteCode(uintptr_t address, const void* bytes, size_t size) {
    DWORD protect;
    VirtualProtect(reinterpret_cast<void*>(address), size, PAGE_EXECUTE_READWRITE, &protect);
    memcpy(reinterpret_cast<void*>(address), bytes, size);
    VirtualProtect(reinterpret_cast<void*>(address), size, protect, &protect);
    FlushInstructionCache(GetCurrentProcess(), reinterpret_cast<void*>(address), size);
}

void __cdecl OnGameEntry() {
    WriteCode(g_entry, g_entryBytes, sizeof(g_entryBytes));
    t3sdk::Initialize(g_self);
}

// Target of the jump patched over the entry point: preserve the registers the
// OS set up, start the SDK, then resume the restored entry point.
__declspec(naked) void EntryTrampoline() {
    __asm {
        pushad
        pushfd
        call OnGameEntry
        popfd
        popad
        jmp dword ptr [g_entry]
    }
}

// dinput8.dll can be loaded into other processes that share the game's
// System/ folder; only T3Main.exe itself should have its entry point patched.
bool IsGame() {
    wchar_t path[MAX_PATH];
    GetModuleFileNameW(nullptr, path, MAX_PATH);
    const wchar_t* name = wcsrchr(path, L'\\');
    return _wcsicmp(name ? name + 1 : path, L"T3Main.exe") == 0;
}

void PatchEntry() {
    auto base = reinterpret_cast<uint8_t*>(GetModuleHandleW(nullptr));
    auto nt = reinterpret_cast<IMAGE_NT_HEADERS*>(base + reinterpret_cast<IMAGE_DOS_HEADER*>(base)->e_lfanew);
    g_entry = reinterpret_cast<uintptr_t>(base) + nt->OptionalHeader.AddressOfEntryPoint;
    memcpy(g_entryBytes, reinterpret_cast<void*>(g_entry), sizeof(g_entryBytes));

    uint8_t jump[5] = {0xE9};
    int32_t rel = int32_t(reinterpret_cast<uintptr_t>(&EntryTrampoline) - (g_entry + 5));
    memcpy(jump + 1, &rel, sizeof(rel));
    WriteCode(g_entry, jump, sizeof(jump));
}

}  // namespace

// ---- dinput8.dll exports (names mapped in dinput8.def) ----------------------

extern "C" HRESULT WINAPI Proxy_DirectInput8Create(HINSTANCE instance, DWORD version, REFIID iid, LPVOID* out,
                                                   void* outer) {
    using Fn = HRESULT(WINAPI*)(HINSTANCE, DWORD, REFIID, LPVOID*, void*);
    static auto fn = reinterpret_cast<Fn>(Real("DirectInput8Create"));
    return fn ? fn(instance, version, iid, out, outer) : E_FAIL;
}

extern "C" HRESULT WINAPI Proxy_DllCanUnloadNow() {
    using Fn = HRESULT(WINAPI*)();
    static auto fn = reinterpret_cast<Fn>(Real("DllCanUnloadNow"));
    return fn ? fn() : S_FALSE;
}

extern "C" HRESULT WINAPI Proxy_DllGetClassObject(REFCLSID clsid, REFIID iid, LPVOID* out) {
    using Fn = HRESULT(WINAPI*)(REFCLSID, REFIID, LPVOID*);
    static auto fn = reinterpret_cast<Fn>(Real("DllGetClassObject"));
    return fn ? fn(clsid, iid, out) : E_FAIL;
}

extern "C" HRESULT WINAPI Proxy_DllRegisterServer() {
    using Fn = HRESULT(WINAPI*)();
    static auto fn = reinterpret_cast<Fn>(Real("DllRegisterServer"));
    return fn ? fn() : E_FAIL;
}

extern "C" HRESULT WINAPI Proxy_DllUnregisterServer() {
    using Fn = HRESULT(WINAPI*)();
    static auto fn = reinterpret_cast<Fn>(Real("DllUnregisterServer"));
    return fn ? fn() : E_FAIL;
}

BOOL APIENTRY DllMain(HMODULE module, DWORD reason, LPVOID) {
    if (reason == DLL_PROCESS_ATTACH) {
        g_self = module;
        DisableThreadLibraryCalls(module);
        if (IsGame()) {
            PatchEntry();
        }
    }
    return TRUE;
}
