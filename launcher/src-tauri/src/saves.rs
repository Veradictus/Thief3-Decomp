// Backups of the game's saved games: finding its SaveGames folder, zipping it
// into the launcher's per-user data folder, and putting a backup back.
//
// The game reads its save folder from the SaveGamePath value of its registry
// key and keeps the saves in SaveGames inside it; the installer points that at
// the user's Documents, and Windows or the store versions may leave the saves
// in Public Documents or the game folder instead (docs/launcher.md, "Saves").
// So every known place is looked at, and the one with the newest save wins,
// unless Settings names a folder.
use std::fs::{self, File};
use std::io::{self, Read, Write};
use std::path::{Path, PathBuf};
use std::time::{SystemTime, UNIX_EPOCH};

use chrono::{DateTime, Datelike, Local, TimeZone, Timelike};
use serde::{Deserialize, Serialize};
use tauri::{AppHandle, Manager, State};
use tauri_plugin_opener::OpenerExt;
use zip::write::SimpleFileOptions;

use crate::config::Config;
use crate::AppState;

/// The folder the game creates under Documents (and under SaveGamePath).
const GAME_FOLDER: &str = "Thief - Deadly Shadows";
const SAVE_GAMES: &str = "SaveGames";
/// The game's copy of the save being played; not a save slot of its own.
const CURRENT_SAVE: &str = "Current Save";
/// The zip entry that describes a backup; never restored into the saves.
const META: &str = ".t3sdk-backup.json";
pub const BEFORE_RESTORE: &str = "before restore";
pub const BEFORE_LAUNCH: &str = "before launch";
/// Automatic backups kept per label; older ones are deleted.
const KEEP_AUTOMATIC: usize = 10;

#[derive(Clone, Debug, Serialize)]
#[serde(rename_all = "camelCase")]
pub struct SavesFolder {
    pub path: PathBuf,
    /// Where the path came from: "Settings", "SaveGamePath (registry)", "Documents"...
    pub source: String,
    pub exists: bool,
}

#[derive(Clone, Debug, Default, PartialEq, Serialize)]
#[serde(rename_all = "camelCase")]
pub struct SavesSummary {
    /// Save slots: the folders in SaveGames other than "Current Save".
    pub count: usize,
    pub files: usize,
    /// Bytes, all files.
    pub size: u64,
    /// Newest file's modification time (Unix seconds).
    pub newest: Option<u64>,
}

#[derive(Debug, Serialize)]
#[serde(rename_all = "camelCase")]
pub struct SavesInfo {
    /// The saves folder in use; None when no candidate exists yet.
    pub folder: Option<SavesFolder>,
    pub exists: bool,
    pub summary: SavesSummary,
    /// Every place looked at, most likely first.
    pub candidates: Vec<SavesFolder>,
}

#[derive(Clone, Debug, Serialize)]
#[serde(rename_all = "camelCase")]
pub struct Backup {
    /// File name in the backups folder: the backup's id.
    pub file: String,
    pub label: Option<String>,
    /// Unix seconds.
    pub created: i64,
    pub saves: Option<usize>,
    /// The saves' size, uncompressed.
    pub size: Option<u64>,
    /// The zip's size.
    pub bytes: u64,
}

#[derive(Debug, Serialize)]
#[serde(rename_all = "camelCase")]
pub struct BackupList {
    pub dir: PathBuf,
    pub backups: Vec<Backup>,
}

#[derive(Debug, Serialize)]
#[serde(rename_all = "camelCase")]
pub struct Restored {
    /// The automatic backup of the saves that were replaced, if there were any.
    pub before: Option<Backup>,
    pub summary: SavesSummary,
}

/// What a backup zip says about itself (the META entry).
#[derive(Debug, Default, Serialize, Deserialize)]
#[serde(rename_all = "camelCase", default)]
struct Meta {
    format: u32,
    created: i64,
    label: Option<String>,
    saves: usize,
    files: usize,
    size: u64,
    newest: Option<u64>,
    source: String,
}

// ---- finding the saves ------------------------------------------------------------

fn mtime(meta: &fs::Metadata) -> Option<u64> {
    Some(meta.modified().ok()?.duration_since(UNIX_EPOCH).ok()?.as_secs())
}

fn walk(dir: &Path, visit: &mut dyn FnMut(&Path, &fs::Metadata)) {
    let Ok(entries) = fs::read_dir(dir) else { return };
    let mut entries: Vec<_> = entries.flatten().collect();
    entries.sort_by_key(|e| e.file_name());
    for e in entries {
        let Ok(meta) = e.metadata() else { continue };
        let path = e.path();
        if meta.is_dir() {
            visit(&path, &meta);
            walk(&path, visit);
        } else if meta.is_file() {
            visit(&path, &meta);
        }
    }
}

pub fn summarize(dir: &Path) -> SavesSummary {
    let mut summary = SavesSummary::default();
    if let Ok(entries) = fs::read_dir(dir) {
        summary.count = entries
            .flatten()
            .filter(|e| e.file_type().is_ok_and(|t| t.is_dir()))
            .filter(|e| !e.file_name().to_string_lossy().eq_ignore_ascii_case(CURRENT_SAVE))
            .count();
    }
    walk(dir, &mut |_, meta| {
        if meta.is_file() {
            summary.files += 1;
            summary.size += meta.len();
            summary.newest = summary.newest.max(mtime(meta));
        }
    });
    summary
}

/// SaveGamePath from the game's registry key, as the installer wrote it.
#[cfg(windows)]
fn registry_save_path() -> Option<PathBuf> {
    use winreg::enums::{HKEY_LOCAL_MACHINE, KEY_READ, KEY_WOW64_32KEY, KEY_WOW64_64KEY};
    use winreg::RegKey;
    [KEY_WOW64_32KEY, KEY_WOW64_64KEY].into_iter().find_map(|view| {
        let key = RegKey::predef(HKEY_LOCAL_MACHINE)
            .open_subkey_with_flags(r"SOFTWARE\Ion Storm\Thief - Deadly Shadows", KEY_READ | view)
            .ok()?;
        let path: String = key.get_value("SaveGamePath").ok()?;
        Some(PathBuf::from(path.trim())).filter(|p| !p.as_os_str().is_empty())
    })
}

#[cfg(not(windows))]
fn registry_save_path() -> Option<PathBuf> {
    None
}

/// Windows gives a legacy 32-bit program that writes under Program Files or
/// ProgramData without admin rights a per-user copy in VirtualStore instead.
#[cfg(windows)]
fn virtual_store(path: &Path) -> Option<PathBuf> {
    use std::path::Component;
    let text = path.to_string_lossy().to_lowercase();
    let protected = ["ProgramFiles", "ProgramFiles(x86)", "ProgramData"]
        .iter()
        .filter_map(|v| std::env::var(v).ok())
        .any(|root| text.starts_with(&root.to_lowercase()));
    if !protected {
        return None;
    }
    let rest: PathBuf = path.components().filter(|c| !matches!(c, Component::Prefix(_) | Component::RootDir)).collect();
    Some(dirs::data_local_dir()?.join("VirtualStore").join(rest))
}

#[cfg(not(windows))]
fn virtual_store(_: &Path) -> Option<PathBuf> {
    None
}

/// Every place the game may keep its saves, most likely first.
pub fn candidates(game_dir: Option<&Path>) -> Vec<SavesFolder> {
    let mut list = Vec::new();
    let mut add = |path: PathBuf, source: &str| {
        if !list.iter().any(|c: &SavesFolder| c.path == path) {
            list.push(SavesFolder { exists: path.is_dir(), path, source: source.to_string() });
        }
    };
    if let Some(root) = registry_save_path() {
        add(root.join(SAVE_GAMES), "SaveGamePath (registry)");
    }
    if let Some(docs) = dirs::document_dir() {
        add(docs.join(GAME_FOLDER).join(SAVE_GAMES), "Documents");
    }
    if cfg!(windows) {
        // Where the game ends up writing on Vista and later for many installs
        // (also reachable as C:\ProgramData\Documents, a link to it).
        if let Some(public) = dirs::public_dir() {
            add(public.join("Documents").join(GAME_FOLDER).join(SAVE_GAMES), "Public Documents");
        }
    }
    if let Some(game) = game_dir {
        add(game.join("save").join(SAVE_GAMES), "game folder");
    }
    let stores: Vec<SavesFolder> = list
        .iter()
        .filter_map(|c| {
            virtual_store(&c.path).map(|path| SavesFolder {
                exists: path.is_dir(),
                path,
                source: format!("{} (VirtualStore)", c.source),
            })
        })
        .collect();
    list.extend(stores);
    list
}

/// The existing candidate with the newest save (the first one on a tie).
fn pick(candidates: &[SavesFolder]) -> Option<(SavesFolder, SavesSummary)> {
    let mut best: Option<(SavesFolder, SavesSummary)> = None;
    for c in candidates.iter().filter(|c| c.exists) {
        let summary = summarize(&c.path);
        if best.as_ref().is_none_or(|(_, b)| summary.newest > b.newest) {
            best = Some((c.clone(), summary));
        }
    }
    best
}

/// The saves folder: the one set in Settings, else the best candidate.
pub fn locate(cfg: &Config) -> SavesInfo {
    let candidates = candidates(cfg.game_dir.as_deref());
    if let Some(dir) = cfg.saves_dir.clone().filter(|d| !d.as_os_str().is_empty()) {
        let exists = dir.is_dir();
        let summary = if exists { summarize(&dir) } else { SavesSummary::default() };
        let folder = SavesFolder { path: dir, source: "Settings".into(), exists };
        return SavesInfo { folder: Some(folder), exists, summary, candidates };
    }
    match pick(&candidates) {
        Some((folder, summary)) => SavesInfo { folder: Some(folder), exists: true, summary, candidates },
        None => SavesInfo { folder: None, exists: false, summary: SavesSummary::default(), candidates },
    }
}

// ---- backup names -----------------------------------------------------------------

/// A label as part of a file name: no characters Windows forbids, one line,
/// at most 60 characters.
pub fn clean_label(label: &str) -> String {
    let spaced: String =
        label.chars().map(|c| if c.is_control() || r#"<>:"/\|?*"#.contains(c) { ' ' } else { c }).collect();
    let words = spaced.split_whitespace().collect::<Vec<_>>().join(" ");
    let short: String = words.chars().take(60).collect();
    short.trim_end_matches(['.', ' ']).to_string()
}

fn stamp(now: &DateTime<Local>) -> String {
    now.format("%Y-%m-%d_%H%M%S").to_string()
}

/// "<YYYY-MM-DD_HHMMSS>[ <label>].zip", with " (2)" and so on when that
/// name is taken.
fn unique_name(dir: &Path, now: &DateTime<Local>, label: &str) -> String {
    let base = if label.is_empty() { stamp(now) } else { format!("{} {label}", stamp(now)) };
    let mut name = format!("{base}.zip");
    let mut n = 2;
    while dir.join(&name).exists() {
        name = format!("{base} ({n}).zip");
        n += 1;
    }
    name
}

/// The time and label in a backup's file name; None for other files.
pub fn parse_name(file: &str) -> Option<(i64, Option<String>)> {
    let stem = file.strip_suffix(".zip")?;
    let (time, rest) = if stem.len() > 17 { stem.split_at_checked(17)? } else { (stem, "") };
    let naive = chrono::NaiveDateTime::parse_from_str(time, "%Y-%m-%d_%H%M%S").ok()?;
    let created = Local.from_local_datetime(&naive).earliest()?.timestamp();
    if !rest.is_empty() && !rest.starts_with(' ') {
        return None;
    }
    let mut label = rest.trim();
    // Drop the " (2)" of a name that was taken.
    if let Some(open) = label.rfind(" (") {
        let n = &label[open + 2..];
        if n.strip_suffix(')').is_some_and(|d| !d.is_empty() && d.bytes().all(|b| b.is_ascii_digit())) {
            label = &label[..open];
        }
    } else if label.starts_with('(')
        && label.ends_with(')')
        && label[1..label.len() - 1].bytes().all(|b| b.is_ascii_digit())
    {
        label = "";
    }
    Some((created, Some(label.to_string()).filter(|l| !l.is_empty())))
}

/// A backup file name from the UI: a plain name in the backups folder.
fn check_file(file: &str) -> Result<(), String> {
    if file.is_empty() || file.contains(['/', '\\', ':']) || file.starts_with('.') || !file.ends_with(".zip") {
        return Err(format!("invalid backup name {file:?}"));
    }
    Ok(())
}

// ---- backups ----------------------------------------------------------------------

pub(crate) fn zip_time(time: SystemTime) -> zip::DateTime {
    let local: DateTime<Local> = time.into();
    let (Ok(year), Ok(month), Ok(day), Ok(hour), Ok(minute), Ok(second)) = (
        u16::try_from(local.year()),
        u8::try_from(local.month()),
        u8::try_from(local.day()),
        u8::try_from(local.hour()),
        u8::try_from(local.minute()),
        u8::try_from(local.second()),
    ) else {
        return zip::DateTime::default();
    };
    zip::DateTime::from_date_and_time(year, month, day, hour, minute, second).unwrap_or_default()
}

fn system_time(time: zip::DateTime) -> Option<SystemTime> {
    let local = Local
        .with_ymd_and_hms(
            time.year().into(),
            time.month().into(),
            time.day().into(),
            time.hour().into(),
            time.minute().into(),
            time.second().into(),
        )
        .earliest()?;
    Some(local.into())
}

fn read_meta(path: &Path) -> Option<Meta> {
    let mut archive = zip::ZipArchive::new(File::open(path).ok()?).ok()?;
    let mut entry = archive.by_name(META).ok()?;
    let mut text = String::new();
    entry.read_to_string(&mut text).ok()?;
    serde_json::from_str(&text).ok()
}

fn describe(path: &Path) -> Option<Backup> {
    let file = path.file_name()?.to_string_lossy().into_owned();
    let (created, label) = parse_name(&file)?;
    let meta = read_meta(path);
    Some(Backup {
        file,
        label,
        created: meta.as_ref().map_or(created, |m| m.created),
        saves: meta.as_ref().map(|m| m.saves),
        size: meta.as_ref().map(|m| m.size),
        bytes: fs::metadata(path).map(|m| m.len()).unwrap_or(0),
    })
}

/// The backups in `dir`, newest first.
pub fn list_backups(dir: &Path) -> Vec<Backup> {
    let Ok(entries) = fs::read_dir(dir) else { return Vec::new() };
    let mut list: Vec<Backup> = entries.flatten().filter_map(|e| describe(&e.path())).collect();
    list.sort_by(|a, b| b.created.cmp(&a.created).then_with(|| b.file.cmp(&a.file)));
    list
}

/// Zips the whole saves folder into `dir` as <time>[ <label>].zip.
pub fn create_backup(saves: &Path, dir: &Path, label: &str, now: &DateTime<Local>) -> Result<Backup, String> {
    if !saves.is_dir() {
        return Err(format!("there is no saves folder at {}", saves.display()));
    }
    let summary = summarize(saves);
    if summary.files == 0 {
        return Err("there are no saves to back up yet".into());
    }
    fs::create_dir_all(dir).map_err(|e| format!("cannot create {}: {e}", dir.display()))?;
    let label = clean_label(label);
    let name = unique_name(dir, now, &label);
    let target = dir.join(&name);
    // Written under another name first, so an interrupted backup is never listed.
    let partial = dir.join(format!("{name}.partial"));
    let written = write_zip(saves, &partial, &summary, &label, now);
    if let Err(e) = written.and_then(|_| fs::rename(&partial, &target)) {
        let _ = fs::remove_file(&partial);
        return Err(format!("cannot write {}: {e}", target.display()));
    }
    describe(&target).ok_or_else(|| format!("cannot read back {}", target.display()))
}

fn write_zip(saves: &Path, out: &Path, summary: &SavesSummary, label: &str, now: &DateTime<Local>) -> io::Result<()> {
    let mut zip = zip::ZipWriter::new(File::create(out)?);
    let options = SimpleFileOptions::default().compression_method(zip::CompressionMethod::Deflated);
    let mut failed: Option<io::Error> = None;
    walk(saves, &mut |path, meta| {
        if failed.is_some() {
            return;
        }
        let Ok(rel) = path.strip_prefix(saves) else { return };
        let name = rel.to_string_lossy().replace('\\', "/");
        let options = options.last_modified_time(meta.modified().map(zip_time).unwrap_or_default());
        let result = if meta.is_dir() {
            zip.add_directory(name, options).map_err(io::Error::other)
        } else {
            zip.start_file(name, options)
                .map_err(io::Error::other)
                .and_then(|()| io::copy(&mut File::open(path)?, &mut zip).map(|_| ()))
        };
        if let Err(e) = result {
            failed = Some(io::Error::new(e.kind(), format!("{}: {e}", path.display())));
        }
    });
    if let Some(e) = failed {
        return Err(e);
    }
    let meta = Meta {
        format: 1,
        created: now.timestamp(),
        label: Some(label.to_string()).filter(|l| !l.is_empty()),
        saves: summary.count,
        files: summary.files,
        size: summary.size,
        newest: summary.newest,
        source: saves.to_string_lossy().into_owned(),
    };
    zip.start_file(META, options).map_err(io::Error::other)?;
    zip.write_all(serde_json::to_string_pretty(&meta).map_err(io::Error::other)?.as_bytes())?;
    zip.finish().map_err(io::Error::other)?.sync_all()
}

/// Deletes all but the newest KEEP_AUTOMATIC backups that carry `label`.
fn prune(dir: &Path, label: &str) {
    let mut seen = 0;
    for b in list_backups(dir) {
        if b.label.as_deref() == Some(label) {
            seen += 1;
            if seen > KEEP_AUTOMATIC {
                let _ = fs::remove_file(dir.join(&b.file));
            }
        }
    }
}

/// An automatic backup (before a restore or a launch): Some((backup, true))
/// when one was written, Some((last, false)) when the newest backup already
/// holds these saves, None when there are no saves.
pub fn auto_backup(
    saves: &Path,
    dir: &Path,
    label: &str,
    now: &DateTime<Local>,
) -> Result<Option<(Backup, bool)>, String> {
    let summary = summarize(saves);
    if summary.files == 0 {
        return Ok(None);
    }
    if let Some(last) = list_backups(dir).into_iter().next() {
        let meta = read_meta(&dir.join(&last.file)).unwrap_or_default();
        let same = meta.files == summary.files && meta.size == summary.size && meta.newest == summary.newest;
        if same && Path::new(&meta.source) == saves {
            return Ok(Some((last, false)));
        }
    }
    let backup = create_backup(saves, dir, label, now)?;
    prune(dir, label);
    Ok(Some((backup, true)))
}

fn sibling(saves: &Path, suffix: &str) -> Option<PathBuf> {
    let name = saves.file_name()?.to_string_lossy();
    Some(saves.with_file_name(format!("{name}.{suffix}")))
}

fn extract(archive: &mut zip::ZipArchive<File>, into: &Path) -> Result<(), String> {
    for i in 0..archive.len() {
        let mut entry = archive.by_index(i).map_err(|e| e.to_string())?;
        let rel = entry.enclosed_name().ok_or_else(|| format!("unsafe path in the backup: {}", entry.name()))?;
        if rel == Path::new(META) {
            continue;
        }
        let target = into.join(&rel);
        if entry.is_dir() {
            fs::create_dir_all(&target).map_err(|e| format!("cannot create {}: {e}", target.display()))?;
            continue;
        }
        if let Some(parent) = target.parent() {
            fs::create_dir_all(parent).map_err(|e| format!("cannot create {}: {e}", parent.display()))?;
        }
        let modified = entry.last_modified().and_then(system_time);
        let mut out = File::create(&target).map_err(|e| format!("cannot create {}: {e}", target.display()))?;
        io::copy(&mut entry, &mut out).map_err(|e| format!("cannot write {}: {e}", target.display()))?;
        if let Some(time) = modified {
            let _ = out.set_modified(time);
        }
    }
    Ok(())
}

/// Replaces the saves folder with a backup's contents: first an automatic
/// backup of the current saves, then the backup is unpacked next to the
/// folder and swapped in, so a failure leaves the current saves in place.
pub fn restore_backup(saves: &Path, dir: &Path, file: &str, now: &DateTime<Local>) -> Result<Restored, String> {
    check_file(file)?;
    let zip_path = dir.join(file);
    let mut archive = File::open(&zip_path)
        .map_err(|e| format!("cannot open {}: {e}", zip_path.display()))
        .and_then(|f| zip::ZipArchive::new(f).map_err(|e| format!("{file} is not a readable zip: {e}")))?;
    if let Some(bad) = (0..archive.len()).find(|&i| archive.by_index(i).map_or(true, |e| e.enclosed_name().is_none())) {
        return Err(format!("{file} holds an unsafe path (entry {bad}); not restoring it"));
    }
    let before = if saves.is_dir() { auto_backup(saves, dir, BEFORE_RESTORE, now)?.map(|(b, _)| b) } else { None };

    let (Some(incoming), Some(outgoing)) = (sibling(saves, "t3sdk-restore"), sibling(saves, "t3sdk-old")) else {
        return Err(format!("{} is not a folder path", saves.display()));
    };
    for leftover in [&incoming, &outgoing] {
        if leftover.exists() {
            fs::remove_dir_all(leftover).map_err(|e| format!("cannot remove {}: {e}", leftover.display()))?;
        }
    }
    fs::create_dir_all(&incoming).map_err(|e| format!("cannot create {}: {e}", incoming.display()))?;
    if let Err(e) = extract(&mut archive, &incoming) {
        let _ = fs::remove_dir_all(&incoming);
        return Err(e);
    }
    if saves.exists() {
        if let Err(e) = fs::rename(saves, &outgoing) {
            let _ = fs::remove_dir_all(&incoming);
            return Err(format!("cannot move the current saves aside (is a file in them open?): {e}"));
        }
    }
    if let Err(e) = fs::rename(&incoming, saves) {
        let _ = fs::remove_dir_all(&incoming);
        if outgoing.exists() && fs::rename(&outgoing, saves).is_err() {
            return Err(format!(
                "cannot put the backup in place ({e}); the saves it replaced are in {}",
                outgoing.display()
            ));
        }
        return Err(format!("cannot put the backup in place: {e}"));
    }
    let _ = fs::remove_dir_all(&outgoing);
    Ok(Restored { before, summary: summarize(saves) })
}

pub fn delete_backup(dir: &Path, file: &str) -> Result<(), String> {
    check_file(file)?;
    let path = dir.join(file);
    fs::remove_file(&path).map_err(|e| format!("cannot delete {}: {e}", path.display()))
}

// ---- commands ---------------------------------------------------------------------

fn config(state: &State<'_, AppState>) -> Config {
    state.config.lock().unwrap().clone()
}

/// Backups live in the per-user local app data (…\org.t3sdk.launcher\saves).
pub fn backups_dir(app: &AppHandle) -> Result<PathBuf, String> {
    app.path().app_local_data_dir().map(|d| d.join("saves")).map_err(|e| format!("no per-user data folder: {e}"))
}

fn saves_folder(cfg: &Config) -> Result<PathBuf, String> {
    locate(cfg).folder.map(|f| f.path).ok_or_else(|| {
        "the game's saves folder was not found: save a game first, or set the folder in Settings".to_string()
    })
}

async fn blocking<T: Send + 'static>(work: impl FnOnce() -> Result<T, String> + Send + 'static) -> Result<T, String> {
    tauri::async_runtime::spawn_blocking(work).await.map_err(|e| e.to_string())?
}

/// The saves folder in use and what it holds; with `path`, that folder
/// instead (the Settings field's check).
#[tauri::command]
pub async fn saves_info(state: State<'_, AppState>, path: Option<PathBuf>) -> Result<SavesInfo, String> {
    let mut cfg = config(&state);
    if let Some(p) = path {
        cfg.saves_dir = Some(p);
    }
    blocking(move || Ok(locate(&cfg))).await
}

#[tauri::command]
pub async fn list_save_backups(app: AppHandle) -> Result<BackupList, String> {
    let dir = backups_dir(&app)?;
    blocking(move || Ok(BackupList { backups: list_backups(&dir), dir })).await
}

#[tauri::command]
pub async fn create_save_backup(
    app: AppHandle,
    state: State<'_, AppState>,
    label: Option<String>,
) -> Result<Backup, String> {
    let saves = saves_folder(&config(&state))?;
    let dir = backups_dir(&app)?;
    blocking(move || create_backup(&saves, &dir, label.as_deref().unwrap_or(""), &Local::now())).await
}

#[tauri::command]
pub async fn restore_save_backup(app: AppHandle, state: State<'_, AppState>, file: String) -> Result<Restored, String> {
    if crate::game::game_running() {
        return Err("Thief is running: quit the game before restoring saves".into());
    }
    let saves = saves_folder(&config(&state))?;
    let dir = backups_dir(&app)?;
    blocking(move || restore_backup(&saves, &dir, &file, &Local::now())).await
}

#[tauri::command]
pub async fn delete_save_backup(app: AppHandle, file: String) -> Result<(), String> {
    delete_backup(&backups_dir(&app)?, &file)
}

#[tauri::command]
pub async fn open_saves_folder(app: AppHandle, state: State<'_, AppState>, which: String) -> Result<(), String> {
    let path = match which.as_str() {
        "saves" => saves_folder(&config(&state))?,
        "backups" => {
            let dir = backups_dir(&app)?;
            fs::create_dir_all(&dir).map_err(|e| format!("cannot create {}: {e}", dir.display()))?;
            dir
        }
        other => return Err(format!("unknown folder {other}")),
    };
    app.opener().open_path(path.to_string_lossy(), None::<&str>).map_err(|e| e.to_string())
}

/// The "back up before launching" setting, for launch_game: a note for the
/// launch message, or None when the setting is off or nothing changed.
pub async fn before_launch(app: AppHandle, cfg: Config) -> Option<String> {
    if !cfg.backup_before_launch {
        return None;
    }
    let result = blocking(move || {
        let (saves, dir) = (saves_folder(&cfg)?, backups_dir(&app)?);
        auto_backup(&saves, &dir, BEFORE_LAUNCH, &Local::now())
    })
    .await;
    match result {
        Ok(Some((_, true))) => Some("Saves backed up.".into()),
        Ok(_) => None,
        Err(e) => Some(format!("Saves not backed up: {e}.")),
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    fn at(h: u32, m: u32, s: u32) -> DateTime<Local> {
        Local.with_ymd_and_hms(2026, 9, 28, h, m, s).earliest().unwrap()
    }

    /// A made-up SaveGames folder: two slots and the game's current save.
    fn fake_saves(root: &Path) -> PathBuf {
        let saves = root.join("Thief - Deadly Shadows").join(SAVE_GAMES);
        for (dir, file, body) in [
            ("save0001", "info.txt", "slot one"),
            ("save0002", "info.txt", "slot two, a little longer"),
            (CURRENT_SAVE, "state.bin", "current"),
        ] {
            fs::create_dir_all(saves.join(dir)).unwrap();
            fs::write(saves.join(dir).join(file), body).unwrap();
        }
        fs::create_dir_all(saves.join("save0002").join("empty")).unwrap();
        saves
    }

    #[test]
    fn labels_become_file_names() {
        assert_eq!(clean_label("  before   the Cathedral  "), "before the Cathedral");
        assert_eq!(clean_label("a/b\\c:d*e?f\"g<h>i|j\nk"), "a b c d e f g h i j k");
        assert_eq!(clean_label("ends with dots..."), "ends with dots");
        assert_eq!(clean_label(&"x".repeat(100)).len(), 60);
        assert_eq!(clean_label(""), "");
    }

    #[test]
    fn names_round_trip() {
        let (created, label) = parse_name("2026-09-28_120000.zip").unwrap();
        assert_eq!(created, at(12, 0, 0).timestamp());
        assert_eq!(label, None);
        assert_eq!(parse_name("2026-09-28_120000 before restore.zip").unwrap().1.as_deref(), Some("before restore"));
        assert_eq!(
            parse_name("2026-09-28_120000 before restore (2).zip").unwrap().1.as_deref(),
            Some("before restore")
        );
        assert_eq!(parse_name("2026-09-28_120000 (3).zip").unwrap().1, None);
        assert_eq!(parse_name("2026-09-28_120000 Keep (draft).zip").unwrap().1.as_deref(), Some("Keep (draft)"));
        assert!(parse_name("2026-09-28_120000x.zip").is_none());
        assert!(parse_name("holiday.zip").is_none());
        assert!(parse_name("2026-09-28_120000.txt").is_none());
    }

    #[test]
    fn summary_counts_slots_not_the_current_save() {
        let tmp = tempfile::tempdir().unwrap();
        let s = summarize(&fake_saves(tmp.path()));
        assert_eq!(s.count, 2);
        assert_eq!(s.files, 3);
        assert_eq!(s.size, (8 + 25 + 7) as u64);
        assert!(s.newest.is_some());
        assert_eq!(summarize(&tmp.path().join("missing")), SavesSummary::default());
    }

    #[test]
    fn candidates_include_the_game_folder() {
        let game = Path::new("/games/Thief Deadly Shadows");
        let list = candidates(Some(game));
        assert!(list.iter().any(|c| c.path == game.join("save").join(SAVE_GAMES) && c.source == "game folder"));
        assert!(list.iter().all(|c| c.path.ends_with(SAVE_GAMES)));
    }

    #[test]
    fn locate_prefers_the_setting_then_the_newest_saves() {
        let tmp = tempfile::tempdir().unwrap();
        let game = tmp.path().join("game");
        let saves = game.join("save").join(SAVE_GAMES);
        fs::create_dir_all(&saves).unwrap();
        fs::write(saves.join("x"), "1").unwrap();
        let mut cfg = Config { game_dir: Some(game), ..Config::default() };
        let found = locate(&cfg);
        // The real Documents folder may hold saves too; either way, one was picked.
        assert!(found.exists && found.folder.is_some());
        cfg.saves_dir = Some(tmp.path().join("elsewhere"));
        let set = locate(&cfg);
        assert_eq!(set.folder.unwrap().source, "Settings");
        assert!(!set.exists);
    }

    #[test]
    fn backup_list_restore_delete() {
        let tmp = tempfile::tempdir().unwrap();
        let saves = fake_saves(tmp.path());
        let dir = tmp.path().join("backups");

        let first = create_backup(&saves, &dir, "before the Docks", &at(12, 0, 0)).unwrap();
        assert_eq!(first.file, "2026-09-28_120000 before the Docks.zip");
        assert_eq!(first.label.as_deref(), Some("before the Docks"));
        assert_eq!(first.saves, Some(2));
        assert_eq!(first.size, Some(40));
        assert!(first.bytes > 0);
        let same_second = create_backup(&saves, &dir, "before the Docks", &at(12, 0, 0)).unwrap();
        assert_eq!(same_second.file, "2026-09-28_120000 before the Docks (2).zip");
        let plain = create_backup(&saves, &dir, "", &at(13, 0, 0)).unwrap();
        assert_eq!(plain.file, "2026-09-28_130000.zip");
        assert!(!fs::read_dir(&dir).unwrap().flatten().any(|e| e.file_name().to_string_lossy().ends_with(".partial")));

        let list = list_backups(&dir);
        assert_eq!(list.len(), 3);
        assert_eq!(list[0].file, plain.file);

        // Play on: a slot changes, a new one appears.
        fs::write(saves.join("save0001").join("info.txt"), "overwritten").unwrap();
        fs::create_dir_all(saves.join("save0003")).unwrap();
        fs::write(saves.join("save0003").join("info.txt"), "new").unwrap();

        let restored = restore_backup(&saves, &dir, &first.file, &at(14, 0, 0)).unwrap();
        assert_eq!(fs::read_to_string(saves.join("save0001").join("info.txt")).unwrap(), "slot one");
        assert!(!saves.join("save0003").exists());
        assert!(saves.join("save0002").join("empty").is_dir());
        assert!(!saves.join(META).exists());
        assert_eq!(restored.summary.count, 2);
        let before = restored.before.expect("the replaced saves were backed up");
        assert_eq!(before.label.as_deref(), Some(BEFORE_RESTORE));
        assert_eq!(before.saves, Some(3));
        assert!(!sibling(&saves, "t3sdk-restore").unwrap().exists());
        assert!(!sibling(&saves, "t3sdk-old").unwrap().exists());

        // The automatic backup can itself be restored.
        restore_backup(&saves, &dir, &before.file, &at(15, 0, 0)).unwrap();
        assert_eq!(fs::read_to_string(saves.join("save0003").join("info.txt")).unwrap(), "new");

        delete_backup(&dir, &same_second.file).unwrap();
        assert!(!dir.join(&same_second.file).exists());
        assert!(delete_backup(&dir, "../outside.zip").is_err());
        assert!(restore_backup(&saves, &dir, "missing.zip", &at(16, 0, 0)).is_err());
    }

    #[test]
    fn restore_into_a_missing_folder() {
        let tmp = tempfile::tempdir().unwrap();
        let saves = fake_saves(tmp.path());
        let dir = tmp.path().join("backups");
        let backup = create_backup(&saves, &dir, "", &at(12, 0, 0)).unwrap();
        fs::remove_dir_all(&saves).unwrap();
        let restored = restore_backup(&saves, &dir, &backup.file, &at(12, 5, 0)).unwrap();
        assert!(restored.before.is_none());
        assert_eq!(restored.summary.count, 2);
    }

    #[test]
    fn nothing_to_back_up() {
        let tmp = tempfile::tempdir().unwrap();
        let empty = tmp.path().join(SAVE_GAMES);
        fs::create_dir_all(&empty).unwrap();
        let dir = tmp.path().join("backups");
        assert!(create_backup(&empty, &dir, "", &at(12, 0, 0)).is_err());
        assert!(create_backup(&tmp.path().join("missing"), &dir, "", &at(12, 0, 0)).is_err());
        assert!(auto_backup(&empty, &dir, BEFORE_LAUNCH, &at(12, 0, 0)).unwrap().is_none());
        assert!(list_backups(&dir).is_empty());
    }

    #[test]
    fn automatic_backups_skip_unchanged_saves_and_are_pruned() {
        let tmp = tempfile::tempdir().unwrap();
        let saves = fake_saves(tmp.path());
        let dir = tmp.path().join("backups");
        let (first, written) = auto_backup(&saves, &dir, BEFORE_LAUNCH, &at(10, 0, 0)).unwrap().unwrap();
        assert!(written);
        let (again, written) = auto_backup(&saves, &dir, BEFORE_LAUNCH, &at(10, 1, 0)).unwrap().unwrap();
        assert!(!written);
        assert_eq!(again.file, first.file);
        for minute in 0..KEEP_AUTOMATIC as u32 + 3 {
            fs::write(saves.join("save0001").join("info.txt"), "x".repeat(minute as usize + 20)).unwrap();
            assert!(auto_backup(&saves, &dir, BEFORE_LAUNCH, &at(11, minute, 0)).unwrap().unwrap().1);
        }
        create_backup(&saves, &dir, "mine", &at(12, 0, 0)).unwrap();
        let list = list_backups(&dir);
        assert_eq!(list.iter().filter(|b| b.label.as_deref() == Some(BEFORE_LAUNCH)).count(), KEEP_AUTOMATIC);
        assert_eq!(list.iter().filter(|b| b.label.as_deref() == Some("mine")).count(), 1);
    }

    #[test]
    fn unsafe_zips_are_refused() {
        let tmp = tempfile::tempdir().unwrap();
        let saves = fake_saves(tmp.path());
        let dir = tmp.path().join("backups");
        fs::create_dir_all(&dir).unwrap();
        let file = "2026-09-28_120000 evil.zip";
        let mut zip = zip::ZipWriter::new(File::create(dir.join(file)).unwrap());
        zip.start_file("../../escaped.txt", SimpleFileOptions::default()).unwrap();
        zip.write_all(b"nope").unwrap();
        zip.finish().unwrap();
        assert!(restore_backup(&saves, &dir, file, &at(12, 0, 0)).unwrap_err().contains("unsafe"));
        assert!(!tmp.path().join("escaped.txt").exists());
        assert_eq!(summarize(&saves).count, 2);
    }
}
