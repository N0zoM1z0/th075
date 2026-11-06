# TH075 — CURRENT AGENT HANDOFF (2026-11-06, F1183)

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

**Canonical summary:** **982 functions / 982 exact units** have
**871,649 original CODE bytes** accepted; **1,004** independently
authored originals are attributed, and **22 authored functions remain nonexact**: **22 large original state advances** (**1,102,055 CODE bytes**) plus **0 other original small/medium whole functions**
(**0 CODE bytes**). The independently reviewed original authored
size denominator is **1,973,704** CODE B; accepted coverage is
**44.16%** (conservative **44.09%**). These numbers must be read from
the live ledger rather than maintained by hand.

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

The 83 strict cases **are interior evidence, not 83 accepted independent
functions**, and even correct mnemonics/GPR/widths do not prove branch CFG.
The F1140–F1143 audit has corrected real gameplay control flow for `0x387`
(per-frame gravity and angle), `0x388` and `0x330` (native ground/status
short-circuit OR), and `0x389` (speed decay only in stages<=1).
Read [F1140 full original CFG proof](CHARACTEROBJECT_ORIGINAL_WHOLE_CFG_AUDIT_F1140.md),
[F1143 latest stage-speed correction](CHARACTEROBJECT_NATIVE_389_STAGE_SPEED_CFG_F1143.md)
and [F1132 native tail](CHARACTEROBJECT_NATIVE_3E3_3E6_F1132.md).

F1146 also restores the original `0x346` status-2-or-4 stage transition;
see [native status CFG proof](CHARACTEROBJECT_NATIVE_346_STATUS_CFG_F1146.md).
F1147 restores the original 3E3/3E4 stage-zero polar update, shared hit
callback and terminal hit/cooldown paths; [native hit CFG proof](CHARACTEROBJECT_NATIVE_HIT_RETURNS_CFG_F1147.md)
supersedes the F1132 claim that positive cooldown continues through meter recovery.

**F1148 clears all remaining physical direct branch-target differences:**
`0x35D` guards its +0xD8 increment with stage 1/frame 0; `0x35E`
executes the final polar velocity call every frame; `0x391` checks both
reflection directions independently inside the scale/difficulty guard.
See [native scope/independent-reflection proof](CHARACTEROBJECT_NATIVE_ALL_DIRECT_CFG_F1148.md).

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
| **`004AC040`** 82,796B/22,721 x86, 1,126 afterRET DATA | 82,796B/22,721 x86, original saved-this and frame; **12 wrong widths, 6,958 GPR positions** | [F1028 native PE targets](THIRD_FIGHTER_WHOLE_82KB_PE_TARGETS_F1028.md), 2,191 external targets |
| **`00543210`** 58,294B/16,471 x86, 943 DATA | 58,293B/16,471 x86; **3 widths, 1,741 GPR positions** | [F1025 native PE targets](FIGHTER_58KB_ALL_NATIVE_PE_TARGETS_F1025.md), 1,697 targets |
| **`005214B0`** 46,755B/13,230 x86, 901 DATA | 46,754B/13,230 x86; **5 widths**, original physical COFF/GPR wrong | [F1026 native PE targets](FIGHTER_46KB_ALL_NATIVE_PE_TARGETS_F1026.md), 1,341 targets |
| **`0045DD70`** 60,999B/16,837 x86 | Live F1183 partial parent **19,282B/5,182 x86**; 80 nondefault markers, frame/stack/GPR still wrong | [F1183 new 12C–136 native bodies](REIMU_FALLING_STATES_F1183.md), 1,001 x86 /91 fields; no whole exact |

Current Reimu source: [`probes/FighterWhole0045DD70F1183.cpp`](../probes/FighterWhole0045DD70F1183.cpp),
continued from the retained F652 D1/D2 source. Eleven real states replace
old markers; all their native CFG/field/operand grammar and the 53 previous
real prefix handlers are checked, but 623 GPR positions in the new states
and native frame/stack slots remain wrong. These are **interior source
progress only**, not new exact callables. Preserve the incomplete default
and remaining marker debt explicitly; do not promote this parent as complete.

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

The following are *real C++ maintenance/layout reconstruction* but preserve
**previously credited CODE**; not new exact original bytes:

| Recent original source cleanup | Complete original cold-replay result |
| --- | --- |
| [F1135/F1136/F1139 CharacterAuxAction](CHARACTER_AUX_ACTION_NATIVE_TRANSFORM_F1139.md), **1,333 named field accesses** in 31KB switch | **1/1 full exact, 31,352 original B**, full physical COFF + native `$L` |
| [F1134 Battle HUD](BATTLE_HUD_NATIVE_BORROW_F1134.md), 127 native typed field accesses | **1/1 full exact, 9,841 original B** |
| [F1124 AuxiliaryActor](AUXILIARY_ACTOR_NATIVE_BORROW_F1124.md), 89 native typed fields | **2/2 complete exact, 6,935 original B** |
| [F1112 BattleState](BATTLE_STATE_NATIVE_BORROW_MACROS_F1112.md), 27 native actor fields | **1/1 complete exact, 4,764 original B** |
| [F1106 frame dependency](FRAME_DEPENDENCIES_NATIVE_BORROW_WINDOWS_F1106.md), 109 native float accesses | **3/3 complete exact, 4,169 original B** |

Only replay **all exact units in an affected translation unit**, e.g.:

    scripts/repo-python scripts/replay-exact-units.py --unit character-aux-action-005fae30
    scripts/repo-python scripts/replay-exact-units.py --unit battle-hud-render-0043e040

VC7.1 can change `$L`/`$SG` local symbols merely because a header
introduces a struct or `<stddef.h>`. The complete original COFF
identity, not mnemonic count alone, is the acceptance standard.

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
