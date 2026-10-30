# F856 — Original 0x190 stage-3 sprite/animation and six native call targets

The SHA-pinned Japanese TH075 1.11 original fighter
at 005214B0 owns 46,755 callable CODE B and
901 separately owned original afterRET packed switch
DATA B. The real original 0x190 at 005273A2..0052747A
is **217 complete native interior CODE B /64 x86
/6 actual original PE REL32 call fields**.

The selected game C++ initializes genuine
stage/frame-zero counters and calls native 00453E20;
checks action completion through 0040FA30
and resets action0 through 0040FAC0.
At stage3/frame0 it sets the real
float owner member +0x314 to 1.0f,
emits native sprite kind **0x320**
through 00453A70 with observed game
coordinate bit patterns/facing byte,
starts original animation **0xFA**
through 0046D000, then calls
PrepareActionAt453D40(0).
At stage4/frame0 it sets the actual
state dword +0x7C to 1.

Five genuinely used complete-parent
source controls test native call order,
stage3 trigger, sprite kind and
actual float owner lvalue expression.
Wrong prep/start order can retain
the same 217B/64-x86 mnemonic geometry,
but swaps the real original PE CALL
destinations and is rejected by the
strict **physical six-field** native
target verification. A wrong sprite
kind/stage also produces genuinely
wrong source machine bytes.

One newly built full VC7.1 selected
parent now emits **25,337 callable
CODE B /6,987 x86**, from F855
25,135B/6,925 x86.
Every original source 190 x86 mnemonic,
instruction size, physical byte position
and all six original PE call targets,
kinds, addends and symbols match.
This is STILL **NONEXACT** CODE:
39 native nonrelocation GPR operand
bytes differ, plus two physical original
whole-function epilogue JMP displacement
bytes at +213/+214 of this case.
They are not classified as relocations.

The same new compiled parent rechecks
all seven preceding 136/186/187/188/
189/18A/18B complete original sources,
their honest real GPR mismatches, and
twenty earlier original C8..135
native case interiors/PE fields.
The common original 46B/16-x86
getter now **34/34 native nonrelocation
machine bytes equal plus three real
PE REL32 calls**. All five separately
owned packed afterRET switch tables
are reverified from current COFF.

Targeted reproduction:

    scripts/repo-python scripts/verify-scripted-fighter-stage-190-f856.py

Fresh whole C++, VC7.1 COFF/PDB, real
PE receipts and alternate call-order
source controls are retained in ignored
.analysis/f856-scripted-stage190/.
The original 46,755B whole function
remains NONEXACT; no split-case,
getter suffix or DATA earns accepted
whole callable authored CODE credit.
No mass cold replay.
