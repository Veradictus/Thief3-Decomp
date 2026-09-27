"""Instruction features of target functions: a difficulty score for the queue and tags for the context packet.

Needs iced-x86 (requirements.txt) and the target's bytes (the exe, else the
split objects). Without either, callers fall back to function size.
Results are cached in build/agent/cache/features.json, keyed by the inputs.
"""

import importlib.util
import json
from typing import Dict, Iterable, Optional

from common import Project, atomic_write, read_json

# Difficulty: a hand formula in the spirit of Lewis's first scorer. Refit it
# from the attempt ledgers once the pilot has outcomes.
WEIGHTS = {"insns": 1, "branches": 3, "calls": 2, "switch": 10, "eh": 10, "fp": 1}


def available() -> bool:
    return importlib.util.find_spec("iced_x86") is not None


def _key(p: Project) -> str:
    parts = [p.symbols_txt]
    parts.append(p.exe if p.exe and p.exe.is_file() else p.obj_dir / ".." / "split.stamp")
    return ";".join(f"{x}:{x.stat().st_mtime_ns}:{x.stat().st_size}" if x.exists() else str(x) for x in parts)


def analyse(p: Project, image, address: int, size: int) -> Optional[dict]:
    from iced_x86 import Decoder, FlowControl, Mnemonic, OpKind, Register

    view = image.view(address, size)
    if view is None:
        return None
    names = {v: k for k, v in vars(Mnemonic).items() if isinstance(v, int)}
    out = {"insns": 0, "branches": 0, "calls": 0, "switch": 0, "eh": 0, "fp": 0, "callees": []}
    for insn in Decoder(32, view.data, ip=address):
        out["insns"] += 1
        flow = insn.flow_control
        if flow == FlowControl.CONDITIONAL_BRANCH:
            out["branches"] += 1
        elif flow in (FlowControl.CALL, FlowControl.INDIRECT_CALL):
            out["calls"] += 1
            if flow == FlowControl.CALL:
                out["callees"].append(insn.near_branch_target)
        elif (flow == FlowControl.INDIRECT_BRANCH and insn.op0_kind == OpKind.MEMORY
              and insn.memory_index_scale == 4):
            out["switch"] += 1
        memory = any(insn.op_kind(i) == OpKind.MEMORY for i in range(insn.op_count))
        if memory and insn.memory_segment == Register.FS:
            out["eh"] = 1  # the fs:[0] exception registration of /GX functions
        if names.get(insn.mnemonic, "").startswith("F"):
            out["fp"] += 1
    if view.relocs is not None:  # split objects: call fields hold relocations, not displacements
        out["callees"] = [a for a, _, t in view.relocs.values() if t == 0x14 and a is not None]
    out["callees"] = sorted(set(out["callees"]))
    out["score"] = sum(WEIGHTS[k] * out[k] for k in WEIGHTS)
    return out


def features(p: Project, addresses: Iterable[int]) -> Dict[int, dict]:
    """Features by address, for those that can be computed; {} without iced-x86 or target bytes."""
    if not available():
        return {}
    from verify import TargetImage

    cache_path = p.state / "cache" / "features.json"
    cache = read_json(cache_path, {}) or {}
    key = _key(p)
    if cache.get("key") != key:
        cache = {"key": key, "functions": {}}
    known = cache["functions"]
    image = None
    out, changed = {}, False
    for address in addresses:
        hit = known.get(f"{address:08X}")
        if hit is None:
            image = image or TargetImage(p)
            f = p.by_addr.get(address)
            code_end, _ = p.code_extent(address)
            hit = analyse(p, image, address, code_end - address) if f else None
            known[f"{address:08X}"] = hit or {}
            changed = True
        if hit:
            out[address] = hit
    if changed:
        atomic_write(cache_path, json.dumps(cache))
    return out
