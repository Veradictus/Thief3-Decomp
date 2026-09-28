# Techniques and patterns

Patterns worth recognising on sight in `T3Main.exe`'s disassembly, each with
what it looks like and how to confirm it. Most of the codegen detail here
comes from the compiler idiom sheet,
[`CHEATSHEET.md`](../../.claude/skills/t3-match/CHEATSHEET.md), which this
page summarises rather than repeats; read it in full before matching a
function ([first-match.md](first-match.md)).

## `__thiscall` and `__fastcall`, and hooking them

A `__thiscall` member function takes `this` in `ECX` and everything else on
the stack; its decorated name looks like `?Get@W@@QBEHXZ` for
`int W::Get() const`. A `__fastcall` function puts its first two integer or
pointer arguments in `ECX` and `EDX`, decorated with a `Y I` in place of
`YA` (`?Fast@@YIHHH@Z` for `int Fast(int, int)`). Both clean up their own
stack arguments, like `__stdcall` (`?Std@@YGHHH@Z`): a function that takes
arguments on the stack ends in `ret N` (`ret 0x4` for one). Only `__cdecl`,
the default for free functions (`LoadingScreen::Begin`, for example), leaves
the cleanup to the caller, which shows as `add esp, N` after the call.

Most of what the SDK hooks is `__thiscall`: `FOutputDeviceFile::Serialize`,
`Config::GetFloat`, `Window::PlacedPosition` (see
[engine.md](../engine.md)). Hooking one means your replacement has to
receive `this` (and, for a `__fastcall` target, the first two arguments) in
the same registers the original did — declare your hook function with a
matching calling convention rather than relying on the stack layout you'd
expect from a plain C function, or the object pointer arrives corrupted.
`Window::PlacedPosition` is a sharper case still: it's a vtable slot that
returns a pointer its caller uses directly, so a detour on it must return
that same pointer, not a copy.

## Vtables and their slots

A virtual call looks like `mov eax, [ecx]; call dword ptr [eax+4*slot]`
(reading the vtable pointer, then a slot in it); `delete v` through a
virtual destructor calls slot 0 specifically (the "scalar deleting
destructor"). The D3D8 interfaces are a documented, numbered example: the
SDK's cursor code hooks `IDirect3DDevice8`'s `SetCursorProperties`,
`SetCursorPosition` and `ShowCursor` at slots 10, 11 and 12, and the log
device's own one-slot vtable (`0x10E47648`) is what
`FOutputDeviceFile::Serialize` sits behind (see [engine.md](../engine.md)).

There are two ways to hook a slot. The SDK reads the function pointer out of
the slot and hooks that function with MinHook (`HookVirtual` in
[`sdk/loader/display.cpp`](../../sdk/loader/display.cpp)), which catches
every caller, whichever vtable or pointer they came through. The other way is
to overwrite the pointer at `vtable + 4*slot`, which only affects calls made
through that vtable. Either way, a slot is often the only handle you have on
a function that nothing else names, like a Direct3D method inside the
system's `d3d8.dll`.

## Unreal's FName and TArray

`TArray<T>` is `{ T* Data; int32 Num; int32 Max; }`, 12 bytes, exactly as
stock Unreal Engine 2 has it — confirmed twice over in this exe, since both
`FName::Names` and `UObject::GObjObjects` match the layout (see
[`sdk/include/t3sdk/unreal.hpp`](../../sdk/include/t3sdk/unreal.hpp), which
declares it with `static_assert(sizeof(TArray<int>) == 12)`).
[reverse-engineering.md](reverse-engineering.md) covers how to *find* one of
these globals from its debug-name string; this is what you're looking at
once you have.

`FName` is one 32-bit value, not a struct: the low 16 bits index
`FName::Names`, and the high 16 bits are an instance number — Ion Storm's own
change, since stock Unreal Engine 2 uses a plain index with no instance
number. A non-zero number N prints as `<name>__<N-1>`, which is why you'll
see names like `Camera__0` in the game rather than a bare `Camera`. The
entry itself (`FNameEntry`) puts its ANSI text at offset `0x1C`, also
`static_assert`ed in `unreal.hpp`.

`FString` is Unreal's dynamic string type and, by convention elsewhere in
UE1/2, would be a `TArray<char>`. Nobody has pinned down an address or
confirmed that shape in this codebase yet — treat that as an open question,
not a fact to copy from another engine's headers.

## MSVC SEH prologues

A function with a local that has a destructor gets an exception-handling
frame under `/GX`: it chains itself onto `fs:[0]` with a pushed handler
stub, then tracks which locals are alive with `esp`-relative state stores (a
`dword` write for the first construction and the final `-1`, `byte` writes
for the states in between as objects come and go). The funclets that
actually run the destructors, and the handler itself, are emitted separately
in `.text$x`, after all ordinary code; their tables go to `.xdata$x`. See
[`CHEATSHEET.md`](../../.claude/skills/t3-match/CHEATSHEET.md) for the exact
instruction sequence.

The one fact worth remembering while writing a candidate: **declaration
order is construction order, and construction order decides which local
gets which stack slot.** If your rows differ only in which slot holds which
object, swap the declarations instead of changing anything else.

## Config reads as a way to find code

`Config::GetFloat`, `GetBool`, `GetString` and `Find` (see
[engine.md](../engine.md)) are called with a literal section and key string,
so a function that calls one is doing exactly what its arguments say. This
works backwards from strings, too: grep the exe for a known `.ini` key or
section name and look at what references it. That's how the player physics
controller's use of `[Physics] PlayerControllerFPSrate` was found, and ruled
out as the cause of the game's choppiness before `TimeManager` turned out to
be the answer; the worked example in
[reverse-engineering.md](reverse-engineering.md) tells the story.

## Patching an immediate

Not every fix needs a hook. The SDK's `SmoothFrames` option changes
`TimeManager`'s minimum frame step from 0.01 s to 0.001 s by overwriting the
constructor's own immediate operand in the running process —
`MOV [ESI+4], 0x3C23D70A` at `0x10D3EB9E` — rather than hooking the
constructor or `EndFrame`. The constructor's logic is untouched; only the
constant it writes changes. The main menu's version label works the same
way: [`sdk/loader/menu.cpp`](../../sdk/loader/menu.cpp) swaps the operand of
one `push <format string>` (at `0x10B28E28`) for its own format string. Both
check the instruction's bytes first and leave the game alone if they differ. This only works when you can point at one exact
instruction and its encoding, and it only ever changes a value, never
behaviour — for anything more than a constant, you need a real hook.

## MinHook versus import-table hooks

The SDK uses both, for different reasons.

- **Import-table patches** ([`sdk/loader/iat.cpp`](../../sdk/loader/iat.cpp))
  for functions the exe imports from Windows DLLs: `Direct3DCreate8`,
  `PeekMessageA`, `ExitProcess`, `TerminateProcess`, `ShellExecuteExA`,
  `ShowCursor` and `SetCursor` (see [target.md](../target.md) for the import
  list). The exe calls these through its import address table, so replacing
  one slot catches every call the exe makes, with no trampoline and no change
  to any code. Calls made by other modules (the Direct3D runtime, say) go
  through their own tables and are not caught.
- **MinHook's inline trampolines** for code inside the exe, which has no
  import slot: `FOutputDeviceFile::Serialize`, `Config::GetFloat`,
  `Window::PlacedPosition`, `UWindowsViewport::ViewportWndProc`,
  `LoadingScreen::Begin`, the intro-movie player and the main menu's input
  functions. The same goes for Direct3D's device methods, found through their
  vtables (above): they live in the system's `d3d8.dll`, and every caller
  must be caught.

Check [target.md](../target.md)'s import list first. If your target is on
it and only the exe's own calls matter, an import-table patch is simpler and
safer than an inline hook; if it isn't, MinHook is the only option.

## Why the image base is fixed

`T3Main.exe` ships with its relocation table stripped — no `.reloc` section
at all (see [target.md](../target.md)) — so it can only ever load at the
address it was linked for, `0x10900000`. That's why every address in
[engine.md](../engine.md) and in this handbook is written as a fixed,
absolute number rather than an offset from some base: there is only one base
it will ever have, on the supported build. It's also why the loader checks
the PE timestamp before doing anything else (see
[CLAUDE.md](../../CLAUDE.md)) — a different build of the exe, even a minor
patch, could move every one of these addresses, and there would be no
relocation table to tell you it happened.
