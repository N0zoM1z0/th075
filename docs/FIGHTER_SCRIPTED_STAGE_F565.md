# F565 — real scripted state actions inside the 46,755-byte fighter giant

**Original native Japanese TH075 1.11 and fresh pinned VC7.1 C++ evidence,
not a full original giant exact function.** SHA256 of original:
bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98.

Original CharacterMove giant 005214B0 contains 46,755 complete
native CODE bytes and 901 bytes of separate after-RET switch DATA.
All original CODE and DATA fingerprints are independently verified
before any new C++ source compile. The actual first-switch physical
DWORD entries for cases 6/7/8/9 delimit three real contiguous cases.

## A distinct script-state fighter, not a frame-advance actor clone

Other F548/F556/F563 fighter source models increment signed-short
frame counters and eventually call an actor virtual frame method.
This giant has a **different native source-level algorithm**:
it first gates x87 contact processing on signed stage +0x62 **greater
than 2**, not on current position +0x48 exceeding a threshold.
Contact changes the +0x54 floating velocity and tests the actual
+0x48 + +0x54 sum against original global 0065782C, with a true
early return on collision. It does **not** call vtbl[0] or increment
frame counters in these three whole original action bodies.

Then actual original per-action state and motion policies differ:

- **Action 6**: 96 x86 instructions /331 original CODE bytes. The real
  stage-four +0x54 float comparison with native global 00657D14
  conditionally issues native 0040FB40(5). A separate real query
  0040FA30 compares signed current action to owner +0x70; if equal
  it issues **0040FB40(11)**. If +0x62 == 3 and +0x64 == 0, it sets
  float motion (0.0f, 16.0f, 0.8f) and clears FLAG.
- **Action 7**: 83 native instructions /290 bytes. It calls
  **0040FAC0(9)** on matching action state, then sets motion
  (5.5f, 16.0f, 0.8f) and clears FLAG on the native stage-three/zero
  frame-state guard. There is no extra-stage callback.
- **Action 8**: 83 native instructions /290 bytes. It calls
  **0040FB40(13)** rather than action7's 0040FAC0(9), and
  initializes (-5.5f, 16.0f, 0.8f) with the same actual conditional
  flag clear. All native calls are confirmed at their original PE
  instruction ordinals; the shared signs and constants are not copied
  from another role's assumptions.

## Full native/COFF, one affected-only compiler TU

[The F565 original-backed C++ source verifier](../scripts/verify-fighter-scripted-stage-actions.py)
regenerates a single normal natural C++ switch using original
source-backed F545 actions 0..5, adds these three genuinely
different cases 6..8, and retains diagnostic-only marker stores for
other unimplemented cases. It compiles just this affected TU with
pinned MSVC 7.1 /Od /Ob0 /Gy /GR- /GX- /GS /Zi.

The selected object matches **all 262/262 full native case instruction
mnemonics, actual EAX/ECX/EDX allocation, x87 operand and branch
grammar, complete per-instruction byte lengths**, and **23/23 genuine
physical typed COFF call/global relocation fields** (9+7+7).
The entire independently native switch DATA layout matches:
**139 original-style physical DWORD COFF fields**, real repeated/default
target partitions, **345 byte-identical original sparse index bytes**,
and **901 separate post-RET DATA-layout bytes**.

    scripts/repo-python scripts/verify-target.py
    scripts/repo-python scripts/verify-fighter-boss-family.py
    scripts/repo-python scripts/verify-fighter-scripted-stage-actions.py

Fresh generated source, COFF object, PDB, compiler logs and summary
are retained under ignored .analysis/f565-scripted-stage-source/.
Full original instruction reconnaissance and negative source trials
are in .analysis/f563-125-127-fighter/ and
.analysis/f565-scripted-fighter/.

All **911 original inner case CODE bytes** remain within the still
unmatched **46,755-byte complete fighter giant**. There is no
independent 331/290-byte native function, no whole giant exact source,
no accepted split CODE/DATA, no machine-byte grafting, no all-unit
cold replay and no external Factory/Oracle receipt.
