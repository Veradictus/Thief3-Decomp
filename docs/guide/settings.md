# Settings explained

Every setting T3SDK and the launcher have, in plain terms: what it does, its
default, and when you'd change it. For how the fixes work under the hood, see
[SDK settings and tools](../sdk.md#settings-and-built-in-fixes) and
[Engine internals](../engine.md).

## Changing settings

Two ways to change `System\T3SDK.ini`:

- The launcher's **SDK settings** page shows every key as a toggle, a key
  box, or a text field. Its list, order and descriptions come straight from
  the SDK's own `T3SDK.ini`, so a setting the SDK adds later shows up here
  without a launcher update. **Save** writes your changes into the file in
  place, keeping its comments; **Revert** discards them. If the file is
  missing (for example after copying just `dinput8.dll` in by hand), the page
  offers to create one with the defaults.
- Edit `System\T3SDK.ini` directly in a text editor. `1` turns a setting on,
  `0` off; a few (`DumpObjectsKey`, `MaxFPS`, `CursorScale`) take a number
  instead.

Either way, **changes take effect the next time the game starts**: T3SDK
reads the file once, at start-up, not while the game is running.

The launcher shows the `[T3SDK]` section as "General"; `[Fixes]` and
`[Display]` keep their names. This page is about what each setting does;
[Playing with T3SDK](playing.md) covers installing and removing the SDK
itself, and [Installing mods](mods.md) covers the mod loader.

## T3SDK's own settings

### General

The `[T3SDK]` section: the log, and a couple of things for mod authors.

| Setting | Default | What it does |
|---|---|---|
| `Console` | off | Opens a console window that mirrors `T3SDK.log` live, so you can watch it without leaving the game. Handy while reporting a problem or testing a mod; otherwise it's one more window on your desktop. |
| `EngineLog` | on | Copies the game's own log lines into `T3SDK.log` alongside T3SDK's own. Turn it off for a shorter, T3SDK-only log. |
| `DumpObjectsKey` | `0x79` (F10) | While the game has focus, this key writes every live engine object to `T3SDK_objects.txt`. It's for mod authors inspecting the object table; set it to `0` to turn the hotkey off, for example if a mod binds F10 to something else. |
| `MenuVersionLabel` | on | Adds `[Modded - T3SDK <version>]` to the main menu's version line, so you can see at a glance that T3SDK is active. Turn it off for an unmarked main menu. |
| `MenuInputTrace` | off | Logs main-menu and pop-up input events. A diagnostic switch for UI modding; leave it off unless someone helping with a menu problem asks you to turn it on. |

### Fixes

| Setting | Default | What it does |
|---|---|---|
| `SkipIntros` | on | Skips the Eidos, Ion Storm, copyright, nVidia and EAX logo movies at start-up, so the main menu appears sooner. Turn it off to see them, or to check the game's original start-up sequence. |

### Display

The biggest section, and the one most worth reading. A borderless window is
what most of the others build on.

| Setting | Default | What it does |
|---|---|---|
| `NativeResolutions` | on | Offers your monitor's own resolutions in Options > Audio/Video, with your native resolution as the top entry. Without it, the game only ever offers five fixed resolutions, 640x480 up to 1600x1200. |
| `Borderless` | on | Runs the game in a window with no border or title bar, sized to cover the monitor, instead of exclusive fullscreen. This is what lets you alt-tab, use other monitors and take screenshots with any normal tool, and it's what makes the VSynch-in-a-window fix, the scaled cursor and the level-change curtain (below, and see [Troubleshooting](troubleshooting.md#display-and-performance)) possible. Turn it off to go back to exclusive fullscreen; you'd lose all of those along with it. |
| `WidescreenUI` | on | Lays menus and the HUD out for your screen's own aspect ratio, instead of stretching the game's 4:3 layout to fill it: menus stay centred, and the HUD moves out to the screen edges. Turn it off to compare against the original stretched layout. |
| `UILayoutTrace` | off | Logs where every UI window is placed, once. For UI modding, not for play. |
| `PauseInBackground` | off | With the default (off), a borderless game keeps running when you switch to another window; set it to `1` to bring back the game's own habit of pausing the moment it loses focus. Either way, pausing yourself before you alt-tab away is the safer habit. |
| `SmoothFrames` | on | Moves the game world every frame. Left off, the engine's own clock only advances the world once 10 ms have passed, so above 100 fps the world and the camera move on only every second or third frame, which looks choppy however high the frame rate. **Not yet tried in the actual game**: if you notice odd behaviour in fast-moving things (physics, jumping, mantling, rope arrows) above 100 fps, turn it off and report it. |
| `MaxFPS` | `0` (no limit) | Caps the frame rate. Uncapped, the main menu has been measured between 200 and about 1,255 fps on one test machine, which is more work for your GPU than the screen can show. With VSynch on (below), the frame rate already follows your monitor; a cap is for when VSynch is off. **Not yet tried in the actual game.** |
| `CursorScale` | `0` (grows with screen height) | Sets the size of the menu cursor in the borderless window. `0` scales it with the screen (1x at 768 lines); a fixed number such as `1.5` overrides that. |
| `FrameStats` | off | Logs frames per second and the time spent presenting a frame, every 10 seconds. For reporting a performance problem, or curiosity. |

## The game's own Options

These live in the game's own **Options > Audio/Video** screen, not in
`T3SDK.ini`, but T3SDK changes what some of them do:

- **Resolution.** With `NativeResolutions` on (the default), this list is
  your monitor's own modes, with your native resolution as the highest
  entry. It's still the game's own option; T3SDK only replaces the five
  entries it would otherwise offer.
- **VSynch.** On by default in the game itself. In the borderless window,
  T3SDK now makes it present once per monitor refresh too, through Direct3D
  8's `COPY_VSYNC` swap effect — the same pacing exclusive fullscreen always
  had. This doesn't apply together with MultiSampling (below); with both on,
  the window presents as fast as it can, unpaced. **Not yet tried in the
  actual game.**
- **MultiSampling.** The game's anti-aliasing option. Switching it on turns
  off the VSynch-in-a-window pacing described above, for that combination.
- **Brightness.** T3SDK doesn't change what this does.

## The launcher's own settings

Separate from `T3SDK.ini`: these live in your own user profile
(`%APPDATA%\org.t3sdk.launcher\launcher.json`), not the game folder, and only
affect the launcher itself.

On the **Settings** page:

- **Paths**: the game folder, the T3SDK folder (the launcher's bundled copy,
  or a checkout), Python, Godot, the Godot project folder (default:
  `build\assets\godot` inside the T3SDK folder) and the saves folder
  (default: found automatically; see [Save backups](saves.md)). **Search
  again** re-detects all of them; each field also shows what it checked, for
  example that `T3Main.exe` is the supported build.
- **Mod index**: the URL the [Mods page's browser](mods.md#the-mod-browser)
  reads. Leave it empty to use the T3SDK project's own index
  (`https://veradictus.github.io/Thief3-Decomp/modindex/index.json`).
- **Updates**: **Check for updates at start-up** (at most once a day) and
  **Check now**. A build made without the update key — a development build,
  or one built from a fork — says so here instead, and links to the releases
  page. See the [FAQ](faq.md#why-isnt-the-launcher-code-signed) for why the
  installer itself still gets a Windows warning even when this works.
- **Collect logs** and **Report a problem** (also on the **Play** page): see
  [Troubleshooting](troubleshooting.md#collect-logs-and-report-a-problem).
- **Run setup again** re-opens the first-run setup screen, so you can
  re-check or change every path.

The **Saves** page has one setting of its own: **Back up before starting the
game** (off by default) makes a save backup, skipping it when nothing has
changed, every time you click Play. See [Save backups](saves.md).
