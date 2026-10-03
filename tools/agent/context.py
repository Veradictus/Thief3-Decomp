#!/usr/bin/env python3
"""A compact context packet for one function, for the worker matching it.

    python tools/agent/context.py <addr> [--similar N] [--json]
    python tools/agent/context.py fill-ghidra [addr ...] [--next N]   # lead: cache Ghidra decompiles

Sections, each left out when its input is missing:
  function    symbols.txt name, demangled signature, size, split unit, status
  target      the target's instructions (objdiff on the split object)
  references  callees and globals with their symbols.txt names; unnamed ones
              are flagged, with any name another accepted function proposed,
              the registered class whose vtable a reference is, and the value
              of each float or double the code loads (`initially` for a variable)
  ghidra      the cached Ghidra decompile (build/agent/cache/ghidra/<ADDR>.c)
  headers     include/ headers declaring the classes involved
  similar     accepted functions most like this one, with their source
  bound       the names accepted callers already gave this function: its
              definition must use the same decorated name, or it is a name
              conflict for the lead
  family      other functions with the same code but for their references
              (clusters.py): accepted ones, and why a stamp failed
  history     earlier attempts and a deferral, if any, with the best earlier
              attempt's source: a starting point for a second pass
  cheatsheet  CHEATSHEET.md entries whose tags match the function's features
"""

import argparse
import difflib
import json
import math
import re
import struct
import subprocess
import sys
from typing import Dict, List, Sequence

import coff
import features as featurelib
from common import (ROOT, Claims, Ledger, Project, addr_key, atomic_write, class_of, demangle, emit, fmt_addr,
                    is_placeholder, qualified_name, read_json)
from verify import TargetImage, target_listing, target_symbol

CHEATSHEET = ROOT / ".claude" / "skills" / "t3-match" / "CHEATSHEET.md"


def switch_tables(image, address: int, code_end: int, region_end: int) -> List[dict]:
    """The tables after a function's code, in order: jump tables (addresses inside the function, shown from
    its start) and MSVC's byte index tables (case value - base -> jump table slot). An aligned word that points
    into the function starts a jump table; index bytes are small, never such an address."""
    view = image.view(code_end, region_end - code_end)
    if view is None:
        return []
    data, out, i = bytes(view.data), [], 0

    def jump_at(k: int):
        if (code_end + k) % 4 or k + 4 > len(data):
            return None
        target = struct.unpack_from("<I", data, k)[0]
        return target - address if address <= target < code_end else None

    while i < len(data):
        if jump_at(i) is not None:
            jumps = []
            while jump_at(i) is not None:
                jumps.append(f"{jump_at(i):#x}")
                i += 4
            out.append({"jump": jumps})
            continue
        index = []
        while i < len(data) and jump_at(i) is None:
            index.append(data[i])
            i += 1
        while index and index[-1] == 0xCC:  # padding up to the next function
            index.pop()
        if index:
            out.append({"index": index})
    return out


def string_at(image, address: int, limit: int = 120):
    """The NUL-terminated printable ASCII string at `address`, if that is what is there."""
    view = image.view(address, limit)
    if view is None:
        return None
    data = bytes(view.data)
    end = data.find(b"\0")
    if end < 2 or any(not (32 <= c < 127 or c in (9, 10, 13)) for c in data[:end]):
        return None
    return data[:end].decode("ascii")


def references(p: Project, address: int) -> List[dict]:
    """What the target function references, from its split object's relocations."""
    path = p.target_object(address)
    if path is None:
        return []
    f = p.function(address)
    obj = coff.Coff.load(path)
    fn = target_symbol(obj, f.name, address)
    if fn is None:
        return []
    code_end, region_end = p.code_extent(address)
    proposals: Dict[int, str] = {}
    for a, rec in p.accepted().items():
        if a == address:
            continue
        for b in rec.get("bindings", []):
            if b.get("status") == "provisional":
                proposals.setdefault(int(b["addr"], 16), f"{b['name']} (accepted {rec['addr']})")
    floats = fpu_operands(obj, fn, code_end - address)
    vtables: Dict[int, List[str]] = {}
    for c in p.classes().values():
        vtables.setdefault(c.vtable, []).append(c.name)
    image = None
    out, seen = [], set()
    for _, r in obj.relocations(fn.section, fn.value, fn.value + code_end - address):
        sym = obj.slots[r.symbol]
        base = p.address_of(sym.name)
        if sym.defined and sym.section == fn.section and fn.value <= sym.value < fn.value + region_end - address                 or sym.name in seen:
            continue  # its own labels and tables
        seen.add(sym.name)
        known = p.by_addr.get(base) if base is not None else None
        kind = "call" if r.type == coff.IMAGE_REL_I386_REL32 else "code" if known and known.is_function else "data"
        entry = {"name": sym.name, "addr": fmt_addr(base) if base is not None else None, "kind": kind,
                 "named": not is_placeholder(sym.name)}
        if known is not None and known.size:
            entry["size"] = known.size
        if base in proposals:
            entry["proposed"] = proposals[base]
        if len(vtables.get(base, [])) == 1:
            entry["vtable_of"] = vtables[base][0]
        width = floats.get(r.offset)
        if width and base is not None and not sym.name.startswith("__real@"):
            image = image or TargetImage(p)
            view = image.view(base, width)
            if view is not None:
                entry["value"] = fpu_literal(view.data)
                sec = image.pe.section_for_rva(base - image.pe.image_base) if image.pe else None
                if sec is not None and sec.writable:
                    entry["value"] = "initially " + entry["value"]  # a variable, not a constant
        elif kind == "data" and base is not None:
            image = image or TargetImage(p)
            text = string_at(image, base)
            if text is not None:
                entry["string"] = text  # what a literal the function pushes says
        out.append(entry)
    dem = demangle(p, [e["name"] for e in out])
    for e in out:
        if dem.get(e["name"]):
            e["demangled"] = dem[e["name"]]
    return out


def fpu_operands(obj: coff.Coff, fn: coff.Symbol, length: int) -> Dict[int, int]:
    """Relocation offsets inside the function's FPU memory operands (fld, fmul, fcomp, ...), with the
    operand's width: the constants the code loads as float (4) or double (8)."""
    try:
        from iced_x86 import Decoder, MemorySize
    except ImportError:
        return {}
    widths = {MemorySize.FLOAT32: 4, MemorySize.FLOAT64: 8}
    sec = obj.section(fn.section)
    relocs = [r.offset for _, r in obj.relocations(fn.section, fn.value, fn.value + length)]
    out = {}
    for insn in Decoder(32, sec.data[fn.value:fn.value + length], ip=fn.value):
        width = widths.get(insn.memory_size)
        if width:
            out.update({o: width for o in relocs if insn.ip <= o < insn.ip + insn.len})
    return out


def fpu_literal(data: bytes) -> str:
    """A float or double constant as the shortest source literal that has its bits, e.g. `0.1f`."""
    if len(data) == 8:
        value = struct.unpack("<d", data)[0]
        return f"{value!r} (double)" if math.isfinite(value) else f"0x{data[::-1].hex()} (double)"
    value = struct.unpack("<f", data)[0]
    if not math.isfinite(value):
        return f"0x{data[::-1].hex()} (float)"
    for digits in range(1, 10):
        text = f"{value:.{digits}g}"
        if struct.pack("<f", float(text)) == data:
            break
    if "e" not in text and "." not in text:
        text += ".0"
    return f"{text}f"


def headers(p: Project, classes: List[str], whole: Sequence[str] = (), max_lines: int = 40) -> List[dict]:
    """The declarations of `classes` in include/: an excerpt; the whole class for those in `whole` that a
    generated <Package>Classes.h declares (tools/assets/t3classes.py: every member with its offset)."""
    if not p.include_dir.is_dir():
        return []
    out = []
    for path in sorted(p.include_dir.rglob("*.h*")):
        text = path.read_text(encoding="utf-8", errors="replace")
        generated = path.name.endswith("Classes.h")
        for cls in classes:
            m = re.search(rf"^\s*(?:class|struct)\s+(?:\w+\s+)?{re.escape(cls)}\b[^;]*$", text, re.M)
            if m:
                lines = text[m.start():].splitlines()
                end = next((i for i, line in enumerate(lines) if line.startswith("};")), len(lines)) + 1
                lines = lines[:end] if generated and cls in whole else lines[:min(end, max_lines)]
                out.append({"class": cls, "path": str(path.relative_to(p.main)).replace("\\", "/"),
                            "excerpt": "\n".join(lines)})
    return out


def similar(p: Project, address: int, mnemonics: List[str], refs: List[dict], limit: int) -> List[dict]:
    """Accepted functions ranked by opcode-sequence similarity, else by shared class and references."""
    f = p.function(address)
    cls = f.name.rsplit("::", 1)[0] if "::" in f.name else ""
    names = {r["name"] for r in refs}
    scored = []
    for a, rec in p.accepted().items():
        if a == address:
            continue
        other = p.mnemonics(a)
        score = 0.0
        if mnemonics and other:
            m = difflib.SequenceMatcher(None, mnemonics, other, autojunk=False)
            if m.real_quick_ratio() > 0.3 and m.quick_ratio() > 0.3:
                score = m.ratio()
        if cls and rec.get("class") == cls:
            score += 0.2
        shared = names & {b.get("target") for b in rec.get("bindings", [])}
        score += 0.05 * len(shared)
        if score > 0:
            scored.append((score, a, rec))
    scored.sort(key=lambda t: -t[0])
    out = []
    for score, a, rec in scored[:limit]:
        src = p.state / "accepted" / f"{addr_key(a)}.cpp"
        out.append({"addr": rec["addr"], "symbol": rec.get("symbol"), "similarity": round(score, 2),
                    "source": src.read_text(encoding="utf-8", errors="replace") if src.is_file() else ""})
    return out


def cheatsheet(tags: List[str]) -> List[str]:
    """Entries (### headings) of CHEATSHEET.md whose `tags:` line names one of `tags`."""
    if not CHEATSHEET.is_file():
        return []
    out = []
    for block in re.split(r"(?m)^(?=### )", CHEATSHEET.read_text(encoding="utf-8")):
        m = re.search(r"(?m)^tags:\s*(.+)$", block)
        if block.startswith("### ") and m:
            entry_tags = {t.strip() for t in m.group(1).split(",")}
            if entry_tags & set(tags):
                out.append(block.strip())
    return out


def vtable_slots(p: Project, address: int) -> List[dict]:
    """The read-only tables of function pointers (vtables, in practice) that hold a function, with its slot.

    Runs of consecutive function addresses in the exe's read-only data are indexed once, cached in
    build/agent/cache/vtables.json. Without RTTI (/GR-) vtables sit back to back, so a run is cut
    wherever the code uses an address inside it as a constant (a constructor storing its vtable). A
    function found in a table is a virtual method of the class that owns it, which workers name after
    the table's address when nothing names it. Only tables whose start the code uses are reported."""
    cache_path = p.state / "cache" / "vtables.json"
    key = featurelib._key(p)
    cache = read_json(cache_path, {}) or {}
    if cache.get("key") != key:
        from iced_x86 import Decoder, OpKind

        index: Dict[str, List[List[int]]] = {}
        pe_image = TargetImage(p).pe
        starts = {f.address for f in p.functions}
        runs: List[List[int]] = []  # [first slot address, function, function, ...]
        used = set()  # addresses the code uses as 32-bit constants
        for sec in (pe_image.sections if pe_image else []):
            data = pe_image.read_rva(sec.va, min(sec.vsize, sec.raw_size)) if sec.raw_size else b""
            base = pe_image.image_base + sec.va
            if sec.executable:
                for insn in Decoder(32, data, ip=base):
                    for i in range(insn.op_count):
                        if insn.op_kind(i) == OpKind.IMMEDIATE32:
                            used.add(insn.immediate32)
                continue
            if sec.writable:
                continue
            run: List[int] = []
            for k in range(0, len(data) - 3, 4):
                value = int.from_bytes(data[k:k + 4], "little")
                if value in starts:
                    run.append(value)
                    continue
                if run:
                    runs.append([base + k - 4 * len(run)] + run)
                run = []
        for run in runs:
            table = None
            for slot, fn in enumerate(run[1:]):
                if run[0] + 4 * slot in used:
                    table = run[0] + 4 * slot
                if table is not None:
                    index.setdefault(f"{fn:08X}", []).append([table, (run[0] + 4 * slot - table) // 4])
        cache = {"key": key, "functions": index}
        atomic_write(cache_path, json.dumps(cache))
    # The registered class whose constructor stores a table (not one the linker folded for several).
    owners: Dict[int, List[str]] = {}
    for c in p.classes().values():
        owners.setdefault(c.vtable, []).append(c.name)
    out = []
    for t, s in cache["functions"].get(f"{address:08X}", [])[:4]:
        names = owners.get(t, [])
        entry = {"table": fmt_addr(t), "slot": s, **({"class": names[0]} if len(names) == 1 else {})}
        if len(names) == 1:
            entry.update(base_slot(p, names[0], s, cache["functions"]))
        out.append(entry)
    return out


def base_slot(p: Project, cls: str, slot: int, functions: Dict[str, list]) -> dict:
    """What the nearest registered super class whose vtable is indexed holds at `slot`: an override's
    base method (its name gives the override's name and signature), or nothing past the end of the
    super's table (a virtual the class adds)."""
    classes = p.classes()
    if not hasattr(p, "_slot_index"):
        index: Dict[int, Dict[int, int]] = {}
        for fn, places in functions.items():
            for t, k in places:
                index.setdefault(t, {})[k] = int(fn, 16)
        p._slot_index = index
    sup = classes.get(classes[cls].super) if cls in classes else None
    while sup is not None and sup.vtable not in p._slot_index:
        sup = classes.get(sup.super)
    if sup is None:
        return {}
    table = p._slot_index[sup.vtable]
    fn = table.get(slot)
    if fn is None:
        return {"base": {"class": sup.name, "new": slot > max(table)}} if slot > max(table) else {}
    rec = p.accepted().get(fn)
    sym = p.by_addr.get(fn)
    name = rec["symbol"] if rec else sym.name if sym else f"FUN_{fn:08x}"
    return {"base": {"class": sup.name, "addr": fmt_addr(fn), "name": name}}


def packet(p: Project, address: int, n_similar: int) -> dict:
    f = p.function(address)
    out: dict = {}
    dem = demangle(p, [f.name]).get(f.name, "")
    unit = p.unit_for(address)
    status = "accepted" if address in p.accepted() else "deferred" if address in p.deferred() else \
        "integrated" if address in p.integrated() else "open"
    claim = Claims(p).get(address)
    code_end, region_end = p.code_extent(address)
    out["function"] = {
        "addr": fmt_addr(address), "name": f.name, **({"demangled": dem} if dem else {}),
        "size": f.size, "code": code_end - address, "tables": region_end - code_end,
        "unit": unit.name if unit else None, "status": status,
        **({"claimed_by": claim["agent"]} if claim else {}),
    }
    if region_end > code_end:
        tables = switch_tables(TargetImage(p), address, code_end, region_end)
        if tables:
            out["function"]["switch_tables"] = tables
    workdir = p.state / "tmp" / f"context-{addr_key(address)}"
    try:
        listing = target_listing(p, address, workdir)
    except RuntimeError:
        listing = None
    mnemonics: List[str] = []
    if listing:
        insns, mnemonics = listing
        out["target"] = [f"{i.offset:04x}  {i.text}" for i in insns]
    refs = references(p, address)
    if refs:
        out["references"] = refs
    cache = p.state / "cache" / "ghidra" / f"{addr_key(address)}.c"
    if cache.is_file():
        out["ghidra"] = cache.read_text(encoding="utf-8", errors="replace")
    slots = vtable_slots(p, address)
    if slots:
        out["vtables"] = slots
    own = {c for c in {class_of(qualified_name(f.name, dem))} | {s.get("class", "") for s in slots} if c}
    classes = own | {c for c in (class_of(qualified_name(r["name"], r.get("demangled", ""))) for r in refs) if c}
    found = headers(p, sorted(classes), whole=sorted(own))
    if found:
        out["headers"] = found
    sims = similar(p, address, mnemonics, refs, n_similar)
    if sims:
        out["similar"] = sims
    bound = []
    for a, rec in sorted(p.accepted().items()):
        for b in rec.get("bindings", []):
            if b.get("kind") == "function" and int(b["addr"], 16) == address:
                bound.append({"by": rec["addr"], "name": b["name"], "status": b.get("status")})
                break
    if bound:
        names = sorted({b["name"] for b in bound})
        dem = demangle(p, names)
        out["bound"] = [dict(b, **({"demangled": dem[b["name"]]} if dem.get(b["name"]) else {})) for b in bound[:4]]
    try:
        import clusters as clusterlib
        idx = clusterlib.index(p)
    except Exception:
        idx = {}
    mine = idx.get(addr_key(address))
    if mine:
        members = clusterlib.families(p, idx).get(mine["key"], [])
        if len(members) > 1:
            accepted = p.accepted()
            stamp = clusterlib.stamps(p).get(addr_key(address))
            out["family"] = {"members": len(members),
                             "accepted": [fmt_addr(m) for m in members if m in accepted][:3],
                             **({"stamp_failed": stamp.get("why")} if stamp and not stamp.get("ok") else {})}
    history = {}
    ledger = Ledger(p, address)
    entries = [e for e in ledger.entries() if e.get("counted")]
    if entries:
        best = ledger.best()
        history["attempts"] = len(entries)
        history["best"] = {"score": best.get("score"), "mismatch_rows": best.get("mismatch_rows"),
                           "agent": best.get("agent"), "file": best.get("file")}
        source = ledger.source(best["sha"]) if best.get("sha") else None
        if source and (not claim or best.get("claim") != claim.get("id")):
            lines = source.decode("utf-8", "replace").splitlines()
            history["best_source"] = "\n".join(lines[:150]) + ("\n// ... (cut)" if len(lines) > 150 else "")
    deferred = p.deferred().get(address)
    if deferred:
        history["deferred"] = {"blocker": deferred.get("blocker"), "needs": deferred.get("needs")}
    if history:
        out["history"] = history
    feat = featurelib.features(p, [address]).get(address)
    tags = [k for k in ("eh", "fp", "switch") if feat and feat.get(k)]
    if listing and not feat:  # without iced-x86, read the tags off objdiff's listing
        text = " ".join(i.text for i in listing[0])
        tags = [t for t, cond in (("eh", "fs:" in text), ("fp", re.search(r"\bf[a-z]+ st", text)),
                                  ("switch", "*0x4+" in text)) if cond]
    tags += ["thiscall"] if "__thiscall" in dem else []
    entries = cheatsheet(tags)
    if entries:
        out["cheatsheet"] = entries
    return out


def print_packet(pk: dict) -> None:
    f = pk["function"]
    print(f"== {f['addr']} {f['name']}  ({f['size']:#x} bytes, {f['status']}, unit {f['unit']})")
    if f.get("demangled"):
        print(f"   {f['demangled']}")
    if f.get("tables"):
        print(f"   code {f['code']:#x} bytes, then {f['tables']:#x} bytes of switch tables")
        for table in f.get("switch_tables", []):
            if "jump" in table:
                print(f"   jump table (targets from the function's start): {' '.join(table['jump'])}")
            else:
                print(f"   byte index table (case - base -> jump slot): {' '.join(map(str, table['index']))}")
    if "target" in pk:
        print("\n== target")
        print("\n".join(pk["target"]))
    if "references" in pk:
        print("\n== references")
        for r in pk["references"]:
            note = "" if r["named"] else "  (unnamed)"
            if r.get("proposed"):
                note += f"  proposed: {r['proposed']}"
            if r.get("vtable_of"):
                note += f"  ({r['vtable_of']}'s vtable)"
            if r.get("value"):
                note += f"  {'' if r['value'].startswith('initially') else '= '}{r['value']}"
            if r.get("string") is not None:
                note += f"  = {json.dumps(r['string'])}"
            print(f"{r['kind']:<5} {r['addr'] or '?':<11} {r['name']}{note}")
            if r.get("demangled"):
                print(f"                  {r['demangled']}")
    if "ghidra" in pk:
        print("\n== ghidra (a starting point, not the answer)")
        print(pk["ghidra"].rstrip())
    if "vtables" in pk:
        print("\n== vtable slots (a virtual method: of the class named here, else of Class_<table>)")
        for v in pk["vtables"]:
            owner = f"{v['class']}'s vtable" if v.get("class") else "the table"
            print(f"slot {v['slot']} (+{4 * v['slot']:#x}) of {owner} at {v['table']}")
            base = v.get("base")
            if base and base.get("new"):
                print(f"   a virtual {v.get('class')} adds: {base['class']}'s vtable ends before this slot")
            elif base:
                print(f"   overrides {base['class']}'s slot {v['slot']}: {base['name']} at {base['addr']} "
                      "(a real name there gives this override's name and signature)")
    for h in pk.get("headers", []):
        print(f"\n== header {h['path']} ({h['class']})")
        print(h["excerpt"])
    for s in pk.get("similar", []):
        print(f"\n== similar {s['addr']} {s['symbol']} (similarity {s['similarity']})")
        print(s["source"].rstrip())
    if "bound" in pk:
        print("\n== bound (accepted callers already named this function: define it under this name, or defer "
              "\"name-conflict: ...\")")
        for b in pk["bound"]:
            print(f"{b['name']}  ({b['status']}, by {b['by']})"
                  + (f"\n    {b['demangled']}" if b.get("demangled") else ""))
    if "family" in pk:
        fam = pk["family"]
        print(f"\n== family: {fam['members']} functions with this code but for their references (clusters.py)"
              + (f"; accepted: {', '.join(fam['accepted'])} (see similar)" if fam["accepted"] else "")
              + (f"; the lead's stamp failed: {fam['stamp_failed']}" if fam.get("stamp_failed") else ""))
    if "history" in pk:
        print("\n== history")
        for k, v in pk["history"].items():
            if k != "best_source":
                print(f"{k}: {v}")
        if pk["history"].get("best_source"):
            print("\n== best earlier attempt (a starting point, not correct: change what its diff showed, do not "
                  "repeat it)")
            print(pk["history"]["best_source"].rstrip())
    if "cheatsheet" in pk:
        print("\n== cheatsheet")
        print("\n\n".join(pk["cheatsheet"]))


def fill_ghidra(p: Project, addresses: List[int]) -> None:
    out = p.state_dir("cache", "ghidra")
    todo = [a for a in addresses if not (out / f"{addr_key(a)}.c").is_file()]
    if not todo:
        print("all cached")
        return
    cmd = [sys.executable, str(p.main / "tools" / "ghidra_headless.py"), "--version", p.version, "script",
           str(p.main / "tools" / "ghidra" / "Decompile.java"), *[fmt_addr(a) for a in todo], f"out:{out}"]
    print("+", " ".join(cmd))
    sys.exit(subprocess.call(cmd, cwd=p.main))


def main() -> None:
    if len(sys.argv) > 1 and sys.argv[1] == "fill-ghidra":
        parser = argparse.ArgumentParser(prog="context.py fill-ghidra")
        parser.add_argument("addrs", nargs="*")
        parser.add_argument("--next", type=int, default=0, help="also the next N functions of the queue")
        parser.add_argument("--min-size", type=int, help="of the queue's functions this size or larger")
        parser.add_argument("--max-size", type=int, help="of the queue's functions this size or smaller")
        args = parser.parse_args(sys.argv[2:])
        p = Project()
        addresses = [p.parse_addr(a) for a in args.addrs]
        if args.next:
            import next as queue_mod
            ns = argparse.Namespace(unit=None, min_size=args.min_size, max_size=args.max_size, all_regions=False,
                                    include_deferred=False)
            addresses += [int(e["addr"], 16) for e in queue_mod.queue(p, ns)[:args.next]]
        fill_ghidra(p, addresses)
        return
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("addr")
    parser.add_argument("--similar", type=int, default=3, help="how many similar accepted functions to show")
    parser.add_argument("--json", action="store_true")
    args = parser.parse_args()
    p = Project()
    pk = packet(p, p.parse_addr(args.addr), args.similar)
    if args.json:
        emit(pk)
    else:
        print_packet(pk)


if __name__ == "__main__":
    main()
