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
| object iterator begin / next (per-class lists, Ion Storm addition) | `0x1096BD50` / `0x1096C8D0` | static |

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
| `0x2C` | `UStruct` SuperField (on class objects) | verified: all 287 classes chain up to `Object` |
| class `+0xE8` | the class's default object | static, probable |

Stock Unreal Engine 2 has SuperField at `0x28`; this fork has one more field
before it. The SDK re-detects Outer and SuperField at startup instead of
trusting these numbers. The checks are structural runtime validation, not a
proof that every object or class layout in this document is correct.

Runtime numbers from a test run: 4,488 objects and 287 classes once the core
packages are loaded, about 6,000 objects and 9,800 names at the main menu. The
menu level is `Entry`, and its player controller is `Entry.Camera__0` (class
`Engine.Camera`, a `PlayerController`).

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

The table names 234 `UObject` natives in `symbols.txt`. Seven functions are
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
| `Config::Find` (core lookup) | `0x109103D0` | static |
| `bool Config::GetBool(section, key, bool*, file)` | `0x109108B0` | static |
| `bool Config::GetFloat(section, key, float*, file)`, `__thiscall` | `0x10910B60` | verified (hooked) |
| `bool Config::GetString(section, key, char**, file)` | `0x10910E20` | static |

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
| `GetUIScreenSize` (the layout size as an `FVector`) | `0x109E47E0` | static |
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
layout size (the layout size for top-level windows): CENTER `x = (avail - w)/2
+ Pos_X`, LEFT and absolute `x = Pos_X`, RIGHT `x = avail - w + Pos_X`; y is the
same with TOP/BOTTOM. The result is relative to the parent. `Width=FULLSCREEN`
makes `w` the layout width, so a full-width window at `Pos_X=325` (the main
menu buttons) sits 325 units from the left edge at any width. Callers use the
returned pointer: a detour must return it.

## Display: viewport and Direct3D 8

| What | Address | Status |
|---|---|---|
| `InitDirect3D`: `Direct3DCreate8(220)`, `CreateDevice` (HAL, hardware then software vertex processing) | `0x10919730` | verified (hooked through the import) |
| `D3DPRESENT_PARAMETERS` the device is created with | `0x10F2C86C` | verified |
| `IDirect3D8*` / `IDirect3DDevice8*` | `0x10F2C8B4` / `0x10F2C8B8` | static |
| `UWindowsViewport::ViewportWndProc` | `0x10C8B820` | verified (hooked: the SDK keeps a borderless game running) |
| `UWindowsViewport::Exec` (console commands: EndFullscreen, ToggleFullscreen, SetRes, ...; list in [game/console.md](game/console.md)) | `0x10C8ADE0` | static |
| `UWindowsViewport::EndFullscreen` (logs "EndFullscreen") | `0x10C86630` | verified (log) |
| `UWindowsViewport::ToggleFullscreen` (logs "AttemptFullscreen") | `0x10C87560` | static |
| `UD3DRenderDevice::Lock` (logs "TestCooperativeLevel failed", "BeginScene failed") | `0x10C83450` | verified (log) |
| `UD3DRenderDevice::SetRes`: present parameters (fullscreen interval ONE with VSynch, else IMMEDIATE; none when windowed), creates or resets the device, then `LoadingScreen::Begin` for the current map | `0x10C84070` | static |
| VSynch as `SetRes` reads it (`Options::ApplyVideo` writes it) | render device `+0x40DC` | static |
| `LoadingScreen::Begin(device, map, flag)`, `__cdecl`: `<[Paths] DynamicTextures>\<map>.dds` (else `Loading1.dds`) as the background, the `[LoadingScreen]` logo and caption textures; draws and presents | `0x109E1FC0` | static (hooked by the SDK's level-change curtain) |
| `LoadingScreen::LoadLayout` (`[LoadingScreen]` positions and sizes) | `0x109DFBA0` | static |
| `UpdateWindowTitle` (localised "Thief - Deadly Shadows") | `0x10C872C0` | static |

The menu cursor is a Direct3D hardware cursor: a 32x32 `A8R8G8B8` image with
its hot spot at 0,0. Every frame the game calls the device's
`SetCursorProperties` and `ShowCursor` (vtable slots 10 and 12) and user32's
`ShowCursor` and `SetCursor` (counted with the SDK's `FrameStats`).

On `WM_ACTIVATEAPP(FALSE)` the window procedure resets the device to the
creation parameters at `0x10F2C86C` (the call at `0x10C8BF6B`) unless
`TestCooperativeLevel` already reports the device lost. An exclusive
fullscreen device always is lost by then, so vanilla never makes that call. A
windowed (borderless) device is not; the reset fails, and `Lock` then sleeps in
10 ms steps waiting for the device, so the game freezes. The SDK skips that one
reset (verified: focus loss and exit both pass through it).

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
