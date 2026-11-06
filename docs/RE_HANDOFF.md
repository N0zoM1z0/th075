# TH075 — CURRENT AGENT HANDOFF (2026-11-06, F1240)

Read [AGENTS.md](../AGENTS.md), [workflow](RE_WORKFLOW.md) and
[storage/recovery](STORAGE_HYGIENE.md). The handoff cleanup preserves F1239's
complete `0057D580` source; no new exact acceptance is claimed. The user reports
no other active sessions. Inspect and continue all dirty work if any appears;
never reset it or attribute it to another worker. Use local `gpt-web: ...` commits,
serial compiler builds, the existing Ghidra wrapper, and `scripts/repo-python`.
Do not use REA or replay the entire exact corpus.

## 1. Original native PE and complete-function exactness

Pinned target: user-supplied Japanese TH075 v1.11 `resources/th075.exe`, SHA256
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
This identifies the user's archive; it is not independently authenticated
against an official distribution. Never substitute `th075c.exe`.

**982 functions / 982 exact units**, **871,649 original CODE bytes**;
reviewed denominator **1,973,704**, coverage **44.16%** / **44.09%** conservative.
**1,004** independently authored originals; **22 authored functions remain nonexact**:
**22 large original state advances** (**1,102,055 CODE bytes**) and
**0 other original small/medium whole functions** (**0 CODE bytes**).
There are 4,351 provisional candidates; 95 origin-unknown rows contribute
3,420 pending bytes to the conservative denominator and remain uncredited.
The 98% authored-byte objective is incomplete.

Use `config/function-origins.csv` for attribution and the canonical manifests
for acceptance. Neither an exact machine function nor a mapped name proves
ownership. All R268 and later accepted exact/origin evidence remains valid
unless independently disproved. Interior states earn no whole-function credit.

## 2. Primary large Boss — original 0050A580 (81KB)

Complete research source:
[`CharacterObjectWhole0050A580F1044.cpp`](../probes/CharacterObjectWhole0050A580F1044.cpp),
including genuine `CharacterObjectBoss*.inc` state bodies. Live selected
COFF/receipts: `.analysis/f1068-boss-live-all-native/`.

| Whole observation | Original PE | Current complete C++ |
| --- | ---: | ---: |
| CODE /instructions | 81,539B /17,435 | 81,542B /17,435 |
| Frame /saved this | 0x3A0 /EBP-0xAC | Both agree |
| Raw EBP operand positions | 5,717 | All agree |
| Direct branch target ordinals | 1,834 | All agree |
| CODE reference destinations /dense ordinals | 1,357 /92 | All agree |
| Owned after-RET DATA extent | 567B | 567B |
| Remaining GPR positions /widths | — | **522 /5** |

All remaining GPR/width debt is in **358–35E and 3E6**. Eight provisional case
intervals remain; the 83 strict interiors (76,519 native B /16,367 x86) are
not accepted functions. Old claims of 13 wrong branches, wrong stack slots,
or unresolved391 x87 fields are superseded by
[CFG F1148](CHARACTEROBJECT_NATIVE_ALL_DIRECT_CFG_F1148.md),
[x87 F1149](CHARACTEROBJECT_NATIVE_391_TRANSFORM_X87_F1149.md),
[stack F1150](CHARACTEROBJECT_NATIVE_ALL_STACK_SLOTS_F1150.md), and
[whole operand F1158](CHARACTEROBJECT_WHOLE_OPERAND_PROOF_F1158.md).

[F1181](CHARACTEROBJECT_NATIVE_EFFECT_ABI_F1181.md) aligns seven parameter
views/six callees with identical CODE+DATA and 1,449 COFF field shapes.
Preserve raw coordinate/angle DWORD transport: float-lvalue arguments add329
instructions. Retain rejected F1137 grammars, F1151 type/assignment controls
and F1194 nested guards; do not repeat them as new evidence.

Affected-parent verifier (builds only this whole parent):

    scripts/repo-python scripts/verify-characterobject-current-recovered-f1068.py

**NONEXACT.** Matching destination ordinals does not establish physical
relocation-offset or raw byte equality when widths differ.

## 3. Complete research parents and remaining giant targets

There are **13 complete tracked research bodies, all NONEXACT**, including
0050A580 above. The other twelve are below. GPR counts are raw instruction
positions, not bytes. Each linked proof records native evidence, compiler
profile, selected source snapshot and rejected controls.

| Original | Complete tracked source /current proof | Original CODE → source CODE /x86 | Remaining GPR /widths |
| --- | --- | ---: | ---: |
| 004AC040 | [F1020 source](../probes/FighterWhole004AC040F1020.cpp), [F1203 proof](THIRD_FIGHTER_NATIVE_CALL_ABI_F1203.md) | 82,796 →82,796 /22,721 | 6,958 /12 |
| 00543210 | [F1041 source](../probes/FighterWhole00543210F1041.cpp), [F1196 proof](FIGHTER_58KB_WHOLE_CFG_OPERANDS_F1196.md) | 58,294 →58,293 /16,471 | 1,741 /3 |
| 005214B0 | [F1040 source](../probes/FighterWhole005214B0F1040.cpp), [F1197 proof](FIGHTER_46KB_WHOLE_CFG_F1197.md) | 46,755 →46,754 /13,230 | 2,736 /5 |
| 0045DD70 | [F1183 source](../probes/FighterWhole0045DD70F1183.cpp), [F1192 proof](REIMU_WHOLE_STACK_CFG_F1192.md) | 60,999 →61,000 /16,837 | 6,311 /5 |
| 0055AC80 | [F1194 source](../probes/CharacterObjectWhole0055AC80F1194.cpp), [F1194 proof](OBJECT_ADVANCE_0055AC80_WHOLE_F1194.md) | 28,432 →28,438 /7,653 | 726 /6 |
| 004EBDA0 | [F572 source](../probes/CharacterObjectActionsF572.cpp), [F1205 proof](OBJECT_ADVANCE_004EBDA0_WHOLE_F1205.md) | 33,293 →33,293 /8,789 | 133 /0 |
| 005EB520 | [F1207 source](../probes/CharacterObjectWhole005EB520F1207.cpp), [F1209 proof](OBJECT_ADVANCE_005EB520_VIRTUAL_ABI_F1209.md) | 34,434 →34,436 /9,378 | 135 /6 |
| 00536400 | [F1211 source](../probes/CharacterObjectActions00536400F1211.cpp), [F1214 proof](OBJECT_ADVANCE_00536400_COMPLETE_PARENT_F1214.md) | 39,999 →39,997 /10,573 | 913 /10 |
| 005C9CC0 | [F1216 source](../probes/CharacterObjectActions005C9CC0F1216.cpp), [F1219 proof](OBJECT_ADVANCE_005C9CC0_COMPLETE_PARENT_F1219.md) | 43,501 →43,502 /11,447 | 935 /1 |
| 004CA6E0 | [F1222 source](../probes/CharacterObjectActions004CA6E0F1222.cpp), [F1227 proof](OBJECT_ADVANCE_004CA6E0_COMPLETE_PARENT_F1227.md) | 42,511 →42,515 /11,201 | 447 /12 |
| 005A1600 | [F1231 source](../probes/CharacterObjectActions005A1600F1231.cpp), [F1236 proof](OBJECT_ADVANCE_005A1600_REGISTER_BOUNDARY_F1236.md) | 43,599 →43,596 /11,620 | 613 /11 |
| 0057D580 | [F1237 source](../probes/CharacterObjectActions0057D580F1237.cpp), [F1239 proof](OBJECT_ADVANCE_0057D580_COMPLETE_PARENT_F1239.md) | 43,845 →43,849 /11,694 | 914 /6 |

Selected private objects and whole diagnostics are **preserved loose**:

| Original | Directory below `.analysis/` | Selected OBJ /whole diagnostic |
| --- | --- | --- |
| 004AC040 | `f1203-third-native-call-abi/` | `tracked.obj` /`whole-audit.py` |
| 00543210 | `f1196-58kb-whole-cfg/` | `tracked.obj` /`whole-audit.py` |
| 005214B0 | `f1197-46kb-whole-cfg/` | `tracked.obj` /`whole-audit.py` |
| 0045DD70 | `f1193-reimu-register-boundary/` | `adopted.obj`; audit in `f1192-reimu-final-states/whole-audit.py` |
| 0055AC80 | `f1194-remilia-whole-recovery/` | `tracked.obj` /`audit.py` |
| 004EBDA0 | `f1205-object-4ebda0-recovery/` | `before.obj` /`whole-audit.py` |
| 005EB520 | `f1209-object-5eb520-virtual-abi/` | `tracked.obj` /`whole-audit.py` |
| 00536400 | `f1214-object-536400-complete/` | `current.obj` /`whole-audit.py` |
| 005C9CC0 | `f1219-object-5c9cc0-late/` | `native-order.obj` /`whole-audit.py` |
| 004CA6E0 | `f1227-object-4ca6e0-complete/` | `compound-counter.obj` /`whole-audit.py` |
| 005A1600 | `f1236-object-5a1600-loop-scope/` | `float-copy909.obj` /`whole-audit.py` |
| 0057D580 | `f1239-object-57d580-remaining/` | `complete.obj` /`whole-audit.py` |

These diagnostic scripts normally take `[OBJ]`; consult their recorded
invocations. Do not rebuild all parents. Use recorded per-unit flags:
004AC040 requires **/GX**; 005EB520 uses **/GX- without explicit /GS**.
Selected source hashes/snapshots, original/native inputs and JSON receipts
remain available. F1025/F1026/F1028 certify external PE destinations,
not physical source relocation offsets or full callable equality.

**Resume boundaries and known negatives:**

- **004AC040:** first 004ADEFA /whole2180. Preserve F1198 shared-getter/default
  skip, F1199 operands and F1200 CFG. F1201/F1202/F1204 controls are rejected;
  [debt map](THIRD_FIGHTER_REGISTER_DEBT_MAP_F1202.md) retains native36-call bodies.
- **00543210 /005214B0:** preserve getter-only 0/2/4/5 entries and ordinary
  post-getter exits. Debt is respectively63 and 63/1FD/252/254. All current
  stack/CFG/non-GPR operands agree; old F917/F901 parents remain protected.
- **0045DD70:** first 59 at0045FDA9 /whole2292; keep F1193 short parameters/getter.
  F1193 and F792/F793 negatives do not override the complete current parent.
- **0055AC80:** debt 389–392, first 0055F711 /whole5225. Chaining, DWORD/array/
  member/guard and /Op controls failed; [F1195](OBJECT_ADVANCE_0055AC80_JOIN_NEGATIVES_F1195.md).
- **004EBDA0:** all real cases/default already present; do not restart F569 markers.
  137 nonfield bytes /133 GPR positions remain:38D45/38E64/3E3first31=24.
  First004F344C /whole8076 /38D91; all native widths and 682 bindings agree.
- **005EB520:** all 60 states/default and virtual slot1 attribution retained.
  Debt only 998, first 005F3904 /whole9200; F1208 controls are exhausted.
- **00536400:** all 66 states; debt 829–835/906–912, first 005392F8 /whole3223.
- **005C9CC0:** all 67 states; debt 918–929, first 005D2558 /whole9213.
  Sole width005D2841 /whole9411 in 919; retain twelve F1219 rejected controls.
- **004CA6E0:** all 55 states; debt 808–811, first 004CCBD7 /whole2526.
  Preserve906 compound update. F1224/F1228–F1230 increment, bound, /G7,
  comma and indexed-expression controls failed.
- **005A1600:** all 76 states/six indices; debt 909–917 opening, first 005A88A8
  /whole7965, last 005A95C7 /8879. All 790 differing register operands share
  EAX→ECX→EDX→EAX; cause unproved. Scope movement breaks20 EBP operands.
  F1235 loop-update and F1236 return/condition/index controls failed. Two
  retained float assignments leave entire CODE/DATA/all 943 COFF records unchanged.
- **0057D580 (latest):** all 70 states, frame 378h /this-40h /ESI, all 3,929 EBP
  positions,1,162 direct targets,972 CODE destinations,71 dense ordinals and 198
  sparse bytes agree. DATA extent482B. Debt837–838/903–904/911–919/995 opening;
  first 00583489 /whole6565, last 00587806 /11161. Allsix widths in 838, first
  00583620 /6677. Reversing837 equality reads the limit before the frame-progress
  call and worsens native order/debt; rejected. Selected source is restored
  byte-for-byte to `complete.cpp`, SHA256
  `293d8a165e563b3fc08fe218247b4914b588e160552b50b695c8765bd165c7a8`.
  Actual OBJ/PDB live in `build/probes/f1239-object-57d580/`; private OBJ links
  point there. Keep F1237 native/owner and F1238 loop evidence too.

The other **nine independently authored giants lack complete tracked research
bodies**: objects **00476A40 (50,915B),0049C8F0 (46,596B)**; fighters
**00486550 (50,735B),004D7E70 (43,601B),004F7130 (44,211B),00564BE0 (61,872B),
0058AF60 (49,230B),005AEEC0 (71,616B),005D73C0 (43,282B)**.
Existing native/partial source evidence remains preserved. Check the
[dispatch manifest](../config/fighter-boss-dispatch-fingerprints.json) and
[origin ledger](../config/function-origins.csv) before choosing a target.

## 4. Remaining independent smaller whole originals

**None pending.** F1155 accepted the complete 171B ArchiveCatalog destructor
0041CE50 ([proof](ARCHIVE_CATALOG_ARRAY_DELETE_EXACT_F1155.md)); F1157 accepted
complete 248B BattleScene destructor0043B0B0
([proof](BATTLE_SCENE_TYPED_DELETE_EXACT_F1157.md)); F1171 accepted
complete 2,987B WinMain00602A60 plus 60B owned DATA/all 173 fields
([proof](WINMAIN_WHOLE_EXACT_F1171.md), [source](../src/WinMainF1171.cpp)).
Do not reopen F911/F914 as the current WinMain parent.

F1156 reconciled65 historical source-hash revisions and 29 headers: **all 268
actually affected units across 66 serial objects cold-replayed exact**.
[Evidence](ACCEPTED_SOURCE_PIN_RECONCILIATION_F1156.md) preserves prior hashes.
Do not repeat completed replay without an affected input change.

## 5. Validation and transfer

Run from the repository root before reconstruction edits:

    git status --short --branch
    scripts/repo-python scripts/verify-target.py
    scripts/repo-python scripts/validate-tracking.py --require-target
    scripts/repo-python scripts/report-reconstruction-status.py --summary
    scripts/repo-python scripts/audit-active-handoff.py
    scripts/repo-python scripts/ghidra.py check

For research changes, build/audit only the affected whole parent. Exact
acceptance requires `scripts/repo-python scripts/replay-exact-units.py --unit NAME`.
Replay affected dependents when shared headers/ABI/flags/relocations change.
No full corpus replay or per-function robustness tests. Run CI only when changing
comparison/checkpoint/byte-accounting/test infrastructure. Preserve truthful
natural C++, one source body, complete extents and every relocation. No assembly,
fake locals, padding or instantiated incomplete owners.

**Storage and private evidence:** F1240 compacts only frozen F1133–F1230
OBJ/PDB and generated COFF listings outside selected proof directories.
All 91 native disassembly views from the initial listing batch are restored
and hash-verified loose; they are excluded from further compaction. All source,
JSON/log/native inputs, selected parents above, F1231+ research, accepted
`build/matching/`, original PE, Wine, Ghidra and prior archives remain preserved.
Use [`archive-handoff-outputs-f1240.py`](../scripts/archive-handoff-outputs-f1240.py)
and the measured [storage/recovery report](STORAGE_HYGIENE.md). Archival savings
are 46.11 MiB; ordinary Git GC/cache cleanup brings the measured operations to
79.33 MiB. Git connectivity checks pass before/after GC. Every archive
and adjacent receipt under `.analysis/cache-archives/` is **Git-ignored**:
a fresh clone or pushed tracked commit does not transfer them. Hand over the
existing checkout, or copy the full private environment plus archives/receipts.
Do not publish game binaries, tools, private settings, or generated decompiles.

Detailed historical evidence is linked from proofs and the
[knowledge journal](KNOWLEDGE_BASE.md). Older handoffs are frozen in
[F1142](history/RE_HANDOFF_AS_OF_F1142_PRE_HANDOFF_2026-11-04.md) and
[F781–F906](history/RE_HANDOFF_F781_THROUGH_F906_PRE_CLEANUP_2026-10-31.md).
Old giant traces remain individually recoverable through
[`archive-frozen-giant-traces.py`](../scripts/archive-frozen-giant-traces.py).
Historical dimensions/negative controls apply to their recorded parents.
Local commits are checkpoints; no network push or external acceptance is implied.
