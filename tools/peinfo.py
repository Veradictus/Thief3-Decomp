#!/usr/bin/env python3
"""Print a PE32 summary: headers, sections, Rich header, PDB path, imports."""

import argparse
import datetime
import hashlib
import math
from collections import Counter
from pathlib import Path

from pe import PE, RICH_PRODUCTS


def entropy(data: bytes) -> float:
    if not data:
        return 0.0
    n = len(data)
    return max(0.0, -sum(c / n * math.log2(c / n) for c in Counter(data).values()))


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("exe", type=Path)
    parser.add_argument("--imports", action="store_true", help="list every imported function")
    args = parser.parse_args()

    data = args.exe.read_bytes()
    pe = PE(data)
    ts = datetime.datetime.fromtimestamp(pe.timestamp, datetime.timezone.utc)
    print(f"{args.exe.name}: {len(data)} bytes, sha1 {hashlib.sha1(data).hexdigest()}")
    print(f"  timestamp  {pe.timestamp:#010x} ({ts:%Y-%m-%d %H:%M:%S} UTC)")
    print(f"  linker     {pe.linker_version[0]}.{pe.linker_version[1]:02d}")
    print(f"  image base {pe.image_base:#010x}, size {pe.image_size:#x}, entry {pe.image_base + pe.entry_rva:#010x}")
    print(f"  flags      {pe.characteristics:#06x}{' (relocations stripped)' if pe.characteristics & 1 else ''}")

    print("  sections:")
    for s in pe.sections:
        raw = data[s.raw_ptr:s.raw_ptr + s.raw_size]
        print(
            f"    {s.name:8s} va {pe.image_base + s.va:#010x} vsize {s.vsize:#09x} "
            f"raw {s.raw_size:#09x} flags {s.characteristics:#010x} entropy {entropy(raw):.2f}"
        )

    print("  directories:")
    for name in ("import", "resource", "basereloc", "debug", "tls", "load_config", "iat", "delay_import"):
        rva, size = pe.directory(name)
        if rva or size:
            print(f"    {name:12s} {pe.image_base + rva:#010x} size {size:#x}")

    cv = pe.codeview()
    if cv:
        print(f"  pdb        {cv[1]} (age {cv[2]}, guid {cv[0]})")

    key, rich = pe.rich_header()
    if rich:
        print(f"  rich header (key {key:#010x}):")
        for e in rich:
            name = RICH_PRODUCTS.get(e.prodid, "?")
            print(f"    id {e.prodid:#06x} build {e.build:5d} x{e.count:<5d} {name}")

    total = 0
    print("  imports:")
    for dll, names in pe.imports():
        total += len(names)
        shown = ", ".join(names if args.imports else names[:4])
        more = "" if args.imports or len(names) <= 4 else ", ..."
        print(f"    {dll:14s} {len(names):4d}  {shown}{more}")
    print(f"    total {total}")


if __name__ == "__main__":
    main()
