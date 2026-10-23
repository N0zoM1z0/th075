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
| Source-present / exact functions / exact units | 112 / 112 / 112 |
| Exact code bytes | 84,826 |
| Reviewed authored coverage | 84,826 / 1,973,516 (4.30%) |
| Conservative coverage, including every pending byte | 84,826 / 1,977,124 (4.29%) |

Origin evidence through R268 remains unchanged. The cumulative exact-adoption
manifest preserves the F009 baseline and 52 reviewed additions /74,943 bytes,
with 32 new source/header inputs through F024. Unknown origins earn no credit.
The ledgers and status script are authoritative; historical counts are archived
in [RE_HANDOFF_HISTORY.md](RE_HANDOFF_HISTORY.md).

The only target is the supplied Japanese `th075.exe`, self-reporting version
1.11, SHA-256
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
Identity is pinned to the supplied archive, without independent official
provenance corroboration. Never substitute `th075c.exe`.

## Latest accepted cohort: F024

`CharacterAction597660::DispatchActions` at `0x00597660..0x0059B48D`
cold-replays exact across all **15,918 code bytes**. Two following INT3 bytes
are alignment. The R047 origin and complete target hash remain unchanged.
All 4,294 instructions, 840 internal branches, one return and 74 ordered
candidates were reconciled; there are no switch tables or external branch exits.

Canonical source is `src/CharacterActionDispatch597660.cpp` / `.hpp`, with a
separate pointer-only owner view. Original character identity and full layout
remain unknown. The unchanged `ReimuActionDispatch.hpp` supplies the existing
slot-reference ABI view. No incomplete owner is instantiated or embedded.

Unit `character-action-dispatch-00597660` binds all **315 relocations**:
234 direct calls and 81 references to nine readonly constants. Actual fresh
COFF payloads and original target constants were checked. Calls comprise
70 vector accesses, 48 input packs, 81 primary resets, nine three-argument
transform calls, and 26 auxiliary-input clears. The original transform callee
at `0x0040FBB0` retains its R036 origin and earns no new exact credit here.

```bash
scripts/repo-python scripts/replay-exact-units.py --unit character-action-dispatch-00597660
```

Profile: pinned VC7.1 build 3077 with `/Od /Ob0 /Gy /GR- /GX- /Zi /I src`.
The 111 prior units and their inputs remain unchanged and were not rebuilt.
The renamed mapped role preserves the original R047 role through
`config/authored-origin-name-aliases.csv`.

Private evidence remains below `.analysis/`: `f024-597660.asm`,
`f024-native-audit.json`, `f024-dispatch.c`, `f024-decompile.log`,
`f024-dispatch-audit.json`, `f024-relocation-bindings.json`,
`f024-accepted-replay.json`, `f024-cold-replay.log` and `f024-progress.json`.
The native audit, complete diagnostic and binding scripts retain reproducible
checks. See the F024 knowledge-base entry for dispatch differences and limits.

Current next cohort: continue reconstructing the complete R047 dispatcher at
`0x00551C00` /14,631 bytes, independently of the unresolved full F021 draft.
Its attested read-only decompile and full native audit are retained below
`.analysis/` as `f025-dispatch.c`, `f025-decompile.log`, `f025-551c00.asm`,
`f025-native-audit.py` / `.json` and `f025-progress.json`. The native extent has
3,944 instructions, 772 internal branches, one return and 208 direct calls,
with no switch tables or external branch exits. Nine trailing INT3 bytes are
alignment. No source draft or exact credit has been registered for F025.
Do not award credit to a partial comparison or normalized register diagnostic.
The 95% objective remains active and incomplete; cleanup/handoff does not stop it.

## Previous accepted cohort: F023

`CharacterAction::DispatchAt004C0AD0` compares exact across the complete
16,098-byte function at `0x004C0AD0..0x004C49B1`. Fourteen following INT3 bytes
are alignment. R047 ownership and full target body hash are preserved. The
extent contains 4,256 instructions, 830 internal branches, one return and no
switch tables or external branch exits. All 67 dispatch candidates are present.

Canonical source is `src/CharacterActionDispatch.cpp` / `.hpp`. Its pointer-only
interfaces reuse the unchanged slot-reference ABI view in
`src/ReimuActionDispatch.hpp`. Neither the original character identity nor a
complete owner layout is established; do not instantiate or embed these owners.
Names and field roles remain inferred.

Unit `character-action-dispatch-004c0ad0` cold-replays all 16,098 bytes with zero
differences, including all 322 relocations: 240 calls and 82 readonly-constant
references to nine constants. Fresh COFF payloads and original target constants
were checked. Compiler profile is pinned VC7.1 build 3077 with
`/Od /Ob0 /Gy /GR- /GX- /Zi /I src`; this does not establish an executable-wide
original profile. The 110 prior units and their inputs are unchanged and were
not rebuilt.

The already successful acceptance command is:

```bash
scripts/repo-python scripts/replay-exact-units.py --unit character-action-dispatch-004c0ad0
```

The previous F022 unit `reimu-fighter-dispatch-actions` remains accepted over
14,141 bytes /278 relocations. Its full evidence and observations are preserved
in [KNOWLEDGE_BASE.md](KNOWLEDGE_BASE.md).

Private F023 receipts, all below `.analysis/`:

| Artifact | Purpose |
| --- | --- |
| `f023-4c0ad0.asm`, `f023-dispatch.c`, `f023-decompile.log` | Native extent and attested read-only decompile |
| `f023-dispatch-audit.json`, `f023-complete-diagnostic.log` | Full instruction, branch and dispatch observations |
| `f023-relocation-bindings.json`, `f023-bind-relocations.py` | Every relocation and actual constant payload |
| `f023-accepted-replay.json`, `f023-cold-replay.log` | Successful canonical cold acceptance |
| `f023-progress.json` | Accepted source/header and object hashes |
| `f023-cleanup.json` | Earlier superseded preview cleanup: 82,944 file bytes |

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

At the preceding cleanup checkpoint, all 3,603 CI tests passed in 76.899 seconds. Target-required tracking, pinned
target identity, read-only Ghidra attestation and whitespace checks passed.
F023 source/header and final-object hashes still agree with its cold receipt;
all removed paired PDBs retain their unchanged COFF objects. The final sampled
available memory was 8.4 GiB and CPU was 76% idle, with 4 KiB/s swap-in and
no swap-out in that interval. CI and Ghidra checks ran at low priority; cleanup
started no compiler builds.

No accepted source/header, ABI, compiler flags or relocation was changed during
cleanup. Existing F023 cold evidence remains valid; no mass replay is needed.
Compiler jobs must remain serial and low priority, with CPU/memory monitoring.
`config/claims.csv` stays header-only. Read [RE_WORKFLOW.md](RE_WORKFLOW.md) and
[AGENTS.md](../AGENTS.md) when continuing reconstruction.

F024 final validation: all 3,603 CI tests passed in 98.647 seconds, including
historical-prefix, complete adoption, name-alias, origin, tracking and progress
freshness checks. The canonical source/header and final-object hashes still
match the successful cold receipt. No prior accepted unit required replay.
Four superseded preview files were removed after canonical-source equality
checks (116,911 bytes); `.analysis/f024-cleanup.json` records paths and hashes.
Original evidence, canonical inputs, final matching output and F021 remain.

Sampled available memory during this work was 6.6–8.8 GiB; the final sample was
6.9 GiB. The latest host CPU interval was 54% idle, with 8 KiB/s swap-in and
548 KiB/s swap-out. Compiler builds and validation ran at low priority, with no
parallel compiler jobs. The 95% goal remains active and incomplete.
