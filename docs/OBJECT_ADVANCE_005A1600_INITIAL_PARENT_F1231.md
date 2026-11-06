# F1231 — initial native-backed source for 005A1600

The new research parent writes **17 of 76** real nondefault states in
`probes/CharacterObjectActions005A1600F1231.cpp`, using the borrowed interfaces
in `probes/ObjectAdvance5A1600F1231.hpp`. It is incomplete and NONEXACT.
**All 43,599 original CODE bytes remain pending.** No interior is accepted as
an independent callable and no unknown origin is promoted.

## Original extent and receiver evidence

The pinned Japanese user-supplied TH075 1.11 PE has SHA256
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
The complete native `005A1600..005AC04E` contains **43,599 CODE bytes /
11,620 instructions**, SHA256
`96af78af15b596aec46bdf6d172710819f1fd23f25ed7f92e5de8935ba7917eb`.
It has frame **0x21C**, saved receiver **EBP-0x1C**, one compressed switch,
and a common epilogue at **005AC04B**. Its separate **508 after-RET DATA
bytes** comprise 77 DWORD targets and 200 sparse bytes, SHA256
`fde7202276267259780bb5382f1c3e597428c4643774a391fabf2a30fb98f29f`.
Five following alignment INT3 bytes are excluded. The local native evidence
rereads both tables and the combined DATA hash from the pinned PE.

R048 already attributes this complete callable to authored CharacterObject
behavior. The separately accepted F422 constructor `005A1560` has native SHA
`5128c158851d1708d2f573c2b6d8f7e46ae392ec3a0aee8ee540e321243f0cc1`.
It stores owner E4h and installs vtable **00659DDC**. Fresh PE reads find its
first five slots at **0045B880, 005A1600, 0040FC70, 00410350, 00410A00**.
The source therefore uses virtual slot 1 and truthful borrowed helper ABIs;
it never instantiates or embeds an incomplete receiver view.

## Written behavior and diagnostic limits

The written states are **800–810, 988, 989, 995, 996, 997 and 999**. Their
complete native intervals total **7,687 CODE bytes /2,023 instructions**.
The original guards and default are also present. The selected fresh source
emits **7,813 CODE bytes /2,070 instructions**, frame **0x60**, receiver
**EBP-0xC**. Its sparse map is 200 bytes, but only 18 owned dense entries are
emitted because **59 real states remain unwritten**. This is not the full
native switch or frame and cannot be used as a replacement.

All written intervals agree in mnemonic sequence, local branch target
ordinals and operand shapes after explicit GPR/negative-EBP normalization.
Actual COFF constant payloads are checked independently of symbol spelling.
Raw differences remain: **50 GPR positions, 21 widths and 657 EBP operands**
across the partial diagnostic. The first eleven states 800–810 have zero raw
GPR/width debt, but their stack positions and the enclosing function remain
nonexact. Normalized agreement is discovery evidence only.

800 and 806 preserve the original three-iteration reward loops, with separate
real indices at native EBP-4 and EBP-8. Four further real native loop indices
are still in unwritten states; no unused locals or padding are added to force
the saved-this slot. 800 retains its hit-qualified reset and zero velocities
before returning. 804's native TEST AH,41h/JP establishes the effect gate
**scale <= 1.0f**, correcting the initial opposite predicate. 806 keeps its
frame-versus-CC comparison, positive Y motion, distinct phase-1/phase-2 owner
updates, counter clamp and early hit return. 808/809 retain the native QWORD
1.5 comparison and distinct repeat limits. 997 uses actual Y=2 and reset9;
999 preserves F0C lifetime and the actual **35.0f** rotation decrement.

## Retained evidence and continuation

`.analysis/f1231-object-5a1600-recovery/` retains all native disassemblies,
read-only analysis-disabled Ghidra hypothesis/log, original owner inputs,
selected constant/callee evidence, family homology, immutable initial/reviewed
CPP/HPP/OBJ/listings/build logs, source diagnostics and `verified-summary.json`.
Selected CPP SHA256:
`70036d899a0bf26a577eb41dd59291e9c033e2b8656306acb5ed19cb83ac0eda`;
OBJ SHA256:
`f36f83c21c094287f3e95561162a4eb4598ef6f472b34abc5d121ca3dc46db12`.
Profile: `/Od /Ob0 /Gy /GR- /GX- /GS /Zi /I src /I probes`.

Continue at native state811 and the remaining real states, keeping one source
body. Do not restart the historical F569 marker source. Only a complete
zero-difference canonical affected-unit cold replay may earn exact credit.
The session ran target/tracking/status/handoff checks, read-only Ghidra and
two serial affected-parent builds. No accepted source, ledger, origin evidence
or canonical infrastructure changed; no full CI, corpus replay or new tests.
