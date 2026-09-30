"""Shared paths, configuration and state for the matching tools in tools/agent/.

The tools run from any checkout: the main one, or a worker's git worktree.
Shared inputs and state live in the *main* checkout, found through git's
common directory:

    build/agent/        claims, attempt ledgers, accepted and deferred records,
                        caches, waves and worker worktrees
    build/tools, build/compilers   the toolchain configure.py downloaded
    build/<version>/obj the split target objects (ninja)
    config/, orig/, include/, src/, configure.py, build.ninja

Environment overrides, mostly for tests: T3_AGENT_MAIN (main checkout),
T3_AGENT_CONFIG (config directory), T3_AGENT_OBJ (target objects),
T3_AGENT_STATE (state directory), T3_AGENT_EXE (the exe; empty for none),
T3_AGENT_SRC (source tree). T3_AGENT_ID names the worker.
"""

import bisect
import importlib.util
import json
import os
import re
import shlex
import subprocess
import sys
import time
import uuid
from pathlib import Path
from typing import Dict, List, Optional, Sequence, Tuple, Union

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))

import ninja_syntax  # noqa: E402
import splits as splitslib  # noqa: E402
import symbols as symbolslib  # noqa: E402

# Where the libraries linked after the game start (configure.py's LIBRARY_START
# when it defines one): functions from here on are mostly library code (qhull,
# CRT, STL, D3DX, Havok), which is matched from library objects or original
# sources rather than decompiled, and not queued.
LIBRARY_START = 0x10CFBFB0
ATTEMPT_CAP = 12
CLAIM_TTL = 2 * 3600
PLACEHOLDER = re.compile(r"^(?:[A-Za-z]+_)*(?:FUN|DAT|LAB|PTR|BYTE|WORD|DWORD|QWORD|switchdataD|caseD|s|u|thunk)_"
                         r"(?:[0-9A-Za-z_]*_)?(?P<addr>[0-9A-Fa-f]{8})$|^Unwind@(?P<unwind>[0-9A-Fa-f]{8})$")


def fmt_addr(address: int) -> str:
    return f"0x{address:08X}"


def addr_key(address: int) -> str:
    """File-name form of an address: 10A52530."""
    return f"{address:08X}"


def placeholder_address(name: str) -> Optional[int]:
    """The address in a Ghidra/delink placeholder name (FUN_10a52530, DAT_.., Unwind@..), else None."""
    m = PLACEHOLDER.match(name)
    if not m:
        return None
    return int(m.group("addr") or m.group("unwind"), 16)


def is_placeholder(name: str) -> bool:
    return placeholder_address(name) is not None


def emit(obj) -> None:
    print(json.dumps(obj, indent=1))


def atomic_write(path: Path, text: str) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    tmp = path.with_name(f".{path.name}.{uuid.uuid4().hex[:8]}.tmp")
    tmp.write_text(text, encoding="utf-8", newline="\n")
    for attempt in range(20):
        try:
            os.replace(tmp, path)
            return
        except PermissionError:  # Windows: a reader has the file open for a moment
            if attempt == 19:
                raise
            time.sleep(0.05)


def unlink(path: Path) -> None:
    """Deletes `path` if it exists, retrying while a reader has it open (Windows
    refuses to delete an open file)."""
    for attempt in range(20):
        try:
            path.unlink(missing_ok=True)
            return
        except PermissionError:
            if attempt == 19:
                raise
            time.sleep(0.05)


def read_json(path: Path, default=None):
    try:
        return json.loads(path.read_text(encoding="utf-8"))
    except (OSError, ValueError):
        return default


def main_root() -> Path:
    """The main checkout: $T3_AGENT_MAIN, else the parent of git's common directory, else this checkout."""
    env = os.environ.get("T3_AGENT_MAIN")
    if env:
        return Path(env).resolve()
    try:
        out = subprocess.run(["git", "rev-parse", "--git-common-dir"], cwd=ROOT, capture_output=True, text=True,
                             timeout=30)
        if out.returncode == 0 and out.stdout.strip():
            return (ROOT / out.stdout.strip()).resolve().parent  # the path may be relative to ROOT
    except (OSError, subprocess.TimeoutExpired):
        pass
    return ROOT


def tool_path(path: Path, cwd: Path) -> str:
    """A path as the compiler sees it. Under wibo/wine an absolute POSIX path
    reads as a cl.exe option, so off Windows paths are made relative to cwd."""
    if os.name == "nt":
        return str(Path(path).resolve())
    return os.path.relpath(Path(path).resolve(), cwd)


class Lock:
    """An exclusive lock file (O_EXCL); a lock older than `stale` seconds is broken."""

    def __init__(self, path: Path, stale: float = 3600, wait: float = 0):
        self.path, self.stale, self.wait = path, stale, wait

    def __enter__(self) -> "Lock":
        self.path.parent.mkdir(parents=True, exist_ok=True)
        deadline = time.time() + self.wait
        while True:
            try:
                fd = os.open(self.path, os.O_CREAT | os.O_EXCL | os.O_WRONLY)
                os.write(fd, json.dumps({"pid": os.getpid(), "time": time.time()}).encode())
                os.close(fd)
                return self
            except PermissionError:
                # Windows refuses to create a file that its holder is still deleting: retry briefly.
                if time.time() >= deadline + 1:
                    raise
                time.sleep(0.05)
            except FileExistsError:
                try:
                    if time.time() - self.path.stat().st_mtime > self.stale:
                        os.replace(self.path, self.path.with_suffix(f".stale.{uuid.uuid4().hex[:8]}"))
                        continue
                except OSError:
                    time.sleep(0.05)
                    continue
                if time.time() >= deadline:
                    held = read_json(self.path, {})
                    raise SystemExit(f"{self.path} is held (pid {held.get('pid')}); try again later")
                time.sleep(0.2)

    def __exit__(self, *exc) -> None:
        try:
            self.path.unlink()
        except OSError:
            pass


def _load_configure(main: Path):
    """configure.py as a module (its top level only defines constants and imports)."""
    path = main / "configure.py"
    if not path.is_file():
        path = ROOT / "configure.py"
    spec = importlib.util.spec_from_file_location("t3_configure", path)
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    return module


class Project:
    def __init__(self, version: Optional[str] = None):
        self.root = ROOT
        self.main = main_root()
        self.configure = _load_configure(self.main)
        self.version = version or os.environ.get("T3_AGENT_VERSION") or self.configure.DEFAULT_VERSION
        env = os.environ.get
        self.config_dir = Path(env("T3_AGENT_CONFIG") or self.main / "config" / self.version)
        self.symbols_txt = self.config_dir / "symbols.txt"
        self.splits_txt = self.config_dir / "splits.txt"
        self.obj_dir = Path(env("T3_AGENT_OBJ") or self.main / "build" / self.version / "obj")
        exe = env("T3_AGENT_EXE")
        if exe is None:
            exe = self.main / "orig" / self.version / self.configure.VERSIONS.get(self.version, {}).get("exe", "")
        self.exe: Optional[Path] = Path(exe) if exe else None
        self.state = Path(env("T3_AGENT_STATE") or self.main / "build" / "agent")
        self.src_dir = Path(env("T3_AGENT_SRC") or self.main / "src")
        self.include_dir = self.main / "include"
        # The toolchain: the main checkout's, else this checkout's (tests point T3_AGENT_MAIN elsewhere).
        ext = ".exe" if os.name == "nt" else ""
        build = next((b for b in (self.main / "build", ROOT / "build")
                      if (b / "compilers" / "Win32" / "7.1" / "cl.exe").is_file()), self.main / "build")
        self.objdiff = build / "tools" / f"objdiff-cli{ext}"
        self.cl = build / "compilers" / "Win32" / "7.1" / "cl.exe"
        self.wibo = build / "tools" / "wibo" if os.name != "nt" else None
        self.chunk_size = self.configure.CHUNK_SIZE

    # -- symbols and units -----------------------------------------------------
    @property
    def symbols(self) -> List[symbolslib.Symbol]:
        if not hasattr(self, "_symbols"):
            self._symbols = symbolslib.load(self.symbols_txt)
        return self._symbols

    @property
    def functions(self) -> List[symbolslib.Symbol]:
        return [s for s in self.symbols if s.is_function and s.size > 0]

    @property
    def by_addr(self) -> Dict[int, symbolslib.Symbol]:
        if not hasattr(self, "_by_addr"):
            self._by_addr = {}
            for s in self.symbols:
                self._by_addr.setdefault(s.address, s)
            for f in self.functions:  # a function wins over a label at its address
                self._by_addr[f.address] = f
        return self._by_addr

    @property
    def by_name(self) -> Dict[str, symbolslib.Symbol]:
        if not hasattr(self, "_by_name"):
            self._by_name = {s.name: s for s in self.symbols}
        return self._by_name

    def address_of(self, name: str) -> Optional[int]:
        sym = self.by_name.get(name)
        return sym.address if sym else placeholder_address(name)

    def function(self, address: int) -> symbolslib.Symbol:
        sym = self.by_addr.get(address)
        if sym is None or not sym.is_function:
            raise SystemExit(f"{fmt_addr(address)} is not a function in {self.symbols_txt}")
        return sym

    def parse_addr(self, text: str) -> int:
        """0x10A52530, 10a52530, FUN_10a52530 or a name from symbols.txt."""
        sym = self.by_name.get(text)
        if sym:
            return sym.address
        if placeholder_address(text) is not None:
            return placeholder_address(text)
        try:
            return int(text, 16)
        except ValueError:
            raise SystemExit(f"not an address or a symbols.txt name: {text}")

    def breaks(self) -> Tuple[int, ...]:
        """Addresses no auto unit spans, as configure.py passes them to splits.plan()."""
        cfg = self.configure
        return tuple(a for a in (getattr(cfg, "LIBRARY_START", None), *getattr(cfg, "FUNCLETS", ())) if a)

    def plan(self, declared: List[splitslib.Unit]) -> List[splitslib.Unit]:
        """Declared plus auto units, exactly as configure.py plans the split."""
        return splitslib.plan(declared, self.functions, self.chunk_size, breaks=self.breaks())

    def units(self) -> List[splitslib.Unit]:
        if not hasattr(self, "_units"):
            self._units = self.plan(splitslib.load(self.splits_txt))
        return self._units

    def unit_for(self, address: int) -> Optional[splitslib.Unit]:
        for u in self.units():
            if any(a <= address < b for a, b in u.text):
                return u
        return None

    def target_object(self, address: int) -> Optional[Path]:
        unit = self.unit_for(address)
        path = self.obj_dir / unit.object if unit else None
        return path if path and path.is_file() else None

    def code_extent(self, address: int) -> Tuple[int, int]:
        """(code end, region end) of a function: its code stops at the first
        data object inside it (a switch table), as in tools/delink_model.py; its
        region runs on over the data objects that follow it."""
        f = self.function(address)
        if not hasattr(self, "_extents"):
            starts = sorted({g.address for g in self.functions})
            objects = sorted((s.address, s.end, s.section) for s in self.symbols if not s.is_function and s.size)
            self._extents = (starts, objects, [o[0] for o in objects])
        starts, objects, object_starts = self._extents
        i = bisect.bisect_right(starts, address)
        limit = max(f.end, starts[i] if i < len(starts) else f.end)
        inside = [o for o in objects[bisect.bisect_right(object_starts, address):bisect.bisect_left(object_starts,
                                                                                                    limit)]
                  if o[2] == f.section]
        code_end = min([a for a, _, _ in inside if a < f.end] + [f.end])
        region_end = max([f.end] + [b for _, b, _ in inside])
        return code_end, region_end

    def text_x_range(self) -> Tuple[int, int]:
        """[start, end) of .text$x (EH unwind funclets and handlers): configure.py's FUNCLETS, else from the
        first `Unwind@` funclet to the last, plus the handler packed right after it."""
        if getattr(self.configure, "FUNCLETS", None):
            return tuple(self.configure.FUNCLETS)
        unwinds = [f for f in self.functions if f.name.startswith("Unwind@")]
        if not unwinds:
            return 0, 0
        start, end = min(f.address for f in unwinds), max(f.end for f in unwinds)
        starts = {f.address: f for f in self.functions}
        while end in starts:
            end = starts[end].end
        return start, end

    def library_start(self) -> int:
        """Where the libraries linked after the game start: configure.py's
        LIBRARY_START, else this module's."""
        return getattr(self.configure, "LIBRARY_START", LIBRARY_START)

    # -- compiling -------------------------------------------------------------
    def cflags_for(self, address: Optional[int] = None) -> List[str]:
        """The unit's cflags from configure.UNITS when a declared unit holds the address, else CFLAGS."""
        unit = self.unit_for(address) if address is not None else None
        opts = self.configure.UNITS.get(unit.source, {}) if unit and not unit.auto else {}
        return list(opts.get("cflags", self.configure.CFLAGS))

    def _ninja_cc(self) -> Optional[str]:
        """The `cc` rule's command from the main checkout's build.ninja (written by configure.py)."""
        path = self.main / "build.ninja"
        if not path.is_file():
            return None
        text = re.sub(r" \$\n\s*", " ", path.read_text(encoding="utf-8"))
        m = re.search(r"^rule cc\n(?:  \w+ = .*\n)*?  command = (.*)$", text, re.M)
        return m.group(1) if m else None

    def compile_command(self, source: Path, output: Path, cflags: Sequence[str]) -> Tuple[Union[str, List[str]], Path]:
        """(command, cwd) compiling one file the way build.ninja does, without /showIncludes: the `cc`
        rule's command line as ninja would run it (a string), or an argv without build.ninja."""
        cwd = self.main
        rule = self._ninja_cc()
        quote = (lambda s: f'"{s}"' if " " in s else s) if os.name == "nt" else shlex.quote
        if rule:
            return ninja_syntax.expand(rule, {}, {
                "cflags": " ".join(cflags),
                "out": quote(tool_path(output, cwd)),
                "in": quote(tool_path(source, cwd)),
            }).replace(" /showIncludes", ""), cwd
        else:
            # No build.ninja yet: the same command configure.py writes, with its default wrapper.
            include = self.cl.parent / "Include"
            argv = ([tool_path(self.wibo, cwd)] if self.wibo else []) + [
                tool_path(self.cl, cwd), "/nologo", "/c", "/X",
                f"/I{tool_path(include, cwd)}", f"/I{tool_path(self.include_dir, cwd)}",
                f"/I{tool_path(self.src_dir, cwd)}", *cflags,
                f"/Fo{tool_path(output, cwd)}", tool_path(source, cwd),
            ]
        return argv, cwd

    def compile(self, source: Path, output: Path, cflags: Sequence[str]) -> Tuple[bool, str]:
        output.parent.mkdir(parents=True, exist_ok=True)
        if output.exists():
            output.unlink()
        command, cwd = self.compile_command(source, output, cflags)
        # Like ninja: a rule's command runs through /bin/sh off Windows, as a command line on Windows.
        shell = isinstance(command, str) and os.name != "nt"
        if isinstance(command, str) and os.name == "nt":
            # Windows looks a relative program up from this process's directory, not
            # from cwd, so a worker in a worktree would not find build/'s cl.exe.
            program, sep, rest = command.partition(" ")
            if not Path(program).is_absolute() and (cwd / program).is_file():
                command = f'"{cwd / program}"{sep}{rest}'
        try:
            proc = subprocess.run(command, cwd=cwd, shell=shell, capture_output=True, text=True, errors="replace",
                                  timeout=300)
        except (OSError, subprocess.TimeoutExpired) as e:
            return False, f"cannot run the compiler: {e}"
        # cl.exe echoes the source file name first; drop it.
        lines = [ln for ln in (proc.stdout + proc.stderr).splitlines() if ln.strip() and ln.strip() != source.name]
        return proc.returncode == 0 and output.is_file(), "\n".join(lines)

    # -- state -----------------------------------------------------------------
    def state_dir(self, *parts: str) -> Path:
        path = self.state.joinpath(*parts)
        path.mkdir(parents=True, exist_ok=True)
        return path

    def _records(self, kind: str) -> Dict[int, dict]:
        """The JSON records in <state>/<kind>/, through an index cached by file time (try.py reads them
        on every attempt)."""
        folder = self.state / kind
        cache_path = self.state / "cache" / f"{kind}-index.json"
        cache = read_json(cache_path, {}) or {}
        out, fresh = {}, {}
        for path in sorted(folder.glob("*.json")) if folder.is_dir() else []:
            try:
                stamp = path.stat().st_mtime_ns
            except OSError:
                continue
            hit = cache.get(path.name)
            if not hit or hit[0] != stamp:
                hit = [stamp, read_json(path)]
            fresh[path.name] = hit
            if hit[1] and "addr" in hit[1]:
                out[int(hit[1]["addr"], 16)] = hit[1]
        if fresh != cache:
            atomic_write(cache_path, json.dumps(fresh))
        return out

    def accepted(self) -> Dict[int, dict]:
        return self._records("accepted")

    def deferred(self) -> Dict[int, dict]:
        return self._records("deferred")

    def mnemonics(self, address: int) -> List[str]:
        """The target's opcode sequence recorded when the function was accepted (for similarity)."""
        path = self.state / "accepted" / f"{addr_key(address)}.mnemonics"
        return path.read_text(encoding="utf-8").split() if path.is_file() else []

    def integrated(self) -> Dict[int, str]:
        """Addresses already in src/, from the `// FUNCTION: 0x...` lines integrate.py writes."""
        out = {}
        if self.src_dir.is_dir():
            for path in sorted(self.src_dir.rglob("*.cpp")):
                for m in FUNCTION_MARKER.finditer(path.read_text(encoding="utf-8", errors="replace")):
                    out[int(m.group(1), 16)] = str(path.relative_to(self.src_dir)).replace(os.sep, "/")
        return out


# The line that introduces a function in scratch files and in src/ units.
FUNCTION_MARKER = re.compile(r"^// FUNCTION: (?:0x)?([0-9A-Fa-f]{8})\b(.*)$", re.M)


def agent_id(explicit: Optional[str] = None) -> str:
    return explicit or os.environ.get("T3_AGENT_ID") or "manual"


class Claims:
    """One file per claimed function in <state>/claims.

    A new claim appears in one atomic step: it is written to a temporary file
    and hard-linked into place, which fails if the claim exists (O_EXCL where
    the file system has no hard links). Taking over an expired claim, renewing
    and releasing happen under a short lock, so two workers never both remove
    and recreate the same claim.
    """

    FRESH = 60  # seconds an unreadable claim is assumed to be still being written

    def __init__(self, project: Project):
        self.dir = project.state_dir("claims")
        self.lock = self.dir / ".lock"

    def path(self, address: int) -> Path:
        return self.dir / f"{addr_key(address)}.json"

    def get(self, address: int) -> Optional[dict]:
        claim = read_json(self.path(address))
        if claim and claim.get("expires", 0) < time.time():
            return None
        return claim

    def all(self) -> List[dict]:
        now = time.time()
        return [c for c in (read_json(p) for p in sorted(self.dir.glob("*.json"))) if c and c.get("expires", 0) >= now]

    def _live(self, path: Path) -> bool:
        claim = read_json(path)
        if claim is not None:
            return claim.get("expires", 0) >= time.time()
        try:
            return time.time() - path.stat().st_mtime < self.FRESH
        except OSError:
            return False

    def _create(self, path: Path, claim: dict) -> bool:
        tmp = path.with_name(f".{path.name}.{uuid.uuid4().hex[:8]}.tmp")
        tmp.write_text(json.dumps(claim), encoding="utf-8")
        try:
            try:
                os.link(tmp, path)
                return True
            except FileExistsError:
                return False
            except OSError:
                pass
            try:  # no hard links: create exclusively, then fill (readers wait FRESH seconds)
                fd = os.open(path, os.O_CREAT | os.O_EXCL | os.O_WRONLY)
            except FileExistsError:
                return False
            with os.fdopen(fd, "w", encoding="utf-8") as f:
                json.dump(claim, f)
            return True
        finally:
            tmp.unlink()

    def take(self, address: int, agent: str, ttl: float, extra: Optional[dict] = None) -> Optional[dict]:
        path = self.path(address)
        claim = {"addr": fmt_addr(address), "agent": agent, "id": uuid.uuid4().hex[:12],
                 "claimed": time.time(), "expires": time.time() + ttl, **(extra or {})}
        if self._create(path, claim):
            return claim
        if self._live(path):
            return None
        with Lock(self.lock, stale=60, wait=30):
            if path.exists() and self._live(path):
                return None
            unlink(path)  # expired
            return claim if self._create(path, claim) else None

    def renew(self, address: int, agent: str, ttl: float = CLAIM_TTL) -> Optional[dict]:
        with Lock(self.lock, stale=60, wait=30):
            claim = self.get(address)
            if claim and claim.get("agent") == agent:
                claim["expires"] = time.time() + ttl
                atomic_write(self.path(address), json.dumps(claim))
            return claim

    def release(self, address: int, agent: Optional[str] = None) -> bool:
        path = self.path(address)
        with Lock(self.lock, stale=60, wait=30):
            claim = read_json(path)
            if claim is None or (agent and claim.get("agent") != agent):
                return False
            try:
                unlink(path)
            except OSError:
                return False
            return True


def demangle(project: Project, names: Sequence[str]) -> Dict[str, str]:
    """MSVC decorated name -> demangled text (cached). Natively undname.exe from
    the compiler bundle; elsewhere objdiff's demangler, fed a generated object
    (undname.exe prints nothing under wibo, which lacks msvcr71's __unDNameEx)."""
    import coff

    cache_path = project.state / "cache" / "demangle.json"
    cache: Dict[str, str] = read_json(cache_path, {}) or {}
    todo = sorted({n for n in names if n.startswith("?") and n not in cache})
    if todo:
        found: Dict[str, str] = {}
        undname = project.cl.parent / "undname.exe"
        if os.name == "nt" and undname.is_file():
            for i in range(0, len(todo), 64):
                chunk = todo[i:i + 64]
                out = subprocess.run([str(undname), *chunk], capture_output=True, text=True, errors="replace")
                for name, text in re.findall(r'Undecoration of :- "(.*?)"\s*is :- "(.*?)"', out.stdout):
                    found[name] = text
        if not found and project.objdiff.is_file():
            tmp = project.state_dir("tmp") / f"demangle-{os.getpid()}.obj"
            tmp.write_bytes(coff.undefined_object(todo))
            out = subprocess.run([str(project.objdiff), "diff", "-1", str(tmp), "-o", "-", "--format", "json",
                                  "_t3_anchor"], capture_output=True, text=True, errors="replace")
            tmp.unlink()
            if out.returncode == 0:
                for sym in json.loads(out.stdout).get("left", {}).get("symbols", []):
                    if sym.get("demangled_name"):
                        found[sym["name"]] = sym["demangled_name"]
        cache.update(found)
        cache.update({n: "" for n in todo if n not in found})
        atomic_write(cache_path, json.dumps(cache, indent=0, sort_keys=True))
    return {n: cache.get(n, "") for n in names}


def qualified_name(name: str, demangled: str = "") -> str:
    """`Class::Method` (or `function`, `Class::member`) from a decorated name and its demangled text.

    C names: `_name`, `_name@8` (stdcall) and `@name@8` (fastcall) give `name`.
    """
    if not name.startswith("?"):
        m = re.match(r"^[_@]?([A-Za-z_$][\w$]*?)(?:@\d+)?$", name)
        return m.group(1) if m else name
    text = demangled.strip()
    if not text:
        return name
    # Drop trailing qualifiers, then the parameter list: the "(...)" matching the last ")".
    text = re.sub(r"(\s*(const|volatile|throw\(.*?\)|__ptr64))*$", "", text)
    if text.endswith(")"):
        depth = 0
        for i in range(len(text) - 1, -1, -1):
            depth += {")": 1, "(": -1}.get(text[i], 0)
            if depth == 0:
                text = text[:i].rstrip()
                break
    # A function-pointer variable, "void (__thiscall UObject::** GNatives)(...)":
    # its name closes the parenthesised declarator (after any array bounds).
    if text.endswith(")"):
        text = re.sub(r"(\[\d*\])+$", "", text[:-1].rstrip()).rstrip()
    # The name is the last space-separated token outside template brackets.
    depth = 0
    for i in range(len(text) - 1, -1, -1):
        c = text[i]
        depth += {">": 1, "<": -1}.get(c, 0)
        if c == " " and depth == 0:
            return text[i + 1:]
    return text


def class_of(qualified: str) -> str:
    """`Class` from `Class::Method` (templates stripped: `TArray<class FName>::Add` -> `TArray`), else ''."""
    depth, cut = 0, -1
    for i, c in enumerate(qualified):
        depth += {"<": 1, ">": -1}.get(c, 0)
        if depth == 0 and qualified.startswith("::", i):
            cut = i
    if cut < 0:
        return ""
    owner = qualified[:cut]
    depth, start = 0, 0
    for i, c in enumerate(owner):  # the innermost class of a nested name
        depth += {"<": 1, ">": -1}.get(c, 0)
        if depth == 0 and owner.startswith("::", i):
            start = i + 2
    return re.sub(r"<.*$", "", owner[start:])


class Ledger:
    """Every scored attempt at one function: <state>/attempts/<ADDR>/ledger.jsonl plus a copy of each source."""

    def __init__(self, project: Project, address: int):
        self.dir = project.state / "attempts" / addr_key(address)
        self.path = self.dir / "ledger.jsonl"

    def entries(self) -> List[dict]:
        if not self.path.is_file():
            return []
        out = []
        for line in self.path.read_text(encoding="utf-8").splitlines():
            try:
                out.append(json.loads(line))
            except ValueError:
                pass
        return out

    def add(self, entry: dict, source: bytes) -> None:
        self.dir.mkdir(parents=True, exist_ok=True)
        (self.dir / f"{entry['sha']}.cpp").write_bytes(source)
        with open(self.path, "a", encoding="utf-8") as f:
            f.write(json.dumps(entry) + "\n")

    def source(self, sha: str) -> Optional[bytes]:
        path = self.dir / f"{sha}.cpp"
        return path.read_bytes() if path.is_file() else None

    def best(self) -> Optional[dict]:
        scored = [e for e in self.entries() if e.get("counted")]
        return max(scored, key=lambda e: (e.get("match", False), e.get("score", 0), -e.get("attempt", 0)),
                   default=None)
