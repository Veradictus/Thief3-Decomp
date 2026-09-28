# Installing mods

Mods come as `.t3mod` files. A package can hold code (a DLL that T3SDK loads
into the game), content (files that replace or add game files, such as a
texture pack), or both. The launcher's **Mods** page installs packages, turns
them on and off, keeps their load order and saves sets of mods as profiles.

Code mods need T3SDK installed (see [Playing with T3SDK](playing.md));
content mods do not. [Back up your saves](saves.md) before you try a mod.

> [!WARNING]
> Only install mods you trust. A mod's DLL is a program: it runs inside the
> game with the same rights as you. The mod index checks that its entries are
> well formed; nobody reviews what the mods do.

## Install a package

Drag a `.t3mod` file onto the launcher window, or add it from the **Mods**
page. The launcher reads the package's manifest (`mod.json`), refuses a
package that is broken or unsafe to unpack, and installs it into its own
folder, `System\mods\<id>\`. A new mod goes to the end of the load order.

## The mod browser

The browser lists the mods published in the [mod index](../modding/publishing.md),
with their descriptions, versions and requirements. Pick one to download and
install it.

Mods are downloaded from their authors' own release pages; the index only
lists them. Before it opens a download, the launcher checks its size and
SHA-256 against the index, and that the package's manifest names the same
mod and version. A mismatch is refused.

## Turning mods on and off

Each installed mod can be switched on or off. For code mods this changes
which DLLs T3SDK loads. For content mods the launcher copies the mod's files
into the game folder, and puts the game's original files back when you turn
the mod off. Changes take effect the next time the game starts.

## Load order

Mods load from the top of the list to the bottom. When two mods provide the
same file, the one lower in the list wins. The launcher checks the mods that
are on:

| Problem | What happens |
|---|---|
| A mod needs another mod that is missing, off, or the wrong version | Error: the mod stays off until it is fixed. |
| A mod needs another mod that loads after it | Warning, with an action that fixes the order. |
| Two mods that conflict with each other are both on | Error. |
| A mod needs a newer SDK than the one installed | Warning: the mod may refuse to load. Update the launcher and install T3SDK again. |
| A code mod is on but T3SDK is not installed | Warning. |
| Two mods provide the same file | Information: the later one wins. |

## Profiles

A profile is a saved set of mods: which ones are on, and in which order.
Switching profiles applies the whole set at once, for example a "Vanilla"
profile with every mod off. Mods named in a profile that are not installed
are skipped, and the launcher tells you which.

## Loose DLLs

A mod DLL put straight into `System\mods` still loads, after the packaged
mods. The launcher lists it as a loose mod that can be switched off (it moves
to `System\mods\disabled`). A loose DLL has no manifest, so there are no
requirement or conflict checks for it.

## Texture packs

Texture packs come in two kinds:

- **Packs for Sneaky Upgrade.** Most texture and material packs replace files
  in [Sneaky Upgrade](https://www.moddb.com/mods/thief-3-sneaky-upgrade)'s
  override folders (`Content\T3\PCTextures\DynamicallyLoaded` and
  `Content\T3\MatLib\DynamicallyLoaded`). They need Sneaky Upgrade installed;
  the mod's description should say so.
- **Packs that replace textures inside the game's bundles** (experimental).
  These work without Sneaky Upgrade: the textures are written into the
  game's `.ibt` files. The bundles are always rewritten from a backup of the
  originals, so turning packs off or changing their order never stacks
  changes. It is experimental because it has not yet been confirmed in the
  game that the engine accepts the rewritten bundles.

## Removing mods

Uninstalling a mod deletes its folder in `System\mods` and puts back any game
files it had replaced. If something else changed one of those files since
the mod placed it, the launcher leaves that file alone and tells you.

How packages, the load order and the files in `System\mods` work in detail
is in the [package specification](../mods.md).
