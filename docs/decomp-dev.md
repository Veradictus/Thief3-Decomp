# Progress on decomp.dev

[decomp.dev](https://decomp.dev/Veradictus/Thief3-Decomp) shows the progress
of public matching decompilations. It reads an objdiff report that this
repository's CI uploads; nothing is uploaded by hand. How the site finds
reports is in [research/llm-matching.md](research/llm-matching.md), section 3.

## How the report gets there

The report comes from a local build: CI cannot make it, because the build
splits `T3Main.exe`, which never enters the repository or CI.

1. After integrating matched functions ([matching.md](matching.md)), run
   `python tools/progress_report.py write` on a machine with `orig/`. It runs
   ninja, which compiles `src/` and has objdiff compare every unit with the
   split exe (`build/PC_20040610/report.json`), checks that the report
   describes the tree, and copies it to `progress/PC_20040610/report.json`,
   one line per function so that a new match is a small diff.
2. Commit that file with the source.
3. On every push and pull request, `.github/workflows/build.yml` (workflow
   "progress") runs `python tools/progress_report.py check`, validates the
   report with objdiff, and uploads it as the artifact `PC_20040610_report`.
   decomp.dev takes it from the latest push run on the default branch.

`check` needs neither the exe nor the compiler. It fails when `src/`,
`splits.txt`, `symbols.txt` or `categories.txt` changed without a new report:
the report's units must be the ones `configure.py` plans, with the same
functions (by address), and the functions it compiles must be exactly those
with a `// FUNCTION:` line in `src/`. Renaming symbols does not make the report
stale; adding a function, resizing one or integrating does. It also fails when
a function in `src/` is not game code by `categories.txt`: only Ion Storm's
code is published (CONTRIBUTING.md).

The report holds names, addresses, sizes and match percentages, and no bytes
of the game. CI cannot prove the matches it lists: `tools/agent/accept.py`
proved each one before it entered `src/` (see "Keeping the number honest").
Other decompilations without a redistributable binary publish the same way,
for example [rac1-decomp](https://github.com/Lynder063/rac1-decomp)
(`progress/report.json`).

## What the report counts

The decompilation covers Ion Storm's game code only, so that is the headline.
Each unit's progress category comes from `config/<version>/categories.txt`,
which `tools/classify.py` writes from the exe (see "Whose code it is" below):

| Category | Name | What |
|---|---|---|
| **main** | Game | Ion Storm's code: the decompilation's scope, and decomp.dev's headline |
| **engine** | Engine (Epic) | Epic's Unreal Engine 2 (Core, Engine, Fire, the drivers, Window): not decompiled |
| **libs** | Libraries | Havok, qhull, the MSVC runtime, STL, D3DX, libjpeg, LIPSinc: not decompiled |
| **unknown** | Unclassified | code without evidence yet of whose it is |

Engine, libraries and unclassified code stay in the report for reference, with
their sizes; only the Game category is progress. Auto units never span two
categories (`configure.py` breaks them at every boundary). Left out entirely:

- the `.text$x` exception-handling funclets no declared unit takes. The
  compiler emits them with their parent function, which is what counts; a
  declared unit includes its own functions' funclets.
- data. Nothing is split into units yet, so `write` drops the data measures
  and the data-only `__shared_data` unit, and decomp.dev shows no data bar.

## Whose code it is

The exe does not record which object file a function came from, and Epic's
and Ion Storm's files sit side by side (Ion Storm added its own files to
Epic's Engine package). `python tools/classify.py write` labels every function
from evidence in the exe, `explain <addr>` prints a function's evidence, and
`stats` the totals:

- The native class registrations: each UObject class registers itself lazily
  with its package name ([engine.md](engine.md), "Native class
  registration"). Ion Storm's packages (AICore, GamePhysics, T3AI, T3Game,
  T3GamePhysics, T3Player) are game; Epic's (Core, Engine, Fire, D3DDrv,
  WinDrv, Window) are engine, except the classes Ion Storm added to them
  (the `*LinkDataObject` links, archetypes, stimuli, subsystems; listed in
  the tool). The registration's getter and the class's internal constructor
  sit in the class's own object file.
- Each class's vtable, from its constructor: its methods take the class's
  category (bodies of 16 bytes or less do not count: the linker folds
  identical ones into a single copy).
- Names in `symbols.txt` of Epic's classes, and strings a function uses:
  Ion Storm's file, ini and system names (`T3...`, Flesh, schemas,
  `cClass::` names, `.\Source\` paths), library errors and class names (STL,
  LIPSinc, Havok), and messages only Epic's stock code prints.
- The library region from `LIBRARY_START` (`0x10CFBFB0`, where qhull and then
  the C runtime begin).

A function between two pieces of evidence of one category takes it, when they
are close enough: inside Epic's libraries only engine evidence fills long
stretches, outside them only game evidence (the tool's docstring has the
rule). Everything else stays unclassified, and so is not published:
integrate.py skips it, and the work queue offers game code only.

## One-time setup (repository owner)

The repository is registered (at <https://decomp.dev/manage/new>, platform
*Windows (win32)*). Left to do on decomp.dev, signed in as an admin of the
repository:

- In the project's settings, set the default category to **main**, so the
  headline counts Ion Storm's game code rather than everything in the exe.
- Optionally install the decomp.dev GitHub App, which comments on pull
  requests with the functions they improve or regress.

A project stays hidden from decomp.dev's list until 0.5% of its code matches
(about 13 KB of the 2.6 MB of game code); its page and badges work before
that.

## Badges

The README shows these. decomp.dev's shields take `style=flat` (the
default), `plastic` or `flatsquare`; `forthebadge` is refused at the moment.

```markdown
[![Decompiled](https://decomp.dev/Veradictus/Thief3-Decomp.svg?mode=shield&measure=matched_code_percent&category=main&label=Decompiled)](https://decomp.dev/Veradictus/Thief3-Decomp)
[![Functions](https://decomp.dev/Veradictus/Thief3-Decomp.svg?mode=shield&measure=matched_functions&category=main&label=Functions)](https://decomp.dev/Veradictus/Thief3-Decomp)
[![Progress report](https://github.com/Veradictus/Thief3-Decomp/actions/workflows/build.yml/badge.svg)](https://github.com/Veradictus/Thief3-Decomp/actions/workflows/build.yml)
![Progress chart](https://decomp.dev/Veradictus/Thief3-Decomp.svg?w=512&h=256)
```

## Keeping the number honest

`objdiff-cli report generate` ignores relocation targets by default, so a
function that calls the wrong callee would still count as matched;
`configure.py` pins `functionRelocDiffs: name_address` in `objdiff.json` to
stop that. It still cannot see a wrong float or string literal (MSVC's COMDAT
constants all sit at offset 0). So functions enter `src/` only through
`tools/agent/accept.py`, which checks callees and data values by address and by
value (see [matching.md](matching.md)): the report is the progress display, the
gate is the proof.

The report can still under-count: objdiff scores a few functions the gate
matched just below 100% (a static local's guard, a reference into a named
array at an offset; see [matching.md](matching.md), "objdiff's report and
the gate"): 8 of the 1,805 in `src/`.
Functions with an exception frame no longer do: `tools/split.py` gives the
split objects the `__except_list` relocations the exe dropped.
