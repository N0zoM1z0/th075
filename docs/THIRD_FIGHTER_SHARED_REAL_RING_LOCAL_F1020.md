# F1020 — Native 82KB fighter CODE/frame/receiver recovered from one real counter lifetime

The SHA-pinned Japanese TH075 v1.11 original complete
004AC040 fighter contains **82,796 callable CODE B /
22,721 x86 instructions**, followed by 1,126 independently
owned afterRET jump DATA bytes. The tracked
[ordinary complete original-shaped PARTIAL C++](../probes/FighterWhole004AC040F1020.cpp)
now emits exactly **82,796 CODE B /22,721 x86**, native
compiler frame **0x720**, and saved receiver
**EBP−0x64**. These whole-function geometry values
are genuinely recovered, but the complete callable
is still NOT byte exact.

## Original native evidence identifies the extra 4-byte local

F1019 restored ALL 22,721 original mnemonic ordinals,
but compiled CODE exceeded native by six bytes, frame
was 0x724 instead of0x720 and saved this was EBP−0x68.
The strict complete PE/instruction audit identified only
**14 original instruction width differences**, with
the entire six-byte positive width imbalance caused by
two local instructions at original x86 ordinals2829/2830:

| Original physical opcode | Original operand | F1019 previous | F1020 corrected |
| --- | --- | --- | --- |
| MOV native x86 ordinal2829 | EBP−0x80, 3B | EBP−0x84, 6B | **EBP−0x80, 3B** |
| FILD native x86 ordinal2830 | EBP−0x80, 3B | EBP−0x84, 6B | **EBP−0x80, 3B** |

Investigating the original native *real loop counter
initializations*, not historical prose, revealed the
first upstream owner mismatch in actual game state2DB.
At original whole x86 ordinals**19050** and **19084**,
both genuine stage11 **36-shot sprite0x385 ring loops**
initialize the SAME signed 32-bit loop-local slot,
**EBP−0x40**. In the prior C++ each loop had its own
separate declaration of int shot, yielding generated
EBP−0x40 for the first and EBP−0x44 for the second.
That extra real C++ variable allocated one 4-byte slot,
shifting the four genuine 2E6 loop counters,
the later four 302 loop counters, all deep FILD
scratch slots, the saved receiver and the whole frame.

The [corrected genuine stage11 source](../probes/FighterThirdBossRingSharedCounter2DBF1020.inc)
declares **ONE actual int shot** in the stage11/frame0
branch and resets that very same variable to zero
before EACH independent 36-shot loop. The two rings
still have original separate speed5.0f and10.0f
and genuine signed-facing×8 world-X and native
float Y global00659460. This is historical original
C++ variable OWNERSHIP semantics, not artificial stack
padding, ASM, a dummy local or forced register choice.

## Whole original 22,721-x86 proof

The [independent complete-fighter verifier](../scripts/verify-third-fighter-shared-ring-counter-f1020.py)
fresh-builds TWO TRACKED ENTIRE original-shaped normal
VC7.1 82KB fathers, prior F1019 and real F1020,
re-reads the independently SHA-pinned Japanese PE,
and compares all **22,721 positional original
mnemonics, widths and GPR roles**. It checks both
original 2DB loop-local EBP instructions, actual
native frame and saved this position, real 2DB,
2EF and 2F0 typed PE call/global fields and
several preceding/following native source cases.
All **151 original afterRET DIR32 case labels and
522 original nonfield DATA bytes** are checked.

| Entire original-shaped PARTIAL fighter | F1019 prior | F1020 real owner |
| --- | ---: | ---: |
| Compiled whole CODE B | 82,802 | **82,796** |
| Compiled whole x86 count | 22,721 | **22,721** |
| Wrong original mnemonic ordinals | 0 | **0** |
| Wrong original width ordinals | 14 | **12** |
| Signed original width delta | +6B | **0B** |
| Wrong original GPR-role instructions | 6,958 | **6,958** |
| Compiler stack frame | 0x724 | **0x720** |
| Saved this EBP slot | −0x68 | **−0x64** |
| Second genuine 2DB shot loop local | EBP−0x44 | **EBP−0x40** |
| Native x87 FILD scratch at ordinal2830 | EBP−0x84 | **EBP−0x80** |
| Whole original byte exact | NO | **NO** |

**Do not conflate whole geometry with complete exact CODE.**
Twelve actual original width roles remain wrong because
some source register choices differ even though positive
and negative widths now cancel. Across the complete
function **6,958 original GPR operand-role instructions**
still differ, including original 2BE's 125 wrong
case-local GPR roles. Entire original external PE/COFF
field positions and many intra-function JMP displacements
also must match before any accepted whole original callable
CODE credit. F1020 does NOT change config/matches.csv,
match units or officially accepted authored coverage.

Reproduce ONLY the two affected original-shaped
whole-function sources:

    scripts/repo-python scripts/verify-third-fighter-shared-ring-counter-f1020.py

True PE receipts and normal VC7.1 C++/OBJ/PDB plus
compiler logs are retained under ignored
.analysis/f1020-third-native-proof/
and .analysis/f1020-third-ring-owner/.
F1019's independent original 2EF/2F0 PE proof
remains valid.

**Zero new accepted original whole callable GAME CODE B.
No 979-unit corpus-wide cold replay.**
