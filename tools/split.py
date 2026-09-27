#!/usr/bin/env python3
"""Run `delink ida-split` into a clean directory, keep its log, write a stamp."""

import argparse
import re
import shutil
import subprocess
import sys
from pathlib import Path


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--delink", type=Path, required=True)
    parser.add_argument("--model", type=Path, required=True)
    parser.add_argument("--exe", type=Path, required=True)
    parser.add_argument("--groups", type=Path, required=True)
    parser.add_argument("--outdir", type=Path, required=True)
    parser.add_argument("--stamp", type=Path, required=True)
    args = parser.parse_args()

    shutil.rmtree(args.outdir, ignore_errors=True)
    args.outdir.mkdir(parents=True)
    log = args.stamp.with_suffix(".log")
    cmd = [
        str(args.delink), "ida-split", str(args.model), str(args.exe),
        "--idapro", str(args.groups), "-o", str(args.outdir), "--coff",
    ]
    proc = subprocess.run(cmd, capture_output=True, text=True, encoding="utf-8", errors="replace")
    log.write_text(proc.stdout + proc.stderr, encoding="utf-8")
    summary = re.search(r"ida-split complete: (\d+) objects \((\d+) failed\)", proc.stdout)
    if proc.returncode != 0 or summary is None or summary.group(2) != "0":
        sys.stderr.write(proc.stdout[-4000:] + proc.stderr[-4000:])
        sys.exit(f"delink failed (exit {proc.returncode}); full log: {log}")
    print(summary.group(0))
    args.stamp.write_text(summary.group(0) + "\n", encoding="utf-8")


if __name__ == "__main__":
    main()
