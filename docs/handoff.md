# Handoff: T3SDK status (2026-09-27)

## Goal

A **modding SDK** for Thief: Deadly Shadows (Steam, `T3Main.exe`), used
against the local game install. It should support ambitious mods, multiplayer
first among them. The matching-decompilation setup (objdiff, delink,
`symbols.txt`) is the reverse-engineering workbench. Decompilation goes along
with the SDK work: whatever we identify gets its name in `symbols.txt` and its
notes in `docs/engine.md`. Decompiler output stays local (`build/`,
`ghidra/`); the repository never holds game code or data (see
[CONTRIBUTING.md](../CONTRIBUTING.md)).

## State of the machine

- The game is **closed**. The current SDK build is **deployed** in `System/`
  (manifest `build/sdk/deployed.json`), with `T3SDK.ini` at its defaults.
  `System/T3SDK.log` is appended to on every run.
- The repository is on GitHub (`git@github.com:Veradictus/Thief3-Decomp.git`,
  branch `main`), committed in Conventional Commits style (see
  [CONTRIBUTING.md](../CONTRIBUTING.md)). The user decides when to commit and
  push.
- The Ghidra database in `ghidra/` is analysed and has the names from
  `symbols.txt` applied (the export round-trips byte for byte).
- The asset exporter (Godot-friendly maps, meshes, textures) in
  `tools/assets/` and `docs/assets.md` works for all 32 maps and is tested
  against the user's local Godot 4.7.2. A Godot viewer (map picker, fly
  camera, actor inspector) is being added. Neither is committed yet.

## What exists

| Piece | Where | Status |
|---|---|---|
| Loader: `dinput8.dll` proxy, entry-point patch, MinHook | `sdk/loader/dllmain.cpp` | works |
| Start-up, frame/exit hooks, settings, guarded mod callbacks | `sdk/loader/sdk.cpp` | works |
| Engine access, lifecycle (`Ready`/`Exiting`), layout validation, log hook | `sdk/loader/engine.cpp` | works |
| Mod loading from `System/mods/*.dll` | `sdk/loader/mods.cpp` | works |
| Crash reporter (vectored handler, logs location/registers/stack) | `sdk/loader/crash.cpp` | works |
| Fixes: skip intro movies | `sdk/loader/fixes.cpp` | works |
| Display: native resolutions, borderless window, widescreen UI | `sdk/loader/display.cpp` | works (details below) |
| Main-menu version label, menu input diagnostics | `sdk/loader/menu.cpp` | works |
| Public C API (`T3SdkApi` v1), C++ engine header | `sdk/include/t3sdk/` | |
| Example mod | `sdk/mods/hello/hello.cpp` | works |
| Build/deploy/run/screenshot/click/keys/close tool | `tools/sdk.py` | works |
| Ghidra scripts: Decompile, Disassemble, ImportNames, ExportSymbols | `tools/ghidra/` | work |

Commands are in [sdk.md](sdk.md) (SDK) and [../CLAUDE.md](../CLAUDE.md).
`tools/sdk.py click`/`keys`/`screenshot` make UI tests possible without
touching the user's mouse: the main menu reacts to posted clicks.

## Display fixes: how they work

- **Resolutions**: the five-entry table at `0x10E6EDC4`/`0x10E6EDD8` gets the
  monitor's own modes, native last (option index 4).
- **Borderless**: `Direct3DCreate8` is hooked through the import;
  `CreateDevice` and `Reset` get windowed presentation parameters and the
  window becomes a popup covering its monitor. The focus-loss `Reset`
  (`WM_ACTIVATEAPP`, call at `0x10C8BF6B`, parameters `0x10F2C86C`) is
  skipped. It used to fail and freeze the game (in `UD3DRenderDevice::Lock`)
  on alt-tab, on a click on another monitor, and on exit.
- **Widescreen UI**: `[WindowManager] AssumedUIScreenWidth` is answered as
  `480 x aspect` (852 on 16:9), which keeps proportions. `Window::PlacedPosition`
  (`0x10A52530`) is hooked. Children of a full-width window inside a modal
  window (every menu, popup and briefing) are moved into a centered 640-wide
  frame: LEFT and absolute positions +106, RIGHT -106, full-width windows with
  an x offset +106, centered windows unchanged. The HUD is not modal and keeps
  its screen-edge anchors. Verified on the main menu and the options screen.
  `UILayoutTrace=1` logs every window's placement.

## Test results (2026-09-27, `tools/sdk.py run`)

- Start-up: intros skipped, the menu comes up about 4 s after launch.
- Main menu and options screen centered on 2560x1440; no faults logged.
- Simulated focus loss (posted `WM_ACTIVATEAPP` 0 then 1): the reset is
  skipped, the game keeps rendering and responding.
- Exit through WM_CLOSE: 1.7 s, exit code `0xC0000005`. Vanilla crashes the
  same way; the crash reporter puts the fault at `0x1098A466` (reads address 0
  during shutdown).

## Next steps

1. **Ask the user to confirm** real alt-tab and clicks on another monitor.
   Only the message was simulated here. Then check the HUD in a level.
2. **SDK options in the game's settings** (user request): a way to toggle
   "skip intros" (and the display options) from the options screen. Leads:
   the options names table `0x10E6ED70`, the A/V row refresh `0x10B72DD0`,
   `T3UI.ini` (`TitleOptionsWindow`, `AVOptionsWindow`, `UniqueOptionsWindow`),
   and `UILayoutTrace` to map the screen.
3. **3D field of view for widescreen** (Hor+): not found yet. The
   `[WindowManager]` FOV is the UI camera's; `0x10A39230` is a camera-overlay
   FOV. The community's `T3FovPatch.exe` binary patch has not been reverse
   engineered.
4. **Shutdown crash** at `0x1098A466` (vanilla bug): fix it, so the game exits
   cleanly.
5. **Background behaviour**: borderless keeps the game running when it loses
   focus. The user may want a pause-on-focus-loss option.
6. **Name and document as we go**: every function the SDK touches gets its
   name in `symbols.txt` and an entry in `docs/engine.md`. Matching a function
   with MSVC 7.1 (`/O2 /GX`) through `splits.txt` and `configure.py` is useful
   to confirm how it was compiled, but the decompiled code stays local.

## Roadmap towards multiplayer

1. ~~Stabilise M1~~: done (lifecycle gating, SEH around mod callbacks, clean
   exit parity with vanilla).
2. **SDK generator**: walk each `UStruct`'s Children (`UField::Next`) and
   `UProperty` fields (Offset, ElementSize, ArrayDim, PropertyFlags). Detect
   their offsets at runtime the way SuperField is detected. Emit C++ headers
   for classes, structs, enums and functions, and an API call that dumps them.
3. **Script events**: find `UObject::ProcessEvent` (the `eventXxx` thunks call
   `FindFunctionChecked` then ProcessEvent). Hook it for pre/post callbacks per
   function, and add `CallFunction` for mods and a console-command hook.
4. **World access**: `ULevel::SpawnActor` (anchored by its error strings),
   `GEngine` and the current level, the player pawn and its transforms,
   destroying actors.
5. **Overlay and input**: the device is already hooked (`display.cpp`); add
   Present/EndScene for an in-game UI. Sneaky Upgrade users run a d3d8
   wrapper, so keep hooking through the import, not by replacing `d3d8.dll`.
6. **Multiplayer prototype** as a mod: a UDP transport (for example ENet),
   local player transform sync, puppet pawns for remote players (look at
   `PlayerPawnPuppet`), then world events (doors, items, AI state). There is
   no engine net layer to reuse.

## Useful facts

- Decompiled outputs from this work are in `build/re_*.c` (regenerate with
  `Decompile.java`).
- Other mods: Sneaky Upgrade uses `d3d8.dll` (d3d8to9, dgVoodoo2, DXVK), so
  `dinput8.dll` is free for our loader.
- `tools/sdk.py run` starts the game through Steam (`steam.exe -applaunch
  6980`), which runs `runme.exe` → `t3.exe` → `T3Main.exe`. The SDK loads
  into `T3Main.exe` only.
- The main menu plays the attract-mode intro after 30 s without input
  (`Attract_Mode_Intro_Timeout`); a click skips it.
- clangd uses `.clangd` → `build/sdk/compile_commands.json` with
  `--target=i686-pc-windows-msvc`. Without a build it shows false 64-bit errors.
