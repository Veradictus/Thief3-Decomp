// Loads mod DLLs from System/mods/: first the packaged mods that
// load-order.txt lists (written by the launcher; docs/mods.md), in its
// order, then every loose *.dll in the folder not loaded yet, in filename
// order. Runs their T3Mod_Shutdown at exit (newest first), and maps a code
// address back to the mod that owns it, for log-line tagging and crash reports.
#include "mods.hpp"

#include "log.hpp"

#include <algorithm>
#include <fstream>
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

// A DLL named by load-order.txt, the name it goes by (its folder's), and
// the line that named it (UTF-8, for the log).
struct Listed {
    std::filesystem::path file;
    std::string name;
    std::string line;
};

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

// UTF-8 to UTF-16; empty for text that is not UTF-8.
std::wstring Widen(const std::string& text) {
    int length = static_cast<int>(text.size());
    int size = MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, text.data(), length, nullptr, 0);
    if (size <= 0) {
        return {};
    }
    std::wstring wide(static_cast<size_t>(size), L'\0');
    MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, text.data(), length, wide.data(), size);
    return wide;
}

// load-order.txt: one `<folder>/<dll>` per line, relative to `dir`; blank
// lines and `#` comments are skipped, and so is a line with an absolute path
// or `..`, with a log line.
std::vector<Listed> ReadLoadOrder(const std::filesystem::path& dir) {
    std::vector<Listed> listed;
    std::ifstream in(dir / "load-order.txt", std::ios::binary);
    if (!in) {
        return listed;
    }
    std::string line;
    for (int number = 1; std::getline(in, line); ++number) {
        if (number == 1 && line.starts_with("\xEF\xBB\xBF")) {
            line.erase(0, 3);  // a byte-order mark from a hand edit
        }
        size_t first = line.find_first_not_of(" \t\r");
        if (first == std::string::npos || line[first] == '#') {
            continue;
        }
        line = line.substr(first, line.find_last_not_of(" \t\r") - first + 1);
        std::wstring wide = Widen(line);
        std::filesystem::path relative(wide);
        bool up = std::any_of(relative.begin(), relative.end(), [](const auto& part) { return part == L".."; });
        if (wide.empty() || relative.has_root_name() || relative.has_root_directory() || up) {
            T3_LOG("load-order.txt line %d: \"%s\" is not a path inside System/mods; skipped", number, line.c_str());
            continue;
        }
        // A packaged mod goes by its folder's name, a DLL listed on its own by its file name.
        size_t slash = line.find_first_of("/\\");
        std::string name = slash != std::string::npos ? line.substr(0, slash) : line.substr(0, line.find_last_of('.'));
        listed.push_back({dir / relative, name, line});
    }
    return listed;
}

bool SamePath(const std::filesystem::path& a, const std::filesystem::path& b) {
    return _wcsicmp(a.lexically_normal().c_str(), b.lexically_normal().c_str()) == 0;
}

// Loads one mod and calls its T3Mod_Init. A packaged mod's DLL is loaded with
// its own folder on the DLL search path, so it can ship helper DLLs next to it.
void Load(const std::filesystem::path& file, const std::string& name, bool packaged, const T3SdkApi* api,
          void (*onUnload)(HMODULE mod)) {
    HMODULE module = packaged ? LoadLibraryExW(file.c_str(), nullptr, LOAD_WITH_ALTERED_SEARCH_PATH)
                              : LoadLibraryW(file.c_str());
    if (!module) {
        T3_LOG("mod %s: LoadLibrary failed (error %lu)", name.c_str(), GetLastError());
        return;
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
        return;
    }
    g_mods.back().shutdown = reinterpret_cast<T3ModShutdownFn>(GetProcAddress(module, "T3Mod_Shutdown"));
    T3_LOG("mod %s loaded", name.c_str());
}

}  // namespace

void LoadAll(const std::filesystem::path& dir, const T3SdkApi* api, void (*onUnload)(HMODULE mod)) {
    std::error_code ec;
    if (!std::filesystem::is_directory(dir, ec)) {
        T3_LOG("no mods folder at %s", dir.string().c_str());
        return;
    }

    // Packaged mods, in the launcher's load order.
    std::vector<std::filesystem::path> tried;
    std::vector<Listed> listed = ReadLoadOrder(dir);
    if (!listed.empty()) {
        T3_LOG("load-order.txt lists %zu mods", listed.size());
    }
    for (const Listed& mod : listed) {
        if (std::any_of(tried.begin(), tried.end(), [&](const auto& t) { return SamePath(t, mod.file); })) {
            continue;
        }
        tried.push_back(mod.file);
        if (!std::filesystem::is_regular_file(mod.file, ec)) {
            T3_LOG("mod %s: %s not found (listed in load-order.txt)", mod.name.c_str(), mod.line.c_str());
            continue;
        }
        Load(mod.file, mod.name, true, api, onUnload);
    }

    // Loose DLLs straight in the folder, as before packages existed.
    std::vector<std::filesystem::path> files;
    for (const auto& entry : std::filesystem::directory_iterator(dir, ec)) {
        if (entry.is_regular_file() && _wcsicmp(entry.path().extension().c_str(), L".dll") == 0) {
            files.push_back(entry.path());
        }
    }
    std::sort(files.begin(), files.end());  // deterministic load order

    for (const auto& file : files) {
        if (std::any_of(tried.begin(), tried.end(), [&](const auto& t) { return SamePath(t, file); })) {
            continue;
        }
        Load(file, file.stem().string(), false, api, onUnload);
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
