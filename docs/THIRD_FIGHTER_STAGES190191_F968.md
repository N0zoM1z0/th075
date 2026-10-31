# F968 — Third original 82KB fighter's two genuine three-shot 190/191 states

The SHA-pinned Japanese TH075 v1.11 original
fighter **004AC040** contains **82,796 whole callable
CODE B/22,721 x86** plus **1,126 genuine afterRET
switch DATA B**. The tracked cumulative
[partial father C++](../probes/FighterWhole004AC040F968.cpp)
now includes real natural sources for states
190 and 191 but still lacks much of the original
82KB parent, including its true saved-`this`
EBP−0x64 and original full 0x720 stack frame.
The original game whole function remains
**NONEXACT**.

Both source-backed native cases occupy separate,
independently verified original physical PE
regions:

| True original action | Original physical range | Complete native CODE | Real external PE fields |
| --- | --- | ---: | ---: |
| **190** | **004B2167..004B23BC** | **597 B/147 x86** | **11** |
| **191** | **004B23BC..004B2611** | **597 B/147 x86** | **11** |
| Both | consecutive | **1,194 B/294 x86** | **22** |

These are **not** the historical F734
other-fighter's eight-shot routines, nor
the shorter F856/F857 actor's states. Here,
**both original cases actually have THREE
ordered original `00453A70` projectile calls
per stage trigger**, not an eight-iteration
loop, and have distinct true actor-specific
source constants.

Real source state190 initializes +0x7C=1,
calls ResetAt453E20, clears signed short
+0xF00 and +0xF02. On stage greater than
**5**, `F00<=0` and `F02<5`, it prepares
`00453D40(0)`, invokes animation
`0046D000(0x28)`, then sets actual float
`+0x314` three times from signed short
`F02*4−8`, `F02*4−4`, `F02*4−12`;
sets float `+0x318=7.0f` for each shot;
and issues **three native sprite0x320
float-XY shots** with genuine facing×**49**
plus original X, original Y plus physical
PE global **00659294**, real facing
and trailing 1. The source then
assigns short F00=2, increments short
F02 and decrements F00, before
original native animation completion.

The physical original 191 differs:
stage greater than **4**, three float
angles `F02*4+30/+34/+26`, genuine
signed facing×**97**, and Y global
**00659498**, retaining three separate
native sprite0x320 calls and the
same real counter semantics.

[Original natural C++ bodies](../probes/FighterThirdBossStages190191F968.inc)
use source-level signed-short and
signed-facing float expressions and
real call ordering, NOT artificial
compiler loop unrolling, dummy stack
variables, manually forced GPR roles,
ASM or native-byte grafting.

## Full-source compiler and pinned PE results

The [targeted verifier](../scripts/verify-third-fighter-stages190191-f968.py)
freshly compiles TWO whole original-shaped
normal VC7.1 partial giant parents:
old F966 markers and new F968 real
source. It independently checks all
294 ordered original x86 mnemonic
positions, the exact original physical
instruction widths, all **22 real typed
zero-addend original PE/COFF target
addresses**, native preceding 189 and
all **151 original afterRET local
DIR32 labels and 522 nonfield DATA B**.

| Entire partial parent source | F966 markers | F968 natural source |
| --- | ---: | ---: |
| Compiled partial CODE B | 25,798 | **26,893** |
| Compiled x86 instructions | 7,113 | **7,403** |
| Original 190 source B/x86 | 15/2 | **561/147** |
| Original 191 source B/x86 | 15/2 | **561/147** |
| Native 190/191 incorrect mnemonics | n/a | **0 in both** |
| Native 190/191 width errors | n/a | **12 each** |
| Native 190/191 wrong GPR roles | n/a | **94 each** |
| Original typed PE external targets checked | markers | **11+11** |
| Real afterRET DIR32 / nonfield DATA | 151/522 | **151/522** |
| Whole 82KB game exact | NO | **NO** |

Each original native case has **six
genuine 32-bit integer-to-x87
scratch temporaries**, emitted as
12 six-byte EBP accesses. The
physical original uses deep
stack locations **EBP−0xA8
through EBP−0xD4**, and the
partial C++ father's smaller
stack allocates shorter 3-byte
EBP displacements. This produces
**36 real source CODE bytes less
per case**, 72 total, even
though all 294 x86 mnemonics
align. Other actual original
register roles and whole-parent
branch/displacement relocations
remain nonnative. No original
exactness is inferred.

The cumulative tracked selected
F968 whole parent emits the
same complete CODE+afterRET
machine bytes and the same
physical relocation offset,
type and local target positions
as the independently expanded
whole C++ source experiment;
internal `$L` COFF symbol
numbers may be renamed by
source-file rewrapping.

Reproduce only the affected
partial original fighter:

    scripts/repo-python scripts/verify-third-fighter-stages190191-f968.py

Complete original-shaped C++/OBJ/PDB,
pinned native PE comparisons, compiler
logs and receipts stay under ignored
`.analysis/f968-third-original-proof/`
and `.analysis/f968-third-190-191/`.

**Zero new accepted complete callable
game CODE bytes or functions, and NO
979-unit all-unit cold replay.**
