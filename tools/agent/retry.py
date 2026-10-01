#!/usr/bin/env python3
"""Lead only: after a naming pass, retry deferred functions and accept what matches now.

    python tools/agent/retry.py [addr ...] [--conflicts] [--dry-run]

A function a name blocked (a callee recorded under a caller's guessed
signature: docs/agent-workflow.md, "Name conflicts") keeps its candidates: the
best attempt in build/agent/deferred/<ADDR>.cpp and the worker's files in
build/scratch/. Once symbols.txt has the right names, this checks each
candidate with the gate's lint and rulers, newest first, and accepts the first
that matches with accept.py (agent "lead"); the address leaves
build/agent/excluded.json. Without addresses it takes every deferred function
and every exclusion for a name conflict; --conflicts only the name conflicts.
"""

import argparse
import hashlib
import json
import os
import subprocess
import sys
from pathlib import Path
from typing import List

import lint as linter
from common import Project, addr_key, atomic_write, fmt_addr
from verify import Verifier

HERE = Path(__file__).resolve().parent


def candidates(p: Project, address: int) -> List[Path]:
    """The deferred best attempt and the scratch files for an address, newest first, one per content."""
    files = [p.state / "deferred" / f"{addr_key(address)}.cpp"]
    for name in (f"0x{addr_key(address)}", addr_key(address)):
        folder = p.main / "build" / "scratch" / name
        if folder.is_dir():
            files += sorted(folder.glob("*.cpp"), key=lambda f: f.stat().st_mtime, reverse=True)
    seen, out = set(), []
    for f in files:
        if f.is_file():
            digest = hashlib.sha256(f.read_bytes()).hexdigest()
            if digest not in seen:
                seen.add(digest)
                out.append(f)
    return out


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("addrs", nargs="*")
    parser.add_argument("--conflicts", action="store_true", help="only functions deferred or excluded as name conflicts")
    parser.add_argument("--dry-run", action="store_true", help="report what matches, accept nothing")
    args = parser.parse_args()
    p = Project()
    excluded_path = p.state / "excluded.json"
    excluded = json.loads(excluded_path.read_text(encoding="utf-8")) if excluded_path.is_file() else {}
    deferred = p.deferred()
    accepted = p.accepted()
    if args.addrs:
        todo = [p.parse_addr(a) for a in args.addrs]
    else:
        conflicts = {int(a, 16) for a, why in excluded.items() if why.startswith("name conflict")}
        conflicts |= {a for a, rec in deferred.items() if "name" in (rec.get("blocker") or "").lower()}
        todo = sorted(conflicts if args.conflicts else conflicts | set(deferred))
    verifier = Verifier(p)
    matched = []
    for address in todo:
        if address in accepted:
            continue
        for f in candidates(p, address):
            source = f.read_text(encoding="utf-8", errors="replace")
            if linter.lint(source, address):
                continue
            res = verifier.run(address, f, p.state / "tmp" / f"lead-{addr_key(address)}-retry")
            if not (res.build_ok and res.match and not res.problems and not res.mismatch_rows):
                continue
            rel = os.path.relpath(f, p.main)
            if args.dry_run:
                print(f"{fmt_addr(address)} matches: {rel}")
                matched.append(address)
                break
            proc = subprocess.run([sys.executable, str(HERE / "accept.py"), fmt_addr(address), str(f), "--agent", "lead"],
                                  cwd=p.main, capture_output=True, text=True)
            print((proc.stdout or proc.stderr).strip().splitlines()[0] + f"  ({rel})")
            if proc.returncode == 0:
                matched.append(address)
                excluded.pop(fmt_addr(address), None)
                break
    if matched and not args.dry_run:
        atomic_write(excluded_path, json.dumps(excluded, indent=1))
    print(f"{len(matched)} of {len(todo)} functions {'match' if args.dry_run else 'accepted'}")


if __name__ == "__main__":
    main()
