#!/usr/bin/env python3
"""Print progress from an objdiff report (objdiff-cli report generate)."""

import argparse
import json
from pathlib import Path


def num(measures: dict, key: str) -> float:
    return float(measures.get(key, 0) or 0)  # u64 fields are JSON strings


def line(label: str, m: dict) -> str:
    """One report line from an objdiff "measures" object (overall or one category). No data:
    nothing is split into units yet (tools/progress_report.py)."""
    code = num(m, "matched_code_percent")
    return (
        f"{label:<14} code {code:6.2f}% ({int(num(m, 'matched_code'))}/{int(num(m, 'total_code'))} bytes)  "
        f"functions {int(num(m, 'matched_functions'))}/{int(num(m, 'total_functions'))}"
    )


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("report", type=Path)
    args = parser.parse_args()
    report = json.loads(args.report.read_text(encoding="utf-8"))
    print(line("All", report.get("measures", {})))
    for cat in report.get("categories", []):
        # Skip categories with nothing assigned to them yet.
        if num(cat.get("measures", {}), "total_code"):
            print(line(cat.get("name", cat.get("id", "?")), cat.get("measures", {})))


if __name__ == "__main__":
    main()
