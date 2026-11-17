#pragma once

// The game's brightness in a window (gamma.cpp): the game sets its brightness,
// contrast and gamma as a Direct3D gamma ramp, which only exclusive fullscreen
// shows. In a window the SDK draws the frame through the same ramp itself.
// display.cpp calls these from its Direct3D 8 hooks, on the game's render
// thread.
namespace t3sdk::display::gamma {

// Turns the pass on or off ([Display] WindowedBrightness). Call once at start-up.
void Configure(bool enabled);

// Whether the pass is on: display.cpp then hooks Present for it.
bool Enabled();

// A device was created (or reset): hooks its SetGammaRamp once and notes whether it runs in a window, which is
// when the pass draws.
void Attach(void* device, bool windowed);

// Before the device is reset: releases what a reset requires to be gone (the frame copy, the state block).
void BeforeReset();

// Before each Present: draws the frame through the game's ramp when the device is windowed and the ramp is not
// the identity.
void BeforePresent(void* device);

}  // namespace t3sdk::display::gamma
