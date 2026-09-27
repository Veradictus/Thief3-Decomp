// Minimal INI reading and in-place editing for T3SDK.ini: values are updated
// where they stand, so the file's comments, order and line endings survive.

/// One `key=value` entry and the comment lines directly above it.
#[derive(Clone, Debug, PartialEq)]
pub struct Entry {
    pub section: String,
    pub key: String,
    pub value: String,
    pub comment: String,
}

fn section_of(line: &str) -> Option<&str> {
    let t = line.trim();
    t.strip_prefix('[').and_then(|r| r.strip_suffix(']')).map(str::trim)
}

fn key_value(line: &str) -> Option<(&str, &str)> {
    let t = line.trim();
    if t.is_empty() || t.starts_with(';') || t.starts_with('#') || t.starts_with('[') {
        return None;
    }
    let (k, v) = t.split_once('=')?;
    Some((k.trim(), v.trim()))
}

pub fn parse(text: &str) -> Vec<Entry> {
    let mut entries = Vec::new();
    let mut section = String::new();
    let mut comment: Vec<&str> = Vec::new();
    for line in text.lines() {
        let t = line.trim();
        if let Some(s) = section_of(line) {
            section = s.to_string();
            comment.clear();
        } else if let Some(c) = t.strip_prefix(';').or_else(|| t.strip_prefix('#')) {
            comment.push(c.trim());
        } else if let Some((k, v)) = key_value(line) {
            entries.push(Entry {
                section: section.clone(),
                key: k.into(),
                value: v.into(),
                comment: comment.join(" "),
            });
            comment.clear();
        } else if t.is_empty() {
            comment.clear();
        }
    }
    entries
}

/// Sets `section.key = value` in `text`, replacing the value in place, or adding
/// the key at the end of its section (or a new section at the end of the file).
pub fn set(text: &str, section: &str, key: &str, value: &str) -> String {
    let newline = if text.contains("\r\n") { "\r\n" } else { "\n" };
    let mut lines: Vec<String> = text.lines().map(str::to_string).collect();
    let mut current = String::new();
    let mut last_in_section: Option<usize> = None;
    for (i, line) in lines.iter_mut().enumerate() {
        if let Some(s) = section_of(line) {
            current = s.to_string();
            if current.eq_ignore_ascii_case(section) {
                last_in_section = Some(i);
            }
            continue;
        }
        if !current.eq_ignore_ascii_case(section) {
            continue;
        }
        if let Some((k, _)) = key_value(line) {
            if k.eq_ignore_ascii_case(key) {
                let indent = &line[..line.len() - line.trim_start().len()];
                *line = format!("{indent}{k}={value}");
                return lines.join(newline) + newline;
            }
        }
        if !line.trim().is_empty() {
            last_in_section = Some(i);
        }
    }
    match last_in_section {
        Some(i) => lines.insert(i + 1, format!("{key}={value}")),
        None => {
            if lines.last().is_some_and(|l| !l.trim().is_empty()) {
                lines.push(String::new());
            }
            lines.push(format!("[{section}]"));
            lines.push(format!("{key}={value}"));
        }
    }
    lines.join(newline) + newline
}

#[cfg(test)]
mod tests {
    use super::*;

    const SAMPLE: &str = "; header\r\n[T3SDK]\r\n; 1 = console.\r\nConsole=0\r\nEngineLog=1\r\n\r\n[Fixes]\r\n; skip them\r\nSkipIntros=1\r\n";

    #[test]
    fn parses_comments_and_sections() {
        let e = parse(SAMPLE);
        assert_eq!(e.len(), 3);
        assert_eq!(
            e[0],
            Entry { section: "T3SDK".into(), key: "Console".into(), value: "0".into(), comment: "1 = console.".into() }
        );
        assert_eq!(e[1].comment, "");
        assert_eq!(e[2].section, "Fixes");
    }

    #[test]
    fn replaces_in_place_and_keeps_crlf() {
        let out = set(SAMPLE, "fixes", "skipintros", "0");
        assert_eq!(out, SAMPLE.replace("SkipIntros=1", "SkipIntros=0"));
    }

    #[test]
    fn adds_missing_key_and_section() {
        let out = set(SAMPLE, "T3SDK", "MenuInputTrace", "1");
        assert!(out.contains("EngineLog=1\r\nMenuInputTrace=1\r\n\r\n[Fixes]"));
        let out = set(SAMPLE, "Display", "Borderless", "1");
        assert!(out.ends_with("SkipIntros=1\r\n\r\n[Display]\r\nBorderless=1\r\n"));
        assert_eq!(set("", "A", "b", "c"), "[A]\nb=c\n");
    }
}
