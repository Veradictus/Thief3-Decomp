# Handoff: T3SDK status (2026-09-27)

## Goal

A **modding SDK** for Thief: Deadly Shadows (Steam, `T3Main.exe`), used
against the local game install. It should support ambitious mods, multiplayer
first among them. Around it: a **launcher** for players and map makers, a
**Godot map workflow** (export, edit, repack), and a public **matching
decompilation** worked mostly by Claude agents under the strict gate in
`tools/agent/`, listed on decomp.dev. What we identify gets its name in
`symbols.txt` and its notes in `docs/engine.md`. Matched source is public
(`src/`, `include/`); raw decompiler output stays local (`build/`,
`ghidra/`), and the repository never holds game files or data (see
[CONTRIBUTING.md](../CONTRIBUTING.md)).

## State of the machine

- The game is **closed**. The SDK build from before this round is deployed
  in `System/` (manifest `build/sdk/deployed.json`), with `T3SDK.ini` at its
  defaults. `System/T3SDK.log` is appended to on every run.
- GitHub: `Veradictus/Thief3-Decomp`, Conventional Commits (see
  [CONTRIBUTING.md](../CONTRIBUTING.md)); the user decides what is merged.
  This round's work is on branch `claude/keen-ramanujan-g6qnld` (PR #1).
  Commits and PRs carry no session links.
- The Ghidra database in `ghidra/` is analysed and has the names from
  `symbols.txt` applied (the export round-trips byte for byte).
- The asset exporter turns all 32 maps into a Godot 4.7 project in
  `build/assets/godot/`, tested against the user's Godot 4.7.2. Maps
  exported before this round lack the editor plugin's metadata: re-export.
- None of this round's work has touched the real install yet: the launcher,
  the map writer, the editor plugin and the matching harness were tested on
  placeholder installs, synthetic maps and synthetic target objects (see Next
  steps 1).

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
| Map and asset export to Godot 4.7; Godot map viewer | `tools/assets/`, `tools/assets/godot/` | works for all 32 maps (static geometry, lights, actor data) |
| Godot editor plugin: move/rotate/scale actors, edit gamesys values, save `<Level>.edits.json` | `tools/assets/godot/addons/t3_map_editor/` | headless tests pass; not tried on a real map |
| Map writer: byte-exact round trip, apply edits, install/restore with backup | `tools/assets/upkgwrite.py`, `t3pack.py` | synthetic tests pass; not run on real maps |
| Launcher (Tauri): setup, play, SDK install, mods, `T3SDK.ini`, Map Studio, task queue | `launcher/`, [launcher.md](launcher.md) | runs (tested under Xvfb on Linux); Windows build green in CI, not yet run on Windows |
| Release bundle (tools, prebuilt SDK, embeddable Python) | `tools/stage_launcher.py` | builds in CI |
| Matching harness: queue, context, try, strict gate, integrate, waves | `tools/agent/`, `.claude/agents/t3-matcher.md`, `.claude/skills/t3-match/`, [matching.md](matching.md) | 14 synthetic tests pass with the real MSVC 7.1 via wibo; not run on the real exe |
| CI: launcher and SDK builds (artifacts), releases on `v*` tags, decomp.dev report | `.github/workflows/` | launcher/SDK green; decomp.dev job waits for `T3_BUILD_IMAGE` ([decomp-dev.md](decomp-dev.md)) |

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

1. **Verify this round on the real install** (ask the user; close the game
   after each test):
   - `tools/assets/t3pack.py roundtrip --all`: every package `identical`;
     note what it says about the summary DWORD at 0x24.
   - Re-export a small map, open it in Godot: "Changed actors: 0" with no
     warnings. Move one visible prop, **Save T3 edits**, `t3pack.py apply`,
     `install`, load the map in the game, `restore`.
   - Install the launcher from the PR's `launcher-windows` artifact and run
     setup, Install T3SDK, Play, Remove. Then tag `v0.1.0` for the first
     release.
2. **decomp.dev**: the private build image, the `T3_BUILD_IMAGE` variable and
   the registration ([decomp-dev.md](decomp-dev.md)). Needs the owner's GitHub
   account.
3. **Matching pilot** (about 300 functions, stratified by size; see
   [matching.md](matching.md) and
   [research/llm-matching.md](research/llm-matching.md)): first check `try.py`
   and `accept.py` on real split functions (a plain one, a switch, an EH
   function), then `wave.py` with a few workers, review every result by hand,
   and measure matches and cost per size bucket before scaling. Pin the
   compiler flags first with ~20 varied functions (`/G6` vs `/G7`, `/GS`).
4. **SDK generator** (roadmap 2 below): the class layouts it emits are what
   matching agents most need (wrong offsets are the top failure in every
   published agent decomp).
5. **Ask the user to confirm** real alt-tab and clicks on another monitor,
   then check the HUD in a level.
6. **SDK options in the game's settings** (user request). The launcher's SDK
   settings page covers it outside the game; in-game leads: the options names
   table `0x10E6ED70`, the A/V row refresh `0x10B72DD0`, `T3UI.ini`
   (`TitleOptionsWindow`, `AVOptionsWindow`, `UniqueOptionsWindow`), and
   `UILayoutTrace`.
7. **3D field of view for widescreen** (Hor+): not found yet. The
   `[WindowManager]` FOV is the UI camera's; `0x10A39230` is a camera-overlay
   FOV. The community's `T3FovPatch.exe` binary patch has not been reverse
   engineered.
8. **Shutdown crash** at `0x1098A466` (vanilla bug): fix it, so the game exits
   cleanly.
9. **Background behaviour**: borderless keeps the game running when it loses
   focus. The user may want a pause-on-focus-loss option.
10. **Map editor** (see `docs/assets.md`, sections 6 and 8):
    - skins and other struct values in `t3pack.py`, then adding and removing
      actors;
    - some materials show a noise texture as their colour: the exporter's
      choice of texture stage needs a look;
    - characters, animation, physics hulls, particles and sounds are not
      exported yet.
11. **Name and document as we go**: every function the SDK touches gets its
    name in `symbols.txt` and an entry in `docs/engine.md`.

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

- The MSVC 7.1 bundle, wibo and objdiff-cli run in a Linux cloud container
  (`tools/download_tool.py`), so matching can run in the cloud too, given the
  exe from a private source.
- objdiff's relocation rulers cannot tell MSVC COMDAT constants apart (every
  one sits at offset 0), and `report generate` ignores callees unless
  `functionRelocDiffs` is pinned (it now is). `accept.py` resolves both sides
  to addresses instead ([matching.md](matching.md)).
- MSVC 7.1 names unwind funclets `$Lnnn`, not `__unwindfunclet$...`, and `/O2`
  inlines same-file functions even when defined after the caller.
- `T3SDK_BUILD_DIR` moves every tool's output (the launcher sets it for its
  bundled tools: `%LOCALAPPDATA%\org.t3sdk.launcher\build`).
- Godot 4.7.2 runs headless for the plugin and viewer tests:
  `godot_check.py --editor-selftest`, `--viewer`.

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
