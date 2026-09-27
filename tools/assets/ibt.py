#!/usr/bin/env python3
"""Reader for Ion Storm .ibt resource bundles (Content/T3/Maps/*.ibt).

Every level ships as <Level>.gmp (Unreal package: actors, BSP, gamesys data)
plus <Level>.ibt, which holds the level's render and physics resources.
Kernel_*ALL.ibt and MainMenu_*ALL.ibt are shared bundles (GFX = shaders and
common textures/meshes, PHY = common physics shapes, TSD = common trigger
scripts).

Layout (all little-endian):

  header, 0x34 bytes
    +00 u32  magic 0xC0000001
    +04 u32  alignment (0x800)
    +08 u32  offset of the first resource (= size of header + tables, aligned)
    +0C u32  size of the resource area (header+08 plus this = file size)
    +10 u32  largest resource size
    +14 u32  largest part size
    +18 u32  resource count
    +1C u32  part count
    +20 20 bytes, probably a SHA-1 (not verified)
  resource table: count entries of 0x134 bytes
    +00 u32  data offset (aligned to 0x800)
    +04 u32  data size
    +08 u32  padding after the data (size + padding is a multiple of 0x800)
    +0C u32  index of the first part in the part table
    +10 u32  number of parts
    +14 20 bytes, probably a SHA-1 of the resource (not verified)
    +28 u8   resource type (RESOURCE_TYPES)
    +29 char name[263], NUL-padded
    +130 u32 0xFFFFFFFF
  part table: part-count u32 sizes.  A resource's data is the concatenation of
  its parts; each part is one field or array written by the engine's
  serialiser (the table probably exists for byte-swapping on console builds).

Usage:
  ibt.py list    <file.ibt|MapName> [--type texture|staticmesh|matlib|...]
  ibt.py stats   <file.ibt|MapName>
  ibt.py parts   <file.ibt|MapName> <resource name> [--type T] [--bytes 32]
  ibt.py extract <file.ibt|MapName> [--type T] [--name N] [-o DIR]   (raw resources + parts)
"""

from __future__ import annotations

import argparse
import hashlib
import json
import struct
import sys
from collections import Counter
from dataclasses import dataclass
from pathlib import Path
from typing import Dict, Iterator, List, Optional, Tuple

sys.path.insert(0, str(Path(__file__).resolve().parent))
from t3common import run_cli, BUILD_DIR, game_dir, resolve_map  # noqa: E402

IBT_MAGIC = 0xC0000001
HEADER_SIZE = 0x34
ENTRY_SIZE = 0x134

# Resource type byte -> name.  The numbering is Ion Storm's eResourceType
# enum (printed by Utility/misc_perl/dumpblockfile.pl in the public T3Ed
# release); only the types found in retail bundles are listed, with what the
# data shows.
RESOURCE_TYPES = {
    0x04: "staticmesh",       # render mesh + skins + hardpoints (see t3mesh.py)
    0x05: "physicshull",      # "PHYS" chunk, Havok 2 shapes; name "<mesh>--<n> sx sy sz"
    0x06: "ragdolls",         # character physics (bone capsules, constraints)
    0x08: "texture",          # D3D texture: format + mip chain (see t3texture.py)
    0x0A: "matlib",           # MatLib material: colours, category, 8 texture stages
    0x10: "skeletalmesh",
    0x11: "skeletalanim",
    0x15: "triggerscriptdef", # TS_<n> trigger scripts
    0x1D: "fleshshader",      # compiled vertex/pixel shaders
}
TYPE_BY_NAME = {v: k for k, v in RESOURCE_TYPES.items()}


@dataclass
class Resource:
    index: int
    offset: int
    size: int
    padding: int
    first_part: int
    part_count: int
    hash: bytes
    type: int
    name: str

    @property
    def type_name(self) -> str:
        return RESOURCE_TYPES.get(self.type, f"type{self.type:02x}")


class IBT:
    def __init__(self, path: Path | str) -> None:
        self.path = Path(path)
        self._f = open(self.path, "rb")
        head = self._f.read(HEADER_SIZE)
        (self.magic, self.alignment, self.data_start, self.data_size, self.max_resource_size,
         self.max_part_size, count, part_count) = struct.unpack_from("<8I", head, 0)
        if self.magic != IBT_MAGIC:
            raise ValueError(f"{self.path}: not an .ibt bundle (magic {self.magic:#010x})")
        self.hash = head[0x20:0x34]
        table = self._f.read(count * ENTRY_SIZE + part_count * 4)
        self.resources: List[Resource] = []
        for i in range(count):
            e = table[i * ENTRY_SIZE:(i + 1) * ENTRY_SIZE]
            off, size, pad, first, nparts = struct.unpack_from("<5I", e, 0)
            name = e[0x29:0x130].split(b"\0", 1)[0].decode("latin-1")
            self.resources.append(Resource(i, off, size, pad, first, nparts, e[0x14:0x28], e[0x28], name))
        pbase = count * ENTRY_SIZE
        self.part_sizes = struct.unpack_from(f"<{part_count}I", table, pbase)
        self._by_key: Optional[Dict[Tuple[int, str], Resource]] = None

    def close(self) -> None:
        self._f.close()

    def __enter__(self) -> "IBT":
        return self

    def __exit__(self, *exc) -> None:
        self.close()

    def of_type(self, rtype: int) -> Iterator[Resource]:
        return (r for r in self.resources if r.type == rtype)

    def find(self, name: str, rtype: Optional[int] = None) -> Optional[Resource]:
        """Case-insensitive lookup (T3 lowercases texture resource names)."""
        if self._by_key is None:
            self._by_key = {}
            for r in self.resources:
                self._by_key.setdefault((r.type, r.name.lower()), r)
        if rtype is not None:
            return self._by_key.get((rtype, name.lower()))
        for r in self.resources:
            if r.name.lower() == name.lower():
                return r
        return None

    def read(self, res: Resource) -> bytes:
        self._f.seek(res.offset)
        data = self._f.read(res.size)
        if len(data) != res.size:
            raise EOFError(f"{res.name}: short read")
        return data

    def parts(self, res: Resource) -> List[int]:
        return list(self.part_sizes[res.first_part:res.first_part + res.part_count])

    def split(self, res: Resource) -> List[bytes]:
        data = self.read(res)
        out, pos = [], 0
        for n in self.parts(res):
            out.append(data[pos:pos + n])
            pos += n
        if pos != len(data):
            raise ValueError(f"{res.name}: parts cover {pos} of {len(data)} bytes")
        return out


class PartReader:
    """Walks a resource part by part: each read must consume exactly one part,
    which catches layout mistakes early."""

    def __init__(self, parts: List[bytes]) -> None:
        self.parts = parts
        self.i = 0

    def done(self) -> bool:
        return self.i >= len(self.parts)

    def peek_size(self) -> int:
        return len(self.parts[self.i])

    def raw(self, expect: Optional[int] = None) -> bytes:
        if self.i >= len(self.parts):
            raise EOFError("no more parts")
        p = self.parts[self.i]
        if expect is not None and len(p) != expect:
            raise ValueError(f"part {self.i}: expected {expect} bytes, found {len(p)}")
        self.i += 1
        return p

    def u8(self) -> int:
        return self.raw(1)[0]

    def u32(self) -> int:
        return struct.unpack("<I", self.raw(4))[0]

    def i32(self) -> int:
        return struct.unpack("<i", self.raw(4))[0]

    def f32(self) -> float:
        return struct.unpack("<f", self.raw(4))[0]

    def string(self) -> str:
        """u32 length (including NUL) in one part, the characters in the next."""
        n = self.u32()
        if n == 0:
            return ""
        return self.raw(n).split(b"\0", 1)[0].decode("latin-1")


def open_ibt(arg: str, game: Optional[str] = None) -> IBT:
    p = Path(arg)
    if not p.is_file():
        p = resolve_map(game_dir(game), arg, ".ibt")
    return IBT(p)


# --- CLI ------------------------------------------------------------------------

def _type_filter(s: Optional[str]) -> Optional[int]:
    if not s:
        return None
    if s in TYPE_BY_NAME:
        return TYPE_BY_NAME[s]
    return int(s, 0)


def cmd_list(ibt: IBT, args) -> None:
    t = _type_filter(args.type)
    for r in ibt.resources:
        if t is not None and r.type != t:
            continue
        print(f"{r.index:5d} {r.type_name:16s} {r.size:9d} parts {r.part_count:4d}  {r.name}")


def cmd_stats(ibt: IBT, args) -> None:
    print(f"{ibt.path.name}: {len(ibt.resources)} resources, {len(ibt.part_sizes)} parts, "
          f"data at {ibt.data_start:#x} ({ibt.data_size} bytes), alignment {ibt.alignment:#x}")
    count, size = Counter(), Counter()
    for r in ibt.resources:
        count[r.type_name] += 1
        size[r.type_name] += r.size
    for k, v in count.most_common():
        print(f"  {k:16s} {v:6d} {size[k]:12d} bytes")


def cmd_parts(ibt: IBT, args) -> None:
    res = ibt.find(args.name, _type_filter(args.type))
    if res is None:
        sys.exit(f"no resource named {args.name!r}")
    print(f"{res.name}: {res.type_name}, {res.size} bytes, {res.part_count} parts")
    pos = 0
    for i, part in enumerate(ibt.split(res)):
        extra = ""
        if len(part) == 4:
            u = struct.unpack("<I", part)[0]
            f = struct.unpack("<f", part)[0]
            extra = f"  u32 {u}  f32 {f:.6g}"
        elif part.endswith(b"\0") and part[:-1] and all(32 <= c < 127 for c in part[:-1]):
            extra = f"  {part[:-1].decode()!r}"
        print(f"  {i:4d} @{pos:6x} {len(part):7d}  {part[:args.bytes].hex()}{extra}")
        pos += len(part)


def cmd_extract(ibt: IBT, args) -> None:
    t = _type_filter(args.type)
    out = Path(args.output) if args.output else BUILD_DIR / "raw" / ibt.path.stem
    out.mkdir(parents=True, exist_ok=True)
    n = 0
    index = []
    for r in ibt.resources:
        if t is not None and r.type != t:
            continue
        if args.name and args.name.lower() not in r.name.lower():
            continue
        safe = "".join(c if c.isalnum() or c in "-_." else "_" for c in r.name)
        fn = out / r.type_name / f"{r.index:05d}_{safe}.bin"
        fn.parent.mkdir(parents=True, exist_ok=True)
        data = ibt.read(r)
        fn.write_bytes(data)
        index.append({"index": r.index, "name": r.name, "type": r.type_name, "size": r.size,
                      "parts": ibt.parts(r), "file": str(fn.relative_to(out)),
                      "sha1": hashlib.sha1(data).hexdigest(), "table_hash": r.hash.hex()})
        n += 1
    (out / "index.json").write_text(json.dumps(index, indent=1), encoding="utf-8")
    print(f"extracted {n} resources to {out}")


def main() -> None:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--game-dir")
    sub = ap.add_subparsers(dest="cmd", required=True)
    s = sub.add_parser("list")
    s.add_argument("ibt")
    s.add_argument("--type", help="type name (texture, staticmesh, ...) or number")
    s = sub.add_parser("stats")
    s.add_argument("ibt")
    s = sub.add_parser("parts")
    s.add_argument("ibt")
    s.add_argument("name")
    s.add_argument("--type", help="disambiguate when several resources share the name")
    s.add_argument("--bytes", type=int, default=32)
    s = sub.add_parser("extract")
    s.add_argument("ibt")
    s.add_argument("--type")
    s.add_argument("--name")
    s.add_argument("-o", "--output")
    args = ap.parse_args()
    with open_ibt(args.ibt, args.game_dir) as ibt:
        {"list": cmd_list, "stats": cmd_stats, "parts": cmd_parts, "extract": cmd_extract}[args.cmd](ibt, args)


if __name__ == "__main__":
    run_cli(main)
