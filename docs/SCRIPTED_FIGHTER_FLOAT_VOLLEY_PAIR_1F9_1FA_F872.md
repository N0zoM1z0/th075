# F872 — Two distinct original 227B float volley states and real x87 stack-slot allocation

The pinned Japanese TH075 v1.11 fighter at 005214B0
owns 46,755 callable original CODE B and five packed
afterRET switch tables totaling 901 independently
owned DATA B. The actual game actions 1F9 at
0052846E..00528550 and 1FA at 00528551..00528633
are two distinct complete **227B/65-x86/seven-PE-field**
native switch interiors, not independent callable leaves.

Both real states reset their motion counters at stage0,
then at stage2 and actual state dword+0x7C equal3,
fire native floating X/Y sprite kind0x32 through
00453C80. Real float X is signed facing*coefficient
converted via a native FILD scratch then added to
float X+0x44. Float Y is native member+0x48 plus
a genuine actor-specific global. The game then
prepares animation0x14 at 00453D60, writes
short0x1E to observed real owner pointer
this+0x2E8 -> +0x82, changes state and
returns through the enclosing giant epilogue.

| Original state | Facing coefficient | Real Y global | Original FILD scratch | Next action |
| --- | ---: | --- | --- | --- |
| 1F9 | 50 | 006598BC | EBP-0x70 | 1FB |
| 1FA | 36 | 00659310 | EBP-0x74 | 1FC |

A freshly compiled ONE normal VC7.1 affected full
parent produces **29,634 callable CODE B/
8,306 x86** (F870 29,210/8,180).
Both complete native case extents have
**all 65 original x86 mnemonic/size/offsets**,
and all seven original PE call/global field
offsets [26,100,140,150,181,194,218],
kinds, zero addends, source symbols and
true original destinations.

Importantly, the source compiler automatically
allocates the original consecutive FILD scratch
slots at EBP-0x70 for the first state and
EBP-0x74 for the second. These are genuinely
used integer-to-float temporary objects,
not artificially inserted padding.
Wrong X coefficient, next state, or owner
field offset controls produce additional
real original nonfield mismatches.
Some equivalent orders of the Y addition
produce identical machine code; its
nominal historical spelling is unproved.

Neither native state is byte exact under this
incomplete whole-parent source: each retains
**35 honest GPR operand differences**
and two original giant epilogue JMP byte
pairs at +186/+187 and +223/+224.
No byte, field or case is separately credited.

The new whole COFF also physically rechecks
all **42 previously source-backed original
case interiors**, their genuine target PE
relocations and prior actual nonfield errors,
all five original 901B packed afterRET
jump tables and the 46B/16-x86 common
getter's **34/34 original nonrelocation
bytes and three correct PE calls**.

Reproduce only this affected giant:

    scripts/repo-python scripts/verify-scripted-fighter-float-volley-pair-f872.py

Complete VC7.1 C++/COFF/PDB, candidate source
experiments, original Japanese PE receipts
and strict JSON proof remain in ignored
.analysis/f872-scripted-pair1f9-1fa/.
Whole original 46,755B fighter NONEXACT.
No independent-case exact authored CODE,
no mass cold replay.
