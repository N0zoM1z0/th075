# F1014 — Native 82KB fighter default and separately owned shared epilogue

The SHA-pinned Japanese TH075 v1.11 original fighter at 004AC040
owns **82,796 whole callable CODE B /22,721 original x86**,
followed by 1,126 independently owned afterRET jump-table DATA B.
The [tracked growing VC7.1 C++ partial father](../probes/FighterWhole004AC040F1014.cpp)
is still NOT the complete native callable: original receiver
EBP−0x64, 0x720 frame, unsourced cases and entire game CODE
physical relocations differ.

The original executable's late action switch is independently
verified from its actual 151 postRET DIR32 local label fields.
Actions 31B and 31C are the actual last distinct handlers;
many other numeric actions map to a **shared default handler**
instead of unique real game states.

Original physical default at **004C037D..004C03A7**
contains **42 CODE B /13 x86**. Original control flow calls
the real animation getter **0040FA30**, compares its
signed short return to native actor+0x70, calls setter
0040FAC0(0) when equal, then JMPs to the shared exit;
otherwise it makes the second original 0040FA30 getter
call and falls through. The normal native C++ contains
a genuine if/else, not an arbitrary g_FighterProbeMarker=0
write. Two independent legitimate if/else bracing
spellings compiled the same native 42B/13x86 original
mnemonic, width and GPR-role sequence. A third source
without else fails its native jump layout and is not
selected.

Critically the **004C03A7** destination is the start of
the separate original common epilogue, **not** an afterRET
jump-table case label. It contains **exactly 5 original
CODE B /4 instructions**:

    pop esi
    mov esp, ebp
    pop ebp
    ret

The complete original callable ends at 004C03AC, where the
1,126B afterRET DATA begins. The original action is
validated up to the epilogue start, and the full 5B
epilogue is validated separately; no cropped compare,
invented table label, or shared epilogue double-counting
was used.

The [bounded original PE verifier](../scripts/verify-third-fighter-default-tail-f1014.py)
fresh-compiles TWO tracked ENTIRE original-shaped PARTIAL
VC7.1 fathers: F1013 marker versus F1014 real default.
It verifies **all 13 physical original default mnemonic,
width and GPR roles**, all **3 genuine zero-addend PE
external targets**, the separate 4-instruction epilogue,
the preceding 303 and 31B/31C authentic source cases,
and all **151 real afterRET DIR32 table labels plus 522
nonfield original DATA bytes**.

| Whole original-shaped PARTIAL father | F1013 old | F1014 genuine |
| --- | ---: | ---: |
| Compiled partial CODE B | 72,707 | **72,739** |
| Compiled partial x86 | 19,938 | **19,950** |
| Actual default source B/x86 | marker 10/1 | **42/13** |
| Wrong native default mnemonic/width/GPR | unaligned | **0/0/0** |
| Default original PE target fields | marker | **3/3** |
| Separate native shared epilogue B/x86 | 5/4 | **5/4** |
| Prior 303/31B/31C native roles | matched | **matched** |
| Compiler partial frame | 0x584 | **0x584** |
| Entire 82KB original callable exact | NO | **NO** |

Reproduce only the two affected full-PARTIAL-parent builds:

    scripts/repo-python scripts/verify-third-fighter-default-tail-f1014.py

The original physical PE receipts and compiled normal VC7.1
C++/OBJ/PDB and logs remain in ignored
.analysis/f1014-third-native-proof/
and .analysis/f1014-third-default/.

**No new accepted exact original whole callable functions or CODE.
No all-979-unit cold replay.**
