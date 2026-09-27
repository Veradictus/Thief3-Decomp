#pragma once

// Options for display.cpp's two independent display features: the monitor's
// own resolutions in the Options menu, and a borderless window instead of
// exclusive fullscreen.
namespace t3sdk::display {

struct Options {
    // Replace the game's five 4:3/5:4 resolutions with the monitor's own modes;
    // the highest entry becomes the native resolution.
    bool nativeResolutions = false;
    // Run in a borderless window covering the monitor instead of exclusive
    // fullscreen, so alt-tab, other monitors and screenshots work.
    bool borderless = false;
};

// Call once at start-up, before the game reads its options, after MinHook is
// initialised.
void Install(const Options& options);

}  // namespace t3sdk::display
