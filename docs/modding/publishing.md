# Publishing to the mod index

The launcher's mod browser reads one index of published mods, published
with this site at
<https://veradictus.github.io/Thief3-Decomp/modindex/index.json>. It is
built from one file per mod in this repository, `modindex/mods/<id>.json`.
To list your mod, open a pull request that adds that file.

The index lists mods; it does not host them. The packages stay on your own
release page.

## 1. Release the package

Upload the `.t3mod` somewhere with a stable `https://` address. A GitHub
release is the usual place, and the [mod template](first-mod.md)'s workflow
puts it there.

Don't replace a file once it is published. The index records each file's
size and SHA-256, and the launcher refuses a download that does not match.
Publish a new version instead.

## 2. Write the entry

`modindex/mods/<id>.json` describes the mod and lists its versions, newest
first:

```json
{
  "id": "my-mod",
  "name": "My Mod",
  "description": "What the mod does, in one paragraph.",
  "authors": ["Your Name"],
  "homepage": "https://github.com/you/my-mod",
  "license": "MIT",
  "tags": ["gameplay"],
  "versions": [
    {
      "version": "1.0.0",
      "url": "https://github.com/you/my-mod/releases/download/v1.0.0/my-mod-1.0.0.t3mod",
      "sha256": "…64 hex digits…",
      "size": 48213,
      "released": "2026-09-01",
      "api": 1
    }
  ]
}
```

- `id`, `name`, `description`, `authors`, `homepage`, `license` and `tags`
  repeat your `mod.json`.
- Per version: `sha256` and `size` (in bytes) are those of the `.t3mod` file;
  `python tools/t3mod.py info <file>` prints the SHA-256. `released` is the
  date, `YYYY-MM-DD`.
- `api`, `requires` and `conflicts` repeat that version's `mod.json`, so that
  the browser can check them before it downloads anything.

The file is one entry of the index's `mods` list;
[the specification](../mods.md) describes the index in full.

## 3. Open a pull request

Fork this repository, add the file, and open a pull request. CI checks it
with `tools/modindex.py validate`. You can run the same checks first, from
a checkout:

```sh
python tools/modindex.py validate   # the entries are well formed
python tools/modindex.py verify     # also downloads each new version and compares it with its manifest
```

After the pull request is merged, the site's workflow rebuilds the index and
publishes it, and the mod shows in every launcher's browser.

## New versions

Upload the new package, add a new element at the top of `versions`, and open
a pull request. Keep the older versions in the list.

## Rules

- The file name, the entry's `id` and the package's `id` are the same.
- Every URL is `https://`.
- The package holds only your own work: no files from the game.
- The description says what the mod does, and what else it needs (such as
  Sneaky Upgrade).
