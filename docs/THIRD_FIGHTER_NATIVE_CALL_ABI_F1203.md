# F1203–F1204 — reconcile 004AC040's real narrow callee interfaces

The live complete
[`F1020 parent`](../probes/FighterWhole004AC040F1020.cpp) now declares sixteen
effect, sound, animation-counter and scalar/command aliases with the parameter
types supported by ten existing cold-exact native callees. This corrects the
caller interface while preserving **all 83,922 candidate CODE+DATA bytes**.
The whole function remains **NONEXACT**: 6,958 GPR positions and twelve
instruction widths still differ from the original.

## Independent accepted interfaces and native argument transport

| Original callee | Supported caller parameter types | Existing accepted source |
| --- | --- | --- |
| 00453A70 | short effect, float-coordinate transport, signed-char facing/layer | `FighterEffectPoliciesF135::SpawnBattleEffect` |
| 00453B50 | As above, plus unsigned-char linked/mode | `FighterEffectPoliciesF135::SpawnTrackedEffect` |
| 00453C80 | short effect, float-coordinate transport, signed-char facing/layer | `FighterEffectPoliciesF135::SpawnAuxEffect` |
| 00453D40 /00453D60 | short sound | `PlaySound` /`PlaySharedSound` |
| 0040FAC0 /0040FB40 | short counter value | `AnimationState::ResetPrimaryCounters` /`ResetSecondaryCounter` |
| 00453E80 | short value | `FighterMoveScalarHelpers::SetNonnegativeWord` |
| 00454A70 | unsigned-char mode | `FighterMoveScalarHelpers::BeginFadeParameters` |
| 00454BC0 | int selection, unsigned-char mode, unsigned-int mask | `FighterCommandSelection454BC0::SetCommandSelection` |

The effect/sound models are in
[`FighterEffectPolicies.cpp`](../src/FighterEffectPolicies.cpp) and its
[`declaration-only header`](../src/FighterEffectPolicies.hpp); counter models
are in [`GameLeafHelpers.cpp`](../src/GameLeafHelpers.cpp). Scalar and command
models are in [`FighterMoveScalarHelpers.cpp`](../src/FighterMoveScalarHelpers.cpp)
and [`FighterCommandSelection454BC0.cpp`](../src/FighterCommandSelection454BC0.cpp).
These accepted sources/headers are unchanged.

Every one of the ten complete native callee bodies was independently reread
from the pinned Japanese original, SHA256
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
The effect wrappers load the ID as WORD [EBP+8], facing/layer as bytes, and
coordinate values as raw DWORDs. Tracked-effect linked is explicitly
zero-extended from [EBP+1C]; its mode is byte [EBP+20]. Native RET cleanup
remains 20 bytes for the five-argument wrappers and 28 for seven arguments.
Sound and nonnegative-word helpers sign-extend their WORD inputs. Counter
setters preserve WORD stores; fade mode is byte transport, and command
selection forwards a byte mode and a DWORD mask.

Signedness that the low-byte copy alone cannot distinguish follows the
existing independently accepted interface model; this is not a claim that
the original private source identifiers or complete class declarations are
known. No incomplete owner is constructed or embedded.

The nine effect aliases retain their existing numeric-float and raw-DWORD
coordinate views. A raw integer argument carries the original float bits;
it is not converted numerically to float. Only the effect ID, facing/layer
and flag types change. The other seven aliases reconcile the independently
supported sound, counter, scalar and command inputs. Existing thiscall
receivers, stack-slot widths and cleanup remain unchanged.

## Complete selected-parent cold build

The unchanged
[F1028 research verifier](../scripts/verify-third-fighter-whole-82kb-pe-targets-f1028.py)
cold-built only the tracked parent with pinned VC7.1:
`/Od /Ob0 /Gy /GR- /GX /GS /Zi /I src /I probes`.
The subsequent complete audit confirms:

- All 82,796 CODE bytes and 1,126 afterRET DATA bytes are identical to F1200's
  candidate. All 2,352 COFF field shapes, offsets, types, addends and local
  target offsets are unchanged.
- Exactly **823 external decorated symbols** change to the reconciled
  parameter signatures. Every actual native destination stays unchanged;
  all 2,201 CODE destinations, 151 dense ordinals and 522 sparse bytes agree.
- Frame 0x720, saved-this EBP-0x64, all 7,432 EBP positions, all 1,927 direct
  targets and all non-GPR operands remain verified.
- The ignored trial and fresh tracked builds have identical entire CODE+DATA
  and COFF records. All 6,958 GPR-debt and twelve width-debt rows are unchanged.

This is an interface adoption with no added exact bytes. Original physical
relocation-offset equality and complete callable byte equality remain unproved.

## F1204 — bounded native receiver control in 25B

The 577-GPR-debt 25B handler's 36 genuine float-coordinate calls were also
compiled through `reinterpret_cast<FighterEffectPoliciesF135*>(this)` and the
existing `SpawnBattleEffect` interface. This uses the same original zero-offset
receiver and actual accepted callee, preserving the real 36-call body.

The complete compiled parent has every CODE+DATA byte and all COFF field
shapes/addends/destinations identical to the new selected parent. Only the
36 external call names and 161 compiler-local names change; all local
offsets stay unchanged. GPR and width debt are unchanged, including
25B's 577 positions. No receiver variant is adopted; this excludes that
particular borrowed-callee spelling as a register-phase fix.

## Retained evidence and validation scope

`.analysis/f1203-third-native-call-abi/` retains `before.cpp`, `before.obj`,
`native-abi.cpp`, `native-abi.obj`, `tracked.obj`, complete audit JSONs,
`declaration-changes.json`, `native-callee-interfaces.json`,
`native-parameter-symbol-changes.json`, `whole-audit.py`, `make-receipt.py`
and `verified-summary.json` with recursive source, callee-source and artifact
SHA256 values. Previous F1028 output is preserved in `f1028-before/`.

The F1204 whole source/include, compiler object/log, complete audit and
symbol-change receipt are retained in
`.analysis/f1204-third-typed-effect-receiver/`. The F1201 per-state native debt
map remains applicable because every GPR/width row is unchanged.

No canonical accepted input, origin, exact manifest or comparison infrastructure
changes. Target/tracking/handoff and whitespace checks pass. Only affected
whole-parent builds are run; no full CI, corpus replay, historical origin
retest or per-function test is added. All 22 authored giants remain pending.
