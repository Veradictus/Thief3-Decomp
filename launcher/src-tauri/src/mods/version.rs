// Version ranges as docs/mods.md defines them: comparators (>=, >, <=, <, =,
// ^, ~) separated by commas, or a lone `*`, with Cargo's meaning (the semver
// crate matches them). This side refuses the forms the crate accepts beyond
// the spec, as tools/mods/t3modlib.py does: a bare version ("1.2.3", which
// the crate reads as ^1.2.3), wildcards ("1.*", "1.x"), and build metadata.
// A pre-release version only matches a range with a comparator that has the
// same MAJOR.MINOR.PATCH and a pre-release tag.
use semver::{Comparator, Op, Prerelease, Version, VersionReq};

#[derive(Clone, Debug, PartialEq, Eq)]
pub struct Range {
    /// Empty for `*`.
    comparators: Vec<Comparator>,
}

const OPERATORS: [(&str, Op); 7] = [
    (">=", Op::GreaterEq),
    ("<=", Op::LessEq),
    (">", Op::Greater),
    ("<", Op::Less),
    ("=", Op::Exact),
    ("^", Op::Caret),
    ("~", Op::Tilde),
];

fn number(text: &str) -> Option<u64> {
    let digits = !text.is_empty() && text.bytes().all(|b| b.is_ascii_digit());
    if !digits || (text.len() > 1 && text.starts_with('0')) {
        return None;
    }
    text.parse().ok()
}

fn comparator(text: &str) -> Result<Comparator, String> {
    let (op, rest) = OPERATORS
        .iter()
        .find_map(|(prefix, op)| text.strip_prefix(prefix).map(|rest| (*op, rest.trim_start())))
        .ok_or_else(|| format!("{text:?} does not start with >=, >, <=, <, =, ^ or ~"))?;
    if rest.contains('+') {
        return Err(format!("{text:?}: build metadata is not allowed in a range"));
    }
    let (core, pre) = match rest.split_once('-') {
        Some((c, p)) => (c, Some(p)),
        None => (rest, None),
    };
    let numbers = core.split('.').map(number).collect::<Option<Vec<u64>>>();
    let numbers = numbers
        .filter(|n| (1..=3).contains(&n.len()))
        .ok_or_else(|| format!("{text:?} is not a version (MAJOR[.MINOR[.PATCH]])"))?;
    if pre.is_some() && numbers.len() < 3 {
        return Err(format!("{text:?}: a pre-release needs MAJOR.MINOR.PATCH"));
    }
    let pre = match pre {
        Some(p) => Prerelease::new(p).map_err(|e| format!("{text:?}: {e}"))?,
        None => Prerelease::EMPTY,
    };
    Ok(Comparator { op, major: numbers[0], minor: numbers.get(1).copied(), patch: numbers.get(2).copied(), pre })
}

impl Range {
    pub fn parse(text: &str) -> Result<Range, String> {
        let text = text.trim();
        if text == "*" {
            return Ok(Range { comparators: Vec::new() });
        }
        if text.is_empty() {
            return Err("empty version range".into());
        }
        let comparators = text
            .split(',')
            .map(|part| match part.trim() {
                "" => Err(format!("{text:?} has an empty comparator")),
                "*" => Err(format!("{text:?}: * must stand alone")),
                c => comparator(c),
            })
            .collect::<Result<Vec<_>, _>>()?;
        Ok(Range { comparators })
    }

    pub fn matches(&self, version: &Version) -> bool {
        if self.comparators.is_empty() {
            return version.pre.is_empty();
        }
        VersionReq { comparators: self.comparators.clone() }.matches(version)
    }
}

/// Whether `range` (text) holds for `version`; false for an invalid range.
pub fn satisfies(range: &str, version: &Version) -> bool {
    Range::parse(range).is_ok_and(|r| r.matches(version))
}

#[cfg(test)]
mod tests {
    use super::*;

    fn fixtures() -> std::path::PathBuf {
        std::path::Path::new(env!("CARGO_MANIFEST_DIR")).join("../../tools/mods/fixtures")
    }

    fn check(range: &str, version: &str) -> Option<bool> {
        Range::parse(range).ok().map(|r| r.matches(&Version::parse(version).unwrap()))
    }

    #[test]
    fn shared_range_vectors() {
        let text = std::fs::read_to_string(fixtures().join("ranges.json")).unwrap();
        let cases: Vec<(String, String, Option<bool>)> = serde_json::from_str(&text).unwrap();
        assert!(cases.len() >= 30);
        for (range, version, expected) in cases {
            assert_eq!(check(&range, &version), expected, "{range:?} against {version}");
        }
    }

    #[test]
    fn partial_versions_as_in_cargo() {
        assert_eq!(check("~1", "1.9.0"), Some(true));
        assert_eq!(check("~1", "2.0.0"), Some(false));
        assert_eq!(check("<2", "1.9.9"), Some(true));
        assert_eq!(check("^0", "0.9.0"), Some(true));
        assert_eq!(check("^0.0", "0.0.7"), Some(true));
        assert_eq!(check("^0.0", "0.1.0"), Some(false));
    }

    #[test]
    fn outside_the_subset() {
        for bad in [
            "1.2.3",
            "1.*",
            "1.x",
            "^1.*",
            ">=1.0.0,",
            "*, >=1.0.0",
            ">=v1",
            ">=1.2-beta",
            ">=01.0.0",
            "^1.2.3+build.9",
        ] {
            assert_eq!(check(bad, "1.2.3"), None, "{bad}");
        }
        assert_eq!(check(" >= 1.0.0 , < 2 ", "1.2.3"), Some(true), "spaces around operators, as t3modlib allows");
        assert_eq!(check(">=18446744073709551616", "1.2.3"), None, "numbers are u64");
    }

    #[test]
    fn prerelease_in_a_multi_comparator_range() {
        assert_eq!(check(">=1.1.0-alpha, <2.0.0", "1.1.0-beta.1"), Some(true));
        assert_eq!(check(">=1.0.0, <2.0.0", "1.1.0-beta.1"), Some(false));
    }
}
