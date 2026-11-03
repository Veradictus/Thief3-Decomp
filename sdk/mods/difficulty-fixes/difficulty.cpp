// Fixes for two difficulty bugs of the original game:
//
// - Missions play at Normal whatever was chosen. The AI's difficulty
//   multipliers ([Difficulty] Difficulty_AIVisual_Mult_<level> and the rest,
//   picked by the gamesys values dif_AISenses and dif_AICombat) are loaded by
//   0x10AB70B0, which nothing calls when a mission loads, so the AI keeps
//   the multipliers it started with. The mod calls it once the map is in
//   (a code hook in UGameEngine::Virtual32, the level load). The AI's
//   hitpoints are scaled once (0x10AB7530) just before the game loads the
//   multipliers itself, so by the ones loaded before; the mod loads them
//   first there too.
// - The Enter Mission and Restart Mission menus offer their default
//   difficulty (Easy on a restart) instead of the one being played. After
//   the game opens either menu, the mod writes the current difficulty
//   (dif_currdifficulty) into the mission record the menu edits.
//
// Settings, in difficulty-fixes.ini next to the DLL:
//   [Difficulty]
//   ApplyOnMissionLoad=1   load the difficulty multipliers when a mission loads
//                          (default 1)
//   KeepInMissionMenus=1   preselect the current difficulty in the mission menus
//                          (default 1)
#include <t3sdk/modkit.hpp>
#include <t3sdk/t3sdk.h>

#include <windows.h>

#include <cstdint>
#include <string>

namespace {

// ---- game addresses ---------------------------------------------------------------

// In UGameEngine::Virtual32 (the level load), after the map is in: `mov al, [0x10F45C0C]`
// (docs/engine.md, "Difficulty").
constexpr uintptr_t kAfterLevelLoad = 0x10985ADC;

// void LoadDifficultyMultipliers() (called with an unused `this`): loads the
// [Difficulty] multipliers for the levels dif_AISenses and dif_AICombat select.
constexpr uintptr_t kLoadDifficultyMultipliers = 0x10AB70B0;

// void ScaleAIHitPoints(), __thiscall on the difficulty event handler: multiplies every AI pawn's hitpoints
// (property 0x80332) by the loaded AIHitPoints multiplier, once (a flag in the difficulty object stops it after).
// The game calls it (0x10AB8470, on event 0x5A) just before it loads the multipliers, so it scales by the ones
// loaded before: the last mission's, or Normal's.
constexpr uintptr_t kScaleAIHitPoints = 0x10AB7530;

// Stats* __cdecl GetStats(); slot 0 of the result's vtable is int Get(FName).
constexpr uintptr_t kGetStats = 0x10A18230;

// FName::FName(const char*, EFindName), __thiscall (docs/engine.md, "Names (FName)").
constexpr uintptr_t kFNameConstruct = 0x10AF9E20;

// bool WindowManager::OpenEnterMissionWindow(bool), __thiscall.
constexpr uintptr_t kOpenEnterMissionWindow = 0x10B15B20;

// bool WindowManager::OpenRestartMissionWindow(), __thiscall.
constexpr uintptr_t kOpenRestartMissionWindow = 0x10B15BF0;

// Pointer to the mission flow object; at kMissionRecords is the table of the
// mission records the menus edit.
constexpr uintptr_t kMissionFlow = 0x10F3A3D8;

// bool __cdecl (mission): true when gamesys 0x800864 is 1, i.e. the mission
// has no difficulty choice.
constexpr uintptr_t kFixedDifficulty = 0x10ABE130;

// ---- game layout --------------------------------------------------------------------

// In the mission flow object: the table of mission records.
constexpr uint32_t kMissionRecords = 0x150;

// In the table: the (mission, record) pair for the Enter Mission menu...
constexpr uint32_t kEnterMission = 0x04;
constexpr uint32_t kEnterRecord = 0x08;

// ...and for the Restart Mission menu.
constexpr uint32_t kRestartMission = 0x0C;
constexpr uint32_t kRestartRecord = 0x10;

// In a mission record: the difficulty the menu shows.
constexpr uint32_t kDifficultyField = 0x174;

// dif_currdifficulty: 0 Easy .. 3 Expert, 4 custom (a custom difficulty is left alone).
constexpr int kCustomDifficulty = 4;

// EFindName value that adds the name when it is new.
constexpr int kFNameAdd = 1;

// The difficulty object (a pointer at kDifficulty): the AIHitPoints multiplier, and the flag set once the AI's
// hitpoints have been scaled.
constexpr uintptr_t kDifficulty = 0x10FF667C;
constexpr uint32_t kHitPointsMultiplier = 0xA4;
constexpr uint32_t kHitPointsScaled = 0xB0;

using OpenEnterFn = bool(__fastcall*)(void* self, void* edx, bool arg);
using OpenRestartFn = bool(__fastcall*)(void* self, void* edx);
using ScaleFn = void(__fastcall*)(void* self, void* edx);

// ---- state ----------------------------------------------------------------------------

// The SDK's function table, kept from T3Mod_Init.
const T3SdkApi* g_api = nullptr;

// The game's menu openers, called through by the detours.
OpenEnterFn g_openEnter = nullptr;
OpenRestartFn g_openRestart = nullptr;
ScaleFn g_scaleAIHitPoints = nullptr;

// ---- the difficulty --------------------------------------------------------------------

void LoadMultipliers() {
    reinterpret_cast<void(__fastcall*)(void*, void*)>(kLoadDifficultyMultipliers)(nullptr, nullptr);
}

// The difficulty being played (dif_currdifficulty: 0 Easy .. 3 Expert, 4
// custom), or -1 when the game has no stats object yet.
int CurrentDifficulty() {
    void* stats = reinterpret_cast<void*(__cdecl*)()>(kGetStats)();

    // The game has no stats object: there is no difficulty to report.
    if (!stats) {
        return -1;
    }

    uint32_t name = 0;
    reinterpret_cast<void*(__fastcall*)(uint32_t*, void*, const char*, int)>(kFNameConstruct)(
        &name, nullptr, "dif_currdifficulty", kFNameAdd);

    auto get = (*reinterpret_cast<int(__fastcall***)(void*, void*, uint32_t)>(stats))[0];
    return get(stats, nullptr, name);
}

// Code hook after the map is loaded: loads the AI's difficulty multipliers,
// which the game forgets to do.
void T3SDK_CALL AfterLevelLoad(void*, T3Registers*) {
    LoadMultipliers();
    g_api->Log("level loaded: difficulty multipliers loaded for difficulty %d", CurrentDifficulty());
}

// Detour of ScaleAIHitPoints: loads the current multipliers first, so the AI's hitpoints are scaled by this
// difficulty's. The game's own flag still keeps it to one scaling.
void __fastcall ScaleAIHitPointsDetour(void* self, void* edx) {
    auto difficulty = *reinterpret_cast<uint8_t**>(kDifficulty);

    // Only a scaling that will run: once done, the game's flag makes the call do nothing.
    if (difficulty && !t3mod::Field<uint8_t>(difficulty, kHitPointsScaled)) {
        LoadMultipliers();
        g_api->Log("AI hitpoints scaled by %.2f (difficulty %d)", t3mod::Field<float>(difficulty, kHitPointsMultiplier),
                   CurrentDifficulty());
    }

    g_scaleAIHitPoints(self, edx);
}

// ---- the mission menus -----------------------------------------------------------------

// Writes the current difficulty into the mission record the menu edits:
// (mission, record) at +4/+8 of the record table for Enter Mission, at
// +0xC/+0x10 for Restart Mission. Does nothing for a custom difficulty, when
// the game's state is not there yet, or for a mission with a fixed difficulty.
void PreselectDifficulty(bool restart) {
    int difficulty = CurrentDifficulty();
    auto flow = *reinterpret_cast<uint8_t**>(kMissionFlow);

    // Do nothing for a custom difficulty (it has no menu entry) or before the mission flow object exists.
    if (difficulty < 0 || difficulty >= kCustomDifficulty || !flow) {
        return;
    }

    auto records = t3mod::Field<uint8_t*>(flow, kMissionRecords);

    // The mission flow has no record table yet: nothing to write into.
    if (!records) {
        return;
    }

    void* mission = t3mod::Field<void*>(records, restart ? kRestartMission : kEnterMission);
    auto record = t3mod::Field<uint8_t*>(records, restart ? kRestartRecord : kEnterRecord);

    // Leave the menu alone when it has no mission or record, or when the mission has a fixed difficulty (no choice).
    if (!mission || !record || reinterpret_cast<bool(__cdecl*)(void*)>(kFixedDifficulty)(mission)) {
        return;
    }

    t3mod::Field<int>(record, kDifficultyField) = difficulty;
    g_api->Log("%s menu: difficulty %d preselected", restart ? "restart mission" : "enter mission", difficulty);
}

// Detour of OpenEnterMissionWindow: preselects the difficulty once the menu is open.
bool __fastcall OpenEnterDetour(void* self, void* edx, bool arg) {
    bool opened = g_openEnter(self, edx, arg);

    // Only preselect when the game really opened the menu.
    if (opened) {
        PreselectDifficulty(false);
    }

    return opened;
}

// Detour of OpenRestartMissionWindow: preselects the difficulty once the menu is open.
bool __fastcall OpenRestartDetour(void* self, void* edx) {
    bool opened = g_openRestart(self, edx);

    // Only preselect when the game really opened the menu.
    if (opened) {
        PreselectDifficulty(true);
    }

    return opened;
}

}  // namespace

// Called by the SDK when the mod is loaded. Returns non-zero (the mod stays
// off) when the SDK has no code hooks; a fix whose hook fails is left off and
// the other still works.
T3SDK_EXPORT int T3SDK_CALL T3Mod_Init(const T3SdkApi* api) {
    // Code hooks need API version 2; an older SDK cannot place this mod's code hook, so the mod stays off.
    if (api->version < 2 || api->size < offsetof(T3SdkApi, AddCodeHook) + sizeof(api->AddCodeHook)) {
        return 1;
    }

    g_api = api;

    std::wstring ini = t3mod::SettingsFile();
    bool onLoad = t3mod::ReadBool(ini, L"Difficulty", L"ApplyOnMissionLoad", true);
    bool menus = t3mod::ReadBool(ini, L"Difficulty", L"KeepInMissionMenus", true);

    // Hook the level load only when the setting asks for it; a failed hook turns this fix off.
    if (onLoad) {
        onLoad = t3mod::CodeHook(api, kAfterLevelLoad, AfterLevelLoad, nullptr, "level load");
    }

    // The AI's hitpoints are part of the same fix; without this hook the multipliers still load.
    if (onLoad) {
        t3mod::Hook(api, kScaleAIHitPoints, reinterpret_cast<void*>(&ScaleAIHitPointsDetour),
                    reinterpret_cast<void**>(&g_scaleAIHitPoints), "AI hitpoint scaling");
    }

    // Hook both menus only when the setting asks for it; if either hook fails the menu fix is reported as off.
    if (menus) {
        menus = t3mod::Hook(api, kOpenEnterMissionWindow, reinterpret_cast<void*>(&OpenEnterDetour),
                            reinterpret_cast<void**>(&g_openEnter), "enter mission menu") &&
                t3mod::Hook(api, kOpenRestartMissionWindow, reinterpret_cast<void*>(&OpenRestartDetour),
                            reinterpret_cast<void**>(&g_openRestart), "restart mission menu");
    }

    api->Log("multipliers on mission load %s, mission menus %s", onLoad ? "on" : "off", menus ? "on" : "off");
    return 0;
}
