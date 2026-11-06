# F1191 — Reimu eight counter/drift/timer states in native physical order

**Historical F1191 checkpoint:** F1192 removes all remaining markers,
restores original frame/all stack slots and whole CFG/PE destinations;
[current full-parent proof](REIMU_WHOLE_STACK_CFG_F1192.md). The dimensions
below describe commit `b3291a60`.

The same one-body `probes/FighterWhole0045DD70F1183.cpp` now restores
2D0–2D3, 2DF/2E0, 2E5 and 2F9 through the F1191 counter/drift/timer
fragments. Original **0045DD70 remains NONEXACT**, 60,999B/16,837 x86.

| State | Complete native interior CODE | Native x86 | Physical external fields | Wrong GPR positions | Wrong widths |
| --- | ---: | ---: | ---: | ---: | ---: |
| 2D0 | 676 | 173 | 14 | 110 | 0 |
| 2D1 | 685 | 176 | 14 | 113 | 0 |
| 2D2 | 779 | 205 | 15 | 135 | 0 |
| 2D3 | 788 | 205 | 15 | 135 | 0 |
| 2DF | 301 | 83 | 11 | 42 | 0 |
| 2E0 | 301 | 83 | 11 | 42 | 0 |
| 2E5 | 368 | 102 | 10 | 66 | 0 |
| 2F9 | 329 | 90 | 10 | 0 | 1 |
| **Eight new states** | **4,227** | **1,117** | **100** | **643** | **1** |

A fresh complete parent verifies every instruction count, mnemonic,
non-GPR operand, actual direct branch target and physical external field
destination. 2F9's sole width difference is the final return JMP: native
5B, source 2B while six short research markers still follow. Its source
interval is 326B; GPR roles agree. This is diagnostic evidence, not exact
credit. Other seven interval lengths and widths agree; stack slots remain
wrong. Sources preserve the **physical order of all 144 native handler
starts**, keeping 2DB/2EF holes between the proper neighboring states.

2D0/2D1 retain three stage-specific shots and signed-setting repeat limit
`3*setting+1`, with angle `5*counter` versus `5*counter+30`. 2D2/2D3
retain actual nonnegative-stage gravity, early landing reset/return, auxiliary
completion and integer formulas `0-6*counter` /`-30-9*counter` before
FILD. These are not algebraically replaced with different machine grammar.

2DF/2E0 retain distinct random drift, auxiliary completion and vertical
ranges: original global 0065907C is **-6**, not an assumed positive speed;
00657850 is **10**. Both land before later state processing. 2E5 keeps
its signed-setting timer, two repeat counters and both original zero additions
to X. 2F9 preserves the setting<2 effect choice and timer factor 20.
No extra sound, gravity, guard or helper calls are introduced.

The partial parent now emits **56,273B/15,547 x86**, plus the native-shaped
**1,090 DATA bytes**. All 142 dense-label identities and 522 sparse bytes
are rechecked. Frame **0x2FC /saved-this EBP-0xC** remains wrong versus
**0x380 /EBP-0x34**. The six remaining case markers are **2DB, 2EF,
303, 304, 31B and 31C**, plus the default marker/missing common getter tail.
Before/after diagnosis preserves all **129 prior nonmarker intervals**,
including counts, mnemonic/GPR/width results, non-GPR operands, branches,
fields and EBP-debt cohorts. The F1183–F1191 recent 84 states span
**41,656 native bytes /11,512 x86 /1,066 fields**, with 5,509 GPR
positions, 26 widths and stack debt still wrong. These are interior totals,
not whole accepted bytes; all pending original bytes remain counted.

Build only this source with the F1183 headless serial command, writing
`.analysis/f1191-reimu-tail-states/native-order.obj`. Before/initial/ordered
objects, native intervals, rejected initial source order, field/CFG diagnosis,
preservation and hashed summary remain in that ignored directory. Target,
tracking, active handoff and `git diff --check` pass. No accepted source,
header, manifest, origin or comparison infrastructure changed; no full CI
or corpus replay. Canonical exact status remains **982 /871,649 CODE
bytes**, 44.16% reviewed /44.09% conservative, with 22 giants pending.
