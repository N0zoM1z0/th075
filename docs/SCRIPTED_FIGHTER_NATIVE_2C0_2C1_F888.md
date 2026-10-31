# F888 — Native 2C0/2C1 original conditional sprite345 and complete getter GPR recovery

Pinned Japanese TH075 v1.11 executable:
original callable 005214B0 fighter owns 46,755 CODE B
and separately owned 901 afterRET packed jump DATA B.

The two original switch-state interiors are distinct:

| State | Full original CODE B | Original x86 | Original PE fields |
| --- | ---: | ---: | ---: |
| 2C0 | 288 | 85 | 11 |
| 2C1 | 276 | 81 | 11 |

Both perform native stage0 ResetAt453E20 with
short+F00=0, dword+7C=0, short+80=1.
At stage1/frame0 they invoke AnimatePush(0x28),
PrepareAction(0x17), PrepareAction(8 for 2C0,
9 for 2C1), update actual float+36C by
subtracting native global00657888 and emit
sprite0x73/0x74 via 00453C80 with integer X
and float Y+48 plus true global00657888.

The real state 2C0 sets short+F10=0x1A4
only when stage+62 > 10, BEFORE checking the
current action. The real state 2C1 instead
writes +F10=0x1A4 ONLY within the
action-matching condition.

## Real native control-flow correction

Initially a plausible full source used:
upon getter match, set action0, and *then*
unconditionally call SpawnExtraAt453B50(sprite0x345).
It generated the correct full case sizes
and original instruction widths and all
11 physical PE relocation positions.
But independent original JNE destination
inspection showed it was **functionally wrong**.

In the real original 2C0/2C1 code, the JNE after
current action mismatch jumps DIRECTLY to each
case's enclosing-giant epilogue JMP, bypassing
BOTH SetAction0 and sprite345. The corrected
normal C++ places the sprite345 invocation INSIDE
the same original if statement, preserving the
genuine original 7-argument call order and type.

The selected full VC7.1 original-source parent now
emits **37,053 callable CODE B /10,463 x86**
(F887 36,519/10,301).
Both cases have exact original 288/276B, 85/81-x86,
all original x86 opcodes/sizes/relative positions,
and ALL **22 physical original PE call/global fields**
at their native offsets/types/zero addends/destinations.
Their only nonrelocation byte differences are
the TWO authentic enclosing whole-fighter far
epilogue JMP bytes EACH: 2C0 +284/+285,
2C1 +272/+273. **No native branch or GPR
operand bytes differ in either selected inner case.**

A deliberately incorrect whole-fighter source
with unconditional sprite345 has exactly the
SAME length/opcode geometry but creates one
TRUE original wrong JNE byte at 2C0+228
and 2C1+204. The verifier compiles this
negative whole version independently and
rejects it as a nonnative gameplay source.

## Important newly observed whole-parent compiler phase

The enlarged and corrected FULL switch shifts the
normal VC7.1 compiler's GPR allocation phase in
the common original 46B getter. In earlier F887
this real native tail had four unmasked GPR
operand differences at +10/+12/+16/+19.
In the new F888 WHOLE parent, those are GONE:
**34/34 original getter nonrelocation bytes now match**,
with three actual physical PE REL32 call operands
at original offsets +4/+28/+38 verified.
Do not force old-parent negative results onto
a larger, newly compiled C++ function.

The new whole OBJ additionally physically rechecks
63 earlier original game interiors, including
the 1FD true one-byte CMP deficiency,
252/254 nonnative byte-register PE field
shifts, 2BF's two enclosing JMP differences,
and all five original afterRET packed 901B
jump tables. No independent 2C0/2C1
case or getter can earn exact callable
CODE while the original 46,755B entire
parent remains NONEXACT.

Targeted verification:

    scripts/repo-python scripts/verify-scripted-fighter-2c0-2c1-f888.py

Normal complete source C++/COFF/PDB,
positive/negative full-parent controls and
real original PE receipts remain in ignored
.analysis/f888-scripted-2c0-2c1/.
No all-unit cold replay.
