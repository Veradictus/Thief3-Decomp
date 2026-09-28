// What is installed in System/mods/ (docs/mods.md, "Installed layout"): one
// folder per package, named by its id, and loose DLLs, switched off by moving
// them into disabled/.
use std::path::{Path, PathBuf};
use std::time::UNIX_EPOCH;

use serde::Serialize;

use super::files::{self, FileRef};
use super::manifest::{self, Manifest, RESERVED_IDS};

/// The API version of the SDK this launcher ships with
/// (T3SDK_API_VERSION in sdk/include/t3sdk/t3sdk.h; a test keeps them equal).
pub const SDK_API_VERSION: u32 = 1;

#[derive(Clone, Debug)]
pub struct Layout {
    pub game: PathBuf,
    /// System/mods/
    pub dir: PathBuf,
}

impl Layout {
    pub fn new(game: &Path) -> Layout {
        Layout { game: game.to_path_buf(), dir: game.join("System").join("mods") }
    }
    pub fn package(&self, id: &str) -> PathBuf {
        self.dir.join(id)
    }
    pub fn state(&self) -> PathBuf {
        self.dir.join("state.json")
    }
    pub fn overlay(&self) -> PathBuf {
        self.dir.join("overlay.json")
    }
    pub fn load_order(&self) -> PathBuf {
        self.dir.join("load-order.txt")
    }
    pub fn originals(&self) -> PathBuf {
        self.dir.join("originals")
    }
    pub fn disabled(&self) -> PathBuf {
        self.dir.join("disabled")
    }
}

/// The installed SDK, as far as the checks need it.
#[derive(Clone, Copy, Debug, Serialize)]
#[serde(rename_all = "camelCase")]
pub struct SdkInfo {
    /// System/dinput8.dll exists.
    pub installed: bool,
    /// Its T3SDK_API_VERSION.
    pub api: u32,
}

/// T3SDK_API_VERSION from a T3SDK folder's sdk/include/t3sdk/t3sdk.h, if it has one.
pub fn header_api_version(sdk_root: &Path) -> Option<u32> {
    let header = std::fs::read_to_string(sdk_root.join("sdk").join("include").join("t3sdk").join("t3sdk.h")).ok()?;
    header
        .lines()
        .find_map(|line| line.trim().strip_prefix("#define T3SDK_API_VERSION")?.split_whitespace().next()?.parse().ok())
}

/// The SDK is deployed from the T3SDK folder, so its header tells the API
/// version; the launcher's own copy of the tools has no header, and then the
/// SDK is the one the launcher ships with.
pub fn sdk_info(game: &Path, sdk_root: Option<&Path>) -> SdkInfo {
    SdkInfo {
        installed: game.join("System").join("dinput8.dll").is_file(),
        api: sdk_root.and_then(header_api_version).unwrap_or(SDK_API_VERSION),
    }
}

/// An entry of `dir` whose name matches `name` case-insensitively.
pub fn find_ci(dir: &Path, name: &str) -> Option<PathBuf> {
    let exact = dir.join(name);
    if exact.exists() {
        return Some(exact);
    }
    std::fs::read_dir(dir)
        .ok()?
        .flatten()
        .find(|e| e.file_name().to_string_lossy().eq_ignore_ascii_case(name))
        .map(|e| e.path())
}

/// An installed package folder.
#[derive(Clone, Debug)]
pub struct Package {
    /// The manifest's id (the folder's name when the manifest cannot be read).
    pub id: String,
    pub dir: PathBuf,
    /// The manifest, or why the package cannot be used.
    pub manifest: Result<Manifest, String>,
    /// The `entry` DLL is there.
    pub entry_found: bool,
    /// Files under files/ and textures/.
    pub files: Vec<FileRef>,
    pub textures: Vec<FileRef>,
    pub size: u64,
}

impl Package {
    pub fn ok(&self) -> Option<&Manifest> {
        self.manifest.as_ref().ok()
    }

    pub fn has_code(&self) -> bool {
        self.ok().is_some_and(|m| m.entry.is_some())
    }
}

pub fn read_manifest(dir: &Path) -> Result<Manifest, String> {
    let file = find_ci(dir, "mod.json").ok_or("no mod.json")?;
    let meta = std::fs::metadata(&file).map_err(|e| format!("cannot read mod.json: {e}"))?;
    if meta.len() > 1024 * 1024 {
        return Err("mod.json is larger than 1 MB".into());
    }
    let bytes = std::fs::read(&file).map_err(|e| format!("cannot read mod.json: {e}"))?;
    let text = String::from_utf8(bytes).map_err(|_| "mod.json is not UTF-8".to_string())?;
    manifest::parse(&text).map_err(|e| format!("mod.json: {}", manifest::describe(&e)))
}

pub fn read_package(dir: &Path) -> Package {
    let folder = dir.file_name().map(|n| n.to_string_lossy().into_owned()).unwrap_or_default();
    let manifest = read_manifest(dir).and_then(|m| {
        if m.id.eq_ignore_ascii_case(&folder) {
            Ok(m)
        } else {
            Err(format!("the folder is named {folder}, but mod.json says its id is {}", m.id))
        }
    });
    let entry_found = manifest
        .as_ref()
        .ok()
        .and_then(|m| m.entry.as_deref())
        .is_some_and(|e| find_ci(dir, e).is_some_and(|p| p.is_file()));
    let sub = |name: &str| find_ci(dir, name).filter(|p| p.is_dir()).map(|p| files::walk(&p)).unwrap_or_default();
    Package {
        id: manifest.as_ref().map_or_else(|_| folder.clone(), |m| m.id.clone()),
        dir: dir.to_path_buf(),
        entry_found,
        files: sub("files"),
        textures: sub("textures"),
        size: files::tree_size(dir),
        manifest,
    }
}

/// Names of the folders of System/mods that hold a mod.json, sorted. Hidden
/// folders (the launcher's temporary ones) and the reserved ones are not
/// packages.
pub fn package_dirs(layout: &Layout) -> Vec<String> {
    let Ok(entries) = std::fs::read_dir(&layout.dir) else { return Vec::new() };
    let mut names: Vec<String> = entries
        .flatten()
        .filter(|e| e.file_type().is_ok_and(|t| t.is_dir()))
        .map(|e| e.file_name().to_string_lossy().into_owned())
        .filter(|name| !name.starts_with('.') && !RESERVED_IDS.contains(&name.to_lowercase().as_str()))
        .filter(|name| find_ci(&layout.dir.join(name), "mod.json").is_some())
        .collect();
    names.sort_by_key(|n| n.to_lowercase());
    names
}

/// The installed packages, in folder order.
pub fn scan(layout: &Layout) -> Vec<Package> {
    let mut packages: Vec<Package> = Vec::new();
    for name in package_dirs(layout) {
        let mut p = read_package(&layout.dir.join(&name));
        if packages.iter().any(|q| q.id == p.id) {
            // Two folders whose names differ only in case (possible off Windows).
            p.manifest = Err(format!("another folder is also named {}", p.id));
            p.id = name;
            if packages.iter().any(|q| q.id == p.id) {
                continue;
            }
        }
        packages.push(p);
    }
    packages
}

// ---- loose DLLs -----------------------------------------------------------------

#[derive(Clone, Debug, Serialize)]
#[serde(rename_all = "camelCase")]
pub struct LooseMod {
    pub name: String,
    pub enabled: bool,
    pub size: u64,
    pub modified: Option<u64>,
}

/// System/mods/*.dll (enabled) and System/mods/disabled/*.dll, by name.
pub fn loose(layout: &Layout) -> Vec<LooseMod> {
    let mut list = Vec::new();
    for (dir, enabled) in [(layout.dir.clone(), true), (layout.disabled(), false)] {
        let Ok(entries) = std::fs::read_dir(&dir) else { continue };
        for e in entries.flatten() {
            let path = e.path();
            if path.is_file() && path.extension().is_some_and(|x| x.eq_ignore_ascii_case("dll")) {
                let meta = e.metadata().ok();
                list.push(LooseMod {
                    name: path.file_stem().unwrap_or_default().to_string_lossy().into_owned(),
                    enabled,
                    size: meta.as_ref().map_or(0, |m| m.len()),
                    modified: meta
                        .and_then(|m| m.modified().ok())
                        .and_then(|t| t.duration_since(UNIX_EPOCH).ok())
                        .map(|d| d.as_secs()),
                });
            }
        }
    }
    list.sort_by_key(|m| m.name.to_lowercase());
    list
}

/// Moves a loose mod's files (<name>.dll and its .pdb/.ini) between
/// System/mods and System/mods/disabled: the SDK only loads DLLs directly in
/// System/mods.
pub fn set_loose_enabled(layout: &Layout, name: &str, enabled: bool) -> Result<(), String> {
    if name.is_empty() || name.contains(['/', '\\', ':']) || name.starts_with('.') {
        return Err(format!("invalid mod name {name:?}"));
    }
    let (from, to) =
        if enabled { (layout.disabled(), layout.dir.clone()) } else { (layout.dir.clone(), layout.disabled()) };
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

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn api_version_matches_the_sdk_header() {
        let root = Path::new(env!("CARGO_MANIFEST_DIR")).join("../..");
        assert_eq!(header_api_version(&root), Some(SDK_API_VERSION));
    }

    #[test]
    fn loose_toggle_moves_the_files() {
        let game = tempfile::tempdir().unwrap();
        let layout = Layout::new(game.path());
        std::fs::create_dir_all(&layout.dir).unwrap();
        std::fs::write(layout.dir.join("hello.dll"), b"MZ").unwrap();
        std::fs::write(layout.dir.join("hello.ini"), b"").unwrap();
        set_loose_enabled(&layout, "hello", false).unwrap();
        assert!(layout.disabled().join("hello.dll").is_file() && layout.disabled().join("hello.ini").is_file());
        let list = loose(&layout);
        assert_eq!((list.len(), list[0].enabled), (1, false));
        set_loose_enabled(&layout, "hello", true).unwrap();
        assert!(layout.dir.join("hello.dll").is_file());
        assert!(set_loose_enabled(&layout, "../x", true).is_err());
        assert!(set_loose_enabled(&layout, "missing", true).is_err());
    }
}
