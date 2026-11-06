# F1147 — Original 3E3/3E4 stage speed, shared hit and return paths

This corrects seven native direct branch targets inside the ONE NONEXACT
`0050A580` whole function. The original Japanese PE is authoritative;
the earlier F1132 mnemonic-based cooldown interpretation was incorrect.

| Case / local branch ordinal | Original destination | Previous C++ destination | Recovered source behavior |
| --- | ---: | ---: | --- |
| 3E3 /43 | 70 | 55 | Polar speed update is inside stage zero |
| 3E3 /163 | 173 | 177 | Both hit-counter and score outcomes call `0045B860(0x2E)` and return |
| 3E4 /43 | 70 | 55 | Polar speed update is inside stage zero |
| 3E4 /179 | 188 | 189 | Positive cooldown returns after either its subtract-five or clear-and-fill path |
| 3E4 /204 | 237 | 238 | Incrementing meter returns before motion |
| 3E4 /214 | 237 | 238 | A set +0x39C flag also returns before motion |
| 3E4 /232 | 237 | 238 | Float +0x36C increment shares the terminal hit return |

The original cooldown subtract branch is `0051DE6E -> 0051DEA6`,
where the latter is the shared whole-function exit jump. It does NOT
continue into the meter policy at `0051DEAB`. The source now places
the return after the complete positive-cooldown if/else. The meter
policy remains subsequent source, reachable only for nonpositive cooldown.

Case 3E3 now emits 985B/200 x86 and 3E4 emits 1,335B/261 x86,
equal to their original interior lengths. All respective mnemonic,
GPR-role and instruction-width positions match, with 17/19 original
physical external PE fields and 31/38 scalar immediate positions.
These are interior observations, not two accepted original callables.

The live one-parent verifier cold-build passed: all 17,435 ordered
whole mnemonics, 1,834 direct branch destinations, 82 strict interiors,
1,246 physical PE fields and 2,964 scalar positions remain checked.
Remaining known branch-target debt decreased from 12 to 5, confined
to 35D, 35E and 391. Correct long JNEs add eight bytes to the candidate:
81,568B against 81,539B original CODE. Original frame, stack slots,
eight provisional GPR interiors and 391 x87 fields remain unresolved.
The 979 accepted whole functions /868,243 CODE bytes are unchanged.

Reproduce only the affected parent:

    scripts/repo-python scripts/verify-characterobject-current-recovered-f1068.py

Previous source, selected before-COFF and receipts, full native before/after
disassembly and an intermediate rejected shared-return-only diagnostic
are retained under ignored `.analysis/f1147-native-hit-cfg/`.
