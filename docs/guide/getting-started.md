# Getting started

You need:

- **Thief: Deadly Shadows from Steam**, installed. T3SDK supports the Steam
  release (patch 1.1); other releases are detected and left alone (see
  [Unsupported builds](troubleshooting.md#unsupported-builds)).
- **Windows 10 or 11**, 64-bit.

Nothing else: the launcher brings its own copy of the tools, the SDK and
Python. Godot is only needed to edit maps.

## Download the launcher

Take one of these from the
[latest release](https://github.com/Veradictus/Thief3-Decomp/releases/latest):

| File | What it is |
|---|---|
| `T3SDK-Launcher_<version>_x64-setup.exe` | The installer. It installs for your user only and needs no admin rights. |
| `T3SDK-Launcher_<version>_portable.zip` | The same files, to unzip into any folder and run from there. |

The installer is not code-signed, so Windows may warn about an unknown
publisher. Choose **More info**, then **Run anyway**.

## First run

The first time it starts, the launcher opens its setup screen. It looks for
each of these by itself and checks what it finds:

| What | Where it looks | What it checks |
|---|---|---|
| The game | the game installer's registry entry, your Steam libraries, `T3_GAME_DIR` | that `T3Main.exe` is the supported Steam build (by its SHA-1) |
| The T3SDK folder | the copy that comes with the launcher | that the tools are there |
| Python | the copy that comes with the launcher, then others on your PC | Python 3.10 or newer |
| Godot | `GODOT`, `PATH`, common install folders | Godot 4.7 or newer (optional: map editing only) |

When the entries show **OK**, click **Continue**. If the game is not found,
pick its folder: the one that holds the `System` and `Content` folders. You
can change every path later under **Settings**.

A game that fails the check still starts, but T3SDK leaves it alone. The
**Play** page shows whether your build is supported.

## Updates

The launcher checks the project's GitHub Releases for a newer version and
offers to install it. You can also download a newer release yourself and
install it over the old one. Each release lists its changes on the
[Releases page](https://github.com/Veradictus/Thief3-Decomp/releases).

## Next

- [Playing with T3SDK](playing.md): install the SDK, and what its fixes do.
- [Installing mods](mods.md): packages, the mod browser, load order and
  profiles.
- [Save backups](saves.md): do this before you try mods.
- [Settings explained](settings.md): every setting T3SDK and the launcher
  have, and when to change it.
- [Other mods and tools](compatibility.md), the [FAQ](faq.md) and the
  [glossary](glossary.md).
