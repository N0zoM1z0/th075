# F966 — Authentic third-fighter 188/189, native floating equality and recovery

Pinned Japanese TH075 v1.11 original fighter
**004AC040** is **82,796 whole callable CODE B /
22,721 x86**, followed by **1,126 separately
owned afterRET DATA B**. The tracked cumulative
[normal VC7.1 partial source](../probes/FighterWhole004AC040F966.cpp)
is still incomplete and NONEXACT against the original
82KB whole game function.

Independently observed original PE action extents:

| Actual original handler | Original physical interval | Entire original internal CODE | Original PE targets |
| --- | --- | ---: | ---: |
| **188** | **004B1F1D..004B2091** | **372 B /106 x86** | **11** |
| **189** | **004B2091..004B2167** | **214 B /61 x86** | **6** |
| **Both** | consecutive | **586 B /167 x86** | **17** |

Both previously were 15-B/two-instruction
source placeholders. Their real natural
C++ is tracked in
[`FighterThirdBossStages188189F966.inc`](../probes/FighterThirdBossStages188189F966.inc).

The original native 188 retains an actual
**float equality** contact test: original
`FLD 0065782C; FLD this+0x48; FUCOMPP;
FNSTSW AX; TEST AH,44h; JP`, just as
the physical game PE demands. When
positive height indicates flight it
subtracts original drag from Y velocity
and on real ground collision calls
ResetAt453E20, clears the actual +0x48
and invokes original auxiliary action
**0xC**. It also contains a physically
observable, logically unusual nested
original check: inside genuine
**stage6/frame0**, the emitted code
checks **stage4/frame0** before
PrepareActionAt453D60(0x1C), then
writes X=10.0f, velocity=12.5f,
drag=1.0f. No seemingly redundant
original conditional was silently deleted.

Original 189 uses genuine
stage0/frame0 native initialization,
signed stage-positive position decrement
using original **00658058**, ground
clamp **0065782C**, native frame
getter/setter **0040FA30/0040FAC0(2)**
and real stage4/frame0 prepare
**00453D60(0x1C)**. It is distinct
from similarly named older 58KB
and 46KB original game fighters.

The independently reproducible bounded
[`verify-third-fighter-stages188189-f966.py`](../scripts/verify-third-fighter-stages188189-f966.py)
compiles two ENTIRE original-shaped
partial giant normal VC7.1 parents:
tracked F965 markers versus tracked
F966 real 188/189. It verifies all
ordered original x86, every one of
the **17 original typed PE-targeted
external fields**, the unchanged
preceding original 187, and complete
**151 original afterRET local DIR32
labels and 522 nonfield DATA bytes**.

| Cumulative original-shaped partial source | F965 prior | F966 selected |
| --- | ---: | ---: |
| Compiled source CODE B | 25,242 | **25,798** |
| Emitted x86 instructions | 6,950 | **7,113** |
| Real 188 source B/x86 | 15/2 | **372/106** |
| Real 189 source B/x86 | 15/2 | **214/61** |
| Original 188/189 mnemonic/width differences | unaligned | **0/0** |
| Original 188/189 GPR-role differences | unaligned | **63/38** |
| Actual PE external fields checked | markers | **11+6** |
| Original afterRET DIR32/nonfield DATA | 151/522 | **151/522** |
| Entire 82KB original fighter exact | NO | **NO** |

The two selected full parent outputs have
identical generated CODE+afterRET DATA
machine bytes and physical relocation
type/offset/target sites to the earlier
independently expanded complete C++
experiment, although compiler internal
local label names may be renumbered.
**Matching native mnemonic and width
sequences is not byte-exact original
CODE when GPR roles, saved-`this` EBP,
parent function control flow and absolute
PE/COFF field positions still differ**.
No original function was cropped into
an invented independent exact callable.

Reproduce ONLY the affected original-
shaped giant builds:

    scripts/repo-python scripts/verify-third-fighter-stages188189-f966.py

Compiled source/OBJ/PDB, pinned original
PE comparison and VC7.1 build transcripts
are preserved in ignored
`.analysis/f966-third-original-proof/`
and `.analysis/f966-third-188-189/`.

**No newly accepted native whole
game function or CODE B. No 979-unit
cold replay.**
