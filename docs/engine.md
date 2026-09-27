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
| intro-movie player (`PlayIntroMovies`) | `0x10A50C30` | verified: returning at once skips the logo movies |

- Functions calling `PeekMessageA` (IAT `0x10E4734C`): `0x10A50C30` (intro
  movies), `0x10AEB350`, `0x10C83450` (`UD3DRenderDevice::Lock`, its
  device-lost wait), `0x10C84070`. Decompiled output: `build/re_mainloop.c`
  (regenerate with `Decompile.java refs:0x10e4734c`).
- The game exits through `TerminateProcess` on itself (called from `0x10906D80`
  and `0x10901D60`; the latter looks like the error handler) or through CRT
  `exit` (IAT: `TerminateProcess` `0x10E47184`, `ExitProcess` `0x10E47268`).
- Closing the window crashes during shutdown, with the SDK or without: exit
  code `0xC0000005`. The SDK's crash reporter places the fault at `0x1098A466`
  (reading address 0). Not analysed yet.
- Not found yet: `UObject::GObjInitialized`, `GEngine`.

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
| `UWindowsViewport::ViewportWndProc` | `0x10C8B820` | static |
| `UWindowsViewport::Exec` (console commands: EndFullscreen, ToggleFullscreen, SetRes, ...) | `0x10C8ADE0` | static |
| `UWindowsViewport::EndFullscreen` (logs "EndFullscreen") | `0x10C86630` | verified (log) |
| `UWindowsViewport::ToggleFullscreen` (logs "AttemptFullscreen") | `0x10C87560` | static |
| `UD3DRenderDevice::Lock` (logs "TestCooperativeLevel failed", "BeginScene failed") | `0x10C83450` | verified (log) |
| `UpdateWindowTitle` (localised "Thief - Deadly Shadows") | `0x10C872C0` | static |

On `WM_ACTIVATEAPP(FALSE)` the window procedure resets the device to the
creation parameters at `0x10F2C86C` (the call at `0x10C8BF6B`) unless
`TestCooperativeLevel` already reports the device lost. An exclusive
fullscreen device always is lost by then, so vanilla never makes that call. A
windowed (borderless) device is not; the reset fails, and `Lock` then sleeps in
10 ms steps waiting for the device, so the game freezes. The SDK skips that one
reset (verified: focus loss and exit both pass through it).

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
