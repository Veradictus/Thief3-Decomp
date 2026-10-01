#!/usr/bin/env python3
"""A candidate's whole function next to the target's, without spending an attempt.

    python tools/agent/sidebyside.py <addr> <file.cpp> [--symbol NAME] [--all]

try.py prints only the rows around differences and counts every compile
against the 12-attempt cap. This compiles the file with the same compiler
and flags (Project.compile), decodes both functions with iced-x86 and prints
every instruction side by side, aligned by difflib, so the shape of a
candidate can be explored first and try.py kept for the versions worth
scoring. It only looks: nothing is recorded and no verdict is given (use
try.py and accept.py for that).

References are shown by name. The candidate's relocated fields are filled
with the address symbols.txt gives their symbol (by decorated name or by the
Class::Method it demangles to), so both sides decode alike; a symbol
symbols.txt does not know gets a placeholder address and keeps its own name,
and its rows are marked `r` against the target's FUN_/DAT_ name (a naming
claim that try.py records as provisional). Rows that differ otherwise are
marked `~`. The listing stops at the end of the code
(switch tables are not decoded), and it fails when the file does not compile.
"""

import argparse
import difflib
import re
import struct
import sys
import tempfile
from pathlib import Path
from typing import Dict, List, Tuple

HERE = Path(__file__).resolve().parent
sys.path.insert(0, str(HERE))

import coff  # noqa: E402
from common import Project, demangle, qualified_name  # noqa: E402
from verify import TargetImage, Verifier  # noqa: E402

ADDRESS = re.compile(r"\b[0-9A-F]{6,8}h\b")
# A reference by name: decorated, placeholder or Class::Method, or an address nothing names.
NAME = re.compile(r"\?[^\s,\]]+|\b(?:FUN|DAT|LAB)_[0-9a-f]+\b|\b[A-Za-z_]\w*::\w+|\b__real@[0-9a-f]+\b"
                  r"|(?<=call )[A-Za-z_]\w*|\b_\w+|\b0x[0-9a-f]+\b|\b[0-9A-F]{6,8}h\b")


def decode(data: bytes, base: int, names: Dict[int, str]) -> List[Tuple[int, str]]:
    """(offset, text) for each instruction, addresses replaced by names."""
    from iced_x86 import Decoder, FlowControl, Formatter, FormatterSyntax
    fmt = Formatter(FormatterSyntax.INTEL)
    rows = []
    for insn in Decoder(32, data, ip=base):
        text = fmt.format(insn)
        if insn.flow_control in (FlowControl.CONDITIONAL_BRANCH, FlowControl.UNCONDITIONAL_BRANCH)                 and base <= insn.near_branch_target < base + len(data):
            text = f"{text.split()[0]} +{insn.near_branch_target - base:03X}"
        elif insn.is_call_near:
            text = f"call {names.get(insn.near_branch_target, hex(insn.near_branch_target))}"
        else:
            text = ADDRESS.sub(lambda m: names.get(int(m.group()[:-1], 16), m.group()), text)
        rows.append((insn.ip - base, text))
    return rows


def link(p: Project, obj: coff.Coff, fn: coff.Symbol, length: int, base: int, dem: Dict[str, str],
         names: Dict[int, str]) -> bytes:
    """The candidate's code with each relocated field set as if linked at the target's addresses."""
    sec = obj.section(fn.section)
    data = bytearray(sec.data[fn.value:fn.value + length])
    placeholder = 0x7F000000
    for r in sec.relocations:
        at = r.offset - fn.value
        if not 0 <= at <= length - 4:
            continue
        sym = obj.slots[r.symbol]
        name = sym.name
        # MSVC's $L labels (switch tables, case entries) sit in the function itself.
        address = base + sym.value - fn.value if sym.defined and sym.section == fn.section \
            and name.startswith("$") else p.address_of(name)
        if name == "__except_list":
            address = 0  # fs:[__except_list] links to the exe's plain fs:[0x0], as verify.py accepts
        if address is None and name in dem:
            address = p.address_of(qualified_name(name, dem[name]))
        if address is None:
            address = placeholder = placeholder + 0x100
            names[address] = name
        addend = obj.addend(sec.index, r)
        if r.type == coff.IMAGE_REL_I386_DIR32:
            struct.pack_into("<I", data, at, (address + addend) & 0xFFFFFFFF)
        elif r.type == coff.IMAGE_REL_I386_REL32:
            struct.pack_into("<i", data, at, address + addend - (base + at + 4))
    return bytes(data)


def resolve(view, base: int, names: Dict[int, str]) -> bytes:
    """The target's code with its relocated fields resolved, when it comes from a split object (the exe
    has them already)."""
    data = bytearray(view.data)
    for at, (address, name, kind) in (view.relocs or {}).items():
        if not 0 <= at <= len(data) - 4:
            continue
        if address is None:
            address = 0x7E000000 + at
            names[address] = name
        if kind == coff.IMAGE_REL_I386_DIR32:
            struct.pack_into("<I", data, at, address)
        elif kind == coff.IMAGE_REL_I386_REL32:
            struct.pack_into("<i", data, at, address - (base + at + 4))
    return bytes(data)


def main() -> None:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("addr", type=lambda v: int(v, 0))
    ap.add_argument("file", type=Path)
    ap.add_argument("--symbol", help="the candidate's decorated name, when the file defines several functions")
    ap.add_argument("--all", action="store_true", help="print matching rows too (default: elide long runs)")
    args = ap.parse_args()

    p = Project()
    f = p.function(args.addr)
    if f is None:
        sys.exit(f"{args.addr:#x} is not a function in symbols.txt")
    out = Path(tempfile.mkdtemp(prefix="t3-sidebyside-")) / "candidate.obj"
    ok, log = p.compile(args.file, out, p.cflags_for(args.addr))
    if not ok:
        sys.exit(f"BUILD FAILED\n{log}")

    obj = coff.Coff.load(out)
    dem = demangle(p, [s.name for s in obj.symbols] + [f.name])
    try:
        fn = Verifier(p).pick(obj, f.name, dem, args.symbol)
    except ValueError as e:
        sys.exit(str(e))
    code_end, _ = p.code_extent(args.addr)
    target = TargetImage(p).view(args.addr, code_end - args.addr)
    if target is None:
        sys.exit("the target's bytes are not available: run python configure.py && ninja (needs orig/)")

    # The candidate's code runs to its first switch table or the next symbol, as verify.py cuts it.
    _, c_code, _ = Verifier(p)._prepare_candidate(obj, fn, f.name)
    names = {s.address: s.name for s in p.symbols}
    right = decode(link(p, obj, fn, c_code, args.addr, dem, names), args.addr, names)
    left = decode(resolve(target, args.addr, names), args.addr, names)

    print(f"{args.addr:#010x} {f.name}  |  {fn.name}")
    print(f"target {code_end - args.addr:#x} bytes of code, candidate {c_code:#x}")
    differ = renamed = 0
    matcher = difflib.SequenceMatcher(None, [t for _, t in left], [t for _, t in right], autojunk=False)
    for op, i1, i2, j1, j2 in matcher.get_opcodes():
        span = max(i2 - i1, j2 - j1)
        for k in range(span):
            a = left[i1 + k] if i1 + k < i2 else None
            b = right[j1 + k] if j1 + k < j2 else None
            if op == "equal" or (a and b and a[1] == b[1]):
                if not args.all and span > 6 and 2 < k < span - 2:
                    if k == 3:
                        print("   ...")
                    continue
                mark = " "
            elif a and b and NAME.sub("X", a[1]) == NAME.sub("X", b[1]):
                mark = "r"
                renamed += 1
            else:
                mark = "~"
                differ += 1
            lt = f"{a[0]:04x}  {a[1]}" if a else ""
            rt = f"{b[0]:04x}  {b[1]}" if b else ""
            print(f"{mark} {lt:<52} | {rt}")
    print(f"{differ} differing rows, {renamed} differing only in a reference's name (r)")

if __name__ == "__main__":
    main()
