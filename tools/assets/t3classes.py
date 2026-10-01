#!/usr/bin/env python3
"""C++ class declarations from the game's UnrealScript, checked against T3Main.exe.

The script packages keep their UnrealScript source (t3props.py), and a native
class's script declares its C++ members: Unreal Engine 2 lays the variables out
in order and checks the result against the C++ class's size. Two kinds of
variables are not members: Ion Storm's gamesys properties (`inherited(N)`,
`runtimeinstantiated(N)`: kept in the property database, see t3props.py) and
`deusexprop` ones (Deus Ex: Invisible War's build only). The property linker
places the rest: bytes 1-aligned, everything else 4-aligned (structs too, their
size rounded up to 4), and a bool shares the 32-bit word of the bool member
before it. Every native class with a script comes out at the size its
registration gives the UClass (config/<version>/classes.txt, tools/classify.py).

Usage:
  t3classes.py check                # each native class's layout against classes.txt
  t3classes.py show <class> [...]   # its members and their offsets (script or C++ name)
  t3classes.py headers              # include/<Package>/<Package>Classes.h

The headers hold names, types and offsets only: no script text, comments or
default values. They are generated, so change this tool rather than them. A
class the scripts do not declare is opaque (padding up to its size). Each
class's size is checked at compile time (T3_CHECK_SIZE, include/Core/Core.h);
`headers` also compiles a check of every member's offset.
"""

from __future__ import annotations

import argparse
import collections
import re
import sys
import tempfile
from dataclasses import dataclass, field
from pathlib import Path
from typing import Dict, Iterable, List, Optional, Set, Tuple

HERE = Path(__file__).resolve().parent
ROOT = HERE.parent.parent
sys.path.insert(0, str(HERE))
sys.path.insert(0, str(ROOT / "tools"))
from t3common import game_dir, run_cli  # noqa: E402
import t3props  # noqa: E402
import categories as categorieslib  # noqa: E402

VERSION = "PC_20040610"
# Variables that are not C++ members (see above).
NOT_MEMBERS = {"inherited", "runtimeinstantiated", "deusexprop"}
# Modifiers that may come between `var` and the type; inherited/runtimeinstantiated take (N).
VAR_MODIFIERS = {
    "const", "native", "private", "protected", "public", "config", "globalconfig", "transient", "localized",
    "travel", "editconst", "editinline", "editinlineuse", "export", "noexport", "input", "deprecated",
    "edfindable", "editinlinenew", "notextexport", "noimport", "duplicatetransient", "cache", "automated",
    "edithide", "editconstarray", "editinlinenotify", "repnotify", "interp", "nontransactional",
    # Ion Storm's
    "customeditor", "customviewer", "deusexprop", "thiefprop", "optiontravel", "objectlist", "configed",
    "inherited", "runtimeinstantiated",
}
BUILTIN = {"byte", "int", "float", "bool", "name", "string", "pointer", "button", "object"}
# Script size and alignment; C++ type and alignment.
SCRIPT_SIZE = {"byte": (1, 1), "button": (1, 1), "int": (4, 4), "float": (4, 4), "name": (4, 4),
               "string": (12, 4), "pointer": (4, 4), "object": (4, 4)}
CPP_TYPE = {"byte": "BYTE", "button": "BYTE", "int": "INT", "float": "FLOAT", "name": "FName",
            "string": "FString", "pointer": "void*", "object": "UObject*"}
# Declared by hand in include/Core/Core.h: not generated. Their C++ sizes where the generated
# classes derive from them.
CORE_H_CLASSES = {"UObject": 0x2C, "UField": 0x34}
CORE_H_STRUCTS = {"vector": "FVector", "rotator": "FRotator"}
CPP_KEYWORDS = {
    "asm", "auto", "bool", "break", "case", "catch", "char", "class", "const", "continue", "default", "delete",
    "do", "double", "else", "enum", "explicit", "export", "extern", "false", "float", "for", "friend", "goto",
    "if", "inline", "int", "long", "mutable", "namespace", "new", "operator", "private", "protected", "public",
    "register", "return", "short", "signed", "sizeof", "static", "struct", "switch", "template", "this",
    "throw", "true", "try", "typedef", "typename", "union", "unsigned", "using", "virtual", "void",
    "volatile", "while",
}
TOKEN = re.compile(r'"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\'|[A-Za-z_]\w*|0x[0-9A-Fa-f]+|\d+(?:\.\d*)?|\S')


def align(n: int, a: int) -> int:
    return (n + a - 1) // a * a


# -- parsing ---------------------------------------------------------------------------
@dataclass
class Var:
    name: str
    type: tuple   # ("byte",) ... ("named", X), ("array", inner), ("class",), ("enum", E), ("struct", S), ...
    dim: str
    mods: Set[str]

    @property
    def member(self) -> bool:
        return not (NOT_MEMBERS & self.mods)


@dataclass
class Scope:
    """A class or struct declaration."""
    kind: str                   # "class" or "struct"
    name: str
    super: Optional[str]
    owner: str                  # the class whose script declares it
    package: str
    vars: List[Var] = field(default_factory=list)
    structs: List["Scope"] = field(default_factory=list)
    enums: Dict[str, List[str]] = field(default_factory=dict)
    consts: Dict[str, str] = field(default_factory=dict)


def tokens(text: str) -> List[str]:
    text = re.sub(r"(?m)^[ \t]*#[^\n]*", "", text)  # #exec directives
    text = re.sub(r"//[^\n]*", "", text)
    text = re.sub(r"/\*.*?\*/", "", text, flags=re.S)
    return TOKEN.findall(text)


class Parser:
    """The declarations of one script: variables, structs, enums and constants; code is skipped."""

    def __init__(self, toks: List[str], package: str):
        self.t, self.i, self.package = toks, 0, package
        self.owner = ""

    def peek(self, k: int = 0) -> str:
        return self.t[self.i + k] if self.i + k < len(self.t) else ""

    def take(self) -> str:
        tok = self.peek()
        self.i += 1
        return tok

    def skip_block(self) -> None:
        depth = 0
        while self.i < len(self.t):
            tok = self.take()
            depth += tok == "{"
            depth -= tok == "}"
            if depth == 0 and tok == "}":
                return

    def skip_declaration(self) -> None:
        paren = 0
        while self.i < len(self.t):
            tok = self.peek()
            paren += tok == "("
            paren -= tok == ")"
            if paren == 0 and tok == ";":
                self.take()
                return
            if paren == 0 and tok == "{":
                self.skip_block()
                if self.peek() == ";":
                    self.take()
                return
            self.take()

    def qualified(self) -> str:
        name = self.take()
        while self.peek() == ".":  # Package.Class, Class.Struct
            self.take()
            name = self.take()
        return name

    def type_(self, scope: Scope) -> tuple:
        tok = self.take()
        low = tok.lower()
        if low == "array" and self.peek() == "<":
            self.take()
            inner = self.type_(scope)
            self.take()  # >
            return ("array", inner)
        if low == "class":
            if self.peek() == "<":
                self.take()
                self.qualified()
                self.take()  # >
            return ("class",)
        if low in ("map", "delegate") and self.peek() == "<":
            depth = 0
            while True:
                tok = self.take()
                depth += tok == "<"
                depth -= tok == ">"
                if depth == 0:
                    return (low,)
        if low == "enum" and self.peek(1) == "{":
            name = self.take()
            scope.enums[name] = self.enum_values()
            return ("enum", name)
        if low == "bitfield":  # Ion Storm: bitfield EFlags [{ ... }]
            name = self.take()
            if self.peek() == "{":
                scope.enums[name] = self.enum_values()
            return ("bitfield", name)
        if low == "struct":
            return ("struct", self.struct(scope).name)
        if low in BUILTIN and self.peek() != ".":
            return (low,)
        self.i -= 1
        return ("named", self.qualified())

    def enum_values(self) -> List[str]:
        self.take()  # {
        values = []
        while self.i < len(self.t) and self.peek() != "}":
            tok = self.take()
            if tok != ",":
                values.append(tok)
        self.take()
        return values

    def var(self, scope: Scope) -> List[Var]:
        if self.peek() == "(":  # editor category
            while self.take() != ")":
                pass
        mods = set()
        while self.peek().lower() in VAR_MODIFIERS:
            mods.add(self.take().lower())
            if self.peek() == "(" and mods & {"inherited", "runtimeinstantiated"}:
                while self.take() != ")":
                    pass
        type_ = self.type_(scope)
        out = []
        while True:
            name, dim = self.take(), "1"
            if self.peek() == "[":
                self.take()
                dim = self.take()
                self.take()  # ]
            while self.peek().startswith('"'):  # Ion Storm's descriptions
                self.take()
            out.append(Var(name, type_, dim, mods))
            if self.peek() != ",":
                break
            self.take()
        while self.i < len(self.t) and self.peek() != ";":
            self.take()
        self.take()
        return out

    def struct(self, scope: Scope) -> Scope:
        while self.peek(1) not in ("{", "") and self.peek(1).lower() != "extends":
            self.take()  # modifiers: native, export, thiefprop, ...
        s = Scope("struct", self.take(), None, self.owner, self.package)
        if self.peek().lower() == "extends":
            self.take()
            s.super = self.qualified()
        scope.structs.append(s)
        self.take()  # {
        while self.i < len(self.t) and self.peek() != "}":
            self.member(s)
        self.take()
        if self.peek() == ";":
            self.take()
        return s

    def member(self, scope: Scope) -> None:
        tok = self.peek().lower()
        if tok == "var":
            self.take()
            scope.vars += self.var(scope)
        elif tok == "struct":
            self.take()
            self.struct(scope)
        elif tok == "enum":
            self.take()
            name = self.take()
            scope.enums[name] = self.enum_values()
            if self.peek() == ";":
                self.take()
        elif tok == "const":
            self.take()
            name = self.take()
            if self.peek() == "=":
                self.take()
                scope.consts[name.lower()] = self.take()
            self.skip_declaration()
        else:
            self.skip_declaration()

    def parse(self) -> Scope:
        while self.i < len(self.t) and self.peek().lower() != "class":
            self.take()
        self.take()
        self.owner = self.take()
        cls = Scope("class", self.owner, None, self.owner, self.package)
        if self.peek().lower() == "extends":
            self.take()
            cls.super = self.qualified()
        while self.i < len(self.t) and self.peek() != ";":
            self.take()  # class modifiers
        self.take()
        while self.i < len(self.t):
            self.member(cls)
        return cls


def load_scripts(game: Path) -> Dict[str, Scope]:
    """Script class name (lowercase) -> its declarations."""
    out = {}
    for package, name, text in t3props.iter_sources(game, t3props.DECL_PACKAGES):
        cls = Parser(tokens(text), package).parse()
        out[cls.name.lower()] = cls
    if not out:
        sys.exit(f"no script sources under {game / 'System'}: pass --game-dir")
    return out


# -- layout ------------------------------------------------------------------------------
@dataclass
class Field:
    offset: int
    bit: Optional[int]          # for bools: the bit in the 32-bit word at offset
    var: Var
    type: tuple                 # resolved: ("byte",) ... ("bool",), ("ref", Cpp class), ("struct", Scope), ...
    size: int                   # bytes, all elements


class Model:
    def __init__(self, scripts: Dict[str, Scope], classes: Dict[str, categorieslib.NativeClass]):
        self.scripts = scripts
        self.classes = classes
        self.native = {name[1:].lower(): c for name, c in classes.items()}
        self.structs: Dict[str, List[Scope]] = collections.defaultdict(list)
        self.enums: Dict[str, List[Tuple[Scope, List[str]]]] = collections.defaultdict(list)
        for cls in scripts.values():
            stack = [cls]
            while stack:
                s = stack.pop()
                for name, values in s.enums.items():
                    self.enums[name.lower()].append((s, values))
                for sub in s.structs:
                    self.structs[sub.name.lower()].append(sub)
                    stack.append(sub)
        self._struct_layouts: Dict[int, Tuple[List[Field], int]] = {}
        self.unknown: collections.Counter = collections.Counter()

    # Names
    def chain(self, name: Optional[str]) -> List[str]:
        """A script class and its supers, lowercase."""
        out = []
        while name and name.lower() not in out:
            out.append(name.lower())
            c = self.scripts.get(name.lower())
            n = self.native.get(name.lower())
            name = c.super if c else (n.super[1:] if n and n.super else None)
        return out

    def cpp_class(self, name: str) -> str:
        """The C++ name of a class the scripts reference."""
        n = self.native.get(name.lower())
        if n:
            return n.name
        c = self.scripts.get(name.lower())
        return ("A" if "actor" in self.chain(name) else "U") + (c.name if c else name)

    def find_struct(self, name: str, owner: str) -> Optional[Scope]:
        found = self.structs.get(name.lower(), [])
        if len(found) > 1:  # the one in the owner's class or its supers
            for cls in self.chain(owner):
                for s in found:
                    if s.owner.lower() == cls:
                        return s
        return found[0] if found else None

    def resolve(self, t: tuple, owner: str) -> tuple:
        kind = t[0]
        if kind == "array":
            return ("array", self.resolve(t[1], owner))
        if kind in ("enum", "bitfield", "class", "map", "delegate") or kind in BUILTIN:
            return t
        name = t[1]
        if kind == "struct" or name.lower() not in self.scripts and name.lower() not in self.native:
            s = self.find_struct(name, owner)
            if s is not None:
                return ("struct", s)
        if name.lower() in self.enums:
            return ("enum", name)
        if name.lower() in self.scripts or name.lower() in self.native:
            return ("ref", self.cpp_class(name))
        self.unknown[name] += 1  # a class without a script (Level, Font, ...)
        return ("ref", "U" + name)

    def dim(self, v: Var, owner: str) -> int:
        if v.dim.isdigit():
            return int(v.dim)
        for cls in self.chain(owner):
            value = self.scripts[cls].consts.get(v.dim.lower()) if cls in self.scripts else None
            if value and value.isdigit():
                return int(value)
        raise ValueError(f"{owner}.{v.name}: array size {v.dim} not found")

    # Script layout
    def script_size(self, t: tuple) -> Tuple[int, int]:
        kind = t[0]
        if kind in SCRIPT_SIZE:
            return SCRIPT_SIZE[kind]
        if kind in ("array", "map"):
            return 12, 4
        if kind in ("class", "object", "ref", "bitfield"):
            return 4, 4
        if kind == "delegate":
            return 8, 4
        if kind == "enum":
            return 1, 1
        if kind == "struct":
            return align(self.struct_layout(t[1])[1], 4), 4
        raise ValueError(f"no size for {t}")

    def lay(self, vars_: Iterable[Var], start: int, owner: str) -> Tuple[List[Field], int]:
        fields_, offset, word, bit = [], start, None, 0
        for v in vars_:
            if not v.member:
                continue  # gamesys properties are not linked: bools around them still pack
            t = self.resolve(v.type, owner)
            if t == ("bool",):
                if word is not None and bit < 31:
                    bit += 1
                else:
                    offset = align(offset, 4)
                    word, bit = offset, 0
                    offset += 4
                fields_.append(Field(word, bit, v, t, 4))
                continue
            word = None
            size, a = self.script_size(t)
            offset = align(offset, a)
            n = self.dim(v, owner)
            fields_.append(Field(offset, None, v, t, size * n))
            offset += size * n
        return fields_, offset

    def struct_layout(self, s: Scope) -> Tuple[List[Field], int]:
        if id(s) not in self._struct_layouts:
            start = 0
            if s.super:
                sup = self.find_struct(s.super, s.owner)
                start = align(self.struct_layout(sup)[1], 4) if sup else 0
            self._struct_layouts[id(s)] = self.lay(s.vars, start, s.owner)
        return self._struct_layouts[id(s)]

    def class_layout(self, cpp: str) -> Tuple[List[Field], int, int]:
        """(fields, start, end) of a native class's own members, from its super's registered size."""
        n = self.classes[cpp]
        s = self.scripts.get(cpp[1:].lower())
        start = self.classes[n.super].size if n.super in self.classes else 0
        if s is None:
            return [], start, start
        fields_, end = self.lay(s.vars, start, s.name)
        return fields_, start, end


# -- C++ -------------------------------------------------------------------------------
class Emitter:
    """C++ declarations for the native classes and the structs and enums their members use."""

    def __init__(self, model: Model):
        self.m = model
        self.struct_names: Dict[int, str] = {}
        self.struct_package: Dict[int, str] = {}
        self.used_enums: Dict[str, Tuple[Scope, List[str]]] = {}
        self.used_structs: List[Scope] = []

    def member_name(self, name: str) -> str:
        return name + "_" if name in CPP_KEYWORDS else name

    def struct_name(self, s: Scope) -> str:
        if id(s) not in self.struct_names:
            core = CORE_H_STRUCTS.get(s.name.lower()) if s.owner.lower() == "object" else None
            name = core or "F" + s.name
            taken = {v for k, v in self.struct_names.items() if k != id(s)}
            if name in taken:
                name = f"F{s.owner}{s.name}"
            self.struct_names[id(s)] = name
        return self.struct_names[id(s)]

    def cpp_type(self, t: tuple) -> Tuple[str, int]:
        """(C++ type, its C++ alignment)."""
        kind = t[0]
        if kind in CPP_TYPE:
            return CPP_TYPE[kind], 1 if kind in ("byte", "button") else 4
        if kind == "class":
            return "UClass*", 4
        if kind == "ref":
            return f"{t[1]}*", 4
        if kind == "array":
            inner, _ = self.cpp_type(t[1])
            return f"TArray<{inner}>", 4
        if kind == "enum":
            return "BYTE", 1
        if kind == "bitfield":
            return "DWORD", 4
        if kind == "struct":
            return self.struct_name(t[1]), self.cpp_align(t[1])
        raise ValueError(f"no C++ type for {t}")

    def cpp_align(self, s: Scope) -> int:
        fields_, _ = self.m.struct_layout(s)
        a = 1
        if s.super:
            sup = self.m.find_struct(s.super, s.owner)
            a = self.cpp_align(sup) if sup else 1
        for f in fields_:
            a = max(a, 4 if f.bit is not None else self.cpp_type(f.type)[1])
        return a

    def members(self, fields_: List[Field], start: int, end: int, comment_enums: bool = True) -> List[str]:
        """Member lines from `start` to `end`, with padding where C++ would place a member early."""
        out, cur = [], start
        for f in fields_:
            name = self.member_name(f.var.name)
            if f.bit is not None and f.bit > 0:
                out.append(f"    BITFIELD {name}:1;")
                continue
            ctype, a = ("BITFIELD", 4) if f.bit is not None else self.cpp_type(f.type)
            if align(cur, a) < f.offset:
                out.append(f"    BYTE Pad{cur:X}[0x{f.offset - cur:X}];")
            elif align(cur, a) > f.offset:
                raise ValueError(f"{name}: C++ would place it at 0x{align(cur, a):X}, the script at 0x{f.offset:X}")
            n = int(f.size // self.m.script_size(f.type)[0]) if f.bit is None else 1
            decl = f"{ctype} {name}:1" if f.bit is not None else f"{ctype} {name}" + (f"[{n}]" if n > 1 else "")
            note = f"  {f.type[1]}" if f.type[0] in ("enum", "bitfield") and comment_enums else ""
            out.append(f"    {decl};".ljust(43) + f" // 0x{f.offset:X}{note}")
            cur = f.offset + f.size
        if cur < end:
            out.append(f"    BYTE Pad{cur:X}[0x{end - cur:X}];")
        return out

    def collect(self, fields_: List[Field]) -> None:
        """Note the structs (with what they use) and enums that members need."""
        for f in fields_:
            t = f.type
            while t[0] == "array":
                t = t[1]
            if t[0] in ("enum", "bitfield") and t[1].lower() in self.m.enums:
                self.used_enums.setdefault(t[1].lower(), self.m.enums[t[1].lower()][0])
            if t[0] == "struct" and t[1] not in self.used_structs:
                s = t[1]
                if s.super:
                    sup = self.m.find_struct(s.super, s.owner)
                    if sup:
                        self.collect([Field(0, None, Var("", ("struct", sup.name), "1", set()), ("struct", sup), 0)])
                self.collect(self.m.struct_layout(s)[0])
                if s not in self.used_structs:
                    self.used_structs.append(s)  # after what it uses


def generate(model: Model) -> Dict[str, str]:
    """Package -> header text."""
    em = Emitter(model)
    classes = model.classes
    # The native classes with a script, and their supers.
    wanted: List[str] = []
    for cpp, n in sorted(classes.items()):
        if cpp[1:].lower() not in model.scripts:
            continue
        chain, c = [], cpp
        while c and c not in CORE_H_CLASSES and c not in wanted and c not in chain:
            chain.append(c)
            c = classes[c].super if c in classes else None
        if c and c not in CORE_H_CLASSES and c not in wanted:
            raise ValueError(f"{cpp} derives from {c}, which neither the scripts nor Core.h declare")
        wanted += reversed(chain)
    bodies: Dict[str, List[str]] = collections.defaultdict(list)
    refs: Dict[str, Set[str]] = collections.defaultdict(set)
    depends: Dict[str, Set[str]] = collections.defaultdict(set)
    for cpp in wanted:
        n = classes[cpp]
        fields_, start, end = model.class_layout(cpp)
        if n.super in CORE_H_CLASSES:
            start = CORE_H_CLASSES[n.super]
            if start != classes[n.super].size:
                raise ValueError(f"{cpp}: Core.h's {n.super} is 0x{start:X} bytes, the game's 0x{classes[n.super].size:X}")
        if align(end, 4) != n.size and fields_:
            raise ValueError(f"{cpp}: the script lays out 0x{align(end, 4):X} bytes, the game registers 0x{n.size:X}")
        em.collect(fields_)
        lines = [f"class {cpp} : public {n.super}", "{", "public:"]
        lines += em.members(fields_, start, n.size if not fields_ else end) if fields_ or n.size > start else []
        lines += ["};", f"T3_CHECK_SIZE({cpp}, 0x{n.size:X});", ""]
        bodies[n.package] += lines
        if n.super in classes and classes[n.super].package != n.package:
            depends[n.package].add(classes[n.super].package)
        for f in fields_:
            t = f.type
            while t[0] == "array":
                t = t[1]
            if t[0] == "ref":
                refs[n.package].add(t[1])
            if t[0] == "struct" and t[1].package != n.package:
                depends[n.package].add(t[1].package)
    # Structs, in the package of the class that declares them, before its classes.
    struct_lines: Dict[str, List[str]] = collections.defaultdict(list)
    for s in em.used_structs:
        if s.owner.lower() == "object" and s.name.lower() in CORE_H_STRUCTS:
            continue
        fields_, end = model.struct_layout(s)
        size = align(end, 4)
        start, base = 0, ""
        if s.super:
            sup = model.find_struct(s.super, s.owner)
            start, base = align(model.struct_layout(sup)[1], 4), f" : public {em.struct_name(sup)}"
            if sup.package != s.package:
                depends[s.package].add(sup.package)
        name = em.struct_name(s)
        lines = [f"struct {name}{base}", "{"] + em.members(fields_, start, size) + ["};",
                                                                                  f"T3_CHECK_SIZE({name}, 0x{size:X});", ""]
        struct_lines[s.package] += lines
        for f in fields_:
            t = f.type
            while t[0] == "array":
                t = t[1]
            if t[0] == "ref":
                refs[s.package].add(t[1])
            if t[0] == "struct" and t[1].package != s.package:
                depends[s.package].add(t[1].package)
    # Enums whose values collide with another enum's stay out (their members are BYTEs anyway).
    owners = collections.Counter(v for _, values in em.used_enums.values() for v in values)
    enum_lines: Dict[str, List[str]] = collections.defaultdict(list)
    for key, (scope, values) in sorted(em.used_enums.items()):
        name = next(k for k in scope.enums if k.lower() == key)
        if any(owners[v] > 1 or not re.fullmatch(r"[A-Za-z_]\w*", v) for v in values):
            continue
        body = [f"    {v}," for v in values]
        body[-1] = body[-1].rstrip(",")
        enum_lines[scope.package] += [f"enum {name}", "{"] + body + ["};", ""]
    packages = [p for p in t3props.DECL_PACKAGES if bodies.get(p) or struct_lines.get(p) or enum_lines.get(p)]
    order = topological(packages, depends)
    out = {}
    for pkg in order:
        guard = f"T3_{pkg.upper()}_{pkg.upper()}CLASSES_H"
        head = [f"// {pkg}/{pkg}Classes.h: the {pkg} package's native classes, as the game's scripts declare",
                "// them (names, types, offsets) and T3Main.exe sizes them. Generated by",
                "// tools/assets/t3classes.py: do not edit.",
                f"#ifndef {guard}", f"#define {guard}", "", '#include "Core/Core.h"']
        head += [f'#include "{d}/{d}Classes.h"' for d in order if d in depends[pkg]]
        forward = sorted(refs[pkg])
        head += [""] + [f"class {c};" for c in forward] + [""] if forward else [""]
        text = head + enum_lines[pkg] + struct_lines[pkg] + bodies[pkg] + [f"#endif"]
        out[pkg] = "\n".join(text).rstrip() + "\n"
    return out


def topological(packages: List[str], depends: Dict[str, Set[str]]) -> List[str]:
    out: List[str] = []
    state: Dict[str, int] = {}

    def visit(p: str) -> None:
        if state.get(p) == 2:
            return
        if state.get(p) == 1:
            raise ValueError(f"the packages' headers depend on each other in a cycle through {p}")
        state[p] = 1
        for d in sorted(depends.get(p, ())):
            if d != p:
                visit(d)
        state[p] = 2
        out.append(p)

    for p in packages:
        visit(p)
    return out


# -- commands --------------------------------------------------------------------------
def offset_checks(model: Model, headers: Dict[str, str]) -> str:
    """A translation unit that checks every non-bitfield member's offset."""
    em = Emitter(model)
    lines = [f'#include "{p}/{p}Classes.h"' for p in headers]
    lines.append("#define T3_OFFSET(T, M) ((unsigned)&((T*)0)->M)")
    k = 0
    for cpp in sorted(model.classes):
        if cpp[1:].lower() not in model.scripts or cpp in CORE_H_CLASSES:
            continue
        for f in model.class_layout(cpp)[0]:
            if f.bit is None:
                lines.append(f"typedef char T3_OffsetCheck{k}[T3_OFFSET({cpp}, {em.member_name(f.var.name)}) == "
                             f"0x{f.offset:X} ? 1 : -1];")
                k += 1
    return "\n".join(lines) + "\n"


def compile_check(text: str) -> Tuple[bool, str]:
    sys.path.insert(0, str(ROOT / "tools" / "agent"))
    from common import Project  # noqa: E402
    p = Project()
    with tempfile.TemporaryDirectory(dir=p.state_dir("tmp")) as tmp:
        src = Path(tmp) / "t3classes_check.cpp"
        src.write_text(text, encoding="utf-8")
        return p.compile(src, Path(tmp) / "t3classes_check.obj", p.configure.CFLAGS)


def main() -> None:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--game-dir")
    ap.add_argument("--version", default=VERSION)
    sub = ap.add_subparsers(dest="cmd", required=True)
    sub.add_parser("check")
    s = sub.add_parser("show")
    s.add_argument("names", nargs="+")
    s = sub.add_parser("headers")
    s.add_argument("-o", "--output", default=str(ROOT / "include"))
    args = ap.parse_args()
    classes = categorieslib.load_classes(ROOT / "config" / args.version / "classes.txt")
    if not classes:
        sys.exit("no classes.txt: run python tools/classify.py write")
    model = Model(load_scripts(game_dir(args.game_dir)), classes)
    if args.cmd == "check":
        good, bad = 0, []
        for cpp, n in sorted(classes.items()):
            if cpp[1:].lower() not in model.scripts or not n.super:
                continue
            _, _, end = model.class_layout(cpp)
            if align(end, 4) == n.size:
                good += 1
            else:
                bad.append(f"{cpp}: the script lays out 0x{align(end, 4):X} bytes, the game registers 0x{n.size:X}")
        print("\n".join(bad + [f"{good} of {good + len(bad)} native classes match their registered size"]))
        sys.exit(1 if bad else 0)
    if args.cmd == "show":
        em = Emitter(model)
        for name in args.names:
            cpp = name if name in classes else model.cpp_class(name)
            if cpp not in classes:
                sys.exit(f"{name} is not a native class")
            n = classes[cpp]
            fields_, start, end = model.class_layout(cpp)
            print(f"class {cpp} : public {n.super}  // {n.package}, {n.category}, 0x{n.size:X} bytes")
            print("\n".join(em.members(fields_, start, n.size if fields_ else start)))
        return
    headers = generate(model)
    out = Path(args.output)
    for pkg, text in headers.items():
        path = out / pkg / f"{pkg}Classes.h"
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_text(text, encoding="utf-8", newline="\n")
        print(f"wrote {path.relative_to(ROOT) if path.is_relative_to(ROOT) else path}")
    ok, log = compile_check(offset_checks(model, headers))
    print("offsets and sizes compile-checked" if ok else f"the check does not compile:\n{log}")
    if model.unknown:
        print("classes without a script, referenced by pointer: " + ", ".join(sorted(model.unknown)))
    sys.exit(0 if ok else 1)


if __name__ == "__main__":
    run_cli(main)
