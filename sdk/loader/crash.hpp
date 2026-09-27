#pragma once

#include <windows.h>

namespace t3sdk::crash {

// Logs the first few faults (access violations, illegal instructions, ...) with
// location, registers and stack, then lets the game handle them as usual.
// `self` is the SDK DLL, so its addresses can be told apart from the game's.
void Install(HMODULE self);

}  // namespace t3sdk::crash
