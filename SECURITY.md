# Security

## Reporting a vulnerability

Please report security problems privately, through the repository's
**Security → Report a vulnerability** form on GitHub, not in a public issue.
Say what is affected (launcher, SDK, a tool, the mod index), how to reproduce
it, and what an attacker could do with it. We aim to answer within a week and
to fix confirmed problems in the next release.

Only the latest release is supported; fixes are not backported.

## What counts

In scope:

- **The launcher**: installing a `.t3mod` (path handling, zip extraction),
  the mod index client (download checks), the updater, save backup and
  restore, and anything that writes outside the folders it manages.
- **The SDK** (`dinput8.dll`): crashes or memory corruption it causes, and
  anything that loads code from places other than `System/mods/`.
- **The tools** in `tools/` and the CI workflows (for example, a pull request
  that could run code with the repository's secrets).
- **The mod index**: ways to get a package installed that does not match the
  index's checksum or its own manifest.

Not vulnerabilities:

- **Mods run native code with the game's rights.** That is what a mod is. A
  malicious mod can do anything the player's account can; the index checks
  that a download is the file that was listed, not that the file is safe.
  Only install mods you trust.
- Bugs in Thief: Deadly Shadows itself, and cheats in a single-player game.

## How releases are protected

- Releases are built by GitHub Actions from a tagged commit
  ([docs/releasing.md](docs/releasing.md)).
- Launcher updates are signed with the Tauri updater key, and the launcher
  refuses an update whose signature does not match the public key it was
  built with.
- Mod downloads from the index are checked against the size and SHA-256 in
  the index before they are opened.
- The Windows executables are not yet Authenticode-signed, so SmartScreen may
  warn on first run; [docs/releasing.md](docs/releasing.md) describes the
  options (SignPath Foundation, Azure Trusted Signing).
