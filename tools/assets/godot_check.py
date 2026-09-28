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
  godot_check.py --editor-selftest [DIR]
      tests the map editor plugin without game files: writes a synthetic level
      (hand-made actors, a generated cube) into a project at DIR (default
      build/assets/editor_selftest), imports it, runs the plugin's model test
      (addons/t3_map_editor/selftest.gd: rotator round trip, edits, save,
      load), checks the edits file it wrote, then opens the level in the
      headless editor and drives the dock (select, edit, save, undo).
      Afterwards --project DIR --viewer and --project DIR also work on it.
"""

from __future__ import annotations

import argparse
import hashlib
import json
import os
import shutil
import subprocess
import sys
from pathlib import Path
from typing import Any, Dict, List, Tuple

sys.path.insert(0, str(Path(__file__).resolve().parent))
from gltf import GLTFBuilder  # noqa: E402
from t3common import BUILD_DIR, run_cli  # noqa: E402
from t3map import ActorRecord, ensure_project, update_index, write_tscn  # noqa: E402
from t3mesh import DEFAULT_SCALE  # noqa: E402
from t3pack import EDITS_VERSION  # noqa: E402

EDIT_TEST_LEVEL = "T3EditTest"


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


# --- map editor self-test ----------------------------------------------------------------

def cube_glb(path: Path, size: float) -> None:
    """A cube of edge `size` metres centred on its origin, in Godot space."""
    b = GLTFBuilder()
    h = size / 2.0
    pos: List[Tuple[float, float, float]] = []
    nrm: List[Tuple[float, float, float]] = []
    idx: List[int] = []
    # (normal, u, v) with u x v = normal, so each face winds counter-clockwise seen from outside
    for n, u, v in (((1, 0, 0), (0, 1, 0), (0, 0, 1)), ((-1, 0, 0), (0, 0, 1), (0, 1, 0)),
                    ((0, 1, 0), (0, 0, 1), (1, 0, 0)), ((0, -1, 0), (1, 0, 0), (0, 0, 1)),
                    ((0, 0, 1), (1, 0, 0), (0, 1, 0)), ((0, 0, -1), (0, 1, 0), (1, 0, 0))):
        base = len(pos)
        for su, sv in ((-1, -1), (1, -1), (1, 1), (-1, 1)):
            pos.append(tuple(h * (n[i] + su * u[i] + sv * v[i]) for i in range(3)))
            nrm.append(n)
        idx += [base, base + 1, base + 2, base, base + 2, base + 3]
    # extras as t3mesh.py writes them (the viewer's inspector reads them)
    mat = b.material("TestCube_Mat", base_color=(0.62, 0.5, 0.36, 1.0),
                     extras={"t3_material": "TestCube_Mat", "stages": ["", "", ""], "category": ""})
    prim = {"attributes": {"POSITION": b.add_floats(pos, "VEC3", with_bounds=True),
                           "NORMAL": b.add_floats(nrm, "VEC3")},
            "indices": b.add_indices(idx), "material": mat}
    extras = {"t3_mesh": "TestCube", "t3_skin": "Default", "t3_skins": ["Default"]}
    b.node("TestCube", mesh=b.mesh("TestCube", [prim], extras), extras=extras, root=True)
    b.write_glb(path)


def edit_fixture_actors() -> List[ActorRecord]:
    """Hand-made actors covering what the editor test needs: every scalar
    gamesys type, rotations at and near pitch +-90 and outside the canonical
    range, a draw scale, lights and markers.  All names and values are made up."""
    types = {"Brightness": "float", "Health": "int", "bActive": "bool", "Mode": "byte:ETestMode",
             "Channel": "byte", "Target": "name", "Message": "string", "Offsets": "array",
             "Flags": "bitfield:ETestFlags", "DrawScale": "float", "Owner": "object"}
    props = {"Brightness": 1.2345000505447388, "Health": 100, "bActive": 1, "Mode": "MODE_B", "Channel": 3,
             "Target": "Door1", "Message": "hello", "Offsets": [1, 2], "Flags": ["FLAG_Y"], "DrawScale": 1.0,
             "Owner": {"ref": 5, "name": "TestPackage.Owner0"}}
    light = {"flesh_type": "LT_Test", "kind": "omni", "hue": 0, "saturation": 255, "brightness": 64,
             "radius": 12.0, "inner_radius": None, "cone": None, "color": [1.0, 0.9, 0.7], "energy": 0.8,
             "on": True}

    def point(name: str, loc: Tuple[float, float, float], rot: Tuple[int, int, int], scale: float = 1.0,
              cls: str = "TestPoint") -> ActorRecord:
        return ActorRecord(name, cls, base=cls, location=loc, rotation=rot, draw_scale=scale)

    return [
        ActorRecord("LevelInfo0", "LevelInfo", base="LevelInfo", properties={"AmbientBrightness": 40}),
        ActorRecord("StaticMeshActor0", "StaticMeshActor", base="StaticMeshActor", location=(100.5, -250.25, 32.0),
                    rotation=(0, 16384, 0), mesh="TestCube", skin="Default", tag="Crate", gamesys=dict(props),
                    gamesys_types=dict(types)),
        ActorRecord("StaticMeshActor1", "StaticMeshActor", base="StaticMeshActor",
                    location=(1234.5677490234375, -987.654296875, 0.0009765625), mesh="TestCube", skin="Default"),
        ActorRecord("D_100_0", "D_100", archetype="Test lamp", base="Light", location=(0.0, 0.0, 128.0),
                    rotation=(0, -8192, 0), mesh="TestCube", skin="Default", light=dict(light),
                    gamesys={"bLightOn": 1, "Mode": 7}, gamesys_types={"bLightOn": "bool", "Mode": "byte:ETestMode"}),
        ActorRecord("Light0", "Light", base="Light", location=(256.0, 256.0, 192.0), rotation=(-16384, 0, 0),
                    light={**light, "kind": "spot", "cone": 30.0}),
        ActorRecord("PlayerStart0", "PlayerStart", base="PlayerStart", location=(0.0, -128.0, 48.0),
                    rotation=(0, 16384, 0), gamesys={"TeleportDestName": "start"},
                    gamesys_types={"TeleportDestName": "name"}),
        point("Gimbal_Up", (-64.0, 32.0, 16.0), (16384, 5000, 1200)),
        point("Gimbal_Down", (-96.0, 32.0, 16.0), (-16384, -3000, 700)),
        point("Near_Gimbal", (-128.0, 32.0, 16.0), (16383, 12345, -2222)),
        point("Wound", (-160.0, 32.0, 16.0), (40000, 70000, -100)),
        point("Yawed", (-192.0, 32.0, 16.0), (0, 1000, 0)),
        point("Scaled", (-224.0, 32.0, 16.0), (1000, 2000, 3000), 2.5),
        point("Far", (30000.0, -29999.5, 4000.25), (0, 0, 0)),
    ]


def build_edit_fixture(project: Path) -> str:
    """Writes the synthetic level into `project` (a Godot project made by
    ensure_project()) with the exporter's own writers; returns its scene path."""
    ensure_project(project)
    level = EDIT_TEST_LEVEL
    out = project / level
    if out.is_dir():
        shutil.rmtree(out)
    (out / "meshes").mkdir(parents=True)
    cube_glb(out / "meshes" / "TestCube.glb", 64 * DEFAULT_SCALE)
    actors = edit_fixture_actors()
    enums = {"ETestMode": ["MODE_A", "MODE_B", "", "MODE_D"], "ETestFlags": ["FLAG_X", "FLAG_Y"],
             "EUnusedEnum": ["UNUSED"]}
    blob = b"synthetic T3EditTest map, not game data"
    source = {"file": f"{level}.gmp", "size": len(blob), "sha1": hashlib.sha1(blob).hexdigest()}
    write_tscn(out / f"{level}.tscn", level, actors, {("TestCube", "Default"): "TestCube.glb"}, DEFAULT_SCALE,
               None, "PlayerStart0", "Editor self-test", enums, source)
    doc = {"level": level, "source": source["file"], "source_size": source["size"], "source_sha1": source["sha1"],
           "units": "unreal (Z up)", "actor_count": len(actors), "actors": [vars(a) for a in actors], "links": []}
    (out / f"{level}.actors.json").write_text(json.dumps(doc, indent=1), encoding="utf-8")
    update_index(project, {"id": level, "title": "Editor self-test", "scene": f"res://{level}/{level}.tscn",
                           "actors": len(actors), "meshes": 1, "lights": sum(1 for a in actors if a.light),
                           "units_per_meter": round(1.0 / DEFAULT_SCALE, 4), "default_start": "PlayerStart0",
                           "source": source})
    return f"res://{level}/{level}.tscn"


def check_edits_file(path: Path) -> List[str]:
    """Checks the edits file the model test saved, with Python's json (value
    types included: rotations must be ints, locations floats)."""
    problems: List[str] = []
    try:
        doc: Dict[str, Any] = json.loads(path.read_text(encoding="utf-8"))
    except (OSError, ValueError) as ex:
        return [f"cannot read {path.name}: {ex}"]

    def expect(what: str, got: Any, want: Any) -> None:
        if got != want or type(got) is not type(want) or (
                isinstance(got, list) and [type(x) for x in got] != [type(x) for x in want]):
            problems.append(f"{what}: {got!r}, expected {want!r}")

    expect("format", doc.get("format"), "t3-map-edits")
    expect("version", doc.get("version"), EDITS_VERSION)
    expect("level", doc.get("level"), EDIT_TEST_LEVEL)
    expect("source keys", sorted(doc.get("source", {})), ["file", "sha1", "size"])
    expect("source size", doc.get("source", {}).get("size"), len(b"synthetic T3EditTest map, not game data"))
    actors = doc.get("actors", {})
    crate = actors.get("StaticMeshActor0", {})
    expect("moved location", crate.get("location"), [152.99, -250.25, 32.0])
    expect("gamesys", crate.get("gamesys"), {"Brightness": 2.5, "Health": 7, "bActive": False, "Mode": "MODE_D",
                                            "Channel": 9, "Target": "Door2", "Message": 'say "hi"'})
    expect("rotation", actors.get("Yawed", {}).get("rotation"), [0, -15384, 0])
    expect("draw scale", actors.get("Scaled", {}).get("draw_scale"), 5.0)
    expect("gimbal rotation", actors.get("Gimbal_Up", {}).get("rotation"), [16384, 5000, 17584])
    for name in ("LevelInfo0", "StaticMeshActor1", "Near_Gimbal", "Far"):
        if name in actors:
            problems.append(f"{name} is in the file but was not changed")
    return problems


def editor_selftest(exe: str, project: Path, timeout: int) -> int:
    scene = build_edit_fixture(project)
    print(f"synthetic level {scene} in {project}")
    failed = import_project(exe, project, timeout)

    edits = project / EDIT_TEST_LEVEL / f"{EDIT_TEST_LEVEL}.edits.json"
    edits.unlink(missing_ok=True)
    r = run([exe, "--headless", "--path", str(project), "--script", "res://addons/t3_map_editor/selftest.gd",
             "--", scene], timeout)
    out = r.stdout + r.stderr
    for ln in out.splitlines():
        if ln.startswith(("  ok", "  FAIL", "SELFTEST", "T3 ", "  time")):
            print(ln)
    problems = problem_lines(out)
    for ln in problems[:20]:
        print("  " + ln)
    failed |= 1 if (r.returncode or problems) else 0

    file_problems = check_edits_file(edits)
    for p in file_problems:
        print("  FAIL  edits file " + p)
    if not file_problems:
        print(f"  ok    {edits.name} checked with Python's json (values and types)")
    failed |= 1 if file_problems else 0

    r = run([exe, "--headless", "--editor", "--path", str(project), "--", "--t3-editor-selftest", scene], timeout)
    out = r.stdout + r.stderr
    for ln in out.splitlines():
        if ln.startswith(("  ok", "  FAIL", "EDITOR SELFTEST", "T3 ")):
            print(ln)
    # "T3 edits:" lines are the plugin's own messages to the user (the test enters a bad value on purpose)
    problems = [ln for ln in problem_lines(out) if "T3 edits:" not in ln]
    for ln in problems[:20]:
        print("  " + ln)
    if "EDITOR SELFTEST PASSED" not in out:
        failed = 1
    failed |= 1 if (r.returncode or problems) else 0
    print("editor self-test " + ("FAILED" if failed else "passed"))
    return failed


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
    ap.add_argument("--editor-selftest", nargs="?", const="", metavar="DIR",
                    help="test the map editor plugin on a synthetic level (no game files needed)")
    ap.add_argument("--no-import", action="store_true", help="skip the headless import step")
    ap.add_argument("--timeout", type=int, default=1800)
    ap.add_argument("scenes", nargs="*")
    args = ap.parse_args(argv)
    exe = godot_exe(args.godot)
    if args.editor_selftest is not None:
        sys.exit(editor_selftest(exe, Path(args.editor_selftest or BUILD_DIR / "editor_selftest").resolve(),
                                 args.timeout))
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
