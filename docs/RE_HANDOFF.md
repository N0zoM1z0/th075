# TH075 function reconstruction handoff

Updated 2026-10-24. The user resumed reconstruction after the cleanup/handoff
checkpoint and set an active **98% authored bytes exact** goal. The objective
is incomplete. Continue the F092 staff-roll timeline investigation below; preserve F085 and the F066 draft.
Subsequent project phases remain deferred. Use existing Ghidra/local tools,
without REA; commit subjects must use `gpt-6.1-sol: ...`. Commits and pushes
remain authorized. Keep compiler builds serial and monitor CPU/memory.

## Verified checkpoint

| Measure | Current value |
| --- | --- |
| Provisional candidates | 4,351 |
| Reviewed authored / library / compiler | 1,002 / 2,671 / 581 |
| Unknown origins | 97, totaling 3,608 bytes |
| Source-present / exact functions / exact units | 185 / 185 / 185 |
| Exact code bytes | 557,962 |
| Reviewed authored coverage | 557,962 / 1,973,516 (28.27%) |
| Conservative coverage, including every pending byte | 557,962 / 1,977,124 (28.22%) |

The ledgers and status script are authoritative. Origin evidence through R268
is unchanged. The exact-adoption manifest retains F009 and **125 additions /
548,079 code bytes / 154 new source/header inputs**. F021/F048/F061/F066/F085 remain
unaccepted. Unknown origins receive no credit and do not block independently
reviewed authored functions.

The only target is the supplied Japanese `th075.exe`, reporting version 1.11:
SHA-256 `bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
Identity is pinned to the supplied archive, without independent official
provenance corroboration. Never substitute `th075c.exe` or patch target bytes.

## Latest accepted function: F091

R001 window-mode toggle 004018A0..004019F3 is independently canonical cold exact
as `Graphics::ToggleWindowMode`: all 340 bytes, 96 instructions, six branches,
15 call packets and 32 physical fields. Twelve following INT3 bytes remain
outside the extent. One new implementation file uses unchanged headers and
existing SDK globals. The original R001 role/name stays unchanged; no alias
is needed. Its two direct calls use the unchanged accepted ResetDevice body.

The callback guard, windowed/fullscreen policy, cursor calls, exact metric-call
order and both SetWindowPos packets are preserved. SDK format values are 23
(R5G6B5) and 21 (A8R8G8B8); the first X8R8G8B8 hypothesis emitted 22 and was
rejected. Four actual metric/centering computations produce the native 16-byte
frame. The ninth GetSystemMetrics result is used to compute vertical centering
and stored at EBP-4, although the final SetWindowPos loads horizontal centering
at EBP-C for both coordinates. The source retains this observed computation
and discarded result; no spare/alignment storage or coordinate repair is added.
Original variable spelling and lexical scopes remain unknown.

Twelve bounded meaningful-name controls and a declaration-order control
preserve those four actual computations. The final screenHeight spelling and
four-variable declaration reproduce every real frame operand. A separate
standalone preview, independent canonical compile and canonical cold replay
match physically. All 32 fields bind two direct calls, thirteen named USER32
imports and seventeen existing global fields. Six real SDK member addends
(8/28 in presentation parameters and 12 in display mode) remain in the COFF;
the manifest pins their bases and cold comparison applies the actual addends.
Widths, member offsets, permissions, import names and operand positions are
checked. Every CFG/stack join and saved ESI passes; incorrect SetWindowPos-ret24
and GetSystemMetrics-ret0 controls fail. No masks, frame aliases or cropping.

```bash
scripts/repo-python scripts/replay-exact-units.py --unit graphics-window-mode-004018a0
```

All 184 old units, 89 canonical objects, 153 source/header inputs, 218 origin
files, nine shared headers, 91 active draft inputs and 4,350 other function rows
stay unchanged. No old units were rebuilt. F009 plus 125 additions retains
548,079 bytes and 154 inputs. All 97 origins remain unknown; F085 and every
older unaccepted draft receive no credit. Keep all f091 native/attested/ABI/
physical/cold/parent/progress/name-control/input/preservation evidence and
source inputs, logs and PDBs. Full CI passes **3,603 tests in 142.161
seconds**, plus target/tracking, progress and whitespace checks. Removed six
obsolete reproducible probe/control objects (89,120 bytes) and
scripts/tests bytecode (8,282,705 bytes), after whole final-preview/
cold-canonical code and all 32 relocation equality. All sources, inputs, logs,
PDBs, evidence and canonical objects remain.
Next F092: full 4,749-byte R043 StaffRollScene::RenderTimeline at 00438D00.
Fresh native/attested root/callee/caller records reconcile 1,215 instructions,
48 branches and 61 direct call sites to seven complete callees: accepted
BeginFrame/EndFrame, three texture-state setters, DrawSprite and ftol2. There
are 47 sprite calls and six implicit-ST0 conversions. DrawSprite has nine real
arguments: texture index, x/y floats, DWORD color, two pivot floats, scale float,
angle float and one byte of flags (36 stack bytes). Reconcile all timeline
paths, signed float conversions and actual packets before source. No F092
source, build, unit or credit yet.
Goal 98% remains active and incomplete.

## Previous accepted function: F090

R015 held-input update00406E80..00407164 is independently canonical cold exact
as `InputMapping4388D0::UpdateHeldCounts`: all741 bytes,211 instructions,
36 branches,five real call packets and15 physical fields. Eleven following
INT3 bytes stay outside the complete extent. Only one new implementation file
is added; its existing F089 partial receiver/header stays unchanged,so no old
units were rebuilt. The first natural probe matches physically.

The signed device selector chooses joystick or keyboard. X/Y counters preserve
-500/+500 thresholds,opposite-sign resets,decrement/increment and idle zero.
Both five-button loops retain their genuine independent indices in the12-byte
frame. Existing real std::vector<DIJOYSTATE> and keyboard-buffer declarations
remain unchanged. Five vector subscripts receive ECX671358 and the signed byte
at owner+4 promoted into one four-byte argument; their returned references and
RET4 agree with the actual49-byte vendor helper. All CFG/loop joins and wrong
0/8-byte cleanup controls pass. No inert storage,layout growth or aliases.

Every field binds independently:five subscript calls,five existing joystick
receiver immediates,five indexed keyboard-buffer accesses. The generated49-byte
vendor subscript also matches physically after binding all three iterator-family
calls at404590/404740/404720. This is diagnostic dependency evidence only;
R003 library ownership/exclusion and zero authored credit remain unchanged.
All original owner/type names,complete scene/mapping layouts and lexical scopes
remain unknown; the pointer-only receiver must not be instantiated or embedded.

```bash
scripts/repo-python scripts/replay-exact-units.py --unit input-held-counts-00406e80
```

All183 old units,88 canonical objects,152 source/header inputs,218 origin files,
nine shared headers,91 active draft inputs and4,350 other function rows remain
unchanged. F009 plus124 additions retains547,739 bytes and153 new inputs. All97
pending origins remain unknown; F085 and all older large drafts receive no
credit. Preserve f090 full native/root/callee/caller/attested/ABI/physical/cold/
parent/progress/compiler-input/preservation evidence and all inputs/logs/PDBs.
Full CI passes **3,603 tests in131.152 seconds**, plus target/tracking,
progress and whitespace checks. Removed one obsolete reproducible probe object
(17,450 bytes) and scripts/tests bytecode(8,282,705 bytes),
after whole preview/cold code and all15 relocation equality. All source/control
inputs,logs,PDBs,evidence and canonical objects remain.
## Previous accepted functions: F089

R043 input poll004388D0..00438A29 (346 bytes) and R015 key query00407170..
00407195 (38 bytes) independently pass canonical cold comparison as
`SelectionInput4388D0::PollInput` and `InputMapping4388D0::IsKeyDown`.
Six/ten following INT3 bytes remain outside the whole extents. The two natural
source bodies share one new source/header and one serial cold object build.
Only these new units were rebuilt. No accepted headers changed.

The input poll's101 instructions/ten branches/eleven actual call packets and
all27 physical fields match. It preserves both complete seven-dword physical
copies,mode!=3 polling,short-circuit Enter/Alt key tests,the5/1/3 mode filter,
signed active-side selection/threshold,input transfer/reset and hold counter.
The28-byte block names express complete copied storage,without establishing
complete scene/mapping layouts or original member partition. Both copied
subregions coincide with the respective input-mapping receivers+2C. All seven
slots are used by the actual complete REP MOVSD operations.

The key query has14 instructions/two branches/one field. Its actual receiver
is in ECX,one unsigned-byte argument occupies a four-byte stack word,AL carries
a bool and RET4 consumes that argument. Explicit natural if/else returns give
the complete38 bytes; the earlier boolean-expression form has35 bytes and gets
no credit. The existing keyboard buffer declaration remains unchanged.

Seven whole callees are reviewed. Memcpy's829-byte R025 auxiliary extent has
embedded dispatch tables and46 relocation fields; its674-byte linear decoded
prefix is not its complete CFG. Preserve the whole pinned vendor-body evidence.
Cdecl memcpy/memset each use12 argument bytes with explicit caller cleanup;
other calls consume0/4 as observed. Saved ESI/EDI,all CFG stack joins,two28-byte
copies and incorrect key-ret0/runtime-ret12 controls are checked. All28 fields
across both accepted functions bind independently; no masks,aliases or cropping.
New global views establish addresses and physical subregions,not data ownership
or complete original types. Pointer-only owner interfaces must not be constructed.

```bash
scripts/repo-python scripts/replay-exact-units.py --unit select-input-004388d0 --unit input-key-down-00407170
```

All181 old units,87 canonical objects,150 source/header inputs,218 origin files,
nine shared headers,91 active draft inputs and4,349 other function rows remain
unchanged. F009 plus123 additions retains546,998 bytes and152 source/header
inputs. All97 origins remain unknown; F085 and every older large draft receive
no credit. Keep all f089 native/root/callee/caller/attested/ABI/physical/cold/
parent/progress/compiler-input/preservation evidence,source inputs,logs/PDBs.
Full CI passes **3,603 tests in131.440 seconds**, plus target/tracking,
progress and whitespace checks. Removed two obsolete reproducible probe objects
(21,407 bytes) and scripts/tests bytecode(8,282,705 bytes),
after full preview/cold code and relocation equality for both accepted functions.
All canonical objects,source/control inputs,logs,PDBs and evidence remain.
## Previous accepted functions: F088

R041 single-player options00438670..004388C3 (596 bytes) and R043 selected-card
value00438A80..00438AB4 (53 bytes) are independently canonical cold exact as
`SinglePlayerOptions438670::RenderOptions` and
`ProgressCard438A80::GetSelectedValue`. The following twelve/eleven INT3 bytes
stay outside their complete extents. One handwritten source body per function,
one shared source/header and one serial object build feed two whole comparisons.
No accepted headers changed and no old units were rebuilt.

The renderer's149 instructions/two branches/21 real call packets and all25
physical fields match. A signed scene-byte guard skips all packet construction;
the 132-byte packet, inner RECT and all168 frame bytes match naturally on the
first probe. Four drawings use this+8 with texture6; signed EC is converted to
float for the cursor. The six complete direct callees are reviewed. Fields
bind17 direct calls,four named SetRect imports and four existing g_BattleRecords
receiver immediates. No receiver extent or data ownership is inferred.

The whole15-instruction getter reads signed selectors at16AC4/16AC5, uses
strides17F0/5FC and returns byte556 in AL. Its four renderer calls receive only
ECX and consume zero stack bytes, including two calls preserving two already
pushed SetRect/BuildQuad argument words. Signed-char return semantics match the
actual MOVSX consumers. No fabricated parameters or complete records layout.
Both owner views remain pointer-only. Every branch/exit stack join passes;
wrong getter-ret4 and SetRect-ret16 controls fail. No masks, aliases or truncation.

```bash
scripts/repo-python scripts/replay-exact-units.py --unit single-player-options-00438670 --unit progress-card-value-00438a80
```

All179 old units,86 canonical objects,148 source/header inputs,218 origin files,
nine shared headers,91 active draft inputs and4,349 other function rows remain
unchanged. F009 plus121 additions retains546,614 bytes and150 source/header
inputs. All97 origins remain unknown. F085 and every older large draft receive
no credit. Keep f088 native/root/callee/caller/attested/ABI/physical/cold/parent/
progress/compiler-input/preservation evidence,complete input sources,logs/PDBs.
Full CI passes **3,603 tests in140.235 seconds**, plus target/tracking,
progress and whitespace checks. Removed one obsolete reproducible probe object
(11,062 bytes) and scripts/tests bytecode(8,282,705 bytes),
after whole code and relocation equality for both preview/cold functions. All
source/input/log/PDB/evidence records and canonical objects remain.
## Previous accepted function: F087

R041 player options 00438240..0043866F is independently cold-replay exact as
`CharacterSelectOptions438240::RenderOptions`: all 1,072 bytes, 255 instructions,
six branches, 30 physical fields and 25 actual call packets. The next function
begins immediately at00438670. The complete five direct callees, six named
SetRect calls and signed/unsigned byte operations are reviewed. The source keeps
the two-side loop and disabled-side continue, five drawings through this+8 and
one mode-dependent drawing through this+44. Integer-to-float spills remain real
conversions. The 132-byte packet lives outside an inner RECT/for scope; the
whole 192-byte frame follows naturally, without inert locals or padding.

Three bounded source scopes produced 1,033 bytes, then 1,072 bytes with thirty
actual frame-byte differences, then complete physical equality. All 30 fields
bind nineteen direct calls, six imports, one existing mode global and four
indexed fields at671434/671438. The former is read signed and the latter
unsigned, both indexed by the actual side loop. New extern arrays have unknown
bounds: no original allocation, data ownership or declaration is inferred.
All branch/loop joins and call cleanups are checked; deliberately incorrect
SetRect and translation cleanup controls fail. No aliases, masks or shortened
comparison. The incomplete owner is pointer-only and must not be instantiated.

```bash
scripts/repo-python scripts/replay-exact-units.py --unit character-select-options-00438240
```

All 178 previous units, 85 canonical objects, 146 source/header inputs, 218
origin files, nine shared headers and 91 active draft inputs stay unchanged.
Only this new unit was cold replayed. F085's complete unaccepted draft and all
older large drafts remain protected; the 97 unknown origins receive no credit.
F009 plus 119 additions retains 545,965 bytes and 148 new source/header inputs.
Keep f087 native/root/callee/caller/attested/ABI/physical/cold/parent/progress/
compiler-input/preservation evidence, probe inputs, logs and PDBs. Full CI passes **3,603 tests in 163.326 seconds**, plus tracking,
progress and whitespace checks. Three obsolete reproducible F087 probe objects
(33,643 bytes) and scripts/tests bytecode (8,282,705 bytes)
were removed after whole preview/cold-canonical code and relocation equality.
All source/input/log/PDB/evidence records and canonical objects remain.

## Previous accepted function: F086

R043 character cards 00437380..00438238 cold-replay exact as
`CharacterSelectCards437380::RenderCards`: all 3,769 bytes, 825 instructions,
fifty branches, 58 physical fields and 41 real call packets. Seven following
INT3 bytes are excluded. Six complete direct callees and twelve named SetRect
calls are reviewed. The preserved F085 caller supplies one ECX owner and no
stack arguments; the complete private owner layout and original names remain
unknown. Never instantiate or embed this partial owner.

The complete handwritten body keeps the actual two-side loop, independent
mode-3/mode-4 side-1 breaks and signed-short badge continue path. Both tint
arrays contain exactly two used entries. The full 132-byte F064 packet and one
SDK RECT are constructed/reused. Ordered angle<=15/<=45 arms, byte truncation
before integer division in the third arm, bool*128/bool*96 atlas arithmetic,
shared ARGB stores, rotation, twelve translations and all nine drawings remain.
No array growth, inert locals, padding, fake returns or assembly.

Six full-body scope controls and eight meaningful index/normal/for-declaration
controls resolve the initial 181 differing frame bytes. The final source gives
normal[2] its per-pass scope, RECT its drawing scope, int i the for declaration,
alpha/color/atlas values their per-iteration scope and the short its actual
badge branch. The complete 228-byte frame, comparison temporaries and genuine
conversion slots match naturally. This is compiler evidence, not proof of
original variable spelling or lexical scopes.

Standalone preview, independent canonical compilation and separate canonical
cold replay match every byte with build3077 and the explicit profile. All 58
fields bind 29 direct calls, twelve named imports, fifteen readonly float
fields and two reads of the unchanged signed mode global. Widths, payloads,
permissions, zero addends, operand positions, imports, every branch and all
loop/continue/break stack joins are checked. The three implicit ftol2 calls
consume ST0 without invented C parameters; wrong ftol2/SetRect cleanup controls
fail. No branch masks, frame aliases or shortened comparison.

All 177 previous units, 84 canonical objects, 144 prior manifest inputs, 218
origin files, 4,350 other function rows and 91 active draft inputs remain
unchanged and were not rebuilt. The latter includes seven protected F085
source/object/ABI/physical/preservation records as well as all 84 older draft
inputs. Every accepted header stays fixed; all 97 pending origins remain
unknown. F009 plus 118 additions retains 544,893 bytes and 146 new source/header
inputs. F085 receives no exact credit. The active 98% goal remains incomplete.

```bash
scripts/repo-python scripts/replay-exact-units.py --unit character-select-cards-00437380
```

Full CI passes **3,603 tests in 131.386 seconds**, plus tracking, progress
and whitespace checks. The indentation-only source cleanup was cold replayed
again; all seven checkpoint guards pass against the final source and manifest.
Keep f086 native/root/callee/caller/attested/ABI/physical/cold/parent/progress/
preservation evidence and complete compiler-control source/profile/result/
input/log/PDB records. Four obsolete reproducible F086 objects and
scripts/tests bytecode were removed after full preview/cold-canonical code and
relocation equality. Every canonical object, F085 active object, source/control
input, PDB, evidence file, older active draft and shared tool remains.

## Preserved unaccepted function: F085

The complete handwritten R040 00435A70..00437373 draft is retained privately in
`.analysis/render-background-435a70/Preview.cpp` and Preview.hpp; its active
object is build/probes/F085Preview01.obj. All 6,404 bytes, 1,471 instructions,
nineteen branches and 124 real calls are reconciled. All 235 physical fields
bind independently: 99 direct calls, 25 named SetRect imports, 103 readonly
float fields and eight fields at three writable globals. Complete call packets,
21 implicit conversions and two nested scalar calls pass the full stack graph.
The runtime/wrapper proof and complete 132-byte physical packet model are reused
unchanged, without helper, data or unknown-origin credit.

The raw fully relocated comparison retains 115 real byte differences, all at
four real locals: draft/native left tint -158/-144, right tint -137/-143,
stage -157/-137 and RECT -156/-160. No aliases, branch masks or truncation are
used. Whole-body meaningful-name/lifetime/real-storage/type/init controls and
/G5,/G7 probes are retained; /G5 is code/relocation equal, /G7 has the wrong
size/instruction/field counts. Best alternative real two-byte aggregate retains
61 differences and still earns no credit. Do not repeat these unchanged
controls or grow arrays/add storage/alignment merely to fill the observed gaps.

Read-only PE/Ghidra references show its slot-2 virtual entry at00658254, in the
three-entry table beginning0065824C (438A30 deleting destructor,433470 Advance,
435A70 render). The adjacent `data\system\selectbg.dat` path and reviewed helpers support
character-selection context; original class identity/layout and nominal private
declarations remain unknown. Virtual and one-ECX-argument views did not resolve
the frame difference and are diagnostic only. Existing R040 ledgers/names remain
unchanged. No canonical F085 source, match unit, source-present or exact credit.

Keep the f085 full source/headers, native/decompile/attestation, ABI/physical,
vtable/xref and all control input/result/log/PDB evidence, including
`.analysis/f085-draft-relocation-bindings.json`, f085-abi-notes.json and
f085-output-cleanup.json. Twenty-one completed reproducible control objects
were removed after pinning inputs/results; the active draft object and all
older accepted objects/drafts/shared tools remain. Return when new source,
compiler or lifetime evidence is available. Continue the independently reviewed
cohort above while preserving the full 98% objective and conservative denominator.

## Previous accepted function: F084

R041 combo counter 0043D570..0043D9CA cold-replays exact as
`HudCombo43E040::Render`: all 1,115 bytes, 272 instructions, nine branches,
33 physical fields and thirteen actual call packets. Five subsequent INT3
bytes are excluded. The complete five direct callees and USER32!SetRect are
reviewed. The existing F075 HUD declaration and caller remain unchanged.

One handwritten thiscall body retains the unsigned alpha and signed-short hit
guards, actual short copy/cap99, signed-byte side test, both placements,
repeated x87 offset/color/number operations and genuine timer updates. The
short countdown decrement uses its observed 16-bit operation; unsigned alpha
subtraction preserves the actual byte wrap and <=5 zero test. No new range
guards or clamping are introduced. Motion uses the real integer spill and
unchanged CameraSineAt0040D940(float/ST0) view, including negation before *200.

Nineteen whole-function meaningful-name/simple-lifetime controls retain the
initial 1,106-byte class/RECT ordering. Four nested-rectangle scope controls
reproduce the entire target. The final body keeps the real short count and
complete 132-byte packet outside the rectangle drawing scope, with the actual
168-byte frame and conversion slot. No padding, inert local, frame alias,
branch mask or shortened extent. Original local spelling/scope and complete
private owner layout remain unknown. The partial HUD owner is pointer-only;
only the complete F064 packet and SDK rectangle are constructed.

Both whole 17/28-byte sine wrappers agree with the retained R163 SDK and
ordinary C++ controls. The full R128 174-byte runtime parent, 13-byte auxiliary
and frozen runtime/dispatch graphs are reused; the nine-byte C entry is an
interior label, not a complete implementation. Original wrapper ownership and
nominal return precision/type remain unknown. Both wrappers and all 97 pending
origins stay unchanged. No runtime, dependency or data exact credit is added.

Independent canonical compilation and separate canonical cold replay match
every byte with build3077 and the explicit profile. All 33 fields bind twelve
direct calls, twenty readonly float fields and one named import. Zero addends,
operand positions, payloads, widths, permissions, import identity and all nine
branches are checked. Whole CFG stack joins and the actual 0/16/20-byte callee
cleanup or 4/16/20-byte caller cleanup pass; wrong draw/SetRect controls fail.
All 176 prior units, 83 canonical objects, 143 previous manifest inputs, 218
origin files, 4,350 other function rows and 84 active draft inputs remain
unchanged and were not rebuilt. Every accepted header stays fixed. F009 plus
117 additions retains 541,124 bytes and 144 new source/header inputs. The
98% goal remains incomplete.

```bash
scripts/repo-python scripts/replay-exact-units.py --unit battle-combo-counter-0043d570
```

Full CI passes **3,603 tests in 121.179 seconds**, plus tracking, progress
and whitespace checks.
Keep f084 native/root/callee/caller/math/attested/ABI/physical/cold/parent/
progress/preservation evidence, all full compiler-control input snapshots,
profiles, results, scripts, logs and PDBs. Four obsolete reproducible objects and
scripts/tests bytecode were removed after complete preview/cold-canonical
code and relocation equality. Canonical objects, evidence, source/control
inputs, PDBs, all older active drafts and shared tools remain.

The F085 unaccepted draft, subsequent F086 acceptance and current F087 cohort
are recorded above. F085 receives no exact credit.

## Previous accepted function: F083

R011 rectangle constructor 0040DA00..0040DB02 cold-replays exact as
`AtlasQuad446B90::AtlasQuad446B90`: all 259 bytes, 93 instructions and nine
physical call fields. Its RET16 occupies 0040DB00..0040DB02; all three bytes
are included. Thirteen subsequent INT3 bytes are excluded. Three complete
callees account for four zero-argument coordinate constructions, one payload
construction and four four-float temporary coordinate constructions.

The natural constructor body assigns first/second/third/fourth from ordinary
D3DXVECTOR4 temporaries using the real left/top/right/bottom arguments and zero
z/w. Compiler-generated member construction, four real 16-byte temporaries,
returned EAX addresses and ordinary member assignments reproduce the entire
68-byte frame and all moves. Final EAX=this and RET16 follow normal constructor
ABI; no explicit return, padding, inert local or assembly is introduced.

The accepted F082 complete physical packet view and unchanged F064 constructor/
33-dword-copy/consumer witness graph support sizeof132 and payload offset64.
The complete packet is constructible; original class identity, payload partition
and nominal declarations remain unknown. Both 14-byte default helpers stay
unknown-origin. No helper/data bytes or original SDK identity receive credit.
All 97 pending origins remain unchanged.

An independent canonical compilation and separate canonical cold replay match
the full body with the explicit build3077 profile. All nine REL32 fields bind
at the actual call operand positions, with zero addends and executable targets.
The entire stack graph and all receiver/argument/result uses are checked; wrong
default-ret4 and temporary-ret12 controls fail. No frame aliases, branch masks
or shortened extent. A separate translation unit reuses the F082 header without
changing it or rebuilding the unchanged number renderer. All 175 prior units,
82 canonical objects, 142 previous manifest inputs, 218 origin files, 4,350 other
function rows and 84 active draft inputs remain unchanged. F009 plus 116
additions retains 540,009 bytes and 143 new source/header inputs. The active
98% goal remains incomplete.

```bash
scripts/repo-python scripts/replay-exact-units.py --unit atlas-quad-rectangle-constructor-0040da00
```

Full CI passes **3,603 tests in 118.809 seconds**, plus tracking, progress and
whitespace checks.
Keep f083 native/root/callee/caller/attested/ABI/physical/cold/parent/progress/
preservation evidence and the full f082 natural constructor/model probe inputs,
profile, results, logs and PDBs. The now-obsolete reproducible constructor probe
object and scripts/tests bytecode were removed after complete code/relocation
equality with the cold canonical object. All evidence, input sources, profiles,
PDBs, canonical objects, older active drafts and shared tools remain.

The subsequent F084 acceptance and current F085 cohort are recorded above.

## Previous accepted function: F082

R042 number worker 00446B90..00446D5E cold-replays exact as
`DrawAtlasNumberAt00446B90`: all 463 bytes, 129 instructions, ten branches,
13 physical fields and five real call packets. One following INT3 byte is
excluded. All three direct callees are reviewed over their complete extents.

The handwritten cdecl body preserves six real parameters, signed-byte style,
negative-number early return, the actual boolean texture-bank expression,
working number, signed division/modulo by ten, the positive fixed-digit loop
and alternate sentinel loop. Real parameter decrements, four integer-to-float
spills and the final per-digit translation remain. Twenty-one complete probes
vary meaningful local names or drawing scope. Only textureIndex to textureId is
needed for the actual remaining-4, packet-90, textureId-94 allocation, 164-byte
frame and saved ESI. This is compiler evidence, not original spelling evidence.

A separate full natural rectangle-constructor probe matches all 259 bytes and
nine actual relocations at 0040DA00. It corroborates the unchanged F064 complete
132-byte packet model: four SDK coordinate records and a constructed 68-byte
payload, plus complete constructor/copy/consumer witnesses. The new physical
packet view guards sizeof132/offsetof64 and preserves the real constructor
lifetime. Original class identity and payload partition remain unknown; no
partial owner is constructed or embedded. Every accepted shared header stays
fixed, including the earlier zero-argument packet interface.

Five inferred writable global access views cover signed-short advance/height/
width, COM texture pointers and RECT rows of ten/stride160. All eight indexed
fields have their actual widths, scales, base/index registers and permissions
checked. Outer extents, original declarations/names and data ownership remain
unknown. No data or dependency bytes receive exact credit. The two 14-byte
constructor dependencies remain unknown; all 97 pending origins stay unchanged.

Preview, independent canonical compile and separate canonical cold replay
match every byte with build3077 and the explicit profile. All five direct-call
fields and eight indexed globals bind with zero addends; no frame aliases,
branch masks or extent truncation. Whole CFG stack joins and actual 16-byte
constructor, 12-byte translation and caller-cleaned 16-byte draw packets pass.
Wrong draw/translation cleanup controls fail. All 174 prior units, 81 canonical
objects, 140 previous manifest inputs, 218 origin files, 4,350 other function
rows and 84 active draft inputs remain unchanged and were not rebuilt. F009
plus 115 additions retains 539,750 bytes and 142 new source/header inputs.
The 98% goal remains incomplete.

```bash
scripts/repo-python scripts/replay-exact-units.py --unit battle-atlas-number-00446b90
```

Full CI passes **3,603 tests in 122.452 seconds**, plus tracking, progress and
whitespace checks.
Keep f082 native/attested/root/callee/caller/ABI/packet/physical/cold/parent/
progress/preservation evidence, all compiler-control sources, profiles, logs,
results, input snapshots and PDBs. Three obsolete reproducible objects and scripts/tests
bytecode were removed after input pinning and whole-preview code/relocation
equality with the cold canonical object. The constructor probe object remains
for F083; canonical objects, PDBs, evidence, old drafts and shared tools remain.

The subsequent F083 acceptance and current F084 cohort are recorded above.

## Previous accepted function: F081

R045 round banner 00441EA0..00441FCE cold-replays exact as
`BattleRoundBanner441EA0::RenderRoundBanner`: all 303 bytes, 78 instructions,
two branches, seven physical fields and seven real call packets. One following
INT3 byte is excluded. Six complete direct callees and USER32!SetRect are checked.
The accepted F074 caller supplies this with no stack arguments.

The body preserves one complete 132-byte packet, initial FF opacity store,
actual >50 branch ordering, unsigned-byte truncation before integer +1, repeated
ARGB construction and the integer-to-float coordinate spill. Outer opacity and
packet lifetime plus the inner count/RECT drawing scope reproduce the native
172-byte frame. Seventeen full-body meaningful-name/scope controls isolate this
layout; changing the real digit byte's name to count resolves the remaining four
frame fields. Original spelling/scope remains unknown; no padding or inert locals.
Accepted shared headers remain unchanged; no partial owner is constructed.

The complete 28-byte 00442040 scalar wrapper widens its float32 argument to
a double64 stack argument for the frozen R130 log10 runtime. Its FST32 leaves
ST0 live for the caller's implicit ftol2 conversion after caller cleanup. The
float declaration is a compatible access view; original nominal precision/type
remains unknown. The wrapper stays unknown-origin and receives no credit.
The complete 63-byte library own code, 336-byte source/auxiliary carrier and
644-byte optimized body are checked against retained R130 hashes; unchanged
origin proofs are not rebuilt. All 97 pending origins remain unknown.

Preview, independent canonical compile and separate canonical cold replay match
every byte with build3077 and the explicit profile. Six direct-call fields and
one named import bind with zero addends, exact operand positions, permissions
and import identity. Whole CFG stack joins pass; wrong SetRect/ftol2 cleanup
controls fail. All 173 prior units, 80 old canonical objects, 138 previous source
inputs, 218 origin files, 4,350 other function rows and 84 active draft inputs
remain unchanged and were not rebuilt. F009 plus 114 additions retains 539,287
bytes and 140 new inputs. The 98% goal remains incomplete.

```bash
scripts/repo-python scripts/replay-exact-units.py --unit battle-round-banner-00441ea0
```

Full CI passes **3,603 tests in 127.600 seconds**, plus tracking and progress.
Whitespace-only source formatting was cold-replayed again; all seven checkpoint
guards pass against the final source and manifest.
Keep f081 native/attested/root/callee/caller/math/ABI/physical/cold/parent/progress
and preservation evidence, all natural compiler-control source/profile inputs,
results, logs and PDBs. Three obsolete reproducible objects and scripts/tests
bytecode were removed after input pinning and whole-preview code/relocation equality with the cold
canonical object. Canonical objects, PDBs, evidence, old drafts and shared tools
remain.

The subsequent F082 acceptance and current F083 cohort are recorded above.

## Previous accepted function: F080

R042 damage flash 004406C0..00440AF8 cold-replays exact as
`BattleDamageFlash4406C0::RenderFlash`: all 1,081 bytes, 292 instructions,
20 branches, 46 physical fields and 23 real call packets. Seven following INT3
bytes are excluded. Five complete direct callees and two USER32!SetRect calls
are checked. The accepted F074 caller supplies this with no stack arguments.

The full handwritten body retains two explicit actor paths, frame/state/timer
checks, actual ordered height comparison and the native color-branch order.
One real byte component, color, shared RECT and two float view snapshots are
preserved. Twelve implicit ftol2 calls consume ST0; coordinate conversions keep
zero/one/two/three pending outer SetRect words. The actual integer direction*
timer*4 contribution uses the native spill and FIADD. Both rectangle draws and
real top+=3/bottom+=1 changes remain. No fake C parameters or return values.

Both complete 58/56-byte state predicates return AL0/1 and ret0. The accepted
IsState50To149 interface is reused unchanged; the second predicate has a new
pointer-only AL view and receives no exact credit. The old writable float globals
g_CombatViewOffsetX/Y are reused without header changes. Original names, nominal
private declarations and full owner layouts remain unknown. Only SDK RECT is
a constructible local; partial owners are never constructed or embedded.

Bounded controls over meaningful names of five real locals resolve the native
60-byte frame, including six genuine integer-conversion slots. The final names
screenY/x retain all other source operations. Controls are diagnostic compiler
observations, not original spelling evidence. Preview, independent canonical
compile and separate canonical cold replay match every byte with build3077 and
the explicit profile. All 46 fields bind 21 direct calls, 21 readonly float fields,
two writable global fields and two named imports. Widths, payloads, zero addends,
permissions, imports, every branch and whole CFG stack joins are checked;
wrong SetRect/ftol2 cleanup controls fail.

All 172 prior units/objects, 136 previous manifest inputs, 218 origin files,
4,350 other function rows and 84 active draft inputs remain unchanged and were
not rebuilt. All 97 pending origins remain unknown. F009 plus 113 additions
retains 538,984 bytes and 138 new source/header inputs. The 98% goal is incomplete.

```bash
scripts/repo-python scripts/replay-exact-units.py --unit battle-damage-flash-004406c0
```

Full CI passes **3,603 tests in 132.728 seconds**, plus tracking, progress and
whitespace. Keep f080 native/root/callee/caller/attested/ABI/physical/cold/parent/
progress/preservation evidence and all compiler-control input/results/logs.
Seven obsolete reproducible objects were removed after pinning source/profile
inputs and final-preview whole code/46-relocation equality with the cold canonical
object. PDBs, sources, evidence, canonical objects, prior active drafts and shared
tools remain. Scripts/tests bytecode was removed after CI.

The subsequent F081 acceptance and current F082 cohort are recorded above.

## Previous accepted function: F079

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

The subsequent F080 acceptance and current F081 cohort are recorded above.

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
