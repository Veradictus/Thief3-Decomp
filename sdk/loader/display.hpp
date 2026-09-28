#pragma once

// Options for display.cpp's three independent display features: the monitor's
// own resolutions in the Options menu, a borderless window instead of
// exclusive fullscreen, and a UI layout scaled for the screen's aspect ratio.
namespace t3sdk::display {

struct Options {
    // Replace the game's five 4:3/5:4 resolutions with the monitor's own modes;
    // the highest entry becomes the native resolution.
    bool nativeResolutions = false;
    // Run in a borderless window covering the monitor instead of exclusive
    // fullscreen, so alt-tab, other monitors and screenshots work.
    bool borderless = false;
    // Lay the menus and HUD out for the monitor's aspect ratio instead of
    // stretching the game's 640x480 layout (the UI width becomes 480 x aspect).
    bool widescreenUI = false;
    // Log where each UI window is placed (first time only), to map out a
    // screen's window tree when modding the UI.
    bool uiLayoutTrace = false;
    // Pause the game while another window has the focus, as the game does on
    // its own. Off: a borderless game keeps running in the background.
    bool pauseInBackground = false;
    // Scale of the borderless window's menu cursor; 0 = follow the screen
    // height (1 at 768 lines).
    double cursorScale = 0;
    // Log frames per second and the time spent presenting, every 10 seconds.
    bool frameStats = false;
};

// Call once at start-up, before the game reads its options, after MinHook is
// initialised.
void Install(const Options& options);

}  // namespace t3sdk::display
