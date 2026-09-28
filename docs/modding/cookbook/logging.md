# Write to the log, and read the engine's own lines

Write your own diagnostic lines to `T3SDK.log`, and react to the lines the
game engine itself writes there.

## Write your own lines

`api->Log` is a printf-style call, tagged automatically with your mod's name:

```cpp
api->Log("player controller: %s", path);
```

Call it from anywhere you hold the API pointer: `T3Mod_Init`, a frame
callback, an engine log callback, or your own hook detour. There is no log
level and no filtering on your side — every call is written to the file (the
`T3SDK.ini` `Console` key, described in [Debug a mod](debugging.md), only
controls whether a live window also shows it). Keep the work cheap: a frame
callback runs every frame, so don't format large strings there unless you
actually need to.

## Read the engine's own lines

Register an engine log callback to see what the game itself writes, from
start-up onward. `T3SDK.ini`'s `EngineLog` setting, on by default, already
copies these lines into `T3SDK.log` for a player to read; use the callback
instead when your mod needs to react to them, not just show them:

```cpp
#include <t3sdk/t3sdk.h>

#include <mutex>
#include <string>
#include <unordered_map>

namespace {

const T3SdkApi* api = nullptr;
std::mutex countsMutex;
std::unordered_map<std::string, int> counts;  // guarded by countsMutex

void T3SDK_CALL OnEngineLog(void*, const char* /*text*/, const char* category) {
    std::lock_guard<std::mutex> lock(countsMutex);
    ++counts[category];
}

void T3SDK_CALL OnFrame(void*) {
    static unsigned frame = 0;
    if (!api->EngineReady() || ++frame % 600 != 0) {
        return;  // report roughly every 10 seconds
    }
    std::lock_guard<std::mutex> lock(countsMutex);
    for (const auto& [category, count] : counts) {
        api->Log("%s: %d lines", category.c_str(), count);
    }
}

}  // namespace

T3SDK_EXPORT int T3SDK_CALL T3Mod_Init(const T3SdkApi* sdk) {
    if (sdk->version < T3SDK_API_VERSION) {
        return 1;
    }
    api = sdk;
    if (api->AddEngineLogCallback(OnEngineLog, nullptr) != 0 || api->AddFrameCallback(OnFrame, nullptr) != 0) {
        return 1;
    }
    return 0;
}
```

`category` is the engine's own category text, the same words you see in the
log file: `Log`, `Init`, `Warning`, `Cmd`, and so on.

## Watch out for

- Engine log callbacks run on whichever thread wrote the line, from
  start-up onward — possibly before `EngineReady()`, and not necessarily the
  main thread. The example above shares `counts` with a frame callback, so
  it guards every access with a `std::mutex`, as
  [`sdk/mods/hello`](../../../sdk/mods/hello/hello.cpp) does for its own
  map.
- An exception in a log callback is caught the same way as a frame callback:
  T3SDK logs it and switches that one callback off.
- `api->Log` does not add anything of its own beyond the one line per call;
  build a complete message before calling it rather than calling it in
  pieces.

## Reference

- [Mod API reference](../../reference/api.md): `Log`, `AddEngineLogCallback`.
- [The mod lifecycle](../lifecycle.md): threading rules for each callback.
- [Debug a mod](debugging.md): `T3SDK.ini`'s `Console` setting, and reading
  a crash report.
