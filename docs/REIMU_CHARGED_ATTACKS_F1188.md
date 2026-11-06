# F1188 — Reimu seven original 1F4–1FB charge and leap policies

The live one-body `probes/FighterWhole0045DD70F1183.cpp` replaces seven
more markers with `ReimuChargedAttacksF1188.inc` and its native-policy
fragments. The independently R063-authored original **0045DD70 remains
NONEXACT**: 60,999 CODE bytes /16,837 x86. No switch interior is accepted
as a separate exact function.

| State | Native complete interior CODE | Native x86 | Physical external fields | Wrong GPR positions |
| --- | ---: | ---: | ---: | ---: |
| 1F4 | 698 | 197 | 16 | 136 |
| 1F5 | 729 | 205 | 18 | 141 |
| 1F6 | 698 | 197 | 16 | 136 |
| 1F7 | 710 | 201 | 16 | 139 |
| 1F8 | 729 | 205 | 18 | 141 |
| 1FA | 467 | 136 | 11 | 90 |
| 1FB | 467 | 136 | 11 | 90 |
| **Seven new states** | **4,498** | **1,277** | **106** | **873** |

One fresh serial pinned-VC7.1 complete-parent build verifies every native
interval length, instruction count, mnemonic, instruction width, non-GPR
operand, direct branch destination and physical external field target.
Original intervals are contiguous **00466B76..00467D07**, with all exits
included. GPR roles and stack operands remain wrong, so these complete
interior comparisons add no accepted whole-function exact bytes.

All five 1F4–1F8 policies retain transform (0,100,0), true unit-scale
and four unsigned color-byte writes, 25-step alpha subtraction/addition,
separate shrink/stretch and restore phases, and sound 2. The scale
addition uses a genuine field lvalue borrow to retain original x87 load
order. The stage gates and instruction destinations are independently
checked from Reimu's own original PE, rather than another fighter's policy.

1F4/1F6 share the same native non-GPR flow but remain distinct physical
handlers and source bodies. They warp relative to the opponent X by
signed-facing times 180, enter at Y=150 with speed (6,8), then use (5,-16).
1F7 shifts the phase and landing stages and requires stage>3 for its
per-frame gravity. Their stage-pair landing test is **strictly below
zero**; it clears all three motion values, selects auxiliary 9/10 and
immediately exits the original function.

1F5/1F8 instead move X forward by facing times 100, enter at Y=50 with
speed (12,6), and apply stage-dependent gravity. Their **at-or-below-zero**
landing path clears Y and vertical speed and selects auxiliary 6/7,
then continues the later original state logic. The limited repeat calls
SetAuxAction **before** incrementing +0xF00, as in the native PE.
This distinct scope/order is retained, rather than replacing it with an
unconditional early break.

1FA/1FB retain air drag, complete landing resets, raw-coordinate effect
0x32D and sound 3 at stage 4, then auxiliary effect 0x7F at stage 5.
Their genuine launch velocities differ: **(7.5,8.5)** versus **(9.5,12.5)**,
both with 0.9 gravity. Stage 10 selects auxiliary 8. DWORD coordinate
views retain original MOV/PUSH transfer rather than numeric conversion.
All names/semantic policy labels remain provisional.

The complete source now emits **41,335B/11,379 x86**, with **1,090
post-RET DATA bytes**, all 142 live dense-label identities and every one
of the 522 sparse DATA bytes checked. Frame **0x18C /saved-this EBP-0xC**
still differs from original **0x380 /EBP-0x34**. There remain **37
nondefault markers**, one default marker and missing shared getter-tail
behavior. Next missing source group: **252–263**. The full original
pending bytes remain in the conservative denominator.

A before/after diagnosis preserves **all 99 previously nonmarker physical
intervals**: full counts, mnemonic/GPR/width results, non-GPR operands,
actual branch targets, physical fields and EBP-debt cohorts are unchanged.
F1183–F1188 together restore 53 earlier markers across **26,268 native
interior bytes /7,282 x86 /658 fields**, still with **3,064 GPR positions,
23 widths and stack debt**. These totals describe interior source evidence,
not new whole exact coverage.

Build only the affected source with the headless serial F1183 command,
writing `.analysis/f1188-reimu-charged-attacks/recovered.obj`. Native
intervals, before/fresh objects, original CFG/field diagnosis, preservation
receipt and hashed summary remain in that ignored directory. Target,
tracking, active handoff and `git diff --check` pass. No accepted source,
header, manifest, origin evidence or comparison infrastructure changed;
no full CI, corpus replay or extra per-function tests were added. Canonical
status remains **982 whole exact functions /871,649 CODE bytes**, 44.16%
reviewed /44.09% conservative, with all 22 authored giants pending.
