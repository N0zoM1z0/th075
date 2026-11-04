# F1116 — Real 0x387 random flying shard, native bounce/opacity: 752B/167 x86 all original widths and PE fields

The pinned Japanese TH075 1.11 original game has one authored `CharacterObject::Advance` at `0050A580`, **81,539 native original CODE B /17,435 x86** with genuine 567B afterRET sparse-switch data. F1116 restores original inner case `0x387` at **`0051B5AF..0051B89F`**, **752 native CODE B /167 x86**, in that still-incomplete one-switch C++ parent. This is a real original game-state interior, NOT a new independently exact original function.

Original 0x387 checks four physical arena boundaries `0065925C/00659258/006583B4/00658374`, then signed parent+0x3A0 loss, with authentic `0045B830` expiry on failure. At stage/frame zero it calls native `0040FBB0` motion reset, sets countdown +0x80=1, status+0x7C=0, direction +0xD8=0, scales to 1.0f, alpha bytes to 0xFF; generates **three real independent random values** using original `00455580`: angle+0x30 is `Random(0,0x167)`, X velocity is `float(Random(0,16)-8)`, Y velocity is `float(Random(0,6)+12)-00659888`. It then adds original angular offset **0065786C** to +0x30.

Each frame it advances native signed-facing X and adds real Y motion. At stage 1 it tests **`actorY+velocityY <= original 0065782C`** using real x87 `TEST AH,0x41; JP`, then calls `0040FB40(2)`, reverses the actual Y velocity with native **`FCHS`** and resets Y to zero. At stage 2 it fades actual unsigned alpha by 15 or expires, followed by true `0040FA30` animation-completion expiry.

| Real Japanese original 0x387 | Ordinary current C++ |
| --- | ---: |
| Original physical CODE B /x86 | **752/752 B, 167/167 x86** |
| Ordered original mnemonic positions | **167/167** |
| Original native GPR roles | **167/167** |
| Native original instruction widths | **167/167** |
| Native original PE REL32/DIR32 call/global fields | **17/17** |
| Original nonrelocated scalar-immediate values | **31/31** |
| Actual original float `FCHS` and x87 unordered-aware ground branch | **verified** |

The live `verify-characterobject-current-recovered-f1068.py` re-compiles only the affected whole partial parent, independently checks the original full 81KB PE and native **92 DIR32/199 sparse afterRET DATA**, and validates **69 strict native GPR-matched inner cases**, **65,905 original CODE B /14,139 original x86**, **14,139/14,139 mnemonic and GPR roles**, **1,081/1,081 real original external PE fields** and **2,610 scalar-immediate positions**. Seven other source-backed cases are explicitly GPR-provisional.

Current partial C++ emits **70,667 CODE B /15,131 x86** while original whole is **81,539B /17,435 x86**. Missing native game states, frame/stack owners and branch displacements still prevent exact whole callable acceptance. **New accepted exact original whole CODE = 0B; 979 already accepted exact whole callables unchanged.**

Reproduce only this affected source:

    scripts/repo-python scripts/verify-characterobject-current-recovered-f1068.py

Normal VC7.1 source/COFF/PDB compiler receipts and independently original PE evidence under ignored `.analysis/f1116-native387/` and `.analysis/f1068-boss-live-all-native/`. No original EXE edit or 979-function replay.
