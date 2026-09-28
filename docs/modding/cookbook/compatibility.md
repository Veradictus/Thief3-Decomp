# Play well with other mods

A player may run your mod alongside several others. None of them coordinate
directly with each other — plan for that instead of assuming your mod is
alone in the process.

## Hooks: expect to lose the race sometimes

Every mod, and a few of T3SDK's own built-in fixes, share one hook table
(see [Hook a game function](hooks.md)). `CreateHook` fails with
`MH_ERROR_ALREADY_CREATED` when the address is already taken, by another mod
or by T3SDK itself. There is no way to ask who holds it, or to reserve it in
advance:

```cpp
int status = api->CreateHook(target, reinterpret_cast<void*>(&Detour), reinterpret_cast<void**>(&original));
if (status != 0) {
    api->Log("could not hook the target (MH_STATUS %d); continuing without it", status);
    // fall back, or return 1 from T3Mod_Init if the feature is essential
}
```

Decide, per hook, whether losing it is something your mod can work around
(log it and skip the feature) or a reason to refuse to load outright (return
non-zero from `T3Mod_Init`, after removing any hook you already created —
see [The mod lifecycle](../lifecycle.md)).

## Load order decides who goes first

Packaged mods run in the launcher's order (`load-order.txt`), then loose
DLLs by file name. Load order decides:

- which mod's `T3Mod_Init` runs first, and so which one wins a contested
  hook;
- which mod's `files/`/`textures/` file wins when two provide the same path
  (later wins).

Declare `requires` and `conflicts` in `mod.json` so the launcher can order
and check your mod correctly, instead of hoping players get it right by
hand; see [Packaging](../packaging.md) and [Mod packages](../../mods.md).

## Check the API version, not just your own build

Set `mod.json`'s `api` to the lowest `T3SDK_API_VERSION` your mod actually
needs, and guard any call added after version 1 with the size check in
[The mod lifecycle](../lifecycle.md). A player with an older T3SDK than the
headers you built against should only see a warning if your mod truly
cannot run without a newer call.

## Don't assume you are the only mod touching the engine

Frame and log callbacks from every loaded mod, and the game itself, share
the same engine state. T3SDK isolates callback *crashes* — one mod's
faulting callback does not stop another's (see [Debug a mod](debugging.md))
— but it does not isolate their *effects*: if your hook changes something
another mod or the game reads, that change is visible everywhere. Prefer
calling through to `original` unless replacing the call outright is the
point, and keep a hooked function's contract (its return value, what it
writes through its pointers) intact for whoever else calls it — including
T3SDK itself, for the few functions it calls directly (see
[Hook a game function](hooks.md)).

## There is no mod-to-mod API

T3SDK connects mods to the game, not to each other: as of API version 1
there is no call to find another mod or exchange data with it. If your mod
genuinely depends on another one's features, say so with `requires` in
`mod.json` so the launcher enforces the order and presence, and have that
other mod expose whatever it offers itself — its own exported functions, its
own file format, and so on. T3SDK neither helps nor prevents that, and it is
untested here.

## Reference

- [Hook a game function](hooks.md), [The mod lifecycle](../lifecycle.md),
  [Packaging](../packaging.md), [Mod packages](../../mods.md).
