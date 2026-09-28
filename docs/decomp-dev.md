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
`splits.txt` or `symbols.txt` changed without a new report: the report's
units must be the ones `configure.py` plans, with the same functions (by
address), and the functions it compiles must be exactly those with a
`// FUNCTION:` line in `src/`. Renaming symbols does not make the report
stale; adding a function, resizing one or integrating does.

The report holds names, addresses, sizes and match percentages, and no bytes
of the game. CI cannot prove the matches it lists: `tools/agent/accept.py`
proved each one before it entered `src/` (see "Keeping the number honest").
Other decompilations without a redistributable binary publish the same way,
for example [rac1-decomp](https://github.com/Lynder063/rac1-decomp)
(`progress/report.json`).

Progress categories (set in `configure.py`): **main** "Game & engine" is the
headline, with **game** and **engine** under it; **libs** is qhull, the MSVC
runtime, STL, D3DX and Havok, matched from library objects or original
sources rather than decompiled. Units get a category from `UNITS` or
`config/<version>/units.json`, or failing that from their address (before
`LIBRARY_START`, `0x10CFBFB0`, where qhull and then the C runtime begin, and
the `.text$x` funclets: main; after: libs).

## One-time setup (repository owner)

The repository is registered (at <https://decomp.dev/manage/new>, platform
*Windows (win32)*). Left to do on decomp.dev, signed in as an admin of the
repository:

- In the project's settings, set the default category to **main**, so the
  headline counts the game and its engine rather than the libraries too.
- Optionally install the decomp.dev GitHub App, which comments on pull
  requests with the functions they improve or regress.

A project stays hidden from decomp.dev's list until 0.5% of its code matches
(about 21 KB of the game and engine code, 27 KB of everything); its page and
badges work before that.

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

The report also under-counts: objdiff scores some functions the gate matched
just below 100% (EH frames, references into a named array at an offset; see
[matching.md](matching.md), "objdiff's report and the gate").
