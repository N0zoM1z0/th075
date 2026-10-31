# F892 — Complete native 2DB 556B: borrowed-owner distance and guarded random selection

Pinned Japanese TH075 v1.11 original fighter 005214B0
owns 46,755 callable native CODE B and 901
independently owned packed afterRET jump DATA B.
Original state 2DB at 0052AD8F..0052AFBA
has **556 complete inner native CODE B/
162 x86/13 original physical PE call/data fields**.

Actual stage0 sets dword+0x7C=0,
short+0x80=1, short+0xF00/+F02/+F04=0,
and calls genuine ResetAt453E20.

For stage 2..9, the source compares
the **absolute value of (borrowed owner's
float X+44 minus current actor float X+44)**
to original global0065787C. The native
original float helper is physically 00412D90;
the borrowed real owner and current actor
X left-values must both be used explicitly.
The correct ordinary C++ yields the
original MOV owner, MOV current actor,
FLD owner, FSUB current actor opcode
order. Earlier equivalent-looking
source returned the right arithmetic
but moved the second MOV AFTER FLD.

If distance is strictly below the
original threshold, the code invokes
auxiliary action10 and **returns through
the original whole fighter's epilogue**.

After stage>15 height correction by genuine
global00657F74 and ground0065782C, the
current native action completion condition
sets native action0 and chooses a random
range 30..60 through genuine
00455580, then writes actual short+0x516.
**This random call and store are INSIDE
the animation completion condition.**
A previous unconditional C++ source preserved
556B/162x86 but wrongly executed random
selection when current action did not
complete, and its JNE target byte differed.

Stage2 sets height12.5; stage10 has
a once-only native 16-bit +F00
increment and auxiliary action2.
Stage15 emits native sprite0x80
with signed facing*100 FILD scratch
EBP-0x108, mixed float X/raw integer Y,
then sprite0x336 with native integer X/Y,
and prepares action2. Stage16 sets
original height17.5.

The selected full pinned normal VC7.1
parent now emits **39,907 callable
CODE B/11,247 x86** (F891 39,366/
11,087), and the entire 2DB source
has **556B/162 x86** with matching
all native opcode/size/relative
instruction positions and all
13 original PE field offsets:
[84,135,144,161,190,208,233,
257,269,384,468,504,514],
including exact physically resolved
real original call targets/types,
zero addends and C++ symbol roles.

Two false but equal-size full-fighter
C++ source controls were independently
compiled and rejected: wrong actual
borrowed float X evaluation order, and
wrongly unguarded random selection.
The correct selected 2DB case has
**zero genuine GPR and internal branch
nonrelocation byte errors**; its only
original differences are the two
enclosing 46KB father far-epilogue
JMP operand pairs +166/+167 and
+552/+553. This internal case is
NOT an independent callable exact
game function.

The same one newly compiled
whole father also physically checks
all 67 previously original PE-backed
state source interiors (including
2C2 2274B, 2C3, 1FD one-byte
CMP negative, 252/254 shifted
PE operand fields), five original
packed 901B jump DATA tables
and the original shared 46B getter
34/34 native nonrelocation bytes
with three real PE calls.

Targeted reproduction only:

    scripts/repo-python scripts/verify-scripted-fighter-stage2db-f892.py

Current full C++, normal VC7.1 COFF/PDB,
alternate complete sources and strict
original PE receipts are in ignored
.analysis/f892-scripted2db/.
Original whole 46,755B callable fighter
still NONEXACT; zero new accepted
whole game CODE and no all-unit cold replay.
