#!/usr/bin/env python3
"""The gate: accept a matching function, or defer one that will not match.

    python tools/agent/accept.py <addr> <file.cpp> [--symbol NAME] [--strict-names]
    python tools/agent/accept.py defer <addr> "<one-line blocker>" [--needs "..."]

accept passes only when
  - the lint passes: no inline asm, _emit, __declspec(naked), goto,
    codegen #pragmas, pointer+integer-offset casts or literal exe addresses,
    and exactly one `// FUNCTION: 0x<ADDR>` line right before the function;
  - the candidate compiles and verify.py finds zero mismatching rows, with
    every reference resolved by the code ruler (callee and global identity)
    and every literal, table and EH structure by the data ruler (values);
  - with --strict-names, no reference relies on a provisional name.
On success the source and a record (bindings, EH ranges, attempts) go to
build/agent/accepted/<ADDR>.{cpp,json} for the lead's integrate.py; workers
never write src/. The claim is released.

defer records the best attempt from the ledger with a one-line blocker (and
what the lead would need to unblock it) in build/agent/deferred/, and releases
the claim. Deferring is a successful outcome.
"""

import argparse
import hashlib
import json
import re
import shutil
import sys
import time
from pathlib import Path

import lint as linter
from common import (Claims, Ledger, Project, addr_key, agent_id, atomic_write, class_of, emit, fmt_addr,
                    qualified_name)
from verify import Verifier, render


# Functions MSVC writes itself: scalar and vector deleting destructors.
GENERATED = ("??_G", "??_E")


def defines(source: str, symbol: str) -> bool:
    """Whether the definition after the `// FUNCTION:` line is the constructor (??0) or destructor (??1)
    `symbol` names, rather than another function's."""
    cls = re.match(r"\?\?[01](\w+?)@", symbol)
    marked = re.search(r"// FUNCTION: [^\n]*\n([^{;]*?)\(", source)
    if not cls or not marked:
        return True
    tilde = "~" if symbol.startswith("??1") else ""
    return bool(re.search(r"\b%s::%s%s\s*$" % (re.escape(cls.group(1)), tilde, re.escape(cls.group(1))),
                          marked.group(1).strip()))


def emitter_of(p: Project, obj_path: Path, address: int):
    """The one function the compiled candidate defines (not inline) that symbols.txt names, other than
    `address`: the definition that made the compiler emit a generated function; None if not exactly one."""
    import coff
    if not obj_path.is_file():
        return None
    obj = coff.Coff.load(obj_path)
    found = {p.by_name[s.name].address for s in obj.functions() if s.external and s.name in p.by_name
             and obj.section(s.section).selection != coff.IMAGE_COMDAT_SELECT_ANY}
    found.discard(address)
    return found.pop() if len(found) == 1 else None


def accept(argv) -> None:
    parser = argparse.ArgumentParser(prog="accept.py", description=__doc__,
                                     formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("addr")
    parser.add_argument("file", type=Path)
    parser.add_argument("--symbol", help="the candidate's decorated name, when the file defines several functions")
    parser.add_argument("--agent", help="worker id (default: $T3_AGENT_ID)")
    parser.add_argument("--strict-names", action="store_true",
                        help="also require every referenced address to be named in symbols.txt")
    parser.add_argument("--replace", action="store_true", help="replace an existing accepted record")
    parser.add_argument("--with", dest="emitter",
                        help="for a compiler-generated function (--symbol ??_G...): the function whose definition "
                             "makes the compiler emit it (default: the file's one function symbols.txt names)")
    args = parser.parse_args(argv)

    p = Project()
    address = p.parse_addr(args.addr)
    fn = p.function(address)
    agent = agent_id(args.agent)
    source = args.file.read_text(encoding="utf-8", errors="replace")

    def reject(reasons, extra=None) -> None:
        print(f"REJECTED {fmt_addr(address)} {fn.name}")
        for reason in reasons:
            print(f"  - {reason}")
        for line in extra or []:
            print(line)
        sys.exit(1)

    claim = Claims(p).get(address)
    if claim and claim.get("agent") != agent:
        reject([f"claimed by {claim.get('agent')}"])
    previous = p.accepted().get(address)
    if previous and not args.replace:
        reject([f"already accepted ({previous.get('symbol')}, by {previous.get('agent')}); --replace to redo it"])
    problems = linter.lint(source, address)
    if problems:
        reject(["lint: " + pr for pr in problems])

    res = Verifier(p).run(address, args.file, p.state / "tmp" / f"{agent}-{addr_key(address)}-accept",
                          symbol=args.symbol)
    if not res.build_ok:
        reject(res.problems if not res.build_log else ["the file does not compile"] + res.build_log.splitlines()[:20])
    reasons = list(res.problems)
    if res.mismatch_rows:
        reasons.append(f"{res.mismatch_rows} of {len(res.rows)} rows differ (score {res.score:.1f})")
    if args.strict_names and res.provisional():
        reasons += [f"{b.target} ({fmt_addr(b.addr)}) is not named in symbols.txt (candidate: {b.name})"
                    for b in res.provisional()]
    if reasons or not res.match:
        reject(reasons or ["no match"], render(res))

    generated = {}
    # An implicit constructor or destructor has no definition either: the marker sits on another function's,
    # which must be the game's own (--with), never one made up to make the compiler emit it.
    implicit = res.symbol.startswith(("??0", "??1")) and not defines(source, res.symbol)
    if implicit and not args.emitter:
        reject([f"the marker sits on another function's definition, not {res.symbol}'s: an implicit constructor "
                f"or destructor is accepted with --with <the game's function whose definition emits it>"])
    if res.symbol.startswith(GENERATED) or implicit:
        # No definition of its own: it is emitted with its class's vtable, where the class's constructor or
        # destructor is defined. integrate.py puts its marker in that function's unit.
        workdir = p.state / "tmp" / f"{agent}-{addr_key(address)}-accept"
        emitter = p.parse_addr(args.emitter) if args.emitter else emitter_of(p, workdir / "candidate.obj", address)
        if emitter is None:
            reject([f"{res.symbol} is compiler-generated: pass --with <the function whose definition emits it>"])
        generated = {"generated": True, "with": fmt_addr(emitter)}

    ledger = Ledger(p, address)
    qualified = qualified_name(res.symbol, res.demangled)
    code_end, region_end = p.code_extent(address)
    eh = []  # the function's EH handler and unwind funclets in .text$x, merged where adjacent
    for a, b in sorted((b.addr, b.addr + b.size) for b in res.bindings if b.kind in ("ehhandler", "funclet")):
        if eh and a <= eh[-1][1]:
            eh[-1][1] = max(eh[-1][1], b)
        else:
            eh.append([a, b])
    record = {
        "addr": fmt_addr(address),
        "target": fn.name,
        "symbol": res.symbol,
        "demangled": res.demangled,
        "qualified": qualified,
        "class": class_of(qualified),
        "size": fn.size,
        "region": [fmt_addr(address), fmt_addr(region_end)],
        "text_x": [[fmt_addr(a), fmt_addr(b)] for a, b in eh],
        "bindings": [b.to_json() for b in res.bindings],
        "provisional": len(res.provisional()),
        "cflags": p.cflags_for(address),
        "source_sha": hashlib.sha256(args.file.read_bytes()).hexdigest()[:16],
        "agent": agent,
        "claim": claim["id"] if claim else "manual",
        "attempts": sum(1 for e in ledger.entries() if e.get("counted")),
        "accepted": time.time(),
        **generated,
    }
    out = p.state_dir("accepted")
    shutil.copyfile(args.file, out / f"{addr_key(address)}.cpp")
    atomic_write(out / f"{addr_key(address)}.mnemonics", " ".join(res.mnemonics) + "\n")
    atomic_write(out / f"{addr_key(address)}.json", json.dumps(record, indent=1))
    Claims(p).release(address)
    for suffix in (".json", ".cpp"):
        (p.state / "deferred" / f"{addr_key(address)}{suffix}").unlink(missing_ok=True)
    print(f"ACCEPTED {fmt_addr(address)} {fn.name} = {res.symbol}"
          + (f" ({record['provisional']} provisional names for the lead)" if record["provisional"] else ""))


def defer(argv) -> None:
    parser = argparse.ArgumentParser(prog="accept.py defer", description="Record a deferred function.")
    parser.add_argument("addr")
    parser.add_argument("blocker", help="one line: why it does not match")
    parser.add_argument("--needs", action="append", default=[],
                        help="what would unblock it (a header, a layout, a name); repeatable")
    parser.add_argument("--agent", help="worker id (default: $T3_AGENT_ID)")
    args = parser.parse_args(argv)

    p = Project()
    address = p.parse_addr(args.addr)
    fn = p.function(address)
    agent = agent_id(args.agent)
    claim = Claims(p).get(address)
    if claim and claim.get("agent") != agent:
        sys.exit(f"{fmt_addr(address)} is claimed by {claim.get('agent')}")
    ledger = Ledger(p, address)
    best = ledger.best()
    record = {
        "addr": fmt_addr(address), "target": fn.name, "size": fn.size,
        "blocker": " ".join(args.blocker.split()), "needs": args.needs, "agent": agent,
        "claim": claim["id"] if claim else "manual",
        "attempts": sum(1 for e in ledger.entries() if e.get("counted")), "deferred": time.time(),
        "best": {k: best.get(k) for k in ("sha", "file", "attempt", "score", "mismatch_rows", "rows")}
        if best else None,
    }
    out = p.state_dir("deferred")
    if best and ledger.source(best["sha"]) is not None:
        (out / f"{addr_key(address)}.cpp").write_bytes(ledger.source(best["sha"]))
    atomic_write(out / f"{addr_key(address)}.json", json.dumps(record, indent=1))
    Claims(p).release(address, agent)
    emit(record)


def main() -> None:
    if len(sys.argv) > 1 and sys.argv[1] == "defer":
        defer(sys.argv[2:])
    else:
        accept(sys.argv[1:])


if __name__ == "__main__":
    main()
