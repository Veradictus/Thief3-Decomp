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
import subprocess
import sys
import tempfile
import time
import traceback
from pathlib import Path

HERE = Path(__file__).resolve().parent
sys.path.insert(0, str(HERE))

import fixture  # noqa: E402
from common import ROOT, Project, splitslib, symbolslib  # noqa: E402

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
}
# In the reference, Callee stays a call (as if it lived in another file); a unit defining it would inline it.
REFERENCE = DECLS + "\n".join(("__declspec(noinline) " if s == "?Callee@@YAHH@Z" else "") + body
                               for s, body in FUNCTIONS.items()) + "\n"
CALLEE_DECL = "int Callee(int);\n"


class Env:
    """A fixture project and a way to run the tools in it."""

    def __init__(self, base: Path, name: str, named=frozenset(), extra=None, aliases=None):
        self.root = base / name
        self.root.mkdir(parents=True)
        project = Project()
        ref = fixture.compile_reference(project, REFERENCE, self.root / "reference")
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
    for i in range(2, 13):
        proc = e.run("try.py", e.addr(sym), e.candidate(sym, f"int Seven(int x) {{ return x * 7 + {99 - i}; }}"))
        check(f"ATTEMPT {i}/12" in proc.stdout, f"attempt {i} is counted", proc)
    proc = e.run("try.py", e.addr(sym), e.candidate(sym))
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
    check(set(by_source) == {"Game/Foo.cpp", "Game/Unsorted.cpp"}, f"units by class: {sorted(by_source)}")
    unsorted = by_source["Game/Unsorted.cpp"]
    check(any(a >= fixture.TEXT_X for a, _ in unsorted.text), "the EH funclets' .text$x range is declared")
    check(len(units) > len(splits), "auto units still cover the rest")
    names = {s.name for s in symbolslib.load(e.root / "config/PC_20040610/symbols.txt")}
    check({"?Get@Foo@@QBEHXZ", "?Helper@@YAHH@Z", "__ehhandler$?WithEh@@YAHH@Z", "__real@40200000"} <= names,
          "names are applied to symbols.txt")
    for unit in by_source:
        src = e.root / "src" / unit
        check(src.is_file() and "// FUNCTION: 0x" in src.read_text(), f"{unit} is written")
    units_json = json.loads((e.root / "config/PC_20040610/units.json").read_text())
    check(units_json["Game/Foo.cpp"]["category"] == "game", "the unit's category is recorded")
    proc = e.run("integrate.py")
    check("nothing to integrate" in proc.stdout, "a second run has nothing to do", proc)
    status = json.loads(e.run("next.py", "status").stdout)
    check(status["integrated"] == 5, f"src/ markers count as integrated: {status}")


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
    check([q["difficulty"] for q in queue] == sorted(q["difficulty"] for q in queue), "the queue is easy first")
    check(e.addr("?Get@Foo@@QBEHXZ") not in [q["addr"] for q in queue], "accepted functions leave the queue")


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
    ]
    for tool, data, expected in cases:
        event = json.dumps({"tool_name": tool, "tool_input": data, "cwd": str(project)})
        proc = subprocess.run([sys.executable, str(HERE / "hooks" / "guard.py")], input=event, text=True,
                              capture_output=True, env=dict(os.environ, CLAUDE_PROJECT_DIR=str(project)))
        check(proc.returncode == expected, f"guard: {tool} {data} -> {proc.returncode}, want {expected}", proc)
    settings = json.loads((HERE / "guard-settings.json").read_text())
    check("guard.py" in settings["hooks"]["PreToolUse"][0]["hooks"][0]["command"], "the settings run the guard")


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
    for name in ("splits.py", "symbols.py", "ninja_syntax.py"):
        shutil.copy(ROOT / "tools" / name, tmp / "tools")
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

    def flags(argv):
        return [a for a in argv if a.startswith("/") and not a.startswith(("/I", "/Fo"))]
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


TESTS = [
    test_exact_match_accepted, test_different_expression_rejected, test_wrong_callee_rejected,
    test_class_method_names, test_qualified_names, test_wrong_literal_rejected, test_lint, test_duplicates_and_cap,
    test_claims_concurrency, test_integrate, test_integrate_drops_what_breaks, test_context_and_queue, test_guard,
    test_wave_dry_run, test_compile_command_matches_configure,
]


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
