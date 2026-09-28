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
zip. For questions, the [Taffer Tavern on Discord](https://discord.gg/eaJkC5C6WJ)
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

## Display and performance

Specific symptoms from T3SDK's display fixes: what causes each one, and the
setting that changes it. [Settings explained](settings.md#display) has every
`[Display]` key in `T3SDK.ini`.

- **The game looks choppy even at a high frame rate.** The engine's own clock
  only moves the game world once 10 ms have passed, so above 100 fps the
  world and the camera move on only every second or third frame, however
  fast the game renders.
  `SmoothFrames=1` (the default) lowers that to 1 ms, so the world moves
  every frame. Not yet tried in the actual game: watch fast-moving things
  (physics, jumping, mantling, rope arrows) above 100 fps, and turn it off
  if something looks wrong.
- **Tearing, or a frame rate that feels unpaced.** Turn on the game's own
  VSynch (Options > Audio/Video): in the borderless window, T3SDK now makes
  it present once per monitor refresh, the way exclusive fullscreen always
  did. This doesn't apply together with MultiSampling; with both on, expect
  an unpaced rate instead. `MaxFPS` caps the rate independently of
  VSynch. Neither has been tried in the actual game yet.
- **The menu cursor is tiny, or flickers.** That's how the game's own
  hardware cursor behaves in a window. T3SDK's borderless window replaces it
  with one Windows cursor scaled to your screen, on by default; this has
  been confirmed fixed by testing. `CursorScale` sets a fixed size instead of
  the automatic one, if you want it bigger or smaller.
- **The game pauses when you click another window.** With
  `PauseInBackground=0` (the default), a borderless game keeps running in
  the background instead; pause yourself before you alt-tab away if you
  don't want it to. Set it to `1` to bring back the game's own
  pause-on-focus-loss behaviour.
- **The desktop, or a black screen, appears between levels.** The game
  restarts its whole process for every level change; that gap is normal,
  with or without T3SDK. The loading-screen curtain keeps the outgoing
  loading screen up until the new one is ready, but it's one of the newest
  fixes and hasn't been tried in the actual game yet, so you may still see a
  brief black screen instead of the loading image.
- **The Inputs page's key table runs past its frame, or the main menu's
  version line sits away from the bottom-left corner.** Both were bugs in
  `WidescreenUI` on wide screens, fixed in the current T3SDK: update it.
  With `WidescreenUI` off, the menus are the game's own 4:3 layout,
  stretched to fill the screen.
- **The picture looks blurry on a monitor scaled above 100%.** The game isn't aware of Windows' display
  scaling, so Windows stretches the borderless window itself, which blurs
  it. This is a known limitation with no fix yet; see
  [Handoff: next steps](../handoff.md#next-steps).

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
