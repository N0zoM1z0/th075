# F1083 — Native 0x34B (412B/85 x86), actual float-ground comparison and -40.0f stage velocity

The original SHA-pinned Japanese TH075 v1.11 game has one
`CharacterObject::Advance` at **0050A580**, containing **81,539
original CODE B /17,435 native x86**, plus genuine 567 separate
afterRET sparse-switch DATA bytes. F1083 replaces its former marker
`0x34B` with actual original gameplay. No inner state is a
separately exact original game callable; the 81KB whole remains
**NONEXACT**.

Original `0x34B` physically occupies **00512BA7..00512D43**,
**412B /85 x86**. The normal C++ source restores native
stage/frame-zero `0040FBB0` reset; signed +0x80 timer **99**;
status+0x7C reset; scale floats+0x1C/+0x20 set to 1.0;
all four alpha bytes set to 0xFF; signed +0xD8 zero and both
motion X/Y floats zero. It increases actual Y scale using original
**006590B4**, tests genuine actor Y against original **00658E80**,
then advances the actor X by signed-facing X velocity and moves Y
by **subtracting actual Y motion**. It reads original `0040FA30`
and conditionally expires the character through `0045B830`.
At actual stage **15**, frame zero, it sets genuine Y velocity to
**−40.0f**, the exact native bit-pattern `0xC2200000` at actor+0x54.

The original Y boundary is a real ordered x87 comparison:
`FLD [actor+0x48]; FCOMP [00658E80]; FNSTSW AX;
TEST AH,0x41; JNE skip-expiry`. The source C++ comparison preserves
this exact **unordered-FPU-aware** `TEST AH,0x41; JNE` lowering,
not a fabricated machine branch. All original field widths, actual
parent/actor pointers and original game helper calls are retained.

| Original native game action 0x34B | Verified |
| --- | ---: |
| Real original CODE/x86 | **412B /85** |
| Selected normal C++ case CODE/x86 | **311B /85** |
| Native mnemonic +GPR roles | **85/85 each** |
| Native instruction widths matching | 52/85 |
| Original physical PE external call/global fields | **6/6** |
| Original `TEST AH,0x41; JNE` | matched |
| Original stage-15 `-40.0f` bits | matched |

The live current parent verifier cold-builds the one changed normal
VC7.1 source under `/Od /Ob0 /Gy /GR- /GX- /GS /Zi`, then
independently reads and SHA-checks the **entire original 81KB PE**,
all 92 original DIR32 label-equivalence partitions and 199 real
sparse-index bytes. Every recovered state is compared by native
x86 mnemonic and GPR ordinal, each original physical nonlocal
REL32/DIR32 field calculated from the original PE and every
nonrelocated scalar literal checked.

After F1083 it verifies **42 genuine game state interiors**,
**34,539 original native state CODE B /7,513 original x86**,
**7,513/7,513 mnemonic and GPR roles**, **602/602 genuine PE
call/global fields** and **1,404/1,404 original scalar-immediate
positions**. Current partial normal C++ parent emits **28,444
CODE B /7,657 x86** with 567 afterRET DATA, but original full
CODE remains **81,539B /17,435 x86**. The original saved receiver
at EBP-`0xAC`, `ESP 0x3A0` frame and many still unrecovered game
states are not restored by this case. Selected parent has
EBP-`0x60`, `ESP 0x184`. **No new whole original exact CODE**;
original 979 accepted whole callables remain unchanged.

Reproduce the affected source only:

    scripts/repo-python scripts/verify-characterobject-current-recovered-f1068.py

All original PE field evidence, normal C++/OBJ/PDB compiler results
and historical prior state proofs reside under ignored
`.analysis/f1083-native34b/` and `.analysis/f1068-boss-live-all-native/`.
No direct byte patch, dummy registers, synthetic stack arrays or
979-unit cold replay were used.
