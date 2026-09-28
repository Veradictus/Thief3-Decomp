#!/usr/bin/env python3
"""Generate build.ninja and objdiff.json.

    python configure.py [--version PC_20040610]
    ninja            # split T3Main.exe, compile src/, report progress

See README.md for the pipeline.
"""

import argparse
import json
import os
import shutil
import sys
from pathlib import Path
from typing import Dict, List

ROOT = Path(__file__).resolve().parent
sys.path.insert(0, str(ROOT / "tools"))

import ninja_syntax  # noqa: E402
import splits as splitslib  # noqa: E402
import symbols as symbolslib  # noqa: E402

VERSIONS = {
    "PC_20040610": {
        "exe": "T3Main.exe",
        "sha1": "40bf68a54246bcde2fb5fcbc75b94dc7c7f78305",
    },
}
DEFAULT_VERSION = "PC_20040610"

TOOL_TAGS = {
    "objdiff-cli": "v3.8.1",
    "delink": "v0.16.2",
    "compilers": "20260903",
    "wibo": "1.2.0",
}

# Automatic units cover unclaimed functions in chunks of about this many bytes.
CHUNK_SIZE = 0x10000

# Microsoft C/C++ 13.10.3077 (Visual C++ .NET 2003 RTM), per T3Main.exe's Rich
# header. Project-wide defaults; a unit can override them in UNITS.
# /O2 /GX reproduce the three functions checked so far (docs/target.md); the
# rest (runtime, defines) is the usual Win32 release setup and unverified.
CFLAGS = [
    "/O2",
    "/GX",
    "/GR-",
    "/MT",
    "/DNDEBUG",
    "/DWIN32",
    "/D_WINDOWS",
]

# Per-unit options, keyed by source path relative to src/ (as in splits.txt):
#   "status":   "NonMatching" (default) | "Matching"
#   "category": "game", "engine" or "libs" (default: from the unit's address)
#   "cflags":   replaces CFLAGS for this unit
UNITS: Dict[str, dict] = {}

# objdiff/decomp.dev progress categories. "main" is the headline (decomp.dev's
# default category): the game and its engine, without the libraries that are
# matched from their own objects or sources rather than decompiled.
CATEGORIES = {
    "main": "Game & engine",
    "game": "Game",
    "engine": "Engine",
    "libs": "Libraries",
}

# Where code comes from, by address, for units without a category. Code before
# the C runtime's entry point is the game and its engine (with Havok, libjpeg
# and CppUnit until they are split out); from the entry point on it is mostly
# the runtime, STL and D3DX. .text$x holds the exception-handling funclets of
# every function, which the compiler emits with their parents (docs/target.md).
CRT_ENTRY = 0x10D1F7AF
FUNCLETS = (0x10E02DA0, 0x10E3BF77)


def unit_categories(unit: splitslib.Unit, category: str = "") -> List[str]:
    if category in ("game", "engine"):
        return ["main", category]
    if category:
        return [category]
    start = unit.text[0][0] if unit.text else 0
    return ["main"] if start < CRT_ENTRY or FUNCLETS[0] <= start < FUNCLETS[1] else ["libs"]


def unit_options(config_dir: Path) -> Dict[str, dict]:
    """UNITS, plus the per-unit options tools/agent/integrate.py records in
    units.json (categories); UNITS wins where both set one."""
    options = {source: dict(opts) for source, opts in UNITS.items()}
    units_json = config_dir / "units.json"
    if units_json.is_file():
        for source, opts in json.loads(units_json.read_text(encoding="utf-8")).items():
            options[source] = {**opts, **options.get(source, {})}
    return options


def plan_units(config_dir: Path) -> List[splitslib.Unit]:
    """The translation units: those declared in splits.txt, plus auto chunks
    covering every other function in symbols.txt."""
    functions = [s for s in symbolslib.load(config_dir / "symbols.txt") if s.is_function and s.size > 0]
    return splitslib.plan(splitslib.load(config_dir / "splits.txt"), functions, CHUNK_SIZE,
                          breaks=(CRT_ENTRY, *FUNCLETS))


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("--version", default=DEFAULT_VERSION, choices=sorted(VERSIONS))
    parser.add_argument("--wrapper", help="wibo/wine used to run cl.exe (default: wibo off Windows)")
    parser.add_argument(
        "--msvc-runtime",
        default=os.environ.get("MSVC71_RUNTIME"),
        help="Windows only: directory holding msvcr71.dll and msvcp71.dll, which cl.exe needs "
             "(default: $MSVC71_RUNTIME)",
    )
    args = parser.parse_args()

    os.chdir(ROOT)
    version = args.version
    info = VERSIONS[version]
    config_dir = Path("config") / version
    build_dir = Path("build") / version
    exe = Path("orig") / version / info["exe"]
    symbols_txt = config_dir / "symbols.txt"
    splits_txt = config_dir / "splits.txt"
    options = unit_options(config_dir)

    if not exe.is_file():
        print(f"warning: {exe} is missing; copy it from the game's System/ folder (see README.md)")

    units = plan_units(config_dir)
    for source in options:
        if not any(u.source == source for u in units):
            sys.exit(f"UNITS entry {source} is not declared in {splits_txt}")

    # -- tools -----------------------------------------------------------------
    ext = ".exe" if os.name == "nt" else ""
    tools_dir = Path("build") / "tools"
    objdiff = tools_dir / f"objdiff-cli{ext}"
    delink = tools_dir / f"delink{ext}"
    compilers_dir = Path("build") / "compilers"
    cl = compilers_dir / "Win32" / "7.1" / "cl.exe"
    wrapper = args.wrapper
    wibo = None
    if wrapper is None and os.name != "nt":
        wibo = tools_dir / "wibo"
        wrapper = str(wibo)
    # objdiff runs this to rebuild objects; prefer the ninja installed next to this Python.
    local_ninja = Path(sys.executable).parent / f"ninja{ext}"
    ninja_exe = str(local_ninja) if local_ninja.is_file() else shutil.which("ninja") or "ninja"

    python = sys.executable
    n = ninja_syntax.Writer(open("build.ninja", "w", encoding="utf-8"), width=120)
    n.comment(f"Generated by configure.py for {version}. Do not edit.")
    n.variable("ninja_required_version", "1.10")
    n.variable("python", python)
    n.newline()

    n.rule("download_tool", f"$python tools/download_tool.py $tool $dest --tag $tag", description="TOOL $out")
    # path is what ninja checks for freshness; dest is download_tool.py's own --output
    # argument. They differ for "compilers": it extracts a whole tree, and cl.exe
    # (part of that tree) stands in as the one file ninja can watch.
    # wibo is fetched only when it will actually be used as the compiler wrapper.
    for tool, path, dest in (
        ("objdiff-cli", objdiff, objdiff),
        ("delink", delink, delink),
        ("compilers", cl, compilers_dir),
    ) + ((("wibo", wibo, wibo),) if wibo else ()):
        n.build(str(path), "download_tool", implicit="tools/download_tool.py",
                variables={"tool": tool, "tag": TOOL_TAGS[tool], "dest": str(dest)})
    n.newline()

    # -- split -----------------------------------------------------------------
    model = build_dir / "delink.json"
    groups = build_dir / "idapro.json"
    obj_dir = build_dir / "obj"
    split_stamp = build_dir / "split.stamp"
    n.rule(
        "model",
        f"$python tools/delink_model.py --exe $exe --sha1 $sha1 --symbols $symbols --splits $splits "
        f"--chunk-size {CHUNK_SIZE:#x} --model $model --groups $groups",
        description="MODEL $model",
    )
    n.build(
        [str(model), str(groups)], "model",
        inputs=[str(exe), str(symbols_txt), str(splits_txt)],
        implicit=["tools/delink_model.py", "tools/splits.py", "tools/symbols.py", "tools/pe.py"],
        variables={"exe": str(exe), "sha1": info["sha1"], "symbols": str(symbols_txt),
                   "splits": str(splits_txt), "model": str(model), "groups": str(groups)},
    )
    n.rule(
        "split",
        "$python tools/split.py --delink $delink --model $model --exe $exe --groups $groups "
        "--outdir $outdir --stamp $out",
        description="SPLIT $exe",
    )
    target_objs = [str(obj_dir / u.object) for u in units] + [str(obj_dir / "__shared_data.obj")]
    n.build(
        str(split_stamp), "split",
        inputs=[str(model), str(groups)],
        implicit=[str(delink), "tools/split.py"],
        implicit_outputs=target_objs,
        variables={"delink": str(delink), "model": str(model), "exe": str(exe),
                   "groups": str(groups), "outdir": str(obj_dir)},
    )
    n.newline()

    # -- compile -----------------------------------------------------------------
    # Natively, cl.exe needs the VC 7.1 runtime next to it (wibo provides its own).
    runtime_dlls: List[str] = []
    if not wrapper:
        runtime = Path(args.msvc_runtime) if args.msvc_runtime else None
        if runtime is None or not all((runtime / d).is_file() for d in ("msvcr71.dll", "msvcp71.dll")):
            sys.exit(
                "cl.exe 13.10 needs msvcr71.dll and msvcp71.dll (VC++ .NET 2003 runtime, shipped with "
                "many 2003-2006 games). Pass --msvc-runtime <dir containing both> or set MSVC71_RUNTIME."
            )
        n.rule("copy", f'$python -c "import shutil,sys; shutil.copyfile(sys.argv[1], sys.argv[2])" $in $out',
               description="COPY $out")
        for dll in ("msvcr71.dll", "msvcp71.dll"):
            dest = cl.parent / dll
            n.build(str(dest), "copy", inputs=str(runtime / dll), implicit=str(cl))
            runtime_dlls.append(str(dest))
    cl_cmd = f"{wrapper} {cl}" if wrapper else str(cl)
    includes = f"/I{compilers_dir / 'Win32' / '7.1' / 'Include'} /Iinclude /Isrc"
    n.rule(
        "cc",
        f"{cl_cmd} /nologo /c /X {includes} $cflags /showIncludes /Fo$out $in",
        description="CC $in",
        deps="msvc",
    )
    base_objs: List[str] = []
    unit_json = []
    for u in units:
        opts = options.get(u.source, {})
        source = Path("src") / u.source
        base = None
        if not u.auto and source.is_file():
            base = build_dir / "src" / u.object
            n.build(str(base), "cc", inputs=str(source),
                    implicit=[str(cl), *runtime_dlls] + ([str(wibo)] if wibo else []),
                    variables={"cflags": " ".join(opts.get("cflags", CFLAGS))})
            base_objs.append(str(base))
        metadata = {"auto_generated": u.auto}
        if base:
            metadata["source_path"] = str(source).replace(os.sep, "/")
        if opts.get("status") == "Matching":
            metadata["complete"] = True
        metadata["progress_categories"] = unit_categories(u, opts.get("category", ""))
        unit_json.append({
            "name": u.name,
            "target_path": str(obj_dir / u.object).replace(os.sep, "/"),
            **({"base_path": str(base).replace(os.sep, "/")} if base else {}),
            "metadata": metadata,
        })
    unit_json.append({
        "name": "__shared_data",
        "target_path": str(obj_dir / "__shared_data.obj").replace(os.sep, "/"),
        "metadata": {"auto_generated": True},
    })
    n.build("all_source", "phony", inputs=base_objs)
    n.newline()

    # -- report ------------------------------------------------------------------
    report = build_dir / "report.json"
    n.rule("report", f"{objdiff} report generate -o $out", description="REPORT $out")
    n.build(str(report), "report", implicit=[str(objdiff), "objdiff.json", str(split_stamp), *base_objs])
    n.rule("progress", "$python tools/progress.py $in", description="PROGRESS", pool="console")
    n.build("progress", "progress", inputs=str(report))
    n.newline()

    reconfigure = f"$python configure.py --version {version}"
    if args.wrapper:
        reconfigure += f' --wrapper "{args.wrapper}"'
    if args.msvc_runtime:
        reconfigure += f' --msvc-runtime "{args.msvc_runtime}"'
    n.rule("configure", reconfigure, generator=True, description="CONFIGURE")
    n.build(["build.ninja", "objdiff.json"], "configure",
            implicit=["configure.py", "tools/splits.py", "tools/symbols.py", str(symbols_txt), str(splits_txt)])
    n.default("progress")
    n.close()

    objdiff_json = {
        "$schema": "https://raw.githubusercontent.com/encounter/objdiff/main/config.schema.json",
        "custom_make": ninja_exe,
        "build_target": False,
        "build_base": True,
        "watch_patterns": ["*.c", "*.cpp", "*.h", "*.hpp", "*.inl", "*.txt", "*.py"],
        # A call to the wrong function must not count as matched: `report
        # generate` ignores relocation targets unless told otherwise. The real
        # gate is tools/agent/accept.py (docs/matching.md).
        "options": {"functionRelocDiffs": "name_address"},
        "units": unit_json,
        "progress_categories": [{"id": k, "name": v} for k, v in CATEGORIES.items()],
    }
    Path("objdiff.json").write_text(json.dumps(objdiff_json, indent=2) + "\n", encoding="utf-8")
    auto = sum(u.auto for u in units)
    print(f"{version}: {len(units) - auto} declared units, {auto} auto units, {len(base_objs)} with source")


if __name__ == "__main__":
    main()
