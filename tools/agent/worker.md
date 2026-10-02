# Matching worker protocol

Match T3Main.exe functions byte for byte with MSVC 7.1 (/O2 /GX /GR-). This
file replaces SKILL.md and CHEATSHEET.md: do not read those, docs, or other
workers' files. Your prompt gives ID, FILTERS, N, COUNT, CAP and PY (the
Python to run the tools with; `.venv/Scripts/python` when it gives none).

## Tools

Run every tool from the repo root exactly as

    T3_AGENT_ID=<ID> <PY> tools/agent/<tool>.py ...

with the prefix on every call (env vars do not persist between calls).

## Loop: claim COUNT functions at a time until N are handled

Handled means accepted or deferred. After finishing a claim, claim again:
do not stop before N functions are handled unless the claim prints
`"empty": true`.

1. `next.py claim --context --count <COUNT> <FILTERS>` prints one JSON line
   (addr, symbol, size), then each function's context packet: the target's
   instructions, what it references, similar accepted functions with their
   source. `"empty": true`: stop.
2. An attempt is ONE message with two tool calls, in this order:
   - Write `build/scratch/<ADDR>/vK.cpp` (K = 1, 2, ...; a new file each time);
   - Bash `T3_AGENT_ID=<ID> <PY> tools/agent/try.py <ADDR> build/scratch/<ADDR>/vK.cpp && T3_AGENT_ID=<ID> <PY> tools/agent/accept.py <ADDR> build/scratch/<ADDR>/vK.cpp`

   ALWAYS chain accept.py with `&&` as shown: a MATCH is recorded only when
   accept.py prints `ACCEPTED`. With several claimed functions, put their
   attempts in the same message. BUILD FAILED is not counted: fix it.
3. NO MATCH: first classify the difference in one line, then change one
   thing aimed at it. "same compiled code as attempt N" means that change did
   nothing.
   - different instructions, operands, offsets or calls: the source differs:
     fix the expression, types, field or callee;
   - the same instructions with registers or order swapped: try at most two
     unrelated rewrites (statement order, a temporary), then defer `tiebreak`;
   - a helper inlined on one side only: defer `inline`;
   - an offset, size or slot you cannot know: defer `layout` or `vtable`;
   - only a name or signature differs (score 99.9+): defer `name-conflict`.
4. Defer after CAP attempts, when try.py refuses (4 attempts in a row with no
   new best), or at once on a systemic blocker:
   `accept.py defer <ADDR> "<slug>: <one-line blocker>" --needs "<what would unblock it>"`.
   Slugs: tiebreak, inline, layout, vtable, signature, name-conflict, eh,
   switch, codegen, library, engine, compiler-generated, asm, adjustor thunk.
   Deferring is a normal outcome; your best attempt is kept for the next pass.
   `CANNOT CHECK`: `next.py release <ADDR>` and note it in needs.

The packet may also show: `bound`: accepted callers already named this
function; define it under exactly that decorated name, or defer
`name-conflict`. `family`: functions with the same code but other references;
keep placeholder names so the lead's tool can reuse your source for them, and
start from an accepted sibling under `similar`. `best earlier attempt`: a
second pass; start from it, the blocker is a lead and not a verdict, and do
not repeat what it tried. Claims of one class (`--by-class`): declare the
class once, the same way in each file.

## Scratch file

Declarations first, then `// FUNCTION: 0x<ADDR>` and exactly one non-inline
function; nothing after it. Declare callees, never define them (MSVC 7.1
inlines any body in the file, even one defined after the caller). Use
`#include "..."` for project headers from include/ when the packet shows them.

## Codegen (verified)

- `x*2` shl 1; `x*3/5/9` lea [x+x*2/4/8]; `x*6` lea then shl; `x*7` imul;
  `x+1` inc; `x-3` add 0xfffffffd; signed `x/2` cdq; sub; sar; unsigned shr.
- `if (a) return 1; return 0;`, `return a != 0;` and a bool return compile the
  same; so do for/while loops and swapped `+` operands.
- A float constant the FPU loads comes from `__real@` (even 0 and 1); one only
  stored is a mov of its bits (`f = 1.0f;` is mov dword ptr [x], 0x3f800000).
  `(int)f` is fld; jmp __ftol2; `a < b` on floats: fcomp; fnstsw ax; test ah, 0x5.
- Stores come out in source order: write them in the target's order.
- thiscall: `this` in ecx. `v->F(3)` with F in vtable slot k: mov eax, [ecx];
  push 3; call [eax+4k]. `delete v` with a virtual destructor: test ecx, ecx;
  je; mov eax, [ecx]; push 1; call [eax]. A last call with the caller's own
  arguments (`return Tail(a);`, or `Obj.Method();` ending a void function) is a
  jmp. A call on a global object: mov ecx, offset Global before each call.
- `mov eax, ecx` first, then fields through eax (or `mov eax, ecx` just
  before ret): the method returns `this`, like a constructor or an init:
  `Class_X* Class_X::FUN_x() { Unknown04 = 0; return this; }`. A `ret N`
  counts every argument, used or not.
- `mov ecx, [Global]` before a call that ecx is otherwise unused for: the
  call is `Global->Method(...)`. `sete al; push eax` with no `xor eax, eax`
  before it: the parameter is `bool`.
- `mov dword ptr [x], DAT_...` (an address as an immediate): declare
  `extern void* DAT_...[];` and assign it; a scalar `extern void* DAT_...;`
  would load through the variable. An inlined base constructor stores the
  base vtable first and the derived one later: write both stores.
- A 1-bit field store (`lea edx, [ecx*8]; xor; and edx, 8; xor`): declare a
  bitfield and assign it; don't write the xor/and by hand.
- A direct call or jmp to a function that is virtual (it sits in a vtable):
  qualify the call (`Base::F();`); an unqualified call goes through the vtable.
- `mov eax, [ecx+N]; mov edx, [ecx+N+4]; ret`: returns a 64-bit field
  (`__int64 Unknown08;` and `return Unknown08;`).
- `mov dword ptr [esp+N], imm` then `jmp F`: a wrapper passing its own
  arguments on with one replaced by a constant (`void G(int a, int b) { F(a, 1); }`).
- `__stdcall`: ret N (`?F@@YG...`); `extern "C"`: `_F`; const method: `QBE`;
  static locals live in .bss.
- A local with a destructor under /GX gives an EH frame (push -1; push
  __ehhandler$...; fs:[0]); the first-declared local gets the higher stack
  slot. No destructible locals, no frame.
- `xor ecx, ecx; lea edx, [eax+N]` then unrolled `mov [edx+k], ecx`: an inline
  `memset(&Field, 0, size)` (declare `extern "C" void* memset(void*, int, unsigned);`).
- 32-byte struct copy: rep movsd; short fixed loops are unrolled. Signed char
  loads movsx, unsigned movzx. Dense switch: cmp; ja; jmp [eax*4+table].
- `if (Member) Member->F();` loads the member into eax and copies it to ecx;
  `C* P = Member; if (P) P->F();` loads straight into ecx. Likewise
  `int Key = A; F(&Key);` stores back into the argument's own slot, `F(&A)`
  does not. A global load hoisted above a member store: `int v = G; f = 0;
  if (v) ...`.
- `movzx eax, al` after a call returning bool: the caller returns int.
  `neg eax; sbb eax, eax; neg eax` after a call: `return F() != 0;` (bool).
  `setge dl; mov eax, edx`: an int return; a bool return is `mov al, dl`.
- `delete P` with no destructor call (operator delete only): give P a
  complete empty type, `struct Struct_<addr> {};`, not `void*` (deleting a
  `void*` is undefined C++, though MSVC compiles it the same).
- COM interfaces (Direct3D): declare slots `virtual int __stdcall
  VirtualN(...)`: `this` is pushed last, no ecx.
- `mov ecx, [esp+4]; test ecx, ecx; je; jmp <ctor>` (14 bytes) is a native
  class's InternalConstructor: config/PC_20040610/classes.txt names the class
  whose `constructor:` is this address. Write it as Unreal does: declare
  `enum EInternal { EC_Internal };` and `inline void* operator new(unsigned
  int, EInternal* Mem) { return Mem; }` (not a `void*` placement new: it
  clashes with `<new>`), the class with `T(); static void
  InternalConstructor(void* X);`, and define `void
  T::InternalConstructor(void* X) { new ((EInternal*)X) T(); }`. The jmp
  target is `T::T()`: declare it as the constructor even when symbols.txt
  calls it a method.

## Rules (accept.py rejects the rest)

Write what a programmer would have written: express the computation, never
transliterate registers (no variables named `eax`, `edx`), and never declare
data as a function to get its address (an address used as an immediate is
`extern void* DAT_x[];`), and never use `volatile` to keep a store the compiler
would drop (repeated vtable stores come from real classes with virtual
functions). A match that breaks these is rejected by accept.py or at review.

Compile only through try.py: no scripts, toy compiles or experiments of your
own. If the target looks hand-written in asm (registers no compiler would
pick, the same sequence repeated unchanged at every use), defer at once.

No `__asm`, `_emit`, naked, `goto` or codegen `#pragma`; no literal exe
addresses; no `*(int*)((char*)p + 0x10)`: declare a struct with the field at
that offset. Never define callees or call a different function than the
target calls. Write only under build/scratch/, with relative forward-slash
paths (a Windows path in Bash loses its backslashes). No git commands.
Library code is not published: a target that is itself part of the STL,
CRT, D3DX or Havok (a member of a `std::` template, a CRT routine) is
deferred at once with the blocker "library: <what>". Game code that uses a library
is game code: include the compiler's header (`#include <vector>`) and use its
types, as Ion Storm did. Neither is Epic's engine: a method of an Unreal Engine class
(`UObject`, `UClass`, `FName`, `FString`, `FArchive`, `AActor`, `UEngine`,
`ULevel`, `UViewport`, the render device, ...) is deferred at once with the
blocker "engine: <class>". Never pass `--replace`, `--cap`, `--patience` or `--include-siblings`,
never run integrate.py, wave.py, sweep.py, fixnames.py, clusters.py stamp,
retry.py, dtors.py or rename.py: those are the lead's, and a guard refuses
them and every write outside build/scratch/.

`add ecx, N` (or `sub ecx, N`) then `jmp`: a this-adjustor thunk the compiler
makes for multiple inheritance, not source anyone wrote. Defer it at once
with the blocker "adjustor thunk". So is a deleting destructor (a destructor
call, `test byte ptr [esp+8], 1`, a delete call, `return this`) and a global
object's initializer (a constructor call, then `atexit`): the compiler emits
them from a virtual destructor or a global's definition. Defer them at once
with the blocker "compiler-generated: <what>"; never write them as functions.

## Names need evidence

A call made while ecx still holds `this` is a member call (a base
constructor, or a method of the same object or a base): declare the callee
as a method of that class or base, never as a free function, even though a
free call gives the same bytes; its name is recorded as you declare it.
Never use `__fastcall` or a parameter named `ecx` to stand in for `this`, and
never cast a global to a class pointer to call through it: declare the
method, and the global with its class type. A call through `[eax+N]` after
`mov eax, [ecx]` is a virtual call: declare `virtual` methods up to slot N/4
and call `this->VirtualK()`; never model a vtable as a struct of function
pointers.

When the packet shows `== vtable slots`, the function is a virtual method of
the class owning that table: the class the packet names (`AGarrett's
vtable`), else `Class_<table>`. Declare that class with `virtual`
placeholder methods `Virtual0()`... before its slot, the function itself
`virtual` at its slot, and define `AGarrett::FUN_x` (or
`Class_<table>::FUN_x`).

Use the symbols.txt and header names the packet shows. A generated header
(`include/<Package>/<Package>Classes.h`) lists a class's fields with their
offsets: name and type the fields you use from it, in your own declaration
of the class (do not include it). An unnamed free function keeps its
placeholder (`void FUN_10926680();`). A member of an unknown class goes in
`Class_<vtable address>` when a constructor stores the vtable, else
`Class_<function address>` (never a made-up name such as `UNK_Class`), and
keeps its placeholder method name. Any other field gets a name only when the
code shows what it holds, else `Unknown34`.

## Finish

Your final message is ONLY this JSON line, with no other text (with a
StructuredOutput tool, return the same object through it). `matched` lists
only what accept.py ACCEPTED; `needs` and `idioms` have at most 3 entries of
at most 25 words each; `empty` is true when a claim printed `"empty": true`:

    {"agent":"<ID>","matched":["0x..."],"deferred":[{"addr":"0x...","best":91.2,"why":"<slug>: ..."}],"needs":["..."],"idioms":["..."],"empty":false}
