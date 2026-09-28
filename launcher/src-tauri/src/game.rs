// The game side of the launcher: status, maps, mods, T3SDK.ini, the SDK log,
// and starting the game or Godot.
use std::path::{Path, PathBuf};
use std::process::Stdio;
use std::time::{Duration, UNIX_EPOCH};

use serde::{Deserialize, Serialize};
use tauri::{AppHandle, State};
use tauri_plugin_opener::OpenerExt;

use crate::config::Config;
use crate::detect::{self, GameCheck, STEAM_APP_ID};
use crate::{ini, proc, AppState};

fn config(state: &State<'_, AppState>) -> Config {
    state.config.lock().unwrap().clone()
}

fn mtime(path: &Path) -> Option<u64> {
    let modified = std::fs::metadata(path).ok()?.modified().ok()?;
    Some(modified.duration_since(UNIX_EPOCH).ok()?.as_secs())
}

fn same_file_stamp(a: &Path, b: &Path) -> bool {
    match (std::fs::metadata(a), std::fs::metadata(b)) {
        (Ok(x), Ok(y)) => x.len() == y.len() && x.modified().ok() == y.modified().ok(),
        _ => false,
    }
}

// ---- overview -------------------------------------------------------------------

#[derive(Debug, Default, Serialize)]
#[serde(rename_all = "camelCase")]
pub struct SdkStatus {
    /// System/dinput8.dll exists.
    pub installed: bool,
    /// ...and the T3SDK tools' deploy manifest lists it.
    pub managed: bool,
    /// build/sdk/bin/dinput8.dll exists, so it can be installed.
    pub built: bool,
    /// The SDK's sources are there (a checkout, not the launcher's own copy).
    pub buildable: bool,
    /// System/T3SDK.ini exists.
    pub settings: bool,
}

#[derive(Debug, Default, Serialize)]
#[serde(rename_all = "camelCase")]
pub struct MapCounts {
    pub total: usize,
    pub exported: usize,
    pub edited: usize,
    pub patched: usize,
    pub installed: usize,
}

#[derive(Debug, Serialize)]
#[serde(rename_all = "camelCase")]
pub struct Overview {
    pub game: Option<GameCheck>,
    pub sdk: SdkStatus,
    pub mods_enabled: usize,
    pub mods_disabled: usize,
    pub maps: MapCounts,
    pub running: bool,
}

pub(crate) fn sdk_status(cfg: &Config) -> SdkStatus {
    let mut status = SdkStatus::default();
    if let Some(game) = &cfg.game_dir {
        let system = game.join("System");
        status.installed = system.join("dinput8.dll").is_file();
        status.settings = system.join("T3SDK.ini").is_file();
    }
    if let Some(root) = &cfg.sdk_root {
        status.built = root.join("build").join("sdk").join("bin").join("dinput8.dll").is_file();
        status.buildable = root.join("sdk").join("CMakeLists.txt").is_file();
    }
    if let Some(build) = cfg.build_root() {
        let manifest = build.join("sdk").join("deployed.json");
        status.managed = status.installed && std::fs::read_to_string(manifest).is_ok_and(|t| t.contains("dinput8.dll"));
    }
    status
}

pub(crate) fn game_running() -> bool {
    if !cfg!(windows) {
        return false;
    }
    let mut cmd = proc::quiet(Path::new("tasklist"));
    cmd.args(["/FI", "IMAGENAME eq T3Main.exe", "/FO", "CSV", "/NH"]);
    proc::probe(cmd, Duration::from_secs(5)).is_some_and(|out| out.contains("T3Main"))
}

#[tauri::command]
pub async fn overview(state: State<'_, AppState>) -> Result<Overview, String> {
    let cfg = config(&state);
    let game = cfg.game_dir.as_deref().map(detect::game_check);
    let mods = mods(&cfg).unwrap_or_default();
    let maps = maps(&cfg);
    Ok(Overview {
        game,
        sdk: sdk_status(&cfg),
        mods_enabled: mods.iter().filter(|m| m.enabled).count(),
        mods_disabled: mods.iter().filter(|m| !m.enabled).count(),
        maps: MapCounts {
            total: maps.len(),
            exported: maps.iter().filter(|m| m.exported).count(),
            edited: maps.iter().filter(|m| m.edited_actors.is_some_and(|n| n > 0)).count(),
            patched: maps.iter().filter(|m| m.patched).count(),
            installed: maps.iter().filter(|m| m.installed).count(),
        },
        running: game_running(),
    })
}

// ---- maps -----------------------------------------------------------------------

#[derive(Debug, Serialize)]
#[serde(rename_all = "camelCase")]
pub struct MapEntry {
    /// File name without .gmp; the tools' map id.
    pub id: String,
    /// English name from the export index, once exported.
    pub title: Option<String>,
    pub size: Option<u64>,
    /// The game has this map (it may also exist only in the Godot project).
    pub in_game: bool,
    /// <project>/<id>/<id>.tscn exists.
    pub exported: bool,
    pub actors: Option<u64>,
    /// Actors changed in <id>.edits.json, if it exists.
    pub edited_actors: Option<usize>,
    pub edits_time: Option<u64>,
    /// build/assets/patched/<id>.gmp exists.
    pub patched: bool,
    pub patched_time: Option<u64>,
    /// The edits changed after the last repack.
    pub stale: bool,
    /// The game's copy is no longer the backed-up original.
    pub installed: bool,
    pub backed_up: bool,
}

fn export_index(project: &Path) -> serde_json::Map<String, serde_json::Value> {
    let text = std::fs::read_to_string(project.join("t3_maps.json")).unwrap_or_default();
    let doc: serde_json::Value = serde_json::from_str(&text).unwrap_or_default();
    let mut index = serde_json::Map::new();
    for m in doc.get("maps").and_then(|v| v.as_array()).into_iter().flatten() {
        if let Some(id) = m.get("id").and_then(|v| v.as_str()) {
            index.insert(id.to_string(), m.clone());
        }
    }
    index
}

fn edited_actors(edits: &Path) -> Option<usize> {
    let text = std::fs::read_to_string(edits).ok()?;
    let doc: serde_json::Value = serde_json::from_str(&text).ok()?;
    Some(doc.get("actors").and_then(|a| a.as_object()).map_or(0, |a| a.len()))
}

fn maps(cfg: &Config) -> Vec<MapEntry> {
    let mut ids: Vec<(String, Option<PathBuf>)> = Vec::new();
    if let Some(game) = &cfg.game_dir {
        if let Ok(entries) = std::fs::read_dir(game.join("Content").join("T3").join("Maps")) {
            for e in entries.flatten() {
                let path = e.path();
                if path.extension().is_some_and(|x| x.eq_ignore_ascii_case("gmp")) {
                    let id = path.file_stem().unwrap().to_string_lossy().into_owned();
                    ids.push((id, Some(path)));
                }
            }
        }
    }
    let project = cfg.project();
    let index = project.as_deref().map(export_index).unwrap_or_default();
    for id in index.keys() {
        if !ids.iter().any(|(i, _)| i.eq_ignore_ascii_case(id)) {
            ids.push((id.clone(), None));
        }
    }
    let build = cfg.assets_build();
    let mut list: Vec<MapEntry> = ids
        .into_iter()
        .map(|(id, gmp)| {
            let info = index.get(&id);
            let scene = project.as_ref().map(|p| p.join(&id).join(format!("{id}.tscn")));
            let edits = project.as_ref().map(|p| p.join(&id).join(format!("{id}.edits.json")));
            let patched = build.as_ref().map(|b| b.join("patched").join(format!("{id}.gmp")));
            let backup = build.as_ref().map(|b| b.join("backup").join(format!("{id}.gmp")));
            let edits_time = edits.as_deref().and_then(mtime);
            let patched_time = patched.as_deref().and_then(mtime);
            let backed_up = backup.as_ref().is_some_and(|b| b.is_file());
            let installed = match (&gmp, &backup) {
                (Some(g), Some(b)) if backed_up => !same_file_stamp(g, b),
                _ => false,
            };
            MapEntry {
                title: info.and_then(|m| m.get("title")).and_then(|v| v.as_str()).map(str::to_string),
                size: gmp.as_deref().and_then(|g| std::fs::metadata(g).ok()).map(|m| m.len()),
                in_game: gmp.is_some(),
                exported: scene.is_some_and(|s| s.is_file()),
                actors: info.and_then(|m| m.get("actors")).and_then(|v| v.as_u64()),
                edited_actors: edits.as_deref().and_then(edited_actors),
                edits_time,
                patched: patched_time.is_some(),
                patched_time,
                stale: matches!((edits_time, patched_time), (Some(e), Some(p)) if e > p),
                installed,
                backed_up,
                id,
            }
        })
        .collect();
    list.sort_by_key(|m| m.title.clone().unwrap_or_else(|| m.id.clone()).to_lowercase());
    list
}

#[tauri::command]
pub async fn list_maps(state: State<'_, AppState>) -> Result<Vec<MapEntry>, String> {
    Ok(maps(&config(&state)))
}

// ---- mods -----------------------------------------------------------------------

#[derive(Debug, Serialize)]
#[serde(rename_all = "camelCase")]
pub struct ModEntry {
    pub name: String,
    pub enabled: bool,
    pub size: u64,
    pub modified: Option<u64>,
}

fn mods_dirs(cfg: &Config) -> Result<(PathBuf, PathBuf), String> {
    let mods = cfg.game()?.join("System").join("mods");
    let disabled = mods.join("disabled");
    Ok((mods, disabled))
}

fn mods(cfg: &Config) -> Result<Vec<ModEntry>, String> {
    let (enabled_dir, disabled_dir) = mods_dirs(cfg)?;
    let mut list = Vec::new();
    for (dir, enabled) in [(enabled_dir, true), (disabled_dir, false)] {
        let Ok(entries) = std::fs::read_dir(&dir) else { continue };
        for e in entries.flatten() {
            let path = e.path();
            if path.is_file() && path.extension().is_some_and(|x| x.eq_ignore_ascii_case("dll")) {
                let meta = e.metadata().ok();
                list.push(ModEntry {
                    name: path.file_stem().unwrap().to_string_lossy().into_owned(),
                    enabled,
                    size: meta.as_ref().map_or(0, |m| m.len()),
                    modified: mtime(&path),
                });
            }
        }
    }
    list.sort_by_key(|m| m.name.to_lowercase());
    Ok(list)
}

#[tauri::command]
pub async fn list_mods(state: State<'_, AppState>) -> Result<Vec<ModEntry>, String> {
    mods(&config(&state))
}

/// Moves a mod's files (<name>.dll and its .pdb/.ini) between System/mods and
/// System/mods/disabled: the SDK only loads DLLs directly in System/mods.
#[tauri::command]
pub async fn set_mod_enabled(state: State<'_, AppState>, name: String, enabled: bool) -> Result<(), String> {
    if name.is_empty() || name.contains(['/', '\\', ':']) || name.starts_with('.') {
        return Err(format!("invalid mod name {name:?}"));
    }
    let (on, off) = mods_dirs(&config(&state))?;
    let (from, to) = if enabled { (off, on) } else { (on, off) };
    std::fs::create_dir_all(&to).map_err(|e| format!("cannot create {}: {e}", to.display()))?;
    let mut moved = 0;
    for ext in ["dll", "pdb", "ini"] {
        let src = from.join(format!("{name}.{ext}"));
        if src.is_file() {
            let dst = to.join(format!("{name}.{ext}"));
            if dst.exists() {
                return Err(format!("{} already exists", dst.display()));
            }
            std::fs::rename(&src, &dst).map_err(|e| format!("cannot move {}: {e}", src.display()))?;
            moved += 1;
        }
    }
    if moved == 0 {
        return Err(format!("no mod named {name} in {}", from.display()));
    }
    Ok(())
}

// ---- T3SDK.ini ------------------------------------------------------------------

#[derive(Debug, Serialize)]
#[serde(rename_all = "camelCase")]
pub struct Setting {
    pub key: String,
    pub value: String,
    pub default: Option<String>,
    pub description: String,
}

#[derive(Debug, Serialize)]
#[serde(rename_all = "camelCase")]
pub struct SettingsSection {
    pub name: String,
    pub settings: Vec<Setting>,
}

#[derive(Debug, Serialize)]
#[serde(rename_all = "camelCase")]
pub struct SdkSettings {
    pub file: PathBuf,
    pub exists: bool,
    pub template: Option<PathBuf>,
    pub sections: Vec<SettingsSection>,
}

#[derive(Debug, Deserialize)]
pub struct SettingChange {
    pub section: String,
    pub key: String,
    pub value: String,
}

fn settings_paths(cfg: &Config) -> Result<(PathBuf, Option<PathBuf>), String> {
    let file = cfg.game()?.join("System").join("T3SDK.ini");
    let template = cfg.sdk_root.as_ref().map(|r| r.join("sdk").join("T3SDK.ini")).filter(|t| t.is_file());
    Ok((file, template))
}

/// The settings in the order and with the descriptions of the SDK's own
/// T3SDK.ini (its comments), holding the values of the game's copy. Keys the
/// template lacks are listed after it, so nothing in the user's file is hidden.
#[tauri::command]
pub async fn read_sdk_settings(state: State<'_, AppState>) -> Result<SdkSettings, String> {
    let (file, template) = settings_paths(&config(&state))?;
    let actual = std::fs::read_to_string(&file).ok();
    let exists = actual.is_some();
    let actual = ini::parse(actual.as_deref().unwrap_or(""));
    let defaults =
        template.as_ref().and_then(|t| std::fs::read_to_string(t).ok()).map(|t| ini::parse(&t)).unwrap_or_default();

    let mut sections: Vec<SettingsSection> = Vec::new();
    let mut add =
        |section: &str, setting: Setting| match sections.iter_mut().find(|s| s.name.eq_ignore_ascii_case(section)) {
            Some(s) => s.settings.push(setting),
            None => sections.push(SettingsSection { name: section.to_string(), settings: vec![setting] }),
        };
    let same = |a: &ini::Entry, b: &ini::Entry| {
        a.section.eq_ignore_ascii_case(&b.section) && a.key.eq_ignore_ascii_case(&b.key)
    };
    for d in &defaults {
        let value = actual.iter().find(|a| same(a, d)).map_or_else(|| d.value.clone(), |a| a.value.clone());
        add(
            &d.section,
            Setting { key: d.key.clone(), value, default: Some(d.value.clone()), description: d.comment.clone() },
        );
    }
    for a in actual.iter().filter(|a| !defaults.iter().any(|d| same(a, d))) {
        add(
            &a.section,
            Setting { key: a.key.clone(), value: a.value.clone(), default: None, description: a.comment.clone() },
        );
    }
    Ok(SdkSettings { file, exists, template, sections })
}

#[tauri::command]
pub async fn write_sdk_settings(state: State<'_, AppState>, changes: Vec<SettingChange>) -> Result<(), String> {
    let (file, _) = settings_paths(&config(&state))?;
    let mut text = std::fs::read_to_string(&file).map_err(|e| format!("cannot read {}: {e}", file.display()))?;
    for c in &changes {
        let bad = |s: &str| s.is_empty() || s.contains(['\r', '\n', '[', ']', '=']);
        if bad(&c.section) || bad(&c.key) || c.value.contains(['\r', '\n']) {
            return Err(format!("invalid setting {}.{}", c.section, c.key));
        }
        text = ini::set(&text, &c.section, &c.key, &c.value);
    }
    std::fs::write(&file, text).map_err(|e| format!("cannot write {}: {e}", file.display()))
}

/// Copies the SDK's default T3SDK.ini into System/ when the game has none.
#[tauri::command]
pub async fn create_sdk_settings(state: State<'_, AppState>) -> Result<(), String> {
    let (file, template) = settings_paths(&config(&state))?;
    if file.exists() {
        return Ok(());
    }
    let template = template.ok_or("no default T3SDK.ini found in the T3SDK folder (sdk\\T3SDK.ini)")?;
    std::fs::copy(&template, &file).map(|_| ()).map_err(|e| format!("cannot create {}: {e}", file.display()))
}

#[tauri::command]
pub async fn read_sdk_log(state: State<'_, AppState>, lines: usize) -> Result<Vec<String>, String> {
    let file = config(&state).game()?.join("System").join("T3SDK.log");
    let Ok(bytes) = std::fs::read(&file) else { return Ok(Vec::new()) };
    // The log grows on every run; only its end is interesting.
    let tail = &bytes[bytes.len().saturating_sub(256 * 1024)..];
    let text = String::from_utf8_lossy(tail);
    let all: Vec<&str> = text.lines().collect();
    Ok(all[all.len().saturating_sub(lines)..].iter().map(|s| s.to_string()).collect())
}

// ---- starting things ------------------------------------------------------------

#[tauri::command]
pub async fn launch_game(app: AppHandle, state: State<'_, AppState>) -> Result<String, String> {
    let game = config(&state).game()?;
    // Settings' "back up saves before launching"; a note for the message, if any.
    let saved =
        crate::saves::before_launch(app.clone(), config(&state)).await.map(|n| format!(" {n}")).unwrap_or_default();
    if detect::is_steam_install(&game) {
        // What Steam's Play button does: Steam starts the game through its launchers.
        app.opener().open_url(format!("steam://rungameid/{STEAM_APP_ID}"), None::<&str>).map_err(|e| e.to_string())?;
        return Ok(format!("Asked Steam to start the game.{saved}"));
    }
    let system = game.join("System");
    std::process::Command::new(system.join("T3Main.exe"))
        .current_dir(&system)
        .spawn()
        .map_err(|e| format!("cannot start T3Main.exe: {e}"))?;
    Ok(format!("Started T3Main.exe.{saved}"))
}

/// Opens the exported project in the Godot editor (optionally on one map's
/// scene), or runs the map viewer on a map.
#[tauri::command]
pub async fn open_godot(state: State<'_, AppState>, level: Option<String>, editor: bool) -> Result<(), String> {
    let cfg = config(&state);
    let godot = cfg.godot()?;
    let project = cfg.project().ok_or("no Godot project folder")?;
    if !project.join("project.godot").is_file() {
        return Err("no exported project yet: export a map first".into());
    }
    if let Some(l) = &level {
        if l.is_empty() || l.contains(['/', '\\', ':', '"']) {
            return Err(format!("invalid map id {l:?}"));
        }
    }
    let mut cmd = std::process::Command::new(&godot);
    cmd.arg("--path").arg(&project);
    match (&level, editor) {
        (Some(l), true) => cmd.args(["-e", &format!("res://{l}/{l}.tscn")]),
        (None, true) => cmd.arg("-e"),
        (Some(l), false) => cmd.args(["--", "--t3-map", l]),
        (None, false) => &mut cmd,
    };
    cmd.stdin(Stdio::null()).stdout(Stdio::null()).stderr(Stdio::null());
    cmd.spawn().map(|_| ()).map_err(|e| format!("cannot start Godot: {e}"))
}

#[tauri::command]
pub async fn open_location(app: AppHandle, state: State<'_, AppState>, which: String) -> Result<(), String> {
    let cfg = config(&state);
    let path = match which.as_str() {
        "game" => cfg.game()?,
        "system" => cfg.game()?.join("System"),
        "mods" => {
            let mods = cfg.game()?.join("System").join("mods");
            std::fs::create_dir_all(&mods).map_err(|e| e.to_string())?;
            mods
        }
        "log" => cfg.game()?.join("System").join("T3SDK.log"),
        "project" => cfg.project().ok_or("no Godot project folder")?,
        "sdk" => cfg.root()?,
        "patched" => cfg.assets_build().ok_or("no T3SDK folder")?.join("patched"),
        "backup" => cfg.assets_build().ok_or("no T3SDK folder")?.join("backup"),
        other => return Err(format!("unknown location {other}")),
    };
    if !path.exists() {
        return Err(format!("{} does not exist yet", path.display()));
    }
    app.opener().open_path(path.to_string_lossy(), None::<&str>).map_err(|e| e.to_string())
}

#[tauri::command]
pub async fn open_link(app: AppHandle, url: String) -> Result<(), String> {
    if !url.starts_with("https://") {
        return Err("only https links can be opened".into());
    }
    app.opener().open_url(url, None::<&str>).map_err(|e| e.to_string())
}
