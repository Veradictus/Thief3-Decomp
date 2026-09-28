# Replace game files with a content pack

Ship a texture, video, config file or map that replaces or adds to the
game's own files — no code required.

## The recipe

A content mod is a package with no `entry`: just `mod.json` and a `files/`
folder that mirrors the game's own folder structure.

```
hd-loading-screens/
├── mod.json
└── files/
    └── Content/T3/Bitmaps/Loading1.dds
```

```json
{
  "format": 1,
  "id": "hd-loading-screens",
  "name": "HD Loading Screens",
  "version": "1.0.0",
  "authors": ["Your Name"],
  "description": "Sharper loading screens.",
  "tags": ["graphics"]
}
```

`files/Content/T3/Bitmaps/Loading1.dds` replaces
`<game folder>/Content/T3/Bitmaps/Loading1.dds` while the mod is enabled, and
the launcher restores the original file when it is disabled. Get the path
exactly right (case does not matter, but every folder and the file name
must match); [Content and texture packs](../content-packs.md) lists what
usually goes under `files/`, and how the backup and restore mechanics work.

Then validate and pack it:

```sh
python tools/t3mod.py validate hd-loading-screens/
python tools/t3mod.py pack hd-loading-screens/
```

Drag the resulting `.t3mod` onto the launcher, enable it, and check that the
file changed in the game folder; disable it again and check that the
original is back.

## An alternative for textures: textures/

`files/` replaces a loose file on disk. Some textures instead live packed
inside the game's `.ibt` bundles; a `textures/<name>.dds` entry replaces one
of those by resource name instead of by path (experimental — needs the exact
name, a supported DXT/A8R8G8B8 format, and a power-of-two size). See
[Content and texture packs](../content-packs.md) (the "textures/" section)
and `tools/assets/t3texpack.py list` to find names.

## Watch out for

- **Only your own work.** Never put a game file — original or edited — into
  a package, even a single texture. Packages are shared with other players;
  what you ship must be yours (see
  [CONTRIBUTING.md](../../../CONTRIBUTING.md)).
- **Two mods, one file.** If another enabled mod also provides the same
  path, whichever is later in the load order wins; there is no merging. Use
  `mod.json`'s `conflicts` if your pack genuinely cannot coexist with a
  specific other one (see [Play well with other mods](compatibility.md)).
- **Nothing under `System/`.** Code goes through `entry` so it shows up in
  the load order and in crash reports; `files/` refuses paths there.

## Reference

- [Content and texture packs](../content-packs.md): the full mechanics of
  `files/` and `textures/`.
- [Mod packages](../../mods.md): the manifest format and how the launcher
  applies content.
- [Packaging](../packaging.md): `tools/t3mod.py` in full.
