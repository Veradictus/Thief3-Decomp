# Mod packages

A mod is shipped as one `.t3mod` file: a zip with a `mod.json` manifest at its
root. A package can hold code (a T3SDK mod DLL), content (files that replace
or add game files, such as a texture pack), or both. The launcher installs
packages by drag and drop or from the mod index, keeps a load order, checks
requirements and conflicts, and switches between profiles.

This page is the format's specification. The launcher (`launcher/src-tauri/src/mods.rs`),
the authoring tool (`tools/t3mod.py`), the index tool (`tools/modindex.py`)
and the SDK's loader (`sdk/loader/mods.cpp`) all follow it, and the shared
examples in `tools/mods/fixtures/` are tested by both the Python and the Rust
side.

## The package

```
my-mod-1.2.0.t3mod          a zip
├── mod.json                 the manifest (required)
├── my-mod.dll               code: the DLL named by "entry" (optional)
├── my-mod.ini, ...          anything else next to it is installed with it
├── files/                   content: overlays the game folder (optional)
│   └── Content/T3/PCTextures/DynamicallyLoaded/stone_wall01.dds
└── textures/                content: replaces textures inside .ibt bundles (optional, experimental)
    └── stone_wall01.dds
```

- The file name is `<id>-<version>.t3mod` by convention; the manifest, not the
  name, is what counts.
- Paths inside the zip use `/`, are relative, and contain no `..`, no drive
  letters and no empty segments. Each segment is a valid Windows name: none of
  `\ : * ? " < > |` or control characters, no trailing dot or space, and no
  device name such as `CON` or `NUL`. Entries are stored or deflated files,
  neither encrypted nor symbolic links; directory entries (names ending in
  `/`) are allowed and ignored. A package that breaks this is refused.
- Names are compared case-insensitively (the game runs on Windows), so two
  entries whose names differ only in case are refused.
- `mod.json` is UTF-8 JSON without a byte-order mark.

## mod.json

```json
{
  "format": 1,
  "id": "better-lockpicks",
  "name": "Better Lockpicks",
  "version": "1.2.0",
  "authors": ["Someone"],
  "description": "Lockpicking without the fuss.",
  "api": 1,
  "entry": "better-lockpicks.dll",
  "requires": { "sdk-ui-helpers": ">=0.3.0" },
  "conflicts": ["old-lockpicks"],
  "homepage": "https://example.org/better-lockpicks",
  "license": "MIT",
  "tags": ["gameplay"]
}
```

| Field | Required | Meaning |
|---|---|---|
| `format` | yes | `1`. A reader refuses a higher number. |
| `id` | yes | Unique, stable name: `^[a-z0-9][a-z0-9_-]{0,63}$`. Also the install folder name. |
| `name` | yes | Display name, 1–80 characters. |
| `version` | yes | [Semantic version](https://semver.org/): `MAJOR.MINOR.PATCH`, optional `-prerelease`, optional `+build`. |
| `authors` | yes | One or more names. |
| `description` | no | One paragraph, at most 1000 characters. |
| `api` | with `entry` | The lowest `T3SDK_API_VERSION` the DLL needs. The launcher warns when the installed SDK is older. |
| `entry` | no | The mod's DLL, a file at the package root ending in `.dll`. Without it the mod is content only. |
| `requires` | no | Other mods this one needs: `{ "<id>": "<version range>" }`. |
| `conflicts` | no | Ids of mods that must not be enabled together with this one. |
| `homepage` | no | An `https://` URL. |
| `license` | no | An SPDX identifier (`MIT`, `CC-BY-4.0`, ...) or free text. |
| `tags` | no | Up to 8 of `gameplay`, `graphics`, `textures`, `audio`, `ui`, `fixes`, `maps`, `tools`, `library`. |

Unknown fields are kept and ignored, so a later `format: 1` field can be added
without breaking older launchers. A package must contain at least one of
`entry`, `files/` or `textures/`.

### Version ranges

A range is one or more comparators separated by commas, all of which must
hold: `>=1.2.0`, `>1.2.0`, `<=2.0.0`, `<2.0.0`, `=1.2.3`, `^1.2.0` (same
major; for `0.x`, same minor; for `0.0.x`, that version only), `~1.2.0` (same
major and minor), or `*` (any). A comparator may leave out the minor and patch
numbers, which then match anything, as in Cargo: `>=1.2` is `>=1.2.0`, `<=1.2`
is `<1.3.0`, `>1.2` is `>=1.3.0` and `=1.2` is `>=1.2.0, <1.3.0`. A version
with a pre-release tag only satisfies a range with a comparator that has the
same `MAJOR.MINOR.PATCH` and a pre-release tag (so neither `*` nor `>=1.0.0`
matches `1.1.0-beta.1`). This is the subset that Rust's `semver` crate and the
Python tool both implement the same way; the tool refuses forms outside it (a
bare `1.2.3`, wildcards such as `1.*`, build metadata).

## Installed layout

Everything the launcher manages lives in the game's `System/mods/` folder, so
it travels with the game install and works without the launcher:

```
System/mods/
├── better-lockpicks/        one folder per installed package (its id)
│   ├── mod.json
│   ├── better-lockpicks.dll
│   ├── files/ ...           kept here; copied into the game while enabled
│   └── textures/ ...
├── load-order.txt           the DLLs T3SDK loads, in order (written by the launcher)
├── state.json               enabled mods, order, profiles (the launcher's)
├── overlay.json             content files placed in the game, and by whom
├── originals/               game files that content mods replaced, to put back
├── some-old-mod.dll         loose DLLs still work (see below)
└── disabled/                loose DLLs that are switched off
```

### load-order.txt

What the SDK reads. One mod per line as `<folder>/<dll>`, relative to
`System/mods/`; blank lines and lines starting with `#` are ignored:

```
# Written by the T3SDK launcher; the SDK loads these top to bottom.
sdk-ui-helpers/sdk-ui-helpers.dll
better-lockpicks/better-lockpicks.dll
```

The SDK loads the listed DLLs in order (a line with an absolute path or `..`
is skipped with a log line), then every loose `System/mods/*.dll` not already
loaded, in name order, as before. Without a `load-order.txt` only the loose
DLLs load. A mod's name in `T3SDK.log` and crash reports is its folder name
(for loose DLLs, the file name). The DLL is loaded with its own folder on the
search path, so it can ship helper DLLs next to it.

### state.json

The launcher's record, rewritten as a whole:

```json
{
  "format": 1,
  "order": ["sdk-ui-helpers", "better-lockpicks", "hd-textures"],
  "enabled": ["sdk-ui-helpers", "better-lockpicks"],
  "profile": "Default",
  "profiles": {
    "Default": { "order": ["sdk-ui-helpers", "better-lockpicks", "hd-textures"], "enabled": ["sdk-ui-helpers", "better-lockpicks"] },
    "Vanilla": { "order": [], "enabled": [] }
  }
}
```

- `order` lists every installed package, enabled or not; a newly installed
  package goes to the end. Later mods load later and win content conflicts.
- `enabled` is a subset of `order`.
- A profile is a saved `order` + `enabled`; switching profiles applies it.
  Ids in a profile that are not installed are skipped (and reported).
- A missing or unreadable file means "nothing enabled, folder order".

### Content: files/

`files/` mirrors the game folder: `files/Content/T3/Bitmaps/x.dds` replaces
`<game>/Content/T3/Bitmaps/x.dds`. It is how most content mods work:

- **Texture and material packs** for [Sneaky Upgrade](https://www.moddb.com/mods/thief-3-sneaky-upgrade)'s
  override folders, `Content/T3/PCTextures/DynamicallyLoaded/` (textures, by
  texture name) and `Content/T3/MatLib/DynamicallyLoaded/` (materials). These
  need Sneaky Upgrade installed; the mod should say so in its description.
- Loose game files: loading screens and fonts (`Content/T3/Bitmaps`,
  `PCTextures`), videos (`Content/T3/VideoTextures/*.bik`), UTX packages,
  configuration files, whole maps (`Content/T3/Maps/*.gmp` + `.ibt`).

Applying the enabled mods ("sync") makes the game folder match them:

1. For every path, the last enabled mod in `order` that provides it wins.
2. Before a game file is replaced for the first time, it is moved to
   `System/mods/originals/<same path>`. A path that did not exist is only
   recorded.
3. `overlay.json` records each placed path with the owning id and the
   file's SHA-256:
   `{ "format": 1, "files": { "Content/T3/Bitmaps/x.dds": { "mod": "hd-ui", "sha256": "…", "original": true } } }`.
4. A recorded path that no enabled mod provides any more is put back from
   `originals/` (or deleted when there was no original).
5. A placed file whose hash no longer matches was changed by something else:
   it is left alone and reported, and its record dropped.

Paths under `System/` (the SDK, other DLLs) are refused in `files/`: code goes
through `entry`, so it shows up in the load order and in crash reports.

### Content: textures/ (experimental)

`textures/<name>.dds` replaces the texture resource named `<name>` inside the
game's `.ibt` bundles (the level bundles and the `Kernel_*` ones), for players
without Sneaky Upgrade. `textures/` holds only `.dds` files, with no
subfolders. `tools/assets/t3texpack.py` does the work:

```sh
python tools/assets/t3texpack.py list [<map or .ibt>]            # texture names, formats, sizes
python tools/assets/t3texpack.py check --pack <dir> [--pack <dir> ...]   # names exist, formats fit
python tools/assets/t3texpack.py apply --pack <dir> [--pack <dir> ...]   # later packs win
python tools/assets/t3texpack.py restore                         # original bundles back
```

`apply` rewrites each affected bundle once from its backup (in the tools'
build folder, like map installs), so applying again, or with fewer packs,
never stacks changes; with no packs it is the same as `restore`. The DDS must
be DXT1, DXT3, DXT5, A8R8G8B8 or X8R8G8B8, with power-of-two sides and a full
or partial mip chain. The texture's usage values are kept from the original.

It is experimental because the engine may check the 20-byte values in the
bundle's header and table ([assets.md](assets.md), section 3); the tool keeps
them, and it has not yet been confirmed in the game.

## Loose DLLs

A `.dll` put straight into `System/mods/` still loads, after the packaged
mods, and shows in the launcher as a "loose" mod that can be switched off
(moved to `System/mods/disabled/`). It has no manifest, so no requirement or
conflict checks.

## Checks

Before a sync and when the list changes, the launcher checks the enabled set:

| Problem | Result |
|---|---|
| `requires` id not installed, disabled, or outside the range | error; the mod stays off until fixed |
| a `requires` mod ordered after the mod that needs it | warning, with a "fix order" action that moves it before |
| two enabled mods that `conflicts` each other (either side) | error |
| `api` higher than the installed SDK's `T3SDK_API_VERSION` | warning (the mod may refuse to load) |
| `entry` set but the SDK is not installed | warning |
| two enabled mods providing the same `files/` or `textures/` path | information: the later one wins |

## Building a package

`tools/t3mod.py` (Python 3.10+, standard library only):

```sh
python tools/t3mod.py validate <mod.json | folder | .t3mod>
python tools/t3mod.py pack <folder> [-o <out.t3mod>]   # validates, then zips as <id>-<version>.t3mod
python tools/t3mod.py info <.t3mod>                     # manifest, file list, SHA-256
```

`pack` skips `.git`, `.gitkeep`, `Thumbs.db`, `.DS_Store`, `desktop.ini`,
`.t3mod` files and `*.pdb` (unless `--with-pdb`), and gives the same bytes for
the same files: entries sorted by path, fixed timestamps, deflate. `validate`
and `pack` also warn about large or unusual files (executables, archives,
empty files, DLLs under `files/`), and `validate` unpacks every entry of a
`.t3mod` to catch a damaged file. The rules live in `tools/mods/t3modlib.py`,
which `tools/modindex.py` shares; `tools/mods/selftest.py` tests both against
the fixtures.

`templates/mod/` is a starter project: CMake builds the DLL against the SDK
headers, writes `mod.json` from the project version, and packs the `.t3mod`;
its GitHub workflow builds it and attaches the package to a release.

## The mod index

The launcher's mod browser reads a JSON index with every published mod. It is
built from one file per mod in this repository's `modindex/mods/<id>.json`
and published with the docs site as
`https://veradictus.github.io/Thief3-Decomp/modindex/index.json` (the URL is a
launcher setting).

```json
{
  "format": 1,
  "generated": "2026-09-28T12:00:00Z",
  "mods": [
    {
      "id": "better-lockpicks",
      "name": "Better Lockpicks",
      "description": "Lockpicking without the fuss.",
      "authors": ["Someone"],
      "homepage": "https://example.org/better-lockpicks",
      "license": "MIT",
      "tags": ["gameplay"],
      "versions": [
        {
          "version": "1.2.0",
          "url": "https://github.com/someone/better-lockpicks/releases/download/v1.2.0/better-lockpicks-1.2.0.t3mod",
          "sha256": "…64 hex digits…",
          "size": 48213,
          "released": "2026-09-01",
          "api": 1,
          "requires": { "sdk-ui-helpers": ">=0.3.0" },
          "conflicts": ["old-lockpicks"]
        }
      ]
    }
  ]
}
```

- A per-mod file is one element of `mods`. Versions are listed newest first.
- `url` is `https://`. The launcher downloads it, checks `size` and `sha256`
  before opening it, and checks that its `mod.json` has the same `id` and
  `version`. A mismatch is refused.
- `api`, `requires` and `conflicts` repeat the package's manifest, so the
  browser can check them before downloading.
- The index lists mods; it does not host them.

`tools/modindex.py validate` checks the per-mod files (CI runs it on every
pull request that touches `modindex/`), `verify` also downloads each new
version and checks it against its manifest, and `build -o <file>` writes the
combined index. Authors prepare the entry for a new version with
`add <.t3mod> --url <url>`; [modindex/README.md](../modindex/README.md) has
how to submit it and the rules.

```sh
python tools/modindex.py validate [<mods/id.json> ...]    # schema, order, fields
python tools/modindex.py verify [--changed-only <git ref>] # download, size, SHA-256, manifest
python tools/modindex.py build -o <index.json>             # the combined index, sorted by id
python tools/modindex.py add <.t3mod> --url <https url> [--released YYYY-MM-DD]
```
