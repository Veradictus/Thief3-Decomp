#!/usr/bin/env python3
"""Write a progress report with nothing matched, without the game's exe.

    python tools/baseline_report.py [--version PC_20040610] [-o build/<version>/report.json]

The report has the objdiff format (version 2) and the same units and progress
categories as the real one from configure.py + ninja, with every function from
symbols.txt counted as unmatched. CI publishes it while no build image with
T3Main.exe is set up (docs/decomp-dev.md), so decomp.dev has a report to
register the project with. It never claims a match: progress shows only once
the real build, which compiles src/ against the split exe, takes over.
Standard library only.
"""

import argparse
import bisect
import json
import sys
from pathlib import Path
from typing import Dict, List

ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT))

import configure  # noqa: E402


def measures(code: int, functions: int, units: int) -> Dict[str, object]:
    """An objdiff Measures object with nothing matched. As in objdiff, u64 fields
    are strings and zero fields are left out. Data is not measured without the
    exe; objdiff would call no data 100% matched, so the data percentages are
    left at 0 instead."""
    m: Dict[str, object] = {}
    if code:
        m["total_code"] = str(code)
    if functions:
        m["total_functions"] = functions
    if units:
        m["total_units"] = units
    return m


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("--version", default=configure.DEFAULT_VERSION, choices=sorted(configure.VERSIONS))
    parser.add_argument("-o", "--output", type=Path)
    args = parser.parse_args()

    config_dir = ROOT / "config" / args.version
    output = args.output or ROOT / "build" / args.version / "report.json"
    functions = sorted((s for s in configure.symbolslib.load(config_dir / "symbols.txt")
                        if s.is_function and s.size > 0), key=lambda s: s.address)
    starts = [f.address for f in functions]
    options = configure.unit_options(config_dir)

    units: List[dict] = []
    totals = {cat: [0, 0, 0] for cat in configure.CATEGORIES}  # code, functions, units
    code_all = functions_all = 0
    for unit in configure.plan_units(config_dir):
        items = []
        for start, end in unit.text:
            for f in functions[bisect.bisect_left(starts, start):bisect.bisect_left(starts, end)]:
                items.append({"name": f.name, "size": str(f.size), "metadata": {}})
        code = sum(int(i["size"]) for i in items)
        categories = configure.unit_categories(unit, options.get(unit.source, {}).get("category", ""))
        metadata: Dict[str, object] = {"progress_categories": categories, "auto_generated": unit.auto}
        source = ROOT / "src" / unit.source
        if not unit.auto and source.is_file():
            metadata["source_path"] = f"src/{unit.source}"
        units.append({
            "name": unit.name,
            "measures": measures(code, len(items), 1),
            "sections": [{"name": ".text", "size": str(sum(end - start for start, end in unit.text)), "metadata": {}}],
            "functions": items,
            "metadata": metadata,
        })
        code_all += code
        functions_all += len(items)
        for cat in categories:
            t = totals[cat]
            t[0] += code
            t[1] += len(items)
            t[2] += 1

    report = {
        "measures": measures(code_all, functions_all, len(units)),
        "units": units,
        "version": 2,
        "categories": [{"id": cat, "name": name, "measures": measures(*totals[cat])}
                       for cat, name in configure.CATEGORIES.items()],
    }
    output.parent.mkdir(parents=True, exist_ok=True)
    output.write_text(json.dumps(report, separators=(",", ":")) + "\n", encoding="utf-8")
    main_code, main_functions, _ = totals["main"]
    print(f"{output}: baseline, nothing matched; {functions_all} functions, {code_all} bytes of code "
          f"({main_functions} functions, {main_code} bytes in main)")


if __name__ == "__main__":
    main()
