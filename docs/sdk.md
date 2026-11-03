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
copies nothing. Settings files that exist (`T3SDK.ini`, a mod's `.ini`) are
the player's and are never overwritten; a fix mod the launcher switched off
(in `System/mods/disabled/`) is updated there, so it stays off; and files an
earlier deploy installed that the build no longer has are removed.
`undeploy` removes only files in the manifest, wherever the launcher's switch
moved them.

## Settings and built-in fixes

`System/T3SDK.ini` (the generated file documents every key):

| Section | Key | Default | Effect |
|---|---|---|---|
| `T3SDK` | `Console` | 0 | show a console with the live log |
| | `EngineLog` | 1 | copy the engine's own log lines into `T3SDK.log` |
| | `DumpObjectsKey` | `0x79` (F10) | key that writes every live object to `T3SDK_objects.txt`; 0 = off |
| | `DumpReflectionDelay` | 0 | seconds after the engine is up to write its classes, functions, properties and native table to `T3SDK_reflection.txt`, once, for the decompilation's naming (docs/engine.md, "Script natives"); 0 = off |
| | `MenuVersionLabel` | 1 | append `[Modded - T3SDK <version>]` to the main menu's version line |
| | `MenuInputTrace` | 0 | log main-menu and popup input events |
| `Fixes` | `SkipIntros` | 1 | skip the logo movies at start-up |
| `Display` | `NativeResolutions` | 1 | offer the monitor's own modes in Options; the top entry is native |
| | `Borderless` | 1 | a borderless window instead of exclusive fullscreen (alt-tab, other monitors, screenshots); it keeps the game's `A8R8G8B8` back buffer where the adapter allows, since some lighting passes use its alpha. With 0, exclusive fullscreen runs at the desktop's refresh rate (Direct3D 8's "default" may pick 60 Hz on a faster monitor) |
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
  it gives up after 20 seconds. Exclusive fullscreen gets the curtain too: there
  the restart switched the monitor back to the desktop and left a window that
  did not answer until the new game had its device.
- **Keeping running, and coming back.** On losing the focus the game pauses,
  releases the mouse and keyboard (DirectInput) and marks itself inactive; the
  SDK undoes the pause and the mark so it keeps running. On getting the focus
  back the game takes the mouse and keyboard again only when it is marked
  inactive, so the SDK marks it so just before.

`T3SDK.log` also receives a crash report for the first faults in the process
(access violations and the like): the location as `T3Main.exe+offset`, the
registers and the code addresses on the stack. The game then handles the fault
as it would without the SDK.

## Writing a mod

Build a 32-bit DLL that exports `T3Mod_Init` using the C API in
[`sdk/include/t3sdk/t3sdk.h`](../sdk/include/t3sdk/t3sdk.h). Mods are loaded
from `System/mods/` before the engine starts, in two groups:

1. **Packages**: a `.t3mod` ([mods.md](mods.md)) that the launcher installed
   lives in `System/mods/<id>/`, and the launcher lists its DLL as
   `<id>/<dll>` in `System/mods/load-order.txt`. The SDK loads those lines
   top to bottom, skipping blank lines and `#` comments, and refuses (with a
   log line) a line with an absolute path or `..`. Each DLL is loaded with
   `LoadLibraryExW(..., LOAD_WITH_ALTERED_SEARCH_PATH)`, so helper DLLs next
   to it are found.
2. **Loose DLLs**: every `System/mods/*.dll` not loaded yet, in filename
   order. The launcher switches these off by moving them to
   `System/mods/disabled/`.

A mod's name in `T3SDK.log` and crash reports is its folder name (a loose
DLL's: its file name). Without a `load-order.txt` only loose DLLs load, as
before packages existed. For a quick test, drop the DLL into `System/mods/`;
to share it, pack it (below).
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

### Game settings and file overrides (API version 2)

Check `api->version >= 2` (or `api->size`) before using these.

- **`SetConfigValue(file, section, key, value)`** answers one of the game's
  INI settings (`Default.ini`, `T3UI.ini`, ...) with `value`. Every bool,
  int, float and string the game reads through its Config layer goes through
  `Config::Find`, which the SDK hooks, so this works for any of them. `file`
  NULL matches any INI; `value` NULL removes the mod's override. Call it from
  `T3Mod_Init` so the game's start-up reads see it.
- **`AddConfigCallback(callback, user)`** sees every lookup with the value
  found so far (NULL for a missing key) and may return other text. Set
  values apply first, then callbacks in registration order; between mods,
  the one loaded later wins. Lookups can come from any thread.
- **`AddFileRoot(dir)`** adds a folder that mirrors the game folder (a
  relative `dir` is relative to the mod's own folder). When the game opens a
  file under `<game>/` for reading, or checks that it exists, and
  `<dir>/<same path>` exists, it gets that file instead; the folder added
  last wins. The install is never changed. Limits: directory listings are
  not merged (a file the game only finds by listing a folder must exist in
  the game folder too), and resources packed in `.ibt` bundles are not
  reached, only loose files.
- **`AddCodeHook(address, callback, user)`** runs `callback` whenever the
  game reaches `address`, at any instruction (CreateHook only takes a
  function's start), with the registers in a `T3Registers` the callback may
  change. This is how a fix goes into the middle of a function: read a
  value the game just computed, or change it before the next instruction
  uses it. The 5 bytes at `address` are moved by MinHook, so they must not
  contain a jump target. A callback that raises an exception is disabled and
  the game's registers are left as they were.

### Mods in this repository

All but `hello`, `save-trace` and `frame-profile` make up T3SDK's fix pack: they build into
`bin/mods/`, ship with a release, and **Install T3SDK** puts them into
`System\mods`. The launcher's Play page switches them under Game fixes;
switching one off moves it to `System\mods\disabled`, and an update of
T3SDK keeps it there. An update also keeps every settings file that already
exists (`T3SDK.ini`, a mod's `.ini`). `hello` is an example to read, and
`save-trace` and `frame-profile` are development tools: they build into
`examples/` and are not installed.

| Mod | What it does | Settings |
|---|---|---|
| [`blackjack-first`](../sdk/mods/blackjack-first/blackjack_first.cpp) | Attack with no weapon in hand draws the blackjack instead of the dagger (`"GarrettDagger"` becomes `"GarrettBlackjack"` at `0x10B26213`) | none |
| [`difficulty-fixes`](../sdk/mods/difficulty-fixes/difficulty.cpp) | Missions play at the chosen difficulty (the AI multipliers are loaded on every level load, and before the game scales the AI's hitpoints, `0x10AB7530`, which it otherwise does with the previous ones), and the Enter/Restart Mission menus preselect the difficulty being played ([engine.md](engine.md#difficulty)) | `difficulty-fixes.ini`: `ApplyOnMissionLoad`, `KeepInMissionMenus` |
| [`dotted-paths`](../sdk/mods/dotted-paths/dotted_paths.cpp) | The game runs from a folder whose path has a dot: `strrchr(path, '.')` (the CRT's, `0x10D1EF20`) only finds a dot after the last path separator | none |
| [`end-mission`](../sdk/mods/end-mission/end_mission.cpp) | Shift+Ctrl+Alt+End ends the current mission as if its exit was reached (`FindExitMissionInfo`, then `OpenMissionCompleteWindow`); missions only, not city sections | `end-mission.ini`: `Keys` |
| [`first-person-death`](../sdk/mods/first-person-death/first_person_death.cpp) | Dying keeps the first-person view: a copy of the installed `T3Camera.ini` with `DeathCam` inheriting from `FirstPerson`, served through `AddFileRoot`; off by default | `first-person-death.ini`: `Enabled` |
| [`hello`](../sdk/mods/hello/hello.cpp) | API walkthrough: logs objects and log categories | none |
| [`frame-profile`](../sdk/mods/frame-profile/frame_profile.cpp) | Development tool: times each frame (the engine tick, the Havok physics step within it, and presenting plus the rest of the main loop) to `frame-profile.csv`, with 10-second summaries in `T3SDK.log` | none |
| [`save-trace`](../sdk/mods/save-trace/save_trace.cpp) | Development tool: logs how a level is saved and loaded (archive positions, the gamesys object table's size, the files opened), to compare an edited map with the original ([assets.md](assets.md#the-level-object-mylevel-class-level)) | none |
| [`hud-tweaks`](../sdk/mods/hud-tweaks/hud_tweaks.cpp) | HUD changes through `T3UI.ini` values: junk items stay lit instead of flashing (on), no "nothing equipped" texts (off), the health bar stays on screen (off), no lockpicking HUD (off), books over the paused game instead of black (off) | `hud-tweaks.ini`: `SteadyJunkItem`, `HideEmptyHands`, `HealthAlwaysShown`, `HideLockpickHud`, `WorldBehindBooks` |
| [`loading-tweaks`](../sdk/mods/loading-tweaks/loading_tweaks.cpp) | Faster loading: loading-screen redraws (each one a presented frame) at least 20 ms apart unless forced; hold Ctrl to stop on the current loading screen and read it | `loading-tweaks.ini`: `MinRedrawMs`, `HoldKeys` |
| [`player-tweaks`](../sdk/mods/player-tweaks/player_tweaks.cpp) | No breathing sway while idle (the idle animations of `T3PlayerAnims.ini` get `Speed` 0) and a gravity multiplier (`[Physics] WorldGravityZ`, `[PointPhysics] Gravity`); off by default | `player-tweaks.ini`: `StillIdle`, `Gravity` |
| [`quicksave-cycle`](../sdk/mods/quicksave-cycle/quicksave_cycle.cpp) | Quick save takes turns between several saves ("Quick Save 1", "Quick Save 2", ...) and quick load loads the newest; off by default (it writes extra save games) | `quicksave-cycle.ini`: `Enabled`, `Count` |
| [`steady-view`](../sdk/mods/steady-view/steady_view.cpp) | A steadier first-person view. The eye stays at a resting spot in front of Garrett's view instead of riding the "Camera Attach" bone's animation (`GetCameraTargetLocation`, `0x10B21830`): its height follows his stance slowly on the ground and holds in the air; its place in front of him is learned while he stands (the bone leans 6 units further forward while he moves); one-frame swings of the bone are ignored. On a ladder or a rope (`bUpdatePhysHeight` clear and `bNoiseEnabled` set) the game's eye takes over again, with only the climb's steps eased. Every caller (camera, bow aim and arrow, melee sweep, camera fade) gets the same eye; only the camera's call (return `0x10AC271A`) moves the smoothing on. In the air the eye follows the physics body's own vertical speed (Garrett's position only chases it at 64 units a second); a jump of his height on the ground (a landing, a stair step) is eased. The body faces the view at once when he moves (turn rate `0x10E793FC`, 302 degrees a second in the game), and the near plane moves from 1.0 to 0.5 so held items do not cut into the view ([engine.md](engine.md#first-person-camera)). `[Debug] TraceCamera=1` writes every camera update to `steady-view-trace.csv` | `steady-view.ini`: `Smoothing`, `HeadBob`, `LandingSmoothing`, `BodyTurnSpeed`, `NearClip` |
| [`unstick`](../sdk/mods/unstick/unstick.cpp) | A key combination (Shift+Ctrl+Enter) frees Garrett when he is stuck floating or in the floor: it posts the game's event `0x7F` | `unstick.ini`: `Keys` |
| [`widescreen-fov`](../sdk/mods/widescreen-fov/fov.cpp) | Hor+: widens the cameras' FOV on screens wider than 4:3, and sets the player's FOV ([engine.md](engine.md#gamesys-properties)) | `widescreen-fov.ini`: `HorPlus`, `PlayerFOV`, `LogReads` |
| [`zone-tweaks`](../sdk/mods/zone-tweaks/zone_tweaks.cpp) | Fog distance and ambient light in every level: scales each zone actor's `DistanceFogStart`/`End` and `AmbientBrightness` once, when it appears | `zone-tweaks.ini`: `FogDistance`, `AmbientLight` |

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
