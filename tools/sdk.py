#!/usr/bin/env python3
"""Build, deploy and run T3SDK, the Thief: Deadly Shadows modding SDK.

  build      compile sdk/ with MSVC for 32-bit x86 into build/sdk/bin/
  deploy     copy build/sdk/bin/ into the game's System/ folder
  undeploy   remove exactly what deploy installed
  run        start the game, through Steam for a Steam install (extra arguments
             go to the game, e.g. LOG=T3.log)
  close      ask a running game to quit (WM_CLOSE) and report how long it took
  click      click in the game window (posted messages: the real cursor does not move)
  keys       press keys in the game window (only while it is in the foreground)
  screenshot capture the game window to a PNG (build/sdk/screenshot.png)
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
import time
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


def game_pids() -> List[int]:
    out = subprocess.run(["tasklist", "/FI", "IMAGENAME eq T3Main.exe", "/FO", "CSV", "/NH"],
                         capture_output=True, text=True).stdout
    return [int(line.split(",")[1].strip('"')) for line in out.splitlines() if "T3Main" in line]


def game_running() -> bool:
    return bool(game_pids())


def describe_exit_code(code: int) -> str:
    names = {0: "clean exit", 0xC0000005: "access violation", 0xC00000FD: "stack overflow",
             0xC0000409: "stack buffer overrun", 0x80000003: "breakpoint"}
    return f"{code} (0x{code:08X}, {names.get(code, 'unknown')})"


def cmd_close(args: argparse.Namespace) -> None:
    pids = game_pids()
    if not pids:
        print("the game is not running")
        return
    import ctypes

    kernel32 = ctypes.WinDLL("kernel32", use_last_error=True)
    kernel32.OpenProcess.restype = ctypes.c_void_p
    SYNCHRONIZE, QUERY_LIMITED = 0x00100000, 0x1000
    handles = [kernel32.OpenProcess(SYNCHRONIZE | QUERY_LIMITED, False, pid) for pid in pids]

    subprocess.run(["taskkill", "/IM", "T3Main.exe"], capture_output=True)  # WM_CLOSE, like closing the window
    start = time.monotonic()
    while game_running() and time.monotonic() - start < args.timeout:
        time.sleep(0.25)
    elapsed = time.monotonic() - start
    if not game_running():
        for pid, handle in zip(pids, handles):
            code = ctypes.c_ulong()
            if handle and kernel32.GetExitCodeProcess(ctypes.c_void_p(handle), ctypes.byref(code)):
                print(f"the game (pid {pid}) exited {elapsed:.1f} s after WM_CLOSE with code "
                      f"{describe_exit_code(code.value)}")
            else:
                print(f"the game (pid {pid}) exited {elapsed:.1f} s after WM_CLOSE")
            if handle:
                kernel32.CloseHandle(ctypes.c_void_p(handle))
        return
    print(f"the game was still running {elapsed:.0f} s after WM_CLOSE", end="")
    if args.force:
        subprocess.run(["taskkill", "/F", "/IM", "T3Main.exe"], capture_output=True)
        print("; terminated it")
    else:
        print("; pass --force to terminate it")
        sys.exit(1)


def write_png(path: Path, width: int, height: int, bgra: bytes) -> None:
    """Minimal RGB PNG writer (standard library only)."""
    import struct
    import zlib

    rows = bytearray()
    for y in range(height):
        row = bgra[y * width * 4:(y + 1) * width * 4]
        rows.append(0)
        rgb = bytearray(width * 3)
        rgb[0::3], rgb[1::3], rgb[2::3] = row[2::4], row[1::4], row[0::4]
        rows += rgb

    def chunk(kind: bytes, data: bytes) -> bytes:
        return struct.pack(">I", len(data)) + kind + data + struct.pack(">I", zlib.crc32(kind + data) & 0xFFFFFFFF)

    header = struct.pack(">IIBBBBB", width, height, 8, 2, 0, 0, 0)
    path.write_bytes(b"\x89PNG\r\n\x1a\n" + chunk(b"IHDR", header) + chunk(b"IDAT", zlib.compress(bytes(rows), 6))
                     + chunk(b"IEND", b""))


def game_window() -> int:
    """The game's main window: its largest visible top-level window."""
    import ctypes
    import ctypes.wintypes as W

    pids = set(game_pids())
    if not pids:
        sys.exit("the game is not running")
    user32 = ctypes.WinDLL("user32")
    user32.SetProcessDPIAware()
    windows: List[int] = []

    @ctypes.WINFUNCTYPE(W.BOOL, W.HWND, W.LPARAM)
    def collect(hwnd, _):
        pid = W.DWORD()
        user32.GetWindowThreadProcessId(hwnd, ctypes.byref(pid))
        if pid.value in pids and user32.IsWindowVisible(hwnd):
            windows.append(hwnd)
        return True

    user32.EnumWindows(collect, 0)
    if not windows:
        sys.exit("no visible game window")

    def area(window: int) -> int:
        r = W.RECT()
        user32.GetWindowRect(window, ctypes.byref(r))
        return (r.right - r.left) * (r.bottom - r.top)

    return max(windows, key=area)


# DirectInput reads the keyboard itself, so keys are sent as scan codes.
KEYS = {"up": (0x48, True), "down": (0x50, True), "left": (0x4B, True), "right": (0x4D, True),
        "enter": (0x1C, False), "esc": (0x01, False), "space": (0x39, False), "tab": (0x0F, False)}


def cmd_keys(args: argparse.Namespace) -> None:
    import ctypes
    import ctypes.wintypes as W

    unknown = [k for k in args.keys if k.lower() not in KEYS]
    if unknown:
        sys.exit(f"unknown keys {unknown}; known: {', '.join(KEYS)}")
    hwnd = game_window()
    user32 = ctypes.WinDLL("user32")
    user32.GetForegroundWindow.restype = W.HWND

    class KEYBDINPUT(ctypes.Structure):
        _fields_ = [("wVk", W.WORD), ("wScan", W.WORD), ("dwFlags", W.DWORD), ("time", W.DWORD),
                    ("dwExtraInfo", ctypes.c_size_t)]

    class MOUSEINPUT(ctypes.Structure):  # the largest union member: sizes INPUT correctly
        _fields_ = [("dx", W.LONG), ("dy", W.LONG), ("mouseData", W.DWORD), ("dwFlags", W.DWORD),
                    ("time", W.DWORD), ("dwExtraInfo", ctypes.c_size_t)]

    class INPUT(ctypes.Structure):
        class _U(ctypes.Union):
            _fields_ = [("ki", KEYBDINPUT), ("mi", MOUSEINPUT)]
        _anonymous_ = ("u",)
        _fields_ = [("type", W.DWORD), ("u", _U)]

    def send(scan: int, extended: bool, up: bool) -> None:
        flags = 0x0008 | (0x0001 if extended else 0) | (0x0002 if up else 0)  # SCANCODE, EXTENDEDKEY, KEYUP
        event = INPUT(type=1)
        event.ki = KEYBDINPUT(0, scan, flags, 0, 0)
        user32.SendInput(1, ctypes.byref(event), ctypes.sizeof(INPUT))

    for name in args.keys:
        # Never type into another program: stop as soon as the game loses the foreground.
        if user32.GetForegroundWindow() != hwnd:
            sys.exit(f"the game window is not in the foreground; stopped before {name!r}")
        scan, extended = KEYS[name.lower()]
        send(scan, extended, up=False)
        time.sleep(args.hold)
        send(scan, extended, up=True)
        time.sleep(args.delay)
    print(f"pressed {' '.join(args.keys)}")


def cmd_click(args: argparse.Namespace) -> None:
    """Posts a left click to the game window. The viewport's window procedure
    reads mouse messages itself, so the real cursor and focus stay untouched."""
    import ctypes
    import ctypes.wintypes as W

    hwnd = game_window()
    user32 = ctypes.WinDLL("user32")
    rect = W.RECT()
    user32.GetClientRect(ctypes.c_void_p(hwnd), ctypes.byref(rect))
    x, y = int(args.x * rect.right), int(args.y * rect.bottom)
    point = (y << 16) | (x & 0xFFFF)
    for message, wparam in ((0x0200, 0), (0x0201, 1), (0x0202, 0)):  # WM_MOUSEMOVE, WM_LBUTTONDOWN, WM_LBUTTONUP
        user32.PostMessageW(ctypes.c_void_p(hwnd), message, wparam, point)
        time.sleep(args.delay)
    print(f"clicked at {x},{y} of the {rect.right}x{rect.bottom} game window")


def cmd_screenshot(args: argparse.Namespace) -> None:
    import ctypes
    import ctypes.wintypes as W

    hwnd = game_window()
    user32, gdi32 = ctypes.WinDLL("user32"), ctypes.WinDLL("gdi32")
    rect = W.RECT()
    user32.GetWindowRect(hwnd, ctypes.byref(rect))
    width, height = rect.right - rect.left, rect.bottom - rect.top
    screen = user32.GetDC(None)
    memdc = gdi32.CreateCompatibleDC(screen)
    bitmap = gdi32.CreateCompatibleBitmap(screen, width, height)
    gdi32.SelectObject(memdc, bitmap)
    user32.PrintWindow(hwnd, memdc, 2)  # PW_RENDERFULLCONTENT: includes Direct3D content

    class BITMAPINFOHEADER(ctypes.Structure):
        _fields_ = [("biSize", W.DWORD), ("biWidth", W.LONG), ("biHeight", W.LONG), ("biPlanes", W.WORD),
                    ("biBitCount", W.WORD), ("biCompression", W.DWORD), ("biSizeImage", W.DWORD),
                    ("biXPelsPerMeter", W.LONG), ("biYPelsPerMeter", W.LONG), ("biClrUsed", W.DWORD),
                    ("biClrImportant", W.DWORD)]

    info = BITMAPINFOHEADER(ctypes.sizeof(BITMAPINFOHEADER), width, -height, 1, 32, 0, 0, 0, 0, 0, 0)
    pixels = ctypes.create_string_buffer(width * height * 4)
    gdi32.GetDIBits(memdc, bitmap, 0, height, pixels, ctypes.byref(info), 0)
    gdi32.DeleteObject(bitmap)
    gdi32.DeleteDC(memdc)
    user32.ReleaseDC(None, screen)

    data = pixels.raw
    if args.max_width and width > args.max_width:  # nearest-neighbour downscale
        step = width / args.max_width
        new_w, new_h = args.max_width, int(height / step)
        scaled = bytearray(new_w * new_h * 4)
        for y in range(new_h):
            src_row = int(y * step) * width * 4
            for x in range(new_w):
                s = src_row + int(x * step) * 4
                scaled[(y * new_w + x) * 4:(y * new_w + x) * 4 + 4] = data[s:s + 4]
        data, width, height = bytes(scaled), new_w, new_h
    out = Path(args.output)
    write_png(out, width, height, data)
    print(f"saved {width}x{height} capture of the game window "
          f"({rect.right - rect.left}x{rect.bottom - rect.top} at {rect.left},{rect.top}) to {out}")


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
    close = sub.add_parser("close")
    close.add_argument("--timeout", type=float, default=30, help="seconds to wait for the game to exit")
    close.add_argument("--force", action="store_true", help="terminate the game if it has not exited by then")
    click = sub.add_parser("click")
    click.add_argument("x", type=float, help="0..1 across the game window")
    click.add_argument("y", type=float, help="0..1 down the game window")
    click.add_argument("--delay", type=float, default=0.15, help="seconds between move, press and release")
    keys = sub.add_parser("keys")
    keys.add_argument("keys", nargs="+", help=f"keys to press in order ({', '.join(KEYS)})")
    keys.add_argument("--delay", type=float, default=0.4, help="seconds between keys")
    keys.add_argument("--hold", type=float, default=0.1, help="seconds each key is held")
    shot = sub.add_parser("screenshot")
    shot.add_argument("-o", "--output", default=str(BUILD / "screenshot.png"))
    shot.add_argument("--max-width", type=int, default=1280, help="downscale wider captures (0 = full size)")
    for name in ("deploy", "undeploy", "log"):
        sub.add_parser(name)
    args = parser.parse_args()
    commands = {"build": cmd_build, "deploy": cmd_deploy, "undeploy": cmd_undeploy, "run": cmd_run,
                "close": cmd_close, "click": cmd_click, "keys": cmd_keys, "screenshot": cmd_screenshot, "log": cmd_log}
    commands[args.cmd](args)


if __name__ == "__main__":
    main()
