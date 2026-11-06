# F1184 — Reimu seven early recovery states and the original 61 exit scope

**Historical F1184 checkpoint:** F1185 extends this same source to
24,967B/6,844 x86 and 63 nondefault markers, and clears the later eleven
12C–136 GPR differences. See [the current native command-state proof](REIMU_COMMAND_STATES_F1185.md).
The dimensions below describe commit `bac6c2a0`. A direct F1185 recount
corrects the former 73-nondefault claim: that count included default;
the F1184 checkpoint had 72 nondefault markers and one default store.

The live `probes/FighterWhole0045DD70F1183.cpp` now includes
`ReimuEarlyRecoveryStatesF1184.inc` in place of seven earlier markers.
The independently R063-authored original remains **NONEXACT**. This
extends the [eleven F1183 falling states](REIMU_FALLING_STATES_F1183.md)
in the same whole source, not separate case functions or exact units.

| State | Original complete interior CODE | Native x86 | Actual external fields | Remaining GPR positions |
| --- | ---: | ---: | ---: | ---: |
| `59` | 359 | 95 | 16 | 19 |
| `5D` | 337 | 101 | 8 | 61 |
| `5E` | 337 | 101 | 8 | 61 |
| `5F` | 144 | 44 | 3 | **0** |
| `61` | 586 | 169 | 11 | **0** |
| `62` | 249 | 65 | 4 | 40 |
| `63` | 533 | 138 | 8 | 88 |
| **New early source** | **2,545** | **713** | **58** | **269** |

All 713 native mnemonic positions, actual non-GPR arithmetic/memory
operands, physical external destinations and every direct branch target
are checked from one freshly built complete parent. All widths agree
except the three EAX-dependent CMP widths in 63: source 534B versus
original 533B. States 5F and 61 match all native GPR roles and widths,
but their stack slots are still wrong and they receive **no exact credit**.

## Actual Reimu policies and the corrected completion path

State 59 retains stage 3, the two genuine float-to-short contact captures,
rotation reset, auxiliary state 3 and native transform arguments
**-7.0f /75.0f /0.0f**. A float parameter view transports those exact
literal representations; using the other actor's 0/95 policy is incorrect.

The shared F617 air-transition body is instantiated for both 5D/5E with
Reimu's stage 3, threshold 11, vertical speed 4.5, horizontal speed
+12.5/-12.5, friction 0.35 and finishing auxiliary state 7. Each preserves
two independent opponent-X direction comparisons. The existing F620,
F622 and F627 bodies are retained with independently checked Reimu values:
5F transitions 0/1, 62's unsigned four-field collision OR and +0xF00
counter, and 63's genuine priority bonus 0x303 before ordinary 0x31C.

State 61 includes the actual ten-effect 0x3E4 loop and threshold-limited
0x3E3 effect, direction-dependent collision capture, strict landing
comparison, and the two distinct 0x3CF-dependent next actions.

The initial candidate had every native instruction mnemonic/GPR/width
but one **wrong branch destination**: source ordinal 131 reached the
stage-4 update at 157, whereas original **00460409** jumps to the final
case exit at **00460487**, ordinal 168. Both stage-3 rebound restoration
and stage-4 auxiliary transition therefore belong to the **else** of
animation completion. An explicit break instead of the original scope
also fails: it jumps directly to the far function return and changes
instruction width. The adopted ordinary C++ else block restores the
actual local jump target and complete native control flow.

This is why a matching mnemonic/GPR stream alone is insufficient. The
native-derived handler/instruction target check was required to find it.
A separate postfix-versus-prefix loop-increment control reproduces every
candidate CODE+DATA byte and physical field shape; it is retained locally
as a negative, without replacing the actual source or inventing a register seed.

## Current complete parent and what is still missing

The same parent now emits **21,723 CODE bytes /5,881 x86**, plus the
original-shaped **1,090-byte post-RET DATA**. Its source frame is **0x38**
and saved-this is **EBP-0xC**, versus original **0x380 /EBP-0x34**.
Both real loop counters are used; no inert local or frame filler was added.

Across F1183 and F1184, **18 newly sourced native interiors** span
**6,074 original CODE bytes /1,714 x86 /149 actual external fields**.
Their branch targets and non-GPR operand grammar all agree; F1183's
same 623 GPR differences remain in the later eleven states. The 142
live dense-label identities and 522 sparse DATA bytes are rechecked in
the latest object. These totals are **interior reconstruction evidence,
not original whole-function accepted bytes**.

There are still **72 nondefault marker statements**, the default marker,
and missing original common-tail behavior. The earliest remaining source
group is **C8–D0**, followed by 186 and later attack states. Continue this
tracked parent rather than regenerating an older F652 partial selection.
All original 60,999 pending bytes remain in the conservative denominator.

Use the same headless serial build command in the F1183 proof, writing
to `.analysis/f1184-reimu-early-recovery/native-scope.obj`. Native interval
receipts, the before object, initial/wrong-scope/corrected objects, actual
CFG/field comparison and final summary are retained locally under ignored
`.analysis/f1184-reimu-early-recovery/`. The local F1183 `compare.py` can
read this object with action arguments `59 5d 5e 5f 61 62 63` followed by
`12c 12d 12e 12f 130 131 132 133 134 135 136`; it diagnoses the complete
parent and the full physical native intervals, and never accepts a unit.

Canonical coverage is unchanged at **982 whole exact functions /871,649
CODE bytes**, 44.16% reviewed and 44.09% conservative. No accepted source,
match manifest, origin evidence or comparison infrastructure changed. Only
this affected research parent was compiled; no full CI or corpus replay.
