# F577 — complete 279-instruction CharacterObject direction reversal action 0x332

**Pinned Japanese TH075 1.11 original native source/VC7.1 C++ evidence;
no byte-exact whole giant or cropped case credit.** Entire original PE
SHA256:
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.

F577 recovers the next real native game-action body inside original giant
`004EBDA0` (**33,293 complete original CODE bytes**), following the F576
complete source of 17 previous game actions. The native original compressed
switch physically bounds **action `0x332` to the next *nondefault*
original action `0x335`**. The original entries `0x333` and `0x334`
are default-target aliases, **not additional real game-action cases**.
We never assume case IDs must be contiguous original CODE addresses.
The entire original PE CODE and separately owned jump DATA are SHA-verified
before newly compiling the selected C++ source.

## Original native game logic, not a clone of the preceding two cases

The **entire native action0x332** contains **279 x86 instructions /
1,019 original CODE bytes**. Its true first-stage parent state checks,
eight-effect `00453A70(0x3E4)` creation, original `0x3E3` saturation,
actor x87 motion/stage updates, frame-11 scale decay, native callbacks
and random effect spawn share visible structure with action0x330, but
are **distinct original source behavior**:

- Stage-zero position `+0x50` is **+6.0f** and native velocity `+0x54`
  is **+4.5f**, not the `−4.0f/+6.0f` of action0x330 or the
  `+3.0f/+16.0f` of action0x331.
- At the original transition `S16(+0x62)==1 && S16(+0x64)==0`,
  after real zero motion stores, it performs a *genuine signed direction
  byte reversal*: `S8(+0x66) = -S8(+0x66)`. This adds exactly five
  original native x86 instructions, including real `MOVSX`, `NEG EAX`
  and `MOV [owner+0x66],AL`, which the natural C++ reproduces.
- The stage-9 computed-position effect-spawn ID is native **`0x322`**,
  not `0x320` from action0x330. The actual random call
  `00455580`, parent `00453A70`, and parent `00453D40(6)` are
  independently checked at their new correct instruction ordinals,
  rather than assumed from a 274-instruction template.
- The stage-zero native velocity subtraction uses real original
  float global `006583FC`. This is independently attested: the
  previous action0x331 instead uses the different native `00659090`.

## Original 1,019 bytes versus selected natural VC7.1 1,013 bytes

The new normal C++ source compiles to **279 x86 instructions /
1,013 CODE bytes**, with all original per-fighter EAX/ECX/EDX
register roles, x87 operand semantics, signed-byte negation, native
conditional branch targets, state methods and gameplay stores intact.
Two physical original source-instruction positions **97/98** differ
in length: the original giant saves an integer-to-FPU temporary
at **`EBP−0x9C`** (a disp32 `MOV` and `FILD`), while the smaller
isolated diagnostic C++ stack uses **`EBP−0x80`** (disp8) for
that same real temporary. Each original native instruction requires
exactly **3 extra bytes**, explaining the entire **6-byte** total gap.
All other 277 native action0x332 instructions retain their original
machine-size and operand/CFG grammar. **No synthetic local array,
compiler-byte padding, ASM, or original machine-code graft** was used
to force the original larger frame in an incomplete whole function.

## Whole original physical source and COFF proof

The tracked reproducer
[`scripts/verify-characterobject-direction-reversal-f577.py`](../scripts/verify-characterobject-direction-reversal-f577.py)
recompiles just one affected normal VC7.1 C++ TU from the tracked
[`probes/CharacterObjectActionsF572.cpp`](../probes/CharacterObjectActionsF572.cpp),
under `/Od /Ob0 /Gy /GR- /GX- /GS /Zi`. It independently rechecks the
whole original PE, the actual 60 physical jump-handler DWORD fields,
198 byte-identical compressed index bytes, original sparse/default
partitions and 438 separately owned after-RET DATA-layout bytes.

It also independently rechecks all 17 previous native game-action
bodies and their authentic original `REL32`/`DIR32` call/global
physical COFF positions and source symbols. For this new action0x332
it proves all **16/16** actual original call/x87 globals at the
correct new instruction ordinals, including native effect-spawn
call at ordinal **273** (not sibling action0x330's ordinal 268).
It permits only the proven pair of `EBP−0x9C` original disp32
width expansions, *not* arbitrary instruction-count or source
control-flow mismatches.

| Physically original game-action cases in same source | Native x86 instructions | Original inner CODE (NOT independently exact) | Genuine typed COFF fields | Known source/whole-frame caveats |
| --- | ---: | ---: | ---: | --- |
| Previous 17 real actions through `0x331` | 2,054 | 7,593 B | 145 | Two bounded MOV/FLD swaps; 18+18 native stack-spill bytes |
| New `0x332` | **279** | **1,019 B** | **16** | Two wider real EBP ops, +6 native bytes |
| **Total 18 real action bodies** | **2,333** | **8,612 B** | **161** | Whole 33K boss remains nonexact |

```bash
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/verify-characterobject-direction-reversal-f577.py
# Revalidate previous real source cases in the same C++:
scripts/repo-python scripts/verify-characterobject-fire-actions-f576.py
scripts/repo-python scripts/verify-characterobject-fade-actions-f575.py
```

All previous original-backed source, negative compiler experiments,
physical original code-disassemblies, independent new case-by-case
alignment and COFF logs remain preserved under ignored
`.analysis/f577-characterobject-action332/` and
`.analysis/f577-characterobject-direction-source/`.
The **8,612 inner original CODE bytes are still part of an unmatched
33,293-byte full native giant**, not 18 independently exact
functions. The many later original action bodies and true owner
class/whole stack lifetimes remain outstanding; zero new accepted
whole/split CODE or DATA credit, no all-unit cold replay, no external
Factory/Oracle receipt.
