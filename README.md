# 東方萃夢想 ～ Immaterial and Missing Power

<p align="center"><img src="resources/title-screen.png" width="640" alt="User-supplied TH075 title screen"></p>
<p align="center"><img src="resources/progress.svg" alt="Original authored-byte reconstruction progress"></p>

This is **Japanese TH075 v1.11 original x86 whole-function reconstruction**
in ordinary C++ under the original pinned VC7.1 compiler. It is
**not a complete playable game or an official executable rebuild**.
Only original, attributable, byte-identical **whole callable functions**
earn canonical exact CODE credit. An internal case, original PE-similar
mnemonic stream or matching total source length is not acceptance.

## Current verified status (2026-10-31, F1029 research / 979 exact ledger)

| Property | Grounded result |
| --- | --- |
| Pinned original | User-supplied Japanese resources/th075.exe v1.11 |
| SHA-256 | bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98 |
| Original PE image base / file bytes | 0x00400000 / 2,576,384 |
| Provisional native candidates | 4,351 |
| Independently source-attributed original authored functions | 1,004 |
| Complete accepted exact native function units | **979 / 979** |
| Accepted entire callable original CODE | **868,243** B |
| Reviewed authored-byte coverage | **43.99%** of **1,973,704** B |
| Conservative authored coverage | **43.91%** |
| Original authored functions still NONEXACT | **25**: **22** large original state advances (1,102,055 B) plus **3** small/medium original functions (3,406 B) |
| Original origin-unknown candidate rows | 95 (3,420 uncredited CODE B) |

The 98% authored-byte goal is **NOT met**. Previously confusing
"25 pending plus 11" counts belong to older source-origin
checkpoints: the additional eleven were accepted through F780.
There are currently **25 total** nonexact attributed originals,
not 27 or 36. The original PE, independent provenance decisions,
whole [exact match units](config/match-units.toml) and
live [reconstruction report](scripts/report-reconstruction-status.py)
always outrank historical F-series prose.

## Start here: current task queue

The [**short active agent handoff**](docs/RE_HANDOFF.md) provides
the latest evidence, unresolved original x86 differences, all
25 remaining whole-function targets and targeted reproductions.
The [source workflow](docs/RE_WORKFLOW.md), [AGENTS.md](AGENTS.md),
and [storage and recovery policy](docs/STORAGE_HYGIENE.md) apply
to every session. The [knowledge base](docs/KNOWLEDGE_BASE.md)
is a historical experiment journal, **not** a live status report.

The old detailed handoff through F906 was frozen as a
[fully linked historical snapshot](docs/history/RE_HANDOFF_F781_THROUGH_F906_PRE_CLEANUP_2026-10-31.md).
Research performed against an earlier partial fighter or
an old compiler context remains useful evidence but must not
be asserted as the current whole-function result.

### Work on the entire giant Boss functions **and** complete small originals

Three large original fighters now have independent **whole-function**
original PE destination audits. Their normal VC7.1 C++ is promising,
but **none is accepted exact**:

| Native whole Boss | Current partial whole-source geometry | Physical original external PE target evidence |
| --- | --- | ---: |
| `004AC040` 82,796B | **82,796B/22,721 x86**, native frame and saved this; still **12 width /6,958 GPR** defects | [F1028](docs/THIRD_FIGHTER_WHOLE_82KB_PE_TARGETS_F1028.md): **2,191/2,191** |
| `00543210` 58,294B | **58,293B/16,471 x86**; still **3 width /1,741 GPR** defects | [F1025](docs/FIGHTER_58KB_ALL_NATIVE_PE_TARGETS_F1025.md): **1,697/1,697** |
| `005214B0` 46,755B | **46,754B/13,230 x86**; still **5 native width** defects | [F1026](docs/FIGHTER_46KB_ALL_NATIVE_PE_TARGETS_F1026.md): **1,341/1,341** |

These **5,229** physical native PE targets are genuine call/global
addresses, **not** proof that the whole machine bytes, GPR allocation,
jump displacements or COFF field positions match. Specifically,
F1020's [native 82KB frame/counter correction](docs/THIRD_FIGHTER_SHARED_REAL_RING_LOCAL_F1020.md)
recovered one real shared 2DB shot-loop variable, while
[F1029](docs/THIRD_FIGHTER_NATIVE_259_ANGLE_GPR_F1029.md) rules out
eight angle-expression spellings without improving the remaining
register phase. The **81,539B `0050A580`** and **60,999B
`0045DD70`** whole originals, plus the other 18 large originals,
must also be attacked seriously; the
[original dispatch manifest](config/fighter-boss-dispatch-fingerprints.json)
provides the true extents and jump DATA owners.

Three complete smaller original authored functions are still
nonexact: **`0041CE50`** Archive destructor (**171B**),
**`0043B0B0`** Scene virtual destructor (**248B**),
and **`00602A60`** WinMain (**2,987B**). Their latest
native stack/owner evidence is [F936 Archive](docs/ARCHIVE_NATIVE_LOOP_VALUE_CATEGORIES_F936.md),
[F1015 Scene](docs/SCENE_THREE_FREE_DECLARATION_ORDER_F1015.md),
and [F914/F911 WinMain](docs/WINMAIN_NATIVE_FRAME_FIRST_SCENE_OWNER_F914.md).
All three still need original full-function byte equality.

Already accepted leaf/code semantics are also actively improved:
[F1022 script WORDs](docs/FIGHTER_SCRIPT_COUNTER_ADJACENT_NATIVE_F1022.md)
**46/46 whole cold exact**;
[F1024 animation counters](docs/FIGHTER_ANIMATION_PHASE_WINDOW_F1024.md)
**9/9**; [F1027 action/timer WORDs](docs/FIGHTER_NATIVE_ACTION_TIMER_PAIR_F1027.md)
**46/46**. These bytes were accepted before those type improvements,
so no duplicate authored CODE credit is due.

## Safe reconstruction workflow

Treat the Git worktree as one worker's work. Inspect **all**
dirty tracked, untracked and relevant ignored research.
Always verify the SHA-pinned original th075.exe, **never**
substitute th075c.exe, and compile only the touched unit
serially under the pinned headless Wine VC7.1 toolchain.

Read-only preflight (no native compiler replay):

    git status --short --branch
    scripts/repo-python scripts/verify-target.py
    scripts/repo-python scripts/validate-tracking.py --require-target
    scripts/repo-python scripts/report-reconstruction-status.py --summary
    scripts/repo-python scripts/audit-active-handoff.py
    scripts/repo-python scripts/ghidra.py check

Only newly accepted or modified **complete callable game functions**
need a targeted canonical replay:

    scripts/repo-python scripts/replay-exact-units.py --unit UNIT_NAME

Do **not** run all 979 exact units as a cold replay.
For normal source experiments use the current unit's
targeted verifier linked from [the handoff](docs/RE_HANDOFF.md).
No fake stack locals, forced assembly register patches,
unproved original provenance, case-only accepted bytes
or masked physically shifted PE relocation fields.
Commit substantial progress several times per session using
the required prefix **gpt-web: xxx**. Git commits are
checkpoints, not Oracle acceptance; no push is assumed.

## Storage, original evidence and recoverability

The original EXE, VC7.1/Wine prefix, Ghidra project,
accepted matching objects, source, manifests, and
uncredited original PE receipts must be preserved.
F1031 also losslessly SHA256-archived **1,749 newer
F907–F1018 historical research OBJ/PDB copies**, recovering
**93,546,883 bytes net (≈89.21 MiB)** after fully
verifying the archive before and after loose-file removal.
The current F917/F901/F1020 whole native parents,
recent experiments, original game evidence and all
previous archive indexes remain protected. Recover a
single older original binary with
`scripts/repo-python scripts/archive-recent-probe-objects-f1031.py --family binaries --restore ORIGINAL_RELATIVE_PATH`.
See the [verified F1031 archival receipt and safety rules](docs/STORAGE_HYGIENE.md).
A further **92 automatically regenerable CPython bytecode caches**
(2,228,154 file bytes) were safely cleared from scripts/tests.
Combined new F1031/F1032 measured file-byte savings:
**95,775,037 B**. Future Python execution may regenerate them.

F907 additionally archived **4,712 regenerable historical
VC7.1 OBJ/PDB research copies**, recovering **220,205,684 bytes**
net after whole-archive SHA256 verification. Safe standard Git
object maintenance reclaimed another **116,556,933 bytes**, and
pure regenerated Python bytecode cleanup recovered **12,665,361 bytes**.
All three changes together reclaimed **349,427,978 B (333.24 MiB)**.
The locally
ignored archive must be retained; restore individual old binaries
through scripts/archive-recent-probe-objects-f907.py.
Older loose machine-generated diagnostics were
compressed into **local, ignored, SHA256-verified
archives**: they are **not included in Git clones**.
Use [storage hygiene and exact recovery](docs/STORAGE_HYGIENE.md)
and scripts/archive-frozen-giant-traces.py to verify or
restore individual original historical traces.
Do not delete the only local copy of compressed
research or compiler/PE provenance evidence.
