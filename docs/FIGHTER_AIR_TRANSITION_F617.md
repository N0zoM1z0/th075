# F617 — six genuine exact-GPR-role 0x5E fighter actions, and the unresolved 0x5D register phase

**Original pinned Japanese TH075 1.11 PE + ordinary VC7.1 source
compile, NOT a complete original giant function reconstruction.**
Executable SHA256:
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
F614 had reconstructed action0x58 inside all eleven huge fighter
`Advance()` C++ source probes. The next real physically distinct
handler intervals in the original second packed switch are
`0x5D` (dense original DWORD index **19**) and `0x5E` (index **20**),
followed by `0x5F` (index **21**). The skipped action IDs do not
create independent complete source functions or automatic accepted
CODE; the original after-RET packed DATA remains separately owned.

## Real original C++ air-transition behavior and source expression-order discovery

Seven original actors use a **101-instruction** common grammar for
both complete case interiors. In original `00564BE0` each physical
case has **430 CODE bytes** because 31 native receiver EBP−0x88
MOV loads widen by three bytes versus normal **337-byte** cases.
The real behavior is a stage-dependent float ground test, subtraction
of drag from `+0x54`, and an eventual contact reset to auxiliary
state. On frame completion it may switch to action 0/1 using the
original `+0x4E0` game counter, then compares the live fighter
horizontal position `+0x44` against the owner pointer `+0x2E8`
horizontal position to update signed direction byte `+0x66`.
The final per-fighter stage initializes actual float speed `+0x54`,
position `+0x50`, and friction `+0x5C`, and another original stage
selects a specific auxiliary state. **Actual values and even the
positive/negative position are actor- and case-dependent**, not a
single universal character parameter table. The source probes derive
each constant directly from each original PE case.

The first natural source used a nested direction comparison, but
independent original x86 decoding shows the `JNE` at native ordinal
62 jumps to **ordinal 65** (the next float comparison) rather than
past both direction tests. The correct source has **two independent
`if`s**. Another original VC7.1 register/x87-order constraint is a
natural member *lvalue* `*(&F32(0x44))`, which makes VC7.1 load the
owner pointer/target coordinate before the member float and retains
the original first/second FCOMP + `TEST AH` roles. No assembly,
artificial saved frame slots or machine-code patch was used.

Tracked reusable natural C++:
[`FighterAirTransitionCaseF617.inc`](../probes/FighterAirTransitionCaseF617.inc).
It generates a separate normal `case 0x5D` and `case 0x5E` with
**different original constants for each**, in the same original
fighter-parent whole C++ TU.

## Do not silently claim both 0x5D and 0x5E are exact

The original whole 101-instruction `0x5E` case is now strictly
**GPR/x87/CFG role identical** to ordinary VC7.1 C++ in six selected
actor owners. Its 8 real physical typed `DIR32/REL32` original
source COFF fields include both float comparisons against global
`0065782C`, game reset `00453E20`, aux `0040FB40`, frame getter
`0040FA30` and native action `0040FAC0`; each original symbol,
relocation operand, actual PE target and zero addend are checked.

However, the preceding `0x5D` in each of these exact same freshly
compiled whole C++ sources **still differs in 61 native register
and CFG operand roles**, even though its natural source emits the
correct 101 x86 instruction count and widths and eight true typed
fields. All seven original 101-case actors were rechecked. The
seventh actor `00543210` has a genuine different register phase
for **both 0x5D and 0x5E**, leaving **61 original role differences
in each**. This negative case has its own explicit reproducible
verification option; it is NOT omitted to inflate strict-match
statistics. Four further giant fighters use genuinely different
**64, 94, 96 or 106-x86** native 0x5D/0x5E case families that
must not be substituted by the 101-instruction grammar.

| Enclosing original fighter, entire giant still NONEXACT | Native full original `0x5E` interior | Real x86 roles | True typed PE/COFF fields | Status of original `0x5D` |
| --- | ---: | ---: | ---: | --- |
| `0045DD70` | **337 B** | 101/101 | 8 | 61 GPR/CFG mismatches |
| `005D73C0` | **337 B** | 101/101 | 8 | 61 GPR/CFG mismatches |
| `00486550` | **337 B** | 101/101 | 8 | 61 GPR/CFG mismatches |
| `004AC040` | **337 B** | 101/101 | 8 | 61 GPR/CFG mismatches |
| `00564BE0` | **430 B** | 101/101, real wide EBP | 8 | 61 GPR/CFG mismatches |
| `005214B0` | **337 B** | 101/101 | 8 | 61 GPR/CFG mismatches |
| **F617 strict source-backed six 0x5E interiors** | **2,115 native inner CODE B** | **606** | **48** | No 0x5D accepted |
| `00543210` **negative** | 337 B | **61 operand-role mismatches** | 8 structurally | Also 61 GPR mismatches |

## Selected original native PE verification

[`verify-fighter-air-transition-f617.py`](../scripts/verify-fighter-air-transition-f617.py)
first rereads *all three* actual native physical packed handler
DWORDs for 0x5D/0x5E/0x5F, separately checks complete original
`0x5D/0x5E` 101-x86 boundaries/byte geometry, real stage constants
and eight PE/COFF call/global targets per case. It then freshly
compiles only the selected original whole giant with pinned MSVC VC7.1
`/Od /Ob0 /Gy /GR- /GX- /GS /Zi`. On that **same object**, it
repeats the complete F614 strict original role/COFF verification of
**all 30 previously reconstructed authentic fighter cases** and
all physical after-RET packed jump DATA. It **requires 61 wrong
roles for 0x5D** and zero wrong roles for normal positive 0x5E,
not ignoring those source-original differences by relocation masking.
Native `00564BE0` requires 31 physical widened EBP receiver loads,
never synthetic stack padding.

The result adds only **six strict case subranges** to the cumulative
original fighter *internal* study, taking F598–F614's 330 strict
case bodies/84,787 CODE bytes to **336 strict interior action bodies
/86,902 native inner CODE bytes**. This is **not** 336 newly
accepted complete original functions. The 0x5D and seventh 0x5E
role failures remain openly documented. All eleven parent giants
and the other original giant/small authors' functions remain
NONEXACT. Official 943 whole authored exact functions /862,726
original CODE bytes are unchanged; no all-unit cold replay or
external Oracle acceptance.

## Reproduce a single affected giant, or the real negative

```bash
scripts/repo-python scripts/verify-fighter-air-transition-f617.py --boss 0x0045DD70
scripts/repo-python scripts/verify-fighter-air-transition-f617.py --boss 0x00564BE0
scripts/repo-python scripts/verify-fighter-air-transition-f617.py --negative-actor
# Optional ONLY the six newly affected original giant source TUs:
scripts/repo-python scripts/verify-fighter-air-transition-f617.py
scripts/repo-python scripts/validate-tracking.py --require-target
```

Selected actual original C++ source, VC7.1 COFF/PDB, typed PE target
and complete source GPR/CFG negative receipts remain under ignored
`.analysis/f617-fighter-air-source/`. Prior independent compiler
expression alternatives are preserved in `.analysis/f617-air-transition/`.
