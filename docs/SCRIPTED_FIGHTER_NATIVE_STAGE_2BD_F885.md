# F885 — Complete native 855B 2BD: distinct owner early exit and two x87 stages

The SHA-pinned original Japanese TH075 v1.11 fighter at
005214B0 owns 46,755 callable original CODE B
plus five separately owned 901B afterRET packed
switch DATA tables. Genuine action2BD is
00529B37..00529E8D, **855 full original inner
CODE B /239 x86/24 original physically typed PE fields**.

This action is NOT just renamed 2BC. Both use the genuine
double qword gravity global00657D00, stage7/9 inverse
float motion and once-only 16-bit ++F00 logic.
But the actual native 2BD state has substantive differences:

- Inside the one-shot +7C==1 path, it fires genuine
  sprite346 via 00453B50 BEFORE PrepareActionD,
  then sets action2C2 via native0040FAC0, calls
  ResetAt453E20, copies observed associated owner
  +0x2E8 -> float/int X+0x44 into current actor X,
  and **jumps directly to the enclosing whole fighter
  epilogue** at native x86 ordinal106.
- At stage5 it invokes AnimatePush(0x28), calls
  PrepareAction(0x17) BEFORE subtracting
  original 00657888 from float+0x36C, then fires
  sprite0x74 (2BC uses 0x73) through 00453C80.
  The actual x87 signed facing*64 scratch slot
  is **EBP-0xC4** and the native uses
  FILD followed by FSUBR of observed actor X.
- Stage7 PrepareAction is 0xB rather than 0xA,
  and original stage8 height is 30.0f rather
  than 20.0f, while float,float,int motion
  calls remain at genuine 0040FBB0.
- Stage8 sprite0x80 is emitted with mixed float
  X signed facing*150 + actorX and raw integer Y.
  Its native FILD scratch is **EBP-0xC8**.
  Its last instruction, ordinal238, is a SECOND
  direct whole-fighter epilogue jump.

The selected normal VC7.1 full-parent C++ emits
**35,615 callable CODE B/10,031 x86**, up
from F884 34,775B/9,794 x86. The entire 2BD
source matches all 239 original instruction
mnemonics, sizes and relative instruction
positions and ALL **24 original PE field
offsets/types/source callees/zero addends/actual
original destination addresses**, including the
original qword gravity and both independent
real x87 integer scratch slots.

Four additional complete VC7.1 negative sources
test the two different native call orders,
sprite74 rather than sprite73 and meaningful
owner-X assignment expressions. Incorrect 2BC
orderings keep 855B/239 x86/24 PE field counts
but change actual original instruction order
and are NOT source-proven.

The selected 2BD still has **149 true
unmasked register operand bytes and four
enclosing-original-giant JMP operand bytes**
at offsets +382/+383 and +851/+852 different.
This is NOT original exact whole callable CODE.

The current full COFF physically rechecks
all **60 preceding original PE-backed game
cases** (including 2BC's full 803B,
corrected 259 physical bound, 252/254
one-byte PE shifts and 1FD CMP error),
all original five 901B packed switch tables,
and the native common 46B getter with
four genuine GPR negatives and three true
physical PE calls.

Reproduce only this affected giant:

    scripts/repo-python scripts/verify-scripted-fighter-stage2bd-f885.py

Full generated normal VC7.1 C++, COFF/PDB,
source variants and strict pinned-original
PE JSON evidence remain under ignored
.analysis/f885-scripted-stage2bd/.
The original 46,755B whole function is
NONEXACT, zero newly accepted authored
callable CODE and no mass cold replay.
