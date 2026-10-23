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
| Source-present / exact functions / exact units | 150 / 150 / 150 |
| Exact code bytes | 461,087 |
| Reviewed authored coverage | 461,087 / 1,973,516 (23.36%) |
| Conservative coverage, including every pending byte | 461,087 / 1,977,124 (23.32%) |

Origin evidence through R268 remains unchanged. The cumulative exact-adoption
manifest preserves the F009 baseline and 90 reviewed additions /451,204 code bytes,
with 96 new source/header inputs through F057. Unknown origins earn no credit.
The ledgers and status script are authoritative; historical counts are archived
in [RE_HANDOFF_HISTORY.md](RE_HANDOFF_HISTORY.md).

The only target is the supplied Japanese `th075.exe`, self-reporting version
1.11, SHA-256
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
Identity is pinned to the supplied archive, without independent official
provenance corroboration. Never substitute `th075c.exe`.

## Latest accepted cohort: F057 (following F056)

`CharacterSequence5AC250::AdvanceSequence` at `0x005AC250` cold-replays exact
from `src/CharacterSequence5AC250.cpp` / `.hpp`: **10,998 code bytes**, 2,556
instructions, 299 branches and one return. Its 280-byte table and 98-byte remap
extend comparison through `0x005AEEBF`, directly adjoining the next function
at `0x005AEEC0` without alignment. Descriptor `size = 10998` and
`compare_size = 11376` compare all **11,376 bytes** and 379 relocations.
R048 evidence, complete bounds and hashes remain unchanged.

All 69 states, defaults and the common music/countdown/current+opponent level
tail are reviewed. Twelve position/alpha offsets are 28 bytes above F051,
without identifying a complete layout or original owner. Forty-five paths
correspond after explicit shifts, GPR classes and actual readonly payloads;
all 24 changed/new paths were independently reviewed. That diagnostic earns
no source compiler or exact credit. Full physical equality and independent
canonical cold replay establish acceptance.

Own phase 230 launch/reset is absent in 0/10/20/30/50; ownX correction is absent
in 0/10/20/30/40/50. Opponent speed in 3/13/33 is 7.75f. State 40 selects 41;
41 initializes notice 12/selects 42; 42 processes/selects 43 and clears only
opponent at `0x005ADA70`, without counter reset. States 46/56 omit the complete
signed continue-count gates. Current transitions in 6/16/26/36/46/56 are
(2,1)/(2,0)/(2,1)/(0,1)/(0,1)/(3,1); opponent in 16/46 uses (8,1)/(8,1).
All notice IDs, thresholds and genuine exits remain native-supported.

State 52 processes/selects 53 without clears or counter reset. State 53
starts opponent state 9 at `0x005ADFC6`, writes vx 7.75 / vy 18 / gravity 0.6, then
on departure writes opponentX 800, selects 54, resets the counter and breaks;
otherwise it increments the counter. The entire old fade/stage block is
absent. State 57 writes +6EF =1 then +713 =7 after processing, with no mode
selection call. States 60/61 retain their meaningful counter/initialization
order and promoted increment before narrowing.

All 220 calls and stack joins pin thirteen complete callees and reject an
incorrect cleanup. All 45 processing calls use current; primary resets use
opponent six times, starts split 6/6 and clears 7/8 current/opponent. There
is no stage-load call or stage-byte/continue-count access. All 379 physical
bindings include 220 calls, 26 readonly floats, 59 writable global accesses,
two distinct NULs at `0x00659E10/0x00659E11`, two switch addresses and 70
destinations. Actual COFF payloads/permissions, widths, addends and local
offsets are checked; globals bind by address. Only unused stage declarations
were omitted from this new header; all shared headers remain unchanged.
Original declarations, identity and complete layout remain unknown. Never
construct/embed the partial receiver; declaration-only callees earn no credit.
The single natural body has no target arrays, assembly, padding, inert locals,
fake returns, ABI misdeclarations or alternate bodies.

```bash
scripts/repo-python scripts/replay-exact-units.py --unit character-sequence-005ac250
```

The first preview, independent canonical compilation and separate cold replay
all match with VC7.1 build 3077 and `/Od /Ob0 /Gy /GR- /GX- /Zi /I src`.
F056 separately cold-replays 11,102 code /11,428 compared bytes and 365
relocations. Together F056/F057 add **22,100 code bytes**, comparing 22,804
bytes and 744 relocations. All 148 earlier units/inputs remain unchanged and
were not rebuilt; the saved F056 checkpoint also proves it unchanged during
F057. The manifest preserves 90 additions /451,204 code bytes and 96 new
source/header inputs above F009, excluding F021/F048. F056 is preserved in
[history](RE_HANDOFF_HISTORY.md#f056-sequence-checkpoint-2026-10-23).

Retain `f057-native-audit.py` / `.json`, `f057-5ac250.asm`, `f057-sequence.c`,
`f057-decompile.log`, `f057-case-index.py` / `.json`,
`f057-native-correspondence.py` / `.json`, `f057-abi-review.py` / `.json`, all
thirteen `f057-callee-*.asm`, `f057-behavior-review.json`, `f057-compose.py`,
`f057-sequence-diagnostic.py`, `f057-bind-draft.py`, `f057-family-bindings.json`,
`f057-accepted-replay.json`, `f057-cold-replay.log`, `f057-progress.json`,
`f056-checkpoint-before-f057.json` and `f056-f057-evidence-check.py` / `.json`.
Both complete first-preview source/header/object snapshots survive in
`f056-probe-00/` and `f057-probe-00/`. Only their bit-identical obsolete
preview duplicates were removed, reclaiming 67,484 bytes with hash-pinned
receipts. Canonical objects, inputs, evidence and all older controls remain.
Shared full CI passes all 3,603 tests in 169.935 seconds. Target, tracking,
progress-card and whitespace checks pass. Combined evidence checks preserve
all 148 prior units/inputs, historical ledger/function rows, R268 and all 97
unknown origins, and prove F056 unchanged during F057. The observed CI worker
used about one CPU core and 270 MiB RSS at niceness 10. Compiler builds retain
the serial lock and niceness 15.

## Current reconstruction cohort: F058

Continue independently reviewed R048 sequence `0x005D4890..0x005D7267`, with
10,712 code bytes, a 232-byte guarded table and 98-byte remap. Compare all
**11,042 bytes** through `0x005D73B1`, excluding fourteen following INT3 bytes
before `0x005D73C0`. Native audit verifies 2,478 instructions, 285 branches,
one return, thirteen direct callees and no external branch exits or indirect
calls. Fresh attested Ghidra/native evidence survives in `f058-native-audit.py`
/ `.json`, `f058-5d4890.asm`, `f058-sequence.c`, `f058-decompile.log` and
`f058-progress.json`. The native index pins 57 states /57 distinct entries
and 202 calls. Twelve observed position/alpha offsets are 20 bytes above F051;
194 word-sized phase-counter accesses use +F28, with no +EFC access in this
body. This is a separate narrow observation, not a complete layout. Thirty-one
native paths correspond after those explicit offsets, GPR classes and readonly
payloads; all 26 changed paths and the complete ABI need independent review.
Retain `f058-case-index.py` / `.json` and `f058-native-correspondence.py` /
`.json`; these diagnostics earn no source or exact credit. Review every actual
state, field, argument, receiver and exit before source reuse; original identity
and complete layouts remain unknown.

Preserve all 150 accepted units, unaccepted F048/F021, R268 and all 97 unknown
origins. Continue toward 95% without pausing for bounded acceptance, cleanup
or handoff. Keep builds serial and low priority, monitor CPU/memory, and use
existing Ghidra/local tools without REA. Subsequent project phases remain deferred.

## Unaccepted work: F048

Continue the reviewed R048 state function at `0x004AC040`.
Its code is `0x004AC040..0x004C03AB` /82,796 bytes; six guarded switch/remap
regions occupy the next **1,126 bytes**, contiguously through `0x004C0811`.
Compare the entire **83,922 bytes**, excluding fourteen following INT3 bytes.
The full native audit verifies 22,721 instructions, 1,933 branches, one return,
four remapped and two direct switches, 146 nondefault table destinations,
1,355 direct calls and six indirect calls. There are no external branch exits.
Retain `f048-native-audit.py` / `.json`, `f048-4ac040.asm`, `f048-action.c` and
`f048-decompile.log`. `f048-dispatch-review.json` / `.py` verify the entry
guards, all six groups and five singleton pivots: 151 nondefault states with
151 distinct entries.

The subsequent ABI audit pins all 22 complete direct callee extents and their
actual RET cleanup, and checks every native instruction across all stack joins
and 1,361 calls. An incorrect 20-to-16-byte effect cleanup is rejected as a
negative control. All thiscall receivers are current except the transform call
at `0x004BF0A0`, which uses the opponent. The six virtual slot-zero calls use
current. The angle wrapper at `0x00483300` is cdecl with two float arguments and
an ST0 result; its worker at `0x00483320` remains unknown-origin, as does the
wrapper. The implicit-ST0 compiler conversion helper is expressed through
ordinary casts. Caller views establish neither original declarations nor
ownership; ignored results do not prove original void returns. Stack/receiver
checking does not complete the remaining cases' argument/behavior review.
Retain `f048-abi-export.py` / `.json`, `f048-abi-review.py` / `.json`, all
`f048-abi-*.asm` and `f048-contexts-*.json`.

Private natural source now covers **151/151 states**, representing 82,372
bytes of native physical case regions. The final 42 cases add 43,047 native
bytes. These partitions are diagnostic regions, never independent acceptance
extents or partial credit. The composer now materializes one complete natural
`Preview.cpp` below `.analysis/character-action-4ac040/`; it still rejects
incomplete inputs. No F048 mapping, source-presence or exact entry is accepted.

The first full compile emitted 83,751 bytes /22,704 instructions with a 0x6DC
frame. Native-supported expression and branch refinements now reproduce the
entire **83,922-byte size, 22,721 instructions and 0x720 frame** with pinned
VC7.1 build 3077 and `/Od /Ob0 /Gy /GR- /GX- /Zi /I src`. All 1,361 static calls,
1,933 branch destinations and 151 relocated table destinations correspond.
Every one of 2,352 relocations is reviewed: 1,355 calls, 811 readonly references,
25 signed-byte global reads, ten table/remap references and 151 destinations.
Actual COFF constant payloads, target widths/permissions, addends and local
symbol offsets are checked. The only new private header declaration repeats
the existing signed byte at `0x006714D0`; accepted headers remain unchanged.

**Physical bytes are still different.** The current 03 draft has 7,209 differing
instruction encodings despite equal total size, first at `0x004ADEFA` in
state 89: native loads this into EAX, the draft into EDX. Twelve accumulator
encoding size differences cancel. Instruction correspondence elides GPR
classes and temporary displacements; it proves neither unrestricted semantic
equivalence nor exact bytes. No canonical unit or acceptance is created.
Continue evidence-based source investigation at the state 88/89 boundary,
including the conversion/counter lifetime and the preserved F021 analogue.
A bounded prefix-versus-postfix increment control for the first ten-effect
loop emits identical whole code and relocations; it is rejected in
`f048-postfix88-control.json`. The fresh attested Ghidra query resolves the
containing function and emits its first 100 instructions, rather than the
requested interior window; it is
identity evidence only (`f048-state88-89-ghidra.*`). Use the complete frozen
native export for the 88/89 boundary. Do not repeat these controls without new
evidence, or add inert locals, padding, assembly, ABI result changes or
alternate bodies to force registers.

The subsequent register-byte diagnostic checks 88,970 reads across all
22,721 reachable instructions and all argument-stack joins, including nested
calls. Every EBP displacement agrees without elision. Both a corrupted state 89
receiver and an undefined high byte of an AL return are rejected. This remains
conditional on the explicit caller ABI and paired-instruction semantics;
memory contents, x87 and flags are not independently symbolically executed.
It grants no byte exactness or unrestricted equivalence. Retain
`f048-register-profile.py` / `.json` and `f048-register-dataflow.py` / `.json`.
The new `/Op` control emits 87,934 bytes /23,366 instructions and is rejected;
its first shape change is at `0x004AE014`, after the initial GPR mismatch.
Keep `f048-consistency-control.json`; do not repeat this control without new
evidence. The active 03 source, object and profile remain unchanged.

The whole compile corrects an earlier syntax-only claim about random operand
order: `(height + constant + index * spacing) + RecordedRange(0, 20)` preserves
the float store before the range call in all eight loops 416/417/419/420. The
previous random-first spelling did not. Nine ambient 830 expressions similarly
compute `(height - 15.0f)` before y-random. These seventeen meaningful compiler
temporaries account for the 0x44-byte frame difference; no frame padding is
introduced. The native call boundary and resulting float rounding matter.

States 731/742/763 use ordered ownX > opponentX for facing-1, otherwise+1,
including unordered values. The earlier <=-first draft had the wrong unordered
outcome. The float-only opponent accessor retains native load order. State 99
places the ordinary mode/flag path first. State 200 has separate genuine returns;
416..420 retain native if/else joins and duplicate 418 fans. Keep all native
integer threshold forms, independent calls, and the phase6/phase4 tests in 392.

The final cases preserve unsigned fade thresholds and real returns in 504..509,
all independent 36-shot 807 and nine-shot 834 calls, functional ten-shot 838/839
loops, distinct spend/call order, and every level-specific card path. Preserve
731's single reused functional angle counter, 741's separate F06<=0/F06<-30
tests, all four independent level branches in 742/770, the opponent transform
in 761, and 771's actual float divisor bits `33fa8e3c`. Both angle helpers remain
unknown-origin. Never infer the complete owner layout or construct this view.

Retain `f048-case-index.json`, `f048-case-review.json`, `f048-progress.json`,
`f048-complete-review.py`, `f048-refresh-draft.py`, `f048-compose.py`,
`f048-whole-diagnostic.py`, `f048-bind-draft.py` and
`f048-draft-relocation-bindings.json`. `f048-probe-00/` through `f048-probe-03/`
preserve complete source/header/object controls and receipts; restore them into
the original private source location to reproduce their compiler paths. The
current object is `build/probes/F048Preview.obj`. The initial-case generators
predate the documented whole-emission refinements; compose the pinned current
fragments instead of blindly regenerating them. Keep prior 85/109 receipts and
syntax snapshots, including the successful 131-case syntax checkpoint.

Complete physical comparison across all 83,922 bytes, then canonical cold replay,
remain required. All 150 accepted units and inputs, R268 evidence, all 97 unknown
origins and F021 remain unchanged. Continue the active 95% goal using Ghidra and
local tools, serial low-priority builds and CPU/memory monitoring, without REA
or pausing for draft completion, cleanup or handoff.

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

Latest F048 109-case validation: all 3,603 CI tests passed in 115.546 seconds
(`.analysis/f048-state400-ci.log`). `f048-private-draft-check-109.json` checks
all twenty native/decompile/draft input hashes; the incomplete-source control
rejects a 109/151-case whole comparison input. No accepted source, header,
descriptor, relocation, compiler profile or origin ledger changed, so no
unchanged accepted unit was rebuilt. The earlier knowledge-base bytes remain
verbatim. The host had about 9 GiB available memory; interval CPU was 85% idle
with no swap activity. `f048-next-state504-checkpoints.json` retains the next
native case's unsigned alpha gates, random order, six independent effect calls
and genuine early exits for source work. State 504 is not yet drafted or
accepted. Continue exploration; whole source/comparison/replay are outstanding.

Keep compiler builds serial and low priority, monitor CPU/memory, and preserve
`config/claims.csv` header-only. Replay only units with relevant source, ABI,
profile or relocation changes. The active 95% goal remains incomplete.
