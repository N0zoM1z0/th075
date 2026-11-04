# F1118 — Original 0x389, genuine randomized trajectory, double scale and 0x33C projectile: 1,111B/238 x86

The pinned Japanese TH075 v1.11 game contains one original authored `CharacterObject::Advance` at `0050A580`: **81,539 original CODE B/17,435 x86**, with 567 separate afterRET sparse-switch DATA. F1118 reconstructs genuine inner native game action **`0x389` at `0051BB8B..0051BFE2`, 1,111 original CODE B/238 x86** inside that still-incomplete single C++ parent. It is NOT a new exact original callable.

Original gameplay checks four actual native arena boundaries `0065925C/00659258/006583B4/00658374`, then status+0x7C==5 expiry. At stage/frame zero it resets motion with `0040FBB0`, sets native countdown+0x80 and status+0x7C, both scales to 1.0f and alpha bytes to 0xFF. It initializes real signed action WORDs: speed+0xD8 **`RandomBoundaryAt00455580(0,300)+200`**; direction+0xDA **`Random(0,50)+45`**; limit+0xDC **`Random(0,15)+5`**; it calls native `0040FB70` with direction and speed scaled by original float **006590B4**.

While native stage <=1, the same real `0040FB70` call executes again, then the parent fires **`0x33C`** through original `00453A70` using actor X/Y and signed facing. Original `Random(0,4)-2` controls X scale via **two true double-precision constants `00658A20` and `00657D00`**, copied bit-preservingly into Y scale, not rounded twice. The native signed speed WORD then decreases by **15** and is clamped to the independently randomized +0xDC floor. The actor moves facing-relative X and subtracts Y velocity.

Original hit/status transitions stop native X/Y motion, advance `0040FB40(2)` and change both scales to **2.5f**. Stages >1 apply genuine `006598A4` fading to both scales and decrease unsigned alpha by 25 or expire through `0045B830`; actual `0040FA30` animation completion also expires. The original has ONE common terminal return path. The first natural source produced **239** instructions because an unnecessary distinct `return` created an extra final `JMP`; restoring the real common return yields the native **238** without adding artificial code.

| Physical original 0x389 | Selected full-parent C++ result |
| --- | ---: |
| Native original case CODE B | **1,111 /1,111** |
| Original ordered x86 mnemonics | **238/238** |
| Native GPR operand roles | **238/238** |
| Original native instruction widths | **238/238** |
| Original physical PE call/global destinations | **24/24** |
| Original non-relocated native scalar immediates | **44/44** |
| Native random helper calls at original ordinals 65/72/79/134 | **4/4** |
| Original double globals at 138/139 and two native motion calls at 97/116 | **verified** |

The tracked live `verify-characterobject-current-recovered-f1068.py` compiles only the one changed entire partial C++ parent and checks the pinned original full 81KB PE, original 92 postRET DIR32 partition classes plus 199 sparse bytes, and now **71 strictly register-matched original inner game cases**: **67,764 original native CODE B/14,537 original x86**, **14,537/14,537 ordered mnemonic+GPR positions**, **1,119/1,119 genuine physical original PE fields**, **2,686 non-relocated scalar immediate values**. Seven source-backed game interiors remain **PROVISIONAL** for uncorrected GPR allocation.

The selected partial one-switch C++ emits **72,496 CODE B/15,525 x86** versus authentic entire original **81,539B/17,435 x86**. Native stack-frame ownership, other game states and branch bytes remain unresolved; **the whole original game callable is NONEXACT and newly accepted exact whole original CODE remains 0B**.

Reproduce only the affected current parent:

    scripts/repo-python scripts/verify-characterobject-current-recovered-f1068.py

Normal original-shaped VC7.1 C++/COFF/PDB, rejected extra-return source, actual original PE field evidence and native scalar controls remain under ignored `.analysis/f1118-native389/` and `.analysis/f1068-boss-live-all-native/`. No all-979 cold replay, original EXE mutation or independent case exact credit.
