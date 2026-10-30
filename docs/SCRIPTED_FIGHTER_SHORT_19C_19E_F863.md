# F863 — Two separate native 122B fighter game states, not independent small functions

The pinned original Japanese TH075 v1.11 fighter
at 005214B0 owns 46,755 callable native CODE B
and five separately owned afterRET packed switch
DATA tables occupying 901B. Original game switch
actions 19C at 005279DF..00527A58 and 19E
at 00527A59..00527AD2 are TWO individually
bounded physical states, each **122 complete
native CODE B/35 x86/three PE REL32 calls**.

Ordinary C++ models the actual stage/frame-zero
owner setup +0x80=1 and +0x7C=0, real
ResetAt453E20, getter GetNativeActionAt40FA30
and conditional state0 through native
SetNativeActionAt40FAC0. At true stage4/frame0
the source updates +0x7C to 1.
Both native original states share this
game behavior but differ in original
compiler GPR phase.

Three complete affected whole-parent
VC7.1 variants test authentic stage4,
incorrect stage3, real action0 versus
incorrect action2. The selected sources
each reproduce all native 35 mnemonic/
width/position pairs and three genuine
original PE call field locations, kinds,
zero addends and destinations.
In this incomplete whole compiler context,
each full case still differs at
**22 true GPR operand bytes and two
genuine original enclosing giant epilogue
JMP bytes** at relative +118/+119.
No case is accepted as a separate
original callable function.

The newly compiled entire VC7.1 parent
grows from F862 26,627B/7,384 x86 to
**26,841 callable CODE B/7,450 x86**.
F863 freshly rechecks all FOURTEEN
preceding 136..19A source-backed
GPR-affected original cases and
TWENTY older C8..135 original
game state interiors with every
real original physical PE reference.
The common original 46B/16-x86
getter retains **34/34 native
nonrelocation bytes equal** and
three actual PE REL32 calls.
All five separately owned original
901B packed afterRET tables
are independently revalidated.

Only the affected giant is rebuilt:

    scripts/repo-python scripts/verify-scripted-fighter-short-19c19e-f863.py

Current complete C++, original target
PE receipt, pinned VC7.1 COFF/PDB
and incorrect stage/action variants
are saved in ignored
.analysis/f863-scripted-19c19e/.
The original entire 46,755B fighter
remains NONEXACT. No independent
small-function or switch DATA CODE
credit, no mass cold replay.
