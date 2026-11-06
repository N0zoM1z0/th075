# F1236 — 005A1600 register boundary controls

The complete [F1235 parent](OBJECT_ADVANCE_005A1600_COMPLETE_PARENT_F1235.md)
remains NONEXACT. Five new serial, headless VC7.1 builds examine the real
908 loop and the beginning of 909. No accepted input or canonical manifest
changes. All 43,599 original CODE bytes remain pending.

## Complete-parent observations

Every trial retains 43,596 CODE bytes /11,620 instructions, the native 0x21C
frame and EBP-0x1C receiver, all 1,196 direct target ordinals, all 866 CODE
reference destinations and all 77 dense targets /200 sparse bytes. All retain
613 wrong GPR instruction positions and 11 wrong widths. No cropped state,
register-normalized comparison or destination-only result earns exact credit.

| Trial | Observed difference from the F1235 complete parent | Decision |
| --- | --- | --- |
| Move all six used loop-index declarations to function scope, in lexical order | 20 wrong EBP operands; native 835/837 index slots are exchanged | Reject; restore original scopes |
| Replace the final 908 switch break with a genuine function return | Identical entire CODE/DATA and all 943 COFF records | Reject as a register fix |
| Split 909's initial conjunction into nested conditions | Identical entire CODE/DATA; local label names change, destinations do not | Reject as a register fix |
| Express 909's two real float copies as float assignments | Identical entire CODE/DATA and all 943 COFF records | Retain the clearer source; no exact gain |
| Name each of the six separately scoped real loop indices `i` | Identical entire CODE/DATA and all 943 COFF records | Reject as a register fix; preserve existing names |

No dummy local, padding, assembly, ABI change or alternate source body is used.
The selected tracked source differs from F1235 only in the two float copies:
owner X into self X, and the C8 angle into rotation30. Header bytes are unchanged.
The selected full source diagnostic independently checks the actual COFF
constant payloads; its complete whole audit has zero mnemonic, non-GPR operand,
EBP, branch, native-field destination or owned-table debt. Physical relocation
offset equality is still unproved because instruction widths differ.

## Uniform register-cycle observation

Across every one of the 613 wrong instruction positions, **all 790 differing
register operands** follow the same source-to-native cycle:
EAX to ECX, ECX to EDX, EDX to EAX, including their observed subregisters.
436 instructions have one such operand; 177 have two. No other differing
register pair occurs. This is an observation of raw operands, not a renaming
used to pass acceptance.

The first remains native 005A88A8 /whole ordinal 7,965, at 909's first load.
The last remains 005A95C7 /whole 8,879, in 917 initialization before its first
RecordedRange call. This supports investigating a persistent compiler register
phase, but does not establish its frontend/backend cause or callable equality.
The scope, index-update, exit, condition-grouping, float-copy and index-name
controls now have retained negative evidence; do not repeat them as new work.

## Retained inputs and validation

`.analysis/f1236-object-5a1600-loop-scope/` retains immutable before/trial
CPP/HPP, all five OBJ/PDB/listings/build logs, complete whole-audit JSON/logs,
selected source diagnostic, `verified-summary.json` and
`register-cycle-observation.json`. The F1235 original selected object and every
earlier native/owner/source receipt remain preserved.

Current selected `float-copy909.cpp` SHA256:
`3104e9e408ca2d30c0fbf04493fd07e816ad3e54e5f4db04766d3d8888daf739`.
Selected `float-copy909.obj` SHA256:
`89504265e4e4fca6ad1c9dcf1eb37488ba55a5e0c5d0f1802d068998c6056989`.
Profile remains `/Od /Ob0 /Gy /GR- /GX- /GS /Zi /I src /I probes`.
Private `whole-audit.py [OBJ]` remains diagnostic only.

Pinned target/tracking/status/handoff checks, read-only/no-analysis Ghidra
attestation and whitespace checks pass. Only this complete research parent was
compiled. No full CI, accepted-unit cold replay, origin retest or new test was
needed or run. A complete zero-difference candidate still requires canonical
affected-unit cold replay before acceptance.
