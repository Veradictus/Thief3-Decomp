#!/usr/bin/env python3
"""Gamesys archetypes (System/T3Gamesys.t3u).

T3's object system descends from the Dark Engine: placeable things are
archetypes, stored as UnrealScript classes named D_<n> ("class D_<n> extends
D_<m>;") whose default properties hold gamesys property blocks (mesh, light,
sounds, scripts...).  Map actors of class D_<n> inherit those blocks and only
store their overrides.

UClass layout in T3 (v95, licensee 133), as parsed here:

  u32 link count, compact link[count]          (UObject: LinkDataObjects owned by the class)
  compact SuperField, compact Next             (UField)
  compact ScriptText, compact Children, compact FriendlyName,
  i32 Line, i32 TextPos, i32 ScriptSize, bytecode (UStruct; archetypes have none)
  u64 ProbeMask, u64 IgnoreMask, u16 LabelTableOffset, u32 StateFlags   (UState)
  u32 ClassFlags, 16-byte GUID, compact n + n x (compact class, u32 deep, u32 crc),
  compact n + n x compact package name, compact ClassWithin, compact ConfigName
  FString archetype display name               (Ion Storm addition: a readable name)
  tagged default properties, gamesys blocks (0-terminated)

Usage:
  t3gamesys.py list [--mesh]          every archetype: id, display name, parent, mesh
  t3gamesys.py show D_<n>             resolved (inherited) gamesys properties
  t3gamesys.py json -o archetypes.json
"""

from __future__ import annotations

import argparse
import json
import sys
from dataclasses import dataclass, field
from pathlib import Path
from typing import Any, Dict, List, Optional

sys.path.insert(0, str(Path(__file__).resolve().parent))
from t3common import run_cli, BUILD_DIR, Reader, game_dir  # noqa: E402
from t3props import PropertyNames, load_table  # noqa: E402
from upkg import GamesysBlock, Package, Property, _jsonable, props_to_json  # noqa: E402


@dataclass
class Archetype:
    name: str               # D_<n>
    display: str            # readable archetype name
    parent: str             # D_<m>, or an engine class such as StaticMeshActor
    defaults: List[Property] = field(default_factory=list)
    blocks: Dict[int, GamesysBlock] = field(default_factory=dict)  # prop id -> block
    links: List[str] = field(default_factory=list)
    error: Optional[str] = None


class Gamesys:
    def __init__(self, path: Path) -> None:
        self.package = Package(path)
        self.archetypes: Dict[str, Archetype] = {}
        p = self.package
        for e in p.exports:
            if e.class_ref != 0 or not e.name.upper().startswith("D_"):
                continue
            self.archetypes[e.name.upper()] = self._parse_class(e)

    def _parse_class(self, e) -> Archetype:
        p = self.package
        parent = p.ref_name(e.super_ref) if e.super_ref else ""
        arch = Archetype(e.name, "", parent)
        r = Reader(p.data, e.serial_offset, e.serial_offset + e.serial_size)
        try:
            arch.links = [p.ref_path(r.index()) for _ in range(r.u32())]
            r.index(), r.index()                      # SuperField, Next
            r.index(), r.index(), r.index()           # ScriptText, Children, FriendlyName
            r.i32(), r.i32()                          # Line, TextPos
            if r.i32() != 0:
                raise ValueError("archetype class has bytecode")
            r.u64(), r.u64(), r.u16(), r.u32()        # UState
            r.u32(), r.bytes(16)                      # ClassFlags, GUID
            for _ in range(r.index()):
                r.index(), r.u32(), r.u32()
            for _ in range(r.index()):
                r.index()
            r.index(), r.index()                      # ClassWithin, ClassConfigName
            arch.display = r.fstring()
            arch.defaults = p.read_properties(r, r.end)
            while r.remaining() >= 4:
                bid = r.u32()
                if bid == 0:
                    break
                ver, size = r.u32(), r.u32()
                b = GamesysBlock(bid, ver, r.bytes(size))
                b.value = p.decode_gamesys(b)
                arch.blocks[b.prop_id] = b
        except (EOFError, IndexError, ValueError, UnicodeDecodeError) as ex:
            arch.error = str(ex)
        return arch

    def chain(self, name: str) -> List[Archetype]:
        """Archetype and its ancestors, most derived first."""
        out = []
        seen = set()
        a = self.archetypes.get(name.upper())
        while a is not None and a.name not in seen:
            out.append(a)
            seen.add(a.name)
            a = self.archetypes.get(a.parent.upper())
        return out

    def engine_class(self, name: str) -> str:
        """First non-archetype ancestor (e.g. StaticMeshActor, Light, AIPawn...)."""
        ch = self.chain(name)
        return ch[-1].parent if ch else name

    def resolved(self, name: str) -> Dict[int, GamesysBlock]:
        blocks: Dict[int, GamesysBlock] = {}
        for a in reversed(self.chain(name)):
            blocks.update(a.blocks)
        return blocks

    def display(self, name: str) -> str:
        a = self.archetypes.get(name.upper())
        return a.display if a else ""


def load_gamesys(game: Optional[Path] = None) -> Gamesys:
    return Gamesys((game or game_dir()) / "System" / "T3Gamesys.t3u")


def mesh_of(blocks: Dict[int, GamesysBlock], names: PropertyNames) -> Optional[Dict[str, str]]:
    """The ObjectMesh property (static mesh name + skin), if present."""
    pid = names.id_of("ObjectMesh")
    b = blocks.get(pid) if pid is not None else None
    if b is None or not isinstance(b.value, list):
        return None
    d = {p.name: p.value for p in b.value if isinstance(p, Property)}
    if not d.get("Name"):
        return None
    return {"name": d.get("Name", ""), "skin": d.get("Skin", "") or "Default"}


def blocks_to_dict(blocks: Dict[int, GamesysBlock], names: PropertyNames) -> Dict[str, Any]:
    out: Dict[str, Any] = {}
    for pid, b in sorted(blocks.items()):
        v = _jsonable(b.value)
        if b.kind == "byte" and isinstance(v, int):
            ev = names.enum_value(b.id, v)
            if ev:
                v = ev
        elif b.kind == "bitfield" and isinstance(v, int):
            bits = names.bitfield_names(b.id, v)
            if bits is not None:
                v = bits
        out[names.name(b.id)] = v
    return out


def main() -> None:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--game-dir")
    sub = ap.add_subparsers(dest="cmd", required=True)
    s = sub.add_parser("list")
    s.add_argument("--mesh", action="store_true", help="only archetypes with a static mesh")
    s = sub.add_parser("show")
    s.add_argument("archetype")
    s = sub.add_parser("json")
    s.add_argument("-o", "--output", default=str(BUILD_DIR / "archetypes.json"))
    args = ap.parse_args()
    game = game_dir(args.game_dir)
    gs = load_gamesys(game)
    names = PropertyNames(load_table(game))
    if args.cmd == "list":
        for key in sorted(gs.archetypes, key=lambda k: int(k[2:]) if k[2:].isdigit() else 1 << 30):
            a = gs.archetypes[key]
            m = mesh_of(gs.resolved(key), names)
            if args.mesh and not m:
                continue
            mesh = f"  mesh {m['name']} ({m['skin']})" if m else ""
            print(f"{a.name:8s} {a.display:40s} parent {a.parent:10s} base {gs.engine_class(key)}{mesh}"
                  + (f"  [parse: {a.error}]" if a.error else ""))
    elif args.cmd == "show":
        chain = gs.chain(args.archetype)
        if not chain:
            sys.exit(f"no archetype {args.archetype}")
        print(" -> ".join(f"{a.name} ({a.display})" for a in chain) + f" -> {gs.engine_class(args.archetype)}")
        for k, v in blocks_to_dict(gs.resolved(args.archetype), names).items():
            print(f"  {k:32s} = {v}")
    else:
        out = {}
        for key, a in gs.archetypes.items():
            out[a.name] = {"display": a.display, "parent": a.parent, "base": gs.engine_class(key),
                           "own": blocks_to_dict(a.blocks, names),
                           "defaults": props_to_json(a.defaults), "links": a.links}
        Path(args.output).parent.mkdir(parents=True, exist_ok=True)
        Path(args.output).write_text(json.dumps(out, indent=1, default=str), encoding="utf-8")
        print(f"wrote {len(out)} archetypes to {args.output}")


if __name__ == "__main__":
    run_cli(main)
