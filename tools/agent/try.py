#!/usr/bin/env python3
"""Compile one candidate for a function and diff it against the target.

    python tools/agent/try.py <addr> <file.cpp> [--symbol NAME] [--json]

Prints a short verdict: score, mismatching rows, the differing rows with one
row of context (`~` differs, `<` target only, `>` candidate only, `r` wrong
reference or bytes, with the reason on a `!` line), and ATTEMPT k/12.

The file defines exactly one non-inline function, the candidate (or name it
with --symbol); declarations and inline helpers may come before it. The
rulers are those of accept.py (see verify.py): a MATCH here means accept.py
will pass unless the lint objects.

Every scored attempt is recorded in build/agent/attempts/<ADDR>/. A file
byte-identical to an earlier attempt is refused, and past the cap (12 per
claim) or after 3 attempts in a row with no new best (--patience; the score,
then fewer differing rows) the tool refuses too: defer instead, and the best
attempt goes to the next pass. Build failures are shown but not counted.
Exit status: 0 match, 1 no match, 2 build failed, 3 refused.
"""

import argparse
import hashlib
import sys
import time
from pathlib import Path

from common import ATTEMPT_CAP, PATIENCE, Claims, Ledger, Project, addr_key, agent_id, emit, fmt_addr
from verify import Verifier, render


def stalled(entries, patience: int) -> bool:
    """True when the last `patience` of a claim's counted attempts set no new best (score, then fewer
    differing rows) over the attempts before them."""
    if patience <= 0 or len(entries) <= patience:
        return False
    marks = [(e.get("score", 0), -e.get("mismatch_rows", 0)) for e in entries]
    before = max(marks[:-patience])
    return all(m <= before for m in marks[-patience:])


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("addr", help="function address (0x10A52530) or its symbols.txt name")
    parser.add_argument("file", type=Path, help="candidate source file")
    parser.add_argument("--symbol", help="the candidate's decorated name, when the file defines several functions")
    parser.add_argument("--agent", help="worker id (default: $T3_AGENT_ID)")
    parser.add_argument("--cap", type=int, default=ATTEMPT_CAP, help=f"attempts per claim (default {ATTEMPT_CAP})")
    parser.add_argument("--patience", type=int, default=PATIENCE,
                        help=f"attempts in a row with no new best before the claim stops (default {PATIENCE})")
    parser.add_argument("--context", type=int, default=1, help="rows of context around differences")
    parser.add_argument("--json", action="store_true", help="print the full result as JSON")
    args = parser.parse_args()

    p = Project()
    address = p.parse_addr(args.addr)
    fn = p.function(address)
    agent = agent_id(args.agent)
    source = args.file.read_bytes()
    sha = hashlib.sha256(source).hexdigest()[:16]

    ledger = Ledger(p, address)
    entries = ledger.entries()

    def refuse(message: str) -> None:
        print(f"REFUSED: {message}")
        sys.exit(3)

    same = next((e for e in entries if e["sha"] == sha), None)
    if same:
        refuse(f"byte-identical to attempt {same.get('attempt', '?')} ({same.get('file')}: "
               f"{same.get('status')}, score {same.get('score', 0)}). Change the source first.")
    claims = Claims(p)
    claim = claims.get(address)
    if claim and claim.get("agent") != agent:
        refuse(f"{fmt_addr(address)} is claimed by {claim.get('agent')}")
    if claim:
        claims.renew(address, agent)
    claim_id = claim["id"] if claim else "manual"
    mine = [e for e in entries if e.get("claim") == claim_id and e.get("counted")]
    attempt = 1 + len(mine)
    if attempt > args.cap:
        refuse(f"attempt cap reached ({args.cap}/{args.cap}). Defer: python tools/agent/accept.py defer "
               f"{fmt_addr(address)} \"<one-line blocker>\"")
    if stalled(mine, args.patience):
        refuse(f"no new best in the last {args.patience} attempts. Defer with the difference you could not "
               f"close: python tools/agent/accept.py defer {fmt_addr(address)} \"<slug>: <one-line blocker>\"")

    workdir = p.state / "tmp" / f"{agent}-{addr_key(address)}"
    res = Verifier(p).run(address, args.file, workdir, symbol=args.symbol)
    if not res.build_ok and not res.build_log:
        print(f"CANNOT CHECK {fmt_addr(address)} (not counted): " + "; ".join(res.problems))
        sys.exit(3)
    entry = {
        "sha": sha, "file": str(args.file), "time": time.time(), "agent": agent, "claim": claim_id,
        "counted": res.build_ok, "attempt": attempt if res.build_ok else None,
        "status": "match" if res.match else "build-failed" if not res.build_ok else "differs",
        "match": res.match, "score": res.score, "mismatch_rows": res.mismatch_rows, "rows": len(res.rows),
        "problems": len(res.problems), "codegen": res.codegen,
    }
    ledger.add(entry, source)

    if args.json:
        out = res.to_json()
        out.update({"attempt": entry["attempt"], "cap": args.cap, "diff": render(res, args.context)})
        emit(out)
        sys.exit(0 if res.match else 1 if res.build_ok else 2)

    print(f"{fmt_addr(address)} {fn.name}" + (f"  {res.symbol}" if res.symbol else ""))
    if not res.build_ok:
        print("BUILD FAILED (not counted as an attempt). Compiler output:")
        print("\n".join(res.build_log.splitlines()[:40]) or "(none)")
        for problem in res.problems:
            print(f"  - {problem}")
        sys.exit(2)
    best = max((e for e in entries if e.get("counted")), key=lambda e: e.get("score", 0), default=None)
    print(f"ATTEMPT {attempt}/{args.cap}   score {res.score:.1f}   mismatch rows {res.mismatch_rows}/{len(res.rows)}"
          + (f"   (best before: {best['score']:.1f}, attempt {best.get('attempt')})" if best else ""))
    twin = next((e for e in entries if e.get("codegen") and e["codegen"] == res.codegen), None)
    if twin:
        print(f"note: same compiled code as attempt {twin.get('attempt')}: that change did not affect codegen")
    for line in render(res, args.context):
        print(line)
    if res.problems:
        print("problems:")
        for problem in res.problems:
            print(f"  - {problem}")
    provisional = res.provisional()
    if provisional:
        print("provisional names (unnamed in symbols.txt; recorded on accept for the lead):")
        for b in provisional:
            print(f"  {fmt_addr(b.addr)} {b.target} = {b.name}")
    if res.match:
        print(f"MATCH. Now: python tools/agent/accept.py {fmt_addr(address)} {args.file}")
    else:
        print("NO MATCH. Name the asm difference your next attempt targets before editing.")
    sys.exit(0 if res.match else 1)


if __name__ == "__main__":
    main()
