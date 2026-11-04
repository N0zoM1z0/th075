# F1101–F1103 — Five actual original game cases 0x358..0x35C, 2,313 native B, provisional GPR lifetime

The pinned Japanese TH075 1.11 game has ONE original `CharacterObject::Advance`
callable at `0050A580`: **81,539 original CODE B /17,435 x86**, with
567 independently owned afterRET switch DATA bytes. The five
physically distinct original states 0x358..0x35C have been restored
as substantive, native-shaped C++ game actions inside that incomplete
one-switch parent. **They are PROVISIONAL, NOT fully recovered or byte-exact**.

## Native gameplay actually reconstructed

- **0x358:** genuine parent `(0x31,0x96)` action/stage check, a ten-shot
  `0x3E4` loop and extra parent-conditional `0x3E3`; stage-zero X speed
  **8.0f**, actual stage-one parent `00453D40(2)` followed by a
  real spawn of **0x359** through `00453A70`; signed-facing X motion,
  original float X boundaries at `00659424` and `0065924C` with native
  `TEST AH,0x41; JE` and `TEST AH,5; JP`, and up to five authentic
  native animation subaction transitions.
- **0x359:** genuine stage/frame-zero signed +0xD8 zero, +0x80 WORD one,
  +0x7C status zero; original `0040FA30` action comparison and native
  `0045B830` expiry.
- **0x35A:** true stage/frame-zero `0040FBB0`, X/Y scale **1.5f**,
  original `0040FA30` completion and `0045B830` expiry.
- **0x35B:** real parent `(0x31,0x96)`/stage below 23 gate and **eight
  `0x3E4` shots** plus original extra `0x3E3`, initial scale 0.1f,
  X speed **22.0f**, signed WORD hit/countdown behavior, native x87
  X speed and scale thresholds at `00658048`/`0065747C`, alpha
  fade, actual signed-facing X motion, stage-23 action transition
  `0040FB40(1)` and original `0040FA30` completion.
- **0x35C:** real initial `0040FBB0`, +0x80 WORD **99**, scale 1.0f,
  zero X/Y motion, two original `006590B4` float scale additions,
  stage-dependent alpha reduction by 10 or `0045B830` expiry, and
  original `0040FA30` completion.

## Actual PE and source comparisons — do NOT promote to exact

Each full physical native PE case interval, every natural C++ case
emitted inside one complete pinned-VC7.1 whole-parent compilation,
and all real external COFF nonlocal fields were re-read and compared.
The tracked live verifier requires original instruction mnemonics,
**every original physical REL32/DIR32 target with true field offset**,
and every non-relocated scalar value, but records the GPR deviations
without masking or accepting them. This is a *separate provisional*
list excluded from the **54 strict matched-GPR cases**.

| Original case | Native CODE B / x86 | Selected source CODE B / x86 | Native widths | GPR positions | Original PE fields | Scalars verified |
| --- | ---: | ---: | ---: | ---: | ---: | ---: |
| 0x358 | **625 /143** | 625 /143 | 143/143 | **52/143** | **11/11** | 25 |
| 0x359 | **115 /24** | 115 /24 | 24/24 | **8/24** | **2/2** | 3 |
| 0x35A | **115 /27** | 115 /27 | 27/27 | **13/27** | **3/3** | 5 |
| 0x35B | **1,109 /233** | 1,121 /233 | 227/233 | **67/233** | **13/13** | 51 |
| 0x35C | **349 /72** | 349 /72 | 72/72 | **21/72** | **6/6** | 16 |
| **Five native interiors, not whole functions** | **2,313B /499** | **2,325B /499** | 493/499 | **161/499** | **35/35** | **100** |

The first 0x35B natural C++ had a distinct unnecessary terminal
return and emitted 234 rather than 233 x86. The authentic common
terminal source flow now correctly emits **233**, but 6 original
jump widths still differ. Twelve additional complete C++ variant
builds of the **entire partial parent** checked actual for-loop
forms, counter spelling, parent pointer lvalue, x-position and
signed facing expressions, and equivalent Boolean guard grammar.
All emitted the same 143 0x358 mnemonics and **52/143 GPR roles**.
This strongly suggests the unresolved native register allocation
lifetime depends on other game state code and declaration sequencing,
not cosmetic loop spelling. Their actual C++/COFF/PDB and original PE
receipts are preserved under ignored `.analysis/f1103-native35b35c/`.

## Honest whole-owner state

The **separately verified 54** previous game-state interiors still
match **46,518 original CODE B /10,086 original x86 mnemonic and GPR
positions**, with **771/771 genuine physical PE external fields**
and **1,895 native scalar immediate positions**. The **five
provisional** states are reported **in addition**, never included
in those strict-role totals or credited as exact. The source's
changed physical receiver slot now crosses the VC7.1 disp8/disp32
boundary: several earlier strict states emit different instruction
widths, but `0x33B/33D/33F/341/343` retain two per-case width gaps.
Whole partial C++ emits **49,493 CODE B /10,695 x86**, original
whole remains **81,539B /17,435 x86** with saved receiver EBP-0xAC
and original `ESP 0x3A0` versus current EBP-0x88, `ESP 0x208`.
The native 92 DIR32 afterRET jump-label equality partition and 199
literal sparse bytes are preserved. **Whole original is NONEXACT.
New accepted exact original callable bytes = zero.**

Reproduce only this one selected complete *partial* parent:

    scripts/repo-python scripts/verify-characterobject-current-recovered-f1068.py

No full 979-unit cold replay, target PE patch, synthetic stack local,
relaxed whole-function acceptance or false authored exact credit.
