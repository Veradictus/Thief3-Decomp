#pragma once

#include <windows.h>

namespace t3sdk {

// Import Address Table patching: redirects one function a module imports by
// name to a replacement. Used for functions the game calls through its
// import table (PeekMessageA, ExitProcess, TerminateProcess, Direct3DCreate8);
// for functions inside T3Main.exe itself, or reached through a vtable, the
// mod API's inline hooks (MinHook) are used instead.
//
// Points `module`'s import of `dll`!`function` at `replacement`. Returns the
// previous pointer, or nullptr when the module does not import that function.
void* PatchImport(HMODULE module, const char* dll, const char* function, void* replacement);

}  // namespace t3sdk
