#!/usr/bin/env python3
"""Lead only: match native classes' registration functions from Core.h's DECLARE_CLASS.

    python tools/agent/classreg.py write [class ...]          # sources to build/scratch/<ADDR>/lead-reg.cpp
    python tools/agent/classreg.py check [class ...] [--spec FILE]   # the gate on each; name conflicts as a spec
    python tools/agent/classreg.py accept [class ...]         # accept.py on each source that matches

Every native class registers lazily (docs/engine.md, "Native class
registration"): StaticClass(), inlined at each use, calls the class's
GetPrivateStaticClass<Class> and InitializePrivateStaticClass<Class>. Both
are the same code for every class but for its constants, so they are
written here from classes.txt rather than by workers:

  - the getter creates the UClass object, through Ion Storm's placement
    `operator new` and inside a scope of their memory manager;
  - the initializer links it to its super and within classes, gives it
    its class and registers its natives.

The class declarations come from the generated headers
(include/<Package>/<Package>Classes.h, tools/assets/t3classes.py), whose
DECLARE_CLASS lines declare the static members. Only Ion Storm's classes
(classes.txt category game) are written; Epic's are named, not matched.
`check` prints, as a fixnames.py spec, the names to give the addresses a
candidate calls under another name (an earlier caller's guess): apply it with
`fixnames.py spec`, re-split, then `accept`.
"""

import argparse
import json
import os
import re
import subprocess
import sys
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path
from typing import Dict, List, Optional

from common import Project, addr_key, emit, fmt_addr
from verify import Verifier

HERE = Path(__file__).resolve().parent
AGENT = "lead"

GETTER = """#include "{package}/{package}Classes.h"

// Ion Storm's memory manager (0x10905AA0): the registration allocates inside a
// scope of it (slots 8 and 9).
class Class_10905A90_Member
{{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5();
    virtual void Virtual6();
    virtual void Virtual7();
    virtual void Virtual8(int A, int B);
    virtual void Virtual9();
}};

Class_10905A90_Member* FUN_10905aa0();

// Ion Storm's placement new and its delete (0x10905C10; the delete folded into ::operator delete).
void* operator new(unsigned int Size, const int& Tag, int A, int B, int C, int D);
void operator delete(void* Ptr, const int& Tag, int A, int B, int C, int D);

// FUNCTION: 0x{addr:08X}
UClass* {cls}::GetPrivateStaticClass{cls}(const TCHAR* Package)
{{
    FUN_10905aa0()->Virtual8(0, 0);
    UClass* ReturnClass = new(0, 0, 0, 0, 0) UClass(EC_StaticConstructor, sizeof({cls}), StaticClassFlags,
                                                    FGuid(0, 0, 0, 0), &TEXT("{cls}")[1], Package,
                                                    StaticConfigName(),
                                                    RF_Public | RF_Standalone | RF_Transient | RF_Native,
                                                    InternalConstructor,
                                                    (void (UObject::*)())&{cls}::StaticConstructor);
    FUN_10905aa0()->Virtual9();
    return ReturnClass;
}}
"""

INIT = """#include "{package}/{package}Classes.h"

// FUNCTION: 0x{addr:08X}
void {cls}::InitializePrivateStaticClass{cls}()
{{
    if (Super::StaticClass() != PrivateStaticClass)
        PrivateStaticClass->SuperField = Super::StaticClass();
    else
        PrivateStaticClass->SuperField = NULL;
    PrivateStaticClass->ClassWithin = WithinClass::StaticClass();
    PrivateStaticClass->SetClass(UClass::StaticClass());
    if (GetInitialized() && PrivateStaticClass->GetClass() == PrivateStaticClass->StaticClass())
        PrivateStaticClass->Register();
}}
"""


def plan(p: Project, names: List[str]) -> List[dict]:
    """[{"class", "kind", "addr", "path"}] for the game classes' getters and initializers."""
    classes = p.classes()
    out = []
    for name, c in sorted(classes.items()):
        if c.category != "game" or (names and name not in names):
            continue
        for kind, addr, template in (("getter", c.getter, GETTER), ("init", c.init, INIT)):
            if not addr:
                continue
            if addr not in p.by_addr or not p.by_addr[addr].is_function:
                print(f"skipped {name} {kind} {fmt_addr(addr)}: not a function in symbols.txt (the split cuts it)")
                continue
            path = p.main / "build" / "scratch" / f"0x{addr:08X}" / "lead-reg.cpp"
            out.append({"class": name, "kind": kind, "addr": addr, "path": path,
                        "source": template.format(package=c.package, cls=name, addr=addr)})
    return out


def check(p: Project, items: List[dict]) -> List[dict]:
    verifier = Verifier(p)

    def one(item: dict) -> dict:
        res = verifier.run(item["addr"], item["path"], p.state / "tmp" / f"classreg-{addr_key(item['addr'])}")
        uses = sorted({n for r in res.rows for n in r.notes
                       if "the candidate uses" in n or "the target is named" in n})
        return dict(item, build_ok=res.build_ok, match=res.match and not res.problems,
                    rows=res.mismatch_rows, total=len(res.rows), score=res.score, uses=uses,
                    problems=res.problems[:2], log=(res.build_log or "")[-400:] if not res.build_ok else "")

    with ThreadPoolExecutor(max_workers=os.cpu_count() or 1) as pool:
        return list(pool.map(one, items))


USES = re.compile(r"the candidate uses (\S+); the target uses (0x[0-9A-F]{8}) \((\S+)\)")
NAMED = re.compile(r"the target is named (\S+); the candidate defines (\S+)")


def spec_of(p: Project, results: List[dict]) -> dict:
    """renames and aliases a fixnames.py spec gives, from the name rows: the candidate's name becomes the
    address's own, the old one an alias (a caller in src/ may use it)."""
    wanted: Dict[int, set] = {}
    for r in results:
        for note in r["uses"]:
            m = USES.search(note)
            if m:
                wanted.setdefault(int(m.group(2), 16), set()).add(m.group(1))
            m = NAMED.search(note)
            if m:
                wanted.setdefault(r["addr"], set()).add(m.group(2))
    renames, aliases, conflicts = {}, {}, {}
    for addr, names in sorted(wanted.items()):
        if len(names) > 1:
            conflicts[fmt_addr(addr)] = sorted(names)
            continue
        new = next(iter(names))
        old = p.by_addr.get(addr)
        renames[fmt_addr(addr)] = new
        if old is not None and old.name != new and not re.fullmatch(r"(FUN|DAT)_[0-9a-f]{8}", old.name):
            aliases[fmt_addr(addr)] = [old.name]
    return {"renames": renames, "aliases": aliases, "patches": [], "candidates": {},
            "blocked": [], "conflicts": conflicts}


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("cmd", choices=["write", "check", "accept"])
    parser.add_argument("classes", nargs="*")
    parser.add_argument("--spec", type=Path, help="check: write the name conflicts as a fixnames.py spec here")
    args = parser.parse_args()
    if os.environ.get("T3_AGENT_ID") not in (None, "", AGENT):
        sys.exit("classreg.py is the lead's")
    p = Project()
    items = plan(p, args.classes)
    for item in items:
        item["path"].parent.mkdir(parents=True, exist_ok=True)
        item["path"].write_text(item["source"], encoding="utf-8", newline="\n")
    if args.cmd == "write":
        print(f"wrote {len(items)} sources")
        return
    if args.cmd == "check":
        results = check(p, items)
        for r in results:
            r.pop("source"), r.pop("path")
        ok = [r for r in results if r["match"]]
        names_only = [r for r in results if not r["match"] and r["build_ok"] and r["uses"]
                      and r["rows"] <= len(r["uses"])]
        print(f"{len(ok)} match, {len(names_only)} differ only in names, "
              f"{sum(1 for r in results if not r['build_ok'])} do not compile, of {len(results)}")
        for r in results:
            if not r["match"] and r not in names_only:
                print(f"  {r['class']} {r['kind']} {fmt_addr(r['addr'])}: "
                      + (f"{r['rows']}/{r['total']} rows" if r["build_ok"] else "build failed: " + r["log"][-200:]))
        spec = spec_of(p, results)
        print(f"names: {len(spec['renames'])} renames, {len(spec['aliases'])} with an old name kept as an alias, "
              f"{len(spec['conflicts'])} addresses wanted under two names")
        for a, names in spec["conflicts"].items():
            print(f"  conflict {a}: {names}")
        if args.spec:
            args.spec.write_text(json.dumps(spec, indent=1), encoding="utf-8")
            print(f"wrote {args.spec}")
        return
    env = dict(os.environ, T3_AGENT_ID=AGENT)

    def accept(item: dict) -> str:
        rel = os.path.relpath(item["path"], p.main)
        proc = subprocess.run([sys.executable, str(HERE / "accept.py"), fmt_addr(item["addr"]), rel], cwd=p.main,
                              env=env, capture_output=True, text=True)
        return (proc.stdout or proc.stderr).strip().splitlines()[0] if (proc.stdout or proc.stderr).strip() else "?"

    done = [i for i in items if i["addr"] not in p.accepted() and i["addr"] not in p.integrated()]
    with ThreadPoolExecutor(max_workers=os.cpu_count() or 1) as pool:
        lines = list(pool.map(accept, done))
    accepted = sum(1 for line in lines if line.startswith("ACCEPTED"))
    for item, line in zip(done, lines):
        if not line.startswith("ACCEPTED"):
            print(f"  {item['class']} {item['kind']}: {line[:150]}")
    print(f"{accepted} of {len(done)} accepted")


if __name__ == "__main__":
    main()
