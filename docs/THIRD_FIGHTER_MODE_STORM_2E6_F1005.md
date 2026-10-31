# F1005 — Native original mode-dependent 2E6 storm, 590 GPR roles aligned

The pinned Japanese TH075 v1.11 original fighter at 004AC040
contains **82,796 original callable CODE B /22,721 x86** and
1,126 separately owned afterRET switch DATA bytes.
[Tracked normal VC7.1 partial C++](../probes/FighterWhole004AC040F1005.cpp)
does not yet reconstruct the original 0x720 frame,
saved actor pointer at EBP−0x64, or the whole function's
absolute PE/COFF positions. The entire fighter is NONEXACT.

Original game action2E6 has the real physical interval
**004BD314..004BDB1E**, **2,058 original CODE B/590 x86**
and **47 genuine typed zero-addend PE call/global targets**.
It is NOT one homogeneous attack. Original stage0 resets
motion, 0x7C/3AC, signed shorts F00/F02/F04, sets F06=30,
F08=1 and drag=0.15f. Stage6/7 fades the original
unsigned opacity byte +0x11 by 30, with auxiliary action8
when zero. Stage8/frame0 uses two genuine random draws
to create X velocity and Y velocity, then compares original
actor X+0x44 with opponent X+0x44 to select signed facing.
Stage9 increases opacity by30, bounded by 255.
Stage14..18 handles actual ground collision, resets motion
and enters auxiliary action19. Stage2..7 emits a true
randomized seven-parameter sprite0x33E.

At stage11..16 with F02=0, original source increments F02
and selects a genuine separate 32-bit ten-plus loop by
**signed global mode at 006714D0**:

| Real original mode | Original number of 0x387 shots | Angle step |
| --- | ---: | ---: |
| 0 | **12** | **30°** |
| 1 | **20** | **18°** |
| 2 | **30** | **12°** |
| 3 | **40** | **9°** |

Each loop writes float +0x314 from signed shot index
multiplied by the real step, then calls original
00453A70(0x387), with native signed facing×16 FILD,
FSUBR world-X +0x44, float Y + native PE global
**0065836C**, signed facing and layer1. Four independent
C++ loops preserve native x86 backedges; no manually
copied machine loops or fake locals were introduced.

Animation completion uses 0040FA30/0040FAC0(0),
random [60,120] minus signed mode×20 to short+0x516.
At stage6/frame0, prepares action2 and independently
launches **six seven-argument 0x338..0x33D** sprites
with original signed facing×7 FILD/FSUBR world-X and
physical Y global **00659490**. Then native 0040FBB0
sets motion and opacity255. Stage8/frame0 has bounded
auxiliary6; stage9 zeroes X/Y velocity, stage11 prepares
action5, stage17 bounded auxiliary15, stage19 auxiliary17.

## Original comparator grammar breakthrough

The first natural
[C++ source](../probes/FighterThirdBossModeStorm2E6F1005.inc)
used a raw opponent float pointer in stage8. VC7.1 emitted
two FLD instructions and FCOMPP, unlike the native
**FLD actor+0x44 / FCOMP opponent+0x44**.
Reusing the independently original-verified
F752 borrowed actor/opponent X views recovered precisely
the native FLD/FCOMP memory layout, all native mnemonic
positions and all **590 native GPR operand roles**.

The [native PE verifier](../scripts/verify-third-fighter-mode-storm2e6-f1005.py)
freshly compiles TWO ENTIRE original-shaped PARTIAL normal VC7.1
fathers, F1004 marker versus F1005 real source.
It checks all 590 original native mnemonic/GPR roles,
all **47 native zero-addend typed PE targets**, prior
2E5 and 2C0..2C3 with all 754 earlier x86 GPR roles,
all **151 native afterRET DIR32 local case labels** and
**522 exact nonfield DATA B**.

| Complete original-shaped PARTIAL father | F1004 previous | F1005 selected |
| --- | ---: | ---: |
| Source partial CODE B | 64,810 | **66,877** |
| Source x86 | 17,756 | **18,344** |
| Real 2E6 source B/x86 | 12/2 marker | **2,055/590** |
| Original physical 2E6 B/x86 | 2,058/590 | **2,058/590** |
| Wrong native mnemonic/GPR positions | unaligned | **0/0** |
| Native wrong instruction widths | n/a | **one: shared-tail JMP** |
| True original external PE fields | marker | **47/47** |
| Partial parent frame | 0x47C | **0x4D8** |
| Original whole fighter exact | NO | **NO** |

The single native width difference is **case-local final
ordinal589**: original native shared-parent-tail JMP to
004C03A7 is 5-byte near, while incomplete source parent
generates a 2-byte short JMP. It must NOT be misreported
as a real matched byte, nor the inner game state accepted
as an independent full callable. Other original stack
displacements, whole-parent branches and COFF physical sites
also remain wrong.

Reproduce only the two affected whole-partial fathers:

    scripts/repo-python scripts/verify-third-fighter-mode-storm2e6-f1005.py

Pinned original PE receipt and generated C++/OBJ/PDB, serial
VC7.1 logs reside under ignored
.analysis/f1005-third-native-proof/ and
.analysis/f1005-third-2e6/.

**New exact original complete callable CODE B: zero.
No all-979-unit cold replay.**
