# F947 — Third original 82KB Fighter gets real 0xCF fall and 0xD0 reflect code

Pinned original Japanese TH075 v1.11 game fighter
**004AC040**: **82,796 original complete callable
CODE B /22,721 x86**, plus **1,126 independently
owned afterRET DATA B**. Existing normal VC7.1
C++ father reconstruction is structurally incomplete
and the full original game function is **NONEXACT**.

Two original handlers still appeared as 15-B/2-x86
placeholders in the prior F943 natural father:

| Original game action | Original physical PE interval | True original full action |
| --- | --- | --- |
| 0xCF | 004B0D42..004B0DB4 | **114 B /30 x86/4 genuine PE external fields** |
| 0xD0 | 004B0DB4..004B0E77 | **195 B /60 x86/6 genuine PE external fields** |

The real original CF source sets the actual
signed `this+0x3AC` facing/fall flag, subtracts
global float `00657478` from the live horizontal
float at +0x50, clamps it to zero against the
native ground float `0065782C`, and on actual
animation completion calls `0040FAC0(0)`.
The original D0 source conditionally reverses
signed facing and x87 horizontal direction,
compares real float motion drag with original
ground using the genuine x87 temporary rules,
then applies drag, ground collision, action 0xA,
frame reset and native auxiliary action 5.
Neither is a new independently callable function.

The C++ is already naturally reconstructed in
[`FighterFallStateCFF647.inc`](../probes/FighterFallStateCFF647.inc)
and [`FighterReflectLandingD0F646.inc`](../probes/FighterReflectLandingD0F646.inc).
**F947 newly verifies both source bodies in the
third original 004AC040 actor's actual parent**, not
by assuming their previous 58KB/46KB actor roles
and sizes are identical.

Tracked, bounded
[`verify-third-fighter-fall-reflect-f947.py`](../scripts/verify-third-fighter-fall-reflect-f947.py)
generates and fresh-compiles four ENTIRE
normal VC7.1 original-shaped partial C++ parents:
old two markers, CF only, D0 only and BOTH real.
The original SHA-pinned game PE independently
supplies the source-boundary mapping through
its actual 151 `DIR32` afterRET local labels,
so no subcase is disassembled as an invented
independent callable native function.

| Entire partial original-shaped parent | Prior markers | CF only | D0 only | Both |
| --- | ---: | ---: | ---: | ---: |
| Emitted complete source CODE B | 18,234 | 18,333 | 18,414 | **18,513** |
| Emitted source x86 | 4,855 | 4,883 | 4,913 | **4,941** |
| Source real CF CODE/x86 | 15/2 | 114/30 | 15/2 | **114/30** |
| Source real D0 CODE/x86 | 15/2 | 15/2 | 195/60 | **195/60** |
| Native CF/D0 mnemonic and width errors | Stub | **0/0** | **0/0** | **0/0** |
| True original CF and D0 typed PE fields | Stub | 4 | 6 | **4+6** |
| Original afterRET DIR32/nonfield DATA | 151/522 | 151/522 | 151/522 | **151/522** |
| Entire native 82KB exact | NO | NO | NO | **NO** |

The four original CF native PE targets are
two float references `00657478,0065782C`
and actual calls `0040FA30,0040FAC0`.
The six original D0 fields include two
ground-float references `0065782C`, actions
`0040FAC0,00453E20,0040FA30,0040FB40`.
All are checked by their original physical
i386 instruction ordinal and typed zero-addend
source COFF destination, NOT masked by approximate
relocation offsets. The real original D1
successor is independently checked as 199B/59
x86 on the same new father.

In the new complete-source context CF still has
**18 GPR-role differences** and D0 has **35**
although their native positional mnemonic/width
geometry and original typed PE fields match.
The source's receiver save slot is not original.
The original D2→12C switch physical boundary is
not a separate afterRET DIR32 label here:
F947 does NOT invent one or claim the missing
mapping. These cases remain internal partial
code only.

Reproduce only this partial 82KB parent:

    scripts/repo-python scripts/verify-third-fighter-fall-reflect-f947.py

All complete parent C++/OBJ/PDB, compiler logs
and original PE JSON receipt retained in ignored
`.analysis/f947-third-giant-fall-reflect/`;
initial independent six-control trial results
are under ignored `.analysis/f947-third-fall-reflect/`.

**0 new accepted original whole callable
functions, 0 credited CODE B; NO complete
979-unit cold replay or target EXE edits.**
