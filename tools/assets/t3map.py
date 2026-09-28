#!/usr/bin/env python3
"""Export a Thief: Deadly Shadows level to JSON and to a Godot 4 scene.

Reads Content/T3/Maps/<Level>.gmp (actors) and <Level>.ibt (+ Kernel_GFXALL.ibt)
(meshes, materials, textures), plus System/T3Gamesys.t3u (archetypes) and the
property table from the script packages.

Output (default build/assets/godot/, itself a Godot 4.7 project):

  project.godot                  the viewer project, updated on every export
  t3_tools/                      the viewer and the headless check scripts
  addons/t3_map_editor/          the map editor plugin (edits -> <Level>/<Level>.edits.json)
  <Level>/<Level>.actors.json    every actor: class, archetype, transform, mesh,
                                 light, instance gamesys properties, links
  <Level>/<Level>.tscn           Node3D scene: static meshes instanced from
                                 .glb files, OmniLight3D/SpotLight3D for lights,
                                 Marker3D for everything else, sorted into folders by
                                 what they are and named after it (a mesh, an archetype,
                                 the item's in-game name); T3 data in node metadata.
                                 The level's saved edits are applied to it.
  <Level>/<Level>.tscn.bak       the scene an export replaced, if it was saved in Godot
  <Level>/meshes/*.glb           one per (mesh, skin) pair used by the level
  <Level>/textures/*.png
  <Level>/meshes/<Level>_bsp.glb  BSP render blocks from the Level object (t3bsp.py)

An export is stamped with the export format version (formats.json,
map_export).  Exporting a map again keeps its saved edits
(<Level>/<Level>.edits.json, written by the map editor plugin): the scene is
the map with them applied.  While the game holds a patched map (t3pack.py
install), the original is exported, from its backup.

Not exported yet: emitters, sounds, skeletal meshes, navigation data, zones
and portals, trigger scripts.  See docs/assets.md.

Usage:
  t3map.py Inn                       JSON + meshes + scene
  t3map.py --all                     every map
  t3map.py Inn --json-only           actor list only
  t3map.py Inn --scale 0.01905 -o DIR
  t3map.py Inn --without-edits       the map as it is, without its saved edits
  t3map.py --project-only -o DIR     update the project's viewer and editor plugin only
"""

from __future__ import annotations

import argparse
import hashlib
import json
import math
import shutil
import struct
import sys
import time
import uuid
from dataclasses import dataclass, field, replace
from pathlib import Path
from typing import Any, Dict, List, Optional, Set, Tuple

sys.path.insert(0, str(Path(__file__).resolve().parent))
from ibt import IBT  # noqa: E402
from t3common import (run_cli, BUILD_DIR, FORMATS, Reader, fmt_float, game_dir, godot_basis,  # noqa: E402
                       resolve_map, u2g)
from t3gamesys import Gamesys, blocks_to_dict, load_gamesys, mesh_of  # noqa: E402
from t3mesh import DEFAULT_SCALE, UNITS_PER_FOOT, ResourceSet, export_mesh, kernel_bundle, mesh_file_name  # noqa: E402
from t3pack import BACKUP_DIR, EditsError, load_edits, sha1_of, source_matches  # noqa: E402
from t3props import PropertyNames, load_table  # noqa: E402
from t3texture import load_categories  # noqa: E402
from t3bsp import export_bsp  # noqa: E402
from upkg import RF_HasStack, GamesysBlock, Package, _jsonable, prop_value, struct_fields  # noqa: E402

TOOLS_DIR = Path(__file__).resolve().parent
EDITOR_PLUGIN = "t3_map_editor"  # tools/assets/godot/addons/<name>, installed into every exported project

# The export format (formats.json, map_export).  Raise it when what an export
# writes changes in a way the viewer or the map editor plugin relies on: an
# export of an older version is then made again in full (meshes and textures
# too), and the launcher does that before it opens such a map.
EXPORT_VERSION: int = FORMATS["map_export"]


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
        self.inv_name = get("InvName")
        self.book_file = get("BookFileName")


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
    gamesys_types: Dict[str, str] = field(default_factory=dict)  # name -> block kind[:enum], see gamesys_types()
    links: List[str] = field(default_factory=list)
    attached_to: Optional[str] = None     # parent actor of an attachment link
    attached_bone: Optional[str] = None   # parent hardpoint/bone
    family: List[str] = field(default_factory=list)  # archetype display names, most derived first
    inv_name: Optional[str] = None        # InvName string tag of an item (t_daggerloot)
    display_name: Optional[str] = None    # the name the game shows for it, from the string tables
    book: Optional[str] = None            # BookFileName of a readable
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


def gamesys_types(blocks: Dict[int, GamesysBlock], names: PropertyNames) -> Dict[str, str]:
    """Property name -> value type of an actor's own gamesys blocks, keyed like
    blocks_to_dict(): the block kind ("float", "int", "bool", "byte", "name",
    "string", "struct", "array", "object", "class", "bitfield"), with the enum
    type appended for enum bytes and bitfields ("byte:<Enum>")."""
    out: Dict[str, str] = {}
    for pid, b in sorted(blocks.items()):
        kind = b.kind
        p = names.get(b.id)
        if p and kind == "byte" and p["type"] in names.enums:
            kind += ":" + p["type"]
        elif p and kind == "bitfield" and p["type"].startswith("bitfield<"):
            kind += ":" + p["type"][9:-1]
        out[names.name(b.id)] = kind
    return out


def _block_value(blocks: Dict[int, GamesysBlock], pid: Optional[int], default: Any = None) -> Any:
    b = blocks.get(pid) if pid is not None else None
    return default if b is None else b.value


def string_tag(value: Any) -> Optional[str]:
    """A string-table tag from a gamesys value: InvName holds either a name
    (t_CourierBag) or a string written as <string=t_WaterArrow>."""
    if not isinstance(value, str):
        return None
    tag = value.strip()
    if tag.startswith("<string=") and tag.endswith(">"):
        tag = tag[len("<string="):-1].strip()
    return tag if tag and tag != "None" else None


def resolve_display_names(actors: List[ActorRecord], strings: Dict[str, str]) -> None:
    """Fills in the name the game shows for each item (InvName through the
    string tables, whose tags differ in case: t_daggerloot, t_WaterArrow)."""
    by_tag = {k.lower(): v for k, v in strings.items()}
    for rec in actors:
        if rec.inv_name:
            rec.display_name = by_tag.get(rec.inv_name.lower()) or None


def extract_actors(pkg: Package, names: PropertyNames, gs: Gamesys) -> List[ActorRecord]:
    ids = PropIds(names)
    actors = []
    # The level's own list, where t3pack.py adds and removes actors; the file
    # keeps a removed actor's object.
    try:
        in_level = set(pkg.level_actors() or [])
    except (ValueError, EOFError, struct.error):
        in_level = set()
    for e in pkg.exports:
        if not (e.flags & RF_HasStack) or (in_level and e.index + 1 not in in_level):
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
            rec.family = [a.display for a in gs.chain(cls)]
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
        rec.inv_name = string_tag(_block_value(merged, ids.inv_name))
        book = _block_value(merged, ids.book_file)
        rec.book = book if isinstance(book, str) and book.strip() else None
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
        rec.gamesys_types = gamesys_types(own, names)
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


def _tscn_literal(v: Any) -> str:
    """`v` as a Godot value in a scene file: Dictionary, Array, String, bool,
    int or float (unlike _tscn_value(), which stores containers as JSON text)."""
    if isinstance(v, dict):
        return "{" + ", ".join(f"{_tscn_str(str(k))}: {_tscn_literal(x)}" for k, x in v.items()) + "}"
    if isinstance(v, (list, tuple)):
        return "[" + ", ".join(_tscn_literal(x) for x in v) + "]"
    if isinstance(v, float):
        return repr(v) if math.isfinite(v) else "0.0"
    return _tscn_value(v)


def _node_name(name: str, used: Dict[str, int]) -> str:
    n = "".join(c if c.isalnum() or c in "_-" else "_" for c in name) or "Node"
    if n in used:
        used[n] += 1
        n = f"{n}_{used[n]}"
    else:
        used[n] = 0
    return n


# --- scene layout ------------------------------------------------------------------------
# Actors are sorted into folders by what they are and named after it (the name
# the game shows for an item, an archetype, a mesh) instead of their object
# names, which stay in the t3_name metadata. The map editor plugin finds actors
# by that metadata, so the layout can change without breaking saved edits.

# Top-level folders, in scene order. The hidden ones hold editor-only actors,
# and parts that would float in the air without the skeletons they belong to.
FOLDER_ORDER = ("Geometry", "Objects", "Characters", "Lights", "Effects", "Sounds", "AI navigation",
                "Player starts", "Volumes and zones", "Level and mission", "Cameras", "Other", "Brushes",
                "Editor cameras", "Character parts")
HIDDEN_FOLDERS = {"Brushes", "Editor cameras", "Character parts"}
UNGROUPED = "Ungrouped"

# Archetypes too generic to name a folder after (the roots of the tree).
GENERIC_ARCHETYPES = {"WorldObj"}
NAV_POINTS = {"PatrolPoint", "WanderPoint", "FleePoint", "LookPoint", "PlayAnimPoint", "AddAIPoint",
              "NavMeshInsertionPoint", "PathNode"}
LEVEL_CLASSES = {"LevelInfo", "EnterMissionInfo", "ExitMissionInfo", "DifficultyInfo", "NorthMarker", "Marker"}
ZONE_CLASSES = {"ZoneProperties", "ZoneInfo", "SkyZoneInfo"}

# Characters Godot does not allow in node names.
INVALID_NODE_CHARS = set('.:@/"%')


def editor_groups(rec: ActorRecord) -> List[str]:
    """The level designers' editor groups (the Group property, comma-separated), without "None"."""
    return [g.strip() for g in (rec.group or "").split(",") if g.strip() and g.strip() != "None"]


def family_of(rec: ActorRecord) -> Optional[str]:
    """The archetype family: the most generic archetype below the tree's
    generic roots, such as SetDressing for the Inn's footprints or
    CityWatchGuard for a watch guard. None for actors without an archetype."""
    for name in reversed(rec.family):  # most generic first
        if name in GENERIC_ARCHETYPES or name.startswith("T3AIPawn"):
            continue
        return name
    return rec.family[0] if rec.family else None


def actor_folder(rec: ActorRecord, character_part: bool) -> Tuple[str, ...]:
    """The folder an actor goes into: a top-level folder and, for most, a subfolder."""
    cls, base = rec.cls, rec.base or rec.cls
    family = family_of(rec)
    if character_part:
        return ("Character parts",)
    if cls == "StaticMeshActor":
        groups = editor_groups(rec)
        return ("Geometry", groups[0] if groups else UNGROUPED)
    if "Pawn" in base:
        return ("Characters", family or cls)
    if base == "Emitter" or cls == "Emitter":
        return ("Effects", family or "Emitters")
    if base == "FX":
        return ("Lights",) if rec.light is not None else ("Effects", family or "FX")
    if rec.family and base == "Actor":
        return ("Objects", family or cls)
    if rec.light is not None:
        return ("Lights",)
    if cls == "AmbientSound" or "Sound" in base:
        return ("Sounds",)
    if cls in NAV_POINTS:
        return ("AI navigation", cls)
    if cls == "PlayerStart":
        return ("Player starts",)
    if "Volume" in cls or "Volume" in base or cls in ZONE_CLASSES:
        return ("Volumes and zones", cls)
    if cls in LEVEL_CLASSES or base in LEVEL_CLASSES:
        return ("Level and mission",)
    if cls == "Camera":
        return ("Editor cameras",)
    if cls == "CameraPoint":
        return ("Cameras",)
    if cls == "Brush":
        return ("Brushes",)
    return ("Other", cls)


def actor_label(rec: ActorRecord) -> str:
    """What an actor is, for its node name: the name the game shows for an
    item, else its archetype or mesh, else its class with a telling detail."""
    label = rec.display_name or rec.archetype or (rec.mesh if rec.cls == "StaticMeshActor" else None) or rec.cls
    if rec.book:
        label += f" ({Path(rec.book).stem})"
    dest = rec.gamesys.get("TeleportDestName")
    if rec.cls == "PlayerStart" and isinstance(dest, str) and dest not in ("", "None"):
        label += f" {dest}"
    elif not (rec.display_name or rec.archetype or rec.mesh) and rec.tag and rec.tag not in (rec.cls, rec.base):
        label += f" {rec.tag}"
    return label


def instance_number(name: str) -> Optional[int]:
    """N in an object name Name__N (FName's instance number, as printed)."""
    _, sep, tail = name.rpartition("__")
    return int(tail) if sep and tail.isdigit() else None


def scene_node_name(label: str, used: Dict[str, int]) -> str:
    """`label` as a node name Godot accepts, unique among its siblings."""
    n = "".join(c for c in label if c not in INVALID_NODE_CHARS and c.isprintable()).strip() or "Node"
    if n in used:
        used[n] += 1
        return f"{n} ({used[n]})"
    used[n] = 1
    return n


def _fmt_exact(v: float) -> str:
    """Float for a scene transform: enough digits to round-trip Godot's 32-bit
    floats, so the map editor plugin can tell moved actors from unmoved ones
    exactly; rounding noise from the rotation matrix (1e-16) becomes 0."""
    if not math.isfinite(v) or abs(v) < 1e-12:
        return "0"
    return f"{v:.9g}"


def transform3d(rec: ActorRecord, scale: float, extra_scale: float = 1.0) -> str:
    s = rec.draw_scale * extra_scale
    cols = godot_basis(rec.rotation[0], rec.rotation[1], rec.rotation[2], (s, s, s))
    o = u2g(rec.location, scale)
    rows = [cols[j][i] for i in range(3) for j in range(3)]
    return "Transform3D(" + ", ".join(_fmt_exact(x) for x in rows + list(o)) + ")"


def origin_meta(rec: ActorRecord) -> Dict[str, Any]:
    """The actor's placement in Unreal units as exported, for the map editor
    plugin: it compares nodes against this to find what was changed."""
    return {"location": [float(c) for c in rec.location], "rotation": [int(c) for c in rec.rotation],
            "draw_scale": float(rec.draw_scale)}


# --- saved edits -------------------------------------------------------------------------
# An export shows the map with its saved edits (<Level>.edits.json, from the
# map editor plugin) applied: changed actors where they were put, with their
# property edits in t3_gamesys_edits, the new actors (copies) and without the
# removed ones.  So exporting a map again, after an update of the tools, keeps
# the work done on it.  Every node keeps t3_origin, its placement in the map
# file, so the plugin tells the edits from the map as before and saves the
# same edits file again.

@dataclass
class SavedEdits:
    """Saved edits matched with the actors of a map (see resolve_edits())."""
    placed: Dict[str, ActorRecord] = field(default_factory=dict)  # changed actors, where they now stand
    gamesys: Dict[str, Dict[str, Any]] = field(default_factory=dict)  # property edits, by actor name
    # new actors in the file's order: (the actor copied, the copy where it stands, its property edits)
    copies: List[Tuple[ActorRecord, ActorRecord, Dict[str, Any]]] = field(default_factory=list)
    removed: Set[str] = field(default_factory=set)
    problems: List[str] = field(default_factory=list)  # edits that match no actor, left out

    def summary(self) -> str:
        changed = len(set(self.placed) | set(self.gamesys))
        return f"{changed} changed, {len(self.copies)} new and {len(self.removed)} removed actors"


def read_saved_edits(path: Path) -> Tuple[Optional[Dict[str, Any]], str]:
    """The edits file at `path` (t3pack.load_edits()), or None and why not
    ("" when there is none)."""
    if not path.is_file():
        return None, ""
    try:
        return load_edits(path), ""
    except EditsError as ex:
        return None, f"not applied: {ex}"


def resolve_edits(actors: List[ActorRecord], doc: Dict[str, Any]) -> SavedEdits:
    """Matches a loaded edits document with the map's actors, by name as
    t3pack.py does (exact, else ignoring case); an edit whose actor is not in
    the map is listed in `problems` and left out."""
    by_name: Dict[str, ActorRecord] = {}
    for a in actors:
        by_name.setdefault(a.name, a)
        by_name.setdefault(a.name.lower(), a)
    saved = SavedEdits()

    def find(name: str, what: str) -> Optional[ActorRecord]:
        rec = by_name.get(name) or by_name.get(name.lower())
        if rec is None:
            saved.problems.append(f"{what} {name}: no actor of that name in the map")
        return rec

    def placed(rec: ActorRecord, e: Dict[str, Any]) -> ActorRecord:
        return replace(rec, location=tuple(float(c) for c in e.get("location", rec.location)),
                       rotation=tuple(int(c) for c in e.get("rotation", rec.rotation)),
                       draw_scale=float(e.get("draw_scale", rec.draw_scale)))

    for name, e in doc.get("actors", {}).items():
        rec = find(name, "changed actor")
        if rec is not None:
            saved.placed[rec.name] = placed(rec, e)
            if e.get("gamesys"):
                saved.gamesys[rec.name] = dict(e["gamesys"])
    for e in doc.get("added", []):
        rec = find(e["copy_of"], "new actor, a copy of")
        if rec is not None:
            saved.copies.append((rec, placed(rec, e), dict(e.get("gamesys") or {})))
    for name in doc.get("removed", []):
        rec = find(name, "removed actor")
        if rec is not None and rec.cls == "LevelInfo":
            saved.problems.append(f"removed actor {name}: the level needs its LevelInfo, so it stays")
        elif rec is not None:
            saved.removed.add(rec.name)
    return saved


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
               title: str = "", enums: Optional[Dict[str, List[str]]] = None,
               source: Optional[Dict[str, Any]] = None, edits: Optional[SavedEdits] = None) -> None:
    """`enums` (enum type -> value names) supplies the value names of the enum
    properties in the scene; `source` ({file, size, sha1} of the .gmp) is
    stored on the root for the edits file of the map editor plugin.  `edits`
    (resolve_edits()) are applied: see "saved edits" above."""
    edits = edits or SavedEdits()
    ext: Dict[str, str] = {}
    lines_nodes: List[str] = []
    pawns = {a.name for a in actors if "Pawn" in (a.base or "")}

    def folder_of(rec: ActorRecord) -> Tuple[str, ...]:
        key = (rec.mesh or "", rec.skin or "Default")
        # eyes, teeth, hair, armour... attached to NPC skeletons, which are not
        # exported yet: kept, hidden, instead of floating in the air
        part = rec.attached_to in pawns and bool(rec.mesh) and key in mesh_files
        return actor_folder(rec, part)

    folders: Dict[Tuple[str, ...], List[ActorRecord]] = {}
    for rec in actors:
        if rec.name not in edits.removed:
            folders.setdefault(folder_of(rec), []).append(rec)
    # New actors go at the end of the folder of the actor they copy.
    copies: Dict[Tuple[str, ...], List[Tuple[ActorRecord, ActorRecord, Dict[str, Any]]]] = {}
    for c in edits.copies:
        folder = folder_of(c[0])
        copies.setdefault(folder, []).append(c)
        folders.setdefault(folder, [])

    def meta(rec: ActorRecord, folder: str, gamesys_edits: Optional[Dict[str, Any]] = None,
             copy: bool = False) -> List[str]:
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
            if rec.gamesys_types:
                out.append(f"metadata/t3_gamesys_types = {_tscn_str(json.dumps(rec.gamesys_types))}")
        if gamesys_edits:
            out.append(f"metadata/t3_gamesys_edits = {_tscn_literal(gamesys_edits)}")
        if rec.display_name:
            out.append(f"metadata/t3_display_name = {_tscn_str(rec.display_name)}")
        if rec.family:
            out.append(f"metadata/t3_family = {_tscn_str(' > '.join(reversed(rec.family)))}")
        groups = editor_groups(rec)
        if groups:
            out.append(f"metadata/t3_groups = {_tscn_str(', '.join(groups))}")
        if rec.book:
            out.append(f"metadata/t3_book = {_tscn_str(rec.book)}")
        out.append(f"metadata/t3_category = {_tscn_str(folder)}")
        out.append(f"metadata/t3_origin = {_tscn_str(json.dumps(origin_meta(rec)))}")
        if default_start and rec.name == default_start and not copy:
            out.append("metadata/t3_default_start = true")
        return out

    def light_lines(rec: ActorRecord, name: str, parent: str, xform: Optional[str]) -> List[str]:
        lt = rec.light or {}
        kind = lt.get("kind", "omni")
        gtype = {"spot": "SpotLight3D", "projector": "SpotLight3D", "directional": "DirectionalLight3D"}.get(
            kind, "OmniLight3D")
        out = [f'\n[node name="{name}" type="{gtype}" parent="{parent}"]']
        if xform:
            out.append(f"transform = {xform}")
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

    def actor_lines(rec: ActorRecord, name: str, parent: str, placed: Optional[ActorRecord] = None,
                    gamesys_edits: Optional[Dict[str, Any]] = None, copy: bool = False) -> List[str]:
        """The node of actor `rec`, standing where `placed` (an edited copy of
        it) stands if given; its metadata stays the actor's own."""
        xform = transform3d(placed or rec, scale)
        key = (rec.mesh or "", rec.skin or "Default")
        if rec.mesh and key in mesh_files:
            f = mesh_files[key]
            if f not in ext:
                ext[f] = f"{len(ext) + 1}_mesh"
            out = [f'\n[node name="{name}" parent="{parent}" instance=ExtResource("{ext[f]}")]',
                   f"transform = {xform}"]
            out.extend(meta(rec, parent, gamesys_edits, copy))
            if rec.light is not None:  # lamps, candles: mesh plus light
                out.extend(light_lines(rec, "T3Light", f"{parent}/{name}", None))
            return out
        if rec.light is not None:
            out = light_lines(rec, name, parent, xform)
        else:
            out = [f'\n[node name="{name}" type="Marker3D" parent="{parent}"]',
                   f"transform = {xform}"]
        out.extend(meta(rec, parent, gamesys_edits, copy))
        return out

    def node_label(rec: ActorRecord) -> str:
        number = instance_number(rec.name)
        return actor_label(rec) + ("" if number is None else f" #{number}")

    def folder_order(folder: Tuple[str, ...]) -> Tuple[Any, ...]:
        top = FOLDER_ORDER.index(folder[0]) if folder[0] in FOLDER_ORDER else len(FOLDER_ORDER)
        return (top, tuple((sub == UNGROUPED, sub.lower()) for sub in folder[1:]))

    def actor_order(rec: ActorRecord) -> Tuple[Any, ...]:
        number = instance_number(rec.name)
        return (actor_label(rec).lower(), -1 if number is None else number, rec.name)

    # Folders in a fixed order (subfolders alphabetically, Ungrouped last), and
    # in each the actors by name, so instances of the same mesh sit together.
    folder_paths: Dict[Tuple[str, ...], str] = {}
    for folder in sorted(folders, key=folder_order):
        for depth in range(1, len(folder) + 1):
            sub = folder[:depth]
            if sub in folder_paths:
                continue
            parent = folder_paths.get(sub[:-1], ".")
            name = scene_node_name(sub[-1], {})
            lines_nodes.append(f'\n[node name="{name}" type="Node3D" parent="{parent}"]')
            if depth == 1 and sub[0] in HIDDEN_FOLDERS:
                lines_nodes.append("visible = false")
            lines_nodes.append("metadata/t3_folder = true")
            folder_paths[sub] = name if parent == "." else f"{parent}/{name}"

        parent = folder_paths[folder]
        used: Dict[str, int] = {}
        for rec in sorted(folders[folder], key=actor_order):
            lines_nodes.extend(actor_lines(rec, scene_node_name(node_label(rec), used), parent,
                                           edits.placed.get(rec.name), edits.gamesys.get(rec.name)))
        # Named like the copies the map editor plugin makes ("... #1920 (copy)"):
        # a name ending in " #" and the instance number marks the actor's own node.
        for original, placed, gamesys_edits in copies.get(folder, []):
            lines_nodes.extend(actor_lines(original, scene_node_name(node_label(original) + " (copy)", used),
                                           parent, placed, gamesys_edits, copy=True))

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
            f"metadata/t3_units_per_meter = {repr(1.0 / scale)}",
            f"metadata/t3_actor_count = {sum(len(recs) for recs in folders.values())}",
            f"metadata/t3_export_version = {EXPORT_VERSION}"]
    if source:
        body.append(f"metadata/t3_source = {_tscn_str(json.dumps(source))}")
    used_enums = {t.split(":", 1)[1] for a in actors for t in a.gamesys_types.values() if ":" in t}
    scene_enums = {e: (enums or {})[e] for e in sorted(used_enums) if e in (enums or {})}
    if scene_enums:
        body.append(f"metadata/t3_enums = {_tscn_str(json.dumps(scene_enums))}")
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
    lines += ["", "[editor_plugins]", "",
              f'enabled=PackedStringArray("res://addons/{EDITOR_PLUGIN}/plugin.cfg")']
    lines += ["", "[rendering]", "", 'renderer/rendering_method="forward_plus"', ""]
    return "\n".join(lines)


def write_if_changed(path: Path, data: bytes) -> bool:
    """Writes `data` to `path` unless the file holds exactly that already, so
    an open Godot editor sees no change; returns whether it wrote."""
    try:
        if path.read_bytes() == data:
            return False
    except OSError:
        pass
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_bytes(data)
    return True


def sync_tree(src: Path, dst: Path, skip: Tuple[str, ...] = ()) -> int:
    """Copies the files under `src` that `dst` lacks or holds differently,
    except under the top-level folders in `skip`; returns how many it wrote.
    Files Godot adds (.uid, .import) are left alone."""
    written = 0
    for f in sorted(src.rglob("*")):
        rel = f.relative_to(src)
        if f.is_file() and rel.parts[0] not in skip and "__pycache__" not in rel.parts:
            written += write_if_changed(dst / rel, f.read_bytes())
    return written


def ensure_project(root: Path) -> int:
    """Make `root` a Godot 4.7 project running the map viewer: project.godot,
    a copy of tools/assets/godot/ in res://t3_tools/, and the map editor
    plugin in res://addons/t3_map_editor/ (enabled in project.godot).  Only
    new and changed files are written; returns how many."""
    root.mkdir(parents=True, exist_ok=True)
    written = int(write_if_changed(root / "project.godot", project_godot_text().encode("utf-8")))
    written += sync_tree(TOOLS_DIR / "godot", root / "t3_tools", skip=("addons",))
    written += sync_tree(TOOLS_DIR / "godot" / "addons" / EDITOR_PLUGIN, root / "addons" / EDITOR_PLUGIN)
    return written


def source_info(path: Path) -> Dict[str, Any]:
    """File name, size and SHA-1 of a map, so edits can be checked against it."""
    h = hashlib.sha1()
    with path.open("rb") as f:
        for chunk in iter(lambda: f.read(1 << 20), b""):
            h.update(chunk)
    return {"file": path.name, "size": path.stat().st_size, "sha1": h.hexdigest()}


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


def read_index(root: Path) -> Dict[str, Any]:
    """The project's map index (t3_maps.json), or an empty one."""
    path = root / INDEX_NAME
    if path.is_file():
        try:
            data = json.loads(path.read_text(encoding="utf-8"))
            if isinstance(data, dict) and isinstance(data.get("maps"), list):
                return data
        except (OSError, ValueError):
            pass
    return {"generator": "tools/assets/t3map.py", "maps": []}


def index_entry(root: Path, level: str) -> Optional[Dict[str, Any]]:
    """The index entry of a level's last export, if any."""
    return next((m for m in read_index(root)["maps"] if isinstance(m, dict) and m.get("id") == level), None)


def update_index(root: Path, entry: Dict[str, Any]) -> None:
    path = root / INDEX_NAME
    data = read_index(root)
    maps = [m for m in data.get("maps", []) if m.get("id") != entry["id"]]
    maps.append(entry)
    maps.sort(key=lambda m: str(m.get("title", m.get("id", ""))).lower())
    data["maps"] = maps
    path.write_text(json.dumps(data, indent=1), encoding="utf-8")


def export_source(gmp: Path, edits: Optional[Dict[str, Any]], backup_dir: Path = BACKUP_DIR) -> Path:
    """The file to export for the game's map `gmp`: `gmp` itself, unless the
    game holds a patched copy (t3pack.py install); then the backed-up
    original, or `gmp` if the saved `edits` were made from that patched copy.
    An installed patch is so never exported as if it were the map."""
    backup = backup_dir / gmp.name
    if not backup.is_file() or backup.resolve() == gmp.resolve():
        return gmp
    if backup.stat().st_size == gmp.stat().st_size and sha1_of(backup) == sha1_of(gmp):
        return gmp
    src = (edits or {}).get("source") or {}
    if ("sha1" in src or "size" in src) and source_matches(gmp, src):
        return gmp
    return backup


def keep_previous_scene(scene: Path, previous: Optional[Dict[str, Any]], edits: Path) -> Optional[Path]:
    """Before an export replaces `scene`: keeps it as <Level>.tscn.bak if it
    was saved in Godot since the last export (its hash is not the one the
    index recorded), in case it holds work its edits file does not.  An
    export from before the index recorded hashes counts as saved when the
    level has an edits file.  Returns the copy, if it made one."""
    if not scene.is_file():
        return None
    recorded = (previous or {}).get("scene_sha1")
    if (sha1_of(scene) == recorded) if recorded else not edits.is_file():
        return None
    bak = scene.with_name(scene.name + ".bak")
    shutil.copyfile(scene, bak)
    return bak


def export_level(gmp: Path, game: Path, root: Path, scale: float, names: PropertyNames, gs: Gamesys,
                 json_only: bool = False, limit: int = 0, strings: Optional[Dict[str, str]] = None,
                 with_edits: bool = True, backup_dir: Path = BACKUP_DIR) -> None:
    """Exports the game's map `gmp` into the project `root` (see the module
    docstring); `with_edits` applies the level's saved edits."""
    level = gmp.stem
    out = root / level
    out.mkdir(parents=True, exist_ok=True)
    t0 = time.time()
    edits_path = out / f"{level}.edits.json"
    edits_doc, edits_problem = read_saved_edits(edits_path) if with_edits else (None, "")
    src = export_source(gmp, edits_doc, backup_dir)
    if src != gmp:
        print(f"{level}: the game holds a patched map; exporting the original, {src}")
    pkg = Package(src)
    actors = extract_actors(pkg, names, gs)
    resolve_display_names(actors, strings or {})
    links = extract_links(pkg)
    apply_attachments(actors, links)
    source = source_info(src)
    doc = {"level": level, "source": gmp.name, "source_size": source["size"], "source_sha1": source["sha1"],
           "export_version": EXPORT_VERSION, "units": "unreal (Z up)", "actor_count": len(actors),
           "actors": [vars(a) for a in actors], "links": links}
    (out / f"{level}.actors.json").write_text(json.dumps(doc, indent=1, default=str), encoding="utf-8")
    print(f"{level}: {len(actors)} actors -> {level}/{level}.actors.json ({time.time() - t0:.1f} s)")
    if json_only:
        return

    # An export by older tools is made again in full: its meshes and textures too.
    previous = index_entry(root, level)
    version = (previous or {}).get("export_version")
    fresh = not isinstance(version, int) or version < EXPORT_VERSION
    ensure_project(root)
    ibt_path = gmp.with_suffix(".ibt")  # the game's bundle, also when exporting the backed-up map
    bundles = [IBT(ibt_path)] if ibt_path.is_file() else []
    k = kernel_bundle(ibt_path)
    if k:
        bundles.append(k)
    try:
        res = ResourceSet(bundles, out / "textures", overwrite=fresh)
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
            if fresh or not target.exists():
                export_mesh(m, skin, res, target, scale)
            mesh_files[(mesh, skin)] = fname
        print(f"  {len(mesh_files)} mesh/skin pairs exported, {len(missing)} meshes not found in the bundles"
              f" ({time.time() - t0:.1f} s)")
        if missing:
            print("  missing: " + ", ".join(sorted(set(missing))[:20]) + (" ..." if len(set(missing)) > 20 else ""))
        bsp = export_bsp(src, out, scale, res)
        print(f"  BSP: {bsp.name if bsp else 'no render blocks found'} ({time.time() - t0:.1f} s)")
        title = level_title(actors, strings or {}, level)
        start = default_player_start(actors)
        edits = resolve_edits(actors, edits_doc) if edits_doc else SavedEdits()
        if edits_problem:
            edits.problems.insert(0, edits_problem)
        scene = out / f"{level}.tscn"
        kept = keep_previous_scene(scene, previous, edits_path)
        write_tscn(scene, level, actors, mesh_files, scale, bsp.name if bsp else None, start, title, names.enums,
                   source, edits)
        update_index(root, {"id": level, "title": title, "scene": f"res://{level}/{level}.tscn",
                            "actors": len(actors), "meshes": len(mesh_files),
                            "lights": sum(1 for a in actors if a.light is not None),
                            "units_per_meter": round(1.0 / scale, 4), "default_start": start or "",
                            "source": source, "export_version": EXPORT_VERSION, "scene_sha1": sha1_of(scene)})
        print(f"  scene: {level}/{level}.tscn  ({title})")
        if kept:
            print(f"  kept the scene it replaced, which may hold changes made in Godot, as {level}/{kept.name}")
        if edits_doc:
            print(f"  saved edits applied ({edits_path.name}): {edits.summary()}")

        # Saving the scene in Godot rewrites the edits file from what the scene
        # holds: keep a copy of the file when the scene lacks some of its edits.
        without = not with_edits and edits_path.is_file()
        if (edits.problems or without) and edits_path.is_file():
            shutil.copyfile(edits_path, edits_path.with_name(edits_path.name + ".bak"))
        if without:
            print(f"  note: the scene is without the saved edits, and saving it in Godot replaces "
                  f"{edits_path.name} (a copy is kept as {edits_path.name}.bak)")
        if edits.problems:
            print(f"  warning: some saved edits could not be applied (a copy of the file is kept as "
                  f"{edits_path.name}.bak):")
            for p in edits.problems:
                print(f"    {p}")
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
    ap.add_argument("--without-edits", action="store_true",
                    help="export the map as it is, without its saved edits (the edits file is kept)")
    ap.add_argument("--project-only", action="store_true",
                    help="only update the project's viewer and map editor plugin; export no map")
    args = ap.parse_args()
    if args.project_only:
        written = ensure_project(Path(args.output))
        print(f"{args.output}: " + (f"{written} project files updated" if written else "project files up to date"))
        return
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
        export_level(gmp, game, Path(args.output), args.scale, names, gs, args.json_only, args.limit, strings,
                     not args.without_edits)


if __name__ == "__main__":
    run_cli(main)
