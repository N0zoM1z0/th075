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
| Source-present / exact functions / exact units | 126 / 126 / 126 |
| Exact code bytes | 245,062 |
| Reviewed authored coverage | 245,062 / 1,973,516 (12.42%) |
| Conservative coverage, including every pending byte | 245,062 / 1,977,124 (12.39%) |

Origin evidence through R268 remains unchanged. The cumulative exact-adoption
manifest preserves the F009 baseline and 66 reviewed additions /235,179 bytes,
with 50 new source/header inputs through F033. Unknown origins earn no credit.
The ledgers and status script are authoritative; historical counts are archived
in [RE_HANDOFF_HISTORY.md](RE_HANDOFF_HISTORY.md).

The only target is the supplied Japanese `th075.exe`, self-reporting version
1.11, SHA-256
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
Identity is pinned to the supplied archive, without independent official
provenance corroboration. Never substitute `th075c.exe`.

## Latest accepted cohort: F033

Six independently reviewed R047 AI policies cold-replay exact from one natural
C++ template body in `src/CharacterAIPolicy.cpp` / `.hpp`. Each complete body
has **8,871 code bytes**, 2,274 instructions, 496 internal branches, one return
and nine following alignment INT3 bytes. There are no switch tables or external
branch exits. Original R047 body hashes and ownership evidence are unchanged.

| Receiver alias | Target address | Writable counter |
| --- | --- | --- |
| `CharacterAI472890` | `0x00472890` | `0x0068D61C` |
| `CharacterAI4E7DE0` | `0x004E7DE0` | `0x0068D634` |
| `CharacterAI579650` | `0x00579650` | `0x0068D654` |
| `CharacterAI59D240` | `0x0059D240` | `0x0068D65C` |
| `CharacterAI5C5D10` | `0x005C5D10` | `0x0068D664` |
| `CharacterAI5E7370` | `0x005E7370` | `0x0068D66C` |

All six `ChooseAction` methods use explicit profiles for the observed selector
offsets, mode value and counter symbol. This source reuse does not establish
original templates, identities, declarations or complete owner layouts. Only
methods are emitted; no incomplete owner object is constructed or embedded.
The two-component local separation value is source-defined. Three observed
command read/store repetitions remain explicit assignment chains. No assembly,
byte arrays, inert locals, padding or alternate conditional bodies are used.

Each unit binds all 225 relocations: 109 calls, 109 readonly references to 22
constants, and seven counter accesses (four reads, three writes). All fresh
COFF payloads and target section permissions were checked; full relocated code
matches every original byte. Counter storage is bound by address, not initial
contents. Calls comprise two float-wrapper calls, 99 CRT rand calls, two exact
state-predicate calls on the opponent, and six thiscall integer-range calls on
the current receiver. Wrapper ownership and original declarations remain
unknown; declaration-only callees earn no new origin or exact credit.

```bash
scripts/repo-python scripts/replay-exact-units.py --unit character-ai-00472890 --unit character-ai-004e7de0 --unit character-ai-00579650 --unit character-ai-0059d240 --unit character-ai-005c5d10 --unit character-ai-005e7370
```

The canonical replay cold-builds one object and checks all **53,226 bytes /
1,350 relocations**. Profile: pinned VC7.1 build 3077 with
`/Od /Ob0 /Gy /GR- /GX- /Zi /I src`. All 120 prior units and inputs remain
unchanged and were not rebuilt. The existing `GameLeafHelpers.hpp` ABI is reused
without modification. Changing the shared AI source/header requires replay of
all six dependent units; avoid rebuilding unrelated accepted units.

Private receipts below `.analysis/`: `f033-native-audit.py` / `.json`,
`f033-472890.asm`, `f033-ai.c`, `f033-decompile.log`,
`f033-ai-family-audit.py`, `f033-ai-family-survey.json`,
`f033-ai-family-differences.json`, `f033-bind-family.py`,
`f033-family-bindings-preview.json`, `f033-family-bindings.json`,
`f033-accepted-replay.json`, `f033-cold-replay.log`, `f033-progress.json` and
retained rejected `f033-probe-*` sources/diagnostics. The family comparison
exposed real per-profile differences; instruction/frame normalization never
earned credit. See [KNOWLEDGE_BASE.md](KNOWLEDGE_BASE.md) for behavior and profiles.

The next bounded R047 AI candidate is F034 at `0x004C6B50..0x004C8CCB`
/8,572 bytes. Its completed native audit checks 2,180 instructions, 480 internal
branches, one return and 116 direct calls, with no switch tables or external
exits. Four following INT3 bytes are alignment. The attested read-only Ghidra
decompile is complete. Retain private `f034-native-audit.py` / `.json`,
`f034-4c6b50.asm`, `f034-ai.c`, `f034-decompile.log` and `f034-progress.json`.
Its 111 CRT rand calls and one range-helper call differ from F033. No source
draft or exact credit is registered. Independently review its full behavior
before extending the shared implementation or authoring another source body. The 95% objective remains active and incomplete;
cleanup/handoff does not stop it. All 97 unknown origins remain unknown.

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

F033 final validation: all 3,603 CI tests passed in 95.813 seconds, including
historical-prefix, complete adoption, name-alias, origin, tracking and progress
freshness checks. All six canonical cold reports and source/header/object pins
remain intact. Four superseded previews were removed after canonical-source
equality checks (176,917 bytes); `.analysis/f033-cleanup.json` records paths and
hashes. Seven private control sources and diagnostics remain, with source hashes
and compiler profiles in `f033-control-manifest.json`. The private compose script
regenerates the canonical source byte-for-byte. Original evidence, canonical
inputs, matching outputs and F021 remain preserved. The final host sample had
8.9 GiB available memory and CPU 95% idle, with 4 KiB/s swap-in and no swap-out
in that interval. Builds and validation remained serial and low priority.
The 95% goal remains active.

Keep compiler builds serial and low priority, monitor CPU/memory, and preserve
`config/claims.csv` header-only. Replay the six AI units after a relevant shared
source, ABI, profile or relocation change; preserve every unrelated accepted unit.
