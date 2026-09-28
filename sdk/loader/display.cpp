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
constexpr uintptr_t kResolutionWidths = 0x10E6EDC4;   // 640, 800, 1024, 1280, 1600
constexpr uintptr_t kResolutionHeights = 0x10E6EDD8;  // 480, 600, 768, 1024, 1200
constexpr int kResolutionCount = 5;

using Mode = std::pair<uint32_t, uint32_t>;  // width, height

std::set<Mode> MonitorModes(Mode* native) {
    std::set<Mode> modes;
    DEVMODEW mode{};
    mode.dmSize = sizeof(mode);
    for (DWORD i = 0; EnumDisplaySettingsW(nullptr, i, &mode); ++i) {
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
    std::vector<Mode> smaller;
    for (const Mode& m : modes) {
        bool sameAspect = std::fabs(double(m.first) / m.second - aspect) < 0.01;
        if (sameAspect && m.first < native.first && m.second < native.second) {
            smaller.push_back(m);
        }
    }
    std::sort(smaller.begin(), smaller.end(), [](const Mode& a, const Mode& b) {
        return uint64_t(a.first) * a.second > uint64_t(b.first) * b.second;
    });
    smaller.resize(std::min<size_t>(smaller.size(), kResolutionCount - 1));
    for (Mode classic : {Mode{1024, 768}, Mode{800, 600}, Mode{640, 480}}) {
        bool listed = std::find(smaller.begin(), smaller.end(), classic) != smaller.end();
        if (smaller.size() < kResolutionCount - 1 && classic.first < native.first && !listed) {
            smaller.push_back(classic);
        }
    }
    std::sort(smaller.begin(), smaller.end(), [](const Mode& a, const Mode& b) {
        return uint64_t(a.first) * a.second < uint64_t(b.first) * b.second;
    });
    smaller.push_back(native);
    while (smaller.size() < kResolutionCount) {  // tiny desktops: repeat native
        smaller.push_back(native);
    }
    return smaller;
}

void PatchResolutionTable() {
    std::vector<Mode> table = ChooseResolutions();
    auto widths = reinterpret_cast<uint32_t*>(kResolutionWidths);
    auto heights = reinterpret_cast<uint32_t*>(kResolutionHeights);
    DWORD protect;
    VirtualProtect(widths, 2 * kResolutionCount * sizeof(uint32_t), PAGE_READWRITE, &protect);
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
constexpr int kD3D8CreateDevice = 15;           // IDirect3D8 vtable slot
constexpr int kD3D8GetAdapterDisplayMode = 8;   // IDirect3D8 vtable slot
constexpr int kDevice8Reset = 14;               // IDirect3DDevice8 vtable slot

using Direct3DCreate8Fn = void*(WINAPI*)(UINT);
using CreateDeviceFn = HRESULT(WINAPI*)(void* d3d, UINT adapter, UINT type, HWND focus, DWORD flags,
                                        PresentParameters* params, void** device);
using ResetFn = HRESULT(WINAPI*)(void* device, PresentParameters* params);
using GetAdapterDisplayModeFn = HRESULT(WINAPI*)(void* d3d, UINT adapter, DisplayMode* mode);

Direct3DCreate8Fn g_direct3DCreate8 = nullptr;
CreateDeviceFn g_createDevice = nullptr;
ResetFn g_reset = nullptr;
bool g_borderless = false;
HWND g_window = nullptr;
UINT g_desktopFormat = 0;

void* VtableEntry(void* object, int slot) { return (*reinterpret_cast<void***>(object))[slot]; }

// Presentation parameters for a windowed device of the size the game asked
// for. The game's VSync option asks a fullscreen device to present once per
// refresh (UD3DRenderDevice::SetRes, 0x10C84070); a window gets the same from
// the swap effect, which allows neither multisampling nor extra back buffers.
void MakeWindowed(PresentParameters* params) {
    if (params->Windowed) {
        return;
    }
    const bool vsync = params->FullScreen_PresentationInterval == kPresentIntervalOne && !params->MultiSampleType;
    params->Windowed = TRUE;
    params->SwapEffect = vsync ? kSwapEffectCopyVSync : kSwapEffectDiscard;
    if (vsync) {
        params->BackBufferCount = 1;
    }
    params->FullScreen_RefreshRateInHz = 0;
    params->FullScreen_PresentationInterval = 0;  // D3DPRESENT_INTERVAL_DEFAULT: required when windowed
    if (g_desktopFormat) {
        params->BackBufferFormat = g_desktopFormat;
    }
}

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
    if (!window) {
        return;
    }
    const RECT r = MonitorRect(window);
    SetWindowLongW(window, GWL_STYLE, WS_POPUP | WS_VISIBLE);
    SetWindowLongW(window, GWL_EXSTYLE, GetWindowLongW(window, GWL_EXSTYLE) & ~(WS_EX_TOPMOST | WS_EX_WINDOWEDGE));
    SetWindowPos(window, HWND_NOTOPMOST, r.left, r.top, r.right - r.left, r.bottom - r.top,
                 SWP_FRAMECHANGED | SWP_SHOWWINDOW);
}

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
constexpr char kGameLauncher[] = "Ion Launcher.exe";
// void LoadingScreen::Begin(IDirect3DDevice8* device, const char* map, bool), __cdecl
constexpr uintptr_t kLoadingScreenBegin = 0x109E1FC0;

using ShellExecuteExAFn = BOOL(WINAPI*)(SHELLEXECUTEINFOA* info);
using LoadingScreenBeginFn = void(__cdecl*)(void* device, const char* map, int flag);
ShellExecuteExAFn g_shellExecuteExA = nullptr;
LoadingScreenBeginFn g_loadingScreenBegin = nullptr;

bool OwnsForeground() {
    DWORD pid = 0;
    GetWindowThreadProcessId(GetForegroundWindow(), &pid);
    return pid == GetCurrentProcessId();
}

bool StartsGameLauncher(const SHELLEXECUTEINFOA* info) {
    if (!info || !info->lpFile) {
        return false;
    }
    const char* name = strrchr(info->lpFile, '\\');
    return _stricmp(name ? name + 1 : info->lpFile, kGameLauncher) == 0;
}

BOOL WINAPI ShellExecuteExADetour(SHELLEXECUTEINFOA* info) {
    // Only when the player is in the game: a level change while they work in
    // another program must neither cover a screen nor pull the next game to
    // the front.
    if (StartsGameLauncher(info) && OwnsForeground()) {
        AllowSetForegroundWindow(ASFW_ANY);
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
    if (!window || front == window) {
        return;
    }

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
    if (attached) {
        AttachThreadInput(self, frontThread, FALSE);
    }

    if (GetForegroundWindow() == window) {
        T3_LOG("display: window brought to the front (through the window in front)");
    } else {
        T3_LOG("display: Windows kept another program in front of the game window");
    }
}

// The present parameters the game created its device with. The viewport's
// WM_ACTIVATEAPP handler (call at 0x10C8BF6B) resets the device to them when
// the game loses focus, unless the device is already lost, which an exclusive
// fullscreen device always is by then. The borderless device is not lost, the
// reset fails, and the engine then waits for the device forever: the game
// freezes after alt-tab, a click on another monitor, or closing the window.
constexpr uintptr_t kCreationPresentParams = 0x10F2C86C;

HRESULT WINAPI ResetDetour(void* device, PresentParameters* params) {
    if (reinterpret_cast<uintptr_t>(params) == kCreationPresentParams) {
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
    T3_LOG("display: Reset %ux%u windowed%s -> 0x%08lX", params->BackBufferWidth, params->BackBufferHeight,
           VSyncNote(params), result);
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
constexpr uintptr_t kTimeManagerMinStep = 0x10D3EBA1;  // imm32 of MOV [ESI+4], 0.01f in TimeManager::TimeManager
constexpr uint32_t kEngineMinStep = 0x3C23D70A;        // 0.01f
constexpr float kSmoothMinStep = 0.001f;               // every frame moves the world, up to 1000 fps

void LowerMinimumStep() {
    auto step = reinterpret_cast<uint32_t*>(kTimeManagerMinStep);
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

using PresentFn = HRESULT(WINAPI*)(void* device, const RECT* source, const RECT* dest, HWND window,
                                   const void* dirty);
PresentFn g_present = nullptr;
LARGE_INTEGER g_ticksPerSecond{};
LONGLONG g_frameTicks = 0;      // the frame interval for MaxFPS; 0 = no limit
LONGLONG g_nextFrame = 0;       // when the next frame may be presented
HANDLE g_frameTimer = nullptr;  // high-resolution timer; without one the wait spins
bool g_frameStats = false;
LARGE_INTEGER g_statsStart{};
LONGLONG g_presentTicks = 0;
int g_frames = 0;

void LogCursorCalls();

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
    if (sleep > 0 && g_frameTimer) {
        LARGE_INTEGER due;
        due.QuadPart = -sleep * 10000000 / g_ticksPerSecond.QuadPart;  // relative, in 100 ns units
        if (SetWaitableTimer(g_frameTimer, &due, 0, nullptr, nullptr, FALSE)) {
            WaitForSingleObject(g_frameTimer, INFINITE);
        }
    }
    while (now.QuadPart < g_nextFrame) {
        YieldProcessor();
        QueryPerformanceCounter(&now);
    }
    g_nextFrame += g_frameTicks;
}

void CountFrame(const LARGE_INTEGER& before) {
    LARGE_INTEGER after;
    QueryPerformanceCounter(&after);
    g_presentTicks += after.QuadPart - before.QuadPart;
    ++g_frames;

    const double seconds = double(after.QuadPart - g_statsStart.QuadPart) / double(g_ticksPerSecond.QuadPart);
    if (seconds >= 10.0) {
        const double presentMs = 1000.0 * double(g_presentTicks) / double(g_ticksPerSecond.QuadPart) / g_frames;
        T3_LOG("display: %.1f fps, %.2f ms per frame in Present", g_frames / seconds, presentMs);
        LogCursorCalls();
        g_statsStart = after;
        g_presentTicks = 0;
        g_frames = 0;
    }
}

HRESULT WINAPI PresentDetour(void* device, const RECT* source, const RECT* dest, HWND window, const void* dirty) {
    if (g_frameTicks) {
        WaitForFrameTurn();
    }
    LARGE_INTEGER before;
    QueryPerformanceCounter(&before);
    HRESULT result = g_present(device, source, dest, window, dirty);
    if (g_frameStats) {
        CountFrame(before);
    }
    return result;
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
constexpr int kDevice8SetCursorProperties = 10;  // IDirect3DDevice8 vtable slots
constexpr int kDevice8SetCursorPosition = 11;
constexpr int kDevice8ShowCursor = 12;
constexpr int kSurface8GetDesc = 8;              // IDirect3DSurface8 vtable slots
constexpr int kSurface8LockRect = 9;
constexpr int kSurface8UnlockRect = 10;
constexpr UINT kFormatA8R8G8B8 = 21;
constexpr DWORD kLockReadOnly = 0x10;            // D3DLOCK_READONLY
constexpr UINT kMaxCursorSide = 256;
constexpr double kCursorDesignHeight = 768.0;    // the screen height the cursor looks right on

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

SetCursorPropertiesFn g_setCursorProperties = nullptr;
SetCursorPositionFn g_setCursorPosition = nullptr;
DeviceShowCursorFn g_deviceShowCursor = nullptr;
ShowCursorFn g_showCursor = nullptr;
SetCursorFn g_setCursor = nullptr;

bool g_ownCursor = false;       // the SDK draws the cursor (borderless window)
double g_cursorScale = 0;       // [Display] CursorScale; 0 = from the screen height
HCURSOR g_cursor = nullptr;     // the game's image as a Windows cursor
bool g_cursorVisible = false;   // as the game last asked through the device
uint32_t g_cursorImageHash = 0;

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
    const CursorCalls& c = g_cursorCalls;
    T3_LOG("display: cursor calls: device properties %d, position %d, show %d, hide %d; user32 ShowCursor "
           "%d/%d (show/hide), SetCursor %d",
           c.properties, c.position, c.deviceShow, c.deviceHide, c.showCursor, c.hideCursor, c.setCursor);
    g_cursorCalls = CursorCalls{};
}

uint32_t HashImage(const std::vector<uint32_t>& pixels, UINT hotX, UINT hotY) {
    uint32_t hash = 2166136261u ^ hotX ^ (hotY << 16);
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

    auto channel = [&](UINT px, UINT py) { return double((image[py * width + px] >> shift) & 0xFF); };
    const double top = channel(x0, y0) * (1 - tx) + channel(x1, y0) * tx;
    const double bottom = channel(x0, y1) * (1 - tx) + channel(x1, y1) * tx;
    return top * (1 - ty) + bottom * ty;
}

// A Windows cursor from a width x height ARGB image, scaled by `scale`.
HCURSOR MakeCursor(const std::vector<uint32_t>& image, UINT width, UINT height, UINT hotX, UINT hotY,
                   double scale) {
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
    HBITMAP color = CreateDIBSection(screen, reinterpret_cast<BITMAPINFO*>(&header), DIB_RGB_COLORS, &bits,
                                     nullptr, 0);
    ReleaseDC(nullptr, screen);
    if (!color) {
        return nullptr;
    }

    auto out = static_cast<uint32_t*>(bits);
    for (UINT y = 0; y < side; ++y) {
        for (UINT x = 0; x < side; ++x) {
            // Sample the source at the point under this pixel's center.
            const double sx = (x + 0.5) / scale - 0.5;
            const double sy = (y + 0.5) / scale - 0.5;
            uint32_t pixel = 0;
            for (int shift : {0, 8, 16, 24}) {
                pixel |= uint32_t(Sample(image, width, height, sx, sy, shift) + 0.5) << shift;
            }
            out[y * side + x] = pixel;
        }
    }

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

void ApplyCursor() {
    g_setCursor(g_cursorVisible ? g_cursor : nullptr);
}

// Reads the game's cursor image and, when it changed, builds the Windows
// cursor from it. Returns false when the image cannot be read (Direct3D then
// keeps handling the cursor).
bool TakeCursorImage(void* surface, UINT hotX, UINT hotY) {
    SurfaceDesc desc{};
    if (FAILED(reinterpret_cast<GetDescFn>(VtableEntry(surface, kSurface8GetDesc))(surface, &desc)) ||
        desc.Format != kFormatA8R8G8B8 || !desc.Width || !desc.Height || desc.Width > 64 || desc.Height > 64) {
        return false;
    }

    LockedRect locked{};
    auto lockRect = reinterpret_cast<LockRectFn>(VtableEntry(surface, kSurface8LockRect));
    if (FAILED(lockRect(surface, &locked, nullptr, kLockReadOnly))) {
        return false;
    }
    std::vector<uint32_t> image(desc.Width * desc.Height);
    for (UINT y = 0; y < desc.Height; ++y) {
        memcpy(&image[y * desc.Width], static_cast<const uint8_t*>(locked.Bits) + y * locked.Pitch,
               desc.Width * sizeof(uint32_t));
    }
    reinterpret_cast<UnlockRectFn>(VtableEntry(surface, kSurface8UnlockRect))(surface);

    // The game sets the same image every frame: rebuild only when it changes.
    const uint32_t hash = HashImage(image, hotX, hotY);
    if (g_cursor && hash == g_cursorImageHash) {
        return true;
    }

    double scale = g_cursorScale;
    if (scale <= 0) {
        const RECT screen = g_window ? MonitorRect(g_window) : RECT{0, 0, 0, LONG(kCursorDesignHeight)};
        scale = std::max(1.0, (screen.bottom - screen.top) / kCursorDesignHeight);
    }
    HCURSOR cursor = MakeCursor(image, desc.Width, desc.Height, hotX, hotY, scale);
    if (!cursor) {
        return false;
    }

    HCURSOR old = g_cursor;
    g_cursor = cursor;
    g_cursorImageHash = hash;
    ApplyCursor();
    if (old) {
        DestroyCursor(old);
    }
    T3_LOG("display: cursor %ux%u shown at x%.2f", desc.Width, desc.Height, scale);
    return true;
}

HRESULT WINAPI SetCursorPropertiesDetour(void* device, UINT hotX, UINT hotY, void* surface) {
    ++g_cursorCalls.properties;
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

BOOL WINAPI DeviceShowCursorDetour(void* device, BOOL show) {
    ++(show ? g_cursorCalls.deviceShow : g_cursorCalls.deviceHide);
    if (!g_ownCursor || !g_cursor) {
        return g_deviceShowCursor(device, show);
    }

    const BOOL wasVisible = g_cursorVisible;
    if (wasVisible != (show != FALSE)) {
        g_cursorVisible = show != FALSE;
        ApplyCursor();
    }
    return wasVisible;
}

int WINAPI ShowCursorDetour(BOOL show) {
    ++(show ? g_cursorCalls.showCursor : g_cursorCalls.hideCursor);
    return g_showCursor(show);
}

HCURSOR WINAPI SetCursorDetour(HCURSOR cursor) {
    ++g_cursorCalls.setCursor;

    // The game hides the Windows cursor every frame, expecting a fullscreen
    // hardware cursor: keep showing ours instead.
    if (g_ownCursor && g_cursor) {
        return g_setCursor(g_cursorVisible ? g_cursor : nullptr);
    }
    return g_setCursor(cursor);
}

void HookVirtual(void* object, int slot, void* detour, void** original) {
    void* target = VtableEntry(object, slot);
    if (MH_CreateHook(target, detour, original) == MH_OK) {
        MH_EnableHook(target);
    }
}

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

void HookPresent(void* device) {
    void* present = VtableEntry(device, kDevice8Present);
    if (MH_CreateHook(present, reinterpret_cast<void*>(&PresentDetour), reinterpret_cast<void**>(&g_present)) ==
            MH_OK &&
        MH_EnableHook(present) == MH_OK) {
        QueryPerformanceCounter(&g_statsStart);
        T3_LOG("display: Present hooked (frame limit %s, frame statistics %s)", g_frameTicks ? "on" : "off",
               g_frameStats ? "on" : "off");
    }
}

HRESULT WINAPI CreateDeviceDetour(void* d3d, UINT adapter, UINT type, HWND focus, DWORD flags,
                                  PresentParameters* params, void** device) {
    const bool wasFullscreen = !params->Windowed;
    if (g_borderless) {
        DisplayMode desktop{};
        auto getMode = reinterpret_cast<GetAdapterDisplayModeFn>(VtableEntry(d3d, kD3D8GetAdapterDisplayMode));
        if (SUCCEEDED(getMode(d3d, adapter, &desktop))) {
            g_desktopFormat = desktop.Format;
        }
        MakeWindowed(params);
    }
    g_window = params->hDeviceWindow ? params->hDeviceWindow : focus;
    HRESULT result = g_createDevice(d3d, adapter, type, focus, flags, params, device);
    T3_LOG("display: CreateDevice %ux%u %s%s -> 0x%08lX", params->BackBufferWidth, params->BackBufferHeight,
           !wasFullscreen ? "windowed" : g_borderless ? "fullscreen made borderless" : "fullscreen",
           VSyncNote(params), result);
    if (FAILED(result)) {
        return result;
    }

    if (g_borderless) {
        MakeBorderless(g_window);
        BringToFront(g_window);
        if (!g_reset) {
            void* reset = VtableEntry(*device, kDevice8Reset);
            if (MH_CreateHook(reset, reinterpret_cast<void*>(&ResetDetour), reinterpret_cast<void**>(&g_reset)) ==
                    MH_OK &&
                MH_EnableHook(reset) == MH_OK) {
                T3_LOG("display: device Reset hooked");
            }
        }
        if (!g_setCursor) {
            HookCursor(*device);
        }
    }
    if ((g_frameTicks || g_frameStats) && !g_present) {
        HookPresent(*device);
    }
    return result;
}

// ---- running in the background ------------------------------------------------------
// On WM_ACTIVATEAPP(FALSE) the viewport's window procedure releases the mouse
// and DirectInput, then pauses the game (TimeManager::SetPaused, after saving
// the pause state it had) and clears the app-active flag, which makes the main
// loop wait in GetMessage until the game is active again. A borderless game
// can keep running instead: the releases stay, the pause is undone. On focus
// the handler then finds the game active and has nothing to restore.
constexpr uintptr_t kViewportWndProc = 0x10C8B820;          // UWindowsViewport::ViewportWndProc(msg, wParam, lParam)
constexpr uintptr_t kAppActive = 0x10F01150;                // BYTE GIsAppActive: 0 while the game is in the background
constexpr uintptr_t kPausedBeforeBackground = 0x10FF71BC;   // BYTE: the pause state saved on focus loss
constexpr uintptr_t kTimeManagerInstance = 0x10D3EBE0;      // TimeManager* TimeManager::Instance()
constexpr uintptr_t kTimeManagerSetPaused = 0x10D3ED00;     // void TimeManager::SetPaused(bool), __thiscall

using ViewportWndProcFn = LRESULT(__fastcall*)(void* viewport, void* edx, UINT message, WPARAM wParam,
                                               LPARAM lParam);
using TimeManagerInstanceFn = void*(__cdecl*)();
using SetPausedFn = void(__fastcall*)(void* timeManager, void* edx, bool paused);
ViewportWndProcFn g_viewportWndProc = nullptr;

LRESULT __fastcall ViewportWndProcDetour(void* viewport, void* edx, UINT message, WPARAM wParam, LPARAM lParam) {
    auto active = reinterpret_cast<volatile uint8_t*>(kAppActive);
    const bool losingFocus = message == WM_ACTIVATEAPP && !wParam && *active;

    LRESULT result = g_viewportWndProc(viewport, edx, message, wParam, lParam);

    // The handler paused the game and marked it inactive: undo both.
    if (losingFocus && !*active) {
        *active = 1;
        void* timeManager = reinterpret_cast<TimeManagerInstanceFn>(kTimeManagerInstance)();
        const bool wasPaused = *reinterpret_cast<const uint8_t*>(kPausedBeforeBackground) != 0;
        reinterpret_cast<SetPausedFn>(kTimeManagerSetPaused)(timeManager, nullptr, wasPaused);
        T3_LOG("display: focus lost; the game keeps running");
    }
    return result;
}

void* WINAPI Direct3DCreate8Detour(UINT sdkVersion) {
    void* d3d = g_direct3DCreate8(sdkVersion);
    if (d3d && !g_createDevice) {
        void* createDevice = VtableEntry(d3d, kD3D8CreateDevice);
        MH_STATUS status = MH_CreateHook(createDevice, reinterpret_cast<void*>(&CreateDeviceDetour),
                                         reinterpret_cast<void**>(&g_createDevice));
        if (status == MH_OK) {
            status = MH_EnableHook(createDevice);
        }
        T3_LOG("display: CreateDevice hook %s", status == MH_OK ? "installed" : MH_StatusToString(status));
    }
    return d3d;
}

// ---- widescreen UI ----------------------------------------------------------------
// The window manager reads [WindowManager] AssumedUIScreenWidth/Height (640x480)
// once at start-up and scales that layout to the screen, so on a wide screen
// everything is stretched sideways. Answering 480 x aspect for the width keeps
// the proportions; placement anchors (LEFT/CENTER/RIGHT) then use the full width.
constexpr uintptr_t kConfigGetFloat = 0x10910B60;  // bool Config::GetFloat(section, key, float*, file)
constexpr float kDesignedUIWidth = 640.0f;

using GetFloatFn = int(__fastcall*)(void* self, void* edx, const char* section, const char* key, float* value,
                                    const char* file);
GetFloatFn g_getFloat = nullptr;
float g_uiWidth = 0;

// The key-mapping table (Options > Inputs) is placed by ratios of the screen
// width ([KeyboardLayoutWindow] TablePosRatio_X, TableWidthRatio), measured
// from its window, which already sits in the centered menu frame. On a wide
// layout the ratios stretch the table past the frame's scroll bar, so they
// are scaled back to the 640-wide design. Its column ratios are relative to
// the table: unchanged.
void ConvertKeyMappingRatio(const char* key, float* value) {
    if (_stricmp(key, "TablePosRatio_X") == 0 || _stricmp(key, "TableWidthRatio") == 0) {
        *value = *value * kDesignedUIWidth / g_uiWidth;
    }
}

int __fastcall GetFloatDetour(void* self, void* edx, const char* section, const char* key, float* value,
                              const char* file) {
    int found = g_getFloat(self, edx, section, key, value, file);
    if (!found || !section || !key || !value) {
        return found;
    }

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
constexpr uintptr_t kWindowManager = 0x10F35DC4;         // WindowManager* global
constexpr uint32_t kWindowManagerUIWidth = 0xCC;         // float: layout width (AssumedUIScreenWidth)
constexpr uint32_t kWindowManagerTopLeftOrigin = 0x1E4;  // int: 1 = positions measured from the parent's top-left
constexpr uintptr_t kWindowPlacedPosition = 0x10A52530;  // FVector* UIWindow::PlacedPosition(FVector*), vtable +0x18
constexpr uint32_t kWindowPosX = 0x1C;                   // float: Pos_X
constexpr uint32_t kWindowFlags = 0xE8;                  // 0x800 ListenForMouseClicks, 0x1000 IsModal
constexpr uint32_t kWindowPlacementX = 0xD0;             // int: 0 absolute, 1 CENTER, 4 LEFT, 5 RIGHT
constexpr uint32_t kWindowGetSizeSlot = 0x84 / 4;        // const FVector* UIWindow::GetSize() (vtable)
constexpr uint32_t kWindowGetParentSlot = 0xA4 / 4;      // UIWindow* UIWindow::GetParent() (vtable)
constexpr uint32_t kWindowFlagModal = 0x1000;
constexpr int kPlacementAbsolute = 0;
constexpr int kPlacementCenter = 1;
constexpr int kPlacementLeft = 4;
constexpr int kPlacementRight = 5;

using PlacedPositionFn = float*(__fastcall*)(void* window, void* edx, float* position);
using GetSizeFn = const float*(__fastcall*)(void* window, void* edx);
using GetParentFn = void*(__fastcall*)(void* window, void* edx);
PlacedPositionFn g_placedPosition = nullptr;
bool g_traceLayout = false;

template <class Fn>
Fn Virtual(void* object, uint32_t slot) {
    return reinterpret_cast<Fn>((*reinterpret_cast<void***>(object))[slot]);
}

template <class T>
T Field(const void* object, uint32_t offset) {
    return *reinterpret_cast<const T*>(static_cast<const uint8_t*>(object) + offset);
}

float Width(void* window) { return Virtual<GetSizeFn>(window, kWindowGetSizeSlot)(window, nullptr)[0]; }
void* Parent(void* window) { return Virtual<GetParentFn>(window, kWindowGetParentSlot)(window, nullptr); }

bool FullWidth(void* window, float uiWidth) { return std::fabs(Width(window) - uiWidth) < 0.5f; }

// A window spanning the whole layout inside a modal window: the area a menu's
// contents were laid out in, at 640 wide.
bool IsMenuFrame(void* window, float uiWidth) {
    if (!FullWidth(window, uiWidth) || Field<float>(window, kWindowPosX) != 0.0f) {
        return false;
    }
    for (int depth = 0; window && depth < 16; ++depth, window = Parent(window)) {
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
    static void* traced[1024];
    static int count = 0;
    for (int i = 0; i < count; ++i) {
        if (traced[i] == window) {
            return;
        }
    }
    if (count == 1024) {
        return;
    }
    traced[count++] = window;
    const float* size = Virtual<GetSizeFn>(window, kWindowGetSizeSlot)(window, nullptr);
    T3_LOG("ui: window %p (vtable %08X) parent %p placement %d/%d pos %.1f,%.1f size %.1f,%.1f flags %X -> %.1f,%.1f "
           "(shifted %+.1f)",
           window, Field<unsigned>(window, 0), parent, Field<int>(window, kWindowPlacementX),
           Field<int>(window, kWindowPlacementX + 4), Field<float>(window, kWindowPosX),
           Field<float>(window, kWindowPosX + 4), size[0], size[1], Field<unsigned>(window, kWindowFlags),
           position[0], position[1], shift);
}

// Returns what the original returns (`position`): callers use the result.
float* __fastcall PlacedPositionDetour(void* window, void* edx, float* position) {
    float* result = g_placedPosition(window, edx, position);
    auto manager = *reinterpret_cast<const uint8_t**>(kWindowManager);
    if (!manager || !Field<int>(manager, kWindowManagerTopLeftOrigin)) {
        return result;  // centre-origin layout: not used by the PC menus, left alone
    }
    const float uiWidth = Field<float>(manager, kWindowManagerUIWidth);
    void* parent = Parent(window);
    float shift = 0;
    if (uiWidth > kDesignedUIWidth && parent && IsMenuFrame(parent, uiWidth)) {
        shift = FrameShift(window, uiWidth);
        position[0] += shift;
    }
    if (g_traceLayout) {
        TracePlacement(window, parent, position, shift);
    }
    return result;
}

bool Hook(uintptr_t target, void* detour, void** original, const char* what) {
    MH_STATUS status = MH_CreateHook(reinterpret_cast<void*>(target), detour, original);
    if (status == MH_OK) {
        status = MH_EnableHook(reinterpret_cast<void*>(target));
    }
    if (status != MH_OK) {
        T3_LOG("display: %s hook failed (%s)", what, MH_StatusToString(status));
    }
    return status == MH_OK;
}

void InstallWidescreenUI() {
    DEVMODEW mode{};
    mode.dmSize = sizeof(mode);
    EnumDisplaySettingsW(nullptr, ENUM_CURRENT_SETTINGS, &mode);
    // Multiples of 4: the community fix found 852 (not 853) stable for 16:9.
    g_uiWidth = float(uint32_t(480.0 * mode.dmPelsWidth / mode.dmPelsHeight) / 4 * 4);
    Hook(kConfigGetFloat, reinterpret_cast<void*>(&GetFloatDetour), reinterpret_cast<void**>(&g_getFloat),
         "widescreen UI width");
}

}  // namespace

void Install(const Options& options) {
    if (options.nativeResolutions) {
        PatchResolutionTable();
    }
    if (options.widescreenUI) {
        InstallWidescreenUI();
    }
    if (options.widescreenUI || options.uiLayoutTrace) {
        g_traceLayout = options.uiLayoutTrace;
        Hook(kWindowPlacedPosition, reinterpret_cast<void*>(&PlacedPositionDetour),
             reinterpret_cast<void**>(&g_placedPosition), "UI placement");
    }
    if (options.smoothFrames) {
        LowerMinimumStep();
    }

    QueryPerformanceFrequency(&g_ticksPerSecond);
    g_frameStats = options.frameStats;
    if (options.maxFps > 0) {
        g_frameTicks = g_ticksPerSecond.QuadPart / options.maxFps;
        g_frameTimer =
            CreateWaitableTimerExW(nullptr, nullptr, CREATE_WAITABLE_TIMER_HIGH_RESOLUTION, TIMER_ALL_ACCESS);
    }
    g_cursorScale = options.cursorScale;

    // The device hooks: borderless, and the frame limit and statistics.
    HMODULE exe = GetModuleHandleW(nullptr);
    g_borderless = options.borderless;
    if (options.borderless || g_frameTicks || g_frameStats) {
        g_direct3DCreate8 = reinterpret_cast<Direct3DCreate8Fn>(
            PatchImport(exe, "d3d8.dll", "Direct3DCreate8", reinterpret_cast<void*>(&Direct3DCreate8Detour)));
        if (!g_direct3DCreate8) {
            T3_LOG("display: borderless, frame limit and statistics unavailable (no Direct3DCreate8 import)");
            g_borderless = false;
        }
    }

    if (g_borderless) {
        g_shellExecuteExA = reinterpret_cast<ShellExecuteExAFn>(
            PatchImport(exe, "SHELL32.dll", "ShellExecuteExA", reinterpret_cast<void*>(&ShellExecuteExADetour)));
        Hook(kLoadingScreenBegin, reinterpret_cast<void*>(&LoadingScreenBeginDetour),
             reinterpret_cast<void**>(&g_loadingScreenBegin), "level-change curtain");

        // Only a borderless game can keep running: an exclusive fullscreen
        // device is lost as soon as another window takes the focus.
        if (!options.pauseInBackground) {
            Hook(kViewportWndProc, reinterpret_cast<void*>(&ViewportWndProcDetour),
                 reinterpret_cast<void**>(&g_viewportWndProc), "running in the background");
        }
    }

    T3_LOG("display: native resolutions %s, borderless %s, widescreen UI %s (width %.0f), %s in the background",
           options.nativeResolutions ? "on" : "off", g_borderless ? "on" : "off", options.widescreenUI ? "on" : "off",
           g_uiWidth, g_viewportWndProc ? "keeps running" : "pauses");
    if (g_frameTicks) {
        T3_LOG("display: smooth frames %s, at most %d fps%s", options.smoothFrames ? "on" : "off", options.maxFps,
               g_frameTimer ? "" : " (no high-resolution timer: frames wait by spinning)");
    } else {
        T3_LOG("display: smooth frames %s, no frame limit", options.smoothFrames ? "on" : "off");
    }
}

}  // namespace t3sdk::display
