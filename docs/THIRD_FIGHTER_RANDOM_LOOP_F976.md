# F976 — Real original 1A0 five/eight random-shot loops and preceding x87 phase

The pinned Japanese TH075 v1.11
original fighter at **004AC040** is
**82,796 whole callable CODE B /
22,721 x86**, plus **1,126
separately owned afterRET jump
DATA B**. The tracked
[cumulative original-shaped
C++ source](../probes/FighterWhole004AC040F976.cpp)
is still PARTIAL and NONEXACT,
without the original 0x720
stack frame and native
EBP−0x64 saved-`this`.

The true original game action
**1A0** spans **004B4097..004B42D1**,
**570 native inner CODE B /
148 x86 /12 genuine typed
PE external fields**.
It initializes real +0x7C
and ResetAt453E20 at
stage0/frame0; decrements
signed short +0xF00, handles
original frame completion
with action0, and at
stage5/frame0 prepares
native 00453D40(0).
The original signed byte
+0x39D selects TWO real
loop profiles:

- **Value 2:** 5 shots,
  original signed 32-bit
  `shot` iterator; angle
  +0x314=0.0f, +0x318=10.0f,
  sprite **0x344**, Y based
  on original **0065786C**
  plus signed `shot*40`
  and `RandAt455580(0,20)`;
  X based on independent
  `RandAt455580(0,80)+30`
  times signed facing, plus
  native X field.
- **Otherwise:** 8 shots,
  same actual source fields
  but Y uses signed
  `shot*30` and X uses
  `RandAt455580(0,100)+20`
  times signed facing.
  Both call actual native
  **00453B50(0x344)** with
  float X and float Y.

The first complete source trial
had the *correct numerical
formula* but performed random
Y computation **before** the
original Y base expression,
because VC7.1 evaluated
`float(Rand20)+base` in
source operand order. This
caused **72 incorrect original
mnemonic positions**, even though
source-level algebra appeared
equivalent. The correct natural
C++ `base + float(Rand20)`
forces native **FLD Y,
FADD global, FIADD shot,
FSTP intermediate, call
Rand20, FILD Rand, FADD
intermediate** evaluation.
It restores **ALL 148
original x86 mnemonics and
original instruction widths**,
including the authentic
two native random calls
per loop iteration and
loop bounds 5/8.
No assembly, fake locals,
native-byte grafts or
artificial loop unrolling
are involved.

The [new tracked ordinary
game C++](../probes/FighterThirdBossRandomLoop1A0F976.inc)
and bounded [complete source
PE verifier](../scripts/verify-third-fighter-random-loop-f976.py)
rebuild TWO entire original-
shaped normal VC7.1 partial
giant parent functions
(F975 marker versus F976
real loops). Both complete
source objects are checked
against the pinned original
whole PE, all **12 typed
actual PE/COFF 1A0 targets**,
true predecessor 191/192
native x86 and fields,
all **151 real afterRET
DIR32 labels and 522
nonfield DATA bytes**.

| Whole partial parent | F975 prior | F976 actual random loops |
| --- | ---: | ---: |
| Emitted partial CODE B | 33,488 | **34,055** |
| Emitted whole-partial x86 | 9,195 | **9,341** |
| Real 1A0 source B/x86 | 15/2 marker | **570/148** |
| Wrong native 1A0 mnemonic/widths | n/a | **0/0** |
| Wrong native 1A0 GPR roles | n/a | **66** |
| Typed original 1A0 PE targets | marker | **12/12** |
| Actual source parent stack frame | **0x144** | **0x16C** |
| Original 191 width errors | **12** | **8** |
| Original afterRET DIR32/nonfield B | 151/522 | **151/522** |
| Full original 82KB exact | NO | **NO** |

**Important cross-case compiler
discovery:** genuine 1A0
local random loop lifetimes
expand the same whole parent
stack frame from 0x144 to
0x16C and move its receiver
save from EBP−0x10 to
EBP−0x18. This naturally
moves four earlier original
191 temporary MOV/FILD pairs
into long-EBP encoding,
recovering **four original
x86 widths** and increasing
191's generated source
length **561→573B**, even
though the actual 191 C++
was never changed. It does
NOT fix the original physical
saved-`this` location
EBP−0x64 or the original
whole 0x720 frame, and
original 191 still has eight
wrong widths. Real full
original register roles,
branch and relocation fields
remain unmatched.

Reproduce ONLY this affected
original-shaped partial giant:

    scripts/repo-python scripts/verify-third-fighter-random-loop-f976.py

Native original PE receipts,
compiled whole C++/OBJ/PDB,
VC7.1 logs and independent
random operand-order controls
are retained under ignored
`.analysis/f976-third-original-proof/`
and `.analysis/f976-third-random-loops/`.

**Zero new accepted entire
original callable game CODE
or exact functions; no
979-unit cold replay.**
