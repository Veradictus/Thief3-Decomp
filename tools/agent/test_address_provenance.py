"""Hostile-input tests for original addresses, using generated metadata/COFF only."""

import json
import struct
import tempfile
import unittest
from unittest.mock import patch
from pathlib import Path
from types import SimpleNamespace

import coff
from address_provenance import ProvenanceError, for_project, load_object, source_path, split_virtual_addresses
from common import Project, ROOT
from verify import TargetImage, object_view


A, U, H, D = 0x41000000, 0x41010000, 0x41010008, 0x42000000
FUNCTION = "?Example@@YAXXZ"
HANDLER = coff.EH_HANDLER + FUNCTION
FUNCLET = coff.eh_funclet_name(FUNCTION, 0)
INFO = coff.eh_funcinfo_name(FUNCTION)


def note(values):
    return struct.pack("<III", 6, 4 * len(values), int.from_bytes(b"VIRT", "big")) \
        + b"Split\0\0\0" + struct.pack(f"<{len(values)}I", *values)


def make_object(sections, symbols):
    """Ordinary i386 COFF; auxiliary slots are represented by each symbol's aux."""
    strings = bytearray(b"\4\0\0\0")
    table = bytearray()
    for name, value, section, typ, storage, aux in symbols:
        encoded = name.encode("ascii")
        if len(encoded) > 8:
            raw_name = struct.pack("<II", 0, len(strings))
            strings.extend(encoded + b"\0")
        else:
            raw_name = encoded.ljust(8, b"\0")
        table.extend(raw_name + struct.pack("<IhHBB", value, section, typ, storage, len(aux) // 18) + aux)
    body = bytearray()
    headers = bytearray()
    offset = 20 + 40 * len(sections)
    for name, data, relocs, flags in sections:
        encoded_name = name.encode()
        if len(encoded_name) > 8:
            raw_section_name = ("/" + str(len(strings))).encode().ljust(8, b"\0")
            strings.extend(encoded_name + b"\0")
        else:
            raw_section_name = encoded_name.ljust(8, b"\0")
        raw, rptr = offset, offset + len(data)
        blob = b"".join(struct.pack("<IIH", *r) for r in relocs)
        headers.extend(raw_section_name + struct.pack("<IIIIIIHHI", 0, 0, len(data), raw,
                                                                  rptr, 0, len(relocs), 0, flags))
        body.extend(data + blob)
        offset += len(data) + len(blob)
    slots = sum(1 + len(s[-1]) // 18 for s in symbols)
    struct.pack_into("<I", strings, 0, len(strings))
    return struct.pack("<HHIIIHH", 0x14C, len(sections), 0, offset, slots, 0, 0) \
        + headers + body + table + strings


class Case:
    def __init__(self):
        base = ROOT / "build" / "address-provenance-tests"
        base.mkdir(parents=True, exist_ok=True)
        self.temp = tempfile.TemporaryDirectory(dir=base)
        self.root = Path(self.temp.name)
        assert self.root.resolve().is_relative_to(ROOT.resolve())
        self.folder = self.root / "build" / "test"
        self.objects = self.folder / "obj"
        self.objects.mkdir(parents=True)
        self.model = dict(delink_ida_version=1, meta=dict(arch="x86", bits=32, endian="little"),
            functions=[dict(start=A, end=A + 4, name=FUNCTION), dict(start=U, end=U + 8, name=f"Unwind@{U:08x}"),
                       dict(start=H, end=H + 10, name=HANDLER)],
            names=[dict(addr=A, name=FUNCTION), dict(addr=U, name=f"Unwind@{U:08x}"), dict(addr=H, name=HANDLER),
                   dict(addr=D, name=f"DAT_{D:08x}"), dict(addr=D + 8, name=f"DAT_{D+8:08x}")],
            relocations=[dict(addr=H + 1, type="OFF32", size=4, target=D + 8),
                         dict(addr=D + 16, type="OFF32", size=4, target=D),
                         dict(addr=D + 4, type="OFF32", size=4, target=U)])
        self.groups = {"unit.obj": dict(functions=[A, U, H], function_ranges=[], rdata=[], data=[], bss=[])}
        self.source_symbols = [(FUNCTION, 0, 1, 32, 2, b""), (FUNCLET, 4, 1, 32, 2, b""),
                               (HANDLER, 12, 1, 32, 2, b""), (INFO, 0, 0, 0, 2, b"")]
        self.values = [A, U, H, 0]
        self.source_relocs = [(0, 2, 6), (13, 3, 6)]
        self.source_data = bytearray(22)
        self.source_note = None
        self.with_note = True
        self.write_shared()
        self.project = Project.__new__(Project)
        self.project.main, self.project.version = self.root, "test"
        self.project.obj_dir, self.project.exe = self.objects, None
        self.project._symbols = [SimpleNamespace(name=FUNCTION, address=A, size=4, type="function", is_function=True),
                                 SimpleNamespace(name=HANDLER, address=H, size=10, type="function", is_function=True)]

    def close(self):
        self.temp.cleanup()

    def write_shared(self, truncate=False):
        data = bytearray(36)
        struct.pack_into("<i", data, 0, -1)
        struct.pack_into("<II", data, 8, coff.EH_MAGIC, 1)
        symbols = [(f"DAT_{D:08x}", 0, 1, 0, 2, b""), (f"DAT_{D+8:08x}", 8, 1, 0, 2, b""),
                   (f"Unwind@{U:08x}", 0, 0, 0, 2, b"")]
        if truncate:
            data = data[:16]
        raw = make_object([(".rdata", bytes(data), [(4, 2, 6), (16, 0, 6)] if not truncate else [(4, 2, 6)], 0x40000040),
                           (".note.split", note([D, D + 8, 0]), [], 0x40000040)], symbols)
        (self.objects / "__shared_data.obj").write_bytes(raw)

    def write(self):
        (self.folder / "delink.json").write_text(json.dumps(self.model))
        (self.folder / "idapro.json").write_text(json.dumps(self.groups))
        sections = [(".text", bytes(self.source_data), self.source_relocs, 0x60000020)]
        if self.with_note:
            sections.append((".note.split", self.source_note if self.source_note is not None else note(self.values), [], 0x40000040))
        raw = make_object(sections, self.source_symbols)
        self.path = self.objects / "unit.obj"
        self.path.write_bytes(raw)
        return load_object(self.path)

    def handler_view(self, obj=None):
        obj = obj or self.write()
        return object_view(self.project, obj, obj.section(1), 12, 10, H)


class AddressProvenanceTests(unittest.TestCase):
    def setUp(self):
        self.case = Case()

    def tearDown(self):
        self.case.close()

    def test_both_real_input_shapes_through_production_APIs(self):
        c = self.case
        obj = c.write()
        self.assertEqual(c.handler_view(obj).relocs[1], (D + 8, INFO, 6))
        image = TargetImage(c.project)
        self.assertIsNotNone(image.view(U, 8))
        self.assertEqual(image.view(H, 10), image.relocated_view(H, 10))
        self.assertEqual(image.view(H, 10).relocs[1][0], D + 8)
        service = for_project(c.project)
        self.assertEqual(service.model_reads, 1)
        self.assertTrue(any(x["kind"] == "VIRT+model+group" for x in service.origins.values()))
        self.assertTrue(any(x["kind"] == "original-handler-field+named-target" for x in service.origins.values()))
        self.assertNotIn(INFO, c.project.by_name)
        self.assertNotIn(FUNCLET, c.project.by_name)

    def test_named_and_same_section_without_notes_keep_legacy_behavior(self):
        c = self.case
        c.with_note = False
        c.source_symbols[1] = ("local", 4, 1, 0, 3, b"")
        c.source_relocs = [(0, 2, 6), (4, 1, 6)]
        obj = c.write()
        view = object_view(c.project, obj, obj.section(1), 0, 8, A)
        self.assertEqual(view.relocs[0][0], H)
        self.assertEqual(view.relocs[4][0], A + 4)
        self.assertEqual(for_project(c.project).model_reads, 0)

    def test_auxiliary_gap_uses_raw_slots(self):
        c = self.case
        first = c.source_symbols[0]
        c.source_symbols[0] = first[:-1] + (bytes(18),)
        c.values = [A, 0, U, H, 0]
        c.source_relocs = [(0, 3, 6), (13, 4, 6)]
        obj = c.write()
        self.assertIsNone(obj.slots[1])
        self.assertEqual(c.handler_view(obj).relocs[1][0], D + 8)
        self.assertEqual(for_project(c.project).symbol_address(obj, obj.slots[2]), U)

    def test_documented_append_is_unknown_not_zero_address(self):
        c = self.case
        c.source_symbols.append(("__except_list", 0, 0, 0, 2, b""))
        obj = c.write()
        self.assertEqual(c.handler_view(obj).relocs[1][0], D + 8)
        self.assertIsNone(for_project(c.project).symbol_address(obj, obj.slots[4]))

    def test_unproven_append_rejects(self):
        c = self.case
        c.source_symbols.append(("invented", 0, 0, 0, 2, b""))
        with self.assertRaises(ProvenanceError):
            c.handler_view()

    def test_defined_uncovered_append_rejects(self):
        c = self.case
        c.source_symbols.append(("invented", 1, 1, 0, 3, b""))
        with self.assertRaises(ProvenanceError):
            c.handler_view()

    def test_zero_defined_slot_stays_unknown(self):
        c = self.case
        c.values[1] = 0
        obj = c.write()
        self.assertIsNone(for_project(c.project).symbol_address(obj, obj.slots[1]))

    def test_undefined_nonzero_rejects(self):
        c = self.case
        c.values[3] = D + 8
        with self.assertRaises(ProvenanceError):
            c.handler_view()

    def test_bad_headers_and_lengths_reject(self):
        valid = note(self.case.values)
        for field, value in ((0, 5), (4, 15), (8, 0)):
            blob = bytearray(valid)
            struct.pack_into("<I", blob, field, value)
            with self.subTest(field=field), self.assertRaises(ValueError):
                c = self.case
                c.source_note = bytes(blob)
                split_virtual_addresses(c.write())
        for blob in (valid[:10], valid[:-1], valid + b"\0", valid[:12] + b"Other\0\0\0" + valid[20:], note([A, 0, U, H, 0])):
            with self.subTest(blob=blob[:20]), self.assertRaises(ValueError):
                self.case.source_note = blob
                split_virtual_addresses(self.case.write())

    def test_nonzero_auxiliary_rejects(self):
        c = self.case
        first = c.source_symbols[0]
        c.source_symbols[0] = first[:-1] + (bytes(18),)
        c.values = [A, A + 1, U, H, 0]
        with self.assertRaises(ProvenanceError):
            c.handler_view()

    def test_wrong_model_machine_rejects(self):
        self.case.model["meta"]["bits"] = 64
        with self.assertRaises(ProvenanceError):
            self.case.handler_view()

    def test_conflicting_independent_anchor_rejects(self):
        self.case.values[2] = H + 4
        with self.assertRaises(ProvenanceError):
            self.case.handler_view()

    def test_slot_permutation_rejects(self):
        self.case.values[0], self.case.values[1] = U, A
        with self.assertRaises(ProvenanceError):
            self.case.handler_view()

    def test_wrong_group_rejects(self):
        self.case.groups["other.obj"] = self.case.groups.pop("unit.obj")
        with self.assertRaises(ProvenanceError):
            self.case.handler_view()

    def test_wrong_group_range_rejects(self):
        self.case.groups["unit.obj"]["functions"] = [A]
        with self.assertRaises(ProvenanceError):
            self.case.handler_view()

    def test_wrong_object_extent_rejects(self):
        self.case.source_symbols[1] = (FUNCLET, 1000, 1, 32, 2, b"")
        with self.assertRaises(ProvenanceError):
            self.case.handler_view()

    def test_wrong_external_field_rejects(self):
        self.case.source_relocs = [(0, 2, 6), (14, 3, 6)]
        with self.assertRaises(ProvenanceError):
            self.case.handler_view()

    def test_wrong_external_type_rejects(self):
        self.case.source_relocs[1] = (13, 3, 20)
        with self.assertRaises(ProvenanceError):
            self.case.handler_view()

    def test_wrong_external_addend_rejects(self):
        struct.pack_into("<I", self.case.source_data, 13, 4)
        with self.assertRaises(ProvenanceError):
            self.case.handler_view()

    def test_wrong_source_view_rejects(self):
        c = self.case
        obj = c.write()
        with self.assertRaises(ProvenanceError):
            object_view(c.project, obj, obj.section(1), 12, 10, H + 4)

    def test_wrong_model_target_rejects(self):
        self.case.model["relocations"][0]["target"] += 4
        with self.assertRaises(ProvenanceError):
            self.case.handler_view()

    def test_wrong_model_relocation_width_rejects(self):
        self.case.model["relocations"][0]["size"] = 8
        with self.assertRaises(ProvenanceError):
            self.case.handler_view()

    def test_duplicate_conflicting_model_anchor_rejects(self):
        self.case.model["functions"].append(dict(start=A, end=A + 8, name=FUNCTION))
        with self.assertRaises(ProvenanceError):
            self.case.handler_view()

    def test_duplicate_conflicting_relocation_rejects(self):
        self.case.model["relocations"].append(dict(addr=H + 1, type="OFF32", size=4, target=D))
        with self.assertRaises(ProvenanceError):
            self.case.handler_view()

    def test_unreadable_target_rejects(self):
        (self.case.objects / "__shared_data.obj").unlink()
        with self.assertRaises(ProvenanceError):
            self.case.handler_view()

    def test_short_target_rejects(self):
        self.case.write_shared(truncate=True)
        with self.assertRaises(ProvenanceError):
            self.case.handler_view()

    def test_missing_metadata_stays_unresolved(self):
        c = self.case
        obj = c.write()
        (c.folder / "delink.json").unlink()
        self.assertIsNone(c.handler_view(obj).relocs[1][0])
        self.assertIsNone(for_project(c.project).symbol_address(obj, obj.slots[1]))

    def test_stale_metadata_rejects(self):
        c = self.case
        obj = c.write()
        c.handler_view(obj)
        (c.folder / "delink.json").write_text("{}")
        with self.assertRaises(ProvenanceError):
            c.handler_view(obj)

    def test_integer_without_relocation_stays_constant(self):
        c = self.case
        c.source_relocs = []
        struct.pack_into("<I", c.source_data, 13, D + 8)
        obj = c.write()
        view = c.handler_view(obj)
        self.assertEqual(view.relocs, {})
        self.assertEqual(TargetImage(c.project).pointer_offsets(view), set())

    def test_packed_section_uses_per_symbol_addresses(self):
        c = self.case
        obj = c.write()
        origins = for_project(c.project)
        self.assertEqual(origins.symbol_address(obj, obj.slots[0]), A)
        self.assertEqual(origins.symbol_address(obj, obj.slots[1]), U)
        self.assertNotEqual(A, H - obj.slots[2].value)
        self.assertNotEqual(A + obj.slots[1].value, U)

    def test_image_pointer_behavior_unchanged(self):
        c = self.case
        image = TargetImage(c.project)
        data = struct.pack("<I", H)
        self.assertIsNone(image.pointer(SimpleNamespace(address=A, data=data), 0, 6))
        image.pe = SimpleNamespace(image_base=A, image_size=0x20000,
                                   read_rva=lambda offset, size: data[:size])
        view = image.view(A, 4)
        self.assertIsNone(view.relocs)
        self.assertEqual(image.pointer(view, 0, 6), (H, HANDLER))

    def test_folded_interior_label_keeps_history_but_stays_undefined(self):
        c = self.case
        c.source_symbols.append((f"$L_{A+1:08x}", 0, 0, 0, 2, b""))
        c.values.append(A + 1)
        obj = c.write()
        self.assertIsNone(for_project(c.project).symbol_address(obj, obj.slots[4]))
        self.assertEqual(c.handler_view(obj).relocs[1][0], D + 8)

    def test_documented_fold_into_append_retains_existing_slots(self):
        c = self.case
        c.source_symbols.extend([(f"DAT_{D+1:08x}", 0, 0, 0, 2, b""), ("Container", 0, 0, 0, 2, b"")])
        c.values.append(0)
        c.project._symbols.append(SimpleNamespace(name="Container", address=D, size=36, type="object", is_function=False))
        obj = c.write()
        self.assertEqual(c.handler_view(obj).relocs[1][0], D + 8)
        self.assertEqual(for_project(c.project).symbol_address(obj, obj.slots[5]), D)

    def test_wrong_named_target_bytes_reject(self):
        c = self.case
        c.write()
        path = c.objects / "__shared_data.obj"
        obj = coff.Coff.load(path)
        # Only this generated fake target is changed; no Game bytes involved.
        path.write_bytes(obj.rewrite(patch={(1, 8): bytes(4)}))
        with self.assertRaises(ProvenanceError):
            c.handler_view()

    def test_funclet_index_must_be_within_actual_state_count(self):
        c = self.case
        old = c.source_symbols[1]
        c.source_symbols[1] = (coff.eh_funclet_name(FUNCTION, 4),) + old[1:]
        # An unrelated original pointer beyond the one-entry map is not lineage.
        c.model["relocations"].append(dict(addr=D + 36, type="OFF32", size=4, target=U))
        obj = c.write()
        with self.assertRaises(ProvenanceError):
            for_project(c.project).symbol_address(obj, obj.slots[1])

    def test_funclet_requires_complete_unwind_map(self):
        c = self.case
        obj = c.write()
        path = c.objects / "__shared_data.obj"
        data = coff.Coff.load(path)
        # Header remains readable, but 5 entries require 40 bytes, not 36.
        path.write_bytes(data.rewrite(patch={(1, 12): struct.pack("<I", 5)}))
        with self.assertRaises(ProvenanceError):
            for_project(c.project).symbol_address(obj, obj.slots[1])

    def test_funclet_last_state_is_valid(self):
        c = self.case
        old = c.source_symbols[1]
        c.source_symbols[1] = (coff.eh_funclet_name(FUNCTION, 1),) + old[1:]
        c.model["names"].append(dict(addr=D + 40, name=f"DAT_{D+40:08x}"))
        c.model["relocations"][1]["target"] = D + 40
        c.model["relocations"][2:] = [dict(addr=D + x, type="OFF32", size=4, target=U) for x in (44, 52)]
        data = bytearray(56)
        struct.pack_into("<II", data, 8, coff.EH_MAGIC, 2)
        struct.pack_into("<i", data, 40, -1)
        raw = make_object([(".rdata", bytes(data), [(16, 0, 6), (44, 2, 6), (52, 2, 6)], 0x40000040),
                           (".note.split", note([D + 40, D + 8, 0]), [], 0x40000040)],
                          [(f"DAT_{D+40:08x}", 40, 1, 0, 2, b""),
                           (f"DAT_{D+8:08x}", 8, 1, 0, 2, b""),
                           (f"Unwind@{U:08x}", 0, 0, 0, 2, b"")])
        (c.objects / "__shared_data.obj").write_bytes(raw)
        obj = c.write()
        self.assertEqual(for_project(c.project).symbol_address(obj, obj.slots[1]), U)

    def test_funclet_data_owner_can_contain_its_own_funclet(self):
        c = self.case
        c.groups["unit.obj"]["rdata"] = [[D, D + 36]]
        c.write()
        shared_path = c.objects / "__shared_data.obj"
        data = coff.Coff.load(shared_path).section(1).data
        symbols = c.source_symbols + [(f"DAT_{D:08x}", 0, 2, 0, 2, b""),
                                      (f"DAT_{D+8:08x}", 8, 2, 0, 2, b""),
                                      (f"Unwind@{U:08x}", 0, 0, 0, 2, b"")]
        raw = make_object([(".text", bytes(c.source_data), c.source_relocs, 0x60000020),
                           (".rdata", data, [(4, 6, 6), (16, 4, 6)], 0x40000040),
                           (".note.split", note(c.values + [D, D + 8, 0]), [], 0x40000040)], symbols)
        c.path.write_bytes(raw)
        shared_path.unlink()
        obj = load_object(c.path)
        self.assertEqual(for_project(c.project).symbol_address(obj, obj.slots[1]), U)
        self.assertEqual(c.handler_view(obj).relocs[1][0], D + 8)

    def test_defined_friendly_map_target_reuses_owner_slot_validation(self):
        c = self.case
        c.groups["unit.obj"]["rdata"] = [[D, D + 36]]
        c.write()
        shared_path = c.objects / "__shared_data.obj"
        data = coff.Coff.load(shared_path).section(1).data
        symbols = c.source_symbols + [(f"DAT_{D:08x}", 0, 2, 0, 2, b""),
                                      (f"DAT_{D+8:08x}", 8, 2, 0, 2, b"")]
        # The map now refers to the defined friendly funclet in this owner.
        raw = make_object([(".text", bytes(c.source_data), c.source_relocs, 0x60000020),
                           (".rdata", data, [(4, 1, 6), (16, 4, 6)], 0x40000040),
                           (".note.split", note(c.values + [D, D + 8]), [], 0x40000040)], symbols)
        c.path.write_bytes(raw)
        shared_path.unlink()
        obj = load_object(c.path)
        with patch("address_provenance.split_virtual_addresses", wraps=split_virtual_addresses) as parse:
            self.assertEqual(for_project(c.project).symbol_address(obj, obj.slots[1]), U)
            self.assertEqual(c.handler_view(obj).relocs[1][0], D + 8)
        # One parse for the caller Coff, one for the separately loaded data owner.
        self.assertEqual(parse.call_count, 2)

    def test_funclet_rejects_bad_actual_header(self):
        for magic, states in ((0, 1), (coff.EH_MAGIC, 0), (coff.EH_MAGIC, -1),
                              (coff.EH_MAGIC, 0x1001)):
            with self.subTest(magic=magic, states=states):
                c = Case()
                try:
                    obj = c.write()
                    path = c.objects / "__shared_data.obj"
                    data = coff.Coff.load(path)
                    path.write_bytes(data.rewrite(patch={(1, 8): struct.pack("<Ii", magic, states)}))
                    with self.assertRaises(ProvenanceError):
                        for_project(c.project).symbol_address(obj, obj.slots[1])
                finally:
                    c.close()

    def test_funclet_requires_actual_map_field_relocation(self):
        c = self.case
        obj = c.write()
        path = c.objects / "__shared_data.obj"
        data = coff.Coff.load(path)
        # Keep the model pointer but remove its actual COFF relocation.
        raw = make_object([(".rdata", data.section(1).data, [(16, 0, 6)], 0x40000040),
                           (".note.split", note([D, D + 8, 0]), [], 0x40000040)],
                          [(f"DAT_{D:08x}", 0, 1, 0, 2, b""),
                           (f"DAT_{D+8:08x}", 8, 1, 0, 2, b""),
                           (f"Unwind@{U:08x}", 0, 0, 0, 2, b"")])
        path.write_bytes(raw)
        with self.assertRaises(ProvenanceError):
            for_project(c.project).symbol_address(obj, obj.slots[1])

    def test_funclet_checks_actual_map_link_and_field(self):
        for relocations in ([(4, 2, 6)], [(4, 2, 7), (16, 0, 6)],
                            [(4, 0, 6), (16, 0, 6)]):
            with self.subTest(relocations=relocations):
                c = Case()
                try:
                    obj = c.write()
                    path = c.objects / "__shared_data.obj"
                    data = coff.Coff.load(path).section(1).data
                    raw = make_object([(".rdata", data, relocations, 0x40000040),
                                       (".note.split", note([D, D + 8, 0]), [], 0x40000040)],
                                      [(f"DAT_{D:08x}", 0, 1, 0, 2, b""),
                                       (f"DAT_{D+8:08x}", 8, 1, 0, 2, b""),
                                       (f"Unwind@{U:08x}", 0, 0, 0, 2, b"")])
                    path.write_bytes(raw)
                    with self.assertRaises(ProvenanceError):
                        for_project(c.project).symbol_address(obj, obj.slots[1])
                finally:
                    c.close()

    def test_funclet_preserves_folded_target_addend(self):
        c = self.case
        c.project._symbols.append(SimpleNamespace(name="Container", address=U - 4, size=12,
                                                 type="object", is_function=False))
        obj = c.write()
        path = c.objects / "__shared_data.obj"
        data = bytearray(coff.Coff.load(path).section(1).data)
        struct.pack_into("<I", data, 4, 4)
        raw = make_object([(".rdata", bytes(data), [(4, 2, 6), (16, 0, 6)], 0x40000040),
                           (".note.split", note([D, D + 8, 0]), [], 0x40000040)],
                          [(f"DAT_{D:08x}", 0, 1, 0, 2, b""),
                           (f"DAT_{D+8:08x}", 8, 1, 0, 2, b""),
                           ("Container", 0, 0, 0, 2, b"")])
        path.write_bytes(raw)
        self.assertEqual(for_project(c.project).symbol_address(obj, obj.slots[1]), U)

    def test_repeated_named_reads_parse_slot_lineage_once(self):
        c = self.case
        c.write()
        service = for_project(c.project)
        service._load()
        with patch("address_provenance.split_virtual_addresses", wraps=split_virtual_addresses) as parse:
            for _ in range(5):
                self.assertEqual(service._funcinfo_states(D + 8), 1)
        self.assertEqual(parse.call_count, 1)

    def test_repeated_named_reads_index_symbols_and_fields_once(self):
        class CountedList(list):
            iterations = 0

            def __iter__(self):
                self.iterations += 1
                return super().__iter__()

        c = self.case
        c.write()
        service = for_project(c.project)
        service._load()
        path = c.objects / "__shared_data.obj"
        owner = load_object(path)
        owner.symbols = CountedList(owner.symbols)
        section = owner.section(1)
        section.relocations = CountedList(section.relocations)
        service._data_objects[path] = service._stat(path), owner
        for _ in range(5):
            service._funcinfo_states(D + 8)
            service._original_pointer(owner, section, 4, D + 4)
        # One name index plus two iterations for the single append-lineage check.
        self.assertLessEqual(owner.symbols.iterations, 3)
        self.assertEqual(section.relocations.iterations, 1)

    def test_cached_named_owner_still_rejects_file_change(self):
        c = self.case
        c.write()
        service = for_project(c.project)
        service._load()
        self.assertEqual(service._funcinfo_states(D + 8), 1)
        path = c.objects / "__shared_data.obj"
        path.write_bytes(path.read_bytes() + b"changed")
        with self.assertRaises(ProvenanceError):
            service._funcinfo_states(D + 8)

    def test_named_index_preserves_conflicting_duplicate_definitions(self):
        c = self.case
        obj = c.write()
        path = c.objects / "__shared_data.obj"
        data = coff.Coff.load(path).section(1).data + bytes(28)
        raw = make_object([(".rdata", data, [(4, 2, 6), (16, 0, 6)], 0x40000040),
                           (".note.split", note([D, D + 8, 0, D + 8]), [], 0x40000040)],
                          [(f"DAT_{D:08x}", 0, 1, 0, 2, b""),
                           (f"DAT_{D+8:08x}", 8, 1, 0, 2, b""),
                           (f"Unwind@{U:08x}", 0, 0, 0, 2, b""),
                           (f"DAT_{D+8:08x}", 36, 1, 0, 2, b"")])
        path.write_bytes(raw)
        with self.assertRaises(ProvenanceError):
            for_project(c.project).symbol_address(obj, obj.slots[1])

    def test_missing_independent_target_name_rejects(self):
        c = self.case
        c.model["names"] = [x for x in c.model["names"] if x["addr"] != D + 8]
        with self.assertRaises(ProvenanceError):
            c.handler_view()


    def test_explicit_load_boundary_preserves_parser_bytes(self):
        c = self.case
        loaded = c.write()
        ordinary = coff.Coff.load(c.path)
        self.assertEqual(loaded.data, ordinary.data)
        self.assertEqual(source_path(loaded), c.path.resolve())
        self.assertIsNone(source_path(ordinary))
        self.assertEqual(split_virtual_addresses(loaded), split_virtual_addresses(ordinary))

    def test_reference_lookup_and_data_loaders_bind_actual_origins(self):
        c = self.case
        obj = c.write()
        image = TargetImage(c.project)
        self.assertEqual(source_path(image._object(str(c.path))), c.path.resolve())
        c.handler_view(obj)
        service = for_project(c.project)
        data_path = c.objects / "__shared_data.obj"
        self.assertEqual(source_path(service._data_objects[data_path][1]), data_path.resolve())

    def test_in_memory_object_cannot_inherit_file_witness(self):
        c = self.case
        loaded = c.write()
        memory = coff.Coff(loaded.data)
        self.assertIsNone(source_path(memory))
        self.assertIsNone(for_project(c.project).symbol_address(memory, memory.symbol(FUNCLET)))
        with self.assertRaises(ProvenanceError):
            c.handler_view(memory)

    def test_rewritten_memory_copy_does_not_inherit_origin(self):
        c = self.case
        loaded = c.write()
        edited = coff.Coff(loaded.rewrite(add=[("__except_list", 0, 0, 0, 2)]))
        self.assertIsNone(source_path(edited))
        self.assertIsNone(for_project(c.project).symbol_address(edited, edited.symbol(FUNCLET)))


if __name__ == "__main__":
    unittest.main()
