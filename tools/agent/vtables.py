#!/usr/bin/env python3
"""Lead only: name the slots of each native class's vtable after the class that introduces them.

    python tools/agent/vtables.py spec <plan.json> [--dry-run]
    python tools/agent/fixnames.py spec <plan.json>
    python configure.py && ninja
    python tools/agent/fixnames.py spec-accept <plan.json>

Workers declare Unreal classes on Core.h's UObject, whose virtual functions are named by slot
(Unknown00, Unknown04, ~UObject in slot 2, ..., CallFunction in 17, Register in 19). A function
that stores a vtable has every slot its classes declare compared with the exe's, so each slot's
function must carry the name the class that overrides it there declares. classes.txt gives each
native class its super and its vtable: a slot whose function is not the super's at that slot is
the class's own, and gets the name the class would declare (`?Unknown18@AAIPathPoint@@UAEXXZ`;
`??_GAFormationPoint@@UAEPAXI@Z` for its deleting destructor in slot 2, and
`??1AFormationPoint@@UAE@XZ` for the destructor that one calls first). A class whose recorded
vtable is its super's (several classes share UObject's InternalConstructor, which gave
classes.txt UObject's table for them) takes the slots its subclasses all agree on; a slot no
table settles is left alone, except the deleting destructor: a class's own table holds its own,
unless the linker folded it with an ancestor's.

A function known only by a placeholder (FUN_, a caller's guessed signature, a Virtual<N> or
Unknown<off> of another class) is renamed and keeps the old name as an alias; a function with a
real name, or library code ICF folded into a slot, keeps it, and the slot names become its
aliases. A function several slots or classes
share (ICF folded identical ones) takes the first class's name and the others as aliases. The
plan retries every function deferred for a name conflict.
"""
import argparse
import json
import re
import struct
import sys
from collections import defaultdict
from pathlib import Path
from typing import Dict, List, Optional, Tuple

HERE = Path(__file__).resolve().parent
sys.path.insert(0, str(HERE))

from common import Project, fmt_addr, is_placeholder, read_json  # noqa: E402

SLOTS = 20  # the virtual functions Core.h declares for UObject


def slot_name(cls: str, slot: int) -> str:
    """The decorated name of a class's override of UObject's virtual in `slot`, as Core.h declares it."""
    if slot == 2:
        return f"??_G{cls}@@UAEPAXI@Z"  # the scalar deleting destructor, ~UObject's slot
    if slot == 17:
        return f"?CallFunction@{cls}@@UAEXAAVFFrame@@QAXPAVUFunction@@@Z"
    if slot == 19:
        return f"?Register@{cls}@@UAEXXZ"
    return f"?Unknown{4 * slot:02X}@{cls}@@UAEXXZ"


def effective_tables(supers: Dict[str, str], tables: Dict[str, Optional[List[int]]]) -> Dict[str, List[Optional[int]]]:
    """Each class's slots: its own table, else (None: not known) the slots all its subclasses agree on."""
    children: Dict[str, List[str]] = defaultdict(list)
    for c, s in supers.items():
        children[s].append(c)
    out: Dict[str, List[Optional[int]]] = {}

    def table(c: str) -> List[Optional[int]]:
        if c in out:
            return out[c]
        own = tables.get(c)
        if own is not None:
            out[c] = list(own)
            return out[c]
        kids = [table(k) for k in children.get(c, [])]
        kids = [k for k in kids if k]
        width = min((len(k) for k in kids), default=0)
        out[c] = [k0 if all(k[i] == (k0 := kids[0][i]) for k in kids) else None for i in range(width)]
        return out[c]

    for c in supers:
        table(c)
    return out


def attribute(supers: Dict[str, str], tables: Dict[str, Optional[List[int]]],
              slots: int = SLOTS) -> List[Tuple[int, str, int]]:
    """[(function, class, slot)] for each slot function a class introduces, base classes first: the
    root's every slot, then each slot where a class's table differs from its super's (both known)."""
    eff = effective_tables(supers, tables)
    depth: Dict[str, int] = {}

    def level(c: str) -> int:
        if c not in depth:
            depth[c] = 0 if not supers.get(c) else level(supers[c]) + 1
        return depth[c]

    def ancestors_slot(c: str, k: int) -> set:
        out, s = set(), supers.get(c)
        while s:
            t = eff.get(s, [])
            if k < len(t) and t[k] is not None:
                out.add(t[k])
            s = supers.get(s)
        return out

    out = []
    for c in sorted(supers, key=lambda c: (level(c), c)):
        mine, base = eff.get(c, []), eff.get(supers.get(c, ""), None) if supers.get(c) else None
        for k in range(min(slots, len(mine))):
            f = mine[k]
            if f is None:
                continue
            # A class's own table holds its own deleting destructor (slot 2) even where its super's is not
            # known, unless the linker folded it with an ancestor's.
            own_dtor = k == 2 and tables.get(c) is not None and f not in ancestors_slot(c, k)
            if base is not None:
                if (k >= len(base) or base[k] is None or base[k] == f) and not own_dtor:
                    continue  # inherited, or the super's slot is not known
            elif supers.get(c) and not own_dtor:
                continue  # the super's table is not known at all
            out.append((f, c, k))
    return out


def read_table(pe_image, vtable: int, slots: int, code: Tuple[int, int]) -> List[int]:
    """The function pointers at the start of a vtable, up to `slots` or the first that is not code."""
    out = []
    for k in range(slots):
        try:
            f = struct.unpack("<I", pe_image.read_rva(vtable + 4 * k - pe_image.image_base, 4))[0]
        except (ValueError, struct.error):
            break
        if not code[0] <= f < code[1]:
            break
        out.append(f)
    return out


SLOT_PLACEHOLDER = re.compile(r"^\?(?:Virtual\d+|Unknown[0-9A-F]{2})@")


# A member of a class known only by an address (`??1Class_10E56A28@@QAE@XZ`).
PLACEHOLDER_CLASS = re.compile(r"(?:^\?\?[0-9A-Z_]{1,2}|@)(?:Class|Struct)_[0-9A-Fa-f]{8}@@")


def placeholder_name(name: str) -> bool:
    """A name that says nothing about the function: FUN_, a guessed signature on one, a slot name, or a
    member of a class known only by an address."""
    return is_placeholder(name) or bool(re.match(r"\?\??(?:FUN|DAT)_[0-9A-Fa-f]{8}@", name)) \
        or bool(SLOT_PLACEHOLDER.match(name)) or bool(PLACEHOLDER_CLASS.search(name))


def destructor_called(pe_image, deleting: int) -> Optional[int]:
    """The destructor a scalar deleting destructor calls first, unless it inlined it (a vtable stored
    before the call): `push esi; mov esi, ecx; call ~C; test [esp+8], 1; ...`."""
    from iced_x86 import Decoder, Mnemonic, OpKind
    try:
        data = pe_image.read_rva(deleting - pe_image.image_base, 0x40)
    except ValueError:
        return None
    for ins in Decoder(32, data, ip=deleting):
        if ins.mnemonic == Mnemonic.CALL:
            return ins.near_branch32 if ins.op0_kind == OpKind.NEAR_BRANCH32 else None
        if ins.mnemonic == Mnemonic.MOV and ins.op_count == 2 and ins.op1_kind == OpKind.IMMEDIATE32:
            return None  # a vtable stored: the destructor's body is inlined here
        if ins.mnemonic in (Mnemonic.RET, Mnemonic.JMP):
            return None
    return None


def introductions(p: Project) -> List[Tuple[int, str, int]]:
    """[(function, class, slot)]: attribute() over classes.txt and the exe's tables."""
    import pe
    classes = p.classes()
    pe_image = pe.PE(p.exe.read_bytes())
    text = next(s for s in pe_image.sections if s.name == ".text")
    code = (pe_image.image_base + text.va, pe_image.image_base + text.va + text.vsize)
    supers = {n: (c.super if c.super in classes else "") for n, c in classes.items()}
    tables: Dict[str, Optional[List[int]]] = {}
    for n, c in classes.items():
        s = classes.get(c.super)
        # A table recorded for a class and its super alike is the super's: this class's is not known.
        tables[n] = None if not c.vtable or (s is not None and s.vtable == c.vtable) else \
            read_table(pe_image, c.vtable, SLOTS, code)
    return attribute(supers, tables)


def declarations(p: Project) -> Dict[str, List[str]]:
    """{class: the virtual functions it overrides, declared as Core.h declares UObject's}, for the
    generated class headers (tools/assets/t3classes.py): a source that includes them gets each vtable's
    slots under the names symbols.txt gives them."""
    out: Dict[str, List[str]] = defaultdict(list)
    for f, c, k in sorted(introductions(p), key=lambda x: (x[1], x[2])):
        if k == 2:
            decl = f"virtual ~{c}();"
        elif k == 17:
            decl = "virtual void CallFunction(FFrame& Stack, RESULT_DECL, UFunction* Function);"
        elif k == 19:
            decl = "virtual void Register();"
        else:
            decl = f"virtual void Unknown{4 * k:02X}();"
        out[c].append(f"{decl:<40}// slot {k}: 0x{f:08X}")
    return out


def plan(p: Project) -> Tuple[dict, List[str]]:
    import pe
    pe_image = pe.PE(p.exe.read_bytes())
    wanted: Dict[int, List[str]] = defaultdict(list)
    for f, c, k in introductions(p):
        names = [slot_name(c, k)]
        if k == 2:  # and the destructor its deleting destructor calls
            d = destructor_called(pe_image, f)
            if d is not None:
                names.append((d, f"??1{c}@@UAE@XZ"))
        for name in names:
            at, name = (f, name) if isinstance(name, str) else name
            if name not in wanted[at]:
                wanted[at].append(name)
    taken = {s.name: s.address for s in p.symbols}
    renames, aliases, notes = {}, defaultdict(list), []
    for f, names in sorted(wanted.items()):
        sym = p.by_addr.get(f)
        if sym is None or sym.address != f or not sym.is_function:
            notes.append(f"{fmt_addr(f)} is not a function in symbols.txt: {names[0]} not given")
            continue
        free = [n for n in names if taken.get(n, f) == f and n != sym.name]
        clash = [n for n in names if taken.get(n, f) != f]
        notes += [f"{n} is already at {fmt_addr(taken[n])}; not given to {fmt_addr(f)}" for n in clash]
        new = [n for n in free if n not in taken]
        if not new:
            continue
        key = fmt_addr(f)
        # A destructor a caller declared non-virtual (`??1C@@QAE@XZ`) takes its virtual name.
        nonvirtual = sym.name.startswith("??1") and sym.name.replace("@@QAE@XZ", "@@UAE@XZ") in new
        # A library function in a slot (ICF folded an empty one with the CRT's) keeps its name.
        if (placeholder_name(sym.name) or nonvirtual) and p.category(f) != "libs":
            renames[key] = new[0]
            if not is_placeholder(sym.name):
                aliases[key].append(sym.name)
            aliases[key] += new[1:]
        else:
            aliases[key] += new
    blocked = set()
    for rec_path in (p.state / "deferred").glob("*.json"):
        rec = read_json(rec_path, {}) or {}
        if "name" in (rec.get("blocker") or "").lower() and rec.get("addr"):
            blocked.add(rec["addr"])
    blocked |= {a for a, why in (read_json(p.state / "excluded.json", {}) or {}).items()
                if why.lower().startswith("name conflict")}
    spec = {"renames": renames, "aliases": {k: v for k, v in aliases.items() if v}, "patches": [],
            "candidates": {}, "blocked": sorted(blocked)}
    return spec, notes


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = parser.add_subparsers(dest="cmd", required=True)
    s = sub.add_parser("spec", help="write a fixnames.py spec that names the slots")
    s.add_argument("out")
    s.add_argument("--dry-run", action="store_true", help="print the counts, write nothing")
    args = parser.parse_args()
    p = Project()
    spec, notes = plan(p)
    print(f"{len(spec['renames'])} renames, {sum(map(len, spec['aliases'].values()))} aliases, "
          f"{len(spec['blocked'])} name-blocked functions to retry; {len(notes)} names not given")
    for n in notes[:20]:
        print("  " + n)
    if not args.dry_run:
        Path(args.out).write_text(json.dumps(spec, indent=1) + "\n", encoding="utf-8")
        print(f"wrote {args.out}: next fixnames.py spec, configure.py && ninja, fixnames.py spec-accept")


if __name__ == "__main__":
    main()
