#!/usr/bin/env python3
"""Lead only: move accepted functions into translation units under src/ and declare them in splits.txt.

    python tools/agent/integrate.py [addr ...] [--unit Game/Unsorted_10B06290_2.cpp] [--category game] [--dry-run]

Without addresses, every accepted function not yet integrated is taken. Each
goes to a unit:
  - --unit, if given;
  - else the declared splits.txt unit whose .text ranges already hold it;
  - else a unit named after its class: `Class::Method` -> <Category>/<Class>.cpp;
  - free functions, and members of classes known only by a placeholder name
    (Class_<address>, Struct_<address>, ...), go to
    <Category>/Unsorted_<start>.cpp, one per auto unit of the split (a chunk
    of up to 64 KB; <start> is its address), not one file per placeholder
    class. In a single file for all, MSVC would inline a small callee into
    callers the game compiled apart from it.
The category is --category, else the function's in config/<version>/categories.txt
(tools/classify.py). Only Ion Storm's game code is published (CONTRIBUTING.md):
Epic's engine is skipped, and so is a method of an Unreal-style class (UObject,
AActor, FName) that config/<version>/classes.txt does not list as Ion Storm's
(--category game integrates it once the class is known to be theirs); library
code is skipped unless --category libs, unclassified code unless --category game.

For each unit the tool assembles the file (the accepted files' declarations,
deduplicated, then the functions in address order behind their
`// FUNCTION: 0x<ADDR> <decorated name>` lines), compiles it with the unit's
flags and checks every function in it against the target with the accept.py
rulers. A new function that no longer matches in the unit's context is left
out (and reported); if a function already in the unit breaks, the unit is not
changed. Only then are the files written:
  - src/<unit>;
  - splits.txt: the unit's .text ranges (each function with its switch
    tables; neighbours merge when only padding lies between them) and its
    .text$x ranges (EH handlers and unwind funclets), checked with
    tools/splits.py;
  - symbols.txt: the functions' decorated names, the names their references
    were bound to (callees, globals, the vtables they store, __real@/??_C@
    literals, __ehhandler$ stubs), never overwriting a real name with a
    different one.
Serialised by build/agent/integrate.lock. Afterwards run configure.py and
ninja, and compare the report with the previous one.
"""

import argparse
import bisect
import json
import os
import re
import sys
import tempfile
import time
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path
from typing import Dict, List, Optional, Tuple

import lint as linter
from common import (FUNCTION_MARKER, Lock, Project, addr_key, atomic_write, fmt_addr, is_placeholder, splitslib,
                    symbolslib)
from verify import Verifier

CATEGORY_DIRS = {"game": "Game", "engine": "Engine", "libs": "Libs"}  # configure.py's unit categories
HEADER = "// {unit}: functions matched byte for byte, assembled by tools/agent/integrate.py.\n" \
         "// Declarations above the functions belong in include/ once they settle.\n"


# -- sources -------------------------------------------------------------------------
def split_file(text: str) -> Tuple[str, str]:
    """(declarations, function) of an accepted file: before and from its `// FUNCTION:` line."""
    m = FUNCTION_MARKER.search(text)
    return (text[:m.start()], text[m.start():]) if m else (text, "")


def parse_unit(text: str) -> Tuple[str, Dict[int, str]]:
    """(declarations, {address: block}) of a unit file integrate.py wrote."""
    marks = list(FUNCTION_MARKER.finditer(text))
    head = text[:marks[0].start()] if marks else text
    first = head.split("\n", 1)[0]
    unit = first[3:first.find(":")] if first.startswith("// ") and ":" in first else ""
    if unit and head.startswith(HEADER.format(unit=unit)):
        head = head[len(HEADER.format(unit=unit)):]
    blocks = {}
    for i, m in enumerate(marks):
        end = marks[i + 1].start() if i + 1 < len(marks) else len(text)
        blocks[int(m.group(1), 16)] = text[m.start():end].rstrip() + "\n"
    return head, blocks


def items(text: str) -> List[str]:
    """Top-level declarations: preprocessor lines, and code up to a `;` or closing `}` at depth 0.
    Comments before an item stay with it."""
    bare = linter.strip(text)
    out, start, depth, i = [], 0, 0, 0
    while i < len(bare):
        c = bare[i]
        line_start = i == 0 or bare[i - 1] == "\n"
        if line_start and bare[i:].lstrip(" \t").startswith("#") and depth == 0:
            j = i
            while True:  # a directive runs to the end of its line, continuations included
                j = bare.find("\n", j)
                if j < 0 or not bare[:j].rstrip().endswith("\\"):
                    break
                j += 1
            j = len(bare) if j < 0 else j + 1
            out.append(text[start:j])
            start = i = j
            continue
        if c == "{":
            depth += 1
        elif c == "}":
            depth -= 1
            if depth == 0:
                j = i + 1
                while j < len(bare) and bare[j] in " \t\r\n":
                    j += 1
                end = j + 1 if j < len(bare) and bare[j] == ";" else i + 1
                out.append(text[start:end])
                start = i = end
                continue
        elif c == ";" and depth == 0:
            out.append(text[start:i + 1])
            start = i + 1
        i += 1
    if text[start:].strip():
        out.append(text[start:])
    return [s.strip("\n") + "\n" for s in out if linter.strip(s).strip()]


COMMENT = re.compile(r"""("(?:\\.|[^"\\\n])*"|'(?:\\.|[^'\\\n])*')|//[^\n]*|/\*.*?\*/""", re.S)


def normal(item: str) -> str:
    """An item's identity: its code without comments or layout. String literals stay (linter.strip blanks
    them): two #include lines, or declarations differing only in a literal, are different items."""
    return " ".join(COMMENT.sub(lambda m: m.group(1) or " ", item).split())


def compose(unit: str, declarations: List[str], blocks: Dict[int, str]) -> str:
    seen, kept = set(), []
    for item in declarations:
        key = normal(item)
        if key not in seen:
            seen.add(key)
            kept.append(item)
    includes = [i for i in kept if normal(i).startswith("#")]
    rest = [i for i in kept if not normal(i).startswith("#")]
    parts = [HEADER.format(unit=unit), "".join(includes), "\n".join(rest)]
    parts += [blocks[a] for a in sorted(blocks)]
    return "\n".join(p.rstrip("\n") + "\n" for p in parts if p.strip())


# -- units and ranges ----------------------------------------------------------------------
_units: Dict[int, List[splitslib.Unit]] = {}
# A class named after an address because nothing names it yet (docs/agent-workflow.md).
PLACEHOLDER_CLASS = re.compile(r"[A-Za-z]+_[0-9A-Fa-f]{8}")


def auto_unit(p: Project, address: int) -> str:
    """The name of the split unit holding an address (auto/text_<start> for most)."""
    units = _units.setdefault(id(p), p.units())
    return next((u.name for u in units if any(a <= address < b for a, b in u.text)), "")


def unit_for(p: Project, rec: dict, args, declared: List[splitslib.Unit]) -> Tuple[str, str]:
    """(source path relative to src/, category) for an accepted record."""
    address = int(rec["addr"], 16)
    if rec.get("generated"):  # compiled where the function that makes the compiler emit it is
        return p.integrated()[int(rec["with"], 16)], args.category or guess_category(p, rec)
    if args.unit:
        source = args.unit[4:] if args.unit.startswith("src/") else args.unit
        return source, args.category or guess_category(p, rec)
    for start, end, source in getattr(p.configure, "UNIT_RANGES", []):
        if start <= address < end:
            return source, args.category or guess_category(p, rec)
    for u in declared:
        if any(a <= address < b for a, b in u.text):
            return u.source, args.category or guess_category(p, rec)
    category = args.category or guess_category(p, rec)
    cls = rec.get("class") or ""
    for u in declared:  # the class's unit may exist already
        if cls and Path(u.source).stem == cls:
            return u.source, category
    auto = auto_unit(p, address) if not cls or PLACEHOLDER_CLASS.fullmatch(cls) else ""
    if auto.startswith("auto/text_"):
        return f"{CATEGORY_DIRS[category]}/Unsorted_{auto[len('auto/text_'):]}.cpp", category
    return f"{CATEGORY_DIRS[category]}/{cls or 'Unsorted'}.cpp", category


def guess_category(p: Project, rec: dict) -> str:
    """Whose code a record is: its category in categories.txt, except that a method of an
    Unreal-style class counts as Epic's engine unless classes.txt has the class as Ion Storm's."""
    category = p.category(int(rec["addr"], 16))
    cls = rec.get("class") or ""
    known = p.classes().get(cls)
    if category == "game" and re.match(r"^[UAF][A-Z]", cls) and not (known and known.category == "game"):
        return "engine"
    return category


def skipped(p: Project, rec: dict, args) -> str:
    """Why a record is not integrated (CONTRIBUTING.md: only Ion Storm's game code is published), or ""."""
    category = args.category or guess_category(p, rec)
    if category == "libs" and args.category != "libs":
        return "is library code, which is not published; skipped (--category libs integrates it anyway)"
    if category == "engine" and not args.category:
        if p.category(int(rec["addr"], 16)) == "game":
            return (f"is a method of {rec.get('class')}, an Unreal-style class: Epic's engine is not published; "
                    f"skipped (--category game integrates it once the class is known to be Ion Storm's)")
        return "is Epic's engine code (categories.txt), which is not published; skipped"
    if category == "unknown":
        return (f"is unclassified (categories.txt: no evidence yet whose code it is, see tools/classify.py "
                f"explain {rec['addr']}); skipped (--category game integrates it once it is known to be Ion Storm's)")
    return ""


def merge(p: Project, ranges: List[Tuple[int, int]]) -> List[Tuple[int, int]]:
    """Sorted ranges, joined where no function starts in the gap between them."""
    starts = sorted(f.address for f in p.functions)
    out: List[List[int]] = []
    for a, b in sorted(ranges):
        if out:
            i = bisect.bisect_left(starts, out[-1][1])
            if a <= out[-1][1] or i >= len(starts) or starts[i] >= a:
                out[-1][1] = max(out[-1][1], b)
                continue
        out.append([a, b])
    return [(a, b) for a, b in out]


def check_splits(p: Project, text: str) -> List[str]:
    """Problems with a splits.txt text: parse errors, overlaps, ranges cutting through functions."""
    with tempfile.TemporaryDirectory() as tmp:
        path = Path(tmp) / "splits.txt"
        path.write_text(text, encoding="utf-8")
        try:
            units = splitslib.load(path)
            p.plan(units)
        except ValueError as e:
            return [str(e)]
    problems = []
    names = [u.source for u in units]
    problems += [f"unit {n} is declared twice" for n in sorted(set(names)) if names.count(n) > 1]
    functions = sorted(p.functions, key=lambda f: f.address)
    starts = [f.address for f in functions]
    for u in units:
        for a, b in u.text:
            for x in (a, b):
                i = bisect.bisect_left(starts, x) - 1
                if i >= 0 and functions[i].address < x < functions[i].end:
                    problems.append(f"{u.source}: range {a:#x}-{b:#x} cuts through {functions[i].name}")
    return problems


def set_unit(text: str, source: str, text_ranges: List[Tuple[int, int, str]]) -> str:
    """splits.txt with `source`'s .text lines replaced (other lines of its block kept), or the unit added
    before the first unit that starts after it."""
    lines = text.splitlines()
    new = [f"\t.text  start:0x{a:08X} end:0x{b:08X}" + (f"  # {note}" if note else "") for a, b, note in text_ranges]

    def header(line: str) -> Optional[str]:
        bare = line.split("#", 1)[0].rstrip()
        return bare[:-1].strip() if bare and not line[0].isspace() and bare.endswith(":") else None

    for i, line in enumerate(lines):
        if header(line) == source:
            j = i + 1
            kept = []
            while j < len(lines) and (not lines[j].strip() or lines[j][0].isspace() or lines[j].startswith("#")):
                if header(lines[j]) is not None:
                    break
                if not re.match(r"\s*\.text\s", lines[j]):
                    kept.append(lines[j])
                j += 1
            trailing = [k for k in kept if not k.strip()]
            kept = [k for k in kept if k.strip()]
            return "\n".join(lines[:i + 1] + new + kept + trailing + lines[j:]) + "\n"
    first = text_ranges[0][0]
    for i, line in enumerate(lines):
        if header(line) is None:
            continue
        m = re.search(r"start:0x([0-9A-Fa-f]+)", "\n".join(lines[i + 1:i + 8]))
        if m and int(m.group(1), 16) > first:
            return "\n".join(lines[:i] + [f"{source}:"] + new + [""] + lines[i:]) + "\n"
    body = "\n".join(lines).rstrip("\n")
    return body + ("\n\n" if body else "") + "\n".join([f"{source}:"] + new) + "\n"


# -- symbols -------------------------------------------------------------------------
def symbol_changes(p: Project, records: List[dict]) -> Tuple[Dict[int, Tuple[str, str]], List[str], List[str]]:
    """({address: (old, new)} renames, new symbols.txt lines, warnings) for integrated records."""
    renames: Dict[int, Tuple[str, str]] = {}
    added: Dict[int, str] = {}
    warnings: List[str] = []
    taken = {s.name: s.address for s in p.symbols}

    def want(address: int, name: str, kind: str, size: int = 0, compatible_with: str = "") -> None:
        if not name or name.startswith("$"):
            return
        if taken.get(name, address) != address:
            warnings.append(f"{name} is already at {fmt_addr(taken[name])} in symbols.txt; "
                            f"{fmt_addr(address)} keeps its name")
            return
        current = p.by_addr.get(address)
        current = current if current is not None and current.address == address else None
        if current is not None:
            if current.name == name:
                return
            if not is_placeholder(current.name) and current.name != compatible_with:
                warnings.append(f"{fmt_addr(address)} is named {current.name} in symbols.txt; not renamed to {name}")
                return
            renames[address] = (current.name, name)
        elif kind in ("data", "literal"):
            section = section_of(p, address, kind)
            added[address] = symbolslib.format_symbol(symbolslib.Symbol(name, section, address, "object", size))
        else:
            warnings.append(f"{fmt_addr(address)} ({name}) has no symbols.txt entry; not added")
            return
        taken[name] = address

    for rec in records:
        address = int(rec["addr"], 16)
        want(address, rec["symbol"], "function", compatible_with=rec.get("qualified", ""))
        for b in rec.get("bindings", []):
            a = int(b["addr"], 16)
            if b["status"] in ("provisional", "compatible") and b["kind"] in ("function", "data"):
                want(a, b["name"], b["kind"], compatible_with=b.get("target", ""))
            elif b["kind"] in ("literal", "ehhandler"):
                want(a, b["name"], "literal" if b["kind"] == "literal" else "function", b.get("size", 0))
            elif b["kind"] == "data" and b["name"].startswith("??_7"):
                # A vtable the function stores, compared by value: named, the report pairs the store.
                want(a, b["name"], "literal", b.get("size", 0))
    return renames, sorted(added.items()), warnings


def section_of(p: Project, address: int, kind: str) -> str:
    """The section of a new data symbol: from the exe, else .rdata for literals and .data for globals."""
    if not hasattr(p, "_pe"):
        import pe
        p._pe = pe.PE(p.exe.read_bytes()) if p.exe and p.exe.is_file() else None
    if p._pe:
        s = p._pe.section_for_rva(address - p._pe.image_base)
        if s:
            return s.name
    return ".rdata" if kind == "literal" else ".data"


def apply_symbols(text: str, renames: Dict[int, Tuple[str, str]], added: List[Tuple[int, str]]) -> str:
    by_old = {old: new for old, new in renames.values()}
    lines = text.splitlines()
    out = []
    pending = list(added)
    for line in lines:
        m = re.match(r"^(\S+) = [^:\s]+:0x([0-9A-Fa-f]+);", line)
        if m:
            address = int(m.group(2), 16)
            while pending and pending[0][0] < address:
                out.append(pending.pop(0)[1])
            if m.group(1) in by_old and renames.get(address, ("", ""))[0] == m.group(1):
                line = by_old[m.group(1)] + line[len(m.group(1)):]
        out.append(line)
    out += [line for _, line in pending]
    return "\n".join(out) + "\n"


# -- main ----------------------------------------------------------------------------
def build_unit(p: Project, verifier: Verifier, source: str, declarations: List[str], blocks: Dict[int, str],
               symbols: Dict[int, str], workdir: Path, cflags: List[str]) -> Tuple[str, Dict[int, str]]:
    """(file text, {address: failure}) for a composed unit; an empty failure dict means every function matches."""
    text = compose(source, declarations, blocks)
    path = workdir / source
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(text, encoding="utf-8")
    obj = path.with_suffix(".obj")
    ok, log = p.compile(path, obj, cflags)
    if not ok:
        return text, {a: "the unit does not compile: " + " / ".join(log.splitlines()[:3]) for a in blocks}
    failures = {}
    for address in sorted(blocks):
        res = verifier.run(address, None, workdir / addr_key(address), symbol=symbols[address], compiled=obj)
        if not res.match:
            reason = (res.problems or [f"{res.mismatch_rows} rows differ"])[0]
            failures[address] = reason
    return text, failures


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("addrs", nargs="*", help="accepted functions to integrate (default: all pending)")
    parser.add_argument("--unit", help="put them all in this unit (path relative to src/)")
    parser.add_argument("--category", choices=sorted(CATEGORY_DIRS), help="progress category of new units")
    parser.add_argument("--dry-run", action="store_true", help="check and report, write nothing")
    parser.add_argument("--no-names", action="store_true", help="leave symbols.txt alone")
    parser.add_argument("--json", action="store_true", help="print the summary as JSON")
    parser.add_argument("--jobs", type=int, default=0, help="units checked at once (default: one per CPU)")
    parser.add_argument("--plan", help="JSON {unit: [address, ...]}: put each function in its unit")
    args = parser.parse_args()

    p = Project()
    with Lock(p.state / "integrate.lock", stale=6 * 3600):
        summary = integrate(p, args)
    if args.json:
        print(json.dumps(summary, indent=1))
        return
    for u in summary["units"]:
        print(f"{u['unit']} ({u['category']}): +{len(u['added'])} -> {u['functions']} functions; "
              f"ranges {', '.join(u['ranges'])}")
    for d in summary["dropped"]:
        print(f"left out {d['addr']} from {d['unit']}: {d['reason']}")
    for line in summary["renamed"]:
        print(f"symbols.txt: {line}")
    for line in summary["added_symbols"]:
        print(f"symbols.txt: + {line}")
    for w in summary["warnings"]:
        print(f"warning: {w}")
    if not summary["units"]:
        print("nothing to integrate")
    elif args.dry_run:
        print("dry run: nothing written")
    else:
        print("written. Next: python configure.py && ninja, compare the report with the previous one "
              "(objdiff-cli report changes), then python tools/progress_report.py write and commit progress/")


def integrate(p: Project, args) -> dict:
    accepted = p.accepted()
    integrated = p.integrated()
    # --plan: {unit: [address, ...]} puts each listed function in its unit (tools/agent overflow bins)
    plan = {p.parse_addr(a): unit for unit, addrs in (json.loads(Path(args.plan).read_text(encoding="utf-8"))
                                                       if getattr(args, "plan", None) else {}).items() for a in addrs}
    wanted = [p.parse_addr(a) for a in args.addrs] or (sorted(plan) if plan else sorted(accepted))
    missing = [fmt_addr(a) for a in wanted if a not in accepted]
    if missing:
        sys.exit(f"not accepted: {', '.join(missing)}")
    declared = splitslib.load(p.splits_txt)
    groups: Dict[str, List[int]] = {}
    categories: Dict[str, str] = {}
    summary: dict = {"units": [], "dropped": [], "warnings": [], "renamed": [], "added_symbols": []}
    for a in wanted:
        if a in integrated:
            continue
        skip = skipped(p, accepted[a], args)
        if not skip and accepted[a].get("generated") and int(accepted[a]["with"], 16) not in integrated:
            skip = (f"is compiler-generated with {accepted[a]['with']}, which is not in src/ yet; skipped until "
                    f"it is")
        if skip:
            summary["warnings"].append(f"{fmt_addr(a)} {skip}")
            continue
        source, category = unit_for(p, accepted[a], args, declared)
        source = plan.get(a, source)
        groups.setdefault(source, []).append(a)
        categories.setdefault(source, category)

    verifier = Verifier(p)
    workdir = Path(tempfile.mkdtemp(prefix="integrate-", dir=p.state_dir("tmp")))
    splits_text = p.splits_txt.read_text(encoding="utf-8")
    text_x = p.text_x_range()
    records: List[dict] = []
    writes: Dict[Path, str] = {}

    def prepare(source: str, addrs: List[int]) -> dict:
        """Compose one unit with its new functions and check every function in it. Units are independent,
        so they are checked in parallel; what they change is merged afterwards, in order."""
        unit_path = p.src_dir / source
        head, blocks = parse_unit(unit_path.read_text(encoding="utf-8")) if unit_path.is_file() else ("", {})
        existing = set(blocks)
        symbols = {a: (FUNCTION_MARKER.search(b).group(2).strip() or None) for a, b in blocks.items()}
        new_decls: Dict[int, List[str]] = {}
        for a in sorted(addrs):
            symbols[a] = accepted[a]["symbol"]
            if accepted[a].get("generated"):
                # No source of its own: the unit emits it with its class's vtable, which needs the unit's
                # class declaration to match the accepted one (a virtual destructor for `??_G`).
                new_decls[a] = []
                blocks[a] = (f"// FUNCTION: {fmt_addr(a)} {symbols[a]}\n// Compiler-generated: emitted with the "
                             f"class's vtable by {accepted[a]['with']}'s definition in this unit.\n")
                continue
            decl, body = split_file((p.state / "accepted" / f"{addr_key(a)}.cpp").read_text(encoding="utf-8"))
            new_decls[a] = items(decl)
            blocks[a] = FUNCTION_MARKER.sub(f"// FUNCTION: {fmt_addr(a)} {accepted[a]['symbol']}",
                                            body, 1).rstrip() + "\n"
        cflags = p.configure.UNITS.get(source, {}).get("cflags", p.configure.CFLAGS)
        dropped, warnings, text = [], [], ""
        while True:
            declarations = items(head) + [d for a in sorted(new_decls) for d in new_decls[a]]
            text, failures = build_unit(p, verifier, source, declarations, blocks, symbols, workdir, cflags)
            broken = [a for a in failures if a in existing]
            if broken:
                warnings.append(f"{source}: left unchanged; {fmt_addr(broken[0])}, already in the unit, "
                                f"breaks: {failures[broken[0]]}")
                new_decls = {}
                break
            for a, why in failures.items():  # leave out what no longer matches here, then try again
                dropped.append({"addr": fmt_addr(a), "unit": source, "reason": why})
                del blocks[a], new_decls[a]
            if not failures or not new_decls:
                break
        return {"source": source, "path": unit_path, "text": text, "blocks": blocks, "added": sorted(new_decls),
                "dropped": dropped, "warnings": warnings}

    with ThreadPoolExecutor(max_workers=getattr(args, "jobs", 0) or os.cpu_count() or 1) as pool:
        results = list(pool.map(lambda item: prepare(*item), sorted(groups.items())))
    for r in results:
        summary["dropped"] += r["dropped"]
        summary["warnings"] += r["warnings"]
        source, blocks, added, unit_path = r["source"], r["blocks"], r["added"], r["path"]
        if not added:
            continue
        writes[unit_path] = r["text"]
        old = next((u for u in declared if u.source == source), None)
        eh = [(int(x, 16), int(y, 16)) for a in added for x, y in accepted[a].get("text_x", [])]
        ranges = merge(p, (old.text if old else []) + [(a, p.code_extent(a)[1]) for a in blocks] + eh)
        note = ".text$x: EH handlers and unwind funclets"
        lines = [(a, b, note if text_x[0] <= a < text_x[1] else "") for a, b in ranges]
        splits_text = set_unit(splits_text, source, lines)
        summary["units"].append({"unit": source, "category": categories[source], "added": [fmt_addr(a) for a in added],
                                 "functions": len(blocks), "ranges": [f"{a:#x}-{b:#x}" for a, b in ranges]})
        records += [dict(accepted[a], integrated=source, integrated_at=time.time()) for a in added]

    problems = check_splits(p, splits_text)
    if problems:
        sys.exit("splits.txt would be invalid:\n  " + "\n  ".join(problems))
    renames, new_symbols, warnings = ({}, [], []) if args.no_names else symbol_changes(p, records)
    summary["warnings"] += warnings
    summary["renamed"] = [f"{fmt_addr(a)} {old} -> {new}" for a, (old, new) in sorted(renames.items())]
    summary["added_symbols"] = [line for _, line in new_symbols]
    summary["written"] = not args.dry_run and bool(records)
    if not summary["written"]:
        return summary

    for path, text in writes.items():
        atomic_write(path, text)
    atomic_write(p.splits_txt, splits_text)
    if renames or new_symbols:
        symbols_text = apply_symbols(p.symbols_txt.read_text(encoding="utf-8"), renames, new_symbols)
        check = workdir / "symbols.txt"
        check.write_text(symbols_text, encoding="utf-8")
        symbolslib.load(check)  # raises on a duplicate name
        atomic_write(p.symbols_txt, symbols_text)
    for rec in records:
        atomic_write(p.state / "accepted" / f"{addr_key(int(rec['addr'], 16))}.json", json.dumps(rec, indent=1))
    return summary


if __name__ == "__main__":
    main()
