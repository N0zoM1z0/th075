# F866 — Original full 1F4 double projectile and genuine narrow facing parameter

The pinned Japanese TH075 1.11 original 005214B0 fighter
contains 46,755 callable native CODE B and five packed
afterRET switch tables totaling 901 separate DATA B.
Its genuine original 0x1F4 at 00527BBE..00527D7D
has **448 complete interior CODE B/136 native x86/
14 physically typed original PE/COFF call/global fields**.

Normal VC7.1 C++ reconstructs original stage/frame-zero
ResetAt453E20, short/dword motion state setup and FLAG
reset, x87 positive-height damping using global006583FC,
second x87 ground check using POS48+POS54, genuine
early ResetAt453E20/auxD and POS48 clear.
A first independent stage4/frame0 branch spawns kind
0x338 through 00453A70. A SECOND, separate stage4
branch prepares action1, initializes POS=8.0f,
POS54=9.5f, POS5C=0.65f and emits kind0x7F
through native 00453C80. Stage13/frame0
calls native auxiliary action0xB. There are
two authentic whole-fighter direct early/final
JMPs and all original branch destinations
are checked.

## Native fourth-argument width breakthrough

The initial real source declared native 00453C80
with a fourth INT parameter. With an observed
signed-facing byte expression, VC7.1 then emits
MOVSX r32, byte ptr [receiver+0x66], a 4-byte
instruction NOT present in the real original.
That complete candidate is 449B/136 x86
with an incorrect opcode and width at ordinal113.

A genuinely narrow fourth source parameter
(CHAR-equivalent under the pinned VC7.1 ABI)
instead emits a 3-byte MOV r8, byte ptr
[receiver+0x66], exactly like native original
ordinal113. The corrected normal whole
source emits **448B/136 x86** with every
original opcode mnemonic, instruction size,
relative location and all 14 native PE
field offsets [26,70,89,107,136,179,194,
204,227,251,310,343,406,439], types,
zero addends and actual original destinations.
Both signed-char and plain-char source
lvalues lead to this 3-byte instruction
when the method's actual fourth argument
is declared narrow, so its historical
nominal signedness remains provisional.

Six complete wrong/alternate full-parent
source variants also test float X/Y
comparison order, stage4 merging, ground
strictness and stage-zero Reset.
Combining the TWO independent native
stage4 branches is incorrect, even
if the resulting source seems simpler:
it changes original branch count and
physical game handler extent.

The source remains NONEXACT, with
**82 honest original nonrelocation
GPR operand bytes** plus two real
enclosing-whole-fighter epilogue
JMP relative pairs at offsets
219/220 and 444/445. No PE field,
GPR or parent-JMP mismatch is
hidden for exact credit.

One freshly compiled entire affected
normal VC7.1 parent now emits
**27,494 callable CODE B/7,649 x86**
(previous F865 27,061B/7,515 x86).
The verifier physically rechecks
all **37 preceding real original
switch state interiors**, their
genuine PE relocations and
honest register/branch negatives.
The original 1A0 stage-zero
guard JNE targets are checked again.
All five original 901B packed
afterRET switch tables are
independently verified.
The native 46B common getter
retains original receiver and
three PE calls but has four
real GPR byte differences
+10/+12/+16/+19.

Reproduce only this affected giant:

    scripts/repo-python scripts/verify-scripted-fighter-doubleprojectile-1f4-f866.py

Complete normal C++, VC7.1 COFF/PDB,
source type experiments and native
physical PE receipts remain in ignored
.analysis/f866-scripted-state1f4/.
The whole original 46,755B fighter
still NONEXACT. No independent
state/whole callable exact CODE
accepted; no corpus-wide cold replay.
