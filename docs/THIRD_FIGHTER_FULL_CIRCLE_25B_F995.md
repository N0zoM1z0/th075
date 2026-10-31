# F995 — Authentic native 25B full-circle 36-shot game state (3,693 CODE B)

The SHA-pinned Japanese TH075 v1.11 original fighter 004AC040
owns **82,796 complete callable original CODE B /22,721 x86**
plus separately owned **1,126 afterRET jump DATA bytes**.
The [tracked normal VC7.1 cumulative C++](../probes/FighterWhole004AC040F995.cpp)
is an INCOMPLETE 82KB original-shaped father, not a
whole-original byte-exact replacement.

**Native original 25B** occupies physical executable
**004B84BA..004B9327**, exactly **3,693 original CODE B /
957 native x86 /77 genuine typed PE call/global target fields**.

## Real original game behavior, not source padding

At original stage0/frame0 this game state sets +0x7C=1,
calls ResetAt453E20 and clears genuine signed shorts
+0xF00 and +0xF02. It then decrements short F00 every
frame. When signed stage exceeds 5, F00<=0 and F02<1,
it prepares native action0 and starts native animation
**0046D000(0xFA)**.

The original executable then issues exactly **36 separately
observable native 00453A70(0x327) projectile calls**. The
actual original writes to float +0x314 were independently
decoded from PE and their IEEE-754 values checked one
by one, not guessed:

    0, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110,
    120, 130, 140, 150, 160, 170, 180, 190, 200, 210,
    220, 230, 240, 250, 260, 270, 280, 290, 300, 310,
    320, 330, 340, 350 degrees

Each physical shot stores +0x318=7.0f, performs authentic
signed-facing byte×**49** integer multiply, **FILD** and
float ADD of original +0x44 X, reads actual Y+0x48 plus
physical PE global **00659294**, and passes original facing
and trailing layer1. Each shot's 25 ordered original x86
instructions are independently preserved in the
[normal C++ source](../probes/FighterThirdBossFullCircle25BF995.inc)
as real sequential game operations, not dummy compiled loops.
After all 36 shots, original F00=2, F02++ and native
animation completion action0 are retained.

## Full 82KB parent compilation and an important GPR phase regression

The [bounded verifier](../scripts/verify-third-fighter-full-circle25b-f995.py)
fresh-compiles TWO ENTIRE pinned normal VC7.1 PARTIAL father
sources, tracked F994 with a 15B marker and F995 with all
36 real calls. It verifies original executable identity,
all **957 native positional mnemonics AND x86 instruction
widths**, all **77 independently typed zero-addend original
PE/COFF destinations**, preceding native 25A,
four other genuine 25F/260/261/262 handlers, and the
entire **151 original afterRET DIR32 local labels and
522 native nonfield DATA bytes**.

| Complete partial father C++ | F994 prior | F995 real original 25B |
| --- | ---: | ---: |
| Emitted partial CODE B | 52,238 | **55,916** |
| Emitted partial x86 | 14,416 | **15,371** |
| 25B source CODE B/x86 | 15/2 marker | **3,693/957** |
| Wrong native 25B mnemonic/width positions | n/a | **0/0** |
| Wrong native 25B GPR-role instructions | n/a | **577** |
| Correct native 25B physical PE targets | marker | **77/77** |
| Partial source compiler frame | 0x380 | **0x410** |
| Entire original 82KB father exact | NO | **NO** |

**Do NOT hide or ignore the cross-case regression.**
The genuine large-state source grows the entire partial
parent's compiler frame from 0x380 to 0x410 and changes
global register allocation across other real actions:

| Original following case | Wrong original GPR roles before 25B | After |
| --- | ---: | ---: |
| 25F, 114 native x86 | 0 | **73** |
| 260, 114 native x86 | 0 | **73** |
| 261, 98 native x86 | 0 | **65** |
| 262, 98 native x86 | 0 | **65** |

For all four preceding-source controls, **native mnemonic,
instruction widths and all 34 genuine original PE external
targets remain correct** after adding 25B. The GPR
phase worsens because the still-incomplete parent lacks
its original full 0x720 stack and other real game owner
lifetimes, not because there are fake data moves in 25B.

Four further full-parent genuine C++ source controls tested
36 per-shot local scopes, six-shot groups, twelve-shot
groups and the independently verified borrowed world-X field.
All reproduced the 3,693B/957 native geometry but NONE
repaired the 73/73/65/65 GPR phase. Their complete source/
compiler results remain under ignored
.analysis/f995-third-25b/grammar/; no artificial stack
padding or manually forced registers were adopted.

The selected tracked 25B represents real game logic,
**not whole-callable exact CODE or a guarantee of all
earlier register roles being matched**. Original receiver
EBP−0x64, 0x720 frame, actual scratch EBP and entire
relative/absolute PE/COFF positions remain different.

Reproduce only the affected whole PARTIAL giant sources:

    scripts/repo-python scripts/verify-third-fighter-full-circle25b-f995.py

Native PE receipt and C++/OBJ/PDB/compiler output are retained
in ignored .analysis/f995-third-native-proof/ and
.analysis/f995-third-25b/.

**New accepted original complete callable functions: zero.
New credited native CODE: zero.
No all-979-unit cold replay.**
