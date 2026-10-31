# F889 — Independent 248B Scene destructor, 29 genuine mixed free-owner lifetime sources

Pinned Japanese TH075 v1.11 source attribution:
independently authored Scene virtual destructor
0043B0B0, **248 complete original callable CODE B /
75 x86 /12 true typed PE call/data fields**.

Original physical temporary slots from its actual PE:

| Live value in original destructor | Native EBP |
| --- | --- |
| texture pointer read from scene+8 | -0x14 |
| scalar deleting receiver | -0x10 |
| free parameter from scene+0x4C | -0x18 |
| free parameter from scene+0x50 | -0x1C |
| free parameter from scene+0x54 | -0x20 |

The current normal VC7.1 baseline has matching whole
248B/75-x86 mnemonic/size/position geometry and all 12
physical original PE fields, but uses texture/deleter
EBP-0x20/-0x1C and three free parameters in the wrong
-0x18/-0x14/-0x10 source arrangement. It correctly
matches only **191/200 original nonrelocation bytes**.

F889 tests a distinct live-source allocation hypothesis:
the historical three actual free parameters may consist of
a **two-element cleanup aggregate plus one independent
named live pointer**, or a **single aggregate element plus
two separately named pointers**, rather than the three-field
aggregate or all-three-named forms previously disproved.
For each actual original member+0x4C,+0x50,+0x54,
the generated C++ assigns the genuine pointer to its
owned variable and actually uses that value in free().
No inert or padding locals and no hand-written assembler.

The 29 full normal pinned VC7.1 /Od /GX sources include
the original three-field aggregate baseline, **24** actual
1+2/2+1 free-owner combinations across four
meaningful declaration sites (after/before each other,
before texture delete, before clock call), and **four**
register/volatile real-live pointer alternatives.
The actual volatile declarations qualify the pointer
rather than the pointee, so none fails an unrelated
CRT free qualifier-conversion error.

All **29 complete** C++ destructors compile to exactly
**248B/75 original x86/12 original physical PE
field locations**, with every field's type, source
callee, zero addend and true original Japanese PE
destination still correct. Original clock value update,
texture delete, three CRT frees and base destructor
are all retained.

The native comparison is decisive:

| Entire real source model | Original nonrelocation equality |
| --- | ---: |
| Baseline three-field owner | **191/200 B** |
| All 28 mixed 1+2/2+1 actual pointer ownership models | **189/200 B** |

All mixed variants retain the wrong texture/deleting
receiver slots **-0x20/-0x1C**, regardless of the
actual free-owner declaration order or live pointer
qualifiers; the physical original requires
**-0x14/-0x10**. The mixed variants introduce two
additional true stack-operand byte mismatches in
the first CRT free at native offsets +146/+149,
so the original-size source match is **worse**.

The original 248B function remains nonexact and no
canonical authored exact function/byte is added.
This rejects a legitimate original-source lifetime
hypothesis rather than claiming a shorter or cropped
original match.

Reproduce ONLY this complete independent small function:

    scripts/repo-python scripts/verify-scene-mixed-owner-slots-f889.py

All 29 generated C++, normal VC7.1 OBJ/PDB, compiler
logs, stack-role summaries and strict original PE
receipts remain under ignored
.analysis/f889-scene-mixed-free-owners/.
No mass cold replay.
