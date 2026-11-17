// The game's brightness in a window. The game turns its Brightness, Contrast
// and Gamma options into a 256-step gamma ramp (UD3DRenderDevice, 0x10C83300)
// and hands it to IDirect3DDevice8::SetGammaRamp, which only exclusive
// fullscreen applies: in a window (Borderless, or the game's own windowed
// mode) Direct3D 8, and DXVK too, keep it and show nothing, so the brightness
// options do nothing. With [Display] WindowedBrightness the SDK keeps the
// ramp the game sets and, before each Present of a windowed device, draws the
// finished frame through it: the frame is copied to a texture and drawn back
// over the back buffer with a ps.1.1 pixel shader that looks each channel up
// in the ramp (texreg2ar/texreg2gb read two lookup textures at the frame's own
// colours). An identity ramp (the default options) draws nothing. Exclusive
// fullscreen keeps Direct3D's own gamma. Evidence: docs/engine.md, "Display".
#include "gamma.hpp"

#include "log.hpp"

#include <MinHook.h>

#include <windows.h>

#include <cstdint>
#include <cstdlib>
#include <cstring>

namespace t3sdk::display::gamma {
namespace {

// ---- Direct3D 8 ---------------------------------------------------------------------
// The loader has no d3d8.h: the slots, constants and structures it uses, as d3d8.h declares them.

// IDirect3DDevice8 vtable slots.
constexpr int kDeviceGetDeviceCaps = 7;
constexpr int kDeviceGetBackBuffer = 16;
constexpr int kDeviceSetGammaRamp = 18;
constexpr int kDeviceCreateTexture = 20;
constexpr int kDeviceCopyRects = 28;
constexpr int kDeviceSetRenderTarget = 31;
constexpr int kDeviceGetRenderTarget = 32;
constexpr int kDeviceGetDepthStencilSurface = 33;
constexpr int kDeviceBeginScene = 34;
constexpr int kDeviceEndScene = 35;
constexpr int kDeviceSetRenderState = 50;
constexpr int kDeviceApplyStateBlock = 54;
constexpr int kDeviceCaptureStateBlock = 55;
constexpr int kDeviceDeleteStateBlock = 56;
constexpr int kDeviceCreateStateBlock = 57;
constexpr int kDeviceSetTexture = 61;
constexpr int kDeviceSetTextureStageState = 63;
constexpr int kDeviceDrawPrimitiveUP = 72;
constexpr int kDeviceSetVertexShader = 76;
constexpr int kDeviceCreatePixelShader = 87;
constexpr int kDeviceSetPixelShader = 88;

// IUnknown, IDirect3DTexture8 and IDirect3DSurface8 vtable slots.
constexpr int kRelease = 2;
constexpr int kTextureGetSurfaceLevel = 15;
constexpr int kTextureLockRect = 16;
constexpr int kTextureUnlockRect = 17;
constexpr int kSurfaceGetDesc = 8;

// Render states (D3DRENDERSTATETYPE).
constexpr DWORD kRsZEnable = 7;
constexpr DWORD kRsFillMode = 8;
constexpr DWORD kRsZWriteEnable = 14;
constexpr DWORD kRsAlphaTestEnable = 15;
constexpr DWORD kRsCullMode = 22;
constexpr DWORD kRsAlphaBlendEnable = 27;
constexpr DWORD kRsFogEnable = 28;
constexpr DWORD kRsSpecularEnable = 29;
constexpr DWORD kRsStencilEnable = 52;
constexpr DWORD kRsWrap0 = 128;
constexpr DWORD kRsColorWriteEnable = 168;

// Texture stage states (D3DTEXTURESTAGESTATETYPE of Direct3D 8, which still holds the sampler states).
constexpr DWORD kTssTexCoordIndex = 11;
constexpr DWORD kTssAddressU = 13;
constexpr DWORD kTssAddressV = 14;
constexpr DWORD kTssMagFilter = 16;
constexpr DWORD kTssMinFilter = 17;
constexpr DWORD kTssMipFilter = 18;
constexpr DWORD kTssTextureTransformFlags = 24;

// Values.
constexpr DWORD kFillSolid = 3;
constexpr DWORD kCullNone = 1;
constexpr DWORD kAddressClamp = 3;
constexpr DWORD kFilterNone = 0;
constexpr DWORD kFilterPoint = 1;
constexpr DWORD kColorWriteAll = 0xF;
constexpr UINT kFormatA8R8G8B8 = 21;
constexpr DWORD kUsageRenderTarget = 1;
constexpr UINT kPoolDefault = 0;
constexpr UINT kPoolManaged = 1;
constexpr UINT kBackBufferMono = 0;
constexpr UINT kStateBlockAll = 1;
constexpr UINT kTriangleStrip = 5;
constexpr DWORD kFvfXyzRhwTex1 = 0x004 | 0x100;

// D3DCAPS8: Caps2 and PixelShaderVersion, and the structure's size.
constexpr size_t kCapsCaps2 = 0x0C;
constexpr size_t kCapsPixelShaderVersion = 0xCC;
constexpr size_t kCapsSize = 0xD4;
constexpr DWORD kCaps2FullscreenGamma = 0x20000;

struct GammaRamp {  // D3DGAMMARAMP
    WORD red[256];
    WORD green[256];
    WORD blue[256];
};

// A ramp as the 8-bit levels the screen shows.
struct Levels {
    BYTE red[256];
    BYTE green[256];
    BYTE blue[256];
};

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
    void* pBits;
};

struct Vertex {  // D3DFVF_XYZRHW | D3DFVF_TEX1
    float x, y, z, rhw, u, v;
};

using SetGammaRampFn = void(WINAPI*)(void* device, DWORD flags, const GammaRamp* ramp);

// The pixel shader, ps.1.1 tokens (a d3d8 runtime takes tokens, not text):
//   tex t0             the frame
//   texreg2ar t1, t0   stage 1 at (alpha, red): the ramp's red for the frame's red
//   texreg2gb t2, t0   stage 2 at (green, blue): the ramp's green and blue
//   add r0, t1, t2     the lookups hold their channels and zero elsewhere
const DWORD kPixelShader[] = {
    0xFFFF0101,                                      // ps.1.1
    0x00000042, 0xB00F0000,                          // tex t0
    0x00000045, 0xB00F0001, 0xB0E40000,              // texreg2ar t1, t0
    0x00000046, 0xB00F0002, 0xB0E40000,              // texreg2gb t2, t0
    0x00000002, 0x800F0000, 0xB0E40001, 0xB0E40002,  // add r0, t1, t2
    0x0000FFFF,                                      // end
};

// ---- state ------------------------------------------------------------------------------
// All of it belongs to the game's render thread, which makes every Direct3D call.

bool g_enabled = false;                    // [Display] WindowedBrightness
SetGammaRampFn g_setGammaRamp = nullptr;   // the original, once hooked
void* g_device = nullptr;                  // the device the objects below belong to
bool g_windowed = false;                   // that device presents to a window
bool g_broken = false;                     // a step failed: the pass stays off (logged once)
Levels g_levels{};                         // the last ramp the game set, as levels
bool g_haveRamp = false;                   // the game set one
bool g_identity = true;                    // that ramp changes nothing
bool g_lutsStale = true;                   // the lookup textures do not hold that ramp yet
void* g_frame = nullptr;                   // texture the frame is copied to (default pool)
UINT g_frameWidth = 0, g_frameHeight = 0;  // its size
UINT g_frameFormat = 0;                    // its format
void* g_lutRed = nullptr;                  // 1x256: red = ramp(v)
void* g_lutGreenBlue = nullptr;            // 256x256: green = ramp(u), blue = ramp(v)
DWORD g_shader = 0;                        // the pixel shader handle
DWORD g_stateBlock = 0;                    // captures the game's state around the pass
bool g_announced = false;                  // the first drawn frame was logged

// ---- helpers ----------------------------------------------------------------------------

// The function in slot `slot` of the COM-style `object`'s vtable, as an Fn.
template <class Fn>
Fn Method(void* object, int slot) {
    return reinterpret_cast<Fn>((*reinterpret_cast<void***>(object))[slot]);
}

void Release(void*& object) {
    // Nothing to release.
    if (!object) {
        return;
    }

    Method<ULONG(WINAPI*)(void*)>(object, kRelease)(object);
    object = nullptr;
}

// Turns the pass off for this run, logging why once.
void Fail(const char* what, HRESULT result) {
    g_broken = true;
    T3_LOG("display: windowed brightness off, %s failed (0x%08lX)", what, result);
}

// A 16-bit ramp entry as the 8-bit value the screen shows.
BYTE Level(WORD entry) {
    return BYTE((unsigned(entry) + 128) / 257);
}

Levels ToLevels(const GammaRamp& ramp) {
    Levels levels;

    // Each entry of each channel.
    for (int i = 0; i < 256; ++i) {
        levels.red[i] = Level(ramp.red[i]);
        levels.green[i] = Level(ramp.green[i]);
        levels.blue[i] = Level(ramp.blue[i]);
    }

    return levels;
}

// Whether two ramps show the same, give or take one level. The game adds 0.005 to its gamma on every other ramp
// (the float at 0x10F06B34 flips between 0.005 and 0), which moves some levels by one; an option step moves them
// by several.
bool Alike(const Levels& a, const Levels& b) {
    // Compare each level of each channel.
    for (int i = 0; i < 256; ++i) {
        // One level that differs by more is enough.
        if (std::abs(a.red[i] - b.red[i]) > 1 || std::abs(a.green[i] - b.green[i]) > 1 ||
            std::abs(a.blue[i] - b.blue[i]) > 1) {
            return false;
        }
    }

    return true;
}

// The ramp that changes nothing.
Levels IdentityLevels() {
    Levels levels;

    // Every level shows as itself.
    for (int i = 0; i < 256; ++i) {
        levels.red[i] = levels.green[i] = levels.blue[i] = BYTE(i);
    }

    return levels;
}

// Detour of IDirect3DDevice8::SetGammaRamp: keeps the ramp for the pass, then lets Direct3D have it (which
// applies it in exclusive fullscreen).
void WINAPI SetGammaRampDetour(void* device, DWORD flags, const GammaRamp* ramp) {
    const Levels levels = ramp ? ToLevels(*ramp) : Levels{};

    // A ramp that shows differently from the kept one makes the lookup textures stale.
    if (ramp && (!g_haveRamp || !Alike(levels, g_levels))) {
        g_levels = levels;
        g_haveRamp = true;
        g_identity = Alike(levels, IdentityLevels());
        g_lutsStale = true;
        T3_LOG("display: the game set its gamma ramp (%s, mid-grey -> %u)", g_identity ? "no change" : "changed",
               unsigned(levels.green[128]));
    }

    g_setGammaRamp(device, flags, ramp);
}

// ---- the pass's objects -------------------------------------------------------------------

// Creates what lives through resets: the lookup textures (managed) and the pixel shader. Returns false (and turns
// the pass off) when the device cannot have them.
bool CreateLasting(void* device) {
    // Done already.
    if (g_shader) {
        return true;
    }

    BYTE caps[kCapsSize] = {};
    Method<HRESULT(WINAPI*)(void*, void*)>(device, kDeviceGetDeviceCaps)(device, caps);
    DWORD shaderVersion;
    memcpy(&shaderVersion, caps + kCapsPixelShaderVersion, sizeof(shaderVersion));

    // The lookups need pixel shader 1.1 (every card since 2001, and DXVK).
    if ((shaderVersion & 0xFFFF) < 0x0101) {
        Fail("pixel shader 1.1 (the device has none)", E_NOTIMPL);
        return false;
    }

    using CreateTextureFn = HRESULT(WINAPI*)(void*, UINT, UINT, UINT, DWORD, UINT, UINT, void**);
    auto createTexture = Method<CreateTextureFn>(device, kDeviceCreateTexture);
    HRESULT result = createTexture(device, 1, 256, 1, 0, kFormatA8R8G8B8, kPoolManaged, &g_lutRed);

    // Both lookup textures are needed.
    if (SUCCEEDED(result)) {
        result = createTexture(device, 256, 256, 1, 0, kFormatA8R8G8B8, kPoolManaged, &g_lutGreenBlue);
    }

    // Without them there is nothing to look up in.
    if (FAILED(result)) {
        Fail("creating the lookup textures", result);
        return false;
    }

    using CreatePixelShaderFn = HRESULT(WINAPI*)(void*, const DWORD*, DWORD*);
    result = Method<CreatePixelShaderFn>(device, kDeviceCreatePixelShader)(device, kPixelShader, &g_shader);

    // The shader does the lookups.
    if (FAILED(result)) {
        g_shader = 0;
        Fail("creating the pixel shader", result);
        return false;
    }

    return true;
}

// Writes the ramp into the lookup textures.
bool FillLookups() {
    using LockFn = HRESULT(WINAPI*)(void*, UINT, LockedRect*, const RECT*, DWORD);
    using UnlockFn = HRESULT(WINAPI*)(void*, UINT);
    LockedRect locked{};
    HRESULT result = Method<LockFn>(g_lutRed, kTextureLockRect)(g_lutRed, 0, &locked, nullptr, 0);

    // A texture that cannot be written cannot hold the ramp.
    if (FAILED(result)) {
        Fail("filling the red lookup", result);
        return false;
    }

    // Red, one level per row: the alpha keeps the frame opaque.
    for (int v = 0; v < 256; ++v) {
        auto row = reinterpret_cast<uint32_t*>(static_cast<BYTE*>(locked.pBits) + v * locked.Pitch);
        row[0] = 0xFF000000u | uint32_t(g_levels.red[v]) << 16;
    }

    Method<UnlockFn>(g_lutRed, kTextureUnlockRect)(g_lutRed, 0);
    result = Method<LockFn>(g_lutGreenBlue, kTextureLockRect)(g_lutGreenBlue, 0, &locked, nullptr, 0);

    // As for red.
    if (FAILED(result)) {
        Fail("filling the green and blue lookup", result);
        return false;
    }

    // Green across, blue down.
    for (int v = 0; v < 256; ++v) {
        auto row = reinterpret_cast<uint32_t*>(static_cast<BYTE*>(locked.pBits) + v * locked.Pitch);
        const uint32_t blue = g_levels.blue[v];

        // One texel per green level.
        for (int u = 0; u < 256; ++u) {
            row[u] = uint32_t(g_levels.green[u]) << 8 | blue;
        }
    }

    Method<UnlockFn>(g_lutGreenBlue, kTextureUnlockRect)(g_lutGreenBlue, 0);
    g_lutsStale = false;
    return true;
}

// Makes sure the frame copy matches the back buffer `desc` and the state block exists (both go on a reset).
bool CreatePerReset(void* device, const SurfaceDesc& desc) {
    // A frame copy of another size or format is replaced.
    if (g_frame && (g_frameWidth != desc.Width || g_frameHeight != desc.Height || g_frameFormat != desc.Format)) {
        Release(g_frame);
    }

    // Copy the frame into a texture of its own size and format (CopyRects neither stretches nor converts).
    if (!g_frame) {
        using CreateTextureFn = HRESULT(WINAPI*)(void*, UINT, UINT, UINT, DWORD, UINT, UINT, void**);
        HRESULT result = Method<CreateTextureFn>(device, kDeviceCreateTexture)(
            device, desc.Width, desc.Height, 1, kUsageRenderTarget, desc.Format, kPoolDefault, &g_frame);

        // Without the copy there is nothing to draw from.
        if (FAILED(result)) {
            g_frame = nullptr;
            Fail("creating the frame copy", result);
            return false;
        }

        g_frameWidth = desc.Width;
        g_frameHeight = desc.Height;
        g_frameFormat = desc.Format;
    }

    // The state block puts the game's state back after the pass.
    if (!g_stateBlock) {
        using CreateStateBlockFn = HRESULT(WINAPI*)(void*, UINT, DWORD*);
        HRESULT result =
            Method<CreateStateBlockFn>(device, kDeviceCreateStateBlock)(device, kStateBlockAll, &g_stateBlock);

        // Drawing without one would leave the game's state changed.
        if (FAILED(result)) {
            g_stateBlock = 0;
            Fail("creating the state block", result);
            return false;
        }
    }

    return true;
}

// Releases everything the pass made for `g_device`.
void ReleaseAll() {
    BeforeReset();
    Release(g_lutRed);
    Release(g_lutGreenBlue);
    g_shader = 0;  // shaders go with their device
    g_lutsStale = true;
}

// ---- the pass -----------------------------------------------------------------------------

// Sets the states the pass draws with: the frame and the lookups on stages 0-2, point sampled and clamped,
// nothing tested, blended or culled.
void SetPassStates(void* device) {
    auto renderState = Method<HRESULT(WINAPI*)(void*, DWORD, DWORD)>(device, kDeviceSetRenderState);
    auto stageState = Method<HRESULT(WINAPI*)(void*, DWORD, DWORD, DWORD)>(device, kDeviceSetTextureStageState);
    auto setTexture = Method<HRESULT(WINAPI*)(void*, DWORD, void*)>(device, kDeviceSetTexture);

    renderState(device, kRsZEnable, FALSE);
    renderState(device, kRsZWriteEnable, FALSE);
    renderState(device, kRsAlphaTestEnable, FALSE);
    renderState(device, kRsAlphaBlendEnable, FALSE);
    renderState(device, kRsStencilEnable, FALSE);
    renderState(device, kRsFogEnable, FALSE);
    renderState(device, kRsSpecularEnable, FALSE);
    renderState(device, kRsCullMode, kCullNone);
    renderState(device, kRsFillMode, kFillSolid);
    renderState(device, kRsColorWriteEnable, kColorWriteAll);

    void* textures[] = {g_frame, g_lutRed, g_lutGreenBlue};

    // Stages 0-2: the frame, then the two lookups.
    for (DWORD stage = 0; stage < 3; ++stage) {
        setTexture(device, stage, textures[stage]);
        renderState(device, kRsWrap0 + stage, 0);
        stageState(device, stage, kTssTexCoordIndex, 0);
        stageState(device, stage, kTssTextureTransformFlags, 0);
        stageState(device, stage, kTssAddressU, kAddressClamp);
        stageState(device, stage, kTssAddressV, kAddressClamp);
        stageState(device, stage, kTssMagFilter, kFilterPoint);
        stageState(device, stage, kTssMinFilter, kFilterPoint);
        stageState(device, stage, kTssMipFilter, kFilterNone);
    }

    Method<HRESULT(WINAPI*)(void*, DWORD)>(device, kDeviceSetVertexShader)(device, kFvfXyzRhwTex1);
    Method<HRESULT(WINAPI*)(void*, DWORD)>(device, kDeviceSetPixelShader)(device, g_shader);
}

// Copies the back buffer `backBuffer` into the frame texture and draws it back through the lookups.
bool Draw(void* device, void* backBuffer) {
    void* copy = nullptr;
    Method<HRESULT(WINAPI*)(void*, UINT, void**)>(g_frame, kTextureGetSurfaceLevel)(g_frame, 0, &copy);

    // The frame texture's surface receives the copy.
    if (!copy) {
        Fail("reading the frame copy's surface", E_FAIL);
        return false;
    }

    using CopyRectsFn = HRESULT(WINAPI*)(void*, void*, const RECT*, UINT, void*, const POINT*);
    HRESULT result = Method<CopyRectsFn>(device, kDeviceCopyRects)(device, backBuffer, nullptr, 0, copy, nullptr);
    Release(copy);

    // Without the copy the pass would draw an old frame.
    if (FAILED(result)) {
        Fail("copying the frame", result);
        return false;
    }

    // Draw into the back buffer, keeping the game's target and depth buffer to put back.
    void* target = nullptr;
    void* depth = nullptr;
    Method<HRESULT(WINAPI*)(void*, void**)>(device, kDeviceGetRenderTarget)(device, &target);
    Method<HRESULT(WINAPI*)(void*, void**)>(device, kDeviceGetDepthStencilSurface)(device, &depth);
    Method<HRESULT(WINAPI*)(void*, DWORD)>(device, kDeviceCaptureStateBlock)(device, g_stateBlock);
    auto setTarget = Method<HRESULT(WINAPI*)(void*, void*, void*)>(device, kDeviceSetRenderTarget);
    setTarget(device, backBuffer, nullptr);

    // A quad over the whole back buffer, half a pixel up and left so texels land on pixels.
    const float right = float(g_frameWidth) - 0.5f;
    const float bottom = float(g_frameHeight) - 0.5f;
    const Vertex quad[] = {
        {-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f},
        {right, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f},
        {-0.5f, bottom, 0.0f, 1.0f, 0.0f, 1.0f},
        {right, bottom, 0.0f, 1.0f, 1.0f, 1.0f},
    };

    Method<HRESULT(WINAPI*)(void*)>(device, kDeviceBeginScene)(device);
    SetPassStates(device);
    using DrawUPFn = HRESULT(WINAPI*)(void*, UINT, UINT, const void*, UINT);
    result = Method<DrawUPFn>(device, kDeviceDrawPrimitiveUP)(device, kTriangleStrip, 2, quad, sizeof(Vertex));
    Method<HRESULT(WINAPI*)(void*)>(device, kDeviceEndScene)(device);

    // The game's target first (setting one resets the viewport), then the rest of its state.
    setTarget(device, target, depth);
    Method<HRESULT(WINAPI*)(void*, DWORD)>(device, kDeviceApplyStateBlock)(device, g_stateBlock);
    Release(target);
    Release(depth);

    // A draw the device refused leaves the frame as the game drew it: say so and stop trying.
    if (FAILED(result)) {
        Fail("drawing the frame", result);
        return false;
    }

    return true;
}

}  // namespace

// ---- entry points ---------------------------------------------------------------------------

void Configure(bool enabled) {
    g_enabled = enabled;
}

bool Enabled() {
    return g_enabled;
}

void Attach(void* device, bool windowed) {
    // Nothing to do with the pass off.
    if (!g_enabled) {
        return;
    }

    // A new device: what was made for the old one goes with it.
    if (device != g_device) {
        ReleaseAll();
        g_device = device;
    }

    g_windowed = windowed;

    // Hook SetGammaRamp once (every device of the process shares the vtable).
    if (!g_setGammaRamp) {
        void* target = Method<void*>(device, kDeviceSetGammaRamp);
        MH_STATUS status = MH_CreateHook(target, reinterpret_cast<void*>(&SetGammaRampDetour),
                                         reinterpret_cast<void**>(&g_setGammaRamp));

        // Enable the hook only when it was created.
        if (status == MH_OK) {
            status = MH_EnableHook(target);
        }

        // Without the hook there is no ramp to draw with.
        if (status != MH_OK) {
            g_broken = true;
            T3_LOG("display: windowed brightness off, SetGammaRamp hook failed (%s)", MH_StatusToString(status));
            return;
        }
    }

    BYTE caps[kCapsSize] = {};
    Method<HRESULT(WINAPI*)(void*, void*)>(device, kDeviceGetDeviceCaps)(device, caps);
    DWORD caps2;
    memcpy(&caps2, caps + kCapsCaps2, sizeof(caps2));
    T3_LOG("display: windowed brightness %s (%s device; the game sets its ramp %s)",
           windowed ? "drawn by the SDK" : "left to Direct3D", windowed ? "windowed" : "fullscreen",
           caps2 & kCaps2FullscreenGamma ? "on this device" : "only with full-screen gamma, which it lacks");
}

void BeforeReset() {
    // Delete the state block before the reset: Reset fails while one exists.
    if (g_stateBlock && g_device) {
        Method<HRESULT(WINAPI*)(void*, DWORD)>(g_device, kDeviceDeleteStateBlock)(g_device, g_stateBlock);
    }

    g_stateBlock = 0;
    Release(g_frame);
}

void BeforePresent(void* device) {
    // Draw only for a windowed device the game gave a ramp that changes something.
    if (!g_enabled || g_broken || !g_windowed || device != g_device || !g_haveRamp || g_identity) {
        return;
    }

    // The lookups and the shader, once.
    if (!CreateLasting(device)) {
        return;
    }

    // Bring the lookups up to the ramp.
    if (g_lutsStale && !FillLookups()) {
        return;
    }

    void* backBuffer = nullptr;
    using GetBackBufferFn = HRESULT(WINAPI*)(void*, UINT, UINT, void**);
    Method<GetBackBufferFn>(device, kDeviceGetBackBuffer)(device, 0, kBackBufferMono, &backBuffer);

    // Without a back buffer there is no frame to draw.
    if (!backBuffer) {
        return;
    }

    SurfaceDesc desc{};
    Method<HRESULT(WINAPI*)(void*, SurfaceDesc*)>(backBuffer, kSurfaceGetDesc)(backBuffer, &desc);
    const bool drawn = CreatePerReset(device, desc) && Draw(device, backBuffer);
    Release(backBuffer);

    // Log the first drawn frame.
    if (drawn && !g_announced) {
        g_announced = true;
        T3_LOG("display: windowed brightness drawn (%ux%u, format %u)", desc.Width, desc.Height, desc.Format);
    }
}

}  // namespace t3sdk::display::gamma
