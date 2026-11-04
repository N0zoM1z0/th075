# F1095 — Native original 0x355, real ten-shot projectile and two-way vertical velocity phases

**Historical F1095 checkpoint:** the live source now also contains genuine [F1097 native 0x356](CHARACTEROBJECT_NATIVE_356_F1097.md). The earlier 52-state/36,587B parent totals below refer to that valid checkpoint, while original 355 20/20 PE fields remain verified.

Pinned Japanese TH075 1.11 has ONE authored original `CharacterObject::Advance`
callable at `0050A580` (**81,539 native CODE B /17,435 x86**) and
567 separately owned afterRET switch DATA bytes. F1095 restores original
case **`0x355` at `00514FE8..005154ED`, 1,285 native CODE B /270
x86**, as genuine C++ gameplay inside the incomplete original-shaped
whole source. Original switch cases are not independent original
whole callables or separately accepted exact CODE bytes.

The native game first tests parent action in `(0x45,0x96)`, expires
through real `0045B830` and launches an authentic **ten-shot loop of
`0x3E4`** through `00453A70`, plus conditional original parent+0xEFA
reset and extra `0x3E3` shot. Otherwise, on stage/frame zero it
resets motion through `0040FBB0`, two 0.0f scales, four alpha bytes
at 0xFF, actual **X/Y speed 10.0f/6.0f**, signed +0xD8/+0xDA/+0xDC
WORDs and action/status fields. The real scale changes use native
`00659898`/`006590B4`; X speed decreases against native `00657478`
and may clamp to 0.5f.

The original Y velocity is a **two-way oscillating state**: signed
+0xDC zero decreases Y velocity by `006583F8` until it passes original
lower threshold `00659894`, then +0xDC one increases it until native
upper threshold `00659890`. Native status+0x7C, action countdown+0x80
and stage 31 transitions disable motion, raise scales using actual
`00658348`, fade alpha by 25, and update actor Y then signed-facing
X. Completion checks original `0040FA30` and `0045B830`. At stage
31/frame zero it cycles +0xDA up to six with native `0040FB40(1)` or
resets both velocities and records +0xDC=2.

## Original PE floating-point operands, not just matching mnemonics

The first full-source normal VC7.1 C++ produced all 270 original
mnemonics but incorrectly had native ordinal **161** load the global
`006583F8` and ordinal **162** add actor Y velocity. The pinned
original game instead has `FLD [actor+0x54]` at 161 and
`FADD [006583F8]` at 162. Both sources use the same x86 mnemonic
sequence, but the initial source's DIR32 relocation field was
physically located on the wrong instruction. The actual borrowed
native actor motion lvalue `(*(&F1037_MOTION(this).yMotion)) + global`
restores correct original x87 order under pinned VC7.1 without
forced register allocations, fake locals or byte patching.

| Original `0x355` entire native state interior | Result |
| --- | ---: |
| Actual Japanese original CODE/x86 | **1,285B /270** |
| Current compiled real C++ case CODE/x86 | **1,027B /270** |
| Original ordered mnemonic positions | **270/270** |
| Original GPR roles | **270/270** |
| Native x86 widths matching | 184/270 |
| Physically original PE nonlocal call/global fields | **20/20** |
| Original FPU parity/control test ordinals | **96/97, 124/125, 135/136, 152/153, 169/170**, verified |
| Original `0x3E4` / `0x3E3` projectile arguments | correct |

The live `verify-characterobject-current-recovered-f1068.py`
compiles **only the one changed whole partial C++ parent**, rechecks
SHA-pinned original 81KB CODE, genuine 92 afterRET DIR32 label
partitions and 199 literal sparse-map bytes, and verifies **52 genuine
original game-state interiors** totaling **44,693 original CODE B /
9,704 native x86 positions**, **9,704/9,704 original mnemonics
and GPR roles**, **750/750 physical PE external fields**, and
**1,816/1,816 nonrelocated scalar-immediate positions**.
Current incomplete source emits **36,587 CODE B /9,828 x86** plus
567 original afterRET DATA, compared to authentic entire game
**81,539B /17,435 x86**. Original `ESP 0x3A0` / saved receiver
EBP-0xAC differ from current partial `ESP 0x1EC` / EBP-0x7C;
many original cases, instruction widths and branch distances are
still missing. **Whole original callable remains NONEXACT; zero
newly accepted full-function CODE bytes.**

Reproduce ONLY the affected partial original-shaped whole game source:

    scripts/repo-python scripts/verify-characterobject-current-recovered-f1068.py

Actual Japanese PE operand/physical field receipts, rejected wrong-Y
source and complete normal VC7.1 OBJ/PDB/compile artifacts are retained
under ignored `.analysis/f1095-native355/` and
`.analysis/f1068-boss-live-all-native/`. No 979-unit corpus replay.
