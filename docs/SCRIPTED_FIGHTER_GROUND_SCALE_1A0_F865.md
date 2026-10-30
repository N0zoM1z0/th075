# F865 — Original native 1A0 float scaling completes five separately bounded game states

The pinned Japanese TH075 v1.11 original fighter at
005214B0 owns 46,755 callable CODE B and five
separately owned afterRET packed switch DATA tables,
901 B in total. The physical interval
005277EA..00527BBD contains FIVE separately
addressed original game handlers, not a single
980-byte action:

| Original switch state | Actual full native inner CODE / x86 |
| --- | --- |
| 198 | 199 B /60 x86 |
| 19A | 302 B /86 x86 |
| 19C | 122 B /35 x86 |
| 19E | 122 B /35 x86 |
| 1A0 | 235 B /67 x86 |
| **Total distinct original interiors** | **980 B /283 x86** |

F865 reconstructs the final original 1A0 state at
00527AD3..00527BBD: **235 native B/67 x86/5
genuine physical original PE call/global fields**.
Stage/frame-zero initializes actual short/dword
owner state +0x80/+0x7C. Two independent
original x87 floating-point operations scale
POS at this+0x50 and POS54 at this+0x54
by the real native global 00658348. Original
physical game CODE requires **FLD member (3 B),
then FMUL global (6 B)** for BOTH operations.
Bare POS54=POS54*global instead reverses the
second x87 width pair. A genuinely evaluated
left-lvalue POS54=(*(&POS54))*global naturally
recovers the original second FLD/FMul pair
without forced registers, fake stack locals
or inline assembly.

The original floating ground comparison
POS48+POS54 <= global0065782C then zeroes
POS, POS54, POS48 IN THAT ORDER. If
actual stage>3 it subtracts drag POS5C;
the real game getter/setter condition
uses action9, and stage4/frame0 sets +0x7C=1.

Seven normal full-parent VC7.1 source variants
checked float left-lvalue forms, compound
multiplication, ground float operand order,
real zero store order and signed stage
condition. The selected source emits the
complete original **235 B/67 x86** state,
all native x86 mnemonics, instruction widths
and relative offsets, plus **all five actual
original PE field positions, relocation
types, zero addends, source symbols and
physical native targets** (two multiplier
DIR32 fields, ground DIR32, getter/setter
REL32 calls). Genuine non-PE machine
differences remain **51 native GPR operand
bytes** and TWO authentic whole-giant
epilogue JMP operand bytes at original
1A0 offsets +231/+232. These must not
be hidden or called exact original CODE.

The tracked verifier regenerates the
previous F863 physical evidence if missing,
then freshly compiles only ONE selected
entire VC7.1 father. It emits **27,061
callable CODE B/7,515 x86**, up from
F863 26,841 B/7,450 x86.
It also independently rechecks all
FIVE 980-byte original switch interiors
with their distinct native entrypoints,
16 preceding original GPR-affected
whole game cases, 20 other native
source-backed cases, and all original
physical PE call/global fields.
All FIVE separate original 901 B
packed afterRET jump tables are
reverified in the new COFF.

The original 46 B/16-x86 shared default
getter still has three correct physical
original PE calls but **four true
nonrelocation GPR byte negatives**
at offsets +10/+12/+16/+19 in the
current bigger source. Do not carry
earlier smaller-context 34/34
claims into this father.

Reproduce ONLY this selected giant:

    scripts/repo-python scripts/verify-scripted-fighter-ground-scale-1a0-f865.py

Whole generated source, VC7.1 COFF/PDB,
original PE receipts and the seven
source alternatives reside in ignored
.analysis/f865-scripted-1a0/.
Original callable 46,755B fighter
remains NONEXACT; no inner case,
getter or packed table DATA receives
independent whole-function authored
exact CODE credit. No all-unit cold replay.
