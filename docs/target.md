# Target: T3Main.exe

What we know about the binary this project matches, and the evidence for it.
Reproduce the numbers with `python tools/peinfo.py orig/PC_20040610/T3Main.exe`.

## The game install

Thief: Deadly Shadows (Ion Storm, 2004) on Steam. Only `T3Main.exe`, the
game itself, is in scope. The launchers and copy-protection components next to
it are out of scope: this project does not analyse, modify or bypass them, and
the game is started through Steam as usual.

| File | What it is |
|---|---|
| `T3Main.exe` (6,455,296 bytes) | The game: engine, game code, and middleware statically linked. **Target.** |
| `runme.exe`, `t3.exe`, `Ion Launcher.exe` | Launchers; Steam starts the game through them. Out of scope. |
| `testapp.exe` | Copy-protection system check left over from the retail release. Out of scope. |
| `binkw32.dll`, `eax.dll` | RAD Bink and Creative EAX runtimes (delay-loaded by `T3Main.exe`). |

The supported build is the Steam `T3Main.exe` (patch 1.1), a standard MSVC
executable with a plain import table.

## T3Main.exe

| | |
|---|---|
| SHA-1 | `40bf68a54246bcde2fb5fcbc75b94dc7c7f78305` |
| Build timestamp | 2004-06-10 18:13:46 UTC (after the May 2004 release; the version resource still says 1.0.0.1) |
| Image base | `0x10900000`, relocations stripped (no `.reloc`) |
| Entry point | `0x10D1F7AF` (CRT `WinMainCRTStartup`) |
| PDB (not shipped) | `c:\T3_Code\Dev\Build\T3\Win32\Release\T3Main.pdb` |
| Linker | 7.10.3077 |

Sections: `.text` 5.4 MB, `.rdata` 0.7 MB, `.data` 1.0 MB (of which 0.1 MB
initialised), `.tls`, `.data1`, `.rsrc`.

### Compiler

The Rich header records every tool that contributed an object:

| Tool | Build | Objects | Notes |
|---|---|---|---|
| C++ 13.10 | 3077 | 1136 | Visual C++ .NET 2003 RTM. Game, engine, STL. |
| C 13.10 | 3077 | 218 | C runtime (static), libjpeg 6a, other C code. |
| MASM 7.10 | 3077 | 50 | Mostly CRT assembly. |
| C/C++ 13.00 | 9178 | 71 | A static library built with a VC 7.0-era compiler, most likely D3DX 8. |
| C++ 12.x | 9044 | 1 | One VC 6.0-era object from a prebuilt library. |
| MASM 6.14 | 8444 | 1 | Likewise. |
| Linker 7.10 | 3077 | | |

So the project compiler is **Microsoft C/C++ 13.10.3077**. The
`dbalatoni13/compilers` bundle's `Win32/7.1` is exactly this build, and
decomp.me offers it as "Microsoft Visual C/C++ 7.1 .NET 2003" (`msvc7.1`,
platform "Windows (9x/NT)").

Flags verified so far: `/O2 /GX`. Three functions were matched byte for byte
with these (`0x10901070`, `0x109010A0`, `0x10908E60`), so optimisation level,
frame-pointer omission and dllimport call codegen line up. Floating point,
`/G5`-`/G7` scheduling and inlining details still need functions that
exercise them.

### Layout facts that matter for splitting

- Every function in the main part of `.text` starts on a 16-byte boundary,
  padded with `int3` (0xCC): `/O2` COMDAT alignment.
- C++ exception-handling funclets (`__unwindfunclet$...`, `__ehhandler$...`)
  are in `.text$x`, which the linker places after all other code. Ghidra
  names the unwind funclets `Unwind@<address>`. They are separate from their
  parent functions.
- C++ `catch` blocks are inline in the parent function (Ghidra's `Catch@`
  functions); `tools/ghidra/ExportSymbols.java` folds them back.
- Switch statements use absolute jump tables, and sometimes byte index tables,
  placed right after the function's code.
- About 28 RTTI type descriptors exist (runtime, STL, CppUnit), so the game
  is built with `/GR-`.

### What is linked in

- **Engine**: Ion Storm's modified Unreal Engine 2, shared with Deus Ex:
  Invisible War. Package names in the binary: `Core`, `Engine`, `Window`,
  `WinDrv`, `D3DDrv`, `Fire`, `AICore`, `GamePhysics`. Log categories include
  `[DX2Game]` and `[Warfare]` (the Unreal Engine 2 codename). Unlike Epic's
  retail games everything is statically linked, so there are no DLL exports to
  harvest symbols from.
- **UnrealScript natives**: 254 `exec*` names are in the binary, alongside
  the script packages (`System/*.t3u`).
- **Havok 2**: `hkWorld.cpp`, `hkCollidable.cpp`, and others appear in assert
  strings.
- **CppUnit** test code is linked into the release build
  (`ObjectSystemUnitTests.cpp`, `StateManagerTest.cpp`, ...).
- **libjpeg 6a**, **D3DX 8**, the **static C runtime** (no `msvcr71.dll`
  import) and Dinkumware STL.
- **Imports**: Direct3D 8, DirectInput 8, DirectSound, plus Win32. Bink and EAX
  are delay-loaded.

## Analysis state (baseline)

Ghidra 12.1.4 auto-analysis found about 32,200 functions.
`FindMissingFunctions.java` added about 8,800 more, mostly virtual functions
referenced only from vtables and `__ehhandler$` stubs. After folding catch
blocks into their parents, `symbols.txt` has 40,585 functions. Their extents
cover 96.3% of `.text`; the rest is int3 padding.

The split has 5,324,477 bytes of code in 84 automatic units. delink leaves 3
call targets unresolved. `delink_model.py` hits 20 undecodable instructions,
all in library code: CRT x87 assembly with overlapping entry points, and a
data table inside D3DX's PSGP code that Ghidra took for a function.

The pipeline was checked end to end with a throwaway unit holding two
functions (`0x10901070`, `0x109010A0`): objdiff paired them by decorated name
and reported 2/2 functions, 91/91 bytes matched.
