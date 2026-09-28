# Troubleshooting

## T3SDK.log

T3SDK writes a log to `System\T3SDK.log` in the game folder, and adds to it
on every run. The launcher's **Play** page shows its end; **Open** opens the
whole file. Set `Console=1` in `T3SDK.ini` to watch it live in a console
window while the game runs.

The log records:

- the T3SDK version, and whether your `T3Main.exe` is supported;
- which of its hooks are in place (`hooks: frame ok, exit ok, ...`);
- each mod: loaded, or why not;
- `engine ready` once the engine is up, and the game's own log lines
  (`EngineLog=1`);
- a mod callback that crashed, and that it was switched off;
- crash reports: where a fault happened (for example `T3Main.exe+0x8A466`),
  the processor's registers and the code addresses on the stack.

Lines you may see:

| Line | What it means |
|---|---|
| `unsupported T3Main.exe ...; SDK disabled, game runs unmodded` | Your game build is not the supported one. See [Unsupported builds](#unsupported-builds). |
| `mod <name>: LoadLibrary failed (error 193)` | The mod is a 64-bit DLL. The game is 32-bit, so mods must be too. |
| `mod <name>: LoadLibrary failed (error 126)` | A DLL the mod needs is missing, for example a Visual C++ runtime DLL. |
| `mod <name>: no T3Mod_Init export; unloading` | The DLL is not a T3SDK mod, or does not export `T3Mod_Init` under its plain name. |
| `mod <name>: T3Mod_Init returned <n>; unloading` | The mod decided not to load. It may have logged why just before. |
| `mod <name>: frame callback raised exception ...; callback disabled` | The mod crashed. The game goes on without that part of the mod. Tell the mod's author. |
| `first-chance fault 0xC0000005 at T3Main.exe+0x8A466 ...` as the game closes | The game's own crash on exit. It happens without T3SDK too. |

A crash report is written when the fault happens, before the game decides
what to do with it. The game can survive some of them.

## Collect logs and report a problem

The launcher's **Collect logs** makes one zip file with the logs and
settings that someone needs to help you. Your user name and the paths on your
PC are replaced in it. Look through it anyway before you post it.

**Report a problem** takes you to the project's issue tracker on GitHub. Say
what you did, what you expected and what happened instead, and attach the
zip. For questions, the [Taffer Tavern on Discord](https://discord.gg/hdAXH73tEG)
is quicker.

Without the launcher, attach `System\T3SDK.log`, and `T3SDK.ini` if you
changed it. Read the log first: it contains the game's path, which can
include your Windows user name.

## Unsupported builds

T3SDK hooks one build only: the Steam release's `T3Main.exe` (patch 1.1,
SHA-1 `40bf68a54246bcde2fb5fcbc75b94dc7c7f78305`). Every other build is
detected at start-up: T3SDK logs it, changes nothing, and the game runs as
if T3SDK were not there. The launcher's **Play** page shows whether your
build is supported.

If you used a tool that patches `T3Main.exe` itself, such as a field-of-view
patch, the file no longer matches. Steam's **Verify integrity of game files**
(the game's **Properties > Installed Files**) puts the original back.

## Something looks wrong

- **A fix causes trouble.** Turn the fixes off one at a time on the **SDK
  settings** page and start the game each time, to find the one. Then report
  it.
- **A mod does not load.** Check that it is on, look for its name in
  `T3SDK.log`, and check the **Mods** page for warnings about requirements.
- **The game keeps running after alt-tab.** That is the borderless window.
  Pause before you switch away.

## Removing everything

In this order, so that every original comes back:

1. On the **Mods** page, turn every mod off (or switch to a profile with none
   on), then uninstall them. The game's original files come back.
2. In **Map Studio**, click **Restore original** for every map you
   installed.
3. On the **Play** page, click **Remove**. T3SDK's files leave the `System`
   folder. Delete `System\mods` if anything is left in it.
4. Uninstall the launcher from Windows' **Settings > Apps** (or delete the
   portable folder). Its settings are in `%APPDATA%\org.t3sdk.launcher` and
   its working files (map exports, backups of original maps) in
   `%LOCALAPPDATA%\org.t3sdk.launcher`. Check them for save backups you want
   to keep, then delete them.

Steam's **Verify integrity of game files** puts back any game file that
differs from Steam's copy. It does not delete files that were added, such
as `System\dinput8.dll`, so use **Remove** first.
