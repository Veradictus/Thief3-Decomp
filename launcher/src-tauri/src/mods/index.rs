// The mod index (docs/mods.md, "The mod index"): fetched over HTTPS, read
// leniently (an entry the launcher cannot use is skipped, not fatal), and
// compared with what is installed: what each version needs, and which
// installed mods have a newer compatible version. Downloads are checked
// against the index's size and SHA-256 before the package is opened.
use std::collections::{BTreeMap, HashSet};
use std::io::{Read, Write};
use std::path::Path;
use std::time::Duration;

use semver::Version;
use serde::Serialize;
use serde_json::Value;
use sha2::{Digest, Sha256};

use super::checks::Severity;
use super::layout::{Package, SdkInfo};
use super::manifest::{valid_https, valid_id};
use super::version::{self, Range};

pub const DEFAULT_URL: &str = "https://veradictus.github.io/Thief3-Decomp/modindex/index.json";

#[derive(Clone, Debug, Serialize)]
#[serde(rename_all = "camelCase")]
pub struct IndexVersion {
    pub version: Version,
    pub url: String,
    #[serde(skip)]
    pub sha256: String,
    pub size: u64,
    pub released: Option<String>,
    pub api: Option<u32>,
    pub requires: BTreeMap<String, String>,
    pub conflicts: Vec<String>,
}

#[derive(Clone, Debug, Serialize)]
#[serde(rename_all = "camelCase")]
pub struct IndexMod {
    pub id: String,
    pub name: String,
    pub description: Option<String>,
    pub authors: Vec<String>,
    pub homepage: Option<String>,
    pub license: Option<String>,
    pub tags: Vec<String>,
    /// Newest first.
    pub versions: Vec<IndexVersion>,
}

#[derive(Clone, Debug)]
pub struct Index {
    pub generated: Option<String>,
    pub mods: Vec<IndexMod>,
    /// Entries (mods or versions) that were left out as invalid.
    pub skipped: usize,
}

impl Index {
    pub fn find(&self, id: &str) -> Option<&IndexMod> {
        self.mods.iter().find(|m| m.id == id)
    }
}

fn string_at(v: &Value, key: &str) -> Option<String> {
    v.get(key).and_then(Value::as_str).map(str::to_string)
}

fn strings(v: &Value, key: &str) -> Vec<String> {
    v.get(key)
        .and_then(Value::as_array)
        .map(|a| a.iter().filter_map(|s| s.as_str().map(str::to_string)).collect())
        .unwrap_or_default()
}

fn read_version(v: &Value) -> Option<IndexVersion> {
    let version = Version::parse(v.get("version")?.as_str()?).ok()?;
    let url = string_at(v, "url").filter(|u| valid_https(u))?;
    let sha256 =
        string_at(v, "sha256").filter(|h| h.len() == 64 && h.bytes().all(|b| b.is_ascii_hexdigit()))?.to_lowercase();
    let size = v.get("size")?.as_u64().filter(|s| *s > 0)?;
    let api = match v.get("api") {
        None | Some(Value::Null) => None,
        Some(a) => Some(u32::try_from(a.as_u64().filter(|n| *n >= 1)?).ok()?),
    };
    let mut requires = BTreeMap::new();
    if let Some(map) = v.get("requires").and_then(Value::as_object) {
        for (id, range) in map {
            let range = range.as_str()?;
            if !valid_id(id) || Range::parse(range).is_err() {
                return None;
            }
            requires.insert(id.clone(), range.to_string());
        }
    }
    let conflicts = strings(v, "conflicts");
    if !conflicts.iter().all(|c| valid_id(c)) {
        return None;
    }
    Some(IndexVersion { version, url, sha256, size, released: string_at(v, "released"), api, requires, conflicts })
}

pub fn parse(text: &str) -> Result<Index, String> {
    let doc: Value = serde_json::from_str(text).map_err(|e| format!("the mod index is not valid JSON: {e}"))?;
    match doc.get("format").and_then(Value::as_u64) {
        Some(1) => {}
        Some(n) if n > 1 => {
            return Err(format!("the mod index is format {n}; this launcher reads format 1: update it"))
        }
        _ => return Err("the mod index has no \"format\": 1".into()),
    }
    let mut skipped = 0;
    let mut mods = Vec::new();
    let mut seen = HashSet::new();
    for m in doc.get("mods").and_then(Value::as_array).into_iter().flatten() {
        let id = string_at(m, "id").filter(|id| valid_id(id));
        let name = string_at(m, "name").filter(|n| !n.trim().is_empty());
        let (Some(id), Some(name)) = (id, name) else {
            skipped += 1;
            continue;
        };
        if !seen.insert(id.clone()) {
            skipped += 1;
            continue;
        }
        let all = m.get("versions").and_then(Value::as_array).cloned().unwrap_or_default();
        let mut versions: Vec<IndexVersion> = all.iter().filter_map(read_version).collect();
        skipped += all.len() - versions.len();
        versions.sort_by(|a, b| b.version.cmp(&a.version));
        versions.dedup_by(|a, b| a.version == b.version);
        if versions.is_empty() {
            skipped += 1;
            continue;
        }
        mods.push(IndexMod {
            id,
            name,
            description: string_at(m, "description"),
            authors: strings(m, "authors"),
            homepage: string_at(m, "homepage").filter(|h| valid_https(h)),
            license: string_at(m, "license"),
            tags: strings(m, "tags"),
            versions,
        });
    }
    mods.sort_by_key(|m| m.name.to_lowercase());
    Ok(Index { generated: string_at(&doc, "generated"), mods, skipped })
}

// ---- compared with what is installed -------------------------------------------

#[derive(Clone, Debug, Serialize)]
#[serde(rename_all = "camelCase")]
pub struct Note {
    pub severity: Severity,
    pub message: String,
}

#[derive(Clone, Debug, Serialize)]
#[serde(rename_all = "camelCase")]
pub struct VersionView {
    #[serde(flatten)]
    pub version: IndexVersion,
    /// No errors: it can be installed and loaded next to the enabled mods.
    pub compatible: bool,
    pub notes: Vec<Note>,
}

#[derive(Clone, Debug, Serialize)]
#[serde(rename_all = "camelCase")]
pub struct ModView {
    pub id: String,
    pub name: String,
    pub description: Option<String>,
    pub authors: Vec<String>,
    pub homepage: Option<String>,
    pub license: Option<String>,
    pub tags: Vec<String>,
    /// The installed version, if any.
    pub installed: Option<Version>,
    pub enabled: bool,
    pub versions: Vec<VersionView>,
    /// What an Install or Update button installs: the newest compatible
    /// release (pre-releases only when nothing else fits).
    pub recommended: Option<Version>,
}

#[derive(Clone, Debug, Serialize)]
#[serde(rename_all = "camelCase")]
pub struct Update {
    pub id: String,
    pub name: String,
    pub installed: Version,
    pub latest: Version,
}

#[derive(Clone, Debug, Serialize)]
#[serde(rename_all = "camelCase")]
pub struct IndexView {
    pub url: String,
    pub generated: Option<String>,
    pub skipped: usize,
    pub mods: Vec<ModView>,
    pub updates: Vec<Update>,
}

/// What installing `v` of `id` would run into, given the installed packages.
pub fn assess(
    id: &str,
    v: &IndexVersion,
    index: &Index,
    packages: &[Package],
    enabled: &HashSet<String>,
    sdk: SdkInfo,
) -> Vec<Note> {
    let mut notes = Vec::new();
    let mut note = |severity, message: String| notes.push(Note { severity, message });
    if let Some(api) = v.api {
        if !sdk.installed {
            note(Severity::Warning, "Has code: needs T3SDK, which is not installed (Play page)".into());
        } else if api > sdk.api {
            note(
                Severity::Error,
                format!("Needs a newer T3SDK (API version {api}; the installed SDK has {})", sdk.api),
            );
        }
    }
    let installed = |need: &str| packages.iter().find(|p| p.id == need).and_then(Package::ok);
    for (need, range) in &v.requires {
        let wanted = if range.trim() == "*" { need.clone() } else { format!("{need} {range}") };
        let available =
            index.find(need).and_then(|m| m.versions.iter().find(|x| version::satisfies(range, &x.version)));
        match (installed(need), available) {
            (Some(m), _) if version::satisfies(range, &m.version) => {
                if !enabled.contains(need) {
                    note(Severity::Warning, format!("Needs {need}, which is installed but disabled"));
                }
            }
            (Some(m), Some(a)) => note(
                Severity::Warning,
                format!("Needs {wanted}; {} is installed, the index has {}", m.version, a.version),
            ),
            (Some(m), None) => note(Severity::Error, format!("Needs {wanted}; {} is installed", m.version)),
            (None, Some(_)) => note(Severity::Warning, format!("Needs {wanted}: install it too (it is in the index)")),
            (None, None) => note(Severity::Error, format!("Needs {wanted}, which is not installed or in the index")),
        }
    }
    for c in &v.conflicts {
        if enabled.contains(c) && installed(c).is_some() {
            note(Severity::Error, format!("Conflicts with {c}, which is enabled"));
        }
    }
    for p in packages.iter().filter(|p| p.id != id && enabled.contains(&p.id)) {
        if p.ok().is_some_and(|m| m.conflicts.iter().any(|c| c == id)) {
            note(Severity::Error, format!("{} (enabled) conflicts with it", p.id));
        }
    }
    notes
}

pub fn view(url: &str, index: &Index, packages: &[Package], enabled: &HashSet<String>, sdk: SdkInfo) -> IndexView {
    let mut updates = Vec::new();
    let mods = index
        .mods
        .iter()
        .map(|m| {
            let installed = packages.iter().find(|p| p.id == m.id).and_then(Package::ok).map(|p| p.version.clone());
            let versions: Vec<VersionView> = m
                .versions
                .iter()
                .map(|v| {
                    let notes = assess(&m.id, v, index, packages, enabled, sdk);
                    let compatible = !notes.iter().any(|n| n.severity == Severity::Error);
                    VersionView { version: v.clone(), compatible, notes }
                })
                .collect();
            let release = |v: &&VersionView| v.version.version.pre.is_empty();
            let recommended = versions
                .iter()
                .filter(release)
                .find(|v| v.compatible)
                .or_else(|| versions.iter().find(|v| v.compatible))
                .or_else(|| versions.iter().find(release))
                .or(versions.first())
                .map(|v| v.version.version.clone());
            if let Some(current) = &installed {
                let newer = versions.iter().find(|v| {
                    v.compatible
                        && v.version.version > *current
                        && (v.version.version.pre.is_empty() || !current.pre.is_empty())
                });
                if let Some(n) = newer {
                    updates.push(Update {
                        id: m.id.clone(),
                        name: m.name.clone(),
                        installed: current.clone(),
                        latest: n.version.version.clone(),
                    });
                }
            }
            ModView {
                id: m.id.clone(),
                name: m.name.clone(),
                description: m.description.clone(),
                authors: m.authors.clone(),
                homepage: m.homepage.clone(),
                license: m.license.clone(),
                tags: m.tags.clone(),
                enabled: enabled.contains(&m.id),
                installed,
                versions,
                recommended,
            }
        })
        .collect();
    IndexView { url: url.to_string(), generated: index.generated.clone(), skipped: index.skipped, mods, updates }
}

// ---- network -------------------------------------------------------------------

fn agent() -> ureq::Agent {
    use ureq::tls::{RootCerts, TlsConfig, TlsProvider};
    let tls = TlsConfig::builder().provider(TlsProvider::NativeTls).root_certs(RootCerts::PlatformVerifier).build();
    ureq::Agent::config_builder()
        .tls_config(tls)
        .https_only(true)
        .user_agent(format!("T3SDK-Launcher/{}", env!("CARGO_PKG_VERSION")))
        .timeout_connect(Some(Duration::from_secs(20)))
        .timeout_recv_response(Some(Duration::from_secs(30)))
        .build()
        .into()
}

pub fn fetch(url: &str) -> Result<Index, String> {
    if !valid_https(url) {
        return Err(format!("the mod index URL must start with https:// ({url})"));
    }
    let mut response = agent().get(url).call().map_err(|e| format!("cannot fetch the mod index from {url}: {e}"))?;
    let text = response
        .body_mut()
        .with_config()
        .limit(32 << 20)
        .read_to_string()
        .map_err(|e| format!("cannot read the mod index from {url}: {e}"))?;
    parse(&text)
}

/// Downloads `v` into `dest`, checking its size and SHA-256 against the index.
pub fn download(v: &IndexVersion, dest: &Path, mut progress: impl FnMut(u64, u64)) -> Result<(), String> {
    let mut response = agent().get(&v.url).call().map_err(|e| format!("cannot download {}: {e}", v.url))?;
    let mut reader = response.body_mut().with_config().limit(v.size + 1).reader();
    let mut file = std::fs::File::create(dest).map_err(|e| format!("cannot write {}: {e}", dest.display()))?;
    let mut hasher = Sha256::new();
    let mut buf = vec![0u8; 256 * 1024];
    let mut received = 0u64;
    loop {
        let n = reader.read(&mut buf).map_err(|e| format!("download of {} failed: {e}", v.url))?;
        if n == 0 {
            break;
        }
        received += n as u64;
        if received > v.size {
            return Err(format!("{} is larger than the index says ({} bytes): refused", v.url, v.size));
        }
        hasher.update(&buf[..n]);
        file.write_all(&buf[..n]).map_err(|e| format!("cannot write {}: {e}", dest.display()))?;
        progress(received, v.size);
    }
    file.sync_all().map_err(|e| format!("cannot write {}: {e}", dest.display()))?;
    if received != v.size {
        return Err(format!("{} is {received} bytes, the index says {}: refused", v.url, v.size));
    }
    let hash = super::files::hex(&hasher.finalize());
    if hash != v.sha256 {
        return Err(format!("{} does not match the index's SHA-256: refused", v.url));
    }
    Ok(())
}

#[cfg(test)]
mod tests {
    use super::*;

    const SHA: &str = "ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad";

    fn version(v: &str, extra: &str) -> String {
        format!(r#"{{"version": "{v}", "url": "https://example.org/{v}.t3mod", "sha256": "{SHA}", "size": 10{extra}}}"#)
    }

    #[test]
    fn reads_leniently() {
        let doc = format!(
            r#"{{"format": 1, "generated": "2026-09-28T12:00:00Z", "mods": [
                {{"id": "a", "name": "A", "versions": [{}, {}, {}]}},
                {{"id": "Bad", "name": "B", "versions": [{}]}},
                {{"id": "c", "name": "C", "versions": [{{"version": "1.0.0", "url": "http://x", "sha256": "{SHA}", "size": 1}}]}}
            ]}}"#,
            version("1.0.0", ""),
            version("1.2.0", r#", "api": 1, "requires": {"c": ">=1.0.0"}"#),
            version("2.0", ""),
            version("1.0.0", ""),
        );
        let index = parse(&doc).unwrap();
        assert_eq!(index.mods.len(), 1);
        assert_eq!(
            index.skipped, 4,
            "one bad version, one bad mod id, one mod without usable versions (and its version)"
        );
        let a = &index.mods[0];
        assert_eq!(a.versions.iter().map(|v| v.version.to_string()).collect::<Vec<_>>(), ["1.2.0", "1.0.0"]);
        assert!(parse(r#"{"format": 2, "mods": []}"#).is_err());
    }
}
