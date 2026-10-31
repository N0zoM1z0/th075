# F994 — Two more native ten-shot loops: all 196 x86 GPR roles align

The SHA-pinned Japanese TH075 v1.11 original fighter 004AC040
contains **82,796 complete callable original CODE B/22,721 x86**
plus 1,126 separately owned afterRET jump-table DATA B.
The tracked
[partial original-shaped normal VC7.1 source](../probes/FighterWhole004AC040F994.cpp)
is not the complete original game callable, which has native
0x720 stack frame and saved receiver EBP−0x64.

Two independently observed actual game handlers:

| Original action | Real PE physical extent | Native case CODE/x86 | Original PE targets |
| --- | --- | ---: | ---: |
| **261** | 004BA93F..004BAAA8 | **361 B/98 x86** | **8** |
| **262** | 004BAAA8..004BAC11 | **361 B/98 x86** | **8** |

Unlike preceding 25F/260 these original states do **not**
invoke ResetAt453E20 at stage0. They set real int+0x7C=1
and two signed shorts F00/F02=0, then multiply the actual
motion floats +0x50/+0x54 by the original **float PE
global 00657F74**, preserving native FLD member then
FMUL global ordering. Signed stage>4 subtracts original
drag from vertical velocity. Frame completion enters
action9.

At signed stage4/frame0, the real source sets X speed
**−3.0f**, vertical speed **9.0f** and drag **0.7f**,
prepares 00453D40(0), starts animation0x96 and executes
an actual **10-iteration native ordinary 32-bit for-loop**.
The source emits float angle **30−shot*6**, float
speed15.0f and native 00453A70 sprite
**0x346** for 261 or **0x347** for 262. The original
X parameter passes the actual **raw 32-bit float X bits**
at +0x44, while Y passes true float member+0x48 plus
original PE global **006590AC**, with real signed
facing and trailing layer1. It is a real mixed
integer/raw-X/float-Y C++ ABI, not the earlier loop's
float X calculation.

The [natural source](../probes/FighterThirdBossTenShot261262F994.inc)
needs no manual register allocation, fake locals, assembly,
unrolled byte sequences or source-only padding.

The bounded
[original PE verifier](../scripts/verify-third-fighter-ten-shot261262-f994.py)
freshly compiles two ENTIRE original-shaped PARTIAL 82KB
normal VC7.1 parent sources, tracked F993 with markers and
F994 with both genuine cases. It checks all **196 positional
original mnemonic, width and GPR operand roles**, all
**16 genuine typed PE/COFF destinations**, independently
rechecks both previous 25F/260 real cases with
**zero original wrong GPR/width/mnemonic roles and all
18 previous PE targets**, and verifies all **151
real afterRET DIR32 labels and 522 original DATA nonfields**.

| Complete original-shaped PARTIAL parent | F993 marker | F994 native source |
| --- | ---: | ---: |
| Compiled partial CODE B | 51,534 | **52,238** |
| Compiled partial x86 | 14,224 | **14,416** |
| 261 source CODE/x86 | 15/2 | **361/98** |
| 262 source CODE/x86 | 15/2 | **361/98** |
| Wrong original mnemonic/width/GPR roles | n/a | **0/0/0 both** |
| Real native 261/262 PE fields | markers | **8+8** |
| Previous native 25F/260 exact register roles | 228/228 | **228/228** |
| Partial source compiler frame | 0x370 | **0x380** |
| Whole 82KB original fighter exact | NO | **NO** |

All four sequential ten-shot cases now have **424 original
positional x86 instructions with correct mnemonic/width/GPR
roles** (228+196) and **34 real original external PE targets**.
These are positive original-source compiler geometry results,
but NOT full original machine-byte equality: the real original
actor's saved receiver, EBP offsets, full frame, many other
game cases and absolute call/jump locations remain different.

Reproduce only the affected two whole-partial-parent builds:

    scripts/repo-python scripts/verify-third-fighter-ten-shot261262-f994.py

The complete C++/OBJ/PDB, VC7.1 compiler logs and original PE
receipts are saved in ignored
.analysis/f994-third-native-proof/ and
.analysis/f994-third-261262/.

**New accepted original whole callable CODE/functions: zero.
No all-979-unit cold replay.**
