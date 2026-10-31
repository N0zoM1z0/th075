# F970 — Third original fighter 194 and 195: two 644-byte native volleys

The SHA-pinned Japanese TH075 v1.11 original
game fighter at **004AC040** has **82,796 whole
callable original CODE B/22,721 x86**, with
**1,126 separately owned afterRET jump DATA B**.
The new [cumulative normal VC7.1 C++ parent](../probes/FighterWhole004AC040F970.cpp)
remains a PARTIAL reconstruction of that entire
original function; original full stack frame,
saved-`this` EBP, many game cases and PE
relocation positions are not recovered.
The entire original fighter is **NONEXACT**.

Both real original actions have 644 original
CODE bytes and 168 x86 instructions:

| Native handler | Physical original executable interval | Original CODE/x86 | Real original PE external fields |
| --- | --- | ---: | ---: |
| **194** | **004B28ED..004B2B71** | **644B/168** | **11** |
| **195** | **004B2B71..004B2DF5** | **644B/168** | **11** |
| Both genuine cases | consecutive | **1,288B/336** | **22** |

The native cases are **not** identical to
older other-fighter eight-shot source.
They initialize the actual +0x7C=1,
signed short +0xF00 and +0xF02=0,
but do **NOT** invoke ResetAt453E20
at state start. With real signed stage
greater than 4, F00 not positive and
F02 less than 5, they call
`00453D40(0)` and animation
`0046D000(0x28)`, then execute
**three genuine separate projectile
calls at 00453A70(0x320)**.

The original action-specific angle
values written as signed-int-converted
float at +0x314 are:

- Native **194**: `F02*4−8`, `F02*4−4`, `F02*4−12`.
- Native **195**: `F02*4−45`, `F02*4−41`, `F02*4−49`.

Both store +0x318=7.0f per shot,
pass the actual raw int bits of
X at +0x44, float Y calculated as
`this+0x48 + original PE global 006590AC`,
signed facing at +0x66 and trailing
layer 1; then update the two real
short counters by F00=2, F02++,
F00--. Native vertical speed subtracts
the observed drag. On frame completion
they transition to action **9**.
Stage4/frame0 fires a distinct
sprite **0x335** call with actual raw
int X/Y, stage5/frame0 writes real
X=−6.0f, vertical velocity=9.0f
and drag=0.7f.

The [new normal C++ source](../probes/FighterThirdBossStages194195F970.inc)
preserves the actual integer/raw-X
versus float-Y calling convention and
three **separate** original projectile
calls. It does not use assembly,
original machine-code bytes,
fake register locals, forced padding,
or source-only split cases.

The targeted
[`verify-third-fighter-stages194195-f970.py`](../scripts/verify-third-fighter-stages194195-f970.py)
fresh-builds the two ENTIRE
original-shaped partial parent
sources: tracked F969 prior
194/195 markers versus tracked
F970 real native gameplay. It
independently decodes the pinned
Japanese original PE, checks all
168+168 ordered x86 mnemonic/
width roles and all **22 actual
zero-addend typed original
PE/COFF external targets**.
The preceding genuine 192
732B/177x86/11 fields and
the entire **151 original
afterRET local DIR32 entries
plus 522 native nonfield DATA
bytes** are rechecked in the
same complete parent builds.

| Full original-shaped partial father | F969 markers | F970 real 194/195 |
| --- | ---: | ---: |
| Source emitted CODE B | 27,610 | **28,868** |
| Source emitted x86 | 7,578 | **7,910** |
| Original 194 source B/x86 | 15/2 | **644/168** |
| Original 195 source B/x86 | 15/2 | **644/168** |
| Original 194/195 wrong mnemonics | n/a | **0/0** |
| Original 194/195 wrong widths | n/a | **0/0** |
| Original 194/195 GPR-role differences | n/a | **118/118** |
| Original PE fields validated | markers | **11+11** |
| Original afterRET DIR32/nonfield | 151/522 | **151/522** |
| Complete original 82KB fighter exact | NO | **NO** |

Unlike the preceding original
190/191, these 194/195 cases
already compile to the same total
CODE byte lengths as their original
native interiors. But their actual
original integer→x87 scratch EBP
displacements and GPR roles
are still different from the
partially generated father.
**Source length and x86 width
equality cannot establish
original complete-function
byte-for-byte exactness.**

The selected tracked whole C++
source was also independently
compiled in expanded form;
its emitted CODE+afterRET bytes
and physical COFF offset/type/
local-target positions are
identical to the tracked source
object. Internal compiler
`$L` symbol identifiers may
differ after source regrouping.

Reproduce only the touched giant:

    scripts/repo-python scripts/verify-third-fighter-stages194195-f970.py

All original-shaped complete
C++/OBJ/PDB, pinned original PE
receipt and VC7.1 compiler logs
are preserved in ignored
`.analysis/f970-third-native-proof/`
and `.analysis/f970-third-194195/`.

**No accepted new original complete
callable functions or CODE B; no
all-979-unit cold replay.**
