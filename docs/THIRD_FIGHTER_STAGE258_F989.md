# F989 — Native five-projectile action258 in the original 82KB fighter

The pinned Japanese TH075 v1.11 original fighter at 004AC040
contains **82,796 complete callable CODE bytes/22,721 x86** and
1,126 separate afterRET switch DATA bytes. The tracked
[normal VC7.1 partial source](../probes/FighterWhole004AC040F989.cpp)
does NOT reconstruct the entire native fighter or its original 0x720
stack frame and EBP−0x64 saved receiver, so it remains **NONEXACT**.

The authentic original state258 occupies **004B7BB0..004B7EF2**,
**834 native CODE B/212 x86/15 actual typed PE external fields**.
It is not a compact compiled loop: at signed stage >4, F02<3,
F00<=0 it prepares native 00453D40(0) and writes five
separate float +0x314 angles **F02*3+100/+95/+90/+85/+80**,
+0x318=10.0f, and issues five ordered native
00453A70(0x325) shots with actual float X formed from
signed facing×97 plus +0x44 and real float Y+original
PE global **00659498**. The state starts with +0x7C=1,
ResetAt453E20, two signed shorts F00/F02 reset, invokes
animation0046D000(0x64), increments F02, assigns F00=3
and decrements F00, then handles animation completion to action0.

The [ordinary original-shaped C++](../probes/FighterThirdBossFiveShot258F989.inc)
produces all 212 native original mnemonics and instruction widths
and the same original 834-B case length. Its body introduces
no fake compiler-local variables, ASM, native-byte grafts or
artificial source loop unrolling.

The bounded
[whole-partial-original-PE verifier](../scripts/verify-third-fighter-five-shot-258-f989.py)
freshly compiles tracked F988 marker versus F989 real C++ as
TWO ENTIRE original-shaped normal VC7.1 partial fighter parents.
It checks the pinned original PE's whole identity, real case258
and preceding 257, **all 15 zero-addend typed native external PE
destinations** (plus 257's six), all **151 native afterRET DIR32
local labels** and **522 nonfield DATA bytes**.

| Complete original-shaped partial source | F988 marker | F989 actual state |
| --- | ---: | ---: |
| Emitted partial CODE B | 48,352 | **49,171** |
| Emitted partial x86 | 13,416 | **13,626** |
| Case258 source CODE B/x86 | 15/2 | **834/212** |
| Original wrong mnemonic/width positions | n/a | **0/0** |
| Wrong original GPR roles | n/a | **137** |
| Genuine original case PE fields | marker | **15/15** |
| Partial father compiler frame | 0x2E4 | **0x30C** |
| Whole original callable exact | NO | **NO** |

The actual original fighter saves its receiver at EBP−0x64 and
owns a 0x720 stack frame; these are NOT recreated, and case258
has 137 wrong GPR roles and nonnative absolute PE/COFF owner
locations. Matching inner cases is never accepted as complete
original callable CODE.

Run only the two affected partial parent compilations:

    scripts/repo-python scripts/verify-third-fighter-five-shot-258-f989.py

Native PE, VC7.1 source/OBJ/PDB, original target and typed COFF
receipts are preserved under ignored .analysis/f989-third-original-proof/
and .analysis/f989-third-258/.

**No new accepted complete original callable functions/CODE B;
no 979-unit corpus cold replay.**
