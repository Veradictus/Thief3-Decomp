# Matching decompilation with agents

How functions of `T3Main.exe` get matched byte for byte, mostly by Claude
Sonnet workers under an Opus lead, and how the tools in `tools/agent/` keep
the results honest. The compiler, flags and split are described in
[target.md](target.md), and the research behind this setup in
[research/llm-matching.md](research/llm-matching.md): the worker loop follows
the published agent setups of other MSVC decompilations (a 12-attempt cap,
deferring as a normal outcome, a growing idiom sheet), and the rulers answer
the ways their agents were found to cheat or be fooled.

A worker takes one function at a time: it claims it, reads a context packet,
writes C++ in a scratch file, compiles and diffs it (at most 12 times), then
either has it accepted by a strict gate or defers it with a one-line blocker.
Workers write only scratch files; the tools record claims, attempts and
accepted functions for them. The lead owns everything shared (headers,
`symbols.txt`, `splits.txt`, `configure.py`, `src/`) and integrates accepted
functions into translation units.

## The tools

All of them run from a checkout's root as `python tools/agent/<tool>.py`, in
the main checkout or in a worker's git worktree. Shared state lives in the
main checkout's `build/agent/` (found through git), next to the toolchain and
the split target objects.

| Tool | Who | What |
|---|---|---|
| `next.py claim\|release\|status\|list\|requeue` | worker, lead | The queue, easy first, with claims |
| `context.py <addr>` | worker | The context packet for one function |
| `context.py fill-ghidra --next N` | lead | Caches Ghidra decompiles for the queue head |
| `try.py <addr> <file>` | worker | Compile, diff, verdict, `ATTEMPT k/12`; stops a claim after 4 attempts with no new best |
| `sidebyside.py <addr> <file>` | worker | Every instruction of a candidate next to the target's, references by name; no attempt spent, no verdict |
| `accept.py <addr> <file>` | worker | The gate; records the function |
| `accept.py defer <addr> "<blocker>"` | worker | Records the best attempt and the blocker |
| `clusters.py list\|show\|stamp` | lead | Families of functions equal but for their references; `stamp` matches open members from an accepted one, through accept.py |
| `sweep.py "<prefix>-*"` | lead | Closes a batch of workers: forgotten matches, claims, parking, stamps, costs |
| `integrate.py` | lead | Accepted functions into `src/`, `splits.txt`, `symbols.txt` |
| `wave.py --workers N` | lead | Runs N headless workers in worktrees |
| `selftest.py` | anyone | Tests the whole chain on synthetic targets |

`build/agent/` holds `claims/` (one file per claimed function, with an expiry),
`attempts/<ADDR>/` (a ledger of every scored attempt and a copy of each
source), `accepted/` and `deferred/` (records for the lead), `cache/`
(demangled names, instruction features, Ghidra decompiles), `waves/` (each
wave's commands, prompt, settings and results) and `worktrees/`.

### Queue

`next.py` lists the functions of `symbols.txt` that are Ion Storm's game
code by `config/<version>/categories.txt` (`tools/classify.py`,
[decomp-dev.md](decomp-dev.md), "Whose code it is"), except EH unwind funclets
(`Unwind@`, `.text$x`), import thunks, and functions already accepted,
integrated (a `// FUNCTION:` line in `src/`), deferred or claimed.
`--all-regions` adds unclassified and library code; Epic's engine is never
queued. With the current files that leaves about 10,500 functions. They are
ordered easy first by a difficulty score when iced-x86 and the target's
bytes are available (instructions, plus 3 per conditional branch, 2 per
call, 10 per switch, 10 for an EH frame and 1 per x87 instruction), else by
size. Refit the weights from the attempt ledgers once the pilot has outcomes.

A claim is a file that appears in one atomic step (written aside, then
hard-linked into place, which fails if it exists), so two workers never get
the same function. It expires after two hours (`--ttl`); try.py renews it on
every attempt. Taking over an expired claim, renewing and releasing run
under a short lock. `--unit` restricts a worker to one split unit, and
`--by-class` gives a worker, after the queue head, the queued functions of
the same class (by name, else by vtable) or its nearest neighbours.

Families ([clusters.py](../tools/agent/clusters.py)) are served one member at
a time: the first goes early (its difficulty divided by the family's size),
the others wait while it is open, claimed, or accepted and not yet stamped,
and go to the workers only if the stamp fails (`--include-siblings` lists
them all). `claim` hands out nothing while the split or the toolchain is
missing.

### Context packet

`context.py` prints, leaving out what it cannot find: the symbols.txt name
and demangled signature; the target's instructions (objdiff on the split
object); every callee and global the target references, with unnamed ones
flagged and any name another accepted function proposed for them; the
vtable slots that hold the function (read-only tables of function pointers
whose start the code uses as a constant, cached in
`build/agent/cache/vtables.json`), so a virtual method is declared as one; the
cached Ghidra decompile (`build/agent/cache/ghidra/<ADDR>.c`, filled by
`fill-ghidra`, which runs `Decompile.java ... out:<dir>` once for many
functions); `include/` headers declaring the classes involved; up to three
accepted functions most like this one (opcode-sequence similarity, class and
shared references) with their source; for a virtual method, what the
nearest registered super class holds at the same slot (an override's base
method, whose real name gives the override's); the decorated name accepted
callers already bound the function to; its family and why a stamp failed;
earlier attempts and deferrals, with the best earlier attempt's source as a
starting point for a second pass; and the cheat-sheet entries for the
function's features (EH, x87, switch).

### Scratch files

```cpp
struct Foo { int a; int b; int Get() const; };   // declarations and headers
int Helper(int);                                  // callees: declared only

// FUNCTION: 0x10A52420
int Foo::Get() const { return a + Helper(b); }
```

The file defines exactly one non-inline function, after its `// FUNCTION:`
line, and nothing follows it. Callees are declared, never defined: MSVC 7.1
inlines any small function whose body is in the file, even one defined after
its caller.

## Pairing and the rulers

The target function and everything it references carry the names
`symbols.txt` gives them (`FUN_10a52420`, `DAT_...`, or real names); a
compiled candidate uses MSVC decorated names. objdiff pairs by name, and its
relocation rulers cannot bridge that gap: under `functionRelocDiffs`
`name_address` or `data_value`, a correct function calling `FUN_10a00000`
differs from one calling `?Helper@@YAHH@Z`, and under `none` any callee
matches. Worse, every symbol MSVC puts in a COMDAT sits at offset 0 of its
own section, so the address half of `name_address` and `data_value` report a
wrong float literal as 100% when both objects define it (the self-test prints
this). And `report generate` scores a wrong callee at 100% unless
`objdiff.json` pins the ruler (see Integration).

So objdiff only aligns the instructions, and the checks are done by
`tools/agent/verify.py`:

1. A copy of the candidate's object is edited (`coff.py`): its function takes
   the target's name, MSVC's `$L` labels inside it (switch case labels and
   tables) become function+offset references as in delink's objects (objdiff
   would otherwise cut the function at the first label), and a boundary
   symbol ends each side at its code.
2. objdiff (`functionRelocDiffs=none`) aligns the rows and reports opcode and
   operand differences.
3. Each aligned row is compared byte for byte outside relocated fields; a
   relocation on one side only is a difference. `__except_list` is accepted
   against the exe's plain `fs:[0x0]` and against the split objects, which
   `tools/split.py` relocates against it.
4. Every relocation pair is resolved to target *addresses*:
   - **Code references** (callees, globals, imports): the candidate's symbol
     must be the one `symbols.txt` names at that address, either the same
     decorated name or a `Class::Method` name it demangles to. An address
     `symbols.txt` leaves unnamed gets a *provisional* name. Provisional names
     must be consistent within the function (one address, one name) and with
     `symbols.txt` and every accepted record; they are listed in the verdict
     and recorded for the lead.
   - **Data** the candidate defines (`__real@` floats, `??_C@` strings, const
     tables, static locals, EH tables) is compared by value with the target's
     bytes, recursively through its pointers. The EH handler, the function
     info, the unwind map and each unwind funclet are checked this way, so a
     wrong destructor fails.
5. Switch tables after the code are compared the same way, and must have the
   same size.

The target's bytes come from the exe in `orig/` when present, else from the
split objects. A function matches when no row differs and nothing else does;
the score is the share of clean rows, and it never reads 100.0 otherwise.

What the gate cannot know: if the target calls an unnamed function and the
candidate calls a name nothing else knows, the pairing is a naming claim, not
a proven identity. The claim fails as soon as either side gets a name
elsewhere (in `symbols.txt` or another accepted function), including when
the function owning that name is matched. `accept.py --strict-names` refuses
provisional names altogether; review them at integration.

### accept.py

On top of a match, `accept.py` runs a lint that refuses inline assembly,
`_emit`, `__declspec(naked)`, `goto`, codegen `#pragma`s (`optimize`,
`code_seg`, `auto_inline`, ...), pointer-plus-integer casts used to reach
fields, literal addresses inside the exe, and a missing or duplicate
`// FUNCTION:` line. It then writes `build/agent/accepted/<ADDR>.cpp` and a
record: the decorated name, the class, the function's region, its `.text$x`
ranges (EH handler and funclets), every binding with its status, the flags
and the attempt count. Accepting an already accepted function needs
`--replace`.

A function MSVC writes itself, a scalar deleting destructor (`??_G`), has
no definition to mark: its candidate is the file whose definition makes the
compiler emit it (the class's constructor or destructor, with the class
declaring `virtual ~C();` at slot 0), with the `// FUNCTION:` line moved to
the deleting destructor's address, accepted with `--symbol ??_GC@@UAEPAXI@Z`.
The record says `generated` and names that function (`with`, or `--with`);
integrate.py puts only the marker in that function's unit, which emits it.
In a vtable, the vector deleting destructor `??_E` is a weak external that
stands for `??_G`; the rulers follow it.

## One address, several names

The linker folds identical functions into one copy, so the game's source
called some addresses by several names: `::operator delete` and
`UObject::operator delete(void*, size_t)`, a 4-byte getter of two classes, a
one-byte `ret`. symbols.txt gives such an address its other names as
`type:alias` lines after its own:

    ??3@YAXPAX@Z = .text:0x10AD1DC0; // type:function size:0x12
    ??3UObject@@SAXPAXI@Z = .text:0x10AD1DC0; // type:alias

The split leaves aliases out, and every object is compiled through
`tools/cc.py`, which gives references to an alias (and a definition under
one) the address's own name: the gate and objdiff's report then pair them.
configure.py writes `build/<version>/aliases.json` from symbols.txt and
rebuilds the objects when it changes.

Aliases also keep an earlier match valid when a better name arrives. Native
classes' constructors were often matched as methods that store the vtable
by hand (`?FUN_x@C@@QAEPAV1@XZ`), before anything showed they were
constructors. Each class's InternalConstructor (`classes.txt`'s
`constructor:`) is written as Unreal writes it, so its jump target becomes
`??0T@@QAE@XZ`, and the method name stays on as an alias:

    enum EInternal { EC_Internal };
    inline void* operator new(unsigned int, EInternal* Mem) { return Mem; }

    void T::InternalConstructor(void* X) { new ((EInternal*)X) T(); }

The `EInternal*` overload has no matching placement delete, so `/GX` adds
no exception frame (the `void*` placement new from `<new>` adds one), and it
does not clash with `<new>` when both end up in one unit.

Unreal's templates are written as templates. Each `Cast<T>` the game keeps
is an explicit instantiation of Core.h's `Cast`, under the marker:

    // FUNCTION: 0x109E9FD0
    template AGarrett* Cast<AGarrett>(UObject* Src);

The instantiation is a COMDAT like the inline functions the file also
emits, so the gate picks it by the name symbols.txt gives the address
(`??$Cast@VAGarrett@@@@YAPAVAGarrett@@PAVUObject@@@Z`), or by try.py's
`--symbol` before the address has it.

try.py refuses a file byte-identical to an earlier attempt, counts only
attempts that compiled, and refuses the 13th attempt of a claim.

## Integration (lead)

`integrate.py` takes accepted functions (all pending by default, `--dry-run`
first) and puts each into a unit:

- `--unit`, else a declared `splits.txt` unit whose ranges hold it, else a
  unit named after its class: `Class::Method` goes to
  `src/<Category>/<Class>.cpp`; free functions and methods of placeholder
  classes (`Class_<address>`) to `src/<Category>/Unsorted_<start>.cpp`, one
  per auto unit of the split (one file for all would let MSVC inline small
  callees into their callers). A function whose class definitions clash with
  its unit's goes to `--unit <Category>/Unsorted_<start>_2.cpp`.
  The category is `--category`, else the function's in `categories.txt`,
  except that a method of an Unreal-style class (`UObject`, `AActor`,
  `FName`) counts as Epic's engine unless `classes.txt` has the class as Ion
  Storm's (`AGarrett`, `UT3GameEngine`). Library code (from the CRT entry
  point on, outside `.text$x`) is not published (CONTRIBUTING.md), so it is
  skipped unless `--category libs`; so is Epic's engine, unless `--category`
  is given (`game` once the class is known to be Ion Storm's).
- The unit file gets the accepted files' declarations, deduplicated, then the
  functions in address order, each behind `// FUNCTION: 0x<ADDR> <decorated
  name>`.
- The unit is compiled with its flags and **every function in it is checked
  again** with the same rulers. A function that matched alone can stop
  matching in its unit (an inline body now visible, a declaration that
  changes codegen); it is left out and reported. If a function already in the
  unit breaks, the unit is left unchanged and each new function is reported
  left out ("its unit breaks with it"). Units are checked in parallel, one
  per CPU (`--jobs`), and their changes merged in order afterwards;
  `--plan <json>` (`{unit: [address, ...]}`) places many functions in many
  units in one run, which is how the lead's overflow units for class clashes
  are filled.
- `splits.txt` gets the unit's `.text` ranges (each function with its switch
  tables; neighbours merge when only padding lies between them) and its
  `.text$x` ranges, and is checked with `tools/splits.py` (parse, overlaps, no
  range cutting through a function).
- `symbols.txt` gets the functions' decorated names and the names their
  bindings establish: callees and globals, `__real@`/`??_C@` literals, and
  `__ehhandler$` stubs. A real name is never replaced by a different one;
  conflicts are reported.
- The unit's progress category comes from `categories.txt` by address, so
  integrate.py records none; `progress_report.py check` fails if a function
  in `src/` is not game code there.

It runs under a lock (`build/agent/integrate.lock`). Afterwards: `python
configure.py && ninja`, compare the report with the previous one
(`objdiff-cli report changes`) and reject any regression, then run `python
tools/progress_report.py write` and commit `progress/` with the source: CI
publishes that report to decomp.dev ([decomp-dev.md](decomp-dev.md)).

The report should use the same code-reference ruler as the gate. With
objdiff 3.8.1, `report generate` on a function calling `?Other@@YAHH@Z`
where the target calls `?Helper@@YAHH@Z` gives 100% by default and 99.6% with
`"options": {"functionRelocDiffs": "name_address"}` in `objdiff.json`
(configure.py writes that file; the option is not set yet). Integration puts
the bound names into `symbols.txt`, so once the split is redone the target
objects use the same names as the compiled units and `name_address` holds
for integrated functions. A literal named `__real@...` in `symbols.txt` (an
external in the unit object) pairs with the unit's own COMDAT under that
setting.

Unwind funclets keep their `Unwind@` names: MSVC 7.1 calls them `$Lnnn`, a
number that changes whenever the file changes, so objdiff's report cannot
pair them by name and counts them as unmatched. The gate checks them through
their parent instead.

## Waves (lead)

The day-to-day setup is now the [agent workflow](agent-workflow.md):
batches of Sonnet sub-agents launched by the lead, with a one-file protocol.
The headless waves below remain for sessions that may start `claude -p`
workers.

```sh
python tools/agent/context.py fill-ghidra --next 200     # optional seeds
python tools/agent/wave.py --workers 8 --functions 5 --dry-run
python tools/agent/wave.py --workers 8 --functions 5 --budget-usd 5
```

Each worker is `claude -p` with `--model claude-sonnet-5`, `--output-format
json`, `--permission-mode dontAsk`, the guard settings and the
[t3-matcher](../.claude/agents/t3-matcher.md) instructions as an appended
system prompt, in a detached worktree of `HEAD` under
`build/agent/worktrees/`. Commit `tools/agent/` and `.claude/` first: the
worktrees are made from `HEAD`. The results go to
`build/agent/waves/<wave>.json`: each worker's exit status, `total_cost_usd`,
turns and final JSON summary (`matched`, `deferred`, `needs`, `idioms`), and
the totals, including the cost per match. Claims a worker left behind are
released.

After a wave: spot-check accepted functions and their provisional names,
integrate, provide what `needs` asks for (headers in `include/`, names in
`symbols.txt`), requeue deferred functions whose blocker is gone (`next.py
requeue`), and verify proposed idioms with the compiler before adding them
to the [cheat sheet](../.claude/skills/t3-match/CHEATSHEET.md).

## Guard rails

Workers get `tools/agent/guard-settings.json` through `--settings`. It is not
the project's `.claude/settings.json`, because the lead has to edit the files
it protects. It has two layers:

- permission rules: reads, writes under `build/scratch/`, and the four worker
  tools are allowed; writes to `config/`, `configure.py`, `objdiff.json`,
  `orig/`, split objects, `src/`, `include/`, the tools and `.claude/` are
  denied, and so are `git stash`, `reset`, `checkout`, `clean`, `push`, `commit`;
- a PreToolUse hook, `tools/agent/hooks/guard.py`, for what rules cannot
  express. Workers may write only under `build/scratch/` of their own
  checkout. Shell commands are refused when they change git history or
  discard work, pass `--no-verify`, delete recursively, run inline scripts
  (`python -c`, `bash -c`), use lead-only options (`integrate.py`,
  `wave.py`, `--cap`, `--replace`, `requeue`, `release --all`), override the
  `T3_AGENT_*` paths, or write a protected path through a redirection, `tee`,
  `sed -i`, `cp`, `mv`, `rm`, `touch`, `dd` or `ln`. Errors in the guard
  block the call.

wave.py writes the settings with the hook run by its own Python, from the
main checkout, by absolute path. It does not use `--bare`: that mode skips
hooks, including those given with `--settings`. The t3-matcher agent
definition carries the same hook in its frontmatter, so a worker the lead
spawns as a sub-agent is guarded too; that hook runs `python3`, which on
Windows must be a real interpreter (not the Store alias).

The rest is in the tools: claims, the attempt cap, refused duplicates, the
lint, a gate that recompiles instead of trusting try.py, and integration
that re-checks everything in context.

## Testing

`python tools/agent/selftest.py` (about ten seconds) needs the toolchain but
not the game. `tools/agent/fixture.py` compiles synthetic reference C++ with
the real compiler and reshapes it the way delink shapes the split:
addresses, placeholder names, `$L` labels folded, `__except_list`
relocations dropped, data moved to a `__shared_data` object. The tests run
the tools in that temporary project and check:

- exact matches are accepted: plain, float literal, switch, EH, string, and
  with `symbols.txt` names written as Ghidra would (`Foo::Get`), which pair
  with decorated names and are upgraded to them at integration;
- rejections: a different expression, a reordered switch, a wrong callee
  (named, known elsewhere, bound by another accepted function, two names for
  one address, a wrong destructor in the funclets), a wrong float, integer or
  string literal;
- the lint, refused duplicate and 13th attempts, and defer;
- claims under twelve concurrent workers, for fresh and for expired claims;
- integration: units, ranges, `.text$x`, names, a function left out when its
  unit breaks it, and a `splits.txt` that `tools/splits.py` still loads;
- the context packet and the queue order, the guard, wave.py's dry run, and
  compiling through configure.py's `build.ninja` rule.

## Checked against the real exe

The self-test cannot cover these, so they were checked on the real split:

- try.py, accept.py and integrate.py on four functions (`Window::GetParent`,
  `HasFlag`, `SetFlag`, `Options::Get`): each matched, a wrong field offset
  and a wrong operator were rejected, integration wrote the units, ranges
  (merged across padding) and names, and objdiff's report counts the four
  (58 bytes). This found one bug the self-test could not: objdiff gives
  section offsets, and a split object holds a whole auto unit per section,
  so rows now use offsets from the function's start.
- delink names the functions after `symbols.txt` and sizes them as it says;
  the functions of an auto unit share its `.text` section.
- next.py's queue over the full `symbols.txt`: about 17,800 functions,
  ordered by instruction features (iced-x86) in about 4 seconds.

- An EH function (`execLen`): its handler, function info and unwind funclet,
  which sits in another auto unit, are checked through the parent.
- Waves: a smoke wave (one worker) found that Windows looked `cl.exe` up
  from the worker's worktree; the first real wave (six Sonnet workers on the
  script natives) matched 32 functions for $21, about 66 cents a match, and
  its deferrals found the gate misreading function-pointer globals
  (`GNatives`). Workers stand in for what the headers lack (local types,
  subclasses to reach undeclared members); review accepted files before
  integrating.
- A function with a switch table (`FUN_10a85660`, a byte index table and a
  jump table) first scored 38.9 with instructions identical to the target's:
  delink labels the jump table (`jpt_...`, storage class `LABEL`) where the
  code ends, verify.py took that for the end boundary and added none, and
  objdiff, which does not end a function at a label, read the tables as rows.
  verify.py now adds the boundary unless the symbol there is not a label;
  `test_labelled_switch_table` reproduces the split's label.

## Not yet checked against the real exe

- The exe path of the data ruler on `__real@` constants (strings and EH
  tables are checked: `execBoolToString`, `execLen`).

## objdiff's report and the gate

The report under-counts what the gate matched in a few cases, to fix in how
the split objects are made rather than in the gate:

- A vtable a constructor or destructor stores: the compiled object
  references `??_7Class@@6B@`, the split object the label symbols.txt gives
  that address. integrate.py names the vtables of the functions it
  integrates, so the store pairs; a vtable the linker folded for several
  classes takes the others' names as aliases (see above).
- A static local: its guard (`?$S1@...`) and the `$E` function that
  registers its destructor are named only in their own object file.
- A reference into a named array at an offset, where the model gives the
  address a label of its own, or delink turns an unnamed one into
  `<section> + offset`, the case `tools/split.py` does not fold (below).

A switch no longer does: MSVC labels its cases and tables with static `$L`
symbols, which objdiff takes for the end of the function, and delink names
the same places `jpt_` and `$L_` labels. `tools/cc.py` and `tools/split.py`
both fold such labels into the function plus an offset
(`coff.Coff.fold_labels`), so both sides of a switch read the same; the gate
finds where the code ends from the references to the tables either way.

Nor does a reference inside a named data object: delink labels an address
the code uses inside a string or an array (`DAT_10e78901`, one past the
start of `"AGarrett"`) where the compiler writes the object plus an offset
(`&TEXT("AGarrett")[1]`). `tools/split.py` makes such a placeholder label,
when `symbols.txt` names and sizes the object around it, the object plus the
offset (`coff.Coff.fold_into`); an address `symbols.txt` names keeps its name.

## /Od units

A few functions were built without optimization: a frame (`push ebp; mov
ebp, esp`) even in a one-line method, `this` spilled to `[ebp-4]` and read
back at every use. `configure.py` lists their address ranges in
`UNIT_RANGES` with the unit each belongs to, and gives those units `/Od` in
place of `/O2` (`UNITS`): the gate compiles a candidate in such a range with
its unit's flags, so a worker writes them like any other function, and
integrate.py puts them in that unit. `splits.txt` declares only what `src/`
holds, as for any unit. 0x10BF7810 to 0x10BF7AD0 is one such file, broken
by one optimized function at 0x10BF7990, and 0x10BF8F00 another.
