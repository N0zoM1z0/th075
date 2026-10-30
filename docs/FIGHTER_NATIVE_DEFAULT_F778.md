# F778 — original 00543210 common default action semantics and native dispatch aliases

**Whole-parent source reconstruction, not an exact accepted game function.**
Target: user-supplied Japanese TH075 v1.11 `resources/th075.exe`,
SHA-256 `bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
The original independently authored fighter `00543210` is **58,294
callable native CODE bytes** and owns **943 separately accounted
post-RET switch DATA bytes**. The actual compiler-shaped source is
not yet whole-function byte exact.

## Discovery: old common switch default was only a marker, not game source

The original PE dispatcher contains seven real tables, some with sparse
byte maps. An independent reread of the complete physical mapping,
not an assumption from historical prose, establishes **239 actual
action IDs** mapped to original handler **`00551598`**. This is the
true compiler switch default / missing-action handler. Before F778,
our full 58KB source incorrectly implemented that handler as a
`g_FighterProbeMarker=0` write. Thus the last native source gap was
*actual missing gameplay* rather than a stack-layout mystery.

At original `00551598..005515B8`, **32 real CODE bytes /10 x86
instructions** obtain the actual action via native game method
`0040FA30`, compare the signed getter against native actor state
`+0x70`, and when equal call game method **`0040FAC0(0)`** to
transition to action zero. This is the new ordinary C++
[`FighterNativeDefaultF778.inc`](../probes/FighterNativeDefaultF778.inc),
compiled into the **entire** parent, not as a new callable function:

```cpp
default:
    if (GetNativeActionAt40FA30()==S16(0x70))
        SetNativeActionAt40FAC0(0);
    break;
```

The pinned MSVC VC7.1 `/Od /Ob0 /Gy /GR- /GX- /GS /Zi`
compiler now emits all **10 original ordered native x86 mnemonics,
widths and instruction starts** for this 32-B policy. The two
original PE `REL32` call destinations **`0040FA30`** and **`0040FAC0`**
are independently decoded from original machine bytes and checked
against both real zero-addend COFF source call fields.

**Four actual original register-operand bytes at native guard offsets
`+0A`, `+0C`, `+10`, `+13` remain wrong** (native `ECX/EDX/EAX`
versus source `EDX/EAX/ECX`), and they are not ignored or claimed
byte exact. Eleven normal original-shaped full-parent variations of
comparison operand order, real signed member lvalues and legitimate
used return temporaries did not improve that original four-byte
GPR allocation without introducing worse stack or opcode differences.

## Resolving 33-byte gap: two different causes, not blind filler

In previous full F771 source, real original was **58,294 CODE B/
16,471 x86** versus source **58,261 B/16,459 x86**. A re-read of
*all* native table-mapped handler boundaries shows:

- The entire initial dispatch prefix before first handler
  `005433B3` is **419 B/90 x86** in both native/source.
- Across **141 consecutive distinct mapped handler intervals**,
  all sizes match except actual native `0x63` at `00545ADE`,
  **706 original B/189 x86 vs 705 generated B/189 x86**.
  Three genuine `CMP 0x96` EAX/ECX/EDX encoding choices account
  for this net **one-byte shortfall**. F777 already disproved the
  older F626 "strict" label in the current compiler context.
- From original common default entry `00551598` to original RET
  `005515C7`, the native suffix is **46 B/16 x86**. The older
  probe marker represented only **14 B/4 x86** there. Restoring
  the real default guard produces **36 B/13 x86** in the source:
  real policy 32 B/10 x86 plus function epilogue.

As a result the **new complete normal C++ giant** is
**58,283 native-shaped CODE B/16,468 x86**, only **11 B/3 x86
shorter** than the original. This is a **22-byte recovery** of
actual game-source policy, not a new exact function. The original
remaining tail bytes are a **two-byte JMP** at `005515B8` and an
**eight-byte getter call** at `005515BA`, ahead of the epilogue;
together these account for 10 B/3 x86, with the last 1 B in the
`0x63` GPR-size context. The current source does not invent a
functionally unneeded call or unconditional branch to fill them.

We compiled additional honest negative C++ controls: putting an
extra getter on the post-switch path made the compiler reproduce
**58,293 B/16,471 x86**, nearly the original global shape; however
these variants incorrectly routed the *other real case `break`
edges* through that additional getter instead of the original
shared epilogue. Therefore they are **rejected as semantically
incorrect**, despite an attractive byte-length number. The
tracked F778 source instead preserves original case exits and
reports the unmatched suffix as negative evidence.

## Selected fresh whole-parent verifier; no mass cold replay

Run exactly one affected full original-shaped fighter source build:

```bash
scripts/repo-python scripts/verify-fighter-native-default-f778.py
# Real native default: 239 original aliases, 32B/10 x86/2 physical refs
# Four genuine GPR-operand bytes still wrong
# Full fighter 58283/58294 CODE B, still NONEXACT
```

The tracked [`F778 verifier`](../scripts/verify-fighter-native-default-f778.py)
regenerates all previous natural C8–CE/1F6–1F8/2DB/2F8–2FB
full-parent game source, inserts the native default into the genuine
whole C++ switch, **freshly compiles only that one VC7.1 TU**, then
checks the entire original PE handler map, physical two target calls,
ten original guard instruction sizes/positions and the four wrong
register bytes. It also revalidates all selected earlier native
complete case interiors, preserving the honest prior 2F8/2F9/2FA/
2FB GPR negatives, and the complete **943-B separately owned
original post-RET jump DATA** (156 true DIR32 label references and
319/319 other sparse-map bytes). No after-RET DATA is counted as
callable game CODE.

The original authored **whole `00543210` remains NONEXACT**:
missing native 11 CODE bytes, 3 original instruction ordinals and
other register/shared-tail displacements. Official whole-authored
exact ledger remains **977 functions / 868,036 original CODE bytes**
(**43.98% reviewed**), with 22 giant and five smaller original
whole functions not accepted. The 98% goal is still incomplete.
Original EXE is unchanged; no speculative origin promotion, split
case CODE credit, original-byte graft, dummy stack padding or
all-977-unit cold replay occurred. Full compiler/COFF/PE receipts
are under ignored `.analysis/f778-fighter-default-native-whole/`.
