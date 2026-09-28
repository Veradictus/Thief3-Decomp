# Map edit recipes

Specific, small edits to an existing map, on top of the general
export/edit/repack workflow in [Map editing](../maps.md). This covers what
is currently supported: moving, rotating, scaling, duplicating and deleting
something already in the map, and changing its properties.

## Move, rotate or scale an actor

1. Export the map and open it in the Godot editor (Map Studio's **Export**,
   then **Edit in Godot**; or `t3map.py` and `godot --editor`, from
   [Map editing](../maps.md)).
2. Select the actor and move, rotate or scale it with Godot's own gizmos or
   the Inspector.
3. Save the scene (Ctrl+S), or click **Save T3 edits** in the **T3 Map**
   dock: either writes the edits file.

Scale is uniform only: Thief has no `DrawScale3D`, so a non-uniform or
mirrored scale is reported by the dock and not saved. Rotating past a pole
(pitch ±90°) is handled for you: the plugin picks the rotator nearest to the
original, so an actor you did not touch always round-trips exactly.

## Change a property

The **T3 Map** dock, below the Inspector, lists the selected actor's class,
archetype, mesh, and its own gamesys properties. You can edit:

- numbers (floats, ints, plain bytes);
- bools, as a check box;
- enum bytes, as a list of names;
- names and strings.

Structs, arrays, object references and bitfields show there but are
read-only for now, and so is `DrawScale` (scale the node itself instead, as
above).

The dock lists every actor you have changed so far; click one to jump back
to it, or **Revert** to undo just that actor. Every edit also goes through
Godot's own undo/redo.

## Get the edit into the game

**Save T3 edits** writes `<Level>.edits.json`, holding only the actors you
actually changed. Back in Map Studio:

1. **Repack** writes a patched copy of the map (or, on the command line,
   `t3pack.py apply <Level>.edits.json`).
2. **Install** puts it into the game, backing up the original the first time
   (`t3pack.py install <patched .gmp>`).
3. Play the map. **Restore original** (`t3pack.py restore <Level>`) puts the
   unmodified map back at any time.

## Share the result

A patched copy of the game's own map is still the game's map: don't share
it. A map you built yourself, for example with the official editor T3Ed, has
none of that restriction and can go into a content pack's own
`files/Content/T3/Maps/` (see
[Replace game files with a content pack](content.md)).

## Watch out for

- **New actors are copies.** Duplicate an actor (Ctrl+D) to add one: the
  repacked map gets a new actor with the original's mesh and properties,
  and your placement. A node you add any other way (a new Node3D, a scene
  dragged in) has no T3 metadata and is not saved; the dock warns about it.
- **Deleting** takes an actor out of the level; the map's LevelInfo cannot
  be deleted.
- **This is experimental.** It has been tested on synthetic maps, not
  confirmed on retail ones; keep a backup, and remember `Restore original`
  always works as long as the map's install itself is intact.
- An actor you did not move keeps its exported position exactly; only
  touched actors round-trip through rounding (0.01 units).

## Reference

- [Map editing](../maps.md): the full launcher and command-line workflow.
- [Assets and formats](../../assets.md): the map editor plugin's exact
  editing rules, and the export format underneath it.
