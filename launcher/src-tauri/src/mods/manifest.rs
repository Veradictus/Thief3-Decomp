// mod.json, the package manifest (docs/mods.md, "mod.json"): parsing and
// validation with the rules of tools/mods/t3modlib.py. Every problem names
// the field at fault, as the shared fixtures in tools/mods/fixtures expect.
// Unknown fields are ignored; the JSON itself is strict (UTF-8 without a
// byte-order mark, no key twice, no NaN).
use std::collections::BTreeMap;
use std::fmt;

use semver::Version;
use serde::de::{self, Deserializer, MapAccess, SeqAccess, Visitor};
use serde::{Deserialize, Serialize};
use serde_json::{Map, Value};

use super::version::Range;

pub const FORMAT: u64 = 1;

pub const TAGS: [&str; 9] = ["gameplay", "graphics", "textures", "audio", "ui", "fixes", "maps", "tools", "library"];

/// Folders in System/mods/ that are not packages, so no package may be named
/// after them.
pub const RESERVED_IDS: [&str; 2] = ["disabled", "originals"];

#[derive(Clone, Debug, Serialize)]
#[serde(rename_all = "camelCase")]
pub struct Manifest {
    pub id: String,
    pub name: String,
    pub version: Version,
    pub authors: Vec<String>,
    pub description: Option<String>,
    pub api: Option<u32>,
    pub entry: Option<String>,
    pub requires: BTreeMap<String, String>,
    pub conflicts: Vec<String>,
    pub homepage: Option<String>,
    pub license: Option<String>,
    pub tags: Vec<String>,
}

#[derive(Clone, Debug, PartialEq, Eq)]
pub struct FieldError {
    pub field: String,
    pub message: String,
}

impl fmt::Display for FieldError {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        write!(f, "{}: {}", self.field, self.message)
    }
}

/// All problems in one line, for messages.
pub fn describe(errors: &[FieldError]) -> String {
    errors.iter().map(ToString::to_string).collect::<Vec<_>>().join("; ")
}

pub fn valid_id(id: &str) -> bool {
    let bytes = id.as_bytes();
    (1..=64).contains(&bytes.len())
        && (bytes[0].is_ascii_lowercase() || bytes[0].is_ascii_digit())
        && bytes.iter().all(|b| b.is_ascii_lowercase() || b.is_ascii_digit() || *b == b'_' || *b == b'-')
        && !RESERVED_IDS.contains(&id)
}

/// An `https://` URL with a host.
pub fn valid_https(url: &str) -> bool {
    url.strip_prefix("https://")
        .and_then(|rest| rest.split(['/', '?', '#']).next())
        .is_some_and(|host| !host.is_empty() && !url.chars().any(char::is_whitespace))
}

// ---- strict JSON: serde_json keeps the last of two equal keys; we refuse them ----

struct Strict(Value);

impl<'de> Deserialize<'de> for Strict {
    fn deserialize<D: Deserializer<'de>>(deserializer: D) -> Result<Self, D::Error> {
        deserializer.deserialize_any(StrictVisitor).map(Strict)
    }
}

struct StrictVisitor;

impl<'de> Visitor<'de> for StrictVisitor {
    type Value = Value;

    fn expecting(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        f.write_str("JSON")
    }
    fn visit_bool<E>(self, v: bool) -> Result<Value, E> {
        Ok(Value::Bool(v))
    }
    fn visit_i64<E>(self, v: i64) -> Result<Value, E> {
        Ok(Value::from(v))
    }
    fn visit_u64<E>(self, v: u64) -> Result<Value, E> {
        Ok(Value::from(v))
    }
    fn visit_f64<E>(self, v: f64) -> Result<Value, E> {
        Ok(Value::from(v))
    }
    fn visit_str<E>(self, v: &str) -> Result<Value, E> {
        Ok(Value::String(v.to_string()))
    }
    fn visit_string<E>(self, v: String) -> Result<Value, E> {
        Ok(Value::String(v))
    }
    fn visit_unit<E>(self) -> Result<Value, E> {
        Ok(Value::Null)
    }
    fn visit_seq<A: SeqAccess<'de>>(self, mut seq: A) -> Result<Value, A::Error> {
        let mut items = Vec::new();
        while let Some(Strict(v)) = seq.next_element()? {
            items.push(v);
        }
        Ok(Value::Array(items))
    }
    fn visit_map<A: MapAccess<'de>>(self, mut map: A) -> Result<Value, A::Error> {
        let mut out = Map::new();
        while let Some(key) = map.next_key::<String>()? {
            if out.contains_key(&key) {
                return Err(de::Error::custom(format!("the key {key:?} appears twice")));
            }
            let Strict(v) = map.next_value()?;
            out.insert(key, v);
        }
        Ok(Value::Object(out))
    }
}

/// JSON text as the mod tools read it: no byte-order mark, no key twice.
pub fn strict_json(text: &str) -> Result<Value, String> {
    if text.starts_with('\u{feff}') {
        return Err("starts with a UTF-8 byte-order mark; save it as UTF-8 without one".into());
    }
    serde_json::from_str::<Strict>(text).map(|s| s.0).map_err(|e| format!("not valid JSON: {e}"))
}

// ---- the fields ---------------------------------------------------------------

struct Reader<'a> {
    doc: &'a Map<String, Value>,
    errors: Vec<FieldError>,
}

impl<'a> Reader<'a> {
    fn fail(&mut self, field: &str, message: impl Into<String>) {
        self.errors.push(FieldError { field: field.to_string(), message: message.into() });
    }

    /// A present field, `null` included (which is then of the wrong type).
    fn get(&self, field: &str) -> Option<&'a Value> {
        self.doc.get(field)
    }

    fn string(&mut self, field: &str, required: bool) -> Option<&'a str> {
        match self.get(field) {
            Some(Value::String(s)) => Some(s),
            Some(_) => {
                self.fail(field, "must be a string");
                None
            }
            None => {
                if required {
                    self.fail(field, "missing (required)");
                }
                None
            }
        }
    }

    /// A list of non-blank strings.
    fn strings(&mut self, field: &str, what: &str) -> Vec<String> {
        match self.get(field) {
            None => Vec::new(),
            Some(Value::Array(items)) if items.iter().all(|v| v.as_str().is_some_and(|s| !s.trim().is_empty())) => {
                items.iter().filter_map(|v| v.as_str().map(str::to_string)).collect()
            }
            Some(_) => {
                self.fail(field, format!("must be a list of {what}"));
                Vec::new()
            }
        }
    }
}

/// Reads mod.json text.
pub fn parse(text: &str) -> Result<Manifest, Vec<FieldError>> {
    match strict_json(text) {
        Ok(doc) => validate(&doc),
        Err(message) => Err(vec![FieldError { field: "mod.json".into(), message }]),
    }
}

pub fn validate(doc: &Value) -> Result<Manifest, Vec<FieldError>> {
    let Some(doc) = doc.as_object() else {
        return Err(vec![FieldError { field: "mod.json".into(), message: "must be a JSON object".into() }]);
    };
    let mut r = Reader { doc, errors: Vec::new() };

    match r.get("format") {
        Some(v) if v.as_u64() == Some(FORMAT) => {}
        Some(v) if v.as_u64().is_some_and(|f| f > FORMAT) => {
            r.fail("format", format!("{v} is newer than this launcher reads ({FORMAT}); update the launcher"))
        }
        Some(v) => r.fail("format", format!("must be {FORMAT}, not {v}")),
        None => r.fail("format", "missing (required)"),
    }

    let id = r.string("id", true).unwrap_or_default().to_string();
    if r.get("id").is_some_and(Value::is_string) && !valid_id(&id) {
        let reserved = if RESERVED_IDS.contains(&id.as_str()) { " (and not disabled or originals)" } else { "" };
        r.fail(
            "id",
            format!("{id:?} is not a mod id: 1-64 of a-z, 0-9, _ and -, starting with a letter or digit{reserved}"),
        );
    }

    let name = r.string("name", true).unwrap_or_default().to_string();
    if r.get("name").is_some_and(Value::is_string) && !(1..=80).contains(&name.chars().count()) {
        r.fail("name", "must be 1-80 characters");
    }

    let version = r.string("version", true).and_then(|v| match Version::parse(v) {
        Ok(v) => Some(v),
        Err(e) => {
            r.fail("version", format!("{v:?} is not a semantic version (MAJOR.MINOR.PATCH): {e}"));
            None
        }
    });

    let authors = match r.get("authors") {
        None => {
            r.fail("authors", "missing (required)");
            Vec::new()
        }
        Some(Value::Array(items)) if items.is_empty() => {
            r.fail("authors", "needs at least one name");
            Vec::new()
        }
        Some(_) => r.strings("authors", "names"),
    };

    let description = r.string("description", false).map(str::to_string);
    if description.as_ref().is_some_and(|d| d.chars().count() > 1000) {
        r.fail("description", "must be at most 1000 characters");
    }

    let entry = r.string("entry", false).map(str::to_string);
    if let Some(e) = &entry {
        if !e.to_ascii_lowercase().ends_with(".dll") {
            r.fail("entry", format!("{e:?} must be the file name of the mod's DLL, ending in .dll"));
        } else if e.contains(['/', '\\']) {
            r.fail("entry", format!("{e:?} must be a file at the package root, not in a folder"));
        } else if let Err(why) = super::files::check_rel(e) {
            r.fail("entry", why);
        }
    }

    let api = match r.get("api") {
        None => {
            if entry.is_some() || r.get("entry").is_some() {
                r.fail("api", "missing: required with entry (the lowest T3SDK_API_VERSION the DLL needs)");
            }
            None
        }
        Some(v) => match v.as_u64().filter(|n| *n >= 1).and_then(|n| u32::try_from(n).ok()) {
            Some(n) => Some(n),
            None => {
                r.fail("api", format!("must be a whole number, 1 or more, not {v}"));
                None
            }
        },
    };

    let mut requires = BTreeMap::new();
    match r.get("requires") {
        None => {}
        Some(Value::Object(map)) => {
            for (other, range) in map {
                let Some(range) = range.as_str() else {
                    r.fail("requires", format!("{other}: the version range must be a string"));
                    continue;
                };
                if !valid_id(other) {
                    r.fail("requires", format!("{other:?} is not a mod id"));
                } else if *other == id {
                    r.fail("requires", "a mod cannot require itself");
                } else if let Err(e) = Range::parse(range) {
                    r.fail("requires", format!("{other}: {e}"));
                } else {
                    requires.insert(other.clone(), range.to_string());
                }
            }
        }
        Some(_) => r.fail("requires", "must be an object of mod id to version range"),
    }

    let conflicts = r.strings("conflicts", "mod ids");
    for other in &conflicts {
        if !valid_id(other) {
            r.fail("conflicts", format!("{other:?} is not a mod id"));
        } else if *other == id {
            r.fail("conflicts", "a mod cannot conflict with itself");
        } else if r.get("requires").and_then(Value::as_object).is_some_and(|m| m.contains_key(other)) {
            r.fail("conflicts", format!("{other} is also in requires"));
        }
    }

    let homepage = r.string("homepage", false).map(str::to_string);
    if homepage.as_ref().is_some_and(|h| !valid_https(h)) {
        r.fail("homepage", "must be an https:// URL");
    }

    let license = r.string("license", false).map(str::to_string);
    if license.as_ref().is_some_and(|l| l.trim().is_empty()) {
        r.fail("license", "must be an SPDX identifier (MIT, CC-BY-4.0, ...) or a short text");
    }

    let tags = r.strings("tags", "tags");
    if tags.len() > 8 {
        r.fail("tags", "at most 8");
    }
    for t in &tags {
        if !TAGS.contains(&t.as_str()) {
            r.fail("tags", format!("{t:?} is not one of {}", TAGS.join(", ")));
        }
    }
    if tags.iter().enumerate().any(|(i, t)| tags[..i].contains(t)) {
        r.fail("tags", "lists a tag twice");
    }

    match version {
        Some(version) if r.errors.is_empty() => Ok(Manifest {
            id,
            name,
            version,
            authors,
            description,
            api,
            entry,
            requires,
            conflicts,
            homepage,
            license,
            tags,
        }),
        _ => Err(r.errors),
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    fn fixtures(kind: &str) -> Vec<(String, String)> {
        let dir = std::path::Path::new(env!("CARGO_MANIFEST_DIR")).join("../../tools/mods/fixtures").join(kind);
        let mut list: Vec<(String, String)> = std::fs::read_dir(&dir)
            .unwrap()
            .flatten()
            .map(|e| (e.file_name().to_string_lossy().into_owned(), std::fs::read_to_string(e.path()).unwrap()))
            .collect();
        list.sort();
        assert!(!list.is_empty(), "no fixtures in {}", dir.display());
        list
    }

    #[test]
    fn valid_fixtures_pass() {
        for (name, text) in fixtures("valid") {
            let m = parse(&text).unwrap_or_else(|e| panic!("{name}: {}", describe(&e)));
            assert!(!m.id.is_empty() && !m.authors.is_empty(), "{name}");
        }
    }

    #[test]
    fn invalid_fixtures_fail_on_their_field() {
        for (name, text) in fixtures("invalid") {
            let doc: Value = serde_json::from_str(&text).unwrap();
            let expect = doc["_expect"].as_str().unwrap_or_else(|| panic!("{name} has no _expect")).to_string();
            let errors = parse(&text).err().unwrap_or_else(|| panic!("{name} was accepted"));
            assert!(errors.iter().all(|e| e.field == expect), "{name}: expected {expect}, got {}", describe(&errors));
        }
    }

    #[test]
    fn details() {
        let base = r#""format": 1, "name": "N", "version": "1.0.0", "authors": ["A"]"#;
        let with = |extra: &str| parse(&format!("{{{base}, {extra}}}"));
        let field = |extra: &str| with(extra).unwrap_err().iter().map(|e| e.field.clone()).collect::<Vec<_>>();
        assert!(with(r#""id": "m", "entry": "M.Dll", "api": 3"#).is_ok());
        assert!(with(r#""id": "m", "authors2": 1, "future": null"#).is_ok());
        assert_eq!(field(r#""id": "originals""#), ["id"]);
        assert_eq!(field(r#""id": "m", "entry": "a:b.dll", "api": 1"#), ["entry"]);
        assert_eq!(field(r#""id": "m", "tags": ["ui", "ui"]"#), ["tags"]);
        assert_eq!(field(r#""id": "m", "homepage": "https://""#), ["homepage"]);
        assert_eq!(field(r#""id": "m", "description": null"#), ["description"]);
        assert_eq!(field(r#""id": "m", "license": " ""#), ["license"]);
        assert_eq!(field(r#""id": "m", "requires": {"x": "*"}, "conflicts": ["x"]"#), ["conflicts"]);
        assert_eq!(field(r#""id": "m", "format": 3"#), ["mod.json"], "a key twice");
        assert!(parse(&format!("\u{feff}{{{base}, \"id\": \"m\"}}")).is_err());
        let m = parse(r#"{"format": 1, "id": "m", "name": "N", "version": "1.0.0", "authors": [" "]}"#);
        assert_eq!(m.unwrap_err()[0].field, "authors");
    }
}
