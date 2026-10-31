# F909 — Action 0x58 does not explain the first native whole-fighter GPR phase

**Pinned Japanese TH075 v1.11, original callable fighter 005214B0**:
46,755 native CODE bytes / 13,230 instructions, plus separately owned
901 afterRET DATA bytes. The selected single normal VC7.1 source emits
46,754 CODE bytes / 13,230 instructions / 901 DATA bytes. **NONEXACT.**

The first native-versus-source *register-operand* disagreement
remains original PE **0052327A**, full x86 ordinal **2103**, precisely
the first instruction of native state **0x59**. Original begins
`MOV EAX,[EBP-10h]; MOVSX ECX,word ptr [EAX+62h]; CMP ECX,3`;
source begins `MOV EDX,[EBP-10h]; MOVSX EAX,word ptr
[EDX+62h]; CMP EAX,3`. The previous 2,103 x86 register roles
already match, but this does **not** establish exactness of the
preceding CODE/relocations.

**New control:** Instead of repeatedly editing only the original
0x59 body (F906), F909 compiles **27 distinct, complete** C++ father
versions with actual source variations in the **preceding original
0x58**. Each source still uses the real ten-projectile loop, actor
position, native counter conversion, stage 0/1 tests, genuine
GetNativeAction/SetAuxAction and original calls. Variations change
only real C++ condition/value expression forms, unsigned/signed
loop declaration, prefix/postfix increment and typed field
lvalues; no fake locals, assembly or target grafts.

All 27 successfully compiled with normal pinned VC7.1
`/Od /Ob0 /Gy /GR- /GX- /GS /Zi`. Whole COFF extents:

| Complete generated whole father | Variants |
| --- | ---: |
| 46,754 CODE B / 13,230 x86 / 901 DATA B | 26 |
| 46,756 CODE B / 13,232 x86 / 901 DATA B | 1 |

Every variant still emits **1,491 COFF references** (including afterRET).
18 entire source CODE arrays are byte-identical to the baseline.
Eight same-sized variants change genuine compiler-emitted bytes;
some change original preceding 0x58 conditional opcode or original
width geometry **for the worse** (at ordinals 2004/2005, 2081/2082,
2088/2089). The differently sized variant is not cropped.

**Crucial result:** Among the 26 ordinal-comparable whole fathers,
**zero** improve the original 0x59 entry GPR roles or the original
19 GPR mismatches within its entire 356-byte/95-instruction body.
The *best* complete father still has **2,736** wrong register-role
instructions, and **none** moves the first mismatch past
ordinal 2103. All original-sized and instruction-aligned versions
retain the five previously known width differences (some add two
worse differences); no one-byte total-length proxy is used.

Consequently, neither the previous 0x58 native-equivalent lexical
choices nor the F906 0x59 lexical choices explain the phase.
The next test should inspect the **source/compiler register allocator
at switch-label transitions** (and possibly a different source
control-flow topology), not assume a syntactic rewrite of 0x58
will repair global registers. This is a **bounded negative result**,
not a solved whole fighter. The native 22-giant backlog and full
function CODE-credit counts are unchanged.

Targeted reproduction (no all-unit cold replay):

    scripts/repo-python scripts/verify-scripted-fighter-pre59-register-phase-f909.py

Full compiler inputs/outputs and original-PE-backed disassembly
comparison receipts stay in ignored
`.analysis/f909-pre59-register-phase/`. The script also pins a
baseline sanity check against F901 and reports actual first
divergence, GPR role count, whole instruction geometry, and
afterRET data length for every compiled whole father.
