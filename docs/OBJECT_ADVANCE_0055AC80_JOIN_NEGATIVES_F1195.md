# F1195 — 0055AC80 initializer-join controls remain nonexact

The live F1194 complete `0055AC80` source remains the selected parent.
Three bounded complete-parent compilations do not reduce its **726 GPR
instruction positions /six width differences**. No source variant is adopted
and no accepted original bytes are added.

## The exact first-divergence boundary

Native state **389** begins at **0055F631**, whole instruction ordinal
**5,166**. Its first **59** instructions already agree in GPR roles,
mnemonics, widths, stack operands, scalar values and resolved PE targets.
These include the owner-health gate, owner-action position attachment,
stage/frame-zero tests, transform reset, collision word, scales, four color
channels and both motion-zero stores.

The first GPR divergence is **0055F711**, whole ordinal **5,225**, at the
join after initialization. Original `MOV ECX,[EBP-24h]` becomes source
`MOV EAX,[EBP-24h]`, followed by native EDX versus source ECX for the
stage-1 signed-short comparison. A matching state entry does not prove its
later register assignments.

The historical `.analysis/object-action-55ac80/04-*` through `24-*`
experiments were inspected before building new controls. They already cover
scale/color chaining, comma grouping, short constants, nested guards and
several lvalue/condition spellings. Their former patched diagnostic byte
counts are historical research, not exact credit or current native proof.

| New complete-parent control | Original-backed result | Decision |
| --- | --- | --- |
| Chained motion-zero assignment, preserving +50 then +54 write order | All 28,868 CODE+DATA bytes and all 696 COFF records identical to F1194 | No improvement; not adopted |
| Explicit DWORD-zero views for the two motion resets | All 28,868 CODE+DATA bytes and all 696 COFF records identical to F1194 | No improvement; not adopted |
| Actual conditional breaks around initialization in a one-pass block | 28,440 CODE bytes /7,657 x86, versus selected 28,438 /7,653 and native 28,432 /7,653 | Rejected at whole instruction-count precondition |

The two identical candidates retain all **2,511** native EBP operand
positions, **859** direct branch destinations, **638** CODE field destinations,
**58** dense target ordinals and **430B** owned DATA. Their mnemonic,
non-GPR, stack, branch, field and sparse-DATA debt remains zero; their
726 GPR /six-width debt remains real. Do not use zipped ordinal differences
from the count-mismatched third candidate as meaningful whole GPR/CFG counts.

## Two pending leaves remain unknown

The original `00454C00` clears DWORD `this+47C`; `00454F70` tests bit 5
of the DWORD reached through `this+74`, then `+3C`. These are substantive
field observations but do not independently identify their original owner.
They are already held as unknown in R233's
[`scene-shared-value-origin-evidence.json`](../config/scene-shared-value-origin-evidence.json).

Read-only Ghidra queries find no recognized incoming references for either
target and no recognized direct callers for `00454F70`. The canonical
accepted-unit relocation map contains no direct calls to either; a fresh
whole-file literal-pointer search also finds none. This does not rule out
computed, runtime, unmodeled or unregistered references. There is no new
same-owner witness sufficient to supersede R233. Both classifications remain
**unknown**, and neither candidate is recompiled merely to repeat the older
source-shape work. The 95 unknown origins remain uncredited.

## Evidence and validation scope

New whole C++, OBJ/PDB, compiler logs, full native audit arrays, the exact
boundary disassembly, read-only Ghidra output and a SHA256-indexed summary
are retained under `.analysis/f1195-0055ac80-first-phase/`. No source bytes,
canonical manifests, origin evidence or comparison infrastructure change.
Do not repeat these controls as fresh leads; continue with a distinct
source/compiler-context explanation or other unfinished whole functions.

The session preflight passed target identity, tracking, current byte summary,
active handoff and headless Ghidra check. Documentation changes pass whitespace
checking. No full CI, corpus cold replay or historical origin-test rerun is
required. The goal remains incomplete at **982 whole exact functions /
871,649 original CODE bytes**, with all 22 authored giants pending.
