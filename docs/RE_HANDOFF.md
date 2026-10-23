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
| Source-present / exact functions / exact units | 118 / 118 / 118 |
| Exact code bytes | 166,913 |
| Reviewed authored coverage | 166,913 / 1,973,516 (8.46%) |
| Conservative coverage, including every pending byte | 166,913 / 1,977,124 (8.44%) |

Origin evidence through R268 remains unchanged. The cumulative exact-adoption
manifest preserves the F009 baseline and 58 reviewed additions /157,030 bytes,
with 44 new source/header inputs through F030. Unknown origins earn no credit.
The ledgers and status script are authoritative; historical counts are archived
in [RE_HANDOFF_HISTORY.md](RE_HANDOFF_HISTORY.md).

The only target is the supplied Japanese `th075.exe`, self-reporting version
1.11, SHA-256
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
Identity is pinned to the supplied archive, without independent official
provenance corroboration. Never substitute `th075c.exe`.

## Latest accepted cohort: F030

`CharacterAction5C0D70::DispatchActions` at `0x005C0D70..0x005C3FA8`
cold-replays exact across all **12,857 code bytes**. Seven following INT3
bytes are alignment. R047 ownership and the complete target body hash are
unchanged. All 3,474 instructions, 680 internal branches, one return and 61
ordered candidates are reconciled, without switch tables or external exits.

Canonical source is `src/CharacterActionDispatch5C0D70.cpp` / `.hpp`. Its
separate pointer-only owner view reuses the unchanged slot-reference ABI in
`ReimuActionDispatch.hpp`. Original character identity and complete layout
remain unknown; no incomplete owner is instantiated or embedded. An explicit
alias preserves the original R047 mapped role. All 117 prior units and their
inputs remain unchanged and were not rebuilt.

Unit `character-action-dispatch-005c0d70` binds all **252 relocations**:
186 calls and 66 references to nine readonly constants. Actual fresh COFF
constant payloads were checked against target bytes. No writable global is
referenced by this unit. Six leading special policies omit cancellation;
input 210 reads height after the priority callback, while 220 omits ground.
Input 103 requires +3A0 ==0; two ordinary 102 policies retain fresh height
reads. All movement rank exceptions remain 99/49. Air A has two separate
input groups, and neutral C omits the repeated vertical-zero read. See the
knowledge base for exact ordering, distance gates and reset IDs.

```bash
scripts/repo-python scripts/replay-exact-units.py --unit character-action-dispatch-005c0d70
```

Profile: pinned VC7.1 build 3077 with `/Od /Ob0 /Gy /GR- /GX- /Zi /I src`.
Private observations and receipts remain below `.analysis/`:
`f030-5c0d70.asm`, `f030-native-audit.py` / `.json`, `f030-dispatch.c`,
`f030-decompile.log`, `f030-dispatch-diagnostic.py`, `f030-dispatch-audit.json`,
`f030-bind-relocations.py`, `f030-relocation-bindings.json`,
`f030-accepted-replay.json`, `f030-cold-replay.log` and `f030-progress.json`.
Detailed F022-F030 observations are in [KNOWLEDGE_BASE.md](KNOWLEDGE_BASE.md);
previous dispatch handoff sections are preserved in the history archive.

The next bounded R047 cohort is F031 at `0x005E2310..0x005E54F8` /12,777 bytes.
Its completed native audit checks 3,428 instructions, 686 internal branches,
one return and 173 direct calls, without switch tables or external branch exits.
Seven following INT3 bytes are alignment. Retain private `f031-native-audit.py`
/ `.json`, `f031-5e2310.asm`, `f031-dispatch.c`, `f031-decompile.log` and
`f031-progress.json` below `.analysis/`. The read-only decompile is attested
and complete. No source draft or exact credit is registered for F031. Continue
its independent C++ reconstruction; do not assume F030 conditions apply.
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

F030 final validation: all 3,603 CI tests passed in 73.158 seconds, including
historical-prefix, complete adoption, name-alias, origin, tracking and progress
freshness checks. Cold source/header and final-object hashes remain intact.
Four superseded preview files were removed after canonical-source equality
checks (107,418 bytes); `.analysis/f030-cleanup.json` records paths and hashes.
Original evidence, canonical inputs, matching outputs and F021 remain preserved.
The latest sampled available memory was 8.9 GiB, with CPU 89% idle and no
swap-in/out in that host interval. Compiler builds and validation remained
low priority, without parallel compiler jobs. The 95% goal remains active.

No prior accepted source/header, ABI, compiler flags or relocation changed in
F030; cold-replay only new or affected units. Keep compiler builds serial and
low priority, monitor CPU/memory, and preserve `config/claims.csv` header-only.
