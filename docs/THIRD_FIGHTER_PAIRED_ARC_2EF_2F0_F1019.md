# F1019 — Original 2EF/2F0 arc pair recovers full 22,721-x86 fighter count

Pinned Japanese TH075 v1.11 original at 004AC040 is **82,796
whole callable CODE B /22,721 x86**, followed by 1,126 separately
owned afterRET jump-table DATA B. The tracked
[original-shaped normal VC7.1 father](../probes/FighterWhole004AC040F1019.cpp)
now produces **82,802 CODE B/22,721 x86**. The entire
original instruction COUNT is recovered; whole-function CODE
equality, original frame and GPR ownership are not.

| Real native action | Physical interval | True CODE/x86 | Original PE fields |
| --- | --- | ---: | ---: |
| 2EF | 004BDB1E..004BE3D3 | **2,229B/573 x86** | **80** |
| 2F0 | 004BE3D3..004BEC88 | **2,229B/573 x86** | **80** |

These two original states have precisely six actual operand
differences: native stage<22 fall-global00658044 versus 00658354;
stage13 vertical speed1.5f versus3.5f; and the four later
random shot angle offsets minus50 versus minus70. Their first
stage15 shot angle both subtracts70. The other 567 original
x86 ordinal roles and their physical control flow are identical.

Original stage0 initializes shorts F00/F02/F04, int+0x7C,
resets motion and sets short+0x80=99. Ground rules use
true float PE global0065782C, vertical drag, real
stage22/stage34 collision, auxiliary34, motion reset and Y=0.
Animation completion invokes 0040FA30/0040FAC0(0);
Rand(60,120) is stored to short+0x516. Stage13 prepares
action7, selects X speed Rand(0,6)−3, real Y speed1.5/3.5f
and drag0.5f.

At stages **15,17,19,21,23**, each actor independently
quantizes float velocities at offsets0x50/0x54 through
the native 00657888 float and __ftol2 into shorts F00/F02,
draws an independent angle Rand(0,100)−70 or−50 and
speed Rand(0,10)+5, and invokes native 0040FB70 with the
real **raw 32-bit float angle bits** and float100. Each
fires authentic sprite0x38F with float Y+original
global0065908C minus vertical speed and native world-X
expression: (global00658264 + actor speed0x50) times
signed facing plus actor X0x44, through real FIMUL.
Velocities restore from original signed F00/F02 and
global00658044, then native action7 is prepared.
Stage23 has the actual nested F04 limiter:
F04 < signed-mode global006714D0×2+8, then F04++
and auxiliary15. Stage34 invokes auxiliary32.

## What the original C++ grammar experiments actually establish

The initial complete father source emitted thirteen
extra instructions in each case. Eight were genuine
non-original repeated stage23/frame0 comparisons; moving
the REAL limiter inside the already verified stage23
branch restored the native 573-instruction CFG. A
float-typed 0040FB70 method argument caused nonoriginal
FLD/FSTP; using a declaration-only raw32 angle parameter
and I32(0x314) recovered original MOV/PUSH bit passing.

Finally, using a mutable actor speed float made VC7.1
generate FLD actor+0x50 then FADD global00658264, reversing
the native x87 operand order. Seven full-parent real C++
variants were cold compiled; a borrowed **const float
read of actor+0x50** (also volatile reads) naturally emits
original FLD global/FADD actor with correct x86 widths.
The selected [native source](../probes/FighterThirdBossPairedArc2EF2F0F1019.inc)
uses the const borrowed value: no fake stack locals,
ASM, forced registers, target-byte grafts or relocation masks.

The [bounded whole-father verifier](../scripts/verify-third-fighter-paired-arc2ef2f0-f1019.py)
fresh-compiles TWO tracked ENTIRE 82KB original-shaped
PARTIAL VC7.1 parents, F1018 markers versus real F1019.
Both native 2EF/2F0 now have **zero wrong mnemonic,
width and GPR roles over all 1,146 original instructions**,
and **160/160 physically typed zero-addend original PE
destinations verified**. It checks the original whole
22,721-instruction count, preceding and following genuine
native cases, all **151 original afterRET DIR32 local
labels and 522 original nonfield DATA bytes** and the
separate common epilogue.

| Complete original-shaped PARTIAL father | Prior F1018 | F1019 real |
| --- | ---: | ---: |
| Compiled partial CODE B | 78,374 | **82,802** |
| Compiled partial x86 | 21,579 | **22,721** |
| Original complete CODE B/x86 | 82,796/22,721 | **82,796/22,721** |
| Original 2EF source B/x86 | marker15/2 | **2,229/573** |
| Original 2F0 source B/x86 | marker15/2 | **2,229/573** |
| Both original states wrong mnemonic/width/GPR | n/a | **0/0/0** |
| Real original case PE fields | markers | **80+80** |
| Compiled parent frame | 0x654 | **0x724** |
| Original native frame | 0x720 | **0x720** |
| Preceding 2BE original GPR defects | 125 | **125** |
| Whole native callable exact | NO | **NO** |

**The remaining mismatches are real.** The compiled
82,802B parent is six CODE bytes longer than the
82,796B original, saved this uses EBP−0x68 rather
than EBP−0x64, frame0x724 rather than0x720, prior
2BE still has 125 wrong GPR operand roles and other
native absolute/relative whole-parent sites remain
different. Never award complete original CODE credit
based on a matching x86 instruction COUNT.

Reproduce only two relevant whole-PARTIAL-parent builds:

    scripts/repo-python scripts/verify-third-fighter-paired-arc2ef2f0-f1019.py

Original PE receipts and genuine full-parent C++/OBJ/PDB
and seven natural grammar controls are retained under
ignored .analysis/f1019-third-native-proof/
and .analysis/f1019-third-2ef2f0/.

**Zero new accepted exact whole original callable CODE B;
no corpus-wide 979-unit cold replay.**
