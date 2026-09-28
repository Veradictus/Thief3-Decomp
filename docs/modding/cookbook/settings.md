# Give your mod its own settings

Let a player configure your mod by editing a plain text file, with no help
from the API — `T3SdkApi` has no settings calls, so a mod reads its own
configuration the same way any other Win32 program would.

## The recipe

1. Ship `<id>.ini` next to your DLL. Packaging already supports this: any
   file placed next to your DLL in the package is installed alongside it
   (see [Packaging](../packaging.md)), so the finished layout is
   `System/mods/<id>/<id>.ini`, right next to `System/mods/<id>/<id>.dll`.
2. Find your own DLL's folder at runtime. A DLL is not handed a path the way
   an executable is, but Windows does pass your module's handle to
   `DllMain`; save it there.
3. Read values with `GetPrivateProfileStringW`/`GetPrivateProfileIntW`, the
   same calls T3SDK itself uses to read `T3SDK.ini` (`sdk/loader/sdk.cpp`).

```c
#include <t3sdk/t3sdk.h>

#include <windows.h>
#include <wchar.h>

static const T3SdkApi* api;
static HMODULE selfModule;
static int verbosity = 1; /* default, used if the key or the file is missing */

static void LoadSettings(void) {
    wchar_t path[MAX_PATH];
    wchar_t* slash;

    GetModuleFileNameW(selfModule, path, MAX_PATH);
    slash = wcsrchr(path, L'\\');
    if (slash) {
        slash[1] = L'\0';
    }
    wcscat_s(path, MAX_PATH, L"my-mod.ini");

    verbosity = (int)GetPrivateProfileIntW(L"MyMod", L"Verbosity", verbosity, path);
}

T3SDK_EXPORT int T3SDK_CALL T3Mod_Init(const T3SdkApi* sdk) {
    if (sdk->version < T3SDK_API_VERSION) {
        return 1;
    }
    api = sdk;
    LoadSettings();
    api->Log("verbosity=%d", verbosity);
    return 0;
}

BOOL WINAPI DllMain(HINSTANCE instance, DWORD reason, LPVOID reserved) {
    (void)reserved;
    if (reason == DLL_PROCESS_ATTACH) {
        selfModule = instance;
    }
    return TRUE;
}
```

with `my-mod.ini`:

```ini
[MyMod]
Verbosity=2
```

## Watch out for

- `GetPrivateProfileInt`/`String` return your default when the file, the
  section or the key is missing — there is no error to handle. Ship a
  default `<id>.ini` in your package anyway, so a player has something to
  find and edit.
- T3SDK does not provide a `DllMain` for you, and mods are not required to
  define one; add your own only if you need it, as above. It runs before
  `T3Mod_Init` and is a normal Windows DLL entry point, so keep it simple:
  do only what you would do in any DLL's `DLL_PROCESS_ATTACH`.
- Settings read this way are static for the run: nothing calls `LoadSettings`
  again on its own. Re-read the file yourself (for example from a frame
  callback, occasionally) if you want a player's edits to take effect without
  restarting the game.
- This is your mod's own file, in your own package folder — it has nothing
  to do with `T3SDK.ini` or the game's own `.ini` files, and nothing here
  lets you add a page to the launcher's settings UI.

## Reference

- [Packaging](../packaging.md): how extra files next to your DLL are
  installed.
- [Mod packages](../../mods.md): the installed layout,
  `System/mods/<id>/...`.
