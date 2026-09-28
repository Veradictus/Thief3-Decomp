// The SDK's own start-up and per-frame pump: loads T3SDK.ini, installs the
// crash reporter and the built-in fixes/display/menu features, hooks the main
// loop and process exit, loads mods, and implements the T3SdkApi they call
// into. Initialize() is the only entry point, called once from dllmain.cpp's
// entry-point trampoline on the game's main thread.
#include "sdk.hpp"

#include "crash.hpp"
#include "display.hpp"
#include "engine.hpp"
#include "fixes.hpp"
#include "iat.hpp"
#include "log.hpp"
#include "menu.hpp"
#include "mods.hpp"

#include <MinHook.h>
#include <t3sdk/t3sdk.h>

#include <intrin.h>
#include <tlhelp32.h>

#include <cstdio>
#include <cstring>
#include <filesystem>
#include <string>
#include <vector>

namespace t3sdk {
namespace {

namespace fs = std::filesystem;

struct Settings {
    bool console = false;
    bool engineLog = true;
    int dumpObjectsKey = VK_F10;
    bool menuVersionLabel = true;
    bool menuInputTrace = false;
    fixes::Options fixes;
    display::Options display;
};

struct FrameCallback {
    T3FrameCallback fn;
    void* user;
    HMODULE owner;
};

struct LogCallback {
    T3LogCallback fn;
    void* user;
    HMODULE owner;
};

HMODULE g_self = nullptr;
fs::path g_dir;
Settings g_settings;
DWORD g_mainThread = 0;
bool g_announced = false;
bool g_shutDown = false;
std::vector<FrameCallback> g_frameCallbacks;
std::vector<LogCallback> g_logCallbacks;

using PeekMessageAFn = BOOL(WINAPI*)(LPMSG, HWND, UINT, UINT, UINT);
using ExitProcessFn = void(WINAPI*)(UINT);
using TerminateProcessFn = BOOL(WINAPI*)(HANDLE, UINT);
PeekMessageAFn g_peekMessageA = nullptr;
ExitProcessFn g_exitProcess = nullptr;
TerminateProcessFn g_terminateProcess = nullptr;

fs::path ModulePath(HMODULE module) {
    wchar_t path[MAX_PATH];
    GetModuleFileNameW(module, path, MAX_PATH);
    return path;
}

// Logs who started this process and with which command line. The game
// restarts for every level change, and this shows which program relaunched it
// and what it passed along.
void LogProcessOrigin() {
    DWORD self = GetCurrentProcessId();
    DWORD parent = 0;
    wchar_t parentName[MAX_PATH] = L"?";

    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (snapshot != INVALID_HANDLE_VALUE) {
        PROCESSENTRY32W entry{};
        entry.dwSize = sizeof(entry);
        for (BOOL ok = Process32FirstW(snapshot, &entry); ok; ok = Process32NextW(snapshot, &entry)) {
            if (entry.th32ProcessID == self) {
                parent = entry.th32ParentProcessID;
            }
        }

        // The parent may already have exited; its name then stays "?".
        for (BOOL ok = Process32FirstW(snapshot, &entry); ok && parent; ok = Process32NextW(snapshot, &entry)) {
            if (entry.th32ProcessID == parent) {
                wcsncpy_s(parentName, entry.szExeFile, _TRUNCATE);
            }
        }
        CloseHandle(snapshot);
    }

    T3_LOG("process %lu, started by %ls (%lu), command line: %s", self, parentName, parent, GetCommandLineA());
}

Settings LoadSettings(const fs::path& ini) {
    Settings s;
    const wchar_t* file = ini.c_str();
    s.console = GetPrivateProfileIntW(L"T3SDK", L"Console", s.console, file) != 0;
    s.engineLog = GetPrivateProfileIntW(L"T3SDK", L"EngineLog", s.engineLog, file) != 0;
    wchar_t key[32];
    GetPrivateProfileStringW(L"T3SDK", L"DumpObjectsKey", L"0x79", key, 32, file);
    s.dumpObjectsKey = int(wcstol(key, nullptr, 0));
    s.menuVersionLabel = GetPrivateProfileIntW(L"T3SDK", L"MenuVersionLabel", s.menuVersionLabel, file) != 0;
    s.menuInputTrace = GetPrivateProfileIntW(L"T3SDK", L"MenuInputTrace", s.menuInputTrace, file) != 0;
    s.fixes.skipIntros = GetPrivateProfileIntW(L"Fixes", L"SkipIntros", s.fixes.skipIntros, file) != 0;
    s.display.nativeResolutions =
        GetPrivateProfileIntW(L"Display", L"NativeResolutions", s.display.nativeResolutions, file) != 0;
    s.display.borderless = GetPrivateProfileIntW(L"Display", L"Borderless", s.display.borderless, file) != 0;
    s.display.widescreenUI = GetPrivateProfileIntW(L"Display", L"WidescreenUI", s.display.widescreenUI, file) != 0;
    s.display.uiLayoutTrace = GetPrivateProfileIntW(L"Display", L"UILayoutTrace", s.display.uiLayoutTrace, file) != 0;
    s.display.pauseInBackground =
        GetPrivateProfileIntW(L"Display", L"PauseInBackground", s.display.pauseInBackground, file) != 0;
    return s;
}

// ---- guarded calls into mods -------------------------------------------------
// An exception in a mod callback is logged and that callback disabled, instead
// of reaching the engine's error handler (which ends the game).

struct Fault {
    DWORD code = 0;
    void* address = nullptr;
};

int CaptureFault(EXCEPTION_POINTERS* info, Fault* fault) {
    fault->code = info->ExceptionRecord->ExceptionCode;
    fault->address = info->ExceptionRecord->ExceptionAddress;
    return EXCEPTION_EXECUTE_HANDLER;
}

bool CallFrame(T3FrameCallback fn, void* user, Fault* fault) {
    __try {
        fn(user);
        return true;
    } __except (CaptureFault(GetExceptionInformation(), fault)) {
        return false;
    }
}

bool CallLog(T3LogCallback fn, void* user, const char* text, const char* category, Fault* fault) {
    __try {
        fn(user, text, category);
        return true;
    } __except (CaptureFault(GetExceptionInformation(), fault)) {
        return false;
    }
}

void ReportFault(const char* kind, const void* callback, const Fault& fault) {
    const char* mod = mods::NameAt(callback);
    const char* where = mods::NameAt(fault.address);
    T3_LOG("mod %s: %s callback raised exception 0x%08lX at %p (in %s); callback disabled", mod ? mod : "?", kind,
           fault.code, fault.address, where ? where : "game or SDK code");
}

bool GameHasFocus() {
    DWORD pid = 0;
    GetWindowThreadProcessId(GetForegroundWindow(), &pid);
    return pid == GetCurrentProcessId();
}

size_t CopyOut(const std::string& text, char* buf, size_t size) {
    if (buf && size) {
        size_t n = text.size() < size - 1 ? text.size() : size - 1;
        memcpy(buf, text.data(), n);
        buf[n] = '\0';
    }
    return text.size();
}

// ---- frame pump --------------------------------------------------------------
// Runs once per game frame, on the main thread; drives engine polling and mod
// frame/log callbacks.

void OnEngineLog(const char* text, uint32_t event) {
    std::string category = engine::NameToString(event);
    if (g_settings.engineLog) {
        log::Write("engine", "%s: %s", category.c_str(), text);
    }
    for (auto& cb : g_logCallbacks) {
        Fault fault;
        if (cb.fn && !CallLog(cb.fn, cb.user, text, category.c_str(), &fault)) {
            ReportFault("engine log", reinterpret_cast<const void*>(cb.fn), fault);
            cb.fn = nullptr;
        }
    }
}

void OnFrame() {
    engine::OnFrame();
    if (!engine::Ready()) {
        return;  // not up yet, or shutting down: engine objects are not safe to touch
    }
    if (!g_announced) {
        g_announced = true;
        T3_LOG("engine ready");
    }
    if (g_settings.dumpObjectsKey && (GetAsyncKeyState(g_settings.dumpObjectsKey) & 1) && GameHasFocus()) {
        fs::path file = g_dir / "T3SDK_objects.txt";
        T3_LOG("dumped %d objects to %s", engine::DumpObjects(file), file.string().c_str());
    }
    for (size_t i = 0; i < g_frameCallbacks.size(); ++i) {
        FrameCallback& cb = g_frameCallbacks[i];
        Fault fault;
        if (cb.fn && !CallFrame(cb.fn, cb.user, &fault)) {
            ReportFault("frame", reinterpret_cast<const void*>(cb.fn), fault);
            cb.fn = nullptr;
        }
    }
}

// ---- OS hooks: frame tick and process exit -----------------------------------

// The game's message loop drains PeekMessageA once per frame on the main
// thread; the call that finds the queue empty marks a frame.
BOOL WINAPI PeekMessageADetour(LPMSG msg, HWND window, UINT first, UINT last, UINT remove) {
    BOOL result = g_peekMessageA(msg, window, first, last, remove);
    if (!result && GetCurrentThreadId() == g_mainThread) {
        OnFrame();
    }
    return result;
}

// The game leaves through ExitProcess (CRT exit) or, usually, TerminateProcess
// on itself (Unreal's fast exit). Either way mods get their shutdown call.
void Shutdown(UINT code) {
    if (!g_shutDown) {
        g_shutDown = true;
        mods::ShutdownAll();
        T3_LOG("game exiting (code %u)", code);
    }
}

void WINAPI ExitProcessDetour(UINT code) {
    Shutdown(code);
    g_exitProcess(code);
}

BOOL WINAPI TerminateProcessDetour(HANDLE process, UINT code) {
    if (process == GetCurrentProcess() || GetProcessId(process) == GetCurrentProcessId()) {
        Shutdown(code);
    }
    return g_terminateProcess(process, code);
}

void DropCallbacksOf(HMODULE module) {
    std::erase_if(g_frameCallbacks, [module](const FrameCallback& cb) { return cb.owner == module; });
    std::erase_if(g_logCallbacks, [module](const LogCallback& cb) { return cb.owner == module; });
}

// ---- mod API ---------------------------------------------------------------

void T3SDK_CALL ApiLog(const char* fmt, ...) {
    const char* tag = mods::NameAt(_ReturnAddress());
    va_list args;
    va_start(args, fmt);
    log::WriteV(tag ? tag : "mod", fmt, args);
    va_end(args);
}

int T3SDK_CALL ApiAddFrameCallback(T3FrameCallback callback, void* user) {
    if (!callback) {
        return -1;
    }
    g_frameCallbacks.push_back({callback, user, mods::ModuleAt(_ReturnAddress())});
    return 0;
}

int T3SDK_CALL ApiAddEngineLogCallback(T3LogCallback callback, void* user) {
    if (!callback) {
        return -1;
    }
    g_logCallbacks.push_back({callback, user, mods::ModuleAt(_ReturnAddress())});
    return 0;
}

int T3SDK_CALL ApiCreateHook(void* target, void* detour, void** original) {
    return MH_CreateHook(target, detour, original);
}
int T3SDK_CALL ApiEnableHook(void* target) { return MH_EnableHook(target); }
int T3SDK_CALL ApiDisableHook(void* target) { return MH_DisableHook(target); }
int T3SDK_CALL ApiRemoveHook(void* target) { return MH_RemoveHook(target); }

int T3SDK_CALL ApiEngineReady() { return engine::Ready(); }
int T3SDK_CALL ApiObjectCount() { return engine::ObjectCount(); }
T3Object* T3SDK_CALL ApiObjectAt(int index) { return engine::ObjectAt(index); }
T3Object* T3SDK_CALL ApiFindObject(const char* className, const char* pathName) {
    return engine::FindObject(className, pathName);
}
T3Object* T3SDK_CALL ApiObjectClass(T3Object* object) {
    return object ? reinterpret_cast<T3Object*>(object->Class) : nullptr;
}
T3Object* T3SDK_CALL ApiObjectOuter(T3Object* object) { return engine::Outer(object); }
int T3SDK_CALL ApiIsA(T3Object* object, T3Object* cls) { return engine::IsA(object, cls); }
size_t T3SDK_CALL ApiObjectName(T3Object* object, char* buf, size_t size) {
    return CopyOut(engine::ObjectName(object), buf, size);
}
size_t T3SDK_CALL ApiObjectPathName(T3Object* object, char* buf, size_t size) {
    return CopyOut(engine::PathName(object), buf, size);
}
size_t T3SDK_CALL ApiNameToString(uint32_t name, char* buf, size_t size) {
    return CopyOut(engine::NameToString(name), buf, size);
}

const T3SdkApi g_api = {
    T3SDK_API_VERSION,
    sizeof(T3SdkApi),
    ApiLog,
    ApiAddFrameCallback,
    ApiAddEngineLogCallback,
    ApiCreateHook,
    ApiEnableHook,
    ApiDisableHook,
    ApiRemoveHook,
    ApiEngineReady,
    ApiObjectCount,
    ApiObjectAt,
    ApiFindObject,
    ApiObjectClass,
    ApiObjectOuter,
    ApiIsA,
    ApiObjectName,
    ApiObjectPathName,
    ApiNameToString,
};

// ---- start-up ----------------------------------------------------------------

void Start() {
    g_dir = ModulePath(g_self).parent_path();
    g_settings = LoadSettings(g_dir / "T3SDK.ini");
    log::Open(g_dir / "T3SDK.log", g_settings.console);
    T3_LOG("T3SDK %s in %s", T3SDK_VERSION, ModulePath(nullptr).string().c_str());
    LogProcessOrigin();

    engine::Build build = engine::CheckBuild();
    if (!build.supported) {
        T3_LOG("unsupported T3Main.exe (timestamp %08X, image size %X); SDK disabled, game runs unmodded",
               build.timestamp, build.imageSize);
        return;
    }
    crash::Install(g_self);
    if (MH_STATUS status = MH_Initialize(); status != MH_OK) {
        T3_LOG("MinHook initialisation failed: %s; SDK disabled", MH_StatusToString(status));
        return;
    }

    fixes::Install(g_settings.fixes);
    display::Install(g_settings.display);
    const char* menuVersion = g_settings.menuVersionLabel ? (menu::InstallModdedVersionFormat() ? "ok" : "MISSING") : "off";
    const char* menuInput = g_settings.menuInputTrace ? (menu::InstallInputDiagnostics() ? "ok" : "MISSING") : "off";

    HMODULE exe = GetModuleHandleW(nullptr);
    g_peekMessageA = reinterpret_cast<PeekMessageAFn>(
        PatchImport(exe, "USER32.dll", "PeekMessageA", reinterpret_cast<void*>(&PeekMessageADetour)));
    g_exitProcess = reinterpret_cast<ExitProcessFn>(
        PatchImport(exe, "KERNEL32.dll", "ExitProcess", reinterpret_cast<void*>(&ExitProcessDetour)));
    g_terminateProcess = reinterpret_cast<TerminateProcessFn>(
        PatchImport(exe, "KERNEL32.dll", "TerminateProcess", reinterpret_cast<void*>(&TerminateProcessDetour)));
    engine::SetLogSink(&OnEngineLog);
    bool engineLog = engine::HookEngineLog();
    T3_LOG("hooks: frame %s, exit %s, engine log %s, menu version label %s, menu input trace %s",
           g_peekMessageA ? "ok" : "MISSING", g_exitProcess && g_terminateProcess ? "ok" : "MISSING",
           engineLog ? "ok" : "MISSING", menuVersion, menuInput);

    mods::LoadAll(g_dir / "mods", &g_api, &DropCallbacksOf);
    T3_LOG("started; waiting for the engine");
}

}  // namespace

void Initialize(HMODULE self) {
    g_self = self;
    g_mainThread = GetCurrentThreadId();
    __try {
        Start();
    } __except (EXCEPTION_EXECUTE_HANDLER) {
        T3_LOG("exception 0x%08lX during start-up; SDK left partially initialised", GetExceptionCode());
    }
}

}  // namespace t3sdk
