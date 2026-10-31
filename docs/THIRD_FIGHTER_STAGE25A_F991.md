# F991 — True original fixed-angle five-shot action 25A

The pinned original Japanese TH075 v1.11 004AC040 fighter is
**82,796 complete callable original CODE B /22,721 x86**,
with 1,126 separately owned afterRET DATA bytes. The
[tracked original-shaped partial VC7.1 source](../probes/FighterWhole004AC040F991.cpp)
still differs from the original whole 82KB game function.

The original native 25A occupies **004B823F..004B84BA**,
**635 complete native interior CODE B /166 x86 /15 real
original typed PE/COFF external fields**. Unlike 258/259,
this actor action is NOT gated by a F02 counter loop:
stage0/frame0 initializes +0x7C=1, ResetAt453E20,
shorts+0xF00/+0xF02=0, and on real native animation
completion transitions to action0. At **stage5/frame0**
it prepares action0, then emits **five individual**
native sprite00453A70(0x325) calls with actual float
angles **10,5,0,5,10** in +0x314, float +0x318=10.0f,
integer facing×97 converted to float and added to original
X+0x44, original float Y+PE global **00659498**, signed
facing and layer 1, then starts animation **0xFA**.

The natural
[C++ gameplay source](../probes/FighterThirdBossFiveShot25AF991.inc)
preserves every native shot and call order, no dummy locals,
copied target bytes, artificial padding or source-only loop
unrolling.

The bounded
[original PE source verifier](../scripts/verify-third-fighter-five-shot-25a-f991.py)
freshly builds TWO ENTIRE original-shaped PARTIAL 82KB normal
VC7.1 fighters (F990 marker and F991 genuine source), checks
all 166 ordered original mnemonic/width positions, all
**15 native original typed PE call/global destinations**,
the preceding real F990 259 case (15 fields, three existing
wrong original register-specific ADD widths), all **151
real afterRET DIR32 labels and 522 native DATA nonfields**.

| Whole original-shaped partial father | F990 prior | F991 real 25A |
| --- | ---: | ---: |
| Emitted partial CODE B | 50,000 | **50,620** |
| Emitted partial source x86 | 13,836 | **14,000** |
| 25A source CODE B/x86 | marker 15/2 | **635/166** |
| Wrong original 25A mnemonic/width | n/a | **0/0** |
| Actual original 25A PE target fields | marker | **15/15** |
| Wrong native GPR roles | n/a | **97** |
| Real partial source frame | 0x334 | **0x348** |
| Whole original 82KB exact | NO | **NO** |

The original game saves receiver at EBP−0x64 and owns a
0x720 frame, still not recovered here. Many original
global relative/absolute call-field positions and GPR
roles remain nonnative. Exact CODE credit can be granted
only to the entire callable original, not to an internal
switch branch.

Reproduce the two affected complete partial parents only:

    scripts/repo-python scripts/verify-third-fighter-five-shot-25a-f991.py

Original PE, C++/OBJ/PDB and VC7.1 compile logs are retained
in ignored .analysis/f991-third-original-proof/ and
.analysis/f991-third-25a/.

**Zero newly accepted original whole callable CODE or functions;
no 979-unit corpus cold replay.**
