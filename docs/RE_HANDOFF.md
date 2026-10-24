# TH075 function reconstruction handoff

Updated 2026-10-24. The user resumed reconstruction after the cleanup/handoff
checkpoint and set an active **98% authored bytes exact** goal. The objective
is incomplete. Continue the F107 fighter resource-loader investigation below; preserve F085 and the F066 draft.
Subsequent project phases remain deferred. Use existing Ghidra/local tools,
without REA; commit subjects must use `gpt-6.1-sol: ...`. Commits and pushes
remain authorized. Keep compiler builds serial and monitor CPU/memory.

## Verified checkpoint

| Measure | Current value |
| --- | --- |
| Provisional candidates | 4,351 |
| Reviewed authored / library / compiler | 1,002 / 2,671 / 581 |
| Unknown origins | 97, totaling 3,608 bytes |
| Source-present / exact functions / exact units | 207 / 207 / 207 |
| Exact code bytes | 579,023 |
| Reviewed authored coverage | 579,023 / 1,973,516 (29.34%) |
| Conservative coverage, including every pending byte | 579,023 / 1,977,124 (29.29%) |

The ledgers and status script are authoritative. Origin evidence through R268
is unchanged. The exact-adoption manifest retains F009 and **147 additions /
569,140 code bytes / 173 new source/header inputs**. F021/F048/F061/F066/F085 remain
unaccepted. Unknown origins receive no credit and do not block independently
reviewed authored functions.

The only target is the supplied Japanese `th075.exe`, reporting version 1.11:
SHA-256 `bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
Identity is pinned to the supplied archive, without independent official
provenance corroboration. Never substitute `th075c.exe` or patch target bytes.

## Latest accepted function: F106

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

## Current reconstruction cohort: F107

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
