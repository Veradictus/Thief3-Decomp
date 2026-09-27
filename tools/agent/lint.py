"""Source lint for accepted functions: the ways a match can be forced without being real source.

Comments and string literals are blanked first, so a rule never fires on text
inside them.
"""

import re
from typing import List, Optional, Tuple

# Addresses inside T3Main.exe's image: a literal one is a hard-coded reference.
IMAGE_START, IMAGE_END = 0x10900000, 0x11018000

RULES: List[Tuple[str, "re.Pattern[str]", str]] = [
    ("asm", re.compile(r"\b_{0,2}asm\b"), "inline assembly"),
    ("emit", re.compile(r"\b_{1,2}emit\b"), "_emit bytes"),
    ("naked", re.compile(r"__declspec\s*\(\s*naked\s*\)"), "__declspec(naked)"),
    ("goto", re.compile(r"\bgoto\b"), "goto"),
    ("pragma", re.compile(r"#\s*pragma\s+(optimize|code_seg|alloc_text|inline_depth|inline_recursion|auto_inline)\b"),
     "#pragma that changes code generation"),
    # (T*)((char*)p + 8), *(int*)((BYTE*)this + 0x10), reinterpret_cast<T*>(reinterpret_cast<char*>(p) + 4)
    ("offset-cast", re.compile(
        r"\(\s*[\w:<>\s]+\*+\s*\)\s*\(\s*\(\s*(?:const\s+)?(?:unsigned\s+)?(?:char|BYTE|byte|uint8_t|int|DWORD|INT|"
        r"UINT|uintptr_t|intptr_t|INT_PTR|UINT_PTR|size_t|long|unsigned)\s*\**\s*\)\s*&?[\w\->.\[\]()]+\s*[-+]\s*"
        r"(?:0[xX][0-9A-Fa-f]+|\d+)"), "pointer + integer offset cast (use a struct field)"),
    ("offset-cast", re.compile(
        r"reinterpret_cast\s*<[^>]*\*\s*>\s*\(\s*(?:reinterpret_cast|\(\s*[\w\s]*\*?\s*\))[^;]*?[-+]\s*"
        r"(?:0[xX][0-9A-Fa-f]+|\d+)\s*\)"), "pointer + integer offset cast (use a struct field)"),
    ("offset-cast", re.compile(r"\(\s*[\w:<>\s]+\*+\s*\)\s*\(\s*this\s*[-+]\s*(?:0[xX][0-9A-Fa-f]+|\d+)\s*\)"),
     "`this` + integer offset cast (use a struct field)"),
]


def strip(source: str) -> str:
    """Blank comments and string/char literals, keeping line structure."""
    out = []
    i, n = 0, len(source)
    while i < n:
        c = source[i]
        if source.startswith("//", i):
            j = source.find("\n", i)
            j = n if j < 0 else j
            out.append(" " * (j - i))
            i = j
        elif source.startswith("/*", i):
            j = source.find("*/", i + 2)
            j = n if j < 0 else j + 2
            out.append(re.sub(r"[^\n]", " ", source[i:j]))
            i = j
        elif c in "\"'":
            j = i + 1
            while j < n and source[j] != c and source[j] != "\n":
                j += 2 if source[j] == "\\" else 1
            out.append(c + " " * (min(j, n) - i - 1) + (c if j < n else ""))
            i = j + 1
        else:
            out.append(c)
            i += 1
    return "".join(out)


def lint(source: str, address: Optional[int] = None) -> List[str]:
    """Problems with a candidate source file; empty when it passes."""
    text = strip(source)
    problems = []
    for rule, pattern, what in RULES:
        for m in pattern.finditer(text):
            line = text.count("\n", 0, m.start()) + 1
            problems.append(f"line {line}: {what} [{rule}]")
    for m in re.finditer(r"\b0[xX]([0-9A-Fa-f]{8})\b|\b(\d{9,10})\b", text):
        value = int(m.group(1), 16) if m.group(1) else int(m.group(2))
        if IMAGE_START <= value < IMAGE_END:
            line = text.count("\n", 0, m.start()) + 1
            problems.append(f"line {line}: literal address {value:#x} inside the exe (reference a symbol) [address]")
    if address is not None:
        markers = re.findall(r"^// FUNCTION: (?:0x)?([0-9A-Fa-f]{8})\b", source, re.M)
        if [int(m, 16) for m in markers] != [address]:
            problems.append(f"the file needs exactly one `// FUNCTION: 0x{address:08X}` line, right before the "
                            f"function's definition [marker]")
    return problems
