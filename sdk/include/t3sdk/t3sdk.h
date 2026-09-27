/*
 * T3SDK mod API.
 *
 * A mod is a 32-bit DLL in the game's System/mods/ folder that exports
 *
 *     T3SDK_EXPORT int  T3SDK_CALL T3Mod_Init(const T3SdkApi* api);  // 0 = loaded
 *     T3SDK_EXPORT void T3SDK_CALL T3Mod_Shutdown(void);             // optional
 *
 * T3Mod_Init runs before the game's own startup code, so the engine does not
 * exist yet: register callbacks there and wait for api->EngineReady().
 *
 * The API is plain C so a mod can use any compiler. The table only grows: a
 * member added after version 1 is usable when api->size covers it.
 *
 * Threading: frame callbacks run on the game's main thread, once per pass of
 * its message loop, starting once EngineReady() first returns non-zero and
 * stopping once the game begins exiting. Engine log callbacks run on
 * whichever thread logged, from start-up onward (so possibly before
 * EngineReady()); protect any state shared with a frame callback.
 * Objects: T3Object* pointers, and the object functions below, are only good
 * while EngineReady() holds; the engine can free objects once the game starts
 * exiting, when EngineReady() goes back to 0.
 * Memory: strings come back through caller buffers; nothing allocated on one
 * side of the API is freed on the other.
 */
#ifndef T3SDK_T3SDK_H
#define T3SDK_T3SDK_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
#define T3SDK_EXTERN_C extern "C" /* so a C++ mod's exports keep their plain-C names */
#else
#define T3SDK_EXTERN_C
#endif
#define T3SDK_EXPORT T3SDK_EXTERN_C __declspec(dllexport) /* use on a mod's T3Mod_Init/T3Mod_Shutdown */
#define T3SDK_CALL __cdecl /* calling convention for every function in this header */

#define T3SDK_API_VERSION 1 /* current version; see T3SdkApi::version/size below */

/* Opaque handle to an engine UObject (see unreal.hpp for the real layout, C++
 * only): mods just carry pointers to it back into the calls below. */
#ifdef __cplusplus
namespace t3 {
struct UObject;
}
typedef t3::UObject T3Object;
#else
typedef struct T3Object T3Object;
#endif

typedef void(T3SDK_CALL* T3FrameCallback)(void* user);
/* `category` is the engine's log category, e.g. "Log", "Init", "Warning". */
typedef void(T3SDK_CALL* T3LogCallback)(void* user, const char* text, const char* category);

typedef struct T3SdkApi {
    uint32_t version; /* T3SDK_API_VERSION implemented by the SDK */
    uint32_t size;    /* sizeof(T3SdkApi) in the SDK */

    /* printf-style line in T3SDK.log, tagged with the calling mod's name. */
    void(T3SDK_CALL* Log)(const char* fmt, ...);

    /* Callbacks; each returns 0 on success, -1 if `callback` is NULL. See
     * Threading, above, for when each one runs. */
    int(T3SDK_CALL* AddFrameCallback)(T3FrameCallback callback, void* user);
    int(T3SDK_CALL* AddEngineLogCallback)(T3LogCallback callback, void* user);

    /* Inline function hooks (MinHook: one table shared by every mod, so two
     * mods cannot hook the same `target`). `target` is a code address in
     * T3Main.exe; `detour` replaces it; `original` (may be NULL) receives a
     * trampoline that calls the unhooked function. CreateHook leaves the hook
     * disabled; call EnableHook to activate it. Each returns 0 (MH_OK) on
     * success, another MH_STATUS otherwise (MinHook.h has the values, e.g.
     * MH_ERROR_ALREADY_CREATED for a `target` another mod already hooked). */
    int(T3SDK_CALL* CreateHook)(void* target, void* detour, void** original);
    int(T3SDK_CALL* EnableHook)(void* target);
    int(T3SDK_CALL* DisableHook)(void* target);
    int(T3SDK_CALL* RemoveHook)(void* target);

    /* Engine objects: usable once EngineReady() returns non-zero (see
     * Objects, above); ObjectCount/ObjectAt/FindObject return 0/NULL before
     * that. */
    int(T3SDK_CALL* EngineReady)(void);
    int(T3SDK_CALL* ObjectCount)(void); /* size of the object table, including free slots */
    T3Object*(T3SDK_CALL* ObjectAt)(int index); /* NULL for a free slot or an out-of-range index */
    /* Linear search by full path, e.g. FindObject("Class", "Engine.Actor").
     * className may be NULL to match any class. NULL if not found. */
    T3Object*(T3SDK_CALL* FindObject)(const char* className, const char* pathName);
    T3Object*(T3SDK_CALL* ObjectClass)(T3Object* object); /* NULL for a NULL object */
    T3Object*(T3SDK_CALL* ObjectOuter)(T3Object* object); /* the object's Outer, or NULL */
    int(T3SDK_CALL* IsA)(T3Object* object, T3Object* cls); /* 1 if object's class is cls or derives from it */
    /* Text into buf, NUL-terminated even when truncated; returns the full
     * untruncated length, like snprintf (buf may be NULL and size 0 to size a
     * buffer first). */
    size_t(T3SDK_CALL* ObjectName)(T3Object* object, char* buf, size_t size); /* "None" for a NULL object */
    /* Dotted Outer chain, e.g. "Engine.Actor"; "" for a NULL object. */
    size_t(T3SDK_CALL* ObjectPathName)(T3Object* object, char* buf, size_t size);
    size_t(T3SDK_CALL* NameToString)(uint32_t name, char* buf, size_t size); /* "<invalid name>" for an unknown value */
} T3SdkApi;

typedef int(T3SDK_CALL* T3ModInitFn)(const T3SdkApi* api);
typedef void(T3SDK_CALL* T3ModShutdownFn)(void);

#endif /* T3SDK_T3SDK_H */
