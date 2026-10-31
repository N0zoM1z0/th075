# F1002 — Original fighter 2C0/2C1, all 276 native GPR roles aligned

The SHA-pinned Japanese TH075 v1.11 original 004AC040 fighter
contains **82,796 callable CODE bytes /22,721 x86**, plus
1,126 separately owned afterRET jump-table DATA bytes. The
[tracked cumulative normal VC7.1 C++](../probes/FighterWhole004AC040F1002.cpp)
is still a PARTIAL original-shaped parent, NOT an exact original
whole callable (native stack frame 0x720, saved receiver EBP−0x64).

Two true original physical game actions were independently decoded:

| Original action | Physical PE CODE interval | Native interior CODE/x86 | True typed original PE fields |
| --- | --- | ---: | ---: |
| **2C0** | 004BC0A8..004BC29A | **498B /135 x86** | **14** |
| **2C1** | 004BC29A..004BC4A4 | **522B /141 x86** | **14** |

Their original stage0/frame0 initializes shorts F00/F02=0,
int +0x7C=0, ResetAt453E20, and short +0x80=99.
The animation getter 0040FA30 transitions through real
setter 0040FAC0(0). Both issue an immediate seven-argument
native **00453B50** effect with actual *raw 32-bit actor X
bits* from +0x44 and genuine *float Y* from actor+0x48
plus native float global **00657888**; its sprite is
**0x332** for 2C0, **0x32F** for 2C1.
The source preserves the genuine mixed raw-X/float-Y ABI,
rather than treating two machine arguments as the same type.

Actual original stage5/frame0 control flow differs:

- **2C0:** original F02<**1** increments F02, invokes
  auxiliary action3 and immediately exits. On its next
  stage5/frame0 path it calls real **00453E80(0x64)**,
  prepares native 00453D60(**0x17**) then 00453D40(**9**).
- **2C1:** at signed stage>=5, the original first writes
  signed short **F0C=180**. Its F02<**4** stage5 guard
  increments F02, calls auxiliary action3 and exits.
  Later native stage5 invokes 00453E80(**0x28**),
  prepares 00453D40(**0xA**) then 00453D60(**0x17**).

Both then reduce float actor+0x36C by physical PE global
**00657888**, emit a genuine **00453C80(0x73)**
special shot with signed-facing×18 converted by native
FILD/FSUBR and **float Y+original global 00659284**,
then call 00453B50 with a fixed float screen-space
640.0f×320.0f effect, sprite **0x330** for 2C0 versus
**0x32E** for 2C1, original layer flags 1,2,0,1.
The original 2C0 stores signed short gauge+0x3B0
into **F10** and sets F12=1; 2C1 instead stores the
same original gauge into **F0C** and sets F0E=0.
Stage11/frame0 invokes auxiliary action9 with bounded F00.

The [normal source](../probes/FighterThirdBossStages2C02C1F1002.inc)
uses genuine original owner fields, C++ argument value
categories, source-order conditions and a declaration-only
physical mixed-ABI member interface. No fake stack values,
manual registers, bytes or relocation masks were introduced.

The [bounded original PE verifier](../scripts/verify-third-fighter-stages2c0-2c1-f1002.py)
freshly compiles TWO ENTIRE original-shaped PARTIAL 82KB
fighter parents (F1001 prior markers and F1002 real C++).
It independently checks **all 276 ordered original
mnemonics, instruction widths AND GPR operand roles**,
**all 28 physical zero-addend typed PE/COFF target fields**,
the preceding real 2BC and 2BD, all **151 original
afterRET DIR32 case labels** and **522 true nonfield
DATA bytes**.

| Whole original-shaped PARTIAL parent | F1001 old | F1002 source |
| --- | ---: | ---: |
| Emitted partial CODE B | 62,063 | **63,053** |
| Emitted partial x86 | 17,012 | **17,284** |
| 2C0 source CODE B/x86 | marker 15/2 | **498/135** |
| 2C1 source CODE B/x86 | marker 15/2 | **522/141** |
| Wrong native mnemonic/width/GPR positions | not aligned | **0/0/0 both** |
| Genuine typed original PE fields | markers | **14+14** |
| Previous 2BC/2BD mnemonic/width debt | 0/1 | **0/1 unchanged** |
| Partial source stack frame | 0x45C | **0x464** |
| Entire original 82KB callable exact | NO | **NO** |

**Matching all 276 original GPR roles does not make either
state an independent complete original game callable.**
Original saved receiver at EBP−0x64, its full 0x720 frame,
original deep native scratch offsets, remaining unsourced
actor cases and absolute/relative whole-parent PE fields
are not yet reconstructed.

Reproduce only the two affected complete PARTIAL parent sources:

    scripts/repo-python scripts/verify-third-fighter-stages2c0-2c1-f1002.py

The real PE/COFF receipts and normal VC7.1
compiler C++/OBJ/PDB are retained in
.analysis/f1002-third-original-proof/ and
.analysis/f1002-third-2c0-2c1/.

**New accepted whole original callable CODE/functions: zero.
No 979-unit cold replay.**
