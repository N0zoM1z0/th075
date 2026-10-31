# F894 — Native 2DD true physical 535B extent and EAX random-return FILD

The pinned Japanese original TH075 v1.11 executable's
fighter at 005214B0 owns 46,755 callable original CODE B,
plus five separately owned packed afterRET switch DATA
tables totaling 901 B.

The original sparse switch dispatcher maps numeric action
2DD to 0052B24F, but the numeric successor 2DE points to
the shared DEFAULT handler at 0052CB25. A naive subtraction
therefore wrongly assigns **6,358 CODE B** to action2DD.
Independently scanning all original physical switch handler
starts shows the actual NEXT physical code entry is
**action2E4 at 0052B466**. Therefore native 2DD is
**0052B24F..0052B465, 535 complete inner CODE B /
153 x86 /14 genuine original PE call/global fields**.

This is still a switch interior of ONE 46,755B
callable fighter, not an independently callable leaf.

The real stage0 resets F00/F02/F04; stage2 sets
motion+7C=0, short+80=1, height10 and speed0.
When original Y+48 is positive and stage<26, it
subtracts true native float global00659090 from
vertical impulse+54, then tests whether
Y+verticalImpulse is <= ground0065782C.
That contact path invokes actual native aux26,
zeros height/speed/Y, and exits through
the enclosing giant's original far epilogue.

After native current-action completion it
calls true RandomBoundaryAt455580(0,60)
and stores short+516 INSIDE the matched action guard.

Stage3 fires sprite7F at original native 00453C80,
calls RandomBoundaryAt455580(0,6), converts
its returned integer to a float through original
**FILD EBP-0x10C**, adds genuine original
float global006592A0, stores height+50,
sets vertical speed16 and resets actor motion.
Stage18 fires sprite335 through 00453A70
and prepares animation4. Stage26 invokes aux24.

## Actual native ABI correction

The borrowed game method 00455580 was previously
declared as returning short to store its value into
short+516 in the preceding 2DB/2DC states.
However, the physical original 2DD code demonstrates
the true return carrier must be the full **32-bit EAX**.
The correct normal VC7.1 C++ method return is int.
It directly stores EAX into EBP-0x10C and FILDs it,
exactly like the original.

An independently compiled WRONG full-parent source
retaining short return generates an additional
MOVSX AX->EAX; its complete original-shaped 2DD
interior becomes **538B/154 x86**, not native
535B/153 x86. The tracked verifier requires that
this false complete source is rejected, and
rechecks previous 2DB/2DC original sources under
the repaired return-type declaration.

A new normal pinned VC7.1 whole fighter generates
**41,072 callable CODE B/11,584 x86**
(F893 previously 40,552/11,433). Its
535B 2DD state matches all 153 original
x86 mnemonic/width/position pairs,
and all **14 physical original PE fields** at
[26,139,170,194,211,254,278,290,356,
368,386,483,493,526], including their
native call/global targets, types and zero addends.

Only four authentic original whole-giant
far epilogue JMP operand bytes at case-relative
+246/+247,+531/+532 remain different;
zero internal GPR or branch operand bytes differ.

The new whole parent physically rechecks
all **69 preceding actual source-backed
original native case interiors**, including
2C2 2274B/50 refs, 2DB and 2DC,
the 1FD one-byte CMP defect and 252/254
one-byte shifted original PE fields.
All five original 901B packed afterRET
tables and the original shared 46B getter's
four genuine current whole-parent GPR operand
errors +10/+12/+16/+19 are also checked.

Targeted verification ONLY for this affected
whole fighter:

    scripts/repo-python scripts/verify-scripted-fighter-physical2dd-f894.py

Generated complete normal C++, VC7.1 COFF/PDB,
full-source negative controls and strict physical
Japanese original PE receipts remain in ignored
.analysis/f894-scripted2dd/.

The full original fighter 46,755B remains
NONEXACT; no independent inner case or
afterRET DATA receives callable exact CODE credit.
No all-unit cold replay.
