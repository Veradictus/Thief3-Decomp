#!/usr/bin/env python3
"""Static mesh resources (.ibt type 0x04) and their export to glTF 2.0.

Resource layout, one serialiser part per field ("string" = u32 length
including the NUL, then the characters):

  u32 skin count
    per skin: string name ("Default" or an alternate skin name),
              u32 section count, string material[section count]
  u32 skin count again, u32 per-skin flags
  u32 mesh flags
  u32 hardpoint count
    per hardpoint: 48 bytes (vec3 position, 3x3 rotation, rows), string name
                   ("Collision", or "hp_*" attachment points)
  u32 render data size, render data (one part):

    +00 vec3 bounding box min, vec3 max, f32 sphere radius, vec3 sphere centre
    +28 u32 vertex count, index count, triangle count, section count,
            shadow index count, shadow triangle count, shadow vertex count,
            unknown (1), vertex stride, unknown (0)
    +50 vertices, stride 64: vec3 position, vec3 normal, vec2 uv0, vec3 tangent,
                  vec2 uv1, vec2 uv2, u32 colour (BGRA);
                  stride -32 (packed, used by the level BSP blocks): vec3 position,
                  4-byte normal (D3DCOLOR order, 128 = 0), vec2 uv, 4-byte tangent, u32 colour
        shadow vertices: vec3 position + u32 (16 bytes each)
        shadow indices (u16), then render indices (u16, absolute)
        sections: FString name ("Default"), u32 triangles, first vertex,
                  vertex count, first index, index count, unknown (0)

Section i of the render data uses material skin.materials[i].  A material
name resolves to a MatLib material (type 0x0A) in the level bundle or in
Kernel_GFXALL.ibt, whose stage 0 names the diffuse texture.  The "BF"
material (category "ignored", texture "BadTexture") marks faces the game does
not draw; they are dropped unless --keep-hidden is given.

Positions are Unreal units in Unreal's axes (Z up).  Export swaps Y and Z and
reverses the triangle winding (see t3common.u2g).

Usage:
  t3mesh.py list   <MapName|file.ibt>
  t3mesh.py info   <MapName|file.ibt> <mesh>
  t3mesh.py export <MapName|file.ibt> [--name SUBSTR] [--skin NAME] [--scale 0.01905] [-o DIR]
"""

from __future__ import annotations

import argparse
import struct
import sys
from dataclasses import dataclass, field
from pathlib import Path
from typing import Dict, List, Optional, Sequence, Tuple

sys.path.insert(0, str(Path(__file__).resolve().parent))
from gltf import GLTFBuilder  # noqa: E402
from ibt import IBT, PartReader, Resource, open_ibt  # noqa: E402
from t3common import run_cli, BUILD_DIR, game_dir, u2g  # noqa: E402
from t3texture import (TYPE_MATERIAL, TYPE_TEXTURE, Material, export_texture, load_categories,  # noqa: E402
                       parse_material, parse_texture, texture_has_alpha)

TYPE_STATICMESH = 0x04
# Material names whose faces the game does not draw.  "BF" is the only one
# seen so far (it names a placeholder texture); override with --keep-hidden.
HIDDEN_MATERIALS = {"bf"}
# Metres per Unreal unit.  T3 content is built at 16 units per foot (a mesh
# named "...Door4x8..." is 64 x 128 units), so 1 unit = 0.3048 / 16 m.
UNITS_PER_FOOT = 16.0
DEFAULT_SCALE = 0.3048 / UNITS_PER_FOOT


@dataclass
class Skin:
    name: str
    materials: List[str]


@dataclass
class Hardpoint:
    name: str
    position: Tuple[float, float, float]
    rotation: Tuple[Tuple[float, float, float], ...]  # 3 rows


@dataclass
class Section:
    name: str
    triangles: int
    first_vertex: int
    vertex_count: int
    first_index: int
    index_count: int
    unknown: int


@dataclass
class RenderMesh:
    bbox_min: Tuple[float, float, float]
    bbox_max: Tuple[float, float, float]
    sphere_radius: float
    sphere_center: Tuple[float, float, float]
    positions: List[Tuple[float, float, float]] = field(default_factory=list)
    normals: List[Tuple[float, float, float]] = field(default_factory=list)
    uv0: List[Tuple[float, float]] = field(default_factory=list)
    tangents: List[Tuple[float, float, float]] = field(default_factory=list)
    uv1: List[Tuple[float, float]] = field(default_factory=list)
    uv2: List[Tuple[float, float]] = field(default_factory=list)
    colors: List[int] = field(default_factory=list)
    indices: List[int] = field(default_factory=list)
    sections: List[Section] = field(default_factory=list)
    shadow_vertex_count: int = 0
    shadow_index_count: int = 0
    size: int = 0  # bytes consumed by parse_render_data


@dataclass
class StaticMesh:
    name: str
    skins: List[Skin]
    skin_flags: List[int]
    flags: int
    hardpoints: List[Hardpoint]
    render: RenderMesh

    def skin(self, name: Optional[str]) -> Skin:
        if name:
            for s in self.skins:
                if s.name.lower() == name.lower():
                    return s
        return self.skins[0]


def _unpack_normal(b: bytes) -> Tuple[float, float, float]:
    """Packed D3DCOLOR-order normal: bytes z, y, x, w with 128 = 0."""
    return ((b[2] - 128) / 127.0, (b[1] - 128) / 127.0, (b[0] - 128) / 127.0)


def parse_render_data(blob: bytes, start: int = 0, end: Optional[int] = None) -> RenderMesh:
    """Render data block (static mesh resources and the level's BSP blocks).

    The vertex stride field is 64 for float vertices; -32 (0xFFFFFFE0) marks
    packed 32-byte vertices: vec3 position, packed normal (4 bytes), vec2 uv0,
    packed tangent (4 bytes), u32 colour.  If `end` is None the block's own
    size is used and returned via RenderMesh.size."""
    bmin = struct.unpack_from("<3f", blob, start)
    bmax = struct.unpack_from("<3f", blob, start + 12)
    radius = struct.unpack_from("<f", blob, start + 24)[0]
    center = struct.unpack_from("<3f", blob, start + 28)
    (nv, ni, nt, ns, nsi, nst, nsv, _u1, stride, _u2) = struct.unpack_from("<10I", blob, start + 0x28)
    if stride >= 0x80000000:
        stride -= 1 << 32
    if stride not in (64, -32):
        raise ValueError(f"unexpected vertex stride {stride}")
    rm = RenderMesh(bmin, bmax, radius, center, shadow_vertex_count=nsv, shadow_index_count=nsi)
    pos = start + 0x50
    if stride == 64:
        vfmt = struct.Struct("<3f3f2f3f2f2fI")
        for i in range(nv):
            v = vfmt.unpack_from(blob, pos + i * 64)
            rm.positions.append(v[0:3])
            rm.normals.append(v[3:6])
            rm.uv0.append(v[6:8])
            rm.tangents.append(v[8:11])
            rm.uv1.append(v[11:13])
            rm.uv2.append(v[13:15])
            rm.colors.append(v[15])
        pos += nv * 64
    else:
        vfmt = struct.Struct("<3f4s2f4sI")
        for i in range(nv):
            x, y, z, n, u, v, t, c = vfmt.unpack_from(blob, pos + i * 32)
            rm.positions.append((x, y, z))
            rm.normals.append(_unpack_normal(n))
            rm.uv0.append((u, v))
            rm.tangents.append(_unpack_normal(t))
            rm.uv1.append((u, v))
            rm.uv2.append((u, v))
            rm.colors.append(c)
        pos += nv * 32
    pos += nsv * 16 + nsi * 2  # shadow volume data (not exported)
    rm.indices = list(struct.unpack_from(f"<{ni}H", blob, pos))
    pos += ni * 2
    for _ in range(ns):
        # FString with a compact-index length (always short here)
        n = blob[pos]
        if n & 0xC0 or n < 1:
            raise ValueError("unexpected section name encoding")
        name = blob[pos + 1:pos + n].decode("latin-1")
        pos += 1 + n
        rm.sections.append(Section(name, *struct.unpack_from("<6I", blob, pos)))
        pos += 24
    if end is not None and pos != end:
        raise ValueError(f"render data: parsed {pos - start} of {end - start} bytes")
    rm.size = pos - start
    # The header triangle count occasionally exceeds index_count / 3 (e.g.
    # 106 vs 104 in one retail mesh), so only the index ranges are checked.
    if any(s.first_index + s.index_count > ni for s in rm.sections):
        raise ValueError("section index range out of bounds")
    return rm


def parse_static_mesh(res: Resource, parts: List[bytes]) -> StaticMesh:
    pr = PartReader(parts)
    skins = []
    for _ in range(pr.u32()):
        name = pr.string()
        mats = [pr.string() for _ in range(pr.u32())]
        skins.append(Skin(name, mats))
    skin_flags = [pr.u32() for _ in range(pr.u32())]
    flags = pr.u32()
    hardpoints = []
    for _ in range(pr.u32()):
        m = struct.unpack("<12f", pr.raw(48))
        name = pr.string()
        hardpoints.append(Hardpoint(name, m[0:3], (m[3:6], m[6:9], m[9:12])))
    size = pr.u32()
    blob = pr.raw(size)
    render = parse_render_data(blob, 0, len(blob))
    if not pr.done():
        raise ValueError(f"{res.name}: {len(parts) - pr.i} unread parts")
    return StaticMesh(res.name, skins, skin_flags, flags, hardpoints, render)


# --- resource lookup across bundles ---------------------------------------------------

class ResourceSet:
    """Resolves names across a level bundle and the kernel bundle, the way the
    game has both loaded at once.  Exports textures on demand."""

    def __init__(self, bundles: Sequence[IBT], texture_dir: Path, texture_uri_prefix: str = "../textures/",
                 overwrite: bool = False) -> None:
        """`overwrite`: export each texture again even if its PNG exists."""
        self.bundles = list(bundles)
        self.texture_dir = texture_dir
        self.uri_prefix = texture_uri_prefix
        self.overwrite = overwrite
        self._materials: Dict[str, Optional[Material]] = {}
        self._textures: Dict[str, Optional[Tuple[str, bool]]] = {}

    def find(self, name: str, rtype: int) -> Optional[Tuple[IBT, Resource]]:
        for b in self.bundles:
            r = b.find(name, rtype)
            if r is not None:
                return b, r
        return None

    def mesh(self, name: str) -> Optional[StaticMesh]:
        hit = self.find(name, TYPE_STATICMESH)
        if hit is None:
            return None
        b, r = hit
        return parse_static_mesh(r, b.split(r))

    def material(self, name: str) -> Optional[Material]:
        key = name.lower()
        if key not in self._materials:
            hit = self.find(name, TYPE_MATERIAL)
            self._materials[key] = parse_material(hit[1], hit[0].split(hit[1])) if hit else None
        return self._materials[key]

    def texture_png(self, name: str) -> Optional[Tuple[str, bool]]:
        """Export texture `name` as PNG once; returns (uri, has_alpha)."""
        key = name.lower()
        if key not in self._textures:
            hit = self.find(name, TYPE_TEXTURE)
            if hit is None:
                self._textures[key] = None
            else:
                tex = parse_texture(hit[1], hit[0].split(hit[1]))
                png = self.texture_dir / f"{key}.png"
                if self.overwrite or not png.exists():
                    export_texture(tex, self.texture_dir, dds=False, png=True)
                self._textures[key] = (self.uri_prefix + png.name, texture_has_alpha(tex))
        return self._textures[key]


def kernel_bundle(level_ibt: Path) -> Optional[IBT]:
    k = level_ibt.parent / "Kernel_GFXALL.ibt"
    if k.is_file() and k.resolve() != level_ibt.resolve():
        return IBT(k)
    return None


# --- glTF export -------------------------------------------------------------------------

def render_primitives(g: GLTFBuilder, rm: RenderMesh, materials: Sequence[str], res: ResourceSet,
                      scale: float, keep_hidden: bool = False) -> List[Dict[str, object]]:
    """glTF primitives for a render data block, one per section; `materials`
    names the material of each section."""
    prims: List[Dict[str, object]] = []
    for si, sec in enumerate(rm.sections):
        mat_name = materials[si] if si < len(materials) else "DefaultTexture"
        if mat_name.lower() in HIDDEN_MATERIALS and not keep_hidden:
            continue
        if sec.index_count < 3:
            continue
        lo, hi = sec.first_vertex, sec.first_vertex + sec.vertex_count
        pos = [u2g(p, scale) for p in rm.positions[lo:hi]]
        nrm = [u2g(n) for n in rm.normals[lo:hi]]
        uv = [(u, v) for u, v in rm.uv0[lo:hi]]
        idx = rm.indices[sec.first_index:sec.first_index + sec.index_count]
        tri = []
        for t in range(0, len(idx) - 2, 3):
            a, b, c = idx[t] - lo, idx[t + 1] - lo, idx[t + 2] - lo
            tri += [a, c, b]  # axis swap flips handedness: reverse winding
        attrs = {"POSITION": g.add_floats(pos, "VEC3", with_bounds=True),
                 "NORMAL": g.add_floats(nrm, "VEC3"),
                 "TEXCOORD_0": g.add_floats(uv, "VEC2")}
        uv1 = rm.uv1[lo:hi]
        if any(abs(a[0] - b[0]) > 1e-6 or abs(a[1] - b[1]) > 1e-6 for a, b in zip(uv1, uv)):
            attrs["TEXCOORD_1"] = g.add_floats(uv1, "VEC2")
        cols = rm.colors[lo:hi]
        if any(c != 0xFFFFFFFF for c in cols):
            attrs["COLOR_0"] = g.add_colors_u8([((c >> 16) & 255, (c >> 8) & 255, c & 255, (c >> 24) & 255)
                                               for c in cols])
        prims.append({"attributes": attrs, "indices": g.add_indices(tri),
                      "material": material_for(g, mat_name, res)})
    return prims


def mesh_to_gltf(mesh: StaticMesh, skin_name: Optional[str], res: ResourceSet, scale: float,
                 keep_hidden: bool = False) -> GLTFBuilder:
    rm = mesh.render
    skin = mesh.skin(skin_name)
    g = GLTFBuilder()
    prims = render_primitives(g, rm, skin.materials, res, scale, keep_hidden)
    extras = {"t3_mesh": mesh.name, "t3_skin": skin.name, "t3_skins": [s.name for s in mesh.skins]}
    mi = g.mesh(mesh.name, prims, extras) if prims else None
    children = []
    for hp in mesh.hardpoints:
        children.append(g.node(hp.name, translation=u2g(hp.position, scale),
                               extras={"t3_hardpoint": hp.name,
                                       "rotation_rows_unreal": [list(r) for r in hp.rotation]}))
    g.node(mesh.name, mesh=mi, children=children or None, extras=extras, root=True)
    return g


def material_for(g: GLTFBuilder, mat_name: str, res: ResourceSet) -> int:
    mat = res.material(mat_name)
    diffuse = normal = glow = None
    extras: Dict[str, object] = {"t3_material": mat_name}
    if mat is not None:
        diffuse, normal, glow = mat.texture(0), mat.texture(1), mat.texture(5)
        extras.update({"category": mat.category_name(), "stage_mask": mat.stage_mask,
                       "stages": [s for s in mat.stages]})
    else:
        diffuse = mat_name  # some skins name a texture directly
        extras["unresolved"] = True
    base = res.texture_png(diffuse) if diffuse else None
    alpha = "OPAQUE"
    if base and base[1]:
        alpha = "MASK"
    ntex = res.texture_png(normal) if normal else None
    gtex = res.texture_png(glow) if glow else None
    if base:
        color = (1.0, 1.0, 1.0, 1.0)
    elif mat is not None:
        # untextured materials (e.g. the metallic loot shaders: normal + environment
        # map only) fall back to the material's colour; unknown ones show magenta
        c = mat.colors[1]
        color = (c[0], c[1], c[2], 1.0)
    else:
        color = (0.8, 0.0, 0.8, 1.0)
    return g.material(mat_name,
                      base_color_tex=g.image(uri=base[0]) if base else None,
                      normal_tex=None if ntex is None else g.image(uri=ntex[0]),
                      emissive_tex=None if gtex is None else g.image(uri=gtex[0]),
                      base_color=color, alpha_mode=alpha, extras=extras,
                      roughness=0.4 if (mat is not None and mat.texture(6) and not base) else 0.9)


def export_mesh(mesh: StaticMesh, skin: Optional[str], res: ResourceSet, out: Path, scale: float,
                keep_hidden: bool = False) -> Path:
    g = mesh_to_gltf(mesh, skin, res, scale, keep_hidden)
    g.write_glb(out)
    return out


def mesh_file_name(mesh: str, skin: Optional[str]) -> str:
    base = "".join(c if c.isalnum() or c in "-_" else "_" for c in mesh)
    if skin and skin.lower() != "default":
        base += "__" + "".join(c if c.isalnum() or c in "-_" else "_" for c in skin)
    return base + ".glb"


# --- CLI ---------------------------------------------------------------------------------

def cmd_list(ibt: IBT, args) -> None:
    for r in ibt.of_type(TYPE_STATICMESH):
        m = parse_static_mesh(r, ibt.split(r))
        rm = m.render
        print(f"{m.name:36s} verts {len(rm.positions):5d} tris {len(rm.indices) // 3:5d} "
              f"sections {len(rm.sections)} skins {len(m.skins):2d} hardpoints {len(m.hardpoints)}")


def cmd_info(ibt: IBT, args) -> None:
    r = ibt.find(args.mesh, TYPE_STATICMESH)
    if r is None:
        sys.exit(f"no static mesh {args.mesh!r}")
    m = parse_static_mesh(r, ibt.split(r))
    rm = m.render
    print(f"{m.name}: flags {m.flags:#x}, bbox {rm.bbox_min} .. {rm.bbox_max}, radius {rm.sphere_radius:.2f}")
    print(f"  {len(rm.positions)} vertices, {len(rm.indices)} indices, shadow {rm.shadow_vertex_count} "
          f"vertices / {rm.shadow_index_count} indices")
    for s in rm.sections:
        print(f"  section {s.name}: {s.triangles} tris, vertices {s.first_vertex}+{s.vertex_count}, "
              f"indices {s.first_index}+{s.index_count}")
    for s, f in zip(m.skins, m.skin_flags):
        print(f"  skin {s.name!r} flags {f:#x}: {s.materials}")
    for h in m.hardpoints:
        print(f"  hardpoint {h.name}: at {tuple(round(c, 3) for c in h.position)}")


def cmd_export(ibt: IBT, args) -> None:
    load_categories(game_dir(args.game_dir))
    out = Path(args.output) if args.output else BUILD_DIR / "godot" / ibt.path.stem
    kern = kernel_bundle(ibt.path)
    res = ResourceSet([ibt] + ([kern] if kern else []), out / "textures")
    n = 0
    for r in ibt.of_type(TYPE_STATICMESH):
        if args.name and args.name.lower() not in r.name.lower():
            continue
        m = parse_static_mesh(r, ibt.split(r))
        export_mesh(m, args.skin, res, out / "meshes" / mesh_file_name(m.name, args.skin), args.scale,
                    args.keep_hidden)
        n += 1
    print(f"exported {n} meshes to {out / 'meshes'}")


def main() -> None:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--game-dir")
    sub = ap.add_subparsers(dest="cmd", required=True)
    s = sub.add_parser("list")
    s.add_argument("ibt")
    s = sub.add_parser("info")
    s.add_argument("ibt")
    s.add_argument("mesh")
    s = sub.add_parser("export")
    s.add_argument("ibt")
    s.add_argument("--name")
    s.add_argument("--skin")
    s.add_argument("--scale", type=float, default=DEFAULT_SCALE)
    s.add_argument("--keep-hidden", action="store_true", help="keep sections using the BF material")
    s.add_argument("-o", "--output")
    args = ap.parse_args()
    with open_ibt(args.ibt, args.game_dir) as ibt:
        {"list": cmd_list, "info": cmd_info, "export": cmd_export}[args.cmd](ibt, args)


if __name__ == "__main__":
    run_cli(main)
