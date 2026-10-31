# F977 — Native original 1A1 five/eight random loops recover real parent ESI saving

The pinned Japanese TH075 v1.11
original fighter `004AC040`
has **82,796 whole callable CODE
B /22,721 x86** and separately
owned **1,126 afterRET jump-table
DATA bytes**. The tracked cumulative
[original-shaped partial fighter](../probes/FighterWhole004AC040F977.cpp)
does NOT reproduce the complete
native original game function:
several actions and exact source
owner lifetimes are absent,
the native full stack frame is
0x720 and the real receiver is
saved at EBP−0x64.

The newly source-backed real
original **1A1** handler physically
occupies **004B42D1..004B450B**,
exactly **570 native internal
CODE B /151 x86 /12 actual
PE external field targets**.
This is distinct from but closely
related to F976's original
1A0 (570B/148 x86/12 real
native fields). Both are genuine
source-level **5/8 randomized
projectile loops**, not fake
compiler padding loops:

- Stage0/frame0 initializes
  true +0x7C and calls
  ResetAt453E20. Unlike
  1A0, 1A1 does **not**
  decrement short F00.
- The real original
  frame getter/setter
  transitions to action0;
  stage5/frame0 prepares
  00453D40(0).
- When signed mode byte
  +0x39D equals **2**, it
  fires FIVE sprite0x344
  projectiles, using actual
  angle +0x314=30.0f,
  speed +0x318=10.0f,
  Y base `this+0x48+
  0065786C+shot*40`
  and RandAt455580(0,20).
  The true integer X offset
  is **`30−shot*10 +
  RandAt455580(0,80)`**,
  multiplied by signed
  facing, then converted
  to float and added to X.
- Otherwise it fires
  EIGHT sprite0x344 shots,
  using Y base `shot*30`
  and native X offset
  **`20−shot*10+
  RandAt455580(0,100)`**.
  Both paths call native
  00453B50 with genuine
  float X/Y arguments,
  signed facing, layer
  1,0,1 and the correct
  original random-source
  evaluation order.

The integer X expression
naturally keeps the
`30/20−shot*10` source
value in **ESI across the
next native 00455580
random-number call**, then
adds the RNG result,
multiplies by signed
facing and performs FILD.
Original ESI roles at
physical 1A1 ordinals
73/74/79/82 and
130/131/135/139 now appear
in real VC7.1 source output.
This is natural compiler
register ownership, not
manual register forcing.

The independently reproducible
[target/VC7.1 verifier](../scripts/verify-third-fighter-random-loop-1a1-f977.py)
freshly builds two ENTIRE
original-shaped partial
fighter C++ parents,
F976 old 1A1 marker and
F977 actual normal source.
It reads the original
SHA-pinned full 82KB game
PE, all original
151 x86 of 1A1, the
real ESI lifetime, all
**12 actual zero-addend
typed 1A1 PE/COFF
call/global destinations**,
previous 1A0 12 PE targets,
the 191 original x87
width debt, all **151
real afterRET DIR32
labels and 522 native
nonfield DATA bytes**.

| Whole partial father | F976 prior | F977 real 1A1 |
| --- | ---: | ---: |
| Emitted source CODE B | 34,055 | **34,624** |
| Emitted source x86 | 9,341 | **9,492** |
| Native 1A1 CODE B/x86 | marker15/2 | **570/151** |
| Wrong 1A1 native mnemonic/width | n/a | **0/0** |
| Wrong original 1A1 GPR roles | n/a | **67** |
| True 1A1 original PE targets | marker | **12/12** |
| Parent saves ESI | NO | **YES** |
| Generated partial frame | 0x16C | **0x194** |
| **Earlier native 191 width errors** | **8** | **4** |
| Native afterRET DIR32/nonfield DATA | 151/522 | **151/522** |
| Complete original 82KB exact | NO | **NO** |

This authentic loop also
**increases the same entire
parent compiler stack frame**
and requires native ESI
saving in the prologue.
Its receiver source stack
slot moves to **EBP−0x20**.
As a separate real
whole-parent effect, four
additional original 191
MOV/FILD instruction widths
become correct, reducing
earlier native 191 source
width errors from **8 to 4**
without editing any 191 C++.
Together with F976's prior
12→8 improvement, the true
1A0 and 1A1 source restores
**eight native 191 width
positions**. This does not
reconstruct the original
EBP−0x64 receiver, 0x720
stack frame, all remaining
GPR roles or whole-game
relocation positions.

Reproduce only the two
affected entire original-
shaped partial 82KB sources:

    scripts/repo-python scripts/verify-third-fighter-random-loop-1a1-f977.py

Compiled original-shaped
C++/OBJ/PDB, target PE
verification receipt and
VC7.1 compiler transcripts
remain under ignored
`.analysis/f977-third-original-proof/`
and independent initial
trials under
`.analysis/f977-third-random-1a1/`.

**Zero new accepted original
complete callable functions or
CODE bytes; no 979-unit full
cold replay.**
