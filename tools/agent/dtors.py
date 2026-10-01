#!/usr/bin/env python3
"""Lead only: plan the matches of the scalar deleting destructors whose class's vtable src/ already emits.

    python tools/agent/dtors.py [-o build/agent/dtors-plan.json]
    python tools/agent/fixnames.py spec build/agent/dtors-plan.json
    python configure.py && ninja
    python tools/agent/fixnames.py spec-accept build/agent/dtors-plan.json
    python tools/agent/integrate.py <the planned addresses>

A class with a virtual destructor has a scalar deleting destructor (`??_GC@@UAEPAXI@Z`) at slot 0 of its
vtable: it calls the destructor, then `operator delete` when bit 0 of its argument is set. MSVC writes it
wherever it emits the vtable, so it matches from the class's declaration, never from a hand-written body
(the queue excludes them). For each vtable an integrated function stores (a `??_7C@@6B@` binding) whose
slot 0 holds one, the plan:

  - gives the class, and its bases declared in the same file, `virtual ~C();` in place of the slot-0
    placeholder (`Virtual0()`), in the emitting function's accepted source and its src/ unit;
  - names the deleting destructor `??_GC@@UAEPAXI@Z` in symbols.txt, with the names of the other classes
    the linker folded it for as aliases, and the destructor it calls `??1C@@UAE@XZ` (an alias when
    something already names that address);
  - writes the candidate: the emitting function's patched source, its marker moved to the deleting
    destructor, accepted as compiler-generated with that function (accept.py --with).

Deleting destructors whose destructor is inlined (no call) need the destructor's definition in the same
unit, and classes with several bases need their secondary vtables: both are reported and left out.
"""

import argparse
import json
import re
import sys
from pathlib import Path

from common import Project, fmt_addr, is_placeholder

VTABLE = re.compile(r"\?\?_7(\w+)@@6B@")


def block(text: str, cls: str):
    m = re.search(r"(?ms)^class %s\b[^;{]*\{.*?^\};" % re.escape(cls), text)
    return m.group(0) if m else None


def bases(text: str, cls: str) -> list:
    """cls and the classes it derives from, as far as the file declares them."""
    out = [cls]
    while True:
        m = re.search(r"(?m)^class %s\s*:\s*public\s+(\w+)" % re.escape(out[-1]), text)
        if not m or m.group(1) in out or block(text, m.group(1)) is None:
            return out
        out.append(m.group(1))


def patch(text: str, chain: list, x: int):
    """[(old block, new block)] giving each class of the chain a virtual destructor at slot 0 (the class itself
    gets one declared when it only inherits slot 0); None when no slot-0 declaration is found."""
    out, missing = [], []
    for cls in chain:
        b = block(text, cls)
        for slot0 in ("    virtual void Virtual0();\n", f"    virtual void FUN_{x:08x}();\n"):
            if slot0 in b:
                out.append((b, b.replace(slot0, f"    virtual ~{cls}();\n", 1)))
                break
        else:
            missing.append(cls)
    if not out:
        return None
    if chain[0] in missing:
        b = block(text, chain[0])
        if "public:\n" not in b:
            return None
        out.append((b, b.replace("public:\n", f"public:\n    virtual ~{chain[0]}();\n", 1)))
    return out


def deleting_destructor(p: Project, image, address: int):
    """The destructor a scalar deleting destructor at `address` calls, 0 when it inlines it, None when the
    function is not one."""
    from iced_x86 import Decoder, Mnemonic, OpKind

    f = p.by_addr.get(address)
    if f is None or f.address != address or not f.is_function:
        return None
    view = image.view(address, f.size)
    if view is None:
        return None
    insns = list(Decoder(32, view.data, ip=address))
    tested = any(i.mnemonic == Mnemonic.TEST and i.op0_kind == OpKind.MEMORY and i.op1_kind == OpKind.IMMEDIATE8
                 and i.immediate8 == 1 for i in insns)
    if not tested or insns[-1].mnemonic != Mnemonic.RET or insns[-1].op_count != 1 or insns[-1].immediate16 != 4:
        return None
    test_at = next(k for k, i in enumerate(insns) if i.mnemonic == Mnemonic.TEST and i.op0_kind == OpKind.MEMORY)
    calls = [i.near_branch32 for i in insns[:test_at] if i.mnemonic == Mnemonic.CALL
             and i.op0_kind == OpKind.NEAR_BRANCH32]
    return calls[0] if calls else 0


def plan(p: Project) -> dict:
    from verify import TargetImage

    image = TargetImage(p)
    accepted, integrated = p.accepted(), p.integrated()
    binders = {}
    for a, rec in accepted.items():
        for b in rec.get("bindings", []):
            binders.setdefault(int(b["addr"], 16), set()).add(a)
    emitters = {}  # slot-0 function -> [(emitter, class)]
    for a in sorted(integrated):
        rec = accepted.get(a)
        for b in (rec or {}).get("bindings", []):
            m = VTABLE.fullmatch(b["name"])
            if not m:
                continue
            view = image.view(int(b["addr"], 16), 4)
            slot0 = int.from_bytes(view.data, "little") if view else None
            if slot0 and (a, m.group(1)) not in emitters.get(slot0, []):
                emitters.setdefault(slot0, []).append((a, m.group(1)))
    spec = {"renames": {}, "aliases": {}, "patches": [], "candidates": {}, "blocked": []}
    skipped = []
    for x, pairs in sorted(emitters.items()):
        if x in accepted or p.category(x) != "game":
            continue
        dtor = deleting_destructor(p, image, x)
        if dtor is None:
            continue
        if dtor == 0:
            skipped.append((x, "inlines its destructor: it needs the destructor's definition in the unit"))
            continue
        patches = []
        for e, c in pairs:
            acc = (p.state / "accepted" / f"{e:08X}.cpp").read_text(encoding="utf-8")
            unit = (p.src_dir / integrated[e]).read_text(encoding="utf-8")
            blocks = [block(t, c) or "" for t in (acc, unit)]
            if all(f"virtual ~{c}();" in b for b in blocks):
                patches.append((e, acc, [], []))  # declared already: the unit emits the deleting destructor
                continue
            if any(f"~{c}(" in b for b in blocks):
                break  # a non-virtual destructor: making it virtual renames a matched function
            pa = patch(acc, bases(acc, c), x)
            pu = patch(unit, bases(unit, c), x) if block(unit, c) else None
            if not pa or not pu:
                break
            patches.append((e, acc, pa, pu))
        if len(patches) != len(pairs):
            skipped.append((x, "no slot-0 declaration found in an emitting function's source or unit, or the "
                               "class declares its destructor already (make it virtual by hand)"))
            continue
        cls = pairs[0][1]
        gname, dname = f"??_G{cls}@@UAEPAXI@Z", f"??1{cls}@@UAE@XZ"
        if p.by_addr[x].name != gname:
            spec["renames"][fmt_addr(x)] = gname
        others = sorted({f"??_G{c}@@UAEPAXI@Z" for _, c in pairs[1:]} - {gname})
        if others:  # one deleting destructor the linker folded for several classes
            spec["aliases"][fmt_addr(x)] = others
        current = p.by_addr[dtor].name if dtor in p.by_addr else ""
        if current and current != dname:
            if dtor in integrated or dtor in accepted or (not is_placeholder(current) and binders.get(dtor)):
                spec["aliases"].setdefault(fmt_addr(dtor), []).append(dname)
            elif not is_placeholder(current):
                spec["renames"][fmt_addr(dtor)] = dname
        for e, acc, pa, pu in patches:
            if pa:
                spec["patches"].append({"binder": fmt_addr(e), "replace": [list(t) for t in pa],
                                        "unit_replace": [list(t) for t in pu]})
        e, acc, pa, _ = patches[0]
        for old, new in pa:
            acc = acc.replace(old, new)
        spec["candidates"][fmt_addr(x)] = acc.replace(f"// FUNCTION: {fmt_addr(e)}", f"// FUNCTION: {fmt_addr(x)}")
        spec["blocked"].append(fmt_addr(x))
    spec["skipped"] = [{"addr": fmt_addr(x), "why": why} for x, why in skipped]
    return spec


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("-o", "--output", type=Path, help="the plan (default: build/agent/dtors-plan.json)")
    args = parser.parse_args()
    p = Project()
    out = args.output or p.state / "dtors-plan.json"
    spec = plan(p)
    out.write_text(json.dumps(spec, indent=1), encoding="utf-8")
    print(f"{len(spec['blocked'])} deleting destructors planned, {len(spec['skipped'])} left out; wrote {out}")
    for s in spec["skipped"]:
        print(f"  {s['addr']}: {s['why']}")


if __name__ == "__main__":
    main()
