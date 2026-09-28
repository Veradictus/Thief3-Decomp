# Handoff: T3SDK status (2026-09-28)

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

- The game is **closed**. `System/` holds an SDK build from before frame
  pacing and the loading-screen curtain (manifest `build/sdk/deployed.json`):
  deploy the current build before testing those. `System/T3SDK.log` is
  appended to on every run.
- GitHub: `Veradictus/Thief3-Decomp`, Conventional Commits (see
  [CONTRIBUTING.md](../CONTRIBUTING.md)). Agents commit on `main` and never
  push: the user pushes. Commits and PRs carry no session links.
- The Ghidra database in `ghidra/` is analysed and has the names from
  `symbols.txt` applied (the export round-trips byte for byte).
- The asset exporter turns all 32 maps into a Godot 4.7 project in
  `build/assets/godot/`, tested against the user's Godot 4.7.2. Inn has been
  re-exported with the editor plugin; the other maps predate it: re-export
  them (Map Studio, or `t3map.py`) before editing.
- On the real install: `t3pack.py roundtrip --all` reports all 55 packages
  identical, and `apply` works on Inn (a dry run moved and scaled one fence;
  every other object stayed byte-identical). No patched map has been loaded
  in the game yet. The launcher builds and runs on Windows (`yarn tauri
  dev`); it needs Rust's MSVC toolchain, which `yarn tauri` selects on its
  own (see [launcher.md](launcher.md)).
- Matching runs on the real split: 57 functions are matched and integrated
  (`src/Game/`, and 53 `UObject` script natives in `src/Engine/UObject.cpp`,
  about 1.7 KB). The game's native table named 234 natives (`docs/engine.md`,
  "Script natives"); `include/Core/Core.h` has what they need, and
  `wave.py --name '^UObject::exec'` works through the rest (the first wave:
  six Sonnet workers, 32 matched, $21). decomp.dev shows the committed
  report `progress/PC_20040610/report.json` (hidden from its list below 0.5%
  matched): regenerate it after integrating, see next step 2.

## What exists

| Piece | Where | Status |
|---|---|---|
| Loader: `dinput8.dll` proxy, entry-point patch, MinHook | `sdk/loader/dllmain.cpp` | works |
| Start-up, frame/exit hooks, settings, guarded mod callbacks | `sdk/loader/sdk.cpp` | works |
| Engine access, lifecycle (`Ready`/`Exiting`), layout validation, log hook | `sdk/loader/engine.cpp` | works |
| Mod loading: `System/mods/load-order.txt` (packages), then `System/mods/*.dll` | `sdk/loader/mods.cpp` | loose DLLs work; the load order is not yet built or run (see Next steps 1) |
| Crash reporter (vectored handler, logs location/registers/stack) | `sdk/loader/crash.cpp` | works |
| Fixes: skip intro movies | `sdk/loader/fixes.cpp` | works |
| Display: native resolutions, borderless window (cursor, VSync, focus, running in the background), frame pacing, widescreen UI | `sdk/loader/display.cpp` | works (details below); frame pacing and VSync not yet tried in the game |
| Level-change curtain (keeps the loading screen up while the game restarts) | `sdk/loader/curtain.cpp` | a black version worked; the loading-screen version is not yet tried in the game |
| Main-menu version label, menu input diagnostics | `sdk/loader/menu.cpp` | works |
| Public C API (`T3SdkApi` v1), C++ engine header | `sdk/include/t3sdk/` | |
| Example mod | `sdk/mods/hello/hello.cpp` | works |
| Build/deploy/run/screenshot/click/keys/close tool | `tools/sdk.py` | works |
| Ghidra scripts: Decompile, Disassemble, ImportNames, ExportSymbols | `tools/ghidra/` | work |
| Map and asset export to Godot 4.7; Godot map viewer | `tools/assets/`, `tools/assets/godot/` | works for all 32 maps (static geometry, lights, actor data) |
| Godot editor plugin: move/rotate/scale actors, edit gamesys values, save `<Level>.edits.json` | `tools/assets/godot/addons/t3_map_editor/` | headless tests pass; not yet used by hand on a real map |
| Map writer: byte-exact round trip, apply edits, install/restore with backup | `tools/assets/upkgwrite.py`, `t3pack.py` | round trip identical on the real install; `apply` checked on Inn; no patched map loaded in the game yet |
| Texture packs: `.ibt` writer, DDS to texture resource, list/check/apply/restore with backup, `--selfcheck` | `tools/assets/ibtwrite.py`, `t3texpack.py` | synthetic tests pass; not run on real bundles |
| Launcher (Tauri): setup, play, SDK install, mods, `T3SDK.ini`, Map Studio, task queue | `launcher/`, [launcher.md](launcher.md) | runs on Windows (`yarn tauri dev`) and under Xvfb on Linux; Windows build green in CI |
| Mod manager: `.t3mod` install/upgrade/remove, load order, profiles, checks, `files/` overlay, texture-pack tasks, mod index browser | `launcher/src-tauri/src/mods.rs`, `launcher/src/pages/Mods.svelte`, [mods.md](mods.md) | Rust tests on temporary game folders and UI tests pass; not run on Windows or a real install |
| Release bundle (tools, prebuilt SDK, embeddable Python) | `tools/stage_launcher.py` | builds in CI |
| Matching harness: queue, context, try, strict gate, integrate, waves | `tools/agent/`, `.claude/agents/t3-matcher.md`, `.claude/skills/t3-match/`, [matching.md](matching.md) | synthetic tests pass; runs on the real split (hand-matched functions, a smoke wave and a natives wave) |
| CI: launcher and SDK builds (artifacts), releases on `v*` tags, decomp.dev report | `.github/workflows/` | launcher/SDK green; the progress job checks and publishes the committed report ([decomp-dev.md](decomp-dev.md)) |

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
  `UILayoutTrace=1` logs every window's placement. Two exceptions: windows
  flush against the left or right edge (`Pos_X` 0, like the main menu's
  version line) stay at the screen edge, and the Inputs key table's
  `[KeyboardLayoutWindow]` width ratios are scaled back to the 640-wide frame.
- **Running in the background**: `UWindowsViewport::ViewportWndProc` is
  hooked; after its `WM_ACTIVATEAPP(FALSE)` handling the SDK sets
  `GIsAppActive` again and restores the saved pause state
  (`PauseInBackground=1` keeps the game's own pause).
- **Cursor**: the device's cursor calls and user32's `ShowCursor`/`SetCursor`
  are hooked; the game's cursor image becomes one scaled Windows cursor, rebuilt
  only when the image changes.
- **Level changes**: `ShellExecuteExA` (the call that starts `Ion Launcher.exe`
  in `RelaunchForLevelChange`) raises the curtain: the outgoing game copies its
  monitor, which shows the next level's loading screen, into a section a
  `rundll32` helper inherits and shows topmost. The incoming game's
  `LoadingScreen::Begin` hook lifts it with a posted message, and the helper
  hands that game the foreground. Fallbacks: the new game's window covering
  the monitor for 3 s, a click or key, 20 s.
- **Frame pacing**: `SmoothFrames` patches the TimeManager constructor's
  minimum step from 10 ms to 1 ms (see [engine.md](engine.md), Clock). With
  VSynch on, the windowed device uses `COPY_VSYNC`. `MaxFPS` waits before
  `Present` (a high-resolution waitable timer, then a short spin).

## Test results (2026-09-27, `tools/sdk.py run`)

- Start-up: intros skipped, the menu comes up about 4 s after launch.
- Main menu and options screen centered on 2560x1440; no faults logged.
- Simulated focus loss (posted `WM_ACTIVATEAPP` 0 then 1): the reset is
  skipped, the game keeps rendering and responding.
- Exit through WM_CLOSE: 1.7 s, exit code `0xC0000005`. Vanilla crashes the
  same way; the crash reporter puts the fault at `0x1098A466` (reads address 0
  during shutdown).

Later the same day, played by the user:

- The scaled cursor replaced the tiny, flickering one (confirmed by the user).
- Losing focus no longer pauses the game (log: "focus lost; the game keeps
  running").
- After New Game the next game window came to the front on its own; the
  first, black curtain covered the gap. The loading-screen curtain replaced
  it and has not been tried yet.
- `FrameStats`: 200 to 1255 fps in the menu, about 180 in Inn, `Present`
  0.3 ms. The user found the game choppy "as if stuck at 60 fps", which led
  to the TimeManager's 10 ms minimum step (`SmoothFrames`; not tried yet).

## Next steps

1. **Verify on the real install** (ask the user before deploying or
   launching; close the game after each test):
   - Deploy the current SDK. New Game should go from the menu straight to
     Inn's loading screen with no black gap. `FrameStats=1` should show
     about the monitor's refresh rate with VSynch on, and motion should be
     smooth. Watch for anything that behaves differently with more than 100
     world updates a second (physics objects, jumping, mantling, rope
     arrows); `SmoothFrames=0` turns it off.
   - The map edit: in Map Studio, open Inn in Godot, move a prop near the
     New Game start (`PlayerStart__1`, for example the iron fence
     `StaticMeshActor__364`), **Save T3 edits**, Repack, Install, New Game,
     Restore. Unknown: whether collision and baked lighting follow a moved
     static mesh.
   - Install the launcher from the latest release (v0.1.0 is out; v0.2.0
     is next, see [releasing.md](releasing.md)) and run setup, Install
     T3SDK, Play, Remove.
   - Texture packs ([mods.md](mods.md), `textures/`; [assets.md](assets.md),
     section 3): `tools/assets/t3texpack.py --selfcheck` must pass on every
     bundle; note the mip padding rule it prints and any layout statement
     marked NO. Then make a one-texture pack with an obvious change (a
     `list` name used in a small level), `check` and `apply` it, load the
     level and look at the texture, and `restore`. A level that fails to
     load or shows the old texture means the engine checks the 20-byte
     values (or reads the padding differently).
   - Mod manager and loader ([mods.md](mods.md), [launcher.md](launcher.md#mods)):
     build the SDK (the loader's `load-order.txt` code has only been
     syntax-checked with clang), deploy it, then from the launcher install a
     code package built from `templates/mod/` and a second one that needs
     it. `T3SDK.log` must show the packages first, in the page's order and
     named by folder, then the loose DLLs; a helper DLL next to a packaged
     DLL must load; a `load-order.txt` line with `..` must be skipped with a
     log line. Then a content overlay: a `files/` mod that replaces a
     loading screen (`Content/T3/Bitmaps`) must show in the game, the
     original must sit in `System/mods/originals/`, and switching the mod
     off must put it back. With a texture pack on, a `files/` mod that
     places an `.ibt` must queue restore, place the bundle, then apply.
2. **decomp.dev**: CI publishes `progress/PC_20040610/report.json`, which
   `python tools/progress_report.py write` makes from a local build (the exe
   stays local) and CI checks against `src/` ([decomp-dev.md](decomp-dev.md)).
   After each integration: write it and commit it with the source. On
   decomp.dev, set the project's default category to **main** (owner).
3. **Matching**:
   - Make objdiff's report count what the gate matched. The split objects
     read `fs:[0x0]` where compiled code refers to `__except_list`, so every
     function with an EH frame scores 99.x% (a post-split fixup adding those
     relocations would do), and a reference into a named array at an offset
     (`GNatives[2 * 256 + B]`) becomes a `DAT_` label of its own
     (execHighNative1-15 score 99.67%).
   - Continue the natives (`wave.py --name '^UObject::exec'`, about 180
     left). Review every accepted file before integrating: workers stand in
     for what the header lacks (local types, `Shim` subclasses to reach
     undeclared members, `DAT_` slices of tables); add the real declarations
     to `include/Core/Core.h`, redo those functions and accept them again.
   - Still unchecked on the real split: a switch table and the data ruler on
     float literals ([matching.md](matching.md)). Pin the compiler flags with
     varied functions (`/G6` vs `/G7`, `/GS`) before large waves outside the
     natives.
4. **SDK generator** (roadmap 2 below): the class layouts it emits are what
   matching agents most need (wrong offsets are the top failure in every
   published agent decomp).
5. **Check the HUD in a level** on a wide screen (alt-tab and clicks on other
   monitors are confirmed).
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
9. **High-DPI displays**: the game is DPI-unaware, so on a monitor scaled
   above 100% Windows stretches the borderless window (blurry), and the
   curtain helper works in the same scaled coordinates. Making both
   DPI-aware needs a tester with a scaled display.
10. **Map editor** (see `docs/assets.md`, sections 6 and 8):
    - skins and other struct values in `t3pack.py`; adding (copies) and
      removing actors works in the tools and the plugin, but no patched map
      has been loaded in the game yet: check that one with new and removed
      actors loads, and that a copy moved far from its original is lit and
      drawn (it keeps the original's zone and BSP leaf);
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
