#pragma once

#include <windows.h>

// The level-change curtain. T3 restarts for every level change: the outgoing
// game draws the next level's loading screen and ends, and about five seconds
// later (while the game's launcher starts it again) the incoming game draws
// the same loading screen. Exclusive fullscreen showed a black screen in
// between; a borderless game would show the desktop. So the outgoing game
// covers its monitor with a copy of the loading screen, shown by a small
// helper process (rundll32 on this DLL's T3SDK_Curtain export), and the
// incoming game lifts it once its own loading screen is up; the helper then
// hands it the foreground.
namespace t3sdk::curtain {

// Copies what `monitor` shows (the loading screen the game just presented)
// and starts the helper that covers the monitor with it. Call from the game
// while it still has the foreground, so the helper may take it over.
void Raise(const RECT& monitor);

// Lifts a raised curtain, if there is one, and has the helper give `game` the
// foreground. Call once the game has presented its loading screen.
void Lift(HWND game);

}  // namespace t3sdk::curtain
