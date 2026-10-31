# F993 — Two original 10-shot fighter loops, all 228 native GPR roles match

The SHA-pinned Japanese TH075 v1.11 fighter at 004AC040
has **82,796 original callable CODE B /22,721 x86** and
1,126 separately owned afterRET switch DATA bytes. The
[tracked original-shaped normal VC7.1 source](../probes/FighterWhole004AC040F993.cpp)
is still a *PARTIAL* parent, not a complete original exact function.

Two true physical original game handlers were independently decoded:

| Actual original case | Physical PE interval | Original native CODE/x86 | Real typed PE fields |
| --- | --- | ---: | ---: |
| **25F** | 004BA59B..004BA76D | **466 B /114 x86** | **9** |
| **260** | 004BA76D..004BA93F | **466 B /114 x86** | **9** |

The original genuine actor behavior sets int+0x7C=1 and resets
signed shorts+0xF00/F02 on stage0/frame0, calls ResetAt453E20,
**decrements signed short F00** every frame, and transitions on
actual animation completion to action0. At stage6/frame0,
F00<=0, F02<1 it prepares action0, starts animation0x96,
and executes a real **ten-iteration ordinary 32-bit signed C++
loop**. The body computes float angle **30−shot*6** into +0x314,
float +0x318=15.0f, and launches genuine
00453A70(**0x346** for 25F, **0x347** for 260)
with signed-facing×49 float X plus original +0x44, Y float
+ original PE global **00659294**, real signed facing and
layer1. After the ten shots it converts real signed shorts F00
and F02 to x87 float, multiplies each by the original float
global **00658044**, stores them at motion +0x50/+0x54,
sets F00=2 and increments F02.

The original C++ loop grammar naturally generates its
real **MOV scratch=0, forward JMP, increment, CMP scratch<10,
backward JMP** layout. Original 25F uses actual loop-local
**EBP−0x30**; original 260 independently uses **EBP−0x34**.
No fictitious extra stack variables, manual registers,
assembler, byte grafts or code slicing were introduced.

The bounded
[original whole-partial-parent verifier](../scripts/verify-third-fighter-ten-shot25f260-f993.py)
freshly builds TWO entire original-shaped PARTIAL 82KB normal VC7.1
fathers: tracked F991 with markers and F993 with real C++.
It independently reads the original executable and all
**228 positional original x86 mnemonic, instruction-width AND
GPR operand roles**, all **18 real zero-addend PE/COFF
external target destinations**, preceding genuine 25A and
all **151 original afterRET DIR32 case labels plus
522 original nonfield DATA bytes**.

| Whole original-shaped PARTIAL parent | F991 markers | F993 genuine |
| --- | ---: | ---: |
| Compiled partial source CODE B | 50,620 | **51,534** |
| Compiled partial x86 | 14,000 | **14,224** |
| 25F source native interior B/x86 | 15/2 | **466/114** |
| 260 source native interior B/x86 | 15/2 | **466/114** |
| Wrong original mnemonic/width/GPR roles | not aligned | **0 / 0 / 0 each** |
| Original real external PE field targets | markers | **9+9** |
| Partial source compiler stack frame | 0x348 | **0x370** |
| Entire original game fighter exact | NO | **NO** |

**Matching all 228 GPR roles is not full game CODE equality.**
The original whole parent saves `this` at EBP−0x64
and owns a 0x720 stack frame; the generated parent still
has different saved receiver and native scratch EBP
operands, absolute original branches and whole-function
relocation positions, plus unrecovered game states.
Inner states are never promoted into independent callable
original exact functions.

Reproduce only the two affected whole-shaped parent builds:

    scripts/repo-python scripts/verify-third-fighter-ten-shot25f260-f993.py

Complete compiled source/OBJ/PDB, VC7.1 logs and real PE
verification receipts remain in ignored
.analysis/f993-third-native-proof/ and
.analysis/f993-third-25f260/.

**New accepted whole original callable CODE: zero.
No all-979-unit cold replay.**
