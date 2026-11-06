# F1205 — resume the complete 33KB 004EBDA0 source with 133 GPR differences

The existing complete F572–F596 source
[`CharacterObjectActionsF572.cpp`](../probes/CharacterObjectActionsF572.cpp)
is retained unchanged and freshly compared with the entire original callable.
It already contains every native action and the actual default; do not restart
the F569 marker skeleton. The original R048-authored **004EBDA0 remains
NONEXACT**, with 137 differing nonfield bytes at 133 GPR instruction positions.
This is a live whole-function work item, not newly accepted original CODE.

## Entire original and selected source

The user-supplied Japanese executable remains pinned to SHA256
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
Its complete 33,293B CODE hash is
`3792bb8be898d5cfb88eca158243e138d8e24d0663829468f05c56694d695807`.
The original separately owned 438B DATA hash is
`27938f97b56b6f35d98a9dc0c93cb943ed3bb7a7eaa92b069f82e27355fe6086`.

The existing read-only, analysis-disabled Ghidra query independently reports
the function body at 004EBDA0..004F3FAC, exactly 33,293 addresses. Its inferred
database calling convention remains unknown; it is not used as ABI proof.
The native ECX save and plain RET support the borrowed no-argument thiscall
source view. No database names, types or boundaries are written.

Only this complete source was cold-built with the existing pinned VC7.1
profile: `/Od /Ob0 /Gy /GR- /GX- /GS /Zi /I src /I probes`.
Do not inherit the separate 82KB parent's `/GX` profile.

| Complete original property | Fresh selected source |
| --- | --- |
| CODE length /x86 count | 33,293B /8,789; every instruction offset and width agrees |
| Frame /saved-this | 0x1FC /EBP-0x40, equal |
| Native EBP operand positions | All 3,005 agree |
| Mnemonics /non-GPR operands | Zero differences |
| Direct branch targets | All 885 native instruction ordinals agree |
| Physical CODE fields | All 622 native positions and destinations agree |
| afterRET dense targets | All 60 original instruction ordinals agree |
| Sparse index bytes | All 198 agree |
| Complete COFF fields | 682, with zero addends and 132 consistent source-symbol bindings |
| Remaining GPR /width differences | **133 /0** |

Unlike the 82KB/58KB/46KB parents, this source currently has no instruction
width debt: every field occupies the same original physical offset. After
resolving all 682 actual fields, a full 33,731B CODE+DATA comparison leaves
exactly **137 different bytes**, all outside relocation fields. The other
30,866 of 31,003 nonfield bytes agree. This remains a failed whole-function
comparison, not structural-only acceptance or partial byte credit.

## Precisely bounded remaining native contexts

The starts are independently read from the original dense/sparse switch data.
Every current GPR difference belongs to one of these physical intervals:

| Action | Native extent | Original CODE /x86 | Wrong GPR positions | First difference |
| --- | --- | --- | ---: | --- |
| 38D | 004F32ED..004F3526 | 570B /155 | 45 | 004F344C, whole ordinal 8,076 /case ordinal 91 |
| 38E | 004F3527..004F3682 | 348B /87 | 64 | 004F3527, case ordinal 0 |
| 3E3 | 004F3683..004F39AE | 812B /200 | 24 | 004F3683; every difference is within the first 31 instructions |

The first 8,076 native/source instructions agree in register roles. At
004F344C, the native loads EAX from EBP-0x40 while the source loads ECX.
This follows 38D's two real float scale additions, whose own instructions
still agree. All later non-GPR, stack, branch and reference observations
remain independently checked across the complete function.

Historical [F593](CHARACTEROBJECT_WHOLE_GEOMETRY_F593.md) and
[F596](CHARACTEROBJECT_NATIVE_COLLISION_ORDER_F596.md) are retained.
F596 already fixed three genuine MOV/FLD order differences; those are not
current debt. F594's 23 scalar-expression negatives were inspected rather
than rerun. The new cold evidence supports the old 137-byte residual and
adds a complete native EBP/direct-CFG/dense-ordinal audit.

## Six bounded complete-parent controls

| New meaningful source/profile candidate | Complete observed outcome | Decision |
| --- | --- | --- |
| Eight-byte two-float scale view in 38D/38E | 138 GPR /six width differences; reverses three x87 member/global operand orders and invalidates three field geometries | Reject |
| Same scale view with explicit addressed member lvalues | All CODE+DATA bytes identical to selected source; 133 GPR remain | No adoption |
| Existing four-byte stage/frame window in 38D/38E/3E3 | All CODE+DATA bytes identical; 133 GPR remain | No adoption |
| `/G5` tuning | All CODE+DATA and COFF records identical; 133 GPR remain | No profile change |
| Commuted growth with addressed member operands | 137 GPR /four width differences; two reversed x87 operand pairs and invalid field geometries | Reject |
| Stage-minus-four zero guard | Same GPR/width debt, but replaces one original CMP with SUB | Reject |

Both borrowed views use actual contiguous, native-observed fields; no owner
is instantiated, and no padding, dummy local, fake return, assembly or target
byte array is introduced. The addressed scale form restores the original
member-first x87 operand order but does not fix the following register phase.
The header-induced compiler-local symbol renaming does not change field
offsets, addends or destinations in the byte-preserving controls.

## Retained evidence and handoff

`.analysis/f1205-object-4ebda0-recovery/` preserves `before.cpp`, the fresh
selected **`before.obj`**, full native disassembly/fingerprint, Ghidra query,
six trial sources/objects/compiler logs, all whole-audit JSONs,
`remaining-native-GPR-contexts.json`, `complete-native-field-bindings.json`,
`whole-audit.py`, `make-receipt.py` and `verified-summary.json` with source
and artifact SHA256 values. The fresh source is byte-identical to the
tracked F596 source. No archived object was substituted for the cold build.

This selected source and new whole-object evidence should stay in the active
cohort. Continue the 38D join and subsequent 38E/3E3 register context from
the actual complete source; preserve all previously verified native cases.
No canonical accepted input, origin, source/match ledger or comparison
infrastructure changes. All 33,293 original CODE bytes stay pending in the
conservative denominator. No full CI, all-unit replay, historical origin
retest or new per-function test is required or run.
