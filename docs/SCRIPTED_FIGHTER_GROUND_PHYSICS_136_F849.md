# F849 — Original 0x136 ground physics and remaining late GPR phase

The pinned original Japanese TH075 1.11 fighter at
005214B0 owns 46,755 callable CODE B, 13,230
original x86 and 901 separately owned packed
afterRET switch DATA B. The selected actual
native 0x136 action at 00526BE3..00526D23
is a full **321 inner CODE B/95 x86/10
original physically typed PE call/global fields**.

Normal C++ reconstructs the original stage/frame-zero
startup, falling ground subtraction via 00658058,
extra native stage>2 and position>threshold
ground correction via 0065747C, conditional
action0, and stage5 projectile kind0x33A
through 00453A70 plus animation0x1D.
These are real gameplay conditions and
resource calls, not synthetic padding or
handwritten machine bytes.

The pinned VC7.1 source compiles this complete
case to **321 B/95 x86 with every original
x86 mnemonic, instruction size, case extent
and all ten native PE relocation field
offsets/types/zero addends/target addresses**.
However the current original source is
**NOT byte exact**. At x86 ordinal70
the original reloads the receiver in ECX
and its source compiler uses EAX; this
phase shift propagates into **15 genuine
nonrelocation GPR operand bytes** at
case-relative offsets 248/252/255/260/264/
267/273/276/278/280/283/285/287/290/292.
Two more genuine native nonrelocation
bytes at offsets 317/318 are the original
complete-fighter final JMP displacement.

Ten meaningful whole-parent source expressions were
also compiled: alternate stage comparison operand
order, nesting vs short-circuit condition, explicit
compound gravity subtraction, reverse float
comparison and alternate getter/action operand
order. None naturally recovered the selected
original late GPR phase. Reverse action comparison
or ground threshold order actually introduces
further original nonfield/opcode differences.
Do not infer native register exactness from
identical instruction counts or masked PE fields.

F849 regenerates/validates the previous F847
whole fighter and cold-compiles ONE current
VC7.1 entire affected parent. Generated
callable source grows from 23,257B/6,371-x86
to **23,563 B/6,464 x86**.
It physically rechecks 20 earlier complete
original C8-D2, 12C-12F, 130/131/133
and 134/135 native cases, all source PE
relocations and genuine original displacement
negatives. All five original 901B afterRET
dense/sparse packed switch tables are
separately verified again in the new COFF.

The original 46B/16-x86 shared default/getter
retains its original three PE calls,
correct saved-this EBP-0x10 and instruction
geometry, but source GPR phase now differs
at four real nonrelocation bytes at
offsets 10/12/16/19. This is explicit
negative evidence, not accepted CODE.

Targeted reproduction:

    scripts/repo-python scripts/verify-scripted-fighter-physics-136-f849.py

Original complete C++ source, physical PE
comparisons, VC7.1 COFF/PDB and alternate
source experiments are saved under ignored
.analysis/f849-scripted-ground-136/.
The 46,755-B whole original fighter remains
NONEXACT. No independent case or separate
packed DATA earns authored whole-function
exact CODE credit. No mass cold replay.
