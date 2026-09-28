# Run code every frame

Run code on every game frame, and separately run something once, the first
time the engine is ready.

## The recipe

Register a frame callback in `T3Mod_Init`. Use a flag to notice the one
moment the engine becomes ready, and act on every frame after that:

```cpp
#include <t3sdk/t3sdk.h>

namespace {

const T3SdkApi* api = nullptr;
bool announced = false;
unsigned frames = 0;

void T3SDK_CALL OnFrame(void*) {
    if (!api->EngineReady()) {
        return;  // never actually seen: T3SDK holds frame callbacks back until this is true
    }
    if (!announced) {
        announced = true;
        api->Log("engine ready");
        // one-time set-up that needs engine objects goes here
    }
    if (++frames % 600 == 0) {  // roughly every 10 seconds at 60 fps
        api->Log("%u frames since the engine came up", frames);
    }
}

}  // namespace

T3SDK_EXPORT int T3SDK_CALL T3Mod_Init(const T3SdkApi* sdk) {
    if (sdk->version < T3SDK_API_VERSION) {
        return 1;
    }
    api = sdk;
    if (api->AddFrameCallback(OnFrame, nullptr) != 0) {
        return 1;
    }
    return 0;
}
```

`OnFrame` runs once per pass of the game's message loop, on the main thread.
T3SDK does not call it at all until `EngineReady()` first returns non-zero,
and stops calling it once the game begins exiting, which is why the check at
the top never actually fails in practice; keep it anyway; it documents the
requirement and costs nothing. [The mod lifecycle](../lifecycle.md) has the
full sequence of events, and the reasons behind it.

There is no separate "engine just became ready" callback, so the `announced`
flag above is the pattern for one-time set-up that needs engine objects: the
same one [`sdk/mods/hello`](../../../sdk/mods/hello/hello.cpp) uses
(`g_engineUp`).

## Running something before the engine exists

`T3Mod_Init` itself runs once, before the engine exists, so it already *is*
"run once at start-up": use it directly for anything that does not need
engine objects, such as registering callbacks or creating hooks. There is no
periodic callback before the engine is ready — frame callbacks wait for it,
and log callbacks only fire when the engine actually writes a line (see
[Write to the log, and read the engine's own lines](logging.md)). If you need
to act earlier than "engine ready" but later than "process start", watching
the engine's own log lines is the closest the API gets.

## Watch out for

- The game waits for every frame callback of every loaded mod before it draws
  the next frame. Keep yours short: no blocking I/O, no sleeping, and no
  large scan of the object table on every single frame (see
  [Find and inspect objects](objects.md) for cheaper ways to look things up).
- Frame callbacks, `T3Mod_Init` and `T3Mod_Shutdown` all run on the game's
  main thread, so they never race each other. They do race engine log
  callbacks, which run on whichever thread logged; see
  [logging.md](logging.md) if you share state between the two.
- An exception inside a frame callback is caught: T3SDK logs it and switches
  that one callback off, and the game and your other callbacks continue.
  `T3Mod_Init` is not guarded the same way: a crash there ends T3SDK's
  start-up, and mods later in the load order do not load at all, so keep it
  to registering callbacks and hooks.
- Object pointers are only valid while `EngineReady()` holds; stop using
  them once the game begins exiting. Every level change restarts the game's
  process, so your mod starts again from `T3Mod_Init` with each level (see
  [Find and inspect objects](objects.md)).

## Reference

- [Mod API reference](../../reference/api.md): `AddFrameCallback`,
  `EngineReady`.
- [The mod lifecycle](../lifecycle.md): the full sequence from start-up to
  exit, and the threading and error rules.
