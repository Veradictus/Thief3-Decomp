#!/usr/bin/env python3
"""The progress report decomp.dev shows: written from a local build, checked and published by CI.

    python tools/progress_report.py write [--version PC_20040610]    after a build, with orig/
    python tools/progress_report.py check [--version PC_20040610]    CI: no exe or compiler needed
    python tools/progress_report.py summary [--version PC_20040610]  a Markdown table of the report

decomp.dev reads an objdiff report (format version 2) from the artifact
<version>_report of the latest push run on the default branch. CI cannot make
one: the build splits T3Main.exe, which never enters the repository or CI. So
`write` builds build/<version>/report.json with ninja (objdiff compares every
compiled unit with the split exe) and commits nothing itself: it copies the
report to progress/<version>/report.json, which is committed, and which CI
checks and uploads. The report holds names, addresses, sizes and match
percentages; no bytes of the game.

Its categories come from config/<version>/categories.txt (tools/classify.py):
the headline, "main", is Ion Storm's game code, which the decompilation
covers; Epic's engine, the libraries and unclassified code are reported for
reference. The .text$x funclets no declared unit takes are left out (the
compiler emits them with their parent function), and so is data: nothing is
split into units yet, so `write` drops the data measures (decomp.dev then shows
none) and the data-only __shared_data unit.

`check` fails when the committed report no longer describes the tree:
  - its units are not the ones configure.py plans from splits.txt,
    symbols.txt and categories.txt, each with the same functions (by address);
  - the functions in its units with source are not exactly those with a
    `// FUNCTION:` line in src/ (their EH handlers and unwind funclets aside);
  - a function in src/ is not game code by categories.txt: only Ion Storm's
    code is published (CONTRIBUTING.md).
It cannot tell whether those functions still match: that takes the exe. The
gate (tools/agent/accept.py) is what proves a match; the report displays it.
Standard library only (and configure.py).
"""

import argparse
import bisect
import json
import os
import re
import shutil
import subprocess
import sys
from pathlib import Path
from typing import Dict, List, Set

ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT))

import configure  # noqa: E402

FORMAT_VERSION = 2
# Units objdiff adds on its own: the data no unit claims (dropped by `write`).
EXTRA_UNITS = {"__shared_data"}
# Measures of data, which no unit has yet (see the module docstring).
DATA_MEASURES = ("total_data", "matched_data", "matched_data_percent", "complete_data", "complete_data_percent")
# Compiled with their parent function, and named after it: no `// FUNCTION:` line.
COMPANIONS = ("Unwind@", "__ehhandler$")
FUNCTION_LINE = re.compile(r"^// FUNCTION: 0x([0-9A-Fa-f]{8})\b", re.M)


def report_path(version: str) -> Path:
    return ROOT / "progress" / version / "report.json"


def planned_units(version: str) -> Dict[str, Set[int]]:
    """Each unit configure.py plans, with the addresses of its functions."""
    config_dir = ROOT / "config" / version
    functions = sorted((s for s in configure.symbolslib.load(config_dir / "symbols.txt")
                        if s.is_function and s.size > 0), key=lambda s: s.address)
    starts = [f.address for f in functions]
    units = {}
    for unit in configure.plan_units(config_dir):
        if not configure.reported(unit):
            continue
        addresses = set()
        for start, end in unit.text:
            addresses.update(f.address for f in functions[bisect.bisect_left(starts, start):bisect.bisect_left(starts, end)])
        units[unit.name] = addresses
    return units


def source_functions() -> Set[int]:
    """The addresses with a `// FUNCTION:` line in src/."""
    found: Set[int] = set()
    for path in sorted((ROOT / "src").rglob("*.cpp")):
        found.update(int(m, 16) for m in FUNCTION_LINE.findall(path.read_text(encoding="utf-8", errors="replace")))
    return found


def address_of(function: dict) -> int:
    return int(function.get("metadata", {}).get("virtual_address", -1))


def problems(report: dict, version: str) -> List[str]:
    """Why `report` no longer describes the tree; empty when it does."""
    out = []
    if report.get("version") != FORMAT_VERSION:
        out.append(f"report format version {report.get('version')}, expected {FORMAT_VERSION}")
    categories = [c.get("id") for c in report.get("categories", [])]
    if categories != list(configure.CATEGORIES):
        out.append(f"progress categories {categories}, configure.py has {list(configure.CATEGORIES)}")

    planned = planned_units(version)
    reported = {u["name"]: u for u in report.get("units", [])}
    for name in sorted(set(planned) - set(reported)):
        out.append(f"unit {name} is planned but not in the report")
    for name in sorted(set(reported) - set(planned) - EXTRA_UNITS):
        out.append(f"unit {name} is in the report but no longer planned")
    for name in sorted(set(planned) & set(reported)):
        have = {address_of(f) for f in reported[name].get("functions", [])}
        if have != planned[name]:
            out.append(f"unit {name}: {len(planned[name] - have)} function(s) missing from the report, "
                       f"{len(have - planned[name])} no longer in the unit")

    with_source = {address_of(f) for u in reported.values() if u.get("metadata", {}).get("source_path")
                   for f in u.get("functions", []) if not f["name"].startswith(COMPANIONS)}
    in_src = source_functions()
    for address in sorted(in_src - with_source):
        out.append(f"0x{address:08X} has a // FUNCTION: line in src/, but the report does not compile it")
    for address in sorted(with_source - in_src):
        out.append(f"0x{address:08X} is compiled in the report, but no // FUNCTION: line in src/ has it")
    index = configure.category_index(ROOT / "config" / version)
    for address in sorted(in_src):
        category = index.at(address) if index.ranges else ""
        if category and category != "game":
            out.append(f"0x{address:08X} in src/ is {category} code (categories.txt): only Ion Storm's game code "
                       f"is published (CONTRIBUTING.md)")
    return out


def without_data(report: dict) -> dict:
    """The report without data measures and without the data-only units."""
    def strip(measures: dict) -> dict:
        return {k: v for k, v in measures.items() if k not in DATA_MEASURES}

    out = dict(report, measures=strip(report.get("measures", {})))
    out["categories"] = [dict(c, measures=strip(c.get("measures", {}))) for c in report.get("categories", [])]
    out["units"] = [dict(u, measures=strip(u.get("measures", {}))) for u in report.get("units", [])
                    if u.get("name") not in EXTRA_UNITS]
    return out


def load(path: Path) -> dict:
    if not path.is_file():
        sys.exit(f"{path.relative_to(ROOT)} is missing: run python tools/progress_report.py write")
    return json.loads(path.read_text(encoding="utf-8"))


def headline(report: dict) -> str:
    """The headline category's progress: Ion Storm's game code."""
    category = next((c for c in report.get("categories", []) if c.get("id") == "main"), None)
    m = category.get("measures", {}) if category else report["measures"]
    name = category.get("name", "main") if category else "all"
    return (f"{name}: {m.get('matched_functions', 0)}/{m.get('total_functions', 0)} functions, "
            f"{float(m.get('matched_code_percent', 0.0)):.3f}% of the code "
            f"({m.get('matched_code', '0')}/{m.get('total_code', '0')} bytes)")


def dumps(report: dict) -> str:
    """The report as JSON with one line per function and per unit header, so a
    new match is a small diff (indenting every key would take 330k lines)."""
    compact = {"separators": (",", ":")}
    units = []
    for unit in report.get("units", []):
        head = {k: v for k, v in unit.items() if k != "functions"}
        text = json.dumps(head, **compact)
        if "functions" in unit:
            lines = ",\n".join("  " + json.dumps(f, **compact) for f in unit["functions"])
            text = text[:-1] + ',"functions":[\n' + lines + "\n ]}"
        units.append(" " + text)
    rest = {k: v for k, v in report.items() if k != "units"}
    return json.dumps(rest, **compact)[:-1] + ',"units":[\n' + ",\n".join(units) + "\n]}\n"


def write(version: str) -> None:
    built = ROOT / "build" / version / "report.json"
    local = Path(sys.executable).parent / f"ninja{'.exe' if os.name == 'nt' else ''}"
    ninja = str(local) if local.is_file() else shutil.which("ninja")
    if ninja is None:
        sys.exit("ninja not found: install requirements.txt, or run ninja yourself first")
    if subprocess.run([ninja, str(built.relative_to(ROOT))], cwd=ROOT).returncode != 0:
        sys.exit("the build failed: fix it before writing the report")

    report = without_data(load(built))
    found = problems(report, version)
    if found:
        print("\n".join(found))
        sys.exit("the build's report does not describe the tree (see above): run python configure.py, then again")
    target = report_path(version)
    target.parent.mkdir(parents=True, exist_ok=True)
    target.write_text(dumps(report), encoding="utf-8", newline="\n")
    print(f"wrote {target.relative_to(ROOT)}: {headline(report)}; commit it with the source")


def check(version: str) -> None:
    report = load(report_path(version))
    found = problems(report, version)
    if found:
        print(f"{report_path(version).relative_to(ROOT)} is out of date:")
        print("\n".join(f"  {p}" for p in found))
        sys.exit("regenerate it on a machine with the exe: python tools/progress_report.py write")
    print(f"report is current: {headline(report)}")


def summary(version: str) -> None:
    report = load(report_path(version))
    print(f"| Progress ({version}) | Code | Functions |")
    print("|---|---|---|")
    rows = [("All", report["measures"])] + [(c["name"], c.get("measures", {})) for c in report.get("categories", [])]
    for name, m in rows:
        print(f"| {name} | {float(m.get('matched_code_percent', 0.0)):.3f}% ({m.get('matched_code', '0')} of "
              f"{m.get('total_code', '0')} bytes) | {m.get('matched_functions', 0)} of {m.get('total_functions', 0)} |")


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("command", choices=["write", "check", "summary"])
    parser.add_argument("--version", default=configure.DEFAULT_VERSION, choices=sorted(configure.VERSIONS))
    args = parser.parse_args()
    {"write": write, "check": check, "summary": summary}[args.command](args.version)


if __name__ == "__main__":
    main()
