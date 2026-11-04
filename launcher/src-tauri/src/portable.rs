// Updates of the portable launcher, a folder unzipped from the portable zip.
// The updater plugin only runs installers, which would install a second copy
// beside this one, so the portable copy updates itself: the release's
// latest.json names the portable zip under PLATFORM (the plugin never reads
// that entry), signed with the same key as the installer and bound to its
// version. The zip is downloaded, checked, unpacked into <folder>/.update/new,
// and swapped in: each of its entries (the launcher, t3sdk/, python/) moves
// the old one to <folder>/.update/old (Windows lets a running executable be
// moved within its volume) and takes its place. A failed swap is undone. The
// next start removes .update/. See docs/releasing.md.
use std::fs;
use std::io::{Cursor, Read};
use std::path::{Path, PathBuf};

use base64::Engine;
use minisign_verify::{PublicKey, Signature};
use serde_json::Value;

/// The latest.json entry of the portable zip.
pub const PLATFORM: &str = "windows-x86_64-portable";

/// The launcher's executable as the portable zip names it.
const ZIP_EXE: &str = "t3sdk-launcher.exe";

/// The work folder inside the launcher's folder.
const WORK: &str = ".update";

/// Larger downloads are refused (the zip is about 40 MB).
const MAX_SIZE: u64 = 1 << 30;

#[derive(Clone, Debug, PartialEq)]
pub struct Package {
    pub url: String,
    pub signature: String,
}

/// The portable zip that latest.json offers, if it offers one.
pub fn package(manifest: &Value) -> Option<Package> {
    let entry = manifest.get("platforms")?.get(PLATFORM)?;
    let text = |key: &str| entry.get(key)?.as_str().map(str::to_string).filter(|s| !s.trim().is_empty());
    Some(Package { url: text("url")?, signature: text("signature")? })
}

/// Checks `data` against `signature` (latest.json's base64 of a minisign signature) and the
/// updater's public key (base64 of a minisign public key), and that it was signed for `version`.
pub fn verify(data: &[u8], signature: &str, pubkey: &str, version: &str) -> Result<(), String> {
    let decode = |text: &str, what: &str| {
        base64::engine::general_purpose::STANDARD
            .decode(text.trim())
            .ok()
            .and_then(|bytes| String::from_utf8(bytes).ok())
            .ok_or(format!("the update's {what} is not readable"))
    };
    let key = PublicKey::decode(&decode(pubkey, "public key")?).map_err(|e| format!("bad update key: {e}"))?;
    let signature =
        Signature::decode(&decode(signature, "signature")?).map_err(|e| format!("bad update signature: {e}"))?;
    key.verify(data, &signature, false).map_err(|e| format!("the download does not match its signature: {e}"))?;
    // The trusted comment is covered by the signature, so it can be believed only now.
    let signed = format!("version:{version}");
    if !signature.trusted_comment().split('\t').any(|field| field.trim() == signed) {
        return Err(format!("the download was not signed for version {version}: refused"));
    }
    Ok(())
}

/// Downloads `url`, reporting (received, total) as it goes.
pub fn download(url: &str, mut progress: impl FnMut(u64, Option<u64>)) -> Result<Vec<u8>, String> {
    let mut response = crate::net::agent().get(url).call().map_err(|e| format!("cannot download {url}: {e}"))?;
    let total = response.body().content_length();
    if total.is_some_and(|t| t > MAX_SIZE) {
        return Err(format!("{url} is too large: refused"));
    }
    let mut reader = response.body_mut().with_config().limit(MAX_SIZE).reader();
    let mut data = Vec::with_capacity(total.unwrap_or(0) as usize);
    let mut buf = vec![0u8; 256 * 1024];
    loop {
        let n = reader.read(&mut buf).map_err(|e| format!("the download of {url} failed: {e}"))?;
        if n == 0 {
            break;
        }
        data.extend_from_slice(&buf[..n]);
        progress(data.len() as u64, total);
    }
    if total.is_some_and(|t| t != data.len() as u64) {
        return Err(format!("the download of {url} was cut short"));
    }
    Ok(data)
}

/// Unpacks the zip into `dest`, which must hold the launcher afterwards.
fn unpack(data: &[u8], dest: &Path) -> Result<(), String> {
    let mut zip = zip::ZipArchive::new(Cursor::new(data)).map_err(|e| format!("the update is not a zip: {e}"))?;
    zip.extract(dest).map_err(|e| format!("cannot unpack the update into {}: {e}", dest.display()))?;
    if !dest.join(ZIP_EXE).is_file() {
        return Err("the update has no launcher in it: refused".into());
    }
    Ok(())
}

/// One swapped entry: where it went, where its staged copy came from, and where the old one is.
struct Swapped {
    target: PathBuf,
    staged: PathBuf,
    old: Option<PathBuf>,
}

/// Puts back what `done` replaced, newest first.
fn undo(done: &[Swapped]) {
    for s in done.iter().rev() {
        let _ = fs::rename(&s.target, &s.staged);
        if let Some(old) = &s.old {
            let _ = fs::rename(old, &s.target);
        }
    }
}

/// Moves each entry of `staged` into `dir` (the launcher's executable to `exe`, its current name),
/// moving what it replaces into `old_dir`. All or nothing: a failure puts everything back.
fn swap(dir: &Path, staged: &Path, old_dir: &Path, exe: &str) -> Result<(), String> {
    fs::create_dir_all(old_dir).map_err(|e| format!("cannot create {}: {e}", old_dir.display()))?;
    let mut entries: Vec<PathBuf> = fs::read_dir(staged)
        .map_err(|e| format!("cannot read {}: {e}", staged.display()))?
        .flatten()
        .map(|e| e.path())
        .collect();
    // The folders first and the launcher last: a folder in use fails before anything that matters moved.
    entries.sort_by_key(|p| (p.file_name().is_some_and(|n| n.eq_ignore_ascii_case(ZIP_EXE)), p.clone()));

    let mut done = Vec::new();
    for source in entries {
        let Some(name) = source.file_name().map(|n| n.to_os_string()) else { continue };
        let target = if name.eq_ignore_ascii_case(ZIP_EXE) { dir.join(exe) } else { dir.join(&name) };
        let shown = target.file_name().unwrap_or_default().to_string_lossy().into_owned();
        let in_use = |e: std::io::Error| {
            format!("cannot replace {shown}: close anything that uses the launcher's folder and try again ({e})")
        };

        let old = if fs::symlink_metadata(&target).is_ok() {
            let old = old_dir.join(&name);
            if let Err(e) = fs::rename(&target, &old) {
                undo(&done);
                return Err(in_use(e));
            }
            Some(old)
        } else {
            None
        };
        if let Err(e) = fs::rename(&source, &target) {
            if let Some(old) = &old {
                let _ = fs::rename(old, &target);
            }
            undo(&done);
            return Err(in_use(e));
        }
        done.push(Swapped { target, staged: source, old });
    }
    Ok(())
}

/// Installs the downloaded, checked zip into `dir`, where the running launcher is `exe`.
pub fn install(dir: &Path, exe: &str, data: &[u8]) -> Result<(), String> {
    let work = dir.join(WORK);
    if work.exists() {
        fs::remove_dir_all(&work).map_err(|e| format!("cannot clear {}: {e}", work.display()))?;
    }
    let staged = work.join("new");
    fs::create_dir_all(&staged).map_err(|e| {
        format!("cannot write to {} ({e}): download the new version from the releases page", dir.display())
    })?;
    unpack(data, &staged)?;
    swap(dir, &staged, &work.join("old"), exe)
}

/// Removes what the last update left in `dir` (the old launcher, which may still be closing).
pub fn cleanup(dir: &Path) {
    let work = dir.join(WORK);
    for _ in 0..20 {
        if !work.exists() || fs::remove_dir_all(&work).is_ok() {
            return;
        }
        std::thread::sleep(std::time::Duration::from_millis(500));
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use std::io::Write;

    // A throwaway key made with `tauri signer generate` (no password) for these tests, and a
    // signature of DATA made with `tauri signer sign --app-version 9.9.9`.
    const PUBKEY: &str = include_str!("../tests/portable/key.pub");
    const SIGNATURE: &str = include_str!("../tests/portable/data.txt.sig");
    const DATA: &[u8] = include_bytes!("../tests/portable/data.txt");

    #[test]
    fn reads_the_portable_entry() {
        let manifest: Value = serde_json::json!({
            "version": "1.0.0",
            "platforms": {
                "windows-x86_64": {"url": "https://x/setup.exe", "signature": "a"},
                PLATFORM: {"url": "https://x/portable.zip", "signature": "b"},
            }
        });
        assert_eq!(package(&manifest), Some(Package { url: "https://x/portable.zip".into(), signature: "b".into() }));
        let older = serde_json::json!({"platforms": {"windows-x86_64": {"url": "u", "signature": "s"}}});
        assert_eq!(package(&older), None);
    }

    #[test]
    fn checks_the_signature_and_its_version() {
        verify(DATA, SIGNATURE, PUBKEY, "9.9.9").unwrap();
        assert!(verify(DATA, SIGNATURE, PUBKEY, "9.9.8").unwrap_err().contains("not signed for version"));
        assert!(verify(b"something else", SIGNATURE, PUBKEY, "9.9.9").unwrap_err().contains("does not match"));
    }

    fn zip_of(files: &[(&str, &str)]) -> Vec<u8> {
        let mut out = Cursor::new(Vec::new());
        {
            let mut zip = zip::ZipWriter::new(&mut out);
            for (name, text) in files {
                zip.start_file(*name, zip::write::SimpleFileOptions::default()).unwrap();
                zip.write_all(text.as_bytes()).unwrap();
            }
            zip.finish().unwrap();
        }
        out.into_inner()
    }

    fn read(path: &Path) -> String {
        fs::read_to_string(path).unwrap()
    }

    #[test]
    fn swaps_the_folder_in_place() {
        let tmp = tempfile::tempdir().unwrap();
        let dir = tmp.path();
        fs::write(dir.join("Launcher.exe"), "old exe").unwrap();
        fs::create_dir_all(dir.join("t3sdk")).unwrap();
        fs::write(dir.join("t3sdk").join("gone.txt"), "old").unwrap();
        fs::write(dir.join("notes.txt"), "the player's").unwrap();

        let data = zip_of(&[(ZIP_EXE, "new exe"), ("t3sdk/tools/sdk.py", "new"), ("python/python.exe", "new python")]);
        install(dir, "Launcher.exe", &data).unwrap();

        assert_eq!(read(&dir.join("Launcher.exe")), "new exe", "the running launcher's own name is kept");
        assert!(!dir.join(ZIP_EXE).exists());
        assert_eq!(read(&dir.join("t3sdk").join("tools").join("sdk.py")), "new");
        assert!(!dir.join("t3sdk").join("gone.txt").exists(), "the old folder is replaced, not merged");
        assert_eq!(read(&dir.join("python").join("python.exe")), "new python");
        assert_eq!(read(&dir.join("notes.txt")), "the player's");

        cleanup(dir);
        assert!(!dir.join(WORK).exists());
    }

    #[test]
    fn undoes_a_failed_swap() {
        let tmp = tempfile::tempdir().unwrap();
        let dir = tmp.path();
        fs::write(dir.join("Launcher.exe"), "old exe").unwrap();
        fs::create_dir_all(dir.join("t3sdk")).unwrap();
        fs::write(dir.join("t3sdk").join("sdk.py"), "old").unwrap();

        let staged = dir.join(WORK).join("new");
        fs::create_dir_all(staged.join("t3sdk")).unwrap();
        fs::write(staged.join("t3sdk").join("sdk.py"), "new").unwrap();
        fs::write(staged.join(ZIP_EXE), "new exe").unwrap();
        // The old launcher's place in .update/old is taken by a folder, so moving it there fails
        // after t3sdk/ was already swapped.
        fs::create_dir_all(dir.join(WORK).join("old").join(ZIP_EXE).join("x")).unwrap();
        let err = swap(dir, &staged, &dir.join(WORK).join("old"), "Launcher.exe").unwrap_err();
        assert!(err.contains("cannot replace Launcher.exe"), "{err}");
        assert_eq!(read(&dir.join("t3sdk").join("sdk.py")), "old");
        assert_eq!(read(&dir.join("Launcher.exe")), "old exe");
        assert_eq!(read(&staged.join("t3sdk").join("sdk.py")), "new", "the new copy went back to staging");
    }

    #[test]
    fn refuses_a_zip_without_the_launcher() {
        let tmp = tempfile::tempdir().unwrap();
        fs::write(tmp.path().join("Launcher.exe"), "old exe").unwrap();
        let err = install(tmp.path(), "Launcher.exe", &zip_of(&[("t3sdk/x", "y")])).unwrap_err();
        assert!(err.contains("no launcher"), "{err}");
        assert_eq!(read(&tmp.path().join("Launcher.exe")), "old exe");
    }
}
