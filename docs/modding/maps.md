# Map editing

Maps can be exported to [Godot](https://godotengine.org/), edited there, and
written back into the game. This is experimental: it has been tested on
synthetic maps. Moving, rotating and scaling what is already in a map, and
changing its properties, works. Adding and removing things does not yet.

## In the launcher

1. Install [Godot 4.7 or newer](https://godotengine.org/download/). The
   launcher usually finds it; otherwise set it under **Settings**.
2. Open **Map Studio**, pick a map and click **Export**.
3. Click **Edit in Godot**. Move, rotate and scale things with Godot's tools,
   or change their properties in the **T3 Map** dock (below the Inspector).
   Then click **Save T3 edits** in that dock.
4. Back in Map Studio, click **Repack**, then **Install**, and play the map.
5. **Restore original** puts the unmodified map back. Every original map is
   backed up once, before it is first replaced.

**View** opens a map in a fly-through viewer instead. The same steps are in
the README's [Edit maps](../../README.md#edit-maps) section.

## On the command line

The launcher runs the tools in `tools/assets/`, which also work by hand from
a checkout:

```sh
python tools/assets/t3map.py Inn                  # export one map (or --all) to build/assets/godot/
godot --path build/assets/godot                   # the viewer
godot --editor --path build/assets/godot          # the editor, with the T3 Map dock
python tools/assets/t3pack.py apply build/assets/godot/Inn/Inn.edits.json   # a patched copy of the map
python tools/assets/t3pack.py install build/assets/patched/Inn.gmp          # backs up the original once
python tools/assets/t3pack.py restore Inn         # the original back
```

[Assets and formats](../assets.md) explains the export (section 6, including
the viewer and the [map editor plugin](../assets.md#map-editor-plugin)), how
edits get back into the game (section 8), and every tool's options
(section 10).

## Sharing maps

A patched map is the game's own map with your changes in it, so don't share
it: what the tools produce from your copy is for your own modding. Maps you
built yourself, for example with the official editor T3Ed, can go into a
[content package](content-packs.md) under `files/Content/T3/Maps/`.
