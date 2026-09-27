#!/usr/bin/env python3
"""Self-test for tools/assets using synthetic data only (no game files).

Builds a tiny Flesh-style Unreal package and a tiny .ibt block file in
build/assets/selftest/, then checks that the parsers, the texture and mesh
converters, the glTF writer and the coordinate conversion agree with what was
written.  Run: python tools/assets/selftest.py
"""

from __future__ import annotations

import json
import math
import struct
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from ibt import IBT, PartReader  # noqa: E402
from t3common import BUILD_DIR, godot_basis, u2g, write_index  # noqa: E402
from t3mesh import ResourceSet, mesh_to_gltf, parse_static_mesh  # noqa: E402
from t3props import PropertyNames, parse_declarations, parse_enums  # noqa: E402
from t3texture import decode_rgba, parse_material, parse_texture, to_dds  # noqa: E402
from upkg import Package, prop_value, struct_fields  # noqa: E402

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
    test_ibt()
    test_math_and_props()
    print("all self-tests passed")


if __name__ == "__main__":
    main()
