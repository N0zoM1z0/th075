# F1042 — Native stage/frame signed WORD pair in both complete 46KB/58KB Fighter sources

The original Japanese TH075 1.11 has original-authored complete Fighter
`Advance` functions at `005214B0` (**46,755B/13,230 x86**) and
`00543210` (**58,294B/16,471 x86**). Both remain NONEXACT.
F1040/F1041 made the currently best original-shaped ordinary VC7.1
C++ sources for these entire fighters Git-backed rather than merely
local ignored experiment artifacts.

The same pinned game independently establishes signed short animation
stage at fighter **+0x62** and frame at **+0x64**, and this borrowed
four-byte pair already has complete-function exact evidence in other
native units (`F1024`). These two giant parents previously still
reconstructed 19 (46KB) and 91 (58KB) signed-stage/frame expressions
through unrelated `S16`/`I16` raw field macros.

F1042 replaces those **110 real C++ source expressions** with
`F1024_PHASE(this).stageAt62` and `.frameAt64` inside the two
*complete*, still-unaccepted normal-shaped fighter source files.
There are no new dummy locals, layout claims for the containing
character, fake scope branches or forced original registers; the
source semantically names the original two adjacent independent WORDs.
The underlying borrowed view is never allocated or embedded as a
complete actor.

Both whole sources were cold built with pinned VC7.1 under Wine, and
verified independently against the actual original PE:

| Evidence | 46KB source | 58KB source |
| --- | ---: | ---: |
| Source-typed stage/frame references | 19 | 91 |
| Full generated original-shaped CODE bytes | 46,754 | 58,293 |
| Generated whole x86 count | 13,230 | 16,471 |
| Whole original external PE fields verified | 1,341/1,341 | 1,697/1,697 |
| Remaining original width errors | 5 | 3 |
| Remaining original GPR-role errors | previously nonexact | 1,741 |
| Actual afterRET DIR32 and literal DATA | 139/345B | 156/319B |
| Generated CODE **and** afterRET DATA vs former best object | **bitwise identical** | **bitwise identical** |
| Changed COFF symbol strings | 150 `$L` locals | 166 `$L` locals |

For both full objects all COFF physical field offsets, types,
addends and internal offsets are unchanged from the previous best
source. Every changed COFF symbol string is solely a VC7.1 synthetic
`$L...` **internal** label with the same actual native target;
none of the external symbol names, physical fields or target offsets
was allowed to change. The literal 345 and 319 afterRET game DATA
bytes are still checked by the original PE-aware verifiers.

Reproduce the two *affected original whole giants only*:

    scripts/repo-python scripts/verify-fighter-whole-46kb-pe-targets-f1026.py
    scripts/repo-python scripts/verify-fighter-whole-58kb-pe-targets-f1025.py

This is an exact-geometry-preserving **source semantic improvement**
in 110 real game operations, not new accepted original CODE.
`005214B0` and `00543210` remain NONEXACT; no inner states were
promoted to individual original functions, and no 979-unit full replay
was run.
