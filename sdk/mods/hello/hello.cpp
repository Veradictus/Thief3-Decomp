// Example mod. Shows the three things a mod does with the SDK:
//   - react to frames (on the game's main thread),
//   - read engine objects once the engine is up,
//   - listen to the engine's log.
// Every ten seconds it logs the number of live objects, the player controller,
// and how many engine log lines of each category it has seen.
#include <t3sdk/t3sdk.h>

#include <windows.h>

#include <cstring>
#include <map>
#include <mutex>
#include <string>

namespace {

const T3SdkApi* g_api = nullptr;
bool g_engineUp = false;
DWORD g_lastReport = 0;
T3Object* g_playerControllerClass = nullptr;
// Engine log callbacks run on whichever thread logged, frame callbacks on the
// main thread: the counts they share are locked.
std::map<std::string, int> g_logLines;
std::mutex g_logLinesMutex;

void T3SDK_CALL OnEngineLog(void*, const char*, const char* category) {
    std::lock_guard<std::mutex> lock(g_logLinesMutex);
    ++g_logLines[category];
}

T3Object* FindPlayerController() {
    if (!g_playerControllerClass) {
        return nullptr;
    }
    for (int i = 0, n = g_api->ObjectCount(); i < n; ++i) {
        T3Object* object = g_api->ObjectAt(i);
        char name[128];
        if (object && g_api->IsA(object, g_playerControllerClass) &&
            g_api->ObjectName(object, name, sizeof(name)) && strncmp(name, "Default", 7) != 0) {
            return object;
        }
    }
    return nullptr;
}

void T3SDK_CALL OnFrame(void*) {
    if (!g_api->EngineReady()) {
        return;
    }
    if (!g_engineUp) {
        g_engineUp = true;
        g_playerControllerClass = g_api->FindObject("Class", "Engine.PlayerController");
        g_api->Log("engine up: %d object slots; class Engine.PlayerController %s", g_api->ObjectCount(),
                   g_playerControllerClass ? "found" : "not found");
    }
    DWORD now = GetTickCount();
    if (now - g_lastReport < 10000) {
        return;
    }
    g_lastReport = now;

    int live = 0;
    for (int i = 0, n = g_api->ObjectCount(); i < n; ++i) {
        live += g_api->ObjectAt(i) != nullptr;
    }
    char controller[256] = "none";
    if (T3Object* pc = FindPlayerController()) {
        g_api->ObjectPathName(pc, controller, sizeof(controller));
    }
    std::string lines;
    {
        std::lock_guard<std::mutex> lock(g_logLinesMutex);
        for (const auto& [category, count] : g_logLines) {
            lines += category + "=" + std::to_string(count) + " ";
        }
    }
    g_api->Log("%d live objects; player controller %s; engine log lines: %s", live, controller, lines.c_str());
}

}  // namespace

T3SDK_EXPORT int T3SDK_CALL T3Mod_Init(const T3SdkApi* api) {
    if (api->version < T3SDK_API_VERSION) {
        return 1;
    }
    g_api = api;
    api->AddFrameCallback(OnFrame, nullptr);
    api->AddEngineLogCallback(OnEngineLog, nullptr);
    api->Log("hello: waiting for the engine");
    return 0;
}

T3SDK_EXPORT void T3SDK_CALL T3Mod_Shutdown(void) { g_api->Log("hello: shutting down"); }
