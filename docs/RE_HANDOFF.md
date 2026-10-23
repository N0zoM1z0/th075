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
| Source-present / exact functions / exact units | 120 / 120 / 120 |
| Exact code bytes | 191,836 |
| Reviewed authored coverage | 191,836 / 1,973,516 (9.72%) |
| Conservative coverage, including every pending byte | 191,836 / 1,977,124 (9.70%) |

Origin evidence through R268 remains unchanged. The cumulative exact-adoption
manifest preserves the F009 baseline and 60 reviewed additions /181,953 bytes,
with 48 new source/header inputs through F032. Unknown origins earn no credit.
The ledgers and status script are authoritative; historical counts are archived
in [RE_HANDOFF_HISTORY.md](RE_HANDOFF_HISTORY.md).

The only target is the supplied Japanese `th075.exe`, self-reporting version
1.11, SHA-256
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
Identity is pinned to the supplied archive, without independent official
provenance corroboration. Never substitute `th075c.exe`.

## Latest accepted cohort: F032

`CharacterAction52D230::DispatchActions` at `0x0052D230..0x005301A1`
cold-replays exact across all **12,146 code bytes**. Fourteen following INT3
bytes are alignment. R047 ownership and the complete target body hash are
unchanged. All 3,267 instructions, 646 internal branches, one return and 56
ordered candidates are reconciled, without switch tables or external exits.

Canonical source is `src/CharacterActionDispatch52D230.cpp` / `.hpp`. Its
separate pointer-only owner view reuses the unchanged slot-reference ABI in
`ReimuActionDispatch.hpp` and the existing signed-byte global symbol. Original
character identity, full owner layout and original global declaration remain
unknown; no incomplete owner is instantiated or embedded. An explicit alias
preserves the R047 mapped role. All 119 prior units and their inputs remain
unchanged and were not rebuilt. No duplicate global ledger row was added.

Unit `character-action-dispatch-0052d230` binds all **237 relocations**:
171 calls, 62 references to five readonly constants and four writable-global
loads. Actual fresh COFF constant payloads match their target bytes. The four
MOVSX byte reads at 0x006714D0 compare 0/1/2/3 separately after packing and
between possible resets 746/745/744/743. They remain fresh reads bound to the
writable address, not its initial value. Advanced choice 2 in both modes uses
resource >250 with +F12/+F10 guards. Air A retains its outer flag check and
its distinct inner reads. See the knowledge base for exact policy order.

```bash
scripts/repo-python scripts/replay-exact-units.py --unit character-action-dispatch-0052d230
```

Profile: pinned VC7.1 build 3077 with `/Od /Ob0 /Gy /GR- /GX- /Zi /I src`.
Private observations and receipts remain below `.analysis/`:
`f032-52d230.asm`, `f032-native-audit.py` / `.json`, `f032-dispatch.c`,
`f032-decompile.log`, `f032-absolute-memory.json`, `f032-dispatch-diagnostic.py`,
`f032-dispatch-audit.json`, `f032-bind-relocations.py`,
`f032-relocation-bindings.json`, `f032-accepted-replay.json`,
`f032-cold-replay.log` and `f032-progress.json`. Detailed F022-F032 observations
are in [KNOWLEDGE_BASE.md](KNOWLEDGE_BASE.md); earlier handoffs are archived.

The next bounded R047 cohort is F033 at `0x00472890..0x00474B36` /8,871 bytes,
provisionally mapped as `CharacterAI::ChooseAt00472890`. Its complete native
audit checks 2,274 instructions, 496 internal branches, one return and 109
direct calls, with no switch tables or external exits. Nine following INT3
bytes are alignment. The read-only Ghidra decompile is attested and complete.
Retain private `f033-native-audit.py` / `.json`, `f033-472890.asm`, `f033-ai.c`,
`f033-decompile.log`, `f033-ai-family-survey.json`,
`f033-ai-family-differences.json` and `f033-progress.json` below `.analysis/`.
No source draft or exact credit is registered for F033. Independently inspect
callee ABI and full policy before authoring natural C++.

Five other R047 bodies of the same length at 0x004E7DE0, 0x00579650,
0x0059D240, 0x005C5D10 and 0x005E7370 have individually checked body hashes
and full CFGs. The complete instruction comparison exposes selector offsets,
mode constants and writable-counter addresses that differ. Preserve every
reported difference; do not treat equal length or normalized calls as exact
credit. A shared source body would require explicit, behavior-bearing profiles
and a complete canonical cold replay for each function.
The 95% objective remains active and incomplete; cleanup/handoff does not stop it.

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

F032 final validation: all 3,603 CI tests passed in 77.264 seconds, including
historical-prefix, complete adoption, name-alias, origin, tracking and progress
freshness checks. Cold source/header and final-object hashes remain intact.
Four superseded preview files were removed after canonical-source equality
checks (96,373 bytes); `.analysis/f032-cleanup.json` records paths and hashes.
Original evidence, canonical inputs, matching outputs and F021 remain preserved.
The final host sample had 8.7 GiB available memory and CPU 91% idle, with
4 KiB/s swap-in and no swap-out during that interval. Compiler builds and
validation remained low priority without parallel compiler jobs. The 95% goal
remains active. The reproducible private `f033-ai-family-audit.py` retains every
reported difference between the six unaccepted R047 AI bodies.

No prior accepted source/header, ABI, compiler flags or relocation changed in
F032; cold-replay only new or affected units. Keep compiler builds serial and
low priority, monitor CPU/memory, and preserve `config/claims.csv` header-only.
