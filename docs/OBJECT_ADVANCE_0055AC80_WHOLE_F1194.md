# F1194 — Continue the complete 0055AC80 source and verify its whole native CFG

The independently authored original `0055AC80` now has a tracked complete
ordinary C++ research parent,
[`CharacterObjectWhole0055AC80F1194.cpp`](../probes/CharacterObjectWhole0055AC80F1194.cpp).
It continues the preserved **complete F167 source**, rather than restarting
the old F569 marker skeleton. All **57 real state entries**, default and the
shared epilogue are present. This recovers existing unfinished work into the
live cohort; it does not claim that these bodies were newly written in F1194.
The complete original **remains NONEXACT**.

## Fresh whole-parent evidence

| Original whole-function property | Pinned Japanese PE | Fresh tracked C++ build |
| --- | ---: | ---: |
| Complete callable CODE | 28,432B | **28,438B (+6)** |
| Ordered x86 instructions | 7,653 | **7,653** |
| Frame allocation | 0x19C | **0x19C** |
| Saved-this | EBP-0x24 | **EBP-0x24** |
| EBP operand positions | 2,511 | **all agree** |
| Ordered mnemonics and non-GPR operands | 7,653 | **all agree** |
| Direct branch destinations by native instruction ordinal | 859 | **859/859** |
| CODE reference destinations at native instruction/field positions | 638 | **638/638** |
| Dense jump-table entry destination ordinals | 58 | **58/58** |
| Owned after-RET DATA | 430B | **430B**, including 198 exact sparse bytes |
| Genuine GPR instruction-position debt | — | **726** |
| Instruction-width debt | — | **6** |
| Complete original cold-exact acceptance | — | **NO** |

The whole audit independently rereads the pinned original CODE and DATA,
checks their fingerprint hashes, and resolves all **696** source COFF fields
(638 CODE plus 58 DATA), with zero unknown references. Existing canonical
helper targets resolve the real method calls. Compiler constant-pool symbols
use historical addresses only as leads: both their native constant bits and
each actual native field destination are checked again. Local table references
are checked against the owned native DATA and all dense entry instruction
ordinals. None of these checks grants original absolute relocation-offset
equality while instruction widths differ.

The F167 source SHA256 is
`71f8869774a078f028a3c6fe58b1ef1d0faaa74137053346c455f2a3ebdfd926`.
The continued research build and the final tracked build have identical
complete CODE+DATA and COFF records. Source changes are a provisional class/
header rename and updated status comments; the state bodies are preserved.
The call-only virtual prefix is independently reread at native `00659B34`:
slots 0/1 are `0045B880` and `0055AC80`. The new header is never instantiated
or embedded and does not establish a complete private object layout.

## Exact debt is localized, not resolved

| Native state | Wrong GPR instruction positions |
| --- | ---: |
| 389 /38A /38B /38C /38D | 78 /68 /119 /90 /56 |
| 38E /38F /390 /391 /392 | 60 /84 /88 /71 /12 |

The first difference is native **0055F711**, whole ordinal **5,225**.
All six wrong widths are accumulator-specific CMP encodings, native EAX
versus source EDX, at **0055FAA4, 0055FAB8, 0055FB02, 0055FB16,
00560027 and 0056016E**. Each is one byte longer in the source, accounting
for the entire six-byte CODE excess. Stack, branch and non-GPR operand debt
are zero; register differences remain real unaccepted machine instructions.
The historical 728 normalized ordinal differences also included two shifted
table-address operands; that is not a count of genuine GPR differences.

The selected object, full difference arrays, constant/call field witnesses,
source-origin receipt and transitive source/artifact SHA256 inventory are
retained in `.analysis/f1194-remilia-whole-recovery/`. Its local `audit.py`
accepts an explicitly selected fresh whole object. It is a bounded research
diagnostic, not a new canonical comparison gate or per-function test suite.

## Bounded 81KB guard control and validation scope

A separate whole 81KB parent changes only the first conjunction guards in
358/3E6 to nested real `if` statements. It preserves all **82,109** previous
CODE+DATA bytes and all **1,449** field shapes, leaving **522 GPR /five widths**.
It is not adopted. The source, compiler output, disassembly and byte/field
identity receipt remain in `.analysis/f1194-native-guard-topology/`; do not
repeat this canonicalized guard spelling as a new lead.

Only these research parents were serially built. Target/tracking, active
handoff and whitespace checks pass. Accepted units, sources, provenance and
comparison infrastructure are untouched. No full CI or corpus cold replay
ran. Canonical coverage stays **982 complete exact functions /871,649 CODE
bytes**; all 22 authored giants, including this entire original 28,432B
callable, remain pending in the conservative denominator.
