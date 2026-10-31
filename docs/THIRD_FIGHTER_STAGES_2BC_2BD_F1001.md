# F1001 — Authentic late fighter 2BC/2BD, 30 verified PE fields

The SHA-pinned Japanese TH075 v1.11 original 004AC040 fighter
owns **82,796 whole callable CODE B/22,721 x86** followed by
**1,126 afterRET jump-table DATA bytes**. The tracked
[normal VC7.1 original-shaped C++](../probes/FighterWhole004AC040F1001.cpp)
is still an INCOMPLETE 82KB fighter, not a complete original
callable exact match.

Two real original game states occupy distinct native ranges:

| Original state | Actual physical PE interval | Original interior CODE/x86 | Actual PE targets |
| --- | --- | ---: | ---: |
| 2BC | 004BAC11..004BAF04 | **755B/199 x86** | **15** |
| 2BD | 004BAF04..004BB1EA | **742B/196 x86** | **15** |

The genuine stage0/frame0 resets native shorts F00/F02/F04/F06,
sets +0x7C=1 and calls ResetAt453E20, and animation completion
transitions with native 0040FA30/0040FAC0(0). Stage3/frame0
calls the original **00453E80(0x28)**, prepares action0x17,
subtracts original PE float **00657888** from actor+0x36C,
and emits one genuine sprite **0x73** for 2BC or **0x74**
for 2BD using signed facing×18 converted through original
FILD/FSUBR world X at +0x44.

**Critical independent PE evidence:** this *initial* sprite Y is
actor+0x48 plus native **00659284**, NOT 0065836C.
The earlier C++ was mnemonic/width-aligned but failed the
strict typed PE target check until its initial Y source was
corrected. The *later two-shot* Y expressions legitimately use
a **different** actual native global **0065836C**. Do not merge
these observed original globals.

The original F04 countdown and stage4..10 conditions control
two actual sprite calls with different actor-specific options:

- **2BC:** original limit F02<**36**, shots **0x323**,
  signed-facing×16 integer shifted then FILD/FSUBR,
  native angles F02×5 and F02×5+180, F02++ **and F04++**.
  Stage5/frame0 prepares action**5**.
- **2BD:** limit F02<**72**, shots **0x32B**, same
  signed-facing/angle arithmetic, but stores native
  **short F14=1** and increments F02 only (no F04++).
  Stage5/frame0 prepares action**6**.

Both use original animation0xA for each two-shot volley;
at stage11/frame0 and F06<5, both invoke auxiliary action9
and increment F06.

The [ordinary C++ source](../probes/FighterThirdBossStages2BC2BDF1001.inc)
uses a generic declaration-only native 00453E80 member ABI,
real actor fields, and the independently established signed
world-X borrowed view. No artificial compiler locals,
register forcing, cropped cases, assembly or relocation masking.

The bounded
[original PE/COFF verifier](../scripts/verify-third-fighter-stages2bc2bd-f1001.py)
freshly builds TWO ENTIRE original-shaped PARTIAL VC7.1 fathers:
F998 old markers and F1001 true 2BC/2BD. It checks **all 395
original ordered mnemonic positions**, every original width,
**all 30 actual typed zero-addend PE/COFF call/global target
addresses**, preceding real 25D/25E and four ten-shot cases,
and all **151 actual afterRET DIR32 table labels with
522 original DATA nonfield bytes**.

| Entire original-shaped PARTIAL father | F998 prior | F1001 genuine |
| --- | ---: | ---: |
| Emitted partial CODE B | 60,595 | **62,063** |
| Emitted partial x86 | 16,621 | **17,012** |
| 2BC source B/x86 | 15/2 marker | **755/199** |
| 2BD source B/x86 | 15/2 marker | **743/196** |
| Wrong native mnemonic positions | unaligned | **0/0** |
| Wrong original x86 widths | unaligned | **0/1** |
| Wrong native GPR roles | unaligned | **128/125** |
| Real original typed PE destinations | stubs | **15+15** |
| Compiler partial source frame | 0x434 | **0x45C** |
| Whole original 82KB exact | NO | **NO** |

**The one real 2BD width defect:** at native local ordinal
133, original ADD EAX,0xB4 uses five bytes, while generated
ADD EDX,0xB4 uses six. Eight normal whole-parent signed
integer expression/cast/operand-order trials left it intact,
with correct 196 mnemonic roles, so do NOT claim byte-exact
internal 2BD. The original full father still has its
0x720 stack frame, saved receiver EBP−0x64, different native
scratch slots, many unsourced actions and whole-parent
relocation positions. Both interior states earn zero
accepted whole-original CODE credit.

Reproduce only the two affected whole-partial-parent builds:

    scripts/repo-python scripts/verify-third-fighter-stages2bc2bd-f1001.py

Full native PE receipt, compiled source/OBJ/PDB and VC7.1 logs
are under ignored .analysis/f1001-third-original-proof/;
eight signed-value-category controls are under
.analysis/f1001-third-2bc-2bd/grammar/.

**Zero new accepted exact original whole callables or CODE B.
No 979-unit corpus-wide cold replay.**
