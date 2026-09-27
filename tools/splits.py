"""Translation-unit splits: config/<version>/splits.txt -> delink object groups.

splits.txt lists the translation units that have been identified, in link
order, by source path relative to src/:

    Engine/Src/UnActor.cpp:
        .text  start:0x10901000 end:0x10912340
        .text  start:0x10E0A000 end:0x10E0A100    (its .text$x EH funclets)
        .rdata start:0x10E50000 end:0x10E50100
        .data  start:0x10F00000 end:0x10F00040
        .bss   start:0x10F80000 end:0x10F80010

Ranges are half-open [start, end). A .text range must not cut through a
function. Every function no unit claims is grouped into an automatic
auto/text_<ADDRESS> unit of roughly `chunk_size` bytes, so the split always
covers all of .text; declaring a unit carves it out of those chunks. Data no
unit claims stays in __shared_data.
"""

import bisect
import re
from dataclasses import dataclass, field
from pathlib import Path
from typing import Dict, List, Sequence, Tuple

from symbols import Symbol

Range = Tuple[int, int]
SECTION_KEYS = {".text": "text", ".rdata": "rdata", ".data": "data", ".bss": "bss"}
_RANGE = re.compile(r"^(?P<section>\.\w+)\s+start:0x(?P<start>[0-9A-Fa-f]+)\s+end:0x(?P<end>[0-9A-Fa-f]+)\s*$")


@dataclass
class Unit:
    source: str  # path relative to src/, e.g. "Engine/Src/UnActor.cpp"
    auto: bool = False
    text: List[Range] = field(default_factory=list)
    rdata: List[Range] = field(default_factory=list)
    data: List[Range] = field(default_factory=list)
    bss: List[Range] = field(default_factory=list)

    @property
    def name(self) -> str:
        """Unit name: the source path without its extension."""
        return self.source.rsplit(".", 1)[0] if not self.auto else self.source

    @property
    def object(self) -> str:
        """Object path relative to the split output directory."""
        return self.name + ".obj"


def load(path: Path) -> List[Unit]:
    """Parse splits.txt (see the module docstring for the format) into declared Units."""
    units: List[Unit] = []
    current = None
    for lineno, raw in enumerate(path.read_text(encoding="utf-8").splitlines(), 1):
        line = raw.split("#", 1)[0].rstrip()
        if not line.strip():
            continue
        if not raw[0].isspace():
            if not line.endswith(":"):
                raise ValueError(f"{path}:{lineno}: expected '<source path>:'")
            current = Unit(source=line[:-1].strip())
            if current.source.startswith("auto/"):
                raise ValueError(f"{path}:{lineno}: 'auto/' is reserved for generated units")
            units.append(current)
            continue
        m = _RANGE.match(line.strip())
        if not m or current is None:
            raise ValueError(f"{path}:{lineno}: expected '<section> start:0x.. end:0x..' under a unit")
        key = SECTION_KEYS.get(m.group("section"))
        if key is None:
            raise ValueError(f"{path}:{lineno}: unknown section {m.group('section')}")
        start, end = int(m.group("start"), 16), int(m.group("end"), 16)
        if end <= start:
            raise ValueError(f"{path}:{lineno}: empty or reversed range")
        getattr(current, key).append((start, end))
    return units


def plan(declared: Sequence[Unit], functions: Sequence[Symbol], chunk_size: int,
         breaks: Sequence[int] = ()) -> List[Unit]:
    """Declared units plus auto units covering every unclaimed function. An auto
    unit never spans an address in `breaks` (e.g. a boundary between progress
    categories)."""
    claimed = sorted(r for u in declared for r in u.text)
    for a, b in zip(claimed, claimed[1:]):
        if b[0] < a[1]:
            raise ValueError(f"overlapping .text ranges {a[0]:#x}-{a[1]:#x} and {b[0]:#x}-{b[1]:#x}")
    starts = [r[0] for r in claimed]

    def claimed_at(address: int) -> bool:
        """Whether a declared unit's .text range already covers `address`."""
        i = bisect.bisect_right(starts, address) - 1
        return i >= 0 and address < claimed[i][1]

    def claim_between(lo: int, hi: int) -> bool:
        """Whether a declared range starts in [lo, hi): a gap an auto chunk must not span."""
        i = bisect.bisect_left(starts, lo)
        return i < len(starts) and starts[i] < hi

    auto: List[Unit] = []
    chunk = None
    for f in sorted(functions, key=lambda s: s.address):
        if claimed_at(f.address):
            chunk = None
            continue
        # Start a new auto chunk unless the current one can simply extend to
        # cover `f` too: still under chunk_size, and with no declared unit's
        # range in the gap. Such a range might hold no function of its own
        # (e.g. pure padding), so claimed_at() alone would not have reset
        # `chunk` already; without this check the auto chunk would silently
        # swallow bytes a declared unit owns.
        if (chunk is None or f.address - chunk.text[0][0] >= chunk_size or claim_between(chunk.text[0][1], f.address)
                or any(chunk.text[0][0] < b <= f.address for b in breaks)):
            chunk = Unit(source=f"auto/text_{f.address:08X}", auto=True, text=[(f.address, f.end)])
            auto.append(chunk)
        else:
            chunk.text[0] = (chunk.text[0][0], f.end)
    return list(declared) + auto


def to_idapro(units: Sequence[Unit]) -> Dict[str, dict]:
    """delink `idapro.json` grouping (dbalatoni13/delink crates/delink-ida/src/idapro_json.rs)."""
    return {
        u.object: {
            "functions": [],
            "function_ranges": [list(r) for r in u.text],
            "rdata": [list(r) for r in u.rdata],
            "data": [list(r) for r in u.data],
            "bss": [list(r) for r in u.bss],
        }
        for u in units
    }
