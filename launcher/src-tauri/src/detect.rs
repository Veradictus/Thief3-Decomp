// Finding and checking the four things the launcher needs: the game, Godot,
// Python and the T3SDK tools. Detection only proposes candidates; the user
// confirms them in the setup screen.
use std::collections::{HashMap, HashSet};
use std::path::{Path, PathBuf};
use std::sync::{Mutex, OnceLock};
use std::time::{Duration, SystemTime};

use serde::Serialize;
use sha1::{Digest, Sha1};
use tauri::{AppHandle, Manager};

use crate::proc;

/// SHA-1 of the Steam T3Main.exe (patch 1.1) that the SDK supports.
pub const SUPPORTED_SHA1: &str = "40bf68a54246bcde2fb5fcbc75b94dc7c7f78305";
pub const STEAM_APP_ID: &str = "6980";
const GODOT_MIN: (u32, u32) = (4, 7);
const PYTHON_MIN: (u32, u32) = (3, 10);

#[derive(Clone, Debug, Serialize)]
#[serde(rename_all = "camelCase")]
pub struct Candidate {
    pub path: PathBuf,
    pub source: String,
}

#[derive(Debug, Serialize)]
#[serde(rename_all = "camelCase")]
pub struct Detected {
    pub games: Vec<Candidate>,
    pub godots: Vec<Candidate>,
    pub pythons: Vec<Candidate>,
    pub sdk_roots: Vec<Candidate>,
}

#[derive(Debug, Serialize)]
#[serde(rename_all = "camelCase")]
pub struct GameCheck {
    pub dir: PathBuf,
    pub ok: bool,
    pub exe_found: bool,
    pub sha1: Option<String>,
    pub supported: bool,
    pub steam: bool,
    pub maps: usize,
    pub message: String,
}

#[derive(Debug, Serialize)]
#[serde(rename_all = "camelCase")]
pub struct ToolCheck {
    pub path: PathBuf,
    pub ok: bool,
    pub version: Option<String>,
    pub message: String,
}

#[derive(Debug, Serialize)]
#[serde(rename_all = "camelCase")]
pub struct SdkRootCheck {
    pub path: PathBuf,
    pub ok: bool,
    pub map_tools: bool,
    pub pack_tools: bool,
    pub sdk_built: bool,
    pub message: String,
}

// ---- helpers ------------------------------------------------------------------

fn exe_name(stem: &str) -> String {
    if cfg!(windows) {
        format!("{stem}.exe")
    } else {
        stem.to_string()
    }
}

fn path_dirs() -> Vec<PathBuf> {
    std::env::var_os("PATH").map(|p| std::env::split_paths(&p).collect()).unwrap_or_default()
}

fn home() -> Option<PathBuf> {
    std::env::var_os(if cfg!(windows) { "USERPROFILE" } else { "HOME" }).map(PathBuf::from)
}

fn env_path(name: &str) -> Option<PathBuf> {
    std::env::var_os(name).filter(|v| !v.is_empty()).map(PathBuf::from)
}

/// Keeps the first candidate for each path (case-insensitive on Windows).
fn dedupe(list: Vec<Candidate>) -> Vec<Candidate> {
    let mut seen = HashSet::new();
    list.into_iter()
        .filter(|c| {
            let key = std::fs::canonicalize(&c.path).unwrap_or_else(|_| c.path.clone());
            let key = key.to_string_lossy().into_owned();
            seen.insert(if cfg!(windows) { key.to_lowercase() } else { key })
        })
        .collect()
}

fn push(list: &mut Vec<Candidate>, path: PathBuf, source: &str) {
    list.push(Candidate { path, source: source.to_string() });
}

/// "4.7.2.stable.official.ed1daf0bf" or "Python 3.12.1" -> (4, 7) / (3, 12).
fn major_minor(text: &str) -> Option<(u32, u32)> {
    let start = text.find(|c: char| c.is_ascii_digit())?;
    let mut parts = text[start..].split(|c: char| !c.is_ascii_digit());
    Some((parts.next()?.parse().ok()?, parts.next()?.parse().ok()?))
}

// ---- Steam --------------------------------------------------------------------

fn steam_roots() -> Vec<PathBuf> {
    let mut roots = Vec::new();
    #[cfg(windows)]
    {
        use winreg::enums::HKEY_CURRENT_USER;
        use winreg::RegKey;
        if let Ok(key) = RegKey::predef(HKEY_CURRENT_USER).open_subkey(r"Software\Valve\Steam") {
            if let Ok(path) = key.get_value::<String, _>("SteamPath") {
                roots.push(PathBuf::from(path));
            }
        }
        if let Some(pf) = env_path("ProgramFiles(x86)") {
            roots.push(pf.join("Steam"));
        }
    }
    if let Some(h) = home() {
        roots.push(h.join(".steam").join("steam"));
        roots.push(h.join(".local").join("share").join("Steam"));
    }
    roots.into_iter().filter(|r| r.is_dir()).collect()
}

/// Every Steam library folder: the root itself plus libraryfolders.vdf's "path" entries.
fn steam_libraries() -> Vec<PathBuf> {
    let mut libraries = Vec::new();
    for root in steam_roots() {
        libraries.push(root.clone());
        let vdf = root.join("steamapps").join("libraryfolders.vdf");
        let Ok(text) = std::fs::read_to_string(vdf) else { continue };
        for line in text.lines() {
            let fields: Vec<&str> = line.split('"').collect();
            // `"path"		"D:\\SteamLibrary"` splits into ["", "path", "\t\t", "D:\\\\SteamLibrary", ""]
            if fields.len() >= 4 && fields[1].eq_ignore_ascii_case("path") {
                libraries.push(PathBuf::from(fields[3].replace("\\\\", "\\")));
            }
        }
    }
    libraries
}

/// Steam's install folder for the game in `library`, from its app manifest.
fn steam_game_in(library: &Path) -> Option<PathBuf> {
    let manifest = library.join("steamapps").join(format!("appmanifest_{STEAM_APP_ID}.acf"));
    let text = std::fs::read_to_string(manifest).ok()?;
    let line = text.lines().find(|l| l.trim_start().starts_with("\"installdir\""))?;
    let dir = line.split('"').nth(3)?;
    Some(library.join("steamapps").join("common").join(dir))
}

/// Whether `game` is Steam's install: its library's manifest names it.
pub fn is_steam_install(game: &Path) -> bool {
    let (Some(common), Some(name)) = (game.parent(), game.file_name()) else { return false };
    let Some(library) = common.parent().and_then(|steamapps| steamapps.parent()) else { return false };
    steam_game_in(library)
        .and_then(|p| p.file_name().map(|n| n.to_string_lossy().to_lowercase()))
        .is_some_and(|n| n == name.to_string_lossy().to_lowercase())
}

// ---- candidates -----------------------------------------------------------------

fn game_candidates() -> Vec<Candidate> {
    let mut list = Vec::new();
    if let Some(dir) = env_path("T3_GAME_DIR") {
        push(&mut list, dir, "T3_GAME_DIR");
    }
    #[cfg(windows)]
    {
        use winreg::enums::{HKEY_LOCAL_MACHINE, KEY_READ, KEY_WOW64_32KEY, KEY_WOW64_64KEY};
        use winreg::RegKey;
        for view in [KEY_WOW64_32KEY, KEY_WOW64_64KEY] {
            if let Ok(key) = RegKey::predef(HKEY_LOCAL_MACHINE)
                .open_subkey_with_flags(r"SOFTWARE\Ion Storm\Thief - Deadly Shadows", KEY_READ | view)
            {
                if let Ok(root) = key.get_value::<String, _>("ION_ROOT") {
                    push(&mut list, PathBuf::from(root), "installer registry entry");
                }
            }
        }
    }
    for library in steam_libraries() {
        if let Some(dir) = steam_game_in(&library) {
            push(&mut list, dir, "Steam library");
        }
    }
    list.retain(|c| c.path.join("System").join("T3Main.exe").is_file());
    dedupe(list)
}

fn godot_candidates() -> Vec<Candidate> {
    let mut list = Vec::new();
    if let Some(exe) = env_path("GODOT") {
        push(&mut list, exe, "GODOT");
    }
    for dir in path_dirs() {
        for stem in ["godot", "godot4", "Godot"] {
            let exe = dir.join(exe_name(stem));
            if exe.is_file() {
                push(&mut list, exe, "PATH");
            }
        }
    }
    // Godot ships as a loose executable, usually left where it was unzipped.
    let mut folders: Vec<(PathBuf, &str)> = Vec::new();
    if let Some(h) = home() {
        for sub in ["Downloads", "Desktop", "Documents", "Apps", "Tools"] {
            folders.push((h.join(sub), "user folder"));
        }
        folders.push((h.join("scoop").join("apps").join("godot").join("current"), "Scoop"));
    }
    if let Some(local) = env_path("LOCALAPPDATA") {
        folders.push((local.join("Programs"), "Programs"));
    }
    for pf in ["ProgramFiles", "ProgramFiles(x86)"] {
        if let Some(dir) = env_path(pf) {
            folders.push((dir, "Program Files"));
        }
    }
    for library in steam_libraries() {
        folders.push((library.join("steamapps").join("common").join("Godot Engine"), "Steam"));
    }
    for (folder, source) in folders {
        scan_for_godot(&folder, source, 2, &mut list);
    }
    dedupe(list)
}

fn looks_like_godot(name: &str) -> bool {
    let lower = name.to_lowercase();
    let exe_ok =
        if cfg!(windows) { lower.ends_with(".exe") } else { !lower.contains('.') || lower.ends_with(".x86_64") };
    lower.starts_with("godot")
        && exe_ok
        && !lower.contains("console")
        && !lower.contains("mono")
        && !lower.ends_with(".zip")
}

fn scan_for_godot(dir: &Path, source: &str, depth: u32, list: &mut Vec<Candidate>) {
    let Ok(entries) = std::fs::read_dir(dir) else { return };
    for entry in entries.flatten() {
        let path = entry.path();
        let name = entry.file_name().to_string_lossy().into_owned();
        if path.is_file() && looks_like_godot(&name) {
            push(list, path, source);
        } else if depth > 0 && path.is_dir() && name.to_lowercase().contains("godot") {
            scan_for_godot(&path, source, depth - 1, list);
        }
    }
}

fn python_candidates(sdk_roots: &[Candidate], resources: Option<&Path>) -> Vec<Candidate> {
    let mut list = Vec::new();
    // Release builds ship CPython's embeddable package (tools/stage_launcher.py).
    if let Some(res) = resources {
        let bundled = res.join("python").join(exe_name("python"));
        if bundled.is_file() {
            push(&mut list, bundled, "bundled with the launcher");
        }
    }
    for root in sdk_roots {
        let venv = if cfg!(windows) {
            root.path.join(".venv").join("Scripts").join("python.exe")
        } else {
            root.path.join(".venv").join("bin").join("python")
        };
        if venv.is_file() {
            push(&mut list, venv, "T3SDK .venv");
        }
    }
    #[cfg(windows)]
    {
        // The py launcher knows every installed Python; ask it for the newest 3.x.
        let mut cmd = proc::quiet(Path::new("py"));
        cmd.args(["-3", "-c", "import sys; print(sys.executable)"]);
        if let Some(out) = proc::probe(cmd, Duration::from_secs(10)) {
            let exe = PathBuf::from(out.trim());
            if exe.is_file() {
                push(&mut list, exe, "py launcher");
            }
        }
    }
    for dir in path_dirs() {
        // Skip the Microsoft Store stubs, which open the Store instead of running.
        if dir.to_string_lossy().contains("WindowsApps") {
            continue;
        }
        for stem in ["python3", "python"] {
            let exe = dir.join(exe_name(stem));
            if exe.is_file() {
                push(&mut list, exe, "PATH");
            }
        }
    }
    dedupe(list)
}

fn is_sdk_root(dir: &Path) -> bool {
    dir.join("tools").join("assets").join("t3map.py").is_file() && dir.join("tools").join("sdk.py").is_file()
}

fn sdk_root_candidates(resources: Option<&Path>) -> Vec<Candidate> {
    let mut list = Vec::new();
    // Release builds ship the tools and the prebuilt SDK as t3sdk/.
    if let Some(bundled) = resources.map(|r| r.join("t3sdk")).filter(|d| is_sdk_root(d)) {
        push(&mut list, bundled, "bundled with the launcher");
    }
    let starts = [
        (std::env::current_exe().ok().and_then(|p| p.parent().map(Path::to_path_buf)), "next to the launcher"),
        (std::env::current_dir().ok(), "working folder"),
    ];
    for (start, source) in starts {
        let mut dir = start;
        for _ in 0..6 {
            let Some(d) = dir else { break };
            if is_sdk_root(&d) {
                push(&mut list, d.clone(), source);
                break;
            }
            dir = d.parent().map(Path::to_path_buf);
        }
    }
    dedupe(list)
}

// ---- checks ---------------------------------------------------------------------

/// SHA-1 of a file, cached by size and modification time: the launcher checks
/// the same T3Main.exe on every refresh.
pub fn sha1_file(path: &Path) -> Option<String> {
    type Cache = Mutex<HashMap<PathBuf, (u64, SystemTime, String)>>;
    static CACHE: OnceLock<Cache> = OnceLock::new();
    let meta = std::fs::metadata(path).ok()?;
    let stamp = (meta.len(), meta.modified().ok()?);
    let cache = CACHE.get_or_init(Default::default);
    if let Some((len, time, hash)) = cache.lock().unwrap().get(path) {
        if (*len, *time) == stamp {
            return Some(hash.clone());
        }
    }
    let hash: String = Sha1::digest(std::fs::read(path).ok()?).iter().map(|b| format!("{b:02x}")).collect();
    cache.lock().unwrap().insert(path.to_path_buf(), (stamp.0, stamp.1, hash.clone()));
    Some(hash)
}

pub fn count_maps(game: &Path) -> usize {
    std::fs::read_dir(game.join("Content").join("T3").join("Maps"))
        .map(|entries| {
            entries.flatten().filter(|e| e.path().extension().is_some_and(|x| x.eq_ignore_ascii_case("gmp"))).count()
        })
        .unwrap_or(0)
}

pub fn game_check(dir: &Path) -> GameCheck {
    let exe = dir.join("System").join("T3Main.exe");
    let exe_found = exe.is_file();
    let sha1 = if exe_found { sha1_file(&exe) } else { None };
    let supported = sha1.as_deref() == Some(SUPPORTED_SHA1);
    let steam = is_steam_install(dir);
    let maps = count_maps(dir);
    let message = if !exe_found {
        "No System\\T3Main.exe here: pick the folder that contains System and Content.".to_string()
    } else if supported {
        format!("Steam release, patch 1.1: supported. {maps} maps.")
    } else {
        format!("Found T3Main.exe, but not the supported build: the SDK will stay disabled. Map tools still work. {maps} maps.")
    };
    GameCheck { dir: dir.to_path_buf(), ok: exe_found, exe_found, sha1, supported, steam, maps, message }
}

pub fn godot_check(path: &Path) -> ToolCheck {
    let mut cmd = proc::quiet(path);
    cmd.arg("--version");
    let version =
        proc::probe(cmd, Duration::from_secs(15)).map(|out| out.lines().last().unwrap_or("").trim().to_string());
    let (ok, message) = match version.as_deref().and_then(major_minor) {
        Some(v) if v >= GODOT_MIN => (true, "Ready.".to_string()),
        Some(_) => {
            (false, format!("Godot {}.{} or newer is needed for the exported project.", GODOT_MIN.0, GODOT_MIN.1))
        }
        None if path.is_file() => (false, "This file did not answer `--version` like Godot does.".to_string()),
        None => (false, "File not found.".to_string()),
    };
    ToolCheck { path: path.to_path_buf(), ok, version, message }
}

pub fn python_check(path: &Path) -> ToolCheck {
    let mut cmd = proc::quiet(path);
    cmd.args(["-c", "import sys; print('%d.%d.%d' % sys.version_info[:3])"]);
    let version = proc::probe(cmd, Duration::from_secs(15)).map(|out| out.trim().to_string());
    let (ok, message) = match version.as_deref().and_then(major_minor) {
        Some(v) if v >= PYTHON_MIN => (true, "Ready.".to_string()),
        Some(_) => (false, format!("Python {}.{} or newer is needed.", PYTHON_MIN.0, PYTHON_MIN.1)),
        None if path.is_file() => (false, "This file did not run like a Python interpreter.".to_string()),
        None => (false, "File not found.".to_string()),
    };
    ToolCheck { path: path.to_path_buf(), ok, version, message }
}

pub fn sdk_root_check(path: &Path) -> SdkRootCheck {
    let tools = path.join("tools");
    let map_tools = is_sdk_root(path);
    let pack_tools = tools.join("assets").join("t3pack.py").is_file();
    let sdk_built = path.join("build").join("sdk").join("bin").join("dinput8.dll").is_file();
    let message = if !map_tools {
        "Not a T3SDK folder: expected tools\\sdk.py and tools\\assets\\t3map.py.".to_string()
    } else if !pack_tools {
        "T3SDK tools found, but no map repacker (tools\\assets\\t3pack.py): update T3SDK to repack maps.".to_string()
    } else {
        "Ready.".to_string()
    };
    SdkRootCheck { path: path.to_path_buf(), ok: map_tools, map_tools, pack_tools, sdk_built, message }
}

// ---- commands -------------------------------------------------------------------

#[tauri::command]
pub async fn detect_all(app: AppHandle) -> Result<Detected, String> {
    let resources = app.path().resource_dir().ok();
    let sdk_roots = sdk_root_candidates(resources.as_deref());
    let pythons = python_candidates(&sdk_roots, resources.as_deref());
    Ok(Detected { games: game_candidates(), godots: godot_candidates(), pythons, sdk_roots })
}

#[tauri::command]
pub async fn check_game(path: PathBuf) -> Result<GameCheck, String> {
    Ok(game_check(&path))
}

#[tauri::command]
pub async fn check_godot(path: PathBuf) -> Result<ToolCheck, String> {
    Ok(godot_check(&path))
}

#[tauri::command]
pub async fn check_python(path: PathBuf) -> Result<ToolCheck, String> {
    Ok(python_check(&path))
}

#[tauri::command]
pub async fn check_sdk_root(path: PathBuf) -> Result<SdkRootCheck, String> {
    Ok(sdk_root_check(&path))
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn versions() {
        assert_eq!(major_minor("4.7.2.stable.official.ed1daf0bf"), Some((4, 7)));
        assert_eq!(major_minor("Python 3.12.1"), Some((3, 12)));
        assert_eq!(major_minor("3.10.0"), Some((3, 10)));
        assert_eq!(major_minor("garbage"), None);
    }

    #[test]
    fn godot_names() {
        if cfg!(windows) {
            assert!(looks_like_godot("Godot_v4.7.2-stable_win64.exe"));
            assert!(!looks_like_godot("Godot_v4.7.2-stable_win64_console.exe"));
        } else {
            assert!(looks_like_godot("Godot_v4.7.2-stable_linux.x86_64"));
            assert!(!looks_like_godot("Godot_v4.7.2-stable_linux.x86_64.zip"));
        }
    }
}
