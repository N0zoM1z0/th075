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
| Source-present / exact functions / exact units | 141 / 141 / 141 |
| Exact code bytes | 356,945 |
| Reviewed authored coverage | 356,945 / 1,973,516 (18.09%) |
| Conservative coverage, including every pending byte | 356,945 / 1,977,124 (18.05%) |

Origin evidence through R268 remains unchanged. The cumulative exact-adoption
manifest preserves the F009 baseline and 81 reviewed additions /347,062 bytes,
with 78 new source/header inputs through F047. Unknown origins earn no credit.
The ledgers and status script are authoritative; historical counts are archived
in [RE_HANDOFF_HISTORY.md](RE_HANDOFF_HISTORY.md).

The only target is the supplied Japanese `th075.exe`, self-reporting version
1.11, SHA-256
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
Identity is pinned to the supplied archive, without independent official
provenance corroboration. Never substitute `th075c.exe`.

## Latest accepted cohort: F047

`CharacterAI49B070::ChooseAction` at `0x0049B070..0x0049C840` cold-replays
exact from `src/CharacterAI49B070.cpp` / `.hpp`: **6,097 code bytes**, 1,554
instructions, 316 internal branches and one return. There are no switches or
external exits; fifteen following INT3 bytes are alignment. R047 origin evidence
and the complete original body hash remain unchanged.

Both short timers decrement before own-state checks. Own states 50..149 take
the refresh/reset/independent-input path and return. Types 3/2/1 test a strictly
negative timer before type and stock; their successful paths bypass ordinary
AI. Type 2 can overwrite command 220 with 221 using the existing signed byte at
0x006714D0. Type 0 with stock writes 200 and bypasses without a timer test.
Preserve queued modes 1..5 and every distinct attack/state/weighted/movement/
ground/air/late decision, separate random call and genuine exit. Three command
assignment chains retain native write/read/store repetitions.

The first whole draft differs in four float-comparison bytes despite matching
length, instruction count, branch destinations and calls. Native 0x0049C56B
loads own height then compares opponent height. Expressing the meaningful
ordered relation as own > opponent reproduces that physical order, with the
same false result for unordered values. Retain the rejected and corrected
sources and `f047-height-comparison-review.json`; no diagnostic alone earns credit.

All 165 relocations are bound: 80 calls, 77 readonly references to 24 actual
float payloads, seven dword counter accesses at `0x0068D628` (four reads, three
writes) and one existing MOVSX byte read at `0x006714D0`. Actual COFF payloads,
zero addends, offsets, widths and section permissions are checked. Writable
storage is bound by address, not contents. Nine range calls use the current
receiver; one predicate uses the opponent. The byte declaration stays signed
and narrow. Declaration-only callees earn no source or exact credit; wrapper
ownership and original declarations remain unresolved.

The natural body uses a fully used local two-float record and a pointer-only
receiver view, never constructed or embedded. No assembly, target arrays,
padding, inert locals, fake returns, ABI misdeclarations or alternate bodies
are used. Original identity and complete layout remain unknown.

```bash
scripts/repo-python scripts/replay-exact-units.py --unit character-ai-0049b070
```

Canonical replay cold-builds one object with pinned VC7.1 build 3077 and
`/Od /Ob0 /Gy /GR- /GX- /Zi /I src`, then compares the whole body and all
relocations. All 140 earlier units and inputs remain unchanged and were not
rebuilt. Shared AI declarations remain unchanged; replay only affected units.
The new header repeats the existing signed-byte declaration without widening it.

Private receipts below `.analysis/`: `f047-native-audit.py` / `.json`,
`f047-49b070.asm`, `f047-ai.c`, `f047-decompile.log`, `f047-review.py`,
`f047-behavior-review.json`, `f047-compose.py`, `f047-ai-diagnostic.py`,
`f047-dispatch-audit.json`, `f047-height-comparison-review.json`, `f047-bind.py`,
`f047-family-bindings-preview.json`, `f047-family-bindings.json`,
`f047-accepted-replay.json`, `f047-cold-replay.log` and `f047-progress.json`.

All **31 R047 authored AI functions /304,135 code bytes** now have complete
exact unit descriptors and matching ledgers. `f047-cohort-completion.json`
checks the whole cohort; only F047 was rebuilt now. This milestone does not
complete or pause the broader 95% goal. All 97 pending origins remain unknown.

The next cohort is F048, the reviewed R048 state function at `0x004AC040`.
Its code is `0x004AC040..0x004C03AB` /82,796 bytes; six guarded switch/remap
regions occupy the next **1,126 bytes**, contiguously through `0x004C0811`.
Compare the entire **83,922 bytes**, excluding fourteen following INT3 bytes.
The full native audit verifies 22,721 instructions, 1,933 branches, one return,
four remapped and two direct switches, 146 nondefault table destinations,
1,355 direct calls and six indirect calls. There are no external branch exits.
Retain `f048-native-audit.py` / `.json`, `f048-4ac040.asm`, `f048-action.c` and
`f048-decompile.log`. `f048-dispatch-review.json` / `.py` verify the entry
guards, all six groups and five singleton pivots: 151 nondefault states with
151 distinct entries. `f048-callee-inventory.json` joins 1,355 direct calls to
22 distinct target entries for discovery only; caller-specific ABIs remain
unreviewed. The decompile is a hypothesis, not source or exact evidence; its
ContextBase/Concurrency labels establish no owner or origin. Review all case
behavior and actual call ABIs before
writing natural source. Do not truncate at the code end or inherit a complete
owner layout from a different character. F021 remains unaccepted and preserved.
Continue reconstruction with Ghidra/local tools, serial low-priority builds and
resource monitoring, without REA or pausing for cohort completion/handoff.

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

F047 final validation: all 3,603 CI tests passed in 97.043 seconds,
including adoption, historical-prefix, alias, origin, tracking and progress
freshness checks. Canonical cold source/object/header pins remain intact.
Four superseded previews were removed after equality and hash checks (91,980
file bytes); `f047-cleanup.json` records paths, sizes and hashes. Rejected and
corrected investigative sources/receipts remain in `f047-probe-00.*` /
`f047-probe-01.*`, with profiles and diagnostic limits in
`f047-control-manifest.json`. Original evidence, canonical inputs, matching
outputs and F021 remain preserved. A host sample had 9.1 GiB available memory
and CPU 92% idle, without interval swap activity. Builds and validation remained
serial and low priority.

Keep compiler builds serial and low priority, monitor CPU/memory, and preserve
`config/claims.csv` header-only. Replay only units with relevant source, ABI,
profile or relocation changes. The active 95% goal remains incomplete.
