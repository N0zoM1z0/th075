# TH075 — active reconstruction handoff

**Maintained 2026-10-29 after F648.** This is the **only current task list**.
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

**F635 independent whole original `004EBDA0` typed-member compiler
hypotheses were negative.** Fresh pinned VC7.1 cold compilations of
**25 entire original 33,293-CODE-byte /8,789-x86 C++ source variants**
plus 438 separately owned afterRET DATA/682 zero-addend typed source
COFF fields tested original-bit-identical float-vs-integer member
stores, authentic C++ `*=`/lvalues, unsigned fade-byte and original
`0x38D/0x38E/0x3E3` source access types. **23 whole candidates
preserve every original x86 start/size/mnemonic and retain the
same 137 differing nonrelocation original bytes**, first native
whole x86 ordinal8076, case38D stage4. **Two `*=`/member-lvalue
versions worsen to 140 differing original bytes and shift actual
x87 instruction starts/widths at whole ordinals8081/8082**
(despite 8,789 x86 and same full original CODE size). No new exact
whole source or case credit; the tracked F596 best giant C++ source
remains untouched. [F635 full PE source compiler alternatives and
negative evidence](CHARACTEROBJECT_TYPED_MEMBER_CONTROLS_F635.md).

```bash
scripts/repo-python scripts/verify-characterobject-typed-member-f635.py --case 38d-zero-velocity-as-bits
scripts/repo-python scripts/verify-characterobject-typed-member-f635.py --case 38d-stage4-assign-op
```

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

**F617 investigates the following original 0x5D and 0x5E air
transitions across the 11 giant fighters without conflating success
and failure.** In six original whole-giant source compilations,
complete native action `0x5E` has **101/101 genuine GPR/x87/CFG
instruction roles** and 8 exact real PE/COFF targets each,
for **six strict internal cases /606 x86 roles /2,115 native
interior CODE bytes /48 true physical typed fields**. The native
physical `00564BE0` version is 430 bytes due to 31 widened EBP−0x88
receiver MOVs (normal 337). Correct natural C++ source requires two
**independent** native float-facing tests with member lvalue
`*(&F32(0x44))`; the first native JNE must reach the next comparator,
not skip both. **Every matching source's action0x5D still has 61
GPR/CFG-role mismatches**, despite equal x86 count/width and 8 typed
fields; original `00543210` 0x5E also has 61 wrong roles and was
**separately compiled as a negative control**. Other original actors
have 64/94/96/106-instruction variants that cannot reuse this source.
Each selected 0x5E source object retains all earlier **30 authentic
original game case roles and afterRET packed DATA** via targeted F614
checks. F598–F617 strictly source-backed **336 native internal game
case bodies /86,902 original inner CODE bytes**, zero new accepted
whole-function exact credit. All official 943/862,726 unchanged.
[F617 actual PE-native C++ role proofs and failures](FIGHTER_AIR_TRANSITION_F617.md),
[ordinary 101-x86 source](../probes/FighterAirTransitionCaseF617.inc).

```bash
scripts/repo-python scripts/verify-fighter-air-transition-f617.py --boss 0x0045DD70
scripts/repo-python scripts/verify-fighter-air-transition-f617.py --negative-actor
```

**F619/F620 investigate a different native 64/64/44-instruction
case family inside `005AEEC0` giant fighter.** Original 0x5D and
0x5E are **each 210 native bytes/64 x86/3 real COFF call fields**,
not F617's 101-x86 air grammar. Normal C++ reproduces complete
native size/instruction count/callees but still has **42 native
GPR/CFG source-role mismatches PER CASE**. The actual next case
`0x5F` has **44 native x86/144 original CODE bytes/3 typed call
fields**, and its natural C++ source is STRICT 44/44 GPR/x87/CFG
role-identical **only in a whole-parent source still using diagnostic
5D/5E placeholders**. When both real 64-instruction predecessor
C++ bodies are inserted in that same newly compiled parent, the
0x5F roles rotate and become **26 differences** as well. This
establishes the importance of *enclosing* source-register grammar;
no full three-case simultaneous exactness or whole giant credit.
F620 adds only **one strict original inner case /44 x86/144 native
internal CODE bytes/3 genuine typed COFF** to the bounded evidence,
bringing F598–F620 to **337 strict original game-case subranges/
87,046 original CODE bytes**. All official 943/862,726 authored
whole-exact units unchanged. [F620 strict positive and explicit
negative original PE proof](FIGHTER_SIMPLE_AIR_CONTEXT_F620.md),
[native-positive 0x5F source](../probes/FighterFacing5FF620.inc),
[native-geometry-only 0x5D/E source](../probes/FighterSimpleAirTransitionF619.inc).

```bash
scripts/repo-python scripts/verify-fighter-facing5f-f620.py
scripts/repo-python scripts/verify-fighter-facing5f-f620.py --negative-context
```

**F622** advances two entire giant fighter C++ sources to the
original native action0x62. Independent PE decoding proved the real
four unsigned collision status fields `+0x4E8/+0x4EC/+0x4F0/+0x4F4`
are a **four-way logical OR of >0**, not three-zero AND one-positive:
three original `JA` branches ENTER the counter assignment and final
`JBE` skips it. The two signed direction×`+0x4DC` paths set original
signed-short counter **1 or 2** at `+0xF00` (wide `00564BE0`) or
**`+0xEFC`** (`005AEEC0`), then use original `0040FA30/0040FAC0`
state transitions to 0x5F/0x5D/0x5E. Both full native cases are strict
**65/65 actual GPR/x87/CFG roles, 4 genuine typed PE/COFF fields
per giant**, giving **two new internal cases /561 native CODE bytes
/130 x86 roles/8 real call fields**. The wide actor has precisely
21 authentic widened EBP−0x88 receiver MOVs. Other original actors
still mismatch native registers: `0045DD70` has 40 wrong roles;
`004AC040` has 10 wrong roles in its actual 25-x86/87-byte case.
All **30 prior** original case source roles and complete afterRET
packed tables remain checked on the newly compiled whole-parent OBJ.
**Important old verifier fix:** `verify-fighter-actionzero-natural-source.py`
previously counted *all* native `JA` as indexed-switch default guards.
F622 filters only guards **before the last indexed dispatch JMP**;
original physical guard targets, jump counts, dense/sparse afterRET
DATA and previous F614/zero-case local regressions still pass.
F598–F622 cumulative **339 internal game case subranges /87,607
original native inner CODE bytes**, NO new accepted whole-fighter
exact functions. Official 943/862,726 unchanged.
[Original F622 unsigned OR and dispatch guard fix](FIGHTER_COUNTER_DISPATCH_F622.md),
[natural C++](../probes/FighterCounterDispatch62F622.inc).

```bash
scripts/repo-python scripts/verify-fighter-counter-dispatch-f622.py --boss 0x00564BE0
scripts/repo-python scripts/verify-fighter-counter-dispatch-f622.py --negative-actor 0x0045DD70
```

**F624** extends the two F622 giant fighter whole-source probes to
the genuine next packed action **`0x63`** (original final real sparse
slot25; slot26 is the DEFAULT handler, not the true source case end).
The real next physical game CODE handler is `0x8C`. Native original
mode byte `006714B4` has a **short-circuit `mode!=3 || +0x2CD==0`**:
original JNE ordinal2 targets ordinal7, JNE ordinal6 targets ordinal27.
The initial intuitive if(mode==3) source wrongly jumped to
ordinals27/26 despite 118/455 matching instruction geometry. The
original first branch of the second group **exits even if the bonus
flag is false** (native JNE ordinal54 targets case-exit ordinal58);
F624 corrects the C++ break position and independent original actor
bonus state: `00564BE0` flag4→action0x302, `005AEEC0`
flag5→action0x31D. Both freshly compiled whole giant C++ sources
now strictly match **118/118 real GPR/x87/CFG roles and 8 genuine
typed PE/COFF targets**, for **two new original inner cases /
1,007 original CODE bytes /236 x86 roles /16 real fields**.
The wide `00564BE0` case is 552 native bytes (31 EBP−0x88
receiver MOVs +3 B, native JLE near +4 B); `005AEEC0` is 455 B.
Each new object preserves previous **31** original game case source
proofs (including true four-way-OR action0x62) and full afterRET
packed switch DATA. F598–F624 bounded source study now documents
**341 strictly matching original interior case subranges /88,614
native original internal CODE bytes**, all still uncredited as
separate functions or fully matched enclosing giant source.
Official 943/862,726 authored whole-function exact unchanged.
[F624 real action0x63 mode/bonus CFG and native PE boundary](FIGHTER_MODE_EVENT_ACTION63_F624.md),
[ordinary C++ source](../probes/FighterMode63F624.inc).

```bash
scripts/repo-python scripts/verify-fighter-mode63-f624.py --boss 0x005AEEC0
```

**F626 extends the genuine original native action0x63 source to
FIVE additional giant fighter owners**, distinct from F624's two
118-instruction/bonus-branch actors. Here the actual native original
has **109 x86/417 CODE bytes and seven true PE/COFF fields** per
strict source, **without** the bonus `this+0x370` after original
`0x31C` transition. Native actors `004AC040`, `00486550`,
`00543210`, `004D7E70`, `005214B0` now source-match **545/545
original GPR/x87/CFG roles /2,085 original inner CODE bytes /
35 exact physical zero-addend PE/COFF destinations**, in **five
freshly compiled whole giant source TUs** retaining the prior 30
original source case proofs through 0x58 and full afterRET DATA.
Original packed slot25 is the LAST actual 0x63 handler in these
actors; slot26 is default, true next physical native game case is
0x8C. **Two other 109-instruction actors** `004F7130` and `0058AF60`
remain **67 register/CFG mismatches each** (after verified mode
DIR32); actual `0058AF60` has only 26 native compressed slots,
0x63 at index24 and next handler 0x89, not generic 0x8C. Their
source was independently compiled as honest negative controls.
A second untracked alternative verifier was inspected for useful
checks, then archived in ignored experiments to avoid duplicate
contradictory tools. F598–F626 strictly source-backed **346 real
native internal game cases /90,699 original inner CODE bytes**, NOT
new accepted whole functions or full fighter CODE. Official authored
943/862,726 unchanged.
[Original F626 native mode-event source and negative PE study](FIGHTER_MODE_EVENT_BASIC_F626.md),
[ordinary source](../probes/FighterMode63BasicF626.inc).

```bash
scripts/repo-python scripts/verify-fighter-mode63-basic-f626.py --boss 0x004AC040
scripts/repo-python scripts/verify-fighter-mode63-basic-f626.py --negative-actor 0x0058AF60
```

**F627** restores a THIRD actual original native case0x63
grammar, a **138-instruction priority bonus BEFORE ordinary action
0x31C**, for strict original fighter `005D73C0` (native 534 CODE
bytes /138 GPR/x87/CFG exact roles /8 genuine typed original
PE/COFF global and game-call targets). Real native first priority
branch checks signed byte `this+0x370[index] == 5` then
`this+0x32A[index] == 2`, sends `0040FAC0(0x303)` and **exits**;
the ordinary `0x31C` branch has its own later full guard. This
is not F624's optional after-31C bonus or F626's no-bonus variant.
Both native `005D73C0` and `0045DD70` use SECOND compressed
switch **26 slots, 0x63 at slot24**, next physical action0x8C;
the true shared slot25 default is not CODE case end. `0045DD70`
is a real **533-byte/138 x86** original negative; the same natural
source emits 534 bytes and **87 GPR/CFG errors**, intentionally not
credited. F627 contributes only **ONE strict source-backed inner
case /138 original x86 roles/534 native internal CODE bytes/8
real field targets**, with all 30 previous original game case and
separate afterRET DATA proofs rechecked in its whole-parent TU.
F598–F627 cumulative **347 source-backed internal native case
subranges /91,233 original inner CODE bytes**, NOT new complete
authored function exact credit; official 943/862,726 unchanged.
[F627 real original bonus-priority case evidence](FIGHTER_MODE_PRIORITY_F627.md),
[natural C++](../probes/FighterMode63PriorityF627.inc).

```bash
scripts/repo-python scripts/verify-fighter-mode63-priority-f627.py
scripts/repo-python scripts/verify-fighter-mode63-priority-f627.py --negative-actor
```

Never run a full 943-unit cold replay.

**F628** restores original complete 0x8C/0x8F/0x90 landing actions
inside **eight different huge fighter parents**, 3 actions each:
**24 original complete case interiors /1,920 native x86 GPR/x87/CFG
roles /7,152 original native inner CODE bytes /192 physically
original-targeted zero-addend PE/COFF fields**. Original x87
sequences prove strict `<` then `>` ground-bound correction against
float `0065782C` with delta `00658058`; real contact method
`00454EE0`, live signed member `+0x3BE` and **double-precision
`FMUL qword [006583E8]`** store reflection to `+0x490`; frame
getter/setter and stage3 signed short original `+0xF00/+0xEFC`
5/7 limit retain their actual per-actor values. The source
correctly handles original `00564BE0` 361-byte wide case with
24 authentic EBP−0x88 MOV receiver widths versus 289 compact.
**All eight source whole-giant objects also preserve a previously
native-strict 0x63**, including real F627 priority 138-instruction
source on `005D73C0`, plus all preceding F614 thirty native
case proofs and full afterRET DATA. Native `0045DD70`,`0058AF60`,
`004F7130` were separately cold-compiled and have **51 original
GPR/CFG role differences per 8C/8F/90 case**, despite correct
native byte count/COFF; none of those nine is claimed strict.
F598–F628 cumulative research **371 real strict internal game case
subranges/98,385 original inner CODE bytes**, ZERO new whole-giant
exact acceptance, official whole authored 943/862,726 unchanged.
[F628 genuine PE landing x87/typed fields and original negatives](FIGHTER_JUMP_LANDINGS_F628.md),
[natural C++](../probes/FighterJumpLandingF628.inc).

```bash
scripts/repo-python scripts/verify-fighter-jump-landings-f628.py --boss 0x005D73C0
scripts/repo-python scripts/verify-fighter-jump-landings-f628.py --negative-actor 0x0045DD70
```

**F629 original complete action0x91 in EIGHT giant fighter whole C++ source TUs**:
each real original compact case **78 x86/288 original CODE bytes/12
physical typed PE/COFF fields**; native wide `00564BE0` **363
original bytes**, 25 true saved-this `EBP−0x88` MOV widenings.
True stage1/2/3 condition `POS54 < original float 00657480` is
followed by native drag/ground float operations, two actual CRT
`__ftol2` transitions with original `00657888` projection and
signed short `+0xF00/+0xF02`, except `005AEEC0` **+0xEFC/+0xEFE**;
reset, original native action0x61 and frame auxiliary transitions
retain true original PE callee targets. All eight new full-giant
C++ objects revalidate previous **three F628 8C/8F/90 cases,
strict original 0x63 (including real F627 priority 138-x86),
previous 30 F614 cases and complete afterRET jump DATA**.
`004F7130` remains an honest **35 GPR/CFG-role mismatch** in 0x91,
correct count/COFF alone is not enough. Two other original bosses
have 105-x86 projectile version, not claimed. **F629 adds 8 strict
original inner cases /624 native x86 roles/2,379 original native
internal CODE bytes/96 real typed PE/COFF fields**, all *uncredited*
as independently callable or whole giant functions. F598–F629:
**379 original strict interiors /100,764 original inner CODE bytes**.
Official complete authored exact remains 943/862,726.
[F629 source/native role and PE evidence](FIGHTER_ARC_ACTION91_F629.md),
[natural C++](../probes/FighterArcTrajectory91F629.inc).

```bash
scripts/repo-python scripts/verify-fighter-arc91-f629.py --boss 0x005D73C0
scripts/repo-python scripts/verify-fighter-arc91-f629.py --negative-actor
```

**F630/F631 restore native complete action0x96 in ALL ELEVEN huge
fighter sources**, with a genuine **73-x86** timer/ground/contact
physics case in nine original actors and **75-x86** in original
`00543210`/`0058AF60` with extra signed-short `+0xF0A` reset.
The PE proves opposite real order: **0058AF60 BEFORE** the trajectory
counter/position, **00543210 AFTER** those stores. Natural VC7.1
C++ matches **all 807 native GPR/x87/CFG instruction roles,
3,126 original internal CODE bytes and 99 authentic zero-addend
physical PE/COFF refs** in 11 new selected whole-giant source
objects, including wide `00564BE0` native 342-byte 22-MOV expanded
frame, signed native `+0xEFC` counter for `005AEEC0`, genuine float
`0065747C/006583B4` animation cap, true double `FMUL qword
[006583E8]` reflection and native game calls. Each new C++ OBJ
independently rechecks **previous F628 landing three cases, native
0x63 when strict, prior 30 game-case grammars and all afterRET
packed DATA**. Eight previous F629 original 78-x86 0x91 cases
remain strict in these same new parent sources. Original `004F7130`
prior0x91 still has 35 native GPR mismatches. Actual two other
previous original F630 0x91 **105-x86/373 B** source grammars have
**13 physical PE/COFF sprite/CRT/game fields** but **55 native
register-role differences each**, and are NOT claimed strict; the
real two 0x91 projectile spawns each use original side **1** (sprite
`0x3B7`/`0x3E7`) rather than borrowing the earlier 0x46 side.
F631 adds **11 strict original internal case bodies /807 native
x86 roles/3,126 native inner CODE bytes/99 real targets**.
F598–F631 cumulative **390 strict internal original action subranges
/103,890 original native inner CODE bytes**, zero newly accepted
full authored functions or whole-giant exact CODE.
[F631 original true timer/byte-field/PE proof](FIGHTER_LANDING_TIMER_F631.md),
[ordinary timer C++](../probes/FighterLandingTimer96F631.inc),
[special earlier sprite negative C++](../probes/FighterArcSpawn91F630.inc).

```bash
scripts/repo-python scripts/verify-fighter-landing-timer96-f631.py --boss 0x0058AF60
scripts/repo-python scripts/verify-fighter-landing-timer96-f631.py --boss 0x00564BE0
```

**F633 reconstructs original complete native actions `0x97`,
`0x98`, and `0x9A` in ALL ELEVEN fighter giants**. Three physically
distinct complete original native cases per parent, with original
initial float heights −10f/−13f/−9f and real next action destinations
0/0/**2**, preserving the true extra short `+0xF0A` reset
**BEFORE** trajectory on native `0058AF60` but **AFTER** on native
`00543210`. Each new normal VC7.1 C++ enclosing giant source OBJ
has **all three newly strict 73/75 native GPR/x87/CFG case roles,
nine authentic typed PE/COFF fields per case**, and rechecks previous
F631 `0x96`, earlier F629/F630 `0x91` (including real known 35/55
register-role negatives), F628 three landing cases, native mode63
when strict, 30 earlier original game cases and entire afterRET
jump DATA. True wide `00564BE0` original is **342 native bytes** per
case versus compact 276 from 22 genuine EBP−0x88 wide MOVs;
`005AEEC0` uses real `+0xEFC` counter. F633 adds **33 strict
original inner case bodies /2,421 native x86 roles /9,378 native
internal CODE bytes/297 real typed fields**, all uncredited as
independent or wholly exact original functions. Cumulative F598–F633
strict original interior record is **423 cases /113,268 original
native inner CODE bytes**. Official 943/862,726 authored whole-exact
still unchanged.
[F633 original native case/PE/whole-source proof](FIGHTER_LANDING_SIBLINGS_F633.md),
[ordinary original-shaped C++](../probes/FighterLandingTimerSiblingsF633.inc).

```bash
scripts/repo-python scripts/verify-fighter-landing-siblings-f633.py --boss 0x0058AF60
```

**F634 complete original game-facing small leaves, zero source-origin
promotion:** three separate original registered whole CODE functions
`0040D980` (14/14 native bytes/8 x86, returns normal `this`),
`0040D9F0` (14/14 native bytes/8 x86, separate `this` identity) and
`0045B850` (13/13 native bytes/7 x86, normal empty method with one
argument and original `RET 4`) are **all entirely linked byte-exact**
from ONE new cold-compiled natural VC7.1 source TU, with **zero
physical original COFF fields**, no byte graft or ASM. Independent
original PE direct-CALL decode across all 4,351 native function
extents finds 16/3/14 actual uses; 14/3/14 CALL instructions are in
currently authored game callers (including four huge CharacterObject
functions for the 13-byte empty method). However native use and
source identity **do NOT establish author-vs-compiler provenance**:
original three rows remain `unknown`/`review`, so **no new accepted
authored whole function CODE credit**. [F634 complete source and
real native CALL provenance](GAME_OBJECT_ACCESSOR_LEAVES_F634.md),
[real natural C++](../probes/GameObjectThisAndNoopLeavesF634.cpp).

```bash
scripts/repo-python scripts/verify-game-object-leaves-f634.py
```

**F636 original native landing action `0x9B/0x9C` source extended to
ALL ELEVEN fighter giants:** real native physical boundaries
`0x9B→0x9C→0x9E` (no independent 0x9D). Two complete 73-x86
source cases each have real heights **−10f/−13f** and true next
**action 2**, not earlier `0x97/0x98` action0. Actor `005AEEC0`
retains real `+0xEFC` counter, `00564BE0` 342 native B per
case from 22 real saved EBP−0x88 MOVs widened 3 bytes; actual
`0058AF60` clears extra `+0xF0A` BEFORE trajectory while
`00543210` clears it AFTER, in their real 75-x86 native versions.
All **22 new internal case bodies**, **1,614 authentic GPR/x87/CFG
roles, 6,252 original uncredited inner CODE bytes, 198 actual typed
PE/COFF fields** are strict in fresh whole giant VC7.1 source TUs.
On each same new OBJ the verifier rechecks F633 `0x97/98/9A`
all three complete strict cases, F631 0x96, prior F629/F630
0x91 with honest 35/55-register-role negatives, F628 three
landings, mode0x63 where strict, 30 earlier original game cases
and complete original afterRET packed DATA. Cumulative F598–F636
**445 original strictly source-backed interior actions/119,520
original native internal CODE bytes**, **zero new accepted whole
native giant authored functions**. Official authored exact ledger
943/862,726 remains unchanged.
[F636 original real two-case PE+COFF and VC7.1 proof](FIGHTER_LANDING_PAIR_F636.md),
[reused natural C++ body](../probes/FighterLandingTimerSiblingsF633.inc).

```bash
scripts/repo-python scripts/verify-fighter-landing-pair-f636.py --boss 0x00564BE0
scripts/repo-python scripts/verify-fighter-landing-pair-f636.py --boss 0x0058AF60
```

**F637 recovers real native whole interior action0x9E in ALL ELEVEN
giant fighter source parents:** 66 authentic x86 normally /68 in
native `00543210`/`0058AF60` from extra `+0xF0A` store in opposite
AFTER/BEFORE motion-init order. Independently decoded original
`005D73C0` uses **strict `POS48 > ground`**, real native `TEST
AH,0x41` versus the other ten actors' **`POS48 >= ground`** with
real `TEST AH,1`; first natural C++ source had 1 real x87/CFG-role
mismatch here until the original equality behavior was fixed.
Ordinary VC7.1 source in 11 fresh whole `Advance()` C++ objects now
strictly matches **730 original native GPR/x87/CFG instruction roles,
2,760 original native inner CODE bytes and 88 genuinely typed
zero-addend PE/COFF global/call fields**. True wide `00564BE0`
306 native bytes have exactly 21 widened saved-this EBP−0x88 MOVs,
not source padding. Each new OBJ rechecks prior F636 original
`9B/9C`, F633 original `97/98/9A`, F631 `0x96`, actual earlier
mode/landing cases and entire afterRET compressed switch DATA.
**F598–F637 total strictly source-backed 456 original case
interiors/122,280 original inner CODE bytes**, still zero newly
accepted complete giant authored functions. Official whole-authored
943/862,726 exact unchanged. [F637 real original strict x87
condition, source and native field proof](FIGHTER_GROUND_BOOST_F637.md),
[ordinary C++](../probes/FighterGroundBoost9EF637.inc).

```bash
scripts/repo-python scripts/verify-fighter-ground-boost-f637.py --boss 0x005D73C0
scripts/repo-python scripts/verify-fighter-ground-boost-f637.py --boss 0x00564BE0
```

**F638 reconstructs FOUR more complete original small game-facing
constructors, with strict origin uncertainty:** native `00458670`
(base virtual table `0065904C`, **23/23 original whole CODE B**),
`00458650` (actual base call then derived vtable `00659038`, **31/31
B**), `004251C0` (native vtable `00657B88` and nontrivial member
ctor `00417210` at +4, **34/34 B**) and `00411C10` (nonvirtual
member ctor `0040D990` at +4, **25/25 B**) are each **complete
native whole byte-exact**, not switch fragments. TWO independent
ordinary pinned VC7.1 source TUs—**explicit** and completely
**implicit** default constructors forced by genuine placement-new—
reproduce **113/113 original whole CODE bytes, 46 actual native x86,
6 real PE-targeted zero-addend typed COFF fields**. Original 4,351
registered CODE extents independently show 2/2/15/1 true CALLs,
with 1/2/15/1 from currently authored game callers. But explicit
versus compiler-generated special-member origin cannot be inferred
from identical machine-code and callers: original four functions
remain `unknown`/`review`, ZERO new authored exact ledger credit.
With F616/F618 constructors and F634 complete game leaves, **11
distinct whole original functions /287 original CODE bytes** are now
source-backed but uncredited pending actual authored provenance.
[F638 fully linked original PE and two source modes](GAME_INHERITANCE_CONSTRUCTORS_F638.md),
[explicit source](../probes/GameInheritanceAndMemberConstructorsF638.cpp),
[implicit](../probes/GameInheritanceAndMemberConstructorsImplicitF638.cpp).

```bash
scripts/repo-python scripts/verify-game-inheritance-constructors-f638.py
```

**F639** restores all three original native `0x9F/0xA0/0xA1`
complete landing cases in **ALL ELEVEN whole giant fighter C++
parents**. Original real x86 CODE boundaries are 0x9F→0xA0,
0xA0→0xA1, 0xA1→0xA3. Native start heights −9f/−10f/−13f,
actual following action0/0/0, true original double reflection and
all **nine original typed physical PE/COFF call/global fields per
case** strictly match GPR/x87/CFG/width roles in newly rebuilt
VC7.1 source. **33 complete original inner cases /2,409 native
x86 roles /9,306 original uncredited native inner CODE bytes /
297 physical PE-target COFF fields**. Native `00564BE0` is 342 B
per case from 22 real EBP−0x88 MOV receiver widenings. Important:
**original `00543210` and `0058AF60` have only 73 x86 here**;
their prior 75-x86 real extra `+0xF0A` reset is an EARLIER-action
feature, not a global per-character rule. On the same new giant OBJ,
previous strict F637 `0x9E`, F636 9B/9C, F633 97/98/9A,
F631 96, earlier mode and 30 real action sources and complete
original packed afterRET DATA remain checked; negative previous
0x91 register cycles remain nonexact. F598–F639 cumulative study
**489 strict native original case interiors /131,586 original
native inner CODE bytes**, still ZERO newly accepted whole-giant
functions/credited authored bytes. Official 943/862,726 unchanged.
[F639 real source/PE original case geometry and role proof](FIGHTER_LAST_LANDINGS_F639.md),
[ordinary natural C++ source](../probes/FighterLandingTimerSiblingsF633.inc).

```bash
scripts/repo-python scripts/verify-fighter-last-landings-f639.py --boss 0x00543210
scripts/repo-python scripts/verify-fighter-last-landings-f639.py --boss 0x00564BE0
```

**F640 reconstructs TWELVE further COMPLETE original game-facing
small functions** from one ordinary VC7.1 C++ TU, **203/203 entire
original native machine CODE bytes, 99/99 complete x86 instruction
roles and 10 genuine original typed zero-addend PE/COFF REL32 calls**.
Six original `17B` single-argument forwarding wrappers
(`0040D900`,`0040D940`,`00412D90`,`00428D20`,`00449A60`,
`00438A60`), two original `11B` no-op thiscall methods
(`004073A0`,`00438CF0`), three genuine `19B` receiver forwarding
methods (`0040DE30`,`0040DF40`,`0040D8E0`) and real `22B` first-
member constructor `0040D8C0`. Every original PE callee address,
whole function length and original complete native CODE byte are
strictly linked and checked. Direct PE CALL scan covers all
**4,351 registered original CODE extents** with concrete game uses.
**Original type/signatures and author-vs-generated ownership remain
UNKNOWN** despite machine-code identity and game callers; all 12
retain `unknown`/`review` and **zero authored exact acceptance**.
Combined F616/F618/F634/F638/F640 study: **23 distinct entire
original functions /490 whole native CODE bytes**, source-backed
but still uncredited. [F640 actual PE-linked byte/source/caller
proof](GAME_CALL_FORWARDERS_F640.md),
[natural C++ grammar](../probes/GameCallForwardersF640.cpp).

```bash
scripts/repo-python scripts/verify-game-call-forwarders-f640.py
```

**F641 original native counter-free timed landing cases `0xA3/
0xA4/0xA5` rebuilt in ALL ELEVEN huge fighter whole-source
VC7.1 translation units.** Three physically separate original
A3→A4→A5→A7 case bounds each own **71 native x86** and genuine
heights **−9f/−10f/−13f**, each completing to native **action 2**.
Unlike prior 73/75-x86 F633/F639 landing cases, original A3/A4/A5
**do NOT clear `+0xF00/+0xEFC` trajectory shorts or `+0xF0A`
extra flag**. Correct natural source
[`FighterLandingNoCounterF641.inc`](../probes/FighterLandingNoCounterF641.inc)
reproduces all genuine native x87 ground/contact/double FMUL
and game call roles, **33 strict original internal case bodies,
2,343 actual x86 GPR/x87/CFG roles, 8,901 uncredited native
CODE bytes and 297 real physical PE/COFF targets**, including
`00564BE0` wide original 327-byte cases from exactly 21 real
saved EBP−0x88 MOV widenings. Same new objects recheck earlier
F639 9F/A0/A1, F637 9E, F636 9B/9C, F633 97/98/9A,
F631 96, native mode63 where previously strict, 30 older native
case proofs and entire separately owned afterRET packed jump DATA;
previous original GPR-negative cases remain negative. F598–F641
strict original interior record: **522 case bodies /140,487 native
original inner CODE bytes**, still **zero accepted new whole-giant
source or authored CODE**. Official 943/862,726 exact ledger
unchanged. [F641 original per-case counter-free/native PE proof](FIGHTER_NO_COUNTER_LANDINGS_F641.md).

```bash
scripts/repo-python scripts/verify-fighter-no-counter-landings-f641.py --boss 0x00564BE0
```

**F642 genuine original 97-x86 projectile-launch actions A7/A8
restored in ALL ELEVEN huge fighter parent TUs**. Authentic two
complete original handler ranges (A7→A8→B4) include real signed
char direction*30 x coordinate (`IMUL/FILD`), y float member+global,
`0046D000(0xFA)` animation, `00453D60(0x2C)` prep,
`00453C80(kind0x38, side1)` sprite, real signed-short cooldown
0xB4 with native `+0xEFC` for `005AEEC0`, native `FILD` bounce
`FMUL [006590B4]` and decrement10, ending in game action 0/2.
**19 whole-giant VC7.1 source trials** established `F32(0x48)`
member access (not generic `POS48` alias) gives original native
`FLD member; FADD [00657888]` pair at x8634/35. All **22 new
native inner cases /2,134 actual GPR/x87/CFG roles /7,918 original
internal CODE bytes /264 exact physically typed PE-target COFF
fields** now match in the new *whole-parent* source objects.
Original `004AC040` has four widened original MOV/FILD integer
scratch accesses (+12 bytes/case); `00564BE0` original 447-byte
case has 27 saved-this receiver MOVs widened +3, FOUR real
integer scratch MOV/FILD widened +3 and one near JNE +4, not
31 receiver MOVs. Every new parent OBJ rechecks all previous
F641 A3/A4/A5, F639 9F/A0/A1, F637 9E, F636 9B/9C,
F633 97/98/9A, earlier native mode, 30 previous game cases and
complete original afterRET packed DATA. Whole originals are still
NONEXACT. F598–F642 strict original interior study **544 cases
/148,405 original inner CODE bytes**, **zero new fully exact
whole-giant functions or accepted authored CODE**; official
943/862,726 whole exact ledger unchanged.
[F642 real original projectile/x87/FILD/PE field source proof](FIGHTER_PROJECTILE_LAUNCH_F642.md),
[natural C++](../probes/FighterProjectileLaunchF642.inc).

```bash
scripts/repo-python scripts/verify-fighter-projectile-launch-f642.py --boss 0x00564BE0
scripts/repo-python scripts/verify-fighter-projectile-launch-f642.py --boss 0x004AC040
```

**F644 six more full original byte-matched native x87 math
adapters:** `0040D920`,`0040D960`,`00412DB0`,`00428D40`,
`00442040`,`00449A80`, each **28/28 original whole native CODE
bytes /12 complete x86 instructions /one real PE-targeted typed
zero-addend REL32 CALL**. Genuine natural C++ float argument→double
`FLD dword; SUB ESP,8; FSTP qword [ESP]`, real native double
callee, `FST dword [EBP−4]` rounded float return, original frame
and `RET` all reproduce **168/168 full original machine bytes,
72 native x86 roles, six physical COFF fields**. Original all-4,351
registered CODE call graph finds one real direct caller each, one
currently authored round-banner caller and five origin-unknown F640
source wrappers. Original six functions' historical explicit-
authored-vs-generated/library origin remains `unknown`/`review`,
so **ZERO new accepted authored exact match units or CODE bytes**.
Combined F616/F618/F634/F638/F640/F644 complete source-backed but
origin-unknown study **29 distinct whole native functions /658
native CODE bytes**, all uncredited; official 943/862,726 whole
exact unchanged. [F644 original full PE/x87/C++ source proof](GAME_FLOAT_MATH_ADAPTERS_F644.md),
[ordinary C++](../probes/GameFloatMathAdaptersF644.cpp).

```bash
scripts/repo-python scripts/verify-game-float-math-adapters-f644.py
```

**F645** reconstructs real native original motion restart cases
`0xB4/0xB5` inside ALL ELEVEN fighter giant C++ parent source TUs.
Actual original physical next handlers **B4→B5→C8**, NOT the B6
common default. Original game stage0 reset `00453E20`, +8f/−8f
initial height, +12.5f velocity/+0.75f drag, `0040FC50` motion reset,
strict native `POS48 > [0065782C]` and ground-cross transition to
native `0040FAC0(0xA)`. Each frame-complete auxiliary `0040FB40`
argument is actor/action-specific (native original B4/B5: 7/5,
8/10, 7/7, 6/6 or 7/6). The original has **two separate final JMP
instructions**, requiring a natural C++ `break` INSIDE the auxiliary
conditional and another `break` OUTSIDE. The first 59-x86 source
is not accepted; F645 normal C++ now recovers **22 distinct whole
native interior cases /1,320 x86 GPR/x87/CFG roles /4,850 original
inner CODE bytes /176 true physical typed PE/COFF refs** in eleven
fresh entire fighter C++ parent objects. Genuine wide `00564BE0`
has 20 saved-this EBP−0x88 receiver MOVs widened +3, native 275B
per case versus 215B compact. Each newly built giant source also
rechecks previous F642 projectile A7/A8, F641 71-x86 landings,
F639/F637/F636, native mode when strict, older 30 native game
cases and full original afterRET packed jump DATA. F598–F645
cumulative source-backed study **566 original native action interiors
/153,255 original internal CODE bytes**, STILL ZERO additional
whole-giant exact source or accepted authored CODE. Official
943/862,726 whole authored exact unchanged.
[F645 original actual B4/B5/C8 C++/PE/COFF proof](FIGHTER_MOTION_RESTART_F645.md),
[natural C++](../probes/FighterMotionRestartB4F645.inc).

```bash
scripts/repo-python scripts/verify-fighter-motion-restart-f645.py --boss 0x00564BE0
scripts/repo-python scripts/verify-fighter-motion-restart-f645.py --boss 0x00543210
```

**F648 eight more COMPLETE pinned original native game-facing leaf
functions** from one ordinary VC7.1 C++ TU: 16-bit thiscall setter
`00410FC0` (**24/24 original CODE B**), `0045B6F0` real pointer
+16/return-this (**27/27 B**), `00458770` native member+4
forward (**22/22 B**), `004229D0` constructor member+0 call and
thiscall `RET 4` (**28/28 B**), plus four complete 15B one-arg
pointer-wrapper/zero-state call adaptors `0040F9F0`,`004229C0`,
`0045B6B0`,`005FAAD0`. All **161/161 native whole linked bytes
/73 actual original x86 roles/6 genuinely typed original PE-target
zero-addend REL32 COFF calls** are verified; original 4,351
registered CODE-extents direct-CALL scan independently finds one
real use per leaf except zero direct callers to 00410FC0.
Original current callers are primarily STL construct/destroy and
compiler-like sources; those labels and full machine-code identity
**do NOT prove** historical explicit user source vs compiler/library
origin. All eight original `unknown`/`review` rows remain pending:
**ZERO accepted authored whole CODE**. F616/F618/F634/F638/F640/
F644/F648 complete source-backed origin-unknown whole functions total
**37 originals/819 original CODE bytes**, all uncredited.
[F648 native full linked-source and caller proof](GAME_STATE_FORWARD_LEAVES_F648.md),
[normal C++](../probes/GameStateSetterAndMemberForwardF648.cpp).

```bash
scripts/repo-python scripts/verify-game-state-forward-leaves-f648.py
```

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

**F615 original complete WinMain native local-layout controls:**
Thirty separately *cold-compiled, whole function* natural VC7.1 C++
source variants for authored `00602A60` examine actual used objects:
scene pointer/path aggregate field orders, real MSG/WNDCLASSEXA lexical
placement, genuinely used HWND/event/metric locals and meaningful
predeclarations. The native remains **2,987 CODE bytes/654 x86,
123 calls and 60 separate afterRET DATA bytes**. Every compiled
candidate retains **654/654 native mnemonic order, 173 source COFF
fields including scene switch, but none has 2,987 original CODE
bytes**; generated lengths are **2,930–3,053 B**. One candidate
naturally moves path to genuine original `EBP−0x180` but source
scene pointer stays wrongly at `−0xC` and total CODE becomes **2,930**.
Another reaches 627/654 equal instruction widths but source code is
3,026 B. Reproducing one stack slot or mnemonic order does **NOT**
make authored whole WinMain exact. All thirty are explicitly NONEXACT,
no F528 provenance/ABI assumption is accepted without original proof.
[Full original F615 real local-lifetime evidence](WINMAIN_LOCAL_OBJECT_LAYOUT_F615.md),
[whole exploratory C++](../probes/WinMainLocalLayoutF615.cpp), targeted:

```bash
scripts/repo-python scripts/verify-winmain-local-layout-f615.py --case msg-before-app-plus-all-hwnd-event-int
```

**F632 independently compiled 15 whole original authored destructor
source-alternative tests**, targeting true local pointer assignment
inside the actual CRT `free(...)` argument instead of a separate
statement. Eight actual ArchiveCatalog source forms stay **171/51
native-shaped x86, 14 real COFF fields but only 108/115 original
nonrelocation bytes**, the same three wrong EBP slots. Four real
SceneObject aggregate `free(assignedPointer)` and comma/cast/identity
forms remain **248/75, 12 true COFF, 191/200 nonfield bytes**;
three individual named-pointer alternatives are **189/200**.
All still assign texture/delete locals `−0x20/−0x1C`, not original
`−0x14/−0x10`; no complete authored exact source credit.
This rules out a further class of ordinary expression-order fixes
without falsely asserting historical object ownership. [F632
full original PE/COFF and assignment-argument negative controls](DESTRUCTOR_FREE_ASSIGNMENT_F632.md).

```bash
scripts/repo-python scripts/verify-destructor-free-assignment-f632.py --case archive-ptr-in-free-arg
scripts/repo-python scripts/verify-destructor-free-assignment-f632.py --case scene-three-assignment-args
```

**F625 complete small-authored destructor native lifetime research:**
Two true original **WHOLE functions**, native `0041CE50`
**171B/51 x86/14 COFF** and original scene EH `0043B0B0`
**248B/75 x86/12 COFF**, have a common actual VC7.1 stack
allocator effect. When the borrowed filename or each of three game
resource pointers is passed directly to CRT `free` without an
independently named source local, C++ **naturally restores both
original deletion-resource EBP slots**: archive `−0xC/−0x8`,
scene texture/delete `−0x14/−0x10`. BUT those source forms emit
**165B/49 x86** and **230B/69 x86** respectively, rather than
native 171/51 or 248/75. They drop precisely the original two
archive filename or six scene free-value store/reload instructions,
so neither is whole-function exact. Separately recompiled 20 C++
archive materialized reference variants and 19 scene local/aggregate
source variants retain wrong native EBP slots or wrong full CODE
sizes; no fake padding, ABI mismatch or partial exact credit.
[Full original F625 direct-free source and EH/stack lifetime
proof](DESTRUCTOR_DIRECT_FREE_LIFETIMES_F625.md),
[archive C++](../probes/ArchiveCatalogDirectFreeF625.cpp),
[scene C++](../probes/BattleSceneDirectFreeF625.cpp).

```bash
scripts/repo-python scripts/verify-destructor-direct-free-f625.py --which archive
scripts/repo-python scripts/verify-destructor-direct-free-f625.py --which scene
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

**F618 another COMPLETE original native game background constructor
`00449DE0` reconstructed with two independently matching C++ sources,
provenance still unknown.** Entire original **45 CODE bytes/16 x86**
set the genuine vtable `0065844C` and construct two members at
`this+4` (`00412620`) and `this+0x18` (`0040AD80`). Both an explicitly
written empty constructor and an **implicit compiler-generated**
default constructor triggered by real placement-new reproduce
**45/45 fully linked native bytes**, with 3 original physical typed
PE/COFF fields and 33/33 nonrelocation bytes. Independent scan of
4,351 native function extents verifies **36 real direct CALLs** from
36 authored background-stage loading functions to this ctor. Caller
ownership cannot choose between explicit and implicit construction:
**native callee stays `unknown`/`review`; zero authored CODE credit.**
Combined F616/F618: four whole-original source-backed ambiguous game
constructor bodies/133 native CODE bytes, all **uncredited**.
[F618 native full ctor evidence](BACKGROUND_OWNER_CONSTRUCTOR_F618.md),
[explicit](../probes/BackgroundOwnerConstructorsF618.cpp),
[implicit](../probes/BackgroundOwnerConstructorsImplicitF618.cpp).

```bash
scripts/repo-python scripts/verify-background-owner-constructor-f618.py
```

**F616 three original COMPLETE constructor CODE bodies rebuilt from two
independent ordinary VC7.1 source grammars; provenance still UNKNOWN.**
The exact original PE function boundaries are `004251C0` (34 B/13 x86,
real vtable `00657B88`, real member ctor call `00417210`),
`00458670` (23 B/10 x86, real vtable `0065904C`) and `00458650`
(31 B/12 x86, actual base ctor call `00458670` and derived vtable
`00659038`). Both C++ source alternatives—explicit empty constructors
**and** compiler-generated implicit default constructors through real
placement-new—cold compile to **all 88/88 linked native CODE bytes**
after verifying every one of the **five true original typed PE/COFF
fields**, 35 native x86 and destination symbols. Real original 4,351-
function direct-call scan finds 15 authored scene initializers calling
the scene ctor, 2 authored game callers of derived ctor, and 2 real
base callers. Game usage does NOT establish explicit-vs-implicit
source provenance: **all three remain `unknown`/`review`, with zero
accepted authored CODE byte credit**. [F616 full original native
constructor proof](NATIVE_GAME_CONSTRUCTORS_F616.md),
[explicit C++](../probes/NativeGameConstructorsF616.cpp),
[implicit generated source](../probes/NativeGameConstructorsImplicitF616.cpp).

```bash
scripts/repo-python scripts/verify-native-game-constructors-f616.py
```


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
