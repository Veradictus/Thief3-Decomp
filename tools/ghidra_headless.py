#!/usr/bin/env python3
"""Run Ghidra's analyzeHeadless against the project's Ghidra database.

Subcommands:
  import     Import orig/<version>/T3Main.exe into ghidra/ and auto-analyse it.
  analyze    Re-run auto-analysis on the already imported program.
  discover   Create functions auto-analysis missed
             (tools/ghidra/FindMissingFunctions.java), then re-analyse.
  names      Apply the names recorded in config/<version>/symbols.txt to the
             program (tools/ghidra/ImportNames.java): run it after naming
             something there, so decompiles show the name.
  export     Write config/<version>/symbols.txt from the analysed program
             (tools/ghidra/ExportSymbols.java).
  bootstrap  import, discover, discover, names, export: rebuilds the database
             from scratch, keeping the recorded names (about 12 minutes).
  script     Run any GhidraScript read-only: script <Script.java> [args...]
             (--write saves what the script changes)

Ghidra is located via --ghidra, then $GHIDRA_INSTALL_DIR, then the newest
ghidra_* directory under %LOCALAPPDATA%/Programs/Ghidra (Windows) or
~/ghidra (elsewhere).
"""

import argparse
import os
import subprocess
import sys
from pathlib import Path
from typing import List, Optional

ROOT = Path(__file__).resolve().parent.parent
DEFAULT_VERSION = "PC_20040610"
PROGRAM_NAME = "T3Main.exe"


def find_ghidra(explicit: Optional[str]) -> Path:
    candidates: List[Path] = []
    if explicit:
        candidates.append(Path(explicit))
    env = os.environ.get("GHIDRA_INSTALL_DIR")
    if env:
        candidates.append(Path(env))
    if os.name == "nt" and os.environ.get("LOCALAPPDATA"):
        base = Path(os.environ["LOCALAPPDATA"]) / "Programs" / "Ghidra"
    else:
        base = Path.home() / "ghidra"
    if base.is_dir():
        candidates.extend(sorted(base.glob("ghidra_*"), reverse=True))
    for candidate in candidates:
        if (candidate / "support").is_dir():
            return candidate
    sys.exit(
        "Ghidra not found. Pass --ghidra <install dir> or set GHIDRA_INSTALL_DIR."
    )


def headless(ghidra: Path, project_dir: Path, args: List[str]) -> int:
    """Run analyzeHeadless against the "T3Main" Ghidra project in `project_dir`.

    "T3Main" here is the Ghidra project name (a fixed choice for this repo),
    not PROGRAM_NAME (the imported program's name inside that project, used
    by -process elsewhere).
    """
    script = "analyzeHeadless.bat" if os.name == "nt" else "analyzeHeadless"
    project_dir.mkdir(parents=True, exist_ok=True)
    cmd = [str(ghidra / "support" / script), str(project_dir), "T3Main", *args]
    print("+", " ".join(cmd), flush=True)
    return subprocess.call(cmd)


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("--ghidra", help="Ghidra install directory")
    parser.add_argument("--project", type=Path, default=ROOT / "ghidra", help="Ghidra project directory (default: ghidra/)")
    parser.add_argument("--version", default=DEFAULT_VERSION, help=f"game version (default: {DEFAULT_VERSION})")
    parser.add_argument("--log", type=Path, help="write Ghidra's application log here")
    sub = parser.add_subparsers(dest="cmd", required=True)
    sub.add_parser("import", help="import and analyse orig/<version>/T3Main.exe")
    sub.add_parser("analyze", help="re-run auto-analysis")
    sub.add_parser("discover", help="create missed functions, then re-analyse")
    names = sub.add_parser("names", help="apply the names in config/<version>/symbols.txt")
    names.add_argument("-i", "--input", type=Path, help="symbols file (default: config/<version>/symbols.txt)")
    for name in ("export", "bootstrap"):
        exp = sub.add_parser(name, help="write config/<version>/symbols.txt" if name == "export"
                             else "import, discover twice, names, export")
        exp.add_argument("-o", "--output", type=Path, help="output path (default: config/<version>/symbols.txt)")
    run = sub.add_parser("script", help="run a GhidraScript read-only")
    run.add_argument("--write", action="store_true", help="save the script's changes to the database")
    run.add_argument("script", type=Path)
    run.add_argument("script_args", nargs=argparse.REMAINDER)
    args = parser.parse_args()

    ghidra = find_ghidra(args.ghidra)
    common: List[str] = []
    if args.log:
        common += ["-log", str(args.log)]
    scripts = ROOT / "tools" / "ghidra"
    exe = ROOT / "orig" / args.version / PROGRAM_NAME
    import_args = ["-import", str(exe), "-overwrite", *common]
    discover_args = ["-process", PROGRAM_NAME, "-scriptPath", str(scripts),
                     "-preScript", "FindMissingFunctions.java", *common]

    symbols_txt = ROOT / "config" / args.version / "symbols.txt"
    # Not read-only: the names are saved into the database.
    # getattr: --input is only defined on the "names" subparser; args has no
    # such attribute when this runs as part of "bootstrap".
    names_args = ["-process", PROGRAM_NAME, "-noanalysis", "-scriptPath", str(scripts),
                  "-postScript", "ImportNames.java", str((getattr(args, "input", None) or symbols_txt).resolve()),
                  *common]

    def export_args() -> List[str]:
        out = args.output or symbols_txt
        return ["-process", PROGRAM_NAME, "-noanalysis", "-readOnly", "-scriptPath", str(scripts),
                "-postScript", "ExportSymbols.java", str(out.resolve()), *common]

    if args.cmd in ("import", "bootstrap") and not exe.is_file():
        sys.exit(f"missing {exe}; see README.md")

    if args.cmd == "import":
        rc = headless(ghidra, args.project, import_args)
    elif args.cmd == "analyze":
        rc = headless(ghidra, args.project, ["-process", PROGRAM_NAME, *common])
    elif args.cmd == "discover":
        rc = headless(ghidra, args.project, discover_args)
    elif args.cmd == "names":
        rc = headless(ghidra, args.project, names_args)
    elif args.cmd == "export":
        rc = headless(ghidra, args.project, export_args())
    elif args.cmd == "bootstrap":
        rc = 0
        for step in (import_args, discover_args, discover_args, names_args, export_args()):
            rc = headless(ghidra, args.project, step)
            if rc != 0:
                break
    else:
        script = args.script.resolve()
        rc = headless(
            ghidra,
            args.project,
            [
                "-process", PROGRAM_NAME, "-noanalysis", *([] if args.write else ["-readOnly"]),
                "-scriptPath", str(script.parent),
                "-postScript", script.name, *args.script_args,
                *common,
            ],
        )
    sys.exit(rc)


if __name__ == "__main__":
    main()
