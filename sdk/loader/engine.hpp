#pragma once

// Engine object system access: build/executable identity, the runtime layout
// validation that locates UObject::Outer and UStruct::SuperField for this
// engine fork, the engine log hook, and the name/object lookups the mod API
// (sdk.cpp) exposes. See engine.cpp for the implementation and docs/engine.md
// for the addresses and evidence.

#include <t3sdk/unreal.hpp>

#include <cstdint>
#include <filesystem>
#include <string>

namespace t3sdk::engine {

// The one T3Main.exe build the SDK's addresses are for.
inline constexpr uint32_t kSupportedTimestamp = 0x40C8A4DA;  // 2004-06-10 18:13:46 UTC
inline constexpr uint32_t kSupportedImageSize = 0x718000;

struct Build {
    uint32_t timestamp;
    uint32_t imageSize;
    bool supported;
};
Build CheckBuild();

// Offsets found by ValidateLayout(). Zero until the layout is validated.
struct Layout {
    uint32_t outer = 0;       // UObject::Outer
    uint32_t superField = 0;  // UStruct::SuperField (walks a class up to Object)
};
const Layout& GetLayout();

// True once names and objects exist and the layout checks passed, until the
// engine starts shutting down.
bool Ready();

// True from the moment the game requests exit or hits a critical error; stays
// true. Engine objects may be freed at any point after this.
bool Exiting();

// Main thread, once per frame: validates the object layout once the object
// system is up, and checks the engine log hook against GLog.
void OnFrame();

// Receives every line the engine writes to its log file device (GLog).
// `event` is the log category as a name value.
using LogSink = void (*)(const char* text, uint32_t event);
void SetLogSink(LogSink sink);

// Hooks the log device at start-up, before the engine logs anything.
bool HookEngineLog();

int ObjectCount();
t3::UObject* ObjectAt(int index);
t3::UObject* FindObject(const char* className, const char* pathName);
bool IsA(t3::UObject* object, t3::UObject* cls);
t3::UObject* Outer(t3::UObject* object);

std::string NameToString(uint32_t name);
std::string ObjectName(t3::UObject* object);
std::string PathName(t3::UObject* object);  // "Engine.Actor"

// Writes "<index> <class> <path>" for every live object. Returns the count.
int DumpObjects(const std::filesystem::path& file);

}  // namespace t3sdk::engine
