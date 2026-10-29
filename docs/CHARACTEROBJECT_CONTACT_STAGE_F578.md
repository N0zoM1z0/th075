# F578 — authentic 269-instruction CharacterObject action0x335 and real cross-case stack layout

**Japanese TH075 v1.11 native PE and fresh VC7.1 natural C++ source-codegen
proof; the complete 33,293-byte giant is not exact.** The original pinned
executable SHA256 is
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.

This new native-original, case-by-case experiment extends the **same one
natural C++ `Advance()` source function** from F572–F577 with the next
real CharacterObject gameplay action `0x335`, *not* another marker or a
cropped independent function. Original `004EBDA0` remains a **33,293
CODE-byte nonexact giant**. Its complete source-body SHA and original
438 separately owned after-RET switch DATA are independently verified
before compilation.

## What the original action0x335 actually does

Physical Japanese compressed-jump target `0x335` to *next nondefault*
`0x338` delimits precisely **1,022 native CODE bytes / 269 entire
x86 instructions**. IDs `0x336/0x337` are shared default-table
entries, **not real additional cases**. This source handles:

- An original `this+0x7C==6` stage reset and `S16(+0x80)=99` guard,
  followed by native parent actor signed state `+0xE4/+0x60`
  range `(0x45,0x96)`, a real positive own `+0x80` guard and
  `S16(+0x62)<11`. Under the range it resets via native `0045B830`,
  executes an **eight-iteration** parent effect spawn loop with genuine
  `00453A70(0x3E4)`, and conditionally spawns `0x3E3` after parent
  effect-frame saturation.
- Stage-zero initialization of signed `+0xD8/+0xDA/+0xDC` counters,
  native `0040FBB0(0,0,0)`, scale/color flags, and an original
  **raw** `+0xC8` argument to `0040FB70` with native **14.0f**
  speed—no erroneous floating conversion of its first input.
- Real x87 motion updates using signed direction `S8(+0x66)`, actual
  game floating globals **`00657CBC` and `00657478`**, followed by
  a stage-ten positional contact `F32(+0x48)-F32(+0x54)` against
  genuine threshold **`00657888`**. Contact sets float movement
  `(2.0f,2.0f)` and calls native `0040FB40(11)`.
- Original post-stage-ten fade/scale policy using native double
  constant `00659730`, float `006583FC`, unsigned color decrement,
  native reset `0045B830` or original signed state callbacks.
  Stage-six action uses a true `S16(+0xDC)` integer-to-FPU
  comparison against the **sum of actual global `0065782C`
  and owner `F32(+0xCC)`**, which controls `0040FB40(2)` and a
  signed counter increment. On original stage ten it emits native
  `00453D40(16)` and initializes float motion `(18.0f,18.0f)`.

The original source grammar is a full 269-instruction state machine,
not a leaf-only handler. The new ordinary C++ implementation in
[`probes/CharacterObjectActionsF572.cpp`](../probes/CharacterObjectActionsF572.cpp)
reproduces every original GPR allocation, x87 operand, actual contact
branch and original byte width, yielding **269 C++-compiled x86
instructions / 1,022 bytes** in one physical case.

## One explicitly limited read-only pair is not byte-exact original CODE

VC7.1 emits the actual native source's `F32(+0x48)` / `F32(+0x54)`
float arithmetic with one code-generation ordering difference. Original
instructions **146/147** are:

```asm
MOV EDX, [saved_this]
FLD DWORD PTR [ECX+0x48]
```

The new C++ emits `FLD` before `MOV`. Both operations are *independent
memory reads*; `MOV` writes EDX, while FLD reads ECX and changes only the
x87 stack. There is no intermediate branch, side effect or COFF field.
The verifier permits **only this explicitly bounded commutation**,
then requires every other native instruction (including GPR choice,
relative branch graph and opcode width) to match exactly. This is
source-semantic equivalence, **not physically exact machine CODE**.

A second independent source-codegen discovery: the actual native
stage-six comparison first performs `FLD` of global **`0065782C`**,
then `FADD` from actor `+0xCC`. A simple expression computes the same
sum but emits global and owner operands in reverse order. A normal C++
lvalue expression
`*(&gCompareAt0065782C) + *(&F32(0xCC))` forces the native
**global-first x87 order** while keeping the true values, unsigned
conditions and total instruction count. Eleven genuine VC7.1 source
expression variants were compiled and checked; no machine-code graft,
inline ASM or artificially padded C++ was used.

## The *neighboring* action0x332 improves naturally because of F578

This is important for whole-boss reconstruction. The earlier F577
*smaller* natural C++ switch emitted its entire action0x332 with
**279 x86 instructions / 1,013 CODE bytes** versus native
**279 / 1,019**, because original integer-to-FPU temporary
`EBP−0x9C` required two native disp32 operations while the smaller
candidate's temp at `EBP−0x80` allowed disp8.

**After adding genuine action0x335 to the very same source function,**
VC7.1 naturally moves this temporary to candidate **`EBP−0x84`**.
Both candidate `MOV/FILD` now use actual disp32 encoding; `0x332`
compiles to **279 / 1,019**, equal to the original entire inner-case
byte length, with no fake local variables or padding. The original
saved-temp location remains `EBP−0x9C` (the entire original containing
stack frame is not recovered), so equal instruction widths **must not
be misrepresented as exact original operand bytes**. F577's targeted
checker now recognizes *both* previously proven natural source
contexts: old `−0x80` compact, and richer F578 `−0x84` disp32.

The original `0x330`/`0x331` native frame still has 18 additional
bytes of width each, as checked from six real `MOV/FILD` disp32
operations per case. Their source register/branch grammar is still
correct and the remaining 36-byte difference is not patched.

## Real original PE/COFF receipts from one newly compiled TU

The new
[`scripts/verify-characterobject-contact-stage-f578.py`](../scripts/verify-characterobject-contact-stage-f578.py)
freshly compiles one selected C++ translation unit under pinned
VC7.1 `/Od /Ob0 /Gy /GR- /GX- /GS /Zi`, independently bounds
all game-action cases using original compressed native tables
(including correct default aliases), and compares each complete
native PE case against this **one enclosing source function**.
It verifies genuine `REL32`/`DIR32` physical COFF relocation type,
real original PE target identity, compiled source symbol, exact
native instruction ordinal and **zero relocation addend**.

| Native whole original game-action bodies | Original instructions | Original internal CODE (uncredited) | True typed COFF | Compiler limits |
| --- | ---: | ---: | ---: | --- |
| Previous 18 game cases through `0x332` | 2,333 | 8,612 B | 161 | Two bounded older read-only swaps; 36 bytes of genuine original deep-frame width |
| **New `0x335` complete case** | **269** | **1,022 B** | **17** | One bounded read-only MOV/FLD swap |
| **Total 19 original action bodies** | **2,602** | **9,634 B** | **178** | Whole 33,293-byte function still nonexact |

The full original source switch also preserves all **60 physical
zero-addend COFF jump-label DWORD slots**, authentic duplicate/default
handler partitions, **198/198 literal original compressed-index
bytes** with SHA256, and **438 separate post-RET DATA-layout bytes**.
These are DATA, not restored independent CODE.

### Affected-only reproducer

```bash
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/verify-characterobject-contact-stage-f578.py
# Independently revalidate all earlier game actions under this new source:
scripts/repo-python scripts/verify-characterobject-direction-reversal-f577.py
scripts/repo-python scripts/verify-characterobject-fade-actions-f575.py
scripts/repo-python scripts/verify-characterobject-action-family-f572.py
```

The new COFF/PDB/log/summary are retained under ignored
`.analysis/f578-characterobject-contact-source/`; eleven alternate
native x87 expression compiles, exact original 269-instruction
independent case disassembly and read-only swap controls live under
`.analysis/f578-characterobject-action335/`. F578 and prior F572–F577
prove no complete whole boss source acceptance, no independent partial
function or DATA credit, no all-unit cold replay and no external
Factory/Oracle acceptance receipt.
