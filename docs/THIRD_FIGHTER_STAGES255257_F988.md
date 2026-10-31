# F988 — Real original third fighter actions 255/256/257

The pinned Japanese TH075 v1.11 original fighter 004AC040
owns **82,796 complete callable original CODE B/22,721 x86**
plus **1,126 separately relocated afterRET jump DATA bytes**.
The tracked [partial original-shaped fighter C++](../probes/FighterWhole004AC040F988.cpp)
remains NONEXACT as a whole game callable.

| Original native state | Physical original CODE range | Full native interior | Genuine PE fields |
| --- | --- | ---: | ---: |
| **255** | 004B7906..004B7A08 | **258B/75 x86** | **7** |
| **256** | 004B7A08..004B7AB8 | **176B/52 x86** | **5** |
| **257** | 004B7AB8..004B7BB0 | **248B/72 x86** | **6** |
| Three original states | contiguous | **682B/199 x86** | **18** |

The original fighter initializes stage0/frame0 by calling
ResetAt453E20, setting signed short +0x80=1, int+0x7C=0,
flag+0x3AC=0 and short +0xF00=0. Frame completion uses
genuine 0040FA30/0040FAC0(**9**). Stage5/frame0
launches original sprite **0x37** through the real
00453C80 with raw integer X+0x44, float Y+PE global
**00657888**, signed facing+0x66, and layer1.

The native actions differ in actual gameplay:

- **255:** additionally prepares action **0x21** after
  the projectile; stage8/frame0 increments bounded
  short+0xF00 and invokes auxiliary action6.
- **256:** stops after its stage5 projectile and
  **does NOT** perform either the action0x21 preparation
  or a stage8 auxiliary branch.
- **257:** has the stage8 bounded F00 auxiliary action6
  branch, but **no** stage5 action0x21 preparation.

The [ordinary original C++](../probes/FighterThirdBossStages255257F988.inc)
expresses all three actual operations without assembler,
filler locals, compiler-only branches or target-byte grafts.

The [targeted PE verifier](../scripts/verify-third-fighter-stages255257-f988.py)
freshly compiles TWO ENTIRE original-shaped PARTIAL normal
VC7.1 father sources, F987 previous markers and F988 real
native states. It independently rereads the pinned original
PE, checks all **199 original positional x86 mnemonics and
widths**, all **18 typed zero-addend original PE/COFF
target addresses**, the preceding original 254
whose source start is derived from real 253's 72-x86
terminus (original 254 lacks a jump-table label),
all **151 native afterRET DIR32 labels**, and
all **522 original nonfield DATA bytes**.

| Whole partial original-shaped father | F987 marker | F988 genuine |
| --- | ---: | ---: |
| Compiled source CODE B | 47,715 | **48,352** |
| Emitted source x86 | 13,223 | **13,416** |
| 255 source B/x86 | 15/2 | **258/75** |
| 256 source B/x86 | 15/2 | **176/52** |
| 257 source B/x86 | 15/2 | **248/72** |
| Wrong original mnemonic/width positions | not aligned | **0/0 all three** |
| Wrong native GPR roles | not aligned | **46/32/46** |
| Actual original PE fields checked | stubs | **7+5+6** |
| Entire 82KB fighter exact | NO | **NO** |

All x86 instruction widths align, but the native game
saved receiver EBP−0x64, original full 0x720 frame,
many unsourced actions, GPR roles and whole-parent
relative/absolute PE fields still differ. Internal cases
must not count as accepted whole native functions.

Reproduce ONLY touched partial giant sources:

    scripts/repo-python scripts/verify-third-fighter-stages255257-f988.py

Compiler C++/OBJ/PDB, original PE receipts and VC7.1 logs
reside in ignored .analysis/f988-third-original-proof/ and
.analysis/f988-third-255-257/.

**New accepted whole original callable functions/CODE: zero.
No all-979-unit cold replay.**
