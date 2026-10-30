# F832 — Actor-specific D1/D2 resource shots in one growing 46KB fighter

The pinned original Japanese TH075 1.11 fighter at 005214B0
contains 46,755 callable native CODE B/13,230 x86, plus
901 separate afterRET packed-switch DATA B. F831 had restored
the actual 0xCF falling-state source followed by original
0xD0 reflected landing, with the full source still nonexact.

F832 adds both later original action states D1 and D2
in ONE freshly compiled entire VC7.1 parent:

| Real original game action | Complete original interior | Physical PE/COFF fields |
| --- | --- | ---: |
| D1 | **199 B /59 x86** | **8** |
| D2 | **251 B /74 x86** | **10** |

The game source uses actual +0x3B0 signed short resource
gate and its native decrement of **six**, original
+0x62/+0x64 stage/frame, projectile kind 0x3E6
and genuine +0x4F4 unsigned resource gate.
Unlike the earlier F651/F652 source used by a
different fighter, actual D2 first multiplies
horizontal/vertical speed by native 00657F74
and calls PrepareActionAt453D60(0x2C)
**before** emitting the original projectile
using SpawnWithFloatAt453A70(0x3E6,...).
The source also preserves the real original
unconditional vertical drag and next-state
transitions. All behavior is ordinary C++,
without artificial registers or added stack locals.

## Independent physical evidence and scope

The tracked verifier first regenerates and PE-verifies
the immediate prior F831 source, then recompiles
the whole affected C++ parent. Emitted callable
source grows **17,955 to 18,375 B** and
x86 grows **4,788 to 4,917**.

The actual original D1 and D2 entire case
mnemonics, instruction widths and relative
positions match the new source:
59/59 and 74/74 native x86. All **18
physically original PE fields**, their
positions, relocation types, zero addends,
compiler symbols and actual call/global
destinations are independently checked.

**An earlier cross-actor assumption was wrong:**
the former F651 D2 relocation ordinals correspond
to a *post-spawn* speed-scaling case.
Although that other action has the same 251B/74-x86
geometry, its PE fields are in a different order.
F832 instead establishes the original selected
actor's correct D2 physical references at
x86 ordinals 6,23,28,33,40,48,51,57,68,72.
The independent original PE disassembly was used
to verify the actual typed target of each field;
source COFF fields were never blindly masked as
native destinations from another fighter.

This longer whole parent remains *not* machine exact.
Actual nonrelocation byte differences remain
**32 in D1 and 46 in D2**, including real
GPR/stack register choices and original
enclosing-giant final JMP operands.
The source/native 0xCF and 0xD0 cases
remain complete original-size with true PE
fields but their 20 and 39 nonrelocation
byte negatives still apply.
The common 46B/16-x86 original default/getter
has its original saved-this EBP-0x10 and three
real REL32 calls, while four actual original
GPR operand bytes still differ.

Run only the affected whole original-shaped parent:

    scripts/repo-python scripts/verify-scripted-fighter-resource-shots-f832.py

Generated entire C++, COFF/PDB and original physical
PE comparison receipts remain in ignored
.analysis/f832-scripted-resource-shots/.
**Original 46,755B giant remains NONEXACT,
zero independent case/whole callable exact CODE,
no accepted-unit corpus cold replay.**
