# F1107 — Real 1,694-byte 0x35E homing angle pursuit, independent post-update branch, 35F GPR phase recovered

**Historical F1107 checkpoint:** the current one-switch parent has since restored [F1108 native 0x360/0x361](CHARACTEROBJECT_NATIVE_360_361_F1108.md), raising the strict original-inner cohort to 57. The 55-case/51,498B whole-parent source sizes below are the earlier valid snapshot, not the current compiler geometry.

The SHA-pinned Japanese TH075 1.11 original has ONE authored
`CharacterObject::Advance` at `0050A580`: **81,539 original CODE
B /17,435 native x86** and 567 genuine separate afterRET switch
DATA bytes. F1107 restores true native state `0x35E`, physically
`00516646..00516CE4`, **1,694 original CODE B /350 x86**, in the
same incomplete normal MSVC7.1 one-switch C++ parent. The 81KB
original whole function is still **NONEXACT**.

## Native gameplay and one material C++ control-flow correction

The original 0x35E first checks four genuinely independent original
X/Y arena bounds `0065925C/00659258/006583B4/00658374`, then the
parent `(0x31,0x96)` action range with an actual **two-shot 0x3E4**
loop and conditional extra `0x3E3` projectile. Native status five
expires early. On stage/frame zero it resets genuine motion and
opacity, both scales, original +0x80 and +0x7C, timer +0xD8 to
**60**, direction +0xDA and +0xDE to zero, and computes +0xDC
signed initial angle from native float actor+0xC8 via actual CRT
`006406AC`. It calculates native `00483300` atan2 of actual X/Y
motion, divides by real float `00657828` and calls authentic
`0040FB70` using floating angle+0xDC and a timer-driven native
`006590B4` motion contribution.

In subsequent animation stages, original +0x80 zero expires and
spawns one real action **0x35F** through parent `00453A70` after
`00453D40(1)`. Otherwise +0xD8 increments by 2, real atan2 updates
angle+0x30, and a second original atan2 computes the signed target
+0xDA from the *grandparent position relative to the actor*, signed
facing multiplier and original `00657888` Y offset, using a second
real CRT float-to-signed conversion. The original steers +0xDC
by 2 degrees with wraparound **±180/360**, and finally refreshes
native `0040FB70` motion, advances facing-relative X and subtracts
Y velocity, and checks original `0040FA30`/`0040FB40(1)` completion.

The initial real C++ version was subtly **wrong**: it modeled
angle-over-target adjustment and angle-under-target adjustment as
an exclusive `if/else`. Original native PE actually does **two
separate comparisons**, re-reading +0xDC **after the first mutation**.
This permits the second branch to execute after the first changes
+0xDC, and is genuine game behavior, not redundant instruction
padding. Changing to the authentic two independent `if` statements
restores all **350/350 native mnemonics** (the initial source emitted
345) with natural VC7.1 code generation.

## Entire parent and original physical PE evidence

Original game x87 conditions, *all* original physical instruction
ordinals and true external field destinations were reread from the
independent pinned executable. The selected complete original-shaped
partial C++ emits **1,707 B /350 x86** for this **1,694 B /350
x86** native interior, matching all 350 ordered mnemonics,
**345/350 original widths**, **28/28 real physical original REL32/
DIR32 call/global fields** and **54/54 nonrelocated scalar immediate
values**. Native GPR positions are **276/350**: most remaining role
errors occur before the initial float-to-int helper around ordinal
123; later 225 ordinal positions have the same original GPR roles.
**This interior remains provisional**, not a new exact callable.

An important *cross-case* compiler result: restoring the authentic
350-instruction 0x35E body fixes the following state **0x35F** from
**6/10** to **10/10 original GPR positions**. The original 0x35F is
only 44 original CODE B /10 x86, with two real original PE call
fields. It is now promoted to the **strict role-matched internal
case list**, but is still part of ONE original giant function,
not an independent accepted exact 44-byte whole callable.

| Live full-parent verification class | Genuine original evidence |
| --- | ---: |
| **55 strict original inner cases**, including 35F | **46,562 native original CODE B /10,096 original x86** |
| Strict original mnemonic/GPR roles | **10,096/10,096** |
| Strict original PE call/global fields | **773/773** |
| Strict original non-relocated scalars | **1,895** |
| **7 other provisional native cases**, including 35E | **4,310 native original CODE B /916 x86** |
| Provisional ordered native mnemonics | **916/916** |
| Provisional original GPR roles | **469/916** |
| Provisional physically original PE fields | **70/70** |
| Provisional original scalar literals | **165** |
| Selected entire incomplete C++ CODE B /x86 | **51,498 /11,116** |
| Original single whole game CODE B/x86 | **81,539 /17,435** |

The current parent has saved receiver EBP-`0x8C` and frame
`ESP 0x22C`, versus original EBP-`0xAC`/`ESP 0x3A0`. The native
**92 afterRET DIR32 jump-label equality classes and 199 sparse
literal index bytes** remain verified. Missing other game-state
code, GPR/stack ownership and original branch widths prevent
entire original whole-function acceptance. **New exact whole
original GAME CODE B = 0**, and the 979 previously accepted exact
whole native functions are unaffected.

Reproduce **only the affected one whole partial 81KB game source**:

    scripts/repo-python scripts/verify-characterobject-current-recovered-f1068.py

Normal pinned VC7.1 source/COFF/PDB/compiler logs, rejected
exclusive-branch hypothesis and original PE physical receipts
remain under ignored `.analysis/f1107-native35e/` and
`.analysis/f1068-boss-live-all-native/`. No full 979-unit replay.
