# F975 — Original third fighter actions 19D/19E/19F and genuine x87/angle grammar

The pinned Japanese TH075 v1.11 whole
game fighter at `004AC040` contains
**82,796 native callable CODE B /
22,721 x86** and **1,126 separately
owned afterRET jump-table DATA B**.
The growing [selected normal VC7.1
C++ parent](../probes/FighterWhole004AC040F975.cpp)
is still PARTIAL, with many real
game states unrecovered and a
nonnative saved-`this` EBP layout
and 0x720 frame. The original
whole function is **NONEXACT**.

Three real actor-specific native
handlers have been sourced:

| Original handler | Physical original PE range | Complete native case CODE | Real PE external fields |
| --- | --- | ---: | ---: |
| **19D** | **004B3B4E..004B3CDE** | **400B /97 x86** | **7** |
| **19E** | **004B3CDE..004B3EB9** | **475B /128 x86** | **12** |
| **19F** | **004B3EB9..004B4097** | **478B /128 x86** | **12** |
| Three contiguous states | — | **1,353B /353 x86** | **31** |

The original 19D initializes
true +0x7C state and signed
+0xF00/+0xF02 counters, then at
signed stage greater than 5,
positive counter guard and F02<5
prepares `00453D40(0)`,
starts `0046D000(0x28)`,
sets actual angle at +0x314
from `F02*4+55` and real
+0x318=15.0f. It emits **one**
native `00453A70(0x326)`
shot with genuine X calculated
from signed facing×
`(47−F02*10)` and float
`this+0x44`; its Y is
`this+0x48+00658264+F02*20`
using the **real integer FIADD
x87 instruction**. The actual
short-counter update and native
animation completion to action2
are preserved.

The original 19E/19F are
different late-ground-motion
states. Both initialize +0x7C,
short F00/F02, and multiply
two real motion floats at
+0x50 and +0x54 by PE float
**00657F74**, with authentic
original **FLD member, FMUL
global** opcode/width order.
They check stage greater than
4 and F00/F02 guards, prepare
action0 and animation0x28,
fire a single real raw-X/
float-Y `00453A70(0x326)`
projectile, update short
counters, then separately
perform ground collision
`POS48+POS54<=0065782C`,
native ResetAt453E20,
SetNativeActionAt40FAC0(0xA),
frame completion action9,
and stage4 sprite0x335
transition.

The true original angle
integer-conversion differs:

- **19E:** `float(0−F02*4)`
  naturally emits original
  **SHL, XOR zero, SUB, FILD**
  grammar.
- **19F:** `float(−45−F02*4)`
  naturally emits **SHL,
  MOV immediate −45, SUB, FILD**.
  This explains the true
  three-byte original
  handler-length difference,
  instead of inventing
  padding.

[Source natural C++](../probes/FighterThirdBossStages19D19FF975.inc)
uses true game operations, member
types, physical PE targets and
original evaluation ordering,
without manual assembly, byte
grafts, compiler-only fake locals
or masked relocation errors.

The bounded [original PE verifier](../scripts/verify-third-fighter-stages19d19f-f975.py)
freshly compiles **two complete
original-shaped normal VC7.1
partial fighter parents**:
tracked F974 with old three
markers and F975 with real
source. It checks whole pinned
original PE state boundaries,
all 353 ordered original native
mnemonics and widths, **31
real zero-addend typed PE
call/global destinations**,
previous authentic 19C, all
**151 real afterRET DIR32
table entries and 522 native
nonfield DATA bytes**.

| Whole partial parent | F974 markers | F975 real |
| --- | ---: | ---: |
| Compiled source CODE B | 32,180 | **33,488** |
| Source x86 | 8,848 | **9,195** |
| Real 19D source B/x86 | 15/2 | **400/97** |
| Real 19E source B/x86 | 15/2 | **475/128** |
| Real 19F source B/x86 | 15/2 | **478/128** |
| Original mnemonic/width differences | unaligned | **0/0 all** |
| Original GPR-role differences | unaligned | **65/84/84** |
| Real typed original PE fields | markers | **7+12+12** |
| Original afterRET DIR32/nonfield DATA | 151/522 | **151/522** |
| Whole original 82KB fighter exact | NO | **NO** |

All native inner-case lengths
and x86 widths match, but
original receiver EBP slot,
actual signed integer-to-x87
scratch positions, 65/84/84
GPR roles, other original game
states, whole-parent jumps
and relocation offsets
remain nonnative. Neither
inner case nor incomplete
parent earns complete original
callable CODE credit.

Reproduce ONLY affected
normal giant partial sources:

    scripts/repo-python scripts/verify-third-fighter-stages19d19f-f975.py

Original physical PE comparison,
native C++/OBJ/PDB, VC7.1
logs and verification JSON
are under ignored
`.analysis/f975-third-original-proof/`
with exploratory original-shaped
source in
`.analysis/f975-third-late/`.

**Zero newly accepted entire
original game callable functions
or CODE B; no all-unit cold replay.**
