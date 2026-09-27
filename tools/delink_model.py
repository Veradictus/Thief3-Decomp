#!/usr/bin/env python3
"""Build the `delink ida-split` inputs for T3Main.exe.

Reads the original executable, config/<version>/symbols.txt and splits.txt;
writes the delink model (the JSON schema delink's IDA exporter produces, see
dbalatoni13/delink crates/delink-ida/src/lib.rs) and the object grouping.

Everything except names and function bounds is derived from the executable:
  * segments come from the PE section table. The import address table is
    carved out of .rdata as an XTRN ".idata" segment and the zero-filled tail
    of .data becomes a BSS segment.
  * absolute relocations are recovered here. The exe has no .reloc table, so a
    relocation is any 4-byte field that holds an address inside the image:
      - code: disp32/imm32 operands of every instruction in every function,
        located exactly with iced-x86 constant offsets;
      - data: every 4-byte-aligned dword in initialised data.
    The unusual image base (0x10900000) makes such values unambiguous in
    practice. Switch tables at the end of a function are not decoded as code;
    delink recovers jump table entries, and rel32 calls/jumps.
  * relocation targets without a symbol get Ghidra-style DAT_/LAB_ names.
"""

import argparse
import bisect
import hashlib
import json
import sys
from array import array
from pathlib import Path
from typing import Dict, List, Optional, Tuple

from iced_x86 import Code, Decoder, MemorySize, Mnemonic, OpKind

import splits as splitslib
import symbols as symbolslib
from pe import PE


def build_segments(pe: PE) -> List[dict]:
    base = pe.image_base
    iat_rva, iat_size = pe.directory("iat")
    segments: List[dict] = []

    def seg(name: str, start: int, end: int, cls: str, w: bool = False, x: bool = False) -> None:
        if end > start:
            segments.append({
                "name": name, "start": base + start, "end": base + end,
                "perm_r": True, "perm_w": w, "perm_x": x, "class": cls, "bitness": 32,
            })

    for s in pe.sections:
        if s.name in (".rsrc", ".reloc"):
            continue  # resources and relocations (stripped; the section would be empty anyway) are not code/data
        start, vend, init_end = s.va, s.va + s.vsize, s.va + s.initialized_size
        if s.executable:
            seg(s.name, start, vend, "CODE", x=True)
        elif s.writable:
            seg(s.name, start, init_end, "DATA", w=True)
            seg(s.name, init_end, vend, "BSS", w=True)
        elif iat_size and start <= iat_rva < vend:
            seg(s.name, start, iat_rva, "CONST")
            seg(".idata", iat_rva, iat_rva + iat_size, "XTRN")
            seg(s.name, iat_rva + iat_size, vend, "CONST")
        else:
            seg(s.name, start, vend, "CONST")
    segments.sort(key=lambda s: s["start"])
    return segments


class Image:
    """Address-range queries over the model segments."""

    def __init__(self, segments: List[dict]):
        self.segments = segments
        self.starts = [s["start"] for s in segments]

    def segment(self, va: int) -> Optional[dict]:
        i = bisect.bisect_right(self.starts, va) - 1
        if i >= 0 and va < self.segments[i]["end"]:
            return self.segments[i]
        return None


def table_reference(insn) -> int:
    """Address of the switch table a dispatch instruction reads, or 0.

    MSVC switches: `jmp [reg*4 + jump_table]`, optionally preceded by
    `movzx reg, byte [reg + index_table]`.
    """
    if insn.op_count < 1:
        return 0
    if insn.mnemonic == Mnemonic.JMP and insn.op0_kind == OpKind.MEMORY and insn.memory_index_scale == 4:
        return insn.memory_displacement & 0xFFFFFFFF
    if (insn.mnemonic == Mnemonic.MOVZX and insn.op_count == 2 and insn.op1_kind == OpKind.MEMORY
            and insn.memory_size == MemorySize.UINT8):
        return insn.memory_displacement & 0xFFFFFFFF
    return 0


def code_relocations(pe: PE, image: Image, functions: List[symbolslib.Symbol],
                     code_objects: List[symbolslib.Symbol]) -> Tuple[List[dict], int]:
    """Absolute operands in every function's instructions.

    MSVC places a function's switch tables after all of its code, so decoding
    stops at the first table: a table object from symbols.txt, or a table a
    dispatch instruction points at.
    """
    relocs = []
    invalid = 0
    object_starts = [o.address for o in code_objects]
    for f in functions:
        code_end = f.end
        i = bisect.bisect_left(object_starts, f.address)
        if i < len(code_objects) and code_objects[i].address < f.end:
            code_end = code_objects[i].address
        data = pe.read_rva(f.address - pe.image_base, f.size)
        decoder = Decoder(32, data, ip=f.address)
        for insn in decoder:
            if insn.ip >= code_end:
                break
            if insn.code == Code.INVALID:
                invalid += 1
                continue
            table = table_reference(insn)
            if insn.next_ip <= table < code_end:
                code_end = table
            offsets = decoder.get_constant_offsets(insn)
            if offsets.displacement_size == 4:
                target = insn.memory_displacement & 0xFFFFFFFF
                if image.segment(target):
                    relocs.append((insn.ip + offsets.displacement_offset, target))
            if offsets.immediate_size == 4:
                for op in range(insn.op_count):
                    if insn.op_kind(op) == OpKind.IMMEDIATE32:
                        target = insn.immediate(op) & 0xFFFFFFFF
                        if image.segment(target):
                            relocs.append((insn.ip + offsets.immediate_offset, target))
    return [{"addr": a, "type": "OFF32", "size": 4, "target": t} for a, t in relocs], invalid


def data_relocations(pe: PE, image: Image) -> List[dict]:
    """Every 4-byte-aligned dword in DATA/CONST segments that points inside the image.

    BSS is zero-filled (nothing to scan), and CODE/XTRN are handled elsewhere
    (code operands by `code_relocations`, import slots by the loader).
    """
    relocs = []
    for seg in image.segments:
        if seg["class"] not in ("DATA", "CONST"):
            continue
        start, end = seg["start"], seg["end"]
        start += -start % 4
        words = array("I", pe.read_rva(start - pe.image_base, (end - start) & ~3))
        if sys.byteorder != "little":
            words.byteswap()
        for i, value in enumerate(words):
            if value and image.segment(value):
                relocs.append({"addr": start + 4 * i, "type": "OFF32", "size": 4, "target": value})
    return relocs


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("--exe", type=Path, required=True)
    parser.add_argument("--sha1", help="expected SHA-1 of --exe")
    parser.add_argument("--symbols", type=Path, required=True)
    parser.add_argument("--splits", type=Path, required=True)
    parser.add_argument("--chunk-size", type=lambda s: int(s, 0), default=0x10000)
    parser.add_argument("--model", type=Path, required=True, help="output: delink model JSON")
    parser.add_argument("--groups", type=Path, required=True, help="output: delink idapro.json grouping")
    args = parser.parse_args()

    exe_bytes = args.exe.read_bytes()
    if args.sha1 and hashlib.sha1(exe_bytes).hexdigest() != args.sha1.lower():
        sys.exit(f"{args.exe}: SHA-1 {hashlib.sha1(exe_bytes).hexdigest()} does not match {args.sha1}")
    pe = PE(exe_bytes)
    segments = build_segments(pe)
    image = Image(segments)
    symbols = symbolslib.load(args.symbols)
    functions = [s for s in symbols if s.is_function and s.size > 0]
    # Data inside code (switch tables) is skipped when decoding and left unnamed,
    # so references to it resolve as <owning function> + offset.
    code_objects = [
        s for s in symbols
        if not s.is_function and s.size > 0 and (image.segment(s.address) or {}).get("class") == "CODE"
    ]

    code, invalid = code_relocations(pe, image, functions, code_objects)
    data = data_relocations(pe, image)
    relocations = sorted({r["addr"]: r for r in code + data}.values(), key=lambda r: r["addr"])

    code_object_addrs = {o.address for o in code_objects}
    names = [
        {"addr": s.address, "name": s.name, "public": s.scope != "local", "weak": False, "is_func": s.is_function}
        for s in symbols
        if s.address not in code_object_addrs
    ]
    known = {s.address for s in symbols} - code_object_addrs
    fstarts = [f.address for f in functions]
    synthesized: Dict[int, str] = {}
    for r in relocations:
        t = r["target"]
        if t in known or t in synthesized:
            continue
        i = bisect.bisect_right(fstarts, t) - 1
        if i >= 0 and t < functions[i].end:
            continue  # delink resolves it as <function> + offset
        prefix = "LAB" if image.segment(t)["class"] == "CODE" else "DAT"
        synthesized[t] = f"{prefix}_{t:08x}"
    names += [{"addr": a, "name": n, "public": True, "weak": False, "is_func": False} for a, n in synthesized.items()]
    names.sort(key=lambda n: n["addr"])

    model = {
        "delink_ida_version": 1,
        "meta": {
            "arch": "x86", "procname": "metapc", "bits": 32, "endian": "little",
            "image_base": pe.image_base,
            "min_ea": segments[0]["start"], "max_ea": segments[-1]["end"],
            "filetype": "PE", "input_file": args.exe.name,
        },
        "segments": segments,
        "functions": [
            {"start": f.address, "end": f.end, "name": f.name, "thunk": False, "lib": False,
             "static": f.scope == "local", "public": f.scope != "local", "thunk_target": None}
            for f in functions
        ],
        "names": names,
        "relocations": relocations,
        "jump_tables": [],
    }
    args.model.parent.mkdir(parents=True, exist_ok=True)
    args.model.write_text(json.dumps(model, separators=(",", ":")), encoding="utf-8")

    units = splitslib.plan(splitslib.load(args.splits), functions, args.chunk_size)
    args.groups.write_text(json.dumps(splitslib.to_idapro(units), indent=1), encoding="utf-8")

    text = next(s for s in pe.sections if s.name == ".text")
    covered = sum(f.size for f in functions)
    print(
        f"{len(functions)} functions ({covered / text.vsize:.1%} of .text), {len(names)} names "
        f"({len(synthesized)} synthesized), {len(relocations)} relocations "
        f"({len(code)} code, {len(data)} data), {invalid} undecodable instructions, "
        f"{len(units)} units ({sum(u.auto for u in units)} auto)"
    )


if __name__ == "__main__":
    main()
