#!/usr/bin/env python3
"""Import and check the exported Godot project with a local Godot 4.7 binary.

The Godot executable comes from --godot or $GODOT (never hard-coded).

Usage:
  godot_check.py [--godot EXE] [--project build/assets/godot] [scene ...]
      imports the project headlessly, then loads every scene (default: all
      <Level>/<Level>.tscn) with t3_tools/check_scene.gd and reports counts.
  godot_check.py --viewer [MAP]
      imports, then runs the map viewer's self-test headlessly: the picker
      lists the maps, MAP (default: the first) loads in the background, the
      camera moves, view modes and toggles respond, the inspector shows an
      actor, and Esc returns to the picker.
  godot_check.py --viewer-shot OUT.png [--map MAP] [--size 1600x900] [-- viewer options]
      runs the viewer in a window (needs a GPU) and saves one frame: the
      picker, or MAP with the viewer UI.  Extra viewer options after "--",
      e.g. -- --t3-select --t3-help --t3-camera x y z tx ty tz
  godot_check.py --render res://Inn/Inn.tscn out.png [cx cy cz tx ty tz]
      renders one frame of a scene with t3_tools/render_scene.gd (opens a window).
"""

from __future__ import annotations

import argparse
import os
import subprocess
import sys
from pathlib import Path
from typing import List

sys.path.insert(0, str(Path(__file__).resolve().parent))
from t3common import BUILD_DIR, run_cli  # noqa: E402
from t3map import ensure_project  # noqa: E402


def godot_exe(explicit: str | None) -> str:
    exe = explicit or os.environ.get("GODOT")
    if not exe:
        sys.exit("pass --godot <path to Godot 4.7 executable> or set GODOT")
    if not Path(exe).is_file():
        sys.exit(f"Godot executable not found: {exe}")
    return exe


def run(cmd: List[str], timeout: int) -> subprocess.CompletedProcess:
    print("+", " ".join(cmd[:1] + [c if " " not in c else f'"{c}"' for c in cmd[1:]]), flush=True)
    return subprocess.run(cmd, capture_output=True, text=True, encoding="utf-8", errors="replace", timeout=timeout)


def problem_lines(text: str) -> List[str]:
    return [ln.strip() for ln in text.splitlines()
            if ln.startswith(("ERROR", "SCRIPT ERROR", "WARNING")) or "Parse Error" in ln]


def import_project(exe: str, project: Path, timeout: int) -> int:
    r = run([exe, "--headless", "--path", str(project), "--import"], timeout)
    errors = [ln for ln in (r.stdout + r.stderr).splitlines() if "ERROR" in ln]
    print(f"import finished (exit {r.returncode}), {len(errors)} error lines")
    for ln in errors[:20]:
        print("  " + ln.strip())
    return 1 if (r.returncode or errors) else 0


def main() -> None:
    argv = sys.argv[1:]
    extra: List[str] = []
    if "--" in argv:
        i = argv.index("--")
        argv, extra = argv[:i], argv[i + 1:]
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--godot", help="Godot 4.7 executable (default: $GODOT)")
    ap.add_argument("--project", default=str(BUILD_DIR / "godot"))
    ap.add_argument("--render", nargs="+", metavar="ARG", help="scene out.png [camera and target]")
    ap.add_argument("--viewer", nargs="?", const="", metavar="MAP", help="run the viewer self-test")
    ap.add_argument("--viewer-shot", metavar="PNG", help="save a frame of the viewer or the picker")
    ap.add_argument("--map", default="", help="map id for --viewer-shot")
    ap.add_argument("--size", default="1600x900", help="window size for --viewer-shot")
    ap.add_argument("--no-import", action="store_true", help="skip the headless import step")
    ap.add_argument("--timeout", type=int, default=1800)
    ap.add_argument("scenes", nargs="*")
    args = ap.parse_args(argv)
    exe = godot_exe(args.godot)
    project = Path(args.project).resolve()
    ensure_project(project)

    if args.render:
        r = run([exe, "--path", str(project), "--resolution", "1280x720", "--script",
                 "res://t3_tools/render_scene.gd", "--", *args.render], args.timeout)
        print(r.stdout[-2000:])
        sys.exit(r.returncode)

    if args.viewer_shot:
        user = ["--t3-screenshot", str(Path(args.viewer_shot).resolve()).replace("\\", "/")]
        if args.map:
            user += ["--t3-map", args.map]
        r = run([exe, "--path", str(project), "--resolution", args.size, "--", *user, *extra], args.timeout)
        for ln in (r.stdout + r.stderr).splitlines():
            if ln.startswith("screenshot") or ln.startswith(("ERROR", "SCRIPT ERROR")):
                print(ln)
        sys.exit(r.returncode)

    failed = 0 if args.no_import else import_project(exe, project, args.timeout)

    if args.viewer is not None:
        user = ["--t3-selftest"] + (["--t3-map", args.viewer] if args.viewer else [])
        r = run([exe, "--headless", "--path", str(project), "--", *user], args.timeout)
        out = r.stdout + r.stderr
        for ln in out.splitlines():
            if ln.startswith(("  ok", "  FAIL", "  map:", "SELFTEST", "T3 viewer")):
                print(ln)
        problems = problem_lines(out)
        for ln in problems[:20]:
            print("  " + ln)
        sys.exit(r.returncode or failed or (1 if problems else 0))

    scenes = args.scenes or [f"res://{p.parent.name}/{p.name}" for p in sorted(project.glob("*/*.tscn"))]
    if not scenes:
        sys.exit("no scenes found; run t3map.py first")
    r = run([exe, "--headless", "--path", str(project), "--script", "res://t3_tools/check_scene.gd", "--",
             *scenes], args.timeout)
    for ln in (r.stdout + r.stderr).splitlines():
        if ln.startswith(("OK", "FAIL", "   AABB")) or "ERROR" in ln:
            print(ln)
    sys.exit(r.returncode or failed)


if __name__ == "__main__":
    run_cli(main)
