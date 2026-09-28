# Content and texture packs

A content mod ships files instead of code, or next to it. A package without
`entry` is content only, and needs no `api`:

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

A package must hold at least one of `entry`, `files/` or `textures/`. Pack it
the same way as a code mod (see [Packaging](packaging.md)).

## files/: files in the game folder

`files/` mirrors the game folder: `files/Content/T3/Bitmaps/x.dds` replaces
`Content/T3/Bitmaps/x.dds` in the game, or adds it if the game has no such
file. When the mod is turned on, the launcher moves the game's original
aside (into `System/mods/originals/`) and puts your file in its place. When
the mod is turned off, the original comes back. If two mods provide the same
file, the one later in the load order wins.

What goes there:

- **Texture and material packs for Sneaky Upgrade.**
  [Sneaky Upgrade](https://www.moddb.com/mods/thief-3-sneaky-upgrade) loads
  textures from `Content/T3/PCTextures/DynamicallyLoaded/` (by texture name)
  and materials from `Content/T3/MatLib/DynamicallyLoaded/`. These packs need
  Sneaky Upgrade installed: say so in the description.
- **Loose game files**: loading screens and fonts (`Content/T3/Bitmaps`,
  `Content/T3/PCTextures`), videos (`Content/T3/VideoTextures/*.bik`), UTX
  packages, configuration files, and whole maps (`Content/T3/Maps/*.gmp`
  with their `.ibt`).

Nothing under `System/` is allowed in `files/`. Code goes through `entry`,
so that it shows in the load order and in crash reports.

## textures/: textures inside the game's bundles (experimental)

`textures/<name>.dds` replaces the texture named `<name>` inside the game's
`.ibt` bundles, for players without Sneaky Upgrade. The textures must be:

- DXT1, DXT3, DXT5, A8R8G8B8 or X8R8G8B8;
- a power of two wide and high;
- with a full or partial mip chain.

`tools/assets/t3texpack.py` in this repository finds the names and checks a
pack against your copy of the game:

```sh
python tools/assets/t3texpack.py list [<map or .ibt>]   # texture names, formats and sizes
python tools/assets/t3texpack.py check --pack <folder>  # the names exist, the formats fit
```

The launcher applies these packs by rewriting each affected bundle from a
backup of the original. It is experimental: the bundles carry values whose
meaning is not known yet (see [Assets and formats](../assets.md), section 3),
and it has not been confirmed in the game that the engine accepts rewritten
bundles. Test your pack in the game before you publish it.

## Only your own work

Packages are shared with other players, so they must hold only what you
made. Files from the game, and files extracted or converted from it, belong
to the game's owners: don't put them in a package. The asset tools in this
repository are for your own modding; what they extract from your copy stays
on your PC.
