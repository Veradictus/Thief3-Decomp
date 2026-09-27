#!/usr/bin/env python3
"""Survey a Thief: Deadly Shadows install: file types, counts, sizes, magic numbers.

Reads the game folder (read-only) and prints, per folder and extension, the
file count, total size and the detected container format.  Paths are printed
relative to the game folder.  --json writes the full per-file listing under
build/assets/.

Usage:
  inventory.py [--game-dir DIR] [--json build/assets/inventory.json]
"""

from __future__ import annotations

import argparse
import json
import struct
import sys
from collections import defaultdict
from pathlib import Path
from typing import Dict, Tuple

sys.path.insert(0, str(Path(__file__).resolve().parent))
from t3common import game_dir, run_cli  # noqa: E402


def classify(head: bytes, size: int) -> Tuple[str, Dict[str, object]]:
    """Container format from the first bytes of a file."""
    info: Dict[str, object] = {}
    if len(head) >= 8 and struct.unpack_from("<I", head)[0] == 0x9E2A83C1:
        ver, lic = struct.unpack_from("<HH", head, 4)
        info.update(version=ver, licensee=lic)
        return "unreal-package", info
    if len(head) >= 8 and struct.unpack_from("<I", head)[0] == 0xC0000001:
        info["alignment"] = struct.unpack_from("<I", head, 4)[0]
        return "ion-ibt", info
    if head[:4] == b"DDS ":
        if len(head) >= 88:
            h, w = struct.unpack_from("<II", head, 12)
            info.update(width=w, height=h, fourcc=head[84:88].decode("latin-1"))
        return "dds", info
    if head[:3] in (b"BIK", b"KB2"):
        return "bink", info
    if head[:4] == b"0FFE":  # Ion chunk file: '0FFE' + 4-char tag reversed ('INF0', 'SM05', ...)
        info["chunk"] = head[4:8][::-1].decode("latin-1")
        return "ion-chunk", info
    if head[:2] == b"MZ":
        return "pe", info
    if head[:4] == b"RIFF":
        return "riff", info
    if head and all(b in (9, 10, 13) or 32 <= b < 127 for b in head[:64]):
        return "text", info
    return "binary", info


def main() -> None:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--game-dir")
    ap.add_argument("--json", help="write the per-file listing here (under build/assets/)")
    args = ap.parse_args()
    game = game_dir(args.game_dir)
    groups: Dict[Tuple[str, str], Dict[str, object]] = defaultdict(lambda: {"count": 0, "bytes": 0, "formats": {}})
    files = []
    for path in sorted(game.rglob("*")):
        if not path.is_file():
            continue
        rel = path.relative_to(game)
        folder = str(rel.parent).replace("\\", "/")
        if folder.count("/") > 2:
            folder = "/".join(folder.split("/")[:3])
        ext = path.suffix.lower() or "(none)"
        size = path.stat().st_size
        with open(path, "rb") as f:
            head = f.read(128)
        fmt, info = classify(head, size)
        g = groups[(folder, ext)]
        g["count"] += 1
        g["bytes"] += size
        key = fmt + (f" v{info['version']}/{info['licensee']}" if fmt == "unreal-package" else
                     f" {info['chunk']}" if fmt == "ion-chunk" else "")
        g["formats"][key] = g["formats"].get(key, 0) + 1
        files.append({"path": str(rel).replace("\\", "/"), "size": size, "format": fmt, **info})

    print(f"{'folder':34s} {'ext':8s} {'files':>6s} {'MB':>9s}  formats")
    for (folder, ext), g in sorted(groups.items()):
        fmts = ", ".join(f"{k} x{v}" for k, v in sorted(g["formats"].items(), key=lambda kv: -kv[1]))
        print(f"{folder:34s} {ext:8s} {g['count']:6d} {g['bytes'] / 1e6:9.2f}  {fmts}")
    total = sum(f["size"] for f in files)
    print(f"\n{len(files)} files, {total / 1e6:.1f} MB")
    if args.json:
        out = Path(args.json)
        out.parent.mkdir(parents=True, exist_ok=True)
        out.write_text(json.dumps(files, indent=1), encoding="utf-8")
        print(f"wrote {out}")


if __name__ == "__main__":
    run_cli(main)
