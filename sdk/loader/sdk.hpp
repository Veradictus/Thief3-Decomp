#pragma once

#include <windows.h>

#define T3SDK_VERSION "0.1.0"

namespace t3sdk {

// Runs on the game's main thread before T3Main.exe's own startup code, once the
// loader lock is released (see dllmain.cpp). Never throws.
void Initialize(HMODULE self);

}  // namespace t3sdk
