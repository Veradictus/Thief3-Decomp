# Architecture

An overview of `T3Main.exe`'s subsystems: Ion Storm's Unreal Engine 2 fork
plus Ion's own additions on top of it. Each section lists what is known,
with a link to the detailed evidence, and what is not known yet.

Addresses are absolute (the exe has no relocations and always loads at
`0x10900000`); see [target.md](../target.md) for the build they hold for.
Full evidence and status labels ("static" inferred from code or data,
"verified" observed in a live run) are in [engine.md](../engine.md), which
this page summarises.

## Core objects and names

Every engine entity is a `UObject`, tracked in a global array, and every
object has a name (`FName`) drawn from a global name table.
[objects.md](objects.md) covers both in detail.

**Known:** the `UObject` fields used at runtime (index, hash chain, Outer,
Name, Class), the global object and name tables and their sizes at the main
menu (about 6,000 objects, 9,800 names), and that `FName` here carries an
instance number printed as `Name__N`, unlike stock Unreal Engine 2.

**Not known yet:** the meaning of most `ObjectFlags` bits, and
`UObject::GObjInitialized`.

## The Config/INI layer

A singleton (`Config::Instance`) reads Ion Storm's own INI files by section
and key, with optional per-platform suffixes (`__p`, `__x`, `__t`). It is
not Unreal's `GConfig`. Details, the file list and notable sections are in
[config.md](config.md).

**Known:** the lookup functions (`Config::Find`, `GetBool`, `GetFloat`,
`GetString`) and that T3SDK intercepts `GetFloat` to rescale the UI for
widescreen.

**Not known yet:** the full set of sections and keys; only the ones observed
in code or in the SDK's own use are documented.

## The window/UI system

Menus, popups and the HUD are native window objects (`WindowManager`,
`Window`) laid out from `System/T3UI.ini` and read at a fixed design size of
640x480. [display.md](display.md) covers placement, anchors and the HUD.

**Known:** the `Window` fields used for placement and modality, the
`PlacedPosition` placement arithmetic for each anchor, and the layout
constants (640x480 design size, 95 degree UI camera field of view).

**Not known yet:** the full window class hierarchy and how input events are
dispatched beyond the two event codes the SDK's menu diagnostics log.

## The Direct3D 8 renderer

The game creates one Direct3D 8 device (`InitDirect3D`, hardware then
software vertex processing) and keeps it in a viewport
(`UWindowsViewport`). [display.md](display.md) covers the modes, VSync and
the hardware cursor; [console.md](console.md) covers the viewport's own
console commands.

**Known:** the device creation and reset path, the present parameters
structure, the resolution and colour-depth options, and why an exclusive
fullscreen device survives a focus loss that would freeze a windowed one
(`UD3DRenderDevice::Lock`'s device-lost wait).

**Not known yet:** the render pipeline beyond device management: draw calls,
the `FleshShader` vertex/pixel shaders baked into the kernel bundle, and the
per-pixel lighting and stencil-shadow model [assets.md](../assets.md) notes
is missing from the Godot export.

## The TimeManager clock

A singleton (`TimeManager::Instance`) that `MainLoop` brackets every frame
with, and the sole source of each frame's game-time delta.
[runtime.md](runtime.md) covers the main loop and the clock's minimum-step
behaviour in full.

**Known:** its main fields and setters (listed in [engine.md](../engine.md)),
the 0.01 s minimum and 0.1 s maximum step, and the `SIMTIME` console
command's subcommands.

**Not known yet:** how the clock interacts with animation playback beyond
the player and AI controller rates below.

## Gamesys and archetypes

Ion Storm bolted a Dark Engine-style property system onto Unreal: every
placeable actor's properties can be serialised as small tagged blocks
instead of (or alongside) Unreal's own tagged properties.
[gamesys.md](gamesys.md) covers this in full; the byte-level format is in
[assets.md](../assets.md).

**Known:** the block-id encoding (type in the high 16 bits, property id in
the low 16), the type-to-UProperty-kind mapping, and that archetypes
(`D_<n>` classes in `T3Gamesys.t3u`) let a map actor store only the
properties it overrides.

**Not known yet:** a few property types are not yet writable by the map
editor (structs, arrays, object references), and the extra per-package table
`assets.md` describes is not understood.

## Flesh

"Flesh" is Ion Storm's name for the object-serialisation fork shared with
Deus Ex: Invisible War (per the UELib project's build name for this format).
It extends Unreal's package and object format rather than replacing it.

**Known:** the package summary's extra fields (an extra DWORD, two DWORDs
after the generations, an extra table between the import and export
tables), that every struct value serialises as a tagged property list, and
the gamesys property blocks appended after Unreal's own tagged properties
(all documented in [assets.md](../assets.md)).

**Not known yet:** the purpose of the extra summary DWORD and the extra
table's per-package lists; the first 13 bytes of the `Level` object and most
of what follows its BSP polygon list; what indexes the BSP render blocks.

## Physics (Havok) and controller rates

Havok 2 (`hkWorld.cpp`, `hkCollidable.cpp` and other source paths appear in
assert strings, per [target.md](../target.md)) provides collision and rigid
body physics, in a `GamePhysics` package (per the same page's package-name
evidence). Above it, the player's and the AI's controllers have configurable
rates.

**Known:** the player's physics controller caps its step size to
`1 / [Physics] PlayerControllerFPSrate` (60 by default) without changing how
often it updates, and AI controllers store four fixed rates for behaviour
tiers: Running (30), Basic (15), Minimal (5) and Off (2), all as `1/rate`
values.

**Not known yet:** everything about the Havok integration itself; physics
hulls (`PhysicsHull` block-file resources) and ragdolls are not decoded (see
[assets.md](../assets.md)).

## AI

The `AICore` package (per [target.md](../target.md)) holds the AI code. The
four controller-rate tiers above suggest that an AI pawn's rate depends on
how active it is, but how the tiers are chosen and used is not known yet.

**Known:** essentially only the above; the `AICore` package's existence and
the rate tiers are the extent of what has been reverse-engineered.

**Not known yet:** everything about AI behaviour: perception, alert states,
patrols and scripting.

## Sound (EAX)

Creative's EAX extends DirectSound with hardware-accelerated environmental
reverb; the game delay-loads `eax.dll` (per [target.md](../target.md)).

**Known:** the Options table has `UseEAX`, `EAXMultipleEnvironments` and
`UseHWMixing` entries (see [config.md](config.md)); `reverbstyles.ini`
configures reverb presets; sound content ships in Ion Storm's own metafile
format (`SchemaMetafile_*.csc`, described in [assets.md](../assets.md)).

**Not known yet:** the runtime sound engine: schema playback, 3D positioning
and how EAX environments are chosen or switched.

## Movies (Bink)

RAD Game Tools' Bink codec plays the intro logos and cutscenes; the game
delay-loads `binkw32.dll` (per [target.md](../target.md)).

**Known:** `PlayIntroMovies` (`0x10A50C30`) plays the start-up logo movies
and nothing else, so T3SDK's `SkipIntros` fix simply returns from it early;
video content ships as 23 `.bik` files (see [files.md](files.md)).

**Not known yet:** movie playback elsewhere in the game (cutscenes between
missions, if any use the same path).

## UnrealScript

Placeable classes and gameplay logic are written in UnrealScript, Unreal
Engine 2's own bytecode language, compiled into the script packages
(`System/*.t3u`). [objects.md](objects.md) covers packages and classes.

**Known:** the packages are file version 95, licensee version 133, and still
contain their UnrealScript source as a `TextBuffer` object per class (see
[assets.md](../assets.md)); 254 native `exec*` function names are registered
in the executable (per [target.md](../target.md)).

**Not known yet:** the bytecode interpreter and `UObject::ProcessEvent`, the
function that dispatches a script event, have not been located (tracked in
[handoff.md](../handoff.md)'s roadmap as a step toward multiplayer).

## The absent network layer

Stock Unreal Engine 2 ships a client/server network layer; this fork does
not.

**Known (static):** there are no `NetDriver`, `ActorChannel` or level
travel strings and no Winsock imports anywhere in the executable. What
remains are only vestiges: `IpDrv.dll` is referenced, and `RemoteRole`,
`Replication` and the `UClass::NetFields`/`ClassReps` containers still exist
as engine plumbing, apparently unused. A multiplayer mod needs its own transport; see
the roadmap in [handoff.md](../handoff.md).
