// Long-running tool jobs (SDK install, map export, repack...), each one a
// T3SDK command-line tool run as a child process. Output lines stream to the UI
// as `task-output` events and the end as a `task-exit` event.
//
// The UI names a job; this side builds its command line, so the webview can
// only start the tools listed here.
use std::collections::HashMap;
use std::ffi::OsString;
use std::io::{BufRead, BufReader, Read};
use std::path::PathBuf;
use std::process::{Child, Stdio};
use std::sync::atomic::{AtomicU32, Ordering};
use std::sync::{Arc, Mutex};
use std::time::Duration;

use serde::{Deserialize, Serialize};
use tauri::{AppHandle, Emitter, State};

use crate::config::Config;
use crate::{proc, AppState};

#[derive(Debug, Deserialize)]
#[serde(tag = "kind", rename_all = "camelCase")]
pub enum TaskSpec {
    /// tools/sdk.py build (needs Visual Studio with the C++ tools).
    SdkBuild,
    /// tools/sdk.py deploy: install T3SDK into System/.
    SdkDeploy,
    /// tools/sdk.py undeploy: remove exactly what deploy installed.
    SdkUndeploy,
    /// tools/assets/t3map.py: export one map, or every map, to the Godot project.
    Export { level: Option<String> },
    /// Godot --headless --import, so the viewer and editor open without waiting.
    Import,
    /// tools/assets/godot_check.py: load every exported scene headlessly.
    GodotCheck,
    /// tools/assets/t3pack.py roundtrip: rewrite unchanged maps and compare.
    Roundtrip { level: Option<String> },
    /// tools/assets/t3pack.py apply: build a patched map from <id>.edits.json.
    Repack { level: String },
    /// tools/assets/t3pack.py install: put a patched map into the game (backs up the original once).
    Install { level: String },
    /// tools/assets/t3pack.py restore: put original maps back.
    Restore { level: Option<String> },
    /// tools/assets/t3texpack.py apply --pack System/mods/<id> ... for these
    /// mods (the enabled ones with textures/, in load order; none restores
    /// every patched bundle). Recorded in state.json when it succeeds.
    TexturePacks { mods: Vec<String> },
    /// tools/assets/t3texpack.py restore, before a sync that places or
    /// removes game bundles (.ibt); when it succeeds, that sync runs.
    TextureRestore,
}

#[derive(Debug, Clone, Serialize)]
#[serde(rename_all = "camelCase")]
pub struct TaskStarted {
    pub id: u32,
    pub title: String,
    pub command: String,
}

#[derive(Debug, Clone, Serialize)]
#[serde(rename_all = "camelCase")]
struct TaskOutput {
    id: u32,
    stream: &'static str,
    line: String,
}

#[derive(Debug, Clone, Serialize)]
#[serde(rename_all = "camelCase")]
struct TaskExit {
    id: u32,
    code: Option<i32>,
    cancelled: bool,
}

#[derive(Default)]
pub struct Tasks {
    next: AtomicU32,
    running: Mutex<HashMap<u32, Arc<Mutex<Child>>>>,
    cancelled: Mutex<Vec<u32>>,
}

/// Runs once the job has succeeded.
type After = Box<dyn FnOnce() -> Result<(), String> + Send>;

struct Plan {
    title: String,
    program: PathBuf,
    args: Vec<OsString>,
    cwd: PathBuf,
    after: Option<After>,
}

fn check_level(level: &str) -> Result<&str, String> {
    if level.is_empty() || level.contains(['/', '\\', ':', '"']) || level.starts_with('-') {
        return Err(format!("invalid map id {level:?}"));
    }
    Ok(level)
}

fn plan(spec: &TaskSpec, cfg: &Config) -> Result<Plan, String> {
    let root = cfg.root()?;
    let tool = |rel: &str| -> Result<OsString, String> {
        let path = root.join("tools").join(rel);
        if !path.is_file() {
            return Err(format!("{} not found: update the T3SDK folder", path.display()));
        }
        Ok(path.into_os_string())
    };
    let python = |title: String, args: Vec<OsString>| -> Result<Plan, String> {
        Ok(Plan { title, program: cfg.python()?, args, cwd: root.clone(), after: None })
    };
    let project = || cfg.project().ok_or_else(|| "no Godot project folder".to_string());
    let one_or_all = |level: &Option<String>| -> Result<Vec<OsString>, String> {
        Ok(match level {
            Some(l) => vec![check_level(l)?.into()],
            None => vec!["--all".into()],
        })
    };
    let name = |level: &Option<String>| level.clone().unwrap_or_else(|| "all maps".into());
    match spec {
        TaskSpec::SdkBuild => python("Build T3SDK".into(), vec![tool("sdk.py")?, "build".into()]),
        TaskSpec::SdkDeploy => python("Install T3SDK".into(), vec![tool("sdk.py")?, "deploy".into()]),
        TaskSpec::SdkUndeploy => python("Remove T3SDK".into(), vec![tool("sdk.py")?, "undeploy".into()]),
        TaskSpec::Export { level } => {
            let mut args = vec![tool("assets/t3map.py")?];
            args.extend(one_or_all(level)?);
            args.extend(["-o".into(), project()?.into_os_string()]);
            python(format!("Export {}", name(level)), args)
        }
        TaskSpec::Import => Ok(Plan {
            title: "Import into Godot".into(),
            program: cfg.godot()?,
            args: vec!["--headless".into(), "--path".into(), project()?.into_os_string(), "--import".into()],
            cwd: root.clone(),
            after: None,
        }),
        TaskSpec::GodotCheck => {
            let args = vec![
                tool("assets/godot_check.py")?,
                "--godot".into(),
                cfg.godot()?.into_os_string(),
                "--project".into(),
                project()?.into_os_string(),
            ];
            python("Check the Godot project".into(), args)
        }
        TaskSpec::Roundtrip { level } => {
            let mut args = vec![tool("assets/t3pack.py")?, "roundtrip".into()];
            args.extend(one_or_all(level)?);
            python(format!("Round-trip check: {}", name(level)), args)
        }
        TaskSpec::Repack { level } => {
            let l = check_level(level)?;
            let edits = project()?.join(l).join(format!("{l}.edits.json"));
            if !edits.is_file() {
                return Err(format!("no edits for {l}: save them in Godot first ({})", edits.display()));
            }
            python(format!("Repack {l}"), vec![tool("assets/t3pack.py")?, "apply".into(), edits.into_os_string()])
        }
        TaskSpec::Install { level } => {
            let l = check_level(level)?;
            let patched = cfg.assets_build().ok_or("no T3SDK folder")?.join("patched").join(format!("{l}.gmp"));
            if !patched.is_file() {
                return Err(format!("{l} has not been repacked yet"));
            }
            python(format!("Install {l}"), vec![tool("assets/t3pack.py")?, "install".into(), patched.into_os_string()])
        }
        TaskSpec::Restore { level } => {
            let mut args = vec![tool("assets/t3pack.py")?, "restore".into()];
            args.extend(one_or_all(level)?);
            python(format!("Restore {}", name(level)), args)
        }
        TaskSpec::TexturePacks { mods } => {
            let game = cfg.game()?;
            let mut args = vec![tool("assets/t3texpack.py")?, "apply".into()];
            for dir in crate::mods::texture_packs(&game, mods)? {
                args.extend(["--pack".into(), dir.into_os_string()]);
            }
            let title = match mods.is_empty() {
                true => "Restore the original textures".to_string(),
                false => format!("Apply texture packs: {}", mods.join(", ")),
            };
            let fingerprint = crate::mods::texture_fingerprint(&game, mods);
            let mut plan = python(title, args)?;
            plan.after = Some(Box::new(move || crate::mods::record_textures(&game, fingerprint)));
            Ok(plan)
        }
        TaskSpec::TextureRestore => {
            let game = cfg.game()?;
            let args = vec![tool("assets/t3texpack.py")?, "restore".into()];
            let mut plan = python("Restore the game's bundles, then place the mods' bundles".into(), args)?;
            plan.after = Some(Box::new(move || crate::mods::place_bundles(&game)));
            Ok(plan)
        }
    }
}

fn quote(arg: &std::ffi::OsStr) -> String {
    let s = arg.to_string_lossy();
    if s.contains(' ') {
        format!("\"{s}\"")
    } else {
        s.into_owned()
    }
}

/// `line` without terminal escape sequences: Godot colours its progress lines
/// (ESC[90m ... ESC[0m) even when its output is a pipe, and ignores NO_COLOR.
fn strip_escapes(line: &str) -> String {
    let mut out = String::with_capacity(line.len());
    let mut chars = line.chars();
    while let Some(c) = chars.next() {
        if c != '\x1b' {
            out.push(c);
            continue;
        }
        match chars.next() {
            // CSI: parameters, then one final character from @ to ~.
            Some('[') => {
                for c in chars.by_ref() {
                    if ('@'..='~').contains(&c) {
                        break;
                    }
                }
            }
            // OSC: up to BEL, or ESC \.
            Some(']') => {
                while let Some(c) = chars.next() {
                    if c == '\x07' {
                        break;
                    }
                    if c == '\x1b' {
                        chars.next();
                        break;
                    }
                }
            }
            // Other escapes: intermediates (space to /), then one final character.
            Some(c) if (' '..='/').contains(&c) => {
                for c in chars.by_ref() {
                    if !(' '..='/').contains(&c) {
                        break;
                    }
                }
            }
            _ => {}
        }
    }
    out
}

/// Emits each line of `stream`; tools print progress with \r as well as \n.
fn pump(app: AppHandle, id: u32, name: &'static str, stream: impl Read + Send + 'static) {
    std::thread::spawn(move || {
        let mut reader = BufReader::new(stream);
        let mut buf = Vec::new();
        loop {
            buf.clear();
            match reader.read_until(b'\n', &mut buf) {
                Ok(0) | Err(_) => break,
                Ok(_) => {
                    let text = String::from_utf8_lossy(&buf);
                    for line in text.trim_end_matches(['\r', '\n']).split('\r') {
                        let _ = app.emit("task-output", TaskOutput { id, stream: name, line: strip_escapes(line) });
                    }
                }
            }
        }
    });
}

#[tauri::command]
pub async fn start_task(app: AppHandle, state: State<'_, AppState>, spec: TaskSpec) -> Result<TaskStarted, String> {
    let cfg = state.config.lock().unwrap().clone();
    let mut plan = plan(&spec, &cfg)?;
    let after = plan.after.take();
    let command = std::iter::once(plan.program.as_os_str())
        .chain(plan.args.iter().map(|a| a.as_os_str()))
        .map(quote)
        .collect::<Vec<_>>()
        .join(" ");

    let mut cmd = proc::quiet(&plan.program);
    cmd.args(&plan.args).current_dir(&plan.cwd).stdin(Stdio::null()).stdout(Stdio::piped()).stderr(Stdio::piped());
    cmd.env("PYTHONUNBUFFERED", "1").env("PYTHONIOENCODING", "utf-8");
    // Every T3SDK tool honours these, so no per-tool flags are needed.
    if let Some(game) = &cfg.game_dir {
        cmd.env("T3_GAME_DIR", game);
    }
    if let Some(build) = cfg.build_root() {
        cmd.env("T3SDK_BUILD_DIR", build);
    }
    if let Some(godot) = &cfg.godot {
        cmd.env("GODOT", godot);
    }
    let mut child = cmd.spawn().map_err(|e| format!("cannot start {}: {e}", plan.program.display()))?;

    let id = state.tasks.next.fetch_add(1, Ordering::Relaxed) + 1;
    if let Some(out) = child.stdout.take() {
        pump(app.clone(), id, "stdout", out);
    }
    if let Some(err) = child.stderr.take() {
        pump(app.clone(), id, "stderr", err);
    }
    let child = Arc::new(Mutex::new(child));
    state.tasks.running.lock().unwrap().insert(id, child.clone());

    let waiter = app.clone();
    std::thread::spawn(move || {
        // Poll instead of wait(), so cancel_task can take the lock and kill.
        let status = loop {
            match child.lock().unwrap().try_wait() {
                Ok(Some(status)) => break Some(status),
                Ok(None) => {}
                Err(_) => break None,
            }
            std::thread::sleep(Duration::from_millis(100));
        };
        // Let the output threads drain before announcing the end.
        std::thread::sleep(Duration::from_millis(150));
        let tasks = &tauri::Manager::state::<AppState>(&waiter).tasks;
        tasks.running.lock().unwrap().remove(&id);
        let cancelled = {
            let mut list = tasks.cancelled.lock().unwrap();
            let was = list.contains(&id);
            list.retain(|c| *c != id);
            was
        };
        let mut code = status.and_then(|s| s.code());
        if let (Some(after), Some(true), false) = (after, status.map(|s| s.success()), cancelled) {
            if let Err(text) = after() {
                for line in text.lines() {
                    let _ = waiter.emit("task-output", TaskOutput { id, stream: "stderr", line: line.to_string() });
                }
                // The tool worked but the launcher's part did not: the job failed.
                code = Some(1);
            }
        }
        let _ = waiter.emit("task-exit", TaskExit { id, code, cancelled });
    });
    Ok(TaskStarted { id, title: plan.title, command })
}

#[tauri::command]
pub async fn cancel_task(state: State<'_, AppState>, id: u32) -> Result<(), String> {
    let Some(child) = state.tasks.running.lock().unwrap().get(&id).cloned() else { return Ok(()) };
    state.tasks.cancelled.lock().unwrap().push(id);
    let mut child = child.lock().unwrap();
    #[cfg(windows)]
    {
        // Take the whole tree down: tools start Godot as their own child.
        let mut kill = proc::quiet(std::path::Path::new("taskkill"));
        kill.args(["/T", "/F", "/PID", &child.id().to_string()]);
        if proc::probe(kill, Duration::from_secs(10)).is_some() {
            return Ok(());
        }
    }
    child.kill().map_err(|e| e.to_string())
}

#[cfg(test)]
mod tests {
    use super::strip_escapes;

    #[test]
    fn escapes_are_stripped_from_tool_output() {
        let godot =
            "[  16% ] \x1b[90m\x1b[1mfirst_scan_filesystem\x1b[22m | Loading global class names...\x1b[39m\x1b[0m";
        assert_eq!(strip_escapes(godot), "[  16% ] first_scan_filesystem | Loading global class names...");
        assert_eq!(strip_escapes("\x1b]0;title\x07done \x1b(B\u{e9}"), "done \u{e9}");
        assert_eq!(strip_escapes("plain text"), "plain text");
    }
}
