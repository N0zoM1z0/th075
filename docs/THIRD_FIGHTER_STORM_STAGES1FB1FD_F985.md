# F985 — Native 1FB/1FC/1FD six-shot storm, 84 verified PE fields

The pinned original Japanese TH075 v1.11 004AC040 fighter is a
**82,796-byte complete callable game function**, containing 22,721
x86 instructions plus 1,126 separate afterRET jump DATA bytes.
The [tracked cumulative VC7.1 C++](../probes/FighterWhole004AC040F985.cpp)
remains a **partial**, NONEXACT original-shaped father. Original
0x720 frame, saved receiver EBP−0x64, GPR allocation and many other
cases are still absent or nonnative.

| Real original game state | Physical native original interval | Native CODE/x86 | Real PE fields |
| --- | --- | ---: | ---: |
| 1FB | 004B6824..004B6CCD | **1,193B /346** | **28** |
| 1FC | 004B6CCD..004B7175 | **1,192B /346** | **28** |
| 1FD | 004B7175..004B761E | **1,193B /346** | **28** |

These are **not** copies of preceding 1F8–1FA: they initialize
the real action-state int +0x7C=1 and signed stage/opacity, at
stage6/7 decrease +0x11 opacity by **20** without an incorrect
early auxiliary exit, and at actual signed stages **9 through 12**
subtract vertical drag, increase opacity by 20, and execute the
real ground collision Reset/auxiliary action **0xD**.
Their randomized sprite0x33E projectiles retain original
real X/Y and random call order. At stage6/frame0, they
prepare native action2, issue six genuine ordered
**0x338–0x33D** seven-argument sprite shots with actual
IMUL signed-facing×7, FILD integer and **FSUBR world X**,
then call original animation **0046D000(0xC8)**,
native SetMotionStateAt40FBB0 and set opacity 255.

After stage8 bounded counter auxiliary action6, these real
states write X=**+60/−60/+120** respectively, vertical
velocity 3.0f and drag 0.5f. Native stage13/frame0
invokes auxiliary action0xB.

The new [natural original game C++ source](../probes/FighterThirdBossStages1FB1FDF985.inc)
uses the independently recovered borrowed native X member at
+0x44 and the **PE-verified 00659490** shot-Y global,
rather than importing unrelated character constants or
inventing an entire historical fighter class.

The [fresh two-whole-partial-father verifier](../scripts/verify-third-fighter-storm1fb1fd-f985.py)
compiles F984 marker source and F985 real source under pinned
normal VC7.1, rereads the pinned original whole function and
case extents, and checks all **84 genuine zero-addend typed
i386 original PE/COFF external targets**, preceding 1FA,
all **151 original afterRET DIR32 case labels** and
**522 original nonfield DATA bytes**.

| Whole partial C++ property | F984 previous | F985 selected |
| --- | ---: | ---: |
| Compiled partial CODE B | 43,483 | **47,016** |
| Source x86 | 11,990 | **13,022** |
| 1FB real source B/x86 | 15/2 | **1,192/346** |
| 1FC real source B/x86 | 15/2 | **1,193/346** |
| 1FD real source B/x86 | 15/2 | **1,193/346** |
| Wrong native mnemonic ordinals | unaligned | **0 all three** |
| Wrong native width ordinals | unaligned | **1/1/0** |
| Original GPR role mismatches | unaligned | **180 each** |
| Original PE target fields | markers | **28+28+28** |
| Original afterRET DIR32/nonfield | 151/522 | **151/522** |
| Entire 82KB original callable exact | NO | **NO** |

The one width discrepancy in each 1FB and 1FC is real
native opacity **CMP EAX/ECX,235** register choice at
state-local ordinal54. Their overall code sizes differ
in the opposite direction by one byte; this must not
be mistaken for complete native byte agreement. The
actual EBP operand locations and 180 GPR roles per state
also remain nonnative.

Reproduce only affected complete original-shaped PARTIAL
father sources:

    scripts/repo-python scripts/verify-third-fighter-storm1fb1fd-f985.py

Compiler C++/OBJ/PDB, pinned original PE evidence and serial
build logs are saved in ignored .analysis/f985-third-original-proof/
and .analysis/f985-third-storm/. **No new accepted whole
original CODE/functions and no all-979-unit cold replay.**
