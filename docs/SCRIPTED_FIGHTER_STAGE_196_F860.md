# F860 — Actor 196 native float projectile and physical stage-3 call ordering

The pinned Japanese TH075 v1.11 original fighter
at 005214B0 owns 46,755 native callable CODE B
and five separately owned original afterRET
packed switch tables totaling 901 DATA B.
The genuine physical 0x196 handler at
00527723..005277E9 has **199 complete original
interior CODE B/60 x86/seven physically
typed original PE call/global fields**.

The normal game source initializes stage/frame-zero
counters and calls original 00453E20,
checks native 0040FA30 and conditionally resets
action0 using 0040FAC0. At **stage3/frame0**
it first calls original PrepareActionAt453D40(3),
then fires sprite **0x353** with genuine
float coordinates through 00453A70,
and finally starts animation **0xC8**
through native 0046D000. X is real facing*100
converted through FILD and added to observed
this+0x44; Y is original FLD this+0x48,
then FADD global006581DC. A true C++ Y
left-lvalue expression preserves this native
3-byte/6-byte x87 operand order.

Five complete affected-parent normal VC7.1 source
variants checked original callback ordering,
stage3 condition, float X add order and
float Y member/global evaluation. Reversing
the actual prepare/shot/animation order breaks
16 native opcode mnemonics and physical
CALL field destinations, while bare
POS48+global reverses native x87 instruction
widths. The selected source reproduces
**all original 60 mnemonic/width/offset pairs
and all seven genuine PE fields**, including
relocation kind, source symbol, zero addend and
real original native destination.

F860 checks the previous selected F859
original PE receipt, then compiles only
ONE updated entire affected VC7.1 source
parent. Generated callable code grows from
**25,972B/7,184 x86 to 26,156B/7,242 x86**.
The new 196 source still has **31 actual
nonrelocation GPR operand byte differences**,
plus two real encompassing whole-fighter
epilogue JMP displacement bytes at original
case offsets +195/+196. No short source
match is called whole exact.

The new whole object physically rechecks
eleven earlier GPR-affected 136/186..194
complete original cases and twenty earlier
C8..135 native cases, all original PE fields
and honest register/JMP negatives.
All five original 901B afterRET
packed switch tables are checked, and
the original 46B/16-x86 getter remains
correct in PE call targets and frame but
has four actual GPR nonfield byte errors
at 10/12/16/19 in this compiler context.

Targeted reproduction:

    scripts/repo-python scripts/verify-scripted-fighter-stage-196-f860.py

Generated normal C++ full parent,
pinned VC7.1 OBJ/PDB, candidate source
controls, independent actual PE comparisons
and receipt are in ignored
.analysis/f860-scripted-stage196/.
The complete original 46,755B fighter
remains NONEXACT; zero independent
case or whole callable exact CODE
accepted. No all-unit cold replay.
