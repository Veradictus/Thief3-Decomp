"""Read and write dtk-style symbols.txt files.

    <name> = <section>:0x<address>; // type:<function|object|label> size:0x<n> [scope:local]
"""

import re
from dataclasses import dataclass
from pathlib import Path
from typing import Dict, Iterable, List

_LINE = re.compile(
    r"^(?P<name>\S+) = (?P<section>[^:\s]+):0x(?P<address>[0-9A-Fa-f]+);\s*(?://(?P<attrs>.*))?$"
)


@dataclass
class Symbol:
    name: str
    section: str
    address: int
    type: str = "label"
    size: int = 0
    scope: str = "global"

    @property
    def end(self) -> int:
        return self.address + self.size

    @property
    def is_function(self) -> bool:
        return self.type == "function"


def _attrs(text: str) -> Dict[str, str]:
    out = {}
    for token in text.split():
        key, sep, value = token.partition(":")
        if sep:
            out[key] = value
    return out


def load(path: Path) -> List[Symbol]:
    """Parse symbols.txt (see the module docstring for the format) into Symbols, sorted by address."""
    symbols: List[Symbol] = []
    names: Dict[str, int] = {}
    for lineno, raw in enumerate(path.read_text(encoding="utf-8").splitlines(), 1):
        line = raw.strip()
        if not line or line.startswith("#"):
            continue
        m = _LINE.match(line)
        if not m:
            raise ValueError(f"{path}:{lineno}: cannot parse symbol line: {raw!r}")
        attrs = _attrs(m.group("attrs") or "")
        sym = Symbol(
            name=m.group("name"),
            section=m.group("section"),
            address=int(m.group("address"), 16),
            type=attrs.get("type", "label"),
            size=int(attrs.get("size", "0"), 0),
            scope=attrs.get("scope", "global"),
        )
        if sym.name in names:
            raise ValueError(f"{path}:{lineno}: duplicate symbol name {sym.name} (first on line {names[sym.name]})")
        names[sym.name] = lineno
        symbols.append(sym)
    symbols.sort(key=lambda s: s.address)
    return symbols


def format_symbol(sym: Symbol) -> str:
    attrs = f"type:{sym.type}"
    if sym.size:
        attrs += f" size:0x{sym.size:X}"
    if sym.scope != "global":
        attrs += f" scope:{sym.scope}"
    return f"{sym.name} = {sym.section}:0x{sym.address:08X}; // {attrs}"


def save(path: Path, symbols: Iterable[Symbol], header: str = "") -> None:
    """Write symbols.txt, sorted by address, with `header` as leading '#' comment lines."""
    lines = [f"# {line}" for line in header.splitlines()]
    lines += [format_symbol(s) for s in sorted(symbols, key=lambda s: s.address)]
    path.write_text("\n".join(lines) + "\n", encoding="utf-8", newline="\n")
