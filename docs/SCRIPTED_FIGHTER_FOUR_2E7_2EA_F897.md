# F897 — Native 2E7..2EA four 555B states, 60 original PE fields and honest last-JMP width

The SHA-pinned original Japanese TH075 v1.11 fighter
005214B0 has 46,755 callable CODE B, plus five
separately owned afterRET packed jump DATA tables of 901B.

Original original physical states 2E7, 2E8, 2E9 and 2EA
are each **555 complete native CODE B/167 x86/
15 physically typed actual PE call/global fields**,
at 0052B8EB, 0052BB16, 0052BD41 and 0052BF6C.
Numeric successor 2EB is NOT the physical
successor of action2EA; the next real original
physical code handler is action2F0 at 0052C197.
Do not use numeric action subtraction for original extents.

The actual four native game handlers share a detailed
original staged barrage source: stage0 initializes
F00/7C and short+80=0x63, stage3 with animation frame
short+64<30 increments short+F02 and emits sprite3E
when short+F02>4, then resets counter. True
facing*65 float conversion naturally allocates four
distinct REAL live x87 FILD temp slots:
- 2E7: EBP-0x110
- 2E8: EBP-0x114
- 2E9: EBP-0x118
- 2EA: EBP-0x11C

On current native action completion, original
SetAction0 is followed by Random455580(0,60),
plus60 and minus original signed global006714D0,
storing native short+516, then whole-fighter
epilogue return. Otherwise frame0 resets dword+7C,
stage2 does two float-to-signed-short C++ conversions
whose true calls physically reach the original
006406AC __ftol2 helper, then emits native sprite33D.
Stage9 emits sprite38B in 2E7/2E8, but true sprite38C
in 2E9/2EA, and prepares action7. Stage11 initializes
true trajectory10 and emits original raw sprite7F.

The selected four-state complete VC7.1 /Od parent emits
**44,353 callable CODE B/12,556 x86**, up from F896
42,184/11,896. All FOUR new states have **167
original x86 with identical mnemonics** and
15 authentic PE field locations/types, actual native
callee/global target addresses and zero COFF addends.
A separate whole-parent false sprite test proves the
actual game sprite38C difference: sprite38B in
2E9/2EA introduces an extra true wrong native
operand byte at original case+459.

## Crucial nonexact last case

In the current four-state parent, 2E7/2E8/2E9 have
the full **555B** original geometry and only
two encompassing giant-epilogue JMP operand pairs
+268/+269,+551/+552 wrong.

2EA is the last currently restored real case in
this source parent, and the compiler naturally
relaxes its final whole-fighter epilogue jump to
a short TWO-byte JMP. The original native JMP
is FIVE bytes. Thus current source 2EA is only
**552B/167 x86**, although its preceding
166 instructions, 15 true physical PE fields,
and real FILD EBP-0x11C geometry match.
The source has a genuine nonrelocation
byte difference at +268/+269 plus nonnative
two-byte final JMP +550/+551; the missing
three original JMP bytes MUST NOT be masked
or claimed exact. This is not a native
whole-callable independent game function.

Later integrating the original physical 2F0 source
behind the four native handlers naturally extends
the jump distance and restores 2EA's native
5B near-JMP geometry. This F897 verifier
conservatively checks the state of its CURRENT
selected parent and will not credit future
improvements until independently compiled and proved.

The new same-COFF physical checker rechecks
73 preceding original source-backed game case
interiors, including honest 1FD/252/254
nonexact variants, all five packed afterRET
901B DATA tables, and the original shared
getter actual GPR byte phase/three PE calls.

Reproduce only this affected whole game giant:

    scripts/repo-python scripts/verify-scripted-fighter-four2e7-2ea-f897.py

Complete full generated VC7.1 C++/OBJ/PDB and native
original PE receipts remain under ignored
.analysis/f897-four-2e7-ea/.
No cold all-unit replay or new exact callable CODE.
