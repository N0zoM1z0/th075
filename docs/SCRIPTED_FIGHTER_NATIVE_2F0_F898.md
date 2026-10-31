# F898 — Original 2F0 828B staged motion and natural repair of preceding 2EA short JMP

The pinned Japanese TH075 v1.11 original fighter 005214B0
is a **46,755-B callable whole function**, with five
separate packed afterRET switch DATA tables (901 B).
Actual original state2F0 at 0052C197..0052C4D2 owns
**828 original inner CODE B/229 x86/19 genuine physical
PE call/global fields**, not a separate callable function.

The complete normal C++ source reconstructs:
- stage0 short+F00/F02 zero, dword+7C=0, short+80=1,
  real Reset453E20
- any stage<6 increments native short+F02 and fires
  sprite3E after true >4 threshold with signed facing*40
  converted by genuine FILD scratch EBP-0x120 and float
  actor X, then resets short+F02
- stage>10 subtracts a DOUBLE qword original native
  global00657D00 from actor height, clamps against
  ground0065782C; stage7/9 modify float+1C/+20 in
  opposite directions through actual globals00658348
  and006598B8, stage9 stores height2
- stage8 has TWO original effects: prepares actionD and
  emits sprite38D at453A70; the later stage8/frame0
  branch computes signed original CloudOpponent
  byte006714D0 *30+240 into short+516, moves
  float,float,int 100/60/0 through0040FBB0,
  initializes movement/height, and emits sprite80
  using facing*150 FILD EBP-0x124 with mixed float
  actor X/raw integer Y
- native current getter completion sets action0,
  stage7/frame0 prepares actionA and sets actual
  float,float,int movement -200/60/0 with real
  four signed-byte actor flags +11..+14=-1,
  stage10 resets float movement multipliers and
  stage11 initializes original height15

One freshly compiled normal VC7.1 /Od complete father
emits **45,169 callable CODE B /12,783 x86**
(F897 previously 44,353/12,556), and the actual
2F0 source emits 229 instructions with exactly the
original opcode mnemonics/widths/relative offsets for
the first 228 original x86 instructions and all
**19 original physical PE operands**, types, zero addends,
relocation sites and original target destinations.

## Deliberately retained last-source short-JMP defect

2F0 is currently the last complete original native case
in this C++ switch parent. Its last source JMP relaxes
from original FIVE-byte far epilogue JMP to a TWO-byte
short JMP. Consequently current 2F0 source is only
**825B rather than native 828B**; its short JMP's two
wrong operand bytes at original case-relative +823/+824
are explicitly recorded. The three missing original
bytes are NOT relocation-masked, CODE-credited, or
described as a matching full handler. The enclosing
46,755B original fighter remains NONEXACT.

The same real addition naturally pushes the preceding
four source game states 2E7..2EA far enough from the
current whole epilogue to compile ALL FOUR original
555B/167-x86 near-JMP forms. In F897 the last 2EA
source only emitted 552B; that authentic short-JMP
defect is now resolved in the new F898 full COFF.
All FOUR have 15 original physically typed PE
fields each and only their genuine encompassing
parent far-epilogue JMP displacement bytes
+268/+269,+551/+552 wrong per case.

Two full-father negative source controls were compiled:
wrong first sprite3E signed-facing multiplier 41 vs
original40 (extra genuine wrong original +156),
and wrong stage8 sprite38E vs native38D (extra genuine
wrong original +432). Both generate same-sized
selected source yet differ at real original PE
opcode operand bytes.

The current father also physically rechecks 73
earlier source-backed original game inner cases,
original 1FD/252/254 honest nonexact byte/PE negatives,
all five original 901B packed afterRET DATA tables,
and the original shared 46B getter's physical
nonrelocation GPR phase and three real PE calls.

Targeted reproduction ONLY for this touched complete
game fighter:

    scripts/repo-python scripts/verify-scripted-fighter-stage2f0-f898.py

Complete normal VC7.1 C++/COFF/PDB and source
negative-control PE receipts live in ignored
.analysis/f898-native-2f0/. Do NOT replay 979 accepted
units or accept 2F0 as a complete original callable
whole function.
