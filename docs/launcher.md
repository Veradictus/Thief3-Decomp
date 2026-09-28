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
| Play | Starts the game (through Steam for a Steam install, as the Play button does), shows whether the build is supported, installs or removes T3SDK (`sdk.py deploy`/`undeploy`), builds it from a checkout (`sdk.py build`, needs Visual Studio), and shows the end of `T3SDK.log` with **Collect logs** and **Report a problem** next to it. The Game box says when the saves were last backed up. |
| Map Studio | Per map: export to Godot (then a headless Godot import), open it in the Godot editor or the viewer, repack the saved edits into a patched `.gmp`, install it into the game, restore the original. Also a byte-exact round-trip check of the unchanged map. |
| Mods | The mod manager ([below](#mods)): installed `.t3mod` packages in load order (drag or arrows to reorder), switches, what each one holds (code, content, textures), the checks' issues with their fixes, remove, profiles, and loose DLLs. **Install mod…** or dropping `.t3mod` files onto the window installs them; the Browse tab reads the mod index, with search, tags, compatibility and updates. |
| Saves | The game's saves folder (how many saves, their size, the newest), **Back up now** with an optional label, and the backups: restore (after a confirmation, and not while the game runs), delete, open the folder. A switch backs the saves up whenever the launcher starts the game. See Saves below. |
| SDK settings | `System/T3SDK.ini` as switches. The list, order and descriptions come from the comments in the SDK's own `sdk/T3SDK.ini`, so new settings appear without launcher changes. Values are edited in place; the file's comments and line endings are kept. |
| Tasks | The job queue. Jobs run one at a time, in order; a job that depends on another (the import after an export) is skipped when that one fails. Output streams live and can be copied; a running job can be cancelled (its whole process tree on Windows). |
| Settings | The paths again, plus the Godot project folder (default `build/assets/godot` in the T3SDK folder), the saves folder (default: found automatically) and the mod index URL (default `https://veradictus.github.io/Thief3-Decomp/modindex/index.json`). **Updates**: the launcher's version, **Check now**, the start-up check switch, and a found update with its notes. **Collect logs** and **Report a problem**. |

The launcher's own settings are `launcher.json` in the per-user config folder
(`%APPDATA%\org.t3sdk.launcher\` on Windows); save backups go to `saves\` in
the per-user local data folder (`%LOCALAPPDATA%\org.t3sdk.launcher\saves\`).
Nothing is written to the repository, and the game folder is written only by
the SDK install, the Mods page (`System/mods/`, and content mods' files, whose
originals it keeps in `System/mods/originals/`), `T3SDK.ini` edits, map installs
and texture packs (which back up the original first; see
[assets.md](assets.md)). The saves folder is written only when a backup is
restored.

## Mods

The Mods page implements the package format of [mods.md](mods.md) in
`src-tauri/src/mods.rs` (with `mods/`: manifest, version ranges, packages,
state, overlay, checks, index) and `src/pages/Mods.svelte` (with
`pages/mods/`, `lib/mods.svelte.ts` and the pure helpers in
`lib/modlist.ts`).

- **Changes apply at once.** There is no Apply button: switching a mod,
  reordering, installing, removing and switching profiles each save
  `state.json` and sync straight away (`load-order.txt`, the `files/`
  overlay), and the command returns the new list. Code mods take effect the
  next time the game starts. **Apply again** re-runs the sync, for files
  changed by hand.
- **Installs** check every entry path and the manifest before anything is
  written, extract into a hidden folder in `System/mods/` and rename it into
  place; an upgrade or downgrade replaces the folder and keeps the mod's
  position and switch. **Remove** switches the mod off, syncs its content
  away, then deletes the folder.
- **Checks** run on every listing and change; a mod with an error is left
  out of the sync until it is fixed. Fixes ("Enable X", "Move X before Y",
  "Disable X") are buttons on the issue.
- **Texture packs** run as tasks, since `t3texpack.py` rewrites whole
  bundles: after a change, when the enabled packs differ from the ones last
  applied (`state.json`'s `textures`), the page queues `texturePacks`
  (`t3texpack.py apply --pack System/mods/<id> ...`), replacing a queued one
  that has not started. A change that places or removes a game bundle
  (`.ibt`) through `files/` is split in two: the sync leaves those bundles
  and reports them, the page queues `textureRestore` (`t3texpack.py
  restore`), whose success runs the rest of the sync, and then
  `texturePacks` to patch the placed bundles again. The launcher records the
  applied set when `apply` succeeds. **Apply texture packs again** is there
  for bundles that changed behind the launcher's back (a Steam file check).
- **The index** is fetched once per session (and on **Refresh**) from the
  URL in Settings. Each version shows what it needs next to the installed
  mods and SDK before anything is downloaded; the updates count is the
  installed mods with a newer compatible release. A download goes to a
  hidden file in `System/mods/`, is checked against the index's size and
  SHA-256, and is installed only when its manifest has the index's id and
  version. HTTPS goes through `ureq` with native TLS (Windows' own, and its
  certificate store).

## Saves

The game reads its save folder from the `SaveGamePath` value of its registry
key (`HKLM\SOFTWARE\Ion Storm\Thief - Deadly Shadows`, under `WOW6432Node` on
64-bit Windows) and keeps the saves in `SaveGames` inside it: one folder per
save, plus `Current Save`, the game's copy of the save being played. The
original installer sets `SaveGamePath` to the installing user's
`My Documents\Thief - Deadly Shadows`. Where the saves really end up differs
by version and Windows version, according to players' reports:

| Version | Reported location of `SaveGames` |
|---|---|
| CD/DVD (2004), Windows XP | `My Documents\Thief - Deadly Shadows\` of the user who installed the game (the registry value) |
| Unpatched game on Vista and later | a path in a user's own Documents is diverted to Public Documents: `C:\Users\Public\Documents\Thief - Deadly Shadows\` (also reachable as `C:\ProgramData\Documents\…`, a compatibility link to it) |
| GOG | its `goglog.ini` names the user's Documents, but saves were found in Public Documents (Windows 10) |
| Steam | the user's `Documents\Thief - Deadly Shadows\`, or `save\` in the game folder (`…\steamapps\common\Thief Deadly Shadows\save\SaveGames`) |
| Sneaky Upgrade (unofficial patch) | uses `SaveGamePath` as it is (no diversion); prefers Public Documents when saves are already there. Thief 3 Gold keeps its own save folder |

Sources: the GOG forum
([one](https://www.gog.com/forum/thief_series/thief_3_deadly_shadows_save_file_location),
[two](https://www.gog.com/forum/thief_series/cant_find_save_file_for_thief_deadly_shadows)),
the [Steam forum](https://steamcommunity.com/app/6980/discussions/0/1458455461497313510/),
[SaveGame.Pro](https://savegame.pro/pc-thief-deadly-shadows-savegame/), and the
Sneaky Upgrade 1.1.12 notes on
[ModDB](https://www.moddb.com/mods/thief-3-sneaky-upgrade/news/sneaky-upgrade-1112-released)
and the [registry value](https://forums.whirlpool.net.au/archive/1013354) as
quoted by search results (both pages refuse automated readers, as does
[PCGamingWiki](https://www.pcgamingwiki.com/wiki/Thief:_Deadly_Shadows), whose
table is worth a look). None of this was checked on a real install yet.

So `src-tauri/src/saves.rs` looks at every candidate: `SaveGamePath\SaveGames`
from the registry, `Thief - Deadly Shadows\SaveGames` in the user's Documents
and in Public Documents (both through the Windows known-folder API), and
`save\SaveGames` in the game folder, each also in `%LOCALAPPDATA%\VirtualStore`
when it lies under Program Files or ProgramData (where Windows redirects an
old 32-bit program's writes). The existing folder with the newest file wins.
**Settings → Saves folder** overrides all of this.

A backup is a zip of the whole folder, named `<YYYY-MM-DD_HHMMSS>[ <label>].zip`
(a second one in the same second gets ` (2)`), written under a temporary name
first. Its `.t3sdk-backup.json` entry records the time, the label, the number
of saves, files and bytes, and the folder it came from. Files keep their
modification times.

Restoring refuses while `T3Main.exe` runs. It first backs up the current
saves ("before restore"; skipped when the newest backup already holds exactly
these saves), then unpacks the backup next to the folder
(`SaveGames.t3sdk-restore`), moves the current folder aside
(`SaveGames.t3sdk-old`), moves the new one in, and deletes the old one. If a
step fails, the current saves stay (or are moved back). Entries that would
land outside the folder are refused.

With **Back up the saves when the launcher starts the game** on, Play makes a
"before launch" backup first, unless the saves are unchanged since the newest
backup. The launcher keeps the ten newest automatic backups of each kind and
never deletes the ones made with **Back up now**.

## Updates

Release builds made with the updater key check
`https://github.com/Veradictus/Thief3-Decomp/releases/latest/download/latest.json`
at start-up, at most once a day (**Settings → Updates** has a switch and
**Check now**). A newer version shows "Update available" in the sidebar;
**Update and restart** downloads the installer, checks its signature, and
runs it without questions (a progress bar), after which the new launcher
starts. The portable zip does not update itself: it links to the releases
page. Builds without the key (development builds, forks) do not check at all.
How the key and the release files fit together: [releasing.md](releasing.md).

## Collect logs

**Collect logs** (Play page and Settings) asks where to save a zip for a bug
report and fills it with:

- `System/T3SDK*.log` (the last 4 MB of each), `System/T3SDK.ini`, and
  `System/mods/load-order.txt`, `state.json` and `overlay.json` when present;
- `listing.txt`: the names and sizes in `System/` and (two levels deep)
  `System/mods/`, with the SHA-256 of every DLL;
- `overview.json`: the game check (`T3Main.exe` SHA-1, supported or not,
  Steam), the SDK status, whether the game runs, the saves folder;
- `launcher.json` (the launcher's settings), `about.txt` (launcher and
  Windows version), the SDK's deploy manifest (`deployed.json`), and
  `tasks.txt`, the output of the last ten tasks.

Every file passes through a redaction first (`src-tauri/src/diag.rs`): the
user's home folder becomes `%USERPROFILE%` and the user name `<user>`,
ignoring case, with backslashes, forward slashes or JSON's doubled
backslashes. **Report a problem** opens the repository's bug report form.

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
| `latest.json`, the installer's `.sig` | for the launcher's updater, when the updater key is set up ([releasing.md](releasing.md)) |

A release launcher is self-contained. `tools/stage_launcher.py stage` puts
three things next to it (its resource folder), and setup picks them first:

- `t3sdk/`: `tools/sdk.py`, `tools/assets/`, `sdk/T3SDK.ini` and the prebuilt
  SDK in `build/sdk/bin/`, laid out like a checkout, with the repository's
  `LICENSE` and `THIRD_PARTY_NOTICES.md` when it has them;
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
python tools/stage_launcher.py stage [--version 0.2.0] [--updater-pubkey <public key>]
cd launcher && yarn tauri build --config src-tauri/bundle/tauri.bundle.conf.json
python tools/stage_launcher.py portable launcher/src-tauri/target/release/t3sdk-launcher.exe dist/portable.zip
```

`--updater-pubkey` builds the updater in; `tauri build` then needs the private
key in `TAURI_SIGNING_PRIVATE_KEY` ([releasing.md](releasing.md)).

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
| Vitest | `yarn test`: display helpers (`src/lib/format.ts`), the report's task log (`diag.ts`), the mod manager's logic (`src/lib/modlist.ts`), and the job queue, the update flow and the mod store, run against the mock with fake timers |
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
