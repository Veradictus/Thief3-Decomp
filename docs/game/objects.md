# Objects, names, classes and packages

How the engine represents everything alive at runtime: objects, their names,
their classes, and the packages they load from. This is the concept page;
[engine.md](../engine.md) has the addresses and evidence, and
[the mod author cookbook](../modding/cookbook/objects.md) has recipes for
working with objects from a mod.

## UObject

Every engine entity — an actor, a class, a package, a texture reference —
is a `UObject`. All live objects sit in one global, growable array
(`UObject::GObjObjects`), and a second array (`GObjAvailable`) tracks freed
slots for reuse. A per-object hash table (`GObjHash`, bucketed by the
object's name) speeds up lookup by name.

The fields the SDK relies on, at their known offsets:

| Offset | Field | What it is |
|---|---|---|
| `0x00` | vtable | |
| `0x04` | Index | the object's slot in `GObjObjects` |
| `0x08` | HashNext | the next object in this name's `GObjHash` bucket |
| `0x18` | Outer | the object this one is nested in (a class's package, an actor's level) |
| `0x1C` | ObjectFlags | bit flags; not mapped yet (see below) |
| `0x20` | Name | an `FName` (below) |
| `0x24` | Class | the `UClass` object describing this object's type |

The first 0x28 bytes match stock Unreal Engine 2 exactly, with one
exception: this fork inserts one extra field before `SuperField` (below), so
everything from there on is shifted by four bytes relative to stock UE2.
Rather than trust a fixed offset for `Outer`, the SDK finds it at start-up by
searching for the known object `Core` (a `Package`) among every live
object's candidate `Outer` fields; it does the same for `SuperField` by
checking which offset chains at least 95% of class objects up to the class
named `Object`. This is why `Outer` and `SuperField` are marked "verified"
in engine.md while nearby fields are only "static, probable": the SDK's own
start-up check, not just static analysis, confirms them on the user's
executable. A test run found 4,488 objects and 287 classes once the core
packages are loaded, growing to about 6,000 objects and 9,800 names at the
main menu.

`ObjectFlags` is not mapped yet: its offset is only "static, probable", and
neither the SDK nor this documentation relies on any of its bits.

## Names (FName)

An `FName` is a single 32-bit value, not a pointer: the low 16 bits index a
global table of interned strings (`FName::Names`), and the high 16 bits are
an **instance number**. This is Ion Storm's own addition — stock Unreal
Engine 2 packs an FName as a plain index with no instance number. A non-zero
number *N* displays as `<name>__<N-1>`; for example, the player controller
at the main menu is named `Camera__0` (class `Engine.Camera`). This lets many
objects share one interned string (`PlayerStart`, `StaticMeshActor`, ...)
while still having distinct, human-readable names.

Each interned string is an `FNameEntry`: an index, a hash-chain pointer, a
flags word (bit `0x1000` suppresses log output tagged with this name), the
highest instance number seen so far, a per-number flags array, and the ANSI
text itself. `FName::Names` starts small and grows as new strings are
interned; nothing currently removes entries from it.

## Classes and the SuperField chain

A class is itself a `UObject`, an instance of the class named `Class` (which
is its own class — the usual Smalltalk-style knot at the root of an
object model). Every class object has a `SuperField` pointing at its parent
class, and following that chain from any class eventually reaches the root
class, `Object`. The SDK validates this at start-up (above); in a test run,
all 287 loaded classes chained up to `Object`.

`SuperField` sits at offset `0x2C` here, one field later than stock Unreal
Engine 2's `0x28`, consistent with the one extra field noted for `UObject`
above. Each class also keeps a pointer to its own default-property object at
offset `0xE8` (static, probable; not runtime-checked).

## Packages: `.t3u`, maps, and what is a package

A package is a `UObject` of class `Package`, and also the file that
serialises a set of objects together (name, import and export tables, plus
Ion Storm's own additions — see [assets.md](../assets.md) for the on-disk
format). Three kinds exist in the install:

- **Script packages** (`System/*.t3u`): compiled UnrealScript classes. Nine
  ship with the game (`Core`, `Engine`, `Fire`, `AICore`, `T3AI`, `T3Game`,
  `T3Gamesys`, `T3Player`, `Editor`), all file version 95, licensee version
  133. They still hold their UnrealScript source as a `TextBuffer` object
  per class.
- **Legacy texture packages** (`Content/T3/UTX/*.utx`): older Unreal package
  versions (61 through 95) carried over, mostly for particles, the sky cube
  and HUD art.
- **Maps** (`Content/T3/Maps/*.gmp`): a level is a package too, whose
  objects are its actors, its `Level` object, and the BSP `Model`. See
  [levels.md](levels.md).

All of this is the stock Unreal package format with Ion Storm's fields
layered on (an extra summary DWORD, a GUID and generations, and an extra
table between the import and export tables); [assets.md](../assets.md)
has the byte layout and what is and is not understood about the extra
fields.

## What the SDK's object API sees

Mods only reach engine objects once `EngineReady()` returns true, and only
through a small, deliberately generic API (`sdk/include/t3sdk/t3sdk.h`):

- `ObjectCount()` / `ObjectAt(index)` — the live count and a slot in
  `GObjObjects`.
- `FindObject(className, pathName)` — a linear search by class name and full
  path name (below).
- `ObjectClass(object)` / `ObjectOuter(object)` / `IsA(object, class)` — the
  fields above, plus a `SuperField` walk for `IsA`.
- `ObjectName(object)` / `ObjectPathName(object)` — an object's own name, or
  its full path.
- `NameToString(name)` — turns a raw `FName` value (as stored in a `T3Object`
  field, for instance) into text.

A **path name** is every `Outer` from the outermost object down to this one,
joined with `.`: the main menu's player controller is
`Entry.Camera__0` — the level package `Entry`, then the object itself. This
matches the pattern Unreal's own logs and error strings use.

The SDK does not expose property access, spawning or script calls yet; see
the roadmap in [handoff.md](../handoff.md) for what that needs
(`UObject::ProcessEvent`, `ULevel::SpawnActor`). For gamesys property
values specifically, see [gamesys.md](gamesys.md). For recipes that read or
change objects from a mod, see
[the mod author cookbook](../modding/cookbook/objects.md).
