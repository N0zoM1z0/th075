# F1234 — native-backed states 900–916 in 005A1600

The live source `probes/CharacterObjectActions005A1600F1231.cpp` now writes
**67/76** real nondefault states. This extends
[F1233](OBJECT_ADVANCE_005A1600_FINAL_EARLY_F1233.md) with **900–916**:
**8,847 native CODE bytes /2,393 instructions**, in complete native case
intervals. **917–925 remain unwritten. All 43,599 original CODE bytes remain
pending.** No interior is accepted as a callable and no origin changes.

## Native behavior retained

900/904 preserve the owner-health gate, separate phase 2/3 polar updates,
phase 4/5 stops, hit reset to 3, difficulty-limited repeat and two independent
phase 5/frame-zero guards. Difficulty is read as the observed signed byte at
006714D0. 904 keeps its distinct initial DA45 and does not add a DC reset
absent from its initializer. Its actual angle/divisor result is stored before
the random call, then added to the integer random result and reduced by 15.0f
before short conversion; the Ghidra hypothesis omits these x87 operations.

901/902 preserve the different placement of polar updates, health and hit
guards, movement-before-bounds order and distinct shrink/fade policy. 903/913
retain **QWORD 0.95**, not float 0.95f. 905/906 retain their parent741 attachment,
opposite rotations, scale cap and raw DWORD angle transport. 909 preserves
both native fade opportunities; they are not merged into one update.

907/910 retain bounds before movement, repeated native collision-field
writes and their original returns. 908 restores the fifth genuine user loop
index at native EBP-0x14. Its two **independent** DC tests can emit 907 and 910
within one iteration, with both native toggles. The loop uses the signed
difficulty limit and actual indexed coordinate expressions. No user local is
introduced for the compiler's floating temporaries.

900/904 must return after the successful animation-reset packet. 907/908/910
must return after frame exhaustion clears the object: the original has a
direct epilogue jump followed by the ordinary case-exit jump. Initial source
joins had the wrong destination or omitted that second jump. The selected
source reproduces the actual native exits without cropping comparison spans.

911 preserves the surprising parent-action 500 clause, floating facing*8.0f
velocity versus integer facing*8 attachment, floor handling and separate
phase bounds. 912 keeps its distinct parent733 guard and no invented health
gate. 914 preserves difficulty-selected 915/916 emission after clear/sound23.
915/916 keep camera shake before transform initialization and the actual
4/2 scales, DWORD 0.5f growth and QWORD 0.95 decay.

## Selected partial build and remaining debt

Three serial headless VC7.1 builds use the unchanged explicit profile
`/Od /Ob0 /Gy /GR- /GX- /GS /Zi /I src /I probes`. The selected `reviewed.obj`
emits **35,595 CODE bytes /9,593 instructions**, frame **0x178**, saved receiver
**EBP-0x18**, 68 dense entries/200 sparse bytes and 787 COFF records. Written
native case intervals total **35,411B /9,546 instructions**; the prefix and
actual default are present. Full native frame 0x21C/receiver-0x1C and all 77
dense entries remain required.

All written mnemonic sequences, local branch target ordinals and normalized
operand shapes agree; actual COFF constant payloads are independently read.
**Raw differences remain: 1,101 GPR positions, 19 widths and 3,125 EBP operands.**
The first GPR difference is native **005A88A8**, state909 ordinal0: native ECX,
source EAX. Its cause is not established. Earlier written states retain zero
raw GPR debt. Finish the remaining nine states and last real loop index before
investigating whole-parent differences; do not pad the receiver slot or infer
that partial normalized agreement proves exactness.

`.analysis/f1234-object-5a1600-late/` retains immutable before, launch, spray
and reviewed CPP/HPP/OBJ/listings/build logs, selected native spans/constants/
callees, all source diagnostics, actual width/GPR debt and `verified-summary.json`.
Selected CPP SHA256:
`03bbcc411d32bb0bc3c4ea3c167a18508be54508269a532a5e4e4deb20fa4406`;
OBJ SHA256:
`f36b74f8ef761155a95db35b3a7c147bc39b5999f20084ff58937e51609accd0`.
F1231 retains the original whole CODE/DATA/constructor/vtable evidence.

Target/tracking/status/handoff checks, read-only Ghidra, affected-parent
builds and whitespace checks were run. No accepted input, header, origin,
ledger or canonical infrastructure changed. No full CI, corpus replay,
origin retest, new tests or exact credit.
