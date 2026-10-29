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

These snapshot counts were rechecked after **F664** (2026-10-30).
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
F659's 14 additional whole-giant C++ condition/lifetime variants did
not reduce the genuine 137-byte register cycle; two `+=` alternatives
actually changed native x87 geometry. [New F659/F660 negative evidence](docs/GIANT_REGISTER_AND_ARCHIVE_LIFETIME_NEGATIVES_F659_F660.md).

**F598–F664's 587 strictly source-backed fighter *internal case
bodies* (158,673 original internal CODE bytes) remain uncredited**:
none of their enclosing giant `Advance()` functions is fully exact.
F664 strictly reconstructs original `0x200/0x201` inside the real
58KB giant `00543210`: **228 genuine original x86 instructions,
779 original internal CODE bytes and 17 physical PE/COFF fields**.
The same newly compiled entire fighter verifies **all 17 previous
strict cases, three retained native EBP scratch negatives and the
full independent after-RET switch DATA**. The selected giant now has
**19 strict original internal cases /1,437 native x86 /4,971
internal CODE bytes /132 original PE/COFF fields**. This is **not**
whole-function exact: original `0x186/0x18A/0x18B` remain nonstrict
and the original physical cases are not one uninterrupted strict run.
[New F664 full-parent physical proof](docs/FIGHTER_SPECIAL_STAGE_F664.md).
No fake local padding or partial whole-function CODE credit.
Native complex `0xCC` in `005AEEC0`
and `00564BE0` still has **80/78 genuine wrong GPR/CFG roles**
despite matching x86 count and all 11 real PE/COFF fields; **do not
promote** it to exact just because the case body geometry matches.

Separately, **whole-function** VC7.1 C++ probes now reproduce
**66 distinct historical origin-unknown complete original functions /
1,183 original native CODE bytes**, all uncredited pending actual
source ownership. F658 adds **19 independently registered complete
5/8/11/14/16-byte leaf functions, 181 original CODE bytes and 111
native x86**, all directly whole-byte identical without relocation
masking or fake locals. Its native direct-caller graph and provisional
source grammars cannot determine actual authored-vs-vendor ownership.
[New F658 whole native leaf proof](docs/GAME_UNATTRIBUTED_SIMPLE_LEAVES_F658.md).
Earlier F655 independently proved seven additional original unknown
leaves, including one true source-backed PE-linked CALL forwarder.
[Previous F655 proof](docs/GAME_UNATTRIBUTED_LEAVES_F655.md).
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
