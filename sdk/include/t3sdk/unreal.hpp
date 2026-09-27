// Engine types of T3Main.exe (Ion Storm's Unreal Engine 2 fork), as laid out in
// memory. Offsets marked "verified" are checked by the SDK at startup; see
// docs/engine.md for the evidence behind each address and field.
#pragma once

#include <cstddef>
#include <cstdint>

namespace t3 {

// Engine dynamic array: { Data, Num, Max }, same as stock Unreal Engine 2.
template <class T>
struct TArray {
    T* Data;
    int32_t Num;
    int32_t Max;

    T& operator[](int32_t i) const { return Data[i]; }
    T* begin() const { return Data; }
    T* end() const { return Data + Num; }
};
static_assert(sizeof(TArray<int>) == 12);

// FName: low 16 bits index FName::Names, high 16 bits are an instance number.
// A non-zero number N displays as "<name>__<N-1>" (Ion Storm change; stock
// Unreal Engine 2 names are a plain index).
struct FName {
    uint32_t Value;

    uint16_t Index() const { return uint16_t(Value & 0xFFFF); }
    uint16_t Number() const { return uint16_t(Value >> 16); }
};
static_assert(sizeof(FName) == 4);

struct FNameEntry {
    int32_t Index;
    FNameEntry* HashNext;
    uint32_t Flags;            // 0x1000: log output with this category is suppressed
    uint16_t MaxNumber;
    uint16_t Pad;
    TArray<uint32_t> NumberFlags;
    char Name[64];             // verified: ANSI text at +0x1C
};
static_assert(offsetof(FNameEntry, Name) == 0x1C);

struct UClass;

// Base of every engine object. Index/Name/Class verified; Outer is detected at
// startup (stock Unreal Engine 2 puts it at 0x18).
struct UObject {
    void** VTable;          // 0x00
    int32_t Index;          // 0x04 verified: slot in GObjObjects
    UObject* HashNext;      // 0x08 verified: GObjHash bucket chain
    void* StateFrame;       // 0x0C
    void* Linker;           // 0x10
    int32_t LinkerIndex;    // 0x14
    UObject* Outer;         // 0x18
    uint32_t ObjectFlags;   // 0x1C
    FName Name;             // 0x20 verified
    UClass* Class;          // 0x24 verified
};
static_assert(offsetof(UObject, Name) == 0x20 && offsetof(UObject, Class) == 0x24);

// Addresses in T3Main.exe (fixed: the exe has no relocations, so it always
// loads at 0x10900000). Only valid for the supported build.
namespace addr {
inline constexpr uintptr_t GObjObjects = 0x10F3E4A0;       // TArray<UObject*> UObject::GObjObjects
inline constexpr uintptr_t GObjAvailable = 0x10F3E4AC;     // TArray<int32_t>  free GObjObjects slots
inline constexpr uintptr_t GObjHash = 0x10F3A418;          // UObject* [4096], bucket = Name.Index() & 0xFFF
inline constexpr uintptr_t FNameNames = 0x10F7AF1C;        // TArray<FNameEntry*> FName::Names
inline constexpr uintptr_t FNameInitialized = 0x10F7AF18;  // BOOL
inline constexpr uintptr_t FNameHash = 0x10F76F18;         // FNameEntry* [4096]
inline constexpr uintptr_t GIsCriticalError = 0x10F46D70;  // UBOOL, set by the error handler
inline constexpr uintptr_t GIsRunning = 0x10F46D7C;        // UBOOL, main loop condition
inline constexpr uintptr_t GIsRequestingExit = 0x10F46D84; // UBOOL, appRequestExit / WM_QUIT
inline constexpr uintptr_t GLog = 0x10F01158;              // FOutputDevice*, points at the log file device
inline constexpr uintptr_t FOutputDeviceLogf = 0x10AF5230; // void __cdecl Logf(FOutputDevice*, EName, const char*, ...)
inline constexpr uintptr_t FOutputDeviceFileSerialize = 0x10901780;  // __thiscall (const char*, EName), GLog's vtable[0]
}  // namespace addr

inline TArray<UObject*>& GObjObjects() { return *reinterpret_cast<TArray<UObject*>*>(addr::GObjObjects); }
inline TArray<FNameEntry*>& FNameNames() { return *reinterpret_cast<TArray<FNameEntry*>*>(addr::FNameNames); }

}  // namespace t3
