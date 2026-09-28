// The mod manager's flows against a temporary folder standing in for a game
// install: install, upgrade, remove, the overlay, load-order.txt, profiles,
// checks, and refused packages.
use std::io::Write;
use std::path::PathBuf;

use zip::write::SimpleFileOptions;

use super::*;

const SDK: SdkInfo = SdkInfo { installed: true, api: 1 };

struct Game {
    root: tempfile::TempDir,
    layout: Layout,
}

impl Game {
    fn new() -> Game {
        let root = tempfile::tempdir().unwrap();
        std::fs::create_dir_all(root.path().join("System")).unwrap();
        let layout = Layout::new(root.path());
        Game { root, layout }
    }

    fn path(&self, rel: &str) -> PathBuf {
        files::join_rel(self.root.path(), rel)
    }

    fn write(&self, rel: &str, data: &str) {
        let p = self.path(rel);
        std::fs::create_dir_all(p.parent().unwrap()).unwrap();
        std::fs::write(p, data).unwrap();
    }

    fn read(&self, rel: &str) -> Option<String> {
        std::fs::read_to_string(self.path(rel)).ok()
    }

    /// Builds a .t3mod next to the game folder.
    fn pack(&self, name: &str, manifest: &str, entries: &[(&str, &str)]) -> PathBuf {
        let path = self.root.path().join(name);
        let mut zip = zip::ZipWriter::new(std::fs::File::create(&path).unwrap());
        let options = SimpleFileOptions::default().compression_method(zip::CompressionMethod::Deflated);
        for (entry, data) in std::iter::once(&("mod.json", manifest)).chain(entries) {
            zip.start_file(*entry, options).unwrap();
            zip.write_all(data.as_bytes()).unwrap();
        }
        zip.finish().unwrap();
        path
    }

    fn install(&self, id: &str, version: &str, extra: &str, entries: &[(&str, &str)]) -> Result<ModList, String> {
        let pkg = self.pack(&format!("{id}-{version}.t3mod"), &manifest(id, version, extra), entries);
        install(&self.layout, SDK, &pkg, None)
    }

    fn overlay(&self) -> overlay::Overlay {
        overlay::load(&self.layout.overlay())
    }

    fn list(&self) -> ModList {
        list(&self.layout, SDK)
    }
}

fn manifest(id: &str, version: &str, extra: &str) -> String {
    format!(
        r#"{{"format": 1, "id": "{id}", "name": "Mod {id}", "version": "{version}", "authors": ["Tester"]{extra}}}"#
    )
}

fn code(id: &str) -> String {
    format!(r#", "entry": "{id}.dll", "api": 1"#)
}

fn ids(list: &ModList) -> Vec<&str> {
    list.packages.iter().map(|p| p.id.as_str()).collect()
}

fn load_order_lines(game: &Game) -> Vec<String> {
    game.read("System/mods/load-order.txt")
        .unwrap_or_default()
        .lines()
        .filter(|l| !l.is_empty() && !l.starts_with('#'))
        .map(str::to_string)
        .collect()
}

#[test]
fn install_writes_the_package_state_and_load_order() {
    let game = Game::new();
    let list = game.install("alpha", "1.0.0", &code("alpha"), &[("alpha.dll", "MZ"), ("alpha.ini", "[x]")]).unwrap();
    assert!(game.path("System/mods/alpha/alpha.dll").is_file());
    assert!(game.path("System/mods/alpha/mod.json").is_file());
    let p = &list.packages[0];
    assert_eq!((p.enabled, p.active, p.code, p.position), (true, true, true, 0));
    assert_eq!(list.report.as_ref().unwrap().installed.as_ref().unwrap().previous, None);
    assert_eq!(load_order_lines(&game), ["alpha/alpha.dll"]);
    let text = game.read("System/mods/load-order.txt").unwrap();
    assert!(text.starts_with("# Written by the T3SDK launcher"));

    let state = state::load(&game.layout.state());
    assert_eq!(state.order, ["alpha"]);
    assert_eq!(state.enabled, ["alpha"]);
    assert_eq!(state.profiles["Default"].enabled, ["alpha"]);
    let leftovers: Vec<_> = std::fs::read_dir(&game.layout.dir)
        .unwrap()
        .flatten()
        .filter(|e| e.file_name().to_string_lossy().starts_with('.'))
        .collect();
    assert!(leftovers.is_empty(), "no temporary folders left");
}

#[test]
fn load_order_lists_active_code_mods_in_order() {
    let game = Game::new();
    game.install("lib", "0.3.1", &code("lib"), &[("lib.dll", "MZ")]).unwrap();
    game.install("tex", "1.0.0", "", &[("files/Content/T3/a.txt", "a")]).unwrap();
    game.install(
        "user",
        "1.0.0",
        &format!(r#"{}, "requires": {{"lib": "^0.3.0"}}"#, code("user")),
        &[("User.DLL", "MZ")],
    )
    .unwrap();
    assert_eq!(load_order_lines(&game), ["lib/lib.dll", "user/User.DLL"]);

    set_order(&game.layout, SDK, vec!["user".into(), "tex".into(), "lib".into()]).unwrap();
    assert_eq!(load_order_lines(&game), ["user/User.DLL", "lib/lib.dll"], "a warning does not switch it off");
    let list = game.list();
    let warning = list.issues.iter().find(|i| i.severity == checks::Severity::Warning).unwrap();
    assert_eq!(warning.id.as_deref(), Some("user"));
    assert_eq!(
        warning.fix.as_ref().unwrap().action,
        checks::FixAction::MoveBefore { id: "lib".into(), before: "user".into() }
    );

    let list = set_enabled(&game.layout, SDK, "lib", false).unwrap();
    assert_eq!(load_order_lines(&game), Vec::<String>::new(), "a missing requirement keeps the mod off");
    let user = list.packages.iter().find(|p| p.id == "user").unwrap();
    assert!(user.enabled && !user.active);
    let error = list.issues.iter().find(|i| i.severity == checks::Severity::Error).unwrap();
    assert!(error.message.contains("disabled"));
    assert_eq!(error.fix.as_ref().unwrap().action, checks::FixAction::Enable { id: "lib".into() });
}

#[test]
fn upgrade_and_downgrade_keep_position_and_state() {
    let game = Game::new();
    game.install("a", "1.0.0", "", &[("files/Content/a.txt", "a1"), ("files/Content/old.txt", "old")]).unwrap();
    game.install("b", "1.0.0", "", &[("files/Content/b.txt", "b")]).unwrap();
    set_order(&game.layout, SDK, vec!["b".into(), "a".into()]).unwrap();
    set_enabled(&game.layout, SDK, "b", false).unwrap();

    let list = game.install("b", "2.0.0", "", &[("files/Content/b.txt", "b2")]).unwrap();
    assert_eq!(ids(&list), ["b", "a"]);
    assert!(!list.packages[0].enabled, "still disabled");
    let installed = list.report.unwrap().installed.unwrap();
    assert_eq!(installed.previous.unwrap().to_string(), "1.0.0");

    let list = game.install("a", "0.9.0", "", &[("files/Content/a.txt", "a0")]).unwrap();
    assert_eq!(ids(&list), ["b", "a"]);
    assert!(list.packages[1].enabled);
    assert_eq!(list.packages[1].version.as_ref().unwrap().to_string(), "0.9.0");
    assert_eq!(game.read("Content/a.txt").as_deref(), Some("a0"), "the new version's file is placed");
    assert_eq!(game.read("Content/old.txt"), None, "a file the new version dropped is removed");
}

#[test]
fn overlay_replaces_restores_and_lets_the_later_mod_win() {
    let game = Game::new();
    game.write("Content/T3/Bitmaps/x.dds", "original");
    game.install("one", "1.0.0", "", &[("files/Content/T3/Bitmaps/x.dds", "one"), ("files/Content/new.txt", "new")])
        .unwrap();
    // First replacement: the original moves to originals/, the new path is only recorded.
    assert_eq!(game.read("Content/T3/Bitmaps/x.dds").as_deref(), Some("one"));
    assert_eq!(game.read("System/mods/originals/Content/T3/Bitmaps/x.dds").as_deref(), Some("original"));
    let overlay = game.overlay();
    let record = &overlay.files["Content/T3/Bitmaps/x.dds"];
    assert_eq!((record.owner.as_str(), record.original), ("one", true));
    assert_eq!(record.sha256, files::sha256_file(&game.path("Content/T3/Bitmaps/x.dds")).unwrap());
    assert!(!overlay.files["Content/new.txt"].original);

    // A later mod wins; the original stays saved once.
    let list = game.install("two", "1.0.0", "", &[("files/content/t3/bitmaps/X.DDS", "two")]).unwrap();
    assert_eq!(game.read("Content/T3/Bitmaps/x.dds").as_deref(), Some("two"));
    assert_eq!(game.read("System/mods/originals/Content/T3/Bitmaps/x.dds").as_deref(), Some("original"));
    assert_eq!(game.overlay().files["Content/T3/Bitmaps/x.dds"].owner, "two");
    let info = list.issues.iter().find(|i| i.severity == checks::Severity::Info).unwrap();
    assert_eq!(info.id.as_deref(), Some("two"));

    // Reordered: the other mod wins.
    set_order(&game.layout, SDK, vec!["two".into(), "one".into()]).unwrap();
    assert_eq!(game.read("Content/T3/Bitmaps/x.dds").as_deref(), Some("one"));

    // Disabled: the originals come back and added files go.
    set_enabled(&game.layout, SDK, "one", false).unwrap();
    assert_eq!(game.read("Content/T3/Bitmaps/x.dds").as_deref(), Some("two"));
    assert_eq!(game.read("Content/new.txt"), None);
    set_enabled(&game.layout, SDK, "two", false).unwrap();
    assert_eq!(game.read("Content/T3/Bitmaps/x.dds").as_deref(), Some("original"));
    assert!(!game.path("System/mods/originals/Content").exists(), "emptied folders in originals/ are removed");
    assert!(game.overlay().files.is_empty());
}

#[test]
fn a_file_changed_outside_the_launcher_is_left_alone() {
    let game = Game::new();
    game.write("Content/a.txt", "original");
    game.install("m", "1.0.0", "", &[("files/Content/a.txt", "mod"), ("files/Content/b.txt", "b")]).unwrap();
    game.write("Content/a.txt", "edited by hand");
    std::fs::remove_file(game.path("Content/b.txt")).unwrap();

    let list = set_enabled(&game.layout, SDK, "m", false).unwrap();
    let changed = &list.report.unwrap().changed;
    assert_eq!(changed.len(), 2, "{changed:?}");
    assert_eq!(game.read("Content/a.txt").as_deref(), Some("edited by hand"));
    assert!(game.overlay().files.is_empty(), "their records are dropped");
}

#[test]
fn remove_puts_the_content_back_first() {
    let game = Game::new();
    game.write("Content/a.txt", "original");
    game.install("m", "1.0.0", &code("m"), &[("m.dll", "MZ"), ("files/Content/a.txt", "mod")]).unwrap();
    game.install("other", "1.0.0", "", &[("files/Content/o.txt", "o")]).unwrap();
    mod_profile_save(&game, "Second");

    let list = remove(&game.layout, SDK, "m").unwrap();
    assert_eq!(list.report.as_ref().unwrap().removed.as_deref(), Some("m"));
    assert_eq!(ids(&list), ["other"]);
    assert!(!game.path("System/mods/m").exists());
    assert_eq!(game.read("Content/a.txt").as_deref(), Some("original"));
    assert_eq!(load_order_lines(&game), Vec::<String>::new());
    let state = state::load(&game.layout.state());
    assert!(state.profiles.values().all(|p| !p.order.contains(&"m".to_string())), "gone from every profile");
    assert!(remove(&game.layout, SDK, "m").is_err());
}

fn mod_profile_save(game: &Game, name: &str) {
    profile(&game.layout, SDK, ProfileAction::SaveAs { name: name.into() }).unwrap();
}

#[test]
fn profiles_switch_and_apply() {
    let game = Game::new();
    game.write("Content/a.txt", "original");
    game.install("a", "1.0.0", &code("a"), &[("a.dll", "MZ")]).unwrap();
    game.install("b", "1.0.0", "", &[("files/Content/a.txt", "b")]).unwrap();
    mod_profile_save(&game, "Vanilla");
    set_enabled(&game.layout, SDK, "a", false).unwrap();
    let list = set_enabled(&game.layout, SDK, "b", false).unwrap();
    assert_eq!(list.profile, "Vanilla");
    assert_eq!(list.profiles, ["Default", "Vanilla"]);
    assert_eq!(game.read("Content/a.txt").as_deref(), Some("original"));

    let list = profile(&game.layout, SDK, ProfileAction::Switch { name: "Default".into() }).unwrap();
    assert_eq!(list.profile, "Default");
    assert!(list.packages.iter().all(|p| p.enabled));
    assert_eq!(load_order_lines(&game), ["a/a.dll"]);
    assert_eq!(game.read("Content/a.txt").as_deref(), Some("b"));

    let list =
        profile(&game.layout, SDK, ProfileAction::Rename { from: "Vanilla".into(), to: "Plain".into() }).unwrap();
    assert_eq!(list.profiles, ["Default", "Plain"]);
    assert!(profile(&game.layout, SDK, ProfileAction::Delete { name: "Default".into() }).is_err());
    let list = profile(&game.layout, SDK, ProfileAction::Delete { name: "Plain".into() }).unwrap();
    assert_eq!(list.profiles, ["Default"]);
}

#[test]
fn conflicts_keep_both_off() {
    let game = Game::new();
    game.install("old", "1.0.0", &code("old"), &[("old.dll", "MZ")]).unwrap();
    let list = game
        .install("new", "1.0.0", &format!(r#"{}, "conflicts": ["old"]"#, code("new")), &[("new.dll", "MZ")])
        .unwrap();
    assert!(list.packages.iter().all(|p| p.enabled && !p.active));
    assert_eq!(list.issues.iter().filter(|i| i.severity == checks::Severity::Error).count(), 2);
    assert_eq!(load_order_lines(&game), Vec::<String>::new());
    set_enabled(&game.layout, SDK, "old", false).unwrap();
    assert_eq!(load_order_lines(&game), ["new/new.dll"]);
}

#[test]
fn sdk_warnings() {
    let game = Game::new();
    game.install("m", "1.0.0", r#", "entry": "m.dll", "api": 2"#, &[("m.dll", "MZ")]).unwrap();
    let list = game.list();
    assert!(list.issues.iter().any(|i| i.severity == checks::Severity::Warning && i.message.contains("API version 2")));
    let list = list_with(&game, SdkInfo { installed: false, api: 1 });
    assert!(list.issues.iter().any(|i| i.message.contains("not installed")));
    assert!(list.packages[0].active, "warnings do not switch a mod off");
}

fn list_with(game: &Game, sdk: SdkInfo) -> ModList {
    list(&game.layout, sdk)
}

#[test]
fn texture_packs_are_reported_until_applied() {
    let game = Game::new();
    let list = game.install("hd", "1.0.0", "", &[("textures/stone.dds", "DDS ")]).unwrap();
    assert_eq!(list.textures, TextureStatus { needed: true, mods: vec!["hd".into()], bundles: vec![] });
    let packs = texture_packs(game.root.path(), &list.textures.mods).unwrap();
    assert_eq!(packs, [game.path("System/mods/hd")], "t3texpack.py takes the installed mod folder");
    record_textures(game.root.path(), texture_fingerprint(game.root.path(), &list.textures.mods)).unwrap();
    assert!(!game.list().textures.needed);
    assert_eq!(state::load(&game.layout.state()).textures, ["hd@1.0.0"]);

    let list = game.install("hd", "1.1.0", "", &[("textures/stone.dds", "DDS 2")]).unwrap();
    assert!(list.textures.needed, "a new version is applied again");
    record_textures(game.root.path(), texture_fingerprint(game.root.path(), &list.textures.mods)).unwrap();

    let list = set_enabled(&game.layout, SDK, "hd", false).unwrap();
    assert_eq!(list.textures, TextureStatus { needed: true, mods: vec![], bundles: vec![] }, "apply without packs");
    assert!(texture_packs(game.root.path(), &["../x".into()]).is_err());
    game.install("plain", "1.0.0", "", &[("files/a.txt", "a")]).unwrap();
    assert!(texture_packs(game.root.path(), &["plain".into()]).is_err());
}

#[test]
fn bundles_wait_for_the_texture_restore() {
    let game = Game::new();
    game.write("Content/T3/Maps/Inn.ibt", "vanilla bundle");
    let list = game
        .install("map", "1.0.0", "", &[("files/Content/T3/Maps/Inn.ibt", "mod bundle"), ("files/Content/a.txt", "a")])
        .unwrap();
    assert_eq!(list.textures.bundles, ["Content/T3/Maps/Inn.ibt"]);
    assert_eq!(game.read("Content/T3/Maps/Inn.ibt").as_deref(), Some("vanilla bundle"), "not placed yet");
    assert_eq!(game.read("Content/a.txt").as_deref(), Some("a"), "other content is placed at once");

    // What the textureRestore task does once t3texpack.py restore succeeded.
    place_bundles(game.root.path()).unwrap();
    assert_eq!(game.read("Content/T3/Maps/Inn.ibt").as_deref(), Some("mod bundle"));
    assert_eq!(game.read("System/mods/originals/Content/T3/Maps/Inn.ibt").as_deref(), Some("vanilla bundle"));
    assert!(game.list().textures.bundles.is_empty());

    // A texture pack patches the placed bundle: that is not "changed outside the launcher".
    game.write("Content/T3/Maps/Inn.ibt", "mod bundle, patched");
    let list = sync_again(&game);
    assert!(list.report.unwrap().changed.is_empty());
    assert!(game.overlay().files.contains_key("Content/T3/Maps/Inn.ibt"));

    // Removing waits for the restore too, then puts the original back.
    let list = remove(&game.layout, SDK, "map").unwrap();
    assert!(!game.path("System/mods/map").exists());
    assert_eq!(list.textures.bundles, ["Content/T3/Maps/Inn.ibt"]);
    game.write("Content/T3/Maps/Inn.ibt", "mod bundle"); // t3texpack.py restore
    place_bundles(game.root.path()).unwrap();
    assert_eq!(game.read("Content/T3/Maps/Inn.ibt").as_deref(), Some("vanilla bundle"));
    assert!(game.overlay().files.is_empty());
}

fn sync_again(game: &Game) -> ModList {
    change(&game.layout, SDK, |_| Ok(SyncReport::default())).unwrap()
}

#[test]
fn loose_dlls_are_listed_next_to_packages() {
    let game = Game::new();
    game.write("System/mods/hello.dll", "MZ");
    game.install("m", "1.0.0", &code("m"), &[("m.dll", "MZ")]).unwrap();
    let list = game.list();
    assert_eq!(list.loose.len(), 1);
    assert_eq!(list.loose[0].name, "hello");
    let cfg = Config { game_dir: Some(game.root.path().to_path_buf()), ..Config::default() };
    assert_eq!(counts(&cfg), (2, 0));
    layout::set_loose_enabled(&game.layout, "hello", false).unwrap();
    assert_eq!(counts(&cfg), (1, 1));
}

#[test]
fn unsafe_or_empty_packages_are_refused() {
    let game = Game::new();
    let m = manifest("m", "1.0.0", "");
    let cases: &[(&str, &[(&str, &str)])] = &[
        ("zip slip", &[("../evil.txt", "x")]),
        ("deep zip slip", &[("files/../../evil.txt", "x")]),
        ("absolute", &[("/etc/evil", "x")]),
        ("drive letter", &[("C:/evil.txt", "x")]),
        ("backslash", &[("files\\..\\evil.txt", "x")]),
        ("empty segment", &[("files//x.txt", "x")]),
        ("System/", &[("files/System/dinput8.dll", "MZ")]),
        ("system/ in any case", &[("files/system/x.ini", "x")]),
        ("nothing to install", &[("readme.txt", "x")]),
        ("duplicate", &[("files/a.txt", "x"), ("files/A.TXT", "y")]),
        ("a file and a folder", &[("files/a", "x"), ("files/A/b.txt", "y")]),
        ("device name", &[("files/Content/aux.dds", "x")]),
        ("trailing dot", &[("files/Content./a.dds", "x")]),
        ("texture folder", &[("textures/sub/a.dds", "x")]),
        ("texture not dds", &[("textures/a.png", "x")]),
    ];
    for (what, entries) in cases {
        let pkg = game.pack("bad.t3mod", &m, entries);
        assert!(install(&game.layout, SDK, &pkg, None).is_err(), "{what} was accepted");
    }
    let pkg = game.pack("bad.t3mod", &manifest("m", "1.0.0", &code("m")), &[("files/x.txt", "x")]);
    assert!(install(&game.layout, SDK, &pkg, None).unwrap_err().contains("no such file"));
    let pkg = game.pack("bad.t3mod", r#"{"format": 1, "id": "Bad"}"#, &[("files/x.txt", "x")]);
    assert!(install(&game.layout, SDK, &pkg, None).unwrap_err().contains("mod.json"));
    let pkg = game.pack("bad.t3mod", &manifest("disabled", "1.0.0", ""), &[("files/x.txt", "x")]);
    assert!(install(&game.layout, SDK, &pkg, None).unwrap_err().contains("id"), "reserved id");
    std::fs::write(game.root.path().join("junk.t3mod"), "not a zip").unwrap();
    assert!(install(&game.layout, SDK, &game.root.path().join("junk.t3mod"), None).is_err());

    assert!(!game.root.path().join("evil.txt").exists() && !game.path("System/evil.txt").exists());
    assert!(!game.path("System/mods/m").exists());
    assert!(std::fs::read_dir(&game.layout.dir).map_or(true, |mut d| d.next().is_none()), "nothing left behind");
}

#[test]
fn directory_entries_are_ignored() {
    let game = Game::new();
    let path = game.root.path().join("dirs.t3mod");
    let mut zip = zip::ZipWriter::new(std::fs::File::create(&path).unwrap());
    let options = SimpleFileOptions::default();
    zip.add_directory("files/", options).unwrap();
    zip.add_directory("files/Content/Empty/", options).unwrap();
    zip.start_file("files/Content/a.txt", options).unwrap();
    zip.write_all(b"a").unwrap();
    zip.start_file("mod.json", options).unwrap();
    zip.write_all(manifest("dirs", "1.0.0", "").as_bytes()).unwrap();
    zip.finish().unwrap();
    install(&game.layout, SDK, &path, None).unwrap();
    assert_eq!(game.read("Content/a.txt").as_deref(), Some("a"));
    assert!(!game.path("System/mods/dirs/files/Content/Empty").exists());
}

#[test]
fn index_downloads_must_match() {
    let game = Game::new();
    let pkg = game.pack("m.t3mod", &manifest("m", "1.0.0", ""), &[("files/a.txt", "a")]);
    let wrong = Version::parse("1.0.1").unwrap();
    assert!(install(&game.layout, SDK, &pkg, Some(("m", &wrong))).unwrap_err().contains("not m 1.0.1"));
    assert!(install(&game.layout, SDK, &pkg, Some(("x", &Version::parse("1.0.0").unwrap()))).is_err());
    assert!(install(&game.layout, SDK, &pkg, Some(("m", &Version::parse("1.0.0").unwrap()))).is_ok());
}

#[test]
fn index_view_marks_compatibility_and_updates() {
    let game = Game::new();
    game.install("lib", "1.0.0", "", &[("files/l.txt", "l")]).unwrap();
    game.install("old", "1.0.0", "", &[("files/o.txt", "o")]).unwrap();
    let sha = "0".repeat(64);
    let v = |v: &str, extra: &str| {
        format!(r#"{{"version": "{v}", "url": "https://example.org/{v}.t3mod", "sha256": "{sha}", "size": 5{extra}}}"#)
    };
    let doc = format!(
        r#"{{"format": 1, "mods": [
            {{"id": "lib", "name": "Lib", "versions": [{}, {}, {}]}},
            {{"id": "new", "name": "New", "versions": [{}]}},
            {{"id": "big", "name": "Big", "versions": [{}]}}
        ]}}"#,
        v("2.0.0-beta.1", ""),
        v("1.1.0", ""),
        v("1.0.0", ""),
        v("1.0.0", r#", "requires": {"lib": ">=1.1.0"}, "conflicts": ["old"]"#),
        v("1.0.0", r#", "api": 9"#),
    );
    let index = index::parse(&doc).unwrap();
    let mods = open(&game.layout, SDK);
    let view = index::view("https://example.org/index.json", &index, &mods.packages, &mods.enabled(), SDK);
    assert_eq!(view.updates.len(), 1);
    assert_eq!((view.updates[0].id.as_str(), view.updates[0].latest.to_string()), ("lib", "1.1.0".into()));
    let new = view.mods.iter().find(|m| m.id == "new").unwrap();
    assert!(!new.versions[0].compatible, "conflicts with an enabled mod");
    assert!(new.versions[0].notes.iter().any(|n| n.message.contains("the index has 1.1.0")));
    let big = view.mods.iter().find(|m| m.id == "big").unwrap();
    assert!(!big.versions[0].compatible, "needs a newer SDK");
    assert_eq!(big.recommended.as_ref().map(ToString::to_string).as_deref(), Some("1.0.0"));
}

#[test]
fn broken_package_folders_are_listed_but_stay_off() {
    let game = Game::new();
    game.write("System/mods/broken/mod.json", "{ not json");
    game.write("System/mods/notes/readme.txt", "not a package");
    let mut st = state::State::default();
    st.enabled.push("broken".into());
    st.order.push("broken".into());
    state::save(&game.layout.state(), &st).unwrap();
    let list = game.list();
    assert_eq!(ids(&list), ["broken"]);
    assert!(list.packages[0].error.is_some() && !list.packages[0].active);
    assert!(list.issues.iter().any(|i| i.severity == checks::Severity::Error));
}
