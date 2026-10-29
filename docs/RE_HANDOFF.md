# TH075 — active reconstruction handoff

**Maintained 2026-10-29 after F614.** This is the **only current task list**.
The [F540–F596 research chronology](history/RE_HANDOFF_F540_THROUGH_F596.md),
[knowledge base](KNOWLEDGE_BASE.md), and older F-series studies are
**historical evidence**, not statements of current progress. Independently
re-read original PE, current Git/files and manifests; old hypotheses
may be wrong. User requests substantive work on **both whole giant boss
functions and small leaves**, immediate `gpt-web: ...` commits, continuing
*every* dirty edit (the user reports no other active session), and **NO
full all-unit cold replay**; only compile/replay affected units.

## 1. Live source-of-truth and exact accounting

| Item | Verified live snapshot (recheck with commands below) |
| --- | --- |
| Original target | User-provided **Japanese** TH075 1.11 `resources/th075.exe` SHA256 `bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`; do not use localized `th075c.exe` |
| Whole exact source | **943 functions / 943 exact units**, **862,726 original CODE bytes** |
| Reviewed authored coverage | **43.71%** of **1,973,704** reviewed bytes; conservative **43.64%** including pending origins |
| Provisional native candidates | 4,351; 1,004 origin-classified authored, **95 unknown** comprising 3,420 original bytes |
| Unmatched authored | **25 complete functions**: **22 large fighter bosses** totaling **1,102,055 CODE bytes**, and 3 smaller complete originals below |
| Goal | 98% authored-byte coverage **not achieved**. No external Oracle acceptance receipt |

```bash
git status --short --branch
git log -5 --oneline
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/report-reconstruction-status.py --summary
scripts/repo-python scripts/validate-tracking.py --require-target
scripts/repo-python scripts/audit-active-handoff.py
```

**Authority order:** actual original pinned PE + physical full function
and x86/relocation boundaries; `config/function-origins.csv` and
`config/functions.csv`; accepted `config/match-units.toml` and cold
replay; then *provisional* C++ names, documentation and decompiler
hypotheses. `structural-exact` without verified provenance is not
accepted authored CODE. A complete boss **case is not its own exact
function**; after-RET jump DATA is not CODE.

## 2. Main large-boss task: original `004EBDA0`

The `CharacterObject::Advance`-like whole native function has
**33,293 CODE bytes, 8,789 complete x86 instructions**, and
**438 separately owned after-RET DATA bytes**. Its tracked normal
C++ source is `probes/CharacterObjectActionsF572.cpp` (provisional
class names, not exact original declarations). Under genuine pinned
VC7.1 `/Od /Ob0 /Gy /GR- /GX- /GS /Zi` it now reproduces **all
8,789 original instruction start offsets, opcode widths and mnemonic
order**, complete native CODE length and compressed table layout.

**Latest original-PE verified F596, NOT F593's historical state:**

| Whole original CODE + DATA comparison | Current F596 |
| --- | ---: |
| CODE / after-RET DATA | **33,293 B / 438 B** |
| Original native x86 instructions / ordered mnemonics | **8,789 / 8,789** |
| Actual typed zero-addend PE/COFF fields | **622 CODE + 60 DATA = 682** |
| Original literal compressed switch index bytes | **198 / 198 identical** |
| Whole non-relocation bytes identical | **30,866 / 31,003** |
| Remaining non-relocation byte differences | **137** across 133 x86 instructions |
| Historical 3 independent `MOV`/`FLD` swaps | **ZERO remain** since F596 |
| Strictly source-grammar verified original *case subranges* | **56 cases**, 8,300 original x86 roles, 31,374 original *internal*, **uncredited** CODE bytes, 586 genuine typed case fields |

All **137** wrong nonrelocation bytes are linked to three remaining
compiler-register cycles; **whole giant remains NONEXACT**:

| Native case | Native complete role/size (not credited exact) | Different original GPR-role operands | Useful next evidence |
| --- | --- | ---: | --- |
| `0x38D` | 155 instructions /570 B | **45**, starting at case ordinal **91** (`004F344C`) | Native registers rotate after stage4 fade; source `F32(+0x1C)`/byte fade lexical scope suspected but **23 F594 + 6 F598 natural variants failed** |
| `0x38E` | 87 /348 B | **64** | Register rotation persists across source case boundary; compare original owner/view, not isolated fake register assignments |
| `0x3E3` | 200 /812 B | **24**, all in ordinals 0–30 | The same cycle disappears at ordinal31; investigate genuine enclosing scope and last-case compiler context |

Three previously disputed collision cases **`0x32A/0x32C/0x335`**
are now strictly native x86/byte-order equal in source after
natural C++ lvalues (`*(&F32(0x48)) ± *(&F32(0x54))`). Do not
reintroduce the old F573/F574/F578 expected swapped instruction
orders. Distinct last actions `0x3E4` (261 instructions /1,126 B)
and `0x3E5` (96 /396 B) are source-grammar strict but the
**whole function is still nonexact**.

Reproduce **only this one affected compilation**:

```bash
scripts/repo-python scripts/verify-characterobject-native-collision-order-f596.py
# Or inspect the underlying whole-original full COFF comparison:
scripts/repo-python scripts/verify-characterobject-whole-geometry-f593.py
```

Primary current results: [F596 collision-order and 137-byte residual](CHARACTEROBJECT_NATIVE_COLLISION_ORDER_F596.md),
[F593 whole CODE+DATA methodology and previous 155-byte baseline](CHARACTEROBJECT_WHOLE_GEOMETRY_F593.md),
`docs/CHARACTEROBJECT_COMPLEX_AIM_F592.md`. Fresh compiler and whole
PE/COFF receipts under ignored `.analysis/f593-characterobject-whole-source/`
and `.analysis/f596-characterobject-native-collision-source/`.

## 3. Other large original fighter bosses — do not only fix leaves

**22 large fighter bosses** together contain **1,102,055 CODE bytes**
plus **16,123 separate after-RET switch DATA bytes**. `004EBDA0`
is only one; **21 other whole giants remain nonexact**, including
Reimu `0045DD70`, CharacterMove `004AC040` (82,796 B), and
other 28–82K native bodies. Their native dispatches, GPR/x87
case families and table partitions have been partially decoded;
**do not conflate a locally strict case C++ probe with an accepted
complete original function**.

Read `config/fighter-boss-dispatch-fingerprints.json`,
[FIGHTER_BOSS_FAMILY_DISPATCH.md](FIGHTER_BOSS_FAMILY_DISPATCH.md),
[FIGHTER_ACTION_CASE_RESOLUTION.md](FIGHTER_ACTION_CASE_RESOLUTION.md),
and [FIGHTER_OPENING_SIX_CASES_CODEGEN.md](FIGHTER_OPENING_SIX_CASES_CODEGEN.md).
**F598, newly original-backed 12th action inside all eleven multi-switch
fighter giants:** native isolated action **0x32/50** now compiles as real
natural C++ in the same `Advance()` function as the earlier 11 original
actions, rather than a diagnostic marker. The 11 whole-case codegen
comparisons prove **638 original x86 instruction roles /2,306 internal
CODE bytes /77 true typed native COFF fields**; the one `00564BE0`
wide-frame case requires 17 physical EBP-0x88 receiver loads
(**256 native vs 205 source CODE bytes**). All earlier 121 native
case grammars and 1,607 physical jump DWORD fields/4,502 original
sparse bytes remain verified. Together **132 inner cases /26,835
original CODE bytes** are source-backed but **NO entire giant CODE
byte-exact acceptance or split-case credit**. At F598, indexed
cases from `0x33` were still unfinished; F600 now reconstructs the
first eleven real second-table actions. States from `0x46` and the
entire enclosing fighter frame remain unfinished.
[F598 PE+VC7.1 11-fighter contact singleton](FIGHTER_SINGLETON_CONTACT_F598.md),
tracked real C++ [case source](../probes/FighterSingletonContactF598.inc).

Use only a *selected* fighter original and source compilation, for example:

```bash
scripts/repo-python scripts/verify-fighter-singleton-contact-f598.py --boss 0x004F7130
scripts/repo-python scripts/verify-fighter-singleton-contact-f598.py --boss 0x00564BE0
```

**F600 continues immediately after F598's standalone `0x32`:**
original indexed action **`0x33`/51** was reconstructed as real
natural C++ in the **same** eleven entire Fighter source switches.
All **11/11** original cases match **58/58 instruction roles,
7/7 actual native typed COFF fields** and **205 original/source
case bytes**, except genuine `00564BE0` wide saved-this
`EBP-0x88` encodes original **256 vs 205 source bytes**. Crucial
original distinction: 0x32 initializes `-8.0f`, 0x33 `-9.0f`;
register roles rotate at the case boundary and now match naturally.
The new 11 cases add **638 original x86 roles, 2,306 native interior
CODE bytes and 77 COFF fields**. Across 11 giant parents,
**143 genuine source-backed case subranges/8,111 x86/29,141 original
interior CODE bytes/944 typed fields** are now reverified, but
**ZERO whole boss is newly exact or added to authored accepted CODE**.
Earlier 11 cases plus full native F598 case50 and all original jump
DATA remain verified in each freshly compiled F600 source TU.
[F600 indexed original action0x33](FIGHTER_INDEXED_CONTACT51_F600.md).

```bash
scripts/repo-python scripts/verify-fighter-indexed-contact51-f600.py --boss 0x004F7130
scripts/repo-python scripts/verify-fighter-indexed-contact51-f600.py --boss 0x00564BE0
```

**F600 further reconstructed the next ELEVEN actual native contact cases
`0x33/34/35/38/39/3A/3B/3E/3F/40/41` in every one of the same 11
giants**, with original physical compressed table boundaries and
normal VC7.1 C++ source. This is **121 complete native inner cases**,
**7,711 x86 GPR/x87/CFG instruction roles**, **28,399 original interior
CODE bytes** and **880 native PE/COFF physical reference fields**.
The original `00564BE0` wide EBP-0x88 stack accounts for 624 extra
physical receiver-displacement bytes; fighter `005AEEC0` uniquely uses
counter `+0xEFC` instead of `+0xF00` in three action cases. Original
`0x3E/3F/40` transitions use state **2**, not 0; three late contact
cases contain an independent stage-7 guarded secondary action. The
new C++ source retains every prior opening case0..10, F598 action0x32
and the full original after-RET table shape. Across F598/F600 this
is **253 inner case bodies /55,234 uncredited original CODE bytes**,
not 253 new whole functions; **all 11 whole giants are still
NONEXACT**. [F600 full physical/source controls](FIGHTER_ADDITIONAL_CONTACT_F600.md),
[real eleven-case C++ source](../probes/FighterAdditionalContactF600.inc).
To reproduce a single affected compilation:

```bash
scripts/repo-python scripts/verify-fighter-additional-contact-f600.py --boss 0x004F7130
```

**F601 original-native counter ownership refinement:** before compiling
each targeted giant, the verifier now independently reads the full
original x86 in all **three** stage-7 cases `0x35`, `0x3B`, `0x41`,
extracts each actual 16-bit member offset and requires agreement.
Ten original fighters use `+0xF00` and `005AEEC0` uses `+0xEFC`;
no per-boss hardcoded member-offset guess remains in source generation.
A wrong universal `+0xF00` guess physically fails the `005AEEC0`
original/source 79-instruction case grammar. The same selected-F600
script remains the reproducer; this still contributes **zero
whole-fighter exact acceptance**.

**F602** restores actual second-switch trajectory action **`0x46`**
inside **nine** of the eleven giant fighters. Each complete native
case has **104 original GPR/x87/CFG instructions** and **15 physically
verified typed PE/COFF destinations**; normal cases have 374 original
bytes, with one real wide-EBP original `00564BE0` having 485: its genuine
111-byte increase consists of 33 widened `MOV` receiver loads
(**3 bytes each**) and **three 2-byte short → 6-byte near `Jcc`**
branches (**4 bytes each**), not 37 widened loads. The native
stage/counter source is derived from the PE. Across nine separate
fresh VC7.1 source builds, **936 native roles,
3,477 original internal CODE bytes, 135 typed fields** are now
source-backed while keeping the earlier 23 true case roles and full
seven-switch after-RET DATA geometry. Native per-boss speed bounds,
stage/early/late actions, 2 float→short `__ftol2` conversions and
original `005AEEC0` +0xEFC counter were independently checked.
**Do not count these as whole game functions:** official exact
943/862,726 remains unchanged. The two other fighter owners
`0045DD70` and `0058AF60` have **131 native x86** in their action0x46
because of an additional stage-one projectile spawn and are still
unimplemented in this family. [F602 real trajectory](FIGHTER_TRAJECTORY_ACTION46_F602.md),
[natural C++](../probes/FighterTrajectoryContact46F602.inc).

```bash
scripts/repo-python scripts/verify-fighter-trajectory46-f602.py --boss 0x004F7130
```

**F603 completes real action0x46 source coverage in the remaining
TWO giant fighters `0045DD70` and `0058AF60`**. Their originals
have **131 distinct x86 instructions /459 bytes /16 real native
PE/COFF call/global fields each**, not F602's 104-instruction source.
A genuine stage-one `+0xF0C` one-shot projectile call to `00453A70`
spawns native IDs `0x3B7`/`0x3E7` with original side 1/0, and different
later game action thresholds. Newly compiled ordinary VC7.1 source
matches all **262 original x86 roles, 918 internal CODE bytes and
32 true typed COFF fields**, with all original prior 23 cases and
complete seven-switch afterRET table shape preserved in each
whole-giant source TU. Across F602+F603 **all 11 action0x46
original cases** have source proofs (1,198 roles/4,395 internal bytes/
167 authentic fields); combined with prior F598/F600 this is
**264 complete inner source cases/59,629 original interior CODE bytes**,
NOT 264 independent exact whole game functions. The eleven full
giant originals remain NONEXACT, all official 943/862,726 accepted
function counts unchanged. [F603 original projectile and complete
native case](FIGHTER_TRAJECTORY_SPAWN_F603.md),
[natural 131-insn C++](../probes/FighterTrajectorySpawn46F603.inc).

```bash
scripts/repo-python scripts/verify-fighter-trajectory-spawn-f603.py --boss 0x0045DD70
scripts/repo-python scripts/verify-fighter-trajectory-spawn-f603.py --boss 0x0058AF60
```

**F605** advances the same huge second-switch fighters by rebuilding
**both original actions `0x47` and `0x48` in all nine of the 104-instruction
`0x46` owners**. The whole native case has 86 x86 roles and 13 genuine
typed original COFF fields each: **18 cases /1,548 native x86 roles /
5,756 real original interior CODE bytes /234 typed fields**, including
the true `00564BE0` 28×3 widened `EBP−0x88` MOVs and one additional
4-byte near-branch expansion in *each* action. The original movement
copies a raw DWORD `+0x98` into `+0x54` instead of using `FLD/FSTP`.
Original stage/early/late constants are verified **independently per
action**, as some differ from action `0x46`. Each selected source
compile retains 23 earlier cases, all native action0x46 roles and
afterRET jump DATA. **Two other fighters** `0045DD70` and `0058AF60`
need genuinely different 113-instruction projectile-spawn source for
these follow-up actions. All full giant functions remain nonexact,
no independent action fragment credited. Across F598–F605:
**282 game inner case bodies /65,385 original internal CODE bytes
source-backed, but officially accepted authored coverage unchanged**.
[PE+VC7.1 original F605 evidence](FIGHTER_TRAJECTORY_FOLLOWUPS_F605.md),
[natural 86-insn cases](../probes/FighterTrajectoryFollowupsF605.inc).

```bash
scripts/repo-python scripts/verify-fighter-trajectory-followups-f605.py --boss 0x004F7130
```

**F606 completes the REAL 0x47/0x48 original source for the other
two projectile-spawning giant fighters**, with native complete code
at `0045DD70`: `0x47` **113/395 B, 14 typed fields** and `0x48`
**86/310 B, 13 typed fields**; and at `0058AF60`: both `0x47/0x48`
**113/395 B, 14 typed fields**. The surprising native difference
is that `0058AF60` `0x48` spawns original sprite `0x3E7` **AFTER**
its stage-2 auxiliary-state early exit, not before like `0x47`.
Separate ordinary C++ bodies preserve the actual stage-one guard,
byte direction and `+0xF0C` flag. **F606 adds 4 complete native
interior cases /425 GPR/x87/CFG roles /1,495 original CODE bytes
/55 physical COFF fields**, with all previous 24 action roles and
complete afterRET jump DATA preserved in freshly compiled source.
Combined F605/F606: all **22** 0x47/0x48 actions in 11 giants source-backed
(1,973 native x86 roles/7,251 original internal CODE bytes/289 typed
fields). Combined F598–F606: **286 native game action subranges/
66,880 original internal CODE bytes**, still **ZERO new complete
whole-fighter exact acceptance**; official 943/862,726 unchanged.
[Original F606 stage-one order evidence](FIGHTER_TRAJECTORY_FOLLOWUP_SPAWNS_F606.md),
[before-early-source](../probes/FighterTrajectoryFollowupSpawnF606.inc),
[after-early-source](../probes/FighterTrajectoryFollowupLateSpawnF606.inc).

```bash
scripts/repo-python scripts/verify-fighter-trajectory-followup-spawns-f606.py --boss 0x0058AF60
```

**F607** extended **nine** of the giant fighters to the true
second-switch action `0x49`, **99 complete native x86 roles and
15 typed original PE/COFF fields per case**: **891 native x86 roles /
3,241 original inner CODE bytes /135 genuine fields**. An initial
99/347-byte source had an incorrect `FLD` order and inter-branch
`JMP`; a real member-lvalue float equality and two separate C++
`break`s reproduce exact original **99/350-byte case geometry**.
Native `00564BE0` remains special at **441 bytes** due to 29
widened receiver reads and one genuine near-branch expansion;
`005AEEC0` still uses original +0xEFC signed-short trajectory
slots. Each freshly compiled parent object preserves all prior
26 game action case roles and every original afterRET jump table.
The **other two giant fighters** have different **118-instruction
action0x49** and must be studied separately. Across F598–F607,
**295 internal native case bodies /70,121 native CODE bytes are
source-backed, NOT whole game function exact credit**. All 22 giant
CODE bodies remain nonexact; official 943/862,726 unchanged.
[F607 original x87/CFG physical source](FIGHTER_TRAJECTORY_LANDING_F607.md),
[natural C++](../probes/FighterTrajectoryLanding49F607.inc).

```bash
scripts/repo-python scripts/verify-fighter-trajectory-landing-f607.py --boss 0x004F7130
```

**F608** reconstructed real 118-instruction projectile-spawning action
`0x49` in the two remaining giant fighters `0045DD70` and `0058AF60`.
Original native complete `0x49` cases are **420 bytes/118 x86/
16 authentic typed COFF fields each**. Stage-one/frame-zero flag
`+0xF0C` guards native game spawn `00453A70`, projectile IDs `0x3B7`
/`0x3E7`, side 1/0. The two true `FUCOMPP` float equality tests and
native `0x49` switch exits are preserved in natural C++.
Both newly compiled VC7.1 giant source objects retain the **previous
26 genuine game cases** and original afterRET DATA. F608 adds
**2 internal cases /236 x86 roles /840 original interior CODE bytes
/32 original physical typed COFF fields**. Combined F607/F608,
**all 11 original 0x49 cases source-backed** (1,127 original x86,
4,081 native inner CODE bytes, 167 fields). Across F598–F608:
**297 native internal game cases /70,961 original CODE bytes**
source-backed but **no new whole-game exact unit**; official 943/
862,726 stays unchanged. Full original [F608 projectile landing
study](FIGHTER_TRAJECTORY_LANDING_SPAWN_F608.md) and
[natural C++](../probes/FighterTrajectoryLandingSpawnF608.inc).

```bash
scripts/repo-python scripts/verify-fighter-trajectory-landing-spawn-f608.py --boss 0x0058AF60
```

**F610 restores full native inner case `0x4A` in NINE regular giant
fighter controllers**. All 9 selected newly compiled VC7.1 whole-parent
source probes have exact original **119/119 x86 GPR/x87/CFG roles and
19 authentic native PE/COFF target destinations** per case, for
**1,071 roles /4,028 internal original CODE bytes /171 true fields**.
The action contains real `ContactAt454EE0()` bounce branching, two
`__ftol2` projections, native action0x4C/0x61 transitions and
actor-specific original `PrepareActionAt453D60` call ordering.
Native `00564BE0` is wide at 556 bytes (38 real extra-wide saved-this
MOVs plus two genuine near Jcc, against 434 candidate source), and
native `005AEEC0` uses +0xEFC. Each newly compiled giant also retains
the earlier 27 original game case grammars and actual afterRET switch
DATA. The other two giants `0045DD70`/`0058AF60` have genuinely
**165-x86/589-byte action0x4A** with extra stage-one spawn work;
these remain undone. Across F598–F610: **306 original interior case
bodies/74,989 original inner CODE bytes studied, but NO whole-giant
exact source credit**; official 943/862,726 unchanged.
[F610 original whole-case evidence](FIGHTER_TRAJECTORY_BOUNCE_F610.md),
[actual natural C++](../probes/FighterTrajectoryBounce4AF610.inc).

```bash
scripts/repo-python scripts/verify-fighter-trajectory-bounce-f610.py --boss 0x004F7130
```

**F611 recovers the remaining TWO original native double-projectile
`0x4A` bounce cases** in giant fighters `0045DD70` and `0058AF60`.
Each complete native case is **165 x86/589 original inner CODE bytes /
21 genuine physical typed PE/COFF fields**. Their original-stage-one
and second collision-bounce paths EACH independently test flag
`+0xF0C`, set once, and may call actual `00453A70` with sprite
`0x3B7`/`0x3E7` (side 1/0), with original-stage and action policy.
Two newly built whole C++ giant translation units reproduce **330
original GPR/x87/CFG roles /1,178 native interior CODE bytes /42
actual typed fields**, preserve all 27 previous real game case
bodies and full original afterRET jump DATA. Combined F610/F611:
**all 11 native `0x4A` case subranges** (1,401 original x86 roles,
5,206 native internal CODE bytes, 213 real COFF fields) source-backed.
F598–F611 cumulatively: **308 studied original inner cases /76,167
original native CODE bytes**, still **NOT whole-giant exactness or
independent case acceptance**. All official 943/862,726 authored
whole-exact bytes unchanged.
[F611 true double-spawn source/PE evidence](FIGHTER_TRAJECTORY_BOUNCE_SPAWN_F611.md),
[natural C++](../probes/FighterTrajectoryBounceSpawn4AF611.inc).

```bash
scripts/repo-python scripts/verify-fighter-trajectory-bounce-spawn-f611.py --boss 0x0058AF60
```

**F613 restores real native action `0x4C` source across ALL ELEVEN
fighter giants**. The full original PE bounded case has 74 complete
native x86 GPR/x87/CFG roles and 14 authentic PE/COFF target fields
per fighter: **11 new original inner cases /814 original x86 roles
/3,210 native internal CODE bytes /154 physical typed fields**.
The real `I16(+0xF00/0xEFC)` one-time motion initialization calls
`0040FBB0(0,95.0f,0)`, but the float angle advance using original
`00657878` occurs **UNCONDITIONALLY outside that guard**. Initial
C++ wrongly scoped it inside: both sources were 74 x86/285 bytes but
the native ordinal-3 JNE had the wrong destination. Natural C++
correction reproduces original JNE to ordinal14 and full register/x87
roles. Native `00564BE0` stays 360 bytes (25 real widened EBP−0x88
receiver MOVs); `005AEEC0` retains actual +0xEFC trajectory.
Each newly compiled whole-giant source preserves all previous 28
native action case roles and full afterRET switch DATA, with all 14
new true COFF call/float targets checked. F598–F613 cumulative
**319 source-backed real game case interiors/79,377 original native
CODE bytes**: still NOT independent or whole-giant exact credit.
Official whole accepted 943/862,726 unchanged.
[F613 native recovery and original case control-flow proof](FIGHTER_TRAJECTORY_RECOVERY_F613.md),
[natural C++](../probes/FighterTrajectoryRecovery4CF613.inc).

```bash
scripts/repo-python scripts/verify-fighter-trajectory-recovery-f613.py --boss 0x004F7130
```

**F614 restores native action `0x58` in all ELEVEN giant fighters**.
The genuine packed second switch jumps from case0x58 dense slot17 to
case0x59 slot18. The complete original action contains a real **ten
projectile 0x3E4 loop**, conditional bonus `0x3E3` if signed-short
`+0xEFA >25`, and two original x87 `FUCOMPP` checks. Nine
original fighters use **135 x86 instructions** (eight normal
469-byte cases, real wide `00564BE0` 580 bytes/37 widened receiver
MOVs); `0045DD70` and `0058AF60` use **154 x86/539 bytes** with a
real additional `+0xF0C` once-only stage-one projectile `0x3B7`/
`0x3E7`. F614 adds **11 complete native internal cases /1,523
original x86 roles /5,410 uncredited original CODE bytes /189 actual
typed PE/COFF fields**. Every new giant source is independently
VC7.1 cold-compiled, retaining all prior **29 native game case
bodies and original afterRET packed DATA**. A reused variable in the
preliminary experimental harness initially omitted the special
branch; the actual source/PE recheck caught and corrected that
control-flow-source mistake before strict verification. F598–F614
cumulative: **330 original real game case interiors /84,787 native
internal CODE bytes**, not accepted whole-function CODE. All giant
parents remain NONEXACT; official 943/862,726 unchanged.
[F614 real original ten-burst and ABI source](FIGHTER_TRAJECTORY_BURST_F614.md),
[natural C++](../probes/FighterTrajectoryBurst58F614.inc).

```bash
scripts/repo-python scripts/verify-fighter-trajectory-burst-f614.py --boss 0x0045DD70
```

Never run a full 943-unit cold replay.

## 4. Other three unmatched authored *whole* functions

| Original | Size / native structure | Precise remaining blocker, best source evidence |
| --- | --- | --- |
| **`00602A60`** `GameApplication::Run` | **2,987 B; 654 original x86, 123 calls**, original 0x278 frame | F528 best normal C++ source emits 2,981 B /654 x86 but wrong native EBP owner local slots; inspect `.analysis/f528-winmain-native-initial-scene/`, [WinMain whole CFG](WINMAIN_ORIGINAL_CONTROL_FLOW.md). The original scene switch's 60 after-RET bytes are DATA |
| **`0043B0B0`** battle scene destructor | **248 B /75 x86 /12 original COFF fields** | True VC7.1 `/GX` ordinary C++ has **191/200** non-COFF bytes; nine different literal EBP temp slots for texture delete and three resource frees. [F589 native destructor probes](SCENE_TEXTURE_DELETE_CONTROLS_F589.md). No 248-byte exact credit |
| **`0041CE50`** archive catalog nonvirtual destructor | **171 B /51 x86 /14 real COFF fields** | Natural `/GX-` C++ has **108/115** nonrelocation bytes; original delete/filename temporary locals use different EBP ownership. F598 confirms direct filename `free` fixes the **resource** stack slots but incorrectly drops 2 native instructions (165 rather than 171 B); meaningful local filename source restores 171 B but shifts slots back. [F584 native archive delete experiments](ARCHIVE_DELETE_EXPRESSION_CONTROLS_F584.md) and [F598 small C++ negatives](FIGHTER_SINGLETON_CONTACT_F598.md). No 171-byte exact credit |

**F612 negative original SceneObject whole destructor audit:**
**22 independently compiled whole-source controls** tested actual
pointer types, const/volatile qualifiers, real three-free-resource
array orders, and genuine reference aliases. Original `0043B0B0`
is still **248 bytes/75 x86/12 true PE/COFF fields**; 16 natural
full-size forms are **191/200**, four natural index orders are
**189/200**, and two real pointer-reference alternatives compile
to **254 bytes/78 x86**, not original. Native EBP texture/delete
slots still require `−0x14/−0x10`, C++ currently `−0x20/−0x1C`.
No whole-original exactness or partial byte credit. The 22 targeted
native PE controls are reproducible via
[real original F612 pointer/field evidence](SCENE_DESTRUCTOR_POINTER_TYPES_F612.md):

```bash
scripts/repo-python scripts/verify-scene-freed-pointer-types-f612.py --case int-pointer
```

**F609 negative small-function research:** 19 freshly compiled
**whole 171-byte/51-instruction** ArchiveCatalog destructor source
variants (signed/unsigned/size_t loop indices, nested source scopes,
actual delete/free casts, pointer lvalues) preserve the **14 true
PE/COFF relocations** but all fail to reproduce native EBP temp
ownership: 18 forms are **108/115** original nonrelocation bytes,
`index!=Size()` is **107/115**. No whole destructor exact promotion.
[Reproducible F609 whole-original negative constraints](ARCHIVE_DESTRUCTOR_SOURCE_TYPES_F609.md),
[one selected native compiler check](../scripts/verify-archive-source-types-f609.py):

```bash
scripts/repo-python scripts/verify-archive-source-types-f609.py --case signed-index
```

Unknown provenance is **separate** from these authored nonexact
functions. F595 produced **40/40 byte-identical native C++** for
`004135F0` but it is **origin UNKNOWN**, zero registered direct
callers and no literal DWORD pointers; do not count in official
exact ledger. `00449DE0` has 36 original exact background-loader
callers yet implicit-vs-explicit constructor ambiguity; also
unknown. `004588B0` has six mixed vendor/game callers.
See [F595 original native small-function provenance](SMALL_ORIGIN_UNKNOWN_FIELDSETTER_F595.md)
and historical [origin review](ORIGIN_PENDING_REVIEW.md).

**F604 added two further complete original byte-identical small
source leaves with unknown provenance.** Original `00454C00`
(24 native CODE bytes/9 x86) naturally clears original receiver
`+0x47C`; `00454F70` (31 native CODE bytes/15 x86) reads the flags
at `(*[this+0x74])+0x3C` and returns `(flags & 0x20) > 0`.
Both whole native functions match **55/55 original machine-code
bytes** under pinned VC7.1 (no COFF relocations). The authentic
unsigned `>0` compiler sequence is `XOR/CMP/SBB/NEG`; equivalent
`!=0` compiles to a **nonexact 29-byte** negative control. An
independent re-scan of all 4,351 original function extents finds
zero direct `CALL` edges to either, and the executable has zero
literal DWORD references; that does **not** prove source ownership,
so **both stay `unknown`/`review` and uncredited**. The 943 authored
whole exact functions/862,726 bytes remain unchanged.
[Native full C++/negative controls](SCENE_FLAG_COUNTER_LEAVES_F604.md),
[actual natural C++](../probes/SceneFlagAndCounterLeavesF604.cpp) and
one selected local compiler verification:

```bash
scripts/repo-python scripts/verify-scene-flag-counter-leaves-f604.py --negative-predicate
```

Fresh source/local-type experiments also eliminated a `register`,
const, and pointer-alignment explanation for the original
`0041CE50` destructor's remaining EBP temporaries; it is still
**108/115 original comparable bytes**, not an accepted 171-byte
whole function. Full failed compiler observations retained privately.

**F601: original 21/37-byte float `atan2` forwarding/worker pair
whole-CODE C++ reconstructed, provenance still UNKNOWN.** Original
`00483300` → `00483320` → CRT `_atan2` `00642240` is confirmed by
all 25 original x86 instructions, both true original `REL32`
fields/callees and **58/58 linked original CODE bytes**, from one
ordinary cold VC7.1 source TU. An independent scan of all 4,351
registered native functions finds **211 direct CALLs from 16
independently authored game owners** to the front wrapper, and the
only direct worker caller is the wrapper. Game use **does not prove**
explicit author vs SDK compiler helper origin; **both remain unknown
and uncredited**, official 943/862,726 unchanged. New complete-source
witness [F601 original math adapter evidence](FLOAT_ATAN2_ADAPTERS_F601.md)
and [real C++](../probes/FloatAtan2AdaptersF601.cpp). Rebuild **only**
this one source TU:

```bash
scripts/repo-python scripts/verify-float-atan2-adapters-f601.py
```

F601 also independently tested the still-unmatched **171-byte archive**
and **248-byte scene** whole destructors using natural pointer/ref
interfaces, sequenced `delete/free`, real resource aggregate/lifetime
reordering. They remain **108/115** and **191/200** (or worse)
original nonfield matches respectively; no false exact credit. Native
EBP local placement remains the blocker; full source/COFF negative
receipts are retained privately and documented in the same F601 report.

**F599: two large, complete, original-PE-byte-identical natural C++
copy members now source-backed, but original provenance still UNKNOWN.**
`0045AAE0` / 368 B /118 x86 and `004591E0` /417 B /128 x86
are generated *implicitly* from one genuinely used 116-byte C++ record
with nontrivial member lifetimes. Their complete **785/785 original CODE
bytes, 753/753 non-relocation bytes and 8/8 real physical typed COFF
destinations** are identical after true relocation linking. The first
nontrivial member destructor and VC7.1 `/GX` frame reproduce both native
exception-state writes; `/GX-` is a negative control. The actual owner
and developer's implicit-vs-explicit syntax remain unproved, so **do not
count 785 source-backed bytes as newly accepted authored CODE**.
An independent original direct-call scan over all 4,351 registered
functions now finds **three distinct library-classified direct callers
for each**, without proving the original member owner or author.
[Complete F599 original source/ownership evidence](RECORD116_IMPLICIT_COPY_ORIGIN_F599.md),
[actual natural C++](../probes/Record116ImplicitCopyF599.cpp) and one
selected cold compile plus optional EH negative:

```bash
scripts/repo-python scripts/verify-record116-implicit-copies-f599.py --with-negative-gxoff
```

## 5. Required workflow and data acceptance

1. Inspect dirty Git changes immediately and **continue all of them**;
   this is a single working session. Reread the actual original PE
   instead of assuming any report, proposed class or previous probe
   is correct. Never skip giant bosses to do only easy leaves.
2. Keep genuine source C++ in tracked `src/` or `probes/`, original
   results/negative controls in ignored `.analysis/`, and preserve
   `resources/th075.exe`, `ghidra-project/`, shared VC7.1/Wine,
   `build/matching/`, all probe COFF objects and immutable adoption
   receipts. **Do not overwrite/delete meaningful dirty work.**
3. Compile **only the affected translation unit** under pinned
   headless VC7.1. For exact authored code, run **only**
   `scripts/repo-python scripts/replay-exact-units.py --unit UNIT_ID`;
   never omit `--unit`. Verify actual complete function CODE and
   every typed physical relocation; never grant CODE to an inner
   switch action or compiler/runtime helper.
4. Commit actual progress promptly with `gpt-web: ...`. Run
   `scripts/repo-python scripts/validate-tracking.py --require-target`,
   `scripts/repo-python scripts/audit-active-handoff.py`,
   `scripts/repo-python scripts/update-progress.py --check`,
   `git diff --check`. Run the *light* `scripts/ci.py` if changing
   verification/ledger infrastructure. No all-unit cold replay.

## 6. Storage protection, recovery and historical navigation

[Storage protection and recovery](STORAGE_HYGIENE.md) is binding.
`.analysis/vc71-wine/` (about **1.3 GiB**) is a working compiler
**dependency**, not old cache. Keep Ghidra project, original PE,
source, manifests, accepted match objects, native JSON evidence and
significant negative controls. Only remove demonstrably redundant
**reproducible** outputs after hash-verified *lossless* archival and
record restoration instructions in `STORAGE_HYGIENE.md`; keep archive
receipts. Old historical JSON/PDB snapshots were previously compressed.
F597 additionally archived **243 redundant pre-F301 CI output logs**
losslessly (108,699,966 original bytes → 13,829,049-byte tar plus
36,446-byte SHA256 receipt; **≈90.4 MiB saved**). Restore any one
with the exact command below; `--verify` rereads all member hashes:

```bash
scripts/repo-python scripts/archive-legacy-ci-logs.py --verify
scripts/repo-python scripts/archive-legacy-ci-logs.py --restore .analysis/f179-ci.log
``` Current F301+ experimental logs and all source/objects,
original PE, Ghidra, `.analysis/vc71-wine` and H184 protected
artifacts are unchanged.

The former 977-line active handoff was archived **losslessly as
tracked English source evidence**:
[Historical F540–F596 handoff](history/RE_HANDOFF_F540_THROUGH_F596.md).
The detailed 10K-line [knowledge base](KNOWLEDGE_BASE.md),
[older handoffs](RE_HANDOFF_HISTORY.md),
[reconstruction workflow](RE_WORKFLOW.md), and
[AGENTS.md](../AGENTS.md) remain searchable but older factual
snapshots must not override live native/tracking evidence.
