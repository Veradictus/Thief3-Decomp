# How the game works

An orientation to Thief: Deadly Shadows' engine, for modders and curious
players: what it is built from, what one session looks like from launch to
the main menu, and where to read about each part of it in more depth. The
detailed, address-level references this section draws on are linked
throughout, and listed together at the end of this page.

## The big picture

`T3Main.exe` runs on Ion Storm's own fork of an early Unreal Engine 2,
shared with Deus Ex: Invisible War. Underneath, it is recognisably Unreal:
objects, names, classes and packages (see [objects.md](objects.md)) all work
the stock way. On top of that, Ion Storm built its own systems specific to
this game:

- a Dark Engine-style **property system** ("gamesys") for the values
  placed objects carry, layered onto Unreal's own tagged properties (see
  [gamesys.md](gamesys.md));
- a native **window/UI system** for menus and the HUD, independent of
  Unreal's usual widget system (see [display.md](display.md));
- Havok physics, with configurable rates for the player's and the AI's
  controllers (see [architecture.md](architecture.md));
- and, notably, **no network layer at all** — stock Unreal Engine 2's
  client/server code has been stripped out, leaving only vestiges (see
  [architecture.md](architecture.md)).

[architecture.md](architecture.md) surveys every subsystem this project has
looked at, marking each fact as known or not known yet.

## One session, from Steam to the menu

Steam launches the game through a small chain of executables:
`runme.exe` → `t3.exe` → `T3Main.exe` (see [target.md](../target.md)). Only
`T3Main.exe`, the last of these, is this project's target; the other two,
and the copy-protection check next to them, are out of scope.

Once `T3Main.exe` is running, start-up brings up the object and name
systems, loads the core packages, and — unless skipped — plays the intro
logo movies before reaching the main menu. The menu itself is a level like
any other (`Entry.gmp`), just one with no meshes or lights of its own; its
player controller is `Entry.Camera__0` (see [objects.md](objects.md)).

## Why every level change restarts the process

This is probably the single most surprising fact about how the game runs:
**New Game, and every mission boundary, restarts `T3Main.exe` from
scratch.** The outgoing process shows a loading screen for the next level,
hands off to a small helper, `Ion Launcher.exe`, and exits; the launcher
starts a brand new `T3Main.exe` with the destination level on its command
line. There is no in-place level transition at all.

[runtime.md](runtime.md) walks through this handoff in full, including the
loading-screen timing and how the new process finds the right
`PlayerStart` (see also [levels.md](levels.md)). It matters for modding
because anything held only in memory — including a mod's own state — does
not survive a level change unless the mod saves and restores it itself.

## A guide to this section

| Page | Covers |
|---|---|
| [Architecture](architecture.md) | Every subsystem, and what is and is not known about it. |
| [Objects, names, classes and packages](objects.md) | `UObject`, `FName`, classes, packages, and what a mod's object API can see. |
| [Gamesys and archetypes](gamesys.md) | The property system placed objects use, and how map edits change it. |
| [Levels](levels.md) | What is inside a level, player starts, and the complete map list. |
| [The install and its files](files.md) | The install's folder layout and each file type's role. |
| [Configuration](config.md) | The INI files, the Options table, and what T3SDK overrides. |
| [Runtime](runtime.md) | The main loop, the clock, focus loss, level-change restarts, and exit. |
| [Display](display.md) | Resolutions, fullscreen versus a window, the cursor, and the UI/HUD layout systems. |
| [Console commands](console.md) | The `Exec` commands known from the code and the executable's strings. |

For the underlying evidence, see [engine.md](../engine.md) (addresses and
status), [assets.md](../assets.md) (file formats and the Godot export),
[target.md](../target.md) (the binary itself) and [handoff.md](../handoff.md)
(project status). For modding itself, start at
[the mod author cookbook](../modding/cookbook/index.md).
