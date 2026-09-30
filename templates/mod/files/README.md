# files/: content for the game folder

Everything in this folder goes into the game folder, at the same path, while
the mod is enabled: `files/Content/T3/Bitmaps/x.dds` replaces
`<game>/Content/T3/Bitmaps/x.dds`. The launcher moves each game file it
replaces aside first and puts it back when the mod is disabled or removed.
When two enabled mods provide the same file, the later one in the load order
wins.

What goes here:

- texture and material packs for Sneaky Upgrade's override folders,
  `Content/T3/PCTextures/DynamicallyLoaded/` and
  `Content/T3/MatLib/DynamicallyLoaded/` (these need Sneaky Upgrade
  installed; say so in the mod's description);
- loose game files: loading screens, fonts, videos, configuration files,
  whole maps (`Content/T3/Maps/*.gmp` with their `.ibt`).

What does not:

- anything under `System/`: code is the mod's DLL (`entry` in `mod.json`),
  so it shows in the load order and in crash reports. Packages with
  `files/System/` are refused.
- the game's own files, as they are: ship only what you made or have the
  right to share.

A top-level `textures/` folder (next to `files/`) can instead replace
textures inside the game's `.ibt` bundles, for players without Sneaky
Upgrade: `textures/<texture name>.dds`. It is experimental; see
[docs/mods.md](https://github.com/Veradictus/Thief3-Decomp/blob/main/docs/mods.md).

This README is not packed (`cmake/package.cmake` skips it). A mod with no
content can delete this folder.
