# F1200 — all 1,927 original 004AC040 direct branch targets agree

The complete live normal C++ source
[`FighterWhole004AC040F1020.cpp`](../probes/FighterWhole004AC040F1020.cpp)
now agrees with every original direct jump destination by whole instruction
ordinal. All 45 remaining differences from F1198/F1199 were real source
scope errors. This is progress toward the original callable, **not whole
exact acceptance**: 6,958 GPR-role and twelve instruction-width differences
remain.

## Native control flow and source correction

Each guard, its native destination and intervening statements were reread
from the supplied Japanese original, SHA256
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
The complete native branch list and surrounding instructions are retained
locally; the source changes are ordinary C++ statement scopes.

| Original actions | Incorrect targets repaired | Native behavior restored |
| --- | ---: | --- |
| 12D | 1 | Reset +F00 only inside the getter/action equality branch; JNE 004B11A5 skips both setter and reset to 004B11BD |
| 134 | 1 | The speed clamp is independent of the preceding positive-speed subtraction; 004B1708 enters clamp checks at 004B171C |
| 190/191/192/194/195, 19B/19C/19D/19E/19F | 30 | Decrement +F00 after the three-part firing guard, including when the guard fails |
| 1F8/1F9/1FA | 3 | Auxiliary action 8, motion initialization and break belong in the alpha<=30 `else`; successful fading continues the rest of the handler |
| 258/259 | 4 | Decrement +F00 inside stage>4, after the inner round/cooldown guard, including when that inner guard fails |
| 2C0/2C1/2C3 | 3 | Initial sprite emission belongs inside the getter/action equality branch |
| 2E5 | 1 | Randomize +516 only inside the getter/action equality branch |
| 2F9 | 2 | The two subsequent mode-gated seven-argument shots remain inside the outer frame-zero /stage9-or10 block |
| **Total** | **45** | **All original direct branch targets now agree** |

For the ten unconditional cooldown decrements, the native failed firing
guards target the five-instruction decrement, rather than the following
getter. In 258/259, the first stage guard still skips the decrement; only
the inner two tests target it. These are different original scopes and
remain expressed differently in source.

The 2F9 inner stage/frame checks are preserved exactly as observed. They
are not removed on an assumption that earlier native calls cannot change
the actor. Its two outer failed conditions now skip the full original
block to 004BEFB8, whole ordinal 21,307.

F1198's shared getter stays inside the switch, with exactly the original
four early 0/2/4/5 entries; the default still skips it. F1199's seventeen
strict x87 comparisons and nine random-angle immediate corrections remain
verified. No target byte arrays, assembly, padding, invented stack slots,
ABI changes or conditional source bodies were used.

## Full fresh selected-parent comparison

The unchanged
[F1028 verifier](../scripts/verify-third-fighter-whole-82kb-pe-targets-f1028.py)
cold-built only the tracked parent using pinned VC7.1:
`/Od /Ob0 /Gy /GR- /GX /GS /Zi /I src /I probes`.
The complete local audit then independently compared the fresh object:

| Original property | Fresh tracked result |
| --- | --- |
| Complete CODE length /x86 count | 82,796B /22,721, equal |
| Frame /saved-this | 0x720 /EBP-0x64, equal |
| Native EBP operand positions | All 7,432 agree |
| Mnemonics /resolved non-GPR operands | Zero differences |
| Direct branch target ordinals | **All 1,927 agree** |
| CODE field destinations | All 2,201 agree: 2,191 external +10 local |
| Dense switch destinations | All 151 native target ordinals agree |
| Owned afterRET DATA | 1,126B, including 522 unchanged sparse bytes |
| Remaining GPR /width debt | **6,958 positions /12 widths**, unchanged |

Exactly **48 candidate byte positions** change from F1199, all within the
45 repaired branch displacement fields. All 2,352 COFF field shapes,
addends and destinations remain unchanged; 45 generated local symbol
names change, retaining their original offsets. The ignored trial and
fresh tracked builds have identical entire CODE+DATA and COFF records.

Equal total CODE length does not prove equal instruction encodings: the
twelve width differences cancel in aggregate. Native PE destinations
matching at instruction ordinals also do not establish original physical
relocation offsets or whole byte equality. The first remaining GPR
divergence is **004ADEFA**, whole ordinal **2,180**: native loads EAX,
while source loads EDX from the same EBP-0x64 saved-this slot.

## Retained evidence and validation scope

Local `.analysis/f1200-82kb-native-cfg/` retains `before-inputs/`,
`before.obj`, `cfg-trial.obj`, `tracked.obj`, `native-branch-context.json`,
`source-changes.json`, before/trial/tracked complete audit JSONs,
`whole-audit.py`, `make-receipt.py`, `local-symbol-renames.json` and
`verified-summary.json` with recursive source/artifact SHA256 values.
Previous F1028 output is preserved in `f1028-before/`.

No accepted source or manifest input is affected, as recorded in
`accepted-input-scope.json`. The canonical ledgers, origins, accepted
R268/later evidence and comparison infrastructure are unchanged. All
original 82,796 pending CODE bytes remain in the denominator. Only this
parent was cold-built; no full CI, all-unit replay, origin retest or new
per-function test was needed. Continue the native GPR/width reconstruction
from the retained first divergence, using this corrected whole CFG parent.
