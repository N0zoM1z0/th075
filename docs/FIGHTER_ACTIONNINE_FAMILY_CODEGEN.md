# F547 — natural C++ action-nine body in eleven full original giant fighter controls

**Original-target research and freshly compiled C++ only; no whole giant
is exact and no partial CODE earns authored credit.** All original native
observations use the supplied Japanese TH075 1.11 PE, SHA256
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
This work builds on the six genuine native action cases and original switch
partition independently reconstructed in [F545](FIGHTER_OPENING_SIX_CASES_CODEGEN.md).
Each candidate is a small, serially rebuilt natural VC7.1 C++ source
*probe*, with deliberately nonoriginal diagnostic stores for still-unrestored
actions. The enclosing full 613,391 original CODE bytes are never truncated
to invent exact coverage.

## What the entire native case 9 actually does

The tenth and eleventh physical DWORD entries in each fighter's first original
11-slot switch delimit an **entire 42-instruction native action-nine case**.
The genuine original logic updates the float at receiver +0x5C if it equals
native threshold global `0065782C`, writes the true float **0.6f**, subtracts
that member from float at +0x54, then tests the sum of real float fields
+0x48 and +0x54. If the sum is at most the threshold, the case invokes
`0040FAC0(10)`, clears +0x48, invokes `00453E20` and **returns from the
whole native boss**. Otherwise it reads signed-short state via `0040FA30`,
compares to real signed-short receiver +0x70 and conditionally calls
`0040FB40` with a fighter-specific integer argument.

The natural source is approximately:

```cpp
if (POS5C == g_ThresholdAt0065782C)
    POS5C = 0.6f;
POS54 = POS54 - POS5C;
if (POS48 + POS54 <= g_ThresholdAt0065782C) {
    SetNativeActionAt40FAC0(10);
    POS48 = 0.0f;
    ResetAt453E20();
    return;
}
if (GetNativeActionAt40FA30() == I16(0x70))
    SetAuxActionAt40FB40(native_fighter_specific_argument);
```

The unparenthesized float-member lvalue form and `POS54 = POS54 - POS5C`
restore the physical original `FLD, FLD, FUCOMPP, TEST AH,0x44, JP` and
subsequent `FSUB` operand ordering. The real `<=` restores native
`FCOMP, TEST AH,0x41, JP`. Source `return` is native-backed by the original
jump to the enclosing function's common return rather than an inert dummy
return. **Earlier plausible `!=`, reversed operand, `>=`, or `else if`
probes did not match all original opcodes/branch sizes.** Their complete
failed C++ and COFF objects are preserved in `.analysis/f547-action-nine/`.

There is one independently original per-fighter exception: **`00543210`
passes `1`**, not `0`, to actual `0040FB40`. The original x86 physically
contains `PUSH 1` at action-nine instruction 38; the other ten cases
contain `PUSH 0`. This source was changed only after independently
reading that instruction, not by assuming all fighter helpers agree.

## Per-fighter original observations and fresh compiler results

| Whole original boss | Entire original case-9 CODE (not accepted) | Natural C++ case | Physical typed case refs | Exact GPR allocation | Native auxiliary argument |
| --- | ---: | ---: | ---: | --- | ---: |
| `0x0045DD70` | 144 bytes | 144 bytes | 6 | Yes | 0 |
| `0x00486550` | 144 bytes | 144 bytes | 6 | No | 0 |
| `0x004AC040` | 144 bytes | 144 bytes | 6 | Yes | 0 |
| `0x004D7E70` | 144 bytes | 144 bytes | 6 | No | 0 |
| `0x004F7130` | 144 bytes | 144 bytes | 6 | No | 0 |
| `0x005214B0` | 144 bytes | 144 bytes | 6 | Yes | 0 |
| `0x00543210` | 144 bytes | 144 bytes | 6 | No | 1 |
| `0x00564BE0` | 183 bytes | 144 bytes | 6 | Yes | 0 |
| `0x0058AF60` | 144 bytes | 144 bytes | 6 | Yes | 0 |
| `0x005AEEC0` | 144 bytes | 144 bytes | 6 | No | 0 |
| `0x005D73C0` | 144 bytes | 144 bytes | 6 | Yes | 0 |

All **11/11** individual C++ probe translation units were freshly compiled
under pinned VC7.1 `/Od /Ob0 /Gy /GR- /GX- /GS /Zi`, after independently
checking their *whole* native fighter CODE hash, native switch targets,
actual instruction boundaries and complete owned post-RET table DATA.
Every source case reproduces **42 ordered original x86 instruction kinds,
real field offsets/typed x87 operands, branching and case exits**, plus
**6/6 real physical typed COFF call/global fields**. Receiver use/thiscall
ECX/dataflow is individually checked, rather than globally ignoring
register choices. **Six fighters also reproduce every exact original
EAX/ECX/EDX allocation**; in the remaining **five**, the case-local free
registers differ from the physical giant-boss original and must be fixed
through accurate surrounding source. Therefore these five are *not*
register-exact, let alone whole-function byte-exact.

Together they reproduce **66 native typed COFF reference roles**, all
**1,607 original-style jump DWORD COFF references**, the same physical
case-target equivalence/default partitions and **4,502 byte-identical
original sparse action index bytes** across real post-RET DATA shapes of
10,930 bytes. The original eleven action-nine bodies occupy **1,623 CODE
bytes inside the unmatched giants** (ten ×144, one ×183). The source
cases emit 144 bytes each; the special original `00564BE0` has the
larger 183-byte case because exactly **13 physical receiver-pointer reloads
at EBP-0x88** require disp32, adding 39 native bytes. No artificial
padding/locals or native-byte copying is used to force length agreement.

## Reproduce only affected units

```bash
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/verify-fighter-boss-family.py
# Just one original giant context and fresh corresponding small source probe:
scripts/repo-python scripts/verify-fighter-actionnine-natural-source.py --boss 0x00543210
# All eleven fresh action-nine probes, serially; NOT a full cold replay:
scripts/repo-python scripts/verify-fighter-actionnine-natural-source.py
```

The deterministic source/COFF/compilation logs and complete comparison
summary are retained in ignored `.analysis/f547-action-nine-natural-source/`;
failed alternative-source controls remain in `.analysis/f547-action-nine/`.
This advances natural C++ work inside large original bosses, but **the
complete giant fighter source, owner layout and other actions remain
unreconstructed**. No `config/matches.csv` or exact-unit manifest is
changed, no accepted CODE/DATA credit is claimed, and there is no external
Factory/Oracle receipt or all-unit cold replay.
