// "Collect logs": one zip with what a bug report needs (the SDK's log and
// settings, the mod files, a listing of System/, the launcher's view of the
// game and its own settings), with the user's home folder and name taken out.
use std::fs::{self, File};
use std::io::{Read, Seek, SeekFrom, Write};
use std::path::{Path, PathBuf};

use serde::Serialize;
use sha2::{Digest, Sha256};
use tauri::{AppHandle, State};
use zip::write::SimpleFileOptions;

use crate::config::Config;
use crate::{detect, game, saves, AppState};

/// Only the end of a log goes in: it grows on every run.
const LOG_TAIL: u64 = 4 * 1024 * 1024;
/// Mod manager files in System/mods, when present.
const MOD_FILES: [&str; 3] = ["load-order.txt", "state.json", "overlay.json"];

const README: &str = "\
Collected by the T3SDK Launcher for a bug report.

Paths inside your user folder are written as %USERPROFILE%, and your user
name as <user>. Nothing else was changed. Look through the files before you
share them, and attach the zip to the issue.
";

#[derive(Debug, Serialize)]
#[serde(rename_all = "camelCase")]
pub struct LogsReport {
    pub path: PathBuf,
    pub files: usize,
    pub bytes: u64,
}

// ---- redaction --------------------------------------------------------------------

/// Takes the home folder and the user name out of text: case-insensitively,
/// with backslashes, forward slashes and the doubled backslashes of JSON.
pub struct Redactor {
    homes: Vec<String>,
    users: Vec<String>,
}

fn is_word(c: char) -> bool {
    c.is_alphanumeric() || c == '_'
}

/// Bytes of `rest` that match `needle` (already lower case) at its start.
fn match_len(rest: &str, needle: &[char]) -> Option<usize> {
    let mut k = 0;
    for (i, c) in rest.char_indices() {
        for lower in c.to_lowercase() {
            if needle.get(k) != Some(&lower) {
                return None;
            }
            k += 1;
        }
        if k == needle.len() {
            return Some(i + c.len_utf8());
        }
    }
    None
}

/// Replaces `needle` case-insensitively where it is not followed by a letter
/// or digit (so C:\Users\Al stays out of C:\Users\Alan), and with `word` not
/// preceded by one either.
fn replace_ci(text: &str, needle: &str, with: &str, word: bool) -> String {
    let needle: Vec<char> = needle.chars().flat_map(char::to_lowercase).collect();
    let Some(&first) = needle.first() else { return text.to_string() };
    let mut out = String::with_capacity(text.len());
    let (mut pos, mut copied) = (0, 0);
    let mut prev: Option<char> = None;
    while let Some(c) = text[pos..].chars().next() {
        if c.to_lowercase().next() == Some(first) && !(word && prev.is_some_and(is_word)) {
            if let Some(len) = match_len(&text[pos..], &needle) {
                if !text[pos + len..].chars().next().is_some_and(is_word) {
                    out.push_str(&text[copied..pos]);
                    out.push_str(with);
                    prev = text[pos..pos + len].chars().last();
                    pos += len;
                    copied = pos;
                    continue;
                }
            }
        }
        prev = Some(c);
        pos += c.len_utf8();
    }
    out.push_str(&text[copied..]);
    out
}

impl Redactor {
    pub fn new(home: Option<&Path>, users: &[String]) -> Self {
        let mut homes = Vec::new();
        // A root folder is no one's; replacing it would wreck every path.
        if let Some(home) = home.filter(|h| h.file_name().is_some()) {
            let text = home.to_string_lossy();
            let text = text.trim_end_matches(['\\', '/']);
            let back = text.replace('/', "\\");
            let forward = text.replace('\\', "/");
            for form in [back.replace('\\', "\\\\"), forward.replace('/', "\\/"), back, forward] {
                if !homes.contains(&form) {
                    homes.push(form);
                }
            }
        }
        let mut names: Vec<String> = Vec::new();
        for user in users.iter().map(|u| u.trim()) {
            if user.chars().count() >= 2 && !names.iter().any(|n| n.to_lowercase() == user.to_lowercase()) {
                names.push(user.to_string());
            }
        }
        // Longer names first, so "Alan Smithee" goes before "Alan".
        names.sort_by_key(|n| std::cmp::Reverse(n.len()));
        Redactor { homes, users: names }
    }

    /// The current user's home folder and name (and the folder's own name,
    /// which differs from the user name after an account rename).
    pub fn from_env() -> Self {
        let home = dirs::home_dir();
        let mut users: Vec<String> = ["USERNAME", "USER"].iter().filter_map(|v| std::env::var(v).ok()).collect();
        if let Some(folder) = home.as_ref().and_then(|h| h.file_name()) {
            users.push(folder.to_string_lossy().into_owned());
        }
        Redactor::new(home.as_deref(), &users)
    }

    pub fn apply(&self, text: &str) -> String {
        let mut text = text.to_string();
        for home in &self.homes {
            text = replace_ci(&text, home, "%USERPROFILE%", false);
        }
        for user in &self.users {
            text = replace_ci(&text, user, "<user>", true);
        }
        text
    }
}

// ---- what goes in -----------------------------------------------------------------

/// The end of a log file, starting at a whole line.
fn log_tail(path: &Path) -> Option<String> {
    let mut file = File::open(path).ok()?;
    let len = file.metadata().ok()?.len();
    let start = len.saturating_sub(LOG_TAIL);
    file.seek(SeekFrom::Start(start)).ok()?;
    let mut bytes = Vec::new();
    file.read_to_end(&mut bytes).ok()?;
    let text = String::from_utf8_lossy(&bytes);
    if start == 0 {
        return Some(text.into_owned());
    }
    let whole = text.find('\n').map_or(&text[..], |i| &text[i + 1..]);
    Some(format!("[the first {start} bytes are left out]\n{whole}"))
}

fn sha256(path: &Path) -> Option<String> {
    let mut file = File::open(path).ok()?;
    let mut hasher = Sha256::new();
    let mut buf = vec![0u8; 64 * 1024];
    loop {
        let n = file.read(&mut buf).ok()?;
        if n == 0 {
            break;
        }
        hasher.update(&buf[..n]);
    }
    Some(hasher.finalize().iter().map(|b| format!("{b:02x}")).collect())
}

/// Names and sizes in `dir` (and folders below it, `depth` levels down), with
/// the SHA-256 of each DLL.
fn listing(dir: &Path, depth: u32, indent: usize, out: &mut String) {
    let Ok(entries) = fs::read_dir(dir) else {
        out.push_str(&format!("{:indent$}(cannot read {})\n", "", dir.display()));
        return;
    };
    let mut entries: Vec<_> = entries.flatten().collect();
    entries.sort_by_key(|e| e.file_name().to_string_lossy().to_lowercase());
    for e in entries {
        let name = e.file_name().to_string_lossy().into_owned();
        let Ok(meta) = e.metadata() else { continue };
        if meta.is_dir() {
            out.push_str(&format!("{:indent$}{name}/\n", ""));
            if depth > 0 {
                listing(&e.path(), depth - 1, indent + 2, out);
            }
        } else {
            let dll = Path::new(&name).extension().is_some_and(|x| x.eq_ignore_ascii_case("dll"));
            let hash = if dll { sha256(&e.path()).unwrap_or_default() } else { String::new() };
            out.push_str(&format!("{:indent$}{name}  {} bytes  {hash}\n", "", meta.len()).replace("  \n", "\n"));
        }
    }
}

#[cfg(windows)]
fn os_version() -> String {
    use winreg::enums::HKEY_LOCAL_MACHINE;
    use winreg::RegKey;
    let Ok(key) = RegKey::predef(HKEY_LOCAL_MACHINE).open_subkey(r"SOFTWARE\Microsoft\Windows NT\CurrentVersion")
    else {
        return "Windows (version unknown)".into();
    };
    let text = |name: &str| key.get_value::<String, _>(name).unwrap_or_default();
    let build = text("CurrentBuildNumber");
    let ubr: u32 = key.get_value("UBR").unwrap_or(0);
    let mut product = text("ProductName");
    // Windows 11 still calls itself Windows 10 here; its builds start at 22000.
    if build.parse::<u32>().is_ok_and(|b| b >= 22000) {
        product = product.replace("Windows 10", "Windows 11");
    }
    let release = Some(text("DisplayVersion")).filter(|v| !v.is_empty()).unwrap_or_else(|| text("ReleaseId"));
    format!("{product} {release} (build {build}.{ubr}), {}", std::env::consts::ARCH)
}

#[cfg(not(windows))]
fn os_version() -> String {
    let release = fs::read_to_string("/etc/os-release").unwrap_or_default();
    let pretty = release.lines().find_map(|l| l.strip_prefix("PRETTY_NAME=")).map(|v| v.trim_matches('"').to_string());
    format!("{} ({}), {}", pretty.unwrap_or_else(|| "unknown".into()), std::env::consts::OS, std::env::consts::ARCH)
}

#[derive(Serialize)]
#[serde(rename_all = "camelCase")]
struct Overview {
    game: Option<detect::GameCheck>,
    sdk: game::SdkStatus,
    game_running: bool,
    saves: saves::SavesInfo,
    build_folder: Option<PathBuf>,
}

/// The report's files (name in the zip, text), before redaction.
pub fn collect(cfg: &Config, version: &str, tasks: Option<&str>) -> Vec<(String, String)> {
    let mut files: Vec<(String, String)> = vec![("README.txt".into(), README.into())];
    files.push((
        "about.txt".into(),
        format!(
            "T3SDK Launcher {version}\n{}\nCollected {}\n",
            os_version(),
            chrono::Local::now().format("%Y-%m-%d %H:%M:%S %:z")
        ),
    ));
    let overview = Overview {
        game: cfg.game_dir.as_deref().map(detect::game_check),
        sdk: game::sdk_status(cfg),
        game_running: game::game_running(),
        saves: saves::locate(cfg),
        build_folder: cfg.build_root(),
    };
    files.push(("overview.json".into(), serde_json::to_string_pretty(&overview).unwrap_or_default()));
    files.push(("launcher.json".into(), serde_json::to_string_pretty(cfg).unwrap_or_default()));

    if let Some(game) = &cfg.game_dir {
        let system = game.join("System");
        if let Ok(entries) = fs::read_dir(&system) {
            let mut logs: Vec<PathBuf> = entries
                .flatten()
                .map(|e| e.path())
                .filter(|p| {
                    let name = p.file_name().map(|n| n.to_string_lossy().to_lowercase()).unwrap_or_default();
                    name.starts_with("t3sdk") && name.contains(".log") && p.is_file()
                })
                .collect();
            logs.sort();
            for log in logs {
                if let Some(text) = log_tail(&log) {
                    files.push((format!("System/{}", log.file_name().unwrap().to_string_lossy()), text));
                }
            }
        }
        if let Ok(text) = fs::read_to_string(system.join("T3SDK.ini")) {
            files.push(("System/T3SDK.ini".into(), text));
        }
        for name in MOD_FILES {
            if let Ok(text) = fs::read_to_string(system.join("mods").join(name)) {
                files.push((format!("System/mods/{name}"), text));
            }
        }
        let mut list = format!("{}\n", system.display());
        listing(&system, 0, 2, &mut list);
        list.push_str(&format!("\n{}\n", system.join("mods").display()));
        listing(&system.join("mods"), 2, 2, &mut list);
        files.push(("listing.txt".into(), list));
    }
    if let Some(manifest) = cfg.build_root().map(|b| b.join("sdk").join("deployed.json")) {
        if let Ok(text) = fs::read_to_string(manifest) {
            files.push(("deployed.json".into(), text));
        }
    }
    if let Some(tasks) = tasks.filter(|t| !t.trim().is_empty()) {
        files.push(("tasks.txt".into(), tasks.to_string()));
    }
    files
}

pub fn write_report(path: &Path, files: &[(String, String)], redactor: &Redactor) -> Result<LogsReport, String> {
    let fail = |e: &dyn std::fmt::Display| format!("cannot write {}: {e}", path.display());
    let mut zip = zip::ZipWriter::new(File::create(path).map_err(|e| fail(&e))?);
    let options = SimpleFileOptions::default()
        .compression_method(zip::CompressionMethod::Deflated)
        .last_modified_time(saves::zip_time(std::time::SystemTime::now()));
    for (name, text) in files {
        zip.start_file(name.as_str(), options).map_err(|e| fail(&e))?;
        zip.write_all(redactor.apply(text).as_bytes()).map_err(|e| fail(&e))?;
    }
    zip.finish().map_err(|e| fail(&e))?;
    let bytes = fs::metadata(path).map(|m| m.len()).unwrap_or(0);
    Ok(LogsReport { path: path.to_path_buf(), files: files.len(), bytes })
}

/// Writes the report to `path` (chosen in a save dialog). `tasks` is the
/// text of recent task output, from the UI.
#[tauri::command]
pub async fn collect_logs(
    app: AppHandle,
    state: State<'_, AppState>,
    path: PathBuf,
    tasks: Option<String>,
) -> Result<LogsReport, String> {
    if !path.extension().is_some_and(|x| x.eq_ignore_ascii_case("zip")) {
        return Err("save the report as a .zip file".into());
    }
    let cfg = state.config.lock().unwrap().clone();
    let version = app.package_info().version.to_string();
    let work = move || write_report(&path, &collect(&cfg, &version, tasks.as_deref()), &Redactor::from_env());
    tauri::async_runtime::spawn_blocking(work).await.map_err(|e| e.to_string())?
}

#[cfg(test)]
mod tests {
    use super::*;

    fn redactor() -> Redactor {
        Redactor::new(Some(Path::new(r"C:\Users\Alan")), &["Alan".into(), "a".into()])
    }

    #[test]
    fn redacts_the_home_folder_in_every_spelling() {
        let r = redactor();
        assert_eq!(r.apply(r"loaded C:\Users\Alan\Games\x.dll"), r"loaded %USERPROFILE%\Games\x.dll");
        assert_eq!(r.apply(r"c:\users\ALAN\AppData"), r"%USERPROFILE%\AppData");
        assert_eq!(r.apply("file:///C:/Users/Alan/Documents"), "file:///%USERPROFILE%/Documents");
        assert_eq!(r.apply(r#"{"gameDir": "C:\\Users\\Alan\\Steam"}"#), r#"{"gameDir": "%USERPROFILE%\\Steam"}"#);
        assert_eq!(r.apply(r#""C:\/Users\/Alan\/x""#), r#""%USERPROFILE%\/x""#);
        assert_eq!(r.apply(r"C:\Users\Alan"), "%USERPROFILE%");
        assert_eq!(r.apply(r"C:\Users\Alan."), "%USERPROFILE%.");
    }

    #[test]
    fn redacts_the_user_name_as_a_word() {
        let r = redactor();
        assert_eq!(r.apply(r"D:\Games\alan\Thief"), r"D:\Games\<user>\Thief");
        assert_eq!(r.apply("user ALAN logged in"), "user <user> logged in");
        assert_eq!(r.apply(r"C:\Users\ALANSM~1\x"), r"C:\Users\ALANSM~1\x");
        assert_eq!(r.apply("Alanis and Catalan stay"), "Alanis and Catalan stay");
        assert_eq!(r.apply(r"C:\Users\Alan2\x"), r"C:\Users\Alan2\x");
        // One-letter names would take out every "a".
        assert_eq!(r.apply("a b c"), "a b c");
    }

    #[test]
    fn redaction_keeps_other_text() {
        let r = Redactor::new(Some(Path::new("/home/zoë")), &["Zoë".into()]);
        assert_eq!(r.apply("/home/ZOË/.steam and ünïcode"), "%USERPROFILE%/.steam and ünïcode");
        assert_eq!(r.apply("zoë"), "<user>");
        assert_eq!(r.apply(""), "");
        let nobody = Redactor::new(Some(Path::new("/")), &[]);
        assert_eq!(nobody.apply("/usr/bin"), "/usr/bin");
    }

    #[test]
    fn report_holds_the_game_files_redacted() {
        let tmp = tempfile::tempdir().unwrap();
        let game = tmp.path().join("Thief");
        let mods = game.join("System").join("mods");
        fs::create_dir_all(mods.join("disabled")).unwrap();
        fs::write(game.join("System").join("T3SDK.log"), "T3SDK in C:\\Users\\Alan\\Thief\\System\n").unwrap();
        fs::write(game.join("System").join("T3SDK.ini"), "[T3SDK]\nConsole=0\n").unwrap();
        fs::write(game.join("System").join("Engine.dll"), b"MZ").unwrap();
        fs::write(mods.join("load-order.txt"), "hello\n").unwrap();
        fs::write(mods.join("disabled").join("old.dll"), b"MZ").unwrap();
        let cfg = Config { game_dir: Some(game), ..Config::default() };

        let files = collect(&cfg, "9.9.9", Some("== Install T3SDK\nok\n"));
        let names: Vec<&str> = files.iter().map(|(n, _)| n.as_str()).collect();
        for expected in [
            "README.txt",
            "about.txt",
            "overview.json",
            "launcher.json",
            "System/T3SDK.log",
            "System/T3SDK.ini",
            "System/mods/load-order.txt",
            "listing.txt",
            "tasks.txt",
        ] {
            assert!(names.contains(&expected), "{expected} missing from {names:?}");
        }
        let listing = &files.iter().find(|(n, _)| n == "listing.txt").unwrap().1;
        assert!(listing.contains("T3SDK.ini  18 bytes\n"), "{listing}");
        assert!(listing.contains("    old.dll  2 bytes  "), "{listing}");
        // Both DLLs hold the same two bytes, so the same hash appears twice.
        let hash = sha256(&tmp.path().join("Thief/System/Engine.dll")).unwrap();
        assert_eq!(hash.len(), 64);
        assert_eq!(listing.matches(&hash).count(), 2, "{listing}");

        let out = tmp.path().join("report.zip");
        let report = write_report(&out, &files, &redactor()).unwrap();
        assert_eq!(report.files, files.len());
        let mut archive = zip::ZipArchive::new(File::open(&out).unwrap()).unwrap();
        let mut log = String::new();
        archive.by_name("System/T3SDK.log").unwrap().read_to_string(&mut log).unwrap();
        assert_eq!(log, "T3SDK in %USERPROFILE%\\Thief\\System\n");
    }

    #[test]
    fn long_logs_keep_their_end() {
        let tmp = tempfile::tempdir().unwrap();
        let path = tmp.path().join("T3SDK.log");
        let line = "0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcde\n";
        let count = (LOG_TAIL as usize / line.len()) + 10;
        fs::write(&path, line.repeat(count) + "last line\n").unwrap();
        let tail = log_tail(&path).unwrap();
        assert!(tail.starts_with("[the first "));
        assert!(tail.ends_with("last line\n"));
        assert!(tail.lines().skip(1).all(|l| l == line.trim_end() || l == "last line"));
    }
}
