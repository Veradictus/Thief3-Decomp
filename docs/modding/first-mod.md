# Your first mod

A T3SDK mod is a 32-bit Windows DLL that exports `T3Mod_Init`. T3SDK loads it
into the game and hands it a table of functions, the
[mod API](../reference/api.md). This page goes from nothing to a `.t3mod`
package that the launcher installs.

## What you need

- Windows with Visual Studio 2022 or newer and its "Desktop development with
  C++" workload, which brings the MSVC compiler for x86 and CMake. Any
  compiler that makes 32-bit Windows DLLs will do, but the template uses
  CMake and MSVC.
- Python 3.10 or newer, for the packaging tool.
- The game with T3SDK installed, to test the mod.
- A GitHub account, if you want the template's release workflow.

## Start from the template

[`templates/mod/`](../../templates/mod/) in this repository is a starter
project:

- CMake builds the DLL against the SDK's headers;
- it writes the package manifest, `mod.json`, from the CMake project's
  version;
- it packs the DLL and the manifest as `<id>-<version>.t3mod`;
- its GitHub workflow builds the mod and attaches the package to a GitHub
  release.

Copy the folder into a repository of your own and follow its README: it
says where to set the mod's id, name and version, and how the build finds
the SDK headers.

## The code

A mod that logs a line once the engine is up:

```cpp
#include <t3sdk/t3sdk.h>

static const T3SdkApi* api;
static bool announced;

static void T3SDK_CALL OnFrame(void*) {
    if (announced) {
        return;
    }
    announced = true;
    T3Object* actor = api->FindObject("Class", "Engine.Actor");
    api->Log("engine up: %d object slots, Engine.Actor %s", api->ObjectCount(), actor ? "found" : "missing");
}

T3SDK_EXPORT int T3SDK_CALL T3Mod_Init(const T3SdkApi* sdk) {
    if (sdk->version < T3SDK_API_VERSION) {
        return 1;  // T3SDK is older than the headers this mod was built with
    }
    api = sdk;
    api->AddFrameCallback(OnFrame, nullptr);
    api->Log("waiting for the engine");
    return 0;
}
```

- `T3SDK_EXPORT` exports the function under its plain C name, and
  `T3SDK_CALL` is the calling convention of every function in the API.
- `T3Mod_Init` runs before the engine exists. Keep the API pointer, register
  callbacks, and return 0 to stay loaded. Any other value unloads the mod.
- Frame callbacks run on the game's main thread, once per frame, while the
  engine is up. That is where engine objects can be used.
- `api->Log` writes a line to `System\T3SDK.log`, tagged with your mod's name.

[The mod lifecycle](lifecycle.md) explains when each part runs.
[sdk/mods/hello](../../sdk/mods/hello/hello.cpp) is a longer example: it also
listens to the engine's log and walks the object table.

## Build and try it

1. Build the template with CMake (its README has the commands). The result
   is `<id>-<version>.t3mod`.
2. Drag the package onto the launcher, and turn the mod on in the **Mods**
   page.
3. Start the game, then open `T3SDK.log` (the **Play** page shows its end).
   Look for `mod <id> loaded` and your own lines.

To try a change quickly, you can also copy the DLL straight into the game's
`System\mods` folder. T3SDK loads such loose DLLs after the packaged mods.
Delete it again when you are done.

## Release it

The template's workflow builds the package and attaches it to a GitHub
release; its README says how to start one. Then
[add it to the mod index](publishing.md) so that it shows in the launcher's
mod browser.

## Without the template

- **In this repository**: add a folder under `sdk/mods/` and list it in
  `sdk/CMakeLists.txt`. `tools/sdk.py build` then builds it with the SDK (see
  [SDK settings and tools](../sdk.md)). Pack it with
  [`tools/t3mod.py`](packaging.md).
- **Any other build system**: make a 32-bit DLL, include
  [`sdk/include/t3sdk/t3sdk.h`](../../sdk/include/t3sdk/t3sdk.h), and export
  `T3Mod_Init` as shown above. Link the C runtime statically (`/MT` with
  MSVC), so that the mod needs no Visual C++ runtime in the game folder.
