# F576 — 274-instruction native CharacterObject states 0x330 and 0x331

**Pinned Japanese TH075 1.11 original PE and selected real VC7.1 C++ source
proof, not byte-exact whole-fighter CODE.** The original PE SHA256 is
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.

The original one-switch fighter giant `004EBDA0` contains **33,293 whole
native CODE bytes** and 438 genuine after-RET switch DATA bytes. Its full
original CODE SHA and complete physical dense/sparse tables are checked
before one new diagnostic C++ source TU is compiled. This builds on F572–
F575's real action bodies and retains **all 17 actual game-action cases**
`0x320..0x32E` plus `0x330..0x331` inside one natural `Advance()` source.
The original `0x32F` is an authentic *default target*, not an 18th
actual action body. Other cases from `0x332` onward remain diagnostic-only
marker stores, NOT reconstructed game logic.

## Two independently original-bounded large state-machine cases

The original first-switch compressed handler targets delimit two separate,
complete **274 x86 instruction /1,003 native CODE byte** bodies:

- **Action `0x330`:** native parent state `+0xE4/+0x60` in `(0x45,0x96)`
  and signed own stage `<11` triggers the true `0045B830` reset and
  the original **8-effect** `00453A70(0x3E4)` loop, with extra `0x3E3`
  under parent `+0xEFA>25`. Else native stage zero initializes position
  `this+0x50=−4.0f`, velocity `this+0x54=6.0f`, scale fields and
  color bytes, calls `0040FBB0(0,0,0)`, and performs genuine float
  motion/color-state updates. The frame-velocity subtraction uses
  **native global `006583FC`**.
- **Action `0x331`:** separate physical native 274-insn/1,003-byte
  block, *not* a repeated table alias. Its stage-zero motion instead
  writes **`+0x50=+3.0f` and `+0x54=16.0f`**; its signed parent
  upper-bound uses the original alternative near `CMP` encoding. It
  subtracts the **different native float global `00659090`** at stage
  zero, rather than `006583FC`. Its random effect argument and native
  effect id are distinct; it is not safe to copy the original `0x330`
  literal values into this action.

Both actions contain real signed direction-byte x87 movement, stage-0
fade growth, stage-11 scale reduction using double `00659730`, stage-6
and stage-10 state change callbacks, and stage-9 effect generation.
On stage9, the normal source calls the real original actor helper
`00455580` with the original argument ordering; it stores the integer
result converted by x87 into parent `+0x318`, writes 1,200.0f into
parent `+0x314`, then calls parent `00453A70` to spawn the original
computed-position effect and `00453D40(6)`. All these are backed by
actual original native call/float COFF fields.

## Native width difference, not fabricated CODE

A selected-only natural VC7.1 switch C++ source emits exactly **274
instructions /985 bytes** for *each* of the two large cases, with
identical register allocation, x87 arithmetic, branch topology and
member field access. The *entire original native giant* instead saves
integer-to-x87 temporaries at deeper EBP locations:

- action330 native `EBP−0x84`, `−0x88`, `−0x8C`;
- action331 native `EBP−0x90`, `−0x94`, `−0x98`.

Each of the three actual integer-to-x87 temporaries is used by a native
`MOV` followed by `FILD`. These **six original instructions per case**
use real 32-bit EBP displacements that are **three bytes wider** than
the compact smaller C++ diagnostic source frame. The complete native
size gap for each case is **6 × 3 = 18 bytes**, `985 + 18 = 1003`.
This is checked at the exact six original instruction ordinals
`97/98`, `244/245`, `259/260`. There are **no other instruction-order,
GPR, branch, or source/target semantic differences** between these
274-insn case bodies. No synthetic local padding or machine-code
byte graft was used to reproduce the original whole function frame;
**neither case is byte-exact CODE**.

## Physical original COFF and whole native jump DATA verification

The tracked selected-only source verifier
[`scripts/verify-characterobject-fire-actions-f576.py`](../scripts/verify-characterobject-fire-actions-f576.py)
freshly builds only the affected C++ from
[`probes/CharacterObjectActionsF572.cpp`](../probes/CharacterObjectActionsF572.cpp)
under pinned VC7.1 `/Od /Ob0 /Gy /GR- /GX- /GS /Zi`. It independently
reads the entire original 33,293-byte giant from Japanese PE and its
physical handler boundaries, then rechecks all fifteen previous real
cases (including two previously documented independent read-only
MOV/FLD swaps in F573/F574). The two new 274-instruction cases are
strictly compared for every native x86 register/x87/branch/operand
role, allowing only those **six actual EBP disp32 width expansions**.

For every native direct `CALL` or absolute float operand, the source
must emit an actual COFF `REL32`/`DIR32` relocation at the authentic
original instruction ordinal, with matching original-PE callee/global,
COFF symbol/type and zero addend. In particular, the separate real
`0x331` float global `00659090` was discovered and corrected during
this physical verification: comparing only opcodes would have missed
that semantic difference.

| Original physically complete game actions | Native original instructions | Internal original CODE (not independent credit) | Real typed COFF fields | Exactness caveat |
| --- | ---: | ---: | ---: | --- |
| Previous 15 real action bodies through `0x32E` | 1,506 | 5,587 B | 113 | Two original/read-only source-order swaps |
| New original `0x330` | 274 | 1,003 B | 16 | Six widened EBP temp operations, +18 original bytes |
| New original `0x331` | 274 | 1,003 B | 16 | Six widened EBP temp operations, +18 original bytes |
| **Total** | **2,054** | **7,593 B** | **145** | No complete giant exact credit |

The original physical **60 dense switch DWORD COFF refs**, default/
repeated target partitions, **198 byte-identical native sparse-index
bytes**, and the **438 distinct after-RET DATA-layout bytes** are all
separately verified. None is counted as CODE.

```bash
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/verify-characterobject-fire-actions-f576.py
# Independently recheck prior native game-action cases:
scripts/repo-python scripts/verify-characterobject-fade-actions-f575.py
scripts/repo-python scripts/verify-characterobject-following-actions-f574.py
```

Ignored `.analysis/f576-characterobject-fire-source/` retains new
C++/OBJ/PDB/compiled COFF and JSON receipts. The original native
instruction alignment, first unsuccessful typed-field controls and
per-fighter stack spill analysis are retained under
`.analysis/f576-characterobject-330-331/`. The **whole 33,293 original
CODE bytes remain unaccepted**; the 7,593 inner native bytes are not
17 separately exact functions and the other game-action bodies are
not yet source-recovered. No all-unit cold replay or external Oracle
acceptance receipt.

## F577 follow-up: genuine native 0x332 facing reversal

The same tracked ordinary C++ source has now gained one further
complete **279-instruction /1,019-byte native game-action `0x332`**
with original stage1 signed byte reversal and two +3 byte native
EBP temporary width expansions. F576's verifier remains strictly
scoped to the prior 17 native action cases and rechecks all of them
under the newer source. The new [F577 direction-reversal study](CHARACTEROBJECT_DIRECTION_REVERSAL_F577.md)
independently verifies the additional 0x332 source, retaining the
still-unmatched whole 33,293-byte original giant accounting.
