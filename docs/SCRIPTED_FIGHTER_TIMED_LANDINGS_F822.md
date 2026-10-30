# F822 — Four complete native timed landing cases with only parent-JMP differences

The pinned Japanese TH075 1.11 original 005214B0 fighter has
46,755 whole callable CODE bytes, 13,230 x86 and 901 separately
accounted original after-RET packed switch DATA bytes.
F821's current normal VC7.1 incomplete parent emitted 13,282
callable CODE B/3,486 x86 with the original 0x91 arc case.

F822 integrates **four complete physical original timed landing
states** into one freshly compiled affected parent:

| Native game state | Whole original interior CODE | Original physical PE/COFF fields | Remaining native machine-byte differences |
| --- | ---: | ---: | --- |
| 0x96 | 276 B /73 x86 | 9 | 2 final enclosing-parent JMP operand bytes |
| 0x97 | 276 B /73 x86 | 9 | 2 final enclosing-parent JMP operand bytes |
| 0x98 | 276 B /73 x86 | 9 | 2 final enclosing-parent JMP operand bytes |
| 0x9A | 276 B /73 x86 | 9 | 2 final enclosing-parent JMP operand bytes |

Total **1,104 original gameplay CODE B /292 x86 /36 true
zero-addend typed native PE calls/globals** source-backed in
one actual whole C++ parent. The tracked natural source variants
in probes/FighterScriptedLanding96F822.inc and
probes/FighterScriptedLandingSiblingsF822.inc retain the actual
original animation-progress x87 FADD/FCOMP at 0065747C/006583B4,
original contact/ground corrections, reflection +0x490 using
double native global 006583E8, original action state 0/2
transitions, true short counter +0xF00 and actor-specific initial
heights -9/-10/-13. The entire game function is void and these
cases' native final branches go directly to its epilogue, so
natural C++ return emits that real CFG, without dummy source locals
or hand-written x86.

## Whole-parent physical proof

The tracked verifier first regenerates and physically validates
the immediately previous F821 source, then builds the affected
complete VC7.1 parent from tracked F631/F633 real C++ with actual
original PE-derived case parameters. Its source now emits
**14,326 callable CODE B /3,770 x86**, versus
13,282 B/3,486 x86 in F821, and preserves the original
901B after-RET packed switch DATA geometry.

Each of the four new source cases has **all 73 original x86
mnemonics, instruction sizes and positions exactly equal**,
and all nine native original physical PE field positions,
relocation types, zero addends, original targets and compiler
symbols independently verified. In each case every physically
comparable nonrelocation byte matches except two bytes of
the original last enclosing-giant long JMP operand. The
original game epilogue is at 0052CB4F; the incomplete
parent's actual epilogue is closer. These two genuine
relative operand bytes per case are NOT masked for acceptance.

The newly compiled parent also rechecks the earlier 0x91
288B/78-x86/12-field arc action (still 37 real unmasked
operand bytes wrong in longer context), all three original
8C/8F/90 289B/80-x86/8-field landings
(each with 55 genuine nonrelocation byte differences),
and the native 0x63 source with its REAL original
ordinal48 COFF operand one byte out of alignment.
The current saved-this EBP-0x10 original role remains
natural; the F806 46B default/getter still has four
real GPR operand byte differences 10/12/16/19.

Selected reproducible verification:

    scripts/repo-python scripts/verify-scripted-fighter-timed-landings-f822.py

Generated full C++, COFF/PDB and original PE evidence
are stored in ignored .analysis/f822-scripted-timed/.
The enclosing original fighter remains NONEXACT.
No internal case or separate jump-table DATA is credited
as an independent callable whole authored game function;
no accepted-corpus mass cold replay was run.
