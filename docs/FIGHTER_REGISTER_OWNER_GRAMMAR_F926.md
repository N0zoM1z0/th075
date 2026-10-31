# F923/F924/F926 — Two original 58KB fighter register-phase blockers are not superficial lvalues

**Pinned Japanese TH075 v1.11, native complete game function 00543210**:
58,294 callable CODE B /16,471 x86, plus separately owned
943 postRET DATA B. The previously improved F917
natural VC7.1 parent emits **58,293 callable CODE B
/16,471 x86**, with all 16,471 mnemonics aligned,
but incorrect GPR roles and three real instruction widths.
The whole giant is **NONEXACT**; no internal case counts
as an independently callable exact game function.

## Original PE facts, independently re-decoded

The physical original state 0x59 begins at **00545109**
(whole function x86 ordinal **2198**) and its complete
native CODE interior is **356 B/95 x86**. The first three
original operands begin with:

    MOV EAX,[EBP-44h]
    MOVSX ECX,word ptr [EAX+62h]
    CMP ECX,1

The selected F917 source instead uses EDX/EAX for the first
two registers and starts the case with **19 different GPR-role
instructions**, the **first global register mismatch** in the
complete father. The 2,198 earlier register operand roles match
but earlier whole CODE/physical relocations are not thereby exact.

Native 0x63, beginning **00545ADE**, still has three
physically width-relevant `CMP …,0x96` operands:
whole x86 ordinal **2934 EDX (6 B)**, **2977 EAX (5 B)**,
**3000 EDX (6 B)**. Selected compiler emits instead
EAX (5 B), ECX (6 B), EAX (5 B). These are actual
source register-allocation issues, not merely one-byte
total-function deficit.

## New complete-father compiler experiments

F923 compiles **38 complete 58KB parent variants** across
three serial batches and a baseline. Source grammar hypotheses
use the real actor signed stage+0x62, frame+0x64, movement
float fields, real F00/F02 contact conversion and original
native call/control flow. Source alternatives include
`stage>1` versus equivalent `stage>=2`/reversed tests,
typed stage borrowed views, const read lvalues, signed short
float conversions, contact summand ordering, true compound
assignments, and real combined changes. Some meaningful
candidates change instruction widths or actual conditional
mnemonics *for the worse*.

Of the 38 source compiles, **36 retained the original
16,471-x86 full source count**, and two added actual x86
instructions. Every original-count source retains the
wrong first GPR role at ordinal 2198 and **at least 19
wrong 0x59 GPR-role instructions**; the best whole parent
still has **1,741** wrong register-role instructions.
No alternative moves the first mismatch later or fixes
the original three 0x63 CMP roles. Each full source
retains original-shaped 943 postRET DATA B and 1,863
total COFF field records. This is diagnostic geometry,
not proof of all physical PE targets for each alternative.

F924 separately compiles **24 complete** native-shaped
58KB parent variants, changing all four actual
opponent `OWNER+0x60` signed-short stage expressions
or individually changing one actual use. True source
value categories include const/volatile pointer reads,
C++ references, direct casts, pointer-index syntax and
typed borrowed stage member access. All 24 source objects
retain **58,293 CODE B/16,471 x86/1,863 COFF records /
943 DATA B**. **None** changes the compiler CMP EAX/ECX/EAX
sequence toward the original EDX/EAX/EDX.

These results reject an initially plausible simple
literal/source-member-category explanation for both
register phases. They do **not** prove a historical
original class type or that no more substantial
control-flow/real value-lifetime source could fix it.
The next useful hypothesis should address actual VC7.1
basic-block register phase and used owner lifetime
rather than repeating cast spelling. No fake locals,
register-forcing asm, target-byte grafts or cropped
case comparisons were introduced.

## Portable bounded verifier and private research receipts

The tracked
[`verify-fighter-register-owner-controls-f926.py`](../scripts/verify-fighter-register-owner-controls-f926.py)
regenerates F917's original-shaped whole source and
freshly compiles **ten representative complete giant
normal /GX- C++ controls** from both families. It
independently re-reads the original PE, checks the
whole 16,471 x86 ordinal sequence, first action0x59
GPR divergence, all three native mode63 CMP roles,
full CODE extent, COFF count and afterRET DATA extent.
The resulting ten representative full parents all
retain the original first register mismatch and three
native mode63 width positions. It explicitly allows
an equivalent C++ comparison expression to change
a conditional mnemonic for the worse; such candidates
are negative, not asserted to be original opcode matches.

    scripts/repo-python scripts/verify-fighter-register-owner-controls-f926.py

Complete C++ source/OBJ/PDB/compiler transcripts and
original PE receipts for the full **38 + 24** controlled
matrix remain in ignored local:
`.analysis/f923-fighter59-stage-grammar/` and
`.analysis/f924-mode63-stage-source/`,
with original/compiled summary JSON per batch.
The reproducible tracked ten-source verifier writes
`.analysis/f926-fighter-register-owners/verified-summary.json`.
No all-unit cold replay; **0 new whole exact functions /
0 new accepted CODE bytes**.
