// File helpers for the mod manager: atomic writes, SHA-256 (with a cache, so
// a sync does not rehash unchanged files), folder walks and safe relative
// paths.
use std::collections::HashMap;
use std::io::{Read, Write};
use std::path::{Path, PathBuf};
use std::sync::atomic::{AtomicU32, Ordering};
use std::sync::Mutex;
use std::time::SystemTime;

use sha2::{Digest, Sha256};

/// A name next to `path` for a temporary file or folder: hidden, unique within
/// this process, and on the same volume, so a rename finishes the job.
pub fn temp_sibling(path: &Path, tag: &str) -> PathBuf {
    static NEXT: AtomicU32 = AtomicU32::new(0);
    let n = NEXT.fetch_add(1, Ordering::Relaxed);
    let name = path.file_name().map(|n| n.to_string_lossy().into_owned()).unwrap_or_default();
    path.with_file_name(format!(".{name}.{tag}-{}-{n}", std::process::id()))
}

/// Writes a whole file so that readers see the old or the new content, never
/// half of it: a temporary file next to it, flushed, then renamed over it.
pub fn atomic_write(path: &Path, data: &[u8]) -> Result<(), String> {
    if let Some(dir) = path.parent() {
        std::fs::create_dir_all(dir).map_err(|e| format!("cannot create {}: {e}", dir.display()))?;
    }
    let tmp = temp_sibling(path, "tmp");
    let written = (|| {
        let mut file = std::fs::File::create(&tmp)?;
        file.write_all(data)?;
        file.sync_all()
    })();
    let result = written.and_then(|()| std::fs::rename(&tmp, path));
    if let Err(e) = result {
        let _ = std::fs::remove_file(&tmp);
        return Err(format!("cannot write {}: {e}", path.display()));
    }
    Ok(())
}

/// Replaces `dst` with a copy of `src` the same way: copy next to it, rename.
pub fn copy_over(src: &Path, dst: &Path) -> std::io::Result<()> {
    if let Some(dir) = dst.parent() {
        std::fs::create_dir_all(dir)?;
    }
    let tmp = temp_sibling(dst, "tmp");
    let result = std::fs::copy(src, &tmp).and_then(|_| std::fs::rename(&tmp, dst));
    if result.is_err() {
        let _ = std::fs::remove_file(&tmp);
    }
    result
}

/// Moves a file, creating the destination's folder; replaces an existing file.
pub fn move_file(src: &Path, dst: &Path) -> std::io::Result<()> {
    if let Some(dir) = dst.parent() {
        std::fs::create_dir_all(dir)?;
    }
    std::fs::rename(src, dst)
}

pub fn hex(bytes: &[u8]) -> String {
    bytes.iter().map(|b| format!("{b:02x}")).collect()
}

pub fn sha256_reader(mut reader: impl Read) -> std::io::Result<String> {
    let mut hasher = Sha256::new();
    let mut buf = vec![0u8; 256 * 1024];
    loop {
        let n = reader.read(&mut buf)?;
        if n == 0 {
            break;
        }
        hasher.update(&buf[..n]);
    }
    Ok(hex(&hasher.finalize()))
}

pub fn sha256_file(path: &Path) -> std::io::Result<String> {
    sha256_reader(std::fs::File::open(path)?)
}

/// SHA-256 of files, remembered by path, size and modification time.
#[derive(Default)]
pub struct HashCache(Mutex<HashMap<PathBuf, (u64, SystemTime, String)>>);

impl HashCache {
    /// The file's hash, or None when it does not exist (or is not a file).
    pub fn sha256(&self, path: &Path) -> std::io::Result<Option<String>> {
        let meta = match std::fs::metadata(path) {
            Ok(m) if m.is_file() => m,
            Ok(_) => return Ok(None),
            Err(e) if e.kind() == std::io::ErrorKind::NotFound => return Ok(None),
            Err(e) => return Err(e),
        };
        let stamp = (meta.len(), meta.modified().unwrap_or(SystemTime::UNIX_EPOCH));
        if let Some((len, time, hash)) = self.0.lock().unwrap().get(path) {
            if (*len, *time) == stamp {
                return Ok(Some(hash.clone()));
            }
        }
        let hash = sha256_file(path)?;
        self.0.lock().unwrap().insert(path.to_path_buf(), (stamp.0, stamp.1, hash.clone()));
        Ok(Some(hash))
    }

    /// Drops what is known about `path`, after writing or moving it.
    pub fn forget(&self, path: &Path) {
        self.0.lock().unwrap().remove(path);
    }
}

/// A file under a folder: its path relative to the folder with `/`
/// separators, where it is, and its size.
#[derive(Clone, Debug)]
pub struct FileRef {
    pub rel: String,
    pub path: PathBuf,
    pub size: u64,
}

/// Every regular file under `root`, sorted by relative path. Symbolic links
/// are skipped: a package never needs them and they could point anywhere.
pub fn walk(root: &Path) -> Vec<FileRef> {
    fn visit(dir: &Path, prefix: &str, out: &mut Vec<FileRef>) {
        let Ok(entries) = std::fs::read_dir(dir) else { return };
        for e in entries.flatten() {
            let Ok(kind) = e.file_type() else { continue };
            let name = e.file_name().to_string_lossy().into_owned();
            let rel = if prefix.is_empty() { name } else { format!("{prefix}/{name}") };
            if kind.is_dir() {
                visit(&e.path(), &rel, out);
            } else if kind.is_file() {
                let size = e.metadata().map_or(0, |m| m.len());
                out.push(FileRef { rel, path: e.path(), size });
            }
        }
    }
    let mut out = Vec::new();
    visit(root, "", &mut out);
    out.sort_by(|a, b| a.rel.cmp(&b.rel));
    out
}

/// Total size of the files under `root`.
pub fn tree_size(root: &Path) -> u64 {
    walk(root).iter().map(|f| f.size).sum()
}

/// Checks a relative path as packages and overlay records use it: `/`
/// separators, no empty, `.` or `..` segments, no drive letters or other
/// colons, and nothing Windows cannot store as a file name (reserved device
/// names, trailing dots or spaces, `<>"|?*`, control characters).
pub fn check_rel(path: &str) -> Result<(), String> {
    if path.is_empty() {
        return Err("empty path".into());
    }
    if path.contains('\\') {
        return Err(format!("{path}: uses \\ instead of /"));
    }
    if path.starts_with('/') {
        return Err(format!("{path}: absolute path"));
    }
    for segment in path.split('/') {
        let bad = |why: &str| Err(format!("{path}: {why}"));
        match segment {
            "" => return bad("empty path segment"),
            "." | ".." => return bad("contains . or .."),
            _ => {}
        }
        if segment.contains(':') {
            return bad("drive letter or colon");
        }
        if segment.chars().any(|c| c.is_control() || "<>\"|?*".contains(c)) {
            return bad("character not allowed in Windows file names");
        }
        if segment.ends_with(['.', ' ']) {
            return bad("name ends with a dot or space");
        }
        let stem = segment.split('.').next().unwrap_or_default().trim_end().to_ascii_uppercase();
        let reserved = matches!(stem.as_str(), "CON" | "PRN" | "AUX" | "NUL")
            || (stem.len() == 4
                && (stem.starts_with("COM") || stem.starts_with("LPT"))
                && stem.as_bytes()[3].is_ascii_digit());
        if reserved {
            return bad("reserved Windows device name");
        }
    }
    Ok(())
}

/// `rel` (checked with `check_rel`) joined onto `root`.
pub fn join_rel(root: &Path, rel: &str) -> PathBuf {
    rel.split('/').fold(root.to_path_buf(), |p, s| p.join(s))
}

/// Removes empty folders from `dir` upwards, stopping at `stop`.
pub fn prune_empty(dir: &Path, stop: &Path) {
    let mut current = Some(dir);
    while let Some(d) = current {
        if d == stop || !d.starts_with(stop) || std::fs::remove_dir(d).is_err() {
            break;
        }
        current = d.parent();
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn relative_paths() {
        for ok in ["mod.json", "files/Content/T3/Bitmaps/x.dds", "textures/a b.dds", "x.tar.gz"] {
            assert!(check_rel(ok).is_ok(), "{ok}");
        }
        for bad in [
            "",
            "/etc/passwd",
            "../x",
            "files/../../x",
            "files/./x",
            "a//b",
            "C:/Windows/x",
            "C:x",
            "a\\b",
            "file.txt:stream",
            "files/NUL",
            "files/com1.txt",
            "files/x.",
            "files/x ",
            "files/a?b",
        ] {
            assert!(check_rel(bad).is_err(), "{bad}");
        }
        assert!(check_rel("files/COM10").is_ok());
    }

    #[test]
    fn atomic_write_replaces() {
        let dir = tempfile::tempdir().unwrap();
        let path = dir.path().join("sub").join("a.txt");
        atomic_write(&path, b"one").unwrap();
        atomic_write(&path, b"two").unwrap();
        assert_eq!(std::fs::read(&path).unwrap(), b"two");
        assert_eq!(std::fs::read_dir(path.parent().unwrap()).unwrap().count(), 1, "no temporary files left");
    }

    #[test]
    fn hashes() {
        let dir = tempfile::tempdir().unwrap();
        let path = dir.path().join("a");
        std::fs::write(&path, b"abc").unwrap();
        let cache = HashCache::default();
        let expected = "ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad";
        assert_eq!(cache.sha256(&path).unwrap().as_deref(), Some(expected));
        assert_eq!(cache.sha256(&dir.path().join("missing")).unwrap(), None);
    }
}
