# Tiered agent workflow

How the matching decompilation runs day to day: one lead model orchestrates
cheap and mid-tier Claude sub-agents, and a strict tool gate decides what
counts as a match. [matching.md](matching.md) describes the tools
(queue, context packets, try, accept, integrate) and their rulers; this page
describes the combination of agents on top of them and why each setting is
what it is, so the same setup can be reused for another decompilation.

The goal is the most matches per token. Every choice below was measured on
this project (pilot of 2026-09-29, numbers in [Why this
combination](#why-this-combination)).

## At a glance

| Role | Model | Takes | Prompt parameters |
|---|---|---|---|
| Lead | Opus | nothing from the queue: prepares, launches, sweeps, verifies, integrates | (the session) |
| Tier 1 | Haiku 4.5 | functions of at most 31 bytes | `FILTERS=--max-size 31 N=20 COUNT=4 CAP=5` |
| Tier 2 | Sonnet 5.5 | functions of 32 bytes or more | `FILTERS=--min-size 32 N=12 COUNT=2 CAP=8` |
| Second pass | Sonnet 5.5 | what tier 1 deferred | `FILTERS=--only-deferred N=<deferred> COUNT=1 CAP=8` |

At most six workers run at once. A worker's whole prompt is one line:

```
Read tools/agent/worker.md and follow it exactly. ID=h05 FILTERS=--max-size 31 N=20 COUNT=4 CAP=5
```

`ID` is the worker's id for claims and ledgers (`h01`, `h02`, ... for Haiku,
`s01`, ... for Sonnet, `t01`, ... for the second pass; never reused), `N` how
many functions it handles, `COUNT` how many it claims at a time, `CAP` its
attempts per function.

## Why this combination

Pilot on the queue head (easy first), counted by
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

## Workers are Agent-tool sub-agents

The lead launches workers with the Agent tool: `subagent_type: t3-matcher`,
`model: haiku` or `sonnet`, in the background. A notification arrives when
each finishes, and the lead refills its slot.

- The agent definition, [t3-matcher](../.claude/agents/t3-matcher.md), gives
  the tools (Read, Write, Edit, Glob, Grep, Bash), a default model and a
  PreToolUse hook that runs the guard. Its body tells workers to read the
  skill and the cheat sheet; the protocol replaces both.
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
- **Caps:** 5 attempts for tier 1 (fail fast, Sonnet picks it up), 8 for
  Sonnet, and defer at once on a systemic blocker.
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
   for the functions Sonnet will reach next:
   `python tools/agent/next.py list --min-size 97 --max-size 300 --limit 300`,
   then `python tools/agent/context.py fill-ghidra <addrs>`.
2. **Smoke test** after any change to the tools or the protocol: one worker,
   two functions, in the foreground; check the records (below), not the
   report.
3. **Keep six workers busy.** On each completion, launch the next worker for
   the band the tier rule gives, with a new id.
4. **Sweep each finished batch:** `python tools/agent/sweep.py <ids>`. It
   accepts the MATCHes a worker left unaccepted (not for functions the lead
   rejected or deferred), releases leftover claims and prints matches,
   deferrals, attempts and tokens per worker.
5. **Second pass** whenever tier-1 deferrals pile up: a Sonnet worker with
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
   - keep library code out: it is never published (CONTRIBUTING.md). The
     first session matched MFC's inline `CRect` constructor. List such
     functions, and inline-asm originals, in `build/agent/excluded.json`
     (address to reason), which the queue skips;
   - settle the parked name conflicts (see [Name conflicts](#name-conflicts)):
     `fixnames.py prepare` with the addresses excluded as name conflicts,
     `python configure.py && ninja`, `fixnames.py accept`;
   - integrate the accepted addresses minus library code
     (`integrate.py --dry-run` first). Free functions go to one unit per
     auto unit of the split (`Unsorted_<start>.cpp`), close to the game's
     own object files: with all of them in one file, MSVC inlined a small
     callee into callers the game had compiled apart from it;
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
  function, the most common source of name conflicts.

## Trust the records, not the reports

- A report's `matched` is a claim. `build/agent/accepted/` is the truth:
  a worker reported a MATCH that it never passed to accept.py (sweep.py
  now accepts such ledger entries).
- Tier-1 blocker notes are often wrong. All seven Haiku deferrals blamed
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
on a two-instruction stub. They are a few percent of tier 1's output.
The lead parks them in `excluded.json`, so no second pass spends tokens on
them, and fixes free functions in batches with
[fixnames.py](../tools/agent/fixnames.py): `fixnames.py prepare <addrs>`
gives each address its real name in symbols.txt and patches the callers'
declarations (their accepted sources and `src/` units), then, after
`configure.py && ninja` (the split must carry the new names),
`fixnames.py accept` re-accepts the callers, accepts the candidates and
lifts the exclusions. Methods and vtable slots are settled by hand. A `jmp` stub whose callee is a method is written as a method
call (the protocol says so), which avoids most of these.

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

Reusable as is: the roles and tiers, the shape of the protocol, the lead's
loop, sweep.py's accounting and the pilot method. To replace:

- the gate: a queue with atomic claims, a context packet, a try tool that
  compiles and diffs with strict reference checks, an accept tool with a
  lint against inline assembly and address casts, and integration that
  re-checks each function in its unit ([matching.md](matching.md));
- the agent definition: tools, default model, the guard hook;
- the protocol's tool lines and codegen section, for that compiler;
- the size bands, measured by a pilot.

The pilot: a smoke test first, then six workers on one size band, half on
each model. Their claims interleave, so both get functions of the same
difficulty. Compare matches, the first-try rate and input tokens per match
with sweep.py, and set the tier-1 band where the cheap model's first-try
rate falls off. Repeat it when the queue moves into larger functions: the
tiers here were measured up to 96 bytes.
