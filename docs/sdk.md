# T3SDK use and mod API

T3SDK loads as `System/dinput8.dll` and is built for the game's 32-bit x86
process. Build on Windows with Python 3.10+, CMake, Ninja, and Visual Studio
2022 or newer with the MSVC x86 C++ tools. `tools/sdk.py` locates Visual Studio
through `vswhere`, configures CMake, and builds into `build/sdk/bin/`.

```powershell
.venv\Scripts\python tools\sdk.py build
.venv\Scripts\python tools\sdk.py build --config Debug
.venv\Scripts\python tools\sdk.py deploy
.venv\Scripts\python tools\sdk.py run            # through Steam; extra arguments go to the game
.venv\Scripts\python tools\sdk.py screenshot     # build/sdk/screenshot.png (-o path, --max-width)
.venv\Scripts\python tools\sdk.py click 0.5 0.75 # left click at a fraction of the game window
.venv\Scripts\python tools\sdk.py keys esc       # up/down/left/right/enter/esc/space/tab
.venv\Scripts\python tools\sdk.py close          # WM_CLOSE, then reports time and exit code
.venv\Scripts\python tools\sdk.py log
.venv\Scripts\python tools\sdk.py undeploy
```

`click` posts mouse messages to the game window, so the real cursor and focus
stay where they are; the main menu reacts to it. `keys` sends scan codes
through `SendInput`, which only reaches the game while it is the foreground
window, and stops as soon as it is not. `screenshot` works while the game runs
borderless (the default), not in exclusive fullscreen.

`--config` is a build option and follows `build`. `--game-dir` is a global
option and precedes the command, for example
`.venv\Scripts\python tools\sdk.py --game-dir "D:\Games\Thief 3" deploy`.
Without it, the tool uses `T3_GAME_DIR`, then the installer's `ION_ROOT`
registry value. The build re-runs CMake configuration each time, so changing
`--config` also updates an existing build directory.

Before copying files, deploy compares the game's `T3Main.exe` SHA-1 with
`40bf68a54246bcde2fb5fcbc75b94dc7c7f78305`. A different hash produces a
warning; the loader independently requires that hash along with the expected
PE timestamp, image size, and load base. If any runtime check fails, it logs
the reason and leaves the game unmodified by SDK hooks. The addresses in
[`engine.md`](engine.md) are for this exact executable.

The build also copies the public headers into `build/sdk/bin/include/t3sdk/`,
so `build/sdk/bin/` holds what the release's `T3SDK_<version>_x86.zip` holds.
Deploy copies DLL, PDB, and INI files from `build/sdk/bin/` into `System/` and
records the files it installed in `build/sdk/deployed.json` (under
`$T3SDK_BUILD_DIR/sdk/` when that is set, as the launcher does for its bundled
copy). It refuses to overwrite an existing file it does not own, and then
copies nothing, except that an existing `System/T3SDK.ini` that is not already
in the manifest is kept as the user's settings. `undeploy` removes only files
in the manifest.

## Settings and built-in fixes

`System/T3SDK.ini` (the generated file documents every key):

| Section | Key | Default | Effect |
|---|---|---|---|
| `T3SDK` | `Console` | 0 | show a console with the live log |
| | `EngineLog` | 1 | copy the engine's own log lines into `T3SDK.log` |
| | `DumpObjectsKey` | `0x79` (F10) | key that writes every live object to `T3SDK_objects.txt`; 0 = off |
| | `MenuVersionLabel` | 1 | append `[Modded - T3SDK <version>]` to the main menu's version line |
| | `MenuInputTrace` | 0 | log main-menu and popup input events |
| `Fixes` | `SkipIntros` | 1 | skip the logo movies at start-up |
| `Display` | `NativeResolutions` | 1 | offer the monitor's own modes in Options; the top entry is native |
| | `Borderless` | 1 | a borderless window instead of exclusive fullscreen (alt-tab, other monitors, screenshots) |
| | `WidescreenUI` | 1 | lay the UI out for the screen's aspect ratio: menus stay centered as a 4:3 frame, the HUD moves to the screen edges |
| | `UILayoutTrace` | 0 | log each UI window's placement once (for UI modding) |
| | `PauseInBackground` | 0 | pause while another window has the focus, as the game does on its own; 0 = a borderless game keeps running |
| | `SmoothFrames` | 1 | move the game world on every frame: the engine moves it only once 10 ms have passed, which looks choppy above 100 fps |
| | `MaxFPS` | 0 | highest frame rate; 0 = no limit |
| | `CursorScale` | 0 | size of the menu cursor in a borderless window: 0 = grow with the screen height (1x at 768 lines), else a fixed factor |
| | `FrameStats` | 0 | log frames per second and the time spent in `Present` every 10 seconds |

A borderless window also takes over what exclusive fullscreen did on its own:

- **VSync.** The game's VSynch option (Options > Audio/Video, on by default)
  presents once per monitor refresh; in a window through Direct3D 8's
  `COPY_VSYNC` swap effect (not with multisampling).
- **The cursor.** Direct3D imitates the game's 32-pixel hardware cursor in a
  window by rebuilding a Windows cursor on every call, and the game makes
  those calls every frame: it flickered, and it was tiny on large screens.
  The SDK shows one Windows cursor made from the game's image, scaled to the
  screen.
- **Focus.** The game window comes to the front when it starts, even when
  Steam or the game's launcher started it.
- **Level changes.** The game restarts for every level (New Game, each
  mission). The outgoing game draws the next level's loading screen; the SDK
  keeps it on the monitor (a helper process, `rundll32` running
  `dinput8.dll`'s `T3SDK_Curtain`) until the incoming game has drawn its own,
  then hands that game the foreground. Any click or key removes it early, and
  it gives up after 20 seconds.

`T3SDK.log` also receives a crash report for the first faults in the process
(access violations and the like): the location as `T3Main.exe+offset`, the
registers and the code addresses on the stack. The game then handles the fault
as it would without the SDK.

## Writing a mod

Build a 32-bit DLL that exports `T3Mod_Init` using the C API in
[`sdk/include/t3sdk/t3sdk.h`](../sdk/include/t3sdk/t3sdk.h). Put it in
`System/mods/`; mods are loaded in filename order before the engine starts.
`T3Mod_Init` should register callbacks and return zero on success. Use the
API's `version` and `size` fields when checking optional later API entries.
For example, initialization should save the API pointer and defer engine
access to a callback:

```c
static const T3SdkApi* api;
static void T3SDK_CALL OnFrame(void* user) {
    if (api->EngineReady()) {
        int slots = api->ObjectCount();
        /* inspect engine objects here */
    }
}
T3SDK_EXPORT int T3SDK_CALL T3Mod_Init(const T3SdkApi* sdk) {
    api = sdk;
    return api->AddFrameCallback(OnFrame, NULL);
}
```

The engine object functions are valid only after `EngineReady()` succeeds.

Frame callbacks run on the game's main thread once per message-loop pass.
Engine log callbacks run on whichever thread writes the log, so protect shared
state if those callbacks communicate with frame callbacks. The optional
`T3Mod_Shutdown` runs in reverse load order when the SDK observes game exit.
If initialization fails, the SDK removes callbacks registered by that DLL
before unloading it. The complete example is
[`sdk/mods/hello/hello.cpp`](../sdk/mods/hello/hello.cpp); register a mod's
CMake target in [`sdk/CMakeLists.txt`](../sdk/CMakeLists.txt).

A mod of its own, outside this repository, starts from
[`templates/mod/`](../templates/mod/): a CMake project (with presets for MSVC
x86) that builds against the SDK headers, from a checkout's `sdk/include` or
downloaded with the SDK release, whose zip has them under `include/t3sdk/`.
It writes `mod.json` from the project's version and packs
`<id>-<version>.t3mod` ([mods.md](mods.md)), and its GitHub workflow attaches
that package to a release for a version tag. CI builds the template against
`sdk/include` on every SDK change.

The public API is plain C and uses caller-owned buffers for returned text.
The optional C++ [`unreal.hpp`](../sdk/include/t3sdk/unreal.hpp) exposes engine
layouts and fixed addresses for advanced use; those addresses and direct
object-memory access are specific to the supported executable. The SDK does
not provide synchronization for engine objects or make arbitrary engine calls
safe from worker threads.
