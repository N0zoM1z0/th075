# F1115 — Authentic original 0x386, 914B/195 x86: absolute X distance and 12 random 0x387 projectiles

**Historical F1115 checkpoint:** the current parent also restores [F1116 genuine 0x387](CHARACTEROBJECT_NATIVE_387_F1116.md), which supplies the real spawned projectile behavior. Original 386 195/195 x86 and 22/22 PE fields remain verified; 68-state/69,930B whole-source dimensions below are the prior snapshot.

The SHA-pinned Japanese TH075 1.11 game has **one** original `CharacterObject::Advance` at `0050A580`, 81,539 original CODE B /17,435 native x86 plus genuine 567 afterRET switch DATA B. F1115 reconstructs real inner original action **`0x386` at PE `0051B21D..0051B5AF`, 914 CODE B /195 x86** in the still-incomplete giant C++ parent. It is not a new independently exact callable.

At entry, real original X/Y bounds `0065925C/00659258/006583B4/00658374` and signed parent+0x3A0 loss trigger original `0045B830` expiry. Stage/frame-zero initializes real `0040FBB0` motion, countdown/status/opacity and scale 1.0, native X motion **3.0f** and Y motion zero. Stage **1** uses the original `00455580(0,4)` random helper; its signed `FILD` result is multiplied by native **006590B4** and added to a genuine **double-precision 006583B8** global. The original resulting X scale bits are copied to Y scale without a float conversion. Then the original absolute-float helper `00412D90` compares `abs(actorX-grandparentX)` against native **0065786C**, and on the actual x87 threshold branch stops X speed, resets scales to 1, calls parent `00453E60(5.0f)`, and advances action `0040FB40(2)`.

Every frame the game advances facing-relative actor X and adds Y motion. On original `0040FA30` completion it invokes parent `00453E60(10.0f)` and performs a genuine **12-shot C++ loop spawning native `0x387`** through parent `00453A70`: Y is **`float(RandomBoundaryAt00455580(0,320))`**, and X is native `actorX + 00658264 - float(RandomBoundaryAt00455580(0,80))`. The original signed actor facing and 1 are passed, then `0045B830` expires the action. Native stage 2/frame zero transitions via `0040FB40(1)`.

## A real original PE x87 loading-order correction

The first full-parent normal VC7.1 C++ matched **195/195 original mnemonics**, but X-coordinate construction loaded the **global first**, giving `FLD [00658264]; FADD [actor+0x44]`. The original PE physically has ordinal **163** `FLD dword ptr [actor+0x44]`, ordinal **164** `FADD dword ptr [00658264]`. Its floating-point relocation was therefore assigned to the wrong original instruction, and original GPR/width matches were only **193/195**. Replacing the source operand with the genuinely borrowed actor X lvalue `(*(&F1037_POSITION(this).xPosition))` restores native `FLD actor; FADD global`, both GPR/width positions and all native PE targets, without assembler, fake variables, byte grafts or a forbidden relocation mask.

| Real native original 0x386 evidence | Current ordinary C++ parent result |
| --- | ---: |
| Original case CODE length | **914B /914B generated** |
| Ordered x86 instructions and mnemonics | **195/195** |
| Native GPR-role positions | **195/195** |
| Native original x86 instruction widths | **195/195** |
| Physical original PE external field positions/types/destinations | **22/22** |
| Real nonrelocated scalar immediates | **40/40** |
| Real native spawned object and 12-shot count | **`0x387`, 12** |

The live one-parent verifier cold-compiles **only the affected current whole partial C++ parent**, checks the independently pinned original entire 81,539-byte CODE, genuine 92 postRET DIR32 partition classes and 199 sparse bytes, then verifies **68 strict original inner game cases**: **65,153 original CODE B /13,972 native x86**, **13,972/13,972 mnemonic/GPR roles**, **1,064/1,064 physical PE fields** and **2,579 nonrelocated scalar immediates**. Another seven genuine source-backed states are still GPR-provisional.

The incomplete C++ emits **69,930 CODE B /14,966 x86** against original **81,539B /17,435 x86**, with different frame/stack ownership and missing original game cases. The original **entire 81KB callable remains NONEXACT, newly accepted whole-function CODE = 0 B**.

Reproduce only the changed giant parent:

    scripts/repo-python scripts/verify-characterobject-current-recovered-f1068.py

Rejected wrong-x87 variant, native COFF/PDB compiler logs and original PE physical-field receipts are retained under ignored `.analysis/f1115-native386/` and `.analysis/f1068-boss-live-all-native/`. No 979-unit replay.
