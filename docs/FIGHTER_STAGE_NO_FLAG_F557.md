# F557 — 115-instruction, flag-clear-free action 6/7 in two entire giant originals

**Original Japanese TH075 1.11 native-PE C++ reconstruction evidence, not
accepted full-boss exactness.** Target SHA256 is
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
New native-only audit and fresh pinned VC7.1 source compiles establish
*complete action 6 and 7 subranges* in whole giant `00543210` (**58,294
original CODE bytes**) and `00564BE0` (**61,872 bytes**), together
**120,166 original CODE bytes currently nonexact**. Each original's entire
CODE SHA256 and physically owned post-RET dense/sparse jump DATA are
independently checked before the affected source is compiled.

## Real 115-instruction actor policy, not 117/104 from other fighters

Each of these two originals has genuine 115-instruction action 6 and 7
switch cases, physically bounded by the original seventh/eighth/ninth
DWORD switch targets. They have the real extra-stage `this+0x62`/x87
`this+0x54` comparison against original global `00657D14`, plus genuine
`0040FB40` auxiliary state calls, similar to the F556 117-instruction
fighters. However these two **omit `FLAG = 0`** within stage-position
initialization. This removes **two native instructions** versus their
117-instruction cousins; the probe removes a real C++ byte assignment,
not any machine bytes or a fabricated empty branch.

The original source-specific values are quite different:

| Original whole giant | Action 6 extra stage / callback | Action 7 extra stage / callback | Native stage | Stage x87 float position / speed | Action 7 position |
| --- | --- | --- | ---: | --- | --- |
| `0x00543210` | 3 / 4 | 4 / 5 | 3 | `19.0f` / `0.95f` | `7.0f` |
| `0x00564BE0` | 2 / 3 | 2 / 3 | 2 | `12.0f` / `0.4f` | `4.0f` |

In both families, the first state test uses 3/5 respectively and the
first `0040FAC0` call receives **0xCC/0xCD** respectively, but the extra
state threshold, second callback argument and stage-dependent float values
are intentionally **not** assumed identical across fighters. The actual
native vtable call is `dword ptr [edx]` in all four cases; it emerges
naturally from the original-profile VC7.1 C++ virtual method call.

## Physical native machine-code geometry and cold source proof

The non-wide `00543210` cases are **393 native CODE bytes** each, exactly
as emitted by the new source compiler. The unusual `00564BE0` original
cases are **508 native CODE bytes each**, against **393** emitted for the
isolated C++ source. This gap is fully, physically explained: the real
whole boss saves its receiver at `EBP-0x88`, so **37 original receiver
reloads per case** use disp32 instead of the small probe's disp8 (**111
additional machine bytes**), and one original `JL` grows from short to
near form (**4 bytes**), totaling **115 per case**. There is **no fake
padding/local or assembly** inserted to force a 508-byte result.

[`scripts/verify-fighter-stage-no-flag-source.py`](../scripts/verify-fighter-stage-no-flag-source.py)
reconstructs the entire real 115-instruction case directly from the native
PE and generates normal C++ by extending the prior F548 signed/float actor
source. It performs one or two separately selected serial compiles under
pinned MSVC 7.1 `/Od /Ob0 /Gy /GR- /GX- /GS /Zi`. Complete case bounds,
all real register assignments, actual x87 branch/operand roles, byte-exact
per-instruction lengths (or precisely validated wide-form exceptions),
per-fighter auxiliary calls and whole switch DATA are all verified.

- **4/4 cases, 460/460 native original x86 instruction roles** match
  precisely, including real per-character general register allocation.
- **32/32 genuine typed COFF `REL32`/`DIR32` fields** have the correct
  original target, physical call/float instruction ordinal and source symbol.
- **287 native-style DWORD switch COFF references**, every original
  default/duplicate handler partition, **669/669 exact original sparse
  index bytes**, and **1,817 after-RET DATA-shape bytes** are preserved.

```bash
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/verify-fighter-stage-no-flag-source.py --boss 0x00564BE0
# Run just both newly affected native C++ probe units, not full cold replay:
scripts/repo-python scripts/verify-fighter-stage-no-flag-source.py
```

Generated source, COFF, PDB, compiler logs and JSON receipts remain under
ignored `.analysis/f557-no-flag-source/`, and individual negative/reverse
source controls under `.analysis/f557-115-action6-7/`. The **1,802
original interior action 6+7 CODE bytes** remain wholly within **120,166
unmatched fighter CODE bytes**. No split-function exact credit, no all-
unit cold replay and no external Oracle receipt.
