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
| Source-present / exact functions / exact units | 127 / 127 / 127 |
| Exact code bytes | 253,634 |
| Reviewed authored coverage | 253,634 / 1,973,516 (12.85%) |
| Conservative coverage, including every pending byte | 253,634 / 1,977,124 (12.83%) |

Origin evidence through R268 remains unchanged. The cumulative exact-adoption
manifest preserves the F009 baseline and 67 reviewed additions /243,751 bytes,
with 52 new source/header inputs through F034. Unknown origins earn no credit.
The ledgers and status script are authoritative; historical counts are archived
in [RE_HANDOFF_HISTORY.md](RE_HANDOFF_HISTORY.md).

The only target is the supplied Japanese `th075.exe`, self-reporting version
1.11, SHA-256
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
Identity is pinned to the supplied archive, without independent official
provenance corroboration. Never substitute `th075c.exe`.

## Latest accepted cohort: F034

`CharacterAI4C6B50::ChooseAction` at `0x004C6B50..0x004C8CCB` cold-replays
exact from `src/CharacterAI4C6B50.cpp` / `.hpp`: **8,572 code bytes**, 2,180
instructions, 480 internal branches and one return. There are no switch tables
or external branch exits. Four following INT3 bytes are alignment. The original
R047 body hash and ownership evidence remain unchanged.

This is a separate natural source body because its decisions differ from F033.
The receiver interface remains pointer-only; do not construct or embed it.
The two-float local separation record is source-defined, with both components
used. Three command assignment chains preserve observed read/store repetitions.
No assembly, byte arrays, inert locals, padding or alternate bodies are used.

All 218 relocations are bound: 116 direct calls, 95 readonly references to 23
float constants and seven accesses to the signed dword counter at `0x0068D62C`
(four reads, three writes). Fresh COFF payloads and target section permissions
were checked. Calls comprise two float-wrapper calls, 111 CRT rand calls, two
state-predicate calls on the opponent, and one thiscall range-helper call on
the current receiver. Callee declarations do not add origin or exact credit;
the original wrapper declaration and ownership remain unknown. The counter is
bound by address, without claiming data contents or a complete owner layout.

```bash
scripts/repo-python scripts/replay-exact-units.py --unit character-ai-004c6b50
```

The canonical replay cold-builds the object with pinned VC7.1 build 3077,
`/Od /Ob0 /Gy /GR- /GX- /Zi /I src`, then compares all bytes and relocations.
All 126 earlier units and their inputs remain unchanged and were not rebuilt.
The new header includes the unchanged `CharacterAIPolicy.hpp` for observed
callee declarations. Changing that shared header affects F034 and all six F033
units; changing only `CharacterAIPolicy.cpp` affects its six F033 units. Replay
affected units only. Preserve the unchanged `GameLeafHelpers.hpp` ABI.

Private receipts below `.analysis/`: `f034-native-audit.py` / `.json`,
`f034-4c6b50.asm`, `f034-ai.c`, `f034-decompile.log`, `f034-compose.py`,
`f034-ai-diagnostic.py`, `f034-dispatch-audit.json`, `f034-bind.py`,
`f034-family-bindings-preview.json`, `f034-family-bindings.json`,
`f034-accepted-replay.json`, `f034-cold-replay.log` and `f034-progress.json`.
The first source draft already aligned all physical operands and branches;
diagnostics alone earned no credit. Only canonical cold replay accepted it.
See [KNOWLEDGE_BASE.md](KNOWLEDGE_BASE.md) for the observed decision behavior.

The next bounded R047 AI candidate is F035 at `0x0059F4F0..0x005A1555`
/8,294 bytes. Its full native audit checks 2,118 instructions, 429 internal
branches, one return and 113 direct calls (including 14 range-helper calls).
There are no switches or external branch exits; ten following INT3 bytes are
alignment. Attested read-only Ghidra decompilation and private native evidence
are retained in `f035-*`. Independently review the full policy before drafting
source or claiming exact credit. The 95% goal remains active and incomplete;
cleanup and handoff do not pause it. All 97 unknown origins remain unknown.

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

F034 final validation: all 3,603 CI tests passed in 85.090 seconds, including
complete adoption, historical-prefix, alias, origin, tracking and progress
freshness checks. The canonical cold source/object pins and both headers remain
intact. Four superseded previews were removed after canonical equality checks
(93,645 file bytes); `f034-cleanup.json` records paths, sizes and hashes. The
first investigative source and receipt remain in `f034-probe-00.cpp` / `.json`,
with its profile and limits in `f034-control-manifest.json`. Original evidence,
canonical inputs, matching outputs and F021 remain preserved. The sampled host
had 8.6 GiB available memory and CPU 88% idle, with no swap-in or swap-out in
that interval. Builds and validation remained serial and low priority.

Keep compiler builds serial and low priority, monitor CPU/memory, and preserve
`config/claims.csv` header-only. Replay only units with relevant source, ABI,
profile or relocation changes. The active 95% goal remains incomplete.
