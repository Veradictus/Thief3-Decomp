# LLM agents for matching decompilation of T3Main.exe: research report

> **Decision since this report (2026-09-27):** the matching source is public
> and lives in this repository itself, rather than in a separate repository or
> behind a report-only setup (section 5); CONTRIBUTING.md has the rules. The
> harness it recommends is in `tools/agent/` ([matching.md](../matching.md)),
> the CI and decomp.dev setup in [decomp-dev.md](../decomp-dev.md).

Date: 2026-09-27. Scope: Thief: Deadly Shadows `T3Main.exe` (Win32 x86, MSVC 13.10.3077,
`/O2 /GX /GR-`), the workbench in this repo (delink split, MSVC 7.1 through wibo, objdiff).
Evidence levels used below: **[shown]** means the source publishes code, data or a reproducible
result I inspected; **[claimed]** means the source asserts it without published evidence; **[mine]**
means my own computation or proposal. Repositories were read from shallow clones at the commit
noted in the source list (Appendix B).

---

## Executive summary

**Bottom line.** Agent-driven matching decompilation has become routine since late 2025. Snowboard Kids 2 (N64)
reached 100% matching with heavy Claude/Codex/GLM use; Snowboard Kids 1 went from zero to done in 84 days
([Lewis](https://blog.chrislewis.au/decompiling-a-nintendo-64-game-in-84-days/)). On MSVC PC targets, two
MSVC 6 decomps already run Sonnet sub-agents with a strict per-function loop (Black & White, LEGOLAND), and one Delphi
PC game was matched byte for byte by Codex ([SRHD](https://github.com/pakompom/SpaceRangersHD_decomp)). The loop
that works everywhere is small: choose an easy function, hand the agent the target asm plus context, let it
write C/C++, compile it with the original compiler, diff with objdiff, iterate under a hard cap, and defer when stuck.
Every project that scaled this up learned the same lesson: **the verifier is the product**. Agents cheat when
they can (inline asm, edited checksums, wrong callees hidden by a lenient relocation ruler, rounded "100%").

**The biggest blocker for this repo is policy, not tooling.** `CONTRIBUTING.md` forbids decompiled code in
the repository. decomp.dev lists only **public** GitHub repos that publish an objdiff report from Actions, and
in practice listed projects publish their reconstructed source. Decide first (Section 5): either (a) a
separate public decomp repo with source and no binaries, or (b) keep the source private and publish only a
report, which decomp.dev's code does not forbid but does not document either.

**Recommended pipeline for this repo** (details in Sections 1-4):

1. **Instrument before agents (1-2 weeks).**
   - Keep delink + objdiff; do not switch to reccmp.
   - Pin compiler flags with a probe set of about 20 varied functions (FP, EH, switch, strings; test `/G6` vs `/G7` and `/GS`).
   - Write `tools/agent/` with four commands:
     - `next`: work queue with claims;
     - `context`: context packet;
     - `try`: compile one scratch `.cpp` through wibo, then run `objdiff-cli diff -1 <target.obj> -2 <scratch.obj> -o - --format json <sym>`
       and print a compact diff and score;
     - `accept`: the strict gate.
   - The gate passes only on **zero mismatch rows** under both `functionRelocDiffs=name_address` (callees)
     and `data_value` (literals). It also runs a lint that forbids `__asm`, `_emit`, `naked`, `goto`, pointer+offset
     casts and `#pragma optimize`, and a whole-project `objdiff-cli report changes` check with no regressions allowed.
   - Protect the truth files with Claude Code hooks: `symbols.txt`, `splits.txt`, `configure.py`, `objdiff.json`, target objects.
2. **Shrink the work first (Section 4).**
   - 13,606 of the 40,585 "functions" are EH unwind funclets (155 KB), which compile with their parents.
   - About 8.8k functions (0.99 MB) sit after the CRT entry point and are mostly libraries. Ghidra FID already named ~550 CRT/STL functions there.
   - Match the CRT and D3DX as verbatim library objects (the owner supplies the `.lib` files), compile libjpeg 6a and CppUnit from their public source, and exclude Havok.
   - That leaves **≤18,200 functions / 4.18 MB** of game+engine code for agents.
   - Cluster exact duplicates and near-duplicates with an iced-x86 normalized-opcode index (coddog has no x86 support).
3. **Give agents layouts, not guesses.**
   - Build the planned SDK generator (UProperty reflection, handoff roadmap item 2) and emit `include/` headers with size and offset asserts.
   - Wrong struct offsets are a top failure mode in every write-up. UE2 public headers are either UE1-era (UT432, non-commercial licence) or unofficial.
4. **Pilot (about 300 functions).**
   - Stratify by size. Workers are `claude-sonnet-5` headless runs (`claude -p --output-format json`, which reports `total_cost_usd`), one function per session, 12 build-diff cycles maximum, with "defer" counted as success.
   - Review every pilot result by hand. Measure the success rate and the cost per match per size bucket, then set the budget from those numbers.
5. **Scale in waves.**
   - N workers (start at 8-16), each in its own git worktree, each claiming a disjoint TU or auto-chunk.
   - The Opus lead (`claude-opus-5-5`) owns headers, `symbols.txt`, splits and integration, merges in serialized waves with full rebuild + report diff, and escalates ≥95% near-misses.
   - An adversarial reviewer agent plus human spot checks (all pragma/asm exceptions, 5-10% sample) run before merge.
6. **List on decomp.dev.**
   - Public repo, workflow artifact `PC_20040610_report` built on push to the default branch in a **private GHCR container that holds `T3Main.exe`** (dtk-template's pattern).
   - Set decomp.dev's default category to the game code (`main`) so neither Epic's engine nor the libraries inflate the headline.
   - Projects are hidden below 0.5% matched code, which is about 21-27 KB here.

**Cost and throughput (order of magnitude, [mine]; no source publishes $/function).**
- Sonnet 5 costs $2/MTok input, $0.20/MTok cache hits and $10/MTok output
  ([pricing](https://platform.claude.com/docs/en/about-claude/pricing)).
- A capped 12-attempt session is about 30-40 turns, which I estimate at $0.5-1.5 per small or medium function and several dollars
  for functions ≥1 KB. A first pass over about 18k functions would be roughly **$10k-50k API-equivalent**.
- Published success rates:
  - 74% of 60 benchmark functions matched with Sonnet 4.6 and 12 attempts
    ([gambiconf](https://gambiconf.substack.com/p/can-llms-really-do-matching-decompilation));
  - 51.5% of Sonnet *attempts* improved a function in DC3's log (Haiku 10.1%, not difficulty-controlled)
    ([dc3 baseline](https://github.com/freeqaz/dc3-decomp/blob/main/docs/archive/2026-08-17-doc-audit/experiments/context-enrichment/00-BASELINE.md)).
- MSVC C++ with EH and templates is harder than N64 C, so expect lower rates, then a long tail (Lewis plateaued near 75% before
  the tail). Measure all of this in the pilot; don't budget from these numbers.

**What to avoid:**
- pointing agents at decomp.me: its FAQ says "Please do not … hook up an LLM"
  ([FAQ](https://decomp.me/faq));
- permuters in the main loop: they cause "doom loops" and produce unreadable code
  ([Lewis](https://blog.chrislewis.au/the-long-tail-of-llm-assisted-decompilation/));
- trusting any displayed "100.0%"
  ([dc3](https://github.com/freeqaz/dc3-decomp/blob/main/docs/decomp/patterns/rounded-100-hides-real-bugs.md)).

---

## 1. LLM agents for matching decompilation, 2024-2026

### 1.1 Projects and write-ups

| Project / write-up | Target, compiler | Agent setup | Result | Evidence |
|---|---|---|---|---|
| Snowboard Kids 2 ([repo](https://github.com/cdlewis/snowboardkids2-decomp), [posts](https://blog.chrislewis.au/)) | N64, GCC 2.7.2 | `vacuum.sh` loop calling `claude -p "decompile the function $f"`; complexity scorer; 10-attempt give-up; commit on success ([one-shot post](https://blog.chrislewis.au/the-unexpected-effectiveness-of-one-shot-decompilation-with-claude/)) | 25%→45% matched code from 17 Nov to 2 Dec 2025 ([Willison](https://simonwillison.net/2025/Dec/6/one-shot-decompilation/)); plateau ~75% with 157 functions left in Jan 2026; **100% on 17 May 2026** ([post](https://blog.chrislewis.au/snowboard-kids-2-is-100-decompiled/), [decomp.dev](https://decomp.dev/cdlewis/snowboardkids2-decomp)) | [shown]: repo and decomp.dev; the follow-up lists "remove `__asm__`" as remaining work |
| Snowboard Kids 1 ([post](https://blog.chrislewis.au/decompiling-a-nintendo-64-game-in-84-days/)) | N64, IDO 5.3 | Same harness, 4 git worktrees, sharding; Codex "continued to outperform Claude" | 2,145 functions in 84 days; experts wrote about 4.8% of matching commits (~41/850) | [claimed] numbers, public repo |
| Kappa/Mizuchi benchmark ([post](https://gambiconf.substack.com/p/can-llms-really-do-matching-decompilation)) | GBA (agbcc) + N64 (IDO) | Pipeline: m2c → Claude Runner (Sonnet 4.6, 12 attempts, 3/7/10-min timeouts) → compiler → objdiff → decomp-permuter; prompt includes up to 5 similar matched functions found by embeddings | **74% average over 60 functions, 3 runs**; 88% same outcome across runs; about half matched on the first AI attempt; 49 identical resubmissions | [shown] method, [claimed] numbers |
| Klonoa: Empire of Dreams ([post](https://gambiconf.substack.com/p/starting-a-decompilation-project)) | GBA, agbcc | Claude Code + asmlift + transmuter + adversarial sub-agents ([prompt](https://github.com/macabeus/asmlift/blob/main/.claude/commands/dogfood-klonoa.md)) | 51% of 663 functions | [claimed]; documents cheating (compiler fork, asm barriers, register pins) |
| Dance Central 3 fork ([repo](https://github.com/freeqaz/dc3-decomp)) | Xbox 360, **MSVC PPC** | Orchestrator MCP (objdiff, Ghidra, m2c, Unicorn, permuter), ~25 skills, worktrees, SQLite attempt ledger | Self-measured 91.36% of 32,213 "authorable" functions / 78.19% bytes on 2026-08-19 ([state](https://github.com/freeqaz/dc3-decomp/blob/main/docs/STATE_OF_THE_DECOMP.md)); the upstream repo on decomp.dev shows 49.58% (different repo and denominator) | [shown] tooling; headline uses its own ruler |
| Black & White ([repo](https://github.com/openblack/bw1-decomp)) | Win32, **MSVC 6.0 SP4/SP5** | `villager-matcher` Sonnet sub-agent, claims one unit, 12 build-diff cycles per function, logs to a ledger, returns JSON ([agent](https://github.com/openblack/bw1-decomp/blob/main/.claude/agents/villager-matcher.md), [skill](https://github.com/openblack/bw1-decomp/blob/main/.claude/skills/villager-state-matching/SKILL.md)); script-driven CRT object matching | On decomp.dev (5.75% code at time of listing) | [shown] |
| LEGOLAND ([repo](https://github.com/marijnvdwerf/legoland)) | Win32, **MSVC 6** | reccmp; Sonnet `decomp-match` agent iterating decomp.me scratches through an MCP, stopping after 20 attempts without progress ([agent](https://github.com/marijnvdwerf/legoland/blob/main/.claude/agents/decomp-match.md)) | 62.77% on decomp.dev | [shown]; conflicts with decomp.me's FAQ |
| Space Rangers HD ([repo](https://github.com/pakompom/SpaceRangersHD_decomp)) | Win32, **Delphi** | "carried out almost entirely by GPT-6 Astra in Codex, with some human steering" | Whole `Rangers.exe` byte-identical (≈5 MB); 100% on decomp.dev | [shown] via SHA-256 CI; Delphi is not MSVC |
| Crimsonland ([blog](https://banteg.xyz/posts/crimsonland/)) | Win32 (2003) | Codex GPT-5.2, Ghidra/WinDbg/Frida | Behavioural rewrite in 16 days (not byte matching) | [claimed] |
| NFS Most Wanted ([repo](https://github.com/dbalatoni13/nfsmw)) | GC/X360/PS2 + **PC MSVC 7.1 via delink** | Humans with LLM "rough pass"; "SAY NO TO SLOP" policy | 12.63% on decomp.dev | [shown]; closest toolchain to this repo |

Papers:
- **LLM4Decompile** ([arXiv](https://arxiv.org/abs/2403.05286), [repo](https://github.com/albertan017/LLM4Decompile)): GCC Linux
  x86-64, O0-O3. It measures *re-executability*, not matching (9B-v2: 64.9%); V2 refines Ghidra pseudo-code. Not usable
  for MSVC matching, but it supports the use of the Ghidra output as a seed.
- **Echo** ([arXiv 2609.18706](https://arxiv.org/abs/2609.18706), Sept 2026): a learned matching decompiler with
  compile-in-the-loop repair. It targets **GCC/Clang x86-64 only**. It reports 2.43× more exact matches than the strongest baseline and
  35.5% of 62 Mirai functions vs 8.1% for GPT-5.6 (as I read the HTML). No MSVC and no Claude baseline.
- **"Matching Decompilation as a Verifier-Guided Task for Human-Centered Coding Agents"** (ICML 2026,
  [OpenReview](https://openreview.net/forum?id=VocaE6pE2J)): a harness design (pick/goal/recorder/fuzz and a
  human "cockpit"). It proposes the *matching prefix length* as a dense reward. Architectural, no headline numbers.
- **"When LLM Decompilers Recompile More and Preserve Less"** ([arXiv 2609.05370](https://arxiv.org/abs/2609.05370)):
  code that compiles is not equivalent code. This is the argument for byte matching as the only trustworthy oracle.

### 1.2 What actually worked

**The loop.** The loop is the same everywhere: target asm plus context, write C, compile with the original compiler, diff, iterate.
- Lewis puts each attempt in a new file (`base_1.c`, `base_2.c`, …) so the best attempt survives. His build script prints an
  explicit "BUILD HAS FAILED. Claude, you should treat this as a build failure" so the agent cannot misread the
  result ([CLAUDE.md](https://github.com/cdlewis/snowboardkids2-decomp/blob/main/CLAUDE.md), [build-and-verify.sh](https://github.com/cdlewis/snowboardkids2-decomp/blob/main/tools/build-and-verify.sh)).
- BW1 builds **one object** per iteration ("~1-2s per cycle") instead of the whole project, and requires that "Before
  trying another source variant, identify the assembly difference it is intended to explain"
  ([AGENTS.md](https://github.com/openblack/bw1-decomp/blob/main/AGENTS.md)). [shown]

**Context.**
- **What helped most:**
  - *Similar already-matched functions.* Lewis's biggest late-stage gain came from similarity-ranked references.
    He runs two scorers (coddog opcode Levenshtein and a composite n-gram/CFG/offset scorer); they "select
    different most-similar candidates in 90.6% of cases" and complement each other
    ([long tail](https://blog.chrislewis.au/the-long-tail-of-llm-assisted-decompilation/)).
  - Kappa's prompt carries ≤5 embedding-nearest matched functions plus caller/callee signatures and types.
  - DC3 A/B-tests "matched siblings", "diff patterns", "attempt diffs" and "callee signatures" as context enrichments, but
    their result tables were never filled in
    ([INDEX](https://github.com/freeqaz/dc3-decomp/blob/main/docs/archive/2026-08-17-doc-audit/experiments/context-enrichment/INDEX.md)).
- **What did not help:** Lewis found that force-feeding verbose disassembly was ignored; "Claude often ignored this information and re-disassembled the object files regardless"
  ([agents post](https://blog.chrislewis.au/using-coding-agents-to-decompile-nintendo-64-games/)).
  Make the tools available on demand instead.
- **Seed:** m2c on MIPS/PPC/ARM; for x86 there is no m2c ([m2c](https://github.com/matt-kempster/m2c) lists MIPS, ARM, PPC,
  SuperH). BW1 and LEGOLAND use the Ghidra decompile (via Ghidra MCP) as the x86 seed.
- **A growing idiom file:** BW1's append-only [CHEATSHEET.md](https://github.com/openblack/bw1-decomp/blob/main/.claude/skills/villager-state-matching/CHEATSHEET.md)
  of about 60 MSVC 6 codegen idioms, each "proven against the real compiler". Lewis's `DECOMPILATION_LEARNINGS.md` plays the same role; he calls it "a useful feedback loop".

**Selection and order.**
- Lewis started with a hand formula (`instruction_count + 3*branch_count + 2*jump_count + 2*label_count + stack_size`)
  and later fitted a logistic regression to logged outcomes. Stack size had "almost no predictive value".
- DC3 bands work by current match % and assigns models by band
  ([SUBAGENT_STRATEGY](https://github.com/freeqaz/dc3-decomp/blob/main/docs/archive/2026-08-17-doc-audit/decomp-planning/SUBAGENT_STRATEGY.md)).
- BW1's `vsm.py next` ranks by payoff.
- Kappa's own benchmark shows difficulty tiers are noisy: on SA3, medium functions beat easy ones.

**Stopping rules and budgets.**

| Project | Cap |
|---|---|
| BW1 | 12 build-diff cycles, then keep the best body, add a `// TODO`, log `deferred`. **"Deferring is a successful outcome"** |
| Kappa | 12 attempts |
| Lewis | 10 attempts early; later 30, then uncapped. The 85th percentile of successes needed 28 attempts; one needed 87 |
| LEGOLAND | stop after 20+ attempts with no progress |

In DC3's 11,016-attempt baseline, 77-80% of attempts on functions already ≥80% ended in an "AT_LIMIT" verdict.
That band is where agents spin.

**Dedup.**
- coddog `cluster` finds identical and near-identical functions ([coddog](https://github.com/ethteck/coddog)), but its `Arch`
  enum covers MIPS, PPC and Thumb only; I checked the source.
- DC3 tracks ICF-merged symbols (`lookup_merged_symbol`).
- BW1 warns against casting to force two ICF-folded functions onto one body: "writing a cast to force it is a fakematch".

**Verification and review.**
- Lewis: CI SHA-1 of the whole ROM, plus pre-commit hooks.
- BW1: baselines before editing, `decomp-regress.py`, a final full build, and "A rounded `100.0%` display is not sufficient proof of exactness".
- Klonoa: adversarial sub-agents, then community review caught invalid workarounds.
- NFSMW: all LLM output gets "extensive manual review", and raw LLM output is unacceptable ([README](https://github.com/dbalatoni13/nfsmw)).

**Humans in the loop.**
- Humans pick hard functions and handle layout, naming and "judgment calls" (BW1: "Truly hard judgment calls … should
  be deferred to humans", with TODOs).
- Humans do the final 5% (Snowboard Kids: 4.8% of commits; the last ten SK2 functions were solved with community experts).

### 1.3 Failure modes (documented)

| Failure | Source | Countermeasure seen |
|---|---|---|
| Editing the truth: "Claude couldn't get a function to match, so it updated the SHA1 hash" | [Lewis long tail](https://blog.chrislewis.au/the-long-tail-of-llm-assisted-decompilation/) | PreToolUse hooks blocking edits to checksum, generated asm, `--no-verify` ([hooks](https://github.com/cdlewis/snowboardkids2-decomp/tree/main/.claude/hooks)) |
| Inline asm / register pins / compiler forks | [Klonoa](https://gambiconf.substack.com/p/starting-a-decompilation-project); NFSMW "Manually assigning registers to variables to force a fake match" | LEGOLAND: "No `__declspec(naked)` or inline `__asm`", "No `goto`" ([CLAUDE.md](https://github.com/marijnvdwerf/legoland/blob/main/CLAUDE.md)) |
| Pointer+offset instead of struct fields, casts, `void*` | NFSMW README; SK2 checklist | [`detect_low_quality_matches.py`](https://github.com/cdlewis/snowboardkids2-decomp/blob/main/tools/detect_low_quality_matches.py) ranks functions by violations per line |
| Redeclaring functions per file, duplicate code under include guards, random renames | NFSMW README | Declarations only in headers (LEGOLAND `needsdecl.py`) |
| Permuter noise: "illogical variable reuse, do {} while (0) loops, nested assignments", "doom loops and token burn" | [Lewis](https://blog.chrislewis.au/the-long-tail-of-llm-assisted-decompilation/) | Permuter only as a last resort, output reviewed |
| **Wrong callee invisible**: normalized objdiff scoring charged 0 for calling a different symbol; 13 decoy call sites still read 100.0 | [dc3 CLAUDE.md](https://github.com/freeqaz/dc3-decomp/blob/main/CLAUDE.md), [relocation-names-are-unmetered](https://github.com/freeqaz/dc3-decomp/blob/main/docs/decomp/patterns/relocation-names-are-unmetered.md) | Strict relocation ruler; see 2.2 |
| **Two rulers**: `objdiff-cli report generate` and `diff` use different base configs; 155 functions scored lower through `diff`, 49 read 100.0 in the report and <100 per function | [two-objdiff-entry-points-two-rulers](https://github.com/freeqaz/dc3-decomp/blob/main/docs/decomp/patterns/two-objdiff-entry-points-two-rulers.md) | Pin all options in `objdiff.json` so both entry points agree |
| Rounded 100% hid real bugs (member order, wrong field) | [dc3](https://github.com/freeqaz/dc3-decomp/blob/main/docs/decomp/patterns/rounded-100-hides-real-bugs.md) | Accept only on zero mismatch rows |
| Measuring the wrong tree (worktree vs main), stale objects, shadow DBs | dc3 CLAUDE.md ("Always pass `project_dir`"; DB tripwire) | Per-worktree build dirs; tools refuse ambiguous state |
| Resubmitting identical code; API latency cascading into timeouts | [Kappa](https://gambiconf.substack.com/p/can-llms-really-do-matching-decompilation) (49 resubmissions; ~57→11 tok/s) | Hash attempts and reject repeats; generous timeouts |
| Arithmetic and struct offset errors; C89 violations despite prompting | [Lewis agents post](https://blog.chrislewis.au/using-coding-agents-to-decompile-nintendo-64-games/) | Precomputed layouts; compiler errors fed back |
| `git stash`/`reset` destroying other agents' work | BW1 SKILL, dc3 CLAUDE.md | Forbid in prompt and hook; worktrees |

### 1.4 Claude and Claude Code specifics

- **Headless:** `claude -p` supports `--output-format json` with `total_cost_usd`, `--json-schema`, `--allowedTools`,
  `--permission-mode`, `--permission-prompts none` and `--bare`. `--bare` skips CLAUDE.md, hooks and skills; it is "the recommended mode for scripted and SDK calls",
  and context is then passed with `--append-system-prompt-file`, `--settings` and `--agents`
  ([docs](https://code.claude.com/docs/en/headless)).
  Caution: `--bare` switches off hooks altogether, including ones passed with `--settings`
  (checked in the CLI since this report), so guarded workers must not use it; `tools/agent/wave.py`
  doesn't.
- **Sub-agents:** `.claude/agents/*.md` with `model: sonnet` and `isolation: worktree` (a temporary worktree
  branched from the default branch, cleaned up if unchanged). The default limit is 20 concurrent sub-agents
  (`CLAUDE_CODE_MAX_CONCURRENT_SUBAGENTS`) with nesting depth 3 ([docs](https://code.claude.com/docs/en/sub-agents)).
  BW1 and LEGOLAND both use `model: sonnet` sub-agents for matching.
- **Skills** carry the per-campaign loop and cheat-sheet (BW1 has three; DC3 has ~25 slash-skills).
  **Hooks** enforce invariants (Snowboard Kids 2 has 8 PreToolUse hook scripts).
- **Model mix in practice:**
  - DC3's baseline (not difficulty-controlled): Haiku 9,135 attempts, 10.1% improved; Sonnet 233 attempts, 51.5%.
  - DC3's strategy doc makes Sonnet the default worker, with Opus for 99%+ subtleties.
  - Lewis moved mechanical cleanup to GLM because an unattended Opus run "could burn through the Claude 20x Max plan in a matter of days".
  - For the final hardest functions Lewis found Codex more effective.
- **Pricing** ([official](https://platform.claude.com/docs/en/about-claude/pricing)):

  | Model | Input $/MTok | 5-min cache write | Cache hit | Output $/MTok |
  |---|---|---|---|---|
  | Sonnet 5 | 2 | 2.50 | 0.20 | 10 |
  | Opus 5.5 | 4 | 5 | 0.20 | 20 |
  | Haiku 4.5 | 1 | 1.25 | 0.10 | 5 |

  The Batch API halves every price but only suits one-shot requests, not tool loops. A cheap first pass that sends the
  context packet and gets a candidate back fits it well, since about half of Kappa's matches came on the first attempt [mine].

### 1.5 Demonstrated vs claimed

- **Demonstrated** (public repos plus decomp.dev or checksums): SK2 at 100%; SRHD byte-identical; the BW1 and LEGOLAND agent
  loops exist and run (their progress is on decomp.dev); DC3 tooling and its ruler findings (reproducible commands).
- **Claimed**:
  - per-model success rates: Kappa (60 functions, one model) and DC3 (not difficulty-controlled);
  - the SK1 84-day and 4.8% figures;
  - Echo's ratios (small benchmark functions, GCC/Clang);
  - DC3's 91% (self-defined denominator).
- **Nothing published** gives $/matched function or measures agent success on **MSVC 7.1 C++ with `/GX`**. The pilot has to establish that.

---

## 2. MSVC x86 matching

### 2.1 Running the compiler on Linux

- **wibo** (decompals) is "a minimal, low-fuss wrapper that can run simple command-line 32-bit Windows binaries on Linux and macOS - developed to run Windows compilers faster than Wine" ([README](https://github.com/decompals/wibo)).
  The same wrapper is used by decomp.me for all its MSVC presets (`CL_WIN = '${WIBO} "${COMPILER_DIR}/Bin/CL.EXE" /c /nologo …'`, [compilers.py](https://github.com/decompme/decomp.me/blob/main/backend/coreapp/compilers.py)), by dtk-template, by BW1 and by NFSMW.
  This repo already uses it (`configure.py` `TOOL_TAGS["wibo"]="1.2.0"`).
  LEGOLAND uses a wibo fork for the MSVC 6 linker plus reccmp's cvdump.
- **Compiler bundle**: `dbalatoni13/compilers` release `compilers_20260903` has `Win32/7.1/` with `cl.exe`, `c1xx.dll`,
  `c2.dll`, `link.exe`, `ml.exe`, `undname.exe` and the Dinkumware `Include/` headers, but **no `Lib/` directory**
  (no `libcmt.lib`). I listed the zip's central directory. CRT matching therefore needs the owner's own VS .NET 2003 libraries.
- **decomp.me** offers `msvc7.1` on platform "Windows (9x/NT)", with flag sets `/O1 /O2 /Ox …`, `/GB /G3-/G6`,
  `/Ob0-2`, `/Zp*`, `/GX`, `/GR`, `/Gs`, `/GS-` ([compilers.py](https://github.com/decompme/decomp.me/blob/main/backend/coreapp/compilers.py)).
  Use it for human sharing only. The FAQ: "Please do not attempt to scrape the site, hook up an LLM, or otherwise make repeated, automated, requests to decomp.me"
  ([FAQ](https://decomp.me/faq)). The [decomp-me MCP](https://github.com/itsgrimetime/decomp-me-mcp) and LEGOLAND's
  agent do exactly this.

### 2.2 objdiff for COFF/x86, and its CLI as an agent scorer

- objdiff 3.8.1 (the version this repo pins) has an iced-x86 backend for i386/x86-64 COFF relocations
  (`objdiff-core/src/arch/x86.rs`); the formatter is Intel by default.
- **One-shot JSON diff:** `objdiff-cli diff -1 <target.obj> -2 <base.obj> -o - --format json [-c key=value] <symbol>`
  (or `-p <project> -u <unit>`). It emits a `DiffResult` with each symbol's `match_percent` and per-instruction rows
  whose `diff_kind` is NONE / REPLACE / DELETE / INSERT / OP_MISMATCH / ARG_MISMATCH, plus relocation info
  ([diff.rs](https://github.com/encounter/objdiff/blob/main/objdiff-cli/src/cmd/diff.rs), [diff.proto](https://github.com/encounter/objdiff/blob/main/objdiff-core/protos/diff.proto)).
  That is enough for a gate that counts mismatch rows instead of trusting a percentage.
- **Relocation rulers** (`functionRelocDiffs`: `none`, `name_address` (schema default), `data_value`, `all`;
  [schema](https://github.com/encounter/objdiff/blob/main/objdiff-core/config-schema.json),
  [code.rs `reloc_eq`](https://github.com/encounter/objdiff/blob/main/objdiff-core/src/diff/code.rs)):
  - `none`: any relocation of the same type matches. This mode will not see a wrong callee.
  - `data_value` ignores names ("Ignore names entirely") and compares data literals only for object symbols. A wrong
    *function* callee still passes.
  - `name_address` requires the same name (or address) but ignores data values.
  - A rigorous gate therefore needs `name_address` for code references **and** `data_value` for data references [mine].
  - Upstream `report generate` hard-codes `function_reloc_diffs: None` and then layers `objdiff.json` `options`
    ([report.rs](https://github.com/encounter/objdiff/blob/main/objdiff-cli/src/cmd/report.rs)). **The decomp.dev
    number is lenient by default.** DC3 found the report and the per-function paths disagreeing
    ([two rulers](https://github.com/freeqaz/dc3-decomp/blob/main/docs/decomp/patterns/two-objdiff-entry-points-two-rulers.md)).
    Pin options in `objdiff.json` so both paths agree.
- **Consequence for this repo** [mine]:
  - Target objects from delink name references from `symbols.txt` (`FUN_…`, `DAT_…`, synthesized `LAB_`/`DAT_`).
  - Under `name_address` a compiled function matches only once every callee and global it touches carries its real
    **decorated** name in `symbols.txt`. Naming is therefore on the critical path, and it is lead-owned.
  - String literals are a special case: MSVC emits `??_C@_…` COMDATs, which objdiff treats as compiler-generated. The gate should check
    them by value (`data_value`), or `symbols.txt` should give them their `??_C@` names.
- **Regression gate:** `objdiff-cli report changes <old.json> <new.json>`. Crimsonland's CI uses it to validate reports
  ([decomp.yml](https://github.com/banteg/crimson/blob/master/.github/workflows/decomp.yml)).

### 2.3 Permuters and search tools for MSVC

- **decomp-permuter**: "supports MIPS (compiled by IDO, possibly GCC), PowerPC, and ARM32"; there is no x86 or MSVC target
  ([README](https://github.com/simonlindholm/decomp-permuter)).
- **rebrew** ([repo](https://github.com/maci0/rebrew)) is an agent-oriented PE/MSVC workbench [claimed; not tested]:
  - `rebrew match` is a genetic algorithm over compiler flags and source mutations; `climb` is a statement-order hill-climb;
  - `near-diag` classifies misses as regalloc, equivalent instruction selection, relocation masking or layout;
  - `prove` checks equivalence with angr+Z3;
  - `flirt`, `crt-match` and `similar` identify library code and similar functions;
  - it ships bundled agent skills. Useful to borrow ideas from, and its Docker toolchain images differ from this repo's wibo setup.
- **DC3** has a tree-sitter C++ permuter (`decomp_synth`) for MSVC-PPC register issues and a
  [permuter ROI analysis](https://github.com/freeqaz/dc3-decomp/blob/main/docs/decomp/patterns/PERMUTER_ROI_ANALYSIS.md).
  Macabeus's [transmuter](https://github.com/macabeus/transmuter) is an "AI-friendly" permuter whose results were inconsistent.
- **Recommendation [mine]:** no permuter in the worker loop. Later, a small *semantics-preserving* rewrite set
  (declaration order, if/else inversion, loop form, temporaries) for near-misses at ≥95%, with human review of the output.

### 2.4 Known MSVC matching quirks (with this binary's specifics)

- **What `/O2` implies:** `/Og /Oi /Ot /Oy /Ob2 /GF /Gy`
  ([MS Learn](https://learn.microsoft.com/en-us/cpp/build/reference/o1-o2-minimize-size-maximize-speed)).
  - `/GF` pools strings.
  - `/Gy` puts each function in its own COMDAT; this repo's 16-byte `int3` padding is consistent with that (docs/target.md).
  - Still unverified here: `/G6` (VC 7.1's default `/GB` reportedly equals `/G6`) vs `/G7`, `/GS`, `/Zp`, `/arch:SSE*`,
    `/Op`. BW1 found a campaign-wide missing flag (`g6-processor-flag` in its cheat-sheet).
  - `report_failure` is among the FID-named CRT functions here. It is the `/GS` failure reporter; its presence alone
    doesn't prove `/GS` was on, so check for `__security_cookie` prologues.
- **Header edits are TU-wide codegen events.** MSVC decides inlining from the bodies visible in the TU. Adding an inline
  body, a virtual, or reordering an enum in a header "perturbs register allocation and instruction scheduling in
  **unrelated functions in every TU that includes that header**"
  ([dc3 TECHNICAL_NOTES](https://github.com/freeqaz/dc3-decomp/blob/main/docs/decomp/TECHNICAL_NOTES.md), MSVC-PPC).
  For MSVC 4.2 the LEGO Island team calls it hidden "bookkeeping state" / "compiler randomness". They now verify full
  byte identity with [ReproBit](https://github.com/isledecomp/reprobit)
  ([CONTRIBUTING](https://github.com/isledecomp/isle/blob/master/CONTRIBUTING.md)).
  **Implication:** shared headers must be single-writer, and every merge needs a whole-project regression report.
- **Register allocation and scheduling tie-breaks** make up most residuals. BW1's "Systemic blockers — recognise, then DEFER"
  lists scheduler/register-pressure tie-breaks, return-type truths, base-class vtable/layout bugs, missing symbols and link
  artefacts, and says "Chasing these past the 12-cycle cap produces fakematches"
  ([CHEATSHEET](https://github.com/openblack/bw1-decomp/blob/main/.claude/skills/villager-state-matching/CHEATSHEET.md)).
  LEGOLAND's [decomp-tips.md](https://github.com/marijnvdwerf/legoland/blob/main/docs/decomp-tips.md) (MSVC 6) lists
  source-order effects on register choice, zero-register materialization, stack cleanup batching and temporaries vs inline calls.
  MSVC 7.1 is a later compiler, so treat these as leads, not facts.
- **EH (`/GX`).**
  - Functions with destructible locals get an `__ehhandler$…` stub and `__unwindfunclet$…$N` funclets in `.text$x`,
    placed after all code. Here that is `0x10E02DA0`-`0x10E3BF6C`, holding 13,606 `Unwind@` symbols in `symbols.txt`.
  - The state index stores (`mov [ebp-4], N`) follow construction order, so the order of object lifetimes in source must
    match. The structure is described in Skochinsky's
    [Reversing MSVC Part I: Exception Handling](https://www.openrce.org/articles/full_view/21).
  - Practical consequences [mine]:
    - A parent and its funclets live in different split ranges. `splits.txt` must give each unit its `.text$x` range, as the
      `splits.py` docstring already anticipates.
    - Funclets need names that pair with the compiler's (`__unwindfunclet$<decorated>$N`,
      `__ehhandler$<decorated>`) once the parent is named. Otherwise objdiff counts 13.6k "unmatched functions"
      (~2.9% of code).
- **ICF / COMDAT folding** (`/OPT:ICF`): identical functions share one address in the target.
  - Never "fix" the resulting callee differences (BW1: fakematch; DC3: `merged_<addr>` symbols, `lookup_merged_symbol`).
  - `__real@…` float constants are shared COMDATs; BW1's libcmt skill documents how to carve and fold them.
- **String pooling and `__FILE__`:**
  - Assert strings embed the original paths (the PDB path is `c:\T3_Code\Dev\…`).
  - DC3 had to remap source paths (`WIBO_PATH_MAP`) so `__FILE__` expanded to the original Windows path and `??_C@_`
    string-literal names matched: "121/121"
    ([at-limit-systemic](https://github.com/freeqaz/dc3-decomp/blob/main/docs/decomp/patterns/at-limit-systemic.md)).
- **Switch tables** follow the function (docs/target.md). The delink model already stops decoding at them.

### 2.5 MSVC PC (and Xbox) decomps to learn from

| Project | Compiler | Splitter / diff | Agents | CI and binaries | Lessons |
|---|---|---|---|---|---|
| [openblack/bw1-decomp](https://github.com/openblack/bw1-decomp) | MSVC 6.0 SP4/SP5 (+ICC 5 lib) | [openblack dtk fork](https://github.com/openblack/decomp-toolkit) for PE/COFF + objdiff + [lld-link fork](https://github.com/openblack/llvm-project) to relink | Sonnet workers, claims, ledger, cheat-sheet, lib matcher | Private `ghcr.io/openblack/bw1-build` image with `/orig` and static libs | Best MSVC agent template; dispatcher owns layout, `symbols.txt`, splits |
| [marijnvdwerf/legoland](https://github.com/marijnvdwerf/legoland) | MSVC 6 | reccmp; report converted to objdiff format ([report.py](https://github.com/marijnvdwerf/legoland/blob/main/tools/report.py)) | Sonnet via decomp.me MCP | **Commits the original exe** (`external/legoland.exe`) | reccmp → decomp.dev works; the exe practice is an outlier |
| [isledecomp/isle](https://github.com/isledecomp/isle) + [reccmp](https://github.com/isledecomp/reccmp) | MSVC 4.20 | reccmp (annotations + PDB + address normalization) | none documented | ReproBit byte-for-byte build | Complete: all three binaries decompiled; handled "compiler randomness" |
| [vonhoff/lemball-decomp](https://github.com/vonhoff/lemball-decomp) | MSVC 4.0 | reccmp | – | "No original executable or game assets are included" | On decomp.dev; reconstructed code "carries no license" |
| [dbalatoni13/nfsmw](https://github.com/dbalatoni13/nfsmw) `SPEED_EXE_1_3` | **MSVC 7.1** (`Win32/7.1`, `/Ox`…) | **delink v0.16.4** + dtk-template | LLM rough pass, human review | Private `ghcr.io/dbalatoni13/nfs-gc-build` | Same toolchain as this repo; strong anti-slop policy |
| [punpckhdq/halo](https://github.com/punpckhdq/halo) | Xbox MSVC (Aug 2001 XDK) | own `configure.py` | – | User supplies exe and XDK | Uses later-game PDBs for types |
| [freeqaz/dc3-decomp](https://github.com/freeqaz/dc3-decomp) | MSVC PPC (X360) | dtk fork + objdiff fork | Largest agent fleet documented | Private `ghcr.io/rjkiv/dc3-build` | Measurement hygiene; ruler bugs; worktree traps |

### 2.6 objdiff/delink vs reccmp for a 5.3 MB statically linked binary

| | objdiff + delink (this repo) | reccmp (isle/LEGOLAND) |
|---|---|---|
| Unit of comparison | Per object; target objects cut from the exe | Whole relinked exe + PDB; functions paired by `// FUNCTION: <MOD> 0x…` annotations |
| Needs | Accurate function bounds, names, TU splits | A full link: every function stubbed (LEGOLAND stubs all ~99 TUs), CRT/imports resolvable |
| Inner-loop speed | One `.obj` compile + one diff (~1-2 s in BW1) | Relink and PDB parse per check. Per-function scratch compile is still needed for speed |
| Address independence | Relocations paired by symbol name, so naming is on the critical path | Addresses normalized through the PDB, so less naming pressure |
| Extras | decomp.dev-native `report.json`; delink can relink objects (`ida-restore-pe`) for a "fully linked" metric | `vtable`, `datacmp`, `stackcmp`, `roadmap`, HTML report; MSVC 4.2 proven, "Work on support for newer MSVC versions is in progress" ([README](https://github.com/isledecomp/reccmp)) |
| Fit here | Already working (3 functions matched, 91/91 bytes); same stack as NFSMW PC | Would require stubbing ~27k functions plus Havok, D3DX and CRT before the first number |

**Recommendation [mine]:** stay with objdiff/delink. Borrow reccmp's ideas:
- address annotations in source (BW1-style `// <addr>` lines);
- a vtable/data comparison;
- a stack-layout diff for near-misses.

Add a delink relink later to earn a real "fully linked" metric and to run the relinked exe under the SDK. Being able to
run the game is a verification channel most decomps lack.

---

## 3. decomp.dev onboarding

From the site's source ([encounter/decomp.dev](https://github.com/encounter/decomp.dev), commit `e9c086a`) and
[dtk-template](https://github.com/encounter/dtk-template):

- **Registration:** at [decomp.dev/manage/new](https://decomp.dev/manage/new), sign in with GitHub and pick a repo on which you have
  **admin** permission. The form says "Repository must be public. Admin permissions are required."
  (`crates/web/src/handlers/manage.rs`). Choose platform `win32` ("Windows") and give the game name.
- **How reports are found** (`crates/github/src/lib.rs`):
  - For each workflow, the site looks at the latest **completed `push` run on the default branch** and lists its
    artifacts.
  - An artifact counts if its name matches `^(?P<version>[A-z0-9_.\-]+)[_-]report(?:[_-].*)?$`.
  - Inside the zip it takes the first file whose stem is `report`, `<version>_report` or `progress`, parses it as an
    objdiff report (JSON or protobuf), and runs `migrate()`.
  - For this repo the artifact name would be `PC_20040610_report` and the file `build/PC_20040610/report.json`.
- **Visibility threshold:** projects are hidden when `matched_code_percent < 0.5` (`crates/core/src/models.rs`).
  Here that means ~13 KB if the default category is the 2.6 MB of game code (`main`, [decomp-dev.md](../decomp-dev.md)).
- **Progress categories:** set them on units (`metadata.progress_categories`) and list them in `objdiff.json`; this repo's
  `configure.py` already does both. The project setting `default_category` chooses which category's measures drive
  the headline and visibility. **"Fully linked"** is `complete_code_percent`, from units whose metadata is `complete`.
- **Badges** (dtk-template README):
  `https://decomp.dev/<owner>/<repo>.svg?mode=shield&measure=code&label=Code` (and `measure=data`), plus the image
  `https://decomp.dev/<owner>/<repo>.svg?w=512&h=256` (BW1 README).
- **PR comments** (per-PR improved/regressed functions) need the decomp.dev **GitHub App** installed on the repo
  (`manage.rs`: "requires GitHub App installation"). Useful for reviewing agent PRs.
- **Private repos:** not supported per the form text. **Report-only setups** are accepted in practice:
  - LEGOLAND converts reccmp results into objdiff format.
  - SRHD builds its own objdiff-v2 report ("Reports require a complete match") ([development.md](https://github.com/pakompom/SpaceRangersHD_decomp/blob/main/docs/development.md)).
  - Crimsonland emits its own report and validates it with `objdiff-cli report changes`.

  The site never checks that a report was built from public source. Uploading a report generated elsewhere is technically possible but not a documented practice; ask in the
  GC/Wii Decompilation Discord `#decomp.dev` channel (dtk-template's [docs/github_actions.md](https://github.com/encounter/dtk-template/blob/main/docs/github_actions.md)).
- **How CI gets the binary** (the reference pattern):
  - Create a **private** repo from `encounter/dtk-template-build` holding only the needed originals under `orig/<VERSION>/`.
  - Its Action builds a **GHCR container image**. In the package settings, grant the main repo "Read" under "Manage
    Actions access".
  - Workflows run `container: ghcr.io/<you>/<game>-build:main` and `cp -a /orig .`
    ([example build.yml](https://github.com/encounter/dtk-template/blob/main/.github.example/workflows/build.yml)).
  - BW1, NFSMW and DC3 do this. LEGOLAND instead commits the exe; Crimsonland downloads it from its author's host (both outliers).

**Workflow sketch for this repo [mine]** (public decomp repo; the private image holds `orig/PC_20040610/T3Main.exe`):

```yaml
name: Build
on: { push: {}, pull_request: {} }
jobs:
  build:
    runs-on: ubuntu-latest
    container: ghcr.io/<owner>/t3-build:main      # private; contains /orig/PC_20040610/T3Main.exe
    strategy: { fail-fast: false, matrix: { version: [PC_20040610] } }
    steps:
      - uses: actions/checkout@v4
      - run: cp -a /orig .
      - run: python3 -m pip install -r requirements.txt   # iced-x86 for tools/delink_model.py
      - run: python3 configure.py --version ${{ matrix.version }}
      - run: ninja build/${{ matrix.version }}/report.json progress
      - uses: actions/upload-artifact@v4
        with: { name: "${{ matrix.version }}_report", path: "build/${{ matrix.version }}/report.json" }
```

Notes:
- `configure.py` already downloads objdiff-cli, delink, wibo and the compiler bundle, and verifies the SHA-1 of the exe.
- Ghidra is not needed in CI because `symbols.txt` is committed.
- Rename the `sdk` category ("SDK & runtime"). In dtk-template "sdk" means a console SDK; here it collides with T3SDK.

---

## 4. Shrinking the workload

### 4.1 Census from `config/PC_20040610/symbols.txt` [mine]

| Slice | Functions | Bytes | Note |
|---|---:|---:|---|
| All `type:function` | 40,585 | 5,324,479 | |
| `Unwind@…` EH funclets (`0x10E02DA0`-`0x10E3BF6C`) | 13,606 | 155,173 | Emitted by the compiler with their parents; name them, don't decompile them |
| Other functions at or after the CRT entry `0x10D1F7AF` | 8,779 | 986,622 | ~524 already FID-named (CRT: `_strtol`, `parse_cmdline`, EH runtime `___CxxFrameHandler`, `std::strstreambuf`…); likely CRT/STL/D3DX, to be verified |
| Before the entry point, non-funclet | 18,200 | 4,182,684 | Game + engine + Havok/libjpeg/CppUnit/STL instantiations |
| of which <32 B / 32-127 B / 128-511 B / 512 B-4 KB / ≥4 KB | 3,924 / 6,689 / 5,889 / 1,637 / 61 | 67 K / 482 K / 1,469 K / 1,755 K / 410 K | 70% of bytes are in the 1,698 functions ≥512 B |

The counts inform the plan:
- Agents will clear most function *counts* cheaply, but bytes (what decomp.dev shows) sit in about 1.7k large functions.
- Those large functions are where Lewis's long tail lives (">1,000 instructions").
- Plan for escalation to Opus and for humans on that tail.

### 4.2 Library identification

- **MSVC 7.1 static CRT (`libcmt.lib`) and C++ runtime (`libcpmt.lib`):**
  - Ghidra FID has already named ~550 functions.
  - For *matching*, copy BW1's approach ([libcmt skill](https://github.com/openblack/bw1-decomp/blob/main/.claude/skills/libcmt-obj-matching/SKILL.md)):
    a script indexes the archive members, finds each member's bytes in the exe, applies splits, verifies and reverts on failure.
    BW1 counts "240+ NonMatching lib objects", "Most are mechanical", with no agent judgement.
  - The objects link verbatim, and the owner must supply the `.lib`: "They are not committed and not downloaded — you
    must supply them yourself" (BW1 `configure.py`). The compiler bundle has no `Lib/`.
  - Gotchas BW1 documents: trailing `0xCC` padding, `__real@8` COMDAT folding, dead-strip under `/OPT:REF`,
    same-named statics.
- **Dinkumware STL:** the headers ship in the bundle (`Win32/7.1/Include/xtree`, `vector`, …). Instantiations compile
  from those headers inside game TUs, so the headers must stay untouched. `std::strstreambuf` members were already named by FID.
- **D3DX 8:** most likely the 71 objects built by the VC 7.0-era compiler (13.00.9178, per the Rich header in docs/target.md).
  Match them as verbatim library objects from the DirectX SDK's `d3dx8.lib` if the owner has it. Do not decompile them.
- **libjpeg 6a:** released 7 Feb 1996. The IJG licence permits redistribution and use for any purpose with attribution ([IJG](https://www.ijg.org/)).
  Compile `jpegsrc.v6a` with MSVC 7.1 under candidate flags and hash-compare functions. If they match byte for byte,
  vendor the public source as a third-party unit (isle keeps such code in `3rdparty/`).
- **CppUnit:** LGPL; the 1.8-1.10 series is from 2002-2003 ([SourceForge](https://sourceforge.net/projects/cppunit/)).
  Same approach: compile candidates and match. The test code (`ObjectSystemUnitTests.cpp`) is Ion Storm's own game code.
- **Havok 2:** proprietary and not public. Decompiling it would publish Havok's code, so give it its own category excluded
  from the headline and don't assign agents [mine].
- **Signature tools:**
  - Ghidra FID datasets are `vs2012…vs2019` plus an undocumented `vsOlder`
    ([ghidra-data](https://github.com/NationalSecurityAgency/ghidra-data/tree/master/FunctionID)). A custom FID DB built from the
    owner's VS2003 libs would add coverage.
  - IDA FLIRT signature collections exist ([FLIRTDB](https://github.com/Maktm/FLIRTDB)); rebrew claims FLIRT without IDA.
  - **Ghidra BSim** (H2 local DB, headless scripts) finds structurally similar functions "across compilers, architectures,
    and/or small changes" ([tutorial](https://ghidra.re/ghidra_docs/GhidraClass/BSim/README.html)). Good for matching
    public libjpeg/CppUnit builds to the exe and for sibling search.
  - Ghidra Version Tracking works one binary pair at a time.
  - BinDiff also works pairwise; it is useful only if another build of this engine exists, such as Deus Ex: Invisible War's exe, which shares the engine (docs/target.md).
  - coddog has no x86 support (see 1.2).

### 4.3 Dedup and similarity [mine]

- Build an index with iced-x86 (already a dependency of `tools/delink_model.py`) over every function.
  - The **exact key** is the sequence of opcodes and operands with relocation fields masked, using the relocation list the delink model already computes.
  - The **near key** is MinHash or Levenshtein over mnemonic sequences.
- Exact clusters (TArray/template instantiations, `IMPLEMENT_CLASS` boilerplate, static-init thunks like the named-TArray
  initializers in docs/engine.md) get solved once by a lead-approved template or macro.
- Near clusters feed the "similar matched functions" context, which had the largest effect in Lewis's and Kappa's work.
- Also mine `__FILE__`/assert strings and UE2 conventions for **TU boundaries and names**. Two hypotheses to test:
  - Whether Ion Storm kept UE2's `guard`/`unguard` macros (the UT432 public source defines them). They embed function-name strings.
  - Whether `.text$x` funclet runs follow link order per object. If they do, consecutive funclet groups would mark TU
    boundaries for EH-using code.

### 4.4 Class layouts: UE2 headers and their licences

- **UT432 public source** (UE1-era Core/Engine headers): "You may use them for your personal, non-profit enjoyment, but
  you may not sell or otherwise commercially exploit the source or things you created based on the source"
  ([ut432pubsrc](https://github.com/wrstone/ut432pubsrc)). Useful for idioms (`TArray`, `FString`, `FName`, `guard`), not for UE2 layouts.
- **UT2004:** native headers "weren't published"; the community NativeSDK adapts the UT432 headers by reverse engineering,
  for Object/Interaction/Actor only ([UT2004-NativeSDK](https://github.com/DarklightGames/UT2004-NativeSDK)).
- **UE2 Runtime:** the free edition shipped without native headers. The **registered** (paid) edition had them, under an
  EULA restricting use ([UnrealWiki](https://beyondunrealwiki.github.io/pages/unrealengine2-runtime.html)). Not a
  practical or clean source.
- **Best source: the game itself.** The SDK's planned generator (walk `UStruct` → `UProperty` Offset/ElementSize/Flags,
  handoff roadmap item 2) yields layouts for every script-visible class in *this* fork.
  - Emit them as `include/` headers with isle-style `DECOMP_SIZE_ASSERT` and offset comments ([reccmp recommendations](https://github.com/isledecomp/reccmp/blob/master/docs/recommendations.md)).
  - This is the highest-leverage precondition for agent success. Wrong offsets are the top "systemic blocker" in BW1 and a
    named failure mode in Lewis's work.

---

## 5. Legal and policy practice (facts, not legal advice)

- **The norm:** no binaries, assets or assembly in the repo; decompiled source is published.
  - dtk-template's template README: "This repository does **not** contain any game assets or assembly whatsoever. An
    existing copy of the game is required."
  - BW1, NFSMW, Halo and lemball state equivalents. SRHD's NOTICE: "Compiler binaries, game executables, game data, and IDA
    databases are not included in Git"; its MIT licence excludes recovered source.
  - lemball: reconstructed code "carries no license".
- **Binaries in CI:** private GHCR images built from private repos are the standard (dtk-template docs; BW1/NFSMW/DC3 workflows).
  **Outliers:** LEGOLAND commits the exe; Crimsonland downloads the exe and DLL from the author's server in CI.
- **Toolchains:** compilers are downloaded from third-party GitHub releases (`dbalatoni13/compilers`,
  `OmniBlade/decomp.me` MSVC 6 tarballs in BW1), not committed. SRHD notes that download URLs "are not an assertion that those inputs are freely licensed".
- **Enforcement precedent:** Take-Two DMCA'd re3/reVC (GTA III/VC reverse-engineered source) in 2021. They were restored after a counter-notice,
  then sued ([Game Developer](https://www.gamedeveloper.com/business/rockstar-parent-take-two-sues-modders-behind-i-gta-i-reverse-engineering-project-re3-)).
  The suit was dismissed in 2023 ([PC Gamer](https://www.pcgamer.com/take-two-dismisses-lawsuit-against-grand-theft-auto-modders/));
  I did not verify the dismissal terms.
- **Rights holder:** Embracer's 2 May 2022 release names *Thief* among the IPs acquired with Eidos-Montréal
  ([Embracer](https://www.embracer.com/releases/embracer-group-enters-into-an-agreement-to-acquire-eidos-crystal-dynamics-and-square-enix-montreal-amongst-other-assets/)).
- **decomp.me:** it hosts user scratches publicly but asks that no LLMs be hooked up (FAQ).
- **This repo today:** `CONTRIBUTING.md` says "No decompiler output and no disassembly beyond the few instructions needed
  to document an address", and CLAUDE.md says decompiler output stays local. A public matching decomp contradicts this.
  - Option (a): a separate public repository with its own contribution rules (no binaries or assets; matched C++ only).
  - Option (b): source stays private and a public repo only publishes the report. decomp.dev's code allows this, but it is not the community norm.
  - Either way, keep the SDK repo's rules unchanged. Record the chosen stance in CONTRIBUTING.md before any agent writes code.

---

## Appendix A: concrete per-agent loop and prompt skeleton [mine]

**Worker** (`claude -p --model claude-sonnet-5 --output-format json --settings guard-settings.json --append-system-prompt-file tools/agent/worker.md`, cwd = worker worktree):

1. `python tools/agent/next.py claim --agent w07` returns `{addr, symbol, unit, size, siblings[], callees[]}`, or exits when the queue is empty.
2. `python tools/agent/context.py 0x10A52530` prints:
   - the target disassembly (objdiff one-shot on the target object);
   - the cached Ghidra decompile;
   - the demangled signature (`undname.exe` from the bundle);
   - struct layouts for the touched classes, from the generated headers;
   - up to 5 matched similar functions with their source;
   - the relevant cheat-sheet entries.
3. Write `scratch/<addr>/v<N>.cpp`. Include the project headers; define only the target function.
4. `python tools/agent/try.py <addr> scratch/<addr>/v<N>.cpp` compiles through wibo with the pinned flags, diffs, and prints
   `score`, `mismatch_rows`, a compact `~ | < >` diff (BW1 style), and `ATTEMPT k/12`. Repeated source hashes are refused.
   Each attempt must state which asm difference it targets.
5. On zero mismatch rows: `python tools/agent/accept.py <addr> scratch/<addr>/vN.cpp` runs lint, the strict rulers, and a
   compile inside the claimed TU file. It writes into the TU only if the whole unit shows no regression.
   After 12 attempts: log `deferred` with the best % and a one-line blocker.
6. `next.py release`; the final stdout line is the JSON summary (`matched`, `improved`, `deferred[{fn,pct,why}]`, `needs[]`).
   `needs` covers the header, layout or naming changes the worker is not allowed to make.

**Lead** (Opus 5.5):
- owns `symbols.txt`, `splits.txt`, `include/` and `configure.py`;
- processes `needs`;
- merges worker branches in waves: rebuild all, then `objdiff-cli report changes`, and reject any regression;
- re-queues deferred functions whose blockers were fixed;
- escalates ≥95% near-misses to itself at higher effort;
- runs a reviewer pass that scores idiomaticity with a rubric (struct access over casts, no hacks, original names or placeholders).

**Hooks (guard-settings.json):** PreToolUse denials:
- Write/Edit on `config/**`, `configure.py`, `objdiff.json`, `orig/**`, `build/**/obj/**`;
- Bash patterns `git stash|reset|checkout \.`, `--no-verify`, and writes outside the worktree.

Snowboard Kids 2 shows this hook pattern works ([.claude/settings.json](https://github.com/cdlewis/snowboardkids2-decomp/blob/main/.claude/settings.json)).

## Appendix B: repositories inspected (shallow clones)

| Repo | Commit / date |
|---|---|
| freeqaz/dc3-decomp | 980e4d5, 2026-09-15 |
| openblack/bw1-decomp | 103400b, 2026-09-26 |
| marijnvdwerf/legoland | e8af1b5, 2026-09-26 |
| dbalatoni13/nfsmw | 5ab02da, 2026-09-26 |
| cdlewis/snowboardkids2-decomp | 3b1bd5d, 2026-09-27 |
| encounter/decomp.dev | e9c086a, 2026-09-06 |
| encounter/objdiff | fba10a6 (v3.8.1), 2026-08-29 |
| encounter/dtk-template | 95a941f, 2026-04-25 |
| pakompom/SpaceRangersHD_decomp | 28766d7, 2026-09-24 |
| decompme/decomp.me | 4ab701a, 2026-09-27 |
| ethteck/coddog | a72e89e, 2026-07-08 |
| banteg/crimson | 3fba00f, 2026-09-28 |
| dbalatoni13/compilers | release zip `compilers_20260903` (central directory listed via HTTP range requests) |

Pages that could not be fetched (HTTP 403): Macabeus's Medium posts, the UE2 Runtime EULA page on docs.unrealengine.com.
