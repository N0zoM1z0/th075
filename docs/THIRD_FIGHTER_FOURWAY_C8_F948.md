# F948 — True 004AC040 four-way C8 source: 149 original x86 roles, 15 PE targets, three honest native widths missing

The SHA-pinned Japanese TH075 v1.11 original
`004AC040` is an **82,796-B/22,721-x86 entire callable
fighter**, with **1,126 separate afterRET DATA bytes**.
The current normal VC7.1 C++ father is a **partial**
source; it has numerous later placeholders and does not
reconstruct the real 82KB original game object lifetime.
It is NONEXACT.

The previously reconstructed F947 partial source still
used a **15-B/two-x86 marker** at real original action
0xC8. Independent original PE decoding gives its
true complete native interval **004B009E..004B02B9**,
**539 complete internal CODE bytes/149 original x86**.

The new natural, tracked C++ action body
[`FighterThirdBossFourWayC8F948.inc`](../probes/FighterThirdBossFourWayC8F948.inc)
was reconstructed from this actor's **own** native
x86 instead of blindly reusing the original
00543210/005214B0 fighters' different C8 actions.
It contains the real beginning facing/fall flag
at `this+0x3AC`, native setup call `00454BC0`
with arguments `(3,4,0xFF)`, the original
stage/frame-zero initializations, real float
comparison against **00657854**, subtract
**00658350**, and native clamp to **11.0f**.
It also reads actual signed facing and opponent
direction, chooses original `0xCC/0xCD/0xCF`
action returns, increments the true short `0xF00`
counter only while below **2**, and on stage3/
frame0 issues the original two native `00453C80`
projectiles with kind `0x7D/0x7E`, real offset
**00658268**, and prepares action `31`.
No fake C++ locals, padding, assembly or target
machine bytes are inserted.

The bounded tracked
[`verify-third-fighter-fourway-c8-f948.py`](../scripts/verify-third-fighter-fourway-c8-f948.py)
rebuilds and serially compiles two ENTIRE normal
VC7.1 original-shaped **partial fighter** C++ parents:
the previous F947 C8 marker and the new F948 real C8
source. It independently compares actual original
PE case boundaries and physical native x86 ordinal
roles, all **15 typed zero-addend original PE
external call/global targets**, 151 real afterRET
local DIR32 table labels and 522 unrelocated
DATA bytes against the original hash-pinned game.

| Whole partial source property | Prior F947 | New F948 |
| --- | ---: | ---: |
| Compiled callable partial parent CODE B | 18,513 | **19,027** |
| Compiled parent x86 | 4,941 | **5,088** |
| Source actual original C8 CODE B/x86 | 15/2 | **529/149** |
| Native original C8 CODE B/x86 | 539/149 | **539/149** |
| **Original C8 wrong positional mnemonics** | Unaligned | **0** |
| **Original C8 wrong GPR-role instructions** | Unaligned | **0** |
| Original C8 wrong x86 widths | Unaligned | **3** |
| Actual PE external targets validated | 0 | **15/15** |
| Original afterRET DIR32 / nonfield DATA | 151/522 | **151/522** |
| Complete 82KB original game function exact | NO | **NO** |

Three **real** native x86 width positions remain
wrong at complete C8-local ordinals **106,121,122**.
They are causally related to **native original
full-parent stack ownership**, not random missing
bytes: original parent prologue executes
`SUB ESP,0x720` and saves ESI; the current
19KB partial source has `SUB ESP,0x40`.
The native actual 32-bit signed-facing→x87
temporary lives at **EBP−0x94**, generating
two 6-byte long stack instructions at
ordinals 121 and 122; the incomplete partial
source uses EBP−0x40 and emits shorter
3-byte instructions. That shortens the
next-branch distance, so ordinal 106 becomes
a short 2-byte JNE instead of the original
6-byte long JNE. **3+3+4=10 genuine missing
original instruction bytes**, but many other
operands, saved-`this` stack slots, parent
external jumps and remaining giant cases
also differ. Do NOT infer whole exactness
from the sum or artificially enlarge stack.

Reproduce only these two partial parent builds:

    scripts/repo-python scripts/verify-third-fighter-fourway-c8-f948.py

The compiled original-shaped C++/OBJ/PDB,
independent original PE native-target receipt,
and compiler logs are retained machine-locally
under ignored `.analysis/f948-third-native-C8/`,
with initial trial evidence at
`.analysis/f948-third-c8-native/`.

**0 newly accepted whole original CODE bytes,
0 independent case-only credits, and NO full
979-unit cold replay.**
