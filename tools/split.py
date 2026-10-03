#!/usr/bin/env python3
"""Run `delink ida-split` into a clean directory, keep its log, write a stamp.

After the split, each object's code gets the relocations the exe no longer
records for the SEH chain head: MSVC reads it as fs:[__except_list], an
absolute symbol whose value (0) the linker wrote into the instruction, so the
split holds a plain fs:[0]. Without the relocation objdiff scores every
function with an exception frame below 100% (the gate, tools/agent/verify.py,
accepts both forms). Then delink's labels inside a function (a switch's
`jpt_` table and `$L_` cases) become the function plus an offset, as
tools/cc.py does for the compiler's: objdiff pairs references by name.
"""

import argparse
import re
import shutil
import struct
import subprocess
import sys
from pathlib import Path
from typing import Dict, List, Tuple

IMAGE_FILE_MACHINE_I386 = 0x14C
IMAGE_SCN_CNT_CODE = 0x20
IMAGE_SCN_LNK_NRELOC_OVFL = 0x01000000
IMAGE_REL_I386_DIR32 = 6
IMAGE_SYM_CLASS_EXTERNAL = 2
EXCEPT_LIST = b"__except_list"


def except_list_offsets(code: bytes) -> List[int]:
    """Offsets of the 4-byte displacements of fs:[0] operands in x86 code."""
    from iced_x86 import Decoder, Register
    out = []
    decoder = Decoder(32, code, ip=0)
    for insn in decoder:
        if (insn.memory_segment == Register.FS and insn.memory_base == Register.NONE
                and insn.memory_index == Register.NONE and insn.memory_displacement == 0):
            offsets = decoder.get_constant_offsets(insn)
            if offsets.displacement_size == 4:
                out.append(insn.ip + offsets.displacement_offset)
    return out


def add_except_list(path: Path) -> int:
    """Relocate the object's fs:[0] operands against __except_list; returns how many."""
    data = bytearray(path.read_bytes())
    machine, nsec, _, psym, nsym, opt, _ = struct.unpack_from("<HHIIIHH", data, 0)
    if machine != IMAGE_FILE_MACHINE_I386:
        return 0
    strtab_at = psym + 18 * nsym
    strtab = bytearray(data[strtab_at:strtab_at + struct.unpack_from("<I", data, strtab_at)[0]])
    symtab = bytearray(data[psym:strtab_at])

    changed = {}  # section header offset -> relocation records
    count = 0
    for i in range(nsec):
        header = 20 + opt + 40 * i
        size, raw, relocs_at, _, nreloc, _, chars = struct.unpack_from("<IIIIHHI", data, header + 16)
        if not chars & IMAGE_SCN_CNT_CODE or not size:
            continue
        first = 0
        if chars & IMAGE_SCN_LNK_NRELOC_OVFL:
            nreloc, first = struct.unpack_from("<I", data, relocs_at)[0], 1
        records = [struct.unpack_from("<IIH", data, relocs_at + 10 * k) for k in range(first, nreloc)]
        covered = {r[0] + b for r in records for b in range(4)}
        offsets = [o for o in except_list_offsets(bytes(data[raw:raw + size]))
                   if not any(o + b in covered for b in range(4))]
        if offsets:
            changed[header] = (records, offsets)
            count += len(offsets)
    if not changed:
        return 0

    symbol = nsym
    symtab += struct.pack("<IIIhHBB", 0, len(strtab), 0, 0, 0, IMAGE_SYM_CLASS_EXTERNAL, 0)
    strtab += EXCEPT_LIST + b"\0"
    struct.pack_into("<I", strtab, 0, len(strtab))
    for header, (records, offsets) in changed.items():
        records = sorted(records + [(o, symbol, IMAGE_REL_I386_DIR32) for o in offsets])
        chars = struct.unpack_from("<I", data, header + 36)[0]
        table = b"".join(struct.pack("<IIH", *r) for r in records)
        if len(records) >= 0xFFFF:
            table = struct.pack("<IIH", len(records) + 1, 0, 0) + table
            chars |= IMAGE_SCN_LNK_NRELOC_OVFL
        else:
            chars &= ~IMAGE_SCN_LNK_NRELOC_OVFL
        struct.pack_into("<I", data, header + 24, len(data))
        struct.pack_into("<H", data, header + 32, min(len(records), 0xFFFF))
        struct.pack_into("<I", data, header + 36, chars)
        data += table
    struct.pack_into("<II", data, 8, len(data), nsym + 1)
    data += symtab + strtab
    path.write_bytes(bytes(data))
    return count


def interior_resolver(symbols_txt: Path):
    """name -> (containing data object's name, offset) for delink's `DAT_<address>` labels that fall inside
    a data object symbols.txt names and sizes; None for any other name."""
    sys.path.insert(0, str(Path(__file__).resolve().parent))
    import bisect
    import symbols as symbolslib
    objects = sorted((s.address, s.end, s.name) for s in symbolslib.load(symbols_txt)
                     if not s.is_function and s.type != "alias" and s.size > 1)
    starts = [o[0] for o in objects]
    named = {s.address for s in symbolslib.load(symbols_txt)}

    def resolve(name: str):
        m = re.fullmatch(r"DAT_([0-9a-fA-F]{8})", name)
        if not m:
            return None
        address = int(m.group(1), 16)
        if address in named:
            return None  # an address symbols.txt names keeps its own name
        i = bisect.bisect_right(starts, address) - 1
        if i >= 0 and objects[i][0] < address < objects[i][1]:
            return objects[i][2], address - objects[i][0]
        return None
    return resolve


def fold_interior(path: Path, resolve) -> bool:
    """Make references to delink's labels inside named data objects the object plus an offset."""
    sys.path.insert(0, str(Path(__file__).resolve().parent / "agent"))
    import coff
    data = coff.Coff.load(path).fold_into(resolve)
    if data is not None:
        path.write_bytes(data)
    return data is not None


def fold_labels(path: Path) -> bool:
    """Make delink's labels inside a function (a switch's `jpt_` table and `$L_` cases) the function plus an
    offset, as tools/cc.py does for the compiler's: True when the object changed."""
    sys.path.insert(0, str(Path(__file__).resolve().parent / "agent"))
    import coff
    data = coff.Coff.load(path).fold_labels(lambda s: s.storage == coff.IMAGE_SYM_CLASS_LABEL)
    if data is not None:
        path.write_bytes(data)
    return data is not None


def eh_chains(exe: Path, symbols_txt: Path) -> Dict[str, Tuple[int, List[int]]]:
    """For each exception handler symbols.txt names (`__ehhandler$F`): its address and, by state, the address
    of its unwind funclet (0 for none), read from the exe through the FuncInfo the handler loads."""
    sys.path.insert(0, str(Path(__file__).resolve().parent))
    sys.path.insert(0, str(Path(__file__).resolve().parent / "agent"))
    import coff
    import pe
    import symbols as symbolslib
    image = pe.PE(exe.read_bytes())

    def words(address: int, count: int) -> Tuple[int, ...]:
        return struct.unpack(f"<{count}I", image.read_rva(address - image.image_base, 4 * count))

    out = {}
    for s in symbolslib.load(symbols_txt):
        if not s.name.startswith(coff.EH_HANDLER):
            continue
        try:
            if image.read_rva(s.address - image.image_base, 1) != b"\xB8":  # mov eax, offset FuncInfo
                continue
            magic, states, unwind = words(words(s.address + 1, 1)[0], 3)
            if magic & ~3 != coff.EH_MAGIC or states > 0x1000:
                continue
            out[s.name] = (s.address, [words(unwind + 8 * k + 4, 1)[0] for k in range(states)])
        except ValueError:  # an address outside the image
            continue
    return out


def name_eh(path: Path, chains: Dict[str, Tuple[int, List[int]]]) -> bool:
    """Give the object's exception tables the names tools/cc.py gives the compiler's (coff.Coff.eh_tables):
    the FuncInfo each handler loads and the unwind funclets the object defines (Ghidra's `Unwind@<address>`
    in symbols.txt). True when the object changed."""
    import coff
    obj = coff.Coff.load(path)
    rename: Dict[str, str] = {}
    taken = {s.name for s in obj.symbols}

    def give(old: str, new: str) -> None:
        if old not in rename and new not in taken:
            rename[old] = new
            taken.add(new)

    for h in obj.symbols:
        if not h.defined or h.name not in chains:
            continue
        function = h.name[len(coff.EH_HANDLER):]
        info = obj.reference(h.section, h.value + 1)
        if info is not None:
            give(info[0].name, coff.eh_funcinfo_name(function))
        for state, funclet in enumerate(chains[h.name][1]):
            name = f"Unwind@{funclet:08x}"
            if funclet and any(s.name == name and s.defined for s in obj.symbols):
                give(name, coff.eh_funclet_name(function, state))
    if not rename:
        return False
    path.write_bytes(obj.rewrite(rename=rename))
    return True


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--delink", type=Path, required=True)
    parser.add_argument("--model", type=Path, required=True)
    parser.add_argument("--exe", type=Path, required=True)
    parser.add_argument("--groups", type=Path, required=True)
    parser.add_argument("--outdir", type=Path, required=True)
    parser.add_argument("--stamp", type=Path, required=True)
    parser.add_argument("--symbols", type=Path, help="symbols.txt: fold labels inside named data objects")
    args = parser.parse_args()

    shutil.rmtree(args.outdir, ignore_errors=True)
    args.outdir.mkdir(parents=True)
    log = args.stamp.with_suffix(".log")
    cmd = [
        str(args.delink), "ida-split", str(args.model), str(args.exe),
        "--idapro", str(args.groups), "-o", str(args.outdir), "--coff",
    ]
    proc = subprocess.run(cmd, capture_output=True, text=True, encoding="utf-8", errors="replace")
    log.write_text(proc.stdout + proc.stderr, encoding="utf-8")
    summary = re.search(r"ida-split complete: (\d+) objects \((\d+) failed\)", proc.stdout)
    if proc.returncode != 0 or summary is None or summary.group(2) != "0":
        sys.stderr.write(proc.stdout[-4000:] + proc.stderr[-4000:])
        sys.exit(f"delink failed (exit {proc.returncode}); full log: {log}")
    relocated = sum(add_except_list(obj) for obj in sorted(args.outdir.rglob("*.obj")))
    folded = sum(fold_labels(obj) for obj in sorted(args.outdir.rglob("*.obj")))
    if args.symbols:
        resolve = interior_resolver(args.symbols)
        interior = sum(fold_interior(obj, resolve) for obj in sorted(args.outdir.rglob("*.obj")))
        chains = eh_chains(args.exe, args.symbols)
        eh = sum(name_eh(obj, chains) for obj in sorted(args.outdir.rglob("*.obj")))
    else:
        interior = eh = 0
    print(f"{summary.group(0)}; {relocated} fs:[0] operands relocated against __except_list; "
          f"switch labels folded in {folded} objects, interior labels in {interior}, "
          f"exception tables named in {eh}")
    args.stamp.write_text(summary.group(0) + "\n", encoding="utf-8")


if __name__ == "__main__":
    main()
