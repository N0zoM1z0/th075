# 東方萃夢想 ～ Immaterial and Missing Power

<p align="center"><img src="resources/title-screen.png" width="640" alt="User-supplied TH075 title screen"></p>
<p align="center"><img src="resources/progress.svg" alt="Original authored-byte reconstruction progress"></p>

This is **Japanese TH075 v1.11 original x86 whole-function reconstruction**
in ordinary C++ under the original pinned VC7.1 compiler. It is
**not a complete playable game or an official executable rebuild**.
Only original, attributable, byte-identical **whole callable functions**
earn canonical exact CODE credit. An internal case, original PE-similar
mnemonic stream or matching total source length is not acceptance.

## Current verified status (2026-10-31, F906 research / F780 exact ledger)

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

### Do substantial work on big Boss functions and small originals

The major research target **005214B0** has **46,755 original CODE B /
13,230 original x86**, plus 901 separate packed afterRET DATA B.
The currently selected normal VC7.1 source emits
**46,754 B /13,230 x86**. While all original native
mnemonics line up, **five opcode widths**, **443 original-absolute
PE field offsets** and many real register roles remain wrong.
[F901 whole-fighter source/PE audit](docs/SCRIPTED_FIGHTER_COMPLETE_TAIL_AND_WIDTH_AUDIT_F901.md)
and [F906 first GPR mismatch at 0052327A](docs/FIGHTER_FIRST_GPR_DIVERGENCE_F906.md)
are the best next steps. **The whole fighter is NOT exact.**

The original **00543210** fighter is another 58,294-B whole giant
with 943 separately owned afterRET DATA B; it and the
other 20 giant originals remain nonexact. Large original
functions **004AC040** (82,796 B), **0050A580** (81,539 B),
and **0045DD70** (60,999 B) must not be neglected in favor
of leaf-only reconstruction.

The three independent nonexact whole-function targets are
**0041CE50** (Archive destructor, 171 B),
**0043B0B0** (Scene destructor, 248 B) and
**00602A60** (WinMain, 2,987 B). The latest real
lifetime/ABI experiments are
[F900 Archive](docs/ARCHIVE_REAL_GROUPED_LIFETIMES_F900.md),
[F889 Scene](docs/SCENE_MIXED_REAL_FREE_POINTER_OWNERS_F889.md),
and [F904 WinMain](docs/WINMAIN_REAL_STAGE_OWNER_LIFETIMES_F904.md).
All three remain nonexact, despite fully compiled C++ experiments.

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
F907 additionally archived **4,712 regenerable historical
VC7.1 OBJ/PDB research copies**, recovering **220,205,684 bytes**
net after whole-archive SHA256 verification. The locally
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
