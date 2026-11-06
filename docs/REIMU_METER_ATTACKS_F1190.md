# F1190 — Reimu eight original 2BC–2C3 meter/effect states

The one-body `probes/FighterWhole0045DD70F1183.cpp` now includes
`ReimuMeterAttacksF1190.inc` and its native-policy fragments. The complete
R063-authored **60,999B/16,837-x86** original remains **NONEXACT**;
no interior is accepted as an independent exact function.

| State | Complete native interior CODE | Native x86 | Physical external fields | Wrong GPR positions |
| --- | ---: | ---: | ---: | ---: |
| 2BC | 815 | 228 | 20 | 133 |
| 2BD | 815 | 228 | 20 | 133 |
| 2BE | 497 | 145 | 15 | 85 |
| 2BF | 497 | 145 | 15 | 85 |
| 2C0 | 432 | 123 | 14 | 68 |
| 2C1 | 415 | 120 | 13 | 68 |
| 2C2 | 955 | 270 | 26 | 154 |
| 2C3 | 955 | 270 | 26 | 154 |
| **Eight new states** | **5,381** | **1,529** | **149** | **880** |

Every native interval length, instruction count, mnemonic, instruction
width, non-GPR operand, actual branch target and physical external field
destination is checked from a fresh whole-parent compilation. The original
intervals are contiguous **0046939C..0046A8A0**, including every exit.
Native GPR roles and EBP operands remain wrong, so this adds zero whole
exact bytes. An initial equal-length/equal-count source had five wrong
mnemonics in each of four burst states: X was loaded before the direction
conversion. The plain original-position lvalue restores **FILD then FSUBR**,
not FLD then FISUB, and all six non-GPR operand differences disappear.
The rejected initial source/object is retained locally.

2BC/2BD/2C2/2C3 retain the true three-way +0xF02 selector and its native
`==1 && <0x43` condition, with float +0x314 derived from signed +0xF00.
Stage 10/frame zero requires repeat<8; +0xF02 cycles through 0/1/2.
Stage 12 increments +0xF00 only while below 13 before auxiliary 10.
2BD uses sound 10; **2C3 still uses sound 6**, as does 2BC/2C2.
Their 0x327/329/32A versus 0x33C/33D/33E effects and 0x73/74 auxiliary
variants remain distinct physical bodies. 2C2/2C3 additionally preserve
stage>11 airborne gravity, an early auxiliary-15 landing/reset return,
and the later stage-15-to-13 transition.

All eight states retain their actual initialization and call ordering,
short SetNonnegativeWord(40), preparation 0x17 and +0x36C resource
subtraction. The accepted helper source corroborates the genuine short
parameter; the seven-argument tracked-effect helper uses its observed
short/float/float/signed-char/signed-char/unsigned-char/unsigned-char ABI.
No incomplete owner is instantiated.

2BE/2BF keep stage 10-or-11 animation 5, raw-Y coordinate transport,
two original zero additions to X, distinct effects/sounds, repeat<10
and secondary repeat<5. 2C0/2C1 preserve two separate stage-zero gates,
actual +128*facing FIADD after X+100, sound 8/9 and repeat limits 9/6.
2C1 genuinely lacks the extra animation-500 call. Native Y constants are
200 (0065835C), 226 (00659088), 144 (00659084) and 93 (00659080).
These are original observations; semantic names remain provisional.

The complete partial source emits **52,151B/14,446 x86**, plus **1,090
post-RET DATA bytes**. All 142 live dense-label identities and 522 sparse
DATA bytes are rechecked. Source **0x284 frame /EBP-0xC saved-this**
remains wrong versus original **0x380 /EBP-0x34**. **14 nondefault
markers**, one default marker and missing native shared-tail behavior
remain. Continue with **2D0–2D3 and the later tail states**.

Before/after diagnosis preserves **all 121 previously nonmarker physical
intervals**, including full counts, mnemonic/GPR/width results, non-GPR
operands, branch targets, fields and EBP-debt cohorts. The 76 newly sourced
F1183–F1190 interiors span **37,429 native bytes /10,395 x86 /966 fields**,
with **4,866 GPR positions, 25 widths and stack debt** still unresolved.
No original whole exact credit is added; all pending bytes remain counted.

Build only this affected source with the serial headless F1183 command,
writing `.analysis/f1190-reimu-meter-attacks/native-subtraction.obj`.
Full original intervals, before/initial/corrected objects, rejected source,
CFG/field diagnosis, preservation and hashed summary remain in that ignored
directory. Target/tracking, active handoff and `git diff --check` pass;
no accepted source/header, manifest, origins or comparison infrastructure
changed. No full CI/corpus replay. Canonical status remains **982 whole
exact functions /871,649 CODE bytes**, 44.16% reviewed /44.09%
conservative, with all 22 authored giants pending.
