#!/usr/bin/env python3
"""The work queue: which function to match next, with claims so parallel workers never collide.

    python tools/agent/next.py claim [--agent ID] [--count N] [--unit U] [--name REGEX] [--min-size N] [--max-size N]
                                     [--only-deferred] [--by-class] [--context]
    python tools/agent/next.py release [--agent ID] [addr ...]
    python tools/agent/next.py status
    python tools/agent/next.py list [--limit N] [--unit U]        # the queue head, unclaimed
    python tools/agent/next.py requeue (addr ... | --all)         # lead: forget deferrals

The queue holds Ion Storm's game code: every function in symbols.txt that
config/<version>/categories.txt (tools/classify.py) calls game, except EH
unwind funclets (`Unwind@`, `.text$x`), import thunks, functions the lead
excluded in
build/agent/excluded.json (address -> reason: library code elsewhere, an
inline-asm original), and functions already accepted, integrated into src/,
deferred or claimed. --all-regions adds unclassified and library code; Epic's
engine is never queued. It is ordered easy first: by a
difficulty score from the target's instructions (instructions, branches,
calls, switches, EH, x87; needs iced-x86 and the exe or split objects), else
by size.

Families (clusters.py: the same code around other callees, globals or
classes) are served one member at a time, the first one early (its
difficulty divided by the family's size): the others wait while it is open,
claimed, or accepted and not yet stamped (`clusters.py stamp`, the lead's),
and go to workers only if the stamp fails. --include-siblings serves them
all.

--only-deferred queues deferred functions only, for a second pass by a
stronger model. `claim --context` prints each claimed function's context
packet (context.py) after the JSON, which is then one line.

--by-class takes the queue head, then the queued functions of its class (by
the class in its name, else the vtable that holds it) before any other, and
for a function of no known class its nearest neighbours in the same unit:
one worker declares the class once for several of its methods, and methods
of one class come out with one declaration.

A claim is a file in build/agent/claims/ created atomically; it expires after
--ttl seconds (try.py renews it on every attempt) and can then be taken over.
Output is JSON.
"""

import argparse
import bisect
import json
import re
import subprocess
import sys
from pathlib import Path
from typing import Dict, List, Optional

import clusters as clusterlib
import features as featurelib
from common import CLAIM_TTL, Claims, Project, addr_key, agent_id, emit, fmt_addr, read_json


def unit_index(p: Project):
    """address -> split unit name, by bisecting the units' .text ranges."""
    ranges = sorted((a, b, u.name) for u in p.units() for a, b in u.text)
    starts = [r[0] for r in ranges]

    def unit_of(address: int) -> str:
        i = bisect.bisect_right(starts, address) - 1
        return ranges[i][2] if i >= 0 and address < ranges[i][1] else ""
    return unit_of


def queue(p: Project, args, claimed: Optional[set] = None) -> List[dict]:
    text_x = p.text_x_range()
    imports = {s.name[len("__imp_"):] for s in p.symbols if s.name.startswith("__imp_")}
    done = set(p.accepted()) | set(p.integrated())
    only_deferred = getattr(args, "only_deferred", False)
    deferred = set() if getattr(args, "include_deferred", False) or only_deferred else set(p.deferred())
    wanted = set(p.deferred()) if only_deferred else None
    claimed = claimed if claimed is not None else {int(c["addr"], 16) for c in Claims(p).all()}
    excluded_file = p.state / "excluded.json"
    excluded = ({int(a, 16) for a in json.loads(excluded_file.read_text(encoding="utf-8"))}
                if excluded_file.is_file() else set())
    unit_of = unit_index(p)
    min_size, max_size = getattr(args, "min_size", None), getattr(args, "max_size", None)
    name, all_regions = getattr(args, "name", None), getattr(args, "all_regions", False)
    out = []
    for f in p.functions:
        a = f.address
        if (f.name.startswith("Unwind@") or text_x[0] <= a < text_x[1] or f.name in imports
                or p.category(a) == "engine" or (p.category(a) != "game" and not all_regions)
                or a in done or a in deferred or a in claimed or a in excluded
                or (min_size and f.size < min_size) or (max_size and f.size > max_size)
                or (name and not re.search(name, f.name)) or (wanted is not None and a not in wanted)):
            continue
        unit = unit_of(a)
        if getattr(args, "unit", None) and not (unit == args.unit or unit.startswith(args.unit)):
            continue
        out.append({"addr": fmt_addr(a), "symbol": f.name, "unit": unit, "size": f.size})
    feats = featurelib.features(p, [int(e["addr"], 16) for e in out])
    for e in out:
        feat = feats.get(int(e["addr"], 16))
        e["difficulty"] = feat["score"] if feat else e["size"]
        if feat:
            e["features"] = {k: feat[k] for k in ("insns", "branches", "calls", "switch", "eh", "fp")}
            e["callees"] = [_callee(p, c) for c in feat["callees"]]
    family = clusterlib.open_sizes(p, [int(e["addr"], 16) for e in out])
    for e in out:
        k = family.get(int(e["addr"], 16))
        if k:
            e["family"] = k
    out.sort(key=lambda e: (e["difficulty"] / e.get("family", 1), e["addr"]))
    if not getattr(args, "include_siblings", False) and not only_deferred:
        waiting = clusterlib.held(p, [int(e["addr"], 16) for e in out])
        if waiting:
            out = [e for e in out if int(e["addr"], 16) not in waiting]
        args.held_siblings = len(waiting)
    return out


def _callee(p: Project, address: int) -> dict:
    sym = p.by_addr.get(address)
    name = sym.name if sym else f"FUN_{address:08x}"
    return {"addr": fmt_addr(address), "name": name, "named": not name.startswith(("FUN_", "LAB_", "thunk_FUN_"))}


def owner(entry: dict, slots: Dict[str, list]) -> str:
    """The class a queued function belongs to, as far as the records tell: from its name (`C::F`, or a
    decorated method `?F@C@@...`), else the vtable holding it; "" when neither does."""
    sym = entry["symbol"]
    if "::" in sym:
        return "class:" + sym.rsplit("::", 1)[0]
    m = re.match(r"\?[^?@][^@]*@([^@]+)@@[ABCEFIJKMNQRSUV]", sym)  # a member, not `@@Y` (namespace)
    if m:
        return "class:" + m.group(1)
    hit = slots.get(entry["addr"][2:].upper())
    return f"vtable:{hit[0][0]:08X}" if hit else ""


def by_class(entries: List[dict], first: dict, slots: Dict[str, list]) -> List[dict]:
    """`entries` (queue order) with `first`'s class first, else its nearest neighbours in its unit."""
    mine = owner(first, slots)
    start = int(first["addr"], 16)
    if mine:
        return sorted(entries, key=lambda e: owner(e, slots) != mine)
    return sorted(entries, key=lambda e: (e["unit"] != first["unit"],
                                          abs(int(e["addr"], 16) - start) if e["unit"] == first["unit"] else 0))


def siblings(p: Project, entry: dict, accepted: Dict[int, dict], limit: int = 5) -> List[dict]:
    """Accepted functions of the same class (by symbols.txt name) or the same split unit."""
    cls = entry["symbol"].rsplit("::", 1)[0] if "::" in entry["symbol"] else ""
    unit_of = unit_index(p)
    out = []
    for a, rec in sorted(accepted.items()):
        if (cls and rec.get("class") == cls) or unit_of(a) == entry["unit"]:
            out.append({"addr": rec["addr"], "symbol": rec.get("symbol")})
        if len(out) >= limit:
            break
    return out


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = parser.add_subparsers(dest="cmd", required=True)
    for name in ("claim", "list"):
        s = sub.add_parser(name)
        s.add_argument("--unit", help="only functions of this split unit (name or prefix, e.g. auto/text_10A5)")
        s.add_argument("--name", help="only functions whose symbols.txt name matches this regex (e.g. ^UObject::exec)")
        s.add_argument("--min-size", type=lambda v: int(v, 0), help="skip functions smaller than this")
        s.add_argument("--max-size", type=lambda v: int(v, 0), help="skip functions larger than this")
        s.add_argument("--all-regions", action="store_true",
                       help="include unclassified and library code (categories.txt); never Epic's engine")
        s.add_argument("--include-deferred", action="store_true")
        s.add_argument("--only-deferred", action="store_true", help="only deferred functions (a second pass)")
        s.add_argument("--include-siblings", action="store_true",
                       help="also family members waiting for another member or for the lead's stamp")
        if name == "claim":
            s.add_argument("--agent", help="worker id (default: $T3_AGENT_ID)")
            s.add_argument("--count", type=int, default=1)
            s.add_argument("--ttl", type=float, default=CLAIM_TTL, help="claim lifetime in seconds")
            s.add_argument("--context", action="store_true", help="print each claimed function's context packet")
            s.add_argument("--by-class", action="store_true",
                           help="after the queue head, its class's functions first (else its neighbours)")
        else:
            s.add_argument("--limit", type=int, default=20)
    rel = sub.add_parser("release")
    rel.add_argument("--agent", help="worker id (default: $T3_AGENT_ID)")
    rel.add_argument("--all", action="store_true", help="lead: release every claim, whoever holds it")
    rel.add_argument("addrs", nargs="*")
    sub.add_parser("status")
    req = sub.add_parser("requeue")
    req.add_argument("--all", action="store_true")
    req.add_argument("addrs", nargs="*")
    args = parser.parse_args()

    p = Project()
    claims = Claims(p)
    if args.cmd == "list":
        emit(queue(p, args)[:args.limit])
    elif args.cmd == "claim":
        missing = [str(x) for x in (p.obj_dir, p.cl, p.objdiff, p.wibo) if x is not None and not x.exists()]
        if missing:  # every attempt would end in CANNOT CHECK: hand out nothing
            emit({"error": "the split or the toolchain is missing: python configure.py && ninja",
                  "missing": missing, "empty": True})
            sys.exit(5)
        agent = agent_id(args.agent)
        accepted = p.accepted()
        taken = []
        # A second pass never hands a worker back its own deferral.
        own = {a for a, rec in p.deferred().items() if rec.get("agent") == agent} if args.only_deferred else set()
        pending = queue(p, args)
        slots = ((read_json(p.state / "cache" / "vtables.json", {}) or {}).get("functions", {})
                 if args.by_class else {})
        while pending:
            entry = pending.pop(0)
            if len(taken) >= args.count:
                break
            if int(entry["addr"], 16) in own:
                continue
            address = int(entry["addr"], 16)
            if claims.take(address, agent, args.ttl, {"symbol": entry["symbol"]}):
                # Another worker may have accepted or deferred it, and released its claim, since
                # the queue was read.
                done_kinds = ("accepted",) if args.only_deferred else ("accepted", "deferred")
                if any((p.state / kind / f"{addr_key(address)}.json").is_file() for kind in done_kinds):
                    claims.release(address, agent)
                    continue
                if not args.context:  # the packet has the references and similar functions
                    entry["siblings"] = siblings(p, entry, accepted)
                taken.append(entry)
                if args.by_class and len(taken) == 1:
                    pending = by_class(pending, entry, slots)
        if not args.context:
            emit({"agent": agent, "claimed": taken, "empty": not taken})
            sys.exit(0 if taken else 4)
        short = [{k: e[k] for k in ("addr", "symbol", "size", "difficulty")} for e in taken]
        print(json.dumps({"agent": agent, "claimed": short, "empty": not taken}), flush=True)
        for entry in taken:
            subprocess.run([sys.executable, str(Path(__file__).with_name("context.py")), entry["addr"]])
        sys.exit(0 if taken else 4)
    elif args.cmd == "release":
        agent = None if args.all else agent_id(args.agent)
        targets = [p.parse_addr(a) for a in args.addrs] or [int(c["addr"], 16) for c in claims.all()]
        released = [fmt_addr(a) for a in targets if claims.release(a, agent)]
        emit({"released": released})
    elif args.cmd == "status":
        live = claims.all()
        args.unit, args.name, args.min_size, args.max_size, args.all_regions = None, None, None, None, False
        args.include_siblings = False
        n = len(queue(p, args))
        emit({
            "queue": n,
            "held_siblings": getattr(args, "held_siblings", 0),
            "claimed": len(live),
            "claims": [{"addr": c["addr"], "agent": c["agent"], "symbol": c.get("symbol")} for c in live],
            "accepted": sum(1 for r in p.accepted().values() if not r.get("integrated")),
            "deferred": len(p.deferred()),
            "integrated": len(p.integrated()),
            "difficulty": "instructions" if featurelib.available() else "size (install iced-x86 for a better order)",
        })
    elif args.cmd == "requeue":
        deferred = p.deferred()
        targets = list(deferred) if args.all else [p.parse_addr(a) for a in args.addrs]
        done = []
        for a in targets:
            for suffix in (".json", ".cpp"):
                (p.state / "deferred" / f"{addr_key(a)}{suffix}").unlink(missing_ok=True)
            done.append(fmt_addr(a))
        emit({"requeued": done})


if __name__ == "__main__":
    main()
