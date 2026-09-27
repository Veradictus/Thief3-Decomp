#!/usr/bin/env python3
"""Build, deploy and run T3SDK, the Thief: Deadly Shadows modding SDK.

  build      compile sdk/ with MSVC for 32-bit x86 into build/sdk/bin/
  deploy     copy build/sdk/bin/ into the game's System/ folder
  undeploy   remove exactly what deploy installed
  run        start the game, through Steam for a Steam install (extra arguments
             go to the game, e.g. LOG=T3.log)
  log        print System/T3SDK.log

The game folder comes from --game-dir, then $T3_GAME_DIR, then the ION_ROOT
registry value the game's installer writes.
"""

import argparse
import hashlib
import json
import os
import re
import shutil
import subprocess
import sys
from pathlib import Path
from typing import Dict, List, Optional

ROOT = Path(__file__).resolve().parent.parent
BUILD = ROOT / "build" / "sdk"
BIN = BUILD / "bin"
MANIFEST = BUILD / "deployed.json"
SUPPORTED_SHA1 = "40bf68a54246bcde2fb5fcbc75b94dc7c7f78305"  # T3Main.exe, PC_20040610
STEAM_APP_ID = "6980"  # Thief: Deadly Shadows


def msvc_x86_env() -> Dict[str, str]:
    """Environment of `vcvarsall.bat x86` from the newest Visual Studio with C++ tools."""
    program_files = os.environ.get("ProgramFiles(x86)", r"C:\Program Files (x86)")
    vswhere = Path(program_files) / "Microsoft Visual Studio" / "Installer" / "vswhere.exe"
    if not vswhere.is_file():
        sys.exit("vswhere.exe not found: install Visual Studio with 'Desktop development with C++'")
    found = subprocess.run(
        [str(vswhere), "-latest", "-products", "*", "-requires",
         "Microsoft.VisualStudio.Component.VC.Tools.x86.x64", "-property", "installationPath"],
        capture_output=True, text=True,
    ).stdout.split("\n")[0].strip()
    if not found:
        sys.exit("no Visual Studio installation with the MSVC x86/x64 tools found")
    vcvars = Path(found) / "VC" / "Auxiliary" / "Build" / "vcvarsall.bat"
    out = subprocess.run(f'cmd /s /c ""{vcvars}" x86 >nul && set"', capture_output=True, text=True).stdout
    env = dict(line.split("=", 1) for line in out.splitlines() if "=" in line)
    if "VCToolsInstallDir" not in env:
        sys.exit(f"{vcvars} x86 did not set up MSVC")
    return env


def run(cmd: List[str], env: Dict[str, str]) -> None:
    print("+", " ".join(str(c) for c in cmd), flush=True)
    if subprocess.call([str(c) for c in cmd], env=env) != 0:
        sys.exit(1)


def game_dir(args: argparse.Namespace) -> Path:
    if args.game_dir:
        return Path(args.game_dir)
    if os.environ.get("T3_GAME_DIR"):
        return Path(os.environ["T3_GAME_DIR"])
    if os.name == "nt":
        import winreg

        for view in (winreg.KEY_WOW64_32KEY, winreg.KEY_WOW64_64KEY):
            try:
                key = winreg.OpenKey(winreg.HKEY_LOCAL_MACHINE, r"SOFTWARE\Ion Storm\Thief - Deadly Shadows",
                                     0, winreg.KEY_READ | view)
                with key:
                    return Path(winreg.QueryValueEx(key, "ION_ROOT")[0])
            except OSError:
                pass
    sys.exit("game folder not found: pass --game-dir or set T3_GAME_DIR")


def system_dir(args: argparse.Namespace) -> Path:
    system = game_dir(args) / "System"
    if not (system / "T3Main.exe").is_file():
        sys.exit(f"{system} has no T3Main.exe")
    return system


def cmd_build(args: argparse.Namespace) -> None:
    env = msvc_x86_env()
    ninja = shutil.which("ninja") or str(Path(sys.executable).parent / "ninja.exe")
    cmake = shutil.which("cmake", path=env.get("Path") or env.get("PATH")) or "cmake"
    run([cmake, "-S", ROOT / "sdk", "-B", BUILD, "-G", "Ninja", f"-DCMAKE_MAKE_PROGRAM={ninja}",
         f"-DCMAKE_BUILD_TYPE={args.config}", "-DCMAKE_C_COMPILER=cl", "-DCMAKE_CXX_COMPILER=cl"], env)
    run([cmake, "--build", BUILD], env)


def cmd_deploy(args: argparse.Namespace) -> None:
    system = system_dir(args)
    sha1 = hashlib.sha1((system / "T3Main.exe").read_bytes()).hexdigest()
    if sha1 != SUPPORTED_SHA1:
        print(f"warning: {system / 'T3Main.exe'} is not the supported build ({sha1}); the SDK will stay disabled")
    if not (BIN / "dinput8.dll").is_file():
        sys.exit("nothing to deploy: run `tools/sdk.py build` first")
    previous = set(json.loads(MANIFEST.read_text())["files"]) if MANIFEST.is_file() else set()

    installed: List[str] = []
    for src in sorted(BIN.rglob("*")):  # sorted: a deterministic manifest, regardless of filesystem order
        if not src.is_file() or src.suffix.lower() not in (".dll", ".pdb", ".ini"):
            continue
        rel = src.relative_to(BIN).as_posix()
        dst = system / rel
        if dst.exists() and rel not in previous:
            if rel == "T3SDK.ini":
                continue  # the user's own settings
            sys.exit(f"{dst} exists and was not installed by this tool; move it away first")
        dst.parent.mkdir(parents=True, exist_ok=True)
        shutil.copy2(src, dst)
        installed.append(rel)
    MANIFEST.write_text(json.dumps({"system": str(system), "files": installed}, indent=1), encoding="utf-8")
    print(f"deployed {len(installed)} files to {system}")


def cmd_undeploy(args: argparse.Namespace) -> None:
    if not MANIFEST.is_file():
        sys.exit("nothing deployed (no build/sdk/deployed.json)")
    data = json.loads(MANIFEST.read_text())
    system = Path(data["system"])
    for rel in data["files"]:
        (system / rel).unlink(missing_ok=True)
    mods = system / "mods"
    if mods.is_dir() and not any(mods.iterdir()):
        mods.rmdir()
    MANIFEST.unlink()
    print(f"removed {len(data['files'])} files from {system}")


def steam_install(game: Path) -> bool:
    """Whether `game` is Steam's install of the game: its library lists it in the app manifest."""
    # game is steamapps/common/<installdir>/; the manifest lives two levels up, in steamapps/.
    manifest = game.parent.parent / f"appmanifest_{STEAM_APP_ID}.acf"
    if not manifest.is_file():
        return False
    found = re.search(r'"installdir"\s+"([^"]*)"', manifest.read_text(encoding="utf-8", errors="replace"))
    return bool(found) and found.group(1).lower() == game.name.lower()


def steam_exe() -> Optional[Path]:
    if os.name != "nt":
        return None
    import winreg

    try:
        with winreg.OpenKey(winreg.HKEY_CURRENT_USER, r"Software\Valve\Steam") as key:
            exe = Path(winreg.QueryValueEx(key, "SteamExe")[0])
    except OSError:
        return None
    return exe if exe.is_file() else None


def cmd_run(args: argparse.Namespace) -> None:
    system = system_dir(args)
    extra = " ".join(args.game_args)
    if steam_install(system.parent):
        # The way Steam's Play button starts it: through Steam and the game's own launcher.
        steam = steam_exe()
        if steam:
            subprocess.Popen([str(steam), "-applaunch", STEAM_APP_ID, *args.game_args])
        elif args.game_args:
            sys.exit("steam.exe not found in the registry; start the game without arguments or from Steam")
        else:
            os.startfile(f"steam://rungameid/{STEAM_APP_ID}")
        print(f"asked Steam to start the game (app {STEAM_APP_ID}) {extra}".rstrip())
        return
    subprocess.Popen([str(system / "T3Main.exe"), *args.game_args], cwd=system)
    print(f"started {system / 'T3Main.exe'} {extra}".rstrip())


def cmd_log(args: argparse.Namespace) -> None:
    log = system_dir(args) / "T3SDK.log"
    if not log.is_file():
        sys.exit(f"no {log} yet")
    sys.stdout.write(log.read_text(encoding="utf-8", errors="replace"))


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("--game-dir", help="Thief: Deadly Shadows install folder")
    sub = parser.add_subparsers(dest="cmd", required=True)
    build = sub.add_parser("build")
    build.add_argument("--config", default="RelWithDebInfo", choices=["Debug", "RelWithDebInfo", "Release"])
    run = sub.add_parser("run")
    run.add_argument("game_args", nargs=argparse.REMAINDER, help="arguments passed to T3Main.exe")
    for name in ("deploy", "undeploy", "log"):
        sub.add_parser(name)
    args = parser.parse_args()
    commands = {"build": cmd_build, "deploy": cmd_deploy, "undeploy": cmd_undeploy, "run": cmd_run, "log": cmd_log}
    commands[args.cmd](args)


if __name__ == "__main__":
    main()
