# Thief: Deadly Shadows modding SDK (T3SDK)

Goal: a modding SDK for the Steam `T3Main.exe` that injects into the local
game install and enables large mods, multiplayer first among them. The
matching-decompilation tooling in this repo is the reverse-engineering
workbench, and decompilation proceeds alongside the SDK: name what we
identify (`symbols.txt`) and document it (`docs/engine.md`). The matching
decompilation is public: hand-written C++ in `src/`/`include/` that compiles
to the game's bytes (process in [docs/matching.md](docs/matching.md)). Raw
decompiler output, disassembly and game binaries or data never enter the
repository.

**Start with [docs/handoff.md](docs/handoff.md)**: current status and next
steps. Engine addresses and layouts, with evidence, are in
[docs/engine.md](docs/engine.md); SDK settings and tools in
[docs/sdk.md](docs/sdk.md).

## Commands

```sh
.venv/Scripts/python tools/sdk.py build|deploy|run|log|undeploy   # the SDK (MSVC x86, CMake + Ninja)
.venv/Scripts/python tools/sdk.py screenshot|click <x> <y>|keys <k..>|close   # drive and check a running game
python tools/ghidra_headless.py script tools/ghidra/Decompile.java <addr> [refs:<addr>]
python tools/ghidra_headless.py script tools/ghidra/Disassemble.java <addr> [<addr>+<count>]
python tools/ghidra_headless.py names                              # apply symbols.txt names to ghidra/
python tools/ghidra_headless.py bootstrap                          # rebuild ghidra/ + symbols.txt (~12 min)
.venv/Scripts/python configure.py --msvc-runtime <dir> && .venv/Scripts/ninja   # split/diff workbench
python tools/agent/next.py status | context.py <addr> | try.py | accept.py        # matching loop (docs/matching.md)
python tools/assets/t3pack.py roundtrip|apply|install|restore                    # write edited maps back
cd launcher && yarn install && yarn tauri dev                                      # the launcher (docs/launcher.md)
cd launcher && yarn verify                                                         # launcher UI: types, lint, format, tests
python tools/assets/selftest.py; python tools/agent/selftest.py                    # tests that need no game files
```

## Facts

- Image base `0x10900000`, no relocations, so absolute addresses are stable.
  The SDK refuses to hook any build other than PE timestamp `0x40C8A4DA`.
- The SDK loads as `System/dinput8.dll`, patches the exe entry point to start
  outside the loader lock, hooks `PeekMessageA` (frames), `ExitProcess` and
  `TerminateProcess` (shutdown), and `FOutputDeviceFile::Serialize` (engine
  log). It validates the UObject layout at runtime before `EngineReady()`.
- Built-in fixes (`T3SDK.ini`): skip intros, native resolutions, borderless
  window (hooks `Direct3DCreate8` → `CreateDevice`/`Reset`), widescreen UI
  (`Config::GetFloat`, `Window::PlacedPosition`). A vectored handler logs
  crashes to `System/T3SDK.log`.
- Mods: `System/mods/*.dll` exporting `T3Mod_Init(const T3SdkApi*)`. The API is
  plain C, `__cdecl`, and only grows (check `api->size`).
- Engine: Ion Storm's early Unreal Engine 2 fork (script packages version 95 /
  licensee 133). FName carries a 16-bit instance number, printed as
  `Name__N`. UStruct SuperField is at `0x2C`. Unreal's network layer is
  absent.
- Workbench compiler: MSVC 13.10.3077 (`/O2 /GX`), verified byte for byte on
  three functions.

## Working agreements

- Ask the user before deploying into the game folder or launching the game,
  and close the game after each test.
- The user commits and pushes; don't commit unless asked. Commit messages
  follow Conventional Commits (`feat`, `fix`, `docs`, ...; see
  [CONTRIBUTING.md](CONTRIBUTING.md)).
- Legal: no game files, extracted assets, raw decompiler output or disassembly
  (beyond a few documenting instructions), decompiled library code (MSVC
  runtime, D3DX, Havok), fake matches (inline asm), DRM work or personal data
  (local paths, names) in the repository. Details in CONTRIBUTING.md.
- `config/PC_20040610/symbols.txt` is the name database; record identified
  functions and globals there (MSVC decorated names where known, otherwise
  `Class::Method`), then run `ghidra_headless.py names`.
- Never commit `orig/`, `ghidra/`, `build/`, `.venv/` or game files.
