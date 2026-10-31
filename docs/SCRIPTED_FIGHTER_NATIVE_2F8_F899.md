# F899 — Native 2F8 full-length investigation and compiler-context correction

Pinned Japanese TH075 v1.11 original: whole 005214B0 has
46,755 callable CODE bytes and 901 separately owned afterRET
jump DATA bytes. The real physical action2F8 at
0052C4D3..0052C951 has **1,151 CODE B, 316 x86 and
28 physically typed PE relocation fields**.

In a new normal VC7.1 full-parent compile, all 316
mnemonics, the first 315 original instruction widths,
and all 28 original relocation positions, types, addends
and original PE destinations match. Native observable
integer/float conversion temporaries are retained:
EBP-0x128, -0x12C, -0x130, -0x134 and -0x138.
The original dynamic state uses a signed global byte
at 006714D0 and a genuine 16-bit threshold comparison.

The currently last source case is **1,148 B** rather
than native 1,151 B: its final original five-byte
whole-parent JMP is emitted as a two-byte JMP.
The three absent bytes are not hidden or credited.
The two nonfield differing present bytes are
case-relative +1146/+1147. The full 46,755B original
callable function therefore remains NONEXACT.

Adding this actual original 2F8 source naturally
restores the PREVIOUS 2F0 from a source-last 825 B
short-JMP form to the native **828 B /229 x86 /
19 physical PE fields**, leaving only its two
whole-parent far-JMP displacement byte differences.

The same freshly compiled full parent physically
verifies 78 earlier original source-backed case
interiors, retains honest nonexact 1FD/252/254
evidence, checks five original packed 901B afterRET
tables and the shared getter's **34/34 original
nonrelocation bytes** and three original PE fields.
Two independently compiled equal-size negative
variants with changed condition/range operands
are rejected against actual original PE bytes.

Selected affected unit only:

    scripts/repo-python scripts/verify-scripted-fighter-stage2f8-f899.py

Complete C++, VC7.1 OBJ/PDB, controls and native PE
receipts are under ignored .analysis/f899-native-2f8/.
No mass cold replay, no independent state CODE credit.
