# F891 — Native 2C3 small transition and whole-parent getter register phase sensitivity

Original Japanese TH075 v1.11 fighter at 005214B0 has 46,755
complete native callable CODE B plus five separate packed
afterRET jump DATA tables of 901 B. The real switch case
2C3 at 0052AD4A..0052AD8E is a complete inner
**69 native CODE B /20 x86 /four actual physical PE calls**.
It is NOT an independently callable original leaf.

The original case begins with ResetAt453E20, compares the
real GetNativeActionAt40FA30 result to observed short+0x70,
then checks real owner field dword this+0x4E0.
If that word is zero, it sets native action0;
otherwise it sets native action1.
Both paths run through the enclosing giant's actual final JMP.

The normal pinned VC7.1 source compiles this complete
case to 69 B/20 x86 with every original mnemonic,
instruction width, relative branch target and all
four genuine original PE REL32 field locations:
[4,12,48,60], true target addresses, and
zero source relocation addends.

Two complete normal VC7.1 parent negative controls
prove that inverting original +4E0 zero polarity or
using wrong field+4DC instead still yields same
69 B/20x86 but introduces genuine wrong nonrelocation
operand bytes (respectively case+40 or +35).
The correct native case has **ZERO actual register or
local branch errors**; only +65/+66 differ in the
original enclosing fighter far-epilogue JMP field.
This is not whole original function exactness.

One complete current father emits **39,366 callable
CODE B/11,087 x86**, versus previous F890 39,312/11,069.
The new object also physically rechecks **66 preceding
original switch case interiors**, including the complex
2C2 complete 2,274 B/608 x86/50 original PE fields,
the 1FD one-byte CMP width negative and the 252/254
physically shifted original PE fields, plus all five
separate original 901B afterRET packed switch tables.

## Native getter context changes

The previous normal F890 whole parent naturally
matched the shared original 46B getter at
34/34 nonrelocation bytes (all three PE fields aligned).
Adding the genuine 69B game case 2C3 changes
VC7.1 register allocation context; now the
new full parent's common getter has four true
original nonrelocation GPR mismatches at
+10/+12/+16/+19 and matches **30/34 bytes**.
This is not an acceptable reason to hide
register differences, manually patch registers,
or freeze an old compiler-context receipt.

Reproduce ONLY this affected giant:

    scripts/repo-python scripts/verify-scripted-fighter-transition2c3-f891.py

Whole normal C++, VC7.1 COFF/PDB, two false
source controls, all original PE receipts
live under ignored .analysis/f891-scripted2c3/.
The original entire 46,755B callable fighter
remains NONEXACT; no split-case exact CODE,
no all-unit cold replay.
