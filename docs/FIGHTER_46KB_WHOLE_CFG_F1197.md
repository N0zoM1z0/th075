# F1197 — Restore all 46KB native exits and the 18B reset scope

The complete tracked `005214B0` parent now reproduces all **1,522**
native direct branch destinations. The full comparison exposes and fixes
**56 ordinary exit targets plus three state-18B guard targets**.
The complete original remains **NONEXACT**, with **2,736 GPR positions /
five widths** unresolved; no original exact unit or CODE credit is added.

## Original control flow restored

The old F806 shared-getter fragment placed a `return` and label after
the switch. Its 56 ordinary switch breaks reached the extra skip JMP
at whole ordinal **13,224**, rather than the native epilogue at **13,227**.
The label now sits inside the switch after default's break. Ordinary exits
directly reach **0052CB4F**; only native JMPs **00521709, 00521891,
00521974 and 00521983** from states 0/2/4/5 enter the genuine getter at
**0052CB47**. Default retains its independent skip over that getter.
The original F806 include is preserved for historical reproduction.

State **18B** contains a distinct source-behavior error. Native jumps
**005272F2, 005272FD and 0052730C** all reach **00527346**, skipping
the counter increment, subaction-6 call and following writes to **+80/+7C**
when stage is not 7, frame is not zero, or signed counter +F00 is at least 2.
The old source instead reached **00527330**, executing the two post-call
field resets outside the actual guard. Those resets now belong inside
`stage==7 && frame==0 && counter<2`, after the increment and subaction call.
The observed instruction order is preserved without new checks or locals.

## Complete fresh comparison

| Original whole property | Pinned Japanese PE | Current normal C++ |
| --- | ---: | ---: |
| Entire callable CODE | 46,755B | **46,754B (-1)** |
| Ordered x86 instructions | 13,230 | **13,230** |
| Frame /saved-this | 0x138 /EBP-0x10 | **both agree** |
| EBP operand positions | 4,133 | **all agree** |
| Mnemonic /non-GPR operand debt | — | **zero /zero** |
| Direct branch destinations by native ordinal | 1,522 | **1,522/1,522** |
| CODE field destinations at native instruction/field positions | 1,352 | **1,352/1,352**, zero unknown references |
| Dense DATA target instruction ordinals | 139 | **139/139** |
| Owned after-RET DATA | 901B | **901B**, including 345 exact sparse bytes |
| Wrong GPR positions /instruction widths | — | **2,736 /five** |
| Complete original cold-exact acceptance | — | **NO** |

All **1,491** COFF records, including symbols, field geometry, addends
and local offsets, are identical before/after. The only changed candidate
bytes are in the 59 corrected jump displacements. The five width differences
remain whole ordinals **2,885 /2,908 /8,455 /8,986 /9,130**, in states
63, 1FD, 252 and 254. PE destination agreement does not establish original
absolute relocation offsets or whole byte equality while those widths differ.

The unchanged F1026 verifier cold-builds only this affected parent and
passes all **1,341 external PE targets, 11 CODE-local fields**, dense table
partitions and sparse bytes. The scoped local
`.analysis/f1197-46kb-whole-cfg/whole-audit.py` additionally diagnoses
every stack operand, non-GPR operand and direct/dense destination ordinal.
Its selected `tracked.obj`, complete before/after arrays, original 18B
policy, transitive source hashes and verified summary are preserved there.
The previous F1026 objects, PDBs, logs and receipts are retained under
`f1026-before/`. These are research receipts, not a new canonical gate.

Only this research parent includes the changed 18B fragment. No accepted
source pins, exact manifests, origin evidence or comparison infrastructure
change. Target/tracking, current summary, active handoff and whitespace
checks pass; no full CI, corpus replay or historical origin tests are run.
Coverage remains **982 exact functions /871,649 original CODE bytes**;
all 22 authored giants and all original 46,755B here remain pending.
