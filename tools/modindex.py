#!/usr/bin/env python3
"""The mod index (docs/mods.md, "The mod index"): one file per mod in
modindex/mods/<id>.json, combined into the index.json the launcher reads.

  validate [<file> ...]
      check the per-mod files (default: every modindex/mods/*.json): the
      schema, the id against the file name, versions unique and newest first,
      https URLs, SHA-256 digests, sizes, release dates, and the manifest
      fields with the package tool's own rules
  verify [<file> ...] [--changed-only <git ref>]
      validate, then download each version (with --changed-only, only those
      added since <git ref>, or whose entry changed) and check its size,
      SHA-256 and mod.json (id, version, api, requires, conflicts) against the
      entry, and the package against the package rules. A version whose
      sha256 or size differs from <git ref> is refused: a published version
      never changes.
  build -o <index.json>
      write the combined index: every mod, sorted by id, and "generated" (the
      current UTC time, or $SOURCE_DATE_EPOCH)
  add <.t3mod> --url <https url> [--released YYYY-MM-DD]
      add a version to modindex/mods/<id>.json (created when new) from a
      package: its size, SHA-256 and manifest fields. The URL is not
      downloaded: upload the package there before opening the pull request.

--index-dir picks another folder of per-mod files (default modindex/mods).
Python 3.10+, standard library only; the rules are in tools/mods/t3modlib.py.
"""

from __future__ import annotations

import argparse
import http.client
import json
import os
import re
import subprocess
import sys
import tempfile
import urllib.error
import urllib.request
from datetime import datetime, timezone
from pathlib import Path
from typing import Any, Dict, List, Optional, Tuple

sys.path.insert(0, str(Path(__file__).resolve().parent / "mods"))
import t3modlib  # noqa: E402
from t3modlib import Problem  # noqa: E402

ROOT = Path(__file__).resolve().parent.parent
INDEX_DIR = ROOT / "modindex" / "mods"
FORMAT = 1
MOD_KEYS = ("id", "name", "description", "authors", "homepage", "license", "tags", "versions")
MOD_REQUIRED = ("id", "name", "authors", "versions")
VERSION_KEYS = ("version", "url", "sha256", "size", "released", "api", "requires", "conflicts")
VERSION_REQUIRED = ("version", "url", "sha256", "size", "released")
SHA256_RE = re.compile(r"[0-9a-f]{64}")
USER_AGENT = "T3SDK-modindex (+https://github.com/Veradictus/Thief3-Decomp)"
TIMEOUT = 60  # seconds without data before a download fails


# --- the per-mod files --------------------------------------------------------------------

def _is_int(value: Any) -> bool:
    return isinstance(value, int) and not isinstance(value, bool)


def check_version_entry(entry: Any, where: str, own_id: Optional[str]) -> List[Problem]:
    if not isinstance(entry, dict):
        return [Problem(where, "must be an object")]
    problems: List[Problem] = []

    def check(key: str, why: Optional[str]) -> None:
        if why:
            problems.append(Problem(f"{where}.{key}", why))

    for key in entry:
        if key not in VERSION_KEYS:
            check(key, f"unknown field (known: {', '.join(VERSION_KEYS)})")
    for key in VERSION_REQUIRED:
        if key not in entry:
            check(key, "missing (required)")
    if "version" in entry:
        check("version", t3modlib.check_version(entry["version"]))
    if "url" in entry:
        check("url", t3modlib.check_https_url(entry["url"]))
    if "sha256" in entry and not (isinstance(entry["sha256"], str) and SHA256_RE.fullmatch(entry["sha256"])):
        check("sha256", "must be the package's SHA-256: 64 lower-case hex digits")
    if "size" in entry and not (_is_int(entry["size"]) and entry["size"] > 0):
        check("size", "must be the package's size in bytes, more than 0")
    if "released" in entry:
        check("released", t3modlib.check_date(entry["released"]))
    if "api" in entry:
        check("api", t3modlib.check_api(entry["api"]))
    if "requires" in entry:
        check("requires", t3modlib.check_requires(entry["requires"], own_id))
    if "conflicts" in entry:
        check("conflicts", t3modlib.check_conflicts(entry["conflicts"], own_id, entry.get("requires")))
    return problems


def check_mod(mod: Any, file_id: str) -> List[Problem]:
    """The rules for one per-mod file; `file_id` is its name without .json."""
    if not isinstance(mod, dict):
        return [Problem(file_id, "must be a JSON object")]
    problems: List[Problem] = []

    def check(key: str, why: Optional[str]) -> None:
        if why:
            problems.append(Problem(key, why))

    for key in mod:
        if key not in MOD_KEYS:
            check(key, f"unknown field (known: {', '.join(MOD_KEYS)})")
    for key in MOD_REQUIRED:
        if key not in mod:
            check(key, "missing (required)")
    own_id = mod.get("id")
    if "id" in mod:
        why = t3modlib.check_id(own_id)
        if not why and own_id != file_id:
            why = f"{own_id!r} does not match the file name, {file_id}.json"
        check("id", why)
    own_id = own_id if isinstance(own_id, str) else None
    for key, checker in (("name", t3modlib.check_name), ("description", t3modlib.check_description),
                         ("authors", t3modlib.check_authors), ("homepage", t3modlib.check_https_url),
                         ("license", t3modlib.check_license), ("tags", t3modlib.check_tags)):
        if key in mod:
            check(key, checker(mod[key]))
    versions = mod.get("versions")
    if "versions" not in mod:
        return problems
    if not isinstance(versions, list) or not versions:
        check("versions", "must be a list of one or more versions, newest first")
        return problems
    seen: Dict[tuple, int] = {}
    previous: Optional[Tuple[int, t3modlib.Version]] = None
    for i, entry in enumerate(versions):
        problems += check_version_entry(entry, f"versions[{i}]", own_id)
        try:
            version = t3modlib.parse_version(entry.get("version") if isinstance(entry, dict) else None)
        except ValueError:
            continue
        if version.key in seen:
            check(f"versions[{i}].version", f"{version} is already listed as versions[{seen[version.key]}]")
            continue
        seen[version.key] = i
        if previous and version.key > previous[1].key:
            check("versions", f"not newest first: {previous[1]} (versions[{previous[0]}]) is listed before "
                              f"{version} (versions[{i}])")
        previous = (i, version)
    return problems


def load_mod_file(path: Path) -> Tuple[Any, List[Problem]]:
    data, problems = t3modlib.load_json(path.read_bytes(), path.name)
    if problems:
        return None, problems
    return data, check_mod(data, path.stem)


def index_files(args: argparse.Namespace) -> List[Path]:
    if getattr(args, "files", None):
        return [Path(f) for f in args.files]
    return sorted(Path(args.index_dir).glob("*.json"))


def report(label: str, problems: List[Problem]) -> bool:
    for p in problems:
        print(f"{'warning' if p.warning else 'error'}: {label}: {p}")
    return not t3modlib.errors(problems)


def load_all(files: List[Path]) -> Tuple[List[Tuple[Path, Dict[str, Any]]], bool]:
    """Every file loaded and checked; (the valid ones, whether all were valid)."""
    loaded = []
    ok = True
    for path in files:
        if not path.is_file():
            print(f"error: {path}: no such file")
            ok = False
            continue
        data, problems = load_mod_file(path)
        if report(path.name, problems):
            loaded.append((path, data))
        else:
            ok = False
    return loaded, ok


def dump(data: Any) -> str:
    return json.dumps(data, indent=2, ensure_ascii=False) + "\n"


def cmd_validate(args: argparse.Namespace) -> int:
    loaded, ok = load_all(index_files(args))
    versions = sum(len(data["versions"]) for _, data in loaded)
    print(f"{len(loaded)} mods, {versions} versions valid" + ("" if ok else "; errors above"))
    return 0 if ok else 1


# --- verify -------------------------------------------------------------------------------

def fetch(url: str, dest: Path, limit: int) -> int:
    """Download `url` into `dest`, stopping once more than `limit` bytes have
    come; returns the number of bytes read."""
    request = urllib.request.Request(url, headers={"User-Agent": USER_AGENT})
    total = 0
    with urllib.request.urlopen(request, timeout=TIMEOUT) as response, dest.open("wb") as out:
        while total <= limit:
            chunk = response.read(1 << 20)
            if not chunk:
                break
            total += len(chunk)
            out.write(chunk)
    return total


def verify_version(mod_id: str, entry: Dict[str, Any]) -> List[Problem]:
    """Download one version and check it against its index entry."""
    where = f"{mod_id} {entry['version']}"
    size = entry["size"]
    with tempfile.TemporaryDirectory(prefix="modindex-") as tmp:
        path = Path(tmp) / "package.t3mod"
        try:
            got = fetch(entry["url"], path, size)
        except (urllib.error.URLError, http.client.HTTPException, OSError, ValueError) as e:
            return [Problem(where, f"download of {entry['url']} failed: {e}")]
        if got != size:
            return [Problem(where, f"size: the download is {'more than ' if got > size else ''}{got} bytes, "
                                   f"the entry says {size}")]
        digest = t3modlib.sha256_file(path)
        if digest != entry["sha256"]:
            return [Problem(where, f"sha256: the download's is {digest}, the entry says {entry['sha256']}")]
        package = t3modlib.read_zip(path)
    problems = [Problem(where, str(p), p.warning) for p in package.problems]
    manifest = package.manifest
    if package.errors or manifest is None:
        return problems
    def fields(source: Dict[str, Any]) -> Dict[str, Any]:  # what the entry repeats from mod.json
        return {"id": source.get("id"), "version": source.get("version"), "api": source.get("api"),
                "requires": source.get("requires") or {}, "conflicts": sorted(source.get("conflicts") or [])}

    expected, actual = fields({**entry, "id": mod_id}), fields(manifest)
    for key in expected:
        if expected[key] != actual[key]:
            problems.append(Problem(where, f"{key}: the package's mod.json has {json.dumps(actual[key])}, "
                                           f"the index {json.dumps(expected[key])}"))
    return problems


def git(repo: Path, *args: str) -> subprocess.CompletedProcess:
    return subprocess.run(["git", "-C", str(repo), *args], capture_output=True)


def git_toplevel(path: Path) -> Path:
    try:
        result = git(path, "rev-parse", "--show-toplevel")
    except OSError as e:
        sys.exit(f"--changed-only needs git: {e}")
    if result.returncode != 0:
        sys.exit(f"--changed-only: {path} is not in a git repository")
    return Path(result.stdout.decode().strip()).resolve()


def changed_versions(path: Path, mod: Dict[str, Any], base_ref: str) -> Tuple[List[Dict[str, Any]], List[Problem]]:
    """The versions of `mod` (read from `path`) to verify against `base_ref`:
    added ones and ones whose entry changed. A changed sha256 or size is an
    error instead."""
    top = git_toplevel(path.resolve().parent)
    rel = path.resolve().relative_to(top).as_posix()
    if git(top, "cat-file", "-e", f"{base_ref}:{rel}").returncode != 0:
        return list(mod["versions"]), []  # a new mod
    base, problems = t3modlib.load_json(git(top, "show", f"{base_ref}:{rel}").stdout, f"{base_ref}:{rel}")
    old: Dict[str, Dict[str, Any]] = {}
    if not problems and isinstance(base, dict) and isinstance(base.get("versions"), list):
        old = {e["version"]: e for e in base["versions"] if isinstance(e, dict) and isinstance(e.get("version"), str)}
    todo: List[Dict[str, Any]] = []
    errors: List[Problem] = []
    for entry in mod["versions"]:
        before = old.get(entry["version"])
        if before is None:
            todo.append(entry)
        elif (before.get("sha256"), before.get("size")) != (entry["sha256"], entry["size"]):
            errors.append(Problem(f"{mod['id']} {entry['version']}",
                                  f"published version changed (sha256 or size differs from {base_ref}); "
                                  "publish a new version instead"))
        elif before != entry:
            todo.append(entry)
    return todo, errors


def cmd_verify(args: argparse.Namespace) -> int:
    loaded, ok = load_all(index_files(args))
    if args.changed_only:
        top = git_toplevel(Path(args.index_dir).resolve() if Path(args.index_dir).exists() else ROOT)
        if git(top, "rev-parse", "--verify", "--quiet", f"{args.changed_only}^{{commit}}").returncode != 0:
            sys.exit(f"--changed-only: {args.changed_only!r} is not a commit in {top}")
    count = 0
    for path, mod in loaded:
        if args.changed_only:
            todo, problems = changed_versions(path, mod, args.changed_only)
            ok = report(path.name, problems) and ok
        else:
            todo = list(mod["versions"])
        for entry in todo:
            print(f"verifying {mod['id']} {entry['version']} from {entry['url']}", flush=True)
            ok = report(path.name, verify_version(mod["id"], entry)) and ok
            count += 1
    what = f"changed since {args.changed_only}" if args.changed_only else "listed"
    print(f"{count} {what} versions verified" + ("" if ok else "; errors above"))
    return 0 if ok else 1


# --- build and add ------------------------------------------------------------------------

def generated_time() -> str:
    epoch = os.environ.get("SOURCE_DATE_EPOCH")
    now = datetime.fromtimestamp(int(epoch), timezone.utc) if epoch else datetime.now(timezone.utc)
    return now.strftime("%Y-%m-%dT%H:%M:%SZ")


def cmd_build(args: argparse.Namespace) -> int:
    loaded, ok = load_all(index_files(args))
    if not ok:
        print("index not written: errors above")
        return 1
    mods = sorted((data for _, data in loaded), key=lambda m: m["id"])
    out = Path(args.output)
    out.parent.mkdir(parents=True, exist_ok=True)
    out.write_text(dump({"format": FORMAT, "generated": generated_time(), "mods": mods}), encoding="utf-8")
    print(f"wrote {out}: {len(mods)} mods")
    return 0


def cmd_add(args: argparse.Namespace) -> int:
    package_path = Path(args.package)
    if not package_path.is_file():
        print(f"error: {package_path}: no such file")
        return 1
    package = t3modlib.read_zip(package_path)
    if not report(package_path.name, package.problems) or package.manifest is None:
        print("not added: fix the package first")
        return 1
    manifest = package.manifest
    released = args.released or datetime.now(timezone.utc).date().isoformat()
    for key, why in (("--url", t3modlib.check_https_url(args.url)), ("--released", t3modlib.check_date(released))):
        if why:
            print(f"error: {key}: {why}")
            return 1
    url_name = args.url.rstrip("/").rsplit("/", 1)[-1]
    if url_name != package_path.name:
        print(f"warning: the URL's file name, {url_name}, is not the package's, {package_path.name}")

    entry: Dict[str, Any] = {"version": manifest["version"], "url": args.url,
                             "sha256": t3modlib.sha256_file(package_path), "size": package_path.stat().st_size,
                             "released": released}
    for key in ("api", "requires", "conflicts"):
        if manifest.get(key) not in (None, {}, []):
            entry[key] = manifest[key]

    mod_id = manifest["id"]
    path = Path(args.index_dir) / f"{mod_id}.json"
    versions: List[Dict[str, Any]] = []
    newest = True
    if path.is_file():
        data, problems = load_mod_file(path)
        if not report(path.name, problems):
            print(f"not added: fix {path} first")
            return 1
        new_key = t3modlib.parse_version(entry["version"]).key
        for existing in data["versions"]:
            if t3modlib.parse_version(existing["version"]).key == new_key:
                print(f"error: {path.name} already lists version {existing['version']}; a published version "
                      "never changes: give the package a new version")
                return 1
        versions = data["versions"]
        newest = all(t3modlib.parse_version(v["version"]).key < new_key for v in versions)
        mod = data
    if newest:  # the newest version describes the mod
        mod = {"id": mod_id}
        for key in ("name", "description", "authors", "homepage", "license", "tags"):
            if key in manifest:
                mod[key] = manifest[key]
    versions = sorted(versions + [entry], key=lambda v: t3modlib.parse_version(v["version"]).key, reverse=True)
    mod["versions"] = versions
    problems = check_mod(mod, mod_id)
    if not report(path.name, problems):
        return 1
    existed = path.is_file()
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(dump(mod), encoding="utf-8")
    print(f"{'updated' if existed else 'created'} {path}: {mod_id} {entry['version']}, {entry['size']} bytes, "
          f"sha256 {entry['sha256']}")
    print("next: make sure the package is at the URL, then open a pull request with this file")
    return 0


def main(argv: Optional[List[str]] = None) -> int:
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    common = argparse.ArgumentParser(add_help=False)
    common.add_argument("--index-dir", default=str(INDEX_DIR), help="the per-mod files (default: modindex/mods)")
    sub = parser.add_subparsers(dest="command", required=True)
    v = sub.add_parser("validate", parents=[common], help="check the per-mod files")
    v.add_argument("files", nargs="*", help="per-mod files (default: all)")
    f = sub.add_parser("verify", parents=[common], help="download versions and check them against the index")
    f.add_argument("files", nargs="*", help="per-mod files (default: all)")
    f.add_argument("--changed-only", metavar="BASE_REF",
                   help="only versions added or changed since this git ref (e.g. origin/master)")
    b = sub.add_parser("build", parents=[common], help="write the combined index")
    b.add_argument("-o", "--output", required=True, help="the index.json to write")
    a = sub.add_parser("add", parents=[common], help="add a package's version to its per-mod file")
    a.add_argument("package", help="the .t3mod")
    a.add_argument("--url", required=True, help="where the package is published (https)")
    a.add_argument("--released", help="release date, YYYY-MM-DD (default: today, UTC)")
    args = parser.parse_args(argv)
    return {"validate": cmd_validate, "verify": cmd_verify, "build": cmd_build, "add": cmd_add}[args.command](args)


if __name__ == "__main__":
    sys.exit(main())
