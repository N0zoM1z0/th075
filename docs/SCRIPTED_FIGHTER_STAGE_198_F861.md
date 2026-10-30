# F861 — First genuinely separate state from the original 980B dispatch region

The pinned Japanese TH075 v1.11 original game fighter
at 005214B0 has 46,755 callable native CODE B and
five separately owned packed afterRET switch tables
of 901 DATA B.

**Original mapping correction:** the native interval
5277EA..527BBD contains FIVE distinct switch
states 198,19A,19C,19E,1A0; it must NOT be
treated as one 980B state. The first genuine
original 0x198 handler is 5277EA..5278B0:
**199 entire native interior CODE B/60 x86/
seven real PE call/global fields**.

Selected actor198 normal C++ has original transition
action2, stage4 source PrepareActionAt453D40(3),
followed by native projectile kind **0x351**
through 00453A70, then animation **0xC8**
through original 0046D000. Real float X is
signed facing*90 FILD then FADD this+0x44,
while Y is the native lvalue FLD this+0x48,
followed by FADD global00659460.

Five whole-parent C++ candidates test wrong
sibling parameters, stage, projectile kind,
facing multiplier and bare versus authentic
Y lvalue. The selected C++ generates
**199B/60 x86**, every original x86
mnemonic/size/location and all seven true
physical native PE fields (types, offset,
zero source addends, symbols and actual
original call/global destinations).
Other candidates retain some length
similarity but have genuinely wrong
machine bytes/float operand widths.

F861 starts from an already verified F860
whole source, then compiles ONE updated
entire VC7.1 fighter. It grows to
**26,340 callable CODE B/7,300 x86**
(previous 26,156B/7,242 x86).
The real original interior remains
**NONEXACT** with 31 genuine GPR operand
byte differences plus two actual enclosing
complete-fighter final-JMP relative
bytes at original case offsets 195/196.
No artificial registers/locals were added,
and no negative bytes are hidden.

Every one of twelve previous GPR-affected
136/186..196 native whole case interiors
and twenty earlier C8..135 original cases
are physically rechecked in the NEW
complete COFF along with all original
typed PE fields and honest byte negatives.
The 46B/16-x86 shared original getter
naturally returns to **34/34 original
nonrelocation bytes equal** plus its
three physical PE REL32 call targets.
All FIVE original packed 901B afterRET
switch tables are independently reverified.

Reproduce only this affected original giant:

    scripts/repo-python scripts/verify-scripted-fighter-stage-198-f861.py

Full generated current C++, VC7.1 COFF/PDB,
five whole-parent source controls, real
native PE comparisons and the strict
verified receipt are in ignored
.analysis/f861-scripted-stage198/.
The full 46,755B original function
still NONEXACT. No independent
inner state, getter or separate switch
DATA receives whole callable CODE credit.
No all-unit cold replay.
