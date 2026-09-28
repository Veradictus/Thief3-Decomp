# Display: resolutions, the window, and the UI

How the game presents itself: display modes, fullscreen versus a window,
the cursor, the loading screen, and the two layout systems behind the menus
and the HUD. See [config.md](config.md) for the INI keys involved and
[sdk.md](../sdk.md) for how T3SDK's own display fixes are configured.

## The resolution table

The Options screen's `Resolution` entry (see [config.md](config.md))
indexes a fixed table of five width/height pairs, stock: 640x480, 800x600,
1024x768, 1280x1024 and 1600x1200. `Options::ApplyVideo` clamps the chosen
index to 0–4 and steps down to a mode the adapter actually supports.
T3SDK's `NativeResolutions` setting replaces this table with the monitor's
own modes at start-up, with the monitor's native mode as the last, highest
entry.

## Exclusive fullscreen versus a borderless window

The game creates one Direct3D 8 device and normally runs it in **exclusive
fullscreen**: the device owns the display mode outright, and losing focus
(alt-tab, a click on another monitor) takes the screen away from it: the
device is lost, and the game's own `WM_ACTIVATEAPP` handling (see
[runtime.md](runtime.md)) finds it lost and leaves the reset for when the
game is back in front.

T3SDK's `Borderless` setting instead creates the device **windowed**,
sized to the game's resolution, and turns the game's window into a popup
covering its monitor — visually indistinguishable from fullscreen, but a
real window: alt-tab, clicking another monitor and taking screenshots all
work normally. Because a windowed device is never automatically lost on
focus loss, the device-reset call the game makes there would otherwise run
for real and fail (the device is still in use), which without T3SDK's fix
freezes the game (see [runtime.md](runtime.md) for why). A window also has
to be brought to the front: exclusive fullscreen took the screen when the
device was created, a window does not, and Windows keeps a program started
in the background (by Steam, or by the game's launcher at a level change)
behind the window in front. T3SDK brings the game window to the front when
it is created, in every new game process (see [runtime.md](runtime.md)).

## VSync

The game's own `VSynch` option (on by default) makes an exclusive
fullscreen device present once per monitor refresh. A windowed Direct3D 8
device cannot request that directly; T3SDK's borderless window instead
selects the `COPY_VSYNC` swap effect when `VSynch` is on and no
multisampling is requested, and plain, uncapped `DISCARD` otherwise (not yet
tried in the game). Since a
window's presentation is not paced by the display hardware the way
exclusive fullscreen's is, T3SDK also offers a `MaxFPS` cap (a
high-resolution waitable timer, then a short spin to the exact frame
boundary) and a `FrameStats` log of frames per second and time spent in
`Present`.

## The hardware cursor

In the menus, the game does not use a normal Windows cursor: every frame it
sets a 32x32 `A8R8G8B8` image as the Direct3D device's own hardware cursor
(hot spot at 0,0) and shows it through both the device and `user32`'s own
cursor calls. A 32-pixel cursor was sized for the screens of 2004; on a
large modern display it is tiny, and — because Direct3D 8 emulates a
hardware cursor in a windowed device by rebuilding a Windows cursor on
every one of those per-frame calls — it also flickers. T3SDK's borderless
mode takes over the cursor entirely: it builds one Windows cursor from the
game's own cursor image, scaled to the screen (`CursorScale`, or
automatically from the screen height), rebuilt only when the image actually
changes, and shows or hides it exactly when the game asks the device to.

## The loading screen

`LoadingScreen::Begin` draws the loading screen for a given map: a
background texture (`<[Paths] DynamicTextures>\<map>.dds`, or `Loading1.dds`
when the map has none), plus the logo and caption art and positions from
`[LoadingScreen]` (see [config.md](config.md)). It runs both for an
ordinary level load and — drawing the *next* level's background — during
the level-change restart described in [runtime.md](runtime.md), which is
also where T3SDK hooks it, to know when it is safe to lift its own curtain.

## The UI window system

Menus, popups and the HUD's frame are native window objects
(`WindowManager`, `Window`), laid out from `System/T3UI.ini` (plus
`T3UILights.ini` and `T3ItemGrid.ini`); each INI section's `Type=` key names
the window class it configures. The whole menu system is designed for a
fixed **640x480** virtual screen (`[WindowManager] AssumedUIScreenWidth`/
`Height`), viewed through a 95 degree field-of-view UI camera, and every
traced PC menu positions its children from its parent's top-left corner.

A `Window` has a position (`Pos_X`/`Y`/`Z`), a parent, an active/visible
state, and flags including `ListenForMouseClicks` and — significant for
widescreen, below — `IsModal`. Its placement anchor
(`CENTER`, `TOP`, `BOTTOM`, `LEFT`, `RIGHT`, or absolute) and its own size
(with the special width `FULLSCREEN`, meaning "the whole layout") together
decide where `PlacedPosition` puts it relative to its parent: for example a
`LEFT`-anchored window sits at `Pos_X` from its parent's left edge, a
`RIGHT`-anchored one at `Pos_X` in from the right, and a `CENTER`-anchored
one splits the remaining space evenly. A window flagged `IsModal` is a
self-contained screen (a menu, a popup, a briefing) rather than part of a
larger layout.

**Widescreen.** Answering a wider-than-640 value for
`AssumedUIScreenWidth` keeps the whole layout's proportions on a wide
screen, but everything that was positioned *from an edge* at the original
640-wide design (left-anchored and absolutely-positioned windows, and
full-width windows offset from the left, such as the main menu's button
column) would then drift away from the screen's centre, while
right-anchored content would hug the far edge instead of framing the
centred content as designed. T3SDK's `WidescreenUI` setting fixes this by
re-centring the children of a menu's full-width frame (a full-width window
inside a modal window: every menu, popup and briefing screen) so they land
where they would in a centred, 640-wide frame. Left-anchored and absolute
windows move right by the margin, right-anchored ones move left, and centred
ones stay. Windows flush against the screen's edge (`Pos_X` 0, like the main
menu's version line) stay at the edge, and the Inputs page's key table has
its width ratios scaled back to 640. The frames and backgrounds themselves,
and the in-game HUD (not modal, and anchored to the screen's own edges), are
left alone. `UILayoutTrace` logs every window's placement once, for anyone
extending this.

## The HUD

The in-game HUD (`T3Hud.ini`) is a separate layout system from the window
manager above: HUD elements are positioned in **normalised** screen
coordinates (`screenx`, `screeny`, both -1 to 1 across the screen), not in
the 640x480 window layout. This is why widescreen re-centring does not
touch the HUD — it was never laid out in that coordinate space to begin
with, and its edge anchors already track the real screen size.
