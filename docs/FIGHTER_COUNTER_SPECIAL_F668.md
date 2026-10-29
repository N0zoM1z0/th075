# F668 — three consecutive strict native 0x252/0x253/0x254 case bodies in giant 00543210

User-supplied pinned original Japanese TH075 version 1.11
`resources/th075.exe`, SHA256
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
This is a genuine VC7.1 reconstruction experiment **inside** selected
original giant `00543210` (58,294 total original CODE bytes, plus 943
separately owned after-RET switch DATA bytes). The enclosing giant is
**still NONEXACT**. The three newly strict native *internal* case
bodies are not independently callable whole game functions.

## Actual native original physical case extents and source evidence

| Original physical action | Genuine original PE native interval | Original whole-case x86 | Original internal CODE | Typed original PE/COFF source fields |
| --- | --- | ---: | ---: | ---: |
| `0x252` | `0054C49A`–`0054C59E` | 72 | 260 B | 6 |
| `0x253` | `0054C59E`–`0054C6A1` | 72 | 259 B | 6 |
| `0x254` | `0054C6A1`–`0054C782` | 63 | 225 B | 6 |
| **New strict contiguous complete native interiors** | | **207** | **744 B** | **18** |

All three cases initialize real stage/frame-zero `+0x62/+0x64`
state by decrementing the native signed byte `+0x366`, calling actual
`00453E20`, setting short `+0x80=1`, zeroing DWORD `+0x7C`, signed
flag `+0x3AC` and short `+0xF00`. The original `0x252/0x253` have an
additional genuine conditional resource stage: if native short
`+0x3B6` is zero and `+0x7C==1`, set short `+0x3B0=1000`.
Original action `0x254` does **not** include this branch, and the
source respects this difference. Action completion compares real
`0040FA30()` with native short `+0x70`, then calls
`0040FAC0(0)` if equal. At stage 4/frame zero each case spawns
resource `0x37` through native `00453C80` with raw x from `+0x44`,
actual float y `+0x48 + 00657888`, signed direction `+0x66` and
argument 1; prepares animation `0x21` through `00453D60`; and clears
the *actual owner pointer's* short `+0xEFA`.

The original full-C++ source is
[`FighterCounterSpecialF668.inc`](../probes/FighterCounterSpecialF668.inc).
Two native codegen issues were resolved without fake locals, manual
bytes or arbitrary register forcing:

- The genuine byte decrement is prefix `--signed_char_member`, which
  preserves VC7.1's 8-bit `MOV; SUB reg8,1; MOV` instead of an extra
  signed-extension instruction from a value-assignment expression.
- The actual y float is expressed as the *same original typed lvalue*
  `(*(&POS48)) + g_ContactProjectionAt00657888`. This ordinary C++
  identity-lvalue form restores the **original `FLD [this+0x48]`
  before `FADD [00657888]`**. Ordinary `POS48+global` in the same
  VC7.1 context instead emitted a swapped x87 load/operand order,
  matching overall width and count but not the original instructions.
  This correction is reproduced across all three adjacent original
  native case bodies, not merely one truncated expression.

For **each** real native case, all **six** physical PE-targeted fields
are independently proven to match original instructions and the
compiler's genuine zero-addend typed COFF records: REL32 calls
`00453E20`, `0040FA30`, `0040FAC0`, `00453C80`, `00453D60`, and
the original DIR32 float global `00657888`. The generated
`SpawnMixedAt453C80(int,int,float,char,int)` type declaration is a
*provisional ABI grammar*, not proof of the original historical C++
class/signature. Original x87 order, **every** branch, GPR role,
complete native instruction width and full physical case interval
are required; an independent raw EBP stack comparison normalizes
**only** the known source `this` save `EBP−0x44` to emitted `EBP−8`.
No other original EBP scratch or COFF displacement is masked.

## Same fresh full-parent compilation; context dependence remains

[`verify-fighter-counter-special-f668.py`](../scripts/verify-fighter-counter-special-f668.py)
regenerates **one full C++ parent source** from authentic original
native fingerprints and tracked ordinary C++ case fragments, then
freshly compiles only the selected giant under pinned VC7.1
`/Od /Ob0 /Gy /GR- /GX- /GS /Zi`. It rechecks the **same new compiler
object** for all preceding **19 context-scoped strict original inner
cases** (including original `0x200/0x201`), original `0x186/0x18A/
0x18B` scratch-negative cases, and the full independently owned
943-byte after-RET switch DATA. Original `0x255` must remain the
actual next physical handler; no invented case or original function
split is credited.

This source context now proves **22 strictly reconstructed original
inner cases /1,644 authentic x86 /5,715 original internal CODE bytes /
150 real typed PE/COFF fields** in the selected giant. The *context
warning* established by F666 still applies: inserting additional
unresolved earlier original cases may change later VC7.1 register
phases, despite case-local exactness. F668 is not whole-parent
exactness or a promise that the case would match in every historical
source layout. Across F598–F668, **590 original native case interiors
/159,417 genuine uncredited original CODE bytes** are strict in
their verified *particular complete parent source contexts*.
All 22 whole fighter bosses remain NONEXACT. Formal whole-authored
accepted exact coverage remains **943 functions /862,726 original
CODE bytes (43.71% of reviewed)**.

```bash
scripts/repo-python scripts/verify-fighter-counter-special-f668.py
scripts/repo-python scripts/verify-fighter-special-stage-f664.py
scripts/repo-python scripts/validate-tracking.py --require-target
```

New entire fighter CPP/COFF/PDB, compiler logs, authentic physical
PE/COFF receipt and earlier comparison trials are under ignored
`.analysis/f668-fighter-counter-special/` and
`.analysis/f667-action252-grammar/`. Only the selected parent was
compiled; no full 943-unit cold replay, original EXE patch, fake
locals, manual assembly or external Oracle acceptance occurred.
