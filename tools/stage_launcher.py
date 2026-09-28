#!/usr/bin/env python3
"""Stage what the release launcher ships with, and pack the portable build.

  stage [--version X.Y.Z] [--sdk-bin DIR] [--no-sdk] [--no-python]
        [--updater-pubkey KEY [--updater-endpoint URL]]
      fill launcher/src-tauri/bundle/ and write tauri.bundle.conf.json there:
        t3sdk/tools/        sdk.py and the asset tools (tools/assets/)
        t3sdk/sdk/T3SDK.ini the settings template (descriptions for the launcher)
        t3sdk/build/sdk/bin the prebuilt SDK (dinput8.dll, mods, T3SDK.ini)
        t3sdk/LICENSE, t3sdk/THIRD_PARTY_NOTICES.md
                            the repository's notices, when it has them
        python/             CPython's embeddable build for Windows (x64), so
                            players need no Python of their own
      `yarn tauri build --config src-tauri/bundle/tauri.bundle.conf.json` then
      installs t3sdk/ and python/ next to the launcher.
      With --updater-pubkey (the public half of the key from `yarn tauri
      signer generate`), the config also turns on the in-app updater
      (plugins.updater) and signed update artifacts; the build then needs
      TAURI_SIGNING_PRIVATE_KEY. Without it the launcher has no updater.
      See docs/releasing.md.
  portable <launcher.exe> <out.zip>
      zip the built launcher with the staged folders: unzip anywhere and run.

The launcher finds t3sdk/ and python/ next to itself (its resource folder) and
sets T3SDK_BUILD_DIR so the tools write into the user's profile, not there.
Standard library only.
"""

import argparse
import hashlib
import io
import json
import shutil
import sys
import urllib.request
import zipfile
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
LAUNCHER = ROOT / "launcher" / "src-tauri"
STAGE = LAUNCHER / "bundle"

# CPython's embeddable package: the interpreter and its standard library, no
# installer. Pinned by hash; the tools need nothing beyond the standard library.
PYTHON_VERSION = "3.12.10"
PYTHON_URL = f"https://www.python.org/ftp/python/{PYTHON_VERSION}/python-{PYTHON_VERSION}-embed-amd64.zip"
PYTHON_SHA256 = "4acbed6dd1c744b0376e3b1cf57ce906f9dc9e95e68824584c8099a63025a3c3"

SKIP = shutil.ignore_patterns("__pycache__", "*.pyc")

# Where release builds look for updates: release.yml attaches latest.json to
# every release, and GitHub serves the newest non-prerelease one here.
UPDATER_ENDPOINT = "https://github.com/Veradictus/Thief3-Decomp/releases/latest/download/latest.json"

# Shipped with the tools when the repository has them.
NOTICES = ("LICENSE", "THIRD_PARTY_NOTICES.md")


def stage_tools(dest: Path) -> None:
    (dest / "tools").mkdir(parents=True)
    shutil.copy2(ROOT / "tools" / "sdk.py", dest / "tools" / "sdk.py")
    shutil.copytree(ROOT / "tools" / "assets", dest / "tools" / "assets", ignore=SKIP)
    (dest / "sdk").mkdir()
    shutil.copy2(ROOT / "sdk" / "T3SDK.ini", dest / "sdk" / "T3SDK.ini")


def stage_notices(dest: Path) -> list[str]:
    copied = []
    for name in NOTICES:
        if (ROOT / name).is_file():
            shutil.copy2(ROOT / name, dest / name)
            copied.append(name)
    return copied


def updater_config(pubkey: str, endpoint: str) -> dict:
    """tauri-plugin-updater's configuration: the launcher registers the plugin
    only when this is present (src-tauri/src/update.rs)."""
    return {"pubkey": pubkey, "endpoints": [endpoint], "windows": {"installMode": "passive"}}


def stage_sdk(dest: Path, sdk_bin: Path) -> int:
    if not (sdk_bin / "dinput8.dll").is_file():
        sys.exit(f"no dinput8.dll in {sdk_bin}: build the SDK first (tools/sdk.py build), or pass --no-sdk")
    out = dest / "build" / "sdk" / "bin"
    count = 0
    for src in sorted(sdk_bin.rglob("*")):
        if src.is_file() and src.suffix.lower() in (".dll", ".pdb", ".ini"):
            target = out / src.relative_to(sdk_bin)
            target.parent.mkdir(parents=True, exist_ok=True)
            shutil.copy2(src, target)
            count += 1
    return count


def stage_python(dest: Path) -> None:
    print(f"downloading {PYTHON_URL}")
    req = urllib.request.Request(PYTHON_URL, headers={"User-Agent": "thief3-decomp"})
    with urllib.request.urlopen(req) as response:
        payload = response.read()
    digest = hashlib.sha256(payload).hexdigest()
    if digest != PYTHON_SHA256:
        sys.exit(f"embeddable Python hash mismatch: got {digest}, expected {PYTHON_SHA256}")
    with zipfile.ZipFile(io.BytesIO(payload)) as z:
        z.extractall(dest)


def cmd_stage(args: argparse.Namespace) -> None:
    shutil.rmtree(STAGE, ignore_errors=True)
    t3sdk = STAGE / "t3sdk"
    stage_tools(t3sdk)
    resources = {"bundle/t3sdk/": "t3sdk/"}
    note = "tools"
    notices = stage_notices(t3sdk)
    if notices:
        note += f", {' and '.join(notices)}"
    if not args.no_sdk:
        note += f", {stage_sdk(t3sdk, Path(args.sdk_bin))} SDK files"
    if not args.no_python:
        stage_python(STAGE / "python")
        resources["bundle/python/"] = "python/"
        note += f", Python {PYTHON_VERSION}"
    config: dict = {"bundle": {"resources": resources}}
    if args.version:
        config["version"] = args.version
    # The key is one line of base64; a pasted repository variable may carry
    # line breaks or spaces.
    pubkey = "".join((args.updater_pubkey or "").split())
    if pubkey:
        config["bundle"]["createUpdaterArtifacts"] = True
        config["plugins"] = {"updater": updater_config(pubkey, args.updater_endpoint)}
        note += ", updater"
    (STAGE / "tauri.bundle.conf.json").write_text(json.dumps(config, indent=2) + "\n", encoding="utf-8")
    print(f"staged {note} in {STAGE}")


def cmd_portable(args: argparse.Namespace) -> None:
    exe = Path(args.exe)
    if not exe.is_file():
        sys.exit(f"no such file: {exe}")
    if not (STAGE / "t3sdk").is_dir():
        sys.exit(f"nothing staged in {STAGE}: run `stage` first")
    out = Path(args.out)
    out.parent.mkdir(parents=True, exist_ok=True)
    with zipfile.ZipFile(out, "w", zipfile.ZIP_DEFLATED) as z:
        z.write(exe, exe.name)
        for folder in ("t3sdk", "python"):
            for f in sorted((STAGE / folder).rglob("*")):
                if f.is_file():
                    z.write(f, f.relative_to(STAGE).as_posix())
    print(f"wrote {out} ({out.stat().st_size / 1e6:.1f} MB)")


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = parser.add_subparsers(dest="command", required=True)
    stage = sub.add_parser("stage")
    stage.add_argument("--version", help="launcher version for this build (semver, e.g. 0.2.0)")
    stage.add_argument("--sdk-bin", default=str(ROOT / "build" / "sdk" / "bin"), help="the built SDK")
    stage.add_argument("--no-sdk", action="store_true", help="ship without the prebuilt SDK")
    stage.add_argument("--no-python", action="store_true", help="ship without the embeddable Python")
    stage.add_argument(
        "--updater-pubkey",
        metavar="KEY",
        help="the updater's public key: turns on the in-app updater and signed update artifacts (empty: off)",
    )
    stage.add_argument(
        "--updater-endpoint", metavar="URL", default=UPDATER_ENDPOINT, help="where the updater finds latest.json"
    )
    portable = sub.add_parser("portable")
    portable.add_argument("exe")
    portable.add_argument("out")
    args = parser.parse_args()
    {"stage": cmd_stage, "portable": cmd_portable}[args.command](args)


if __name__ == "__main__":
    main()
