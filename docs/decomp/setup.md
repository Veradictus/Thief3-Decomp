# Setting up the workbench

How to get from a fresh checkout to a working Ghidra database and a
compiling, diffable split of `T3Main.exe`, so you can follow
[reverse-engineering.md](reverse-engineering.md) and
[first-match.md](first-match.md) locally.

## What you need

| | |
|---|---|
| The game | Your own copy of Thief: Deadly Shadows on Steam, patch 1.1 (see [target.md](../target.md)). |
| Python | 3.10 or newer, for the tools and a `.venv`. |
| Ghidra | Installed by hand; this project uses 12.1.4. No download script fetches it. |
| The MSVC 7.1 compiler bundle, objdiff, delink, wibo | Downloaded automatically the first time you run `ninja` (below); you only need network access once. |
| `msvcr71.dll` and `msvcp71.dll` | Needed to run `cl.exe` on Windows; not part of the compiler bundle (see below). |

Everything the tools produce from your copy of the game (the Ghidra
database, split objects, decompiler output) stays in ignored local folders
(`orig/`, `ghidra/`, `build/`, `.venv/`); never commit it
([CONTRIBUTING.md](../../CONTRIBUTING.md)).

## Clone and the Python environment

```sh
python -m venv .venv
.venv/Scripts/pip install -r requirements.txt
```

`requirements.txt` pins `iced-x86` (instruction decoding, used by
`tools/delink_model.py` and the matching tools' difficulty scoring) and
`ninja`.

## Point the tools at the game

Copy `T3Main.exe` from `<game folder>/System/` to `orig/PC_20040610/T3Main.exe`
in your checkout. `orig/` is ignored (`.gitignore` blocks everything under it
except a `.gitkeep`), so this never risks a commit. Both `configure.py` and
`tools/ghidra_headless.py` expect the exe at exactly this path; there is no
flag to point them elsewhere. If it is missing, `configure.py` prints a
warning and the split step of `ninja` fails.

## Build the Ghidra database

Set `GHIDRA_INSTALL_DIR`, or install Ghidra where
[`tools/ghidra_headless.py`](../../tools/ghidra_headless.py) looks for it by
default (the newest `ghidra_*` folder under
`%LOCALAPPDATA%/Programs/Ghidra` on Windows, `~/ghidra` elsewhere), then:

```sh
python tools/ghidra_headless.py bootstrap
```

This imports the exe, auto-analyses it, runs
[`FindMissingFunctions.java`](../../tools/ghidra/FindMissingFunctions.java)
twice (it finds functions auto-analysis missed, mostly virtual functions only
referenced from vtables and `__ehhandler$` stubs), applies the names already
recorded in `config/PC_20040610/symbols.txt`, then exports it again so the
file's names survive the rebuild. It takes about 12 minutes. Open
`ghidra/T3Main.gpr` in the Ghidra GUI afterwards if you want to browse the
database interactively; the headless tools work against the same project.

You only need this for [reverse-engineering.md](reverse-engineering.md)'s
`Decompile.java` and `Disassemble.java` scripts. Compiling and diffing
candidates (below) does not touch Ghidra at all.

## Build the split and the compiler workbench

```sh
python configure.py --msvc-runtime <dir containing msvcr71.dll and msvcp71.dll>
ninja
```

`configure.py` writes `build.ninja` and `objdiff.json` for the version it
targets (`PC_20040610` by default). `ninja` then:

1. downloads objdiff-cli, delink, the MSVC 7.1 compiler bundle, and, off
   Windows, wibo (the pinned versions in `configure.py`'s `TOOL_TAGS`);
2. splits `orig/PC_20040610/T3Main.exe` into COFF objects with delink, one
   per translation unit declared in `config/PC_20040610/splits.txt`, plus
   automatic chunks for everything else in `symbols.txt`;
3. compiles whatever exists in `src/` (nothing yet, besides a `.gitkeep`)
   with the same flags as the original build;
4. writes a progress report.

The compiler bundle
([`dbalatoni13/compilers`](https://github.com/dbalatoni13/compilers)) does
not ship `msvcr71.dll` or `msvcp71.dll`: `cl.exe` needs them to run at all,
and they cannot be redistributed with the bundle. Many games from
2003-2006 ship them; point `--msvc-runtime` (or set `MSVC71_RUNTIME`) at a
folder holding both, and `configure.py` copies them next to `cl.exe`. Off
Windows, the compiler runs through wibo instead and this flag is not needed.

Re-run `configure.py` (with the same flags) whenever `splits.txt` or
`symbols.txt` change; `ninja` also does this on its own, since `build.ninja`
depends on both files.

## Check that it works

```sh
python tools/agent/selftest.py
```

About ten seconds. It needs the toolchain (the compiler bundle downloaded
above, and wibo or your `msvcr71.dll`/`msvcp71.dll`) but not the game or
Ghidra: it compiles synthetic reference C++ with the real MSVC 7.1, reshapes
it the way delink shapes a real split, and runs the whole matching chain
(claims, `try.py`, `accept.py`, the lint, integration, the guard) against it.
A clean run prints one line per test and ends with `all passed`.

If you have the exe in place, `python tools/peinfo.py orig/PC_20040610/T3Main.exe`
reproduces the numbers in [target.md](../target.md) (SHA-1, timestamp,
section sizes) as a sanity check that your copy matches the supported build.

> [!NOTE]
> The matching harness itself (`tools/agent/`) is proven only against the
> synthetic targets `selftest.py` builds. Nobody has yet run `try.py` or
> `accept.py` against a real function of the split `T3Main.exe`; expect rough
> edges the first time you do (see [handoff.md](../handoff.md)).

With the workbench built, continue to
[reverse-engineering.md](reverse-engineering.md) to find something to name,
or [first-match.md](first-match.md) to match a function.
