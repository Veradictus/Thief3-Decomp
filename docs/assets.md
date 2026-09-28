# Thief: Deadly Shadows assets and levels, and their export to Godot

This document covers how Thief: Deadly Shadows (T3) stores its levels and
assets, what the prototype tools in `tools/assets/` already export, and a plan
for a Godot 4 map editor built on them.

> **Personal use only.** These tools read and convert data from your own,
> legally owned copy of the game so that you can mod it. Extracted and
> converted assets (everything under `build/assets/`) are copyrighted game
> content: do not redistribute them and never commit them. The tools read
> the install; only `t3pack.py install` and `restore` and `t3texpack.py apply`
> and `restore` write to it (a patched map or bundle, after backing up the
> original once). They do not touch DRM and do not launch the game.

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
- **Works on synthetic data, untested on real maps.**
  - Editing: an editor plugin records moved, rotated and scaled actors and
    changed gamesys values in the Godot editor (section 6), and `t3pack.py`
    writes them into a patched copy of the map and installs it, backing up
    the original (section 8).
  - Texture replacement: `t3texpack.py` rebuilds `.ibt` bundles with
    textures from DDS files, for texture packs (section 3).
- **Not decoded yet.**
  - Skeletal meshes, animations, Havok physics shapes, trigger scripts,
    particle emitters, sounds.
  - Zones and portals, and the navigation mesh.
  - The index structure around the BSP render blocks.
  - Adding and removing actors, and new geometry.

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
- Width and height, then width and height again (0 for some environment
  maps).
- Total mip bytes.
- Two bytes (the second is 1 for render targets).
- Per mip: level, width, height, size, an alignment-padding part, and the
  data part.

The fields before the first mip take 39 bytes. `t3texture.py` writes a DDS
directly and decodes DXT1/3/5 in pure Python to PNG; `texture_parts()` writes
a parsed texture back part for part, and `parse_dds()` reads DDS files for
texture replacement (below).

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

### Writing block files

`ibtwrite.py` re-serialises a block file read by `ibt.py`. An unchanged file
comes out byte-identical, and resources can be given new parts:

- **Kept as they are**: the header's magic, alignment and 20-byte value, and
  in every entry the 20-byte value, the type, the whole 263-byte name field
  (anything after the NUL included) and the load filter. The writer does not
  know what the 20-byte values are and never recomputes them. If the engine
  checks them against the data, a rebuilt bundle will not load.
- **Rewritten**: the header's data start, data size, largest resource size,
  largest part size and part count; each entry's offset, size, padding,
  first part and part count; the part table.
- The data area is copied verbatim apart from the replaced resources.
  Resources keep their order in the file, and when one changes size
  everything after it moves by a multiple of the alignment.

What the writer assumes, taken from the reader's view of the format:

- Offsets are absolute file offsets, and data start + data size is the file
  size.
- A resource's padding is the smallest that makes size + padding a multiple
  of 0x800; its bytes are zero, and the next resource starts right after it.
- The data start is the size of the header and tables rounded up to 0x800,
  and the bytes before it are zero. When the part table grows past that
  boundary, the data start and every offset move up to the next multiple of
  0x800.
- The two "largest" header fields are the largest resource and the largest
  part. The writer keeps them in step with the data, since a loader may size
  a buffer by them. A value that does not match (none is expected) is kept,
  and only raised when the new data needs more.
- Part ranges follow the table order. The writer only needs them not to
  overlap; entries that share their data are replaced together.

Irregular files still round-trip: gaps and non-zero padding are copied, and
an empty resource's offset follows its neighbour. `t3texpack.py --selfcheck`
(below) tests each assumption on the retail bundles and prints any that does
not hold.

### Replacing textures

`t3texpack.py` replaces texture resources by name with DDS files. It serves
the `textures/` folder of a mod package ([mods.md](mods.md)):

```
t3texpack.py list [<map or .ibt>] [--json]         names, format, size, mips, usage, bundles
t3texpack.py check --pack <dir> [--pack <dir> ...]
t3texpack.py apply --pack <dir> [--pack <dir> ...] [--dry-run]
t3texpack.py restore [--dry-run]
t3texpack.py --selfcheck [<map or .ibt> ...]
```

**Encoding** turns a DDS into a type-8 resource, the inverse of
`t3texture.parse_texture()`:

- The DDS must be DXT1, DXT3 or DXT5 (by FourCC), or 32-bit A8R8G8B8 or
  X8R8G8B8 (by the pixel-format masks; BGRA bytes). It needs power-of-two
  sides and a full or partial mip chain from the top level. DX10 headers,
  DXT2/DXT4, other masks, luminance formats, cube maps, volumes and trailing
  bytes are refused with the reason.
- Taken from the DDS: format, width, height, the mip count and the mip data.
- Kept from the original resource: version, usage, usage detail and the two
  bytes. The second width and height follow the first when they were equal
  in the original, and are kept otherwise (the zeros of environment maps).
- Derived, as assumptions:
  - mip levels are numbered from 0;
  - "total mip bytes" is the sum of the mip data sizes;
  - padding parts are zero bytes.
- **The padding rule is not known** from the engine. The candidates are
  "align each mip's data to N bytes" (N a power of two up to 4096), counted
  from the start of the resource or from the first mip header (byte 39).
  Every mip of a full chain constrains the rule, so the textures of a bundle
  pin it down. For each bundle the tool takes the rule that explains the
  most textures; a tie (a bundle of single-mip textures) goes to the rule
  that explains the most textures in all the bundles. A texture whose own
  original does not follow the rule is not replaced. If the engine computes
  the padding itself rather than using the part table, a wrong rule would
  make it read the wrong bytes, so the selfcheck prints the rule and how
  many textures it explains.

**Packs.** A pack is a mod folder with a `textures/` folder, or a folder of
DDS files. Each `<name>.dds` replaces every texture resource named `<name>`
(case-insensitively) in every bundle of `Content/T3/Maps`, the level bundles
and the `Kernel_*` and `MainMenu_*` ones. Later packs win. `check` reports
unknown names, unreadable DDS files, names given twice and textures whose
layout cannot be rebuilt as errors. It warns when a texture's format or
aspect ratio differs from the original's, or when it is larger. `list` and
`check` read a patched bundle's original from its backup.

**Apply and restore** write into the game; everything else stays under
`build/assets/`:

- Each affected bundle is backed up once to `build/assets/backup/` and
  rebuilt from that original, never from a patched file. The rebuild is read
  back before it is installed: `ibtwrite.compare_bundles()` checks every
  other resource, and each new texture must parse and read back as the DDS.
  The game's file is replaced through a temporary file.
- `build/assets/backup/t3texpack.json` records each patched bundle: the
  original's and the installed file's size and SHA-256, the recipe (pack
  file hashes, the padding rule and the encoder version), and which pack
  file replaced each texture. A bundle whose recipe and file are unchanged is
  skipped, so running `apply` again does nothing.
- A bundle patched before and no longer affected is restored. With no packs,
  `apply` is `restore`. A restored bundle's record and backup are removed.
- The record is saved before the game's file is replaced, and the file the
  game held is remembered until the new one is in place, so an interrupted
  run is recognised next time.
- A bundle that is neither the original nor the file `apply` installed was
  changed by something else (a game update, another tool). It is left alone
  and reported. Deleting its backup accepts it as the new original.
- The record names the game folder. Another install is refused until the
  first one is restored (or that folder is gone).
- Exit status: 0 done (warnings allowed), 1 a problem was reported, 2 a bad
  command line. The last line is a one-line summary, for the launcher's live
  output.

**`--selfcheck`** is the proof on real data. For each bundle (a patched
bundle's backup) it:

1. tests the writer's layout assumptions (above);
2. writes the bundle back unchanged, which must be identical;
3. finds the mip padding rule;
4. decodes every texture, exports it to DDS, reads it back and re-encodes it
   with the original as the template. The result must equal the original
   part for part; a difference names the first field that differs (for
   example "total mip bytes" or "mip padding (length)"). It also counts the
   textures whose second size equals the first, is zero, or is something
   else (a replacement keeps that last kind as it was);
5. puts every texture that matched back through the writer, which must give
   the identical file;
6. replaces one texture with a smaller and a larger one and checks that
   every other resource is intact.

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
t3_maps.json                   index of exported maps: id, title, scene, counts, default start, source
t3_tools/                      copy of tools/assets/godot/: the viewer and check scripts
addons/t3_map_editor/          the map editor plugin (enabled in project.godot)
<Level>/<Level>.tscn           the level (text scene, format 3)
<Level>/<Level>.actors.json    every actor and link object, lossless-ish, for tools
<Level>/<Level>.edits.json     changes saved by the map editor plugin (not written by the export)
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
- `t3_gamesys_types`: the value type of each of them, as JSON: the block kind
  (`float`, `int`, `bool`, `byte`, `name`, `string`, `struct`, `array`,
  `object`, `class`, `bitfield`), plus the enum for enum bytes and
  bitfields (`byte:<Enum>`).
- `t3_origin`: the actor's location, rotation and draw scale as exported, in
  Unreal units, as JSON. The map editor plugin compares against it.
- `t3_default_start` on the player start the viewer opens at: one whose
  travel destination mentions "start", else one without a destination, else
  the first.

The level root carries `t3_level`, `t3_title` (the English level name from
the install's string tables, e.g. from `LevelEnterText`),
`t3_units_per_meter` (full precision), `t3_actor_count`, `t3_source` (file
name, size and SHA-1 of the `.gmp`) and `t3_enums` (the value names of the
enums that the scene's properties use). Transforms are written with enough
digits to round-trip Godot's 32-bit floats.

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
viewer, and `--render` renders one frame of a scene. `--editor-selftest`
tests the map editor plugin (below) on a synthetic level.

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

### Map editor plugin

The project also enables an editor plugin: original GDScript in
`tools/assets/godot/addons/t3_map_editor/`, which the exporter copies to
`res://addons/t3_map_editor/`. It is the edit step of export, edit, repack
(section 8): open `<Level>/<Level>.tscn` in the Godot editor, change actors,
and save the changes as `<Level>/<Level>.edits.json` for `t3pack.py`.

- **Placement.** Move, rotate and scale actor nodes with Godot's gizmos or
  the Inspector. The plugin converts the node back to an Unreal location,
  rotator and `DrawScale`. T3 has no `DrawScale3D`: a non-uniform or mirrored
  scale is reported and not saved.
- **The T3 Map dock** (below the Inspector) shows the selected actor's class,
  archetype, mesh, its placement in Unreal units and its own gamesys
  properties. Scalar values can be edited there: floats, ints, bools (check
  box), enum bytes (list of names), plain bytes, names and strings. Structs,
  arrays, object references and bitfields are read-only, and so is
  `DrawScale` (scale the node). Edits are kept in the node's
  `t3_gamesys_edits` metadata, so they are saved with the scene;
  `t3_gamesys` keeps the exported values.
- **Changed actors.** The dock lists the changed actors (click one to select
  it) and reverts one with **Revert**. All changes go through undo/redo.
- **Save T3 edits** (dock button, or Project > Tools) writes the edits file.
  **Load** (or Load T3 edits) applies it to the scene, for example after a
  re-export: every actor in the file gets its saved state.

Only changes are written. The plugin compares each actor with its
`t3_origin` and `t3_gamesys`:

- An untouched actor never appears.
- A location component that did not move keeps its exported value exactly;
  a moved one is rounded to 0.01 units.
- A rotation is recovered from the matrix, as the inverse of the export
  (section 5). Of the rotators that give the same matrix (whole turns, and
  `(p, y, r)` or `(32768 - p, y + 32768, r + 32768)`), it takes the one
  nearest to the exported rotator, so an unchanged rotation comes back
  exactly and a changed one keeps its range. At pitch ±90° only yaw − roll
  (or yaw + roll) is defined; the exported yaw is kept.
- Float properties compare as 32-bit floats, enums by name.

Adding and removing actors is not supported yet. The dock warns about
duplicated actor nodes, nodes without T3 metadata in the actor groups and
removed actors; the edits file does not record them.

The edits file is format `t3-map-edits` version 1, described with
`t3pack.py` in section 8 ("Getting edits back into the game"). The plugin
writes gamesys values in their property's type: numbers for float, int and
byte, `true` or `false` for bool, the value's name for an enum byte (its
number if the enum has no name for it), strings for name and string. It
fills `source` from the scene root's `t3_source` and leaves it out for
scenes exported without it.

`godot_check.py --editor-selftest [DIR]` tests the plugin without game
files. It writes a synthetic level (made-up actors and a cube) into a
project at DIR (default `build/assets/editor_selftest/`) with the exporter's
own writers. Then it runs the model test headlessly (`selftest.gd`: rotator
round trip including pitch ±90°, every kind of edit, save and load), checks
the saved file with Python, and opens the level in the headless editor to
drive the dock (select, edit, save, undo, load, revert).

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
   editor edits nodes; the `t3_map_editor` plugin (section 6) records the
   changes, keyed by export name, in `<Level>.edits.json`, which
   `t3pack.py` applies to the map.

Assets (meshes, textures) should move from per-level folders into a shared,
content-addressed library (`res://t3/meshes/<name>__<skin>.glb`,
`res://t3/textures/<name>.png`). The kernel bundle is loaded with every
level, and the levels share most props.

A Godot import plugin (`EditorImportPlugin` for `.gmp`) is possible but would
mean porting the parsers to GDScript or C#. The Python converter plus a
GDScript editor plugin is simpler and keeps one implementation.

The editor plugin has a gamesys inspector for scalar values (types and enum
names come from the export). Still to add:

- An archetype palette with names, from `t3gamesys.py json`.
- Categories and descriptions from the `t3props.py` table in the inspector.
- Skin selection per mesh (needs struct values in `t3pack.py`).
- Light previews.

### Getting edits back into the game

From least to most work:

1. **Runtime patching through T3SDK.** A mod DLL reads a "map patch" (moved,
   added or removed actors and property overrides, keyed by export name)
   when a level loads, and applies it through engine functions (spawn, set
   location). This needs no file writer and fits the SDK's direction, but it
   needs `ULevel::SpawnActor` and the property accessors reverse-engineered
   (see [engine.md](engine.md)).
2. **In-place `.gmp` patching.** Done for existing actors by `t3pack.py`
   (below): Location, Rotation, DrawScale and scalar gamesys values.
   Adding and removing exports would also mean updating the Level's actor
   list and the extra table (identity lists); not done yet.
3. **Through T3Ed.** Export `.t3d` text that T3Ed imports, then build with
   the official pipeline (or with Sneaky Upgrade's `-mkibt`), which produces
   a consistent `.gmp` + `.ibt`. This is the most robust way to get new BSP,
   zones and portals, navigation meshes and lighting. It needs a T3Ed
   install, and our understanding of T3D for Flesh actors.
4. **New resources.** For new meshes and textures, either use Sneaky Upgrade's
   loose-file overrides (`DynamicallyLoaded`) or write `.ibt` files. The
   container is fully understood, and `ibtwrite.py` writes it (section 3);
   `t3texpack.py` uses it to replace textures. The 20-byte per-entry value
   and the header value are unknown, and we must check whether the engine
   validates them.

**The package writer** (`upkgwrite.py`) re-serialises a package read by
`upkg.py`. An unchanged package comes out byte-identical.

- The summary keeps its Ion fields as they are: the DWORD at 0x24, the
  GUID, and the two DWORDs after the generations. Only the table counts and
  offsets change. The last generation follows the export and name counts
  when it matched them before.
- The name, import and export tables are re-encoded from their values. A
  compact index written wider than needed keeps its width. A name that does
  not re-encode exactly is kept as raw bytes.
- The extra table is written back as its index lists (as raw bytes if it is
  not a run of lists).
- Objects that are not edited are copied verbatim, and so are bytes between
  the known regions.
- The regions keep their order in the file. When an object changes size,
  everything after it moves, and the export table's serial sizes and offsets
  follow. A missing name (a struct field such as `Roll`, a new `Tag` value)
  is appended to the name table.

**Editing an actor** re-serialises that object only; its state frame, links
and native tail are copied verbatim.

- `Location` and `Rotation` are `Vector` and `Rotator` tagged lists that
  hold only non-default fields. A changed field is overwritten, or inserted
  in declaration order (`X Y Z`, `Pitch Yaw Roll`) when absent. A field set
  back to 0 stays written: the loader reads it the same way, and nothing
  depends on knowing the default. A field that keeps the value read (0 when
  absent) is left alone.
- `DrawScale` goes into the actor's own gamesys block if it has one, else
  into its tagged property. An archetype instance (`D_*`) without its own
  block gets a block, because the inherited block would override a tagged
  value; so does an actor with neither. When an actor has both, both are
  set.
- Gamesys values: float, int, bool, byte (an enum name or a number),
  bitfield (bit names or a mask), name and string. A property the actor does
  not override gets a new block, using the block id the map already uses for
  it, else one built from the declared type. Blocks in ascending property-id
  order stay in that order. Structs (including `ObjectMesh`, so skins),
  arrays and object references are refused.

**The edits file** is what the Godot editor plugin writes (version 1):

```json
{
  "format": "t3-map-edits",
  "version": 1,
  "level": "Inn",
  "source": {"file": "Inn.gmp", "size": 1234567, "sha1": "<hex>"},
  "actors": {
    "<export name, as in the node's t3_name metadata>": {
      "location": [x, y, z],
      "rotation": [pitch, yaw, roll],
      "draw_scale": 1.0,
      "gamesys": {"<property name, as in actors.json>": value}
    }
  }
}
```

- Every key under an actor is optional, and only changed values appear.
- `location` is in Unreal units (floats). `rotation` is in rotator units
  (ints, 65536 = 360°; other numbers are rounded).
- `gamesys` values take the form `actors.json` shows (enum and bit names, or
  numbers); `prop<N>` names a property by id.
- `source` is optional (older exports lack it). When present, `apply`
  refuses a map whose size or SHA-1 differs.
- Other top-level keys are ignored. An unknown key under an actor, an
  unknown actor or an unsupported property type is an error, and nothing is
  written. `t3pack.load_edits()` checks a file and returns a normalised
  copy; `apply --dry-run` runs the whole apply and check and keeps no
  output.

**Commands** (`t3pack.py`):

```
t3pack.py roundtrip Inn | --all          re-write in memory and compare
t3pack.py apply Inn.edits.json [-o OUT] [--source X.gmp] [--dry-run]
t3pack.py install build/assets/patched/Inn.gmp [--dry-run]
t3pack.py restore Inn | --all [--dry-run]
```

- `roundtrip` prints `identical`, or the first differing offset and the
  table entry or object it is in; then it saves the rewritten package in
  `build/assets/roundtrip/`. It also re-serialises every actor through the
  editing code. For maps, it grows one actor near the middle of the file
  (an absent struct field written as 0) and checks with `upkg.py` that every
  other object is intact. It prints what the DWORD at 0x24 coincides with,
  if anything. `--all` covers every map, script package and UTX file.
- `apply` writes `build/assets/patched/<Level>.gmp` and lists each change.
  It reads the file back: every other object must be byte-identical, and
  every edited value must read as requested. When the game holds a patched
  copy and the edits were made from the original, it patches the backup.
- `install` backs the installed map up to `build/assets/backup/`, once (an
  existing backup is never replaced), then copies the patched map over it.
  `restore` copies backups back and keeps them. These two are the only
  commands that write to the game folder, and they print every copy.

To check on a real install: `t3pack.py roundtrip --all` should report every
package identical. Then move one visible prop in a small map, `apply`,
`install`, load the map in the game, and `restore`.

### Milestones

1. **Round-trip safety net.** Done: `t3pack.py roundtrip` re-serialises a
   package (summary, names, imports, exports, extra table, objects copied
   verbatim) and every actor, and passes on synthetic packages
   (`selftest.py`). Still to confirm on the retail maps.
2. **Actor editing.** Transforms, DrawScale and scalar gamesys values are
   written into a copy of the `.gmp` under `build/` (`t3pack.py apply`) and
   installed with a backup; the Godot plugin writes the edits file. Still to
   do: a test in the game (with the user's go-ahead), and skins and other
   struct values.
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
  summary DWORD at 0x24 may be checked when loading. `t3pack.py` keeps the
  DWORD, the GUID and the generations (apart from the last one's counts) as
  they were. If the DWORD depends on the layout, a patched map that changed
  size will not load. An object that stores absolute file offsets (like
  UE2's lazy arrays) would break when it moves; none is known in maps.
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
  how they are computed. A texture replaced with `t3texpack.py` and seen in
  the game answers the first half.
- The rule behind the mip padding parts of texture resources. `t3texpack.py`
  infers it per bundle, and `--selfcheck` prints it. The same run shows
  whether mip levels count from 0, whether "total mip bytes" is the sum of
  the mip sizes, and whether the block-file layout assumptions of
  `ibtwrite.py` hold (section 3).
- Whether the loader relies on the `.ibt` header's largest resource and part
  sizes (the writer keeps them in step).
- The native tail of `Entry.gmp` actors (licensee 107).
- The header "triangle count" that disagrees with the index count in a few
  meshes.

## 10. Tool reference

All tools live in `tools/assets/` and use the standard library only. They
find the game with `--game-dir`, then `$T3_GAME_DIR`, then the installer's
registry value. They write only under `build/assets/`, except
`t3pack.py install` and `restore`, which replace maps in the game folder,
and `t3texpack.py apply` and `restore`, which replace `.ibt` bundles.

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
| `t3pack.py roundtrip\|apply\|install\|restore` | Write maps back: round-trip check, edits file to a patched `.gmp`, install with a backup, restore (section 8) |
| `upkgwrite.py` | Package writer and actor editing, used by `t3pack.py` |
| `t3texpack.py list\|check\|apply\|restore`, `--selfcheck` | Texture packs: replace textures inside `.ibt` bundles with DDS files, with a backup and a record; restore. `--selfcheck` checks the writer and the encoder on the retail bundles (section 3) |
| `ibtwrite.py` | Block-file writer (byte-exact round trip, resource replacement), used by `t3texpack.py` |
| `godot_check.py [--godot EXE] [--viewer [MAP]] [--viewer-shot PNG] [--render ...] [--editor-selftest [DIR]]` | Import and check the Godot project, run the viewer self-test, save preview frames, test the editor plugin on a synthetic level |
| `godot/viewer/*.gd` | The map viewer (picker, fly camera, HUD, help, inspector), installed into the project by `t3map.py` |
| `selftest.py` | Checks the parsers and writers against synthetic data only (no game files needed); runs `selftest_texpack.py` |
