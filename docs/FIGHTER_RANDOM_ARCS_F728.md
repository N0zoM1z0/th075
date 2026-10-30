# F728 — complete original 1F4/1F5 random-arc fighter source with honest upstream regression

**Meaningful game action source recovery, not a byte-exact complete original function.**
Original target is the user's pinned Japanese TH075 1.11 executable
`resources/th075.exe`, SHA-256
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
The authored whole fighter `00543210` owns **58,294 original CODE bytes**
plus **943 independent post-RET switch DATA bytes**. The recovered actions
are parts of that same physical whole function; their original CODE is not
separately accepted as exact authored functions.

## Two original, complete previously placeholder-backed game actions

| Physical original handler | Native PE original extent | Original entire CODE/x86 | Natural VC7.1 new case CODE/x86 | Typed original PE/COFF fields |
| --- | --- | ---: | ---: | ---: |
| `0x1F4` | `0054A6CC`–`0054A8E6` | **538 B /149 x86** | **506 B /149 x86** | **18/18 physical fields** |
| `0x1F5` | `0054A8E6`–`0054AB00` | **538 B /149 x86** | **506 B /149 x86** | **18/18 physical fields** |
| Both original native action interiors | | **1,076 original B /298 x86** | **1,012 emitted B /298 x86** | **36/36** |

Tracked normal C++ [`FighterRandomArcsF728.inc`](../probes/FighterRandomArcsF728.inc)
implements both authentic game actions rather than placeholder markers:

- Actual stage-zero `ResetAt453E20`, signed frame/phase gates and three
  game motion/flag member assignments.
- Native `RandomBoundaryAt455580(0,100)<40` gate and stage 4–7 test,
  followed by the *other two* real random calls `(0,140)` and `(0,60)`.
  Both calls genuinely participate in the projectile's Y and X float
  coordinate computation, not synthetic stack-frame padding.
- Genuine `SpawnFloatXYAt453A70(0x330, X, Y, direction, 1)` with
  original global `[00657878]` for X and `[00657858]` for Y.
- Distinct original source order: `1F4` tests random volley before
  X-velocity drag `[006583FC]`; `1F5` performs X drag with `[00658058]`
  before random volley. Both retain true ground-height checks,
  decrement by the actual Y-motion drag, real collision reset,
  completion callback and separate stage-4 velocities, 8/14 versus
  18/16, with the native stage-18 action 16 versus stage-12 action 10.

The pinned VC7.1 compiler uses the ordinary original-shaped whole
fighter TU, `/Od /Ob0 /Gy /GR- /GX- /GS /Zi`, with no fabricated
saved registers, ASM, inert locals or modified original executable.

## The genuine global-FADD ordinal recovered by a real C++ lvalue

The first complete C++ candidates used `(POS48 + globalY)` and
emitted **`FLD [globalY]; FADD [actor+0x48]`** rather than the native
original **`FLD [actor+0x48]; FADD [00657858]`**. The original
physical native `DIR32` relocation at `1F4` x86 ordinal **36** and
`1F5` ordinal **55** therefore had the wrong instruction owner,
although both compiled entire cases had 149 x86 instructions and the
same total 18 relocation counts. This is not cosmetic: original
machine-code relocation provenance matters independently of call count.

F728 freshly compiled **eight entire original-shaped fighter source
parents** with actual used X/Y lvalue access, const-like C++ spelling
and natural reversed float term orders. The meaningful expression
`(*(&POS48)) + g_F728_RandomOffsetYAt00657858` causes VC7.1 to emit
the authentic **member `FLD` followed by physical global `FADD`**
in both cases. Both corrected global fields, and **all 36 original
`REL32`/`DIR32` fields**, now have authentic original owning x86
ordinal, source symbol, actual native target, type and zero addend.
This is useful source-grammar evidence, not native case byte-exactness.

The generated x86 **mnemonics all match the 149 original positions**
in each case, but **10 real instruction widths differ per case**:
original 538B versus generated 506B. True random float conversion
intermediates have much shallower C++ stack slots:

| Native original handler | Original x87 scratch slots | Actually generated source scratch slots |
| --- | --- | --- |
| `1F4`, used float Y then X random temporaries | `EBP−0xD8`, `−0xDC`, `−0xE0`, `−0xE4` | `−0x4C`, `−0x50`, `−0x54`, `−0x58` |
| `1F5`, Y then X random temporaries | `EBP−0xE8`, `−0xEC`, `−0xF0`, `−0xF4` | `−0x5C`, `−0x60`, `−0x64`, `−0x68` |

These are real used float and integer scratch owners; their original
`FSTP/MOV/FILD/FADD/FSUBR` operands are checked individually. Exactly
**71 nonfield normalized GPR/CFG operand discrepancies per action**
remain. Neither these source cases nor the full giant are exact.

## Important compiler-phase regression: DO NOT repeat old 27-strict claim

Restoring these early actual C++ actions changes register allocation
in the same full parent, including actions *before* the new cases.
The earlier F724 selected whole-parent had 27 original context-strict
internal nonterminal cases. In the current newly compiled F728 parent:

| Previously strict native original handler | Complete native original geometry | Actual current source nonfield GPR discrepancies |
| --- | --- | ---: |
| `0x200` | **343 original B /102 x86 /8 physical typed refs** | **67** |
| `0x201` | **436 original B /126 x86 /9 physical typed refs** | **85** |
| `0x2EF` | **788 original B /224 x86 /20 physical typed refs** | **0** (still context strict) |

Original/source CODE lengths, x86 opcode/width positions and physical
COFF counts for these three sampled complete internal handlers are
rechecked in this same parent. `0x200` and `0x201` are **real new
NONSTRICT register-phase regressions**. The exact total number of
remaining strict prior internal actions in the new F728 context is
**not claimed**: more earlier cases could have changed. It would be
incorrect to transport F724's 27-strict result to F728, or to treat
field counts and normalized registers as byte-exactness. The entire
58KB original boss still has substantial unrecovered source and
cannot earn accepted whole CODE credit.

## Independently audited entire original 943-byte after-RET DATA

The new [`verify-fighter-random-arcs-f728.py`](../scripts/verify-fighter-random-arcs-f728.py)
rebuilds one original-shaped source parent and verifies **all seven
actual native dispatch tables**, including the original 943 post-RET
DATA bytes. It reads every original `DIR32` physical target from the
pinned PE and the matching COFF `local_symbol_offset` from the newly
compiled parent. There are **156 actual table relocations** (all real
`DIR32`, zero addend and distinct nonoverlapping 4-byte locations):
every original target and every source target is an actual *decoded
x86 instruction start* in its own entire CODE body. The native
physical original `1F5` and following `1F6` targets resolve to the
actual new source case labels. The 156 relocations own 624 bytes;
**all other 319/319 original sparse-map bytes match**, including the
switch-index arrays. This is genuine separate original DATA evidence,
not 943 accepted CODE bytes.

The verifier checks each complete new action boundary, all 36 PE
fields at original x86 owner ordinal, native float/stack/width
negatives, actual register-phase regressions in original `200/201`,
original strict `2EF` in this exact source context and the entire
after-RET DATA. `probes/FighterRandomArcsF728.inc` is the only new
normal C++ game source. Source/OBJ/PDB, the eight real expression
variants and physical original-byte evidence are kept locally under
Git-ignored `.analysis/f728-fighter-random-arcs/`.

```bash
scripts/repo-python scripts/verify-fighter-random-arcs-f728.py
scripts/repo-python scripts/verify-fighter-followup-burst-f724.py
scripts/repo-python scripts/validate-tracking.py --require-target
```

No original EXE edits, no invented saved stack locals, no whole-function
byte-exact adoption, no fake inherited strict counts, and no all-943-unit
cold replay. Formal accepted authored coverage remains **943 whole
functions /862,726 original CODE bytes (43.71% reviewed)**.
