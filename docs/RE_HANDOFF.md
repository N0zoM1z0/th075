# TH075 function reconstruction handoff

Updated 2026-10-24. The user resumed reconstruction after the cleanup/handoff
checkpoint and set an active **98% authored bytes exact** goal. The objective
is incomplete. Continue the F080 damage-flash investigation below; preserve the F066 draft.
Subsequent project phases remain deferred. Use existing Ghidra/local tools,
without REA; commit subjects must use `gpt-6.1-sol: ...`. Commits and pushes
remain authorized. Keep compiler builds serial and monitor CPU/memory.

## Verified checkpoint

| Measure | Current value |
| --- | --- |
| Provisional candidates | 4,351 |
| Reviewed authored / library / compiler | 1,002 / 2,671 / 581 |
| Unknown origins | 97, totaling 3,608 bytes |
| Source-present / exact functions / exact units | 172 / 172 / 172 |
| Exact code bytes | 547,786 |
| Reviewed authored coverage | 547,786 / 1,973,516 (27.76%) |
| Conservative coverage, including every pending byte | 547,786 / 1,977,124 (27.71%) |

The ledgers and status script are authoritative. Origin evidence through R268
is unchanged. The exact-adoption manifest retains F009 and **112 additions /
537,903 code bytes / 136 new source/header inputs**. F021/F048/F061/F066 remain
unaccepted. Unknown origins receive no credit and do not block independently
reviewed authored functions.

The only target is the supplied Japanese `th075.exe`, reporting version 1.11:
SHA-256 `bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
Identity is pinned to the supplied archive, without independent official
provenance corroboration. Never substitute `th075c.exe` or patch target bytes.

## Latest accepted function: F079

R042 mode-5 menu 00448710..004491DD cold-replays exact as
`BattleModeFive448710::RenderMenu`: all 2,766 bytes, 665 instructions, 43 branches,
65 physical fields and 65 real call packets. Two following INT3 bytes are excluded.
Seven complete direct callees and 16 USER32!SetRect calls are checked. The accepted
F078 caller supplies this with no stack arguments. Alias preserves the historical
BattleScene::RenderPauseMenu role without claiming the original screen identity.

Four loops reuse one real index, with nine/six/ten/two entries. Actual white/gray
color stores, signed actor selectors, repeated integer expressions, four int-to-
float conversions and the alpha early exit are retained. One initialized complete
132-byte F064 packet precedes the guard and is reused. The final portrait uses
left actor+534; ordinary atlas drawing uses current+8. No partial owner is
constructed or embedded. All accepted shared headers stay unchanged.

The first complete preview has the native size and instruction count; 76 bytes
encode different color/RECT frame positions. A single meaningful local rename
from rect to region reproduces the actual allocation; all 65 relocations remain
unchanged. This is a compiler observation, not original local spelling or owner-
layout evidence. The complete 184-byte frame contains the shared index, packet,
color, RECT, this and four real conversion slots. No padding or inert locals.

Independent canonical compilation and separate canonical cold replay match all
bytes with the explicit build3077 profile. Physical bindings are 49 direct calls
and 16 named imports; no globals or readonly data fields receive credit. Zero
addends, operand positions, executable/import permissions, every branch and whole
CFG stack joins are checked. Wrong SetRect/translation cleanup controls fail.
All 171 prior units/objects, 134 previous manifest inputs, 218 origin files,
4,350 other function rows and 84 active draft inputs remain unchanged and were
not rebuilt. All 97 pending origins remain unknown. F009 plus 112 additions
retains 537,903 bytes and 136 new source/header inputs. The 98% goal is incomplete.

```bash
scripts/repo-python scripts/replay-exact-units.py --unit battle-mode-five-menu-00448710
```

Full CI passes **3,603 tests in 119.171 seconds**, plus tracking, progress and
whitespace. Keep f079 native/attested/ABI/physical/cold/parent/progress/preservation
evidence and both complete compiler input snapshots. Two obsolete preview objects
were removed after pinning inputs and whole cold-canonical code/relocation equality.
PDBs, logs, source/control inputs, evidence, canonical objects, older active drafts
and shared tools remain. Scripts/tests bytecode was removed after CI.

Next F080: complete R042 damage flash 004406C0..00440AF8, 1,081 bytes.
`.analysis/f080-native-index.json` pins 292 instructions, 20 branches and 23 calls:
21 direct calls to five complete callees plus two SetRect calls. Fresh attested
root/callee/caller views are retained. ABI review checks all packets and twelve
implicit ST0 conversions; nested coordinate calls preserve zero/one/two/three
outer SetRect words. Review the actual x87 formulas and shared byte/color local
before one complete natural body. The original scan misclassified writable float
00671404 as a constant; PE permission review corrects the index and preserves the
old scan. Reuse existing g_CombatViewOffsetX/Y views without changing headers.
No F080 source, object, canonical unit or credit exists. Keep all older units and
large unaccepted drafts.

## Previous accepted function: F078

R042 end overlay 00441910..00441E95 cold-replays exact as
`BattleEndOverlay441910::RenderEndOverlay`: all 1,414 bytes, 340 instructions,
20 branches, 38 physical fields and 30 real call packets. Ten following INT3
bytes are excluded. Eight complete direct callees and seven USER32!SetRect calls
are checked. The accepted F074 caller supplies this with no stack arguments.

The mode-5 path invokes the complete 2,766-byte 00448710 delegate and skips quad
construction. The alternate path constructs the unchanged complete 132-byte
F064 packet and shares one RECT within its render-pass scope. That scope accounts
for the native 156-byte frame. Actual alpha/flag guards return along the native
early-exit paths; no return value is invented. Single-side portrait branches
retain native ordering. Portrait drawing uses actor+534, while ordinary UI uses
current+8. All byte selectors and the actual repeated quad operations remain.
Partial owners are pointer-only and never constructed or embedded. Original
names, declarations and complete owner layouts remain unknown.

Preview, independent canonical compile and separate canonical cold replay match
the whole function with the explicit build3077 profile. All 38 physical fields
bind 23 direct calls, seven named imports and eight fields at four globals.
Widths, zero addends, permissions, import identity, all branch fields and whole
CFG stack joins are checked; wrong SetRect/translation cleanup controls fail.
Three global names are reused unchanged. New g_EndOverlayFlagAt00671624 is an
inferred unsigned-byte access view supported by native MOVZX and the zero gate;
its original declaration/name/data ownership remains unknown and earns no data
credit. The delegate remains unimplemented and receives no exact credit.

All 170 previous units/objects, 132 previous manifest inputs, 218 origin files,
4,350 other function rows and 84 active draft inputs remain unchanged and were
not rebuilt. Every accepted shared header stays fixed. All 97 pending origins
remain unknown. F009 plus 111 additions retains 535,137 bytes and 134 new source/
header inputs. The 98% conservative authored-byte goal remains incomplete.

```bash
scripts/repo-python scripts/replay-exact-units.py --unit battle-end-overlay-00441910
```

Full CI passes **3,603 tests in 127.667 seconds**, plus tracking, progress and
whitespace. Keep f078 native/root/callee/caller/attested/ABI/physical/cold/parent/
progress/preservation evidence. Three obsolete reproducible preview objects
were removed after pinning source/header/profile snapshots. The last preview
matched all canonical code and 38 relocations after the explicit Draft-to-
canonical owner rename. Inputs, PDBs, logs, evidence, canonical objects, older
active drafts and shared tools remain. Scripts/tests bytecode was removed after CI.

The subsequent F079 acceptance and current F080 cohort are recorded above.

## Previous accepted function: F077

R042 overlay timeline 00447340..004480C2 cold-replays exact as
`BattleTimeline447340::RenderTimeline`: all 3,459 bytes, 858 instructions, 25
branches, 137 physical fields and 72 real call packets. Thirteen following
INT3 bytes are excluded. Eight complete direct callees and 14 USER32!SetRect
calls are checked. The accepted F074 caller supplies this without stack arguments.

The native byte discriminator uses a two-case switch, with a real generated
byte slot. One complete initialized 132-byte F064 packet and one shared RECT
scoped to the switch reproduce the native 160-byte frame without added locals.
The last case falls through to the switch exit. Every accepted shared header
remains unchanged; the new rotation interface is pointer-only and is never
constructed or embedded. Original names, declarations and full owner layouts
remain unknown. No local-span estimate establishes an owner size.

Native scroll arithmetic is zero minus tick*5, including width minus tick*5;
Ghidra normalizes it to multiplication by -5. The raw positive-angle comparison
runs rotation first and sends nonpositive/unordered results to its fallback.
Ghidra's reversed <=0 rendering does not preserve that unordered route. The
source retains the actual comparison order and literal signed bounds >70,
<=75, <=10 and >65. Both first previews remain diagnostic controls; the final
complete body matches every instruction, register, displacement and branch.
Three actual unsigned-byte alpha conversions consume ST0 through implicit
ftol2, preserve native low-byte extraction, and build the real white ARGB colors.

The full 1,212-byte rotation helper is reviewed: all receiver memory accesses
stay within the four coordinate records at offsets 0..63, all six float inputs
are real stack words, and cleanup is ret24. No receiver pointer is passed to
its math helpers. All 72 root call packets and whole CFG stack joins are checked;
wrong SetRect/rotation cleanup controls fail. Physical bindings include 58 direct
calls, 65 readonly float fields and 14 named imports. Payloads, widths, zero
addends, permissions, import identity, every branch and the full extent match.
No writable global or additional dependency receives new credit.

Independent canonical compilation and separate canonical cold replay pass with
the explicit build3077 profile. All 169 prior units/objects, 130 previous manifest
inputs, 218 origin files, 4,350 other function rows and 84 active draft inputs
remain unchanged and were not rebuilt. All 97 pending origins remain unknown.
F009 plus 110 additions retains 533,723 bytes and 132 new source/header inputs.
The 98% conservative authored-byte goal remains active and incomplete.

```bash
scripts/repo-python scripts/replay-exact-units.py --unit battle-overlay-timeline-00447340
```

Full CI passes **3,603 tests in 115.937 seconds**, plus tracking, progress and
whitespace. Keep all f077 native/root/callee/caller/attested/ABI/physical/cold/
parent/progress and preservation evidence. Three obsolete reproducible preview
objects were removed after pinning complete source/header/profile inputs; the
last preview first matched all canonical code and 137 relocations. Sources,
PDBs, compiler logs, diagnostic results, canonical objects, prior active drafts
and shared tools remain. Generated scripts/tests bytecode was removed after CI.

The subsequent F078 acceptance and current F079 cohort are recorded above.

## Previous accepted function: F076

R042 status renderer 00440B50..00441905 cold-replays exact as
`BattleStatus440B50::RenderStatus`: all 3,510 bytes, 750 instructions, 13
branches, 84 physical fields and 45 actual call packets. Ten complete direct
callees and eight USER32!SetRect calls are checked; ten following INT3 bytes
are excluded. The accepted F074 caller supplies this without stack arguments.

The first complete handwritten preview is structural-exact. Independent
canonical compilation and separate canonical cold replay match every byte.
One initialized 132-byte F064 packet is reused across both loop sides. Its
actual render-loop scope, two conversion slots, shared RECT, selected texture,
group, index, float offset and saved ESI account for the full 184-byte frame.
All accepted shared headers remain unchanged. Partial receivers are pointer-only
and never constructed or embedded; original names/declarations and full owner
layouts remain unknown. No Ghidra local-span value becomes an owner-size claim.

The raw code keeps indexed coordinates and alpha arrays on side 0, although
Ghidra folds them to fixed offsets in that branch. Nested directory lookups
retain actual outer indices, including signed repeat-byte +5. Both complete
44-byte record getters consume a signed-byte selector, return ret4, and define
the whole EAX by zero-extending a word; each caller immediately pushes EAX to
the full integer number worker. Their outer style/padding words remain pending.
The new scoped integer-result declarations describe that observed behavior;
original nominal declarations remain unknown and neither getter earns credit.
The existing g_BattleRecords address and both byte globals are reused.

Physical bindings include 37 direct calls, 33 readonly float fields, four byte
global fields, two record-owner address fields and eight named imports. Actual
payloads, permissions, operand widths, zero addends, all branch fields and whole
CFG stack joins are checked. Wrong nested/getter cleanup controls fail. All 168
older units/objects, 128 previous manifest inputs, 218 origin files, 4,350 other
function rows and 84 active draft inputs remain unchanged and were not rebuilt.
All 97 pending origins remain unknown. F009 plus 109 additions retains 530,264
code bytes and 130 new source/header inputs. The 98% goal remains incomplete.

```bash
scripts/repo-python scripts/replay-exact-units.py --unit battle-status-render-00440b50
```

Full CI passes **3,603 tests in 119.952 seconds**, plus tracking, progress and
whitespace. Keep f076 native/root/callee/attested/ABI/physical/cold/parent/progress/
preservation evidence. The duplicate preview object was removed after complete
code and all 84 relocations matched the cold canonical object. Scripts/tests
bytecode was removed after CI; sources, headers, PDBs, evidence, active drafts,
canonical objects and shared tools remain.

The subsequent F077 acceptance and current F078 cohort are recorded above.

## Previous accepted function: F075

R040 HUD renderer 0043E040..004406B0 is independently cold-exact as
`BattleHud43E040::RenderHud`: all 9,841 bytes, 2,401 instructions, 81 branches,
265 physical fields and 189 real call packets. The following 15 INT3 bytes
are excluded. All 13 complete direct callees and 36 USER32!SetRect calls are
checked. The complete accepted F074 caller supplies this and no stack arguments.

The source reuses the unchanged complete 132-byte F064 physical quad packet.
Its constructor initializes all transferred storage; transform helpers consume
the coordinate prefix. A genuine quad-submission scope plus meaningful names
for the ten real locals reproduces every frame displacement. Bounded compiler
controls and local CodeView records support this allocation; no owner-size
claim is derived from Ghidra's 140-byte local span. Original names, nominal
private declarations, payload partition and full receiver layouts remain unknown.

Six nested directory lookups preserve pending outer record indices. Complete
iterator helpers establish four-byte pointer slots and 116-byte record stride;
only borrowed shorts at record +0/+6 are read. No partial owner is constructed.
Six ftol2 calls consume ST0 without explicit C arguments; the last two preserve
outer style 10 and retain the native short conversion. Double meter thresholds,
ordered float clamps, color construction, signed byte reads, all repeated draws
and both complete combo-widget receiver calls remain intact. The final explicit
mode-3 empty branch expresses its omitted right numeric gauge and reproduces
the native two-jump path. A one-case switch adds an unsupported local and is
rejected. This source choice does not establish original control-flow spelling.

All 265 physical fields bind 153 direct calls, 61 readonly constants, 15 fields
at five existing globals and 36 named imports. Actual payloads, operand widths,
PE/COFF permissions, zero addends, import identity, all 81 branch fields and
whole CFG stack joins are checked. Wrong nested/ftol2 cleanup controls fail.
Independent canonical compile and separate canonical cold replay match every
byte using the explicit build3077 profile. All 167 previous units/objects, 126
prior manifest inputs, 218 origin files, 4,350 other function rows and 84 active
draft inputs remain unchanged. No older unit was rebuilt. All 97 pending origins
remain unknown and receive no credit; the 98% goal remains active and incomplete.

```bash
scripts/repo-python scripts/replay-exact-units.py --unit battle-hud-render-0043e040
```

Full CI passes **3,603 tests in 120.751 seconds**; tracking, progress and
whitespace checks pass. Keep f075 native/attested/lookup/ABI/physical/cold/
adoption-parent/progress/preservation receipts and compiler input snapshots.
Twenty-two obsolete reproducible objects (1,310,871 bytes) were removed after
recording their hashes and retaining inputs/results/logs/PDBs. The final preview
matched the cold canonical code and all 265 relocations before removal. Nearest
whole draft06 and final scoped-local control remain. Generated scripts/tests
bytecode was removed after CI; evidence, active objects and shared tools remain.

The subsequent F076 acceptance and current F077 cohort are recorded above.

## Previous accepted function: F074

R041 render callback0043D9D0..0043E034 is cold-exact as
`BattleRender43D9D0::RenderFrame`: all1,637 bytes,455 instructions,31 branches,
91 physical fields and64 actual calls. The following11 INT3 bytes are excluded.
All23 complete direct callees,14 virtual calls across11 recorded fighter
families,and three named IAT calls are reviewed. The full data xref0065833C
references this callback; there are no direct call xrefs in the current database.

The caller consumes AL from the complete36-byte graphics wrapper. Its accepted
bool worker supplies the status; the wrapper forwards AL unchanged. A natural
independent bool-forwarding compiler proof matches all36 bytes/three fields.
The new declaration-only status view leaves the older ignored-result body and
all accepted shared headers unchanged. This does not recover the original
nominal declaration or add dependency credit. Native DWORD timing,signed-byte
selectors,true zero terms,real RECT local and saved ESI are retained. Partial
receivers are pointer-only and never constructed or embedded. Unused virtual
signatures,full owner layouts and live dispatcher identities remain unknown.

Preview,independent canonical compile and separate cold replay match every
byte with the explicit build3077 profile. All166 earlier units/objects,124
prior manifest inputs,218 origin files,4,350 other function rows and84 active
draft inputs remain unchanged. No older unit was rebuilt. Retain f074 native,
attested,ABI,status-proof,virtual-family,physical-binding,cold,adoption-parent,
progress and preservation/cleanup receipts under .analysis/.

```bash
scripts/repo-python scripts/replay-exact-units.py --unit battle-render-frame-0043d9d0
```

Full CI passes **3,603 tests in116.318 seconds**,plus tracking and progress.
The duplicate preview object was removed after complete code/relocation equality;
generated scripts/tests bytecode was removed after CI. Inputs,PDBs,evidence,
active objects,the separate ABI proof and shared tools remain.

The subsequent F075 acceptance and current F076 cohort are recorded above.

## Previous accepted function: F073

R100 camera initializer00412660..004126BF is independently cold-exact as
`CameraInputs412660::Initialize`: all96 bytes/22 instructions/14 physical fields.
Four coordinate pointer stores,one actual accepted camera update call,the real
horizontal/vertical snapshots and outputX/currentY+300.0f are retained. The
next byte starts the separate1520-byte camera update; no padding is credited.
Alias preserves CameraMotion::InitializeAt00412660. All origins stay fixed.

The complete004176F0 caller passes four scalar addresses in order left+44,
left+48,right+44,right+48 and cleans16 bytes. The initializer is cdecl,ret0,
with no user locals/frame storage. It borrows real float addresses without
constructing/embedding any actor. Update runs before snapshots,so its actual
shake/bias/override effects remain. No zoom or bias reset is invented. All
existing camera globals/header are reused unchanged. Original names/types/
full pointed owner layouts and nominal return declarations remain unknown.

Preview,independent canonical compile and separate canonical cold replay match
all96 bytes and14 fields with the explicit build3077 profile. Constant payload,
COFF/PE permissions/widths and actual call/argument contracts are checked.
All165 prior units/canonical objects and122 prior manifest inputs remain
unchanged and were not rebuilt. Retain f073 binder/ABI/native/caller/attested/
physical/cold/parent/progress evidence and private preview source/header.

```bash
scripts/repo-python scripts/replay-exact-units.py --unit camera-inputs-00412660
```

Full CI passes **3,603 tests in125.315 seconds**,plus tracking,progress and
whitespace. Evidence check retains165 prior units/objects,122 inputs,218 origin
files,4350 other rows and every active draft/fragment. The duplicate preview
object and scripts/tests bytecode are removed after full equality/CI; inputs,
PDBs,evidence,active objects and shared tools remain. The prior next-cohort
paragraph's mistaken R102 label is corrected to the ledger's actual R100.

The subsequent F074 acceptance and current F075 cohort are recorded above.

## Previous accepted function: F072

R035 camera update004126C0..00412CAF is independently cold-exact as
`CameraUpdate4126C0::Advance`: complete1520 bytes/336 instructions/36 branches,
48 readonly constant fields,135 writable global fields and8 calls. All191
physical fields, payloads,permissions,widths,addends and operand positions match.
The next byte starts the already accepted setter00412CB0; no alignment or
subsequent function bytes are credited. Alias preserves CameraMotion::Update.

The natural free-function body retains weighted coordinate order, horizontal/
vertical/zoom clamps,override controls,signed span/3,smoothing and strict bias
crossings. Shake preserves radians0.01745328866f,83/107 phase increments,single
360-degree wraps,0.95f decay and actual zero stores. Zoom's minimum calls its
math helper twice and retains both +0.0f operations. All equality/unordered
floating paths and both signed integer conversions remain exact. One actual
int span plus two conversion temporaries explain the native twelve-byte frame.

All eight real call packets and six full math wrapper/worker bodies are
reviewed. Four-byte float inputs,worker widening to double,actual ST0 results,
CRT fabs and complete174-byte cosine/sine primaries are pinned; the nine-byte
interior C entries are not treated as whole runtime implementations. Implicit
ftol2 uses ST0-to-EDX:EAX with no declared fake C arguments. Ghidra's void/
thiscall guesses are rejected against the raw bodies and R163 alternatives.
The six helper origins remain unknown. Original names,declarations and nominal
return precision remain unrecovered. No owner is constructed or embedded.

There are23 actual global locations. Nineteen new inferred views are appended;
three F018 output/span names and the F071 shake amount are reused unchanged.
The complete96-byte initializer and1637-byte render caller each invoke the
new function without explicit arguments. Both full caller exports are pinned.
Preview,independent canonical compile and separate canonical cold replay match
with the explicit build3077 profile. All164 older units/objects and120 older
inputs are unchanged and were not rebuilt. Keep f072 binder/ABI/physical/cold/
parent/progress evidence,all dependency/caller exports and attested views/logs.

```bash
scripts/repo-python scripts/replay-exact-units.py --unit camera-update-004126c0
```

Full CI passes **3,603 tests in114.956 seconds**, plus tracking,progress and
whitespace checks. Evidence check preserves164 prior units/objects,120 inputs,
218 origin files,4350 other rows and all active drafts/fragments. The duplicate
preview object and two identical F066 profile objects are removed only after
full function/relocation equality; source/PDB/evidence/shared tools remain.
Generated scripts/tests bytecode is removed after CI with hash receipts.

New F066 controls/G5 and/Z7 on unchanged active03 also emit identical complete
28868-byte code and all696 relocations. They do not explain the first0055F711
register difference. Keep `.analysis/f066-profile-controls/` source hashes,
profiles/logs/results and retained active03; do not repeat without new evidence.

Next F073: complete camera initializer00412660,96 bytes,R100. Natural private
source/header at `.analysis/camera-initialize-412660/Preview.cpp` / `.hpp`
and active `build/probes/F073Preview.obj` are structural-exact with14 fields.
This is diagnostic only,no source presence,unit or exact credit. Finish all
physical/ABI bindings then canonical compile/cold replay. Its full native and
fresh attested views also expose the next complete render parent0043D9D0,
1637 bytes. Preserve all F066/F061/F048/F021 drafts and97 pending origins.

## Previous accepted cohort: F071

Three complete service bodies from `src/EffectServices.cpp` / `.hpp` are
independently cold-exact: shared sound0045B860 (29 bytes/11 instructions),
fighter shake00453E60 (25/11), and shake amount00412CB0 (13/6). All67 bytes,
four physical relocations, actual returns and adjacent alignment boundaries
are checked. Explicit aliases preserve R102/R035 historical roles; ownership,
native extents/hashes and all97 unknown origins remain unchanged.

Sound sign-extends the actual short to the existing SoundBank::Play(int)
contract and loads the real shared bank pointer. The actual142-byte bank
callee uses a dword argument and ret4. Shake forwards the unchanged float word
to the cdecl setter with four-byte caller cleanup; setter stores the same
word at006713F8. Its float view is independently supported by six x87 uses in
complete004126C0 and the real F0663.0f owner-at-E4 call. Both wrong-cleanup
controls fail. Two sound callers pass current; one shake caller passes owner.
Original declarations/names/full layouts remain unknown. Never construct/embed
partial owners. The existing shared GameLeafHelpers header is unchanged.

Preview, independent canonical compile and a separate cold build accept all
three units across one new object with the existing explicit build3077 profile.
All161 previous units/objects and118 previous source inputs are unchanged and
were not rebuilt. Retain f071 binder, ABI review, both physical receipts,
accepted replay/log, adoption-parent/progress, fresh attested views/log,
candidate/native evidence and private preview sources. Reproduce only these:

```bash
scripts/repo-python scripts/replay-exact-units.py --unit effect-shared-sound-0045b860 --unit fighter-camera-shake-00453e60 --unit camera-shake-amount-00412cb0
```

Full CI passes **3,603 tests in126.719 seconds**; tracking, progress and
whitespace checks pass. The evidence check retains all161 prior units/objects,
118 inputs,218 origin files,4348 other function rows and every active draft.
The redundant preview object and generated scripts/tests bytecode were removed
after full equality/CI, preserving PDBs/inputs/evidence/shared tools.

Next: R035 complete camera update004126C0,1520 bytes. Full raw native export
and fresh attested view are retained. The natural preview at
`.analysis/camera-update-4126c0/Preview.cpp` / `.hpp` and active
`build/probes/F072Preview.obj` emits a1520-byte structural-exact body.
No F072 source-presence entry, canonical unit or exact credit exists. Complete
physical191-relocation/global/constant binding and ABI review are still required.
All six small dependency origins remain unknown and receive no credit.
Continue large F066 only from preserved active03, without repeating controls.

## Previous accepted function: F070

`RecordedRange455580::SelectRange` cold-replays exact across all 139 bytes at
`0x00455580..0x0045560A`: 40 instructions, four branches, five actual calls,
11 complete relocation bindings and ret8. Five following INT3 bytes are
excluded. The R109 historical role, native extent/hash and ownership are fixed.

Mode2 consumes a signed word from the shared queue when count>0, or keeps
zero on empty. Other modes cast the real CRT rand result to short; mode1
records the same local word by reference. The return retains signed
`(upper-lower)*sample/32768+lower`, including truncation toward zero. Frame8
saves this at EBP-8 and the real short sample at EBP-4. All 24 F066 calls use
current. Full count/front/pop/push/rand bodies, the actual two-byte construction
leaf, every branch/stack join and a wrong PushBack-cleanup negative are checked.

Both mode reads bind to the existing signed byte at0066C238. Four immediate
ECX receivers bind to006718B8; an unbounded external byte storage view plus a
pointer-only call interface models those actual addresses. No partial container
or game owner is instantiated/embedded, and no extent or original template
argument is claimed. The actual push takes a pointer to the local short and
returns with four-byte cleanup; the other four calls consume no caller args.
All dependency origins, including unknowns, remain unchanged and get no credit.

Preview, independent canonical compile and separate canonical cold replay
match with the existing explicit build3077 profile. All 160 previous units,
canonical objects and accepted inputs remain unchanged and were not rebuilt.
Retain f070-bind.py, both physical receipts, accepted replay/log, parent/progress,
full dependency exports/index, attested views/log and private preview inputs.

```bash
scripts/repo-python scripts/replay-exact-units.py --unit recorded-random-range-00455580
```

Full CI passes **3,603 tests in 236.917 seconds**. Tracking, progress and
whitespace checks pass; `f070-evidence-check.json` verifies all 160 prior
units/objects, 116 prior source inputs, 218 origin files, 4,350 other function
rows and active drafts unchanged. The preview object and generated scripts/
tests bytecode were removed after checks with hash receipts. No swap was
observed; sampled available memory is about 12 GiB.

The F071 preview now has one natural body per complete function in
`.analysis/effect-services-f071/Preview.cpp` / `.hpp`, with active
`build/probes/F071Preview.obj`. The full 67 bytes and four physical bindings
match diagnostically in `f071-draft-relocation-bindings.json`. Full native
exports and candidate origins are pinned in `f071-candidate-index.json`.
No F071 source presence, canonical unit, origin change or exact credit exists.
Continue complete source/ABI review, fresh attested views, independent canonical
compile and affected-unit cold replay. Preserve all PDBs/inputs/evidence.

Next: the complete actual sound/shake wrappers at0045B860/00453E60, with the
13-byte shake setter00412CB0 and its already retained x87 consumer evidence.
Continue the large F066 draft only from preserved active03; none of its 976
physical instruction differences has been resolved or accepted.

## Previous accepted function: F069

`ObjectMotion40FB70::SetPolarVelocity` cold-replays exact across all 57 bytes
at `0x0040FB70..0x0040FBA8`: 22 instructions, two complete REL32 bindings,
ret8 and no branches/tables. Seven following INT3 bytes are excluded.
An explicit alias preserves R217's historical role and fixed extent/hash.

The X component is the accepted cosine lookup result multiplied by speed.
The Y component negates the accepted phase lookup result before multiplying
speed. Both callees take the unchanged float angle with cdecl four-byte caller
cleanup and return in x87 ST0. Native FCHS precedes the second FMUL. Ghidra's
inferred int returns for the callees are rejected against their complete native
bodies and accepted MathLookup units. All 23 F066 calls pass current, with
ret8 cleanup. Native frame is four bytes; this is saved at EBP-4.

Preview, independent canonical compilation and separate cold replay match with
the existing explicit build3077 profile. All 159 previous units/canonical
objects and existing source/header inputs are unchanged and were not rebuilt.
No prior MathLookup or partial owner layout is changed. Never construct/embed
this receiver. Original declarations/names and complete owner layout remain
unknown. Retain f069-bind.py, physical receipts, accepted replay/log,
adoption-parent, progress, attested views/log and private preview inputs.

```bash
scripts/repo-python scripts/replay-exact-units.py --unit object-polar-velocity-0040fb70
```

Focused adoption/goal checks pass, along with tracking, progress and whitespace.
The preceding full CI checkpoint is F068 (3,603 tests). Next: complete recorded
range `0x00455580` (139 bytes, R109), then sound/shake wrappers. F066 remains
unaccepted at its preserved active03 state.

## Previous accepted function: F068

`SpriteTransform40FBB0::ResetNodeTransform` cold-replays exact across all
158 bytes at `0x0040FBB0..0x0040FC4D`: 47 instructions, one fully bound
`memset` relocation, one ret12, no branches/tables. Two following INT3 bytes
are excluded. The R036 role `SpriteScene::ResetNodeTransform` is retained by
alias; ownership, native extent and hash remain fixed.

The declaration-only receiver takes three float words, stores them at
+34/+38/+3C, enables +40, clears exactly 36 bytes at +10, and performs all
actual scale/color/short/byte resets, including duplicate writes after the
clear. The real memset call is cdecl with 12-byte caller cleanup. All 57 F066
sites pass current and the callee returns with 12-byte argument cleanup.
Original declarations/names and full owner layout remain unknown. Never
construct or embed this receiver or the older partial SpriteTransform view.

Preview, independent canonical compile and separate canonical cold replay
match with the existing explicit VC7.1 build 3077 profile. No prior accepted
source/header changed; all 158 earlier units/canonical objects are unchanged
and were not rebuilt. Retain `.analysis/f068-bind.py`, both binding receipts,
`f068-accepted-replay.json`, `f068-cold-replay.log`, `f068-adoption-parent.json`,
`f068-progress.json`, attested transform view/log and private preview inputs.

```bash
scripts/repo-python scripts/replay-exact-units.py --unit sprite-transform-reset-0040fbb0
```

Full CI passes all **3,603 tests in 149.169 seconds**. Tracking, progress-card
and whitespace checks pass. `f068-evidence-check.json` verifies all prior
accepted inputs/objects/origins and active drafts unchanged. The preview object
and generated scripts/tests bytecode were removed after verification, with
hash receipts in `f068-obsolete-output-cleanup.json` and
`f068-bytecode-cleanup.json`.

The next bounded dependency is the complete polar velocity helper at
`0x0040FB70` (57 bytes, R217), then recorded range `0x00455580` and sound/shake
wrappers. F066 remains the active large caller draft. The dependency work
counts only independently cold-accepted authored functions.

## Previous accepted function: F067

`AnimationProgress40FA30::AdvanceNestedFrame`, from
`src/AnimationProgress40FA30.cpp` / `.hpp`, independently cold-replays exact at
`0x0040FA30..0x0040FABD`: **all 142 bytes**, 48 instructions, four internal
branches, two actual virtual slot-zero calls and one ret0. There are no tables
or relocations. Two following INT3 bytes before `0x0040FAC0` are excluded.
The alias preserves R103 `AnimationState::AdvanceNestedFrameAt0040FA30`;
origin classification, extent and native hash remain unchanged.

The method increments the 16-bit tick at +64, compares signed words against
+72, resets the tick and advances phase +62 when due. On wrapping it resets
phase, calls virtual slot zero and returns the **post-callback** +70 word;
on a nonwrapping advance it calls the same slot and returns post-callback +62.
Before the threshold it returns AX zero. Never cache those fields across the
callback. All 58 F066 caller sites use current; 57 consume AX with MOVSX and
the default ignores the result. The four-byte frame saves this at EBP-4.

The callback view passes only this and ignores its result, matching the
existing F008 declaration-only slot-zero view. Original callback targets,
declarations, names and complete owner layout remain unknown. Do not construct
or embed this partial receiver. No existing shared header or accepted source
was changed. All 157 prior units and canonical objects remain unchanged and
were not rebuilt.

Preview, independent canonical compilation and a separate canonical cold replay
match with VC7.1 build 3077 and `/Od /Ob0 /Gy /GR- /GX- /Zi /I src`:

```bash
scripts/repo-python scripts/replay-exact-units.py --unit animation-progress-0040fa30
```

Keep `.analysis/f067-bind.py`, both physical binding receipts,
`f067-abi-review.py` / `.json`, `f067-accepted-replay.json`, `f067-cold-replay.log`,
`f067-adoption-parent.json`, `f067-progress.json`, the private
`animation-progress-40fa30/` sources and the retained canonical cold object.
The full native export and attested view remain in `f066-callee-40fa30.asm`,
`f066-callee-views.c` and `f066-callee-decompile.log`. Historical acceptance
and detailed older investigations are preserved in the
[handoff archive](RE_HANDOFF_HISTORY.md#f065-and-pre-f066-full-draft-handoff-snapshot-2026-10-24).

## Next reconstruction: F066

Continue R048 `0x0055AC80..0x00561B8F`, historical role
`CharacterObject::AdvanceAt0055AC80`. Its **28,432 code bytes** contain 7,653
instructions, 860 internal branches, 394 direct calls to 14 callees and one
ret0. There are no indirect calls or external branch exits. The contiguous
232-byte switch table and 198-byte remap extend comparison through
`0x00561D3D`: compare **all 28,862 bytes**. Exclude only the two following INT3
bytes. The native frame is 0x19C, with ESI saved and this at EBP-24.

All **57/57 states**, entry guards and the real default now have handwritten
natural source in `.analysis/object-action-55ac80/Preview.cpp` / `.hpp` and
`states/*.inc`. `active03/` pins the complete source/header; the live object is
`build/probes/F066Preview.obj`. Never replace these with a partial switch or
blindly rerun the initial one-shot `f066-complete-fragments.py` bootstrap.
The review index pins each fragment's hash, native region and manual behavior
notes. Eight genuine loop indices explain the user locals; add no inert locals,
padding, assembly, fake results or alternate bodies to force a match.

The full caller/14-callee ABI audit checks every native instruction, all 394
calls and stack joins; wrong 16-byte effect cleanup is rejected. Thirty-four
owner-at-E4 calls comprise 25 effects, seven sounds, one gauge update and one
shake; other thiscall receivers are current. Twelve angle calls use cdecl,
two floats and ST0; 11 ftol2 uses are ordinary casts with the actual implicit
ST0-to-EDX:EAX ABI. The gauge argument is a full dword. Shake passes real 3.0f
through a setter to a field independently read by x87. Both angle origins stay
unknown. F067 now accepts only the separate frame helper, not F066 itself.

All **696 relocations** are physically bound: 394 calls, 237 readonly constants,
five existing signed-byte reads at `0x006714D0`, two table/remap addresses and
58 table destinations. Actual COFF/PE payloads, widths, permissions, addends,
operand fields and every branch/table destination are checked. Preserve the
qword double literals 0.85 in state 902 and 998.9 in state 996, exact radian
coefficient `0.01745328866f`, ordered floating comparisons, nested RNG evaluation
order and all real early exits. Original field meanings and full layouts remain
unknown; do not construct or embed any partial owner.

**F066 remains unaccepted.** The complete draft emits 28,868 bytes, six too
many, with the correct instruction count and frame. There are 976 differing
instruction encodings. The first nonbranch difference is `0x0055F711` in state
905: native loads this into ECX, the draft into EAX. Six later accumulator
encoding differences account for the extra bytes. Register classes and temporary
displacements are elided only to locate gaps; correspondence earns no exactness
or unrestricted equivalence. No F066 source-presence entry, canonical descriptor
or exact credit exists.

State 996's positive-3B6 arm must return directly to the epilogue; that genuine
exit correction makes every branch destination correspond. Integer versus
float zero spelling, chained velocity-zero initialization and state 905's
owner-failure return/break control all emit identical whole function bytes and
relocations after that correction. Retain the revision intents and binding
receipts; do not repeat these controls without new native/compiler evidence.
Use current full binding receipts, not cached pre-control diagnostic copies.

Keep `f066-native-audit.py` / `.json`, `f066-55ac80.asm`, the attested action and
callee views/logs, `f066-abi-review.py` / `.json`, dependency/consumer/global-xref
evidence, case/review indexes, `f066-native-constants.json`, state sources,
`f066-source-revisions.json`, diagnostic/binder scripts and receipts, and
`f066-progress.json`. From the repository root, after normal target preflight:

```bash
scripts/repo-python .analysis/f066-whole-diagnostic.py
scripts/repo-python .analysis/f066-bind-draft.py
```

These diagnose the retained object; they do not cold-build or accept it. A new
source revision requires serial compilation with the recorded profile, complete
physical equality and a separate canonical cold replay before any credit.
Continue native/compiler statement and temporary-lifetime investigation at
state 905, preserving all earlier exact units and pending origins.

The resumed session tested controls 04..24 without changing active03.
Nineteen controls emit identical complete patched bytes and all 696 physical
bindings: scale/color chaining, velocity commas, signed/unsigned/long constant
promotions, reversed/negated equality, double zero literals, nested guards,
expanded scale additions, statement scopes and lvalue parentheses. Both
subtract-one forms change the instruction sequence and are rejected. Do not
repeat these controls without new evidence. See `f068-f066-controls.json` and
individual source/header/intent/binding/log inputs. Removed 19 reproducible
objects / 1,119,252 bytes after full equality; five differ only in generated
local switch label names, whose offsets/addends/destinations remain identical.
All inputs, evidence, PDBs and active objects are retained.

## Other active drafts

| Cohort | Complete comparison | Active inputs and first remaining difference |
| --- | ---: | --- |
| F061 | 34,877 bytes | `.analysis/object-action-5eb520/Preview.cpp` / `.hpp`, `active07/`, `build/probes/F061Preview.obj`; draft +2 bytes, 324 instruction encodings, first nonbranch `0x005F3904` in state 998 |
| F048 | 83,922 bytes | `.analysis/character-action-4ac040/Preview.cpp`, active03 evidence, `build/probes/F048Preview.obj`; equal total size, 7,209 encodings, first `0x004ADEFA` in state 89 |
| F021 | 62,089 bytes | `.analysis/reimu/Preview.cpp` and 18 case includes; draft +1 byte, 6,311 physical operand differences, first `0x0045FDA9` in state 89 |

These are diagnostic drafts with no acceptance credit. Full ABI/CFG reviews,
controls, remaining uncertainties and retention paths are preserved verbatim in
the [archived snapshot](RE_HANDOFF_HISTORY.md#f065-and-pre-f066-full-draft-handoff-snapshot-2026-10-24).
Do not regenerate them from older initial-case generators or repeat rejected
controls without new evidence. Their active sources/objects remain unchanged.

## Cleanup and verification

Removed **five redundant objects / 335,907 bytes** after complete COFF equality:
F066 controls 01/02 have the same function and all 696 relocations as retained
active03; the F067 preview matches the canonical cold object after only the
explicit owner rename. The F048 probe-03 and F061 active07 snapshot object files
are entire-file identical copies of their retained live `build/probes/` objects.
Their sources, headers, intents and receipts remain; use the retained object
paths in `.analysis/f067-obsolete-output-cleanup.json` or rebuild a control.

Removed **375 Python bytecode cache files / 8,282,484 bytes** from `scripts/` and
`tests/` after CI. Python sources, tests and the private environment remain;
imports can regenerate caches. See `.analysis/f067-bytecode-cleanup.json`.
Total cleanup reclaimed **8,618,391 bytes (about 8.22 MiB)**. All active sources,
objects, manifests, origin evidence, PDBs and shared tools remain.

The private Wine compiler environment accounts for about 1.3 GiB of the 1.7 GiB
analysis directory. It is required tool state, not disposable game output.
Origin scans and attested exports are evidence. Do not delete either to reduce
size. Only reproducible Python bytecode caches were removed after checks.
Private `.analysis/`, `build/`, `ghidra-project/` and tools are not committed;
a new checkout alone cannot restore unaccepted drafts. Keep this workspace for
handoff. Never commit game binaries/data, archives, generated decompiles,
analysis databases, downloaded tools or secrets.

Run the [AGENTS.md](../AGENTS.md) preflight before reconstruction, then replay
only affected units. Use `scripts/repo-python` for every repository Python
command. Compiler niceness is 15; CI niceness is 10.

Full CI passes **3,603 tests in 135.949 seconds**; tracking, progress-card and
whitespace checks pass. `.analysis/f067-evidence-check.json` verifies all 157
prior unit descriptors and canonical objects, 110 prior manifest source inputs,
4,350 other function rows, 218 origin files and historical prefixes unchanged.
The previous detailed handoff is archived verbatim. F066 active03 and F061/F048
live sources/objects are pinned; F021 remains untouched. Recorded resource
samples show about 8.5 to 9.0 GiB available memory, 81–93% interval CPU idle and
zero interval swap-in/out. No compiler build or CI job remains running.
