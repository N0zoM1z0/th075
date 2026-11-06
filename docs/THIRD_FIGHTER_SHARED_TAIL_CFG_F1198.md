# F1198 — restore 004AC040's shared getter and default exit

The complete normal C++ parent in
[`FighterWhole004AC040F1020.cpp`](../probes/FighterWhole004AC040F1020.cpp)
now reaches the native shared getter from actions 0/2/4/5 and skips that
getter after the default handler. This repairs five genuine control-flow
differences. The whole original remains **NONEXACT**, with no accepted
CODE credit or ownership changes.

The supplied Japanese target is unchanged:
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
The comparison covers the complete original 82,796 CODE bytes /22,721 x86
instructions and all 1,126 owned afterRET DATA bytes. This continues the
complete F1020 source; it does not restart the historical F938 marker draft.
Stale source-header claims about missing cases/frame have been corrected.

## Native observations and source correction

| Original branch site | Original destination | Previous source destination | Corrected source |
| --- | --- | --- | --- |
| 004AC268, action 0 | 004C039F, shared getter | Epilogue, skipping getter | Jump to shared getter |
| 004AC3F0, action 2 | 004C039F | Epilogue | Jump to shared getter |
| 004AC4D3, action 4 | 004C039F | Epilogue | Jump to shared getter |
| 004AC4E2, action 5 | 004C039F | Epilogue | Jump to shared getter |
| 004C0391, default JNE | 004C039D, skip getter | 004C039F, extra getter call | Skip getter |

The early branches target whole instruction ordinal 22,715, rather than
epilogue ordinal 22,717. The default conditional targets ordinal 22,714,
whose jump skips the shared call. Its first getter/comparison and conditional
setter remain present. The epilogue begins at 004C03A7.

The natural source uses four explicit `goto` statements to a single label
inside the switch, after the default handler's `break`. The default's old
`else GetNativeActionAt40FA30()` was removed. The shared body is
[`FighterThirdSharedGetter004AC040F1198.inc`](../probes/FighterThirdSharedGetter004AC040F1198.inc).
No target bytes, padding, assembly, false ABI or conditional source body
was introduced.

## Fresh whole-parent evidence

The unchanged
[`verify-third-fighter-whole-82kb-pe-targets-f1028.py`](../scripts/verify-third-fighter-whole-82kb-pe-targets-f1028.py)
cold-built only this parent with its existing pinned VC7.1 profile:
`/Od /Ob0 /Gy /GR- /GX /GS /Zi /I src /I probes`.
Its original PE destination/DATA checks pass. This is research evidence,
not canonical whole-function acceptance.

The additional local whole audit checks every instruction, ordinary branch
destination, non-GPR operand, EBP operand, CODE field and owned table:

| Complete-function observation | Fresh source result |
| --- | --- |
| CODE length /instruction count | 82,796B /22,721, equal to original |
| Frame /saved-this | 0x720 /EBP-0x64, equal |
| Native EBP operand positions | All 7,432 agree |
| Mnemonics | All agree |
| Direct branches audited | 1,927; incorrect targets reduced from 50 to **45** |
| Non-GPR operand differences | **26**, unchanged |
| GPR-role differences | **6,958**, unchanged |
| Instruction-width differences | **12**, unchanged |
| CODE fields | All 2,201 native destinations agree: 2,191 external +10 local |
| Dense table destinations | All 151 native instruction ordinals agree |
| Sparse DATA | All 522 nonfield bytes agree |

Equal total CODE length does not imply equal per-instruction widths:
the twelve width differences cancel in aggregate. Neither original relocation
offset equality nor callable byte equality follows from the PE target checks.

Comparing the selected baseline and final candidate confines all **five
changed byte positions** to the five repaired direct-branch displacement
fields. All 2,352 COFF field shapes, addends and destinations remain unchanged;
160 compiler-generated local symbol names change, with their offsets unchanged.
The trial and tracked builds have identical complete CODE+DATA and COFF records.

An initial diagnostic used `/GX-`; a fresh baseline with the actual selected
`/GX` profile was built before adoption. Their complete CODE+DATA and COFF
records agree. Final evidence and the unchanged F1028 verifier use `/GX`.

## Retained evidence and next work

Local evidence is preserved under `.analysis/f1198-82kb-whole-cfg/`:

- `before.cpp`, `before-GX.obj`, `tracked.obj`, and both whole-audit JSONs;
- `whole-audit.py`, `make-receipt.py`, and `verified-summary.json`, including
  recursive source-input and artifact SHA256 values;
- `profile-check.json`, `local-symbol-renames.json`, and the complete earlier
  F1028 output snapshot in `f1028-before/`;
- `native-action-differences.json` attributes the original 50 branch and
  26 operand differences; `remaining-native-actions.json` retains the current
  **45 branch /26 operand** rows with native instruction addresses and actions;
- `accepted-input-scope.json` records no affected canonical accepted unit.

Remaining branch differences are in 12D, 134, 190/191/192/194/195,
19B–19F, 1F8–1FA, 258/259, 2C0/2C1/2C3, 2E5 and 2F9. The operand debt
includes seventeen x87 comparison masks and nine random-range subtraction
immediates. Read the native FPU operand order and full guard scopes before
changing source; matching mnemonic counts alone previously missed these.

No accepted source, exact manifest, origin decision or comparison infrastructure
changed. No all-unit replay, full CI or additional per-function tests were run.
Canonical exact totals stay at 982 units /871,649 original authored CODE bytes.
