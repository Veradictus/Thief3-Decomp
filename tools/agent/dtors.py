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

    python tools/agent/dtors.py native [--dry-run]
    python configure.py && ninja
    python tools/agent/integrate.py

A native class (classes.txt, the generated include/<Package>/<Package>Classes.h) has DECLARE_CLASS's
destructor, `C::~C() { ConditionalDestroy(); }`, and a deleting destructor at slot 2 that calls it, then
UObject::operator delete(this, sizeof(C)) (Core.h). `native` accepts each of Ion Storm's: the destructor
in the header form (as matched, or accepted anew; a worker's placeholder-chain form is re-accepted when it
is not in src/ or is alone in its unit, which is removed with its splits.txt block for the integration to
write anew), then the deleting destructor as compiler-generated with it.
"""

import argparse
import json
import os
import re
import subprocess
import sys
from collections import Counter, defaultdict
from pathlib import Path
from typing import Dict, List

from common import Project, addr_key, fmt_addr, is_placeholder

HERE = Path(__file__).resolve().parent

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
        old = p.by_addr[x].name
        if old != gname:
            spec["renames"][fmt_addr(x)] = gname
        # one deleting destructor the linker folded for several classes; and the slot's old name (Virtual0),
        # which sources in src/ still declare
        others = sorted({f"??_G{c}@@UAEPAXI@Z" for _, c in pairs[1:]} - {gname})
        if old != gname and not is_placeholder(old) and old not in others:
            others.append(old)
        if others:
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


# A native class's destructor as workers wrote it before the generated headers declared the class: one
# call, to ConditionalDestroy (or its placeholder name), in a placeholder chain of classes.
STOCK_BODY = re.compile(r"(\w+)::~\1\(\)\s*\{\s*(?:FUN_10ad5310|ConditionalDestroy)\(\);\s*\}")


def accept(p: Project, *args: str) -> str:
    proc = subprocess.run([sys.executable, str(HERE / "accept.py"), *args], cwd=p.root,
                          env=dict(os.environ, T3_AGENT_ID="lead"), capture_output=True, text=True)
    lines = (proc.stdout + proc.stderr).strip().splitlines()
    return lines[-1] if lines else str(proc.returncode)


def drop_unit(p: Project, unit: str) -> None:
    """Remove a src/ unit and its splits.txt block."""
    (p.src_dir / unit).unlink()
    text = p.splits_txt.read_text(encoding="utf-8")
    m = re.search(r"(?ms)^%s:\n.*?(?:\n\n|\Z)" % re.escape(unit), text)
    if m:
        p.splits_txt.write_text(text[:m.start()] + text[m.end():], encoding="utf-8", newline="\n")


def native(p: Project, dry_run: bool = False) -> Dict[str, List[str]]:
    """{outcome: [class]} for each of Ion Storm's native classes whose deleting destructor is not accepted."""
    accepted, integrated = p.accepted(), p.integrated()
    alone = Counter(integrated.values())
    work = p.state_dir("tmp", "dtors")
    out: Dict[str, List[str]] = defaultdict(list)
    for cls, c in sorted(p.classes().items()):
        g, d = p.address_of(f"??_G{cls}@@UAEPAXI@Z"), p.address_of(f"??1{cls}@@UAE@XZ")
        if g is None or g in accepted or c.category != "game":
            continue
        if d is None:
            out["no destructor named (vtables.py)"].append(cls)
            continue
        include = f'#include "{c.package}/{c.package}Classes.h"'
        source = f"{include}\n\n// FUNCTION: {fmt_addr(d)}\n{cls}::~{cls}()\n{{\n    ConditionalDestroy();\n}}\n"
        unit, replace = integrated.get(d), d in accepted
        if replace:
            old = (p.state / "accepted" / f"{addr_key(d)}.cpp").read_text(encoding="utf-8")
            if include in old:
                source, replace = old, None
            elif not STOCK_BODY.search(old) or (unit is not None and alone[unit] != 1):
                out["destructor not in the stock form, or not alone in its unit"].append(cls)
                continue
        if dry_run:
            out["planned"].append(cls)
            continue
        if replace is not None:  # the destructor in the header form first
            path = work / f"{addr_key(d)}.cpp"
            path.write_text(source, encoding="utf-8")
            verdict = accept(p, fmt_addr(d), str(path), "--symbol", f"??1{cls}@@UAE@XZ",
                             *(["--replace"] if replace else []))
            if not verdict.startswith("ACCEPTED"):
                out["destructor does not match in the header form"].append(f"{cls}: {verdict[:100]}")
                continue
            if unit is not None:
                drop_unit(p, unit)  # its placeholder form: the integration writes it anew
                out["units removed"].append(unit)
        path = work / f"{addr_key(g)}.cpp"
        path.write_text(source.replace(f"// FUNCTION: {fmt_addr(d)}", f"// FUNCTION: {fmt_addr(g)}"),
                        encoding="utf-8")
        verdict = accept(p, fmt_addr(g), str(path), "--symbol", f"??_G{cls}@@UAEPAXI@Z", "--with", fmt_addr(d))
        out["accepted" if verdict.startswith("ACCEPTED") else "deleting destructor rejected"].append(
            cls if verdict.startswith("ACCEPTED") else f"{cls}: {verdict[:100]}")
    return out


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("mode", nargs="?", choices=("plan", "native"), default="plan")
    parser.add_argument("-o", "--output", type=Path, help="the plan (default: build/agent/dtors-plan.json)")
    parser.add_argument("--dry-run", action="store_true", help="native: list what would be accepted")
    args = parser.parse_args()
    p = Project()
    if args.mode == "native":
        for outcome, items in native(p, args.dry_run).items():
            print(f"{outcome}: {len(items)}")
            for item in items[:20]:
                print(f"  {item}")
        if not args.dry_run:
            print("Next: python configure.py && ninja, then integrate.py")
        return
    out = args.output or p.state / "dtors-plan.json"
    spec = plan(p)
    out.write_text(json.dumps(spec, indent=1), encoding="utf-8")
    print(f"{len(spec['blocked'])} deleting destructors planned, {len(spec['skipped'])} left out; wrote {out}")
    for s in spec["skipped"]:
        print(f"  {s['addr']}: {s['why']}")


if __name__ == "__main__":
    main()
