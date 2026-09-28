# Hook a game function

Replace or wrap a documented function inside `T3Main.exe` with your own code,
using T3SDK's shared MinHook table.

## Before you hook anything

- **Addresses hold only for the one supported build.** T3SDK checks the
  executable's timestamp, image size, load base and whole-file hash before
  it hooks anything at all (see [SDK use and settings](../../sdk.md)); if a
  mod loaded, you are on that build, and every address in
  [Engine internals](../../engine.md) is valid.
- **Match the real calling convention exactly**, or you will corrupt
  registers the caller still needs. Engine internals gives the convention
  where it is known; check it before you hook. In this exe free functions
  are usually `__cdecl` and C++ methods and vtable slots `__thiscall`, but
  a guess is not good enough. MSVC has no portable function-pointer syntax for
  `__thiscall`, so declare a `__thiscall` detour as `__fastcall` with an
  unused second parameter: `__fastcall` passes its first two arguments in
  `ECX`/`EDX`, `__thiscall` passes only `this` in `ECX`, so the extra
  parameter simply absorbs the register `__thiscall` leaves alone. [The mod
  lifecycle](../lifecycle.md) shows the same trick; T3SDK's own display code
  uses it for the exact function this page hooks, below.
- **Pick a target nothing else has hooked.** One hook table is shared by
  every mod and by T3SDK's own built-in fixes — a function can be hooked
  only once, system-wide. As shipped, T3SDK hooks these when their setting
  is at its default:

  | Function | Address | Hooked when |
  |---|---|---|
  | `FOutputDeviceFile::Serialize` | `0x10901780` | always (the engine log) |
  | `Config::GetFloat` | `0x10910B60` | `Display.WidescreenUI` (on by default) |
  | `Window::PlacedPosition` | `0x10A52530` | `Display.WidescreenUI` or `Display.UILayoutTrace` |
  | `LoadingScreen::Begin` | `0x109E1FC0` | `Display.Borderless` (on by default) |
  | `UWindowsViewport::ViewportWndProc` | `0x10C8B820` | `Display.Borderless` and not `Display.PauseInBackground` (both at their defaults) |
  | `PlayIntroMovies` | `0x10A50C30` | `Fixes.SkipIntros` (on by default) |
  | main-menu/popup input dispatch | `0x10B28750`, `0x10A52DD0` | `T3SDK.MenuInputTrace` (off by default) |

  This is what `sdk/loader/fixes.cpp`, `display.cpp` and `menu.cpp` hook as
  of this SDK; it says nothing about what other *mods* might already have
  hooked, which you can only discover by trying (below). Prefer a target
  outside this table for your first hook.

## The recipe

1. Declare a function-pointer type matching the target's calling convention,
   and a matching detour.
2. In `T3Mod_Init`, call `CreateHook(target, detour, &original)`. It leaves
   the hook disabled.
3. Call `EnableHook(target)` to switch it on.
4. In the detour, do your work, then call `original(...)` — unless replacing
   the call outright is the whole point — and return whatever the caller
   expects.

`TimeManager::SetPaused(bool)` is a good first target: it is `__thiscall`,
verified, and — unlike everything in the table above — never hooked or
replaced by T3SDK itself, only called directly (to undo the game's own
pause when a borderless game loses focus), so it stays free on every
install regardless of settings:

```cpp
#include <t3sdk/t3sdk.h>

namespace {

const T3SdkApi* api = nullptr;

// TimeManager::SetPaused(bool), __thiscall; address and calling convention
// from docs/engine.md's "Clock (TimeManager)" table.
using SetPausedFn = void(__fastcall*)(void* self, void* edx, bool paused);
SetPausedFn original = nullptr;

// __fastcall with an unused second parameter stands in for __thiscall: ECX
// still carries `this`, and the (unused) EDX slot is declared but ignored.
void __fastcall Detour(void* self, void* edx, bool paused) {
    api->Log("game %s", paused ? "paused" : "unpaused");
    original(self, edx, paused);
}

}  // namespace

T3SDK_EXPORT int T3SDK_CALL T3Mod_Init(const T3SdkApi* sdk) {
    if (sdk->version < T3SDK_API_VERSION) {
        return 1;
    }
    api = sdk;
    void* target = reinterpret_cast<void*>(0x10D3ED00);  // TimeManager::SetPaused, docs/engine.md
    int status = api->CreateHook(target, reinterpret_cast<void*>(&Detour), reinterpret_cast<void**>(&original));
    if (status != 0) {
        api->Log("could not hook TimeManager::SetPaused (MH_STATUS %d); continuing without it", status);
        return 0;  // not fatal: the mod still works, just without this feature
    }
    api->EnableHook(target);
    return 0;
}
```

Because T3SDK calls `SetPaused` directly by address (not through the hook
table) to keep a borderless game running when it loses focus, your hook
also intercepts *that* call, not only the game's own. Keep the detour fast and always forward to
`original` unless you mean to change whether the game actually pauses.

## When CreateHook fails

`CreateHook` and `EnableHook` return a MinHook `MH_STATUS`. Mods do not get
`MinHook.h` (it is not part of the public headers), so here are the values
that matter:

| Value | Name | Meaning |
|---|---|---|
| 0 | `MH_OK` | success |
| 3 | `MH_ERROR_ALREADY_CREATED` | another mod, or T3SDK itself, already hooked this address |
| 4 | `MH_ERROR_NOT_CREATED` | `EnableHook`/`DisableHook`/`RemoveHook` called for a target with no hook |
| 5 | `MH_ERROR_ENABLED` | `EnableHook` called on a hook that is already on |
| 6 | `MH_ERROR_DISABLED` | `DisableHook` called on a hook that is already off |
| 7 | `MH_ERROR_NOT_EXECUTABLE` | the address is not valid code |
| 8 | `MH_ERROR_UNSUPPORTED_FUNCTION` | the target's machine code cannot be hooked (rare) |
| 9 | `MH_ERROR_MEMORY_ALLOC` | MinHook could not allocate memory for the trampoline |
| 10 | `MH_ERROR_MEMORY_PROTECT` | MinHook could not change the target's page protection |

The one you will actually see in practice is `MH_ERROR_ALREADY_CREATED`: two
mods (or a mod and a built-in fix) both wanted the same function. There is
no way to ask who got there first or to reserve a target in advance — see
[Play well with other mods](compatibility.md) for how to plan around it.

## Watch out for

- **Two mods, one function, one winner.** Whichever mod's `T3Mod_Init` runs
  first — earlier in the launcher's load order, or earlier alphabetically
  among loose DLLs — gets the hook; every later `CreateHook` on that address
  fails. Handle the failure (as the example above does) rather than assuming
  you will always get it.
- **Clean up on your own failure.** If `T3Mod_Init` fails *after* it created
  a hook, remove that hook before returning non-zero: T3SDK removes a failed
  mod's callbacks automatically, but not its hooks (see
  [The mod lifecycle](../lifecycle.md)).
- **A crash in a detour is not caught.** T3SDK guards frame and log
  callbacks with an exception handler; it does not guard hooked functions,
  because they run as part of the game's own call chain, on whatever thread
  called them. A bad detour crashes exactly like any other engine bug, and
  shows up the same way in a crash report (see [Debug a mod](debugging.md)).
- **`CreateHook`'s `target` means a code address inside `T3Main.exe`.**
  Hooking something in another DLL (Direct3D, for example) is possible with
  the same MinHook mechanism T3SDK itself uses for a few things internally,
  but it is not what this call is documented for, and this page does not
  cover it.
- Only replace the call outright (pass `NULL` for `original`, or never call
  it) when you are certain nothing else depends on the original's side
  effects. Forwarding to `original` is almost always the safer choice.

## Reference

- [Mod API reference](../../reference/api.md): `CreateHook`, `EnableHook`,
  `DisableHook`, `RemoveHook`.
- [Engine internals](../../engine.md): every documented address, and its
  calling convention where known.
- [The mod lifecycle](../lifecycle.md): the hooks section, and what happens
  when `T3Mod_Init` fails.
