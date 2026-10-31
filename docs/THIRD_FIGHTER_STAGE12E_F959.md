# F959 — Native fighter 12E seven-argument spawn, 270B/82x86, plus 12C/D

Pinned original Japanese TH075 v1.11 giant fighter
**004AC040**: 82,796 original callable CODE bytes /
22,721 x86, plus 1,126 separate afterRET switch DATA bytes.
The new [tracked cumulative source](../probes/FighterWhole004AC040F959.cpp)
continues F958's whole-parent source work and remains
structurally PARTIAL and **NONEXACT** against that original
complete fighter. No internal case is an independent native
callable function.

The original real consecutive case **0x12E** is physically
**004B11E3..004B12F1**, exactly **270 original CODE B /
82 x86 /7 independently resolved typed PE external fields**.
It extends the genuine 12C and 12D actions that F958
already sourced (207B/59 x86 and 219B/61 x86, with
6+6 original PE fields).

New ordinary [12E game C++](../probes/FighterThirdBossStage12EF959.inc)
implements the original stage0/frame0 signed fall-flag
ResetAt453E20, real short +0x80 initialization and
32-bit +0x7C reset, signed positive fall motion
subtracting the genuine float at **00658058**,
the native ground clamp **0065782C** and
native GetNativeActionAt40FA30 completion action **2**.
At **stage4/frame0**, it first invokes real
PrepareActionAt453D60(**0x1D**) and then issues
a native **seven-argument effect spawn at
00453B50** of original sprite **0x333**,
with actual raw actor X/Y at +0x44/+0x48,
signed facing +0x66 and true trailing 1,0,1
arguments. The original PE source order is
preserved, with **no fake stack locals, ASM,
or target-byte copying**.

The independently reproducible
[`verify-third-fighter-stage12e-f959.py`](../scripts/verify-third-fighter-stage12e-f959.py)
freshly cold-compiles TWO complete original-shaped
natural VC7.1 partial giant sources, directly from
tracked F958 and F959 master C++ files. It
independently re-decodes the pinned original
PE, all original 12C/12D/12E x86, the actual
**19 typed zero-addend original PE/COFF
target addresses**, and every one of the
**151 physical afterRET DIR32 local labels plus
522 native nonfield DATA bytes**.

It also respects the original **absence of a
12C afterRET table entry**: that genuine original
12C start is determined from the preceding
D2's full **251B/74-x86 terminus** and real
12D following jump-table label. No artificial
case entry or truncated comparison is used.

| Complete natural partial father source | F958 source | F959 source |
| --- | ---: | ---: |
| Compiled source CODE B | 22,012 | **22,267** |
| Compiled source x86 | 5,975 | **6,055** |
| Original 12C/12D whole native interiors | 207B/59 +219B/61 | same |
| Original 12E source CODE B/x86 | 15B/2 marker | **270B/82** |
| Native 12E wrong positional mnemonic/width/GPR roles | unaligned | **0/0/0** |
| 12C/12D/12E genuine PE fields verified | 12 real, 12E stub | **19/19** |
| Original afterRET DIR32/nonfield bytes | 151/522 | **151/522** |
| Complete original 82KB callable exact | NO | **NO** |

Across all three contiguous authored native cases,
**696 internal original CODE bytes /202 native x86
have matching C++ mnemonic, width and register
roles**, with all 19 original external targets
validated. This is original GAME case evidence,
NOT an exact match for the whole 82KB native callable
function: source still uses nonnative saved-`this`
stack ownership, has many unimplemented game cases,
and does not share the original full source
relocation offsets. Do not credit these internal
source bytes as additional accepted exact coverage.

Reproduce only the affected partial giant:

    scripts/repo-python scripts/verify-third-fighter-stage12e-f959.py

Full parent C++/OBJ/PDB compiler transcripts,
original PE comparison and verified JSON remain
in ignored `.analysis/f959-third-stage12e-proof/`.
Initial complete experimental source remains
under ignored `.analysis/f958-third-stage12c/`.

**Zero newly accepted complete original functions
and CODE bytes; no 979-unit cold replay.**
