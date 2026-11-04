# F1129–F1132 — Four original 0x3E3..0x3E6 tail actions; real hit/meter policy, 82 PE-verified strict interiors

The SHA-pinned Japanese TH075 1.11 executable has **one** independently authored original `CharacterObject::Advance` at `0050A580`, **81,539 original whole CODE B /17,435 native x86**, followed by **567 original afterRET switch DATA bytes**. F1129–F1132 reconstruct four *distinct physical game-state interiors* inside the same ordinary pinned-VC7.1 **NONEXACT whole parent**, not four newly exact standalone game functions. Preexisting dirty C++ for the tail was inspected and continued, including a substantive original-control-flow correction.

## Actual native original gameplay

**0x3E3** (original `0051D70F..0051DAE8`, **985B/200 x86**) starts facing+0x66=1, stage-zero scale/opacity/motion and signed +0xD8 random degree `Random(0,360)-180`, with +0xDA speed 15. Stage zero decrements/clamps +0xDA to minimum 3. Original `0040FB70` uses native signed angle and scaled speed `00659090`; stage one uses true `00483300` atan2 relative to actual grandparent position plus `00657888` Y offset, `00657828` angle conversion and original CRT `006406AC`, then invokes another `0040FB70(angle,20.0f)`. Four real independent x87 X/Y grandparent-distance tests compare against **0065786C/00659230/006590A8/00658268**. On hit, it calls `0045B830`, increments original grandparent+0x366 hit byte up to two, otherwise increments its native +0x2D0 score by **0x4E20** and calls authentic `0045B860(0x2E)`. It continues original X/Y motion and `0040FA30` completion/`0040FB40(1)`.

**0x3E4** (`0051DAE8..0051E01F`, **1,335B/261 x86**) shares actual facing, original two polar callbacks, genuine random angle and four grandparent hit-bound comparisons. Its hit behavior is *not* the same as 3E3: original parent+0xEFA increments, real `0045B860(0x2E)` and `0045B830` happen, then it processes independently native signed grandparent+0x3B6 cooldown and +0x3B0 meter, including decrement by 5, +10 meter increments, clamp to 1,000, real +0x39C flag and a physical **double-precision** comparator at `00659228` controlling grandparent+0x36C float growth and a **900.0f** fallback. The first real C++ source incorrectly placed grandparent+0x3B0 recovery in an exclusive `else` after +0x3B6; the actual PE branches **continue through +0x3B0 policy even when +0x3B6 was greater than 5** and decremented. Removing that `else` restores both real game behavior and **261 original ordered mnemonic/GPR positions**, without padding or an invented helper.

**0x3E5** (`0051E01F..0051E215`, **502B/96 x86**) follows the original parent X coordinate, forces actual Y=0 and signed +0x8A flag, initializes scale 3.0f, opacity, original sprite id **0x4E2**, -80.0f rotation+0x28 and retains parent signed health at own+0xD8. It expires when parent health reaches zero, otherwise calculates both scale floats from **`float(parentHealth)/nativeInitialHealth*2.0f`** using original signed `FILD/FIDIV`, increments native angle+0x30 with true `0065747C`, and performs original action-completion transition `0040FB40(0xA)`. The initial C++ generated 95 x86; recovering a *genuine second terminal return branch* restores full **96/96 original mnemonics, GPR roles and x86 widths**.

**0x3E6** (`0051E215..0051E3F4`, **479B/105 x86**) checks parent action **0xD1/0xD2** and own stage below 2; calls original `0040FB40(2)` when needed. Each frame it follows actual parent X and Y+physical global `00657888`, initializes stage-zero original scales and opacity, subtracts native `006590BC` from scale X/Y, adds real `0065747C` to orientation+0x30, fades alpha by **12** in stage 2, expires on `0040FA30`, and invokes `0040FB40(1)` on stage 2/frame zero. This is genuine C++ gameplay with all **105/105 original mnemonics, 9/9 original physical PE external fields and 20 original scalar immediates**, but its normal generated C++ currently has only **30/105 original GPR roles** and **103/105 original widths**. It remains explicitly **PROVISIONAL**, not in the strict cohort.

## Original whole-parent native evidence — no false byte acceptance

| Original game-case interior | Native CODE B /x86 | Current C++ B /x86 | Original mnemonic/GPR | Width match | Physically correct PE | Scalar immediates |
| --- | ---: | ---: | ---: | ---: | ---: | ---: |
| 0x3E3 | **985 /200** | 981 /200 | **200/200** each | 199/200 | **17/17** | **31** |
| 0x3E4 | **1,335 /261** | 1,331 /261 | **261/261** each | 260/261 | **19/19** | **38** |
| 0x3E5 | **502 /96** | 502 /96 | **96/96** each | **96/96** | **5/5** | **16** |
| 0x3E6 — **PROVISIONAL** | **479 /105** | 481 /105 | **105/105** mnemonic, **30/105** GPR | 103/105 | **9/9** | **20** |

The 3E3 and 3E4 full mnemonic/GPR sources differ from original by **one six-byte-vs-two-byte JNE at native ordinal 43 each**, reflecting real remaining branch-width debt. No manual `JMP` byte inflation or acceptance mask was applied.

The selected `scripts/verify-characterobject-current-recovered-f1068.py` now cold-compiles **only this one affected 81KB original-shaped C++**, independently rereads the SHA-pinned original PE, checks **92 genuine DIR32 postRET jump-target equivalence classes and 199 literal sparse bytes**, and compares original machine mnemonic/GPR ordinals, physical COFF field/kind/PE-calculated destinations and original nonrelocated scalar values for **82 STRICT native case interiors**: **75,260 original CODE B /16,090 original x86**, **16,090/16,090 original mnemonic/GPR positions**, **1,246/1,246 native physical PE fields** and **2,964 scalar positions**. Another **eight genuine cases**, including 3E6, are *GPR-provisional*, and `0x391` with two unsolved x87 PE fields remains separately uncredited.

This entire selected C++ emits **81,559 CODE B /17,434 x86**, compared with original **81,539 B /17,435 x86**. The current compiler frame `ESP 0x3A4` and saved receiver `EBP-0xDC` are **not** original `ESP 0x3A0`/`EBP-0xAC`; original branch distances, local stack ownership and GPR phase differ. The 20-byte code excess and one native instruction deficit are not evidence of exactness. **Original whole function remains NONEXACT; newly accepted whole-original game CODE = 0B; previous 979 independently accepted whole functions untouched.**

Reproduce **only the affected partial original-shaped whole parent**:

    scripts/repo-python scripts/verify-characterobject-current-recovered-f1068.py

Rejected mutually exclusive meter logic, earlier missing 3E5 return, real Japanese PE field receipts and ordinary VC7.1 compiler OBJ/PDB evidence retained under ignored `.analysis/f1130-native3e5-continuation/`, `.analysis/f1131-native3e3/` and `.analysis/f1068-boss-live-all-native/`. No 979-unit replay or original-EXE patch.
