# Unreal Engine reverse engineering and agent swarms: research report

Date: 2026-10-02. Question: how did other Unreal Engine 2 decompilations, and
the matching decompilations that run AI agents at scale, approach the work;
what did their commit histories show about the problems they hit; and what
should change in this repository's swarm ([agent-workflow.md](../agent-workflow.md))
as a result. It follows [llm-matching.md](llm-matching.md) (2026-09-27), which
covers the earlier state of the field.

Method: web searches for decompilation and native reverse-engineering projects
of games on Unreal Engine 1, 2 and 2.5, and for matching decompilations on MSVC
targets that use agents. The repositories below (23, listed under Sources)
were cloned and their histories read (`git log` on their tooling and agent files, commit messages,
doc diffs). decomp.dev itself was not reachable from the research environment,
so project lists there were not consulted. Labels as in the earlier report:
**[shown]** for what a repository's files or history show, **[claimed]** for
what a project states without evidence we could check, **[mine]** for
inference.

## Summary

- **No public matching decompilation of an Unreal Engine 2 game was found.**
  The work around UE2 games is header reconstruction for native mods
  (Republic Commando, UT2004), reflection-based SDK generators, script
  decompilers, and one AI-assisted behavioural reverse engineering of a UE1
  game (Deus Ex). This project appears to be the first matching
  decompilation in the family, so the Unreal-specific lessons come from those
  neighbours, and the swarm lessons from MSVC projects on other engines.
- **The Unreal-specific findings that matter most** [shown]: the "lazy
  registration" functions of our native classes are Epic's `__STATIC_LINK`
  macros (`GetPrivateStaticClass<C>`, `InitializePrivateStaticClass<C>`,
  `InternalConstructor`), so about 260 unnamed functions can be named from
  `classes.txt`; the `UObject` virtual order of two UE2 descendants fits the 16
  unknown slots of our `Core.h`; MSVC emits overloaded virtuals in reverse
  declaration order; and a runtime dump of `UFunction` objects can name every
  script native.
- **The swarm findings that matter most** [shown]: later attempts rarely
  match (byte-tactics: 80% of matches on the first attempt, 44% on the second,
  16% on the third, under 9% after); families of functions that differ only in
  their references can be matched from one member with no model
  (meteor-decomp: about 97% of its matches, although mostly as byte copies we
  forbid); placeholder virtuals and per-file class views turn into thousands of
  cleanup commits later (gruntz); a different model on another model's
  deferrals finds real matches (DC3: 49 of 150 "hopeless" functions); workers
  degrade after about 100 tool calls (LEGOLAND).
- **What changed here as a result** is in section 3: a guard that actually
  runs, families stamped without a model, a stop rule for attempts, richer
  context packets, claims by class, blocker slugs, and the swarm as a saved
  workflow script. Section 4 lists what is recommended next.

## 1. Unreal Engine projects

| Project | What it is | History |
|---|---|---|
| [SWRC-Modding/CT](https://github.com/SWRC-Modding/CT) | Republic Commando C++ headers rebuilt from the UT v432 public headers, plus mods | 995 commits, 2018-07 to 2026-09, almost all by one maintainer |
| [DarklightGames/UT2004-NativeSDK](https://github.com/DarklightGames/UT2004-NativeSDK) | UT2004 native SDK adapted from the UT432 headers (Object, Interaction, Actor, Volume) | 2 commits, 2020 (a mirror of a 2019 forum release) |
| [kosumosu/unreal-headers-and-libs](https://github.com/kosumosu/unreal-headers-and-libs) | UE1 headers and import libraries (Unreal 226, UT432, Rune, Deus Ex) | 2 commits, 2017 |
| [polivilas/UnrealEngineSDKGenerator](https://github.com/polivilas/UnrealEngineSDKGenerator) | Runtime SDK generator for UE1 to UE4, MIT | 107 commits, 2016-2017 |
| [FaultyRAM/Ut99PubSrc](https://github.com/FaultyRAM/Ut99PubSrc) | Epic's UT432 public source, ported to CMake | 4 commits, 2017 |
| [FilRip/RainbowSix_RavenShield](https://github.com/FilRip/RainbowSix_RavenShield), [jkelin/TribesRevengeance-Source](https://github.com/jkelin/TribesRevengeance-Source) | Script sources and UCC-generated headers; no C++ | a few commits |
| [JuggyMcNutty/dx-reverse-info](https://github.com/JuggyMcNutty/dx-reverse-info), [port-ex-machina](https://github.com/JuggyMcNutty/port-ex-machina) | Deus Ex (UE1) binaries described "in our own words", written with Claude | 87 and 223 commits, 2026-09 |
| [Encryqed/Dumper-7](https://github.com/Encryqed/Dumper-7), [Fischsalat/IDAExecFunctionsImporter](https://github.com/Fischsalat/IDAExecFunctionsImporter) | UE4/5 runtime dumper and its IDA importer: exec natives, vtables, FName constants | active |

None of the UE projects uses agent tooling except the Deus Ex pair; all are
headers, SDKs or notes, not matching source.

### 1.1 Registration is Epic's static-link mode

In `Ut99PubSrc/Core/Inc/UnObjBas.h:284-323` and `:387-430` (the same in the
UT2004 SDK) [shown], a statically linked build defines:

- `StaticClass()` inline: when `PrivateStaticClass` is null, call
  `GetPrivateStaticClass<C>(TEXT("Package"))`, then
  `InitializePrivateStaticClass<C>()`;
- `GetPrivateStaticClass<C>`: `new UClass(EC_StaticConstructor, sizeof(C),
  flags, guid, name, package, config name, RF_Public | RF_Standalone |
  RF_Transient | RF_Native, InternalConstructor, StaticConstructor)`. The
  four flags OR to `0x04084004`, the value [engine.md](../engine.md#native-class-registration)
  records for our getters;
- `InitializePrivateStaticClass<C>`: super field, class within, `SetClass`,
  `Register()`;
- `DECLARE_CLASS`: a virtual destructor calling `ConditionalDestroy()` and
  `InternalConstructor(void* X) { new ((EInternal*)X) C(); }`.

So the getter, initializer and internal constructor that `classes.txt` lists
for each of the 266 classes are macro instantiations with known names; 258 of
the getters and initializers are still `FUN_` names with guessed signatures,
and 132 internal constructors are unnamed [shown, counted in our
`classes.txt` and `symbols.txt`]. Our own `DECLARE_CLASS`/`IMPLEMENT_CLASS`
macros in `include/Core/Core.h`, written to the binary, would match the Ion
Storm classes' registration functions in one pass [mine].

### 1.2 Layouts and virtual order

- **Where their layouts came from.** CT reads the exported `??_7Class@@6B@`
  vtables and decorated names of Republic Commando's DLLs (`Core.lib` 2,389
  names, `Engine.lib` 8,073; the UT2004 SDK's 2,230 and 7,535); link errors
  catch wrong signatures. Their only layout check is at run time:
  `VERIFY_CLASS_SIZE`/`VERIFY_CLASS_OFFSET` against the script's sizes and
  property offsets, and crashes. Wrong sizes surfaced years later (CT
  `b453dd1`, `8dcf278`, `d46d5b1`) [shown]. T3Main.exe has no exports and no
  RTTI, so only the techniques carry over.
- **`UObject`'s virtuals** [shown, names and order as facts]: Republic
  Commando, which like T3 has no `FUnknown` base, declares the destructor, then
  ProcessEvent, ProcessDelegate, ProcessState, ProcessRemoteFunction, Modify,
  PostLoad, Destroy, Serialize, IsPendingKill, IsInState, GotoState,
  GotoLabel, InitExecution, ShutdownAfterError, PostEditChange, PreEditUndo,
  PostEditUndo, CallFunction, ... UT2004 has the same list with `FUnknown`'s
  three slots first and `ScriptInit` after GotoLabel. Our `Core.h` has 16
  unknown slots between the destructor and CallFunction (slot 17); either list
  without its extra entry gives exactly 16 [mine]. Each slot still has to be
  confirmed by behaviour (Serialize takes an `FArchive&`, GotoState an
  `FName`, IsPendingKill is tiny).
- **Overloaded virtuals**: CT `231d562` fixed a crash by swapping FArchive's
  two `operator<<` declarations; the Deus Ex notes say MSVC "reverses overload
  groups in vtables" [shown]. Adjacent slots of one overload set are declared
  in reverse.
- **Licensee changes they met**: Republic Commando's `FName` holds an entry
  pointer, its `CPF_Native` is `0x10` (CT `7c354f2`), and `UProperty`,
  `UStruct` and `UClass` gained fields (`e29efd9`, `2699503`); UT2004's
  `UObject` is `0x2C` bytes, like ours, and both SDKs found the extra field by
  reading live objects [shown].

### 1.3 Naming from the running game

The SDK generator walks `GObjects` and every `UStruct`'s children; Dumper-7
writes each `UFunction` with `FUNC_Native` and its `Func` pointer as
`Class::execName`, de-duplicated by address, and finds field offsets by
known-answer probing (the one offset where several known objects hold their
known values) [shown]. For T3, with `UObject` 4 bytes longer than stock, the
generator's UE2 offsets shift by 4 (Next near `0x30`, Children near `0x40`,
`UProperty::Offset` near `0x4C`) [mine]; our SDK already probes Outer and
SuperField this way (`sdk/loader/engine.cpp`). Known answers we have: the 234
`UObject::exec*` addresses in `symbols.txt` for `Func`, stock Core native
numbers for `iNative`, the 266 class sizes, and the generated class headers'
offsets. Coverage estimate: 1,000 to 1,600 native functions, about 800 to
1,300 new names, plus their callees and overrides [mine, to measure].

### 1.4 How the Deus Ex work was run

`port-ex-machina/agent.md` (touched by 169 of 223 commits) holds state,
numbered and dated decisions ("4. Reverse-engineering the game's DLLs (owner,
2026-09-24)") and open decisions, and links to the one document that holds
each fact. One finding per commit, titled `<binary>: <finding>`, with the
address and how it was checked (static, live run, or the original routine run
in Unicorn); corrections are committed as corrections; names live in the IDA
databases and are recreated by scripts that rename only placeholders and
print counts [shown].

### 1.5 Licences

UT432's public source allows personal, non-profit use only; CT has no licence,
derives from UT432 and a UT2003 source of unclear origin, and commits raw
Hex-Rays output of the game's DLLs; the import libraries in these repositories
are the games' own binaries. Names and declaration order are facts, usable as
references; nothing of their text belongs in this repository
(CONTRIBUTING.md). The SDK generator is MIT.

## 2. Agent swarms on MSVC targets

| Project | Target, compiler | Agents | Result |
|---|---|---|---|
| [HectorBailey/byte-tactics](https://github.com/HectorBailey/byte-tactics) | Total Annihilation, MSVC 5 | Claude Code lead with sub-agents, then GitHub issues claimed by Claude, OpenCode, DeepSeek and others; 17 models in `data/attempts.csv` | 3,089 of 3,267 functions (94.6%), 73% of bytes, 6 days, about 2,400 PRs |
| [swstegall/meteor-decomp](https://github.com/swstegall/meteor-decomp), [decomp-agents](https://github.com/swstegall/decomp-agents) | Final Fantasy XIV 1.23b, VS2005 | Agent SDK workers, SQLite claims, per-function worktrees; later forks claiming through issues | 69,247 files, mostly templates and `_emit` byte copies |
| [sushi-shi/gruntz-decomp](https://github.com/sushi-shi/gruntz-decomp) | Gruntz, MSVC 5, no PDB | 3 worktree slots, lead plus matcher, holista, wall-identifier skills | 4,005 of 4,426 exact (90.5%), 8,609 commits by one person |
| [srp-survarium/vostok](https://github.com/srp-survarium/vostok) | Survarium's engine, VS2008, retail PDB | orchestrator, matcher, structure verifier, reviewer | 10,473 of 13,014 exact (80.5%) |
| [openblack/bw1-decomp](https://github.com/openblack/bw1-decomp) | Black & White, MSVC 6 | Sonnet matchers; an inliner-budget agent | (on decomp.dev) |
| [marijnvdwerf/legoland](https://github.com/marijnvdwerf/legoland) | LEGOLAND, MSVC 6 | Claude as manager, one worker at a time | (on decomp.dev) |
| [freeqaz/dc3-decomp](https://github.com/freeqaz/dc3-decomp) | Dance Central 3, MSVC PPC | six long lanes on disjoint directories, Opus and Fable | waves of +165 to +267 functions |
| [dbalatoni13/nfsmw](https://github.com/dbalatoni13/nfsmw) | NFS Most Wanted PC, MSVC 7.1 + delink | none on PC yet | symbol pairing stage |
| [AARosson48/SummonerDecomp](https://github.com/AARosson48/SummonerDecomp) | Summoner, MSVC 6 | Cursor | 210 of 6,978 functions, 2 days old |

### 2.1 Measured

- **Attempts** (byte-tactics, computed from `data/attempts.csv`): first
  attempt 80.1%, second 44.3%, third 15.9%, fourth to ninth 1 to 9%, tenth and
  later 3.0%. Their stop rule moved from a count to "no new best in 30 runs or
  60 minutes" (`da37e36d`, after `e840cc75`); retry yield went from 2.7% to
  12.1% at the same time as a permuter arrived, so the two are confounded
  [shown].
- **Model by size** (byte-tactics `data/batches.csv`, Opus): up to 40 bytes
  142/142 at 11.2K tokens per match; 41 to 160 bytes 1,021/1,030 at 13.8K; 161
  to 400 bytes 54/67 at 89K; 401 bytes and more 55/76 at 154K. Haiku 91% at 1
  to 16 bytes and under 30% above 40; Sonnet 88 to 90% at 17 to 64 bytes. Their
  token counts are probably the harness's summary, not billed tokens, so they
  do not compare directly with ours [shown; mine for the caveat].
- **Throughput curve** (byte-tactics): matches per day fell from 607 to 49
  while landed PRs per day rose from 170 to 824: the tail is retries [shown].
- **Templates** (meteor-decomp, `docs/decomp-status.md`): byte-identical and
  relocation-masked clusters, a recogniser of about 75 shapes
  (`derive_templates.py`) and `stamp_clusters.py` gave 10,577 matches in a day
  and about 97% of the project's files; of the 2,039 agent files, 1,489 use
  `_emit` and 415 `__asm`, and only 130 are plain C++ [shown]. The clustering
  works; their gate does not check relocations or forbid assembly, which ours
  does.
- **Different model on deferrals** (DC3 wave 7, `bb2e759e`): Fable retried 150
  functions Opus lanes had called hopeless; 49 reached 100%, and about 20 hid
  real bugs. "An Opus AT_LIMIT note is now a lead, not a verdict" [shown].
- **Inliner** (BW1 `a75648f`): the MSVC 6 inline decision recovered from
  c2.dll; a helper's `if` rewritten as a ternary took a function from 68.1% to
  98.4%; about 5,200 builds over plausible variants found nothing for x87
  operand-order tie-breaks [shown].

### 2.2 Problems and their fixes

- **Placeholder classes cost later** (gruntz): June used per-unit class
  "views" and placeholder virtuals; July spent about 1,000 commit subjects on
  views, 555 on vtables and 505 on placeholders, and a padded base caused a
  crash in the game (`d74d21db`). The fix: one shared header per class, and
  virtuals transcribed from a mechanical slot map (inherited: declare nothing,
  override, new) [shown]. Our units still declare `Virtual0()`... placeholders.
- **Signatures and names** (byte-tactics): agents may redeclare a callee
  locally because "the checker compares names, not types"; the result is
  linkability debt: 20.4% of referenced names resolve, 2,027 calls use a name
  with another signature (`docs/linking.md`, #2662) [shown]. Our gate checks
  decorated names, which is why name conflicts block us instead; the remedy is
  to settle them continuously, not to stop checking.
- **Claims** (byte-tactics, meteor): issue claims raced within two minutes;
  `rva % 8` sharding sent 54,232 of 54,494 functions to one shard because
  addresses are 16-byte aligned (meteor `8564b91`); worktrees missing ignored
  inputs bailed on the same function five times. Our atomic file claims avoid
  all three [shown].
- **Long workers** (LEGOLAND `docs/manager-handover.md`): after about 100
  tool calls workers ignore instructions and ship duplicate code; one reached
  464 calls and caused a regression. gruntz retires an agent at about 700K
  tokens and refills slots before integrating (`22ecb849`) [shown].
- **Header edits are global** (DC3): giving `Symbol` a copy constructor moved
  9 functions up and 3,409 down; a struct edit reordered COMDATs in 18
  unrelated objects [shown]. Shared headers need a whole-project regression
  check.
- **Measurement**: `objdiff-cli diff` and `report generate` use different
  defaults (DC3 `2859f0c1`); the access letter is part of the mangled name
  (`2e4d1ac5`); a flat transcript glob saw 1.4% of sub-agent transcripts
  (`fa4fdf6f`) [shown]. Our sweep reads `*/*/subagents/agent-*.jsonl`.
- **Triage before trying** (BW1): classify the difference first, prove that a
  knob moves the output before sweeping it, budget 20 builds for an inliner
  problem and 15 for a tie-break, and defer a confirmed tie-break with a slug
  [shown].

### 2.3 What they do worse

No CI at byte-tactics, gruntz or vostok; byte copies counted as matches at
meteor; callee types unchecked at byte-tactics; gruntz certifies scores
reached under a temporary probe it then removes; vostok copies leaked engine
source and needs a PDB; no project publishes cost per match. Our strict gate,
categories and per-band token accounting are ahead of all of them.

## 3. What changed in this repository

| Change | Where | Why |
|---|---|---|
| The guard runs for workers: a project hook that checks calls whose `agent_type` is `t3-matcher` | `.claude/settings.json`, `tools/agent/hooks/guard.py` | A hook in an agent's frontmatter did not run for Agent-tool sub-agents (tested with Claude Code 2.1.287: a worker wrote into `build/` and ran `python3 -c`); the project hook ran with `agent_type` set and blocked both |
| Workers skip CLAUDE.md | `.claude/agents/t3-matcher.md` (`omitClaudeMd`) | Tested: the worker no longer sees it; it costs every worker tokens and holds nothing it needs |
| Families matched without a model | `tools/agent/clusters.py`, `next.py`, `sweep.py` | meteor-decomp's clusters with real C++ and our gate: one accepted member's source is rewritten for each sibling and must pass accept.py |
| A stop rule: 3 attempts in a row with no new best end a claim | `try.py --patience`, `common.PATIENCE` | byte-tactics' attempt curve |
| The best earlier attempt, the callers' bound name, the family and the base class's slot in the context packet | `context.py` | byte-tactics (carry the best partial forward), DC3 (notes are leads), gruntz and the Deus Ex notes (override names from the base) |
| Claims by class | `next.py claim --by-class` | gruntz and DC3 lanes, BW1 units: a class declared once per worker |
| A triage step and blocker slugs | `worker.md`, `sweep.py` | BW1's triage; the lead batches unblocking by slug, and out-of-scope slugs leave the queue |
| Matches by attempt number, deferrals by slug, a batch log | `sweep.py`, `build/agent/swarms.jsonl` | to tune caps and bands from our own curve |
| The swarm as a saved workflow | `.claude/workflows/t3-swarm.js` | refill without the lead's tokens per completion, stamps between workers, structured results |
| Claims refuse without the split or the toolchain | `next.py` | meteor-decomp's workers bailed five times on missing inputs |

## 4. Recommended next

In order of expected matches per hour of lead time [mine]:

1. **Name the registration functions** (section 1.1): check one getter's
   decorated name against the exe (does T3's `UClass` constructor take the
   `FGuid`?), then generate `GetPrivateStaticClass<C>`,
   `InitializePrivateStaticClass<C>` and `InternalConstructor` names for every
   class in `classes.txt` with `fixnames.py spec`, and write `DECLARE_CLASS`
   and `IMPLEMENT_CLASS` macros in `Core.h` so that the Ion Storm classes'
   registration matches in one pass.
2. **Dump the natives from the running game** (section 1.3): an SDK developer
   command that probes the `UFunction` offsets with known answers, writes
   every native function's class, name, `iNative` and `Func` outside the
   repository, and a `tools/natives.py import` that names only placeholders.
3. **Confirm `UObject`'s slots** (section 1.2) by behaviour and rename
   `Unknown04`...`Unknown40` in `Core.h`; the packet's base-slot line then
   names every override of them.
4. **Shared class headers with a ratchet** (gruntz): one header per class,
   virtuals from the slot map (inherited, override, new), a count of
   `Virtual\d+` placeholders and `Unknown` fields that may only fall, and a
   whole-project regression check on every header edit (DC3).
5. **A slot-binding check in the gate** (byte-tactics `6cbd5f1d`, gruntz
   `vtables.py`): a declared virtual must sit at the slot the real vtable gives
   it, and the class must not declare more slots than its table has.
6. **Types back into Ghidra** (byte-tactics `af719a3b`): compile the
   integrated units with `/Z7`, read the struct layouts and signatures from the
   debug information and apply them before `fill-ghidra`, so the packets of
   large functions show named fields.
7. **Second passes by the other model** (DC3): Opus on Sonnet's deferrals and
   Sonnet on Opus's, with the best attempt in the packet.
8. **delink v0.16.4** (nfsmw `5ab02dae`): function sizes for objdiff and
   layout-preserving relinking; A/B the split objects first, as it changes the
   section layout.
9. **`__FILE__` and `__LINE__`**: UE2's `check()` and `guard` macros will put
   `c:\T3_Code\...` paths and line numbers into larger functions; DC3 maps the
   compiler's paths (`WIBO_PATH_MAP`).

## Sources

Repositories as cloned on 2026-10-02 (blob-less clones, histories read with
`git log`): the 21 listed in sections 1 and 2, plus
[dbalatoni13/delink](https://github.com/dbalatoni13/delink) at v0.16.4 and
[sushi-shi/giten-decomp](https://github.com/sushi-shi/giten-decomp). Commit
hashes above are those repositories'. The Claude Code facts in section 3 were
checked in this repository with Claude Code 2.1.287 and against
<https://code.claude.com/docs/en/sub-agents>, <https://code.claude.com/docs/en/hooks>
and <https://code.claude.com/docs/en/workflows>.
