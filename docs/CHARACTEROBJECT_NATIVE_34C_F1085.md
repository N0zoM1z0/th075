# F1085 — Original 1,266B action 0x34C, eight real 0x360 shots and actor-first velocity x87

**Historical F1085 source checkpoint:** restoring authentic [F1086 0x34D](CHARACTEROBJECT_NATIVE_34D_F1086.md) has since expanded the live parent to 44 cases. Earlier 43-case/29,479B numbers below describe that source state; original 34C 18/18 PE fields remain verified.

Pinned Japanese TH075 v1.11 has **one** original authored
`CharacterObject::Advance` at `0050A580`: **81,539 original
CODE B /17,435 native x86**, followed by **567 independent afterRET
jump/sparse DATA B**. F1085 reconstructs real game state `0x34C`
inside the still incomplete natural C++ parent. It is an original
*interior*, not another accepted independently callable game function.

Original 0x34C is physically `00512D43..00513235`, **1,266 original
CODE B /273 native x86**. Its actual C++ gameplay resets motion,
alpha, 1.0f scale and active status at stage/frame zero while retaining
the native special +0xD8 timer 140. Each frame it sends genuine
`0040FB70` a real parent+0xF0C signed WORD, scaled original actor+0xC8
and actual +0xD8 timer; computes actor X/Y from parent position and
native velocity using original constants **0065989C, 00657F74,
0065835C**; advances the stage timer in steps of 5 up to 140; and
tests the **actual parent/grandparent signed +0x324 health** and
parent +0x3A0 status, not a guessed target pointer.

The native action then distinguishes real parent action/state combinations
`0x2C1/2`, `0x190/4`, `0x258/7`, `0x259/7`, `0x25A/3`.
A genuine **eight-iteration original C++ loop** writes parent
+0x314 a real trajectory angle `float(shot*45)` and invokes
parent `00453A70` with projectile ID **0x360** and the actual actor
X/Y and parent signed facing. It performs authentic native
`0040FB40`/`00453D40` transitions, stage-dependent alpha fade by
10, `0040FA30` completion, and stage 2/frame 0 parent +0x36C
vertical adjustment by the original global **006592A4**.

## Native PE x87 operand roles, not mere arithmetic equivalence

The initial full-source C++ emitted all **273/273 native ordered
mnemonics** but incorrectly loaded the 00657F74 Y-motion scale first,
then FMULed actor+0x54. The original PE at ordinal **60** actually
has `FLD dword ptr [actor+0x54]`, and at ordinal **61** `FMUL
dword ptr [00657F74]`. Hence original COFF `00657F74` DIR32
was in the **wrong native physical instruction** in the initial source.
Borrowing the genuine used motion field lvalue with
`(*(&F1037_MOTION(this).yMotion))` restores the authentic native
x87 load/multiply order under ordinary pinned MSVC7.1.

The verified current complete one-switch parent now matches:

| Original action 0x34C | Native result |
| --- | ---: |
| Original PE CODE/x86 | **1,266B /273** |
| Natural C++ inner CODE/x86 | **1,044B /273** |
| Ordered native mnemonics | **273/273** |
| Original GPR operand roles | **273/273** |
| Matching original instruction widths | 200/273 |
| Genuine physically correct PE external call/global fields | **18/18** |
| Native parent+0x314 loop multiplier | **45**, correct |
| Original projectile ID / actual call | `0x360` /`00453A70`, correct |
| Original Y-motion global DIR32 at ordinal 61 | **correct** |

The live `verify-characterobject-current-recovered-f1068.py` cold
builds **only the one affected complete partial C++ parent**, independently
SHA-checks the actual **81,539B Japanese original CODE** and 567B
DATA, all **92 physical DIR32 case-label equivalence partitions** and
**199 literal sparse-map bytes**, and compares every recovered state
opcode/GPR position and independently computed original PE REL32/
DIR32 target, including native scalar immediates.

After F1085 it covers **43 recovered authentic original game state
interiors**, totaling **35,805 native original CODE B /7,786 x86**,
with **7,786/7,786 original mnemonic+GPR role positions**,
**620/620 genuinely original physical nonlocal PE fields** and
**1,452/1,452 nonrelocated scalar immediates**. Current C++ emits
**29,479 CODE B /7,928 x86** with 567B authentic afterRET DATA.
Original complete game is still **81,539B /17,435 x86**, its
original receiver EBP-0xAC and `ESP 0x3A0` differ from current
EBP-0x64 and `ESP 0x194`. Remaining switch states are real source
debt, as are original instruction widths and branch distances:
**whole original 81KB remains NONEXACT; newly accepted exact CODE 0B**.

Reproduce **only the changed large game source**, not all 979 units:

    scripts/repo-python scripts/verify-characterobject-current-recovered-f1068.py

Normal C++/COFF/PDB compiler and independent original PE receipts,
including the rejected wrong-x87 version, remain under ignored
`.analysis/f1085-native34c/` and `.analysis/f1068-boss-live-all-native/`.
No manual x86 patches, fictitious locals, cropped-case exact credit
or corpus-wide cold replay.
