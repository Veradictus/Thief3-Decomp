# Progress on decomp.dev

[decomp.dev](https://decomp.dev) shows the progress of public matching
decompilations. It reads the objdiff report that this repository's CI builds;
nothing is uploaded by hand. Findings behind this setup (how the site finds
reports, how other projects feed CI the original binary) are in
[research/llm-matching.md](research/llm-matching.md), section 3.

## How the report is built

`.github/workflows/build.yml` runs on every push and pull request:

1. It starts in a **private** container image that holds
   `/orig/PC_20040610/T3Main.exe`, and copies `/orig` into the checkout.
2. `configure.py` downloads the pinned tools (objdiff-cli, delink, wibo, the
   MSVC 7.1 bundle) and checks the exe's SHA-1.
3. `ninja all_source build/PC_20040610/report.json progress` splits the exe,
   compiles `src/`, and writes the report.
4. The report is uploaded as the artifact `PC_20040610_report`. decomp.dev
   takes the newest one from a completed push run on the default branch.

Until the repository variable `T3_BUILD_IMAGE` names that image, the build
job is skipped and a **baseline** job runs instead: `tools/baseline_report.py`
writes a report with the same units and categories from `symbols.txt` alone,
every function unmatched (data is left unmeasured), and uploads it under the
same artifact name. That is enough to register the project on decomp.dev,
which refuses a repository without a report ("No workflow runs containing
reports found"). It never shows progress: matched code counts only once the
real build runs.

Progress categories (set in `configure.py`): **main** "Game & engine" is the
headline, with **game** and **engine** under it; **libs** is the MSVC runtime,
STL and D3DX, matched from library objects rather than decompiled. Units get a
category from `UNITS` or, failing that, from their address (before
`LIBRARY_START`, `0x10CFBFB0`, where qhull and then the C runtime begin, and
the `.text$x` funclets: main; after: libs).

## One-time setup (repository owner)

**Register first** (no exe needed): once `build.yml` with the baseline job is
on the default branch and a push to it has run the workflow (Actions tab, a
green "build" run with a `PC_20040610_report` artifact), do step 4. Steps 1-3
switch the report from the baseline to the real build; they are needed before
matched code can show as progress.

1. **The build image.** Create a *private* repository, for example
   `<owner>/t3-build`, from
   [encounter/dtk-template-build](https://github.com/encounter/dtk-template-build)
   or from scratch. Put the Steam `T3Main.exe` (SHA-1
   `40bf68a54246bcde2fb5fcbc75b94dc7c7f78305`) at `orig/PC_20040610/T3Main.exe`
   and use this `Dockerfile`:

   ```dockerfile
   FROM python:3.12-slim
   RUN apt-get update && apt-get install -y --no-install-recommends ninja-build git \
       && rm -rf /var/lib/apt/lists/*
   COPY orig /orig
   CMD ["bash"]
   ```

   The template's workflow builds it and pushes `ghcr.io/<owner>/t3-build:main`
   on every push. Keep the repository and the package private: they contain the
   game's executable.
2. **Access.** In the package's settings on GitHub (Packages → t3-build →
   Package settings → Manage Actions access), add this repository with the
   *Read* role.
3. **The variable.** In this repository: Settings → Secrets and variables →
   Actions → Variables, add `T3_BUILD_IMAGE` = `ghcr.io/<owner>/t3-build:main`.
   The next push builds the real report, and the baseline job stops.
4. **decomp.dev.** Sign in at <https://decomp.dev/manage/new> with a GitHub
   account that is an admin of this repository, pick the repository, platform
   *Windows (win32)*, and set the default category to **main**. Installing the
   decomp.dev GitHub App adds per-PR comments listing improved and regressed
   functions, which helps when reviewing agent work.

A project stays hidden on decomp.dev until 0.5% of its code matches (about
21 KB of the 4.2 MB game and engine code).

## Badges

```markdown
![Code](https://decomp.dev/Veradictus/Thief3-Decomp.svg?mode=shield&measure=code&label=Code)
![Progress](https://decomp.dev/Veradictus/Thief3-Decomp.svg?w=512&h=256)
```

## Keeping the number honest

`objdiff-cli report generate` ignores relocation targets by default, so a
function that calls the wrong callee would still count as matched;
`configure.py` pins `functionRelocDiffs: name_address` in `objdiff.json` to
stop that. It still cannot see a wrong float or string literal (MSVC's COMDAT
constants all sit at offset 0). So functions enter `src/` only through
`tools/agent/accept.py`, which checks callees and data values by address and by
value (see [matching.md](matching.md)): the report is the progress display, the
gate is the proof.
