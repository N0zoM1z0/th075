# TH075 function reconstruction handoff

Updated 2026-10-23. The latest user instruction resumes continuous exploration
and reconstruction toward 95% authored bytes exact. Cleanup and handoff do not
authorize pausing or stopping the goal. Subsequent project phases remain
deferred. Commit subjects must use `gpt-6.1-sol: ...`. Use the existing Ghidra
wrapper and local tools, without REA. Preserve serial low-priority builds and
CPU/memory monitoring.

## Current verified state

| Measure | Current value |
| --- | --- |
| Provisional candidates | 4,351 |
| Reviewed authored / library / compiler | 1,002 / 2,671 / 581 |
| Unknown origins | 97, totaling 3,608 bytes |
| Source-present / exact functions / exact units | 114 / 114 / 114 |
| Exact code bytes | 113,769 |
| Reviewed authored coverage | 113,769 / 1,973,516 (5.76%) |
| Conservative coverage, including every pending byte | 113,769 / 1,977,124 (5.75%) |

Origin evidence through R268 remains unchanged. The cumulative exact-adoption
manifest preserves the F009 baseline and 54 reviewed additions /103,886 bytes,
with 36 new source/header inputs through F026. Unknown origins earn no credit.
The ledgers and status script are authoritative; historical counts are archived
in [RE_HANDOFF_HISTORY.md](RE_HANDOFF_HISTORY.md).

The only target is the supplied Japanese `th075.exe`, self-reporting version
1.11, SHA-256
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
Identity is pinned to the supplied archive, without independent official
provenance corroboration. Never substitute `th075c.exe`.

## Latest accepted cohort: F026

`CharacterAction493470::DispatchActions` at `0x00493470..0x00496C57`
cold-replays exact across all **14,312 code bytes**. Eight following INT3 bytes
are alignment. R047 ownership and complete target body hash remain unchanged.
All 3,841 instructions, 764 internal branches, one return and 65 ordered
candidates are reconciled, with no switch tables or external branch exits.

Canonical source is `src/CharacterActionDispatch493470.cpp` / `.hpp`. The
separate pointer-only owner view reuses the unchanged slot-reference ABI in
`ReimuActionDispatch.hpp`. Original character identity and full layout remain
unknown; no incomplete owner is instantiated or embedded. An explicit alias
preserves the original R047 mapped role. All 113 prior units and their inputs
remain unchanged and were not rebuilt.

Unit `character-action-dispatch-00493470` binds all **269 relocations**:
198 calls, 70 references to nine readonly constants, and one writable global
byte reference. Actual fresh COFF constants were checked against target bytes.
The signed byte load at `0x00493A17` reads `0x006714D0` after reset 742 and
before the zero test controlling reset 743. Its target `.data` section is
readable/writable. The inferred name `g_StateRepeatLevelAt006714D0` and its
original declaration remain provisional; the storage earns no exact byte credit.

```bash
scripts/repo-python scripts/replay-exact-units.py --unit character-action-dispatch-00493470
```

Profile: pinned VC7.1 build 3077 with `/Od /Ob0 /Gy /GR- /GX- /Zi /I src`.
Private observations and receipts remain below `.analysis/`:
`f026-493470.asm`, `f026-native-audit.py` / `.json`, `f026-dispatch.c`,
`f026-decompile.log`, `f026-dispatch-diagnostic.py`, `f026-dispatch-audit.json`,
`f026-bind-relocations.py`, `f026-relocation-bindings.json`,
`f026-accepted-replay.json`, `f026-cold-replay.log` and `f026-progress.json`.
Detailed F022-F026 observations are in [KNOWLEDGE_BASE.md](KNOWLEDGE_BASE.md);
previous dispatch handoff sections are preserved in the history archive.

The next bounded R047 cohort is F027 at `0x00502450..0x00505A5E` /13,839 bytes.
The completed native audit checks 3,751 instructions, 734 internal branches,
one return and 200 direct calls, without switch tables or external branch exits.
One following INT3 byte is alignment. Retain private `f027-native-audit.py` /
`.json`, `f027-502450.asm`, `f027-dispatch.c`, `f027-decompile.log` and
`f027-progress.json` below `.analysis/`. The read-only decompile is attested
and complete. No source draft or exact credit is registered for F027. Continue
its full C++ reconstruction independently of F021 and F026 behavior assumptions.
The 95% objective remains active and incomplete; cleanup/handoff does not stop it.

## Unaccepted work: F021

The Reimu action handler at `0x0045DD70` has 60,999 code bytes plus 1,090
contiguous switch/remap bytes. Compare the entire **62,089 bytes**; seven
following INT3 bytes are alignment. All 143 non-default destinations across
six switches are drafted in `.analysis/reimu/Preview.cpp` and 18 case includes.
These sources are compiler-only diagnostics and earn no exact credit.

The restored draft emits 62,090 bytes /16,837 instructions, with 6,311 physical
operand differences, first at `0x0045FDA9` in state 89. Five accumulator
encodings explain the net one-byte size difference. Its unrelocated function
SHA-256 is `e2b757b2007e18c766a2978cfcab4c03a97fbb05831b04264ad50e9b360fafe6`.

Register-class normalization aligns all instructions, 1,684 direct branches
and 142 table destinations; the complete 1,824-relocation diagnostic also binds
1,020 calls, 630 readonly references, 142 switch destinations, ten table/remap
addresses and 22 global references. Byte-lane analysis checks 64,412 reads
under explicit draft ABI assumptions and rejects two negative controls. These
observations do not establish exact bytes or unrestricted semantic equivalence.

Latest reverted controls: explicit and commuted first-counter additions both
reproduce the baseline. Uniformly parenthesized float leaves worsen emission
to 62,282 bytes /16,900 instructions, with a first difference at `0x0045E293`.
The baseline source and final object/diagnostic hashes were restored. Do not
repeat negative controls without new evidence or replace genuine locals and
control flow with padding, assembly or inert declarations.

Retain `.analysis/reimu/`, all `f021-*` native evidence, scripts and receipts,
and `build/probes/F021Preview.obj` with its PDB. Start with
`f021-draft-progress.json`, `f021-register-probes.json`,
`f021-draft-call-check.json`, `f021-draft-relocation-bindings.json`,
`f021-alignment-register-classes.json`, `f021-register-dataflow.json` and
`f021-whole-diagnostic.json`. Detailed compiler controls are in the knowledge
base. Continue evidence-based investigation of state 89 or another independently
reviewed authored body; do not repeat reverted controls without new evidence.

## Local retention and cleanup

A Git clone omits the pinned game input, `.analysis/`, `build/`, `.tools/` and
`ghidra-project/`. Transfer these separately for a complete local handoff.
Preserve accepted matching objects, all canonical source/manifests, native
observations and origin evidence, the F021 draft and the private Ghidra project.
Shared Ghidra/JDK/MSVC installations are read-only symlink targets; provision
them separately if moving machines. Preserve the fixed private MCP configuration
without copying its URL or secrets into tracked files.

Retain the approximately 1.3 GiB `.analysis/vc71-wine` environment:
`.analysis/r226-tool-env.sh` explicitly selects it. Current default-prefix builds
do not prove historical replay compatibility. The historical worktrees outside
this repository were not part of cleanup.

The preceding cleanup removed obsolete compiler-generated PDB caches only from
`build/probes/` and `build/origin-probes/`, retaining the active F021 PDB, all
COFF objects and all `build/matching/` contents. Each removed paired PDB has a
retained corresponding object. The superseded F022 preview PDB and Python
bytecode caches are also removed. Rebuild a probe with its retained source and
recorded compiler profile using `scripts/compile-probe.sh`; Python recreates
bytecode caches automatically. Paths, sizes and SHA-256 hashes are recorded in
`.analysis/handoff-cleanup-20261023.json`. Analysis receipts and original/private
symbol evidence are retained.

Removed 668 files: 33,724,295 file bytes
(32.2 MiB), with 33,832,960 allocated bytes. This comprises
261 generated PDB caches and 407 Python bytecode files. All retained
paired-object hashes were checked after removal.

Earlier cleanup records remain in `.analysis/handoff-cleanup.json` and
`f023-cleanup.json`; their historical totals are separate from this cleanup.
The former includes the recoverable historical baseline worktree removal.

## Verification and recovery

Run from the repository root, serially, using the private Python wrapper:

```bash
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/validate-tracking.py --require-target
scripts/repo-python scripts/report-reconstruction-status.py --summary
nice -n 10 scripts/repo-python scripts/ghidra.py check
nice -n 10 scripts/repo-python scripts/ci.py
git diff --check
```

F026 final validation: all 3,603 CI tests passed in 68.915 seconds, including
historical-prefix, complete adoption, name-alias, origin, tracking and progress
freshness checks. Cold source/header and final-object hashes remain intact.
Four superseded preview files were removed after canonical-source equality
checks (103,520 bytes); `.analysis/f026-cleanup.json` records paths and hashes.
Original evidence, canonical inputs, matching outputs and F021 remain preserved.
The latest sampled available memory was 8.8 GiB, with CPU 84% idle and no
swap-in/out in that host interval. Compiler builds and validation remained
low priority, with no parallel compiler jobs. The 95% goal remains active.

No prior accepted source/header, ABI, compiler flags or relocation changed in
F026; cold-replay only new or affected units. Keep compiler builds serial and
low priority, monitor CPU/memory, and preserve `config/claims.csv` header-only.
Read [RE_WORKFLOW.md](RE_WORKFLOW.md) and [AGENTS.md](../AGENTS.md) when continuing
reconstruction. The goal remains active until the full 95% objective is proved.
