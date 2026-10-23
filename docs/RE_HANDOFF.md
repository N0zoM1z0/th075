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
| Source-present / exact functions / exact units | 138 / 138 / 138 |
| Exact code bytes | 337,777 |
| Reviewed authored coverage | 337,777 / 1,973,516 (17.12%) |
| Conservative coverage, including every pending byte | 337,777 / 1,977,124 (17.08%) |

Origin evidence through R268 remains unchanged. The cumulative exact-adoption
manifest preserves the F009 baseline and 78 reviewed additions /327,894 bytes,
with 72 new source/header inputs through F044. Unknown origins earn no credit.
The ledgers and status script are authoritative; historical counts are archived
in [RE_HANDOFF_HISTORY.md](RE_HANDOFF_HISTORY.md).

The only target is the supplied Japanese `th075.exe`, self-reporting version
1.11, SHA-256
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
Identity is pinned to the supplied archive, without independent official
provenance corroboration. Never substitute `th075c.exe`.

## Latest accepted cohort: F044

`CharacterAI557380::ChooseAction` at `0x00557380..0x00558F48` cold-replays
exact from `src/CharacterAI557380.cpp` / `.hpp`: **7,113 code bytes**, 1,846
instructions, 397 internal branches and one return. There are no switches or
external branch exits; seven following INT3 bytes are alignment. The complete
R047 body hash and ownership evidence remain unchanged.

Only queued mode 1 remains. Preserve five command-103 gates, six early spell
choices, the attack/state/weighted/movement/ground/air sequence and six distinct
late spell gates. The late third gate reads +0x398 mode 0, fourth reads +0x39A
mode 1, and sixth reads +0x398 mode 1. The second and sixth command-13 writes
continue. No +0xF10/+0xF12 access or state-301 queued-mode-2 write is present.
The ground B/vertical-one gate requires distance above 240 and below 360.
Three assignment chains retain native command read/store repetitions.

The pointer-only receiver view is never constructed or embedded. Both floats
in the source-defined local separation record are used. Original identity,
declarations and complete layout remain unknown. Six inline Boolean threshold
values are meaningful compiler temporaries. No assembly, target arrays, padding,
inert locals, fake returns, ABI misdeclarations or alternate bodies are used.

All 198 relocations are bound: 90 calls, 101 readonly references to 25 actual
float payloads, and seven dword counter accesses at `0x0068D64C` (four reads,
three writes). Fresh COFF payloads, zero addends, access widths and target section
permissions were checked. Writable storage is bound by address, not contents.
Calls comprise two float wrappers, 86 CRT rand and two predicates on the
opponent. There are no range calls. Wrapper ownership stays unresolved.

```bash
scripts/repo-python scripts/replay-exact-units.py --unit character-ai-00557380
```

Canonical replay cold-builds one object with pinned VC7.1 build 3077,
`/Od /Ob0 /Gy /GR- /GX- /Zi /I src`, then compares the whole body and every
relocation. All 137 earlier units and inputs remain unchanged and were not
rebuilt. Independently reviewed portions of our authored F036 statements are
reused with the whole F044 emission separately verified. The new header includes
unchanged `CharacterAIPolicy.hpp` for observed callee declarations. Changing that
header affects all prior dependent AI units plus F044; its source affects the
six F033 units. Replay affected units only.

Private receipts below `.analysis/`: `f044-native-audit.py` / `.json`,
`f044-557380.asm`, `f044-ai.c`, `f044-decompile.log`,
`f044-behavior-review.json`, `f044-compose.py`, `f044-ai-diagnostic.py`,
`f044-dispatch-audit.json`, `f044-bind.py`, `f044-family-bindings-preview.json`,
`f044-family-bindings.json`, `f044-accepted-replay.json`, `f044-cold-replay.log`
and `f044-progress.json`. The first complete draft aligns all physical operands
and branch destinations. Diagnostic alignment alone earns no exact credit.

The next bounded R047 AI candidate is F045 at `0x005349B0..0x00536356`
/6,567 bytes. Its whole native audit checks 1,683 instructions, 340 internal
branches, one return and 92 calls: two float wrappers, 77 CRT rand, ten integer
range helpers, one call at `0x00455580` and two predicates. There are no switches
or external exits; nine following INT3 bytes are alignment. Retain `f045-*`
evidence. The full decompile, behavior and thirteen receiver contexts are
reviewed in `f045-behavior-review.json`; the complete R109 recorded-range helper
at `0x00455580` is separately audited. Its observed ABI is ECX plus two dword
endpoints, signed EAX result and RET 8, with distinct recording/replay behavior.
Do not substitute plain rand/range. Source remains undrafted; full physical
comparison and canonical cold replay are required before any exact credit. The 95% goal remains active and incomplete;
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

F044 final validation: all 3,603 CI tests passed in 108.042 seconds,
including adoption, historical-prefix, alias, origin, tracking and progress
freshness checks. Canonical cold source/object/header pins remain intact.
Four superseded previews were removed after equality and hash checks (87,594
file bytes); `f044-cleanup.json` records paths, sizes and hashes. The first
complete investigative source and receipt remain in `f044-probe-00.*`, with
profile and diagnostic limits in `f044-control-manifest.json`. Original evidence,
canonical inputs, matching outputs and F021 remain preserved. A host sample had
8.9 GiB available memory and CPU 80% idle, without interval swap activity. Builds
and validation remained serial and low priority.

Keep compiler builds serial and low priority, monitor CPU/memory, and preserve
`config/claims.csv` header-only. Replay only units with relevant source, ABI,
profile or relocation changes. The active 95% goal remains incomplete.
