# F971 — Three authentic five-shot states in original 82KB fighter 004AC040

The pinned Japanese TH075 v1.11 original
`004AC040` contains **82,796 callable original
CODE B/22,721 x86**, plus a distinct owned
**1,126B afterRET jump-table DATA region**.
The now-tracked cumulative [partial natural
VC7.1 C++ father](../probes/FighterWhole004AC040F971.cpp)
still has unrecovered original actions, stack
owner lifetimes, original saved-this EBP and
full 0x720 frame, so the *whole original*
fighter remains **NONEXACT**.

Three genuine native original handlers,
previously two-instruction 15-B source
markers, each own **507 original CODE B,
146 original x86, fifteen true original
PE-targeted external fields**:

| Handler | Physical native original interval | Real original 5-shot behavior |
| --- | --- | --- |
| **196** | **004B2DF5..004B2FF0** | stage6, X facing multipliers **39/44/49/54/59**, angle=0.0f, animation completion action0 |
| **197** | **004B2FF0..004B31EB** | stage5, X facing multipliers **85/91/97/103/109**, angle=25.0f, action0 |
| **198** | **004B31EB..004B33E6** | stage6, X facing multipliers **92/98/104/110/116**, angle=0.0f, action2 |

Each real original state initializes
+0x7C=1 and calls ResetAt453E20
at stage0/frame0; independently
tests frame completion using
0040FA30/0040FAC0, then at the
actual stage/frame gate calls
PrepareActionAt453D40(0), stores
real source float `+0x314` angle
and `+0x318=20.0f`, and issues
**five complete individual original
`00453A70(0x328)` sprite shots**
with real float X calculated from
signed facing×distinct multiplier
plus actual this+0x44, original
Y=this+0x48 plus its independently
observed original global float,
signed facing, trailing layer 1.
Finally it invokes
StartAnimationAt46D000(**0x96**).

The fifteen original global Y
target addresses are *different*
and are checked individually:

- 196: 00659494, 00659490,
  00659294, 0065948C, 00659488.
- 197: 00659484, 00659480,
  00659498, 0065947C, 00659478.
- 198: 0065826C, 00658264,
  00658294, 00657878, 00657CBC.

Other fighters' historical eight-shot
or three-shot handlers are **not**
assumed to be these original
five-shot sequences. The
[new normal C++](../probes/FighterThirdBossFiveShot196198F971.inc)
uses source-level actor game fields,
preserving real five separate calls,
original signedness and argument
evaluation order; it does not use
filler stack locals, fake loops,
manual native bytes or ASM.

## Entire original-shaped parent checks

The bounded
[`verify-third-fighter-five-shot-f971.py`](../scripts/verify-third-fighter-five-shot-f971.py)
freshly builds **two ENTIRE normal
pinned VC7.1 partial father C++
sources**: tracked F970 with
three markers versus selected
F971 with actual C++ states.
It independently rereads the pinned
original complete 82KB game
function, original case boundaries,
all **438 ordered native instruction
mnemonics and widths**, all **45
true zero-addend typed PE/COFF
external destinations**, preceding
original 195 PE references, and
all **151 real afterRET local
DIR32 table entries plus 522
nonfield DATA bytes**.

| Whole partial parent | F970 original markers | F971 three real cases |
| --- | ---: | ---: |
| Compiled source CODE B | 28,868 | **30,344** |
| Compiled source x86 | 7,910 | **8,342** |
| 196 source CODE/x86 | 15/2 | **507/146** |
| 197 source CODE/x86 | 15/2 | **507/146** |
| 198 source CODE/x86 | 15/2 | **507/146** |
| Wrong original mnemonic/width positions | not aligned | **0 / 0 each** |
| Wrong original GPR-role positions | not aligned | **77 each** |
| Typed original external PE fields checked | markers | **15 + 15 + 15** |
| AfterRET original DIR32/nonfield bytes | 151/522 | **151/522** |
| Complete 82KB original game function exact | NO | **NO** |

Although the original inner case
lengths and ordered instruction
widths are now exactly aligned
and the original 15 relocation
targets/case are verified, the
source still saves `this` at
a nonnative EBP slot and its
15 true signed integer-to-x87
scratch locations are not the
original deep EBP−0x114..−0x14C
region. Physical GPR roles differ
in **77 instructions per state**.
Original whole-parent jump/COFF
field locations also differ.
**Matching total length is not
byte-for-byte original CODE.**

Reproduce only two full affected
partial parent normal VC7.1 builds:

    scripts/repo-python scripts/verify-third-fighter-five-shot-f971.py

Source/OBJ/PDB/compiler logs and
original PE-backed receipt are
under ignored
`.analysis/f971-third-original-proof/`
and exploratory full-source builds
under `.analysis/f971-third-five-shot/`.

**Zero new original whole callable
exact CODE/units; no 979-unit
cold replay.**
