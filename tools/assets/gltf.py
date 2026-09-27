"""Minimal glTF 2.0 binary (.glb) writer, standard library only.

Enough for static meshes: several primitives per mesh, POSITION / NORMAL /
TANGENT / TEXCOORD_n / COLOR_0 attributes, 16- or 32-bit indices, PBR
materials with base colour, normal and emissive textures, images referenced
by URI or embedded, node hierarchy with TRS or matrix, and "extras".
"""

from __future__ import annotations

import json
import struct
from pathlib import Path
from typing import Any, Dict, List, Optional, Sequence

FLOAT = 5126
UNSIGNED_SHORT = 5123
UNSIGNED_INT = 5125
UNSIGNED_BYTE = 5121
ARRAY_BUFFER = 34962
ELEMENT_ARRAY_BUFFER = 34963
REPEAT = 10497
LINEAR = 9729
LINEAR_MIPMAP_LINEAR = 9987


class GLTFBuilder:
    def __init__(self, generator: str = "Thief3-Decomp tools/assets") -> None:
        self.doc: Dict[str, Any] = {
            "asset": {"version": "2.0", "generator": generator},
            "scene": 0,
            "scenes": [{"nodes": []}],
            "nodes": [], "meshes": [], "materials": [], "textures": [], "images": [],
            "samplers": [{"magFilter": LINEAR, "minFilter": LINEAR_MIPMAP_LINEAR,
                          "wrapS": REPEAT, "wrapT": REPEAT}],
            "accessors": [], "bufferViews": [], "buffers": [],
        }
        self.bin = bytearray()
        self._images: Dict[str, int] = {}
        self._materials: Dict[str, int] = {}

    # --- buffers ----------------------------------------------------------

    def _view(self, data: bytes, target: Optional[int] = None) -> int:
        while len(self.bin) % 4:
            self.bin.append(0)
        view = {"buffer": 0, "byteOffset": len(self.bin), "byteLength": len(data)}
        if target:
            view["target"] = target
        self.bin += data
        self.doc["bufferViews"].append(view)
        return len(self.doc["bufferViews"]) - 1

    def _accessor(self, view: int, ctype: int, count: int, atype: str,
                  minv: Optional[List[float]] = None, maxv: Optional[List[float]] = None,
                  normalized: bool = False) -> int:
        acc: Dict[str, Any] = {"bufferView": view, "componentType": ctype, "count": count, "type": atype}
        if minv is not None:
            acc["min"], acc["max"] = minv, maxv
        if normalized:
            acc["normalized"] = True
        self.doc["accessors"].append(acc)
        return len(self.doc["accessors"]) - 1

    def add_floats(self, values: Sequence[Sequence[float]], atype: str, with_bounds: bool = False) -> int:
        n = {"VEC2": 2, "VEC3": 3, "VEC4": 4}[atype]
        flat = [float(c) for v in values for c in v]
        data = struct.pack(f"<{len(flat)}f", *flat)
        minv = maxv = None
        if with_bounds and values:
            minv = [min(v[i] for v in values) for i in range(n)]
            maxv = [max(v[i] for v in values) for i in range(n)]
        return self._accessor(self._view(data, ARRAY_BUFFER), FLOAT, len(values), atype, minv, maxv)

    def add_colors_u8(self, rgba: Sequence[Sequence[int]]) -> int:
        flat = [c for v in rgba for c in v]
        data = struct.pack(f"<{len(flat)}B", *flat)
        return self._accessor(self._view(data, ARRAY_BUFFER), UNSIGNED_BYTE, len(rgba), "VEC4", normalized=True)

    def add_indices(self, indices: Sequence[int]) -> int:
        big = max(indices, default=0) > 0xFFFF
        data = struct.pack(f"<{len(indices)}{'I' if big else 'H'}", *indices)
        return self._accessor(self._view(data, ELEMENT_ARRAY_BUFFER),
                              UNSIGNED_INT if big else UNSIGNED_SHORT, len(indices), "SCALAR")

    # --- materials ----------------------------------------------------------

    def image(self, uri: Optional[str] = None, png_bytes: Optional[bytes] = None, name: Optional[str] = None) -> int:
        key = uri or name or f"embedded{len(self._images)}"
        if key in self._images:
            return self._images[key]
        img: Dict[str, Any] = {}
        if png_bytes is not None:
            img["bufferView"] = self._view(png_bytes)
            img["mimeType"] = "image/png"
        else:
            img["uri"] = uri
        if name:
            img["name"] = name
        self.doc["images"].append(img)
        self.doc["textures"].append({"sampler": 0, "source": len(self.doc["images"]) - 1})
        self._images[key] = len(self.doc["textures"]) - 1
        return self._images[key]

    def material(self, name: str, base_color_tex: Optional[int] = None, normal_tex: Optional[int] = None,
                 emissive_tex: Optional[int] = None, base_color=(1.0, 1.0, 1.0, 1.0),
                 alpha_mode: str = "OPAQUE", alpha_cutoff: float = 0.5, double_sided: bool = False,
                 roughness: float = 0.9, extras: Optional[Dict[str, Any]] = None) -> int:
        if name in self._materials:
            return self._materials[name]
        pbr: Dict[str, Any] = {"baseColorFactor": list(base_color), "metallicFactor": 0.0,
                               "roughnessFactor": roughness}
        if base_color_tex is not None:
            pbr["baseColorTexture"] = {"index": base_color_tex}
        m: Dict[str, Any] = {"name": name, "pbrMetallicRoughness": pbr}
        if normal_tex is not None:
            m["normalTexture"] = {"index": normal_tex}
        if emissive_tex is not None:
            m["emissiveTexture"] = {"index": emissive_tex}
            m["emissiveFactor"] = [1.0, 1.0, 1.0]
        if alpha_mode != "OPAQUE":
            m["alphaMode"] = alpha_mode
            if alpha_mode == "MASK":
                m["alphaCutoff"] = alpha_cutoff
        if double_sided:
            m["doubleSided"] = True
        if extras:
            m["extras"] = extras
        self.doc["materials"].append(m)
        self._materials[name] = len(self.doc["materials"]) - 1
        return self._materials[name]

    # --- meshes and nodes --------------------------------------------------------

    def mesh(self, name: str, primitives: List[Dict[str, Any]], extras: Optional[Dict[str, Any]] = None) -> int:
        m: Dict[str, Any] = {"name": name, "primitives": primitives}
        if extras:
            m["extras"] = extras
        self.doc["meshes"].append(m)
        return len(self.doc["meshes"]) - 1

    def node(self, name: str, mesh: Optional[int] = None, translation=None, rotation=None, scale=None,
             matrix=None, children: Optional[List[int]] = None, extras: Optional[Dict[str, Any]] = None,
             root: bool = False) -> int:
        n: Dict[str, Any] = {"name": name}
        if mesh is not None:
            n["mesh"] = mesh
        if matrix is not None:
            n["matrix"] = list(matrix)
        else:
            if translation is not None:
                n["translation"] = list(translation)
            if rotation is not None:
                n["rotation"] = list(rotation)
            if scale is not None:
                n["scale"] = list(scale)
        if children:
            n["children"] = children
        if extras:
            n["extras"] = extras
        self.doc["nodes"].append(n)
        idx = len(self.doc["nodes"]) - 1
        if root:
            self.doc["scenes"][0]["nodes"].append(idx)
        return idx

    # --- output ----------------------------------------------------------------

    def _finish(self) -> Dict[str, Any]:
        doc = dict(self.doc)
        for key in ("materials", "textures", "images", "samplers"):
            if not doc[key]:
                del doc[key]
        if "textures" not in doc:
            doc.pop("samplers", None)
        if self.bin:
            doc["buffers"] = [{"byteLength": len(self.bin)}]
        else:  # glTF forbids empty buffers (e.g. a mesh whose sections are all hidden)
            for key in ("buffers", "bufferViews", "accessors", "meshes"):
                doc.pop(key, None)
        for key in ("meshes", "nodes"):
            if key in doc and not doc[key]:
                del doc[key]
        return doc

    def write_glb(self, path: Path) -> None:
        doc = self._finish()
        js = json.dumps(doc, separators=(",", ":")).encode("utf-8")
        js += b" " * (-len(js) % 4)
        binp = bytes(self.bin) + b"\0" * (-len(self.bin) % 4)
        total = 12 + 8 + len(js) + (8 + len(binp) if binp else 0)
        # glTF binary container: 12-byte header ('glTF', version 2, total length),
        # then a JSON chunk (type 'JSON') and an optional binary chunk (type 'BIN\0').
        out = struct.pack("<III", 0x46546C67, 2, total)
        out += struct.pack("<II", len(js), 0x4E4F534A) + js
        if binp:
            out += struct.pack("<II", len(binp), 0x004E4942) + binp
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_bytes(out)
