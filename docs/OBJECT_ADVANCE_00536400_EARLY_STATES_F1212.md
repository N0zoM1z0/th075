# F1212 — restore original 801–811 behavior in 00536400

The same [natural C++ body](../probes/CharacterObjectActions00536400F1211.cpp)
now contains **33 of 66 nondefault states**, adding the actual 801–811 logic
to F1211's history relay and states. No marker bodies or synthetic locals are
used. **33 states remain unwritten**, so the entire original 39,999B function
is still NONEXACT and receives zero exact credit.

## Native behavior recovered

- 801/802 follow the owner's distinct actions with native position offsets,
  hit reset, transform, asymmetric scale evolution and wrapping alpha fade.
- 803/805/807 retain cancellation order, three separate effect-996 calls,
  the owner sound callback, stage-2 parameter transfer and conditional child
  creation. The parameter transfer still occurs when the child is suppressed.
- 804/806/808 preserve the original float-to-short conversions, three distinct
  angle-limit policies, minimum speed, hit transition, motion/bounds checks
  and fade. The unusual angle assignments are retained, not regularized.
- 809 retains its owner-stage transition and scale/fade sequence.
- 810 restores the owner F12/F10 path, indexed mode-byte access, difficulty-3
  extra object, five action transitions, signed-facing pursuit expressions,
  tracked/untracked effects and frame-bound random scaling.
- 811 retains the observed facing/link selection, gravity, motion and fade.

The three new owner callback declarations follow existing exact F135 sources:
`00453D40`/`00453D60` consume a short sound ID, and `00453B50` consumes the
short/float/float/signed-byte/signed-byte/unsigned-byte/unsigned-byte contract.
Only this unaccepted research header is affected; no canonical input changes.

## Source operand order and native control flow

Native instructions independently resolve details that the decompiler elides:
804/806/808 initialize speed from `1000 - parameter*60`, convert the aimed angle
after division by the original radians constant, and keep both independent
angle tests. In 801/802, the owner-coordinate operand precedes the facing
integer expression in source; it restores the actual pointer-load order.
The alpha predicate is unsigned-byte **greater than zero**, preserving native
JLE rather than an apparently equivalent JE. The indexed owner byte uses
`owner + 370h + selected-index` in its actual operand order. The negative-facing
pursuit expression likewise reads the owner coordinate before the integer
offset. All changes are ordinary meaningful C++ operations.

Fresh builds use the unchanged diagnostic profile
`/Od /Ob0 /Gy /GR- /GX- /GS /Zi /I src /I probes`, pinned VC7.1, headless and
serial. Current output is **16,603 CODE B /4,402 x86**, frame **0x124** versus
original **0x2A0**. The original saved-this/history/index slots remain correct.
The source has 34 dense entries and 199 sparse bytes versus original 67/199.

All 33 written intervals and the prefix pass the explicit GPR/negative-stack-
elided operand diagnostic. It checks actual helper destinations, field
offsets, native conditional target ordinals and actual COFF literal payloads;
the writable difficulty global is compared by its native address. This is
research evidence, not a complete byte comparison or acceptance.

Additionally, the prefix and every actual nondefault interval through state
827 have **zero raw GPR-role, EBP-operand or instruction-width differences**.
Their scalar operands agree apart from the deliberately unresolved whole
frame allocation. Real forward-branch displacements and table addresses still
depend on unwritten later code. No interior becomes a separate accepted unit;
all original CODE bytes remain pending. Other later written states still have
real context-dependent GPR/stack/width residuals.

## Retention and continuation

`.analysis/f1212-object-536400-801-811/` retains the F1211 source/header snapshots,
all three new source/build/listing stages, actual native observations, local
`add-states.py`, `diagnose-source.py`, selected **`current.obj`** /`current.asm`,
immutable `current.cpp` /`current.hpp`, `current-source-diagnostic.json` and
`verified-summary.json`. The prior F1211 whole native/decompiler exports and
all earlier objects remain untouched. Continue the missing middle and
900-series states from the original intervals in the same source body.
No origin, accepted unit, comparison infrastructure or byte accounting changes;
no full CI, corpus replay, historical origin retest or per-function test is run.
