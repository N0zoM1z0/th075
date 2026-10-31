# F1008 — Native 2F9 randomized volleys recover following 2FA GPR phase

The pinned Japanese TH075 v1.11 original fighter 004AC040
owns **82,796 original callable CODE B/22,721 x86** plus
**1,126 owned afterRET jump DATA bytes**.
The [tracked cumulative normal VC7.1 C++](../probes/FighterWhole004AC040F1008.cpp)
remains a PARTIAL 82KB original-shaped father, not
complete byte-exact game CODE.

Physical original action2F9 occupies **004BEC88..004BF16E**:
**1,254 original CODE B/326 native x86/33 genuine typed
zero-addend PE target fields**. The original stage0 resets
shorts F00/F02, draws signed short F04 from Rand(0,3),
F06 from Rand(0,100), clears int+0x7C, calls ResetAt453E20
and sets short+0x80=99.

At frame0/stage9 or stage10 it emits original sprite
**0x38B** with real signed facing, randomized Y from
Rand(0,200) and an additional +200 iff signed F06>50.
Its X uses actor X+0x44 plus native PE world center
**006593D0**, minus a separate Rand(0,480), computed
through true native x87 **FILD/FSUBR** temporary geometry.
When original signed mode global **006714D0**>0 it
emits a second 0x38B, with independent Y random(0,250)
plus +250 iff F06>50, world center **00658370**,
minus Rand(0,560). Stage9/frame0 and mode>1 adds
real seven-argument sprite **0x38A** using the first
center/ranges; stage10/frame0 and mode>2 adds another
using the second. These are genuine distinct native calls
with three trailing flags after signed facing, not four.
The first normal VC7.1 probe diagnosed this actual ABI
parameter error before any source was accepted.

Original completion uses 0040FA30/0040FAC0(0),
then stores short+0x516 = 180 − signed mode×20.
At stage5/frame0 it invokes auxiliary3 up to F02<3;
afterward it prepares action9, calls 00453E80(75) and
00453D60(23), emits a genuine fixed seven-arg
**0x330** sprite at 640/320, sets F10=1, invokes
native 0040FBB0 on the actual opponent receiver
and stores opponent byte+0x10=0x82. Stage11 increments
F00 and invokes auxiliary9 while F00<10, otherwise
clears F10, opponent byte+0x10 and F00. Stage13
increments F00 and invokes auxiliary11 while F00<10.

The [normal source](../probes/FighterThirdBossRandom2F9F1008.inc)
generates all **326 original mnemonic, instruction-width
AND GPR operand roles** and the exact original case
1,254B source CODE length, with **33/33 original PE
call/global destinations** independently checked.
No fake locals, source padding, ASM or target-byte
injection were used.

**Material real preceding-source register phase recovery:**
before true 2F9 C++, adjacent 2FA's 186 mnemonic roles
aligned but **113 native GPR operands were wrong**.
After adding the actual original 2F9 source, **all 113
differences disappear** with no modification to the 2FA
source itself. The original 2FA still has one shared-tail
JMP width error (last local ordinal185): original near5B
versus current short2B.

The [native PE verifier](../scripts/verify-third-fighter-random2f9-f1008.py)
freshly builds two ENTIRE original-shaped PARTIAL normal
VC7.1 82KB fathers (F1007 marker and F1008 genuine).
It checks all original 2F9 fields/instructions, original
2FA, previous 2C0–2C3 and 2E5/2E6, **151 native
afterRET DIR32 labels and 522 original DATA nonfields**.

| Whole original-shaped PARTIAL father | Prior F1007 | New F1008 |
| --- | ---: | ---: |
| Generated partial CODE B | 67,546 | **68,785** |
| Generated partial x86 | 18,528 | **18,852** |
| 2F9 compiled inner source B/x86 | 15/2 marker | **1,254/326** |
| Wrong original 2F9 mnemonic/width/GPR | unaligned | **0/0/0** |
| Real original 2F9 PE fields | marker | **33/33** |
| Following original 2FA GPR errors | 113 | **0** |
| Following original 2FA width errors | 1 | **1 shared tail** |
| Partial compiler frame | 0x4DC | **0x50C** |
| Entire original fighter exact | NO | **NO** |

Matching internal original instruction geometry cannot credit
an independent complete native callable. The original
whole saved receiver EBP−0x64, 0x720 stack frame,
many as-yet unsourced game action bodies and whole-parent
absolute/relative PE relocation offsets remain different.

Reproduce only the two affected normal VC7.1 PARTIAL parents:

    scripts/repo-python scripts/verify-third-fighter-random2f9-f1008.py

Original PE receipt and compiled C++/OBJ/PDB/serial VC7.1
logs are retained under ignored
.analysis/f1008-third-native-proof/ and
.analysis/f1008-third-2f9/.

**No newly accepted exact whole game function or original CODE B.
No all-979-unit cold replay.**
