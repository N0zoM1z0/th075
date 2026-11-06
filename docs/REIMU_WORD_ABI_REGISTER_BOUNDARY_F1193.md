# F1193 — Reimu native WORD parameters and first register divergence

The live `0045DD70` parent now declares three independently accepted callees
with their actual signed-short parameters. This is an interface correction;
the complete original **remains NONEXACT** and gains no exact-byte credit.

| Native destination | Current caller declaration | Accepted implementation |
| --- | --- | --- |
| `0040FAC0` | `SetNativeActionAt40FAC0(short)` | `AnimationState::ResetPrimaryCounters(short)` in `src/GameLeafHelpers.cpp` |
| `0040FB40` | `SetAuxActionAt40FB40(short)` | `AnimationState::ResetSecondaryCounter(short)` in `src/GameLeafHelpers.cpp` |
| `00453D60` | `PrepareActionAt453D60(short)` | `FighterEffectPoliciesF135::PlaySharedSound(short)` in `src/FighterEffectPolicies.cpp` |

Names remain provisional. Raw coordinate-DWORD transport views are preserved;
this change does not reinterpret coordinate bits as numeric integer inputs.

A fresh serial VC7.1 build of the tracked parent produces **all 62,090
CODE+DATA bytes identical** to the selected F1192 object. All **1,824** COFF
field shapes, offsets, addends and local target offsets agree. Exactly **337**
decorated external names change from the int to the short parameter signature;
the whole native-field audit resolves them to the same original destinations.

The complete original has 60,999 CODE bytes; the source still emits **61,000
CODE bytes /16,837 x86**, frame **0x380**, saved-this **EBP-0x34**. The audit
retains all **5,444** native EBP operand positions, **1,684** direct branch
destinations, **1,682** CODE field destinations, **142** dense entry target
ordinals and the full **1,090B** after-RET DATA. Non-GPR operand, mnemonic,
stack and branch debt remain zero; **6,311 GPR positions /five widths remain**.
Matching PE destinations does not establish original absolute relocation sites.

## Bounded first-divergence investigations

The first wrong register is still native **0045FDA9**, state **59**, whole
instruction ordinal **2,292**. Its 19 GPR differences precede the first
`__ftol2` call; the remainder of that handler agrees. Every earlier whole
instruction, including the complete preceding state 58, agrees in GPR roles.
Historical F792/F793 negative controls were consulted before these experiments.

| Complete-parent experiment | Observed result | Decision |
| --- | --- | --- |
| Bare signed-short stage lvalue instead of parenthesized access | Identical CODE+DATA and field geometry; 6,311 GPR /five widths | No adoption |
| Explicit int intermediate for both float-to-short captures | Identical CODE+DATA and field geometry; 6,311 GPR /five widths | No adoption |
| Existing borrowed counter-window members for the two capture stores | Identical CODE+DATA and field geometry; 6,311 GPR /five widths | No adoption |
| Existing borrowed transform member for rotation reads/stores | 6,312 GPR /seven widths; reversed x87 load/add order, two non-GPR differences and one field-geometry difference | Rejected |
| Flat stage guard with a real continuation label | 61,001 CODE bytes /16,838 x86; state 59 has 96 rather than 95 instructions | Rejected |

The last candidate fails the whole instruction-count precondition. Its zipped
per-instruction differences are not meaningful whole GPR/CFG counts. None of
these variants replaces the verified parent, and no filler, assembly, fake
locals or exact-only body was introduced. Do not repeat these controls as new
leads or claim they resolved register phase.

## Retained evidence and validation scope

The selected current object is
`.analysis/f1193-reimu-register-boundary/adopted.obj`. Its
`adopted-whole-audit.json` records all remaining differences; the local F1192
`whole-audit.py` accepts that object path for diagnosis. `verified-summary.json`
contains transitive source and artifact SHA256s, byte/field identity results
and all bounded experiment outcomes. `word-parameter-field-changes.json`
retains each of the 337 before/after decorated symbols. Sources, previous
source snapshots, objects and compiler logs are preserved in the same ignored
directory. These are local research receipts, not canonical acceptance tests.

Only the research parent changes; accepted sources, headers, manifests,
ownership and comparison infrastructure are untouched. Target/tracking,
active handoff and whitespace checks pass. No full CI, corpus cold replay,
historical origin tests or new per-function tests are required or run.
Coverage remains **982 whole exact functions /871,649 CODE bytes**, with all
22 authored giants and all 60,999 original Reimu bytes still pending.
