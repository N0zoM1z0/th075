# F564: all 11 original action cases integrated per fighter C++ function

**New actual source integration and pinned MSVC 7.1 compile evidence; the
complete giant functions are not exact.** Japanese TH075 1.11 original
PE SHA256: bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98.

Whole original fighters 004F7130 (44,211 CODE bytes) and 005AEEC0
(71,616 CODE bytes) are first SHA verified in their *entirety*, with
all native jump tables and after-RET DATA separately validated. Their
total 115,827 original CODE bytes remain unaccepted.

## Newly integrated source rather than independently tested snippets

This experiment builds **one normal C++ Advance() switch for each giant**
containing eleven genuine complete original gameplay cases **0 through 10**.

The source is freshly generated from the original PE and tracked,
previously verified helpers: actions 0-5 real x87/reset/state logic,
actions 6-8 the per-fighter F563 positive-FLAG conditional secondary
motion, action 9 native collision and early return, and action 10 the
per-fighter first-state guard and literal state transition. F549 action
10 has low/high arguments 0/1 in 004F7130, but 3/2 in 005AEEC0.

Unlike assembling separate object snippets, VC7.1 must compile all
eleven of these true game-action bodies in the SAME C++ function.
All later unimplemented action labels remain **diagnostic-only marker
stores**, not reconstructed game behavior. The partial borrowed owner
type and full original local-frame lifetime are still unproven.

## Whole-original COFF and native x86 evidence

The tracked reproducible source verifier:
[verify-fighter-integrated-opening-switch.py](../scripts/verify-fighter-integrated-opening-switch.py)
first checks the full 44K/71K original CODE and all switch DATA.
It regenerates two ordinary C++ source units from these original
physical cases and fresh-compiles only these two affected TUs with
pinned VC7.1 /Od /Ob0 /Gy /GR- /GX- /GS /Zi.

Both compiler objects independently pass:

- All **22 genuine, physically complete action-case boundaries**, from
  original first-switch DWORD slots for actions 0..9 and the separately
  original singleton action 0x32 JE entry for action 10.
- **1,296/1,296 original native x86 instruction roles and lengths**,
  including EAX/ECX/EDX actor registers, original x87 operand/branch
  control flow and per-character source method semantics. These are
  **4,558 original internal CODE bytes**, 2,313 from 004F7130 and
  2,245 from 005AEEC0, not independently credited functions.
- **146/146 genuine per-case typed REL32/DIR32 COFF references**, 73 per
  fighter, verifying the actual original call/global destination and
  correct physical native instruction ordinal. The three-instruction
  actions 4 and 5 correctly have zero such fields.
- All **305 original-style physical DWORD switch COFF slots** across
  the full two giant functions, original default/repeated-target
  partitions, **822 byte-identical original compressed map bytes** and
  **2,042 separate after-RET DATA-shape bytes**.

| Whole original giant | Integrated original case instructions | Inner original CODE (not accepted) | Typed COFF fields | All native DWORD slots | Original sparse bytes |
| --- | ---: | ---: | ---: | ---: | ---: |
| 0x004F7130 | 655 | 2,313 | 73 | 141 | 411 |
| 0x005AEEC0 | 641 | 2,245 | 73 | 164 | 411 |

**Noteworthy integration constraint:** older isolated action-9 and
action-10 probes did not always reproduce original GPR choices for
these fighters; with the actual action 6-8 source also present in the
same compiled function, the physical native source register/branch
grammar matches all eleven cases. The enclosing case mix *can affect
code generation* and must not be ignored in whole-fighter reconstruction.

## Affected-only reproduction

    scripts/repo-python scripts/verify-target.py
    scripts/repo-python scripts/verify-fighter-boss-family.py
    scripts/repo-python scripts/verify-fighter-integrated-opening-switch.py --boss 0x004F7130
    scripts/repo-python scripts/verify-fighter-integrated-opening-switch.py

New C++ sources, COFF objects, PDBs and per-case complete instruction
alignment remain under ignored .analysis/f564-integrated-opening-switch/.
No original executable bytes copied into source, no fake local padding,
no complete giant exact CODE or independent partial function credit,
no all-unit cold replay, and no external Factory/Oracle receipt.
