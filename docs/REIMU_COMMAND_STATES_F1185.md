# F1185 — Reimu C8–D0 command and motion states

**Historical F1185 checkpoint:** F1186 extends the same parent to
29,020B/7,980 x86, preserving all 80 prior nonmarker physical intervals.
See [the current scripted-attack proof](REIMU_SCRIPTED_ATTACKS_F1186.md).
The dimensions below describe commit `0bbfeaf7`.

The same live `probes/FighterWhole0045DD70F1183.cpp` replaces nine
markers with normal C++ in `ReimuCommandStatesF1185.inc` and its three
parameterized `ReimuComplexMotionF1185.inc` bodies. The independently
R063-authored original **0045DD70 remains NONEXACT**: 60,999 CODE
bytes /16,837 x86, plus 1,090 owned after-RET DATA bytes. No interior
state is accepted as a separately callable exact unit.

| State | Original complete interior CODE | Native x86 | Physical external fields |
| --- | ---: | ---: | ---: |
| C8 | 529 | 149 | 15 |
| C9 | 443 | 131 | 12 |
| CA | 418 | 121 | 11 |
| CB | 416 | 119 | 11 |
| CC | 435 | 128 | 11 |
| CD | 435 | 128 | 11 |
| CE | 394 | 115 | 9 |
| CF | 114 | 30 | 4 |
| D0 | 195 | 60 | 6 |
| **Nine new bodies** | **3,379** | **981** | **90** |

A fresh serial pinned-VC7.1 whole-parent build reproduces all these
native instruction counts, mnemonics, GPR roles and instruction widths.
All non-GPR operands, direct branch destinations by actual native
handler/instruction ordinal, and 90 physical external field destinations
agree. **Their EBP stack operands still differ.** Instruction agreement
with stack displacement excluded is diagnostic evidence, not byte exactness.
The original physical intervals are contiguous **00461E9B..00462BCD**;
none is cropped to obtain a match.

The earlier eleven 12C–136 bodies now also reproduce all 1,001 GPR
positions and widths: genuine earlier source and expression temporaries
clear the historical F1183/F1184 623-position GPR debt. The seven earlier
59–63 states retain their previous diagnostic results, including all
native control flow, 5F/61 GPR agreement, 269 wrong GPR positions in the
other five states, and three EAX-dependent width differences in 63.
All 27 recently sourced states together cover **9,453 native interior
bytes /2,695 x86 /239 actual external fields**. These are not new
whole-function accepted bytes.

## Independently observed Reimu policies

C8 preserves the native command-selection call at 00454BC0 with actual
three stack arguments `(3, 4, 0xFF)`. Original helper source corroborates
the int /unsigned-char /unsigned-int interface. C8 chooses CC/CD from
signed collision direction, stops on reversal, and limits its auxiliary
repeat to fewer than three. Its brake really tests speed **greater than
8**, subtracts the original shared constant, then clamps speeds **below
9** to 9. The apparently odd thresholds are native behavior.

C8/CA project effect 0x7D horizontally by signed facing times 80, then
emit 0x7E at unshifted X. C9/CB use unshifted X and negated facing for
both effects. Their original Y offsets are respectively 80, 110 and
120. Coordinate DWORD views preserve native MOV/PUSH representation;
computed Y arguments preserve FLD(member)/FADD(global) through a genuine
lvalue borrow. This is not a numeric float-to-int conversion.

CC/CD/CE retain the native animation loop and virtual frame-advance call.
Their velocities are `(0,20)`, `(9,15)` and `(-9,15)`, with **0.65**
acceleration. Only CC/CD have the stage-4 auxiliary transition. CF
reuses the independently checked existing decay body. D0 reverses facing
and horizontal velocity, applies 0.6 gravity and finishes with auxiliary
state **4**, rather than another fighter's state 5.

## Remaining whole-function work and reproduction

The source emits **24,967 CODE bytes /6,844 x86**, with all six switch
groups, 142 actual zero-addend live dense-label identities, and every one
of the 522 sparse DATA bytes rechecked. Its **0x40 frame /EBP-0xC
saved-this** remain wrong versus original **0x380 /EBP-0x34**. There
are still **63 nondefault markers** (64 stores including default), the default marker, and missing
shared getter-tail behavior. Continue with 186 and later attack states;
all original pending bytes remain in the conservative denominator.

Build only this affected research parent, using the command in
[the F1183 proof](REIMU_FALLING_STATES_F1183.md), with output
`.analysis/f1185-reimu-c8-d0/final.obj`. Full native interval disassemblies,
before/recovered/final objects, source snapshot, field/CFG comparisons
and a hashed verified summary are preserved in that ignored directory.
The existing local F1183 `compare.py` reads the final object with action
arguments `c8 c9 ca cb cc cd ce cf d0`, then the seven F1184 and eleven
F1183 actions. It diagnoses the complete object and full native intervals;
it does not accept an exact unit.

Canonical coverage remains **982 whole exact functions /871,649 CODE
bytes**, 44.16% reviewed and 44.09% conservative. No accepted source,
header, exact manifest, origin evidence or comparison infrastructure
changed. No full CI, corpus cold replay or extra test suite was run.
