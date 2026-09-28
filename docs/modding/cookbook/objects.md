# Find and inspect objects

Locate engine objects — actors, classes, the player controller — and read
basic facts about them, once the engine is up.

## Wait for the engine

Every object function returns 0/`NULL` until `EngineReady()` holds (see
[Run code every frame](every-frame.md)). Everything below runs inside a
frame callback.

## Find or enumerate objects

`FindObject(className, pathName)` does a linear search by full path; pass
`NULL` for `className` to match any class. The path is the object's dotted
`Outer` chain, for example `FindObject("Class", "Engine.PlayerController")`
for a class, or `FindObject(NULL, "Entry.Camera__0")` for one particular
instance. An FName with a non-zero instance number prints with that `__N-1`
suffix; see [`unreal.hpp`](../../../sdk/include/t3sdk/unreal.hpp)'s comment
on `FName` for why.

`ObjectCount`/`ObjectAt` walk the whole object table instead, including free
slots (`NULL`). Combined with `IsA`, that is how you find every object of a
class rather than one specific instance:

```cpp
#include <t3sdk/t3sdk.h>

#include <cstring>

namespace {

const T3SdkApi* api = nullptr;
T3Object* playerControllerClass = nullptr;
bool reported = false;

void T3SDK_CALL OnFrame(void*) {
    if (!api->EngineReady() || reported) {
        return;
    }
    if (!playerControllerClass) {
        playerControllerClass = api->FindObject("Class", "Engine.PlayerController");
        if (!playerControllerClass) {
            return;  // classes are not all loaded on the very first ready frame
        }
    }
    for (int i = 0, n = api->ObjectCount(); i < n; ++i) {
        T3Object* object = api->ObjectAt(i);
        if (!object || !api->IsA(object, playerControllerClass)) {
            continue;
        }
        char name[128];
        api->ObjectName(object, name, sizeof(name));
        if (strncmp(name, "Default", 7) == 0) {
            continue;  // the class's own template instance, not a real one
        }
        char path[256];
        api->ObjectPathName(object, path, sizeof(path));
        api->Log("player controller: %s", path);
        reported = true;
        break;
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

`IsA` matches the object's own class or anything it derives from. Every
class also has a default object (its own template instance), which is why
the example above skips names starting with `Default` —
[`sdk/mods/hello`](../../../sdk/mods/hello/hello.cpp) does the same to find
"the" player controller rather than its class default.

## Read an object's name, path and class

- `ObjectName`/`ObjectPathName` write into a buffer you own and return the
  *full* length, like `snprintf` — call with `NULL`/`0` first to size a
  buffer, the same idiom [The mod lifecycle](../lifecycle.md) shows.
- `ObjectClass(object)` and `ObjectOuter(object)` walk up: an object's class,
  or the object (a package, usually) it is nested in. Walking `ObjectOuter`
  repeatedly reaches the same chain `ObjectPathName` prints, one segment at a
  time.

## Finding a path to search for

Press `T3SDK.ini`'s `DumpObjectsKey` (F10 by default) in game to write every
live object's class and path to `T3SDK_objects.txt`, next to `T3SDK.log`.
Skimming that file is usually faster than guessing a path to pass to
`FindObject`. See [SDK use and settings](../../sdk.md).

## Advanced: reading fields directly with unreal.hpp

The C API above is stable across engine internals. `unreal.hpp` additionally
exposes the real `UObject` layout for C++ mods that need a field the C API
has no accessor for. `T3Object` and `t3::UObject` are the same type, so no
cast is needed:

```cpp
#include <t3sdk/t3sdk.h>
#include <t3sdk/unreal.hpp>

namespace {

const T3SdkApi* api = nullptr;

void LogRawName(t3::UObject* object) {
    char text[64];
    api->NameToString(object->Name.Value, text, sizeof(text));
    api->Log("raw name: %s (index %u, number %u)", text, object->Name.Index(), object->Name.Number());
}

void T3SDK_CALL OnFrame(void*) {
    static bool done = false;
    if (!api->EngineReady() || done) {
        return;
    }
    done = true;
    if (t3::UObject* actor = api->FindObject("Class", "Engine.Actor")) {
        LogRawName(actor);
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

Of the fields `unreal.hpp` declares, `Outer`, `Name`, `Class` and a class's
`SuperField` are verified, and T3SDK re-detects `Outer` and `SuperField` at
start-up. The rest, and every fixed address it names, are specific to the
one supported build, which T3SDK checks before any mod loads (see
[Engine internals](../../engine.md)). Prefer the C API above unless you
specifically need a field it does not expose.

## Watch out for

- Object pointers are only good while `EngineReady()` holds. The engine can
  free objects once the game starts exiting. A level change restarts the
  game's process, so nothing carries over from one level to the next.
- `FindObject` and the enumeration loop are both linear scans (a few
  thousand objects even at the main menu; see
  [Engine internals](../../engine.md) for a sample count). Cheap enough once
  per "engine ready" transition, or every few seconds; avoid repeating a full
  scan on every single frame.
- `FindObject("Class", ...)` does the same linear search every time it is
  called. Cache the class pointer, as the examples above do, instead of
  calling it again each frame.

## Reference

- [Mod API reference](../../reference/api.md): the engine objects section.
- [Engine internals](../../engine.md): verified and static evidence for
  `UObject`'s layout and the fixed addresses `unreal.hpp` uses.
