#!/usr/bin/env python3
"""Writer for Thief: Deadly Shadows Unreal packages (the counterpart of upkg.py).

Re-serialises a package parsed by upkg.Package: the summary (with Ion Storm's
fields), the name, import and export tables, the extra table and the object
data.  An unchanged package comes out byte for byte identical:

- The tables are re-encoded from their parsed values.  A compact index keeps
  the width it had in the file when that was wider than needed, and the sign
  bit of a negative zero; a name that does not re-encode exactly is kept as
  opaque bytes, and so is an extra table that is not a run of index lists.
- Objects that are not edited are copied verbatim, and so are the bytes
  between the known regions (padding, unknown data).
- The regions keep their order.  When one changes size, everything after it
  moves, and the summary's table offsets and the export table's serial sizes
  and offsets are recomputed.  Added names go at the end of the name table,
  and the last generation follows the counts when it matched them before.

Actor editing (ActorEdit) re-serialises the tagged properties and gamesys
blocks of one object; its state frame, links and native tail are copied
verbatim.  Flesh writes every struct as its own tagged list and omits fields
equal to their defaults: setting a missing field inserts its tag, and a value
set back to its default is written explicitly (the tag stays).

This is a library; the command line is t3pack.py.  See docs/assets.md,
section 8.
"""

from __future__ import annotations

import bisect
import math
import struct
import sys
from collections import Counter
from dataclasses import dataclass, field
from pathlib import Path
from typing import Any, Callable, Collection, Dict, List, Optional, Sequence, Tuple

sys.path.insert(0, str(Path(__file__).resolve().parent))
from t3common import Reader, write_index  # noqa: E402
from upkg import GAMESYS_TYPES, RF_HasStack, Export, Package  # noqa: E402


class LayoutError(ValueError):
    """A package or object that cannot be re-serialised safely."""


# --- encodings -------------------------------------------------------------------------

def _index_value(raw: bytes) -> int:
    return Reader(raw).index()


def enc_index(value: int, like: bytes = b"") -> bytes:
    """Compact index for `value`.  `like` is the encoding it replaces: if that
    was padded (wider than canonical), the result is padded to the same width,
    and a negative zero stays one.  Canonical when `like` is empty."""
    out = bytearray(write_index(value))
    if like:
        old = _index_value(like)
        if len(like) > len(write_index(old)) and len(like) > len(out):
            pad = len(like) - len(out)
            out[-1] |= 0x40 if len(out) == 1 else 0x80
            out += b"\x80" * (pad - 1) + b"\x00"
        if value == 0 and old == 0 and like[0] & 0x80:
            out[0] |= 0x80
    return bytes(out)


def is_padded(raw: bytes) -> bool:
    """True for a compact index that is not in canonical form."""
    return raw != write_index(_index_value(raw))


def enc_fstring(text: str, wide: bool = False) -> bytes:
    """FString: compact length including the NUL, latin-1 (UTF-16 when `wide`
    or when the text needs it); an empty string is a zero length."""
    if not text:
        return write_index(0)
    if not wide:
        try:
            b = text.encode("latin-1") + b"\0"
            return write_index(len(b)) + b
        except UnicodeEncodeError:
            pass
    b = text.encode("utf-16-le") + b"\0\0"
    return write_index(-(len(b) // 2)) + b


def _read_index(r: Reader) -> Tuple[int, bytes]:
    p = r.pos
    v = r.index()
    return v, r.data[p:r.pos]


# --- tables ------------------------------------------------------------------------------

@dataclass
class NameEntry:
    text: str
    flags: int
    wide: bool = False
    raw: Optional[bytes] = None  # the name's bytes, when they do not re-encode exactly

    def encode(self, asciiz: bool) -> bytes:
        if self.raw is not None:
            s = self.raw
        elif asciiz:
            s = self.text.encode("latin-1") + b"\0"
        else:
            s = enc_fstring(self.text, self.wide)
        return s + struct.pack("<I", self.flags)


@dataclass
class ImportEntry:
    class_package: int
    class_name: int
    package: int
    name: int
    shape: Tuple[bytes, bytes, bytes]  # original compact indices: class package, class name, name

    def encode(self) -> bytes:
        s = self.shape
        return (enc_index(self.class_package, s[0]) + enc_index(self.class_name, s[1]) +
                struct.pack("<i", self.package) + enc_index(self.name, s[2]))


@dataclass
class ExportEntry:
    class_ref: int
    super_ref: int
    package: int
    name: int
    flags: int
    shape: Tuple[bytes, bytes, bytes, bytes, bytes]  # class, super, name, serial size, serial offset

    def encode(self, size: int, offset: int) -> bytes:
        s = self.shape
        out = (enc_index(self.class_ref, s[0]) + enc_index(self.super_ref, s[1]) +
               struct.pack("<i", self.package) + enc_index(self.name, s[2]) +
               struct.pack("<I", self.flags) + enc_index(size, s[3]))
        return out + enc_index(offset, s[4]) if size > 0 else out


@dataclass
class Region:
    """A span of the source file: the summary, a table, one object's data, or
    unassigned bytes ("gap")."""
    kind: str
    start: int
    end: int
    index: int = -1        # export index of an object
    placed: bool = True    # False: an empty table whose offset is kept as it was
    new_start: int = 0


def _parse_lists(raw: bytes) -> Optional[List[List[int]]]:
    """The extra table as `u32 count, u32 index[count]` lists, or None when
    the bytes are not exactly such a run."""
    out: List[List[int]] = []
    pos = 0
    while pos < len(raw):
        if pos + 4 > len(raw):
            return None
        n = struct.unpack_from("<I", raw, pos)[0]
        if pos + 4 + 4 * n > len(raw):
            return None
        out.append(list(struct.unpack_from(f"<{n}I", raw, pos + 4)))
        pos += 4 + 4 * n
    return out


def _encode_lists(lists: List[List[int]]) -> bytes:
    return b"".join(struct.pack(f"<I{len(x)}I", len(x), *x) for x in lists)


class PackageWriter:
    """A package parsed for writing.  write() returns the file; set_object()
    replaces an object's data and name_index() adds names."""

    def __init__(self, pkg: Package) -> None:
        self.pkg = pkg
        self.data = pkg.data
        self.padded: Counter = Counter()   # compact indices in non-canonical form, per table
        self.opaque: Counter = Counter()   # entries kept as raw bytes, per table
        self.names: List[NameEntry] = []
        self.imports: List[ImportEntry] = []
        self.exports: List[ExportEntry] = []
        self._read_tables()
        self.orig_counts = (len(self.exports), len(self.names))
        self.added_names: List[str] = []
        self.objects: Dict[int, bytes] = {}
        self._exact: Dict[str, int] = {}
        self._folded: Dict[str, int] = {}
        self.regions = self._find_regions()
        extra = self.region("extra")
        self.extra_raw = self.data[extra.start:extra.end] if extra else b""
        self.extra = _parse_lists(self.extra_raw) if extra else None
        if extra and self.extra is None:
            self.opaque["extra table"] += 1
        self._layout: List[Tuple[int, int, Region, List[int]]] = []

    # --- reading -----------------------------------------------------------------

    def _index(self, r: Reader, table: str) -> Tuple[int, bytes]:
        v, raw = _read_index(r)
        if is_padded(raw):
            self.padded[table] += 1
        return v, raw

    def _read_tables(self) -> None:
        p, data = self.pkg, self.data
        r = Reader(data, p.name_offset)
        asciiz = p.file_version < 64
        for text in p.names:
            start = r.pos
            if asciiz:
                r.pos = data.index(b"\0", r.pos) + 1
                wide = False
            else:
                wide = Reader(data, r.pos).index() < 0
                r.fstring()
            raw = data[start:r.pos]
            entry = NameEntry(text, r.u32(), wide)
            if entry.encode(asciiz)[:-4] != raw:
                entry.raw = raw
                self.opaque["names"] += 1
            self.names.append(entry)
        self.names_end = r.pos

        r.pos = p.import_offset
        for _ in p.imports:
            cp, cp_raw = self._index(r, "imports")
            cn, cn_raw = self._index(r, "imports")
            pk = r.i32()
            on, on_raw = self._index(r, "imports")
            self.imports.append(ImportEntry(cp, cn, pk, on, (cp_raw, cn_raw, on_raw)))

        r.pos = p.export_offset
        for e in p.exports:
            cl, cl_raw = self._index(r, "exports")
            su, su_raw = self._index(r, "exports")
            pk = r.i32()
            on, on_raw = self._index(r, "exports")
            fl = r.u32()
            size, size_raw = self._index(r, "exports")
            off_raw = self._index(r, "exports")[1] if size > 0 else b""
            self.exports.append(ExportEntry(cl, su, pk, on, fl, (cl_raw, su_raw, on_raw, size_raw, off_raw)))

    def _find_regions(self) -> List[Region]:
        p, size = self.pkg, len(self.data)
        regs = [Region("summary", 0, p.header_size), Region("names", p.name_offset, self.names_end),
                Region("imports", p.import_offset, p.import_end), Region("exports", p.export_offset, p.export_end)]
        if p.file_version < 68:
            regs.append(Region("heritage", p.heritage_offset, p.heritage_offset + 16 * p.heritage_count))
        for e in p.exports:
            if e.serial_size > 0:
                regs.append(Region("object", e.serial_offset, e.serial_offset + e.serial_size, e.index))
        full = [g for g in regs if g.end > g.start]
        if p.depends_offset is not None:
            # the extra table runs up to the next region
            x = p.depends_offset
            nxt = [g.start for g in full if g.start >= x] + [size]
            inside = any(g.start < x < g.end for g in full)
            regs.append(Region("extra", x, x if inside else max(x, min(nxt))))
            full = [g for g in regs if g.end > g.start]
        for g in regs:
            if g.end == g.start and (g.start > size or any(f.start < g.start < f.end for f in full)):
                g.placed = False  # an empty table at an offset inside other data: keep the offset
        regs.sort(key=lambda g: (g.start, g.end > g.start))
        pos, out = 0, []
        for g in regs:
            if not g.placed:
                out.append(g)
                continue
            if g.end > size:
                raise LayoutError(f"{self._describe(g)} runs past the end of the file")
            if g.start < pos:
                raise LayoutError(f"{self._describe(g)} at {g.start:#x} overlaps the data before it")
            if g.start > pos:
                out.append(Region("gap", pos, g.start))
            out.append(g)
            pos = max(pos, g.end)
        if pos < size:
            out.append(Region("gap", pos, size))
        return out

    def region(self, kind: str) -> Optional[Region]:
        return next((g for g in self.regions if g.kind == kind), None)

    # --- editing -----------------------------------------------------------------

    def name_text(self, index: int) -> str:
        if index < 0:
            raise IndexError(f"negative name index {index}")
        return self.names[index].text

    def find_name(self, text: str) -> Optional[int]:
        """Index of a name: an exact match, else one that differs in case."""
        if not self._exact:
            for i, n in enumerate(self.names):
                self._exact.setdefault(n.text, i)
                self._folded.setdefault(n.text.lower(), i)
        i = self._exact.get(text)
        return i if i is not None else self._folded.get(text.lower())

    def name_index(self, text: str) -> int:
        """Index of a name, appending it to the name table when missing."""
        i = self.find_name(text)
        if i is not None:
            return i
        flags = Counter(n.flags for n in self.names).most_common(1)
        self.names.append(NameEntry(text, flags[0][0] if flags else 0))
        self.added_names.append(text)
        i = len(self.names) - 1
        self._exact.setdefault(text, i)
        self._folded.setdefault(text.lower(), i)
        return i

    def object_data(self, index: int) -> bytes:
        if index in self.objects:
            return self.objects[index]
        e = self.pkg.exports[index]
        return self.data[e.serial_offset:e.serial_offset + e.serial_size]

    def set_object(self, index: int, data: bytes) -> None:
        if self.pkg.exports[index].serial_size == 0 or not data:
            raise LayoutError(f"export #{index}: only non-empty objects can be replaced")
        self.objects[index] = bytes(data)

    # --- writing -----------------------------------------------------------------

    def _generations(self) -> List[Tuple[int, int]]:
        gens = list(self.pkg.generations)
        if gens and gens[-1] == self.orig_counts:
            gens[-1] = (len(self.exports), len(self.names))
        return gens

    def _summary_fields(self, off: Dict[str, int]) -> List[Tuple[str, bytes]]:
        p = self.pkg
        u32 = struct.Struct("<I").pack
        f = [("tag", u32(p.tag)), ("file version", struct.pack("<H", p.file_version)),
             ("licensee version", struct.pack("<H", p.licensee_version)), ("package flags", u32(p.package_flags)),
             ("name count", u32(len(self.names))), ("name offset", u32(off["names"])),
             ("export count", u32(len(self.exports))), ("export offset", u32(off["exports"])),
             ("import count", u32(len(self.imports))), ("import offset", u32(off["imports"]))]
        if p.file_version < 68:
            return f + [("heritage count", u32(p.heritage_count)), ("heritage offset", u32(off["heritage"]))]
        if p.ion_unknown is not None:
            f.append(("Ion DWORD at 0x24", u32(p.ion_unknown)))
        gens = self._generations()
        f += [("GUID", p.guid), ("generation count", u32(len(gens)))]
        f += [(f"generation {i}", struct.pack("<II", *g)) for i, g in enumerate(gens)]
        if p.depends_offset is not None:
            f += [("Ion DWORD after the generations", u32(p.ion_extra)), ("extra table offset", u32(off["extra"]))]
        return f

    @staticmethod
    def _entries(parts: Sequence[bytes]) -> Tuple[bytes, List[int]]:
        pos, starts = 0, []
        for b in parts:
            starts.append(pos)
            pos += len(b)
        return b"".join(parts), starts

    def _bytes(self, g: Region, off: Dict[str, int], objects: Dict[int, Region]) -> Tuple[bytes, List[int]]:
        """A region's bytes, and where its entries start (for locate())."""
        if g.kind == "summary":
            return self._entries([b for _, b in self._summary_fields(off)])
        if g.kind == "names":
            asciiz = self.pkg.file_version < 64
            return self._entries([n.encode(asciiz) for n in self.names])
        if g.kind == "imports":
            return self._entries([m.encode() for m in self.imports])
        if g.kind == "exports":
            parts = []
            for i, e in enumerate(self.exports):
                obj = objects.get(i)
                size = len(self.object_data(i)) if obj else 0
                parts.append(e.encode(size, obj.new_start if obj else 0))
            return self._entries(parts)
        if g.kind == "extra":
            return self._entries([_encode_lists([x]) for x in self.extra]) if self.extra is not None \
                else (self.extra_raw, [])
        if g.kind == "object":
            return self.object_data(g.index), []
        return self.data[g.start:g.end], []

    def _entry_label(self, g: Region, i: int) -> str:
        if g.kind == "summary":
            return self._summary_fields({k: 0 for k in ("names", "exports", "imports", "extra", "heritage")})[i][0]
        if g.kind == "names":
            return f"entry {i} ({self.names[i].text})"
        if g.kind == "imports":
            return f"entry {i} ({self.names[self.imports[i].name].text})"
        if g.kind == "exports":
            return f"entry {i} ({self.names[self.exports[i].name].text})"
        return f"list {i}"

    def write(self) -> bytes:
        """Serialise the package, laying the regions out again in order."""
        placed = [g for g in self.regions if g.placed]
        objects = {g.index: g for g in placed if g.kind == "object"}
        sizes = [g.end - g.start if g.kind != "object" else len(self.object_data(g.index)) for g in placed]
        for _ in range(8):
            pos = 0
            for g, n in zip(placed, sizes):
                g.new_start = pos
                pos += n
            off = {g.kind: (g.new_start if g.placed else g.start) for g in self.regions if g.kind != "object"}
            blobs = [self._bytes(g, off, objects) for g in placed]
            new_sizes = [len(b) for b, _ in blobs]
            if new_sizes == sizes:
                break
            sizes = new_sizes  # a compact offset changed width: lay out again
        else:
            raise LayoutError("the layout does not settle")
        self._layout = [(g.new_start, g.new_start + len(b), g, starts) for g, (b, starts) in zip(placed, blobs)]
        return b"".join(b for b, _ in blobs)

    def extra_bytes(self) -> bytes:
        return _encode_lists(self.extra) if self.extra is not None else self.extra_raw

    # --- reporting -----------------------------------------------------------------

    def _describe(self, g: Region) -> str:
        if g.kind == "object":
            e = self.pkg.exports[g.index]
            return f"object #{g.index} {e.name} ({self.pkg.export_class(e)})"
        return {"summary": "summary", "names": "name table", "imports": "import table",
                "exports": "export table", "extra": "extra table", "heritage": "heritage table",
                "gap": "unassigned bytes"}.get(g.kind, g.kind)

    def locate(self, offset: int) -> str:
        """What lies at `offset` in the file last produced by write()."""
        for start, end, g, starts in self._layout:
            if start <= offset < end:
                rel = offset - start
                i = bisect.bisect_right(starts, rel) - 1
                if i < 0:
                    return f"{self._describe(g)} +{rel:#x}"
                return f"{self._describe(g)}, {self._entry_label(g, i)} +{rel - starts[i]:#x}"
        return "past the end of the file"


def first_difference(a: bytes, b: bytes) -> Optional[int]:
    """Offset of the first byte where a and b differ (None when equal)."""
    if a == b:
        return None
    n = min(len(a), len(b))
    step = 1 << 16
    for pos in range(0, n, step):
        if a[pos:pos + step] != b[pos:pos + step]:
            return next(i for i in range(pos, min(pos + step, n)) if a[i] != b[i])
    return n


# --- object layout (tagged properties, gamesys blocks) ---------------------------------

_FIXED_SIZES = (1, 2, 4, 12, 16)


def _size_fits(code: int, size: int) -> bool:
    if code < 5:
        return size == _FIXED_SIZES[code]
    return size <= (0xFF, 0xFFFF, 0xFFFFFFFF)[code - 5]


def _size_code(size: int) -> int:
    """The size code UE2's writer picks."""
    if size in _FIXED_SIZES:
        return _FIXED_SIZES.index(size)
    return 5 if size <= 0xFF else 6 if size <= 0xFFFF else 7


@dataclass
class Tag:
    """One tagged property, kept in the shape it was read."""
    name: str
    name_raw: bytes                    # compact name index as found
    info: int                          # type | size code << 4 | array (or bool value) bit
    struct: Optional[str] = None
    struct_raw: bytes = b""
    array_raw: bytes = b""
    array_index: int = 0
    value: bytes = b""
    fields: Optional["TagList"] = None  # a struct value parsed as a tagged list

    @property
    def ptype(self) -> int:
        return self.info & 0x0F

    def encode(self) -> bytes:
        value = self.fields.encode() if self.fields is not None else self.value
        size = len(value)
        code = (self.info >> 4) & 7
        if not _size_fits(code, size):
            code = _size_code(size)
        out = self.name_raw + bytes([(self.info & 0x8F) | code << 4]) + self.struct_raw
        if code >= 5:
            out += struct.pack(("<B", "<H", "<I")[code - 5], size)
        return out + self.array_raw + value


@dataclass
class TagList:
    tags: List[Tag]
    end_raw: bytes  # the "None" name index that ends the list

    def find(self, name: str, index: int = 0) -> Optional[Tag]:
        n = name.lower()
        return next((t for t in self.tags if t.name.lower() == n and t.array_index == index), None)

    def encode(self) -> bytes:
        return b"".join(t.encode() for t in self.tags) + self.end_raw


def read_tags(r: Reader, name_of: Callable[[int], str]) -> TagList:
    """A tagged property list up to and including its "None", read the way
    upkg.Package.read_properties reads it."""
    tags: List[Tag] = []
    while True:
        ni, name_raw = _read_index(r)
        name = name_of(ni)
        if name == "None":
            return TagList(tags, name_raw)
        info = r.u8()
        ptype = info & 0x0F
        tag = Tag(name, name_raw, info)
        if ptype == 10:
            si, tag.struct_raw = _read_index(r)
            tag.struct = name_of(si)
        code = (info >> 4) & 7
        if code < 5:
            size = _FIXED_SIZES[code]
        else:
            size = r.u8() if code == 5 else r.u16() if code == 6 else r.u32()
        if info & 0x80 and ptype != 3:
            p = r.pos
            b = r.u8()
            if b & 0x80:
                if b & 0x40:
                    tag.array_index = ((b & 0x3F) << 24) | (r.u8() << 16) | (r.u8() << 8) | r.u8()
                else:
                    tag.array_index = ((b & 0x7F) << 8) | r.u8()
            else:
                tag.array_index = b
            tag.array_raw = r.data[p:r.pos]
        tag.value = r.bytes(size)
        tags.append(tag)


@dataclass
class Block:
    id: int
    version: int
    data: bytes

    def encode(self) -> bytes:
        return struct.pack("<III", self.id, self.version, len(self.data)) + self.data


@dataclass
class ObjectLayout:
    """An object in Ion Storm's layout: [state frame] tagged properties,
    gamesys blocks, and the rest (links and native data) as raw bytes."""
    state: bytes
    props: TagList
    blocks: List[Block] = field(default_factory=list)
    blocks_end: bytes = b""  # the zero id ending the blocks (absent when the object ends first)
    rest: bytes = b""

    def encode(self) -> bytes:
        return (self.state + self.props.encode() + b"".join(b.encode() for b in self.blocks) +
                self.blocks_end + self.rest)


def parse_object(data: bytes, flags: int, name_of: Callable[[int], str]) -> ObjectLayout:
    """Split an object's data the way upkg.Package.read_actor reads it."""
    r = Reader(data)
    try:
        if flags & RF_HasStack:
            node = r.index()
            r.index()
            r.u64()
            r.u32()
            if node:
                r.index()
        out = ObjectLayout(data[:r.pos], read_tags(r, name_of))
        while r.remaining() >= 4:
            p = r.pos
            bid = r.u32()
            if bid == 0:
                out.blocks_end = data[p:r.pos]
                break
            ver, size = r.u32(), r.u32()
            out.blocks.append(Block(bid, ver, r.bytes(size)))
        out.rest = data[r.pos:]
        return out
    except (EOFError, IndexError, struct.error) as ex:
        raise LayoutError(str(ex)) from ex


def parse_fields(tag: Tag, name_of: Callable[[int], str]) -> TagList:
    """A struct tag's value as a tagged list (cached in tag.fields)."""
    if tag.fields is None:
        r = Reader(tag.value)
        try:
            fl = read_tags(r, name_of)
        except (EOFError, IndexError, struct.error) as ex:
            raise LayoutError(f"{tag.name} is not a tagged list: {ex}") from ex
        if r.pos != len(tag.value):
            raise LayoutError(f"{tag.name} has {len(tag.value) - r.pos} bytes after its tagged list")
        tag.fields = fl
    return tag.fields


# --- actor editing ---------------------------------------------------------------------

PT_INT, PT_FLOAT, PT_STRUCT = 2, 4, 10
# Struct -> (field names in declaration order, field property type).
STRUCTS = {"Vector": (("X", "Y", "Z"), PT_FLOAT), "Rotator": (("Pitch", "Yaw", "Roll"), PT_INT)}


def f32(v: float) -> float:
    """`v` rounded to single precision (raises OverflowError out of range)."""
    return struct.unpack("<f", struct.pack("<f", v))[0]


def _scalar(ptype: int, raw: bytes) -> Any:
    return struct.unpack("<f" if ptype == PT_FLOAT else "<i", raw)[0]


def _pack(ptype: int, v: Any) -> bytes:
    return struct.pack("<f", v) if ptype == PT_FLOAT else struct.pack("<i", v)


def _fmt(v: Any) -> str:
    return f"{v:.7g}" if isinstance(v, float) else repr(v) if isinstance(v, str) else str(v)


def block_kind(block_id: int) -> str:
    return GAMESYS_TYPES.get((block_id >> 16) & 0x0FFF, f"type{block_id >> 16:#x}")


def gamesys_data(kind: str, value: Any, writer: PackageWriter, like: bytes = b"") -> bytes:
    """Block data for a scalar gamesys value (int for int/bool/byte/bitfield,
    float, str for name/string).  `like` is the data it replaces."""
    if kind == "float":
        return struct.pack("<f", value)
    if kind == "int":
        return struct.pack("<i", value)
    if kind == "bitfield":
        return struct.pack("<I", value)
    if kind in ("bool", "byte"):
        return bytes([value])
    if kind == "name":
        return enc_index(writer.name_index(value), like)
    if kind == "string":
        return enc_fstring(value, bool(like) and _index_value(like) < 0)
    raise LayoutError(f"{kind} values cannot be written")


class ActorEdit:
    """Edits to one actor export.  commit() stores the re-serialised object in
    the writer; `changes` describes what was done."""

    def __init__(self, writer: PackageWriter, exp: Export) -> None:
        if not exp.flags & RF_HasStack or exp.serial_size == 0:
            raise LayoutError(f"{exp.name} is not an actor (it has no state frame)")
        self.writer, self.exp = writer, exp
        data = writer.object_data(exp.index)
        self.layout = parse_object(data, exp.flags, writer.name_text)
        if self.layout.encode() != data:
            raise LayoutError(f"{exp.name} does not re-serialise exactly; not editing it")
        self.changes: List[str] = []

    def _new_tag(self, name: str, ptype: int, value: bytes = b"", struct_name: Optional[str] = None) -> Tag:
        w = self.writer
        tag = Tag(name, enc_index(w.name_index(name)), ptype, value=value)
        if struct_name:
            tag.struct = struct_name
            tag.struct_raw = enc_index(w.name_index(struct_name))
            tag.fields = TagList([], enc_index(w.name_index("None")))
        return tag

    def _insert_top(self, tag: Tag) -> None:
        """New top-level tags go at the end, except that Location and Rotation
        are kept next to each other."""
        tags = self.layout.props.tags
        names = [t.name.lower() for t in tags]
        pos = len(tags)
        if tag.name == "Location" and "rotation" in names:
            pos = names.index("rotation")
        elif tag.name == "Rotation" and "location" in names:
            pos = names.index("location") + 1
        tags.insert(pos, tag)

    def struct_values(self, prop: str, struct_name: str) -> List[Any]:
        """A struct property's field values as read (0 for absent fields)."""
        fields, ptype = STRUCTS[struct_name]
        tag = self.layout.props.find(prop)
        sub = self._fields(tag, prop, struct_name) if tag else None
        out = []
        for name in fields:
            ft = sub.find(name) if sub else None
            out.append(self._field_value(ft, ptype, prop) if ft else (0.0 if ptype == PT_FLOAT else 0))
        return out

    def _fields(self, tag: Tag, prop: str, struct_name: str) -> TagList:
        if tag.ptype != PT_STRUCT or (tag.struct or "").lower() != struct_name.lower():
            raise LayoutError(f"{self.exp.name}: {prop} is not a {struct_name} struct")
        return parse_fields(tag, self.writer.name_text)

    def _field_value(self, ft: Tag, ptype: int, prop: str) -> Any:
        if ft.ptype != ptype or len(ft.value) != 4 or ft.array_raw:
            raise LayoutError(f"{self.exp.name}: {prop}.{ft.name} has an unexpected type")
        return _scalar(ptype, ft.value)

    def set_struct(self, prop: str, struct_name: str, values: Sequence[Any], explicit: bool = False) -> None:
        """Set a Vector or Rotator property (a tagged list).  A field equal to
        the value read is left alone, which keeps an absent field absent when
        it stays 0.  A changed field is overwritten or inserted; one set back
        to 0 stays written.  `explicit` writes absent fields even when 0."""
        fields, ptype = STRUCTS[struct_name]
        tag = self.layout.props.find(prop)
        sub = self._fields(tag, prop, struct_name) if tag else None
        todo = []
        for name, new in zip(fields, values):
            ft = sub.find(name) if sub else None
            new = f32(new) if ptype == PT_FLOAT else int(new)
            if ft is not None:
                cur = self._field_value(ft, ptype, prop)
                if cur != new:
                    todo.append((name, ft, cur, new))
            elif new != 0 or explicit:
                todo.append((name, None, 0, new))
        if not todo:
            return
        if tag is None:
            tag = self._new_tag(prop, PT_STRUCT, struct_name=struct_name)
            self._insert_top(tag)
            sub = tag.fields
            self.changes.append(f"{prop}: added ({struct_name})")
        assert sub is not None
        for name, ft, cur, new in todo:
            if ft is not None:
                ft.value = _pack(ptype, new)
                self.changes.append(f"{prop}.{name}: {_fmt(cur)} -> {_fmt(new)}")
                continue
            ft = self._new_tag(name, ptype | 2 << 4, _pack(ptype, new))
            rank = fields.index(name)
            later = [i for i, t in enumerate(sub.tags) if t.name in fields and fields.index(t.name) > rank]
            sub.tags.insert(later[0] if later else len(sub.tags), ft)
            self.changes.append(f"{prop}.{name}: {_fmt(new)} (inserted)")

    def set_location(self, xyz: Sequence[float]) -> None:
        self.set_struct("Location", "Vector", xyz)

    def set_rotation(self, pyr: Sequence[int]) -> None:
        self.set_struct("Rotation", "Rotator", pyr)

    def tagged_float(self, prop: str) -> Optional[Tag]:
        tag = self.layout.props.find(prop)
        if tag is not None and (tag.ptype != PT_FLOAT or len(tag.value) != 4):
            raise LayoutError(f"{self.exp.name}: {prop} is not a float property")
        return tag

    def set_tagged_float(self, prop: str, value: float) -> None:
        new = f32(value)
        tag = self.tagged_float(prop)
        if tag is None:
            self._insert_top(self._new_tag(prop, PT_FLOAT | 2 << 4, _pack(PT_FLOAT, new)))
            self.changes.append(f"{prop}: {_fmt(new)} (inserted)")
            return
        cur = _scalar(PT_FLOAT, tag.value)
        if cur != new:
            tag.value = _pack(PT_FLOAT, new)
            self.changes.append(f"{prop}: {_fmt(cur)} -> {_fmt(new)}")

    def block(self, prop_id: int) -> Optional[Block]:
        return next((b for b in self.layout.blocks if b.id & 0xFFFF == prop_id), None)

    def set_block(self, prop_id: int, data: bytes, label: str, insert_id: Optional[int] = None,
                  shown: Any = None) -> None:
        """Set the actor's own gamesys block for `prop_id`, adding one with
        `insert_id` when it has none.  Blocks already in ascending property id
        order stay so; otherwise a new block goes last."""
        b = self.block(prop_id)
        text = _fmt(shown) if shown is not None else data.hex()
        if b is not None:
            if b.data != data:
                b.data = data
                self.changes.append(f"gamesys {label}: set to {text}")
            return
        if insert_id is None:
            raise LayoutError(f"{self.exp.name}: no block id known for gamesys {label}")
        if not self.layout.blocks_end:
            raise LayoutError(f"{self.exp.name} has no gamesys block list")
        blocks = self.layout.blocks
        versions = Counter(x.version for x in blocks).most_common(1)
        ids = [x.id & 0xFFFF for x in blocks]
        pos = bisect.bisect_right(ids, prop_id) if ids == sorted(ids) else len(ids)
        blocks.insert(pos, Block(insert_id, versions[0][0] if versions else 1, data))
        self.changes.append(f"gamesys {label}: {text} (added, id {insert_id:#010x})")

    def commit(self) -> bool:
        """Store the object in the writer if anything changed."""
        if self.changes:
            self.writer.set_object(self.exp.index, self.layout.encode())
        return bool(self.changes)


# --- checks ------------------------------------------------------------------------------

def compare_packages(old: Package, new: Package, edited: Collection[int] = ()) -> List[str]:
    """Differences between two packages other than the data of the `edited`
    exports and names appended to the table; empty for a clean patch.  An
    edited actor must keep its state frame, links and native tail."""
    out = []
    head = ("file_version", "licensee_version", "package_flags", "guid", "ion_unknown", "ion_extra")
    for k in head:
        if getattr(old, k) != getattr(new, k):
            out.append(f"summary: {k} changed")
    if new.names[:len(old.names)] != old.names:
        out.append("name table: existing names changed")
    if [vars(i) for i in new.imports] != [vars(i) for i in old.imports]:
        out.append("import table changed")
    if len(new.exports) != len(old.exports):
        return out + [f"export count {len(old.exports)} -> {len(new.exports)}"]
    for a, b in zip(old.exports, new.exports):
        if (a.class_ref, a.super_ref, a.package, a.name, a.flags) != (b.class_ref, b.super_ref, b.package,
                                                                       b.name, b.flags):
            out.append(f"export #{a.index} {a.name}: table entry changed")
        elif a.index not in edited:
            if old.export_bytes(a) != new.export_bytes(b):
                out.append(f"export #{a.index} {a.name}: data changed")
        elif a.flags & RF_HasStack:
            ra, rb = old.read_actor(a), new.read_actor(b)
            if rb.parse_error:
                out.append(f"export #{a.index} {a.name}: does not parse: {rb.parse_error}")
            elif (ra.state, ra.links, ra.tail) != (rb.state, rb.links, rb.tail):
                out.append(f"export #{a.index} {a.name}: state frame, links or tail changed")
    if PackageWriter(old).extra_bytes() != PackageWriter(new).extra_bytes():
        out.append("extra table changed")
    return out


def is_finite_f32(v: float) -> bool:
    try:
        return math.isfinite(v) and math.isfinite(f32(v))
    except OverflowError:
        return False
