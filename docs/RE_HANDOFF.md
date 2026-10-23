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
| Source-present / exact functions / exact units | 140 / 140 / 140 |
| Exact code bytes | 350,848 |
| Reviewed authored coverage | 350,848 / 1,973,516 (17.78%) |
| Conservative coverage, including every pending byte | 350,848 / 1,977,124 (17.75%) |

Origin evidence through R268 remains unchanged. The cumulative exact-adoption
manifest preserves the F009 baseline and 80 reviewed additions /340,965 bytes,
with 76 new source/header inputs through F046. Unknown origins earn no credit.
The ledgers and status script are authoritative; historical counts are archived
in [RE_HANDOFF_HISTORY.md](RE_HANDOFF_HISTORY.md).

The only target is the supplied Japanese `th075.exe`, self-reporting version
1.11, SHA-256
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
Identity is pinned to the supplied archive, without independent official
provenance corroboration. Never substitute `th075c.exe`.

## Latest accepted cohort: F046

`CharacterAI4C8CD0::ChooseAction` at `0x004C8CD0..0x004CA637` cold-replays
exact from `src/CharacterAI4C8CD0.cpp` / `.hpp`: **6,504 code bytes**, 1,639
instructions, 343 internal branches and one return. There are no switches or
external exits; eight following INT3 bytes are alignment. The whole R047 body
hash and ownership evidence remain unchanged.

Own states 50..149 refresh a negative short timer with range (0,60), clear queued
mode/timer and continue. Types 2/1/0 with stock, expired decrement and ground
height bypass ordinary AI; type 2 chooses 221/220 and type 0 chooses 201/200,
with native distinct command exits. Type 1 writes 211. Nonexpired paths continue.
Queued modes 1..5 and ordinary policies reuse independently reviewed portions
of our authored F034 source. Preserve state-specific successive command
10/11/20/21 writes and C input, 0.8/1.0/0.4 weighted choices, three assignment
chains, the meaningful inline height threshold and final 40/41/42 overwrites.
Five command-103 and twelve early/late command-13 gates are absent.

The pointer-only receiver is never constructed or embedded; both local separation
floats are used. Original identity, declarations and complete layout remain
unknown. No assembly, target arrays, padding, inert locals, fake returns, ABI
misdeclarations or alternate bodies are used.

All 183 relocations are bound: 99 calls, 77 readonly references to 23 actual
float payloads, and seven dword counter accesses at `0x0068D630` (four reads,
three writes). Actual COFF payloads, zero addends, widths and target section
permissions are checked. Writable storage is bound by address, not contents.
Calls comprise two float wrappers, 92 CRT rand, four range helpers on the current
receiver and one predicate on the opponent. Declaration-only callees gain no
source or exact credit; wrapper ownership stays unresolved.

```bash
scripts/repo-python scripts/replay-exact-units.py --unit character-ai-004c8cd0
```

Canonical replay cold-builds one object with pinned VC7.1 build 3077,
`/Od /Ob0 /Gy /GR- /GX- /Zi /I src`, then compares the whole body and every
relocation. All 139 earlier units and inputs remain unchanged and were not
rebuilt. The new header includes unchanged `CharacterAIPolicy.hpp`; changing
that header affects all prior dependent AI units plus F046, while its source
affects six F033 units. Replay affected units only.

Private evidence below `.analysis/`: `f046-native-audit.py` / `.json`,
`f046-4c8cd0.asm`, `f046-ai.c`, `f046-decompile.log`,
`f046-behavior-review.json`, `f046-compose.py`, `f046-ai-diagnostic.py`,
`f046-dispatch-audit.json`, `f046-bind.py`, `f046-family-bindings-preview.json`,
`f046-family-bindings.json`, `f046-accepted-replay.json`, `f046-cold-replay.log`
and `f046-progress.json`. The first whole draft aligns all physical operands
and branch destinations; diagnostic alignment alone earns no exact credit.

The last unaccepted R047 candidate is F047 at `0x0049B070..0x0049C840`
/6,097 bytes. Its complete native audit checks 1,554 instructions, 316 internal
branches, one return and 80 calls: two wrappers, 68 CRT rand, nine range helpers
and one predicate. There are no switches or external exits; fifteen following
INT3 bytes are alignment. Retain `f047-*` native evidence and the attested
read-only decompile. The complete behavior, ten receiver contexts and existing
signed-byte global read are reviewed in `f047-behavior-review.json`; a private
natural source and composer are ready for compilation. Preserve both initial
short decrements, strictly negative timer checks and timer-free type-0 bypass.
No source or exact credit yet. The broader 95% goal remains active and incomplete; cohort
completion or cleanup/handoff does not pause it. All 97 unknown origins remain
unknown and receive no exact credit.

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

F046 final validation: all 3,603 CI tests passed in 101.781 seconds,
including adoption, historical-prefix, alias, origin, tracking and progress
freshness checks. Canonical cold source/object/header pins remain intact.
Four superseded previews were removed after equality and hash checks (85,952
file bytes); `f046-cleanup.json` records paths, sizes and hashes. The first
complete investigative source and receipt remain in `f046-probe-00.*`, with
profile and diagnostic limits in `f046-control-manifest.json`. Original evidence,
canonical inputs, matching outputs and F021 remain preserved. A host sample had
9.0 GiB available memory and CPU 86% idle, without interval swap activity. Builds
and validation remained serial and low priority.

Keep compiler builds serial and low priority, monitor CPU/memory, and preserve
`config/claims.csv` header-only. Replay only units with relevant source, ABI,
profile or relocation changes. The active 95% goal remains incomplete.
