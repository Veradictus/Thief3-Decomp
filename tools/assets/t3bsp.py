#!/usr/bin/env python3
"""Level BSP geometry: render blocks stored in the ULevel export of a .gmp.

T3's cooked maps keep only the BSP *nodes* in the level Model (planes,
bounding spheres, 256-bit zone masks, zone table); vertices and surfaces are
gone.  What the renderer draws instead are render blocks inside the Level
object ("MyLevel"): each is a u32 id followed by the same render-data layout
as a static mesh (see t3mesh.parse_render_data) with packed 32-byte vertices
(stride field -32) in world coordinates, and sections named after the
MatLib material they use.

How the blocks are indexed (zones? BSP leaves?) is not decoded yet, so this
module finds them by scanning the Level export for a valid render-data header
(counts, stride -32, section names) and keeps non-overlapping hits.  The
Level also holds, among others, the actor list, the URL, a navigation mesh and
a list of BSP polygons with 92-byte vertices (probably the source surfaces);
see docs/assets.md.

Usage:
  t3bsp.py stats  <Level>
  t3bsp.py export <Level> [--scale 0.01905] [-o build/assets/godot]   -> <Level>/meshes/<Level>_bsp.glb
"""

from __future__ import annotations

import argparse
import re
import struct
import sys
from dataclasses import dataclass
from pathlib import Path
from typing import List, Optional

sys.path.insert(0, str(Path(__file__).resolve().parent))
from gltf import GLTFBuilder  # noqa: E402
from ibt import IBT  # noqa: E402
from t3common import BUILD_DIR, game_dir, resolve_map, run_cli  # noqa: E402
from t3mesh import DEFAULT_SCALE, RenderMesh, ResourceSet, kernel_bundle, parse_render_data, render_primitives  # noqa: E402
from t3texture import load_categories  # noqa: E402
from upkg import Package  # noqa: E402

_HEADER_TAIL = struct.pack("<IiI", 1, -32, 0)  # unknown(1), stride(-32), unknown(0) at +0x44


@dataclass
class RenderBlock:
    offset: int      # offset of the render data inside the Level export
    block_id: int    # the u32 stored just before it
    mesh: RenderMesh


def level_export(pkg: Package):
    for e in pkg.exports:
        if pkg.export_class(e) == "Level":
            return e
    raise ValueError(f"{pkg.path.name}: no Level export")


def _plausible(rm: RenderMesh) -> bool:
    if not rm.sections or not rm.positions:
        return False
    for s in rm.sections:
        if not s.name or not all(32 <= ord(c) < 127 for c in s.name):
            return False
        if s.first_vertex + s.vertex_count > len(rm.positions):
            return False
    lo, hi = rm.bbox_min, rm.bbox_max
    return all(abs(v) < 1e6 for v in lo + hi) and all(a <= b for a, b in zip(lo, hi))


def find_render_blocks(pkg: Package) -> List[RenderBlock]:
    exp = level_export(pkg)
    data = pkg.export_bytes(exp)
    hits: List[RenderBlock] = []
    for m in re.finditer(re.escape(_HEADER_TAIL), data):
        start = m.start() - 0x44
        if start < 4:
            continue
        try:
            rm = parse_render_data(data, start)
        except (ValueError, struct.error, IndexError, UnicodeDecodeError):
            continue
        if _plausible(rm):
            hits.append(RenderBlock(start, struct.unpack_from("<I", data, start - 4)[0], rm))
    # drop overlapping hits (keep the first)
    out: List[RenderBlock] = []
    end = -1
    for b in sorted(hits, key=lambda b: b.offset):
        if b.offset >= end:
            out.append(b)
            end = b.offset + b.mesh.size
    return out


def bsp_to_gltf(level: str, blocks: List[RenderBlock], res: ResourceSet, scale: float,
                keep_hidden: bool = False) -> GLTFBuilder:
    g = GLTFBuilder()
    children = []
    for i, b in enumerate(blocks):
        prims = render_primitives(g, b.mesh, [s.name for s in b.mesh.sections], res, scale, keep_hidden)
        if not prims:
            continue
        name = f"bsp_{i:03d}_{b.block_id}"  # block ids repeat, so the index keeps names unique
        extras = {"t3_block_id": b.block_id, "t3_block_index": i}
        mi = g.mesh(name, prims, extras)
        children.append(g.node(name, mesh=mi, extras=extras))
    g.node(f"{level}_BSP", children=children or None, extras={"t3_level": level, "t3_bsp_blocks": len(blocks)},
           root=True)
    return g


def export_bsp(gmp: Path, out_dir: Path, scale: float, res: ResourceSet, keep_hidden: bool = False) -> Optional[Path]:
    pkg = Package(gmp)
    blocks = find_render_blocks(pkg)
    if not blocks:
        return None
    g = bsp_to_gltf(gmp.stem, blocks, res, scale, keep_hidden)
    # next to the mesh .glb files so the relative texture URIs (../textures/) resolve
    path = out_dir / "meshes" / f"{gmp.stem}_bsp.glb"
    g.write_glb(path)
    return path


def main() -> None:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--game-dir")
    sub = ap.add_subparsers(dest="cmd", required=True)
    s = sub.add_parser("stats")
    s.add_argument("level")
    s = sub.add_parser("export")
    s.add_argument("level")
    s.add_argument("--scale", type=float, default=DEFAULT_SCALE)
    s.add_argument("--keep-hidden", action="store_true")
    s.add_argument("-o", "--output", default=str(BUILD_DIR / "godot"))
    args = ap.parse_args()
    game = game_dir(args.game_dir)
    gmp = resolve_map(game, args.level, ".gmp")
    if args.cmd == "stats":
        blocks = find_render_blocks(Package(gmp))
        verts = sum(len(b.mesh.positions) for b in blocks)
        tris = sum(len(b.mesh.indices) for b in blocks) // 3
        mats = sorted({s.name for b in blocks for s in b.mesh.sections})
        print(f"{gmp.stem}: {len(blocks)} BSP render blocks, {verts} vertices, {tris} triangles, "
              f"{len(mats)} materials")
        for m in mats:
            print(f"  {m}")
        return
    load_categories(game)
    out = Path(args.output) / gmp.stem
    ibt_path = gmp.with_suffix(".ibt")
    bundles = [IBT(ibt_path)] if ibt_path.is_file() else []
    k = kernel_bundle(ibt_path)
    if k:
        bundles.append(k)
    res = ResourceSet(bundles, out / "textures")
    path = export_bsp(gmp, out, args.scale, res, args.keep_hidden)
    print(f"wrote {path}" if path else "no BSP render blocks found")


if __name__ == "__main__":
    run_cli(main)
