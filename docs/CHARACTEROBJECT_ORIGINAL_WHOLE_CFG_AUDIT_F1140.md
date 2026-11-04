# F1140 — Original 81KB FighterSwitch physical branch-target audit and native 0x387 per-frame gravity/angle correction

Pinned original Japanese TH075 v1.11 contains one authored `CharacterObject::Advance` at `0050A580`, **81,539 native original CODE B /17,435 original x86** and genuine 567B afterRET switch DATA. The natural C++ partial whole `probes/CharacterObjectWhole0050A580F1044.cpp` currently generates **81,560 CODE B /17,435 x86**, but this is **NONEXACT**, not newly accepted original function CODE. Earlier actual recovery established 82 strict-role-matched and 8 provisional inner states plus uncredited 0x391.

## Instruction-mnemonic matches did not prove true native control flow

The older full-parent verifier checked all original switch-case mnemonics, native GPR roles, every original physical external call/global PE field and scalar immediates. A new **independent full-original PE x86 control-flow audit** maps every native *direct intra-function JMP/Jcc target* and emitted normal VC7.1 C++ branch target to their respective **global original instruction ordinal**. Since all **17,435 ordered whole-function mnemonics** match, global x86 instruction ordinals are an independent, unambiguous cross-build branch-target key even while byte offsets, stack slots and branch widths differ.

It finds **1,834** actual direct native original intra-function jump edges, all resolving within both entire original and current C++ bodies. Previously **18 actual branch targets differed**, despite identical x86 mnemonics, many original widths, and correct PE globals. Those were real C++ control-flow discrepancies, not benign internal `$L` symbol name renumbering.

## First genuine native behavior correction: 0x387

The original physical `0x387` flying projectile interior `0051B5AF..0051B89F` is **752 native CODE B /167 x86**. Its stage/frame-zero guard has two real `JNE`s at *case-local ordinals 38 and 42*. Both pinned original branch targets land at **ordinal 92**, immediately **before** the original Y-motion decrement and angular offset. The earlier C++ placed BOTH inside the stage/frame-zero-only initialization, and those JNEs jumped directly to **ordinal 102**. Thus the previously sourced projectile applied its downward velocity offset and angle nudge only once, while the original game applies **both each frame**.

F1140 moves the real native `F1037_MOTION(this).yMotion -= [00659888]` and `SELF_FIELD(float,0x30) += [0065786C]` **outside the initialization block**, preserving their original order. Both guard JNEs now genuinely land at **92/92 original target ordinals**, reproducing the original per-frame trajectory rather than merely matching 167 instruction mnemonics. Current whole normal C++ still emits the native **167/167 original 0x387 mnemonic, GPR, width and physical PE field positions** and all original scalar immediates.

## Live 81KB parent verifier now rejects new CFG regressions

The tracked `scripts/verify-characterobject-current-recovered-f1068.py` was extended to cold-build **only this one affected whole parent**, independently SHA-check the original game PE, compare all **17,435 entire-function mnemonics**, and resolve all **1,834 native direct branch destinations** by global instruction ordinal. It requires that the original two 0x387 JNEs land on ordinal 92 in BOTH bodies and no additional source-graph differences arise. **16 original branch-target mismatches remain unresolved** in other source cases (0x330, 0x346, 0x35D/35E, 0x388/389, 0x391 and 0x3E3/3E4). Those 16 are **explicit debt, not an acceptance whitelist**: the tool refuses new mismatches while retaining the known remainder in its JSON report.

It still independently verifies the **82 native strict GPR-role case interiors** representing **75,260 original CODE B /16,090 x86**, **1,246/1,246 original physical PE external fields**, **2,964 scalar values**, and all original **92 afterRET DIR32 target-equivalence classes plus 199 sparse bytes**. Another 8 genuine original game states remain GPR-provisional, plus 0x391 with unresolved FUCOMPP PE field order. The source has original saved-this `EBP-0xDC` rather than genuine original `EBP-0xAC`, and its total CODE remains **21B larger than the game original**. **Whole original callable NONEXACT, newly accepted entire original CODE B=0**.

Reproduce the same single large affected parent:

    scripts/repo-python scripts/verify-characterobject-current-recovered-f1068.py

The previous C++ init-guard source and complete normal VC7.1 COFF plus original PE receipts are preserved under ignored `.analysis/f1140-boss-cfg-recovery/` and `.analysis/f1068-boss-live-all-native/`. No all-979 cold replay or machine-byte patch.
