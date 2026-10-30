# F847 — Two original 134/135 projectile launches in the same 46KB fighter

The pinned Japanese TH075 1.11 fighter at 005214B0
owns 46,755 original callable CODE B plus five
packed afterRET dispatch tables totaling 901 DATA B.
The real original actor's cases at 005269B7..00526ACC
are two independent contiguous game interiors:

| Native action | Original CODE/x86 | Actual typed PE fields | Sprite / spawn stage / animation stage |
| --- | --- | ---: | --- |
| 134 | **278 B/82 x86** | 7 | 0x334 at stage4, prepare 0x1D at stage5 |
| 135 | **278 B/82 x86** | 7 | 0x339 at stage7, prepare 0x1D at stage7 |

Both normal C++ sources preserve actual original
stage/frame-zero reset, real FLAG and ground x87
motion, conditional action0 and +0xF00 short clear,
then genuinely spawn the game projectile at
00453A70 using observed this+0x44/+0x48
coordinate bit patterns, real facing byte this+0x66,
and source kind 0x334 or 0x339. The machine code
alone cannot distinguish a signed-char from a
plain-char formal argument for this method.
Those original historical type declarations
remain provisional.

The selected whole VC7.1 source is rebuilt after
physically verifying the immediate F846 parent.
It now emits **23,257 callable CODE B/6,371 x86**
(previous 22,731B/6,211 x86). Each new
state matches every original 82 x86 mnemonic,
width, GPR/x87 operand and all seven real
PE global/call field offsets/types/zero addends
and original destinations. The only two
authentic nonrelocation byte differences per
full original interior are offsets 274/275:
the last long JMP targets the enclosing complete
fighter epilogue 0052CB4F, whose final relative
displacement cannot match this incomplete parent.

Two independent original-source controls were
also compiled: C++ plain versus signed char
facing arguments emit identical code; using
animation0x1C instead of genuine 0x1D
changes an additional physical native operand
byte in each state. This prevents mistaking
a structurally identical but behaviorally wrong
actor parameter for exact source.

The same freshly compiled whole parent physically
rechecks 18 prior original C8..D2, 12C..12F,
130/131/133 case extents and all typed PE fields.
The actual 46B/16-x86 common default/getter
still matches **34/34 native nonrelocation bytes**
and all three original PE REL32 calls.
All five original afterRET packed switch
tables are independently verified in the
new whole COFF object.

Selected targeted reproduction:

    scripts/repo-python scripts/verify-scripted-fighter-projectile-134135-f847.py

The source experiments, full VC7.1 COFF/PDB and
original physical PE receipts reside under ignored
.analysis/f847-scripted-spawns134135/.
Original whole 46,755B fighter remains NONEXACT.
No independent case or separate packed DATA
receives callable authored exact CODE credit.
No mass accepted-unit cold replay.
