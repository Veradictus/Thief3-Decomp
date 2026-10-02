#!/usr/bin/env python3
"""Lead only: close a batch of workers and report what each matched and what it cost.

    python tools/agent/sweep.py <worker id or glob> ... [--transcripts DIR] [--report-only] [--no-stamp]

For the given worker ids (the ID= in each worker's prompt, see
docs/agent-workflow.md; a glob such as 's3-*' takes every id it matches):

  1. accepts every attempt a ledger records as a MATCH that accept.py never
     recorded (workers sometimes stop after try.py), under the worker's id,
     unless the lead rejected the function (its records moved to
     build/agent/rejected/) or deferred it;
  2. releases the claims the workers left behind;
  3. adds two kinds of the workers' deferrals to build/agent/excluded.json,
     which the queue skips, so no second pass spends tokens on them:
     adjustor thunks (compiler-made, not source), and name conflicts (the
     code matches but a name does not: tools/agent/fixnames.py settles
     them, see docs/agent-workflow.md);
  4. stamps the families of what was accepted (clusters.py stamp), unless
     --no-stamp: their other members match without a model;
  5. prints per worker: accepted and deferred functions, counted attempts,
     first-try matches, and the tokens of its transcript: API messages,
     input, cache writes, cache reads and output, each message counted once;
     then the matches by attempt number and the deferrals by blocker slug
     (the word before the blocker's first colon), and appends the batch's
     totals to build/agent/swarms.jsonl.

The transcripts are Claude Code's sub-agent transcripts
(<DIR>/<project>/<session>/subagents/agent-*.jsonl, DIR defaulting to
~/.claude/projects); a worker's is the one whose first prompt holds its
`ID=<id>` and whose `cwd` is this checkout. --report-only skips 1 to 3.
"""

import argparse
import collections
import fnmatch
import json
import os
import re
import subprocess
import sys
import time
from pathlib import Path
from typing import Dict, Optional, Tuple

from common import Claims, Project, atomic_write

HERE = Path(__file__).resolve().parent
KEYS = ("input_tokens", "cache_creation_input_tokens", "cache_read_input_tokens", "output_tokens")


def records(p: Project, kind: str):
    for path in (p.state / kind).glob("*.json"):
        yield json.loads(path.read_text(encoding="utf-8"))


def accept_forgotten(p: Project, workers) -> None:
    """Accepts the ledgers' unaccepted MATCHes of these workers."""
    # Rejected at review or deferred: a match in the ledger is not to be taken again.
    done = {path.stem for kind in ("accepted", "rejected", "deferred") for path in (p.state / kind).glob("*.json")}
    for ledger in sorted((p.state / "attempts").glob("*/ledger.jsonl")):
        if ledger.parent.name in done:
            continue
        entries = [json.loads(line) for line in ledger.read_text(encoding="utf-8").splitlines() if line.strip()]
        hit = next((e for e in entries if e.get("match") and e.get("agent") in workers), None)
        if not hit or not (p.root / hit["file"]).is_file():
            continue
        proc = subprocess.run([sys.executable, str(HERE / "accept.py"), "0x" + ledger.parent.name, hit["file"]],
                              env=dict(os.environ, T3_AGENT_ID=hit["agent"]), cwd=p.root, capture_output=True,
                              text=True)
        lines = (proc.stdout or proc.stderr).strip().splitlines()
        print(f"accepted for {hit['agent']}: {lines[0] if lines else proc.returncode}")


THUNK = "adjustor thunk: made by the compiler for multiple inheritance, not source"
CONFLICT = ("name conflict: an earlier caller's guessed signature fixed this function's name; "
            "tools/agent/fixnames.py, then requeue")
NAME_WORDS = re.compile(r"symbol|decorat|mangl|signature|return type|name[- ](mismatch|conflict)|void\b[^.]*\beax\b",
                        re.I)
# Deferrals no worker can turn into a match (worker.md's slugs): out of the queue and of second passes.
OUT_OF_SCOPE = {
    "library": "library code: matched from library objects or original sources, not by workers",
    "engine": "Epic's engine code: not decompiled (CONTRIBUTING.md)",
    "compiler-generated": "compiler-generated: emitted from a class's virtual destructor or a global (dtors.py)",
    "asm": "hand-written assembly in the original: no C++ source compiles to it",
}


def park(p: Project, workers) -> None:
    """Adds these workers' adjustor thunks, name conflicts and out-of-scope deferrals to excluded.json."""
    path = p.state / "excluded.json"
    excluded = json.loads(path.read_text(encoding="utf-8")) if path.is_file() else {}
    added = collections.Counter()
    for rec in records(p, "deferred"):
        if rec.get("agent") not in workers or rec["addr"] in excluded:
            continue
        blocker = rec.get("blocker") or ""
        slug = blocker.split(":", 1)[0].strip().lower()
        best = rec.get("best") or {}
        if "adjustor thunk" in blocker.lower():
            excluded[rec["addr"]], kind = THUNK, "adjustor thunks"
        elif slug in OUT_OF_SCOPE:
            excluded[rec["addr"]], kind = OUT_OF_SCOPE[slug], slug
        elif (best.get("score", 0) >= 99.9 and not best.get("mismatch_rows")) or NAME_WORDS.search(blocker):
            # The code matches and only a name differs.
            excluded[rec["addr"]], kind = CONFLICT, "name conflicts"
        else:
            continue
        added[kind] += 1
    if added:
        atomic_write(path, json.dumps(excluded, indent=1) + "\n")
        print("excluded " + ", ".join(f"{n} {kind}" for kind, n in added.items()))


def transcript_usage(path: Path, workers, checkout: Path) -> Optional[Tuple[str, str, int, Dict[str, int]]]:
    """(worker id, model, API messages, token totals) of a worker's transcript, or None."""
    ident, last, model = None, {}, None
    with open(path, encoding="utf-8") as f:
        for line in f:
            row = json.loads(line)
            message = row.get("message") or {}
            if ident is None and row.get("type") == "user":
                found = re.search(r"\bID=(\w+)", json.dumps(message.get("content")))
                cwd = row.get("cwd")
                if not found or found.group(1) not in workers or not cwd or not os.path.normcase(str(Path(cwd).resolve())).startswith(os.path.normcase(str(checkout))):
                    return None
                ident = found.group(1)
            if row.get("type") == "assistant" and message.get("usage"):
                last[message.get("id")] = message["usage"]  # streamed rows repeat a message: keep its last
                model = message.get("model")
    if ident is None:
        return None
    totals = collections.Counter()
    for usage in last.values():
        for key in KEYS:
            totals[key] += usage.get(key) or 0
    return ident, model or "?", len(last), totals


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("workers", nargs="+", help="worker ids (the ID= of their prompts)")
    parser.add_argument("--transcripts", type=Path, default=Path.home() / ".claude" / "projects",
                        help="Claude Code's projects folder")
    parser.add_argument("--report-only", action="store_true", help="accept nothing, release nothing, stamp nothing")
    parser.add_argument("--no-stamp", action="store_true", help="do not stamp the families of what was accepted")
    args = parser.parse_args()
    if os.environ.get("T3_AGENT_ID"):
        sys.exit("sweep.py is the lead's")

    p = Project()
    workers = Workers(args.workers)
    if not args.report_only:
        accept_forgotten(p, workers)
        claims = Claims(p)
        for claim in claims.all():
            if claim.get("agent") in workers and claims.release(int(claim["addr"], 16), claim["agent"]):
                print(f"released {claim['addr']} ({claim['agent']})")
        park(p, workers)
        if not args.no_stamp:
            import clusters as clusterlib
            try:
                result = clusterlib.stamp(p)
                print("stamped families: " + ", ".join(f"{n} {k}" for k, n in result["summary"].items()))
            except Exception as e:  # no split objects, no iced-x86: the batch's records are still swept
                print(f"stamping skipped: {e}")

    outcome = collections.defaultdict(collections.Counter)
    by_attempt = collections.Counter()
    slugs = collections.Counter()
    for rec in records(p, "accepted"):
        if rec.get("agent") in workers:
            o = outcome[rec["agent"]]
            o["matched"] += 1
            o["attempts"] += rec.get("attempts") or 0
            o["first"] += rec.get("attempts") == 1
            by_attempt[min(rec.get("attempts") or 0, 5)] += 1
    for rec in records(p, "deferred"):
        if rec.get("agent") in workers:
            outcome[rec["agent"]]["deferred"] += 1
            outcome[rec["agent"]]["attempts"] += rec.get("attempts") or 0
            blocker = (rec.get("blocker") or "").strip()
            slugs[blocker.split(":", 1)[0].strip().lower()[:24] if ":" in blocker[:30] else "(no slug)"] += 1

    usage = {}
    checkout = p.root.resolve()
    for path in args.transcripts.glob("*/*/subagents/agent-*.jsonl"):
        found = transcript_usage(path, workers, checkout)
        if found:
            usage[found[0]] = found[1:]

    print(f"{'id':8} {'model':26} {'match':>5} {'defer':>5} {'tries':>5} {'first':>5} {'msgs':>5} "
          f"{'input':>7} {'c.write':>8} {'c.read':>10} {'output':>7}")
    total = collections.Counter()
    models = collections.Counter()
    for worker in sorted(set(outcome) | set(usage)):
        o = outcome[worker]
        model, messages, t = usage.get(worker, ("(no transcript)", 0, collections.Counter()))
        models[model] += 1
        print(f"{worker:8} {model:26} {o['matched']:5} {o['deferred']:5} {o['attempts']:5} {o['first']:5} "
              f"{messages:5} {t['input_tokens']:7} {t['cache_creation_input_tokens']:8} "
              f"{t['cache_read_input_tokens']:10} {t['output_tokens']:7}")
        total.update(o)
        total.update(t)
    read = total["cache_read_input_tokens"] + total["cache_creation_input_tokens"] + total["input_tokens"]
    # Priced as billed: cache reads at 0.1 and cache writes at 1.25 of uncached input, output at 5.
    priced = (total["input_tokens"] + 0.1 * total["cache_read_input_tokens"]
              + 1.25 * total["cache_creation_input_tokens"] + 5 * total["output_tokens"])
    if total["matched"]:
        print(f"{total['matched']} matched, {total['deferred']} deferred; "
              f"{read // total['matched']} input tokens per match (cache reads and writes included), "
              f"{int(priced // total['matched'])} priced")
    if by_attempt:
        print("matches by attempt: "
              + ", ".join(f"{'5+' if k == 5 else k}: {n}" for k, n in sorted(by_attempt.items())))
    if slugs:
        print("deferrals by slug: " + ", ".join(f"{k} {n}" for k, n in slugs.most_common(12)))
    if not args.report_only and (total["matched"] or total["deferred"]):
        line = {"time": time.time(), "workers": sorted(set(outcome) | set(usage)), "models": dict(models),
                "matched": total["matched"], "deferred": total["deferred"], "attempts": total["attempts"],
                "first": total["first"], "input_side": read, "output": total["output_tokens"],
                "priced": int(priced), "by_attempt": {str(k): n for k, n in sorted(by_attempt.items())},
                "slugs": dict(slugs)}
        with open(p.state_dir() / "swarms.jsonl", "a", encoding="utf-8") as f:
            f.write(json.dumps(line) + "\n")


class Workers:
    """Worker ids given as names or globs (`s3-*`); `id in workers` matches either."""

    def __init__(self, patterns):
        self.patterns = list(patterns)

    def __contains__(self, ident) -> bool:
        return bool(ident) and any(fnmatch.fnmatchcase(ident, pat) for pat in self.patterns)


if __name__ == "__main__":
    main()
