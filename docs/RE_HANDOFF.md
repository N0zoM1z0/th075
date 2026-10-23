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
| Source-present / exact functions / exact units | 130 / 130 / 130 |
| Exact code bytes | 278,457 |
| Reviewed authored coverage | 278,457 / 1,973,516 (14.11%) |
| Conservative coverage, including every pending byte | 278,457 / 1,977,124 (14.08%) |

Origin evidence through R268 remains unchanged. The cumulative exact-adoption
manifest preserves the F009 baseline and 70 reviewed additions /268,574 bytes,
with 58 new source/header inputs through F037. Unknown origins earn no credit.
The ledgers and status script are authoritative; historical counts are archived
in [RE_HANDOFF_HISTORY.md](RE_HANDOFF_HISTORY.md).

The only target is the supplied Japanese `th075.exe`, self-reporting version
1.11, SHA-256
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
Identity is pinned to the supplied archive, without independent official
provenance corroboration. Never substitute `th075c.exe`.

## Latest accepted cohort: F037

`CharacterAI499030::ChooseAction` at `0x00499030..0x0049B06F` cold-replays
exact from `src/CharacterAI499030.cpp` / `.hpp`: **8,256 code bytes**, 2,125
instructions, 460 internal branches and one return. There are no switches,
external branch exits or trailing alignment bytes. The next candidate begins
immediately after the complete return. R047 body hash and ownership are unchanged.

The natural body preserves common exits of the 0xF14-gated command branches,
two pairs of independent late random checks with identical conditions but
different commands 13/23, and the native current-height > opponent-height
comparison. Three assignment chains retain observed command read/store
repetitions. The receiver interface is pointer-only; do not construct or embed
it. The fully used two-float local separation record is source-defined. No
assembly, byte arrays, padding, inert locals, ABI misdeclarations or alternate
bodies are used. Original identities, declarations and complete layouts remain
unknown; the signed-short view at 0xF14 does not establish a full owner layout.

All 207 relocations are bound: 100 direct calls, 100 readonly references to 24
float constants and seven signed-dword counter references at `0x0068D624`
(four reads, three writes). Fresh COFF payloads, access widths and target section
permissions were checked. Writable storage is bound by address, not contents.
Calls comprise two float wrappers, 92 CRT rand calls, two predicates on the
opponent and four thiscall range helpers on the current receiver. Declaration-only
callees earn no additional origin or exact credit; wrapper ownership stays unknown.

```bash
scripts/repo-python scripts/replay-exact-units.py --unit character-ai-00499030
```

Canonical replay cold-builds the object with pinned VC7.1 build 3077,
`/Od /Ob0 /Gy /GR- /GX- /Zi /I src`, then compares the complete function and
every relocation. All 129 earlier units and inputs remain unchanged and were
not rebuilt. The new header includes unchanged `CharacterAIPolicy.hpp` for
callee declarations. Changing that header affects the six F033 units, F034,
F035, F036 and F037; changing only `CharacterAIPolicy.cpp` affects its six F033
units. Replay affected units only; preserve the unchanged `GameLeafHelpers.hpp` ABI.

Private receipts below `.analysis/`: `f037-native-audit.py` / `.json`,
`f037-499030.asm`, `f037-ai.c`, `f037-decompile.log`, `f037-compose.py`,
`f037-branch-review.json`, `f037-ai-diagnostic.py`, `f037-dispatch-audit.json`,
`f037-bind.py`, `f037-family-bindings-preview.json`,
`f037-family-bindings.json`, `f037-accepted-replay.json`,
`f037-cold-replay.log` and `f037-progress.json`. The first draft's 14 extra bytes
were rejected; common exits and comparison operand order were reconciled with
the complete native body. Diagnostics alone earn no exact credit.

The next R047 cohort F038 consists of two independently audited 7,780-byte AI
functions at `0x00474B40..0x004769A3` and `0x005E9620..0x005EB483`.
Each has 1,985 instructions, 391 internal branches, one return, 102 direct calls
and twelve following alignment INT3 bytes, without switches or external exits.
Complete comparison finds only seven non-call instruction differences: counter
references at `0x0068D620` versus `0x0068D670`. All direct call targets agree.
The attested two-function decompile and native/family reports are retained in
`f038-*` / `f038b-*`, with state in `f038-progress.json`. Full first-body
reading and native call-site checks are in `f038-behavior-review.json`; the
complete second-body comparison preserves that behavior. Each has sixteen
range-helper calls on the current receiver and one predicate on the opponent.
Preserve type-3/1/0 command writes that can fall through into ordinary AI, and
type-4/2 paths that bypass it. Independently confirm the source and bind and
cold-replay both complete functions separately. No F038 source or exact credit is registered. The 95%
goal remains active and incomplete; cleanup/handoff does not pause it. All 97
unknown origins remain unknown.

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

F037 final validation: all 3,603 CI tests passed in 81.970 seconds, including
complete adoption, historical-prefix, alias, origin, tracking and progress
freshness checks. Canonical cold source/object and header pins remain intact.
Four superseded previews were removed after equality and cold-hash checks
(101,013 file bytes); `f037-cleanup.json` records paths, sizes and hashes. Both
investigative drafts and receipts remain in `f037-probe-00.*` / `f037-probe-01.*`,
with profiles and diagnostic limits in `f037-control-manifest.json`. Original
evidence, canonical inputs, matching outputs and F021 remain preserved. A host
sample during CI had 8.5 GiB available memory and CPU 89% idle, with no interval
swap activity. Builds and validation remained serial and low priority.

Keep compiler builds serial and low priority, monitor CPU/memory, and preserve
`config/claims.csv` header-only. Replay only units with relevant source, ABI,
profile or relocation changes. The active 95% goal remains incomplete.
