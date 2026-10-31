# F1004 — Original 2E5 mode-controlled dual shots, complete native GPR phase

The pinned Japanese TH075 v1.11 original fighter 004AC040 owns
**82,796 callable CODE B/22,721 x86**, with **1,126
afterRET switch DATA B**. The tracked
[normal VC7.1 C++](../probes/FighterWhole004AC040F1004.cpp)
remains a PARTIAL original-shaped father, not a complete
native exact function: original receiver EBP−0x64 and frame0x720
are not reconstructed.

Original case 2E5 occupies **004BD017..004BD314**:
**765 original CODE B/199 x86/14 physical zero-addend
PE/COFF target fields**.

Original PE independently shows stage0/frame0 ResetAt453E20,
clear of original shorts F00/F02/F04/F06, then F08 =
signed mode global **006714D0**+2. Signed stage 5..10
and F08>0 decrements F06. If F06 exceeds 3−signed mode,
two original sprite **0x387** shots fire: angles F02×5
and F02×5+180 with real signed facing×16 SHL/FILD,
**FSUBR world X at +0x44**, float Y at +0x48 plus
original PE global **0065836C**, original signed facing and
layer1. F02 increments, while F06<−30 resets F06=10 and
decrements F08.

Animation completion uses 0040FA30/0040FAC0(0).
Actual 00455580 random draw [60,120] minus signed mode×20
sets short +0x516. Stage4 resets F06=10; stage5 prepares
action5; stage11 positive F08 triggers auxiliary9; stage13
increments F04 and triggers auxiliary11 while F04<13.

The [ordinary C++ source](../probes/FighterThirdBossCadence2E5F1004.inc)
naturally reproduces **all 199 native mnemonic, x86 width AND
GPR operand roles** with pinned VC7.1, no artificial locals,
asm, stack padding, forced registers or target-byte grafts.

The bounded [verifier](../scripts/verify-third-fighter-native-cadence2e5-f1004.py)
freshly compiles TWO ENTIRE original-shaped PARTIAL 82KB
parent sources (F1003 marker and F1004 real source). It checks
all 199 original positional mnemonic/width/GPR roles, **all
14 actual typed PE/COFF destinations**, four previous native
2C0–2C3 cases (their **555 previously correct GPR roles**
and **56 PE fields**), **151 native afterRET DIR32 labels**
and **522 original nonfield DATA B**.

| Whole original-shaped partial father | F1003 prior | F1004 genuine |
| --- | ---: | ---: |
| Partial CODE B | 64,060 | **64,810** |
| Partial x86 | 17,559 | **17,756** |
| 2E5 source B/x86 | 15/2 marker | **765/199** |
| Wrong native mnemonic/width/GPR | n/a | **0/0/0** |
| Correct original 2E5 PE fields | marker | **14/14** |
| Prior 2C0–2C3 correct GPR roles | 555 | **555** |
| Partial compiler frame | 0x46C | **0x47C** |
| Whole original 82KB callable exact | NO | **NO** |

Internal source opcode matches do not earn full original GAME
CODE credit: native parent still has wrong receiver EBP,
frame, many unsourced cases and absolute/relative relocations.

Run only the two affected partial parents:

    scripts/repo-python scripts/verify-third-fighter-native-cadence2e5-f1004.py

VC7.1 compiler source/OBJ/PDB and original PE evidence
are retained in ignored .analysis/f1004-third-native-proof/
and .analysis/f1004-third-2e5/.

**New accepted original whole callable CODE/function: zero.
No all-979-unit cold replay.**
