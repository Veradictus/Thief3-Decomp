# Reverse engineering a function

How to go from a string, an import or an address to an understanding of what
a piece of `T3Main.exe` does, in the order people actually use it. This page
is about finding and confirming facts; write them down as you go following
[naming.md](naming.md).

You need the workbench from [setup.md](setup.md), at least its Ghidra
database, before any of this.

## Start from something you can find

You rarely start from a blank address. Something already points at the
function or global you want:

- **A debug-name string.** Ion Storm gave many global `TArray`s a debug name,
  so the exe carries 209 strings like `"UObject::GObjLoaded"` or
  `"UClass::ClassReps"`. Each one sits next to a small, recognisable
  construction sequence: push the name string, push the element size, `mov
  ecx, <the global>`, call the `TArray` constructor. Search for the string,
  read the `mov ecx` operand next to its reference, and you have the
  global's address (see the Names section of [engine.md](../engine.md) for
  the pattern and 209-string count). Most of the `G`-prefixed globals in
  `symbols.txt` were found this way.
- **An import.** `T3Main.exe`'s import table
  ([target.md](../target.md#what-is-linked-in)) is small and stable:
  Direct3D 8, DirectInput 8, DirectSound, Win32, plus Bink and EAX
  delay-loaded. Anything that calls `Direct3DCreate8` or `ShellExecuteExA`
  is worth a look.
- **A config key.** Ion Storm's own INI layer (not Unreal's `GConfig`) is
  read through `Config::GetFloat`, `GetBool`, `GetString` and `Find` (the
  Configuration section of [engine.md](../engine.md)). A section or key name
  (`[Physics]`, `AssumedUIScreenWidth`) is a string too, and finding its
  readers tells you what feature it controls.
- **A known address.** You may already have one: a vtable slot next to a
  function you understand, a call target from a disassembly you're reading,
  or a function queued by [`next.py`](../../tools/agent/next.py) for
  matching (see [first-match.md](first-match.md), which needs a name only in
  the loose sense the queue already gives it, not a full understanding).

## Decompile and disassemble

```sh
python tools/ghidra_headless.py script tools/ghidra/Decompile.java <addr>
python tools/ghidra_headless.py script tools/ghidra/Decompile.java refs:<addr>
python tools/ghidra_headless.py script tools/ghidra/Disassemble.java <addr>
python tools/ghidra_headless.py script tools/ghidra/Disassemble.java <addr>+<count>
```

[`Decompile.java`](../../tools/ghidra/Decompile.java) prints Ghidra's
decompilation of the function containing each address you give it. Prefix an
address with `refs:` instead to decompile every function that *references*
that address (up to 12): this is how you read every caller of a global or an
import in one go, instead of following each reference by hand.
[`Disassemble.java`](../../tools/ghidra/Disassemble.java) prints raw
instructions the same way, or `<count>` instructions starting at an address
that isn't a function's entry point; it annotates any `call` with the
callee's name. Both run read-only against the database `bootstrap` built;
neither needs the game running.

Treat the decompilation as a starting point, not the answer: it is Ghidra's
guess at source, and it is often wrong about types, signed-ness or which
local belongs to which loop. Cross-check it against the disassembly and
against [techniques.md](techniques.md) for how MSVC 7.1 actually compiles
things.

## Read MSVC 7.1 and UE2 code

The disassembly follows patterns specific to this compiler and this engine
fork more than it follows general x86 idiom: calling conventions and their
decorated names, vtable calls, the `/GX` exception-handling frame, and
Unreal's `FName`/`TArray`. [techniques.md](techniques.md) collects these with
what they look like in the disassembly, so this page doesn't repeat them.

## Confirm a guess

A decompilation or a disassembly is a hypothesis until something independent
agrees with it. Two documented examples:

**The `TimeManager` clock.** The trail started with a symptom: above 100 fps
the game looked choppy, "as if stuck at 60 fps". `[Physics]
PlayerControllerFPSrate=60` in `Default.ini` was the obvious suspect, so its
reader came first. The player's physics controller constructor
(`0x10B8C4D0`) reads it through `Config::GetFloat` and stores 1/60 s, and the
only method that uses that value (`0x10B8C690`) returns `min(dt, step)`: a
cap on each step, not an update rate. A plausible guess, disproved by
reading the code. The real answer came from the main loop: `MainLoop`
(`0x10C95BE0`) brackets every frame with `BeginFrame` and `EndFrame` on one
singleton and passes the resulting delta to `GEngine->Tick`. The same
singleton's getter (`TimeManager::Instance`, `0x10D3EBE0`) and `SetPaused`
(`0x10D3ED00`) had already turned up in the viewport's focus-loss handler,
where the SDK calls them at runtime to keep a borderless game running, which
is what makes those two verified. Reading `EndFrame` then explained the
symptom: below the minimum step (0.01 s, set by the constructor at
`0x10D3EB80` with `MOV [ESI+4], 0x3C23D70A`) it advances nothing and carries
the time over to the next frame. See the Clock section of
[engine.md](../engine.md) for the field layout.

**The level-change relaunch.** The game restarts itself on every level
change. In the code, `appRequestExit(1)` leads to a function that presents
three black frames, draws the next level's loading screen, then calls
`ShellExecuteExA`. The call's own arguments and the strings around it say
what it is: `Ion Launcher.exe` next to the exe, a command line built as
`T3MAIN.exe <display> "dummy" <URL> <arguments>`, and a wait for a window
whose class and title are `Ion Launcher`. The confirmation came from
outside the exe: Ion Launcher writes its own log
(`Documents\Thief - Deadly Shadows\Launcher.log`), and after a New Game it
shows exactly that command line arriving and the new `T3Main.EXE` it
starts. That runtime record is what justifies naming `0x10901D60`
`RelaunchForLevelChange` and marking it verified; see
[engine.md](../engine.md#game-loop-and-exit).

Look for the same kind of independent second source before you upgrade a
guess: another caller, a string, a config key, or a struct layout already
pinned down in [`sdk/include/t3sdk/unreal.hpp`](../../sdk/include/t3sdk/unreal.hpp).

## Evidence levels

[engine.md](../engine.md) records every address with one of two labels, and
this handbook uses them the same way:

- **Static**: inferred from the executable's code, data, strings or PE
  metadata. It has not necessarily been observed at runtime. Most results
  from decompiling or disassembling alone are static.
- **Verified**: observed in a live game run, as recorded in the project's
  status notes. Turning a static guess into a verified one is what the next
  section is for.

The SDK's own runtime checks (the UObject layout validation it does before
`EngineReady()`) are a third, narrower thing: they confirm a couple of
specific, load-bearing facts (`UObject::Outer`, the `UStruct::SuperField`
chain) every time the game starts, but they don't prove any other address or
field in the document. Don't cite "the SDK's runtime checks" as evidence for
something they don't actually check.

## Test a theory with an SDK hook and the log

When reading code isn't conclusive, you can make the running game tell you.
The SDK already does this throughout: `Config::GetFloat`,
`FOutputDeviceFile::Serialize`, `Window::PlacedPosition` and
`UWindowsViewport::ViewportWndProc` are hooked, and `appRequestExit` was
hooked while the level-change handling was worked out. Their evidence is
marked verified in [engine.md](../engine.md) for exactly this reason. A
hook that exists but has not run in the game yet stays "static". The pattern
is the same one those hooks use: hook the candidate function (or its
caller), log its arguments or return value, deploy, run the game, and read
`System/T3SDK.log`. [sdk.md](../sdk.md) has the build, deploy, log and
`tools/sdk.py` commands; [techniques.md](techniques.md) covers how to choose
between an import-table hook and MinHook for the function you're testing.

> [!IMPORTANT]
> Ask before deploying into the game folder or launching the game, and close
> the game after each test — this is a working agreement of the whole
> project, not just this page.

Once you can state a fact with its evidence level, record it: continue to
[naming.md](naming.md).
