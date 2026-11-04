# F1117 — Real original action 0x388, 748B/160 x86: native 60.0f reset and unordered-aware JNP ground transition

Pinned Japanese TH075 v1.11 contains one independently authored original `CharacterObject::Advance` at `0050A580`, **81,539 original CODE B /17,435 x86** plus 567 actual afterRET switch DATA bytes. F1117 restores true game action **`0x388` at `0051B89F..0051BB8B`, 748 native original CODE B /160 x86**, inside the still-NONEXACT original-shaped whole C++ parent. It is not a separate exact-original callable.

Original gameplay checks actual parent+0x3A0 health, authentic +0x7C hit-status six and signed +0x80 countdown, and at stage/frame (0,0) invokes `0040FBB0(0,60.0f,0)`, sets both scales to 1.0f, four alpha bytes 0xFF, countdown +0x80=1, status+0x7C zero, real Y velocity **22.5f**, and calls parent `00453D40(3)` plus real `00453A70` to launch native game action **`0x345`**. It advances actual Y by velocity, then stage 1 increases +0x30 angle by original `00657878`, decreases real Y velocity by original `0065747C`, and clamps it at zero on the native `0065782C` ground threshold.

At stage 2 it subtracts real global `00657478` from Y speed, advances native Y, and makes a second authentic ground collision comparison. When actual status+0x7C is neither 0 nor 6 and the native floating branch allows it, it stops Y velocity, advances native subaction `0040FB40(3)`, invokes parent `00453D40(5)` and returns. On original `0040FA30` completion it expires through `0045B830`; at stage 2/frame zero it invokes parent `00453D40(4)`, assigns X speed **−10.0f**, resets +0x30 angle and returns.

## Why `if (Y+Vy > ground)` was incorrect

The first ordinary C++ version compiled all but one of the **160 ordered original mnemonics**, and emitted **161** instructions because of an unnecessarily separate terminal `return`. Its stage-2 x87 comparison lowered to **`TEST AH,0x41; JNE`**, while the actual original PE uses **`TEST AH,0x41; JNP`**. These differ on x87 unordered/NaN inputs; this was not merely a branch label spelling issue. The native-shape source uses **`if (!(Y+Vy <= ground))`** to preserve the original unordered-aware semantics. The real common terminal return removes the extra JMP without adding fabricated operations. The corrected natural C++ now emits the full native `TEST AH,0x41; JNP` at ordinals **116–117**.

| Real original `0x388` | Verified selected C++ |
| --- | ---: |
| Complete native original case CODE B | **748 /748 generated inner bytes** |
| Original x86 mnemonics | **160/160** |
| Original GPR-role operands | **160/160** |
| Original instruction-width ordinals | **160/160** |
| Physically correct original PE call/global fields | **14/14** |
| Non-relocated native scalar immediates | **32/32** |
| Original FPU `TEST AH,0x41; JNP` | **exactly reproduced** |

`verify-characterobject-current-recovered-f1068.py` compiles only this one changed partial original C++ whole parent, compares it to the independently pinned original entire 81KB PE, original **92 afterRET DIR32 label equivalence partitions /199 literal sparse bytes**, and now checks **70 strict GPR-role-matched original inner cases**, **66,653 original native CODE B /14,299 original x86**, **14,299/14,299 original mnemonic+GPR positions**, **1,095/1,095 physical original external PE fields**, and **2,642 scalar immediates**. Seven other genuinely source-backed original cases remain **PROVISIONAL** for GPR debt.

The selected incomplete C++ parent emits **71,400 CODE B /15,289 x86** versus entire authentic game **81,539B /17,435 x86**. Missing states, original stack frame, and branch geometry are still incomplete. **The whole original callable remains NONEXACT and newly accepted whole original game CODE bytes remain 0.**

Reproduce only the affected partial one-switch game parent:

    scripts/repo-python scripts/verify-characterobject-current-recovered-f1068.py

Normal VC7.1 source/COFF/PDB compiler logs, rejected `JNE`/extra-return variant and original Japanese PE evidence are retained under ignored `.analysis/f1117-native388/` and `.analysis/f1068-boss-live-all-native/`; no all-979 cold replay or target EXE modification.
