#!/usr/bin/env python3
"""Check, build and inspect .t3mod mod packages (docs/mods.md).

  validate <mod.json | folder | .t3mod> ...
      check a manifest on its own, a folder as `pack` would package it, or a
      package: the manifest rules, safe paths, something to install, the
      entry DLL at the root, nothing under files/System/, only .dds files in
      textures/. Large or unusual files get a warning; every entry of a
      .t3mod is unpacked to catch damage.
  pack <folder> [-o <out.t3mod | folder>] [--with-pdb]
      validate the folder, then write <id>-<version>.t3mod (into the current
      folder unless -o says otherwise): a zip with sorted entries, fixed
      timestamps and deflate, so the same files always give the same bytes.
      Skips .git, .gitkeep, Thumbs.db, .DS_Store, desktop.ini, .t3mod files,
      and *.pdb unless --with-pdb.
  info <.t3mod>
      print the manifest, the files, and the package's size and SHA-256

Errors exit with status 1; warnings do not. Python 3.10+, standard library only.
"""

from __future__ import annotations

import argparse
import json
import sys
from pathlib import Path
from typing import List

sys.path.insert(0, str(Path(__file__).resolve().parent / "mods"))
import t3modlib  # noqa: E402
from t3modlib import Package, Problem  # noqa: E402


def report(label: str, problems: List[Problem]) -> bool:
    """Print the problems; True when there is no error."""
    for p in problems:
        print(f"{'warning' if p.warning else 'error'}: {label}: {p}")
    return not t3modlib.errors(problems)


def is_manifest(path: Path) -> bool:
    return path.is_file() and path.suffix.lower() == ".json"


def validate(path: Path, with_pdb: bool) -> bool:
    if not path.exists():
        print(f"error: {path}: no such file or folder")
        return False
    if is_manifest(path):
        manifest, problems = t3modlib.load_manifest_file(path)
        ok = report(str(path), problems)
        if ok and manifest is not None:
            print(f"{path}: {manifest['id']} {manifest['version']}: manifest ok")
        return ok
    package = t3modlib.read_any(path, with_pdb)
    ok = report(str(path), package.problems)
    if ok and package.manifest is not None:
        size = sum(e.size for e in package.entries)
        print(f"{path}: {package.manifest['id']} {package.manifest['version']}: ok "
              f"({len(package.entries)} files, {size} bytes, {len(package.warnings)} warnings)")
    return ok


def cmd_validate(args: argparse.Namespace) -> int:
    results = [validate(Path(p), args.with_pdb) for p in args.paths]
    return 0 if all(results) else 1


def cmd_pack(args: argparse.Namespace) -> int:
    folder = Path(args.folder)
    if not folder.is_dir():
        print(f"error: {folder}: not a folder")
        return 1
    out_arg = Path(args.output) if args.output else Path.cwd()
    into_folder = not args.output or out_arg.is_dir() or args.output.endswith(("/", "\\"))
    package = t3modlib.read_folder(folder, args.with_pdb, exclude=[] if into_folder else [out_arg])
    if not report(str(folder), package.problems) or package.manifest is None:
        print(f"{folder}: not packed")
        return 1
    out = out_arg / package.file_name if into_folder else out_arg
    out.parent.mkdir(parents=True, exist_ok=True)
    t3modlib.write_package(package, out)
    # Read back what was written: the package must pass on its own.
    written = t3modlib.read_zip(out)
    if written.errors:
        report(str(out), written.errors)
        return 1
    print(f"wrote {out}: {package.manifest['id']} {package.manifest['version']}, {len(package.entries)} files, "
          f"{out.stat().st_size} bytes, sha256 {t3modlib.sha256_file(out)}")
    return 0


def cmd_info(args: argparse.Namespace) -> int:
    path = Path(args.package)
    if not path.is_file():
        print(f"error: {path}: no such file")
        return 1
    package: Package = t3modlib.read_zip(path)
    print(f"{path}")
    print(f"  size    {path.stat().st_size} bytes")
    print(f"  sha256  {t3modlib.sha256_file(path)}")
    if package.manifest is not None:
        print(f"\n{t3modlib.MANIFEST}")
        for line in json.dumps(package.manifest, indent=2, ensure_ascii=False).splitlines():
            print(f"  {line}")
    total = sum(e.size for e in package.entries)
    print(f"\nfiles ({len(package.entries)}, {total} bytes unpacked)")
    width = len(str(max((e.size for e in package.entries), default=0)))
    for e in sorted(package.entries, key=lambda e: e.path):
        print(f"  {e.size:>{width}}  {e.path}")
    if package.problems:
        print()
    return 0 if report(str(path), package.problems) else 1


def main(argv: List[str] | None = None) -> int:
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = parser.add_subparsers(dest="command", required=True)
    v = sub.add_parser("validate", help="check a mod.json, a mod folder or a .t3mod")
    v.add_argument("paths", nargs="+", help="mod.json, a folder with one, or a .t3mod")
    v.add_argument("--with-pdb", action="store_true", help="for a folder: count *.pdb files in, as pack --with-pdb")
    p = sub.add_parser("pack", help="validate a folder and write <id>-<version>.t3mod")
    p.add_argument("folder")
    p.add_argument("-o", "--output", help="the package to write, or the folder to write it into (default: .)")
    p.add_argument("--with-pdb", action="store_true", help="include *.pdb files (debug symbols)")
    i = sub.add_parser("info", help="print a package's manifest, files and SHA-256")
    i.add_argument("package")
    args = parser.parse_args(argv)
    return {"validate": cmd_validate, "pack": cmd_pack, "info": cmd_info}[args.command](args)


if __name__ == "__main__":
    sys.exit(main())
