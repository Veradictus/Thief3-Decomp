# Your first match

A walkthrough of the loop in [matching.md](../matching.md), from claiming a
function to accepting it, reading what each tool actually prints. It's the
same loop [`.claude/agents/t3-matcher.md`](../../.claude/agents/t3-matcher.md)
gives an automated worker; here it's explained for a person running it by
hand.

> [!NOTE]
> The matching harness is proven end to end only against the synthetic
> targets `tools/agent/selftest.py` builds (see [setup.md](setup.md)).
> `src/` and `include/` hold nothing but a `.gitkeep` so far, and nobody has
> yet taken a real function of the split `T3Main.exe` through this loop.
> Expect this page's first real use to turn up rough edges; if it does,
> that's worth reporting.

You need the compiled split from [setup.md](setup.md) (`configure.py` +
`ninja`) before any of `tools/agent/` will work: `try.py` and `context.py`
both read the target's instructions from the split object.

## Claim a function

```sh
python tools/agent/next.py claim
```

This prints a JSON claim: an `addr`, the `symbol` `symbols.txt` currently
has for it (often a placeholder like `FUN_10a52420`), its `size`,
`callees`, and `siblings` — already-accepted functions of the same class or
split unit, useful as a style guide. The queue is easy first, ordered by a
difficulty score built from the target's own instructions (roughly:
instruction count, plus weight for conditional branches, calls, switches,
an EH frame, and x87 instructions), falling back to plain size when that
scoring isn't available. It already leaves out EH unwind funclets, import
thunks, the library region after the CRT entry point, and anything already
accepted, integrated, deferred or claimed by someone else, so everything it
offers you is fair game. Add `--unit <name>` to stay within one split unit,
or `--max-size` to skip anything above a byte count.

A claim is exclusive but not permanent: it expires after two hours unless
renewed (which `try.py` does automatically on every attempt), so an
abandoned claim doesn't block the function forever. If the queue is empty,
`claim` reports `"empty": true` and exits non-zero: stop, or ask the lead
for more of the split (`--all-regions`, a wider `symbols.txt`, and so on).

## Read the context

```sh
python tools/agent/context.py <addr>
```

This prints everything [matching.md](../matching.md) says a worker needs,
skipping any section it can't fill:

- the name, demangled signature, size and split unit;
- the target's own instructions (from the split object, via objdiff);
- what the function references — every callee and global, flagged when
  unnamed, with any name another accepted function has already proposed for
  it;
- the cached Ghidra decompile, if one exists — a starting point, not the
  answer;
- `include/` headers that already declare the classes involved;
- up to three (`--similar N` for more) already-accepted functions ranked by
  opcode-sequence similarity, as a concrete style guide;
- earlier attempts or a previous deferral, if you're returning to this
  function;
- [`CHEATSHEET.md`](../../.claude/skills/t3-match/CHEATSHEET.md) entries
  whose tags match this function's features (`eh`, `fp`, `switch`,
  `thiscall`).

Add `--json` to get the same packet as structured data. The lead can run
`context.py fill-ghidra --next N` to pre-populate the Ghidra decompile cache
for the next N queued functions, so an ordinary `context.py` call never
needs a live Ghidra session.

## Write a candidate

Create `build/scratch/<ADDR>/v1.cpp` — the only place a worker writes to.
One non-inline function, after a `// FUNCTION: 0x<ADDR>` marker, and nothing
after it:

```cpp
struct Foo { int a; int b; int Get() const; };   // declarations and headers
int Helper(int);                                  // callees: declared only

// FUNCTION: 0x10A52420
int Foo::Get() const { return a + Helper(b); }
```

Declare callees; never define them. `/O2` inlines any small function whose
body is visible in the same file, even one written after its caller, which
would silently turn your `call` into inlined code the target doesn't have
(see [techniques.md](techniques.md)). Start from the target's instructions
and the Ghidra decompile, lean on the similar accepted functions the context
showed you for style, and keep every attempt in its own file (`v2.cpp`,
`v3.cpp`, …), so the best one survives even if you end up deferring.

## Try it

```sh
python tools/agent/try.py <addr> build/scratch/<ADDR>/v1.cpp
```

`try.py` compiles the file with the project's flags, aligns it against the
target with objdiff, and applies the same rulers `accept.py` will: a code
reference must be the symbol `symbols.txt` (or another accepted function)
actually names at that address, and a literal, table or EH structure is
compared by value, not by a lenient relocation match. The verdict:

- `ATTEMPT k/12` and a `score` — the share of matching rows. It's never
  exactly 100.0 unless every row is clean; treat anything less as a
  mismatch, not "close enough".
- The differing rows, one per line, target on the left and your candidate on
  the right: `~` the rows differ, `<` only the target has this row, `>` only
  your candidate does, `r` a wrong reference or wrong bytes. A `!` line under
  a row explains why.
- `problems`: differences outside the row-by-row diff — a switch table, an
  EH table, a name conflict.
- `provisional names`: callees or globals `symbols.txt` hasn't named yet,
  paired with whatever name you gave them. They're recorded so the lead can
  reconcile them with `symbols.txt` and every other accepted function; a
  later conflict fails the claim.

For example (continuing the `Foo::Get` sketch above — illustrative of the
format, not a captured run):

```
0x10A52420 Foo::Get
ATTEMPT 3/12   score 94.8   mismatch rows 2/19
~ 000a  add     eax, [ecx+0x4]                              | add     eax, [ecx+0x8]
  !     field offset differs
NO MATCH. Name the asm difference your next attempt targets before editing.
```

`BUILD FAILED` doesn't count as an attempt — fix the compile error and try
again. A file byte-identical to an earlier attempt is refused outright, and
"same compiled code as attempt N" means your last change didn't affect
codegen at all, so it burned nothing. Past the cap, the 13th attempt is
refused too: defer instead (below). Before writing each new version, state
in one line which specific difference it targets, and change one thing at a
time — with only 12 attempts, an undirected edit is an attempt wasted.

## Accept it

```sh
python tools/agent/accept.py <addr> build/scratch/<ADDR>/vN.cpp
```

`accept.py` doesn't trust `try.py`'s last result: it re-lints the file (no
inline assembly, `_emit`, `__declspec(naked)`, `goto`, codegen pragmas,
pointer-plus-offset casts, literal exe addresses, and exactly one
`// FUNCTION:` line) and re-compiles and re-verifies from scratch. On
success it writes the source and a record — the decorated name, class,
region, any EH ranges, every binding and its status, compiler flags, attempt
count — to `build/agent/accepted/<ADDR>.{cpp,json}`, releases your claim, and
prints `ACCEPTED`. Workers never write `src/` directly: the lead's
`integrate.py` folds accepted functions into a translation unit later (see
the Integration section of [matching.md](../matching.md)), re-checking the
whole unit before it lands.

`--strict-names` refuses to accept while any reference still relies on a
provisional name, if you'd rather wait for the lead to settle it first.
`--replace` is for redoing an already-accepted function; you won't need it
for a first match.

## Defer instead

Sometimes 12 honestly-targeted attempts still don't close the gap, or you
recognise a systemic blocker early: the same register or instruction-order
difference surviving several unrelated rewrites, a struct or vtable layout
you can't see, an unknown callee signature that changes the call sequence, a
naming conflict `try.py` flagged, or the target having inlined something
whose body you'd have to invent. Either way:

```sh
python tools/agent/accept.py defer <addr> "<one-line blocker>" --needs "<what would unblock it>"
```

This keeps your best attempt and the blocker for the lead, and releases the
claim. **Deferring is a successful outcome, not a failure** — an honest
blocker is worth more than a forced match, and `next.py requeue <addr>`
brings the function back once whatever it needed shows up.

## What not to do

`accept.py`'s lint exists because these have all been observed elsewhere as
ways to force a "match" that isn't real source (see
[research/llm-matching.md](../research/llm-matching.md)):

- inline assembly, `_emit`, `__declspec(naked)`, `goto`, or a codegen
  pragma (`optimize`, `code_seg`, …);
- a literal address inside the exe, or a pointer-plus-integer-offset cast in
  place of a declared struct field;
- defining a callee's body just to force it inline, or copying one function
  into another's file.

None of these are lint rules for their own sake — call a function the target
doesn't call, and the result is a wrong callee regardless of what objdiff's
percentage says. This project pins objdiff's relocation ruler
(`functionRelocDiffs: name_address`, see [decomp-dev.md](../decomp-dev.md))
specifically because a default, lenient ruler would show 100% for exactly
that mistake; `accept.py`'s own address-resolved rulers catch it independent
of that pin.

## How it reaches src/

A worker's job ends at `accept.py`; folding accepted functions into `src/`,
`splits.txt` and `symbols.txt`, and committing the result, is the lead's
`integrate.py`, covered in the Integration section of
[matching.md](../matching.md). It re-verifies every function in a unit
together (an accepted function can stop matching once another function's
declaration changes what the compiler inlines around it), so nothing you
did here is the last word until that step has run.
