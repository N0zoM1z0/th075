# F961 — Third fighter 12F and 130, five consecutive native stage handlers

Pinned Japanese TH075 v1.11 original whole fighter
**004AC040** spans 82,796 complete original callable
CODE bytes/22,721 x86 plus 1,126 separately owned
afterRET jump-table DATA B. Its growing natural
[tracked cumulative VC7.1 C++ parent](../probes/FighterWhole004AC040F961.cpp)
remains PARTIAL and NONEXACT. The saved original
receiver EBP−0x64 and original full 0x720 frame
are not yet reconstructed.

Two further REAL game-state interiors had remained
15-B/two-instruction placeholders:

| True original state | Native original executable interval | Entire original CODE | Genuine PE fields |
| --- | --- | ---: | ---: |
| **12F** | **004B12F1..004B13C0** | **207 B /59 x86** | **6** |
| **130** | **004B13C0..004B14C9** | **265 B /81 x86** | **6** |

Native **12F** is NOT the historical F654 different
fighter's much longer late-fall dual-drag behavior.
The physical original 004AC040 uses the authentic
stage0/frame0 initialization (fall flag, actual
+0x80 short and +0x7C int), original signed
positive-fall position decrement using real
float 00658058, ground threshold 0065782C,
frame completion native getter/setter calls,
and **stage4/frame0** prepares game action **0x1C**.

Native **130** starts by subtracting the actual
vertical drag from motion, tests the genuine
ground collision, and invokes action **0xA**,
zeroing real position/velocity on landing.
Otherwise stage0/frame0 sets the original
+0x80/+0x7C values; completion triggers
original action **9**. At **stage3/frame0**
the original calls PrepareActionAt453D60(**0x1C**)
and then real **seven-argument projectile
00453B50** kind **0x334** with actual
raw X/Y and signed facing and trailing
1,0,1 arguments. This differs materially
from old F654's other fighter 0x130
five-argument sprite 0x339 hypothesis.

The new natural
[`FighterThirdBossStage12F130F961.inc`](../probes/FighterThirdBossStage12F130F961.inc)
expresses these game operations as ordinary
C++ inside the real whole-parent source.
No original byte patches, artificial register
storage, ASM or inert stack-padding locals.

## Real whole-parent original-PE verification

The tracked bounded
[`verify-third-fighter-stage12f130-f961.py`](../scripts/verify-third-fighter-stage12f130-f961.py)
serially cold-compiles TWO ENTIRE normal
VC7.1 partial original-shaped whole fighter
sources (tracked F959 and selected F961)
and independently checks native original
12C,12D,12E,12F,130 physical case
boundaries, all **342 complete original
positional x86**, real zero-addend
typed source PE call/global targets and
original 151 afterRET DIR32 local labels
with 522 native nonfield DATA bytes.

The genuine **12C missing original
afterRET table label** remains handled via
the actual previous D2 251B/74x86 terminus;
the real 12D table label supplies the next
boundary. No fake table entry or cropped
case is introduced.

| Whole partial selected source | F959 prior | F961 selected |
| --- | ---: | ---: |
| Emitted cumulative C++ CODE B | 22,267 | **22,709** |
| Source whole x86 | 6,055 | **6,191** |
| Native 12F source B/x86 | 15/2 | **207/59** |
| Native 130 source B/x86 | 15/2 | **265/81** |
| 12F/130 wrong native mnemonics, widths, GPR roles | Unaligned | **0/0/0** |
| Original 12F+130 external typed PE targets | Stub | **12/12** |
| Native 12C–130 contiguous original CODE/x86 | existing 696/202 | **1,168/342** |
| All five original case PE fields verified | 19 | **31/31** |
| Original afterRET real DIR32/nonfield DATA | 151/522 | **151/522** |
| Entire 82KB original native fighter exact | NO | **NO** |

The **1,168B/342-x86 natural compiler source
geometry** and PE target backing is meaningful
reconstruction of five real original internal
handlers, NOT newly accepted whole callable
native original CODE. More game states remain
unimplemented, and the full fighter's physical
stack/register/relocation layout still differs.

Reproduce the bounded two-whole-partial-father
VC7.1/PE-backed test:

    scripts/repo-python scripts/verify-third-fighter-stage12f130-f961.py

Compiler C++/OBJ/PDB, VC7.1 command receipts and
original PE target confirmations remain locally
in ignored `.analysis/f961-original-stage-proof/`
and the earlier full-source experimental controls
at `.analysis/f961-third-stage12f/`.

**Zero new exact whole original game functions
or credited original CODE bytes; no full
979-unit cold replay.**
