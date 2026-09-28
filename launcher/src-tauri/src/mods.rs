// The mod manager (docs/mods.md): .t3mod packages installed into
// System/mods/<id>/, a load order and profiles in state.json, the checks,
// and "sync", which makes the game folder match the enabled mods:
// load-order.txt for the SDK, files/ content placed with overlay.json and
// originals/, and whether the texture packs have to be applied again. Loose
// DLLs in System/mods/ keep working next to packages.
//
// Every change is saved and synced at once; the commands return the new list.
// Operations run on a blocking thread, one at a time.
//
// Texture packs (textures/) are applied by tools/assets/t3texpack.py, which
// the UI queues as tasks (tasks.rs): `apply` when the enabled packs changed,
// and, when a sync has game bundles (.ibt) to place or remove, `restore`
// first; that task's success places the bundles (place_bundles) and the
// `apply` queued after it patches them again.
mod checks;
mod files;
mod index;
mod layout;
mod manifest;
mod overlay;
mod package;
mod state;
#[cfg(test)]
mod tests;
mod version;

use std::collections::{BTreeMap, HashSet};
use std::path::{Path, PathBuf};
use std::sync::{LazyLock, Mutex, MutexGuard};

use semver::Version;
use serde::Serialize;
use tauri::{AppHandle, Emitter, State};

use crate::config::Config;
use crate::AppState;
use checks::Issue;
use files::HashCache;
use index::{Index, IndexView};
use layout::{Layout, LooseMod, Package, SdkInfo};
use package::Installed;

pub use index::DEFAULT_URL as DEFAULT_INDEX_URL;

static LOCK: Mutex<()> = Mutex::new(());
static HASHES: LazyLock<HashCache> = LazyLock::new(HashCache::default);
static INDEX: Mutex<Option<(String, Index)>> = Mutex::new(None);

fn lock() -> MutexGuard<'static, ()> {
    LOCK.lock().unwrap_or_else(|e| e.into_inner())
}

// ---- what the UI gets -----------------------------------------------------------

#[derive(Clone, Debug, Serialize)]
#[serde(rename_all = "camelCase")]
pub struct PackageView {
    pub id: String,
    pub name: String,
    pub version: Option<Version>,
    pub authors: Vec<String>,
    pub description: Option<String>,
    pub homepage: Option<String>,
    pub license: Option<String>,
    pub tags: Vec<String>,
    pub entry: Option<String>,
    pub api: Option<u32>,
    pub requires: BTreeMap<String, String>,
    pub conflicts: Vec<String>,
    /// Switched on (in state.json).
    pub enabled: bool,
    /// Enabled and without errors: in load-order.txt and the overlay.
    pub active: bool,
    /// Place in the load order, from 0.
    pub position: usize,
    pub size: u64,
    /// Has a DLL (code), files/ (content) or textures/ (texture replacements).
    pub code: bool,
    pub files: usize,
    pub textures: usize,
    /// Why the package cannot be used (unreadable or invalid mod.json).
    pub error: Option<String>,
}

#[derive(Clone, Debug, Default, PartialEq, Eq, Serialize)]
#[serde(rename_all = "camelCase")]
pub struct TextureStatus {
    /// The active texture packs differ from the ones last applied: run
    /// `t3texpack.py apply` with `mods`.
    pub needed: bool,
    /// The active packages with textures/, in load order.
    pub mods: Vec<String>,
    /// Game bundles (.ibt) that files/ mods place or remove, waiting for
    /// `t3texpack.py restore` (then the sync places them).
    pub bundles: Vec<String>,
}

#[derive(Clone, Debug, Default, Serialize)]
#[serde(rename_all = "camelCase")]
pub struct SyncReport {
    pub placed: usize,
    pub restored: usize,
    /// Placed files something else changed: left alone.
    pub changed: Vec<String>,
    pub errors: Vec<String>,
    /// Ids a profile listed that are not installed.
    pub skipped: Vec<String>,
    pub installed: Option<Installed>,
    pub removed: Option<String>,
}

#[derive(Clone, Debug, Serialize)]
#[serde(rename_all = "camelCase")]
pub struct ModList {
    pub dir: PathBuf,
    /// In load order.
    pub packages: Vec<PackageView>,
    pub loose: Vec<LooseMod>,
    pub profile: String,
    pub profiles: Vec<String>,
    pub issues: Vec<Issue>,
    pub sdk: SdkInfo,
    pub textures: TextureStatus,
    /// What the change just made did (None for a plain listing).
    pub report: Option<SyncReport>,
}

// ---- the installed mods ---------------------------------------------------------

struct Mods {
    layout: Layout,
    /// In load order.
    packages: Vec<Package>,
    state: state::State,
    sdk: SdkInfo,
}

fn open(layout: &Layout, sdk: SdkInfo) -> Mods {
    let mut packages = layout::scan(layout);
    let mut state = state::load(&layout.state());
    let ids: Vec<String> = packages.iter().map(|p| p.id.clone()).collect();
    state.normalize(&ids);
    packages.sort_by_key(|p| state.order.iter().position(|o| *o == p.id));
    Mods { layout: layout.clone(), packages, state, sdk }
}

const LOAD_ORDER_HEADER: &str = "# Written by the T3SDK launcher; the SDK loads these top to bottom.\n\
# Change the order in the launcher's Mods page: it rewrites this file.\n";

impl Mods {
    fn enabled(&self) -> HashSet<String> {
        self.state.enabled.iter().cloned().collect()
    }

    fn package(&self, id: &str) -> Option<&Package> {
        self.packages.iter().find(|p| p.id == id)
    }

    fn check(&self) -> checks::Report {
        checks::check(&self.packages, &self.enabled(), self.sdk)
    }

    /// `id@version` of each package, as state.json records applied texture packs.
    fn fingerprint(&self, ids: &[String]) -> Vec<String> {
        ids.iter()
            .map(|id| match self.package(id).and_then(Package::ok) {
                Some(m) => format!("{id}@{}", m.version),
                None => id.clone(),
            })
            .collect()
    }

    fn textures(&self, active: &[String]) -> TextureStatus {
        let mods: Vec<String> =
            active.iter().filter(|id| self.package(id).is_some_and(|p| !p.textures.is_empty())).cloned().collect();
        let bundles = overlay::pending_bundles(&self.layout.overlay(), &self.desired(active), &HASHES);
        TextureStatus { needed: self.fingerprint(&mods) != self.state.textures, mods, bundles }
    }

    /// The files/ content of `active`, in load order.
    fn desired(&self, active: &[String]) -> Vec<overlay::Source> {
        active
            .iter()
            .filter_map(|id| self.package(id))
            .flat_map(|p| {
                p.files.iter().map(|f| overlay::Source {
                    rel: f.rel.clone(),
                    path: f.path.clone(),
                    owner: p.id.clone(),
                })
            })
            .collect()
    }

    fn load_order_text(&self, active: &[String]) -> String {
        let mut text = LOAD_ORDER_HEADER.to_string();
        for p in active.iter().filter_map(|id| self.package(id)) {
            let Some(entry) = p.ok().and_then(|m| m.entry.as_deref()) else { continue };
            let dll =
                layout::find_ci(&p.dir, entry).and_then(|f| f.file_name().map(|n| n.to_string_lossy().into_owned()));
            let folder = p.dir.file_name().map_or_else(|| p.id.clone(), |n| n.to_string_lossy().into_owned());
            text.push_str(&format!("{folder}/{}\n", dll.as_deref().unwrap_or(entry)));
        }
        text
    }

    /// Saves the state and makes the game folder match it.
    fn sync(&mut self, bundles: overlay::Bundles) -> SyncReport {
        package::clean_leftovers(&self.layout);
        let check = self.check();
        let mut report = SyncReport::default();
        let order_file = self.layout.load_order();
        let text = self.load_order_text(&check.active);
        let current = std::fs::read_to_string(&order_file).ok();
        let wanted = current.is_some() || !self.packages.is_empty();
        if wanted && current.as_deref() != Some(text.as_str()) {
            if let Err(e) = files::atomic_write(&order_file, text.as_bytes()) {
                report.errors.push(e);
            }
        }

        let desired = self.desired(&check.active);
        let (game, originals) = (&self.layout.game, self.layout.originals());
        let outcome = overlay::sync(game, &originals, &self.layout.overlay(), &desired, bundles, &HASHES);
        report.placed = outcome.placed;
        report.restored = outcome.restored;
        report.changed = outcome.changed;
        report.errors.extend(outcome.errors);

        self.state.commit();
        if let Err(e) = state::save(&self.layout.state(), &self.state) {
            report.errors.push(e);
        }
        report
    }

    fn list(&self, report: Option<SyncReport>) -> ModList {
        let check = self.check();
        let enabled = self.enabled();
        let packages = self
            .packages
            .iter()
            .enumerate()
            .map(|(position, p)| {
                let m = p.ok();
                PackageView {
                    id: p.id.clone(),
                    name: m.map_or_else(|| p.id.clone(), |m| m.name.clone()),
                    version: m.map(|m| m.version.clone()),
                    authors: m.map(|m| m.authors.clone()).unwrap_or_default(),
                    description: m.and_then(|m| m.description.clone()),
                    homepage: m.and_then(|m| m.homepage.clone()),
                    license: m.and_then(|m| m.license.clone()),
                    tags: m.map(|m| m.tags.clone()).unwrap_or_default(),
                    entry: m.and_then(|m| m.entry.clone()),
                    api: m.and_then(|m| m.api),
                    requires: m.map(|m| m.requires.clone()).unwrap_or_default(),
                    conflicts: m.map(|m| m.conflicts.clone()).unwrap_or_default(),
                    enabled: enabled.contains(&p.id),
                    active: check.active.contains(&p.id),
                    position,
                    size: p.size,
                    code: p.has_code(),
                    files: p.files.len(),
                    textures: p.textures.len(),
                    error: p.manifest.as_ref().err().cloned(),
                }
            })
            .collect();
        ModList {
            dir: self.layout.dir.clone(),
            packages,
            loose: layout::loose(&self.layout),
            profile: self.state.profile.clone(),
            profiles: self.state.profiles.keys().cloned().collect(),
            issues: check.issues,
            sdk: self.sdk,
            textures: self.textures(&check.active),
            report,
        }
    }
}

// ---- operations (also used by the tests) ------------------------------------------

/// Opens the mods, applies `change` to the state, saves and syncs, and lists.
fn change(
    layout: &Layout,
    sdk: SdkInfo,
    apply: impl FnOnce(&mut Mods) -> Result<SyncReport, String>,
) -> Result<ModList, String> {
    let _guard = lock();
    let mut mods = open(layout, sdk);
    let mut report = apply(&mut mods)?;
    let synced = mods.sync(overlay::Bundles::Defer);
    report.placed += synced.placed;
    report.restored += synced.restored;
    report.changed.extend(synced.changed);
    report.errors.extend(synced.errors);
    Ok(mods.list(Some(report)))
}

pub(crate) fn list(layout: &Layout, sdk: SdkInfo) -> ModList {
    let _guard = lock();
    open(layout, sdk).list(None)
}

fn install(layout: &Layout, sdk: SdkInfo, path: &Path, expect: Option<(&str, &Version)>) -> Result<ModList, String> {
    change(layout, sdk, |mods| {
        let installed = package::install(layout, path, expect)?;
        let is_new = !mods.state.order.contains(&installed.id);
        *mods = open(layout, sdk);
        if is_new {
            mods.state.add(&installed.id);
        }
        Ok(SyncReport { installed: Some(installed), ..SyncReport::default() })
    })
}

fn remove(layout: &Layout, sdk: SdkInfo, id: &str) -> Result<ModList, String> {
    change(layout, sdk, |mods| {
        let dir = mods.package(id).map(|p| p.dir.clone()).ok_or_else(|| format!("{id} is not installed"))?;
        // Content first: its files go back to the originals before the package goes.
        // Bundles wait for the texture restore; putting them back needs only originals/.
        mods.state.set_enabled(id, false);
        let mut report = mods.sync(overlay::Bundles::Defer);
        let records = overlay::load(&layout.overlay()).files;
        let left = records.iter().filter(|(path, r)| r.owner == id && !overlay::is_bundle(path)).count();
        if left > 0 {
            return Err(format!(
                "{id} is disabled, but {left} of its files could not be put back ({}); close the game and remove it again",
                report.errors.join("; ")
            ));
        }
        let trash = files::temp_sibling(&dir, "remove");
        std::fs::rename(&dir, &trash)
            .map_err(|e| format!("cannot remove {}: {e} (is the game running?)", dir.display()))?;
        let _ = std::fs::remove_dir_all(&trash);
        mods.state.forget(id);
        mods.packages.retain(|p| p.id != id);
        report.removed = Some(id.to_string());
        Ok(report)
    })
}

fn set_enabled(layout: &Layout, sdk: SdkInfo, id: &str, enabled: bool) -> Result<ModList, String> {
    change(layout, sdk, |mods| {
        mods.package(id).ok_or_else(|| format!("{id} is not installed"))?;
        mods.state.set_enabled(id, enabled);
        Ok(SyncReport::default())
    })
}

fn set_order(layout: &Layout, sdk: SdkInfo, order: Vec<String>) -> Result<ModList, String> {
    change(layout, sdk, |mods| {
        mods.state.set_order(order)?;
        let state = &mods.state;
        mods.packages.sort_by_key(|p| state.order.iter().position(|o| *o == p.id));
        Ok(SyncReport::default())
    })
}

#[derive(Clone, Debug, serde::Deserialize)]
#[serde(tag = "kind", rename_all = "camelCase")]
pub enum ProfileAction {
    SaveAs { name: String },
    Switch { name: String },
    Delete { name: String },
    Rename { from: String, to: String },
}

fn profile(layout: &Layout, sdk: SdkInfo, action: ProfileAction) -> Result<ModList, String> {
    change(layout, sdk, |mods| {
        let mut report = SyncReport::default();
        match action {
            ProfileAction::SaveAs { name } => mods.state.save_as(&name)?,
            ProfileAction::Switch { name } => {
                // Packages the profile does not know yet keep their current order, at the end.
                let installed: Vec<String> = mods.packages.iter().map(|p| p.id.clone()).collect();
                report.skipped = mods.state.switch(&name, &installed)?;
                let state = &mods.state;
                mods.packages.sort_by_key(|p| state.order.iter().position(|o| *o == p.id));
            }
            ProfileAction::Delete { name } => mods.state.delete(&name)?,
            ProfileAction::Rename { from, to } => mods.state.rename(&from, &to)?,
        }
        Ok(report)
    })
}

// ---- texture packs (the texturePacks task in tasks.rs) ---------------------------

/// The installed folders of `ids`, for t3texpack.py's --pack arguments (it
/// uses their textures/).
pub fn texture_packs(game: &Path, ids: &[String]) -> Result<Vec<PathBuf>, String> {
    let layout = Layout::new(game);
    ids.iter()
        .map(|id| {
            if !manifest::valid_id(id) {
                return Err(format!("invalid mod id {id:?}"));
            }
            let dir = layout.package(id);
            match layout::find_ci(&dir, "textures") {
                Some(t) if t.is_dir() => Ok(dir),
                _ => Err(format!("{id} has no textures/ folder")),
            }
        })
        .collect()
}

/// What to record once `ids`' texture packs have been applied.
pub fn texture_fingerprint(game: &Path, ids: &[String]) -> Vec<String> {
    let _guard = lock();
    open(&Layout::new(game), layout::sdk_info(game, None)).fingerprint(ids)
}

/// Records in state.json that t3texpack.py applied these packs.
pub fn record_textures(game: &Path, fingerprint: Vec<String>) -> Result<(), String> {
    let _guard = lock();
    let layout = Layout::new(game);
    let mut state = state::load(&layout.state());
    state.textures = fingerprint;
    state::save(&layout.state(), &state)
}

/// After `t3texpack.py restore`: nothing is patched any more, so the sync
/// places and removes the bundles it had to leave. Returns its problems.
pub fn place_bundles(game: &Path) -> Result<(), String> {
    let _guard = lock();
    let layout = Layout::new(game);
    let mut mods = open(&layout, layout::sdk_info(game, None));
    mods.state.textures.clear();
    let report = mods.sync(overlay::Bundles::Place);
    match report.errors.is_empty() {
        true => Ok(()),
        false => Err(report.errors.join("\n")),
    }
}

/// Mods switched on and off, for the Play page: packages and loose DLLs.
pub fn counts(cfg: &Config) -> (usize, usize) {
    let Some(game) = cfg.game_dir.as_deref() else { return (0, 0) };
    let layout = Layout::new(game);
    let names = layout::package_dirs(&layout);
    let state = state::load(&layout.state());
    let on = names.iter().filter(|n| state.enabled.iter().any(|e| e.eq_ignore_ascii_case(n))).count();
    let loose = layout::loose(&layout);
    let loose_on = loose.iter().filter(|m| m.enabled).count();
    (on + loose_on, names.len() - on + loose.len() - loose_on)
}

// ---- commands -------------------------------------------------------------------

fn context(state: &State<'_, AppState>) -> Result<(Layout, SdkInfo, Config), String> {
    let cfg = state.config.lock().unwrap().clone();
    let game = cfg.game()?;
    Ok((Layout::new(&game), layout::sdk_info(&game, cfg.sdk_root.as_deref()), cfg))
}

async fn blocking<T: Send + 'static>(work: impl FnOnce() -> Result<T, String> + Send + 'static) -> Result<T, String> {
    tauri::async_runtime::spawn_blocking(work).await.map_err(|e| e.to_string())?
}

#[tauri::command]
pub async fn list_mods(state: State<'_, AppState>) -> Result<ModList, String> {
    let (layout, sdk, _) = context(&state)?;
    blocking(move || Ok(list(&layout, sdk))).await
}

/// Switches a loose DLL on or off (moves it in or out of System/mods/disabled).
#[tauri::command]
pub async fn set_mod_enabled(state: State<'_, AppState>, name: String, enabled: bool) -> Result<ModList, String> {
    let (layout, sdk, _) = context(&state)?;
    blocking(move || {
        layout::set_loose_enabled(&layout, &name, enabled)?;
        Ok(list(&layout, sdk))
    })
    .await
}

#[tauri::command]
pub async fn set_package_enabled(state: State<'_, AppState>, id: String, enabled: bool) -> Result<ModList, String> {
    let (layout, sdk, _) = context(&state)?;
    blocking(move || set_enabled(&layout, sdk, &id, enabled)).await
}

#[tauri::command]
pub async fn set_mod_order(state: State<'_, AppState>, order: Vec<String>) -> Result<ModList, String> {
    let (layout, sdk, _) = context(&state)?;
    blocking(move || set_order(&layout, sdk, order)).await
}

#[tauri::command]
pub async fn install_mod(state: State<'_, AppState>, path: PathBuf) -> Result<ModList, String> {
    let (layout, sdk, _) = context(&state)?;
    blocking(move || install(&layout, sdk, &path, None)).await
}

#[tauri::command]
pub async fn remove_mod(state: State<'_, AppState>, id: String) -> Result<ModList, String> {
    let (layout, sdk, _) = context(&state)?;
    blocking(move || remove(&layout, sdk, &id)).await
}

/// Applies the current state again (after files were changed by hand).
#[tauri::command]
pub async fn sync_mods(state: State<'_, AppState>) -> Result<ModList, String> {
    let (layout, sdk, _) = context(&state)?;
    blocking(move || change(&layout, sdk, |_| Ok(SyncReport::default()))).await
}

#[tauri::command]
pub async fn mod_profile(state: State<'_, AppState>, action: ProfileAction) -> Result<ModList, String> {
    let (layout, sdk, _) = context(&state)?;
    blocking(move || profile(&layout, sdk, action)).await
}

fn index_url(cfg: &Config) -> String {
    cfg.mod_index_url.clone().filter(|u| !u.trim().is_empty()).unwrap_or_else(|| DEFAULT_INDEX_URL.to_string())
}

fn cached_index(url: &str, refresh: bool) -> Result<Index, String> {
    if !refresh {
        if let Some((cached_url, index)) = INDEX.lock().unwrap().as_ref() {
            if cached_url == url {
                return Ok(index.clone());
            }
        }
    }
    let index = index::fetch(url)?;
    *INDEX.lock().unwrap() = Some((url.to_string(), index.clone()));
    Ok(index)
}

/// The mod index compared with the installed mods (fetched once per session,
/// or again with `refresh`).
#[tauri::command]
pub async fn mod_index(state: State<'_, AppState>, refresh: bool) -> Result<IndexView, String> {
    let (layout, sdk, cfg) = context(&state)?;
    let url = index_url(&cfg);
    blocking(move || {
        let index = cached_index(&url, refresh)?;
        let _guard = lock();
        let mods = open(&layout, sdk);
        Ok(index::view(&url, &index, &mods.packages, &mods.enabled(), sdk))
    })
    .await
}

#[derive(Clone, Debug, Serialize)]
#[serde(rename_all = "camelCase")]
struct DownloadProgress {
    id: String,
    received: u64,
    total: u64,
}

/// Downloads a version listed in the index, checks it, and installs it.
#[tauri::command]
pub async fn install_from_index(
    app: AppHandle,
    state: State<'_, AppState>,
    id: String,
    version: String,
) -> Result<ModList, String> {
    let (layout, sdk, cfg) = context(&state)?;
    let url = index_url(&cfg);
    blocking(move || {
        let index = cached_index(&url, false)?;
        let wanted = Version::parse(&version).map_err(|e| format!("{version}: {e}"))?;
        let entry = index
            .find(&id)
            .and_then(|m| m.versions.iter().find(|v| v.version == wanted))
            .ok_or_else(|| format!("{id} {version} is not in the mod index"))?
            .clone();
        std::fs::create_dir_all(&layout.dir).map_err(|e| format!("cannot create {}: {e}", layout.dir.display()))?;
        let temp = files::temp_sibling(&layout.dir.join(format!("{id}-{version}.t3mod")), "download");
        let mut last = 0;
        let downloaded = index::download(&entry, &temp, |received, total| {
            if received == total || received - last >= total / 100 {
                last = received;
                let _ = app.emit("mod-download", DownloadProgress { id: id.clone(), received, total });
            }
        });
        let result = downloaded.and_then(|()| install(&layout, sdk, &temp, Some((&id, &wanted))));
        let _ = std::fs::remove_file(&temp);
        result
    })
    .await
}
