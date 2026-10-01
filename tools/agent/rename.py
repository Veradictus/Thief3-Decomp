#!/usr/bin/env python3
"""Lead only: give placeholder classes their real names, everywhere at once.

    python tools/agent/rename.py <old> <new> [<old> <new> ...] [--dry-run]
    python tools/agent/rename.py --registered [--dry-run]

A class keeps its placeholder name (Class_<vtable or function address>,
docs/agent-workflow.md) until something names it. --registered names every
Class_<vtable> whose vtable the constructor of exactly one registered class
stores (config/<version>/classes.txt, tools/classify.py); a vtable the linker
folded for several classes names none of them.

The new name goes everywhere the old one is:
  - symbols.txt, decorated names included (`?F@Class_X@@`, `PAVClass_X@@`,
    `??0Class_X@@`, `??_7Class_X@@6B@`);
  - src/ and include/;
  - the agent records (build/agent/accepted, deferred and rejected: sources
    and records), the JSON files beside them and the lead's backlog;
  - the scratch files (build/scratch), so a deferred candidate can still be
    accepted.
A lowercase letter before the old name makes it part of a longer one
(InnerClass_<address>), which is left alone. A decorated name that already
holds the new name would need a back-reference after the rename (MSVC writes
a repeated name as a digit), and a header in include/ that declares the new
name would clash with the units' own declarations: such renames are refused.
Afterwards: python configure.py && ninja (the split must carry the new names),
then python tools/progress_report.py check (only names may change).
"""

import argparse
import collections
import hashlib
import os
import re
import sys
from pathlib import Path
from typing import Dict, List, Tuple

from common import Project, symbolslib

TEXT_SUFFIXES = {".cpp", ".h", ".hpp", ".c", ".json", ".md", ".txt"}


def registered(p: Project) -> Dict[str, str]:
    """Class_<vtable> -> C++ name for every vtable exactly one registered class stores."""
    classes = p.classes()
    if not classes:
        sys.exit("no config/<version>/classes.txt: run python tools/classify.py write")
    count = collections.Counter(c.vtable for c in classes.values() if c.vtable)
    return {f"Class_{c.vtable:08X}": c.name for c in classes.values() if c.vtable and count[c.vtable] == 1}


def pattern(names: List[str]) -> re.Pattern:
    """The old names, hex digits in either case, not inside a longer identifier."""
    alternatives = []
    for name in sorted(names, key=len, reverse=True):
        m = re.fullmatch(r"([A-Za-z]+_)([0-9A-Fa-f]{8})", name)
        alternatives.append(re.escape(m.group(1)) + f"(?i:{m.group(2)})" if m else re.escape(name))
    return re.compile(r"(?<![a-z])(" + "|".join(alternatives) + r")(?![0-9A-Za-z_])")


def files(p: Project) -> List[Tuple[str, Path]]:
    """(area, path) of every text file the rename covers, symbols.txt first."""
    out = [("symbols.txt", p.symbols_txt)]
    for area, root in (("src", p.root / "src"), ("include", p.root / "include")):
        out += [(area, f) for f in sorted(root.rglob("*")) if f.suffix in TEXT_SUFFIXES and f.is_file()]
    for kind in ("accepted", "deferred", "rejected"):
        folder = p.state / kind
        out += [(kind, f) for f in sorted(folder.glob("*")) if f.suffix in (".cpp", ".json") and f.is_file()]
    out += [("records", f) for f in sorted(p.state.glob("*")) if f.suffix in (".json", ".md") and f.is_file()]
    scratch = p.root / "build" / "scratch"
    out += [("scratch", f) for f in sorted(scratch.rglob("*")) if f.suffix in TEXT_SUFFIXES and f.is_file()]
    return out


def refusals(p: Project, mapping: Dict[str, str]) -> Dict[str, str]:
    """old -> why it cannot be renamed."""
    out = {}
    headers = "\n".join(f.read_text(encoding="utf-8", errors="replace") for f in (p.root / "include").rglob("*.h"))
    for old, new in mapping.items():
        if not re.fullmatch(r"[A-Za-z_]\w*", new):
            out[old] = f"{new} is not a C++ identifier"
        elif re.search(rf"\b(?:class|struct)\s+{new}\b", headers):
            out[old] = f"include/ declares {new}: rename by hand, the units declare the class themselves"
    decorated = [s.name for s in p.symbols if s.name.startswith("?")]
    for old, new in mapping.items():
        rx = pattern([old])
        clash = next((n for n in decorated if f"{new}@" in n and rx.search(n)), None) if old not in out else None
        if clash:
            out[old] = f"{clash} holds both names: its decorated form needs a back-reference"
    return out


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("names", nargs="*", help="pairs: old new")
    parser.add_argument("--registered", action="store_true", help="every Class_<vtable> a registered class owns")
    parser.add_argument("--dry-run", action="store_true", help="report, write nothing")
    args = parser.parse_args()
    if len(args.names) % 2:
        sys.exit("names come in pairs: old new")
    p = Project()
    mapping = dict(zip(args.names[::2], args.names[1::2]))
    if args.registered:
        mapping.update(registered(p))
    if not mapping:
        sys.exit("nothing to rename")
    refused = {old.lower(): why for old, why in refusals(p, mapping).items()}
    rx = pattern(list(mapping))
    by_lower = {old.lower(): new for old, new in mapping.items()}

    def rename(text: str) -> Tuple[str, collections.Counter]:
        hits = collections.Counter()

        def sub(m: re.Match) -> str:
            hits[m.group(1).lower()] += 1
            return m.group(0) if m.group(1).lower() in refused else by_lower[m.group(1).lower()]
        return rx.sub(sub, text), hits

    totals: Dict[str, collections.Counter] = collections.defaultdict(collections.Counter)
    writes: Dict[Path, str] = {}
    for area, path in files(p):
        text = path.read_bytes().decode("utf-8", errors="surrogateescape")  # line endings as they are
        new, hits = rename(text)
        for old, n in hits.items():
            totals[old][area] += n
        if new != text:
            writes[path] = new
    for old in sorted(mapping):
        if old.lower() in refused and old.lower() in totals:
            print(f"refused {old} -> {mapping[old]}: {refused[old.lower()]}")
    mapping = {old: new for old, new in mapping.items() if old.lower() not in refused}
    # A record keeps the hash of its source.
    for path in list(writes):
        if path.suffix == ".cpp" and path.parent.name in ("accepted", "deferred", "rejected"):
            record = path.with_suffix(".json")
            text = writes.get(record) or (record.read_bytes().decode("utf-8") if record.is_file() else "")
            sha = hashlib.sha256(writes[path].encode("utf-8", errors="surrogateescape")).hexdigest()[:16]
            if '"source_sha"' in text:
                writes[record] = re.sub(r'("source_sha":\s*")[0-9a-f]+(")', rf"\g<1>{sha}\g<2>", text)
    if p.symbols_txt in writes:
        check = p.state_dir("tmp") / "rename-symbols.txt"
        check.write_text(writes[p.symbols_txt], encoding="utf-8")
        try:
            symbolslib.load(check)  # raises on a duplicate name
        except ValueError as e:
            sys.exit(f"symbols.txt would be invalid: {e}")
        finally:
            check.unlink()
    for old in sorted(mapping, key=lambda o: mapping[o]):
        hits = totals.get(old.lower())
        if hits:
            print(f"{old} -> {mapping[old]}: " + ", ".join(f"{area} {n}" for area, n in sorted(hits.items())))
    print(f"{len(writes)} files" + (" (dry run: nothing written)" if args.dry_run else " written"))
    if args.dry_run:
        return
    for path, text in writes.items():
        tmp = path.with_name(f".{path.name}.rename.tmp")
        tmp.write_bytes(text.encode("utf-8", errors="surrogateescape"))
        os.replace(tmp, path)
    print("Next: python configure.py && ninja, python tools/progress_report.py check, "
          "python tools/ghidra_headless.py names")


if __name__ == "__main__":
    main()
