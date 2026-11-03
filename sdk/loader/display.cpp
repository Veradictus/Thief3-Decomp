// The display features, each behind its own T3SDK.ini option (see
// display.hpp): rewriting the resolution table, running the Direct3D 8 device
// windowed and borderless (with what that needs: the game's cursor and VSync,
// bringing the window to the front, covering level changes, running in the
// background), frame pacing, and rescaling the UI layout for widescreen.
// Facts and evidence for the addresses below are in docs/engine.md.
#include "display.hpp"

#include "curtain.hpp"
#include "engine.hpp"
#include "iat.hpp"
#include "log.hpp"

#include <MinHook.h>

#include <windows.h>
#include <shellapi.h>

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <cstring>
#include <set>
#include <utility>
#include <vector>

namespace t3sdk::display {
namespace {

// ---- resolution table ---------------------------------------------------------
// The Resolution option indexes two parallel tables of five entries; the game
// clamps the index to 0..4 and falls back to lower entries the adapter lacks.

// uint32_t[5] of widths: 640, 800, 1024, 1280, 1600 (docs/engine.md, "Options").
constexpr uintptr_t kResolutionWidths = 0x10E6EDC4;

// uint32_t[5] of heights: 480, 600, 768, 1024, 1200 (docs/engine.md, "Options").
constexpr uintptr_t kResolutionHeights = 0x10E6EDD8;

constexpr int kResolutionCount = 5;

using Mode = std::pair<uint32_t, uint32_t>;  // width, height

// The 32-bit display modes of the primary monitor. `native` receives its
// current mode.
std::set<Mode> MonitorModes(Mode* native) {
    std::set<Mode> modes;
    DEVMODEW mode{};
    mode.dmSize = sizeof(mode);

    // Walk every display mode the monitor lists.
    for (DWORD i = 0; EnumDisplaySettingsW(nullptr, i, &mode); ++i) {
        // Only 32-bit modes count.
        if (mode.dmBitsPerPel == 32) {
            modes.insert({mode.dmPelsWidth, mode.dmPelsHeight});
        }
    }

    EnumDisplaySettingsW(nullptr, ENUM_CURRENT_SETTINGS, &mode);
    *native = {mode.dmPelsWidth, mode.dmPelsHeight};
    return modes;
}

// Native resolution last; before it the largest smaller modes with the same
// aspect ratio, topped up with classic 4:3 modes (those not listed yet) when
// there are too few.
std::vector<Mode> ChooseResolutions() {
    Mode native;
    std::set<Mode> modes = MonitorModes(&native);
    const double aspect = double(native.first) / native.second;

    // The monitor's smaller modes with the native aspect ratio, largest first.
    std::vector<Mode> smaller;

    // Pick the modes that are smaller than native with the native aspect ratio.
    for (const Mode& mode : modes) {
        bool sameAspect = std::fabs(double(mode.first) / mode.second - aspect) < 0.01;

        // Both sides must be smaller than the native resolution.
        if (sameAspect && mode.first < native.first && mode.second < native.second) {
            smaller.push_back(mode);
        }
    }

    std::sort(smaller.begin(), smaller.end(),
              [](const Mode& a, const Mode& b) { return uint64_t(a.first) * a.second > uint64_t(b.first) * b.second; });
    smaller.resize(std::min<size_t>(smaller.size(), kResolutionCount - 1));

    // Top up with classic modes while the list is short.
    for (Mode classic : {Mode{1024, 768}, Mode{800, 600}, Mode{640, 480}}) {
        bool listed = std::find(smaller.begin(), smaller.end(), classic) != smaller.end();

        // Add a classic mode only when the list is short, it is narrower than native and it is not listed yet.
        if (smaller.size() < kResolutionCount - 1 && classic.first < native.first && !listed) {
            smaller.push_back(classic);
        }
    }

    // Ascending, then the native resolution last.
    std::sort(smaller.begin(), smaller.end(),
              [](const Mode& a, const Mode& b) { return uint64_t(a.first) * a.second < uint64_t(b.first) * b.second; });
    smaller.push_back(native);

    // Tiny desktops: repeat the native resolution.
    while (smaller.size() < kResolutionCount) {
        smaller.push_back(native);
    }

    return smaller;
}

// Writes the chosen resolutions into the game's two tables and logs them.
void PatchResolutionTable() {
    std::vector<Mode> table = ChooseResolutions();
    auto widths = reinterpret_cast<uint32_t*>(kResolutionWidths);
    auto heights = reinterpret_cast<uint32_t*>(kResolutionHeights);

    DWORD protect;
    VirtualProtect(widths, 2 * kResolutionCount * sizeof(uint32_t), PAGE_READWRITE, &protect);

    // Write every table entry.
    for (int i = 0; i < kResolutionCount; ++i) {
        widths[i] = table[i].first;
        heights[i] = table[i].second;
    }

    VirtualProtect(widths, 2 * kResolutionCount * sizeof(uint32_t), protect, &protect);

    T3_LOG("display: resolutions %ux%u, %ux%u, %ux%u, %ux%u, %ux%u (option 4 = native)", widths[0], heights[0],
           widths[1], heights[1], widths[2], heights[2], widths[3], heights[3], widths[4], heights[4]);
}

// ---- borderless window ----------------------------------------------------------
// Direct3D 8 layouts (d3d8.h), so no DirectX 8 SDK is needed.
struct PresentParameters {
    UINT BackBufferWidth;
    UINT BackBufferHeight;
    UINT BackBufferFormat;
    UINT BackBufferCount;
    UINT MultiSampleType;
    UINT SwapEffect;
    HWND hDeviceWindow;
    BOOL Windowed;
    BOOL EnableAutoDepthStencil;
    UINT AutoDepthStencilFormat;
    DWORD Flags;
    UINT FullScreen_RefreshRateInHz;
    UINT FullScreen_PresentationInterval;
};

struct DisplayMode {
    UINT Width;
    UINT Height;
    UINT RefreshRate;
    UINT Format;
};

constexpr UINT kSwapEffectDiscard = 1;
constexpr UINT kSwapEffectCopyVSync = 4;
constexpr UINT kPresentIntervalOne = 1;

// Slots in the IDirect3D8 and IDirect3DDevice8 vtables.
constexpr int kD3D8CreateDevice = 15;            // IDirect3D8
constexpr int kD3D8GetAdapterDisplayMode = 8;    // IDirect3D8
constexpr int kD3D8CheckDeviceType = 9;          // IDirect3D8
constexpr int kD3D8CheckDepthStencilMatch = 12;  // IDirect3D8
constexpr int kDevice8Reset = 14;                // IDirect3DDevice8

using Direct3DCreate8Fn = void*(WINAPI*)(UINT);
using CheckDeviceTypeFn = HRESULT(WINAPI*)(void* d3d, UINT adapter, UINT type, UINT displayFormat,
                                           UINT backBufferFormat, BOOL windowed);
using CheckDepthStencilMatchFn = HRESULT(WINAPI*)(void* d3d, UINT adapter, UINT type, UINT adapterFormat,
                                                  UINT renderTargetFormat, UINT depthStencilFormat);
using CreateDeviceFn = HRESULT(WINAPI*)(void* d3d, UINT adapter, UINT type, HWND focus, DWORD flags,
                                        PresentParameters* params, void** device);
using ResetFn = HRESULT(WINAPI*)(void* device, PresentParameters* params);
using GetAdapterDisplayModeFn = HRESULT(WINAPI*)(void* d3d, UINT adapter, DisplayMode* mode);

// The originals of the hooked Direct3D 8 functions (null until hooked).
Direct3DCreate8Fn g_direct3DCreate8 = nullptr;
CreateDeviceFn g_createDevice = nullptr;
ResetFn g_reset = nullptr;

bool g_borderless = false;  // [Display] Borderless is on and the Direct3DCreate8 import was found
HWND g_window = nullptr;    // the game's device window, set when the device is created
UINT g_desktopFormat = 0;   // the desktop's back buffer format, read before a windowed device is created
UINT g_desktopRefresh = 0;  // the desktop's refresh rate on the game's adapter, read with the format

// The IDirect3D8 object, adapter and device type the game created its device with, for format checks on a reset.
void* g_d3d = nullptr;
UINT g_adapter = 0;
UINT g_deviceType = 0;

// Fills in the desktop's refresh rate for an exclusive fullscreen device that leaves it to Direct3D.
void UseDesktopRefresh(PresentParameters* params);

// The function in slot `slot` of the vtable of the COM-style `object`.
void* VtableEntry(void* object, int slot) {
    return (*reinterpret_cast<void***>(object))[slot];
}

// Hooks `target` and enables the hook. Returns true when both steps worked.
bool HookFunction(void* target, void* detour, void** original) {
    return MH_CreateHook(target, detour, original) == MH_OK && MH_EnableHook(target) == MH_OK;
}

// Whether the back buffer format in `params` works for a window on the
// desktop. The game asks for A8R8G8B8 (UD3DRenderDevice::SetRes, 0x10C844E4)
// and uses its alpha: some lighting passes write a mask into it and blend
// with DESTALPHA. The desktop's X8R8G8B8 has no alpha, so those passes
// light at full strength and surfaces turn white. Direct3D 8 allows an
// A8R8G8B8 back buffer in a window on an X8R8G8B8 desktop where the driver
// says so.
bool WindowedFormatWorks(const PresentParameters* params) {
    // Without the creating object there is nothing to ask.
    if (!g_d3d) {
        return false;
    }

    auto checkType = reinterpret_cast<CheckDeviceTypeFn>(VtableEntry(g_d3d, kD3D8CheckDeviceType));

    // The adapter has to show this back buffer format in a window.
    if (FAILED(checkType(g_d3d, g_adapter, g_deviceType, g_desktopFormat, params->BackBufferFormat, TRUE))) {
        return false;
    }

    // And the depth buffer the game asks for has to go with it.
    if (params->EnableAutoDepthStencil) {
        auto checkDepth = reinterpret_cast<CheckDepthStencilMatchFn>(VtableEntry(g_d3d, kD3D8CheckDepthStencilMatch));
        return SUCCEEDED(checkDepth(g_d3d, g_adapter, g_deviceType, g_desktopFormat, params->BackBufferFormat,
                                    params->AutoDepthStencilFormat));
    }

    return true;
}

// Presentation parameters for a windowed device of the size the game asked
// for. The game's VSync option asks a fullscreen device to present once per
// refresh (UD3DRenderDevice::SetRes, 0x10C84070); a window gets the same from
// the swap effect, which allows neither multisampling nor extra back buffers.
void MakeWindowed(PresentParameters* params) {
    // Already windowed: nothing to change.
    if (params->Windowed) {
        return;
    }

    const bool vsync = params->FullScreen_PresentationInterval == kPresentIntervalOne && !params->MultiSampleType;
    params->Windowed = TRUE;
    params->SwapEffect = vsync ? kSwapEffectCopyVSync : kSwapEffectDiscard;

    // A VSync swap effect allows a single back buffer.
    if (vsync) {
        params->BackBufferCount = 1;
    }

    params->FullScreen_RefreshRateInHz = 0;
    params->FullScreen_PresentationInterval = 0;  // D3DPRESENT_INTERVAL_DEFAULT: required when windowed

    // The game's own format stays when the adapter can show it in a window; otherwise the desktop's.
    if (g_desktopFormat && !WindowedFormatWorks(params)) {
        params->BackBufferFormat = g_desktopFormat;
    }
}

// ", VSync" when `params` asks for the VSync swap effect, for the log.
const char* VSyncNote(const PresentParameters* params) {
    return params->SwapEffect == kSwapEffectCopyVSync ? ", VSync" : "";
}

// The rectangle of the monitor `window` is on.
RECT MonitorRect(HWND window) {
    MONITORINFO monitor{};
    monitor.cbSize = sizeof(monitor);
    GetMonitorInfoW(MonitorFromWindow(window, MONITOR_DEFAULTTOPRIMARY), &monitor);
    return monitor.rcMonitor;
}

// A popup window covering the monitor it is on; Present scales the back buffer to it.
void MakeBorderless(HWND window) {
    // No window yet: nothing to change.
    if (!window) {
        return;
    }

    const RECT rect = MonitorRect(window);
    SetWindowLongW(window, GWL_STYLE, WS_POPUP | WS_VISIBLE);
    SetWindowLongW(window, GWL_EXSTYLE, GetWindowLongW(window, GWL_EXSTYLE) & ~(WS_EX_TOPMOST | WS_EX_WINDOWEDGE));
    SetWindowPos(window, HWND_NOTOPMOST, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top,
                 SWP_FRAMECHANGED | SWP_SHOWWINDOW);
}

// ---- level changes ------------------------------------------------------------
// T3 restarts for every level change (New Game, entering or leaving a
// mission). The outgoing game draws the next level's loading screen, starts
// the game's launcher with the level and ends; the launcher starts a new
// T3Main.exe, which draws the same loading screen while it loads the level
// (RelaunchForLevelChange at 0x10901D60, LoadingScreen::Begin at 0x109E1FC0).
// An exclusive fullscreen device takes the screen when it is created; a
// borderless window has to be brought to the front, and Windows only allows
// that when the program in front lets it. So the outgoing game passes that
// right on while it still has the foreground, and covers its monitor with the
// loading screen until the incoming game has drawn its own (curtain.hpp).
// Without this the player lands on the desktop for seconds, then has to
// click the game.

// The file name of the launcher the game starts for a level change.
constexpr char kGameLauncher[] = "Ion Launcher.exe";

// void LoadingScreen::Begin(IDirect3DDevice8* device, const char* map, bool), __cdecl.
constexpr uintptr_t kLoadingScreenBegin = 0x109E1FC0;

using ShellExecuteExAFn = BOOL(WINAPI*)(SHELLEXECUTEINFOA* info);
using LoadingScreenBeginFn = void(__cdecl*)(void* device, const char* map, int flag);

ShellExecuteExAFn g_shellExecuteExA = nullptr;
LoadingScreenBeginFn g_loadingScreenBegin = nullptr;

// Whether the window in front belongs to this process.
bool OwnsForeground() {
    DWORD pid = 0;
    GetWindowThreadProcessId(GetForegroundWindow(), &pid);
    return pid == GetCurrentProcessId();
}

// Whether `info` starts the game's launcher.
bool StartsGameLauncher(const SHELLEXECUTEINFOA* info) {
    // Without a file name this is not the launcher.
    if (!info || !info->lpFile) {
        return false;
    }

    const char* name = strrchr(info->lpFile, '\\');
    return _stricmp(name ? name + 1 : info->lpFile, kGameLauncher) == 0;
}

// Detour of the ShellExecuteExA import: when the game starts its launcher for
// a level change, lets the next game take the foreground and raises the curtain.
BOOL WINAPI ShellExecuteExADetour(SHELLEXECUTEINFOA* info) {
    // Only when the player is in the game: a level change while they work in
    // another program must neither cover a screen nor pull the next game to
    // the front.
    if (StartsGameLauncher(info) && OwnsForeground()) {
        AllowSetForegroundWindow(ASFW_ANY);

        // Raise the curtain over the game's monitor once the window is known.
        if (g_window) {
            curtain::Raise(MonitorRect(g_window));
        }

        T3_LOG("display: level change; the next game window may come to the front");
    }

    return g_shellExecuteExA(info);
}

// The outgoing game draws the loading screen before it raises the curtain,
// so the curtain found here is always a previous game's.
void __cdecl LoadingScreenBeginDetour(void* device, const char* map, int flag) {
    g_loadingScreenBegin(device, map, flag);
    curtain::Lift(g_window);
}

// Called once per game process, when its window is created: the moment an
// exclusive fullscreen device would have taken the screen. Windows refuses a
// plain SetForegroundWindow when the game was started by a background
// process (Steam, the game's launcher after a level change), so the fallback
// briefly shares input with the window in front, which lets the call through.
void BringToFront(HWND window) {
    HWND front = GetForegroundWindow();

    // Nothing to do without a window, or when it is in front already.
    if (!window || front == window) {
        return;
    }

    // The plain call works when Windows lets this process take the foreground.
    if (SetForegroundWindow(window)) {
        T3_LOG("display: window brought to the front");
        return;
    }

    DWORD self = GetCurrentThreadId();
    DWORD frontThread = front ? GetWindowThreadProcessId(front, nullptr) : 0;
    bool attached = frontThread && frontThread != self && AttachThreadInput(self, frontThread, TRUE);
    BringWindowToTop(window);
    SetForegroundWindow(window);
    SetFocus(window);

    // Detach from the input of the window that was in front.
    if (attached) {
        AttachThreadInput(self, frontThread, FALSE);
    }

    // Report whether the fallback worked.
    if (GetForegroundWindow() == window) {
        T3_LOG("display: window brought to the front (through the window in front)");
    } else {
        T3_LOG("display: Windows kept another program in front of the game window");
    }
}

// ---- device reset -----------------------------------------------------------------

// The present parameters the viewport's WM_ACTIVATEAPP handler (call at
// 0x10C8BF6B) resets the device with when the game loses focus, unless the
// device is already lost, which an exclusive fullscreen device always is by
// then. They are not the device's own: this global is only touched by
// InitDirect3D and stays zero in play (the real ones are at
// UD3DRenderDevice+0x4630, which SetRes resets with at 0x10C84693). So the
// reset asks for a 0x0 back buffer and fails, and the engine then waits for
// the device forever: the game freezes after alt-tab, a click on another
// monitor, or closing the window. Skipping it loses nothing; a lost device
// still recovers through SetRes.
constexpr uintptr_t kFocusLossPresentParams = 0x10F2C86C;

// Detour of IDirect3DDevice8::Reset: skips the focus-loss reset and any reset
// while the game exits, and keeps every other reset windowed and borderless.
HRESULT WINAPI ResetDetour(void* device, PresentParameters* params) {
    // Exclusive fullscreen loses its device on a focus change, so the game never makes its focus-loss reset there.
    // But Windows' fullscreen optimisations keep the device, and the game then makes that reset, which fails (0x0)
    // and loses the device for real: skip it, as borderless does.
    if (!g_borderless && reinterpret_cast<uintptr_t>(params) == kFocusLossPresentParams) {
        T3_LOG("display: focus-loss Reset skipped (fullscreen kept its device)");
        return S_OK;
    }

    // Exclusive fullscreen: other resets go through (they restore the device after a focus change), at the
    // desktop's refresh rate.
    if (!g_borderless) {
        UseDesktopRefresh(params);
        HRESULT result = g_reset(device, params);
        T3_LOG("display: Reset %ux%u %s at %u Hz, present interval %u -> 0x%08lX", params->BackBufferWidth,
               params->BackBufferHeight, params->Windowed ? "windowed" : "fullscreen",
               params->FullScreen_RefreshRateInHz, params->FullScreen_PresentationInterval, result);
        return result;
    }

    // The focus-loss reset: skip it.
    if (reinterpret_cast<uintptr_t>(params) == kFocusLossPresentParams) {
        T3_LOG("display: focus-loss Reset skipped (the borderless device stays as it is)");
        return S_OK;
    }

    // Nothing to reset while shutting down either.
    if (engine::Exiting()) {
        T3_LOG("display: Reset skipped, the game is exiting");
        return S_OK;
    }

    MakeWindowed(params);
    HRESULT result = g_reset(device, params);
    MakeBorderless(g_window);
    T3_LOG("display: Reset %ux%u windowed%s, format %u -> 0x%08lX", params->BackBufferWidth, params->BackBufferHeight,
           VSyncNote(params), params->BackBufferFormat, result);
    return result;
}

// ---- frame pacing ---------------------------------------------------------------------
// The engine's clock (TimeManager, advanced by EndFrame at 0x10D3EDF0 once a
// frame) moves the world only once 10 ms have passed and carries shorter
// frames over to the next one. That caps the world at 100 updates a second:
// above 100 fps the world, and the camera with it, moves on every second or
// third frame, unevenly, and the game looks choppy however high the frame
// rate is. [Display] SmoothFrames lowers that minimum step, which the
// TimeManager constructor sets (later only the SIMTIME SETMIN console command
// changes it), so every frame moves the world.

// The imm32 of MOV [ESI+4], 0.01f in TimeManager::TimeManager.
constexpr uintptr_t kTimeManagerMinStep = 0x10D3EBA1;

// What the engine stores there: 0.01f as a 32-bit pattern.
constexpr uint32_t kEngineMinStep = 0x3C23D70A;

// The step SmoothFrames stores instead: every frame moves the world, up to 1000 fps.
constexpr float kSmoothMinStep = 0.001f;

// Replaces the engine's minimum world step, after checking that the code at
// the address is what the patch expects.
void LowerMinimumStep() {
    auto step = reinterpret_cast<uint32_t*>(kTimeManagerMinStep);

    // Patch only when the instruction holds the expected value.
    if (*step != kEngineMinStep) {
        T3_LOG("display: smooth frames not applied, unexpected code at %08X", unsigned(kTimeManagerMinStep));
        return;
    }

    DWORD protect;
    VirtualProtect(step, sizeof(*step), PAGE_EXECUTE_READWRITE, &protect);
    memcpy(step, &kSmoothMinStep, sizeof(*step));
    VirtualProtect(step, sizeof(*step), protect, &protect);
    FlushInstructionCache(GetCurrentProcess(), step, sizeof(*step));
}

// [Display] MaxFPS holds each frame back until its turn, so frames leave at an
// even pace (and the world, which steps by the frame time, moves evenly).
// [Display] FrameStats logs frames per second and the time spent in Present
// every 10 seconds; a Present that takes a whole frame means something below
// the game (VSync, runtime, driver, compositor) paces it.
constexpr int kDevice8Present = 15;  // IDirect3DDevice8 vtable slot

using PresentFn = HRESULT(WINAPI*)(void* device, const RECT* source, const RECT* dest, HWND window, const void* dirty);

// State of the frame limiter and the statistics.
PresentFn g_present = nullptr;
LARGE_INTEGER g_ticksPerSecond{};
LONGLONG g_frameTicks = 0;      // the frame interval for MaxFPS; 0 = no limit
LONGLONG g_nextFrame = 0;       // when the next frame may be presented
HANDLE g_frameTimer = nullptr;  // high-resolution timer; without one the wait spins
bool g_frameStats = false;      // [Display] FrameStats
LARGE_INTEGER g_statsStart{};   // when the current statistics period began
LONGLONG g_presentTicks = 0;    // time spent in Present during the period
int g_frames = 0;               // frames presented during the period

// Logs and resets the cursor call counters; defined with the cursor.
void LogCursorCalls();

// Blocks until the next frame's turn: sleeps on the timer, then spins for the
// last millisecond.
void WaitForFrameTurn() {
    LARGE_INTEGER now;
    QueryPerformanceCounter(&now);

    // More than a frame late (or the first frame): start a new schedule
    // instead of hurrying frames out to catch up.
    if (now.QuadPart - g_nextFrame > g_frameTicks) {
        g_nextFrame = now.QuadPart;
    }

    // Sleep until a millisecond before the turn, then spin: timers wake late.
    const LONGLONG sleep = g_nextFrame - now.QuadPart - g_ticksPerSecond.QuadPart / 1000;

    // Wait on the timer only when the turn is more than a millisecond away and a timer exists.
    if (sleep > 0 && g_frameTimer) {
        LARGE_INTEGER due;
        due.QuadPart = -sleep * 10000000 / g_ticksPerSecond.QuadPart;  // relative, in 100 ns units

        // Wait only when the timer was armed.
        if (SetWaitableTimer(g_frameTimer, &due, 0, nullptr, nullptr, FALSE)) {
            WaitForSingleObject(g_frameTimer, INFINITE);
        }
    }

    // Spin for the rest of the wait.
    while (now.QuadPart < g_nextFrame) {
        YieldProcessor();
        QueryPerformanceCounter(&now);
    }

    g_nextFrame += g_frameTicks;
}

// Adds a frame whose Present began at `before` to the statistics, and logs
// them every 10 seconds.
void CountFrame(const LARGE_INTEGER& before) {
    LARGE_INTEGER after;
    QueryPerformanceCounter(&after);
    g_presentTicks += after.QuadPart - before.QuadPart;
    ++g_frames;

    const double seconds = double(after.QuadPart - g_statsStart.QuadPart) / double(g_ticksPerSecond.QuadPart);

    // Report only once 10 seconds have passed.
    if (seconds < 10.0) {
        return;
    }

    const double presentMs = 1000.0 * double(g_presentTicks) / double(g_ticksPerSecond.QuadPart) / g_frames;
    T3_LOG("display: %.1f fps, %.2f ms per frame in Present", g_frames / seconds, presentMs);
    LogCursorCalls();
    g_statsStart = after;
    g_presentTicks = 0;
    g_frames = 0;
}

// Detour of IDirect3DDevice8::Present: waits for the frame's turn when MaxFPS
// is set and times the call when FrameStats is on.
HRESULT WINAPI PresentDetour(void* device, const RECT* source, const RECT* dest, HWND window, const void* dirty) {
    // Hold the frame back when MaxFPS is set.
    if (g_frameTicks) {
        WaitForFrameTurn();
    }

    LARGE_INTEGER before;
    QueryPerformanceCounter(&before);
    HRESULT result = g_present(device, source, dest, window, dirty);

    // Time the call when FrameStats is on.
    if (g_frameStats) {
        CountFrame(before);
    }

    return result;
}

// Hooks Present on `device` and starts the statistics period.
void HookPresent(void* device) {
    void* present = VtableEntry(device, kDevice8Present);

    // Start the statistics period once the hook is in.
    if (HookFunction(present, reinterpret_cast<void*>(&PresentDetour), reinterpret_cast<void**>(&g_present))) {
        QueryPerformanceCounter(&g_statsStart);
        T3_LOG("display: Present hooked (frame limit %s, frame statistics %s)", g_frameTicks ? "on" : "off",
               g_frameStats ? "on" : "off");
    }
}

// ---- cursor ---------------------------------------------------------------------------
// The game's menu cursor is a Direct3D hardware cursor: a 32x32 image, sized
// for the screens of 2004, that the game sets again every frame (device
// SetCursorProperties and ShowCursor, user32 ShowCursor and SetCursor). In a
// window, Direct3D 8 imitates the hardware cursor with a Windows cursor it
// rebuilds on every such call, while the game's own SetCursor works against
// it: the cursor flickers, and it is tiny on a large screen. So with a
// borderless window the SDK owns the cursor: one Windows cursor built from the
// game's image (again only when the image changes), scaled to the screen, and
// shown whenever the game shows its cursor. Direct3D's imitation stays off.

// Slots in the IDirect3DDevice8 vtable.
constexpr int kDevice8SetCursorProperties = 10;
constexpr int kDevice8SetCursorPosition = 11;
constexpr int kDevice8ShowCursor = 12;

// Slots in the IDirect3DSurface8 vtable.
constexpr int kSurface8GetDesc = 8;
constexpr int kSurface8LockRect = 9;
constexpr int kSurface8UnlockRect = 10;

constexpr UINT kFormatA8R8G8B8 = 21;
constexpr DWORD kLockReadOnly = 0x10;  // D3DLOCK_READONLY
constexpr UINT kMaxCursorSide = 256;
constexpr UINT kMaxGameCursorSide = 64;        // larger game cursor images are left to Direct3D
constexpr double kCursorDesignHeight = 768.0;  // the screen height the cursor looks right on

struct SurfaceDesc {  // D3DSURFACE_DESC (d3d8.h)
    UINT Format;
    UINT Type;
    DWORD Usage;
    UINT Pool;
    UINT Size;
    UINT MultiSampleType;
    UINT Width;
    UINT Height;
};

struct LockedRect {  // D3DLOCKED_RECT
    INT Pitch;
    void* Bits;
};

using SetCursorPropertiesFn = HRESULT(WINAPI*)(void* device, UINT hotX, UINT hotY, void* surface);
using SetCursorPositionFn = void(WINAPI*)(void* device, UINT x, UINT y, DWORD flags);
using DeviceShowCursorFn = BOOL(WINAPI*)(void* device, BOOL show);
using GetDescFn = HRESULT(WINAPI*)(void* surface, SurfaceDesc* desc);
using LockRectFn = HRESULT(WINAPI*)(void* surface, LockedRect* locked, const RECT* rect, DWORD flags);
using UnlockRectFn = HRESULT(WINAPI*)(void* surface);
using ShowCursorFn = int(WINAPI*)(BOOL show);
using SetCursorFn = HCURSOR(WINAPI*)(HCURSOR cursor);

// The originals of the hooked cursor functions: three device methods, then
// the user32 imports.
SetCursorPropertiesFn g_setCursorProperties = nullptr;
SetCursorPositionFn g_setCursorPosition = nullptr;
DeviceShowCursorFn g_deviceShowCursor = nullptr;
ShowCursorFn g_showCursor = nullptr;
SetCursorFn g_setCursor = nullptr;

bool g_ownCursor = false;        // the SDK draws the cursor (borderless window)
double g_cursorScale = 0;        // [Display] CursorScale; 0 = from the screen height
HCURSOR g_cursor = nullptr;      // the game's image as a Windows cursor
bool g_cursorVisible = false;    // as the game last asked through the device
uint32_t g_cursorImageHash = 0;  // hash of the image g_cursor was built from

// [Display] FrameStats also counts the calls, to see how the game drives the cursor.
struct CursorCalls {
    int properties = 0;
    int position = 0;
    int deviceShow = 0;
    int deviceHide = 0;
    int showCursor = 0;
    int hideCursor = 0;
    int setCursor = 0;
};

CursorCalls g_cursorCalls;

void LogCursorCalls() {
    const CursorCalls& calls = g_cursorCalls;
    T3_LOG(
        "display: cursor calls: device properties %d, position %d, show %d, hide %d; user32 ShowCursor "
        "%d/%d (show/hide), SetCursor %d",
        calls.properties, calls.position, calls.deviceShow, calls.deviceHide, calls.showCursor, calls.hideCursor,
        calls.setCursor);
    g_cursorCalls = CursorCalls{};
}

// An FNV-1a style hash of the cursor image and its hotspot, to tell whether
// the game set a new image.
uint32_t HashImage(const std::vector<uint32_t>& pixels, UINT hotX, UINT hotY) {
    uint32_t hash = 2166136261u ^ hotX ^ (hotY << 16);

    // Mix every pixel into the hash.
    for (uint32_t pixel : pixels) {
        hash = (hash ^ pixel) * 16777619u;
    }

    return hash;
}

// One channel of a bilinear sample at (x, y) in a width x height ARGB image.
double Sample(const std::vector<uint32_t>& image, UINT width, UINT height, double x, double y, int shift) {
    const double fx = std::clamp(x, 0.0, double(width - 1));
    const double fy = std::clamp(y, 0.0, double(height - 1));
    const UINT x0 = UINT(fx);
    const UINT y0 = UINT(fy);
    const UINT x1 = std::min(x0 + 1, width - 1);
    const UINT y1 = std::min(y0 + 1, height - 1);
    const double tx = fx - x0;
    const double ty = fy - y0;

    auto channel = [&](UINT px, UINT py) {
        return double((image[py * width + px] >> shift) & 0xFF);
    };
    const double top = channel(x0, y0) * (1 - tx) + channel(x1, y0) * tx;
    const double bottom = channel(x0, y1) * (1 - tx) + channel(x1, y1) * tx;
    return top * (1 - ty) + bottom * ty;
}

// Scales a width x height ARGB image by `scale` into `out`, a side x side
// image, sampling each pixel at the source point under its center.
void ScaleImage(const std::vector<uint32_t>& image, UINT width, UINT height, double scale, UINT side, uint32_t* out) {
    // Scale the image row by row.
    for (UINT y = 0; y < side; ++y) {
        // Scale each pixel of the row.
        for (UINT x = 0; x < side; ++x) {
            const double sourceX = (x + 0.5) / scale - 0.5;
            const double sourceY = (y + 0.5) / scale - 0.5;

            uint32_t pixel = 0;

            // Sample the four channels.
            for (int shift : {0, 8, 16, 24}) {
                pixel |= uint32_t(Sample(image, width, height, sourceX, sourceY, shift) + 0.5) << shift;
            }

            out[y * side + x] = pixel;
        }
    }
}

// A Windows cursor from a width x height ARGB image, scaled by `scale`.
// Returns null when the bitmap cannot be created.
HCURSOR MakeCursor(const std::vector<uint32_t>& image, UINT width, UINT height, UINT hotX, UINT hotY, double scale) {
    const UINT side = std::min<UINT>(kMaxCursorSide, UINT(std::max(width, height) * scale + 0.5));

    BITMAPV5HEADER header{};
    header.bV5Size = sizeof(header);
    header.bV5Width = LONG(side);
    header.bV5Height = -LONG(side);  // top-down
    header.bV5Planes = 1;
    header.bV5BitCount = 32;
    header.bV5Compression = BI_BITFIELDS;
    header.bV5RedMask = 0x00FF0000;
    header.bV5GreenMask = 0x0000FF00;
    header.bV5BlueMask = 0x000000FF;
    header.bV5AlphaMask = 0xFF000000;

    void* bits = nullptr;
    HDC screen = GetDC(nullptr);
    HBITMAP color = CreateDIBSection(screen, reinterpret_cast<BITMAPINFO*>(&header), DIB_RGB_COLORS, &bits, nullptr, 0);
    ReleaseDC(nullptr, screen);

    // Without a bitmap there is no cursor.
    if (!color) {
        return nullptr;
    }

    ScaleImage(image, width, height, scale, side, static_cast<uint32_t*>(bits));

    HBITMAP mask = CreateBitmap(LONG(side), LONG(side), 1, 1, nullptr);
    ICONINFO info{};
    info.fIcon = FALSE;
    info.xHotspot = DWORD(hotX * scale);
    info.yHotspot = DWORD(hotY * scale);
    info.hbmMask = mask;
    info.hbmColor = color;
    HCURSOR cursor = reinterpret_cast<HCURSOR>(CreateIconIndirect(&info));
    DeleteObject(mask);
    DeleteObject(color);
    return cursor;
}

// Makes the Windows cursor show the game's image, or nothing while the game
// has its cursor hidden.
void ApplyCursor() {
    g_setCursor(g_cursorVisible ? g_cursor : nullptr);
}

// Copies the pixels of the game's cursor `surface` into `image`. Returns false
// when the surface is not a small A8R8G8B8 image that can be read.
bool ReadCursorSurface(void* surface, SurfaceDesc* desc, std::vector<uint32_t>* image) {
    // Reject a surface that cannot be described, is not A8R8G8B8, is empty or is larger than the limit.
    if (FAILED(reinterpret_cast<GetDescFn>(VtableEntry(surface, kSurface8GetDesc))(surface, desc)) ||
        desc->Format != kFormatA8R8G8B8 || !desc->Width || !desc->Height || desc->Width > kMaxGameCursorSide ||
        desc->Height > kMaxGameCursorSide) {
        return false;
    }

    LockedRect locked{};
    auto lockRect = reinterpret_cast<LockRectFn>(VtableEntry(surface, kSurface8LockRect));

    // Reject a surface that cannot be locked.
    if (FAILED(lockRect(surface, &locked, nullptr, kLockReadOnly))) {
        return false;
    }

    image->resize(desc->Width * desc->Height);

    // Copy the image row by row: the pitch may exceed the row length.
    for (UINT y = 0; y < desc->Height; ++y) {
        memcpy(&(*image)[y * desc->Width], static_cast<const uint8_t*>(locked.Bits) + y * locked.Pitch,
               desc->Width * sizeof(uint32_t));
    }

    reinterpret_cast<UnlockRectFn>(VtableEntry(surface, kSurface8UnlockRect))(surface);
    return true;
}

// The scale of the Windows cursor: [Display] CursorScale, or from the height
// of the game's monitor.
double CursorScale() {
    // [Display] CursorScale was set.
    if (g_cursorScale > 0) {
        return g_cursorScale;
    }

    const RECT screen = g_window ? MonitorRect(g_window) : RECT{0, 0, 0, LONG(kCursorDesignHeight)};
    return std::max(1.0, (screen.bottom - screen.top) / kCursorDesignHeight);
}

// Reads the game's cursor image and, when it changed, builds the Windows
// cursor from it. Returns false when the image cannot be read (Direct3D then
// keeps handling the cursor).
bool TakeCursorImage(void* surface, UINT hotX, UINT hotY) {
    SurfaceDesc desc{};
    std::vector<uint32_t> image;

    // Leave the cursor to Direct3D when the image cannot be read.
    if (!ReadCursorSurface(surface, &desc, &image)) {
        return false;
    }

    // The game sets the same image every frame: rebuild only when it changes.
    const uint32_t hash = HashImage(image, hotX, hotY);

    // The same image as the current cursor: nothing to rebuild.
    if (g_cursor && hash == g_cursorImageHash) {
        return true;
    }

    const double scale = CursorScale();
    HCURSOR cursor = MakeCursor(image, desc.Width, desc.Height, hotX, hotY, scale);

    // Leave the cursor to Direct3D when it could not be built.
    if (!cursor) {
        return false;
    }

    HCURSOR old = g_cursor;
    g_cursor = cursor;
    g_cursorImageHash = hash;
    ApplyCursor();

    // Free the previous cursor.
    if (old) {
        DestroyCursor(old);
    }

    T3_LOG("display: cursor %ux%u shown at x%.2f", desc.Width, desc.Height, scale);
    return true;
}

// Detour of IDirect3DDevice8::SetCursorProperties: takes the game's image for
// the SDK's own cursor when it can, otherwise lets Direct3D have it.
HRESULT WINAPI SetCursorPropertiesDetour(void* device, UINT hotX, UINT hotY, void* surface) {
    ++g_cursorCalls.properties;

    // Take the image for the SDK's cursor when it owns it; otherwise Direct3D gets the call.
    if (g_ownCursor && surface && TakeCursorImage(surface, hotX, hotY)) {
        return S_OK;
    }

    return g_setCursorProperties(device, hotX, hotY, surface);
}

void WINAPI SetCursorPositionDetour(void* device, UINT x, UINT y, DWORD flags) {
    ++g_cursorCalls.position;

    // The Windows cursor follows the mouse on its own.
    if (!g_ownCursor || !g_cursor) {
        g_setCursorPosition(device, x, y, flags);
    }
}

// Detour of IDirect3DDevice8::ShowCursor: records whether the game wants its
// cursor shown. Returns the previous state, as the original does.
BOOL WINAPI DeviceShowCursorDetour(void* device, BOOL show) {
    ++(show ? g_cursorCalls.deviceShow : g_cursorCalls.deviceHide);

    // Without the SDK's cursor, Direct3D handles the call.
    if (!g_ownCursor || !g_cursor) {
        return g_deviceShowCursor(device, show);
    }

    const BOOL wasVisible = g_cursorVisible;

    // Change the Windows cursor only when the state changes.
    if (wasVisible != (show != FALSE)) {
        g_cursorVisible = show != FALSE;
        ApplyCursor();
    }

    return wasVisible;
}

// Detour of the user32 ShowCursor import: only counts the calls.
int WINAPI ShowCursorDetour(BOOL show) {
    ++(show ? g_cursorCalls.showCursor : g_cursorCalls.hideCursor);
    return g_showCursor(show);
}

// Detour of the user32 SetCursor import.
HCURSOR WINAPI SetCursorDetour(HCURSOR cursor) {
    ++g_cursorCalls.setCursor;

    // The game hides the Windows cursor every frame, expecting a fullscreen
    // hardware cursor: keep showing ours instead.
    if (g_ownCursor && g_cursor) {
        return g_setCursor(g_cursorVisible ? g_cursor : nullptr);
    }

    return g_setCursor(cursor);
}

// Hooks the function in slot `slot` of `object`'s vtable. A failure leaves
// the function as it is.
void HookVirtual(void* object, int slot, void* detour, void** original) {
    void* target = VtableEntry(object, slot);

    // Enable the hook only when it was created.
    if (MH_CreateHook(target, detour, original) == MH_OK) {
        MH_EnableHook(target);
    }
}

// Hooks the device's cursor methods and the game's user32 cursor imports.
// The SDK owns the cursor only when the SetCursor import was found.
void HookCursor(void* device) {
    HookVirtual(device, kDevice8SetCursorProperties, reinterpret_cast<void*>(&SetCursorPropertiesDetour),
                reinterpret_cast<void**>(&g_setCursorProperties));
    HookVirtual(device, kDevice8SetCursorPosition, reinterpret_cast<void*>(&SetCursorPositionDetour),
                reinterpret_cast<void**>(&g_setCursorPosition));
    HookVirtual(device, kDevice8ShowCursor, reinterpret_cast<void*>(&DeviceShowCursorDetour),
                reinterpret_cast<void**>(&g_deviceShowCursor));

    HMODULE exe = GetModuleHandleW(nullptr);
    g_showCursor = reinterpret_cast<ShowCursorFn>(
        PatchImport(exe, "USER32.dll", "ShowCursor", reinterpret_cast<void*>(&ShowCursorDetour)));
    g_setCursor = reinterpret_cast<SetCursorFn>(
        PatchImport(exe, "USER32.dll", "SetCursor", reinterpret_cast<void*>(&SetCursorDetour)));
    g_ownCursor = g_setCursor != nullptr;
}

// ---- device creation ----------------------------------------------------------------

// Reads the desktop's display format, so a windowed back buffer can match it.
void ReadDesktopFormat(void* d3d, UINT adapter) {
    DisplayMode desktop{};
    auto getMode = reinterpret_cast<GetAdapterDisplayModeFn>(VtableEntry(d3d, kD3D8GetAdapterDisplayMode));

    // Remember the format and refresh rate when the adapter answers.
    if (SUCCEEDED(getMode(d3d, adapter, &desktop))) {
        g_desktopFormat = desktop.Format;
        g_desktopRefresh = desktop.RefreshRate;
    }
}

// An exclusive fullscreen device asks for the refresh rate "default" (0), for
// which Direct3D 8 may pick 60 Hz on a faster monitor: ask for the desktop's
// rate instead, which the monitor is known to run.
void UseDesktopRefresh(PresentParameters* params) {
    // Only a fullscreen device that leaves the rate to Direct3D, on an adapter whose rate is known.
    if (!params->Windowed && params->FullScreen_RefreshRateInHz == 0 && g_desktopRefresh) {
        params->FullScreen_RefreshRateInHz = g_desktopRefresh;
    }
}

// Hooks Reset on the freshly created `device`, once per process.
void HookReset(void* device) {
    void* reset = VtableEntry(device, kDevice8Reset);

    // Log once the hook is installed.
    if (HookFunction(reset, reinterpret_cast<void*>(&ResetDetour), reinterpret_cast<void**>(&g_reset))) {
        T3_LOG("display: device Reset hooked");
    }
}

// Detour of IDirect3D8::CreateDevice: turns a fullscreen device into a
// windowed one when Borderless is on, then makes its window borderless and
// hooks what the enabled options need on the new device.
HRESULT WINAPI CreateDeviceDetour(void* d3d, UINT adapter, UINT type, HWND focus, DWORD flags,
                                  PresentParameters* params, void** device) {
    const bool wasFullscreen = !params->Windowed;

    g_d3d = d3d;
    g_adapter = adapter;
    g_deviceType = type;
    ReadDesktopFormat(d3d, adapter);

    // A borderless game needs a windowed device; exclusive fullscreen runs at the desktop's refresh rate.
    if (g_borderless) {
        MakeWindowed(params);
    } else {
        UseDesktopRefresh(params);
    }

    g_window = params->hDeviceWindow ? params->hDeviceWindow : focus;
    HRESULT result = g_createDevice(d3d, adapter, type, focus, flags, params, device);
    T3_LOG("display: CreateDevice %ux%u %s%s, format %u, %u Hz, present interval %u -> 0x%08lX",
           params->BackBufferWidth, params->BackBufferHeight,
           !wasFullscreen ? "windowed"
           : g_borderless ? "fullscreen made borderless"
                          : "fullscreen",
           VSyncNote(params), params->BackBufferFormat,
           params->Windowed ? g_desktopRefresh : params->FullScreen_RefreshRateInHz,
           params->FullScreen_PresentationInterval, result);

    // Stop here when the device could not be created.
    if (FAILED(result)) {
        return result;
    }

    // Hook Reset once: borderless keeps its window through resets, exclusive fullscreen its refresh rate.
    if (!g_reset) {
        HookReset(*device);
    }

    // Borderless setup of the new device.
    if (g_borderless) {
        MakeBorderless(g_window);
        BringToFront(g_window);

        // Hook the cursor once.
        if (!g_setCursor) {
            HookCursor(*device);
        }
    }

    // Hook Present once when the frame limit or the statistics are on.
    if ((g_frameTicks || g_frameStats) && !g_present) {
        HookPresent(*device);
    }

    return result;
}

// Detour of the Direct3DCreate8 import: hooks CreateDevice on the first
// Direct3D 8 object the game creates.
void* WINAPI Direct3DCreate8Detour(UINT sdkVersion) {
    void* d3d = g_direct3DCreate8(sdkVersion);

    // Nothing to hook when creation failed or CreateDevice is hooked already.
    if (!d3d || g_createDevice) {
        return d3d;
    }

    void* createDevice = VtableEntry(d3d, kD3D8CreateDevice);
    MH_STATUS status = MH_CreateHook(createDevice, reinterpret_cast<void*>(&CreateDeviceDetour),
                                     reinterpret_cast<void**>(&g_createDevice));

    // Enable the hook only when it was created.
    if (status == MH_OK) {
        status = MH_EnableHook(createDevice);
    }

    T3_LOG("display: CreateDevice hook %s", status == MH_OK ? "installed" : MH_StatusToString(status));
    return d3d;
}

// ---- running in the background ------------------------------------------------------
// On WM_ACTIVATEAPP(FALSE) the viewport's window procedure releases the mouse
// and DirectInput, then pauses the game (TimeManager::SetPaused, after saving
// the pause state it had) and clears the app-active flag, which makes the main
// loop wait in GetMessage until the game is active again. A borderless game
// can keep running instead: the releases stay, the pause is undone. On focus
// the handler then finds the game active and has nothing to restore.

// UWindowsViewport::ViewportWndProc(msg, wParam, lParam), __thiscall.
constexpr uintptr_t kViewportWndProc = 0x10C8B820;

// BYTE GIsAppActive: 0 while the game is in the background.
constexpr uintptr_t kAppActive = 0x10F01150;

// BYTE: the pause state saved on focus loss.
constexpr uintptr_t kPausedBeforeBackground = 0x10FF71BC;

// TimeManager* TimeManager::Instance(), __cdecl.
constexpr uintptr_t kTimeManagerInstance = 0x10D3EBE0;

// void TimeManager::SetPaused(bool), __thiscall.
constexpr uintptr_t kTimeManagerSetPaused = 0x10D3ED00;

using ViewportWndProcFn = LRESULT(__fastcall*)(void* viewport, void* edx, UINT message, WPARAM wParam, LPARAM lParam);
using TimeManagerInstanceFn = void*(__cdecl*)();
using SetPausedFn = void(__fastcall*)(void* timeManager, void* edx, bool paused);

ViewportWndProcFn g_viewportWndProc = nullptr;

// Set when a focus loss was undone to keep the game running, until the focus comes back.
bool g_keptRunning = false;

// Detour of the viewport's window procedure: after a focus loss, marks the
// game active again and restores the pause state the handler saved.
LRESULT __fastcall ViewportWndProcDetour(void* viewport, void* edx, UINT message, WPARAM wParam, LPARAM lParam) {
    auto active = reinterpret_cast<volatile uint8_t*>(kAppActive);
    const bool losingFocus = message == WM_ACTIVATEAPP && !wParam && *active;

    // The handler re-acquires the mouse and keyboard (DirectInput, released on focus loss) only when the game is
    // marked inactive, which it no longer is after a kept-running focus loss: mark it so again first.
    if (message == WM_ACTIVATEAPP && wParam && g_keptRunning) {
        *active = 0;
        g_keptRunning = false;
        T3_LOG("display: focus back; the game takes the mouse and keyboard again");
    }

    LRESULT result = g_viewportWndProc(viewport, edx, message, wParam, lParam);

    // The handler paused the game and marked it inactive: undo both.
    if (losingFocus && !*active) {
        *active = 1;
        g_keptRunning = true;
        void* timeManager = reinterpret_cast<TimeManagerInstanceFn>(kTimeManagerInstance)();
        const bool wasPaused = *reinterpret_cast<const uint8_t*>(kPausedBeforeBackground) != 0;
        reinterpret_cast<SetPausedFn>(kTimeManagerSetPaused)(timeManager, nullptr, wasPaused);
        T3_LOG("display: focus lost; the game keeps running");
    }

    return result;
}

// ---- widescreen UI ----------------------------------------------------------------
// The window manager reads [WindowManager] AssumedUIScreenWidth/Height (640x480)
// once at start-up and scales that layout to the screen, so on a wide screen
// everything is stretched sideways. Answering 480 x aspect for the width keeps
// the proportions; placement anchors (LEFT/CENTER/RIGHT) then use the full width.

// bool Config::GetFloat(section, key, float*, file), __thiscall.
constexpr uintptr_t kConfigGetFloat = 0x10910B60;

constexpr float kDesignedUIWidth = 640.0f;  // the layout width the menus were designed for

using GetFloatFn = int(__fastcall*)(void* self, void* edx, const char* section, const char* key, float* value,
                                    const char* file);

GetFloatFn g_getFloat = nullptr;
float g_uiWidth = 0;  // the layout width the game is told: 480 x the monitor's aspect ratio

// The key-mapping table (Options > Inputs) is placed by ratios of the screen
// width ([KeyboardLayoutWindow] TablePosRatio_X, TableWidthRatio), measured
// from its window, which already sits in the centered menu frame. On a wide
// layout the ratios stretch the table past the frame's scroll bar, so they
// are scaled back to the 640-wide design. Its column ratios are relative to
// the table: unchanged.
void ConvertKeyMappingRatio(const char* key, float* value) {
    // Only the table's position and width ratios are rescaled.
    if (_stricmp(key, "TablePosRatio_X") == 0 || _stricmp(key, "TableWidthRatio") == 0) {
        *value = *value * kDesignedUIWidth / g_uiWidth;
    }
}

// Detour of Config::GetFloat: answers the widened layout width, and rescales
// the key-mapping table's ratios. Returns what the original returns.
int __fastcall GetFloatDetour(void* self, void* edx, const char* section, const char* key, float* value,
                              const char* file) {
    int found = g_getFloat(self, edx, section, key, value, file);

    // Pass through when the lookup failed or an argument is missing.
    if (!found || !section || !key || !value) {
        return found;
    }

    // Replace the layout width, or rescale the key-mapping table's ratios.
    if (_stricmp(section, "WindowManager") == 0 && _stricmp(key, "AssumedUIScreenWidth") == 0) {
        T3_LOG("display: UI layout width %.0f -> %.0f", *value, g_uiWidth);
        *value = g_uiWidth;
    } else if (_stricmp(section, "KeyboardLayoutWindow") == 0) {
        ConvertKeyMappingRatio(key, value);
    }

    return found;
}

// The widened layout keeps proportions, but menus were designed for 640 wide:
// whatever they position from the left edge (LEFT and absolute placement, and
// full-width windows with an x offset, like the main menu buttons) drifts left
// of center, and RIGHT anchors drift to the screen edge. Children of a
// full-width window inside a modal window (every menu, popup and briefing
// screen) are therefore moved into a centered 640-wide frame. The in-game HUD
// is not modal and keeps its anchors at the screen edges.

// WindowManager* GWindowManager (docs/engine.md, "UI windows").
constexpr uintptr_t kWindowManager = 0x10F35DC4;

// FVector* UIWindow::PlacedPosition(FVector*), __thiscall, vtable +0x18.
constexpr uintptr_t kWindowPlacedPosition = 0x10A52530;

// Offsets in WindowManager.
constexpr uint32_t kWindowManagerUIWidth = 0xCC;         // float: layout width (AssumedUIScreenWidth)
constexpr uint32_t kWindowManagerTopLeftOrigin = 0x1E4;  // int: 1 = positions measured from the parent's top-left

// Offsets in UIWindow.
constexpr uint32_t kWindowPosX = 0x1C;        // float: Pos_X
constexpr uint32_t kWindowFlags = 0xE8;       // 0x800 ListenForMouseClicks, 0x1000 IsModal
constexpr uint32_t kWindowPlacementX = 0xD0;  // int: see the placement values below

// UIWindow vtable slots (byte offset / 4).
constexpr uint32_t kWindowGetSizeSlot = 0x84 / 4;    // const FVector* UIWindow::GetSize()
constexpr uint32_t kWindowGetParentSlot = 0xA4 / 4;  // UIWindow* UIWindow::GetParent()

constexpr uint32_t kWindowFlagModal = 0x1000;

// Values of the window placement field.
constexpr int kPlacementAbsolute = 0;
constexpr int kPlacementCenter = 1;
constexpr int kPlacementLeft = 4;
constexpr int kPlacementRight = 5;

constexpr int kMaxTracedWindows = 1024;
constexpr int kMaxParentDepth = 16;  // how far up the parent chain IsMenuFrame looks for a modal window

using PlacedPositionFn = float*(__fastcall*)(void* window, void* edx, float* position);
using GetSizeFn = const float*(__fastcall*)(void* window, void* edx);
using GetParentFn = void*(__fastcall*)(void* window, void* edx);

PlacedPositionFn g_placedPosition = nullptr;
bool g_traceLayout = false;  // [Display] UILayoutTrace

// The function in vtable slot `slot` of `object`, as a Fn.
template <class Fn>
Fn Virtual(void* object, uint32_t slot) {
    return reinterpret_cast<Fn>((*reinterpret_cast<void***>(object))[slot]);
}

// The T at byte offset `offset` in `object`.
template <class T>
T Field(const void* object, uint32_t offset) {
    return *reinterpret_cast<const T*>(static_cast<const uint8_t*>(object) + offset);
}

// The width of a UI window.
float Width(void* window) {
    return Virtual<GetSizeFn>(window, kWindowGetSizeSlot)(window, nullptr)[0];
}

// The parent of a UI window; null for a root window.
void* Parent(void* window) {
    return Virtual<GetParentFn>(window, kWindowGetParentSlot)(window, nullptr);
}

bool FullWidth(void* window, float uiWidth) {
    return std::fabs(Width(window) - uiWidth) < 0.5f;
}

// A window spanning the whole layout inside a modal window: the area a menu's
// contents were laid out in, at 640 wide.
bool IsMenuFrame(void* window, float uiWidth) {
    // Only a full-width window at the left edge can be a frame.
    if (!FullWidth(window, uiWidth) || Field<float>(window, kWindowPosX) != 0.0f) {
        return false;
    }

    // Walk up the parents looking for a modal window.
    for (int depth = 0; window && depth < kMaxParentDepth; ++depth, window = Parent(window)) {
        // A modal window in the chain makes it a menu frame.
        if (Field<uint32_t>(window, kWindowFlags) & kWindowFlagModal) {
            return true;
        }
    }

    return false;
}

// How far a child of a menu frame moves to land where it would in a centered
// 640-wide frame.
float FrameShift(void* window, float uiWidth) {
    const float margin = (uiWidth - kDesignedUIWidth) * 0.5f;
    const bool fullWidth = FullWidth(window, uiWidth);
    const float posX = Field<float>(window, kWindowPosX);
    const int placement = Field<int>(window, kWindowPlacementX);

    // A background or a nested frame: keeps covering the screen.
    if (fullWidth && posX == 0.0f) {
        return 0;
    }

    // Flush against the left or right edge (Pos_X 0), like the main menu's
    // version line: anchored to the screen by design, so it stays there.
    if ((placement == kPlacementLeft || placement == kPlacementRight) && posX == 0.0f) {
        return 0;
    }

    // Shift according to the window's placement anchor.
    switch (placement) {
        case kPlacementAbsolute:
        case kPlacementLeft:
            return margin;
        case kPlacementCenter:
            return fullWidth ? margin : 0;  // centered windows already are
        case kPlacementRight:
            return fullWidth ? margin : -margin;
        default:
            return 0;
    }
}

// [Display] UILayoutTrace: logs the first placement of each window, to map out
// a screen's window tree.
void TracePlacement(void* window, void* parent, const float* position, float shift) {
    static void* traced[kMaxTracedWindows];
    static int count = 0;

    // Log each window only once.
    for (int i = 0; i < count; ++i) {
        // Skip a window that was traced already.
        if (traced[i] == window) {
            return;
        }
    }

    // The table is full: stop tracing new windows.
    if (count == kMaxTracedWindows) {
        return;
    }

    traced[count++] = window;

    const float* size = Virtual<GetSizeFn>(window, kWindowGetSizeSlot)(window, nullptr);
    T3_LOG(
        "ui: window %p (vtable %08X) parent %p placement %d/%d pos %.1f,%.1f size %.1f,%.1f flags %X -> %.1f,%.1f "
        "(shifted %+.1f)",
        window, Field<unsigned>(window, 0), parent, Field<int>(window, kWindowPlacementX),
        Field<int>(window, kWindowPlacementX + 4), Field<float>(window, kWindowPosX),
        Field<float>(window, kWindowPosX + 4), size[0], size[1], Field<unsigned>(window, kWindowFlags), position[0],
        position[1], shift);
}

// Detour of UIWindow::PlacedPosition: moves the children of a menu frame into
// the centered 640-wide frame. Returns what the original returns (`position`):
// callers use the result.
float* __fastcall PlacedPositionDetour(void* window, void* edx, float* position) {
    float* result = g_placedPosition(window, edx, position);
    auto manager = *reinterpret_cast<const uint8_t**>(kWindowManager);

    // Nothing to shift without a window manager or in a centre-origin layout.
    if (!manager || !Field<int>(manager, kWindowManagerTopLeftOrigin)) {
        return result;  // centre-origin layout: not used by the PC menus, left alone
    }

    const float uiWidth = Field<float>(manager, kWindowManagerUIWidth);
    void* parent = Parent(window);
    float shift = 0;

    // Shift the children of a menu frame, on a layout wider than the design.
    if (uiWidth > kDesignedUIWidth && parent && IsMenuFrame(parent, uiWidth)) {
        shift = FrameShift(window, uiWidth);
        position[0] += shift;
    }

    // Log the placement when tracing is on.
    if (g_traceLayout) {
        TracePlacement(window, parent, position, shift);
    }

    return result;
}

// Hooks the game function at `target` and enables the hook. Logs a failure,
// naming `what`. Returns true on success.
bool Hook(uintptr_t target, void* detour, void** original, const char* what) {
    MH_STATUS status = MH_CreateHook(reinterpret_cast<void*>(target), detour, original);

    // Enable the hook only when it was created.
    if (status == MH_OK) {
        status = MH_EnableHook(reinterpret_cast<void*>(target));
    }

    // Log a failure.
    if (status != MH_OK) {
        T3_LOG("display: %s hook failed (%s)", what, MH_StatusToString(status));
    }

    return status == MH_OK;
}

// Works out the layout width from the monitor's aspect ratio and hooks the
// config lookup that the window manager reads it through.
void InstallWidescreenUI() {
    DEVMODEW mode{};
    mode.dmSize = sizeof(mode);
    EnumDisplaySettingsW(nullptr, ENUM_CURRENT_SETTINGS, &mode);

    // Multiples of 4: the community fix found 852 (not 853) stable for 16:9.
    g_uiWidth = float(uint32_t(480.0 * mode.dmPelsWidth / mode.dmPelsHeight) / 4 * 4);
    Hook(kConfigGetFloat, reinterpret_cast<void*>(&GetFloatDetour), reinterpret_cast<void**>(&g_getFloat),
         "widescreen UI width");
}

// ---- installing ---------------------------------------------------------------------

// Sets up the frame limiter and statistics from the options.
void ConfigureFramePacing(const Options& options) {
    QueryPerformanceFrequency(&g_ticksPerSecond);
    g_frameStats = options.frameStats;

    // A frame limit needs a timer.
    if (options.maxFps > 0) {
        g_frameTicks = g_ticksPerSecond.QuadPart / options.maxFps;
        g_frameTimer =
            CreateWaitableTimerExW(nullptr, nullptr, CREATE_WAITABLE_TIMER_HIGH_RESOLUTION, TIMER_ALL_ACCESS);
    }
}

// Hooks the Direct3DCreate8 import, which the borderless window, the
// fullscreen refresh rate, the frame limit and the statistics all hang off.
// Without the import Borderless is switched off.
void HookDirect3D(const Options& options, HMODULE exe) {
    g_borderless = options.borderless;
    g_direct3DCreate8 = reinterpret_cast<Direct3DCreate8Fn>(
        PatchImport(exe, "d3d8.dll", "Direct3DCreate8", reinterpret_cast<void*>(&Direct3DCreate8Detour)));

    // Without the import there is nothing to hook: switch Borderless off.
    if (!g_direct3DCreate8) {
        T3_LOG("display: borderless, frame limit and statistics unavailable (no Direct3DCreate8 import)");
        g_borderless = false;
    }
}

// The level-change curtain: the game restarts for every level change and
// every loaded save, which in a borderless window shows the desktop and in
// exclusive fullscreen a mode switch and a window that does not answer until
// the new game has its device. The curtain covers the monitor meanwhile.
void HookCurtain(HMODULE exe) {
    g_shellExecuteExA = reinterpret_cast<ShellExecuteExAFn>(
        PatchImport(exe, "SHELL32.dll", "ShellExecuteExA", reinterpret_cast<void*>(&ShellExecuteExADetour)));
    Hook(kLoadingScreenBegin, reinterpret_cast<void*>(&LoadingScreenBeginDetour),
         reinterpret_cast<void**>(&g_loadingScreenBegin), "level-change curtain");
}

// The hooks that only make sense with a borderless window: running in the
// background.
void HookBorderlessExtras(const Options& options) {
    // Only a borderless game can keep running: an exclusive fullscreen
    // device is lost as soon as another window takes the focus.
    if (!options.pauseInBackground) {
        Hook(kViewportWndProc, reinterpret_cast<void*>(&ViewportWndProcDetour),
             reinterpret_cast<void**>(&g_viewportWndProc), "running in the background");
    }
}

// Logs which display features ended up on.
void LogSummary(const Options& options) {
    T3_LOG("display: native resolutions %s, borderless %s, widescreen UI %s (width %.0f), %s in the background",
           options.nativeResolutions ? "on" : "off", g_borderless ? "on" : "off", options.widescreenUI ? "on" : "off",
           g_uiWidth, g_viewportWndProc ? "keeps running" : "pauses");

    // Describe the frame limit when there is one.
    if (g_frameTicks) {
        T3_LOG("display: smooth frames %s, at most %d fps%s", options.smoothFrames ? "on" : "off", options.maxFps,
               g_frameTimer ? "" : " (no high-resolution timer: frames wait by spinning)");
    } else {
        T3_LOG("display: smooth frames %s, no frame limit", options.smoothFrames ? "on" : "off");
    }
}

}  // namespace

// ---- entry point ----------------------------------------------------------------------

void Install(const Options& options) {
    // Rewrite the resolution table.
    if (options.nativeResolutions) {
        PatchResolutionTable();
    }

    // Widen the UI layout width.
    if (options.widescreenUI) {
        InstallWidescreenUI();
    }

    // Hook UI placement for the widescreen shift or for the trace.
    if (options.widescreenUI || options.uiLayoutTrace) {
        g_traceLayout = options.uiLayoutTrace;
        Hook(kWindowPlacedPosition, reinterpret_cast<void*>(&PlacedPositionDetour),
             reinterpret_cast<void**>(&g_placedPosition), "UI placement");
    }

    // Lower the engine's minimum world step.
    if (options.smoothFrames) {
        LowerMinimumStep();
    }

    ConfigureFramePacing(options);
    g_cursorScale = options.cursorScale;

    // The device hooks: borderless, and the frame limit and statistics.
    HMODULE exe = GetModuleHandleW(nullptr);
    HookDirect3D(options, exe);

    HookCurtain(exe);

    // The hooks that only a borderless window needs.
    if (g_borderless) {
        HookBorderlessExtras(options);
    }

    LogSummary(options);
}

}  // namespace t3sdk::display
