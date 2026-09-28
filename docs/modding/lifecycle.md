# The mod lifecycle

When each part of a mod runs, on which thread, and what it may touch. The
rules come from the comments in
[`t3sdk.h`](../../sdk/include/t3sdk/t3sdk.h); the
[API reference](../reference/api.md) lists every call.

## From start to exit

1. **T3SDK starts.** The game loads `System\dinput8.dll`, and T3SDK starts
   before the game's own start-up code. It checks the game build (on any
   other build it stops here, and no mod is loaded), installs its fixes and
   hooks, and loads the mods: the packaged mods in the launcher's load order,
   then loose DLLs in `System\mods` by name.
2. **`T3Mod_Init` runs**, once per mod, in load order, before the engine
   exists. Keep the API pointer, check the API version, register callbacks
   and create hooks. Don't use the object functions yet: they return 0 or
   `NULL` until the engine is ready. Return 0 to stay loaded. Any other value
   (or a missing `T3Mod_Init`) unloads the DLL, and T3SDK removes the
   callbacks it registered.
3. **The engine starts.** Engine log callbacks receive the engine's log lines
   from the start, before the engine is ready.
4. **The engine is ready.** Once the engine's objects exist and T3SDK has
   checked their layout, `EngineReady()` returns non-zero and T3SDK logs
   `engine ready`.
5. **Frames.** Frame callbacks run once per pass of the game's message loop,
   on the main thread, from the first time `EngineReady()` is true. The game
   waits for them, so keep them short.
6. **The game exits.** When the game begins exiting, `EngineReady()` returns
   0 again and frame callbacks stop. Object pointers you kept may now be
   freed. When the process ends, T3SDK calls each mod's optional
   `T3Mod_Shutdown`, in reverse load order.

## Threads

- `T3Mod_Init`, frame callbacks and `T3Mod_Shutdown` run on the game's main
  thread.
- Engine log callbacks run on whichever thread wrote the log line. Protect
  any state they share with a frame callback (a critical section, or an
  atomic flag), and do engine work in the frame callback instead.
- T3SDK does not make engine objects safe to use from other threads. Use
  them from frame callbacks only.

## Objects and memory

- `T3Object*` pointers, and the object functions, are only good while
  `EngineReady()` holds. Look objects up again rather than keeping pointers
  across the game's exit.
- Text comes back through your own buffers. Each text function returns the
  full length, like `snprintf`, so a call with `NULL` and 0 tells you the
  size to allocate:

  ```cpp
  char name[256];
  size_t length = api->ObjectPathName(object, name, sizeof name);
  // length >= sizeof name means the text was cut short
  ```

- Nothing allocated on one side of the API is freed on the other.

## Hooks

`CreateHook` replaces a function of `T3Main.exe` with your detour and gives
you a trampoline that calls the original. The hook stays off until
`EnableHook`:

```cpp
using SomeFn = int(__cdecl*)(int);
static SomeFn original;

static int __cdecl Detour(int value) {
    return original(value) + 1;
}

// in T3Mod_Init; 0x10A00000 stands for a real function address from docs/engine.md
void* target = reinterpret_cast<void*>(0x10A00000);
if (api->CreateHook(target, reinterpret_cast<void*>(&Detour), reinterpret_cast<void**>(&original)) == 0) {
    api->EnableHook(target);
}
```

- Hooks can be created in `T3Mod_Init`: the game's code is there from the
  start, even though the engine is not running yet.
- Addresses are fixed because the game has one supported build, and T3SDK
  loads no mods on any other. [Engine internals](../engine.md) lists the
  known addresses with their evidence.
- The detour must match the target's calling convention. For a `__thiscall`
  method, MSVC mods can use `__fastcall` with an unused second parameter
  (`edx`).
- Every mod and T3SDK share one hook table, so a function can be hooked only
  once. `CreateHook` returns an error (`MH_ERROR_ALREADY_CREATED`) when
  someone else got there first. T3SDK hooks a few engine functions itself;
  `engine.md` marks them "hooked".
- If `T3Mod_Init` fails after it created hooks, remove them before it
  returns: T3SDK removes a failed mod's callbacks, but not its hooks.

## Errors

- An exception in a frame or log callback is caught. T3SDK logs it with your
  mod's name and switches that callback off; the game and other mods go on.
- The same holds for `T3Mod_Shutdown`.
- `T3Mod_Init` is not guarded in the same way: a crash there ends T3SDK's
  start-up, and later mods do not load. Keep it simple.
- Don't let C++ exceptions leave a callback.

## API versions

`api->version` is the API version the installed T3SDK implements, and
`api->size` the size of its function table. The table only grows. A member
added after version 1 is usable when `api->size` covers it; the
[API reference](../reference/api.md) says which version added each member.

```cpp
#include <cstddef>

// NewCall stands for any member added after version 1.
bool hasNewCall = api->size >= offsetof(T3SdkApi, NewCall) + sizeof api->NewCall;
```

Set `api` in your package's `mod.json` to the lowest version your mod needs;
the launcher warns when the installed T3SDK is older (see
[Packaging](packaging.md)).
