# TH075 function reconstruction handoff

Updated 2026-10-03. Work resumed with origin-review batch R070. The public
repository is [N0zoM1z0/th075](https://github.com/N0zoM1z0/th075) on
`main`. Commit subjects use `gpt-6.1-sol: ...`. Keep documentation in English.

## Verified checkpoint

The pinned target is the supplied Japanese `th075.exe` (reported `ver1.11`),
SHA-256 `bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
The initial Ghidra inventory has 4,351 provisional candidates. Origin review
has resolved 2,166: 800 authored, 792 library and 574 compiler generated.
There are 2,185 pending. Candidate count is not authored function count.

The unchanged exact baseline is 42 source-present and exact functions,
covering 8,916 bytes across 42 match units. Exact coverage of the currently
reviewed authored bytes is 8,916 / 1,950,601 (0.46%). This denominator is
provisional because origin review is incomplete. The origin-review batches
added no exact credit; F001–F007 established the existing exact baseline.
The requested order was to finish origin review, then rank core authored
functions by value and dependencies before resuming exact reconstruction.
Both the complete-origin and 50%-exact milestones remain unfinished.

The canonical state lives in `config/functions.csv`,
`config/function-origins.csv`, the origin evidence CSVs and the exact
match-unit manifests. The progress SVG is generated from those ledgers.
[Origin review](ORIGIN_REVIEW.md) records the evidence and boundaries for
R001–R070; the [knowledge base](KNOWLEDGE_BASE.md) records accepted facts.
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
scripts/repo-python scripts/verify-fighter-script-origins.py
scripts/repo-python scripts/update-progress.py --check
scripts/repo-python scripts/ci.py
git diff --check
```

The R069 local run passed 98 public tests, target-required tracking,
complete checks of 751 explicitly recorded authored bodies, and progress
freshness. The public GitHub CI for R067–R069 passed.

## Deferred investigations

The repeated 520/511-byte bodies near `0x00414B40` and related addresses
match a newly compiled VC7 `std::deque::_Growmap` probe outside all 13
relocation fields. A complete cold verifier and typed bindings are being
prepared before any library-origin promotion. The earlier vector probes
were a wrong family. Private diagnostics are under `.analysis/r071-*`.

The CRT survey at `.analysis/crt-origin-survey.json` still contains 353
pending, relocation-bearing observations. A source fingerprint alone does
not establish each relocated callee or data binding. The metadata-vector
and stream-deque probes likewise remain diagnostic. The 2,301-byte
`0x00420880` candidate has a bounded remap dispatch, but Ghidra did not
recover its semantics; it was left pending. Private reads are under
`.analysis/r067-*`. Preserve unknown classifications until a complete
source/target binding or game-owner witness is available.

Complete the 2,185 pending origin decisions before doing further exact
reconstruction. Then derive a priority list from
confirmed authored bytes, core behavior, cross-function dependencies and
likely matching cost. R070's script loader/parser is verified; the adjacent
deque methods still need independent vendor review.
