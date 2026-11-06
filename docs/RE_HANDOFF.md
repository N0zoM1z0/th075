# TH075 — CURRENT AGENT HANDOFF (2026-11-06, F1228)

**Start here.** Continue all dirty work; there are no other active sessions.
Work on both large/core and smaller authored originals. Use local commits
named `gpt-web: ...`; never replay the complete 982-unit corpus.
Read [AGENTS.md](../AGENTS.md), [workflow](RE_WORKFLOW.md) and
[storage/recovery](STORAGE_HYGIENE.md). Current pinned target, ledgers and
fresh source evidence supersede historical labels. Inner cases, mapped
names and compiler output alone prove neither whole exactness nor ownership.

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

Interior states and accepted-source refactors earn no new exact CODE.
Origin-unknown candidates remain uncredited without independent attribution.
Use the canonical status reporter in the preflight checklist below.

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

The 83 strict cases are interiors, not accepted independent functions.
F1140–F1148 restore the [complete direct CFG](CHARACTEROBJECT_NATIVE_ALL_DIRECT_CFG_F1148.md)
and the [3E3/3E4 hit/return scopes](CHARACTEROBJECT_NATIVE_HIT_RETURNS_CFG_F1147.md),
superseding the old positive-cooldown continuation interpretation.
F1149 resolves both 391 FUCOMPP load orders: 29 PE fields /277 x86;
[typed x87 proof](CHARACTEROBJECT_NATIVE_391_TRANSFORM_X87_F1149.md).
F1150 recovers frame/this/all EBP slots through genuine temporaries and one
used 38A loop index; [stack proof](CHARACTEROBJECT_NATIVE_ALL_STACK_SLOTS_F1150.md).
F1158 verifies every non-GPR operand, all 1,357 CODE fields and 92 dense
ordinals; [whole operand proof](CHARACTEROBJECT_WHOLE_OPERAND_PROOF_F1158.md).
F1181 aligns seven narrow declarations /six native callees, retaining all
82,109 CODE+DATA bytes and 1,449 field shapes (202 symbol renames).
Keep raw coordinate/angle DWORD transport: the float-lvalue trial adds 329
instructions. [Native parameter proof](CHARACTEROBJECT_NATIVE_EFFECT_ABI_F1181.md).

Remaining **522 GPR /five widths** are in358–35E/3E6. F1149 supersedes
[F1128](CHARACTEROBJECT_NATIVE_391_392_393_F1128.md). Retain rejected
F1137 grammars (`.analysis/f1137-*`), F1151 typed/assignment controls
(`.analysis/f1151-native-gpr-types/`) and F1194 nested guards; do not repeat.

**Reproduction:**

    scripts/repo-python scripts/verify-characterobject-current-recovered-f1068.py

Build only this affected parent. Preserve [F1138's phase/meter borrow proof](CHARACTEROBJECT_WHOLE_NATIVE_PHASE_GAUGE_F1138.md); it adds no whole exact credit.

## 3. Other large original functions — do not abandon them

| Actual original complete callable | Current original-shaped normal C++ research | Local scoped proof |
| --- | --- | --- |
| **`004EBDA0`** 33,293B/8,789 x86, 438 DATA | F1205 fresh complete F572–F596 source: original frame 0x1FC /this EBP-0x40, all 3,005 EBP; **133 GPR /zero width differences** | [F1205 full native proof](OBJECT_ADVANCE_004EBDA0_WHOLE_F1205.md): all 885 direct targets, 622 CODE fields, 60 dense targets; 137 nonfield bytes remain; NONEXACT |
| **`005EB520`** 34,434B/9,378 x86, 443 DATA | F1209 tracked complete F061 active07 source: 34,436B /same count, frame 0x210 /this EBP-4, all 3,170 EBP; **135 GPR /six widths**, all state 998 | [F1209 native virtual/whole proof](OBJECT_ADVANCE_005EB520_VIRTUAL_ABI_F1209.md): all 901 direct targets, 745 CODE fields, 61 dense targets /199 sparse bytes; NONEXACT |
| **`004AC040`** 82,796B/22,721 x86, 1,126 afterRET DATA | F1203 same length/count; frame 0x720 /this EBP-0x64, all 7,432 EBP positions; **6,958 GPR /12 widths**; all direct CFG/non-GPR operands agree | [F1200 all direct CFG proof](THIRD_FIGHTER_ALL_DIRECT_CFG_F1200.md): all 1,927 direct targets, 2,201 CODE fields and 151 dense ordinals agree; NONEXACT |
| **`00543210`** 58,294B/16,471 x86, 943 DATA | F1196 live tracked source 58,293B/16,471 x86; native frame/this/all 5,119 EBP positions; **3 widths, 1,741 GPR positions** | [F1196 whole CFG/operand proof](FIGHTER_58KB_WHOLE_CFG_OPERANDS_F1196.md): all 1,905 direct targets, 1,707 CODE fields and 156 dense destinations; NONEXACT |
| **`005214B0`** 46,755B/13,230 x86, 901 DATA | F1197 source 46,754B/13,230 x86; native frame/this/all 4,133 EBP positions; **2,736 GPR /5 widths** | [F1197 whole CFG proof](FIGHTER_46KB_WHOLE_CFG_F1197.md): all 1,522 direct targets, 1,352 CODE fields and 139 dense destinations; NONEXACT |
| **`0045DD70`** 60,999B/16,837 x86 | Live F1193 complete source **61,000B/16,837 x86 (+1B)**; original frame/saved-this/all 5,444 EBP slots; **6,311 GPR positions /5 widths** | [F1192 complete stack/CFG/PE proof](REIMU_WHOLE_STACK_CFG_F1192.md), [F1193 native WORD parameters](REIMU_WORD_ABI_REGISTER_BOUNDARY_F1193.md): all 1,684 direct targets, 1,682 CODE fields, 142 actual dense destinations; NONEXACT |
| **`0055AC80`** 28,432B/7,653 x86 | F1194 continues the complete F167 source: **28,438B/7,653 x86 (+6B)**; original frame/this/all 2,511 EBP positions; **726 GPR positions /6 widths** | [F1194 whole native proof](OBJECT_ADVANCE_0055AC80_WHOLE_F1194.md): all 859 direct targets, 638 CODE fields and 58 dense destinations; NONEXACT |
| **`00536400`** 39,999B/10,573 x86, 467 DATA | **F1214 complete source, NONEXACT**: 39,997B/10,573 x86; history +66/66 states, original frame0x2A0/all3,469 EBP slots; 913 GPR/10 width debt | [F1214 whole-parent proof](OBJECT_ADVANCE_00536400_COMPLETE_PARENT_F1214.md); zero exact credit |

Current 33KB source:
[`probes/CharacterObjectActionsF572.cpp`](../probes/CharacterObjectActionsF572.cpp).
It already contains every real case/default; do not restart F569 markers.
F1205 verifies all8,789 native offsets/widths, CFG/stack/non-GPR operands and
all682 COFF bindings. **137 bytes /133 GPR** remain:38D45/38E64/3E3first31=24.
First **004F344C /whole8,076 /38D91**. Selected
`.analysis/f1205-object-4ebda0-recovery/before.obj`; `whole-audit.py OBJ`,
`verified-summary.json`; **/GX-**. [F1205 proof](OBJECT_ADVANCE_004EBDA0_WHOLE_F1205.md)
preserves F594/F756/F773 and six new negatives. All33,293 original B pending.

Current 82KB source:
[`probes/FighterWhole004AC040F1020.cpp`](../probes/FighterWhole004AC040F1020.cpp).
F1198 restores the inside-switch four-entry shared getter/default skip;
F1199 fixes 26 operands; F1200 fixes all 45 interior direct targets.
F1203 reconciles16 declarations/10 accepted callees; all83,922 candidate
CODE+DATA bytes and2,352 field shapes stay unchanged. Preserve raw DWORD
coordinate transport; [native interface proof](THIRD_FIGHTER_NATIVE_CALL_ABI_F1203.md).
Fresh selected object: `.analysis/f1203-third-native-call-abi/tracked.obj`;
`whole-audit.py` there verifies all CFG/non-GPR/EBP operands. F1028 builds
only this parent using **/GX**. Remaining **6,958 GPR /12 widths**;
first divergence **004ADEFA /ordinal 2,180**. Equal length is not exactness.
F1201/F1202/F1204 controls are rejected; do not repeat. Preserve the
[native debt map](THIRD_FIGHTER_REGISTER_DEBT_MAP_F1202.md) and original
36-call bodies: `.analysis/f1201-82kb-first-register/native-state-debt.json`.

Current 58KB source:
[`probes/FighterWhole00543210F1041.cpp`](../probes/FighterWhole00543210F1041.cpp).
F1196 restores 253 exits/five operands. Only 0/2/4/5 enter getter005515BA;
ordinary exits reach005515C2. Selected `.analysis/f1196-58kb-whole-cfg/tracked.obj`
and `whole-audit.py`; F1025 verifies only this parent's PE/DATA. All stack/
CFG/non-GPR operands agree; **1,741 GPR /three widths in63** remain.

Current 46KB source:
[`probes/FighterWhole005214B0F1040.cpp`](../probes/FighterWhole005214B0F1040.cpp).
F1197 restores 56 ordinary exits0052CB4F and three18B guards. The post-action6
resets stay inside stage7/frame0/counter<2; only 0/2/4/5 enter getter0052CB47.
Selected `.analysis/f1197-46kb-whole-cfg/tracked.obj`, `whole-audit.py`;
F1026 verifies scoped PE/DATA. **2,736 GPR /five widths in63/1FD/252/254**.

Current Reimu source:
[`probes/FighterWhole0045DD70F1183.cpp`](../probes/FighterWhole0045DD70F1183.cpp).
Selected `.analysis/f1193-reimu-register-boundary/adopted.obj`;
audit `.analysis/f1192-reimu-final-states/whole-audit.py OBJ`.
**6,311 GPR /five widths**; first59 at0045FDA9 /ordinal2,292. Preserve
F1193 short parameters/getter. F1193 and F792/F793 negatives stay excluded.

Current `0055AC80` source:
[`probes/CharacterObjectWhole0055AC80F1194.cpp`](../probes/CharacterObjectWhole0055AC80F1194.cpp),
continued from complete F167. All 57 states/default remain; frame 0x19C /
this EBP-0x24, stack/CFG/fields/DATA agree as above. Selected object/audit:
`.analysis/f1194-remilia-whole-recovery/tracked.obj`, `audit.py`.
Remaining **726 GPR /six widths**, 389–392; first **0055F711 /ordinal5,225**.
F1195/F1196 chaining/DWORD/array/member/guard controls are negative; /Op
breaks frame/count. [Retained controls](OBJECT_ADVANCE_0055AC80_JOIN_NEGATIVES_F1195.md).
R233 454C00/454F70 still lack owner witnesses; no new rebuild or promotion.

Current 34KB source:
[`probes/CharacterObjectWhole005EB520F1207.cpp`](../probes/CharacterObjectWhole005EB520F1207.cpp)
and `ObjectAdvance5EB520F1207.hpp`. Complete F061 active07 body: all 60
states/default. F1209 proves virtual slot1 with original ctor/vtable/queue dispatch;
`?AdvanceAction@ObjectActor5EB520Draft@@UAEXXZ`. CODE/DATA and806 binding
shapes/destinations stay unchanged (63 local-label renames).
**135 GPR /six widths** remain only in 998, first **005F3904 /ordinal9,200**.
Selected `.analysis/f1209-object-5eb520-virtual-abi/tracked.obj`; `whole-audit.py OBJ`,
`verified-summary.json`, fresh physical receipts there. Use recorded **/GX-**
profile. [F1209 proof](OBJECT_ADVANCE_005EB520_VIRTUAL_ABI_F1209.md) retains
F1208's eight identical-code controls and two wrong-shape candidates; do not
repeat. All34,434 original CODE B remain pending.
Earlier forward-branch bytes can differ despite correct target ordinals.

Current complete 40KB source:
[`probes/CharacterObjectActions00536400F1211.cpp`](../probes/CharacterObjectActions00536400F1211.cpp),
`ObjectAdvance536400F1211.hpp`. F1214 has history relay +all66 actual states,
39,997B/10,573 x86 vsnative39,999B; frame0x2A0, named slots and all3,469 EBP
operands agree. All967 direct target ordinals,871 CODE destinations and67 dense
entries/199 sparse bytes agree. **913 GPR/10 width differences remain** in
829–835 and906–912. First:005392F8/whole3223/state829 instruction61.
Selected `.analysis/f1214-object-536400-complete/current.obj`, `current.asm`,
immutable `current.cpp`/`current.hpp`, both current diagnostic JSONs and
`verified-summary.json`; `whole-audit.py [OBJ]` checks this parent. Destination
identity is not original relocation-offset equality. [F1214 proof](OBJECT_ADVANCE_00536400_COMPLETE_PARENT_F1214.md).
Continue register debt in this complete body; never count interiors as exact.
Current complete 43KB source:
[`probes/CharacterObjectActions005C9CC0F1216.cpp`](../probes/CharacterObjectActions005C9CC0F1216.cpp).
F1219 has all67 states, 43,502B/11,447 x86 vsnative43,501B; original frame0x470,
this-4Ch/all3,971 EBP operands. All1,001 direct targets,923 CODE destinations,
68 dense ordinals/198 sparse bytes agree. **935 GPR/one width remain** in918–929;
first005D2558/whole9213; sole width005D2841/whole9411 in919.
Selected `.analysis/f1219-object-5c9cc0-late/native-order.obj`, immutable CPP/HPP,
listing, both diagnostics and `verified-summary.json`; `whole-audit.py [OBJ]`.
[F1219 whole proof](OBJECT_ADVANCE_005C9CC0_COMPLETE_PARENT_F1219.md) records
all final25 states and twelve rejected controls. Continue this complete body;
no whole exact credit. All other parents and unknown origins stay preserved.

Current complete 42KB source:
[`probes/CharacterObjectActions004CA6E0F1222.cpp`](../probes/CharacterObjectActions004CA6E0F1222.cpp).
F1227 has all55 states; selected42,515B/11,201 x86 vsnative42,511B; original
frame0x288/this-4/ESI/all3,717 EBP operands. All1,014 direct targets,873 CODE
destinations,56 dense ordinals/198 sparse bytes agree. **447 GPR/12 widths**
remain only in808–811, first004CCBD7/whole2526. Postfix/compound increment and boundary controls are negative;
906 LEA is fixed by natural compound update. Selected
`.analysis/f1227-object-4ca6e0-complete/compound-counter.obj`, immutable CPP/HPP,
listing/both diagnostics/verified-summary.json; `whole-audit.py [OBJ]`.
[F1227 proof](OBJECT_ADVANCE_004CA6E0_COMPLETE_PARENT_F1227.md). Continue this
complete body; all42,511 original B remain pending.

All other giant authored originals remain open; use the
[actual giant dispatch manifest](../config/fighter-boss-dispatch-fingerprints.json)
and [authored origin decisions](../config/function-origins.csv).
F1025/1026/1028 certify **external game PE destinations**, not
physical relocation sites or entire byte exactness. Older research is preserved in the [F1142 handoff
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
All independently authored smaller originals are accepted; 22 giants remain.
Do not reopen F911/F914 as the WinMain parent. Replay WinMain only when affected:

    scripts/repo-python scripts/replay-exact-units.py --unit game-application-run-00602a60

F1156 reconciled 65 historical source-hash revisions and pinned 29 new
borrowed headers plus the baseline policy source. **All 268 affected units
across 66 serial objects passed canonical cold replay**; no full-corpus replay.
Previous/current hashes and exact affected names are retained in the adoption
manifest; [reconciliation evidence](ACCEPTED_SOURCE_PIN_RECONCILIATION_F1156.md).
Do not repeat these completed replays without a new affected input change.

## 5. Previously accepted entire native leaf functions, source improved

Accepted source maintenance adds no exact CODE. Preserve the cold receipts:
[CharacterAuxAction](CHARACTER_AUX_ACTION_NATIVE_TRANSFORM_F1139.md),
[Battle HUD](BATTLE_HUD_NATIVE_BORROW_F1134.md),
[AuxiliaryActor](AUXILIARY_ACTOR_NATIVE_BORROW_F1124.md),
[BattleState](BATTLE_STATE_NATIVE_BORROW_MACROS_F1112.md),
[frame dependencies](FRAME_DEPENDENCIES_NATIVE_BORROW_WINDOWS_F1106.md).
Replay every affected unit in a changed translation unit only. Header edits
can rename VC7.1 local COFF symbols; CODE equality alone is insufficient.

## 6. Storage, source recovery and safe next-agent checklist

Preserve `resources/th075.exe`, `.analysis/vc71-wine/`, all accepted
`build/matching/`, Ghidra, the **live `.analysis/f1068-boss-live-all-native/`
OBJ/JSON**, all original PE/COFF reference files, tracked C++/scripts/
config/provenance, and archives under `.analysis/cache-archives/`.
**Archive bytes are Git-ignored and NOT backed up by a fresh clone.**
The machine-local F1144 archive/receipt preserves 673 historical binaries;
use the [`F1144 restore/verify tool`](../scripts/archive-post-f1031-probe-binaries-f1144.py)
and [storage hygiene](STORAGE_HYGIENE.md). Never discard archives/receipts.
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
