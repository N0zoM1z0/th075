# F884 — Entire original 803B native 2BC: DOUBLE gravity, staged flight and two x87 projectile methods

The SHA-pinned Japanese TH075 v1.11 original
fighter at 005214B0 owns 46,755 native
callable CODE B and five separate packed
afterRET switch DATA tables of 901B.
Physical game state **2BC at 00529814..00529B36**
is **803 complete native inner CODE B /
228 x86 /22 genuine physically typed PE fields**.
It is NOT an independent callable function.

The complete normal C++ source restores
these genuinely original native operations:

- Stage0/frame0 sets short+0xF00=0, dword+0x7C=0
  and short+0x80=1, then calls ResetAt453E20.
- For stage >8 the original loads float actor
  height+0x50 but subtracts a **DOUBLE qword**
  real global00657D00, then compares to
  real float ground0065782C and clamps to zero.
  The 64-bit original field width is verified,
  not silently treated as a float.
- Stage7 updates float+0x1C by global00658348
  and float+0x20 by minus global006598B8;
  stage9 reverses both adjustments.
- An original one-shot SHORT+0xF00==0 and
  dword+0x7C nonzero test increments the
  genuine 16-bit counter. If +0x7C==1, it
  prepares native action0xD and emits sprite
  0x346 through native 00453B50, using
  real integer X, float Y with original
  global00657888, narrow facing, and
  the original THREE trailing integer
  arguments (the full source call contains
  seven user arguments).
- After original GetNativeActionAt40FA30/
  SetNativeActionAt40FAC0, stage5/frame0
  animates 0x28 through 00453E80,
  updates actor float+0x36C via native
  00657888, prepares action0x17 and
  fires sprite0x73 via 00453C80.
  Its X expression must use the genuinely
  observed borrowed actor X member,
  producing native FILD EBP-0xBC then
  **FSUBR member+0x44**, rather than
  nonnative FISUB.
- At stage7/frame0 it prepares action0xA,
  sets actual 0040FBB0 motion with two
  **float** values -200.0f,60.0f and
  integer0, sets float+0x1C/+0x20=1 and
  four true original signed-byte flags
  +0x11..+0x14 to -1.
- Stage10/frame0 resets both those
  observed floats to 1. At stage8/
  frame0 it sets motion 100.0f,60.0f,0,
  float+0x1C=3, float+0x20=0.05 and
  height+0x50=20; starts actual native
  animation0046D000(0x1F4), then fires
  sprite0x80 through 00453C80 with
  genuinely mixed float X (facing*150
  FILD EBP-0xC0 plus actor X), raw integer
  Y+0x48, and narrow char facing.

One freshly compiled selected full VC7.1
C++ parent emits **34,775 callable CODE B/
9,794 x86** (F883 33,987/9,568).
The complete 2BC source reproduces
all 228 original instruction mnemonics,
sizes and relative positions and all
22 actual physical original PE field
offsets [60,84,102,143,161,191,209,
281,306,330,338,362,395,410,429,450,
496,529,549,687,730,794], including
native DIR32/REL32 types, zero source
addends, C++ callee/global symbols and
physically resolved original targets.

## Independently compiled full-function negative controls

The verifier builds a WRONG but same-length
full-parent source where stage5 bare
actorX-float(facing*64) emits nonnative
FISUB instead of original FILD/FSUBR.
The 803B/228x86 aggregate length does
NOT make that source equal.

The verifier also compiles a WRONG
dword-style once-only counter assignment,
which produces MOVSX and a complete
**802B** case rather than the native 803B,
even though both versions have 228 x86.
Neither false source is credited or
compared through a cropped matching range.

The current original case still differs
at **142 authentic unmasked GPR operand
bytes** and two original enclosing-whole-
fighter final JMP bytes +799/+800.
Thus 2BC is fully reconstructed at
native source grammar/PE topology level
but is NOT complete whole-fighter
byte-exact callable CODE.

The newly compiled whole father also
physically rechecks 59 preceding actual
native source-backed game case interiors,
including 1FD original one-byte CMP,
252/254 true PE field shifts, and
corrected 259 physical boundary
(at 2BC, not numeric25A).
All five original 901B afterRET packed
tables and the 46B common getter's
four real GPR byte negatives and three
true original PE calls are verified.

Targeted original-PE rerun ONLY for
this affected whole giant:

    scripts/repo-python scripts/verify-scripted-fighter-stage2bc-f884.py

Complete current VC7.1 C++, OBJ/PDB,
source error controls and pinned PE
receipts remain in ignored
.analysis/f884-scripted-stage2bc/.
The full original 46,755B giant remains
NONEXACT, zero new accepted whole
callable CODE and no mass cold replay.
