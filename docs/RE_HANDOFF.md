# TH075 function reconstruction handoff

Updated 2026-10-24. The latest user instruction resumes continuous exploration
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
| Source-present / exact functions / exact units | 157 / 157 / 157 |
| Exact code bytes | 522,980 |
| Reviewed authored coverage | 522,980 / 1,973,516 (26.50%) |
| Conservative coverage, including every pending byte | 522,980 / 1,977,124 (26.45%) |

Origin evidence through R268 remains unchanged. The cumulative exact-adoption
manifest preserves the F009 baseline and 97 reviewed additions / 513,097 code bytes,
with 110 new source/header inputs through F065. Unknown origins earn no credit.
The ledgers and status script are authoritative; historical counts are archived
in [RE_HANDOFF_HISTORY.md](RE_HANDOFF_HISTORY.md).

The only target is the supplied Japanese `th075.exe`, self-reporting version
1.11, SHA-256
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
Identity is pinned to the supplied archive, without independent official
provenance corroboration. Never substitute `th075c.exe`.

## Latest accepted cohort: F065

`CharacterInput5E6F70::PollCommands` cold-replays exact from
`src/CharacterInput5E6F70.cpp` / `.hpp`: **all 1,021 bytes and 52 relocations
match**, with 294 instructions, 51 internal branches and one return. There are
no tables, indirect calls or external branch exits. Three following INT3 bytes
before `0x005E7370` stay outside comparison. An explicit alias preserves the
R049 historical role `CharacterAux::RunAt005E6F70`; extents, hashes and origin
evidence remain unchanged. Original names/declarations and the complete owner
layout remain unknown; never construct or embed this partial receiver.

The function first clears current+511, tests 26 original patterns in native
priority order, and writes the first successful pattern's outcome byte.
All-negative leaves zero. Every original NUL-terminated payload, length,
history window and output byte is checked; retain target strings such as
`236236D`, `NRNR`, `NLNL` and the N-prefixed three-character forms. A natural
ordered if/else body has no pasted decompile, target byte arrays, assembly,
inert locals, padding, fake returns, false ABI results or alternate bodies.

The complete 695-byte R112 matcher at `0x00455800`, including all 108 switch
bytes, and fresh attested Ghidra establish the actual caller ABI: thiscall,
pattern pointer, signed-byte length and signed-byte window, ret12. The caller
consumes the AL result with MOVSX. The callee can return 1..4 for terminal X;
do not replace its byte result with bool. All 26 receivers are current saved
at EBP-4. Every caller stack path/join is checked; wrong 8-byte cleanup fails.
Ignored policy return registers establish no original void declaration.
No matcher source or origin credit is added, and its full owner remains unknown.

The 52 physical bindings include 26 direct calls and 26 original readonly
strings. Actual COFF and PE payloads, section permissions, addends and operand
fields are checked against the entire native body; no relocation field or
branch is omitted. Preview, independent canonical compile and a separate
canonical cold replay match with VC7.1 build 3077 and
`/Od /Ob0 /Gy /GR- /GX- /Zi /I src`. The native frame is four bytes.

```bash
scripts/repo-python scripts/replay-exact-units.py --unit character-input-policy-005e6f70
```

All 156 prior units and accepted inputs remain unchanged and were not rebuilt.
The manifest retains F009 plus 97 additions / 513,097 code bytes / 110 new
source/header inputs, excluding F021/F048/F061. Every pending byte stays in the
conservative denominator. F064 is archived in
[history](RE_HANDOFF_HISTORY.md#f064-complete-stage-renderer-checkpoint-2026-10-24).

Retain `f065-session-check.log`, `f062-r049-native.py` / `.json`,
`f062-5e6f70.asm`, the attested `f062-r049-views.c` / `f062-decompile.log`,
`f065-callee-455800.asm`, `f065-matcher-view.c` / `f065-matcher-decompile.log`,
`f065-abi-review.py` / `.json`, `aux-input-5e6f70/`, `f065-bind-draft.py`,
`f065-bind.py`, both complete binding receipts, `f065-accepted-replay.json`,
`f065-cold-replay.log`, `f065-adoption-parent.json`, `f065-progress.json`
and `f065-evidence-check.json`. The 95% goal remains active; do not pause for
this bounded acceptance, cleanup or handoff. Use Ghidra/local tools without
REA, serial low-priority builds, affected cold replays and resource monitoring.

One obsolete reproducible preview object / **4,207 bytes** is removed after
complete COFF function-byte and all-relocation equality with the retained
canonical cold object, allowing only the explicit Draft-to-canonical owner
name transition. Both complete physical binding receipts agree.
`f065-obsolete-output-cleanup.json` records the proof and removed hash.
All source/control inputs, manifests, evidence, accepted objects, unaccepted
active objects and shared tools remain. Compilation uses niceness 15;
CI uses niceness 10.

Full CI passes all **3,603 tests in 145.951 seconds**. Tracking, progress-card,
all 156 prior units and inputs, raw origin hashes, historical prefixes and
whitespace checks pass. Recorded samples show about 8.5 to 8.8 GiB available
memory, mostly idle CPU and zero interval swap-in/out. F066 exploration
continues without receiving source or exact credit.

## Current reconstruction cohort: F066

Continue independently reviewed R048 `0x0055AC80..0x00561B8F`, historical role
`CharacterObject::AdvanceAt0055AC80`: **28,432 code bytes**, 7,653 instructions,
860 internal branches, one return and 394 direct calls to 14 callees. There
are no indirect calls or external branch exits. The contiguous 232-byte table
and 198-byte remap extend comparison through `0x00561D3D`: compare all
**28,862 bytes**. Two following INT3 bytes before `0x00561D40` are excluded.
Full code/table/remap hashes and native CFG are pinned in
`f066-native-audit.py` / `.json` and `f066-55ac80.asm`.

The signed-word selector at current+0x60 subtracts 800 before unsigned guard 197.
Entry guards inspect owner at +0xE4, its opponent at +0x2E8, their +0x3BA words,
current+0x8A and current+0x82 countdown. Do not infer original owner layout or
reuse F061 receivers and expressions from names alone. The native frame is
0x19C with saved ESI; current is saved at EBP-24. The complete attested Ghidra
view is `f066-action-view.c` / `f066-action-decompile.log`. All 14 complete
native callee exports are pinned in `f066-callee-export.py` / `.json` and
`f066-callee-*.asm`. Full caller stack/receiver review now checks every
instruction and all 394 calls/14 complete callees; wrong 16-byte effect cleanup
fails. There are 34 owner-at-E4 calls: 25 effects, seven sounds, one gauge
update and one shake; all other thiscall receivers are current. Twelve angle
calls use cdecl/two floats/ST0; 11 conversions use the real implicit
ST0-to-EDX:EAX compiler ABI through ordinary casts. The gauge callee consumes
a full dword parameter despite Ghidra's short spelling. Shake passes 3.0f
through the full 13-byte setter to a field independently consumed by x87.
Keep `f066-abi-review.py` / `.json`, attested callee view/log, full dependency
exports, shake consumer and attested global-xref query/log. Both angle
wrapper/worker remain unknown; ftol2 stays library. No new callee credit.

`f066-case-index.py` / `.json` pins **57 nondefault states / 57 entries** across
selector 800..997; default is 0x00561B83. `f066-state-review-index.py` materializes
all complete native regions in `object-action-55ac80/native-states/`, and
`f066-native-constants.json` retains actual payloads/widths/permissions/uses.
The sole writable absolute reference is the existing signed byte at 0x006714D0;
retain its existing narrow declaration. Physical state regions are review
coordinates, never independently callable extents or partial exact units.

States 800 and 801 have manually authored natural fragments at
`object-action-55ac80/states/800.inc` / `801.inc`; the declaration-only
`Preview.hpp` records actual ABI views. `f066-state-review-index.json` pins
source hashes and explicit native behavior notes. The fragments retain real
early exits, field widths, operation order and 16-bit increment; state 800
continues its independent frame handlers after a frame-result ClearField74.
Original field meanings/names and full owner layouts remain unknown.
Continue review/source from **state 802 and all remaining 55 states**, then
compose one complete body with guards/default. No partial-switch compile,
fake fallback state, source-presence entry, descriptor or exact credit is
added. Full physical matching of all 28,862 bytes/every relocation and a
separate canonical cold replay remain required. Keep `f066-progress.json`.


Continue the full 95% goal without pausing. Preserve all 157 exact units,
F061 active07, F048 active03/F021, R268 and all 97 unknown origins. Keep builds
serial and low priority; replay affected units only and monitor CPU/memory.

## Unaccepted work: F061

Continue independently reviewed R048 `0x005EB520..0x005F3BA1`, historical role
`CharacterObject::AdvanceAt005EB520`: 34,434 code bytes / 9,378 instructions,
902 branches, one return, ten direct callees and 492 call sites, with no
indirect calls or external branch exits. Its contiguous 244-byte table and
199-byte remap extend comparison through `0x005F3D5C`, excluding three INT3
bytes before `0x005F3D60`. Compare all **34,877 bytes**. The observed signed-word
selector subtracts 800 before its unsigned guard and remap; entry guards read
the actual +E4 owner/opponent fields and the object's +82 countdown. Do not
infer a complete owner or reuse F060 layouts/receivers from names alone.
The complete native index pins 60 nondefault states / 60 distinct entries
across selector values 800..998, plus default frame advance at `0x005F3B96`.
All states, guards, field widths, arguments, receivers and exits now have a
private natural source draft. All ten complete callees and every stack join
are checked across 9,378 instructions and **492 calls**; incorrect 20-to-16-byte
effect-call cleanup is rejected. The earlier 592-call prose was a counting
error, not an extent or origin change. SpawnEffect's 93 calls use the +E4 owner.
Current receives frame 61, secondary reset 31, polar velocity 24, transform 59,
RecordedRange 57, clear-field74 154 and shared sound 2 calls. Nine angle calls
use cdecl/two floats/ST0; two conversions use the implicit ST0-to-EDX:EAX ABI
through ordinary casts. Unknown angle origins remain unknown.

The complete draft is `.analysis/object-action-5eb520/Preview.cpp` / `.hpp`;
the pinned snapshot is `active07/`, and the active object is
`build/probes/F061Preview.obj`. With VC7.1 build 3077 and
`/Od /Ob0 /Gy /GR- /GX- /Zi /I src`, it emits 9,378 instructions and the native
0x210 frame. All 492 static calls and every branch/table destination correspond.
All **806 relocations** are physically bound: 492 calls, 251 actual readonly
references, two table/remap addresses and 61 table destinations. Actual COFF
payloads, target/COFF permissions, widths, addends and local offsets are checked;
there are no writable-global references. This correspondence is diagnostic.

**F061 remains unaccepted.** The draft compares 34,879 bytes, two too many,
and 324 instruction encodings differ. The first nonbranch difference is
`0x005F3904` in state 998: native begins with EAX, the draft with EDX. Earlier
forward-branch encodings also differ because the destination moved by two
bytes. GPR classes and compiler-temporary displacements are elided only to
locate gaps; they establish neither unrestricted equivalence nor exact bytes.
No mapping, source-presence entry, canonical descriptor or exact credit is
added. Preserve the native exits and operation order, including both rounded
angle divisions before integer conversion. Byte-copy spelling/signedness,
integer-versus-float doubling literals and the final state-997 return/break
controls emitted identical whole code and relocation records. Do not repeat
these controls without new evidence, or force registers with inert locals,
padding, assembly, false ABI results or alternate source bodies.

The subsequent genuine float-angle postfix-increment control also emits
identical whole code and bindings; retain `f061-control08-draft-relocation-bindings.json`
and `object-action-5eb520/control-08/intent.json`. Do not repeat it without new
evidence. The active07 source/object remain unchanged. Continue native/compiler
statement and temporary-lifetime investigation at 997/998. Full physical equality and a separate canonical cold replay remain
required. Retain `f061-native-audit.py` / `.json`, `f061-5eb520.asm`,
`f061-action.c`, both attested decompile logs and `f061-recheck-action.c`,
`f061-case-index.py` / `.json`, `f061-native-constants.json`,
`f061-abi-review.py` / `.json`, all ten `f061-callee-*.asm`,
`f061-native-correspondence.py` and its reports, `f061-compose.py`,
`f061-review-view.py`, `f061-whole-diagnostic.py` / `.json`,
`f061-bind-draft.py`, `f061-draft-relocation-bindings.json`,
`f061-checkpoint.py`, `f061-progress.json`, and controls 01 through 06.
The fresh Ghidra recheck has both completion and target attestation markers
and reproduces the earlier complete export hash. Two obsolete control objects
were removed only after their whole COFF function bytes and normalized
relocations matched the retained active object: **131,640 bytes** reclaimed in
`f061-obsolete-output-cleanup.json`. All source/control inputs and receipts,
active objects, accepted evidence and shared tools remain.

The previous F061 checkpoint passed all 3,603 CI tests in 144.960 seconds. Retained-unit,
manifest raw-byte pins, historical-prefix, progress-card and whitespace checks
pass; all 153 accepted units remain unchanged and were not rebuilt. Available
memory stayed about 8.7 to 9.1 GiB; interval samples had no swap activity.
Compilation remains serial at niceness 15 and CI at niceness 10.

Preserve all 155 accepted units, unaccepted F048/F021, R268 and all 97 unknown
origins. Continue the full 95% goal without pausing for bounded acceptance,
cleanup or handoff. Use existing Ghidra/local tools without REA, affected cold
replays only, serial low-priority compilation and CPU/memory monitoring.
Later project phases remain deferred. The earlier F048 exclusions and active
03 source/object remain preserved; do not repeat rejected controls without new
native/compiler evidence.

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
remain required. All 153 accepted units and inputs, R268 evidence, all 97 unknown
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
