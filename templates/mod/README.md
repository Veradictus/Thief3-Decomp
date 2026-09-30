# My Mod

A mod for Thief: Deadly Shadows, built on
[T3SDK](https://github.com/Veradictus/Thief3-Decomp).

This folder started as T3SDK's mod template (`templates/mod/`). The sections
below say how to make it yours, build it, try it and publish it; replace them
with your mod's own description when you are done.

## Make it yours

1. Copy this folder into a new repository (or, if it is a GitHub template
   repository, click **Use this template**).
2. In `CMakeLists.txt`, set the mod's id (`MOD_ID`) and version
   (`project(... VERSION 0.1.0)`). The id is the mod's permanent name, its
   install folder and its DLL's name: 1-64 characters of `a-z`, `0-9`, `_` and
   `-`. The version there is the only one: `mod.json`, the package name and
   the release tag follow it.
3. In `mod.json.in`, fill in `name`, `authors`, `description` and `tags`, and
   add `homepage`, `license`, `requires` or `conflicts` as needed. The fields
   are described in [docs/mods.md](https://github.com/Veradictus/Thief3-Decomp/blob/main/docs/mods.md).
4. Choose a license: replace `LICENSE` with its text and add
   `"license": "<SPDX id>"` (for example `"MIT"`) to `mod.json.in`.
5. Write the mod in `src/mod.cpp`. The API is `t3sdk/t3sdk.h`; its lifecycle
   and threading rules are in
   [docs/sdk.md](https://github.com/Veradictus/Thief3-Decomp/blob/main/docs/sdk.md).
   Content (textures, maps, loose game files) goes into `files/`, see
   [files/README.md](files/README.md).

## Build

You need Windows and Visual Studio 2022 or newer with **Desktop development
with C++** (it brings CMake and Ninja). The game is a 32-bit program, so the
mod is built for x86. In an **x86 Native Tools Command Prompt for VS 2022**:

```bat
cmake --preset release
cmake --build --preset package
```

That writes `build/release/<id>-<version>.t3mod` (and the DLL next to it).
In Visual Studio or VS Code, open the folder, pick the **Release** preset and
build the `package` target. **RelWithDebInfo** also writes a PDB for
debugging; the package never includes it.

CMake downloads the SDK headers from the T3SDK release named by
`T3SDK_VERSION` (0.2.0 is the first release whose zip has them). To build
against a T3SDK checkout instead, pass its headers:

```bat
cmake --preset release -DT3SDK_INCLUDE_DIR=C:/path/to/Thief3-Decomp/sdk/include
```

## Try it

Drag the `.t3mod` into the T3SDK launcher's **Mods** page, enable it and
play. The mod's log lines appear in the game's `System/T3SDK.log`, tagged
with its name. Without the launcher, copy the DLL into `System/mods/`.

## Release

1. Set the new version in `CMakeLists.txt` and commit.
2. Tag the commit `v<version>` (for example `v0.2.0`) and push the tag.

`.github/workflows/build.yml` builds every push; for a tag it checks that the
tag matches the version, creates a GitHub release with
`<id>-<version>.t3mod` and prints the package's SHA-256. A published version
never changes: fix a problem with a new version.

## Submit it to the mod index

The launcher's mod browser lists the mods in T3SDK's
[mod index](https://github.com/Veradictus/Thief3-Decomp/tree/main/modindex).
In a fork of T3SDK, with the released package downloaded:

```sh
python tools/modindex.py add <id>-<version>.t3mod \
  --url https://github.com/<you>/<repo>/releases/download/v<version>/<id>-<version>.t3mod
```

Then open a pull request with the `modindex/mods/<id>.json` it wrote. CI
downloads the package and checks it against the entry; the index's README
has the rules.
