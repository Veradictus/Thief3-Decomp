# Releasing

How a version of the launcher and the SDK is published, how the launcher
updates itself, and what code signing would add. The workflows are in
`.github/workflows/`: `launcher.yml` builds every change, `release.yml`
publishes a tag, and both call `launcher-build.yml`.

## Cutting a release

A release is a tag named `v<semver>`:

```sh
git checkout main && git pull          # the commit to release, with a green launcher workflow
git tag v0.2.0
git push origin v0.2.0
```

`release.yml` then builds on Windows and publishes a GitHub release with
generated notes:

| File | What it is |
|---|---|
| `T3SDK-Launcher_<version>_x64-setup.exe` | NSIS installer (per user, no admin rights) |
| `T3SDK-Launcher_<version>_x64-setup.exe.sig` | the updater's signature of the installer (with the updater key) |
| `T3SDK-Launcher_<version>_portable.zip` | the same files, to unzip and run |
| `T3SDK_<version>_x86.zip` | the SDK alone, for `System/` by hand |
| `latest.json` | what the launcher's updater reads (with the updater key) |

The tag is the version: the build passes it to
`tools/stage_launcher.py stage --version`, which puts it into the launcher's
config. Bump `tauri.conf.json`, `Cargo.toml` (and the launcher's entry in
`Cargo.lock`) and `package.json` to the same version in a pull request before
tagging, so a local build reports the version being released. A tag with a hyphen (`v0.3.0-beta.1`) becomes a
pre-release. The updater never offers pre-releases: it reads
`releases/latest/download/latest.json`, and GitHub's "latest" is the newest
full release.

To redo a failed release, delete the release and the tag on GitHub, fix, and
push the tag again:

```sh
git push origin :refs/tags/v0.2.0      # delete the tag on GitHub
git tag -d v0.2.0                      # and locally
git checkout main && git pull
git tag v0.2.0 && git push origin v0.2.0
```

`failed to decode secret key: incorrect updater private key password` in the
launcher build's Build step means `TAURI_SIGNING_PRIVATE_KEY_PASSWORD` does not
match `TAURI_SIGNING_PRIVATE_KEY` (see the updater key, below): set the
password the key was generated with and redo the release.

## The updater key

The launcher installs an update only if the installer is signed with the
private updater key whose public half is built into the launcher
([tauri-plugin-updater](https://v2.tauri.app/plugin/updater/)). This key has
nothing to do with Windows code signing (below); Windows never sees it.

Generate it once, on your own computer (Tauri's CLI is in the launcher's
dependencies):

```sh
cd launcher
yarn tauri signer generate -w ~/.tauri/t3sdk-updater.key
```

It asks for a password and writes the private key (`t3sdk-updater.key`) and
the public key (`t3sdk-updater.key.pub`). Keep the private key and its
password somewhere safe, such as a password manager: installed launchers
accept updates signed with this key only. If it is lost, every user has to
install the next version by hand.

Then, in the repository's **Settings → Environments**, create an environment
named `Updater` and add to it:

| Name | Kind | Value |
|---|---|---|
| `TAURI_SIGNING_PRIVATE_KEY` | secret | the contents of `t3sdk-updater.key` |
| `TAURI_SIGNING_PRIVATE_KEY_PASSWORD` | secret | its password (leave it out for a key without one) |
| `T3_UPDATER_PUBKEY` | secret or variable | the contents of `t3sdk-updater.key.pub` (one line) |

`release.yml` runs the launcher build in that environment, so only release
builds see the key; the builds for pushes and pull requests never do. If the
environment has deployment rules, allow the `v*` tags. (Repository-level
secrets and variables under **Settings → Secrets and variables → Actions**
work too, but then every same-repository build can read the key.)

What the workflows do with them:

1. `launcher-build.yml` stages with
   `stage_launcher.py stage --updater-pubkey "$T3_UPDATER_PUBKEY"` (and this
   repository's endpoint) when both the public and the private key are
   there. The generated
   `launcher/src-tauri/bundle/tauri.bundle.conf.json` then has
   `plugins.updater` (the public key, the endpoint
   `https://github.com/<repo>/releases/latest/download/latest.json`, Windows
   install mode `passive`) and `bundle.createUpdaterArtifacts: true`.
2. `yarn tauri build` gets the two secrets as environment variables and signs
   the NSIS installer: next to `…_x64-setup.exe` it writes
   `…_x64-setup.exe.sig`. (Tauri 2 signs the installer itself; the `.nsis.zip`
   of Tauri 1 is not made.) The Package step copies the `.sig` next to the
   renamed installer; the signature covers the bytes, not the name.
3. `release.yml` writes `latest.json` from the `.sig` and attaches both:

   ```json
   {
     "version": "0.2.0",
     "notes": "T3SDK Launcher 0.2.0: https://github.com/Veradictus/Thief3-Decomp/releases/tag/v0.2.0",
     "pub_date": "2026-09-28T12:00:00Z",
     "platforms": {
       "windows-x86_64": {
         "signature": "<the contents of the .sig>",
         "url": "https://github.com/Veradictus/Thief3-Decomp/releases/download/v0.2.0/T3SDK-Launcher_0.2.0_x64-setup.exe"
       }
     }
   }
   ```

In the launcher, `src-tauri/src/update.rs` registers the updater plugin only
when the app's config has `plugins.updater` with a key. It checks at start-up
(at most once a day; Settings can turn this off), shows "Update available"
in the sidebar, and on "Update and restart" downloads the installer, checks
its signature and runs it in passive mode: a progress bar, no questions, and
the new launcher starts when it is done. A copy unzipped from the portable
zip does not update itself (the installer would install a second copy); it
points to the releases page instead.

The UI calls the launcher's own commands (`updater_status`, `check_update`,
`install_update`), not the plugin's JavaScript API, so the window's
capability (`src-tauri/capabilities/default.json`) grants no `updater:`
permission. Tauri checks capability permissions when the app is built,
against the plugins compiled into it; a plugin that is compiled in but not
registered only matters when the web page calls one of its commands, which
then fails. With no updater permission granted, the page cannot call the
plugin in any build; the launcher's commands check whether it is registered.

Development builds (`launcher.yml` on a push to this repository) are signed
too when the key is set up. They carry the version in `tauri.conf.json`, so
they offer the latest release as an update when it is newer than that.

`latest.json` itself is not signed, only the installer is. The plugin can
also refuse a `latest.json` that pairs a new version number with an older
(validly signed) installer, when the signatures carry their version
(`requireSignedVersion` in `plugins.updater`); that is not turned on, since
it rejects every installer signed without a version.

### Changing the key

A running launcher checks updates against the public key it was built with.
To move to a new key, publish one release signed with the old private key
but carrying the new public key (set `T3_UPDATER_PUBKEY` to the new key and
keep the old `TAURI_SIGNING_PRIVATE_KEY` for that release), then switch the
private key.

## Without the key

Forks, pull requests from forks (GitHub gives them no secrets) and a
repository without the secret or the variable build exactly as before:

- `stage_launcher.py` writes no updater section, and the installer is not
  signed for the updater (no `.sig`);
- the launcher says in Settings that this build cannot update itself and
  links to the releases page; it never contacts the endpoint;
- `release.yml` skips `latest.json` (with a notice in the run's log).

Nothing fails. Once one release had `latest.json`, though, a later release
without it leaves `releases/latest/download/latest.json` pointing at nothing:
installed launchers then see no update (the start-up check stays quiet,
"Check now" shows the error) until a signed release follows.

## Windows code signing

Windows knows nothing of the updater key. What it checks is an Authenticode
signature. An unsigned installer downloaded from the internet makes
SmartScreen show "Windows protected your PC" with "Unknown publisher", and
the user has to click **More info → Run anyway**; some antivirus programs are
also warier of unsigned installers and of a `dinput8.dll` that is not
Microsoft's. A signature names the publisher, and SmartScreen builds
reputation for that certificate over downloads. Since 2024 EV certificates no
longer skip this: EV and OV certificates build reputation the same way, so a
newly signed release may still warn at first; signing every release with the
same certificate keeps the reputation
([Tauri's notes](https://v2.tauri.app/distribute/sign/windows/)).

`release.yml` has no signing step yet. Two services fit an open-source
project:

**[SignPath Foundation](https://signpath.org/)**: free code signing for open
source projects. The certificate is the Foundation's, so the publisher shows
as "SignPath Foundation". Its [conditions](https://signpath.org/terms.html)
include an OSI-approved licence for the whole project, no proprietary
components, published releases, a code signing policy on the project's page,
and two-factor authentication for the maintainers. Ask them before applying
whether a repository that also holds a matching decompilation of a commercial
game qualifies: the signed files (the launcher and the SDK) are original code,
but they judge the project. Signing is asynchronous: the build uploads the
unsigned files as a workflow artifact, and
[`signpath/github-action-submit-signing-request`](https://docs.signpath.io/trusted-build-systems/github)
(with a `SIGNPATH_API_TOKEN` secret, the organization id and the project
and signing policy slugs) submits them, waits for approval if the policy asks
for it, and downloads the signed files. In `launcher-build.yml` this would go
after the Build step: upload the installer and the portable zip's launcher,
sign them, put the signed files back, and then make the updater signature
again with `yarn tauri signer sign --app-version <version> <installer>` (the
two secrets in its environment), because Authenticode changes the
installer's bytes and the `.sig` from the build no longer matches. The
launcher inside the installer stays unsigned this way: the bundler packs it
during `tauri build`, and only a synchronous `signCommand` (below) can sign
it there.

**[Azure Artifact Signing](https://azure.microsoft.com/en-us/products/artifact-signing)**
(formerly Trusted Signing): Microsoft's signing service, about USD 10 a month
([pricing](https://azure.microsoft.com/en-us/pricing/details/artifact-signing/)).
Identity validation is needed; at the time of writing, individual developers
qualify only in the USA and Canada, organisations in more countries. It is
synchronous, so it fits Tauri's own hook: `bundle.windows.signCommand`, which
the bundler runs on the launcher executable and on the installer before the
updater signature is made. `stage_launcher.py` would add

```json
"windows": { "signCommand": "artifact-signing-cli -e https://<region>.codesigning.azure.net -a <account> -c <profile> -d T3SDK %1" }
```

to the staged config's `bundle`, the Windows job would install
`artifact-signing-cli` (`cargo install artifact-signing-cli`), and the Build
step would get `AZURE_TENANT_ID`, `AZURE_CLIENT_ID` and `AZURE_CLIENT_SECRET`
secrets for an app registration with the signing role. Nothing else changes:
the `.sig` is made from the signed installer.

Either way, the SDK zip's `dinput8.dll` and mod DLLs can be signed the same
way before they are zipped.
