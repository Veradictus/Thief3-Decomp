# Mod format fixtures

Shared test data for the mod package format ([docs/mods.md](../../../docs/mods.md)).
`tools/t3mod.py` (Python) and the launcher (`launcher/src-tauri/src/mods.rs`,
Rust) both run over these, so the two implementations agree.

- `valid/*.json`: manifests that must be accepted.
- `invalid/*.json`: manifests that must be refused. Each has a top-level
  `"_expect"` field naming the field at fault; readers ignore unknown fields,
  so the manifest is otherwise read as is.
- `ranges.json`: `[range, version, satisfied]` triples for version ranges;
  a `null` result means the range itself is invalid.
