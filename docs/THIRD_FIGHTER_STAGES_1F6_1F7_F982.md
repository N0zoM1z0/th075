# F982 — Two original double-scaled 777-byte fighter actions 1F6/1F7

The pinned Japanese TH075 v1.11 original fighter 004AC040
has **82,796 complete callable CODE B /22,721 x86**
and **1,126 separately owned afterRET jump DATA B**.
The [tracked cumulative original-shaped C++ parent](../probes/FighterWhole004AC040F982.cpp)
is a **PARTIAL original fighter**, not byte-exact: original
0x720 stack frame, saved receiver EBP−0x64, GPR allocation
and many game actions remain unimplemented or different.

| Original handler | Physical native executable interval | Original CODE/x86 | Original PE fields |
| --- | --- | ---: | ---: |
| **1F6** | 004B5463..004B576C | **777 B/215** | **22** |
| **1F7** | 004B576C..004B5A75 | **777 B/215** | **22** |

The original 1F6 and 1F7 are NOT direct copies of
the earlier 1F4/1F5 states. Original stage0/frame0
first scales real fighter motion floats +0x50/+0x54 by
a **double-precision global**, using actual original
FLD float member / **FMUL QWORD** instructions:

- **1F6:** original double global at **006583E0**.
- **1F7:** independently observed double global at **006584C8**.

The native initializes short +0x80=99, +0x7C=0,
signed fall flag+0x3AC and shorts+0xF00/F02.
On actual stages **greater than 3 and less than 6**,
it subtracts native drag from vertical speed and
does genuine Y/ground contact detection, ResetAt453E20,
auxiliary action **6** and Y reset on collision.
Its real short F02 counter resets after 6 if +0x7C
is nonzero; animation completion triggers action0.

At **stage2/frame0**, unlike 1F4/1F5's stage8,
the original emits two genuine **0x32A/0x329 pairs**,
using float +0x314/0x318/0x31C groups (15,−20,−60
then 10,−135,−30) and Y global **00659270**,
before native PrepareActionAt453D40(3).
At stage4/frame0, genuine F00 limited auxiliary action2
uses **F00 less than 2** for 1F6 and **less than 4**
for 1F7. Stage6/frame0 invokes auxiliary action5.

The [actual natural C++ source](../probes/FighterThirdBossStages1F61F7F982.inc)
uses declaration-only double globals, honest native receiver
fields and actual call ordering; no assembly, fake padding,
artificial register variables or original-byte grafts.

The [bounded verifier](../scripts/verify-third-fighter-stages1f6-1f7-f982.py)
cold-builds TWO ENTIRE original-shaped PARTIAL normal VC7.1
fathers, tracked F981 markers and selected F982 real source.
It independently compares pinned original complete 82KB PE
and both case extents, **430 ordered native mnemonic/width
positions**, all **44 zero-addend actual typed original
PE/COFF destinations**, previous native 1F5 and the original
**151 afterRET DIR32 local labels and 522 nonfield DATA bytes**.

| Whole partial father | Previous F981 | Selected F982 |
| --- | ---: | ---: |
| Compiled source CODE B | 38,501 | **40,025** |
| Source x86 | 10,553 | **10,979** |
| Source 1F6 B/x86 | 15/2 | **777/215** |
| Source 1F7 B/x86 | 15/2 | **777/215** |
| Original wrong mnemonics/widths | n/a | **0/0 both** |
| Original GPR-role mismatches | n/a | **126/126** |
| Original PE target fields verified | markers | **22+22** |
| Entire original 82KB callable exact | NO | **NO** |

Matching inner case lengths, opcode types and relocation destinations
is meaningful source reconstruction, **not** acceptance of the
incomplete entire native game function. The original whole receiver,
frame, registers, jumps and many additional game actions still differ.

Reproduce only affected full-partial original-shaped parents:

    scripts/repo-python scripts/verify-third-fighter-stages1f6-1f7-f982.py

Private C++/OBJ/PDB, serial compiler transcripts and original PE
verification are preserved under .analysis/f982-third-original-proof/.
**Zero new accepted original whole CODE; no all-979-unit cold replay.**
