# F1207 — recover the complete 34KB 005EB520 research parent

The complete F061 `active07` source is now tracked as
[`CharacterObjectWhole005EB520F1207.cpp`](../probes/CharacterObjectWhole005EB520F1207.cpp)
with its [borrowed receiver interfaces](../probes/ObjectAdvance5EB520F1207.hpp).
It contains all 60 real nondefault states and the actual default, entry guards,
effects and exits. This recovers existing natural C++ research; it does not
claim newly reconstructed behavior or exact acceptance. Independently attributed
R048-authored `005EB520` remains NONEXACT, with **135 GPR positions /six widths**
in its final state 998. All 34,434 original CODE bytes remain pending.

## Original extent and fresh complete build

The pinned user-supplied Japanese target has SHA256
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
Its complete CODE is `005EB520..005F3BA1`, followed by 443 owned DATA bytes
through `005F3D5C`; exclude only the three following INT3 alignment bytes.
The CODE hash is
`bebf4c9ef7e78e20248b2845cf57d86095a06420b822cfa9a014c1371e7e1992`;
DATA hash is
`4f1b58de68f4a9b431d55ce03ad71ea3dcc9efcf57756dbdc10e9d3615c1633c`.

A fresh read-only, analysis-disabled Ghidra query independently reports the
34,434-address body. Its database calling convention is still unknown; native
ECX use and RET, plus complete callee evidence, support the borrowed source ABI.
No database writes or target patches are made.

F061's actual inputs, source/header hashes, full diagnostic, physical bindings
and controls were inspected before building. The recovered source SHA256 is
`4b80fb41c02b2f390a6673d79a1a7386f43ddc9193b44d07a5aea3634dd1924d`.
Fresh serial headless VC7.1 builds use its recorded per-unit profile:
`/Od /Ob0 /Gy /GR- /GX- /Zi /I src`. The tracked copy changes only its include
filename and explanatory comments; a separate fresh build preserves the entire
34,879-byte emitted CODE+DATA and every function relocation record of the recovered source.

| Complete property | Original /fresh tracked source |
| --- | --- |
| CODE /x86 count | 34,434B /34,436B; both 9,378 instructions |
| Frame /saved-this | Both 0x210 /EBP-4 |
| EBP operand positions | All 3,170 agree |
| Mnemonics /non-GPR operands | Zero differences |
| Direct jump destinations | All 901 native instruction ordinals agree |
| CODE field bindings | All 745 native instruction/field positions and destinations agree |
| Owned DATA | 443B: 61 dense destinations /199 sparse bytes, all agree |
| Complete physical COFF bindings | 806: 492 calls, 251 readonly constants, two table addresses, 61 destinations |
| GPR /instruction-width differences | **135 /six**, all in state 998 |

The fresh F061 physical binder also checks actual COFF constant payloads,
PE section permissions, zero addends, call order and local destinations.
The new whole audit separately checks every EBP operand and direct/dense target
ordinal, without eliding temporary displacements. The ten callee destinations
retain their complete F061 evidence; eight authored callees now also have
canonical exact sources. No original COFF relocation identity is inferred.

## Final state 998 and retained negative controls

All GPR/width differences start at whole ordinal **9,200**, original
`005F3904`: native `mov eax,[ebp-4]`, source `mov edx,[ebp-4]`, at the genuine
owner-to-current +66 byte copy. Earlier instructions agree in GPR roles,
widths, stack operands and independently bound nonbranch operands. Earlier
forward-branch displacement bytes can still differ because later instructions
are two bytes longer. Neither those earlier instructions nor the other states
are independent exact functions.

| Original CMP | Native register/width | Source register/width |
| --- | --- | --- |
| 005F398D /149 | EAX /5 | EDX /6 |
| 005F39A1 /154 | EAX /5 | EDX /6 |
| 005F3A03 /153 | ECX /6 | EAX /5 |
| 005F3A18 /158 | ECX /6 | EAX /5 |
| 005F3ADE /150 | EAX /5 | EDX /6 |
| 005F3AF2 /158 | EAX /5 | EDX /6 |

The six width differences explain the net +2 CODE bytes. The historical
324 differing physical instruction encodings include moved branch displacements;
they are not 324 GPR mismatches. Fresh whole physical comparison reproduces
that result and fails equality.

Four complete fresh controls all preserve every CODE+DATA byte and physical
binding shape, leaving 135 GPR /six widths: a one-byte borrowed direction view,
ordinary byte subscripting, state 997's integer one-step angle increment, and
its explicit `angle = angle + 1.0f` form. None is adopted. Historical F061
byte-copy signedness/pointer spellings, doubling literals, genuine break/return
forms and float postfix increment were inspected rather than rebuilt.
A float-divisor source was generated but deliberately not compiled because
it replaces the observed integer FIDIV operand; no compiled result is claimed.

## F1206 inventory and 33KB deduplication

The bounded ignored-source inventory exposed this preserved complete parent;
it does not prove that other complete drafts are absent. Its regex/name
heuristics can miss source names, includes and owner declarations.

The fresh 33KB 004EBDA0 comma-expression candidate duplicates F756's already
compiled negative and again leaves 133 GPR /zero width differences. F773 also
contains historical typed stage/color windows related to F1205's experiments;
F1205's fresh builds and whole audits remain valid, but those ideas are not
all novel. A valid F1206 nested stage-4 switch finally compiles where F756's
attempt had failed syntax: it emits 33,305 CODE bytes /8,791 instructions and
the wrong 0x200 frame, so it is rejected on shape. No ordinal-zipped GPR
comparison is claimed for that different instruction count. The current
F572–F596 complete 33KB source remains unchanged.

## Preserved evidence and next work

`.analysis/f1207-object-5eb520-recovery/` retains the original source/header,
fresh `before.obj`, selected `tracked.obj`, full native disassembly, Ghidra
query/log, four negative sources/objects/logs, all whole-audit JSONs,
`whole-audit.py`, `control-summary.json`, `verified-summary.json` and fresh
F061 physical-binding receipts for both selected builds. Historical
`object-action-5eb520/active07` and all controls remain untouched.
F1206's inventory and 33KB controls remain in their corresponding local folders.

Continue from this complete tracked source at the 997/998 register boundary;
do not restart a marker skeleton or repeat the recorded negatives without
new native/compiler evidence. Preserve all other live complete giant parents.
No accepted inputs, manifests, ownership decisions or comparison infrastructure
change. There is no exact acceptance or canonical replay to claim; no full CI,
corpus replay, origin retest or new per-function test is run.
