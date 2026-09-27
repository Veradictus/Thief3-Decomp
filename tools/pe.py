"""Minimal, dependency-free PE32 reader (headers, sections, directories, Rich header)."""

import struct
from dataclasses import dataclass
from typing import List, Optional, Tuple

IMAGE_SCN_CNT_CODE = 0x00000020
IMAGE_SCN_CNT_UNINITIALIZED_DATA = 0x00000080
IMAGE_SCN_MEM_EXECUTE = 0x20000000
IMAGE_SCN_MEM_READ = 0x40000000
IMAGE_SCN_MEM_WRITE = 0x80000000

DIRECTORY_NAMES = [
    "export", "import", "resource", "exception", "security", "basereloc",
    "debug", "architecture", "globalptr", "tls", "load_config", "bound_import",
    "iat", "delay_import", "com_descriptor", "reserved",
]


@dataclass
class Section:
    name: str
    va: int  # RVA
    vsize: int
    raw_ptr: int
    raw_size: int
    characteristics: int

    @property
    def executable(self) -> bool:
        return bool(self.characteristics & (IMAGE_SCN_MEM_EXECUTE | IMAGE_SCN_CNT_CODE))

    @property
    def writable(self) -> bool:
        return bool(self.characteristics & IMAGE_SCN_MEM_WRITE)

    @property
    def initialized_size(self) -> int:
        """Bytes backed by file data; the rest of vsize is zero-filled."""
        return min(self.raw_size, self.vsize)


@dataclass
class RichEntry:
    prodid: int
    build: int
    count: int


class PE:
    def __init__(self, data: bytes):
        self.data = data
        if data[:2] != b"MZ":
            raise ValueError("not an MZ executable")
        pe = struct.unpack_from("<I", data, 0x3C)[0]
        if data[pe:pe + 4] != b"PE\0\0":
            raise ValueError("not a PE executable")
        self.pe_offset = pe
        fh = pe + 4
        (self.machine, nsec, self.timestamp, _, _, opt_size,
         self.characteristics) = struct.unpack_from("<HHIIIHH", data, fh)
        oh = fh + 20
        magic = struct.unpack_from("<H", data, oh)[0]
        if magic != 0x10B:
            raise ValueError("only PE32 is supported")
        self.linker_version = (data[oh + 2], data[oh + 3])
        self.entry_rva = struct.unpack_from("<I", data, oh + 16)[0]
        self.image_base = struct.unpack_from("<I", data, oh + 28)[0]
        self.section_alignment, self.file_alignment = struct.unpack_from("<II", data, oh + 32)
        self.image_size = struct.unpack_from("<I", data, oh + 56)[0]
        self.subsystem = struct.unpack_from("<H", data, oh + 68)[0]
        ndirs = struct.unpack_from("<I", data, oh + 92)[0]
        self.directories: List[Tuple[int, int]] = [
            struct.unpack_from("<II", data, oh + 96 + 8 * i) for i in range(ndirs)
        ]
        self.sections: List[Section] = []
        so = oh + opt_size
        for i in range(nsec):
            o = so + 40 * i
            name = data[o:o + 8].rstrip(b"\0").decode("latin-1")
            vsize, va, raw_size, raw_ptr = struct.unpack_from("<IIII", data, o + 8)
            chars = struct.unpack_from("<I", data, o + 36)[0]
            self.sections.append(Section(name, va, vsize, raw_ptr, raw_size, chars))

    # -- address helpers -------------------------------------------------
    def section_for_rva(self, rva: int) -> Optional[Section]:
        for s in self.sections:
            if s.va <= rva < s.va + max(s.vsize, s.raw_size):
                return s
        return None

    def read_rva(self, rva: int, size: int) -> bytes:
        """Read `size` bytes at an RVA; bytes past the raw data read as zero."""
        s = self.section_for_rva(rva)
        if s is None:
            raise ValueError(f"RVA {rva:#x} is not mapped")
        off = rva - s.va
        avail = max(0, min(size, s.raw_size - off))
        chunk = self.data[s.raw_ptr + off:s.raw_ptr + off + avail]
        return chunk + b"\0" * (size - len(chunk))

    def directory(self, name: str) -> Tuple[int, int]:
        i = DIRECTORY_NAMES.index(name)
        return self.directories[i] if i < len(self.directories) else (0, 0)

    # -- metadata --------------------------------------------------------
    def rich_header(self) -> Tuple[Optional[int], List[RichEntry]]:
        end = self.data.find(b"Rich", 0, self.pe_offset)
        if end < 0:
            return None, []
        key = struct.unpack_from("<I", self.data, end + 4)[0]
        start = end - 4
        while start >= 0x40:
            if struct.unpack_from("<I", self.data, start)[0] ^ key == 0x536E6144:  # "DanS"
                break
            start -= 4
        entries = []
        for o in range(start + 16, end, 8):
            comp, count = (v ^ key for v in struct.unpack_from("<II", self.data, o))
            entries.append(RichEntry(comp >> 16, comp & 0xFFFF, count))
        return key, entries

    def codeview(self) -> Optional[Tuple[str, str, int]]:
        """(guid, pdb path, age) from an RSDS debug entry, if present."""
        rva, size = self.directory("debug")
        for i in range(size // 28):
            entry = self.read_rva(rva + 28 * i, 28)
            typ, sz, _, ptr = struct.unpack_from("<IIII", entry, 12)
            if typ == 2 and self.data[ptr:ptr + 4] == b"RSDS":
                guid = self.data[ptr + 4:ptr + 20].hex()
                age = struct.unpack_from("<I", self.data, ptr + 20)[0]
                path = self.data[ptr + 24:self.data.index(b"\0", ptr + 24)].decode("latin-1")
                return guid, path, age
        return None

    def imports(self) -> List[Tuple[str, List[str]]]:
        """[(dll, [function name or '#ordinal', ...]), ...]"""
        rva, _ = self.directory("import")
        out = []
        while rva:
            ilt, _, _, name_rva, iat = struct.unpack_from("<IIIII", self.read_rva(rva, 20))
            if not name_rva:
                break
            dll = self._cstr(name_rva)
            names = []
            thunk = ilt or iat
            while True:
                value = struct.unpack_from("<I", self.read_rva(thunk, 4))[0]
                if not value:
                    break
                names.append(f"#{value & 0xFFFF}" if value & 0x80000000 else self._cstr(value + 2))
                thunk += 4
            out.append((dll, names))
            rva += 20
        return out

    def _cstr(self, rva: int) -> str:
        s = self.section_for_rva(rva)
        off = s.raw_ptr + rva - s.va
        return self.data[off:self.data.index(b"\0", off)].decode("latin-1")


# Rich header product IDs for the Visual Studio 6.0 - .NET 2003 era.
# Source: the public "comp_id" tables maintained by the RE community.
RICH_PRODUCTS = {
    0x0001: "Import (import object)",
    0x000E: "MASM 6.13",
    0x000F: "MASM 7.10",
    0x0012: "MASM 6.14",
    0x0019: "Implib 7.00",
    0x001C: "C 13.00 (VC 7.0)",
    0x001D: "C++ 13.00 (VC 7.0)",
    0x0030: "C 12.x (VC 6.0 era)",
    0x0031: "C++ 12.x (VC 6.0 era)",
    0x003D: "Linker 7.00",
    0x0045: "Cvtres 7.00",
    0x005A: "Linker 7.10",
    0x005B: "Cvtomf 7.10",
    0x005C: "Export 7.10",
    0x005D: "Implib 7.10",
    0x005E: "Cvtres 7.10",
    0x005F: "C 13.10 (VC 7.1)",
    0x0060: "C++ 13.10 (VC 7.1)",
    0x0061: "C 13.10 std",
    0x0062: "C++ 13.10 std",
    0x0063: "C 13.10 LTCG",
    0x0064: "C++ 13.10 LTCG",
    0x0069: "AliasObj 7.10",
}
