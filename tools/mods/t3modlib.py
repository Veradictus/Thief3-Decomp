"""The .t3mod package format (docs/mods.md): manifest rules, semantic versions
and version ranges, and the rules for a package's files, in a folder or a zip.

Shared by tools/t3mod.py and tools/modindex.py; import it the way the other
tools import their neighbours:

    sys.path.insert(0, str(Path(__file__).resolve().parent / "mods"))
    import t3modlib

The launcher implements the same rules in Rust (launcher/src-tauri/src/mods.rs);
tools/mods/fixtures/ keeps the two in step. Standard library only.
"""

from __future__ import annotations

import hashlib
import json
import os
import re
import stat
import zipfile
import zlib
from dataclasses import dataclass, field
from datetime import date
from pathlib import Path
from typing import Any, Callable, Dict, Iterable, List, Optional, Tuple
from urllib.parse import urlsplit

FORMAT = 1  # the mod.json "format" this module reads
MANIFEST = "mod.json"
TAGS = ("gameplay", "graphics", "textures", "audio", "ui", "fixes", "maps", "tools", "library")
MAX_TAGS = 8
MAX_NAME = 80
MAX_DESCRIPTION = 1000
MAX_MANIFEST_BYTES = 1 << 20  # far above any real manifest; stops a huge entry from being read
LARGE_FILE = 256 << 20  # warn about a single file above this...
LARGE_PACKAGE = 2 << 30  # ...and about a package above this in all
MAX_NUMBER = 2**64 - 1  # version numbers are u64 in the launcher (Rust's semver crate)

# Skipped when a folder is packed (compared case-insensitively). *.pdb is
# skipped too unless asked for, and so are .t3mod packages left in the folder.
JUNK_NAMES = frozenset({".git", ".gitignore", ".gitattributes", ".gitkeep", ".gitmodules", ".ds_store",
                        "thumbs.db", "desktop.ini"})
PACKAGE_SUFFIX = ".t3mod"
# Deterministic packages: every entry gets this time (the zip format's epoch)
# and these attributes (a regular rw-r--r-- file, "made on Unix").
PACKAGE_TIME = (1980, 1, 1, 0, 0, 0)
PACKAGE_ATTR = (stat.S_IFREG | 0o644) << 16

EXECUTABLE_SUFFIXES = frozenset({".exe", ".com", ".scr", ".msi", ".bat", ".cmd", ".ps1", ".vbs", ".sh", ".lnk"})
ARCHIVE_SUFFIXES = frozenset({".zip", ".7z", ".rar", PACKAGE_SUFFIX})


@dataclass
class Problem:
    """One finding. `where` names a manifest field, a path in the package, or
    "package"/"mod.json" for the whole; warnings never fail a check."""

    where: str
    message: str
    warning: bool = False

    def __str__(self) -> str:
        return f"{self.where}: {self.message}"


def errors(problems: Iterable[Problem]) -> List[Problem]:
    return [p for p in problems if not p.warning]


def warnings(problems: Iterable[Problem]) -> List[Problem]:
    return [p for p in problems if p.warning]


def _is_int(value: Any) -> bool:
    return isinstance(value, int) and not isinstance(value, bool)


# --- semantic versions and ranges --------------------------------------------------------

_NUM = r"0|[1-9][0-9]*"
_PRE_IDENT = r"0|[1-9][0-9]*|[0-9]*[A-Za-z-][0-9A-Za-z-]*"
_PRE = rf"(?:{_PRE_IDENT})(?:\.(?:{_PRE_IDENT}))*"
_BUILD = r"[0-9A-Za-z-]+(?:\.[0-9A-Za-z-]+)*"
_VERSION_RE = re.compile(rf"({_NUM})\.({_NUM})\.({_NUM})(?:-({_PRE}))?(?:\+({_BUILD}))?")
_COMPARATOR_RE = re.compile(rf"\s*(>=|<=|>|<|=|\^|~)\s*({_NUM})(?:\.({_NUM})(?:\.({_NUM})(?:-({_PRE}))?)?)?\s*")


def _pre_key(pre: Tuple[str, ...]) -> tuple:
    """Pre-release precedence: none is highest; numeric identifiers sort below
    alphanumeric ones; a longer list wins when the shorter is its prefix."""
    if not pre:
        return (1,)
    return (0, tuple((0, int(p), "") if p.isdigit() else (1, 0, p) for p in pre))


def _number(text: str) -> int:
    value = int(text)
    if value > MAX_NUMBER:
        raise ValueError(f"{text} is larger than {MAX_NUMBER}")
    return value


@dataclass(frozen=True)
class Version:
    major: int
    minor: int
    patch: int
    pre: Tuple[str, ...] = ()
    build: str = ""

    @property
    def key(self) -> tuple:
        """Semantic-version precedence (build metadata does not count)."""
        return (self.major, self.minor, self.patch, _pre_key(self.pre))

    def __str__(self) -> str:
        text = f"{self.major}.{self.minor}.{self.patch}"
        if self.pre:
            text += "-" + ".".join(self.pre)
        return text + (f"+{self.build}" if self.build else "")


def parse_version(text: Any) -> Version:
    """A semantic version, MAJOR.MINOR.PATCH[-pre][+build]; ValueError otherwise."""
    if not isinstance(text, str):
        raise ValueError("must be a string")
    m = _VERSION_RE.fullmatch(text)
    if not m:
        raise ValueError(f"{text!r} is not a semantic version (MAJOR.MINOR.PATCH, optional -pre-release and +build)")
    pre = tuple(m.group(4).split(".")) if m.group(4) else ()
    for part in pre:
        if part.isdigit():
            _number(part)
    return Version(_number(m.group(1)), _number(m.group(2)), _number(m.group(3)), pre, m.group(5) or "")


@dataclass(frozen=True)
class Comparator:
    """One comparator of a range. Missing minor/patch numbers are None and
    match anything, as in Cargo: `<=1.2` is `<1.3.0`, `=1.2` is
    `>=1.2.0, <1.3.0`. The rules follow Rust's semver crate."""

    op: str
    major: int
    minor: Optional[int] = None
    patch: Optional[int] = None
    pre: Tuple[str, ...] = ()

    def _exact(self, v: Version) -> bool:
        if v.major != self.major:
            return False
        if self.minor is not None and v.minor != self.minor:
            return False
        if self.patch is not None and v.patch != self.patch:
            return False
        return v.pre == self.pre

    def _greater(self, v: Version) -> bool:
        if v.major != self.major:
            return v.major > self.major
        if self.minor is None:
            return False
        if v.minor != self.minor:
            return v.minor > self.minor
        if self.patch is None:
            return False
        if v.patch != self.patch:
            return v.patch > self.patch
        return _pre_key(v.pre) > _pre_key(self.pre)

    def _less(self, v: Version) -> bool:
        if v.major != self.major:
            return v.major < self.major
        if self.minor is None:
            return False
        if v.minor != self.minor:
            return v.minor < self.minor
        if self.patch is None:
            return False
        if v.patch != self.patch:
            return v.patch < self.patch
        return _pre_key(v.pre) < _pre_key(self.pre)

    def _tilde(self, v: Version) -> bool:
        if v.major != self.major:
            return False
        if self.minor is not None and v.minor != self.minor:
            return False
        if self.patch is not None and v.patch != self.patch:
            return v.patch > self.patch
        return _pre_key(v.pre) >= _pre_key(self.pre)

    def _caret(self, v: Version) -> bool:
        if v.major != self.major:
            return False
        if self.minor is None:
            return True
        if self.patch is None:
            return v.minor >= self.minor if self.major > 0 else v.minor == self.minor
        if self.major > 0:
            if v.minor != self.minor:
                return v.minor > self.minor
            if v.patch != self.patch:
                return v.patch > self.patch
        elif self.minor > 0:
            if v.minor != self.minor:
                return False
            if v.patch != self.patch:
                return v.patch > self.patch
        elif v.minor != self.minor or v.patch != self.patch:
            return False
        return _pre_key(v.pre) >= _pre_key(self.pre)

    def matches(self, v: Version) -> bool:
        if self.op == "=":
            return self._exact(v)
        if self.op == ">":
            return self._greater(v)
        if self.op == ">=":
            return self._exact(v) or self._greater(v)
        if self.op == "<":
            return self._less(v)
        if self.op == "<=":
            return self._exact(v) or self._less(v)
        if self.op == "~":
            return self._tilde(v)
        return self._caret(v)


@dataclass(frozen=True)
class Range:
    comparators: Tuple[Comparator, ...]  # empty for "*"

    def satisfied_by(self, v: Version) -> bool:
        """Every comparator holds; a pre-release version also needs a
        comparator with the same MAJOR.MINOR.PATCH and a pre-release tag."""
        if not all(c.matches(v) for c in self.comparators):
            return False
        if not v.pre:
            return True
        return any(c.pre and (c.major, c.minor, c.patch) == (v.major, v.minor, v.patch) for c in self.comparators)


def parse_range(text: Any) -> Range:
    """A version range (docs/mods.md, "Version ranges"); ValueError otherwise."""
    if not isinstance(text, str):
        raise ValueError("a version range must be a string")
    if text.strip() == "*":
        return Range(())
    comparators = []
    for part in text.split(","):
        m = _COMPARATOR_RE.fullmatch(part)
        if not m:
            raise ValueError(f"{text!r} is not a version range (comparators such as >=1.2.0 or ^1.2.0, "
                             "separated by commas, or *)")
        op, major, minor, patch, pre = m.groups()
        comparators.append(Comparator(op, _number(major), None if minor is None else _number(minor),
                                      None if patch is None else _number(patch),
                                      tuple(pre.split(".")) if pre else ()))
    return Range(tuple(comparators))


def satisfies(range_text: str, version_text: str) -> bool:
    return parse_range(range_text).satisfied_by(parse_version(version_text))


# --- manifest fields ----------------------------------------------------------------------
# Each check returns None when the value is fine, else what is wrong with it.

ID_RE = re.compile(r"[a-z0-9][a-z0-9_-]{0,63}")
# Folders of System/mods/ that are not packages (the install folder is the id).
RESERVED_IDS = frozenset({"disabled", "originals"})


def check_id(value: Any) -> Optional[str]:
    if not isinstance(value, str) or not ID_RE.fullmatch(value):
        return (f"{value!r} is not a mod id: 1-64 characters of a-z, 0-9, '_' and '-', "
                "starting with a letter or digit")
    if value in RESERVED_IDS:
        return f"{value!r} is reserved: System/mods/{value}/ is not a package folder"
    return None


def check_name(value: Any) -> Optional[str]:
    if not isinstance(value, str) or not 1 <= len(value) <= MAX_NAME:
        return f"must be a string of 1-{MAX_NAME} characters"
    return None


def check_version(value: Any) -> Optional[str]:
    try:
        parse_version(value)
    except ValueError as e:
        return str(e)
    return None


def check_authors(value: Any) -> Optional[str]:
    if not isinstance(value, list) or not value:
        return "must be a list of one or more names"
    if not all(isinstance(a, str) and a.strip() for a in value):
        return "every author must be a non-empty string"
    return None


def check_description(value: Any) -> Optional[str]:
    if not isinstance(value, str) or len(value) > MAX_DESCRIPTION:
        return f"must be a string of at most {MAX_DESCRIPTION} characters"
    return None


def check_api(value: Any) -> Optional[str]:
    if not _is_int(value) or value < 1:
        return "must be a whole number, 1 or more (the lowest T3SDK_API_VERSION the DLL needs)"
    return None


def check_entry(value: Any) -> Optional[str]:
    if not isinstance(value, str) or not value.lower().endswith(".dll"):
        return "must be the file name of the mod's DLL, ending in .dll"
    if "/" in value or "\\" in value:
        return f"{value!r} must be a file at the package root, not in a folder"
    why = check_segment(value)
    return f"{value!r}: {why}" if why else None


def check_requires(value: Any, own_id: Optional[str] = None) -> Optional[str]:
    if not isinstance(value, dict):
        return 'must be an object of {"<mod id>": "<version range>"}'
    for key, rng in value.items():
        if check_id(key):
            return f"{key!r} is not a mod id"
        if key == own_id:
            return "a mod cannot require itself"
        try:
            parse_range(rng)
        except ValueError as e:
            return f"{key}: {e}"
    return None


def check_conflicts(value: Any, own_id: Optional[str] = None, requires: Any = None) -> Optional[str]:
    if not isinstance(value, list):
        return "must be a list of mod ids"
    for item in value:
        if check_id(item):
            return f"{item!r} is not a mod id"
        if item == own_id:
            return "a mod cannot conflict with itself"
        if isinstance(requires, dict) and item in requires:
            return f"{item} is also in requires"
    return None


def check_https_url(value: Any) -> Optional[str]:
    if not isinstance(value, str) or any(c.isspace() for c in value):
        return "must be an https:// URL"
    parts = urlsplit(value)
    if parts.scheme != "https" or not parts.netloc:
        return f"{value!r} is not an https:// URL"
    return None


def check_license(value: Any) -> Optional[str]:
    if not isinstance(value, str) or not value.strip():
        return "must be an SPDX identifier (MIT, CC-BY-4.0, ...) or a short text"
    return None


def check_tags(value: Any) -> Optional[str]:
    if not isinstance(value, list) or len(value) > MAX_TAGS:
        return f"must be a list of at most {MAX_TAGS} tags"
    unknown = [t for t in value if t not in TAGS]
    if unknown:
        return f"unknown {unknown}; known: {', '.join(TAGS)}"
    if len(set(value)) != len(value):
        return "lists a tag twice"
    return None


REQUIRED_FIELDS = ("format", "id", "name", "version", "authors")


def check_manifest(manifest: Any) -> List[Problem]:
    """The manifest rules; each problem's `where` is the field at fault.
    Unknown fields are ignored."""
    if not isinstance(manifest, dict):
        return [Problem(MANIFEST, "must be a JSON object")]
    problems: List[Problem] = []

    def check(name: str, why: Optional[str]) -> None:
        if why:
            problems.append(Problem(name, why))

    for name in REQUIRED_FIELDS:
        if name not in manifest:
            check(name, "missing (required)")
    fmt = manifest.get("format")
    if "format" in manifest:
        if not _is_int(fmt) or fmt < 1:
            check("format", f"must be {FORMAT}")
        elif fmt > FORMAT:
            check("format", f"{fmt} is newer than this tool reads ({FORMAT}); update the tools")
    own_id = manifest.get("id")
    if "id" in manifest:
        check("id", check_id(own_id))
    own_id = own_id if isinstance(own_id, str) else None
    for name, checker in (("name", check_name), ("version", check_version), ("authors", check_authors),
                          ("description", check_description), ("api", check_api), ("entry", check_entry),
                          ("homepage", check_https_url), ("license", check_license), ("tags", check_tags)):
        if name in manifest:
            check(name, checker(manifest[name]))
    if "entry" in manifest and "api" not in manifest:
        check("api", "missing: required with entry (the lowest T3SDK_API_VERSION the DLL needs)")
    if "requires" in manifest:
        check("requires", check_requires(manifest["requires"], own_id))
    if "conflicts" in manifest:
        check("conflicts", check_conflicts(manifest["conflicts"], own_id, manifest.get("requires")))
    return problems


def _unique_keys(pairs: List[Tuple[str, Any]]) -> Dict[str, Any]:
    out: Dict[str, Any] = {}
    for key, value in pairs:
        if key in out:
            raise ValueError(f"the key {key!r} appears twice")
        out[key] = value
    return out


def _no_constant(name: str) -> Any:
    raise ValueError(f"{name} is not JSON")


def load_json(data: bytes, where: str) -> Tuple[Any, List[Problem]]:
    """Strict JSON as the launcher reads it: UTF-8 without a byte-order mark,
    no duplicate keys, no NaN/Infinity. Returns (value or None, problems)."""
    if data.startswith(b"\xef\xbb\xbf"):
        return None, [Problem(where, "starts with a UTF-8 byte-order mark; save it as UTF-8 without BOM")]
    try:
        text = data.decode("utf-8")
    except UnicodeDecodeError as e:
        return None, [Problem(where, f"not UTF-8 ({e.reason} at byte {e.start})")]
    try:
        return json.loads(text, object_pairs_hook=_unique_keys, parse_constant=_no_constant), []
    except ValueError as e:
        return None, [Problem(where, f"not valid JSON: {e}")]


def load_manifest_file(path: Path) -> Tuple[Optional[Dict[str, Any]], List[Problem]]:
    manifest, problems = load_json(path.read_bytes(), MANIFEST)
    if problems:
        return None, problems
    problems = check_manifest(manifest)
    return (manifest if isinstance(manifest, dict) else None), problems


# --- package files ------------------------------------------------------------------------

_BAD_CHARS = frozenset('<>:"|?*\\')
_DEVICE_RE = re.compile(r"(con|prn|aux|nul|com[0-9]|lpt[0-9])", re.IGNORECASE)


def check_segment(segment: str) -> Optional[str]:
    """Why `segment` cannot be a file or folder name on Windows, or None."""
    if segment in ("", ".", ".."):
        return "empty, '.' or '..' path segment"
    bad = sorted({c for c in segment if c in _BAD_CHARS or ord(c) < 32})
    if bad:
        return f"characters not allowed in Windows names: {' '.join(repr(c) for c in bad)}"
    if segment[-1] in ". ":
        return "a name cannot end with a dot or a space on Windows"
    if _DEVICE_RE.fullmatch(segment.split(".")[0].rstrip(" ")):
        return "a reserved Windows device name"
    return None


def check_path(path: str) -> Optional[str]:
    """Why `path` (a name inside a package) is unsafe, or None: relative,
    '/'-separated, no '..', no drive letter, no empty segment, and every
    segment a valid Windows name."""
    if not path:
        return "empty name"
    if "\\" in path:
        return "uses '\\': paths in a package use '/'"
    if path.startswith("/"):
        return "absolute path"
    if re.match(r"[A-Za-z]:", path):
        return "drive letter"
    for segment in path.split("/"):
        why = check_segment(segment)
        if why:
            return why
    return None


@dataclass
class Entry:
    """A file of a package: its path inside the package ('/'-separated), its
    size, and for a folder the file on disk."""

    path: str
    size: int
    source: Optional[Path] = None


@dataclass
class Package:
    manifest: Optional[Dict[str, Any]]
    entries: List[Entry]
    problems: List[Problem] = field(default_factory=list)

    @property
    def errors(self) -> List[Problem]:
        return errors(self.problems)

    @property
    def warnings(self) -> List[Problem]:
        return warnings(self.problems)

    @property
    def file_name(self) -> str:
        """<id>-<version>.t3mod, the conventional name."""
        assert self.manifest is not None
        return f"{self.manifest['id']}-{self.manifest['version']}{PACKAGE_SUFFIX}"


def _mib(size: int) -> str:
    return f"{size / (1 << 20):.0f} MiB"


def check_package(entries: List[Entry], read: Callable[[str], bytes],
                  problems: Optional[List[Problem]] = None) -> Package:
    """The package rules over a list of files: safe paths, mod.json at the
    root and valid, something to install, the entry DLL present, nothing under
    files/System/, only .dds files directly in textures/. Warns about large
    and unusual files. `read(path)` returns the bytes of an entry."""
    problems = list(problems or [])
    safe: List[Entry] = []
    for e in entries:
        why = check_path(e.path)
        if why:
            problems.append(Problem(e.path, f"refused: {why}"))
        else:
            safe.append(e)

    seen: Dict[str, str] = {}
    folders = {e.path.lower().rsplit("/", 1)[0] for e in safe if "/" in e.path}
    folders |= {f.rsplit("/", i)[0] for f in folders for i in range(1, f.count("/") + 1)}
    for e in safe:
        key = e.path.lower()
        if key in seen:
            problems.append(Problem(e.path, f"same name as {seen[key]} (names are compared case-insensitively)"))
        elif key in folders:
            problems.append(Problem(e.path, "a file with the same name as a folder"))
        else:
            seen[key] = e.path

    manifest: Optional[Dict[str, Any]] = None
    root = {e.path.lower(): e for e in safe if "/" not in e.path}
    found = root.get(MANIFEST)
    if found is None:
        nested = [e.path for e in safe if e.path.lower().endswith("/" + MANIFEST)]
        hint = f" (found {nested[0]}: pack the folder's contents, not the folder)" if nested else ""
        problems.append(Problem(MANIFEST, f"missing at the package root{hint}"))
    elif found.size > MAX_MANIFEST_BYTES:
        problems.append(Problem(MANIFEST, f"larger than {MAX_MANIFEST_BYTES} bytes"))
    else:
        if found.path != MANIFEST:
            problems.append(Problem(found.path, f"name it {MANIFEST}, in lower case", warning=True))
        value, json_problems = load_json(read(found.path), MANIFEST)
        problems += json_problems
        if not json_problems:
            problems += check_manifest(value)
            manifest = value if isinstance(value, dict) else None

    content = {"files": 0, "textures": 0}
    total = 0
    for e in safe:
        total += e.size
        top, _, rest = e.path.partition("/")
        top = top.lower()
        suffix = os.path.splitext(e.path)[1].lower()
        if rest and top in content:
            content[top] += 1
        if top == "files" and rest:
            if rest.split("/", 1)[0].lower() == "system":
                problems.append(Problem(e.path, 'refused: files/System/ is not allowed; ship code as the '
                                                '"entry" DLL so it shows in the load order'))
            elif "/" not in rest:
                problems.append(Problem(e.path, "lands in the game's top folder", warning=True))
            elif suffix == ".dll":
                problems.append(Problem(e.path, 'a DLL under files/ is copied into the game, not loaded; '
                                                'mods ship code as the "entry" DLL', warning=True))
        elif top == "textures" and rest:
            if "/" in rest:
                problems.append(Problem(e.path, "refused: textures/ holds <texture name>.dds files, no folders"))
            elif suffix != ".dds":
                problems.append(Problem(e.path, "refused: textures/ holds only .dds files"))
        if suffix in EXECUTABLE_SUFFIXES:
            problems.append(Problem(e.path, "an executable or script: mods ship code as the entry DLL",
                                    warning=True))
        elif suffix in ARCHIVE_SUFFIXES:
            problems.append(Problem(e.path, "an archive: it is installed as it is, not unpacked", warning=True))
        if e.size == 0:
            problems.append(Problem(e.path, "empty file", warning=True))
        elif e.size > LARGE_FILE:
            problems.append(Problem(e.path, f"large file ({_mib(e.size)})", warning=True))
        if any(s.startswith(".") for s in e.path.split("/")):
            problems.append(Problem(e.path, "hidden file", warning=True))
    if total > LARGE_PACKAGE:
        problems.append(Problem("package", f"{_mib(total)} of files in all", warning=True))

    if manifest is not None:
        entry = manifest.get("entry")
        if isinstance(entry, str) and not check_entry(entry) and entry.lower() not in root:
            problems.append(Problem("entry", f"{entry} is not in the package: it belongs at the root, "
                                             f"next to {MANIFEST}"))
        if "entry" not in manifest and not content["files"] and not content["textures"]:
            problems.append(Problem("package", "nothing to install: no entry DLL, files/ or textures/"))
    return Package(manifest, safe, problems)


def _skipped(name: str, with_pdb: bool) -> bool:
    lower = name.lower()
    return lower in JUNK_NAMES or lower.endswith(PACKAGE_SUFFIX) or (lower.endswith(".pdb") and not with_pdb)


def read_folder(folder: Path, with_pdb: bool = False, exclude: Iterable[Path] = ()) -> Package:
    """A folder as `pack` would package it: junk skipped (JUNK_NAMES, packages
    left in it, *.pdb unless with_pdb), symbolic links refused."""
    folder = Path(folder)
    excluded = {Path(p).resolve() for p in exclude}
    problems: List[Problem] = []
    entries: List[Entry] = []
    for dirpath, dirnames, filenames in os.walk(folder):
        here = Path(dirpath)
        kept = []
        for d in sorted(dirnames):
            if d.lower() in JUNK_NAMES:
                continue
            if (here / d).is_symlink():
                problems.append(Problem((here / d).relative_to(folder).as_posix(), "refused: a symbolic link"))
                continue
            kept.append(d)
        dirnames[:] = kept
        for name in sorted(filenames):
            path = here / name
            rel = path.relative_to(folder).as_posix()
            if _skipped(name, with_pdb) or path.resolve() in excluded:
                continue
            if path.is_symlink():
                problems.append(Problem(rel, "refused: a symbolic link"))
                continue
            entries.append(Entry(rel, path.stat().st_size, path))

    def read(name: str) -> bytes:
        return (folder / name).read_bytes()

    return check_package(entries, read, problems)


def read_zip(path: Path) -> Package:
    """A .t3mod: its entries (directory entries aside) and the package rules,
    plus the zip's own: no encryption, stored or deflated, no links."""
    path = Path(path)
    try:
        archive = zipfile.ZipFile(path)
    except (zipfile.BadZipFile, OSError) as e:
        return Package(None, [], [Problem(path.name, f"not a readable zip file: {e}")])
    problems: List[Problem] = []
    with archive:
        infos: Dict[str, zipfile.ZipInfo] = {}
        entries: List[Entry] = []
        for info in archive.infolist():
            name = info.orig_filename  # as stored: zipfile rewrites '\' to '/' on Windows
            if info.flag_bits & 0x1:
                problems.append(Problem(name, "refused: encrypted"))
                continue
            if info.create_system == 3 and stat.S_ISLNK(info.external_attr >> 16):
                problems.append(Problem(name, "refused: a symbolic link"))
                continue
            if name.endswith("/"):  # a directory entry: nothing to install, but its name must be safe
                why = check_path(name[:-1])
                if why:
                    problems.append(Problem(name, f"refused: {why}"))
                continue
            if info.compress_type not in (zipfile.ZIP_STORED, zipfile.ZIP_DEFLATED):
                problems.append(Problem(name, f"refused: compression method {info.compress_type}; "
                                              "use deflate (or store)"))
                continue
            entries.append(Entry(name, info.file_size))
            infos[name] = info

        def read(name: str) -> bytes:
            with archive.open(infos[name]) as f:
                return f.read(MAX_MANIFEST_BYTES + 1)

        try:
            package = check_package(entries, read, problems)
        except (zipfile.BadZipFile, OSError, EOFError, RuntimeError, zlib.error) as e:  # a damaged manifest
            return Package(None, entries, problems + [Problem(path.name, f"damaged zip file: {e}")])
        for e in package.entries:  # every entry unpacks, with the right size and CRC
            try:
                with archive.open(infos[e.path]) as f:
                    while f.read(1 << 20):
                        pass
            except (zipfile.BadZipFile, OSError, EOFError, RuntimeError, zlib.error) as err:
                package.problems.append(Problem(e.path, f"damaged: {err}"))
        return package


def read_any(path: Path, with_pdb: bool = False) -> Package:
    """A folder or a .t3mod."""
    path = Path(path)
    return read_folder(path, with_pdb) if path.is_dir() else read_zip(path)


def write_package(package: Package, out: Path) -> None:
    """Zip a folder's package deterministically: entries sorted by path, fixed
    time and attributes, deflate, no directory entries. Written to a
    temporary name first, so a failure leaves no half package behind."""
    out = Path(out)
    tmp = out.with_name(out.name + ".tmp")
    with zipfile.ZipFile(tmp, "w", zipfile.ZIP_DEFLATED) as archive:
        for e in sorted(package.entries, key=lambda e: e.path):
            assert e.source is not None
            info = zipfile.ZipInfo(e.path, date_time=PACKAGE_TIME)
            info.compress_type = zipfile.ZIP_DEFLATED
            info.create_system = 3
            info.external_attr = PACKAGE_ATTR
            info.file_size = e.size  # lets zipfile decide on zip64 up front
            with e.source.open("rb") as src, archive.open(info, "w") as dst:
                while True:
                    chunk = src.read(1 << 20)
                    if not chunk:
                        break
                    dst.write(chunk)
    os.replace(tmp, out)


def sha256_file(path: Path) -> str:
    digest = hashlib.sha256()
    with Path(path).open("rb") as f:
        for chunk in iter(lambda: f.read(1 << 20), b""):
            digest.update(chunk)
    return digest.hexdigest()


def check_date(value: Any) -> Optional[str]:
    """A YYYY-MM-DD calendar date."""
    if isinstance(value, str) and re.fullmatch(r"[0-9]{4}-[0-9]{2}-[0-9]{2}", value):
        try:
            date.fromisoformat(value)
            return None
        except ValueError:
            pass
    return "must be a date, YYYY-MM-DD"
