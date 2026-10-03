#!/usr/bin/env python3
"""Self-test of the matching tools against synthetic targets built with the real compiler.

    python tools/agent/selftest.py [-k NAME] [--keep]

Needs the toolchain configure.py downloads (build/tools, build/compilers),
not the game: reference C++ is compiled and reshaped like delink's split
(tools/agent/fixture.py) inside a temporary project, which the tools reach
through the T3_AGENT_* variables. The real config/ is never touched.
"""

import argparse
import json
import os
import shlex
import shutil
import struct
import subprocess
import sys
import tempfile
import time
import traceback
from pathlib import Path

HERE = Path(__file__).resolve().parent
sys.path.insert(0, str(HERE))

import coff  # noqa: E402
import fixture  # noqa: E402
from common import PATIENCE, ROOT, Project, splitslib, symbolslib  # noqa: E402

DECLS = """struct Foo { int a; int b; float c; int Get() const; };
extern int g_counter;
int Helper(int);
int Other(int);
struct Res { Res(); ~Res(); int n; };
int Use(int);
"""
FUNCTIONS = {
    "?Get@Foo@@QBEHXZ": "int Foo::Get() const { return a + b * 3 + Helper(g_counter); }",
    "?Scale@@YAMPAUFoo@@@Z": "float Scale(Foo* f) { return f->c * 2.5f; }",
    "?Seven@@YAHH@Z": "int Seven(int x) { return x * 7 + 100; }",
    "?Twice@@YAHH@Z": "int Twice(int x) { return Helper(x) + Helper(x + 1); }",
    "?Sw@@YAHHH@Z": """int Sw(int k, int v)
{
    switch (k) {
    case 0: return v + 1;
    case 1: return v * 7;
    case 2: return v - 3;
    case 3: return v ^ 5;
    case 4: return v << 2;
    case 5: return v / 3;
    default: return 0;
    }
}""",
    "?WithEh@@YAHH@Z": "int WithEh(int a) { Res r1; Res r2; return Use(a + r1.n + r2.n); }",
    "?Name@@YAPBDXZ": 'const char* Name() { return "hello world"; }',
    "?Callee@@YAHH@Z": "int Callee(int x) { return x * 5 + 3; }",
    "?Caller@@YAHH@Z": "int Caller(int x) { return Callee(x) + 1; }",
    "?Fib@@YAHH@Z": "int Fib(int n) { return n < 2 ? n : Fib(n - 1) + Fib(n - 2); }",
    # A family: the same code around another callee.
    "?TwinA@@YAHH@Z": "int TwinA(int x) { return Helper(x) * 3 + 1; }",
    "?TwinB@@YAHH@Z": "int TwinB(int x) { return Other(x) * 3 + 1; }",
}
# In the reference, Callee stays a call (as if it lived in another file); a unit defining it would inline it.
REFERENCE = DECLS + "\n".join(("__declspec(noinline) " if s == "?Callee@@YAHH@Z" else "") + body
                               for s, body in FUNCTIONS.items()) + "\n"
CALLEE_DECL = "int Callee(int);\n"
# A family whose members each have their own EH handler (test_families).
EH_TWINS = ("int EhTwinA(int a) { Res r; return Helper(a + r.n); }\n"
            "int EhTwinB(int a) { Res r; return Other(a + r.n); }\n")


class Env:
    """A fixture project and a way to run the tools in it."""

    def __init__(self, base: Path, name: str, named=frozenset(), extra=None, aliases=None, reference=REFERENCE):
        self.root = base / name
        self.root.mkdir(parents=True)
        project = Project()
        ref = fixture.compile_reference(project, reference, self.root / "reference")
        self.target = fixture.build(ref, self.root, named=set(named), extra_symbols=extra, aliases=aliases)
        self.env = fixture.environment(self.root)
        self.scratch = self.root / "scratch"
        self.scratch.mkdir()
        self.n = 0

    def addr(self, symbol: str) -> str:
        return f"0x{self.target.addr(symbol):08X}"

    def candidate(self, symbol: str, body: str = None, marker: bool = True, extra: str = "") -> Path:
        """A scratch file for `symbol`: the shared declarations, then the function (default: the reference)."""
        self.n += 1
        extra += CALLEE_DECL if symbol == "?Caller@@YAHH@Z" else ""
        path = self.scratch / f"c{self.n:03d}.cpp"
        mark = f"// FUNCTION: {self.addr(symbol)}\n" if marker else ""
        path.write_text(DECLS + extra + mark + (body or FUNCTIONS[symbol]) + "\n", encoding="utf-8")
        return path

    def run(self, tool: str, *args, agent: str = "selftest", env=None) -> subprocess.CompletedProcess:
        e = dict(self.env, T3_AGENT_ID=agent, **(env or {}))
        return subprocess.run([sys.executable, str(HERE / tool), *map(str, args)], env=e, capture_output=True,
                              text=True, cwd=ROOT)


def check(condition: bool, what: str, proc: subprocess.CompletedProcess = None) -> None:
    if not condition:
        detail = f"\n--- stdout\n{proc.stdout}\n--- stderr\n{proc.stderr}" if proc is not None else ""
        raise AssertionError(what + detail)


# -- tests -----------------------------------------------------------------------------
def test_exact_match_accepted(base: Path) -> None:
    e = Env(base, "exact")
    for symbol in FUNCTIONS:
        path = e.candidate(symbol)
        proc = e.run("try.py", e.addr(symbol), path)
        check(proc.returncode == 0 and "MATCH" in proc.stdout, f"try.py should match {symbol}", proc)
        proc = e.run("accept.py", e.addr(symbol), path)
        check(proc.returncode == 0 and "ACCEPTED" in proc.stdout, f"accept.py should accept {symbol}", proc)
    record = json.loads((e.root / "build/agent/accepted" / f"{e.addr('?WithEh@@YAHH@Z')[2:]}.json").read_text())
    kinds = {b["kind"] for b in record["bindings"]}
    check({"ehhandler", "funclet", "ehdata"} <= kinds, f"EH structures verified, got {kinds}")
    check(record["text_x"], "the EH function's .text$x range is recorded")
    scale = json.loads((e.root / "build/agent/accepted" / f"{e.addr('?Scale@@YAMPAUFoo@@@Z')[2:]}.json").read_text())
    check(any(b["kind"] == "literal" and b["name"] == "__real@40200000" for b in scale["bindings"]),
          "the float literal is checked by value")


def test_different_expression_rejected(base: Path) -> None:
    e = Env(base, "reorder")
    sym = "?Get@Foo@@QBEHXZ"
    path = e.candidate(sym, "int Foo::Get() const { return a * 3 + b + Helper(g_counter); }")
    proc = e.run("try.py", e.addr(sym), path)
    check(proc.returncode == 1 and "NO MATCH" in proc.stdout, "try.py should not match", proc)
    check("~ " in proc.stdout and "mov ecx, [esi+0x4]" in proc.stdout, "try.py should show the differing rows", proc)
    check("mismatch rows 2/" in proc.stdout, "two rows differ", proc)
    proc = e.run("accept.py", e.addr(sym), path)
    check(proc.returncode == 1 and "REJECTED" in proc.stdout, "accept.py should reject", proc)
    sw = "?Sw@@YAHHH@Z"  # same instructions in another order: the switch table must differ
    body = FUNCTIONS[sw].replace("case 4: return v << 2;", "case 4: return v / 3;#").replace(
        "case 5: return v / 3;", "case 5: return v << 2;").replace("#", "")
    proc = e.run("try.py", e.addr(sw), e.candidate(sw, body))
    check(proc.returncode == 1 and "switch tables" in proc.stdout, "a reordered switch should fail", proc)


def test_labelled_switch_table(base: Path) -> None:
    """delink labels the jump table after a function's code (jpt_..., storage class LABEL), and objdiff does
    not end a function at a label: the target must still end at its code, as the candidate does."""
    e = Env(base, "jpt")
    sw = "?Sw@@YAHHH@Z"
    table = e.target.addr(sw) + e.target.sizes[sw]
    for path in (e.root / "build" / "PC_20040610" / "obj" / "auto").glob("*.obj"):
        obj = coff.Coff.load(path)
        fn = next(s for s in obj.symbols if s.name == e.target.names[sw])
        path.write_bytes(obj.rewrite(add=[(f"jpt_{table:08X}", fn.value + e.target.sizes[sw], fn.section, 0,
                                           coff.IMAGE_SYM_CLASS_LABEL)]))
    proc = e.run("try.py", e.addr(sw), e.candidate(sw))
    check(proc.returncode == 0 and "MATCH" in proc.stdout, "a switch whose table delink labelled should match", proc)


def test_sidebyside(base: Path) -> None:
    """sidebyside.py: every row of an exact match lines up (named callee, float literal, switch), a
    different expression shows, a build error fails, and no attempt is spent."""
    e = Env(base, "sidebyside")
    for sym in ("?Get@Foo@@QBEHXZ", "?Scale@@YAMPAUFoo@@@Z", "?Sw@@YAHHH@Z"):
        proc = e.run("sidebyside.py", e.addr(sym), e.candidate(sym))
        check(proc.returncode == 0 and "\n0 differing rows," in proc.stdout, f"{sym} should line up", proc)
    sym = "?Get@Foo@@QBEHXZ"
    proc = e.run("sidebyside.py", e.addr(sym), e.candidate(sym, "int Foo::Get() const { return a * 3 + b + Helper(g_counter); }"))
    check(proc.returncode == 0 and "\n~ " in proc.stdout and "\n0 differing rows," not in proc.stdout,
          "a different expression should show", proc)
    proc = e.run("sidebyside.py", e.addr(sym), e.candidate(sym, "int Foo::Get() const { return nope; }"))
    check(proc.returncode != 0 and "BUILD FAILED" in proc.stderr, "a build error should fail", proc)
    check(not (e.root / "build/agent/attempts").exists(), "sidebyside.py records no attempt")


def test_wrong_callee_rejected(base: Path) -> None:
    sym, body = "?Get@Foo@@QBEHXZ", "int Foo::Get() const { return a + b * 3 + Other(g_counter); }"
    # 1. symbols.txt names the callee: the instruction bytes are identical, the callee is not.
    e = Env(base, "callee-named", named={"?Helper@@YAHH@Z"})
    proc = e.run("try.py", e.addr(sym), e.candidate(sym, body))
    check(proc.returncode == 1 and "r " in proc.stdout and "?Helper@@YAHH@Z" in proc.stdout,
          "a wrong named callee must not match", proc)
    check("bytes differ" not in proc.stdout, "only the reference differs", proc)
    proc = e.run("accept.py", e.addr(sym), e.candidate(sym, body))
    check(proc.returncode == 1, "accept.py must reject a wrong callee", proc)
    # 2. the callee is unnamed, but the candidate's callee is known elsewhere.
    e = Env(base, "callee-elsewhere", extra={"?Other@@YAHH@Z": 0x10A40000})
    proc = e.run("try.py", e.addr(sym), e.candidate(sym, body))
    check(proc.returncode == 1 and "symbols.txt puts at 0x10A40000" in proc.stdout,
          "a callee named at another address must not match", proc)
    # 3. one target callee, two candidate callees.
    e = Env(base, "callee-registry")
    twice = "?Twice@@YAHH@Z"
    proc = e.run("try.py", e.addr(twice), e.candidate(twice, "int Twice(int x) { return Helper(x) + Other(x + 1); }"))
    check(proc.returncode == 1 and "is used as both" in proc.stdout, "one address cannot be two functions", proc)
    # 4. an accepted function already bound the address to another name.
    proc = e.run("accept.py", e.addr(sym), e.candidate(sym))
    check(proc.returncode == 0, "the reference Get is accepted", proc)
    proc = e.run("try.py", e.addr(twice), e.candidate(twice, "int Twice(int x) { return Other(x) + Other(x + 1); }"))
    check(proc.returncode == 1 and "which accepted" in proc.stdout and "?Helper@@YAHH@Z" in proc.stdout,
          "the accepted binding must win", proc)
    # 5. EH: a wrong destructor in the unwind funclets.
    eh = "?WithEh@@YAHH@Z"
    extra = "struct Res2 { Res2(); ~Res2(); int n; };\n"
    proc = e.run("try.py", e.addr(eh), e.candidate(eh, "int WithEh(int a) { Res r1; Res2 r2; return Use(a + r1.n + "
                                                   "r2.n); }", extra=extra))
    check(proc.returncode == 1 and "unwind funclet" in proc.stdout, "wrong destructors must fail in the funclets",
          proc)


def test_self_call(base: Path) -> None:
    """A function's calls to itself carry no relocation in the split (delink resolves them in the unit)."""
    e = Env(base, "self-call")
    fib = "?Fib@@YAHH@Z"
    t_obj = coff.Coff.load(e.root / "build/PC_20040610/obj/auto" / f"text_{fixture.TEXT:08X}.obj")
    fn = next(s for s in t_obj.symbols if s.name == f"FUN_{e.target.addr(fib):08x}")
    sec = t_obj.section(fn.section)
    start = fn.value
    calls = [r for _, r in t_obj.relocations(sec.index, start, start + e.target.sizes[fib])
             if t_obj.slots[r.symbol] is fn]
    check(not calls, "the fixture drops the self-call relocations, as delink does")
    proc = e.run("try.py", e.addr(fib), e.candidate(fib))
    check(proc.returncode == 0 and "MATCH" in proc.stdout, "a recursive function matches", proc)
    proc = e.run("accept.py", e.addr(fib), e.candidate(fib))
    check(proc.returncode == 0 and "ACCEPTED" in proc.stdout, "and is accepted", proc)
    other = "int Fib(int n) { return n < 2 ? n : Helper(n - 1) + Fib(n - 2); }"
    proc = e.run("try.py", e.addr(fib), e.candidate(fib, other))
    check(proc.returncode == 1 and "where the target calls itself" in proc.stdout,
          "a call elsewhere where the target calls itself fails", proc)


def test_class_method_names(base: Path) -> None:
    """symbols.txt names written as Ghidra would (`Foo::Get`, `Helper`) pair with decorated names."""
    get = "?Get@Foo@@QBEHXZ"
    e = Env(base, "class-names", aliases={get: "Foo::Get", "?Helper@@YAHH@Z": "Helper"})
    check(e.addr(get) and "Foo::Get = " in (e.root / "config/PC_20040610/symbols.txt").read_text(), "fixture")
    proc = e.run("try.py", "Foo::Get", e.candidate(get))
    check(proc.returncode == 0 and "MATCH" in proc.stdout and "= ?Helper@@YAHH@Z" not in proc.stdout,
          "the candidate is found by its demangled name and Helper binds by name", proc)
    body = "int Foo::Get() const { return a + b * 3 + Other(g_counter); }"
    proc = e.run("try.py", "Foo::Get", e.candidate(get, body))
    check(proc.returncode == 1 and "(Helper)" in proc.stdout, "a callee named Helper is not Other", proc)
    proc = e.run("accept.py", "Foo::Get", e.candidate(get))
    record = json.loads((e.root / "build/agent/accepted" / f"{e.addr(get)[2:]}.json").read_text())
    check(proc.returncode == 0 and any(b["status"] == "compatible" for b in record["bindings"]),
          "the Helper binding is recorded as compatible", proc)
    proc = e.run("integrate.py")
    names = {s.name for s in symbolslib.load(e.root / "config/PC_20040610/symbols.txt")}
    check(proc.returncode == 0 and {get, "?Helper@@YAHH@Z"} <= names and "Foo::Get" not in names,
          "integration replaces the undecorated names with the decorated ones", proc)


def test_qualified_names(base: Path) -> None:
    """Demangled names reduce to what symbols.txt writes, for functions and for variables."""
    from common import qualified_name
    for name, demangled, want in (
        ("?execIsA@UObject@@QAEXAAVFFrame@@QAX@Z",
         "public: void __thiscall UObject::execIsA(class FFrame &,void * const)", "UObject::execIsA"),
        ("?GLog@@3PAVFOutputDevice@@A", "class FOutputDevice * GLog", "GLog"),
        ("?GNatives@@3PAP8UObject@@AEXAAVFFrame@@QAX@ZA",
         "void (__thiscall UObject::** GNatives)(class FFrame &,void * const)", "GNatives"),
        ("?GCasts@@3PAP8UObject@@AEXAAVFFrame@@QAX@ZA",
         "void (__thiscall UObject::* GCasts[256])(class FFrame &,void * const)", "GCasts"),
        ("_strlen", "", "strlen"),
    ):
        got = qualified_name(name, demangled)
        check(got == want, f"{name} reduces to {got}, not {want}")


def test_wrong_literal_rejected(base: Path) -> None:
    e = Env(base, "literal")
    scale = "?Scale@@YAMPAUFoo@@@Z"
    proc = e.run("try.py", e.addr(scale), e.candidate(scale, "float Scale(Foo* f) { return f->c * 3.5f; }"))
    check(proc.returncode == 1 and "literal __real@40600000 (0x10E50000): bytes differ" in proc.stdout,
          "a wrong float must fail", proc)
    seven = "?Seven@@YAHH@Z"
    proc = e.run("try.py", e.addr(seven), e.candidate(seven, "int Seven(int x) { return x * 7 + 101; }"))
    check(proc.returncode == 1 and "NO MATCH" in proc.stdout, "a wrong integer must fail", proc)
    name = "?Name@@YAPBDXZ"
    proc = e.run("try.py", e.addr(name), e.candidate(name, 'const char* Name() { return "hello wurld"; }'))
    check(proc.returncode == 1 and "literal ??_C@" in proc.stdout, "a wrong string must fail", proc)
    # For the record: objdiff's own data ruler calls the wrong float equal (both constants sit at
    # offset 0 of their COMDAT sections), which is why the harness does not rely on it.
    p = Project()
    work = e.root / "objdiff-ruler"
    a = fixture.compile_reference(p, DECLS + FUNCTIONS[scale], work, "a")
    b = fixture.compile_reference(p, DECLS + "float Scale(Foo* f) { return f->c * 3.5f; }", work, "b")
    out = subprocess.run([str(p.objdiff), "diff", "-1", str(a), "-2", str(b), "-o", "-", "-c",
                          "functionRelocDiffs=data_value", scale], capture_output=True, text=True)
    pct = next((s.get("match_percent") for s in json.loads(out.stdout)["left"]["symbols"] if s["name"] == scale),
               None) if out.returncode == 0 else None
    print(f"    note: objdiff functionRelocDiffs=data_value scores the wrong float at {pct}%")


def test_guessed_names(base: Path) -> None:
    """A caller's guess at a function's signature (a decorated name on its FUN_ placeholder) is not a real
    name: the function's own match on the same placeholder replaces it."""
    from common import guessed_name
    check(guessed_name("?FUN_10b760b0@@YAXXZ", 0x10B760B0) and guessed_name("?FUN_10B760B0@C@@QAEXH@Z", 0x10B760B0),
          "a decorated name on the address's own placeholder is a guess")
    check(not guessed_name("?Foo@C@@QAEXXZ", 0x10B760B0) and not guessed_name("?FUN_10b760c0@@YAXXZ", 0x10B760B0)
          and not guessed_name("FUN_10b760b0", 0x10B760B0), "a real name, another address's, a bare placeholder")


def test_implicit_needs_emitter(base: Path) -> None:
    """An implicit destructor's marker on a constructor's definition is a stand-in unless --with names the
    game's function that emits it: accept.py tells the two apart."""
    import accept
    stand_in = "struct C { C(); int n; };\n// FUNCTION: 0x10901000\nC::C()\n{\n}\n"
    check(not accept.defines(stand_in, "??1C@@UAE@XZ"), "a constructor's definition does not define ~C")
    check(accept.defines("// FUNCTION: 0x10901000\nC::~C()\n{\n}\n", "??1C@@UAE@XZ")
          and accept.defines("// FUNCTION: 0x10901000\nC::C(int A)\n    : n(A)\n{\n}\n", "??0C@@QAE@H@Z")
          and accept.defines("// FUNCTION: 0x10901000\nint F()\n{\n    return 0;\n}\n", "?F@@YAHXZ"),
          "a destructor, a constructor and any other function define themselves")


def test_lint(base: Path) -> None:
    e = Env(base, "lint")
    sym = "?Seven@@YAHH@Z"
    for body, rule in (("int Seven(int x) { __asm { nop } return x * 7 + 100; }", "[asm]"),
                       ("int Seven(int x) { if (x) goto done; done: return x * 7 + 100; }", "[goto]"),
                       ("int Seven(int x) { return *(int*)((char*)&x + 0) * 7 + 100; }", "[offset-cast]"),
                       ("int Seven(int x) { return x * 7 + *(int*)0x10F00000; }", "[address]")):
        proc = e.run("accept.py", e.addr(sym), e.candidate(sym, body))
        check(proc.returncode == 1 and rule in proc.stdout, f"lint should reject {rule}", proc)
    proc = e.run("accept.py", e.addr(sym), e.candidate(sym, marker=False))
    check(proc.returncode == 1 and "[marker]" in proc.stdout, "the FUNCTION line is required", proc)


def test_duplicates_and_cap(base: Path) -> None:
    e = Env(base, "ledger")
    sym = "?Seven@@YAHH@Z"
    path = e.candidate(sym, "int Seven(int x) { return x * 7 + 99; }")
    first = e.run("try.py", e.addr(sym), path)
    again = e.run("try.py", e.addr(sym), path)
    check(first.returncode == 1 and again.returncode == 3 and "byte-identical" in again.stdout,
          "an identical resubmission is refused", again)
    for i in range(2, PATIENCE + 2):
        proc = e.run("try.py", e.addr(sym), e.candidate(sym, f"int Seven(int x) {{ return x * 7 + {99 - i}; }}"))
        check(f"ATTEMPT {i}/12" in proc.stdout, f"attempt {i} is counted", proc)
    proc = e.run("try.py", e.addr(sym), e.candidate(sym, "int Seven(int x) { return x * 7 + 50; }"))
    check(proc.returncode == 3 and f"no new best in the last {PATIENCE} attempts" in proc.stdout,
          f"{PATIENCE} attempts in a row with no new best stop the claim", proc)
    for i in range(PATIENCE + 2, 13):  # the lead may lift the patience; the cap still holds
        proc = e.run("try.py", e.addr(sym), e.candidate(sym, f"int Seven(int x) {{ return x * 7 + {99 - i}; }}"),
                     "--patience", "0")
        check(f"ATTEMPT {i}/12" in proc.stdout, f"attempt {i} is counted", proc)
    proc = e.run("try.py", e.addr(sym), e.candidate(sym), "--patience", "0")
    check(proc.returncode == 3 and "cap reached" in proc.stdout, "the 13th attempt is refused", proc)
    proc = e.run("accept.py", "defer", e.addr(sym), "register allocation differs", "--needs", "nothing")
    record = json.loads(proc.stdout)
    check(proc.returncode == 0 and record["best"]["attempt"] and record["attempts"] == 12,
          "defer records the best of 12 attempts", proc)
    proc = e.run("next.py", "list", "--all-regions", "--limit", "50")
    check(e.addr(sym) not in proc.stdout, "a deferred function leaves the queue", proc)


def test_claims_concurrency(base: Path) -> None:
    e = Env(base, "claims")
    queue = json.loads(e.run("next.py", "list", "--all-regions", "--limit", "1000").stdout)

    def race(workers: int, count: int) -> list:
        procs = [subprocess.Popen([sys.executable, str(HERE / "next.py"), "claim", "--all-regions", "--count",
                                   str(count)], env=dict(e.env, T3_AGENT_ID=f"w{i:02d}"), stdout=subprocess.PIPE,
                                  text=True, cwd=ROOT) for i in range(workers)]
        claimed = []
        for proc in procs:
            out, _ = proc.communicate(timeout=300)
            claimed += [c["addr"] for c in json.loads(out)["claimed"]]
        check(len(claimed) == len(set(claimed)), f"no function claimed twice: {sorted(claimed)}")
        check(len(claimed) == min(workers * count, len(queue)), f"{len(claimed)} claims, {len(queue)} queued")
        return claimed

    claimed = race(12, 3)
    # A claim held by another worker blocks try.py.
    addr = claimed[0]
    holder = next(c for c in json.loads(e.run("next.py", "status").stdout)["claims"] if c["addr"] == addr)["agent"]
    proc = e.run("try.py", addr, e.candidate("?Seven@@YAHH@Z"), agent="intruder")
    check(proc.returncode == 3 and f"claimed by {holder}" in proc.stdout, "another worker's claim is respected", proc)
    # Expired claims are taken over, again by exactly one worker each.
    e.run("next.py", "release", "--all")
    e.run("next.py", "claim", "--all-regions", "--count", "1000", "--ttl", "0", agent="old")
    time.sleep(0.05)
    race(12, 3)


def test_integrate(base: Path) -> None:
    e = Env(base, "integrate")
    for sym in ("?Get@Foo@@QBEHXZ", "?WithEh@@YAHH@Z", "?Sw@@YAHHH@Z", "?Scale@@YAMPAUFoo@@@Z", "?Twice@@YAHH@Z"):
        proc = e.run("accept.py", e.addr(sym), e.candidate(sym))
        check(proc.returncode == 0, f"accept {sym}", proc)
    splits_before = (e.root / "config/PC_20040610/splits.txt").read_text()
    proc = e.run("integrate.py", "--dry-run")
    check(proc.returncode == 0 and "dry run" in proc.stdout, "integrate --dry-run", proc)
    check((e.root / "config/PC_20040610/splits.txt").read_text() == splits_before, "a dry run writes nothing")
    proc = e.run("integrate.py")
    check(proc.returncode == 0 and "written" in proc.stdout, "integrate writes the units", proc)
    splits = splitslib.load(e.root / "config/PC_20040610/splits.txt")
    functions = [s for s in symbolslib.load(e.root / "config/PC_20040610/symbols.txt") if s.is_function and s.size]
    units = splitslib.plan(splits, functions, Project().chunk_size, breaks=Project().breaks())  # raises if invalid
    by_source = {u.source: u for u in splits}
    free = {s for s in by_source if s.startswith("Game/Unsorted_")}
    check(free and set(by_source) == {"Game/Foo.cpp"} | free,
          f"units by class, free functions by auto unit: {sorted(by_source)}")
    check(any(a >= fixture.TEXT_X for s in free for a, _ in by_source[s].text),
          "the EH funclets' .text$x range is declared")
    check(len(units) > len(splits), "auto units still cover the rest")
    names = {s.name for s in symbolslib.load(e.root / "config/PC_20040610/symbols.txt")}
    check({"?Get@Foo@@QBEHXZ", "?Helper@@YAHH@Z", "__ehhandler$?WithEh@@YAHH@Z", "__real@40200000"} <= names,
          "names are applied to symbols.txt")
    for unit in by_source:
        src = e.root / "src" / unit
        check(src.is_file() and "// FUNCTION: 0x" in src.read_text(), f"{unit} is written")
    proc = e.run("integrate.py")
    check("nothing to integrate" in proc.stdout, "a second run has nothing to do", proc)
    status = json.loads(e.run("next.py", "status").stdout)
    check(status["integrated"] == 5, f"src/ markers count as integrated: {status}")


def test_integrate_skips_excluded(base: Path) -> None:
    """A function the lead excluded after a worker accepted it (library code, say) is not integrated."""
    e = Env(base, "integrate-excluded")
    for sym in ("?Seven@@YAHH@Z", "?Twice@@YAHH@Z"):
        proc = e.run("accept.py", e.addr(sym), e.candidate(sym))
        check(proc.returncode == 0, f"accept {sym}", proc)
    (e.root / "build/agent/excluded.json").write_text(json.dumps({e.addr("?Twice@@YAHH@Z"): "library: an STL member"}))
    proc = e.run("integrate.py")
    check(proc.returncode == 0 and "is excluded" in proc.stdout, "integrate says why it skips it", proc)
    status = json.loads(e.run("next.py", "status").stdout)
    check(status["integrated"] == 1, f"only the other function is integrated: {status}")


def test_integrate_generated_follows_emitter(base: Path) -> None:
    """A deleting destructor accepted with the destructor whose unit emits it (--with) is integrated there,
    though the queue excludes it: the exclusion keeps workers from matching it by hand."""
    gen, body = "struct Gen { virtual ~Gen(); int n; };\n", "Gen::~Gen() { Helper(n); }"
    e = Env(base, "integrate-generated", reference=REFERENCE + gen + body + "\n")
    dtor, deleting = "??1Gen@@UAE@XZ", "??_GGen@@UAEPAXI@Z"
    proc = e.run("accept.py", e.addr(dtor), e.candidate(dtor, body, extra=gen))
    check(proc.returncode == 0, "accept the destructor", proc)
    proc = e.run("accept.py", e.addr(deleting), e.candidate(deleting, body, extra=gen), "--symbol", deleting,
                 "--with", e.addr(dtor))
    check(proc.returncode == 0, "accept the deleting destructor with it", proc)
    (e.root / "build/agent/excluded.json").write_text(json.dumps({e.addr(deleting): "compiler-generated"}))
    proc = e.run("integrate.py")
    check(proc.returncode == 0 and "is excluded" not in proc.stdout, "nothing is skipped as excluded", proc)
    status = json.loads(e.run("next.py", "status").stdout)
    check(status["integrated"] == 2, f"both are integrated, in one run: {status}")
    text = (e.root / "src/Game/Gen.cpp").read_text()
    check(f"// FUNCTION: {e.addr(deleting)} {deleting}" in text, f"the deleting destructor's marker: {text}")


def test_integrate_keeps_distinct_includes(base: Path) -> None:
    """Declarations that differ only inside a string literal, such as two #include lines, are both kept."""
    import integrate
    decls = integrate.items('#include "A.h"\n#include "B.h"\n// again\n#include "A.h"\n'
                            'const char* F() { return "x"; }\nconst char* F() { return "x"; }\n'
                            'const char* G() { return "y"; }\n')
    text = integrate.compose("Game/X.cpp", decls, {})
    check(text.count('#include "A.h"') == 1 and '#include "B.h"' in text, f"both includes, once each: {text}")
    check(text.count('return "x"') == 1 and 'return "y"' in text, f"literals tell items apart: {text}")


def test_integrate_drops_what_breaks(base: Path) -> None:
    """A function that matches alone but not in its unit is left out of it."""
    e = Env(base, "integrate-context")
    callee, caller, get = "?Callee@@YAHH@Z", "?Caller@@YAHH@Z", "?Get@Foo@@QBEHXZ"
    for sym in (callee, caller, get):
        proc = e.run("accept.py", e.addr(sym), e.candidate(sym))
        check(proc.returncode == 0, f"accept {sym} on its own", proc)
    # In one unit, Callee's body is visible to Caller, which then inlines it.
    proc = e.run("integrate.py", "--unit", "Game/Mixed.cpp", "--category", "game")
    check(proc.returncode == 0 and f"left out {e.addr(caller)}" in proc.stdout, "Caller no longer matches", proc)
    text = (e.root / "src/Game/Mixed.cpp").read_text()
    check(text.count("// FUNCTION:") == 2 and e.addr(caller) not in text, "Callee and Get are integrated", proc)
    check(text.count("struct Foo {") == 1 and text.count("int Helper(int);") == 1, "declarations are deduplicated")
    unit = next(u for u in splitslib.load(e.root / "config/PC_20040610/splits.txt") if u.source == "Game/Mixed.cpp")
    caller_addr = e.target.addr(caller)
    check(not any(a <= caller_addr < b for a, b in unit.text), "the dropped function's range is not declared")

    e = Env(base, "integrate-breaks")  # a new function that breaks one already in the unit
    for sym in (callee, caller):
        proc = e.run("accept.py", e.addr(sym), e.candidate(sym))
        check(proc.returncode == 0, f"accept {sym} on its own", proc)
    proc = e.run("integrate.py", e.addr(caller), "--unit", "Game/Pair.cpp", "--category", "game")
    check(proc.returncode == 0 and (e.root / "src/Game/Pair.cpp").is_file(), "Caller alone in its unit", proc)
    proc = e.run("integrate.py", e.addr(callee), "--unit", "Game/Pair.cpp", "--category", "game")
    check(f"left out {e.addr(callee)} from Game/Pair.cpp: its unit breaks" in proc.stdout,
          "a function that would break its unit's functions is said to be left out", proc)


def test_context_and_queue(base: Path) -> None:
    e = Env(base, "context")
    e.run("accept.py", e.addr("?Get@Foo@@QBEHXZ"), e.candidate("?Get@Foo@@QBEHXZ"))
    proc = e.run("context.py", e.addr("?WithEh@@YAHH@Z"), "--json")
    pk = json.loads(proc.stdout)
    check({"function", "target", "references"} <= set(pk), f"context sections: {sorted(pk)}", proc)
    check(any(not r["named"] for r in pk["references"]), "unnamed references are flagged")
    check(any("tags: eh" in c for c in pk.get("cheatsheet", [])), "EH cheat-sheet entries for an EH function")
    pk = json.loads(e.run("context.py", e.addr("?Twice@@YAHH@Z"), "--json").stdout)
    check(any("?Get@Foo@@QBEHXZ" == s["symbol"] for s in pk.get("similar", [])), "similar accepted functions")
    check(any(r.get("proposed", "").startswith("?Helper@@YAHH@Z") for r in pk["references"]),
          "names proposed by accepted functions are shown")
    queue = json.loads(e.run("next.py", "list", "--all-regions", "--limit", "100").stdout)
    order = [q["difficulty"] / q.get("family", 1) for q in queue]
    check(order == sorted(order), "the queue is easy first, a family's member by its share of the family's work")
    check(e.addr("?Get@Foo@@QBEHXZ") not in [q["addr"] for q in queue], "accepted functions leave the queue")
    # A caller binds its callee's name; the callee's packet shows it.
    e.run("accept.py", e.addr("?Caller@@YAHH@Z"), e.candidate("?Caller@@YAHH@Z"))
    pk = json.loads(e.run("context.py", e.addr("?Callee@@YAHH@Z"), "--json").stdout)
    check([b["name"] for b in pk.get("bound", [])] == ["?Callee@@YAHH@Z"],
          f"the callers' name is shown: {pk.get('bound')}")
    # A second pass sees the best earlier attempt.
    seven = "?Seven@@YAHH@Z"
    e.run("try.py", e.addr(seven), e.candidate(seven, "int Seven(int x) { return x * 7 + 99; }"), agent="w1")
    e.run("accept.py", "defer", e.addr(seven), "tiebreak: constant", agent="w1")
    pk = json.loads(e.run("context.py", e.addr(seven), "--json").stdout)
    check("x * 7 + 99" in pk.get("history", {}).get("best_source", ""), "the best earlier attempt is shown")
    check(pk["history"].get("deferred", {}).get("blocker") == "tiebreak: constant", "with its blocker")


def test_base_slot(base: Path) -> None:
    """A virtual method's packet names what the super class holds at its slot."""
    import types
    import context as ctx
    cls = lambda name, sup, vt: types.SimpleNamespace(name=name, super=sup, vtable=vt)  # noqa: E731
    classes = {"UObject": cls("UObject", "", 0x10E00000), "AActor": cls("AActor", "UObject", 0x10E10000),
               "AThing": cls("AThing", "AActor", 0x10E20000)}
    serialize = types.SimpleNamespace(name="?Serialize@UObject@@UAEXAAVFArchive@@@Z")
    p = types.SimpleNamespace(classes=lambda: classes, accepted=lambda: {}, by_addr={0x10A00010: serialize})
    functions = {"10A00010": [[0x10E00000, 2]], "10A00020": [[0x10E00000, 3]],
                 "10B00010": [[0x10E20000, 2]], "10B00020": [[0x10E20000, 9]]}
    found = ctx.base_slot(p, "AThing", 2, functions)  # AActor's table is not indexed: UObject's is next
    check(found["base"]["class"] == "UObject" and found["base"]["name"].startswith("?Serialize@UObject"),
          f"the override's base method is named: {found}")
    check(ctx.base_slot(p, "AThing", 9, functions)["base"].get("new"), "a slot past the super's table is new")


def test_claim_by_class(base: Path) -> None:
    """--by-class: after the queue head, its class's functions (by name, else by vtable), else its neighbours."""
    import next as nextlib
    head = {"addr": "0x10000010", "symbol": "?A@C1@@QAEXXZ", "unit": "u"}
    rest = [{"addr": "0x10000100", "symbol": "FUN_10000100", "unit": "u"},
            {"addr": "0x10000020", "symbol": "?B@C2@@QAEXXZ", "unit": "u"},
            {"addr": "0x10000300", "symbol": "C1::D", "unit": "v"},
            {"addr": "0x10000400", "symbol": "FUN_10000400", "unit": "u"},
            {"addr": "0x10000500", "symbol": "?Free@ns@@YAXXZ", "unit": "u"}]
    check(nextlib.by_class(rest, head, {})[0]["addr"] == "0x10000300", "the class's other method comes next")
    check(nextlib.owner(rest[4], {}) == "", "a namespace is not a class")
    slots = {"10000100": [[0x10E00000, 2]], "10000400": [[0x10E00000, 3]]}
    ordered = nextlib.by_class(rest[1:], rest[0], slots)
    check(ordered[0]["addr"] == "0x10000400", f"a function of the same vtable comes next: {ordered}")
    loose = {"addr": "0x10000110", "symbol": "FUN_10000110", "unit": "u"}
    check(nextlib.by_class(rest, loose, {})[0]["addr"] == "0x10000100", "else the nearest neighbour in the unit")
    e = Env(base, "by-class")
    proc = e.run("next.py", "claim", "--all-regions", "--by-class", "--count", "3")
    out = json.loads(proc.stdout)
    addrs = [int(c["addr"], 16) for c in out["claimed"]]
    check(proc.returncode == 0 and len(addrs) == 3, "claim --by-class takes its count", proc)
    left = json.loads(e.run("next.py", "list", "--all-regions", "--limit", "100").stdout)
    check(abs(addrs[1] - addrs[0]) <= max(abs(int(q["addr"], 16) - addrs[0]) for q in left),
          "the second claim is a neighbour of the first")


def test_families(base: Path) -> None:
    """Two functions equal but for their callee: the queue serves one, and once it is accepted, clusters.py
    stamp matches the other from its source with no model; a named callee is not rewritten."""
    a, b, helper, other = "?TwinA@@YAHH@Z", "?TwinB@@YAHH@Z", "?Helper@@YAHH@Z", "?Other@@YAHH@Z"

    def template(e: Env) -> Path:
        h, own = e.target.addr(helper), e.target.addr(a)
        callee = "Helper" if helper in e.target.names.values() else f"FUN_{h:08x}"
        path = e.scratch / "twin-a.cpp"
        path.write_text(f"int {callee}(int);\n// FUNCTION: {e.addr(a)}\n"
                        f"int FUN_{own:08x}(int x) {{ return {callee}(x) * 3 + 1; }}\n", encoding="utf-8")
        return path

    e = Env(base, "families")
    queue = [q["addr"] for q in json.loads(e.run("next.py", "list", "--all-regions", "--limit", "100").stdout)]
    check((e.addr(a) in queue) != (e.addr(b) in queue), f"the queue serves one member of the family: {queue}")
    shown = json.loads(e.run("clusters.py", "show", e.addr(b), agent="").stdout)
    check({m["addr"] for m in shown["members"]} == {e.addr(a), e.addr(b)}, "clusters.py show lists the family")
    proc = e.run("accept.py", e.addr(a), template(e))
    check(proc.returncode == 0 and "ACCEPTED" in proc.stdout, "the template is accepted", proc)
    queue = [q["addr"] for q in json.loads(e.run("next.py", "list", "--all-regions", "--limit", "100").stdout)]
    check(e.addr(b) not in queue, "an open member waits for the stamp once another is accepted")
    proc = e.run("clusters.py", "stamp", agent="worker")
    check(proc.returncode != 0, "stamp is the lead's", proc)
    proc = e.run("clusters.py", "stamp", agent="")
    out = json.loads(proc.stdout)
    check([s["addr"] for s in out["stamped"]] == [e.addr(b)], "the other member is stamped", proc)
    record = json.loads((e.root / "build/agent/accepted" / f"{e.addr(b)[2:]}.json").read_text())
    check(record["agent"] == "stamp" and record["symbol"] == f"?FUN_{e.target.addr(b):08x}@@YAHH@Z"
          and any(int(x["addr"], 16) == e.target.addr(other) for x in record["bindings"]),
          f"through the gate, under its own name and with its own callee: {record}")

    e = Env(base, "families-excluded")  # the lead excluded the other member (library code, say)
    (e.root / "build/agent").mkdir(parents=True, exist_ok=True)
    (e.root / "build/agent/excluded.json").write_text(json.dumps({e.addr(b): "library: an STL member"}))
    proc = e.run("accept.py", e.addr(a), template(e))
    check(proc.returncode == 0, "the template is accepted", proc)
    out = json.loads(e.run("clusters.py", "stamp", agent="").stdout)
    check(not out["stamped"] and not out["failed"], f"an excluded member is not stamped: {out}")
    listed = json.loads(e.run("clusters.py", "list", "--min", "1", agent="").stdout)
    check(listed["open_members"] == 0, f"nor counted as open: {listed}")

    e = Env(base, "families-named", named={helper})
    proc = e.run("accept.py", e.addr(a), template(e))
    check(proc.returncode == 0, "the template with a named callee is accepted", proc)
    out = json.loads(e.run("clusters.py", "stamp", agent="").stdout)
    check(not out["stamped"] and out["failed"] and "named" in out["failed"][0]["why"],
          f"a named callee is not rewritten: {out}")
    queue = [q["addr"] for q in json.loads(e.run("next.py", "list", "--all-regions", "--limit", "100").stdout)]
    check(e.addr(b) in queue, "a member the stamp failed for goes back to the queue")

    e = Env(base, "families-class")  # a member of a class nothing gives the other function
    h, own = e.target.addr(helper), e.target.addr(a)
    path = e.scratch / "twin-a-static.cpp"
    path.write_text(f"int FUN_{h:08x}(int);\nstruct Holder {{ static int FUN_{own:08x}(int x); }};\n"
                    f"// FUNCTION: {e.addr(a)}\n"
                    f"int Holder::FUN_{own:08x}(int x) {{ return FUN_{h:08x}(x) * 3 + 1; }}\n", encoding="utf-8")
    proc = e.run("accept.py", e.addr(a), path)
    check(proc.returncode == 0, "a static member template is accepted", proc)
    out = json.loads(e.run("clusters.py", "stamp", agent="").stdout)
    check(not out["stamped"] and "Holder" in out["failed"][0]["why"], f"its class is not guessed: {out}")

    eha, ehb = "?EhTwinA@@YAHH@Z", "?EhTwinB@@YAHH@Z"
    e = Env(base, "families-eh", reference=REFERENCE + EH_TWINS)  # each member pushes its own EH handler
    h, own = e.target.addr(helper), e.target.addr(eha)
    path = e.scratch / "eh-twin-a.cpp"
    path.write_text(f"struct Res {{ Res(); ~Res(); int n; }};\nint FUN_{h:08x}(int);\n// FUNCTION: {e.addr(eha)}\n"
                    f"int FUN_{own:08x}(int a) {{ Res r; return FUN_{h:08x}(a + r.n); }}\n", encoding="utf-8")
    proc = e.run("accept.py", e.addr(eha), path)
    check(proc.returncode == 0 and "ACCEPTED" in proc.stdout, "a template with an EH handler is accepted", proc)
    out = json.loads(e.run("clusters.py", "stamp", agent="").stdout)
    check([s["addr"] for s in out["stamped"]] == [e.addr(ehb)],
          f"the other member is stamped: its handler is its own, not a reference to rewrite: {out}")


def test_stamp_derive(base: Path) -> None:
    """clusters.derive: a callee the template's source names through its class (`~Class_10E4A538`, bound to a
    FUN_) maps that class to the other function's, from its callee's name or a same-shape callee's references."""
    import clusters
    dtor = "??1Class_10E4A538@@QAE@XZ"
    m: dict = {}
    check(clusters.derive({}, 1, 2, dtor, "??1Class_10E55E78@@QAE@XZ", m) == "" and m == {0x10E4A538: 0x10E55E78},
          f"from the other callee's name: {m}")
    m = {}
    check(clusters.derive({}, 1, 2, dtor, "?Get@Class_10E55E78@@QAEHXZ", m) != "" and not m,
          f"not from a name of another shape: {m}")
    idx = {"00000001": {"key": "k", "refs": [[8, 0x10E4A538, "DAT_10e4a538"]]},
           "00000002": {"key": "k", "refs": [[8, 0x10E55E78, "DAT_10e55e78"]]},
           "00000003": {"key": "j", "refs": [[8, 0x10E66000, "DAT_10e66000"]]}}
    m = {}
    check(clusters.derive(idx, 1, 2, dtor, "FUN_00000002", m) == "" and m == {0x10E4A538: 0x10E55E78},
          f"from the references of a callee of the same shape: {m}")
    m = {}
    check("shape" in clusters.derive(idx, 1, 3, dtor, "FUN_00000003", m) and not m,
          "not from a callee of another shape")
    m = {0x10E4A538: 0x10E77000}
    check("two" in clusters.derive({}, 1, 2, dtor, "??1Class_10E55E78@@QAE@XZ", m),
          "nor onto an address already mapped elsewhere")

    known = {"AAIModel", "AInfo", "UObject", "UClass", "UStruct"}
    check(clusters.classes_in("??_7AAIModel@@6B@", known) == ["AAIModel"]
          and clusters.classes_in("?F@AAIModel@@QAEXXZ", known) == ["AAIModel"], "a vtable's and a method's class")
    names: dict = {}
    check(clusters.rename_classes("??_7AAIModel@@6B@", "??_7AInfo@@6B@", "class AAIModel {};", known, names) == ""
          and names == {"AAIModel": "AInfo"}, f"one native class's name for another's: {names}")
    names = {}
    check(clusters.rename_classes("?IsA@UObject@@QBEHPAVUClass@@@Z", "?IsA@UObject@@QBEHPAVUStruct@@@Z",
                                  "UClass* Class;", known, names) != "" and not names,
          "not a class glued to a parameter's type code")
    names = {}
    check(clusters.rename_classes("??_7AAIModel@@6B@", "??_7AInfo@@6B@", "class Other {};", known, names) != "",
          "nor a class the template does not spell")
    names = {"AAIModel": "AInfo"}
    check(clusters.rename_words("class AAIModel : public AAIModelBase { ~AAIModel(); };", names)
          == "class AInfo : public AAIModelBase { ~AInfo(); };", "renamed as whole words only")


def test_vtables(base: Path) -> None:
    """vtables.py names each slot function after the class whose table first holds it: inherited slots
    are left to the super, a class whose own table is not known takes what its subclasses agree on, and
    a class's own table holds its own deleting destructor (slot 2) unless the linker folded it."""
    import vtables
    supers = {"UObject": "", "AActor": "UObject", "ALink": "UObject", "AKid1": "ALink", "AKid2": "ALink",
              "AKid3": "ALink", "APawn": "AActor"}
    tables = {"UObject": [1, 2, 3], "AActor": [1, 20, 3], "ALink": None, "AKid1": [1, 40, 30], "AKid2": [1, 41, 31],
              "AKid3": [1, 2, 3], "APawn": [1, 20, 300]}
    got = vtables.attribute(supers, tables, slots=3)
    check(got == [(1, "UObject", 0), (2, "UObject", 1), (3, "UObject", 2), (20, "AActor", 1), (30, "AKid1", 2),
                  (31, "AKid2", 2), (300, "APawn", 2)],
          f"the root's slots, then each override; under an unknown table only a deleting destructor not folded "
          f"with an ancestor's: {got}")
    check(vtables.placeholder_name("??1Class_10E56A28@@QAE@XZ") and not vtables.placeholder_name("??1AActor@@UAE@XZ"),
          "a method of a class known by its address is a placeholder")
    check(vtables.slot_name("AActor", 2) == "??_GAActor@@UAEPAXI@Z"
          and vtables.slot_name("AActor", 6) == "?Modify@AActor@@UAEXXZ"
          and vtables.slot_name("AActor", 8) == "?Serialize@AActor@@UAEXAAVFArchive@@@Z"
          and vtables.slot_name("AActor", 15) == "?Unknown3C@AActor@@UAEXXZ"
          and vtables.slot_name("AActor", 19) == "?Register@AActor@@UAEXXZ", "slots named as Core.h declares them")
    check(vtables.slot_name("UObject", 18).endswith("PAV1@@Z") and vtables.slot_declaration("AActor", 2)
          == "virtual ~AActor();", "UObject's own signature back-references itself; slot 2 is the destructor")


def test_sweep(base: Path) -> None:
    """sweep.py with a glob: accepts a forgotten MATCH, parks out-of-scope deferrals, logs the batch."""
    e = Env(base, "sweep")
    seven, twice, fib = "?Seven@@YAHH@Z", "?Twice@@YAHH@Z", "?Fib@@YAHH@Z"
    proc = e.run("try.py", e.addr(seven), e.candidate(seven), agent="s9-a")
    check(proc.returncode == 0, "a MATCH left unaccepted", proc)
    e.run("try.py", e.addr(twice), e.candidate(twice, "int Twice(int x) { return Helper(x) + 1; }"), agent="s9-b")
    e.run("accept.py", "defer", e.addr(twice), "library: an STL member", agent="s9-b")
    e.run("accept.py", e.addr(fib), e.candidate(fib), agent="other")
    proc = e.run("sweep.py", "s9-*", "--transcripts", base / "no-transcripts", agent="")
    check(proc.returncode == 0 and "accepted for s9-a" in proc.stdout, "the forgotten MATCH is accepted", proc)
    excluded = json.loads((e.root / "build/agent/excluded.json").read_text())
    check(e.addr(twice) in excluded and "library" in excluded[e.addr(twice)], "a library deferral is parked", proc)
    check("matches by attempt: 1: 1" in proc.stdout and "deferrals by slug: library 1" in proc.stdout,
          "attempts and slugs are counted", proc)
    line = json.loads((e.root / "build/agent/swarms.jsonl").read_text().splitlines()[-1])
    check(line["matched"] == 1 and line["deferred"] == 1 and set(line["workers"]) == {"s9-a", "s9-b"},
          f"the batch is logged, without other workers: {line}")


def test_guard(base: Path) -> None:
    project = base / "guard-project"
    (project / "build" / "scratch").mkdir(parents=True)
    cases = [
        ("Write", {"file_path": "build/scratch/0x10901000/v1.cpp"}, 0),
        ("Write", {"file_path": "config/PC_20040610/symbols.txt"}, 2),
        ("Edit", {"file_path": str(project / "src/Game/Foo.cpp")}, 2),
        ("Write", {"file_path": "build/PC_20040610/obj/auto/text_10901000.obj"}, 2),
        ("Write", {"file_path": "build/agent/accepted/10901000.json"}, 2),
        ("Write", {"file_path": "build/scratch/../../configure.py"}, 2),
        ("Bash", {"command": "python tools/agent/try.py 0x10901000 build/scratch/v1.cpp"}, 0),
        ("Bash", {"command": "git stash"}, 2),
        ("Bash", {"command": "cd build && git checkout ."}, 2),
        ("Bash", {"command": "git commit --no-verify -m x"}, 2),
        ("Bash", {"command": "echo x >> include/Foo.h"}, 2),
        ("Bash", {"command": "sed -i s/a/b/ config/PC_20040610/splits.txt"}, 2),
        ("Bash", {"command": "python3 -c 'print(1)'"}, 2),
        ("Bash", {"command": "python tools/agent/sweep.py w1"}, 2),
        ("Bash", {"command": "python tools/agent/clusters.py stamp"}, 2),
        ("Bash", {"command": "python tools/agent/clusters.py show 0x10901000"}, 0),
        ("Bash", {"command": "python tools/agent/try.py 0x10901000 build/scratch/v1.cpp --patience 9"}, 2),
    ]
    for tool, data, expected in cases:
        event = json.dumps({"tool_name": tool, "tool_input": data, "cwd": str(project)})
        proc = subprocess.run([sys.executable, str(HERE / "hooks" / "guard.py")], input=event, text=True,
                              capture_output=True, env=dict(os.environ, CLAUDE_PROJECT_DIR=str(project)))
        check(proc.returncode == expected, f"guard: {tool} {data} -> {proc.returncode}, want {expected}", proc)
    settings = json.loads((HERE / "guard-settings.json").read_text())
    check("guard.py" in settings["hooks"]["PreToolUse"][0]["hooks"][0]["command"], "the settings run the guard")

    # The project settings run it for the whole session: it checks only the workers' calls.
    for agent_type, expected in ((None, 0), ("general-purpose", 0), ("t3-matcher", 2)):
        event = {"tool_name": "Write", "tool_input": {"file_path": "src/Game/Foo.cpp"}, "cwd": str(project)}
        if agent_type:
            event.update(agent_id="a1", agent_type=agent_type)
        proc = subprocess.run([sys.executable, str(HERE / "hooks" / "guard.py"), "--agent-types", "t3-matcher"],
                              input=json.dumps(event), text=True, capture_output=True,
                              env=dict(os.environ, CLAUDE_PROJECT_DIR=str(project)))
        check(proc.returncode == expected, f"guard --agent-types: {agent_type} -> {proc.returncode}, want {expected}",
              proc)
    project_settings = json.loads((ROOT / ".claude" / "settings.json").read_text())
    command = project_settings["hooks"]["PreToolUse"][0]["hooks"][0]["command"]
    check("guard.py" in command and "--agent-types t3-matcher" in command, "the project settings run the guard")
    if os.name != "nt":  # the hook's shell line finds a Python and blocks a worker's write
        event = json.dumps({"tool_name": "Write", "tool_input": {"file_path": "src/Game/Foo.cpp"},
                            "cwd": str(project), "agent_id": "a1", "agent_type": "t3-matcher"})
        proc = subprocess.run(["sh", "-c", command], input=event, text=True, capture_output=True,
                              env=dict(os.environ, CLAUDE_PROJECT_DIR=str(ROOT)))
        check(proc.returncode == 2 and "matching guard" in proc.stderr, "the hook command runs the guard", proc)


def test_wave_dry_run(base: Path) -> None:
    proc = subprocess.run([sys.executable, str(HERE / "wave.py"), "--workers", "2", "--dry-run"], capture_output=True,
                          text=True, cwd=ROOT, env=dict(os.environ, T3_AGENT_STATE=str(base / "wave-state")))
    check(proc.returncode == 0, "wave.py --dry-run", proc)
    for needle in ("worktree add --detach", "--model claude-sonnet-5", "--output-format json", "--settings",
                   "--append-system-prompt-file"):
        check(needle in proc.stdout, f"wave.py prints {needle}", proc)
    check("--bare" not in proc.stdout, "no --bare: it would disable the guard hooks", proc)
    check(not (base / "wave-state").exists(), "a dry run writes nothing")


def test_compile_command_matches_configure(base: Path) -> None:
    """The fallback compile command uses the same flags as configure.py's build.ninja rule."""
    if os.name == "nt" and not os.environ.get("MSVC71_RUNTIME"):
        print("    skipped: set MSVC71_RUNTIME (configure.py needs it on Windows)")
        return
    tmp = base / "configure-copy"
    (tmp / "tools").mkdir(parents=True)
    shutil.copy(ROOT / "configure.py", tmp)
    for name in ("categories.py", "splits.py", "symbols.py", "ninja_syntax.py", "cc.py"):
        shutil.copy(ROOT / "tools" / name, tmp / "tools")
    (tmp / "tools" / "agent").mkdir()
    shutil.copy(HERE / "coff.py", tmp / "tools" / "agent")  # cc.py's
    shutil.copytree(Env(base, "configure-fixture").root / "config", tmp / "config")
    proc = subprocess.run([sys.executable, "configure.py"], cwd=tmp, capture_output=True, text=True)
    check(proc.returncode == 0 and (tmp / "build.ninja").is_file(), "configure.py runs on the fixture", proc)
    env = dict(os.environ, T3_AGENT_MAIN=str(tmp))
    code = ("import sys, json; sys.path.insert(0, sys.argv[1]); import common; p = common.Project(); "
            "a = p.compile_command(p.main / 'x.cpp', p.main / 'x.obj', p.configure.CFLAGS)[0]; "
            "p._ninja_cc = lambda: None; b = p.compile_command(p.main / 'x.cpp', p.main / 'x.obj', "
            "p.configure.CFLAGS)[0]; print(json.dumps([a, b]))")
    out = subprocess.run([sys.executable, "-c", code, str(HERE)], env=env, capture_output=True, text=True)
    ninja, fallback = json.loads(out.stdout)
    check(isinstance(ninja, str), "build.ninja's rule is run as ninja would, as one command line")
    ninja = shlex.split(ninja, posix=os.name != "nt")

    def flags(argv):  # cl.exe options, not POSIX paths (the interpreter running cc.py)
        return [a for a in argv if a.startswith("/") and "/" not in a[1:] and not a.startswith(("/I", "/Fo"))]
    check(flags(ninja) == flags(fallback), f"flags differ:\n  {ninja}\n  {fallback}")
    check("/showIncludes" not in ninja, "no /showIncludes in the agent's compile")
    if os.name != "nt":  # and compile through the rule, with the toolchain where build.ninja expects it
        (tmp / "build").mkdir(exist_ok=True)
        for name in ("tools", "compilers"):
            (tmp / "build" / name).symlink_to(ROOT / "build" / name)
        src = tmp / "scratch dir" / "x.cpp"
        src.parent.mkdir()
        src.write_text(DECLS + FUNCTIONS["?Seven@@YAHH@Z"] + "\n", encoding="utf-8")
        code = ("import sys; sys.path.insert(0, sys.argv[1]); import common; from pathlib import Path; "
                "p = common.Project(); "
                "ok, log = p.compile(Path(sys.argv[2]), Path(sys.argv[3]), p.configure.CFLAGS); "
                "print(ok, log)")
        out = subprocess.run([sys.executable, "-c", code, str(HERE), str(src), str(tmp / "out dir" / "x.obj")],
                             env=env, capture_output=True, text=True)
        check(out.stdout.startswith("True") and (tmp / "out dir" / "x.obj").is_file(),
              "compiling through build.ninja's rule (paths with spaces)", out)


def test_categories_and_except_list(base: Path) -> None:
    """categories.txt gives units their progress category; the split relocates fs:[0] (tools/split.py)."""
    sys.path.insert(0, str(ROOT / "tools"))
    import categories as categorieslib
    import coff
    import split
    path = base / "categories.txt"
    categorieslib.save(path, [(0x1000, 0x2000, "game"), (0x2000, 0x2800, "engine")])
    index = categorieslib.Index(categorieslib.load(path))
    check(index.at(0x1800) == "game" and index.at(0x2000) == "engine" and index.at(0x2800) == "",
          "categories by address, nothing outside the ranges")
    check(index.boundaries() == [0x1000, 0x2000, 0x2800], "the boundaries auto units must not span")
    unit_categories = Project().configure.unit_categories
    check(unit_categories(splitslib.Unit(source="Game/X.cpp", text=[(0x2100, 0x2200)]), index) == ["engine"],
          "a unit takes the category of its range")
    check(unit_categories(splitslib.Unit(source="Game/Y.cpp", text=[(0x1100, 0x1200)]), index) == ["main"],
          "game code is the headline category")
    # mov eax, fs:[0]; push eax; mov fs:[0], esp; ret: two SEH chain accesses, as the exe holds them.
    code = bytes.fromhex("64a100000000" "50" "64892500000000" "c3")
    symtab = 20 + 40 + len(code)
    obj = (struct.pack("<HHIIIHH", 0x14C, 1, 0, symtab, 1, 0, 0)
           + struct.pack("<8sIIIIIIHHI", b".text", 0, 0, len(code), 60, 0, 0, 0, 0, 0x60000020)
           + code + struct.pack("<8sIhHBB", b".text", 0, 1, 0, 3, 0) + struct.pack("<I", 4))
    target = base / "seh.obj"
    target.write_bytes(obj)
    check(split.add_except_list(target) == 2, "both fs:[0] operands are relocated")
    c = coff.Coff.load(target)
    relocs = [(r.offset, c.slots[r.symbol].name, r.type) for r in c.section(1).relocations]
    check(relocs == [(2, "__except_list", 6), (10, "__except_list", 6)], f"relocations against __except_list: {relocs}")
    check(c.section(1).data == code, "the code itself is unchanged")
    check(split.add_except_list(target) == 0, "an operand that already has a relocation is left alone")


TESTS = [
    test_exact_match_accepted, test_different_expression_rejected, test_labelled_switch_table, test_sidebyside,
    test_wrong_callee_rejected, test_self_call,
    test_class_method_names, test_qualified_names, test_wrong_literal_rejected, test_guessed_names,
    test_implicit_needs_emitter,
    test_lint, test_duplicates_and_cap,
    test_claims_concurrency, test_integrate, test_integrate_skips_excluded, test_integrate_generated_follows_emitter,
    test_integrate_keeps_distinct_includes,
    test_integrate_drops_what_breaks,
    test_context_and_queue, test_base_slot, test_claim_by_class, test_families, test_stamp_derive, test_vtables,
    test_sweep, test_guard,
    test_wave_dry_run, test_compile_command_matches_configure, test_categories_and_except_list,
]


def test_weak_externals_and_aliases(base: Path) -> None:
    """A vtable's vector deleting destructor (??_E) resolves to the scalar one the file defines, and tools/cc.py
    points references to an alias at the address's own name."""
    import coff
    sys.path.insert(0, str(ROOT / "tools"))
    import cc
    p = Project()
    path = fixture.compile_reference(p, (
        "struct Base { virtual ~Base(); };\n"
        "struct Kid : Base { Kid(); ~Kid(); };\n"
        "Kid::Kid() {}\n"
        "void Freed(void*);\n"
        "void Primary(void*);\n"
        "void Once() { Freed(0); }\n"
        "void Both() { Primary(0); Freed(0); }\n"), base / "weak")
    obj = coff.Coff.load(path)
    weak = obj.symbol("??_EKid@@UAEPAXI@Z")
    check(weak is not None and not weak.defined, "the vtable references the vector deleting destructor")
    check(obj.resolve(weak).name == "??_GKid@@UAEPAXI@Z" and obj.resolve(weak).defined,
          "the weak ??_E resolves to the scalar deleting destructor the file defines")
    cc.normalize(path, {"?Freed@@YAXPAX@Z": "?Primary@@YAXPAX@Z"})
    obj = coff.Coff.load(path)
    targets = {obj.slots[r.symbol].name for sec in obj.sections for r in sec.relocations
               if obj.slots[r.symbol] is not None and not obj.slots[r.symbol].is_section}
    check("?Freed@@YAXPAX@Z" not in targets and "?Primary@@YAXPAX@Z" in targets,
          "every reference to the alias now names the primary")


TESTS.append(test_weak_externals_and_aliases)


def test_fold_labels(base: Path) -> None:
    """A switch's case labels and tables become the function plus an offset, so objdiff reads the function
    whole, and the gate still finds where its code ends."""
    import coff
    p = Project()
    os.environ["T3_CC_NO_FOLD"] = "1"  # the compiler's own labels, as tools/cc.py receives them
    try:
        path = fixture.compile_reference(p, (
            "int Pick(int k)\n{\n    switch (k)\n    {\n"
            "    case 0: return 3;\n    case 1: return 7;\n    case 2: return 11;\n    case 3: return 13;\n"
            "    case 4: return 17;\n    case 5: return 19;\n    }\n    return 0;\n}\n"), base / "fold")
    finally:
        del os.environ["T3_CC_NO_FOLD"]
    obj = coff.Coff.load(path)
    is_label = lambda s: s.storage == coff.IMAGE_SYM_CLASS_STATIC and s.name.startswith("$L") and not s.is_function
    fn = obj.symbol("?Pick@@YAHH@Z")
    labels = [s for s in obj.symbols if s.section == fn.section and is_label(s)]
    check(bool(labels), "MSVC labels the switch's cases and table with static $L symbols")
    folded = coff.Coff(obj.fold_labels(is_label))
    fn2 = folded.symbol("?Pick@@YAHH@Z")
    check(not any(s.defined and is_label(s) for s in folded.symbols), "no label is left defined")
    check(folded.extent(fn2) == (fn2.value, len(folded.section(fn2.section).data)),
          "the function runs to the end of its section, tables included")
    before = {r.offset: obj.slots[r.symbol].value + obj.addend(fn.section, r)
              for r in obj.section(fn.section).relocations}
    after = {r.offset: folded.slots[r.symbol].value + folded.addend(fn2.section, r)
             for r in folded.section(fn2.section).relocations}
    check(before == after, "every reference still lands on the same byte")
    from verify import Verifier
    data, code, length = Verifier(p)._prepare_candidate(folded, fn2, "?Pick@@YAHH@Z")
    data0, code0, length0 = Verifier(p)._prepare_candidate(obj, fn, "?Pick@@YAHH@Z")
    check((code, length) == (code0, length0) and code < length,
          "the gate ends the folded function's code where the tables start, as with labels")


TESTS.append(test_fold_labels)


def test_fold_into(base: Path) -> None:
    """A reference to a label inside a named data object (`&TEXT("AGarrett")[1]` as the split names it)
    becomes the object plus the offset, as the compiler writes it."""
    import coff
    p = Project()
    path = fixture.compile_reference(p, 'extern "C" const char DAT_10e78901[];\n'
                                        'const char* Name() { return DAT_10e78901; }\n', base / "interior")
    obj = coff.Coff.load(path)
    container = "??_C@_08PCNBEJK@AGarrett?$AA@"
    folded = obj.fold_into(lambda name: (container, 1) if name == "_DAT_10e78901" else None)
    check(folded is not None, "the label's reference is folded")
    c = coff.Coff(folded)
    refs = [(c.slots[r.symbol].name, c.addend(sec.index, r)) for sec in c.sections for r in sec.relocations]
    check((container, 1) in refs and not any(n == "_DAT_10e78901" for n, _ in refs),
          f"the reference is the object plus the offset: {refs}")
    check(obj.fold_into(lambda name: None) is None, "nothing to fold leaves the object alone")


TESTS.append(test_fold_into)


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("-k", help="run only tests whose name contains this")
    parser.add_argument("--keep", action="store_true", help="keep the temporary projects")
    args = parser.parse_args()
    project = Project()
    if not project.cl.is_file() or not project.objdiff.is_file():
        sys.exit("the toolchain is missing: run python configure.py && ninja build/tools/objdiff-cli first")
    base = Path(tempfile.mkdtemp(prefix="t3-agent-selftest-"))
    failed = 0
    try:
        for test in TESTS:
            if args.k and args.k not in test.__name__:
                continue
            start = time.time()
            try:
                test(base)
                print(f"PASS {test.__name__} ({time.time() - start:.1f}s)")
            except Exception:
                failed += 1
                print(f"FAIL {test.__name__}")
                traceback.print_exc()
    finally:
        if args.keep:
            print(f"kept {base}")
        else:
            shutil.rmtree(base, ignore_errors=True)
    print("all passed" if not failed else f"{failed} failed")
    sys.exit(1 if failed else 0)


if __name__ == "__main__":
    main()
