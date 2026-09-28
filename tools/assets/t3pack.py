#!/usr/bin/env python3
"""Write edited maps back into Thief: Deadly Shadows: round trip, apply,
install, restore.

The "repack" half of the Godot workflow (docs/assets.md, section 8).  Maps
are re-serialised with upkgwrite.py: objects that are not edited are copied
verbatim, and an edited actor keeps its state frame, links and native tail.

Usage:
  t3pack.py roundtrip <map or package> | --all
      parse and re-write each package in memory, and report "identical" or
      the first differing offset and the table or object it is in.  It also
      checks that every actor re-serialises exactly, and (for maps) that
      growing one actor in the middle of the file leaves every other object
      intact.  --all: every map, script package and UTX file of the install.
      A package that differs is written to build/assets/roundtrip/.
  t3pack.py apply <edits.json> [-o out.gmp] [--source <.gmp>] [--dry-run]
      apply a map edits file (t3-map-edits version 1, see docs/assets.md) to
      the level's .gmp and write build/assets/patched/<Level>.gmp.
  t3pack.py install <patched.gmp> [--level NAME] [--dry-run]
      copy a patched map into Content/T3/Maps, after backing up the original
      once to build/assets/backup/ (an existing backup is never replaced).
  t3pack.py restore <Level> | --all [--dry-run]
      copy the backed-up originals back into Content/T3/Maps.

install and restore are the only commands that write to the game folder.
"""

from __future__ import annotations

import argparse
import hashlib
import json
import math
import os
import re
import shutil
import struct
import sys
from collections import Counter
from dataclasses import dataclass, field
from pathlib import Path
from typing import Any, Callable, Dict, List, Optional, Tuple, Union

sys.path.insert(0, str(Path(__file__).resolve().parent))
from t3common import run_cli, BUILD_DIR, content_dir, game_dir, resolve_map  # noqa: E402
from t3props import PropertyNames, load_table  # noqa: E402
from upkg import RF_HasStack, Export, Package, prop_value, struct_fields  # noqa: E402
from upkgwrite import (STRUCTS, ActorEdit, LayoutError, PackageWriter, block_kind, compare_packages, f32,  # noqa: E402
                       first_difference, gamesys_data, is_finite_f32, parse_fields, parse_object)

PATCHED_DIR = BUILD_DIR / "patched"
BACKUP_DIR = BUILD_DIR / "backup"
ROUNDTRIP_DIR = BUILD_DIR / "roundtrip"

EDITS_FORMAT = "t3-map-edits"
# 2 adds "added" (new actors, each a copy of one in the map) and "removed";
# version 1 files, which only change actors, still load.
EDITS_VERSION = 2
EDITS_VERSIONS = (1, 2)
ACTOR_KEYS = ("location", "rotation", "draw_scale", "gamesys")


class EditsError(ValueError):
    """An edits file that is invalid, or edits that cannot be applied."""


# --- the edits file ----------------------------------------------------------------------

def _is_number(v: Any) -> bool:
    return isinstance(v, (int, float)) and not isinstance(v, bool)


def _is_integral(v: Any) -> bool:
    return _is_number(v) and math.isfinite(v) and float(v).is_integer()


def load_edits(source: Union[str, Path, Dict[str, Any]]) -> Dict[str, Any]:
    """Read and check a map edits document (format "t3-map-edits", version 1
    or 2) from a path or an already parsed dict.

    Returns a normalised copy: {"format", "version", "level", "source" (a
    dict, or None when absent), "actors": {export name: {...}}, "added":
    [{"copy_of": export name, ...}], "removed": [export name]}, with
    location and draw_scale as floats and rotation rounded to ints.  Raises
    EditsError listing every problem.  Unknown top-level keys are ignored;
    an unknown key under an actor is an error."""
    where = "edits"
    if isinstance(source, dict):
        doc: Any = source
    else:
        where = Path(source).name
        try:
            doc = json.loads(Path(source).read_text(encoding="utf-8"))
        except OSError as ex:
            raise EditsError(f"{where}: cannot read it: {ex}") from ex
        except ValueError as ex:
            raise EditsError(f"{where}: not valid JSON: {ex}") from ex
    if not isinstance(doc, dict):
        raise EditsError(f"{where}: expected a JSON object")
    problems: List[str] = []
    if doc.get("format") != EDITS_FORMAT:
        problems.append(f'"format" must be "{EDITS_FORMAT}", not {doc.get("format")!r}')
    ver = doc.get("version")
    if not _is_integral(ver) or ver not in EDITS_VERSIONS:
        problems.append(f'"version" {ver!r} is not supported: this tool reads versions '
                        f'{", ".join(map(str, EDITS_VERSIONS))}')
    level = doc.get("level")
    if not isinstance(level, str) or not level.strip():
        problems.append('"level" must name the map, e.g. "Inn"')
    src = doc.get("source")
    out_src: Optional[Dict[str, Any]] = None
    if src is not None:
        if not isinstance(src, dict):
            problems.append('"source" must be an object: {"file", "size", "sha1"}')
        else:
            out_src = {}
            if src.get("file") is not None:
                if isinstance(src["file"], str):
                    out_src["file"] = src["file"]
                else:
                    problems.append('"source.file" must be a string')
            if src.get("size") is not None:
                if _is_integral(src["size"]) and src["size"] >= 0:
                    out_src["size"] = int(src["size"])
                else:
                    problems.append('"source.size" must be a byte count')
            if src.get("sha1") is not None:
                if isinstance(src["sha1"], str) and re.fullmatch(r"[0-9a-fA-F]{40}", src["sha1"]):
                    out_src["sha1"] = src["sha1"].lower()
                else:
                    problems.append('"source.sha1" must be 40 hex digits')
    actors = doc.get("actors")
    if not isinstance(actors, dict):
        problems.append('"actors" must be an object keyed by export name')
        actors = {}
    out_actors: Dict[str, Dict[str, Any]] = {}
    for name, a in actors.items():
        rec = _actor_record(a, f"actor {name!r}", problems)
        if rec is not None:
            out_actors[str(name)] = rec

    added = doc.get("added", [])
    out_added: List[Dict[str, Any]] = []
    if not isinstance(added, list):
        problems.append('"added" must be a list of new actors')
        added = []
    for i, a in enumerate(added):
        label = f"added actor {i + 1}"
        copy_of = a.get("copy_of") if isinstance(a, dict) else None
        if not isinstance(copy_of, str) or not copy_of.strip():
            problems.append(f'{label}: "copy_of" must name the actor it copies')
            continue
        rec = _actor_record({k: v for k, v in a.items() if k != "copy_of"}, f"{label} ({copy_of})", problems)
        if rec is not None:
            out_added.append({"copy_of": copy_of, **rec})

    removed = doc.get("removed", [])
    if not (isinstance(removed, list) and all(isinstance(r, str) and r.strip() for r in removed)):
        problems.append('"removed" must be a list of actor names')
        removed = []
    for name in sorted(set(removed) & set(out_actors)):
        problems.append(f"actor {name!r} is both edited and removed")
    if problems:
        raise EditsError(f"{where}:\n  " + "\n  ".join(problems))
    return {"format": EDITS_FORMAT, "version": int(ver), "level": level.strip(), "source": out_src,
            "actors": out_actors, "added": out_added, "removed": sorted(set(removed))}


def _actor_record(a: Any, label: str, problems: List[str]) -> Optional[Dict[str, Any]]:
    """One actor's changes (under "actors", or a new actor under "added"),
    checked and normalised; problems are appended to `problems`."""
    if not isinstance(a, dict):
        problems.append(f"{label}: expected an object")
        return None
    rec: Dict[str, Any] = {}
    for k, v in a.items():
        if k == "location":
            if isinstance(v, list) and len(v) == 3 and all(_is_number(x) and is_finite_f32(x) for x in v):
                rec[k] = [float(x) for x in v]
            else:
                problems.append(f"{label}: location must be [x, y, z], three finite numbers (Unreal units)")
        elif k == "rotation":
            if (isinstance(v, list) and len(v) == 3 and all(_is_number(x) and math.isfinite(x) for x in v)
                    and all(-2 ** 31 <= round(x) < 2 ** 31 for x in v)):
                rec[k] = [int(round(x)) for x in v]
            else:
                problems.append(f"{label}: rotation must be [pitch, yaw, roll] in Unreal units (65536 = 360 deg)")
        elif k == "draw_scale":
            if _is_number(v) and is_finite_f32(v):
                rec[k] = float(v)
            else:
                problems.append(f"{label}: draw_scale must be a finite number")
        elif k == "gamesys":
            if not isinstance(v, dict):
                problems.append(f"{label}: gamesys must be an object of property name: value")
                continue
            rec[k] = {}
            for pk, pv in v.items():
                ok = (_is_number(pv) and math.isfinite(pv)) or isinstance(pv, (bool, str)) or (
                    isinstance(pv, list) and all(isinstance(x, str) for x in pv))
                if ok:
                    rec[k][pk] = pv
                else:
                    problems.append(f"{label}: gamesys {pk}: {pv!r} is not a number, bool, string or "
                                    "list of bit names")
        else:
            problems.append(f"{label}: unknown key {k!r} (expected {', '.join(ACTOR_KEYS)})")
    return rec


def sha1_of(path: Path) -> str:
    h = hashlib.sha1()
    with open(path, "rb") as f:
        for chunk in iter(lambda: f.read(1 << 20), b""):
            h.update(chunk)
    return h.hexdigest()


def _source_matches(path: Path, src: Dict[str, Any]) -> bool:
    if "size" in src and path.stat().st_size != src["size"]:
        return False
    return "sha1" not in src or sha1_of(path) == src["sha1"]


def check_source(edits: Dict[str, Any], path: Path, backup_dir: Path = BACKUP_DIR) -> str:
    """Compare a map file with the edits' "source" record.  Returns a note;
    raises EditsError when the file is not the one the edits were made from."""
    src = edits.get("source") or {}
    if "sha1" not in src and "size" not in src:
        return "no source hash in the edits file: not checked"
    if _source_matches(path, src):
        what = f"sha1 {src['sha1'][:12]}" if "sha1" in src else f"size {src['size']}"
        return f"matches the edits' source ({what})"
    hint = ""
    backup = backup_dir / path.name
    if backup.is_file() and backup.resolve() != path.resolve() and _source_matches(backup, src):
        hint = f" The backup matches: pass --source {backup}"
    raise EditsError(f"{path} is not the file these edits were made from (expected size {src.get('size')}, "
                     f"sha1 {src.get('sha1')}). Export the map again and redo the edits, or pass --source "
                     f"with the file they were made from.{hint}")


def original_source(edits: Dict[str, Any], path: Path, backup_dir: Path = BACKUP_DIR,
                    log: Callable[[str], None] = print) -> Path:
    """The map to patch: `path`, or its backup when the game holds a patched
    copy and the edits were made from the original (the backup matches the
    edits' source record and `path` does not)."""
    src = edits.get("source") or {}
    backup = backup_dir / path.name
    if (("sha1" in src or "size" in src) and backup.is_file() and backup.resolve() != path.resolve()
            and not _source_matches(path, src) and _source_matches(backup, src)):
        log(f"{path.name}: the game has a patched copy; using the backed-up original {backup}")
        return backup
    return path


# --- applying edits ----------------------------------------------------------------------

_DECLARED_BITS = {"float": 0x0010, "int": 0x0020, "bool": 0x0080, "name": 0x0100, "byte": 0x0200,
                  "string": 0x0004}
WRITABLE_KINDS = ("float", "int", "bool", "byte", "bitfield", "name", "string")


class _Props:
    """Gamesys property ids and types for one package: names from the
    property table, block ids as the package already uses them."""

    def __init__(self, writer: PackageWriter, names: Optional[PropertyNames]) -> None:
        self.writer, self.names = writer, names
        self._usage: Optional[Dict[int, Counter]] = None
        self._enums = {k.lower(): v for k, v in names.enums.items()} if names else {}

    def label(self, block_id: int) -> str:
        return self.names.name(block_id) if self.names else f"prop{block_id & 0xFFFF}"

    def record(self, prop_id: int) -> Optional[dict]:
        return self.names.get(prop_id) if self.names else None

    def id_of(self, key: str) -> Optional[int]:
        m = re.fullmatch(r"prop(\d+)", key)
        if m:
            return int(m.group(1))
        return self.names.id_of(key) if self.names else None

    def usage(self) -> Dict[int, Counter]:
        """Block ids per property id over the package's actors."""
        if self._usage is None:
            self._usage = {}
            p = self.writer.pkg
            for e in p.exports:
                if not e.flags & RF_HasStack or not e.serial_size:
                    continue
                try:
                    lay = parse_object(p.export_bytes(e), e.flags, self.writer.name_text)
                except LayoutError:
                    continue
                for b in lay.blocks:
                    self._usage.setdefault(b.id & 0xFFFF, Counter())[b.id] += 1
        return self._usage

    def insert_id(self, prop_id: int) -> Optional[int]:
        """The block id for a new block: the one the package uses for this
        property, else one built from the declared type."""
        used = self.usage().get(prop_id)
        if used:
            return used.most_common(1)[0][0]
        rec = self.record(prop_id)
        if rec is None:
            return None
        t = rec["type"].lower()
        bits = _DECLARED_BITS.get(t) or (0x0200 if t in self._enums else 0x0800 if t.startswith("bitfield<") else 0)
        if not bits:
            return None
        return (bits | (0x4000 if rec.get("kind") == "runtimeinstantiated" else 0)) << 16 | prop_id

    def enum(self, prop_id: int) -> Optional[List[str]]:
        rec = self.record(prop_id)
        if rec is None:
            return None
        t = rec["type"].lower()
        return self._enums.get(t[9:-1] if t.startswith("bitfield<") else t)


def _convert(kind: str, value: Any, key: str, enum: Optional[List[str]]) -> Any:
    """A JSON value as the Python value gamesys_data() writes for `kind`."""
    bad = EditsError(f"gamesys {key} ({kind}): {value!r} is not a valid value")
    if kind == "float":
        if not _is_number(value) or not is_finite_f32(value):
            raise bad
        return float(value)
    if kind == "int":
        if not _is_integral(value) or not -2 ** 31 <= value < 2 ** 31:
            raise bad
        return int(value)
    if kind == "bool":
        if isinstance(value, bool) or (_is_integral(value) and value in (0, 1)):
            return int(bool(value))
        raise bad
    if kind == "byte":
        if isinstance(value, str):
            names = [n.lower() for n in enum or []]
            if value.lower() not in names:
                raise EditsError(f"gamesys {key}: {value!r} is not a value of its enum"
                                 + (f" ({', '.join(n for n in enum if n)})" if enum else " (enum not known)"))
            return names.index(value.lower())
        if _is_integral(value) and 0 <= value <= 255:
            return int(value)
        raise bad
    if kind == "bitfield":
        if _is_integral(value) and 0 <= value < 2 ** 32:
            return int(value)
        if isinstance(value, list):
            names = [n.lower() for n in enum or []]
            mask = 0
            for bit in value:
                m = re.fullmatch(r"bit(\d+)", bit, re.IGNORECASE)
                if bit.lower() in names:
                    mask |= 1 << names.index(bit.lower())
                elif m and int(m.group(1)) < 32:
                    mask |= 1 << int(m.group(1))
                else:
                    raise EditsError(f"gamesys {key}: {bit!r} is not one of its bits")
            return mask
        raise bad
    if kind == "name":
        if isinstance(value, str) and value and "\0" not in value:
            return value
        raise bad
    if kind == "string":
        if isinstance(value, str) and "\0" not in value:
            return value
        raise bad
    raise EditsError(f"gamesys {key} is a {kind} property; only {', '.join(WRITABLE_KINDS)} values can be written")


@dataclass
class Patch:
    """Edits applied to a writer.  `expect` lists (export index, what, prop
    id, value) for verify_patch(); `added` the new actors' export indices,
    `removed` the names of actors taken out of the level, and
    `level_actors` the Level's new actor list when it changed."""
    writer: PackageWriter
    changes: List[str] = field(default_factory=list)
    edited: List[int] = field(default_factory=list)
    expect: List[Tuple[int, str, Optional[int], Any]] = field(default_factory=list)
    added: List[int] = field(default_factory=list)
    removed: List[str] = field(default_factory=list)
    level_actors: Optional[List[int]] = None


def _export_index(pkg: Package) -> Dict[str, List[Export]]:
    """Exports by name and by lower-case name."""
    out: Dict[str, List[Export]] = {}
    for e in pkg.exports:
        out.setdefault(e.name, []).append(e)
        if e.name.lower() != e.name:
            out.setdefault(e.name.lower(), []).append(e)
    return out


def _find_actor(pkg: Package, by_name: Dict[str, List[Export]], name: str) -> Export:
    found = [e for e in by_name.get(name, []) if e.name == name] or by_name.get(name.lower(), [])
    actors = [e for e in found if e.flags & RF_HasStack and e.serial_size]
    if len(actors) == 1:
        return actors[0]
    if len(actors) > 1:
        raise EditsError(f"{len(actors)} actors are named {name!r}")
    if found:
        raise EditsError(f"{name!r} is a {pkg.export_class(found[0])} object, not an actor")
    raise EditsError("no actor of that name in the map")


def _set_draw_scale(act: ActorEdit, value: float, props: _Props) -> Optional[int]:
    """DrawScale: the actor's own gamesys block if it has one, else its tagged
    property, except on archetype instances (D_*), whose inherited block would
    win over a tagged value: those, and actors with neither, get a block.
    Returns the property id of the block written (None: the tag)."""
    pid = props.id_of("DrawScale")
    own = act.block(pid) if pid is not None else None
    tag = act.tagged_float("DrawScale")
    archetype = act.writer.pkg.export_class(act.exp).upper().startswith("D_")
    data = struct.pack("<f", value)
    if own is not None:
        if block_kind(own.id) != "float" or len(own.data) != 4:
            raise LayoutError("its DrawScale block is not a float")
        act.set_block(pid, data, "DrawScale", shown=f32(value))
    elif tag is None or archetype:
        if pid is None:
            raise EditsError("draw_scale: adding a DrawScale block needs the gamesys property table")
        bid = props.insert_id(pid)
        if bid is None or block_kind(bid) != "float":
            raise EditsError("draw_scale: no float block id known for DrawScale")
        act.set_block(pid, data, "DrawScale", insert_id=bid, shown=f32(value))
    else:
        act.set_tagged_float("DrawScale", value)
        return None
    if tag is not None:
        act.set_tagged_float("DrawScale", value)  # keep both in step
    return pid


def _set_gamesys(act: ActorEdit, key: str, value: Any, props: _Props) -> Tuple[int, Any]:
    """Set one gamesys property; returns (property id, value written)."""
    own = next((b for b in act.layout.blocks if props.label(b.id).lower() == key.lower()), None)
    pid = own.id & 0xFFFF if own is not None else props.id_of(key)
    if pid is None:
        raise EditsError(f"unknown gamesys property {key!r}"
                         + ("" if props.names else " (the gamesys property table is not loaded)"))
    own = own or act.block(pid)
    bid = own.id if own is not None else props.insert_id(pid)
    if bid is None:
        raise EditsError(f"gamesys {key}: the actor has no such block and its type is not known")
    kind = block_kind(bid)
    v = _convert(kind, value, key, props.enum(pid))
    size = {"float": 4, "int": 4, "bitfield": 4, "bool": 1, "byte": 1}.get(kind)
    if own is not None and size is not None and len(own.data) != size:
        raise LayoutError(f"gamesys {key}: its block holds {len(own.data)} bytes, not {size}")
    try:
        data = gamesys_data(kind, v, act.writer, own.data if own is not None else b"")
    except (struct.error, OverflowError) as ex:
        raise EditsError(f"gamesys {key}: {ex}") from ex
    act.set_block(pid, data, key, insert_id=bid, shown=value)
    if kind == "name":  # the name as stored (an existing name may differ in case)
        v = act.writer.name_text(act.writer.name_index(v))
    return pid, v


def _apply_record(act: ActorEdit, rec: Dict[str, Any], props: _Props, label: str,
                  problems: List[str]) -> List[Tuple[int, str, Optional[int], Any]]:
    """Set an actor's placement and gamesys values from an edits record;
    returns what verify_patch() should read back."""
    index = act.exp.index
    expect: List[Tuple[int, str, Optional[int], Any]] = []
    if "location" in rec:
        act.set_location(rec["location"])
        expect.append((index, "Location", None, rec["location"]))
    if "rotation" in rec:
        act.set_rotation(rec["rotation"])
        expect.append((index, "Rotation", None, rec["rotation"]))
    if "draw_scale" in rec:
        pid = _set_draw_scale(act, rec["draw_scale"], props)
        expect.append((index, "DrawScale", pid, rec["draw_scale"]))
    for key, value in rec.get("gamesys", {}).items():
        try:
            pid, v = _set_gamesys(act, key, value, props)
        except (EditsError, LayoutError) as ex:
            problems.append(f"{label}: {ex}")
            continue
        expect.append((index, key, pid, v))
    return expect


def _new_actor_name(writer: PackageWriter, like: str) -> str:
    """A name for an actor copied from `like` ("StaticMeshActor__1920"):
    the same stem with the next instance number no name uses yet."""
    stem = re.sub(r"__\d+$", "", like)
    pattern = re.compile(re.escape(stem) + r"__(\d+)$", re.I)
    taken = [int(m.group(1)) for m in (pattern.match(n.text) for n in writer.names) if m]
    number = max(taken, default=-1) + 1
    while writer.find_name(f"{stem}__{number}") is not None:
        number += 1
    return f"{stem}__{number}"


def apply_edits(pkg: Package, edits: Dict[str, Any], names: Optional[PropertyNames] = None) -> Patch:
    """Apply checked edits (see load_edits) to a parsed map.  Call
    patch.writer.write() for the file.  Raises EditsError listing every
    actor or value that cannot be applied.

    A new actor copies the object data of the actor it names (as in the
    file, before any edit to it) under a new name, and joins the Level's
    actor list.  A removed actor leaves that list: its object stays in the
    file, but the level does not have it."""
    patch = Patch(PackageWriter(pkg))
    props = _Props(patch.writer, names)
    by_name = _export_index(pkg)
    problems: List[str] = []
    for name, rec in edits["actors"].items():
        try:
            exp = _find_actor(pkg, by_name, name)
            act = ActorEdit(patch.writer, exp)
            expect = _apply_record(act, rec, props, name, problems)
        except (EditsError, LayoutError) as ex:
            problems.append(f"{name}: {ex}")
            continue
        if act.commit():
            patch.edited.append(exp.index)
        patch.changes += [f"{exp.name}: {c}" for c in act.changes]
        patch.expect += expect

    added = edits.get("added", [])
    removed = edits.get("removed", [])
    if added or removed:
        refs = pkg.level_actors()
        if refs is None:
            raise EditsError("cannot add or remove actors: the map has no Level object")
        # The LevelInfo and the builder brush open every level's list.
        keep = set(refs[:2])
        gone = set()
        for name in removed:
            try:
                exp = _find_actor(pkg, by_name, name)
            except EditsError as ex:
                problems.append(f"removed actor {name!r}: {ex}")
                continue
            if exp.index + 1 in keep:
                problems.append(f"removed actor {name!r}: the level needs its {pkg.export_class(exp)}")
            elif exp.index + 1 not in refs:
                problems.append(f"removed actor {name!r}: it is not in the level")
            else:
                gone.add(exp.index + 1)
                patch.removed.append(exp.name)
                patch.changes.append(f"{exp.name}: removed from the level")

        new_refs = []
        for i, rec in enumerate(added):
            label = f"added actor {i + 1} (a copy of {rec['copy_of']})"
            try:
                src = _find_actor(pkg, by_name, rec["copy_of"])
                name = _new_actor_name(patch.writer, src.name)
                index = patch.writer.add_export(src.index, name, pkg.export_bytes(src))
                act = ActorEdit(patch.writer, patch.writer.export_view(index))
                expect = _apply_record(act, rec, props, label, problems)
            except (EditsError, LayoutError) as ex:
                problems.append(f"{label}: {ex}")
                continue
            act.commit()
            patch.added.append(index)
            patch.changes.append(f"{name}: added, a copy of {src.name}")
            patch.changes += [f"{name}: {c}" for c in act.changes]
            patch.expect += expect
            new_refs.append(index + 1)

        if not problems:
            patch.level_actors = [r for r in refs if r not in gone] + new_refs
            try:
                patch.writer.set_level_actors(patch.level_actors)
            except LayoutError as ex:
                raise EditsError(f"cannot add or remove actors: {ex}") from ex
            patch.edited.append(pkg.level().index)
    if problems:
        raise EditsError("cannot apply these edits:\n  " + "\n  ".join(problems))
    return patch


def _same(got: Any, want: Any) -> bool:
    if isinstance(want, float):
        return isinstance(got, (int, float)) and not isinstance(got, bool) and got == f32(want)
    return got == want


def verify_patch(orig: Package, new: Package, patch: Patch) -> List[str]:
    """Read the patched package back with upkg: every other object must be
    byte-identical and every edited value must read as requested."""
    problems = compare_packages(orig, new, patch.edited, added=len(patch.added))
    if patch.level_actors is not None and new.level_actors() != patch.level_actors:
        problems.append("the Level's actor list does not read back as written")
    for idx, what, pid, want in patch.expect:
        e = new.exports[idx]
        a = new.read_actor(e)
        if what in ("Location", "Rotation"):
            fields = STRUCTS["Vector" if what == "Location" else "Rotator"][0]
            f = struct_fields(prop_value(a.properties, what))
            got: Any = [f.get(n, 0) for n in fields]
            ok = all(_same(g, w) for g, w in zip(got, [float(x) if what == "Location" else x for x in want]))
        else:
            b = a.block(pid) if pid is not None else None
            got = b.value if b is not None else prop_value(a.properties, "DrawScale") if what == "DrawScale" else None
            ok = _same(got, want)
        if not ok:
            problems.append(f"{e.name}: {what} reads {got!r}, expected {want!r}")
    return problems


def write_verified(orig: Package, patch: Patch, out: Path, keep: bool = True) -> int:
    """Write the patch to `out` through a temporary file, read it back and
    verify it; returns the size written.  Raises EditsError on a problem."""
    data = patch.writer.write()
    out.parent.mkdir(parents=True, exist_ok=True)
    tmp = out.with_name(out.name + ".tmp")
    tmp.write_bytes(data)
    try:
        try:
            new = Package(tmp)
        except (ValueError, EOFError, IndexError, UnicodeDecodeError, struct.error) as ex:
            raise EditsError(f"the patched map does not read back: {ex}") from ex
        problems = verify_patch(orig, new, patch)
        if problems:
            raise EditsError("the patched map does not check out:\n  " + "\n  ".join(problems))
        if keep:
            os.replace(tmp, out)
    finally:
        if tmp.exists():
            tmp.unlink()
    return len(data)


# --- round trip ---------------------------------------------------------------------------

@dataclass
class RoundTrip:
    path: Path
    ok: bool = False
    lines: List[str] = field(default_factory=list)


def check_actors(pkg: Package, writer: PackageWriter) -> Tuple[int, int, List[str], List[str]]:
    """Parse every actor into its layout (struct values into their fields)
    and re-encode it.  Returns (actors, exact, not parsed, mismatched)."""
    total = exact = 0
    unparsed: List[str] = []
    mismatched: List[str] = []
    for e in pkg.exports:
        if not e.flags & RF_HasStack or not e.serial_size:
            continue
        total += 1
        data = pkg.export_bytes(e)
        try:
            lay = parse_object(data, e.flags, writer.name_text)
        except LayoutError as ex:
            unparsed.append(f"{e.name}: {ex}")
            continue
        for t in lay.props.tags:
            if t.ptype == 10:
                try:
                    parse_fields(t, writer.name_text)
                except LayoutError:
                    pass
        if lay.encode() == data:
            exact += 1
        else:
            mismatched.append(e.name)
    return total, exact, unparsed, mismatched


def resize_test(pkg: Package, writer: PackageWriter, scratch: Path) -> Tuple[bool, str]:
    """Grow an actor near the middle of the file by writing a missing Rotation
    or Location field explicitly as 0 (the value it already reads as), write
    the package, and check with upkg that everything else is intact.  The
    writer is changed."""
    offsets = sorted(e.serial_offset for e in pkg.exports if e.serial_size)
    mid = offsets[len(offsets) // 2] if offsets else 0
    cands = sorted((e for e in pkg.exports if e.flags & RF_HasStack and e.serial_size),
                   key=lambda e: abs(e.serial_offset - mid))
    for e in cands[:500]:
        try:
            act = ActorEdit(writer, e)
            before = {}
            for prop, st in (("Rotation", "Rotator"), ("Location", "Vector")):
                if act.layout.props.find(prop) is not None:
                    before[prop] = act.struct_values(prop, st)
                    act.set_struct(prop, st, before[prop], explicit=True)
                    if act.changes:
                        break
        except LayoutError:
            continue
        if not act.changes:
            continue
        act.commit()
        grow = len(writer.object_data(e.index)) - e.serial_size
        patch = Patch(writer, edited=[e.index],
                      expect=[(e.index, p, None, v) for p, v in before.items()])
        try:
            write_verified(pkg, patch, scratch, keep=False)
        except EditsError as ex:
            return False, f"FAILED: {ex}"
        return True, (f"ok: {e.name} grown by {grow} bytes ({'; '.join(act.changes)}), "
                      f"{_count(len(writer.added_names), 'name')} added, every other object intact")
    return True, "skipped: no actor with a missing Location or Rotation field"


def x24_note(pkg: Package) -> Optional[str]:
    """What the Ion DWORD at 0x24 coincides with, if anything (evidence for
    its meaning; see docs/assets.md, section 9)."""
    v = pkg.ion_unknown
    if not v:
        return None
    cands = [("the file size", len(pkg.data)), ("the name table offset", pkg.name_offset),
             ("the import table offset", pkg.import_offset), ("the export table offset", pkg.export_offset),
             ("the extra table offset", pkg.depends_offset), ("the end of the import table", pkg.import_end),
             ("the end of the export table", pkg.export_end), ("the name count", len(pkg.names)),
             ("the import count", len(pkg.imports)), ("the export count", len(pkg.exports)),
             ("the actor count", sum(1 for e in pkg.exports if e.flags & RF_HasStack)),
             ("the total object size", sum(e.serial_size for e in pkg.exports))]
    for e in pkg.exports:
        if e.serial_size:
            cands += [(f"the offset of export #{e.index} {e.name}", e.serial_offset),
                      (f"the end of export #{e.index} {e.name}", e.serial_offset + e.serial_size)]
    hits = [k for k, c in cands if c == v]
    return (f"DWORD at 0x24 = {v:#x} ({v}): "
            + ("equals " + ", ".join(hits[:4]) if hits else "matches no table offset, object offset or count"))


def roundtrip(path: Path, resize: bool = True) -> RoundTrip:
    res = RoundTrip(path)
    try:
        pkg = Package(path)
    except (ValueError, EOFError, IndexError, UnicodeDecodeError, struct.error) as ex:
        res.lines.append(f"cannot read: {ex}")
        return res
    try:
        writer = PackageWriter(pkg)
        out = writer.write()
    except LayoutError as ex:
        res.lines.append(f"cannot lay out: {ex}")
        return res
    d = first_difference(pkg.data, out)
    if d is None:
        res.lines.append(f"identical ({len(out):,} bytes, {len(pkg.exports)} exports)")
    else:
        ROUNDTRIP_DIR.mkdir(parents=True, exist_ok=True)
        (ROUNDTRIP_DIR / path.name).write_bytes(out)
        res.lines.append(f"DIFFERS at {d:#x} ({writer.locate(d)}); sizes {len(pkg.data):,} / {len(out):,}")
        res.lines.append(f"rewritten file: {ROUNDTRIP_DIR / path.name}")
    for label, counts in (("non-canonical compact indices (kept)", writer.padded),
                          ("entries kept as raw bytes", writer.opaque)):
        if counts:
            res.lines.append(f"{label}: " + ", ".join(f"{k} {n}" for k, n in sorted(counts.items())))
    total, exact, unparsed, mismatched = check_actors(pkg, writer)
    ok = d is None and not mismatched
    if total:
        res.lines.append(f"actors: {exact} of {total} re-serialise exactly"
                         + (f", {len(unparsed)} not parsed (cannot be edited)" if unparsed else ""))
        res.lines += [f"  not parsed: {u}" for u in unparsed[:5]]
        if mismatched:
            res.lines.append("  MISMATCH: " + ", ".join(mismatched[:10]))
    if resize and total:
        rok, text = resize_test(pkg, writer, ROUNDTRIP_DIR / f"{path.stem}.resized{path.suffix}")
        res.lines.append(f"resize test: {text}")
        ok = ok and rok
    note = x24_note(pkg)
    if note:
        res.lines.append(note)
    res.ok = ok
    return res


# --- install / restore ------------------------------------------------------------------

def _map_file(maps: Path, level: str) -> Optional[Path]:
    stem = Path(level).stem.lower()
    if maps.is_dir():
        for f in maps.iterdir():
            if f.suffix.lower() == ".gmp" and f.stem.lower() == stem:
                return f
    return None


def _copy(src: Path, dst: Path) -> None:
    """Copy through a temporary file next to `dst`, so it is never half written."""
    tmp = dst.with_name(dst.name + ".t3pack.tmp")
    shutil.copy2(src, tmp)
    os.replace(tmp, dst)


def _same_file_content(a: Path, b: Path) -> bool:
    return a.stat().st_size == b.stat().st_size and sha1_of(a) == sha1_of(b)


def install(patched: Path, game: Path, level: Optional[str] = None, backup_dir: Path = BACKUP_DIR,
            dry_run: bool = False, log: Callable[[str], None] = print) -> Path:
    """Copy a patched map over the level's map in the game folder, backing up
    the original first unless a backup already exists.  Returns the target."""
    maps = content_dir(game) / "Maps"
    name = level or patched.stem
    target = _map_file(maps, name)
    if target is None:
        raise EditsError(f"no map {name!r} in {maps}: install only replaces an existing map")
    if not patched.is_file():
        raise EditsError(f"no such file: {patched}")
    if patched.resolve() == target.resolve():
        raise EditsError(f"{patched} is the installed map itself")
    backup = backup_dir / target.name
    # A patch is made from the original map (the backup once one exists): it
    # keeps the original's objects in order, and new actors come after them.
    original = Package(backup if backup.exists() else target)
    new = Package(patched)
    same = [(e.name.lower(), e.class_ref) for e in original.exports]
    if ((new.file_version, new.licensee_version) != (original.file_version, original.licensee_version)
            or [(e.name.lower(), e.class_ref) for e in new.exports[:len(same)]] != same):
        raise EditsError(f"{patched.name} is not a patched {target.name}: its package version or its objects "
                         f"differ from the original's (repack it from the current edits)")
    if backup.exists():
        log(f"backup kept (it exists already): {backup}")
    else:
        log(f"{'would copy' if dry_run else 'copied'} {target} -> {backup} (backup of the original)")
        if not dry_run:
            backup_dir.mkdir(parents=True, exist_ok=True)
            shutil.copy2(target, backup)
    if not dry_run:
        _copy(patched, target)
    log(f"{'would copy' if dry_run else 'copied'} {patched} -> {target}")
    return target


def restore(level: Optional[str], game: Path, backup_dir: Path = BACKUP_DIR, dry_run: bool = False,
            log: Callable[[str], None] = print) -> int:
    """Copy backed-up maps (one level, or all when `level` is None) back into
    the game folder.  Backups are kept.  Returns the number of maps copied."""
    maps = content_dir(game) / "Maps"
    backups = sorted((f for f in backup_dir.iterdir() if f.suffix.lower() == ".gmp"),
                     key=lambda f: f.name.lower()) if backup_dir.is_dir() else []
    if level is not None:
        backups = [f for f in backups if f.stem.lower() == Path(level).stem.lower()]
        if not backups:
            raise EditsError(f"no backup of {level} in {backup_dir}")
    elif not backups:
        log(f"no backups in {backup_dir}: nothing to restore")
        return 0
    copied = 0
    for b in backups:
        target = _map_file(maps, b.stem) or maps / b.name
        if target.is_file() and _same_file_content(b, target):
            log(f"unchanged: {target} is already the original")
            continue
        if not dry_run:
            _copy(b, target)
        log(f"{'would copy' if dry_run else 'copied'} {b} -> {target}")
        copied += 1
    return copied


# --- CLI ----------------------------------------------------------------------------------

def _count(n: int, what: str) -> str:
    return f"{n} {what}" + ("" if n == 1 else "s")


def _game_or_none(explicit: Optional[str]) -> Optional[Path]:
    try:
        return game_dir(explicit)
    except SystemExit:
        return None


def _files(folder: Path, ext: str) -> List[Path]:
    if not folder.is_dir():
        return []
    return sorted((f for f in folder.iterdir() if f.suffix.lower() == ext), key=lambda f: f.name.lower())


def _load_names(game: Optional[Path]) -> PropertyNames:
    try:
        return PropertyNames(load_table(game))
    except (SystemExit, OSError, ValueError, KeyError) as ex:
        raise EditsError("draw_scale and gamesys edits need the gamesys property table: run t3map.py or "
                         "t3props.py table once (it is cached in build/assets/cache/), or pass --game-dir") from ex


def cmd_roundtrip(args) -> None:
    if args.all:
        game = game_dir(args.game_dir)
        paths = (_files(content_dir(game) / "Maps", ".gmp") + _files(game / "System", ".t3u")
                 + _files(content_dir(game) / "UTX", ".utx"))
        if not paths:
            sys.exit(f"no packages found under {game}")
    elif args.package:
        p = Path(args.package)
        paths = [p if p.is_file() else resolve_map(game_dir(args.game_dir), args.package, ".gmp")]
    else:
        sys.exit("give a map or package, or --all")
    bad = 0
    for p in paths:
        res = roundtrip(p, resize=p.suffix.lower() in (".gmp", ".unr"))
        print(f"{p.name}: {res.lines[0]}", flush=True)
        for ln in res.lines[1:]:
            print(f"  {ln}")
        bad += not res.ok
    if len(paths) > 1:
        print(f"{len(paths) - bad} of {len(paths)} packages round-trip" + (f"; {bad} FAILED" if bad else ""))
    sys.exit(1 if bad else 0)


def cmd_apply(args) -> None:
    edits = load_edits(args.edits)
    game = _game_or_none(args.game_dir)
    if args.source:
        src = Path(args.source)
        if not src.is_file():
            sys.exit(f"no such file: {src}")
    else:
        if game is None:
            sys.exit("game folder not found: pass --game-dir, set T3_GAME_DIR, or give --source")
        src = original_source(edits, resolve_map(game, edits["level"], ".gmp"))
    print(f"{src.name}: {check_source(edits, src)}")
    if src.stem.lower() != edits["level"].lower():
        print(f"  note: the edits are for level {edits['level']!r}")
    need_table = any("draw_scale" in a or a.get("gamesys") for a in list(edits["actors"].values()) + edits["added"])
    names = _load_names(game) if need_table else None
    pkg = Package(src)
    patch = apply_edits(pkg, edits, names)
    out = Path(args.output) if args.output else PATCHED_DIR / f"{src.stem}.gmp"
    if game is not None and out.resolve().is_relative_to(game.resolve()):
        sys.exit(f"refusing to write into the game folder ({out}); write under build/assets/ and use install")
    for c in patch.changes:
        print(f"  {c}")
    if not patch.changes:
        print("  no changes: every value already matches the map")
    size = write_verified(pkg, patch, out, keep=not args.dry_run)
    names = patch.writer.added_names
    changed = len([i for i in patch.edited if i < len(pkg.exports) and pkg.exports[i] != pkg.level()])
    summary = (f"{_count(changed, 'actor')} changed, {len(patch.added)} added, {len(patch.removed)} removed, "
               f"{_count(len(names), 'name')} added to the table; {len(pkg.data):,} -> {size:,} bytes; "
               "verified: every other object is byte-identical")
    print(f"  {summary}")
    print("dry run: nothing written" if args.dry_run else f"wrote {out}")


def cmd_install(args) -> None:
    game = game_dir(args.game_dir)
    install(Path(args.patched), game, args.level, dry_run=args.dry_run)


def cmd_restore(args) -> None:
    if not args.level and not args.all:
        sys.exit("give a level or --all")
    game = game_dir(args.game_dir)
    restore(None if args.all else args.level, game, dry_run=args.dry_run)


def main() -> None:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--game-dir", help="game install folder (default: $T3_GAME_DIR or registry)")
    sub = ap.add_subparsers(dest="cmd", required=True)
    s = sub.add_parser("roundtrip", help="re-write packages and compare them with the originals")
    s.add_argument("package", nargs="?", help="map name (Inn) or path to a package")
    s.add_argument("--all", action="store_true", help="every map, script package and UTX file")
    s = sub.add_parser("apply", help="apply a map edits file; writes build/assets/patched/<Level>.gmp")
    s.add_argument("edits", help="edits file (t3-map-edits, version 1)")
    s.add_argument("-o", "--output", help="patched map to write (default build/assets/patched/<Level>.gmp)")
    s.add_argument("--source", help="map to patch (default: the level's .gmp in the game folder)")
    s.add_argument("-n", "--dry-run", action="store_true", help="check and verify, write nothing")
    s = sub.add_parser("install", help="copy a patched map into the game, backing up the original once")
    s.add_argument("patched", help="patched .gmp")
    s.add_argument("--level", help="map to replace (default: the patched file's name)")
    s.add_argument("-n", "--dry-run", action="store_true", help="show what would be copied")
    s = sub.add_parser("restore", help="copy backed-up original maps back into the game")
    s.add_argument("level", nargs="?")
    s.add_argument("--all", action="store_true")
    s.add_argument("-n", "--dry-run", action="store_true", help="show what would be copied")
    args = ap.parse_args()
    try:
        {"roundtrip": cmd_roundtrip, "apply": cmd_apply, "install": cmd_install,
         "restore": cmd_restore}[args.cmd](args)
    except (EditsError, LayoutError) as ex:
        sys.exit(f"error: {ex}")


if __name__ == "__main__":
    run_cli(main)
