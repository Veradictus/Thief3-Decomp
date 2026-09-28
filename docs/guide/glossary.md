# Glossary

Terms used across these docs, in alphabetical order. Each links to where it's
explained in full.

- **API version.** The version of the mod API (`T3SdkApi`) an installed
  T3SDK implements. The table only grows, so a mod can check `api->size`
  before using a member added later. See
  [The mod lifecycle](../modding/lifecycle.md#api-versions).
- **Archetype.** An UnrealScript class (named `D_<n>`) that gives a
  placeable thing its default properties. A map actor of that class inherits
  the archetype's gamesys values and stores only what it overrides;
  `T3Gamesys.t3u` holds about 2,300 of them. See
  [Game and engine: the gamesys property system](../game/gamesys.md).
- **Borderless window.** T3SDK's default display mode: a window with no
  border or title bar that covers the monitor, instead of the game's own
  exclusive fullscreen. Enables alt-tab, other monitors, screenshots, VSync
  in a window, and the level-change curtain (below). See
  [Settings explained](settings.md#display).
- **Code mod.** A `.t3mod` package with a DLL (`entry` in its manifest) that
  T3SDK loads into the game. Needs T3SDK installed, unlike a content pack
  (below). See [Mod packages](../mods.md).
- **Content pack.** A `.t3mod` package that ships files instead of code, or
  alongside it — textures, loading screens, even a whole map — rather than a
  DLL. See [Content and texture packs](../modding/content-packs.md).
- **Curtain (level-change curtain).** T3SDK's fix for the gap when the game
  restarts between levels: a helper process keeps the outgoing loading
  screen on the monitor until the new game's own is ready. New, and not yet
  tried in the actual game. See
  [Troubleshooting: display and performance](troubleshooting.md#display-and-performance).
- **decomp.dev.** The public dashboard that tracks how much of `T3Main.exe`
  has been matched, built from this repository by CI. See
  [decomp.dev reporting](../decomp-dev.md).
- **Flesh.** Ion Storm's own name for the early Unreal Engine 2 fork Thief:
  Deadly Shadows runs on. See [Assets and formats](../assets.md).
- **Frame callback.** A function a mod registers that T3SDK calls once per
  frame, on the game's main thread, from the point the engine is ready. See
  the cookbook's [every-frame recipe](../modding/cookbook/every-frame.md).
- **Gamesys.** Ion Storm's own property system, layered on top of Unreal's
  own tagged properties, that stores extra per-object data (AI, physics,
  interactions). The map editor can change scalar gamesys values on an
  actor. See [Game and engine: the gamesys property system](../game/gamesys.md).
- **Ghidra.** The disassembler and decompiler this project's reverse
  engineering runs on. See
  [Decomp handbook: reverse engineering](../decomp/reverse-engineering.md).
- **`.gmp`.** A map file, `Content/T3/Maps/<Level>.gmp`: one level's actors,
  BSP geometry, navigation data and gamesys property overrides, in Unreal's
  own package format. See [Assets and formats](../assets.md).
- **Hook.** Code that redirects one of `T3Main.exe`'s own functions to a
  mod's or T3SDK's own function first, with a trampoline back to the
  original. Every mod and T3SDK share one hook table, so a given function can
  only be hooked once. See [The mod lifecycle](../modding/lifecycle.md#hooks).
- **`.ibt`.** A bundle of a map's textures and other resources. Experimental
  texture packs rewrite these in place. See
  [Installing mods: texture packs](mods.md#texture-packs).
- **Load order.** The order T3SDK loads mod DLLs in, top to bottom
  (`System\mods\load-order.txt`); when two mods provide the same file, the
  one lower in the list wins. Drag mods to reorder them on the **Mods**
  page. See [Installing mods](mods.md#load-order).
- **Loose DLL.** A mod DLL dropped straight into `System\mods` without a
  package around it. It still loads, after every packaged mod, but has no
  manifest, so the launcher can't check its requirements or conflicts. See
  [Installing mods](mods.md#loose-dlls).
- **Manifest (`mod.json`).** The JSON file at the root of every `.t3mod`
  package: id, version, author, what it needs and conflicts with. The
  launcher goes by this, not by the file's name. See
  [Mod packages](../mods.md#modjson).
- **Map Studio.** The launcher's page for exporting a map to Godot, editing
  it there, and repacking, installing or restoring it in the game. See
  [The launcher: screens](../launcher.md#screens).
- **Matching decompilation.** Rewriting `T3Main.exe`'s functions as C++ that
  its original compiler turns into the same machine code, byte for byte.
  Public, unlike raw decompiler output. See
  [Decomp handbook](../decomp/index.md).
- **Mod index.** The list of published mods the launcher's mod browser
  reads, built from this repository's `modindex/` folder. It only lists
  mods; it doesn't host them. See
  [Publishing to the mod index](../modding/publishing.md).
- **Mod profile.** A saved set of mods — which ones are on, and in what
  order — that you can switch to in one step, for example a "Vanilla"
  profile with everything off. See [Installing mods](mods.md#profiles).
- **Sneaky Upgrade.** A popular third-party patch for this game, distributed
  separately from T3SDK. Its Direct3D wrappers and texture/material override
  folders coexist with T3SDK; see
  [Other mods and tools](compatibility.md#sneaky-upgrade-and-direct3d-wrappers).
- **`symbols.txt`.** This project's name database
  (`config/PC_20040610/symbols.txt`): every identified function and global,
  by address. See [Decomp handbook: naming](../decomp/naming.md).
- **T3Ed.** Ion Storm's own level editor for the game, released publicly in
  February 2005. Maps built from scratch still need it; T3SDK's own map
  editor only edits what's already in a map. See
  [Map editing](../modding/maps.md#sharing-maps) and
  [Assets and formats](../assets.md).
- **`T3SDK.ini`.** T3SDK's own settings file, next to `dinput8.dll` in the
  game's `System` folder. Edit it directly, or use the launcher's **SDK
  settings** page. See [Settings explained](settings.md).
- **`.t3mod`.** The file every mod ships as: a zip with a `mod.json`
  manifest at its root, holding code, content, or both. See
  [Mod packages](../mods.md).
- **`.t3u`.** A script package, `System/*.t3u`: compiled UnrealScript, and
  for `T3Gamesys.t3u`, the archetypes too. Unreal's own package format, like
  `.gmp` (above). See [Assets and formats](../assets.md).
- **Texture pack.** A content mod that replaces textures, either through
  Sneaky Upgrade's override folders or, experimentally, written straight
  into the game's `.ibt` bundles (above). See
  [Installing mods](mods.md#texture-packs).
- **TimeManager.** Ion Storm's own game clock: a singleton that brackets
  every frame and produces its game-time delta. Its 10 ms minimum step is
  what `SmoothFrames` changes. See
  [Game and engine: runtime](../game/runtime.md) and
  [Settings explained](settings.md#display).
- **UnrealScript.** Unreal Engine's own scripting language. The game's
  classes and archetypes are written in it and shipped compiled, inside
  `.t3u` packages (above). See [Game and engine: objects](../game/objects.md).
- **Unsupported build.** Any `T3Main.exe` that isn't the exact Steam patch
  1.1 build T3SDK checks for. T3SDK detects it, changes nothing, and lets the
  game run exactly as it would without T3SDK. See
  [Unsupported builds](troubleshooting.md#unsupported-builds).
- **VSync (VSynch).** The game's own Options > Audio/Video setting that
  paces frames to the monitor's refresh rate. In T3SDK's borderless window it
  now works there too, except together with MultiSampling. See
  [Settings explained](settings.md#display).
- **WidescreenUI.** The T3SDK fix that lays menus and the HUD out for the
  screen's own aspect ratio instead of stretching a 4:3 layout to fill it.
  See [Settings explained](settings.md#display).
