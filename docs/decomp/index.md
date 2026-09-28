# The decomp handbook

How to help reverse-engineer `T3Main.exe` and grow its matching
decompilation: finding what a function or global does, naming and
documenting it, and writing C++ that turns, byte for byte, into the same
machine code the original compiler produced. The reference material lives in
[matching.md](../matching.md) and [engine.md](../engine.md); this handbook is
the walkthrough that gets you there.

## Who this is for

Anyone with some x86 and C++ who wants to identify part of the engine or add
a function to `src/`, whether by hand or with an AI agent's help. No prior
reverse-engineering experience is assumed, but the handbook does not repeat
what Ghidra, MSVC or x86 already teach elsewhere; it covers what is specific
to this project.

Automated matching workers follow
[`.claude/agents/t3-matcher.md`](../../.claude/agents/t3-matcher.md) and the
[t3-match skill](../../.claude/skills/t3-match/SKILL.md) directly: shorter,
more operational versions of [first-match.md](first-match.md) meant to be
read by an agent rather than a person. This handbook explains the same tools
in more depth, for the person setting a session up, reviewing its output, or
matching a function by hand.

## Two paths through it

| Goal | Start here |
|---|---|
| Find out what a function or global does, and record it | [setup.md](setup.md), then [reverse-engineering.md](reverse-engineering.md), then [naming.md](naming.md) |
| Turn a queued function into matched C++ in `src/` (it doesn't need to be understood first) | [setup.md](setup.md), then [first-match.md](first-match.md), which sends you back to the other two pages as needed |

[techniques.md](techniques.md) is a reference to come back to while you work,
not a step in either path.

## What may go into the repository

This project keeps a hard line between what is written by contributors and
what comes from the game, so that decompiling it stays on the right side of
its owners. The rules are in
[CONTRIBUTING.md](../../CONTRIBUTING.md); this handbook exists to teach and
follow them, not to repeat them in full. In short:

- **Matched C++, not decompiler output.** `src/` and `include/` hold source
  that the game's own compiler turns into its bytes. Raw Ghidra output,
  disassembly listings and anything copied from the binary stay in your local
  `build/` and `ghidra/` folders, which are never committed. `docs/` may
  quote the few instructions needed to document an address or a pattern, as
  the worked examples in [reverse-engineering.md](reverse-engineering.md) and
  [techniques.md](techniques.md) do.
- **No fake matches.** No inline assembly, `__declspec(naked)`, codegen
  pragmas or pointer-plus-offset casts to force a match, from a person or
  from an agent. `accept.py`'s lint rejects all of it; see
  [first-match.md](first-match.md).
- **Only your own code.** The statically linked libraries (the MSVC runtime
  and STL, D3DX 8, Havok) are not decompiled here.
- **No game files, extracted assets or DRM work.** Nothing from the game's
  install enters the repository, whole or in part, and copy protection is out
  of scope.
- **No personal data.** No local paths or user names in `docs/`: write
  `<game folder>` and similar placeholders, as the rest of this handbook
  does.

## The rest of the site

This handbook covers the *process*. The facts it produces are the reference
pages: [engine.md](../engine.md) for addresses and layouts,
[target.md](../target.md) for the binary itself, and
[decomp-dev.md](../decomp-dev.md) for how progress is published. Once
something is identified, the [mod author cookbook](../modding/cookbook/index.md)
is where it turns into a mod hook, and the [player guide](../guide/faq.md) is
where players ask what any of this means for them.
