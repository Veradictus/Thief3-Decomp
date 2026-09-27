// Loads mod DLLs from System/mods/ in filename order, runs their
// T3Mod_Shutdown at exit (newest first), and maps a code address back to the
// mod that owns it, for log-line tagging and crash reports.
#include "mods.hpp"

#include "log.hpp"

#include <algorithm>
#include <string>
#include <vector>

namespace t3sdk::mods {
namespace {

struct Mod {
    std::string name;
    HMODULE module;
    uintptr_t begin;
    uintptr_t end;
    T3ModShutdownFn shutdown;
};

std::vector<Mod> g_mods;

uintptr_t ImageEnd(HMODULE module) {
    auto base = reinterpret_cast<const BYTE*>(module);
    auto nt = reinterpret_cast<const IMAGE_NT_HEADERS*>(base + reinterpret_cast<const IMAGE_DOS_HEADER*>(base)->e_lfanew);
    return reinterpret_cast<uintptr_t>(base) + nt->OptionalHeader.SizeOfImage;
}

// Returns the exception code, or 0 when the mod's shutdown returned normally.
DWORD CallShutdown(T3ModShutdownFn shutdown) {
    __try {
        shutdown();
        return 0;
    } __except (EXCEPTION_EXECUTE_HANDLER) {
        return GetExceptionCode();
    }
}

const Mod* Find(const void* address) {
    auto a = reinterpret_cast<uintptr_t>(address);
    for (const Mod& mod : g_mods) {
        if (a >= mod.begin && a < mod.end) {
            return &mod;
        }
    }
    return nullptr;
}

}  // namespace

void LoadAll(const std::filesystem::path& dir, const T3SdkApi* api, void (*onUnload)(HMODULE mod)) {
    std::error_code ec;
    if (!std::filesystem::is_directory(dir, ec)) {
        T3_LOG("no mods folder at %s", dir.string().c_str());
        return;
    }
    std::vector<std::filesystem::path> files;
    for (const auto& entry : std::filesystem::directory_iterator(dir, ec)) {
        if (entry.is_regular_file() && _wcsicmp(entry.path().extension().c_str(), L".dll") == 0) {
            files.push_back(entry.path());
        }
    }
    std::sort(files.begin(), files.end());  // deterministic load order

    for (const auto& file : files) {
        std::string name = file.stem().string();
        HMODULE module = LoadLibraryW(file.c_str());
        if (!module) {
            T3_LOG("mod %s: LoadLibrary failed (error %lu)", name.c_str(), GetLastError());
            continue;
        }
        // Registered before init so the mod's log lines and callbacks are attributed to it.
        g_mods.push_back({name, module, reinterpret_cast<uintptr_t>(module), ImageEnd(module), nullptr});
        auto init = reinterpret_cast<T3ModInitFn>(GetProcAddress(module, "T3Mod_Init"));
        int result = init ? init(api) : -1;
        if (result != 0) {
            T3_LOG("mod %s: %s; unloading", name.c_str(),
                   init ? ("T3Mod_Init returned " + std::to_string(result)).c_str() : "no T3Mod_Init export");
            onUnload(module);
            g_mods.pop_back();
            FreeLibrary(module);
            continue;
        }
        g_mods.back().shutdown = reinterpret_cast<T3ModShutdownFn>(GetProcAddress(module, "T3Mod_Shutdown"));
        T3_LOG("mod %s loaded", name.c_str());
    }
}

void ShutdownAll() {
    for (auto it = g_mods.rbegin(); it != g_mods.rend(); ++it) {
        if (!it->shutdown) {
            continue;
        }
        if (DWORD code = CallShutdown(it->shutdown)) {
            T3_LOG("mod %s: T3Mod_Shutdown raised exception 0x%08lX", it->name.c_str(), code);
        }
    }
}

HMODULE ModuleAt(const void* address) {
    const Mod* mod = Find(address);
    return mod ? mod->module : nullptr;
}

const char* NameAt(const void* address) {
    const Mod* mod = Find(address);
    return mod ? mod->name.c_str() : nullptr;
}

}  // namespace t3sdk::mods
