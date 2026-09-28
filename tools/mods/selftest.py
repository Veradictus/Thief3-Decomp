#!/usr/bin/env python3
"""Self-test for the mod package tools (tools/t3mod.py, tools/modindex.py,
tools/mods/t3modlib.py) and the mod template, on synthetic data only.

Runs the shared fixtures (valid manifests pass, invalid ones fail on the
field their "_expect" names, ranges.json exactly), packs and validates mod
folders in a temporary folder (junk skipped, deterministic zips, round trips,
zip-slip and files/System/ refused), builds and checks a mod index, verifies
packages over a local HTTP server and file:// URLs (and --changed-only against
a scratch git repository when git is installed), and checks the template's
mod.json.in and, when CMake is installed, its packaging script.
Run: python tools/mods/selftest.py
"""

from __future__ import annotations

import contextlib
import functools
import hashlib
import http.server
import io
import json
import os
import re
import shutil
import stat
import subprocess
import sys
import tempfile
import threading
import zipfile
from pathlib import Path
from typing import Any, Dict, List, Optional, Tuple

HERE = Path(__file__).resolve().parent
TOOLS = HERE.parent
ROOT = TOOLS.parent
FIXTURES = HERE / "fixtures"
TEMPLATE = ROOT / "templates" / "mod"
sys.path.insert(0, str(HERE))
sys.path.append(str(TOOLS))
import t3modlib as L  # noqa: E402
import modindex  # noqa: E402
import t3mod  # noqa: E402

CODE = json.loads((FIXTURES / "valid" / "code.json").read_text(encoding="utf-8"))
CONTENT = json.loads((FIXTURES / "valid" / "content.json").read_text(encoding="utf-8"))


def run(module: Any, *argv: Any) -> Tuple[int, str]:
    """Run a tool's main() in-process; (exit status, stdout and exit message)."""
    out = io.StringIO()
    with contextlib.redirect_stdout(out):
        try:
            code = module.main([str(a) for a in argv])
        except SystemExit as e:
            code = e.code if isinstance(e.code, int) else 1
            if not isinstance(e.code, int):
                out.write(str(e.code))
    return code, out.getvalue()


def write_json(path: Path, data: Any) -> Path:
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(json.dumps(data, indent=2) + "\n", encoding="utf-8")
    return path


def make_mod(folder: Path, manifest: Dict[str, Any], files: Dict[str, bytes]) -> Path:
    write_json(folder / "mod.json", manifest)
    for name, data in files.items():
        (folder / name).parent.mkdir(parents=True, exist_ok=True)
        (folder / name).write_bytes(data)
    return folder


def make_zip(path: Path, entries: List[Tuple[str, bytes]], tweak: Optional[Dict[str, Any]] = None) -> Path:
    """A zip whose names are written exactly as given (zipfile's own clean-up
    bypassed), so unsafe names can be tested. `tweak` sets ZipInfo fields per
    name; "flag_bits" is patched into the central directory afterwards, since
    zipfile resets it while writing."""
    flags: Dict[bytes, int] = {}
    with zipfile.ZipFile(path, "w", zipfile.ZIP_DEFLATED) as z:
        for name, data in entries:
            info = zipfile.ZipInfo("placeholder", date_time=L.PACKAGE_TIME)
            info.filename = name
            info.compress_type = zipfile.ZIP_DEFLATED
            for key, value in (tweak or {}).get(name, {}).items():
                if key == "flag_bits":
                    flags[name.encode()] = value
                else:
                    setattr(info, key, value)
            z.writestr(info, data)
    if flags:
        raw = bytearray(path.read_bytes())
        pos = raw.find(b"PK\x01\x02")
        while pos >= 0:  # central directory records: flags at +8, name length at +28, name at +46
            length = int.from_bytes(raw[pos + 28:pos + 30], "little")
            raw[pos + 8] |= flags.get(bytes(raw[pos + 46:pos + 46 + length]), 0)
            pos = raw.find(b"PK\x01\x02", pos + 46 + length)
        path.write_bytes(bytes(raw))
    return path


def error_places(package: L.Package) -> set:
    return {p.where for p in package.errors}


DLL = b"MZ" + bytes(62)  # stands in for a DLL: the tools only look at names and sizes
DDS = b"DDS " + bytes(124)


# --- fixtures -----------------------------------------------------------------------------

def test_fixtures() -> None:
    valid = sorted((FIXTURES / "valid").glob("*.json"))
    invalid = sorted((FIXTURES / "invalid").glob("*.json"))
    assert valid and invalid
    for path in valid:
        manifest, problems = L.load_manifest_file(path)
        assert not problems and manifest is not None, (path.name, [str(p) for p in problems])
    for path in invalid:
        expect = json.loads(path.read_text(encoding="utf-8"))["_expect"]
        _, problems = L.load_manifest_file(path)
        places = {p.where for p in L.errors(problems)}
        assert places == {expect}, (path.name, expect, [str(p) for p in problems])

    # Every valid manifest also passes as a package, with its entry DLL or some content.
    with tempfile.TemporaryDirectory() as tmp:
        for path in valid:
            manifest = json.loads(path.read_text(encoding="utf-8"))
            files = {manifest["entry"]: DLL} if "entry" in manifest else {"files/Content/T3/Bitmaps/x.dds": DDS}
            package = L.read_folder(make_mod(Path(tmp) / path.stem, manifest, files))
            assert not package.problems, (path.name, [str(p) for p in package.problems])

    code, out = run(t3mod, "validate", FIXTURES / "valid" / "code.json")
    assert code == 0 and "better-lockpicks 1.2.0: manifest ok" in out, out
    code, out = run(t3mod, "validate", FIXTURES / "invalid" / "tags-unknown.json")
    assert code == 1 and "error:" in out and "tags: unknown" in out, out
    print(f"fixtures: {len(valid)} valid and {len(invalid)} invalid manifests: ok")


def test_ranges() -> None:
    triples = json.loads((FIXTURES / "ranges.json").read_text(encoding="utf-8"))
    for rng, version, expected in triples:
        try:
            got: Optional[bool] = L.satisfies(rng, version)
        except ValueError:
            got = None
        assert got == expected, (rng, version, expected, got)
    # Precedence, in the order of the semver specification's example.
    ordered = ["1.0.0-alpha", "1.0.0-alpha.1", "1.0.0-alpha.beta", "1.0.0-beta", "1.0.0-beta.2", "1.0.0-beta.11",
               "1.0.0-rc.1", "1.0.0", "1.0.1", "1.1.0", "2.0.0"]
    keys = [L.parse_version(v).key for v in ordered]
    assert keys == sorted(keys) and len(set(keys)) == len(keys)
    assert L.parse_version("1.0.0+a").key == L.parse_version("1.0.0+b").key
    for bad in ("1.0.0-01", "1.0.0-", "1.0.0+", "v1.0.0", " 1.0.0", "1.0.0\n", "18446744073709551616.0.0"):
        try:
            L.parse_version(bad)
        except ValueError:
            continue
        raise AssertionError(f"{bad!r} parsed as a version")
    print(f"version ranges: {len(triples)} cases: ok")


# --- pack and validate --------------------------------------------------------------------

def test_pack() -> None:
    with tempfile.TemporaryDirectory() as tmp:
        tmp = Path(tmp)
        src = make_mod(tmp / "src", CODE, {
            "better-lockpicks.dll": DLL,
            "better-lockpicks.pdb": b"pdb",
            "better-lockpicks.ini": b"[Lockpicks]\nFast=1\n",
            "files/Content/T3/Bitmaps/loading.dds": DDS,
            "textures/stone_wall01.dds": DDS,
            # junk, skipped
            "Thumbs.db": b"x", ".DS_Store": b"x", "desktop.ini": b"x", ".git/config": b"x", "files/.gitkeep": b"",
            "better-lockpicks-1.1.0.t3mod": b"an older package", "dist/x.t3mod": b"another",
        })
        dist = tmp / "dist"
        dist.mkdir()
        code, out = run(t3mod, "pack", src, "-o", dist)
        assert code == 0, out
        package = dist / "better-lockpicks-1.2.0.t3mod"
        with zipfile.ZipFile(package) as z:
            infos = z.infolist()
        expected = ["better-lockpicks.dll", "better-lockpicks.ini", "files/Content/T3/Bitmaps/loading.dds",
                    "mod.json", "textures/stone_wall01.dds"]
        assert [i.filename for i in infos] == expected, [i.filename for i in infos]
        for i in infos:
            assert i.date_time == L.PACKAGE_TIME and i.compress_type == zipfile.ZIP_DEFLATED, i
            assert i.external_attr == L.PACKAGE_ATTR and i.create_system == 3, i
        assert f"sha256 {L.sha256_file(package)}" in out, out

        # Same files, other timestamps: the same bytes.
        for path in src.rglob("*"):
            os.utime(path, (1_000_000_000, 1_000_000_000))
        again = tmp / "again.t3mod"
        assert run(t3mod, "pack", src, "-o", again)[0] == 0
        assert again.read_bytes() == package.read_bytes()

        # --with-pdb keeps the PDB.
        with_pdb = tmp / "with-pdb.t3mod"
        assert run(t3mod, "pack", src, "-o", with_pdb, "--with-pdb")[0] == 0
        with zipfile.ZipFile(with_pdb) as z:
            assert "better-lockpicks.pdb" in z.namelist()

        # Round trip: unpack, validate the folder, pack it again.
        unpacked = tmp / "unpacked"
        with zipfile.ZipFile(package) as z:
            z.extractall(unpacked)
        code, out = run(t3mod, "validate", unpacked)
        assert code == 0 and "5 files" in out, out
        assert run(t3mod, "pack", unpacked, "-o", tmp / "round.t3mod")[0] == 0
        assert (tmp / "round.t3mod").read_bytes() == package.read_bytes()

        code, out = run(t3mod, "info", package)
        assert code == 0 and L.sha256_file(package) in out and '"id": "better-lockpicks"' in out, out
        assert "files/Content/T3/Bitmaps/loading.dds" in out and "Thumbs.db" not in out, out

        # The scripts run as programs too.
        result = subprocess.run([sys.executable, str(TOOLS / "t3mod.py"), "validate", str(package)],
                                capture_output=True, text=True)
        assert result.returncode == 0 and "ok" in result.stdout, result.stdout + result.stderr

        # Warnings do not stop a package.
        make_mod(src, CODE, {"files/Content/tool.exe": b"MZ", "files/notes.txt": b"x", "files/Content/empty.txt": b""})
        package = L.read_folder(src)
        assert not package.errors, [str(p) for p in package.errors]
        warned = {p.where for p in package.warnings}
        assert {"files/Content/tool.exe", "files/notes.txt", "files/Content/empty.txt"} <= warned, warned
    print("pack: sorted, junk skipped, fixed times, deterministic, round trip, info: ok")


def test_folder_refusals() -> None:
    cases: List[Tuple[str, Dict[str, Any], Dict[str, bytes], str]] = [
        ("System/", CONTENT, {"files/System/evil.dll": DLL}, "files/System/evil.dll"),
        ("system/ in lower case", CONTENT, {"files/system/T3SDK.ini": b"x"}, "files/system/T3SDK.ini"),
        ("not .dds in textures/", CONTENT, {"textures/readme.txt": b"x"}, "textures/readme.txt"),
        ("folder in textures/", CONTENT, {"textures/sub/a.dds": DDS}, "textures/sub/a.dds"),
        ("nothing to install", CONTENT, {"readme.txt": b"x"}, "package"),
        ("entry missing", CODE, {"files/Content/a.dds": DDS}, "entry"),
    ]
    if os.name != "nt":  # names Windows cannot even create
        cases += [
            ("device name", CONTENT, {"files/Content/aux.dds": DDS}, "files/Content/aux.dds"),
            ("trailing dot", CONTENT, {"files/Content/a.dds.": DDS}, "files/Content/a.dds."),
            ("colon", CONTENT, {"files/Content/a:b.dds": DDS}, "files/Content/a:b.dds"),
            ("same name in another case", CONTENT, {"files/A.dds": DDS, "files/a.dds": DDS}, "files/a.dds"),
        ]
    with tempfile.TemporaryDirectory() as tmp:
        tmp = Path(tmp)
        for i, (what, manifest, files, where) in enumerate(cases):
            folder = make_mod(tmp / f"case{i}", manifest, files)
            package = L.read_folder(folder)
            assert where in error_places(package), (what, [str(p) for p in package.problems])
            out_file = tmp / f"case{i}.t3mod"
            code, out = run(t3mod, "pack", folder, "-o", out_file)
            assert code == 1 and "not packed" in out and not out_file.exists(), (what, out)

        bom = tmp / "bom"
        bom.mkdir()
        (bom / "mod.json").write_bytes(b"\xef\xbb\xbf" + json.dumps(CONTENT).encode())
        (bom / "files").mkdir()
        (bom / "files" / "a.txt").write_bytes(b"x")
        assert "mod.json" in error_places(L.read_folder(bom))
        (bom / "mod.json").write_bytes(b'{"format": 1, "format": 1}')
        assert "mod.json" in error_places(L.read_folder(bom))

        nested = tmp / "nested"
        make_mod(nested / "inner", CONTENT, {"files/a.txt": b"x"})
        problems = L.read_folder(nested).errors
        assert any(p.where == "mod.json" and "inner/mod.json" in p.message for p in problems), problems

        if hasattr(os, "symlink"):
            linked = make_mod(tmp / "linked", CONTENT, {"files/a.txt": b"x"})
            try:
                os.symlink(linked / "mod.json", linked / "files" / "link.txt")
            except OSError:
                pass  # no symlink rights (Windows without developer mode)
            else:
                assert "files/link.txt" in error_places(L.read_folder(linked))
    print(f"folder refusals: {len(cases) + 3} cases: ok")


def test_zip_refusals() -> None:
    base = [("mod.json", json.dumps(CONTENT).encode()), ("files/Content/T3/Bitmaps/ok.dds", DDS)]
    cases = [
        ("../evil.dll", None), ("files/../../evil.dll", None), ("/abs.dll", None), ("C:/Windows/evil.dll", None),
        ("files\\..\\..\\evil.dll", None), ("files//Content/x.dds", None), ("files/./x.dds", None),
        ("files/Content/x.dds:stream", None), ("files/Content/con.dds", None), ("files/Content/x.dds ", None),
        ("files/System/evil.dll", None), ("textures/evil.exe", None),
        ("files/link.dds", {"create_system": 3, "external_attr": (stat.S_IFLNK | 0o777) << 16}),
        ("files/secret.dds", {"flag_bits": 0x1}),
        ("files/bzip.dds", {"compress_type": zipfile.ZIP_BZIP2}),
        ("../", None),
    ]
    with tempfile.TemporaryDirectory() as tmp:
        tmp = Path(tmp)
        ok = L.read_zip(make_zip(tmp / "ok.t3mod", base + [("files/", b""), ("files/Content/", b"")]))
        assert not ok.problems, [str(p) for p in ok.problems]  # directory entries are fine
        for i, (name, tweak) in enumerate(cases):
            path = make_zip(tmp / f"case{i}.t3mod", base + [(name, DDS)], {name: tweak} if tweak else None)
            package = L.read_zip(path)
            assert name in error_places(package), (name, [str(p) for p in package.problems])
            code, out = run(t3mod, "validate", path)
            assert code == 1 and "error:" in out, (name, out)
        dup = L.read_zip(make_zip(tmp / "dup.t3mod", base + [("FILES/Content/T3/Bitmaps/OK.dds", DDS)]))
        assert "FILES/Content/T3/Bitmaps/OK.dds" in error_places(dup), dup.problems
        clash = L.read_zip(make_zip(tmp / "clash.t3mod", base + [("files/Content", DDS)]))
        assert "files/Content" in error_places(clash), clash.problems
        folder = L.read_zip(make_zip(tmp / "folder.t3mod", [("my-mod/" + n, d) for n, d in base]))
        assert any("my-mod/mod.json" in p.message for p in folder.errors), folder.problems
        (tmp / "junk.t3mod").write_bytes(b"not a zip")
        assert L.read_zip(tmp / "junk.t3mod").errors
        damaged = make_zip(tmp / "damaged.t3mod", base + [("files/data.bin", b"A" * 100)],
                           {"files/data.bin": {"compress_type": zipfile.ZIP_STORED}})
        damaged.write_bytes(damaged.read_bytes().replace(b"A" * 100, b"B" * 100))
        assert "files/data.bin" in error_places(L.read_zip(damaged))  # the CRC no longer matches
    print(f"zip refusals: {len(cases) + 5} cases, directory entries allowed: ok")


# --- the mod index ------------------------------------------------------------------------

def pack(folder: Path, out: Path) -> Path:
    code, text = run(t3mod, "pack", folder, "-o", out)
    assert code == 0, text
    return out


def versioned(manifest: Dict[str, Any], version: str, **changes: Any) -> Dict[str, Any]:
    return {**manifest, "version": version, **changes}


def test_index() -> None:
    with tempfile.TemporaryDirectory() as tmp:
        tmp = Path(tmp)
        index = tmp / "mods"
        url = "https://mods.test/better-lockpicks-{}.t3mod"
        packages = {}
        for version, name in (("1.2.0", "Better Lockpicks"), ("1.3.0", "Better Lockpicks 2"),
                              ("1.1.0", "Old Lockpicks")):
            folder = make_mod(tmp / version, versioned(CODE, version, name=name), {"better-lockpicks.dll": DLL})
            packages[version] = pack(folder, tmp / f"better-lockpicks-{version}.t3mod")

        code, out = run(modindex, "add", packages["1.2.0"], "--url", url.format("1.2.0"), "--released", "2026-09-01",
                        "--index-dir", index)
        assert code == 0 and "created" in out, out
        path = index / "better-lockpicks.json"
        data = json.loads(path.read_text(encoding="utf-8"))
        assert data["versions"] == [{
            "version": "1.2.0", "url": url.format("1.2.0"), "sha256": L.sha256_file(packages["1.2.0"]),
            "size": packages["1.2.0"].stat().st_size, "released": "2026-09-01", "api": 1,
            "requires": {"sdk-ui-helpers": ">=0.3.0"}, "conflicts": ["old-lockpicks"]}], data["versions"]
        for key in ("name", "description", "authors", "homepage", "license", "tags"):
            assert data[key] == CODE[key], key
        assert list(data) == ["id", "name", "description", "authors", "homepage", "license", "tags", "versions"]

        code, out = run(modindex, "add", packages["1.2.0"], "--url", url.format("1.2.0"), "--index-dir", index)
        assert code == 1 and "already lists version 1.2.0" in out, out
        assert run(modindex, "add", packages["1.3.0"], "--url", url.format("1.3.0"), "--index-dir", index)[0] == 0
        assert run(modindex, "add", packages["1.1.0"], "--url", url.format("1.1.0"), "--index-dir", index)[0] == 0
        data = json.loads(path.read_text(encoding="utf-8"))
        assert [v["version"] for v in data["versions"]] == ["1.3.0", "1.2.0", "1.1.0"]
        assert data["name"] == "Better Lockpicks 2"  # the newest version describes the mod
        code, out = run(modindex, "add", packages["1.1.0"], "--url", "http://mods.test/x.t3mod",
                        "--index-dir", index)
        assert code == 1 and "--url" in out, out

        content = pack(make_mod(tmp / "hd", CONTENT, {"textures/stone.dds": DDS}), tmp / "hd-textures.t3mod")
        assert run(modindex, "add", content, "--url", "https://mods.test/hd.t3mod", "--index-dir", index)[0] == 0
        code, out = run(modindex, "validate", "--index-dir", index)
        assert code == 0 and "2 mods, 4 versions valid" in out, out

        site = tmp / "site" / "modindex" / "index.json"
        os.environ["SOURCE_DATE_EPOCH"] = "0"
        try:
            code, out = run(modindex, "build", "-o", site, "--index-dir", index)
        finally:
            del os.environ["SOURCE_DATE_EPOCH"]
        assert code == 0, out
        built = json.loads(site.read_text(encoding="utf-8"))
        assert built["format"] == 1 and built["generated"] == "1970-01-01T00:00:00Z"
        assert [m["id"] for m in built["mods"]] == ["better-lockpicks", "hd-textures"]
        assert run(modindex, "build", "-o", tmp / "now.json", "--index-dir", index)[0] == 0
        generated = json.loads((tmp / "now.json").read_text(encoding="utf-8"))["generated"]
        assert re.fullmatch(r"\d{4}-\d\d-\d\dT\d\d:\d\d:\d\dZ", generated), generated
        empty = tmp / "empty"
        empty.mkdir()
        assert run(modindex, "build", "-o", tmp / "empty.json", "--index-dir", empty)[0] == 0
        assert json.loads((tmp / "empty.json").read_text(encoding="utf-8"))["mods"] == []

        # Broken per-mod files, each with the field at fault.
        good = json.loads(path.read_text(encoding="utf-8"))
        first = good["versions"][0]
        cases = [
            ("id", "other", good),
            ("versions", "better-lockpicks", {**good, "versions": list(reversed(good["versions"]))}),
            ("versions[1].version", "better-lockpicks",
             {**good, "versions": [first, {**first, "version": "1.3.0+again"}]}),
            ("versions[0].url", "better-lockpicks", {**good, "versions": [{**first, "url": "http://x.test/a"}]}),
            ("versions[0].sha256", "better-lockpicks",
             {**good, "versions": [{**first, "sha256": first["sha256"].upper()}]}),
            ("versions[0].size", "better-lockpicks", {**good, "versions": [{**first, "size": 0}]}),
            ("versions[0].released", "better-lockpicks", {**good, "versions": [{**first, "released": "2026-13-01"}]}),
            ("versions[0].released", "better-lockpicks",
             {**good, "versions": [{k: v for k, v in first.items() if k != "released"}]}),
            ("versions[0].requires", "better-lockpicks",
             {**good, "versions": [{**first, "requires": {"better-lockpicks": "*"}}]}),
            ("versions", "better-lockpicks", {**good, "versions": []}),
            ("tags", "better-lockpicks", {**good, "tags": ["weapons"]}),
            ("screenshots", "better-lockpicks", {**good, "screenshots": []}),
            ("name", "better-lockpicks", {k: v for k, v in good.items() if k != "name"}),
        ]
        for where, file_id, mod in cases:
            places = {p.where for p in modindex.check_mod(mod, file_id)}
            assert where in places, (where, places)
        bad = tmp / "bad"
        write_json(bad / "other.json", good)
        code, out = run(modindex, "validate", "--index-dir", bad)
        assert code == 1 and "other.json: id:" in out, out
        code, out = run(modindex, "build", "-o", tmp / "bad.json", "--index-dir", bad)
        assert code == 1 and not (tmp / "bad.json").exists(), out
    print(f"mod index: add, order, validate ({len(cases)} broken files), build: ok")


class QuietHandler(http.server.SimpleHTTPRequestHandler):
    def log_message(self, format: str, *args: Any) -> None:
        pass


@contextlib.contextmanager
def serve(folder: Path):
    """A local HTTP server for `folder`; yields its base URL."""
    os.environ["no_proxy"] = ",".join(filter(None, [os.environ.get("no_proxy"), "127.0.0.1", "localhost"]))
    server = http.server.ThreadingHTTPServer(("127.0.0.1", 0), functools.partial(QuietHandler, directory=str(folder)))
    thread = threading.Thread(target=server.serve_forever, daemon=True)
    thread.start()
    try:
        yield f"http://127.0.0.1:{server.server_address[1]}/"
    finally:
        server.shutdown()
        server.server_close()


def git(repo: Path, *args: str) -> None:
    env = {**os.environ, "GIT_AUTHOR_NAME": "selftest", "GIT_AUTHOR_EMAIL": "selftest@example.invalid",
           "GIT_COMMITTER_NAME": "selftest", "GIT_COMMITTER_EMAIL": "selftest@example.invalid",
           "GIT_CONFIG_NOSYSTEM": "1"}
    subprocess.run(["git", "-C", str(repo), "-c", "commit.gpgsign=false", "-c", "init.defaultBranch=main", *args],
                   check=True, capture_output=True, env=env)


def test_verify() -> None:
    with tempfile.TemporaryDirectory() as tmp:
        tmp = Path(tmp)
        www = tmp / "www"
        www.mkdir()
        packages = {}
        for version in ("1.2.0", "1.3.0"):
            folder = make_mod(tmp / version, versioned(CODE, version), {"better-lockpicks.dll": DLL})
            packages[version] = pack(folder, www / f"better-lockpicks-{version}.t3mod")
        bad = make_zip(www / "bad.t3mod", [("mod.json", json.dumps(CONTENT).encode()), ("files/System/x.dll", DLL)])

        def entry(path: Path, url: str, **changes: Any) -> Dict[str, Any]:
            manifest = json.loads(zipfile.ZipFile(path).read("mod.json"))
            base = {"version": manifest["version"], "url": url, "sha256": L.sha256_file(path),
                    "size": path.stat().st_size, "released": "2026-09-01"}
            base.update({k: manifest[k] for k in ("api", "requires", "conflicts") if k in manifest})
            return {**base, **changes}

        pkg = packages["1.2.0"]
        with serve(www) as base_url:
            http_url = base_url + pkg.name
            assert modindex.verify_version("better-lockpicks", entry(pkg, http_url)) == []
            assert modindex.verify_version("better-lockpicks", entry(pkg, pkg.as_uri())) == []
            cases = [
                ("sha256", entry(pkg, http_url, sha256="0" * 64)),
                ("size", entry(pkg, http_url, size=pkg.stat().st_size - 1)),
                ("size", entry(pkg, http_url, size=pkg.stat().st_size + 1)),
                ("api", entry(pkg, http_url, api=2)),
                ("conflicts", entry(pkg, http_url, conflicts=[])),
                ("requires", entry(pkg, http_url, requires={"sdk-ui-helpers": ">=0.4.0"})),
                ("version", entry(pkg, http_url, version="1.2.1")),
                ("failed", entry(pkg, base_url + "missing.t3mod")),
                ("files/System/x.dll", entry(bad, base_url + bad.name)),
            ]
            for what, e in cases:
                problems = modindex.verify_version("better-lockpicks" if what != "files/System/x.dll" else "hd-textures",
                                                   e)
                assert any(what in p.message for p in L.errors(problems)), (what, [str(p) for p in problems])
            id_problems = modindex.verify_version("other-mod", entry(pkg, http_url))
            assert any(p.message.startswith("id:") for p in id_problems), id_problems

            if shutil.which("git"):
                test_changed_only(tmp, packages, base_url)
            else:
                print("verify --changed-only: skipped (no git)")
    print(f"verify: HTTP and file:// downloads, {len(cases) + 1} mismatches caught: ok")


def test_changed_only(tmp: Path, packages: Dict[str, Path], base_url: str) -> None:
    repo = tmp / "repo"
    index = repo / "modindex" / "mods"
    index.mkdir(parents=True)
    git(repo, "init", "-q")
    url = "https://mods.test/better-lockpicks-{}.t3mod"
    assert run(modindex, "add", packages["1.2.0"], "--url", url.format("1.2.0"), "--index-dir", index)[0] == 0
    git(repo, "add", "-A")
    git(repo, "commit", "-q", "-m", "one version")
    base = subprocess.run(["git", "-C", str(repo), "rev-parse", "HEAD"], capture_output=True, text=True,
                          check=True).stdout.strip()
    assert run(modindex, "add", packages["1.3.0"], "--url", url.format("1.3.0"), "--index-dir", index)[0] == 0
    path = index / "better-lockpicks.json"
    data = json.loads(path.read_text(encoding="utf-8"))

    todo, problems = modindex.changed_versions(path, data, base)
    assert [e["version"] for e in todo] == ["1.3.0"] and not problems, (todo, problems)
    moved = {**data, "versions": [data["versions"][0], {**data["versions"][1], "url": url.format("moved")}]}
    todo, problems = modindex.changed_versions(path, moved, base)
    assert [e["version"] for e in todo] == ["1.3.0", "1.2.0"] and not problems
    changed = {**data, "versions": [data["versions"][0], {**data["versions"][1], "sha256": "0" * 64}]}
    todo, problems = modindex.changed_versions(path, changed, base)
    assert any("published version changed" in p.message for p in problems), problems

    original = modindex.fetch

    def local(url: str, dest: Path, limit: int) -> int:
        return original(url.replace("https://mods.test/", base_url), dest, limit)

    modindex.fetch = local
    try:
        code, out = run(modindex, "verify", "--changed-only", base, "--index-dir", index)
        assert code == 0 and "verifying better-lockpicks 1.3.0" in out and "1.2.0 from" not in out, out
        assert "1 changed since" in out, out
        code, out = run(modindex, "verify", "--index-dir", index)
        assert code == 0 and "2 listed versions verified" in out, out
        code, out = run(modindex, "verify", "--changed-only", "no-such-ref", "--index-dir", index)
        assert code == 1 and "not a commit" in out, out
        write_json(path, changed)
        code, out = run(modindex, "verify", "--changed-only", base, "--index-dir", index)
        assert code == 1 and "published version changed" in out, out
    finally:
        modindex.fetch = original
    print("verify --changed-only: new, moved and changed versions: ok")


# --- the template -------------------------------------------------------------------------

def template_values() -> Dict[str, str]:
    cmake = (TEMPLATE / "CMakeLists.txt").read_text(encoding="utf-8")
    version = re.search(r"^project\(\s*\S+\s+VERSION\s+([0-9.]+)", cmake, re.M)
    mod_id = re.search(r'^set\(MOD_ID\s+"([^"]+)"\)', cmake, re.M)
    assert version and mod_id, "templates/mod/CMakeLists.txt: no project(... VERSION) or set(MOD_ID ...)"
    return {"PROJECT_VERSION": version.group(1), "MOD_ID": mod_id.group(1)}


def test_template() -> None:
    values = template_values()
    text = (TEMPLATE / "mod.json.in").read_text(encoding="utf-8")
    for key, value in values.items():
        text = text.replace(f"@{key}@", value)
    assert "@" not in text, "mod.json.in uses a variable CMakeLists.txt does not set"
    manifest, problems = L.load_json(text.encode("utf-8"), "mod.json.in")
    problems += L.check_manifest(manifest)
    assert not problems, [str(p) for p in problems]
    note = "mod.json.in: ok"

    cmake = shutil.which("cmake")
    if not cmake:
        print(f"template: {note}; packaging script skipped (no cmake)")
        return
    with tempfile.TemporaryDirectory() as tmp:
        tmp = Path(tmp)
        build = tmp / "build"
        build.mkdir()
        (build / "mod.json").write_text(text, encoding="utf-8")
        dll = build / f"{values['MOD_ID']}.dll"
        dll.write_bytes(DLL)
        content = tmp / "project"
        shutil.copytree(TEMPLATE / "files", content / "files")
        make_mod(content, {}, {"files/Content/T3/Bitmaps/x.dds": DDS, "files/.gitkeep": b"",
                               "textures/stone.dds": DDS})
        (content / "mod.json").unlink()
        out = build / f"{values['MOD_ID']}-{values['PROJECT_VERSION']}.t3mod"
        result = subprocess.run([cmake, f"-DMOD_JSON={build / 'mod.json'}", f"-DMOD_DLL={dll}",
                                 f"-DCONTENT_DIR={content}", f"-DSTAGE_DIR={build / 'package'}", f"-DOUTPUT={out}",
                                 "-P", str(TEMPLATE / "cmake" / "package.cmake")], capture_output=True, text=True)
        assert result.returncode == 0, result.stdout + result.stderr
        package = L.read_zip(out)
        assert not package.problems, [str(p) for p in package.problems]
        with zipfile.ZipFile(out) as z:
            names = z.namelist()
            assert all(i.date_time == L.PACKAGE_TIME for i in z.infolist())
        assert names == sorted(["files/Content/T3/Bitmaps/x.dds", f"{values['MOD_ID']}.dll", "mod.json",
                                "textures/stone.dds"]), names
        note += ", cmake/package.cmake: ok"

        version = subprocess.run([cmake, "--version"], capture_output=True, text=True).stdout.split()
        if len(version) > 2 and tuple(int(n) for n in re.findall(r"\d+", version[2])[:2]) >= (3, 25):
            presets = subprocess.run([cmake, "--list-presets=all"], cwd=TEMPLATE, capture_output=True, text=True)
            assert presets.returncode == 0 and '"release"' in presets.stdout, presets.stdout + presets.stderr
            note += ", CMakePresets.json: ok"
    print(f"template: {note}")


def main() -> None:
    test_fixtures()
    test_ranges()
    test_pack()
    test_folder_refusals()
    test_zip_refusals()
    test_index()
    test_verify()
    test_template()
    print("all mod tool self-tests passed")


if __name__ == "__main__":
    main()
