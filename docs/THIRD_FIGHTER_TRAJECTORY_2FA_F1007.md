# F1007 — Original 2FA trajectory and recovery of prior 2E6 near shared-tail JMP

The pinned Japanese TH075 v1.11 original fighter 004AC040 is
**82,796 callable CODE B /22,721 x86**, followed by
**1,126 owned afterRET jump-table DATA B**.
[Tracked normal VC7.1 original-shaped PARTIAL father](../probes/FighterWhole004AC040F1007.cpp)
remains NONEXACT: its saved receiver, 0x720 original
stack frame and unsourced game actions differ.

Real native action 2FA occupies **004BF16E..004BF40E**:
**672 original CODE B /186 x86 /18 genuine physical PE
call/global destination fields**. Original stage0 resets
motion and shorts F00/F02/F04/F06 and sets signed short
F08 to actual signed global mode **006714D0**+2.

The real game checks floating Y against native ground
**0065782C**, subtracts vertical drag and on landing
invokes auxiliary action15, resets motion, sets Y=0
and exits through the original shared tail. It increases
short F00 every frame. At signed stage4..10, when F00>8,
resets F00, writes float angle−45.0f to +0x314,
emits one genuine 00453A70 sprite **0x38E** with actual
RAW 32-bit X+0x44, float Y+original global **00657888**,
signed facing and layer1, then prepares action12.

Original animation completion transitions to action0
and stores short+0x516 = genuine random[60,120]
minus signed mode×20. At stage2/frame0, it sets
vertical velocity16.0f, drag0.5f and random horizontal
speed [12,18]. The game flips horizontal velocity
depending on signed facing and **two distinct native
absolute world-X bounds**: right **0065945C** and
left **00657888**. Real shared FCHS/FSTP branching is
preserved in natural source rather than copied byte code.
At stage11/frame0, bounded F02 auxiliary action4 occurs;
stage15/frame0 invokes auxiliary action13.

The ordinary
[actual C++ source](../probes/FighterThirdBossTrajectory2FAF1007.inc)
emits all **186 native mnemonic positions**, but source
size is **669B** versus original **672B**. The sole
original width mismatch is the final shared-tail JMP:
5-byte original near versus 2-byte incomplete-parent
short. There remain 113 original GPR-role differences.
All **18 actual zero-addend typed PE/COFF targets**,
including world bounds, random getter and grounded float
constants, were independently checked.

**Crucial cross-case compiler effect:** the real 2FA
source grows the entire partial father just enough to
restore the preceding genuine 2E6's last shared-tail
JMP to native *5-byte near* form. The full source
now compiles native **2E6=2,058B/590 x86 with zero wrong
mnemonics, widths and GPR roles**, and all 47 genuine
external PE destinations still correct. The earlier
2E6 had one shared-tail JMP width debt. No fabricated
padding or register hints were added to obtain this.

The [bounded full-original-shaped verifier](../scripts/verify-third-fighter-trajectory2fa-f1007.py)
freshly builds TWO ENTIRE PARTIAL 82KB normal VC7.1
fathers, F1005 prior 2FA marker and F1007 genuine
2FA. It independently verifies the pinned original PE
for both cases, earlier 2E5 and all 2C0..2C3,
all 18+47 actual typed PE fields, **151 native afterRET
DIR32 local labels and 522 original nonfield DATA B**.

| Whole original-shaped partial source | F1005 old | F1007 real 2FA |
| --- | ---: | ---: |
| Compiled partial CODE B | 66,877 | **67,546** |
| Compiled partial x86 | 18,344 | **18,528** |
| Real 2FA generated B/x86 | 12/2 marker | **669/186** |
| Wrong native 2FA mnemonic/width/GPR | n/a | **0/1/113** |
| Real native 2FA PE fields | marker | **18/18** |
| Previous real 2E6 generated B/x86 | 2055/590 | **2058/590** |
| Previous original 2E6 wrong widths | 1 (last JMP) | **0** |
| Previous original 2E6 wrong mnemonic/GPR | 0/0 | **0/0** |
| Compiler partial father frame | 0x4D8 | **0x4DC** |
| Entire original callable exact | NO | **NO** |

Restoring an inner case's original JMP width and all
GPR roles does not provide whole 82KB byte equality.
Native original receiver EBP−0x64, real 0x720 frame,
many physical whole-parent COFF fields, all remaining
unsourced action bodies and other original branch owners
must still be reconstructed.

Reproduce only the two affected complete PARTIAL parent builds:

    scripts/repo-python scripts/verify-third-fighter-trajectory2fa-f1007.py

Original PE receipt and normal VC7.1 C++/OBJ/PDB/compiler
logs are in ignored .analysis/f1007-third-native-proof/
and .analysis/f1007-third-2fa/.

**No new accepted exact original complete callable CODE/functions;
no 979-unit cold replay.**
