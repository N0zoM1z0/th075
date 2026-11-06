# F1186 — Reimu seven original scripted attacks, 186–192

The live one-body `probes/FighterWhole0045DD70F1183.cpp` now includes
`ReimuScriptedAttacksF1186.inc` and its two five-shot source fragments.
Seven more markers are replaced by actual Reimu behavior. The complete
R063-authored original **0045DD70 remains NONEXACT**; these interiors
are not separate exact functions.

| State | Native complete interior CODE | Native x86 | Actual external fields | Wrong GPR positions | Wrong widths |
| --- | ---: | ---: | ---: | ---: | ---: |
| 186 | 295 | 84 | 9 | 51 | 0 |
| 187 | 444 | 122 | 10 | 79 | 0 |
| 188 | 378 | 114 | 9 | 72 | 0 |
| 189 | 407 | 114 | 8 | 76 | 0 |
| 190 | 1,184 | 318 | 28 | 186 | 8 |
| 191 | 1,220 | 318 | 28 | 186 | 12 |
| 192 | 287 | 80 | 9 | 45 | 0 |
| **New source** | **4,215** | **1,150** | **101** | **695** | **20** |

The native intervals are contiguous **00463B59..00464BCF**, including
all original exits. One freshly compiled complete parent verifies all
1,150 instruction mnemonics, non-GPR operand grammar, physical external
field destinations and every actual native handler-relative direct jump
target. All 20 width differences in 190/191 are actual MOV/FILD EBP
scratch operands crossing the short-displacement boundary; none is hidden
by cropping. Their generated CODE sizes are 1,160 and 1,184 bytes.
Native stack slots and GPR debt remain explicit.

## Native gameplay recovered

186 initializes the native phase flags without the other fighter's initial
speed assignment. Positive +0x3AC enables one drag path, while stage>3
and positive speed enable another; stage 4 sets speed 15 and preparation
0x1D. These distinct gates and constants come from original PE operands.

187 clears its repeat counter, applies stage<5 ground drag, initializes
speed 9 and zero vertical motion, then takes the original auxiliary-11
landing exit. Stage 5 starts speed 10, vertical 12.5, acceleration 0.85
and preparation 0x1C. 189 separately preserves stage-0 and stage-2 speed
12 policies, stage>4 ground drag, preparation 0x1D, and one auxiliary-3
repeat. Their native ground-equality sequences load the global before
the field. A plain field expression restores that order; the initially
borrowed equality reverses two FLD operands and is retained as rejected
evidence. This is independently checked, rather than assuming every x87
expression needs the same source spelling.

188 retains its separate stage-zero flag writes, stage>0 drag, action-2
completion, and four independent preparation-0x1B events at stages
3/5/7/9. The frame-zero/stage<12 reset is distinct from those events.

190 and 191 each contain **two actual five-shot sequences**, not a
source loop. Every shot writes the real +0x314 angle and +0x318 speed,
then reevaluates signed-facing X and Y arguments before calling 00453A70.
The first sequence is stage 8; the second requires stage 10, frame zero,
repeat<2 and an **unsigned** positive +0x4F0 value. It increments the
real repeat counter and returns to auxiliary stage 8. The sound helper's
short argument is corroborated by its accepted original source.

190 angles are -20/-10/0/10/20, X offset 114, Y offset **96** at
006590A0. 191 angles are 60/50/40/30/20, X offset 90, Y offset
**158** at 0065909C. Both Y values are read directly from the pinned PE.
The per-shot integer-to-float temporaries are genuine expression values;
no inert local or fabricated stack filler was introduced. 192 emits
0x338 at native zero-added coordinates, sound 4 and animation 250,
then repeats auxiliary stage 4 fewer than twice.

## Complete parent and preserved previous evidence

The parent now emits **29,020 CODE bytes /7,980 x86**, plus **1,090
DATA bytes**. The original is still **60,999 /16,837**. Source frame
**0x90 /saved-this EBP-0xC** remains wrong versus **0x380 /EBP-0x34**.
All 142 live zero-addend dense-label identities and 522 sparse DATA bytes
are rechecked. There are **56 nondefault markers**, one default marker
and missing native common-tail behavior. The next missing state is 194.

A separate before/after review preserves **all 80 previously nonmarker
physical handler intervals**: full instruction counts, mnemonic/GPR/width
results, non-GPR operands, actual branch targets, external fields and EBP
debt cohorts are unchanged. This checks preservation of earlier research;
it does not assert that those older handlers were exact.

F1183–F1186 together restore 34 formerly missing interiors, spanning
**13,668 original CODE bytes /3,845 x86 /340 fields**. Every mnemonic,
non-GPR operand, branch target and field destination in that cohort
agrees; **964 GPR positions, 23 widths and stack debt remain**. The
20 C8–D0/12C–136 states retain their full GPR/width agreement, as do 5F/61.
These are interior evidence and add **zero whole exact credit**.

Build only this affected source with the F1183 headless serial command,
writing `.analysis/f1186-reimu-scripted-attacks/native-equality.obj`.
Before/recovered/final objects, rejected equality source, original interval
listings, physical field/CFG comparisons, prior-handler preservation and
hashed summary remain in that ignored directory. The local F1183 comparison
script accepts the seven new action arguments and then the earlier 27;
it remains a research diagnostic, not canonical acceptance infrastructure.

Target/tracking and active-handoff checks pass. Canonical exact status
remains **982 whole functions /871,649 CODE bytes**, 44.16% reviewed /
44.09% conservative, with all 22 authored giants still pending. No accepted
source/header, exact manifest, origins or comparison infrastructure changed;
no full CI, corpus replay or extra per-function tests were added.
