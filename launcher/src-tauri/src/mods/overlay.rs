// Content mods' files/ applied to the game folder (docs/mods.md, "Content:
// files/"): the last enabled mod providing a path wins; a game file is moved
// to System/mods/originals/ before it is first replaced; overlay.json records
// every placed file with its owner and SHA-256; a path no mod provides any
// more is put back (or deleted when the game had none); a placed file that
// something else changed is left alone and forgotten.
//
// Game bundles (.ibt) are special because texture packs (textures/) patch
// them in place: a change to a bundle waits (Bundles::Defer) until
// t3texpack.py has restored the bundles, and a placed bundle is only checked
// against its hash when it is about to change.
//
// overlay.json is written once, at the end, even when some files failed (a
// locked file while the game runs), so it always describes what is in place.
// A sync interrupted before that is recovered by the next one: a game file
// already equal to the mod's with its original saved is adopted, and a
// missing game file whose original is saved keeps that original.
use std::collections::{BTreeMap, HashMap, HashSet};
use std::path::{Path, PathBuf};

use serde::{Deserialize, Serialize};

use super::files::{self, HashCache};

#[derive(Clone, Debug, PartialEq, Eq, Serialize, Deserialize)]
pub struct Record {
    #[serde(rename = "mod")]
    pub owner: String,
    pub sha256: String,
    pub original: bool,
}

#[derive(Clone, Debug, PartialEq, Eq, Serialize, Deserialize)]
#[serde(default)]
pub struct Overlay {
    pub format: u32,
    pub files: BTreeMap<String, Record>,
}

impl Default for Overlay {
    fn default() -> Self {
        Overlay { format: 1, files: BTreeMap::new() }
    }
}

/// A file an enabled mod wants in the game: `rel` under the game folder,
/// copied from `path`.
#[derive(Clone, Debug)]
pub struct Source {
    pub rel: String,
    pub path: PathBuf,
    pub owner: String,
}

/// What a sync does with game bundles (.ibt) that have to change.
#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub enum Bundles {
    /// Leave them for later: the texture packs have not been restored.
    Defer,
    /// Place and restore them: t3texpack.py has just restored the bundles.
    Place,
}

#[derive(Clone, Debug, Default, Serialize)]
#[serde(rename_all = "camelCase")]
pub struct Outcome {
    /// Files copied into the game.
    pub placed: usize,
    /// Files put back from originals/ or removed.
    pub restored: usize,
    /// Placed files changed by something else: left alone, no longer tracked.
    pub changed: Vec<String>,
    /// Bundles waiting for a texture restore (Bundles::Defer).
    pub deferred: Vec<String>,
    pub errors: Vec<String>,
}

pub fn load(path: &Path) -> Overlay {
    std::fs::read_to_string(path).ok().and_then(|t| serde_json::from_str(&t).ok()).unwrap_or_default()
}

/// Paths under System/ are never content (docs/mods.md): code goes through
/// `entry`.
pub fn under_system(rel: &str) -> bool {
    rel.split('/').next().is_some_and(|first| first.eq_ignore_ascii_case("System"))
}

/// A game bundle, which texture packs patch.
pub fn is_bundle(rel: &str) -> bool {
    rel.to_ascii_lowercase().ends_with(".ibt")
}

/// The files wanted in the game, by lower-case path; later sources win.
fn wanted(desired: &[Source]) -> HashMap<String, &Source> {
    let mut want = HashMap::new();
    for src in desired.iter().filter(|s| files::check_rel(&s.rel).is_ok() && !under_system(&s.rel)) {
        want.insert(src.rel.to_lowercase(), src);
    }
    want
}

/// Whether a recorded bundle stays as it is: the same file is still wanted.
fn bundle_stays(record: &Record, src: Option<&Source>, cache: &HashCache) -> bool {
    src.is_some_and(|s| cache.sha256(&s.path).ok().flatten().as_deref() == Some(record.sha256.as_str()))
}

/// The bundles a sync would place or remove, which have to wait for a
/// texture restore.
pub fn pending_bundles(overlay_file: &Path, desired: &[Source], cache: &HashCache) -> Vec<String> {
    let overlay = load(overlay_file);
    let want = wanted(desired);
    let mut pending = Vec::new();
    let mut tracked = HashSet::new();
    for (key, record) in &overlay.files {
        tracked.insert(key.to_lowercase());
        if is_bundle(key) && !bundle_stays(record, want.get(&key.to_lowercase()).copied(), cache) {
            pending.push(key.clone());
        }
    }
    let mut new: Vec<String> = want
        .iter()
        .filter(|(lower, s)| is_bundle(&s.rel) && !tracked.contains(*lower))
        .map(|(_, s)| s.rel.clone())
        .collect();
    new.sort();
    pending.extend(new);
    pending
}

struct Sync<'a> {
    game: &'a Path,
    originals: &'a Path,
    cache: &'a HashCache,
    out: Outcome,
}

impl Sync<'_> {
    fn hash(&self, path: &Path, rel: &str) -> Result<Option<String>, String> {
        self.cache.sha256(path).map_err(|e| format!("{rel}: cannot read {}: {e}", path.display()))
    }

    fn source_hash(&self, src: &Source) -> Result<String, String> {
        self.hash(&src.path, &src.rel)?
            .ok_or_else(|| format!("{}: {} is missing from {}", src.rel, src.path.display(), src.owner))
    }

    /// Copies a mod's file over `target`.
    fn copy(&self, src: &Source, target: &Path) -> Result<(), String> {
        let result = files::copy_over(&src.path, target);
        self.cache.forget(target);
        result.map_err(|e| format!("{}: cannot copy from {}: {e}", src.rel, src.owner))
    }

    /// Puts the original back (or removes the mod's file when there was none).
    fn restore(&mut self, key: &str, record: &Record) -> Result<(), String> {
        let target = files::join_rel(self.game, key);
        let saved = files::join_rel(self.originals, key);
        let result = if record.original && saved.is_file() {
            let moved = files::move_file(&saved, &target);
            if let Some(parent) = saved.parent() {
                files::prune_empty(parent, self.originals);
            }
            moved
        } else {
            if record.original {
                self.out
                    .errors
                    .push(format!("{key}: its original was missing from originals/; removed the mod's copy"));
            }
            std::fs::remove_file(&target)
        };
        self.cache.forget(&target);
        result.map_err(|e| format!("{key}: cannot put the original back: {e}"))
    }

    /// A path the overlay already tracks, whose placed file is intact.
    fn update(
        &mut self,
        overlay: &mut Overlay,
        key: &str,
        record: &Record,
        src: Option<&Source>,
    ) -> Result<(), String> {
        let Some(src) = src else {
            self.restore(key, record)?;
            self.out.restored += 1;
            overlay.files.remove(key);
            return Ok(());
        };
        let hash = self.source_hash(src)?;
        if hash != record.sha256 {
            self.copy(src, &files::join_rel(self.game, key))?;
            self.out.placed += 1;
        }
        let updated = Record { owner: src.owner.clone(), sha256: hash, original: record.original };
        overlay.files.insert(key.to_string(), updated);
        Ok(())
    }

    /// First placement of `src` at a path the overlay does not track yet.
    fn place(&mut self, src: &Source) -> Result<Record, String> {
        let hash = self.source_hash(src)?;
        let target = files::join_rel(self.game, &src.rel);
        let saved = files::join_rel(self.originals, &src.rel);
        let moved = match self.hash(&target, &src.rel)? {
            // Left by an interrupted sync: the mod's file is in place, the original saved.
            Some(current) if current == hash && saved.is_file() => false,
            Some(_) => {
                let result = files::move_file(&target, &saved);
                self.cache.forget(&target);
                result.map_err(|e| format!("{}: cannot back up the original: {e}", src.rel))?;
                true
            }
            None => {
                self.copy(src, &target)?;
                false
            }
        };
        if moved {
            if let Err(e) = self.copy(src, &target) {
                let _ = files::move_file(&saved, &target);
                return Err(e);
            }
        }
        self.out.placed += 1;
        Ok(Record { owner: src.owner.clone(), sha256: hash, original: saved.is_file() })
    }
}

/// Makes the game folder match `desired` (in load order; later entries win).
pub fn sync(
    game: &Path,
    originals: &Path,
    overlay_file: &Path,
    desired: &[Source],
    bundles: Bundles,
    cache: &HashCache,
) -> Outcome {
    let before = load(overlay_file);
    let mut overlay = before.clone();
    let mut s = Sync { game, originals, cache, out: Outcome::default() };
    let want = wanted(desired);

    let mut tracked: HashSet<String> = HashSet::new();
    for (key, record) in &before.files {
        tracked.insert(key.to_lowercase());
        if files::check_rel(key).is_err() || under_system(key) {
            s.out.errors.push(format!("overlay.json: ignored the invalid path {key:?}"));
            overlay.files.remove(key);
            continue;
        }
        let src = want.get(&key.to_lowercase()).copied();
        if is_bundle(key) {
            if bundle_stays(record, src, cache) {
                // Possibly patched by a texture pack: not checked, not touched.
                if let Some(src) = src.filter(|s| s.owner != record.owner) {
                    overlay.files.insert(key.clone(), Record { owner: src.owner.clone(), ..record.clone() });
                }
                continue;
            }
            if bundles == Bundles::Defer {
                s.out.deferred.push(key.clone());
                continue;
            }
        }
        let current = match s.hash(&files::join_rel(game, key), key) {
            Ok(h) => h,
            Err(e) => {
                s.out.errors.push(e);
                continue;
            }
        };
        if current.as_deref() != Some(record.sha256.as_str()) {
            s.out.changed.push(format!("{key} (from {})", record.owner));
            overlay.files.remove(key);
            continue;
        }
        if let Err(e) = s.update(&mut overlay, key, record, src) {
            s.out.errors.push(e);
        }
    }

    let mut new: Vec<&Source> = want.iter().filter(|(lower, _)| !tracked.contains(*lower)).map(|(_, s)| *s).collect();
    new.sort_by(|a, b| a.rel.cmp(&b.rel));
    for src in new {
        if bundles == Bundles::Defer && is_bundle(&src.rel) {
            s.out.deferred.push(src.rel.clone());
            continue;
        }
        match s.place(src) {
            Ok(record) => {
                overlay.files.insert(src.rel.clone(), record);
            }
            Err(e) => s.out.errors.push(e),
        }
    }

    if overlay != before || (!overlay_file.exists() && !overlay.files.is_empty()) {
        let text = serde_json::to_string_pretty(&overlay).unwrap_or_default() + "\n";
        if let Err(e) = files::atomic_write(overlay_file, text.as_bytes()) {
            s.out.errors.push(e);
        }
    }
    s.out
}
