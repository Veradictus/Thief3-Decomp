# Packaging

Mods are shipped as `.t3mod` files: a zip with a `mod.json` manifest at its
root. [Mod packages](../mods.md) is the format's specification; this page is
the how-to. The [mod template](first-mod.md#start-from-the-template) does all
of this in its build, so you only need it when you pack by hand or check a
package.

## The folder

Put everything the package holds in one folder:

```
my-mod/
├── mod.json          the manifest
├── my-mod.dll        the code, named by "entry"
├── my-mod.ini        optional: other files next to the DLL are installed with it
└── files/            optional: content (see Content and texture packs)
```

## mod.json

A code mod:

```json
{
  "format": 1,
  "id": "my-mod",
  "name": "My Mod",
  "version": "1.0.0",
  "authors": ["Your Name"],
  "description": "What the mod does, in one paragraph.",
  "api": 1,
  "entry": "my-mod.dll",
  "license": "MIT",
  "tags": ["gameplay"]
}
```

What to get right:

- **`id`** names the mod for good: lower-case letters, digits, `-` and `_`,
  at most 64 characters. It is also the mod's folder name in
  `System\mods`. Don't change it between versions.
- **`version`** is a [semantic version](https://semver.org/)
  (`MAJOR.MINOR.PATCH`). Raise it for every release.
- **`api`** is the lowest `T3SDK_API_VERSION` your DLL needs. The launcher
  warns when the installed T3SDK is older.
- **`entry`** is the DLL, at the package root. Leave it out for a content-only
  mod.
- **`requires`** lists other mods yours needs, with a version range:
  `{ "sdk-ui-helpers": ">=0.3.0" }`. Ranges are comparisons separated by
  commas (`">=1.0.0, <2.0.0"`), `^1.2.0` (same major version) or `~1.2.0`
  (same major and minor).
- **`conflicts`** lists the ids of mods that must not be on at the same time.
- **`tags`**: up to 8 of `gameplay`, `graphics`, `textures`, `audio`, `ui`,
  `fixes`, `maps`, `tools`, `library`.

The `mod.json` section of the [specification](../mods.md) has every field
and its limits.

## tools/t3mod.py

The packaging tool is in this repository. It needs Python 3.10 or newer and
nothing else:

```sh
python tools/t3mod.py validate my-mod/                   # check the manifest and the files
python tools/t3mod.py pack my-mod/                       # validate, then write my-mod-1.0.0.t3mod
python tools/t3mod.py pack my-mod/ -o dist/my-mod.t3mod  # choose the output file
python tools/t3mod.py info my-mod-1.0.0.t3mod            # manifest, file list, SHA-256
```

`validate` also takes a `mod.json` or a finished `.t3mod`. The name of the
package file is `<id>-<version>.t3mod` by convention; the launcher goes by
the manifest, not by the file name.

## Before you release

- `t3mod.py validate` passes.
- Install the package in the launcher, turn it on and start the game:
  `T3SDK.log` says `mod <id> loaded`.
- Turn it off again. The game runs without it, and content mods have put the
  original files back.
- The version is new, and the package holds only your own work: no files
  from the game.

Then [publish it to the mod index](publishing.md).
