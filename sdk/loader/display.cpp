// Three independent display features, each behind its own T3SDK.ini option
// (see display.hpp): rewriting the resolution table, running the Direct3D 8
// device windowed and borderless (and keeping it running in the background),
// and rescaling the UI layout for widescreen.
// Facts and evidence for the addresses below are in docs/engine.md.
#include "display.hpp"

#include "engine.hpp"
#include "iat.hpp"
#include "log.hpp"

#include <MinHook.h>
#include <windows.h>

#include <algorithm>
#include <cmath>
#include <cstdint>
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
HWND g_window = nullptr;
UINT g_desktopFormat = 0;

void* VtableEntry(void* object, int slot) { return (*reinterpret_cast<void***>(object))[slot]; }

// Presentation parameters for a windowed device of the size the game asked for.
void MakeWindowed(PresentParameters* params) {
    if (params->Windowed) {
        return;
    }
    params->Windowed = TRUE;
    params->SwapEffect = kSwapEffectDiscard;
    params->FullScreen_RefreshRateInHz = 0;
    params->FullScreen_PresentationInterval = 0;  // D3DPRESENT_INTERVAL_DEFAULT: required when windowed
    if (g_desktopFormat) {
        params->BackBufferFormat = g_desktopFormat;
    }
}

// A popup window covering the monitor it is on; Present scales the back buffer to it.
void MakeBorderless(HWND window) {
    if (!window) {
        return;
    }
    MONITORINFO monitor{};
    monitor.cbSize = sizeof(monitor);
    GetMonitorInfoW(MonitorFromWindow(window, MONITOR_DEFAULTTOPRIMARY), &monitor);
    const RECT& r = monitor.rcMonitor;
    SetWindowLongW(window, GWL_STYLE, WS_POPUP | WS_VISIBLE);
    SetWindowLongW(window, GWL_EXSTYLE, GetWindowLongW(window, GWL_EXSTYLE) & ~(WS_EX_TOPMOST | WS_EX_WINDOWEDGE));
    SetWindowPos(window, HWND_NOTOPMOST, r.left, r.top, r.right - r.left, r.bottom - r.top,
                 SWP_FRAMECHANGED | SWP_SHOWWINDOW);
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
    T3_LOG("display: Reset %ux%u windowed -> 0x%08lX", params->BackBufferWidth, params->BackBufferHeight, result);
    return result;
}

HRESULT WINAPI CreateDeviceDetour(void* d3d, UINT adapter, UINT type, HWND focus, DWORD flags,
                                  PresentParameters* params, void** device) {
    DisplayMode desktop{};
    auto getMode = reinterpret_cast<GetAdapterDisplayModeFn>(VtableEntry(d3d, kD3D8GetAdapterDisplayMode));
    if (SUCCEEDED(getMode(d3d, adapter, &desktop))) {
        g_desktopFormat = desktop.Format;
    }
    bool wasFullscreen = !params->Windowed;
    MakeWindowed(params);
    g_window = params->hDeviceWindow ? params->hDeviceWindow : focus;
    HRESULT result = g_createDevice(d3d, adapter, type, focus, flags, params, device);
    T3_LOG("display: CreateDevice %ux%u %s -> 0x%08lX", params->BackBufferWidth, params->BackBufferHeight,
           wasFullscreen ? "fullscreen made borderless" : "windowed", result);
    if (SUCCEEDED(result)) {
        MakeBorderless(g_window);
        if (!g_reset) {
            void* reset = VtableEntry(*device, kDevice8Reset);
            if (MH_CreateHook(reset, reinterpret_cast<void*>(&ResetDetour), reinterpret_cast<void**>(&g_reset)) ==
                    MH_OK &&
                MH_EnableHook(reset) == MH_OK) {
                T3_LOG("display: device Reset hooked");
            }
        }
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
    if (options.borderless) {
        g_direct3DCreate8 = reinterpret_cast<Direct3DCreate8Fn>(PatchImport(
            GetModuleHandleW(nullptr), "d3d8.dll", "Direct3DCreate8", reinterpret_cast<void*>(&Direct3DCreate8Detour)));
        if (!g_direct3DCreate8) {
            T3_LOG("display: borderless unavailable (no Direct3DCreate8 import)");
        } else if (!options.pauseInBackground) {
            // Only a borderless game can keep running: an exclusive fullscreen
            // device is lost as soon as another window takes the focus.
            Hook(kViewportWndProc, reinterpret_cast<void*>(&ViewportWndProcDetour),
                 reinterpret_cast<void**>(&g_viewportWndProc), "running in the background");
        }
    }
    T3_LOG("display: native resolutions %s, borderless %s, widescreen UI %s (width %.0f), %s in the background",
           options.nativeResolutions ? "on" : "off", options.borderless && g_direct3DCreate8 ? "on" : "off",
           options.widescreenUI ? "on" : "off", g_uiWidth, g_viewportWndProc ? "keeps running" : "pauses");
}

}  // namespace t3sdk::display
