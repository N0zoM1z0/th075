# F852 — Selected original 189 x87 bounce case, source exact geometry but real GPR mismatch

The SHA-pinned Japanese TH075 v1.11 original fighter
005214B0 contains 46,755 callable native CODE B
and five separately owned packed afterRET tables
totaling 901 DATA B.

The real original 0x189 case at 00526FCA..00527146
is **381 complete original inner CODE B/107 x86/
11 physical original PE global/call fields**.
F852 sources its actual actor-specific stage0
initialization POS=12.5f and drag=0f, followed by
native ordered global-vs-member **FUCOMPP**
equality (the original TEST AH,0x44), signed
height subtraction via 0065747C, actual
POS48>ground and stage<7 gate, physics
POS54 -= POS5C and the physical x87
POS48+POS54<ground comparison.
The bounce path zeros POS48, multiplies
POS by the genuine 00657478 global and
sets auxiliary action7 before immediately
exiting the whole fighter. Stage3 sets
POS15f/vertical8.5f/drag0.85f and
prepares animation0x1D.

Seven normal C++ expression variants were compiled
inside the full current giant, including equality
versus inequality, swapping original FUCOMPP
operands, changing the float addition operand
order or comparison strictness, and compound
arithmetic assignment. The selected version
reproduces **all 107 native mnemonic/width/
instruction offset pairs**, plus **all eleven
original PE field offsets, kinds, zero addends,
actual game targets and emitted source symbols**.
Other C++ spellings change genuinely native
float order, branch grammar or width and are
not substituted merely because they are
mathematically similar.

The selected entire affected VC7.1 parent is
regenerated from a fresh F851 original physical
replay and compiled once. Its generated callable
CODE grows to **24,562 B/6,759 x86** (previous
24,196B/6,654 x86). The full original
0x189 source is still **NONEXACT**:
68 real nonrelocation GPR operand bytes
differ under the incomplete parent context,
as do two genuine original whole-giant
epilogue JMP operand bytes at native
case-relative offsets +377/+378.
Neither class of mismatch can be masked
or counted as whole original exact CODE.

The new whole object physically rechecks
the preceding 136/186/187/188 GPR
mismatch byte locations, their ten-plus
real typed PE fields, and 20 earlier
C8-D2/12C-12F/130/131/133/134/135
native complete case interiors.
The common original 46B/16-x86 default
again has **34/34 nonrelocation byte
equality plus three correct physical
original PE REL32 calls**, while all five
separately owned original 901B packed
afterRET jump DATA tables remain verified.

Selected reproducible command:

    scripts/repo-python scripts/verify-scripted-fighter-bounce-189-f852.py

Fresh entire source, compiler COFF/PDB, seven
expression-control objects and physical
native receipts are retained in ignored
.analysis/f852-scripted-189/.
The original 46,755B game function remains
NONEXACT. No independent inner case,
getter or switch DATA is accepted as
authored callable exact CODE.
No all-unit cold replay.
