# F1199 — restore all 26 outstanding 004AC040 non-GPR operands

The complete live
[`F1020 parent`](../probes/FighterWhole004AC040F1020.cpp) now agrees with
every original non-GPR operand after resolving actual PE destinations.
Seventeen strict comparisons and nine random-angle subtraction constants
were incorrect. Only their 26 candidate immediate bytes change; the whole
function remains **NONEXACT** with 45 direct branch-target differences,
6,958 GPR-role differences and twelve width differences.

## Native evidence and natural source changes

The pinned original is the same user-supplied Japanese executable, SHA256
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
Each comparison was reread with its preceding FLD/FADD/FCOMP sequence and
following branch. The source preserves the actual arithmetic and changes
the comparison's inclusion of equality.

| Action | Original comparison/mask sites | Source correction |
| --- | --- | --- |
| 61 | 004AE722, TEST AH,5 /JP | Vertical velocity +Y `<` threshold; 60's existing `<=` is preserved |
| 2BE /2BF | 004BB238 /004BB87F, TEST AH,41h /JNE | Y `>` threshold |
| 2E6 | 004BD4B3, TEST AH,41h /JNE | Y `>` threshold |
| 2EF | 004BDB84 /004BDBB5, TEST AH,41h /JNE | Both Y guards use `>` |
| 2F0 | 004BE439 /004BE46A, TEST AH,41h /JNE | Both Y guards use `>` |
| 2FA | 004BF1DE /004BF36E, TEST AH,41h /JNE or JE | Y and right-side X guards use `>` |
| 2FB | 004BF8F3, TEST AH,41h /JNE | Right-side X guard uses `>` |
| 302 | 004BFA12 /004BFA37 /004BFA60 | Two Y guards use `>`; velocity clamp uses `<` (TEST AH,5 /JP) |
| 303 | 004BFE32 /004BFE57 /004BFE80 | Two Y guards use `>`; velocity clamp uses `<` (TEST AH,5 /JP) |

These are direct native observations: the loaded member/sum is compared
against the existing global. With this operand order, TEST AH,41h /JNE
skips less/equal/unordered; TEST AH,5 /JP skips greater/equal/unordered.
The 2FA JE takes the successful right-bound alternative instead.

The paired arc source also had its angle subtraction constants copied
incorrectly. Original 2EF keeps `Rand(0,100)-70` at stage 15 and uses
`-50` at stages 17/19/21/23. Original 2F0 uses `-70` at all five stages.
The nine repaired original SUB sites are:

- 2EF: 004BDE77, 004BDFCE, 004BE125, 004BE27C (50).
- 2F0: 004BE5D5, 004BE72C, 004BE883, 004BE9DA, 004BEB31 (70).

The target's actual helper arguments and return transport remain unchanged.
No assembly, target byte arrays, padding, fake locals or source split is used.

## Complete fresh build and retained evidence

Only the live parent was cold-built with the existing pinned VC7.1 profile
`/Od /Ob0 /Gy /GR- /GX /GS /Zi /I src /I probes` using the unchanged
[F1028 research verifier](../scripts/verify-third-fighter-whole-82kb-pe-targets-f1028.py).
The additional complete-function diagnostic confirms:

- 82,796 CODE bytes /22,721 x86; frame 0x720, saved-this EBP-0x64 and
  all 7,432 native EBP positions agree.
- All mnemonics and resolved non-GPR operands agree. All 2,201 CODE
  destinations, 151 dense target ordinals and 522 sparse DATA bytes agree.
- All 2,352 physical COFF records are identical before/after. The trial
  and tracked builds have identical complete CODE+DATA and COFF records.
- Exactly 26 candidate byte positions change, confined to the seventeen
  TEST masks and nine SUB immediate fields. Every branch/GPR/width debt
  row is unchanged, including all 45 outstanding branch-target differences.

Local evidence is under `.analysis/f1199-82kb-native-operands/`:
`before-inputs/`, `before.obj`, `operand-trial.obj`, `tracked.obj`,
`native-operand-context.json`, `source-changes.json`, complete before/trial/
tracked whole-audit JSONs, `whole-audit.py`, `make-receipt.py`, and
`verified-summary.json` with recursive source/artifact SHA256 values.
The previous F1028 output is retained in `f1028-before/`.
`accepted-input-scope.json` records no canonical accepted input affected;
other includers are historical nonexact research parents.

This is bounded whole-parent reconstruction evidence, not canonical exact
acceptance. All original bytes remain in the pending denominator; the
982-unit /871,649-byte accepted total and 95 unknown origins are unchanged.
No comparison infrastructure, full CI, all-unit replay or per-function tests
were added. Continue the 45 original branch differences listed in F1198's
`remaining-native-actions.json` before concentrating on GPR roles.
