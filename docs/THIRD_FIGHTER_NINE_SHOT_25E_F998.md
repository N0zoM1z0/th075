# F998 — Original 25E nine-shot motion and a genuine downstream GPR phase regression

Pinned Japanese TH075 v1.11 original 004AC040 fighter owns
**82,796 callable CODE B /22,721 x86**, followed by 1,126
separate afterRET switch DATA B. The tracked
[normal VC7.1 cumulative partial C++](../probes/FighterWhole004AC040F998.cpp)
still does NOT match the complete original game function.

The original physical 25E state occupies **004BA229..004BA59B**,
**882 native CODE B /236 x86 /24 actual original PE fields**.
It is not an exact copy of the preceding 25C nine-shot state:
stage0/frame0 sets native int+0x7C=1 and shorts F00/F02=0,
scales actual float motion +0x50/+0x54 by original
**PE global 00657F74**, but does not call a nonexistent
stage0 ResetAt453E20. Signed stage>4 subtracts
vertical drag; animation completion transitions to action9.

At stage4/frame0, original code writes X speed **−3.0f**,
vertical speed **9.0f**, drag **0.7f**, prepares action0
and starts native animation0xFA. It then emits nine original
00453A70(**0x342**) sprite shots with true angles
**−28,−21,−14,−7,0,7,14,21,28**, speed10.0f,
*raw float-X bits* at +0x44 but float Y calculated as
original +0x48 plus native PE global **006590AC**,
signed facing and layer1.

The natural
[source C++](../probes/FighterThirdBossNineShot25EF998.inc)
retains nine distinct original calls, genuine source
operand types and evaluation order; no ASM, fake locals,
game-target byte grafts or masked relocation errors.

The bounded
[original PE verifier](../scripts/verify-third-fighter-nine-shot25e-f998.py)
freshly compiles two tracked ENTIRE original-shaped PARTIAL
82KB VC7.1 parent sources, F997 with 25E marker and F998
with real native 25E. It independently checks all **236
original positional x86 mnemonics and widths**, all
**24 actual zero-addend PE/COFF call/global destinations**,
prior real 25B/25C/25D and following genuine 25F/260/261/262,
all **151 native afterRET DIR32 table labels and 522
native DATA nonfield bytes**.

| Entire original-shaped PARTIAL father | F997 prior | F998 real |
| --- | ---: | ---: |
| Generated partial CODE B | 59,728 | **60,595** |
| Generated partial x86 | 16,387 | **16,621** |
| Real 25E inner source B/x86 | 15/2 marker | **882/236** |
| Wrong original 25E mnemonic/width positions | n/a | **0/0** |
| Wrong 25E native GPR roles | n/a | **153** |
| Real 25E original PE targets | marker | **24/24** |
| Partial father source frame | 0x434 | **0x434** |
| Complete original 82KB exact | NO | **NO** |

**Material cross-state result, including the regression:**
the real previous F997 25D source had repaired native
GPR roles in all four following ten-shot cases. Adding the
actual original 25E C++ reverses that compiler allocation phase:

| Following real original handler | Incorrect GPR roles before 25E | With 25E |
| --- | ---: | ---: |
| 25F, 114 x86 | 0 | **73** |
| 260, 114 x86 | 0 | **73** |
| 261, 98 x86 | 0 | **65** |
| 262, 98 x86 | 0 | **65** |

All four following original mnemonic sequences, instruction
widths and physical PE external destinations remain correct.
Prior 25B/25C/25D likewise retain their exact original
mnemonic/width geometry and PE destinations. Both father
source versions have the same 0x434 stack frame, so these
changes concern real register allocation roles rather than
artificial frame growth.

The native complete original has a **0x720 frame** and
saved `this` at EBP−0x64; the current partial C++ still has
wrong EBP scratch locations, absolute/relative whole-function
COFF positions and missing native game cases. Therefore
the internal 25E is **not independently accepted exact CODE**.

Rerun only the two affected whole-partial-parent compiles:

    scripts/repo-python scripts/verify-third-fighter-nine-shot25e-f998.py

Private C++/OBJ/PDB, compiler logs and original physical PE
receipts are preserved under ignored .analysis/f998-third-native-proof/
and .analysis/f998-third-25e/.

**New accepted whole original callable functions and CODE: zero.
No 979-unit full corpus cold replay.**
