# F815 — Original fighter 0x5F face-to-opponent state in a whole 46KB parent

A freshly built pinned VC7.1 source for the original TH075 scripted
fighter 005214B0 integrates the true second-switch action 0x5F
at physical PE 00523680..0052370F, **144 original CODE bytes and
44 x86 instructions**, with three real zero-addend original REL32
calls to 0040FA30 / 0040FAC0 / 0040FAC0.

The source reuses the tracked natural C++ owner-facing action
from probes/FighterFacing5FF620.inc with the **independently observed
original action values 0 and 1**. The real behavior checks the action
getter and a positive +0x4E0 resource count, then compares actual
this+0x44 and opponent(this+0x2E8)+0x44 float fields in two
independent x87 status tests, setting direction at this+0x66.
No fake temporaries, byte arrays or register forcing are used.

scripts/verify-scripted-fighter-facing-f815.py regenerates and verifies
the earlier F814 selected whole-parent source from tracked native
verifiers, adds the actual F620 case, and recompiles **the whole
affected parent**. The new source emits **10,409 callable CODE B /
2,672 x86**, compared with F814 10,280/2,630; the previous
32 native game actions, real 901B separately owned after-RET DATA,
and authentic 46B shared default/getter are rechecked in the same
fresh source object.

The complete 144B/44-x86 original action's mnemonic, instruction
width, control-flow shape, three physically typed original PE
fields and source field locations all agree. **It is not machine
byte exact in this still-incomplete parent:** 13 real saved-this
EBP displacement bytes are source EBP-8 vs original EBP-0x10,
and the two differing bytes in its final long JMP address are
the authentic **external encompassing giant epilogue** destination
relative to an incomplete parent. Neither type of byte is ignored
for whole-function acceptance. The original native function owns
46,755 callable CODE B and remains NONEXACT; no separate case
or jump table DATA receives callable CODE credit.

Targeted rerun:

    scripts/repo-python scripts/verify-scripted-fighter-facing-f815.py

Compiler source, COFF/PDB, original physical comparisons and the
generated receipt are under ignored .analysis/f815-fighter-facing/.
No all-unit cold replay was run.
