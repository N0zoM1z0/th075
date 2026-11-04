# F1085 — Restore real original 1,266B action 0x34C: health gates, eight-shot 0x360 and x87 order

The pinned Japanese TH075 1.11 has one independently authored
`CharacterObject::Advance` at **0050A580**, with original
**81,539 callable CODE B /17,435 x86**, plus separately owned
**567 afterRET sparse jump DATA B**. The entire original remains
NONEXACT. F1085 reconstructs the true switch interior `0x34C`
from independently inspected actual original PE bytes rather than
inventing a new exact callable.

Native original `0x34C` occupies **00512D43..00513235**, a genuine
**1,266 CODE B /273 x86** complete state segment. The C++
source now implements real stage/frame-zero reset `0040FBB0`,
actual status/scale/alpha fields, preservation of signed +0xD8
140 counter, original `0040FB70` trajectory with signed parent
+0xF0C, actor+C8, global float `0065989C`, motion X+parent X and
actual Y velocity×`00657F74` plus parent Y+`0065835C` offset.
It advances +0xD8 by 5 to a maximum of 140.

The original then checks **grandparent signed current health
+0x324**, parent current health+0x324 and parent's native
+0x3A0 count, and changes auxiliary action when real actor stage
is below 2. It handles genuine parent action `0x2C1`/parent stage 2
and actor stage below 2, then four original stage-dependent
parent action/phase alternatives: `0x190/4`, `0x258/7`, `0x259/7`
and `0x25A/3`. The true stage-zero branch executes a genuine
**eight-shot loop**: for each shot 0..7, it writes a real float
`shot*45` into parent+0x314, then spawns **`0x360`** at native
`00453A70` with the actor X/Y and parent+0x66 facing. Parent
`00453D40(4)` and source `0040FB40(2)` follow in the authentic
order. Stage 1 has original `0x2C1`/phase 3 action-zero transition,
parent `00453D40(20)` and early return; later stage fade drops
original unsigned alpha by 10 or expires, followed by authentic
`0040FA30` completion. Stage 2/frame zero resets action, subtracts
original global **006592A4** from parent+0x36C float and invokes
native parent `00453D40(20)`.

## Genuine original x87 operand and COFF-target correction

The first full VC7.1 C++ source produced **273/273 original
mnemonics**, **271/273 GPR roles** and **17/18 original physical PE
nonlocal fields**. The only two GPR/physical relocation errors were
from one actual Y-velocity multiplier: source emitted
`FLD [00657F74]; FMUL [actor+54]`, while the real PE at x86
ordinals **60/61** has `FLD [actor+0x54]; FMUL [00657F74]`.

Expressing the *genuinely used borrowed actor velocity lvalue*
as `*(&F1037_MOTION(this).yMotion)` in the existing multiply
restores the authentic native `FLD`/`FMUL` order with normal C++
semantics and no fake variable lifetime, asm, or binary patch.
The selected source now compiles inside the entire one-switch parent:

| Original native action `0x34C` | Recompiled normal C++ |
| --- | ---: |
| Original CODE/x86 | **1,266B /273** |
| Selected source case CODE/x86 | **1,044B /273** |
| Native mnemonic positions correct | **273/273** |
| Native GPR-role positions correct | **273/273** |
| Matching original instruction widths | 200/273 |
| Actual original physical PE nonlocal fields | **18/18** |
| Original x87 Y-global field | Native **ordinal 61**, correct |
| Actual `0x360` spawn loop | 8 real iterations, call ordinal 192 |

The source is not original-byte exact due to the much larger
original stack. A new complete normal VC7.1 one-parent build was
independently checked against the entire SHA-pinned Japanese PE,
including original **92 DIR32 case-label equivalence partitions**,
**199 literal sparse-index bytes**, all physical PE REL32/DIR32
call/global field positions and every nonrelocated original scalar
immediate. The live verifier now checks **43 authentic original
state interiors** containing **35,805 original native CODE B /
7,786 x86**: **7,786/7,786 mnemonic and GPR roles**, **620/620
actual physical external PE targets** and **1,452 original scalar
literal positions**. The incomplete C++ emits **29,479 CODE B /
7,928 x86**, of which **28,598B** are generated restored-case
interior source, plus the actual 567B afterRET DATA. The true
original still has `ESP 0x3A0` and receiver EBP-`0xAC`, vs
current `ESP 0x194` and EBP-`0x64`, and many original states
are still marker-only; **zero new accepted complete original
callable CODE bytes** were added.

Reproduce the ONE affected original-shaped parent only:

    scripts/repo-python scripts/verify-characterobject-current-recovered-f1068.py

All older original-PE state/float controls were recompiled against
the current frame without all-979 cold replay. Full source, normal
VC7.1 OBJ/PDB/compiler logs and original PE receipts are retained
under ignored `.analysis/f1085-native34c/` and
`.analysis/f1068-boss-live-all-native/`.
