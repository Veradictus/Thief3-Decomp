# Levels

What a level is made of, how the game gets the player from one `PlayerStart`
to the right one, and the complete list of the game's 32 maps. The byte
format behind everything on this page is in [assets.md](../assets.md).

## A level's files

A level is always a pair of files sharing a name:

| File | Format | Holds |
|---|---|---|
| `<Level>.gmp` | Unreal package | The level's objects: its actors, the `Level` object, and the BSP `Model` |
| `<Level>.ibt` | Ion Storm block file | The level's own resources: static meshes, textures, materials, physics hulls, ragdolls, skeletal meshes and animations, trigger scripts |

Every level also loads three **kernel** block files shared by the whole
game, `Kernel_GFXALL.ibt`, `Kernel_PHYALL.ibt` and `Kernel_TSDALL.ibt`
(shaders, HUD art, Garrett's own meshes), and the main menu level loads its
own kernel set, `MainMenu_*ALL.ibt`, instead of a per-level `.ibt` — `Entry`,
the menu level below, has no `Entry.ibt` of its own for exactly this reason.

## What is in a level

Decoded so far, inside the `Level` object and the package around it, in
order:

- **The actor list**: every actor in the level, starting with the
  `LevelInfo` actor and the level's builder `Brush`.
- **The URL**: the protocol, host, map name, portal, options, port and a
  validity flag — the same URL structure used to travel between levels (see
  [runtime.md](runtime.md)).
- **A reference to the level's `Model`** (the BSP, below).
- **Navigation-mesh polygons.**
- **BSP render blocks**: the actual drawable geometry, packed the same way
  as a static mesh's render data, one block per piece of world geometry.
  What indexes these blocks — by zone, by BSP leaf, or something else — is
  not known yet.
- **A list of BSP polygons**, kept with position, normal, UV and material
  data per vertex; probably the source surfaces, kept for decals or
  lighting rather than for drawing.
- Several hundred kilobytes more that are not decoded.

The `Model` itself is a cooked, stripped-down BSP: nodes (plane, a 256-bit
zone mask, flags, bounding sphere, zone and vertex counts) and a zone table,
with the actual points, vertices, surfaces and brush polygons removed —
they are not needed to render the game's own render blocks. **Zones** exist
in this data (the per-node zone mask, and a zone table), but portals and the
navigation mesh's structure are not decoded, so nothing about the level's
visibility or AI navigation graph is understood yet beyond their raw
presence.

A level's resource file (`.ibt`) holds, among other things, `TriggerScriptDef`
resources (`TS_<n>`, not decoded) and, for every static mesh used, its
render data and any physics hulls scaled for that placement. See
[assets.md](../assets.md) for the resource-type table.

## Player starts and travelling between levels

A `PlayerStart` actor is where a player can appear when a level loads.
Because every level restarts the process (see [runtime.md](runtime.md)),
arriving at the right start is done through the level-change URL: it
carries a `DestTeleporter` argument, and the new level picks the
`PlayerStart` whose own `TeleportDestName` property matches it. A New Game,
for instance, launches the URL
`Inn?-LoadTravel?-LoadSave?-ObjectFilter=0?DestTeleporter="Inn"`, landing the
player at the `PlayerStart` in `Inn` tagged `TeleportDestName="Inn"`.

Like any other actor, a level's `PlayerStart`s are plain objects with
instance-numbered names (`PlayerStart__0`, `PlayerStart__1`, ...); a level
with several entry points — one per way of reaching it — has one
`PlayerStart` per destination name.

## The map list

The install ships 32 maps. Titles are the level's own English name (read
from its string tables); file names are the `.gmp`/`.ibt` pair's shared
name. Several locations are visited more than once, as a separate mission
each time; grouped here by their shared file-name prefix, which is the only
grouping the files themselves make clear:

| Group | Title | File |
|---|---|---|
| Auldale | Auldale | `Auldale1` |
| | Gamall's Lair | `Auldale3` |
| Castle | Castle Front | `Castle1` |
| | Inner Quarters | `Castle2` |
| Clocktower | Upper Clocktower | `Clocktower1` |
| | Lower Clocktower | `Clocktower2` |
| Citadel | Outer Citadel | `dungeon1` |
| | Citadel Core | `dungeon2` |
| Docks | Docks | `docks2` |
| | The Abysmal Gale | `docks3` |
| Hammerite intro | Cathedral Grounds | `HammerIntro1` |
| | Hammer Factory | `HammerIntro2` |
| Cradle | Outer Cradle | `HauntedHouse1` |
| | Inner Cradle | `HauntedHouse2` |
| Keeper Compound | Keeper Compound | `KeeperCompound1` |
| | Lower Libraries | `KeeperCompound2` |
| Museum | Porter Hall | `museum1` |
| | Tesero Hall | `museum2` |
| Old Quarter | Old Quarter | `OldQuarter1` |
| | Fort Ironwood | `OldQuarter3` |
| Pagan intro | Pagan Tunnels | `PaganIntro1` |
| | Pagan Sanctuary | `PaganIntro2` |
| Overlook | Overlook Grounds | `SeasideMansion1` |
| | Overlook Proper | `SeasideMansion2` |
| South Quarter | South Quarter | `SouthQuarter1` |
| | Garrett's Building | `SouthQuarter1_int1` |
| | Pavelock Prison | `SouthQuarter3` |
| Stonemarket | Stonemarket Plaza | `Stonemarket1` |
| | Stonemarket Proper | `Stonemarket2` |
| | Keeper Library | `Stonemarket3` |
| — | Entry | `Entry` |
| — | The Blue Heron Inn | `Inn` |

Notes on the two ungrouped maps: `Entry` is the main menu level (its player
controller is `Entry.Camera__0`, per [engine.md](../engine.md)), not a
mission. `Inn` is the game's hub level — New Game and several mission exits
travel back to it (the URL example above lands there).

`SouthQuarter1_int1` is an interior reached from `SouthQuarter1`, per its
file name; no other relationship between same-group maps beyond "the same
place, at a different point in the story" is established here. No file
exists for `OldQuarter2` or `SouthQuarter2` in the retail install.
