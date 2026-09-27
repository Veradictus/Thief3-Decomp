#!/usr/bin/env python3
"""Texture and material resources from .ibt bundles.

Texture resource (type 0x08), one serialiser part per field:

  u8   version (1)
  u32  format: FourCC 'DXT1'/'DXT3'/'DXT5', or a D3DFORMAT number
       (21 = A8R8G8B8, 22 = X8R8G8B8)
  u32  mip count
  u32  usage (0 diffuse, 1 normal map, 2 specular, 3 mask, 5 emissive, 6 environment, ...)
  u32  usage detail (0..5; meaning unknown)
  u32  width, u32 height
  u32  width, u32 height again (0 for some environment maps)
  u32  total size of the mip data
  u8, u8 (unknown; the second is 1 for render targets)
  per mip: u32 level, u32 width, u32 height, u32 size, <padding part>, <data part>

Material resource (type 0x0A, from the MatLib .mlb files authored with the
"IonShader" 3ds Max rollout): colours, a stage mask, the source .mlb path, a
surface category (index into the install's MatLib/categories.txt) and eight
texture stage names (0 diffuse, 1 normal map, 5 glow, 6 environment...).

Usage:
  t3texture.py list   <MapName|file.ibt>
  t3texture.py export <MapName|file.ibt> [--name SUBSTR] [--dds] [--png] [-o DIR]
  t3texture.py materials <MapName|file.ibt> [--json out.json]

PNG conversion decodes DXT1/3/5 in pure Python (a few seconds per 512x512).
"""

from __future__ import annotations

import argparse
import json
import struct
import sys
import zlib
from dataclasses import dataclass, field
from pathlib import Path
from typing import Dict, List, Optional, Tuple

sys.path.insert(0, str(Path(__file__).resolve().parent))
from ibt import IBT, PartReader, Resource, open_ibt  # noqa: E402
from t3common import run_cli, BUILD_DIR, game_dir  # noqa: E402

TYPE_TEXTURE = 0x08
TYPE_MATERIAL = 0x0A

D3DFMT = {21: "A8R8G8B8", 22: "X8R8G8B8", 25: "A1R5G5B5", 26: "A4R4G4B4", 23: "R5G6B5", 28: "A8", 50: "L8"}
USAGE = {0: "diffuse", 1: "normal", 2: "specular", 3: "mask", 4: "detail", 5: "emissive", 6: "environment",
         7: "normal2"}
STAGES = ["diffuse", "normal", "stage2", "stage3", "stage4", "glow", "environment", "stage7"]


@dataclass
class Mip:
    width: int
    height: int
    data: bytes


@dataclass
class Texture:
    name: str
    format: str  # 'DXT1', 'DXT3', 'DXT5' or a D3DFMT name
    width: int
    height: int
    usage: int
    usage_detail: int
    mips: List[Mip] = field(default_factory=list)

    @property
    def is_dxt(self) -> bool:
        return self.format.startswith("DXT")


def parse_texture(res: Resource, parts: List[bytes]) -> Texture:
    pr = PartReader(parts)
    version = pr.u8()
    if version != 1:
        raise ValueError(f"{res.name}: texture version {version}")
    fourcc = pr.raw(4)
    if all(0x20 <= c < 0x7F for c in fourcc):
        fmt = fourcc.decode("ascii")
    else:
        code = struct.unpack("<I", fourcc)[0]
        fmt = D3DFMT.get(code, f"D3DFMT_{code}")
    mip_count = pr.u32()
    usage, detail = pr.u32(), pr.u32()
    width, height = pr.u32(), pr.u32()
    pr.u32(), pr.u32()  # second width/height (0 for some environment maps)
    pr.u32()  # total mip bytes
    pr.u8(), pr.u8()
    tex = Texture(res.name, fmt, width, height, usage, detail)
    for _ in range(mip_count):
        level, w, h, size = pr.u32(), pr.u32(), pr.u32(), pr.u32()
        pr.raw()  # alignment padding (may be an empty part)
        data = pr.raw(size)
        tex.mips.append(Mip(w, h, data))
    if not pr.done():
        raise ValueError(f"{res.name}: {len(parts) - pr.i} unread parts")
    return tex


# --- DDS ------------------------------------------------------------------------

DDSD_CAPS, DDSD_HEIGHT, DDSD_WIDTH, DDSD_PITCH = 0x1, 0x2, 0x4, 0x8
DDSD_PIXELFORMAT, DDSD_MIPMAPCOUNT, DDSD_LINEARSIZE = 0x1000, 0x20000, 0x80000
DDPF_ALPHAPIXELS, DDPF_FOURCC, DDPF_RGB = 0x1, 0x4, 0x40
DDSCAPS_COMPLEX, DDSCAPS_TEXTURE, DDSCAPS_MIPMAP = 0x8, 0x1000, 0x400000


def to_dds(tex: Texture) -> bytes:
    mips = len(tex.mips)
    flags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH | DDSD_PIXELFORMAT
    caps = DDSCAPS_TEXTURE
    if mips > 1:
        flags |= DDSD_MIPMAPCOUNT
        caps |= DDSCAPS_COMPLEX | DDSCAPS_MIPMAP
    if tex.is_dxt:
        flags |= DDSD_LINEARSIZE
        pitch = len(tex.mips[0].data)
        pf = struct.pack("<II4sIIIII", 32, DDPF_FOURCC, tex.format.encode(), 0, 0, 0, 0, 0)
    elif tex.format in ("A8R8G8B8", "X8R8G8B8"):
        flags |= DDSD_PITCH
        pitch = tex.width * 4
        alpha = tex.format == "A8R8G8B8"
        pf = struct.pack("<II4sIIIII", 32, DDPF_RGB | (DDPF_ALPHAPIXELS if alpha else 0), b"\0\0\0\0", 32,
                         0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000 if alpha else 0)
    else:
        raise ValueError(f"{tex.name}: no DDS mapping for {tex.format}")
    header = struct.pack("<4sIIIIIII44x", b"DDS ", 124, flags, tex.height, tex.width, pitch, 0, mips)
    header += pf + struct.pack("<IIIII", caps, 0, 0, 0, 0)
    assert len(header) == 128
    return header + b"".join(m.data for m in tex.mips)


# --- DXT decoding -------------------------------------------------------------------

def _rgb565(c: int) -> Tuple[int, int, int]:
    r = (c >> 11) & 31
    g = (c >> 5) & 63
    b = c & 31
    return (r << 3 | r >> 2, g << 2 | g >> 4, b << 3 | b >> 2)


def _color_block(block: bytes, off: int, dxt1: bool):
    c0, c1, bits = struct.unpack_from("<HHI", block, off)
    p0, p1 = _rgb565(c0), _rgb565(c1)
    if c0 > c1 or not dxt1:
        p2 = tuple((2 * a + b) // 3 for a, b in zip(p0, p1))
        p3 = tuple((a + 2 * b) // 3 for a, b in zip(p0, p1))
        pal = (p0 + (255,), p1 + (255,), p2 + (255,), p3 + (255,))
    else:
        p2 = tuple((a + b) // 2 for a, b in zip(p0, p1))
        pal = (p0 + (255,), p1 + (255,), p2 + (255,), (0, 0, 0, 0))
    return [pal[(bits >> (2 * i)) & 3] for i in range(16)]


def decode_rgba(tex: Texture, mip: int = 0) -> Tuple[int, int, bytearray]:
    """Decode one mip to RGBA8 (row-major, top row first)."""
    m = tex.mips[mip]
    w, h, data = m.width, m.height, m.data
    out = bytearray(w * h * 4)
    if tex.format in ("A8R8G8B8", "X8R8G8B8"):
        for i in range(w * h):
            b, g, r, a = data[4 * i:4 * i + 4]
            out[4 * i:4 * i + 4] = bytes((r, g, b, a if tex.format == "A8R8G8B8" else 255))
        return w, h, out
    if not tex.is_dxt:
        raise ValueError(f"{tex.name}: cannot decode {tex.format}")
    bsize = 8 if tex.format == "DXT1" else 16
    bw, bh = max(1, (w + 3) // 4), max(1, (h + 3) // 4)
    pos = 0
    for by in range(bh):
        for bx in range(bw):
            if tex.format == "DXT1":
                px = _color_block(data, pos, True)
            else:
                px = _color_block(data, pos + 8, False)
                if tex.format == "DXT3":
                    abits = int.from_bytes(data[pos:pos + 8], "little")
                    alphas = [((abits >> (4 * i)) & 15) * 17 for i in range(16)]
                else:
                    a0, a1 = data[pos], data[pos + 1]
                    abits = int.from_bytes(data[pos + 2:pos + 8], "little")
                    if a0 > a1:
                        pal = [a0, a1] + [((7 - k) * a0 + k * a1) // 7 for k in range(1, 7)]
                    else:
                        pal = [a0, a1] + [((5 - k) * a0 + k * a1) // 5 for k in range(1, 5)] + [0, 255]
                    alphas = [pal[(abits >> (3 * i)) & 7] for i in range(16)]
                px = [(p[0], p[1], p[2], a) for p, a in zip(px, alphas)]
            pos += bsize
            for i, p in enumerate(px):
                x, y = bx * 4 + (i & 3), by * 4 + (i >> 2)
                if x < w and y < h:
                    o = (y * w + x) * 4
                    out[o:o + 4] = bytes(p)
    return w, h, out


def write_png(path: Path, w: int, h: int, rgba: bytes, alpha: bool = True) -> None:
    stride = w * 4
    if alpha:
        raw = b"".join(b"\0" + bytes(rgba[y * stride:(y + 1) * stride]) for y in range(h))
        ctype = 6
    else:
        rows = []
        for y in range(h):
            row = rgba[y * stride:(y + 1) * stride]
            rgb = bytearray(w * 3)
            rgb[0::3], rgb[1::3], rgb[2::3] = row[0::4], row[1::4], row[2::4]
            rows.append(b"\0" + bytes(rgb))
        raw = b"".join(rows)
        ctype = 2

    def chunk(tag: bytes, body: bytes) -> bytes:
        return struct.pack(">I", len(body)) + tag + body + struct.pack(">I", zlib.crc32(tag + body) & 0xFFFFFFFF)

    png = b"\x89PNG\r\n\x1a\n" + chunk(b"IHDR", struct.pack(">IIBBBBB", w, h, 8, ctype, 0, 0, 0))
    png += chunk(b"IDAT", zlib.compress(raw, 6)) + chunk(b"IEND", b"")
    path.write_bytes(png)


def texture_has_alpha(tex: Texture) -> bool:
    return tex.format in ("DXT3", "DXT5", "A8R8G8B8") or (tex.format == "DXT1" and _dxt1_has_alpha(tex))


def _dxt1_has_alpha(tex: Texture) -> bool:
    data = tex.mips[0].data
    for pos in range(0, len(data), 8):
        c0, c1, bits = struct.unpack_from("<HHI", data, pos)
        if c0 <= c1:
            for i in range(16):
                if (bits >> (2 * i)) & 3 == 3:
                    return True
    return False


def export_texture(tex: Texture, out_dir: Path, dds: bool, png: bool) -> Dict[str, str]:
    out_dir.mkdir(parents=True, exist_ok=True)
    files = {}
    base = tex.name.lower()
    if dds:
        p = out_dir / f"{base}.dds"
        p.write_bytes(to_dds(tex))
        files["dds"] = p.name
    if png:
        p = out_dir / f"{base}.png"
        w, h, rgba = decode_rgba(tex)
        write_png(p, w, h, rgba, alpha=texture_has_alpha(tex))
        files["png"] = p.name
    return files


# --- materials ---------------------------------------------------------------------

_CATEGORIES: List[str] = []


def load_categories(game: Optional[Path] = None) -> List[str]:
    """Surface categories from the install's Content/T3/MatLib/categories.txt
    (a material stores its category as an index into this list)."""
    if not _CATEGORIES:
        try:
            g = game or game_dir()
            path = g / "Content" / "T3" / "MatLib" / "categories.txt"
            for line in path.read_text(encoding="latin-1").splitlines():
                line = line.strip()
                if line and not line.startswith("//"):
                    _CATEGORIES.append(line)
        except (OSError, SystemExit):
            pass
    return _CATEGORIES

@dataclass
class Material:
    name: str
    stage_mask: int
    colors: List[Tuple[float, float, float, float]]
    floats: Tuple[float, float, float]
    source: str
    category: int
    stages: List[str]

    def category_name(self, categories: Optional[List[str]] = None) -> str:
        cats = categories if categories is not None else _CATEGORIES
        return cats[self.category] if 0 <= self.category < len(cats) else str(self.category)

    def texture(self, stage: int) -> Optional[str]:
        s = self.stages[stage] if stage < len(self.stages) else ""
        return s or None


def parse_material(res: Resource, parts: List[bytes]) -> Material:
    pr = PartReader(parts)
    pr.u8()
    pr.u32()
    mask = pr.u32()
    colors = [struct.unpack("<4f", pr.raw(16)) for _ in range(3)]
    floats = (pr.f32(), pr.f32(), pr.f32())
    pr.u8(), pr.u32(), pr.u32(), pr.u8(), pr.u8(), pr.u8(), pr.u32(), pr.f32()
    source = pr.string()
    category = pr.u32()
    pr.u8(), pr.u32()
    stages = [pr.string() for _ in range(8)]
    return Material(res.name, mask, colors, floats, source, category, stages)


def load_materials(ibt: IBT) -> Dict[str, Material]:
    mats = {}
    for r in ibt.of_type(TYPE_MATERIAL):
        try:
            mats[r.name.lower()] = parse_material(r, ibt.split(r))
        except (ValueError, EOFError, struct.error) as ex:
            print(f"warning: material {r.name}: {ex}", file=sys.stderr)
    return mats


# --- CLI ------------------------------------------------------------------------------

def cmd_list(ibt: IBT, args) -> None:
    for r in ibt.of_type(TYPE_TEXTURE):
        t = parse_texture(r, ibt.split(r))
        print(f"{t.name:40s} {t.format:9s} {t.width:5d}x{t.height:<5d} mips {len(t.mips):2d} "
              f"usage {USAGE.get(t.usage, t.usage)}/{t.usage_detail}")


def cmd_export(ibt: IBT, args) -> None:
    out = Path(args.output) if args.output else BUILD_DIR / "textures" / ibt.path.stem
    dds, png = args.dds, args.png
    if not dds and not png:
        dds = png = True
    n = 0
    for r in ibt.of_type(TYPE_TEXTURE):
        if args.name and args.name.lower() not in r.name.lower():
            continue
        tex = parse_texture(r, ibt.split(r))
        try:
            export_texture(tex, out, dds, png)
            n += 1
        except ValueError as ex:
            print(f"skipped {r.name}: {ex}", file=sys.stderr)
    print(f"exported {n} textures to {out}")


def cmd_materials(ibt: IBT, args) -> None:
    load_categories(game_dir(args.game_dir))
    mats = load_materials(ibt)
    rows = []
    for m in mats.values():
        used = {STAGES[i]: s for i, s in enumerate(m.stages) if s}
        rows.append({"name": m.name, "category": m.category_name(), "mask": m.stage_mask,
                     "source": m.source, "stages": used,
                     "colors": m.colors, "params": m.floats})
        if not args.json:
            print(f"{m.name:36s} {m.category_name():10s} mask {m.stage_mask:#04x} {used}")
    if args.json:
        Path(args.json).write_text(json.dumps(rows, indent=1), encoding="utf-8")
        print(f"wrote {len(rows)} materials to {args.json}")


def main() -> None:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--game-dir")
    sub = ap.add_subparsers(dest="cmd", required=True)
    s = sub.add_parser("list")
    s.add_argument("ibt")
    s = sub.add_parser("export")
    s.add_argument("ibt")
    s.add_argument("--name")
    s.add_argument("--dds", action="store_true")
    s.add_argument("--png", action="store_true")
    s.add_argument("-o", "--output")
    s = sub.add_parser("materials")
    s.add_argument("ibt")
    s.add_argument("--json")
    args = ap.parse_args()
    with open_ibt(args.ibt, args.game_dir) as ibt:
        {"list": cmd_list, "export": cmd_export, "materials": cmd_materials}[args.cmd](ibt, args)


if __name__ == "__main__":
    run_cli(main)
