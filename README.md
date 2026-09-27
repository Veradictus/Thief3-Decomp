# Thief: Deadly Shadows modding SDK

[![Discord: join the Taffer Tavern](https://img.shields.io/badge/Discord-Join%20the%20Taffer%20Tavern-5865F2?style=for-the-badge&logo=discord&logoColor=white)](https://discord.gg/hdAXH73tEG)

**T3SDK** is a modding SDK for **Thief: Deadly Shadows** (Ion Storm, 2004), PC.
It loads into your installed copy of the game, gives mods access to the engine
(objects, names, the engine log, function hooks) and fixes the PC version's
display problems. The goal is mods as large as multiplayer. The repository
also holds the reverse-engineering workbench used to find what the SDK hooks.

## Buy the damn game

**BUY THE DAMN GAME. IT'S WORTH IT.**

And while you're at it, **buy the whole classic trilogy**:
[*Thief Gold*](https://store.steampowered.com/app/211600/),
[*Thief II: The Metal Age*](https://store.steampowered.com/app/211740/) and
[*Thief: Deadly Shadows*](https://store.steampowered.com/app/6980/). They're on
Steam, and they're on sale about half the time, so the lot costs less than a
fence would pay Garrett for a single candlestick.

Loved them? **Leave the classics a glowing review on Steam.** They've earned
it, and it helps the next taffer find them.

As for *Thief* (2014): we don't talk about *Thief* (2014). Its Garrett isn't
even voiced by Stephen Russell. If you've played it, you already know what to
write in your review. Honesty is a virtue, even among thieves.

Stealing is Garrett's job, not yours. Don't pirate the game, and don't share
its files, with this project or with anyone else. Only a taffer would.

T3SDK is not the game and contains none of it: no game code, no assets,
nothing you could play. It modifies a copy you own, in memory, while it runs.
Every copy sold tells whoever owns the series today that people still play
these games and care about them, and paying for the games we mod is how we
support the developers who make them.

The SDK supports the Steam release of Thief: Deadly Shadows (patch 1.1):
<https://store.steampowered.com/app/6980/>. Other releases are detected and
left untouched.

## Legal

- T3SDK is a fan project. It is not affiliated with or endorsed by Ion Storm,
  Eidos Interactive or the current owners of the Thief series. *Thief* and
  *Thief: Deadly Shadows* are trademarks of their respective owners and are
  used here only to name the game this software works with.
- The repository holds work written by its contributors: the SDK, the
  launcher, the tools, notes on how the game works (addresses, data layouts,
  file formats) so that mods can interoperate with it, and a matching
  decompilation: C++ source that the game's original compiler turns into the
  same machine code. It contains no files from the game, no game assets, no
  disassembly and no raw decompiler output, and the libraries the game links
  (Microsoft's runtime, D3DX, Havok) are not decompiled.
- The tools work on your own installed copy. What they produce from it
  (Ghidra databases, split objects, decompiler output, extracted assets) stays
  on your machine in ignored folders (`orig/`, `ghidra/`, `build/`). Don't
  commit or redistribute any of it; extracted assets are for your own modding.
- T3SDK does not circumvent copy protection and does not touch DRM components.
  On a Steam install, `tools/sdk.py run` starts the game through Steam, as the
  Play button does.
- The SDK changes the game only in memory while it runs. `deploy` adds its own
  files to the game's `System/` folder, and `undeploy` removes exactly those.
- The software is provided as is, without warranty of any kind. Back up your
  saves before modding.

## Using the SDK

See [docs/sdk.md](docs/sdk.md) for the settings, the built-in fixes, the tools
and the mod API's lifecycle and threading rules.

Requires Windows, Python 3.10+, and Visual Studio 2022 or newer with
"Desktop development with C++" (the SDK is built for 32-bit x86, like the game).

```sh
python -m venv .venv
.venv/Scripts/pip install -r requirements.txt

.venv/Scripts/python tools/sdk.py build     # dinput8.dll + example mod into build/sdk/bin/
.venv/Scripts/python tools/sdk.py deploy    # copy into the game's System/ folder
.venv/Scripts/python tools/sdk.py run       # start the game (through Steam)
.venv/Scripts/python tools/sdk.py log       # show System/T3SDK.log
.venv/Scripts/python tools/sdk.py undeploy  # remove everything deploy installed
```

The game folder is found through the registry entry the game's installer
writes. Pass `--game-dir` to override it.

The SDK installs itself as `System/dinput8.dll`, which the game loads at
startup, and forwards DirectInput to the real system DLL. It does not replace
`d3d8.dll`, so it coexists with Sneaky Upgrade's Direct3D wrappers. Settings
live in `System/T3SDK.ini`. Besides the mod API, it fixes the PC version's
display: the monitor's native resolution, a borderless window instead of
exclusive fullscreen (alt-tab and screenshots work), menus laid out for
widescreen, and skipping the start-up logo movies.

## The launcher

[`launcher/`](launcher/) is a desktop app (Tauri) that puts all of this behind
buttons: it finds the game, Godot and Python, installs T3SDK, starts the game,
switches mods on and off, edits `T3SDK.ini`, and takes a map through export,
editing in Godot, repacking and installing (with the original backed up).
See [docs/launcher.md](docs/launcher.md).

```sh
cd launcher && npm install && npm run tauri dev
```

## Writing a mod

A mod is a 32-bit DLL in `System/mods/` that exports `T3Mod_Init` and receives
the API table from [sdk/include/t3sdk/t3sdk.h](sdk/include/t3sdk/t3sdk.h):

```c
#include <t3sdk/t3sdk.h>

static const T3SdkApi* api;

static void T3SDK_CALL OnFrame(void* user) {
    if (api->EngineReady()) {
        /* read objects: api->ObjectCount(), api->FindObject("Class", "Engine.Actor"), ... */
    }
}

T3SDK_EXPORT int T3SDK_CALL T3Mod_Init(const T3SdkApi* sdk) {
    api = sdk;
    api->AddFrameCallback(OnFrame, NULL);
    api->Log("loaded");
    return 0;
}
```

`T3Mod_Init` runs before the engine starts, so do engine work from callbacks
once `EngineReady()` is true. [sdk/mods/hello](sdk/mods/hello/hello.cpp) is a
complete example, and [sdk/include/t3sdk/unreal.hpp](sdk/include/t3sdk/unreal.hpp)
has the engine's memory layouts for direct access. To build a mod with the SDK,
add a folder under `sdk/mods/` and list it in `sdk/CMakeLists.txt`.

## Maps and assets in Godot

`tools/assets/` converts the maps and assets of your installed game into a
Godot 4.7 project in `build/assets/godot/`: textured static meshes, the level
geometry, lights, and every actor with its gameplay properties. The project
opens on a map picker, and each map gets a fly camera and an actor inspector.
It is the groundwork for a map editor. The formats, the tools and the viewer's
controls are described in [docs/assets.md](docs/assets.md).

```sh
.venv/Scripts/python tools/assets/t3map.py --all    # export every map (about 790 MB)
godot --path build/assets/godot                     # open the viewer
```

What the tools extract from your copy is for your own modding: don't share it.

## Reverse-engineering workbench and matching decompilation

What the SDK hooks is found here, and the game is being decompiled function by
function into C++ that compiles back to the same bytes (a matching
decompilation, in `src/`). [docs/engine.md](docs/engine.md) collects the
engine addresses and layouts with their evidence, and
[docs/target.md](docs/target.md) describes the binary. Everything below runs on
your own copy of `T3Main.exe` and writes its results into ignored folders.

- **Ghidra**: `tools/ghidra_headless.py bootstrap` builds an analysed database
  in `ghidra/` (about 12 minutes; open `ghidra/T3Main.gpr` in the GUI).
  `tools/ghidra_headless.py script tools/ghidra/Decompile.java <addr>` prints
  the decompilation of a function; `refs:<addr>` prints the functions that
  reference an address.
- **Symbols**: `config/PC_20040610/symbols.txt` lists every function by address
  (dtk format) and is where names are recorded as they are identified;
  `tools/ghidra_headless.py names` applies them to the Ghidra database.
- **Split and diff**: `configure.py` plus `ninja` split `T3Main.exe` into
  objects with [delink](https://github.com/dbalatoni13/delink) and compare
  them with [objdiff](https://github.com/encounter/objdiff) against code
  compiled with the game's own compiler (MSVC 7.1), to check how a function was
  compiled. It needs `msvcr71.dll` and `msvcp71.dll`
  (`configure.py --msvc-runtime <folder>`), which many games from 2003-2006
  ship with. On Linux and macOS the compiler runs through
  [wibo](https://github.com/decompals/wibo) instead.
- **Matching**: `tools/agent/` is the per-function loop used by people and AI
  agents alike (claim a function, get its context, try a candidate, pass the
  strict gate); see [docs/matching.md](docs/matching.md). Progress is published
  on [decomp.dev](https://decomp.dev) by CI
  ([docs/decomp-dev.md](docs/decomp-dev.md)).

## Contributing

Questions, ideas, or want to help? Come to the
[Taffer Tavern on Discord](https://discord.gg/hdAXH73tEG).

Read [CONTRIBUTING.md](CONTRIBUTING.md) first. Commit messages follow
Conventional Commits, and there are hard rules about what may enter the
repository.

## Layout

```
sdk/                 the SDK: loader (dinput8.dll), public headers, example mods, MinHook
launcher/            the desktop launcher (Tauri: Rust backend, Svelte UI)
tools/sdk.py         build / deploy / run / drive the SDK
tools/assets/        map and asset export to Godot, and the Godot map viewer
tools/ghidra/        Ghidra scripts (export, names, decompile, disassemble)
tools/agent/         the matching loop: work queue, context, try, accept, integrate
tools/               split/diff pipeline and binary tools
src/, include/       the matching decompilation
config/PC_20040610/  symbols.txt, splits.txt
docs/                engine notes, SDK guide, target analysis, current status
orig/PC_20040610/    your copy of T3Main.exe for the workbench (never committed)
```
