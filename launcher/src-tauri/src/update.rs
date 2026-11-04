// Launcher updates through tauri-plugin-updater. Release builds made with the
// updater key carry `plugins.updater` in their config (written by
// tools/stage_launcher.py --updater-pubkey); only those register the plugin,
// so development and unsigned builds run without it. The UI goes through the
// commands here rather than the plugin's own JavaScript API, so the window's
// capability needs no updater permission. The installed launcher updates
// through the plugin (the installer); the portable one replaces its own files
// (portable.rs). See docs/releasing.md.
use std::sync::Mutex;
use std::time::{Duration, Instant, SystemTime, UNIX_EPOCH};

use serde::Serialize;
use tauri::{AppHandle, Emitter, Manager, State};
use tauri_plugin_updater::{Update, UpdaterExt};

use crate::AppState;

/// The automatic check runs at most this often.
const CHECK_INTERVAL: u64 = 24 * 60 * 60;

pub struct Updates {
    /// The plugin is registered: the build has an update key and endpoint.
    enabled: bool,
    /// The update found by the last check, installed by install_update.
    pending: Mutex<Option<Update>>,
    /// The version this launcher was updated from, on its first start after the update ("" when
    /// that version did not record itself).
    updated_from: Option<String>,
}

#[derive(Debug, Serialize)]
#[serde(rename_all = "camelCase")]
pub struct UpdaterStatus {
    /// This build can update itself (it was built with the update key).
    pub enabled: bool,
    /// A copy unzipped from the portable zip: updates are downloaded by hand.
    pub portable: bool,
    pub version: String,
    pub last_check: Option<u64>,
    /// Set on the first start after an update: the version before it ("" when unknown).
    pub updated_from: Option<String>,
}

#[derive(Debug, Serialize)]
#[serde(rename_all = "camelCase")]
pub struct UpdateInfo {
    pub version: String,
    pub current_version: String,
    pub notes: Option<String>,
    /// Release date (Unix seconds).
    pub date: Option<i64>,
    /// This copy can install it itself; false for a portable copy when the release has no signed
    /// portable zip (it is then downloaded by hand).
    pub in_app: bool,
}

#[derive(Debug, Serialize)]
#[serde(rename_all = "camelCase")]
pub struct UpdateCheck {
    /// False when an automatic check was skipped (turned off, or done today).
    pub checked: bool,
    pub update: Option<UpdateInfo>,
}

#[derive(Clone, Debug, Serialize)]
#[serde(rename_all = "camelCase")]
struct Progress {
    downloaded: u64,
    total: Option<u64>,
    /// The download is complete and the installer starts.
    finished: bool,
}

/// Whether the app config has an updater section with a public key.
fn configured(app: &AppHandle) -> bool {
    let updater = app.config().plugins.0.get("updater");
    updater.and_then(|u| u.get("pubkey")).and_then(|k| k.as_str()).is_some_and(|k| !k.trim().is_empty())
}

/// The updater's public key (base64), from the build's config.
fn pubkey(app: &AppHandle) -> Option<String> {
    let updater = app.config().plugins.0.get("updater")?;
    updater.get("pubkey")?.as_str().map(str::to_string).filter(|k| !k.trim().is_empty())
}

/// Registers the updater plugin when the build is configured for it, and the
/// state the commands below use. Also notes a launcher update since the last
/// start, and clears what a portable update left behind.
pub fn setup(app: &AppHandle) {
    let enabled = configured(app)
        && match app.plugin(tauri_plugin_updater::Builder::new().build()) {
            Ok(()) => true,
            Err(e) => {
                eprintln!("updater disabled: {e}");
                false
            }
        };
    let updated_from = record_version(app);
    if portable() {
        if let Some(dir) = launcher_dir() {
            std::thread::spawn(move || crate::portable::cleanup(&dir));
        }
    }
    app.manage(Updates { enabled, pending: Mutex::new(None), updated_from });
}

/// Records this version as the last one that ran, and returns the one before it when it differs.
fn record_version(app: &AppHandle) -> Option<String> {
    let current = app.package_info().version.to_string();
    let state = app.state::<AppState>();
    let (previous, saved) = {
        let mut cfg = state.config.lock().unwrap();
        let previous = match cfg.last_version.replace(current.clone()) {
            Some(v) => Some(v),
            // Set up by a launcher that did not record its version: an update from it.
            None if cfg.setup_complete => Some(String::new()),
            None => None,
        };
        (previous, cfg.clone())
    };
    let updated_from = updated_from(previous.as_deref(), &current);
    if previous.as_deref() != Some(current.as_str()) {
        if let Err(e) = crate::config::store(app, &saved) {
            eprintln!("{e}");
        }
    }
    updated_from
}

/// `previous`: the version recorded by the last start ("" for a launcher that was set up before
/// versions were recorded; None for a first start).
pub fn updated_from(previous: Option<&str>, current: &str) -> Option<String> {
    previous.filter(|p| *p != current).map(str::to_string)
}

/// The folder of the running launcher.
fn launcher_dir() -> Option<std::path::PathBuf> {
    std::env::current_exe().ok().and_then(|exe| exe.parent().map(std::path::Path::to_path_buf))
}

/// The NSIS installer puts uninstall.exe next to the launcher; a copy from
/// the portable zip has none, and the updater plugin (which runs the
/// installer) would install a second copy instead of updating that one, so
/// a portable copy updates itself (portable.rs).
fn portable() -> bool {
    cfg!(windows) && launcher_dir().is_none_or(|dir| !dir.join("uninstall.exe").is_file())
}

/// Whether this copy can install `update` itself.
fn in_app(update: &Update) -> bool {
    !portable() || crate::portable::package(&update.raw_json).is_some()
}

fn now() -> u64 {
    SystemTime::now().duration_since(UNIX_EPOCH).map_or(0, |d| d.as_secs())
}

/// An automatic check is due: never checked, a day has passed, or the clock
/// went back.
pub fn due(last: Option<u64>, now: u64) -> bool {
    last.is_none_or(|t| t > now || now - t >= CHECK_INTERVAL)
}

#[tauri::command]
pub async fn updater_status(app: AppHandle, state: State<'_, AppState>) -> Result<UpdaterStatus, String> {
    Ok(UpdaterStatus {
        enabled: app.state::<Updates>().enabled,
        portable: portable(),
        version: app.package_info().version.to_string(),
        last_check: state.config.lock().unwrap().last_update_check,
        updated_from: app.state::<Updates>().updated_from.clone(),
    })
}

/// Asks the release endpoint for a newer version. `auto` is the start-up
/// check: skipped when turned off in Settings or already done today.
#[tauri::command]
pub async fn check_update(app: AppHandle, state: State<'_, AppState>, auto: bool) -> Result<UpdateCheck, String> {
    let updates = app.state::<Updates>();
    if !updates.enabled {
        if auto {
            return Ok(UpdateCheck { checked: false, update: None });
        }
        return Err("this build of the launcher cannot update itself: get new versions from the releases page".into());
    }
    let cfg = state.config.lock().unwrap().clone();
    if auto && (cfg.auto_update_check == Some(false) || !due(cfg.last_update_check, now())) {
        return Ok(UpdateCheck { checked: false, update: None });
    }
    let updater = app.updater().map_err(|e| e.to_string())?;
    let found = updater.check().await.map_err(|e| format!("could not check for updates: {e}"))?;

    // Remember the check, keeping whatever else changed in the meantime.
    let saved = {
        let mut current = state.config.lock().unwrap();
        current.last_update_check = Some(now());
        current.clone()
    };
    if let Err(e) = crate::config::store(&app, &saved) {
        eprintln!("{e}");
    }

    let info = found.as_ref().map(|u| UpdateInfo {
        version: u.version.clone(),
        current_version: u.current_version.clone(),
        notes: u.body.clone().filter(|n| !n.trim().is_empty()),
        date: u.date.map(|d| d.unix_timestamp()),
        in_app: in_app(u),
    });
    *updates.pending.lock().unwrap() = found;
    Ok(UpdateCheck { checked: true, update: info })
}

/// Downloads the update found by the last check, with `update-progress`
/// events, and installs it. On Windows the installer takes over (passive
/// mode: a progress bar, no questions) and starts the new launcher; the
/// process ends here. A portable copy replaces its own files and starts the
/// new launcher. Elsewhere the app restarts itself.
#[tauri::command]
pub async fn install_update(app: AppHandle) -> Result<(), String> {
    let pending = app.state::<Updates>().pending.lock().unwrap().take();
    let update = match pending {
        Some(update) => update,
        None => {
            let updater = app.updater().map_err(|e| e.to_string())?;
            updater.check().await.map_err(|e| e.to_string())?.ok_or("the launcher is up to date")?
        }
    };
    if portable() {
        return install_portable(app, update).await;
    }
    let mut downloaded = 0u64;
    let mut last = Instant::now();
    let progress = app.clone();
    let finished = app.clone();
    update
        .download_and_install(
            move |chunk, total| {
                downloaded += chunk as u64;
                // Chunks are small; a few updates a second are plenty.
                if last.elapsed() >= Duration::from_millis(100) || Some(downloaded) == total {
                    last = Instant::now();
                    let _ = progress.emit("update-progress", Progress { downloaded, total, finished: false });
                }
            },
            move || {
                let _ = finished.emit("update-progress", Progress { downloaded: 0, total: None, finished: true });
            },
        )
        .await
        .map_err(|e| format!("the update failed: {e}"))?;
    app.restart()
}

/// The portable copy's update: the signed portable zip from latest.json, swapped in over this
/// folder (portable.rs), then the new launcher is started and this one closes.
async fn install_portable(app: AppHandle, update: Update) -> Result<(), String> {
    let no_package = "this is the portable launcher: download the new version from the releases page";
    let package = crate::portable::package(&update.raw_json).ok_or(no_package)?;
    let key = pubkey(&app).ok_or(no_package)?;
    let exe = std::env::current_exe().map_err(|e| e.to_string())?;
    let dir = exe.parent().ok_or("the launcher's folder is unknown")?.to_path_buf();
    let name = exe.file_name().ok_or("the launcher's name is unknown")?.to_string_lossy().into_owned();
    let version = update.version.clone();

    let progress = app.clone();
    tauri::async_runtime::spawn_blocking(move || {
        let mut last = Instant::now();
        let data = crate::portable::download(&package.url, |downloaded, total| {
            if last.elapsed() >= Duration::from_millis(100) || Some(downloaded) == total {
                last = Instant::now();
                let _ = progress.emit("update-progress", Progress { downloaded, total, finished: false });
            }
        })?;
        crate::portable::verify(&data, &package.signature, &key, &version)?;
        let _ = progress.emit("update-progress", Progress { downloaded: 0, total: None, finished: true });
        crate::portable::install(&dir, &name, &data)
    })
    .await
    .map_err(|e| format!("the update failed: {e}"))?
    .map_err(|e| format!("the update failed: {e}"))?;

    // The new launcher now sits where this one was started from.
    std::process::Command::new(&exe)
        .current_dir(exe.parent().unwrap_or(std::path::Path::new(".")))
        .spawn()
        .map_err(|e| format!("the update is installed, but the new launcher did not start ({e}): start it again"))?;
    app.exit(0);
    Ok(())
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn checks_at_most_daily() {
        let now = 1_790_000_000;
        assert!(due(None, now));
        assert!(!due(Some(now - 60), now));
        assert!(!due(Some(now - CHECK_INTERVAL + 1), now));
        assert!(due(Some(now - CHECK_INTERVAL), now));
        assert!(due(Some(now + 3600), now), "a clock that went back does not block checks");
    }

    #[test]
    fn notices_an_update() {
        assert_eq!(updated_from(Some("0.3.2"), "0.3.3"), Some("0.3.2".into()));
        assert_eq!(updated_from(Some(""), "0.3.3"), Some("".into()), "set up before versions were recorded");
        assert_eq!(updated_from(Some("0.3.3"), "0.3.3"), None);
        assert_eq!(updated_from(None, "0.3.3"), None, "a first start is not an update");
    }
}
