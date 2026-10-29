# F610 — original 119-instruction native action0x4A in nine giant fighters

**Japanese TH075 1.11 original PE backed, natural pinned VC7.1 C++ source;
NO whole-giant acceptance.** Original target SHA256 is
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
F607/F608 had recovered the original complete action0x49 interiors
inside all eleven huge fighter `Advance()` functions. F610 extends the
*NINE regular* whole giant C++ source probes to the **next** original
second indexed switch action `0x4A`, bounded by the real original
packed dense jump slots 15 (action0x4A) and 16 (action0x4C), whose
physical sparse indices were checked directly from the original PE.
The intervening action0x4B is not an independent normal case body.

## Original control flow, x87 semantics and actual C++ source

The complete original native `0x4A` subrange is **119 instructions**:
434 physical CODE bytes in eight fighter originals, **556 bytes** in
native `00564BE0`, with **19 true original typed COFF references**.
The original stage/frame-zero action negates live float `this+0x94`
into `+0x50`, copies the 32-bit velocity bits from `+0x98` to `+0x54`
using a **raw DWORD MOV**, sets drag to 0.8f and clears `+0x7C`.
A real per-fighter stage test may dispatch early auxiliary state. A
true signed-byte `ContactAt454EE0()` query and an x87 compare of
`+0x50` against original float global `006590C0` determine whether
bounce is taken. If so, it changes native game action to `0x4C`,
negates and scales `+0x50` by the genuine float at `00657F74`, sets
`+0x54=15.0f`, `+0x5C=0.5f`, initializes a 2.0f motion and prepares
0x16, clears the original `+0xF00` (or `+0xEFC`) signed-short
trajectory slot, then exits the original switch.

Otherwise the actor subtracts drag and performs real original ground
contact using float `0065782C`. That path invokes two independent
native CRT `__ftol2` conversions into consecutive signed-short
trajectory members, plus the original reset, action0x61 transition and
trajectory initialization game calls. One crucial native distinction is
the placement of the **second `PrepareActionAt453D60(0x16)` call**:
most original fighters do this *before* the two x87 projections; native
`005D73C0` does so *after* the action0x61 transition and 2.0f
initialization. Both versions naturally compile to the same native
119-instruction/434-byte geometry but have genuinely different
call order/COFF x86 ordinals. F610 derives this choice from the
original PE instruction at ordinal 82 before producing its source.
Final frame equality checks retain real per-fighter late auxiliary
states, not guessed universal numbers.

Tracked real C++:
[`FighterTrajectoryBounce4AF610.inc`](../probes/FighterTrajectoryBounce4AF610.inc).
Its actual original source is ordinary `/Od /Ob0 /Gy /GR- /GX- /GS
/Zi` MSVC VC7.1, with source-level `#if F610_PREPARE_BEFORE` reflecting
those two confirmed original call sequences. It has no machine-code
copying, fake saved locals, inline assembly, or fabricated control-flow
markers used to force a match.

## Original whole-case verification and accounting

[`verify-fighter-trajectory-bounce-f610.py`](../scripts/verify-fighter-trajectory-bounce-f610.py)
independently decodes each original PE 119-instruction case, checks the
physical switch slots, actual compiler source COFF target symbol,
zero relocation addend and true original target destination for all
**19 DIR32/REL32 fields**, x86 GPR/x87/branch order and source widths.
It also builds the *whole selected giant* source afresh and rechecks
all **27 prior authentic original game case bodies** plus the entire
separately owned after-RET switch jump DATA on that same object.
For the real wide-frame actor `00564BE0`, original 556 vs generated
434 CODE bytes are explained by **38 genuine EBP−0x88 receiver MOVs
widening three bytes each and two original local conditional branches
widening four bytes each** (38×3+2×4=122 bytes). The exact widened
branch instruction ordinals are 39 (`JE`) and 81 (`JP`).

| Original containing giant (still nonexact) | New original entire 0x4A interior CODE | Original x86 | Native typed COFF |
| --- | ---: | ---: | ---: |
| `005D73C0` | 434 B | 119 | 19 |
| `00486550` | 434 B | 119 | 19 |
| `004AC040` | 434 B | 119 | 19 |
| `00543210` | 434 B | 119 | 19 |
| `00564BE0` | **556 B** | 119 | 19 |
| `004D7E70` | 434 B | 119 | 19 |
| `004F7130` | 434 B | 119 | 19 |
| `005AEEC0` | 434 B | 119 | 19 |
| `005214B0` | 434 B | 119 | 19 |
| **F610: 9 original inner cases** | **4,028 B** | **1,071** | **171** |

The other original fighters `0045DD70` and `0058AF60` each have
**165 x86 /589-byte** `0x4A` native cases with real extra projectile
spawn paths: these are **NOT claimed as matched** by the 119-insn
source, and require separate natural VC7.1 source work.
Cumulatively, with F598–F609, **306 original internal game case bodies
/74,989 original interior CODE bytes** have source-backed native
instruction-role and typed COFF evidence. These fragments are not
306 original callable functions or new exact units. The official
completed authored ledger remains **943 full functions/862,726 native
CODE bytes**, with 22 entire giant functions and three smaller
original authored functions still nonexact. No all-unit cold replay
or external Oracle exact acceptance.

## Reproduce only selected affected large translation units

```bash
scripts/repo-python scripts/verify-fighter-trajectory-bounce-f610.py --boss 0x004F7130
scripts/repo-python scripts/verify-fighter-trajectory-bounce-f610.py --boss 0x00564BE0
# Optional only the nine F610 affected giant C++ translation units:
scripts/repo-python scripts/verify-fighter-trajectory-bounce-f610.py
scripts/repo-python scripts/validate-tracking.py --require-target
```

Real original code/source compiler logs, selected C++/COFF/PDB and
actual case field receipts are under ignored `.analysis/f610-fighter-bounce-source/`;
first source hypothesis is in `.analysis/f610-bounce-trials/`.
