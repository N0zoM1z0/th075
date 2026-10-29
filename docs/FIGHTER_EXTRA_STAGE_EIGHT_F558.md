# F558 — complete action 8 in both original extra-stage fighter megabosses

**Original Japanese TH075 1.11 PE backed by fresh MSVC 7.1 C++ probes; no
whole-fighter exactness claim.** Original target SHA256:
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
Original `00486550` (50,735 bytes) and CharacterMove `004AC040`
(**82,796 original CODE bytes**) are both verified as *entire giant
functions* first, including all native post-RET jump table DATA. This
extends [F556's genuine 117-instruction action 6/7 source](FIGHTER_EXTRA_STAGE_SOURCE_F556.md)
by a third newly modeled **full original action-8 code body** per fighter.
The enclosing original functions remain **133,531 unmatched CODE bytes**.

## Native action-8 policy and real ordering difference

The physical first-switch ninth/tenth DWORD destinations bound the complete
**362-byte, 104-instruction original action 8** in each of these fighters.
It differs from the longer actions 6/7: there is **no 13-instruction
extra-stage `0040FB40(5)` branch**; otherwise its real actor state/frame,
x87 contact test, reset, motion setup and virtual `dword ptr [edx]` call
follow the core C++ control flow. The original state byte `this+0x511`
is compared with **4**, and the first original `0040FAC0` callback gets
**0xCE**. The stage-specific position is the actual float **−4.0f**;
position/speed remain authentic per-character values, not inferred from
another fighter.

The compiler requires two **different original source expression orders**:

- Fighter `00486550`: `POS = -4.0f; FLAG = 0; POS54 = 16.0f;
  POS5C = 0.75f;` (the original moves `FLAG` between position and velocity).
- CharacterMove `004AC040`: `FLAG = 0; POS = -4.0f; POS54 = 15.0f;
  POS5C = 0.7f;` (the original clears the flag **before** all three
  floating-point field stores).

Original `00486550` order is **not** the same as its own action 6/7,
whereas CharacterMove's action 8 matches the early flag-clear ordering
seen in its action 7. This was independently observed at original MOV
instruction ordinals **81/83/85/87** and checked against the ordinary
VC7.1 source output. No artificial register selection, field padding or
copied CODE was required to reproduce the compiler's resulting C++ flow.

## Full selected-only original/VC7.1 validation

[`scripts/verify-fighter-extra-stage-action-eight.py`](../scripts/verify-fighter-extra-stage-action-eight.py)
independently regenerates all C++ from original PE, F556's two authentic
117-instruction cases and F548's normal 104-instruction actor case. One
or two selected *new diagnostic source TUs* compile with pinned VC7.1
`/Od /Ob0 /Gy /GR- /GX- /GS /Zi`; remaining unfinished action labels
are explicitly test-only marker stores, not claimed original C++.

Across the **two** original whole-fighter native switch contexts:

- **6/6 complete cases**, each with **403, 403, 362** native CODE bytes;
  all **676/676 original machine instruction kinds, real register selection,
  x87 operand widths, member accesses and branch graphs** match their
  per-character C++ source compilation geometry.
- **44/44 physical typed `REL32`/`DIR32` COFF fields** match their real
  original call/float ordinal/target; per-fighter source contains 8+8+6
  valid fields. The real original virtual call form is also preserved.
- **314 original-style DWORD switch COFF fields**, true default/duplicate
  case partitions, **934 literal original sparse index bytes**, and the
  complete **2,190 after-RET DATA-shape bytes** are verified. This DATA
  is not extra CODE credit.

| Original complete giant | Action 6 / 7 / 8 original sizes | Original stage | Original POS54 / POS5C floats | Action-8 FLAG store order | Original table DWORD fields | Original sparse index bytes |
| --- | --- | ---: | --- | --- | ---: | ---: |
| `0x00486550` | 403 / 403 / 362 bytes | 4 | `16.0f` / `0.75f` | between position and velocity | 163 | 412 |
| `0x004AC040` | 403 / 403 / 362 bytes | 2 | `15.0f` / `0.7f` | before position | 151 | 522 |

## Reproduce only affected source compilation

```bash
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/verify-fighter-extra-stage-action-eight.py --boss CharacterMove
# Only these two newly affected C++ prototypes, never all 943 exact units:
scripts/repo-python scripts/verify-fighter-extra-stage-action-eight.py
```

Fresh source, COFF, PDB, compiler logs and summary remain in ignored
`.analysis/f558-extra-stage-eight/`, native-PE analysis alternatives in
`.analysis/f558-stage-action-eight/`. The **2,336 original interior CODE
bytes** remain part of **133,531 nonexact giant CODE bytes**, not new
independent 362/403-byte functions. No full original fighter exact source,
no accepted CODE/DATA credit, no all-unit cold replay and no external
Oracle receipt.
