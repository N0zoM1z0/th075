# F1098 — Authentic 0x357: parent-facing X ×120, real 120.0f Y and x87 scale fade

The SHA-pinned Japanese TH075 1.11 original has ONE independently
authored `CharacterObject::Advance` at `0050A580`: **81,539 original
CODE B /17,435 x86**, plus separately owned authentic 567B
switch DATA. F1098 restores genuine action `0x357`, physically
`005159A0..00515C0E`, **622 original CODE B /131 native x86**,
inside the same incomplete natural VC7.1 parent. A switch case is
not a separately accepted original game callable.

This real game action first checks actual parent `(0x31,0x96)` and
its own stage below `0x17`, then uses original `0040FB40(0x17)`
transition. For actual parent action **0x189** below own stage 0x17,
it moves the actor's X to **parent X plus signed-facing ×120**
(real native `IMUL 0x78; FILD; FADD [parent+0x44]`) and fixes Y at
the exact original **120.0f** bit pattern `0x42F00000`.

At stage/frame zero it uses real `0040FBB0` motion reset,
0.1f initial scale, alpha zero/255/255/255 and signed +0xD8/+0xDA
timers zero. It then grows scales/alpha using independent native
`0065747C` threshold, native `006590B4` float step and alpha
increment 25, or sets the scales to 1.0f and alpha to 0xFF.
The actual x87 threshold uses native **`TEST AH,5; JP`** at
ordinals 76/77. On full alpha it increments +0xD8 and sets the
real +0x80 timer to 1. Original completion requires parent+0x82
timer zero AND original `0040FA30` action equal to own +0x70,
then expires through `0045B830`.

| Actual original 0x357 game interior | Verified source |
| --- | ---: |
| Native Japanese CODE B / x86 | **622 /131** |
| Selected C++ case CODE B /x86 | **499 /131** |
| Original ordered mnemonic and GPR positions | **131/131** each |
| Native matching instruction widths | 90/131 |
| Physically original PE external call/global fields | **7/7** |
| Native signed facing multiplication | **×120**, original immediate |
| Native Y=120.0f bit value and `TEST AH,5; JP` | verified |

The live `scripts/verify-characterobject-current-recovered-f1068.py`
cold compiles **only the changed entire partial one-switch C++**,
reads and SHA-checks the entire independent original 81KB PE CODE,
92 original postRET DIR32 jump-target equivalence classes and all
199 native sparse literals, and checks **54 real original game-state
interiors**, **46,518 original native CODE B /10,086 native x86**,
**10,086/10,086 native mnemonic and GPR positions**, **771/771
correct original physical PE nonlocal fields** and **1,895/1,895
nonrelocated scalar-immediate positions**.

Current normal partial source emits **38,034 CODE B /10,206 x86**
plus 567 original-shaped afterRET DATA versus whole original
**81,539B /17,435 x86**. Original ESP `0x3A0`, saved receiver
EBP-`0xAC` differ from incomplete current ESP `0x1F8` and
EBP-`0x80`. Many original game cases, branch width and stack
geometry remain missing. **The whole original native game callable
is NONEXACT; newly accepted whole original CODE = 0 B.**

Reproduce only this affected whole source:

    scripts/repo-python scripts/verify-characterobject-current-recovered-f1068.py

Original native PE field receipts and full ordinary VC7.1
C++/OBJ/PDB logs remain in ignored `.analysis/f1098-native357/`
and `.analysis/f1068-boss-live-all-native/`. No original EXE mutation,
cropped-case exactness claim or 979-unit mass cold replay.
