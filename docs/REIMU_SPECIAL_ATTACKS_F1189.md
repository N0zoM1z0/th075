# F1189 — Reimu fifteen original 252–263 special-action states

The one-body `probes/FighterWhole0045DD70F1183.cpp` now includes
`ReimuSpecialAttacksF1189.inc` and its shared native-policy fragments.
The complete independently R063-authored **60,999B/16,837-x86** original
remains **NONEXACT**. No interior is accepted as a separate function.

| State | Native complete interior CODE | Native x86 | Physical external fields | Wrong GPR positions | Wrong widths |
| --- | ---: | ---: | ---: | ---: | ---: |
| 252 | 260 | 72 | 6 | 47 | 1 |
| 253 | 260 | 72 | 6 | 47 | 0 |
| 254 | 224 | 63 | 6 | 40 | 1 |
| 258 | 484 | 134 | 14 | 74 | 0 |
| 259 | 484 | 134 | 14 | 74 | 0 |
| 25A | 512 | 142 | 15 | 82 | 0 |
| 25B | 512 | 142 | 15 | 82 | 0 |
| 25C | 320 | 87 | 9 | 48 | 0 |
| 25D | 707 | 187 | 17 | 108 | 0 |
| 25E | 348 | 95 | 10 | 56 | 0 |
| 25F | 735 | 195 | 18 | 116 | 0 |
| 260 | 209 | 59 | 6 | 33 | 0 |
| 261 | 223 | 62 | 7 | 33 | 0 |
| 262 | 251 | 70 | 8 | 41 | 0 |
| 263 | 251 | 70 | 8 | 41 | 0 |
| **Fifteen new states** | **5,780** | **1,584** | **159** | **922** | **2** |

One fresh serial pinned-VC7.1 whole-parent build reproduces all instruction
counts, mnemonics, non-GPR operands, actual handler-relative branch targets
and physical external field destinations. Native intervals are contiguous
**00467D08..0046939B**, including every exit. 252/254 differ by one byte
each because native/source decrement uses DL/AL and AL/CL respectively;
this is actual AL-immediate encoding debt. Other widths agree. Stack slots
and GPR roles still differ, so no exact-byte credit is added.

252/253 remain separate physical source handlers despite identical native
non-GPR behavior. They decrement byte +0x366 without a fabricated zero
guard, initialize the native flags, conditionally grant short +0x3B0=1000
when +0x3B6 is zero and +0x7C is one, and spawn effect 0x37 at stage 5.
254 lacks that bonus branch. All retain preparation 0x21 and the actual
opponent +0xEFA reset after the spawn/preparation calls.

258/259 emit four independent 0x321/0x322 effects with selectors
0.0/1.0/2.0/3.0. They assign +0x318 from current Y+96 only before the
first spawn, yet reevaluate each call's Y and signed-facing X arguments.
25A/25B instead scale both motion values by the real 00657F74 constant,
use X offset 12 /Y+120, and finish through action 9. Their singleton/table
entries remain distinct. No source loop replaces the original four calls.

25C emits angles **30/-30**, while 25E emits **-30/30**. Ground 25D
uses **20/40/70/-20/-40/-70**; airborne 25F uses
**20/40/60/-20/-40/-60**. Ground shots use X offset 30 and native
Y=130 at 0065908C; air uses offset 12 and Y=120. Each writes actual
angle/speed fields before spawning. Animation precedes sound, while the
ground animation-completion query occurs after firing and the air query
before firing. These actual order differences are preserved.

260 is a zero-angle single 0x32C shot with animation 200 and no invented
sound/preparation call. 261 uses angle -45, X offset 37 /Y=117 and
preparation 0x29. Air 262/263 use angles 0/+45, X offset 12 /Y=120,
the same preparation and native action-9 completion. All names and
semantic labels remain provisional; original raw ownership is unchanged.

The complete partial source now emits **46,890B/12,933 x86**, plus
**1,090 post-RET DATA bytes**. All 142 live dense-label identities and
522 sparse DATA bytes are checked. Source **0x21C frame /saved-this
EBP-0xC** remains wrong versus original **0x380 /EBP-0x34**. There
are still **22 nondefault markers**, a default marker and missing native
shared-tail behavior. Next missing source group: **2BC–2C3**.

Before/after diagnosis preserves **all 106 previous nonmarker physical
intervals**, including counts, mnemonic/GPR/width results, non-GPR operands,
actual branch targets, fields and EBP-debt cohorts. F1183–F1189 now source
68 earlier missing states across **32,048 native bytes /8,866 x86 /
817 fields**. This recent cohort still has **3,986 wrong GPR positions,
25 widths and stack debt**. No whole original exact bytes are accepted;
all pending bytes remain in the conservative denominator.

Build only this affected source with the headless serial F1183 command,
writing `.analysis/f1189-reimu-special-attacks/recovered.obj`. Full native
intervals, before/fresh objects, CFG/field comparisons, preservation and
hashed summary are retained in that ignored directory. Target/tracking,
handoff audit and `git diff --check` pass. No accepted source/header,
manifest, origin evidence or comparison infrastructure changed, and no
full CI or corpus replay ran. Canonical status remains **982 whole exact
functions /871,649 CODE bytes**, 44.16% reviewed /44.09% conservative;
all 22 authored giant callables remain pending.
