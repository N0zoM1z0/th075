# F972 — Real 199/19A five-shot motions and native x87 operand order

The pinned Japanese TH075 v1.11 original
game fighter `004AC040` spans **82,796
callable native CODE B/22,721 x86** plus
**1,126 afterRET jump-table DATA B**.
The [tracked cumulative original-shaped C++](../probes/FighterWhole004AC040F972.cpp)
still implements only a partial native
game parent; original 0x720 frame and
the saved-`this` EBP−0x64, many actions,
call fields and GPR roles remain nonnative.
The whole original fighter is **NONEXACT**.

Two genuine original physical cases:

| Original handler | True original PE range | Complete inner CODE/x86 | Real native external fields |
| --- | --- | ---: | ---: |
| **199** | **004B33E6..004B3637** | **593 B /170 x86** | **19** |
| **19A** | **004B3637..004B3888** | **593 B /170 x86** | **19** |
| Both | consecutive | **1,186 B /340 x86** | **38** |

The actual original starts with
signed stage0/frame0 X and vertical
velocity scaled by global float
**00657F74**, sets int +0x7C=1,
and has a real ground collision
`POS48+POS54<=0065782C`,
zeroing actual Y, calling
ResetAt453E20 and original
`0040FAC0(0xA)` before its
normal stage5 continuation.
Animation completion otherwise
transitions with action9.

At stage5/frame0 each handler
sets the true native float
+0x314 and +0x318=20.0f,
calls original
PrepareActionAt453D40(0),
issues **five complete
`00453A70(0x328)` float-X/Y
projectiles**, then calls
StartAnimationAt46D000(0x96).
The original physical operands
are actor-specific:

- **199** angle0, signed facing
  multipliers **76/81/86/91/96**,
  real Y globals **0065836C,
  00659474, 00657860, 00659284,
  00659470**.
- **19A** angle−20.0f, facing
  multipliers **98/92/86/80/74**,
  actual Y globals **00659470,
  00658364, 0065946C, 00659468,
  00659464**.

## Re-testing prior source value-category hypotheses

The initial correct-valued ordinary
source used `POS54=POS54*global`.
In the full father, pinned VC7.1
emitted x87 source
`FLD [00657F74]; FMUL [this+54h]`
rather than the **real original**
`FLD [this+54h]; FMUL [00657F74]`.
Although total case length was
593B in both versions, the two
original inner x86 widths were
incorrect at native state ordinals
**14/15** (6B/3B instead of
3B/6B). Thus the earlier source
must **not** be treated as
native-width exact.

Nine honest full-partial-father C++
variants of lvalue and const
access grammar were rebuilt
under pinned normal VC7.1.
The source `F32(0x54)=F32(0x54)*global`,
without dummy locals or forced
compiler register allocation,
restores the actual original
**FLD member then FMUL global**
width order at both 199/19A,
with identical total CODE B
and one fewer mismatched GPR
role (92→91 per case). Several
independent native-value-category
spellings reach the same geometry,
so no unique historical C++ spelling
is falsely claimed.

The [tracked source](../probes/FighterThirdBossFiveShot19919AF972.inc)
uses this verified natural float-field
access and the five real distinct
projectile calls per state.

The targeted
[`verify-third-fighter-five-shot-motion-f972.py`](../scripts/verify-third-fighter-five-shot-motion-f972.py)
fresh-compiles **two entire original-
shaped normal VC7.1 partial 82KB
parent sources**, tracked F971
markers and F972 natural cases.
It compares the whole pinned
original PE, all ordered 170+170
native mnemonic/width positions,
all **38 typed actual original
PE/COFF call/global destinations**,
previous source-backed 198,
all **151 real afterRET DIR32**
and **522 native nonfield DATA B**.

| Whole *partial* father | F971 source | F972 source |
| --- | ---: | ---: |
| Source original-shaped CODE B | 30,344 | **31,500** |
| Source x86 | 8,342 | **8,678** |
| Real 199 CODE/x86 | 15/2 marker | **593/170** |
| Real 19A CODE/x86 | 15/2 marker | **593/170** |
| Wrong native mnemonic/width roles | n/a | **0/0 both** |
| Wrong native GPR roles | n/a | **91 per case** |
| Real native external PE targets | markers | **19+19** |
| Original afterRET labels/nonfield bytes | 151/522 | **151/522** |
| Original entire 82KB exact | NO | **NO** |

Both case lengths now match and
external source references are
verified, but saved `this`,
original whole-parent EBP,
branches, local integer-to-x87
scratch positions and many GPR
roles remain different. Never
mask relocated bytes or interpret
a same-length internal case
as original complete-function
byte exactness.

Reproduce ONLY the two affected
whole-partial-parent sources:

    scripts/repo-python scripts/verify-third-fighter-five-shot-motion-f972.py

Native PE receipt, C++/OBJ/PDB and
compiler logs remain in ignored
`.analysis/f972-third-original-proof/`;
nine full-parent source grammar
probes are preserved at
`.analysis/f972-third-19919a/grammar/`.

**No new original whole callable
exact function or credited CODE B.
No 979-unit cold replay.**
