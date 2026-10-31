# F981 — Two original 830-byte Fighter 1F4/1F5 states

The pinned Japanese TH075 v1.11 original fighter 004AC040
owns **82,796 callable CODE B/22,721 x86** and **1,126
afterRET jump-table DATA B**. The tracked
[original-shaped partial VC7.1 C++](../probes/FighterWhole004AC040F981.cpp)
is still NONEXACT as a whole original function: full original
0x720 frame, saved receiver at EBP−0x64, many states and GPR
ownership remain missing.

| Real native action | Physical original PE range | Whole native inner CODE | Original PE fields |
| --- | --- | ---: | ---: |
| **1F4** | 004B4DE7..004B5125 | **830B/232 x86** | **23** |
| **1F5** | 004B5125..004B5463 | **830B/232 x86** | **23** |

Both real states initialize native signed short +0x80=99,
zero +0x7C, signed fall flag +0x3AC and shorts +0xF00/F02,
call ResetAt453E20, and handle original x87 height/ground
collision, subtracting real drag, setting auxiliary action0xC
and clearing Y. Original +0x7C!=0 increments short F02
and resets it after exceeding 6; frame completion triggers
native action0. Stage7/frame0 changes genuine motion
and issues a real **0x7F** projectile through 00453C80
before preparing action3. Stage8/frame0 sets true original
+0x314/+0x318/+0x31C float parameters and emits two
**0x32A/0x329 pairs** via the real 00453B50 API, with
native X/Y plus physical PE global 00659270 and actual
signed facing. Stage10/frame0 changes auxiliary action8
with a bounded original short +0xF00 counter, and stage12
enters auxiliary action0xB.

A critical actor-specific original difference is preserved:
**1F4** stage7 sets X=2.0f, velocity=6.5f, drag=0.4f
**before** its projectile; **1F5** sets X=8.0f,
velocity=13.5f, launches the 0x7F projectile, **then**
sets drag=0.5f. Their stage10 real F00 thresholds are
**less than 1** and **less than 3**, respectively. Swapping
the drag placement or treating the modes identically would
lose original instruction roles and gameplay ordering.

The [authentic ordinary C++ states](../probes/FighterThirdBossStages1F41F5F981.inc)
are embedded in the still-partial whole parent; no fake
padding, assembly, manually forced registers or native-byte
grafts were introduced.

The bounded [native PE verifier](../scripts/verify-third-fighter-stages1f4-1f5-f981.py)
freshly compiles TWO entire original-shaped PARTIAL VC7.1
fighter parents (F979 markers and F981 real C++). It checks
all **464 original x86 mnemonic/width positions**,
all **46 original typed zero-addend PE/COFF destinations**,
the preceding native 1A4 state, all **151 original afterRET
DIR32 labels** and **522 native nonfield DATA B**.

| Partial whole father | F979 prior | F981 source |
| --- | ---: | ---: |
| Generated partial CODE B | 36,871 | **38,501** |
| Generated x86 | 10,093 | **10,553** |
| 1F4 inner CODE/x86 | 15/2 marker | **830/232** |
| 1F5 inner CODE/x86 | 15/2 marker | **830/232** |
| Wrong native mnemonic/width ordinals | not aligned | **0/0 both** |
| Wrong original GPR roles | not aligned | **135/135** |
| Real PE destinations | markers | **23+23** |
| Entire original callable exact | NO | **NO** |

Full original PE/COFF results, compiler source/OBJ/PDB and
serial VC7.1 logs are retained under ignored
.analysis/f981-third-original-proof/ and earlier controls in
.analysis/f981-third-1f4-1f5/. Reproduce only affected parents:

    scripts/repo-python scripts/verify-third-fighter-stages1f4-1f5-f981.py

**No newly accepted complete original callable CODE; no all-unit
979-function cold replay.**
