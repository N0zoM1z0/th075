# F1081 — Real action 0x349, native parent-X DWORD copy and parent-Y-first x87

The SHA-pinned Japanese TH075 1.11 original includes **one**
`CharacterObject::Advance` at `0050A580`, original **81,539
CODE B /17,435 x86** and separate 567 afterRET sparse-switch
DATA B. The current C++ source is a still-NONEXACT partial
original-shaped whole parent; no inner switch case is a standalone
exact original callable.

Native action `0x349` occupies **00512815..005129C1, 428 original
CODE B /94 x86**. F1081 removes its synthetic marker and restores
real gameplay: stage/frame-zero `0040FBB0` and scale/opacity/status
initialisation; actor+0x44 takes a **bit-preserving 32-bit DWORD
copy of the parent X** (native MOV, no FLD/FSTP); actor+0x48
receives actual parent Y plus original global `00658268`;
actor+0x30 subtracts native `00657874`. Stage 1 has the genuine
repeated parent-action `0x2BE` comparisons and parent's animation
stage threshold 8 leading to real `0040FB40(2)`; later stages
fade unsigned opacity by 25 or expire through native `0045B830`,
followed by genuine `0040FA30` completion.

## Actual original x87 relocation, not merely correct arithmetic

An initial ordinary full-parent VC7.1 source used
`F1037_POSITION(PARENT).yPosition + global`, generating original
**94/94 mnemonics** but loading **the global first**: `FLD
[00658268]; FADD [parent+0x48]`. The original PE instead has at
native x86 ordinal **36** `FLD [parent+0x48]` and ordinal **37**
`FADD [00658268]`. The source's DIR32 global relocation was
therefore physically in the wrong original instruction, and GPR
role matching was only **92/94**.

F1081 compiled **twelve genuinely used C++ parent-Y expression
grammars in the entire current switch-parent C++**, not a cropped
state. The natural explicit borrowed **`*(&F1037_POSITION(PARENT).yPosition)`**
restores the original field-first `FLD`/global `FADD` operand order,
without invented storage, forced x86 registers, byte patching or
reordering game effects. Native PE physical field verification then
became **7/7 original external call/global sites**, including both
original Y and angle globals at ordinals 37/42.

| Verified actual original `0x349` | Result |
| --- | ---: |
| Native original CODE and x86 | **428 B /94** |
| Selected C++ emitted case CODE and x86 | **338 B /94** |
| Original mnemonic sequence | **94/94** |
| Original GPR register roles | **94/94** |
| Original instruction width matches | 64/94 |
| Actual original PE physical call/global fields | **7/7** |
| Original Y global at native opcode 37 | **correct** |
| Bit-preserving parent X MOV | **correct** |

The tracked live one-parent verifier
`scripts/verify-characterobject-current-recovered-f1068.py`
now freshly compiles only the affected whole partial C++ parent,
independently checks the original **81,539B CODE SHA**, original
92 DIR32 label-equality partitions, literal 199 sparse DATA,
**40 real original state interiors** covering **33,641 native
CODE B /7,326 original x86**, **7,326/7,326 native ordered
mnemonics and GPR positions**, **589/589 genuine original physical
PE external fields** and **1,363 non-relocated scalar immediate
positions**. The incomplete selected source emits **27,780
CODE B /7,474 x86** and original sparse DATA; the authentic
complete game remains **81,539 B /17,435 x86**, with many marker
states and different original `ESP 0x3A0`, `EBP-0xAC` receiver,
branch/stack widths. **No whole original function or new original
CODE bytes are exact** from this change.

Reproduce only this one parent:

    scripts/repo-python scripts/verify-characterobject-current-recovered-f1068.py

Full original PE, the twelve normal C++/COFF/PDB/compiler grammar
controls and the rejected wrong-x87 first source are retained under
ignored `.analysis/f1081-native349/` and current
`.analysis/f1068-boss-live-all-native/`. No all-979 replay.
