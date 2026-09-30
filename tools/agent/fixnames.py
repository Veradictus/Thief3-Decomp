#!/usr/bin/env python3
"""Lead only: settle name conflicts where a caller's guessed signature fixed a free function's name.

    python tools/agent/fixnames.py prepare <addr> ...
    python tools/agent/fixnames.py constants   # prepare every queued function that only returns a constant
    python configure.py && ninja          # the split must carry the new names
    python tools/agent/fixnames.py accept

A stub that jumps to an unmatched function guesses its signature, and
integration writes the guess into symbols.txt. When the function is matched
later with its real signature, the gate rejects its name and the worker
defers it (see docs/agent-workflow.md, "Name conflicts"). For each deferred
address, `prepare`:

  1. takes the name the deferred candidate compiles to (try.py --json on a
     copy of it, so the lead's probe is never refused as a duplicate); a
     target that is only `mov eax, imm; ret` gets a candidate written for it
     when its worker deferred it without one;
  2. gives the address that name in symbols.txt;
  3. writes each accepted caller that bound the old name with the
     candidate's declaration instead, to build/scratch/<caller>/lead-fix.cpp,
     and changes the declaration in the caller's src/ unit the same way;
  4. records all this in build/agent/fixnames-plan.json.

After a new split, `accept` accepts each patched caller (its old record
moved to build/agent/rejected/, since accept.py --replace would still check
names against it), then the deferred candidate, and takes the address off
build/agent/excluded.json. Free functions only; the rest is reported.
"""

import json
import os
import re
import subprocess
import sys
import time
from pathlib import Path
from typing import Optional

from common import Project, atomic_write, fmt_addr

HERE = Path(__file__).resolve().parent


def tool(p: Project, *args) -> subprocess.CompletedProcess:
    return subprocess.run([sys.executable, str(HERE / args[0]), *args[1:]], cwd=p.root,
                          env=dict(os.environ, T3_AGENT_ID="lead"), capture_output=True, text=True)


def first_line(proc: subprocess.CompletedProcess) -> str:
    lines = (proc.stdout or proc.stderr).strip().splitlines()
    return lines[0][:100] if lines else str(proc.returncode)


def declarations(fname: str) -> re.Pattern:
    # File-scope declarations only: they start in column 0, statements are indented.
    return re.compile(r"^(?![ \t])[^\n;{}]*\b" + fname + r"\s*\([^;{]*\)\s*;", re.M)


def constant_value(p: Project, address: int, image=None) -> Optional[str]:
    """The constant a function returns when its whole code is `mov eax, imm; ret` or `xor eax, eax; ret`."""
    from iced_x86 import Decoder, Formatter, FormatterSyntax
    from verify import TargetImage

    code_end, _ = p.code_extent(address)
    view = (image or TargetImage(p)).view(address, code_end - address)
    if view is None:
        return None
    formatter = Formatter(FormatterSyntax.INTEL)
    rows = [formatter.format(insn) for insn in Decoder(32, view.data, ip=address)]
    if len(rows) != 2 or rows[1] != "ret":
        return None
    if rows[0] == "xor eax,eax":
        return "0"
    value = re.fullmatch(r"mov eax,([0-9A-Fa-f]+)h?", rows[0])
    return "0x" + value.group(1).lstrip("0").lower() if value and value.group(1).strip("0") else None


def constant_functions(p: Project) -> list:
    """Queued and deferred functions (outside excluded.json) whose whole code returns a constant."""
    import argparse

    import next as queue
    from verify import TargetImage

    args = argparse.Namespace(unit=None, name=None, min_size=None, max_size=16, all_regions=False,
                              include_deferred=True)
    image = TargetImage(p)
    return [int(e["addr"], 16) for e in queue.queue(p, args) if constant_value(p, int(e["addr"], 16), image)]


def constant_candidate(p: Project, addr: str, fname: str) -> Optional[str]:
    """A candidate for a target that only returns a constant: a free function returning it."""
    value = constant_value(p, p.parse_addr(addr))
    if value is None:
        return None
    path = p.root / "build" / "scratch" / addr / "lead-const.cpp"
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(f"// FUNCTION: {addr}\nint {fname}()\n{{\n    return {value};\n}}\n", encoding="utf-8")
    return str(path.relative_to(p.root))


def prepare(p: Project, addr: str) -> dict:
    key = addr[2:]
    fname = f"FUN_{key.lower()}"
    record = p.state / "deferred" / f"{key}.json"
    best = (json.loads(record.read_text(encoding="utf-8")).get("best") or {}).get("file") if record.is_file() else None
    best = best or constant_candidate(p, addr, fname)
    if not best:
        return {"addr": addr, "skip": "no deferred candidate"}
    source = (p.root / best).read_text(encoding="utf-8")
    head = re.search(r"// FUNCTION:[^\n]*\n([^\n{]*\b" + fname + r"\s*\([^)]*\))", source)
    if not head or "::" in head.group(1):
        return {"addr": addr, "skip": "not a free function"}
    decl = head.group(1).strip() + ";"

    probe = p.root / "build" / "scratch" / addr / f"lead-probe-{int(time.time())}.cpp"
    probe.parent.mkdir(parents=True, exist_ok=True)
    probe.write_text(source, encoding="utf-8")
    proc = tool(p, "try.py", addr, str(probe.relative_to(p.root)), "--json")
    try:
        result = json.loads(proc.stdout)
    except ValueError:
        return {"addr": addr, "skip": "try.py: " + first_line(proc)}
    new = result.get("symbol")
    if not new or result.get("mismatch_rows"):
        return {"addr": addr, "skip": f"differs apart from its name (score {result.get('score')})"}

    text = p.symbols_txt.read_text(encoding="utf-8")
    line = re.search(r"^(\S+) = \.text:" + addr + r";", text, re.M | re.I)
    if not line:
        return {"addr": addr, "skip": "no symbols.txt entry"}
    old = line.group(1)
    if old != new:
        atomic_write(p.symbols_txt, text[:line.start(1)] + new + text[line.end(1):])

    pattern = declarations(fname)
    callers = []
    for path in sorted((p.state / "accepted").glob("*.json")):
        rec = json.loads(path.read_text(encoding="utf-8"))
        if not any(b.get("name") == old and b.get("addr", "").upper() == addr.upper() for b in rec.get("bindings", [])):
            continue
        caller = "0x" + path.stem
        fixed, n = pattern.subn(decl, path.with_suffix(".cpp").read_text(encoding="utf-8"))
        if not n:
            callers.append({"addr": caller, "skip": "declaration not found"})
            continue
        target = p.root / "build" / "scratch" / caller / "lead-fix.cpp"
        target.parent.mkdir(parents=True, exist_ok=True)
        target.write_text(fixed, encoding="utf-8", newline="\n")
        for unit in (p.root / "src").rglob("*.cpp"):
            text = unit.read_text(encoding="utf-8")
            if f"// FUNCTION: {caller}" in text:
                unit.write_text(pattern.sub(decl, text), encoding="utf-8", newline="\n")
        callers.append({"addr": caller, "file": str(target.relative_to(p.root))})
    return {"addr": addr, "old": old, "new": new, "file": best, "callers": callers}


def accept(p: Project, plan: list) -> None:
    rejected = p.state_dir("rejected")
    excluded_path = p.state / "excluded.json"
    excluded = json.loads(excluded_path.read_text(encoding="utf-8")) if excluded_path.is_file() else {}
    for item in plan:
        if item.get("skip"):
            continue
        for caller in item["callers"]:
            if caller.get("skip"):
                continue
            for f in (p.state / "accepted").glob(caller["addr"][2:] + ".*"):
                f.replace(rejected / f.name)
            print(f"  caller {caller['addr']}: {first_line(tool(p, 'accept.py', caller['addr'], caller['file']))}")
        verdict = first_line(tool(p, "accept.py", item["addr"], item["file"]))
        print(f"{item['addr']} {item['old']} -> {item['new']}: {verdict}")
        if verdict.startswith("ACCEPTED"):
            excluded.pop(item["addr"], None)
    atomic_write(excluded_path, json.dumps(excluded, indent=1) + "\n")


def main() -> None:
    if len(sys.argv) < 2 or sys.argv[1] not in ("prepare", "constants", "accept"):
        sys.exit(__doc__)
    if os.environ.get("T3_AGENT_ID"):
        sys.exit("fixnames.py is the lead's")
    p = Project()
    plan_path = p.state / "fixnames-plan.json"
    if sys.argv[1] == "accept":
        accept(p, json.loads(plan_path.read_text(encoding="utf-8")))
        plan_path.unlink()
        return
    if sys.argv[1] == "constants":
        addresses = constant_functions(p)
        print(f"{len(addresses)} queued or deferred functions only return a constant")
    else:
        addresses = [p.parse_addr(a) for a in sys.argv[2:]]
    # A plan not yet accepted is kept: preparing an address again finds no caller with the old
    # name any more, so its first entry wins.
    plan = {item["addr"]: item for item in (json.loads(plan_path.read_text(encoding="utf-8"))
                                            if plan_path.is_file() else [])}
    new = [prepare(p, fmt_addr(a)) for a in addresses]
    for item in new:
        if item.get("skip") or item["addr"] not in plan or plan[item["addr"]].get("skip"):
            plan[item["addr"]] = item
    atomic_write(plan_path, json.dumps(list(plan.values()), indent=1))
    if sys.argv[1] == "constants":  # out of the queue until `accept`, so no worker spends tokens on them
        excluded_path = p.state / "excluded.json"
        excluded = json.loads(excluded_path.read_text(encoding="utf-8")) if excluded_path.is_file() else {}
        for item in new:
            if not item.get("skip"):
                excluded.setdefault(item["addr"], "returns a constant: fixnames.py constants, then accept")
        atomic_write(excluded_path, json.dumps(excluded, indent=1) + "\n")
    for item in new:
        print(item["addr"], item.get("skip") or f"{item['old']} -> {item['new']}; callers: "
              + (", ".join(c["addr"] + (f" ({c['skip']})" if c.get("skip") else "") for c in item["callers"])
                 or "none"))


if __name__ == "__main__":
    main()
