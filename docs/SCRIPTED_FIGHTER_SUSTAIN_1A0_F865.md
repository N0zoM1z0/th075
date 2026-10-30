# F865 — Original 1A0 float lvalue fixes physical PE field positions

The pinned Japanese TH075 v1.11 fighter at
005214B0 has 46,755 original callable CODE B
and five afterRET packed switch tables totaling
901 separate DATA B. The real 1A0 state at
00527AD3..00527BBD is **235 complete native
inner B/67 x86/five genuine PE fields**.

At stage0/frame0 its C++ scales native POS+0x50
and POS54+0x54 by actual global00658348.
The original physical x87 instructions must
be FLD this+0x54 (3B), then FMUL global
00658348 (6B). Bare C++ POS54*global
reverses those x87 operands and emits
6B FLD global, 3B FMUL member, moving
the original second DIR32 global field
from offset70 to 67. This is a dangerous
false positive if physical PE fields are
not independently checked.

A meaningful source lvalue expression
(*(&POS54))*global instead reproduces
all original x87 instruction sizes and
all five actual original PE field positions
[52,70,94,169,193], kinds, zero addends,
source symbols and real native target
addresses. Thirteen natural whole-parent
VC7.1 source expression experiments test
these width/order controls and actual
ground, speed/reset and stage behavior.

The selected source also checks original
POS48+POS54 against ground0065782C,
zeros real POS/POS54/POS48 in native order,
damps vertical speed for stage>3 and
handles state9 and stage4 state flag1.
It compiles to the entire **235B/67-x86
native mnemonic/width/offset grammar**,
but still has **49 real source GPR
operand byte differences and two
enclosing-giant original final JMP
operand negatives** at offsets231/232.

One affected complete VC7.1 parent
now generates **27,061 callable CODE B/
7,515 x86** (F863 26,841/7,450).
The verifier also rechecks all 36
preceding original C8..19E case interiors
and true physically typed original
PE fields, all five 901B afterRET
packed tables, and the genuine common
46B getter (still four real GPR
nonrelocation byte differences
at 10/12/16/19, with three PE calls).

Reproduce only the affected giant:

    scripts/repo-python scripts/verify-scripted-fighter-sustain-1a0-f865.py

Complete generated parent, VC7.1 COFF/PDB,
normal and false x87 controls and strict
native PE receipts are in ignored
.analysis/f865-scripted-stage1a0/.
Whole original 46,755B fighter remains
NONEXACT. No inner case, getter
or switch DATA earns callable whole-game
exact CODE credit. No mass cold replay.
