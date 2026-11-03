// Steady first-person view: three fixes for a camera that is tied too closely
// to Garrett's animated body (docs/engine.md, "First-person camera").
//
// - Eye: the first-person eye is the "Camera Attach" bone of Garrett's
//   skeleton, so every animation moves the view: breathing, the walk bob,
//   the jump (the eye rises 8 units above his centre in the air), the climb
//   (it swings over 30 units) and the landing. Here the eye stays at a resting
//   spot relative to Garrett and the way he looks (height, forward, side).
//   On the ground that spot slowly follows the bone's average place, which
//   changes with his stance (standing, moving, crouching); while he moves up
//   or down (jumping, falling, climbing) it holds still. A little of the
//   animation's motion stays on top, as head bob. On a ladder or a rope the
//   game's eye takes over, with only the climb's steps eased: Garrett faces
//   the rungs there, and his animation keeps the eye clear of them.
//   Everything that asks for the eye (the camera, the bow's aim and arrow,
//   the melee sweep) gets the same one; only the camera's call, once a
//   frame, moves the smoothing on.
// - Snaps: on touching the ground Garrett's physics body drops about 19 units
//   in one frame (its airborne shape becomes its standing one), then settles.
//   The eye keeps to the path his vertical speed predicted and eases into the
//   new height, so a landing or the top of a climb no longer jolts the view.
// - Turning: once Garrett moves, his body turns toward the view at about
//   302 degrees a second, and movement input is applied in the body's frame,
//   so walking off at an angle curves. The turn rate is a constant; it is
//   raised so the body faces the view at once (or set to any speed).
// - Clipping: the scene is drawn with its near plane 1 unit from the eye, and
//   the bow and held items, drawn with the world, cut into it (more so with a
//   wider FOV). The near plane is moved closer.
#include <t3sdk/modkit.hpp>
#include <t3sdk/t3sdk.h>

#include <windows.h>

#include <intrin.h>

#include <cmath>
#include <cstdint>
#include <cstdio>
#include <iterator>

namespace {

// ---- game addresses -----------------------------------------------------------------

// FVector* __thiscall AGarrett::GetCameraTargetLocation(FVector* out): the "Camera Attach" bone's world
// position (Location without one), pulled back from walls along the view.
constexpr uintptr_t kGetCameraTargetLocation = 0x10B21830;

// float: the body's turn rate toward the view while moving, in rotation units (65536 a turn) per second,
// read only by the body-turn function (0x10B19300).
constexpr uintptr_t kBodyTurnRate = 0x10E793FC;
constexpr float kGameTurnRate = 55000.0f;

// The near-plane distance the scene render (0x109FCF10) pushes for each pass: `push 1.0` immediates.
constexpr uintptr_t kNearPlanes[] = {0x109FD10E, 0x109FD3FD, 0x109FD54E, 0x109FD5FC};
constexpr float kGameNearPlane = 1.0f;

// AActor / APawn / AGarrett fields.
constexpr uint32_t kLocation = 0x2C;
constexpr uint32_t kVelocity = 0x44;
constexpr uint32_t kBodyYaw = 0x3C;
constexpr uint32_t kBaseEyeHeight = 0x118;
constexpr uint32_t kEyeHeight = 0x11C;
constexpr uint32_t kViewYaw = 0x404;           // HeadRot.Yaw: where Garrett looks
constexpr uint32_t kGarrettFlags = 0x450;      // bit 1: crouching
constexpr uint32_t kThirdPersonFlags = 0x490;  // bit 0: bIn3rdPersonMode
constexpr uint32_t kNoiseFlags = 0x4D0;        // bit 2: bNoiseEnabled

// bUpdatePhysHeight (kGarrettFlags 0x10) is set on the ground and cleared by every climb (ladders, ropes, mantles).
// bNoiseEnabled (kNoiseFlags 0x4) is turned on by the ladder and rope climbs only (SetNoiseEnabled, 0x10B21B90).
constexpr uint32_t kUpdatePhysHeight = 0x10;
constexpr uint32_t kNoiseEnabled = 0x4;

// The return address of the camera's own call (GarrettOnCamera, 0x10AC2630): once a frame. The bow, its reticle,
// the melee sweep and a camera fade call too, and get the same eye without moving the state.
constexpr uintptr_t kCameraCall = 0x10AC271A;

// Rotation units per degree, and per radian.
constexpr float kUnitsPerDegree = 65536.0f / 360.0f;
constexpr float kRadiansPerUnit = 6.2831853f / 65536.0f;

// ---- settings -----------------------------------------------------------------------

struct Settings {
    // How long the resting eye spot takes to follow a change of stance, in seconds (0 = the eye rides the bone).
    float smoothing = 0.25f;

    // How much of the animation's motion stays on top of the resting spot, 0 to 1.
    float headBob = 0.15f;

    // How long the eye takes to settle after Garrett's body snaps to a new height, in seconds (0 = at once).
    float landing = 0.12f;

    // Body turn speed in degrees a second while moving; 0 = at once.
    float turnSpeed = 0.0f;

    // The near plane's distance from the eye, in Unreal units.
    float nearPlane = 0.5f;

    // Write every camera update to steady-view-trace.csv (debugging).
    bool trace = false;
};

Settings g_settings;

// ---- the eye ---------------------------------------------------------------------------

struct FVector {
    float x, y, z;
};

using GetCameraTargetLocationFn = FVector*(__fastcall*)(void* pawn, void* edx, FVector* out);

// The SDK's function table, kept from T3Mod_Init.
const T3SdkApi* g_api = nullptr;

// The original GetCameraTargetLocation (MinHook trampoline).
GetCameraTargetLocationFn g_getCameraTargetLocation = nullptr;

// Above this vertical speed (units a second) Garrett is jumping, falling or climbing: the resting spot holds.
// He counts as on the ground again only after this long below it, so the top of a jump (where his speed passes
// through 0) does not.
constexpr float kSteadySpeed = 20.0f;
constexpr float kGroundedAfter = 0.15f;

// A height change this far (units) from what his vertical speed predicted, plus 100 units a second of frame
// time, is a snap of the physics body (a landing, a stair step), not motion.
constexpr float kSnapDistance = 1.0f;
constexpr float kSnapPerSecond = 100.0f;

// A snap or change larger than this (units) is a teleport or a new level: start afresh.
constexpr float kTeleport = 100.0f;

// In the air the eye follows the physics body's speed and drifts back toward Garrett's position over this long
// (seconds), so a long fall cannot leave it behind.
constexpr float kAirCorrection = 1.0f;

// What the eye keeps from one camera update to the next.
struct EyeState {
    bool tracking = false;

    // Garrett's height at the last update, and his vertical speed as the last frames showed it.
    float lastZ = 0.0f;
    float speedZ = 0.0f;

    // How far the eye stays above (or below) his new height after a snap; eases back to 0.
    float snap = 0.0f;

    // How long his vertical speed has stayed low, and the share of head bob shown (1 on the ground, 0 in the air).
    float still = 0.0f;
    float bob = 1.0f;

    // The physics body's vertical speed at the last update, and whether it could be read: in the air gravity
    // changes it every frame; on the ground it stays as it was at the landing.
    float lastFall = 0.0f;
    bool fallKnown = false;

    // The resting spot, relative to Garrett and the way he looks: forward, to the side, up.
    float forward = 0.0f;
    float side = 0.0f;
    float up = 0.0f;

    LARGE_INTEGER last = {};

    // The bone's last accepted place (forward, to the side), and how many updates in a row have been set aside
    // as a glitch.
    float rawForward = 0.0f;
    float rawSide = 0.0f;
    int glitches = 0;

    // How far the eye is pulled back from a wall in front, eased in and out.
    float pull = 0.0f;

    // Garrett's place over the ground at the last update.
    float lastX = 0.0f;
    float lastY = 0.0f;

    // How far the eye has gone over to the climbing eye (0 off a ladder, 1 on one), and the climbing eye's height,
    // eased.
    float climb = 0.0f;
    float climbZ = 0.0f;
};

EyeState g_eye;

// For one frame now and then the game computes the eye bone with Garrett's old facing (when his body turns at
// once as he starts to move): its place swings about 90 degrees around him. A horizontal change this large (units)
// from one update to the next is set aside, unless it lasts.
constexpr float kGlitch = 5.0f;
constexpr int kGlitchUpdates = 2;

// The wall pull-back eases in over this long (seconds) and out over the second.
constexpr float kPullIn = 0.08f;
constexpr float kPullOut = 0.2f;

// Head bob leaves over this long (seconds) when Garrett leaves the ground, and comes back over the second.
constexpr float kBobLeave = 0.1f;
constexpr float kBobReturn = 0.4f;

// Below this speed over the ground (units a second) Garrett stands.
constexpr float kStandingSpeed = 10.0f;

// A wall pull-back smaller than this (units) is noise, not a wall.
constexpr float kPullFree = 0.5f;

// The eye goes over to the climbing eye, and back, over this long (seconds); the climbing eye's height eases over the
// second, which smooths the steps of the climb without lagging behind it.
constexpr float kClimbBlend = 0.2f;
constexpr float kClimbHeight = 0.06f;

// Without a camera update for this long (seconds) the other callers move the state, so it can never freeze.
constexpr float kCameraQuiet = 0.05f;

// Garrett is on a ladder or a rope (a mantle, also a climb, keeps the steady eye).
bool OnLadder(void* pawn) {
    bool climbing = !(t3mod::Field<uint32_t>(pawn, kGarrettFlags) & kUpdatePhysHeight);
    return climbing && (t3mod::Field<uint32_t>(pawn, kNoiseFlags) & kNoiseEnabled);
}

// The seconds this call moves the state by, at most 0.1 (a paused game, a loading screen): the time since the last
// state update for the camera's call (or any call once the camera has been quiet a while), 0 for the others.
float StateStep(bool camera) {
    LARGE_INTEGER now;
    LARGE_INTEGER frequency;
    QueryPerformanceCounter(&now);
    QueryPerformanceFrequency(&frequency);
    float since = float(double(now.QuadPart - g_eye.last.QuadPart) / double(frequency.QuadPart));

    // Another caller between two camera updates leaves the state as it is.
    if (!camera && since <= kCameraQuiet) {
        return 0.0f;
    }

    g_eye.last = now;
    return since < 0.1f ? since : 0.1f;
}

// The share of the way to a target that `dt` covers with time constant `tau` (all of it when tau is 0).
float Approach(float dt, float tau) {
    return tau > 0.0f ? 1.0f - std::exp(-dt / tau) : 1.0f;
}

// ---- camera trace (debugging) ------------------------------------------------------------

// The most lines the trace writes, about 20 minutes at 165 frames a second.
constexpr int kMaxTraceLines = 200000;

// steady-view-trace.csv next to the DLL, while [Debug] TraceCamera is on.
FILE* g_trace = nullptr;
int g_traceLines = 0;

// The physics character's block that the game writes Garrett's collision height into (at +0x118, from his state,
// while bUpdatePhysHeight is set; Class_10B22D70 at 0x10B23035): AActor+0xB0 is his physics object, whose
// vtable slot 8 returns the block. The trace records the floats around that height, to find the current one.
constexpr uint32_t kPhysicsObject = 0xB0;
constexpr int kPhysicsBlockSlot = 0x20 / 4;
constexpr uint32_t kTraceBlockFirst = 0xF0;
constexpr int kTraceBlockFloats = 24;

using PhysicsBlockFn = uint8_t*(__fastcall*)(void* self, void* edx);

// The physics character's block, or null.
uint8_t* PhysicsBlock(void* pawn) {
    void* physics = t3mod::Field<void*>(pawn, kPhysicsObject);

    // A pawn without a physics object has no block.
    if (!physics) {
        return nullptr;
    }

    auto get = reinterpret_cast<PhysicsBlockFn*>(*reinterpret_cast<void**>(physics))[kPhysicsBlockSlot];
    return get(physics, nullptr);
}

// The physics block's floats for the trace, or zeros when it cannot be read.
void ReadPhysicsBlock(void* pawn, float* out) {
    // The block is read through a game virtual: guard it, the trace must never take the game down.
    __try {
        uint8_t* block = PhysicsBlock(pawn);

        // Copy the floats around the collision height.
        for (int i = 0; i < kTraceBlockFloats; ++i) {
            out[i] = block ? *reinterpret_cast<float*>(block + kTraceBlockFirst + 4 * i) : 0.0f;
        }
    } __except (EXCEPTION_EXECUTE_HANDLER) {
        // Leave whatever was copied; the rest stays zero.
    }
}

// The physics body's vertical velocity (block +0x100; +0xF8 and +0xFC hold the horizontal ones). While Garrett is
// in the air it is his real, smooth fall; on the ground it keeps its value from the landing. False when it cannot
// be read.
constexpr uint32_t kBodyFallSpeed = 0x100;

bool FallSpeed(void* pawn, float* speed) {
    // Read through a game virtual: guard it, the camera must never take the game down.
    __try {
        uint8_t* block = PhysicsBlock(pawn);

        // A pawn without a physics character has no fall speed.
        if (!block) {
            return false;
        }

        *speed = *reinterpret_cast<float*>(block + kBodyFallSpeed);
        return true;
    } __except (EXCEPTION_EXECUTE_HANDLER) {
        return false;
    }
}

// Opens the trace and writes its header.
void OpenTrace() {
    g_trace = _wfopen(t3mod::ModFile(L"-trace.csv").c_str(), L"w");

    // Without the file there is no trace; the mod works the same.
    if (!g_trace) {
        return;
    }

    std::fputs(
        "t_ms,dt_ms,x,y,z,vx,vy,vz,eye_x,eye_y,eye_z,out_x,out_y,out_z,base_eye,eye_height,flags,body_yaw,"
        "view_yaw,speed_z,snap",
        g_trace);

    // One column per traced float of the physics block, named by its offset.
    for (int i = 0; i < kTraceBlockFloats; ++i) {
        std::fprintf(g_trace, ",p%03X", unsigned(kTraceBlockFirst + 4 * i));
    }

    std::fputs("\n", g_trace);
}

// One line per camera update: what the game gave and what the mod made of it.
void Trace(void* pawn, float dt, const FVector& raw, const FVector& out) {
    // Stop at the size limit: the file is for a short test.
    if (!g_trace || g_traceLines >= kMaxTraceLines) {
        return;
    }

    LARGE_INTEGER now;
    LARGE_INTEGER frequency;
    QueryPerformanceCounter(&now);
    QueryPerformanceFrequency(&frequency);
    const FVector& at = t3mod::Field<FVector>(pawn, kLocation);
    const FVector& v = t3mod::Field<FVector>(pawn, kVelocity);
    std::fprintf(g_trace,
                 "%.3f,%.3f,%.3f,%.3f,%.3f,%.2f,%.2f,%.2f,%.3f,%.3f,%.3f,%.3f,%.3f,%.3f,%.2f,%.2f,%u,%d,%d,%.2f,%.3f",
                 double(now.QuadPart) * 1000.0 / double(frequency.QuadPart), dt * 1000.0f, at.x, at.y, at.z, v.x, v.y,
                 v.z, raw.x, raw.y, raw.z, out.x, out.y, out.z, t3mod::Field<float>(pawn, kBaseEyeHeight),
                 t3mod::Field<float>(pawn, kEyeHeight), t3mod::Field<uint32_t>(pawn, kGarrettFlags),
                 t3mod::Field<int>(pawn, kBodyYaw), t3mod::Field<int>(pawn, kViewYaw), g_eye.speedZ, g_eye.snap);

    float block[kTraceBlockFloats] = {};
    ReadPhysicsBlock(pawn, block);

    // The physics block's floats, after the fixed columns.
    for (float value : block) {
        std::fprintf(g_trace, ",%.4g", value);
    }

    std::fputs("\n", g_trace);
    ++g_traceLines;

    // Flush now and then, so a crash or a quit keeps most of it.
    if (g_traceLines % 256 == 0) {
        std::fflush(g_trace);
    }
}

// ---- the hook --------------------------------------------------------------------------

FVector* __fastcall GetCameraTargetLocationDetour(void* pawn, void* edx, FVector* out) {
    FVector* eye = g_getCameraTargetLocation(pawn, edx, out);
    const bool camera = reinterpret_cast<uintptr_t>(_ReturnAddress()) == kCameraCall;
    FVector raw = *eye;

    // Third person keeps the game's camera; start afresh when first person comes back.
    if (t3mod::Field<uint32_t>(pawn, kThirdPersonFlags) & 1) {
        g_eye.tracking = false;
        Trace(pawn, 0.0f, raw, *eye);
        return eye;
    }

    // Only the camera's own call, once a frame, moves the state; the others see the same eye.
    float dt = StateStep(camera);

    const FVector& body = t3mod::Field<FVector>(pawn, kLocation);
    const float viewYaw = float(t3mod::Field<int>(pawn, kViewYaw)) * kRadiansPerUnit;
    const float c = std::cos(viewYaw);
    const float s = std::sin(viewYaw);

    // The bone's place relative to Garrett and the way he looks: his head turns with the view (up to 90 degrees from
    // his body), so in front of the view is where the bone stays.
    const float dx = raw.x - body.x;
    const float dy = raw.y - body.y;
    float forward = dx * c + dy * s;
    float side = dy * c - dx * s;
    const float up = raw.z - body.z;

    // The first update, or a teleport: take the bone's place as the resting spot.
    if (!g_eye.tracking || std::fabs(body.z - g_eye.lastZ) > kTeleport) {
        g_eye = {true, body.z, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, false, forward, side, up, g_eye.last};
        g_eye.rawForward = forward;
        g_eye.rawSide = side;
        g_eye.lastX = body.x;
        g_eye.lastY = body.y;
    }

    // A call that moves the state: once a frame (a second camera call in the same frame changes nothing).
    if (dt > 0.0005f) {
        // A one-update swing of the bone (see kGlitch): use its last place instead. A change that lasts is taken.
        if (std::hypot(forward - g_eye.rawForward, side - g_eye.rawSide) > kGlitch && g_eye.glitches < kGlitchUpdates) {
            forward = g_eye.rawForward;
            side = g_eye.rawSide;
            ++g_eye.glitches;
        } else {
            g_eye.rawForward = forward;
            g_eye.rawSide = side;
            g_eye.glitches = 0;
        }

        float fall = 0.0f;
        const bool known = FallSpeed(pawn, &fall);
        const bool airborne = known && g_eye.fallKnown && fall != g_eye.lastFall;
        g_eye.fallKnown = known;
        g_eye.lastFall = fall;

        // On a ladder or a rope the eye goes over to the climbing eye (below), and its own height simply keeps up
        // with Garrett's: the climb's steps are not snaps, and its speed is not a fall.
        const bool ladder = OnLadder(pawn);
        g_eye.climb += ((ladder ? 1.0f : 0.0f) - g_eye.climb) * Approach(dt, kClimbBlend);

        // Off the ladder (and back from it) the climbing eye's height starts at the bone; on it, it eases after it.
        if (g_eye.climb < 0.001f) {
            g_eye.climbZ = raw.z;
        } else {
            g_eye.climbZ += (raw.z - g_eye.climbZ) * Approach(dt, kClimbHeight);
        }

        // On the ladder: keep up with Garrett's height, and let any snap settle.
        if (ladder) {
            g_eye.lastZ = body.z;
            g_eye.speedZ = 0.0f;
            g_eye.snap *= 1.0f - Approach(dt, g_settings.landing);
        } else if (airborne) {
            // In the air the physics body's own vertical speed carries the eye: Garrett's position only chases the
            // body, at 64 units a second, which bumps up at the top of a jump and drops 19 units on landing.
            float height = g_eye.lastZ + g_eye.snap + fall * dt;
            height += (body.z - height) * Approach(dt, kAirCorrection);
            g_eye.snap = height - body.z;
            g_eye.speedZ = fall;
            g_eye.lastZ = body.z;
        } else {
            float dz = body.z - g_eye.lastZ;
            float error = dz - g_eye.speedZ * dt;
            g_eye.lastZ = body.z;

            // The body jumped away from where its speed was taking it: keep the eye on that path, and ease it over.
            // A snap ends the motion that predicted it (a landing stops the fall, a stair step the stride), so the
            // speed starts over: kept, a long fall's speed would call every following update a snap and sink the eye.
            if (std::fabs(error) > kSnapDistance + kSnapPerSecond * dt) {
                g_eye.snap -= error;
                g_eye.speedZ = 0.0f;
            } else {
                g_eye.speedZ += (dz / dt - g_eye.speedZ) * Approach(dt, 0.04f);
            }

            g_eye.snap *= 1.0f - Approach(dt, g_settings.landing);
        }

        // A snap that never settles (a lift, a teleport the check missed) is let go.
        if (std::fabs(g_eye.snap) > kTeleport) {
            g_eye.snap = 0.0f;
        }

        // A ladder is no ground: the resting spot holds there as it does in the air.
        g_eye.still = std::fabs(g_eye.speedZ) < kSteadySpeed && !ladder ? g_eye.still + dt : 0.0f;
        const bool grounded = g_eye.still >= kGroundedAfter;

        // Head bob leaves quickly on take-off and comes back slowly after landing, so the land animation (which sags
        // the eye for a few hundred milliseconds) does not come back as a dip.
        const bool rising = grounded && g_eye.bob < 1.0f;
        g_eye.bob += ((grounded ? 1.0f : 0.0f) - g_eye.bob) * Approach(dt, rising ? kBobReturn : kBobLeave);

        // Garrett's speed over the ground, for telling standing from moving.
        const float groundSpeed = std::hypot(body.x - g_eye.lastX, body.y - g_eye.lastY) / dt;
        g_eye.lastX = body.x;
        g_eye.lastY = body.y;

        // On the ground the resting height follows the bone's average height (standing, moving, crouching); in
        // the air or climbing it holds.
        if (grounded) {
            float k = Approach(dt, g_settings.smoothing);
            g_eye.up += (up - g_eye.up) * k;

            // The bone leans about 6 units further forward while Garrett moves, and back when he stops: a head
            // does not, so its place in front of him is learned only while he stands, and not while a wall pulls it.
            if (groundSpeed < kStandingSpeed && g_eye.pull < kPullFree) {
                g_eye.forward += (forward - g_eye.forward) * k;
                g_eye.side += (side - g_eye.side) * k;
            }
        }

        // The game pulls the eye back from a wall in front: on the ground, when its eye is closer than the resting
        // spot, follow it there, eased in and out.
        const float wanted = grounded && forward < g_eye.forward - kPullFree ? g_eye.forward - forward : 0.0f;
        g_eye.pull += (wanted - g_eye.pull) * Approach(dt, wanted > g_eye.pull ? kPullIn : kPullOut);
    }

    // The resting spot, pulled back from walls, with a share of the animation's up and down motion as head bob (none
    // in the air: the jump animation lifts the eye). The bone's forward and sideways motion is animation (the lean,
    // the landing), not bob, and stays out.
    const float bob = g_settings.headBob * g_eye.bob;
    const float f = g_eye.forward - g_eye.pull;
    const float r = g_eye.side;
    const float u = g_eye.up + bob * (up - g_eye.up);

    FVector steady = {body.x + f * c - r * s, body.y + f * s + r * c, body.z + u + g_eye.snap};

    // On a ladder or a rope the game's eye leads: Garrett faces the rungs, and the climb animation keeps his head
    // clear of them, which a spot in front of the view would not. Only the climb's steps are eased (climbZ).
    const float w = g_eye.climb;
    eye->x = steady.x + (raw.x - steady.x) * w;
    eye->y = steady.y + (raw.y - steady.y) * w;
    eye->z = steady.z + (g_eye.climbZ - steady.z) * w;

    Trace(pawn, dt, raw, *eye);
    return eye;
}

// ---- setup ----------------------------------------------------------------------------

void ReadSettings() {
    std::wstring ini = t3mod::SettingsFile();
    g_settings.smoothing = t3mod::ReadFloat(ini, L"View", L"Smoothing", 250.0f, 0.0f, 2000.0f) / 1000.0f;
    g_settings.headBob = t3mod::ReadFloat(ini, L"View", L"HeadBob", 0.15f, 0.0f, 1.0f);
    g_settings.landing = t3mod::ReadFloat(ini, L"View", L"LandingSmoothing", 120.0f, 0.0f, 1000.0f) / 1000.0f;
    g_settings.turnSpeed = t3mod::ReadFloat(ini, L"Turning", L"BodyTurnSpeed", 0.0f, 0.0f, 3600.0f);
    g_settings.nearPlane = t3mod::ReadFloat(ini, L"Clipping", L"NearClip", 0.5f, 0.05f, 1.0f);
    g_settings.trace = t3mod::ReadBool(ini, L"Debug", L"TraceCamera", false);
}

}  // namespace

// Called by the SDK when the mod is loaded. Each part that is set to change
// something is applied on its own; returns non-zero (the mod unloads) when none is.
T3SDK_EXPORT int T3SDK_CALL T3Mod_Init(const T3SdkApi* api) {
    g_api = api;
    ReadSettings();
    int applied = 0;

    // Eye: smoothing 0 leaves the camera on the bone, as the game has it.
    if (g_settings.smoothing > 0.0f) {
        bool hooked =
            t3mod::Hook(api, kGetCameraTargetLocation, reinterpret_cast<void*>(&GetCameraTargetLocationDetour),
                        reinterpret_cast<void**>(&g_getCameraTargetLocation), "camera target location");

        // A missing hook leaves the eye as the game has it; the other parts still apply.
        if (hooked) {
            api->Log("steady eye: stance follows over %.0f ms, %.0f%% head bob, landings settle over %.0f ms",
                     g_settings.smoothing * 1000.0f, g_settings.headBob * 100.0f, g_settings.landing * 1000.0f);
            ++applied;
        }

        // The trace records in the eye hook.
        if (hooked && g_settings.trace) {
            OpenTrace();
            api->Log("tracing the camera to steady-view-trace.csv");
        }
    }

    // Turning: 0 is "at once", which a rate far above any frame's turn gives.
    float rate = g_settings.turnSpeed > 0.0f ? g_settings.turnSpeed * kUnitsPerDegree : 1.0e7f;

    // The game's own 302 degrees a second needs no patch.
    if (rate != kGameTurnRate && t3mod::Patch(api, kBodyTurnRate, kGameTurnRate, rate, "body turn rate")) {
        // Say which of the two the setting asked for.
        if (g_settings.turnSpeed > 0.0f) {
            api->Log("body turns at %.0f degrees a second", g_settings.turnSpeed);
        } else {
            api->Log("body faces the view at once");
        }

        ++applied;
    }

    // Clipping: the four render passes share the near plane; patch all or report the ones that differ.
    if (g_settings.nearPlane != kGameNearPlane) {
        int patched = 0;

        // Each pass pushes its own copy of the near-plane distance.
        for (uintptr_t address : kNearPlanes) {
            patched += t3mod::Patch(api, address, kGameNearPlane, g_settings.nearPlane, "near plane") ? 1 : 0;
        }

        // Count the clipping fix as applied only if every pass got the new distance.
        if (patched == int(std::size(kNearPlanes))) {
            api->Log("near plane at %.2f units", g_settings.nearPlane);
            ++applied;
        }
    }

    return applied ? 0 : 1;
}
