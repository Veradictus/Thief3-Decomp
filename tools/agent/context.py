#!/usr/bin/env python3
"""A compact context packet for one function, for the worker matching it.

    python tools/agent/context.py <addr> [--similar N] [--json]
    python tools/agent/context.py fill-ghidra [addr ...] [--next N]   # lead: cache Ghidra decompiles

Sections, each left out when its input is missing:
  function    symbols.txt name, demangled signature, size, split unit, status
  target      the target's instructions (objdiff on the split object)
  references  callees and globals with their symbols.txt names; unnamed ones
              are flagged, with any name another accepted function proposed
  ghidra      the cached Ghidra decompile (build/agent/cache/ghidra/<ADDR>.c)
  headers     include/ headers declaring the classes involved
  similar     accepted functions most like this one, with their source
  history     earlier attempts and a deferral, if any
  cheatsheet  CHEATSHEET.md entries whose tags match the function's features
"""

import argparse
import difflib
import re
import subprocess
import sys
from typing import Dict, List

import coff
import features as featurelib
from common import (ROOT, Claims, Ledger, Project, addr_key, class_of, demangle, emit, fmt_addr, is_placeholder,
                    qualified_name)
from verify import target_listing, target_symbol

CHEATSHEET = ROOT / ".claude" / "skills" / "t3-match" / "CHEATSHEET.md"


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
    code_end, _ = p.code_extent(address)
    proposals: Dict[int, str] = {}
    for a, rec in p.accepted().items():
        if a == address:
            continue
        for b in rec.get("bindings", []):
            if b.get("status") == "provisional":
                proposals.setdefault(int(b["addr"], 16), f"{b['name']} (accepted {rec['addr']})")
    out, seen = [], set()
    for _, r in obj.relocations(fn.section, fn.value, fn.value + code_end - address):
        sym = obj.slots[r.symbol]
        base = p.address_of(sym.name)
        if sym.defined and sym.section == fn.section or sym.name in seen:
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
        out.append(entry)
    dem = demangle(p, [e["name"] for e in out])
    for e in out:
        if dem.get(e["name"]):
            e["demangled"] = dem[e["name"]]
    return out


def headers(p: Project, classes: List[str], max_lines: int = 40) -> List[dict]:
    if not p.include_dir.is_dir():
        return []
    out = []
    for path in sorted(p.include_dir.rglob("*.h*")):
        text = path.read_text(encoding="utf-8", errors="replace")
        for cls in classes:
            m = re.search(rf"^\s*(?:class|struct)\s+(?:\w+\s+)?{re.escape(cls)}\b[^;]*$", text, re.M)
            if m:
                lines = text[m.start():].splitlines()[:max_lines]
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
    classes = [c for c in {f.name.rsplit("::", 1)[0] if "::" in f.name else ""} | {
        class_of(qualified_name(r["name"], r.get("demangled", ""))) for r in refs} if c]
    found = headers(p, sorted(classes))
    if found:
        out["headers"] = found
    sims = similar(p, address, mnemonics, refs, n_similar)
    if sims:
        out["similar"] = sims
    history = {}
    entries = [e for e in Ledger(p, address).entries() if e.get("counted")]
    if entries:
        best = max(entries, key=lambda e: e.get("score", 0))
        history["attempts"] = len(entries)
        history["best"] = {"score": best.get("score"), "file": best.get("file")}
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
    if "target" in pk:
        print("\n== target")
        print("\n".join(pk["target"]))
    if "references" in pk:
        print("\n== references")
        for r in pk["references"]:
            note = "" if r["named"] else "  (unnamed)"
            if r.get("proposed"):
                note += f"  proposed: {r['proposed']}"
            print(f"{r['kind']:<5} {r['addr'] or '?':<11} {r['name']}{note}")
            if r.get("demangled"):
                print(f"                  {r['demangled']}")
    if "ghidra" in pk:
        print("\n== ghidra (a starting point, not the answer)")
        print(pk["ghidra"].rstrip())
    for h in pk.get("headers", []):
        print(f"\n== header {h['path']} ({h['class']})")
        print(h["excerpt"])
    for s in pk.get("similar", []):
        print(f"\n== similar {s['addr']} {s['symbol']} (similarity {s['similarity']})")
        print(s["source"].rstrip())
    if "history" in pk:
        print("\n== history")
        for k, v in pk["history"].items():
            print(f"{k}: {v}")
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
        args = parser.parse_args(sys.argv[2:])
        p = Project()
        addresses = [p.parse_addr(a) for a in args.addrs]
        if args.next:
            import next as queue_mod
            ns = argparse.Namespace(unit=None, max_size=None, all_regions=False, include_deferred=False)
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
