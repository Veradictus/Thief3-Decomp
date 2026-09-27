// See engine.hpp for what this module is for.
#include "engine.hpp"
#include "executable_hash.hpp"

#include "log.hpp"

#include <MinHook.h>
#include <windows.h>

#include <cstdio>
#include <vector>
#include <unordered_set>

namespace t3sdk::engine {

using t3::UObject;

namespace {

// ---- state --------------------------------------------------------------------

Layout g_layout;
bool g_ready = false;
bool g_exiting = false;
bool g_sawRunning = false;
bool g_loggedFailure = false;
DWORD g_lastAttempt = 0;
LogSink g_sink = nullptr;
void* g_serializeTarget = nullptr;

// ---- build and executable identity ---------------------------------------------

bool SupportedExecutableHash() {
    std::vector<wchar_t> path(512);
    DWORD pathLength = 0;
    for (;;) {
        pathLength = GetModuleFileNameW(nullptr, path.data(), DWORD(path.size()));
        if (!pathLength) {
            T3_LOG("cannot verify T3Main.exe SHA-1: GetModuleFileNameW failed (error %lu)", GetLastError());
            return false;
        }
        if (pathLength < path.size() - 1) {
            break;
        }
        if (path.size() >= 32768) {
            T3_LOG("cannot verify T3Main.exe SHA-1: executable path is too long");
            return false;
        }
        path.resize(path.size() * 2);
    }

    HashCheck check = CheckSupportedExecutableHash(path.data());
    if (check.failure == HashFailure::OpenFile) {
        T3_LOG("cannot verify T3Main.exe SHA-1: opening executable failed (error %lu)", check.win32Error);
    } else if (check.failure == HashFailure::ReadFile) {
        T3_LOG("cannot verify T3Main.exe SHA-1: reading executable failed (error %lu)", check.win32Error);
    } else if (check.failure == HashFailure::Crypto) {
        T3_LOG("cannot verify T3Main.exe SHA-1: Windows CNG failed (status 0x%08lX)", check.cryptoStatus);
    } else if (!check.matches) {
        T3_LOG("unsupported T3Main.exe SHA-1; SDK disabled");
    }
    return check.failure == HashFailure::None && check.matches;
}

// ---- engine log hook ------------------------------------------------------------

// FOutputDeviceFile::Serialize(const char* text, EName event), the log file
// device GLog points at. __fastcall with a dummy EDX stands in for __thiscall.
using SerializeFn = void(__fastcall*)(void* self, void* edx, const char* text, uint32_t event);
SerializeFn g_serialize = nullptr;
bool g_checkedGLog = false;
thread_local bool t_inSerialize = false;

void* GLog() { return *reinterpret_cast<void**>(t3::addr::GLog); }

void __fastcall SerializeDetour(void* self, void* edx, const char* text, uint32_t event) {
    // Serialize re-enters itself in some error paths; report each line once.
    if (g_sink && text && !t_inSerialize) {
        t_inSerialize = true;
        g_sink(text, event);
        t_inSerialize = false;
    }
    g_serialize(self, edx, text, event);
}

// Once GLog exists, confirm the hooked function really is its Serialize.
void CheckGLog() {
    void* glog = GLog();
    if (!glog || !*reinterpret_cast<void***>(glog)) {
        return;
    }
    g_checkedGLog = true;
    void* serialize = (*reinterpret_cast<void***>(glog))[0];
    if (serialize != reinterpret_cast<void*>(t3::addr::FOutputDeviceFileSerialize)) {
        T3_LOG("warning: GLog %p serializes through %p, not the hooked %p; engine log capture is incomplete", glog,
               serialize, reinterpret_cast<void*>(t3::addr::FOutputDeviceFileSerialize));
    }
}

// ---- name and object helpers ----------------------------------------------------

bool NamesReady() {
    return *reinterpret_cast<int*>(t3::addr::FNameInitialized) != 0 && t3::FNameNames().Num > 0;
}

// Base text of a name (without its number), or nullptr for an invalid name.
const char* NameText(uint32_t value) {
    auto& names = t3::FNameNames();
    uint32_t index = value & 0xFFFF;
    if (index >= uint32_t(names.Num)) {
        return nullptr;
    }
    t3::FNameEntry* entry = names.Data[index];
    return entry ? entry->Name : nullptr;
}

bool NameIs(const UObject* object, const char* text) {
    const char* name = NameText(object->Name.Value);
    return name && object->Name.Number() == 0 && strcmp(name, text) == 0;
}

UObject* Field(const UObject* object, uint32_t offset) {
    return *reinterpret_cast<UObject* const*>(reinterpret_cast<const uint8_t*>(object) + offset);
}

UObject* ClassOf(const UObject* object) { return reinterpret_cast<UObject*>(object->Class); }

// ---- object layout validation ----------------------------------------------------

// Checks the UObject layout against known objects and finds the offsets that
// stock Unreal Engine 2 layouts do not pin down for this fork.
bool TryValidateLayout(const char** why) {
    auto& objects = t3::GObjObjects();
    if (!NamesReady() || objects.Num <= 0) {
        *why = "object system not initialised";
        return false;
    }

    std::unordered_set<const UObject*> live;
    live.reserve(size_t(objects.Num) * 2);
    UObject* classClass = nullptr;
    for (UObject* object : objects) {
        if (!object) {
            continue;
        }
        live.insert(object);
        if (ClassOf(object) == object && NameIs(object, "Class")) {
            classClass = object;
        }
    }
    if (!classClass) {
        *why = "no object named Class that is its own class";
        return false;
    }
    auto isClass = [&](const UObject* object) { return object && ClassOf(object) == classClass; };
    auto findClass = [&](const char* name) -> UObject* {
        for (UObject* object : objects) {
            if (isClass(object) && NameIs(object, name)) {
                return object;
            }
        }
        return nullptr;
    };
    UObject* objectClass = findClass("Object");
    UObject* packageClass = findClass("Package");
    if (!objectClass || !packageClass) {
        *why = "classes Object/Package not found";
        return false;
    }

    // Outer: the field of class Object that holds package Core.
    uint32_t outer = 0;
    for (uint32_t offset = 0x0C; offset < 0x20 && !outer; offset += 4) {
        UObject* candidate = Field(objectClass, offset);
        if (live.count(candidate) && ClassOf(candidate) == packageClass && NameIs(candidate, "Core")) {
            outer = offset;
        }
    }
    if (!outer) {
        *why = "no UObject field of class Object points at package Core";
        return false;
    }

    // SuperField: the field that chains (nearly) every class up to Object.
    int classes = 0;
    for (UObject* object : objects) {
        classes += isClass(object);
    }
    uint32_t bestOffset = 0;
    int bestHits = 0;
    for (uint32_t offset = 0x28; offset < 0x80; offset += 4) {
        int hits = 0;
        for (UObject* object : objects) {
            if (!isClass(object)) {
                continue;
            }
            const UObject* cls = object;
            for (int depth = 0; depth < 64; ++depth) {
                if (cls == objectClass) {
                    ++hits;
                    break;
                }
                UObject* super = Field(cls, offset);
                if (!live.count(super) || !isClass(super)) {
                    break;
                }
                cls = super;
            }
        }
        if (hits > bestHits) {
            bestHits = hits;
            bestOffset = offset;
        }
    }
    if (bestHits * 100 < classes * 95) {
        *why = "no class field chains the classes up to Object";
        return false;
    }

    g_layout.outer = outer;
    g_layout.superField = bestOffset;
    T3_LOG("object layout validated: %d objects, %d classes, Outer at 0x%X, SuperField at 0x%X (%d/%d classes reach Object)",
           objects.Num, classes, outer, bestOffset, bestHits, classes);
    return true;
}

// Recursive helper for PathName(): writes outermost object first, then '.',
// down to `object` itself; capped in case an Outer chain is ever cyclic.
void AppendPath(UObject* object, std::string& out, int depth) {
    UObject* outer = Outer(object);
    if (outer && depth < 32) {
        AppendPath(outer, out, depth + 1);
        out += '.';
    }
    out += ObjectName(object);
}

}  // namespace

// ---- public API (engine.hpp) -----------------------------------------------------

Build CheckBuild() {
    auto base = reinterpret_cast<BYTE*>(GetModuleHandleW(nullptr));
    auto nt = reinterpret_cast<IMAGE_NT_HEADERS*>(base + reinterpret_cast<IMAGE_DOS_HEADER*>(base)->e_lfanew);
    Build build{nt->FileHeader.TimeDateStamp, nt->OptionalHeader.SizeOfImage, false};
    build.supported = build.timestamp == kSupportedTimestamp && build.imageSize == kSupportedImageSize &&
                      reinterpret_cast<uintptr_t>(base) == 0x10900000;
    if (build.supported) {
        build.supported = SupportedExecutableHash();
    }
    return build;
}

const Layout& GetLayout() { return g_layout; }

bool Exiting() {
    if (!g_exiting) {
        auto flag = [](uintptr_t address) { return *reinterpret_cast<const int*>(address) != 0; };
        bool running = flag(t3::addr::GIsRunning);
        g_sawRunning |= running;
        if (flag(t3::addr::GIsRequestingExit) || flag(t3::addr::GIsCriticalError) || (g_sawRunning && !running)) {
            g_exiting = true;
            T3_LOG("engine shutting down (requesting exit %d, critical error %d, running %d); engine access closed",
                   flag(t3::addr::GIsRequestingExit), flag(t3::addr::GIsCriticalError), running);
        }
    }
    return g_exiting;
}

bool Ready() { return g_ready && !Exiting(); }

void SetLogSink(LogSink sink) { g_sink = sink; }

bool HookEngineLog() {
    auto target = reinterpret_cast<void*>(t3::addr::FOutputDeviceFileSerialize);
    MH_STATUS status = MH_CreateHook(target, reinterpret_cast<void*>(&SerializeDetour),
                                     reinterpret_cast<void**>(&g_serialize));
    if (status == MH_OK) {
        status = MH_EnableHook(target);
    }
    if (status != MH_OK) {
        T3_LOG("engine log hook failed: %s", MH_StatusToString(status));
        return false;
    }
    g_serializeTarget = target;
    return true;
}

void OnFrame() {
    if (g_serializeTarget && !g_checkedGLog) {
        CheckGLog();
    }
    if (g_ready) {
        return;
    }
    DWORD now = GetTickCount();
    if (now - g_lastAttempt < 1000) {
        return;
    }
    g_lastAttempt = now;
    const char* why = "";
    g_ready = TryValidateLayout(&why);
    if (!g_ready && !g_loggedFailure && NamesReady() && t3::GObjObjects().Num > 0) {
        g_loggedFailure = true;
        T3_LOG("object layout not validated yet (%s); retrying every second", why);
    }
}

int ObjectCount() { return Ready() ? t3::GObjObjects().Num : 0; }

UObject* ObjectAt(int index) {
    auto& objects = t3::GObjObjects();
    return Ready() && index >= 0 && index < objects.Num ? objects.Data[index] : nullptr;
}

UObject* Outer(UObject* object) { return object && g_layout.outer ? Field(object, g_layout.outer) : nullptr; }

bool IsA(UObject* object, UObject* cls) {
    if (!Ready() || !object || !cls) {
        return false;
    }
    UObject* current = ClassOf(object);
    for (int depth = 0; current && depth < 64; ++depth) {
        if (current == cls) {
            return true;
        }
        current = Field(current, g_layout.superField);
    }
    return false;
}

UObject* FindObject(const char* className, const char* pathName) {
    if (!Ready() || !pathName) {
        return nullptr;
    }
    for (UObject* object : t3::GObjObjects()) {
        if (!object || (className && ObjectName(ClassOf(object)) != className)) {
            continue;
        }
        if (PathName(object) == pathName) {
            return object;
        }
    }
    return nullptr;
}

std::string NameToString(uint32_t name) {
    const char* text = NameText(name);
    if (!text) {
        return "<invalid name>";
    }
    std::string out = text;
    if (uint16_t number = uint16_t(name >> 16)) {
        out += "__" + std::to_string(number - 1);
    }
    return out;
}

std::string ObjectName(UObject* object) { return object ? NameToString(object->Name.Value) : "None"; }

std::string PathName(UObject* object) {
    std::string out;
    if (object) {
        AppendPath(object, out, 0);
    }
    return out;
}

int DumpObjects(const std::filesystem::path& file) {
    if (!Ready()) {
        return 0;
    }
    FILE* f = _wfopen(file.c_str(), L"w");
    if (!f) {
        return 0;
    }
    int count = 0;
    auto& objects = t3::GObjObjects();
    for (int i = 0; i < objects.Num; ++i) {
        if (UObject* object = objects.Data[i]) {
            fprintf(f, "%6d %-32s %s\n", i, ObjectName(ClassOf(object)).c_str(), PathName(object).c_str());
            ++count;
        }
    }
    fclose(f);
    return count;
}

}  // namespace t3sdk::engine
