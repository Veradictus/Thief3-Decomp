# Runtime: the game loop, the clock, and exit

How the game spends a frame, what happens when it loses focus, why it
restarts for every level, and how it ends. Everything here is drawn from
[engine.md](../engine.md) and [handoff.md](../handoff.md); this page
explains it in order rather than by address.

## The main loop

Once start-up is done, `MainLoop` runs once per frame:

1. `TimeManager::BeginFrame` — records the frame's start time.
2. `GEngine->Tick(delta)` — the engine and game world advance by this
   frame's game-time delta (the clock, below, decides what that delta is).
3. `PumpMessages` — handles the waiting Windows messages (`PeekMessageA`).
4. `TimeManager::EndFrame` — advances the clock's own game time.

While the game is inactive (window in the background), the loop then waits
in `PumpMessages` again, this time in `GetMessageA`, which blocks until a
message arrives, so an inactive game does not spin the CPU.

## The clock

A single `TimeManager` (`TimeManager::Instance`) is the source of every
frame's game-time delta, and it does not simply pass through real elapsed
time. It clamps very long frames to a **maximum step** of 0.1 s (so a stall
does not cause a huge jump in game time), and — the more visible behaviour —
it will not advance game time at all for a frame shorter than a **minimum
step** of 0.01 s; the leftover real time is carried over to the next frame
instead.

That 10 ms minimum caps the world at 100 updates a second. Above 100 frames
per second, some frames render without moving the world at all, and the
next one gets the accumulated time in one lump: the world (and the camera
moving through it) moves on every second or third frame, in uneven jumps
rather than smoothly, however high the frame rate is. T3SDK's `SmoothFrames` setting
(on by default) lowers the minimum step to 0.001 s, so every frame moves the
world a little; see [sdk.md](../sdk.md).

The clock also exposes a time scale, and a pause flag that `SetPaused`
toggles; the console command `SIMTIME` can adjust the clock directly (see
[console.md](console.md)).

## Focus loss and pausing

When the game's window receives `WM_ACTIVATEAPP(FALSE)` (another program
takes the foreground), the window procedure releases the mouse and
DirectInput, saves whether the clock was already paused, pauses it, and
clears a global "app active" flag — which makes the main loop wait in
`GetMessageA` above until the flag is set again. It also normally resets
the Direct3D device to its original creation parameters.

That last part matters for how a windowed game differs from an exclusive
fullscreen one: an exclusive fullscreen device is *already* lost by the
time this handler runs (losing focus takes the screen away from it), so the
reset is a no-op there and vanilla never needed to think about it. A
windowed device is not lost, so the reset actually runs — and normally
fails outright while the device is still in use, after which the code that
waits for the device to come back (`UD3DRenderDevice::Lock`) sleeps in 10 ms
steps forever: the game freezes. T3SDK's borderless mode (see
[display.md](display.md)) skips exactly this one reset call, and restores
the "app active" flag and the saved pause state itself, so a borderless
game keeps running in the background instead of freezing or (by default)
pausing; `[Display] PauseInBackground` restores the vanilla pause-on-focus-
loss behaviour for players who want it.

## Level changes restart the process

Every level change — New Game, entering a mission, leaving a mission — is a
full process restart, not an in-place level load. Concretely, from an
outgoing game:

1. `appRequestExit(Force=1)` runs `RelaunchForLevelChange`.
2. It shows three black frames, then begins drawing the *next* level's
   loading screen (`LoadingScreen::Begin`, see [display.md](display.md))
   for three more frames.
3. It starts `Ion Launcher.exe` (next to the game executable) with the
   command line `T3MAIN.exe <display-or-window> "dummy" <URL> <arguments>`,
   waits for that launcher's window and a signal event, hands it a
   duplicated handle to itself, and ends.

The launcher (which keeps its own log, `Launcher.log`, in the current
user's `Documents\Thief - Deadly Shadows\` folder; see
[files.md](files.md)) waits about a second for the outgoing game to end,
restores the display mode, waits another second, then starts a new
`T3Main.exe -display \\.\DISPLAYn WxH <URL>` and waits for it to signal that
it has reached exclusive mode.

The URL carries where to go next; for New Game, for example, it is
`Inn?-LoadTravel?-LoadSave?-ObjectFilter=0?DestTeleporter="Inn"`. The new
process reads `DestTeleporter` from it and starts the player at the
matching `PlayerStart` (see [levels.md](levels.md)).

T3SDK's own contribution here is cosmetic, not structural. In a borderless
window the restart would leave the desktop showing for seconds (exclusive
fullscreen kept the screen black meanwhile), so T3SDK covers the gap with a
curtain window that holds the loading screen the outgoing game left on the
monitor, until the incoming game has drawn its own and takes the
foreground. This has not been tried in the game yet. See [sdk.md](../sdk.md)
and [display.md](display.md).

## Exit

`appRequestExit(Force)` is how the game asks to end. With `Force` false, it simply posts `WM_QUIT` and sets a global
"requesting exit" flag, for the main loop to notice and stop on its own.
With `Force` true — as at every level change, above — it instead calls
`ForceExit`: releases input, runs the same `RelaunchForLevelChange` used for
level changes (which, with no next level queued, just restores the display
mode instead of starting a new process), shuts the renderer down, and calls
`TerminateProcess` on itself directly.

Closing the window ends the main loop, and the game then crashes during
shutdown, with or without T3SDK installed: the process exits with code
`0xC0000005` (access violation), and T3SDK's crash reporter (see
[sdk.md](../sdk.md)) places the fault at `0x1098A466`, reading address zero.
This has not been analysed further; it is a pre-existing bug in the
retail game, not something T3SDK introduces.
