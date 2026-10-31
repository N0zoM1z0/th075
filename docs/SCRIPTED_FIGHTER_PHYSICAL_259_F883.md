# F883 — Correct original 259 physical extent: next real handler is 2BC, not numeric 25A

The pinned Japanese TH075 v1.11 fighter at 005214B0
has **46,755 original callable CODE B** and five
packed original afterRET switch DATA tables (901B).

The original afterRET action map is SPARSE.
A naive range based on the next numeric action would
incorrectly treat state259 as starting at 00529746 and
ending at 0052CB25, for a purported **13,279 CODE B**,
because numeric action25A points to the common DEFAULT
getter at 0052CB25. But original action2BC has the
actual physical handler at 00529814. Therefore the
NEXT PHYSICAL native action start after 259 is 2BC,
not 25A. The real contiguous original action259
interior is exactly **00529746..00529813**:
**206 complete CODE B/60 x86/six physical PE calls**.

Real action259 resets the actor at stage0/frame0,
sets +0x80=1, +0x7C=1, clears FLAG and handles
native animation completion by setting action0.
At stage2/frame0 it emits sprite0x34D through
real 00453A70 with mixed coordinates:
float X from signed facing byte *80, converted
through true x87 FILD EBP-0xB8 and added to
actor X+44, but native raw integer Y+48.
It then calls original 0046D000(0x1F4) and
PrepareActionAt453D40(5), followed by the
ONE real enclosing-giant epilogue JMP.

Normal VC7.1 source produces the entire original
**206B/60-x86** opcode/width/offset geometry and
all six genuine original PE REL32 call fields
at case offsets [26,66,90,174,187,197],
including real original native targets and
zero addends. Source controls independently
test the sprite kind, animation argument
and x87 floating evaluation order; incorrect
controls introduce genuine original mismatches.

One new entire VC7.1 affected parent emits
**33,987 callable CODE B/9,568 x86**,
from F881 33,796/9,510. The same compiled
parent physically rechecks 58 previous
original case interiors, including real
1FD one-byte CMP GPR phase negative and
252/254 physical PE field offset shifts,
all five original packed 901B afterRET
DATA tables, and the common 46B getter
with four true GPR operand errors.

Although the 259 original handler source
has all actual x86 opcode/width and six PE
field positions correct, it still differs
at **34 nonrelocation register operand bytes**
and two authentic original full-fighter
epilogue JMP operand bytes at +202/+203.
No inner state is an independent whole
callable exact game function.
Original enclosing 46,755B giant remains NONEXACT.

Reproduce ONLY this affected original giant:

    scripts/repo-python scripts/verify-scripted-fighter-physical259-f883.py

Normal C++, VC7.1 COFF/PDB, full-source
controls and physical Japanese original PE
receipts remain in ignored
.analysis/f883-scripted-stage259/.
No mass cold replay.
