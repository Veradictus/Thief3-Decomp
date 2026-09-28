#!/usr/bin/env python3
"""Reader for Thief: Deadly Shadows Unreal packages.

Handles the Ion Storm "Flesh" fork of Unreal Engine 2 used by T3 and Deus Ex:
Invisible War:

- file version 95, licensee 107..133: System/*.t3u (script/gamesys packages)
  and Content/T3/Maps/*.gmp (levels);
- file version 88, licensee 5: Content/T3/UTX/*.utx (legacy texture packages).

Layout notes (see docs/assets.md for the full description):

- The v95 summary has one extra DWORD after ImportOffset (0 in .t3u, non-zero
  in .gmp; meaning unknown) and two DWORDs after the generation table; the
  second is the offset of an extra table that sits between the import and
  export tables (lists of export indices; purpose not confirmed).
- Name, import and export tables use the stock UE2 encoding.  Names keep the
  instance number as text ("Camera__19"), the form T3Main.exe prints.
- Tagged properties use the UE2 tag format, but *every* struct value,
  including Vector and Rotator, is itself a tagged property list terminated by
  "None".
- Actor-like objects follow their tagged properties with Ion Storm gamesys
  property blocks: repeated (u32 id, u32 1, u32 size, data) until an id of 0.
  The high 16 bits of the id encode the value type (see GAMESYS_TYPES).

Usage:
  upkg.py summary  <package>
  upkg.py names    <package>
  upkg.py imports  <package>
  upkg.py exports  <package> [--class StaticMeshActor]
  upkg.py classes  <package>
  upkg.py dump     <package> <export name or #index> [--hex]
  upkg.py json     <package> -o out.json      (tables + parsed properties)

<package> is a path, or a bare map name (resolved in Content/T3/Maps as .gmp).
"""

from __future__ import annotations

import argparse
import json
import struct
import sys
from collections import Counter
from dataclasses import dataclass
from pathlib import Path
from typing import Any, Dict, List, Optional, Tuple

sys.path.insert(0, str(Path(__file__).resolve().parent))
from t3common import run_cli, Reader, game_dir, resolve_map  # noqa: E402

PACKAGE_TAG = 0x9E2A83C1

# Object flags (stock UE2 values).
RF_Public = 0x00000004
RF_Transactional = 0x00000001
RF_HasStack = 0x02000000
RF_Standalone = 0x00080000

PROP_TYPES = {
    1: "Byte", 2: "Int", 3: "Bool", 4: "Float", 5: "Object", 6: "Name",
    7: "String", 8: "Class", 9: "Array", 10: "Struct", 11: "Vector",
    12: "Rotator", 13: "Str", 14: "Map", 15: "FixedArray",
}

# High 16 bits of a gamesys block id -> value encoding.  Confirmed against the
# property declarations in the game's UnrealScript (see t3props.py); the bits
# mirror the UProperty class of the declaration.  0x4000 marks properties
# declared "runtimeinstantiated" (engine-owned, e.g. StaticMesh, DrawScale).
GAMESYS_TYPES = {
    0x0001: "class",    # compact object index (class<...>)
    0x0002: "object",   # compact object index
    0x0004: "string",   # FString
    0x0008: "struct",   # tagged property list
    0x0010: "float",
    0x0020: "int",
    0x0080: "bool",     # one byte
    0x0100: "name",     # compact name index
    0x0200: "byte",     # one byte (enums)
    0x0400: "array",    # compact count, then elements
    0x0800: "bitfield", # u32 bit mask (Ion "bitfield" declarations with an inline enum)
}
GAMESYS_RUNTIME = 0x4000


@dataclass
class Import:
    class_package: str
    class_name: str
    package: int
    name: str


@dataclass
class Export:
    index: int  # 0-based position in the export table
    class_ref: int
    super_ref: int
    package: int
    name: str
    flags: int
    serial_size: int
    serial_offset: int


@dataclass
class Property:
    name: str
    type: str
    array_index: int
    value: Any
    struct: Optional[str] = None
    size: int = 0


@dataclass
class GamesysBlock:
    id: int
    version: int
    data: bytes
    value: Any = None

    @property
    def kind(self) -> str:
        return GAMESYS_TYPES.get((self.id >> 16) & 0x0FFF, f"type{(self.id >> 16):#x}")

    @property
    def prop_id(self) -> int:
        return self.id & 0xFFFF

    @property
    def runtime(self) -> bool:
        return bool((self.id >> 16) & GAMESYS_RUNTIME)


@dataclass
class ActorData:
    """What we can decode of an object serialised with Ion Storm's layout:
    [state frame] tagged properties, gamesys blocks (0-terminated), then a
    u32 count of object links (compact indices, e.g. LinkDataObjects), then
    class-specific native data (`tail`)."""
    state: Optional[Dict[str, int]]
    properties: List[Property]
    gamesys: List[GamesysBlock]
    links: List[int]
    tail: bytes
    parse_error: Optional[str] = None

    def block(self, prop_id: int) -> Optional[GamesysBlock]:
        for b in self.gamesys:
            if b.prop_id == prop_id:
                return b
        return None


class Package:
    def __init__(self, path: Path | str) -> None:
        self.path = Path(path)
        self.data = self.path.read_bytes()
        r = Reader(self.data)
        self.tag = r.u32()
        if self.tag != PACKAGE_TAG:
            raise ValueError(f"{self.path}: not an Unreal package (tag {self.tag:#010x})")
        self.file_version = r.u16()
        self.licensee_version = r.u16()
        self.package_flags = r.u32()
        name_count, name_offset = r.u32(), r.u32()
        export_count, export_offset = r.u32(), r.u32()
        import_count, import_offset = r.u32(), r.u32()
        self.name_offset, self.export_offset, self.import_offset = name_offset, export_offset, import_offset
        self.ion_unknown = None   # DWORD at 0x24 (v95, licensee >= 44)
        self.ion_extra = None     # first DWORD after the generations (v95, licensee >= 22)
        self.depends_offset = None
        self.guid = b""
        self.generations: List[Tuple[int, int]] = []
        if self.file_version < 68:
            # Unreal 1 era (e.g. CoreTexDetail.utx, version 61): heritage table, no generations.
            self.heritage_count, self.heritage_offset = r.u32(), r.u32()
        else:
            self._read_summary_tail(r, name_offset)
        self.header_size = r.pos

        # names (ASCIIZ before version 64, FString after)
        r.pos = name_offset
        self.names: List[str] = []
        self.name_flags: List[int] = []
        for _ in range(name_count):
            if self.file_version < 64:
                end = self.data.index(b"\0", r.pos)
                self.names.append(self.data[r.pos:end].decode("latin-1"))
                r.pos = end + 1
            else:
                self.names.append(r.fstring())
            self.name_flags.append(r.u32())

        # imports
        r.pos = import_offset
        self.imports: List[Import] = []
        for _ in range(import_count):
            cp, cn = r.index(), r.index()
            pk = r.i32()
            on = r.index()
            self.imports.append(Import(self.names[cp], self.names[cn], pk, self.names[on]))
        self.import_end = r.pos

        # exports
        r.pos = export_offset
        self.exports: List[Export] = []
        for i in range(export_count):
            cl, su = r.index(), r.index()
            pk = r.i32()
            on = r.index()
            fl = r.u32()
            size = r.index()
            off = r.index() if size > 0 else 0
            self.exports.append(Export(i, cl, su, pk, self.names[on], fl, size, off))
        self.export_end = r.pos
        self._by_name: Optional[Dict[str, int]] = None

    def _read_summary_tail(self, r: Reader, name_offset: int) -> None:
        """GUID, generations and Ion Storm's extra fields.

        The extras grew with the licensee version: none up to 19, two DWORDs
        after the generations from 22, plus one DWORD before the GUID from 44.
        Rather than trusting those thresholds, pick the layout whose header
        ends exactly at the name table (the names always follow the header).
        """
        base = r.pos
        for has_x24, has_extra in ((True, True), (False, True), (False, False)):
            r.pos = base
            try:
                x24 = r.u32() if has_x24 else None
                guid = r.bytes(16)
                gen_count = r.u32()
                if gen_count > 4096:
                    continue
                gens = [(r.u32(), r.u32()) for _ in range(gen_count)]
                extra = (r.u32(), r.u32()) if has_extra else None
            except EOFError:
                continue
            if r.pos == name_offset:
                self.ion_unknown = x24
                self.guid, self.generations = guid, gens
                if extra:
                    self.ion_extra, self.depends_offset = extra
                return
        raise ValueError(f"{self.path}: unrecognised package summary layout")

    # --- object references -------------------------------------------------

    def ref_name(self, ref: int) -> str:
        """Object name for a package reference (<0 import, >0 export, 0 None)."""
        if ref < 0:
            return self.imports[-ref - 1].name
        if ref > 0:
            return self.exports[ref - 1].name
        return "None"

    def ref_outer(self, ref: int) -> int:
        if ref < 0:
            return self.imports[-ref - 1].package
        if ref > 0:
            return self.exports[ref - 1].package
        return 0

    def ref_path(self, ref: int) -> str:
        """Dotted path including outers, e.g. Engine.StaticMeshActor."""
        parts = []
        seen = 0
        while ref and seen < 64:
            parts.append(self.ref_name(ref))
            ref = self.ref_outer(ref)
            seen += 1
        return ".".join(reversed(parts))

    def ref_class(self, ref: int) -> str:
        if ref < 0:
            return self.imports[-ref - 1].class_name
        if ref > 0:
            return self.ref_name(self.exports[ref - 1].class_ref) if self.exports[ref - 1].class_ref else "Class"
        return "None"

    def export_class(self, exp: Export) -> str:
        return self.ref_name(exp.class_ref) if exp.class_ref else "Class"

    def find_export(self, key: str) -> Export:
        if key.startswith("#"):
            return self.exports[int(key[1:])]
        if self._by_name is None:
            self._by_name = {e.name.lower(): e.index for e in self.exports}
        idx = self._by_name.get(key.lower())
        if idx is None:
            raise KeyError(f"no export named {key!r}")
        return self.exports[idx]

    def export_bytes(self, exp: Export) -> bytes:
        return self.data[exp.serial_offset:exp.serial_offset + exp.serial_size]

    def level(self) -> Optional[Export]:
        """The map's Level object ("MyLevel"), or None in other packages."""
        return next((e for e in self.exports if e.serial_size and self.export_class(e) == "Level"), None)

    def level_actors(self) -> Optional[List[int]]:
        """The export refs (index + 1) in the Level's actor list: the actors
        that make up the map, in its order; None without a Level object."""
        lvl = self.level()
        if lvl is None:
            return None
        return [ref for ref, _ in level_actor_list(self.export_bytes(lvl))[0]]

    # --- tagged properties -------------------------------------------------

    def read_properties(self, r: Reader, end: int, depth: int = 0) -> List[Property]:
        """Read a tagged property list up to and including its "None" tag."""
        props: List[Property] = []
        while r.pos < end:
            name = self.names[r.index()]
            if name == "None":
                return props
            info = r.u8()
            ptype = info & 0x0F
            size_code = (info >> 4) & 7
            is_array = bool(info & 0x80)
            struct_name = self.names[r.index()] if ptype == 10 else None
            # size code 0-4: fixed size (byte/word/dword/vector/rotator+1); 5-7: an
            # explicit u8/u16/u32 size follows.
            if size_code < 5:
                size = (1, 2, 4, 12, 16)[size_code]
            elif size_code == 5:
                size = r.u8()
            elif size_code == 6:
                size = r.u16()
            else:
                size = r.u32()
            array_index = 0
            if is_array and ptype != 3:
                # Not a compact INDEX (see Reader.index): a separate 1/2/4-byte
                # packed unsigned int, width selected by the top two bits.
                b = r.u8()
                if b & 0x80:
                    if b & 0x40:
                        array_index = ((b & 0x3F) << 24) | (r.u8() << 16) | (r.u8() << 8) | r.u8()
                    else:
                        array_index = ((b & 0x7F) << 8) | r.u8()
                else:
                    array_index = b
            vstart = r.pos
            if vstart + size > end:
                raise EOFError(f"property {name} ({size} bytes at {vstart:#x}) overruns {end:#x}")
            raw = r.data[vstart:vstart + size]
            value = self._decode_value(ptype, raw, is_array, struct_name, depth)
            props.append(Property(name, PROP_TYPES.get(ptype, str(ptype)), array_index, value,
                                  struct_name, size))
            r.pos = vstart + size
        raise EOFError("property list has no None terminator")

    def _decode_value(self, ptype: int, raw: bytes, flag: bool, struct_name: Optional[str], depth: int) -> Any:
        try:
            if ptype == 3:
                return flag
            if ptype == 1 and len(raw) == 1:
                return raw[0]
            if ptype == 2 and len(raw) == 4:
                return struct.unpack("<i", raw)[0]
            if ptype == 4 and len(raw) == 4:
                return struct.unpack("<f", raw)[0]
            if ptype in (5, 8):
                ref = Reader(raw).index()
                return {"ref": ref, "name": self.ref_path(ref)} if ref else None
            if ptype == 6:
                return self.names[Reader(raw).index()]
            if ptype == 13:
                return Reader(raw).fstring()
            if ptype == 10:
                sub = Reader(raw)
                props = self.read_properties(sub, len(raw), depth + 1)
                if sub.pos == len(raw):
                    return props
            if ptype == 11 and len(raw) == 12:
                return list(struct.unpack("<3f", raw))
            if ptype == 12 and len(raw) == 12:
                return list(struct.unpack("<3i", raw))
        except (EOFError, IndexError, UnicodeDecodeError, struct.error):
            pass
        return raw.hex()

    # --- Ion Storm actor layout ----------------------------------------------

    def read_actor(self, exp: Export) -> ActorData:
        """Decode state frame, tagged properties, gamesys blocks and the tail."""
        r = Reader(self.data, exp.serial_offset, exp.serial_offset + exp.serial_size)
        state = None
        props: List[Property] = []
        blocks: List[GamesysBlock] = []
        links: List[int] = []
        try:
            if exp.flags & RF_HasStack:
                node, state_node = r.index(), r.index()
                probe = r.u64()
                latent = r.u32()
                offset = r.index() if node else None
                state = {"node": node, "state_node": state_node, "probe_mask": probe,
                         "latent_action": latent, "offset": offset}
            props = self.read_properties(r, r.end)
            while r.remaining() >= 4:
                bid = r.u32()
                if bid == 0:
                    break
                ver = r.u32()
                size = r.u32()
                data = r.bytes(size)
                block = GamesysBlock(bid, ver, data)
                block.value = self.decode_gamesys(block)
                blocks.append(block)
            if r.remaining() >= 4:
                n = r.u32()
                if n > r.remaining():
                    raise ValueError(f"implausible link count {n}")
                links = [r.index() for _ in range(n)]
            return ActorData(state, props, blocks, links, r.data[r.pos:r.end])
        except (EOFError, IndexError, UnicodeDecodeError, struct.error, ValueError) as ex:
            return ActorData(state, props, blocks, links, r.data[r.pos:r.end], parse_error=str(ex))

    def decode_gamesys(self, block: GamesysBlock) -> Any:
        kind = block.kind
        raw = block.data
        try:
            if kind == "struct":
                sub = Reader(raw)
                props = self.read_properties(sub, len(raw))
                return props if sub.pos == len(raw) else raw.hex()
            if kind == "string":
                return Reader(raw).fstring()
            if kind == "float" and len(raw) == 4:
                return struct.unpack("<f", raw)[0]
            if kind == "int" and len(raw) == 4:
                return struct.unpack("<i", raw)[0]
            if kind == "bitfield" and len(raw) == 4:
                return struct.unpack("<I", raw)[0]
            if kind in ("bool", "byte") and len(raw) == 1:
                return raw[0]
            if kind == "name":
                return self.names[Reader(raw).index()]
            if kind in ("object", "class"):
                r = Reader(raw)
                v = r.index()
                if r.pos == len(raw):
                    return {"ref": v, "name": self.ref_path(v)} if v else None
            if kind == "array":
                return self._decode_array(raw)
        except (EOFError, IndexError, UnicodeDecodeError, struct.error):
            pass
        return raw.hex()

    def _decode_array(self, raw: bytes) -> Any:
        """Arrays carry no element type.  Try, in order: tagged structs,
        compact indices (object refs / names), FStrings; else return hex."""
        r = Reader(raw)
        n = r.index()
        start = r.pos
        for mode in ("struct", "index", "string"):
            r.pos = start
            try:
                items: List[Any] = []
                for _ in range(n):
                    if mode == "struct":
                        items.append(self.read_properties(r, len(raw)))
                    elif mode == "index":
                        items.append(r.index())
                    else:
                        items.append(r.fstring())
                if r.pos == len(raw):
                    return {"count": n, "items": items, "as": mode}
            except (EOFError, IndexError, UnicodeDecodeError, ValueError):
                continue
        return raw.hex()


# --- property helpers ----------------------------------------------------------

# The Level object's data starts with 13 bytes of unknown meaning (the same in
# every shipped map), then its actor list, as stock Unreal Engine 2's
# ULevelBase serialises it after them: the count twice, then one object ref
# per actor; the level's URL follows.
LEVEL_ACTORS_AT = 13


def level_actor_list(data: bytes) -> Tuple[List[Tuple[int, bytes]], int, int]:
    """The actor list in a Level object's data: ([(export ref, its encoded
    bytes)], where the refs start, where they end).  Raises ValueError when
    the data does not have that shape."""
    r = Reader(data, LEVEL_ACTORS_AT)
    count, again = r.u32(), r.u32()
    if count != again or count > len(data):
        raise ValueError(f"no actor list at +{LEVEL_ACTORS_AT} of the Level object ({count}, {again})")
    start = r.pos
    refs = []
    for _ in range(count):
        at = r.pos
        refs.append((r.index(), data[at:r.pos]))
    return refs, start, r.pos


def prop_value(props: List[Property], name: str, default: Any = None, index: int = 0) -> Any:
    for p in props:
        if p.name == name and p.array_index == index:
            return p.value
    return default


def struct_fields(value: Any) -> Dict[str, Any]:
    """Turn a decoded struct (list of Property) into {name: value}."""
    if isinstance(value, list):
        return {p.name: p.value for p in value if isinstance(p, Property)}
    return {}


def props_to_json(props: List[Property]) -> List[Dict[str, Any]]:
    out = []
    for p in props:
        v = _jsonable(p.value)
        d = {"name": p.name, "type": p.type, "value": v}
        if p.array_index:
            d["index"] = p.array_index
        if p.struct:
            d["struct"] = p.struct
        out.append(d)
    return out


def _jsonable(v: Any) -> Any:
    if isinstance(v, list) and v and isinstance(v[0], Property):
        return props_to_json(v)
    if isinstance(v, dict) and "items" in v:
        return {**v, "items": [_jsonable(x) for x in v["items"]]}
    return v


def gamesys_to_json(pkg: Package, blocks: List[GamesysBlock], names=None) -> List[Dict[str, Any]]:
    out = []
    for b in blocks:
        d = {"id": f"{b.id:#010x}", "kind": b.kind, "value": _jsonable(b.value)}
        if names is not None:
            d["name"] = names.name(b.id)
        out.append(d)
    return out


def format_props(props: List[Property], indent: str = "  ") -> List[str]:
    lines = []
    for p in props:
        idx = f"[{p.array_index}]" if p.array_index else ""
        v = p.value
        if isinstance(v, list) and v and isinstance(v[0], Property):
            inner = ", ".join(f"{q.name}={_short(q.value)}" for q in v)
            lines.append(f"{indent}{p.name}{idx} ({p.struct or p.type}) = ({inner})")
        else:
            lines.append(f"{indent}{p.name}{idx} ({p.type}) = {_short(v)}")
    return lines


def _short(v: Any) -> str:
    if isinstance(v, float):
        return f"{v:.6g}"
    if isinstance(v, dict) and "name" in v:
        return v["name"]
    if isinstance(v, list) and v and isinstance(v[0], Property):
        return "(" + ", ".join(f"{q.name}={_short(q.value)}" for q in v) + ")"
    return repr(v) if isinstance(v, str) else str(v)


# --- CLI ------------------------------------------------------------------------

def open_package(arg: str, game: Optional[str]) -> Package:
    p = Path(arg)
    if not p.is_file():
        p = resolve_map(game_dir(game), arg, ".gmp")
    return Package(p)


_NAMES_CACHE: List[Any] = []


def _property_names():
    """Gamesys property names from t3props (None if the table cannot be built)."""
    if not _NAMES_CACHE:
        try:
            from t3props import PropertyNames, load_table
            _NAMES_CACHE.append(PropertyNames(load_table()))
        except (SystemExit, OSError, ValueError, KeyError):
            _NAMES_CACHE.append(None)
    return _NAMES_CACHE[0]


def cmd_summary(pkg: Package, args) -> None:
    d = len(pkg.data)
    print(f"{pkg.path.name}: {d} bytes")
    print(f"  version {pkg.file_version}, licensee {pkg.licensee_version}, flags {pkg.package_flags:#x}")
    print(f"  names   {len(pkg.names):6d} at {pkg.name_offset:#x}")
    print(f"  imports {len(pkg.imports):6d} at {pkg.import_offset:#x} (ends {pkg.import_end:#x})")
    print(f"  exports {len(pkg.exports):6d} at {pkg.export_offset:#x} (ends {pkg.export_end:#x})")
    print(f"  guid    {pkg.guid.hex()}  generations {pkg.generations}")
    if pkg.ion_unknown is not None:
        print(f"  ion: DWORD at 0x24 = {pkg.ion_unknown:#x}")
    if pkg.depends_offset is not None:
        print(f"  ion: after generations = {pkg.ion_extra:#x}, extra table at {pkg.depends_offset:#x} "
              f"({pkg.export_offset - pkg.depends_offset} bytes)")
    classes = Counter(pkg.export_class(e) for e in pkg.exports)
    print("  top export classes: " + ", ".join(f"{k} {v}" for k, v in classes.most_common(12)))


def cmd_names(pkg: Package, args) -> None:
    for i, (n, f) in enumerate(zip(pkg.names, pkg.name_flags)):
        print(f"{i:6d} {f:#010x} {n}")


def cmd_imports(pkg: Package, args) -> None:
    for i, im in enumerate(pkg.imports):
        print(f"{-i - 1:6d} {im.class_package}.{im.class_name:24s} {pkg.ref_path(-i - 1)}")


def cmd_exports(pkg: Package, args) -> None:
    for e in pkg.exports:
        cls = pkg.export_class(e)
        if args.cls and cls.lower() != args.cls.lower():
            continue
        sup = f" super {pkg.ref_name(e.super_ref)}" if e.super_ref else ""
        outer = f" in {pkg.ref_path(e.package)}" if e.package else ""
        print(f"{e.index + 1:6d} {cls:28s} {e.name:36s} flags {e.flags:#010x} "
              f"size {e.serial_size:7d} @ {e.serial_offset:#08x}{sup}{outer}")


def cmd_classes(pkg: Package, args) -> None:
    count = Counter(pkg.export_class(e) for e in pkg.exports)
    size = Counter()
    for e in pkg.exports:
        size[pkg.export_class(e)] += e.serial_size
    for k, v in count.most_common():
        print(f"{v:6d} {size[k]:10d} {k}")


def cmd_dump(pkg: Package, args) -> None:
    exp = pkg.find_export(args.export)
    cls = pkg.export_class(exp)
    print(f"export #{exp.index} {exp.name} class {cls} flags {exp.flags:#010x} "
          f"size {exp.serial_size} @ {exp.serial_offset:#x}")
    a = pkg.read_actor(exp)
    if a.state:
        print(f"  state frame: {a.state}")
    print("  properties:")
    for line in format_props(a.properties, "    "):
        print(line)
    if a.gamesys:
        names = _property_names()
        print("  gamesys blocks:")
        for b in a.gamesys:
            v = b.value
            if isinstance(v, list) and v and isinstance(v[0], Property):
                v = "(" + ", ".join(f"{q.name}={_short(q.value)}" for q in v) + ")"
            label = names.name(b.id) if names else ""
            enum = names.enum_value(b.id, v) if names and b.kind == "byte" and isinstance(v, int) else None
            print(f"    {b.id:#010x} {b.kind:7s} {label:28s} = {_short(v)}" + (f" ({enum})" if enum else ""))
    if a.links:
        print("  links: " + ", ".join(pkg.ref_path(x) for x in a.links))
    if a.parse_error:
        print(f"  parse stopped: {a.parse_error}")
    print(f"  tail: {len(a.tail)} bytes" + (f": {a.tail[:64].hex()}" if a.tail else ""))
    if args.hex:
        raw = pkg.export_bytes(exp)
        for i in range(0, len(raw), 16):
            ch = raw[i:i + 16]
            print(f"  {exp.serial_offset + i:08x}: {ch.hex(' '):47s} "
                  + "".join(chr(c) if 32 <= c < 127 else "." for c in ch))


def cmd_json(pkg: Package, args) -> None:
    out: Dict[str, Any] = {
        "file": pkg.path.name,
        "version": pkg.file_version,
        "licensee": pkg.licensee_version,
        "names": pkg.names,
        "imports": [vars(i) for i in pkg.imports],
        "exports": [],
    }
    for e in pkg.exports:
        d = {"index": e.index + 1, "name": e.name, "class": pkg.export_class(e),
             "outer": pkg.ref_path(e.package) if e.package else None,
             "flags": e.flags, "size": e.serial_size, "offset": e.serial_offset}
        if args.props and e.serial_size and pkg.export_class(e) != "Class":
            a = pkg.read_actor(e)
            d["properties"] = props_to_json(a.properties)
            if a.gamesys:
                d["gamesys"] = gamesys_to_json(pkg, a.gamesys, _property_names())
            if a.links:
                d["links"] = [pkg.ref_path(x) for x in a.links]
            d["tail_bytes"] = len(a.tail)
            if a.parse_error:
                d["parse_error"] = a.parse_error
        out["exports"].append(d)
    Path(args.output).parent.mkdir(parents=True, exist_ok=True)
    Path(args.output).write_text(json.dumps(out, indent=1, default=str), encoding="utf-8")
    print(f"wrote {args.output}")


def main() -> None:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--game-dir", help="game install folder (default: $T3_GAME_DIR or registry)")
    sub = ap.add_subparsers(dest="cmd", required=True)
    for name in ("summary", "names", "imports", "classes"):
        s = sub.add_parser(name)
        s.add_argument("package")
    s = sub.add_parser("exports")
    s.add_argument("package")
    s.add_argument("--class", dest="cls")
    s = sub.add_parser("dump")
    s.add_argument("package")
    s.add_argument("export", help="export name or #index (0-based)")
    s.add_argument("--hex", action="store_true")
    s = sub.add_parser("json")
    s.add_argument("package")
    s.add_argument("-o", "--output", required=True)
    s.add_argument("--no-props", dest="props", action="store_false")
    args = ap.parse_args()
    pkg = open_package(args.package, args.game_dir)
    {"summary": cmd_summary, "names": cmd_names, "imports": cmd_imports, "exports": cmd_exports,
     "classes": cmd_classes, "dump": cmd_dump, "json": cmd_json}[args.cmd](pkg, args)


if __name__ == "__main__":
    run_cli(main)
