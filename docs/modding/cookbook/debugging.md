# Debug a mod

Work out why a mod did not load, is not doing what you expect, or crashed
the game.

## Check it loaded

`T3SDK.log` records every load attempt. Look for `mod <name> loaded`; if it
is missing, look earlier for why:

- `mod <name>: no T3Mod_Init export` — the DLL does not export `T3Mod_Init`
  under that exact name. Check that `T3SDK_EXPORT`/`T3SDK_CALL` are on the
  function, and that the mod is a 32-bit DLL.
- `mod <name>: T3Mod_Init returned N; unloading` — your own code returned
  non-zero; T3SDK also removes any callbacks you registered before this.
- `mod <name>: LoadLibrary failed (error N)` — the DLL itself did not load.
  Look up `N` as a Windows error code; a common cause is a missing
  dependency, or a 64-bit DLL in this 32-bit process.

A mod's name here is its package folder name, or a loose DLL's file name.

## Watch it run

- Call `api->Log` freely; see
  [Write to the log, and read the engine's own lines](logging.md).
- Set `T3SDK.ini`'s `[T3SDK] Console=1` for a live window instead of tailing
  the file (see [SDK use and settings](../../sdk.md)).

## A callback misbehaved

If a frame or engine log callback throws, T3SDK catches it, logs a line
naming your mod, the exception code and where it happened, and switches off
just that one callback; your mod's other callbacks, and the game, continue.

`T3Mod_Init` is not guarded this way: a crash there ends T3SDK's start-up
(the log says `exception 0x... during start-up; SDK left partially
initialised`), and mods later in the load order do not load at all. See
[The mod lifecycle](../lifecycle.md) for the exact rule; keep `T3Mod_Init` to
registering callbacks and creating hooks, nothing that can fail
unpredictably.

## The game crashed

`T3SDK.log` gets a report for the first faults in the process: the faulting
instruction and every recognisable return address on the stack, each tagged
`T3Main.exe+offset` (game code), `T3SDK+offset` (the loader) or
`mod <name> (address)` — so a fault inside your own DLL is named directly,
by address. This is a report, not a safety net: T3SDK always lets the game
go on to handle the fault as it would without the SDK, which usually still
means it closes (see [SDK use and settings](../../sdk.md)).

A hook detour that reads or writes through a bad pointer crashes exactly
like any other engine bug, and shows up the same way (see
[Hook a game function](hooks.md)).

## Attach a real debugger

A mod is an ordinary DLL loaded into `T3Main.exe`, so you can attach Visual
Studio (or WinDbg) to the running game once it has started: **Debug > Attach
to Process**, then pick `T3Main.exe`. Build with debug information (CMake's
`RelWithDebInfo` or `Debug` configuration) and keep the `.pdb` next to your
DLL — copy the loose DLL and PDB straight into `System/mods/` while you
work, rather than testing through a packaged `.t3mod` (which never includes
a PDB unless you pack with `--with-pdb`; see [Packaging](../packaging.md)).
Set breakpoints in your own source once the debugger has attached.

Two things to know. Mods load at start-up, before you can attach, so
`T3Mod_Init` has already run by then: log from it instead of breaking in
it. And every level change starts a new `T3Main.exe` (the game restarts
itself; see [How the game works](../../game/index.md)), so after New Game
or a mission change, attach again to the new process.

## Reference

- [Write to the log, and read the engine's own lines](logging.md),
  [Hook a game function](hooks.md).
- [The mod lifecycle](../lifecycle.md): the full error-handling rules.
- [SDK use and settings](../../sdk.md): `T3SDK.ini`'s `Console` key, and the
  crash report format.
