# FAQ

Short answers to the questions players ask most, with links to the longer
explanation.

### Which releases does T3SDK work with?

Only the Steam release of Thief: Deadly Shadows, patch 1.1 (`T3Main.exe`
SHA-1 `40bf68a54246bcde2fb5fcbc75b94dc7c7f78305`). T3SDK checks this file at
start-up; on any other build — a different store, an unpatched copy, or a
Steam copy changed by another tool — it logs that and leaves the game to run
exactly as it would without T3SDK. See
[Unsupported builds](troubleshooting.md#unsupported-builds).

### Is it safe to use?

T3SDK changes the running game only in memory. Installing and removing it
only adds or deletes its own files in the game's `System` folder
(`dinput8.dll`, `T3SDK.ini`, `mods\`), and it refuses to overwrite a file it
doesn't already own (see [Playing with T3SDK](playing.md#install-and-remove)).
It doesn't touch Steam's DRM or the game's copy protection: the launcher's
**Play** button starts the game through Steam, exactly as Steam's own Play
button does. The one thing to be careful about is mods themselves: a mod's
DLL is a program that runs with your own rights, so only install mods you
trust (see the warning on [Installing mods](mods.md)).
[Back up your saves](saves.md) before trying any mod, in any case.

### Does it change game files?

No, not the game's own code or data. Playing with plain T3SDK only ever adds
its own files (above); installing an edited map, or a content mod, backs up
the original file first and puts it back when you remove the map or turn the
mod off (see [Installing mods](mods.md#removing-mods)).

### How do I remove it?

Click **Remove** in the T3SDK box on the launcher's **Play** page, or delete
the files you copied in if you installed by hand
(see [Playing with T3SDK](playing.md#install-and-remove)). To take
everything back to how it was — mods, edited maps and T3SDK itself — follow
[Removing everything](troubleshooting.md#removing-everything) in that
order.

### Is there multiplayer?

Not yet. Multiplayer is the whole reason this project exists, but nothing
playable is available today. Unreal's own network layer is gone from
`T3Main.exe` entirely — no `NetDriver`, `ActorChannel` or travel strings, and
no Winsock imports — so multiplayer has to be built from scratch as a mod,
and that work hasn't started; only the groundwork (stable hooking and
lifecycle) is done. See the
[roadmap towards multiplayer](../handoff.md#roadmap-towards-multiplayer) for
what's needed and in what order.

### Why does the game restart, or flash to the desktop, between levels?

The restart itself is the original game's own behaviour, not something
T3SDK adds: Thief: Deadly Shadows relaunches its whole process for New Game
and for every mission change, always has. T3SDK's loading-screen curtain
hides the gap by keeping the outgoing loading screen up until the new one is
ready, but that fix is new and hasn't been tried in the actual game yet, so
you may still see a black flash instead. See
[Display and performance](troubleshooting.md#display-and-performance).

### Will it make the game run better?

T3SDK doesn't optimise the game's renderer or engine; what it changes is
presentation — a borderless window, a paced frame rate in that window
(VSynch, `MaxFPS`), and smoother world updates above 100 fps
(`SmoothFrames`). None of that is a performance fix by itself, and the last
two haven't been tried in the actual game yet. On one test machine the main
menu ran between 200 and about 1,255 fps uncapped, and about 180 fps in the
game's first level. If that's more heat and fan noise than you want, turn on
the game's own VSynch, which paces it to your monitor; with VSynch off,
`MaxFPS` caps it instead. See [Settings explained](settings.md#display).

### Why isn't the launcher code-signed?

Windows checks installers for an Authenticode signature, and getting one
costs money or an application process that this project hasn't gone through
yet (see [Releasing: Windows code signing](../releasing.md#windows-code-signing)
for the two options being considered). Until then, Windows shows "unknown
publisher" for the installer: click **More info**, then **Run anyway**. This
is separate from the launcher's automatic updates, which already check a
different, unrelated key before installing anything — that part is already
verified.

### Where are the logs and saves?

Logs: `System\T3SDK.log` in the game folder. The launcher's **Play** page
shows the end of it, **Open** opens the whole file, and **Collect logs**
packages it for a bug report (see [Troubleshooting](troubleshooting.md)).
Saves: the game's own `SaveGames` folder, wherever your installation keeps
it — the launcher's **Saves** page shows where it found yours, and
**Settings** can override the location. See [Save backups](saves.md).

### How do I get help?

The [Taffer Tavern on Discord](https://discord.gg/eaJkC5C6WJ) for questions,
or **Report a problem** (Play page or Settings) for the project's GitHub
issue tracker if you've found a bug. Run **Collect logs** first and attach
the zip either way.

### How can I support the developers?

By buying the game: T3SDK works with your own copy and contains none of the
game itself. See the README's
[Buy the damn game](../../README.md#buy-the-damn-game) section.
