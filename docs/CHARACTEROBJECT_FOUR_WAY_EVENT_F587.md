# F587 — full 397-instruction four-way CharacterObject game action 0x34C

**Original Japanese TH075 v1.11 PE and newly compiled original-shaped
MSVC VC7.1 C++ source evidence, not an accepted exact whole boss.**
Original PE SHA256:
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
The incomplete native original giant `004EBDA0` has **33,293 whole
CODE bytes**, with **438 after-RET original sparse-switch DATA bytes**.
F587 directly reads its complete pinned original CODE and real physical
compressed dispatch, then source-compiles ONE selected ordinary C++
`Advance()` that includes all previous F572–F586 genuine game actions
and newly reconstructed action `0x34C`. Other later source cases remain
**diagnostic marker stores**, never incorrectly claimed as gameplay.

## Original real 397 x86 instructions /1,529 CODE bytes

The physical Japanese original jump target `0x34C`, ending at the next
true nondefault target `0x34D`, contains exactly **397 complete x86
instructions and 1,529 original CODE bytes**. The naturally compiled
C++ emits the same **397/1,529**, with complete correct original
EAX/ECX/EDX member register roles, all source x87 operations, relative
branch graphs, conditional exits and *every individual x86 width*.

The original does not implement a single easy generic state. It has:

- Parent actor `+0xE4 -> signed +0x60` in `(0x45,0x96)` with own
  signed stage `<5` triggers true original `0045B830`, runs the
  original **8-iteration effect loop** `00453A70(0x3E4)`, and
  conditionally saturates original parent `+0xEFA` followed by
  real `00453A70(0x3E3)`.
- Four **different** real parent action states `0x198`, `0x19C`,
  `0x19A`, `0x19D`, guarded by the actual parent signed stage
  bounds `<7`, `<5`, `<7`, `<5`, reposition the actor by the native
  signed facing byte ×60 and real parent position; the vertical
  offset uses native float **`006590A8`** and, only for state
  `0x19A`, the **additional** float `00658264`. In the fallback,
  native signed stage `<5` calls `0040FB40(5)` and exits.
- Original stage0/frame0 reset `0040FBB0(0,0,0)`, transform flags,
  x87 scale values, signed +0xDA counter and actor colors. Stage5
  uses genuine double x87 **`00659730`**, float `006583FC`,
  signed fade/byte semantics, and actual `0045B830` early reset.
  It checks real `0040FA30` current action and signed `+0x70`.
- Original stage4/frame0 with signed counter `<8` increments
  actual `S16(+0xDA)` and calls `0040FB40(3)`. On stage3/frame0,
  **four genuinely separate parent state policies** each set real
  `parent+0x314 = 1000.0f`, call original
  `00455580(0,10)` and apply distinct signed offsets, convert
  the random result by native `FILD` and save parent float
  `+0x318`; then spawn real computed-x parent effect at
  `S8(+0x66)*10 + F32(+0x44)` and native actor y, ending with
  the real `00453D40(6)` callback:

| Actual native parent state | Original random transformation | Original effect created |
| --- | --- | --- |
| `0x198` | `RandomAt455580(0,10) − 5` | **0x322** |
| `0x19A` | `RandomAt455580(0,10) + 30` | **0x323** |
| `0x19C` | `RandomAt455580(0,10) − 5` | **0x324** |
| `0x19D` | `−RandomAt455580(0,10) − 30` | **0x325** |

The genuine PE has the last action's `NEG EAX; SUB EAX,0x1E`
and its own native full arithmetic/branch path; it is not correct to
collapse all four paths into a single guessed effect choice.

## Physical original COFF and complete native switch validation

New tracked verifier:
[`scripts/verify-characterobject-four-way-event-f587.py`](../scripts/verify-characterobject-four-way-event-f587.py).
Actual C++ source:
[`probes/CharacterObjectActionsF572.cpp`](../probes/CharacterObjectActionsF572.cpp).
The verifier rereads the entire original 33K CODE and first switch
from pinned PE, then **fresh-compiles just ONE affected VC7.1 C++
translation unit** under `/Od /Ob0 /Gy /GR- /GX- /GS /Zi`
through F586's independently original-backed native source checker.
It checks the **39 previous complete game-action bodies**, and then
checks *all 397* original native instruction roles for the entire
new case. It requires **all 25 original `REL32`/`DIR32` call/global
fields** be present physically in the new COFF at the genuine
original instruction ordinal, with original native PE destination,
correct source symbol, field type and zero addend. This includes
all four real `00455580`, four effect-creating `00453A70` and
four parent `00453D40` calls, plus real x87 constant globals
`006590A8/00658264/00659730/006583FC`.

The whole first switch retains **60 physical zero-addend `DIR32`
handler-label COFF fields**, original repeated/default equivalence
partitions and **198 byte-identical compressed index bytes**.
Original **438 after-RET DATA bytes** are verified separately, not
mistaken for original CODE.

| Complete real original subranges inside one unfinished boss | Original x86 instruction roles | Original inner CODE (NOT accepted standalone) | Physical typed COFF call/global fields |
| --- | ---: | ---: | ---: |
| Previous 39 game-action bodies F572–F586 | 5,651 | 21,245 B | 389 |
| New entire `0x34C` four-state event | **397** | **1,529 B** | **25** |
| **Total 40 real original game actions** | **6,048** | **22,774 B** | **414** |

## The *same* real source once again improves neighboring EBP codegen

Another original-PE-attested source context finding: before F587, the
old native `0x331` was 274/1,003 but the C++ candidate was
274/997 because its first two integer-to-FPU `MOV/FILD` used disp8
at source `EBP−0x80` and original native uses disp32 `EBP−0x90`.
Adding the **genuine 397-insn game action0x34C** naturally moves
those source temporary slots to **`EBP−0x84/−0x88/−0x8C`** so all
six source `MOV/FILD` operations now use disp32; its source
length is **274/1,003**, the same as original. No fake stack
array, artificially initialized unused variables, handwritten
assembly or byte patch was used. The real original temporary
EBP slots are **still different**, so this does *not* make native
machine bytes or complete giant original function exact.

Earlier original `0x330` still has 18 extra original width bytes;
`0x332` now uses another valid source disp32 candidate `EBP−0x90`
(previously −0x84 then −0x8C) and continues to have native-sized
279/1,019 CODE. All affected older native verifiers have been updated
to require only **three actual physically observed `0x331` source
modes**, specifically the six original integer-to-FPU MOV/FILD
ordinals and exact source candidate stack addresses; they also
recheck the original GPR/x87/branch operands. They never simply
accept arbitrary COFF changes or compiler-frame byte differences.

### Affected-only verification, never all-unit cold replay

```bash
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/verify-characterobject-four-way-event-f587.py
scripts/repo-python scripts/verify-characterobject-late-stage-actions-f586.py
scripts/repo-python scripts/validate-tracking.py --require-target
```

The freshly selected original-PE/COFF source OBJ, PDB, physical
case alignments and original source COFF receipts are preserved under
ignored `.analysis/f587-characterobject-four-way-source/` and
`.analysis/f587-characterobject-34c/`. Older failed/negative C++
controls are preserved in the same ignored source experiment trees.
**The 22,774 original inner CODE bytes are not 40 standalone exact
original functions.** The **complete original 33,293 CODE-byte giant
remains NONEXACT** because later game-action bodies, original receiver
class/whole stack frame and final real source are not all recovered.
No new accepted whole/split CODE or DATA, full all-unit cold replay,
or external Factory/Oracle receipt.
