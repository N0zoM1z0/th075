# F1216 — recover original 005C9CC0 initial states and real loops

F1217 continues the same body to30/67 states; see [middle-state evidence](OBJECT_ADVANCE_005C9CC0_MIDDLE_STATES_F1217.md). The measurements below describe the frozen F1216 checkpoint.

The new [natural C++ body](../probes/CharacterObjectActions005C9CC0F1216.cpp)
contains **13 of 67 nondefault states**: 800–806, 835, 901, 902 and 995–997.
The original 43,501B callable remains incomplete and NONEXACT; **all original
CODE bytes remain pending**. No case interval is an accepted match unit.
The independently reviewed R048 authored origin remains unchanged.

## Original extent, owner and virtual interface

The pinned Japanese PE contains 005C9CC0..005D46AC, **43,501 CODE B /11,447
x86**, frame **0x470**, saved this **EBP-0x4C**. Original CODE SHA-256 is
`5f27a4c2461b838ee1f74ca2c5cbd8fea07f2278d6d0bd0270b593929d182c5c`.
Its owned after-RET DATA is **470B**, 68 dense entries and 198 sparse bytes,
SHA-256 `5bd09eae717bf0546d5053797341d7af2bb58771f39fd900d800fe67529812ab`.
Default is 005D46A1; the epilogue begins 005D46A9. Thirteen INT3 bytes follow
the DATA. These entire boundaries are retained, not inferred from the draft.

Already accepted F422 constructor 005C9C20 is 146B, SHA-256
`e9f615d51763e7a742cd56d6e4110b957c8ea828ff36132fa28a9a9494fff1a6`.
It installs vtable 00659F14 and stores the owner at E4h. Independently reread
20 native vtable bytes contain 0045B880, **005C9CC0**, 0040FC70, 00410350,
00410A00. The new declaration therefore exposes the observed slot-0 binding
and virtual slot-1 advance. No constructor bytes are counted again. The
borrowed receiver interfaces establish no complete owner layout and are
never instantiated or embedded.

## Genuine native behavior

The prefix retains opponent/owner freeze guards and the short countdown
decrement/early exit. 800 follows owner action 301 with facing*128 and y+66,
retains the distinct owner-loss phase transition, status-6 reset, transform,
asymmetric initial scale and the second observed short hit-count write.

801/802 retain different growth, bounce, hit, landing and repetition policies.
Their cancellation paths each contain an actual six-iteration effect-996 loop.
803 has an actual fifteen-iteration cancellation loop, movement and speed
clamp, effect-804 trail, and an actual eighteen-iteration effect-805 burst
after sound and camera shake. 804 retains randomized velocity and shrinking.
805 has an actual two-iteration cancellation loop, different frame-0/frame-1
hit counts, polar speed decay, effect-806 trail and distinct stage scaling.
806 preserves the ordered alpha/blue/green wrapping subtraction and early exit.

The five real local indices are used for these loops:

| Source index | Original EBP offset | Fresh COFF/listing offset |
| --- | ---: | ---: |
| cancelIndex801 | -4 | -4 |
| cancelIndex802 | -8 | -8 |
| cancelIndex803 | -0xC | -0xC |
| burstIndex803 | -0x10 | -0x10 |
| cancelIndex805 | -0x14 | -0x14 |

No dummy index or filler local is added for later code. Source this is
currently EBP-0x18, because later genuine locals are still absent.
Ghidra's local names are offset by four relative to physical EBP slots;
native MOV/CMP/back-edge instructions and the fresh listing establish the
table above. Native loops are not replaced by unrolled statements.

835, 901/902 and 995–997 have independently checked correspondence to
existing natural source. 835 retains its two 2.0 scales; 901/902 retain the
plain advance/clear guard. 995/996 preserve their full distinct reward/hit
behavior; 997 retains owner health ratio, scale, angle and stage 10.
The correspondence scan is discovery evidence, not separate exact credit.

## Scoped compiler and operand evidence

The serial headless pinned VC7.1 profile is
`/Od /Ob0 /Gy /GR- /GX- /GS /Zi /I src /I probes`. Fresh selected
**reviewed.obj** emits **7,168 CODE B /1,925 x86**, frame **0x80**. The
partial dispatch contains 14 dense entries and the actual 198 sparse bytes;
all selected case destinations and the default are checked from COFF.

The prefix and all 13 written native intervals agree in instruction sequence
and operand shapes after explicit GPR/negative-stack elision. The diagnostic
retains actual branch destination ordinals, helper addresses, field offsets,
scalar bits and independently reread COFF literal contents. Original integer
comparisons require **>8** and **>15** for the two landing ranges; >=9 and
>=16 preserve behavior but emit different native comparisons. Both first and
reviewed source/object/listing stages are preserved.

The prefix and all written states through835 have **zero raw GPR-role debt**.
Frame/this/later temporary stack positions and some instruction widths remain
wrong in this incomplete context. Later written states retain GPR differences
as well. These diagnostics do not establish callable byte equality.

`.analysis/f1216-object-5c9cc0-recovery/` retains pinned native exports,
fresh read-only Ghidra decompilation and attested log, actual constructor/
vtable/origin inputs, native family comparisons, source generator, both
source/header snapshots, objects/listings/build logs, local diagnostic,
`reviewed-source-diagnostic.json` and `verified-summary.json`.
Continue the remaining 54 states in this same body from the complete native
intervals; 807 is the next unwritten state. Preserve the nine existing complete
research parents, all accepted units and every local historical archive.

Only this unaccepted source/header and documentation are added. Target/tracking
and handoff checks suffice; no accepted input changes, canonical infrastructure
changes, origin retest, full CI, corpus replay or per-function test is needed.
