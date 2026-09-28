---
name: t3-match
description: The per-function loop for matching T3Main.exe functions byte for byte with MSVC 7.1 through tools/agent (next, context, try, accept, defer), its rules, and how to read the verdicts. Use when matching, deferring or reviewing a queued function.
---

# Matching one T3Main.exe function

The goal is C++ that the original compiler (MSVC 13.10.3077, `/O2 /GX /GR-`)
turns into exactly the bytes of one function of `T3Main.exe`. The tools do
the compiling and judging; the source has to be plausible, readable C++ that
the game's programmers could have written. Background: `docs/matching.md`.

Run every tool from the checkout root as `python tools/agent/<tool>.py`.
Your worker id comes from `$T3_AGENT_ID` (wave.py sets it).

## The loop

1. **Claim.** `python tools/agent/next.py claim` prints JSON: `addr`,
   `symbol` (the symbols.txt name, often a placeholder like `FUN_10a52420`),
   `size`, `callees`, and `siblings` (accepted functions nearby). If
   `empty` is true, the queue is done: stop.
2. **Read the context.** `python tools/agent/context.py <addr>`: the target's
   instructions, what it references (unnamed ones flagged, with any name
   another accepted function proposed), the Ghidra decompile if cached, the
   headers for the classes involved, similar accepted functions with their
   source, earlier attempts, and the cheat-sheet entries that apply. Read
   `CHEATSHEET.md` in this folder once per session.
3. **Write a candidate** in `build/scratch/<ADDR>/v1.cpp` (your only writable
   place). Layout:

   ```cpp
   #include "..."            // project headers from include/, when they exist
   struct Foo { int a; int b; int Get() const; };   // what the function needs
   int Helper(int);          // callees: declared, never defined (see the cheat sheet)

   // FUNCTION: 0x10A52420
   int Foo::Get() const
   {
       return a + Helper(b);
   }
   ```

   Exactly one non-inline function is defined, after the `// FUNCTION:` line,
   and nothing follows it. Types and declarations you need but cannot find in
   `include/` go above it; list them under `needs` at the end so the lead can
   add real headers.
4. **Try.** `python tools/agent/try.py <addr> build/scratch/<ADDR>/vN.cpp`.
   Keep each version in a new file (`v2.cpp`, `v3.cpp`, ...), so the best one
   survives. The verdict:
   - `ATTEMPT k/12` and `score`, the share of matching rows. The score is
     never 100.0 unless everything matches; 99.9 is not a match.
   - the differing rows, target left and yours right: `~` differ,
     `<` only in the target, `>` only in yours, `r` a wrong reference or
     wrong bytes, with the reason on the `!` line below it;
   - `problems`: differences outside the rows (switch tables, EH tables,
     names);
   - `provisional names`: callees or globals symbols.txt has not named yet,
     paired with your names. They are recorded for the lead; a later
     conflict with symbols.txt or another accepted function rejects them.
   `BUILD FAILED` is not counted as an attempt; fix the error. A byte-identical
   file is refused, and "same compiled code as attempt N" means your change
   had no effect on the code. `CANNOT CHECK` means the split is missing or
   out of date: release the function (`python tools/agent/next.py release
   <addr>`), mention it under `needs`, and take the next one.
5. **Before every new version, write one line saying which asm difference
   it targets** ("the target constructs its second object at `[esp+0x8]`:
   swap the two declarations"). Change one thing at a time.
6. **Accept** as soon as try.py says MATCH:
   `python tools/agent/accept.py <addr> build/scratch/<ADDR>/vN.cpp`. It runs
   the lint and the strict comparison again and records the function for the
   lead. If it rejects, read why; the lint rules are below.
7. **Defer** after 12 attempts, or earlier on a systemic blocker:
   `python tools/agent/accept.py defer <addr> "<one line: what differs and why>" --needs "<what would unblock it>"`.
   The best attempt is kept. **Deferring is a successful outcome**: an honest
   blocker is worth more than a forced match.

Then claim the next function.

## Rules

- No `__asm`, `_emit`, `__declspec(naked)`, `goto`, `#pragma optimize` (or
  other codegen pragmas), no literal exe addresses, and no raw pointer
  arithmetic to reach fields (`*(int*)((char*)this + 0x10)`): declare the
  struct with the field at that offset. accept.py rejects all of these.
- Don't define callees; don't copy a function body just to make it inline.
- Don't make a call match by renaming things: calling a function the target
  does not call is a wrong callee, whatever the score says. When the target
  calls an unnamed `FUN_...`, give it the most plausible name and signature;
  it becomes a provisional name the lead reviews.
- Write only under `build/scratch/`. `config/`, `src/`, `include/`,
  `configure.py`, `objdiff.json`, `orig/`, the rest of `build/` and the tools
  belong to the lead, and the guard blocks writes there and history-changing
  git commands.
  Don't try to work around it; put what you need in `needs`.
- Don't raise the attempt cap or replace someone else's accepted function.

## Systemic blockers: recognise them, then defer

- The same register-allocation or instruction-order difference survives
  several unrelated rewrites.
- The difference comes from a struct layout or a class you cannot see (a
  field offset, a vtable slot, a base class): `needs` a header.
- A callee's return type or calling convention is unknown and changes the
  call sequence: `needs` its declaration.
- try.py reports a naming conflict with symbols.txt or an accepted function:
  `needs` the lead to settle the name.
- The context shows the target inlined something whose body you would have to
  invent.

## Final summary

End your run with one line of JSON, and nothing after it:

```json
{"agent": "w03", "matched": ["0x10A52420"], "deferred": [{"addr": "0x10A52440", "best": 87.5, "why": "register allocation in the loop"}], "needs": ["a header for Foo: the target reads fields at +0x30 and +0x34"], "idioms": ["x * 6 compiles to lea eax, [eax+eax*0x2]; shl eax, 0x1"]}
```

`needs` lists headers, layouts, names and declarations the lead should
provide; `idioms` lists codegen observations for the cheat sheet (the lead
verifies them before adding them).
