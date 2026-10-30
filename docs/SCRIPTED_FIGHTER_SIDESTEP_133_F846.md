# F846 — Native 0x133 side-step recovers all original 46B getter register bytes

The pinned original Japanese TH075 v1.11 giant fighter at
005214B0 has 46,755 callable native CODE bytes plus
901 separately owned original packed switch DATA bytes.

F846 adds the original 0x133 at 005268A9..005269B6:
**270 complete interior CODE B /78 x86 /six true typed
PE global/call fields**. Authentic falling/ground logic
checks stage0/FLAG, corrects height via 00658058,
resets the actual stage/resource short and performs the
native animation0x1D at stage5. At stage8 the original
signed direction byte this+0x66 is multiplied by **70**,
converted to float through genuine FILD scratch, then
added in that precise order to the existing float X
at this+0x44. The source uses ordinary meaningful C++
and actual original game state, not fabricated ASM/locals.

Four complete affected-parent VC7.1 source variants
independently checked original x87 expression ordering,
true signed multiplication constant and animation
stage. The selected one matches every native x86
mnemonic, instruction size, PE field offset/kind/zero
addend and source register operand. The *only* original
nonrelocation byte differences are the two authentic
whole-fighter epilogue relative-JMP bytes at source
0x133 offsets 266/267. Reversing the float sum yields
18 additional genuine source byte differences; changing
the stage or multiplier produces other native mismatches.

The tracked verifier regenerates and verifies the
preceding F845 current whole parent, then compiles
one updated full VC7.1 C++ translation unit. The
generated callable source grows **22,476 to 22,731 B**,
and x86 **6,135 to 6,211**. All previous 17 fully
source-backed C8..D2, 12C..12F and 130/131
native original cases and their physical PE fields
are rechecked in the same compiled object.

**Important positive context effect:** adding genuine 0x133
recovers the entire original 46B/16-x86 shared
default/getter: **34/34 original nonrelocation bytes
now match**, and all three physical native PE REL32
calls have correct targets. All FIVE original packed
afterRET tables totaling 901B are again independently
checked from the new source COFF, never counted as CODE.

Targeted reproduction:

    scripts/repo-python scripts/verify-scripted-fighter-sidestep-133-f846.py

Generated complete original-shaped source, pinned VC7.1
COFF/PDB, source alternatives and native PE receipts
are saved in ignored .analysis/f846-scripted-133-launch/.
The actual original 46,755B whole callable fighter
remains NONEXACT. None of these case interiors,
the getter suffix or switch DATA earns whole-function
exact authored CODE credit. No mass cold replay.
