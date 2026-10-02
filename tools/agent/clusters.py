#!/usr/bin/env python3
"""Families: functions whose code is the same once the addresses it references are masked.

    python tools/agent/clusters.py list [--min N] [--limit N]     # the largest open families
    python tools/agent/clusters.py show <addr>                    # a function's family
    python tools/agent/clusters.py stamp [addr ...] [--dry-run]   # lead: match open members from accepted ones

Two functions are in one family when their code bytes are equal after every
relocated field (the references delink recovered: calls, globals, vtables,
literals) is masked, and their relocations sit at the same offsets. Such
functions come from the same source pattern applied to other callees, globals
or classes: a getter of another global, the same wrapper around another
function, the InternalConstructor of another class.

One accepted member then matches the others without a model. `stamp` takes
an accepted member's source, rewrites the address in every placeholder name
whose reference differs (`FUN_10a52530` -> `FUN_10b11e40`, `DAT_`, `Class_`,
and the function's own name and `// FUNCTION:` line), and passes the result
through accept.py, the same gate as a worker's, under the worker id `stamp`.
A family is not stamped when a differing reference has a real name on
either side (its declaration may differ) or is a literal, when the function
is only a jump to its callee (whose signature is still a guess; matching it
would spread the guess), or when the accepted member is a method of a class
the rewrite does not rename (nothing then says the other function belongs to
it; a virtual method's class follows its vtable). Members the lead excluded
(build/agent/excluded.json: library code, compiler-generated functions) are
never stamped, whatever an accepted member looks like. Every outcome is
recorded in build/agent/cache/stamps.json; a member that failed goes back to
the workers.

The queue (next.py) serves one member of a family at a time: the others are
held while it is open, claimed or accepted and not yet stamped. A family's
first member goes first, its difficulty divided by the family's size.

Needs the split objects (the exe has no relocations), and iced-x86 to
compare vtable slots when stamping. The index is cached in
build/agent/cache/clusters.json, keyed like the difficulty cache.
"""

import argparse
import hashlib
import json
import os
import re
import subprocess
import sys
import time
from pathlib import Path
from typing import Dict, List, Optional, Tuple

import features as featurelib
from common import Claims, Project, addr_key, atomic_write, emit, fmt_addr, is_placeholder, read_json

HERE = Path(__file__).resolve().parent
STAMPER = "stamp"
TEMPLATES = 3  # accepted members tried per open member
MIN_SIZE = 6  # a jmp or a 5-byte call stub alone is only its callee's signature, which nobody knows yet
HEX = re.compile(r"(?<=_)([0-9A-Fa-f]{8})(?![0-9A-Za-z])")


def shape(p: Project, image, address: int) -> Optional[Tuple[str, List[list]]]:
    """(shape key, [[offset, target address or None, target name], ...]) of a function, or None when it
    has switch tables, cannot be read, or is a bare jump to another function."""
    code_end, region_end = p.code_extent(address)
    size = code_end - address
    if region_end != code_end or size < MIN_SIZE:
        return None
    view = image.relocated_view(address, size)
    if view is None or view.relocs is None:
        return None
    data = bytearray(view.data)
    if data[0] == 0xE9 and size <= 8:  # jmp rel32 and padding: a forwarding stub
        return None
    refs, layout = [], []
    for off in sorted(view.relocs):
        target, name, rtype = view.relocs[off]
        if off + 4 > len(data):
            return None
        data[off:off + 4] = b"\0\0\0\0"
        own = target is not None and address <= target < region_end
        layout.append(f"{off}:{rtype}:{'s%x' % (target - address) if own else 'x'}")
        refs.append([off, None if own else target, name])
    key = hashlib.sha1(bytes(data) + "|".join(layout).encode()).hexdigest()[:20]
    return key, refs


def index(p: Project) -> Dict[str, dict]:
    """{address: {"key", "refs"}} for every game function that has a shape, cached."""
    cache_path = p.state / "cache" / "clusters.json"
    key = featurelib._key(p)
    cache = read_json(cache_path, {}) or {}
    if cache.get("key") == key:
        return cache["functions"]
    from verify import TargetImage

    image = TargetImage(p)
    text_x = p.text_x_range()
    out = {}
    for f in p.functions:
        a = f.address
        if f.name.startswith("Unwind@") or text_x[0] <= a < text_x[1] or p.category(a) != "game":
            continue
        try:
            found = shape(p, image, a)
        except (OSError, ValueError, KeyError):
            found = None
        if found:
            out[addr_key(a)] = {"key": found[0], "refs": found[1]}
    atomic_write(cache_path, json.dumps({"key": key, "functions": out}))
    return out


def families(p: Project, idx: Optional[Dict[str, dict]] = None) -> Dict[str, List[int]]:
    """shape key -> member addresses, for shapes with two or more members."""
    idx = index(p) if idx is None else idx
    groups: Dict[str, List[int]] = {}
    for a, e in idx.items():
        groups.setdefault(e["key"], []).append(int(a, 16))
    return {k: sorted(v) for k, v in groups.items() if len(v) > 1}


def stamps(p: Project) -> Dict[str, dict]:
    return read_json(p.state / "cache" / "stamps.json", {}) or {}


def excluded(p: Project) -> set:
    """Addresses the lead took out of the queue (excluded.json): library code, compiler-generated functions,
    name conflicts. A family member there is not stamped: its family's shape says nothing about whose
    code it is."""
    return {int(a, 16) for a in (read_json(p.state / "excluded.json", {}) or {})}


def held(p: Project, queued: List[int]) -> Dict[int, int]:
    """{address: the member it waits for} for queued functions the queue holds back: another member of
    their family is queued before them, claimed, or accepted and not yet stamped onto them. Members a
    stamp failed for are never held."""
    try:
        idx = index(p)
    except Exception:  # no split objects yet: nothing is held
        return {}
    fams = families(p, idx)
    if not fams:
        return {}
    failed = {int(a, 16) for a, s in stamps(p).items() if not s.get("ok")}
    accepted = set(p.accepted())
    claimed = {int(c["addr"], 16) for c in Claims(p).all()}
    key_of = {int(a, 16): e["key"] for a, e in idx.items()}
    waiting_on: Dict[str, int] = {}
    for k, members in fams.items():
        done = [m for m in members if m in accepted]
        taken = [m for m in members if m in claimed]
        if done:
            waiting_on[k] = done[0]
        elif taken:
            waiting_on[k] = taken[0]
    out = {}
    for a in queued:  # in queue order: the first open member of a family is served
        k = key_of.get(a)
        if k is None or k not in fams or a in failed:
            continue
        if k in waiting_on:
            out[a] = waiting_on[k]
        else:
            waiting_on[k] = a
    return out


def open_sizes(p: Project, queued: List[int]) -> Dict[int, int]:
    """{address: how many queued members its family has} for queued family members."""
    try:
        idx = index(p)
    except Exception:
        return {}
    counts: Dict[str, int] = {}
    keys = {}
    for a in queued:
        e = idx.get(addr_key(a))
        if e:
            keys[a] = e["key"]
            counts[e["key"]] = counts.get(e["key"], 0) + 1
    return {a: counts[k] for a, k in keys.items() if counts[k] > 1}


# -- stamping ---------------------------------------------------------------------------
def rewrite(source: str, mapping: Dict[int, int]) -> str:
    """`source` with the address in every placeholder name (FUN_x, DAT_x, Class_x, ...) and in the
    FUNCTION line replaced through `mapping`. Names keep their letter case; an address of digits only
    takes the convention of its prefix (`Class_` and `Struct_` upper case, the rest lower case)."""
    def sub(m: re.Match) -> str:
        old = int(m.group(1), 16)
        if old not in mapping:
            return m.group(1)
        new = f"{mapping[old]:08x}"
        text = m.group(1)
        if any(c.isalpha() for c in text):
            return new.upper() if text.isupper() else new
        prefix = m.string[max(0, m.start() - 7):m.start()]
        return new.upper() if prefix.endswith(("Class_", "Struct_")) else new
    out = HEX.sub(sub, source)
    return re.sub(r"(?m)^(// FUNCTION: 0x)([0-9A-Fa-f]{8})", lambda m: m.group(1) + (
        f"{mapping[int(m.group(2), 16)]:08X}" if int(m.group(2), 16) in mapping else m.group(2)), out)


def placeholder_like(name: str) -> bool:
    """A placeholder name, or a decorated name made from one (`?FUN_10a52530@@YAHH@Z`, a method of
    `Class_10E98D50`): its source spelling carries the address."""
    return is_placeholder(name) or bool(re.match(r"\?\??(?:FUN|DAT|PTR)_[0-9A-Fa-f]{8}@", name))


LITERAL = ("__real@", "??_C@", "s_", "u_")
# What a decorated name puts before its first class name: a vtable, a deleting destructor, a constructor,
# a destructor, or a method's own name (the class follows its `@`).
NAME_PREFIXES = ("??_7", "??_G", "??_E", "??0", "??1", "?")


def classes_in(name: str, known: set) -> List[str]:
    """The native classes a decorated name spells (`??_7AAIModel@@6B@`, `?F@AAIModel@@QAEXXZ`)."""
    out = []
    for fragment in name.split("@"):
        prefix = next((x for x in NAME_PREFIXES if fragment.startswith(x)), "")
        if fragment[len(prefix):] in known:
            out.append(fragment[len(prefix):])
    return out


def rename(names: Dict[str, str], old: str, new: str) -> str:
    """Records class `old` -> `new` in `names`; "" unless it contradicts what is there."""
    if names.get(old, new) != new or (old != new and new in names.values() and names.get(old) != new):
        return f"{old} would be renamed twice"
    if old != new:
        names[old] = new
    return ""


def rename_classes(tname: str, oname: str, source: str, known: set, names: Dict[str, str]) -> str:
    """Maps the native classes in which two decorated names differ when they are otherwise the same name
    (`??_7AAIBehaviorModel@@6B@` / `??_7AAICombatModel@@6B@`): each differing `@` fragment must be a class
    classes.txt knows, behind the same prefix, and a word of the template's source. "" when all map."""
    tf, of = tname.split("@"), oname.split("@")
    if len(tf) != len(of):
        return f"names of other shapes ({tname} / {oname})"
    for a, b in zip(tf, of):
        if a == b:
            continue
        pa = next((x for x in NAME_PREFIXES if a.startswith(x)), "")
        pb = next((x for x in NAME_PREFIXES if b.startswith(x)), "")
        ca, cb = a[len(pa):], b[len(pb):]
        if pa != pb or ca not in known or cb not in known:
            return f"names differ in more than a native class ({tname} / {oname})"
        if not re.search(rf"\b{re.escape(ca)}\b", source):
            return f"{ca} is not a name in the template"
        why = rename(names, ca, cb)
        if why:
            return why
    return ""


def derive(idx: Dict[str, dict], ta: int, oa: int, name: str, oname: str, mapping: Dict[int, int],
           source: str = "", known: Optional[set] = None, names: Optional[Dict[str, str]] = None,
           vtable_class: Optional[Dict[int, str]] = None) -> str:
    """Maps the addresses in `name`, the template's name for its callee `ta` (`??1Class_10E4A538@@QAE@XZ`),
    to the other function's: from its callee's name when that is the same name around other addresses,
    else from the two callees' references at equal offsets when they have one shape (the destructor of
    Class_10E4A538 stores vtable 0x10E4A538 where the other one stores its class's). A name that carries
    a native class instead (`??1AAIModel@@UAE@XZ`) maps that class into `names` the same two ways (the
    callee's vtable gives the class). "" when all map."""
    known, names, vtable_class = known or set(), names if names is not None else {}, vtable_class or {}
    parts = HEX.split(name)  # text, address, text, ...
    classes = classes_in(name, known)
    if len(parts) < 3 and not classes:
        return f"{name} carries no address"
    pairs = []
    if not placeholder_like(oname):
        if len(parts) < 3:
            return rename_classes(name, oname, source, known, names)
        m = re.fullmatch("".join(re.escape(t) if i % 2 == 0 else "([0-9A-Fa-f]{8})" for i, t in enumerate(parts)),
                         oname)
        if not m:
            return f"the callee is named ({name} / {oname})"
        pairs = [(int(x, 16), int(y, 16)) for x, y in zip(parts[1::2], m.groups())]
    else:
        te, oe = idx.get(addr_key(ta)), idx.get(addr_key(oa))
        if not te or not oe or te["key"] != oe["key"]:
            return f"{name} ({fmt_addr(ta)}) and {fmt_addr(oa)} differ in shape"
        trefs, orefs = {r[0]: (r[1], r[2]) for r in te["refs"]}, {r[0]: (r[1], r[2]) for r in oe["refs"]}
        if len(parts) < 3:  # the callee's own references give the classes (its vtable)
            for c in classes:
                offs = sorted(off for off, (a, n) in trefs.items()
                              if vtable_class.get(a) == c or c in classes_in(n, known))
                if not offs or offs[0] not in orefs:
                    return f"{fmt_addr(ta)} does not reference {c}"
                oa2, on = orefs[offs[0]]
                new = vtable_class.get(oa2) or next(iter(classes_in(on, known)), "")
                if not new:
                    return f"{fmt_addr(oa)} references no native class where {fmt_addr(ta)} references {c}"
                if not re.search(rf"\b{re.escape(c)}\b", source):
                    return f"{c} is not a name in the template"
                why = rename(names, c, new)
                if why:
                    return why
            return ""
        for x in (int(h, 16) for h in parts[1::2]):
            offs = sorted(off for off, (a, _) in trefs.items() if a == x)
            if not offs or orefs.get(offs[0], (None,))[0] is None:
                return f"{fmt_addr(ta)} does not reference {fmt_addr(x)}"
            pairs.append((x, orefs[offs[0]][0]))
    for x, y in pairs:
        if mapping.get(x, y) != y:
            return f"{fmt_addr(x)} would map to two addresses"
        mapping[x] = y
    return ""


def rename_words(source: str, names: Dict[str, str]) -> str:
    """`source` with each class `names` maps renamed, as a whole word, all at once."""
    if not names:
        return source
    return re.sub(r"\b(" + "|".join(map(re.escape, sorted(names, key=len, reverse=True))) + r")\b",
                  lambda m: names[m.group(1)], source)


def plan(p: Project, template: int, target: int, idx: Dict[str, dict]) -> Tuple[Optional[str], str]:
    """(candidate source for `target` made from accepted `template`, "") or (None, why not)."""
    src = p.state / "accepted" / f"{addr_key(template)}.cpp"
    if not src.is_file():
        return None, "the template's source is gone"
    source = src.read_text(encoding="utf-8", errors="replace")
    tref, oref = idx[addr_key(template)]["refs"], idx[addr_key(target)]["refs"]
    bindings = (p.accepted().get(template) or {}).get("bindings", ())
    # The template's own EH handler and tables: a candidate emits its own, which the gate binds by place.
    own = {int(b["addr"], 16) for b in bindings if b.get("kind") in ("ehhandler", "funclet", "ehdata")}
    bound = {int(b["addr"], 16): b["name"] for b in bindings if b.get("kind") in ("function", "data")}
    native = p.classes()  # classes.txt: the names a stamp may swap for one another
    known = set(native)
    owners: Dict[int, List[str]] = {}
    for n, c in native.items():
        owners.setdefault(c.vtable, []).append(n)
    vtable_class = {v: ns[0] for v, ns in owners.items() if v and len(ns) == 1}  # not folded tables
    mapping, names = {template: target}, {}

    def by_super(name: str) -> str:
        """Renames each native class in `name` to the super of the class that replaces its subclass."""
        for c in classes_in(name, known):
            subs = [t for t in names if native[t].super == c]
            if not subs:
                return f"no renamed class derives from {c}"
            new = native[names[subs[0]]].super
            if not new or new not in known or not re.search(rf"\b{re.escape(c)}\b", source):
                return f"{names[subs[0]]} has no super to replace {c} with"
            why = rename(names, c, new)
            if why:
                return why
        return ""
    for (off, ta, tname), (_, oa, oname) in zip(tref, oref):
        if ta == oa or ta in own:
            continue
        if ta is None or oa is None:
            return None, f"reference at +{off:#x} unresolved"
        if tname.startswith(LITERAL) or oname.startswith(LITERAL):
            return None, f"literal at +{off:#x} differs"
        tc, oc = vtable_class.get(ta), vtable_class.get(oa)
        if tc and oc and re.search(rf"\b{tc}\b", source):
            # One native class's vtable for another's (classes.txt), whatever symbols.txt calls them yet.
            why = rename(names, tc, oc)
            if why:
                return None, f"reference at +{off:#x}: {why}"
            continue
        if ta in bound and f"{ta:08x}" not in source.lower() and (
                HEX.search(bound[ta]) or classes_in(bound[ta], known)):
            # A callee the source names through its class (`~Class_10E4A538` or `~AAIModel`, bound to a FUN_).
            before = dict(names)
            why = derive(idx, ta, oa, bound[ta], oname, mapping, source, known, names, vtable_class)
            if why and not HEX.search(bound[ta]):
                # Else the class's super (classes.txt): the template's class derives from the callee's,
                # so the other function's class derives from the other callee's.
                names.clear()
                names.update(before)
                why = by_super(bound[ta]) or ""
            if why:
                return None, f"reference at +{off:#x}: {why}"
            continue
        # Names made from the reference's own address (`??_7Class_10E55F00@@6B@`) are placeholders too.
        if not ((placeholder_like(tname) or f"{ta:08x}" in tname.lower())
                and (placeholder_like(oname) or f"{oa:08x}" in oname.lower())):
            # The same name around another native class (the vtable of AAIBehaviorModel / AAICombatModel).
            why = rename_classes(tname, oname, source, known, names)
            if why:
                return None, f"reference at +{off:#x} is named ({tname} / {oname})"
            continue
        if mapping.get(ta, oa) != oa:
            return None, f"{fmt_addr(ta)} would map to two addresses"
        if f"{ta:08x}" not in source.lower():
            return None, f"{fmt_addr(ta)} does not appear in the template's names"
        mapping[ta] = oa
    # A virtual method: the class named after its vtable maps to the other function's vtable.
    import context as contextlib
    try:
        tslots, oslots = contextlib.vtable_slots(p, template), contextlib.vtable_slots(p, target)
    except ImportError:
        return None, "needs iced-x86 to compare the vtable slots"
    if bool(tslots) != bool(oslots):
        return None, "one is in a vtable and the other is not"
    if tslots:
        (tt, ts), (ot, os_) = (int(tslots[0]["table"], 16), tslots[0]["slot"]), \
            (int(oslots[0]["table"], 16), oslots[0]["slot"])
        if ts != os_:
            return None, f"vtable slots differ ({ts} / {os_})"
        tcls, ocls = tslots[0].get("class"), oslots[0].get("class")
        if (tcls or ocls) and tcls != ocls:
            return None, f"registered classes differ ({tcls} / {ocls})"
        if tt != ot:
            mapping[tt] = ot
    if not placeholder_like(p.function(target).name):
        return None, f"the target is already named {p.function(target).name}"
    # A method of a class the mapping does not rename (not virtual, and not named after an address that
    # maps): nothing says the other function belongs to that class.
    cls = (p.accepted().get(template) or {}).get("class") or ""
    if cls and not tslots and cls not in names and not any(f"{a:08x}" in cls.lower() for a in mapping):
        return None, f"a method of {cls}: nothing gives the other function's class"
    out = rename_words(source, names)
    if names:  # a renamed class registers with its own flags and package
        def declare(m: re.Match) -> str:
            c = native.get(m.group(1))
            if m.group(1) not in names.values() or c is None:
                return m.group(0)
            return f"DECLARE_CLASS({m.group(1)}, {m.group(2)}, {c.flags:#x}, {c.package})"
        out = re.sub(r"DECLARE_CLASS\((\w+),\s*(\w+),\s*[^,()]+,\s*(\w+)\)", declare, out)
    return rewrite(out, mapping), ""


def stamp(p: Project, targets: Optional[List[int]] = None, dry_run: bool = False, jobs: int = 4) -> dict:
    """Stamps accepted members' sources onto the open members of their families."""
    idx = index(p)
    fams = families(p, idx)
    accepted = p.accepted()
    integrated = set(p.integrated())
    deferred = set(p.deferred())
    skip = excluded(p)
    records = stamps(p)
    claims = Claims(p)
    work = []
    for k, members in fams.items():
        templates = [m for m in members if m in accepted and (p.state / "accepted" / f"{addr_key(m)}.cpp").is_file()]
        if not templates:
            continue
        for m in members:
            if m in accepted or m in integrated or m in deferred or m in skip or addr_key(m) in records:
                continue
            if targets and m not in targets:
                continue
            # The accepted members nearest to this one first: fewest references to rewrite (a sibling with
            # the same base destructor shares its class chain).
            mrefs = idx[addr_key(m)]["refs"]
            near = sorted(templates, key=lambda t: (sum(x[1] != y[1] for x, y in zip(idx[addr_key(t)]["refs"], mrefs)), t))
            work.append((near[:TEMPLATES], m))
    stamp_dir = p.state_dir("stamps")

    def one(item) -> Tuple[str, dict]:
        templates, target = item
        tried = []
        for template in templates:  # the first member whose source rewrites and passes the gate
            candidate, why = plan(p, template, target, idx)
            if candidate is None:
                tried.append(f"{fmt_addr(template)}: {why}")
                continue
            if dry_run:
                return "stamped", {"addr": fmt_addr(target), "from": fmt_addr(template), "dry_run": True}
            if not claims.take(target, STAMPER, 600):
                return "skipped", {"addr": fmt_addr(target), "why": "claimed by a worker"}
            path = stamp_dir / f"{addr_key(target)}.cpp"
            path.write_text(candidate, encoding="utf-8", newline="\n")
            proc = subprocess.run([sys.executable, str(HERE / "accept.py"), fmt_addr(target),
                                   os.path.relpath(path, p.root)],
                                  env=dict(os.environ, T3_AGENT_ID=STAMPER), cwd=p.root, capture_output=True, text=True)
            claims.release(target, STAMPER)
            if proc.returncode == 0 and "ACCEPTED" in proc.stdout:
                return "stamped", {"addr": fmt_addr(target), "from": fmt_addr(template)}
            reasons = [line.strip()[2:] for line in proc.stdout.splitlines() if line.strip().startswith("- ")]
            tried.append(f"{fmt_addr(template)}: " + (reasons[0] if reasons else
                                                      (proc.stdout + proc.stderr).strip()[-200:] or "rejected"))
        return "failed", {"addr": fmt_addr(target), "from": fmt_addr(templates[0]),
                          "why": "; ".join(tried[:2]) or "no template"}

    out = {"stamped": [], "failed": [], "skipped": []}
    from concurrent.futures import ThreadPoolExecutor
    with ThreadPoolExecutor(max_workers=max(1, jobs)) as pool:
        for kind, result in pool.map(one, work):
            out[kind].append(result)
            if dry_run or kind == "skipped":
                continue
            records[result["addr"][2:]] = {"ok": kind == "stamped", "from": result["from"], "time": time.time(),
                                           **({"why": result["why"]} if kind == "failed" else {})}
    if not dry_run and work:
        atomic_write(p.state / "cache" / "stamps.json", json.dumps(records, indent=1))
    out["summary"] = {k: len(v) for k, v in out.items()}
    return out


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = parser.add_subparsers(dest="cmd", required=True)
    ls = sub.add_parser("list")
    ls.add_argument("--min", type=int, default=2, help="families with at least this many open members")
    ls.add_argument("--limit", type=int, default=30)
    sh = sub.add_parser("show")
    sh.add_argument("addr")
    st = sub.add_parser("stamp")
    st.add_argument("addrs", nargs="*", help="only these open members (default: every one with a template)")
    st.add_argument("--dry-run", action="store_true")
    st.add_argument("--jobs", type=int, default=max(1, min(8, (os.cpu_count() or 2) - 1)),
                    help="members checked in parallel")
    args = parser.parse_args()
    if args.cmd == "stamp" and os.environ.get("T3_AGENT_ID"):
        sys.exit("clusters.py stamp is the lead's")

    p = Project()
    if args.cmd == "list":
        idx = index(p)
        accepted, integrated, deferred = p.accepted(), set(p.integrated()), set(p.deferred())
        skip = excluded(p)
        rows = []
        for k, members in families(p, idx).items():
            open_ = [m for m in members if m not in accepted and m not in integrated and m not in skip]
            if len(open_) < args.min:
                continue
            size = p.function(members[0]).size
            rows.append({"members": len(members), "open": len(open_), "size": size,
                         "accepted": [fmt_addr(m) for m in members if m in accepted][:3],
                         "deferred": sum(1 for m in open_ if m in deferred),
                         "first": fmt_addr(open_[0]), "symbol": p.function(open_[0]).name})
        rows.sort(key=lambda r: (-r["open"] * r["size"], r["first"]))
        emit({"families": len(rows), "open_members": sum(r["open"] for r in rows), "top": rows[:args.limit]})
    elif args.cmd == "show":
        address = p.parse_addr(args.addr)
        idx = index(p)
        e = idx.get(addr_key(address))
        if not e:
            emit({"addr": fmt_addr(address), "family": None})
            return
        members = families(p, idx).get(e["key"], [address])
        accepted, records = p.accepted(), stamps(p)
        skip = excluded(p)
        emit({"addr": fmt_addr(address), "key": e["key"], "members": [
            {"addr": fmt_addr(m), "symbol": p.function(m).name,
             "status": "accepted" if m in accepted else "deferred" if m in p.deferred() else
             "excluded" if m in skip else "open",
             **({"stamp": records[addr_key(m)]} if addr_key(m) in records else {})} for m in members]})
    else:
        emit(stamp(p, [p.parse_addr(a) for a in args.addrs] or None, args.dry_run, args.jobs))


if __name__ == "__main__":
    main()
