# F887 — Real original 2BF 473B complete source: only two enclosing-giant JMP operand bytes differ

Pinned original Japanese TH075 v1.11 resources/th075.exe:
full callable fighter 005214B0 is **46,755 native CODE B** with
**901 separate packed afterRET switch DATA B**. Original
physical action 2BF at 0052A05B..0052A233 is
**473 complete inner CODE B/138 x86/15 typed original PE fields**.

The source differs fundamentally from 2BE in its stage0 initialization:
the original actually writes short this+0x80=**0x63**, followed by
another real write of short this+0x80=**1**, *before* ResetAt453E20.
Removing the first real write generates nonnative opcode geometry.
At stage2 native sprite0x74 and sprite0x33D replace the earlier
0x73/0x33C; the two real float-to-signed-short C++ casts naturally
call original __ftol2 at original PE 006406AC, writing
this+0xF00 and +0xF02. Stage10 prepares action7, and stage11
uses true InitTrajectoryAt453E60(10.0f).

The new one-parent pinned VC7.1 /Od C++ compilation
generates **36,519 callable CODE B/10,301 x86**
(F886 36,061B/10,165x86). The actual 2BF inner case
compiles to **473 B/138 x86**, all original native
instruction mnemonics, sizes, relative positions, and
all fifteen physically typed PE operands:
[72,80,104,166,176,191,221,267,278,299,349,385,395,431,464].
Every real PE field offset, REL32/DIR32 type, zero addend,
symbol and original executable destination is checked.

**Unusually strong result:** after masking only the 15
physically identical 4-byte original/source relocation fields,
the entire 2BF inner case has **ZERO real GPR/stack nonfield
differences**. The *only* two remaining original differing
source bytes are case-relative +469/+470, belonging to the
whole still-incomplete fighter's long JMP operand pointing to
original far epilogue at 0052CB4F instead of the generated
closer epilogue. The case is not separately callable and is
NOT eligible for whole-function exact CODE credit.

Four whole-source variants were normally compiled:
the selected native source, the incorrect missing first
short+0x80 store, a wrong initialization value and a wrong
sprite kind. The false versions are rejected against
the original PE even when code size is equal.

The same new complete parent physically rechecks all
**62 preceding original game case interiors**, including the
1FD native CMP-width defect, 252/254 original PE field
shifts, 2BC/2BD/2BE, all five original afterRET 901B
packed jump tables and the common native 46B getter's
four genuine GPR operand bytes and three PE calls.

Reproduce only this affected giant:

    scripts/repo-python scripts/verify-scripted-fighter-2bf-f887.py

Source/COFF/PDB, alternate entire VC7.1 C++ sources and
real original PE receipts stay in ignored
.analysis/f887-scripted-followups/.
The 46,755B full fighter still remains **NONEXACT**.
No mass all-unit cold replay and no unearned CODE acceptance.
