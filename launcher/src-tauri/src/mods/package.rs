// .t3mod packages (docs/mods.md, "The package"): every entry path and the
// manifest are checked before anything is written; the package is extracted
// into a hidden folder in System/mods/ and then renamed into place, replacing
// an installed version as a whole.
use std::collections::HashSet;
use std::fs::File;
use std::io::Read;
use std::path::Path;

use semver::Version;
use serde::Serialize;
use zip::{CompressionMethod, ZipArchive};

use super::files;
use super::layout::{self, Layout};
use super::manifest::{self, Manifest};
use super::overlay::under_system;

/// Limits against zip bombs and broken archives.
const MAX_ENTRIES: usize = 200_000;
const MAX_BYTES: u64 = 16 << 30;
const MAX_MANIFEST: u64 = 1 << 20;

#[derive(Clone, Debug, Serialize)]
#[serde(rename_all = "camelCase")]
pub struct Installed {
    pub id: String,
    pub name: String,
    pub version: Version,
    /// The version it replaced (an upgrade or a downgrade).
    pub previous: Option<Version>,
}

fn file_name(path: &Path) -> String {
    path.file_name().map_or_else(|| path.display().to_string(), |n| n.to_string_lossy().into_owned())
}

/// Opens a package and checks it without extracting anything.
pub fn inspect(path: &Path) -> Result<(ZipArchive<File>, Manifest), String> {
    let label = file_name(path);
    let file = File::open(path).map_err(|e| format!("cannot open {label}: {e}"))?;
    let mut zip = ZipArchive::new(file).map_err(|e| format!("{label} is not a mod package (zip): {e}"))?;
    if zip.len() > MAX_ENTRIES {
        return Err(format!("{label} has more than {MAX_ENTRIES} files"));
    }
    let refuse = |why: String| Err(format!("{label} was refused: {why}"));

    let mut names = HashSet::new();
    let mut folders = HashSet::new();
    let mut manifest_at = None;
    let mut root_files = Vec::new();
    let (mut has_files, mut has_textures) = (false, false);
    let mut total = 0u64;
    for i in 0..zip.len() {
        let entry = zip.by_index_raw(i).map_err(|e| format!("{label}: {e}"))?;
        let name = entry.name().to_string();
        let dir = entry.is_dir();
        let rel = if dir { name.trim_end_matches('/') } else { name.as_str() };
        if let Err(e) = files::check_rel(rel) {
            return refuse(e);
        }
        if entry.enclosed_name().is_none() {
            return refuse(format!("{name}: unsafe path"));
        }
        if entry.is_symlink() {
            return refuse(format!("{name} is a symbolic link"));
        }
        if entry.encrypted() {
            return refuse(format!("{name} is encrypted"));
        }
        // Directory entries are allowed and ignored: folders come from the files' paths.
        if dir {
            continue;
        }
        if !matches!(entry.compression(), CompressionMethod::Stored | CompressionMethod::Deflated) {
            return refuse(format!("{name}: compression method {}; use deflate (or store)", entry.compression()));
        }
        let lower = rel.to_lowercase();
        if let Some(inside) = lower.strip_prefix("files/") {
            if under_system(inside) {
                return refuse(format!("{name}: files/ may not contain System/ (a mod's code goes in \"entry\")"));
            }
            has_files = true;
        }
        if let Some(texture) = lower.strip_prefix("textures/") {
            if texture.contains('/') {
                return refuse(format!("{name}: textures/ holds <texture name>.dds files, no folders"));
            }
            if !texture.ends_with(".dds") {
                return refuse(format!("{name}: textures/ holds only .dds files"));
            }
            has_textures = true;
        }
        if !names.insert(lower.clone()) {
            return refuse(format!("{name} is in the package twice (names are compared ignoring case)"));
        }
        let mut parent = lower.as_str();
        while let Some((up, _)) = parent.rsplit_once('/') {
            folders.insert(up.to_string());
            parent = up;
        }
        total += entry.size();
        if total > MAX_BYTES {
            return refuse("it unpacks to more than 16 GB".into());
        }
        if lower == "mod.json" {
            manifest_at = Some(i);
        }
        if !lower.contains('/') {
            root_files.push(lower);
        }
    }
    if let Some(clash) = names.iter().find(|n| folders.contains(*n)) {
        return refuse(format!("{clash} is both a file and a folder"));
    }

    let index = manifest_at.ok_or_else(|| format!("{label} has no mod.json at its root: it is not a mod package"))?;
    let mut entry = zip.by_index(index).map_err(|e| format!("{label}: mod.json: {e}"))?;
    let mut bytes = Vec::new();
    (&mut entry).take(MAX_MANIFEST + 1).read_to_end(&mut bytes).map_err(|e| format!("{label}: mod.json: {e}"))?;
    drop(entry);
    if bytes.len() as u64 > MAX_MANIFEST {
        return refuse("mod.json is larger than 1 MB".into());
    }
    let text = String::from_utf8(bytes).map_err(|_| format!("{label}: mod.json is not UTF-8"))?;
    let m = manifest::parse(&text).map_err(|e| format!("{label}: mod.json: {}", manifest::describe(&e)))?;

    let entry_found = m.entry.as_ref().map(|e| root_files.contains(&e.to_lowercase()));
    if entry_found == Some(false) {
        return refuse(format!(
            "mod.json names {} as its DLL, but the package has no such file at its root",
            m.entry.as_deref().unwrap_or_default()
        ));
    }
    if entry_found.is_none() && !has_files && !has_textures {
        return refuse("it has no DLL (\"entry\"), files/ or textures/, so there is nothing to install".into());
    }
    Ok((zip, m))
}

fn extract(zip: &mut ZipArchive<File>, dest: &Path) -> Result<(), String> {
    std::fs::create_dir_all(dest).map_err(|e| format!("cannot create {}: {e}", dest.display()))?;
    for i in 0..zip.len() {
        let mut entry = zip.by_index(i).map_err(|e| e.to_string())?;
        if entry.is_dir() {
            continue;
        }
        let name = entry.name().to_string();
        let out = files::join_rel(dest, &name);
        if let Some(parent) = out.parent() {
            std::fs::create_dir_all(parent).map_err(|e| format!("cannot create {}: {e}", parent.display()))?;
        }
        let mut file = std::fs::OpenOptions::new()
            .write(true)
            .create_new(true)
            .open(&out)
            .map_err(|e| format!("cannot write {}: {e}", out.display()))?;
        let size = entry.size();
        // Reading to the end checks the CRC; one byte more than declared catches a lying header.
        let copied = std::io::copy(&mut (&mut entry).take(size + 1), &mut file).map_err(|e| format!("{name}: {e}"))?;
        if copied != size {
            return Err(format!("{name}: {copied} bytes instead of {size}"));
        }
    }
    Ok(())
}

/// Installs a package into System/mods/<id>/, replacing an installed version.
/// With `expect`, the package must be that id and version (index downloads).
pub fn install(layout: &Layout, package: &Path, expect: Option<(&str, &Version)>) -> Result<Installed, String> {
    let (mut zip, m) = inspect(package)?;
    if let Some((id, version)) = expect {
        if m.id != id || m.version != *version {
            return Err(format!(
                "the download is {} {}, not {id} {version} as the index says: refused",
                m.id, m.version
            ));
        }
    }
    let target = layout.package(&m.id);
    let previous = if target.exists() {
        match layout::read_manifest(&target) {
            Ok(old) => Some(old.version),
            Err(_) if layout::find_ci(&target, "mod.json").is_some() => None,
            Err(_) => {
                return Err(format!("{} exists but is not a mod package; move it away first", target.display()));
            }
        }
    } else {
        None
    };

    std::fs::create_dir_all(&layout.dir).map_err(|e| format!("cannot create {}: {e}", layout.dir.display()))?;
    let staging = files::temp_sibling(&target, "install");
    if let Err(e) = extract(&mut zip, &staging) {
        let _ = std::fs::remove_dir_all(&staging);
        return Err(e);
    }
    if target.exists() {
        let old = files::temp_sibling(&target, "old");
        if let Err(e) = std::fs::rename(&target, &old) {
            let _ = std::fs::remove_dir_all(&staging);
            return Err(format!("cannot replace {}: {e} (is the game running?)", target.display()));
        }
        if let Err(e) = std::fs::rename(&staging, &target) {
            let _ = std::fs::rename(&old, &target);
            let _ = std::fs::remove_dir_all(&staging);
            return Err(format!("cannot install into {}: {e}", target.display()));
        }
        let _ = std::fs::remove_dir_all(&old);
    } else if let Err(e) = std::fs::rename(&staging, &target) {
        let _ = std::fs::remove_dir_all(&staging);
        return Err(format!("cannot install into {}: {e}", target.display()));
    }
    Ok(Installed { id: m.id, name: m.name, version: m.version, previous })
}

/// Removes what an interrupted install or removal left behind (older than an
/// hour, so another launcher's work in progress is left alone).
pub fn clean_leftovers(layout: &Layout) {
    let Ok(entries) = std::fs::read_dir(&layout.dir) else { return };
    let hour_ago = std::time::SystemTime::now() - std::time::Duration::from_secs(3600);
    for e in entries.flatten() {
        let name = e.file_name().to_string_lossy().into_owned();
        let ours = [".install-", ".old-", ".remove-", ".download-", ".tmp-"].iter().any(|tag| name.contains(tag));
        let stale = e.metadata().and_then(|m| m.modified()).is_ok_and(|t| t < hour_ago);
        if name.starts_with('.') && ours && stale {
            let path = e.path();
            let _ = if path.is_dir() { std::fs::remove_dir_all(&path) } else { std::fs::remove_file(&path) };
        }
    }
}
