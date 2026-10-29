# F593 — whole 33,293-byte CharacterObject boss now matches every instruction offset and native CODE/DATA layout

**Original Japanese TH075 v1.11 PE vs pinned MSVC VC7.1, one fresh ordinary C++ translation unit.** Native PE SHA256
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.

This is the first original-backed comparison of *the entire*
`004EBDA0` CharacterObject giant compiled with **all physically
nondefault original gameplay cases represented in normal C++ source**,
including the actual final default branch `GetStateAt40FA30()` rather
than the previous source-only diagnostic marker store. Original whole
CODE is **33,293 bytes** and original separate after-RET compressed
switch DATA is **438 bytes**. The compiled selected C++ object section
has **exactly 33,293 CODE + 438 post-RET DATA bytes**. Neither complete
original CODE nor its independent DATA is yet byte-exact; no Factory or
Oracle acceptance and no new whole/split original CODE credit.

## The entire original giant, not just a few convenient leaf routines

| Entire physical original-PE measurement | Original game executable | Fresh natural VC7.1 C++ |
| --- | ---: | ---: |
| Whole original CODE extent | **33,293 B** | **33,293 B** |
| Entire original x86 instruction count | **8,789** | **8,789** |
| Every instruction start offset and individual machine-code length | **8,789** | **8,789 matched** |
| Mnemonic at identical instruction ordinal | **8,789** | **8,783 matched** |
| Original after-RET switch DATA layout | **438 B** | **438 B** |
| Genuine typed physical COFF CODE references | **622** | **622** |
| Genuine `DIR32` after-RET jump-table fields | **60** | **60** |
| Original byte-identical sparse dispatch indexes | **198 B** | **198 B** |
| Original native COFF relocations, all zero addends | **682** | **682** |
| Whole CODE+DATA non-relocation bytes | **31,003** | **30,848 identical / 155 different** |

This was checked against all **33,731 contiguous original PE
CODE-plus-DATA bytes**, not a cropped source-object section. The
relocation-aware full-object comparator reports
**`mismatch`, not `exact`**, with 30,848 of 31,003 comparable bytes.
The exact *original source ELF/COFF* relocation count includes
**432 `REL32` and 190 `DIR32` fields in CODE**, plus **60**
additional post-RET `DIR32` switch targets, totaling 682. Each
COFF record is checked for the actual PE destination, one unique
source-symbol identity and zero addend. The 60 local jump-table
symbols are distinct from the 72 symbols referenced by the CODE;
all **132** names resolve consistently. This is genuinely global
CODE and DATA geometry, not a sample of a few short handlers.

Only **six machine instruction mnemonics** differ at the same
ordinal, and these are the previously independently checked three
read-only `MOV`/`FLD` reorderings at whole-function ordinals
**1062–1063, 1350–1351 and 2521–2522**. Each pair is two
three-byte instructions in a different order, preserving the
original computation's loaded values without reassigning the
original x87 stack. These are **not** accepted byte-exact
machine code. Their affected native instruction source order is
explicitly checked, never silently ignored.

Of 30,805 CODE bytes outside 622 real typed relocation fields,
**30,650** exactly match. The remaining **155 non-COFF bytes**
are at 139 native instruction positions: the above six instruction
swaps and source register allocations in just three whole
native action bodies. The contiguous source and original
8,789-instruction layout is otherwise byte-position identical.
This reveals *exactly* where more original source/lifetime research
will matter, without inventing byte grafts or considering an
entire-body exact comparison passed.

## Two newly strict native original action bodies

| Physical original game-action case | Complete native x86 roles | Original internal CODE bytes, uncredited | Original typed call/global COFF fields | Full original source-grammar result |
| --- | ---: | ---: | ---: | --- |
| **`0x3E4`** | **261** | **1,126 B** | **19** | **strict entire case** |
| **`0x3E5`** | **96** | **396 B** | **5** | **strict entire case** |
| **F593 new verified original gameplay** | **357** | **1,522 B** | **24** | **0 register/x87/branch/width differences** |

### `0x3E4`: native angle, x87 boundary gates and real owner-state timers

The genuine 261-instruction action initializes original signed angle
and random `00455580(0,360)-180`, stage0 dynamic polar speed, and
stage1 target angle through the **actual** `00483300` two-float
external geometry helper followed by native CRT `__ftol2`, not
a reconstructed game-owned helper. Four independent x87 collision
limits check real physical globals `0065786C`, `00659230`,
`006590A8` and `00658268`, with original `FCOMP/FNSTSW` flags and
native branch semantics. A real collision updates original
parent counters `+0xEFA`, `+0x3B6`, `+0x3B0`, and conditional
float `+0x36C`, including native double global `00659228`
and original float `00657478`. It invokes actual target
`0045B860(0x2E)`, `0045B830`, `0040FA30` and `0040FB40`
with native control-flow order.

Crucial original C++ source finding: writing the float expression
with natural lvalue ownership `PARENT_TARGET_Y +
gCollisionAt00657888 - *(&F32(0x48))` causes VC7.1 to emit
**original `FLD parent.y` before `FADD [00657888]`**. Writing
an apparently equivalent `*(&PARENT_TARGET_Y)` expression loads
the global first and gives a nonmatching source order. Using
actual member float lvalue dereferences for each of the four
boundary checks naturally restores the original three-member
owner preload order before `FLD` and `FSUB`.

This recovers **all 261 original GPR/x87/CFG/branch roles, all
1,126 original internal CODE bytes in length, every instruction
width and all 19 genuine typed physical PE/COFF records**, with
no machine byte patch, assembly or fake stack filler.

### `0x3E5`: native floating scale from two signed shorts

The genuine last nondefault handler has **96 native x86 instructions
and 396 original CODE bytes**, and five original call/float COFF
fields. It copies parent x into actor x with a raw DWORD
operation, zeroes actor y, sets real short `+0x8A=1`; initial
stage resets via true `0040FBB0`, sets both scales to **3.0f**,
sprite `0x4E2`, actor y offset **−80.0f** and owner signed
counter. When real parent short `+0x3A0` is positive, the two
scales use x87 **`FILD parent short; FIDIV actor short;
FADD ST(0),ST(0)`**, followed by actual float
`0065747C` and `0040FA30/0040FB40(9)`.

Writing source `float(parent)/short * 2.0f` yields exactly
that native FILD→FIDIV→FADD order; `2.0f*float(parent)/short`
puts the FADD before the native FIDIV, which is incorrect.
The genuine last case also has **two independent short JMP exits**
at its end: one after `SetStateAt40FB40(9)`, the other on
fall-through. The real source needs the distinct inner `break`
rather than relying on a combined exit.

The source produces **all 96 native original instruction roles/
396 bytes and five original typed COFF call/global fields**.
An independent negative control that compiled *just* `0x3E5`
without source for the neighboring last real game cases gave the
correct length but rotated the original EAX/ECX/EDX roles:
**the native register assignment requires the real adjacent
`0x3E3`/`0x3E4` compiler context**, not handwritten register
patches.

## Three explicitly nonexact whole source cases still need work

| Original case | Native original complete instructions / source-matched total byte width | Original PE/COFF fields | Source/PE GPR-operand mismatches |
| --- | --- | ---: | ---: |
| **`0x38D`** | 155 /570 B | 10 | **45** |
| **`0x38E`** | 87 /348 B | 6 | **64** |
| **`0x3E3`** | 200 /812 B | 17 | **24**, all confined to its first 31 instruction ordinals |

These *do* have natural C++ gameplay source and each complete original
case length, mnemonic and per-instruction width, but their actual
register allocation is not identical, so none is counted among the
56 strict source cases. The `0x3E3` first-31 difference is a
register cycle: from instruction 31 onward its entire native
x87/control/operand grammar is identical. `0x38D/0x38E` also
still contain register cycles; they should be tackled from real
original source compiler context rather than simply rotating
machine bytes. Their collective original CODE bytes are
**570+348+812 = 1,730**, all excluded from strict case sums.
The three pre-existing independent read-only `MOV/FLD` pairs
remain nonidentical under linker-masked byte comparison.

## Source counts and exact-credit safeguards

Previous F572–F592 verified **54 real whole native game-action
subranges** with 7,943 original x86 roles, 29,852 original inner
CODE bytes and 562 PE-typed physical fields. This round adds the
two genuinely strict original 3E4/3E5 action bodies: **56**
strict case bodies, **8,300** native source-instruction roles,
**31,374** original internal CODE bytes and **586** true typed
case call/global fields. Other three cases are explicitly
nonexact *even though source and original x86 counts, widths,
whole source CODE and jump layout all match*.

Tracked normal C++ source:
[`probes/CharacterObjectActionsF572.cpp`](../probes/CharacterObjectActionsF572.cpp).
New complete giant code/data source checker:
[`scripts/verify-characterobject-whole-geometry-f593.py`](../scripts/verify-characterobject-whole-geometry-f593.py).
The verifier reads the original pinned entire PE, compiles **one
and only one selected affected MSVC7.1 C++ TU** under
`/Od /Ob0 /Gy /GR- /GX- /GS /Zi`, reruns prior F592's strict
54 complete case checks, verifies all 8,789 entire original
opcode positions and lengths, all 682 original physical COFF
zero-addend fields and their real native destinations, then
checks exactly the documented 155 nonrelocation byte differences
and all five last native original action ranges. It runs an
independent whole-source PE/COFF comparator over **33,731
original CODE+DATA bytes**, never just function CODE with
trailing switch DATA misclassified as instructions.

### Affected-only reproduction

```bash
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/verify-characterobject-whole-geometry-f593.py
scripts/repo-python scripts/verify-characterobject-five-complex-actions-f592.py
scripts/repo-python scripts/validate-tracking.py --require-target
```

All fresh VC7.1 original-shaped selected COFF/PDB, full 682-field
physical original PE proof, full original whole-object comparator
and strict summary are retained under ignored
`.analysis/f593-characterobject-whole-source/`;
source trials, negative controls and byte-difference logs remain
under `.analysis/f593-characterobject-finalcases/`.
**THE ORIGINAL WHOLE 33,293-BYTE FUNCTION REMAINS NONEXACT.**
This is not a cold all-unit replay and it yields neither an
independent exact original case CODE unit nor a whole giant
Factory/Oracle acceptance receipt. The official **943 exact
functions and 862,726 original CODE bytes remain unchanged**.
