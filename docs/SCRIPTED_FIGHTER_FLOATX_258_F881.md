# F881 — Original 258 mixed float-X/raw-Y sprite340 and true char facing

Original pinned Japanese TH075 1.11 executable
fighter at 005214B0 has **46,755 original
callable CODE B**, plus five packed original
afterRET switch DATA tables (901 separate B).

Original native action258 at 00529678..00529745
has **206 complete game interior CODE B /
60 native x86 / six physically typed PE fields**.
Its real stage0/frame0 branch resets native
motion, initializes state short +0x80=1,
dword +0x7C=1 and clears FLAG+0x3AC.
Upon native current action matching
the observed +0x70 animation, it sets
action0.

At stage2/frame0 it emits original
sprite0x340 via 00453A70. The real
callee's second argument is a float:
signed facing byte+0x66 times 80, converted
through true x87 FILD temporary EBP-0xB4,
then added to actor float X+0x44.
The third argument is raw integer
Y+0x48, not the floating Y coordinate
used in previous states. Its fourth
formal is a narrow char-equivalent
facing value. It next calls native
0046D000(0xFA) and
00453D40(5), then returns through
the enclosing giant's epilogue.

The natural normal VC7.1 source
reproduces all **206 original inner
B/60 x86**, every mnemonic/size/
instruction-relative offset and all
six original physical PE REL32
fields at offsets [26,66,90,
174,187,197], with genuine original
call targets, zero addends and
source callee identities.

A separately compiled entire
parent with a WRONG integer
fourth parameter emits
MOVSX byte->int (4B) instead
of native MOV r8 (3B).
Its complete state grows to
**207 B** despite retaining
60 x86 and six relocation
fields; F881 rejects this
as a false native C++ signature.

The new complete source parent
emits **33,796 callable CODE B/
9,510 x86** (F880 previously
33,605/9,452). Its same COFF
rechecks **57 preceding actual
original game case interiors**,
including 1FD's remaining
one-byte CMP defect and 252/254
incorrect byte-register PE field
offset shifts, all five original
901B packed afterRET tables and
the native shared 46B getter's
four genuine GPR byte negatives.

The original action258 source
still has 34 true GPR operand
byte errors plus two enclosing
whole-fighter original JMP
operand bytes at +202/+203,
so neither it nor the full
46,755B original giant is
exact. No independent case
credit is claimed.

Reproduce only this affected
complete giant:

    scripts/repo-python scripts/verify-scripted-fighter-floatx-258-f881.py

Generated entire normal VC7.1
C++, OBJ/PDB, positive/negative
controls and actual original PE
receipts remain under ignored
.analysis/f881-scripted-stage258/.
No mass cold replay.
