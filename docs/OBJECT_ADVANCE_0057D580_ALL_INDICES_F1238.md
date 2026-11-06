# F1238 — 45 states, all real indices and ESI recovery in 0057D580

Current continuation: [F1239 complete-parent audit](OBJECT_ADVANCE_0057D580_COMPLETE_PARENT_F1239.md)
writes all 70 states and restores the entire native frame/stack, but still
has 914 GPR /six width differences. The 45-state figures below are historical.

The existing [F1237 research source](OBJECT_ADVANCE_0057D580_INITIAL_PARENT_F1237.md)
now writes **45/70** real nondefault states of original 0057D580. Thirteen
new states add **9,596 native CODE B /2,583 x86**: 812, 816–817, 820–826,
830, 834 and905. The entire **43,845B original callable remains NONEXACT**
and uncredited. No interior becomes a separate acceptance unit.

## Real storage and register preservation

All seven previously missing loop indices are now used by their actual
native branches. Together with the eight F1237 indices they naturally restore
the original receiver at **EBP-0x40**. A separate raw comparison checks every
one of the **67 references to all fifteen named-index slots**, including each
instruction ordinal within its state, mnemonic, operand position, width and
displacement. All agree. The index check uses raw stack operands; GPR selection is recorded separately.
It does not claim equality of compiler temporaries or whole code.

| Native index slot | State |
| --- | --- |
| EBP-4 /-8 /-C | 800 /801 /802 |
| EBP-10 /-14 /-18 | 808 /812 /813 |
| EBP-1C /-20 /-24 /-28 | 816 /817 /818 /819 |
| EBP-2C /-30 /-34 /-38 /-3C | 822 /825 /830 /834 /843 |

The original's non-prologue/epilogue ESI instructions all belong to three
integer-expression groups in state905, with products held across RecordedRange
calls. Source
expressions `D8 * 300/270/240 + RecordedRange(0, 50)` naturally recover the
saved register and its PUSH/POP. No register annotation or artificial local
is introduced. 905 preserves signed difficulty <=1 /==2 /==3, separate spawn
limits, event packet6 and the post-frame counter/reset ordering.

## Native behavior recovered

812/816/817 preserve four independent directional boundary checks, one genuine
single-iteration index loop, owner parameter stores, distinct trail/effect
IDs, sound and immediate clear/return. Their native intervals differ only in
the two independently checked effect IDs. No loop is replaced with a crop.

822/825 preserve different parent actions, hit counts and phase limits. The
five-iteration burst keeps sound inside the loop and assigns `8 - index * 4`.
Their random scale arithmetic uses **DWORD 0.25 then QWORD 1.0**; 825 retains
three distinct effect/shake events and counter clears. 823/826 preserve their
different phase predicates, small 0.0025f growth and repeated 3.0f additions.
824 retains its true random rotation, scale growth and immediate fade exit.

830 preserves both native D8 initialization stores, then decrement/clamp and
counter-scaled polar speed. 834 retains its unusual phase38 threshold,
hit4 clearing policy, phase38 transition, fade/shrink and reset21. 820 emits
its random-position effect before first-frame initialization; no absent D8
initializer is added. 821 keeps both valid parent actions and its own offsets.

## Selected compiler observation and remaining work

| Property | Original | Selected incomplete C++ |
| --- | ---: | ---: |
| Complete callable CODE /x86 | 43,845 /11,694 | **28,476 /7,597** |
| Frame | 0x378 | **0x23C**, still wrong |
| Saved receiver /ESI | EBP-0x40 /yes | EBP-0x40 /yes |
| Written state intervals | 70 | 45, covering native 28,288B /7,548 x86 |
| Unwritten states | — | **25** |

Every written region retains the original instruction count, mnemonic sequence,
actual constants, fields, direct callees and diagnostic branch target shapes.
The shape diagnostic normalizes scratch GPRs and unfinished compiler stack
temporaries. Its prefix also normalizes the unfinished frame size and owned
table references. It is not byte-exact evidence. Raw GPR/EBP/width positions
agree throughout the written 800–830 intervals; later partial regions retain
raw differences. The complete native CFG, physical relocations and entire
owned DATA still require whole-function comparison after the remaining source
is written. All original bytes remain in the conservative pending denominator.

Continue with **831**, then 835–840/845/847 and the remaining late states.
The source diagnostic and `verified-summary.json` retain the exact 25-state
list. Preserve the full F1237 original CODE/DATA/constructor/vtable evidence
and all previous exact units, origins and research parents.

## Evidence and validation

`.analysis/f1238-object-57d580-loops/` retains immutable before/collision/
all-indices/esi-restored/descendants CPP/HPP, native constant/callee inputs,
three-loop native deltas, all four serial build logs/listings, source
diagnostics, `descendants-named-indices.json` and `verified-summary.json`.
Actual OBJ/PDB files are in `build/probes/f1238-object-57d580/`; private OBJ
symlinks point there. Selected stage: **descendants**.

CPP SHA256:
`9536885e7980aa058846b1323206a04cebd75cf17a6c8d0631505ff422f6bc53`.
OBJ SHA256:
`16c13715f4aa40baf272553a5d3c0b0bbb3498bfe26fdf180a7ae55a3cbc2936`.
Profile remains `/Od /Ob0 /Gy /GR- /GX- /GS /Zi /I src /I probes`.

The private diagnostic now identifies the source epilogue immediately after
the independently inspected default call, including POP ESI before MOV ESP.
Its earlier parser is retained as `diagnose-source-before-esi.py`. This changes
no canonical comparison or acceptance infrastructure. Pinned target/tracking,
read-only/no-analysis Ghidra, active handoff and whitespace checks pass.
No accepted input, header, origin or canonical ledger changes. Only this
research parent was compiled; no full CI, canonical cold replay, origin retest
or new test was needed or run. Complete zero-difference source and canonical
affected-unit cold replay remain necessary for acceptance.
