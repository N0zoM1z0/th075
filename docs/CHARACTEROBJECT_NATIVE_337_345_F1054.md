# F1054 — Two more original CharacterObject action handlers with native call/field proof

The pinned Japanese TH075 v1.11 **81,539B / 17,435-x86** complete
CharacterObject Advance at `0050A580` is still NONEXACT. Its one native
sparse switch owns 92 afterRET DIR32 jump entries and 199 original
literal index bytes, not independent callable game state functions.

The selected partial whole-parent C++ already reconstructs ten true
original states, including the 1,048B action 0x321 and genuine 0x325
three-shot loop. F1054 adds two more complete original game cases,
recovering the original physical state, motion and rendering writes:

- `0x337`: original `0050E9C0..0050EA5B`, **155B /35 x86**. The
  native stage/frame `(0,0)` initializes real motion at `0040FBB0`,
  actor scale X/Y to **1.0f**, and four native opacity bytes. It
  then reads the true action from `0040FA30`, and calls the real
  completion handler `0045B830` if the action equals own +0x70.
- `0x345`: original `00511C8A..00511D25`, **155B /35 x86**. The
  same physical state/opacity operations appear, but genuine scale
  values are **2.0f** for both axes. The original dispatch/handler
  identity is distinct from 0x337; it is not merged into that case.

The selected C++ uses two physical state fragments inside the ONE
original-shaped partial whole parent, without new dummy locals,
forced register decorations, assembler, patched instructions, or
source-only literal target masks. It retains the authentic game
calls and native field widths.

## Pinned PE versus entire normal source

The independent original-native full-parent verifier
`scripts/verify-characterobject-multi-state-f1047.py` was rerun
against all **12 real source cases**. It SHA-checks original complete
81KB CODE, checks the full 92-entry afterRET original jump-label
equality partitions and all 199 original sparse bytes, and compares
every original genuine case x86 ordinal and typed COFF call/global
field against original physical PE bytes and destinations.

| Actual game action | Original CODE/x86 | Compiled inner CODE/x86 | Native mnemonic | Native GPR | Real PE targets |
| --- | ---: | ---: | ---: | ---: | ---: |
| `0x337` | 155B /35 | 119B /35 | **35/35** | **35/35** | **3/3** |
| `0x345` | 155B /35 | 119B /35 | **35/35** | **13/35** | **3/3** |
| **All 12 recovered states** | **3,907B /846** | **3,030B /846** | **846/846** | **824/846** | **62/62** |

`0x345`'s **22 wrong GPR-role positions** are real and unhidden.
The same true case compiled with its preceding 0x337 temporarily
replaced by a marker remains 13/35, so merely adding/removing 0x337
is not the cause. The unimplemented earlier `0x338`–`0x344` native
state behaviors and entire stack frame are more appropriate places
to continue the register-lifetime investigation. Neither state
has original-width byte equality: the real native parent saved-this
slot is EBP-0xAC, while the short incomplete C++ prototype uses
EBP-0xC. All twelve sources still have authentic nonlocal PE field
targets; **wrong widths cannot be ignored as exact CODE**.

The current whole selected prototype compiles to **4,373 CODE B /
1,050 x86** plus 567 true switch DATA bytes, whereas the original
full game callable is **81,539B /17,435 x86**. Most original states
are still source markers, so even complete case-local mnemonics,
register roles or physical PE fields add **zero** newly accepted
whole-game CODE bytes.

Run only the affected full current partial parent, plus optional
bounded original action-321 and cross-state controls:

    scripts/repo-python scripts/verify-characterobject-multi-state-f1047.py
    scripts/repo-python scripts/verify-characterobject-boss321-f1051.py
    scripts/repo-python scripts/verify-characterobject-cross-state-phase-f1052.py

Compiled C++/COFF/PDB and actual PE receipts are under ignored
`.analysis/f1047-object-multistate/`, `.analysis/f1051-*`, and
`.analysis/f1054-two-states/`. No 979-unit global cold replay, no
independently accepted inner switch-state CODE and no whole function
promoted to exact.
