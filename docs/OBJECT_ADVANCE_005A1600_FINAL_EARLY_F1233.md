# F1233 — all early states of 005A1600 written

The live research source `probes/CharacterObjectActions005A1600F1231.cpp`
now writes **50/76** real nondefault states. This extends
[F1232](OBJECT_ADVANCE_005A1600_MIDDLE_STATES_F1232.md) with **827–844**:
**7,334 native CODE bytes /1,982 instructions**, in complete native case
intervals. The only unwritten states are **900–925**. No interior is an
accepted callable; all **43,599 original CODE bytes** remain pending.

Two serial headless VC7.1 builds use the existing
`/Od /Ob0 /Gy /GR- /GX- /GS /Zi /I src /I probes` profile. The selected
`charged.obj` emits **26,741 CODE bytes /7,200 instructions**, frame
**0x108**, saved receiver **EBP-0x14**, 51 dense entries, 200 sparse bytes
and 554 COFF records. Written native case intervals total **26,564B /
7,153 instructions**; the prefix and actual default are also present.
The full native frame is still **0x21C**, saved receiver **EBP-0x1C**,
with 77 dense entries and 508 after-RET DATA bytes. This remains incomplete.

## Verified source behavior

827 preserves owner-facing offset 8, Y+135, rotation 15 and its three separate
parent-action/phase reset predicates. 828 preserves phase-before-action
ordering. 829 retains the owner-action cancellation, raw X attachment and
the genuine **QWORD 0.25** addition; its other growth uses **DWORD 0.25f**.
830 keeps the clamp/reset return and phase 3 fade. 831/832 preserve their
different horizontal/vertical motion and growth/shrink order.

833 preserves the F30-to-D8 transfer, QWORD 1.5 clamp, phase/frame-qualified
three random calls, owner314/318/31C writes and final reset to 3. 834/836 retain
their different initial counters, reset to 10 at phase 21, independent subsequent
phase > 9 shot guard, actual **NEG then SUB 75**, and the X expression kept live
across the random call. Their effect IDs remain 835/837 respectively.

835 adds the native floor test after its conditional polar update, with zero
velocities before reset to 2 and immediate return. Its later hit reset has reset to 2
before the zero stores. 837 retains fixed -90-degree initialization, the
unconditional phase 0 reset, distinct phase 1 owner writes and phase 2 D0/D8
updates. Their three-iteration reward loops introduce the third and fourth
real user indices at native EBP-0xC/-0x10. 838–843 keep separate effect states
and their observed growth/fade policies; owner-facing attachment is retained
where present. 844 preserves its distinct parent 303 attachment.

## Remaining partial-parent differences

Every written mnemonic sequence, local branch target ordinal and normalized
operand shape agrees. Actual COFF literal payloads are independently reread.
**All 50 written states now have zero raw GPR differences.** Their four
remaining width differences are two MOV/FILD pairs: native EBP-0x84 versus
source-0x7C in 819, and native-0x88 versus source-0x80 in 820. These positions
are eight bytes above the original slots, following recovery of two real
loops. Two further real indices remain in unwritten states; no padding or
unused locals are added. **2,343 raw EBP positions still differ** in the
partial source. Whole-function byte equality is not established.

`.analysis/f1233-object-5a1600-final-early/` retains immutable before,
outer-effects and charged CPP/HPP/OBJ/listings/build logs, selected native
spans/constants/callees, both source diagnostics, actual width differences
and `verified-summary.json`. Selected CPP SHA256:
`e8f738a58a5b2242a88a1880b5c0e50f965b36822c7431c810aee81c168d8ee4`;
OBJ SHA256:
`fc27f5479f5a821a9bb830fade6c432d09cb71093d6be79eb62024b1d25936cc`.
F1231 retains complete original CODE/DATA and constructor/vtable evidence.

Continue at 900, then recover all 26 remaining states before investigating
whole-parent differences. Target/tracking/status/handoff checks, read-only
Ghidra, two affected-parent builds and whitespace checks were run. No accepted
input, header, ledger, origin or canonical infrastructure changed. No full CI,
corpus replay, origin retest, new tests or new exact credit.
