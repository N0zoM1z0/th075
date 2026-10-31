# F1009 — Native 2FB rebound source repairs preceding 2FA shared-tail JMP

The SHA-pinned Japanese TH075 v1.11 original fighter
004AC040 contains **82,796 callable original CODE bytes /
22,721 x86 instructions**, plus separately owned 1,126
afterRET switch DATA bytes. The
[tracked growing original-shaped normal VC7.1 C++](../probes/FighterWhole004AC040F1009.cpp)
remains a PARTIAL parent, NOT the complete original 82KB
game callable (original stack frame 0x720 and saved receiver
EBP−0x64 are still wrong).

The real original 2FB action lies at **004BF40E..004BF9A2**,
**1,428 native CODE bytes / 411 ordered x86 instructions /
33 genuine zero-addend typed PE external target fields**.

The original stage0 resets motion, sets int+0x7C=1,
signed flag+0x3AC=0 and shorts F00/F02=0. Stage6/7
reduces unsigned opacity byte+0x11 by 20, clamped to
zero without incorrectly exiting the frame. Stage9..12
subtracts vertical drag, increases opacity (clamped
255), then detects Y contact with original ground global
**0065782C**; the real contact path restores opacity255,
resets motion, enters auxiliary action13 and sets Y=0.

Stage2..7 generates the genuine randomized seven-argument
sprite **0x33E**, using original world-X offset
**00658264** and float Y offset **00657CBC**.
Stage9/frame0 first zeroes X/Y speed and increments F00.
On native animation completion the original explicitly
transitions to **action0x2F9**, NOT action0.

At stage6/frame0 it prepares action2, issues **six separate
native seven-argument sprites 0x338 through 0x33D** with
signed-facing×7 integer FILD, FSUBR world X+0x44,
Y+physical global **00659490**, and true facing/layer
flags. It then starts animation0xC8, invokes
SetMotionStateAt40FBB0 and sets opacity255.

At stage8/frame0 the original first performs bounded F02
auxiliary6 and exits while F02<4. Its next stage8 path
draws random X velocity Rand(0,480)−240 and applies
additional original-facing-relative bounds at **0065787C**
and **0065920C** with separate Rand(0,180)+90 calls.
It sets vertical speed3.0f, drag0.5f. Stage9/frame0
compares original actor/opponent X+0x44 through real
FCOMP memory, choosing signed facing−1 or+1; stage13
invokes auxiliary11.

The
[ordinary C++ implementation](../probes/FighterThirdBossRebound2FBF1009.inc)
reuses independently native-verified borrowed X views,
not a guessed complete original fighter. The entire
normal VC7.1 PARTIAL father naturally emits the correct
**411 ordered original mnemonic and GPR operand roles**.
All **33 actual physical original PE/COFF destinations**
were independently checked, including both world bounds
and randomized projectile globals. The source is
**1,425B/411 x86** against original 1,428B/411 x86.
Its ONLY ordered width error is the final shared-tail
JMP: original five-byte near versus incomplete-parent
two-byte short. No fake locals, manual registers,
injected target bytes or relaxed relocation fields were used.

**Real preceding-case JMP recovery:** the original 2FA
native action at 004BF16E previously had one five-byte
shared JMP width error. Adding genuine preceding-later
2FB C++ changes entire parent control-flow geometry;
2FA now compiles its original **672B/186 x86 with
zero mnemonic, width or GPR differences**. Earlier 2F9,
2E6, 2E5 and 2C0..2C3 retain all their original
mnemonic/width/GPR roles and PE destinations.

The [independent complete-partial-parent PE verifier](../scripts/verify-third-fighter-rebound2fb-f1009.py)
freshly builds TWO tracked ENTIRE original-shaped normal
VC7.1 father sources, F1008 marker and F1009 real 2FB.
It checks all 411 original mnemonic/GPR positions,
the remaining one real width mismatch, all **33 original
typed PE fields**, all preceding genuine actions,
**151 original afterRET DIR32 local labels** and
**522 native nonfield DATA bytes**.

| Entire original-shaped PARTIAL fighter | F1008 prior | F1009 genuine |
| --- | ---: | ---: |
| Compiled partial CODE B | 68,785 | **70,201** |
| Compiled partial x86 | 18,852 | **19,261** |
| Real 2FB generated B/x86 | marker 12/2 | **1,425/411** |
| Wrong original 2FB mnemonic/GPR | n/a | **0/0** |
| Wrong original 2FB x86 widths | n/a | **1 (final JMP)** |
| Original actual 2FB PE targets | marker | **33/33** |
| Prior 2FA source B/x86 | 669/186 | **672/186** |
| Prior 2FA wrong width/GPR | 1/0 | **0/0** |
| Partial compiler stack frame | 0x50C | **0x53C** |
| Whole original 82KB callable exact | NO | **NO** |

The original whole receiver saved at EBP−0x64, true
0x720 frame, native scratch stack displacements, other
unsourced game-state bodies and entire physical PE/COFF
fields still differ. Matching any cropped internal case
is NOT independently accepted callable original CODE.

Reproduce only these two complete PARTIAL parent builds:

    scripts/repo-python scripts/verify-third-fighter-rebound2fb-f1009.py

Original PE receipts and serial VC7.1 C++/OBJ/PDB,
compiler logs are saved under ignored
.analysis/f1009-third-native-proof/ and
.analysis/f1009-third-2fb/.

**No newly accepted whole original callable CODE/functions;
no all-979-unit cold replay.**
