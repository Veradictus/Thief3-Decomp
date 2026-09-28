# Gamesys and archetypes

The property system placeable objects use for the values a mission builder
sets on them: lights, meshes, AI, triggers. This page explains the concept;
[assets.md](../assets.md) has the on-disk byte format this is drawn from,
and the [mod author cookbook](../modding/cookbook/objects.md) and its
[map edit recipes](../modding/cookbook/maps.md) show how to read and change
these values from a mod or from the map editor, respectively.

## What the property system is

Thief: Deadly Shadows bolts a Dark Engine-style property system onto
Unreal's own. Where stock Unreal Engine 2 stores an actor's non-default
values as tagged properties (name, type, value, repeated until `None`), Ion
Storm's engine additionally supports small, densely-encoded **gamesys
property blocks**: `id, 1, size, data[size]`, terminated by an id of zero.
UnrealScript declares which properties get this treatment with an explicit
numeric id, for example a mesh reference declared
`var(Render) inherited(<id>) ... ObjectMesh` or a float declared
`var runtimeinstantiated(<id>) float DrawScale`.

A block's id is not arbitrary: `(type << 16) | property id`, where the type
bits identify the UProperty kind the property was declared as (object
reference, string, struct, float, int, bool, byte or enum, name, dynamic
array, or bitfield). Engine-owned properties such as `StaticMesh` and
`DrawScale` carry an additional flag marking them `runtimeinstantiated`.
With this encoding, a reader that has parsed the UnrealScript source once
can name and type almost every block it sees without touching the compiled
class data at all: `tools/assets/t3props.py` does exactly that, building a
table of about 1,130 properties from the script source inside the game's
own `.t3u` files, and with it over 99.8% of the gamesys blocks in the
retail maps get a name.

Two properties place a mesh in the world: **`ObjectMesh`** (a struct naming
a static mesh resource and one of its skins) and **`DrawScale`** (a uniform
scale factor — this engine has no `DrawScale3D`). Lights use `LightColor`
(brightness, hue and saturation), `LightShape`, `FleshLightType` (omni,
spot, directional, ambient or projector, with or without shadows) and
`bLightOn`.

## Archetypes

A mission builder rarely sets every property on every object by hand.
Instead, placeable things are **archetypes**: UnrealScript classes named
`D_<n>` that extend each other in a chain up to a base engine class such as
`Actor`, `Light` or `T3AIPawn`. `T3Gamesys.t3u` holds about 2,345 of them,
each carrying an Ion Storm addition on top of the stock class fields: an
`FString` display name, which is why tools can show a readable archetype
name instead of `D_4217`.

A map actor of class `D_<n>` inherits every gamesys block anywhere in its
archetype chain, and stores in the map file only the blocks where *this*
instance's value differs from the archetype's. A lamp placed in a level, for
example, need not repeat its mesh, its light colour or its shape: those
come from the archetype, and the map only records that this particular lamp
is, say, unlit or moved.

## How a level's actors carry property blocks

Inside a map package, each actor object serialises (in order): an optional
state frame, Unreal's own tagged properties, then the gamesys property
blocks described above, then link data (attachments, trigger-script links),
then a small class-specific native tail. See
[assets.md](../assets.md) for the exact byte layout. Because only overrides
are stored, most actors carry only a handful of gamesys blocks even though
their effective property set (inherited plus overridden) can be large.

## How map edits change values

The Godot-based map editor (see [assets.md](../assets.md), sections 6 and
8) reads a level, resolves every actor's effective gamesys values through
its archetype chain, and lets a mission builder change the scalar ones
(floats, ints, bools, byte enums, plain bytes, names and strings) in an
inspector panel. Structs, arrays, object references and bitfields are
read-only there today.

Saved changes go into a small JSON edits file, keyed by the actor's export
name, which `tools/assets/t3pack.py` then applies to a copy of the map:

- An actor that already overrides a changed property gets that block's
  value rewritten in place.
- An actor that does not yet override it — including an archetype instance
  relying entirely on inherited blocks — gets a **new** gamesys block
  inserted, using the block id the map already uses for that property
  elsewhere, or one built from the property's declared type if it does not.
  New blocks are inserted in ascending property-id order among the actor's
  existing ones.
- `DrawScale` is a special case: it goes into the actor's tagged properties
  or its own gamesys block, whichever the actor already has (both, if it has
  both), because an inherited gamesys block would otherwise override a
  tagged value.

Every other object in the package is copied through unchanged, and the
result is checked by reading it back before it is installed. This is how a
mission builder changes, for instance, a single lamp's brightness or a
door's open/closed state without touching anything else in the level.
