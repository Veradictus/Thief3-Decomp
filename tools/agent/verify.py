"""Compile a candidate and compare one function with its target: the rulers behind try.py and accept.py.

Pairing. The target function and everything it references carry the names
symbols.txt gives them (FUN_10a52530, DAT_.., or real names); the compiled
candidate uses MSVC decorated names. Nothing is paired by name. Instead:

  1. A copy of the candidate object is edited: its function is renamed to the
     target's name, and MSVC's `$L` labels inside it (switch case labels and
     tables) become function+offset references, as in delink's objects. A
     boundary symbol ends each side at its code, so switch tables do not
     reach objdiff as instructions.
  2. objdiff aligns the two functions (functionRelocDiffs=none) and reports
     opcode and operand differences. Its own relocation rulers are not used:
     they compare names or section offsets. Names differ between the two
     sides by construction, and every COMDAT symbol MSVC emits sits at
     offset 0 of its own section, so a wrong literal defined on both sides
     reads as equal in every mode.
  3. Each aligned row is then compared byte for byte outside relocated
     fields, and every relocation pair is resolved to target *addresses*:
       - code reference ruler: a referenced function or global must be the
         one symbols.txt names at that address (same decorated name, or a
         `Class::Method` name the decorated name demangles to). An address
         symbols.txt leaves unnamed (FUN_/DAT_) gets a provisional binding,
         which must agree with symbols.txt and every accepted record (one
         address, one name) and is recorded for the lead to review.
       - data ruler: literals and other constant or local data the candidate
         defines (__real@ floats, ??_C@ strings, EH tables) are compared by
         value with the target's bytes, recursively through their pointers,
         so EH handlers, unwind funclets and their tables are checked too.
     The target's bytes come from the exe (orig/) when present, else from the
     split objects.
  4. Switch tables after the code, and the region's length, are compared the
     same way.
"""

import hashlib
import json
import struct
import subprocess
from bisect import bisect_right
from dataclasses import dataclass, field
from pathlib import Path
from typing import Dict, List, Optional, Set, Tuple

import coff
from common import Project, demangle, fmt_addr, is_placeholder, qualified_name

# Absolute symbols MSVC relocates against where the linked exe holds a plain value.
ABSOLUTE = {"__except_list": 0, "__tls_array": 0x2C}
BOUNDARY = "$t3_end"
COMDAT_SELECT_ASSOCIATIVE = 5


@dataclass
class Insn:
    offset: int  # from the function start
    size: int
    text: str


@dataclass
class Row:
    t: Optional[Insn]
    s: Optional[Insn]
    kind: str = ""  # objdiff's diff kind (replace/insert/delete/op/arg), or reloc/bytes from the rulers
    notes: List[str] = field(default_factory=list)


@dataclass
class Binding:
    addr: int
    target: str  # the name symbols.txt (or delink) gives the address
    name: str  # the candidate's symbol
    kind: str  # function, data, literal, ehhandler, funclet, ehdata, local
    status: str  # named, compatible, provisional, verified
    size: int = 0  # verified code and data: the bytes compared

    def to_json(self) -> dict:
        out = {"addr": fmt_addr(self.addr), "target": self.target, "name": self.name,
               "kind": self.kind, "status": self.status}
        if self.size:
            out["size"] = self.size
        return out


@dataclass
class Result:
    addr: int
    target: str
    size: int
    symbol: str = ""
    demangled: str = ""
    build_ok: bool = False
    build_log: str = ""
    rows: List[Row] = field(default_factory=list)
    problems: List[str] = field(default_factory=list)  # failures outside the rows
    bindings: List[Binding] = field(default_factory=list)
    codegen: str = ""  # hash of the compiled function's bytes and relocations
    mnemonics: List[str] = field(default_factory=list)  # the target's, for similarity search

    @property
    def mismatch_rows(self) -> int:
        return sum(1 for r in self.rows if r.kind)

    @property
    def match(self) -> bool:
        return self.build_ok and bool(self.rows) and not self.mismatch_rows and not self.problems

    @property
    def score(self) -> float:
        """Percentage of clean rows, rounded down; never 100.0 unless it matches."""
        if not self.build_ok or not self.rows:
            return 0.0
        pct = int(1000 * (len(self.rows) - self.mismatch_rows) / len(self.rows)) / 10
        return 100.0 if self.match else min(pct, 99.9)

    def provisional(self) -> List[Binding]:
        return [b for b in self.bindings if b.status == "provisional"]

    def to_json(self) -> dict:
        return {
            "addr": fmt_addr(self.addr), "target": self.target, "size": self.size, "symbol": self.symbol,
            "demangled": self.demangled, "build_ok": self.build_ok, "match": self.match, "score": self.score,
            "mismatch_rows": self.mismatch_rows, "rows": len(self.rows), "problems": self.problems,
            "bindings": [b.to_json() for b in self.bindings], "codegen": self.codegen,
        }


class TargetImage:
    """The original program's bytes and pointers by address: the exe when present, else the split objects."""

    def __init__(self, project: Project):
        self.p = project
        self.pe = None
        if project.exe and project.exe.is_file():
            import pe
            self.pe = pe.PE(project.exe.read_bytes())
        self._index: Optional[List[Tuple[int, str, int, int]]] = None
        self._starts: List[int] = []
        self._objs: Dict[str, coff.Coff] = {}

    def _object(self, path: str) -> coff.Coff:
        if path not in self._objs:
            self._objs[path] = coff.Coff.load(Path(path))
        return self._objs[path]

    def _locate(self, address: int, size: int) -> Optional[Tuple[coff.Coff, coff.Section, int]]:
        """The split object, section and offset holding [address, address + size)."""
        if self._index is None:
            entries = []
            if self.p.obj_dir.is_dir():
                for path in sorted(self.p.obj_dir.rglob("*.obj")):
                    obj = self._object(str(path))
                    for s in obj.symbols:
                        a = self.p.address_of(s.name) if s.defined and not s.is_section else None
                        if a is not None:
                            entries.append((a, str(path), s.section, s.value))
            entries.sort()
            self._index = entries
            self._starts = [e[0] for e in entries]
        i = bisect_right(self._starts, address) - 1
        while i >= 0:
            start, path, section, value = self._index[i]
            sec = self._object(path).section(section)
            offset = value + address - start
            if offset + size <= len(sec.data):
                return self._object(path), sec, offset
            if address - start > 0x100000:
                break
            i -= 1
        return None

    def view(self, address: int, size: int) -> Optional["View"]:
        """The target's bytes at [address, address + size) and, from split objects, their relocations."""
        if self.pe:
            try:
                return View(address, self.pe.read_rva(address - self.pe.image_base, size), None)
            except ValueError:
                return None
        found = self._locate(address, size)
        if not found:
            return None
        obj, sec, offset = found
        return object_view(self.p, obj, sec, offset, size, address)

    def in_image(self, value: int) -> bool:
        return self.pe is not None and self.pe.image_base <= value < self.pe.image_base + self.pe.image_size

    def pointer(self, view: "View", k: int, rtype: int) -> Optional[Tuple[int, str]]:
        """(address, target's name) a field of an exe view points to, or None when it holds no pointer."""
        value = struct.unpack_from("<i", view.data, k)[0]
        rel = rtype == coff.IMAGE_REL_I386_REL32
        target = (view.address + k + 4 + value if rel else value) & 0xFFFFFFFF
        if not self.in_image(target):
            return None
        sym = self.p.by_addr.get(target)
        return target, sym.name if sym else ""

    def pointer_offsets(self, view: "View") -> Set[int]:
        """Offsets of a data view's pointer fields, as tools/delink_model.py finds them."""
        if view.relocs is not None:
            return set(view.relocs)
        return {o for o in range(-view.address % 4, len(view.data) - 3, 4)
                if self.in_image(struct.unpack_from("<I", view.data, o)[0])}


@dataclass
class View:
    address: int
    data: bytes
    relocs: Optional[Dict[int, Tuple[Optional[int], str, int]]]  # offset -> (address, name, type); None: unknown


def object_view(project: Project, obj: coff.Coff, sec: coff.Section, offset: int, size: int, address: int) -> View:
    """A target object's bytes and relocations; references resolve by name (symbols.txt or the address in a
    placeholder name), else as a position in the same section."""
    section_base = address - offset
    relocs = {}
    for _, r in obj.relocations(sec.index, offset, offset + size):
        sym = obj.slots[r.symbol]
        base = project.address_of(sym.name)
        if base is None and sym.defined and sym.section == sec.index:
            base = section_base + sym.value
        relocs[r.offset - offset] = (None if base is None else (base + obj.addend(sec.index, r)) & 0xFFFFFFFF,
                                     sym.name, r.type)
    return View(address, sec.data[offset:offset + size], relocs)


def objdiff_rows(project: Project, target_obj: Path, base_obj: Path, symbol: str) -> Tuple[List[Row], dict]:
    """objdiff's aligned instruction rows for `symbol` (present in both objects)."""
    cmd = [str(project.objdiff), "diff", "-1", str(target_obj), "-2", str(base_obj), "-o", "-", "--format", "json",
           "-c", "functionRelocDiffs=none", symbol]
    proc = subprocess.run(cmd, capture_output=True, text=True, errors="replace")
    if proc.returncode != 0:
        raise RuntimeError(f"objdiff failed: {proc.stderr.strip()[-2000:]}")
    data = json.loads(proc.stdout)
    left = next((s for s in data["left"]["symbols"] if s["name"] == symbol), None)
    right = next((s for s in data.get("right", {}).get("symbols", []) if s["name"] == symbol), None)
    if left is None or right is None:
        raise RuntimeError(f"objdiff did not pair {symbol}")

    # objdiff gives section offsets (for the symbol and each instruction), and a
    # split object holds many functions per section: rows use offsets from the
    # function's start.
    def insn(row: dict, start: int) -> Optional[Insn]:
        i = row.get("instruction")
        return Insn(int(i.get("address", 0)) - start, int(i.get("size", 0)), i.get("formatted", "")) if i else None

    def mnemonic(row: dict) -> str:
        for part in row.get("instruction", {}).get("parts", []):
            if "opcode" in part:
                return part["opcode"].get("mnemonic", "")
        return ""

    rows = []
    left_start, right_start = int(left.get("address", 0)), int(right.get("address", 0))
    for a, b in zip(left.get("instructions", []), right.get("instructions", [])):
        kind = a.get("diff_kind") or b.get("diff_kind") or ""
        rows.append(Row(insn(a, left_start), insn(b, right_start), kind.replace("DIFF_", "").lower()))
    return rows, {"mnemonics": [mnemonic(a) for a in left.get("instructions", []) if a.get("instruction")]}


class Verifier:
    def __init__(self, project: Project):
        self.p = project
        self.image = TargetImage(project)

    # -- the candidate -----------------------------------------------------------
    def pick(self, obj: coff.Coff, target: str, dem: Dict[str, str], symbol: Optional[str]) -> coff.Symbol:
        """The candidate's function: --symbol, else the one whose name matches the target's, else the
        only non-inline function the file defines."""
        defined = [s for s in obj.functions() if s.external]
        if symbol:
            found = [s for s in defined if s.name == symbol]
            if not found:
                raise ValueError(f"{symbol} is not defined in the compiled file")
            return found[0]
        if not is_placeholder(target):
            found = [s for s in defined if s.name == target or qualified_name(s.name, dem.get(s.name, "")) == target]
            if len(found) == 1:
                return found[0]
        own = [s for s in defined if obj.section(s.section).selection != coff.IMAGE_COMDAT_SELECT_ANY]
        if len(own) == 1:
            return own[0]
        names = ", ".join(s.name for s in (own or defined)) or "none"
        raise ValueError(f"cannot tell which function is the candidate (defined: {names}); define exactly one "
                         f"non-inline function or pass --symbol")

    def _prepare_candidate(self, obj: coff.Coff, fn: coff.Symbol, target: str) -> Tuple[bytes, int, int]:
        """The edited copy of the candidate (see the module docstring), its code length and its length with
        the tables after the code."""
        sec = obj.section(fn.section)
        # The function runs to the next symbol that is not one of MSVC's local `$` labels.
        fn_end = min([s.value for s in obj.symbols if s.section == fn.section and s.value > fn.value
                      and not s.is_section and not s.name.startswith("$")] + [len(sec.data)])
        labels = {s.index: s for s in obj.symbols if s.section == fn.section and s.name.startswith("$")
                  and fn.value < s.value < fn_end}
        # A table's label is referenced from before it (the dispatch); case labels only from the tables after them.
        tables = [labels[r.symbol].value for r in sec.relocations
                  if r.symbol in labels and r.offset < labels[r.symbol].value]
        code_end = min(tables + [fn_end]) - fn.value
        retarget, patch = {}, {}
        for i, r in enumerate(sec.relocations):
            if r.symbol in labels:
                retarget[(sec.index, i)] = fn.index
                patch[(sec.index, r.offset)] = struct.pack("<i", obj.addend(sec.index, r) + labels[r.symbol].value
                                                           - fn.value)
        rename = {fn.name: target}
        clash = obj.symbol(target)
        if clash is not None and clash is not fn:
            rename[target] = target + "$candidate"
        add = [(BOUNDARY, fn.value + code_end, fn.section, 0, coff.IMAGE_SYM_CLASS_STATIC)] \
            if fn.value + code_end < fn_end else []
        data = obj.rewrite(rename=rename, undefine=[s.name for s in labels.values()], retarget=retarget,
                           patch=patch, add=add)
        return data, code_end, fn_end - fn.value

    # -- the check -----------------------------------------------------------------
    def run(self, address: int, source: Optional[Path], workdir: Path, symbol: Optional[str] = None,
            cflags: Optional[List[str]] = None, target_obj: Optional[Path] = None,
            compiled: Optional[Path] = None) -> Result:
        """Compile `source` (or take the `compiled` object) and compare its function with the target's."""
        p = self.p
        f = p.function(address)
        res = Result(address, f.name, f.size)
        code_end, region_end = p.code_extent(address)
        tpath = target_obj or p.target_object(address)
        if tpath is None:
            unit = p.unit_for(address)
            if unit and p.obj_dir.is_dir():
                res.problems.append(f"{p.obj_dir / unit.object} is missing: splits.txt changed since the last "
                                    f"split; run python configure.py && ninja")
            else:
                res.problems.append(f"no target objects under {p.obj_dir}: run python configure.py && ninja "
                                    f"(needs orig/{p.version}/)")
            return res
        workdir.mkdir(parents=True, exist_ok=True)
        out = compiled or workdir / "candidate.obj"
        if compiled is None:
            res.build_ok, res.build_log = p.compile(source, out, cflags or p.cflags_for(address))
            if not res.build_ok:
                return res
        res.build_ok = True

        obj = coff.Coff.load(out)
        dem = demangle(p, [s.name for s in obj.symbols] + [f.name])
        try:
            fn = self.pick(obj, f.name, dem, symbol)
        except ValueError as e:
            res.problems.append(str(e))
            return res
        res.symbol, res.demangled = fn.name, dem.get(fn.name, "")

        tobj = coff.Coff.load(tpath)
        tfn = target_symbol(tobj, f.name, address)
        if tfn is None:
            res.problems.append(f"{tpath.name} does not define {f.name}: the split is older than symbols.txt; "
                                f"run ninja")
            return res
        cdata, s_code, s_len = self._prepare_candidate(obj, fn, tfn.name)
        cpath = workdir / "candidate.paired.obj"
        cpath.write_bytes(cdata)
        cand = coff.Coff(cdata)
        cfn = cand.symbol(tfn.name)
        tsec = tobj.section(tfn.section)
        t_code = code_end - address
        add = []
        # delink labels a jump table after the code (jpt_...), but objdiff does not end a function at a label.
        if tfn.value + t_code < len(tsec.data) and not any(
                s.section == tfn.section and s.value == tfn.value + t_code
                and s.storage != coff.IMAGE_SYM_CLASS_LABEL for s in tobj.symbols):
            add = [(BOUNDARY, tfn.value + t_code, tfn.section, 0, coff.IMAGE_SYM_CLASS_STATIC)]
        tcopy = workdir / "target.obj"
        tcopy.write_bytes(tobj.rewrite(add=add))

        try:
            res.rows, extra = objdiff_rows(p, tcopy, cpath, tfn.name)
        except RuntimeError as e:
            res.problems.append(str(e))
            return res
        res.mnemonics = extra["mnemonics"]

        check = _Check(self, res, address, tobj, tfn, cand, cfn, dem)
        check.rows()
        check.tail(s_code, s_len, t_code, region_end - address, tsec)
        check.own_name()
        res.codegen = check.codegen(s_len)
        return res


def target_symbol(tobj: coff.Coff, name: str, address: int) -> Optional[coff.Symbol]:
    """The target function in its split object: by its symbols.txt name, or by the placeholder name an
    older split gave it (after integrate.py renamed it and before ninja re-split)."""
    for candidate in (name, f"FUN_{address:08x}"):
        sym = tobj.symbol(candidate)
        if sym is not None and sym.defined:
            return sym
    return None


def target_listing(project: Project, address: int, workdir: Path) -> Optional[Tuple[List[Insn], List[str]]]:
    """The target function's instructions and mnemonics, as objdiff shows them (code only, no tables)."""
    path = project.target_object(address)
    if path is None:
        return None
    f = project.function(address)
    tobj = coff.Coff.load(path)
    tfn = target_symbol(tobj, f.name, address)
    if tfn is None:
        return None
    sec = tobj.section(tfn.section)
    t_code = project.code_extent(address)[0] - address
    add = [(BOUNDARY, tfn.value + t_code, tfn.section, 0, coff.IMAGE_SYM_CLASS_STATIC)] \
        if tfn.value + t_code < len(sec.data) else []
    workdir.mkdir(parents=True, exist_ok=True)
    copy = workdir / "target.obj"
    copy.write_bytes(tobj.rewrite(add=add))
    rows, extra = objdiff_rows(project, copy, copy, tfn.name)
    return [r.t for r in rows if r.t], extra["mnemonics"]


class _Check:
    """One comparison: the rulers applied to a paired candidate and target."""

    def __init__(self, v: Verifier, res: Result, address: int, tobj: coff.Coff, tfn: coff.Symbol,
                 cand: coff.Coff, cfn: coff.Symbol, dem: Dict[str, str]):
        self.v, self.p, self.res, self.address = v, v.p, res, address
        self.tobj, self.tfn, self.tsec = tobj, tfn, tobj.section(tfn.section)
        self.cand, self.cfn, self.csec = cand, cfn, cand.section(cfn.section)
        self.dem = dem
        self.by_addr: Dict[int, Binding] = {}
        self.by_name: Dict[str, int] = {}
        self.visited: Dict[Tuple[int, int], Optional[str]] = {}  # (symbol, address) -> blob() result
        self.registry_names: Dict[str, Tuple[int, str]] = {}
        self.registry_addrs: Dict[int, Tuple[str, str]] = {}
        for other, record in self.p.accepted().items():
            if other == address:
                continue
            for b in record.get("bindings", []) + [{"addr": record["addr"], "name": record.get("symbol", "")}]:
                if b.get("name") and not b["name"].startswith("$") and b.get("kind") not in ("funclet", "ehdata"):
                    a = int(b["addr"], 16)
                    self.registry_names.setdefault(b["name"], (a, record["addr"]))
                    self.registry_addrs.setdefault(a, (b["name"], record["addr"]))

    # -- rows --------------------------------------------------------------------
    def rows(self) -> None:
        for row in self.res.rows:
            if row.kind or row.t is None or row.s is None:
                if not row.kind:
                    row.kind = "delete" if row.s is None else "insert"
                continue
            if row.t.size != row.s.size:
                row.kind = "bytes"
                row.notes.append("instruction encodings differ in length")
                continue
            t_addr = self.address + row.t.offset
            view = object_view(self.p, self.tobj, self.tsec, self.tfn.value + row.t.offset, row.t.size, t_addr)
            notes = self.compare(view, self.cand, self.csec, self.cfn.value + row.s.offset, row.s.size, t_addr)
            if notes:
                row.kind = "reloc" if any(n.startswith("reloc") for n in notes) else "bytes"
                row.notes += [n.split(": ", 1)[1] if n.startswith("reloc: ") else n for n in notes]

    def compare(self, view: Optional[View], cobj: coff.Coff, csec: coff.Section, c_off: int, size: int,
                t_addr: int) -> List[str]:
        """Compare `size` candidate bytes with a target view; notes about what differs (reloc: ... for references)."""
        if view is None:
            return [f"cannot read the target at {fmt_addr(t_addr)} (needs orig/ or the split objects)"]
        notes = []
        c_rel = {r.offset - c_off: r for _, r in cobj.relocations(csec.index, c_off, c_off + size)}
        t_rel = view.relocs or {}
        c_bytes, t_bytes = csec.data[c_off:c_off + size], view.data
        masked = set()
        for k in list(c_rel) + list(t_rel):
            masked.update(range(k, k + 4))
        diff = [i for i in range(size) if i not in masked and t_bytes[i] != c_bytes[i]]
        if diff:
            notes.append(f"bytes differ at +{diff[0]:#x}")
        for k in sorted(set(c_rel) | set(t_rel)):
            cr = c_rel.get(k)
            csym = cobj.slots[cr.symbol] if cr else None
            # A plain value in the exe; tools/split.py relocates __except_list in the split objects.
            if csym is not None and csym.name in ABSOLUTE and (k not in t_rel or t_rel[k][1] == csym.name):
                if struct.unpack_from("<I", t_bytes, k)[0] != ABSOLUTE[csym.name] + cobj.addend(csec.index, cr):
                    notes.append(f"reloc: {csym.name} does not match the target's value")
                continue
            if cr is None:
                notes.append(f"reloc: the target references {t_rel[k][1]} where the candidate has a constant")
                continue
            if view.relocs is None:
                ref = self.v.image.pointer(view, k, cr.type)
                if ref is None:
                    notes.append(f"reloc: the target has no pointer at {fmt_addr(t_addr + k)}")
                    continue
                target, tname = ref
            elif k not in t_rel:
                notes.append(f"reloc: the candidate references {csym.name} where the target has a constant")
                continue
            else:
                target, tname, ttype = t_rel[k]
                if ttype != cr.type:
                    notes.append("reloc: relocation types differ")
                    continue
                if target is None:
                    notes.append(f"reloc: cannot resolve the target's {tname} (split older than symbols.txt? "
                                 f"run ninja)")
                    continue
            problem = self.reference(target, tname, cobj, csym, cobj.addend(csec.index, cr))
            if problem:
                notes.append("reloc: " + problem)
        return notes

    # -- references --------------------------------------------------------------
    def reference(self, target: int, tname: str, cobj: coff.Coff, csym: coff.Symbol, cadd: int) -> Optional[str]:
        """Check that candidate symbol+addend denotes target address `target`; None when it does."""
        if csym is self.cfn or (cobj is self.cand and csym.defined and csym.section == self.cfn.section):
            offset = csym.value - self.cfn.value + cadd
            if target != self.address + offset:
                there = f"function+{target - self.address:#x}" if 0 <= target - self.address < 0x100000 \
                    else fmt_addr(target)
                return f"points to function+{offset:#x}, the target to {there}"
            return None
        base = (target - cadd) & 0xFFFFFFFF
        if csym.defined:
            sec = cobj.section(csym.section)
            local = (not csym.external or csym.name.startswith(("$", "__ehhandler$", "__real@", "??_C@"))
                     or sec.selection == COMDAT_SELECT_ASSOCIATIVE)
            if sec.is_code and local:
                kind = "ehhandler" if csym.name.startswith("__ehhandler$") else \
                    "funclet" if sec.name.startswith(".text$x") else "local"
                return self.blob(base, cobj, csym, kind)
            if not sec.is_code and (local or not sec.writable):
                kind = "literal" if csym.name.startswith(("__real@", "??_C@")) else \
                    "ehdata" if sec.name.startswith(".xdata") or csym.name.startswith("$T") else "data"
                return self.blob(base, cobj, csym, kind)
        base_sym = self.p.by_addr.get(base)
        if base_sym is None and self.p.address_of(tname) == base:
            name = tname
        else:
            name = base_sym.name if base_sym else ""
        return self.name_rule(base, name, csym.name, csym.is_function)

    def name_rule(self, base: int, tname: str, name: str, is_func: bool) -> Optional[str]:
        where = f"{fmt_addr(base)} ({tname or 'unnamed'})"
        known = self.p.by_name.get(name)
        if tname and not is_placeholder(tname):
            if tname == name:
                status = "named"
            elif qualified_name(name, self.dem.get(name, "")) == tname:
                status = "compatible"
            else:
                return f"the candidate uses {name}; the target uses {where}"
        else:
            if known is not None and known.address != base:
                return f"the candidate uses {name}, which symbols.txt puts at {fmt_addr(known.address)}; " \
                       f"the target uses {where}"
            other = self.registry_names.get(name)
            if other and other[0] != base:
                return f"the candidate uses {name}, which accepted {other[1]} binds to {fmt_addr(other[0])}; " \
                       f"the target uses {where}"
            other = self.registry_addrs.get(base)
            if other and other[0] != name:
                return f"the target uses {where}, which accepted {other[1]} names {other[0]}; the candidate " \
                       f"uses {name}"
            tsym = self.p.by_addr.get(base)
            if tsym is not None and tsym.address == base and tsym.is_function != is_func and not name.startswith(
                    "__imp_"):
                return f"the candidate uses {'function' if is_func else 'data'} {name}; the target " \
                       f"{'function' if tsym.is_function else 'data'} at {where}"
            status = "provisional"
        return self.bind(base, tname or f"{'FUN' if is_func else 'DAT'}_{base:08x}", name,
                         "function" if is_func else "data", status)

    def bind(self, base: int, tname: str, name: str, kind: str, status: str) -> Optional[str]:
        current = self.by_addr.get(base)
        if current is not None and current.name != name:
            return f"{fmt_addr(base)} is used as both {current.name} and {name}"
        if self.by_name.get(name, base) != base and not name.startswith("$"):
            return f"{name} is used for both {fmt_addr(self.by_name[name])} and {fmt_addr(base)}"
        if current is None:
            b = Binding(base, tname, name, kind, status)
            self.by_addr[base] = b
            self.by_name[name] = base
            self.res.bindings.append(b)
        return None

    def blob(self, base: int, cobj: coff.Coff, csym: coff.Symbol, kind: str) -> Optional[str]:
        """Compare a local code or data symbol of the candidate with the target's bytes at `base`."""
        key = (csym.index, base)
        if key not in self.visited:
            self.visited[key] = None  # a structure that points back to itself holds so far
            self.visited[key] = self._blob(base, cobj, csym, kind)
        return self.visited[key]

    def _blob(self, base: int, cobj: coff.Coff, csym: coff.Symbol, kind: str) -> Optional[str]:
        tname = (self.p.by_addr[base].name if base in self.p.by_addr else "") or f"DAT_{base:08x}"
        problem = self.bind(base, tname, csym.name, kind, "verified")
        if problem:
            return problem
        sec = cobj.section(csym.section)
        start, end = cobj.extent(csym)
        view = self.v.image.view(base, end - start)
        notes = self.compare(view, cobj, sec, start, end - start, base)
        if view is not None and view.relocs is None and not sec.is_code and kind != "literal":
            # From the exe, a dword that looks like an address counts as a pointer (as in
            # tools/delink_model.py); literals hold none, whatever their bits look like.
            mine = {r.offset - start for _, r in cobj.relocations(sec.index, start, end)}
            for k in sorted(self.v.image.pointer_offsets(view) - mine):
                notes.append(f"the target holds a pointer at +{k:#x} where the candidate has a constant")
        what = {"literal": "literal", "ehdata": "EH table", "funclet": "unwind funclet", "ehhandler": "EH handler",
                "local": "local function"}.get(kind, kind)
        if notes:
            self.res.bindings = [b for b in self.res.bindings if not (b.addr == base and b.name == csym.name)]
            self.by_addr.pop(base, None)
            # Nested structures (handler > table > funclet) read as one chain down to the difference.
            note = notes[0][len("reloc: "):] if notes[0].startswith("reloc: ") else notes[0]
            sep = " > " if note.split(" ", 1)[0] in ("literal", "EH", "unwind", "local", "data") else ": "
            return f"{what} {csym.name} ({fmt_addr(base)}){sep}{note}"
        self.by_addr[base].size = end - start
        return None

    # -- whole-function checks ------------------------------------------------------
    def tail(self, s_code: int, s_len: int, t_code: int, t_region: int, tsec: coff.Section) -> None:
        """Switch tables after the code: same length and equivalent contents."""
        if s_code >= s_len and t_region <= t_code:
            return
        if s_len - s_code != t_region - t_code:
            self.res.problems.append(f"data after the code differs in size: candidate {s_len - s_code:#x} bytes, "
                                     f"target {t_region - t_code:#x} (switch tables)")
            return
        size, t_addr = s_len - s_code, self.address + t_code
        if self.tfn.value + t_region <= len(tsec.data):
            view = object_view(self.p, self.tobj, tsec, self.tfn.value + t_code, size, t_addr)
        else:
            view = self.v.image.view(t_addr, size)
        notes = self.compare(view, self.cand, self.csec, self.cfn.value + s_code, size, t_addr)
        self.res.problems += [f"switch tables: {n}" for n in notes]

    def own_name(self) -> None:
        name = self.res.symbol
        known = self.p.by_name.get(name)
        if known is not None and known.address != self.address:
            self.res.problems.append(f"the candidate defines {name}, which symbols.txt puts at "
                                     f"{fmt_addr(known.address)}")
        other = self.registry_names.get(name)
        if other and other[0] != self.address:
            self.res.problems.append(f"the candidate defines {name}, which accepted {other[1]} binds to "
                                     f"{fmt_addr(other[0])}")
        target = self.res.target
        if not is_placeholder(target) and target != name and qualified_name(name, self.dem.get(name, "")) != target:
            self.res.problems.append(f"the target is named {target}; the candidate defines {name}")

    def codegen(self, length: int) -> str:
        """Identity of the compiled function: its bytes and what each relocation points to."""
        h = hashlib.sha1(self.csec.data[self.cfn.value:self.cfn.value + length])
        for _, r in self.cand.relocations(self.csec.index, self.cfn.value, self.cfn.value + length):
            h.update(f"{r.offset}:{self.cand.slots[r.symbol].name}:{r.type}".encode())
        return h.hexdigest()[:16]


def render(res: Result, context: int = 1, limit: int = 40) -> List[str]:
    """The differing rows with `context` rows around them, BW1 style:
    `~` differs, `<` target only, `>` candidate only, `r` reference or bytes."""
    marks = {"insert": ">", "delete": "<", "reloc": "r", "bytes": "r"}
    show: Set[int] = set()
    for i, row in enumerate(res.rows):
        if row.kind:
            show.update(range(max(0, i - context), min(len(res.rows), i + context + 1)))
    lines, last = [], -1
    for i in sorted(show):
        if len(lines) >= limit:
            lines.append(f"   ... {sum(1 for r in res.rows[i:] if r.kind)} more differing rows")
            break
        if last >= 0 and i != last + 1:
            lines.append("   ...")
        last = i
        row = res.rows[i]
        mark = marks.get(row.kind, "~") if row.kind else " "
        off = f"{row.t.offset:04x}" if row.t else "    "
        left = row.t.text if row.t else ""
        right = row.s.text if row.s else ""
        lines.append(f"{mark} {off}  {left[:44]:<44} | {right[:44]}")
        for note in row.notes:
            lines.append(f"         ! {note}")
    return lines
