# F978 — Original third-fighter 1A2 two genuine five-projectile branches

The pinned Japanese TH075 v1.11 original fighter at **004AC040**
contains **82,796 complete callable CODE B /22,721 x86**, plus
**1,126 separate afterRET jump-table DATA B**. The growing
[tracked normal VC7.1 partial source](../probes/FighterWhole004AC040F978.cpp)
does not yet reproduce the full original 0x720 stack, native
EBP−0x64 saved receiver, many game states or original GPR roles.
It remains **NONEXACT**.

The physical original action **1A2** occupies
**004B450B..004B4981**, exactly **1,142 native internal CODE B /
309 x86 /24 actual PE-targeted source fields**. Its real
stage0/frame0 branch sets +0x7C=1 and calls ResetAt453E20.
Animation completion sets action2. Stage5/frame0 prepares
00453D40(0), then checks the genuine signed mode at +0x39D.

**Two genuinely separate original paths** exist: mode==2
and otherwise. Each explicitly writes five native angles
at +0x314: **65, 55, 45, 35, 25** (floats),
writes +0x318=10.0f per shot, then issues five native
seven-argument **00453B50(0x344)** projectile calls.
Each X is float(signedFacing×47)+actual float this+0x44;
each Y is real float this+0x48 plus physical PE global
**00658264**. The source keeps both native branches and
ten genuine calls. Simplifying them into a single compiler
loop could alter real original x86/COFF control flow.
No fake registers, assembler, byte grafts or padding were used.

The new [natural C++](../probes/FighterThirdBossDualFiveShot1A2F978.inc)
was first compiled in an independently expanded whole
original-shaped 82KB source; the tracked cumulative parent
then produced identical complete CODE+DATA bytes, physical COFF
relocation positions, types and local targets.

The bounded [native PE verifier](../scripts/verify-third-fighter-dual-five-shot-f978.py)
cold-compiles TWO complete original-shaped normal VC7.1 partial
parents: tracked F977 with marker, and F978 with authentic 1A2.
It independently checks all **309 native mnemonic and instruction
width ordinals**, all **24 real zero-addend PE/COFF call/global
targets**, genuine previous 1A1 case, the **151 original afterRET
DIR32 case labels and 522 real nonfield DATA bytes**.

| Whole partial father | F977 previous | F978 authentic |
| --- | ---: | ---: |
| Emitted partial CODE B | 34,624 | **35,751** |
| Emitted x86 | 9,492 | **9,799** |
| Real 1A2 CODE B/x86 | 15/2 marker | **1,142/309** |
| Wrong native 1A2 mnemonic/width positions | n/a | **0/0** |
| Real original 1A2 PE target fields | marker | **24/24** |
| Wrong original 1A2 GPR-role instructions | n/a | **171** |
| Original afterRET DIR32/nonfield DATA | 151/522 | **151/522** |
| Whole original 82KB game function exact | NO | **NO** |

The original complete callable has many remaining GPR, EBP,
jump/displacement and relocation differences. Original CODE
credit is **zero** for these internal state bodies until
the whole callable matches.

Reproduce only the two affected original-shaped parents:

    scripts/repo-python scripts/verify-third-fighter-dual-five-shot-f978.py

C++/OBJ/PDB, original physical PE verification and serial VC7.1
compiler logs are retained under ignored
`.analysis/f978-third-original-proof/` and
`.analysis/f978-third-1a2/`. **No all-979-unit cold replay.**
