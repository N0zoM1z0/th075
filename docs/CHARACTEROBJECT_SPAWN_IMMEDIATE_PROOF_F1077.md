# F1077 — Genuine game projectile IDs: first 0x339 then fifteen 0x33A, plus 1,321 native immediate checks

The Japanese TH075 v1.11 independent original has ONE original
`CharacterObject::Advance` callable at `0050A580` of **81,539
CODE B /17,435 native x86**, followed by genuine 567B afterRET
switch DATA. This document corrects a previously wrong C++ gameplay
literal in three still-NONEXACT original game case interiors:

| Original native game action | Native case CODE/x86 | Actual source after correction |
| --- | ---: | --- |
| `0x328` | 1,824B /435 | First `0x339`, then fifteen `0x33A` |
| `0x329` | 1,729B /413 | First `0x339`, then fifteen `0x33A` |
| `0x32A` | 1,729B /413 | First `0x339`, then fifteen `0x33A` |

These three original states each invoke `00453A70` **sixteen times
in one physically unrolled section**. Their original spawn `CALL`
addresses, machine-code mnemonics, width and register allocations
are unchanged when the C++ first argument is wrong. The earlier F1074
source incorrectly supplied `0x33A` to **all sixteen** calls.
Re-reading the original PE's `PUSH` immediate at the actual native
call ordinals (for 0x328: 212..422 step 14; 0x329/32A: 190..400
step 14) proves the original first object ID is **`0x339`**, then
exactly **15 `0x33A`** IDs. All three selected C++ cases have now
been corrected. This changes genuine game behavior while preserving
fully natural C++ control flow; it is not a synthetic opcode patch.

This also exposed a blind spot in relying solely on **all native
original mnemonic/GPR and all original PE external fields**: all
of those previously matched despite the wrong projectile ID because
these `PUSH` immediate bytes are *not* relocation fields. The tracked
live one-parent verifier now checks **non-relocated original scalar
immediate values at their actual original x86 ordinal** as well as
opcode mnemonic, GPR roles, original physical REL32/DIR32 targets,
afterRET jump partition and literal sparse index bytes. Jumps and
physical call/global relocation fields are independently verified,
not confused with scalar literals. It additionally asserts for each
of these three cases the original 16 unrolled `00453A70` call sites,
**initial `PUSH 0x339` and fifteen `PUSH 0x33A`** sequences, and
both genuine `00455580` random-coordinate calls.

A fresh cold build of **only the affected complete one-switch partial
C++ parent**, under original VC7.1, passes **1,321 non-relocated
original scalar immediate x86 positions**, across **38 genuine
recovered game state interiors /32,592 native original CODE B /
7,100 native x86 mnemonic and GPR positions**, plus **573/573
physical original PE external call/global fields**, the original
**92 afterRET DIR32 label equality partitions** and **199 sparse
literal data bytes**. All 38 cases remain original-shaped C++
*interiors*, not 38 independently exact original functions.

Current normal partial source remains **26,974 generated CODE B /
7,252 x86** plus 567 afterRET DATA versus original **81,539B /
17,435 x86**, and the original whole callable is **NONEXACT** due
to missing original game cases and stack-frame/branch-width debt.
Original whole GAME CODE newly accepted exact: **0B**. The wrong
literal was corrected, not disguised by a loosened acceptance mask.

Reproduce only the changed one large game function:

    scripts/repo-python scripts/verify-characterobject-current-recovered-f1068.py

Original PE, actual normal C++/COFF/PDB and literal checks remain
under ignored `.analysis/f1068-boss-live-all-native/` with earlier
F1074 original-state physical target proofs. No mass cold replay,
original EXE modification, assembler or independent case credit.
