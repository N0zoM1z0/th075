# F853 — Original 18A float Y lvalue recovers native x87 widths

The SHA-pinned Japanese TH075 1.11 fighter at 005214B0
contains 46,755 callable native CODE B, plus five
afterRET packed switch tables totaling 901 separate DATA B.
The actual original 18A handler is **250 B/71 x86/
six typed original PE fields**.

Its actual stage-zero position15f and short timer reset,
gravity00658058, stage5 projectile kind327,
signed facing*151 X coordinate converted by FILD,
and original Y/global float calculation are natural C++.
The original native Y operand is first FLD this+0x48
(3-byte x86), then FADD global0065929C (6-byte x86).
Ordinary bare POS48+global instead emitted reversed
FLD global/FADD member widths. A genuine lvalue
expression, **(*(&POS48))+g_F853OffsetYAt0065929C**,
naturally reproduces BOTH original instruction widths
and source field offsets. Seven real full-parent
source expression controls were compared.

The tracked verifier regenerates/validates the F852
parent and compiles ONE entire affected normal VC7.1
fighter. Current source emits **24,797 callable
CODE B /6,828 x86**, from 24,562B/6,759.
All 71 current source opcode/size and original
six physical PE call/global destinations, field
types, offsets and zero addends now match.

This remains NONEXACT source: **45 genuine source
GPR operand byte differences** are present and
two actual original whole-function epilogue JMP
bytes at case offsets +246/+247 differ.
These are not masked or accepted as exact CODE.
The new COFF independently re-verifies five
previous 136/186/187/188/189 states and twenty
other complete source-backed native C8..135
case extents/PE fields, retaining honest nonfield
register negatives. All five original packed 901B
afterRET tables are checked.

The shared 46B original default getter retains
its true saved-this location and three native
REL32 call targets, but the current parent
has four actual nonrelocation GPR operand
byte negatives +10/+12/+16/+19.

Reproduce only this affected original giant:

    scripts/repo-python scripts/verify-scripted-fighter-floatshot-18a-f853.py

Generated C++, VC7.1 COFF/PDB, expression controls
and original physical evidence are retained
in ignored .analysis/f853-scripted-float-shot18a/.
Entire original giant 46,755B NONEXACT; zero
independent case/suffix exact callable CODE.
No accepted-unit mass cold replay.
