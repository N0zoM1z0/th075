# F873 — Two original 253B actor recovery states: physics before stage0 initialization

The SHA-pinned Japanese TH075 v1.11 original
fighter at 005214B0 owns 46,755 callable CODE B
and five original separately owned packed
afterRET switch tables (901 DATA B).
States 1FB at 00528634..00528730 and 1FC
at 00528731..0052882D are TWO genuinely separate
native case entrypoints, each **253 whole
interior CODE B/70 x86/six physical PE fields**.

Unlike the previous stage2 float volley pair,
both original 1FB/1FC handlers BEGIN by testing
positive POS+0x50, subtracting actual native
float global00658350 and grounding at
threshold0065782C. They only THEN evaluate
stage0/frame0, call genuine ResetAt453E20,
set short +0x80=1, dword +0x7C=0 and FLAG=0.
A separate real stage6/frame0 repeats those
three counter/flag stores without Reset.
After real getter/action0 handling,
stage6/frame0 sets POS+0x50 to native
15.0f. All stage/float operations and
native order are backed by original PE.

Five complete whole-parent pinned VC7.1
C++ source controls prove that changing
this order is NOT equivalent native CFG:
putting stage0 initialization before the
physics produces many wrong original
mnemonics/widths even though the complete
case remains 253B/70 x86.
Wrong stage6/float value also produces
genuinely wrong machine-code bytes.
Compound subtraction can compile to the
same code as explicit subtraction, so
the exact historical expression spelling
remains provisional.

The selected full affected VC7.1 parent
now emits **30,110 callable CODE B/
8,442 x86** (F872 29,634/8,306).
Each of the two 253B cases has ALL
70 genuine native mnemonic/size/offset
pairs and all six original PE field
offsets [8,27,45,92,187,211],
field kinds, zero addends, C++ symbol
roles and actual game targets.
**Each remains NONEXACT**, with 46
real original GPR operand bytes and
two native enclosing-giant final-JMP
operand bytes at case offsets249/250.
No internal case is independently
accepted as callable game CODE.

The same new whole object physically
rechecks **44 preceding original
source-backed game case interiors**,
all actual PE references and their
honest register/JMP negatives,
all five original 901B afterRET
packed switch tables and the
common 46B/16-x86 getter's
**34/34 native nonrelocation
bytes and three physical PE calls**.

Only the changed whole fighter is rebuilt:

    scripts/repo-python scripts/verify-scripted-fighter-recovery-pair-f873.py

Full regenerated C++, VC7.1 COFF/PDB,
negative source alternatives and strict
original PE receipt remain under ignored
.analysis/f873-scripted-pair1fb-1fc/.
Original whole fighter 46,755B
remains NONEXACT; no mass cold replay.
