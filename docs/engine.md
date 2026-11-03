# Engine internals of T3Main.exe

Reverse-engineering results the SDK relies on, with the evidence for each.
All addresses are absolute: the exe has no relocation table, so it always
loads at `0x10900000`. They hold for the supported build only (PE timestamp
`0x40C8A4DA`, SizeOfImage `0x718000`; see [target.md](target.md)).

The status labels distinguish evidence types. **Static** means inferred from
the executable's code, data, strings, or PE metadata; it has not necessarily
been observed at runtime. **Verified** means observed in a live game run, as
recorded in the handoff notes. The SDK's runtime checks are a third category:
they validate selected invariants on the user's executable when it starts,
but they do not prove every address or field below. Decompile anything below with
`python tools/ghidra_headless.py script tools/ghidra/Decompile.java <addr>` (or
`refs:<addr>` for the functions that reference it); `Disassemble.java` takes
the same addresses, or `<addr>+<count>` for a run of instructions.

The names below are recorded in
[`config/PC_20040610/symbols.txt`](../config/PC_20040610/symbols.txt), the
name database (`Class::Method` until the MSVC decorated name is known). After
naming something there, run `python tools/ghidra_headless.py names` so
Ghidra's decompiles show it; `bootstrap` re-applies the names when it rebuilds
the database.

The compile-time `static_assert`s in
[`unreal.hpp`](../sdk/include/t3sdk/unreal.hpp) check the SDK compiler's own
type sizes and field offsets. They do not inspect the game binary. At runtime,
the loader accepts only the expected timestamp, image size, load base, and
whole-file SHA-1. Once engine objects exist, it searches live objects to find
`UObject::Outer`, then checks that a candidate `UStruct::SuperField` chain
reaches the `Object` class for at least 95% of class objects. These checks
cover the build identity and those two runtime-discovered offsets; other
addresses and fields remain based on the static or observed evidence shown
below.

## Finding globals: Ion Storm's named containers

Ion Storm gave many global `TArray`s a debug name. Their static initializers
look like this:

```
push offset "FName::Names"   ; name string
push 4                       ; element size
mov  ecx, 0x10F7AF1C         ; the global
call 0x109B2010              ; TArray ctor (forwards to FArray ctor 0x10AF4B90, which ignores the name)
```

The exe has 209 such `Class::member` strings (`UObject::GObjLoaded`,
`UGameEngine::Actors`, `UClass::ClassReps`, ...). Search the string, take the
`mov ecx` operand next to its reference, and you have the global.

## Names (FName)

| What | Address | Status |
|---|---|---|
| `FName::Names` (`TArray<FNameEntry*>`: Data, Num at +4, Max at +8) | `0x10F7AF1C` | verified |
| `FName::Available` (free indices) | `0x10F7AF28` | static |
| names initialised flag | `0x10F7AF18` | verified |
| `FName::NameHash[4096]` | `0x10F76F18` | static |
| `FName::StaticInit` (logs "Name subsystem initialized") | `0x10AF9FB0` | static |
| `FName::FName(const char*, EFindName)` | `0x10AF9E20` | static |
| `FName::Hardcode` ("Hardcoded name %i was duplicated") | `0x10AF9C00` | static |
| `FName::SafeSuppressed(EName)` (flag `0x1000`) | `0x10AF9A30` | static |
| name to text (formats `"%s%s%d"`) | `0x10AF9730` | static |

An FName is one 32-bit value: the low 16 bits index `Names`, the high 16 bits
are an instance number. A non-zero number N prints as `<name>__<N-1>` (the
separator `"__"` is at `0x10E49388`). Example seen in game: `Camera__0`. This
differs from stock Unreal Engine 2, where an FName is a plain index.

`FNameEntry`: `+0x00` Index, `+0x04` HashNext, `+0x08` Flags, `+0x0C` WORD
highest number, `+0x10` `TArray<DWORD>` per-number flags, `+0x1C` ANSI text
(verified).

## Objects (UObject)

| What | Address | Status |
|---|---|---|
| `UObject::GObjObjects` (`TArray<UObject*>`, Num at `0x10F3E4A4`) | `0x10F3E4A0` | verified |
| `UObject::GObjAvailable` (free slots) | `0x10F3E4AC` | static |
| `GObjHash[4096]`, bucket = `Name.Index & 0xFFF` | `0x10F3A418` | static |
| `UObject::AddObject(INT Index)` | `0x10AD4070` | static |
| `UObject::IsA(UClass*) const` | `0x10AD1EE0` | static: every `Cast<T>` instance calls it after `T::StaticClass()` |
| `UObject::ConditionalDestroy()` | `0x10AD5310` | static: logs "%s failed to route Destroy" through GError |
| `UObject::~UObject()`; its deleting destructor (vtable slot 2) | `0x10ADC750`; `0x10ADD4C0` | static |
| `UObject::operator delete(void*, size_t)`, folded with `::operator delete` | `0x10AD1DC0` | static: every native class's deleting destructor passes it the class's size |
| object iterator begin / next (per-class lists, Ion Storm addition) | `0x1096BD50` / `0x1096C8D0` | static |

Every native class's destructor is the one Unreal's `DECLARE_CLASS` writes,
`virtual ~TClass() { ConditionalDestroy(); }`: an EH frame, the class's
vtable stored, `ConditionalDestroy`, then the parent's destructor (133
functions call `ConditionalDestroy`; 103 of them are one family of 79-byte
destructors). The destructor is slot 2 of UObject's
vtable (`0x10E70A50`), not slot 0 as in stock Unreal Engine 2: slot 0 is
`Destroy()` (`0x10ADB3A0`; `ConditionalDestroy` calls it), and slot 1 is not
identified. The rest follow stock Unreal Engine 2's order: `ProcessEvent`,
`ProcessState`, `ProcessRemoteFunction`, `Modify`, `PostLoad`,
`Serialize(FArchive&)` (slot 8), `IsPendingKill`, `GotoState`, `GotoLabel`,
`InitExecution`, `ShutdownAfterError`, `PostEditChange`, two unidentified
slots (15, 16), `CallFunction`, `ScriptConsoleExec` and `Register` (19).
The argument bytes each slot's functions pop (`ret N`) agree in all 236
native tables and with these signatures. The class's deleting destructor at
slot 2 calls it, then `UObject::operator delete(this, sizeof(TClass))`;
MSVC writes it wherever it writes the vtable, so it matches from the
destructor's unit. `Cast<T>` is stock: the game keeps one
out-of-line copy per class it casts to (`Cast<AGarrett>` at `0x109E9FD0`).

`UObject` layout (the first 0x28 bytes match stock Unreal Engine 2):

| Offset | Field | Status |
|---|---|---|
| `0x00` | vtable | |
| `0x04` | Index in GObjObjects | static (AddObject) |
| `0x08` | HashNext | static (AddObject) |
| `0x18` | Outer | verified (detected at runtime) |
| `0x1C` | ObjectFlags | static, probable |
| `0x20` | Name (FName) | verified |
| `0x24` | Class | verified |
| `0x28` | `ObjectInternalPropertyHash` (Ion Storm's, `Object.uc`) | static: `UObject` registers `0x2C` bytes |
| `0x2C` | `UStruct` SuperField (on class objects) | verified: all 287 classes chain up to `Object` |
| class `+0xE8` | `Defaults` (`TArray<BYTE>`: data, then count and capacity, the class's size) | verified (reflection dump) |
| class `+0xF4` | the class's `InternalConstructor` | verified (reflection dump, `classes.txt`) |

Stock Unreal Engine 2 has SuperField at `0x28`; this fork's `UObject` is one
field longer ("Class layouts" below). The SDK re-detects Outer and SuperField
at startup instead of trusting these numbers. The checks are structural
runtime validation, not a proof that every object or class layout in this
document is correct.

Runtime numbers from a test run: 4,488 objects and 287 classes once the core
packages are loaded, about 6,000 objects and 9,800 names at the main menu. The
menu level is `Entry`, and its player controller is `Entry.Camera__0` (class
`Engine.Camera`, a `PlayerController`).

### Native class registration

Native classes register lazily rather than through stock Unreal Engine 2's
static `UClass` objects. Wherever the code needs a class, it runs the
equivalent of

    if (!PrivateStaticClass)
    {
        PrivateStaticClass = GetPrivateStaticClass(TEXT("<Package>"));
        InitializePrivateStaticClass();
    }

The getter constructs the `UClass`: its name, config name (`System`), flags
(`0x04084004`), static and internal constructors. The package name is the
getter's only argument, so every call site names the class's package. The
initializer fills in the class's `SuperField` (`+0x2C`), its own class
(`+0x24`, `Core.Class`) and its `Within` class (`+0xA4`, `Core.Object`).

| What | Address | Status |
|---|---|---|
| `GamePhysics` (package `GamePhysics`): getter | `0x10B7C5A0` | static |
| its initializer (super class from `Engine`) | `0x10B7BEF0` | static |
| its `PrivateStaticClass` | `0x10FF65D0` | static |

`tools/classify.py` reads every registration from the exe: 266 native classes,
209 in Epic's packages (Engine 164, Core 34, Fire 7, WinDrv 2, D3DDrv 1,
Window 1) and 57 in Ion Storm's (AICore 30, T3Game 11, T3Player 8, T3AI 6,
GamePhysics and T3GamePhysics 1 each). About 80 of the classes in Core and
Engine are Ion Storm's own (the `*LinkDataObject` links, `MetaProperty`,
`AISubsystem`, ...): their UnrealScript source has no Epic header. The tool
uses them to tell Ion Storm's code from Epic's ([bytematch.md](bytematch.md),
"Whose code it is").

It also writes `config/PC_20040610/classes.txt`, one line per class: C++ name
(`A` for `Actor` and its subclasses, else `U`), package, whose code, super
class, object size and class flags (the getter passes both to the `UClass`
constructor, after the name), the vtable its internal constructor stores, and
the getter, initializer and internal constructor. The super class is the first
class the initializer registers. Every native class the game's scripts declare
is there; 74 more have no script (`UClass`, the property classes, `ULevel`,
...). 22 classes share one vtable (`0x10E70A50`) and three another
(`0x10E4D808`): the linker folded identical tables. `classes.txt` also gives
each class's within class (the second class its initializer registers,
unless that is `UClass`: properties live in `UField`s, `UEnum` and `UConst`
in `UStruct`s, `UFunction` in `UState`s, `UClass` in `UPackage`s, as in stock
Unreal Engine 2), config name (always `System`), static constructor (nine
classes have their own; the rest inherit `UObject`'s empty one) and the
global its `StaticClass()` fills (`tools/classify.py classes` rewrites only
this file).

Both functions are stock Unreal Engine 2's statically linked
`IMPLEMENT_CLASS`, with one Ion Storm change in the getter. `Core.h`
declares the members (`DECLARE_CLASS`), the generated class headers declare
them in every class, and `tools/agent/classreg.py` writes and matches both
functions for each of Ion Storm's classes; 250 are in
`src/Game/<Package>Registration.cpp`:

- **The getter** (`GetPrivateStaticClass<Class>`, 192 to 196 bytes) opens a
  scope of Ion Storm's memory manager (the singleton `0x10905AA0`, slots 8
  and 9 around the allocation), then `::new(0, 0, 0, 0, 0) UClass(...)`
  through Ion Storm's placement `operator new` (`0x10905C10`, which passes the
  size and the last four arguments to the manager's slot 2 and ignores the
  second, a `const&`). Its placement `operator delete`, called by the unwind
  code if the constructor throws, is folded into `::operator delete`
  (`0x10AD1DC0`). The `::` is needed: `UObject`'s own `operator delete`
  would hide the placement one from a plain `new`, and the unwind code
  would go. The `UClass` constructor (`0x10AE7E30`) takes
  `EC_StaticConstructor`, the object size, the class flags, a zero `FGuid`
  by value, the name without its prefix letter (`&TEXT("AGarrett")[1]`), the
  package, `StaticConfigName()`, `RF_Public | RF_Standalone | RF_Transient |
  RF_Native` and the two constructors. The getters' exception code is the
  same for every class, so the linker folded their handler stubs: 14 serve
  136 getters (`symbols.txt` gives each stub every getter's name as an
  alias).
- **The initializer** (`InitializePrivateStaticClass<Class>`, 264 bytes):
  `SuperField` is `Super::StaticClass()` unless that is the class itself,
  `ClassWithin` is `WithinClass::StaticClass()`, `SetClass(UClass::StaticClass())`,
  then, once `UObject::GetInitialized()` (`0x10AD1D60`) and if the object's
  class is `UClass`, a tail call to the virtual `Register()` (slot 19). Each
  `StaticClass()` is inlined. `UBitfieldEnum`'s, in Core, reads
  `GObjInitialized` directly: its file defines `GetInitialized`.
- **`InternalConstructor`**: 22 classes whose constructor is `UObject`'s
  share one (`0x10964A80`, folded), named `UObject`'s. `classes.txt`
  therefore records `UObject`'s vtable for them; their own tables show only
  in their destructors (`UTriggerRegistrar`'s, `0x10AB3C50`, stores
  `0x10E6E178`).

`UStruct`, `UState` and `UClass` are `0x74`, `0x8C` and `0x114` bytes (the
sizes their registrations allocate); `ClassWithin` is at `0xA4`.

### Class layouts

A native class's C++ members are the variables its script declares, in order,
except two kinds:

- Ion Storm's gamesys properties, `inherited(N)` and `runtimeinstantiated(N)`:
  they live in the property database (`tools/assets/t3props.py`), not in the
  object, which is why `AActor` is only `0xC0` bytes;
- `deusexprop` variables, which exist only in Deus Ex: Invisible War's build
  of the shared code (`AController::CameraBob`).

Unreal Engine 2's property linker places the rest: bytes 1-aligned, everything
else 4-aligned (structs too, their size rounded up to 4), and a bool shares the
32-bit word of the bool member before it, gamesys properties in between
notwithstanding. Laid out this way, all 191 native classes with a script and a
super class come out at their registered size (`tools/assets/t3classes.py
check`). `UObject` is `0x2C` bytes: Ion Storm added `ObjectInternalPropertyHash`
at `0x28` after stock Unreal Engine 2's fields, so `UField::SuperField` is at
`0x2C`. `t3classes.py headers` writes the layouts as
`include/<Package>/<Package>Classes.h` (names, types and offsets, each class's
size checked at compile time). One accessor confirms a member: `AGarrett`'s
virtual at `0x10B21280` returns bit 1 of the word at `0x450`, `isCrouching`.
A string variable is an `FStringNoInit`, as in stock Unreal Engine 2's
generated headers: a destructor inlines its implicit destructor (a call to
`FString::~FString`, `0x10AF83B0`), and the unwind code calls its
out-of-line copy, `0x10BB7C00`, a jump to `~FString`.

## Script natives

The UnrealScript interpreter runs a function's bytecode through native C++
functions. `GNatives` maps each opcode or native index to one; `FFrame::Step`
reads the next opcode and calls it.

| What | Address | Status |
|---|---|---|
| native table: 254 `{"int<Class>exec<Name>", function}` pairs, the names `IMPLEMENT_FUNCTION` exports in stock Unreal Engine 2 (all `UObject`, plus `UCommandlet::execMain` with no function) | `0x10F012F8`-`0x10F01AF0` | static |
| `GNatives` (`Native[4096]`, `Native` = `void (UObject::*)(FFrame&, void*)`) | `0x10F41C08` | static (`FFrame::Step`) |
| `GCasts` (`Native[256]`) | `0x10F417F8` | static (`UObject::execPrimitiveCast`) |
| `FFrame::Step(UObject* Context, void* Result)`, `__thiscall`, out of line (stock Unreal Engine 2 inlines it) | `0x10B0FC50` | static, matched as called |
| `UObject::execPrimitiveCast` | `0x10AFDC90` | static |
| `UFunction` fields: `FunctionFlags` `+0x74`, native index (`_WORD`) `+0x78`, native function `+0x84`; `0x88` bytes | | verified (reflection dump: `Object.Abs`, native 186, `execAbs`) |

Little of this runs in Thief: Deadly Shadows: a reflection dump at the main menu (the SDK's `DumpReflectionDelay`) finds 700 classes but only 163 function objects, 157 of them `Core.Object`'s, and 221 registered natives in `GNatives`, nearly all Core's; Engine's script natives (`Spawn`, `Trace`, ...) are not registered. The table names 234 `UObject` natives in `symbols.txt`. Seven functions are
shared by two or three natives (the linker folded identical bodies, such as
`execIntZero`, `execFalse` and `execNoObject` at `0x10AFDC00`), and stay
unnamed. Fifteen natives sat inside a neighbour's range in Ghidra's export,
which never saw a function start there; see the note below.

`FFrame` (stock layout; the natives read these offsets): `+0x00` vtable
(`FOutputDevice`), `+0x04` Node, `+0x08` Object, `+0x0C` Code (the bytecode
pointer), `+0x10` Locals. A native's parameters are read by `Step`, one per
call, into zeroed locals, and `Code++` skips the end-of-parameters opcode; the
header `include/Core/Core.h` has these as the stock `P_GET_*` and `P_FINISH`
macros, which match (`execIsA`, `execAdd_IntInt`, `execMultiply_FloatFloat`,
`execNot_PreBool`).

**Functions only pointers reach.** Ghidra's export started a function only
where code flows or calls go, so a function reached only through a pointer
table (vtables, the native table) and placed right after another one's
`ret` became part of it. Data pointers to 16-byte aligned addresses inside
an exported function, right after a return, jump or padding, and sitting
among other code pointers found 252 such starts inside 241 exported
functions; `symbols.txt` now splits them.

## Logging

| What | Address | Status |
|---|---|---|
| `GLog` (`FOutputDevice*`) | `0x10F01158` | verified |
| the log file device GLog points at | `0x10EFE9D8` (vtable `0x10E47648`, one slot) | verified |
| `FOutputDeviceFile::Serialize(const char*, EName)`, `__thiscall` | `0x10901780` | verified (hooked) |
| `FOutputDevice::Logf(this, EName, fmt, ...)`, `__cdecl` | `0x10AF5230` | static |
| probably `GError` / `GFileManager` | `0x10F01160` / `0x10F01168` | static |

`Logf` returns early when the category is suppressed. When called on GLog, it
also echoes the line with a `Log: `/`Init: `/`Cmd: ` prefix to a debug console.
Log categories are name values: `0x2F8` Log, `0x2FA` Init, `0x2FC` Cmd.
`DEFAULT.INI` suppresses only the `Dev*` categories. Nothing writes a log file
in the Steam install.

## Game loop and exit

| What | Address | Status |
|---|---|---|
| `GIsCriticalError` (set by the error handler) | `0x10F46D70` | verified |
| `GIsRunning` (main loop condition) | `0x10F46D7C` | verified |
| `GIsRequestingExit` (`appRequestExit`, `WM_QUIT`) | `0x10F46D84` | verified |
| `GIsAppActive` (byte; 0 while another program has the focus) | `0x10F01150` | verified |
| `GEngine` (`UEngine*`): `MainLoop` calls its `Tick` (vtable `+0x7C`); `+0x38` is the client, whose `+0x30` holds the viewports | `0x10F34AD0` | static |
| intro-movie player (`PlayIntroMovies`) | `0x10A50C30` | verified: returning at once skips the logo movies |
| `MainLoop`: per frame `TimeManager::BeginFrame`, `GEngine->Tick(game delta)` (vtable `+0x7C`), `PumpMessages`, `TimeManager::EndFrame`; while inactive it waits in `GetMessageA` | `0x10C95BE0` | static |
| `PumpMessages(wait, active, window)`: `PeekMessageA`, or `GetMessageA` when waiting | `0x10AEB350` | static |
| `appRequestExit(Force)`: logs `appRequestExit(%i)`; Force calls `ForceExit`, else `PostQuitMessage` and `GIsRequestingExit` | `0x10AEA960` | verified (an earlier SDK hook saw Force 1 at level changes; no longer hooked) |
| `ForceExit`: releases input, `RelaunchForLevelChange`, shuts the renderer down, `TerminateProcess(-1)` | `0x10906D80` | static |
| `RelaunchForLevelChange` (below); with no next level it restores the display mode | `0x10901D60` | verified (Ion Launcher's log shows the command line it passes) |
| `GNextLevelURL` (`char[0x400]`), followed by the extra arguments passed on | `0x10F34AD8` / `0x10F34ED8` | static |
| `appLaunchURL` (`ShellExecuteA`) | `0x10AEBC40` | static |
| engine console commands (`MEMSTAT`, `RES_DUMPSTATS`, `CONFIGHASH`, `EXIT`/`QUIT`, `RELAUNCH`, `DIR`, `DEBUG CRASH`/`GPF`/`EATMEM`; list in [game/console.md](game/console.md)); not named yet | `0x10AEB6D0` | static |

- Functions calling `PeekMessageA` (IAT `0x10E4734C`): `0x10A50C30` (intro
  movies), `0x10AEB350`, `0x10C83450` (`UD3DRenderDevice::Lock`, its
  device-lost wait), `0x10C84070`. Decompiled output: `build/re_mainloop.c`
  (regenerate with `Decompile.java refs:0x10e4734c`).
- The game exits through `TerminateProcess` on itself (`ForceExit`, and
  `RelaunchForLevelChange` when the launcher does not answer) or through CRT
  `exit` (IAT: `TerminateProcess` `0x10E47184`, `ExitProcess` `0x10E47268`).
- **Level changes restart the game** (New Game, entering and leaving a
  mission). `appRequestExit(1)` runs `RelaunchForLevelChange`: three black
  frames, `LoadingScreen::Begin` with the next level's URL, three frames of
  that loading screen, then `ShellExecuteExA` on `Ion Launcher.exe` (next to
  the exe) with `T3MAIN.exe <display or "window"> "dummy" <URL> <arguments>`.
  It waits for the launcher's event (`0x10EFE8B0`) and window (class and title
  `Ion Launcher`), sends it `WM_USER` with a duplicated handle of itself, and
  ends. The launcher (log: `Documents\Thief - Deadly Shadows\Launcher.log`)
  waits for the game to end (about 1.1 s), restores the display mode, waits
  one second, starts `T3Main.EXE -display \\.\DISPLAYn WxH <URL>` (for New
  Game `Inn?-LoadTravel?-LoadSave?-ObjectFilter=0?DestTeleporter="Inn"`) and
  waits for the new game to signal exclusive mode (about 3 s). The player
  starts at the `PlayerStart` whose `TeleportDestName` matches
  `DestTeleporter`.
- Closing the window crashes during shutdown, with the SDK or without: exit
  code `0xC0000005`. The SDK's crash reporter places the fault at `0x1098A466`
  (reading address 0). Not analysed yet.
- Not found yet: `UObject::GObjInitialized`.

## Clock (`TimeManager`)

Ion Storm's game clock: a singleton `MainLoop` brackets every frame with, and
the source of each frame's game delta.

| What | Address | Status |
|---|---|---|
| `TimeManager::Instance()` (creates it on first use) / `TimeManager::GSingleton` | `0x10D3EBE0` / `0x10FFCC8C` | verified (called by the SDK) |
| `TimeManager::TimeManager`: time scale 1, min step 0.01 s (`MOV [ESI+4], 0x3C23D70A` at `0x10D3EB9E`), max step 0.1 s | `0x10D3EB80` | static (the SDK's `SmoothFrames` patches the min step) |
| `BeginFrame` (frame-start TSC) / `EndFrame` (advances game time) | `0x10D3EDD0` / `0x10D3EDF0` | static |
| `GetGameTime` / `SetGameTime` (double) | `0x10D3EC80` / `0x10D3EC90` | static |
| `SetMaxStep` / `SetMinStep` | `0x10D3ECA0` / `0x10D3ECD0` | static |
| `SetPaused(bool)`, `__thiscall` (events `0x74`/`0x75` through `0x10F46DA0`) / `IsPaused` | `0x10D3ED00` / `0x10D3ED40` | verified (called by the SDK) |
| `GetTimeScale` / `SetTimeScale` / `GetDeltaTime` | `0x10D3ED70` / `0x10D3ED80` / `0x10D3EDB0` | static |
| console command `SIMTIME` (`SCALE`, `SETMIN`, `SETMAX`, `PAUSE`, `UNPAUSE`, `TOGGLEPAUSE`, `STEP`) | `0x10D3EF30` | static |

Fields: `+0x00` time scale, `+0x04` min step, `+0x08` max step, `+0x0C` real
time not applied this frame, `+0x10` the frame's game delta, `+0x14` pause
countdown, `+0x18` game time (double), `+0x20` game time at frame start,
`+0x28` time carried to the next frame, `+0x2C` frame-start TSC, `+0x34` TSC
ticks per second (64-bit), `+0x3E` paused, `+0x40` frame count.

`EndFrame` scales the frame's real time by the time scale and adds the carried
time. Above the max step it clamps (the game runs slower); below the min step
it advances nothing and carries the time over. `MainLoop` passes the result
to `GEngine->Tick`, so with the 10 ms minimum the world updates at most 100
times a second: above 100 fps it moves on every second or third frame, which
looks choppy. The SDK's `SmoothFrames` lowers the minimum to 1 ms. Only the
constructor and `SIMTIME SETMIN` set it.

The player's physics controller (constructor `0x10B8C4D0`, vtable
`0x10E896A8`) reads `[Physics] PlayerControllerFPSrate` (60) into `+0x128` as
1/60 s. Vtable slot 21 (`0x10B8C690`) returns `min(dt, +0x128)`: it caps the
step size, not the update rate. The `AIControllerFPSrate_*` values are stored
as 1/rate at `0x10FF65F0` (Running, 30), `0x10FF65F4` (Basic, 15),
`0x10FF65F8` (Minimal, 5) and `0x10FF65FC` (Off, 2).

## Configuration (Ion Storm's INI layer)

The game reads its own INI files (`Default.ini`, `T3UI.ini`, ...) through a
config singleton, not through Unreal's `GConfig`. Keys can carry platform
suffixes: `__p` (PC), `__x` (Xbox), `__t` (Thief), for example
`VersionWindow__p=VersionText`.

| What | Address | Status |
|---|---|---|
| `Config::Instance()` (returns the singleton) | `0x10911950` | static |
| the singleton | `0x10F2C3E4` | static |
| `bool Config::Find(const cString& section, const cString& key, const char* file, cString& value)`, `__thiscall`: the lookup every getter parses | `0x109103D0` | hooked (SDK config overrides) |
| `cString& cString::operator=(const char*)` (frees the old text, copies with the game's allocator; `""` leaves it empty) | `0x1090A590` | used by the SDK |
| `bool Config::GetBool(section, key, bool*, file)` | `0x109108B0` | static |
| `bool Config::GetFloat(section, key, float*, file)`, `__thiscall` | `0x10910B60` | verified (hooked) |
| `bool Config::GetString(section, key, char**, file)` | `0x10910E20` | static |

## Gamesys properties

Gameplay values (Ion Storm's gamesys, from `T3Gamesys.t3u`) are read through
property getters keyed by an ID whose low 16 bits index the property table at
`DAT_10F3EDA4 + 8`; bit `0x800000` asks for the value to be cleared first.

| What | Address | Status |
|---|---|---|
| `GetPropertyValue(uint32_t id, void* out)`, `__thiscall`, `ret 8`, returns int: looks the ID up (`0x10AD3DF0`), then copies the value through the table entry's vtable `+0xB4` | `0x1098E330` | hooked by the `widescreen-fov` mod |
| property write path | `0x10AD9C90` | static |

FOV properties (float degrees, designed for 4:3), IDs with bit `0x100000`
set: `0x100534` the player camera (85), `0x100509`, `0x10050A`, `0x10050C`,
`0x100775`, `0x100776`, `0x100777`, `0x10084E`, `0x10084F` (the other cameras
and zoom views; values 20 to 200). The `widescreen-fov` mod converts each
to Hor+ on screens wider than 4:3 (`tan(h'/2) = tan(h/2) * aspect / (4/3)`,
which keeps the 4:3 vertical view; values of 180 or more, not angles, stay)
and moves the player's by its `PlayerFOV` minus 85. Not yet confirmed in the
game: that the IDs are FOVs in this build, and which of them are horizontal
angles. The mod's `LogReads=1` logs each ID's first read.

## Difficulty

The chosen difficulty lives in the stats as gamesys values: `dif_currdifficulty`
(0 Easy .. 3 Expert, 4 custom), `dif_AISenses`, `dif_AICombat`. The AI
multipliers come from `Default.ini` `[Difficulty]`
(`Difficulty_AIVisual_Mult_<Easy|Normal|Hard|Expert>`, `_AIAudio_`,
`_AITactile_`, `_AIHitPoints_`, `_AICombatSpeed_`, ...) into the object at
`DAT_10FF667C + 0x98` onward.

| What | Address | Status |
|---|---|---|
| `GetStats()`, `__cdecl`; slot 0 of the result: `int Get(FName)` | `0x10A18230` | used by the `difficulty-fixes` mod |
| `LoadDifficultyMultipliers`: loads the `[Difficulty]` multipliers for `dif_AISenses`/`dif_AICombat`; only caller `0x10AB8470`, nothing calls it on a level load (missions play with the multipliers the game started with) | `0x10AB70B0` | called by the `difficulty-fixes` mod |
| in `UGameEngine::Virtual32` (the level load), after the map is in: `mov al, [0x10F45C0C]` | `0x10985ADC` | code hook (`difficulty-fixes`) |
| `FindExitMissionInfo()`, `__cdecl`: the level's `AExitMissionInfo` actor, NULL in city sections | `0x10AC89C0` | called by the `end-mission` mod |
| `WindowManager::OpenMissionCompleteWindow()`, `__thiscall` on `GWindowManager`: shows `MissionCompleteWindow` | `0x10B15CC0` | called by the `end-mission` mod |
| `WindowManager::OpenEnterMissionWindow(bool)` / `OpenRestartMissionWindow()` | `0x10B15B20` / `0x10B15BF0` | hooked (`difficulty-fixes`) |
| mission records the menus edit: `*(DAT_10F3A3D8 + 0x150)`, `+4`/`+8` (mission, record) for Enter Mission, `+0xC`/`+0x10` for Restart Mission; the record's difficulty at `+0x174` | `0x10F3A3D8` | static |
| `bool __cdecl (mission)`: gamesys `0x800864` is 1 (the mission has no difficulty choice) | `0x10ABE130` | static |

## First-person camera

Static analysis; the `steady-view` mod relies on the parts marked hooked.
Each engine tick (`UT3GameEngine::Tick`, `0x1098A410`) updates the camera
after physics and the actors, at `0x1098A89B`, and `UT3GameEngine::Draw`
(`0x10B23BA0`) reads it in the same tick.

- **Position.** The first-person modes (`LookAt ActorsTarget` in
  `T3Camera.ini`) take `AGarrett::GetCameraTargetLocation`: the world
  position of the "Camera Attach" bone (`AGarrett+0x390` name, `+0x39C`
  number), pulled back from walls by a short trace along the view. The bone
  moves with every animation (breathing, walk bob, the landing animation,
  crouch blends); the root bone's translation is cancelled, so there is no
  root motion. `T3Camera.ini`'s springs do nothing at `Stiffness 1.0`, and
  `Default.ini`'s `[CameraEffects]` keys are not read by this build.
- **Rotation.** The view is `AGarrett::HeadRot` (`+0x400`), not the
  controller's rotation. Standing, the head turns up to 90 degrees from the
  body; moving, the body turns toward the view at a fixed rate. Movement input
  is applied in the body's frame, so starting off at an angle curves.
- **Movement.** Velocity is computed from input, not from animation, and
  smoothed with 0.10 (walking) or 0.95 (running) per application, once per
  10 ms or per frame, whichever is longer: the smoothing depends on the frame
  rate.
- **Landing.** The land state zeroes Garrett's velocity and plays the land
  animation, which moves the eye bone.
- **Near plane.** The scene render pushes a near plane of 1.0 and a far plane
  of 32000 for each pass. Held items hang from the hand bones and are drawn
  with the world, so they cut into the near plane, more so with a wider FOV.
- **Physics.** Havok rigid bodies step at a fixed 1/60 s with an
  accumulator and no interpolation (props, carried bodies, ragdolls). The
  player character steps by the frame time, so Garrett himself moves every
  frame.
- **Garrett's position chases his physics body.** The physics character's
  block (`AActor+0xB0`, vtable slot 8) holds its velocity at `+0xF8`, `+0xFC`,
  `+0x100` (z) and the collision height the game asks for at `+0x118`. In the
  air its vertical speed is a clean ballistic curve (240 units/s at take-off,
  gravity 515), but `Location.Z` follows the body at no more than 64 units/s:
  it lags at take-off, keeps rising at +64 after the body has passed the top
  of the jump, falls at -64, and catches up on landing in one frame (about 19
  units). On the ground the velocity keeps its value from the landing. Stairs
  and slopes move `Location.Z` in 2-5 unit steps.
- **The eye bone.** Measured in front of the view, the bone sits about 6.5
  units ahead of Garrett's centre standing and 12-13 moving (he leans), and
  about 24 / 21.5 units above it. The jump animation lifts it 8 units; the
  climb swings it over 30. When his body turns at once, the bone is computed
  for one frame with his old facing (it swings about 90 degrees around him).

| What | Address | Status |
|---|---|---|
| `cT3Camera::Update(dt)`, `__thiscall` | `0x10AC2D30` | static |
| `AGarrett::GetCameraTargetLocation(FVector* out)`, `__thiscall`: the eye bone, pulled back from walls | `0x10B21830` | hooked by `steady-view` |
| eye bone or Location, plus the wall trace, `__thiscall(filter; out, pawn, bone)` | `0x10ABFBC0` | static |
| `AGarrett::GetCameraTargetRotation` / view rotation (returns `HeadRot`) | `0x10B22120` / `0x10B21250` | static |
| body turn toward the view while moving; its rate, 55000 units/s (302 degrees/s) | `0x10B19300`; `0x10E793FC` | rate patched by `steady-view` |
| velocity from input and smoothing, `__stdcall(pawn, float)`; factors 0.10 / 0.95 | `0x10B3BD10`; `0x10E7E4C0` / `0x10E7E4C4` | static |
| land state Enter: zeroes velocity, plays `JumpLand_FWD` | `0x10B49250` | static |
| scene render: near 1.0 (`push` immediates at `0x109FD10E`, `0x109FD3FD`, `0x109FD54E`, `0x109FD5FC`), far 32000 | `0x109FCF10` | near plane patched by `steady-view` |
| set view, near, far, FOV, `__cdecl(view*, near, far, fov)` | `0x10917D20` | static |
| Havok world step: fixed 1/60 s (`0x10EBF560`) with an accumulator | `0x10D9E840` | static |
| player character simulate: steps by the frame time | `0x10B86D00` | static |

## Save games

| What | Address | Status |
|---|---|---|
| save/load dispatcher (input commands; `0x3D` quick save, `0x3E` quick load): quick save names the save after the localized `T_QuickSave` ("Quick Save") and overwrites the save of that name (skipped when its game time is the current one); quick load loads the save of that name | `0x10B17810` | static |
| quick save: the name settled, `cString` at `[esp+0x14]` | `0x10B17CE0` | code hook (`quicksave-cycle`) |
| quick load: the name settled, `cString` at `[esp+0x14]` | `0x10B181AA` | code hook (`quicksave-cycle`) |
| `FormatHexId`: a save's 20-byte ID as dashed hex, its folder name | `0x10D64D80` | static |
| save loader: a `LOADGAME:` level opens `<save>/<Level>.wgs` through the save reader; a reader of size 0 falls back to the map itself (a fresh start) | `0x10B090C0` | static |
| save reader (archive over the unpacked level), `thiscall(path, loading)` | `0x10B0EE30` | static |
| `.wgs` check: the file id, the block sizes and the SHA-1 of the blocks and the header (docs/assets.md, "Saved games") | `0x10D4B230` | static |
| `.wgs` unpack: 0x4000-byte blocks of LZO1X into a temporary file | `0x10D4BB10` | static |
| SHA-1 init / update / final | `0x10D64900` / `0x10D64D60` / `0x10D64A00` | static |
| `ULevelBase::Serialize`: a save load (`ar[0xD] & 0x200`) reopens the map and reads its static gamesys data at the summary's offset 0x24 | `0x109753E0` | static |
| gamesys object system serialise (`this+0xC` the item count) / read the items | `0x10BA0570` / `0x10B9F870` | static |

## Options (`options.ini`)

Options are stored as ints at `options + 4 + 4*i`, indexed by the names table
at `0x10E6ED70` (21 `char*`): Version, Subtitles, InvertYAxis, LookSpring,
Vibration, SFXVolume, MusicVolume, ControllerLayout, Brightness, VSynch (9),
AutoBowZoom, Resolution (11), ShadowDetail, Bloom, LightCutoff, MultiSampling
(15), UseLowResTextures, LOD, UseHWMixing, UseEAX, EAXMultipleEnvironments.

| What | Address | Status |
|---|---|---|
| `Options::Load` / `Save` / `SetDefaults` | `0x10AB66F0` / `0x10AB6440` / `0x10AB6320` | static |
| `Options::Get(i)` / `Set(i, value)` | `0x10AB5AB0` / `0x10AB5BC0` | static |
| `Options::GetResolution` (option 11) | `0x10AB5AC0` | static |
| `Options::ApplyVideo`: clamps Resolution to 0..4, keeps modes the adapter has | `0x10AB61A0` | static |
| `SupportsDisplayMode(width, height, 32)` | `0x10C82CB0` | static |
| resolution widths / heights, 5 entries each (640x480 ... 1600x1200) | `0x10E6EDC4` / `0x10E6EDD8` | verified (the SDK rewrites them) |
| A/V options row refresh (kind 0 slider, 1 checkbox, 2 button; label `T_OptionsScreen<name>`) | `0x10B72DD0` | static |

## UI windows

Menus and the HUD are native window objects laid out from `System/T3UI.ini`
(plus `T3UILights.ini` and `T3ItemGrid.ini`); each section's `Type=` names the
window class. The HUD items in `T3Hud.ini` are a separate system with
normalised screen coordinates (`screenx`, `screeny` in -1..1).

| What | Address | Status |
|---|---|---|
| `GWindowManager` (`WindowManager*`) | `0x10F35DC4` | verified |
| `Window::PlacedPosition(FVector* out)`, vtable `+0x18`, returns `out` | `0x10A52530` | verified (hooked) |
| `Window::LoadConfig` (reads the window's INI section) | `0x10A54080` | static |
| `ParsePlacement` (CENTER 1, TOP 2, BOTTOM 3, LEFT 4, RIGHT 5, else 0) | `0x10A51DF0` | static |
| `ReadWindowHeight` (`FULLSCREEN`, `LETTERBOX` or a number) | `0x10A538B0` | static |
| `WindowManager::GetUIScreenSize(FVector* out)`: the layout size (`+0xCC`, `+0xD0`) | `0x109E47E0` | matched |
| `Window::GetParent`, vtable `+0xA4` (`mov eax, [ecx+0xB4]`) | `0x109E38E0` | verified |
| `Window::HasFlag` / `SetFlag` / `ClearFlag`, vtable `+0x100` / `+0x104` / `+0x108` | `0x109E3820` / `0x109E3840` / `0x109E3860` | static |

`WindowManager` fields: `+0xCC` / `+0xD0` layout width / height
(`[WindowManager] AssumedUIScreenWidth/Height`, 640x480), `+0xD4` UI camera FOV
(95), `+0x198` Ortho, `+0x1E4` layout origin (1 = positions from the parent's
top-left corner; 1 in every PC menu traced).

`Window` fields (verified with the SDK's `UILayoutTrace`): `+0x1C`/`+0x20`/`+0x24`
Pos_X/Y/Z (floats), `+0xB4` parent, `+0xC8` Active (0 NOT, 1 VISIBLE, 2
ACTIVE), `+0xCC` PauseGame (byte), `+0xCD` BlackScreen, `+0xCE` Selectable,
`+0xD0`/`+0xD4` Placement_X/Y, `+0xE8` flags (`0x800` ListenForMouseClicks,
`0x1000` IsModal). Vtable `+0x84` returns a pointer to the window's own size;
`+0x88` writes a size into an out parameter (used on the parent).

`PlacedPosition` in top-left mode, with `avail` the parent's size clamped to the
layout size (the layout size for top-level windows): CENTER
`x = (avail - w)/2 + Pos_X`, LEFT and absolute `x = Pos_X`, RIGHT `x = avail - w + Pos_X`; y is the
same with TOP/BOTTOM. The result is relative to the parent. `Width=FULLSCREEN`
makes `w` the layout width, so a full-width window at `Pos_X=325` (the main
menu buttons) sits 325 units from the left edge at any width. Callers use the
returned pointer: a detour must return it.

HUD values the game reads from `T3UI.ini` (through `Config`, so `SetConfigValue`
answers them): `[JunkItemWindow] FlashOnTime`/`FlashOffTime` (0.75/0.25 s,
the picked-up junk item's flashing); `[ItemCycleWindow]`/`[WeaponCycleWindow]
DeEquipText` (the "nothing equipped" string tag; an empty value counts as
missing); `[HealthMeter] Pos_X/Pos_Y` and `ClearPos_X/ClearPos_Y` (20/-15 and
20/100: where the bar sits and where it slides when idle).

Other settings read through `Config`: `T3PlayerAnims.ini`'s animation
sections (`Name`, `Speed`, `Looping`, ...; the idle ones are `[MainIdle]`,
`[MainIdleCrouching]`, `[MainIdle_PS]`, `[BodyCarryIdle]`,
`[BodyCarryIdleCrouching]`); `Default.ini` `[Physics] WorldGravityZ`
(-514.96, Unreal units/s², Havok) and `[PointPhysics] Gravity` (-32 ft/s²,
flinders), `[T3Settings] WalkMultiplier` (0.5) and `CreepMultiplier` (0.33).

`System/T3Camera.ini` is not read through `Config`: it lists camera modes as
`CameraMode <name>` ... `EndCameraMode` blocks (`InheritsFrom`, `Distance`,
`PitchLimit`, ...); `DeathCam` inherits from `FarThirdPerson`. A changed copy
reaches the game through a file override.

## Display: viewport and Direct3D 8

| What | Address | Status |
|---|---|---|
| `InitDirect3D`: `Direct3DCreate8(220)`, `CreateDevice` (HAL, hardware then software vertex processing) | `0x10919730` | verified (hooked through the import) |
| `D3DPRESENT_PARAMETERS` the focus-loss reset passes: only `InitDirect3D` touches it, zero in play | `0x10F2C86C` | verified |
| `D3DPRESENT_PARAMETERS` of the live device (`SetRes` creates and resets with them, the reset at `0x10C84693`) | render device `+0x4630` | verified |
| `IDirect3D8*` / `IDirect3DDevice8*` | `0x10F2C8B4` / `0x10F2C8B8` | static |
| `UWindowsViewport::ViewportWndProc` | `0x10C8B820` | verified (hooked: the SDK keeps a borderless game running) |
| `UWindowsViewport::Exec` (console commands: EndFullscreen, ToggleFullscreen, SetRes, ...; list in [game/console.md](game/console.md)) | `0x10C8ADE0` | static |
| `UWindowsViewport::EndFullscreen` (logs "EndFullscreen") | `0x10C86630` | verified (log) |
| `UWindowsViewport::ToggleFullscreen` (logs "AttemptFullscreen") | `0x10C87560` | static |
| `UD3DRenderDevice::Lock` (logs "TestCooperativeLevel failed", "BeginScene failed") | `0x10C83450` | verified (log) |
| `UD3DRenderDevice::SetRes`: present parameters (fullscreen interval ONE with VSynch, else IMMEDIATE; none when windowed), creates or resets the device, then `LoadingScreen::Begin` for the current map | `0x10C84070` | static |
| VSynch as `SetRes` reads it (`Options::ApplyVideo` writes it) | render device `+0x40DC` | static |
| `DrawLoadingProgress(float progress, bool force)`, `__cdecl`: redraws the loading screen (and presents) when forced or when the bar moved; the loading code calls it many times, each a frame that waits for VSynch | `0x109E1E80` | hooked by the `loading-tweaks` mod |
| `LoadingScreen::Begin(device, map, flag)`, `__cdecl`: `<[Paths] DynamicTextures>\<map>.dds` (else `Loading1.dds`) as the background, the `[LoadingScreen]` logo and caption textures; draws and presents | `0x109E1FC0` | static (hooked by the SDK's level-change curtain) |
| `LoadingScreen::LoadLayout` (`[LoadingScreen]` positions and sizes) | `0x109DFBA0` | static |
| `UpdateWindowTitle` (localised "Thief - Deadly Shadows") | `0x10C872C0` | static |

The menu cursor is a Direct3D hardware cursor: a 32x32 `A8R8G8B8` image with
its hot spot at 0,0. Every frame the game calls the device's
`SetCursorProperties` and `ShowCursor` (vtable slots 10 and 12) and user32's
`ShowCursor` and `SetCursor` (counted with the SDK's `FrameStats`).

On `WM_ACTIVATEAPP(FALSE)` the window procedure resets the device with the
parameters at `0x10F2C86C` (the call at `0x10C8BF6B`) unless
`TestCooperativeLevel` already reports the device lost. Those are not the
device's own parameters: only `InitDirect3D` touches that global and it stays
zero, so the reset asks for a 0x0 back buffer. An exclusive fullscreen device
is normally lost by then, so vanilla never makes that call. A windowed
(borderless) device is not, and neither is a fullscreen one that Windows'
fullscreen optimisations keep; the reset fails, and `Lock` then sleeps in
10 ms steps waiting for the device, so the game freezes. The SDK skips that one
reset (verified: focus loss and exit both pass through it). Nothing is lost:
`Lock` recovers a lost device through `SetRes`, which resets with the real
parameters (render device `+0x4630`).

The game asks for an `A8R8G8B8` back buffer (`SetRes`, `0x10C844E4`, checked
with `CheckDeviceFormat` at `0x10C8451D` and `0x10C845A5`) and uses its
alpha: render-state preset 5 (`0x109388C0`) blends with
`SRCBLEND = DESTALPHA`, and `0x109569F0` writes alpha only, so some lighting
passes first write a mask into the back buffer's alpha and then add light
weighted by it. On an alpha-less back buffer those passes light at full
strength (DXVK even rewrites `DESTALPHA` to `ONE` there). A windowed device
keeps that format whenever the adapter supports it (`CheckDeviceType` with
the desktop format, windowed).

The same handler releases the mouse and DirectInput, saves
`TimeManager::IsPaused` to `GPausedBeforeDeactivation` (`0x10FF71BC`), pauses
the game and clears `GIsAppActive`; `MainLoop` then waits in `GetMessageA`
until the game is active again. Setting the flag back and restoring the saved
pause state after the handler keeps the game running (verified).

## Other anchors

- `ULevel::SpawnActor`: referenced by the strings "SpawnActor failed because ..." (4 variants).
- `UGameEngine`: strings `UGameEngine::Actors`, `::EnginePackages`, `::ServerActors`.
- Player classes: `APlayerController`, `AT3PlayerController`, `APlayerPawn`, and
  a `PlayerPawnPuppet` name (worth checking for multiplayer).
- UnrealScript natives: 254 `exec*` names in ASCII (native registration tables).
- Script packages `System/*.t3u`: Unreal package format, file version 95,
  licensee version 133 (an early Unreal Engine 2 fork).
- Networking: Unreal's net layer is gone. There are no `NetDriver`,
  `ActorChannel` or travel strings and no Winsock imports; only `IpDrv.dll`,
  `RemoteRole`, `Replication` and the `UClass::NetFields`/`ClassReps`
  containers remain. Multiplayer needs its own transport.

## City AI and collection matching evidence

The following entries are **static** evidence for `PC_20040610`, the original
executable identified in [target.md](target.md). They are not runtime tests,
an address map for patched executables, or a guard-disappearance fix. Class,
field and parameter names that retain address-based placeholders are
reconstructed; descriptive roles below do not establish original source names.

The linked contributor-written C++ was compiled with MSVC 7.1
(`13.10.3077`, `/O2 /GX /GR- /MT /DNDEBUG /DWIN32 /D_WINDOWS`) and checked
in its integrated translation unit with the strict [matching gate](matching.md).
Each listed contribution passed at 100%, with zero provisional bindings,
including the gate's code/data references, argument counts and generated
exception-cleanup data. The source's `// FUNCTION:` marker identifies the
function and its decorated symbol; [symbols.txt](../config/PC_20040610/symbols.txt)
records the address/name bindings and supported aliases. Generated handlers,
aliases and already matched neighbors are not additional contributed functions.

The boundary tables record the external function and global references paired
by that verification, including engine/library declarations. The evidence for
each row is the linked caller's matching reference to that exact target address,
not an inference from a suggestive name. Folded functions can share an address;
the table uses the caller's symbol spelling rather than claiming that one
class's name uniquely owns the shared body. No engine or library body is
reconstructed here. Vtable/data references are declarations, not extracted
assets. Scalar/string constants and compiler-generated EH tables are checked by
value by the gate; they are not new engine entry points.

### Scratch allocation

The scratch acquisition function reuses the last pool entry or constructs an
empty object under the allocator's paired scope calls. Its strict result is
100%; the ordinary objdiff progress report displays 99.85714% for this same
function/object. These are different comparisons, not a rounded match claim.

| Function | Bytes | Static role and matching source |
|---|---:|---|
| `0x1092F040` | 184 | [Preserved scratch-pool acquisition helper](../src/Game/Unsorted_1092E9C0.cpp) |

External references first used by this group (common references are recorded
with the earlier group above):

| Target address | Referenced name | Matching caller evidence |
|---|---|---|
| `0x10905AA0` | `GetAllocator` | [0x1092F040](../src/Game/Unsorted_1092E9C0.cpp) |
| `0x10905C10` | `new` | [0x1092F040](../src/Game/Unsorted_1092E9C0.cpp) |
| `0x10BFBD70` | `cIntArray::SetCount` | [0x1092F040](../src/Game/Unsorted_1092E9C0.cpp) |
| `0x10F31B9C` | `DAT_10f31b9c` | [0x1092F040](../src/Game/Unsorted_1092E9C0.cpp) |

### Item range lifetimes

The range move destroys displaced elements, moves the retained range, and
reconstructs the vacated elements. It calls the existing `memmove` library
entry point; no library implementation is included.

| Function | Bytes | Static role and matching source |
|---|---:|---|
| `0x10C08B50` | 527 | [Item collection range movement/lifetime](../src/Game/Unsorted_10C08B50.cpp) |

External references first used by this group (common references are recorded
with the earlier group above):

| Target address | Referenced name | Matching caller evidence |
|---|---|---|
| `0x10C013A0` | `Class_10E97B00::Class_10E97B00` | [0x10C08B50](../src/Game/Unsorted_10C08B50.cpp) |
| `0x10D1F040` | `__CxxFrameHandler` | [0x10C08B50](../src/Game/Unsorted_10C08B50.cpp) |
| `0x10D20990` | `memmove` | [0x10C08B50](../src/Game/Unsorted_10C08B50.cpp) |
| `0x10D660B0` | `UObject::StaticConstructor` | [0x10C08B50](../src/Game/Unsorted_10C08B50.cpp) |
| `0x10E47660` | `DAT_10e47660` | [0x10C08B50](../src/Game/Unsorted_10C08B50.cpp) |
| `0x10E97BBC` | `DAT_10e97bbc` | [0x10C08B50](../src/Game/Unsorted_10C08B50.cpp) |

### Guard state, population and return

The matched bodies cover the controller/state stack, pawn/model lifetime,
population bookkeeping, patrol ownership, and return movement/orientation.
They establish original-build behavior that can support later City research;
they do not establish compatibility with a different executable.

The declaration corrections in [EngineClasses.h](../include/Engine/EngineClasses.h)
and [AICoreClasses.h](../include/AICore/AICoreClasses.h) have these specific limits:

| Address | Contract and evidence |
|---|---|
| `0x109A5330` | `APawn::Virtual100(AController*, bool)`: the matched `AAIPawn::Virtual100` forwards two stack words to the base entry; its target cleanup is eight bytes. Engine declaration only. |
| `0x10BC3190` | `AAIPawn::Virtual100(AController*, bool)`: matched 1,017-byte body, two-argument cleanup and the base call above; `Restored` describes the observed skip flag, not a recovered original name. |
| `0x10B9C4A0` | `AAIPawnController::Virtual101(bool)`: matched 116-byte reset body with one stack argument; the inherited slot-101 declarations agree with that call shape. |
| `0x109E3C90` | Shared folded slot target for `AAIController` and `APlayerController`: the one-word slot-101 aliases are retained alongside existing spellings; this is not evidence that the other folded methods have identical source-level types. |
| `0x10C07960` | `Class_10E97B68::FUN_10c07960(int,int,int,int)` occupies slot zero before the virtual destructor. The matched event body and the existing constructor/destructor vtable agree; the old destructor remains unchanged. |

The cached-state maximum at `0x10C083C0` reads the registry and stores its
timestamp at owner `+0x14` and maximum at `+0x18`, returning the cache within
the observed 0.1-second interval. A separate population-point eligibility
function at `0x10A491B0` uses `0x10F3A054` (float distance cache) and
`0x10F3A058` (initialization flag); its matched accesses establish those types.
The behavior context at `0x10BF7B90` is 52 bytes. The movement and orientation
constructors preserve their observed member/temporary lifetimes; opaque
fields remain opaque.

| Function | Bytes | Static role and matching source |
|---|---:|---|
| `0x1091F420` | 148 | [Portal plane-array allocation and count](../src/Game/PortalPlaneArray.cpp) |
| `0x10B9C4A0` | 116 | [Controller state reset](../src/Game/AAIPawnController_7.cpp) |
| `0x10B9CAD0` | 164 | [State activation/notification](../src/Game/cStateStack_16.cpp) |
| `0x10B9DBB0` | 140 | [Guard-state stack lifetime](../src/Game/cStateStack_17.cpp) |
| `0x10B9D7E0` | 238 | [State replacement and pending-state queue](../src/Game/Unsorted_10B9D7E0.cpp) |
| `0x10C083C0` | 177 | [Cached maximum of active AI-state values on the search registry](../src/Game/Unsorted_10C08130.cpp) |
| `0x10BC40E0` | 125 | [AI-state eligibility threshold check](../src/Game/StateEligibility.cpp) |
| `0x10BC4240` | 278 | [Pending AI-state request replacement](../src/Game/StateRequest.cpp) |
| `0x10BCE0D0` | 305 | [AI-state animation command creation and submission](../src/Game/StateAnimation.cpp) |
| `0x10BC3190` | 1017 | [Pawn/controller initialization and five AI-model lifetimes](../src/Game/PawnModelInitialization.cpp) |
| `0x10BC3120` | 109 | [Spawn an AI model using the pawn transform and context](../src/Game/PawnModelFactory.cpp) |
| `0x10A491B0` | 242 | [Population point exclusion using cached LeavingDistance and view direction](../src/Game/PopulationPointEligibility.cpp) |
| `0x10B9DDB0` | 436 | [Reconcile patrol/path-point requests with active state-stack lifetimes](../src/Game/PatrolStack.cpp) |
| `0x10BDFEF0` | 956 | [Returning state: move home, finish orientation, and advance toward state pop](../src/Game/ReturningState.cpp) |
| `0x10C36700` | 158 | [MC_Turn constructor used to restore home orientation during Returning](../src/Game/ReturnOrientationCommand.cpp) |
| `0x10C2EA30` | 241 | [MC_MoveToPoint constructor creates Returning movement and owns its nested path list](../src/Game/ReturnMovementCommand.cpp) |
| `0x10BF7B90` | 149 | [Construct the 52-byte movement context used by Returning commands](../src/Game/BehaviorContextConstruction.cpp) |
| `0x10C36630` | 80 | [Initialize the MC_Turn orientation request during Returning](../src/Game/ReturnOrientationInitialization.cpp) |
| `0x10C07960` | 330 | [Population events: adjust counts, remove group membership, update CityGroup and delegate quota](../src/Game/Class_10E97B68_3.cpp) |

External references first used by this group (common references are recorded
with the earlier group above):

| Target address | Referenced name | Matching caller evidence |
|---|---|---|
| `0x1096D780` | `Class_1096D780::Get` | [0x10BC3190](../src/Game/PawnModelInitialization.cpp), [0x10BC3120](../src/Game/PawnModelFactory.cpp) |
| `0x10971570` | `Class_10971570::FUN_10971570` | [0x10C07960](../src/Game/Class_10E97B68_3.cpp) |
| `0x10974340` | `Class_10974340::FUN_10974340` | [0x10A491B0](../src/Game/PopulationPointEligibility.cpp) |
| `0x10978090` | `Class_10978090::FUN_10978090` | [0x10C36630](../src/Game/ReturnOrientationInitialization.cpp) |
| `0x1098E330` | `Class_1098E330::FUN_1098e330` | [0x10BC3190](../src/Game/PawnModelInitialization.cpp), [0x10A491B0](../src/Game/PopulationPointEligibility.cpp) |
| `0x109A5330` | `APawn::Virtual100` | [0x10BC3190](../src/Game/PawnModelInitialization.cpp) |
| `0x109DFF50` | `cIntArray::RemoveAt` | [0x10B9D7E0](../src/Game/Unsorted_10B9D7E0.cpp), [0x10B9DDB0](../src/Game/PatrolStack.cpp) |
| `0x109E38B0` | `cGarrettLockPickController::FUN_109e38b0` | [0x10C2EA30](../src/Game/ReturnMovementCommand.cpp) |
| `0x109EFF30` | `Class_109EFF30::FUN_109eff30` | [0x10A491B0](../src/Game/PopulationPointEligibility.cpp) |
| `0x10A0A8C0` | `cPawnArray::FUN_10a0a8c0` | [0x10B9DDB0](../src/Game/PatrolStack.cpp) |
| `0x10A0C5F0` | `Class_10A0C5F0::FUN_10a0c5f0` | [0x10C07960](../src/Game/Class_10E97B68_3.cpp) |
| `0x10A15B00` | `destructor'` | [0x10B9CAD0](../src/Game/cStateStack_16.cpp) |
| `0x10A905A0` | `Class_10E50610::~Class_10E50610` | [0x10B9CAD0](../src/Game/cStateStack_16.cpp) |
| `0x10AA8050` | `AFormationPointAbsolute::Virtual94` | [0x10C2EA30](../src/Game/ReturnMovementCommand.cpp) |
| `0x10AA82D0` | `Class_10AA82D0::GetLinkedObject` | [0x10BDFEF0](../src/Game/ReturningState.cpp) |
| `0x10AA82E0` | `Class_10AA82E0::FUN_10aa82e0` | [0x10BDFEF0](../src/Game/ReturningState.cpp) |
| `0x10AAF570` | `Class_10AAF570::GetLinkType` | [0x10B9C4A0](../src/Game/AAIPawnController_7.cpp) |
| `0x10AD1DC0` | `delete` | [0x10BC4240](../src/Game/StateRequest.cpp), [0x10BCE0D0](../src/Game/StateAnimation.cpp), [0x10BDFEF0](../src/Game/ReturningState.cpp), [0x10C2EA30](../src/Game/ReturnMovementCommand.cpp) |
| `0x10AD1EE0` | `UObject::IsA` | [0x10BC3190](../src/Game/PawnModelInitialization.cpp), [0x10B9DDB0](../src/Game/PatrolStack.cpp) |
| `0x10AD2800` | `Class_1098E330::FUN_10ad2800` | [0x10BC3190](../src/Game/PawnModelInitialization.cpp) |
| `0x10B94280` | `AAIPathPoint::InitializePrivateStaticClassAAIPathPoint` | [0x10B9DDB0](../src/Game/PatrolStack.cpp) |
| `0x10B944A0` | `AAIPawnController::InitializePrivateStaticClassAAIPawnController` | [0x10BC3190](../src/Game/PawnModelInitialization.cpp) |
| `0x10B957C0` | `AAIPathPoint::GetPrivateStaticClassAAIPathPoint` | [0x10B9DDB0](../src/Game/PatrolStack.cpp) |
| `0x10B96180` | `AAIPawnController::GetPrivateStaticClassAAIPawnController` | [0x10BC3190](../src/Game/PawnModelInitialization.cpp) |
| `0x10B9BAB0` | `Class_10B9BAB0::FUN_10b9bab0` | [0x10B9C4A0](../src/Game/AAIPawnController_7.cpp) |
| `0x10B9BCD0` | `Class_10B9BCD0::FUN_10b9bcd0` | [0x10BC3190](../src/Game/PawnModelInitialization.cpp) |
| `0x10B9BEB0` | `Class_10B9BEB0::FUN_10b9beb0` | [0x10B9C4A0](../src/Game/AAIPawnController_7.cpp) |
| `0x10B9C060` | `FUN_10b9c060` | [0x10B9C4A0](../src/Game/AAIPawnController_7.cpp) |
| `0x10B9C450` | `Class_10B9C450::FUN_10b9c450` | [0x10B9C4A0](../src/Game/AAIPawnController_7.cpp) |
| `0x10B9CA60` | `Class_10E8BF90::Clone` | [0x10B9CAD0](../src/Game/cStateStack_16.cpp) |
| `0x10B9CAD0` | `cStateStack::FUN_10b9cad0` | [0x10B9D7E0](../src/Game/Unsorted_10B9D7E0.cpp) |
| `0x10B9D740` | `cStateStack::ApplyNextState` | [0x10B9DBB0](../src/Game/cStateStack_17.cpp), [0x10B9DDB0](../src/Game/PatrolStack.cpp) |
| `0x10B9D7E0` | `Class_10B9F200::FUN_10b9d7e0` | [0x10B9DDB0](../src/Game/PatrolStack.cpp) |
| `0x10B9D8D0` | `cStateStack::FUN_10b9d8d0` | [0x10B9DBB0](../src/Game/cStateStack_17.cpp), [0x10B9DDB0](../src/Game/PatrolStack.cpp) |
| `0x10BA91E0` | `Distance` | [0x10BDFEF0](../src/Game/ReturningState.cpp) |
| `0x10BA9FD0` | `Class_10BA9FD0::FUN_10ba9fd0` | [0x10B9DBB0](../src/Game/cStateStack_17.cpp), [0x10C083C0](../src/Game/Unsorted_10C08130.cpp) |
| `0x10BAA6B0` | `FUN_10baa6b0` | [0x10C083C0](../src/Game/Unsorted_10C08130.cpp) |
| `0x10BAA6F0` | `Class_10BAA6F0::FUN_10baa6f0` | [0x10C083C0](../src/Game/Unsorted_10C08130.cpp) |
| `0x10BAE1D0` | `cStructArray::SetCount` | [0x10BCE0D0](../src/Game/StateAnimation.cpp) |
| `0x10BAEC40` | `cStructArray::~cStructArray` | [0x10BF7B90](../src/Game/BehaviorContextConstruction.cpp) |
| `0x10BAF8A0` | `Class_10BAF8A0::~Class_10BAF8A0` | [0x10BCE0D0](../src/Game/StateAnimation.cpp), [0x10BDFEF0](../src/Game/ReturningState.cpp) |
| `0x10BB7580` | `Class_10BB7580::FUN_10bb7580` | [0x10B9DBB0](../src/Game/cStateStack_17.cpp) |
| `0x10BB7670` | `Class_10BB7670::FUN_10bb7670` | [0x10C083C0](../src/Game/Unsorted_10C08130.cpp) |
| `0x10BB7F20` | `Class_10BB7F20::FUN_10bb7f20` | [0x10BC40E0](../src/Game/StateEligibility.cpp) |
| `0x10BB89D0` | `Class_10BB89D0::FUN_10bb89d0` | [0x10C083C0](../src/Game/Unsorted_10C08130.cpp) |
| `0x10BB8D60` | `Class_10BB8D60::Reset` | [0x10B9DDB0](../src/Game/PatrolStack.cpp) |
| `0x10BBB410` | `Class_10BBB410::GetCurrent` | [0x10BC40E0](../src/Game/StateEligibility.cpp) |
| `0x10BBDB40` | `Class_10BBDB40::GetFloat` | [0x10BC40E0](../src/Game/StateEligibility.cpp) |
| `0x10BC3120` | `FUN_10bc3120` | [0x10BC3190](../src/Game/PawnModelInitialization.cpp) |
| `0x10BC3F90` | `Class_10BC3F90::FUN_10bc3f90` | [0x10BDFEF0](../src/Game/ReturningState.cpp) |
| `0x10BC4010` | `Class_10BC4010::FUN_10bc4010` | [0x10B9CAD0](../src/Game/cStateStack_16.cpp) |
| `0x10BC4020` | `Class_10BC4020::FUN_10bc4020` | [0x10B9CAD0](../src/Game/cStateStack_16.cpp), [0x10B9D7E0](../src/Game/Unsorted_10B9D7E0.cpp) |
| `0x10BC4160` | `Class_10BC4160::FUN_10bc4160` | [0x10BCE0D0](../src/Game/StateAnimation.cpp), [0x10BDFEF0](../src/Game/ReturningState.cpp) |
| `0x10BC4BF0` | `Class_10BC4BF0::GetTargetLinkType` | [0x10BCE0D0](../src/Game/StateAnimation.cpp), [0x10BDFEF0](../src/Game/ReturningState.cpp) |
| `0x10BD4160` | `cStructArray::CopyFrom` | [0x10BF7B90](../src/Game/BehaviorContextConstruction.cpp) |
| `0x10BDF0A0` | `Class_10BDF0A0::FUN_10bdf0a0` | [0x10BDFEF0](../src/Game/ReturningState.cpp) |
| `0x10BECEE0` | `UCanvas::SetViewport` | [0x10B9DDB0](../src/Game/PatrolStack.cpp) |
| `0x10BF7E00` | `Class_10BF7F90::FUN_10bf7e00` | [0x10BCE0D0](../src/Game/StateAnimation.cpp), [0x10BDFEF0](../src/Game/ReturningState.cpp) |
| `0x10BF7F90` | `Class_10bf7f90::FUN_10bf7f90` | [0x10BCE0D0](../src/Game/StateAnimation.cpp), [0x10BDFEF0](../src/Game/ReturningState.cpp) |
| `0x10BFC3A0` | `Class_10BFD210::FUN_10bfc3a0` | [0x10BC40E0](../src/Game/StateEligibility.cpp) |
| `0x10BFF460` | `Class_10BFF460::FUN_10bff460` | [0x10BC40E0](../src/Game/StateEligibility.cpp) |
| `0x10C00480` | `GetTimeSeconds` | [0x10C083C0](../src/Game/Unsorted_10C08130.cpp), [0x10BDFEF0](../src/Game/ReturningState.cpp) |
| `0x10C00710` | `FUN_10c00710` | [0x10B9DDB0](../src/Game/PatrolStack.cpp) |
| `0x10C06F80` | `FUN_10c06f80` | [0x10C07960](../src/Game/Class_10E97B68_3.cpp) |
| `0x10C06FF0` | `Class_10E97B68::FUN_10c06ff0` | [0x10C07960](../src/Game/Class_10E97B68_3.cpp) |
| `0x10C07220` | `Class_10C07220::FUN_10c07220` | [0x10C07960](../src/Game/Class_10E97B68_3.cpp) |
| `0x10C07690` | `Class_10E97B68::AddIfMissing` | [0x10C07960](../src/Game/Class_10E97B68_3.cpp) |
| `0x10C16580` | `Class_10E98C8C::Class_10E98C8C` | [0x10C36700](../src/Game/ReturnOrientationCommand.cpp) |
| `0x10C165A0` | `Class_10E98C8C::~Class_10E98C8C` | [0x10C36700](../src/Game/ReturnOrientationCommand.cpp) |
| `0x10C27090` | `MC_MoveToPoint::IsCurrent` | [0x10C2EA30](../src/Game/ReturnMovementCommand.cpp) |
| `0x10C27140` | `MC_Follow::GetStateFromFlags` | [0x10C2EA30](../src/Game/ReturnMovementCommand.cpp) |
| `0x10C27290` | `MoveCommand::~MoveCommand` | [0x10C36700](../src/Game/ReturnOrientationCommand.cpp), [0x10C2EA30](../src/Game/ReturnMovementCommand.cpp) |
| `0x10C27320` | `MoveCommand::MoveCommand` | [0x10C36700](../src/Game/ReturnOrientationCommand.cpp), [0x10C2EA30](../src/Game/ReturnMovementCommand.cpp) |
| `0x10C2E350` | `Class_10E9AA20::Class_10E9AA20` | [0x10BC4240](../src/Game/StateRequest.cpp) |
| `0x10C2E370` | `Class_10E9AA2C::Class_10E9AA2C` | [0x10BC4240](../src/Game/StateRequest.cpp) |
| `0x10C2E6E0` | `MC_PlayAnimation::MC_PlayAnimation` | [0x10BCE0D0](../src/Game/StateAnimation.cpp) |
| `0x10C2EA30` | `MC_MoveToPoint::MC_MoveToPoint` | [0x10BDFEF0](../src/Game/ReturningState.cpp) |
| `0x10C2EB40` | `MC_MoveToPoint::FUN_10c2eb40` | [0x10C2EA30](../src/Game/ReturnMovementCommand.cpp) |
| `0x10C2EB60` | `MC_MoveToPoint::IsFinished` | [0x10C2EA30](../src/Game/ReturnMovementCommand.cpp) |
| `0x10C2EB90` | `MC_MoveToPoint::FUN_10c2eb90` | [0x10C2EA30](../src/Game/ReturnMovementCommand.cpp) |
| `0x10C2EBB0` | `destructor'` | [0x10C2EA30](../src/Game/ReturnMovementCommand.cpp) |
| `0x10C2EBD0` | `MC_MoveToPoint::GetClassName` | [0x10C2EA30](../src/Game/ReturnMovementCommand.cpp) |
| `0x10C36630` | `MC_Turn::FUN_10c36630` | [0x10C36700](../src/Game/ReturnOrientationCommand.cpp) |
| `0x10C36700` | `MC_Turn::MC_Turn` | [0x10BDFEF0](../src/Game/ReturningState.cpp) |
| `0x10C37960` | `FUN_10c37960` | [0x10C36630](../src/Game/ReturnOrientationInitialization.cpp) |
| `0x10C3B6A0` | `Class_10E9AF6C::Class_10E9AF6C` | [0x10C2EA30](../src/Game/ReturnMovementCommand.cpp) |
| `0x10C7D570` | `Class_10C7D570::FUN_10c7d570` | [0x10B9C4A0](../src/Game/AAIPawnController_7.cpp), [0x10B9CAD0](../src/Game/cStateStack_16.cpp), [0x10B9DDB0](../src/Game/PatrolStack.cpp), [0x10BDFEF0](../src/Game/ReturningState.cpp) |
| `0x10DBD510` | `Class_10C7D570::FUN_10dbd510` | [0x10BC40E0](../src/Game/StateEligibility.cpp) |
| `0x10E8BF90` | `Class_10E8BF90::`vftable'` | [0x10B9CAD0](../src/Game/cStateStack_16.cpp) |
| `0x10E93B5C` | `DAT_10e93b5c` | [0x10BF7B90](../src/Game/BehaviorContextConstruction.cpp) |
| `0x10E9AA7C` | `DAT_10e9aa7c` | [0x10C2EA30](../src/Game/ReturnMovementCommand.cpp) |
| `0x10E9AD9C` | `DAT_10e9ad9c` | [0x10C36700](../src/Game/ReturnOrientationCommand.cpp) |
| `0x10EAFBDC` | `DAT_10eafbdc` | [0x10A491B0](../src/Game/PopulationPointEligibility.cpp) |
| `0x10F35DEC` | `DAT_10f35dec` | [0x10A491B0](../src/Game/PopulationPointEligibility.cpp) |
| `0x10F3A054` | `DAT_10f3a054` | [0x10A491B0](../src/Game/PopulationPointEligibility.cpp) |
| `0x10F3A058` | `DAT_10f3a058` | [0x10A491B0](../src/Game/PopulationPointEligibility.cpp) |
| `0x10F46DA0` | `DAT_10f46da0` | [0x10B9CAD0](../src/Game/cStateStack_16.cpp) |
| `0x10FF661C` | `AAIPathPoint::PrivateStaticClass` | [0x10B9DDB0](../src/Game/PatrolStack.cpp) |
| `0x10FF664C` | `AAIPawnController::PrivateStaticClass` | [0x10BC3190](../src/Game/PawnModelInitialization.cpp) |

### Mesh lookup and flee submission

The mesh receiver at `0x10BAA580` reads the wrapper owner at `+0x34`, resolves
its object, checks `USkeletalMeshInstance::StaticClass()` with `UObject::IsA`,
and caches a compatible receiver at `+0x164`. Those offsets and the calls in
the matched body support the local ABI view; they do not name other fields.

The flee submission body at `0x10BEBC70` retries destination selection once,
submits a move command when it succeeds, and otherwise marks failure. Its
local complete declarations retain the observed eleven-slot movement vtable,
`0x34`-byte context and `0x58`-byte move command (compile-time size checks in
the source). `MoveCommand::Virtual6` binds to the shared `0x10D660B0` return
entry; its two-argument slots 7/8 bind to `0x109E38B0`. These are declaration
aliases to existing folded code, not new implementation matches. Helpers
`0x10BEA3B0` and `0x10BEB6C0` are called through their recorded declarations;
their bodies are not contributed or credited here.

| Function | Bytes | Static role and matching source |
|---|---:|---|
| `0x10BAA580` | 100 | [Cache and type-check the associated skeletal-mesh instance receiver](../src/Game/Class_10BAA580_2.cpp) |
| `0x10BEBC70` | 329 | [Resolve/rebuild flee destination and submit a movement command while preserving context lifetime](../src/Game/State_Flee_8.cpp) |

External references first used by this group (common references are recorded
with the earlier group above):

| Target address | Referenced name | Matching caller evidence |
|---|---|---|
| `0x10991E10` | `Class_10B21820::FUN_10991e10` | [0x10BAA580](../src/Game/Class_10BAA580_2.cpp) |
| `0x109B2760` | `USkeletalMeshInstance::InitializePrivateStaticClassUSkeletalMeshInstance` | [0x10BAA580](../src/Game/Class_10BAA580_2.cpp) |
| `0x109CC060` | `USkeletalMeshInstance::GetPrivateStaticClassUSkeletalMeshInstance` | [0x10BAA580](../src/Game/Class_10BAA580_2.cpp) |
| `0x10BEA3B0` | `Class_10BEA3B0::FUN_10bea3b0` | [0x10BEBC70](../src/Game/State_Flee_8.cpp) |
| `0x10BEB6C0` | `Class_10BEB6C0::FUN_10beb6c0` | [0x10BEBC70](../src/Game/State_Flee_8.cpp) |
| `0x10F35488` | `USkeletalMeshInstance::PrivateStaticClass` | [0x10BAA580](../src/Game/Class_10BAA580_2.cpp) |
