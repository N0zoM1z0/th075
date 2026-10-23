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
| Source-present / exact functions / exact units | 133 / 133 / 133 |
| Exact code bytes | 301,693 |
| Reviewed authored coverage | 301,693 / 1,973,516 (15.29%) |
| Conservative coverage, including every pending byte | 301,693 / 1,977,124 (15.26%) |

Origin evidence through R268 remains unchanged. The cumulative exact-adoption
manifest preserves the F009 baseline and 73 reviewed additions /291,810 bytes,
with 62 new source/header inputs through F039. Unknown origins earn no credit.
The ledgers and status script are authoritative; historical counts are archived
in [RE_HANDOFF_HISTORY.md](RE_HANDOFF_HISTORY.md).

The only target is the supplied Japanese `th075.exe`, self-reporting version
1.11, SHA-256
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
Identity is pinned to the supplied archive, without independent official
provenance corroboration. Never substitute `th075c.exe`.

## Latest accepted cohort: F039

`CharacterAI5086E0::ChooseAction` at `0x005086E0..0x0050A4DB` cold-replays
exact from `src/CharacterAI5086E0.cpp` / `.hpp`: **7,676 code bytes**, 1,957
instructions, 405 internal branches and one return. There are no switches or
external branch exits; four following INT3 bytes are alignment. The complete
R047 body hash and ownership evidence remain unchanged.

The separate natural body preserves signed-byte indexed type-2/1/0 decisions,
short-timer decrements, own-x/facing early exits and a type-0 random command
choice that continues into queued/ordinary behavior. Position gates use 240/1040
and signed facing 1/-1. Three assignment chains retain observed command
read/store repetitions. The receiver interface stays pointer-only; never
construct or embed it. The fully used two-float local separation record is
source-defined. No assembly, target arrays, padding, inert locals, fake returns,
ABI misdeclarations or alternate bodies are used. Original names, declarations
and complete owner layouts remain unknown.

All 206 relocations are bound: 102 calls, 97 readonly references to 24 actual
float payloads and seven dword counter accesses at `0x0068D640` (four reads,
three writes). Fresh COFF payloads, zero addends, access widths and target
section permissions were checked. Writable storage is bound by address, not
contents. Calls comprise two float wrappers, 83 CRT rand, sixteen range helpers
on the current receiver and one predicate on the opponent. Declaration-only
callees earn no additional origin or exact credit; wrapper ownership is unknown.

```bash
scripts/repo-python scripts/replay-exact-units.py --unit character-ai-005086e0
```

Canonical replay cold-builds one object with pinned VC7.1 build 3077,
`/Od /Ob0 /Gy /GR- /GX- /Zi /I src`, then compares the complete body and every
relocation. All 132 earlier units and inputs remain unchanged and were not
rebuilt, including both F038 card policies. Our authored ordinary F035 statements
are reused, with the entire emitted F039 body independently verified. The new
header includes unchanged `CharacterAIPolicy.hpp` for callee declarations; a
change to that header affects the six F033 units, F034..F037, both F038 units
and F039. Its source affects its six F033 units. Replay affected units only.

Private receipts below `.analysis/`: `f039-native-audit.py` / `.json`,
`f039-5086e0.asm`, `f039-ai.c`, `f039-decompile.log`,
`f039-behavior-review.json`, `f039-compose.py`, `f039-ai-diagnostic.py`,
`f039-dispatch-audit.json`, `f039-bind.py`, `f039-family-bindings-preview.json`,
`f039-family-bindings.json`, `f039-accepted-replay.json`,
`f039-cold-replay.log` and `f039-progress.json`. The first full draft aligns
all physical operands and branch destinations; only canonical cold replay
earns credit, not diagnostic alignment.

The next bounded R047 AI candidate is F040 at `0x00558F50..0x0055ABD6`
/7,303 bytes. Its complete native audit checks 1,903 instructions, 351 internal
branches, one return and 106 calls: two float wrappers, 83 CRT rand, twenty range
helpers and one predicate. There are no switches or external exits; nine
following INT3 bytes are alignment. Retain `f040-*` native evidence and the
attested read-only decompile. Full behavior reading and call-site checks are
recorded in `f040-behavior-review.json` / `f040-call-contexts.json`. Twenty range
calls use the current receiver and the predicate uses the opponent. Preserve
the separate type-4 movement/counter path and type-3/2 command fallthroughs;
only queued mode 1 appears in the ordinary path. No source or exact credit is
registered; independently reconstruct the complete body before acceptance. The 95% goal remains active and incomplete;
cleanup/handoff does not pause it. All 97 unknown origins remain unknown.

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

F039 final validation: all 3,603 CI tests passed in 90.471 seconds, including
complete adoption, historical-prefix, alias, origin, tracking and progress
freshness checks. Canonical cold source/object/header pins remain intact.
Four superseded previews were removed after equality and hash checks (91,455
file bytes); `f039-cleanup.json` records paths, sizes and hashes. The first
complete investigative source and receipt remain in `f039-probe-00.*`, with
profile and diagnostic limits in `f039-control-manifest.json`. Original evidence,
canonical inputs, matching outputs and F021 remain preserved. A host sample had
8.5 GiB available memory and CPU 89% idle, without interval swap activity.
Builds and validation remained serial and low priority.

Keep compiler builds serial and low priority, monitor CPU/memory, and preserve
`config/claims.csv` header-only. Replay only units with relevant source, ABI,
profile or relocation changes. The active 95% goal remains incomplete.
