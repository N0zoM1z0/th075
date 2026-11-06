# F1187 — Reimu twelve original 194–1A1 attack states

The live one-body `probes/FighterWhole0045DD70F1183.cpp` now includes
`ReimuScriptedCombosF1187.inc` and its genuine shared shot/policy fragments.
The complete R063-authored **60,999B/16,837-x86** original remains
**NONEXACT**. These are original switch interiors, not separately accepted
functions.

| State | Native complete interior CODE | Native x86 | Physical external fields | Wrong GPR positions |
| --- | ---: | ---: | ---: | ---: |
| 194 | 1,260 | 328 | 27 | 198 |
| 195 | 1,260 | 328 | 27 | 198 |
| 196 | 680 | 181 | 19 | 96 |
| 197 | 680 | 181 | 19 | 96 |
| 198 | 287 | 80 | 9 | 45 |
| 19A | 808 | 217 | 22 | 123 |
| 19B | 808 | 217 | 22 | 123 |
| 19C | 680 | 181 | 19 | 96 |
| 19D | 223 | 62 | 7 | 33 |
| 19E | 287 | 80 | 9 | 45 |
| 1A0 | 808 | 217 | 22 | 123 |
| 1A1 | 321 | 88 | 10 | 51 |
| **Twelve new states** | **8,102** | **2,160** | **212** | **1,227** |

All source interval lengths, instruction counts, mnemonics and instruction
widths agree. Every actual direct branch destination, non-GPR operand and
physical external field destination is checked from one freshly compiled
complete parent. Native intervals are contiguous **00464BD0..00466B75**,
with all exits retained. GPR roles and EBP operands still differ, so none
receives exact-byte credit.

194/195 retain per-frame gravity, a stage-4 recoil (-3,8,0.55), two actual
five-shot sequences, the unsigned +0x4F0 resource guard, repeat<2 and
auxiliary-4 rewind. 194 uses angles -20/-10/0/10/20, facing offset 83
and native Y=117 (00659098); 195 uses -30/-40/-50/-60/-70, offset 67
and Y=75 (0065826C). The existing F1186 volley body now parameterizes
its fifth angle; both previously sourced 190/191 still instantiate 20.

The six random-angle attacks preserve three separate native RNG calls,
actual `int SelectRange(int,int)` ABI, signed subtraction before FILD,
per-shot speed/animation and unsigned resource predicates. Ground
196/197 use different angle biases (2/22), X offsets (114/90) and Y
constants (96/158), with speed 25, range 4, repeat<4 and +0x4E8.
Air 19A/19B use biases 2/-28 and offsets 83/67, with stage>5 gravity
and an early landing return before animation completion.

19C is intentionally asymmetric: speed 10, range 10, bias 5, effect
0x342, repeat<3 /+0x4EC, but animations **30/20/30**. Air 1A0 keeps
speed 25 and effect 0x342, with ranges **10/4/4**, biases **5/2/2**
and animations **30/30/20**. Initial uniform policies for 1A0 were
rejected against the actual second/third native immediates. A borrowed
vertical-speed read restores native FLD(member)/FMUL(global) ordering
without changing arithmetic or adding an unused temporary.

198/19E preserve 192's actual repeated projectile flow with distinct
0x33A/0x339 effects. 19D emits 0x32C at stage 6, angle -30, speed 8,
X offset 37 /Y=117, with animation 200 before its completion query.
1A1 checks landing before stage-zero motion scaling, emits 0x32C with
angle 30, offset 12 /Y=120 and retains the native absence of added gravity.
No other fighter's superficially similar policy is substituted.

The complete source now emits **36,942B/10,116 x86**, with **1,090
post-RET DATA bytes**, all 142 live dense-label identities and all 522
sparse DATA bytes checked. Frame **0x178 /saved-this EBP-0xC** remains
wrong versus original **0x380 /EBP-0x34**. There are **44 nondefault
markers**, one default store and missing native common-tail behavior.
Next source group: 1F4–1FB. All original pending bytes stay in the denominator.

Before/after diagnosis preserves **all 87 previous nonmarker physical
intervals**, including full counts, mnemonics/GPR/widths, non-GPR operands,
actual branch targets, external fields and EBP-debt cohorts. Across
F1183–F1187, 46 newly sourced interiors span **21,770 native bytes /
6,005 x86 /552 fields**; 2,191 GPR positions, 23 widths and stack debt
remain. This is interior evidence, not new whole-function exact credit.

Build only the affected source with the serial headless F1183 command,
writing `.analysis/f1187-reimu-scripted-combos/native-policy.obj`.
Native intervals, before/recovered/final objects, rejected initial policies,
physical CFG/field diagnosis, prior-preservation and hashed summary are
retained locally in that ignored directory. No accepted source/header,
manifest, origin evidence or comparison infrastructure changed. Target,
tracking, handoff audit and `git diff --check` pass; no full CI or corpus
replay. Canonical status remains **982 exact whole functions /871,649
CODE bytes**, 44.16% reviewed /44.09% conservative, 22 giants pending.
