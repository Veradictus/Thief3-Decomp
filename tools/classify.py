#!/usr/bin/env python3
"""Whose code each function is: Ion Storm's game, Epic's engine or a third-party library.

    python tools/classify.py write [--version PC_20040610]   # config/<version>/categories.txt
    python tools/classify.py explain <addr> [...]            # the evidence for a function
    python tools/classify.py stats                           # bytes and functions per category

The decompilation covers Ion Storm's game code only (CONTRIBUTING.md). The exe
does not record which object file a function came from, so this derives it from
evidence in T3Main.exe (orig/) and symbols.txt:

  * Native class registrations. Each UObject class registers itself lazily:
        if (!G) { G = <getter>("<Package>"); <init>(); }
    The getter holds the class name and hands the UClass its internal
    constructor; getter and constructor sit in the class's own object file.
  * Authorship of a class. Ion Storm's packages (AICore, GamePhysics, T3AI,
    T3Game, T3GamePhysics, T3Player) are game. Epic's (Core, Engine, Fire,
    D3DDrv, WinDrv, Window) are engine, except the classes Ion Storm added to
    them (ION_CLASSES): their UnrealScript source lacks Epic's header, and they
    are Ion Storm's systems (links, archetypes, stimuli, subsystems).
  * Virtual methods. A class's constructor stores its vtable; the functions in
    it are the class's methods, inherited ones included. A function only in
    game classes' vtables is game, only in engine classes' is engine; one in
    both (an inherited engine method, or identical code the linker folded) is
    left to its neighbours.
  * Names in symbols.txt of Epic's classes (UObject::..., FName::...) and of
    Ion Storm's systems (Window, Options, Config, ...), and the vtables that
    hold a method of the latter.
  * Strings a function uses (LIB_STRINGS, ION_STRINGS, EPIC_STRINGS).
  * Libraries: from configure.py's LIBRARY_START on, except game evidence.

The functions of one object file are contiguous, and so are the object files
of one library, so the functions between two evidence points of one category
take it when the points are close enough. Epic's and Ion Storm's files
interleave inside Epic's libraries (Ion Storm added its own files to the
Engine package): there, engine evidence fills the stretch to the next engine
evidence and game evidence only FILL_LIMIT bytes; outside them it is the
other way round. Library evidence fills up to LIBRARY_FILL. Everything else
is unknown: no evidence yet. EH funclets (.text$x) are not classified: they
are compiled with their parent function.

categories.txt is generated and committed (configure.py reads it; CI has no
exe): one half-open range per line (tools/categories.py), covering .text
outside .text$x.
"""

import argparse
import bisect
import collections
import re
import struct
import sys
from pathlib import Path
from typing import Dict, List, Optional, Set, Tuple

ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT))
sys.path.insert(0, str(ROOT / "tools"))

import categories as categorieslib  # noqa: E402
import configure  # noqa: E402
from pe import PE  # noqa: E402

GAME, ENGINE, LIBS, UNKNOWN = categorieslib.GAME, categorieslib.ENGINE, categorieslib.LIBS, categorieslib.UNKNOWN

ION_PACKAGES = {"AICore", "GamePhysics", "T3AI", "T3Game", "T3GamePhysics", "T3Player"}
EPIC_PACKAGES = {"Core", "D3DDrv", "Engine", "Fire", "WinDrv", "Window"}
# Classes Ion Storm added to Epic's packages. Their UnrealScript source has no
# Epic header ("This is a built-in Unreal class"), or they are Ion Storm's own
# systems; the *LinkDataObject classes (Ion Storm's links) are matched by name.
# A class that is not certainly Ion Storm's stays Epic's.
ION_CLASSES = {
    "Core": {"BitfieldEnum", "BitfieldProperty", "LinkDataObject"},
    "Engine": {
        "AISubsystem", "AmbientLightVolume", "CARDEntry", "ElevatorFloors", "FX", "GameSubsystem", "Marker",
        "MetaData", "MetaProperty", "MissingArch", "ObjSysTest", "ObjSysTestChild", "PhysicsSubsystem",
        "PlayerPawn", "SpecialOptions", "StimulusModifierObject", "SwooshEffectObject", "TriggerRegistrar",
        "VulnerabilityObject", "ZoneProperties",
    },
}
# Ion Storm's own systems that symbols.txt names (docs/engine.md: the INI layer, options, the
# loading screen, UI windows, the clock).
ION_NAMED = re.compile(r"^(?:\?[^@]+@|\?\?[0-9A-Z_])(Window|WindowManager|Options|Config|LoadingScreen|TimeManager"
                       r"|T3[A-Za-z]\w*)@@|^(?:Window|WindowManager|Options|Config|LoadingScreen|TimeManager)::")
# C++ classes of Epic's Core and Engine that symbols.txt names (not UObject classes).
EPIC_NAMED = re.compile(r"^(?:\?[^@]+@|\?\?[0-9A-Z_])(U|A|F)(Object|Name|String|Array|Frame|OutputDevice\w*|Archive"
                        r"|WindowsViewport|D3DRenderDevice|Malloc\w*|Canvas\w*|URL)@@")
# Strings a function uses. Library code: STL's errors, the LIPSinc lip-sync SDK, Havok's
# collision classes. Ion Storm's: its file and ini names, systems and naming (cHungarian::,
# ::m_ members, .\Source\ paths). Epic's: messages only its stock code prints.
LIB_STRINGS = re.compile(r"<T> too long|<T> iterator|string too long|invalid string position|TLIPSinc"
                         r"|^(?:Tt|Lt|St|Lthk)[A-Z][A-Za-z]+$")
ION_STRINGS = re.compile(r"(?<![A-Za-z])T3|Flesh|Garrett|Schema|Papyrus|LinkDataObject|Gamesys|ION_ROOT|VIKTORIA"
                         r"|DX2|MetaSound|\.\\Source\\|UnitTests?\.cpp|Test\.cpp|^c[A-Z][a-z]\w*::|::m_")
EPIC_STRINGS = re.compile(r"SpawnActor failed because|FLineBatcher|FCanvasUtil|FURL::|UnrealEd|EditorPrefs\.ini"
                          r"|FPropertyItem|FObjectsHierarchyItem|ClassCaption|appError called|%sUnreal%s|Log file open")
# Epic's libraries are where engine evidence lies at most CLUSTER apart. Inside them Epic's and
# Ion Storm's files interleave: engine evidence fills the stretch to the next engine evidence,
# game evidence only up to FILL_LIMIT. Outside them it is the other way round.
CLUSTER = 0x10000
FILL_LIMIT = 0x4000
LIBRARY_FILL = 0x20000
# Virtual methods this small are not evidence (see evidence()).
TRIVIAL = 16

# mov eax,[G]; test eax,eax; jne short; push "<Package>"; call <getter>; add esp,4; mov [G],eax
REGISTRATION = re.compile(rb"\xA1(.{4})\x85\xC0\x75.\x68(.{4})\xE8(.{4})\x83\xC4\x04\xA3(.{4})", re.S)


class Image:
    def __init__(self, version: str):
        info = configure.VERSIONS[version]
        self.pe = PE((ROOT / "orig" / version / info["exe"]).read_bytes())
        self.base = self.pe.image_base
        config = ROOT / "config" / version
        symbols = configure.symbolslib.load(config / "symbols.txt")
        self.symbols = symbols
        self.functions = sorted((s for s in symbols if s.is_function and s.size > 0), key=lambda s: s.address)
        self.at = {f.address: f for f in self.functions}
        self.starts = [f.address for f in self.functions]

    def read(self, va: int, size: int) -> bytes:
        return self.pe.read_rva(va - self.base, size)

    def cstr(self, va: int) -> Optional[str]:
        try:
            raw = self.read(va, 96).split(b"\0")[0]
        except Exception:
            return None
        return raw.decode("latin-1") if raw and all(32 <= c < 127 for c in raw) else None

    def decode(self, address: int, limit: int = 0x400):
        from iced_x86 import Decoder
        f = self.at.get(address)
        return list(Decoder(32, self.read(address, f.size if f else limit), ip=address))


def vtables(img: Image) -> Dict[int, List[int]]:
    """Tables of function pointers in read-only data, keyed by every start the code uses."""
    from iced_x86 import Decoder, OpKind
    starts = set(img.starts)
    used: Set[int] = set()
    runs: List[Tuple[int, List[int]]] = []
    for sec in img.pe.sections:
        data = img.pe.read_rva(sec.va, min(sec.vsize, sec.raw_size)) if sec.raw_size else b""
        base = img.base + sec.va
        if sec.executable:
            for insn in Decoder(32, data, ip=base):
                for i in range(insn.op_count):
                    if insn.op_kind(i) == OpKind.IMMEDIATE32:
                        used.add(insn.immediate32)
            continue
        if sec.writable:
            continue
        run: List[int] = []
        for k in range(0, len(data) - 3, 4):
            value = int.from_bytes(data[k:k + 4], "little")
            if value in starts:
                run.append(value)
                continue
            if run:
                runs.append((base + k - 4 * len(run), run))
            run = []
    tables: Dict[int, List[int]] = {}
    for first, run in runs:
        cuts = [i for i in range(len(run)) if first + 4 * i in used] + [len(run)]
        for a, b in zip(cuts, cuts[1:]):
            tables[first + 4 * a] = run[a:b]
    return tables


def registrations(img: Image) -> Dict[int, Tuple[str, int]]:
    """getter -> (package, global) for every lazy native class registration."""
    text = next(s for s in img.pe.sections if s.name == ".text")
    code = img.pe.read_rva(text.va, text.initialized_size)
    out: Dict[int, Tuple[str, int]] = {}
    for m in REGISTRATION.finditer(code):
        g1, s, rel, g2 = (struct.unpack("<I", m.group(i))[0] for i in (1, 2, 3, 4))
        if g1 != g2:
            continue
        getter = (img.base + text.va + m.end(3) + struct.unpack("<i", m.group(3))[0]) & 0xFFFFFFFF
        package = img.cstr(s)
        if getter in img.at and package:
            out.setdefault(getter, (package, g1))
    return out


def class_vtable(img: Image, fn: int, tables: Dict[int, List[int]], depth: int = 0) -> Optional[int]:
    """The last vtable a constructor stores through `this` (ecx at entry, or the wrapper's [esp+4])."""
    from iced_x86 import Mnemonic, OpKind, Register
    this = {Register.ECX}
    last = None
    for i in img.decode(fn):
        m = i.mnemonic
        if m == Mnemonic.MOV and i.op0_kind == OpKind.REGISTER:
            if i.op1_kind == OpKind.REGISTER and i.op1_register in this:
                this.add(i.op0_register)
            elif (depth == 0 and i.op1_kind == OpKind.MEMORY and i.memory_base == Register.ESP
                  and i.memory_displacement == 4):
                this.add(i.op0_register)
            else:
                this.discard(i.op0_register)
        elif m == Mnemonic.MOV and i.op0_kind == OpKind.MEMORY and i.op1_kind == OpKind.IMMEDIATE32:
            if (i.memory_base in this and i.memory_index == Register.NONE and i.memory_displacement == 0
                    and i.immediate32 in tables):
                last = i.immediate32
        elif m in (Mnemonic.CALL, Mnemonic.JMP) and i.op0_kind == OpKind.NEAR_BRANCH32:
            t = i.near_branch32
            if last is None and depth < 3 and Register.ECX in this and t in img.at and img.at[t].size < 0x800:
                last = class_vtable(img, t, tables, depth + 1) or last
            if m == Mnemonic.CALL:
                this -= {Register.EAX, Register.ECX, Register.EDX}
        elif m not in (Mnemonic.TEST, Mnemonic.CMP, Mnemonic.PUSH) and i.op_count and i.op0_kind == OpKind.REGISTER:
            this.discard(i.op0_register)
    return last


def classes(img: Image, tables: Dict[int, List[int]]) -> List[dict]:
    """Every registered native class: name, package, category, getter, constructor, vtable."""
    from iced_x86 import Mnemonic, OpKind
    out = []
    for getter, (package, _) in sorted(registrations(img).items()):
        strings, pointers = [], []
        for i in img.decode(getter):
            if i.mnemonic == Mnemonic.PUSH and i.op0_kind == OpKind.IMMEDIATE32:
                s = img.cstr(i.immediate32)
                if s:
                    strings.append(s)
                elif i.immediate32 in img.at and not configure.FUNCLETS[0] <= i.immediate32 < configure.FUNCLETS[1]:
                    pointers.append(i.immediate32)
        name = strings[-1] if strings else "?"
        # The UClass constructor takes the static constructor, then the internal one.
        constructor = pointers[-1] if pointers else None
        vtable = class_vtable(img, constructor, tables) if constructor else None
        ion = (package in ION_PACKAGES or name in ION_CLASSES.get(package, ())
               or (package == "Engine" and name.endswith("LinkDataObject")))
        category = GAME if ion else ENGINE if package in EPIC_PACKAGES else UNKNOWN
        out.append({"name": name, "package": package, "category": category, "getter": getter,
                    "constructor": constructor, "vtable": vtable})
    return out


def evidence(img: Image) -> Tuple[Dict[int, Set[str]], Dict[int, List[str]]]:
    """function -> categories its evidence gives, and the reasons."""
    tables = vtables(img)
    cats: Dict[int, Set[str]] = collections.defaultdict(set)
    why: Dict[int, List[str]] = collections.defaultdict(list)

    def add(address: int, category: str, reason: str) -> None:
        cats[address].add(category)
        why[address].append(reason)

    for c in classes(img, tables):
        label = f"{c['package']}.{c['name']}"
        add(c["getter"], c["category"], f"registers {label}")
        if c["constructor"]:
            add(c["constructor"], c["category"], f"internal constructor of {label}")
        for slot, fn in enumerate(tables.get(c["vtable"], [])):
            # The linker folds identical small bodies (return 0, {}) into one copy that sits in
            # whichever object came first: their vtables say nothing about where they are.
            if img.at[fn].size > TRIVIAL:
                add(fn, c["category"], f"slot {slot} of {label}'s vtable 0x{c['vtable']:08X}")
    for f in img.functions:
        if EPIC_NAMED.match(f.name):
            add(f.address, ENGINE, f"named {f.name}")
        elif ION_NAMED.match(f.name):
            add(f.address, GAME, f"named {f.name}")
    # The vtables of Ion Storm's named classes (and of the classes derived from them).
    for table, slots in tables.items():
        named = next((img.at[fn].name for fn in slots if ION_NAMED.match(img.at[fn].name)), None)
        if named:
            for slot, fn in enumerate(slots):
                if img.at[fn].size > TRIVIAL:
                    add(fn, GAME, f"slot {slot} of vtable 0x{table:08X}, which holds {named}")
    from iced_x86 import OpKind
    funclets = configure.FUNCLETS
    for f in img.functions:
        if funclets[0] <= f.address < funclets[1]:
            continue
        for insn in img.decode(f.address):
            for k in range(insn.op_count):
                if insn.op_kind(k) != OpKind.IMMEDIATE32:
                    continue
                s = img.cstr(insn.immediate32)
                if not s:
                    continue
                for pattern, category in ((LIB_STRINGS, LIBS), (ION_STRINGS, GAME), (EPIC_STRINGS, ENGINE)):
                    if pattern.search(s):
                        add(f.address, category, f"uses the string {s[:48]!r}")
                        break
    return cats, why


def classify(img: Image) -> Tuple[Dict[int, str], Dict[int, List[str]]]:
    """function -> category, for every function outside .text$x."""
    cats, why = evidence(img)
    funclets = configure.FUNCLETS
    fns = [f for f in img.functions if not funclets[0] <= f.address < funclets[1]]
    out: Dict[int, str] = {}
    points: List[Tuple[int, str]] = []
    for f in fns:
        c = cats.get(f.address, set())
        if len(c) == 1:
            out[f.address] = next(iter(c))
            points.append((f.address, out[f.address]))
    # Library region: libs unless evidence says otherwise.
    for f in fns:
        if f.address >= configure.LIBRARY_START and f.address not in out:
            out[f.address] = LIBS
    # Epic's libraries: runs of engine evidence at most CLUSTER apart.
    epic: List[Tuple[int, int]] = []
    for a, c in points:
        if c != ENGINE:
            continue
        if epic and a - epic[-1][1] <= CLUSTER:
            epic[-1] = (epic[-1][0], a)
        else:
            epic.append((a, a))
    epic_starts = [s for s, _ in epic]

    def in_epic(a: int, b: int) -> bool:
        i = bisect.bisect_right(epic_starts, b) - 1
        return i >= 0 and epic[i][1] >= a

    # Fill between evidence points of one category. Library code the compiler instantiates
    # inside an object (STL's helpers) does not interrupt it.
    index = {f.address: i for i, f in enumerate(fns)}
    chain = [(a, c) for a, c in points if c != LIBS]
    for (a, ca), (b, cb) in zip(chain, chain[1:]):
        if ca != cb:
            continue
        inside = in_epic(a, b)
        if b - a > FILL_LIMIT and (ca == GAME) == inside:
            continue
        for f in fns[index[a] + 1:index[b]]:
            if f.address not in out:
                out[f.address] = ca
                why[f.address].append(f"between 0x{a:08X} and 0x{b:08X}, both {ca}")
    # Libraries linked in one piece (Havok before LIBRARY_START): library evidence with nothing
    # else between fills up to LIBRARY_FILL.
    for (a, ca), (b, cb) in zip(points, points[1:]):
        if ca == cb == LIBS and b - a <= LIBRARY_FILL:
            for f in fns[index[a] + 1:index[b]]:
                if f.address not in out:
                    out[f.address] = LIBS
                    why[f.address].append(f"between 0x{a:08X} and 0x{b:08X}, both library code")
    for f in fns:
        out.setdefault(f.address, UNKNOWN)
    return out, why


def ranges(img: Image, labels: Dict[int, str]) -> List[Tuple[int, int, str]]:
    """Merged half-open ranges: each function's category runs until the next function starts."""
    funclets = configure.FUNCLETS
    fns = [f for f in img.functions if f.address in labels]
    text = next(s for s in img.pe.sections if s.name == ".text")
    text_end = img.base + text.va + text.vsize
    out: List[Tuple[int, int, str]] = []
    for i, f in enumerate(fns):
        end = fns[i + 1].address if i + 1 < len(fns) else text_end
        if f.address < funclets[0] < end:
            end = funclets[0]
        cat = labels[f.address]
        if out and out[-1][2] == cat and out[-1][1] == f.address:
            out[-1] = (out[-1][0], end, cat)
        else:
            out.append((f.address, end, cat))
    return out


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("command", choices=["write", "explain", "stats"])
    parser.add_argument("addrs", nargs="*")
    parser.add_argument("--version", default=configure.DEFAULT_VERSION, choices=sorted(configure.VERSIONS))
    args = parser.parse_args()
    img = Image(args.version)
    labels, why = classify(img)
    if args.command == "explain":
        for a in args.addrs:
            address = int(a, 16)
            print(f"0x{address:08X} {labels.get(address, 'not a function outside .text$x')}")
            for reason in why.get(address, []) or ["no evidence"]:
                print(f"  {reason}")
        return
    sizes = collections.Counter()
    counts = collections.Counter()
    for f in img.functions:
        if f.address in labels:
            sizes[labels[f.address]] += f.size
            counts[labels[f.address]] += 1
    for c in (GAME, ENGINE, LIBS, UNKNOWN):
        print(f"{c:8} {counts[c]:6} functions {sizes[c]:9} bytes")
    if args.command == "write":
        path = ROOT / "config" / args.version / "categories.txt"
        categorieslib.save(path, ranges(img, labels))
        print(f"wrote {path.relative_to(ROOT)}")


if __name__ == "__main__":
    main()
