#!/usr/bin/env python3
"""The work queue: which function to match next, with claims so parallel workers never collide.

    python tools/agent/next.py claim [--agent ID] [--count N] [--unit U] [--max-size N]
    python tools/agent/next.py release [--agent ID] [addr ...]
    python tools/agent/next.py status
    python tools/agent/next.py list [--limit N] [--unit U]        # the queue head, unclaimed
    python tools/agent/next.py requeue (addr ... | --all)         # lead: forget deferrals

The queue holds every function in symbols.txt except EH unwind funclets
(`Unwind@`, `.text$x`), import thunks, the library region from the CRT entry
point on (--all-regions includes it), and functions already accepted,
integrated into src/, deferred or claimed. It is ordered easy first: by a
difficulty score from the target's instructions (instructions, branches,
calls, switches, EH, x87; needs iced-x86 and the exe or split objects), else
by size.

A claim is a file in build/agent/claims/ created atomically; it expires after
--ttl seconds (try.py renews it on every attempt) and can then be taken over.
Output is JSON.
"""

import argparse
import bisect
import sys
from typing import Dict, List, Optional

import features as featurelib
from common import CLAIM_TTL, Claims, Project, addr_key, agent_id, emit, fmt_addr


def unit_index(p: Project):
    """address -> split unit name, by bisecting the units' .text ranges."""
    ranges = sorted((a, b, u.name) for u in p.units() for a, b in u.text)
    starts = [r[0] for r in ranges]

    def unit_of(address: int) -> str:
        i = bisect.bisect_right(starts, address) - 1
        return ranges[i][2] if i >= 0 and address < ranges[i][1] else ""
    return unit_of


def queue(p: Project, args, claimed: Optional[set] = None) -> List[dict]:
    lib = p.library_start()
    text_x = p.text_x_range()
    imports = {s.name[len("__imp_"):] for s in p.symbols if s.name.startswith("__imp_")}
    done = set(p.accepted()) | set(p.integrated())
    deferred = set() if getattr(args, "include_deferred", False) else set(p.deferred())
    claimed = claimed if claimed is not None else {int(c["addr"], 16) for c in Claims(p).all()}
    unit_of = unit_index(p)
    out = []
    for f in p.functions:
        a = f.address
        if (f.name.startswith("Unwind@") or text_x[0] <= a < text_x[1] or f.name in imports
                or (a >= lib and not args.all_regions) or a in done or a in deferred or a in claimed
                or (args.max_size and f.size > args.max_size)):
            continue
        unit = unit_of(a)
        if args.unit and not (unit == args.unit or unit.startswith(args.unit)):
            continue
        out.append({"addr": fmt_addr(a), "symbol": f.name, "unit": unit, "size": f.size})
    feats = featurelib.features(p, [int(e["addr"], 16) for e in out])
    for e in out:
        feat = feats.get(int(e["addr"], 16))
        e["difficulty"] = feat["score"] if feat else e["size"]
        if feat:
            e["features"] = {k: feat[k] for k in ("insns", "branches", "calls", "switch", "eh", "fp")}
            e["callees"] = [_callee(p, c) for c in feat["callees"]]
    out.sort(key=lambda e: (e["difficulty"], e["addr"]))
    return out


def _callee(p: Project, address: int) -> dict:
    sym = p.by_addr.get(address)
    name = sym.name if sym else f"FUN_{address:08x}"
    return {"addr": fmt_addr(address), "name": name, "named": not name.startswith(("FUN_", "LAB_", "thunk_FUN_"))}


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
        s.add_argument("--max-size", type=lambda v: int(v, 0), help="skip functions larger than this")
        s.add_argument("--all-regions", action="store_true", help="include the library region after the CRT entry")
        s.add_argument("--include-deferred", action="store_true")
        if name == "claim":
            s.add_argument("--agent", help="worker id (default: $T3_AGENT_ID)")
            s.add_argument("--count", type=int, default=1)
            s.add_argument("--ttl", type=float, default=CLAIM_TTL, help="claim lifetime in seconds")
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
        agent = agent_id(args.agent)
        accepted = p.accepted()
        taken = []
        for entry in queue(p, args):
            if len(taken) >= args.count:
                break
            if claims.take(int(entry["addr"], 16), agent, args.ttl, {"symbol": entry["symbol"]}):
                entry["siblings"] = siblings(p, entry, accepted)
                taken.append(entry)
        emit({"agent": agent, "claimed": taken, "empty": not taken})
        sys.exit(0 if taken else 4)
    elif args.cmd == "release":
        agent = None if args.all else agent_id(args.agent)
        targets = [p.parse_addr(a) for a in args.addrs] or [int(c["addr"], 16) for c in claims.all()]
        released = [fmt_addr(a) for a in targets if claims.release(a, agent)]
        emit({"released": released})
    elif args.cmd == "status":
        live = claims.all()
        args.unit, args.max_size, args.all_regions = None, None, False
        emit({
            "queue": len(queue(p, args)),
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
