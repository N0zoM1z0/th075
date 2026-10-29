# F671 — full original fighter 0x258 four-projectile C++ source, genuine EBP negative

Original target: pinned user-supplied Japanese TH075 version 1.11
`resources/th075.exe`, SHA256
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
This work reconstructs the **entire physical 502-byte original native
handler `0x258`** inside the genuine fighter giant `00543210`.
It is intentionally **NONSTRICT**: all original x86 instruction roles and
physical PE/COFF references are recovered, but eight real EBP scratch
operands are still wrong. The entire 58,294-byte enclosing parent
plus 943 separately owned after-RET switch DATA bytes remains
**whole-NONEXACT**. This case earns neither strict inner-case credit
nor an independently exact whole game function.

## Original complete native source grammar and four distinct projectiles

Original native 0x258 covers actual physical `0054CA22`–`0054CC18`:
**502 native CODE bytes, 134 x86 instructions and 12 genuine typed
PE/COFF fields**. Real stage/frame-zero control sets `I32(+0x7C)=1`
and calls original reset `00453E20`. On native stage 4/frame 0,
it first calls the original animation method `0046D000(100)`.
It then sets float velocity/angle fields `+0x314/+0x318` and emits
**four distinct original kind `0x322` resource shots** via genuine
`00453A70`, preserving their exact native byte, x87 and call order:

| Shot | Real float +0x314/+0x318 | X from signed `+0x66` | Original Y float operand |
| --- | --- | --- | --- |
| 1 | `−110.0f`, `5.0f` | `side * 40 + F32(+0x44)` | `F32(+0x48) + 006591EC` |
| 2 | `110.0f`, `5.0f` | `side * 40 + F32(+0x44)` | `F32(+0x48) + 006581DC` |
| 3 | `−70.0f`, `4.0f` | `side * 75 + F32(+0x44)` | `F32(+0x48) + 0065908C` |
| 4 | `70.0f`, `4.0f` | `side * 75 + F32(+0x44)` | `F32(+0x48) + 00657888` |

After the four projectiles, it compares actual native
`0040FA30()` to original short `+0x70` and transitions through
`0040FAC0(0)` when they match. The source's
`SpawnFloatXYAt453A70` declaration is a **provisional compiler ABI
proxy**, not a historical C++ method signature assertion.

The ordinary C++ fragment
[`FighterFourShotBarrageF671.inc`](../probes/FighterFourShotBarrageF671.inc)
is included in one full regenerated giant, with natural
`float(signed_direction * 40/75)` and typed float members, no
manual x86 bytes, invented padding, ASM, or faked EBP locals.
Its `(*(&POS48))` typed identity lvalue preserves the authentic
native **FLD Y member before FADD original PE global** evaluation.
All **134 native x86 mnemonic/CFG/GPR/x87 roles**, four original
`IMUL` signed-side multiplication forms, and **all twelve physical
zero-addend typed `REL32`/`DIR32` source fields** match native PE,
after normalizing *only independently verified unlinked global
float addresses*. Actual original reset, animation, four sprite
calls, float globals and native action query/set are individually
checked against genuine COFF symbols/physical operand ordinals.

## Why the new source is still NONSTRICT

The actual original compiler stores four separately meaningful
integer-to-x87 float temporaries in **eight full-width instructions**:

| Original case x86 ordinal pair | Original `MOV [EBP],reg; FILD [EBP]` | Current full-parent emitted temporary |
| --- | --- | --- |
| `39/40` | `EBP−0x114` | `EBP−0x2C` |
| `64/65` | `EBP−0x118` | `EBP−0x30` |
| `89/90` | `EBP−0x11C` | `EBP−0x34` |
| `114/115` | `EBP−0x120` | `EBP−0x38` |

Each original instruction is six bytes; the current C++ compiler
emits a three-byte instruction because its temporary slots are
much closer to EBP. The only **eight genuine non-field original
operand/width mismatches** therefore reduce the compiled case to
**478 bytes versus 502 original** (24 bytes shorter).
The earlier F598 normalization erases all EBP local offsets, so
using that comparator alone would incorrectly report an exact case.
The new verifier explicitly compares **raw original versus compiler
EBP operands**, only allowing the already authenticated receiver
save `EBP−0x44` → new `EBP−8`, and **requires exactly these eight
mismatches**. No fake earlier local declarations were added merely
to push the four integer-to-float slots to their original positions.
The real missing original parent stack-lifetime and earlier case
source context remain open reconstruction work.

## Reproducible selected whole-parent verification

[`verify-fighter-four-shot-barrage-f671.py`](../scripts/verify-fighter-four-shot-barrage-f671.py)
regenerates the entire original fighter parent using tracked natural
native C++ cases and original dispatch fingerprints, cold-builds
**only that full giant** using pinned VC7.1 `/Od /Ob0 /Gy /GR-
/GX- /GS /Zi`, checks this genuine 502-byte original case and
all 12 source fields, and also fully rechecks **all 25 previous
context-strict original native cases** (including the six consecutive
252–257 handler source bodies), the three older original
`186/18A/18B` EBP scratch negatives, and every original independently
owned after-RET jump DATA byte **in the same newly compiled C++
parent**. The genuine next physical handler is `0x259`, not a
cropped pseudo-function split.

The selected giant retains **25 context-strict native interiors /
1,840 original x86 /6,387 original internal CODE bytes /167 true
PE/COFF fields**. F671 adds **zero strict inner case bodies** and
zero accepted whole-function CODE. The overall F598–F671
context-strict original native fighter interior cohort remains
**593 /160,089 internal CODE bytes**, all uncredited because their
original 22 giant enclosing functions remain whole-NONEXACT.
Official accepted game-authored entire CODE remains
**943 whole functions /862,726 bytes (43.71% reviewed)**.

```bash
scripts/repo-python scripts/verify-fighter-four-shot-barrage-f671.py
scripts/repo-python scripts/verify-fighter-post-counter-f669.py
scripts/repo-python scripts/validate-tracking.py --require-target
```

All actual source/COFF/PDB, native PE field receipts and compiler
transcripts are preserved under ignored `.analysis/f671-fighter-four-shot-barrage/`
and source-grammar trials under `.analysis/f671-complex-barrage/`.
No original EXE modifications, fabricated locals, all-943-unit cold
replay or external Oracle whole-function acceptance was performed.
