# F1146 — Native 0x346 status 2/4 transition

The pinned Japanese original `0050A580` remains one NONEXACT whole
callable. Its `0x346` interior is `00511D25..005123B9`, 1,684 CODE
bytes /365 x86 instructions; it is not an independent exact unit.

Original `00512229`, case ordinal 271, is a `JE` to ordinal 275,
entering the stage-2 test when status +0x7C equals 2. Otherwise the
next comparison admits status 4. The previous natural C++ used
`status != 2 && status == 4`, sending that same JE to ordinal 283
and skipping the transition for status 2. The corrected expression
is `(status == 2 || status == 4) && stage == 2`; it invokes the
native action-3 transition and returns for either admitted status.

The one-parent verifier cold-built only the affected complete C++
under pinned VC7.1. All 17,435 whole-function mnemonics and all
1,834 direct native branch destinations were compared. The known
branch-target debt decreased from 13 to 12 without a new mismatch;
82 strict interiors retain 16,090 mnemonic/GPR matches, 1,246
physical external PE fields and 2,964 scalar immediate positions.
The selected source still emits 81,560 CODE bytes against original
81,539, with unresolved original frame, stack, GPR and x87 debt.
New accepted whole original CODE bytes: zero; 979 exact units remain.

Reproduce only this parent:

    scripts/repo-python scripts/verify-characterobject-current-recovered-f1068.py

Before/after native disassembly, the previous source, original selected
COFF and verifier receipt are retained under ignored
`.analysis/f1146-native-cfg/`. No full-corpus replay was run.
