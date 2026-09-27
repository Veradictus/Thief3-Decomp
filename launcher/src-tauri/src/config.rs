// The launcher's own settings: where the game, Godot, Python and the T3SDK
// tools are. Stored as launcher.json in the per-user config folder, never in
// the repository or the game folder.
use std::path::PathBuf;

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

    /// The Godot project folder, explicit or under the T3SDK build folder.
    pub fn project(&self) -> Option<PathBuf> {
        self.project_dir
            .clone()
            .or_else(|| self.sdk_root.as_ref().map(|r| r.join("build").join("assets").join("godot")))
    }

    /// build/assets/ of the T3SDK folder: patched maps and backups live here.
    pub fn assets_build(&self) -> Option<PathBuf> {
        self.sdk_root.as_ref().map(|r| r.join("build").join("assets"))
    }
}

fn file(app: &AppHandle) -> Option<PathBuf> {
    app.path().app_config_dir().ok().map(|dir| dir.join("launcher.json"))
}

pub fn load(app: &AppHandle) -> Config {
    file(app)
        .and_then(|path| std::fs::read_to_string(path).ok())
        .and_then(|text| serde_json::from_str(&text).ok())
        .unwrap_or_default()
}

#[tauri::command]
pub async fn get_config(state: State<'_, AppState>) -> Result<Config, String> {
    Ok(state.config.lock().unwrap().clone())
}

#[tauri::command]
pub async fn save_config(app: AppHandle, state: State<'_, AppState>, config: Config) -> Result<Config, String> {
    let path = file(&app).ok_or("no per-user config folder")?;
    if let Some(dir) = path.parent() {
        std::fs::create_dir_all(dir).map_err(|e| format!("cannot create {}: {e}", dir.display()))?;
    }
    let text = serde_json::to_string_pretty(&config).map_err(|e| e.to_string())?;
    std::fs::write(&path, text).map_err(|e| format!("cannot write {}: {e}", path.display()))?;
    *state.config.lock().unwrap() = config.clone();
    Ok(config)
}
