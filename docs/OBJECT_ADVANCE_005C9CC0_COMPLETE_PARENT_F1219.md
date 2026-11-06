# F1219 — complete original 005C9CC0 source and whole native audit

The [single natural C++ body](../probes/CharacterObjectActions005C9CC0F1216.cpp)
now contains all **67 nondefault states**, adding the final 25 actual
900-series states to F1218. It is **complete but NONEXACT**. All **43,501
original CODE bytes remain pending**; no interior state or helper receives
exact credit. Independent R048 authorship, original constructor/vtable and
full native extent remain in [F1216](OBJECT_ADVANCE_005C9CC0_INITIAL_STATES_F1216.md).

## Complete source and original machine evidence

| Checked property | Original PE | Selected fresh VC7.1 object |
| --- | ---: | ---: |
| Entire callable CODE | 43,501B | **43,502B (+1B)** |
| Entire x86 instruction count | 11,447 | **11,447** |
| Stack frame / saved-this | 0x470 / EBP-0x4C | **Both agree** |
| EBP operand positions | 3,971 | **All agree** |
| Mnemonic / non-GPR operand differences | — | **Zero / zero** |
| Direct native branch targets | 1,001 | **All instruction ordinals agree** |
| CODE reference destinations | 923 | **All agree at actual native instruction fields** |
| Owned after-RET DATA | 470B | **470B** |
| Dense destination ordinals / sparse bytes | 68 /198 | **All agree** |
| Wrong GPR roles / instruction widths | — | **935 /1 remain** |
| Whole callable cold-exact acceptance | — | **NO** |

The 68 dense entries include the default; the sparse remap spans actions
800–997. The entire original CODE is `005C9CC0..005D46AC`, followed by the
owned 470B table/remap and thirteen alignment INT3 bytes. CODE SHA256:
`5f27a4c2461b838ee1f74ca2c5cbd8fea07f2278d6d0bd0270b593929d182c5c`.
Owned DATA SHA256:
`5bd09eae717bf0546d5053797341d7af2bb58771f39fd900d800fe67529812ab`.
No boundary, original hash, origin or canonical accepted manifest changes.

All eighteen real used loop indices from F1218 remain. Completing actual
later expressions restores the original **0x470** frame naturally, without
padding or forced slots. All temporary and named stack operands now agree.
The prefix, every state through916, and 995–997 have zero GPR/EBP/width debt.

## Recovered final native behavior

900 retains gravity, its immediate ground transition/return, independent
upper bound and later phase velocities. 903 copies raw owner coordinates;
904 retains randomized scale and a 32-bit promoted byte subtraction.
905 retains its two independent owner-stage seeking paths, X-square before
Y-square in the scalar input, separate repeat limits/timers, signed-short
angle assignments, wrap tests and the native early completion exits.
906 preserves hit/fade/aim behavior and 907 its expanding speed, bounds and
completion return. Their angle helper consumes two floats and returns ST0;
no spurious third argument is inferred from Ghidra's provisional decompile.

910 retains the repeated owner-action read and stage>12 guard. 911 borrows
actual owner F22/F24 coordinates, preserves ten distinct attachment offsets,
owner action774, phase16 reaction, bounce, fade and immediate exits. 912
writes converted coordinates back every tick, then follows, aims and reacts
to the ground independently. 913/914 preserve different growth, rotation,
repeat and shrink policies. 913's two separately randomized effect916
spawns use speed **960**, not a guessed donor value. 915 retains native
spawn-after-clear exits; 916 retains the hit/phase reaction and velocity reset.

918/928/929 remain three separately emitted states with growth **0.033f**,
clamping, random scale `range * 0.025f + 0.95` (double addition), native bounds,
rotation and sound/aim behavior. 919 retains duplicate initialization writes,
fade-in threshold220 and phase-qualified motion. 920/921 retain their actual
simplified phase repetition instead of copying all of 913/914's behavior.
922/924/926 preserve three independent initialization/advance bodies.
923/925/927 retain `-RecordedRange(0, 3) - 13`: original NEG precedes SUB.
The native post-motion `Y - velocityY` ground test, independent pair spawns,
continuation after ClearField74 and 927's first-bounce **0.75** factor remain.

The observed 0045B850 notification receives integer31 in 913 and remains an
undefined borrowed receiver call. Neither it nor scalar helper00428D20 gains
an origin or exact adoption. All 95 unknown origins remain uncredited.

## Remaining complete-function debt

| State | Wrong GPR positions | Wrong widths |
| --- | ---: | ---: |
| 918 | 82 | 0 |
| 919 | 140 | 1 |
| 920 | 136 | 0 |
| 921 | 56 | 0 |
| 922 /924 /926 | 32 each | 0 |
| 923 /925 | 97 each | 0 |
| 927 | 93 | 0 |
| 928 | 110 | 0 |
| 929 | 28 | 0 |

First divergence: **005D2558**, whole instruction **9,213** (zero-based),
inside918 after initialization: native `mov ecx,[ebp-4Ch]`, source EAX.
The sole width difference is whole instruction **9,411**, **005D2841** in919:
native `cmp eax,220` is5B; source `cmp edx,220` is6B. Register differences
continue through928 and 929's initialization, then stop. This is observed
debt, not proof of a particular frontend or allocator cause.

Six natural source controls—chained zero velocities, explicit growth
assignment, unsigned phase literal, integer-zero velocity literals, nested
initialization guards and a health-guard switch break—retain the same CODE,
CFG and935/1 debt. Double0.033 introduces the wrong qword literal; a borrowed
00659F28 growth reference reverses the original FLD/FADD order. Both are
rejected. Selected source is restored; do not repeat these controls.

## Reproduction and retained evidence

`.analysis/f1219-object-5c9cc0-late/` preserves immutable **native-order.cpp**,
**native-order.hpp**, **native-order.obj**, **native-order.asm**, build log,
`native-order-source-diagnostic.json`, `native-order-whole-audit.json` and
`verified-summary.json`. Earlier seek/capture/complete stages, generators and
all negative-control sources/objects/listings remain. Native/Ghidra and
constructor exports remain in F1216; F1217/F1218 snapshots stay preserved.

Selected serial headless VC7.1 profile:
`/Od /Ob0 /Gy /GR- /GX- /GS /Zi /I src /I probes`.
`whole-audit.py [OBJ]` checks all native instructions, direct targets, actual
reference destinations and owned DATA. The source diagnostic also reads
literal payloads from actual COFF sections. These are research diagnostics;
matching reference destinations does not certify original relocation offsets.
Only a complete canonical unit with zero differences after affected-unit
cold replay can be accepted. No full CI, corpus replay, new per-function
test, origin retest, accepted-source edit or helper definition is added.
