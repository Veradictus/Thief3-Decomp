# Naming and documenting what you find

Once you can state a fact about `T3Main.exe` with its evidence (see
[reverse-engineering.md](reverse-engineering.md)), record it: a name in
`symbols.txt`, and, for anything worth explaining, an entry in
[engine.md](../engine.md). [CONTRIBUTING.md](../../CONTRIBUTING.md) treats
this as a hard rule, not a suggestion: "record every engine address you use
in `docs/engine.md` with its evidence, and its name in
`config/PC_20040610/symbols.txt`."

## The symbols.txt format

[`config/PC_20040610/symbols.txt`](../../config/PC_20040610/symbols.txt) is
one line per symbol:

```
<name> = <section>:0x<address>; // type:<function|object|label> size:0x<bytes>
```

For example:

```
Config::GetFloat = .text:0x10910B60; // type:function size:0x13A
GEngine = .data:0x10F34AD0; // type:object size:0x4
```

Lines are sorted by address, `#`-comment lines are allowed, and every name
must be unique across the whole file:
[`tools/symbols.py`](../../tools/symbols.py) (the parser both `configure.py`
and the matching tools use) raises an error naming the file and line of the
first use if you duplicate one. A function's size covers everything that
belongs with it (its code, any switch tables, and EH-only blocks the linker
can only reach through the exception tables), which
[`ExportSymbols.java`](../../tools/ghidra/ExportSymbols.java) already
computes for you; when you hand-add or rename an entry, keep whatever size
Ghidra exported unless you have a specific reason to change it.

## Naming conventions

The file mixes four kinds of name, and the tools tell them apart by shape:

| Kind | Looks like | Meaning |
|---|---|---|
| Placeholder | `FUN_10a52420`, `DAT_10906b08`, `LAB_...`, `switchdataD_...`, `caseD_...`, `thunk_FUN_...`, `__imp_...` | Ghidra's default name; nothing is known yet. |
| `Class::Method` | `Config::GetFloat`, `Window::PlacedPosition` | Identified, but the MSVC decorated form isn't known (or doesn't apply, for a free function you'd just use a plain descriptive name). |
| MSVC decorated | `?uflow@?$basic_streambuf@DU?$char_traits@D@std@@@std@@MAEHXZ`, `??0CRect@@QAE@HHHH@Z` | The real compiled symbol: from Ghidra's Function ID matching a library, or from a matched function once it's accepted (see [first-match.md](first-match.md)). |
| Global (`G` prefix) | `GEngine`, `GLog`, `GIsRunning` | A named global. Where the name is also Unreal's own (`GEngine`, `GLog` are genuine engine globals, not invented labels), use it; otherwise pick a descriptive `G`-prefixed name. |

Use the MSVC decorated name whenever you know it — it's what a compiled
candidate actually produces, and it's what
[the matching gate](first-match.md) checks references against. Fall back to
`Class::Method` (or a plain name for a free function) when you know what
something is but not its exact decorated form;
[`ImportNames.java`](../../tools/ghidra/ImportNames.java) turns a
`Class::Method` name into a proper Ghidra namespace and symbol for you.

Leave `Unwind@<address>` funclet names alone. MSVC 7.1 calls them `$Lnnn`
internally, a label that changes on every rebuild, so they can't be paired
by name; the matching tools identify them through their parent function
instead (see [matching.md](../matching.md)).

## Adding an object entry

For a global you've identified, add a line in the same format, `type:object`
and a byte size (4 for a pointer, `BOOL` or `int`; the real size for
anything bigger — `GNextLevelURL`, for example, is a 0x400-byte buffer).
Where the line goes in the file doesn't matter much day to day (export and
save both re-sort by address), but keeping it near its neighbours makes for
a readable diff.

## Applying names to Ghidra

```sh
python tools/ghidra_headless.py names
```

This runs [`ImportNames.java`](../../tools/ghidra/ImportNames.java) against
your local database: every `symbols.txt` line whose name isn't a
placeholder gets applied, renaming a function's own symbol or creating a
(possibly namespaced) label for data. It skips an address where Ghidra's
analysis already found a *different* real name (so it never fights Function
ID), and it skips import thunks, whose name comes from the import itself.
For an `object` entry it also sizes the data: a dword when nothing is
defined yet and the size is 4, otherwise an array of whatever element type
is already there. Run this after any `symbols.txt` edit so decompiles show
the new name; `bootstrap` already includes this step, so a fresh database
never loses names you've recorded.

## Writing a docs/engine.md entry

Match the existing style: a short paragraph of context, then a table with
`| What | Address | Status |` columns for addresses, or a field-offset table
for a struct layout (the `UObject`, `TimeManager` and `Window` entries in
[engine.md](../engine.md) are good models for either). Every entry needs a
status:

- **static** — inferred from the executable's code, data, strings or PE
  metadata, not necessarily observed running;
- **verified** — observed in a live game run.

Use exactly these two words; they're what the rest of the documentation
(and this handbook) assumes when it reads "static" or "verified". Don't
invent a third status for something the SDK's own runtime checks happen to
touch — those checks only cover a couple of specific facts (see
[reverse-engineering.md](reverse-engineering.md)) and aren't a general
evidence source for a docs entry.

## Checking your work

```sh
python tools/progress_report.py check
```

This parses `symbols.txt`, plans its units the way `configure.py` does and
compares them with the committed progress report, with nothing but the Python
standard library. It's a fast way to catch a broken edit before you run
anything heavier: a malformed line or a name reused at a different address
makes `tools/symbols.py`'s parser raise immediately, naming the exact line.
It doesn't check that a name is *correct*. Renaming never makes the report
stale; adding or resizing a function does, since it changes the units: then
run `python tools/progress_report.py write` (it needs the exe) and commit the
report with your change. CI runs the same check ([decomp-dev.md](../decomp-dev.md)).

## What not to record

- **No personal data.** Never write a local path or a user name into
  `docs/engine.md` or anywhere else in `docs/`; write `<game folder>` and
  similar placeholders, as the rest of the documentation does.
- **No raw decompiler output.** A short instruction-level snippet that
  documents a specific address (the `TArray` construction pattern in
  [engine.md](../engine.md), for instance) is fine; a pasted decompilation
  is not — it stays in your local `build/` or `ghidra/`.

With a name and an entry recorded, either keep exploring
([reverse-engineering.md](reverse-engineering.md)) or use what you've
learned to match the function itself ([first-match.md](first-match.md)).
