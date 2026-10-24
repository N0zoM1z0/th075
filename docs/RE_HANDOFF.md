# TH075 function reconstruction handoff

Updated 2026-10-25. The user resumed reconstruction after the cleanup/handoff
checkpoint and set an active **98% authored bytes exact** goal. The objective
is incomplete. Continue the F124 scene-drawing investigation below; preserve F085 and the F066 draft.
Subsequent project phases remain deferred. Use existing Ghidra/local tools,
without REA; commit subjects must use `gpt-6.1-sol: ...`. Commits and pushes
remain authorized. Keep compiler builds serial and monitor CPU/memory.

## Verified checkpoint

| Measure | Current value |
| --- | --- |
| Provisional candidates | 4,351 |
| Reviewed authored / library / compiler | 1,002 / 2,671 / 581 |
| Unknown origins | 97, totaling 3,608 bytes |
| Source-present / exact functions / exact units | 275 / 275 / 275 |
| Exact code bytes | 672,654 |
| Reviewed authored coverage | 672,654 / 1,973,516 (34.08%) |
| Conservative coverage, including every pending byte | 672,654 / 1,977,124 (34.02%) |

The ledgers and status script are authoritative. Origin evidence through R268
is unchanged. The exact-adoption manifest retains F009 and **215 additions /
662,771 code bytes / 190 new source/header inputs**. F021/F048/F061/F066/F085 remain
unaccepted. Unknown origins receive no credit and do not block independently
reviewed authored functions.

The only target is the supplied Japanese `th075.exe`, reporting version 1.11:
SHA-256 `bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
Identity is pinned to the supplied archive, without independent official
provenance corroboration. Never substitute `th075c.exe` or patch target bytes.

## Latest accepted functions: F123

Eight independently authored R049 command-poll routines pass canonical cold
comparison: **8,285 code bytes,2,385 instructions,211 actual calls and all422
real relocation fields**. Every own complete CFG,4byte this-only frame,
plain RET, shared exit, stack join and following INT3 is checked. There are
no tables or cropped tails. One new source/object contains eight natural
if-else bodies, with all original per-character ordering retained:

| Entry | Code bytes | Ordered decisions |
| --- | --- | --- |
| 004724B0 | 982 | 25 |
| 00498BE0 | 1,099 | 28 |
| 004C6700 | 1,099 | 28 |
| 004E7A00 | 982 | 25 |
| 00556FA0 | 982 | 25 |
| 00579220 | 1,060 | 27 |
| 0059CDA0 | 1,177 | 30 |
| 005C5980 | 904 | 23 |

Every native true edge stores its own command and exits. Every false edge
continues to the next ordered packet or final shared exit. All211 actual this
receivers, three-word packets, signed AL tests, literal bytes/counts/windows/
command assignments and initial command0 are independently reconciled.
The complete695byte helper confirms signed byte arguments, RET12 and actual
AL values including4. Source uses a signed-byte result, without guessed BOOL
or leftover-register return. Original strings remain unchanged.

The natural bodies have no named local beyond this and no aggregate/array/
loop/table replacing the actual decisions. Private owner declarations remain
pointer-only; none is instantiated or embedded. The first preview and canonical
object match every whole byte and real field. Five wrong real helper or
string bindings each reject all eight whole units. No name fixture, extra
storage/scope/padding, pasted decompiler body, native-code array, assembly,
manual EH, fake return, ABI alias, relocation mask or truncated comparison is
used. Original identities, names, full layouts and unproved types remain
provisional; no helper/library/global/data/layout receives credit.

Cold replay selected only the eight `character-input-ADDRESS` units above;
one canonical object was built. All267 prior units,121 canonical objects,
189 source inputs,218 origin files,nine shared headers,91 active drafts and
4,343 other function rows remain unchanged. F009 plus215 additions retains
662,771 code bytes and190 new inputs. R049 historical roles remain through
aliases, all97 unknown origins remain unknown. Preserve all f123 complete
native/attested/policy/CFG/receiver/byte-result/ordered-decision/string/binding/
cold/parent evidence, first preview, source, results, logs and PDBs.

Current totals: **275 exact functions/units,672,654 code bytes**,34.08% of
reviewed authored bytes and **34.02% conservatively**, including every pending
byte. The98% goal remains active and incomplete.

Validation:3603 CI tests passed in161.764s; seven exact-checkpoint tests
passed in0.529s; target/tracking and diff checks passed. Only eight new units
were cold-built. Evidence-preserving cleanup removed one obsolete own probe
(26,274bytes) and375 reproducible Python bytecode files(8,282,863bytes),
retaining all canonical objects, native/policy/CFG/receiver/string/binding/cold/
parent evidence, first preview, source, results, logs and PDBs. Receipts are
`.analysis/f123-{final-compiler-inputs,object-cleanup,preservation-cleanup}.json`.

## Current reconstruction cohort: F124

Review the complete independently authored scene drawing candidates:
SceneRenderer::DrawAt004292E0 `004292E0/2759` and
ReplayBrowserScene::RenderList `0042CA60/2246`, total5,005 code bytes.
Reconcile each full native CFG, code/table/tail extent, real return/stack/FPU
carrier, local-value contract, field widths and helper receivers/packets
before source. Accepted SDK-based quad/RECT contracts supply methodology;
they do not prove a private scene/container/row layout or automatic clone.
Preserve every genuine native drawing and update order, original string and
unproved declaration. Never instantiate or embed incomplete owner views.

Native-only F124 exports under `.analysis/f124-scene-drawing/` retain
attested function/callee/decompile results and both whole native spans. R065
004292E0 linearly decodes675 instructions/79 calls, actual frame172bytes;
R040 0042CA60 decodes546/49, actual frame240bytes plus savedESI. These are
preliminary observations, not accepted CFG/local-value/type/source evidence.
004292E0 owns a four-target16byte table at00429DA7 immediately after its RET;
its full comparison must include2,759code+16table bytes, then nine INT3 bytes.
The dispatch reads the signed global difficulty byte at006714D0. Do not crop
this table or trust the decompiler to establish complete source/local layouts.

Keep all accepted source/header inputs and unaccepted F021/F048/F061/F066/F085
drafts and failed controls. No unchanged retries or relaxed physical comparison.
Unknown math overloads and all97 unknown origins remain unknown; evidence
throughR268 is immutable. The F119 row projection is never an allocatable
complete private owner. QueueFile00407A50/QueueArchiveEntry00407B80 still need
a proved complete local record layout; resource root00456B60 retains f107's
real588byte frame and unresolved texture80/layout/filename bound. Build
serially; cold-replay only new/affected units and remove only obsolete
reproducible outputs while retaining inputs/evidence. Later phases deferred.

## Previous accepted functions: F122

Nine individually reviewed R049 stage renderers pass canonical cold comparison:
`00471E00`, `00498540`, `004C6050`, `004E7350`, `00531570`, `005568F0`,
`00578B70`, `0059C6F0`, `005C52D0`. Each has1,584 code bytes and22 owned
dispatch bytes: **14,256 code +198 table bytes,3,177 instructions,243 actual
calls and all360 real relocation fields**. One new natural template source
uses nine distinct policy types naming observed offsets; no private owner
is instantiated or embedded. Each own160byte frame, RET4, signed stage byte,
complete ESP/EBP/x87 CFG joins, shared exit, three-target12byte table and ten
selectors are checked independently. Ten following INT3 bytes remain outside
each extent. Every table/selector field and byte is included in comparison.

Before source, every actual native instruction operand was reconciled with
explicit own field/table differences; none was ignored. This methodological
check earned no exact credit. Complete physical comparison, individual CFG/
packet/type review and selected-unit canonical cold replay are separate gates.
The target observations establish these pointer field projections only:

| Entry | x base | y base | opacity base | signed short timer |
| --- | --- | --- | --- | --- |
| 00471E00 | F2C | F54 | FF4 | EFE |
| 00498540 | F34 | F5C | FFC | EFE |
| 004C6050 | F18 | F40 | FE0 | EFE |
| 004E7350 | F18 | F40 | FE0 | EFE |
| 00531570 | F18 | F40 | FE0 | EFE |
| 005568F0 | F10 | F38 | FD8 | EFE |
| 00578B70 | F14 | F3C | FDC | EFE |
| 0059C6F0 | F34 | F5C | FFC | EFE |
| 005C52D0 | F2C | F54 | FF4 | F2A |

All actual filtering uses field4; draws use field700. Every SetRect/image/
filter/draw order and packet is retained. Local values are only the complete
132byte SDK-based quad atEBP-136 and RECT atEBP-152. The real DrawQuad helper
copies33 DWORDs from its reference; source never passes an undersized view.
Signed activation/timer and unsigned opacity behavior remain, including each
native impossible negative clamp after byte zero extension. No decompiler
omission or bug correction changes the emitted extent. Five wrong real
constructor/filter/draw/builder/own-selector controls each reject all nine
whole units. First preview and canonical object match every byte and field,
without a name fixture, extra locals/scopes, padding or old dependency edits.

There is no pasted decompiler body, native-code array, manual table, fake
return, manual EH, assembly, ABI alias, relocation mask or truncated extent.
No automatic clone, complete layout or original identity inference follows
from shared source. Original names and unproved types remain provisional;
no helper/library/global/table-data code receives credit.

Cold replay selected only the nine `character-special-render-ADDRESS` units
at the addresses above; one canonical object was built. All258 prior units,
120 canonical objects,188 source inputs,218 origin files,nine shared headers,
91 active drafts and4,342 other function rows remain unchanged. F009 plus207
additions retains654,486 code bytes and189 new inputs. R049 historical roles
remain through aliases; all97 unknown origins remain unknown. Preserve all
f122 native/attested/field/operand/policy/CFG/x87/dispatch/receiver/binding/cold/
parent evidence, first preview, sources, results, logs and PDBs.

Current totals: **267 exact functions/units,664,369 code bytes**,33.66% of
reviewed authored bytes and **33.60% conservatively**, including every pending
byte. The98% goal remains active and incomplete.

Validation:3603 CI tests passed in154.752s; seven exact-checkpoint tests
passed in0.500s; target/tracking/diff checks passed. Only nine new units were
cold-built. Evidence-preserving cleanup removed one obsolete own probe
(38,101bytes) and375 reproducible Python bytecode files(8,282,863bytes);
canonical objects, first preview, sources, native/operand/policy/CFG/dispatch/
binding/cold evidence, logs and PDBs remain. Receipts are retained under
`.analysis/f122-{final-compiler-inputs,object-cleanup,preservation-cleanup}.json`.

## F123 investigation at the F122 checkpoint

Independently review the remaining authored R049 character input-poll routines
adjacent to the stage renderers. Reconcile each complete CFG, ordered input
strings/counts/time windows/command assignments, true receiver, signed-byte
arguments and AL result, stack frame/return/tail/data extents before source.
F121 supplies methodology only; per-character order and command differences
must come from each own native body, not an automatically credited clone.
Keep actual target strings unchanged and preserve all accepted declarations.

The bounded F123 candidate set is `004724B0/982`, `00498BE0/1099`,
`004C6700/1099`, `004E7A00/982`, `00556FA0/982`, `00579220/1060`,
`0059CDA0/1177`, `005C5980/904`:8,285 code bytes. Native-only exports under
`.analysis/f123-input-polls/` retain2,385 instructions and211 calls with
25/28/28/25/25/27/30/23 decisions respectively. Ordered strings/counts/windows/
commands and a natural private preview are retained; no new source/byte credit
follows from these exports. Independently reconcile CFG/ABI and do complete
physical plus canonical cold comparison before adoption.

All accepted source/header inputs and unaccepted F021/F048/F061/F066/F085
drafts and failed controls remain protected. Do not repeat unchanged controls
or relax full physical comparison. Unknown math overloads and all97 unknown
origins remain unknown; evidence throughR268 is immutable. Private owners and
the F119 row projection are never instantiated or embedded. QueueFile00407A50/
QueueArchiveEntry00407B80 still need a proved complete local record layout;
resource root00456B60 retains f107's real588byte frame and unresolved
texture80/layout/filename bound. Build serially; cold-replay only new/affected
units and remove only obsolete reproducible outputs with full inputs/evidence
preserved. Later phases remain deferred.

## Previous accepted functions: F121

R049 special-stage renderer `00507040/1584` and command polling
`005076F0/1060` independently pass canonical cold comparison: **2,644 code
bytes plus22 table/selector bytes,658 instructions,54 actual calls and all94
real relocation fields**. Each own complete CFG, shared exit, ESP/EBP/x87
join and actual160/4byte frame is checked. Renderer returns RET4 and consumes
a signed stage byte; input returns plain RET. Ten/twelve following INT3 bytes
remain outside the extents. No tail, field or owned dispatch data is cropped.

The natural switch emits its complete three-target12byte table and ten-byte
selector mapping stages1..7,8..9,10. Both dispatch fields and all three table
fields are bound and compared, together with the actual selector bytes.
Only an independently complete132byte SDK-based quad and RECT are local;
private renderer/drawing owners remain pointer-only and are never instantiated
or embedded. The actual DrawQuad helper copies33 DWORDs from its quad reference.
Filtering uses owner field4 while all draws use field700. The signed timer,
unsigned opacity and all conditional updates remain unchanged.

Native code retains an impossible negative-opacity clamp after byte zero
extension. The decompiler omitted that block; the source retains the actual
unsigned check and zero store. This preserves the target's behavior and full
emitted extent, without adding arbitrary inert storage or correcting the bug.

The input routine independently retains all27 ordered literal string/count/
window/command choices. The full helper body reads signed byte arguments and
returns actual AL values, including4; the caller sign-extends AL. Source
uses a signed-byte result rather than a guessed BOOL. Every actual receiver,
initial command0 and native string byte is checked. F121's character-specific
ordering, including early623B/421C and final NRNR/NLNL, is preserved.

The first natural source preview and canonical object agree over all2,666
comparison bytes and94 fields. No name fixture, extra local/scope/padding or
old dependency edit is required. Five wrong real constructor/filter/draw/input/
selector bindings fail. There is no pasted decompiler body, target-code array,
manual table, fake return, manual EH, assembly, ABI alias, relocation mask or
comparison truncation. Original identities, names, full private layouts and
unproved types remain provisional; no helper/library/global/table-data code
receives credit.

```bash
scripts/repo-python scripts/replay-exact-units.py --unit character-special-render-00507040 --unit character-input-005076f0
```

All256 prior units,119 canonical objects,187 source inputs,218 origin files,
nine shared headers,91 active drafts and4,349 other function rows remain
unchanged. F009 plus198 additions retains640,230 code bytes and188 new inputs.
R049 roles remain through aliases; all97 unknown origins remain unknown.
Preserve f121 complete native/attested/callee/policy/CFG/x87/dispatch/receiver/
scalar/binding/cold/parent inputs, first preview, source, results, logs and PDBs.

Current totals: **258 exact functions/units,650,113 code bytes**,32.94% of
reviewed authored bytes and **32.88% conservatively**, including every pending
byte. The98% goal remains active and incomplete.

Validation:3603 CI tests passed in156.661s; seven exact-checkpoint tests
passed in0.521s; target/tracking and diff checks passed. Only the two new
units were cold-built. Evidence-preserving cleanup removed one obsolete own
probe(15,737bytes) and375 reproducible Python bytecode files(8,282,863bytes),
retaining all sources/inputs/native/policy/dispatch/binding/cold evidence, logs,
PDBs and canonical objects. Receipts are `.analysis/f121-{final-compiler-inputs,
object-cleanup,preservation-cleanup}.json`.

## F122 investigation at the F121 checkpoint

Independently review the nine remaining R049 special-stage render candidates:
`00471E00`, `00498540`, `004C6050`, `004E7350`, `00531570`, `005568F0`,
`00578B70`, `0059C6F0`, `005C52D0`. Each provisional code extent is1,584
bytes, total14,256 code bytes. Reconcile every own CFG, code/table/selector/
tail extent, signed stage ABI, true frame/local-value contract, private field
offsets and actual filtering/drawing receivers/packets before source. F121
supplies methodology and a complete SDK-based quad contract, not automatic
clone, layout or identity credit. Review all actual opacity/timer differences
and any redundant emitted branches rather than trusting decompiler omissions.

Native-only F122 exports are retained under `.analysis/f122-stage-renderers/`,
with attested function/callee queries, full assembly and field projections.
They receive no exact credit. Own tables/selectors are12+10 bytes each; all
nine currently decode353 instructions/27 calls. Native this-derived reads
show five x-field basesF2C/F34/F18/F10/F14, corresponding y bases40 bytes
higher and opacity bases200 bytes higher. The first eight timers areEFE;
005C52D0 instead usesF2A. These are operand observations, not complete layouts
or permission to omit any individual CFG/type/packet/source/cold review.

Keep all accepted inputs and unaccepted F021/F048/F061/F066/F085 drafts and
failed controls. No unchanged retries or relaxed physical comparison. Unknown
math overloads and all97 unknown origins remain unknown; evidence throughR268
is immutable. Incomplete private owners and the F119 row projection are never
instantiated or embedded. QueueFile00407A50/QueueArchiveEntry00407B80 still
need a proved complete local record layout; resource root00456B60 retains
f107's actual588-byte frame and unresolved texture80/layout/filename bound.
Build serially, cold-replay only new/affected units and remove only obsolete
reproducible outputs while retaining inputs/evidence. Later phases are deferred.

## Previous accepted functions: F120

Two independently authored R049 routines, auxiliary update `004A80F0/3935`
and AI action policy `00507B20/3000`, pass canonical cold comparison:
**6,935 code bytes, 1,789 instructions, 94 actual calls and all161 real
relocation fields**. Both complete CFGs, shared exits, plain RETs, ESP/EBP
and x87 stack joins are checked independently. The actual frames are120 and
12 bytes, with saved ESI in the AI. One/eight following INT3 bytes remain
outside the extents; there are no embedded tables or cropped tails.

The auxiliary update has no named local beyond this. Its29 remaining scalar
frame slots are generated by genuine signed integer/float conversions, not
manufactured arrays or padding. Six independent action828..833 paths store
short x/y pairs in owner fieldsF1A..F30. The orbital angle uses signed owner
F10 minus180 plus local C8. The actual two-float angle carrier is divided by
the observed radians-per-degree float before conversion. Position paths use
signed owner coordinatesF0C/F0E, signed facing and velocity, then convert to
integer and back to float exactly as the native x87/FTOL sequences do.

All six Spawn calls use ownerE4 as receiver. The complete helper confirms
effect short, x/y float, facing byte and layer byte; source retains all real
phase/collision/animation/reset/opacity/decrement ordering and early returns.
No incomplete actor or owner is constructed or embedded.

The AI uses one complete source-defined two-float local value. Native code
really computes and stores both components; its vertical difference is
subsequently unread. This actual store is retained, with no extra local or
invented storage. Both state predicates use opponent2E8. Signed facing,
the actual <=10 integer bound, random-call order, signed remainders90/2 and
countdown global68D63C remain unchanged. The policy has a void caller view,
without an invented return from leftover registers. Original local declaration,
private identities, full owner layouts and unproved types remain unknown.

The first auxiliary preview differed because parenthesized float lvalues
changed native expression loading/argument emission; ordinary unparenthesized
float views and the real byte assignment resolve it. The first AI preview
already matched except the two encoding bytes for <11 versus <=10. The
fourth combined preview and canonical object match all complete bytes and
relocations. No local-name fixture or added storage is required. Five wrong
real frame/spawn/angle/rand/countdown bindings fail. Unknown math overloads
remain unknown; no helper/library/global data/layout receives credit.
There is no pasted decompiler body, target-code array, fake return, manual EH,
assembly, padding, ABI alias, relocation mask or comparison truncation.

```bash
scripts/repo-python scripts/replay-exact-units.py --unit auxiliary-actor-update-004a80f0 --unit character-ai-policy-00507b20
```

All254 prior units,118 canonical objects,186 source inputs,218 origin files,
nine shared headers,91 active drafts and4,349 other function rows remain
unchanged. F009 plus196 additions retains637,586 code bytes and187 new
inputs. R049 historical roles remain through aliases; all97 unknown origins
remain unknown. Preserve f120 complete native/attested/callee/CFG/x87/receiver/
scalar/binding/cold/parent inputs, four previews, sources, results, logs and PDBs.

Current totals: **256 exact functions/units,647,469 code bytes**,32.81% of
reviewed authored bytes and **32.75% conservatively**, including every pending
byte. The98% goal remains active and incomplete.

Validation:3603 CI tests passed in146.273s; seven exact-checkpoint tests
passed in0.556s; target/tracking checks passed. Only the two new units were
cold-built. Cleanup receipts retain all canonical objects/inputs/evidence
before deleting four obsolete own probes and reproducible Python bytecode.

## F121 investigation at the F120 checkpoint

Review the nearby independently authored R049 routines:
CharacterSpecial::RenderAt00507040 `00507040/1584` and
CharacterAux::RunAt005076F0 `005076F0/1060`, total2,644 bytes. These are
independent ledger candidates, not automatically accepted clones. Reconcile
each full CFG, code/table/tail extent, actual return/stack/FPU carriers and
all actual helper receivers/packets before source. Establish any genuine
SDK/local value before constructing it; private owners remain pointer-only.
Keep math wrapper origins unknown and all accepted declarations unchanged.

Preserve all accepted sources/headers and unaccepted F021/F048/F061/F066/F085
drafts and failed controls. Do not repeat unchanged hypotheses or relax
complete physical comparison. QueueFile00407A50/QueueArchiveEntry00407B80 still
need a proved complete local record layout; resource root00456B60 retains
f107's actual588-byte frame and unresolved texture80/layout/filename bound.
The F119 row projection is never an allocatable complete private owner.
All97 unknown origins and evidence throughR268 remain unchanged. Build
serially; cold-replay only new/affected units and remove only obsolete
reproducible outputs while retaining inputs/evidence. Later phases are deferred.

## Previous accepted functions: F119

R040 MusicRoom RenderList `00425C80/2429` and R043 Result RenderRecordPage
`00430080/3314` independently pass canonical cold comparison: **5,743 code
bytes, 1,405 instructions, 170 actual calls and all 171 real relocation
fields**. One new source/object contains the two natural bodies. Every own
static CFG, ESP/EBP/x87 stack join, plain RET and the real324/216 byte frames
are checked. Three/fourteen following INT3 bytes remain outside the extents;
there are no embedded tables or cropped tails. Old inputs remain unchanged.

The only local aggregates are independently complete132 byte SDK-based quad
values and complete RECTs. Private scenes, managers and the record container
are pointer-only interfaces, never instantiated or embedded. The actual
DrawQuad helper copies33 DWORDs from its quad reference before drawing; the
source passes the complete132 byte value, not an undersized coordinate view.
Accepted SpriteTransform and graphics headers retain their existing declarations.

Music retains its signed list fields and bounds. The nonselected opacity128
store precedes the selected255 store. Its two distinct row quads translate
vertically by18 independently. All cumulative outline translations, drawing
receivers, input rectangles, row numbering and final image/header draws remain.

Result's mirrored gray backdrop actually uses manager field12; the other
manager calls use field8. The same genuine row variable is initialized to10
before SetBlend2 and serves as the first loop's row limit, then becomes0 and
increments as the page's display-row counter. This reuse is retained without
adding a count local or storage. The flag byte is zero-extended; signed page,
category, record bytes and the actual signed Size-result comparison remain.
All row glyph, score, outline and mode-specific draw orders are unchanged.

The read-only row projection uses the independently observed16 byte stride,
eight name glyph bytes, signed bytes8/9 and score at12. The glyph helper
consumes at most eight signed codes; no string terminator or buffer extent is
invented. The two unobserved alignment bytes remain unknown and have no filler
members. The projection is never instantiated or embedded and establishes no
complete original row/owner layout. It supplies only the observed pointer
reads and stride; no private layout earns new credit.

One bounded compiler fixture measures100 genuine local addresses. It selects
names only for the existing quad/RECT/index/opacity values. The final third
preview passes complete physical comparison with no extra local, array,
scope or padding. Both own cold units preserve actual syscall/method argument
widths, all drawing/transform receivers and the accepted BeginFrame AL view.
Five wrong real begin/constructor/draw/builder/import bindings fail.
There is no pasted decompiler output, target-code array, fake return, manual
EH, assembly, ABI alias, relocation mask or cropped comparison. Original names,
full private layouts and unproved types remain provisional; no helper,
library or global data receives credit.

```bash
scripts/repo-python scripts/replay-exact-units.py --unit music-room-render-list-00425c80 --unit result-render-record-page-00430080
```

All 252 prior units, 117 canonical objects, 185 source inputs, 218 origin files,
nine shared headers, 91 active drafts and 4,349 other function rows remain
unchanged. F009 plus194 additions retains630,651 code bytes and186 new inputs.
R040/R043 roles remain through aliases. All97 unknown origins remain unknown.
Preserve all f119 native/attested/callee/SDK/CFG/packet/receiver/row-view/local-
name/binding/cold/parent inputs, sources, results, logs and PDBs, including the
compiler fixture and all three previews.

Validation: both complete units pass canonical cold replay, seven checkpoint
tests pass, and full CI passes 3,603 tests in 154.055s. Target identity,
tracking, progress and diff checks pass. Cleanup removes three obsolete game
probe objects and one pure compiler fixture (65,007 bytes), plus 375 Python
bytecode files (8,282,863 bytes), total 8,347,870 bytes. Canonical objects,
sources, compiler inputs, evidence, results, logs and PDBs remain. Hash receipts
are `.analysis/f119-final-compiler-inputs.json`,
`.analysis/f119-object-cleanup.json` and
`.analysis/f119-preservation-cleanup.json`. No prior unit was rebuilt.

Current totals: **254 exact functions/units, 640,534 code bytes**, 32.46% of
reviewed authored bytes and **32.40% conservatively**, including every pending
byte. The 98% goal remains active and incomplete.

## F120 investigation at the F119 checkpoint

Review two complete independently authored R049 auxiliary actor routines:
CharacterAux::RunAt004A80F0 `004A80F0/3935` and
CharacterAux::RunAt00507B20 `00507B20/3000`, total6,935 bytes. Their raw prefixes
show ordinary actor-update/relative-position work rather than constructor
stubs. Reconcile full code/table extents, CFG, true exits/return carriers,
floating-point conditions and every actual helper packet before source.
Establish any genuine SDK vector/local-value contract before constructing it;
private owners stay pointer-only. Preserve unknown math-wrapper origins.

Keep all accepted source/header inputs and old F048/F061/F066/F085 drafts and
failed controls. Do not repeat unchanged hypotheses or relax complete physical
comparison. The record projection above is never an allocatable complete
private owner. QueueFile00407A50/QueueArchiveEntry00407B80 still need a proved
complete local record layout; resource root00456B60 retains f107's real588-byte
frame and unresolved texture80/layout/meaningful filename bound. All97 unknown
origins and evidence throughR268 remain unchanged. Builds stay serial;
cold-replay only new or affected units and remove only obsolete reproducible
outputs after retaining inputs and evidence. Later phases remain deferred.

## Previous accepted function: F118

Complete independently authored R035 opening timeline `004277A0..00428C7A`
passes canonical cold comparison: **5,339 code bytes, 1,188 instructions,
57 calls and all 124 real relocation fields**. Five following INT3 bytes
remain outside the extent. There are no embedded tables. Every static CFG
instruction, ESP/EBP join, x87 stack join and the common plain RET is checked,
including the actual 448 byte frame. No prior source or header changes.

The accepted BeginFrame AL-return view is reused; EndFrame only occurs after
a successful begin. The real constructor call at004277C5 constructs a complete
132 byte SpriteQuad drawing value at local-152. The native routine does not
subsequently read that value. Its actual constructor invocation remains in
source. F064/F083 already establish the complete physical packet and the
unchanged SDK-based header; no original owner layout or new padding is
inferred from the local spacing. The incomplete scene and drawing-manager
owners remain pointer-only and are never instantiated or embedded.

All40 actual draw indices, drawing receivers, nine-word/RET36 packets and
settings0/0/2 are checked. The three float-carrier calls have one argument
each; they retain two, three and four already-pushed outer draw words. The
decompiler's extra apparent parameters are not used as ABI evidence. Both
00428D20 and00428D40 remain unknown/review origins under their unchanged R163
function evidence and initial inventory origin rows. Their actual observed
float-carrier interface does not classify them or earn helper credit.

Unsigned interval arithmetic and qword FILD conversions, the1.1f/1.2f designer
tile constant folding, SDK ARGB/XRGB packing and all eight real compiler
float-to-byte conversions remain. The scale expression really uses double
1.5 and1.0 constants; other observed arithmetic keeps its float widths.
Caption-loop fade-out specifically divides first, multiplies255, then subtracts
from255. It is not reassociated into an endpoint difference. The complete
physical comparison includes all floating constants and native operations.

One bounded compiler fixture observes115 genuine local addresses and measures
identifier buckets. The final source names only eight actual values:
closingScale-4, begin-8, rangeEnd-12, complete localQuad-152, inProgress-156,
scrollPosition-160, opacity-161 and entryIndex-168; this is-172. No extra local,
array, scope or storage is introduced. The final third preview passes whole
physical comparison, without frame aliases or masks. The natural source
retains the observed time intervals, drawing order, positions and alpha policy.

Five wrong actual begin/constructor/draw/scalar/constant bindings fail.
There is no pasted decompiler text, code byte array, fake return, manual EH,
assembly, ABI alias or cropped comparison. Original names, complete scene
layout and unproved types remain provisional. No helper, library or global
data receives new credit. The /GS flag remains explicit reproducibility
configuration, not an inferred executable-wide compiler profile.

```bash
scripts/repo-python scripts/replay-exact-units.py --unit opening-timeline-004277a0
```

All 251 prior units, 116 canonical objects, 184 source inputs, 218 origin files,
nine shared headers, 91 active drafts and 4,350 other function rows remain
unchanged. F009 plus192 additions retains624,908 code bytes and185 new inputs.
The R035 historical role remains through its alias. All97 unknown origins
remain unknown. Preserve all f118 source, scalar timeline authoring, native/
attested/callee/FP/SDK/CFG/packet/local-name/binding/cold/parent inputs,
results, logs and PDBs, including the compiler fixture and all three previews.

Validation: the selected complete unit passes canonical cold replay, seven
checkpoint tests pass, and full CI passes 3,603 tests in 147.951s. Target
identity, tracking, progress and diff checks pass. Cleanup removes three
obsolete game-probe objects and one compiler name-control object (69,894 bytes),
plus 375 Python bytecode files (8,282,863 bytes), total 8,352,757 bytes.
Canonical objects, all sources, compiler inputs, evidence, results, logs and
PDBs remain. Hash receipts are `.analysis/f118-final-compiler-inputs.json`,
`.analysis/f118-object-cleanup.json` and
`.analysis/f118-preservation-cleanup.json`. No prior unit was rebuilt.

Current totals: **252 exact functions/units, 634,791 code bytes**, 32.17% of
reviewed authored bytes and **32.11% conservatively**, including every pending
byte. The 98% goal remains active and incomplete.

## F119 investigation at the F118 checkpoint

Review two complete independently authored scene drawing functions:
R040 MusicRoomScene::RenderList `00425C80/2429` and R043
ResultScene::RenderRecordPage `00430080/3314`, total5,743 bytes. Reconcile each
full code/table extent, CFG, actual text/renderer/helper packet, floating
expression, calling convention and genuine SDK/local buffer before source.
Use unchanged accepted graphics/drawing interfaces and independently complete
values. Private owners stay pointer-only; never allocate/embed an incomplete
owner or infer a buffer bound merely from a stack gap.

Preserve all old accepted inputs, unknown math chains,97 unknown origins and
active drafts. F048/F061/F066/F085 remain unaccepted; do not repeat unchanged
failed controls or weaken whole physical comparison. QueueFile00407A50/
QueueArchiveEntry00407B80 still need a proved complete local record layout.
Resource root00456B60 retains f107's real588-byte frame and unresolved
texture80/layout/meaningful filename bound. Compiler builds remain serial;
cold-replay only new or affected units and remove only obsolete reproducible
outputs after retaining inputs and evidence. Subsequent phases remain deferred.

## Previous accepted functions: F117

The remaining nine R049 stage configurations independently pass canonical cold
comparison: **34,230 code bytes plus all 360 bytes of their own switch tables**,
8,423 instructions, 523 actual calls and all 1,479 real relocation fields.
One new source/object contains nine natural C++ bodies; the first complete
probe is entirely exact. Each complete code/table extent, all ten table edges,
default exit, plain RET, actual eight-byte frame and every static CFG/stack
join are checked separately. Following INT3 bytes remain outside each extent.

| Address | Code bytes | Compared bytes | Instructions | Calls | Four flag bytes begin |
| --- | ---: | ---: | ---: | ---: | --- |
| 00497630 | 3,814 | 3,854 | 937 | 58 | 0xFFC |
| 004C5150 | 3,800 | 3,840 | 935 | 58 | 0xFE0 |
| 004E6450 | 3,800 | 3,840 | 935 | 58 | 0xFE0 |
| 00506140 | 3,800 | 3,840 | 935 | 58 | 0xFDC |
| 00530650 | 3,822 | 3,862 | 941 | 59 | 0xFE0 |
| 005559F0 | 3,800 | 3,840 | 935 | 58 | 0xFD8 |
| 00577C70 | 3,800 | 3,840 | 935 | 58 | 0xFDC |
| 0059B7F0 | 3,797 | 3,837 | 935 | 58 | 0xFFC |
| 005C43D0 | 3,797 | 3,837 | 935 | 58 | 0xFF4 |

All 1,398 ordered policy events are re-read from the pinned native target:
702 actor/borrowed-actor stores, 173 global stores and 523 calls. Every own
intro selection, field offset, position, life, duration, scalar expression
and write/call order is retained. The generic pointer view does not establish
that these are the same original class, character or complete layout.

00497630 really resets the transition timer and mode0 in stage7. 00530650
really makes two override calls in stage7. Six methods reset the borrowed
animation counter to137 in stage6; the other methods use0. 005C43D0 uses intro
value9 in every configured stage and final life5000/duration2400. Individual
round-life differences and the five actual flag bases remain distinct.
No duplicate call, state policy or layout is corrected to fit a common template.

Actual signed difficulty multiply/add/IDIV behavior and real byte/word/DWORD
argument carriers follow the complete independently reviewed389-byte callee.
Raw dirty upper register bits stay included unmasked in physical comparison;
only the separate semantic packet audit normalizes genuinely consumed narrow
arguments. All eleven own dispatch/table fields per function are checked.
The accepted AnimationState declaration and every old header remain unchanged.

Source uses ordinary typed scalar statements and natural switches authored
from reviewed native behavior observations. It contains no pasted decompiler
text, target-code array, manually supplied table, extra local, padding, fake
return, manual EH, assembly, ABI alias, relocation mask or cropped extent.
No incomplete owner is instantiated, embedded or allocated. Original names
and types not proved by native reads remain provisional. No helper, global
data or switch-table data byte receives new code credit.

```bash
scripts/repo-python scripts/replay-exact-units.py --unit character-special-stage-00497630 --unit character-special-stage-004c5150 --unit character-special-stage-004e6450 --unit character-special-stage-00506140 --unit character-special-stage-00530650 --unit character-special-stage-005559f0 --unit character-special-stage-00577c70 --unit character-special-stage-0059b7f0 --unit character-special-stage-005c43d0
```

All 242 prior units, 115 canonical objects, 183 source inputs, 218 origin files,
nine shared headers, 91 active drafts and 4,342 other function rows remain
unchanged. F009 plus191 additions retains619,569 code bytes and184 new inputs.
R049 historical roles remain through aliases; all97 unknown origins remain
unknown. Preserve all f117 native/attested/scalar-policy/authoring/CFG/packet/
store/table/binding/cold/parent inputs, sources, results, logs and PDBs.

Validation: all nine complete code/table units pass canonical cold replay,
seven checkpoint tests pass, and full CI passes 3,603 tests in 139.432s.
Target identity, tracking, progress and diff checks pass. Cleanup removes one
obsolete reproducible probe object (70,336 bytes) and 375 Python bytecode files
(8,282,863 bytes), total 8,353,199 bytes. Canonical objects, all sources,
compiler inputs, evidence, results, logs and PDBs remain. Hash receipts are
`.analysis/f117-final-compiler-inputs.json`,
`.analysis/f117-object-cleanup.json` and
`.analysis/f117-preservation-cleanup.json`. No prior unit was rebuilt.

Current totals: **251 exact functions/units, 629,452 code bytes**, 31.89% of
reviewed authored bytes and **31.84% conservatively**, including every pending
byte. The 98% goal remains active and incomplete.

## F118 investigation at the F117 checkpoint

Review complete independently authored R035 OpeningScene::RenderTimeline
`004277A0`, provisionally5,339 bytes. Establish every code/table extent, full
CFG, actual calling convention, floating-point expression, renderer/font/
helper packet and genuine SDK local value before source. Preserve accepted
source/header inputs using separate pointer-only views where necessary.
Do not allocate/embed partial owners or invent layout/stack storage.

Large F048/F061/F066/F085 drafts remain unaccepted. Preserve every draft and
its existing failed controls; do not repeat unchanged hypotheses or weaken
whole physical exactness. QueueFile00407A50/QueueArchiveEntry00407B80 still need
a proved complete local record layout. Resource root00456B60 retains f107's
real588-byte frame and unresolved texture80/layout/meaningful filename bound.
Keep all97 unknown origins and origin evidence throughR268 unchanged. Builds
remain serial; replay only new or affected units and remove only obsolete
reproducible outputs after retaining inputs and evidence.

## Previous accepted function: F116

Complete R049 stage configuration `00470F00` independently passes canonical
cold comparison: **3,797 code bytes plus the entire 40 byte switch table**,
935 instructions, 58 actual calls and all 164 real relocation fields. The
comparison covers00470F00..00471DFC; three following INT3 bytes are excluded.
Only code earns authored-byte credit. All ten table targets, the signed-stage
default exit, common plain RET and every static CFG/stack join are checked.
The real eight-byte frame contains this and the compiler's switch value.

One natural C++ switch handles stages1..10. Its first source probe is entirely
exact, including the compiler-generated table and each local table symbol.
No target byte array, manual jump table, extra local or name-control build is
needed. Every one of the78 actor/borrowed-actor field stores and19 global
stores agrees with the hand-reviewed native stage policies. Stage1 retains
its different camera-call ordering; stage7 omits the earlier transition reset
stores and uses its distinct positions, durations and final round life.
Stages8..10 only set their entry/flag fields as the native code does.

The signed difficulty expressions retain multiplication, addition and signed
IDIV with no common-expression caching. Complete native round-field callee
004574D0 independently proves the first signed byte index, short life, three
byte carriers, three DWORD carriers and RET32. All actual receiver and packet
values agree. The native low-byte argument writes leave dirty upper register
bits; those bits are included unmasked in the full physical comparison.
Only the separate semantic packet audit normalizes the actual subword widths
consumed by the callee. Camera calls retain their actual cdecl four-word/no-arg
packets, and the accepted AnimationState reset retains its real borrowed
receiver and short argument. Ignored results and original state policy remain.

A pointer-only actor view and the unchanged accepted AnimationState header
avoid allocating or embedding incomplete owners. Full layouts, original
character/class/field names and types not proved by native reads remain
provisional. Five wrong real stage/difficulty/helper/table-edge bindings fail
whole comparison. There is no padding, inert local, artificial array, fake
return, manual EH, assembly, ABI alias, relocation mask or cropped extent.
No helper, global data or table data bytes receive new code credit.

```bash
scripts/repo-python scripts/replay-exact-units.py --unit character-special-stage-00470f00
```

All 241 prior units, 114 canonical objects, 182 source inputs, 218 origin files,
nine shared headers, 91 active drafts and 4,350 other function rows remain
unchanged. F009 plus182 additions retains585,339 code bytes and183 new inputs.
The R049 historical role remains through its alias. All97 unknown origins
remain unknown. Preserve all f116 source and its scalar-policy authoring
input, full native/table/callee/attested/CFG/packet/store/binding/cold/parent
evidence, results, logs and PDBs. The registered canonical cold replay is the
acceptance evidence.

Validation: the complete code-and-table unit passes canonical cold replay,
seven checkpoint tests pass, and full CI passes 3,603 tests in 144.833s.
Target identity, tracking, progress and diff checks pass. Cleanup removes one
obsolete reproducible probe object (9,411 bytes) and 375 Python bytecode files
(8,282,863 bytes), total 8,292,274 bytes. Canonical objects, all sources,
compiler inputs, evidence, results, logs and PDBs remain. Hash receipts are
`.analysis/f116-final-compiler-inputs.json`,
`.analysis/f116-object-cleanup.json` and
`.analysis/f116-preservation-cleanup.json`. No prior unit was rebuilt.

Current totals: **242 exact functions/units, 595,222 code bytes**, 30.16% of
reviewed authored bytes and **30.11% conservatively**, including every pending
byte. The 98% goal remains active and incomplete.

## F117 investigation at the F116 checkpoint

Review the remaining nine R049 special-stage methods individually:
`00497630/3814`, `004C5150/3800`, `004E6450/3800`, `00506140/3800`,
`00530650/3822`, `005559F0/3800`, `00577C70/3800`, `0059B7F0/3797`,
and `005C43D0/3797`, provisionally34,230 code bytes. F116 supplies a natural
control-flow and scalar-policy methodology. Establish every own complete
code/table extent, call packet, state store, constant and ABI independently;
similarity alone supplies no credit. Cold-build each new unit before accepting
its complete code and table. No old unit needs replay without a dependency
change. Preserve the first F116 source and all its authoring/evidence inputs.

Keep accepted inputs unchanged and use pointer-only views for incomplete
owners. QueueFile00407A50 and QueueArchiveEntry00407B80 still need a proved
complete local record layout. Resource root00456B60 retains f107's real588-byte
frame and unresolved texture80/layout/meaningful filename bound. Keep all old
drafts and97 unknown origins unchanged. Compiler builds remain serial; clean
only obsolete reproducible outputs after retaining inputs and evidence.
No padding, invented storage or incomplete owner allocation/embedding.

## Previous accepted functions: F115

The remaining independent R016/R017 audio functions pass canonical cold
comparison: SoundBank volume `004073B0/13`, stream volume `004073C0/13`,
SoundBank Play `004079C0/142`, record constructor `00409290/83` and record
destructor `004092F0/87`. One new source/object adds **338 code bytes,
121 instructions, nine actual calls and all seven real relocation fields**.
The complete CFG, stack joins, physical returns and following INT3 boundaries
are checked. All five bodies are exact on the first natural source probe.

The setters are cdecl byte carriers; their original signedness is unknown.
Play is thiscall RET4. It rejects a negative index or an index at/above the
signed Size result, checks the actual unchecked element for null, then uses
the checked At element. Its one real buffer local receives Stop,
SetCurrentPosition(0), SetVolume((signedBankVolume-100)*50), then Play(0,0,0).
It adds no clamp and no special treatment of zero master volume. All actual
SDK slots, helper cleanup and ignored result behavior remain unchanged.

Two actual queue-file/archive caller lifetimes prove the real constructor and
destructor independently. Each installs EH state0 after construction, invokes
the same destructor normally after clearing that state, and has a real
parent-1 unwind action destroying the same ebp-0x54 local. The actual handler
FuncInfo and unwind maps are parsed from the pinned target. This establishes
the lifecycle roles without allocating or declaring a complete local record
in the reconstructed source. These own bodies have no manual EH graph.
The C++ constructor naturally returns this and performs exactly the seven
observed zero stores at offsets0,32,36,40,44,60,8. Other fields remain untouched.
The destructor skips CloseHandle when byte58 marks the handle borrowed;
it leaves that borrowed handle unchanged. An owned nonnull handle is closed
and zeroed. Independently, a nonnull buffer is Released and zeroed.

Separate pointer-only views leave every prior input unchanged. Neither owner
is instantiated, embedded or allocated, and full layouts remain unknown.
There is no padding, extra local, artificial array, fake return, manual EH,
assembly, ABI alias, relocation mask or cropped comparison. Four wrong real
volume/At/unchecked/import bindings fail physical comparison. Names and types
not established by the evidence remain provisional. No helper, global data,
constructor-caller EH metadata or complete layout receives new credit.

```bash
scripts/repo-python scripts/replay-exact-units.py --unit sound-bank-volume-004073b0 --unit stream-volume-004073c0 --unit sound-bank-play-004079c0 --unit audio-record-ctor-00409290 --unit audio-record-dtor-004092f0
```

All 236 prior units, 113 canonical objects, 181 source inputs, 218 origin files,
nine shared headers, 91 active drafts and 4,346 other function rows remain
unchanged. F009 plus181 additions retains581,542 code bytes and182 new inputs.
R016/R017 historical names remain through aliases. All97 unknown origins
remain unknown. Preserve all f115 source, attested/native/helper/SDK/CFG/
packet/lifetime/binding/cold/parent evidence, results, logs and PDBs.

Validation: all five selected units pass canonical cold replay, seven checkpoint
tests pass, and full CI passes 3,603 tests in 153.360s. Target identity,
tracking, progress and diff checks pass. Cleanup removes only one obsolete
reproducible probe object (11,972 bytes) and 375 Python bytecode files
(8,282,863 bytes), total 8,294,835 bytes. Canonical objects, sources, compiler
inputs, evidence, results, logs and PDBs remain. Hash receipts are
`.analysis/f115-final-compiler-inputs.json`,
`.analysis/f115-object-cleanup.json` and
`.analysis/f115-preservation-cleanup.json`. No prior unit was rebuilt.

Current totals: **241 exact functions/units, 591,425 code bytes**, 29.97% of
reviewed authored bytes and **29.91% conservatively**, including every pending
byte. The 98% goal remains active and incomplete.

## F116 investigation at the F115 checkpoint

Review the complete independently authored R049 method
CharacterSpecial::AdvanceAt00470F00, provisionally3,797 bytes. Reconcile every
exit, switch table and shared tail; establish actual calling conventions,
floating-point expressions, helper packets and genuine local values before
source. Related R049 special methods may offer a coherent family after
individual full extent, control-flow, packet and constant review. Similarity
alone does not earn credit.

Preserve all accepted inputs and use pointer-only views for incomplete owners.
QueueFile00407A50 and QueueArchiveEntry00407B80 still need an independently
proved complete local record layout; exact constructor/destructor methods and
a container stride do not establish all member types. Resource root00456B60
remains unaccepted with f107's real588-byte frame and unresolved texture80/
layout/meaningful filename bound. Keep every old draft and all97 unknown
origins unchanged. Builds remain serial; cold-replay only new or affected
units and remove only obsolete reproducible outputs after preserving inputs
and evidence. No invented padding, storage or incomplete owner allocation.

## Previous accepted functions: F114

The complete R016 controls independently pass canonical cold comparison in one
new source/object: ClearPlayback `00407CA0/29`, Start `00407CC0/169`, Stop
`00407D70/88`, ApplyVolumeOffset `00407DD0/129`, ScheduleFade `00407E60/138`,
and Worker `00407EF0/535`. This adds **1,088 code bytes, 332 instructions,
40 actual calls and all 77 real relocation fields**. All static CFG
instructions, stack joins, physical returns and following INT3 boundaries
are checked. There are no embedded data tables or cropped tails.

Five functions are cdecl controls, rather than instance methods suggested by
the earlier role names. The actual CreateThread producer at00407219 passes
Worker00407EF0 as its callback with a null argument. The verified KERNEL32
import and pinned WinBase PTHREAD_START_ROUTINE declaration independently
prove DWORD WINAPI Worker(LPVOID), including its physical RET4. The native
constant loop has a physical zero-result epilogue; its ordinary runtime exit
is unreachable. That complete epilogue remains inside the comparison. The
source contains the SDK callback completion return, without manufacturing
an alternative exit, return value, or ABI to obtain a match.

The master volume is a signed byte. Start sends MIN only when master is0;
otherwise it sends (master-100)*50 without clamping, then Play(0,0,LOOPING).
ApplyVolumeOffset adds the LONG offset and separately clamps below MIN or
master0, then above0. Clear clears both flags and the queue. Stop clears both
flags and pops the first entry only when its buffer is nonnull. Empty queues
and null buffers retain the native differences between these functions.

ScheduleFade retains separate Front calls for target/step LONG fields48/52
and byte flags56/57. When already playing it marks fading only for a nonnull
buffer; when stopped it clears fading and optionally starts immediately.
The worker distinguishes streaming, explicit nonstream looping and ordinary
nonstream playback. Streaming calls the accepted Refill(0x20000), checks
GetStatus and invokes Stop when playback ends. Explicit looping queries the
write cursor, not the play cursor, and subtracts loopLength once only when
writeCursor exceeds loopEnd. Ordinary nonstream completion clears playing
without adding the streaming Stop/fading cleanup.

The current LONG fade is applied before current+=step*4. Negative steps stop
fading below the target or at/below MIN. The positive branch preserves the
native current<target or current>=0 condition, including its apparently
counterintuitive direction; only the nonnegative value is clamped to0.
Completion preserves Stop then Start order when both byte flags request it.
The lazily created event and Wait80 polling, ignored SDK results, empty-queue
playing-only reset and null-buffer behavior remain unchanged.

Real SDK vtable slots and every actual argument packet are checked
independently. Four incorrect physical queue/master/Front/refill bindings
fail comparison. The first natural source is entirely exact with the genuine
root DWORDs and scoped record pointer; no name-control build is needed.
Separate pointer-only queue/record views preserve all accepted inputs. The
external unsized BYTE address anchor defines no storage and allows the real
queue object address to be passed without inventing a pointer global or
allocatable owner. Neither partial owner is instantiated or embedded. Original
names, full layouts, flag types and volatile spelling remain provisional.
There is no padding, inert local, artificial array, manual EH, assembly, ABI
alias, relocation mask or comparison truncation. /GS is an explicit
reproducibility setting; these bodies do not prove an executable-wide profile.

```bash
scripts/repo-python scripts/replay-exact-units.py --unit stream-control-clearplayback-00407ca0 --unit stream-control-start-00407cc0 --unit stream-control-stop-00407d70 --unit stream-control-applyvolumeoffset-00407dd0 --unit stream-control-schedulefade-00407e60 --unit stream-control-worker-00407ef0
```

All 230 prior units, 112 canonical objects, 180 source inputs, 218 origin files,
nine shared headers, 91 active drafts and 4,345 other function rows stay
unchanged. F009 plus176 additions retains581,204 code bytes and181 new inputs.
The six R016 historical roles remain through aliases. All97 unknown origins
remain unknown. Preserve all f114 inputs, attested/native/helper/SDK/CFG/
packet/binding/cold/parent evidence, results, logs and PDBs. No helper, global
data or complete private layout receives new credit.

Validation: all six selected units pass canonical cold replay, seven checkpoint
tests pass, and the full CI passes3,603 tests in127.617s. Target identity,
tracking, progress and diff checks pass. Cleanup removes only one obsolete
reproducible probe object (14,218 bytes) and375 Python bytecode files
(8,282,863 bytes), total8,297,081 bytes. Canonical objects, compiler inputs,
all sources, evidence, results, logs and PDBs remain. Hash receipts are
`.analysis/f114-final-compiler-inputs.json`,
`.analysis/f114-object-cleanup.json` and
`.analysis/f114-preservation-cleanup.json`. No prior unit was rebuilt.

Current totals: **236 exact functions/units, 591,087 code bytes**, 29.95% of
reviewed authored bytes and **29.90% conservatively**, including every pending
byte. The 98% goal remains active and incomplete.

## F115 investigation at the F114 checkpoint

Review the remaining independent audio lifecycle/control functions:
SoundBank SetVolume `004073B0/13`, AudioStream SetVolume `004073C0/13`,
SoundBank Play `004079C0/142`, AudioStreamRecord Initialize `00409290/83` and
ReleaseResources `004092F0/87`, total338 bytes. Establish actual calling
conventions, SDK slots, lifecycle field widths and return/constructor evidence
before source. Preserve all accepted inputs through separate pointer-only
views where necessary; never instantiate or embed a partial owner.

QueueFile00407A50 and QueueArchiveEntry00407B80 still need independently proved
complete local record construction before they can use a real local record.
Do not infer that layout solely from an exact pointer-only method or the
container stride. Keep wrapper00409490 and all old drafts unchanged. All97
unknown origins stay unknown. Compiler builds remain serial; cold-replay only
new or affected units and remove only obsolete reproducible outputs after
retaining evidence and inputs. Resource root00456B60 remains unaccepted with
f107's real588-byte frame and unresolved texture80/layout/meaningful filename
bound. No invented padding, storage, buffers or incomplete owner allocation.

## Previous accepted function: F113

Complete R017 refill `00408BD0..0040928B` independently passes canonical cold
comparison: **1,724 code bytes, 626 instructions, 25 calls and all 19 real
relocation fields**. Four following INT3 bytes stay outside the extent. One
new source/object/unit preserves every old source and header, so no prior
unit needs replay. The full ordinary/polling CFG and every stack join agree,
with the actual 76 byte frame, one RET4 and no embedded data tables.

The SDK call is GetCurrentPosition(null-play-cursor, &write-cursor), not a
play-cursor query. Missing owner handle returns immediately. The nonloop EOF
Stop windows retain their strict circular comparisons and continue into the
refill gate. The gate uses the unsigned cursor interval and the actual
bool-product/SBB-NEG-IMUL expression for its wrapped upper boundary. The sole
reviewed caller pushes the fixed0x20000 block size and ignores the return.

After the gate, CreateEventA(0,0,0,0) and Wait20 poll the request byte67138C.
The event is closed before the active byte67138D becomes1. Every normal return
after that claim necessarily passes the active=0 store. Each of the three
Locks necessarily reaches its own Unlock. Early no-handle/gate exits leave
the active byte untouched. The source preserves this actual protocol without
claiming original volatile spelling or synchronization correctness.

The three complete policies retain all native differences. Nonloop mode
seeks to the current file position. A crossing that starts before EOF reads
the valid prefix, zero-fills the overflow, advances the half boundary by that
overflow (not the full count), wraps each ring boundary by at most one buffer
size and advances the file position by the full count. Once already at/past
EOF, the locked path performs no read or state update before Unlock. The
noncrossing path reads the full count and advances normally.

An explicit loop uses dataBegin+loopEnd as its limit. A crossing reads the
first segment, seeks to dataBegin+loopEnd-loopLength, reads the overflow, and
writes next=count-loopLength+next. With looping enabled but loopEnd0, the
crossing has two consecutive reads without a second seek and writes
next=count-absoluteDataEnd+next. Both use full-count ring advancement. These
behaviors, inclusive crossing comparisons, zero-length boundary calls,
ENTIREBUFFER2 flags and ignored SDK results remain unchanged.

The source has two genuine root DWORDs, the actual scoped event, and three
scoped groups of four SDK outputs plus one real overflow value each. Their
observed slots are -4/-8/-12, -16..-32, -36..-52, -56..-72 and owner-76.
The first natural source is entirely exact using retained compiler name
measurements; no new name-control build or storage search is needed. A
separate pointer-only owner view leaves the accepted input declarations
unchanged. It is never instantiated, embedded or allocated. Full owner layout,
original names/types and original return declaration remain provisional; the
source uses a compatible void interface without inventing a return value.

All actual SDK slots/packet widths/imports are independently checked. Four
wrong physical bindings, three packet mutations and three native state-store
mutations fail. The complete vendor memset evidence remains unchanged and
receives no new credit. There is no padding, inert local, artificial array,
extra scope/storage, manual EH, assembly, ABI alias, mask or cropped comparison.
The /GS setting is explicit reproducibility configuration; this body has no
eligible local array and no cookie sequence, so it does not distinguish an
executable-wide original /GS profile.

```bash
scripts/repo-python scripts/replay-exact-units.py --unit audio-record-refill-00408bd0
```

All 229 prior units, 111 canonical objects, 179 source inputs, 218 origin files,
nine shared headers, 91 active drafts and 4,350 other function rows stay
unchanged. F009 plus170 additions retains580,116 code bytes and180 new inputs.
R017 historical role remains through its alias. All97 unknown origins remain
unknown. Keep every f113 source, attested/native/CFG/SDK/packet/state/helper/
name-selection/binding/cold/parent input and all results, logs and PDBs.

Full CI passes **3,603 tests in 127.319 seconds**; seven exact-checkpoint
checks also pass. Target, tracking, progress and whitespace checks pass.
No old unit was cold-rebuilt.

Cleanup removes only the one obsolete reproducible probe object / 11,939 bytes
and375 Python bytecode caches / 8,282,863 bytes, reclaiming8,294,802 bytes.
The first probe and canonical object agree on the full1724 bytes and all19
relocation records. Canonical outputs, all source/compiler inputs, retained
prior name measurements, complete native/CFG/SDK/packet/state/helper evidence,
results, logs and PDBs remain. Hash receipts and preservation guards are in
`.analysis/f113-object-cleanup.json`, `.analysis/f113-preservation-cleanup.json`
and `.analysis/f113-final-compiler-inputs.json`. All229 old units,111 old objects,
179 source inputs,218 origin files,nine headers,91 active drafts and4,350
other function rows pass unchanged checks. No compiler or CI job remains active.

Current totals: **230 exact functions/units, 589,999 code bytes**, 29.90% of
reviewed authored bytes and **29.84% conservatively**, including every pending
byte. The 98% goal remains active and incomplete.

## F114 investigation at the F113 checkpoint

Bounded raw exports for all six candidates are retained in
`.analysis/f114-native-frontier.json` and `.analysis/f114-stream-control/`.
These linear exports establish no source, ABI, layout or CFG acceptance;
no F114 source or credit exists yet.


Continue the complete R016 stream-control cohort: ClearPlayback `00407CA0`
(29 bytes), Start `00407CC0` (169), Stop `00407D70` (88), ApplyVolumeOffset
`00407DD0` (129), ScheduleFade `00407E60` (138), and Worker `00407EF0` (535),
total1,088 bytes. The complete worker export is retained in
`.analysis/f113-audio-refill/caller-00407ef0.asm`. Refill and the four input
methods, factory and device prerequisites are now exact. Review the real SDK
queue/control/fade packets, all fields and scalar arithmetic before source.
Do not infer an allocatable stream/queue owner or complete private layout.

Preserve accepted interfaces and dependencies, using a separate pointer-only
view where needed. ABI/header changes require replay of affected units. Keep
all old units,97 unknown origins and active drafts, including wrapper00409490.
Compiler builds remain serial; remove only obsolete reproducible outputs after
retaining inputs and evidence. Resource root00456B60 remains unaccepted with
f107's real588-byte frame and unresolved texture80/layout/meaningful filename
bound. No invented padding, storage, buffers or incomplete owner allocation.

## Previous accepted functions: F112

Four complete R017 input functions independently pass canonical cold comparison:
OpenFile `00408110..00408382` (627 bytes), OpenArchiveEntry
`00408390..00408666` (727), ReadLoopPointsFromFile `00408670..004088F3` (644),
and ReadLoopPointsFromArchive `00408900..00408BC8` (713). All **2,711 code bytes,
824 instructions, 55 calls and 66 real relocation fields** match. The following
13/9/12/7 INT3 bytes remain outside their extents. Four reports share one serial
cold object build. Both ordinary and polling-loop CFGs are complete, with all
stack joins, actual frames of 60/68/352/360 bytes below EBP and RET8/12/4/8.
No old source, interface or header changes, so no prior unit needs replay.

File opening closes any prior nonzero owner handle before CreateFileA, stores
the new handle, and returns on INVALID_HANDLE_VALUE. It then marks disk mode,
reads format size at16 and the complete SDK WAVEFORMATEX18, locates data size
at formatSize+24 and payload at formatSize+28, and turns the size into an
absolute end. A requested buffer larger than the payload becomes zero, which
selects a genuine whole-payload array read/create/delete path. The nonzero
path creates an empty buffer, requests half its size while retaining the
native ENTIREBUFFER Lock flag, reads that half into the first returned region,
sets half0/boundary-half/next-position-half+start, and Unlocks both reported
regions and lengths. All ignored results remain ignored.

Archive opening creates the actual unnamed, initially unsignaled event with
CreateEventA(0,0,0,0). While the BYTE busy flag at67138D is nonzero it waits20ms
on that event, then closes the event and sets the request byte at67138C.
Find takes only the archive string and retains the outer filename word;
unsized Seek returns the borrowed archive handle. Failure clears the request
and returns. Success records the entry base, resets to that absolute base
before each relative format/data seek, and performs the same whole/half paths.
It clears the request at the shared exit and never closes the archive handle.
The compatible BYTE declarations do not prove original volatile spelling or
synchronization correctness. No mutex, timeout policy or cleanup is added.

The loop readers scan binary RIFF metadata, correcting the earlier tentative
text-parser description. Each actual local byte array is **320 bytes**, proved
independently by ReadFile320 and the scan's signed i<320 bound. Disk input seeks
-320 from FILE_END and closes the owned file after reading. Archive input uses
sized Seek, retains outer filename plus size-reference words through Find,
and seeks entrySize-320 relative to the current entry base without closing the
borrowed handle. Its nonzero-size check still queries the whole archive file.
Small-entry subtraction, short-read behavior and absent error checks remain.

Every scanner has fifteen independently checked indexed byte reads: cue's
three-character prefix, its four bytes at+16..19, adtl's four-character prefix,
and its four bytes at+16..19. Native repeated shifts of8 assemble each DWORD.
If both values are nonzero, fields32/36 receive (cue+length)<<2 and length<<2;
missing markers retain old fields. No trailing-bound guard is added, so the
native potential read through index338 remains. The buffer is not enlarged.
Invalid/empty input zeros both fields and clears the request. A valid empty
disk handle is left open on that failure path. The second disk GetFileSize
result is genuinely stored once at00408710 / EBP-12 and never read; the source
retains that native capture from its first probe without adding dummy storage.

The exact special filename `wave\bgm\59.wav` bypasses event/claim work and
sets fields32/36 to0x60E8AC/0x5E0D90. The original text payload plus NUL is
checked against the source object and target. Only observed owner field views
at0/8/12/16/20/24/28/32/36/58/60 are used. No partial stream or archive owner is
instantiated, embedded or allocated; its full extent and original names remain
unknown. Archive context definitions and the five-word sound factory prototype
remain token-compatible with accepted source. Complete helper exits/array
thunks, actual Win32 imports and SDK COM packet widths are checked separately.

The first two open bodies already have the correct complete instruction shape.
One bounded measurement of103 genuinely observed local names resolves all
remaining fields, including the natural GS alignment around each actual320
byte array. The final source keeps the same real values and lexical scopes.
Four wrong physical bindings and three explicit packet mutations fail.
No buffer growth, source padding, inert locals, extra storage/scopes, fake
returns, manual EH, assembly, aliases, masks or cropped comparisons are used.

```bash
scripts/repo-python scripts/replay-exact-units.py --unit audio-record-open-file-00408110 --unit audio-record-open-archive-00408390 --unit audio-record-loop-file-00408670 --unit audio-record-loop-archive-00408900
```

All 225 prior units, 110 canonical objects, 178 source inputs, 218 origin files,
nine shared headers, 91 active drafts and 4,347 other function rows stay
unchanged. F009 plus169 additions retains578,392 code bytes and179 new inputs.
R017 roles remain through aliases. All97 unknown origins remain unknown.
Keep every f112 source/control, attested/native/CFG/packet/binary/SDK/helper/
name/binding/cold/parent input and all results, logs and PDBs.

Full CI passes **3,603 tests in 140.579 seconds**; seven exact-checkpoint
checks also pass. Target, tracking, progress and whitespace checks pass.
No old unit was cold-rebuilt.

Cleanup removes only two obsolete reproducible function probes and one
local-name measurement object / 40,309 bytes, plus 375 Python bytecode caches /
8,282,863 bytes, reclaiming 8,323,172 bytes. Final02 and the canonical object
agree on every complete body byte and all66 relocation records. Canonical
outputs, all source/compiler inputs, measurements, complete native/CFG/SDK/
packet/binary/helper evidence, results, logs and PDBs remain. Hash receipts
and preservation guards are in `.analysis/f112-object-cleanup.json`,
`.analysis/f112-preservation-cleanup.json` and
`.analysis/f112-final-compiler-inputs.json`. All225 old units,110 old objects,
178 source inputs,218 origin files,nine headers,91 active drafts and4,347
other function rows pass unchanged checks. No compiler or CI job remains active.

Current totals: **229 exact functions/units, 588,275 code bytes**, 29.81% of
reviewed authored bytes and **29.75% conservatively**, including every pending
byte. The 98% goal remains active and incomplete.

## F113 investigation at the F112 checkpoint

Continue complete R017 AudioStreamRecord::RefillBuffer `00408BD0` (1,724 bytes).
Its raw export is in `.analysis/f112-audio-record/native-00408bd0.asm` and its
initial metadata in `.analysis/f112-native-frontier.json`. Reconcile the full
code/data/exit extent and guarded flow before source; linear decoding alone
does not establish that reconciliation. Review every half-buffer/loop-boundary
policy, actual SDK packet and shared busy/request byte transition. The four
input methods and sound factory/device prerequisites are now exact.

Keep accepted source interfaces and dependencies unchanged; any necessary ABI
or header change requires replay of the affected units. Use pointer views of
actual fields and complete meaningful local values, never an allocated partial
owner. Preserve all old units, origins and active drafts, including the unknown
clear/destructor wrapper00409490. Keep compiler builds serial and remove only
obsolete reproducible outputs after retaining inputs and evidence. Resource
root00456B60 remains unaccepted with f107's real588-byte frame and unresolved
texture80/layout/meaningful filename bound. No fabricated padding or storage.

## Previous accepted functions: F111

Three complete R016 disk functions independently pass canonical cold comparison:
LoadWaveDirectory `004073D0..0040753E` (367 bytes), LoadSerializedFile
`00407540..00407694` (341), and SaveSerializedFile `004077E0..004079B7` (472).
All **1,180 code bytes, 398 instructions, 46 calls and 43 real relocation
fields** match. The following 1/11/8 INT3 bytes stay outside each extent.
Three reports share one serial cold object build. Complete ordinary CFGs and
stack joins agree with actual frames of 288/60/100 bytes below EBP and RET8/4/4.
No prior source, interface or header changes, so no old unit needs replay.

Directory loading writes the supplied count at owner offset16, releases and
zeros every previous buffer, invokes the actual storage-reset wrapper, then
assigns null pointer values by reference. Its filename is the original
`%s\%03d.wav`; explicit conversion to int supplies the correct %d varargs
type without changing emitted bytes. A real Windows MAX_PATH260 buffer was
chosen before comparison. The compiler produces the complete GS frame,
including its automatic rounding, without array growth or source padding.
This is a meaningful source-compatible SDK bound; the original declared bound
is not uniquely recovered from the native frame. Each existing file is opened
and closed before calling the accepted three-word wave loader. Its retained
literal zero survives the checked at() call on the stack.

The 19 byte wrapper at00409490 has a complete observed thiscall0 contract and
calls the storage Tidy body. The pinned VC7.1 vector clear and destructor both
call Tidy; this identity/ownership ambiguity remains unknown. ClearStorage is
only a provisional effect name in the pointer-only interface, not a new origin
claim. All 97 unknown origins, including this wrapper, remain unchanged.
No helper, library, compiler or global-data byte receives new exact credit.

Serialized input retains its initial Size call before CreateFileA, the redundant
SetFilePointer0, signed count, integral assign, presence byte, payload size,
complete WAVEFORMATEX18, and genuine payload allocation/deletion. Including
<new> naturally emits the actual array thunks. ReadFile results and the factory
result remain ignored. No extra COM Release is added before overwriting old
slots. The real five-word creation packet retains its zero across the unchecked
element lookup. The accepted wave and factory declarations remain identical.

Serialized output writes the signed container size, then presence1/0 for each
entry. A present entry uses the complete SDK DSBCAPS20 with dwSize initialized
to20, writes its buffer size before querying the complete 18 byte format, then
writes that format. The native GetCaps result is stored once at004078B9 /
EBP-80 and never read. The source preserves that genuine result capture from
the first probe; it is not newly invented frame storage. Other SDK results
remain ignored. The buffer is locked in full, and the first returned pointer
is written using caps.dwBufferBytes, not the reported first-region length.
Both returned regions and lengths go to Unlock in native order. File access,
failure exits and final CloseHandle behavior remain unchanged.

The first natural 341 byte loader already matches. A positive directory success
block removes the first control's extra two-byte continue jump. One bounded
measurement of 108 genuinely observed local names resolves 46 real save-frame
fields using the same actual SDK values and outputs. The final probe adds only
the truthful printf int conversion; all code and relocation records still
agree. Four wrong physical bindings and three explicit packet mutations fail.
No padding, inert locals, artificial buffers, extra storage, manual returns/EH,
assembly, aliases, masks or cropped extents are introduced. The partial sound
bank is never instantiated or embedded; its complete extent and original names
remain unknown. No direct callers or xrefs were found for these entrypoints;
runtime reachability is unclaimed, while independent R016 ownership is retained.

```bash
scripts/repo-python scripts/replay-exact-units.py --unit sound-bank-wave-directory-004073d0 --unit sound-bank-file-load-00407540 --unit sound-bank-file-save-004077e0
```

All 222 prior units, 109 canonical objects, 177 source inputs, 218 origin files,
nine shared headers, 91 active drafts and 4,348 other function rows stay
unchanged. F009 plus 165 additions retains 575,681 code bytes and 178 new inputs.
R016 historical roles remain through aliases. Keep f111 sources/controls,
attested/native/CFG/SDK/packet/GS/name/helper/binding/cold/parent inputs and
their complete results, logs and PDBs.

Full CI passes **3,603 tests in 133.969 seconds**; seven exact-checkpoint
checks also pass. Target, tracking, progress and whitespace checks pass.
No old unit was cold-rebuilt.

Cleanup removes only three obsolete reproducible function probes and one
local-name measurement object / 48,173 bytes, plus 375 Python bytecode caches /
8,282,863 bytes, reclaiming 8,331,036 bytes. The final03 probe and canonical
object have identical full bytes and all 43 relocation records. Probe02 has
identical code and bindings; its one internal literal name is SG57269 instead
of final03's SG57270 after the truthful printf conversion. Both complete
literal payloads/NULs, native address and all other record fields agree; both
original labels remain recorded. The initial strict cleanup assertion and its
refined literal check are retained in `.analysis/f111-cleanup.log` and
`.analysis/f111-cleanup-refined.log`. No actual code/data alias is introduced.

Canonical outputs, all compiler inputs, native/CFG/SDK/packet/name/helper
measurements and evidence, results, logs and PDBs remain. Hash receipts and
preservation guards are in `.analysis/f111-object-cleanup.json`,
`.analysis/f111-preservation-cleanup.json` and
`.analysis/f111-final-compiler-inputs.json`. All 222 old units, 109 old objects,
177 source inputs, 218 origin files, nine headers, 91 active drafts and 4,348
other function rows pass unchanged checks. No compiler or CI job remains active.

Current totals: **225 exact functions/units, 585,564 code bytes**, 29.67% of
reviewed authored bytes and **29.62% conservatively**, including every pending
byte. The 98% goal remains active and incomplete.

## F112 investigation at the F111 checkpoint

Bounded raw exports are retained in `.analysis/f112-native-frontier.json`
and `.analysis/f112-audio-record/`. They include the four selected bodies and
refill dependency. The open bodies call the accepted sound factory and array
thunks; archive paths additionally use the previously reviewed sized/unsized
seek helpers. Review actual archive handle ownership, SDK RIFF/WAVE reads and
loop-text parsing. No decoder/owner-layout/source/ABI acceptance is implied by
these linear exports, and no F112 source or credit exists yet.


Continue the complete R017 AudioStreamRecord input cohort: OpenFile `00408110`
(627 bytes), OpenArchiveEntry `00408390` (727), ReadLoopPointsFromFile
`00408670` (644), and ReadLoopPointsFromArchive `00408900` (713).
Review the real decoder/SDK/helper contracts, full CFGs, actual member views,
complete local values and lifetimes before writing source. Do not infer a full
stream owner extent from a partial interface or instantiate/allocate one.
The refill function `00408BD0` (1,724) can supply dependency evidence after
its full code/data/exit extent is reconciled; it is not yet reconstructed.

Preserve all old accepted units, source inputs, origins and active drafts,
including the unknown clear/destructor wrapper00409490. Replay only new or
affected units and keep compiler builds serial. Remove only obsolete
reproducible outputs after retaining inputs and evidence. The resource root
00456B60 remains unaccepted, with f107's real588-byte frame and unresolved
texture80/layout/meaningful filename bound. No fabricated storage or padding.

## Previous accepted functions: F110

The complete R015 wave loader `00406820..00406A13` (500 bytes) and PCM reader
`00406B80..00406DAE` (559) independently pass canonical cold comparison.
All **1,059 code bytes, 352 instructions, 42 calls and 52 real relocation
fields** match. The following 12/1 INT3 bytes stay outside their extents.
Two reports share one serial cold object build. No accepted source or shared
header changed, so no old unit needs replay. Both complete ordinary CFGs and
all stack joins agree, with actual frames of 108/48 bytes below EBP, one RET
per body, and AL0/1 on every ordinary return path.

The only actual loader caller keeps a literal zero across the checked vector
at() call, pushes the returned buffer8 slot address and filename, and cleans
three cdecl words. The loader body reads only its first two words. The source
preserves that third zero with a compatible DWORD formal; its original type
and name remain unknown. The reader receives four actual words and uses all
four. Imported/decompiled parameter counts are not acceptance evidence.

The reader owns two complete SDK MMCKINFO values of 20 bytes each: five real
FOURCC/DWORD fields, all explicitly zero-initialized in the parent, then copied
to the child before the parent receives WAVE. mmioOpenA receives a null
MMIOINFO pointer; there is no fabricated MMIOINFO local. It opens with
MMIO_READ | MMIO_ALLOCBUF, descends to FINDRIFF/WAVE, then descends to the next
fmt chunk with the native flag value 0. It reads exactly 18 WAVEFORMATEX bytes,
requires the PCM format tag, ascends, finds the data chunk with FINDCHUNK,
allocates the actual chunk size and reads precisely that count. SDK import
names, stdcall widths, field widths and packet order are independently checked.

Open failure displays its diagnostic without closing a null handle. Every
later failure closes the opened MMIO handle before displaying the exact
Japanese text. A payload short read leaves the allocated pointer in the
output and does not write the size. The loader immediately reports reader
failure and returns without freeing that allocation, preserving the native
leak. Later Create/Query/Lock failures and the successful copy path each
conditionally delete the real payload. No rollback or validation is added.

The loader releases and zeros a previous output before initializing its
temporary buffer and payload pointers. Its real local WAVEFORMATEX is 18
bytes, and its DSBUFFERDESC is the complete 36 byte SDK type. Reserved and
GUID fields are zeroed; the ordinary two-byte alignment gap after the format
is not an added source field. Device creation, Buffer8 QueryInterface followed
by unconditional temporary Release, whole-buffer Lock, first-region copy and
two-region Unlock preserve the native order and ignored results. The F109
DS8 producer, SDK vtable/GUID and GS evidence remain unchanged and hash-checked.

Natural new[]/delete[] expressions without including <new> emit the actual
scalar entry symbols with this pinned VC7.1 implicit-declaration profile.
The complete 14 byte scalar-new body passes flag1 and size to __nh_malloc;
the five byte delete tail jumps to free. R153/R154 ownership evidence remains
unchanged. Array-thunk substitutions fail full physical comparison. Library
allocation, memset, memcpy and GS helper bytes receive no new exact credit.
All original source names and the unused third formal's original type remain
unknown. No incomplete reconstructed owner is instantiated or embedded.

The first natural 500 byte loader already matches. The first reader uses an
abbreviated {0} initializer that emits a register clear plus four stores and
is 14 bytes shorter, with the two real chunk slots reversed. Explicit zeros
for all five actual SDK fields and a bounded 46-used-name compiler measurement
produce the correct complete body with the same real local values. No new
storage, scopes, padding, inert locals, fake returns, manual EH, assembly,
aliases, masks or truncated comparisons are introduced. Original CP932 payloads
and NULs bind their actual native occurrences, including the duplicate open
error texts. Four wrong physical bindings and three packet mutations fail.

```bash
scripts/repo-python scripts/replay-exact-units.py --unit shared-wave-load-00406820 --unit shared-pcm-read-00406b80
```

All 220 prior units, 108 canonical objects, 176 source inputs, 218 origin files,
nine shared headers, 91 active drafts and 4,349 other function rows stay
unchanged. F009 plus 162 additions retains 574,501 code bytes and 177 new inputs.
R015 historical roles remain through aliases. Keep every f110 source/control,
attested/native/CFG/packet/SDK/allocator/GS/name/binding/cold/parent input and
its results, logs and PDBs. All 97 unknown origins remain unknown.

Full CI passes **3,603 tests in 129.572 seconds**; seven exact-checkpoint
checks also pass. Target, tracking, progress and whitespace checks pass.
No old unit was cold-rebuilt.

Cleanup removes only two obsolete reproducible function probes and one
local-name measurement object / 30,105 bytes, plus 375 Python bytecode caches /
8,282,863 bytes, reclaiming 8,312,968 bytes. Canonical outputs, all compiler
inputs, measurements, complete evidence, results, logs and PDBs remain.
Hash receipts and preservation guards are in `.analysis/f110-object-cleanup.json`,
`.analysis/f110-preservation-cleanup.json` and
`.analysis/f110-final-compiler-inputs.json`. All 220 old units, 108 old objects,
176 source inputs, 218 origin files, nine headers, 91 active drafts and 4,349
other function rows pass unchanged checks. No compiler or CI job remains active.

Current totals: **222 exact functions/units, 584,384 code bytes**, 29.61% of
reviewed authored bytes and **29.56% conservatively**, including every pending
byte. The 98% goal is active and incomplete.

## F111 investigation at the F110 checkpoint

Further bounded raw exports for the three candidates and the assign/clear
helpers are retained in `.analysis/f111-native-frontier.json` and
`.analysis/f111-sound-bank/`. These exports alone do not establish their ABI,
source layouts or acceptance; no F111 source or credit exists yet.


Continue the complete R016 SoundBank disk cohort: LoadWaveDirectory `004073D0`
(367 bytes), LoadSerializedFile `00407540` (341) and SaveSerializedFile
`004077E0` (472). The wave loader, PCM reader, factory and device prerequisites
are now exact. The full directory-loader native body is retained in
`.analysis/f110-wave-streams/caller-004073d0.asm`. Review each full extent,
its actual SDK descriptions/format/buffer calls, physical member accesses,
true argument packets and meaningful filename bound before writing source.
Preserve pointer-only owners and do not instantiate a partial sound bank.

Retain all old exact units, shared headers, origins and active drafts. Replay
only new or affected units, keep compiler builds serial, and remove only
obsolete reproducible outputs after preserving inputs and evidence. The R045
resource root 00456B60 remains unaccepted with the f107 texture80/layout and
meaningful filename-bound frontier; its real frame is 588 bytes below EBP.
Do not manufacture storage, padding or larger arrays to resolve that frontier.

## Previous accepted functions: F109

Five complete R015 sound functions independently pass canonical cold comparison:
client constructor `00406610..00406647` (56 bytes), destructor
`00406650..004066B1` (98), error display `004066C0..004066DC` (29), initialization
`004066E0..00406816` (311), and buffer creation `00406A20..00406B7B` (348).
All **842 code bytes, 273 instructions, 26 calls and 58 real relocation fields**
match. Following INT3 alignment of 8/14/3/9/4 bytes stays outside each extent.
One serial cold object build produces five independent reports; no old unit
needs replay. All ordinary CFG edges and stack joins agree, with actual
frames of 4/4/0/44/64 bytes below EBP and plain RET on every exit.

The producer uses the actual CoCreateInstance import, CLSID_DirectSound8 and
IID_IDirectSound8, with flags 3 (INPROC_SERVER | INPROC_HANDLER). It initializes
the device, tries priority cooperative level with normal-level fallback, then
creates the deferred primary buffer. The shared client count resets both
pointers on its first acquisition and releases primary before device on its
last destruction. The complete main caller supplies a local client address
and explicit ordinary cleanup sites. The reconstruction only defines this
partial owner's lifetime bodies; it never instantiates or embeds that owner.
Original client extent, source names and counter signedness remain unknown.

Both actual local descriptions are complete SDK DSBUFFERDESC values, including
dwReserved and the GUID member, with a measured sizeof of 36. Their native
memset clears all nine words. Primary flags are PRIMARYBUFFER | LOCDEFER;
secondary flags are CTRLVOLUME | GLOBALFOCUS | GETCURRENTPOSITION2 | LOCDEFER.
All three complete GUID payloads are checked against the pinned SDK. Every COM
slot and packet width is independently derived from that SDK, including the
receiver word. PE imports prove CoCreateInstance and MessageBoxA identities.
The original Japanese diagnostic payloads and DSound-Error title remain exact;
hex escapes preserve CP932 text without depending on the host source code page.

Creation releases and zeros the previous output before initializing its
temporary base buffer. It queries IID_IDirectSoundBuffer8, then releases that
temporary even when QueryInterface fails. Null data skips Lock and copy.
Nonnull data locks the entire buffer, copies exactly the supplied size into
the first returned region, and passes both reported pointers and lengths to
Unlock, ignoring its result. Failures preserve native ownership and ordering;
no rollback or input validation is added. The five-word cdecl Create prototype
in the old stream source remains unchanged. Native reads only four words;
the unused fifth formal's original type/name remain unknown, and the compatible
DWORD carrier preserves the observed zero. Both boolean functions return AL0/1
on every ordinary path. ShowError ignores the SDK result; its original source
return declaration remains unknown and no fake source return is introduced.

An explicit /GS reproduces the two real cookie sequences. The complete 14 byte
check helper preserves AL on its normal return; its failure tail remains in
vendor code. /GX- is an explicit reproducibility setting, not proof of an
executable-wide original profile. The first probe lacks the cookie and initializes
the temporary too early; the second corrects those facts and leaves 27 actual
factory frame fields. One bounded measurement of 78 genuinely observed local
names supplies meaningful names and declaration order for the same seven real
values. Final probe and canonical object agree on every physical operand.
No padding, inert locals, extra storage, manual returns/EH, assembly, aliases,
masks or cropped comparisons are used. Four wrong physical bindings and three
explicit packet mutations fail. Whole memset96 and the retained complete
memcpy829 review receive no new library/helper code credit.

```bash
scripts/repo-python scripts/replay-exact-units.py --unit shared-sound-client-constructor-00406610 --unit shared-sound-client-destructor-00406650 --unit shared-sound-error-004066c0 --unit shared-sound-initialize-004066e0 --unit shared-sound-create-00406a20
```

All 215 prior units, 107 canonical objects, 175 source inputs, 218 origin files,
nine shared headers, 91 active drafts and 4,346 other function rows stay
unchanged. F009 plus 160 additions retains 573,442 code bytes and 176 new inputs.
R015 roles remain through aliases. Keep f109 parent, native/attested/SDK/CFG/
packet/GS/name/binding/cold evidence, compiler inputs, results, logs and PDBs.

Full CI passes **3,603 tests in 143.571 seconds**, together with seven exact
checkpoint tests and three runtime-origin tests. Target, tracking, progress and
whitespace checks pass. No old unit was cold-rebuilt.

Cleanup removes only three obsolete reproducible function probes and the one
local-name measurement object / 48,766 bytes, plus 375 Python bytecode caches /
8,282,863 bytes, reclaiming 8,331,629 bytes. Canonical outputs, all sources,
complete evidence, measurements, results, logs and PDBs remain. Hash receipts
and preservation guards are in `.analysis/f109-object-cleanup.json`,
`.analysis/f109-preservation-cleanup.json` and
`.analysis/f109-final-compiler-inputs.json`. The 215 old units, 107 old objects,
175 source inputs, 218 origin files, nine headers, 91 active drafts and 4,346
other function rows pass unchanged checks. No compiler or CI job remains active.

Current totals: **220 exact functions/units, 583,325 code bytes**, 29.56% of
reviewed authored bytes and **29.50% conservatively**, including every pending
byte. All 97 unknown origins remain unknown. The 98% goal is active and incomplete.

## F110 investigation at the F109 checkpoint

Continue the complete R015 wave-buffer loader `00406820` (500 bytes) and its
reader `00406B80` (559). Full native exports are retained in
`.analysis/f109-sound-factory/native-00406820.asm` and
`.analysis/f109-sound-factory/callee-00406b80.asm`; the first reader export
alone is not ABI/source/layout acceptance evidence. The underlying device,
factory and shared lifetime policies are now exact in SharedSound406610.cpp.
Reconcile the real MMIOINFO/chunk/WAVEFORMAT layouts, all SDK packets, source
allocation/deallocation identities, native ignored results and failure ordering
before accepting either new body. Preserve complete SDK values and meaningful
locals, and never instantiate or embed an incomplete reconstructed owner.

The R045 resource root 00456B60 remains unaccepted. Its texture80 base/layout
and meaningful filename bound remain unresolved; retain the f107 frontier and
588 byte frame refinement. Do not guess an array bound or fabricate storage.
Preserve all old exact units, origins, headers and active drafts. Replay only
new or affected units, keep compiler builds serial and remove only obsolete
reproducible outputs after preserving their inputs and evidence.

## Previous accepted functions: F108

The complete R070 parser `00420880..0042117C` (2,301 code bytes), both R153
record lifetimes `00421200..00421217` (24) / `00421220..0042124A` (43), R212
sequence constructor `00421250..0042129A` (75) and R257 sequence destructor
`004212A0..004212E7` (72) independently pass canonical cold comparison.
All 2,515 code bytes, 701 instructions, 100 calls and 132 real relocation
fields match. The parser additionally compares all 128 dispatch bytes:
seven DWORD entries at42117D and 100 selectors at421199. None earns code credit.
Three/eight/five/five/eight following INT3 bytes remain outside. Five independent
reports share one serial cold object build; no old dependency replay is needed.

A natural signed-char switch emits the same states 0/1/2/3/4/99, unsigned range
guard 99, seven actual targets and both complete tables. The former failed
decompile supplies no source or ABI proof. Full native CFGs and stack joins
cover every instruction, with actual frames128/4/8/16/16 belowEBP and RET8 for
the parser /RET0 for the lifetimes. Every real local table relocation binds to
the actual function plus its actual COFF label offset. No branch destination,
frame slot, operand or table byte is aliased, masked or cropped.

The source retains the complete language policy. State 0 handles #/B/P/E/N/
F/M/W/V/R, parentheses and quotes, consumes one byte and updates token start.
P/E/N append kinds 0/1/2; F/M/W/V/R append kinds 10..14 then scan a decimal value.
B scans a signed 16 bit group number; a nondigit appends an empty sequence and
writes the new group index without consuming that delimiter. Numeric record
arguments likewise reprocess the nondigit in state 0. Parentheses initialize
the value to-1 and match the eleven original two-byte CP932 prefixes, consuming
two bytes on a match and one otherwise. Quoted text allocates length+1, stores
the owned pointer, captures it, copies the substring and terminates it with 0.
Only LF ends comments. No new escape, clamp, EOF guard or default-state cursor
advance is added. Signed16 accumulation and narrowing retain native behavior.

Original two-byte token payloads plus their NUL are independently checked
against the source object's literals. Escaped byte literals preserve the real
text encoding without relying on the compiler host's source code page; they
are language tokens, not target code arrays. Every one of the100 call packets
and receivers is checked, including outer record-reference arguments across
nested back() calls, the eight separate record scopes, the sequence scope,
all strncmp lengths and the allocation/copy counts. The old complete R025/R102
memcpy CFG/data evidence remains; its embedded tables are not disassembled as
new instructions and no helper/library byte receives credit.

The 8-byte source-compatible record contains kind0, a 16 bit value at2 and an
owned text pointer4, with ordinary one-byte alignment. Its constructor only
zeros text; kind/value remain uninitialized. Its destructor conditionally
array-deletes text without resetting it. Original field signedness is not
uniquely proved by writes; the compatible short carrier and local signed 16 bit
accumulator are distinguished. The 20 byte sequence contains the complete
vendor deque<Record8> at 0, explicitly clears in its constructor and clears
before automatic member destruction. Complete fields, member lifetimes,
container strides and observed stack extents justify these two values. Original
names, grouping and copy declarations remain provisional. The script/group
owner interfaces remain pointer-only and are never instantiated. The old
ScriptResource4205F0 interface is token-identical in the new source file;
all accepted caller bodies and headers remain unchanged.

All three complete EH graphs independently match118 code plus 172 data bytes
and all 31 real fields. The parser's nine states each unwind to-1 and destroy
its eight record values /one sequence. Constructor/destructor graphs each have
one member-cleanup state. All registrations, cleanup bodies, full unwind maps
and FuncInfo records agree. These 290 compiler bytes receive no exact credit.
Natural C++ scopes emit these lifetimes; no manual EH or fake returns are used.
The first five natural body shapes and all scope slots already agreed; four
meaningful scalar names, selected from retained prior compiler measurements,
resolve the 117 real frame fields. No padding, inert locals or artificial arrays
were added. Four actual wrong-field comparisons and three explicit packet
mutation comparisons fail; the latter are not compiled source variants.

```bash
scripts/repo-python scripts/replay-exact-units.py --unit script-parser-00420880 --unit script-record-constructor-00421200 --unit script-record-destructor-00421220 --unit script-sequence-constructor-00421250 --unit script-sequence-destructor-004212a0
```

All 210 prior units, 106 canonical objects, 174 source inputs, 218 origin files,
nine shared headers, 91 active drafts and 4,346 other function rows stay
unchanged. F009 plus 155 additions retains 572,600 code bytes and 175 inputs.
Keep all f108 source/name controls, native/attested/layout/CFG/packet/CP932/
EH/binding/cold/parent evidence and results/logs/PDBs. All historical
R070/R153/R212/R257 roles remain by aliases. All 97 unknown origins and older
drafts receive no credit.

Full CI passes **3,603 tests in 124.341 seconds**. The initial four historical
fixture failures are retained in `.analysis/f108-ci.log`. Four test adapters
now reverse only hash-pinned approved exact transitions before reversing older
origin transitions; immutable origin evidence/verifiers and rejection of
unapproved changes remain intact. Related 64 historical tests and seven
checkpoint tests pass. Target, tracking, progress and whitespace checks pass.

Cleanup removes only two obsolete reproducible F108 objects / 55,021 bytes
and Python bytecode caches / 8,282,863 bytes (8,337,884 bytes total). Canonical
objects, all compiler inputs, name measurements, native/CFG/ABI/EH evidence,
results, logs and PDBs remain. Hash receipts and complete preservation guards
are in `.analysis/f108-object-cleanup.json`,
`.analysis/f108-preservation-cleanup.json` and
`.analysis/f108-final-compiler-inputs.json`. No old unit was rebuilt.

Current totals: 215 exact functions/units, 582,483 code bytes, 29.51% of
reviewed authored bytes and 29.46% conservatively including all pending bytes.
The 98% goal remains active and incomplete.

## F109 investigation at the F108 checkpoint

Continue the resource chain through the complete 348 byte R015
SharedSound::CreateBuffer at `00406A20`. Its full native body, AL0/1 normal-return
flow, output IID_IDirectSoundBuffer8 and actual five-word cdecl caller packet
were reviewed in F107. Reconcile the complete SDK DSBUFFERDESC (36 bytes), all COM
packets, shared device producer, true GS/frame/locals and meaningful source
before acceptance. Keep the existing SoundCreation406A20 declaration in
ResourceStreams4205F0.cpp identical. The native body reads only four of the
five caller words; the original unused fifth formal type/name is unknown.
A compatible DWORD carrier preserves the actual zero; do not turn it into an
invented flag policy or erase the fifth argument. No F109 source or credit yet.

The nearby complete shared-sound initialization (311 bytes) / wave loader (500 bytes) bodies can
supply independent device/format/lifecycle evidence if needed. Inspect their
actual target contracts before choosing an interface or SDK call. Preserve
all old accepted units, origins, headers, compiler inputs and drafts. Do not
replay old exact callers unless their source/interface dependencies change.

The R045 resource root 00456B60 still has no accepted source or credit. Its
80-byte texture base/layout and meaningful filename bound remain unresolved;
retain the f107 frontier and 588 byte frame refinement. Do not instantiate the
old partial graphics client or manufacture padding/raw storage/array growth.

## Previous accepted functions: F107

R070 script archive loader `004205F0..004206C8` (217 bytes), R040 script
file loader `004206D0..00420871` (418 bytes) and R016 sound archive loader
`004076A0..004077D5` (310 bytes) independently pass canonical cold comparison.
All 945 code bytes, 328 instructions, 29 calls and 29 actual relocation fields
match. Seven/fourteen/ten following INT3 bytes remain outside. Actual frames
are 40/44/60 bytes with RET8/RET12/RET8. One new source file leaves every prior
source/header intact. Three independent reports share one serial cold object
build; no old dependency replay is needed.

Both archive lookups have one cdecl archive-name parameter. The sound caller
retains filename on the stack; the script caller retains filename plus the
size address. The 180-byte sized seek method returns the borrowed handle from
context0 and writes the record's size at100 after seeking to record offset104.
It has two parameters and RET8. The older decompile's extra apparent lookup
arguments are disproved by complete bodies and actual stack cleanup. Archive
handles are borrowed and are not closed by either loader. The script archive
loader always applies the byte transform before parsing and deletes its array.

The disk loader owns both CreateFileA handles. Mode2 decodes the input buffer;
other input modes pass it directly to the parser. It closes the input handle
before mode1 optionally creates an output, transforms the same post-parse
buffer, writes it and closes the output. SDK results remain ignored and the
native error/cleanup order stays unchanged. All three transform loops preserve
unsigned byte keys99/98, key+=step, step+=66, wrapping stores and signed char
payload loads. An explicit XOR assignment reproduces the target's load order;
compound XOR is a retained same-size nonexact control.

The sound loader retains its initial size call before lookup, then reads the
signed entry count, assigns the slots to zero, reads each presence byte and,
when nonzero, reads payload size, the complete SDK WAVEFORMATEX18 and payload.
It passes the actual slot address to the creation helper, followed by temporary
array deletion. No partial sound/script/archive owner is instantiated. The
local SDK format is complete; file-sized char arrays are genuine payloads.
No guessed complete owner or artificial storage is introduced.

The entire 348-byte creation helper proves an AL0/1 return and its QueryInterface
GUID matches the pinned SDK IID_IDirectSoundBuffer8. The final source declares
bool and the correct interface pointer. The first probe's void/base-interface
prototype was corrected from this independent callee evidence; ignored caller
results and pointer width cannot prove those facts from matching caller bytes.
There are five actual cdecl argument words and caller cleanup20. The native
body reads only the first four; the original unused fifth formal type/name
remains unknown, and its actual literal zero is retained with a compatible
DWORD carrier. The 50-byte vector helper is integral assign, not a preserving
resize; the final interface names it Assign.

Every normal CFG edge/stack join and all 29 call packets, including thirteen
SDK packets and nested outer arguments, are reviewed. The parser dependency's
complete 2,301-byte/633-instruction ordinary CFG is recovered independently of
the failed decompile: its seven DWORD targets and all100 selector bytes are
bounded by the actual range guard. Its one RET8 and parameters at EBP+8/+12
agree with both callers. The 128 dispatch bytes lie outside its old code extent
and are explicitly retained. This is ABI/dependency evidence, not parser source,
EH reconstruction or new code/data credit. Three actual physical binding
controls and three explicit packet mutation controls fail; the latter are not
compiled source variants. Native imports are checked from the pinned PE.

Bounded compiler measurements select meaningful used local names/declarations.
Final natural source matches all real bytes without padding, inert locals,
manual EH/returns, assembly, frame aliases, masks, array growth or cropped
extents. Actual array-new/delete entry identities are preserved, including
their difference from scalar aliases. Original names and complete owner layouts
remain provisional. All historical R070/R040/R016 roles remain by aliases.

```bash
scripts/repo-python scripts/replay-exact-units.py --unit script-archive-load-004205f0 --unit script-file-load-004206d0 --unit sound-archive-load-004076a0
```

All 207 prior units, 105 canonical objects, 173 source inputs, 218 origin files,
nine shared headers, 91 active drafts and 4,348 other function rows stay
unchanged. F009 plus 150 additions retains 570,085 code bytes and 174 inputs.
Keep all f107 source/prototype/name controls, native/attested/CFG/packet/import/
ABI/binding/cold/parent/frontier evidence and results/logs/PDBs. All 97 unknown
origins and older drafts receive no credit.

Current totals: 210 exact functions/units, 579,968 code bytes, 29.39% of
reviewed authored bytes and 29.33% conservatively including all pending bytes.
The 98% goal remains active and incomplete.

Final F107 CI passes 3,603 tests in 134.710s. The initial run exposed one
R228 test fixture still comparing an exact parent against its historical
unimplemented row. The fixture now uses the existing hash-pinned exact-adoption
projection, which accepts only the complete approved before/after transitions
and rejects other metadata. The immutable R228 verifier/evidence and all
negative guards remain intact. Fourteen focused provenance tests and seven
checkpoint tests pass before the full rerun; both CI logs remain. No source,
header, ABI or compiler profile changed for this fixture correction, so no
additional cold replay was needed.

Bounded cleanup removes six obsolete reproducible probe/control objects
(75,337 bytes) and 8,282,863 bytes of Python caches, with per-file hash receipts.
Canonical outputs, every source/control input, complete evidence, results,
logs and PDBs remain.

## F108 investigation at the F107 checkpoint

Continue the resource chain through the complete R070 parser `00420880`:
2,301 code bytes /633 instructions, seven DWORD dispatch entries at `0042117D`
and100 selector bytes at `00421199`. Code plus both tables span2,429 bytes,
followed by three INT3 bytes before `00421200`. Reconcile the complete switch,
all states/exits, true two-parameter thiscall ABI, ownership and EH graph before
natural source. The old decompile failed at the indirect jump and exposed an
incorrect extra parameter; use the attested query plus the f107 full native
export/ordinary CFG/table evidence. No parser source or exact credit yet.

Keep ScriptResource4205F0's interface identical if implementing Parse in a new
source file; old caller bodies and headers need not change. Preserve all old
accepted units, origins and draft inputs. This independently reviewed authored
function can progress while the resource root's layout/buffer proof stays open.

The complete1,186-byte R045 resource root `00456B60` remains unaccepted.
The f107 frontier independently retains both texture-vector COM pointer
carriers, actual deque element width4 from the complete177-byte Tidy/R072,
and paired global-only graphics-client lifecycle bodies. Those methods alone
do not prove the original base size or unused prefix; the old partial client
interface still cannot be instantiated or embedded. Do not invent a vptr,
padding fields, raw storage, size-ignoring new or byte arrays to make80.
The 24-byte command model's color mask20 is proved and remains uninitialized
by its constructor. Keep its other real members/defaults unchanged.

Use the refined resource frame evidence: subESP0x240 reserves576 bytes after
a12-byte EH registration, giving588 bytes belowEBP. This is atEBP-576 and the
last temporary atEBP-588. Earlier frozen notes'576-byte whole-frame shorthand
is superseded by the f107 refinement, without overwriting their pinned inputs.
The532-byte span between filename EBP-548 and cookie EBP-16 is still not a
proved array bound. No buffer growth or incomplete-owner allocation was used.

## Previous accepted function: F106

R045 fighter pattern loader `00457660..004584CF` (3,696 bytes) independently
passes canonical cold comparison as FighterPattern457660::Load. All 1,091
instructions, 26 branches, 158 calls and 171 real relocation fields match.
The next function begins immediately at `004584D0`; no alignment or table byte
is credited. One new implementation file leaves all prior sources and headers
intact. The actual 568-byte GS/C++ EH frame and RET0 are preserved.

The loader builds a default frame value, formats the character pattern path,
and borrows the archive context/handle using the already reviewed one-name
cdecl lookup and one-filename thiscall seek. Filename remains live on the stack
during lookup. It clears and deletes existing sequences, clears/reassigns the
slot vector, then reads each sequence and frame in native order. SDK results
remain ignored; no CloseHandle or new archive ownership is added. All eighteen
direct callees retain complete extents and real return cleanup. Every ordinary
CFG edge is reachable and stack joins agree, including nested helper calls
while outer SDK arguments remain live.

All 47 ReadFile packets are independently traced. Modes 0/1/2, the extension's
initial two-byte field followed by a one-byte read at overlapping offset1,
its four one-byte reads, the signed short scratch and actual float
conversions are retained. One short supplies three `0.01f` stores; three later
reads convert separately to float. The frame angle uses the actual `0.001f`
constant, and its scales use `0.01f`. Raw serialized 16-byte records feed two
distinct vectors at offsets84/100. Complete source-compatible 16/116/20-byte
values use real serialized fields, members and natural alignment. Their
extents are independently anchored by full constructors, memset16/116,
new20, the complete iterator's multiply-by116 and box capacity's divide-by16.
The opaque box element is never instantiated; its vector uses the complete
vendor layout with externally defined lifetimes. The fighter, slot and other
helper owners remain pointer-only. No missing owner bytes are supplied as
arbitrary storage. Original names, grouping and box element declarations stay
unknown.

The meaningful filename bound remains SDK MAX_PATH260 through every probe.
The first full natural source emitted all 1,091 instructions and the full frame,
with different real local positions. Bounded compiler controls measure genuine
used names and declaration order. The final seven differences were a real
pointer temporary: `assign(count, 0)` materializes a null pointer bound to the
const reference at EBP-476 after the deletion temporaries. Directly passing
zero reproduces this naturally. The accepted source adds no named null local,
padding, inert storage, manual returns/EH, assembly, frame aliases, masked
fields, array growth or cropped extent.

The entire generated cleanup/registration section (35 bytes) and unwind map/
FuncInfo (44 bytes) independently match all seven real fields. State0 destroys
the default frame at EBP-444; state1 deletes a failed sequence allocation at
EBP-484 and then unwinds to state0. The whole 44-byte generated scalar deleting
CODECOMDAT independently matches its destructor/delete targets; it has no
function definition AUX, so no AUX-sized extraction is claimed. Neither these
compiler bodies nor support helpers receive code credit. Three actual wrong
binding comparisons and three explicit SDK/call-packet mutation comparisons
fail. The latter are packet controls, not compiled source variants.

```bash
scripts/repo-python scripts/replay-exact-units.py --unit fighter-pattern-load-00457660
```

Only this new unit is cold-built. All 206 prior units, 104 canonical objects,
172 source inputs, 218 origin files, nine shared headers, 91 active drafts and
4,350 other function rows stay unchanged. F009 plus 147 additions retains
569,140 code bytes and 173 inputs. Keep all f106 native/attested/CFG/packet/
layout/EH/binding/cold/parent evidence, every compiler/source/name control and
results/logs/PDBs. Existing frozen f105 root notes remain unchanged. All 97
unknown origins and older drafts receive no credit.

Current totals: 207 exact functions/units, 579,023 code bytes, 29.34% of
reviewed authored bytes and 29.29% conservatively including all pending bytes.
The 98% goal remains active and incomplete.

Final F106 CI passes 3,603 tests in 124.209s. Bounded cleanup removes seven
obsolete reproducible probe/control objects (108,444 bytes) and 8,282,705 bytes of
Python caches, with per-file hash receipts. Canonical outputs, all source and
compiler inputs, complete evidence, results, logs and PDBs remain. The refined
final name-selection receipt explicitly distinguishes the earlier named-zero
controls from the accepted literal-zero pointer-reference temporary.

## F107 investigation at the F106 checkpoint

Continue the complete 1,186-byte R045 fighter resource loader `00456B60`.
Its pattern-loading prerequisite is now accepted above; the F105 bitmap
lifecycle prerequisites remain exact. The root still has no accepted source
or exact credit. Preserve its original f105 exports/attestation/caller/index/
ABI notes, together with the f106 dependency decompile and field scans.

The 24-byte command owner now has independent complete member evidence:
texture pointer0, actual list12 at4, signed sampling byte16, signed capacity
word18 and DWORD color mask20. The constructor defaults byte16 to5 and word18
to15 and leaves color mask20 untouched. Full setter `00410FE0` stores20 and
full renderer `00411110` ANDs that mask with each element's color. The earlier
missing-field question is resolved; this does not yet accept that owner's
constructor or claim original type names. Its list element remains opaque.

The 80-byte texture owner still needs an independently justified complete
allocatable model. Its constructor calls the graphics client base and actual
vectors at8/24/40, a deque at56, then sets palette pointer4 and format byte76.
The first vector has a 44-byte stride; its 22-byte constructor wrapper calls
the accepted bitmap constructor at0 but does not establish extra fields or the
full base extent. The existing graphics client partial declaration still
cannot be instantiated or embedded. Recover actual member/base evidence;
do not invent a vptr, padding fields, raw storage substitutes, size-ignoring
new, or opaque byte arrays to manufacture allocation80.

Reconcile the root's real GS/EH cleanup/scope graph and meaningful filename
bound. Its decompiled 532-byte array is not a proved bound. Keep actual three
constructor new expressions/null checks/cleanup states, character/archive-key
comparisons, signed palette+1, diagnostics, script loads, notice-mode call and
final virtual slot0x18 in native order. Do not grow arrays to force a frame
match. Preserve all old accepted units, origins, headers and draft inputs.

## Previous accepted functions: F105

The R021 bitmap lifecycle bodies at `0041A2D0..0041A308` (57 bytes),
`0041A310..0041A378` (105 bytes) and `0041A380..0041A3CA` (75 bytes)
independently pass canonical cold comparison. All 237 code bytes, 80 instructions,
two actual relocation fields and complete reachable CFGs match. Seven/seven/five
following INT3 bytes remain outside. One new implementation file leaves every
previous source and header intact. Three unit reports share one serial cold
object build; no old dependency replay is needed.

Natural constructors preserve EAX=this and RET0/RET4, rather than adding a
manual return. Both initialize format+0, pixels+28, palette+20, encoded size+16
and palette ownership+24, in that order. The format overload accepts exactly
8/16/24/32 and otherwise stores zero. Width, height, stride and any other
unobserved fields remain untouched. The destructor tests pixels, deletes them
when nonnull, then deletes the palette only when the ownership byte is set.
It retains the native lack of pointer resets. Its frame is 12 bytes; both
constructors use four bytes. Every real branch, stack join and RET is reviewed.

The two delete fields bind to the actual R142 five-byte scalar operator-delete
thunk at `00640F15`, which jumps to the CRT implementation. The underlying
free destination and array-delete thunk are distinct targets; both negative
binding controls fail. Minimal SDK headers naturally emit the observed scalar
identity for these byte/word array deletes with this compiler profile. This is
a reproducible compiler observation, not an executable-wide compiler claim.
The complete 22/19-byte direct caller wrappers preserve the ECX object and RET0.
Attested decompile, caller and xref queries are complete; the format overload
has no recovered xrefs. Constructor/destructor identities and names remain
source-compatible inferences. No helper/library byte receives new credit.

The owner remains a pointer-only interface and is never instantiated or
embedded. A 44-byte vector element stride does not establish the complete
extent or extra fields of the base reached by its 22-byte constructor wrapper.
No padding, invented fields, inert locals, manual returns, assembly, frame
aliases, masked relocation fields or cropped extents were introduced. The first
natural source already matched every physical byte.

```bash
scripts/repo-python scripts/replay-exact-units.py --unit bitmap-default-constructor-0041a2d0 --unit bitmap-format-constructor-0041a310 --unit bitmap-destructor-0041a380
```

All 203 prior units, 103 canonical objects, 171 source inputs, 218 origin files,
nine shared headers, 91 active drafts and 4,348 other function rows stay
unchanged. F009 plus 146 additions retains 565,444 code bytes and 172 inputs.
Keep all f105 lifecycle source, native/attested/caller/xref/CFG/binding/cold/
parent evidence and compiler inputs/logs/PDBs. Existing frozen f105 root notes
are retained unchanged. All 97 unknown origins and old drafts receive no credit.

Current totals: 206 exact functions/units, 575,327 code bytes, 29.15% of
reviewed authored bytes and 29.10% conservatively including all pending bytes.
The 98% goal remains active and incomplete.

Final F105 CI passes 3,603 tests in 132.300s. Bounded cleanup removes one
obsolete reproducible probe object (9,747 bytes) and 8,282,705 bytes of Python caches,
with per-file hash receipts. Canonical outputs, source inputs, complete
evidence, logs and PDBs remain.

## F106 investigation at the F105 checkpoint

Continue the complete 1,186-byte R045 fighter resource loader `00456B60`,
retaining the original f105 root exports/attestation/caller/index/ABI notes.
This root still has no accepted source or exact credit. It allocates two
80-byte texture owners and one 24-byte command owner through actual constructor
new expressions, three null checks and EH cleanup states 0/1/2. Establish
complete allocatable types before source; existing pointer-only interfaces
cannot be instantiated. Do not substitute padding classes, raw storage,
custom size-ignoring new, or manual exception handling.

The complete `0040AD80` constructor calls the accepted graphics client base,
then vector constructors at offsets 8/24/40 and a deque constructor at 56;
these are actual members, not invented scalar tail fields. The last format
byte is at 76. The vector at 8 has an observed 44-byte element stride. The
bitmap lifecycle acceptance above establishes behavior, not the full element
layout or the types of its remaining fields. Recover those fields and actual
vector/deque element types from their complete users and existing origin
evidence. `00410F30` constructs a list at offset4, stores its texture owner at
0 and defaults at bytes16/18; the rest of the 24-byte command owner is still
unresolved. Its clear method only calls list clear and supplies no missing
field evidence. Keep these distinctions explicit.

Reconcile the root's real GS/C++ EH graph, cleanup thunks/scope data and meaningful
filename-buffer bound before compiling. Its native handler is `00656155`,
cookie global `0066FE30` and check helper `00640611`. Its decompiled 532-byte
array is not a proved bound. Do not enlarge arrays to fit the frame. Real
character comparisons, archive keys, signed palette+1, three diagnostic calls,
pattern/script loads, final notice mode and virtual slot0x18 must remain in
native order. Preserve all old accepted units, origin evidence and draft inputs.

## Previous accepted functions: F104

R019 archive texture-pack loader `0040BBA0..0040BF35` (918 bytes) and its
default wrapper `0040BB80..0040BB9E` (31 bytes) independently pass canonical
cold comparison as TexturePackArchive40BBA0::Load/LoadDefault. All 949 code
bytes, 333 instructions and 38 real relocation fields match. Ten/one following
INT3 bytes remain outside. The main has three parameters/RET12; the wrapper
has two/RET8 and passes exactly zero for palette selection. Both historical
R019 roles remain by aliases. One new implementation file leaves all old
sources and headers intact.

Entry count is obtained before archive lookup. The caller prepares filename,
then calls a true one-argument cdecl archive-name lookup while that filename
remains live on the stack. Lookup returns a borrowed context or null. Its
result becomes ECX for a one-filename thiscall seek method with RET4. The older
root decompile's apparent second lookup argument is disproved by the complete
113-byte callee: only EBP+8 is read. The complete 164-byte seek method compares
entry names, positions the existing handle from context+0 at the directory
record's offset104, and returns that same handle or INVALID_HANDLE_VALUE.
There is no added null guard, CreateFileA, redundant initial seek or CloseHandle.
The context and handle remain borrowed; their complete layouts are unknown.

The full normal lookup/list/deque/strcmp graph and two explicit existing
library range-error boundaries retain 36 complete bodies/1,705 bytes. All
34 normal support CFGs pass actual stack/return checks. Equality/inversion,
iterator initialization/next-node/payload-address behavior and seek arguments
are reviewed. The original range-error bodies retain their throw calls and
prior library classification; their broader EH/runtime graph is not claimed
as new source reconstruction. No helper/library byte receives new exact credit.

The rest preserves signed palette count/selection, negative seek offsets,
actual zero default, ignored SDK results and eleven ReadFile packets. The
complete 24-byte descriptor repeats accepted definitions; metadata stays
4/4/4/1/4 bytes and the three actual payload-size forms stay unchanged. Entry
format/palette/flag initialization, serialized deep copy, temporary deletion,
texture creation, palette refresh and final pixel deletion/clear remain in
native order. All fourteen SDK calls, nine entry lookups and the texture-slot
lookup preserve their real nested four/eight/twelve-byte packets. Word/byte
factory values occupy the actual DWORD carriers without invented upper bits.
Partial owner/context interfaces remain pointer-only and are never constructed.

Both real callers are checked. The complete 1,186-byte fighter resource loader
has two calls with the actual archive keys `datab` and `data`, a filename-local
address and signed palette field+1. Literal bytes are verified from the target.
The default wrapper forwards both string arguments and zero. Six wrong-ABI,
three helper wrong-ABI and two wrong-binding controls fail. The first natural
source already matches every byte, including complete 76/4-byte frames; no
local-placement controls, padding, inert storage, assembly, aliases, masks or
cropped extents. Separate cold reports cover both new units in one serial
object build. No old dependency replay is needed.

```bash
scripts/repo-python scripts/replay-exact-units.py --unit texture-pack-archive-0040bba0 --unit texture-pack-archive-default-0040bb80
```

All 201 prior units, 102 canonical objects, 170 source inputs, 218 origin files,
nine shared headers, 91 active drafts and 4,349 other function rows stay
unchanged. F009 plus 143 additions retains 565,207 code bytes and 171 inputs.
Keep all f104 native/attested/ABI/normal-graph/library-boundary/caller/import/
physical/cold/parent records and source/control results/logs/PDBs. All 97 unknown
origins and old drafts receive no credit. Original names/grouping/layouts stay
provisional despite exact emitted bytes.

Current totals: 203 exact functions/units, 575,090 code bytes, 29.14% of
reviewed authored bytes and 29.09% conservatively including all pending bytes.

Next F105 is the complete 1,186-byte fighter resource loader `00456B60` from
these archive callers. Reconcile its full resource/filename setup graph,
actual character/palette fields, SDK-sized buffers, physical frame and ABI
before natural source. It has two real archive calls as reviewed above.
No F105 source or exact credit yet. The 98% goal remains active and incomplete.

Final F104 CI passes 3,603 tests in 135.054s. Bounded cleanup
removes one obsolete reproducible probe object (13,919 bytes) and
8,282,705 bytes of Python caches, with per-file hash receipts.
Canonical outputs, all source inputs, complete evidence, logs and PDBs remain.
Independent full R052 open/R175 release bodies corroborate responsibility for
the context's stored handle; their observed open/store/close instructions are
retained without new credit. F105 native/dependency index, completed own root
decompile/caller query and bounded ABI notes are retained privately.

F105 first requires complete allocatable 80-byte texture-owner and 24-byte
command-owner types: two/one actual constructor new expressions have three
EH cleanup states. Existing pointer-only interfaces cannot be instantiated.
Also reconcile its real GS/EH scope graph and filename-buffer bounds; the
decompiler's apparent 532-byte array is not a bound. Do not introduce padding
classes, raw storage substitutes, artificial array growth or manual EH to
force comparison. Continue the F105 cohort with these prerequisites before
source; no F105 source or exact credit yet.

## Previous accepted functions: F103

R019 texture-pack loader `0040B7C0..0040BB74` (949 bytes) and its default
wrapper `0040B7A0..0040B7BA` (27 bytes) independently pass canonical cold
comparison as TexturePackLoad40B7C0::Load/LoadDefault. All 976 bytes,
341 instructions and 39 real relocation fields match. Eleven/five following
INT3 bytes remain outside. The wrapper supplies exactly zero as the signed
palette-selection argument, with one parameter/RET4; main has two/RET8.
Both historical R019 roles remain by aliases. One new implementation file
leaves every old source and header unchanged.

Entry count is obtained before opening the file. Invalid handle exits
immediately. File position resets to zero, then the signed palette-count
byte is read and the old palette array deleted. A positive count allocates
512 bytes. Selection<=count seeks to the selected palette, reads it and skips
the rest; larger selection reads the first palette and skips count-1 blocks.
Nonpositive header count clears the palette pointer. Signed byte arithmetic,
negative seek offsets, actual zero default and ignored SDK results remain as
observed. There is no palette-index clamp or error-path repair added.

Each entry receives owner format/palette and flag zero before reading its
metadata. The complete 24-byte descriptor repeats the accepted Save and
serialized-loader definition; all six fields are actually used. Metadata
reads remain 4/4/4/1/4 bytes. Encoded payloads use their byte size, raw high-depth
payloads use stride*height*4, and lower depths retain the actual unsigned
multiply/right-shift expression. The descriptor is passed to the accepted
serialized loader, then its temporary payload is deleted. Texture creation
uses the real word width/height, byte depth and texture-slot address. Palette
refresh precedes deletion/clearing of the entry pixels. CloseHandle remains
after the entry loop. Partial owner/container interfaces are pointer-only and
never constructed or embedded; original names/grouping/layouts stay unknown.

All 38 main packets and the wrapper packet pass review, including seventeen
SDK calls, eleven ReadFiles, nine entry lookups and one texture-slot lookup.
Nested lookups preserve the actual four/eight/twelve bytes of outer arguments.
The real SDK factory receives byte/word values in DWORD stack carriers;
upper carrier bits are not falsely claimed to be logical parameter bits.
Every physical carrier/register byte still matches in the full comparison.
Four wrong-ABI and two wrong-binding controls fail. Four array new/three array
delete fields bind their true thunks; scalar aliases are rejected. All actual
PE import names are checked independently.

Initial source has all 329 main instructions and the exact wrapper, with only
seven actual local-displacement bytes differing. Ordinary used-local name
choices reproduce the complete 76/4-byte frames. The final comparison uses
all physical bytes without normalization, padding, inert storage, assembly,
register/frame aliases, masks or cropped extents. Separate canonical cold
reports cover both new units in one serial object build. Old dependencies
receive no replay or new exact credit.

```bash
scripts/repo-python scripts/replay-exact-units.py --unit texture-pack-load-0040b7c0 --unit texture-pack-load-default-0040b7a0
```

All 199 prior units, 101 canonical objects, 169 source inputs, 218 origin files,
nine shared headers, 91 active drafts and 4,349 other function rows stay
unchanged. F009 plus 141 additions retains 564,258 code bytes and 170 inputs.
Keep all f103 native/attested/ABI/import/physical/cold/parent records and
compiler control sources/results/logs/PDBs. The older private hypothesis note
incorrectly said thirteen wrapper instructions; the unchanged native index
and refined review show twelve. Original note/accepted retention hashes remain
intact. No unknown origin or old draft receives credit.

Current totals: 201 exact functions/units, 574,141 code bytes, 29.09% of
reviewed authored bytes and 29.04% conservatively including all pending bytes.

Next F104 is the complete 918-byte R019 archive texture-pack loader `0040BBA0`.
Its palette/record/upload graph is closely related, but archive lookup/open
calls and handle ownership require independent review. Native setup preserves
an outer filename argument across the context lookup, then moves its result
to ECX before opening. Reconcile both full archive callees and the caller's
actual stack/return policy before source. No F104 source or exact credit yet.
The 98% goal remains active and incomplete.

Final F103 CI passes 3,603 tests in 114.424s. Bounded cleanup
removes two obsolete reproducible probe/control objects (56,898 bytes)
and 8,282,705 bytes of Python caches, with per-file hash receipts.
Canonical outputs, all source/control inputs, complete evidence, logs and PDBs
remain. F104 full native/callee/caller exports and indices, completed own
archive-callee decompile/caller query and bounded ABI notes are retained
privately. The archive lookup consumes one cdecl name argument while the
outer filename stays live for the returned context's RET4 seek method; older
root decompile's extra argument is not an ABI fact. No F104 source or exact
credit yet.

## Previous accepted function: F102

R021 serialized-record loader `0041B2B0..0041B3F5` independently passes
canonical cold comparison as BitmapSerialized41B2B0::Load(const
TextureRecordSnapshot40BF60*). All 326 code bytes, 114 instructions, four
branches and six physical REL32 fields match. Ten following INT3 bytes remain
outside; there is no associated switch data. One new implementation file
leaves all old headers and sources intact. The historical
BitmapData::LoadSerializedPixels role remains by an R021 alias.

The incoming descriptor supplies width/height/stride at offsets 0/4/8, byte
depth at 12, encoded size at 16 and payload pointer at 20. These six actual
fields support the complete 24-byte source-compatible descriptor already used
by accepted Save; its definition is identical across the two translation units.
Both full callers independently read 4/4/4/1/4 bytes into the metadata fields
at EBP-32, then store/read the payload pointer at EBP-12. Their index at EBP-8
lies outside this record. Original type names/grouping remain unknown. This
value does not establish the complete bitmap owner layout. The new owner
view stays pointer-only and is never constructed or embedded.

All five metadata values are copied before the allocation branch. Unsigned
encoded-size >0 copies exactly that many bytes. Otherwise depth>=24 allocates
and copies stride*height*4; lower depths retain the actual unsigned
(stride*height*depth)>>3 expression, repeated for allocation and copy. No old
pixel deletion, format/dimension repair or validation is added. Three genuine
scalar new calls and three memcpy calls bind independent library entries.
The actual <new> compiler control emits three different array-new identities;
those real thunks cannot be aliased. Full R025 memcpy provenance, all 46 local
fields, six tables and eight RET0 routes are rechecked without a library build
or dependency credit.

The complete CFG and all six packets preserve the actual 16-byte frame,
one descriptor parameter, ECX receiver and RET4. Both 949/918-byte callers
preserve four bytes of outer descriptor argument during entry lookup, then
pass the returned entry as ECX. Both ignore the loader result and delete
their temporary payload after the copy. Three wrong-ABI and two wrong-binding
controls fail. There are no fake returns, inert locals, padding, assembly,
frame/register aliases, masks or cropped extents. Only this new unit is cold
built; no accepted dependency replay is needed.

```bash
scripts/repo-python scripts/replay-exact-units.py --unit bitmap-serialized-load-0041b2b0
```

All 198 prior units, 100 canonical objects, 168 source inputs, 218 origin files,
nine shared headers, 91 active drafts and 4,350 other function rows stay
unchanged. F009 plus 139 additions retains 563,282 code bytes and 169 inputs.
Keep all f102 native/attested/ABI/memcpy/physical/cold/parent records and source,
compiler controls, results, logs and PDBs. All 97 unknown origins and old drafts
receive no credit.

Current totals: 199 exact functions/units, 573,165 code bytes, 29.04% of
reviewed authored bytes and 28.99% conservatively including all pending bytes.

Next F103 is the complete 949-byte R019 texture-pack loader `0040B7C0`, one of
these two callers. The full native export and attested view already exist;
reconcile signed palette count/selection, all file/metadata/payload lifetimes,
complete local descriptor, actual texture/upload packets and the true ABI
before natural source. Preserve the sibling archive loader `0040BBA0` for a
later cohort. No F103 source or exact credit yet. The 98% goal remains active
and incomplete.

Final F102 CI passes 3,603 tests in 126.212s. Bounded cleanup
removes two obsolete reproducible probe/control objects (18,052 bytes)
and 8,282,705 bytes of Python caches, with per-file hash receipts.
Canonical outputs, source/control inputs, complete ABI evidence, logs and PDBs
remain. F103 native/dependency index, sole-caller query, complete 27-byte
default wrapper and bounded ABI notes are retained privately. The wrapper
passes exactly zero, with RET4; the 949-byte main has RET8. Reconcile and
cold-compare both independently if accepted together. No F103 source or
exact credit yet.

## Previous accepted function: F101

R021 bitmap run encoder `0041B400..0041B966` independently passes canonical
cold comparison as BitmapPackSource40BF60::Encode(). All 1,383 code bytes,
382 instructions, 31 branches and 21 physical relocation fields match.
The 1,424-byte comparison includes the full 16-byte destination table at
`0041B967` and 25-byte selector at `0041B977`; table bytes earn no coverage.
The next accepted function starts immediately at `0041B990`, without an INT3
gap. One new implementation file leaves all prior headers and sources intact.
The historical BitmapData::EncodeRuns role remains by an R021 alias.

The no-argument method uses ECX and RET0 with a real 140-byte frame. An existing
encoded size returns immediately. Separate byte, word and shared 24/32-bit
cases retain real 1/2/4-byte run counts and colors, unsigned row/pixel loops,
stride-aware source reads and final run emission. Only the byte case has a
255-count guard; word/dword paths retain their observed overflow behavior.
Temporary capacity is height*width*two elements, including the actual two
successive allocation shifts for word/dword elements. Old pixels are deleted
before replacement allocation; encoded byte size is stored, payload copied,
and temporary storage deleted in that order. No validation or count repair
is added. The pointer-only owner is never constructed or embedded.

Three native zero DWORD initializers lack later loads. Genuine used per-case
run-length field-index constants explain these stores while folding six
count-field write addresses. The full index-one control changes all three
initializers and all six actual stores. These are functional source constants,
with no inert locals or padding; original declarations, names and scopes remain
unknown. Compiler ordering controls reproduce the complete physical frame;
all 646 earlier diagnostic name buckets also reproduce independently.

Six scalar new, six scalar delete and three memcpy calls bind independently.
A real <new> control emits twelve different array-operator identities and
cannot bind to the scalar native calls. Complete R025 vendor memcpy remains
829 bytes with all 46 real local relocations. Its six tables contain 120 bytes
in total, and all 231 reachable instructions/eight RET0 routes preserve three
cdecl arguments and the destination result in EAX. Thirty-seven extent bytes
of alignment remain covered by the complete vendor comparison. SDK header
and assembly context corroborate the ABI without proving original build flags.
No library dependency receives new source or exact credit.

All fifteen packets, three buffer lifetimes, the full switch CFG and both
full callers pass review. Both callers supply only the entry receiver and
ignore the result. Four wrong-ABI and three wrong-binding controls fail.
All six local fields bind actual newly emitted COFF table/case offsets.
There are no masks, register/frame aliases, patched branches, assembly or
cropped extents. Only this new unit is cold built.

```bash
scripts/repo-python scripts/replay-exact-units.py --unit bitmap-encode-0041b400
```

All 197 prior units, 99 canonical objects, 167 source inputs, 218 origin files,
nine shared headers, 91 active drafts and 4,350 other function rows stay
unchanged. F009 plus 138 additions retains 562,956 code bytes and 168 inputs.
Keep all f101 native/attested/ABI/policy/memcpy/physical/cold/parent/recovery
records and compiler sources, controls, results, logs and PDBs. A stale input
filename in the initial private adoption script was rejected by its guard;
only its six new ledger rows/appends were restored, then the corrected script
derived the input from the verified unit and completed all checks. Earlier
accepted state and origin evidence never changed.

Current totals: 198 exact functions/units, 572,839 code bytes, 29.03% of
reviewed authored bytes and 28.97% conservatively including all pending bytes.

Next F102 is the complete 326-byte R021 serialized-record loader `0041B2B0`:
114 instructions, four branches, six calls and RET4, with ten following INT3
bytes excluded and no switch data. It takes a descriptor pointer, copies five
metadata fields to the owner, then allocates/copies encoded or raw pixels
from the descriptor's data pointer. It has no file API calls. Reconcile the
complete 24-byte descriptor field evidence, unsigned size/depth policy, actual
one-argument ECX/RET4 and all three scalar new/memcpy packets before source.
Preserve all 97 unknown origins and old drafts without credit. No F102 source
or exact credit yet. The 98% goal remains active and incomplete.

Final F101 CI passes 3,603 tests in 124.896s. Bounded cleanup
removes five obsolete reproducible probe/control objects (86,740 bytes)
and 8,282,705 bytes of Python caches, with per-file hash receipts.
Canonical outputs, all sources/controls/results, vendor ABI evidence, logs
and PDBs remain. F102 own root/caller decompiles and caller query complete
with target attestation and their completion markers; full native/dependency/
caller indices and bounded ABI notes are retained privately. No F102 source
or exact credit yet.

## Previous accepted function: F100

R021 bitmap loader `0041A3D0..0041B276` independently passes canonical cold
comparison as BitmapPackSource40BF60::LoadFile(const char*). All 3,751 code
bytes, 1,001 instructions, 88 branches and 24 actual relocation fields match.
The full comparison also includes 45 generated switch-data bytes: the 20-byte
destination table at `0041B277` and 25-byte selector map at `0041B28B`.
Only code earns coverage credit. Twelve following INT3 bytes stay outside.
One new implementation file leaves all old headers and sources unchanged;
the historical BitmapData::LoadBitmap role remains by an R021 alias.

The pointer-only interface exactly repeats the accepted save header's class
members; the incomplete owner is never constructed or embedded. Complete SDK
BITMAPFILEHEADER/INFOHEADER/RGBQUAD views provide real file records. A separate
complete four-byte RGBA temporary copies all four real channels and does not
establish the bitmap owner layout. True scalar new/delete symbols bind nine
allocations and four deletes. Minimal SDK headers naturally emit these scalar
symbols for array expressions with VC7.1; an actual <new> control emits thirteen
different array-operator identities. Their real thunks cannot be aliased.
Four SDK imports are independently read from the actual target PE table.

File-format precedence, depth minimum, palette ownership, four-byte row
alignment and all 8/16/24/32 output paths remain as observed. Indexed paths,
vertical row reversal, BGR conversion and black-pixel alpha tests preserve
actual operations. Read results remain ignored. Invalid handle and bad BMP
signature retain their direct failure exits and original cleanup behavior.
There is no dimension validation, allocation check or odd-width repair added.

One native zero byte is initialized but never loaded. A genuinely used const
BYTE transparent palette index supplies a source-compatible explanation:
VC7.1 retains its initialization while folding three zero-index uses into
addresses. The complete index-one control changes that initializer and six
actual palette load/store addresses; a small independent control confirms
the same behavior. The constant is functionally used, with no inert local or
padding. Its original declaration and name remain unknown. Ordinary local
names and scopes reproduce the complete physical 200-byte frame plus ESI;
private compiler ordering controls provide diagnostics, without exact credit.

All seventeen packets, the complete switch CFG, AL0/AL1 exits and RET4 pass
review. All three full callers pass filename/entry-receiver review; the two
directory loaders actually test AL, while accepted Save ignores it. Four
wrong-ABI and three wrong-binding controls are rejected. All seven local
switch fields bind their newly emitted COFF offsets. There are no frame or
register aliases, relocation masks, patched branches or cropped comparisons.
Only this new unit is cold built; no old dependency replay is needed.

```bash
scripts/repo-python scripts/replay-exact-units.py --unit bitmap-load-0041a3d0
```

All 196 prior units, 98 canonical objects, 166 inputs, 218 origin files, nine
shared headers, 91 active drafts and 4,350 other function rows stay unchanged.
F009 plus 137 additions retains 561,573 code bytes and 167 source/header inputs.
Keep all f100 native/attested/ABI/policy/import/physical/cold/parent records and
compiler control sources, results, logs and PDBs. Original names, scopes and
whole owner layouts remain unknown. All 97 unknown origins and old drafts
receive no credit. The progress card now takes its goal percentage from the
same status result, replacing its stale literal 95% with the active 98% goal.

Current totals: 197 exact functions/units, 571,456 code bytes, 28.96% of
reviewed authored bytes and 28.90% conservatively including all pending bytes.

Next F101 is the complete 1,383-byte R021 run encoder `0041B400` from accepted
Save's graph. The native index retains 382 instructions, 31 branches, fifteen
calls and all 41 associated switch-data bytes (1,424-byte comparison extent).
No following INT3 gap exists before accepted `0041B990`. Six scalar new, six
scalar delete and three complete memcpy calls need full run-count/color/type,
allocation and ECX/no-argument/RET0 reconciliation before source. Existing
attested F099 views contain the whole encoder; retain the own caller query.
No F101 source or exact credit yet. The 98% goal remains active and incomplete.

Final F100 CI passes 3,603 tests in 125.909s. Bounded cleanup
removes ten obsolete reproducible probe/control objects (194,525 bytes)
and 8,282,705 bytes of Python caches, with per-file hash receipts.
Canonical outputs, control sources/results, evidence, logs and PDBs remain.
F101 own caller query completed with target attestation and its completion
marker; complete native/callee/switch index and bounded ABI notes are retained
privately. No F101 source or exact credit yet.

## Previous accepted functions: F099

R019 SaveTexturePack `0040BF60..0040C375` (1,046 bytes) and its default wrapper
`0040BF40..0040BF5E` (31 bytes) independently pass canonical cold comparison as
TexturePack40BF60::Save/SaveDefault. All 1,077 bytes, 327 instructions and 39
physical relocation fields match. Ten/one following INT3 bytes stay outside
the extents. Two new source/header inputs leave all old headers and sources
unchanged. Both historical R019 roles remain by aliases. The wrapper passes
exactly zero as the third argument, with two real parameters and RET8; the
main method has three parameters and RET12, including a signed byte count.

The save retains palette mutation and ordering: absent palette writes header
zero; count<=1 writes header one and one 512-byte palette; count>1 appends the
requested additional palettes after loading `%s\pal%dp.bmp` into the owner.
Each entry receives selected format/palette, loads `%s\%04d.bmp`, encodes,
then writes metadata in exact 4/4/4/1/4-byte order. Encoded data reloads the
entry pointer while twelve bytes of outer WriteFile arguments remain live.
Raw data preserves format-dependent byte size and unsigned right shift. All
API error handling and ignored write/load results remain as observed.

A complete 24-byte local serialization value groups six actual fields with
ordinary alignment; every field is used. This source-compatible local value
is not a complete native manager/bitmap owner or original grouping claim.
All owner/bitmap interfaces remain pointer-only and are never constructed or
embedded. Initial scalar probes reproduce all 313 instructions but place
locals differently. Natural scopes, that real value model, ordinary local
names and SDK MAX_PATH (260) reproduce the full 324-byte frame and GS output.
The 268-byte path/cookie distance does not imply a 268-byte array: no array
growth, explicit padding, inert storage or manual cookie code is used.

All 35 main packets, the wrapper packet and both full CFGs pass review,
including four rejected cleanup controls. Fourteen WriteFile calls use the
real SDK DWORD output local. Eleven entry lookups preserve outer argument
counts, including the bitmap-loader filename and encoded payload packet.
Full 3,751/1,383-byte R021 bitmap bodies and their complete switch maps are
revalidated; loader returns AL0/AL1 and its result is ignored here. Compiler
cookie/check and both complete readonly string payloads bind independently.
Original names/scopes and whole owner layouts remain unknown. No masks,
frame/register aliases or cropped comparison. Only the two new units are cold
compared in one serial object build; no old dependency rebuilds are needed.

```bash
scripts/repo-python scripts/replay-exact-units.py --unit texture-pack-save-0040bf60 --unit texture-pack-save-default-0040bf40
```

All 194 old units, 97 canonical objects, 164 inputs, 218 origin files, nine
shared headers, 91 active drafts and 4,349 other function rows stay unchanged.
F009 plus 136 additions retains 557,822 code bytes and 166 inputs. Keep all
f099 native/attested/ABI/snapshot-model/bitmap-CFG/import/physical/cold/parent
records and compiler control sources, logs and PDBs.
Final F099 CI passes 3,603 tests in 137.061s. Bounded cleanup
removes six obsolete reproducible probe objects (119,578 bytes)
and 8,282,705 bytes of Python caches, with per-file hash receipts.
Canonical objects, compiler/source inputs, evidence, logs and PDBs remain.
F100 complete native/dependency/switch index, existing attested root view,
completed caller query and bounded ABI notes are retained privately; no F100
source or exact credit yet. Three callers include both directory loaders and
the accepted save policy. Its true scalar allocation symbols and all format/
row-stride/return policies require independent reconciliation before source. The 97 unknown origins and old drafts receive no credit.
Next F100 is the complete 3,751-byte R021 bitmap loader `0041A3D0` from this
graph. Reconcile file/format policy, actual source/output buffers, scalar
allocator identities, AL failures and full associated switch data before
source; never construct incomplete owners. Goal 98% remains incomplete.

## Previous accepted function: F098

R014 bitmap-palette loader `0040C380..0040C58A` independently passes canonical
cold comparison as BitmapPalette40C380::Load(const char*): all 523 bytes,
161 instructions, ten branches and eight real fields. Five following INT3
bytes remain outside the extent. One new implementation file leaves all old
headers and sources unchanged. The historical TextureManager::LoadBitmapPalette
role remains by alias. The partial owner is never constructed or embedded;
its complete original layout, source names and prototype remain unknown.

The old palette is array-deleted and cleared before opening the new file.
CreateFileA/GetFileSize/ReadFile read a file-sized primitive byte array. Real
complete SDK BITMAPFILEHEADER/INFOHEADER/RGBQUAD pointer views provide the
14/40/4-byte records and observed offsets. The real unused bfOffBits snapshot
is preserved. The low byte of biBitCount feeds an unmasked shift before the
signed depth<=8/count-loop checks. Colors begin at fixed offset 54, rather than
the snapshot offset. A real 256-WORD/512-byte array receives B/G/R five-bit
conversion, with alpha OR0x8000 and first-entry AND0x7FFF. Width, file-read and
format error behavior receive no repair. In particular bad BM exits directly
with the native live file/buffer behavior; valid BM alone reaches deletion and
CloseHandle. Ignored ReadFile byte count remains a genuine API output local.

All four PE import names and stdcall packets (28/8/20/4 bytes) are independently
read back. Both five-byte array-operator thunks and complete R154/R120/R142
runtime parents/headers remain unchanged. Including the real <new> header
naturally emits array new/delete symbols. The declaration-free control emits
scalar symbols; binding those to their legitimate scalar entries fails four
physical fields. Scalar symbols are never mapped onto array thunks to force
a match. All 64-byte frame joins, eight packets and cdecl caller cleanup pass;
wrong allocation-callee-ret4 and ReadFile-ret16 controls fail. The complete
1,046-byte sole caller passes filename/owner and ignores the result.

The first probe already reproduces all 161 instructions/ten branches. Bounded
meaningful local-name controls reproduce the actual frame positions; final
source keeps ordinary flat scopes and one body. Source names remain provisional.
No padding, inert locals, symbol/frame/register aliases, masks or shortened
comparison. Only the new unit is cold replayed; no old rebuilds are needed.

```bash
scripts/repo-python scripts/replay-exact-units.py --unit bitmap-palette-load-0040c380
```

All 193 old units, 96 canonical objects, 163 inputs, 218 origin files, nine
shared headers, 91 active drafts and 4,350 other function rows remain unchanged.
F009 plus 134 additions retains 556,745 code bytes and 164 inputs. Preserve all
f098 native/attested/ABI/allocation/import/physical/cold/parent evidence and
compiler-control sources, logs and PDBs.
Final F098 CI passes 3,603 tests in 136.295s. Bounded cleanup
removes seven obsolete reproducible probe objects (272,737 bytes)
and 8,282,705 bytes of Python caches, with per-file hash receipts.
Canonical objects, compiler/source inputs, evidence, logs and PDBs remain.
F099 complete native/callee exports, root and seven-callee attested views,
index and provisional ABI notes are retained privately; no F099 source or
exact credit yet. The separate caller query completed with its own attestation
and completion marker, recording the 31-byte R019 default-palette caller
0040BF40 (two arguments/RET8, passes count zero). Its whole native export is
retained; any later exact credit requires its own source and cold comparison.
Filename array size remains unknown; the distance to the
security cookie alone does not prove an array extent or authorize padding.
Next F099 is the complete 1,046-byte R019 SaveTexturePack `0040BF60`, the sole
palette-loader caller. Reconcile serialization, signed-byte palette count,
real filename buffer/security cookie, nested bitmap load/encode and complete
callee ABIs before source; never construct incomplete owner views. The 97
unknown origins and old drafts receive no credit. Goal 98% stays incomplete.

## Previous accepted functions: F097

R014 upload adapter `0040C730..0040C7DC` (173 bytes) and its sole static caller
`0040C6F0..0040C725` (54 bytes) independently pass canonical cold comparison as
TextureUpload40C730::Upload and UploadByHandle. All 227 bytes, 92 instructions,
eight call packets and three direct relocation fields match. Three/ten INT3
alignment bytes remain outside the respective extents. Two new source/header
inputs provide one natural body per entry and pointer-only interfaces; no old
header or source changes. Both historical R014 roles remain by aliases.

Both entries have two actual parameters and RET8. The caller resolves a texture
by index, saves the SDK pointer in a genuine local, checks null, then passes
its address and the bitmap with original owner ECX to the adapter. The adapter
saves ECX without otherwise consuming it. Its second argument is a pointer to
a live texture-pointer slot, not a direct texture pointer or constructed owner.
Original complete owner identity/layout and ignored result prototypes remain
unknown. Partial owner/bitmap views are never constructed or embedded.

The adapter retains three actual metadata reads/stores at bitmap+4/+8/+0xC
with no later consumer. GetSurfaceLevel uses the caller's texture slot first;
GetDesc supplies surface Width, then the texture slot is loaded again before
surface Release. Five COM calls use true SDK stdcall packets including this:
12/8/4/20/8 bytes. Complete SDK surface description and lock records occupy
32/8 bytes with Width/pBits at offsets 24/4. LockRect HRESULT zero gates the
byte/three-word bitmap conversion and UnlockRect. The native unused Pitch and
existing error behavior remain. No metadata computation or API ordering repair.

Both full CFGs, 72/8-byte frames, actual SDK output objects and all eight packets
pass review. Wrong converter-ret8, LockRect-ret16, adapter-ret4 and caller-ret4
controls fail. Bounded name/scope controls explain compiler local allocation;
the final canonical source uses flat scopes and ordinary lockInfo/pSurface
names, with all physical frame fields equal. Original source names/scopes are
not inferred from byte equality. No padding, inert locals, masks, aliases or
shortened comparison. Only the two new units are cold compared in one serial
object build; old accepted resolver/bitmap dependencies remain unchanged.

```bash
scripts/repo-python scripts/replay-exact-units.py --unit texture-upload-0040c730 --unit texture-upload-handle-0040c6f0
```

All 191 old units, 95 canonical objects, 161 inputs, 218 origin files, nine
shared headers, 91 active drafts and 4,349 other function rows remain unchanged.
F009 plus 133 additions retains 556,222 code bytes and 163 inputs. Preserve all
f097 native/attested/ABI/physical/cold/parent/progress evidence and compiler
control sources, logs and PDBs.
Final F097 CI passes 3,603 tests in 145.142s. Bounded cleanup
removes three obsolete reproducible probe objects (85,215 bytes)
and 8,282,705 bytes of Python caches, with per-file hash receipts.
Canonical objects, compiler/source inputs, evidence, logs and PDBs remain.
F098 whole native index, root decompile, caller query and allocation-parent
exports are retained privately; no F098 source or exact credit yet. The 97
unknown origins and old unaccepted drafts receive no credit.
Next F098 is the complete 523-byte R014 bitmap-palette loader `0040C380` in the
same texture graph. Reconcile file reads, complete format/SDK records, all 256
palette entries and error paths before natural source. Goal 98% remains active
and incomplete.

## Previous accepted function: F096

R021 bitmap conversion `0041B990..0041BF37` is independently canonical cold
exact as `BitmapUpload40C590::CopyTo(void*, unsigned char, unsigned int)`.
The comparison covers 1,530 bytes: all 1,448 code bytes plus 82 bytes of actual
compiler-generated switch data. Only the 1,448 code bytes earn credit. Both
25-byte selector maps and 16-byte destination tables are retained at their
actual following addresses; six INT3 alignment bytes precede the next function.
All 12 DIR32 fields bind actual newly emitted local COFF offsets, including
case/default labels. No fixed binding can hide a moved table or case label.

One new implementation uses the same pointer-only bitmap interface as F095.
Its complete owner layout and original names remain unknown; it is never
constructed or embedded. The historical BitmapData::UploadDecodedPixels role
remains by alias. Nonzero input+0x10 selects encoded runs, zero selects raw copy.
The three typed encoded paths preserve byte/word/DWORD run lengths and colors,
palette conversion, source pair advancement, nested unsigned loops and terminal
pixel guards. Only the byte path resets consumed count to the unsigned boolean
count>run; word/DWORD paths reset zero. The converter observes width/height and
source stride at +4/+8/+0xC, palette pointer+0x14 and source pointer+0x1C.
These are accessed fields, without a complete original object-layout claim.

Raw byte input converts palette entries into WORD output. Raw 16-bit copying
shifts the actual output-width parameter and snapshots width/stride shifted
by one, then copies DWORD pairs. Raw 24/32 selectors share DWORD copying.
Odd-width behavior and source/output width units are preserved. No memcpy,
format repair, helper extraction or guessed record instantiation is introduced.
The first probe already has all 371 instructions and 58 branches in place;
bounded meaningful local-name controls reproduce the real frame fields.
Source names/scopes remain provisional even though emitted bytes match.

The 164-byte frame contains three real 32-byte encoded scopes, 16/24/16-byte
raw scopes, saved this and two compiler switch temporaries. Saved ESI occupies
four additional stack bytes. All CFG joins, both compressed switch maps and
RET12 are checked. Wrong RET8 and omitted ESI-pop controls fail. The accepted
F095 caller proves the nested byte/three-word packet; the complete second
173-byte caller independently passes the same converter arguments and has its
own RET8. No old caller/header/body changes or old cold builds are needed.

```bash
scripts/repo-python scripts/replay-exact-units.py --unit bitmap-upload-0041b990
```

All 190 old units, 94 canonical objects, 160 inputs, 218 origin files, nine
shared headers, 91 active drafts and 4,350 other function rows stay unchanged.
F009 plus 131 additions retains 555,995 code bytes and 161 inputs. Preserve all
f096 native/attested/ABI/switch/physical/cold/parent/progress evidence and all
compiler control sources, logs and PDBs.
Final F096 CI passes 3,603 tests in 143.025s. Bounded cleanup
removes four obsolete reproducible probe objects (310,729 bytes)
and 8,282,705 bytes of Python caches, with per-file hash receipts.
Canonical objects, compiler/source inputs, evidence, logs and PDBs remain.
F097 complete native index, attested root/caller views, caller query and ABI
notes are retained privately; no F097 source or exact credit yet. Its sole
54-byte R014 caller passes a real live texture-pointer slot and original owner
ECX to the 173-byte adapter; consider that complete caller as a separate unit
after its own independent source, physical binding and cold comparison.
Next F097 is the complete 173-byte R014 upload adapter `0040C730`, with two
real parameters/RET8, a pointer-to-texture argument and SDK surface/lock values.
Reconcile all five COM packets before natural source. Unknown 97 origins and
old drafts receive no credit. Goal 98% remains active and incomplete.

## Previous accepted function: F095

R014 palette refresh `0040C590..0040C6E3` is independently canonical cold exact
as `TexturePalette40C8C0::Refresh(int)`: all 340 bytes, 125 instructions,
six branches, 16 real call packets and 11 direct relocation fields. Twelve
following INT3 bytes remain outside the extent. One new implementation file
uses unchanged accepted interfaces. Its two repeated pointer-only class
interfaces have identical definitions to F094; no old header/body is changed.
The historical `TextureManager::UploadIndexedTexture` role remains by alias.
Original complete owner/vector/bitmap layouts and source names remain unknown.

Signed index validation uses the normal handle count at owner+0x18. Three
actual entry reads at +4/+8/+0xC are stored before selection and have no later
consumer; the source retains those observed metadata computations. The meaning
of +0xC is unknown. A palette flag at entry+0x28 selects handle zero from
owner+0x28 with width 256. Otherwise the normal texture yields a surface,
its complete SDK D3DSURFACE_DESC supplies Width, the handle is looked up again,
and the surface is released. LockRect succeeds only on HRESULT zero. The bitmap
converter receives SDK locked pBits, a byte from entry+0, and the selected
surface width. The native locked Pitch is unused; do not replace width with it.
UnlockRect follows the conversion. Existing target API error handling remains.

Five COM slots use actual SDK stdcall signatures including this: texture
GetSurfaceLevel/12, surface GetDesc/8, Release/4, texture LockRect/20 and
UnlockRect/8 bytes. SDK records are complete 32-byte surface description and
8-byte lock record; partial owner views are never constructed or embedded.
Both nested entry lookups retain four and twelve bytes of outer arguments;
the converter consumes three words and RET12, with a real byte argument.
All 16 packets, six branch joins and the 76-byte frame pass review. Wrong
copy-ret8 and LockRect-ret16 controls fail. The full 1,448-byte R021 converter
and both compressed switch selector/destination maps are revalidated without
converter credit or ownership changes.

The first probe is 342 bytes/126 instructions. A natural success block gives
340/125; bounded meaningful local-name controls then reproduce all actual
frame fields. The chosen +0xC scalar name remains explicitly provisional.
No inert locals, padding, byte arrays, masks, frame aliases or cropped extent.
Only the new unit is cold replayed; no old build is needed.

```bash
scripts/repo-python scripts/replay-exact-units.py --unit texture-palette-refresh-0040c590
```

All 189 old units, 93 canonical objects, 159 inputs, 218 origin files, nine
shared headers, 91 active draft inputs and 4,350 other rows remain unchanged.
F009 plus 130 additions retains 554,547 bytes and 160 inputs. Keep all f095
native/attested/ABI/bitmap-CFG/physical/cold/parent/progress evidence, compiler
control sources, logs and PDBs.
Final F095 CI passes 3,603 tests in 146.206s. Bounded cleanup
removes five obsolete reproducible probe objects (119,429 bytes)
and 8,282,705 bytes of Python caches, with per-file hash receipts.
Canonical objects, source/control inputs, evidence, logs and PDBs remain.
Fresh attested F096 decompile/callers, complete native/switch index and ABI
observations are retained privately; no F096 source or exact credit yet.
Next F096 is the complete 1,448-byte R021 bitmap converter `0041B990`, including
both switch maps outside its code extent. Reconcile every loop and real field
before source. The 97 unknown origins and old drafts receive no credit.
Goal 98% remains active and incomplete.

## Previous accepted function: F094

R014 texture resolver0040C8C0..0040C961 is independently canonical cold exact
as `SpriteTextures40CA80::GetTexture(int)`: all162 bytes,53 instructions,
seven branches,five real call packets and11 physical fields. Fourteen following
INT3 bytes stay outside the extent. One new implementation file uses the
existing unchanged F093 method declaration. Original R014 role is retained by
alias; complete manager/vector/entry layouts and data ownership remain unknown.

The first-use flag test/OR1 and cached index store precede signed input-index
validation. Count is explicitly converted to signed32 for the actual JL
comparison. Entry flagbyte+0x28 selects palette refresh/index update and handle0
from receiver+0x28; normal handles use callerindex at receiver+0x18. Both index
helpers return an EAX slot reference,then MOV EAX,[EAX] returns the actual SDK
texture pointer. Invalid indices returnnull. No validation reordering or cache
policy repair. Pointer-only helper views are never instantiated/embedded.

The initial explicit-global model matched physically. A single function-local
static cachedIndex=index emits identical raw162 function bytes with VC7.1 and
is the sole final canonical body. Its guard/cache symbols bind independently;
both compiler BSS cells are four zero bytes,matching target initial storage.
Separate final canonical cold comparison passes; only this changed unit is
replayed again. Original source spelling/scope/data ownership remains unknown. All11 fields bind five direct calls and six writable
DWORD accesses at6713B8(flags)/6713B4(index). Two ledger names are physical aliases
for those observed scalar addresses; they do not claim original source names,
declarations or data ownership. Final source uses the compiler-generated guard
and one genuine cached scalar; no manual guard or alternate body remains. All four whole callees,zero/4-byte helper cleanups,
4-byte frame joins and finalRET4 are checked. Wrong count-ret4/index-ret0
controls fail. No masks,aliases,padding or cropped comparison.

```bash
scripts/repo-python scripts/replay-exact-units.py --unit texture-resolve-0040c8c0
```

All188 old units,92 canonical objects,158 inputs,218 origin files,nine shared
headers,91 active drafts and4,350 other rows remain unchanged; no old rebuilds.
F009+129 additions retains554,207 bytes and159 inputs. Unknown97 origins and
all old unaccepted drafts receive no credit. Preserve f094 native/attested/
ABI/physical/cold/parent/progress/input/preservation evidence,source probes,
logs and PDBs. Final full CI passes3,603 tests in140.355s. Bounded cleanup
removes three obsolete reproducible F094 objects/35,120 bytes and8,282,705
bytes of Python caches,with per-file hash receipts. Canonical objects and all
source/evidence inputs remain. Fresh F095 root/callee/caller attested queries
and native index are retained privately; no F095 source or credit yet. Next F095:
complete340-byte R014 palette refresh0040C590 from this direct graph. Reconcile
SDK surface/lock objects and entry/palette source data before natural source;
never instantiate incomplete owners. Goal98% remains active/incomplete.

## Previous accepted functions: F093

R011 DrawSprite 0040CA80..0040CEEB (1,132 bytes) and clear constructor
0040D990..0040D9E4 (85 bytes) independently pass canonical cold comparison as
`TimelineDrawing438D00::DrawSprite` and `SpriteQuad40CA80::SpriteQuad40CA80`.
Four/eleven following INT3 bytes are excluded. Two new source/header inputs
hold one natural body per function and one complete physical packet interface.
Both previous R011 roles are retained by alias. Complete original manager,
entry and class identities/layout partitions remain unknown.

The draw retains all303 instructions,11 branches,12 packets and16 fields:
twelve direct calls and four readonly scalar fields. Its nine arguments occupy
36 bytes. Exact scale/angle tests keep unordered and signed-zero behavior.
Mirrored/nonmirrored fast and scaled paths construct four real132-byte
value temporaries and copy33 dwords each. The rotated path preserves both
cdecl(float)/ST0 math calls and the native eight-field arithmetic order. One
real SDK D3DXVECTOR4 swaps all four coordinate words for each flipped pair.
Nested texture resolution feeds the actual cdecl16-byte final draw packet.

The established F064/F083 complete132-byte physical model now has both
constructor entries in a new interface, leaving old headers unchanged. It
contains four16-byte coordinate records and the existing68-byte payload at64;
size/offset guards and full constructor/copy evidence are retained. This is a
physical value view, not a complete original manager/entry layout claim.
Entry access returns an observed EAX address; only signedDWORD+4/+8 dimensions
are read. Manager/entry views are pointer-only and never constructed/embedded.
The authored clear constructor has28 instructions/six relocations and clears
exactly132 bytes after four real SDK vector and one payload constructions.
The two14-byte auxiliaries remain unknown and receive no credit.

First probe is1,099 bytes with the same303 instructions because the outer RECT
precedes the packet in the frame. Nesting the real RECT/drawing scope yields
all1,132 bytes and the natural708-byte frame, with genuine rotation/swap locals
and four constructor temporaries. Adding the independent clear body keeps the
draw code unchanged and separately matches85 bytes. No spare storage, padding,
conditional bodies, masks, aliases or shortened extents. Original names/scopes
are not established by a compiler match.

All18 packets across the two bodies, saved ESI/EDI, full frame joins, four132-
byte copies and22 fields pass review. Wrong parameterized-ctor-ret12 and final-
draw-ret16 controls fail. Both17/28-byte cosine/sine wrapper pairs, both complete
174-byte runtime parents and13-byte auxiliary are rechecked against unchanged
R163/R128 evidence. Existing declarations and all97 unknown origins stay fixed;
no wrapper/runtime credit. Each new unit has its own canonical cold comparison,
sharing one serial object build. Old units were not rebuilt.

```bash
scripts/repo-python scripts/replay-exact-units.py --unit sprite-draw-0040ca80 --unit sprite-quad-clear-0040d990
```

All186 old units,91 canonical objects,156 inputs,218 origin files,nine shared
headers,91 active draft inputs and4,349 other rows remain unchanged. F009+128
additions retains554,045 bytes and158 inputs. Unknown97 origins and all old
unaccepted drafts receive no credit. Keep f093 native/attested/ABI/physical/
packet-model/math/cold/parent/progress/input/preservation evidence and all
probe sources, logs and PDBs. Full CI passes **3,603 tests in 126.739
seconds**, plus target/tracking, progress and whitespace checks. Removed three
obsolete reproducible probe objects (42,616 bytes) and scripts/tests
bytecode (8,282,705 bytes), after full final-preview/cold code and all22
relocation equality across both functions. All sources, inputs, logs, PDBs,
evidence and canonical objects remain.
## Previous accepted function: F092

R043 staff-roll timeline 00438D00..00439F8C is independently canonical cold
exact as `StaffTimeline438D00::RenderTimeline`: all 4,749 bytes, 1,215
instructions, 48 branches, 61 call packets and 117 physical fields. Three
following INT3 bytes stay outside the extent. Two new source/header inputs
contain one natural body and pointer-only scene/drawing interfaces. Original
R043 role/name is retained by alias; complete owner layouts remain unknown.

The complete timeline keeps 25 assignments to genuine unsigned begin/end
bounds, four real locals, all interval and unbounded-tail tests, 47 sprite
calls, state changes, scroll offsets and six byte-alpha conversions. Unsigned
subtractions use the native zero-extended qword FILD temporaries. Fade-in
multiply/divide ordering differs between actual phases and is preserved.
The final entry slide reuses the real offset local before subtracting from320.
Initial 4,739-byte/1,213-instruction expressions omitted that store; the genuine
offset assignment restores the full extent. The actual pivot value is12.

Third probe aligns every instruction/field but has159 actual bound/alpha frame
operand differences. Fourth probe gives bounds their outer scope, offset the
successful-frame scope and alpha a drawing scope. The full292-byte frame then
matches naturally. No spare locals, array growth, padding, aliasing, masking,
truncated comparisons or source splits. Original lexical scopes/names are not
proved by the match. All four locals are used by the actual timeline.

All seven complete callees and 61 packets are reviewed. Forty-seven DrawSprite
calls have36 argument bytes: index, float x/y, DWORD color, float pivots,
float scale/angle and byte flags. Six ftol2 calls consume ST0 without fabricated
C parameters. Every CFG/stack join passes; wrong ftol2-ret4/DrawSprite-ret32
controls fail. All117 fields bind61 direct calls and56 readonly scalar fields,
with exact float payloads, widths, permissions, operand positions and zero
addends. Standalone preview, independent canonical compilation and separate
canonical cold comparison match physically.

Native402660 propagates accepted BeginTarget's AL bool through both exits;
this timeline consumes AL. Existing accepted BeginFrame remains a void caller
interface/body and is unchanged. An address-named bool declaration views that
observed native return for this new caller; it introduces no second body,
wrapper, fake return or extra argument. Old header/source/object hashes stay
fixed. Original source prototype remains unknown; the typed entry view states
only the observed x86 return-register contract.

```bash
scripts/repo-python scripts/replay-exact-units.py --unit staff-timeline-00438d00
```

All185 old units,90 canonical objects,154 inputs,218 origin files,nine shared
headers,91 active draft inputs and4,350 other rows remain unchanged. No old
units were rebuilt. F009+126 additions retains552,828 bytes and156 inputs.
All97 origins remain unknown; F085 and every older large draft receive no
credit. Preserve f092 full native/attested/ABI/physical/cold/parent/progress/
input/preservation evidence, all probe sources, logs and PDBs. Full CI passes
**3,603 tests in 118.147 seconds**, plus target/tracking, progress
and whitespace checks. Removed four obsolete reproducible probe objects
(70,830 bytes) and scripts/tests bytecode (8,282,705 bytes),
after whole final-preview/cold code and all117 relocation equality. All
canonical objects, source/control inputs, logs, PDBs and evidence remain.

## Previous accepted function: F091

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
