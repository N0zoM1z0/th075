# F1012 — Original native 303 x87 arc, and preceding 302 shared-tail recovery

The pinned Japanese TH075 v1.11 executable has a complete
004AC040 game fighter of **82,796 original CODE B /22,721 x86**
plus 1,126 separately owned afterRET jump-table DATA bytes.
The tracked [original-shaped normal VC7.1 C++](../probes/FighterWhole004AC040F1012.cpp)
is still a PARTIAL parent, not whole-original exact; the original
receiver EBP−0x64, 0x720 frame and other game actions remain different.

Original action 303 physical **004BFDAB..004C01A1** contains
**1,014 CODE B/267 x86/29 genuine typed PE external fields**.
At stage0/frame0 it resets shorts F00/F02/F04, then draws a random
[0,100] and chooses signed F06=+5 or −5. Native landing and
vertical-motion guards use the separate true global floats
0065782C and 0065747C. At stage7/8 frame0, F00 increments,
bounded by signed original mode global006714D0×5+10, and
native action 00453D40(0) prepares original short velocity
quantization from the float members +0x50/+0x54 and
global00657888 via two genuine x87 FLD/FMUL and __ftol2
conversions. It sets shot angle from F04, speed10,
invokes two-float member0040FB70, fires original 0x388
with facing-scaled X velocity and Y+original global006591EC,
then restores velocities from signed F02/F08 and
float global00658044. The actual short F04 adds F06.

Stage7/frame0 uses the native cdecl x87 two-float
**00483300** mathematical helper, independent actual
opponent/actor X and Y fields and real PE globals
00657888/006591EC; its return is divided by native00657828,
passed through __ftol2 and saved into signed short F04.
Animation completion sets native action0 and mode-adjusted
random short+0x516; stage6 sets vertical speed6.5 and
drag0.25; stage9/frame0 bounds auxiliary action7 by F00<25.

## Actual native compiler grammar recovery

Eight independent full-PARTIAL-parent C++ grammar pilots and
four combined probes are retained under ignored
.analysis/f1012-third-303/grammar/ and /combined/.
Actual native member float access F32(0x54) repairs the
otherwise reversed FLD global/FMUL member into original
FLD member/FMUL global, including correct physical PE field
offset. The previously independently native-verifiable F752
borrowed actor/opponent X view repairs the original MOV-before-FLD
evaluation order. The genuine C++ signed short F04+=F06
recovers the original register allocation phase. Combining
these three real game semantics produces **267 native ordered
mnemonic and GPR operand roles**, **29 actual zero-addend
PE targets** and all x86 widths except the last source
shared-tail JMP (5B native near versus 2B partial short).

**Cross-case recovery:** adding real action303 automatically
changes the preceding genuine action302 shared-tail JMP from
partial short to original 5-byte near. Native302 now
emits all original **1,033 B/279 x86 with ZERO wrong
mnemonic, width and GPR roles**, plus its 25 real PE fields,
without editing 302 source.

The bounded
[original PE verifier](../scripts/verify-third-fighter-angle303-f1012.py)
freshly compiles TWO ENTIRE normal VC7.1 original-shaped
PARTIAL father sources, F1011 old marker versus F1012
real303; verifies all original 29 external destinations,
all preceding original 2C0–2C3/2E5/2E6/2F9–302 cases,
all **151 actual afterRET DIR32 local labels** and
**522 native nonfield DATA bytes**.

| Entire original-shaped PARTIAL fighter | F1011 old | F1012 genuine |
| --- | ---: | ---: |
| Generated partial CODE B | 71,250 | **72,252** |
| Generated partial x86 | 19,538 | **19,803** |
| Native303 source CODE B/x86 | 12/2 marker | **1,011/267** |
| Wrong original303 mnemonic/GPR | n/a | **0/0** |
| Wrong original303 width | n/a | **1, final shared JMP** |
| Original303 real PE targets | marker | **29/29** |
| Previous302 wrong native width/GPR | 1/0 | **0/0** |
| Partial father stack frame | 0x56C | **0x584** |
| Whole original 82KB callable exact | NO | **NO** |

The source is still a nonexact PARTIAL game giant. It
cannot earn accepted complete original callable CODE B.
Reproduce only the two affected partial fathers:

    scripts/repo-python scripts/verify-third-fighter-angle303-f1012.py

Native PE evidence and VC7.1 C++/OBJ/PDB/logs remain
under ignored .analysis/f1012-third-native-proof/ and
.analysis/f1012-third-303/. No all-979-unit cold replay.
