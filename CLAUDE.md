# Thief: Deadly Shadows decompilation

Matching decompilation of `T3Main.exe` (PC, Steam build of 2004-06-10, version
ID `PC_20040610`). README.md covers setup and the pipeline; docs/target.md
covers what is known about the binary.

## Facts

- Compiler: MSVC 13.10.3077 (VC++ .NET 2003 RTM), from the Rich header. Flags
  `/O2 /GX` are verified on three functions; `CFLAGS` in configure.py holds the
  project defaults and `UNITS` holds per-unit overrides.
- Image base 0x10900000, no relocation table. Functions in the main `.text` are
  16-byte aligned with int3 padding. EH unwind funclets live in `.text$x` at
  the end of `.text`; catch blocks are inline in their parent function.
- Engine is Ion Storm's Unreal Engine 2 fork (shared with Deus Ex: Invisible
  War), statically linked with Havok 2, D3DX 8, libjpeg 6a, CppUnit and the
  static CRT.

## Commands

```sh
.venv/Scripts/python configure.py --msvc-runtime <dir with msvcr71.dll+msvcp71.dll>
.venv/Scripts/ninja                          # split, compile, report, print progress
python tools/ghidra_headless.py bootstrap    # rebuild ghidra/ and symbols.txt (~12 min)
python tools/peinfo.py orig/PC_20040610/T3Main.exe
```

## Conventions

- `config/PC_20040610/symbols.txt` is the source of truth for names and
  function extents. Decompiled functions get their MSVC decorated name there so
  objdiff pairs them. Unnamed functions are `FUN_xxxxxxxx`.
- `config/PC_20040610/splits.txt` lists identified translation units; unit
  paths are relative to `src/`. Unclaimed functions fall into `auto/` units.
- Generated files (`build/`, `build.ninja`, `objdiff.json`) and `orig/`,
  `ghidra/`, `.venv/` are never committed.

## Known gaps in the split

- Function extents run to the next function start minus int3 padding, so an
  undiscovered function would be absorbed by the one before it. delink
  reports 3 unresolved call targets.
- Switch byte index tables that follow a jump table are emitted inside the
  function; delink's rel32 recovery decodes them as code, so large index
  tables may get spurious relocations.
- 20 undecodable instructions remain, all in library code (CRT x87 assembly,
  D3DX PSGP data).
- String literals and most data are named `DAT_xxxxxxxx`, not MSVC's
  `??_C@...` names, so relocations to them show as differences until renamed.
- Unwind funclets are named `Unwind@<address>`, not
  `__unwindfunclet$<parent>$<n>`.
