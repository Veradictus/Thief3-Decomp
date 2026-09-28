"""Shared helpers for the Thief: Deadly Shadows asset tools.

- `Reader`: little-endian cursor over a bytes buffer, with Unreal's compact
  index ("INDEX") and FString encodings.
- `game_dir()`: finds the game install (--game-dir, $T3_GAME_DIR, then the
  ION_ROOT registry value, like tools/sdk.py).
- Coordinate conversion from Unreal space (left-handed, Z up) to glTF/Godot
  space (right-handed, Y up).

Standard library only.
"""

from __future__ import annotations

import json
import math
import os
import struct
import sys
from pathlib import Path
from typing import Any, Dict, Optional, Sequence, Tuple

REPO_ROOT = Path(__file__).resolve().parents[2]
# Output goes under <repo>/build, or under $T3SDK_BUILD_DIR: the launcher points
# that at a per-user folder when it runs the copy of the tools it ships with.
BUILD_ROOT = Path(os.environ.get("T3SDK_BUILD_DIR") or REPO_ROOT / "build")
BUILD_DIR = BUILD_ROOT / "assets"

# Format versions of what the map tools write (map_export, map_edits), shared
# with the launcher and the map editor plugin; see formats.json.
FORMATS: Dict[str, Any] = json.loads((Path(__file__).resolve().parent / "formats.json").read_text(encoding="utf-8"))

_U8 = struct.Struct("<B")
_U16 = struct.Struct("<H")
_I16 = struct.Struct("<h")
_U32 = struct.Struct("<I")
_I32 = struct.Struct("<i")
_U64 = struct.Struct("<Q")
_F32 = struct.Struct("<f")


class Reader:
    """Little-endian reader over an immutable buffer."""

    __slots__ = ("data", "pos", "end")

    def __init__(self, data: bytes, pos: int = 0, end: Optional[int] = None) -> None:
        self.data = data
        self.pos = pos
        self.end = len(data) if end is None else end

    def remaining(self) -> int:
        return self.end - self.pos

    def eof(self) -> bool:
        return self.pos >= self.end

    def _need(self, n: int) -> None:
        if self.pos + n > self.end:
            raise EOFError(f"read of {n} bytes at {self.pos:#x} runs past {self.end:#x}")

    def bytes(self, n: int) -> bytes:
        self._need(n)
        b = self.data[self.pos:self.pos + n]
        self.pos += n
        return b

    def skip(self, n: int) -> None:
        self._need(n)
        self.pos += n

    def u8(self) -> int:
        self._need(1)
        v = self.data[self.pos]
        self.pos += 1
        return v

    def _unpack(self, s: struct.Struct):
        self._need(s.size)
        v = s.unpack_from(self.data, self.pos)[0]
        self.pos += s.size
        return v

    def u16(self) -> int:
        return self._unpack(_U16)

    def i16(self) -> int:
        return self._unpack(_I16)

    def u32(self) -> int:
        return self._unpack(_U32)

    def i32(self) -> int:
        return self._unpack(_I32)

    def u64(self) -> int:
        return self._unpack(_U64)

    def f32(self) -> float:
        return self._unpack(_F32)

    def vec3(self) -> Tuple[float, float, float]:
        self._need(12)
        v = struct.unpack_from("<3f", self.data, self.pos)
        self.pos += 12
        return v

    def index(self) -> int:
        """Unreal compact index: sign bit 0x80 and continue bit 0x40 in the
        first byte (6 value bits), then 7 value bits per byte with 0x80 as the
        continue bit."""
        b = self.u8()
        neg = b & 0x80
        v = b & 0x3F
        if b & 0x40:
            shift = 6
            while True:
                b = self.u8()
                v |= (b & 0x7F) << shift
                shift += 7
                if not b & 0x80:
                    break
        return -v if neg else v

    def fstring(self) -> str:
        """Unreal FString: compact length including the NUL; a negative length
        means UTF-16 characters."""
        n = self.index()
        if n == 0:
            return ""
        if n > 0:
            return self.bytes(n)[:-1].decode("latin-1")
        return self.bytes(-2 * n)[:-2].decode("utf-16-le")

    def string32(self) -> str:
        """Ion Storm resource string: u32 length including the NUL, then bytes."""
        n = self.u32()
        if n == 0:
            return ""
        return self.bytes(n).split(b"\0", 1)[0].decode("latin-1")


def read_index(data: bytes, pos: int = 0) -> Tuple[int, int]:
    """Compact index at `pos`; returns (value, new position)."""
    r = Reader(data, pos)
    v = r.index()
    return v, r.pos


def write_index(value: int) -> bytes:
    """Encode a compact index (the inverse of Reader.index)."""
    out = bytearray()
    v = abs(value)
    b0 = (0x80 if value < 0 else 0) | (v & 0x3F)
    v >>= 6
    if v:
        b0 |= 0x40
    out.append(b0)
    while v:
        b = v & 0x7F
        v >>= 7
        if v:
            b |= 0x80
        out.append(b)
    return bytes(out)


def run_cli(main) -> None:
    """Run a CLI entry point; exit quietly when stdout is closed early
    (e.g. piped into `head`)."""
    try:
        main()
    except BrokenPipeError:
        pass
    except OSError as ex:  # Windows reports a closed pipe as EINVAL
        if ex.errno != 22:
            raise
    finally:
        try:
            sys.stdout.flush()
        except (BrokenPipeError, OSError):
            try:
                sys.stdout = open(os.devnull, "w")
            except OSError:
                pass


# --- game install ---------------------------------------------------------

def game_dir(explicit: Optional[str] = None) -> Path:
    """The Thief: Deadly Shadows install folder (read-only for these tools)."""
    if explicit:
        return Path(explicit)
    if os.environ.get("T3_GAME_DIR"):
        return Path(os.environ["T3_GAME_DIR"])
    if os.name == "nt":
        import winreg

        for view in (winreg.KEY_WOW64_32KEY, winreg.KEY_WOW64_64KEY):
            try:
                key = winreg.OpenKey(winreg.HKEY_LOCAL_MACHINE,
                                     r"SOFTWARE\Ion Storm\Thief - Deadly Shadows",
                                     0, winreg.KEY_READ | view)
                with key:
                    return Path(winreg.QueryValueEx(key, "ION_ROOT")[0])
            except OSError:
                pass
    sys.exit("game folder not found: pass --game-dir or set T3_GAME_DIR")


def content_dir(game: Path) -> Path:
    return game / "Content" / "T3"


def resolve_map(game: Path, name: str, ext: str) -> Path:
    """Accept a path or a bare map name ("Inn") and return Content/T3/Maps/<name><ext>."""
    p = Path(name)
    if p.suffix.lower() == ext and p.is_file():
        return p
    if p.is_file():
        return p
    cand = content_dir(game) / "Maps" / (p.stem + ext)
    if cand.is_file():
        return cand
    # case-insensitive match (the shipped names mix case: docks2, Inn, museum1)
    for f in (content_dir(game) / "Maps").glob("*" + ext):
        if f.stem.lower() == p.stem.lower():
            return f
    sys.exit(f"no such map file: {cand}")


# --- coordinates ----------------------------------------------------------
#
# Unreal: X forward, Y right, Z up, left-handed.  glTF and Godot: Y up,
# right-handed.  We map (x, y, z)_unreal -> (x, z, y): a single axis swap, so
# handedness flips and triangle winding must be reversed.  UNREAL_TO_GODOT is
# its own inverse.

UNREAL_TO_GODOT = ((1.0, 0.0, 0.0),
                   (0.0, 0.0, 1.0),
                   (0.0, 1.0, 0.0))


def u2g(v: Sequence[float], scale: float = 1.0) -> Tuple[float, float, float]:
    return (v[0] * scale, v[2] * scale, v[1] * scale)


ROT_UNIT = 2.0 * math.pi / 65536.0


def rotator_matrix(pitch: int, yaw: int, roll: int):
    """FRotationMatrix from Unreal Engine 2 (row vectors: rows are the rotated
    X, Y and Z axes).  Angles are in Unreal units (65536 = 360 degrees)."""
    sp, cp = math.sin(pitch * ROT_UNIT), math.cos(pitch * ROT_UNIT)
    sy, cy = math.sin(yaw * ROT_UNIT), math.cos(yaw * ROT_UNIT)
    sr, cr = math.sin(roll * ROT_UNIT), math.cos(roll * ROT_UNIT)
    return (
        (cp * cy, cp * sy, sp),
        (sr * sp * cy - cr * sy, sr * sp * sy + cr * cy, -sr * cp),
        (-(cr * sp * cy + sr * sy), cy * sr - cr * sp * sy, cr * cp),
    )


def godot_basis(pitch: int, yaw: int, roll: int, scale3: Sequence[float] = (1.0, 1.0, 1.0)):
    """Godot Basis (as three column vectors) for an Unreal actor rotation and
    DrawScale3D, in the swapped-axis space used by u2g().

    Unreal transforms a local point v (row vector) as v * S * R.  In column
    form the world point is R^T S v, so the Unreal-space basis columns are the
    rows of R, scaled.  Godot space: B_g = P * B_u * P with P = UNREAL_TO_GODOT.
    """
    rows = rotator_matrix(pitch, yaw, roll)
    # Unreal-space column j = rows[j] * scale3[j]
    cols_u = [tuple(rows[j][i] * scale3[j] for i in range(3)) for j in range(3)]
    # B_u as a matrix M[i][j] = cols_u[j][i]
    mu = [[cols_u[j][i] for j in range(3)] for i in range(3)]
    p = UNREAL_TO_GODOT
    mg = [[sum(p[i][k] * mu[k][l] * p[l][j] for k in range(3) for l in range(3)) for j in range(3)]
          for i in range(3)]
    return tuple(tuple(mg[i][j] for i in range(3)) for j in range(3))  # columns


def fmt_float(v: float) -> str:
    """Compact float for text output (Godot scenes, JSON-like dumps)."""
    if abs(v) < 1e-7:
        return "0"
    s = f"{v:.6g}"
    return s
