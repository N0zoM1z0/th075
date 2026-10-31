# F983 — Native 1F8/1F9 signed X, twelve authentic FILD/FSUBR chains

The pinned Japanese TH075 v1.11 original game Fighter 004AC040
owns **82,796 original callable CODE bytes /22,721 x86** plus
**1,126 separately owned afterRET jump-table DATA bytes**.
The tracked [normal VC7.1 C++ partial father](../probes/FighterWhole004AC040F983.cpp)
is still NOT a complete original source or whole-function exact match.

Two authentic game-state interiors occupy these independently
verified original PE ranges:

| Native game state | Real original CODE interval | Native CODE/x86 | Original typed PE fields |
| --- | --- | ---: | ---: |
| 1F8 | 004B5A75..004B5F05 | **1,168 B /339 x86** | **28** |
| 1F9 | 004B5F05..004B6394 | **1,167 B /339 x86** | **28** |

Both native states manipulate actual signed short stage/frame,
signed short +0xF00/F02, original +0x11 opacity byte, fall motion
and ground contact. They include an original randomized 0x33E
projectile, **six ordered 0x338–0x33D seven-argument shots**,
native stage6 motion state, stage8 bounded auxiliary action
and a stage11 auxiliary transition. Original 1F8 and 1F9
have opposite source X velocity: **+60** versus **−60**.

## A real compiler grammar recovery, not a byte graft

An initial complete natural parent emitted 339 x86 instructions
per case, but six independent X shot calculations produced
**FLD + FISUB integer** instead of the true native
**MOVSX, IMUL facing×7, MOV integer temp, FILD, MOV receiver,
FSUBR this+0x44** sequences. Those errors repeated twelve
times across the two cases, creating **30 incorrect ordered
mnemonics per case**.

Five full-parent natural C++ X-expression variants
reused the already independently verified F917 *borrowed original X*
view rather than assuming a complete fighter type. With

    reinterpret_cast<FighterProjectileXViewF917*>(this)->coordinateXAt44
        - float(signedFacing * 7)

the real VC7.1 compiler naturally restores all **twelve
original signed IMUL/FILD/FSUBR chains**, for ZERO wrong
mnemonics in all 678 native instruction positions.
No manual registers, artificial stack padding, assembler or
original-machine-code copying was involved.

A further eight whole-parent genuine opacity expression variants
tested native unsigned byte +0x11 comparison grammar. They did NOT
fix its one remaining x86 width mismatch per case at local ordinal
**64**: original 1F8 uses **CMP ECX,235** (6B) while source
chooses **CMP EAX,235** (5B); original 1F9 uses **CMP EAX,235**
(5B) while source chooses **CMP ECX,235** (6B). That is
a real native GPR ownership and register-specific x86 width
difference, NOT a missing line of gameplay code.

An independent original PE relocation check also identified a
false initial assumption: the six 1F8/1F9 shot-Y additions
must use native global **00659490**, NOT 00659270 inherited
from another action. The tracked final C++ source was corrected
and all twelve Y source fields independently checked against
the original actual PE target addresses, along with all
other actual PE target fields.

The [replayable bounded complete-partial-father verifier](../scripts/verify-third-fighter-signed-x87-f983.py)
freshly compiles both tracked normal VC7.1 parent sources
(F982 old case markers versus F983 real game C++), checks every
one of **56 real original typed zero-addend PE external targets**,
all original x86 positions, previous 1F7 case, all **151 afterRET
DIR32 local labels** and **522 native DATA nonfield bytes**.

| Whole original-shaped partial father | F982 old | F983 selected |
| --- | ---: | ---: |
| Source CODE B | 40,025 | **42,330** |
| Source x86 instructions | 10,979 | **11,653** |
| 1F8 source B/x86 | 15/2 | **1,167/339** |
| 1F9 source B/x86 | 15/2 | **1,168/339** |
| Original incorrect mnemonics | not aligned | **0/0** |
| Incorrect original x86 widths | not aligned | **1/1** |
| Wrong original GPR roles | not aligned | **174/168** |
| Original PE call/global targets | markers | **28+28** |
| Original afterRET DIR32/nonfield | 151/522 | **151/522** |
| Whole original callable exact | NO | **NO** |

The original complete fighter still has a 0x720 frame,
saved receiver EBP−0x64, different global absolute PE/COFF
positions and many remaining unsourced game actions.
Matching the order of inner-case mnemonics does not earn
whole callable exact CODE credit.

Reproduce only the two affected complete partial father sources:

    scripts/repo-python scripts/verify-third-fighter-signed-x87-f983.py

Original PE and object compiler evidence plus negative controls are
retained under ignored .analysis/f983-third-original-proof/,
.analysis/f983-third-1f8/x87_variants.log,
.analysis/f983-third-1f8/x87_variants.py,
.analysis/f983-third-1f8/opacity_variants.py and
.analysis/f983-third-1f8/opacity-variants.json.

**New exact entire callable GAME functions: zero.
New credited original CODE bytes: zero.
No corpus-wide cold replay.**
