# TH075 function reconstruction handoff

Updated 2026-10-03. Work resumed with origin-review batches R070–R084. The public
repository is [N0zoM1z0/th075](https://github.com/N0zoM1z0/th075) on
`main`. Commit subjects use `gpt-6.1-sol: ...`. Keep documentation in English.

## Verified checkpoint

The pinned target is the supplied Japanese `th075.exe` (reported `ver1.11`),
SHA-256 `bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
The initial Ghidra inventory has 4,351 provisional candidates. Origin review
has resolved 2,600: 804 authored, 1,222 library and 574 compiler generated.
There are 1,751 pending. Candidate count is not authored function count.

The unchanged exact baseline is 42 source-present and exact functions,
covering 8,916 bytes across 42 match units. Exact coverage of the currently
reviewed authored bytes is 8,916 / 1,950,893 (0.46%). This denominator is
provisional because origin review is incomplete. The origin-review batches
added no exact credit; F001–F007 established the existing exact baseline.
The requested order was to finish origin review, then rank core authored
functions by value and dependencies before resuming exact reconstruction.
Both the complete-origin and 50%-exact milestones remain unfinished.

The canonical state lives in `config/functions.csv`,
`config/function-origins.csv`, the origin evidence CSVs and the exact
match-unit manifests. The progress SVG is generated from those ledgers.
[Origin review](ORIGIN_REVIEW.md) records the evidence and boundaries for
R001–R084; the [knowledge base](KNOWLEDGE_BASE.md) records accepted facts.
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
scripts/repo-python scripts/verify-vendor-deque-growmap-origins.py
scripts/repo-python scripts/verify-vendor-deque-operation-origins.py
scripts/repo-python scripts/verify-vendor-deque-helper-origins.py
scripts/repo-python scripts/verify-vendor-deque-callee-origins.py
scripts/repo-python scripts/verify-vendor-deque-allocation-origins.py
scripts/repo-python scripts/verify-fighter-script-accessor-origins.py
scripts/repo-python scripts/verify-vendor-deque-destructor-origins.py
scripts/repo-python scripts/verify-vendor-deque-access-origins.py
scripts/repo-python scripts/verify-vendor-deque-begin-origins.py
scripts/repo-python scripts/verify-vendor-deque-iterator-origins.py
scripts/repo-python scripts/verify-vendor-deque-const-iterator-origins.py
scripts/repo-python scripts/verify-vendor-deque-dereference-origins.py
scripts/repo-python scripts/verify-vendor-deque-iterator-advance-origins.py
scripts/repo-python scripts/verify-vendor-deque-comparison-origins.py
scripts/repo-python scripts/update-progress.py --check
scripts/repo-python scripts/ci.py
git diff --check
```

The R084 local run passed 98 public tests, target-required tracking,
complete checks of 757 explicitly recorded authored bodies, and progress
freshness. The no-auth public Funnel MCP ran all thirteen deque cold verifiers
and the fighter script accessor verifier successfully. Public GitHub CI
through R083 passed.

## Deferred investigations

Twelve repeated 520/517/511-byte bodies are now verified as complete VC7
`std::deque::_Growmap` templates, including all 13 typed relocations per
body and internal control flow. The independently compiled record widths do
not identify the game's original element types. A scan of remaining pending
candidates found no further whole-body matches to these seven probe variants.
The earlier vector hypothesis for these bodies was wrong. Reproduce with
`scripts/repo-python scripts/verify-vendor-deque-growmap-origins.py`.
Forty-six further complete deque push/pop/cleanup bodies, 8,220 bytes,
have their own cold verifier and typed target bindings. The many shorter
STL-like matches remain diagnostic until their ownership is independently
resolved; an identical tiny body alone is insufficient. Another 97 complete
49–72-byte deque constructors and helper templates have 190 typed bindings
and a cold verifier. A 44-byte no-relocation allocator match remains pending.
Another 126 short, 20–29-byte deque helpers have both a complete cold
source match and a same-family call from an independently reviewed parent
template. Their 126 typed relocations and all parent call fields replay.
Short matches without this corroborating parent remain pending.
Twenty-two `std::_Allocate` helpers now have the same complete code and
parent-call chain, including their call from the R074 allocator wrappers.
The fighter script initializer and three byte/word/dword field getters are
now reviewed as authored through their complete bodies and independently
reviewed fighter callers. Twenty-four 19-byte deque destructor templates,
including the script owner's cleanup helpers, call verified VC7 `_Tidy`
functions. The adjacent composite cleanup body remains pending.
An independent seven-width `deque::at` probe now verifies 33 more complete
bounds-checked access and iterator bodies. The two 68-byte helpers used by
the script getters are among the seven verified `deque::at` methods.
Seven 35-byte `begin` helpers are now bound to those reviewed `at` callers;
six similar helpers without that parent witness remain pending.
Those seven reviewed `begin` calls in turn bind seven 32-byte iterator
constructors, which bind seven 33-byte const-iterator constructors. Each
link is checked against its complete parent body and typed call field.
Ten 19-byte iterator dereferences now bind to separately verified
const-iterator dereference bodies; same-shape calls to other functions
remain pending.
Nine 31-byte iterator advances are now backed by the reviewed iterator
addition calls. Seven 27-byte variants do not match the current probe and
remain pending.
The independent iterator-operations probe now verifies 30 complete
comparison, subtraction and `end` bodies, 1,576 bytes. Five `end` helpers
whose typed callee is not the verified iterator constructor remain pending.

The CRT survey at `.analysis/crt-origin-survey.json` still contains 353
pending, relocation-bearing observations. A source fingerprint alone does
not establish each relocated callee or data binding. The metadata-vector
and other stream-deque probes likewise remain diagnostic. The 2,301-byte
`0x00420880` script parser was reviewed in R070 using the complete guarded
remap dispatch, even though Ghidra did not recover it. Preserve unknown
classifications until a complete
source/target binding or game-owner witness is available.

Complete the 1,751 pending origin decisions before doing further exact
reconstruction. Then derive a priority list from
confirmed authored bytes, core behavior, cross-function dependencies and
likely matching cost. R070's script loader/parser is verified; remaining
adjacent short deque-like helpers still need independent origin review.
