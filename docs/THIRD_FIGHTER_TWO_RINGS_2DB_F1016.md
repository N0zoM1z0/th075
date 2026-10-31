# F1016 — Original 2DB double 36-shot rings, 548 native GPR roles matched

The SHA-pinned Japanese TH075 v1.11 fighter at original
004AC040 owns **82,796 whole-callable CODE B /22,721 x86**,
plus 1,126 original afterRET jump-table DATA bytes.
The [tracked original-shaped normal VC7.1 C++](../probes/FighterWhole004AC040F1016.cpp)
remains a PARTIAL father and does NOT reproduce original
whole-game receiver EBP−0x64, original 0x720 frame,
all remaining case bodies or all physical PE/COFF sites.

The true original game state2DB occupies physical
**004BC8B1..004BD017**, exactly **1,894 CODE B /548 x86 /
38 genuine typed zero-addend PE external target fields**.
It is not a copy of 2E6. Native stage0 resets motion,
int+0x7C=0, signed FLAG+0x3AC=0, shorts F00/F02/F04/F06
and sets drag0.2f. Stage6/7 reduces opacity by30 or
enters auxiliary8. Stage8/frame0 draws Rand(0,100)−50
and Rand(0,30)−15 as horizontal/vertical velocity,
and compares actual actor/opponent X+0x44 with the
previously native-verified borrowed X views to update facing.
Stage9 increases opacity by30, bounded to255.

At stages15/16 with F00<2 it reduces opacity by40, with
auxiliary8 and original shared-tail exit in its native
zero-opacity branch. Stages18/19 subtract vertical drag
and increase opacity by20, with auxiliary20 when clamped
to255. At stage20/21 the true landing/ground threshold
**0065782C** resets motion, opacity and Y, enters
auxiliary22, and exits via the shared parent tail.

Stage2..7 generates one genuine randomized
seven-argument **0x33E** effect using native
globals **00658264/00657CBC**. Animation completion
uses native 0040FA30/0040FAC0(0). Stage6/frame0
prepares action2 and generates **six separate original
0x338–0x33D seven-argument effects**, all signed-facing×7
FILD/FSUBR world-X and Y global **00659490**. It then
resets motion and opacity255. Stage8 has bounded
auxiliary6; stage9 zeroes X/Y velocities.

At stage11/frame0 the native body increments short F00,
clears F06 and executes TWO distinct ordinary signed
C++ loops, each **36 sprite0x385 projectiles at angles
0,10,...,350**. Each has the genuine facing×8
FILD/FSUBR X and original float Y+physical global
**00659460**. The original first loop stores float
speed **5.0f**, the second **10.0f**; it is not one
72-shot loop. Stages17/20/22 then invoke original
auxiliary actions15/18/20 with the native F06 count
guard at stage17.

The [genuine C++ source](../probes/FighterThirdBossRing2DBF1016.inc)
generates **ALL 548 original positional mnemonic,
x86 instruction widths and GPR operand roles**, plus
**38 actual native PE call/global targets**. The two
genuine signed angle loops compile their native FILD
and backward JMP geometry without assembler, fake
locals, copied target bytes or relocation masking.

The bounded
[original PE verifier](../scripts/verify-third-fighter-ring2db-f1016.py)
freshly compiles TWO tracked ENTIRE original-shaped
PARTIAL 82KB fathers (F1014 old marker and F1016
native 2DB). It checks the complete original SHA,
all 548 native roles, actual PE fields, four preceding
2C0–2C3 cases and eight following 2E5/2E6/2F9–303,
and all **151 original afterRET DIR32 local labels
plus 522 native nonfield DATA B**. Every preceding and
following tested state retains zero original mnemonic,
width and GPR-role errors with its real PE targets.

| Complete original-shaped PARTIAL father | F1014 old | F1016 genuine |
| --- | ---: | ---: |
| Generated partial CODE B | 72,739 | **74,630** |
| Generated partial x86 | 19,950 | **20,496** |
| Source real 2DB B/x86 | 15/2 marker | **1,894/548** |
| Wrong native 2DB mnemonic/width/GPR | n/a | **0/0/0** |
| Original real 2DB PE fields | marker | **38/38** |
| Surrounding native C++ GPR phase | previously aligned | **unchanged** |
| Partial source compiler frame | 0x584 | **0x5C0** |
| Entire original 82KB callable exact | NO | **NO** |

Matching every local original instruction is still not
entire native GAME CODE equality. Original EBP slots,
true 0x720 frame and other missing cases remain different.

Reproduce only the two affected entire PARTIAL parent builds:

    scripts/repo-python scripts/verify-third-fighter-ring2db-f1016.py

Original PE receipts, compiled C++/OBJ/PDB and serial VC7.1
logs are retained under ignored
.analysis/f1016-third-native-proof/
and .analysis/f1016-third-2db/.

**Zero new accepted exact whole original game callables/CODE B.
No corpus-wide 979-unit cold replay.**
