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
| Setup | First run: finds the game (installer registry entry, Steam libraries, `T3_GAME_DIR`), Godot (`GODOT`, `PATH`, common folders), Python (the bundled one, the T3SDK `.venv`, the `py` launcher, `PATH`) and the T3SDK folder (the bundled one, or a checkout found by walking up from the launcher). Each path is checked: the game's `T3Main.exe` SHA-1, `godot --version` (4.7+), Python 3.10+, the tools. |
| Play | Starts the game (through Steam for a Steam install, as the Play button does), shows whether the build is supported, installs or removes T3SDK (`sdk.py deploy`/`undeploy`), builds it from a checkout (`sdk.py build`, needs Visual Studio), and shows the end of `T3SDK.log`. |
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
| repacked | `<build>/assets/patched/<id>.gmp`; "repack needed" when the edits are newer |
| installed | a backup exists in `<build>/assets/backup/` and the game's map differs from it |

`<build>` is the T3SDK folder's `build/`, or the per-user folder for the
bundled tools (see Releases).

## Releases

`.github/workflows/launcher.yml` checks and builds the launcher and the SDK on
every change; a `v*` tag runs `release.yml`, which publishes the files as a
GitHub release (both call `launcher-build.yml`):

| File | What it is |
|---|---|
| `T3SDK-Launcher_<version>_x64-setup.exe` | NSIS installer (per user, no admin rights) |
| `T3SDK-Launcher_<version>_portable.zip` | the same files, to unzip and run |
| `T3SDK_<version>_x86.zip` | the SDK alone (`dinput8.dll`, mods, `T3SDK.ini`), for `System/` by hand |

A release launcher is self-contained. `tools/stage_launcher.py stage` puts
three things next to it (its resource folder), and setup picks them first:

- `t3sdk/`: `tools/sdk.py`, `tools/assets/`, `sdk/T3SDK.ini` and the prebuilt
  SDK in `build/sdk/bin/`, laid out like a checkout;
- `python/`: CPython's embeddable package for Windows (pinned by SHA-256), so
  players need no Python of their own.

The bundled folder is replaced on update and may not be writable, so for it
the launcher sets `T3SDK_BUILD_DIR` to `build\` in the per-user local app data
(`%LOCALAPPDATA%\org.t3sdk.launcher\`). The tools write there instead of into
`build/`: the SDK's deploy manifest, the Godot project, patched maps and the
backups of original maps. With a checkout as the T3SDK folder, everything stays
in the checkout's `build/`.

## Building

Needs Node 20+ (its Corepack supplies the Yarn version pinned in
`package.json`) and Rust (stable). On Windows, Rust's MSVC toolchain with
Visual Studio's C++ build tools (see [Windows toolchain](#windows-toolchain))
and WebView2 (part of Windows 10 and 11); on Linux, WebKitGTK 4.1
(`libwebkit2gtk-4.1-dev` and Tauri's other
[prerequisites](https://tauri.app/start/prerequisites/)).

```sh
corepack enable          # once: makes `yarn` the pinned Yarn 4
cd launcher
yarn install
yarn tauri dev           # the app, with live reload
yarn tauri build         # release build and NSIS installer in src-tauri/target/release/bundle/
```

A release-style build with the bundled tools, SDK and Python (the SDK built
first with `tools/sdk.py build`):

```sh
python tools/stage_launcher.py stage [--version 0.2.0]
cd launcher && yarn tauri build --config src-tauri/bundle/tauri.bundle.conf.json
python tools/stage_launcher.py portable launcher/src-tauri/target/release/t3sdk-launcher.exe dist/portable.zip
```

`yarn dev` serves the UI alone in a browser. Outside Tauri, `src/lib/mock.ts`
answers the commands with made-up data, so the UI can be worked on, tested and
screenshotted without the game (`?page=maps` opens a page, `?setup` the setup
screen).

### Windows toolchain

On Windows the launcher builds with Rust's MSVC toolchain
(`x86_64-pc-windows-msvc`): the default of rustup's installer, the one Tauri
recommends and the one CI uses. With a GNU toolchain (`x86_64-pc-windows-gnu`)
the `windows` crates fail with `error calling dlltool 'dlltool.exe': program
not found`, as they need MinGW's `dlltool.exe` on `PATH` and neither Git for
Windows nor rustup puts one there. `rustc -vV` shows the active toolchain
(`host:`).

`yarn tauri` (`launcher/scripts/tauri.js`) takes care of this. On Windows, when
rustup's toolchain for `src-tauri/` is a GNU one and no `dlltool.exe` is on
`PATH`, it prints a note and runs the Tauri CLI with the MSVC toolchain of the
same channel, through `RUSTUP_TOOLCHAIN` (rustup installs it on first use). A
`RUSTUP_TOOLCHAIN` that is already set is left alone. A `rust-toolchain.toml`
cannot do this, since its toolchain would apply to Linux and macOS too.

Plain `cargo` commands in `src-tauri/` and rust-analyzer do not go through
`yarn tauri`. For those, choose MSVC once:

```sh
rustup toolchain install stable-msvc
rustup override set stable-msvc     # in launcher/: for the launcher only
rustup default stable-msvc          # or: for every project
```

Set the override in `launcher/`, not `src-tauri/`: the Tauri CLI runs its own
`rustc -vV` from `launcher/` to learn the target, and cargo runs in
`src-tauri/`, so both folders need the same toolchain.

### The UI stack

| Tool | What for |
|---|---|
| Yarn 4 (Corepack, `nodeLinker: node-modules`) | packages; `yarn.lock` is committed, CI installs with `--immutable` |
| TypeScript 6, strict (`noUncheckedIndexedAccess`, unused checks) | `yarn typecheck` runs svelte-check over `.ts` and `.svelte` |
| ESLint 10 flat config: typescript-eslint strict + stylistic (type-checked), eslint-plugin-svelte | `yarn lint` |
| Prettier 3 with the Svelte plugin, 120 columns | `yarn format`, `yarn format:check` |
| Vitest | `yarn test`: display helpers (`src/lib/format.ts`) and the job queue, run against the mock with fake timers |
| Vite 8 + Svelte 5 (runes) | `yarn dev`, `yarn build`; imports use the `$lib/` and `$components/` aliases |

`yarn verify` runs typecheck, lint, format check and tests, as CI does.

Checks:

```sh
yarn verify                                      # the UI: types, lint, format, tests
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
