# F979 — Native third-fighter 1A3/1A4 randomized loops

Pinned Japanese TH075 v1.11 original fighter 004AC040 is
**82,796 complete callable CODE B /22,721 x86** plus a separate
1,126B afterRET jump DATA. The [tracked partial C++ parent](../probes/FighterWhole004AC040F979.cpp)
remains NONEXACT: original 0x720 frame, saved receiver EBP−0x64,
GPR allocation and many game-state actions remain unrecovered.

| Original state | Native physical PE interval | Native interior | Original typed PE fields |
| --- | --- | ---: | ---: |
| 1A3 | 004B4981..004B4BAD | **556B/147 x86** | 11 |
| 1A4 | 004B4BAD..004B4DE7 | **570B/151 x86** | 11 |

The original corrects earlier actor hypotheses: neither action
calls ResetAt453E20 at stage0; both set +0x7C=1, reduce
vertical speed by drag at +0x54/+0x5C, transition on actual
animation completion to **action9**, and at stage5/frame0
prepare native 00453D40(0). Both dispatch authentic
**5-shot /8-shot randomized projectile loops** by signed
mode byte +0x39D, each using actual sprite 00453B50(0x344),
native RandAt455580(0,20) for float Y offset and distinct
random calls for X.

- **1A3:** original Y global **00657858**, loop Y steps
  **30/20**, X based on random80+30 or random100+20
  multiplied by signed facing. **147 x86**.
- **1A4:** original Y global **0065786C**, Y steps
  **40/30**, native angle −30.0f, X based on loop shot*10
  plus random80/100 plus 30/20. Original ESI survives
  the random call. **151 x86**.

The real original-shaped source is
[FighterThirdBossRandomLoops1A31A4F979.inc](../probes/FighterThirdBossRandomLoops1A31A4F979.inc).
An initial full-parent experiment incorrectly copied an
unobserved stage0 Reset from another fighter into 1A4,
adding two false x86 instructions. Removing it, restoring
action9 and retaining the actual original X expression
recovers correct native mnemonic and width geometry.
No fake locals, byte grafts or assembly.

The [bounded native verifier](../scripts/verify-third-fighter-random-loops-1a3-1a4-f979.py)
rebuilds two ENTIRE normal VC7.1 original-shaped PARTIAL
82KB fighter parents (tracked F978 prior markers and F979
real handlers). It independently reads the original PE,
verifies all **298 complete original x86 mnemonic/width
positions**, **22 genuine typed zero-addend PE/COFF targets**,
preceding real 1A2, all **151 afterRET DIR32 labels** and
**522 native nonfield DATA bytes**.

| Whole partial father | F978 old | F979 real |
| --- | ---: | ---: |
| C++ partial CODE B | 35,751 | **36,871** |
| Whole partial x86 | 9,799 | **10,093** |
| 1A3 source B/x86 | 15/2 | **556/147** |
| 1A4 source B/x86 | 15/2 | **570/151** |
| Wrong original mnemonic/widths | unaligned | **0/0 both** |
| Genuine original GPR errors | unaligned | **67/71** |
| Native actual PE targets | markers | **11+11** |
| Entire original callable exact | NO | **NO** |

Complete whole-source C++/OBJ/PDB, original PE receipt
and VC7.1 logs reside at ignored
.analysis/f979-third-original-proof/. Reproduce only
the affected partial giant:

    scripts/repo-python scripts/verify-third-fighter-random-loops-1a3-1a4-f979.py

**Zero newly accepted complete original game functions or CODE.
No 979-unit all-unit cold replay.**
