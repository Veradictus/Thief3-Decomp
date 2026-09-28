# Configuration

The game's own INI files and the settings in them. This covers vanilla
configuration; T3SDK's own settings (`T3SDK.ini`) are documented in full in
[sdk.md](../sdk.md), and this page notes only where T3SDK overrides a
vanilla setting.

## The config layer

Ion Storm's engine reads its INI files through its own singleton
(`Config::Instance`, looked up by section and key: `GetBool`, `GetFloat`,
`GetString`), not through stock Unreal's `GConfig`. A key can carry a
platform suffix that is tried before the plain key: `__p` (PC), `__x`
(Xbox), `__t` (Thief) — for example `VersionWindow__p=VersionText` overrides
plain `VersionWindow` on PC specifically. See [engine.md](../engine.md) for
the addresses.

## The INI files

All of these live in `System/`, except `options.ini` (see below). Roles
below are confirmed where a linked page has the evidence; the rest are not
known beyond what the file's own name suggests.

| File | Governs |
|---|---|
| `DEFAULT.INI` | Default settings; confirmed to suppress `Dev*` log categories (see [engine.md](../engine.md)'s Logging section), and presumably much more. |
| `T3UI.ini` | Menu and popup window layout (see [display.md](display.md)). |
| `T3UILights.ini`, `T3ItemGrid.ini`, `T3UISoup.ini` | By name, layout for specific UI screens (lighting-related menus, inventory grids, and shared UI elements). |
| `T3Hud.ini` | The in-game HUD's own, separate layout (see [display.md](display.md)). |
| `T3Camera.ini` | By name, camera behaviour. |
| `T3PhysicsSound.ini` | By name, footstep and impact sound selection by surface. |
| `T3PlayerAnims.ini` | By name, player animation selection. |
| `T3AutoTag.ini`, `MotionTags.ini` | By name, motion-tag data alongside `Content/T3/TagDatabase` (see [files.md](files.md)). |
| `T3InputMem.ini` | By name, input configuration; not otherwise examined. |
| `T3Rumble.ini` | By name, controller vibration. |
| `FacialExp.ini` | By name, facial expression data. |
| `reverbstyles.ini` | EAX reverb presets (see [architecture.md](architecture.md)). |
| `user.ini` (install root, not `System/`) | Three engine switches: `[BlockLoading] LoadFromResourceBlockFiles`, `[Source Control] UseSourceSafe` and `[Engine.Engine] UpdateGameSys`. The exe names the file; how it combines with the other files is not known yet. |
| `T3SDK.ini` | T3SDK's own settings; see [sdk.md](../sdk.md). Not a vanilla file. |

`options.ini` is different from the rest: it is written by the game itself,
under `<game folder>/save/SaveGames/User Options/options.ini` (see
[files.md](files.md)), and holds the player's saved audio/video choices,
below.

## options.ini and the Options table

Rather than named keys, `options.ini` stores the player's settings as a
flat array of integers, indexed by position against a fixed table of 21
names:

| Index | Name | Index | Name |
|---|---|---|---|
| 0 | Version | 11 | Resolution |
| 1 | Subtitles | 12 | ShadowDetail |
| 2 | InvertYAxis | 13 | Bloom |
| 3 | LookSpring | 14 | LightCutoff |
| 4 | Vibration | 15 | MultiSampling |
| 5 | SFXVolume | 16 | UseLowResTextures |
| 6 | MusicVolume | 17 | LOD |
| 7 | ControllerLayout | 18 | UseHWMixing |
| 8 | Brightness | 19 | UseEAX |
| 9 | VSynch | 20 | EAXMultipleEnvironments |
| 10 | AutoBowZoom | | |

`Options::Load`, `Save` and `SetDefaults` manage the file; `Get`/`Set` read
and write one entry by index. `Resolution` (index 11) is special-cased:
`Options::ApplyVideo` clamps it to 0–4 and steps down to a mode the graphics
adapter actually supports, indexing the five-entry resolution table below.
Each row on the in-game Audio/Video options screen (a slider, a checkbox or
a button) is driven from the same table by a shared refresh routine.

## Notable sections

- **`[Physics]`**: `PlayerControllerFPSrate` (60) caps the player physics
  controller's step size. `AIControllerFPSrate_Running` (30), `_Basic` (15),
  `_Minimal` (5) and `_Off` (2) are stored as 1/rate for the AI's
  controllers; how they are used is not known yet. See
  [architecture.md](architecture.md).
- **`[LoadingScreen]`**: the loading screen's logo and caption texture names
  and their positions and sizes, read by `LoadingScreen::LoadLayout`. See
  [display.md](display.md).
- **`[WindowManager]`**: `AssumedUIScreenWidth`/`Height` (640x480, the UI's
  design resolution) and the UI camera's field of view (95 degrees). See
  [display.md](display.md).
- **`[D3DDrv.D3DRenderDevice]`**: device-level switches such as
  `UseComputedRefreshRate` and `UseManualRefreshRate`, read while setting up
  a display mode.
- **`[Paths]`**: `DynamicTextures`, the folder `LoadingScreen::Begin` looks
  in for a per-map loading background (`<map>.dds`, falling back to
  `Loading1.dds` when there is none).
- **`[PCStartup]`**: `ShowIntroMovies`, which the retail game itself can set
  to skip the start-up logo movies (the list itself is
  `ShortIntroMovies`); T3SDK's `SkipIntros` fix instead hooks the function
  that plays them (see [engine.md](../engine.md)), independent of this key.
- **`[Flesh]`**: `Multisample`, read while setting up the backbuffer format.

## What T3SDK overrides

T3SDK does not edit these files; it intercepts a few values in memory. See
[sdk.md](../sdk.md) for the settings that control each:

- The five-entry resolution table (`NativeResolutions`) is rewritten from
  the monitor's own modes instead of the stock 640x480–1600x1200 list.
- `TimeManager`'s minimum frame step (`SmoothFrames`) is lowered from its
  compiled-in 0.01 s, independently of any INI key (see
  [runtime.md](runtime.md)).
- `Config::GetFloat` is intercepted for two things, both for
  `WidescreenUI`: `[WindowManager] AssumedUIScreenWidth`, answered with a
  widened value, and two `[KeyboardLayoutWindow]` ratios, scaled so the
  Inputs page's key table fits its 640-wide frame.
- `Window::PlacedPosition` is hooked, also for `WidescreenUI`, to move
  menu content into a centred 640-wide frame. See
  [display.md](display.md).
