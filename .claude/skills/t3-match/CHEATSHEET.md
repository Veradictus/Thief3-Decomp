# MSVC 7.1 codegen cheat sheet (T3Main.exe matching)

Append-only. Every entry was observed with the project compiler,
`cl.exe` 13.10.3077 with `/O2 /GX /GR- /MT` (configure.py's CFLAGS), on
synthetic code; none of it is game code. An entry states what was compiled
and what came out, nothing more. Workers propose new entries in their final
summary (`idioms`); the lead verifies each with the compiler before adding
it here. Leads from other projects (MSVC 6, other flags) do not go here until
reproduced.

Each entry has a `tags:` line. Read the whole sheet once per session;
`context.py` repeats the entries whose tags match a function's features
(`eh`, `fp`, `switch`, `thiscall`). `general` entries apply everywhere.

### Functions defined in the same file are inlined, even after the caller
tags: general
verified: 2026-09-27

`/O2` implies `/Ob2`: any small function whose body is in the translation
unit can be inlined, whether it is defined before or after its caller.

```cpp
int HelperAfter(int x);
int CallerB(int a) { return HelperAfter(a) + 1; }
int HelperAfter(int x) { return x * 5; }
```
```
CallerB:  mov eax, [esp+0x4]
          lea eax, [eax+eax*0x4+0x1]
          ret
```

So a scratch file declares its callees and never defines them: a `call`
in the target must stay a call. The same holds in the lead's units, which is
why integrate.py re-checks every function once it sits in its unit.

### Rewrites that do not change the code
tags: general
verified: 2026-09-27

These pairs compile to identical instructions, so switching between them
spends an attempt for nothing:

- `s->x + s->y` and `s->y + s->x` (both `mov eax, [ecx+0x4]; add eax, [ecx]`);
- `if (a) return 1; return 0;`, `return a != 0;` and a `bool` return
  (`xor eax, eax; test ecx, ecx; setne al`);
- a `for` loop and the equivalent `while` loop.

try.py says "same compiled code as attempt N" when a change had no effect.

### Arithmetic by constants
tags: general
verified: 2026-09-27

| Source | Code |
|---|---|
| `x * 2` | `shl eax, 0x1` |
| `x * 3`, `x * 5`, `x * 9` | `lea eax, [eax+eax*0x2]` / `*0x4` / `*0x8` |
| `x * 6` | `lea eax, [eax+eax*0x2]; shl eax, 0x1` |
| `x * 7` | `imul eax, 0x7` |
| `x * 3 + 1` | `lea eax, [eax+eax*0x2+0x1]` |
| `x + 1` | `inc eax` |
| `x - 3` | `add eax, 0xfffffffd` |
| `x / 2` (int) | `cdq; sub eax, edx; sar eax, 0x1` |
| `x / 2` (unsigned) | `shr eax, 0x1` |
| `x / 3` (int) | `mov eax, 0x55555556; imul ecx; mov eax, edx; shr eax, 0x1f; add eax, edx` |

### Floating point constants, compares and conversions
tags: fp
verified: 2026-09-27

- Every float constant is loaded from a `__real@` constant, even 0 and 1
  (no `fldz`/`fld1`): `0.0f` is `fld dword ptr [__real@00000000]`, `1.0f`
  `__real@3f800000`, `2.5f` `__real@40200000`, the double `2.5`
  `qword ptr [__real@4004000000000000]`. The literal's value is checked by
  the data ruler, so a wrong constant never matches.
- `a < b` on floats: `fld a; fcomp b; fnstsw ax; test ah, 0x5; jp ...`;
  `a <= b` tests `0x41`.
- `(int)f` is `fld f; jmp __ftol2` (a tail call to the 7.1 CRT helper).

### Dense switch: bounds check, jump table after the code
tags: switch
verified: 2026-09-27

Six consecutive cases give `cmp eax, 0x5; ja default; jmp dword ptr
[eax*0x4+table]`, and the table sits right after the function's code, in
the same section. MSVC names the table and the case entry
points `$Lnnn`; the tools turn those into function+offset references (as the
split does) and compare the table separately ("switch tables: ..." in
try.py's problems).

A sparse switch (`case 1`, `100`, `1000`, `5000`) becomes a compare tree:
`cmp eax, 0x3e8; jg ...; je ...; dec eax; je ...; sub eax, 0x63; jne ...`.

### EH frame of a function with destructible locals
tags: eh
verified: 2026-09-27

With `/GX`, a function holding a local with a destructor gets:

```
push 0xffffffff
push __ehhandler$<decorated name>
mov eax, fs:[__except_list]
push eax
mov fs:[__except_list], esp
sub esp, ...                      ; or push ecx for one dword
...
mov dword ptr [esp+N], 0x0        ; state 0 after the first construction
mov byte ptr [esp+N], 0x1         ; later states are stored as bytes
mov byte ptr [esp+N], 0x0         ; going back down as objects die
mov dword ptr [esp+N], 0xffffffff ; -1 before the last destructor
...
mov fs:[__except_list], ecx
```

The body stays `esp`-relative. The unwind funclets (`$Lnnn`, one per
object: `lea ecx, [ebp-0x10]; jmp <destructor>`) and then the handler
(`mov eax, $Tnnn; jmp ___CxxFrameHandler`) go to `.text$x`; the tables
(`$Tnnn`) to `.xdata$x`. The linked exe holds a plain `fs:[0x0]`, and the
tools accept that for `__except_list`. They also check the handler, the
tables and every funclet against the target, so a wrong destructor fails.
A function without destructible locals gets no frame at all.

### Declaration order of destructible locals
tags: eh
verified: 2026-09-27

`R x; R y;` constructs `x` first and gives it the higher stack slot
(`[esp+0x8]`, `y` at `[esp+0x4]`); `R y; R x;` swaps the slots. The rest of
the function is identical, so a difference confined to which stack offset
holds which object means the declarations are in the wrong order.

### Struct copies and small fills
tags: general
verified: 2026-09-27

- Copying a 32-byte struct: `mov ecx, 0x8; rep movsd` between `push
  esi`/`push edi`. A 12-byte struct: three `mov edx, [eax+k]; mov [ecx+k],
  edx` pairs.
- `for (int i = 0; i < 16; i++) p[i] = 0;` is fully unrolled: `xor eax, eax`
  then 16 `mov [ecx+k], eax`.

### Virtual calls, delete, tail calls
tags: thiscall
verified: 2026-09-27

- `v->F(3)` with F in vtable slot 1: `mov ecx, v; mov eax, [ecx]; push 0x3;
  call dword ptr [eax+0x4]`.
- `delete v` with a virtual destructor: `test ecx, ecx; je ...; mov eax,
  [ecx]; push 0x1; call dword ptr [eax]` (the scalar deleting destructor in
  slot 0).
- `return Tail(x);` with the caller's own arguments: `jmp Tail`.

### Calling conventions and names
tags: general
verified: 2026-09-27

| Declaration | Name | Code |
|---|---|---|
| `int Std(int, int)` `__stdcall` | `?Std@@YGHHH@Z` | `ret 0x8` |
| `int Fast(int, int)` `__fastcall` | `?Fast@@YIHHH@Z` | arguments in `ecx`, `edx` |
| `extern "C" int CFunc(int)` | `_CFunc` | |
| `int W::Get() const` | `?Get@W@@QBEHXZ` | `this` in `ecx` |
| `static int n` inside `Counter()` | `?n@?1??Counter@@YAHXZ@4HA` | in `.bss` |

A member function defined inside its class and called in the file can also
appear as a pick-any COMDAT copy (seen for an in-class `W::Get` whose only
call was inlined); try.py never takes such a copy for the candidate.

### Character loads and string literals
tags: general
verified: 2026-09-27

- `s[1]` on `const char*`: `movsx eax, byte ptr [eax+0x1]`; on
  `const unsigned char*`: `movzx`.
- A string literal is a COMDAT named after its contents and a hash:
  `"shared"` is `??_C@_06HBFNPGIC@shared?$AA@`; two functions returning the
  same literal reference the same symbol.
