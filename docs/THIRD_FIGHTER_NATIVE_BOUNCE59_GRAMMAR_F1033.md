# F1033 — Whole 82KB fighter's native 0x58/0x59 register boundary

The pinned Japanese TH075 1.11 `004AC040` is **82,796 original
callable CODE bytes / 22,721 x86 instructions**, followed by 1,126
separately owned jump-table/data bytes. The selected normal-compiler
F1020 complete source keeps the original 0x720 frame, saved receiver,
full CODE length and ordered instruction mnemonics, but remains
**NONEXACT** (12 wrong whole x86 instruction widths and 6,958 GPR-role
positions). This is source-generated evidence, never exact source credit.

At native `004ADD25..004ADEFA`, action **0x58** is a complete 469B/
135-x86 region; its original mnemonic, width and GPR roles agree with
the selected compiled parent. Its neighboring **0x59** at
`004ADEFA..004AE05E` is 356B/95 x86 with 16 genuine original
physical external PE fields. The normal current parent has all 95
mnemonics and widths but **19 wrong GPR-role positions**, starting
immediately at the `0x59` prologue. The mismatch cyclically renames
GPR owners EAX/ECX/EDX in the first stage-3 branch. Prior F1021
tried changing the real 0x58 burst loop: a postincrement variant
corrected the following 0x59 phase only by breaking the original 0x58
body. That regression is not an acceptable source fix.

## New entire original-shaped C++ experiments

The tracked `verify-third-fighter-bounce59-grammars-f1033.py` compiles
**15 entire normal VC7.1 /Od fighters** from F1020, modifying only
actually used fields/expressions of the native `0x59` game behavior.
It independently reads the SHA-pinned original PE, checks whole-body
x86 ordinal mnemonics/widths/GPR roles, the complete original 0x58
and 0x59 region geometry, the real 16 PE call/global fields for
unchanged-byte-width source variants, and all 151 genuine afterRET
DIR32 table slots plus 522 literal data bytes. Cases with a changed
instruction mnemonic/width **do not receive claimed PE target
identity for unaligned source instruction fields**.

| Actual C++ category | Entire compiled CODE/x86 | 0x59 wrong width/GPR | Whole wrong mnemonic/width/GPR |
| --- | --- | --- | --- |
| Unmodified F1020 parent | 82,796 / 22,721 | 0 / 19 | 0 / 12 / 6,958 |
| Float `+=` on live +0x30 | 82,796 / 22,721 | **2 / 20** | 0 / **14** / 6,959 |
| `+=` on +0x54 instead | 82,796 / 22,721 | 0 / 19 | 0 / 12 / 6,958 |
| Both compound assignments | 82,796 / 22,721 | 2 / 20 | 0 / 14 / 6,959 |
| Commuted float addition | 82,796 / 22,721 | 0 / 19 | 0 / 12 / 6,958 |
| Typed `F32(0x54)` field/condition | 82,796 / 22,721 | 0 / 19 | **2** / 12 / 6,958 |
| Readonly pointer, short array, signed stage alias, reversed condition, const float reference | 82,796 / 22,721 | 0 / 19 | 0 / 12 / 6,958 |

All 15 complete compiles retain **0/0/0 original 0x58 mnemonic/
width/GPR defects**. Fourteen alternative field-expression spellings
neither repair the following 0x59 GPR phase nor improve whole
source bytes. In particular, the real +0x30 compound assignment
creates extra genuine width defects; it is not an improvement even
though the complete generated CODE length stays at 82,796B.

The preserved, selected `F1020` source is unchanged. A promising
next explanation would involve real source-level register lifetime
spanning two states, rather than a local spelling tweak that
maintains the same compiler allocation. No assembler, fake locals,
forced register allocations, edited target bytes, cropped state
comparison, or 979-unit mass replay was used.

Reproduce only the affected whole boss C++ research set:

    scripts/repo-python scripts/verify-third-fighter-bounce59-grammars-f1033.py

Ignored original-source variants and independently measured results
are under `.analysis/f1033-third-59-grammar/`.
**No newly exact whole callable and no new accepted original bytes.**
