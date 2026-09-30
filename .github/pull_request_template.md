## What and why

<!-- What this changes and why. Link the issue if there is one. -->

## Checks

<!-- Tick what you ran; CI runs the rest. -->

- [ ] `cd launcher && yarn verify` (launcher UI)
- [ ] `cd launcher/src-tauri && cargo fmt --check && cargo clippy && cargo test` (launcher backend)
- [ ] `python tools/sdk.py build` (SDK, needs Visual Studio)
- [ ] `python tools/assets/selftest.py`, `python tools/agent/selftest.py`, `python tools/mods/selftest.py`
- [ ] Tested in the game (say what you tried)
- [ ] Docs updated

## Repository rules

- [ ] No game files, extracted assets, raw decompiler output or disassembly
- [ ] No personal data (local paths, user names, keys)
- [ ] Commit messages follow Conventional Commits ([CONTRIBUTING.md](https://github.com/Veradictus/Thief3-Decomp/blob/main/CONTRIBUTING.md))
