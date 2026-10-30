# F701 — entire native 302 four-tier radial volley in one complete fighter boss

**New meaningful source reconstruction, NOT whole-function byte-exact.**
Original target: supplied Japanese TH075 v1.11 `resources/th075.exe`,
SHA-256 `bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
The original independently bounded authored `00543210` boss still owns
**58,294 CODE bytes** and **943 after-RET switch DATA bytes**. Its real
internal action `0x302` is **not independently callable** or separately
creditable to the function exact-match ledger.

## Direct original-native case and actual source

Original CODE `0055101E`–`005513C5`: **935 bytes, 261 x86 instructions,
28 physical zero-addend PE/COFF typed call/global references**. We decoded
every physical original instruction, its shared case exit, genuine globals
and full following native `0x31B` handler. Tracked ordinary C++ source
[`FighterFourTierVolleyF701.inc`](../probes/FighterFourTierVolleyF701.inc)
reconstructs the complete case inside a freshly compiled entire boss:

- `00454BC0(3,4,0xFF0000)` storm setup; original frame/state reset,
  two short fields, integer control and original frame end handling.
- Positive-Y gravity decrement, x87 ground crossing comparison,
  auxiliary state `11`, clearing Y and the original reset/exit.
- Native completion check; stage-2 vertical velocity, randomized
  horizontal velocity `float(Random(0,8)-4)`, 0.25f drag.
- Stage-9 setup: prepare action `18`, member `+0x516=120`, native
  original `Random(0,359)` stored in short `+0xF04`.
- **Four genuinely different, full integer-indexed projectile loops**
  chosen by signed byte global `006714D0`: `0` and `1` each run six
  shots with angle step `60`; `2` and `3` each run eight shots with step
  `45`. Each converts `index*step+base` to the real float member
  `+0x314`, then issues the authentic `0x393` spawn with x/y offsets,
  original facing byte and flag. These are four separate source loops,
  not unrolled dummy calls or a generic fake shared function.
- Native stage-11 auxiliary action `9`, then the original shared exit.

The single freshly compiled pinned VC7.1 `/Od /Ob0 /Gy /GR- /GX- /GS /Zi`
whole-parent C++ emits the **identical 935-byte/261-x86 instruction
start/width/mnemonic geometry**. All **28 original physical typed
PE/COFF fields** are matched in their *original x86 ordinals*, with
correct `REL32`/`DIR32`, zero addend, actual PE target and source
symbol. No original bytes are copied into a generated source.

One concrete source correction independently improved the entire native
case: naive `POS48 + global_00658268` made VC7.1 generate
`FLD [global] / FADD [this+0x48]`, which inverted four original Y
expression evaluations. Expressing the meaningful member as the true
read-only lvalue `(*(&POS48)) + global_00658268` instead generates
**the actual original `FLD [this+0x48] / FADD [global]` at all four
original x86 ordinals 125/162/199/236**. Original code remains
935/261/28, but eight genuine instruction operand widths/positions
now line up that did not in the previous source. Both baseline and
fixed whole-parent compiler source/OBJ evidence are preserved locally
under `.analysis/f701-fighter-four-tier-volley/`.

## Physical negatives: original GPR ownership and local EBP frames

**Do NOT declare strict/exact.** In the new original-shaped whole parent,
**136 genuine nonfield GPR/CFG instruction operand positions differ**
from original native, despite identical case opcode/length positions
and every genuine typed source target being accounted for. The native
saved `this` pointer is `EBP−0x44`; source saves `this` at **`EBP−0x28`**
(one actual prologue store and **2,526 actual source reloads**).
The source builds the four real loop indices at `EBP−0x18`, `−0x1C`,
`−0x20`, `−0x24` whereas native uses `−0x34`, `−0x38`, `−0x3C`,
`−0x40`. The original five integer-to-x87 conversion scratches
at `EBP−0x208/−0x20C/−0x210/−0x214/−0x218` compile at
`−0x9C/−0xA0/−0xA4/−0xA8/−0xAC`. All ten genuine six-byte
scratch instruction operands are checked separately; **none** is
normalized as mere cosmetic EBP difference.

## New source-context dependency — real adjacent cases and DATA

The newly restored four integer loops change actual VC7.1 compiler
frame allocation in *preceding* cases, even though their C++ is
unchanged. The F701 verifier checks ALL these against the **same new
whole-parent COFF**, not independent older cases:

| Original physical action | Current compiled context | Nonexact source facts |
| --- | --- | --- |
| `2F9`: 1,367 B /381 x86 /34 original fields | **1,331 B /381 x86 /34 fields** | 12 remaining six-byte/native versus three-byte/source scratch operands; four already have genuine wide source operands; 236 other normalized nonfield GPR/x87 differences |
| `2FA`: 971 B /279 x86 /31 original fields | **979 B /281 x86 /31 fields** | Two extra `FLD/FCOMPP` operations, actual `EBP−0x8C` scratch, real CFG differences |
| `2FB`: 647 B /181 x86 /17 original fields | **647 B /181 x86 /17 fields** | Natural source scratches now widen to six bytes, but `EBP−0x90/−0x94` instead of original `−0x1FC/−0x200`; 106 actual normalized nonfield GPR differences, four MOV/FLD reorders |
| `302`: **935 B /261 x86 /28 original fields** | **935 B /261 x86 /28 fields** | Correct opcode/width and typed fields, but 136 actual nonfield GPR/CFG operand differences and unproven EBP class frame |

The verifier rechecks all **27 previously context-strict nonterminal
internal cases** within the newly built full parent, earlier real
negative cases (including `2F8/2F9` and the two terminal `31B/31C`
GPR phase negatives), and the **complete independently owned 943-B
after-RET switch DATA**. It verifies 2FA's 31 and 2FB's 17 original
physical fields, 302's 28 fields, and the full native 31B/31C
following handler boundaries. The `f674` and `f684` helpers now
accept an explicit *previously verified source 302 end ordinal*,
instead of incorrectly searching for the old 302 placeholder marker.
Older F684/F696/F699 selected contexts keep their default behavior
and remain subject to separate regression checks.

Targeted reproduction (one new affected whole-giant TU, no 943-unit replay):

```bash
scripts/repo-python scripts/verify-fighter-four-tier-volley-f701.py
scripts/repo-python scripts/validate-tracking.py --require-target
```

Generated CPP/OBJ/PDB, compiler log, actual PE/COFF and full-context
verification receipt: ignored `.analysis/f701-fighter-four-tier-volley/`.
The original entire `00543210` giant is still **NONEXACT**; source
function names, owner layouts and class signatures remain provisional.
Formal credited authored whole-function coverage is **unchanged:
943 functions /862,726 native CODE bytes (43.71%)**. No external
Oracle exactness claim, no cropped case credited as separate function,
no artificial local padding or raw target-byte graft.
