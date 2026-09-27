# T3SDK Launcher

A desktop app for players and map makers that puts the SDK and the asset tools
behind buttons: play the game with T3SDK, turn mods on and off, change
`T3SDK.ini`, and take a map through export → edit in Godot → repack → install.
It is a [Tauri 2](https://tauri.app/) app: a Rust backend in
`launcher/src-tauri/` and a Svelte 5 UI in `launcher/src/`. The backend does
every file and process operation; the UI only calls its commands.

The launcher does not reimplement the tools. It runs the same command-line
tools a contributor uses (`tools/sdk.py`, `tools/assets/t3map.py`,
`tools/assets/t3pack.py`, `tools/assets/godot_check.py`) with the user's
Python, and shows their output live.

## Screens

| Screen | What it does |
|---|---|
| Setup | First run: finds the game (installer registry entry, Steam libraries, `T3_GAME_DIR`), Godot (`GODOT`, `PATH`, common folders), Python (the T3SDK `.venv`, the `py` launcher, `PATH`) and the T3SDK folder (walks up from the launcher). Each path is checked: the game's `T3Main.exe` SHA-1, `godot --version` (4.7+), Python 3.10+, the tools. |
| Play | Starts the game (through Steam for a Steam install, as the Play button does), shows whether the build is supported, installs or removes T3SDK (`sdk.py deploy`/`undeploy`), builds it (`sdk.py build`, needs Visual Studio), and shows the end of `T3SDK.log`. |
| Map Studio | Per map: export to Godot (then a headless Godot import), open it in the Godot editor or the viewer, repack the saved edits into a patched `.gmp`, install it into the game, restore the original. Also a byte-exact round-trip check of the unchanged map. |
| Mods | Lists `System/mods/*.dll`. Turning a mod off moves its `.dll` (and `.pdb`/`.ini`) into `System/mods/disabled/`, which the SDK does not load. |
| SDK settings | `System/T3SDK.ini` as switches. The list, order and descriptions come from the comments in the SDK's own `sdk/T3SDK.ini`, so new settings appear without launcher changes. Values are edited in place; the file's comments and line endings are kept. |
| Tasks | The job queue. Jobs run one at a time, in order; a job that depends on another (the import after an export) is skipped when that one fails. Output streams live and can be copied; a running job can be cancelled (its whole process tree on Windows). |
| Settings | The paths again, plus the Godot project folder (default `build/assets/godot` in the T3SDK folder). |

The launcher's own settings are `launcher.json` in the per-user config folder
(`%APPDATA%\org.t3sdk.launcher\` on Windows). Nothing is written to the
repository, and the game folder is written only by the SDK install, the mod
switches, `T3SDK.ini` edits and map installs (which back up the original
first; see [assets.md](assets.md)).

## Map files the launcher reads

Map Studio derives each map's state from files, so it stays right when the
tools are run by hand:

| State | File |
|---|---|
| in the game | `<game>/Content/T3/Maps/<id>.gmp` |
| exported, title, actor count | `<project>/<id>/<id>.tscn`, `<project>/t3_maps.json` |
| edited | `<project>/<id>/<id>.edits.json` (actors changed = keys of `actors`) |
| repacked | `<T3SDK>/build/assets/patched/<id>.gmp`; "repack needed" when the edits are newer |
| installed | a backup exists in `<T3SDK>/build/assets/backup/` and the game's map differs from it |

## Building

Needs Node 20+ and Rust (stable). On Windows, WebView2 (part of Windows 10
and 11); on Linux, WebKitGTK 4.1 (`libwebkit2gtk-4.1-dev` and Tauri's other
[prerequisites](https://tauri.app/start/prerequisites/)).

```sh
cd launcher
npm install
npm run tauri dev        # the app, with live reload
npm run tauri build      # release build and NSIS installer in src-tauri/target/release/bundle/
```

`npm run dev` serves the UI alone in a browser. Outside Tauri, `src/lib/mock.ts`
answers the commands with made-up data, so the UI can be worked on and
screenshotted without the game (`?page=maps` opens a page, `?setup` the setup
screen).

Checks:

```sh
npm run check                                    # svelte-check (TypeScript)
cd src-tauri && cargo test && cargo clippy && cargo fmt --check
cargo check --target x86_64-pc-windows-msvc      # the Windows-only code, from Linux
```

## Adding a tool to the launcher

1. Add a variant to `TaskSpec` in `src-tauri/src/tasks.rs` and its command line
   in `plan()`. The UI can only start what is listed there.
2. Add the same variant to `TaskSpec` in `src/lib/api.ts` (and a title in
   `mock.ts`).
3. Call `enqueue({ kind: ... }, "Title")` from a page.

Tools get the game folder and Godot through `T3_GAME_DIR` and `GODOT`, so they
need no extra flags.
