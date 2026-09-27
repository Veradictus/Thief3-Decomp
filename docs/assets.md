# Thief: Deadly Shadows assets and levels, and their export to Godot

This document covers how Thief: Deadly Shadows (T3) stores its levels and
assets, what the prototype tools in `tools/assets/` already export, and a plan
for a Godot 4 map editor built on them.

> **Personal use only.** These tools read and convert data from your own,
> legally owned copy of the game so that you can mod it. Extracted and
> converted assets (everything under `build/assets/`) are copyrighted game
> content: do not redistribute them and never commit them. The tools only
> read the install. They do not modify it, do not touch DRM, and do not
> launch the game.

Status at a glance:

- **Works.** Every retail map exports to a Godot 4.7 scene:
  - static meshes with their skins, materials and textures;
  - the BSP world geometry;
  - lights;
  - every other actor as a marker, carrying its gamesys properties as node
    metadata.

  The scenes import and load in Godot 4.7.2 (headless import and a load
  check), and rendered views look like the game. The exported project opens
  as a map viewer, with a map picker, a fly camera and an actor inspector
  (section 6).
- **Not decoded yet.**
  - Skeletal meshes, animations, Havok physics shapes, trigger scripts,
    particle emitters, sounds.
  - Zones and portals, and the navigation mesh.
  - The index structure around the BSP render blocks.
  - Anything needed to write a level back.

## 1. What is in the install

The file survey is reproducible with `tools/assets/inventory.py`. Game data
is in `Content/T3/`, engine and script data in `System/`.

| Where | Files | Format | Role |
|---|---|---|---|
| `Content/T3/Maps/<Level>.gmp` | 32 | Unreal package, v95, licensee 107–133 | Level: actors, BSP nodes, BSP render blocks, navigation data, gamesys property overrides |
| `Content/T3/Maps/<Level>.ibt` | 31 + 6 | Ion Storm block file (`0xC0000001`) | The level's resources: static meshes, textures, materials, physics hulls, ragdolls, skeletal meshes and animations, trigger scripts |
| `Content/T3/Maps/Kernel_{GFX,PHY,TSD}ALL.ibt` | 3 | block file | Resources shared by all levels (shaders, HUD, Garrett); loaded together with every level |
| `Content/T3/Maps/MainMenu_*ALL.ibt` | 3 | block file | Kernel set for the menu map (`Entry.gmp`) |
| `System/*.t3u` | 9 | Unreal package, v95/133 | Script packages. They still contain their UnrealScript source (`TextBuffer`). `T3Gamesys.t3u` holds the ~2,300 archetypes |
| `Content/T3/UTX/*.utx` | 14 | Unreal packages, v61–v95 | Legacy texture packages (particles, sky cube, HUD). Several engine generations are mixed |
| `Content/T3/PCTextures`, `Bitmaps`, `System/Data` | ~120 | DDS | Loose textures (maps, loading screens, fonts, lighting lookup tables) |
| `Content/T3/Sounds/SchemaMetafile_*.csc` | 5 | Ion sound metafile | Sound schemas and embedded audio (RIFF/WAV, Ogg) |
| `Content/T3/VideoTextures/*.bik` | 23 | Bink | Videos |
| `Content/T3/Books/*.sch`, `Conversations/*.con`, `LipsincData/*.lbd`, `TagDatabase`, `Flags` | | text and binary | Readables, conversations, lip sync, motion tags, quest flags |
| `System/Data/_Missing.*`, `_Corrupt.*` | | Ion chunk files (`0FFE`) | Fallback resources in the editor's loose formats (`.sm`, `.smd`, `.tim`, `.arc`) |

A level is always the pair `<Level>.gmp` + `<Level>.ibt`, plus the kernel
bundles. The `.gmp` refers to `.ibt` resources **by name**: a mesh name plus
a skin name, a material name, a texture name.

T3 shipped cooked data only. The official editor release (T3Ed, February 2005;
see section 7) contains the editor sources: `.unr` maps with their brushes
and polys, `.tim` static meshes, `.mlb` material libraries, `.dds` textures,
and ActorX `.psk`/`.psa` files. `upkg.py` also reads `.unr` files, which are
the same package format.

## 2. Unreal packages (.t3u, .gmp, .unr, .utx)

T3 runs on Ion Storm's fork of an early Unreal Engine 2 ("Flesh", shared with
Deus Ex: Invisible War). Reader: `tools/assets/upkg.py`.

### Summary

The layout is the stock UE2 summary for version 95 with Ion Storm fields
added:

| Offset | Field |
|---|---|
| 0x00 | tag `0x9E2A83C1`, u16 file version (95), u16 licensee (107–133 in maps and scripts) |
| 0x08 | package flags, name count/offset, export count/offset, import count/offset |
| 0x24 | **Ion:** one extra DWORD. It is 0 in `.t3u` files and non-zero in maps; meaning unknown. Present from licensee 44 |
| 0x28 | GUID (16 bytes), then at 0x38 the generation count and the generations (export count, name count each) |
| after the generations | **Ion:** two DWORDs, present from licensee 22. The first is 0 in maps and small in scripts. The second is the offset of an extra table that sits between the import table and the export table. The name table follows (at 0x4C with one generation) |

The retail UTX files span engine versions 61, 68, 69, 88 and 95 (licensee
0–126). `upkg.py` picks whichever layout makes the header end exactly at the
name table.

The **extra table** is, in every shipped map, 32 lists of export indices of
the form `u32 count, u32 index[count]`, each list the identity `0..N-1`.
Script packages vary. Its purpose is not established; it looks like
per-phase load or preload order.

### Tables

The name, import and export tables use the stock UE2 encoding (compact
indices, FString names plus u32 flags). Names keep the instance number as
text (`Camera__19`); at runtime the engine holds an FName as a 16-bit index
plus a 16-bit number (see [engine.md](engine.md)).

### Object serialisation (Flesh)

A non-class object is serialised as:

1. **State frame**, only when the object has `RF_HasStack`: compact Node,
   compact StateNode, u64 ProbeMask, u32 LatentAction (garbage in shipped
   maps), and compact Offset if Node ≠ 0.
2. **Tagged properties.** Stock UE2 tags (name, info byte, struct name, size
   code, array index). **Every struct value, including `Vector` and
   `Rotator`, is itself a tagged property list** ending in `None`. Only fields
   that differ from their defaults are written.
3. **Gamesys property blocks**, repeated `u32 id, u32 1, u32 size, data[size]`
   and terminated by an id of 0.
4. **Links**: `u32 count` followed by compact object references
   (LinkDataObjects: attachments, trigger scripts, loadouts...).
5. **Class-specific native data.** Most actors have 4 more bytes here;
   `TextBuffer` has `u32 Pos, u32 Top, FString Text`; others vary.

UELib calls part 4 "LinkedData"; see section 7.

### The gamesys property system

T3 bolted a Dark Engine-style property system onto Unreal. The engine's own
UnrealScript declares these properties with explicit numeric ids, for
example `var(Render) inherited(<id>) ... ObjectMesh` or
`var runtimeinstantiated(<id>) float DrawScale`. A gamesys block id is
`(type << 16) | property id`.

The type bits match the UProperty class of the declaration:

| Bits | Value encoding | Declared as |
|---|---|---|
| 0x0001 | compact object index | `class<...>` |
| 0x0002 | compact object index | object reference |
| 0x0004 | FString | `string` |
| 0x0008 | tagged property list | struct |
| 0x0010 | f32 | `float` |
| 0x0020 | i32 | `int` |
| 0x0080 | u8 | `bool` |
| 0x0100 | compact name index | `name` |
| 0x0200 | u8 | `byte` / enum |
| 0x0400 | compact count, then elements | dynamic array |
| 0x0800 | u32 bit mask | `bitfield` (Ion syntax with an inline enum of bit names) |
| 0x4000 | flag | declared `runtimeinstantiated` (engine-owned, e.g. `StaticMesh`, `DrawScale`, `PrePivot`) |

`t3props.py` builds the id → (name, type, category, owner class,
description) table at run time from the script source inside the user's own
`.t3u` files. About 1,130 properties are declared this way, mostly in
`Actor` and the AI classes. With this table, over 99.8% of the gamesys blocks
in the retail maps get a name. It caches the table in
`build/assets/cache/`. The same ids are also stored in the compiled UProperty
objects; UELib reads them there. That is an alternative source not used yet.

Mesh placement uses these properties:

- **`ObjectMesh`**: struct `{Name, Skin}`, naming a static mesh resource in
  the level `.ibt` and one of its skins.
- **`DrawScale`**: uniform scale. T3 has no `DrawScale3D`.

Lights use `LightColor`, a struct of brightness, hue and saturation in UE
HSV bytes. They also use `LightShape` (radius, cone...), `FleshLightType`
(omni, spot, directional, ambient, projector, with or without shadows) and
`bLightOn`.

### Archetypes (T3Gamesys.t3u)

Placeable things are archetypes: UnrealScript classes named `D_<n>` that
extend each other (`D_<n> extends D_<m> ...` up to `Actor`, `Light`,
`T3AIPawn`...). A map actor of class `D_<n>` inherits the archetype chain's
gamesys blocks and stores only its overrides.

The class layout, as parsed by `t3gamesys.py`:

- UObject part: `u32 link count` plus links.
- Stock v95 UField/UStruct/UState/UClass fields. UState masks are 64-bit.
- **Ion addition:** an FString display name. This gives human-readable
  archetype names.
- Default tagged properties, then gamesys blocks.

2,318 of the 2,345 classes parse completely. The rest are non-actor helper
classes with custom native data.

### The level object (`MyLevel`, class `Level`)

Decoded so far, in order:

- 13 bytes, not decoded.
- The actor list: `u32 num, u32 max, compact[num]`. It starts with
  `LevelInfo` and the builder `Brush`.
- The URL: protocol, host, map, portal, options, port, valid.
- A reference to the level `Model`.
- Navigation-mesh polygons.
- **BSP render blocks** (see below).
- A list of BSP polygons with 92-byte vertices (position, normal, UVs), a
  material name and flags. These are probably the source surfaces, kept for
  decals or lighting.
- Several hundred kilobytes more, not decoded.

**BSP.** The cooked `Model` keeps only the BSP nodes: plane, 256-bit zone
mask, flags, the stock compact links, a bounding sphere, zone and vertex
count, and leaves. It also keeps the zone table. Points, vertices and
surfaces are stripped, and so are the `Polys` of every brush.

What the game draws are the render blocks inside the Level object. Each
block is a u32 id followed by the same render-data layout as a static mesh
(section 3), with **packed 32-byte vertices**, world-space positions and
sections named after their material. `t3bsp.py` finds them by scanning for
a valid render-data header. The structure that indexes them (per zone? per
BSP leaf?) is the main open item for the level format.

### Other objects in a map

- `StaticMesh` exports are small proxies: the resource name and a bounding
  box. The data is in the `.ibt`.
- Brush `Model`s are stripped to their bounds.
- LinkDataObjects (attachments, trigger-script links, loadouts...) are
  tagged objects (bones, offsets, flags). Their native tail is two compact
  object references: the source (parent) and the destination (child). Actors
  also list the link objects they own. `t3map.py` exports all links and
  records `attached_to` and `attached_bone` on child actors.
- Emitters (`SpriteEmitter`, `BeamEmitter`...) are UE2-style particle
  objects, not decoded here.

## 3. Block files (.ibt)

Reader: `tools/assets/ibt.py`. The same container is `.cbt` (compressed,
used by fan missions), `.xbt` on Xbox, and `.ibd` in DX:IW.

- **Header** (0x34 bytes): magic `0xC0000001`, alignment `0x800`, data
  start, data size, largest resource size, largest part size, resource
  count, part count, and a 20-byte value (probably a hash).
- **Resource table**: 0x134-byte entries.
  - Data offset (aligned to 0x800), size, and padding.
  - First part and part count.
  - A 20-byte value. It is not the SHA-1 of the data or of the name.
  - A u8 resource type.
  - A 263-byte name.
  - A u32 load filter (always `0xFFFFFFFF`).
- **Part table**: one u32 per part. A resource is the concatenation of its
  parts, and each part is one field or array written by the serialiser. This
  makes resources easy to walk field by field; `ibt.PartReader` checks every
  read against the part sizes.

The resource type numbers follow Ion Storm's `eResourceType` enum. The public
T3Ed release prints it in `Utility/misc_perl/dumpblockfile.pl`. Types found
in retail bundles:

| Type | Name | Status |
|---|---|---|
| 4 | StaticMesh | decoded: skins, hardpoints, render data (below) |
| 5 | PhysicsHull | `PHYS` chunk with Havok 2 serialised shapes; named `<mesh>--<n> <sx> <sy> <sz>` (one per mesh and scale). Not decoded |
| 6 | Ragdolls | bone capsules and constraints. Not decoded |
| 8 | Texture | decoded (below) |
| 10 | MatLib (material) | decoded (below) |
| 16 | SkeletalMesh | header parts: name, source `.psk` path, a transform, flags and a second name; then one blob with bones, vertices and weights. Not decoded (the source format is ActorX `.psk`) |
| 17 | SkeletalAnim | not decoded (source `.psa`) |
| 21 | TriggerScriptDef | `TS_<n>` trigger scripts: conditions and actions with UTF-16 strings. Not decoded |
| 29 | FleshShader | compiled vertex and pixel shaders (kernel only) |

### Texture (type 8)

Fields, one part each:

- u8 version (1).
- Format: a FourCC (`DXT1`, `DXT3`, `DXT5`) or a D3DFORMAT number (`A8R8G8B8`,
  `X8R8G8B8`).
- Mip count.
- u32 usage: 0 diffuse, 1 normal, 2 specular, 5 emissive, 6 environment, ...
- u32 usage detail.
- Width and height, then width and height again.
- Total mip bytes.
- Two bytes.
- Per mip: level, width, height, size, an alignment-padding part, and the
  data part.

`t3texture.py` writes a DDS directly and decodes DXT1/3/5 in pure Python to
PNG.

### Material (type 10)

A MatLib material, authored in 3ds Max with Ion's "IonShader" and exported
to `.mlb` libraries. Fields:

- Flags.
- A stage-usage mask.
- Three RGBA colours.
- Three floats.
- Some flags.
- The source `.mlb` path.
- A surface category: an index into `Content/T3/MatLib/categories.txt`,
  used for footstep and physics sounds.
- **Eight texture stage names.** Stage 0 is diffuse and stage 1 the normal
  map. Stages 2 and 4 look like specular, 3 like a mask or detail map, 5 glow
  and 6 an environment map.

A mesh section's "material" is the name of one of these materials. The
material's stage-0 texture is the diffuse texture, found case-insensitively
by texture name.

### Static mesh (type 4)

- Skins: each skin has a name and one material name per section. Skins are
  alternate texture sets, and the actor's `ObjectMesh.Skin` picks one.
- Per-skin flags.
- Mesh flags.
- Hardpoints: a 3×4 transform and a name. Examples are `Collision` and
  `hp_*` points for lights, emitters, sitting and locks.
- One render-data part.

**Render data** is shared with the BSP blocks:

- Bounding box, then sphere radius and centre.
- Counts: vertices, indices, triangles, sections, shadow indices, shadow
  triangles, shadow vertices, `1`, stride, `0`.
- Vertices. Stride 64: position, normal, uv0, tangent, uv1, uv2, BGRA colour.
  Stride −32: packed; the normal and tangent are 4-byte D3DCOLOR-order
  vectors with 128 = 0.
- Stencil-shadow vertices (16 bytes each).
- Shadow indices.
- Render indices (u16, absolute).
- Sections: name, triangle count, first vertex, vertex count, first index,
  index count, 0.

Positions are in Unreal units and axes. Triangles are front-facing when
`(b−a)×(c−a)` points along the normal.

Faces using the material `BF` (category "ignored", placeholder texture) are
not drawn by the game; the exporter drops them.

## 4. Loose formats

- **Ion chunk files** (`System/Data`, and T3Ed's `.tim`/`.sm`/`.smd`): the
  magic `0FFE`/`EFF1`, then chunks of `{FourCC stored reversed, version, size}`.
  Chunk types include `INF0` (UTF-16 name, source and author), `SM05`
  (static mesh), and `SKA0` (skin assignment).
- **Sound metafiles** (`SchemaMetafile_*.csc`): an Ion Storm schema database
  (tags, schemas, per-sound offsets) with embedded RIFF/WAV and Ogg data.
  T3Ed's `compileschemas.pl` and `dumpschemanames.pl` describe the layout
  exactly. snobel's `csc-tool` converts it both ways.
- **Books** (`.sch`) are text. Conversations (`.con`), lip sync (`.lbd`) and
  the tag database are small binaries. None of these is needed for
  geometry.

## 5. Coordinates and units

- **Axes.** Unreal is X forward, Y right, Z up (left-handed). Godot and glTF
  are Y up and right-handed. The exporter maps `(x, y, z)` to `(x, z, y)`.
  Because a single axis swap mirrors the space, triangle winding is reversed.
  Actor rotations are converted as matrices: UE2's `FRotationMatrix`
  conjugated by the swap. There is no Euler conversion.
- **Units.** T3 content is built at 16 units per foot (a `...4x8` door mesh
  is 64 × 128 units). The default export scale is therefore
  0.3048 / 16 = 0.01905 m per unit. The scene stores this as
  `metadata/t3_units_per_meter`, and `--scale` changes it.
- **Lights.** The unit of `LightRadius` is not established. The exporter
  assumes feet (radius × 16 units) and keeps the raw values in metadata.
- **Colour.** Light colour follows UE2's `FGetHSV`, in which saturation 255
  is white.

## 6. The Godot export (prototype)

Run `t3map.py <Level>` or `t3map.py --all`. The output goes to
`build/assets/godot/`, which is itself a Godot 4.7 project:

```
project.godot                  the viewer project (rewritten on every export)
t3_maps.json                   index of exported maps: id, title, scene, counts, default start
t3_tools/                      copy of tools/assets/godot/: the viewer and check scripts
<Level>/<Level>.tscn           the level (text scene, format 3)
<Level>/<Level>.actors.json    every actor and link object, lossless-ish, for tools
<Level>/meshes/<mesh>[__<skin>].glb   one per (mesh, skin) pair used
<Level>/meshes/<Level>_bsp.glb        BSP render blocks, one node per block
<Level>/textures/*.png                 decoded textures (lower-case names)
```

Scene structure:

- An instance of the BSP `.glb`.
- A `StaticMeshes` node. It holds a `.glb` instance for every actor that has
  a mesh (plain `StaticMeshActor`s and archetype instances such as lamps and
  doors). Actors that also have a light get a `T3Light` child.
- A `Lights` node with `OmniLight3D`, `SpotLight3D` or `DirectionalLight3D`.
- A `Markers` node with a `Marker3D` for every other actor: player starts,
  volumes, AI points, emitters, sounds, cameras, brushes.
- A hidden `CharacterParts` node. It holds the meshes attached to NPC
  skeletons (eyes, teeth, hair, armour). The skeletons are not exported yet,
  so these parts would otherwise float in the air.
- A `WorldEnvironment` built from the LevelInfo actor: ambient colour and
  brightness (UE HSV) and depth fog (colour, start and end).

Every node carries metadata:

- `t3_name` and `t3_class`.
- `t3_archetype` (display name) and `t3_base`.
- `t3_mesh` and `t3_skin`.
- `t3_tag`.
- `t3_attached_to` and `t3_attached_bone`, for attachment children.
- `t3_gamesys`: the instance's own gamesys properties as JSON, with property
  names and enum and bitfield names resolved.
- `t3_default_start` on the player start the viewer opens at: one whose
  travel destination mentions "start", else one without a destination, else
  the first.

The level root carries `t3_level`, `t3_title` (the English level name from
the install's string tables, e.g. from `LevelEnterText`) and
`t3_units_per_meter`.

glTF materials:

- Diffuse, normal and glow stages become base colour, normal and emissive
  textures.
- Textures with alpha use `alphaMode: MASK`.
- Untextured materials (such as the metallic loot shaders) fall back to the
  material colour.
- Each material keeps its T3 name, stages and category in `extras`.

Godot creates `StandardMaterial3D`s from these on import.

To verify, run
`godot_check.py --godot <Godot 4.7 exe>` (or set `$GODOT`). It imports the
project headlessly and loads every level scene with `check_scene.gd`.
`--viewer [MAP]` runs the viewer's self-test (below) headlessly,
`--viewer-shot OUT.png [--map MAP]` saves a frame of the picker or the
viewer, and `--render` renders one frame of a scene.

What is missing for a faithful look:

- T3's lighting model: per-pixel lights with stencil shadows, projected
  light textures and the `LightingBehavior` animations. A `ShaderMaterial`
  or light scripts could mimic it.
- Specular and environment stages.
- Particle emitters.
- The sky cube, which is in a UTX.
- Characters and animation.
- Zone ambient light (the level-wide ambient and fog are exported).

### Viewer

The exported project is a map viewer. Its code is original GDScript in
`tools/assets/godot/viewer/`. The exporter copies it to `res://t3_tools/` and
writes `project.godot`: the main scene is the map picker, the input map holds
the `t3_*` actions below, and the window opens at 1600×900 with the UI scaled
to the window size (so it stays readable at 1440p). Run it by opening
`build/assets/godot/` in Godot 4.7 and pressing Play, or from a shell:

```
godot --path build/assets/godot                    # map picker
godot --path build/assets/godot -- --t3-map Inn    # straight into one map
```

**Map picker.** It lists every exported map: the `t3_maps.json` index plus
any `<Map>/<Map>.tscn` found by scanning the project. It shows the map's
English name, its file and its actor count. Type to filter, move with
Up/Down/PageUp/PageDown, and press Enter or double-click to load. Loading
runs in the background (`ResourceLoader.load_threaded_request`) with a
progress bar.

**In a map**, the camera starts at the default player start, or above the
map's bounds if there is none. The default bindings (the help overlay reads
the live input map, so edits in Project Settings show up there):

| Action | Default keys |
|---|---|
| Move | W A S D, or the arrow keys |
| Down / up | Q / E, Ctrl / Space, PageDown / PageUp |
| Look | hold the right mouse button, or press C to capture the mouse |
| Fast / slow | hold Shift (×4) / Alt (×0.25) |
| Base speed | mouse wheel (the HUD shows speeds in m/s) |
| Inspect | left click at the cursor, or I at the cursor or crosshair |
| Focus the camera on the selection | F |
| Next player start | P |
| View: lit / unlit / wireframe / cycle | 1 / 2 / 3 / V |
| Lamps (the map's own lights) on/off | L |
| Lighting: editor / game / flat (see below) | K |
| Markers for actors without geometry | M |
| Help overlay | F1 or H |
| Release the mouse, close help, then back to the picker | Esc |

The HUD shows the map name, FPS, the camera position (metres and Unreal
units), the speeds and the view state.

**Lighting.** T3 maps have no sun: they are lit by their lamps and by the
level's ambient light and fog, which the export carries over. The Godot
editor adds its own preview sun to any scene without a `DirectionalLight3D`,
so a map opened in the editor is lit differently from the game. K cycles:
- **editor** (the default): the level's environment and lamps plus a copy of
  the editor's default preview sun, so the running viewer matches the editor;
- **game**: the level's environment and lamps only, as in T3;
- **flat**: an even, bright light, for looking into dark corners.

**Inspector.** Picking needs no physics: it tests the ray against mesh
bounds, then against the triangles of the nearest candidates, plus small
coloured markers for actors without geometry. The side panel shows the
actor's class, archetype, mesh and skin, tag, attachment, position, the
material and texture stages of the surface under the cursor, and the gamesys
properties as a tree. It also has Focus and Copy JSON buttons.

`t3_pick.gd` (picking), `t3_meta.gd` (reading the node metadata) and
`actor_inspector.gd` (the panel) do not depend on the viewer, so the map
editor can reuse them.

**Scripted use.** Options after `--`:
- `--t3-selftest [--t3-map ID]` drives the picker and the viewer and exits
  with 0 or 1. It works headless.
- `--t3-screenshot PNG` (with `--t3-map ID`, or alone for the picker) saves
  a frame and quits.
- `--t3-camera x y z tx ty tz`, `--t3-view lit|unlit|wireframe`,
  `--t3-lighting editor|game|flat`, `--t3-select` and `--t3-help` set up
  that frame.

Not done yet:
- Characters (their attached parts are hidden) and particles.
- T3's own lighting model; the game lights are plain unshadowed Godot lights.
- Streaming for very large maps: a map is instanced in one go after loading.

## 7. Existing tools and documentation

- **T3Ed**, the official editor, released by Eidos/Ion Storm on 23 Feb 2005
  as `thief3editorrelease_jan2005.zip`.
  - Announcement: https://worthplaying.com/article/2005/2/23/news/22704-thief-deadly-shadows-game-editor-available-now/
  - ModDB: https://www.moddb.com/games/thief-deadly-shadows/downloads/thief-3-editor-t3ed
  - Its setup readme explains `.unr` (editor maps), `.gmp` (maps stripped
    for the game) and `.ibt` (cooked resources), and the 3ds Max pipeline
    (`.tim` export, IonShader, `.mlb` "Mat Export", Collision Maker):
    http://www.ttlg.com/dave/t3ed/t3edsetup.html (archived at
    https://web.archive.org/web/20050418233306/http://www.ttlg.com/dave/t3ed/t3edsetup.html).
  - Ion Storm's Perl utilities ship in the zip: `dumpblockfile.pl` (block
    file table and resource-type enum), and `compileschemas.pl` and
    `dumpschemanames.pl` (the sound metafile).
  - The game writes `.ibt` files itself when `WriteResourceBlockFiles=True`
    is set: https://www.ttlg.com/forums/showthread.php?t=94324
  - T3Ed can import and export `.t3d` text.
- **FleshWorks wiki (TTLG, archived)**:
  - Installing T3Ed: https://web.archive.org/web/20071109210753/http://www.ttlg.com:80/wiki/index.php?title=Installing_T3ed
  - Tips: https://web.archive.org/web/20071109210859/http://www.ttlg.com:80/wiki/index.php?title=T3ed_Tips
  - Utilities: https://web.archive.org/web/20071109211047/http://www.ttlg.com:80/wiki/index.php?title=Useful_T3Ed_Utilities
  - Static meshes in 3ds Max: https://thief.fandom.com/wiki/3dsmax/creating_a_static_mesh
  - Komag's tutorial: http://www.shadowdarkkeep.com/files/komagtutt3.htm
- **Sneaky Upgrade** (snobel), the community patch with the fan-mission
  loader and resource overrides from `Content/T3/*/DynamicallyLoaded`:
  - Readme: https://darkfate.org/files/projects/t3sneakyupgrade/Readme_1.1.11.pdf
  - Editor edition readme (`-mkibt` export of `.gmp`/`.ibt`): https://www.darkfate.org/files/projects/t3sneakyupgrade/Readme_Editor_1.1.11.pdf
- **Thief 3 File Tools** (snobel, closed source): `csc-tool`, `mlb-tool`,
  `ibt_tool` (IBT to CBT), `cubemap-tool`, and a texture extractor for
  IBT/XBT/IBD. snobel has also announced a Blender materials importer and a
  mesh-to-OBJ tool.
  - Download: https://www.moddb.com/mods/thief-3-sneaky-upgrade/downloads/thief-3-file-tools
  - Thread: https://www.ttlg.com/forums/showthread.php?t=151472
  - Map-merging thread (T3D export from a patched T3Ed): https://www.ttlg.com/forums/showthread.php?t=151942
- **Texture packs.** John P's pack patched texture names inside `.ibt` files
  so the game loads loose DDS files
  (https://www.ttlg.com/forums/showthread.php?t=101276). Current packs use
  Sneaky Upgrade overrides instead.
- **UELib / UE Explorer** (Eliot van Uytfanghe):
  https://github.com/EliotVU/Unreal-Library.
  - Builds `Thief_DS` (95/133) and `DeusEx_IW` (95/69), with generation
    `Flesh`. The build match is exact, so maps with licensee 107–132 are not
    detected.
  - It reads the extra summary DWORD, the "LinkedData" object block, the
    UClass display name, and the extra UProperty fields: Ion flags and the
    inherited/runtime-instantiated id.
  - Its README says "LinkedData not supported" and it cannot write.
  - Support was added in PR #17 (https://github.com/EliotVU/Unreal-Library/pull/17)
    and commit https://github.com/EliotVU/Unreal-Library/commit/4f8800733f7ca16e180631065c7f317e84f60995.
- **UE Viewer / UModel** (Gildor) supports neither game: its compatibility
  table lists both as "unsupported". Gildor on DX:IW in 2010: "too custom"
  (https://www.gildor.org/smf/index.php?topic=449.0).
- **Unreal package format references**:
  - Unreal Wiki: https://beyondunrealwiki.github.io/pages/package-file-format.html
  - Antonio Cordero, *UT Package File Format*: https://archive.org/details/ut-package-file-format
- **Other tools**:
  - DXTool (DX:IW tweaker with T3 texture extraction): https://www.moddb.com/games/deus-ex-invisible-war/downloads/dxtool
  - Shadowspawn's TIMtoE (`.tim` to `.E`): https://web.archive.org/web/20250109010707/http://www.angelfire.com/games4/shadowspawn/TIMtoE.zip
  - aluigi's QuickBMS `.csc` Ogg carver: https://web.archive.org/web/20230429105251/https://zenhax.com/viewtopic.php?t=6986

As far as we could find, there is no public open-source parser for `.ibt`,
`.tim` or `.mlb`, nor for the Flesh object layout beyond UELib's script
support. The tools in `tools/assets/` fill that gap.

## 8. Toward a Godot map editor

### Interchange

Keep two representations of a level:

1. **Canonical: the JSON actor list** (`<Level>.actors.json`, to be versioned
   as a schema). It records per actor:
   - export name and index, class, archetype;
   - transform in Unreal units;
   - instance gamesys properties, typed by id;
   - tagged properties and links;
   - an opaque copy of the undecoded native tail, so an edit can be written
     back without understanding everything.
2. **A view: the `.tscn`**, rebuilt from the JSON and the shared assets. The
   editor edits nodes; a Godot `EditorPlugin` writes changes back into the
   JSON using the `t3_*` metadata as keys.

Assets (meshes, textures) should move from per-level folders into a shared,
content-addressed library (`res://t3/meshes/<name>__<skin>.glb`,
`res://t3/textures/<name>.png`). The kernel bundle is loaded with every
level, and the levels share most props.

A Godot import plugin (`EditorImportPlugin` for `.gmp`) is possible but would
mean porting the parsers to GDScript or C#. The Python converter plus a
GDScript editor plugin is simpler and keeps one implementation.

The editor plugin should offer:

- An archetype palette with names, from `t3gamesys.py json`.
- An inspector for gamesys properties: types, categories, descriptions and
  enum values from the `t3props.py` table.
- Skin selection per mesh.
- Light previews.

### Getting edits back into the game

From least to most work:

1. **Runtime patching through T3SDK.** A mod DLL reads a "map patch" (moved,
   added or removed actors and property overrides, keyed by export name)
   when a level loads, and applies it through engine functions (spawn, set
   location). This needs no file writer and fits the SDK's direction, but it
   needs `ULevel::SpawnActor` and the property accessors reverse-engineered
   (see [engine.md](engine.md)).
2. **In-place `.gmp` patching.** Changing an existing actor's
   Location/Rotation/DrawScale or a gamesys value, or adding and removing
   exports, means re-serialising those objects. It also means updating the
   export table's sizes and offsets, the Level's actor list, the extra table
   (identity lists), and the generation counts. Everything outside the
   touched objects can be copied verbatim. Feasible now for transforms and
   property edits.
3. **Through T3Ed.** Export `.t3d` text that T3Ed imports, then build with
   the official pipeline (or with Sneaky Upgrade's `-mkibt`), which produces
   a consistent `.gmp` + `.ibt`. This is the most robust way to get new BSP,
   zones and portals, navigation meshes and lighting. It needs a T3Ed
   install, and our understanding of T3D for Flesh actors.
4. **New resources.** For new meshes and textures, either use Sneaky Upgrade's
   loose-file overrides (`DynamicallyLoaded`) or write `.ibt` files. The
   container is fully understood; the 20-byte per-entry value and the
   header value are unknown, and we must check whether the engine validates
   them.

### Milestones

1. **Round-trip safety net.** Re-serialise an unchanged `.gmp`
   byte-identically: summary, names, imports, exports, extra table, and
   objects copied verbatim. Then re-serialise edited actors.
2. **Actor editing.** Transforms, skins and gamesys values edited in Godot,
   written into a copy of the `.gmp` under `build/`, and tested in the game
   (with the user's go-ahead).
3. **Decode the rest of the level.**
   - The BSP render-block index and zone and portal data (for culling and
     editing).
   - The navigation mesh.
   - LinkDataObjects (attachments, trigger scripts).
4. **Assets.**
   - Skeletal meshes and animations (from the `.ibt`, or the T3Ed `.psk`/`.psa`).
   - Havok hulls for collision in Godot.
   - Emitters, the sky cube (UTX) and sounds (`.csc`).
5. **Lighting fidelity.** A T3-like light and shadow preview in Godot.
6. **Authoring new geometry.** Either BSP through T3Ed/T3D, or static
   meshes plus hand-made or generated zones, portals and nav meshes. This is
   the hardest part, because T3 bakes zones, portals and navigation at build
   time.

### Risks

- **Undocumented Ion Storm structures.** The Level object's middle part,
  zones and portals, the navigation mesh, trigger scripts, Havok 2 hulls and
  skeletal data are all custom. Some of it will need static analysis of
  `T3Main.exe` (the Ghidra project in this repo).
- **Build-time data.** BSP render blocks, zone visibility, navigation meshes
  and shadow data are compiled by the editor. Structural edits (new rooms)
  require regenerating them, so reusing T3Ed's build (item 3 above) may be
  unavoidable.
- **Validation in the engine.** Hashes in `.ibt`, the extra table and the
  summary DWORD at 0x24 may be checked when loading.
- **Licensee drift.** Maps span licensee versions 107–133. `Entry.gmp`
  (107) already has a different actor tail.
- **Legal.** Assets stay local. Nothing extracted may be committed or shared.

## 9. Open questions

- The DWORD at 0x24 in map summaries, and the purpose of the 32 export-index
  lists.
- The first 13 bytes of the Level object, and everything after the BSP
  polygon list.
- What indexes the BSP render blocks (block ids look like node or surface
  indices). What the 92-byte BSP polygons are for, and their flag.
- The unit of `LightRadius` (assumed feet), and how T3 maps `LightBrightness`
  to intensity.
- Material stages 2–7 and the three material colours.
- Texture `usage detail` values.
- The per-skin flags and the mesh flags of static meshes. The numeric field
  in the `StaticMesh` proxy objects.
- Whether the 20-byte values in `.ibt` headers and entries are checked, and
  how they are computed.
- The native tail of `Entry.gmp` actors (licensee 107).
- The header "triangle count" that disagrees with the index count in a few
  meshes.

## 10. Tool reference

All tools live in `tools/assets/` and use the standard library only. They
find the game with `--game-dir`, then `$T3_GAME_DIR`, then the installer's
registry value. They write only under `build/assets/`.

| Tool | Purpose |
|---|---|
| `inventory.py` | Survey the install: formats, counts, sizes |
| `upkg.py summary\|names\|imports\|exports\|classes\|dump\|json <pkg>` | Unreal packages. `dump` shows an object's tagged properties, named gamesys blocks and links |
| `ibt.py list\|stats\|parts\|extract <map or .ibt>` | Block files. `parts` shows a resource field by field |
| `t3texture.py list\|export\|materials <map>` | Textures to DDS/PNG, material table |
| `t3mesh.py list\|info\|export <map>` | Static meshes to glTF (`.glb`) |
| `t3bsp.py stats\|export <map>` | BSP render blocks to glTF |
| `t3props.py table\|scripts\|enums` | Gamesys property table, UnrealScript source dump |
| `t3gamesys.py list\|show\|json` | Archetypes and their resolved properties |
| `t3map.py <map>\|--all [--json-only] [--scale S]` | Level to JSON + Godot scene |
| `godot_check.py [--godot EXE] [--viewer [MAP]] [--viewer-shot PNG] [--render ...]` | Import and check the Godot project, run the viewer self-test, save preview frames |
| `godot/viewer/*.gd` | The map viewer (picker, fly camera, HUD, help, inspector), installed into the project by `t3map.py` |
| `selftest.py` | Checks the parsers and writers against synthetic data only (no game files needed) |
