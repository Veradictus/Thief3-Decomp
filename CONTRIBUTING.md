# Contributing

## What may enter the repository

These rules keep the project on the right side of the game's owners. They are
not negotiable:

- **No game files.** Nothing from the game's install, whole or in part:
  executables, DLLs, packages, textures, sounds, videos, maps, INI files.
  `.gitignore` blocks the game's file types; don't force them in.
- **No game code.** No decompiler output and no disassembly beyond the few
  instructions needed to document an address or a pattern in `docs/`.
  Decompiled functions stay in your local `build/` and `ghidra/` folders.
- **No extracted assets.** The asset tools write into `build/assets/`, which is
  ignored. Test fixtures must be synthetic, not cut from game files.
- **No DRM work.** Don't analyse, patch, bypass or document copy protection
  (Steam's launcher wrapper, SecuROM). The SDK hooks `T3Main.exe` only.
- **No personal data.** No local paths (`C:\Users\<name>\...`, library
  folders), user names, e-mail addresses, keys or tokens in files. Tools find
  the game through the registry, `--game-dir` or `T3_GAME_DIR`.

What does belong here: the SDK and tools (original code), and notes on how the
game works (addresses, structure layouts, file formats) with the evidence for
them, which mods need in order to interoperate with the game.

## Commit messages

We use [Conventional Commits](https://www.conventionalcommits.org/):

```
<type>(<scope>): <summary>

<body: what changed and why, wrapped at 72 columns>

<trailers>
```

- **type**:
  - `feat`: a new capability (SDK feature, fix option, tool command).
  - `fix`: a bug fix.
  - `docs`: documentation only.
  - `refactor`: a code change that changes no behaviour.
  - `chore`: repository housekeeping (ignore rules, configuration).
  - `build`: build system changes.
- **scope** (optional) names the area: `sdk`, `display`, `fixes`, `menu`,
  `crash`, `tools`, `workbench`, `assets`, `docs`.
- **summary**: imperative mood ("add", not "added"), lower case, no final
  period, at most 72 characters in all.
- **body**: optional for small changes. For fixes, say what broke and how it
  showed up (for example "the game froze after alt-tab").
- A breaking change to the mod API or the INI format gets a `!` after the type
  (`feat(sdk)!: ...`) and a `BREAKING CHANGE:` trailer.

Examples:

```
feat(display): run the game in a borderless window
fix(display): stop the freeze when the borderless game loses focus
docs(engine): record the options table and the UI window fields
```

Keep commits small and about one thing. A feature and the documentation that
describes it can go together; unrelated clean-ups go in their own commit.

## Code

Match the surrounding code: its naming, comment density and idiom. The SDK is
C++ built with MSVC for 32-bit x86 and must build without warnings. Tools are
Python using only the standard library, plus Ghidra scripts in Java. Record
every engine address you use in `docs/engine.md` with its evidence, and its
name in `config/PC_20040610/symbols.txt`.
