# F831 — Original 0xCF fall state reintroduces native default GPR alignment

The pinned original Japanese TH075 1.11 game function at
005214B0 is 46,755 callable CODE B with 901 separate
packed after-RET switch DATA B. The F830 previous parent
added real 0xD0 with the common 46B default/getter tail
still wrong in four nonrelocation GPR operands.

F831 incorporates the preceding actual original 0xCF
falling-state source at 005260D6..00526147,
**114 native inner B /30 x86 /4 real original
zero-addend typed PE call/global fields**. Real game
behavior sets the +0x3AC falling flag, subtracts the
actual global 00657478 from height, checks a native
x87 ground threshold 0065782C, clears the flag,
then conditionally changes state via original
0040FA30/0040FAC0. This ordinary C++ shares the
source grammar of F647, but source GPR roles are
recompared independently against the selected actor:
they are NOT assumed equal to the different fighter.

F831 regenerates and physically validates F830's
selected native parent, then compiles one entire
new VC7.1 C++ translation unit with the new CF case.
Generated callable source increases **17,856 to
17,955 B** and x86 **4,760 to 4,788**, preserving
the actual original saved-this EBP-0x10, the
previous B4/B5 PE-backed cases and 901B separate
postRET switch DATA. All 30 original CF instruction
mnemonics, sizes, relative positions and four actual
native PE target fields match. Its 20 genuine
nonrelocation operand differences include real
GPR/source allocation and two encompassing parent
final-JMP bytes. It is NOT exact in the new parent.

The native source of following 0xD0 remains
195B/60-x86/6 real PE fields, but the genuine
preceding CF C++ also rotates the later D0
compiler register phase, increasing D0's authentic
unmasked byte differences from F830's four to
**39**. Do not inherit a strict D0 source match
from a shorter parent.

**Positive native-tail result:** in the new full
17,955B parent, the complete original 46B/16-x86
default/shared getter now matches **34/34 actual
nonrelocation machine bytes** (all original EBP
saved-this operands, GPR registers, branch bytes),
and its three real source REL32 call fields have
the exact physical PE destinations. This is
a natural compiler-context effect of restoring
real previous gameplay, not a manually selected
register or padded local.

Targeted reproduction:

    scripts/repo-python scripts/verify-scripted-fighter-fall-cf-f831.py

Regenerated source C++, COFF/PDB and physical PE
comparison receipts are in ignored
.analysis/f831-scripted-cf/. The original 46,755B
giant remains NONEXACT; no inner case or tail
CODE is credited as an independent whole
authored function. No mass cold replay.
