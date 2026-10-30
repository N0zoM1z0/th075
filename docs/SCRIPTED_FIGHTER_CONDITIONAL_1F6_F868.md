# F868 — Original 1F6 special stage switch and mixed-coordinate projectile

The SHA-pinned Japanese TH075 v1.11 fighter at
005214B0 owns 46,755 native callable CODE B,
with five separately owned packed afterRET
switch tables occupying 901 DATA B.
The actual original 0x1F6 at
00527FF2..00528165 is **372 complete
native interior CODE B/111 x86/12 actual
physical PE call/global fields**.

Natural C++ reconstructs the real original
stage-zero ResetAt453E20, motion flags,
x87 height damping via global00657478
and threshold0065782C, then the unique
original three-condition special guard:
the stage must be **greater than 7 and
less than 11**, and unsigned byte
this+0x511 must equal **0x14**.
If true, the actor sets action0x1F7,
resets motion and calls the native
game-effect method at **00455B30**,
then returns directly to the enclosing
complete fighter epilogue.
All three condition branches must
target the same original post-event
instruction boundary.

The ordinary fall-through checks
native action0, then at stage5/frame0
sets POS=14.0f. It fires sprite0x80
through original 00453C80 with
real **float X = signed facing*100
converted by FILD and added to
this+0x44**, but a raw 32-bit
Y coordinate from this+0x48.
This mixed float-X/raw-Y C++
method parameter arrangement emits
the original native push/FILD
instruction sequence, with an
8-bit-facing fourth parameter.
The state then emits a separate
integer-coordinate sprite0x336
through original 00453A70 and
prepares action2 via 00453D40.

Five full affected-parent VC7.1
source alternatives tested the
true signed stage bound, unsigned
U8 byte511 condition, float X
evaluation order and projectile
kind. Incorrect variants may
retain equal source size but
produce genuine wrong original
Jcc operands or x87 widths.

The selected source reproduces
**all 111 original x86 mnemonics,
instruction widths/positions and
12 physically typed real PE fields**,
at native original case offsets
[26,70,89,107,176,184,192,205,
229,317,353,363], including field
kinds, zero addends, source symbols
and actual native game destinations.

It is still NOT original whole-code
exact: **64 honest native GPR
operand bytes**, plus two original
enclosing-whole-fighter long-JMP
displacement pairs at offsets
+197/+198 and +368/+369,
remain different. These are never
relocation-masked as correct CODE.

The targeted verifier compiles
ONE newly affected full normal
VC7.1 fighter. Generated callable
source grows to **28,464 CODE B/
7,951 x86** (F867 previous
28,107B/7,842 x86). All
**39 preceding original native
case interiors**, including
the genuine guarded stage-zero
multipliers in 1A0, are rechecked
against their real PE fields
and remaining register negatives.
All five original 901B packed
afterRET tables are independently
reverified. The original
46B/16-x86 shared getter remains
**34/34 true native nonrelocation
bytes equal** and three correct
PE REL32 destinations.

Reproduce only this affected giant:

    scripts/repo-python scripts/verify-scripted-fighter-conditional-1f6-f868.py

Generated complete source, pinned
VC7.1 COFF/PDB, alternate source
controls and native PE receipts
remain in ignored
.analysis/f868-scripted-state1f6/.
The original 46,755B callable
fighter remains NONEXACT.
No inner case/getter or switch
DATA accepted as whole-game
exact CODE. No all-unit cold replay.
