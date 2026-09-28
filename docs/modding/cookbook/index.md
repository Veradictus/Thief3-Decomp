# Mod author cookbook

Task-by-task recipes for writing a T3SDK mod: short, concrete answers to "how
do I...", each with a minimal working example. Start with
[Your first mod](../first-mod.md) if you have not built one yet; come back
here once you have something loading and want to do something specific with
it.

Every recipe links back to the [mod API reference](../../reference/api.md)
and to the mod author guide's own pages
([The mod lifecycle](../lifecycle.md), [Packaging](../packaging.md),
[Content and texture packs](../content-packs.md),
[Publishing](../publishing.md), [Map editing](../maps.md)) for the full
rules; the recipes only show how to apply them to one task.

## Getting going

- [Run code every frame](every-frame.md) — a per-frame callback, and running
  something once when the engine comes up.
- [Write to the log, and read the engine's own lines](logging.md) —
  `api->Log`, and watching the engine's own log output.
- [Find and inspect objects](objects.md) — `FindObject`, walking the object
  table, and reading a name, path or class.

## Going further

- [Hook a game function](hooks.md) — replace or wrap a documented engine
  function safely, and what to do when another mod got there first.
- [Give your mod its own settings](settings.md) — a plain INI file next to
  your DLL, with no API support needed.

## Content

- [Replace game files with a content pack](content.md) — a code-free package
  that overlays or replaces game files.
- [Map edit recipes](maps.md) — moving, rotating, scaling and editing
  properties on an existing map.

## Keeping it working

- [Debug a mod](debugging.md) — why a mod did not load, watching it run,
  reading a crash report, and attaching a debugger.
- [Play well with other mods](compatibility.md) — hook conflicts, load
  order, API versions, and what T3SDK does and does not isolate between mods.
