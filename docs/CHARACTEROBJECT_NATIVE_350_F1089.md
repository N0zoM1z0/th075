# F1089 — Native 0x350 1,263B action with real 0x364 eight-shot loop and four parent guards

The SHA-pinned Japanese TH075 1.11 original contains ONE original
authored `CharacterObject::Advance` at `0050A580` with **81,539 CODE
B /17,435 native x86** and a separate 567B afterRET sparse switch.
The current one-switch normal VC7.1 C++ parent remains incomplete,
and is **not byte exact as a whole original game callable**.

F1089 replaces its old `0x350` marker with genuine normal C++
source recovered from original game PE interval
**00514048..00514537: 1,263 native CODE B /273 x86**.
The state initializes original motion, scale, opacity and stage
counters on stage/frame zero, computes the genuine parent+0xF0C
angle, actor+C8 multiplier and Y-motion x87 expressions, preserves
original signed +0xD8 timer with a ceiling at 140, handles native
parent/grandparent health windows and original parent action `0x2C1`
conditions, and performs actual action transition, alpha fade and
parent+0x36C vertical motion correction.

It uses a **real eight-shot C++ loop**, storing `float(shot*45)` in
parent+0x314 and spawning object ID **`0x364`** through original
`00453A70`. Unlike the neighboring original `0x34E` and `0x34F`,
its independently native stage-zero parent-action combinations are
**`0x192/4`, `0x260/4`, `0x261/4`, `0x262/4`**. These source
literal values cannot be inferred from identical native mnemonics
or matched external call destinations; they are independently
validated original scalar immediates.

The same tracked `verify-characterobject-current-recovered-f1068.py`
compiled **the entire one-switch current partial parent** under
pinned normal MSVC7.1 `/Od /Ob0 /Gy /GR- /GX- /GS /Zi` and
independently read and SHA-checked actual original PE bytes.
It verifies every real state ordinal's mnemonic, GPR role, external
PE REL32/DIR32 instruction field and genuine original game target,
nonrelocated scalar literal, original **92 physical DIR32 case-label
equality partitions** and **199 literal sparse-index bytes**.

| Original native action `0x350` | Verified source |
| --- | ---: |
| Original native CODE and x86 | **1,263B /273** |
| Current generated inner C++ CODE/x86 | **1,041B /273** |
| Native mnemonic positions | **273/273** |
| Native GPR-role positions | **273/273** |
| Physically original nonlocal PE fields | **18/18** |
| Original motion/parent/projectile literals | checked |

The live complete-parent original-PE verifier now audits **47 genuine
original game-state interiors**, totaling **40,671 native CODE B /
8,838 x86** with **8,838/8,838 matched native mnemonic/GPR
positions**, **692/692 original physical call/global PE fields**
and **1,636 native nonrelocated scalar-immediate positions**.
The selected source function emits **33,457 CODE B /8,972 x86**,
with 32,636B of generated recovered case-interior source. This is
still far from the full original **81,539 CODE B /17,435 x86**, with
many remaining diagnostic marker handlers and mismatched original
whole stack/branch widths. **Original 81KB whole exact CODE added:
0B; no cropped case is independently accepted as a callable.**

Reproduce only the changed original-shaped whole parent:

    scripts/repo-python scripts/verify-characterobject-current-recovered-f1068.py

Fresh normal C++/COFF/PDB/compiler and actual original PE receipts
are retained under ignored `.analysis/f1068-boss-live-all-native/`.
No target mutation, assembly-byte transplant, synthetic register
lifetime or full 979-unit cold replay was used.
