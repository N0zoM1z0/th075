# F859 — Real 297B grounded 194 exposes a false inherited Reset call

The pinned original Japanese TH075 v1.11 fighter at
005214B0 owns 46,755 callable CODE B plus 901
separately owned packed afterRET switch DATA B.
Original state 0x194 at 005275FA..00527722
has **297 complete interior original CODE B/86 x86/
7 genuine physically typed PE call/global fields**.

The initial F859 source was based on true sibling
0x192 and retained its stage0 ResetAt453E20() call.
**That was wrong for this actor's actual 0x194.**
The inherited call emitted an incorrect
**298B/88-x86/8-COFF-field** state rather than
the original 297B/86-x86/7-PE-field case.
Deleting that *incorrect behavior*, not adding
synthetic padding, restores the native original
full function interior geometry.

The actual normal C++ now handles stage-zero
counter setup, true POS54=POS54-POS5C
drag, x87 **POS48+POS54 <= ground** native
threshold0065782C, real early action0xA
and actual position/drag/velocity clear
order, then original getter and state9.
At stage5 it stores original float
**2.0f** to this+0x314, emits sprite0x320
through native 00453A70, starts animation
0xFA, prepares action0 and sets +0x7C
at stage6.

Five source expressions were tested in the
complete affected VC7.1 giant parent:
the invalid inherited Reset, correct
native source, reversed float operand
order, strict rather than inclusive ground
threshold, different ground clear order and
incorrect float member value. The selected
**297B/86-x86** source matches every
native opcode, instruction width, relative
position and all seven physical original
PE field offsets/types/zero addends/targets.
The other candidates have genuinely
different native bytes or an incorrect
whole original case extent.

The new parent is freshly regenerated
from F858 and emits **25,972 callable
CODE B/7,184 x86** (F858 25,690B/
7,100 x86). Its original 194 case
still contains **55 real source GPR
operand byte differences** and two
whole original fighter epilogue JMPs
(four non-PE relative operand bytes,
at +128/+129 and +293/+294).
No register/parent-JMP mismatch is
masked or declared original whole exact.

In the same compiled whole COFF, F859
physically rechecks ten earlier GPR-
affected cases 136/186-192 and
twenty prior C8-D2/12C-135 cases,
all original PE fields and real
nonfield byte negatives. All five
packed afterRET switch tables
(901 separate DATA B) are verified.
The common 46B default/getter
continues to differ at four true
GPR operand bytes +10/+12/+16/+19
while its three real PE calls
remain correctly targeted.

Reproduce ONLY the selected giant:

    scripts/repo-python scripts/verify-scripted-fighter-ground-194-f859.py

Generated full C++, pinned VC7.1
COFF/PDB, source alternatives and
physical original PE evidence are
stored in ignored
.analysis/f859-scripted-ground-194/.
Original 46,755B entire fighter
remains NONEXACT; no independent
case/whole callable CODE accepted.
No mass cold replay.
