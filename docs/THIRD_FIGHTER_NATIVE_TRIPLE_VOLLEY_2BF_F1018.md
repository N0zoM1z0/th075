# F1018 — Original 2BF five triple volleys; all 616 native GPR roles aligned

The SHA-pinned Japanese TH075 v1.11 original fighter
004AC040 is one **82,796B/22,721-x86 callable**, followed
by 1,126 separately owned afterRET switch DATA bytes.
The [tracked growing original-shaped VC7.1 parent](../probes/FighterWhole004AC040F1018.cpp)
is still a PARTIAL source, not the original whole exact callable;
the native receiver EBP−0x64, 0x720 stack frame and missing
case bodies have not been recovered.

Physical original action2BF occupies **004BB831..004BC0A8**:
**2,167 native CODE B, 616 native x86 and 65 real typed,
zero-addend PE call/global target fields**. It is NOT merely
the preceding 2BE actor with renamed sprites.

Stage0/frame0 sets signed F00=0, int+0x7C=0, resets the actor
and sets short+0x80=99. The real ground collision stage23..34
uses global0065782C, motion drag, actual auxiliary34 and resets
Y to0. The original animation-completion flow calls
0040FA30/0040FAC0(0). Stage4/frame0 invokes
00453E80(40), 00453D60(0x17), reduces float+0x36C
by native00657888 and fires sprite0x74 using signed-facing×30
FILD/FADD world X and float Y plus native00658268.
Stage13 prepares action7 and sets actual X speed0.5f,
Y speed0.9f, drag0.5f and short+0x84=20.

Each of **five separate original stages 15,17,19,21,23**
at frame0 performs THREE authentic projectile calls,
in this precise observed original order:

1. Sprite **0x322 + (Rand(0,100)>200)** at signed-facing×60
   FILD/FADD world X and Y+original global0065908C.
2. Fixed sprite **0x340** with the same native X/Y grammar.
3. Sprite **0x341** at actor X minus signed-facing×640,
   converted through **FILD/FSUBR**; the original Y is
   actor+0x48 + physical global **0065784C** minus a separate
   float(Rand(0,400)), with true x87 evaluation order.

Only **after all three projectiles** does the original
call StartAnimationAt46D000(0xC) then prepare action7.
Stage23 increments signed F00 and invokes auxiliary15
only for F00<10. Stage34 invokes auxiliary32.

The [natural C++ source](../probes/FighterThirdBossTripleVolley2BFF1018.inc)
preserves 15 real separate calls and the five independent
stage branches. No injected native bytes, fabricated unused
locals, register tricks, ASM or masked relocations are used.

The bounded
[original PE/COFF verifier](../scripts/verify-third-fighter-triple-volley2bf-f1018.py)
freshly compiles TWO tracked ENTIRE original-shaped PARTIAL
82KB fathers (F1017 prior marker and F1018 genuine C++).
It checks **all 616 ordered original mnemonics, widths AND
GPR operand roles**, **65 physically genuine original PE
targets**, preceding real2BE, following real 2C0–2C3,
2DB/2E5/2E6 and 303, and all **151 original afterRET
DIR32 labels plus 522 true nonfield DATA bytes**.

| Complete original-shaped PARTIAL father | F1017 prior | F1018 selected |
| --- | ---: | ---: |
| Generated partial CODE B | 76,222 | **78,374** |
| Generated partial x86 | 20,965 | **21,579** |
| Real 2BF source B/x86 | marker 15/2 | **2,167/616** |
| Wrong native mnemonic/width/GPR roles | unaligned | **0/0/0** |
| Real original 2BF typed PE targets | marker | **65/65** |
| Preceding 2BE GPR role defects | 125 | **125** |
| Later true game state GPR roles | aligned | **still aligned** |
| Generated PARTIAL frame | 0x5EC | **0x654** |
| Entire original callable exact | NO | **NO** |

**A negative result matters:** adding genuine 2BF does NOT
repair preceding original 2BE's 125 GPR-role differences.
Original 2BE still matches all 1,607 CODE B, 471 native
mnemonic and width positions and 50 PE targets, but not
the original full machine instructions. Neither cropped
case is accepted as an independent whole callable.
Full original 82KB frame, receiver, COFF and all remaining
native cases must still be reconstructed.

Reproduce only the two affected original-shaped parent compiles:

    scripts/repo-python scripts/verify-third-fighter-triple-volley2bf-f1018.py

True PE evidence and normal VC7.1 C++/OBJ/PDB compiler
logs remain in ignored .analysis/f1018-third-native-proof/
and .analysis/f1018-third-2bf/.

**New credited exact whole original callable CODE: zero.
No all-979-unit mass cold replay.**
