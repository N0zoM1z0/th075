# F603 — complete native stage-one projectile action0x46 in two final giant fighters

**Original Japanese TH075 1.11 PE verified; entire game giants remain
NONEXACT.** Executable SHA256 is
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
This is a bounded continuation of F602's fully source-reconstructed
104-instruction trajectory action inside nine huge fighter
`Advance()` routines. F603 does NOT substitute the smaller version
into the other two original huge functions. In `0045DD70` and
`0058AF60`, the actual original action0x46 occupies **459 whole
native interior bytes and 131 x86 instructions**, not 374/104.
Its extra **27 real instructions / 85 bytes** are a genuine
conditional *one-shot stage-one projectile spawn*, not padding,
a different saving convention, an invented helper or compiler noise.

## Genuine original PE-only action ownership

Each original native action0x46 is physically delimited by the real
second compressed-index switch's owned dense case0x46 and case0x47
DWORD destinations, with the original sparse map binding action
`0x46` to slot 11 and `0x47` to slot 12. The first 39 native
instructions initialize trajectory from original `+0x94/+0x98`,
clamp the two signed float motion values, set `+0x5C = 0.8f`
and clear integer `+0x7C`. The next **27 native instructions**
are not present in any of the nine compact F602 owners:

- Only when signed-short stage `+0x62 == 1`, frame `+0x64 == 0`,
  and real signed-short one-shot flag `+0xF0C == 0`, set that
  flag to **1** and call the actual game `thiscall` at `00453A70`.
- The original call pushes the actual signed-char direction at
  `+0x66`, actual 32-bit positions `+0x44/+0x48`, an original
  projectile-kind literal, and the native final integer side.
  No inferred pointer-to-parent ABI is substituted for the
  original native `ECX = this` receiver.
- `0045DD70` physically pushes kind `0x3B7` and side `1`, then
  follows stage `3`, early aux `4`, and late aux `5`.
  `0058AF60` pushes kind `0x3E7` and side `0`, then follows
  stage `2`, early aux `3`, and late aux `5`.

The remainder preserves the actual two float-to-short conversions
at original `+0xF00` and `+0xF02` via two distinct `__ftol2`
`REL32` calls to `006406AC`; the genuine `ResetAt453E20`,
`SetNativeActionAt40FAC0(0x61)`,
`InitTrajectoryAt453E60(2.0f)`, and
`PrepareActionAt453D60(0x16)` calls, and the original final
frame-match/aux transition. Both originals have real 2.0f and
12.0f clamp constants, using original physical floats `00657480`
and `006590C4`, not the 6.0f/25.0f configuration of most F602
fighters. There are **ten true original call instructions and
16 physical original typed COFF/global fields** per entire native
459-byte action.

## Natural C++ and full original-native verifier

Tracked [`FighterTrajectorySpawn46F603.inc`](../probes/FighterTrajectorySpawn46F603.inc)
contains the natural 131-instruction trajectory body, including
original `I16(0xF0C)` flag and `SpawnDirectedAt453A70(...)` invocation.
The two earlier F602 x87-expression order discoveries remain genuine
source expressions:

```cpp
POS54 = *(&POS54) + *(&F32(0x98));
I16(CONTACT_STAGE_OFFSET + 2) =
    static_cast<short>((POS54) * g_ContactProjectionAt00657888);
```

Each fighter's original owner parameters are **read from the actual
original machine instructions**, not a presumed shared character
layout. Newly compiled pinned VC7.1 `/Od /Ob0 /Gy /GR- /GX- /GS /Zi`
source emits **the same complete 131 instruction starts, sizes,
mnemonics and GPR/x87/CFG roles and exactly 459 bytes** for both
native action subranges. Both source objects have all **16 true
zero-addend COFF fields**, independently matched to their
original PE calls and float-global address destinations, including
the additional actual projectile-spawn call. The real original
source signed-byte `MOV AL,[EDX+0x66]` and actual
five-argument call ABI are checked rather than silently casting to
an unrelated `int`/float method.

[`verify-fighter-trajectory-spawn-f603.py`](../scripts/verify-fighter-trajectory-spawn-f603.py)
regenerates the actual original PE-backed giant C++ skeleton and
all F598/F600 earlier **23 real game actions**, inserts the genuine
new source action, and **only cold-compiles the selected new giant
translation unit**. It verifies the entire original 459-byte
case boundary/131-x86 shape, the native spawn flag, game events,
all 16 typed/target-checked physical COFF fields, and the complete
original seven-switch after-RET DATA shape. The prior 23 actual
C++ cases are reverified on that *same newly compiled object*;
no previous diagnostic OBJ can silently supply a matching result.

| Original enclosing whole fighter, still unmatched | New whole inner case CODE | X86 roles | Typed real fields | Native projectile | Native stage / aux |
| --- | ---: | ---: | ---: | --- | --- |
| `0045DD70` | 459 | 131 | 16 | `0x3B7`, side 1 | 3 / 4 / 5 |
| `0058AF60` | 459 | 131 | 16 | `0x3E7`, side 0 | 2 / 3 / 5 |
| **Total (F603 only)** | **918** | **262** | **32** | | |

With the nine F602 compact cases, this completes source-backed
**all 11 actual native action0x46 bodies**: **1,198 original x86
roles, 4,395 original *internal* CODE bytes, 167 genuine
PE/COFF fields**, under eleven independently compiled large-parent
sources. With earlier F598/F600 cases that is **264 original
internal game action bodies /59,629 original interior CODE bytes**.
These are NOT 264 independently callable complete functions.

**All eleven containing fighter bosses remain nonexact and the
official exact authored ledger remains 943 complete functions /
862,726 original CODE bytes.** The separately owned afterRET
jump DATA and runtime/game callees receive no implicit credit;
none of the unmatched parent CODE is promoted. No all-unit cold
replay, manual ASM, patched machine bytes, bogus source locals or
external Factory/Oracle acceptance was used.

## Targeted only: the two newly affected original source translation units

```bash
scripts/repo-python scripts/verify-fighter-trajectory-spawn-f603.py --boss 0x0045DD70
scripts/repo-python scripts/verify-fighter-trajectory-spawn-f603.py --boss 0x0058AF60
# Or only these two, not any previously exact unit:
scripts/repo-python scripts/verify-fighter-trajectory-spawn-f603.py
scripts/repo-python scripts/validate-tracking.py --require-target
```

New sources/COFF/PDB, compiler transcripts and original field/operand
receipts are retained in ignored `.analysis/f603-fighter-spawn-source/`;
prior natural source trials, including complete 131-instruction
matching first prototypes, are under `.analysis/f603-spawn-trajectory/`.
