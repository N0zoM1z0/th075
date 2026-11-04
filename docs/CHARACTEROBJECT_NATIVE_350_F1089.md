# F1089 — Real original 1,263B 0x350: four parent actions, eight 0x364 projectile shots

**Historical F1089 checkpoint:** the live parent now additionally restores [F1090 0x351](CHARACTEROBJECT_NATIVE_351_F1090.md); previous 47-state/33,457B partial source totals below are historical, and original 350 PE fields remain verified.

Pinned Japanese TH075 1.11 has ONE authored original game callable
`CharacterObject::Advance` at `0050A580`: **81,539 native CODE B /
17,435 x86**, followed by 567 independently owned sparse-switch
DATA bytes. F1089 restores a further genuine original inner game
state; the source remains an incomplete NONEXACT one-switch parent,
not an accepted independent original case function.

Actual native original `0x350` physically occupies
**00514048..00514537**: **1,263 original CODE B /273 x86**.
This native family resembles `0x34C`'s 273-x86 geometry but differs
in original stage-one transition placement, specific parent action
conditions, literal spawned projectile ID and genuine scratch slots.
It resets native animation/motion, opacity, scales and status, updates
actual parent-relative X/Y using original 0065989C/00657F74/0065835C
floats and actor+0xC8, checks native signed fighter health and
parent collision state, and increments/clamps signed +0xD8 by 5 to 140.

The original stage-zero trigger is the exact **four** parent action
pairs **`(0x192,4)`, `(0x260,4)`, `(0x261,4)`, `(0x262,4)`**.
The game then performs a real **eight-iteration C++ loop** writing
parent+0x314 float `float(shot*45)` and spawning original game action
**`0x364`** with actual actor position and parent facing through
`00453A70`. The authentic subsequent alpha fade, stage-one native
`0x2C1/3` early return/parent `00453D40(20)`, action completion
and stage-two parent+0x36C vertical adjustment use the original
native call order. The 0x364 game ID is not interchangeable with
0x34C's 0x360, 0x34D's 0x361, 0x34E's 0x362 or 0x34F's 0x363.

Actual Japanese original PE was re-read for all real 273 x86
ordinals; natural source was built under the actual pinned VC7.1
compiler inside the *entire current partial one-switch parent*. The
original source action exists once at its own original dense/sparse
switch entry, not as a new callable or a fake matching byte buffer.

| Original action 0x350 | Verified current C++ |
| --- | ---: |
| Original native CODE B/x86 | **1,263B /273** |
| Selected generated inner C++ CODE B/x86 | **1,041B /273** |
| Matching original mnemonic and GPR roles | **273/273 each** |
| Original native instruction widths matching | 200/273 |
| Correct original physical PE external fields | **18/18** |
| Original four parent action/phase pairs | **all verified** |
| Original `0x364` projectile and 45° step | **verified** |

The live original PE verifier
`scripts/verify-characterobject-current-recovered-f1068.py`
rebuilds **only the one affected current C++ parent**, SHA-checks
the independently verified original entire 81KB CODE, original
92 afterRET DIR32 jump-label equality classes and all 199 native
sparse literal bytes, and checks every recovered case's original
x86 ordinal, GPR role and actual physical PE REL32/DIR32 target,
including scalar immediate bytes that can differ despite the same
mnemonic/GPR and call target.

After F1089, it verifies **47 source-recovered original game-state
interiors** representing **40,671 original native CODE B /
8,838 native x86**, with **8,838/8,838 original mnemonic+GPR
positions**, **692/692 original physical nonlocal PE fields** and
**1,636/1,636 scalar immediate positions**. Current partial parent
emits **33,457 CODE B /8,972 x86** plus real 567B afterRET DATA,
with saved receiver EBP-0x74 and frame `ESP 0x1D4`, versus
**original 81,539B /17,435 x86**, original receiver EBP-0xAC
and frame `ESP 0x3A0`. Many authentic game states and instruction
width/branch geometry remain nonexact. **New accepted whole original
GAME CODE = 0B**; 979 previously accepted exact callables remain
separate and unchanged.

Reproduce **only this affected partial whole game source**:

    scripts/repo-python scripts/verify-characterobject-current-recovered-f1068.py

Native PE, regular VC7.1 COFF/PDB/compiler results and independent
physical field receipts under ignored `.analysis/f1089-native350/`
and `.analysis/f1068-boss-live-all-native/`. No forced registers,
assembler, direct original PE byte graft or 979-unit mass replay.
