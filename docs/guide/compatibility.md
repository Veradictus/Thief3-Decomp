# Other mods and tools

How T3SDK behaves alongside the other tools Thief: Deadly Shadows players
commonly use. Where the repository has no direct evidence either way, this
page says so plainly instead of guessing.

## Sneaky Upgrade and Direct3D wrappers

T3SDK installs as `System\dinput8.dll` and only forwards DirectInput calls
on to Windows; it never touches `d3d8.dll`.
[Sneaky Upgrade](https://www.moddb.com/mods/thief-3-sneaky-upgrade) and the
Direct3D wrappers people run under it (d3d8to9, dgVoodoo2, DXVK) all work by
replacing `d3d8.dll`, so the two don't compete for the same file. T3SDK's own
Direct3D hook (for the borderless window) goes through `T3Main.exe`'s import
table rather than by supplying a `d3d8.dll` of its own — see [SDK settings
and tools](../sdk.md#settings-and-built-in-fixes) and
[Engine internals](../engine.md). That's why the two are expected to
coexist; it hasn't been confirmed by actually running them together in the
game.

Sneaky Upgrade also matters for content mods: its override folders,
`Content\T3\PCTextures\DynamicallyLoaded` and
`Content\T3\MatLib\DynamicallyLoaded`, are where most texture and material
packs for this game go, and a `.t3mod` package can ship files straight into
them (see [Installing mods](mods.md#texture-packs) and
[Content and texture packs](../modding/content-packs.md)). Those packs need
Sneaky Upgrade installed regardless of whether T3SDK is; the mod's own
description should say so.

## Widescreen and field-of-view patches

`WidescreenUI` (on by default) re-lays-out the game's menus and HUD for your
screen's aspect ratio, but it doesn't change the 3D field of view during
play — a true widescreen (Hor+) fix for that hasn't been found yet (see
[Handoff: next steps](../handoff.md#next-steps)). If you also use a
separate field-of-view patch, how it works matters: a tool that edits
`T3Main.exe` itself, such as the community's `T3FovPatch.exe`, changes the
very file T3SDK checks the identity of at start-up. T3SDK only hooks the one
exact supported build (Steam, patch 1.1); on a file that no longer matches
it, it disables itself and leaves the game to run exactly as it would
without T3SDK (see [Unsupported builds](troubleshooting.md#unsupported-builds)).
It doesn't undo the FOV patch, or refuse to start the game — it just doesn't
load. Steam's **Verify integrity of game files** puts back the original
`T3Main.exe` if you'd rather have T3SDK.

## ReShade

ReShade wraps the game's own rendering API rather than `dinput8.dll`, so
installing it alongside T3SDK doesn't clash by file name. Beyond that, this
project documents nothing about ReShade specifically, and the combination
hasn't been tried: T3SDK also hooks Direct3D 8's device creation and reset,
through `T3Main.exe`'s import table, for the borderless window (see
[Engine internals](../engine.md)), and whether that gets along with
ReShade's own hooks is untested. Treat it as unverified rather than assume
either way, and say so if you try it and hit a problem.

## The Steam overlay

The game always starts through Steam, whether you click **Play** in the
launcher or in Steam itself (see [Playing with T3SDK](playing.md#install-and-remove)),
so the overlay attaches the same way with or without T3SDK. T3SDK adds no
file that Steam itself uses, and it hooks nothing before `T3Main.exe` is
already running. Whether the overlay's own rendering hook interacts with
T3SDK's borderless-window and cursor fixes hasn't been checked either way.

## Other `dinput8.dll` mods

T3SDK's own loader is `System\dinput8.dll` — the one file a game like this
only has room for one of. Installing T3SDK when another tool's
`dinput8.dll` is already there does nothing: install refuses to overwrite a
file it didn't put there itself, and copies nothing rather than guess which
one you meant to keep (see [Playing with T3SDK](playing.md#install-and-remove)).
The reverse holds too: dropping in another `dinput8.dll`-based tool after
T3SDK is installed overwrites T3SDK's own file, outside the launcher's
knowledge. Only one such tool can be active at a time; remove one before
installing the other.

## What isn't covered here

If a tool you use isn't listed above, this project has no specific
information about it. As a general rule (not a guarantee): a tool that only
adds its own files alongside the game, under a different name, is unlikely
to clash; a tool that also wants to be `System\dinput8.dll`, or that patches
`T3Main.exe` itself, will run into T3SDK for the reasons above. When in
doubt, ask in the [Taffer Tavern on Discord](https://discord.gg/hdAXH73tEG)
— someone may already have tried the combination you're asking about.
