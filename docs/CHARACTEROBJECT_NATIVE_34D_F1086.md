# F1086 — Real original 0x34D, 1,171B/253 native x86 and eight 0x361 projectile shots

**Historical F1086 checkpoint:** current parent now restores authentic [F1087 0x34E](CHARACTEROBJECT_NATIVE_34E_F1087.md). Earlier 44-state/30,435B partial-source dimensions are historical; native F1086 34D PE evidence remains verified.

Pinned Japanese TH075 1.11 has one independently authored original
`CharacterObject::Advance` callable at `0050A580`, **81,539 original
CODE B /17,435 x86** with 567 separately owned afterRET switch DATA.
F1086 restores another genuine original switch *interior*, native
`0x34D` at **00513235..005136C8**, **1,171 original CODE B /253
x86**, rather than an independent exact callable. The current
original-shaped parent remains NONEXACT overall.

The original `0x34D` shares much real gameplay with `0x34C` but has
separate physical COFF call/global locations, frame scratch slots,
parent-action cases, projectile ID and code ordering. It resets
normal scale, opacity and native motion on stage/frame zero; sends
real signed parent+0xF0C and own +0xD8 to `0040FB70`; advances real
parent-relative X/Y using originals `0065989C`, `00657F74`,
`0065835C`; checks signed fighter/target health and native frame
status; then advances the signed timer up to 140 in steps of 5.
The x87 source borrows the actual actor velocity+0x54 lvalue, so
native ordinal 60 is `FLD [actor+0x54]`, ordinal 61 is `FMUL
[00657F74]`, not the wrong reverse global-first variant.

Distinct original conditions trigger eight real `0x361` shots when
parent state is `(0x191,4)` or `(0x25C,6)`, rather than original
`0x34C`'s wider `0x190/0x258/0x259/0x25A` set and `0x360` objects.
The original **eight-iteration C++ loop** writes a real 45°-step
parent+0x314 float trajectory and invokes actual parent `00453A70`
with `0x361`, actor X/Y and native signed facing. The selected
source preserves the actual order of native alpha fade, stage-1
`(0x2C1,3)` transition/early return, action getter/expiry and
stage-2 parent+0x36C vertical adjustment/parent action `00453D40`.
This exact ordering is different from `0x34C` even though gameplay
branches can appear semantically similar. No fake stack locals,
assembler, invented gameplay, binary grafting or fixed GPR hints.

The selected real C++ was compiled **inside the entire one-switch
partial parent** with pinned ordinary VC7.1 profile, and the real
independent Japanese PE was SHA-checked for the whole 81KB. Its
entire original `0x34D` 253-x86 action and every actual physical
nonlocal source COFF field were checked against native original
instruction ordinal, original PE field-byte position, REL32/DIR32
kind, original PE-calculated target and actual symbol destination.

| Original 0x34D evidence | Measured |
| --- | ---: |
| Actual original native CODE/x86 | **1,171B /253** |
| Selected C++ inner CODE/x86 | **965B /253** |
| Original mnemonic sequence | **253/253** |
| Original GPR roles | **253/253** |
| Original matching instruction widths | 185/253 |
| Authentic physical PE external call/global fields | **18/18** |
| Real loop multiplication / projectile | **45° / `0x361`**, verified |

The live `verify-characterobject-current-recovered-f1068.py` now
freshly compiles **only the one affected partial C++ parent**, reads
the original complete 81KB PE plus all 92 native jump-label
DIR32 partitions and 199 sparse literal bytes, and checks **44
original native game-state interiors**, **36,976 original game CODE B
/8,039 native x86**, **8,039/8,039 mnemonic and GPR positions**, and
**638/638 physical original PE nonlocal fields**, plus
**1,496/1,496 original nonrelocated scalar-immediate positions**.
Current incomplete C++ emits **30,435 CODE B /8,179 x86**, 567
original-shaped DATA and saved receiver EBP-0x68 / `ESP 0x1A4`,
versus original **81,539B/17,435 x86**, EBP-0xAC / `ESP 0x3A0`.
Remaining authentic game cases, original width and branch/stack
geometry are still unresolved. **Whole original callable NONEXACT;
newly accepted entire GAME CODE = 0B.**

Reproduce only this changed entire parent:

    scripts/repo-python scripts/verify-characterobject-current-recovered-f1068.py

The initial game source, normal VC7.1 COFF/PDB/compiler logs and
independent actual original PE evidence are under ignored
`.analysis/f1086-native34d/` and `.analysis/f1068-boss-live-all-native/`.
No all-979 exact function replay or original EXE mutation.
