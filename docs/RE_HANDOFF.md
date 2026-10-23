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
| Source-present / exact functions / exact units | 139 / 139 / 139 |
| Exact code bytes | 344,344 |
| Reviewed authored coverage | 344,344 / 1,973,516 (17.45%) |
| Conservative coverage, including every pending byte | 344,344 / 1,977,124 (17.42%) |

Origin evidence through R268 remains unchanged. The cumulative exact-adoption
manifest preserves the F009 baseline and 79 reviewed additions /334,461 bytes,
with 74 new source/header inputs through F045. Unknown origins earn no credit.
The ledgers and status script are authoritative; historical counts are archived
in [RE_HANDOFF_HISTORY.md](RE_HANDOFF_HISTORY.md).

The only target is the supplied Japanese `th075.exe`, self-reporting version
1.11, SHA-256
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
Identity is pinned to the supplied archive, without independent official
provenance corroboration. Never substitute `th075c.exe`.

## Latest accepted cohort: F045

`CharacterAI5349B0::ChooseAction` at `0x005349B0..0x00536356` cold-replays
exact from `src/CharacterAI5349B0.cpp` / `.hpp`: **6,567 code bytes**, 1,683
instructions, 340 internal branches and one return. There are no switches or
external branch exits; nine following INT3 bytes are alignment. The whole R047
body hash and ownership evidence remain unchanged.

Preserve type-3 bypass, type-2 range-before-timer<=-180 ordering, type-1 command
210 fallthrough, and every type-0 separate range call, overwrite and real exit.
The type-1 call at `0x00455580` is a distinct recording/replay policy. Its whole
139-byte R109 body saves ECX, consumes two signed dword endpoints, returns EAX
and RET 8. Mode 2 consumes a queued short or retains zero when empty; other modes
use CRT rand and mode 1 appends the short value. Preserve that separate call on
the current receiver. Its declaration is local to the new pointer-only class;
no accepted shared ABI is changed and the helper earns no source or exact credit.

Queued modes 1..5 and ordinary decisions reuse independently reviewed portions
of our authored F036 statements. Preserve both +0xF12 checks, state-301 queued
mode 2, the two inline Boolean threshold values and three command assignment
chains. Five command-103 gates and all twelve command-13 spell gates are absent.
The receiver is never constructed or embedded; both local separation floats are
used. Original identity, declarations and complete layout remain unknown.
No assembly, target arrays, padding, inert locals, fake returns, ABI
misdeclarations or alternate bodies are used.

All 189 relocations are bound: 92 calls, 90 readonly references to 22 actual
float payloads, and seven dword counter accesses at `0x0068D648` (four reads,
three writes). Actual COFF payloads, zero addends, widths and target section
permissions are checked. Writable storage is bound by address, not contents.
Calls comprise two float wrappers, 77 CRT rand, ten range helpers, one distinct
recorded-range helper and two opponent predicates. Eleven range calls use the
current receiver. Wrapper ownership remains unresolved.

```bash
scripts/repo-python scripts/replay-exact-units.py --unit character-ai-005349b0
```

Canonical replay cold-builds one object with pinned VC7.1 build 3077,
`/Od /Ob0 /Gy /GR- /GX- /Zi /I src`, then compares the whole body and every
relocation. All 138 earlier units and inputs remain unchanged and were not
rebuilt. The new header includes unchanged `CharacterAIPolicy.hpp`; changing
that header affects all prior dependent AI units plus F045, while its source
affects the six F033 units. Replay affected units only.

Private evidence below `.analysis/`: `f045-native-audit.py` / `.json`,
`f045-5349b0.asm`, `f045-ai.c`, `f045-decompile.log`, `f045-review.py`,
`f045-behavior-review.json`, `f045-recorded-range-455580.asm` / `.json`,
`f045-compose.py`, `f045-ai-diagnostic.py`, `f045-dispatch-audit.json`,
`f045-bind.py`, `f045-family-bindings-preview.json`, `f045-family-bindings.json`,
`f045-accepted-replay.json`, `f045-cold-replay.log` and `f045-progress.json`.
The first complete draft aligns all physical operands and branch destinations;
diagnostic alignment alone earns no exact credit.

The next bounded R047 AI candidate is F046 at `0x004C8CD0..0x004CA637`
/6,504 bytes. Its full native audit checks 1,639 instructions, 343 internal
branches, one return and 99 calls: two wrappers, 92 CRT rand, four range helpers
and one predicate. There are no switches or external exits; eight following
INT3 bytes are alignment. Retain `f046-*` native evidence and the attested
read-only decompile. Full behavior and five receiver contexts are reviewed in
`f046-behavior-review.json`; a private natural draft and composer are retained.
Preserve type-2/0 distinct command exits, state-specific successive command
overwrites and the absent command-103/13 gates. Full comparison and cold replay
remain required. No source or exact credit is registered. The 95%
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

F045 final validation: all 3,603 CI tests passed in 93.719 seconds,
including adoption, historical-prefix, alias, origin, tracking and progress
freshness checks. Canonical cold source/object/header pins remain intact.
Four superseded previews were removed after equality and hash checks (86,197
file bytes); `f045-cleanup.json` records paths, sizes and hashes. The first
complete investigative source and receipt remain in `f045-probe-00.*`, with
profile and diagnostic limits in `f045-control-manifest.json`. Original evidence,
canonical inputs, matching outputs and F021 remain preserved. A host sample had
8.9 GiB available memory and CPU 90% idle, without interval swap activity. Builds
and validation remained serial and low priority.

Keep compiler builds serial and low priority, monitor CPU/memory, and preserve
`config/claims.csv` header-only. Replay only units with relevant source, ABI,
profile or relocation changes. The active 95% goal remains incomplete.
