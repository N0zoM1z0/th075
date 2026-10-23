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
| Source-present / exact functions / exact units | 128 / 128 / 128 |
| Exact code bytes | 261,928 |
| Reviewed authored coverage | 261,928 / 1,973,516 (13.27%) |
| Conservative coverage, including every pending byte | 261,928 / 1,977,124 (13.25%) |

Origin evidence through R268 remains unchanged. The cumulative exact-adoption
manifest preserves the F009 baseline and 68 reviewed additions /252,045 bytes,
with 54 new source/header inputs through F035. Unknown origins earn no credit.
The ledgers and status script are authoritative; historical counts are archived
in [RE_HANDOFF_HISTORY.md](RE_HANDOFF_HISTORY.md).

The only target is the supplied Japanese `th075.exe`, self-reporting version
1.11, SHA-256
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
Identity is pinned to the supplied archive, without independent official
provenance corroboration. Never substitute `th075c.exe`.

## Latest accepted cohort: F035

`CharacterAI59F4F0::ChooseAction` at `0x0059F4F0..0x005A1555` cold-replays
exact from `src/CharacterAI59F4F0.cpp` / `.hpp`: **8,294 code bytes**, 2,118
instructions, 429 internal branches and one return. There are no switch tables
or external branch exits. Ten following INT3 bytes are alignment. The original
R047 body hash and ownership evidence remain unchanged.

The separate natural body preserves signed-byte indexed reads at offset 0x370,
conditional short-timer decrements, command overwrites and two native copies of
the movement/counter policy. The receiver interface remains pointer-only; do
not construct or embed it. The local two-float separation record is source-defined
and fully used. Six command assignment chains preserve observed read/store
repetitions. No assembly, byte arrays, inert locals, padding or alternate bodies
are used. Original identities, declarations and full owner layouts stay unknown.

All 229 relocations are bound: 113 direct calls, 101 readonly references to 22
float constants and 15 writable-global references. The counter at `0x0068D660`
has eight dword reads and six writes across the two paths. The existing global
at `0x006714D0` has one MOVSX byte read, preserving its previously accepted
signed-byte declaration. Fresh COFF payloads, access widths and target section
permissions were checked; writable storage is bound by address, not contents.
Calls comprise two float wrappers, 96 CRT rand calls, one predicate on the
opponent and 14 thiscall range-helper calls on the current receiver. These
declaration-only callees earn no new origin or exact credit.

```bash
scripts/repo-python scripts/replay-exact-units.py --unit character-ai-0059f4f0
```

Canonical replay cold-builds the object with pinned VC7.1 build 3077,
`/Od /Ob0 /Gy /GR- /GX- /Zi /I src`, then compares all bytes and relocations.
All 127 earlier units and inputs remain unchanged and were not rebuilt. The
new header includes unchanged `CharacterAIPolicy.hpp` for observed callee
declarations. Changing that header affects the six F033 units, F034 and F035;
changing only `CharacterAIPolicy.cpp` affects its six F033 units. Replay affected
units only, preserving the unchanged `GameLeafHelpers.hpp` ABI.

Private receipts below `.analysis/`: `f035-native-audit.py` / `.json`,
`f035-59f4f0.asm`, `f035-ai.c`, `f035-decompile.log`, `f035-compose.py`,
`f035-ai-diagnostic.py`, `f035-dispatch-audit.json`, `f035-bind.py`,
`f035-family-bindings-preview.json`, `f035-family-bindings.json`,
`f035-accepted-replay.json`, `f035-cold-replay.log` and `f035-progress.json`.
The rejected first draft omitted the reviewed attack-state group; its source
and diagnostic remain in `f035-probe-00.*`. The corrected full draft aligns all
physical operands and branches, but only canonical cold replay earns credit.
See [KNOWLEDGE_BASE.md](KNOWLEDGE_BASE.md) for the observed behavior.

The next bounded R047 AI candidate is F036 at `0x00532950..0x005349A0`
/8,273 bytes. Its full native audit checks 2,137 instructions, 457 internal
branches, one return and 98 direct calls, with no range-helper calls. There are
no switches or external exits; fifteen following INT3 bytes are alignment.
Attested read-only Ghidra decompilation and private native evidence are retained
in `f036-*`. Full behavior reading and native receiver checks are recorded in
`f036-behavior-review.json`: all three predicate calls use the opponent, and
two late weighted spell writes continue into later decisions. Preserve those
fallthroughs, signed-short checks at 0xF10/0xF12 and random-call ordering when
drafting. No source or exact credit is registered. The 95% goal remains active and incomplete; cleanup and handoff
do not pause it. All 97 unknown origins remain unknown.

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

F035 final validation: all 3,603 CI tests passed in 88.236 seconds, including
complete adoption, historical-prefix, alias, origin, tracking and progress
freshness checks. Canonical cold source/object and header pins remain intact.
Four superseded previews were removed after equality and cold-hash checks
(101,634 file bytes); `f035-cleanup.json` records paths, sizes and hashes.
Both investigative source drafts and receipts remain in `f035-probe-00.*` and
`f035-probe-01.*`; `f035-control-manifest.json` records profiles and diagnostic
limits. All original evidence, canonical inputs, matching outputs and F021 are
preserved. A host sample during CI had 8.6 GiB available memory and CPU 72% idle,
with 8 KiB/s swap-in and no swap-out in that interval. Builds and validation
remained serial and low priority.

Keep compiler builds serial and low priority, monitor CPU/memory, and preserve
`config/claims.csv` header-only. Replay only units with relevant source, ABI,
profile or relocation changes. The active 95% goal remains incomplete.
