#!/usr/bin/env python3
"""Ion Storm gamesys property table, recovered from the game's own UnrealScript.

The .t3u script packages still contain their UnrealScript source (TextBuffer
objects).  T3's "new property system" declares properties with explicit ids:

    var(Render) inherited(56) CustomEditor RenderObjectMeshStruct ObjectMesh "...";
    var runtimeinstantiated(48) float DrawScale;

In maps and archetypes these properties are stored as gamesys blocks whose id
is (type bits << 16) | property id, e.g. 0x00080038 = ObjectMesh (struct),
0x40100030 = DrawScale (float, 0x4000 = runtime-instantiated).

Usage:
  t3props.py table [--json out.json]          print the id -> property table
  t3props.py scripts [-o build/assets/script] write every .uc source file
  t3props.py enums                             print enum declarations
"""

from __future__ import annotations

import argparse
import json
import re
import sys
from dataclasses import asdict, dataclass
from pathlib import Path
from typing import Dict, Iterator, List, Optional, Tuple

sys.path.insert(0, str(Path(__file__).resolve().parent))
from t3common import run_cli, BUILD_DIR, Reader, game_dir  # noqa: E402
from upkg import Package  # noqa: E402

SCRIPT_PACKAGES = ["Core", "Engine", "Fire", "AICore", "T3AI", "T3Game", "T3Player", "Editor", "T3Gamesys"]
DECL_PACKAGES = ["Core", "Engine", "Fire", "AICore", "T3AI", "T3Game", "T3Player"]
CACHE = BUILD_DIR / "cache" / "gamesys_props.json"

_DECL = re.compile(
    r"^\s*var\s*(?:\((?P<cat>\w*)\))?(?P<pre>[^;\"]*?)\b(?P<kind>inherited|runtimeinstantiated)\s*\(\s*(?P<id>\d+)\s*\)"
    r"(?P<post>[^;\"]*?)(?P<type>(?:array|Array)\s*<\s*\w+\s*>|class\s*<\s*\w+\s*>|\w+)\s+(?P<name>\w+)\s*(?:\[\s*(?P<dim>\w+)\s*\])?"
    r"\s*(?:\"(?P<desc>[^\"]*)\")?\s*;",
    re.MULTILINE)
# var(Cat) inherited(N) bitfield EnumName { A, B, ... } PropName "description";
_BITFIELD = re.compile(
    r"^\s*var\s*(?:\((?P<cat>\w*)\))?(?P<pre>[^;\"{]*?)\b(?P<kind>inherited|runtimeinstantiated)\s*\(\s*(?P<id>\d+)\s*\)"
    r"[^;\"{]*?\bbitfield\s+(?P<enum>\w+)\s*\{(?P<body>[^}]*)\}\s*(?P<name>\w+)\s*(?:\"(?P<desc>[^\"]*)\")?\s*;",
    re.MULTILINE)
_ENUM = re.compile(r"\benum\s+(\w+)\s*\{([^}]*)\}", re.MULTILINE)
_COMMENT = re.compile(r"//[^\n]*|/\*.*?\*/", re.DOTALL)


@dataclass
class GamesysProperty:
    id: int
    name: str
    type: str
    category: str
    owner: str  # class whose script declares it
    kind: str   # inherited | runtimeinstantiated
    description: str = ""
    dim: Optional[str] = None


def iter_sources(game: Path, packages: List[str]) -> Iterator[Tuple[str, str, str]]:
    """Yield (package, class, source text) for every TextBuffer in the script packages."""
    system = game / "System"
    for pk in packages:
        path = system / f"{pk}.t3u"
        if not path.is_file():
            continue
        p = Package(path)
        for e in p.exports:
            if p.export_class(e) != "TextBuffer" or e.serial_size == 0:
                continue
            r = Reader(p.data, e.serial_offset, e.serial_offset + e.serial_size)
            try:
                p.read_properties(r, r.end)
                while True:                       # gamesys blocks (none expected)
                    bid = r.u32()
                    if bid == 0:
                        break
                    r.u32()
                    r.skip(r.u32())
                for _ in range(r.u32()):          # object links
                    r.index()
                r.u32(), r.u32()                  # Pos, Top
                text = r.fstring()
            except (EOFError, IndexError):
                continue
            yield pk, p.ref_name(e.package), text


def parse_declarations(pk: str, cls: str, text: str) -> List[GamesysProperty]:
    out = []
    code = _COMMENT.sub(lambda m: "" if m.group(0).startswith("/*") else "", text)
    for m in _DECL.finditer(code):
        t = re.sub(r"\s+", "", m.group("type"))
        out.append(GamesysProperty(int(m.group("id")), m.group("name"), t, m.group("cat") or "",
                                   f"{pk}.{cls}", m.group("kind"), (m.group("desc") or "").strip(),
                                   m.group("dim")))
    for m in _BITFIELD.finditer(code):
        out.append(GamesysProperty(int(m.group("id")), m.group("name"), f"bitfield<{m.group('enum')}>",
                                   m.group("cat") or "", f"{pk}.{cls}", m.group("kind"),
                                   (m.group("desc") or "").strip()))
    return out


def parse_enums(text: str) -> Dict[str, List[str]]:
    """enum name -> list indexed by value (entries may carry "= N").  Inline
    bitfield enums are included; their index is the bit number."""
    code = _COMMENT.sub("", text)
    enums = {}
    for m in list(_ENUM.finditer(code)) + [(b.group("enum"), b.group("body")) for b in _BITFIELD.finditer(code)]:
        if isinstance(m, tuple):
            name, body = m
            enums[name] = [v.strip().split("=")[0].strip() for v in body.split(",") if v.strip()]
            continue
        vals: List[str] = []
        for item in m.group(2).split(","):
            item = item.strip()
            if not item:
                continue
            name, _, num = item.partition("=")
            name = name.strip()
            if num.strip().isdigit():
                idx = int(num)
                while len(vals) < idx:
                    vals.append("")
                if len(vals) == idx:
                    vals.append(name)
                else:
                    vals[idx] = name
            else:
                vals.append(name)
        enums[m.group(1)] = vals
    return enums


def build_table(game: Path) -> Dict[str, object]:
    props: Dict[int, GamesysProperty] = {}
    enums: Dict[str, List[str]] = {}
    for pk, cls, text in iter_sources(game, DECL_PACKAGES):
        for d in parse_declarations(pk, cls, text):
            props.setdefault(d.id, d)
        enums.update(parse_enums(text))
    return {"properties": {str(k): asdict(v) for k, v in sorted(props.items())}, "enums": enums}


def load_table(game: Optional[Path] = None, refresh: bool = False) -> Dict[str, object]:
    """Property table, cached in build/assets/cache/ (rebuilt from the game's
    script packages when missing)."""
    if CACHE.is_file() and not refresh:
        return json.loads(CACHE.read_text(encoding="utf-8"))
    table = build_table(game or game_dir())
    CACHE.parent.mkdir(parents=True, exist_ok=True)
    CACHE.write_text(json.dumps(table, indent=1), encoding="utf-8")
    return table


class PropertyNames:
    """Lookup helper: gamesys block id -> property record."""

    def __init__(self, table: Dict[str, object]) -> None:
        self.props = {int(k): v for k, v in table["properties"].items()}  # type: ignore[union-attr]
        self.enums: Dict[str, List[str]] = table.get("enums", {})  # type: ignore[assignment]

    def get(self, block_id: int) -> Optional[dict]:
        return self.props.get(block_id & 0xFFFF)

    def id_of(self, name: str) -> Optional[int]:
        """Property id declared for `name` (first declaration wins)."""
        if not hasattr(self, "_by_name"):
            self._by_name: Dict[str, int] = {}
            for pid, rec in sorted(self.props.items()):
                self._by_name.setdefault(rec["name"].lower(), pid)
        return self._by_name.get(name.lower())

    def name(self, block_id: int) -> str:
        p = self.get(block_id)
        return p["name"] if p else f"prop{block_id & 0xFFFF}"

    def enum_value(self, block_id: int, value: int) -> Optional[str]:
        p = self.get(block_id)
        if p and p["type"] in self.enums and 0 <= value < len(self.enums[p["type"]]):
            return self.enums[p["type"]][value]
        return None

    def bitfield_names(self, block_id: int, mask: int) -> Optional[List[str]]:
        """Names of the bits set in a bitfield property's value."""
        p = self.get(block_id)
        if not p or not p["type"].startswith("bitfield<"):
            return None
        names = self.enums.get(p["type"][9:-1], [])
        return [names[i] if i < len(names) else f"bit{i}" for i in range(32) if mask >> i & 1]


def main() -> None:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--game-dir")
    sub = ap.add_subparsers(dest="cmd", required=True)
    s = sub.add_parser("table")
    s.add_argument("--json")
    s.add_argument("--refresh", action="store_true")
    s = sub.add_parser("scripts")
    s.add_argument("-o", "--output", default=str(BUILD_DIR / "script"))
    sub.add_parser("enums")
    args = ap.parse_args()
    game = game_dir(args.game_dir)
    if args.cmd == "table":
        table = load_table(game, refresh=args.refresh)
        if args.json:
            Path(args.json).write_text(json.dumps(table, indent=1), encoding="utf-8")
            print(f"wrote {args.json}")
        else:
            for k, v in table["properties"].items():  # type: ignore[union-attr]
                print(f"{int(k):5d} {v['kind'][:7]:7s} {v['category']:22s} {v['type']:28s} {v['name']:32s} {v['owner']}")
    elif args.cmd == "scripts":
        out = Path(args.output)
        n = 0
        for pk, cls, text in iter_sources(game, SCRIPT_PACKAGES):
            d = out / pk
            d.mkdir(parents=True, exist_ok=True)
            (d / f"{cls}.uc").write_text(text, encoding="latin-1", newline="")
            n += 1
        print(f"wrote {n} script files to {out}")
    else:
        for pk, cls, text in iter_sources(game, DECL_PACKAGES):
            for name, vals in parse_enums(text).items():
                print(f"{pk}.{cls}: enum {name} {{{', '.join(vals)}}}")


if __name__ == "__main__":
    run_cli(main)
