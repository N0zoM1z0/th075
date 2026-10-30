# F855 — Original 18B short-counter volley and native register-phase negatives

Pinned Japanese TH075 v1.11 original fighter at
005214B0 contains 46,755 callable game CODE B
and 901 separately owned packed afterRET switch
DATA bytes. Its genuine original 0x18B state
at 00527241..005273A1 is **353 complete
native inner B/99 x86/seven original physical
PE call/global fields**.

The reconstructed normal C++ preserves real
stage-zero position 10.0f and short +0xF00
counter reset, stage>6 native gravity via
00658058, original auxiliary state6 when
stage7/frame0 and the real short counter
below2, followed by genuine S16(0x80)/I32(0x7C)
native stores. At stage6/frame0 the source
emits projectile kind0x328 with float X
**signed facing*128 → integer shift → FILD,
then FADD actual X at this+0x44**.
The real float Y uses native FLD this+0x48
then FADD game global00658400. This
requires an actual Y lvalue expression,
not a bare POS48+global compiler ordering.

Five full VC7.1 source controls were built
inside the entire affected fighter: genuine
16-bit prefix increment vs ordinary short+1,
exact stage>6 vs equivalent >=7,
real x87 signed float addition order,
and normal vs lvalue Y. Incorrect
spellings change original opcode widths/
branch opcodes or introduce actual original
nonrelocation differences.

The selected complete 18B case compiles to
**353 B/99 x86**, matching every original
instruction mnemonic, size, original relative
position and all seven genuine original
PE field offsets, relocation types, zero
addends and true game call/global targets.
However **71 actual original GPR operand
bytes remain different**, including native
MOV AX/ADD AX,1 for the short timer
versus source MOV DX/ADD DX,1, and original
SHL EAX,7 versus source SHL EDX,7.
The original giant's final long JMP
contributes two further real nonrelocation
byte mismatches at 18B-relative +349/+350.
These 73 bytes are NEVER called exact or
hidden by relocation masks.

One affected full parent is freshly rebuilt
from F853 and now emits **25,135 callable
CODE B/6,925 x86**, compared with F853
24,797/6,828. The verifier also rechecks
six preceding 136/186/187/188/189/18A
complete original case PE fields and
their honest GPR negatives, and 20
earlier native C8..135 cases.
All five original packed afterRET tables
are verified from the same new COFF.

The original 46B common default/getter
still has its true saved-this EBP-0x10
and three actual original PE calls,
but four genuine GPR operand byte
differences at +10/+12/+16/+19 remain.

Selected reproduction:

    scripts/repo-python scripts/verify-scripted-fighter-volley-18b-f855.py

Current generated C++, VC7.1 COFF/PDB,
alternative source objects and real
PE evidence are saved under ignored
.analysis/f855-scripted-18b/.
The entire original 46,755-B fighter
remains NONEXACT; zero independently
accepted inner-case/whole callable
CODE, no corpus-wide cold replay.
