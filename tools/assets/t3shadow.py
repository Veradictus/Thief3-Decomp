#!/usr/bin/env python3
"""Stencil shadow volumes for the Godot export (.t3shadow files).

T3 draws its shadows with stencil shadow volumes.  Every static mesh and BSP
render block stores a ready-made volume mesh next to its render data (see
t3mesh.parse_render_data): each face has its own three vertices carrying the
face normal, and the triangles are the faces plus two degenerate triangles per
edge.  A vertex shader pushes the vertices of light-facing faces to infinity;
the degenerate triangles on the silhouette then become the volume's sides.

A .t3shadow file holds one or more such meshes in Godot's axes and scale, laid
out so the viewer can hand the bytes to the GPU as they are:

  +00 char[4] "T3SV", u32 version (1), u32 mesh count, u32 0
  +10 per mesh, 32 bytes: u32 vertex count, u32 index count, u32 index size
      (2 or 4), u32 data offset (from the file start), f32 bounding sphere
      centre x, y, z, f32 radius (metres, in the mesh's own space)
  data, per mesh, each part padded to 4 bytes:
      f32 position x, y, z per vertex
      i8 face normal x, y, z, 0 per vertex (snorm: value / 127)
      indices (u16 or u32), three per triangle

Positions are converted like the render mesh (t3common.u2g, scaled), normals
get the same axis swap, and the triangle winding is reversed.  A mesh without
shadow data has zero counts; a BSP file has one entry per render block, in
block order (the glTF extras' t3_block_index).

Usage:
  t3shadow.py info <file.t3shadow>
"""

from __future__ import annotations

import argparse
import math
import struct
import sys
from dataclasses import dataclass, field
from pathlib import Path
from typing import List, Optional, Sequence, Tuple

sys.path.insert(0, str(Path(__file__).resolve().parent))
from t3common import run_cli, u2g  # noqa: E402
from t3mesh import RenderMesh  # noqa: E402

MAGIC = b"T3SV"
VERSION = 1
SUFFIX = ".t3shadow"
_HEADER = struct.Struct("<4sIII")
_ENTRY = struct.Struct("<4I4f")


@dataclass
class ShadowVolume:
    """A shadow-volume mesh in Godot's axes and scale."""
    positions: List[Tuple[float, float, float]] = field(default_factory=list)
    normals: List[Tuple[int, int, int]] = field(default_factory=list)  # snorm8: value / 127
    indices: List[int] = field(default_factory=list)

    def sphere(self) -> Tuple[Tuple[float, float, float], float]:
        """Bounding sphere: the box centre and the farthest vertex from it."""
        if not self.positions:
            return (0.0, 0.0, 0.0), 0.0
        lo = [min(p[i] for p in self.positions) for i in range(3)]
        hi = [max(p[i] for p in self.positions) for i in range(3)]
        c = tuple((a + b) * 0.5 for a, b in zip(lo, hi))
        r = max(math.dist(c, p) for p in self.positions)
        return c, r


def _snorm8(v: float) -> int:
    return max(-127, min(127, round(v * 127.0)))


def shadow_volume(rm: RenderMesh, scale: float) -> Optional[ShadowVolume]:
    """The shadow volume of a render data block in Godot's axes and scale, or
    None if it has none."""
    if not rm.shadow_positions or not rm.shadow_indices:
        return None
    vol = ShadowVolume([u2g(p, scale) for p in rm.shadow_positions],
                       [tuple(_snorm8(c) for c in u2g(n)) for n in rm.shadow_normals])
    idx = rm.shadow_indices
    for t in range(0, len(idx) - 2, 3):
        vol.indices += [idx[t], idx[t + 2], idx[t + 1]]  # axis swap flips handedness: reverse winding
    return vol


def _pad4(b: bytes) -> bytes:
    return b + b"\0" * (-len(b) % 4)


def encode(volumes: Sequence[Optional[ShadowVolume]]) -> bytes:
    """A .t3shadow file holding `volumes` (None: an entry without data)."""
    head = _HEADER.pack(MAGIC, VERSION, len(volumes), 0)
    offset = len(head) + _ENTRY.size * len(volumes)
    entries, data = b"", b""
    for vol in volumes:
        vol = vol or ShadowVolume()
        nv, ni = len(vol.positions), len(vol.indices)
        wide = nv > 0x10000
        c, r = vol.sphere()
        entries += _ENTRY.pack(nv, ni, 4 if wide else 2, offset + len(data) if nv else 0, *c, r)
        if not nv:
            continue
        data += _pad4(struct.pack(f"<{nv * 3}f", *(c for p in vol.positions for c in p)))
        data += _pad4(struct.pack(f"<{nv * 4}b", *(c for n in vol.normals for c in (*n, 0))))
        data += _pad4(struct.pack(f"<{ni}{'I' if wide else 'H'}", *vol.indices))
    return head + entries + data


def decode(data: bytes) -> List[ShadowVolume]:
    """The meshes of a .t3shadow file (the inverse of encode())."""
    magic, version, count, _ = _HEADER.unpack_from(data, 0)
    if magic != MAGIC:
        raise ValueError("not a .t3shadow file")
    if version != VERSION:
        raise ValueError(f".t3shadow version {version}, expected {VERSION}")
    out = []
    for i in range(count):
        nv, ni, isize, off, *_ = _ENTRY.unpack_from(data, _HEADER.size + i * _ENTRY.size)
        vol = ShadowVolume()
        if nv:
            pos = struct.unpack_from(f"<{nv * 3}f", data, off)
            vol.positions = [pos[k:k + 3] for k in range(0, len(pos), 3)]
            off += nv * 12
            nrm = struct.unpack_from(f"<{nv * 4}b", data, off)
            vol.normals = [nrm[k:k + 3] for k in range(0, len(nrm), 4)]
            off += nv * 4
            vol.indices = list(struct.unpack_from(f"<{ni}{'I' if isize == 4 else 'H'}", data, off))
        out.append(vol)
    return out


def write(path: Path, volumes: Sequence[Optional[ShadowVolume]]) -> Path:
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_bytes(encode(volumes))
    return path


def file_name(mesh: str) -> str:
    """The file of a static mesh's volume, named like its .glb."""
    return "".join(c if c.isalnum() or c in "-_" else "_" for c in mesh) + SUFFIX


def main() -> None:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = ap.add_subparsers(dest="cmd", required=True)
    s = sub.add_parser("info")
    s.add_argument("file")
    args = ap.parse_args()
    vols = decode(Path(args.file).read_bytes())
    print(f"{args.file}: {len(vols)} meshes, {sum(1 for v in vols if v.positions)} with shadow data")
    for i, v in enumerate(vols):
        if v.positions:
            c, r = v.sphere()
            print(f"  {i:4d}: {len(v.positions)} vertices, {len(v.indices) // 3} triangles, "
                  f"sphere ({c[0]:.2f}, {c[1]:.2f}, {c[2]:.2f}) r {r:.2f}")


if __name__ == "__main__":
    run_cli(main)
