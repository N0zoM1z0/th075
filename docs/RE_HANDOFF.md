# TH075 function reconstruction handoff

Updated 2026-10-25 for resumed reconstruction, F156.
**The 98% authored-byte objective is active and incomplete.**
The user resumed after the cleanup and handoff checkpoint. Subsequent project
phases remain deferred. Continue the complete function cohort below.

## Verified reconstruction state

| Measure | Value |
| --- | --- |
| Provisional candidates | 4,351 |
| Reviewed authored / library / compiler | 1,002 / 2,671 / 581 |
| Unknown origins | 97 / 3,608 code bytes |
| Source-present / exact functions / exact units | 338 / 338 / 338 |
| Exact code bytes | 717,509 |
| Reviewed authored coverage | 717,509 / 1,973,516 (36.36%) |
| Conservative coverage, including pending bytes | 717,509 / 1,977,124 (36.29%) |
| Canonical objects / accepted source-header inputs | 139 / 217 |

The ledgers and status script are authoritative. The adoption manifest retains
F009 plus 278 additions / 707,626 code bytes / 217 inputs. Origin evidence through
R268 is intact. Every pending code byte remains in the conservative denominator.
CODE `size` determines credit; full `compare_size` also includes owned tables.

Only use the supplied Japanese th075.exe 1.11, SHA-256
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
Identity is pinned to the user's archive, without independent official
provenance corroboration. Never substitute th075c.exe or patch target bytes.

The preceding pushed reconstruction checkpoint is **d197080 (F155)**.
F156 accepts the complete 149-byte R068 callback
`fighter-bind-animation-00453d80` in `src/FighterAnimationReset453D80.cpp`.
One canonical cold build passed 149/149 bytes with all five actual REL32 fields.
The six real slot-0 calls in the large draft now have an independently cold-exact
target body. No private class/vtable name or complete owner layout is inferred.

F155 accepts the complete215-byte R109 policy
`fighter-resource-parameters-00452b30` in
`src/FighterResourceParameters452B30.cpp`. One canonical cold build passed
215/215 bytes, all seven actual relocation fields included. Its R182 counter
callee remains unaccepted: two complete79-byte controls each have23 differences.
Only the resource policy gains credit. The large caller uses its canonical header.

F154 accepts three whole R213/R239 policies in
`src/FighterCommandSelection454BC0.cpp`: `fighter-command-selection-00454bc0`
(61 bytes), `sprite-sampling-mode-00410fa0` (22 bytes) and
`sprite-color-mask-00410fe0` (22 bytes). All passed one canonical cold build,
105/105 complete bytes with both real REL32 fields replayed. The current large
caller uses their canonical header; its whole comparison still fails.

F152 accepts two new whole R103 policies in `src/FighterMoveScalarHelpers.cpp`:
`fighter-set-nonnegative-word-00453e80` (37 bytes) and
`fighter-begin-fade-parameters-00454a70` (35 bytes). Both passed canonical cold
replay, 72/72 bytes with zero differences, across one new object. Both have no
actual relocations. Names and complete owner layout remain provisional.
F146's 51-byte motion helper remains accepted. The large drafts earn no credit.

## Continue after F156: match complete 004AC040

The authoritative private source is **`.analysis/character-move-4ac040/f156/`**.
All **151/151 nondefault entries** plus the real prefix/default/shared tail are
in one complete source body. Current `Preview.cpp` is byte-identical to the
compiled `snapshots/baseline-dataflow/Preview.cpp`, SHA-256:
`97e045e6d90a2f18d855f4541ef6b0e3cd0f18376e9a073ff6cc3d200029c5f0`.
The draft remains unaccepted, with no source-presence or exact credit.

1. Read `source-evidence-audit.json`, `baseline-dataflow-whole-diagnostic.json`,
   `baseline-dataflow-relational-dataflow.json`, `closed-controls.json` and
   `.analysis/f156-animation-reset-unit-proof.json`. Retain F153..F155 audits,
   actual source transformations and the complete/focused compiler traces.
2. Seed a fresh F157 before edits. Keep `F156BaselineDataflow.obj`, both active
   F155 and F154 objects, all three positive F153 objects, `F152Complete.obj`
   and every earlier active object. Preserve all native evidence and snapshots.
3. Continue state89 at004ADEFA..004AE05D, first actual byte difference004ADEFB:
   native receiverEAX, emittedEDX. Frozen F155 pre-resource inputs establish
   event737/virtual18681, three free/noninterfering GPRs and candidate-headEDX.
   This does not establish target original virtual state or current logical IDs.
4. The new relational diagnostic checks 22,721 actual instruction pairs and
   24,442 actual CFG edges, including register bytes, memory base/index reads,
   call clobbers and used stack argument widths. Its 24,492 read constraints have
   no unresolved relationships under the recorded ABI/memory/x87 assumptions.
   Two wrong in-memory emitted instruction copies are caught. This is conditional
   diagnostic evidence, not formal equivalence, original type recovery or exactness.
   Investigate supported source/compiler IR and allocation evidence; do not add
   inert work, alter queues or invent ABI/layout to obtain native register names.
5. Keep the complete body, actual extents and all fields. Only the new149-byte
   callback was cold-replayed. Neither large draft nor the79-byte counter gains
   credit. No old accepted dependency changed or needed replay.

Current whole diagnostic: **83,922 emitted bytes** = **82,796 code + 1,126
owned data**, **18,539 position differences**, all **2,352 actual relocation
fields** resolved. Native and emitted code both have **22,721 instructions**.
The 0x720 frame, saved ESI, EBP-0x64 receiver, six pointer-table widths and four
byte remaps agree. Seventy nondefault entries have physical differences; eight
individual entry extents differ by one byte and cancel in the whole extent.
All other bytes still require exact unmasked comparison.

The optional `resolved-shapes-colorless-diagnostic.json` discards eax/ecx/edx
identity only to locate instruction-shape differences. It finds none, but does
not prove register data flow or exactness and earns no credit. The separate full
unmasked comparison is authoritative. Every actual local COFF offset stays
actual; no native-label rebasing, aliases, masks or crops are used there.

F152's first whole diagnostic remains preserved: 84,234 emitted bytes / 74,320
position differences, code +312 bytes. F153 introduced bounded observed field
views, 96 native-width counter operations and two natural expression corrections.
See the knowledge index and source-transformation audit. All 151 current entries
project byte-for-byte to F152 source through only those recorded transformations;
the earlier native call-order/exit/literal contracts remain retained.

F153's four no-change controls remain closed. F154 additionally closed five
whole-source controls with identical raw function bytes and relocation targets:
545 observed word-field views, nested final guard in88, implicit snapshot
conversions in88, /G6 tuning and /GX exception handling. None were adopted to claim progress in bytes.
Two double-zero comparisons in88 instead emit8-byte constant loads versus the
native4-byte loads; that candidate was rejected with both new constant fields
explicitly unresolved. Never invent a native constant destination or mask them.

F155 adds two closed whole-source controls: moving the existing genuine i88
declaration to function scope and enabling /Zc:forScope. Both retain the complete
83,922 raw bytes, all actual destinations and18,539 differences. The declaration
control renumbers29 local symbols while preserving their actual offsets/targets;
no native-label rebasing is used. Do not repeat these without new evidence.
The debugger's four hardware watchpoints observed the cursor and three busy
slots only around maps730..740; no compiler queue or tool file was changed.
Stopped PCs are after writes. F155 pre-resource logical labels are not inferred
for the current canonical-resource header bundle, even though whole code agrees.

F156 closes four further complete caller controls. Scalar30 +=40 in89 and
an extra lexical block around89 leave raw bytes/actual destinations unchanged.
A complete natural int-formal ResetSecondaryCounter body also reproduces all43
callee bytes (four-byte slot, low-word use/RET4), but the full caller remains
unchanged. The accepted short-formal header/body were never edited. Original
formal type remains unknown; neither declaration is used to force acceptance.
Naming a genuine consumed switch discriminator instead adds a real slot: frame
724, saved receiverEBP-68, two extra instructions,83,932 emitted bytes/80,231
differences. That control is rejected and the original prefix restored.

The relational diagnostic tracks partial GPR writes and intersects relationships
at CFG joins. Its609 zero-width PUSH allocations are each immediately fully
overwritten by an actual FSTP [ESP]; low-byte/word arguments are checked through
their observed callee contracts. Unspecified padding/clobbers, stable saved-this
storage and paired x87/memory state are explicit assumptions. Do not turn a zero
diagnostic count into an exact claim. The full byte failure remains18,539.

The F154 bounded headless compiler debugger completed normally:8,223 mapping events,
8,223 use events,2,639 forced bindings and13,951 emission tokens. Its whole
83,922-byte object and all2,352 actual fields equal F153. There are5,913 explicit
register-token differences from target; this is a diagnostic count, not goal
credit or a complete data-flow proof. The first difference is token1352/event737.
The compiler build remains hash-pinned3077. Raw Rich observations include
multiple historical builds and do not identify this function's original profile.

Required comparison remains **83,922 bytes**:82,796 code plus 1,126 owned
switch/remap bytes. Four remapped/two direct guards, five equality states,
ten contiguous owned data segments and 1,933 internal branches are checked.
Code ends 004C03AC; the full owned extent ends 004C0812 exclusive. Preserve
actual default 004C037D, common tail 004C039F, epilogue 004C03A7 and sole RET 004C03AB.
Frame 0x720, saved ESI and ECX at EBP-0x64 are observations: recover genuine locals
and nested packets without artificial storage.

The source audit checks all 151 entry hashes, native call evaluation order and
real exits. There are 24 genuine loop counters/25 loop statements and 41
float-to-short conversions. F152 adds 20 entries/22,380 native investigation
bytes; its scalar audit checks direct literal store widths, values and order
in those entries. It does not prove computed expressions or conditions.
The preacceptance call audit had 1,290 canonical named calls, 21 pending named
calls, 41 CRT conversions and six true slot-0 calls. Eleven pending call sites
now have independently cold-exact helper bodies (nine 453E80, two 454A70).
F154 adds canonical bodies for all seven command454BC0 sites. F155 adds the
canonical215-byte resource452B30 body at both remaining resource sites. Only
one named site lacks a canonical body: unknown483300. Resource452B30's transitive authored counter454D00 is separately reviewed
under R182 and remains unaccepted. F153 uses the new canonical scalar helper
declaration at all eleven sites;
all actual relocation targets remain independently checked.
Both483300/483320 remain unknown. Do not reclassify ownership from call ABI.
A complete F155 call recount gives1,361 calls:1,313 canonical named,41 CRT,
six virtual and one pending named. Earlier1,358/1,290 counts cover only the151
nondefault fragments; default/shared-tail calls at004C0380,004C0398 and004C03A2
add three canonical calls. This reporting correction changes no code or credit.

Current source/evidence is frozen by `.analysis/f156-source-checkpoint.json`.
Earlier checkpoints remain immutable. Preserve both explicit 36-site rings in
603/605, four real loops in607..610, repeated signed-global level reads and
all short motion snapshots/restores. Nested random arguments retain native
right-to-left evaluation order. See the knowledge index for further details.

## Native contracts and details to retain

- Constructor 004C0820 installs 006594A8 through the actual receiver at 004C0832.
  The used prefix is slot 0=00453D80,slot 1=004AC040. Whole R050/R068 bodies and
  four character slot 1 calls in already-exact 859-byte BattleFrame::UpdateFrame
  support it. The separate draw-dispatcher slot 1 call is excluded. Original
  identifiers/full layouts remain unknown; never instantiate/embed partial owners.
- State 96 uses ordered <=0 landing, state 97 ordered <0. State 89 uses 40.0f
  for field 30,0.0025f horizontal and 0.01f vertical restoration, with integer
  negation before conversion. Keep pre/post-advance reads, strict crossings,
  short-circuit branches, effect argument order and repeated phase guards.
- R213 wrapper 454BC0 is 61 bytes: DWORD selection/low-byte mode/DWORD mask,
  pointer 480 receiver and RET12. Its 22-byte setters 410FA0/410FE0 use RET4 and
  byte at +0x10 / DWORD at +0x14 stores. All three are authored (R213/R239) and now cold-exact in F154.
  Old functions.csv notes calling the setters unknown are historical. Do not
  change any current unknown origin on that basis.
- Callback453D80 is now cold-exact149 bytes. Its table at receiver468 selects
  sequence state60, then frame phase62; the actual frame address is stored74 and
  copied8. Frame word+4 goes to72, sequence count low word to70, selected sequence
  pointer to78. Five calls bind to the complete R205 at() and R032 count bodies.
  Forward-declared frame and declaration-only containers establish used contracts
  only. Never instantiate/embed them or turn generic vendor stride74 into a
  recovered original frame/owner size. Slot0 at6594A8 is453D80; slot1 is4AC040.
- Resource452B30 clears word3A2, tests signed byte2CD/global6714B4 and
  selects DWORDs from3D0/400 through signed byte39D when mode3 is active.
  Clock mode1 forwards the selected byte384 entry to the actual6718F8 receiver
  of454D00. The other path converts float36C*8800/900 to integer, adds1201,
  narrows to word3A0 and clears byte464. All215 bytes/seven fields are cold-exact.
  The counter's complete79-byte body/RET4 is R182 authored evidence, not an
  accepted implementation or a recovered bank/array extent. No fake padding or
  owner/array dimensions were introduced to fix its23-byte diagnostic failure.
- F149 only read states 390..402; no new source was written. State392's actual
  phase 6/tick 0 guard encloses a phase 4/tick 0 sound guard at004B204D..004B2069.
  Preserve those nested tests rather than removing instructions as unreachable;
  original intent is unknown. States 400..402 contain three explicit spawn
  sites and signed-short timers; do not substitute a synthesized runtime loop.

## Preserve the earlier full 0050A580 draft

All 92 entries exist, but the entire function remains unaccepted: 81,539 code
and 82,106 required comparison bytes. Current source SHA-256:
`80ca174bef3d407ec40f159f292765ecb5fd5deb85808f4d17fcf96b364215b0`.
Its whole diagnostic remains 82,109 emitted bytes / 26,719 differences, 522 GPR
differences and 1,449 actual fields. All 801 authored/helper calls use accepted
symbols; 20 CRT and 25 unknown-origin calls remain explicit.

Keep `build/probes/F145CanonicalViews.obj` and older active
`F142WordWindow.obj`, `F139VirtualMain.obj`, `F138CallViews.obj`,
`F136RecordView.obj`, `F134CompleteFinal.obj`. Preserve all 91 older drafts and
F131..F148 evidence. F146 closed width/copy/937-token, /Ob1, visible-callee
and 18-qualifier controls without a supported fix; do not repeat without new
evidence. Older F021/F048/F061/F066/F085 drafts/details remain in history.

## Tools and final checks

Read [AGENTS.md](../AGENTS.md), [workflow](RE_WORKFLOW.md) and
[knowledge index](KNOWLEDGE_BASE.md). Run the four preflight commands in
AGENTS.md. Use `scripts/repo-python` for every repository Python command.
Cold-replay only new/affected whole units with `replay-exact-units.py --unit NAME`.

Everything stays **headless**. Unset DISPLAY/WAYLAND_DISPLAY for Wine/debuggers;
disable graphical drivers per process, for example
`WINEDLLOVERRIDES='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'`.
Use native32 Wine/batch GDB and the existing attested headless Ghidra wrapper,
not REA/interactive WineDbg. Keep compilers serial, bound debugger runs, monitor
RAM/CPU and preserve shared tools/private service settings. Never print/commit
the private service URL. Commit subjects: `gpt-6.1-sol: ...`; commits/pushes
remain authorized.

No fake returns/ABI, inert locals, padding, assembly/target arrays, conditional
game bodies, masks/aliases/rebasing or cropped comparison. Never count partial
source or reclassify origins because a build/source audit succeeds.

Final handoff checks: **3,603 CI tests passed in 165.653 seconds**;
target, tracking, status and diff checks pass. No accepted dependency changed,
so no compiler build or cold replay was needed. Cleanup removed
243 duplicate working files (1,097,307 bytes),
375 reproducible bytecode files (8,285,269 bytes), and
161 empty build directories. Complete retention/cleanup receipts:
`.analysis/f149-handoff-cleanup.json`, `.analysis/f149-duplicate-cleanup.json`
and `.analysis/f149-handoff-source-checkpoint.json`. These historical checks
do not complete the resumed 98% objective.

The complete former documents remain byte-for-byte in
[handoff history](history/RE_HANDOFF_THROUGH_F148.md) and
[knowledge history](history/KNOWLEDGE_BASE_THROUGH_F148.md). Their active-goal
and next-task wording is historical; this document and AGENTS.md govern the
handoff. Historical relative links were authored from docs/: resolve them
there, or use Git at fd82165.

## F150 verification

Public CI passed **3,603 tests in 169.898 seconds**. Target,
tracking, status and diff checks pass. F148's 244 private files and all forty
previously protected groups were hash-verified unchanged, including 331 units,
135 canonical objects, 209 accepted source/header inputs and origin evidence.
No accepted dependency changed; no compiler build or cold replay was needed.
Cleanup removed 375 reproducible bytecode files (8,285,269 bytes).
Source and preservation receipts: `.analysis/f150-source-checkpoint.json`,
`.analysis/f150-preservation-before-ci.json` and `.analysis/f150-cleanup.json`.
The 24 new fragments remain private, uncompiled and unaccepted; exact code
remains 716,968 bytes and conservative coverage remains 36.26%.

## F151 verification

Public CI passed **3,603 tests in 173.573 seconds**. Target,
tracking, status and diff checks pass. F150's 268 private files and 283 checkpoint files and all forty
previously protected groups were hash-verified unchanged, including 331 units,
135 canonical objects, 209 accepted source/header inputs and origin evidence.
No accepted dependency changed; no compiler build or cold replay was needed.
Cleanup removed 375 reproducible bytecode files (8,285,269 bytes).
Source and preservation receipts: `.analysis/f151-source-checkpoint.json`,
`.analysis/f151-preservation-before-ci.json` and `.analysis/f151-cleanup.json`.
The 27 new fragments remain private, uncompiled and unaccepted; exact code
remains 716,968 bytes and conservative coverage remains 36.26%.

## F152 verification

Public CI passed **3,603 tests in 152.063 seconds**. Target,
tracking, status and diff checks pass. Both new helper units passed one canonical
cold build, 72/72 complete bytes exact. All 331 prior unit definitions, 209 prior
accepted source/header inputs, all origin evidence and forty protected groups
were checked; 134 prior objects remain byte-for-byte unchanged. An accidental
default R100 verifier invocation rebuilt the remaining graphics object; its
complete 495-byte canonical replay passed exact. The explicit R103 check passed
and performed no builds. No other accepted unit needed cold replay.

F151's 296 private files and 313 checkpoint files were hash-verified
unchanged. The complete 151-entry draft was compiled once successfully after an
include-macro error; its full 84,234-byte diagnostic remains a failure with 74,320
position differences and earns no credit. All sources, native evidence, active
objects and acceptance manifests are retained. Cleanup removed 375
reproducible bytecode files (8,285,274 bytes). Receipts:
`.analysis/f152-source-checkpoint.json`, `.analysis/f152-preservation-final.json`,
`.analysis/f152-scalar-canonical-replay.json`,
`.analysis/f152-unintended-r100-anchor-replay.json` and `.analysis/f152-cleanup.json`.
Exact code is 717,040 bytes; conservative coverage is 36.27%. The 98% goal remains
active and incomplete.

## F153 verification

Public CI passed **3,603 tests in 165.534 seconds**. Target,
tracking, status and diff checks pass. All 333 prior unit definitions, 136
canonical objects, 211 accepted source/header inputs, all origin evidence and
forty protected groups were hash-verified unchanged. F152's 328 private files
and its complete object are preserved. No accepted dependency changed and no
cold replay was needed. Seven complete private builds ran serially and headless.

The complete draft improved from 84,234 emitted bytes / 74,320 differences to
exactly 83,922 emitted bytes / 18,539 differences. Both streams have 22,721
instructions; all 2,352 actual relocation fields are replayed. This still fails
full comparison and earns no source-presence or exact credit. The first byte
difference is 004ADEFB. Exact code remains 717,040 bytes / 36.27% conservative.

Cleanup removed 4 redundant negative-control objects
(639,160 bytes) and 375 reproducible bytecode files
(8,285,274 bytes). Their full source/control inputs, compiler logs and raw
function/relocation evidence remain retained. Keep the three positive F153
objects and every earlier active object. Receipts:
`.analysis/f153-source-checkpoint.json`, `.analysis/f153-preservation-final.json`
and `.analysis/f153-cleanup.json`. The 98% goal remains active and incomplete.

## F154 verification

Public CI passed **3,603 tests in 160.234 seconds**. Target,
tracking, status and diff checks pass. Three new units passed one canonical cold
build, 105/105 complete bytes exact including both actual REL32 fields. All 333
prior unit definitions, 136 prior objects, 211 prior accepted source/header inputs,
all origin evidence and forty protected groups were hash-verified unchanged.
F153's 1491 private files and 1510 checkpoint files remain intact.
No accepted dependency changed; no old unit needed cold replay.

The complete caller now uses the canonical command header. Its 83,922 emitted
bytes, all 2,352 fields and 18,539 differences are unchanged. Eight private complete
caller builds, one helper diagnostic and one canonical group build ran serially
and headless. The bounded compiler debugger completed normally; its 13,951 explicit
register emissions agree with the whole own COFF. Descriptor labels belong only
to the frozen baseline inputs, not inferred target or post-migration identities.

Cleanup removed 6 obsolete reproducible control objects
(958,396 bytes) and 375 bytecode files (8,285,279 bytes).
Source/control snapshots, native/raw-COFF evidence, compiler logs and active
objects remain preserved. Receipts: `.analysis/f154-source-checkpoint.json`,
`.analysis/f154-preservation-final.json`, `.analysis/f154-command-canonical-replay.json`
and `.analysis/f154-cleanup.json`. Exact code is 717,145 bytes; conservative
coverage remains 36.27%. The 98% goal is active and incomplete.

## F155 verification

Public CI passed **3,603 tests in 177.937 seconds**. Target,
tracking, status, generated progress card and diff checks pass. The first CI run
found only the stale progress card; it was regenerated before the passing run.
Only the new resource policy was cold-built:215/215 complete bytes exact,
including all seven actual relocation fields. All336 prior unit definitions,
137 canonical objects,213 accepted source/header inputs, all origin evidence and
forty protected groups were hash-verified unchanged. F154's 1646 private files
and 1671 checkpoint files remain intact. No old replay was needed.

Four complete caller builds, two helper diagnostics and one canonical build ran
serially and headless. The full caller remains83,922 bytes/18,539 differences;
all2,352 fields retain their actual destinations. The bounded mapper trace now
establishes that its first different choice has three free/noninterfering GPRs
and candidate-headEDX. Only56 emission values were logged and checked in this
trace; F154's separate full trace remains preserved. Original target virtual
state and the cause of the source/compiler discrepancy remain unknown.

Cleanup removed4 obsolete control objects (325,805 bytes)
and375 bytecode files (8,285,284 bytes). All source/control
snapshots, full native/raw-function/relocation evidence, logs and active objects
are retained. Receipts: `.analysis/f155-source-checkpoint.json`,
`.analysis/f155-preservation-final.json`, `.analysis/f155-resource-canonical-replay.json`
and `.analysis/f155-cleanup.json`. Exact code is717,360 bytes; conservative
coverage is36.28%. The98% goal remains active and incomplete.

## F156 verification

Public CI passed **3,603 tests in 173.671 seconds**. Target,
tracking, status, generated progress card and diff checks pass. Only the new
callback was cold-built: 149/149 complete bytes exact, including all five actual
REL32 fields. All337 prior unit definitions,138 canonical objects,215 accepted
source/header inputs, all origin evidence and forty protected groups were
hash-verified unchanged. F155's 991 private files and 1016
checkpoint files remain intact. No old accepted unit needed replay.

Five complete caller builds, two helper diagnostics and one canonical build ran
serially and headless. The current complete caller source is unchanged from
F155 and still fails83,922 bytes/18,539 positions, all2,352 fields included.
The new normal-flow relational diagnostic checks22,721 instruction pairs,
24,442 real CFG edges and24,492 register-byte read relationships. No relationship
is unresolved under the recorded assumptions; two wrong in-memory instruction
controls are detected. This adds no formal equivalence or exact claim. Its
measured run took3.67 seconds with318,076 KiB peak RSS.

Cleanup removed6 obsolete reproducible objects (647,634 bytes)
and375 bytecode files (8,285,289 bytes). Complete source/control
snapshots, native/targeted raw-function/relocation evidence, logs and active
objects remain retained. Receipts: `.analysis/f156-source-checkpoint.json`,
`.analysis/f156-preservation-final.json`, `.analysis/f156-animation-reset-canonical-replay.json`
and `.analysis/f156-cleanup.json`. Exact code is717,509 bytes; conservative
coverage is36.29%. The98% objective remains active and incomplete.
