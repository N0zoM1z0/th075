# F896 — Two native original 2E5/2E6 random-action and stage-trigger handlers

The Japanese TH075 v1.11 original fighter 005214B0 owns
46,755 callable CODE B plus five independently owned
afterRET jump DATA tables (901 separate B).

Two physically adjacent original real switch state handlers:
- 2E5 at 0052B5FF..0052B774, 374 complete native CODE B,
  102 original x86, 12 physically typed real PE fields
- 2E6 at 0052B775..0052B8EA, 374 complete native CODE B,
  102 original x86, 12 physically typed real PE fields

Both really reset the short+F00 counter, dword+7C=0
and short+80=1 at stage0/frame0, then subtract
float00657478 from height and clamp against
ground global0065782C.

On current native GetNativeActionAt40FA30 completion,
both call original RandomBoundaryAt455580(0,100),
storing short+F00. When current original dword+7C
is zero, they set action0, call genuine
RandomBoundaryAt455580(60,120), write short+516,
and return through enclosing-giant original epilogue.
When +7C is nonzero, their action cascade depends
on the two real short+F00 strict thresholds:
- random F00<30: original 2E5 sets action2E6,
  original 2E6 instead sets action2E5
- random F00<60: BOTH set action2E7
- otherwise: BOTH set action2E8

The final independent sprite branch is stage2/frame0
for 2E5 and stage3/frame0 for 2E6. It sets height15,
prepares native action7 and emits original sprite38E
at 453A70 with genuinely integer X, float Y+native
global657888, and narrow direction.

The new normal VC7.1 whole fighter emits
**42,184 callable CODE B /11,896 x86**
(F895 41,466/11,696). Both complete new source
cases have all original 374 B/102 x86, instruction
mnemonics, widths and relative positions,
each with **12 genuine original PE call/global
fields** at source-original identical offsets
[64,82,107,137,166,178,221,254,272,320,341,365].
All original typed PE source symbol identities,
zero addends and original executable destinations
are checked.

Each 2E5/2E6 native interior has ZERO unmasked
register/local-branch byte errors. The ONLY
ten source/native differing bytes are case-relative
+193/+194,+226/+227,+259/+260,+277/+278,+370/+371,
all genuinely belonging to original shared
46,755B enclosing-fighter epilogue JMPs
at native x86 ordinals52,60,68,72,101.
The five original far JMPs are produced naturally
by five corresponding C++ returns, rather than
hand-authored or cropped matching source.

Three independently compiled false whole-fighter
source control families (six resulting wrong cases)
also produce 374B/102x86/12 PE fields but change
one additional real original nonfield operand byte:
wrong low-random destination action at +213,
inclusive random threshold instead of strict <30 at
+210, or wrong animation trigger stage at +290.
Each case is physically rejected.

The same full new VC7.1 object rechecks all
**71 preceding original native game state interiors**,
including F895's 2E4, 2C2 entire 2274B/50 fields,
the 1FD genuine one-byte CMP negative and 252/254
actual shifted PE reference locations, all five
original packed 901B afterRET tables and native
46B shared getter. Current F896 getter still
has FOUR honest nonrelocation GPR source bytes wrong
at +10,+12,+16,+19 (30/34 equal).

Reproduce only the affected whole game fighter:

    scripts/repo-python scripts/verify-scripted-fighter-pair2e5-2e6-f896.py

Complete current normal C++/VC7.1 OBJ/PDB,
three alternative full source families and
pinned-original PE/COFF receipts are in ignored
.analysis/f896-paired-2e5-2e6/.
The 46,755B whole fighter is NONEXACT.
Neither internal state can count as
an independent exact callable original function;
no all-unit cold replay.
