#pragma once

// Interface to mods.cpp: mod DLL loading/unloading and address-to-mod lookup.
// See sdk.cpp for how LoadAll's `api` and `onUnload` are wired up.

#include <t3sdk/t3sdk.h>

#include <windows.h>

#include <filesystem>

namespace t3sdk::mods {

// Loads every *.dll in `dir` and calls its T3Mod_Init. A mod whose init fails
// is unloaded; `onUnload` is told first so its callbacks can be dropped.
void LoadAll(const std::filesystem::path& dir, const T3SdkApi* api, void (*onUnload)(HMODULE mod));

// Calls T3Mod_Shutdown of every loaded mod, newest first.
void ShutdownAll();

// The loaded mod whose image contains `address` (its module handle and file
// name without extension), or nullptr. Uses the SDK's own table rather than
// loader APIs, so it is safe while the process is exiting.
HMODULE ModuleAt(const void* address);
const char* NameAt(const void* address);

}  // namespace t3sdk::mods
