# F893 — Complete original 2DC 660B game state and authentic ground-contact condition

Pinned original Japanese TH075 v1.11 fighter at 005214B0:
46,755 callable whole CODE B and 901 separately owned
packed afterRET switch DATA B. Physical state2DC at
0052AFBB..0052B24E is **660 complete original inner
CODE B /188 x86 /17 physically typed actual PE fields**.

This complete original state resets stage0 short+F00/+F02/+F04.
At stage2/frame0 it sets original motion dword+7C=0,
short+80=1, height12.5f? No: the original code
unambiguously stores height **10.0f** at this stage
and vertical speed0.0f. It emits native sprite0x33B
through 00453A70 with raw integer X/Y and prepares1.
At stage13/frame0 it emits real sprite0x338 and also
prepares action1.

The original physics then has two distinct x87
thresholds against native ground global0065782C.
For positive height+0x50, it subtracts actual
float global00657478 and clamps height to zero
when below ground. When position+0x48 is above
ground and stage<24, it subtracts original
global006598B0 from float vertical impulse+0x54.
If **positionY+verticalImpulse <= ground**, it
calls original auxiliary action24, clears
height/speed/position to zero, then RETURNS
through the enclosing entire fighter's far
epilogue. This relation is inclusive <=,
not the plausible strict < alternative.

Only after those checks does the original
getter completion branch set native action0
and call original RandomBoundaryAt455580(0,30),
storing actual short+0x516. The random call
is within the current-action completion if.
At stage13 it uses genuine once-only
short+F00<1, increments the actual
16-bit counter and invokes auxiliary2.
Stage15 initializes height12.5,
vertical speed15.0, dword+7C=0
and short+80=1. Stage24 calls auxiliary22.

One freshly compiled full pinned VC7.1 parent
generates **40,552 callable CODE B/11,433 x86**
(F892 prior 39,907/11,247).
The native 2DC source has exactly 660B/188
original x86, with all opcode widths,
instruction-relative positions and
**seventeen true physical original PE
field offsets/types/zero addends and
actual executable/global destinations**:
[26,163,173,232,242,254,273,291,320,
351,375,392,435,459,471,553,651].

The complete selected 2DC state has
ZERO native wrong GPR or internal branch
bytes: only four genuine enclosing
father far-epilogue JMP operand bytes
at original case-relative +427/+428 and
+656/+657 remain different.

Three independently compiled full VC7.1
false-source parents have identical
660B/188x86/17-field case geometry but
different ORIGINAL bytes: wrong strict
ground < instead of <= (additional wrong
case+383), moving true random outside
current action guard (case+452), and
incorrect sprite0x33A instead of
native0x33B (case+155). The verifier
requires these false source negatives,
not merely matching lengths.

The new whole parent also physically
rechecks all **68 previous source-backed
original game cases**, including
2C2 whole 2,274B and 2DB whole 556B,
the 1FD true one-byte CMP error
and 252/254 shifted PE fields,
all five original 901B afterRET
packed jump tables and native
shared getter's 34/34 original
nonrelocation byte equality with
three true original PE calls.

Reproduce ONLY this affected original
whole fighter:

    scripts/repo-python scripts/verify-scripted-fighter-stage2dc-f893.py

Whole normal C++, VC7.1 OBJ/PDB,
three false-source control objects
and strict original PE JSON receipt
remain under ignored .analysis/f893-scripted2dc/.
Whole original 46,755B fighter still
NONEXACT. No independent case or
DATA credited as exact callable
CODE. No all-unit cold replay.
