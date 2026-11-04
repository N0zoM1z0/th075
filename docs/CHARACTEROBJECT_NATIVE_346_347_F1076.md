# F1075/F1076 — Original 365-x86 action 0x346 restores following 101-x86 0x347 GPR phase

The SHA-pinned Japanese TH075 v1.11 original has ONE complete
CharacterObject::Advance at `0050A580`: **81,539 original callable
CODE B / 17,435 native x86** followed by 567 independent afterRET
switch DATA bytes. F1075/F1076 add TWO *inner* original game cases
to the current normal VC7.1 original-shaped C++ parent, not separate
original callables. The whole original game function remains NONEXACT.

| Original physical game action | Real Japanese PE interval | Original CODE/x86 | Current source case CODE/x86 |
| --- | --- | ---: | ---: |
| `0x346` | `00511D25..005123B9` | **1,684B / 365** | 1,363B / 365 |
| `0x347` | `005123B9..005125A8` | **495B / 101** | 401B / 101 |
| **Two restored game interiors** | — | **2,179B / 466** | 1,764B / 466 |

## Original actual gameplay

**`0x346`** independently implements: real status-5 expiry, parent
action `(0x31,0x96)` with real **three-shot** loop of `0x3E4`
projectiles and conditional parent+0xEFA reset/extra `0x3E3`;
animation stage/frame and native +0xD8 initialization (15), actual
`0040FBB0` and raw-bits +0xC8 motion initialization at `0040FB70`,
actor movement, stage-1 velocity and angle changes, stage-2/3 scale,
alpha and signed-short angle changes, native x87 calls into
`00483300`, real parent+0x310 float orientation update, authentic
status 2/4 guards and `0040FB40(3)` transition, four native arena
bounds and original `0040FA30/0045B830` completion. Its stage-2
player-facing trajectory computes the actual grandparent target X/Y
with original `00658398` offset and `00657828` divisor, converts the
float through the real CRT **`006406AC`**, and writes signed short
angle at +0xDC. The genuine original PE calls `00483300` **four
times** and `0040FB70` **four times** in this one source case.

**`0x347`** separately reconstructs the original 101-x86 animation
handler. Like original action `0x339`, it initializes native scale,
opacity, visual sprite WORD and facing-dependent +0x2C angle, but
its native facing multiplier is **25**, not -45. Its native x87
rate at `006598A0`, subtract-reversed term at `00658058` and
remaining offset at `00658354` are distinct physical PE globals,
with alpha fade and native expiry/action completion. These are real
independent original switch cases; the similar x86 mnemonic shape
does not imply shared constants or a merged game action.

## Physical PE fields and compiler GPR-lifetime recovery

Before `0x346` existed in the parent, writing only genuine 0x347
produced all **101/101** original x86 mnemonics but only **30/101**
original GPR roles. Restoring the *full* real 365-instruction C++
`0x346` motion/combat/parent logic restores 0x347 to **101/101**
original GPR roles without fabricated locals, explicit register
binding, manual assembly, byte grafts or source marker tricks.

The current original-PE live verifier
`scripts/verify-characterobject-current-recovered-f1068.py`
cold-builds **the ONE current full partial C++ parent** under
pinned VC7.1, SHA-verifies the full independent original **81KB
CODE**, rechecks all **92 original DIR32 jump-label equivalence
partitions and 199 sparse-index bytes** and resolves each original
external PE field by original x86 instruction ordinal, actual
physical field byte, REL32/DIR32 type and original game destination.

| Actual original native verification | `0x346` | `0x347` |
| --- | ---: | ---: |
| Matching ordered original mnemonics | **365/365** | **101/101** |
| Matching original GPR-role positions | **365/365** | **101/101** |
| Matching original instruction widths | 259/365 | 70/101 |
| Actual native PE call/global fields | **34/34** | **10/10** |
| Real PE `00483300` calls | **4/4** | — |
| Actual CRT `006406AC` float-to-int | **1/1** | — |
| Original 0x347 signed facing immediate | — | **25** |

**Current entire partial original-shaped C++ function** emits
**26,974 CODE B / 7,252 x86** with saved receiver at EBP-`0x60`
and frame `ESP 0x178`; the original has **81,539 CODE B /17,435
x86**, receiver at EBP-`0xAC` and full `ESP 0x3A0` frame.
Across **38 recovered genuine original action intervals**, it
represents **32,592 original native CODE B /7,100 original x86**,
with **7,100/7,100 mnemonic and GPR matches**, **573/573 physically
correct original PE call/global fields**, and only **26,018
generated C++ inner case CODE B**. Many other original action
handlers are still marker-only and the real original instruction
widths/branch distances are nonexact. *No additional original whole
GAME CODE or whole callable is newly accepted exact.*

Reproduce only the affected current parent:

    scripts/repo-python scripts/verify-characterobject-current-recovered-f1068.py

All earlier targeted original-PE state checks and 12 normal C++
original-Y operand-order controls have been updated to this parent
and run. Normal C++/COFF/PDB/compiler and original physical PE
receipts are under ignored `.analysis/f1075-native347/`,
`.analysis/f1076-native346/` and `.analysis/f1068-boss-live-all-native/`.
No 979-unit cold replay or original executable mutation was performed.
