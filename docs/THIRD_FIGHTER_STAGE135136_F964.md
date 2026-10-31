# F964 — Third original Fighter stages 135/136: real falling and projectile source, 23 PE targets

The pinned Japanese TH075 v1.11 original giant
fighter **004AC040** spans **82,796 callable
native game CODE B/22,721 x86**, with a separate
**1,126B afterRET jump DATA**. Its tracked
[cumulative normal VC7.1 C++ parent](../probes/FighterWhole004AC040F964.cpp)
is still PARTIAL, retains many original
game-state placeholders and does not
recover native saved-`this` at EBP−0x64
or the entire 0x720 original frame.
The complete original game fighter remains
NONEXACT.

Two more original real game handlers have
now been reconstructed into ordinary C++:

| Real original case | Original PE physical interval | Entire native interior | Original external PE targets |
| --- | --- | ---: | ---: |
| **135** | **004B18B1..004B1A98** | **487B/137 x86** | **12** |
| **136** | **004B1A98..004B1C5B** | **451B/134 x86** | **11** |
| Both real cases | contiguous | **938B/271 x86** | **23** |

The new [F964 normal C++](../probes/FighterThirdBossStage135136F964.inc)
preserves the actual actor-specific original
stage motion, real original typed fields,
true game calls, signed facing and sprite
arguments, without fictitious locals,
assembly or native-byte grafts.

Original **135** starts with the real
stage0/frame0 positive fall-flag reset;
when the signed flag is positive it
subtracts actual global float **00658058**
from horizontal position and clamps against
original zero **0065782C**. At actual
stage 3 or 4 it subtracts original
animation delta **0065747C** from vertical
velocity, tests ground contact, resets
true Y, calls native ResetAt453E20 and
SetAuxActionAt40FB40(5), and fires genuine
sprite kind **0x80** via `00453C80`
with **signed facing×150 + raw X float**,
native Y and actual facing byte. For
stage greater than 4, it subtracts true
global **00658048** and clamps ground.
The original stage3/frame0 then sets
X=15.0f, Y-velocity=4.5f and clears
fall flag; stage5/frame0 sets X=4.0f.

Original **136** differs materially
from historical game-source guesses.
Its actual native x87 `FLD original
0065782C; FLD this+0x48; FUCOMPP;
FNSTSW AX; TEST AH,0x44; JP` is
an **equality condition**, not a
simple greater-than float test. F964
retested both natural C++ forms in a
whole original-shaped source. Using
the **real equality** at this branch
restores all original 134 ordered
x86 mnemonics and widths. The
original also performs a stage-12
landing/Reset/aux-action exit,
sets stage6 float X=4.0,
vertical velocity=9.5, drag=1,
fires actual seven-argument sprite
**0x337** through `00453B50`
at stage8, and resets +0x7C
at stage9.

## Actual normal VC7.1 and original PE evidence

The bounded
[`verify-third-fighter-stage135136-f964.py`](../scripts/verify-third-fighter-stage135136-f964.py)
fresh-compiles TWO complete original-shaped
partial fighter parents: tracked F963
with two 15B/two-x86 markers, and
tracked F964 with both actual cases.
Each is checked against the pinned
original Japanese executable's whole
callable function and real physical
case instruction extents, including all
**23 original typed zero-addend
source PE/COFF call/global targets**.

The true original 136→186 physical
successor at **004B1C5B** has **NO
independent afterRET DIR32 case
entry**. The source case136 boundary
is derived from its original **134
x86 instructions**, and its following
real 186 two-instruction source marker
before independently mapped 187
at **004B1D70**. The verifier never
invents a missing jump-table case
label, and rechecks all **151 real
DIR32 afterRET labels plus 522
native nonfield DATA bytes**.

| Complete partial source feature | Prior F963 | F964 |
| --- | ---: | ---: |
| Generated whole partial CODE B | 23,664 | **24,566** |
| Whole emitted source x86 | 6,479 | **6,746** |
| Source native case135 B/x86 | 15/2 | **481/137** |
| Source native case136 B/x86 | 15/2 | **451/134** |
| Original 135 mnemonic errors | n/a | **0** |
| Original 135 width errors | n/a | **2** |
| Original 135 wrong GPR-role instructions | n/a | **89** |
| Original 136 mnemonic/width errors | n/a | **0/0** |
| Original 136 wrong GPR-role instructions | n/a | **84** |
| Genuine PE external targets | markers | **12+11** |
| Real afterRET DIR32/nonfield DATA | 151/522 | **151/522** |
| Whole 82KB original game exact | NO | **NO** |

The native 135's two genuine wide
integer→x87 stack accesses at local
ordinals **75/76** use physically
original **EBP−0xA4**, each six
bytes. The partial father compiler
uses a shallow short-EBP temporary,
producing two 3-byte instructions
and leaving **6 actual native CODE
bytes missing**. Its 89 wrong
GPR roles and 136's 84 wrong
GPR roles remain separately
accounted for; neither is masked by
the external PE relocations.
The genuine parent frame and entire
source control-flow/owner lifetime
remain the next higher-leverage
work, not artificial stack padding.

Reproduce only these two original-
shaped whole partial father builds:

    scripts/repo-python scripts/verify-third-fighter-stage135136-f964.py

All complete C++ source/OBJ/PDB,
original PE-backed x86 and target
receipts, plus genuine earlier
equality/inequality compiler trial,
are retained under ignored
`.analysis/f964-third-native-stage-proof/`
and `.analysis/f964-third-135-136/`.

**Zero newly accepted whole original
callable game functions or CODE bytes;
no all-979-unit cold replay.**
