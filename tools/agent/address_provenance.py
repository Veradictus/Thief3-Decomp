"""Read object-owned original addresses without creating project-wide aliases.

Split VIRT entries survive name changes by raw symbol slot. They are witnesses
only after the declared model/group, object origin, slot lineage and independent
names agree. Undefined EH references need their original source-field relocation;
a zero note entry or a friendly name is never an address.
"""

import bisect
import hashlib
import json
import re
import struct
from pathlib import Path
from typing import Dict, Optional, Tuple

import coff


def load_object(path):
    """Load an unchanged Coff and bind its actual file origin for reference views."""
    obj = coff.Coff.load(path)
    obj._source_path = Path(path).resolve()
    return obj


def source_path(obj) -> Optional[Path]:
        """Where a loaded object came from; in-memory edited copies have no origin."""
        return getattr(obj, "_source_path", None)

def split_virtual_addresses(obj) -> Optional[Tuple[int, ...]]:
        """The producer's raw-slot-indexed VIRT note, without interpreting symbol names.

        The i386 producer writes four-byte addresses, including zero auxiliary
        gaps. Later append-only processing may leave a shorter descriptor;
        its lineage is checked by the provenance consumer, not guessed here.
        """
        notes = [s for s in obj.sections if s.name == ".note.split"]
        if not notes:
            return None
        if len(notes) != 1:
            raise ValueError("duplicate .note.split sections")
        data = notes[0].data
        if obj.machine != coff.IMAGE_FILE_MACHINE_I386 or len(data) < 20:
            raise ValueError("unsupported or truncated split metadata")
        namesz, descsz, kind = struct.unpack_from("<III", data)
        if namesz != 6 or kind != int.from_bytes(b"VIRT", "big") or data[12:20] != b"Split\0\0\0":
            raise ValueError("invalid split metadata header/name/type")
        if descsz % 4 or len(data) != 20 + descsz or descsz // 4 > len(obj.slots):
            raise ValueError("invalid split metadata length/slot count")
        values = struct.unpack_from(f"<{descsz // 4}I", data, 20)
        if any(a and obj.slots[i] is None for i, a in enumerate(values)):
            raise ValueError("split metadata gives an auxiliary slot an address")
        return values


class ProvenanceError(ValueError):
    """Malformed, stale or contradictory original-address evidence."""


def for_project(project):
    """One metadata snapshot/cache per project, shared by views and lookup."""
    if not hasattr(project, "_address_provenance"):
        project._address_provenance = OriginalAddresses(project)
    return project._address_provenance


class OriginalAddresses:
    def __init__(self, project):
        self.p = project
        self._loaded = False
        self._available = False
        self._stats = {}
        self._objects = {}
        self._data_objects = {}
        self._anchor_notes = {}
        self._defined_names = {}
        self._field_relocations = {}
        self.origins: Dict[Tuple[str, int], dict] = {}
        self.model_reads = 0

    @staticmethod
    def _stat(path):
        s = path.stat()
        return s.st_size, s.st_mtime_ns

    def _fresh(self):
        for path, stamp in self._stats.items():
            if not path.is_file() or self._stat(path) != stamp:
                raise ProvenanceError(f"original-address metadata changed: {path.name}")

    def _load(self):
        if self._loaded:
            self._fresh()
            return self._available
        self._loaded = True
        main, version = getattr(self.p, "main", None), getattr(self.p, "version", None)
        if main is None or version is None:
            return False
        folder = Path(main) / "build" / version
        model_path, group_path = folder / "delink.json", folder / "idapro.json"
        if not model_path.is_file() or not group_path.is_file():
            return False
        self._stats = {p: self._stat(p) for p in (model_path, group_path)}
        try:
            raw_model, raw_groups = model_path.read_bytes(), group_path.read_bytes()
            model, groups = json.loads(raw_model), json.loads(raw_groups)
            self.model_reads += 1
            if model.get("delink_ida_version") != 1 or model.get("meta", {}).get("bits") != 32 \
                    or model["meta"].get("endian") != "little" or model["meta"].get("arch") != "x86":
                raise ProvenanceError("unsupported original-address model schema/machine")
            self.functions = {}
            self.function_names = {}
            for f in model["functions"]:
                a, end, name = f["start"], f["end"], f["name"]
                if not isinstance(a, int) or not isinstance(end, int) or not 0 <= a < end <= 0x100000000:
                    raise ProvenanceError("invalid model function bounds")
                if a in self.functions and self.functions[a] != f:
                    raise ProvenanceError("conflicting model function anchors")
                if name in self.function_names and self.function_names[name] != a:
                    raise ProvenanceError("conflicting model function name")
                self.functions[a], self.function_names[name] = f, a
            self.starts = sorted(self.functions)
            self.names = {}
            self.named_addresses = {}
            for n in model["names"]:
                a, name = n["addr"], n["name"]
                if not isinstance(a, int) or not 0 <= a <= 0xFFFFFFFF:
                    raise ProvenanceError("invalid model name address")
                if name in self.named_addresses and self.named_addresses[name] != a:
                    raise ProvenanceError("conflicting model data/name anchor")
                self.named_addresses[name] = a
                self.names.setdefault(a, set()).add(name)
            self.relocations = {}
            for r in model["relocations"]:
                self.relocations.setdefault(r["addr"], []).append(r)
            self.groups = {}
            self.data_owners = []
            if not isinstance(groups, dict):
                raise ProvenanceError("invalid original-address groups")
            for key, group in groups.items():
                path = Path(key.replace("\\", "/"))
                if path.is_absolute() or ".." in path.parts:
                    raise ProvenanceError("invalid object group path")
                key = path.as_posix()
                ranges = {kind: [tuple(x) for x in group.get(kind, [])]
                          for kind in ("function_ranges", "rdata", "data", "bss")}
                if any(len(x) != 2 or not all(isinstance(a, int) for a in x) or x[0] >= x[1]
                       for values in ranges.values() for x in values):
                    raise ProvenanceError("invalid object group range")
                self.groups[key] = dict(ranges=ranges, functions=set(group.get("functions", [])))
                for kind in ("rdata", "data", "bss"):
                    self.data_owners.extend((a, b, key) for a, b in ranges[kind])
            self.model_identity = dict(model_sha256=hashlib.sha256(raw_model).hexdigest(),
                                       groups_sha256=hashlib.sha256(raw_groups).hexdigest())
        except (KeyError, TypeError, json.JSONDecodeError) as e:
            raise ProvenanceError(f"invalid original-address metadata: {e}") from e
        self._fresh()
        self._available = True
        return True

    def _group_key(self, obj):
        path, root = source_path(obj), getattr(self.p, "obj_dir", None)
        if path is None or root is None:
            return None
        try:
            return path.relative_to(Path(root).resolve()).as_posix()
        except ValueError:
            return None

    def _contains(self, key, address, code):
        if key == "__shared_data.obj":
            return not code and not any(a <= address < b for a, b, _ in self.data_owners)
        group = self.groups.get(key)
        if group is None:
            return False
        if code:
            function = self._function(address)
            return address in group["functions"] or (function is not None and function["start"] in group["functions"]) \
                or any(a <= address < b for a, b in group["ranges"]["function_ranges"])
        return any(a <= address < b for kind in ("rdata", "data", "bss") for a, b in group["ranges"][kind])

    def _relocation(self, address):
        entries = self.relocations.get(address, [])
        unique = {(r.get("type"), r.get("size"), r.get("target")) for r in entries}
        if len(unique) != 1:
            raise ProvenanceError("missing or conflicting original field relocation")
        kind, size, target = next(iter(unique))
        if kind != "OFF32" or size != 4 or not isinstance(target, int) or not 0 < target <= 0xFFFFFFFF:
            raise ProvenanceError("wrong original field relocation kind/width/target")
        return target

    def _eh_info(self, function):
        handler = coff.EH_HANDLER + function
        start = self.function_names.get(handler)
        if start is None or self.functions[start]["end"] - start != 10:
            raise ProvenanceError("missing original EH handler identity/bounds")
        target = self._relocation(start + 1)
        if target not in self.names:
            raise ProvenanceError("EH target has no independent original name")
        return start, target

    def _function(self, address):
        i = bisect.bisect_right(self.starts, address) - 1
        if i >= 0:
            f = self.functions[self.starts[i]]
            if address < f["end"]:
                return f
        return None

    def _renamed_funclet(self, sym, address):
        m = re.fullmatch(r"__unwindfunclet\$(.+)\$(\d+)", sym.name)
        if not m:
            return False
        _, info = self._eh_info(m[1])
        states = self._funcinfo_states(info)
        state = int(m[2])
        if state >= states:
            raise ProvenanceError("funclet state exceeds original FuncInfo bounds")
        _, owner, section, offset = self._named_view(info, 28)
        unwind = self._original_pointer(owner, section, offset + 8, info + 8)
        # Read the complete map, not merely a pointer at an unchecked index.
        _, obj, section, offset = self._named_view(unwind, states * 8)
        field = state * 8 + 4
        expected = self._original_pointer(obj, section, offset + field, unwind + field)
        return expected == address and address in self.functions

    def _original_pointer(self, obj, section, offset, original_field):
        """Join the model field to its actual COFF relocation, including folding."""
        expected = self._relocation(original_field)
        identity = (obj, id(obj.data), section.index)
        if identity not in self._field_relocations:
            fields = {}
            for r in section.relocations:
                fields.setdefault(r.offset, []).append(r)
            self._field_relocations[identity] = fields
        relocs = self._field_relocations[identity].get(offset, [])
        if len(relocs) != 1 or relocs[0].type != coff.IMAGE_REL_I386_DIR32:
            raise ProvenanceError("original unwind field lacks its COFF relocation")
        r = relocs[0]
        target = obj.slots[r.symbol]
        if target is None:
            raise ProvenanceError("invalid original unwind field target")
        base = (expected - obj.addend(section.index, r)) & 0xFFFFFFFF
        known = self.p.address_of(target.name)
        named = target.name in self.names.get(base, set()) \
            or self.function_names.get(target.name) == base
        if known is not None and known != base:
            raise ProvenanceError("conflicting original unwind field target")
        if target.defined:
            self._check_named_slot(obj, target, base)
        if known is None and not named:
            values = self._anchor_notes.get((obj, id(obj.data)))
            if not target.defined or values is None or target.index >= len(values) \
                    or values[target.index] != base:
                raise ProvenanceError("unwind field target lacks original slot/name evidence")
        return expected

    def _tail(self, obj, values):
        """Recognize only append-only passes documented by split.py/coff.py."""
        covered = [s for s in obj.symbols if s.index < len(values)]
        for s in obj.symbols:
            if s.index < len(values):
                continue
            if s.defined or s.aux or s.value or s.storage != coff.IMAGE_SYM_CLASS_EXTERNAL:
                raise ProvenanceError("unproven appended split symbol")
            if s.name == "__except_list":
                continue
            # fold_into appends an existing named container for an original
            # undefined DAT label strictly inside it; it never removes slots.
            known = getattr(self.p, "by_name", {}).get(s.name)
            if known is None or getattr(known, "size", 0) <= 1 or not any(
                    re.fullmatch(r"DAT_[0-9A-Fa-f]{8}", old.name) and not old.defined
                    and known.address < int(old.name[4:], 16) < known.address + known.size for old in covered):
                raise ProvenanceError("appended symbol lacks fold_into provenance")

    def _note(self, obj):
        # A parsed Coff's bytes are immutable. Reusing its identity avoids
        # hashing a shared data object once for every one of its symbols.
        identity = (obj, id(obj.data))
        if identity in self._objects:
            self._fresh()
            return self._objects[identity]
        try:
            values = split_virtual_addresses(obj)
        except ValueError as e:
            raise ProvenanceError(str(e)) from e
        if values is None:
            self._objects[identity] = None
            return None
        # Header/auxiliary/length failures reject even before a witness is used.
        available = self._load()
        self._tail(obj, values)
        key = self._group_key(obj)
        result = {}
        object_digest = hashlib.sha256(obj.data).hexdigest()
        referenced = {r.symbol for sec in obj.sections for r in sec.relocations}
        for i, address in enumerate(values):
            sym = obj.slots[i]
            if not address or sym is None:
                continue
            if not sym.defined:
                # fold_labels leaves historical addresses for now-undefined,
                # unreferenced interior labels. Never resolve them as externals.
                f = self._function(address) if available else None
                label = re.fullmatch(r"(?:\$L_|jpt_)([0-9A-Fa-f]+)", sym.name)
                named = sym.name in self.names.get(address, set()) if available else False
                named = named or (label is not None and int(label[1], 16) == address)
                if not available or i in referenced or f is None or address == f["start"] \
                        or not named or not self._contains(key, address, True):
                    raise ProvenanceError("nonzero undefined split slot lacks folded-label lineage")
                continue
            independent = self.p.address_of(sym.name)
            if independent is not None and independent != address:
                raise ProvenanceError(f"conflicting split/name address for {sym.name}")
            if not available or key is None:
                continue
            sec = obj.section(sym.section)
            if sec is None or sym.value >= len(sec.data) or not self._contains(key, address, sec.is_code):
                raise ProvenanceError("split slot disagrees with object group/bounds")
            original_names = self.names.get(address, set())
            f = self.functions.get(address)
            matches = sym.name in original_names or (f is not None and sym.name == f["name"])
            if not matches and independent is None:
                matches = self._renamed_funclet(sym, address)
            if not matches and independent is None:
                # Unsupported producer anchors/renames remain unknown.
                continue
            if sec.is_code and sym.is_function and f is not None and sym.value + f["end"] - address > len(sec.data):
                raise ProvenanceError("split function extent exceeds object section")
            result[i] = address
            self.origins[(str(source_path(obj)), i)] = dict(kind="VIRT+model+group", address=address,
                object_sha256=object_digest, group=key, **self.model_identity)
        self._objects[identity] = result
        return result

    def symbol_address(self, obj, sym):
        """An independent project name or validated defined raw-slot witness."""
        note = self._note(obj)
        known = self.p.address_of(sym.name)
        witnessed = note.get(sym.index) if note is not None and sym.defined else None
        if known is not None and witnessed is not None and known != witnessed:
            raise ProvenanceError("independent original-address witnesses disagree")
        return known if known is not None else witnessed

    def has_note(self, obj):
        return self._note(obj) is not None

    def _check_named_slot(self, obj, sym, address):
        """Check one anchored definition without recursively loading its peers.

        A data owner may contain the funclet currently being validated by _note.
        Re-entering symbol_address for this independent named data anchor would
        re-enter that unfinished note. Validate its own raw slot directly instead.
        """
        identity = (obj, id(obj.data))
        if identity not in self._anchor_notes:
            try:
                values = split_virtual_addresses(obj)
            except ValueError as e:
                raise ProvenanceError(str(e)) from e
            if values is not None:
                self._tail(obj, values)
            # Cache only successful immutable slot/append-lineage validation.
            self._anchor_notes[identity] = values
        values = self._anchor_notes[identity]
        if values is not None:
            if sym.index >= len(values):
                raise ProvenanceError("named EH definition lacks its original slot")
            witness = values[sym.index]
            if witness:
                sec = obj.section(sym.section)
                if witness != address or sec is None or not self._contains(self._group_key(obj), address, sec.is_code):
                    raise ProvenanceError("EH target name/slot/group conflict")

    def _named_view(self, address, size):
        candidates = [(a, b, key) for a, b, key in self.data_owners if a <= address and address + size <= b]
        keys = {key for _, _, key in candidates}
        if len(keys) > 1:
            raise ProvenanceError("conflicting data owners for original EH target")
        key = next(iter(keys)) if keys else "__shared_data.obj"
        path = Path(self.p.obj_dir) / key
        if not path.is_file():
            raise ProvenanceError("original EH target object is unreadable")
        stamp = self._stat(path)
        cached = self._data_objects.get(path)
        if cached is None:
            obj = load_object(path)
            self._data_objects[path] = stamp, obj
        else:
            if cached[0] != stamp:
                raise ProvenanceError("original EH target object changed")
            obj = cached[1]
        # Parsed Coff bytes/symbols are immutable, as for _objects above. Index
        # once rather than rescanning a potentially huge shared owner per state.
        identity = (obj, id(obj.data))
        if identity not in self._defined_names:
            names = {}
            for s in obj.symbols:
                if s.defined and not s.is_section:
                    names.setdefault(s.name, []).append(s)
            self._defined_names[identity] = names
        names = self._defined_names[identity]
        matches = sorted((s for name in self.names.get(address, set()) for s in names.get(name, [])
                          if self.p.address_of(s.name) == address), key=lambda s: s.index)
        if not matches:
            raise ProvenanceError("EH target lacks an independent readable named definition")
        views = []
        locations = []
        for s in matches:
            sec = obj.section(s.section)
            self._check_named_slot(obj, s, address)
            if sec is None or s.value + size > len(sec.data):
                raise ProvenanceError("EH target name/slot/extent conflict")
            views.append(sec.data[s.value:s.value + size])
            locations.append((obj, sec, s.value))
        if any(v != views[0] for v in views[1:]):
            raise ProvenanceError("conflicting named EH target definitions")
        return (views[0], *locations[0])

    def _read_named(self, address, size):
        return self._named_view(address, size)[0]

    def _funcinfo_states(self, target):
        # Shared by undefined FuncInfo and renamed funclet witnesses.
        data = self._read_named(target, 28)
        magic, states = struct.unpack_from("<Ii", data)
        if magic & ~3 != coff.EH_MAGIC or not 0 <= states <= 0x1000:
            raise ProvenanceError("original named FuncInfo is not a supported EH table")
        return states

    def relocation_address(self, obj, section, relocation, offset, address):
        """Base of an undefined friendly FuncInfo, proved by its original field."""
        sym = obj.slots[relocation.symbol]
        if sym.defined or not sym.name.startswith("__ehfuncinfo$"):
            return None
        if not self._load():
            return None
        function = sym.name[len("__ehfuncinfo$"):]
        handler = obj.symbol(coff.EH_HANDLER + function)
        if handler is None or not handler.defined or handler.section != section.index \
                or relocation.offset != handler.value + 1 or relocation.type != coff.IMAGE_REL_I386_DIR32 \
                or obj.addend(section.index, relocation) != 0:
            raise ProvenanceError("EH external is not the original handler field")
        start, target = self._eh_info(function)
        actual = self.symbol_address(obj, handler)
        if actual != start or address + handler.value - offset != start:
            raise ProvenanceError("EH source view disagrees with original handler")
        key = self._group_key(obj)
        if key is None or not self._contains(key, start, True):
            raise ProvenanceError("EH source object/group identity mismatch")
        self._funcinfo_states(target)
        self.origins[(str(source_path(obj)), sym.index)] = dict(kind="original-handler-field+named-target",
            address=target, source_field=start + 1, relocation_type=relocation.type, addend=0,
            object_sha256=hashlib.sha256(obj.data).hexdigest(), group=key, **self.model_identity)
        return target
