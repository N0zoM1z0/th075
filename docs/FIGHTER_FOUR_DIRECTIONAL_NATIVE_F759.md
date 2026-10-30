# F759 — four original C8–CB fighter actions and downstream x87 scratch restored

**Significant original game-source reconstruction, NOT a whole-function exact
match.** Target is the pinned user-supplied Japanese TH075 1.11
`resources/th075.exe`, SHA-256
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
The actual game-authored callable function is `00543210`, **58,294
native CODE bytes** plus **943 separately owned after-RET dispatch DATA
bytes**. Four switch cases here are not independent callable functions;
zero new original CODE bytes are added to the canonical exact ledger.

## Reconstructed original native state actions

`probes/FighterFourDirectionalC8F759.inc` provides a normal VC7.1 C++
source for four complete adjacent original action branches, compiled in
**one full parent** with all previously reconstructed fighter cases.
These are true game transition/attack handlers with concrete stage checks,
x87 movement and direction-based projectile launches, not fake markers
or decompiler-copy fragments.

| Action | Original physical handler interval | Complete original CODE | Native x86 | Genuine typed physical PE/COFF fields | Legitimate jumps outside action to shared parent tail |
| --- | --- | ---: | ---: | ---: | ---: |
| `0xC8` | `0054737F..0054756F` | 496 B | 145 | 16 | 5 |
| `0xC9` | `0054756F..00547717` | 424 B | 127 | 14 | 3 |
| `0xCA` | `00547717..005478CE` | 439 B | 129 | 12 | 2 |
| `0xCB` | `005478CE..00547A8B` | 445 B | 131 | 12 | 2 |
| **Sum** | | **1,804 B** | **532** | **54** | **12** |

The original PE establishes each complete interval, original ordered
instruction and field type, control-flow branch, and source owner.
`0xC8/0xC9` set up the original `ConfigureStormAt454BC0(3,4,0xFF)`
policy, initialize position and counter, handle bounce, owner-target
facing and projectile families `0x7D/0x7E/0x81`; `0xCA/0xCB`
include return-to-action `0xA`, position/velocity resets and directed
`0x7D/0x7E` launches. The original two x87 deceleration constants
`006593E8` and `00658290` are observed actual memory operands.
Borrowed X-coordinate source uses only the separately proven `+0x44`
float view from F752, not an instantiated guessed complete fighter.

The entire 58KB compiled C++ parent now reproduces all **532/532
ordered original action instructions, sizes and mnemonics**, and all
**54/54 physically typed zero-addend COFF relocations**, each at the
native instruction and with the same original PE destination.
There are **1,540 byte-identical nonrelocation/non-tail bytes** across
these four complete actions. The remaining **12 legitimate parent-tail
relative JMP displacement fields** differ because the complete parent
CODE is still shorter, so those bytes are specifically *not*
accepted as exact. No branch displacement is patched, no original
executables are modified, and no partial case receives callable CODE
credit.

## Unexpected causal win: nine downstream native x87 scratch slots

Compared with the previous complete F752 parent, the additional real
C8–CB game sources change VC7.1's natural lifetime allocation and
restore **nine later, physically original `MOV` + `FILD` scratch
locations** in the same full parent:

| Later original action | Original and new source integer-to-x87 EBP scratch |
| --- | --- |
| `0x18A` | `EBP−0x88` |
| `0x18B` | `EBP−0x8C` |
| `0x190` | `EBP−0x90` |
| `0x191` | `EBP−0x94` |
| `0x192` | `EBP−0x98` |
| `0x194` | `EBP−0x9C` |
| `0x195` | `EBP−0xA0` |
| `0x2D0` | `EBP−0x184` |
| `0x302` | `EBP−0x208` |

Each original and generated backing integer store and consuming
`FILD` instruction was checked using original PE x86 data and the
new COFF instructions in the full parent. In particular, F752's
`0x190` loop had compiler scratch `EBP−0x80` (three-byte MOV/FILD
operands) versus original `EBP−0x90` (six-byte memory offsets).
Those authentic original operand widths now emerge naturally from
the preceding real C8–CB source, rather than an invented padding local
or independently compiled case. **This fixes a genuine cross-case
source lifetime hypothesis**, but the newer full-parent register allocation
also regresses three formerly strict contexts: original action `190`
now has **40** source GPR-role discrepancies, `191` has **40**, and
`192` has **34**, despite their now-native machine-code widths. The
prior F752 source had zero normalized GPR errors in those same cases,
but a 10-byte size deficit in `190`. These are genuine current-parent
comparisons against the original PE, and the F759 verifier now checks
all three negative register counts. Do not claim whole-case exactness
from recovered FILD scratch alone.

## Whole parent and after-RET DATA remain separately accounted

The current parent generates **56,954 of the original 58,294 callable
CODE bytes**, a remaining **1,340-byte deficit**. It is *not*
byte exact as an entire function, and has **zero newly accepted whole
authored CODE**. The verified generated after-RET DATA is still the
original 943-byte structure, with **156 actual DIR32 switch label
fields** pointing to real native/source instruction starts, and
**319/319 other sparse bytes** identical. This DATA is not new
callable game CODE, and the whole-function 98% goal is not achieved.

## Reproducible strict affected-parent verification

The tracked [`verify-fighter-four-directional-c8-f759.py`](../scripts/verify-fighter-four-directional-c8-f759.py)
rereads the attested original, generates an entire naturally composed
fighter source with all earlier tracked genuine cases, freshly builds
**only that one affected original-shaped VC7.1 source TU** using
`/Od /Ob0 /Gy /GR- /GX- /GS /Zi`, then verifies entire case
intervals, 54 original PE/COFF relocation field owners/targets,
nonfield differences including shared-tail negative bytes, nine
downstream integer-to-FPU slots, and all original after-RET DATA.

```bash
scripts/repo-python scripts/verify-fighter-four-directional-c8-f759.py
# F759 C8: 496B /145 x86/16 fields; C9: 424B/127/14
# F759 CA: 439B/129/12; CB: 445B/131/12
# Downstream: nine original MOV/FILD slots recovered
# 943B original afterRET DATA /156 DIR32 /319 nonfield correct
# Whole 00543210 boss NONEXACT; zero new official match credit
```

Complete source, fresh COFF object, compiler transcript and output
receipt remain under ignored local
`.analysis/f759-fighter-c8-cb-original/`; this directory does **not**
replace the tracked source/verifier. This is one affected parent
comparison, **not a cold replay of the 970 accepted units**.
