# F844 — Original native stage 0x130 202B grounded recovery in the giant fighter

The pinned Japanese TH075 v1.11 005214B0 fighter is
46,755 original callable CODE bytes/13,230 native x86
with five independently owned packed afterRET dispatch
tables totaling 901 separate DATA bytes.

F844 extends the full source with the physical original
0x130 case at 00526715..005267DE, **202 complete native
inner B/58 x86/5 physically typed original PE fields**.
This genuine case has real horizontal/vertical/drag
collision handling: it first subtracts POS5C from POS54,
computes **POS48+POS54** in that precise native x87
order, and conditionally sets action0xA and clears
POS48, POS5C, then POS54 in their original order.
The stage-zero setup uses real short +0x80 and
word +0x7C, native getter/action9, and prepares
animation **0x1C at stage3**.

Four full-parent C++ source alternatives test the
physical operand-order, three actual reset stores
and true stage guard. Every candidate preserves a
202-B/58-x86/5-PE-field original-sized source
interior, but the three incorrect alternatives
introduce genuine nonrelocation native mismatches
at x87/source operand or condition/store bytes.
The selected natural C++ has every original
x86 mnemonic, size, GPR/x87 operand, position
and PE field matching except **four genuine
unrelocated byte differences at +84/+85 and
+198/+199**, the two original entire-fighter
epilogue long-JMP displacement pairs.
Those bytes are not masked or accepted as exact.

The tracked verifier first regenerates/validates the
immediate F843 selected whole-parent source, then
compiles only the new affected entire VC7.1
translation unit. Current source grows from F843
22,102 B/6,023 x86 to **22,289 callable CODE B/
6,079 x86**. Its actual native saved receiver
remains EBP-0x10, and all five original call/global
PE fields are independently rechecked by physical
original instruction ordinal, relocation type,
zero addend and true destination.

The new COFF independently rechecks all four previous
12C/12D/12E/12F complete original state interiors
and eleven earlier C8..D2 case extents and true PE
relocation targets. All five genuine original
901B afterRET dense/sparse jump tables are
physically verified, not just size-matched.

The 46B original default/getter still has the
genuine original saved-this geometry and all
three true PE calls, with **four actual non-PE
GPR operand bytes** wrong at +10/+12/+16/+19
in this new parent. These are not hidden.

Targeted reproduction:

    scripts/repo-python scripts/verify-scripted-fighter-grounded-130-f844.py

Actual sources, VC7.1 OBJ/PDB, alternative
whole-source compiler experiments and physical
PE verification receipts are in ignored
.analysis/f844-scripted-stage130/.
The entire 46,755-B original callable game giant
remains NONEXACT; no standalone case or packed
jump DATA is credited as independently callable
authored exact CODE. No all-units cold replay.
