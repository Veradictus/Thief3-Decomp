#!/usr/bin/env python3
"""Self-test for the block-file writer (ibtwrite.py) and texture packs
(t3texpack.py), with synthetic data only.  selftest.py runs it; it can also
run alone: python tools/assets/selftest_texpack.py

The synthetic bundles are written here from the layout in docs/assets.md
(section 3) and the texture fields as t3texture.py reads them, independently
of the writer and the encoder under test.
"""

from __future__ import annotations

import hashlib
import json
import os
import random
import shutil
import struct
import subprocess
import sys
from pathlib import Path
from typing import Dict, List, Optional, Sequence, Tuple

sys.path.insert(0, str(Path(__file__).resolve().parent))
from ibt import IBT, Resource  # noqa: E402
from ibtwrite import BlockWriter, LayoutError, compare_bundles, survey  # noqa: E402
from t3common import BUILD_DIR  # noqa: E402
from t3texpack import (MANIFEST, PadRule, Report, State, TexPackError, cmd_apply, cmd_check, cmd_list,  # noqa: E402
                       cmd_restore, cmd_selfcheck, encode_replacement, find_rule, rule_counts, rules_for,
                       texture_head)
from t3texture import DDSError, Mip, Texture, parse_dds, parse_texture, texture_parts, to_dds  # noqa: E402

OUT = BUILD_DIR / "selftest" / "texpack"
ALIGN = 0x800
FOURCC = {"DXT1": b"DXT1", "DXT3": b"DXT3", "DXT5": b"DXT5", "A8R8G8B8": struct.pack("<I", 21),
          "X8R8G8B8": struct.pack("<I", 22)}


def u32(v: int) -> bytes:
    return struct.pack("<I", v)


def noise(n: int, seed) -> bytes:
    return random.Random(str(seed)).randbytes(n)


def mip_bytes(fmt: str, w: int, h: int) -> int:
    if fmt.startswith("DXT"):
        return max(1, (w + 3) // 4) * max(1, (h + 3) // 4) * (8 if fmt == "DXT1" else 16)
    return w * h * 4


# --- synthetic resources ---------------------------------------------------------------------------------

def tex_parts(fmt: str, w: int, h: int, mips: int, align: int = 16, origin: int = 0, usage: int = 0,
              detail: int = 0, size2: Optional[Tuple[int, int]] = None, flags: bytes = b"\0\1",
              seed="t") -> List[bytes]:
    """A texture resource as documented: 12 head fields, then per mip level,
    width, height, size, a zero padding part aligning the data to `align`
    (counted from `origin` in the resource), and the data."""
    datas = [noise(mip_bytes(fmt, max(1, w >> i), max(1, h >> i)), (seed, i)) for i in range(mips)]
    s2 = size2 if size2 is not None else (w, h)
    parts = [b"\x01", FOURCC[fmt], u32(mips), u32(usage), u32(detail), u32(w), u32(h), u32(s2[0]), u32(s2[1]),
             u32(sum(len(d) for d in datas)), flags[:1], flags[1:]]
    pos = 39  # 12 head fields: 1 + 9 x 4 + 2 bytes
    for i, d in enumerate(datas):
        pos += 16
        pad = (-(pos - origin)) % align
        parts += [u32(i), u32(max(1, w >> i)), u32(max(1, h >> i)), u32(len(d)), bytes(pad), d]
        pos += pad + len(d)
    return parts


def resource(name: str) -> Resource:
    return Resource(0, 0, 0, 0, 0, 0, bytes(20), 0x08, name)


def blob_parts(n: int, size: int, seed) -> List[bytes]:
    return [noise(size // n + (1 if i < size % n else 0), (seed, i)) for i in range(n)]


def build_bundle(resources, order: Optional[Sequence[int]] = None, irregular: bool = False) -> bytes:
    """A block file laid out as docs/assets.md describes: header, 0x134-byte
    entries, the part table in table order, zeros up to the data start (the
    table size rounded up to 0x800), each resource at an aligned offset with
    the smallest padding, zero-filled.  `order` places the resources in
    another file order.  `irregular` adds what a reader ignores but a writer
    must keep: bytes after the names' NUL, non-zero padding and table gap,
    an extra gap after one resource, and larger header maxima."""
    count = len(resources)
    all_parts = [p for _, _, parts in resources for p in parts]
    table_end = 0x34 + count * 0x134 + len(all_parts) * 4
    data_start = (table_end + ALIGN - 1) // ALIGN * ALIGN
    order = list(order) if order is not None else list(range(count))
    offsets: Dict[int, Tuple[int, int, int]] = {}
    data = bytearray()
    for i in order:
        blob = b"".join(resources[i][2])
        pad = (-len(blob)) % ALIGN
        offsets[i] = (data_start + len(data) if blob else 0, len(blob), pad)
        fill = b"\xAB" * pad if irregular else bytes(pad)
        data += blob + (fill if blob else b"")
        if irregular and i == order[0] and blob:
            data += b"\xEE" * ALIGN  # a gap nobody points at
    entries = b""
    first = 0
    for i, (rtype, name, parts) in enumerate(resources):
        off, size, pad = offsets[i]
        name_field = name.encode().ljust(263, b"\0")
        if irregular:
            name_field = (name.encode() + b"\0" + b"junk%d" % i).ljust(263, b"\0")
        entries += struct.pack("<5I", off, size, pad if size else 0, first, len(parts))
        entries += hashlib.sha1(name.encode()).digest() + bytes([rtype]) + name_field + u32(0xFFFFFFFF)
        first += len(parts)
    max_res = max(len(b"".join(p)) for _, _, p in resources)
    max_part = max(len(p) for p in all_parts)
    if irregular:
        max_res, max_part = max_res + 0x10000, max_part + 0x10000
    head = struct.pack("<8I", 0xC0000001, ALIGN, data_start, len(data), max_res, max_part, count, len(all_parts))
    head += hashlib.sha1(b"header").digest()
    table = head + entries + b"".join(u32(len(p)) for p in all_parts)
    gap = (b"\xCD" if irregular else b"\0") * (data_start - len(table))
    return table + gap + bytes(data)


def level_resources(filler_parts: int = 0) -> list:
    res = [
        (0x08, "wall_d", tex_parts("DXT1", 64, 64, 7, seed="wall")),
        (0x0A, "WallMat", blob_parts(10, 300, "mat")),
        (0x08, "floor_d", tex_parts("A8R8G8B8", 16, 16, 5, usage=1, detail=3, seed="floor")),
        (0x04, "Mesh", blob_parts(3, 5000, "mesh")),
        (0x08, "sky_e", tex_parts("DXT5", 32, 32, 6, usage=6, size2=(0, 0), flags=b"\x02\x00", seed="sky")),
        (0x08, "glass_d", tex_parts("DXT3", 64, 16, 7, seed="glass")),
        (0x08, "hud_x", tex_parts("X8R8G8B8", 8, 8, 1, seed="hud")),
    ]
    if filler_parts:
        res.append((0x05, "hull--1 1 1 1", blob_parts(filler_parts, filler_parts * 3, "hull")))
    return res


def read_all(data: bytes) -> Dict[str, Tuple[int, List[bytes]]]:
    """Every resource's type and parts, by name, read with ibt.py (split()
    checks that the parts cover each resource)."""
    with IBT("check.ibt", data=data) as b:
        return {r.name: (r.type, b.split(r)) for r in b.resources}


def check_textures(data: bytes) -> Dict[str, Texture]:
    """Parse every texture with t3texture.parse_texture, whose PartReader
    checks that each field is exactly one part."""
    with IBT("check.ibt", data=data) as b:
        return {r.name: parse_texture(r, b.split(r)) for r in b.of_type(0x08)}


# --- the writer ------------------------------------------------------------------------------------------

def test_writer() -> None:
    plain = build_bundle(level_resources())
    w = BlockWriter(plain)
    assert w.write() == plain
    assert all(holds for _, holds in survey(w)), [s for s, h in survey(w) if not h]

    odd = build_bundle(level_resources() + [(0x15, "TS_empty", [])], order=[3, 0, 6, 7, 2, 5, 1, 4],
                       irregular=True)
    w = BlockWriter(odd)
    assert w.write() == odd, "an irregular bundle must round-trip byte for byte"
    failing = {s for s, h in survey(w) if not h}
    assert {"resources are in table order in the file", "padding bytes are zero", "names are NUL-padded",
            "header: largest resource size = the largest size"} <= failing, failing
    assert w.locate(0x34 + 2 * 0x134 + 0x30) == "table entry 2 (floor_d) +0x30"

    # replacing in the irregular file: everything the reader ignores is kept
    before = read_all(odd)
    new_parts = tex_parts("DXT1", 128, 128, 8, seed="wall2")
    w.replace(0, new_parts)
    out = w.write()
    assert not compare_bundles(odd, out, w.replaced_entries())
    after = read_all(out)
    assert after["wall_d"][1] == new_parts and all(after[k] == before[k] for k in before if k != "wall_d")
    n = len(w.resources)
    assert out[0x34:0x34 + n * 0x134] != odd[0x34:0x34 + n * 0x134]
    for i in range(n):  # names with their junk, 20-byte values, load filters
        e = slice(0x34 + i * 0x134 + 0x14, 0x34 + (i + 1) * 0x134)
        assert out[e] == odd[e]
    assert out[0x20:0x34] == odd[0x20:0x34] and out[:8] == odd[:8]
    with IBT("odd.ibt", data=odd) as a, IBT("out.ibt", data=out) as b:
        assert b.max_resource_size == a.max_resource_size  # kept: it was larger than any resource
        assert b.data_start + b.data_size == len(out)
        # the extra gap after the first resource in file order moved with it
        mesh = b.find("Mesh")
        assert out[mesh.offset + mesh.size + mesh.padding:][:ALIGN] == b"\xEE" * ALIGN
        empty_a, empty_b = a.find("TS_empty"), b.find("TS_empty")
        assert empty_b.size == 0 and empty_b.first_part == len(b.part_sizes)  # parts after the grown range
        assert empty_a.first_part == len(a.part_sizes)

    # the table crosses an alignment boundary: the data start and every offset move
    base = 0x34 + 8 * 0x134 + sum(len(p) for _, _, p in level_resources()) * 4
    filler = (0x1000 - 8 - base) // 4
    data = build_bundle(level_resources(filler))
    with IBT("x.ibt", data=data) as b:
        assert b.data_start == 0x1000, hex(b.data_start)
    before = read_all(data)
    w = BlockWriter(data)
    big = tex_parts("DXT1", 256, 256, 9, seed="big")  # 2 more mips: 12 more parts
    w.replace(0, big)
    out = w.write()
    assert not compare_bundles(data, out, w.replaced_entries())
    with IBT("out.ibt", data=out) as b:
        assert b.data_start == 0x1800
        assert all(r.offset % ALIGN == 0 and r.padding == (-r.size) % ALIGN for r in b.resources)
        assert b.data_start + b.data_size == len(out)
        assert b.max_resource_size == max(r.size for r in b.resources) == len(b"".join(big))
        assert b.max_part_size == max(b.part_sizes) == len(big[-6 * 9 + 5])
        assert len(b.part_sizes) == len(BlockWriter(data).part_sizes) + 12
        assert BlockWriter(out).write() == out
        assert all(h for s, h in survey(BlockWriter(out))), [s for s, h in survey(BlockWriter(out)) if not h]
    after = read_all(out)
    assert all(after[k] == before[k] for k in before if k != "wall_d")
    tex = check_textures(out)
    assert (tex["wall_d"].width, len(tex["wall_d"].mips)) == (256, 9)
    # and back down: the table shrinks and the data start follows it
    w = BlockWriter(out)
    w.replace(0, before["wall_d"][1])
    assert w.write() == data, "putting the original parts back must give the original file"
    small = tex_parts("DXT1", 4, 4, 1, seed="small")
    w.replace(0, small)
    out2 = w.write()
    assert not compare_bundles(out, out2, w.replaced_entries())
    with IBT("small.ibt", data=out2) as b:
        assert b.data_start == 0x1000 and len(out2) < len(data)

    # refusals
    bad = bytearray(plain)
    struct.pack_into("<I", bad, 0x34 + 0x134, struct.unpack_from("<I", bad, 0x34)[0] + 16)  # 2nd inside 1st
    try:
        BlockWriter(bytes(bad))
        raise AssertionError("overlapping resources not refused")
    except LayoutError as ex:
        assert "overlap" in str(ex)
    bad = bytearray(plain)
    struct.pack_into("<I", bad, 8, 0x40)
    try:
        BlockWriter(bytes(bad))
        raise AssertionError("a data start inside the tables was not refused")
    except LayoutError as ex:
        assert "data start" in str(ex)
    w = BlockWriter(build_bundle(level_resources() + [(0x15, "TS_empty", [])]))
    try:
        w.replace(7, [b"x"])
        raise AssertionError("an empty resource cannot be replaced")
    except LayoutError:
        pass
    print("block-file writer: round trip, relayout, refusals: ok")


# --- textures and DDS ------------------------------------------------------------------------------------

def test_textures() -> None:
    rules = [(16, 0), (128, 0), (32, 39), (4, 0), (2048, 0)]
    shapes = [("DXT1", 64, 64, 7), ("DXT3", 128, 32, 8), ("DXT5", 32, 32, 3), ("A8R8G8B8", 16, 8, 5),
              ("X8R8G8B8", 8, 8, 4), ("DXT1", 4, 4, 1), ("DXT5", 256, 256, 9)]
    for align, origin in rules:
        frame = "resource" if origin == 0 else "chain"
        for fmt, w, h, mips in shapes:
            parts = tex_parts(fmt, w, h, mips, align, origin, usage=5, detail=2, seed=(fmt, w, align))
            info_rules = rules_for([len(p) for p in parts])
            assert PadRule(align, frame) in info_rules, (fmt, align, frame)
            orig = parse_texture(resource("t"), parts)
            dds = to_dds(orig)
            new = parse_dds(dds, "t")
            assert (new.format, new.width, new.height, len(new.mips)) == (fmt, w, h, mips)
            enc = texture_parts(encode_replacement(orig, new, PadRule(align, frame)))
            assert enc == parts, (fmt, w, h, align, frame)
            assert texture_parts(orig) == parts  # the exact inverse of parse_texture
    # a full chain pins the rule down
    one = rules_for([len(p) for p in tex_parts("DXT1", 256, 256, 9, 16)])
    assert one == {PadRule(16, "resource")}, one
    # usage values and the two bytes are kept; the second size follows the first, or stays 0
    orig = parse_texture(resource("sky"),
                         tex_parts("DXT5", 32, 32, 6, usage=6, detail=4, size2=(0, 0), flags=b"\x02\x07"))
    new = parse_dds(to_dds(Texture("x", "DXT1", 64, 64, 0, 0, [Mip(64 >> i, 64 >> i, bytes(mip_bytes(
        "DXT1", 64 >> i, 64 >> i))) for i in range(3)])))
    t = encode_replacement(orig, new, PadRule(16, "resource"))
    assert (t.usage, t.usage_detail, t.flag_bytes, t.size2, t.total) == (6, 4, b"\x02\x07", (0, 0),
                                                                       2048 + 512 + 128)
    orig.size2 = (32, 32)
    assert encode_replacement(orig, new, PadRule(16, "resource")).size2 == (64, 64)

    # DDS refusals
    good = to_dds(Texture("x", "DXT1", 8, 8, 0, 0, [Mip(8, 8, bytes(32)), Mip(4, 4, bytes(8))]))

    def refused(data: bytes, text: str) -> None:
        try:
            parse_dds(data)
        except DDSError as ex:
            assert text in str(ex), (text, str(ex))
            return
        raise AssertionError(f"DDS not refused: {text}")

    def patched(off: int, fmt: str, *vals) -> bytes:
        b = bytearray(good)
        struct.pack_into(fmt, b, off, *vals)
        return bytes(b)

    refused(patched(84, "4s", b"DX10"), "DX10")
    refused(patched(84, "4s", b"DXT2"), "premultiplied")
    refused(patched(16, "I", 12), "not a power of two")
    refused(patched(112, "I", 0x200 | 0xFE00), "cube maps")
    refused(good[:-1], "ends inside mip 1")
    refused(good + b"\0" * 8, "bytes after the last mip")
    refused(patched(28, "I", 5), "at most 4")
    refused(b"XXXX" + good[4:], "not a DDS file")
    argb = bytearray(to_dds(Texture("x", "A8R8G8B8", 2, 2, 0, 0, [Mip(2, 2, bytes(16))])))
    assert parse_dds(bytes(argb)).format == "A8R8G8B8"
    struct.pack_into("<I", argb, 80, 0x41)
    assert parse_dds(bytes(argb)).format == "A8R8G8B8"
    struct.pack_into("<4I", argb, 92, 0xFF, 0xFF00, 0xFF0000, 0xFF000000)  # A8B8G8R8
    refused(bytes(argb), "not supported")
    struct.pack_into("<I", argb, 80, 0x20000)  # luminance
    refused(bytes(argb), "not supported")
    xrgb = to_dds(Texture("x", "X8R8G8B8", 2, 2, 0, 0, [Mip(2, 2, bytes(16))]))
    assert parse_dds(xrgb).format == "X8R8G8B8"
    b = bytearray(xrgb)
    struct.pack_into("<I", b, 20, 12)  # pitch
    refused(bytes(b), "pitch")
    print("texture encoding (DXT1/3/5, A8R8G8B8, X8R8G8B8), padding rules, DDS reader: ok")


# --- packs in a stand-in game folder ------------------------------------------------------------------------

def dds_file(path: Path, fmt: str, w: int, h: int, mips: int, seed) -> bytes:
    tex = Texture(path.stem, fmt, w, h, 0, 0, [Mip(max(1, w >> i), max(1, h >> i), noise(
        mip_bytes(fmt, max(1, w >> i), max(1, h >> i)), (seed, i))) for i in range(mips)])
    path.parent.mkdir(parents=True, exist_ok=True)
    data = to_dds(tex)
    path.write_bytes(data)
    return b"".join(m.data for m in tex.mips[:1])


def sha(path: Path) -> str:
    return hashlib.sha256(path.read_bytes()).hexdigest()


def top_mip(path: Path, name: str) -> bytes:
    return check_textures(path.read_bytes())[name].mips[0].data


def test_packs() -> None:
    root = OUT / "packs"
    shutil.rmtree(root, ignore_errors=True)
    game, state_dir = root / "game", root / "state"
    maps = game / "Content" / "T3" / "Maps"
    maps.mkdir(parents=True)
    originals = {
        "Level1.ibt": build_bundle(level_resources()),
        "Kernel_GFXALL.ibt": build_bundle([(0x08, "wall_d", tex_parts("DXT1", 32, 32, 6, seed="kwall")),
                                           (0x08, "gui_x", tex_parts("A8R8G8B8", 16, 16, 5, seed="gui")),
                                           (0x1D, "Shader", blob_parts(2, 900, "sh"))]),
        "MainMenu_GFXALL.ibt": build_bundle([(0x08, "menu_d", tex_parts("DXT5", 64, 64, 7, seed="menu"))]),
    }
    for name, data in originals.items():
        (maps / name).write_bytes(data)
    (maps / "Level1.gmp").write_bytes(b"not touched")

    p1, p2, p3, bad = root / "p1", root / "p2", root / "p3", root / "bad"
    wall1 = dds_file(p1 / "textures" / "wall_d.dds", "DXT1", 64, 64, 7, "w1")
    floor1 = dds_file(p1 / "textures" / "floor_d.dds", "A8R8G8B8", 32, 32, 6, "f1")
    (p1 / "mod.json").write_text("{}")
    wall2 = dds_file(p2 / "WALL_D.dds", "DXT1", 128, 128, 3, "w2")  # a bare textures folder, other case
    gui3 = dds_file(p3 / "textures" / "gui_x.dds", "A8R8G8B8", 16, 16, 5, "g3")
    p5 = root / "p5"
    floor5 = dds_file(p5 / "textures" / "Floor_D.dds", "A8R8G8B8", 16, 16, 1, "f5")

    def run(fn, *args, **kw) -> Tuple[int, Report]:
        rep = Report(echo=False)
        return fn(game, *args, rep, **kw), rep

    # list
    rep = Report(echo=False)
    assert cmd_list(game, None, False, rep, backup_dir=state_dir) == 0
    wall_rows = [ln for ln in rep.lines if ln.startswith("wall_d ")]
    assert len(wall_rows) == 2 and "Kernel_GFXALL.ibt" in rep.text() and "menu_d" in rep.text(), rep.text()
    assert rep.lines[-1] == "list: 7 texture names in 3 bundles", rep.lines[-1]
    rep = Report(echo=False)
    assert cmd_list(game, "level1", False, rep, backup_dir=state_dir) == 0
    assert "menu_d" not in rep.text() and "gui_x" not in rep.text() and "Level1.ibt" in rep.text()

    # check: warnings and errors
    code, rep = run(cmd_check, [p1, p2], backup_dir=state_dir)
    assert code == 0 and rep.errors == 0, rep.text()
    text = rep.text()
    assert "larger than the original 64x64 (in Level1.ibt" in text  # wall 128 > 64
    assert "is A8R8G8B8" not in text and "floor_d.dds: is 32x32, larger" in text
    assert "p1/textures/wall_d.dds: overridden by p2/WALL_D.dds" in text
    assert rep.lines[-1].startswith("check: ok: 2 textures from 2 packs"), rep.lines[-1]
    dds_file(bad / "textures" / "nosuch_d.dds", "DXT1", 8, 8, 1, "x")
    dds_file(bad / "textures" / "sky_e.dds", "DXT1", 64, 32, 1, "x")  # format and aspect ratio differ
    (bad / "textures" / "wall_d.dds").write_bytes(b"DDS " + bytes(200))
    (bad / "textures" / "readme.txt").write_text("hi")
    code, rep = run(cmd_check, [bad], backup_dir=state_dir)
    text = rep.text()
    assert code == 1 and rep.errors == 2, text
    assert "no texture named 'nosuch_d'" in text and "wall_d.dds: bad DDS header" in text
    assert "sky_e.dds: is DXT1, the original is DXT5" in text and "another aspect ratio" in text
    assert "readme.txt: not a .dds file" in text and rep.lines[-1].startswith("check: FAILED")
    code, rep = run(cmd_check, [root / "missing"], backup_dir=state_dir)
    assert code == 1 and "no such pack folder" in rep.text()

    # apply refuses bad packs and writes nothing
    code, rep = run(cmd_apply, [p1, bad], backup_dir=state_dir)
    assert code == 1 and "nothing was written" in rep.lines[-1] and not state_dir.exists()
    assert all((maps / n).read_bytes() == d for n, d in originals.items())

    # dry run
    code, rep = run(cmd_apply, [p1, p2], backup_dir=state_dir, dry_run=True)
    assert code == 0 and rep.lines[-1].startswith("apply: dry run") and not state_dir.exists(), rep.text()
    assert all((maps / n).read_bytes() == d for n, d in originals.items())

    # apply: later packs win, both bundles holding wall_d are patched
    code, rep = run(cmd_apply, [p1, p2], backup_dir=state_dir)
    assert code == 0, rep.text()
    assert rep.lines[-1] == "apply: ok: 2 textures from 2 packs; 2 bundles patched, 0 unchanged", rep.lines[-1]
    assert top_mip(maps / "Level1.ibt", "wall_d") == wall2 and top_mip(maps / "Kernel_GFXALL.ibt", "wall_d") == wall2
    assert top_mip(maps / "Level1.ibt", "floor_d") == floor1
    assert (maps / "MainMenu_GFXALL.ibt").read_bytes() == originals["MainMenu_GFXALL.ibt"]
    assert (state_dir / "Level1.ibt").read_bytes() == originals["Level1.ibt"]
    assert (state_dir / "Kernel_GFXALL.ibt").read_bytes() == originals["Kernel_GFXALL.ibt"]
    doc = json.loads((state_dir / MANIFEST).read_text())
    rec = doc["bundles"]["content/t3/maps/level1.ibt"]
    assert rec["textures"]["wall_d"]["file"] == "WALL_D.dds" and rec["textures"]["floor_d"]["file"] == "floor_d.dds"
    assert rec["installed"]["sha256"] == sha(maps / "Level1.ibt")
    assert rec["original"]["sha256"] == hashlib.sha256(originals["Level1.ibt"]).hexdigest()
    lvl = check_textures((maps / "Level1.ibt").read_bytes())
    assert (lvl["wall_d"].usage, lvl["floor_d"].usage, lvl["floor_d"].usage_detail) == (0, 1, 3)
    assert not compare_bundles(originals["Level1.ibt"], (maps / "Level1.ibt").read_bytes(),
                               {0: read_all((maps / "Level1.ibt").read_bytes())["wall_d"][1],
                                2: read_all((maps / "Level1.ibt").read_bytes())["floor_d"][1]})
    # list and check read the originals while bundles are patched
    rep = Report(echo=False)
    cmd_list(game, None, False, rep, backup_dir=state_dir)
    assert any(ln.startswith("wall_d ") and "64x64" in ln for ln in rep.lines), rep.text()

    # again: nothing to do, nothing touched
    stamps = {n: (maps / n).stat().st_mtime_ns for n in originals}
    code, rep = run(cmd_apply, [p1, p2], backup_dir=state_dir)
    assert code == 0 and rep.lines[-1].endswith("0 bundles patched, 2 unchanged"), rep.lines
    assert stamps == {n: (maps / n).stat().st_mtime_ns for n in originals}

    # fewer packs: rebuilt from the backup, not stacked on the patched file
    orig_lvl = check_textures(originals["Level1.ibt"])
    code, rep = run(cmd_apply, [p1], backup_dir=state_dir)
    assert code == 0 and rep.lines[-1].endswith("2 bundles patched, 0 unchanged"), rep.lines
    assert top_mip(maps / "Level1.ibt", "wall_d") == wall1 and top_mip(maps / "Level1.ibt", "floor_d") == floor1
    assert top_mip(maps / "Kernel_GFXALL.ibt", "wall_d") == wall1
    code, rep = run(cmd_apply, [p5], backup_dir=state_dir)
    assert code == 0 and rep.lines[-1].endswith("1 bundle patched, 0 unchanged, 1 restored"), rep.lines
    assert (maps / "Kernel_GFXALL.ibt").read_bytes() == originals["Kernel_GFXALL.ibt"]  # no longer affected
    assert not (state_dir / "Kernel_GFXALL.ibt").exists()
    assert top_mip(maps / "Level1.ibt", "floor_d") == floor5
    assert top_mip(maps / "Level1.ibt", "wall_d") == orig_lvl["wall_d"].mips[0].data  # not stacked
    code, rep = run(cmd_apply, [p2, p3], backup_dir=state_dir)
    assert code == 0, rep.text()
    lvl = check_textures((maps / "Level1.ibt").read_bytes())
    assert lvl["floor_d"].mips[0].data == orig_lvl["floor_d"].mips[0].data  # p5's floor is gone
    assert lvl["wall_d"].mips[0].data == wall2 and top_mip(maps / "Kernel_GFXALL.ibt", "gui_x") == gui3
    assert top_mip(maps / "Kernel_GFXALL.ibt", "wall_d") == wall2

    # an interrupted run: the record names the new file, the game still holds the previous one
    doc = json.loads((state_dir / MANIFEST).read_text())
    rec = doc["bundles"]["content/t3/maps/level1.ibt"]
    rec["previous"], rec["installed"], rec["recipe"] = rec["installed"], {"size": 1, "sha256": "0" * 64}, "x"
    (state_dir / MANIFEST).write_text(json.dumps(doc))
    code, rep = run(cmd_apply, [p2, p3], backup_dir=state_dir)
    assert code == 0 and "2 unchanged" not in rep.lines[-1], rep.text()
    assert "previous" not in json.loads((state_dir / MANIFEST).read_text())["bundles"]["content/t3/maps/level1.ibt"]

    # the game's file cannot be written (the game is running): the record stays as it was
    import t3texpack
    real_write = t3texpack._write_atomic

    class Killed(BaseException):
        pass

    def failing(exc):
        def write(path: Path, data: bytes) -> None:
            if path.suffix == ".ibt":
                raise exc
            real_write(path, data)
        return write

    def snapshot() -> tuple:
        return tuple((f).read_bytes() for f in (state_dir / MANIFEST, maps / "Level1.ibt", maps / "Kernel_GFXALL.ibt"))

    before = snapshot()
    t3texpack._write_atomic = failing(PermissionError("in use"))
    try:
        code, rep = run(cmd_apply, [p1], backup_dir=state_dir)
    finally:
        t3texpack._write_atomic = real_write
    assert code == 1 and rep.text().count("is the game running?") == 2, rep.text()
    assert before == snapshot()
    # killed between saving the record and replacing the file (the Kernel comes
    # first): the next run still knows the file the game holds
    t3texpack._write_atomic = failing(Killed())
    try:
        run(cmd_apply, [p1], backup_dir=state_dir)
        raise AssertionError("not killed")
    except Killed:
        pass
    finally:
        t3texpack._write_atomic = real_write
    assert before[1:] == snapshot()[1:]
    kernel = json.loads((state_dir / MANIFEST).read_text())["bundles"]["content/t3/maps/kernel_gfxall.ibt"]
    assert kernel["previous"]["sha256"] == hashlib.sha256(before[2]).hexdigest(), kernel
    code, rep = run(cmd_apply, [p1], backup_dir=state_dir)
    assert code == 0 and top_mip(maps / "Level1.ibt", "wall_d") == wall1, rep.text()
    assert top_mip(maps / "Kernel_GFXALL.ibt", "wall_d") == wall1
    code, rep = run(cmd_apply, [p2, p3], backup_dir=state_dir)
    assert code == 0 and top_mip(maps / "Level1.ibt", "wall_d") == wall2, rep.text()

    # a bundle changed by something else is left alone, by apply and by restore
    foreign = bytearray((maps / "Level1.ibt").read_bytes())
    with IBT("l.ibt", data=bytes(foreign)) as b:
        mesh = b.find("Mesh")
    foreign[mesh.offset] ^= 0xFF
    (maps / "Level1.ibt").write_bytes(bytes(foreign))
    code, rep = run(cmd_apply, [p2, p3], backup_dir=state_dir)
    assert code == 1 and "changed outside t3texpack" in rep.text() and "1 left alone" in rep.lines[-1], rep.text()
    assert (maps / "Level1.ibt").read_bytes() == bytes(foreign)
    code, rep = run(cmd_restore, backup_dir=state_dir)
    assert code == 1 and "1 bundle restored, 1 left alone" in rep.lines[-1], rep.lines
    assert (maps / "Kernel_GFXALL.ibt").read_bytes() == originals["Kernel_GFXALL.ibt"]
    assert (maps / "Level1.ibt").read_bytes() == bytes(foreign)
    # deleting the backup accepts the changed file as the new original
    (state_dir / "Level1.ibt").unlink()
    code, rep = run(cmd_apply, [p1], backup_dir=state_dir)
    assert code == 0, rep.text()
    assert (state_dir / "Level1.ibt").read_bytes() == bytes(foreign)
    assert top_mip(maps / "Level1.ibt", "wall_d") == wall1
    code, rep = run(cmd_apply, [], backup_dir=state_dir)  # no packs: restore
    assert code == 0 and rep.lines[-1] == "apply: ok: 2 bundles restored", rep.lines
    assert (maps / "Level1.ibt").read_bytes() == bytes(foreign)
    (maps / "Level1.ibt").write_bytes(originals["Level1.ibt"])
    assert not json.loads((state_dir / MANIFEST).read_text())["bundles"]
    assert sorted(p.name for p in state_dir.iterdir()) == [MANIFEST]
    code, rep = run(cmd_restore, backup_dir=state_dir)
    assert code == 0 and rep.lines[-1] == "restore: ok: nothing to restore"

    # a backup without a record, different from the game's file, is not trusted
    (state_dir / "Level1.ibt").write_bytes(b"stale")
    code, rep = run(cmd_apply, [p1], backup_dir=state_dir)
    assert code == 1 and "no record of" in rep.text(), rep.text()
    (state_dir / "Level1.ibt").unlink()

    # the record belongs to one game folder
    run(cmd_apply, [p1], backup_dir=state_dir)
    other = root / "other-game"
    (other / "Content" / "T3" / "Maps").mkdir(parents=True)
    try:
        State(other, state_dir)
        raise AssertionError("another game folder was accepted")
    except TexPackError as ex:
        assert "another game folder" in str(ex)

    # selfcheck on the stand-in game (patched bundles: their originals)
    code, rep = run(cmd_selfcheck, [], backup_dir=state_dir)
    assert code == 0 and rep.lines[-1] == "selfcheck: ok: 3 of 3 bundles passed", rep.text()
    assert "Level1.ibt is patched: checking its original" in rep.text()
    assert "re-encoded from their own DDS: 5 of 5 identical" in rep.text(), rep.text()
    code, rep = run(cmd_restore, backup_dir=state_dir)
    assert code == 0 and all((maps / n).read_bytes() == d for n, d in originals.items())

    # a texture whose padding breaks the bundle's rule cannot be replaced
    mixed = build_bundle([(0x08, "a", tex_parts("DXT1", 64, 64, 7, 16, seed="a")),
                          (0x08, "b", tex_parts("DXT1", 64, 64, 7, 16, seed="b")),
                          (0x08, "c", tex_parts("DXT1", 64, 64, 7, 128, seed="c"))])
    with IBT("m.ibt", data=mixed) as b:
        found = find_rule(texture_head(b, r) for r in b.resources)
    assert found.rule == PadRule(16, "resource") and (found.explained, found.total) == (2, 3)

    def heads(data: bytes) -> list:
        with IBT("h.ibt", data=data) as b:
            return [texture_head(b, r) for r in b.resources]

    # single-mip textures cannot tell 16 from 32 or 64: the other bundles decide
    singles = heads(build_bundle([(0x08, "ui", tex_parts("DXT1", 4, 4, 1, 16, seed="ui"))]))
    full = heads(build_bundle([(0x08, "f", tex_parts("DXT1", 64, 64, 7, 16, seed="f"))]))
    alone = find_rule(singles)
    assert alone.rule == PadRule(64, "resource") and PadRule(16, "resource") in alone.also, alone
    assert find_rule(singles, rule_counts(full + singles)[0]).rule == PadRule(16, "resource")
    (maps / "Mixed.ibt").write_bytes(mixed)
    dds_file(root / "p4" / "c.dds", "DXT1", 64, 64, 7, "c4")
    code, rep = run(cmd_check, [root / "p4"], backup_dir=state_dir)
    assert code == 1 and "follows no rule" in rep.text(), rep.text()
    code, rep = run(cmd_selfcheck, ["Mixed"], backup_dir=state_dir)
    assert code == 1 and "1 textures do not follow the padding rule" in rep.text(), rep.text()
    (maps / "Mixed.ibt").unlink()
    print("texture packs: list, check, apply (precedence, idempotency, fewer packs, interruption, "
          "foreign changes), restore, selfcheck: ok")

    # the command line, as the launcher runs it
    env = {**os.environ, "T3_GAME_DIR": str(game), "T3SDK_BUILD_DIR": str(root / "build"),
           "PYTHONIOENCODING": "utf-8"}
    tool = str(Path(__file__).resolve().parent / "t3texpack.py")

    def cli(*args: str) -> subprocess.CompletedProcess:
        return subprocess.run([sys.executable, tool, *args], capture_output=True, text=True, env=env)

    r = cli("list", "--json")
    assert r.returncode == 0, r.stderr
    doc = json.loads(r.stdout)
    assert {t["name"] for t in doc["textures"]} >= {"wall_d", "menu_d", "gui_x"}
    assert [t["bundles"] for t in doc["textures"] if t["name"] == "gui_x"] == [["Kernel_GFXALL.ibt"]]
    r = cli("check", "--pack", str(bad))
    assert r.returncode == 1 and "error: " in r.stderr and r.stdout.splitlines()[-1].startswith("check: FAILED")
    r = cli("apply", "--pack", str(p1), "--pack", str(p2))
    assert r.returncode == 0 and r.stdout.splitlines()[-1].startswith("apply: ok: 2 textures"), (r.stdout, r.stderr)
    assert (root / "build" / "assets" / "backup" / MANIFEST).is_file()
    r = cli("--selfcheck")
    assert r.returncode == 0 and r.stdout.splitlines()[-1].startswith("selfcheck: ok"), (r.stdout, r.stderr)
    r = cli("restore")
    assert r.returncode == 0 and r.stdout.splitlines()[-1] == "restore: ok: 2 bundles restored", r.stdout
    assert all((maps / n).read_bytes() == d for n, d in originals.items())
    r = cli("check")
    assert r.returncode == 1 and "at least one --pack" in r.stderr
    r = cli()
    assert r.returncode == 2
    print("t3texpack.py command line: ok")


def main() -> None:
    OUT.mkdir(parents=True, exist_ok=True)
    test_writer()
    test_textures()
    test_packs()


if __name__ == "__main__":
    main()
    print("texture pack self-tests passed")
