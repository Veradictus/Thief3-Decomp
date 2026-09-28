// A minimal T3SDK mod: logs when it loads, when the engine is up, and how many
// frames it saw when the game exits. The API is t3sdk/t3sdk.h; the rules for
// when each callback runs are in its header comment and in docs/sdk.md.
#include <t3sdk/t3sdk.h>

namespace {

const T3SdkApi* g_api = nullptr;
unsigned g_frames = 0;

// Runs on the game's main thread once per pass of its message loop.
void T3SDK_CALL OnFrame(void*) {
    if (!g_api->EngineReady()) {
        return;  // engine objects are only valid while EngineReady() holds
    }
    if (g_frames++ == 0) {
        g_api->Log("engine up: %d object slots", g_api->ObjectCount());
    }
}

}  // namespace

// Runs before the game's own start-up code: register callbacks, touch no engine state.
T3SDK_EXPORT int T3SDK_CALL T3Mod_Init(const T3SdkApi* api) {
    if (api->version < T3SDK_API_VERSION) {
        return 1;  // an older SDK than this mod was built for: stay unloaded
    }
    g_api = api;
    if (api->AddFrameCallback(OnFrame, nullptr) != 0) {
        return 1;
    }
    api->Log("loaded; waiting for the engine");
    return 0;
}

// Optional: runs when the game exits, in reverse load order.
T3SDK_EXPORT void T3SDK_CALL T3Mod_Shutdown(void) { g_api->Log("shutting down after %u frames", g_frames); }
