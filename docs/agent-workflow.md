# Agent workflow

How the matching decompilation runs day to day: one lead model orchestrates
batches of Sonnet sub-agents, and a strict tool gate decides what counts as a
match. [matching.md](matching.md) describes the tools
(queue, context packets, try, accept, integrate) and their rulers; this page
describes the combination of agents on top of them and why each setting is
what it is, so the same setup can be reused for another decompilation.

The goal is the most matches per token. The choices below were measured on
this project (pilots of 2026-09-29 and 2026-09-30, numbers in [Why this
combination](#why-this-combination)).

## At a glance

| Role | Model | Takes | Prompt parameters |
|---|---|---|---|
| Lead | Opus | nothing from the queue: prepares, launches, sweeps, verifies, integrates | (the session) |
| Head band | Sonnet 5.5 | the queue head: functions of at most 31 bytes | `FILTERS=--max-size 31 N=20 COUNT=4 CAP=5` |
| Main band | Sonnet 5.5 | functions of 32 bytes or more | `FILTERS=--min-size 32 N=10 COUNT=2 CAP=8` |
| Second pass | Sonnet 5.5 | deferrals whose blocker the lead removed | `FILTERS=--only-deferred N=<deferred> COUNT=1 CAP=8` |

Workers run in batches: as many at once as Claude Code allows (20 by
default; `CLAUDE_CODE_MAX_CONCURRENT_SUBAGENTS` raises it, set before the
session starts), and the lead launches the next one into each slot a worker
frees until the batch is done. A worker's whole prompt is one line:

```
Read tools/agent/worker.md and follow it exactly. ID=b05 FILTERS=--min-size 32 N=10 COUNT=2 CAP=8
```

`ID` is the worker's id for claims and ledgers, never reused: each batch
takes new prefixes (`h`, `s`, `t` were the Haiku pilot's; the first Sonnet
batch used `a01`... for the head band and `b01`... for the main band). `N` is
how many functions it handles, `COUNT` how many it claims at a time, `CAP` its
attempts per function. The bands keep a worker's claims alike: many tiny
functions with a low cap, or fewer larger ones with a higher cap.

## Why this combination

Since 2026-09-30 every worker runs Sonnet 5.5: on the user's experience with
the RAC1 decompilation (rac1-decomp's `match-worker` agent runs Sonnet on the
same kind of queue protocol), Sonnet costs less per match than Haiku once
Haiku's retries and the Sonnet passes over its failures count, and the table
below already shows it from 32 bytes on. The first Sonnet-only batch is in
[Sonnet batches](#sonnet-batches).

The Haiku pilot on the queue head (easy first), counted by
[sweep.py](../tools/agent/sweep.py) from the records and the workers'
transcripts. Tokens are input-side (input, cache writes and cache reads):
the transcripts under-count streamed output, which is small next to them.

| Band | Model | Matched | Input tokens per match |
|---|---|---|---|
| up to 31 bytes | Haiku | 201 of 202, 97% on the first try | about 43K |
| 32 to 96 bytes | Haiku | 12 of 26 | 927K |
| 32 to 96 bytes | Sonnet | 38 of 40 | 217K (393K counting one worker's 8M on an inline-asm function) |
| Haiku's deferrals | Sonnet | 12 of 14 | 129K on the first seven |

- Up to 31 bytes, Haiku matches nearly everything on the first attempt, and
  its tokens cost a fraction of Sonnet's.
- From 32 bytes, Sonnet uses fewer tokens per match than Haiku (Haiku
  spends its attempts on wrong structure) and leaves nothing behind, while
  every Haiku failure costs a Sonnet pass anyway. So Sonnet takes the band
  directly.
- Tier 1's deferrals are cheap for Sonnet: the first seven all matched on
  the first attempt.
- The cost sits in the tail: functions that cannot match (an inline-asm
  original) or need a class nobody has declared. One Sonnet worker spent 8
  million tokens on an inline-asm function, with side experiments outside
  try.py. The protocol now forbids those and says to defer asm-looking
  targets at once, and the lead excludes such functions from the queue.
- For comparison, a headless worker of the earlier waves (`wave.py`,
  `claude -p`) used about 2 million input tokens per match on the script
  natives (measured on one of its six workers): each request carried about
  63K tokens of Claude Code's default system prompt, every built-in tool and
  the user's CLAUDE.md files. A sub-agent of the `t3-matcher` type starts at
  about 12.6K.

## Sonnet batches

The first Sonnet-only batch (2026-09-30): 56 workers in two bands, 20 at a
time, after a smoke test. Counted by sweep.py; "priced" weighs cache reads at
0.1 and cache writes at 1.25 of uncached input, as billed.

| Band | Workers | Matched | First try | Input-side tokens per match | Priced |
|---|---|---|---|---|---|
| head, up to 31 bytes | 20 | 373 of 400 (93%) | 82% | 126K | 20K |
| main, 32 to 78 bytes | 36 | 259 of 360 (72%) | 56% | 479K | 71K |

Not a like-for-like comparison with the Haiku pilot above: the pilot took the
easiest head of the queue, this batch what was left of the tiny functions and
the next 360 larger ones, and most of its deferrals are functions no worker
could match:

- **Wrong callee names** (the largest group, most of the main band's): an
  early accepted jump wrapper records its callee as `void FUN_x()`, and every
  real caller then fails the name ruler although its bytes match (bindings of
  `this`, arguments or a return value the guess lacks). The global
  `operator delete` alone (`0x10AD1DC0`, recorded as a free function) blocked
  a dozen. They go to the lead's naming pass ([Name conflicts](#name-conflicts)).
- **Compiler-generated code** the queue still held: deleting destructors
  calling a sized delete (139 more were excluded mid-batch), adjustor thunks,
  a global object's initializer. The protocol now defers them at once.
- **Library code** inside game objects: STL instantiations without strings
  the classifier could see (`_Copy_opt`, `_Ufill`, `basic_string`).
- **Bad function bounds** in symbols.txt (a function split in two) and a few
  codegen puzzles (a `call; ret` MSVC turns into a tail jump, dead stack
  temporaries, registers kept across a call only for a callee in the same
  unit).

Lessons: exclude compiler-generated shapes and known library code before a
batch; settle name conflicts between batches, since each one blocks several
callers; and the claim must re-check the records after taking the lock
(next.py now does), or a worker can be handed a function another one has just
accepted.

### Swarms (2026-10-01)

Then a continuous swarm: 8 to 12 workers at once, later 16, each freed slot
refilled at once, with one to three Opus workers on functions of 80 bytes and
more (`FILTERS=--min-size 80 N=6 COUNT=1 CAP=10`). Three swarms, each drained
for a checkpoint (sweep, review, naming pass, integration), 109 workers in
all. "Priced" as above, plus output at 5x; Opus's higher price per token is
not included.

| Swarm | Band | Model | Workers | Matched | Priced per match |
|---|---|---|---|---|---|
| 1 | head, up to 31 bytes | Sonnet | 25 | 466 (97%) | 26K |
| 1 | main, 32 bytes and more | Sonnet | 10 | 81 (81%) | 105K |
| 1 | big, 80 bytes and more | Opus | 6 | 30 (83%) | 110K |
| 2 | head | Sonnet | 7 | 127 (91%) | 36K |
| 2 | main | Sonnet | 15 | 118 (79%) | 85K |
| 2 | big | Opus | 6 | 28 (78%) | 97K |
| 3 | head | Sonnet | 13 | 248 (97%) | 28K |
| 3 | main | Sonnet | 21 | 162 (81%) | 90K |
| 3 | big | Opus | 6 | 24 (67%) | 205K |

The lead adds what needs no model between swarms: a naming pass over the
name-blocked deferrals (each blocked function's candidate names its callee;
the old guess stays as an alias, so callers in `src/` keep matching), 66
InternalConstructor thunks rewritten from one template, and families of
byte-identical functions matched from one accepted member (68 wrappers
returning `Class_109081E0(DAT_x)`). Library and compiler-generated shapes the
workers recognize (STL `_Tidy`, `_Ufill`, `std::fill`, global initializers)
go to `excluded.json` as they report them.

## Workers are Agent-tool sub-agents

The lead launches workers with the Agent tool: `subagent_type: t3-matcher`,
`model: sonnet`, in the background, all of a batch's first workers in one
message. A notification arrives when each finishes, and the lead refills its
slot.

- The agent definition, [t3-matcher](../.claude/agents/t3-matcher.md), gives
  the tools (Read, Write, Edit, Glob, Grep, Bash), Sonnet as the default
  model and a PreToolUse hook that runs the guard. Its body only points to
  the protocol, like rac1-decomp's `match-worker`: an earlier body sent
  workers to the t3-match skill and cheat sheet, about 6K tokens each that the
  protocol replaces.
- Sub-agents run in the lead's checkout, not in worktrees. They see the
  lead's uncommitted headers and tool changes at once; claims keep them
  apart, and each writes only `build/scratch/<ADDR>/`.
- Headless `claude -p` workers are not used: besides their heavier context,
  the lead session's auto-mode classifier refuses to start
  `claude -p --permission-mode dontAsk` processes.

## The worker protocol

[tools/agent/worker.md](../tools/agent/worker.md) is the workers' whole
instruction set, about 2K tokens. Each part is there to save tokens or to
close a failure seen in the pilot:

- **One file, read once.** The lead's output tokens are the most expensive
  in the system; a one-line prompt of parameters costs the lead almost
  nothing, and the protocol is read by each worker as cheap input.
- **It replaces SKILL.md and CHEATSHEET.md** (about 6K tokens per worker)
  with the loop, the rules, the naming rules and the codegen idioms that
  matter, condensed.
- **`next.py claim --context --count COUNT`** claims and prints the context
  packets in one call.
- **One message per attempt:** Write `build/scratch/<ADDR>/vK.cpp`, then Bash
  `try.py ... && accept.py ...`, so a match is accepted in the same turn.
  The C++ goes through Write, not a heredoc: the guard parses whole Bash
  commands and refuses C++'s `->`, `>>` and apostrophes as redirections and
  quotes.
- **`T3_AGENT_ID=<ID>` on every call:** sub-agents share the lead's
  environment and do not keep variables between calls, and the claims need
  a per-worker id.
- **Handled means accepted or deferred; claim again until N.** A Haiku
  worker stopped after its first claim without that sentence.
- **Caps:** 5 attempts in the head band, 8 in the main band, and defer at
  once on a systemic blocker.
- **The final message is only the JSON line**, with at most three `needs`
  and `idioms` of 25 words: the reports land in the lead's context.
- **Plausible source only:** no variables named after registers, no data
  declared as a function to get its address, no `volatile` to keep a store,
  no invented class names. Each passed the byte gate in the first session
  and was rejected at review.
- **Compile only through try.py**, and defer at once when the target looks
  hand-written in asm.
- **The codegen section grows** with idioms the gate has verified (an
  accepted function shows them), for example `mov eax, ecx` meaning the
  method returns `this`, a float stored to memory being a plain `mov` of its
  bits, `extern void* DAT_x[];` for an address used as an immediate, a `bool`
  parameter behind `sete al; push eax`.

## The lead's loop

1. **Prepare.** `python tools/agent/next.py status`. Cache Ghidra decompiles
   for the functions the main band will reach:
   `python tools/agent/next.py list --min-size 32 --limit 450`, then
   `python tools/agent/context.py fill-ghidra <addrs>` (a few minutes).
2. **Smoke test** after any change to the tools or the protocol: one worker,
   two functions, in the foreground; check the records (below), not the
   report.
3. **Run the batch.** Launch as many workers as the limit allows in one
   message, mixing the bands; on each completion, launch the next worker of
   the batch with a new id.
4. **Sweep each finished batch:** `python tools/agent/sweep.py <ids>`. It
   accepts the MATCHes a worker left unaccepted (not for functions the lead
   rejected or deferred), releases leftover claims and prints matches,
   deferrals, attempts and tokens per worker.
5. **Second pass** once the lead has removed blockers (a header, a name):
   `next.py requeue` those deferrals, then workers with
   `FILTERS=--only-deferred`.
6. **Checkpoint every few batches.** Stop launching and let the running
   workers finish (re-splitting rewrites the target objects that try.py
   reads), then, in this order:
   - sweep the last workers;
   - review `build/agent/accepted/*.cpp`: grep for the hacks above
     (`volatile`, variables named after registers, `DAT_` declared as a
     function, `__fastcall` or a parameter named `ecx` standing in for
     `this`, casts of globals to class pointers, made-up class names) and
     read a sample. To reject a pending match, move its records to
     `build/agent/rejected/`, and the queue takes it again; or fix it and
     accept the fix with `accept.py --replace`. Rejecting one match can
     break the name bindings of others that share a global; move them
     together. A match already in `src/` has to be taken out of its unit by
     hand;
   - keep everything but the game's own code out: Epic's engine and library
     code are never published (CONTRIBUTING.md). The queue offers only what
     `config/<version>/categories.txt` calls game code (`tools/classify.py`
     writes it from evidence in the exe; rerun it when `symbols.txt` gains or
     moves functions), integrate.py skips the rest, and `progress_report.py
     check` fails on a function in `src/` outside it. What the evidence
     misses still reaches the queue: the first session matched MFC's inline
     `CRect` constructor. List such functions, and inline-asm originals, in
     `build/agent/excluded.json` (address to reason), which the queue skips;
   - settle the parked name conflicts (see [Name conflicts](#name-conflicts)):
     `fixnames.py prepare` with the addresses excluded as name conflicts,
     `python configure.py && ninja`, `fixnames.py accept`; the rest with a
     plan (`fixnames.py spec`), then `retry.py`;
   - integrate the accepted addresses (`integrate.py --dry-run` first). Free
     functions, and methods of classes known only by a placeholder name
     (`Class_<address>`), go to one unit per auto unit of the split
     (`Unsorted_<start>.cpp`, a chunk of up to 64 KB; the exe does not record
     its object files): with all of them in one file, MSVC inlined a small
     callee into callers the game had compiled apart from it, and with one
     file per placeholder class the tree held a file per function;
   - `python configure.py && ninja`, compare the objdiff report with the
     previous one and reject regressions, then
     `python tools/progress_report.py write`;
   - add verified idioms to the protocol, provide what `needs` asks for
     (headers, names), and requeue deferrals whose blocker is gone
     (`next.py requeue`);
   - commit only when the user says so.

## Matches without a model

The cheapest match is the one no worker makes. The lead's tools take the
patterns that need no judgement:

- `fixnames.py constants` finds every queued function whose whole code is
  `mov eax, imm; ret` (or `xor eax, eax; ret`), writes `int FUN_x() { return
  imm; }` for it, and excludes it from the queue until `fixnames.py accept`
  has put it through the gate. The first run matched 43 functions this way.
  Functions that return an address (a relocation) are left to the workers.
- A method that only stores an address at +0 and returns `this`
  (`mov eax, ecx; mov dword ptr [eax], offset DAT; ret`) is written from a
  template too: 27 of 30 went through the gate on the first run.
- Most of what is left under 32 bytes is a handful of shapes. At the end of
  the first session, of 2,625 queued tiny functions: 470 scalar deleting
  destructors (compiler-generated, excluded until the gate can match
  synthetic functions), 243 null-checked method calls on an argument
  (`if (p) p->F();`), 169 constructor-like functions (base call, vtable
  store, `return this`), 130 returns of a class by value, about 50 setters.
  Templating the non-synthetic ones is the next cheapest block of matches.
- The context packet lists the vtable slots that hold a function (tables in
  read-only data whose start the code uses as a constant), so workers
  declare virtual methods as virtual methods instead of guessing a free
  function, the most common source of name conflicts. Its references name
  the registered class whose vtable a constant is, and print the value of
  each float or double the code loads from an unnamed address, so a worker
  writes `0.01f` instead of guessing a global.
- A switch's jump table carries a label symbol in the split object, which
  objdiff does not treat as the end of a function: the gate bounds the
  target at the end of its code anyway, as it does the candidate.

## Trust the records, not the reports

- A report's `matched` is a claim. `build/agent/accepted/` is the truth:
  a worker reported a MATCH that it never passed to accept.py (sweep.py
  now accepts such ledger entries).
- Blocker notes are often wrong. All seven of the Haiku pilot's deferrals blamed
  register allocation, a calling convention or `mov eax, ecx`; the causes
  were a missing `return this;`, a call through a global object pointer
  and a double indirection.
- `idioms` in a report are leads: add one to the protocol only when an
  accepted function shows it.

## Name conflicts

A stub that only jumps to an unmatched function (`jmp FUN_x`) has to guess
`FUN_x`'s signature, usually `void FUN_x()`, and integration writes the
guess into symbols.txt. When `FUN_x` itself is matched later with its real
signature (an `int` return, `__stdcall` parameters, a method), the gate
rejects its name: such deferrals score 99.9 with no differing row, or 50
on a two-instruction stub. They are a few percent of the head band's output.
The lead parks them in `excluded.json`, so no second pass spends tokens on
them, and fixes free functions in batches with
[fixnames.py](../tools/agent/fixnames.py): `fixnames.py prepare <addrs>`
gives each address its real name in symbols.txt and patches the callers'
declarations (their accepted sources and `src/` units), then, after
`configure.py && ninja` (the split must carry the new names),
`fixnames.py accept` re-accepts the callers, accepts the candidates and
lifts the exclusions. A `jmp` stub whose callee is a method is written as a
method call (the protocol says so), which avoids most of these.

The first naming pass (2026-09-30) settled the rest by hand: 44 symbols got
their real names, the 32 accepted callers that had pinned the guesses were
rewritten (and `operator delete`'s 33), and 46 blocked functions matched.
The kinds it met, and their fixes:

- A **jump wrapper** (`void FUN_x() { FUN_y(); }`) is a method forwarding its
  arguments: a virtual override calling the base's implementation
  (`Super::Serialize(Ar)` at the same vtable slot), a member's assignment or
  destructor at offset 0, or a getter returning its callee's result. MSVC
  7.1 tail-jumps all of these, arguments included.
- A **base constructor or destructor** called as a free function: the class
  derives from the base and calls `this->Base::Base()`, or the base is an
  empty class at offset 0.
- A **return type** a tail call passes through (`return p->Virtual6();`), a
  `float` parameter written as `int` (`push 0` is `0.0f`), an argument pushed
  early for the next call rather than for the callee.
- A **global** recorded as `int` or `void*` that holds an object.
- A **function split in two** in symbols.txt: merge the entries.

[rename.py](../tools/agent/rename.py) renames a class everywhere (symbols.txt,
`src/`, records, scratch files); `--registered` gives every `Class_<vtable>`
its registered name from classes.txt. `fixnames.py spec <plan.json>` applies
a lead-written plan (symbols.txt renames, edits to the callers that bound the
old names, hand-written candidates) after checking every edit, and
`fixnames.py spec-accept` re-accepts the callers and retries the blocked
functions. [retry.py](../tools/agent/retry.py) re-checks every deferred
function's candidates after names change and accepts what matches now.

The linker folds identical small bodies (`mov eax, [ecx+4]; ret`, a 1-byte
`ret`, two classes' slot-0 virtuals, `operator delete` and `UObject`'s sized
one) into one address that callers name differently. Such an address gets
more names in symbols.txt (`type:alias`, with `fixnames.py spec`'s
`aliases`), and every object is compiled through
[tools/cc.py](../tools/cc.py), which gives references to an alias the
address's own name, so the gate and objdiff's report pair them
([matching.md](matching.md), "One address, several names").

Scalar deleting destructors (`??_G`) are compiler-generated: they match
from a class that declares `virtual ~C();` at slot 0, where the class's
vtable is emitted, never from a hand-written body (the queue excludes them).
After integrating, [dtors.py](../tools/agent/dtors.py) writes a plan for
every one whose class's vtable a function in `src/` emits: the class gets
its virtual destructor, the constructor is re-accepted, and the deleting
destructor is accepted as generated with it (`fixnames.py spec`,
`configure.py && ninja`, `fixnames.py spec-accept`, `integrate.py`). The
first run matched 19.

## Guard and permissions

- The guard ([hooks/guard.py](../tools/agent/hooks/guard.py)) keeps workers'
  writes to `build/scratch/` and refuses history-changing git commands,
  inline scripts and lead-only options. The agent definition declares it as
  a PreToolUse hook, but in the first session it never ran for sub-agents
  started with the Agent tool: a worker passed `--replace`, which the guard
  refuses when run by hand, and no transcript holds a guard message. Until
  the hook is wired in a way that reaches sub-agents, what keeps workers in
  bounds is the protocol, the session's permission mode, and the lead's
  audit at each checkpoint (`git status` outside `build/`); `--replace`
  still has to pass the whole gate.
- Changes to the guard are the user's to make: the lead session's
  classifier refuses them as self-modification. sweep.py refuses to run
  under a worker id; the guard's lead-only list does not name it yet.
- The editor's clangd diagnostics on `build/scratch/` files are noise: they
  know neither MSVC 7.1 nor the project's include paths.

## Porting to another project

Reusable as is: the roles and bands, the shape of the protocol, the lead's
loop, sweep.py's accounting and the pilot method. To replace:

- the gate: a queue with atomic claims, a context packet, a try tool that
  compiles and diffs with strict reference checks, an accept tool with a
  lint against inline assembly and address casts, and integration that
  re-checks each function in its unit ([matching.md](matching.md));
- the agent definition: tools, default model, the guard hook;
- the protocol's tool lines and codegen section, for that compiler;
- the size bands, measured by a pilot.

The pilot: a smoke test first, then a batch on the size bands. To compare
models, run half of a band's workers on each: their claims interleave, so
both get functions of the same difficulty. Compare matches, the first-try
rate and input tokens per match with sweep.py. Repeat it when the queue
moves into larger functions.
