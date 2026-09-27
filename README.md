# Thief: Deadly Shadows decompilation

A work-in-progress matching decompilation of **Thief: Deadly Shadows** (Ion
Storm, 2004) for PC: C++ source that Visual C++ .NET 2003 compiles back into
byte-identical functions of `T3Main.exe`.

This repository contains no game code or assets. You need your own copy of the
game.

| | |
|---|---|
| Target | `System/T3Main.exe` from the Steam release |
| SHA-1 | `40bf68a54246bcde2fb5fcbc75b94dc7c7f78305` |
| Version ID | `PC_20040610` (the executable's build date) |
| Compiler | Microsoft C/C++ 13.10.3077 (Visual C++ .NET 2003), `/O2 /GX` |
| Progress | 0 of 40,585 functions (baseline) |

[docs/target.md](docs/target.md) describes what is in the executable and how
that was established.

## Setup

Requires Python 3.10+. Windows is the primary platform. On Linux and macOS
the compiler runs under [wibo](https://github.com/decompals/wibo), which is
downloaded automatically.

1. Install the Python dependencies:

   ```sh
   python -m venv .venv
   .venv/Scripts/pip install -r requirements.txt   # .venv/bin/pip elsewhere
   ```

2. Copy `System/T3Main.exe` from your game folder to `orig/PC_20040610/`.

3. **Windows only:** `cl.exe` 13.10 needs `msvcr71.dll` and `msvcp71.dll`
   (the Visual C++ .NET 2003 runtime), which current Windows doesn't ship.
   Many games from 2003-2006 include both in their folder (for example
   *Prince of Persia: The Sands of Time* on Steam). Point `configure.py` at such
   a folder.

4. Configure and build:

   ```sh
   .venv/Scripts/python configure.py --msvc-runtime "<folder with msvcr71.dll and msvcp71.dll>"
   .venv/Scripts/ninja
   ```

`ninja` downloads the pinned tools (objdiff-cli, delink, the MSVC 7.1
compiler), splits `T3Main.exe` into objects, compiles `src/`, and prints
progress. It reruns `configure.py` by itself when the configuration changes.

## How it fits together

```
orig/PC_20040610/T3Main.exe ─┐
config/PC_20040610/symbols.txt ─┼─ tools/delink_model.py ─ delink ─> build/PC_20040610/obj/  (target objects)
config/PC_20040610/splits.txt ─┘                                          │
                                                                          ├─ objdiff
src/**/*.cpp ─────────── cl.exe 13.10 ───────────> build/PC_20040610/src/  (base objects)
```

- **`config/PC_20040610/symbols.txt`** lists every function and named object
  (dtk format: `name = .text:0xADDRESS; // type:function size:0x..`). It is the
  source of truth for names and function boundaries. It was bootstrapped from
  Ghidra and is edited by hand from then on.
- **`config/PC_20040610/splits.txt`** declares the translation units found so
  far. Functions no unit claims are grouped into `auto/text_<ADDRESS>` units.
- **`tools/delink_model.py`** combines both with the executable into the input
  for [delink](https://github.com/dbalatoni13/delink), recovering absolute
  relocations with iced-x86 (the exe has no relocation table).
- **delink** cuts the executable into COFF objects. **objdiff** compares them
  with what `src/` compiles to.

## Decompiling a function

1. Declare its translation unit in `splits.txt` (the `.text` range may not cut
   through a function), and add options for it to `UNITS` in `configure.py`
   when it needs any.
2. Write the code in `src/<unit path>.cpp`.
3. Rename the function in `symbols.txt` to its MSVC decorated name (e.g.
   `?Close@FHandlePair@@QAEXXZ`) so objdiff pairs it with your compiled function.
4. Run `ninja`, then open the repository folder as the project in
   [objdiff](https://github.com/encounter/objdiff) to diff.

[decomp.me](https://decomp.me) has the same compiler for scratches: platform
"Windows (9x/NT)", compiler "Microsoft Visual C/C++ 7.1 .NET 2003".

## Ghidra

`tools/ghidra_headless.py` drives a local Ghidra 12 database in `ghidra/`:

```sh
python tools/ghidra_headless.py bootstrap   # import, analyse, find missed functions, export symbols.txt (~12 min)
```

Open `ghidra/T3Main.gpr` in the Ghidra GUI to browse and decompile. The
bootstrap overwrites `symbols.txt`, so after names have been added by hand,
use `export -o <file>` and merge.

## Layout

```
config/<version>/   symbols.txt, splits.txt
docs/               notes on the target
include/, src/      decompiled headers and sources
orig/<version>/     your copy of T3Main.exe (not committed)
tools/              build and analysis scripts; tools/ghidra/ has the Ghidra scripts
```

## References

- [decomp.wiki](https://decomp.wiki): community wiki for matching decompilation
- [objdiff](https://github.com/encounter/objdiff), [decomp.dev](https://decomp.dev)
- [delink](https://github.com/dbalatoni13/delink), used the same way by the
  Need for Speed: Most Wanted PC decompilation
