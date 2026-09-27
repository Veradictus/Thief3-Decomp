#!/usr/bin/env python3
"""Download a pinned build tool into build/.

  objdiff-cli  encounter/objdiff release binary
  delink       dbalatoni13/delink release binary (splits the exe into COFF objects)
  wibo         decompals/wibo, runs the Win32 compiler on Linux/macOS
  compilers    dbalatoni13/compilers bundle; only Win32/7.1 (MSVC 13.10.3077) is extracted
"""

import argparse
import io
import os
import platform
import shutil
import stat
import sys
import urllib.request
import zipfile
from pathlib import Path


def host() -> tuple:
    system = platform.system().lower()
    system = {"darwin": "macos"}.get(system, system)
    arch = platform.machine().lower()
    arch = {"amd64": "x86_64", "aarch64": "arm64"}.get(arch, arch)
    return system, arch, ".exe" if system == "windows" else ""


def url_for(tool: str, tag: str) -> str:
    system, arch, ext = host()
    if tool == "objdiff-cli":
        return f"https://github.com/encounter/objdiff/releases/download/{tag}/objdiff-cli-{system}-{arch}{ext}"
    if tool == "delink":
        return f"https://github.com/dbalatoni13/delink/releases/download/{tag}/delink-{system}-{arch}{ext}"
    if tool == "wibo":
        name = "wibo-macos" if system == "macos" else "wibo-x86_64"
        return f"https://github.com/decompals/wibo/releases/download/{tag}/{name}"
    if tool == "compilers":
        return f"https://github.com/dbalatoni13/compilers/releases/download/compilers_{tag}/compilers_{tag}.zip"
    sys.exit(f"unknown tool {tool}")


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("tool", choices=["objdiff-cli", "delink", "wibo", "compilers"])
    parser.add_argument("output", type=Path, help="file to write (for compilers: the directory to extract into)")
    parser.add_argument("--tag", required=True)
    args = parser.parse_args()

    url = url_for(args.tool, args.tag)
    print(f"downloading {url}")
    req = urllib.request.Request(url, headers={"User-Agent": "thief3-decomp"})
    with urllib.request.urlopen(req) as response:
        payload = response.read()

    if args.tool == "compilers":
        prefix = "Win32/7.1/"
        with zipfile.ZipFile(io.BytesIO(payload)) as z:
            members = [m for m in z.namelist() if m.startswith(prefix)]
            if not members:
                sys.exit(f"{prefix} not found in the compiler bundle")
            shutil.rmtree(args.output / "Win32" / "7.1", ignore_errors=True)
            z.extractall(args.output, members)
        return

    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_bytes(payload)
    if os.name != "nt":
        args.output.chmod(args.output.stat().st_mode | stat.S_IXUSR | stat.S_IXGRP | stat.S_IXOTH)


if __name__ == "__main__":
    main()
