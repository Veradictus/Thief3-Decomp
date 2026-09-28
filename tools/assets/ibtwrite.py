#!/usr/bin/env python3
"""Writer for Ion Storm .ibt block files (the counterpart of ibt.py).

Re-serialises a block file read by ibt.IBT.  An unchanged file comes out byte
for byte identical, and one resource or several can be given new parts:

- The header and each table entry are kept as their raw bytes; only the
  fields that follow the layout are rewritten: the header's data start, data
  size, largest resource and part sizes and part count, and each entry's
  offset, size, padding, first part and part count.  The 20-byte values (the
  header's and every entry's), the alignment, the names (including any bytes
  after their NUL) and the load filters are copied as they are.
- The part table is re-encoded from its sizes, with a replaced resource's
  parts put in place of the old ones; later first-part indices move.
- The data area is copied verbatim, except for the replaced resources.  It is
  read as "spans" in file order: a resource's bytes, then everything up to
  the next resource (its padding, and any other gap).  Resources keep their
  order in the file; when one changes size, everything after it moves.

What this relies on, as ibt.py reads the format (docs/assets.md, section 3):

- Offsets are absolute file offsets, and header+08 + header+0C is the file
  size.  A replaced resource starts where its old one did (after the moves)
  and gets the smallest padding that makes size + padding a multiple of the
  header's alignment (0x800), filled with zero bytes.  Anything the old
  resource had after its padding is kept after the new padding.
- The data start is the table size rounded up to the alignment when it was
  so before; otherwise it is kept, and only moved up (aligned) when a larger
  part table no longer fits in front of it.  When the table changes size, the
  bytes between it and the data start are written as zeros.
- The largest resource and part sizes follow the new data when they matched
  the old data; otherwise they are kept, and only raised when the new data
  needs more (a loader may size a buffer by them).
- A resource of size 0 has no span: its offset follows the next resource's
  move.  Entries that share their data (same offset and size) are one span
  and are replaced together; they must also share their part range.

`t3texpack.py --selfcheck` checks each of these on the retail files.  This is a
library; the command line is t3texpack.py.
"""

from __future__ import annotations

import bisect
import struct
import sys
from dataclasses import dataclass, field
from pathlib import Path
from typing import Dict, Iterator, List, Optional, Sequence, Tuple, Union

sys.path.insert(0, str(Path(__file__).resolve().parent))
from ibt import ENTRY_SIZE, HEADER_SIZE, IBT  # noqa: E402

# Header fields rewritten by the layout (offsets into the 0x34-byte header).
H_DATA_START, H_DATA_SIZE, H_MAX_RESOURCE, H_MAX_PART, H_COUNT, H_PART_COUNT = 0x08, 0x0C, 0x10, 0x14, 0x18, 0x1C


class LayoutError(ValueError):
    """A block file, or a change to one, that cannot be laid out safely."""


def align_up(n: int, a: int) -> int:
    return (n + a - 1) // a * a if a > 1 else n


@dataclass
class Span:
    """One stretch of the data area: a resource's bytes, then its tail up to
    the next span (or the end of the file).  `entries` share the data."""
    offset: int
    size: int
    end: int
    entries: List[int] = field(default_factory=list)

    @property
    def tail(self) -> int:
        return self.end - self.offset - self.size


class BlockWriter:
    """A block file, with resources that can be given new parts.  Build from a
    path or from the file's bytes; write() returns the new file."""

    def __init__(self, source: Union[Path, str, bytes], name: Optional[str] = None) -> None:
        if isinstance(source, (bytes, bytearray, memoryview)):
            self.data = bytes(source)
            self.path = Path(name or "memory.ibt")
        else:
            self.path = Path(source)
            self.data = self.path.read_bytes()
        try:
            self.ibt = IBT(self.path, data=self.data)
        except struct.error as ex:
            raise LayoutError(f"{self.path.name}: the tables run past the end of the file") from ex
        except ValueError as ex:  # not a block file
            raise LayoutError(str(ex)) from ex
        ibt = self.ibt
        self.resources = ibt.resources
        self.part_sizes: List[int] = list(ibt.part_sizes)
        self.align = ibt.alignment or 1
        self.header = self.data[:HEADER_SIZE]
        self.entries = [self.data[HEADER_SIZE + i * ENTRY_SIZE:HEADER_SIZE + (i + 1) * ENTRY_SIZE]
                        for i in range(len(self.resources))]
        self.table_end = HEADER_SIZE + len(self.resources) * ENTRY_SIZE + len(self.part_sizes) * 4
        self.data_start = ibt.data_start
        name = self.path.name
        if not self.table_end <= self.data_start <= len(self.data):
            raise LayoutError(f"{name}: data start {self.data_start:#x} is not between the end of the tables "
                              f"({self.table_end:#x}) and the end of the file ({len(self.data):#x})")
        for r in self.resources:
            if r.first_part + r.part_count > len(self.part_sizes):
                raise LayoutError(f"{name}: resource {r.index} ({r.name}) has parts past the part table")
            if r.size and not self.data_start <= r.offset <= r.offset + r.size <= len(self.data):
                raise LayoutError(f"{name}: resource {r.index} ({r.name}) lies outside the data area")
        by_key: Dict[Tuple[int, int], Span] = {}
        for r in self.resources:
            if r.size:
                by_key.setdefault((r.offset, r.size), Span(r.offset, r.size, 0)).entries.append(r.index)
        self.spans: List[Span] = sorted(by_key.values(), key=lambda s: s.offset)
        for a, b in zip(self.spans, self.spans[1:]):
            if b.offset < a.offset + a.size:
                raise LayoutError(f"{name}: resources {a.entries[0]} and {b.entries[0]} overlap")
            a.end = b.offset
        if self.spans:
            self.spans[-1].end = len(self.data)
        self._span_of = {i: s for s in self.spans for i in s.entries}
        self._starts = [s.offset for s in self.spans]
        self.replaced: Dict[int, List[bytes]] = {}  # span offset -> new parts
        self.notes: List[str] = []

    # --- reading ------------------------------------------------------------------------

    def parts(self, index: int) -> List[bytes]:
        """A resource's parts as the file will hold them (replaced or not)."""
        span = self._span_of.get(index)
        if span is not None and span.offset in self.replaced:
            return list(self.replaced[span.offset])
        return self.ibt.split(self.resources[index])

    def replaced_entries(self) -> Dict[int, List[bytes]]:
        """Every entry given new parts (with the entries sharing its data)."""
        return {i: list(parts) for off, parts in self.replaced.items()
                for s in self.spans if s.offset == off for i in s.entries}

    def aliases(self, index: int) -> List[int]:
        """Other entries sharing a resource's data."""
        span = self._span_of.get(index)
        return [i for i in span.entries if i != index] if span else []

    def locate(self, offset: int) -> str:
        """What an offset of the original file belongs to."""
        if offset < HEADER_SIZE:
            return f"header +{offset:#x}"
        entries_end = HEADER_SIZE + len(self.entries) * ENTRY_SIZE
        if offset < entries_end:
            i, o = divmod(offset - HEADER_SIZE, ENTRY_SIZE)
            return f"table entry {i} ({self.resources[i].name}) +{o:#x}"
        if offset < self.table_end:
            return f"part table, part {(offset - entries_end) // 4}"
        if offset < self.data_start:
            return "between the tables and the data start"
        k = bisect.bisect_right(self._starts, offset) - 1
        if k < 0:
            return "before the first resource"
        s = self.spans[k]
        r = self.resources[s.entries[0]]
        if offset < s.offset + s.size:
            return f"resource {r.index} ({r.name}) +{offset - s.offset:#x}"
        return f"after resource {r.index} ({r.name}), +{offset - s.offset - s.size:#x} into its padding"

    # --- changes ------------------------------------------------------------------------

    def replace(self, index: int, parts: Sequence[bytes]) -> None:
        """Give a resource (and any entry sharing its data) new parts."""
        r = self.resources[index]
        span = self._span_of.get(index)
        if span is None:
            raise LayoutError(f"resource {index} ({r.name}) is empty and has no place in the data area")
        ranges = {(self.resources[i].first_part, self.resources[i].part_count) for i in span.entries}
        if len(ranges) > 1:
            raise LayoutError(f"resource {index} ({r.name}) shares its data but not its parts with "
                              f"{', '.join(str(i) for i in span.entries if i != index)}")
        first, count = r.first_part, r.part_count
        for o in self.resources:
            if o.index in span.entries or not o.part_count or not count:
                continue
            if o.first_part < first + count and first < o.first_part + o.part_count:
                raise LayoutError(f"resource {index} ({r.name}) shares parts with resource {o.index} ({o.name})")
        pad = max(self.resources[i].padding for i in span.entries)
        if span.tail < pad:
            raise LayoutError(f"resource {index} ({r.name}): its padding runs past the next resource or the file end")
        if not parts:
            raise LayoutError(f"resource {index} ({r.name}): a resource needs at least one part")
        self.replaced[span.offset] = [bytes(p) for p in parts]
        if len(span.entries) > 1:
            self.notes.append(f"resource {index} ({r.name}) shares its data with "
                              f"{', '.join(self.resources[i].name for i in span.entries if i != index)}: "
                              "they change together")

    # --- layout -------------------------------------------------------------------------

    def _layout(self):
        """Compute the new file: returns (header, table entries, part sizes,
        [table gap], [bytes before the first resource], [(span, new offset,
        data chunks, tail chunks)] in file order, file size)."""
        align = self.align
        # part table: replaced ranges in table order
        groups = []
        for s in self.spans:
            if s.offset in self.replaced:
                r = self.resources[s.entries[0]]
                groups.append((r.first_part, r.part_count, self.replaced[s.offset], s))
        groups.sort(key=lambda g: g[0])
        new_sizes: List[int] = []
        new_first: Dict[int, int] = {}
        ends, deltas, starts_new = [], [], []
        pos = total = 0
        for first, count, parts, s in groups:
            new_sizes += self.part_sizes[pos:first]
            new_first[s.offset] = len(new_sizes)
            starts_new.append(len(new_sizes))
            new_sizes += [len(p) for p in parts]
            pos = first + count
            total += len(parts) - count
            ends.append(first + count)
            deltas.append(total)
        new_sizes += self.part_sizes[pos:]

        def map_part(old: int) -> int:
            k = bisect.bisect_right(ends, old)
            if k < len(groups) and groups[k][0] < old:  # inside a replaced range (an empty entry)
                return starts_new[k] + min(old - groups[k][0], len(groups[k][2]))
            return old + (deltas[k - 1] if k else 0)

        # tables and data start
        count = len(self.resources)
        table_end = HEADER_SIZE + count * ENTRY_SIZE + len(new_sizes) * 4
        if table_end == self.table_end:
            data_start = self.data_start
            gap: List[bytes] = [self.data[self.table_end:self.data_start]]
        else:
            if self.data_start == align_up(self.table_end, align) or table_end > self.data_start:
                data_start = align_up(table_end, align)
            else:
                data_start = self.data_start
            gap = [bytes(data_start - table_end)]

        # data area
        view = memoryview(self.data)
        pos = data_start
        lead_end = self.spans[0].offset if self.spans else len(self.data)
        lead = view[self.data_start:lead_end]
        pos += len(lead)
        placed = []
        new_off: Dict[int, int] = {}
        new_size: Dict[int, int] = {}
        new_pad: Dict[int, int] = {}
        for s in self.spans:
            new_off[s.offset] = pos
            if s.offset in self.replaced:
                chunks = self.replaced[s.offset]
                size = sum(len(p) for p in chunks)
                pad = (-size) % align
                old_pad = max(self.resources[i].padding for i in s.entries)
                tail = [bytes(pad), view[s.offset + s.size + old_pad:s.end]]
                new_size[s.offset], new_pad[s.offset] = size, pad
            else:
                chunks = [view[s.offset:s.offset + s.size]]
                size = s.size
                tail = [view[s.offset + s.size:s.end]]
            placed.append((s, pos, chunks, tail))
            pos += size + sum(len(t) for t in tail)
        file_size = pos

        def map_offset(old: int) -> int:
            """Where an empty resource's offset goes: it follows the span it
            points into, or the next one (or the end of the file)."""
            if old < self.data_start:
                return old
            k = bisect.bisect_right(self._starts, old) - 1
            if k >= 0 and old < self.spans[k].offset + self.spans[k].size:
                s = self.spans[k]
                return new_off[s.offset] + min(old - s.offset, new_size.get(s.offset, s.size))
            if k + 1 < len(self.spans):
                nxt = self.spans[k + 1]
                return new_off[nxt.offset] - (nxt.offset - old)
            return file_size - (len(self.data) - old)

        # table entries
        entries: List[bytes] = []
        for r, raw in zip(self.resources, self.entries):
            e = bytearray(raw)
            s = self._span_of.get(r.index)
            if s is None:
                vals = (map_offset(r.offset), r.size, r.padding, map_part(r.first_part), r.part_count)
            elif s.offset in self.replaced:
                vals = (new_off[s.offset], new_size[s.offset], new_pad[s.offset], new_first[s.offset],
                        len(self.replaced[s.offset]))
            else:
                vals = (new_off[s.offset], r.size, r.padding, map_part(r.first_part), r.part_count)
            if any(not 0 <= v < 1 << 32 for v in vals):
                raise LayoutError(f"resource {r.index} ({r.name}): the new layout does not fit in 32 bits")
            struct.pack_into("<5I", e, 0, *vals)
            entries.append(bytes(e))

        # header
        head = bytearray(self.header)
        old_size, old_parts = self.ibt.max_resource_size, self.ibt.max_part_size
        derived_size_old = max((r.size for r in self.resources), default=0)
        derived_parts_old = max(self.part_sizes, default=0)
        sizes_new = [new_size.get(s.offset, s.size) if s else r.size
                     for r in self.resources for s in [self._span_of.get(r.index)]]
        derived_size_new = max(sizes_new, default=0)
        derived_parts_new = max(new_sizes, default=0)

        def follow(old: int, derived_old: int, derived_new: int) -> int:
            if old == derived_old:
                return derived_new
            return max(old, derived_new) if derived_new > derived_old else old

        data_size = self.ibt.data_size + (file_size - len(self.data)) - (data_start - self.data_start)
        if data_size < 0 or file_size >= 1 << 32:
            raise LayoutError("the new layout does not fit in 32 bits")
        struct.pack_into("<I", head, H_DATA_START, data_start)
        struct.pack_into("<I", head, H_DATA_SIZE, data_size)
        struct.pack_into("<I", head, H_MAX_RESOURCE, follow(old_size, derived_size_old, derived_size_new))
        struct.pack_into("<I", head, H_MAX_PART, follow(old_parts, derived_parts_old, derived_parts_new))
        struct.pack_into("<I", head, H_PART_COUNT, len(new_sizes))
        return bytes(head), entries, new_sizes, gap, [lead], placed, file_size

    def chunks(self) -> Iterator[bytes]:
        """The new file, piece by piece (memoryviews of the original where
        nothing changed)."""
        head, entries, sizes, gap, lead, placed, _ = self._layout()
        yield head
        yield b"".join(entries)
        yield struct.pack(f"<{len(sizes)}I", *sizes)
        yield from gap
        yield from lead
        for _s, _pos, data, tail in placed:
            yield from data
            yield from tail

    def write(self) -> bytes:
        return b"".join(self.chunks())


# --- checks ---------------------------------------------------------------------------------

def compare_bundles(old: bytes, new: bytes, replaced: Dict[int, List[bytes]], name: str = "bundle") -> List[str]:
    """Read a rewritten block file back with ibt.py and check it against the
    original: the same entries (types, names, 20-byte values, load filters),
    the same header values that are not layout, every resource that was not
    replaced byte-identical with the same parts, the replaced ones holding
    exactly their new parts, parts covering each resource, offsets aligned,
    padding within the file, and data start + data size = file size and the
    header's largest sizes covering the data when they did before.  Returns the problems (empty when all is well)."""
    problems: List[str] = []
    try:
        a, b = IBT(name, data=old), IBT(name, data=new)
    except (ValueError, struct.error) as ex:
        return [f"{name}: does not read back: {ex}"]
    if len(a.resources) != len(b.resources):
        return [f"{name}: {len(b.resources)} resources, expected {len(a.resources)}"]
    if old[:8] != new[:8] or old[0x18:0x1C] != new[0x18:0x1C] or old[0x20:HEADER_SIZE] != new[0x20:HEADER_SIZE]:
        problems.append(f"{name}: the header's magic, alignment, count or 20-byte value changed")
    if a.data_start + a.data_size == len(old) and b.data_start + b.data_size != len(new):
        problems.append(f"{name}: data start + data size is not the file size")
    if b.data_start < HEADER_SIZE + len(b.resources) * ENTRY_SIZE + len(b.part_sizes) * 4:
        problems.append(f"{name}: the data start lies inside the tables")
    align = b.alignment or 1
    for ra, rb in zip(a.resources, b.resources):
        ea = old[HEADER_SIZE + ra.index * ENTRY_SIZE:HEADER_SIZE + (ra.index + 1) * ENTRY_SIZE]
        eb = new[HEADER_SIZE + rb.index * ENTRY_SIZE:HEADER_SIZE + (rb.index + 1) * ENTRY_SIZE]
        label = f"{name}: resource {ra.index} ({ra.name})"
        if ea[0x14:] != eb[0x14:]:
            problems.append(f"{label}: its type, name, 20-byte value or load filter changed")
        if rb.size and (ra.offset % align == 0) != (rb.offset % align == 0):
            problems.append(f"{label}: offset {rb.offset:#x} lost its alignment")
        if rb.size and rb.offset + rb.size + rb.padding > len(new):
            problems.append(f"{label}: its data or padding runs past the end of the file")
        try:
            parts = b.split(rb)
        except (ValueError, EOFError) as ex:
            problems.append(f"{label}: {ex}")
            continue
        if ra.index in replaced:
            if parts != list(replaced[ra.index]):
                problems.append(f"{label}: does not hold its new parts")
        elif b.parts(rb) != a.parts(ra) or b.read(rb) != a.read(ra):
            problems.append(f"{label}: changed, but it was not replaced")
    for what, x in (("resource", lambda f: (f.max_resource_size, max((r.size for r in f.resources), default=0))),
                    ("part", lambda f: (f.max_part_size, max(f.part_sizes, default=0)))):
        (ha, da), (hb, db) = x(a), x(b)
        if ha >= da and hb < db:
            problems.append(f"{name}: the header's largest {what} size ({hb}) is below the largest {what} ({db})")
    return problems


def survey(w: BlockWriter) -> List[Tuple[str, bool]]:
    """How a block file is laid out, against what the writer assumes (for
    t3texpack.py --selfcheck): (statement, holds) pairs."""
    ibt, align = w.ibt, w.align
    res = ibt.resources
    sized = [r for r in res if r.size]
    out: List[Tuple[str, bool]] = []
    out.append(("data start = table size rounded up to the alignment",
                w.data_start == align_up(w.table_end, align)))
    out.append(("the first resource starts at the data start", bool(w.spans) and w.spans[0].offset == w.data_start))
    out.append(("data start + data size = file size", ibt.data_start + ibt.data_size == len(w.data)))
    out.append(("resources are in table order in the file",
                [s.entries[0] for s in w.spans] == sorted(s.entries[0] for s in w.spans)))
    out.append(("offsets are aligned", all(r.offset % align == 0 for r in sized)))
    out.append(("padding is the smallest that aligns the size", all(r.padding == (-r.size) % align for r in res)))
    out.append(("each resource ends where the next starts (size + padding)",
                all(s.tail == max(w.resources[i].padding for i in s.entries) for s in w.spans)))
    gaps = [w.data[w.table_end:w.data_start]] + [w.data[s.offset + s.size:s.end] for s in w.spans]
    out.append(("padding bytes are zero", not any(any(g) for g in gaps)))
    first = 0
    in_order = True
    for r in res:
        in_order &= r.first_part == first
        first += r.part_count
    out.append(("part ranges follow the table order", in_order and first == len(w.part_sizes)))
    out.append(("parts cover each resource exactly", all(sum(ibt.parts(r)) == r.size for r in res)))
    out.append(("header: largest resource size = the largest size",
                ibt.max_resource_size == max((r.size for r in res), default=0)))
    out.append(("header: largest part size = the largest part", ibt.max_part_size == max(w.part_sizes, default=0)))
    out.append(("no two entries share data", all(len(s.entries) == 1 for s in w.spans)))
    out.append(("names are NUL-padded", all(not any(e[0x29:0x130].split(b"\0", 1)[1]) for e in w.entries
                                             if b"\0" in e[0x29:0x130])))
    out.append(("load filters are 0xFFFFFFFF", all(e[0x130:0x134] == b"\xff\xff\xff\xff" for e in w.entries)))
    return out
