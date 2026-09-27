// Two independent display features, each behind its own T3SDK.ini option
// (see display.hpp): rewriting the resolution table, and running the
// Direct3D 8 device windowed and borderless.
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
// aspect ratio, topped up with classic 4:3 modes when there are too few.
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
        if (smaller.size() < kResolutionCount - 1 && classic.first < native.first) {
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

HRESULT WINAPI ResetDetour(void* device, PresentParameters* params) {
    // On exit the engine "leaves fullscreen" with a Reset. A borderless device
    // has nothing to leave, and a Reset that fails there (device lost) makes the
    // engine wait forever for the device to come back.
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

}  // namespace

void Install(const Options& options) {
    if (options.nativeResolutions) {
        PatchResolutionTable();
    }
    if (options.borderless) {
        g_direct3DCreate8 = reinterpret_cast<Direct3DCreate8Fn>(PatchImport(
            GetModuleHandleW(nullptr), "d3d8.dll", "Direct3DCreate8", reinterpret_cast<void*>(&Direct3DCreate8Detour)));
        if (!g_direct3DCreate8) {
            T3_LOG("display: borderless unavailable (no Direct3DCreate8 import)");
        }
    }
    T3_LOG("display: native resolutions %s, borderless %s", options.nativeResolutions ? "on" : "off",
           options.borderless && g_direct3DCreate8 ? "on" : "off");
}

}  // namespace t3sdk::display
