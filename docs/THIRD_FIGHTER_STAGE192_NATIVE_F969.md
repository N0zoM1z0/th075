# F969 — Original third-fighter action192, native 177 x86 with integer FIADD

The original SHA-pinned Japanese TH075 v1.11 game
fighter **004AC040** has **82,796 complete callable
CODE B /22,721 x86** and separately owns
**1,126 afterRET jump-table DATA B**. The new
[tracked cumulative C++ source](../probes/FighterWhole004AC040F969.cpp)
is still a *partial* normal VC7.1 father.
Its native saved-`this` and full original
0x720 stack frame and many original actions
remain unimplemented. This giant is **NONEXACT**.

The next actual native game-state action
**192** physically occupies
**004B2611..004B28ED**, precisely
**732 original CODE B /177 x86
with eleven original typed PE fields**.
It differs from other fighters' historic
F734 eight-shot routines and from the
preceding 190/191 three-shot functions:

- Real stage0/frame0 initializes
  +0x7C=1, invokes ResetAt453E20 and
  clears BOTH signed 16-bit +0xF00
  and +0xF02 counters.
- Its real trigger is **stage>4,
  F00<=0, F02<5**, then native
  PrepareActionAt453D40(0) and
  StartAnimationAt46D000(0x28).
- It issues **three original
  00453A70(0x320) float-X/Y shots**
  with real angles
  **`F02*4+45/+49/+41`**
  stored at +0x314 and original
  float +0x318=7.0f before
  each individual call.
- Each original shot uses **X =
  `float((47−F02*10)*signedFacing)
  + real float this+0x44`**,
  and actual **Y = `this+0x48
  + PE global 00658264
  + signed F02*20`**.
  The original Y calculation uses
  x87 **FIADD of a genuine 32-bit
  signed integer temporary**,
  not ordinary FILD followed by
  FADD. All three FIADD occurrences
  are reproduced naturally in C++.
- Original signed short F00 is
  then assigned 2, F02 incremented,
  F00 decremented, and actual
  animation completion transitions
  to action **2**.

The new [natural C++ source](../probes/FighterThirdBossStage192F969.inc)
restores real original integer/float
evaluation order without faked
compiler scratch padding, manually
forced registers or copied target
instructions.

## Two whole-parent normal VC7.1 cold compiles

The bounded
[`verify-third-fighter-stage192-f969.py`](../scripts/verify-third-fighter-stage192-f969.py)
fresh-compiles two ENTIRE original-shaped
partial fathers from tracked F968/F969
sources. It decodes the SHA-pinned
original PE and checks native previous
190/191 147-x86 cases and new
192 177-x86 case, original individual
scratch opcode semantics, all **33
actual real source/PE call/global
typed targets**, and the physical
151 afterRET DIR32 labels plus
522 native nonfield DATA bytes.

| Whole partial father | F968 prior marker | F969 real 192 |
| --- | ---: | ---: |
| Emitted normal C++ CODE B | 26,893 | **27,610** |
| Emitted whole partial x86 | 7,403 | **7,578** |
| Source 192 B/x86 | 15/2 | **732/177** |
| Native original 192 B/x86 | 732/177 | **732/177** |
| Original 192 mnemonic differences | n/a | **0** |
| Original 192 instruction-width errors | n/a | **0** |
| Original 192 GPR-role errors | n/a | **121** |
| Actual original 192 PE targets | marker | **11/11** |
| Original 190/191 PE targets | 22 | **22** |
| Native afterRET DIR32/nonfield B | 151/522 | **151/522** |
| Entire 82KB original fighter exact | NO | **NO** |

This is a valuable illustration of
why **original code length and
instruction-width equality is NOT
complete original game byte exactness**.
All original 192 nine deep signed
integer-to-x87 temporary accesses
use physical **EBP−0xD8..−0xF8**.
The new partial source has actual
compiler-generated temporary
lvalues at **EBP−0x84..−0xA4**.
Both use long six-byte EBP
displacements so the x86 width
geometry agrees, but their real
machine operand bytes differ.
Furthermore the original game
GPR roles differ at 121 of
177 instructions, and many
whole-parent call/jump/relocation
positions remain different.

Reproduce ONLY this affected giant:

    scripts/repo-python scripts/verify-third-fighter-stage192-f969.py

The complete C++/OBJ/PDB, VC7.1
compiler output and original
physical PE-target verification
receipts are retained in ignored
`.analysis/f969-third-original-proof/`
and `.analysis/f969-third-192/`.

**No new accepted entire original
callable game CODE or functions;
no full 979-unit cold replay.**
