# F1050 — Two separate, complete source-backed native 0x32C and 0x32E game states

The pinned Japanese TH075 v1.11 original game has an 81,539B/17,435-x86
single-switch CharacterObject `Advance` callable at **0050A580**.
It remains largely source-incomplete and **NONEXACT**. The original
92 afterRET DIR32 jump fields and 199 sparse-index bytes are
separate DATA, not portions of independently callable case CODE.

The previous F1047 complete-source prototype recovered the actual
`0x320`, `0x322`, `0x32B`, `0x32D`, `0x332` state behaviors. F1050
further restores **two more whole original game state bodies**:

| Native action | Original physical interval | Original CODE/x86 | Current natural-source interior |
| --- | --- | --- | --- |
| `0x32C` | `0050CD7A..0050CE97` | **285B /63 x86** | **222B /63 x86** |
| `0x32E` | `0050CF7A..0050D097` | **285B /63 x86** | **222B /63 x86** |

These are distinct physical original dispatch branches, not aliases.
Although their original opcode/operand sequences are structurally
parallel, their physical PE original entries and following action
states are separate; F1050 intentionally emits two genuine C++
case bodies rather than merging them into one synthetic handler.

Both original bodies first copy **one actual parent-facing BYTE**
from parent+0x66 to the owned actor+0x66. Under parent action `0x131`,
they copy X/Y coordinates from parent+0x44/+0x48 with **DWORD MOVs**
rather than floating-point arithmetic (`FLD/FSTP` would be wrong).
A nonmatching parent action calls the real `0045B830` handler and
exits. At actual zero animation stage/frame and zero +0xD8 flag,
source initializes native `0040FBB0(0,0,0)`, X/Y scale `1.0f`
and four opacity bytes, then executes the original action getter
`0040FA30` and possible `0045B830` completion. All four genuine
external call targets for each case are retained.

The selected complete-source prototype was recompiled with original
pinned VC7.1 `/Od /Ob0 /Gy /GR- /GX- /GS /Zi`. Crucially, the
**entire original CODE** and postRET native switch partitions are
re-read and SHA-checked before assigning state boundaries.
The tracked `scripts/verify-characterobject-multi-state-f1047.py`
now checks all seven game-state source cases. For both new states it
proves:

- **63/63** original ordered x86 mnemonics per state
- **63/63** original GPR roles per state
- **4/4** genuinely physical original external PE call destinations,
  by true instruction ordinal/field offset and natural source symbol
- **42/63** original x86 widths per state; the remaining 21 wrong
  widths are **only** `EBP-0xAC` original saved-receiver loads
  versus the current partial prototype's `EBP-4`, each 3 bytes shorter

There are no missing opcode mnemonics in these two complete inner
state sources; matching instruction count does **not** imply exact
machine bytes. The real whole original has an `ESP 0x3A0` frame,
whereas the partial parent still has `EBP-4` and a much smaller
frame. The switch table equality partitions and all sparse-map DATA
bytes remain independently preserved.

## Current live source with all seven recovered original game states

| Measurement | Native original state set | Current full-switch C++ prototype |
| --- | ---: | ---: |
| State cases reconstructed | **7** | 7 real gameplay handlers, others markers |
| Combined distinct original CODE/interior bytes | **1,861B** | 1,431 compiled inner CODE B |
| Combined ordered x86 instructions | **397** | **397/397 mnemonic matches** |
| Original GPR-role positions equal | — | **359/397**; 38 wrong all in pending `0x322` register phase |
| Genuine physical original PE external fields | **27** | **27/27 source targets verified** |
| Original whole callable status | **81,539B /17,435 x86** | NONEXACT, **2,849B/611 x86** prototype only |
| Switch afterRET original DATA | 92 DIR32 +199 index B | authentic entries/partitions/literals retained |

The genuine preceding original `0x321` action remains a **marker**,
which can affect the following `0x322` source's GPR allocation.
The currently emitted parent is not a playable, fully reconstructed
or original-byte-identical 81KB function. All accepted authored
coverage remains unchanged. Do not count 1,861 internal state bytes
as new complete-callable exact coverage.

Run only the affected complete parent verifier and original `0x320`
grammar controls:

    scripts/repo-python scripts/verify-characterobject-multi-state-f1047.py
    scripts/repo-python scripts/verify-characterobject-boss320-f1044.py

Both targeted verifiers were rerun after including the two newly
reconstructed actions. Entire normal-generated COFF/PDB, compiler
logs and original-native PE receipts remain in ignored
`.analysis/f1047-object-multistate/` and
`.analysis/f1044-object320-grammars/`. No all-979 unit cold replay,
no target modification, no fake source register allocation and no
accepted new whole original CODE bytes.
