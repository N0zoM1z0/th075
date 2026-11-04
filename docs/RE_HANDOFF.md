# TH075 — CURRENT AGENT HANDOFF (2026-11-04, F1144)

**Start here.** Work on both large/core original functions and smaller entire
original functions. The user requests meaningful **multiple local commits** named
`gpt-web: ...`, wants all dirty work continued rather than discarded, and forbids
a complete 979-unit cold replay. Read [AGENTS.md](../AGENTS.md),
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
| **Accepted complete original exact callables** | **979 units, 868,243 original CODE B** |
| Reviewed authored byte exactness | **868,243/1,973,704 = 43.99%**; conservative **43.91%** |
| **Whole authored originals remaining NONEXACT** | **25 =22 giant (1,102,055B) +3 other (3,406B)** |
| Completion objective | 98% authored CODE target **NOT achieved** |

**Canonical summary:** **979 functions / 979 exact units** have
**868,243 original CODE bytes** accepted; **1,004** independently
authored originals are attributed, and **25 authored functions remain nonexact**: **22 large original state advances** (**1,102,055 CODE bytes**) plus **3 other original small/medium whole functions**
(**3,406 CODE bytes**). The independently reviewed original authored
size denominator is **1,973,704** CODE B; accepted coverage is
**43.99%** (conservative **43.91%**). These numbers must be read from
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
| Entire callable CODE | **81,539B** | **81,560B** (**+21B**) |
| Entire native x86 instruction count | **17,435** | **17,435** |
| Actual saved-this stack slot | **EBP-0xAC** | **EBP-0xDC** (wrong) |
| Actual frame allocation | **ESP 0x3A0** | **ESP 0x3A4** (wrong) |
| Owned separately afterRET switch DATA | **567B** | **567B** (verified) |
| Strict original inner case intervals | — | **82 cases; 75,260 original CODE B /16,090 native x86 mnemonic+GPR matches** |
| Original physical external PE fields in those 82 cases | **1,246** | **1,246/1,246** |
| Original scalar immediate positions in those cases | **2,964** | **2,964** |
| Explicit GPR-provisional case intervals | — | **8 cases:** `0x358–0x35E` and `0x3E6` |
| Separate uncredited x87 case | — | **`0x391`**, 2 incorrect physical `FUCOMPP` fields, 4 GPR-role differences |
| Actual direct intra-function branches audited by native target ordinal | **1,834** | **13 incorrect CFG destinations remain** |
| **Whole original callable accepted exact** | — | **NO** |

The 82 strict cases **are interior evidence, not 82 accepted independent
functions**, and even correct mnemonics/GPR/widths do not prove branch CFG.
The F1140–F1143 audit has corrected real gameplay control flow for `0x387`
(per-frame gravity and angle), `0x388` and `0x330` (native ground/status
short-circuit OR), and `0x389` (speed decay only in stages<=1).
Read [F1140 full original CFG proof](CHARACTEROBJECT_ORIGINAL_WHOLE_CFG_AUDIT_F1140.md),
[F1143 latest stage-speed correction](CHARACTEROBJECT_NATIVE_389_STAGE_SPEED_CFG_F1143.md)
and [F1132 native tail](CHARACTEROBJECT_NATIVE_3E3_3E6_F1132.md).

**The 13 remaining *physical original branch-target* differences** are
mapped by original game action and local x86 ordinal below. This is the
current complete, verified debt set, not a list of permitted exact-match
exceptions:

| Original state | Wrong native branch ordinals | First next step |
| --- | --- | --- |
| `0x346` | **271** | Restore original status branch into the correct native body |
| `0x35D` | **13, 17** | Correct stage/frame guarded projectile sequencing; GPR also provisional |
| `0x35E` | **155** | Correct original later-stage homing branch; GPR also provisional |
| `0x391` | **124, 130** | Correct target-aim/float-branch CFG together with the 2 `FUCOMPP` PE fields |
| `0x3E3` | **43, 163** | Repair noninitial stage speed and hit/score switch targets |
| `0x3E4` | **43, 179, 204, 214, 232** | Repair independent meter/hit outcome branches, preserve prior 3B6/3B0 fix |

**Important:** the live parent verifier re-checks the exact set of all
1,834 original jump target ordinals and independently requires these 13
explicit debts; new mismatches fail. Its JSON result is under ignored
`.analysis/f1068-boss-live-all-native/verified-summary.json`. Consult
[original native 0x391 attempts](CHARACTEROBJECT_NATIVE_391_392_393_F1128.md)
before retrying; 12 plus 12 natural float grammar variants already
failed. `0x3E6` retained **105/105 native mnemonics and 9/9 PE fields**
but only **30/105 native GPR positions**. Ten isolated 3E6 and eleven
preceding 3E5 full-parent grammar tests were unsuccessful (retained
under ignored `.analysis/f1137-*`).

**Reproduction:**

    scripts/repo-python scripts/verify-characterobject-current-recovered-f1068.py

No need to replay all 979 exact units. This cold-rebuilds ONLY the
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
| **`0045DD70`** 60,999B | Complete original C++ still substantially unfinished | Original source provenance/giant manifest |

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

## 4. All three remaining independent smaller whole originals

| Complete original | Real native evidence and next meaningful attack |
| --- | --- |
| `0041CE50` ArchiveCatalog nonvirtual destructor **171B /51 x86** | Natural candidate **171B/51 x86**, correct 14 physical PE fields, but only **108/115 nonfield bytes** match. Original genuine pointer stack roles resource `EBP-0xC`, deleting receiver `-0x8`, filename `-0x10`; source cyclically rotates all three. Previous return categories [F1034](ARCHIVE_NATIVE_RETURN_CATEGORIES_F1034.md) and genuine owner lifetimes [F1078](ARCHIVE_TRUE_ELEMENT_LIFETIMES_F1078.md) negative. |
| `0043B0B0` Scene virtual destructor **248B /75 x86** | Genuine 12 PE fields; nearest 248B native shape only **191/200 nonfield bytes**. Actual texture/delete locals differ; [F1015](SCENE_THREE_FREE_DECLARATION_ORDER_F1015.md), [F1048](SCENE_REUSED_TEXTURE_LIFETIMES_F1048.md) negative. |
| `00602A60` WinMain **2,987B /654 x86** | Selected F911 natural source **2,984B/654 x86; 645/654 native widths**. F914 restores original frame/three pointer slots at width cost. Original 60B afterRET scene table is DATA, not code. [F911](WINMAIN_REAL_MAIN_BEFORE_SCENE_F911.md), [F914](WINMAIN_NATIVE_FRAME_FIRST_SCENE_OWNER_F914.md). |

Do NOT artificially patch stack offsets, force dummy locals, add
assembler or crop callables to earn coverage. **All three are NONEXACT**.

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

Preserve `resources/th075.exe`, `.analysis/vc71-wine/`, all current exact
`build/matching/`, Ghidra, current original PE/COFF reference objects,
tracked C++/scripts/config/provenance, and SHA256-indexed archives under
`.analysis/cache-archives/`. **The archives are machine-local, Git-ignored,
not backed up by a fresh clone**. See [storage hygiene and restore
commands](STORAGE_HYGIENE.md). Historical full research evidence and
older handoffs remain available in [history](history/).

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
Do not run a full 979-unit cold replay. Git commits remain local without
network push; hand off the checkout or transfer/push through an
external authorized mechanism.
