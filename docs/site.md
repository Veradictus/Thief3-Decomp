# This site

The documentation site, <https://veradictus.github.io/Thief3-Decomp/>, is
built with [VitePress](https://vitepress.dev/) from the Markdown files in
`docs/`. The same files read as plain Markdown on GitHub. The VitePress
project is in `site/`, a Yarn 4 project of its own like the launcher.

## Working on it

Needs Node 22.18 or newer, with Corepack enabled (`corepack enable`, once),
which supplies the Yarn version pinned in `site/package.json`.

```sh
cd site
yarn install
yarn docs:dev       # live preview at http://localhost:5173/Thief3-Decomp/
yarn docs:build     # the static site, in site/.vitepress/dist/
yarn docs:preview   # serve the built site
yarn typecheck      # the config and the scripts
```

- Every `.md` file in `docs/` is a page. New pages also need an entry in the
  sidebar, in `site/.vitepress/config.ts`.
- Write ordinary relative links, the kind that work on GitHub. Links that
  leave `docs/` (to `../CONTRIBUTING.md`, `../tools/sdk.py`, a folder) are
  turned into links to the file on GitHub's `main` branch by
  `site/.vitepress/repo-links.ts`. A link to a page in `docs/` that does not
  exist fails the build; a link to a repository path that does not exist is
  printed as a warning.
- Callouts that work in both places are GitHub's (`> [!NOTE]`,
  `> [!WARNING]`); VitePress's `:::` containers show as plain text on GitHub.
- VitePress gives headings that start with a digit an id starting with `_`
  (`## 6. The Godot export` becomes `#_6-the-godot-export`), and GitHub does
  not. Link to such sections by name ("section 6"), not by anchor.

## The API reference

[Mod API reference](reference/api.md) is generated from the comments in
`sdk/include/t3sdk/t3sdk.h` by `site/scripts/api-reference.ts`, and
committed, so that it reads the same on GitHub.

- `yarn api` rewrites `docs/reference/api.md` (`yarn docs:dev` runs it
  first).
- `yarn api:check` fails when the page is out of date with the header.
  `yarn docs:build` runs it, so CI fails until the page is regenerated and
  committed with the header change.

The script reads the header's own conventions: members of `T3SdkApi` are
grouped by blank lines; a comment above two or more members describes the
group, any other comment the member below it, and a comment after a member
on its line belongs to that member. Write "Since API version N." in the
comment of a member added after version 1; the page shows it.

## Publishing

`.github/workflows/docs.yml` builds the site for every pull request that
touches `docs/`, `site/`, `sdk/include/` or `modindex/`. A push to `main`
also deploys it to GitHub Pages, and so does starting the workflow by hand.

Before the upload it writes the [mod index](modding/publishing.md) into the
site as `modindex/index.json`, with `tools/modindex.py build`, so the
launcher finds it at
<https://veradictus.github.io/Thief3-Decomp/modindex/index.json>.

### One-time setup (repository owner)

In the repository's **Settings > Pages**, under **Build and deployment**,
set **Source** to **GitHub Actions**. The next run of the docs workflow on
`main` publishes the site. Nothing else is needed: the workflow creates the
`github-pages` environment on its first deploy.
