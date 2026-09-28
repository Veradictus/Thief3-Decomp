# The mod index

The T3SDK launcher's mod browser lists the mods in this folder: one file per
mod, `mods/<id>.json`, with its published versions and where to download
them. The index lists mods; it does not host them. Each package stays where
its author published it, and the launcher checks its size and SHA-256 against
the entry before opening it. The format is in
[docs/mods.md](../docs/mods.md#the-mod-index); the combined index is built by
`tools/modindex.py build` and published with the docs site.

## Submit a mod or a new version

1. Build your `.t3mod`: [templates/mod](../templates/mod/) does it with CMake,
   or `python tools/t3mod.py pack <folder>` from a folder with `mod.json`.
   Check it with `python tools/t3mod.py validate <id>-<version>.t3mod`.
2. Publish it at a stable `https://` URL. A GitHub release asset is the best
   place, for example
   `https://github.com/<you>/<repo>/releases/download/v1.2.0/<id>-1.2.0.t3mod`
   (the template's workflow creates that release when you push a tag).
3. In a fork of this repository, add the version to the index:

   ```sh
   python tools/modindex.py add <id>-<version>.t3mod --url <the URL> [--released YYYY-MM-DD]
   ```

   It creates or updates `modindex/mods/<id>.json` with the package's size,
   SHA-256 and the fields from its `mod.json`; the newest version's name,
   description, authors, homepage, license and tags describe the mod.
4. Open a pull request with that one file.

## What CI checks

The `modindex` workflow runs on every pull request that touches this folder:

- `python tools/modindex.py validate`: the file's fields; the id matches the
  file name; versions are valid, unique and newest first; URLs are `https://`;
  `sha256`, `size` and `released` are well formed; the fields repeated from
  `mod.json` follow the manifest rules.
- `python tools/modindex.py verify --changed-only <base>`: downloads every
  version the pull request adds and checks its size and SHA-256, that its
  `mod.json` has the entry's id, version, api, requires and conflicts, and
  that the package passes `tools/t3mod.py validate`. It refuses a change to
  the `sha256` or `size` of a version that is already listed.

A maintainer then reviews the pull request.

## Rules

- **One file per mod, named after its id.** The id is permanent; the first
  mod published under an id owns it. Change only your own mod's file.
- **A stable `https://` URL** that serves the package itself: a release asset,
  not a link shortener, a download page or a file-sharing link that expires.
- **No re-uploads under the same version.** Once a version is listed, its
  file never changes: players and the launcher rely on its SHA-256. Publish a
  fix as a new version. Moving the same file to a new URL is fine.
- **Licensing.** You must have the right to distribute everything in the
  package. Name the license in `mod.json` (`license`, an SPDX identifier such
  as `MIT` or `CC-BY-4.0`). Don't include the game's own files or other
  people's work without their permission.
- **Nothing harmful.** No malware, no copy-protection circumvention, nothing
  that changes files outside the game folder. Code mods should link their
  source from `homepage`.
- To withdraw a version or a mod, open a pull request that removes it.
  Maintainers remove entries that break these rules.
