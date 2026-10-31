# F974 — Original 82KB fighter's two authentic single-shot 19B/19C actions

The hash-pinned Japanese TH075 v1.11
original fighter `004AC040` has
**82,796 complete callable CODE B/22,721 x86**
and separately owned **1,126 afterRET
jump-table DATA B**. The growing
[tracked whole-shaped normal VC7.1
source](../probes/FighterWhole004AC040F974.cpp)
is still a PARTIAL fighter, with
incomplete original 0x720 stack owner,
EBP−0x64 saved `this` and other
original game actions. This whole
original remains NONEXACT.

The real physical original actions,
which previously had 15B/two-x86
source markers, are:

| Original state | Native physical range | Original full inner CODE | Real PE fields |
| --- | --- | ---: | ---: |
| **19B** | **004B3888..004B39EB** | **355B/87 x86** | **7** |
| **19C** | **004B39EB..004B3B4E** | **355B/87 x86** | **7** |

Both real original game states
initialize +0x7C=1, call original
ResetAt453E20 and clear signed
short +0xF00/+0xF02 at stage0.
After native signed stage/frame
checks, they run actual
PrepareActionAt453D40(0),
StartAnimationAt46D000(0x28),
write source angle and
float +0x318=15.0f, issue
**ONE** true float X/Y
sprite **0x326** using
native 00453A70, set
short F00=2, increment F02,
decrement F00, and transition
via 0040FA30/0040FAC0(0)
on real animation completion.

These are not the older actor's
eight-shot routines. Their original
values differ:

- **19B**: stage greater than
  **5**, angle `F02*4−30`,
  signed facing multiplier **49**,
  original float Y `this+0x48
  + PE global 00659294`.
- **19C**: stage greater than
  **4**, angle `F02*4+30`,
  signed facing multiplier **97**,
  original Y global **00659498**.

The normal [source C++](../probes/FighterThirdBossSingleShot19B19CF974.inc)
preserves source-level game values
and actual native call order,
without artificial locals,
original-byte grafts, fake case
function boundaries or assembly.

The bounded
[`verify-third-fighter-single-shot-f974.py`](../scripts/verify-third-fighter-single-shot-f974.py)
freshly compiles **two ENTIRE original-
shaped partial 82KB VC7.1 father
C++ sources**, tracked F972
prior markers and F974 real
single-shot cases. The pinned
original PE independently
supplies native case boundaries,
all ordered 87+87 original
mnemonics/widths, all
**14 actual zero-addend typed
PE/COFF external target
addresses**, the preceding
source-backed 19A, and the
**151 genuine afterRET local
DIR32 labels with 522 original
nonfield DATA bytes**.

| Whole partial source | F972 marker | F974 natural |
| --- | ---: | ---: |
| Compiled partial CODE B | 31,500 | **32,180** |
| Generated whole x86 | 8,678 | **8,848** |
| 19B source CODE/x86 | 15/2 | **355/87** |
| 19C source CODE/x86 | 15/2 | **355/87** |
| Wrong native mnemonic/widths | n/a | **0/0 each** |
| Genuine GPR-role mismatches | n/a | **56 each** |
| Native original PE targets | stubs | **7+7** |
| Original afterRET DIR32/nonfield DATA | 151/522 | **151/522** |
| Entire 82KB fighter exact | NO | **NO** |

Although the native inner source
lengths and width geometry match,
the cumulative partial parent
still assigns real GPR roles
differently at 56 instructions
per handler. Actual saved receiver,
deep x87 stack scratch, absolute
PE call/jump fields and remaining
game cases prevent byte-exact
whole game comparison. These inner
cases are never separately counted
as original whole callable
native functions.

Run only affected whole-shaped
partial giant compiles:

    scripts/repo-python scripts/verify-third-fighter-single-shot-f974.py

Original PE/COFF verification,
compiled C++/OBJ/PDB, VC7.1
transcripts and independent
expanded source comparisons are
preserved under ignored
`.analysis/f974-third-original-proof/`
and `.analysis/f974-third-single-shot/`.

**Zero new accepted original whole
callable function CODE; no full
979-unit cold replay.**
