# F1088 — Real native 1,216B action 0x34F, third parent-action family and eight 0x363 shots

The pinned Japanese TH075 v1.11 original has ONE original
`CharacterObject::Advance` callable at `0050A580`: **81,539 native
CODE B /17,435 x86** followed by separate authentic 567B afterRET
switch DATA. F1088 restores original native inner action
`0x34F` at **00513B88..00514048**, **1,216 original CODE B
/263 x86**. The selected whole C++ remains partial and NONEXACT.

This original case has the same ordered 263-mnemonic/operand-width
family as native `0x34E`, but different real parent game-state
conditions, separate jump-table entry, physical float-to-int scratch
slots and object ID. Actual game gameplay maintains the signed
+0xD8 frame timer, resets native status/motion/scale and four opacity
bytes, calculates parent-relative actor X/Y from genuine globals
0065989C/00657F74/0065835C, checks the actual fighter+0x324
health and native +0x3A0 status, advances the signed timer by 5
up to 140 and responds to original `0x2C1/2` parent stage.

The distinct real native state-zero branch is triggered by
**parent `(0x194,4)`, `(0x263,5)` or `(0x264,5)`**, rather than the
`0x34E` case's `(0x195,4)`, `(0x1F4,14)`, `(0x1F5,14)`.
It performs the authentic **eight-iteration C++ trajectory loop**:
sets parent+0x314 float `float(shot*45)` and calls real
`00453A70` with game projectile **ID `0x363`**, actual actor X/Y,
parent facing and a real final 1 argument. Afterwards it preserves
original action/expiry, stage-1 fade and original native parent
+0x36C adjustment through 006592A4 and `00453D40`.

The original Japanese PE was read directly before reusing the C++
family. All 263 native opcode mnemonics, register positions,
actual parent-trigger immediate values, physical nonlocal call/global
fields and native 0x363 object ID were checked against the freshly
compiled **whole** source. No register forcing, partial byte patch,
ASM, fabricated stack local or marker gameplay was introduced.

| Real original 0x34F | Selected C++ original-shaped game case |
| --- | ---: |
| Original CODE/x86 | **1,216B /263** |
| Native compiled inner CODE/x86 | **1,004B /263** |
| Original mnemonic and GPR roles | **263/263 each** |
| Native original instruction widths matching | 193/263 |
| Genuine physical original PE nonlocal call/global fields | **18/18** |
| Original three parent action conditions | **0x194/4, 0x263/5, 0x264/5** |
| Projectile ID / angle step | **0x363 /45**, verified |

The live original-PE verifier cold-compiles **only the current one
partial whole C++ game callable**, verifies the independently
SHA-pinned complete Japanese 81KB original, all 92 original DIR32
jump-label equivalence partitions, all 199 native sparse index
bytes, each original recovered case's instruction mnemonics and
GPR roles and all native calculated physical PE call/global fields
and nonrelocated scalar immediates.

After F1088 it now covers **46 authentic original game-state
interiors**, totaling **39,408 original native CODE B /8,565
native x86**, with **8,565/8,565 original mnemonic and GPR
positions**, **674/674 physical original PE external fields** and
**1,588/1,588 original nonrelocated scalar immediates**.
The selected incomplete normal C++ parent emits **32,425 CODE B /
8,701 x86** plus 567 original afterRET DATA; saved receiver
EBP-0x70 and `ESP 0x1C4` differ from authentic original
EBP-0xAC and `ESP 0x3A0`. The entire original 81KB game still has
many unreconstructed states, stack width and branch geometry debt.
**Whole original remains NONEXACT; newly accepted whole original
GAME exact CODE = 0B**, the 979 existing exact whole callables are
unchanged.

Reproduce **only the affected whole game parent**:

    scripts/repo-python scripts/verify-characterobject-current-recovered-f1068.py

Pinned original PE, compiled normal VC7.1 COFF/PDB/logs and native
physical fields retained under ignored `.analysis/f1088-native34f/`
and `.analysis/f1068-boss-live-all-native/`; no full-979 replay.
