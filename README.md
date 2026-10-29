# 東方萃夢想 ～ Immaterial and Missing Power

<p align="center"><img src="resources/title-screen.png" width="640" alt="User-supplied TH075 title screen"></p>
<p align="center"><img src="resources/progress.svg" alt="Function reconstruction progress"></p>

This repository reconstructs **TH075 (ver1.11) functions in natural C++**, comparing
complete VC7.1-compiled x86 code and all physical COFF relocations against a
user-supplied executable. It is **not yet a complete game rebuild**.

## Pinned target and progress

| Property | Value |
| --- | --- |
| Target | Japanese `th075.exe` (ver1.11), supplied by the user |
| Size / image base | 2,576,384 bytes / `0x00400000` |
| SHA-256 | `bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98` |
| MD5 | `21bcb855a39f2170195811e6ad292f18` |
| Source-present / exact functions | **943 / 943** |
| Accepted CODE bytes | **862,726** |
| Reviewed authored coverage | **43.71%** of 1,973,704 reviewed bytes |
| Conservative coverage | **43.64%**, with 3,420 origin-pending bytes included |
| Unresolved origins | **95** of 4,351 provisional function candidates |

**The 98% authored-byte goal is incomplete.** Function labels and C++ owner
types are provisional; machine-code matches alone do not prove an entire
original class layout. The target's official distribution provenance has not
been independently verified; do not substitute a localized `th075c.exe`.

These snapshot counts were rechecked after **F652** (2026-10-29).
The **live** sources of truth, not any dated prose milestone, are `config/functions.csv`,
`config/function-origins.csv`, and `config/match-units.toml`.
Refresh using `scripts/repo-python scripts/report-reconstruction-status.py --summary`.

The original authored backlog is **25 whole functions**: **22 large fighter
bosses** totaling **1,102,055 uncredited CODE bytes** (plus 16,123 distinct
after-RET switch DATA bytes), the 2,987-byte WinMain, 248-byte battle scene
destructor and 171-byte archive catalog destructor. **No giant is currently
accepted whole exact.** The 95 origin-unknown candidates are a separate
classification issue and cannot be silently counted as game-authored CODE.

### Latest verified giant research and complete small-function evidence

The one native giant `004EBDA0` now compiles from ordinary VC7.1 C++ into
the same **33,293 bytes of CODE, 8,789 x86 instructions in identical order,
and 438 after-RET DATA-layout bytes**. All **682 physical typed PE COFF
fields** and 198 original sparse-index bytes are independently checked.
Following F596's genuine C++ evaluation-order corrections, **30,866/31,003
nonrelocation bytes match**; **137 bytes in three register-allocation case
bodies remain wrong**. This is outstanding, **not a fully byte-exact
33K function**. Reproduce via
`scripts/repo-python scripts/verify-characterobject-native-collision-order-f596.py`.

**F598–F652's 572 strictly source-backed fighter *internal case
bodies* (154,461 original internal CODE bytes) remain uncredited**:
none of their enclosing giant `Advance()` functions is fully exact.
The latest strict evidence is four consecutive native `CF/D0/D1/D2`
cases in giant `00543210` (223 real x86, 759 internal CODE bytes,
28 physical fields); only the last `D1/D2` (450 bytes) were newly
reconstructed in F651/F652. Native complex `0xCC` in `005AEEC0`
and `00564BE0` still has **80/78 genuine wrong GPR/CFG roles**
despite matching x86 count and all 11 real PE/COFF fields; **do not
promote** it to exact just because the case body geometry matches.

Separately, recent **whole-function** VC7.1 C++ probes have fully
reproduced 39 origin-unknown original functions /889 native CODE bytes,
plus the distinct prior F595 **40-byte** three-field setter: **40
complete origin-unknown source-backed originals /929 bytes**, all
uncredited pending authored-vs-compiler/library provenance. The newest
pair is `004170B0` (**27/27 bytes**, virtual `__stdcall` slot) and
`004588B0` (**43/43 bytes**, original conditional CRT `free`).
All previously accepted 111-byte mapping transform `00455770`,
77-byte Shift-JIS classifier `0041CA30`, Replay render, StaffRoll,
rank-label and selected-progress functions stay accepted exact.
Do not revive their superseded negative experiments.

For the actual unresolved work, start with the
[short current agent handoff](docs/RE_HANDOFF.md); the full *former* [F598–F652 active-handoff research narrative](docs/history/RE_HANDOFF_F598_THROUGH_F652_2026-10-29.md)
and still older [F540–F596 chronology](docs/history/RE_HANDOFF_F540_THROUGH_F596.md)
preserve the original experimental detail without cluttering the first
screen. Both are **frozen historical sources, not the live backlog**. Git commits preserve local checkpoints; they are
**not external Oracle acceptance**.

## Begin a new reconstruction session

**Read [the current agent handoff](docs/RE_HANDOFF.md) first.** It lists current
unresolved large functions, the latest accepted units, private research to
retain and the next experiments. Then follow
[AGENTS.md](AGENTS.md), [the reconstruction workflow](docs/RE_WORKFLOW.md)
and the [source-backed knowledge base](docs/KNOWLEDGE_BASE.md).

Inspect **all dirty work** before editing; do not discard it because an
earlier agent left it. Address both large/core functions and small helpers,
recheck old hypotheses against native instructions, and promptly commit
substantial accepted progress using `gpt-web: ...` subjects.
Preserve and continue all pre-existing dirty work; the user reports no other active reconstruction session.

From the repository root:

```bash
git status --short --branch
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/validate-tracking.py --require-target
scripts/repo-python scripts/report-reconstruction-status.py --summary
scripts/repo-python scripts/audit-active-handoff.py
scripts/repo-python scripts/ghidra.py check
```

Use the hash-checked `scripts/repo-python` wrapper, not arbitrary system
Python. For a new installation see `scripts/bootstrap-python.sh` and
`scripts/bootstrap-tools.sh`; **do not re-import or overwrite the
already initialized target/Ghidra project**.

## Complete-function matching

Full source and all relocations for each accepted function are registered
in `config/match-units.toml`. Reconstruct the genuine function, including
all exits and owned jump tables. `structural-exact` excludes relocation
fields and is **only diagnostic**. Acceptance requires an independent
pinned-compiler cold replay:

```bash
scripts/repo-python scripts/replay-exact-units.py --unit UNIT_NAME
scripts/repo-python scripts/validate-tracking.py --require-target
git diff --check
```

For probes, use VC7.1 build 3077 with explicit per-unit flags, serialized
headless Wine processes and the existing tools. Do not manufacture byte
matches with copied target bytes, assembly, arbitrary padding, masks or
unproved owner layouts. Do not count external data or runtime helper bytes.
Keep the 95 unresolved origin candidates uncredited.

Keep validation focused on exact reconstruction: `scripts/ci.py` runs the small
comparison/checkpoint/byte-accounting suite without compiling accepted units.
Run it when that infrastructure or its tests change. Cold-replay only new or
affected units; routine acceptance and handoff need no additional suite.
Do not add a test file per function, duplicate source-text assertions, or
allocation-failure/null-pointer tests. Do not run the full historical suite.
Historical origin tests remain available for changes to
their evidence or verifiers. See [the workflow](docs/RE_WORKFLOW.md).

## Finding information

| Resource | Purpose |
| --- | --- |
| [Current handoff](docs/RE_HANDOFF.md) | Live status and next practical tasks |
| [Reconstruction workflow](docs/RE_WORKFLOW.md) | Step-by-step native analysis, VC7.1 matching, acceptance |
| [Knowledge base](docs/KNOWLEDGE_BASE.md) | Detailed F-series proofs, rejected attempts and limitations |
| [Build and matching guide](docs/BUILD_MATCHING.md) | Compiler profiles, COFF and cold-replay mechanics |
| [Ghidra MCP guide](docs/GHIDRA_MCP.md) | Headless project/bridge operation |
| [Origin review](docs/ORIGIN_PENDING_REVIEW.md) | 95 currently unclassified origins (R263 historical matrix) |
| [Frozen F598–F652 detailed handoff](docs/history/RE_HANDOFF_F598_THROUGH_F652_2026-10-29.md) | Full old 1,500-line evidence narrative; **not** current backlog |
| [Historical detailed F540–F596 handoff](docs/history/RE_HANDOFF_F540_THROUGH_F596.md) | All previous milestone notes; **not** current backlog |
| [Earlier handoffs](docs/history/RE_HANDOFF_THROUGH_F183.md) | Older archived experiments |
| [Storage protection and recovery](docs/STORAGE_HYGIENE.md) | Recoverable native evidence, historic PDB/CI logs, and latest **219 old JSON diagnostics → 4 SHA256-verified archives (≈244.66 MiB net reclaimed)** plus normal Git GC (≈371.62 MiB); **≈616.28 MiB total** without discarding current source, original PE, VC7.1/Wine, Ghidra or accepted COFF objects |

The pre-cleanup verbose F223 handoff and README are also recoverable from
Git commit `ca81d72`; older origin work is retained under `docs/history/`,
`docs/RE_HANDOFF_HISTORY.md` and `docs/ORIGIN_REVIEW.md`. Private native
analysis, experiments and build objects are ignored by Git and must remain in
the **same workspace** when changing agents. Protect the `.analysis/vc71-wine`
tool environment, shared `.tools` installations and `ghidra-project`.

## Copyright and license

Repository code and documentation use the [MIT license](LICENSE).
The game, its data and supplied artwork retain their original rights. No
game executable, protected analysis database, downloaded toolchain or private
MCP endpoint is distributed with this repository.
