# TH075 — CURRENT AGENT HANDOFF (2026-11-06, F1200)

**Start here.** Work on both large/core original functions and smaller entire
original functions. The user requests meaningful **multiple local commits** named
`gpt-web: ...`, wants all dirty work continued rather than discarded, and forbids
a complete 982-unit cold replay. Read [AGENTS.md](../AGENTS.md),
[the whole-function build workflow](RE_WORKFLOW.md), and
[storage and recovery](STORAGE_HYGIENE.md). The original Japanese PE,
`config/function-origins.csv`, exact `config/match-units.toml`, current
pinned-VC7.1 source builds and local Git status supersede all past F-series
research prose. **Do not infer completion, exactness, or original ownership
from an internal native case, mnemonic count, or identical source bytes.**

## 1. Original native PE and complete-function exactness

| Verified source of truth | Current factual status |
| --- | --- |
| Target | User-supplied Japanese TH075 v1.11 `resources/th075.exe` |
| Target SHA-256 | `bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98` |
| Provisional original function candidates / origin unknown | **4,351 /95** (3,420 uncredited CODE B) |
| Independently attributed original authored functions | **1,004** |
| **Accepted complete original exact callables** | **982 units, 871,649 original CODE B** |
| Reviewed authored byte exactness | **871,649/1,973,704 = 44.16%**; conservative **44.09%** |
| **Whole authored originals remaining NONEXACT** | **22 =22 giant (1,102,055B) +0 other (0B)** |
| Completion objective | 98% authored CODE target **NOT achieved** |

**982 functions / 982 exact units**, **871,649 original CODE bytes**;
reviewed denominator **1,973,704**, coverage **44.16%** / **44.09%** conservative.
**1,004** authored originals; **22 authored functions remain nonexact**:
**22 large original state advances** (**1,102,055 CODE bytes**) and
**0 other original small/medium whole functions** (**0 CODE bytes**).
Read the live ledger rather than inferring coverage from research cases.

**No recently recovered Boss *inner state* has independently added an
accepted whole-function exact unit.** Source refactors of already accepted
functions also add zero new exact bytes. Do not count the 95 origin-unknown
candidates as authored without independent evidence. Read the current ledger
with `scripts/repo-python scripts/report-reconstruction-status.py --summary`.

## 2. Primary large Boss — original 0050A580 (81KB)

Current tracked parent: [`probes/CharacterObjectWhole0050A580F1044.cpp`](../probes/CharacterObjectWhole0050A580F1044.cpp),
with genuine included `CharacterObjectBoss*.inc` game-state sources.
Single source/whole-parent verifier:
[`scripts/verify-characterobject-current-recovered-f1068.py`](../scripts/verify-characterobject-current-recovered-f1068.py).

| Independently checked property | Original PE | Current partial C++ |
| --- | ---: | ---: |
| Entire callable CODE | **81,539B** | **81,542B** (**+3B**) |
| Entire native x86 instruction count | **17,435** | **17,435** |
| Actual saved-this stack slot | **EBP-0xAC** | **EBP-0xAC** (verified) |
| Actual frame allocation | **ESP 0x3A0** | **ESP 0x3A0** (verified) |
| Native EBP stack operand positions | **5,717** | **5,717/5,717** |
| Whole native GPR-role /width debt | **17,435 x86** | **522 wrong GPR positions /5 wrong widths** |
| Owned separately afterRET switch DATA | **567B** | **567B** (verified) |
| Strict original inner case intervals | — | **83 cases; 76,519 original CODE B /16,367 native x86 mnemonic+GPR matches** |
| Original physical external PE fields in those 83 cases | **1,275** | **1,275/1,275** |
| All whole CODE reference destinations | **1,357** | **1,357/1,357 at native instruction/field positions** |
| Dense DIR32 table destination instruction ordinals | **92** | **92/92** |
| Original scalar immediate positions in those cases | **3,013** | **3,013** |
| Explicit GPR-provisional case intervals | — | **8 cases:** `0x358–0x35E` and `0x3E6` |
| Original `0x391` x87 equality loads | **29 external PE fields /277 x86** | **all PE fields, mnemonic/GPR/width positions verified** |
| Actual direct intra-function branches audited by native target ordinal | **1,834** | **all 1,834 destinations match** |
| **Whole original callable accepted exact** | — | **NO** |

The 83 strict cases **are interior evidence, not accepted independent
functions**. F1140–F1148 restore the actual scopes and all direct targets;
the [complete CFG proof](CHARACTEROBJECT_NATIVE_ALL_DIRECT_CFG_F1148.md)
indexes the current native conditions. The
[3E3/3E4 hit/return proof](CHARACTEROBJECT_NATIVE_HIT_RETURNS_CFG_F1147.md)
supersedes F1132's positive-cooldown continuation interpretation.

The live parent verifier independently requires **zero mismatches across
all 1,834 original direct jump target ordinals**. This proves those direct
edges, not original stack slots, GPR roles or
whole-function byte equality. F1149 resolves both original `0x391` FUCOMPP load orders using the existing
borrowed transform field, verified across all 29 PE fields and 277 native
mnemonic/GPR/width positions; see [typed x87 source proof](CHARACTEROBJECT_NATIVE_391_TRANSFORM_X87_F1149.md).
F1150 recovers the original frame and all EBP stack offsets through genuine
expression temporaries and a shared 38A loop index; see [native stack proof](CHARACTEROBJECT_NATIVE_ALL_STACK_SLOTS_F1150.md).
F1158 verifies the complete operand grammar and all 1,357 CODE field destinations,
plus the true native instruction destination of each of the 92 dense entries.
The two helper parameter views now agree with the existing exact helper sources,
without changing emitted CODE/DATA or physical field geometry;
[whole operand and indirect-target proof](CHARACTEROBJECT_WHOLE_OPERAND_PROOF_F1158.md).
F1181 reconciles seven narrow effect/sound parameter declarations (six native
callees), preserving all **82,109 candidate CODE+DATA bytes** and all 1,449
physical COFF field shapes. The 202 changed decorated names retain their
native destinations. Raw coordinate/angle DWORD transport is deliberately
preserved: a float-lvalue argument experiment adds 329 instructions and is
rejected. [Native parameter/transport proof](CHARACTEROBJECT_NATIVE_EFFECT_ABI_F1181.md).
Remaining work is original GPR roles in 358–35E and 3E6, with five instruction
width differences in 35B/35E/3E6. The source is only 3B longer but remains NONEXACT.
Earlier [F1128 attempts](CHARACTEROBJECT_NATIVE_391_392_393_F1128.md)
remain negative historical evidence, not a current x87 blocker. `0x3E6` retained **105/105 native mnemonics and 9/9 PE fields**
but only **30/105 native GPR positions**. Ten isolated 3E6 and eleven
preceding 3E5 full-parent grammar tests were unsuccessful (retained
under ignored `.analysis/f1137-*`). Four additional typed-parent-action /preceding
transform-assignment full-parent probes after F1150 likewise leave all 522
GPR differences unchanged (`.analysis/f1151-native-gpr-types/`); those
negative sources are retained and were not adopted.

F1194 also rules out nesting the first 358/3E6 conjunction guards: all
82,109 candidate CODE+DATA bytes and 1,449 field shapes remain identical,
with the same 522 GPR /five-width debt. This is another bounded negative
control, retained under `.analysis/f1194-native-guard-topology/`.

**Reproduction:**

    scripts/repo-python scripts/verify-characterobject-current-recovered-f1068.py

No need to replay all 982 exact units. This cold-rebuilds ONLY the
one affected partial Boss source. F1138 introduced 358 genuine phase
and meter borrows in 72 action files while keeping **82,127/82,127
selected CODE+DATA bytes** and **1,449 physical COFF offsets/targets**;
94 *compiler-local `$L` names* changed. That is **NOT original whole
CODE/COFF exactness**. See [F1138 source borrow](CHARACTEROBJECT_WHOLE_NATIVE_PHASE_GAUGE_F1138.md).

## 3. Other large original functions — do not abandon them

| Actual original complete callable | Current original-shaped normal C++ research | Local scoped proof |
| --- | --- | --- |
| **`004AC040`** 82,796B/22,721 x86, 1,126 afterRET DATA | F1200 same length/count; frame 0x720 /this EBP-0x64, all 7,432 EBP positions; **6,958 GPR /12 widths**; all direct CFG/non-GPR operands agree | [F1200 all direct CFG proof](THIRD_FIGHTER_ALL_DIRECT_CFG_F1200.md): all 1,927 direct targets, 2,201 CODE fields and 151 dense ordinals agree; NONEXACT |
| **`00543210`** 58,294B/16,471 x86, 943 DATA | F1196 live tracked source 58,293B/16,471 x86; native frame/this/all 5,119 EBP positions; **3 widths, 1,741 GPR positions** | [F1196 whole CFG/operand proof](FIGHTER_58KB_WHOLE_CFG_OPERANDS_F1196.md): all 1,905 direct targets, 1,707 CODE fields and 156 dense destinations; NONEXACT |
| **`005214B0`** 46,755B/13,230 x86, 901 DATA | F1197 source 46,754B/13,230 x86; native frame/this/all 4,133 EBP positions; **2,736 GPR /5 widths** | [F1197 whole CFG proof](FIGHTER_46KB_WHOLE_CFG_F1197.md): all 1,522 direct targets, 1,352 CODE fields and 139 dense destinations; NONEXACT |
| **`0045DD70`** 60,999B/16,837 x86 | Live F1193 complete source **61,000B/16,837 x86 (+1B)**; original frame/saved-this/all 5,444 EBP slots; **6,311 GPR positions /5 widths** | [F1192 complete stack/CFG/PE proof](REIMU_WHOLE_STACK_CFG_F1192.md), [F1193 native WORD parameters](REIMU_WORD_ABI_REGISTER_BOUNDARY_F1193.md): all 1,684 direct targets, 1,682 CODE fields, 142 actual dense destinations; NONEXACT |
| **`0055AC80`** 28,432B/7,653 x86 | F1194 continues the complete F167 source: **28,438B/7,653 x86 (+6B)**; original frame/this/all 2,511 EBP positions; **726 GPR positions /6 widths** | [F1194 whole native proof](OBJECT_ADVANCE_0055AC80_WHOLE_F1194.md): all 859 direct targets, 638 CODE fields and 58 dense destinations; NONEXACT |

Current 82KB source:
[`probes/FighterWhole004AC040F1020.cpp`](../probes/FighterWhole004AC040F1020.cpp).
F1198 restores four early shared-getter entries/default skip; keep the
getter inside the switch. F1199 fixes 26 operands. F1200 restores all
45 remaining direct targets through actual cooldown, fade, clamp and
getter/cadence guard scopes. All whole CFG/non-GPR/EBP operands agree.
Fresh proof: `.analysis/f1200-82kb-native-cfg/tracked.obj` and
`whole-audit.py`; F1028 cold-builds only this parent using **/GX**.
All 2,352 COFF field shapes/addends/destinations remain unchanged;
45 local names change, offsets preserved. Remaining **6,958 GPR /12 widths**;
first divergence **004ADEFA /whole ordinal 2,180**, native EAX vs source EDX.
Equal total CODE length is not exactness. Continue from this corrected parent.

Current 58KB source:
[`probes/FighterWhole00543210F1041.cpp`](../probes/FighterWhole00543210F1041.cpp).
F1196 restores 253 ordinary exits and five real operands; all whole CFG,
stack and non-GPR operands agree. Keep the getter inside the switch: only
0/2/4/5 enter 005515BA; ordinary exits reach 005515C2. Frame 0x218 /this
EBP-0x44 agree. Selected proof: `.analysis/f1196-58kb-whole-cfg/tracked.obj`
and `whole-audit.py`; F1025 cold-builds only this parent for PE/DATA checks.
Remaining **1,741 GPR /three widths in 63**; whole exactness is unproved.

Current 46KB source:
[`probes/FighterWhole005214B0F1040.cpp`](../probes/FighterWhole005214B0F1040.cpp).
F1197 restores 56 ordinary exits to 0052CB4F and three 18B guard targets.
The post-subaction-6 +80/+7C resets belong inside stage7/frame0/counter<2.
Keep the shared getter inside the switch; only 0/2/4/5 enter 0052CB47.
Frame 0x138 /this EBP-0x10, every stack/non-GPR operand and all native
targets agree. Selected proof: `.analysis/f1197-46kb-whole-cfg/tracked.obj`
and `whole-audit.py`; F1026 cold-builds this parent for PE/DATA checks.
Remaining **2,736 GPR /five widths in 63/1FD/252/254**; NONEXACT.

Current Reimu source: [`probes/FighterWhole0045DD70F1183.cpp`](../probes/FighterWhole0045DD70F1183.cpp).
All real cases/default and the four-entry inside-switch getter are present.
Native frame 0x380 /this EBP-0x34, all 5,444 EBP positions, 1,684 direct
branches, 1,682 CODE fields, 142 dense entries and 1,090B DATA agree.
Remaining **6,311 GPR /five widths**; first GPR divergence is 59 at
0045FDA9 /ordinal 2,292. F1193 adopts native short helper parameters;
all CODE+DATA and field shapes stay unchanged. Current object:
`.analysis/f1193-reimu-register-boundary/adopted.obj`; scoped verifier:
`.analysis/f1192-reimu-final-states/whole-audit.py OBJ`.
Preserve the inside-switch getter. F1193 bare/captured/borrowed-access
and guard controls, plus F792/F793, are retained negatives; do not repeat.
See the linked F1192/F1193 proofs above. All 60,999 original bytes remain
pending; whole NONEXACT.

Current `0055AC80` source is
[`probes/CharacterObjectWhole0055AC80F1194.cpp`](../probes/CharacterObjectWhole0055AC80F1194.cpp),
continued from the actual complete F167 normal C++ draft. All 57 real states
and default are present; do not replace it with the F569 marker skeleton.
Frame 0x19C, saved-this EBP-0x24, every stack operand, all 859 direct branches,
638 CODE references and 58 dense entry ordinals agree with the original.
Its 430B owned DATA includes 198 exact sparse bytes. GPR debt is limited to
389–392, beginning **0055F711 /whole ordinal 5,225**; the six remaining CMP
widths account for all +6 source bytes. The current object and scoped audit
are `.analysis/f1194-remilia-whole-recovery/tracked.obj` and `audit.py`.
All original 28,432 bytes remain unaccepted and counted.

State 389's first **59** instructions agree; the divergence starts at its
initializer join. F1195/F1196's chaining, DWORD, array/member and guarded-block
controls are negative; `/Op` wrongly changes frame/instruction count. See
[retained controls](OBJECT_ADVANCE_0055AC80_JOIN_NEGATIVES_F1195.md) and F1196;
do not repeat them or the old 04–24 spellings. R233's 454C00/454F70 leaves
still lack owner witnesses and remain unknown without another source rebuild.

All other giant authored originals remain open; use the
[actual giant dispatch manifest](../config/fighter-boss-dispatch-fingerprints.json)
and [authored origin decisions](../config/function-origins.csv).
F1025/1026/1028 certify **external game PE destinations**, not
physical relocation sites or entire byte exactness. The old F917/F901
source is not automatically current acceptance. Older original research is preserved in the [F1142 handoff
snapshot](history/RE_HANDOFF_AS_OF_F1142_PRE_HANDOFF_2026-11-04.md)
and the complete [F781–F906 frozen historical handoff](history/RE_HANDOFF_F781_THROUGH_F906_PRE_CLEANUP_2026-10-31.md).
Former repeated giant traces can be recovered with the tracked
[`scripts/archive-frozen-giant-traces.py`](../scripts/archive-frozen-giant-traces.py)
using [storage instructions](STORAGE_HYGIENE.md).

## 4. Remaining independent smaller whole originals

F1155 accepted the complete 171B ArchiveCatalog destructor `0041CE50`,
including all 14 real fields, by restoring new[]-paired filename deletion.
See [whole destructor cold-exact proof](ARCHIVE_CATALOG_ARRAY_DELETE_EXACT_F1155.md).
F1157 also accepted the complete 248B virtual BattleScene destructor `0043B0B0`,
all 12 fields, restoring actual scalar deletion of three new-allocated HUD objects.
See [whole Scene cold-exact proof](BATTLE_SCENE_TYPED_DELETE_EXACT_F1157.md).
F1171 accepts the complete **2,987B/654-x86 WinMain `00602A60`**, all
173 physical fields and the complete 60B after-RET scene table, through
canonical **1/1 cold exact**. The new canonical source is
[`src/WinMainF1171.cpp`](../src/WinMainF1171.cpp); [whole-function proof](WINMAIN_WHOLE_EXACT_F1171.md).
All independently authored smaller originals are now accepted. The remaining
queue consists of the 22 giant functions above; do not reopen F911/F914
as the current WinMain parent. Their negative evidence remains historical.
No dummy locals, altered path capacity, assembly, cropped extent or
structural-only acceptance was used.

Reproduce only this new unit when its inputs change:

    scripts/repo-python scripts/replay-exact-units.py --unit game-application-run-00602a60

F1156 reconciled 65 historical source-hash revisions and pinned 29 new
borrowed headers plus the baseline policy source. **All 268 affected units
across 66 serial objects passed canonical cold replay**; no full-corpus replay.
Previous/current hashes and exact affected names are retained in the adoption
manifest; [reconciliation evidence](ACCEPTED_SOURCE_PIN_RECONCILIATION_F1156.md).
Do not repeat these completed replays without a new affected input change.

## 5. Previously accepted entire native leaf functions, source improved

Accepted whole-source maintenance adds no new exact CODE. Current examples:
[CharacterAuxAction](CHARACTER_AUX_ACTION_NATIVE_TRANSFORM_F1139.md),
[Battle HUD](BATTLE_HUD_NATIVE_BORROW_F1134.md),
[AuxiliaryActor](AUXILIARY_ACTOR_NATIVE_BORROW_F1124.md),
[BattleState](BATTLE_STATE_NATIVE_BORROW_MACROS_F1112.md) and
[frame dependencies](FRAME_DEPENDENCIES_NATIVE_BORROW_WINDOWS_F1106.md).
Their full cold-exact receipts remain authoritative.

Replay all accepted units in an affected translation unit, never the whole
registry. Header changes can rename VC7.1 `$L`/`$SG` symbols; complete original
COFF identity matters alongside CODE bytes. For example:

    scripts/repo-python scripts/replay-exact-units.py --unit character-aux-action-005fae30

## 6. Storage, source recovery and safe next-agent checklist

Preserve `resources/th075.exe`, `.analysis/vc71-wine/`, all accepted
`build/matching/`, Ghidra, the **live `.analysis/f1068-boss-live-all-native/`
OBJ/JSON**, all original PE/COFF reference files, tracked C++/scripts/
config/provenance, and archives under `.analysis/cache-archives/`.
**Archive bytes are Git-ignored and NOT backed up by a fresh clone.**
F1144 losslessly SHA256-archived **673 regenerable OBJ/PDB research
files** into 6,453,751 archive B plus 117,927 receipt B, reclaiming
**32,524,192 file bytes net**. Normal two-week-retention
Git GC additionally saved **12,348,518 bytes**, and the narrow Python
bytecode cleanup reclaimed **159,841 bytes**. See F1145 in the storage
guide for integrity checks. The tracked
[`F1144 restore/verify tool`](../scripts/archive-post-f1031-probe-binaries-f1144.py)
recovers exact historical paths once the **machine-local archive and
receipt** accompany the handoff. See [storage hygiene](STORAGE_HYGIENE.md).
Historical full research evidence and older handoffs are indexed in
[history](history/).

Before editing, run:

    git status --short --branch
    scripts/repo-python scripts/verify-target.py
    scripts/repo-python scripts/validate-tracking.py --require-target
    scripts/repo-python scripts/audit-active-handoff.py
    scripts/repo-python scripts/report-reconstruction-status.py --summary
    scripts/repo-python scripts/ghidra.py check

For a **Boss-only** change, run only the affected whole-parent verifier;
for a **leaf** change, cold replay only that leaf and all other exact
units in the same source object. Record what passed and what remains
unresolved. After meaningful progress, commit with `gpt-web: ...`.
Do not run a full 982-unit cold replay. Git commits remain local without
network push; hand off the checkout or transfer/push through an
external authorized mechanism.
