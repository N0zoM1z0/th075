# 東方萃夢想 ～ Immaterial and Missing Power

<p align="center"><img src="resources/title-screen.png" width="640" alt="User-supplied TH075 title screen"></p>
<p align="center"><img src="resources/progress.svg" alt="Function reconstruction progress"></p>

**TH075 Japanese v1.11 original x86 complete-function reconstruction** in
ordinary C++, using the actual pinned VC7.1 compiler and comparing full native
PE CODE plus genuine physical COFF relocations. **This is not a complete
playable game or an officially verified distribution rebuild.**

## Current verified snapshot (2026-10-30, F758 exact ledger; F754 maintenance)

| Property | Verified value |
| --- | --- |
| Original | User-supplied Japanese `resources/th075.exe` (v1.11) |
| Size / image base | 2,576,384 bytes / `0x00400000` |
| SHA-256 | `bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98` |
| MD5 | `21bcb855a39f2170195811e6ad292f18` |
| Provisional native candidates | **4,351** |
| Independently origin-reviewed authored candidates | **1,004** |
| Source-present / whole-byte-exact units | **970 / 970** |
| Accepted original CODE | **864,961** bytes |
| Reviewed authored coverage | **43.82%** of **1,973,704** original bytes |
| Conservative authored coverage | **43.75%**, including **3,420** provenance-pending bytes |
| **Authored not exact** | **34** total: **22** large original state advances (**1,102,055 CODE B**) and **12** small/medium functions (**6,688 CODE B**) |
| Independently unknown origin | **95** candidates; **3,420** CODE B uncredited |

**The 98% authored-byte objective is NOT achieved.** The old claim that
only **25** authored functions remained is incomplete: it counted only
`config/functions.csv.owner=authored` pending rows and missed **11**
other independently authored original candidates. F755 and F758 have now accepted two
of those 11, leaving **9** nonexact; their provenance was already recorded
in `config/function-origins.csv`. Those 9 are not accepted exact and must
remain on the small/medium task queue. The original PE, independent
origin ledger, canonical full-function match records and live status
scripts are more authoritative than historical F-series prose.

Read [the short **current agent handoff**](docs/RE_HANDOFF.md) for the
full 34-function original-authored backlog, native source checkpoints
and targeted compiler commands. The previous 1,289-line handoff is
preserved [as a frozen F653–F753 historical archive](docs/history/RE_HANDOFF_F653_THROUGH_F753_2026-10-30.md),
with all local links updated. The [chronological knowledge base](docs/KNOWLEDGE_BASE.md)
is historical experimental evidence, **not** an active status ledger.

## Work on both large and small original functions

The **22 large whole original state-advance functions** are not accepted
whole exact. The most developed `00543210` fighter has 58,294 native CODE B
and separate 943-B after-RET dispatch DATA; ordinary real C++ restores the
native `this` stack frame `EBP−0x44`, and recent F752 restores original
`05D/05E` direct floating-point `FCOMP` grammar. Nonetheless the whole
function's shared tail and other original GPR/EBP geometry still differ.
Use the [F752 physical evidence](docs/FIGHTER_BORROWED_POSITION_F752.md)
and the full-parent targeted verifier, **not** truncated standalone case
credit. The `004EBDA0` 33,293-B original state-advance still has 137
real nonfield register-phase byte differences despite correct whole
opcode widths and 682 real typed fields.

The **12 unmatched small/medium authored originals** include SpriteDrawing
(6), AudioStream (1), TextureManager (2), and WinMain/Scene/Archive (3).
They are fully enumerated in the [active handoff](docs/RE_HANDOFF.md).
For example `0040CA20` has real 92-B/34-x86 projected-quad source but
still differs in the original used local-copy stack frame; do not call
that source exact. Recently accepted complete original AudioStream
constructor `004071C0` is already **161-B cold exact** with its 18
real COFF fields and separately verified EH handler/unwind data,
which is not double-counted ([F753](docs/AUDIO_STREAM_CLIENT_ACQUIRE_F753.md)).
The paired audio client release/destructor `00407270` is now **292-B
whole-function cold exact**, with 24 authentic physical relocations
([F755](docs/AUDIO_STREAM_CLIENT_RELEASE_F755.md)). The original
`00407A50` audio file queue is now **289-B/77-x86/26-reloc cold exact**
([F758](docs/AUDIO_QUEUE_FILE_F758.md)).

## Begin a safe reconstruction session

Read [AGENTS.md](AGENTS.md), [the reconstruction workflow](docs/RE_WORKFLOW.md)
and [the active handoff](docs/RE_HANDOFF.md). Inspect **all** dirty
tracked and ignored research first: one worker owns the worktree.
Use only the pinned original `th075.exe`, **not** `th075c.exe`;
compile serially with pinned VC7.1. Do **not** run an all-unit cold
replay; rerun only the newly added or affected complete source unit.

```bash
git status --short --branch
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/validate-tracking.py --require-target
scripts/repo-python scripts/report-reconstruction-status.py --summary
scripts/repo-python scripts/audit-active-handoff.py
scripts/repo-python scripts/ghidra.py check

# An accepted new/affected complete game function ONLY:
scripts/repo-python scripts/replay-exact-units.py --unit UNIT_NAME
```

Each accepted whole function must preserve complete original control flow,
true native ABI, all COFF relocation owners and independent authored
provenance. Valid compiler source has **no** fake locals, alignment hacks,
assembly patches, truncated game bodies or guessed origin attribution.
Historical original class names and whole object layouts remain provisional.
Commit verified substantial progress locally as **`gpt-web: ...`**;
no push is assumed.

## Storage, historical evidence and recovery

Previous generated diagnostic archives are **ignored and local**, not
stored in Git. Their contents are original-SHA256-verifiable and can be
restored individually. The latest maintenance archived **1,931 old
f133–f166 generated giant ASM/COD/LOG traces**, reclaiming
**86,614,259 bytes** without deleting original source, JSON receipts,
COFF objects, compiler environment, Ghidra project or accepted units.
See [storage hygiene and exact restoration commands](docs/STORAGE_HYGIENE.md)
and `scripts/archive-frozen-giant-traces.py`. **Never delete the locally
ignored archives** without a verified independent replacement backup.
