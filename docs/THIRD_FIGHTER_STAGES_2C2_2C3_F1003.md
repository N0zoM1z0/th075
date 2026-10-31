# F1003 — Original 2C2/2C3: 279 native GPR roles and 28 PE fields aligned

The SHA-pinned Japanese TH075 v1.11 original fighter at 004AC040
owns **82,796 complete callable CODE B/22,721 x86**, plus
**1,126 separately owned afterRET switch DATA bytes**.
The [tracked complete original-shaped PARTIAL source](../probes/FighterWhole004AC040F1003.cpp)
does NOT yet reproduce the entire original game fighter: its native
0x720 stack frame, saved receiver EBP−0x64, original scratch slots
and remaining game cases are not recovered. Whole parent NONEXACT.

The real physical original game handlers are:

| Native original action | Physical PE interval | Original inner CODE/x86 | Actual original typed PE fields |
| --- | --- | ---: | ---: |
| **2C2** | 004BC4A4..004BC6A7 | **515B /138 x86** | **14** |
| **2C3** | 004BC6A7..004BC8B1 | **522B /141 x86** | **14** |
| Together | contiguous | **1,037B /279 x86** | **28** |

Both authentic states initialize signed shorts+0xF00/F02=0,
int+0x7C=0, ResetAt453E20 and short+0x80=99 at stage0/frame0.
The real native animation completion and stage5 subflows are
different, not cloned from the preceding actor:

- **2C2:** if native 0040FA30 matches stage/frame end, invoke
  0040FAC0(0), store real short **F12=1**, issue the original
  00453B50(**0x332**) mixed raw-32-bit-X / float-Y
  seven-argument projectile and **immediately branch to the
  original parent shared tail**. Otherwise the native
  stage5/frame0 F02<1 branch increments F02, invokes auxiliary
  action3 and exits. Its later stage5 path invokes
  00453E80(0x64), prepares 00453D60(0x17) then
  00453D40(9); special projectile **0x74** uses
  signed-facing×18 converted by genuine FILD/FSUBR,
  and fixed screen effect is sprite **0x330**.
  Real F10 stores signed gauge+0x3B0 and F12=1.
- **2C3:** independently sets short **F0C=300**
  only for signed stage>5 (not stage>=5), transitions
  through native animation completion, and emits initial
  seven-arg sprite **0x32F**. Its native stage5 F02<4
  path increments F02/auxiliary3, later invokes
  00453E80(**0x28**) then prepares **00453D60(0x17)
  BEFORE 00453D40(0xA)**. Its special projectile is
  **0x74**, fixed seven-arg effect sprite **0x32E**,
  with real F0C=short3B0 and F0E=0.

Both preserve actual initial float-Y PE global **00657888**,
special-shot Y global **00659284**, original raw-X actor
+0x44 or signed FILD/FSUBR world-X, fixed float screen-space
640×320 parameters, and stage11 bounded F00 auxiliary action9.
The [natural C++ source](../probes/FighterThirdBossStages2C22C3F1003.inc)
does not add dummy locals, assembler, arbitrary padding,
target-native instruction bytes or relaxed relocation checks.

The [bounded original PE verifier](../scripts/verify-third-fighter-stages2c2-2c3-f1003.py)
freshly compiles TWO ENTIRE normal VC7.1 original-shaped
PARTIAL 82KB fighters (tracked F1002 markers and F1003
real states). It checks all **279 original x86 positional
mnemonics, instruction widths AND GPR operand roles**,
**all 28 genuine typed zero-addend PE/COFF call/global
destinations**, the genuine preceding 2C0/2C1 cases,
all **151 original afterRET DIR32 case labels** and
**522 true native nonfield DATA bytes**.

| Whole original-shaped PARTIAL father | Prior F1002 | Real F1003 |
| --- | ---: | ---: |
| Generated partial CODE B | 63,053 | **64,060** |
| Generated partial x86 | 17,284 | **17,559** |
| Real 2C2 generated B/x86 | 15/2 marker | **515/138** |
| Real 2C3 generated B/x86 | 15/2 marker | **522/141** |
| Wrong original mnemonic/width/GPR positions | not aligned | **0/0/0 both** |
| Real original 2C2/2C3 typed PE fields | markers | **14+14** |
| Previous 2C0/2C1 GPR mnemonic/width/PE | 276 x86 aligned | **276 still aligned** |
| Source partial compiler frame | 0x464 | **0x46C** |
| Entire original 82KB callable exact | NO | **NO** |

The complete consecutive **2C0/2C1/2C2/2C3** cohort
now reproduces **555 original positional native x86
mnemonic/width/GPR roles** and **56 actual original PE
target addresses**, but NOT original whole-function
EBP displacements, absolute PE/COFF field placements or
complete fighter source. Internal state bodies are not
independently accepted exact callable functions.

Reproduce only the two affected original-shaped partial
fighter source builds:

    scripts/repo-python scripts/verify-third-fighter-stages2c2-2c3-f1003.py

Normal VC7.1 C++/OBJ/PDB, original PE/COFF receipts and
compiler logs are stored under ignored
.analysis/f1003-third-original-proof/
and .analysis/f1003-third-2c2-2c3/.

**No new accepted complete original callable CODE/functions.
No all-979-unit cold replay.**
