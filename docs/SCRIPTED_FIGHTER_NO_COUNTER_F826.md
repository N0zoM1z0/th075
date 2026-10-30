# F826 — Three real counter-free native landings in the growing 46KB fighter

The pinned Japanese TH075 1.11 original fighter 005214B0
owns 46,755 complete callable CODE B, 13,230 original x86
and 901 separately owned after-RET jump DATA B. F825's
incomplete original-shaped source already had nine genuine
timer landings and the original ground boost 0x9E.

F826 adds three new, independently bounded native actions:
**0xA3 / 0xA4 / 0xA5**. Their actual original case extents
are **264 B /71 x86 /9 typed PE/COFF fields each**,
rather than the earlier 276-B/73-x86 timer family.
The physical PE confirms that these cases do NOT reset the
+0xF00 short trajectory counter; only the real initial
ground height -9/-10/-13, native position, x87 contact,
reflection and action2 transition are retained.
Natural tracked C++ in probes/FighterScriptedNoCounterF826.inc
preserves this exact behavioral distinction.

## Whole-function source re-verification

The targeted verifier regenerates the immediately prior
F825 original-backed parent, then compiles one updated
complete affected VC7.1 C++ function. Generated source
now contains **16,606 callable CODE B /4,396 x86**,
up from F825's 15,859 B/4,189 x86.
The original 46,755-B whole function remains incomplete.

Every newly inserted case matches all native original
71 instruction mnemonics, x86 sizes, positions, GPR
registers and nine true original call/global PE fields.
Across each of the three complete native interiors,
the **only two remaining nonrelocation byte differences**
are the original encompassing-giant long-JMP operand
at offsets 260/261. The source JMP also goes directly
to its own enclosing void-function epilogue, but the
original entire game function has a different final
CODE length. These two bytes are not hidden or counted
as independently exact callable CODE.

The newly compiled parent again independently checks all
nine original preceding 96/97/98/9A/9B/9C/9F/A0/A1
276-B/73-x86 timer case extents and nine physical PE
fields each (two actual parent-JMP bytes different per case),
the 243B/66-x86 0x9E ground boost and its eight native
PE fields, the complete 901B original afterRET packed
DATA and original saved-this frame EBP-0x10.
The common 46B native default getter still has
four GPR nonrelocation byte mismatches.

Selected affected parent only:

    scripts/repo-python scripts/verify-scripted-fighter-no-counter-landings-f826.py

The generated C++, compiled COFF/PDB and physical PE
receipts remain under ignored .analysis/f826-scripted-no-counter/.
**No whole 46,755B game function or split-case exact CODE credited,
and no accepted-unit cold replay performed.**
