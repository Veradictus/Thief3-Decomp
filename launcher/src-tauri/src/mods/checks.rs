// The checks of docs/mods.md ("Checks") over the enabled packages, and which
// of them are active: an enabled package with an error stays off (out of
// load-order.txt and the overlay) until it is fixed. Requirements are
// resolved to a fixed point, so a mod whose requirement is itself off is off
// too.
use std::collections::{BTreeMap, HashMap, HashSet};

use serde::Serialize;

use super::layout::{Package, SdkInfo};
use super::version;

#[derive(Clone, Copy, Debug, PartialEq, Eq, Serialize)]
#[serde(rename_all = "camelCase")]
pub enum Severity {
    Error,
    Warning,
    Info,
}

/// A change that fixes an issue, which the UI offers as a button.
#[derive(Clone, Debug, PartialEq, Eq, Serialize)]
#[serde(tag = "kind", rename_all = "camelCase")]
pub enum FixAction {
    /// Move `id` to just before `before` in the load order.
    MoveBefore {
        id: String,
        before: String,
    },
    Enable {
        id: String,
    },
    Disable {
        id: String,
    },
}

#[derive(Clone, Debug, Serialize)]
#[serde(rename_all = "camelCase")]
pub struct Fix {
    pub label: String,
    pub action: FixAction,
}

#[derive(Clone, Debug, Serialize)]
#[serde(rename_all = "camelCase")]
pub struct Issue {
    pub severity: Severity,
    /// The package the issue is about (None: the whole list).
    #[serde(rename = "mod")]
    pub id: Option<String>,
    pub message: String,
    pub fix: Option<Fix>,
}

impl Issue {
    pub fn new(severity: Severity, id: Option<&str>, message: impl Into<String>) -> Issue {
        Issue { severity, id: id.map(str::to_string), message: message.into(), fix: None }
    }

    fn with(mut self, label: String, action: FixAction) -> Issue {
        self.fix = Some(Fix { label, action });
        self
    }
}

pub struct Report {
    pub issues: Vec<Issue>,
    /// Enabled packages without errors, in load order.
    pub active: Vec<String>,
}

fn conflict(a: &Package, b: &Package) -> bool {
    let names = |p: &Package, other: &str| p.ok().is_some_and(|m| m.conflicts.iter().any(|c| c == other));
    names(a, &b.id) || names(b, &a.id)
}

/// Checks `packages` (in load order) with `enabled` switched on.
pub fn check(packages: &[Package], enabled: &HashSet<String>, sdk: SdkInfo) -> Report {
    let by_id: HashMap<&str, &Package> = packages.iter().map(|p| (p.id.as_str(), p)).collect();
    let position = |id: &str| packages.iter().position(|p| p.id == id);
    let on: Vec<&Package> = packages.iter().filter(|p| enabled.contains(&p.id)).collect();
    let mut issues = Vec::new();

    // Broken packages and missing DLLs: errors, off.
    let mut active: HashSet<&str> = HashSet::new();
    for p in &on {
        match &p.manifest {
            Err(e) => issues.push(Issue::new(Severity::Error, Some(&p.id), format!("Cannot be used: {e}"))),
            Ok(m) if m.entry.is_some() && !p.entry_found => issues.push(Issue::new(
                Severity::Error,
                Some(&p.id),
                format!("Its DLL {} is missing; reinstall the mod", m.entry.as_deref().unwrap_or_default()),
            )),
            Ok(_) => {
                active.insert(&p.id);
            }
        }
    }

    // Conflicts (either side): both stay off.
    for (i, a) in on.iter().enumerate() {
        for b in &on[i + 1..] {
            if conflict(a, b) {
                for (x, y) in [(a, b), (b, a)] {
                    let issue = Issue::new(
                        Severity::Error,
                        Some(&x.id),
                        format!("Conflicts with {}; both stay off until one is disabled", y.id),
                    );
                    issues.push(issue.with(format!("Disable {}", y.id), FixAction::Disable { id: y.id.clone() }));
                }
                active.remove(a.id.as_str());
                active.remove(b.id.as_str());
            }
        }
    }

    // Requirements, to a fixed point.
    let satisfied = |need: &str, range: &str, active: &HashSet<&str>| {
        active.contains(need) && by_id[need].ok().is_some_and(|m| version::satisfies(range, &m.version))
    };
    loop {
        let off: Vec<&str> = active
            .iter()
            .copied()
            .filter(|id| {
                let requires = by_id[id].ok().map(|m| &m.requires);
                requires.is_some_and(|r| r.iter().any(|(need, range)| !satisfied(need, range, &active)))
            })
            .collect();
        if off.is_empty() {
            break;
        }
        for id in off {
            active.remove(id);
        }
    }
    for p in &on {
        let Some(m) = p.ok() else { continue };
        for (need, range) in &m.requires {
            let wanted = if range.trim() == "*" { need.clone() } else { format!("{need} {range}") };
            let issue = match by_id.get(need.as_str()).map(|q| (q, q.ok())) {
                None => Issue::new(Severity::Error, Some(&p.id), format!("Needs {wanted}, which is not installed")),
                Some((_, None)) => {
                    Issue::new(Severity::Error, Some(&p.id), format!("Needs {need}, which cannot be used"))
                }
                Some((_, Some(q))) if !version::satisfies(range, &q.version) => {
                    Issue::new(Severity::Error, Some(&p.id), format!("Needs {wanted}; {} is installed", q.version))
                }
                Some(_) if !enabled.contains(need) => {
                    Issue::new(Severity::Error, Some(&p.id), format!("Needs {need}, which is disabled"))
                        .with(format!("Enable {need}"), FixAction::Enable { id: need.clone() })
                }
                Some(_) if !active.contains(need.as_str()) => Issue::new(
                    Severity::Error,
                    Some(&p.id),
                    format!("Needs {need}, which is off because of its own problem"),
                ),
                Some(_) if position(need) > position(&p.id) => Issue::new(
                    Severity::Warning,
                    Some(&p.id),
                    format!("{need} should load before {}: it is a requirement", p.id),
                )
                .with(
                    format!("Move {need} before {}", p.id),
                    FixAction::MoveBefore { id: need.clone(), before: p.id.clone() },
                ),
                Some(_) => continue,
            };
            issues.push(issue);
        }
    }
    // Code needs the SDK, and a new enough one: warnings only.
    for p in &on {
        let Some(m) = p.ok() else { continue };
        if m.entry.is_some() {
            if !sdk.installed {
                issues.push(Issue::new(
                    Severity::Warning,
                    Some(&p.id),
                    "Has code, but T3SDK is not installed (Play page), so the game will not load it",
                ));
            } else if m.api.is_some_and(|api| api > sdk.api) {
                issues.push(Issue::new(
                    Severity::Warning,
                    Some(&p.id),
                    format!(
                        "Needs T3SDK API version {}; the installed SDK has {}, so the mod may refuse to load",
                        m.api.unwrap_or_default(),
                        sdk.api
                    ),
                ));
            }
        }
    }

    let active: Vec<String> =
        packages.iter().filter(|p| active.contains(p.id.as_str())).map(|p| p.id.clone()).collect();
    issues.extend(overlaps(packages, &active));
    issues.sort_by_key(|i| (i.id.as_deref().and_then(position), i.severity as u8));
    Report { issues, active }
}

/// Active packages providing the same files/ or textures/ path: the later one wins.
fn overlaps(packages: &[Package], active: &[String]) -> Vec<Issue> {
    let mut issues = Vec::new();
    for (kind, pick) in [("file", 0), ("texture", 1)] {
        // path (lower case) -> earlier owner; (earlier, later) -> paths
        let mut owner: HashMap<String, &str> = HashMap::new();
        let mut pairs: BTreeMap<(usize, usize), Vec<&str>> = BTreeMap::new();
        for (index, id) in active.iter().enumerate() {
            let Some(p) = packages.iter().find(|p| &p.id == id) else { continue };
            let list = if pick == 0 { &p.files } else { &p.textures };
            for f in list {
                if let Some(before) = owner.insert(f.rel.to_lowercase(), id) {
                    let earlier = active.iter().position(|a| a == before).unwrap_or_default();
                    pairs.entry((earlier, index)).or_default().push(&f.rel);
                }
            }
        }
        for ((earlier, later), paths) in pairs {
            let n = paths.len();
            let example = paths.first().copied().unwrap_or_default();
            issues.push(Issue::new(
                Severity::Info,
                Some(&active[later]),
                format!(
                    "Replaces {n} {kind}{} of {} (such as {example}): it loads later, so it wins",
                    if n == 1 { "" } else { "s" },
                    active[earlier]
                ),
            ));
        }
    }
    issues
}
