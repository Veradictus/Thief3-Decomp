"""Minimal COFF object reader and editor (i386, standard and /bigobj headers).

The matching tools use it to read symbols, section bytes and relocations, and
to edit a copy of an object: rename or undefine symbols, retarget or drop
relocations, patch relocated fields and append symbols. That is how a
compiled function is paired with its target for objdiff, and how the tests
turn a compiled object into something shaped like delink's output.
"""

import struct
from dataclasses import dataclass, field
from pathlib import Path
from typing import Dict, Iterable, List, Optional, Sequence, Set, Tuple

IMAGE_FILE_MACHINE_I386 = 0x14C
IMAGE_SCN_CNT_CODE = 0x00000020
IMAGE_SCN_MEM_WRITE = 0x80000000
IMAGE_SYM_CLASS_EXTERNAL = 2
IMAGE_SYM_CLASS_STATIC = 3
IMAGE_SYM_CLASS_LABEL = 6
IMAGE_SYM_DTYPE_FUNCTION = 0x20
IMAGE_REL_I386_DIR32 = 0x06
IMAGE_REL_I386_REL32 = 0x14
IMAGE_COMDAT_SELECT_NODUPLICATES = 1
IMAGE_COMDAT_SELECT_ANY = 2
_BIGOBJ_CLASS_ID = bytes.fromhex("c7a1bad1eebaa94baf20faf66aa4dcb8")


@dataclass
class Relocation:
    offset: int  # within the section
    symbol: int  # symbol table index
    type: int


@dataclass
class Section:
    index: int  # 1-based, as symbols refer to it
    name: str
    characteristics: int
    data: bytes
    relocations: List[Relocation] = field(default_factory=list)
    selection: int = 0  # COMDAT selection, from the section symbol's aux record
    header: int = 0  # file offsets of the section header, raw data and relocation table
    raw: int = 0
    reloc_table: int = 0

    @property
    def is_code(self) -> bool:
        return bool(self.characteristics & IMAGE_SCN_CNT_CODE)

    @property
    def writable(self) -> bool:
        return bool(self.characteristics & IMAGE_SCN_MEM_WRITE)


@dataclass
class Symbol:
    index: int
    name: str
    value: int
    section: int  # 0 undefined, -1 absolute, -2 debug, else a Section.index
    type: int
    storage: int
    aux: bytes  # raw auxiliary records

    @property
    def defined(self) -> bool:
        return self.section > 0

    @property
    def external(self) -> bool:
        return self.storage == IMAGE_SYM_CLASS_EXTERNAL

    @property
    def is_function(self) -> bool:
        return (self.type & 0xF0) == IMAGE_SYM_DTYPE_FUNCTION

    @property
    def is_section(self) -> bool:
        """The section's own symbol (static, value 0, section definition aux record)."""
        return self.storage == IMAGE_SYM_CLASS_STATIC and self.value == 0 and bool(self.aux)


class Coff:
    def __init__(self, data: bytes):
        self.data = data
        sig1, sig2 = struct.unpack_from("<HH", data, 0)
        self.bigobj = sig1 == 0 and sig2 == 0xFFFF and data[12:28] == _BIGOBJ_CLASS_ID
        if self.bigobj:
            self.machine = struct.unpack_from("<H", data, 6)[0]
            nsec, self.symtab, nsym = struct.unpack_from("<III", data, 44)
            sec_off, self.sym_size, self.nsym_offset = 56, 20, 52
        else:
            self.machine, nsec, _, self.symtab, nsym, opt, _ = struct.unpack_from("<HHIIIHH", data, 0)
            sec_off, self.sym_size, self.nsym_offset = 20 + opt, 18, 12
        if self.machine != IMAGE_FILE_MACHINE_I386:
            raise ValueError(f"not an i386 COFF object (machine {self.machine:#x})")
        strtab = self.symtab + nsym * self.sym_size
        self.strtab = data[strtab:strtab + struct.unpack_from("<I", data, strtab)[0]] if nsym else b"\4\0\0\0"

        self.sections: List[Section] = []
        for i in range(nsec):
            o = sec_off + 40 * i
            raw_name = data[o:o + 8].rstrip(b"\0").decode("latin-1")
            if raw_name.startswith("/"):
                raw_name = self._string(int(raw_name[1:]))
            _, _, size, ptr, rptr, _, nrel, _, chars = struct.unpack_from("<IIIIIIHHI", data, o + 8)
            relocs = [Relocation(*struct.unpack_from("<IIH", data, rptr + 10 * r)) for r in range(nrel)]
            body = data[ptr:ptr + size] if ptr else bytes(size)  # no raw data: uninitialised (.bss)
            self.sections.append(Section(i + 1, raw_name, chars, body, relocs, header=o, raw=ptr, reloc_table=rptr))

        self.symbols: List[Symbol] = []
        self.slots: List[Optional[Symbol]] = []  # by symbol table index; aux slots are None
        i = 0
        while i < nsym:
            o = self.symtab + i * self.sym_size
            if data[o:o + 4] == b"\0\0\0\0":
                name = self._string(struct.unpack_from("<I", data, o + 4)[0])
            else:
                name = data[o:o + 8].rstrip(b"\0").decode("latin-1")
            if self.bigobj:
                value, section, typ, storage, naux = struct.unpack_from("<IiHBB", data, o + 8)
            else:
                value, section, typ, storage, naux = struct.unpack_from("<IhHBB", data, o + 8)
            aux = data[o + self.sym_size:o + self.sym_size * (1 + naux)]
            sym = Symbol(i, name, value, section, typ, storage, aux)
            self.symbols.append(sym)
            self.slots += [sym] + [None] * naux
            if sym.is_section and 0 < section <= nsec and len(aux) >= 15:
                self.sections[section - 1].selection = aux[14]
            i += 1 + naux

    @classmethod
    def load(cls, path: Path) -> "Coff":
        return cls(Path(path).read_bytes())

    def _string(self, offset: int) -> str:
        end = self.strtab.index(b"\0", offset)
        return self.strtab[offset:end].decode("latin-1")

    # -- queries -------------------------------------------------------------
    def section(self, index: int) -> Optional[Section]:
        return self.sections[index - 1] if 0 < index <= len(self.sections) else None

    def symbol(self, name: str) -> Optional[Symbol]:
        """The defined symbol called `name`, else an undefined one, else None."""
        found = [s for s in self.symbols if s.name == name]
        return next((s for s in found if s.defined), found[0] if found else None)

    def extent(self, sym: Symbol) -> Tuple[int, int]:
        """[start, end) of a defined symbol in its section: up to the next symbol or the section end."""
        end = len(self.section(sym.section).data)
        for other in self.symbols:
            if other.section == sym.section and sym.value < other.value < end and not other.is_section:
                end = other.value
        return sym.value, end

    def functions(self) -> List[Symbol]:
        """Defined function symbols."""
        return [s for s in self.symbols if s.defined and s.is_function]

    def relocations(self, section: int, start: int = 0, end: Optional[int] = None) -> List[Tuple[int, Relocation]]:
        """(index in the section's table, relocation) for relocations with start <= offset < end."""
        sec = self.section(section)
        stop = len(sec.data) if end is None else end
        return [(i, r) for i, r in enumerate(sec.relocations) if start <= r.offset < stop]

    def addend(self, section: int, reloc: Relocation) -> int:
        """The addend i386 COFF keeps in the relocated field (MSVC stores 0 for a
        plain call or a reference to a symbol's start)."""
        return struct.unpack_from("<i", self.section(section).data, reloc.offset)[0]

    # -- editing -------------------------------------------------------------
    def rewrite(
        self,
        rename: Optional[Dict[str, str]] = None,
        undefine: Iterable[str] = (),
        retarget: Optional[Dict[Tuple[int, int], int]] = None,
        drop: Iterable[Tuple[int, int]] = (),
        patch: Optional[Dict[Tuple[int, int], bytes]] = None,
        add: Sequence[Tuple[str, int, int, int, int]] = (),
    ) -> bytes:
        """An edited copy of the object.

        rename    old name -> new name, for every symbol of that name
        undefine  names of defined symbols to turn into undefined externals
        retarget  (section, relocation index) -> new symbol table index
        drop      (section, relocation index) of relocations to delete
        patch     (section, offset) -> bytes written over the raw data
        add       (name, value, section, type, storage) symbols appended to the table

        Sections, data and relocation tables keep their places (a table only
        shrinks); the symbol and string tables are rebuilt at the end of the
        file, where compilers and delink put them.
        """
        rename = rename or {}
        undefine = set(undefine)
        retarget = retarget or {}
        drop_set: Set[Tuple[int, int]] = set(drop)
        tail = self.symtab + len(self.slots) * self.sym_size + len(self.strtab)
        if tail != len(self.data):
            raise ValueError("unexpected data after the string table")
        out = bytearray(self.data[:self.symtab])
        for (section, offset), blob in (patch or {}).items():
            sec = self.section(section)
            if offset < 0 or offset + len(blob) > len(sec.data) or not sec.raw:
                raise ValueError(f"patch outside section {sec.name}")
            out[sec.raw + offset:sec.raw + offset + len(blob)] = blob
        relocs_left: Dict[int, int] = {}
        for sec in self.sections:
            if not any(k[0] == sec.index for k in list(retarget) + list(drop_set)):
                continue
            kept = [
                Relocation(r.offset, retarget.get((sec.index, i), r.symbol), r.type)
                for i, r in enumerate(sec.relocations) if (sec.index, i) not in drop_set
            ]
            for i, r in enumerate(kept):
                struct.pack_into("<IIH", out, sec.reloc_table + 10 * i, r.offset, r.symbol, r.type)
            struct.pack_into("<H", out, sec.header + 32, len(kept))
            relocs_left[sec.index] = len(kept)

        # Keep the old string table as a prefix: long section names point into it.
        strings = bytearray(self.strtab)
        fmt = "<IiHBB" if self.bigobj else "<IhHBB"
        pad = b"\0" * (self.sym_size - 18)

        def entry(name: str, value: int, section: int, typ: int, storage: int, naux: int) -> bytes:
            encoded = name.encode("latin-1")
            if len(encoded) <= 8:
                raw_name = encoded.ljust(8, b"\0")
            else:
                raw_name = struct.pack("<II", 0, len(strings))
                strings.extend(encoded + b"\0")
            return raw_name + struct.pack(fmt, value, section, typ, storage, naux)

        table = bytearray()
        for sym in self.symbols:
            section, value, storage, aux = sym.section, sym.value, sym.storage, bytearray(sym.aux)
            if sym.name in undefine and sym.defined and not sym.is_section:
                section, value, storage = 0, 0, IMAGE_SYM_CLASS_EXTERNAL
            if sym.is_section and section in relocs_left and len(aux) >= 6:
                struct.pack_into("<H", aux, 4, relocs_left[section])  # the section definition's relocation count
            table += entry(rename.get(sym.name, sym.name), value, section, sym.type, storage, len(aux) // self.sym_size)
            table += aux
        for name, value, section, typ, storage in add:
            table += entry(name, value, section, typ, storage, 0) + pad
        struct.pack_into("<I", strings, 0, len(strings))
        struct.pack_into("<I", out, self.nsym_offset, len(self.slots) + len(add))
        return bytes(out) + bytes(table) + bytes(strings)


def undefined_object(names: Sequence[str], anchor: str = "_t3_anchor") -> bytes:
    """A one-byte-function object that references every name in `names`.

    objdiff demangles every symbol of the object it diffs, undefined ones
    included, so this gives an MSVC demangler that works off Windows (the
    bundle's undname.exe needs the real msvcr71.dll).
    """
    strings = bytearray(b"\0\0\0\0")
    symbols = bytearray()

    def add(name: str, value: int, section: int, typ: int, storage: int) -> None:
        encoded = name.encode("latin-1")
        if len(encoded) <= 8:
            raw_name = encoded.ljust(8, b"\0")
        else:
            raw_name = struct.pack("<II", 0, len(strings))
            strings.extend(encoded + b"\0")
        symbols.extend(raw_name + struct.pack("<IhHBB", value, section, typ, storage, 0))

    add(anchor, 0, 1, IMAGE_SYM_DTYPE_FUNCTION, IMAGE_SYM_CLASS_EXTERNAL)
    for name in names:
        add(name, 0, 0, 0, IMAGE_SYM_CLASS_EXTERNAL)
    struct.pack_into("<I", strings, 0, len(strings))
    code = b"\xC3"
    header_size = 20 + 40
    symtab = header_size + len(code)
    header = struct.pack("<HHIIIHH", IMAGE_FILE_MACHINE_I386, 1, 0, symtab, 1 + len(names), 0, 0)
    section = b".text\0\0\0" + struct.pack("<IIIIIIHHI", 0, 0, len(code), header_size, 0, 0, 0, 0, 0x60500020)
    return header + section + code + bytes(symbols) + bytes(strings)
