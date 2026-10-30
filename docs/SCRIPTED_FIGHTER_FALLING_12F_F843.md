# F843 — Original 12F 207B falling state, not other actor's 288B finish

The pinned Japanese TH075 1.11 fighter at 005214B0 owns
46,755 original callable CODE B and 901 separate afterRET
jump DATA B. F842 reconstructed current actor's real
12C/12D/12E source. F843 adds the next original action
12F, physically bounded by 00526646..00526714.

The selected original is **207 complete CODE B /59 x86 /
six physically typed PE/COFF fields**. This is NOT the
other original actor F654 12F, which is 288B/82 x86.
The selected original PE independently proves these C++
game parameters: transition to state 2, prepare native
animation **0x1B** at stage **1**, real x87
height subtraction at 00658058 and ground
test at 0065782C, and **no +0xF00
counter clear**. The source naturally uses
the prior F842 normal gameplay C++ with
these independently verified actor parameters.

A targeted verifier first reconstructs and physically
verifies the F842 parent, then cold-compiles only the
entire affected VC7.1 fighter. Callable source grows
**21,910 to 22,102 B** and x86 **5,966
to 6,023**. All 59 original native instructions,
widths, positions, register roles and six
actual original zero-addend typed PE field locations/
call/global targets match.

The original 12F has only two real nonrelocation
byte differences at native case offsets 203/204:
the complete original-game epilogue long JMP
relative displacement. The source return goes
directly to the generated incomplete parent epilogue.
These two bytes are not waived or marked exact.

The newly compiled parent independently rechecks
ALL FOUR original 12C/12D/12E/12F complete
physical case interiors (207/219/207/207 B),
all 24 actual PE calls/globals, all ELEVEN
previous C8..D2 source-backed physical native cases,
and all FIVE original packed afterRET tables
in the genuine separate 901B DATA region.

The 46B native shared default retains correct
EBP-0x10 and three original REL32 calls
but four true nonrelocation GPR operand bytes
10/12/16/19 remain wrong in the longer parent.
Do not reuse the shorter F841 native-default
34/34 source result.

Reproduce only the affected whole fighter:

    scripts/repo-python scripts/verify-scripted-fighter-falling-12f-f843.py

Source, pinned VC7.1 COFF/PDB and native PE
receipts are in ignored .analysis/f843-scripted-stage12f/.
The original 46,755B whole function remains NONEXACT;
no split case or other callable CODE credited and no
mass cold replay.
