// The SDK's own start-up and per-frame pump: loads T3SDK.ini, installs the
// crash reporter and the built-in fixes/display/menu features, hooks the main
// loop and process exit, loads mods, and implements the T3SdkApi they call
// into. Initialize() is the only entry point, called once from dllmain.cpp's
// entry-point trampoline on the game's main thread.
//
// The game has no frame callback of its own, so the SDK redirects the exe's
// PeekMessageA import: the call that finds the message queue empty marks a
// frame, and OnFrame() runs there on the main thread. Mods run from that pump
// and through the T3SdkApi table; every call into a mod is guarded so a crash
// in one callback disables that callback instead of the game.
#include "sdk.hpp"

#include "codehook.hpp"
#include "config.hpp"
#include "crash.hpp"
#include "display.hpp"
#include "engine.hpp"
#include "files.hpp"
#include "fixes.hpp"
#include "iat.hpp"
#include "log.hpp"
#include "menu.hpp"
#include "mods.hpp"

#include <MinHook.h>
#include <t3sdk/t3sdk.h>

#include <windows.h>

#include <intrin.h>
#include <tlhelp32.h>

#include <cstdarg>
#include <cstdio>
#include <cstring>
#include <filesystem>
#include <string>
#include <vector>

namespace t3sdk {
namespace {

namespace fs = std::filesystem;

// ---- types and state ---------------------------------------------------------

// What T3SDK.ini holds: the [T3SDK] section here, [Fixes] and [Display] in the members.
struct Settings {
    bool console = false;
    bool engineLog = true;
    int dumpObjectsKey = VK_F10;
    int dumpReflectionDelay = 0;  // seconds after the engine is up; 0 = off
    bool menuVersionLabel = true;
    bool menuInputTrace = false;
    fixes::Options fixes;
    display::Options display;
};

// A frame callback a mod registered, with the mod's module so it can be dropped when the mod is unloaded.
struct FrameCallback {
    T3FrameCallback fn;
    void* user;
    HMODULE owner;
};

// An engine log callback a mod registered, with the mod's module.
struct LogCallback {
    T3LogCallback fn;
    void* user;
    HMODULE owner;
};

// The functions the SDK takes over from the game's import table.
using PeekMessageAFn = BOOL(WINAPI*)(LPMSG, HWND, UINT, UINT, UINT);
using ExitProcessFn = void(WINAPI*)(UINT);
using TerminateProcessFn = BOOL(WINAPI*)(HANDLE, UINT);

// This DLL's module handle, set by Initialize.
HMODULE g_self = nullptr;

// The folder the DLL is in (the game's System folder).
fs::path g_dir;

// T3SDK.ini, read by Start.
Settings g_settings;

// The id of the game's main thread (the one that called Initialize); the frame pump runs only there.
DWORD g_mainThread = 0;

// True once "engine ready" has been logged.
bool g_announced = false;

// GetTickCount() when the engine became ready.
DWORD g_readyAt = 0;

// True once the DumpReflectionDelay dump has been written, so it is written once.
bool g_dumpedReflection = false;

// True once Shutdown has run, so mods are told once.
bool g_shutDown = false;

// Callbacks mods registered. A callback whose `fn` is null has been disabled after a fault.
std::vector<FrameCallback> g_frameCallbacks;
std::vector<LogCallback> g_logCallbacks;

// The originals of the imports PatchImport redirected; nullptr when the exe does not import that function.
PeekMessageAFn g_peekMessageA = nullptr;
ExitProcessFn g_exitProcess = nullptr;
TerminateProcessFn g_terminateProcess = nullptr;

// ---- settings and process info ---------------------------------------------------

// The path of `module`'s file; a null module is the exe.
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

    // Without a snapshot the parent stays unknown.
    if (snapshot != INVALID_HANDLE_VALUE) {
        PROCESSENTRY32W entry{};
        entry.dwSize = sizeof(entry);

        // First pass: this process's entry gives its parent's id.
        for (BOOL ok = Process32FirstW(snapshot, &entry); ok; ok = Process32NextW(snapshot, &entry)) {
            // Only this process's own entry names its parent.
            if (entry.th32ProcessID == self) {
                parent = entry.th32ParentProcessID;
            }
        }

        // The parent may already have exited; its name then stays "?".
        for (BOOL ok = Process32FirstW(snapshot, &entry); ok && parent; ok = Process32NextW(snapshot, &entry)) {
            // Only the parent's entry has the name wanted.
            if (entry.th32ProcessID == parent) {
                wcsncpy_s(parentName, entry.szExeFile, _TRUNCATE);
            }
        }

        CloseHandle(snapshot);
    }

    T3_LOG("process %lu, started by %ls (%lu), command line: %s", self, parentName, parent, GetCommandLineA());
}

// Reads a boolean setting; `fallback` is used when the key is missing.
bool ReadBool(const wchar_t* section, const wchar_t* key, bool fallback, const wchar_t* file) {
    return GetPrivateProfileIntW(section, key, fallback, file) != 0;
}

// Reads the [T3SDK] section of the ini file.
void LoadCoreSettings(Settings& settings, const wchar_t* file) {
    settings.console = ReadBool(L"T3SDK", L"Console", settings.console, file);
    settings.engineLog = ReadBool(L"T3SDK", L"EngineLog", settings.engineLog, file);

    wchar_t key[32];
    GetPrivateProfileStringW(L"T3SDK", L"DumpObjectsKey", L"0x79", key, 32, file);
    settings.dumpObjectsKey = int(wcstol(key, nullptr, 0));

    settings.dumpReflectionDelay = int(GetPrivateProfileIntW(L"T3SDK", L"DumpReflectionDelay", 0, file));
    settings.menuVersionLabel = ReadBool(L"T3SDK", L"MenuVersionLabel", settings.menuVersionLabel, file);
    settings.menuInputTrace = ReadBool(L"T3SDK", L"MenuInputTrace", settings.menuInputTrace, file);
}

// Reads the [Display] section of the ini file.
void LoadDisplaySettings(display::Options& options, const wchar_t* file) {
    options.nativeResolutions = ReadBool(L"Display", L"NativeResolutions", options.nativeResolutions, file);
    options.borderless = ReadBool(L"Display", L"Borderless", options.borderless, file);
    options.widescreenUI = ReadBool(L"Display", L"WidescreenUI", options.widescreenUI, file);
    options.uiLayoutTrace = ReadBool(L"Display", L"UILayoutTrace", options.uiLayoutTrace, file);
    options.pauseInBackground = ReadBool(L"Display", L"PauseInBackground", options.pauseInBackground, file);
    options.smoothFrames = ReadBool(L"Display", L"SmoothFrames", options.smoothFrames, file);
    options.maxFps = int(GetPrivateProfileIntW(L"Display", L"MaxFPS", options.maxFps, file));

    wchar_t scale[32];
    GetPrivateProfileStringW(L"Display", L"CursorScale", L"0", scale, 32, file);
    options.cursorScale = wcstod(scale, nullptr);

    options.frameStats = ReadBool(L"Display", L"FrameStats", options.frameStats, file);
    options.windowedBrightness = ReadBool(L"Display", L"WindowedBrightness", options.windowedBrightness, file);
}

// Reads every setting from the ini file at `ini`; a missing file or key keeps the default.
Settings LoadSettings(const fs::path& ini) {
    Settings settings;
    const wchar_t* file = ini.c_str();

    LoadCoreSettings(settings, file);
    settings.fixes.skipIntros = ReadBool(L"Fixes", L"SkipIntros", settings.fixes.skipIntros, file);
    LoadDisplaySettings(settings.display, file);
    return settings;
}

// ---- guarded calls into mods -------------------------------------------------
// An exception in a mod callback is logged and that callback disabled, instead
// of reaching the engine's error handler (which ends the game).

// The code and address of an exception raised inside a mod callback.
struct Fault {
    DWORD code = 0;
    void* address = nullptr;
};

// SEH filter: records the exception in `fault` and handles it.
int CaptureFault(EXCEPTION_POINTERS* info, Fault* fault) {
    fault->code = info->ExceptionRecord->ExceptionCode;
    fault->address = info->ExceptionRecord->ExceptionAddress;
    return EXCEPTION_EXECUTE_HANDLER;
}

// Calls a mod's frame callback. Returns false, with the exception in `fault`, when it raised one.
bool CallFrame(T3FrameCallback fn, void* user, Fault* fault) {
    // A faulting callback must not reach the engine's error handler.
    __try {
        fn(user);
        return true;
    } __except (CaptureFault(GetExceptionInformation(), fault)) {
        return false;
    }
}

// Calls a mod's engine log callback. Returns false, with the exception in `fault`, when it raised one.
bool CallLog(T3LogCallback fn, void* user, const char* text, const char* category, Fault* fault) {
    // A faulting callback must not reach the engine's error handler.
    __try {
        fn(user, text, category);
        return true;
    } __except (CaptureFault(GetExceptionInformation(), fault)) {
        return false;
    }
}

// Logs which mod's callback faulted and where; `kind` names the callback type.
void ReportFault(const char* kind, const void* callback, const Fault& fault) {
    const char* mod = mods::NameAt(callback);
    const char* where = mods::NameAt(fault.address);
    T3_LOG("mod %s: %s callback raised exception 0x%08lX at %p (in %s); callback disabled", mod ? mod : "?", kind,
           fault.code, fault.address, where ? where : "game or SDK code");
}

// True when the foreground window belongs to this process.
bool GameHasFocus() {
    DWORD pid = 0;
    GetWindowThreadProcessId(GetForegroundWindow(), &pid);
    return pid == GetCurrentProcessId();
}

// Copies `text` into the caller's buffer, truncated and null-terminated. Returns the full length, so a caller can
// size a second buffer.
size_t CopyOut(const std::string& text, char* buf, size_t size) {
    // Do nothing for a missing or empty buffer.
    if (buf && size) {
        size_t length = text.size() < size - 1 ? text.size() : size - 1;
        memcpy(buf, text.data(), length);
        buf[length] = '\0';
    }

    return text.size();
}

// ---- frame pump --------------------------------------------------------------
// Runs once per game frame, on the main thread; drives engine polling and mod
// frame/log callbacks.

// The engine log sink: writes each line to T3SDK.log (when EngineLog is on) and hands it to the mods' log callbacks.
void OnEngineLog(const char* text, uint32_t event) {
    std::string category = engine::NameToString(event);

    // EngineLog off silences the engine lines in T3SDK.log; mods still get them.
    if (g_settings.engineLog) {
        log::Write("engine", "%s: %s", category.c_str(), text);
    }

    // Call every mod's log callback.
    for (auto& callback : g_logCallbacks) {
        Fault fault;

        // A callback that already faulted has been disabled; call the others, guarded.
        if (callback.fn && !CallLog(callback.fn, callback.user, text, category.c_str(), &fault)) {
            ReportFault("engine log", reinterpret_cast<const void*>(callback.fn), fault);
            callback.fn = nullptr;
        }
    }
}

// Logs "engine ready" the first time the engine is usable and remembers when.
void AnnounceReady() {
    // Announce only once.
    if (g_announced) {
        return;
    }

    g_announced = true;
    g_readyAt = GetTickCount();
    T3_LOG("engine ready");
}

// Writes the reflection dump once, DumpReflectionDelay seconds after the engine became ready.
void MaybeDumpReflection() {
    // Dump only when DumpReflectionDelay is set, and only once.
    if (g_settings.dumpReflectionDelay <= 0 || g_dumpedReflection) {
        return;
    }

    // Wait until the delay has passed since the engine became ready.
    if (GetTickCount() - g_readyAt < DWORD(g_settings.dumpReflectionDelay) * 1000) {
        return;
    }

    g_dumpedReflection = true;
    fs::path file = g_dir / "T3SDK_reflection.txt";
    T3_LOG("dumped reflection data of %d objects to %s", engine::DumpReflection(file), file.string().c_str());
}

// Writes the object list when the DumpObjectsKey was pressed while the game has focus.
void MaybeDumpObjects() {
    // The low bit of GetAsyncKeyState is set when the key went down since the last call.
    if (!g_settings.dumpObjectsKey || !(GetAsyncKeyState(g_settings.dumpObjectsKey) & 1) || !GameHasFocus()) {
        return;
    }

    fs::path file = g_dir / "T3SDK_objects.txt";
    T3_LOG("dumped %d objects to %s", engine::DumpObjects(file), file.string().c_str());
}

// Calls every mod's frame callback, guarded; a callback that faults is logged and disabled.
void CallFrameCallbacks() {
    // Index, not iterator: a callback may register another one and grow the vector.
    for (size_t i = 0; i < g_frameCallbacks.size(); ++i) {
        FrameCallback& callback = g_frameCallbacks[i];
        Fault fault;

        // A callback that already faulted has been disabled.
        if (callback.fn && !CallFrame(callback.fn, callback.user, &fault)) {
            ReportFault("frame", reinterpret_cast<const void*>(callback.fn), fault);
            callback.fn = nullptr;
        }
    }
}

// One frame of the SDK, on the main thread: engine polling, the dumps, then the mods' frame callbacks.
void OnFrame() {
    engine::OnFrame();

    // The engine is not up yet, or is shutting down.
    if (!engine::Ready()) {
        return;  // not up yet, or shutting down: engine objects are not safe to touch
    }

    AnnounceReady();
    MaybeDumpReflection();
    MaybeDumpObjects();
    CallFrameCallbacks();
}

// ---- OS hooks: frame tick and process exit -----------------------------------

// The game's message loop drains PeekMessageA once per frame on the main
// thread; the call that finds the queue empty marks a frame.
BOOL WINAPI PeekMessageADetour(LPMSG msg, HWND window, UINT first, UINT last, UINT remove) {
    BOOL result = g_peekMessageA(msg, window, first, last, remove);

    // An empty queue on the main thread is the end of a frame; other threads may call PeekMessageA too.
    if (!result && GetCurrentThreadId() == g_mainThread) {
        OnFrame();
    }

    return result;
}

// The game leaves through ExitProcess (CRT exit) or, usually, TerminateProcess
// on itself (Unreal's fast exit). Either way mods get their shutdown call.
void Shutdown(UINT code) {
    // Tell the mods only once.
    if (g_shutDown) {
        return;
    }

    g_shutDown = true;
    mods::ShutdownAll();
    T3_LOG("game exiting (code %u)", code);
}

// Gives the mods their shutdown call, then exits as the game asked.
void WINAPI ExitProcessDetour(UINT code) {
    Shutdown(code);
    g_exitProcess(code);
}

// Treats terminating this process as an exit; terminating another process is passed through untouched.
BOOL WINAPI TerminateProcessDetour(HANDLE process, UINT code) {
    // Another process being terminated is not the game exiting.
    if (process == GetCurrentProcess() || GetProcessId(process) == GetCurrentProcessId()) {
        Shutdown(code);
    }

    return g_terminateProcess(process, code);
}

// Removes everything a mod registered once its module is unloaded: callbacks, config and file hooks, code hooks.
void DropCallbacksOf(HMODULE module) {
    std::erase_if(g_frameCallbacks, [module](const FrameCallback& callback) { return callback.owner == module; });
    std::erase_if(g_logCallbacks, [module](const LogCallback& callback) { return callback.owner == module; });
    config::DropOwner(module);
    files::DropOwner(module);
    codehook::DropOwner(module);
}

// ---- mod API ---------------------------------------------------------------
// The functions behind T3SdkApi (t3sdk.h documents each member). Mods call them
// on the main thread; those that need to know the calling mod find it from
// the return address.

void T3SDK_CALL ApiLog(const char* fmt, ...) {
    const char* tag = mods::NameAt(_ReturnAddress());
    va_list args;
    va_start(args, fmt);
    log::WriteV(tag ? tag : "mod", fmt, args);
    va_end(args);
}

int T3SDK_CALL ApiAddFrameCallback(T3FrameCallback callback, void* user) {
    // A callback is required.
    if (!callback) {
        return -1;
    }

    g_frameCallbacks.push_back({callback, user, mods::ModuleAt(_ReturnAddress())});
    return 0;
}

int T3SDK_CALL ApiAddEngineLogCallback(T3LogCallback callback, void* user) {
    // A callback is required.
    if (!callback) {
        return -1;
    }

    g_logCallbacks.push_back({callback, user, mods::ModuleAt(_ReturnAddress())});
    return 0;
}

// The hook functions pass straight through to MinHook and return its status.
int T3SDK_CALL ApiCreateHook(void* target, void* detour, void** original) {
    return MH_CreateHook(target, detour, original);
}

int T3SDK_CALL ApiEnableHook(void* target) {
    return MH_EnableHook(target);
}

int T3SDK_CALL ApiDisableHook(void* target) {
    return MH_DisableHook(target);
}

int T3SDK_CALL ApiRemoveHook(void* target) {
    return MH_RemoveHook(target);
}

int T3SDK_CALL ApiEngineReady() {
    return engine::Ready();
}

int T3SDK_CALL ApiObjectCount() {
    return engine::ObjectCount();
}

T3Object* T3SDK_CALL ApiObjectAt(int index) {
    return engine::ObjectAt(index);
}

T3Object* T3SDK_CALL ApiFindObject(const char* className, const char* pathName) {
    return engine::FindObject(className, pathName);
}

T3Object* T3SDK_CALL ApiObjectClass(T3Object* object) {
    return object ? reinterpret_cast<T3Object*>(object->Class) : nullptr;
}

T3Object* T3SDK_CALL ApiObjectOuter(T3Object* object) {
    return engine::Outer(object);
}

int T3SDK_CALL ApiIsA(T3Object* object, T3Object* cls) {
    return engine::IsA(object, cls);
}

size_t T3SDK_CALL ApiObjectName(T3Object* object, char* buf, size_t size) {
    return CopyOut(engine::ObjectName(object), buf, size);
}

size_t T3SDK_CALL ApiObjectPathName(T3Object* object, char* buf, size_t size) {
    return CopyOut(engine::PathName(object), buf, size);
}

size_t T3SDK_CALL ApiNameToString(uint32_t name, char* buf, size_t size) {
    return CopyOut(engine::NameToString(name), buf, size);
}

int T3SDK_CALL ApiSetConfigValue(const char* file, const char* section, const char* key, const char* value) {
    return config::SetValue(file, section, key, value, mods::ModuleAt(_ReturnAddress()));
}

int T3SDK_CALL ApiAddConfigCallback(T3ConfigCallback callback, void* user) {
    return config::AddCallback(callback, user, mods::ModuleAt(_ReturnAddress()));
}

// Adds a folder the game's file lookups also search. A relative path is taken from the calling mod's folder.
int T3SDK_CALL ApiAddFileRoot(const char* dir) {
    // A folder is required.
    if (!dir) {
        return -1;
    }

    HMODULE owner = mods::ModuleAt(_ReturnAddress());
    fs::path path(std::u8string(reinterpret_cast<const char8_t*>(dir)));

    // Relative to the mod's own folder, or to the SDK's when the caller is not a mod.
    if (path.is_relative()) {
        path = (owner ? ModulePath(owner).parent_path() : g_dir) / path;
    }

    return files::AddRoot(path, owner);
}

int T3SDK_CALL ApiAddCodeHook(void* address, T3CodeCallback callback, void* user) {
    return codehook::Add(address, callback, user, mods::ModuleAt(_ReturnAddress()));
}

// The table handed to every mod. Members stay in this order (t3sdk.h); new ones go at the end.
const T3SdkApi g_api = {
    T3SDK_API_VERSION,       sizeof(T3SdkApi),  ApiLog,          ApiAddFrameCallback,
    ApiAddEngineLogCallback, ApiCreateHook,     ApiEnableHook,   ApiDisableHook,
    ApiRemoveHook,           ApiEngineReady,    ApiObjectCount,  ApiObjectAt,
    ApiFindObject,           ApiObjectClass,    ApiObjectOuter,  ApiIsA,
    ApiObjectName,           ApiObjectPathName, ApiNameToString, ApiSetConfigValue,
    ApiAddConfigCallback,    ApiAddFileRoot,    ApiAddCodeHook,
};

// ---- start-up ----------------------------------------------------------------

// Reads T3SDK.ini, opens T3SDK.log and logs the process's origin.
void OpenLogAndSettings() {
    g_dir = ModulePath(g_self).parent_path();
    g_settings = LoadSettings(g_dir / "T3SDK.ini");
    log::Open(g_dir / "T3SDK.log", g_settings.console);

    T3_LOG("T3SDK %s in %s", T3SDK_VERSION, ModulePath(nullptr).string().c_str());
    LogProcessOrigin();
}

// Checks that this is the supported T3Main.exe build. Logs and returns false when it is not.
bool BuildIsSupported() {
    engine::Build build = engine::CheckBuild();

    // An unsupported build gets no hooks at all.
    if (!build.supported) {
        T3_LOG("unsupported T3Main.exe (timestamp %08X, image size %X); SDK disabled, game runs unmodded",
               build.timestamp, build.imageSize);
        return false;
    }

    return true;
}

// Redirects the exe's imports for the frame tick and for process exit.
void HookOsImports() {
    HMODULE exe = GetModuleHandleW(nullptr);
    g_peekMessageA = reinterpret_cast<PeekMessageAFn>(
        PatchImport(exe, "USER32.dll", "PeekMessageA", reinterpret_cast<void*>(&PeekMessageADetour)));
    g_exitProcess = reinterpret_cast<ExitProcessFn>(
        PatchImport(exe, "KERNEL32.dll", "ExitProcess", reinterpret_cast<void*>(&ExitProcessDetour)));
    g_terminateProcess = reinterpret_cast<TerminateProcessFn>(
        PatchImport(exe, "KERNEL32.dll", "TerminateProcess", reinterpret_cast<void*>(&TerminateProcessDetour)));
}

// Installs everything the SDK hooks in the game, then logs one line saying which hooks are in place.
void InstallHooks() {
    fixes::Install(g_settings.fixes);
    display::Install(g_settings.display);
    const char* menuVersion =
        g_settings.menuVersionLabel ? (menu::InstallModdedVersionFormat() ? "ok" : "MISSING") : "off";
    const char* menuInput = g_settings.menuInputTrace ? (menu::InstallInputDiagnostics() ? "ok" : "MISSING") : "off";

    HookOsImports();
    engine::SetLogSink(&OnEngineLog);
    bool engineLog = engine::HookEngineLog();
    bool configHook = config::Install();
    files::Install(g_dir.parent_path());

    T3_LOG("hooks: frame %s, exit %s, engine log %s, config %s, menu version label %s, menu input trace %s",
           g_peekMessageA ? "ok" : "MISSING", g_exitProcess && g_terminateProcess ? "ok" : "MISSING",
           engineLog ? "ok" : "MISSING", configHook ? "ok" : "MISSING", menuVersion, menuInput);
}

// The whole start-up: settings and log, build check, crash reporter, MinHook, hooks, then the mods.
void Start() {
    OpenLogAndSettings();

    // Leave the game unmodded on an unsupported build.
    if (!BuildIsSupported()) {
        return;
    }

    crash::Install(g_self);
    MH_STATUS status = MH_Initialize();

    // Nothing can be hooked without MinHook.
    if (status != MH_OK) {
        T3_LOG("MinHook initialisation failed: %s; SDK disabled", MH_StatusToString(status));
        return;
    }

    InstallHooks();
    mods::LoadAll(g_dir / "mods", &g_api, &DropCallbacksOf);
    T3_LOG("started; waiting for the engine");
}

}  // namespace

void Initialize(HMODULE self) {
    g_self = self;
    g_mainThread = GetCurrentThreadId();

    // Anything thrown during start-up must not end the game before it has begun.
    __try {
        Start();
    } __except (EXCEPTION_EXECUTE_HANDLER) {
        T3_LOG("exception 0x%08lX during start-up; SDK left partially initialised", GetExceptionCode());
    }
}

}  // namespace t3sdk
