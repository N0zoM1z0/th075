# TH075 function reconstruction handoff

Updated 2026-10-03. Work is stopped after origin-review batch R069. No
origin or exact reconstruction work is in progress. The public repository is
[N0zoM1z0/th075](https://github.com/N0zoM1z0/th075); the current checkpoint
is commit `1180754` on `main`. Its [GitHub CI run](https://github.com/N0zoM1z0/th075/actions/runs/37031358595)
passed. Commit subjects use `gpt-6.1-sol: ...`. Keep documentation in English.

## Verified checkpoint

The pinned target is the supplied Japanese `th075.exe` (reported `ver1.11`),
SHA-256 `bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
The initial Ghidra inventory has 4,351 provisional candidates. Origin review
has resolved 2,164: 798 authored, 792 library and 574 compiler generated.
There are 2,187 pending. Candidate count is not authored function count.

The unchanged exact baseline is 42 source-present and exact functions,
covering 8,916 bytes across 42 match units. Exact coverage of the currently
reviewed authored bytes is 8,916 / 1,948,083 (0.46%). This denominator is
provisional because origin review is incomplete. The origin-review batches
added no exact credit; F001–F007 established the existing exact baseline.
The requested order was to finish origin review, then rank core authored
functions by value and dependencies before resuming exact reconstruction.
Both the complete-origin and 50%-exact milestones remain unfinished; this
handoff records the stopped state, not a completed goal.

The canonical state lives in `config/functions.csv`,
`config/function-origins.csv`, the origin evidence CSVs and the exact
match-unit manifests. The progress SVG is generated from those ledgers.
[Origin review](ORIGIN_REVIEW.md) records the evidence and boundaries for
R001–R069; the [knowledge base](KNOWLEDGE_BASE.md) records accepted facts.
The former chronological handoff is preserved in
[handoff history](RE_HANDOFF_HISTORY.md); its earlier counts and next-step
notes are historical snapshots.

## Tooling and verification

Run repository Python through `scripts/repo-python`. TH075 has its own
Ghidra project and Bash + Ghidra MCP bridge, with pinned VC7.1/D3D8 tools
reused privately from TH095. The user-requested Tailscale Funnel endpoint
has no bearer authentication. Its random path is private in the ignored
`.tools/mcp_for_gptweb-ghidra/.env`; do not print or commit it. The latest
public HTTPS smoke test passed 15 checks, including Ghidra attestation and a
cold exact-unit replay. See [MCP operations](GHIDRA_MCP.md).

```bash
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/validate-tracking.py --require-target
scripts/repo-python scripts/report-reconstruction-status.py --summary
scripts/repo-python scripts/verify-authored-origins.py
scripts/repo-python scripts/verify-effect-fighter-origins.py
scripts/repo-python scripts/verify-fighter-final-virtual-origins.py
scripts/repo-python scripts/verify-combat-reaction-origins.py
scripts/repo-python scripts/update-progress.py --check
scripts/repo-python scripts/ci.py
git diff --check
```

The final local run passed 98 public tests, target-required tracking,
complete checks of 751 explicitly recorded authored bodies, and progress
freshness. The public GitHub CI for R067–R069 passed. No tool service or
public route was changed in the final batches.

## Deferred investigations

The repeated 520/511-byte container-growth bodies near `0x00414B40` and
related addresses remain pending. Their shape resembles a VC7 container,
but the cold `std::vector::_Insert_n` probes did not match complete bodies;
do not exclude them by resemblance. Private diagnostic probes are under
`.analysis/r067-vector-*` and `build/r067-vector-*`.

The CRT survey at `.analysis/crt-origin-survey.json` still contains 353
pending, relocation-bearing observations. A source fingerprint alone does
not establish each relocated callee or data binding. The metadata-vector
and stream-deque probes likewise remain diagnostic. The 2,301-byte
`0x00420880` candidate has a bounded remap dispatch, but Ghidra did not
recover its semantics; it was left pending. Private reads are under
`.analysis/r067-*`. Preserve unknown classifications until a complete
source/target binding or game-owner witness is available.

When the project resumes, complete the 2,187 pending origin decisions
before doing further exact reconstruction. Then derive a priority list from
confirmed authored bytes, core behavior, cross-function dependencies and
likely matching cost. The user has stopped work for this handoff, so no
further analysis is queued.
