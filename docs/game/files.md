# The install and its files

The folder layout of a Thief: Deadly Shadows install, and what each part of
it is for. File **formats** (packages, block files, textures, ...) are
covered in [assets.md](../assets.md); this page is about where things live
and their role. Paths below are written as `<game folder>`.

## Top level

```
<game folder>/
├── Content/               game data (below)
├── System/                engine, script packages, executables, config (below)
├── save/                  save games and the Options table (below)
├── user.ini                three engine switches (block-file loading, source control, gamesys updates)
└── installscript.vdf       Steam's installer script; out of scope (see target.md)
```

## System/

`System/` holds the engine itself and everything it loads that is not level
content:

- **`T3Main.exe`**: the game. `runme.exe`, `t3.exe` and `Ion Launcher.exe`
  are launchers Steam and the engine itself use to start and restart it
  (see [runtime.md](runtime.md)); `testapp.exe` is left over from the
  retail release. All four are out of scope for this project (see
  [target.md](../target.md)).
- **Script packages** (`*.t3u`): `AICore`, `Core`, `Editor`, `Engine`,
  `Fire`, `T3AI`, `T3Game`, `T3Gamesys` and `T3Player` — nine in total. See
  [objects.md](objects.md).
- **Localised text** (`*.int`): Unreal's convention for English-language
  string tables, one per package that needs them (`Core.int`, `Engine.int`,
  `Window.int`, `WinDrv.int`, `D3DDrv.int`, `Editor.int`, `UnrealEd.int`,
  `Startup.int`, `T3UIText.int`, `t3uw.int`) — the game's on-screen text.
- **INI files**: the game's own settings and the UI/HUD layout. See
  [config.md](config.md) for the full list and what each governs.
- **Middleware DLLs**: `binkw32.dll` (Bink video) and `eax.dll` (EAX audio),
  both delay-loaded (see [target.md](../target.md)).
- **`Data/`**: small fallback and lookup resources loaded directly as loose
  files rather than from a block file — lighting lookup textures (falloff
  and attenuation gradients, a normalisation cube map) and the `_Missing`/
  `_Corrupt` placeholders the editor's tools substitute for resources that
  fail to load, in the editor's own loose formats (see
  [assets.md](../assets.md), section 4).
- **`mods/`**: present when [T3SDK](../sdk.md) is installed. Holds mod DLLs,
  the load order and the content-overlay bookkeeping described in
  [mods.md](../mods.md).
- T3SDK's own files when installed: `dinput8.dll` (the loader, see
  [sdk.md](../sdk.md)), `T3SDK.ini` and `T3SDK.log`.

## Content/T3/

Game content proper:

| Folder | Holds |
|---|---|
| `Maps/` | Every level's `.gmp` + `.ibt` pair, plus the shared `Kernel_*ALL.ibt` and `MainMenu_*ALL.ibt` bundles. See [levels.md](levels.md). |
| `UTX/` | Legacy Unreal texture packages (particles, the sky cube, HUD art), spanning several old engine versions. |
| `PCTextures/`, `Bitmaps/` | Loose textures: menu and loading-screen art, fonts. |
| `MatLib/` | `categories.txt`, the surface-category table materials index into for footstep and physics sounds (see [assets.md](../assets.md)); the materials themselves are baked into each level's `.ibt`. |
| `Sounds/` | Ion Storm's own sound metafiles (`SchemaMetafile_*.csc`), five in total, holding both the sound schema database and the embedded audio. |
| `VideoTextures/` | The game's videos (`.bik`, Bink), 23 in total: intro logos and cutscenes. |
| `Books/`, `Conversations/`, `LipsincData/`, `TagDatabase/`, `Flags/` | Readables, conversation trees, lip-sync data, motion tags and quest-flag data. None of these carry geometry. |

`DynamicallyLoaded` subfolders under `PCTextures` and `MatLib` are where
Sneaky Upgrade-style overlays and T3SDK content mods place loose
replacement textures and materials (see [assets.md](../assets.md) and
[mods.md](../mods.md)).

## save/

```
save/
├── SaveGames/
│   ├── Current Save/        metadata.ion, TravelData, AsParams, and their Restart_ variants
│   ├── SaveIndex.ion         the save list
│   └── User Options/
│       └── options.ini       the Options table (see config.md)
└── dummy.txt
```

`Current Save` is the game's in-progress state: which level and travel
destination to resume, separately from a named save slot. `options.ini`
here, not in `System/`, is where the player's audio/video settings
(resolution, volume, brightness, and the rest of the Options table in
[config.md](config.md)) actually live.

## Outside the install

The level-change launcher (`Ion Launcher.exe`, see
[runtime.md](runtime.md)) writes its own log, separately from the game, to
the current user's `Documents\Thief - Deadly Shadows\Launcher.log`. It is
the only game-related file this project has found outside the install
folder itself.
