#!/usr/bin/env python3
"""Self-test for tools/assets using synthetic data only (no game files).

Builds a tiny Flesh-style Unreal package, a map-like package and a tiny .ibt
block file in build/assets/selftest/, then checks that the parsers, the
texture and mesh converters, the glTF writer, the coordinate conversion, the
package writer and the map edits (t3pack.py) agree with what was written.
selftest_texpack.py then checks the block-file writer and texture packs
(ibtwrite.py, t3texpack.py) in a stand-in game folder.
Run: python tools/assets/selftest.py
"""

from __future__ import annotations

import hashlib
import json
import math
import os
import shutil
import struct
import subprocess
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from ibt import IBT, PartReader  # noqa: E402
from t3common import BUILD_DIR, Reader, godot_basis, u2g, write_index  # noqa: E402
from t3mesh import ResourceSet, mesh_to_gltf, parse_static_mesh  # noqa: E402
from t3pack import (EditsError, apply_edits, check_source, install, load_edits, original_source,  # noqa: E402
                    restore, roundtrip, write_verified)
from t3props import PropertyNames, parse_declarations, parse_enums  # noqa: E402
from t3texture import decode_rgba, parse_material, parse_texture, to_dds  # noqa: E402
from upkg import Package, prop_value, struct_fields  # noqa: E402
from upkgwrite import PackageWriter, enc_index, first_difference  # noqa: E402
import selftest_texpack  # noqa: E402

OUT = BUILD_DIR / "selftest"


def fstring(s: str) -> bytes:
    return write_index(len(s) + 1) + s.encode("latin-1") + b"\0"


# --- synthetic package ------------------------------------------------------------------

def build_package() -> bytes:
    names = ["None", "Core", "Engine", "Package", "Class", "StaticMeshActor", "Actor0", "Location", "Vector",
             "X", "Y", "Z", "Rotation", "Rotator", "Yaw", "Name", "Skin", "Tag"]
    n = {s: i for i, s in enumerate(names)}

    def tag(name: str, info: int, payload: bytes, struct_name: str | None = None) -> bytes:
        out = write_index(n[name]) + bytes([info])
        if struct_name:
            out += write_index(n[struct_name])
        return out + payload

    def sized(name: str, ptype: int, payload: bytes, struct_name: str | None = None) -> bytes:
        # size code 5: one size byte follows
        return tag(name, ptype | 0x50, bytes([len(payload)]) + payload, struct_name)

    vec = (tag("X", 0x24, struct.pack("<f", 100.0)) + tag("Y", 0x24, struct.pack("<f", -50.0)) +
           tag("Z", 0x24, struct.pack("<f", 25.0)) + write_index(0))
    rot = tag("Yaw", 0x22, struct.pack("<i", 16384)) + write_index(0)
    props = sized("Location", 10, vec, "Vector") + sized("Rotation", 10, rot, "Rotator") + write_index(0)
    mesh_struct = (sized("Name", 13, fstring("TestMesh")) + sized("Skin", 13, fstring("Default")) + write_index(0))
    gamesys = (struct.pack("<III", 0x00080038, 1, len(mesh_struct)) + mesh_struct +
               struct.pack("<III", 0x0100004F, 1, 1) + write_index(n["StaticMeshActor"]) +
               struct.pack("<I", 0))
    state = write_index(-2) + write_index(-2) + struct.pack("<QI", 0xFFFFFFFFFFFFFFFF, 0) + write_index(-1)
    actor = state + props + gamesys + struct.pack("<I", 0) + struct.pack("<I", 0)

    body = bytearray()
    header_size = 0x4C
    name_table = b"".join(fstring(s) + struct.pack("<I", 0x70010) for s in names)
    data_off = header_size + len(name_table)
    imports = (write_index(n["Core"]) + write_index(n["Package"]) + struct.pack("<i", 0) + write_index(n["Engine"]) +
               write_index(n["Core"]) + write_index(n["Class"]) + struct.pack("<i", -1) +
               write_index(n["StaticMeshActor"]))
    import_off = data_off + len(actor)
    extra_off = import_off + len(imports)
    extra = b"".join(struct.pack("<II", 1, 0) for _ in range(32))
    export_off = extra_off + len(extra)
    exports = (write_index(-2) + write_index(0) + struct.pack("<i", 0) + write_index(n["Actor0"]) +
               struct.pack("<I", 0x02070001) + write_index(len(actor)) + write_index(data_off))
    head = struct.pack("<IHHIIIIIIII", 0x9E2A83C1, 95, 133, 1, len(names), header_size, 1, export_off,
                       2, import_off, 0)
    head += b"\x11" * 16 + struct.pack("<III", 1, 1, len(names)) + struct.pack("<II", 0, extra_off)
    assert len(head) == header_size
    body += head + name_table + actor + imports + extra + exports
    return bytes(body)


def test_package() -> None:
    path = OUT / "synthetic.gmp"
    path.write_bytes(build_package())
    pkg = Package(path)
    assert (pkg.file_version, pkg.licensee_version) == (95, 133)
    assert pkg.depends_offset is not None and pkg.ion_unknown == 0
    e = pkg.exports[0]
    assert pkg.export_class(e) == "StaticMeshActor" and e.name == "Actor0"
    a = pkg.read_actor(e)
    assert a.parse_error is None, a.parse_error
    loc = struct_fields(prop_value(a.properties, "Location"))
    assert (loc["X"], loc["Y"], loc["Z"]) == (100.0, -50.0, 25.0)
    assert struct_fields(prop_value(a.properties, "Rotation"))["Yaw"] == 16384
    mesh = struct_fields(a.block(0x38).value)
    assert mesh == {"Name": "TestMesh", "Skin": "Default"}, mesh
    assert a.block(0x4F).value == "StaticMeshActor"
    assert a.links == [] and a.tail == b"\0\0\0\0"
    print("package: ok")


# --- synthetic map for the writer ---------------------------------------------------------------

# "Roll" and "NewTag" are missing on purpose: the edits add them.
MAP_NAMES = ["None", "Core", "Engine", "T3Gamesys", "Package", "Class", "Level", "LevelInfo", "StaticMeshActor",
             "Light", "D_100", "AttachmentLinkDataObject", "MyLevel", "LevelInfo0", "StaticMeshActor0", "D_100_0",
             "Light0", "AttachmentLinkDataObject0", "StaticMeshActor1", "Location", "Vector", "X", "Y", "Z",
             "Rotation", "Rotator", "Pitch", "Yaw", "Name", "Skin", "DrawScale", "Title", "bHidden",
             "m_parentBone", "Bone01", "OldTag"]
MAP_X24 = 0x0BADF00D
# Gamesys property ids of the synthetic property table (see map_property_names).
P_DRAWSCALE, P_MESH, P_TAG, P_LIGHTON, P_LIGHTTYPE, P_BRIGHTNESS, P_DISPLAY, P_HEALTH, P_FLAGS = (
    0x30, 0x38, 0x4F, 0x60, 0x61, 0x62, 0x63, 0x64, 0x65)


def padded_index(v: int, width: int) -> bytes:
    """A compact index written wider than needed (continue bits, zero payload)."""
    b = bytearray(write_index(v))
    b[-1] |= 0x40 if len(b) == 1 else 0x80
    b += b"\x80" * (width - len(b) - 1) + b"\x00"
    assert Reader(bytes(b)).index() == v and len(b) == width
    return bytes(b)


def build_map() -> bytes:
    """A map-like package: Ion summary fields, two generations, an extra table,
    a level object, actors with state frames, tagged Location/Rotation structs,
    gamesys blocks, links and native tails, a link object, a gap between two
    objects, and compact indices written wider than needed."""
    n = {s: i for i, s in enumerate(MAP_NAMES)}

    def tag(name: str, info: int, payload: bytes, struct_name: str | None = None, name_raw: bytes = b"") -> bytes:
        out = (name_raw or write_index(n[name])) + bytes([info])
        return out + (write_index(n[struct_name]) if struct_name else b"") + payload

    def sized(name: str, ptype: int, payload: bytes, struct_name: str | None = None) -> bytes:
        return tag(name, ptype | 0x50, bytes([len(payload)]) + payload, struct_name)

    def fields(**kw) -> bytes:
        out = b""
        for k, v in kw.items():
            out += tag(k, 0x24, struct.pack("<f", v)) if isinstance(v, float) else tag(k, 0x22, struct.pack("<i", v))
        return out + write_index(0)

    def block(pid: int, bits: int, data: bytes) -> bytes:
        return struct.pack("<III", bits << 16 | pid, 1, len(data)) + data

    def actor(state: bytes, props: bytes, blocks: bytes, links=(), tail=b"\x2A\0\0\0") -> bytes:
        return (state + props + write_index(0) + blocks + struct.pack("<I", 0) + struct.pack("<I", len(links))
                + b"".join(write_index(x) for x in links) + tail)

    frame = write_index(-2) + write_index(-2) + struct.pack("<QI", 0xFFFFFFFFFFFFFFFF, 0x1234) + write_index(-1)
    frame0 = write_index(0) + write_index(0) + struct.pack("<QI", 0, 0)  # Node 0: no Offset
    mesh = sized("Name", 13, fstring("TestMesh")) + sized("Skin", 13, fstring("Default")) + write_index(0)
    # "Yaw" with a padded name index: a tag must keep it
    rot_yaw = tag("Yaw", 0x22, struct.pack("<i", 16384), name_raw=padded_index(n["Yaw"], 2)) + write_index(0)
    objects = [
        ("MyLevel", -3, 0x00070004, b"\0" * 13 + struct.pack("<II", 5, 5) + bytes([2, 3, 4, 5, 7]) + b"LEVEL" * 8),
        ("LevelInfo0", -4, 0x02070004, actor(frame, sized("Title", 13, fstring("Synthetic")) +
                                           tag("bHidden", 0xD3, b"\0"), b"")),
        ("StaticMeshActor0", -5, 0x02070004, actor(
            frame, sized("Location", 10, fields(X=100.0, Y=-50.0, Z=25.0), "Vector") +
            sized("Rotation", 10, rot_yaw, "Rotator"),
            block(P_MESH, 0x0008, mesh) + block(P_DRAWSCALE, 0x4010, struct.pack("<f", 1.5)), links=[6])),
        ("D_100_0", -7, 0x02070004, actor(
            frame0, sized("Location", 10, fields(X=1.0, Z=3.0), "Vector"),
            block(P_TAG, 0x0100, write_index(n["OldTag"])) + block(P_LIGHTON, 0x0080, b"\0") +
            block(P_LIGHTTYPE, 0x0200, b"\0") + block(P_DISPLAY, 0x0004, fstring("Old")) +
            block(P_HEALTH, 0x0020, struct.pack("<i", 10)) + block(P_FLAGS, 0x0800, struct.pack("<I", 1)))),
        ("Light0", -6, 0x02070004, actor(
            frame, sized("Location", 10, fields(X=5.0, Y=6.0, Z=7.0), "Vector") +
            sized("Rotation", 10, fields(Pitch=-4096), "Rotator") + tag("DrawScale", 0x24, struct.pack("<f", 2.0)),
            b"")),
        ("AttachmentLinkDataObject0", -8, 0x00070004,
         sized("m_parentBone", 6, write_index(n["Bone01"])) + write_index(0) + struct.pack("<II", 0, 0) +
         write_index(3) + write_index(5)),
        ("StaticMeshActor1", -5, 0x02070004, actor(
            frame, sized("Location", 10, fields(X=-1.0, Y=-2.0, Z=-3.0), "Vector"),
            block(P_DRAWSCALE, 0x4010, struct.pack("<f", 1.0)))),
    ]
    gap_after = "Light0"  # three unassigned bytes follow this object

    gens = [(5, 30), (len(objects), len(MAP_NAMES))]
    header_size = 0x24 + 4 + 16 + 4 + 8 * len(gens) + 8
    names = b"".join(fstring(s) + struct.pack("<I", 0x04070010 if s == "None" else 0x00070010) for s in MAP_NAMES)
    body = bytearray(names)
    placed = []
    for name, cls, flags, data in objects:
        placed.append((header_size + len(body), len(data)))
        body += data
        if name == gap_after:
            body += b"\xEE\xEE\xEE"
    imports = b""
    for i, (cp, cn, pk, on) in enumerate([("Core", "Package", 0, "Engine"), ("Core", "Package", 0, "T3Gamesys"),
                                          ("Core", "Class", -1, "Level"), ("Core", "Class", -1, "LevelInfo"),
                                          ("Core", "Class", -1, "StaticMeshActor"), ("Core", "Class", -1, "Light"),
                                          ("Core", "Class", -2, "D_100"),
                                          ("Core", "Class", -1, "AttachmentLinkDataObject")]):
        on_raw = padded_index(n[on], 2) if i == 7 else write_index(n[on])
        imports += write_index(n[cp]) + write_index(n[cn]) + struct.pack("<i", pk) + on_raw
    import_off = header_size + len(body)
    extra = b"".join(struct.pack(f"<I{len(objects)}I", len(objects), *range(len(objects))) for _ in range(32))
    extra_off = import_off + len(imports)
    export_off = extra_off + len(extra)
    exports = b""
    for i, ((name, cls, flags, data), (off, size)) in enumerate(zip(objects, placed)):
        outer = 0 if i == 0 else 1
        size_raw = padded_index(size, 3) if name == "Light0" else write_index(size)
        exports += (write_index(cls) + write_index(0) + struct.pack("<i", outer) + write_index(n[name]) +
                    struct.pack("<I", flags) + size_raw + write_index(off))
    head = struct.pack("<IHHI6I", 0x9E2A83C1, 95, 133, 1, len(MAP_NAMES), header_size, len(objects), export_off,
                       8, import_off)
    head += struct.pack("<I", MAP_X24) + bytes(range(16)) + struct.pack("<I", len(gens))
    head += b"".join(struct.pack("<II", *g) for g in gens) + struct.pack("<II", 0, extra_off)
    assert len(head) == header_size
    return bytes(head + body + imports + extra + exports)


def map_property_names() -> PropertyNames:
    props = {P_DRAWSCALE: ("DrawScale", "float", "runtimeinstantiated"),
             P_MESH: ("ObjectMesh", "RenderObjectMeshStruct", "inherited"), P_TAG: ("Tag", "name", "inherited"),
             P_LIGHTON: ("bLightOn", "bool", "inherited"),
             P_LIGHTTYPE: ("FleshLightType", "EFleshLightType", "inherited"),
             P_BRIGHTNESS: ("LightBrightness", "float", "inherited"),
             P_DISPLAY: ("DisplayName", "string", "inherited"), P_HEALTH: ("Health", "int", "inherited"),
             P_FLAGS: ("Flags", "bitfield<EFlagBits>", "inherited")}
    return PropertyNames({"properties": {str(k): {"name": a, "type": t, "kind": kind}
                                         for k, (a, t, kind) in props.items()},
                          "enums": {"EFleshLightType": ["FLT_Omni", "FLT_Spot", "FLT_Directional"],
                                    "EFlagBits": ["F_A", "F_B", "F_C"]}})


def test_writer() -> None:
    path = OUT / "synthmap.gmp"
    data = build_map()
    path.write_bytes(data)
    pkg = Package(path)
    assert pkg.ion_unknown == MAP_X24 and pkg.depends_offset is not None and len(pkg.generations) == 2
    assert all(pkg.read_actor(e).parse_error is None for e in pkg.exports if e.flags & 0x02000000)

    # unchanged: byte-identical, padded compact indices kept, extra table understood
    w = PackageWriter(pkg)
    assert w.write() == data
    assert dict(w.padded) == {"imports": 1, "exports": 1} and not w.opaque and len(w.extra or []) == 32
    assert [g.kind for g in w.regions].count("gap") == 1
    assert enc_index(5, padded_index(9, 3)) == padded_index(5, 3) and enc_index(0, b"\x80") == b"\x80"
    rt = roundtrip(path)
    assert rt.ok and rt.lines[0].startswith("identical"), rt.lines
    assert any(ln.startswith("resize test: ok") for ln in rt.lines), rt.lines
    assert any(ln.startswith("actors: 5 of 5") for ln in rt.lines), rt.lines

    # a difference is reported with the region it falls in
    lvl = pkg.find_export("D_100_0")
    bad = bytearray(data)
    bad[lvl.serial_offset + 5] ^= 0xFF
    assert first_difference(data, bytes(bad)) == lvl.serial_offset + 5
    assert w.locate(lvl.serial_offset + 5) == "object #3 D_100_0 (D_100) +0x5"
    assert w.locate(0x24) == "summary, Ion DWORD at 0x24 +0x0"
    assert w.locate(pkg.export_offset + 1).startswith("export table, entry 0 (MyLevel)")

    # edits: values in place, missing struct fields and a missing struct, gamesys
    # blocks changed, resized and added, names added, one value set back to its default
    names = map_property_names()
    sha = hashlib.sha1(data).hexdigest()
    doc = {"format": "t3-map-edits", "version": 1, "level": "synthmap",
           "source": {"file": "synthmap.gmp", "size": len(data), "sha1": sha.upper()},
           "actors": {
               "StaticMeshActor0": {"location": [150.0, -50.0, 25.0], "rotation": [0, 16384.0, 1024],
                                    "draw_scale": 2.5},
               "D_100_0": {"location": [10.0, 20.0, 30.0], "rotation": [0, 8192, 0], "draw_scale": 0.75,
                           "gamesys": {"Tag": "NewTag", "bLightOn": True, "FleshLightType": "flt_spot",
                                       "DisplayName": "A longer display name", "Health": 0, "Flags": ["F_B", "F_C"]}},
               "light0": {"location": [5, 6, 7], "draw_scale": 0.5, "gamesys": {"LightBrightness": 1.25}}}}
    edits = load_edits(doc)
    assert edits["source"]["sha1"] == sha and edits["actors"]["StaticMeshActor0"]["rotation"] == [0, 16384, 1024]
    assert check_source(edits, path).startswith("matches")
    patch = apply_edits(pkg, edits, names)
    out = OUT / "patched" / "synthmap.gmp"
    write_verified(pkg, patch, out)
    new = Package(out)
    assert new.names == MAP_NAMES + ["Roll", "NewTag"], new.names[len(MAP_NAMES):]
    assert new.generations == [(5, 30), (7, len(MAP_NAMES) + 2)] and new.ion_unknown == MAP_X24
    assert new.guid == pkg.guid and new.ion_extra == pkg.ion_extra
    edited = {"StaticMeshActor0", "D_100_0", "Light0"}
    assert sorted(new.exports[i].name for i in patch.edited) == sorted(edited)
    for a, b in zip(pkg.exports, new.exports):
        if a.name not in edited:
            assert pkg.export_bytes(a) == new.export_bytes(b), a.name
    assert new.export_offset != pkg.export_offset and new.export_end - new.export_offset == \
        pkg.export_end - pkg.export_offset
    assert dict(PackageWriter(new).padded) == {"imports": 1, "exports": 1}  # Light0's size stays 3 bytes wide
    grow = sum(len(new.export_bytes(b)) - a.serial_size for a, b in zip(pkg.exports, new.exports))
    assert len(out.read_bytes()) == len(data) + grow + len(fstring("Roll") + fstring("NewTag")) + 8

    def actor(name: str):
        return new.read_actor(new.find_export(name))

    def vec(a, prop: str, keys: str):
        f = struct_fields(prop_value(a.properties, prop))
        return [f.get(k, 0) for k in keys.split()]

    a = actor("StaticMeshActor0")
    assert vec(a, "Location", "X Y Z") == [150.0, -50.0, 25.0]
    assert vec(a, "Rotation", "Pitch Yaw Roll") == [0, 16384, 1024]
    assert "Pitch" not in struct_fields(prop_value(a.properties, "Rotation"))  # still 0, still absent
    assert a.block(P_DRAWSCALE).value == 2.5 and a.links == [6] and a.tail == b"\x2A\0\0\0"
    a = actor("D_100_0")
    assert vec(a, "Location", "X Y Z") == [10.0, 20.0, 30.0] and vec(a, "Rotation", "Pitch Yaw Roll") == [0, 8192, 0]
    assert [b.id for b in a.gamesys] == [0x40100030, 0x0100004F, 0x00800060, 0x02000061, 0x00040063, 0x00200064,
                                         0x08000065]  # DrawScale added in id order, with the package's block id
    assert (a.block(P_DRAWSCALE).value, a.block(P_TAG).value, a.block(P_LIGHTON).value) == (0.75, "NewTag", 1)
    assert (a.block(P_LIGHTTYPE).value, a.block(P_DISPLAY).value) == (1, "A longer display name")
    assert a.block(P_HEALTH).value == 0 and a.block(P_FLAGS).value == 0b110  # the default, written explicitly
    assert a.state is not None and a.state["offset"] is None
    a = actor("Light0")
    assert vec(a, "Location", "X Y Z") == [5.0, 6.0, 7.0] and prop_value(a.properties, "DrawScale") == 0.5
    assert a.block(P_BRIGHTNESS).id == 0x00100062 and a.block(P_BRIGHTNESS).value == 1.25  # id from the table
    assert a.block(P_DRAWSCALE) is None  # plain actor with a tagged DrawScale: the tag was edited

    # applying the same edits again changes nothing
    assert not apply_edits(new, edits, names).changes

    # refusals
    def refused(doc: dict, text: str) -> None:
        """load_edits or apply_edits must refuse `doc` with a message containing `text`."""
        try:
            apply_edits(pkg, load_edits(doc), names)
        except EditsError as ex:
            assert text in str(ex), (text, str(ex))
            return
        raise AssertionError(f"not refused: {text}")

    base = {"format": "t3-map-edits", "version": 1, "level": "synthmap"}
    refused({**base, "actors": {"Nobody": {"location": [0, 0, 0]}}}, "Nobody: no actor of that name")
    refused({**base, "actors": {"AttachmentLinkDataObject0": {"draw_scale": 1}}}, "not an actor")
    refused({**base, "actors": {"StaticMeshActor0": {"gamesys": {"ObjectMesh": "x"}}}}, "is a struct property")
    refused({**base, "actors": {"D_100_0": {"gamesys": {"FleshLightType": "FLT_Nope"}}}}, "not a value of its enum")
    refused({**base, "actors": {"D_100_0": {"gamesys": {"NoSuchProp": 1}}}}, "unknown gamesys property")
    refused({**base, "format": "other", "actors": {}}, '"format" must be')
    refused({**base, "version": 3, "actors": {}}, "not supported")
    refused({**base, "actors": {}, "removed": ["LevelInfo0"]}, "the level needs its LevelInfo")
    refused({**base, "actors": {}, "removed": ["Nobody"]}, "removed actor 'Nobody'")
    refused({**base, "actors": {}, "added": [{"copy_of": "AttachmentLinkDataObject0"}]}, "not an actor")

    # new and removed actors: a copy of StaticMeshActor1 moved and turned, Light0
    # taken out of the level; the copy joins the level's list and the export lists
    grow = load_edits({**base, "version": 2, "actors": {},
                       "added": [{"copy_of": "StaticMeshActor1", "location": [40.0, 50.0, 60.0],
                                  "rotation": [0, 4096, 0]}], "removed": ["Light0"]})
    patch = apply_edits(pkg, grow, names)
    write_verified(pkg, patch, OUT / "grown.gmp")
    grown = Package(OUT / "grown.gmp")
    copy = grown.exports[len(pkg.exports)]
    assert len(grown.exports) == len(pkg.exports) + 1 and copy.name == "StaticMeshActor1__0", copy.name
    assert grown.export_class(copy) == "StaticMeshActor" and copy.flags == pkg.find_export("StaticMeshActor1").flags
    c = grown.read_actor(copy)
    assert vec(c, "Location", "X Y Z") == [40.0, 50.0, 60.0] and vec(c, "Rotation", "Pitch Yaw Roll") == [0, 4096, 0]
    assert c.block(P_DRAWSCALE).value == 1.0 and c.tail == b"\x2A\0\0\0"  # the rest as in the original
    assert grown.level_actors() == [2, 3, 4, 7, len(grown.exports)], grown.level_actors()
    assert all(lst == list(range(len(grown.exports))) for lst in PackageWriter(grown).extra)
    assert grown.export_bytes(grown.find_export("Light0")) == pkg.export_bytes(pkg.find_export("Light0"))
    assert grown.level_actors() is not None and pkg.level_actors() == [2, 3, 4, 5, 7]
    refused({**base, "actors": {"A": {"location": [1, 2]}}}, "location must be")
    refused({**base, "actors": {"A": {"scale": 2}}}, "unknown key 'scale'")
    refused({**base, "actors": {"A": {"rotation": [0, "x", 0]}}}, "rotation must be")
    try:
        check_source(load_edits({**base, "source": {"sha1": "0" * 40}, "actors": {}}), path)
        raise AssertionError("source hash not checked")
    except EditsError as ex:
        assert "not the file these edits were made from" in str(ex)

    # the command line, without a game folder (location edits need no property table)
    (OUT / "edits.json").write_text(json.dumps({**base, "actors": {"StaticMeshActor1": {"location": [0, 0, 64]}}}))
    env = {k: v for k, v in os.environ.items() if k != "T3_GAME_DIR"}
    tool = str(Path(__file__).resolve().parent / "t3pack.py")
    for cmd in (["roundtrip", str(path)],
                ["apply", str(OUT / "edits.json"), "--source", str(path), "-o", str(OUT / "cli.gmp")]):
        r = subprocess.run([sys.executable, tool, *cmd], capture_output=True, text=True, env=env)
        assert r.returncode == 0, (cmd, r.stdout, r.stderr)
    a = Package(OUT / "cli.gmp")
    assert vec(a.read_actor(a.find_export("StaticMeshActor1")), "Location", "X Y Z") == [0.0, 0.0, 64.0]

    # install and restore, in a stand-in game folder
    game, backups = OUT / "game", OUT / "backup"
    for d in (game, backups):
        shutil.rmtree(d, ignore_errors=True)
    maps = game / "Content" / "T3" / "Maps"
    maps.mkdir(parents=True)
    (maps / "SynthMap.gmp").write_bytes(data)
    log: list = []
    install(out, game, backup_dir=backups, log=log.append)
    assert (maps / "SynthMap.gmp").read_bytes() == out.read_bytes()
    assert (backups / "SynthMap.gmp").read_bytes() == data and len(log) == 2, log
    install(OUT / "cli.gmp", game, level="synthmap", backup_dir=backups, log=log.append)
    assert (backups / "SynthMap.gmp").read_bytes() == data and "backup kept" in log[2], log
    # edits made from the original still apply while a patched copy is installed: to the backup
    sha1 = hashlib.sha1(data).hexdigest()
    made_from_original = load_edits({**base, "source": {"size": len(data), "sha1": sha1}, "actors": {}})
    assert original_source(made_from_original, maps / "SynthMap.gmp", backups, log.append) == backups / "SynthMap.gmp"
    patched_sha1 = hashlib.sha1((maps / "SynthMap.gmp").read_bytes()).hexdigest()
    made_from_patch = load_edits({**base, "source": {"sha1": patched_sha1}, "actors": {}})
    assert original_source(made_from_patch, maps / "SynthMap.gmp", backups, log.append) == maps / "SynthMap.gmp"
    assert restore("SYNTHMAP", game, backup_dir=backups, log=log.append) == 1
    assert (maps / "SynthMap.gmp").read_bytes() == data
    assert restore(None, game, backup_dir=backups, log=log.append) == 0 and "already the original" in log[-1]
    print("package writer, map edits, install and restore: ok")


# --- synthetic block file ---------------------------------------------------------------------

def s32(s: str) -> list:
    b = s.encode("latin-1") + b"\0"
    return [struct.pack("<I", len(b)), b]


def texture_parts() -> list:
    # one 4x4 DXT1 block: colour0 red, colour1 blue, all pixels index 0 (red)
    block = struct.pack("<HHI", 0xF800, 0x001F, 0)
    parts = [b"\x01", b"DXT1", struct.pack("<I", 1), struct.pack("<I", 0), struct.pack("<I", 0)]
    parts += [struct.pack("<I", v) for v in (4, 4, 4, 4, len(block))] + [b"\0", b"\0"]
    parts += [struct.pack("<I", v) for v in (0, 4, 4, len(block))] + [b"\0" * 16, block]
    return parts


def material_parts() -> list:
    parts = [b"\0", struct.pack("<I", 0), struct.pack("<I", 1)]
    parts += [struct.pack("<4f", 0, 0, 0, 1), struct.pack("<4f", 1, 1, 1, 1), struct.pack("<4f", 1, 1, 1, 1)]
    parts += [struct.pack("<f", 1), struct.pack("<f", 0.5), struct.pack("<f", 0)]
    parts += [b"\0", struct.pack("<I", 0), struct.pack("<I", 0), b"\1", b"\0", b"\0", struct.pack("<I", 0),
              struct.pack("<f", 1)]
    parts += s32("test.mlb") + [struct.pack("<I", 0), b"\0", struct.pack("<I", 0)]
    parts += s32("red_d")
    for _ in range(7):
        parts += [struct.pack("<I", 1), b"\0"]
    return parts


def mesh_parts() -> list:
    verts = [((0, 0, 0), (0, 0, 1), (0, 0)), ((64, 0, 0), (0, 0, 1), (1, 0)), ((0, 64, 0), (0, 0, 1), (0, 1))]
    blob = struct.pack("<3f3ff3f", 0, 0, 0, 64, 64, 0, 45.3, 21, 21, 0)
    blob += struct.pack("<10I", 3, 3, 1, 1, 0, 0, 0, 1, 64, 0)
    for p, nrm, uv in verts:
        blob += struct.pack("<3f3f2f3f2f2fI", *p, *nrm, *uv, 1, 0, 0, *uv, *uv, 0xFFFFFFFF)
    blob += struct.pack("<3H", 0, 1, 2)
    blob += fstring("Default") + struct.pack("<6I", 1, 0, 3, 0, 3, 0)
    parts = [struct.pack("<I", 1)] + s32("Default") + [struct.pack("<I", 1)] + s32("RedMat")
    parts += [struct.pack("<I", 1), struct.pack("<I", 0), struct.pack("<I", 0), struct.pack("<I", 1)]
    parts += [struct.pack("<12f", 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1)] + s32("Collision")
    parts += [struct.pack("<I", len(blob)), blob]
    return parts


def build_ibt(resources) -> bytes:
    align = 0x800
    count = len(resources)
    all_parts = [p for _, _, parts in resources for p in parts]
    table_size = 0x34 + count * 0x134 + len(all_parts) * 4
    data_start = (table_size + align - 1) // align * align
    entries, data, first = b"", b"", 0
    for rtype, name, parts in resources:
        blob = b"".join(parts)
        pad = (-len(blob)) % align
        entry = struct.pack("<5I", data_start + len(data), len(blob), pad, first, len(parts))
        entry += b"\0" * 20 + bytes([rtype]) + name.encode().ljust(263, b"\0") + struct.pack("<I", 0xFFFFFFFF)
        entries += entry
        data += blob + b"\0" * pad
        first += len(parts)
    head = struct.pack("<8I", 0xC0000001, align, data_start, len(data), 0, 0, count, len(all_parts)) + b"\0" * 20
    table = head + entries + b"".join(struct.pack("<I", len(p)) for p in all_parts)
    return table + b"\0" * (data_start - len(table)) + data


def test_ibt() -> None:
    path = OUT / "synthetic.ibt"
    path.write_bytes(build_ibt([(0x08, "red_d", texture_parts()), (0x0A, "RedMat", material_parts()),
                                (0x04, "TestMesh", mesh_parts())]))
    with IBT(path) as b:
        assert [r.type_name for r in b.resources] == ["texture", "matlib", "staticmesh"]
        tex = parse_texture(b.find("RED_D", 0x08), b.split(b.find("red_d", 0x08)))
        assert (tex.format, tex.width, tex.height, len(tex.mips)) == ("DXT1", 4, 4, 1)
        dds = to_dds(tex)
        assert dds[:4] == b"DDS " and len(dds) == 128 + 8
        w, h, rgba = decode_rgba(tex)
        assert (w, h) == (4, 4) and tuple(rgba[:4]) == (255, 0, 0, 255), tuple(rgba[:4])
        mat = parse_material(b.find("RedMat"), b.split(b.find("RedMat")))
        assert mat.texture(0) == "red_d" and mat.texture(1) is None
        pr = PartReader(b.split(b.find("TestMesh")))
        assert pr.u32() == 1
        mesh = parse_static_mesh(b.find("TestMesh"), b.split(b.find("TestMesh")))
        assert len(mesh.render.positions) == 3 and mesh.render.indices == [0, 1, 2]
        assert mesh.skins[0].materials == ["RedMat"] and mesh.hardpoints[0].name == "Collision"
        res = ResourceSet([b], OUT / "textures")
        g = mesh_to_gltf(mesh, None, res, 0.01)
        glb = OUT / "TestMesh.glb"
        g.write_glb(glb)
    raw = glb.read_bytes()
    assert raw[:4] == b"glTF"
    doc = json.loads(raw[20:20 + struct.unpack_from("<I", raw, 12)[0]])
    prim = doc["meshes"][0]["primitives"][0]
    assert doc["materials"][prim["material"]]["name"] == "RedMat"
    assert doc["images"][0]["uri"] == "../textures/red_d.png"
    acc = doc["accessors"][prim["attributes"]["POSITION"]]
    assert acc["max"] == [0.64, 0.0, 0.64] or all(abs(a - b) < 1e-6 for a, b in zip(acc["max"], [0.64, 0.0, 0.64]))
    assert (OUT / "textures" / "red_d.png").is_file()
    print("block file, texture, material, mesh, glTF: ok")


def test_math_and_props() -> None:
    assert u2g((1, 2, 3)) == (1, 3, 2)
    cols = godot_basis(0, 16384, 0)  # yaw 90 degrees: Unreal X turns into Unreal Y = Godot Z
    assert all(abs(a - b) < 1e-6 for a, b in zip(cols[0], (0, 0, 1))), cols
    assert all(abs(a - b) < 1e-6 for a, b in zip(cols[1], (0, 1, 0))), cols
    src = ('enum EColourTest { CT_A, CT_B = 5, CT_C };\n'
           'var(Test) inherited(12) float Alpha "first";\n'
           'var runtimeinstantiated(13) array<name> Betas;\n'
           '// var inherited(14) int Commented;\n'
           'var(Test) inherited(15) bitfield EFlagsTest\n{\n\tF_A,\n\tF_B\n} Gammas "bits";\n')
    decls = parse_declarations("Pkg", "Cls", src)
    assert [(d.id, d.name, d.type, d.kind) for d in decls] == [
        (12, "Alpha", "float", "inherited"), (13, "Betas", "array<name>", "runtimeinstantiated"),
        (15, "Gammas", "bitfield<EFlagsTest>", "inherited")], decls
    enums = parse_enums(src)
    assert enums["EColourTest"][0] == "CT_A" and enums["EColourTest"][5] == "CT_B" and enums["EColourTest"][6] == "CT_C"
    assert enums["EFlagsTest"] == ["F_A", "F_B"]
    names = PropertyNames({"properties": {"12": {"name": "Alpha", "type": "float"},
                                          "15": {"name": "Gammas", "type": "bitfield<EFlagsTest>"}},
                           "enums": enums})
    assert names.id_of("alpha") == 12 and names.name(0x0010000C) == "Alpha"
    assert names.bitfield_names(0x0800000F, 0b10) == ["F_B"]
    assert write_index(-1) == b"\x81" and write_index(64) == b"\x40\x01"
    print("coordinates, property declarations, compact indices: ok")


def main() -> None:
    OUT.mkdir(parents=True, exist_ok=True)
    test_package()
    test_writer()
    test_ibt()
    test_math_and_props()
    selftest_texpack.main()
    print("all self-tests passed")


if __name__ == "__main__":
    main()
