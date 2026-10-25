# TH075 function reconstruction handoff

Updated 2026-10-26 for continued reconstruction, F160.
**The 98% authored-byte goal is active and incomplete. Do not pause it.**
The user explicitly confirmed continuation and prohibited pausing. The earlier
pause was an agent error caused by treating stale handoff instructions as a
current stop request. Cleanup, documentation, verification and commits do not
suspend reconstruction or require another resume request. Subsequent project
phases remain deferred. F160 accepts two complete functions/963 bytes. Both
large drafts remain unaccepted. Current F160 outcomes supersede historical
pending-work instructions.

## Continuation command

Carry this instruction into every successor handoff or context continuation:

```text
Continue TH075 reconstruction toward 98% authored-byte exact. The goal is
active and incomplete. Do not pause it or wait for another resume request.
Read AGENTS.md and the current RE_HANDOFF.md, RE_WORKFLOW.md and
KNOWLEDGE_BASE.md; verify the working tree, target, tracking and Ghidra project;
then execute the current cohort below. Preserve accepted units, origin evidence,
active drafts and all pending bytes in the conservative denominator. Cold-replay
only new or affected units, keep compiler builds serial, remain headless, and
commit/push bounded progress with subjects "gpt-6.1-sol: ...". Cleanup,
documentation, verification, commits and context handoff are continuation work,
not reasons to stop or pause. Carry this command forward unchanged unless the
user changes it. Only a new explicit user request to pause authorizes pausing.
```

## Verified reconstruction state

| Measure | Value |
| --- | --- |
| Provisional candidates | 4,351 |
| Reviewed authored / library / compiler | 1,002 / 2,671 / 581 |
| Unknown origins | 97 / 3,608 code bytes |
| Source-present / exact functions / exact units | 377 / 377 / 377 |
| Exact code bytes | 720,508 |
| Reviewed authored coverage | 720,508 / 1,973,516 (36.51%) |
| Conservative coverage, including pending bytes | 720,508 / 1,977,124 (36.44%) |
| Canonical objects / accepted source-header inputs | 143 / 222 |

The ledgers and status script are authoritative. The adoption manifest retains
F009 plus 317 additions / 710,625 code bytes / 222 inputs. Origin evidence through
R268 is intact. Every pending code byte remains in the conservative denominator.
CODE `size` determines credit; full `compare_size` also includes owned tables.

Only use the supplied Japanese th075.exe 1.11, SHA-256
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
Identity is pinned to the user's archive, without independent official
provenance corroboration. Never substitute th075c.exe or patch target bytes.

The preceding reconstruction checkpoint is **6afb9bb (F159)**. Earlier checkpoints
include **cbda145 (F158)** and **f8f655c (F156)**. Policy correction **7f34a0b**
explicitly prohibits pausing.
F156 accepts the complete 149-byte R068 callback
`fighter-bind-animation-00453d80` in `src/FighterAnimationReset453D80.cpp`.
One canonical cold build passed 149/149 bytes with all five actual REL32 fields.
The six real slot-0 calls in the large draft now have an independently cold-exact
target body. No private class/vtable name or complete owner layout is inferred.

F155 accepts the complete215-byte R109 policy
`fighter-resource-parameters-00452b30` in
`src/FighterResourceParameters452B30.cpp`. One canonical cold build passed
215/215 bytes, all seven actual relocation fields included. Its R182 counter
callee was then unaccepted: two complete79-byte controls each had23 differences.
F158 subsequently accepted that complete counter, as recorded below.
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

## Current F160 outcomes and continuation

Two new objects pass canonical cold replay,963/963 complete authored bytes with
all29 actual fields (27 REL32 and two DIR32):

| Unit | Source | Code bytes |
| --- | --- | --- |
| fighter-select-movement-animation-00451eb0 | FighterMovementSelection451EB0.cpp | 742 |
| effect-delete-four-deques-0045ba30 | FighterEffectCleanup45BA30.cpp | 221 |

Both implement existing declarations from the unchanged F159 header. Native
provisional roles remain literal; explicit unit mappings identify their actual
call-only COFF symbols. R045/R109 origins, name/verifier/alias guards and all375
prior units/141 objects/220 adoption inputs are unchanged. Existing shared-header
protection also retains GameLeafHelpers.hpp; it is not in the later-adoption
source_sha256 set. Preserve both guard sets. No existing header needed replay.

Movement selection preserves two independent ordered y<=0 reads, repeated signed
state loads/exclusions6,7,8, signed facing/axis multiplication and unsigned
positive4F4 tests. All14 reset state literals and three existing canonical bool
facing calls/ignored results are retained. The crouch state2-to2 reset remains
literal. No cached fields, fake return or extra local is introduced. Both actual
float-zero fields bind to the independently observed32-bit zero at0065782C.

Cleanup uses complete vendor deque/iterator types (20/8 bytes), the observed
four-container range atreceiver+4 and actual postfix iterator result. The
pointee is a deletion-only pointer view with a private undefined constructor:
never construct/embed it or treat it as an original pointee/owner extent.
It models only the observed no-destructor-work/unsized global release contract.
Original pointee type/size and destructor spelling stay unknown. An earlier
valid raw-storage release with a named pointer local differs at five actual
stack-slot bytes; it remains a rejected private control. The selected natural
delete expression uses the genuine compiler-generated operand temporary, with
no padding or inert local. All22 complete pointer-element vendor helper bodies
and every field match the independently frozen R110 graph. They gain no new
library/source/origin credit. Vendor clear()/~deque() wrappers both call_Tidy;
the historical R077 destructor title stays unchanged and original spelling is
not recovered. Full library proof is retained in vendor-whole-callee-checks.json.

The whole move-body int-truncation88 control adds an explicit int intermediate
to two existing float-to-short conversions. It leaves all83,922 raw bytes and
all2,352 actual field destinations unchanged. Exactly132 source-local label
spellings shift, with every actual local offset/type/addend/target unchanged;
no aliasing or native-label rebasing is used. Whole comparison still fails at
18,539 positions, first004ADEFB. The control is closed and all151 F160 source
entries/prefix/default/shared tail restored to F159/F156, SHA prefix97e045e6.

Continue fresh F161 from `.analysis/character-move-4ac040/f160/`. Keep the full
004AC040 and0050A580 candidates and all pending bytes in the goal. Seek genuine
source/type/expression evidence for the first register difference; do not repeat
closed conversion or function-order cursor controls without new evidence.
The related effect-manager lifetime85/initialization131 evidence in
config/effect-manager-lifetime-origin-evidence.json is available for further
whole-function investigation. Reconcile complete storage and EH paths before
source acceptance; allocation84/stride20 alone does not recover a full owner.
Preserve all97 unknown origins and both F159 compiler trace objects, all14 F157
probes and every earlier active object. Cold replay only new/affected units.
Do not pause the active98% goal.

Receipts: `.analysis/f160-dependencies-unit-proof.json`,
`.analysis/f160-dependencies-canonical-replay.json`, F160 source-evidence-audit.json,
int-truncation88-local-symbol-observations.json and `.analysis/f160-dependencies/`.

## Retained F159 outcomes and previous work

One canonical cold build accepts36 complete authored functions /1,957 code bytes
in `src/FighterVirtualActionsF159.cpp`, with its new call-only header:

| Reviewed cohort | Functions | Code bytes |
| --- | --- | --- |
| R060 action forwards / no-op overrides | 32 | 440 |
| R050 Sakuya round reset004C09A0 | 1 | 247 |
| R045 base round reset00457010 | 1 | 1,151 |
| R103 clear-six-DWORD policy00453A10 | 1 | 89 |
| R015 held-count clear004071A0 | 1 | 30 |

All36 pass complete canonical replay, including all16 actual REL32 fields.
Each source body is a sole complete code COMDAT, every extent/soleRET0 and all
following excluded INT3 alignment were checked. Original provisional native
role names remain unchanged. Explicit unit role-to-COFF mappings use distinct
call-only receiver views, avoiding conflicts with accepted Reimu/Meiling owner
declarations. No frozen origin role/verifier or alias guard was changed. No
receiver is instantiated/embedded or treated as a complete owner/vtable layout.
The historical blank function.owner on R015 only mirrors its already-authored
origin at source adoption; origin ownership itself is unchanged.

The Sakuya slot6 policy preserves19 ordered word-zero stores, including repeated
F16, then calls the complete base reset. The base reset preserves repeated3A0
and6E6 writes, bool-derived positions/facing, true slot0 animation dispatch,
the actual28-byte input-clear range and owned-effect cleanup. Existing animation
header/source are unchanged. Only the new shared object was cold-built; all339
prior units/140 objects/218 inputs, all97 unknown origins and full pending-byte
denominator remain unchanged. Base action451EB0 and effect cleanup45BA30 remain
independently reviewed authored callees awaiting their own source/exact credit.

Two headless compiler traces use33 genuine reviewed method bodies in one TU.
Both observe33 entries and33 cursor initializations. Reordering the real247-byte
Sakuya reset first yields19 mapping events before the next entry: cursor/head2
is then reset to head1. The captured return PC10774FAC independently identifies
actual CALL10774FA7->10775782 in the pinned C2 image. All33 complete function
bodies/687 bytes and12 actual fields remain identical across the orders. This
closes carryover of this cursor phase from a preceding function on the observed
3077/profile path. Other global state, full C2 CFG and original target compiler/
virtual state remain unknown. No filler functions or queue/tool/target mutation
were used. Reports are under `.analysis/f159-action-slots/`.

Continue the full98% goal without pausing:

1. Seed fresh F160 from `.analysis/character-move-4ac040/f159/`. All151 entries,
   prefix/default/shared tail and headers remain byte-identical to F158/F156;
   source SHA prefix97e045e6. The full failure is still83,922 bytes/18,539
   positions/all2,352 fields, first difference004ADEFB (state89 receiverEAX
   native versusEDX emitted). Seek genuine source/type/expression evidence.
   The observed cursor phase is reset across function boundaries; do not add
   unrelated function bodies or inert work to try to force it.
2. The directly related R045 base movement policy00451EB0 is742 bytes and already
   declared as `FighterBaseActionsF159::SelectMovementAnimation()`. Review its
   complete control flow/owned data before reconstruction. Its body can go in a
   new source including the unchanged F159 header, without changing the36 newly
   accepted bodies or replaying them unnecessarily. The R109 effect cleanup
   0045BA30/221 bytes is another independently reviewed direct dependency.
3. Preserve375 exact units,141 canonical objects,220 inputs, both F159 trace
   objects, all14 F157 probes and every prior active object/checkpoint. Both
   large functions and all pending code stay in the full conservative denominator.
   No fake ABI/layout/padding, aliases/masks/crops/rebasing or compiler queue edits.

Receipts: `.analysis/f159-actions-unit-proof.json`,
`.analysis/f159-actions-canonical-replay.json`, F159 `source-evidence-audit.json`,
`allocator-init-correlation.json` and `allocator-reordered-correlation.json`.

## Retained F158 outcomes

The complete R182 counter `profile-increment-counter-00454d00` is accepted from
`src/ProfileSelection454D00.cpp`: canonical cold replay79/79 bytes, all20
instructions and soleRET4, zero actual relocations. Its natural discarded
postfix word increment retains the native repeated-address order. Signed byte
argument and bank16AC4 form address bank*17F0+394+index*2. One following INT3
is excluded and the next function starts454D50. Existing pointer-only header
and accepted resource caller are unchanged; no owner is instantiated/embedded.
Original names, nominal word type, array bounds and complete owner stay unknown.
Proof and replay: `.analysis/f158-counter-unit-proof.json` and
`.analysis/f158-counter-canonical-replay.json`. Only this new unit was cold-built;
all338 prior definitions,139 objects,217 inputs and all97 unknown origins remain
unchanged. The resource policy's authored counter dependency is now closed.

Current complete caller source is `.analysis/character-move-4ac040/f158/`, restored
byte-for-byte to the F156 baseline after the controls below. Read its
`source-evidence-audit.json` before seeding fresh F159 work. Preserve every prior
active object, all14 F157 probes and all source/evidence/checkpoints.

Two whole source controls are closed with identical raw code and all actual
relocation records: inherited F157 `field-prefix` changes20 existing postfix
increments to prefix; F158 `all-postfix` changes96 existing prefix operations to
postfix, leaving the20 old postfix sites. The baseline has116 discarded field
operations: the96 F153 corrections plus20 older postfix operations. Genuine int
loops, field widths, values, exits, ABI and storage are unchanged. Both full
comparisons remain83,922 bytes/18,539 differences/all2,352 fields. Neither is
adopted as a fix. The inherited prefix control is now fully compared; its old
pending note below is historical. Retain snapshots and complete raw reports.

F158 `c2-known-cursor-references.json` freezes four actual .text literal cursor
references and individually decodes the known read/init/advance/reset MOVs in
the hash-pinned C2 image. It supersedes the incomplete empty F157 shortlist.
Indirect writes and complete compiler CFG remain outside that evidence; tool
files, compiler queues and target bytes were not changed.

## Retained F156 complete004AC040 baseline evidence

Current continuation instructions are in the F159 section above. The retained
F156 source/body/whole-failure measurements remain unchanged. The loose F157
Preview is the closed all-prefix control. The retained baseline source is
**`.analysis/character-move-4ac040/f156/`**.
All **151/151 nondefault entries** plus the real prefix/default/shared tail are
in one complete source body. Current `Preview.cpp` is byte-identical to the
compiled `snapshots/baseline-dataflow/Preview.cpp`, SHA-256:
`97e045e6d90a2f18d855f4541ef6b0e3cd0f18376e9a073ff6cc3d200029c5f0`.
The draft remains unaccepted, with no source-presence or exact credit.

1. Read `source-evidence-audit.json`, `baseline-dataflow-whole-diagnostic.json`,
   `baseline-dataflow-relational-dataflow.json`, `closed-controls.json` and
   `.analysis/f156-animation-reset-unit-proof.json`. Retain F153..F155 audits,
   actual source transformations and the complete/focused compiler traces.
2. F157..F159 already exist; preserve them and seed fresh F160 before edits. Keep
   `F156BaselineDataflow.obj`, both active F155 and F154 objects, all three
   positive F153 objects, `F152Complete.obj`
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
5. Keep the complete body, actual extents and all fields. F156 cold-replayed the
   new149-byte callback; F158 cold-replayed the new79-byte counter. Both large
   drafts remain unaccepted. No old accepted dependency changed or needed replay.

## Historical F157 pending work; current resolutions are above

The private directory `.analysis/character-move-4ac040/f157/` contains 1,656
retained files. All 14 `build/probes/F157*.obj` objects are retained, with hashes
in `.analysis/f157-handoff/retained-f157-inputs.json`. No F157 source or exact
credit has been entered. Preserve this workspace: private evidence, probes and
the Ghidra project are excluded from Git.

- **Counter454D00:** `CounterPostfix.cpp` naturally uses `COUNTERS[index]++`
  with the existing declaration in `src/FighterResourceParameters452B30.hpp`.
  `F157CounterPostfix.obj` has a positive old-object diagnostic over all 79 bytes,
  with zero relocation fields. The report is
  `.analysis/f157-handoff/counter-old-object-diagnostic.json`; its result is
  `structural-exact`, not canonical cold acceptance. The earlier prefix and
  compound-expression controls remain private. Neither an original bank type
  nor a complete owner layout is established.
- An unfinished `profile-increment-counter-00454d00` registration referenced
  missing `src/ProfileSelection454D00.cpp`, causing tracking validation to fail.
  Cleanup preserved the exact registration in
  `.analysis/f157-handoff/pending-registration.patch` and restored the manifest
  to its 338 accepted definitions. The private source/object remain available.
  Review the complete R182 extent, add a real production source,
  and run canonical cold replay before updating acceptance ledgers.
- **Whole caller controls:** seven complete reports are retained. `/G5`, `/G7`,
  void-return expression in 88, read-only phase accessor and typed field indexing
  still report 83,922 bytes/18,539 differences/all 2,352 fields. A mutable phase
  accessor emits 84,021 bytes/79,585 differences and is rejected. The bounded
  `cursor-resets` debugger build retains the same baseline comparison.
- The eighth caller build, `F157FieldPrefix.obj`, changes 20 discarded word-field
  increments from postfix to prefix. Its source/profile/compile log and snapshot are
  retained under `snapshots/field-prefix/`. **No complete whole diagnostic was
  recorded for this candidate.** Do not infer a match from compilation. Use
  `snapshots/cursor-resets/Preview.cpp` for the F157 baseline, SHA prefix97e045e6;
  it matches the authoritative F156 source.
- The completed cursor trace records 8,223 maps/13,951 emissions, one initial
  cursor initialization and zero observations of the known conditional reset.
  This does not exclude other writes or recover the target's original virtual
  state. `c2-cursor-xref-shortlist.json` came from an incomplete linear decode;
  its empty `hits` must not be read as absence of cursor references.
- Profile initializer 416640 establishes cleared storage ranges and observed
  loop strides, not a complete nominal bank/owner layout. Related 4C stores in
  57D580 belong to a different receiver family and do not establish Fighter4C.
  The return-consumer scan has unresolved branch/forward cases; its five reviewed
  candidates consume only an independently overwritten low byte. No reset return
  ABI or broader receiver layout was adopted. All 97 unknown origins stay unknown.

Cleanup adds no reconstruction bytes and runs no compiler or cold replay.
The accepted 338 definitions, 139 canonical objects, 217 source/header inputs,
all origin evidence, forty protected groups and prior active objects were
hash-checked unchanged against the F157 seed. F156's 1,155 private files and
1,176 checkpoint files are also intact. Preservation receipts are under
`.analysis/f157-handoff/`; final validation is recorded at the end of this file.

## Retained F156 complete caller evidence

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

## F157 cleanup and handoff verification

Public CI passed **3,603 tests in 180.527 seconds**. Target identity, tracking,
status and headless Ghidra attestation pass. The accepted manifest is restored
to 338 units; exact credit remains 717,509 bytes and conservative coverage 36.29%.
No accepted source/header or canonical object changed, so no cold replay was
needed. All prior evidence and all 14 F157 probe objects remain intact.

Cleanup removed 375 reproducible bytecode files from scripts/tests, freeing
8,285,289 bytes. Sources, manifests, evidence, all accepted/active/pending
objects, the private project and shared tools were preserved. Receipts are
`.analysis/f157-handoff/initial-checkpoint.json`, `retained-f157-inputs.json`,
`source-state-check.json`, `cleanup.json`, `final-verification.json` and
`source-checkpoint.json`, all under `.analysis/f157-handoff/`.
The cleanup checkpoint did not complete the 98% objective. Its pause was an
agent error; the user has explicitly prohibited pausing. Continue reconstruction.

## F158 verification

Public CI passed **3603 tests in 166.926 seconds**. Target,
tracking, status, generated progress card and diff checks pass. Only the new
counter was cold-replayed:79/79 complete bytes exact with zero actual fields.
All338 prior unit definitions,139 canonical objects,217 accepted source/header
inputs, forty protected groups, origin evidence through R268, all14 F157 probes
and prior active objects were hash-verified unchanged. No old unit needed replay.

Two compiler builds ran serially/headless: the new canonical counter and one
whole caller control. The inherited prefix control was compared from its retained
object. Both full controls retain83,922 bytes/18,539 differences/all2,352 fields;
neither earns exact credit. All151 F158 entries and prefix/default/shared tail
were restored byte-for-byte to F156. The first real difference remains004ADEFB.

Cleanup removed one obsolete reproducible control object (159,716 bytes)
and 375 bytecode files (8,285,294 bytes). Full source/control
snapshots, profiles, raw bytes/actual relocation/native reports and logs remain.
Receipts: `.analysis/f158-counter-unit-proof.json`,
`.analysis/f158-counter-canonical-replay.json`, `.analysis/f158-preservation-final.json`,
`.analysis/f158-cleanup.json` and `.analysis/f158-source-checkpoint.json`.
Current exact code is717,588 bytes across339 units; conservative coverage36.29%.
The98% objective stays active and incomplete. Do not pause it.

## F159 verification

Public CI passed **3,603 tests in 175.094 seconds**. Target,
tracking, status, progress card and diff checks pass. One new canonical object
cold-replayed36/36 complete authored units,1,957 bytes and all16 actual REL32
fields. All339 prior units,140 objects,218 source/header inputs, all origin
records/verifier guards, forty protected groups, fourteen F157 probes and prior
active objects were hash-verified unchanged. No old dependency required replay.

Four compiler builds ran serially/headless: two33-function compiler observations,
one36-function diagnostic and one36-unit canonical cold build. The reordered
trace observes a real allocating predecessor leave head2, followed by initializer
reset to head1; all687 code bytes/12 fields are unchanged between orders. Original
target virtual state/other compiler globals remain unknown. No filler, tool/target
patch or queue mutation. The complete151-entry move source is unchanged, with
its full83,922-byte/18,539-position failure/all2,352 fields retained.

Cleanup removed one obsolete diagnostic object (23,185 bytes)
and376 bytecode files (8,297,864 bytes). Full sources,
profiles, raw native/function/relocation evidence, logs and both F159 trace
objects remain. Receipts: `.analysis/f159-actions-unit-proof.json`,
`.analysis/f159-actions-canonical-replay.json`, `.analysis/f159-preservation-final.json`,
`.analysis/f159-cleanup.json` and `.analysis/f159-source-checkpoint.json`.
Current exact code is719,545 bytes/375 units; conservative coverage36.39%.
The98% goal remains active and incomplete. Do not pause it.

## F160 verification

Public CI passed **3,603 tests in 190.513 seconds**. Target,
tracking, status, progress card and diff checks pass. Two new objects cold-replay
963/963 complete authored bytes and all29 actual fields. All375 prior units,
141 objects,220 adoption inputs plus shared-header protection, every origin/
verifier guard, forty protected groups and all prior active objects were
hash-verified unchanged. No old accepted dependency required replay.

Six compiler builds ran serially/headless: four diagnostics/controls and two
new canonical objects. All22 complete generic vendor helper bodies/fields
retain their frozen R110 comparison, without new credit. The rejected named
pointer-local cleanup has five genuine stack-slot differences. The int-truncation
control preserves all83,922 raw bytes/all2,352 actual destinations, while132 local
labels change; full target comparison remains18,539 differences/first004ADEFB.
All151 current source entries/prefix/default/shared tail are restored to baseline.

Cleanup removed four obsolete diagnostic objects (202,581 bytes)
and375 bytecode files (8,285,304 bytes). Full source/header
snapshots, raw code/native/relocation/template evidence and logs remain, along
with both F159 traces/all14 F157 probes/all old active objects. Receipts:
`.analysis/f160-dependencies-unit-proof.json`,
`.analysis/f160-dependencies-canonical-replay.json`, `.analysis/f160-preservation-final.json`,
`.analysis/f160-cleanup.json` and `.analysis/f160-source-checkpoint.json`.
Current exact code is720,508 bytes/377 units; conservative coverage36.44%.
The98% goal remains active and incomplete. Do not pause it.
