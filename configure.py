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

import categories as categorieslib  # noqa: E402
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
#   "cflags":   replaces CFLAGS for this unit
UNITS: Dict[str, dict] = {}

# Built without optimization: every method spills `this` to [ebp-4] (docs/matching.md, "/Od units").
OD_CFLAGS = ["/Od" if flag == "/O2" else flag for flag in CFLAGS]

# Address ranges whose functions belong to a unit before they are matched: the gate compiles them with
# the unit's flags and integrate.py puts them there. splits.txt declares only what src/ holds.
UNIT_RANGES = [
    (0x10BF7810, 0x10BF7990, "Game/Unsorted_10BF7810.cpp"),
    (0x10BF79D0, 0x10BF7AD0, "Game/Unsorted_10BF79D0.cpp"),
    (0x10BF8F00, 0x10BF8F5C, "Game/Unsorted_10BF8F00.cpp"),
]
for _start, _end, _source in UNIT_RANGES:
    UNITS[_source] = {"cflags": OD_CFLAGS}

# objdiff/decomp.dev progress categories, from config/<version>/categories.txt
# (tools/classify.py). "main" is the headline (decomp.dev's default category):
# Ion Storm's game code, which the decompilation covers. Epic's engine and the
# third-party libraries stay in the binary; they are reported for reference.
CATEGORIES = {
    "main": "Game",
    "engine": "Engine (Epic)",
    "libs": "Libraries",
    "unknown": "Unclassified",
}
PROGRESS_CATEGORY = {
    categorieslib.GAME: "main",
    categorieslib.ENGINE: "engine",
    categorieslib.LIBS: "libs",
    categorieslib.UNKNOWN: "unknown",
}

# Where code comes from by address, when categories.txt has no range for it.
# Code before LIBRARY_START is the game and Epic's engine (tools/classify.py
# tells them apart), with Havok before it too. The libraries linked after it
# start there: qhull, then the static C runtime from 0x10D1EE33 (entry point
# 0x10D1F7AF), then mostly STL, D3DX, Havok and libjpeg. .text$x holds the
# exception-handling funclets of every function, which the compiler emits with
# their parents (docs/target.md): a declared unit takes its functions'
# funclets, and the rest are not reported.
LIBRARY_START = 0x10CFBFB0
FUNCLETS = (0x10E02DA0, 0x10E3BF77)


def category_index(config_dir: Path) -> categorieslib.Index:
    return categorieslib.Index(categorieslib.load(config_dir / "categories.txt"))


def unit_categories(unit: splitslib.Unit, index: categorieslib.Index) -> List[str]:
    """The progress categories of a unit: its first .text range's in categories.txt."""
    start = unit.text[0][0] if unit.text else 0
    if FUNCLETS[0] <= start < FUNCLETS[1]:
        return []
    category = index.at(start)
    if not category:
        return ["main"] if start < LIBRARY_START else ["libs"]
    return [PROGRESS_CATEGORY[category]]


def reported(unit: splitslib.Unit) -> bool:
    """Whether the progress report holds a unit: all but the leftover .text$x funclets."""
    return not (unit.auto and unit.text and FUNCLETS[0] <= unit.text[0][0] < FUNCLETS[1])


def unit_options(config_dir: Path) -> Dict[str, dict]:
    """UNITS, plus per-unit options from config/<version>/units.json, if there
    is one; UNITS wins where both set one."""
    options = {source: dict(opts) for source, opts in UNITS.items()}
    units_json = config_dir / "units.json"
    if units_json.is_file():
        for source, opts in json.loads(units_json.read_text(encoding="utf-8")).items():
            options[source] = {**opts, **options.get(source, {})}
    return options


def breaks(config_dir: Path) -> List[int]:
    """Addresses no auto unit may span: the category boundaries and the regions' edges."""
    return sorted({LIBRARY_START, *FUNCLETS, *category_index(config_dir).boundaries()})


def plan_units(config_dir: Path) -> List[splitslib.Unit]:
    """The translation units: those declared in splits.txt, plus auto chunks
    covering every other function in symbols.txt."""
    functions = [s for s in symbolslib.load(config_dir / "symbols.txt") if s.is_function and s.size > 0]
    return splitslib.plan(splitslib.load(config_dir / "splits.txt"), functions, CHUNK_SIZE,
                          breaks=breaks(config_dir))


def write_aliases(symbols_txt: Path, out: Path) -> None:
    """{alias: the address's own name} from symbols.txt's `type:alias` lines, for tools/cc.py. Written only
    when it changes, so the objects are rebuilt only then."""
    symbols = symbolslib.load(symbols_txt)
    own: Dict[int, str] = {}
    for s in symbols:
        if s.type != "alias" and (s.is_function or s.address not in own):
            own[s.address] = s.name  # a function wins over a label at its address, as in the agent tools
    aliases = {s.name: own[s.address] for s in symbols if s.type == "alias" and s.address in own}
    text = json.dumps(aliases, indent=1, sort_keys=True) + "\n"
    if not out.is_file() or out.read_text(encoding="utf-8") != text:
        out.parent.mkdir(parents=True, exist_ok=True)
        out.write_text(text, encoding="utf-8")


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
    categories_txt = config_dir / "categories.txt"
    options = unit_options(config_dir)
    index = category_index(config_dir)

    if not exe.is_file():
        print(f"warning: {exe} is missing; copy it from the game's System/ folder (see README.md)")

    units = plan_units(config_dir)
    ranged = {source for _, _, source in UNIT_RANGES}  # declared once they hold a function
    for source in options:
        if source not in ranged and not any(u.source == source for u in units):
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
        f"--categories $categories --chunk-size {CHUNK_SIZE:#x} "
        f"{' '.join(f'--break {b:#x}' for b in (LIBRARY_START, *FUNCLETS))} --model $model --groups $groups",
        description="MODEL $model",
    )
    n.build(
        [str(model), str(groups)], "model",
        inputs=[str(exe), str(symbols_txt), str(splits_txt)],
        implicit=["tools/delink_model.py", "tools/splits.py", "tools/symbols.py", "tools/pe.py",
                  "tools/categories.py"] + ([str(categories_txt)] if categories_txt.is_file() else []),
        variables={"exe": str(exe), "sha1": info["sha1"], "symbols": str(symbols_txt),
                   "splits": str(splits_txt), "categories": str(categories_txt), "model": str(model),
                   "groups": str(groups)},
    )
    n.rule(
        "split",
        "$python tools/split.py --delink $delink --model $model --exe $exe --groups $groups "
        "--outdir $outdir --symbols $symbols --stamp $out",
        description="SPLIT $exe",
    )
    target_objs = [str(obj_dir / u.object) for u in units] + [str(obj_dir / "__shared_data.obj")]
    n.build(
        str(split_stamp), "split",
        inputs=[str(model), str(groups)],
        implicit=[str(delink), "tools/split.py", "tools/agent/coff.py", "tools/symbols.py", str(symbols_txt)],
        implicit_outputs=target_objs,
        variables={"delink": str(delink), "model": str(model), "exe": str(exe),
                   "groups": str(groups), "outdir": str(obj_dir), "symbols": str(symbols_txt)},
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
    # Every object goes through tools/cc.py, which gives references to an address's other names (symbols.txt
    # aliases) the address's own name. The rule names Python itself: the agent tools run it outside ninja.
    aliases_json = build_dir / "aliases.json"
    write_aliases(symbols_txt, aliases_json)
    cc_deps = ["tools/cc.py", "tools/agent/coff.py", str(aliases_json)]
    n.rule(
        "cc",
        f'"{python}" tools/cc.py --aliases {aliases_json} -- '
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
                    implicit=[str(cl), *runtime_dlls, *cc_deps] + ([str(wibo)] if wibo else []),
                    variables={"cflags": " ".join(opts.get("cflags", CFLAGS))})
            base_objs.append(str(base))
        if not reported(u):
            continue
        metadata = {"auto_generated": u.auto}
        if base:
            metadata["source_path"] = str(source).replace(os.sep, "/")
        if opts.get("status") == "Matching":
            metadata["complete"] = True
        metadata["progress_categories"] = unit_categories(u, index)
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
            implicit=["configure.py", "tools/splits.py", "tools/symbols.py", "tools/categories.py", str(symbols_txt),
                      str(splits_txt)] + ([str(categories_txt)] if categories_txt.is_file() else []))
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
