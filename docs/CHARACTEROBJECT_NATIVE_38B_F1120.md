# F1120 — Real original 0x38B, 1,088-byte 226-x86 braking and acceleration phases; actor-first x87 global

The original SHA-pinned Japanese TH075 v1.11 `CharacterObject::Advance` is ONE 81,539-byte/17,435-x86 whole authored game function at `0050A580` with a genuine 567-byte afterRET switch table. F1120 restores its actual **`0x38B` game-state interior** at original PE `0051C3ED..0051C82D`, **1,088 native CODE B /226 x86**, into the existing ordinary VC7.1 original-shaped C++ parent, not as an independent exact callable.

Original game behavior checks four genuine X/Y arena bounds and expires out-of-bounds actors through real `0045B830`. Stage/frame-zero initializes motion, two **0.1f** scale floats, alpha bytes **0/255/255/128**, X velocity **20.0f**, signed +0xD8/+0xDA/+0xDC, collision status and countdown. While original +0xDC==0, it decreases native X velocity by **00659090**; a genuine x87 threshold comparison to **0065747C** clamps speed to **1.0f** and changes +0xDC to 1. At +0xDC in (0,30) the phase increments, and above 29 the original **00657478** global is added to X velocity.

While signed +0xD8 is zero, the actor expands both scale floats using real **006590B4**, and increments unsigned alpha by 25 until the real **0065747C** threshold switches to scales 1.0f and alpha 255. Native alpha completion increments signed +0xD8 and sets the true +0x80 countdown to 1. Status 6 clears +0x7C and increments countdown; other actual collision flags update +0xD8 and clear status after 5. Native facing-relative X movement, original `0040FB40(0x17)` fallback, `0040FA30` animation completion/expiry, and stage-23 reset via `0040FB40(1)` are preserved.

The initial source already compiled all **226 original mnemonic ordinals**, but two x87 operands were wrong: C++ loaded `00657478` first and then added actor X speed. The *actual original PE* at **ordinal 101** requires `FLD [actor+0x50]`, and at **ordinal 102** `FADD [00657478]`. The initial source therefore physically misplaced a DIR32 original field despite preserving instruction order. The real native X-motion borrowed lvalue `(*(&F1037_MOTION(this).xMotion)) + global` makes pinned VC7.1 emit the original actor-first float loading order, restores all register/width roles and the genuine physical global-field position without any assembler, register coercion, synthetic stack allocation or byte-patching.

| Actual original 0x38B | Current whole-parent C++ case |
| --- | ---: |
| Real original native case CODE B | **1,088 /1,088 emitted** |
| Ordered original x86 mnemonics | **226/226** |
| Original GPR roles | **226/226** |
| Original instruction widths | **226/226** |
| Physically correct PE call/global fields | **16/16** |
| Real nonrelocated original scalar immediate positions | **45/45** |
| Original x87 global at ordinal 102 | **00657478**, correct |

The live targeted `scripts/verify-characterobject-current-recovered-f1068.py` compiles only the affected current partial *whole* original-shaped parent, verifies the pinned entire original 81KB PE and authentic **92 postRET DIR32 equivalence partitions and 199 sparse bytes**, and checks **73 strictly native-role-matched inner game cases**, **69,887 original CODE B /14,989 original x86**, **14,989/14,989 native mnemonic+GPR positions**, **1,153/1,153 real original physical PE fields** and **2,780 genuine scalar immediate values**. Seven additional native game cases remain separately tracked GPR-provisional.

Current partial whole C++ emits **74,589 CODE B /15,973 x86** versus original entire **81,539B /17,435 x86**. Source is still incomplete, original real stack/frame and physical branch-distance ownership are not restored, and **the original entire callable remains NONEXACT, zero newly accepted whole original CODE B**. The 979 already accepted whole exact functions remain unchanged.

Reproduce only the affected game source:

    scripts/repo-python scripts/verify-characterobject-current-recovered-f1068.py

The real PE original field evidence and rejected global-first VC7.1/COFF/PDB result are retained under ignored `.analysis/f1120-native38b/` and `.analysis/f1068-boss-live-all-native/`. No full-979-unit cold replay.
