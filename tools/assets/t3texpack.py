#!/usr/bin/env python3
"""Texture packs: replace textures inside the game's .ibt bundles.

A texture pack is a folder of DDS files named after the texture resources
they replace: `textures/<name>.dds` in a mod package (docs/mods.md).  Every
bundle in Content/T3/Maps that holds a replaced name (level bundles, Kernel_*
and MainMenu_*) is rebuilt from its original with new texture resources
(ibtwrite.py) and written into the game.

Usage:
  t3texpack.py list [<map or .ibt>] [--json]
      texture names with their format, size, mip count and usage, and the
      bundles that hold each name.  With a map, only the names it holds.
  t3texpack.py check --pack <dir> [--pack <dir> ...]
      every <dir>/textures/<name>.dds must name a texture somewhere and be a
      supported DDS; warns when its format or aspect ratio differs from the
      original's, or when it is larger.
  t3texpack.py apply --pack <dir> [--pack <dir> ...] [--dry-run]
      replace the textures (later packs win).  Each affected bundle is backed
      up once to build/assets/backup/ and rebuilt from that original; bundles
      patched before and no longer affected are restored.  Without packs it is
      restore.
  t3texpack.py restore [--dry-run]
      put every patched bundle back.
  t3texpack.py --selfcheck [<map or .ibt> ...]
      on the retail files: re-write each bundle unchanged, re-encode every
      texture from its own DDS, and compare with the original bytes.

A pack <dir> is a mod folder with a textures/ folder, or the textures folder
itself.  Exit status: 0 done (warnings allowed), 1 a problem was reported,
2 a bad command line.  apply and restore are the only commands that write to
the game folder; the record of what they did is build/assets/backup/t3texpack.json.
See docs/assets.md, section 3, for the format and the assumptions.
"""

from __future__ import annotations

import argparse
import hashlib
import json
import os
import shutil
import struct
import sys
from dataclasses import dataclass, field
from pathlib import Path
from typing import Dict, Iterable, List, Optional, Sequence, Set, Tuple

sys.path.insert(0, str(Path(__file__).resolve().parent))
from ibt import IBT, Resource  # noqa: E402
from ibtwrite import BlockWriter, LayoutError, compare_bundles, survey  # noqa: E402
from t3common import BUILD_DIR, content_dir, game_dir, resolve_map, run_cli  # noqa: E402
from t3texture import (MIP_HEAD_SIZE, TEXTURE_HEAD_PARTS, TEXTURE_HEAD_SIZE, TYPE_TEXTURE, USAGE,  # noqa: E402
                       DDSError, Mip, Texture, format_name, mip_size, parse_dds, parse_texture, texture_parts,
                       to_dds)
from upkgwrite import first_difference  # noqa: E402

BACKUP_DIR = BUILD_DIR / "backup"
MANIFEST = "t3texpack.json"
MANIFEST_FORMAT = 1
# Part of every bundle's recipe: raise it when the encoder's output changes, so
# that apply rebuilds bundles patched by an older version.
ENCODER_VERSION = 1


class TexPackError(Exception):
    """A problem that stops the command."""


class Report:
    """Output for the launcher's live view: progress on stdout, warnings and
    errors on stderr (prefixed), and counts for the summary."""

    def __init__(self, echo: bool = True) -> None:
        self.echo = echo
        self.errors = self.warnings = 0
        self.lines: List[str] = []

    def _emit(self, text: str, stream) -> None:
        self.lines.append(text)
        if self.echo:
            print(text, file=stream, flush=True)

    def info(self, text: str) -> None:
        self._emit(text, sys.stdout)

    def warn(self, text: str) -> None:
        self.warnings += 1
        self._emit(f"warning: {text}", sys.stderr)

    def error(self, text: str) -> None:
        self.errors += 1
        self._emit(f"error: {text}", sys.stderr)

    def text(self) -> str:
        return "\n".join(self.lines)


def _count(n: int, what: str) -> str:
    return f"{n} {what}" + ("" if n == 1 else "es" if what.endswith("s") else "s")


# --- texture heads (no pixel data read) ------------------------------------------------------

@dataclass
class TexInfo:
    """A texture resource as the table and its first 39 bytes describe it."""
    name: str
    index: int
    format: str
    width: int
    height: int
    mips: int
    usage: int
    usage_detail: int
    part_sizes: List[int]
    standard: bool  # the part layout parse_texture() reads and this tool rebuilds

    @property
    def usage_name(self) -> str:
        return USAGE.get(self.usage, str(self.usage))


def texture_head(ibt: IBT, res: Resource) -> TexInfo:
    sizes = ibt.parts(res)
    head = ibt.read_prefix(res, TEXTURE_HEAD_SIZE)
    if len(head) < TEXTURE_HEAD_SIZE or tuple(sizes[:12]) != TEXTURE_HEAD_PARTS:
        return TexInfo(res.name, res.index, "?", 0, 0, 0, 0, 0, sizes, False)
    mips, usage, detail, width, height = struct.unpack_from("<5I", head, 5)
    standard = (head[0] == 1 and len(sizes) == 12 + 6 * mips
                and all(sizes[12 + 6 * i:16 + 6 * i] == [4, 4, 4, 4] for i in range(mips)))
    return TexInfo(res.name, res.index, format_name(head[1:5]), width, height, mips, usage, detail, sizes,
                   standard)


# --- mip padding ---------------------------------------------------------------------------------
#
# Each mip's data is preceded by a padding part.  Its rule is not known from
# the engine; the candidates are "pad the data to a multiple of N bytes",
# counted from the start of the resource or from the first mip header, for N
# a power of two up to 4096.  The rule for a bundle is the one that explains
# most of its textures' padding parts (they pin it down: every mip of a full
# chain is a constraint); a tie, as when a bundle only has single-mip
# textures, goes to the rule that explains most textures in all the bundles.
# A texture is only replaced when its own original follows the rule.
# --selfcheck prints the rule and how many textures it explains.

@dataclass(frozen=True)
class PadRule:
    align: int
    frame: str  # "resource": from the resource's first byte; "chain": from the first mip header

    def pad(self, pos: int) -> int:
        origin = 0 if self.frame == "resource" else TEXTURE_HEAD_SIZE
        return (-(pos - origin)) % self.align

    def __str__(self) -> str:
        if self.align == 1:
            return "no padding"
        where = "the start of the resource" if self.frame == "resource" else "the first mip header"
        return f"{self.align}-byte alignment from {where}"


ALL_RULES = [PadRule(1, "resource")] + [PadRule(1 << k, f) for k in range(1, 13) for f in ("resource", "chain")]


def pad_observations(part_sizes: Sequence[int]) -> List[Tuple[int, int]]:
    """(position before the padding part, its size) for each mip."""
    obs = []
    pos = TEXTURE_HEAD_SIZE
    for i in range((len(part_sizes) - 12) // 6):
        base = 12 + 6 * i
        pos += MIP_HEAD_SIZE
        obs.append((pos, part_sizes[base + 4]))
        pos += part_sizes[base + 4] + part_sizes[base + 5]
    return obs


def rules_for(part_sizes: Sequence[int]) -> Set[PadRule]:
    obs = pad_observations(part_sizes)
    return {r for r in ALL_RULES if all(r.pad(pos) == pad for pos, pad in obs)}


@dataclass
class RuleFinding:
    rule: Optional[PadRule]
    explained: int  # textures the rule explains
    total: int  # textures with the standard layout and at least one mip
    also: List[PadRule] = field(default_factory=list)  # other rules explaining as many


def rule_counts(textures: Iterable[TexInfo]) -> Tuple[Dict[PadRule, int], int]:
    """How many of these textures each rule explains, and how many count
    (the standard layout, at least one mip)."""
    counts: Dict[PadRule, int] = {r: 0 for r in ALL_RULES}
    total = 0
    for t in textures:
        if not t.standard or not t.mips:
            continue
        total += 1
        for r in rules_for(t.part_sizes):
            counts[r] += 1
    return counts, total


def find_rule(textures: Iterable[TexInfo], prior: Optional[Dict[PadRule, int]] = None) -> RuleFinding:
    """The padding rule that explains the most of these textures.  Ties go to
    the rule with the higher count in `prior` (all the install's textures),
    then to the larger alignment, then to counting from the resource start."""
    counts, total = rule_counts(textures)
    if not total:
        return RuleFinding(None, 0, 0)
    prior = prior or {}
    ranked = sorted(ALL_RULES, key=lambda r: (-counts[r], -prior.get(r, 0), -r.align, r.frame != "resource"))
    best = ranked[0]
    if not counts[best]:
        return RuleFinding(None, 0, total)
    return RuleFinding(best, counts[best], total, [r for r in ranked[1:] if counts[r] == counts[best]
                                                   and prior.get(r, 0) == prior.get(best, 0)])


def encode_replacement(orig: Texture, new: Texture, rule: PadRule) -> Texture:
    """The texture resource for `new` (a parsed DDS) in place of `orig`:
    format, size and mips from the DDS; usage, usage detail, version and the
    two bytes from the original; the second size follows the first when it
    equalled it in the original (else it is kept); mip levels count from 0,
    the total is the sum of the mip sizes, and each padding part (zero bytes)
    follows `rule`."""
    size2 = (new.width, new.height) if orig.size2 == (orig.width, orig.height) else orig.size2
    tex = Texture(orig.name, new.format, new.width, new.height, orig.usage, orig.usage_detail,
                  version=orig.version, size2=size2, flag_bytes=orig.flag_bytes)
    pos = TEXTURE_HEAD_SIZE
    for i, m in enumerate(new.mips):
        pos += MIP_HEAD_SIZE
        pad = rule.pad(pos)
        tex.mips.append(Mip(m.width, m.height, m.data, i, bytes(pad)))
        pos += pad + len(m.data)
    tex.total = sum(len(m.data) for m in tex.mips)
    return tex


# --- files -----------------------------------------------------------------------------------------

def file_id(path: Path) -> Optional[Dict[str, object]]:
    """{"size", "sha256"} of a file, or None when it does not exist."""
    if not path.is_file():
        return None
    h = hashlib.sha256()
    with open(path, "rb") as f:
        for chunk in iter(lambda: f.read(1 << 20), b""):
            h.update(chunk)
    return {"size": path.stat().st_size, "sha256": h.hexdigest()}


def data_id(data: bytes) -> Dict[str, object]:
    return {"size": len(data), "sha256": hashlib.sha256(data).hexdigest()}


def _write_atomic(path: Path, data: bytes) -> None:
    """Write through a temporary file next to `path`, so it is never half written."""
    tmp = path.with_name(path.name + ".t3texpack.tmp")
    try:
        with open(tmp, "wb") as f:
            f.write(data)
            f.flush()
            os.fsync(f.fileno())
        os.replace(tmp, path)
    finally:
        if tmp.exists():
            tmp.unlink()


def _copy_atomic(src: Path, dst: Path) -> None:
    tmp = dst.with_name(dst.name + ".t3texpack.tmp")
    try:
        shutil.copy2(src, tmp)
        os.replace(tmp, dst)
    finally:
        if tmp.exists():
            tmp.unlink()


def maps_dir(game: Path) -> Path:
    return content_dir(game) / "Maps"


def game_bundles(game: Path) -> List[Path]:
    d = maps_dir(game)
    if not d.is_dir():
        return []
    return sorted((f for f in d.iterdir() if f.suffix.lower() == ".ibt" and f.is_file()), key=lambda f: f.name.lower())


def rel_key(game: Path, path: Path) -> Tuple[str, str]:
    """(record key, path as stored) for a bundle in the game folder."""
    rel = path.relative_to(game).as_posix()
    return rel.lower(), rel


# --- the record of patched bundles ------------------------------------------------------------------

class State:
    """build/assets/backup/t3texpack.json and the backups next to it.

    A record per patched bundle: its path, the original's and the installed
    file's size and SHA-256, the recipe (packs and encoder) it was built
    from, and which pack file replaced each texture.  The record is saved
    before the game's file is replaced, and the previous installed file is
    remembered until the new one is in place, so an interrupted run is
    recognised the next time."""

    def __init__(self, game: Path, backup_dir: Path = BACKUP_DIR, report: Optional[Report] = None) -> None:
        self.game, self.dir = game, backup_dir
        self.path = backup_dir / MANIFEST
        self.doc = {"format": MANIFEST_FORMAT, "tool": "t3texpack", "game": str(game.resolve()), "bundles": {}}
        if self.path.is_file():
            try:
                doc = json.loads(self.path.read_text(encoding="utf-8"))
            except ValueError as ex:
                raise TexPackError(f"{self.path} is not valid JSON ({ex}); it records which bundles are "
                                   "patched: fix it, or restore the bundles with the game's file check") from ex
            if not isinstance(doc, dict) or doc.get("format") != MANIFEST_FORMAT or not isinstance(
                    doc.get("bundles"), dict):
                raise TexPackError(f"{self.path}: not a t3texpack record (format {MANIFEST_FORMAT})")
            for key, rec in doc["bundles"].items():
                if not (isinstance(rec, dict) and isinstance(rec.get("path"), str)
                        and all(isinstance(rec.get(k), dict) for k in ("original", "installed"))):
                    raise TexPackError(f"{self.path}: the record of {key} is damaged")
            self.doc = doc
        recorded = self.doc.get("game") or ""
        if self.records() and os.path.normcase(recorded) != os.path.normcase(str(game.resolve())):
            if Path(recorded).is_dir():
                raise TexPackError(f"{self.path} records bundles patched in another game folder, {recorded}: "
                                   f"run `t3texpack.py restore --game-dir \"{recorded}\"` first")
            if report:
                report.info(f"note: the recorded game folder {recorded} is gone; using {game}")
        self.doc["game"] = str(game.resolve())

    def records(self) -> Dict[str, dict]:
        return self.doc["bundles"]

    def record(self, key: str) -> Optional[dict]:
        return self.records().get(key)

    def backup_path(self, stored: str) -> Path:
        return self.dir / Path(stored).name

    def save(self) -> None:
        self.dir.mkdir(parents=True, exist_ok=True)
        _write_atomic(self.path, (json.dumps(self.doc, indent=1, sort_keys=True) + "\n").encode("utf-8"))

    def set(self, key: str, rec: Optional[dict]) -> None:
        if rec is None:
            self.records().pop(key, None)
        else:
            self.records()[key] = rec
        self.save()


class Foreign(TexPackError):
    """A bundle changed by something other than this tool: left alone."""


def original_of(state: State, key: str, path: Path, stored: str,
                dry_run: bool = False) -> Tuple[Path, Optional[Dict[str, object]]]:
    """Where a bundle's original is: the game's file, or the backup.  Returns
    (path, the game file's id).  Raises Foreign or TexPackError when neither
    can be trusted.  A changed file whose backup was deleted becomes the new
    original (its record is dropped, except in a dry run)."""
    rec = state.record(key)
    cur = file_id(path)
    backup = state.backup_path(stored)
    if rec is None:
        if cur is None:
            raise TexPackError(f"{stored}: not in the game folder")
        if backup.exists():
            if file_id(backup) == cur:
                return path, cur
            raise TexPackError(f"{stored}: a backup {backup} exists that t3texpack has no record of, and it "
                               "differs from the game's file. If the game's file is the original, delete the "
                               "backup and run again")
        return path, cur
    known = [rec.get("installed"), rec.get("previous")]
    if cur == rec["original"]:
        return path, cur
    backup_ok = file_id(backup) == rec["original"]
    if cur is None or cur in known:
        if backup_ok:
            return backup, cur
        raise TexPackError(f"{stored}: the backup of the original ({backup}) is missing or damaged, so the "
                           "bundle cannot be rebuilt or restored. Let the game's launcher verify the game "
                           "files, then run again")
    if not backup.exists():
        if not dry_run:
            state.set(key, None)
        return path, cur
    raise Foreign(f"{stored} was changed outside t3texpack since it was patched (it is neither the original nor "
                  f"the patched file): left alone. If a game update or another tool replaced it on purpose, "
                  f"delete {backup} to take the new file as the original")


# --- packs -------------------------------------------------------------------------------------------

@dataclass
class PackFile:
    name: str  # the texture name, from the file name
    path: Path
    pack: Path
    order: int
    sha256: str = ""
    tex: Optional[Texture] = None
    error: Optional[str] = None

    @property
    def key(self) -> str:
        return self.name.lower()

    @property
    def label(self) -> str:
        return _label(self.pack, self.path)


def _label(pack: Path, f: Path) -> str:
    """A pack file as "<pack folder name>/textures/<file>", for messages."""
    try:
        return f"{pack.resolve().name}/{f.relative_to(pack).as_posix()}"
    except ValueError:
        return str(f)


def pack_folder(d: Path) -> Optional[Path]:
    """A pack's DDS folder: <d>/textures, or <d> itself when it is not a mod
    folder (no mod.json).  None for a mod folder without textures."""
    t = d / "textures"
    if t.is_dir():
        return t
    return None if (d / "mod.json").is_file() else d


def load_packs(dirs: Sequence[Path], report: Report) -> Tuple[Dict[str, PackFile], List[PackFile]]:
    """Every pack's DDS files (errors reported), and the winner for each name
    (the last pack that provides it)."""
    files: List[PackFile] = []
    for order, d in enumerate(dirs):
        if not d.is_dir():
            report.error(f"{d}: no such pack folder")
            continue
        folder = pack_folder(d)
        if folder is None:
            report.warn(f"{d}: a mod folder without a textures/ folder: nothing to replace")
            continue
        seen: Dict[str, PackFile] = {}
        n = 0
        for f in sorted(folder.iterdir(), key=lambda p: p.name.lower()):
            if f.is_dir():
                report.warn(f"{_label(d, f)}: folders inside a pack are ignored")
                continue
            if f.suffix.lower() != ".dds":
                report.warn(f"{_label(d, f)}: not a .dds file, ignored")
                continue
            pf = PackFile(f.name[:-4], f, d, order)
            if pf.key in seen:
                report.error(f"{pf.label}: the pack names texture {pf.name!r} twice ({seen[pf.key].path.name})")
                continue
            seen[pf.key] = pf
            n += 1
            data = f.read_bytes()
            pf.sha256 = hashlib.sha256(data).hexdigest()
            try:
                pf.tex = parse_dds(data, pf.name)
            except DDSError as ex:
                pf.error = str(ex)
                report.error(f"{pf.label}: {ex}")
            files.append(pf)
        if not n:
            report.warn(f"{d}: no .dds files in {folder}")
    winners: Dict[str, PackFile] = {}
    for pf in files:
        winners[pf.key] = pf
    return winners, files


# --- the game's bundles ------------------------------------------------------------------------------

@dataclass
class Bundle:
    key: str
    stored: str  # path relative to the game folder
    path: Path  # the game's file
    source: Path  # where the original was read from (the backup while patched)
    textures: List[TexInfo]
    patched: bool

    @property
    def name(self) -> str:
        return self.path.name

    def rule(self, prior: Optional[Dict[PadRule, int]] = None) -> RuleFinding:
        return find_rule(self.textures, prior)


def read_bundle_textures(path: Path) -> List[TexInfo]:
    with IBT(path) as ibt:
        return [texture_head(ibt, r) for r in ibt.of_type(TYPE_TEXTURE)]


def scan(game: Path, state: Optional[State], report: Report) -> List[Bundle]:
    """The game's bundles with their original textures (read from the backup
    when a bundle is patched and its backup is there)."""
    out = []
    for path in game_bundles(game):
        key, stored = rel_key(game, path)
        rec = state.record(key) if state else None
        source = path
        if rec is not None:
            backup = state.backup_path(stored)
            if backup.is_file() and backup.stat().st_size == rec["original"]["size"]:
                source = backup
        try:
            textures = read_bundle_textures(source)
        except (ValueError, OSError, struct.error) as ex:
            report.warn(f"{stored}: cannot read it: {ex}")
            continue
        out.append(Bundle(key, stored, path, source, textures, rec is not None))
    return out


def index_names(bundles: Sequence[Bundle]) -> Dict[str, List[Tuple[Bundle, TexInfo]]]:
    idx: Dict[str, List[Tuple[Bundle, TexInfo]]] = {}
    for b in bundles:
        for t in b.textures:
            idx.setdefault(t.name.lower(), []).append((b, t))
    return idx


# --- list ---------------------------------------------------------------------------------------------

def cmd_list(game: Optional[Path], only: Optional[str], as_json: bool, report: Report,
             backup_dir: Path = BACKUP_DIR) -> int:
    state = None
    bundles: List[Bundle] = []
    if game is not None:
        state = State(game, backup_dir, report)
        bundles = scan(game, state, report)
    names_in: Optional[Set[str]] = None
    if only:
        p = Path(only)
        if not p.is_file():
            if game is None:
                raise TexPackError("game folder not found: pass --game-dir or set T3_GAME_DIR, or give a .ibt file")
            p = resolve_map(game, only, ".ibt")
        mine = [b for b in bundles if b.path.resolve() == p.resolve()]
        if mine:
            names_in = {t.name.lower() for t in mine[0].textures}
        else:
            textures = read_bundle_textures(p)
            bundles = [Bundle(p.name.lower(), p.name, p, p, textures, False)]
    rows: Dict[Tuple[str, str, int, int, int, int, int], dict] = {}
    for b in bundles:
        for t in b.textures:
            if names_in is not None and t.name.lower() not in names_in:
                continue
            k = (t.name.lower(), t.format, t.width, t.height, t.mips, t.usage, t.usage_detail)
            row = rows.setdefault(k, {"name": t.name, "format": t.format, "width": t.width, "height": t.height,
                                      "mips": t.mips, "usage": t.usage_name, "usage_detail": t.usage_detail,
                                      "replaceable": t.standard, "bundles": []})
            if b.name not in row["bundles"]:
                row["bundles"].append(b.name)
            row["replaceable"] = row["replaceable"] and t.standard
    ordered = sorted(rows.values(), key=lambda r: (r["name"].lower(), r["bundles"]))
    names = {r["name"].lower() for r in ordered}
    used = {bn for r in ordered for bn in r["bundles"]}
    if as_json:
        doc = {"format": 1, "textures": ordered,
               "bundles": [{"file": b.name, "path": b.stored, "textures": len(b.textures), "patched": b.patched}
                           for b in bundles if b.name in used]}
        print(json.dumps(doc, indent=1))
        return 0
    for r in ordered:
        size = f"{r['width']}x{r['height']}"
        note = "" if r["replaceable"] else "  (layout not supported)"
        report.info(f"{r['name']:40s} {r['format']:9s} {size:>11s} mips {r['mips']:2d}  {r['usage']:11s} "
                    f"{', '.join(r['bundles'])}{note}")
    patched = [b.name for b in bundles if b.patched]
    if patched:
        report.info(f"patched now (originals listed): {', '.join(patched)}")
    report.info(f"list: {_count(len(names), 'texture name')} in {_count(len(used), 'bundle')}")
    return 0


# --- check --------------------------------------------------------------------------------------------

@dataclass
class Plan:
    """Which pack file replaces which resources in which bundle."""
    winners: Dict[str, PackFile]
    bundles: Dict[str, Bundle] = field(default_factory=dict)
    targets: Dict[str, List[Tuple[TexInfo, PackFile]]] = field(default_factory=dict)  # bundle key -> list
    rules: Dict[str, PadRule] = field(default_factory=dict)


def plan_packs(game: Path, dirs: Sequence[Path], state: State, report: Report, warnings: bool) -> Plan:
    """Load the packs and match them against the original bundles.  Reports
    errors (unknown names, bad files, layouts that cannot be rebuilt) and,
    with `warnings`, the differences from the originals."""
    winners, files = load_packs(dirs, report)
    bundles = scan(game, state, report)
    idx = index_names(bundles)
    plan = Plan(winners, {b.key: b for b in bundles})
    rules: Dict[str, RuleFinding] = {}
    prior, _ = rule_counts(t for b in bundles for t in b.textures)
    for pf in files:
        where = idx.get(pf.key)
        if not where:
            report.error(f"{pf.label}: no texture named {pf.name!r} in any bundle (see `t3texpack.py list`)")
            continue
        winner = winners[pf.key]
        if winner is not pf:
            report.info(f"{pf.label}: overridden by {winner.label} (a later pack)")
            continue
        if pf.tex is None:
            continue
        diffs: Dict[str, List[str]] = {}
        for b, t in where:
            if not t.standard:
                report.error(f"{pf.label}: {t.name} in {b.name} has a texture layout this tool cannot rebuild")
                continue
            if b.key not in rules:
                rules[b.key] = b.rule(prior)
            finding = rules[b.key]
            if finding.rule is None or finding.rule not in rules_for(t.part_sizes):
                report.error(f"{pf.label}: {t.name} in {b.name}: its mip padding follows no rule that the other "
                             "textures of the bundle share, so it cannot be rebuilt (run --selfcheck)")
                continue
            plan.rules[b.key] = finding.rule
            plan.targets.setdefault(b.key, []).append((t, pf))
            new = pf.tex
            notes = []
            if new.format != t.format:
                notes.append(f"is {new.format}, the original is {t.format}")
            if new.width * t.height != new.height * t.width:
                notes.append(f"is {new.width}x{new.height}, the original {t.width}x{t.height} has another "
                             "aspect ratio")
            if new.width > t.width or new.height > t.height:
                notes.append(f"is {new.width}x{new.height}, larger than the original {t.width}x{t.height}")
            if notes:
                diffs.setdefault("; ".join(notes), []).append(b.name)
        if warnings:
            for text, names in diffs.items():
                report.warn(f"{pf.label}: {text} (in {', '.join(names)})")
    return plan


def cmd_check(game: Path, dirs: Sequence[Path], report: Report, backup_dir: Path = BACKUP_DIR) -> int:
    if not dirs:
        raise TexPackError("give at least one --pack <dir>")
    state = State(game, backup_dir, report)
    plan = plan_packs(game, dirs, state, report, warnings=True)
    n_res = sum(len(v) for v in plan.targets.values())
    status = "FAILED" if report.errors else "ok"
    report.info(f"check: {status}: {_count(len(plan.winners), 'texture')} from {_count(len(dirs), 'pack')}, "
                f"{_count(n_res, 'resource')} in {_count(len(plan.targets), 'bundle')}; "
                f"{_count(report.errors, 'error')}, {_count(report.warnings, 'warning')}")
    return 1 if report.errors else 0


# --- apply and restore ----------------------------------------------------------------------------------

def recipe(targets: Sequence[Tuple[TexInfo, PackFile]], rule: PadRule) -> str:
    items = sorted({(pf.key, pf.sha256) for _, pf in targets})
    blob = json.dumps({"encoder": ENCODER_VERSION, "rule": [rule.align, rule.frame], "textures": items})
    return hashlib.sha256(blob.encode()).hexdigest()


def rebuild(source: Path, targets: Sequence[Tuple[TexInfo, PackFile]],
            rule: PadRule) -> Tuple[bytes, bytes, List[str]]:
    """The original bundle's bytes, the rebuilt ones, and the writer's notes.
    The new file is checked by reading it back (ibtwrite.compare_bundles, and
    parse_texture on every replaced resource).  Raises TexPackError."""
    w = BlockWriter(source)
    wanted: Dict[int, Texture] = {}
    for info, pf in targets:
        res = w.resources[info.index] if info.index < len(w.resources) else None
        if res is None or res.type != TYPE_TEXTURE or res.name != info.name:
            raise TexPackError(f"{source.name} changed while it was being read (resource {info.index} is not "
                               f"{info.name}): run again")
        try:
            orig = parse_texture(res, w.parts(res.index))
        except (ValueError, EOFError, struct.error) as ex:
            raise TexPackError(f"{source.name}: {res.name}: the original does not parse: {ex}") from ex
        assert pf.tex is not None
        new = encode_replacement(orig, pf.tex, rule)
        w.replace(res.index, texture_parts(new))
        wanted[res.index] = new
    data = w.write()
    problems = compare_bundles(w.data, data, w.replaced_entries(), source.name)
    with IBT(source.name, data=data) as check:
        for i, want in wanted.items():
            r = check.resources[i]
            try:
                got = parse_texture(r, check.split(r))
            except (ValueError, EOFError, struct.error) as ex:
                problems.append(f"{r.name}: the new resource does not parse: {ex}")
                continue
            if (got.format, got.width, got.height, [m.data for m in got.mips]) != (
                    want.format, want.width, want.height, [m.data for m in want.mips]):
                problems.append(f"{r.name}: the new resource does not read back as the DDS")
    if problems:
        raise TexPackError(f"{source.name}: the rebuilt bundle does not check out:\n  " + "\n  ".join(problems))
    return w.data, data, w.notes


def ensure_backup(state: State, stored: str, source: Path, original: Dict[str, object]) -> None:
    """Copy the original to the backup folder, unless it is there already."""
    backup = state.backup_path(stored)
    if source == backup or file_id(backup) == original:
        return
    state.dir.mkdir(parents=True, exist_ok=True)
    _copy_atomic(source, backup)
    if file_id(backup) != original:
        raise TexPackError(f"{stored}: the backup {backup} does not match the original after copying")


def patch_bundle(state: State, b: Bundle, targets: Sequence[Tuple[TexInfo, PackFile]], rule: PadRule,
                 report: Report, dry_run: bool) -> str:
    """Bring one bundle to the plan.  Returns "patched" or "unchanged"."""
    want = recipe(targets, rule)
    rec = state.record(b.key)
    if rec is not None and rec.get("recipe") == want and not rec.get("previous"):
        if file_id(b.path) == rec.get("installed"):
            return "unchanged"
    source, cur = original_of(state, b.key, b.path, b.stored, dry_run)
    original_bytes, data, notes = rebuild(source, targets, rule)
    original = data_id(original_bytes)
    for n in notes:
        report.info(f"note: {b.stored}: {n}")
    rec = state.record(b.key)
    names = sorted({t.name for t, _ in targets}, key=str.lower)
    what = f"{b.stored}: {_count(len(names), 'texture')} ({', '.join(names[:6])}{', ...' if len(names) > 6 else ''})"
    if dry_run:
        report.info(f"would patch {what}")
        return "patched"
    ensure_backup(state, b.stored, source, original)
    installed = data_id(data)
    new_rec = {"path": b.stored, "backup": state.backup_path(b.stored).name, "original": original,
               "installed": installed, "recipe": want, "rule": str(rule),
               "textures": {t.name: {"pack": str(pf.pack), "file": pf.path.name, "sha256": pf.sha256}
                            for t, pf in targets}}
    if rec is not None and cur not in (None, original, installed) and cur in (rec.get("installed"),
                                                                               rec.get("previous")):
        new_rec["previous"] = cur  # the patched file the game holds, recognised until the new one is in place
    state.set(b.key, new_rec)
    try:
        _write_atomic(b.path, data)
    except OSError as ex:
        state.set(b.key, rec)  # the game still holds what it held before
        raise TexPackError(f"cannot write {b.path}: {ex} (is the game running?)") from ex
    new_rec.pop("previous", None)
    state.set(b.key, new_rec)
    report.info(f"patched {what}")
    return "patched"


def restore_bundle(state: State, key: str, report: Report, dry_run: bool) -> str:
    """Put one recorded bundle back from its backup, then drop its record and
    the backup (the game holds the original again).  Returns "restored" or
    "original".  Raises Foreign or TexPackError."""
    rec = state.record(key)
    assert rec is not None
    stored = rec["path"]
    path = state.game / stored
    backup = state.backup_path(stored)
    cur = file_id(path)

    def forget() -> None:
        state.set(key, None)
        if backup.is_file() and file_id(backup) == rec["original"]:
            backup.unlink()

    if cur == rec["original"]:
        if not dry_run:
            forget()
        report.info(f"{stored}: already the original")
        return "original"
    if cur is not None and cur not in (rec.get("installed"), rec.get("previous")):
        if backup.exists():
            raise Foreign(f"{stored} was changed outside t3texpack since it was patched (it is neither the "
                          f"original nor the patched file): left alone. If a game update or another tool "
                          f"replaced it on purpose, delete {backup} to accept it")
        if not dry_run:
            state.set(key, None)
        report.warn(f"{stored} was changed outside t3texpack and its backup is gone: left as it is, record dropped")
        return "original"
    if file_id(backup) != rec["original"]:
        raise TexPackError(f"{stored}: the backup of the original ({backup}) is missing or damaged. Let the game's "
                           "launcher verify the game files to get the original back")
    if dry_run:
        report.info(f"would restore {stored}")
        return "restored"
    try:
        _copy_atomic(backup, path)
    except OSError as ex:
        raise TexPackError(f"cannot write {path}: {ex} (is the game running?)") from ex
    if file_id(path) != rec["original"]:
        raise TexPackError(f"{stored}: the restored file does not match the original")
    forget()
    report.info(f"restored {stored}")
    return "restored"


def cmd_apply(game: Path, dirs: Sequence[Path], report: Report, backup_dir: Path = BACKUP_DIR,
              dry_run: bool = False) -> int:
    state = State(game, backup_dir, report)
    if not dirs:
        report.info("apply: no packs, so every patched bundle is restored")
        return cmd_restore(game, report, backup_dir, dry_run, label="apply")
    plan = plan_packs(game, dirs, state, report, warnings=False)
    if report.errors:
        report.info(f"apply: FAILED: {_count(report.errors, 'error')}; nothing was written")
        return 1
    counts = {"patched": 0, "unchanged": 0, "restored": 0, "original": 0, "left": 0}
    for key in sorted(plan.targets):
        b = plan.bundles[key]
        try:
            counts[patch_bundle(state, b, plan.targets[key], plan.rules[key], report, dry_run)] += 1
        except Foreign as ex:
            counts["left"] += 1
            report.error(str(ex))
        except (TexPackError, LayoutError) as ex:
            report.error(str(ex))
    for key in sorted(k for k in state.records() if k not in plan.targets):
        try:
            counts[restore_bundle(state, key, report, dry_run)] += 1
        except Foreign as ex:
            counts["left"] += 1
            report.error(str(ex))
        except TexPackError as ex:
            report.error(str(ex))
    n_tex = len({pf.key for v in plan.targets.values() for _, pf in v})
    parts = [f"{_count(counts['patched'], 'bundle')} {'to patch' if dry_run else 'patched'}",
             f"{counts['unchanged']} unchanged"]
    if counts["restored"] or counts["original"]:
        parts.append(f"{counts['restored'] + counts['original']} {'to restore' if dry_run else 'restored'}")
    if counts["left"]:
        parts.append(f"{counts['left']} left alone")
    status = "FAILED" if report.errors else "dry run" if dry_run else "ok"
    report.info(f"apply: {status}: {_count(n_tex, 'texture')} from {_count(len(dirs), 'pack')}; "
                + ", ".join(parts))
    return 1 if report.errors else 0


def cmd_restore(game: Path, report: Report, backup_dir: Path = BACKUP_DIR, dry_run: bool = False,
                label: str = "restore") -> int:
    state = State(game, backup_dir, report)
    keys = sorted(state.records())
    if not keys:
        report.info(f"{label}: ok: nothing to restore")
        return 0
    done = left = 0
    for key in keys:
        try:
            restore_bundle(state, key, report, dry_run)
            done += 1
        except Foreign as ex:
            left += 1
            report.error(str(ex))
        except TexPackError as ex:
            report.error(str(ex))
    status = "FAILED" if report.errors else "dry run" if dry_run else "ok"
    report.info(f"{label}: {status}: {_count(done, 'bundle')} {'to restore' if dry_run else 'restored'}"
                + (f", {left} left alone" if left else ""))
    return 1 if report.errors else 0


# --- selfcheck ----------------------------------------------------------------------------------------

HEAD_FIELDS = ["version", "format", "mip count", "usage", "usage detail", "width", "height", "second width",
               "second height", "total mip bytes", "byte 1", "byte 2"]
MIP_FIELDS = ["mip level", "mip width", "mip height", "mip size", "mip padding", "mip data"]


def part_field(i: int) -> str:
    return HEAD_FIELDS[i] if i < 12 else MIP_FIELDS[(i - 12) % 6]


def _first_part_diff(a: Sequence[bytes], b: Sequence[bytes]) -> Optional[str]:
    if len(a) != len(b):
        return "part count"
    for i, (x, y) in enumerate(zip(a, b)):
        if x != y:
            f = part_field(i)
            if f == "mip padding":
                return f + (" (length)" if len(x) != len(y) else " (bytes are not zero)")
            return f
    return None


def selfcheck_bundle(path: Path, report: Report, prior: Optional[Dict[PadRule, int]] = None) -> bool:
    """Check the writer and the encoder on one retail bundle (see --selfcheck)."""
    ok = True
    try:
        w = BlockWriter(path)
    except (LayoutError, OSError) as ex:
        report.error(f"{path.name}: cannot lay it out: {ex}")
        return False
    textures = [texture_head(w.ibt, r) for r in w.ibt.of_type(TYPE_TEXTURE)]
    report.info(f"{path.name}: {_count(len(w.resources), 'resource')}, {_count(len(textures), 'texture')}, "
                f"{len(w.data):,} bytes")
    facts = survey(w)
    report.info("  layout, as the writer assumes: "
                + ("all hold" if all(h for _, h in facts) else "; ".join(f"NO: {s}" for s, h in facts if not h)))
    out = w.write()
    d = first_difference(w.data, out)
    del out  # the bundle can be large
    if d is None:
        report.info("  written back unchanged: identical")
    else:
        ok = False
        report.error(f"{path.name}: written back unchanged, it DIFFERS at {d:#x} ({w.locate(d)})")

    finding = find_rule(textures, prior)
    if finding.rule is None:
        if finding.total:
            ok = False
            report.error(f"{path.name}: no padding rule explains the mips of any of its {finding.total} textures")
        else:
            report.info("  mip padding: no textures")
        return ok
    also = f" (as well: {', '.join(str(r) for r in finding.also)})" if finding.also else ""
    report.info(f"  mip padding: {finding.rule}, explains {finding.explained} of {finding.total} textures{also}")
    if finding.explained != finding.total:
        ok = False
        report.error(f"{path.name}: {finding.total - finding.explained} textures do not follow the padding rule")

    same = skipped = 0
    fields: Dict[str, List[str]] = {}
    rebuilt: Dict[int, List[bytes]] = {}
    second: Dict[str, List[str]] = {"equal": [], "zero": [], "other": []}  # the second width and height
    for info in textures:
        if not info.standard:
            skipped += 1
            fields.setdefault("(layout not supported)", []).append(info.name)
            continue
        res = w.resources[info.index]
        parts = w.parts(info.index)
        try:
            tex = parse_texture(res, parts)
        except (ValueError, EOFError, struct.error) as ex:
            fields.setdefault(f"texture parsing ({ex})", []).append(info.name)
            continue
        kind = "equal" if tex.size2 == (tex.width, tex.height) else "zero" if tex.size2 == (0, 0) else "other"
        second[kind].append(f"{tex.name} {tex.width}x{tex.height}/{tex.size2[0]}x{tex.size2[1]}")
        try:
            dds = to_dds(tex)
        except ValueError:
            skipped += 1
            fields.setdefault(f"(skipped, {tex.format} has no DDS mapping)", []).append(info.name)
            continue
        try:
            new = parse_dds(dds, tex.name)
        except DDSError as ex:
            skipped += 1
            fields.setdefault(f"(cannot be replaced: its DDS export is refused: {ex})", []).append(info.name)
            continue
        enc = texture_parts(encode_replacement(tex, new, finding.rule))
        diff = _first_part_diff(parts, enc)
        if diff is None:
            same += 1
            rebuilt[info.index] = enc
        else:
            fields.setdefault(diff, []).append(info.name)
    report.info(f"  re-encoded from their own DDS: {same} of {len(textures) - skipped} identical"
                + (f" ({skipped} skipped)" if skipped else ""))
    for f, names in sorted(fields.items(), key=lambda kv: -len(kv[1])):
        some = f"{', '.join(names[:5])}{', ...' if len(names) > 5 else ''}"
        if f.startswith("("):
            report.info(f"    {len(names)} {f[1:-1]}: {some}")
        else:
            ok = False
            report.error(f"{path.name}: {len(names)} textures differ first in {f}: {some}")
    # a replacement's second size follows the first when they were equal, else it is kept
    report.info(f"  second width and height: equal to the first in {len(second['equal'])}, zero in "
                f"{len(second['zero'])}, other in {len(second['other'])}"
                + (f" ({', '.join(second['other'][:3])})" if second["other"] else ""))
    if rebuilt:
        w2 = BlockWriter(w.data, path.name)
        for i, parts in rebuilt.items():
            w2.replace(i, parts)
        d = first_difference(w.data, w2.write())
        if d is None:
            report.info("  every identical texture put back through the writer: file identical")
        else:
            ok = False
            report.error(f"{path.name}: with the textures replaced by themselves the file DIFFERS at {d:#x} "
                         f"({w.locate(d)})")
    ok &= _resize_test(w, textures, finding.rule, report)
    return ok


def _resize_test(w: BlockWriter, textures: Sequence[TexInfo], rule: PadRule, report: Report) -> bool:
    """Replace one texture near the middle of the file with a smaller one (its
    top mip dropped) and a larger one (a new top mip of zero blocks), and read
    the result back: every other resource must be intact."""
    cands = [t for t in textures if t.standard and t.mips >= 2 and t.format in ("DXT1", "DXT3", "DXT5",
                                                                                 "A8R8G8B8", "X8R8G8B8")]
    if not cands:
        report.info("  resize test: skipped (no texture with two mips or more)")
        return True
    mid = w.resources[len(w.resources) // 2].offset
    t = min(cands, key=lambda c: abs(w.resources[c.index].offset - mid))
    res = w.resources[t.index]
    tex = parse_texture(res, w.parts(t.index))
    smaller = Texture(tex.name, tex.format, tex.mips[1].width, tex.mips[1].height, 0, 0,
                      mips=[Mip(m.width, m.height, m.data) for m in tex.mips[1:]])
    top = (tex.width * 2, tex.height * 2)
    larger = Texture(tex.name, tex.format, *top, 0, 0,
                     mips=[Mip(*top, bytes(mip_size(tex.format, *top)))] + [Mip(m.width, m.height, m.data)
                                                                              for m in tex.mips])
    ok = True
    for label, new in (("smaller", smaller), ("larger", larger)):
        w2 = BlockWriter(w.data, w.path.name)
        w2.replace(t.index, texture_parts(encode_replacement(tex, new, rule)))
        data = w2.write()
        problems = compare_bundles(w.data, data, w2.replaced_entries(), w.path.name)
        if problems:
            ok = False
            report.error(f"{w.path.name}: resize test ({label} {t.name}): " + "; ".join(problems[:3]))
        else:
            report.info(f"  resize test: {t.name} {label} ({new.width}x{new.height}), "
                        f"{len(data) - len(w.data):+,} bytes: every other resource intact")
    return ok


def cmd_selfcheck(game: Optional[Path], only: Sequence[str], report: Report, backup_dir: Path = BACKUP_DIR) -> int:
    paths: List[Path] = []
    state = None
    if game is not None:
        try:
            state = State(game, backup_dir, report)
        except TexPackError as ex:
            report.warn(f"{ex}; checking the game's files as they are")
    if only:
        for arg in only:
            p = Path(arg)
            if not p.is_file():
                if game is None:
                    raise TexPackError("game folder not found: pass --game-dir or set T3_GAME_DIR, or give .ibt files")
                p = resolve_map(game, arg, ".ibt")
            paths.append(p)
    elif game is not None:
        paths = game_bundles(game)
        if not paths:
            raise TexPackError(f"no .ibt bundles in {maps_dir(game)}")
    else:
        raise TexPackError("game folder not found: pass --game-dir or set T3_GAME_DIR")
    if state is not None:  # patched bundles: check their originals
        for i, p in enumerate(paths):
            try:
                key, stored = rel_key(game.resolve(), p.resolve())
            except ValueError:
                continue
            if state.record(key) is not None and state.backup_path(stored).is_file():
                report.info(f"{p.name} is patched: checking its original, {state.backup_path(stored)}")
                paths[i] = state.backup_path(stored)
    heads: List[TexInfo] = []
    for p in paths:
        try:
            heads += read_bundle_textures(p)
        except (ValueError, OSError, struct.error):
            pass  # selfcheck_bundle reports it
    prior, total = rule_counts(heads)
    overall = find_rule(heads)
    if overall.rule is not None:
        also = f" (as well: {', '.join(str(r) for r in overall.also)})" if overall.also else ""
        report.info(f"mip padding, all bundles: {overall.rule}, explains {overall.explained} of "
                    f"{_count(total, 'texture')}{also}")
    bad = [p.name for p in paths if not selfcheck_bundle(p, report, prior)]
    report.info(f"selfcheck: {'FAILED' if bad else 'ok'}: {len(paths) - len(bad)} of {_count(len(paths), 'bundle')} "
                "passed" + (f" ({', '.join(bad[:8])}{', ...' if len(bad) > 8 else ''} did not)" if bad else ""))
    return 1 if bad else 0


# --- CLI ------------------------------------------------------------------------------------------------

def _game(explicit: Optional[str], required: bool = True) -> Optional[Path]:
    try:
        return game_dir(explicit)
    except SystemExit:
        if required:
            raise TexPackError("game folder not found: pass --game-dir or set T3_GAME_DIR")
        return None


def main() -> None:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--game-dir", help="game install folder (default: $T3_GAME_DIR or the registry)")
    ap.add_argument("--selfcheck", nargs="*", metavar="MAP",
                    help="check the writer and the encoder on retail bundles (default: all)")
    sub = ap.add_subparsers(dest="cmd")
    s = sub.add_parser("list", help="texture names, formats, sizes, and the bundles holding them")
    s.add_argument("bundle", nargs="?", help="a map name (Inn) or a .ibt file: only its textures")
    s.add_argument("--json", action="store_true", help="print JSON")
    s = sub.add_parser("check", help="check texture packs against the game's textures")
    s.add_argument("--pack", action="append", default=[], type=Path, help="pack folder (repeat; later packs win)")
    s = sub.add_parser("apply", help="replace the textures in the game's bundles (later packs win)")
    s.add_argument("--pack", action="append", default=[], type=Path, help="pack folder (repeat; later packs win)")
    s.add_argument("-n", "--dry-run", action="store_true", help="check and rebuild in memory, write nothing")
    s = sub.add_parser("restore", help="put every patched bundle back")
    s.add_argument("-n", "--dry-run", action="store_true", help="show what would be restored")
    for p in sub.choices.values():
        p.add_argument("--game-dir", default=argparse.SUPPRESS, help=argparse.SUPPRESS)
    args = ap.parse_args()
    report = Report()
    try:
        if args.selfcheck is not None:
            code = cmd_selfcheck(_game(args.game_dir, required=not args.selfcheck), args.selfcheck, report)
        elif args.cmd == "list":
            code = cmd_list(_game(args.game_dir, required=not args.bundle), args.bundle, args.json, report)
        elif args.cmd == "check":
            code = cmd_check(_game(args.game_dir), args.pack, report)
        elif args.cmd == "apply":
            code = cmd_apply(_game(args.game_dir), args.pack, report, dry_run=args.dry_run)
        elif args.cmd == "restore":
            code = cmd_restore(_game(args.game_dir), report, dry_run=args.dry_run)
        else:
            ap.error("choose a command: list, check, apply, restore (or --selfcheck)")
            return
    except (TexPackError, LayoutError) as ex:
        report.error(str(ex))
        report.info(f"{args.cmd or 'selfcheck'}: FAILED")
        code = 1
    sys.exit(code)


if __name__ == "__main__":
    run_cli(main)
