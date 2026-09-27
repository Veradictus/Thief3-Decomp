// Small, self-contained fixes gated by T3SDK.ini's [Fixes] section. Currently
// just skipping the intro movies; see fixes.hpp for the option and Install().
#include "fixes.hpp"

#include "log.hpp"

#include <MinHook.h>

#include <cstdint>

namespace t3sdk::fixes {
namespace {

// Plays [PCStartup] ShortIntroMovies (Eidos, Ion Storm, copyright, nVidia and
// EAX logos) before the main menu. It does nothing else, so returning early is
// the same as ShowIntroMovies=False.
constexpr uintptr_t kPlayIntroMovies = 0x10A50C30;

using PlayIntroMoviesFn = void(__cdecl*)();
PlayIntroMoviesFn g_playIntroMovies = nullptr;

void __cdecl PlayIntroMoviesDetour() { T3_LOG("intro movies skipped"); }

bool Hook(uintptr_t target, void* detour, void** original, const char* what) {
    MH_STATUS status = MH_CreateHook(reinterpret_cast<void*>(target), detour, original);
    if (status == MH_OK) {
        status = MH_EnableHook(reinterpret_cast<void*>(target));
    }
    if (status != MH_OK) {
        T3_LOG("%s: hook failed (%s)", what, MH_StatusToString(status));
    }
    return status == MH_OK;
}

}  // namespace

void Install(const Options& options) {
    if (options.skipIntros) {
        Hook(kPlayIntroMovies, reinterpret_cast<void*>(&PlayIntroMoviesDetour),
             reinterpret_cast<void**>(&g_playIntroMovies), "skip intros");
    }
    T3_LOG("fixes: skip intros %s", options.skipIntros ? "on" : "off");
}

}  // namespace t3sdk::fixes
