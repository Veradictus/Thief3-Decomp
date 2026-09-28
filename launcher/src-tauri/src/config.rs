// The launcher's own settings: where the game, Godot, Python and the T3SDK
// tools are. Stored as launcher.json in the per-user config folder, never in
// the repository or the game folder.
use std::path::{Path, PathBuf};

use serde::{Deserialize, Serialize};
use tauri::{AppHandle, Manager, State};

use crate::AppState;

#[derive(Clone, Debug, Default, Serialize, Deserialize)]
#[serde(rename_all = "camelCase", default)]
pub struct Config {
    /// Game install root (holds System/ and Content/).
    pub game_dir: Option<PathBuf>,
    /// Godot 4.7+ editor executable.
    pub godot: Option<PathBuf>,
    /// Python 3.10+ interpreter that runs the tools.
    pub python: Option<PathBuf>,
    /// T3SDK checkout or release folder (holds tools/ and sdk/).
    pub sdk_root: Option<PathBuf>,
    /// Godot project the maps are exported to; default <sdk_root>/build/assets/godot.
    pub project_dir: Option<PathBuf>,
    /// The first-run setup was finished (or skipped).
    pub setup_complete: bool,
    /// The game's SaveGames folder; unset or empty: found automatically (saves.rs).
    pub saves_dir: Option<PathBuf>,
    /// Back up the saves before the launcher starts the game.
    pub backup_before_launch: bool,
    /// Look for a launcher update at start-up, at most once a day; unset means yes.
    pub auto_update_check: Option<bool>,
    /// When the launcher last looked for an update (Unix seconds); kept by update.rs.
    pub last_update_check: Option<u64>,
    /// The mod index the Mods page browses; default `mods::DEFAULT_INDEX_URL`.
    pub mod_index_url: Option<String>,
    /// Where the tools write, when not <sdk_root>/build (see `resolve`).
    #[serde(skip)]
    pub data_dir: Option<PathBuf>,
}

impl Config {
    pub fn game(&self) -> Result<PathBuf, String> {
        self.game_dir.clone().ok_or_else(|| "the Thief folder is not set (Settings)".into())
    }

    pub fn root(&self) -> Result<PathBuf, String> {
        self.sdk_root.clone().ok_or_else(|| "the T3SDK folder is not set (Settings)".into())
    }

    pub fn python(&self) -> Result<PathBuf, String> {
        self.python.clone().ok_or_else(|| "Python is not set (Settings)".into())
    }

    pub fn godot(&self) -> Result<PathBuf, String> {
        self.godot.clone().ok_or_else(|| "Godot is not set (Settings)".into())
    }

    /// The tools' output folder (their T3SDK_BUILD_DIR): the T3SDK folder's
    /// build/, or a per-user folder for the tools bundled with the launcher.
    pub fn build_root(&self) -> Option<PathBuf> {
        self.data_dir.clone().or_else(|| self.sdk_root.as_ref().map(|r| r.join("build")))
    }

    /// The Godot project folder, explicit or under the build folder.
    pub fn project(&self) -> Option<PathBuf> {
        self.project_dir.clone().or_else(|| self.assets_build().map(|a| a.join("godot")))
    }

    /// build/assets/: patched maps and backups live here.
    pub fn assets_build(&self) -> Option<PathBuf> {
        self.build_root().map(|b| b.join("assets"))
    }
}

/// The copy of the tools that ships with the launcher lives in its resource
/// folder, which an update replaces (and which may not be writable), so their
/// output (backups of original maps among it) goes to the user's local app
/// data instead. A T3SDK checkout keeps its own build/.
pub fn resolve(app: &AppHandle, config: &mut Config) {
    let canonical = |p: &Path| std::fs::canonicalize(p).unwrap_or_else(|_| p.to_path_buf());
    let bundled = match (&config.sdk_root, app.path().resource_dir()) {
        (Some(root), Ok(resources)) => canonical(root).starts_with(canonical(&resources)),
        _ => false,
    };
    config.data_dir = if bundled { app.path().app_local_data_dir().ok().map(|d| d.join("build")) } else { None };
}

fn file(app: &AppHandle) -> Option<PathBuf> {
    app.path().app_config_dir().ok().map(|dir| dir.join("launcher.json"))
}

pub fn load(app: &AppHandle) -> Config {
    let mut config: Config = file(app)
        .and_then(|path| std::fs::read_to_string(path).ok())
        .and_then(|text| serde_json::from_str(&text).ok())
        .unwrap_or_default();
    resolve(app, &mut config);
    config
}

#[tauri::command]
pub async fn get_config(state: State<'_, AppState>) -> Result<Config, String> {
    Ok(state.config.lock().unwrap().clone())
}

#[tauri::command]
pub async fn save_config(app: AppHandle, state: State<'_, AppState>, mut config: Config) -> Result<Config, String> {
    resolve(&app, &mut config);
    // The UI may send an older copy of what the launcher records by itself.
    config.last_update_check = config.last_update_check.max(state.config.lock().unwrap().last_update_check);
    let path = file(&app).ok_or("no per-user config folder")?;
    if let Some(dir) = path.parent() {
        std::fs::create_dir_all(dir).map_err(|e| format!("cannot create {}: {e}", dir.display()))?;
    }
    let text = serde_json::to_string_pretty(&config).map_err(|e| e.to_string())?;
    std::fs::write(&path, text).map_err(|e| format!("cannot write {}: {e}", path.display()))?;
    *state.config.lock().unwrap() = config.clone();
    Ok(config)
}

/// Writes launcher.json for settings the launcher records by itself (the last
/// update check), outside save_config.
pub fn store(app: &AppHandle, config: &Config) -> Result<(), String> {
    let path = file(app).ok_or("no per-user config folder")?;
    if let Some(dir) = path.parent() {
        std::fs::create_dir_all(dir).map_err(|e| format!("cannot create {}: {e}", dir.display()))?;
    }
    let text = serde_json::to_string_pretty(config).map_err(|e| e.to_string())?;
    std::fs::write(&path, text).map_err(|e| format!("cannot write {}: {e}", path.display()))
}
