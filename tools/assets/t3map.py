#!/usr/bin/env python3
"""Export a Thief: Deadly Shadows level to JSON and to a Godot 4 scene.

Reads Content/T3/Maps/<Level>.gmp (actors) and <Level>.ibt (+ Kernel_GFXALL.ibt)
(meshes, materials, textures), plus System/T3Gamesys.t3u (archetypes) and the
property table from the script packages.

Output (default build/assets/godot/, itself a Godot 4.7 project):

  project.godot                  created if missing
  t3_tools/check_scene.gd        headless load check
  <Level>/<Level>.actors.json    every actor: class, archetype, transform, mesh,
                                 light, instance gamesys properties, links
  <Level>/<Level>.tscn           Node3D scene: static meshes instanced from
                                 .glb files, OmniLight3D/SpotLight3D for lights,
                                 Marker3D for everything else; T3 data in node metadata
  <Level>/meshes/*.glb           one per (mesh, skin) pair used by the level
  <Level>/textures/*.png
  <Level>/meshes/<Level>_bsp.glb  BSP render blocks from the Level object (t3bsp.py)

Not exported yet: emitters, sounds, skeletal meshes, navigation data, zones
and portals, trigger scripts.  See docs/assets.md.

Usage:
  t3map.py Inn                       JSON + meshes + scene
  t3map.py --all                     every map
  t3map.py Inn --json-only           actor list only
  t3map.py Inn --scale 0.01905 -o DIR
"""

from __future__ import annotations

import argparse
import json
import math
import shutil
import sys
import time
import uuid
from dataclasses import dataclass, field
from pathlib import Path
from typing import Any, Dict, List, Optional, Tuple

sys.path.insert(0, str(Path(__file__).resolve().parent))
from ibt import IBT  # noqa: E402
from t3common import run_cli, BUILD_DIR, Reader, fmt_float, game_dir, godot_basis, resolve_map, u2g  # noqa: E402
from t3gamesys import Gamesys, blocks_to_dict, load_gamesys, mesh_of  # noqa: E402
from t3mesh import DEFAULT_SCALE, UNITS_PER_FOOT, ResourceSet, export_mesh, kernel_bundle, mesh_file_name  # noqa: E402
from t3props import PropertyNames, load_table  # noqa: E402
from t3texture import load_categories  # noqa: E402
from t3bsp import export_bsp  # noqa: E402
from upkg import RF_HasStack, GamesysBlock, Package, _jsonable, prop_value, struct_fields  # noqa: E402

TOOLS_DIR = Path(__file__).resolve().parent


def light_kind(enum_name: Optional[str]) -> str:
    """Map a Flesh light type enum name to a Godot light kind."""
    n = (enum_name or "").lower()
    for key, kind in (("spot", "spot"), ("direct", "directional"), ("project", "projector"),
                      ("ambient", "ambient")):
        if key in n:
            return kind
    return "omni"


class PropIds:
    """Gamesys property ids resolved by name from the script-derived table."""

    def __init__(self, names: PropertyNames) -> None:
        get = names.id_of
        self.draw_scale = get("DrawScale")
        self.tag = get("Tag")
        self.group = get("Group")
        self.trigger_scripts = get("TriggerScripts")
        self.light_color = get("LightColor")
        self.light_shape = get("LightShape")
        self.light_type = get("FleshLightType")
        self.light_on = get("bLightOn")


@dataclass
class ActorRecord:
    name: str
    cls: str
    archetype: str = ""
    base: str = ""
    location: Tuple[float, float, float] = (0.0, 0.0, 0.0)
    rotation: Tuple[int, int, int] = (0, 0, 0)  # pitch, yaw, roll
    draw_scale: float = 1.0
    mesh: Optional[str] = None
    skin: Optional[str] = None
    light: Optional[Dict[str, Any]] = None
    tag: Optional[str] = None
    group: Optional[str] = None
    properties: Dict[str, Any] = field(default_factory=dict)  # tagged properties (instance)
    gamesys: Dict[str, Any] = field(default_factory=dict)     # instance gamesys overrides
    links: List[str] = field(default_factory=list)
    attached_to: Optional[str] = None     # parent actor of an attachment link
    attached_bone: Optional[str] = None   # parent hardpoint/bone
    error: Optional[str] = None


def extract_links(pkg: Package) -> List[Dict[str, Any]]:
    """LinkDataObjects (attachments, trigger scripts, loadouts, ...): their
    properties, and source and destination objects, which are the two compact
    object references in the object's native tail."""
    out = []
    for e in pkg.exports:
        cls = pkg.export_class(e)
        if not cls.endswith("LinkDataObject") or e.serial_size == 0:
            continue
        a = pkg.read_actor(e)
        refs: List[int] = []
        r = Reader(a.tail)
        try:
            while not r.eof() and len(refs) < 2:
                refs.append(r.index())
        except EOFError:
            pass
        rec: Dict[str, Any] = {"name": e.name, "class": cls,
                               "properties": {q.name: _jsonable(q.value) for q in a.properties}}
        if len(refs) == 2:
            rec["source"] = pkg.ref_name(refs[0]) if refs[0] else None
            rec["dest"] = pkg.ref_name(refs[1]) if refs[1] else None
        out.append(rec)
    return out


def apply_attachments(actors: List[ActorRecord], links: List[Dict[str, Any]]) -> None:
    by_name = {a.name: a for a in actors}
    for ln in links:
        if "Attachment" not in ln["class"] or not ln.get("dest") or ln["dest"] not in by_name:
            continue
        child = by_name[ln["dest"]]
        child.attached_to = ln.get("source")
        bone = ln["properties"].get("m_parentBone")
        child.attached_bone = bone if isinstance(bone, str) else None


def hsv_to_rgb_unreal(hue: int, sat: int, bright: int) -> Tuple[float, float, float, float]:
    """UE2's FGetHSV: note that saturation 255 means *white* in Unreal."""
    b = bright * 1.4 / 255.0
    b *= 0.7 / (0.01 + math.sqrt(b)) if b > 0 else 0.0
    b = max(0.0, min(1.0, b))
    h = hue
    if h < 86:
        base = ((85 - h) / 85.0, h / 85.0, 0.0)
    elif h < 171:
        base = (0.0, (170 - h) / 85.0, (h - 85) / 85.0)
    else:
        base = ((h - 170) / 85.0, 0.0, (255 - h) / 84.0)
    s = sat / 255.0
    rgb = tuple((c + s * (1.0 - c)) for c in base)
    return rgb[0], rgb[1], rgb[2], b


def _block_value(blocks: Dict[int, GamesysBlock], pid: Optional[int], default: Any = None) -> Any:
    b = blocks.get(pid) if pid is not None else None
    return default if b is None else b.value


def extract_actors(pkg: Package, names: PropertyNames, gs: Gamesys) -> List[ActorRecord]:
    ids = PropIds(names)
    actors = []
    for e in pkg.exports:
        if not (e.flags & RF_HasStack):
            continue
        cls = pkg.export_class(e)
        a = pkg.read_actor(e)
        rec = ActorRecord(e.name, cls)
        if a.parse_error:
            rec.error = a.parse_error
        own = {b.prop_id: b for b in a.gamesys}
        if cls.upper().startswith("D_"):
            rec.archetype = gs.display(cls)
            rec.base = gs.engine_class(cls)
            merged = {**gs.resolved(cls), **own}
        else:
            rec.base = cls
            merged = own
        loc = struct_fields(prop_value(a.properties, "Location"))
        rec.location = (float(loc.get("X", 0.0)), float(loc.get("Y", 0.0)), float(loc.get("Z", 0.0)))
        rot = struct_fields(prop_value(a.properties, "Rotation"))
        rec.rotation = (int(rot.get("Pitch", 0)), int(rot.get("Yaw", 0)), int(rot.get("Roll", 0)))
        ds = _block_value(merged, ids.draw_scale)
        if ds is None:
            ds = prop_value(a.properties, "DrawScale", 1.0)
        rec.draw_scale = float(ds) if isinstance(ds, (int, float)) else 1.0
        m = mesh_of(merged, names)
        if m:
            rec.mesh, rec.skin = m["name"], m["skin"]
        tag = _block_value(merged, ids.tag)
        rec.tag = tag if isinstance(tag, str) else None
        grp = _block_value(merged, ids.group)
        rec.group = grp if isinstance(grp, str) else None
        # lights: anything with a Flesh light type or a LightColor
        ltype = _block_value(merged, ids.light_type)
        color = struct_fields(_block_value(merged, ids.light_color))
        if ltype is not None or color:
            shape = struct_fields(_block_value(merged, ids.light_shape))
            r, g, b, energy = hsv_to_rgb_unreal(int(color.get("LightHue", 0)), int(color.get("LightSaturation", 255)),
                                                int(color.get("LightBrightness", 64)))
            on = _block_value(merged, ids.light_on)
            ltname = names.enum_value(ids.light_type, ltype) if isinstance(ltype, int) and ids.light_type else None
            rec.light = {
                "flesh_type": ltname,
                "kind": light_kind(ltname),
                "hue": color.get("LightHue", 0), "saturation": color.get("LightSaturation", 255),
                "brightness": color.get("LightBrightness", 64),
                "radius": shape.get("LightRadius"), "inner_radius": shape.get("LightInnerRadius"),
                "cone": shape.get("LightCone"), "color": [r, g, b], "energy": energy,
                "on": None if on is None else bool(on),
            }
        rec.properties = {p.name: _jsonable(p.value) for p in a.properties
                          if p.name not in ("Location", "Rotation", "Level", "Region", "PhysicsVolume",
                                            "bSentSpawnNotification", "ColLocation")}
        rec.gamesys = blocks_to_dict(own, names)
        ts = own.get(ids.trigger_scripts) if ids.trigger_scripts is not None else None
        if ts is not None and isinstance(ts.value, dict) and ts.value.get("as") == "index":
            rec.gamesys["TriggerScripts"] = [pkg.names[i] if 0 <= i < len(pkg.names) else i
                                             for i in ts.value["items"]]
        rec.links = [pkg.ref_path(x) for x in a.links]
        actors.append(rec)
    return actors


# --- Godot scene -----------------------------------------------------------------------

def _tscn_str(s: str) -> str:
    return '"' + s.replace("\\", "\\\\").replace('"', '\\"').replace("\n", "\\n") + '"'


def _tscn_value(v: Any) -> str:
    if isinstance(v, bool):
        return "true" if v else "false"
    if isinstance(v, int):
        return str(v)
    if isinstance(v, float):
        return fmt_float(v) if math.isfinite(v) else "0"
    if isinstance(v, str):
        return _tscn_str(v)
    return _tscn_str(json.dumps(v, default=str))


def _node_name(name: str, used: Dict[str, int]) -> str:
    n = "".join(c if c.isalnum() or c in "_-" else "_" for c in name) or "Node"
    if n in used:
        used[n] += 1
        n = f"{n}_{used[n]}"
    else:
        used[n] = 0
    return n


def transform3d(rec: ActorRecord, scale: float, extra_scale: float = 1.0) -> str:
    s = rec.draw_scale * extra_scale
    cols = godot_basis(rec.rotation[0], rec.rotation[1], rec.rotation[2], (s, s, s))
    o = u2g(rec.location, scale)
    rows = [cols[j][i] for i in range(3) for j in range(3)]
    return "Transform3D(" + ", ".join(fmt_float(x) for x in rows + list(o)) + ")"


def level_environment(actors: List[ActorRecord]) -> Optional[Dict[str, Any]]:
    """Ambient light and distance fog from the LevelInfo actor's properties."""
    info = next((a for a in actors if a.cls == "LevelInfo"), None)
    if info is None:
        return None
    p = info.properties
    r, g, b, energy = hsv_to_rgb_unreal(int(p.get("AmbientHue", 0)), int(p.get("AmbientSaturation", 255)),
                                        int(p.get("AmbientBrightness", 0)))
    env: Dict[str, Any] = {"ambient_color": [r, g, b], "ambient_energy": energy}
    if p.get("bDistanceFog"):
        # properties are stored JSON-style: a struct is a list of {name, type, value}
        raw = p.get("DistanceFogColor")
        fc = {q["name"]: q["value"] for q in raw if isinstance(q, dict)} if isinstance(raw, list) else {}
        env["fog_color"] = [fc.get("R", 0) / 255.0, fc.get("G", 0) / 255.0, fc.get("B", 0) / 255.0]
        env["fog_start"] = float(p.get("DistanceFogStart", 0.0))
        env["fog_end"] = float(p.get("DistanceFogEnd", 0.0))
    return env


def write_tscn(path: Path, level: str, actors: List[ActorRecord], mesh_files: Dict[Tuple[str, str], str],
               scale: float, bsp_file: Optional[str] = None, default_start: Optional[str] = None,
               title: str = "") -> None:
    ext: Dict[str, str] = {}
    lines_nodes: List[str] = []
    used: Dict[str, int] = {}
    groups = {"StaticMeshes": [], "Lights": [], "Markers": [], "CharacterParts": []}
    pawns = {a.name for a in actors if "Pawn" in (a.base or "")}
    for rec in actors:
        key = (rec.mesh or "", rec.skin or "Default")
        if rec.attached_to in pawns and rec.mesh and key in mesh_files:
            # eyes, teeth, hair, armour... attached to NPC skeletons, which are
            # not exported yet: keep them, hidden, instead of floating in the air
            groups["CharacterParts"].append(rec)
        elif rec.mesh and key in mesh_files:
            groups["StaticMeshes"].append(rec)
        elif rec.light is not None:
            groups["Lights"].append(rec)
        else:
            groups["Markers"].append(rec)

    def meta(rec: ActorRecord) -> List[str]:
        out = [f"metadata/t3_name = {_tscn_str(rec.name)}", f"metadata/t3_class = {_tscn_str(rec.cls)}"]
        if rec.archetype:
            out.append(f"metadata/t3_archetype = {_tscn_str(rec.archetype)}")
        if rec.base and rec.base != rec.cls:
            out.append(f"metadata/t3_base = {_tscn_str(rec.base)}")
        if rec.mesh:
            out.append(f"metadata/t3_mesh = {_tscn_str(rec.mesh)}")
            out.append(f"metadata/t3_skin = {_tscn_str(rec.skin or 'Default')}")
        if rec.tag:
            out.append(f"metadata/t3_tag = {_tscn_str(rec.tag)}")
        if rec.attached_to:
            out.append(f"metadata/t3_attached_to = {_tscn_str(rec.attached_to)}")
            if rec.attached_bone:
                out.append(f"metadata/t3_attached_bone = {_tscn_str(rec.attached_bone)}")
        if rec.gamesys:
            out.append(f"metadata/t3_gamesys = {_tscn_str(json.dumps(rec.gamesys, default=str))}")
        if default_start and rec.name == default_start:
            out.append("metadata/t3_default_start = true")
        return out

    def light_lines(rec: ActorRecord, name: str, parent: str, with_transform: bool) -> List[str]:
        lt = rec.light or {}
        kind = lt.get("kind", "omni")
        gtype = {"spot": "SpotLight3D", "projector": "SpotLight3D", "directional": "DirectionalLight3D"}.get(
            kind, "OmniLight3D")
        out = [f'\n[node name="{name}" type="{gtype}" parent="{parent}"]']
        if with_transform:
            out.append(f"transform = {transform3d(rec, scale)}")
        r, g, b = lt.get("color", [1, 1, 1])
        out.append(f"light_color = Color({fmt_float(r)}, {fmt_float(g)}, {fmt_float(b)}, 1)")
        out.append(f"light_energy = {fmt_float(max(0.05, float(lt.get('energy', 1.0))))}")
        radius = lt.get("radius")
        if radius is not None and gtype != "DirectionalLight3D":
            # Unit of LightRadius not established; assume feet (16 Unreal units), see docs/assets.md.
            rng = max(0.1, float(radius) * UNITS_PER_FOOT * scale)
            out.append(f"{'omni_range' if gtype == 'OmniLight3D' else 'spot_range'} = {fmt_float(rng)}")
        if lt.get("on") is False:
            out.append("visible = false")
        out.append(f"metadata/t3_light = {_tscn_str(json.dumps(lt))}")
        return out

    for group, recs in groups.items():
        lines_nodes.append(f'\n[node name="{group}" type="Node3D" parent="."]')
        if group == "CharacterParts":
            lines_nodes.append("visible = false")
        lines_nodes.append("")
        gused: Dict[str, int] = {}
        for rec in recs:
            nn = _node_name(rec.name, gused)
            if group in ("StaticMeshes", "CharacterParts"):
                f = mesh_files[(rec.mesh or "", rec.skin or "Default")]
                if f not in ext:
                    ext[f] = f"{len(ext) + 1}_mesh"
                lines_nodes.append(f'\n[node name="{nn}" parent="{group}" instance=ExtResource("{ext[f]}")]')
                lines_nodes.append(f"transform = {transform3d(rec, scale)}")
                lines_nodes.extend(meta(rec))
                if rec.light is not None:  # lamps, candles: mesh plus light
                    lines_nodes.extend(light_lines(rec, "T3Light", f"{group}/{nn}", False))
                continue
            if group == "Lights":
                lines_nodes.extend(light_lines(rec, nn, group, True))
            else:
                lines_nodes.append(f'\n[node name="{nn}" type="Marker3D" parent="{group}"]')
                lines_nodes.append(f"transform = {transform3d(rec, scale)}")
            lines_nodes.extend(meta(rec))

    env = level_environment(actors)
    steps = len(ext) + 1 + (1 if bsp_file else 0) + (1 if env else 0)
    header = [f'[gd_scene load_steps={steps} format=3 uid="uid://{_uid(level)}"]\n']
    if bsp_file:
        header.append(f'[ext_resource type="PackedScene" path="res://{level}/meshes/{bsp_file}" id="0_bsp"]')
    for f, rid in ext.items():
        header.append(f'[ext_resource type="PackedScene" path="res://{level}/meshes/{f}" id="{rid}"]')
    if env:
        def col(c: List[float]) -> str:
            return f"Color({fmt_float(c[0])}, {fmt_float(c[1])}, {fmt_float(c[2])}, 1)"
        sub = ['\n[sub_resource type="Environment" id="Environment_t3"]',
               "background_mode = 1",
               f"background_color = {col(env.get('fog_color', [0, 0, 0]))}",
               "ambient_light_source = 2",
               f"ambient_light_color = {col(env['ambient_color'])}",
               f"ambient_light_energy = {fmt_float(max(env['ambient_energy'], 0.02))}"]
        if "fog_start" in env:
            sub += ["fog_enabled = true", "fog_mode = 1", f"fog_light_color = {col(env['fog_color'])}",
                    "fog_density = 1.0",
                    f"fog_depth_begin = {fmt_float(env['fog_start'] * scale)}",
                    f"fog_depth_end = {fmt_float(max(env['fog_end'], env['fog_start'] + 1) * scale)}"]
        header.extend(sub)
    body = [f'\n[node name="{_node_name(level, {})}" type="Node3D"]',
            f"metadata/t3_level = {_tscn_str(level)}",
            f"metadata/t3_title = {_tscn_str(title or level)}",
            f"metadata/t3_units_per_meter = {fmt_float(1.0 / scale)}"]
    if env:
        body += ['\n[node name="T3Environment" type="WorldEnvironment" parent="."]',
                 'environment = SubResource("Environment_t3")',
                 f"metadata/t3_environment = {_tscn_str(json.dumps(env))}"]
    if bsp_file:
        body.append('\n[node name="BSP" parent="." instance=ExtResource("0_bsp")]')
    path.write_text("\n".join(header) + "\n" + "\n".join(body) + "\n" + "\n".join(lines_nodes) + "\n",
                    encoding="utf-8")


def _uid(seed: str) -> str:
    # Godot uids are base-34-ish strings; any stable lowercase alnum works for text scenes.
    h = uuid.uuid5(uuid.NAMESPACE_URL, "t3-level:" + seed).hex
    alphabet = "abcdefghijklmnopqrstuvwxy0123456789"
    n = int(h, 16)
    out = ""
    while n and len(out) < 13:
        n, r = divmod(n, len(alphabet))
        out += alphabet[r]
    return out


# Godot key codes (engine constants) used by the viewer's input map.
_KEY = {"W": 87, "A": 65, "S": 83, "D": 68, "Q": 81, "E": 69, "C": 67, "I": 73, "F": 70, "P": 80, "V": 86,
        "L": 76, "K": 75, "M": 77, "H": 72, "1": 49, "2": 50, "3": 51, "SPACE": 32,
        "ESCAPE": 4194305, "LEFT": 4194319, "UP": 4194320, "RIGHT": 4194321, "DOWN": 4194322,
        "PAGEUP": 4194323, "PAGEDOWN": 4194324, "SHIFT": 4194325, "CTRL": 4194326, "ALT": 4194328,
        "F1": 4194332}
# Viewer input map; keep in sync with DEFAULT_ACTIONS in godot/viewer/viewer_state.gd.
# "phys" = physical key (layout independent), "key" = key label, "mouse" = button index.
VIEWER_ACTIONS = [
    ("t3_move_forward", [("phys", "W"), ("key", "UP")]),
    ("t3_move_back", [("phys", "S"), ("key", "DOWN")]),
    ("t3_move_left", [("phys", "A"), ("key", "LEFT")]),
    ("t3_move_right", [("phys", "D"), ("key", "RIGHT")]),
    ("t3_move_down", [("phys", "Q"), ("key", "CTRL"), ("key", "PAGEDOWN")]),
    ("t3_move_up", [("phys", "E"), ("key", "SPACE"), ("key", "PAGEUP")]),
    ("t3_fast", [("key", "SHIFT")]),
    ("t3_slow", [("key", "ALT")]),
    ("t3_look", [("mouse", 2)]),
    ("t3_select", [("mouse", 1)]),
    ("t3_toggle_capture", [("key", "C")]),
    ("t3_inspect", [("key", "I")]),
    ("t3_focus", [("key", "F")]),
    ("t3_next_start", [("key", "P")]),
    ("t3_view_lit", [("key", "1")]),
    ("t3_view_unlit", [("key", "2")]),
    ("t3_view_wireframe", [("key", "3")]),
    ("t3_view_cycle", [("key", "V")]),
    ("t3_toggle_lights", [("key", "L")]),
    ("t3_cycle_lighting", [("key", "K")]),
    ("t3_toggle_markers", [("key", "M")]),
    ("t3_help", [("key", "F1"), ("key", "H")]),
    ("t3_back", [("key", "ESCAPE")]),
]


def _input_event(kind: str, code) -> str:
    """Text encoding of one InputEventKey/InputEventMouseButton resource, the
    way Godot itself writes an action's events into project.godot's [input]."""
    common = ('"resource_local_to_scene":false,"resource_name":"","device":-1,"window_id":0,'
              '"alt_pressed":false,"shift_pressed":false,"ctrl_pressed":false,"meta_pressed":false,')
    if kind == "mouse":
        return (f'Object(InputEventMouseButton,{common}"button_mask":0,"position":Vector2(0, 0),'
                f'"global_position":Vector2(0, 0),"factor":1.0,"button_index":{code},"canceled":false,'
                f'"pressed":false,"double_click":false,"script":null)')
    keycode, physical = (0, _KEY[code]) if kind == "phys" else (_KEY[code], 0)
    return (f'Object(InputEventKey,{common}"pressed":false,"keycode":{keycode},"physical_keycode":{physical},'
            f'"key_label":0,"unicode":0,"location":0,"echo":false,"script":null)')


def project_godot_text() -> str:
    lines = [
        "; Engine configuration file.",
        "; Generated by tools/assets/t3map.py for the T3 map viewer; rewritten on every export.",
        "",
        "config_version=5",
        "",
        "[application]",
        "",
        'config/name="T3 Map Viewer"',
        'config/description="Viewer for Thief: Deadly Shadows maps exported by tools/assets/t3map.py"',
        'run/main_scene="res://t3_tools/viewer/map_picker.tscn"',
        'config/features=PackedStringArray("4.7", "Forward Plus")',
        "",
        "[autoload]",
        "",
        'T3Viewer="*res://t3_tools/viewer/viewer_state.gd"',
        "",
        "[display]",
        "",
        "window/size/viewport_width=1280",
        "window/size/viewport_height=720",
        "window/size/window_width_override=1600",
        "window/size/window_height_override=900",
        'window/stretch/mode="canvas_items"',
        'window/stretch/aspect="expand"',
        "",
        "[input]",
        "",
    ]
    for action, events in VIEWER_ACTIONS:
        lines.append(f"{action}={{")
        lines.append('"deadzone": 0.2,')
        lines.append('"events": [' + "\n, ".join(_input_event(k, c) for k, c in events) + "\n]")
        lines.append("}")
    lines += ["", "[rendering]", "", 'renderer/rendering_method="forward_plus"', ""]
    return "\n".join(lines)


def ensure_project(root: Path) -> None:
    """Make `root` a Godot 4.7 project running the map viewer: project.godot
    plus a copy of tools/assets/godot/ in res://t3_tools/."""
    root.mkdir(parents=True, exist_ok=True)
    (root / "project.godot").write_text(project_godot_text(), encoding="utf-8")
    shutil.copytree(TOOLS_DIR / "godot", root / "t3_tools", dirs_exist_ok=True)


# --- map index and titles ---------------------------------------------------------------

INDEX_NAME = "t3_maps.json"


def load_string_tags(game: Path, language: str = "english") -> Dict[str, str]:
    """Localised strings from Content/T3/Books/<Language>/String_Tags/*.sch:
    a key line, then one line per language: lang_<name> <date> <time> "text"."""
    out: Dict[str, str] = {}
    books = game / "Content" / "T3" / "Books"
    if not books.is_dir():
        return out
    lang_dir = next((d for d in books.iterdir() if d.is_dir() and d.name.lower() == language), None)
    if lang_dir is None:
        return out
    tags = next((d for d in lang_dir.iterdir() if d.is_dir() and d.name.lower() == "string_tags"), None)
    if tags is None:
        return out
    for f in sorted(tags.glob("*.sch")):
        key = None
        for line in f.read_text(encoding="latin-1").splitlines():
            t = line.strip()
            if not t:
                continue
            if not t.startswith("lang_"):
                key = t
            elif key and t.startswith("lang_" + language):
                a, b = t.find('"'), t.rfind('"')
                if 0 <= a < b:
                    out.setdefault(key, t[a + 1:b])
    return out


def level_title(actors: List[ActorRecord], strings: Dict[str, str], fallback: str) -> str:
    info = next((a for a in actors if a.cls == "LevelInfo"), None)
    if info is not None:
        key = info.properties.get("LevelEnterText")
        if isinstance(key, str) and strings.get(key):
            return strings[key]
        for prop in ("CitySectionName", "Title"):
            v = info.properties.get(prop)
            if isinstance(v, str) and v.strip() and v.strip().lower() != fallback.lower():
                return v.strip()
    return fallback


def default_player_start(actors: List[ActorRecord]) -> Optional[str]:
    """The player start to open a map at: one whose travel destination name
    mentions "start", else one without a destination name, else the first."""
    starts = [a for a in actors if a.cls == "PlayerStart"]
    if not starts:
        return None

    def rank(a: ActorRecord) -> int:
        dest = str(a.gamesys.get("TeleportDestName") or "")
        return 0 if "start" in dest.lower() else 1 if not dest else 2
    return min(enumerate(starts), key=lambda ia: (rank(ia[1]), ia[0]))[1].name


def update_index(root: Path, entry: Dict[str, Any]) -> None:
    path = root / INDEX_NAME
    data: Dict[str, Any] = {"generator": "tools/assets/t3map.py", "maps": []}
    if path.is_file():
        try:
            data = json.loads(path.read_text(encoding="utf-8"))
        except (OSError, ValueError):
            pass
    maps = [m for m in data.get("maps", []) if m.get("id") != entry["id"]]
    maps.append(entry)
    maps.sort(key=lambda m: str(m.get("title", m.get("id", ""))).lower())
    data["maps"] = maps
    path.write_text(json.dumps(data, indent=1), encoding="utf-8")


def export_level(gmp: Path, game: Path, root: Path, scale: float, names: PropertyNames, gs: Gamesys,
                 json_only: bool = False, limit: int = 0, strings: Optional[Dict[str, str]] = None) -> None:
    level = gmp.stem
    out = root / level
    out.mkdir(parents=True, exist_ok=True)
    t0 = time.time()
    pkg = Package(gmp)
    actors = extract_actors(pkg, names, gs)
    links = extract_links(pkg)
    apply_attachments(actors, links)
    doc = {"level": level, "source": gmp.name, "units": "unreal (Z up)", "actor_count": len(actors),
           "actors": [vars(a) for a in actors], "links": links}
    (out / f"{level}.actors.json").write_text(json.dumps(doc, indent=1, default=str), encoding="utf-8")
    print(f"{level}: {len(actors)} actors -> {level}/{level}.actors.json ({time.time() - t0:.1f} s)")
    if json_only:
        return

    ensure_project(root)
    ibt_path = gmp.with_suffix(".ibt")
    bundles = [IBT(ibt_path)] if ibt_path.is_file() else []
    k = kernel_bundle(ibt_path)
    if k:
        bundles.append(k)
    try:
        res = ResourceSet(bundles, out / "textures")
        wanted = sorted({(a.mesh, a.skin or "Default") for a in actors if a.mesh})
        mesh_files: Dict[Tuple[str, str], str] = {}
        missing = []
        for i, (mesh, skin) in enumerate(wanted):
            if limit and i >= limit:
                break
            m = res.mesh(mesh)
            if m is None:
                missing.append(mesh)
                continue
            fname = mesh_file_name(m.name, skin)
            target = out / "meshes" / fname
            if not target.exists():
                export_mesh(m, skin, res, target, scale)
            mesh_files[(mesh, skin)] = fname
        print(f"  {len(mesh_files)} mesh/skin pairs exported, {len(missing)} meshes not found in the bundles"
              f" ({time.time() - t0:.1f} s)")
        if missing:
            print("  missing: " + ", ".join(sorted(set(missing))[:20]) + (" ..." if len(set(missing)) > 20 else ""))
        bsp = export_bsp(gmp, out, scale, res)
        print(f"  BSP: {bsp.name if bsp else 'no render blocks found'} ({time.time() - t0:.1f} s)")
        title = level_title(actors, strings or {}, level)
        start = default_player_start(actors)
        write_tscn(out / f"{level}.tscn", level, actors, mesh_files, scale, bsp.name if bsp else None,
                   start, title)
        update_index(root, {"id": level, "title": title, "scene": f"res://{level}/{level}.tscn",
                            "actors": len(actors), "meshes": len(mesh_files),
                            "lights": sum(1 for a in actors if a.light is not None),
                            "units_per_meter": round(1.0 / scale, 4), "default_start": start or ""})
        print(f"  scene: {level}/{level}.tscn  ({title})")
    finally:
        for b in bundles:
            b.close()


def main() -> None:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("level", nargs="?", help="map name (Inn) or path to a .gmp")
    ap.add_argument("--all", action="store_true", help="export every map in Content/T3/Maps")
    ap.add_argument("--game-dir")
    ap.add_argument("-o", "--output", default=str(BUILD_DIR / "godot"), help="Godot project folder")
    ap.add_argument("--scale", type=float, default=DEFAULT_SCALE, help="metres per Unreal unit")
    ap.add_argument("--json-only", action="store_true")
    ap.add_argument("--limit", type=int, default=0, help="export at most N meshes (debugging)")
    args = ap.parse_args()
    if not args.level and not args.all:
        ap.error("give a map name or --all")

    game = game_dir(args.game_dir)
    load_categories(game)
    names = PropertyNames(load_table(game))
    gs = load_gamesys(game)
    if args.all:
        maps = sorted((game / "Content" / "T3" / "Maps").glob("*.gmp"), key=lambda p: p.stem.lower())
    else:
        maps = [resolve_map(game, args.level, ".gmp")]
    strings = load_string_tags(game)
    for gmp in maps:
        export_level(gmp, game, Path(args.output), args.scale, names, gs, args.json_only, args.limit, strings)


if __name__ == "__main__":
    run_cli(main)
