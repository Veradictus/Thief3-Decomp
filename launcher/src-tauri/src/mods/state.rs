// System/mods/state.json (docs/mods.md, "state.json"): the load order, the
// enabled packages, and the profiles. The active profile follows every change,
// so "save as" copies it and switching applies another one.
use std::collections::{BTreeMap, HashSet};
use std::path::Path;

use serde::{Deserialize, Serialize};

use super::files;

pub const DEFAULT_PROFILE: &str = "Default";

#[derive(Clone, Debug, Default, PartialEq, Eq, Serialize, Deserialize)]
#[serde(default)]
pub struct Profile {
    pub order: Vec<String>,
    pub enabled: Vec<String>,
}

#[derive(Clone, Debug, PartialEq, Eq, Serialize, Deserialize)]
#[serde(default)]
pub struct State {
    pub format: u32,
    pub order: Vec<String>,
    pub enabled: Vec<String>,
    pub profile: String,
    pub profiles: BTreeMap<String, Profile>,
    /// The texture packs last applied to the game's bundles (`id@version`, in
    /// load order), so a sync can tell when t3texpack.py has to run again.
    #[serde(skip_serializing_if = "Vec::is_empty")]
    pub textures: Vec<String>,
}

impl Default for State {
    fn default() -> Self {
        State {
            format: 1,
            order: Vec::new(),
            enabled: Vec::new(),
            profile: DEFAULT_PROFILE.into(),
            profiles: BTreeMap::new(),
            textures: Vec::new(),
        }
    }
}

/// The saved state; a missing or unreadable file means "nothing enabled".
pub fn load(path: &Path) -> State {
    std::fs::read_to_string(path).ok().and_then(|t| serde_json::from_str(&t).ok()).unwrap_or_default()
}

pub fn save(path: &Path, state: &State) -> Result<(), String> {
    let mut text = serde_json::to_string_pretty(state).map_err(|e| e.to_string())?;
    text.push('\n');
    files::atomic_write(path, text.as_bytes())
}

/// A profile name as the UI offers it: 1-40 characters, no control characters.
pub fn check_profile_name(name: &str) -> Result<&str, String> {
    let name = name.trim();
    if name.is_empty() || name.chars().count() > 40 || name.chars().any(char::is_control) {
        return Err("a profile name is 1-40 characters".into());
    }
    Ok(name)
}

/// `order` and `enabled` limited to `installed` (listed in folder order):
/// unknown ids dropped (and returned), duplicates removed, new packages
/// appended, `enabled` kept in load order.
fn fit(profile: &Profile, installed: &[String]) -> (Profile, Vec<String>) {
    let known: HashSet<&str> = installed.iter().map(String::as_str).collect();
    let mut seen = HashSet::new();
    let mut skipped = Vec::new();
    let mut order = Vec::new();
    for id in &profile.order {
        if !known.contains(id.as_str()) {
            skipped.push(id.clone());
        } else if seen.insert(id.as_str()) {
            order.push(id.clone());
        }
    }
    for id in installed {
        if seen.insert(id.as_str()) {
            order.push(id.clone());
        }
    }
    let on: HashSet<&str> = profile.enabled.iter().map(String::as_str).collect();
    for id in &profile.enabled {
        if !known.contains(id.as_str()) && !skipped.contains(id) {
            skipped.push(id.clone());
        }
    }
    let enabled = order.iter().filter(|id| on.contains(id.as_str())).cloned().collect();
    (Profile { order, enabled }, skipped)
}

impl State {
    pub fn current(&self) -> Profile {
        Profile { order: self.order.clone(), enabled: self.enabled.clone() }
    }

    /// Fits the state to the installed packages and makes sure the active
    /// profile exists and matches it.
    pub fn normalize(&mut self, installed: &[String]) {
        self.format = 1;
        let (fitted, _) = fit(&self.current(), installed);
        self.order = fitted.order;
        self.enabled = fitted.enabled;
        if check_profile_name(&self.profile).is_err() {
            self.profile = DEFAULT_PROFILE.into();
        }
        self.commit();
    }

    /// Records the current order and enabled set in the active profile.
    pub fn commit(&mut self) {
        let current = self.current();
        self.profiles.insert(self.profile.clone(), current);
    }

    pub fn is_enabled(&self, id: &str) -> bool {
        self.enabled.iter().any(|e| e == id)
    }

    pub fn set_enabled(&mut self, id: &str, on: bool) {
        if on && !self.is_enabled(id) {
            self.enabled.push(id.to_string());
            let order = &self.order;
            self.enabled.sort_by_key(|e| order.iter().position(|o| o == e));
        } else if !on {
            self.enabled.retain(|e| e != id);
        }
        self.commit();
    }

    /// Takes a new order, which must list exactly the installed packages.
    pub fn set_order(&mut self, order: Vec<String>) -> Result<(), String> {
        let mut a: Vec<&String> = order.iter().collect();
        let mut b: Vec<&String> = self.order.iter().collect();
        a.sort();
        b.sort();
        if a != b {
            return Err("the new order must list every installed package once".into());
        }
        self.order = order;
        let order = &self.order;
        self.enabled.sort_by_key(|e| order.iter().position(|o| o == e));
        self.commit();
        Ok(())
    }

    /// Adds a newly installed package at the end, enabled.
    pub fn add(&mut self, id: &str) {
        if !self.order.iter().any(|o| o == id) {
            self.order.push(id.to_string());
        }
        self.set_enabled(id, true);
    }

    /// Forgets a removed package, in every profile.
    pub fn forget(&mut self, id: &str) {
        self.order.retain(|o| o != id);
        self.enabled.retain(|e| e != id);
        for p in self.profiles.values_mut() {
            p.order.retain(|o| o != id);
            p.enabled.retain(|e| e != id);
        }
        self.commit();
    }

    fn find(&self, name: &str) -> Option<String> {
        self.profiles.keys().find(|k| k.eq_ignore_ascii_case(name)).cloned()
    }

    /// Saves the current order and enabled set as a new profile and makes it
    /// the active one.
    pub fn save_as(&mut self, name: &str) -> Result<(), String> {
        let name = check_profile_name(name)?;
        if self.find(name).is_some() {
            return Err(format!("there is already a profile named {name}"));
        }
        self.profile = name.to_string();
        self.commit();
        Ok(())
    }

    /// Makes `name` the active profile and applies it; returns the ids it
    /// lists that are not installed (skipped).
    pub fn switch(&mut self, name: &str, installed: &[String]) -> Result<Vec<String>, String> {
        let key = self.find(name).ok_or_else(|| format!("no profile named {name}"))?;
        let (profile, skipped) = fit(&self.profiles[&key], installed);
        self.profile = key;
        self.order = profile.order;
        self.enabled = profile.enabled;
        self.commit();
        Ok(skipped)
    }

    pub fn delete(&mut self, name: &str) -> Result<(), String> {
        let key = self.find(name).ok_or_else(|| format!("no profile named {name}"))?;
        if key == self.profile {
            return Err("switch to another profile before deleting this one".into());
        }
        self.profiles.remove(&key);
        Ok(())
    }

    pub fn rename(&mut self, from: &str, to: &str) -> Result<(), String> {
        let key = self.find(from).ok_or_else(|| format!("no profile named {from}"))?;
        let to = check_profile_name(to)?;
        if self.find(to).is_some_and(|k| k != key) {
            return Err(format!("there is already a profile named {to}"));
        }
        let profile = self.profiles.remove(&key).unwrap_or_default();
        self.profiles.insert(to.to_string(), profile);
        if self.profile == key {
            self.profile = to.to_string();
        }
        Ok(())
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    fn ids(list: &[&str]) -> Vec<String> {
        list.iter().map(|s| s.to_string()).collect()
    }

    #[test]
    fn missing_file_means_nothing_enabled_in_folder_order() {
        let dir = tempfile::tempdir().unwrap();
        let mut state = load(&dir.path().join("state.json"));
        state.normalize(&ids(&["a", "b"]));
        assert_eq!(state.order, ids(&["a", "b"]));
        assert!(state.enabled.is_empty());
        assert_eq!(state.profile, DEFAULT_PROFILE);
        assert_eq!(state.profiles[DEFAULT_PROFILE].order, ids(&["a", "b"]));
    }

    #[test]
    fn normalize_drops_unknown_and_appends_new() {
        let mut state = State { order: ids(&["c", "x", "a", "c"]), enabled: ids(&["a", "x", "c"]), ..State::default() };
        state.normalize(&ids(&["a", "b", "c"]));
        assert_eq!(state.order, ids(&["c", "a", "b"]));
        assert_eq!(state.enabled, ids(&["c", "a"]));
    }

    #[test]
    fn profiles() {
        let installed = ids(&["a", "b", "c"]);
        let mut state = State::default();
        state.normalize(&installed);
        state.set_enabled("a", true);
        state.set_enabled("c", true);
        state.save_as("Two").unwrap();
        assert!(state.save_as("two").is_err(), "names compare case-insensitively");
        state.set_order(ids(&["c", "b", "a"])).unwrap();
        state.set_enabled("a", false);
        assert_eq!(state.profiles["Two"].enabled, ids(&["c"]));
        assert_eq!(state.profiles[DEFAULT_PROFILE].enabled, ids(&["a", "c"]));

        state.profiles.get_mut(DEFAULT_PROFILE).unwrap().order.push("gone".into());
        let skipped = state.switch("default", &installed).unwrap();
        assert_eq!(skipped, ids(&["gone"]));
        assert_eq!(state.profile, DEFAULT_PROFILE);
        assert_eq!(state.order, ids(&["a", "b", "c"]));
        assert_eq!(state.enabled, ids(&["a", "c"]));

        assert!(state.delete(DEFAULT_PROFILE).is_err());
        state.rename("Two", "Coop").unwrap();
        state.rename(DEFAULT_PROFILE, "Main").unwrap();
        assert_eq!(state.profile, "Main");
        state.delete("coop").unwrap();
        assert_eq!(state.profiles.keys().collect::<Vec<_>>(), vec!["Main"]);
        assert!(state.set_order(ids(&["a", "b"])).is_err());
    }

    #[test]
    fn round_trip() {
        let dir = tempfile::tempdir().unwrap();
        let path = dir.path().join("state.json");
        let mut state = State::default();
        state.normalize(&ids(&["a"]));
        state.add("a");
        save(&path, &state).unwrap();
        assert_eq!(load(&path), state);
        let text = std::fs::read_to_string(&path).unwrap();
        assert!(text.contains("\"profiles\"") && !text.contains("textures"));
    }
}
