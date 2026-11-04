# F1093 — Authentic original 0x354, 1,203B/251-x86 eight-shot actor and genuine x87 parity branches

The pinned Japanese TH075 1.11 original contains ONE independently
authored `CharacterObject::Advance` at `0050A580` (**81,539 native
CODE B /17,435 x86**) followed by genuine 567 separately owned
switch DATA bytes. This work restores an original game-state *interior*
not an independently exact native game function.

Physical original case `0x354` occupies **00514B35..00514FE8**:
**1,203 original CODE B /251 x86**. It expires the actor when the
real parent action is within `(0x31,0x96)` and its own stage is below
`0x17`, then executes an authentic **eight-shot loop of `0x3E4`**
through the real `00453A70`, and conditional parent+0xEFA timer
reset and extra `0x3E3` projectile. Otherwise, at stage/frame zero,
it initializes real `0040FBB0` motion, **0.1f** X/Y scale, alpha
zero/255/255/255, X speed **18.0f**, Y speed zero, actual +0xD8/+0xDA
and signed action countdown/status fields.

The real stage loop subtracts original global **00658048** from X
velocity and adds **006583F8** to Y velocity, clamps X speed to
**2.0f** based on the *actual* native unordered-aware x87 condition,
and grows scales/opacity using originals **0065747C** and **006590B4**.
It tracks native hit status 6,4, and other original status values,
advances the actor's facing-relative X and real Y velocity, and
transitions at action stage `0x17` using `0040FB40`; game animation
completion uses `0040FA30`/`0045B830` and frame-zero final
subaction handles the signed +0xDA transition.

## Correct two native parity conditions and x87 PE relocation

The original x87 sequence compares X speed at ordinal 105 and scale
at ordinal 117 and then uses **`TEST AH,5; JP`** at native ordinal
108/109 and 120/121. Initial natural C++
`if (!(speed < threshold))` produced the **wrong** native `JNP`,
even though the same x87 FCOMP had already emitted. Using the
actual source **`speed < threshold`** and **`scale < threshold`**
branches reproduces the exact original parity-aware JP opcodes and
correct game floating-point conditions. The original ends with a
single common return path, so eliminating one unnecessary distinct
source return also removed an extra machine JMP.

A second source-codegen issue remained: ordinary Y-motion addition
compiled to `FLD [006583F8]; FADD [actor+0x54]`, with the global
DIR32 relocation at the wrong original x86 instruction. The genuine
borrowed used lvalue `(*(&F1037_MOTION(this).yMotion)) + global`
makes pinned VC7.1 emit original **ordinal 100 `FLD [actor+0x54]`,
ordinal 101 `FADD [006583F8]`**. The selected entire case now
matches native GPR roles and **all 14 original physical PE call/global
fields**, rather than only instruction mnemonics.

| Native original 0x354 evidence | Verified |
| --- | ---: |
| Original PE CODE B/x86 | **1,203 /251** |
| Natural current C++ interior CODE B/x86 | **963 /251** |
| Original ordered mnemonic positions | **251/251** |
| Original GPR operand roles | **251/251** |
| Matching original instruction widths | 171/251 |
| Original calculated physical PE nonlocal targets | **14/14** |
| Native two x87 TEST+JP conditions | **both exact** |
| Real first/extra projectile IDs | **0x3E4/0x3E3** |

The tracked live one-parent original-PE verifier compiles **only the
current one changed partial original-shaped C++ parent**, SHA-checks
the independent full 81KB original PE and all 92 true afterRET
DIR32 jump-label partitions/199 literal sparse-map bytes, and
checks **51 genuine original game-state interiors** representing
**43,408 original native CODE B /9,434 native x86**, with
**9,434/9,434 matching original mnemonic and GPR roles**, **730/730
physical original PE nonlocal fields** and **1,759/1,759 nonrelocated
scalar immediate values**. Current normal source emits **35,569
CODE B /9,560 x86** plus genuine 567 DATA B, vs authentic whole
**81,539B /17,435 x86** and its original ESP frame `0x3A0`, saved
receiver EBP-0xAC; current incomplete source has `ESP 0x1E4` and
EBP-0x78. Many original actions and instruction/branch widths remain
unreconstructed. **The complete original giant remains NONEXACT;
new accepted whole original CODE bytes = 0B.**

Reproduce just the one affected game-source parent:

    scripts/repo-python scripts/verify-characterobject-current-recovered-f1068.py

Normal C++/OBJ/PDB/compiler artifacts, rejected wrong-FPU/return
sources and original PE measurements are in ignored
`.analysis/f1093-native354/` and `.analysis/f1068-boss-live-all-native/`.
No mass 979-function cold replay or original EXE mutation.
