"""Synthetic targets for the matching tools' tests: no game code or data involved.

Reference C++ is compiled with the project's compiler, then reshaped the way
delink shapes a split of T3Main.exe: every symbol is given an address in the
exe's layout and renamed to the placeholder symbols.txt would use (FUN_...,
DAT_..., Unwind@...) unless the test names it; MSVC's `$L` labels become
function+offset references; __except_list relocations disappear (the exe
holds a plain fs:[0]); and data moves out of the code object into a
__shared_data object. The result is a small project directory (config, split
objects, state) that the tools use through the T3_AGENT_* variables.
"""

import os
import struct
from dataclasses import dataclass, field
from pathlib import Path
from typing import Dict, Optional, Set

import coff
from common import Project

TEXT, TEXT_X, RDATA, XDATA, DATA, EXTERN_FN, EXTERN_DATA = (
    0x10901000, 0x10E02DA0, 0x10E50000, 0x10E60000, 0x10F10000, 0x10A00000, 0x10F00000)


def align(value: int, to: int = 16) -> int:
    return (value + to - 1) & ~(to - 1)


@dataclass
class Target:
    """Where each of the reference object's symbols landed."""
    addresses: Dict[str, int] = field(default_factory=dict)  # decorated or $-label name -> address
    names: Dict[str, str] = field(default_factory=dict)  # decorated or $-label name -> target name
    sizes: Dict[str, int] = field(default_factory=dict)  # functions: code size
    tables: Dict[str, int] = field(default_factory=dict)  # functions: size of the switch tables after the code

    def addr(self, name: str) -> int:
        return self.addresses[name]


def compile_reference(project: Project, source: str, workdir: Path, name: str = "reference") -> Path:
    workdir.mkdir(parents=True, exist_ok=True)
    src = workdir / f"{name}.cpp"
    src.write_text(source, encoding="utf-8")
    out = workdir / f"{name}.obj"
    ok, log = project.compile(src, out, project.configure.CFLAGS)
    if not ok:
        raise RuntimeError(f"reference did not compile:\n{log}")
    return out


def function_layout(obj: coff.Coff, fn: coff.Symbol):
    """(code length, length with tables) of a compiled function, as verify.py sees it."""
    sec = obj.section(fn.section)
    end = min([s.value for s in obj.symbols if s.section == fn.section and s.value > fn.value
               and not s.is_section and not s.name.startswith("$")] + [len(sec.data)])
    labels = {s.index: s for s in obj.symbols if s.section == fn.section and s.name.startswith("$")}
    tables = [labels[r.symbol].value for r in sec.relocations
              if r.symbol in labels and r.offset < labels[r.symbol].value]
    return min(tables + [end]) - fn.value, end - fn.value


def build(ref: Path, root: Path, named: Set[str] = frozenset(), extra_symbols: Optional[Dict[str, int]] = None,
          aliases: Optional[Dict[str, str]] = None, version: str = "PC_20040610") -> Target:
    """Lay out and split `ref` into <root>/build/<version>/obj and write <root>/config/<version>/symbols.txt.

    named: decorated names that keep their name in symbols.txt (the others become placeholders).
    extra_symbols: further functions for symbols.txt (name -> address), e.g. a known function elsewhere.
    aliases: decorated name -> the name symbols.txt uses instead, e.g. `Foo::Get` as Ghidra would write it.
    """
    obj = coff.Coff.load(ref)
    t = Target()
    text = TEXT
    ext_fn, ext_data = EXTERN_FN, EXTERN_DATA
    cursor = {"xdata": XDATA, "rdata": RDATA, "data": DATA, "textx": TEXT_X}
    section_base: Dict[int, int] = {}
    for sym in obj.symbols:
        if sym.is_section or sym.section < 0 or sym.name.startswith("@"):
            continue
        if not sym.defined:
            if sym.name in ("__except_list", "__tls_array", "__fltused"):
                continue
            if sym.is_function:
                t.addresses[sym.name] = ext_fn
                ext_fn += 0x40
            else:
                t.addresses[sym.name] = ext_data
                ext_data += 0x10
            continue
        sec = obj.section(sym.section)
        if sec.name == ".text" and not sym.name.startswith("$"):
            code, total = function_layout(obj, sym)
            t.addresses[sym.name], t.sizes[sym.name], t.tables[sym.name] = text, code, total - code
            text = align(text + total + 1)
            continue
        if sec.name == ".text":
            continue  # a label inside a function: folded below
        # Other sections keep their internal layout: each is placed whole.
        kind = "textx" if sec.is_code else "xdata" if sec.name.startswith(".xdata") else \
            "data" if sec.writable else "rdata"
        if sym.section not in section_base:
            section_base[sym.section] = cursor[kind]
            cursor[kind] = align(cursor[kind] + len(sec.data), 4 if kind == "textx" else 16)
        t.addresses[sym.name] = section_base[sym.section] + sym.value

    for name, address in t.addresses.items():
        if name in (aliases or {}):
            t.names[name] = aliases[name]
        elif name in named:
            t.names[name] = name
        elif name.startswith("$L") and TEXT_X <= address < RDATA:
            t.names[name] = f"Unwind@{address:08x}"
        elif TEXT <= address < RDATA:
            t.names[name] = f"FUN_{address:08x}"
        else:
            t.names[name] = f"DAT_{address:08x}"

    # Fold $ labels of each function into function+offset, as delink references switch tables.
    retarget, patch, labels = {}, {}, []
    for fn in obj.symbols:
        if fn.name not in t.sizes:
            continue
        sec = obj.section(fn.section)
        local = {s.index: s for s in obj.symbols if s.section == fn.section and s.name.startswith("$")}
        labels += [s.name for s in local.values()]
        for i, r in enumerate(sec.relocations):
            if r.symbol in local:
                retarget[(sec.index, i)] = fn.index
                patch[(sec.index, r.offset)] = struct.pack("<i", obj.addend(sec.index, r) + local[r.symbol].value
                                                           - fn.value)
    drop = [(sec.index, i) for sec in obj.sections for i, r in enumerate(sec.relocations)
            if obj.slots[r.symbol].name == "__except_list"]
    # A function's calls to itself: delink resolves them in the unit, so the split holds the displacement
    # and no relocation.
    for fn in obj.symbols:
        if fn.name not in t.sizes:
            continue
        sec = obj.section(fn.section)
        for i, r in enumerate(sec.relocations):
            if (r.type == coff.IMAGE_REL_I386_REL32 and obj.slots[r.symbol] is fn
                    and fn.value <= r.offset < fn.value + t.sizes[fn.name]):
                drop.append((sec.index, i))
                patch[(sec.index, r.offset)] = struct.pack("<i", obj.addend(sec.index, r) + fn.value - r.offset - 4)
    rename = dict(t.names)
    data_names = [s.name for s in obj.symbols if s.defined and not s.is_section and not obj.section(s.section).is_code]
    objdir = root / "build" / version / "obj"
    (objdir / "auto").mkdir(parents=True, exist_ok=True)
    code_obj = obj.rewrite(rename=rename, undefine=labels + data_names, retarget=retarget, patch=patch, drop=drop)
    shared = obj.rewrite(rename=rename, undefine=labels, retarget=retarget, patch=patch, drop=drop)
    for unit in (TEXT, TEXT_X):
        (objdir / "auto" / f"text_{unit:08X}.obj").write_bytes(code_obj)
    (objdir / "__shared_data.obj").write_bytes(shared)

    lines = ["# synthetic symbols for the tools/agent tests"]
    for name, address in sorted(t.addresses.items(), key=lambda kv: kv[1]):
        target = t.names[name]
        if name in t.sizes:
            lines.append(f"{target} = .text:0x{address:08X}; // type:function size:0x{t.sizes[name]:X}")
            if t.tables[name]:
                table = address + t.sizes[name]
                lines.append(f"switchdataD_{table:08x} = .text:0x{table:08X}; // type:object "
                             f"size:0x{t.tables[name]:X}")
        elif TEXT_X <= address < RDATA:
            sym = obj.symbol(name)
            start, end = obj.extent(sym)
            lines.append(f"{target} = .text:0x{address:08X}; // type:function size:0x{end - start:X}")
        elif EXTERN_FN <= address < TEXT_X:
            lines.append(f"{target} = .text:0x{address:08X}; // type:function size:0x10")
        elif name in named or name in (aliases or {}) or EXTERN_DATA <= address < DATA:
            lines.append(f"{target} = .data:0x{address:08X}; // type:object size:0x4")
    for name, address in (extra_symbols or {}).items():
        lines.append(f"{name} = .text:0x{address:08X}; // type:function size:0x10")
    config = root / "config" / version
    config.mkdir(parents=True, exist_ok=True)
    (config / "symbols.txt").write_text("\n".join(lines) + "\n", encoding="utf-8")
    if not (config / "splits.txt").exists():
        (config / "splits.txt").write_text("# synthetic splits\n", encoding="utf-8")
    return t


def environment(root: Path, version: str = "PC_20040610") -> Dict[str, str]:
    """T3_AGENT_* variables pointing the tools at a fixture project."""
    env = dict(os.environ)
    env.update({
        "T3_AGENT_MAIN": str(root),
        "T3_AGENT_CONFIG": str(root / "config" / version),
        "T3_AGENT_OBJ": str(root / "build" / version / "obj"),
        "T3_AGENT_STATE": str(root / "build" / "agent"),
        "T3_AGENT_SRC": str(root / "src"),
        "T3_AGENT_EXE": "",
    })
    return env
