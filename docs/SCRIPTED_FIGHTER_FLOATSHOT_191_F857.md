# F857 — Original 191 stage5 signed-float shot and native Y load order

The pinned Japanese TH075 1.11 original game fighter
at 005214B0 contains 46,755 callable CODE B and
901 separately owned packed switch DATA B.
Native original 0x191 at 0052747B..00527520
is **166 complete original inner B/53 x86/
five physically typed PE global/call fields**.

The natural C++ reconstructs authentic stage0
game state +0x7C, then stage5/frame0
projectile kind 0x321. Real float X is
signed facing byte times 100, converted
through native FILD, followed by FADD
this+0x44. Original float Y must
FLD this+0x48 first and FADD real
global00659298 second: this is preserved
by an actual source left-lvalue read.
The projectile uses actual native
00453A70, then PrepareActionAt453D40(0),
followed by real getter 0040FA30 and
conditional state0 via 0040FAC0.

Five complete-parent VC7.1 source
experiments compare original signed
float X/Y order, actual stage5
guard and genuine callback placement.
A bare POS48+global instead reverses
the x87 FLD/FADD operands and loses
native instruction widths; reversing
float X likewise destroys the
original integer conversion and x87
codegen. The selected source is
**166B/53 x86**, with all original
mnemonics, sizes, real physical PE
field locations/kinds/zero-addends,
symbols and native targets correct.

The source is still NONEXACT. It
differs at **29 true original
nonrelocation GPR operand bytes**
and two genuine entire-original-giant
epilogue long-JMP relative operand
bytes +162/+163. They are never
hidden by masking relocation fields.

F857 regenerates/physically validates
the F856 parent, then cold-compiles
only the newly affected full normal
VC7.1 fighter. The entire generated
callable source grows to **25,488 B/
7,038 x86**, from F856 25,337B/
6,987 x86. Its physical verifier
rechecks eight earlier 136/186..190
GPR-affected original case sources,
twenty earlier C8..135 cases,
all native PE fields and actual
nonfield negatives, plus all five
separately owned afterRET 901B
packed switch tables.

The complete original 46B/16-x86
common getter remains **34/34 native
nonrelocation byte equal** plus all
three physical original PE REL32
calls, from genuine source context,
not forced register names.

Run only the selected affected giant:

    scripts/repo-python scripts/verify-scripted-fighter-floatshot-191-f857.py

Full current C++, VC7.1 COFF/PDB,
source alternatives and target PE
receipts are saved under ignored
.analysis/f857-scripted-191/.
The entire 46,755B original giant
remains NONEXACT. No independent
case/suffix or packed jump DATA
accepted as whole callable CODE.
No mass exact-unit cold replay.
