# F624 — native 118-instruction mode/event action0x63 in two giant fighters

**Original pinned Japanese TH075 1.11 PE, normal MSVC VC7.1 natural
C++ in two complete whole-giant probe translation units.** Original
EXE SHA256 `bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
Both entire giant fighter `Advance()` functions remain NONEXACT; no
independent action case becomes an accepted complete authored function.

## Actual original 0x63 physical boundary is not the packed default slot

The native second compressed packed switch maps action `0x63` to
physical dense slot **25**, the final real case in its 49-byte sparse
index. Dense slot **26** points to a shared default handler, **NOT**
to the physical end of action0x63 or the next actual game action.
The independently verified next complete original code handler is
`0x8C`, beginning **immediately after the real 0x63 CODE extent**.
The verifier reads both real registered original handler addresses,
confirms their immediate ordering and the original case0x63 packed
slot 25, then finds the new generated case0x8C's actual following
`g_FighterProbeMarker=141` **COFF-typed instruction** as the
unambiguous emitted C++ case boundary. It does not cut the source at
packed default slot26 or at a convenient partial `RET`.

## The real mode-three predicate is a short circuit, not two simple alternatives

Native original x86 instruction 0 tests signed-byte global
`006714B4` against 3. Its **`JNE` jumps to instruction ordinal 7**,
not to the second group at ordinal27. Only when mode is exactly 3
does it inspect signed byte `this+0x2CD`, whose native `JNE` at
ordinal6 **jumps to ordinal27**. The authentic condition governing
the first-stage path is therefore:

```cpp
if (g_ModeAt006714B4 != 3 ||
    *reinterpret_cast<signed char*>(RAW+0x2CD) == 0) {
    // Stage-two path; original native state transition 0x5F
} else {
    // Three target-owner gated game action paths
}
```

The first natural C++ attempt instead used an intuitive
`if (mode==3) ... else ...`. It generated the complete **118
instructions /455-byte source geometry**, but had two incorrect
native CFG edges: original ordinal2 `JNE` target 7 versus source 27,
and original ordinal6 target 27 versus source 26. Independently
correcting the source semantic OR reproduces both true native edges.
The other important original behavior occurs when a target-specific
signed byte at `this+0x32A + this[0x39D]` equals **2**: it first
calls genuine game method `0040FAC0(0x31C)`. It then checks another
byte at `this+0x370 + this[0x39D]` for an actor-specific bonus flag.
The native `JNE` at ordinal54 goes directly to the original shared
case exit at ordinal58 **even when no extra bonus applies**. The
first C++ candidate incorrectly continued into the other branches
in that situation. Moving the ordinary C++ `break` **outside** the
optional bonus `if` fixes this actual behavior and exactly restores
native ordinal54 `JNE -> 58`.

The real two special owners have different concrete bonus values:

| Entire original fighter, still nonexact | Full original 0x63 native CODE | Genuine x86 roles | True typed PE/COFF fields | Original bonus flag/action |
| --- | ---: | ---: | ---: | --- |
| `00564BE0` | **552 B** | **118/118** | **8** | flag 4, native action `0x302` |
| `005AEEC0` | **455 B** | **118/118** | **8** | flag 5, native action `0x31D` |
| **F624: 2 real case interiors** | **1,007 B** | **236** | **16** | **zero whole-function exact credit** |

Other real branches require genuine owner `this+0x2E8` signed-short
stage `<150`, live signed-byte `this+0x39D >0`, and per-stage
lookups at `+0x32A` matching 2, 1 or 0. The corresponding original
game states set `0x31C`, `0x5F`, and optionally bonus 0x302/0x31D;
setting `this+0x3CF` on the 0x5F branch, and the final native
`0040FA30` frame state check and `0040FB40(2)` auxiliary transition
are preserved in source order. These are distinct original control-
flow guards; no guessed universal boss template is asserted for
other owners, whose native cases have 109/138 instructions instead.

## Complete GPR/x87/CFG and typed native PE/COFF verification

Tracked real C++ source:
[`FighterMode63F624.inc`](../probes/FighterMode63F624.inc).
Reproducible original-backed verifier:
[`verify-fighter-mode63-f624.py`](../scripts/verify-fighter-mode63-f624.py).

For each original whole-parent translation unit it cold-compiles
normal VC7.1 `/Od /Ob0 /Gy /GR- /GX- /GS /Zi` source and checks
**all 118 physical instruction starts, widths, true register/x87/CFG
operand roles, full native action extent, and eight genuinely typed
zero-addend physical COFF records** against actual pinned PE
callee/global targets. Those eight original fields are:

- `DIR32` on instruction0 `MOVSX` to actual signed-byte game global
  `006714B4`. Its source unlinked operand `[0]` is normalized **only
  after** verifying the physical COFF ordinal, type, zero addend,
  symbol and actual original PE target.
- Five actual `REL32` calls to game action method `0040FAC0`, at
  native instruction ordinals 22, 48, 57, 80 and 103.
- Real frame getter `0040FA30` at ordinal108 and auxiliary-state
  transition `0040FB40` at ordinal116, both genuine `REL32`.

The native wide-stack actor `00564BE0` has **31 genuine EBP−0x88
receiver MOVs widened three bytes each**, and one original native
`JLE` at ordinal30 expanded by four bytes: total
`455 + 31×3 + 4 = 552` original CODE bytes. The normal source
never fakes saved frame slots or widens instructions by padding.

Critically, **the same fresh new source OBJ** is also checked by the
strict F622 verifier for actual original case0x62, all earlier
F598–F614 **30 original game action case interiors** and the
entire separately owned after-RET switch DATA, including its typed
dense jump fields and literal sparse map. Original action0x5D/0x5E
and other later cases remain incomplete or from distinct source
register phases, not silently accepted by this proof.

## Accounting and bounded reproduction

F598–F622 had recorded **339 strictly source-backed original
case interiors /87,607 original native interior CODE bytes** across
separately compiled original giant probes. F624 adds **two**
complete 118-instruction original inner cases, **236 source-backed
x86 roles /1,007 native original internal CODE bytes /16 typed
COFF fields**: cumulative **341 distinct original internal case
subranges /88,614 native inner CODE bytes**. This is a bounded
research evidence total, **not** 341 jointly accepted whole functions,
and not a claim that all case proofs are simultaneously x86 exact
when the unfinished predecessor cases are inserted. The original
eleven fighter giants, the other original giant functions and the
three unmatched authored smaller whole functions remain NONEXACT.
Official accepted authored exact coverage remains **943 whole
functions /862,726 original CODE bytes**, with no target executable
modification, all-unit cold replay, manual ASM, fake stack locals or
external Oracle acceptance.

```bash
scripts/repo-python scripts/verify-fighter-mode63-f624.py --boss 0x00564BE0
scripts/repo-python scripts/verify-fighter-mode63-f624.py --boss 0x005AEEC0
# Optional ONLY these two affected original giant C++ source TUs:
scripts/repo-python scripts/verify-fighter-mode63-f624.py
scripts/repo-python scripts/validate-tracking.py --require-target
```

Fresh original-native matched C++ source, COFF/PDB, compiler logs,
physical PE/COFF typed field receipts and previous original case
regressions are under ignored `.analysis/f624-mode63-verified/`.
Actual preliminary competing C++ control-flow experiment evidence is
retained under `.analysis/f624-mode63/`.
