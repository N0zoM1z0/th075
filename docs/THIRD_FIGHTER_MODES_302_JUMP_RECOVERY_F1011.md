# F1011 — Native action302 mode loops repair preceding 2FB shared JMP

The SHA-pinned Japanese TH075 v1.11 original fighter 004AC040
has **82,796 original callable CODE B /22,721 x86**, followed
by **1,126 separately owned afterRET switch DATA B**.
The tracked
[original-shaped partial normal VC7.1 fighter](../probes/FighterWhole004AC040F1011.cpp)
is still **NONEXACT** as a whole: real original frame0x720,
saved receiver EBP−0x64 and other game states remain missing.

Original action302 occupies **004BF9A2..004BFDAB**,
**1,033 native CODE bytes/279 x86/25 actual typed zero-addend
PE external target fields**. Native stage0 resets motion,
shorts F00/F02/F04 and stores F08=signed PE mode global
**006714D0**+2. At signed stage<13, if original Y+0x48
is above ground **0065782C**, vertical speed+0x54
loses drag+0x5C and is clamped to 1.0f if <= original
float PE global **0065747C**. Later, at stage>12,
actual ground collision sets Y=0, resets motion and
enters auxiliary action15. The two native floating-point
conditions retain their original FCOMP+FNSTSW branch order.

Original animation completion invokes 0040FA30/
0040FAC0(0), then real random draw [0,60]+180
minus signed mode×20 stores to short+0x516.
Stage2/frame0 sets vertical speed13.5f, drag0.5f.
Stage5/frame0 prepares action5 and chooses one of
FOUR ordinary 32-bit signed C++ loops, independently
observed from the original executable:

| Genuine original mode | Sprite 0x389 shots | Angle step |
| --- | ---: | ---: |
| 0 | **10** | **36°** |
| 1 | **12** | **30°** |
| 2 | **15** | **24°** |
| 3 | **20** | **18°** |

Each loop stores float +0x314=shot×step and float
+0x318=4.0f, launches native 00453A70(0x389)
with signed-facing×16 FILD/FSUBR world X+0x44,
float Y+physical PE global **0065836C**, signed
facing and layer1. The
[normal C++](../probes/FighterThirdBossModes302F1011.inc)
uses original game values and source evaluation order
without fake stack variables, manual register hints or
original target-machine-code grafts.

The
[bounded whole-PARTIAL-parent verifier](../scripts/verify-third-fighter-mode-loop302-f1011.py)
freshly compiles two tracked ENTIRE 82KB original-shaped
normal VC7.1 C++ parents (F1009 previous marker and
F1011 genuine 302). It compares all **279 original
mnemonic and GPR operand positions**, all **25 actual
typed PE/COFF destinations**, eight preceding native
game actions, and the entire **151 native afterRET DIR32
local labels plus 522 original nonfield DATA B**.

The original action302 source is **1,030B/279 x86**
versus native **1,033B/279 x86**; the sole width
mismatch is its final five-byte near JMP to shared
parent tail versus current short two-byte JMP.
The real partial father has not recovered the complete
original physical shared tail or EBP stack slots.

**Independent cross-state recovery:** adding real 302
makes the PRECEDING genuine 2FB change its final
shared-tail JMP from nonnative short2B to original
near5B without altering 2FB source or adding fake
padding. The complete 2FB source now generates
**1,428B/411 x86 with ZERO native mnemonic, width
and GPR-role differences**, preserving its 33 genuine
PE targets. All earlier real 2FA/2F9/2E6/2E5 and
2C0..2C3 native mnemonic/width/GPR roles and external
PE targets remain unchanged.

| Entire original-shaped PARTIAL source | Prior F1009 | F1011 real 302 |
| --- | ---: | ---: |
| Generated partial CODE B | 70,201 | **71,250** |
| Generated partial x86 | 19,261 | **19,538** |
| 302 source B/x86 | 12/2 marker | **1,030/279** |
| Wrong original 302 mnemonic/GPR | n/a | **0/0** |
| Wrong original 302 widths | n/a | **1 (final JMP)** |
| Real original 302 PE targets | marker | **25/25** |
| Previous 2FB generated B/x86 | 1,425/411 | **1,428/411** |
| Previous 2FB wrong widths | 1 | **0** |
| Compiler PARTIAL stack frame | 0x53C | **0x56C** |
| Whole original 82KB callable exact | NO | **NO** |

Matching inner cases, register roles and relative
shared-tail widths is not independently accepted whole
original callable CODE. Remaining native game actions,
receiver EBP/frame, original COFF locations and physical
branch displacements still differ.

Reproduce only the two affected complete partial parents:

    scripts/repo-python scripts/verify-third-fighter-mode-loop302-f1011.py

Full original PE receipts and serial VC7.1 source/OBJ/PDB
logs are retained under ignored
.analysis/f1011-third-native-proof/ and
.analysis/f1011-third-302/.

**New accepted original whole callable CODE/functions: zero.
No all-979-unit cold replay.**
