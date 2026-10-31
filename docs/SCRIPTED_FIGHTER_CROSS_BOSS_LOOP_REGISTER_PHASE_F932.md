# F932 — The identical native 0x59 register-phase source lead reproduces in a second giant

Pinned original Japanese TH075 v1.11 fighter at **005214B0**:
**46,755 complete callable CODE B /13,230 x86**,
plus independently owned **901 afterRET DATA bytes**.
This is a DIFFERENT original actor from F931's 58,294-B
fighter at 00543210. Both giant functions remain NONEXACT.

## Native PE original and whole VC7.1 evidence

The actual original 005214B0 action 0x58 runs from
**005230A5 to 0052327A**, **469 B/135 x86**;
the immediately following original action 0x59 spans
**0052327A..005233DE**, **356 B/95 x86/16 true
zero-addend PE/COFF external fields**.

F901 selected normal pinned VC7.1 whole source
emits **46,754 CODE B/13,230 x86**, with five
later wrong instruction widths. Its actual original
0x58 predecessor is still strict in x86 mnemonic
and width geometry. Its 0x59 source instead allocates
EDX/EAX where native expects EAX/ECX, causing
**19 wrong GPR-role instructions and 19 native
nonfield/nonshared-tail operand-byte differences**.

As in the independent F931 58KB original, change ONLY
the preceding real 32-bit ten-shot C++ loop to:

    int burst=0;
    while (burst++<10) {
        SpawnDirectedAt453A70(0x3E4,I32(0x44),I32(0x48),1,1);
    }

This naturally invokes the same original game call ten
times. The local loop counter has no subsequent consumer.
The complete new source STILL emits **46,754 B/13,230
x86/1,491 COFF fields/901 afterRET DATA B**.

| Actual whole original-shaped 46KB father | F901 selected for-loop | F932 postincrement-while control |
| --- | ---: | ---: |
| Whole generated CODE B (native 46,755) | 46,754 | 46,754 |
| Whole generated x86 (native 13,230) | 13,230 | 13,230 |
| Original action0x58 mnemonic differences | **0** | **1, local 55** |
| Original action0x58 width differences | **0** | **2, local 55 and 59** |
| Original action0x59 native CODE B / x86 | 356 /95 | 356 /95 |
| Original action0x59 GPR-role differences | **19** | **0** |
| Original action0x59 nonfield/nonshared-tail byte differences | **19** | **0** |
| Actual original action0x59 PE-targeted fields checked | 16 | 16 |
| Actual original shared epilogue exits verified | 2 | 2 |
| Entire original giant exact | NO | NO |

The two original action0x59 external JMPs target native
**0052CB4F**, the genuine shared function epilogue.
The source reaches that epilogue through its real
adjacent shared-exit jump block. F932 verifies both
actual source edges before excluding precisely their
four-byte jump *displacement* fields for local
diagnosis. These are NOT true native CODE byte matches
or a new independently callable function.

The updated source REGRESSES the real native 0x58
loop at x86 ordinal 55 (original first JMP, new
MOV) and width ordinals 55 and 59. That additionally
changes the complete parent width-error ordinals
from the previous five original differences
**[2885,2908,8455,8986,9130]** to **[2023,2027,
2885,2908,8455,8986,9130]**. None can be cropped,
ignored or counted as an exact original source.
F901's strict predecessor remains the selected
whole-source baseline.

**New cross-actor conclusion:** the preceding C++
loop lowering, not merely the 0x59 actor-stage literal
or float lvalue, can account for ALL native next-case
register differences in BOTH independently compiled
46KB and 58KB fighters. It is meaningful compiler
register-phase evidence, not a complete historical
source solution. Future work should recover a
preceding source grammar preserving both original
0x58 emitted CODE and original 0x59 register phase
simultaneously. Never introduce fake register storage,
manual assembly or target byte grafts.

## Exact scope and reproduction

Portable tracked original-PE-backed verifier:
scripts/verify-scripted-fighter-following-bounce-f932.py.
It regenerates the latest native F901 whole source
from tracked F899/F901 code, compiles ONLY TWO
complete VC7.1 original-shaped giant parents,
reads the original hash-pinned 46,755 native
CODE bytes, compares all 13,230 ordinal
instructions, every original case 0x59 physical
zero-addend target among all 16 source COFF fields,
both external case 0x59 source/native true
epilogue JMP targets, all remaining nonfield
case operands, the actual preceding 0x58
mnemonic/width penalties, and the unchanged
whole compiled 901B afterRET DATA and source
COFF field mapping.

    scripts/repo-python scripts/verify-scripted-fighter-following-bounce-f932.py

Its two full C++, OBJ/PDB, logs and verified
receipt stay in machine-local ignored
.analysis/f932-scripted-next-bounce/. The
independent five-source exploratory cross-check
is in .analysis/f932-other-boss-loop-phase/.
No full 979-unit cold replay, no original EXE
modification, and **0 original exact CODE
accepted**.
