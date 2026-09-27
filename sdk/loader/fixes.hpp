#pragma once

// Options for fixes.cpp's small built-in gameplay/start-up fixes.
namespace t3sdk::fixes {

struct Options {
    bool skipIntros = false;
};

// Installs the game fixes the options enable. Call once at start-up, after
// MinHook is initialised.
void Install(const Options& options);

}  // namespace t3sdk::fixes
