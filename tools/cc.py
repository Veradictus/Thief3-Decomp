#!/usr/bin/env python3
"""Compile one file with MSVC, then give the object's references to an address's other names that address's
own name.

    python tools/cc.py --aliases build/<version>/aliases.json -- <cl.exe command line>

symbols.txt can give an address more names than one (`type:alias`): the linker folded identical functions
into one copy, so the game's source called the same code by different names (the global `operator delete`
and `UObject`'s sized one, a trivial getter of two classes). The split objects know an address by its own
name only, so a compiled object that uses an alias gets the address's own name instead: objdiff's report and
the gate (tools/agent/verify.py) then pair the reference. configure.py writes the aliases file from
symbols.txt and builds every object through this script; cl.exe's output (/showIncludes) passes through.

It also folds the static labels MSVC gives a switch's cases and tables (`$L272`) into the function plus an
offset (coff.fold_labels): objdiff would take them for the end of the function, and the split objects name
the same places differently.
"""

import json
import os
import subprocess
import sys
from pathlib import Path
from typing import Dict

sys.path.insert(0, str(Path(__file__).resolve().parent / "agent"))

import coff  # noqa: E402


def normalize(path: Path, aliases: Dict[str, str]) -> int:
    """Point the object's references to aliases at the primary names; the number of symbols changed."""
    obj = coff.Coff.load(path)
    by_name = {}
    for s in obj.symbols:
        by_name.setdefault(s.name, s)
    rename: Dict[str, str] = {}
    retarget = {}
    for s in obj.symbols:
        primary = aliases.get(s.name)
        if primary is None or s.is_section:
            continue
        other = by_name.get(primary)
        if other is None or (s.defined and not other.defined):
            rename[s.name] = primary  # the object knows the address by the alias only
            continue
        for sec in obj.sections:  # both names present: the alias's references go to the primary
            for i, r in enumerate(sec.relocations):
                if r.symbol == s.index:
                    retarget[(sec.index, i)] = other.index
    if rename or retarget:
        path.write_bytes(obj.rewrite(rename=rename, retarget=retarget))
    return len(rename) + len({k for k in retarget})


def is_label(sym: coff.Symbol) -> bool:
    """MSVC's local code labels: a switch's case labels and tables."""
    return sym.storage == coff.IMAGE_SYM_CLASS_STATIC and sym.name.startswith("$L") and not sym.is_function


def fold(path: Path) -> bool:
    """Fold the object's labels into their functions; True when it changed."""
    data = coff.Coff.load(path).fold_labels(is_label)
    if data is not None:
        path.write_bytes(data)
    return data is not None


def main() -> None:
    argv = sys.argv[1:]
    if "--" not in argv:
        sys.exit(__doc__)
    split = argv.index("--")
    options, command = argv[:split], argv[split + 1:]
    aliases_path = Path(options[options.index("--aliases") + 1]) if "--aliases" in options else None
    proc = subprocess.run(command)
    if proc.returncode:
        sys.exit(proc.returncode)
    out = next((a[3:] for a in command if a.startswith("/Fo")), None)
    if aliases_path and aliases_path.is_file() and out and Path(out).is_file():
        aliases = json.loads(aliases_path.read_text(encoding="utf-8"))
        if aliases:
            normalize(Path(out), aliases)
    if out and Path(out).is_file() and not os.environ.get("T3_CC_NO_FOLD"):  # set by tests that need the labels
        fold(Path(out))


if __name__ == "__main__":
    main()
