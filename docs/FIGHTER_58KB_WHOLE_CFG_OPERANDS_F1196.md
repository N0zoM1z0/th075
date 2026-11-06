# F1196 — Restore all 58KB native branch targets and five real operands

The live `probes/FighterWhole00543210F1041.cpp` now reproduces all
**1,905** original direct branch destinations and every non-GPR operand.
This extends the old F1025 external-target proof to the complete native
instruction sequence and corrects **253 jump targets plus five operands**.
The complete independently authored original **00543210 remains NONEXACT**:
**1,741 GPR positions /three CMP widths** still differ.

## Ordinary exits and the actual four-entry shared getter

The old F781 tail include placed a `return` and shared-getter label outside
the switch. All 253 ordinary switch exits reached the extra skip JMP at
whole ordinal **16,465**, rather than the native epilogue at **16,468**.
This can preserve high-level behavior while failing original native CFG.

The label now belongs **inside the switch**, following default's break.
Ordinary exits directly reach native **005515C2**; default retains its
separate short skip over the getter. Only native JMPs **00543462,
005435EA, 005436CD and 005436DC** from actions 0/2/4/5 reach the
shared getter at **005515BA**. The new tail fragment preserves those
four entries and introduces no extra call or invented return.

## Five actual non-GPR source corrections

| State / native instruction | Previous source | Original-backed correction |
| --- | --- | --- |
| 60 /005456FC | Landing sum `<=` ground | Strict `<`; native `TEST AH,5; JP` |
| 61 /00545925 | Landing sum `<=` ground | Strict `<`; native `TEST AH,5; JP` |
| 2DC /0054EA1C | Clamp X speed when `<=` zero | Strict `<`; native `TEST AH,5; JP` |
| 2F0 /0054FCA0 | `00453E60(10.0f)` | **20.0f**, native pushed bits `41A00000` |
| 2FA /00550BC3 | Left-side offset comparison `<` own X | Inclusive `<=`; native `TEST AH,41h; JP` |

These are genuine boundary/parameter differences overlooked by a
mnemonic/GPR-only comparison. The x87 comparisons retain their native
unordered exits. Existing handler bodies, real loops, call order and all
other operands are preserved. The four affected policy includes have only
one tracked C++ includer, this 58KB parent; none is a pinned accepted input.
The historical F781 tail remains unchanged for historical reproduction.

## Complete fresh evidence

| Whole original property | Pinned Japanese PE | Current normal C++ |
| --- | ---: | ---: |
| Entire callable CODE | 58,294B | **58,293B (-1)** |
| Ordered x86 instructions | 16,471 | **16,471** |
| Frame /saved-this | 0x218 /EBP-0x44 | **both agree** |
| EBP operand positions | 5,119 | **all agree** |
| Mnemonic /non-GPR operand debt | — | **zero /zero** |
| Direct branch destinations by native instruction ordinal | 1,905 | **1,905/1,905** |
| CODE field destinations at native instruction/field positions | 1,707 | **1,707/1,707**, zero unknown references |
| Dense DATA target instruction ordinals | 156 | **156/156** |
| Owned after-RET DATA | 943B | **943B**, including 319 exact sparse bytes |
| Wrong GPR positions /instruction widths | — | **1,741 /three** |
| Complete original exact acceptance | — | **NO** |

All **1,863** COFF records, including symbol identities, field geometry,
addends and local offsets, remain unchanged from the fresh previous parent.
Candidate byte changes are confined to the 253 jump displacements and five
corrected operands. The final tracked build is identical in CODE+DATA and
COFF to the last corrected research build. Original absolute relocation
offsets and whole byte equality remain unproved while widths differ.

The three wrong widths remain original 63's CMPs at **00545B1F,
00545BC6 and 00545C20**, whole ordinals **2,934 /2,977 /3,000**.
They account for the net one-byte CODE deficit; equal instruction counts
do not excuse them or the remaining GPR roles.

The unchanged tracked F1025 verifier cold-builds **only the affected parent**
and passes all 1,697 external PE destinations, ten CODE-local references,
156 DATA fields and all sparse bytes. The scoped local
`.analysis/f1196-58kb-whole-cfg/whole-audit.py` additionally checks every
whole operand, stack position and branch/dense target ordinal against an
explicit object path. Its `tracked.obj`, full before/after difference arrays,
source corrections, source-input SHA256 inventory and verified summary are
retained there. The previous F1025 OBJ/PDB, logs and receipts are preserved
under that directory's `f1025-before/` before the current output is rebuilt.
This local diagnosis is not a new canonical comparison gate or exact unit.

## Bounded 28KB controls and validation scope

Two earlier controls of 0055AC80's motion initialization use a two-float
array view or existing borrowed motion members. Both preserve all **28,868**
candidate CODE+DATA bytes and 696 field shapes, leaving 726 GPR /six widths.
An `/Op` control instead emits **29,323 CODE B /7,787 x86 /frame 0x2D0**
and is rejected against native 28,432 /7,653 /0x19C. They are unadopted;
all evidence remains in `.analysis/f1196-0055ac80-motion-layout/`.

Target/tracking, current summary, active handoff and whitespace checks pass.
Accepted source pins, canonical manifests, origin evidence and comparison
infrastructure are unchanged, so no full CI, corpus cold replay or historical
origin-test rerun is required. Coverage stays **982 whole exact functions /
871,649 original CODE bytes**. All 22 authored giants, including all original
58,294B here, remain pending in the conservative denominator.
