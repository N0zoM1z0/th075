# Pending origin review matrix (R263 historical snapshot)

## Current follow-up

For `0x004591E0`, the real frame-header fields and two
`std::vector<tagRECT>` members reproduce the complete copy when the
16-byte prefix has a destructor. A probe using the existing trivial
`FighterFrameInfo` header layout instead emits 491 CODE bytes and omits
the prefix cleanup. The three native callers are `0x00458E70`,
`0x00459CB0`, and `0x0045B640`. The last caller passes the record
size `0x74` to placement new before invoking the copy.

An implicit copy constructor and an explicit initializer-list constructor
both reproduce 417 CODE bytes at `0x004591E0`, the 29-byte EH carrier at
`0x00656260`, and 44 bytes of unwind map and FuncInfo at `0x00669824`.
All 13 relocation fields resolve to their original destinations in both
builds. The prefix cleanup calls `0x004588B0` and the completed first
vector cleans up through `0x004589F0`. The two fully matching source
forms leave the original declaration and attribution unresolved.

The two VC7.1 builds use `/Od /Ob0 /Gy /GR- /GX /GS /Zi /I src` on
`.analysis/frame-copy-origin/owned-copy.cpp` with `/DEXPLICIT_COPY=0`
and `/DEXPLICIT_COPY=1`, producing
`build/probes/FrameCopyOriginOwnedImplicit.obj` and
`build/probes/FrameCopyOriginOwnedExplicit.obj`. Run
`scripts/repo-python .analysis/frame-copy-origin/compare.py` for the
complete comparisons.

### R272 — D3DX8 StringBuffer contribution

`0x00620132` and `0x006200DA` come from `obj\i386\cd3dxbuffer.obj`
in the pinned D3DX8 archive. The complete five-byte section 52 defines
`CD3DXStringBuffer::~CD3DXStringBuffer` and has one REL32 to its
base destructor at `0x0061FE0A`. The complete 24-byte section 43
defines `CD3DXBuffer::CD3DXBuffer`, calls the interface constructor
at `0x00620090`, and installs the vtable at `0x0065DE1C`.

The archive member replays 25 code sections and five data sections
with 54 relocation fields and zero linked byte differences. The vtable
and same-object call and jump destinations follow the actual COFF
definitions and weak fallback indices. This establishes library
provenance for both functions, using the same evidence standard as
[R039's D3DX8 forwarders](ORIGIN_REVIEW.md#r039--complete-d3dx8-destructor-forwarding-comdats).
R264 preserves the unresolved explicit-versus-implicit source forms.

The [R264 evidence](../config/sdk-string-buffer-review-evidence.json)
records the archive and member identities, all section placements and
the relocation bindings. The local replay is
`scripts/repo-python .analysis/sdk-string-buffer-origin/verify-contribution.py`.

### R273 — remaining D3DX8 lifetime bodies

The other 17 R265 SDK candidates account for 1,269 CODE bytes. Each
complete defining section in the pinned D3DX8 archive now compares
unmasked with the PE, including all 65 relocation fields. Whole
incoming SDK code sections also match and name the candidate through
a typed COFF reference. The replay compares each candidate's original
section, AUX records, fields, and linked bytes with the archived
shader/font, presentation, image, lifetime, blit, or graphics graph.
It derives relocation destinations from those source layouts, the
previous provider records, and the PE imports.

The canonical rows now record D3DX8 library provenance. The retained
R265 alternatives still describe uncertainty about private C++
declarations. The historical source graphs retain their original
snapshots and verify the complete linked sections when the current
origin row supersedes an unknown one.

[R265 defines the archive member and section of every candidate.](../config/sdk-compilation-witness-audit-evidence.json)
Run `scripts/repo-python .analysis/sdk-lifetime-origin/native-replay.py`
to replay the current set, or pass one address to check its scope.

### R274 — the game frame's optional extension cleanup

`0x004588B0` releases the optional extension of the game's 16-byte
frame prefix. The authored fighter pattern loader passes a real frame
to `0x00458790` at `0x00457AEB`. That routine allocates and clears the
36-byte extension at prefix offset `+8`. The loader then reads pose
fields into the extension. The nested record initializes the prefix
at offset zero at `0x004587FF` and calls its cleanup at `0x00458941`.
The construction unwind map's state zero reaches the same cleanup
through `0x006561C0`. The independent effects loader also initializes
and destroys the same stack prefix at `0x005F7214` and `0x005F7897`.

The full 43-byte body has a source-level null guard and one REL32 at
`+0x20` to scalar `operator delete` at `0x00640F15`. Direct `delete`
emits 34 bytes. Under `/Ob0`, implicit destruction of either an
`std::auto_ptr` member or a nested owning member instead emits a
22-byte outer destructor that calls the member destructor. The
`/Ob1` builds inline those operations into their caller through
different instruction sequences. The native frame-copy routine
copies the prefix words, including `+8`, without transferring
ownership from the source as `std::auto_ptr` copy construction does.

The accepted source pairs `::operator delete` with the existing
raw allocation through `::operator new`. It and both existing
prefix methods cold-replay exactly from one object. The full call
and unwind observations and probe comparisons run with
`scripts/repo-python .analysis/frame-prefix-origin/inspect.py`.

    scripts/repo-python scripts/replay-exact-units.py --unit record-prefix-destroy-004588b0 --unit record-prefix-reset-allocation-00458790 --unit record-prefix-zero-flag-00458880

### R275 — RECT vector clear and element destruction

The cold-exact 381-byte `std::vector<RECT>::operator=` at `0x0045AC50`
calls the real VC7.1 `clear()` symbol at `0x0045AC75` for an empty source.
From the same object, the complete 19-byte clear at `0x00458A80` calls
the 103-byte `_Tidy` at `0x00458DA0`. Its destruction path reaches
`allocator<RECT>::destroy` at `0x0045B290`, whose typed relocation calls
the complete five-byte `std::_Destroy<RECT>` at `0x0045B630`.

The RECT type comes from the independently recovered collision layout
and the exact whole vector assignment. The earlier R209 graph used a
generic 16-byte element. Replaying those same source edges with the
typed frame object matches nine cleanup sections and all nine
relocation fields, including the range loop and allocator call. The
clear and trivial destruction bodies therefore have independent
library attribution. Their byte-equivalent ordinary controls remain
valid for callers without a typed source reference.

    scripts/repo-python scripts/replay-exact-units.py --unit std-vector-rect-assignment --unit fighter-frame-info-assignment
    scripts/repo-python .analysis/rect-vector-clear/compare.py

### R276 — RECT const iterator increment

The pinned VC7.1 `std::vector<RECT>` copy constructor at `0x00459390`
reaches the 27-byte prefix increment at `0x0045B6F0` through
`_Ucopy`, `_Uninitialized_copy`, and `_Uninit_copy`. The relocation
at `0x0045B33E` in the last function names
`std::vector<RECT>::const_iterator::operator++`. All nine sections
in this chain, including both exception handlers and their unwind
and catch data, reproduce 696 original bytes and 38 relocations.
The R209 placements come from its generic element model. The new
build verifies them with the frame's concrete RECT type.

Build the frame-copy probe with `/DEXPLICIT_COPY=0` as above, then
run `scripts/repo-python .analysis/rect-vector-copy/compare.py`.

### R277 — Youmu history list helpers

Youmu's constructor, auxiliary update and round reset reach the same
`std::list<ObservedInputSnapshotF378>` at `this+0xFEC`. The exact
auxiliary update calls `push_back` at `0x00530225` and `pop_front`
at `0x00530246`. The round reset calls `clear` at `0x0052D1E8`.
The exact resource destructor at `0x0052D020` clears that member and
then calls its destructor at `0x0052D067`.

The typed `clear` COMDAT calls the complete link accessors at
`0x00531D80` and `0x00531D90`. The typed `_Insert` and `erase`
call `const_iterator::_Mynode` at `0x00532350`. The
node allocator reached from `clear` calls `std::_Destroy` at
`0x00532480`. Compiling the same list's destructor reproduces the
path through `_Tidy` and the node-pointer allocator to the second
`std::_Destroy` specialization at `0x00532500`.

Four authored callers cold-replay exactly. With the concrete snapshot
type substituted for the generic R216 carrier, 17 complete VC7.1
sections match the original 879 bytes and all 42 relocation fields.
The five newly attributed helpers account for 45 library bytes.
R216's ordinary getter and destruction controls still explain why
isolated bodies of these sizes cannot establish origin.

The destructor probe invokes `history.~SnapshotList()` on a reference
to the existing list type. Run these commands from the repository root
with the headless Wine settings in [SHARED_TOOLS.md](SHARED_TOOLS.md).

    scripts/repo-python scripts/replay-exact-units.py --unit youmu-fighter-initialize-0052cee0 --unit youmu-fighter-reset-round-0052d110 --unit character-aux-queue-and-mode-effects-005301b0 --unit character-resources-clear-and-release-base-0052d020
    scripts/compile-probe.sh .analysis/pending-origin-2026-11-24/youmu-destroy.cpp build/probes/YoumuListDestroyOrigin.obj /Od /Ob0 /Gy /GR- /GX- /Zi /I src
    scripts/repo-python .analysis/pending-origin-2026-11-24/compare-youmu.py

## Historical R263 inventory

**Historical as of R263, before F536:** the 97-row/3,608-byte table below is
retained as original research evidence, not the live 2026-10-30 inventory.
F536 subsequently classified and cold-exactly reconstructed `00455770`
(111 CODE bytes) on independent game-coordinate/x87/physical COFF evidence.
F555 independently identified the 77-byte game-local Shift-JIS lead-byte
classifier `0041CA30` via the only native caller, true hard-coded ranges,
and fresh 1/1 77-byte cold exact source compilation. The historical R183
unknown-provenance row in the R263 matrix remains as original negative
source evidence, not as a current pending classification. Original source
owner/type naming and possible vendored origin remain *provisional*.
F595 independently compiled one of the original pending leaves,
`004135F0`, into **40/40 byte-for-byte identical ordinary VC7.1
C++** with complete 16-instruction/RET12 shape and 0 COFF fields.
However, none of the 4,351 registered native functions calls it
directly, and its absolute address never appears as a literal
DWORD in the pinned PE file, so this is **source-shape proof,
NOT authored-origin proof**. It stays unknown and uncredited.
F595 also independently counted 36 original exact BackgroundStage
loader calls of R108 origin-unknown constructor `00449DE0`, its
pure-virtual vtable, and six mixed game/STL callers of
`004588B0`; those remain unknown. See
[small leaf/call graph F595](SMALL_ORIGIN_UNKNOWN_FIELDSETTER_F595.md).

The pending set reached **90 functions /3,315 bytes** at a later checkpoint.
Use `config/function-origins.csv` for the authoritative current
classification and `docs/RE_HANDOFF.md` for the active tasks.
F595–F691 ordinary VC7.1 source research now matches **85 distinct
complete original unknown-origin functions /1,949 machine CODE B**,
including F686's 19-byte destructor, F687's 58/64-byte COM owners and
F691's substantial **249-byte COM manager cleanup**. All 85 remain
historically **source-UNKNOWN**, no game-authored exact credit:
[F691 whole native proof](SDK_NATIVE_COM_MANAGER_CLEANUP_F691.md),
[F687 complete COM destructor source](SDK_NATIVE_COM_OWNER_DESTRUCTORS_F687.md).
Do not interpret `00455770` or `0041CA30` rows in the *historical*
R263 table as still pending. A byte-perfect compiler product alone
never resolves authored-vs-library provenance.

**Historical R263 table only:** the following 97 rows / 3,608 bytes
record what was unresolved **at the time of R263**, not today's live
90-row/3,315-byte queue. Some old rows have since been resolved by
F536 and F555; `004135F0` is byte-reproduced by F595 but still has
unknown provenance. Treat each row's evidence and needed witness as a
historical research lead; use live `config/function-origins.csv` for
present classification. This matrix does **not** mark the
complete-origin milestone achieved.

The target remains the supplied Japanese `th075.exe`, self-reporting version
1.11, SHA-256 `bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
**At the older R263 checkpoint**, the exact baseline was 60 functions
/9,883 bytes /60 units across eleven objects; the *current* accepted whole register is **986 exact
functions /871,717 CODE bytes** (live snapshot 2026-11-19). No new source, mapping or exact ledger credit is awarded by
this archived provenance matrix.

The original R251 audit covered all116 whole target bodies,114 RET-based
CFGs and both complete11-/5-byte native tail cases. R253 classifies two19-byte
library lifetimes through the complete paired same-global chain. R254 classifies
three19-byte vector destructors through independently accepted construction42
and actual completed-state EH cleanup of the same subobject. Their original
unknown snapshots remain preserved. R255 additionally classifies four19-byte
neighboring vector destructors through five independent construction-state links
and nine complete original EH frames; all four ordinary clear aliases stay
unknown. R256 classifies two72-byte outer game cleanup policies as inferred authored
through coherent whole construction/destruction, independent game allocation
and actual source-provider/EH context. Complete byte-positive implicit alternatives
and their incompatible construction/provider chains remain quarantined.
R257 classifies one72-byte deque outer cleanup as inferred authored through
coherent whole construction/destruction, real providers and independent game
parser same-local/state8 ownership. Genuine implicit72 positives and their
incompatible full construction/provider/EH chains remain preserved.
R260 classifies two zeroing leaves14/12 as inferred library through complete
source-ordered object contributions and defining-data/provider topology.
Genuine byte-positive ordinary leaf alternatives remain preserved.
R261 classifies two SDK stack read/reset8 policies as inferred library through
complete primary739/EH20/data36 source contributions. A coherent implicit
ctor16/dtor14 positive preserves the related destructor as unknown.
R262 classifies two identifier comparison23 leaves as inferred library through
complete Font/Surface source contributions and independently replayed GUID/
vtable/provider context; complete ordinary equality23 remains preserved.
R263 classifies only641DAA /11 as inferred library through complete original
abs11/abs64 auxiliary28 source-order contribution39. Separate labs-shaped11
and original ordinary int/long/wide alternatives remain unresolved.
The **historical R263** remaining projection counted 95
RET-based bodies and two native tail cases before later origin
reclassifications. This is NOT the current 94-function inventory. Every remaining whole
body hash and literal canonical pair is read back after these bounded transitions.

Original structured references are read back by exact JSON trail and original
record hash; current artifact file hashes are retained. Source/control/context
references below are representative discovery locations; a link is not proof
of ownership and does not replace that artifact's full original replay. A
missing discovered reference does not imply no previous investigation.

Private `.analysis/r263-remaining-review.json` retains the current literal
pairs, full body hashes/instructions/control flow, calls, non-stack writes,
all original structured trails/hashes and mapped PE absolute-value discovery.
Numeric offsets and unused argument observations do not establish complete
original C++ types or signatures. Raw value occurrence scans and candidate/
Ghidra reference observations do not rule out computed, interior, runtime or
unmodeled reachability. The original R251 artifact is retained without rewriting.

The categories group evidence gaps, not origins. All remaining rows have the
outcome **underdetermined origin**. The R263-era Web MCP acceptance remark was a historical request,
not a current requirement. The current workflow uses the pinned PE,
source provenance and **selected new/affected whole-unit cold replay**;
never run all 943 simply because a frozen R263 matrix says so.

| Address | Bytes | Evidence gap category | Whole target observation | Representative prior evidence | Required distinguishing witness |
| --- | ---: | --- | --- | --- | --- |
| `0x004073A0` | 11 | empty-body | 7 instructions; 0 branches; RET 0; 0 calls | No discovered structured record; full target audit retained. | Original empty-operation signature and owner. |
| `0x00409490` | 19 | default-or-lifetime | 9 instructions; 0 branches; RET 0; 1 calls | [member-vector-lifetime-origin-evidence.json](../config/member-vector-lifetime-origin-evidence.json); original whole audit | Original ordinary-clear versus vendor namespace; paired EH identifies a separate destructor. |
| `0x0040D8C0` | 22 | default-or-lifetime | 10 instructions; 0 branches; RET 0; 1 calls | [game-lifetime-origin-evidence.json](../config/game-lifetime-origin-evidence.json) | Outer lifetime/declaration and receiver identity. |
| `0x0040D8E0` | 19 | default-or-lifetime | 9 instructions; 0 branches; RET 0; 1 calls | [game-lifetime-origin-evidence.json](../config/game-lifetime-origin-evidence.json); [vector-count-assignment-origin-evidence.json](../config/vector-count-assignment-origin-evidence.json) | Outer lifetime/declaration and receiver identity. |
| `0x0040D900` | 17 | floating-or-geometry | 8 instructions; 0 branches; RET 0; 1 calls | [math-overload-origin-evidence.json](../config/math-overload-origin-evidence.json) | Typed operation/owner beyond ordinary math alternatives. |
| `0x0040D920` | 28 | floating-or-geometry | 12 instructions; 0 branches; RET 0; 1 calls | [math-overload-origin-evidence.json](../config/math-overload-origin-evidence.json) | Typed operation/owner beyond ordinary math alternatives. |
| `0x0040D940` | 17 | floating-or-geometry | 8 instructions; 0 branches; RET 0; 1 calls | [math-overload-origin-evidence.json](../config/math-overload-origin-evidence.json) | Typed operation/owner beyond ordinary math alternatives. |
| `0x0040D960` | 28 | floating-or-geometry | 12 instructions; 0 branches; RET 0; 1 calls | [math-overload-origin-evidence.json](../config/math-overload-origin-evidence.json) | Typed operation/owner beyond ordinary math alternatives. |
| `0x0040D980` | 14 | floating-or-geometry | 8 instructions; 0 branches; RET 0; 0 calls | [effect-manager-lifetime-origin-evidence.json](../config/effect-manager-lifetime-origin-evidence.json) | Typed operation/owner beyond ordinary math alternatives. |
| `0x0040D9F0` | 14 | floating-or-geometry | 8 instructions; 0 branches; RET 0; 0 calls | [effect-manager-lifetime-origin-evidence.json](../config/effect-manager-lifetime-origin-evidence.json) | Typed operation/owner beyond ordinary math alternatives. |
| `0x0040DE30` | 19 | default-or-lifetime | 9 instructions; 0 branches; RET 0; 1 calls | [member-vector-lifetime-origin-evidence.json](../config/member-vector-lifetime-origin-evidence.json); original whole audit | Original ordinary-clear versus vendor namespace; paired EH identifies a separate destructor. |
| `0x0040DF40` | 19 | default-or-lifetime | 9 instructions; 0 branches; RET 0; 1 calls | [member-vector-lifetime-origin-evidence.json](../config/member-vector-lifetime-origin-evidence.json); original whole audit | Original ordinary-clear versus vendor namespace; paired EH identifies a separate destructor. |
| `0x0040E9B0` | 16 | container-or-ordinary-leaf | 9 instructions; 0 branches; RET 0; 0 calls | [vector-list-leaf-alternatives-origin-evidence.json](../config/vector-list-leaf-alternatives-origin-evidence.json); [vector-endpoint-route-origin-evidence.json](../config/vector-endpoint-route-origin-evidence.json) | Original receiver/element and leaf source identity. |
| `0x0040EA20` | 16 | container-or-ordinary-leaf | 9 instructions; 0 branches; RET 0; 0 calls | [vector-list-leaf-alternatives-origin-evidence.json](../config/vector-list-leaf-alternatives-origin-evidence.json); [vector-endpoint-route-origin-evidence.json](../config/vector-endpoint-route-origin-evidence.json) | Original receiver/element and leaf source identity. |
| `0x0040F9F0` | 15 | default-or-lifetime | 7 instructions; 0 branches; RET 0; 1 calls | [vector-count-assignment-origin-evidence.json](../config/vector-count-assignment-origin-evidence.json); [deque-front-back-origin-evidence.json](../config/deque-front-back-origin-evidence.json) | Outer lifetime/declaration and receiver identity. |
| `0x00410FC0` | 24 | receiver-or-output-without-identity | 10 instructions; 0 branches; RET 4; 0 calls | [sprite-render-parameter-origin-evidence.json](../config/sprite-render-parameter-origin-evidence.json) | Independent same-owner/destination identity. |
| `0x00411C10` | 25 | default-or-lifetime | 11 instructions; 0 branches; RET 0; 1 calls | [game-lifetime-origin-evidence.json](../config/game-lifetime-origin-evidence.json); [deque-front-back-origin-evidence.json](../config/deque-front-back-origin-evidence.json) | Outer lifetime/declaration and receiver identity. |
| `0x00411E80` | 8 | container-or-ordinary-leaf | 5 instructions; 0 branches; RET 0; 0 calls | [list-node-link-alternatives-origin-evidence.json](../config/list-node-link-alternatives-origin-evidence.json); [list-recovery-origin-evidence.json](../config/list-recovery-origin-evidence.json) | Original receiver/element and leaf source identity. |
| `0x00411E90` | 11 | container-or-ordinary-leaf | 6 instructions; 0 branches; RET 0; 0 calls | [list-node-link-alternatives-origin-evidence.json](../config/list-node-link-alternatives-origin-evidence.json); [list-recovery-origin-evidence.json](../config/list-recovery-origin-evidence.json) | Original receiver/element and leaf source identity. |
| `0x004124B0` | 16 | container-or-ordinary-leaf | 9 instructions; 0 branches; RET 0; 0 calls | [vector-list-leaf-alternatives-origin-evidence.json](../config/vector-list-leaf-alternatives-origin-evidence.json); [vector-endpoint-route-origin-evidence.json](../config/vector-endpoint-route-origin-evidence.json) | Original receiver/element and leaf source identity. |
| `0x004124C0` | 11 | container-or-ordinary-leaf | 6 instructions; 0 branches; RET 0; 0 calls | [list-node-link-alternatives-origin-evidence.json](../config/list-node-link-alternatives-origin-evidence.json) | Original receiver/element and leaf source identity. |
| `0x00412580` | 5 | empty-body | 4 instructions; 0 branches; RET 0; 0 calls | [archive-list-policy-origin-evidence.json](../config/archive-list-policy-origin-evidence.json) | Original empty-operation signature and owner. |
| `0x00412600` | 5 | empty-body | 4 instructions; 0 branches; RET 0; 0 calls | [list-recovery-origin-evidence.json](../config/list-recovery-origin-evidence.json) | Original empty-operation signature and owner. |
| `0x00412D90` | 17 | floating-or-geometry | 8 instructions; 0 branches; RET 0; 1 calls | [math-overload-origin-evidence.json](../config/math-overload-origin-evidence.json) | Typed operation/owner beyond ordinary math alternatives. |
| `0x00412DB0` | 28 | floating-or-geometry | 12 instructions; 0 branches; RET 0; 1 calls | [math-overload-origin-evidence.json](../config/math-overload-origin-evidence.json) | Typed operation/owner beyond ordinary math alternatives. |
| `0x004135F0` | 40 | receiver-or-output-without-identity | 16 instructions; 0 branches; RET 0xc; 0 calls | No discovered structured record; full target audit and R259 FontSurface store-pattern/context retained. | Independent same-owner/destination identity. |
| `0x004138D0` | 11 | empty-body | 7 instructions; 0 branches; RET 0; 0 calls | No discovered structured record; full target audit retained. | Original empty-operation signature and owner. |
| `0x004169D0` | 11 | empty-body | 7 instructions; 0 branches; RET 0; 0 calls | No discovered structured record; full target audit retained. | Original empty-operation signature and owner. |
| `0x004170B0` | 27 | default-or-lifetime | 14 instructions; 0 branches; RET 0; 1 calls | [remaining-lifetime-policy-origin-evidence.json](../config/remaining-lifetime-policy-origin-evidence.json) | Outer lifetime/declaration and receiver identity. |
| `0x0041CA30` | 77 | receiver-or-output-without-identity | 28 instructions; 8 branches; RET 4; 0 calls | [font-byte-policy-origin-evidence.json](../config/font-byte-policy-origin-evidence.json) | Independent same-owner/destination identity. |
| `0x0041E100` | 8 | container-or-ordinary-leaf | 5 instructions; 0 branches; RET 0; 0 calls | [list-node-link-alternatives-origin-evidence.json](../config/list-node-link-alternatives-origin-evidence.json) | Original receiver/element and leaf source identity. |
| `0x0041E110` | 11 | container-or-ordinary-leaf | 6 instructions; 0 branches; RET 0; 0 calls | [list-node-link-alternatives-origin-evidence.json](../config/list-node-link-alternatives-origin-evidence.json) | Original receiver/element and leaf source identity. |
| `0x0041E330` | 14 | container-or-ordinary-leaf | 8 instructions; 0 branches; RET 0; 0 calls | [indexed-owner-policy-origin-evidence.json](../config/indexed-owner-policy-origin-evidence.json) | Original receiver/element and leaf source identity. |
| `0x0041F7E0` | 16 | container-or-ordinary-leaf | 9 instructions; 0 branches; RET 0; 0 calls | [vector-list-leaf-alternatives-origin-evidence.json](../config/vector-list-leaf-alternatives-origin-evidence.json); [vector-endpoint-route-origin-evidence.json](../config/vector-endpoint-route-origin-evidence.json) | Original receiver/element and leaf source identity. |
| `0x0041F7F0` | 11 | container-or-ordinary-leaf | 6 instructions; 0 branches; RET 0; 0 calls | [archive-iterator-operation-origin-evidence.json](../config/archive-iterator-operation-origin-evidence.json) | Original receiver/element and leaf source identity. |
| `0x0041F9F0` | 5 | empty-body | 4 instructions; 0 branches; RET 0; 0 calls | [deque-retreat-origin-evidence.json](../config/deque-retreat-origin-evidence.json) | Original empty-operation signature and owner. |
| `0x0041FDF0` | 5 | empty-body | 4 instructions; 0 branches; RET 0; 0 calls | [deque-retreat-origin-evidence.json](../config/deque-retreat-origin-evidence.json) | Original empty-operation signature and owner. |
| `0x004229C0` | 15 | default-or-lifetime | 7 instructions; 0 branches; RET 0; 1 calls | [allocator-destroy-origin-evidence.json](../config/allocator-destroy-origin-evidence.json) | Outer lifetime/declaration and receiver identity. |
| `0x004229D0` | 28 | default-or-lifetime | 12 instructions; 0 branches; RET 4; 1 calls | [deque-copy-insert-origin-evidence.json](../config/deque-copy-insert-origin-evidence.json); [deque-leaf-origin-evidence.json](../config/deque-leaf-origin-evidence.json) | Outer lifetime/declaration and receiver identity. |
| `0x00423B20` | 26 | default-or-lifetime | 11 instructions; 0 branches; RET 0; 2 calls | [queue-lifetime-origin-evidence.json](../config/queue-lifetime-origin-evidence.json) | Outer lifetime/declaration and receiver identity. |
| `0x004251C0` | 34 | default-or-lifetime | 13 instructions; 0 branches; RET 0; 1 calls | [game-lifetime-origin-evidence.json](../config/game-lifetime-origin-evidence.json); [deque-front-back-origin-evidence.json](../config/deque-front-back-origin-evidence.json) | Outer lifetime/declaration and receiver identity. |
| `0x00428D20` | 17 | floating-or-geometry | 8 instructions; 0 branches; RET 0; 1 calls | [math-overload-origin-evidence.json](../config/math-overload-origin-evidence.json) | Typed operation/owner beyond ordinary math alternatives. |
| `0x00428D40` | 28 | floating-or-geometry | 12 instructions; 0 branches; RET 0; 1 calls | [math-overload-origin-evidence.json](../config/math-overload-origin-evidence.json) | Typed operation/owner beyond ordinary math alternatives. |
| `0x0042E580` | 5 | empty-body | 4 instructions; 0 branches; RET 0; 0 calls | [allocator-destroy-origin-evidence.json](../config/allocator-destroy-origin-evidence.json) | Original empty-operation signature and owner. |
| `0x00438A60` | 17 | floating-or-geometry | 8 instructions; 0 branches; RET 0; 1 calls | [game-switch-policy-origin-evidence.json](../config/game-switch-policy-origin-evidence.json) | Typed operation/owner beyond ordinary math alternatives. |
| `0x00438CF0` | 11 | empty-body | 7 instructions; 0 branches; RET 0; 0 calls | No discovered structured record; full target audit retained. | Original empty-operation signature and owner. |
| `0x00441FD0` | 5 | empty-body | 4 instructions; 0 branches; RET 0; 0 calls | No discovered structured record; full target audit retained. | Original empty-operation signature and owner. |
| `0x00442040` | 28 | floating-or-geometry | 12 instructions; 0 branches; RET 0; 1 calls | No discovered structured record; full target audit retained. | Typed operation/owner beyond ordinary math alternatives. |
| `0x00449A60` | 17 | floating-or-geometry | 8 instructions; 0 branches; RET 0; 1 calls | [math-overload-origin-evidence.json](../config/math-overload-origin-evidence.json) | Typed operation/owner beyond ordinary math alternatives. |
| `0x00449A80` | 28 | floating-or-geometry | 12 instructions; 0 branches; RET 0; 1 calls | [math-overload-origin-evidence.json](../config/math-overload-origin-evidence.json) | Typed operation/owner beyond ordinary math alternatives. |
| `0x00449DE0` | 45 | default-or-lifetime | 16 instructions; 0 branches; RET 0; 2 calls | [game-lifetime-origin-evidence.json](../config/game-lifetime-origin-evidence.json); [deque-front-back-origin-evidence.json](../config/deque-front-back-origin-evidence.json) | Outer lifetime/declaration and receiver identity. |
| `0x00454C00` | 24 | receiver-or-output-without-identity | 9 instructions; 0 branches; RET 0; 0 calls | [scene-shared-value-origin-evidence.json](../config/scene-shared-value-origin-evidence.json) | Independent same-owner/destination identity. |
| `0x00454F70` | 31 | receiver-or-output-without-identity | 15 instructions; 0 branches; RET 0; 0 calls | [scene-shared-value-origin-evidence.json](../config/scene-shared-value-origin-evidence.json) | Independent same-owner/destination identity. |
| `0x00455770` | 111 | receiver-or-output-without-identity | 29 instructions; 0 branches; RET 8; 0 calls | [paired-clear-policy-origin-evidence.json](../config/paired-clear-policy-origin-evidence.json) | Independent same-owner/destination identity. |
| `0x00458650` | 31 | default-or-lifetime | 12 instructions; 0 branches; RET 0; 1 calls | [archive-list-policy-origin-evidence.json](../config/archive-list-policy-origin-evidence.json) | Outer lifetime/declaration and receiver identity. |
| `0x00458670` | 23 | default-or-lifetime | 10 instructions; 0 branches; RET 0; 0 calls | [archive-list-policy-origin-evidence.json](../config/archive-list-policy-origin-evidence.json) | Outer lifetime/declaration and receiver identity. |
| `0x00458770` | 22 | default-or-lifetime | 10 instructions; 0 branches; RET 0; 1 calls | No discovered structured record; full target audit retained. | Outer lifetime/declaration and receiver identity. |
| `0x004588B0` | 43 | default-or-lifetime | 17 instructions; 1 branches; RET 0; 1 calls | [neighbor-policy-origin-evidence.json](../config/neighbor-policy-origin-evidence.json); [deque-front-back-origin-evidence.json](../config/deque-front-back-origin-evidence.json) | Outer lifetime/declaration and receiver identity. |
| `0x00458A80` | 19 | default-or-lifetime | 9 instructions; 0 branches; RET 0; 1 calls | [neighbor-vector-lifetime-origin-evidence.json](../config/neighbor-vector-lifetime-origin-evidence.json); original whole audit | Original ordinary-clear versus vendor namespace; whole inherited Cleanup19 and parent93/75 counterexamples preserved. |
| `0x00458B50` | 19 | default-or-lifetime | 9 instructions; 0 branches; RET 0; 1 calls | [neighbor-vector-lifetime-origin-evidence.json](../config/neighbor-vector-lifetime-origin-evidence.json); original whole audit | Original ordinary-clear versus vendor namespace; whole inherited Cleanup19 and parent93/75 counterexamples preserved. |
| `0x00458C20` | 19 | default-or-lifetime | 9 instructions; 0 branches; RET 0; 1 calls | [neighbor-vector-lifetime-origin-evidence.json](../config/neighbor-vector-lifetime-origin-evidence.json); original whole audit | Original ordinary-clear versus vendor namespace; whole inherited Cleanup19 and parent93/75 counterexamples preserved. |
| `0x004591E0` | 417 | mixed-member-copy | 128 instructions; 0 branches; RET 4; 2 calls | [neighbor-policy-origin-evidence.json](../config/neighbor-policy-origin-evidence.json) | Original copy syntax and member types. |
| `0x0045AAE0` | 368 | mixed-member-copy | 118 instructions; 0 branches; RET 4; 2 calls | [neighbor-policy-origin-evidence.json](../config/neighbor-policy-origin-evidence.json) | Original copy syntax and member types. |
| `0x0045B630` | 5 | empty-body | 4 instructions; 0 branches; RET 0; 0 calls | [neighbor-policy-origin-evidence.json](../config/neighbor-policy-origin-evidence.json) | Original empty-operation signature and owner. |
| `0x0045B6B0` | 15 | default-or-lifetime | 7 instructions; 0 branches; RET 0; 1 calls | [neighbor-policy-origin-evidence.json](../config/neighbor-policy-origin-evidence.json) | Outer lifetime/declaration and receiver identity. |
| `0x0045B6F0` | 27 | container-or-ordinary-leaf | 13 instructions; 0 branches; RET 0; 0 calls | [neighbor-policy-origin-evidence.json](../config/neighbor-policy-origin-evidence.json) | Original receiver/element and leaf source identity. |
| `0x0045B850` | 13 | empty-body | 7 instructions; 0 branches; RET 4; 0 calls | No discovered structured record; full target audit retained. | Original empty-operation signature and owner. |
| `0x00483300` | 21 | floating-or-geometry | 10 instructions; 0 branches; RET 0; 1 calls | No discovered structured record; full target audit retained. | Typed operation/owner beyond ordinary math alternatives. |
| `0x00483320` | 37 | floating-or-geometry | 15 instructions; 0 branches; RET 0; 1 calls | No discovered structured record; full target audit retained. | Typed operation/owner beyond ordinary math alternatives. |
| `0x00531D80` | 8 | container-or-ordinary-leaf | 5 instructions; 0 branches; RET 0; 0 calls | [list-head-erase-origin-evidence.json](../config/list-head-erase-origin-evidence.json) | Original receiver/element and leaf source identity. |
| `0x00531D90` | 11 | container-or-ordinary-leaf | 6 instructions; 0 branches; RET 0; 0 calls | [list-head-erase-origin-evidence.json](../config/list-head-erase-origin-evidence.json) | Original receiver/element and leaf source identity. |
| `0x00532350` | 16 | container-or-ordinary-leaf | 9 instructions; 0 branches; RET 0; 0 calls | [list-head-erase-origin-evidence.json](../config/list-head-erase-origin-evidence.json) | Original receiver/element and leaf source identity. |
| `0x00532480` | 5 | empty-body | 4 instructions; 0 branches; RET 0; 0 calls | [list-head-erase-origin-evidence.json](../config/list-head-erase-origin-evidence.json) | Original empty-operation signature and owner. |
| `0x00532500` | 5 | empty-body | 4 instructions; 0 branches; RET 0; 0 calls | [list-head-erase-origin-evidence.json](../config/list-head-erase-origin-evidence.json) | Original empty-operation signature and owner. |
| `0x00540280` | 11 | container-or-ordinary-leaf | 6 instructions; 0 branches; RET 0; 0 calls | [character-list-front-origin-evidence.json](../config/character-list-front-origin-evidence.json) | Original receiver/element and leaf source identity. |
| `0x005F8020` | 19 | default-or-lifetime | 9 instructions; 0 branches; RET 0; 1 calls | [neighbor-vector-lifetime-origin-evidence.json](../config/neighbor-vector-lifetime-origin-evidence.json); original whole audit | Original ordinary-clear versus vendor namespace; whole inherited Cleanup19 and parent93/75 counterexamples preserved. |
| `0x005FAAD0` | 15 | default-or-lifetime | 7 instructions; 0 branches; RET 0; 1 calls | [paired-clear-policy-origin-evidence.json](../config/paired-clear-policy-origin-evidence.json); [deque-front-back-origin-evidence.json](../config/deque-front-back-origin-evidence.json) | Outer lifetime/declaration and receiver identity. |
| `0x00608D8E` | 58 | sdk-private-lifetime | 22 instructions; 3 branches; RET 0; 4 calls | [background-counter-origin-evidence.json](../config/background-counter-origin-evidence.json) | Private member/outer lifetime or native forwarding declarations. |
| `0x00608F7B` | 27 | sdk-private-lifetime | 8 instructions; 0 branches; RET 0; 0 calls | [background-counter-origin-evidence.json](../config/background-counter-origin-evidence.json) | Private member/outer lifetime or native forwarding declarations. |
| `0x00608F96` | 64 | sdk-private-lifetime | 27 instructions; 3 branches; RET 0; 3 calls | [sdk-presentation-origin-evidence.json](../config/sdk-presentation-origin-evidence.json) | Private member/outer lifetime or native forwarding declarations. |
| `0x00609AA4` | 30 | sdk-private-lifetime | 9 instructions; 0 branches; RET 0; 0 calls | [background-counter-origin-evidence.json](../config/background-counter-origin-evidence.json) | Private member/outer lifetime or native forwarding declarations. |
| `0x00609F58` | 39 | sdk-private-lifetime | 12 instructions; 0 branches; RET 0; 0 calls | [background-counter-origin-evidence.json](../config/background-counter-origin-evidence.json) | Private member/outer lifetime or native forwarding declarations. |
| `0x0060B728` | 104 | sdk-private-lifetime | 34 instructions; 1 branches; RET 0; 0 calls | [background-counter-origin-evidence.json](../config/background-counter-origin-evidence.json) | Private member/outer lifetime or native forwarding declarations. |
| `0x0060C120` | 11 | sdk-private-lifetime | 4 instructions; 2 branches; RET 0; 0 calls | [sdk-image-chain-origin-evidence.json](../config/sdk-image-chain-origin-evidence.json); [deque-front-back-origin-evidence.json](../config/deque-front-back-origin-evidence.json) | Private member/outer lifetime or native forwarding declarations. |
| `0x0060C12B` | 169 | sdk-private-lifetime | 45 instructions; 0 branches; RET 0; 10 calls | [sdk-graphics-origin-evidence.json](../config/sdk-graphics-origin-evidence.json); [sdk-shader-font-origin-evidence.json](../config/sdk-shader-font-origin-evidence.json) | Private member/outer lifetime or native forwarding declarations. |
| `0x0060C1D4` | 143 | sdk-private-lifetime | 38 instructions; 0 branches; RET 0; 10 calls | [sdk-graphics-origin-evidence.json](../config/sdk-graphics-origin-evidence.json); [sdk-shader-font-origin-evidence.json](../config/sdk-shader-font-origin-evidence.json) | Private member/outer lifetime or native forwarding declarations. |
| `0x0060EA69` | 14 | sdk-private-lifetime | 6 instructions; 1 branches; RET 0; 1 calls | [sdk-image-entry-origin-evidence.json](../config/sdk-image-entry-origin-evidence.json) | Private member/outer lifetime or native forwarding declarations. |
| `0x0060EBCD` | 89 | sdk-private-lifetime | 38 instructions; 6 branches; RET 0; 6 calls | [sdk-image-chain-origin-evidence.json](../config/sdk-image-chain-origin-evidence.json) | Private member/outer lifetime or native forwarding declarations. |
| `0x00614BC6` | 6 | sdk-private-lifetime | 3 instructions; 0 branches; RET 0; 0 calls | [sdk-blit-origin-evidence.json](../config/sdk-blit-origin-evidence.json); [sdk-image-entry-origin-evidence.json](../config/sdk-image-entry-origin-evidence.json) | Private member/outer lifetime or native forwarding declarations. |
| `0x0061535A` | 19 | sdk-private-lifetime | 5 instructions; 0 branches; RET 0; 1 calls | [sdk-blit-origin-evidence.json](../config/sdk-blit-origin-evidence.json); [sdk-lifetime-alternatives-origin-evidence.json](../config/sdk-lifetime-alternatives-origin-evidence.json) | Private member/outer lifetime or native forwarding declarations. |
| `0x0061572C` | 160 | sdk-private-lifetime | 49 instructions; 6 branches; RET 0; 5 calls | [sdk-blit-origin-evidence.json](../config/sdk-blit-origin-evidence.json); [sdk-lifetime-alternatives-origin-evidence.json](../config/sdk-lifetime-alternatives-origin-evidence.json) | Private member/outer lifetime or native forwarding declarations. |
| `0x0061A453` | 73 | sdk-private-lifetime | 23 instructions; 1 branches; RET 0; 4 calls | [sdk-blit-origin-evidence.json](../config/sdk-blit-origin-evidence.json); [sdk-lifetime-alternatives-origin-evidence.json](../config/sdk-lifetime-alternatives-origin-evidence.json) | Private member/outer lifetime or native forwarding declarations. |
| `0x0061F125` | 249 | sdk-private-lifetime | 104 instructions; 17 branches; RET 0; 10 calls | [sdk-shader-font-origin-evidence.json](../config/sdk-shader-font-origin-evidence.json) | Private member/outer lifetime or native forwarding declarations. |
| `0x0061FB37` | 14 | sdk-private-lifetime | 7 instructions; 1 branches; RET 0; 1 calls | [sdk-graphics-origin-evidence.json](../config/sdk-graphics-origin-evidence.json); [sdk-shader-font-origin-evidence.json](../config/sdk-shader-font-origin-evidence.json) | Original explicit versus generated special-member declaration; R261 preserves coherent implicit ctor16/dtor14 equality. |
| `0x006200DA` | 24 | sdk-private-lifetime | 6 instructions; 0 branches; RET 0; 0 calls | [background-counter-origin-evidence.json](../config/background-counter-origin-evidence.json) | Private member/outer lifetime or native forwarding declarations. |
| `0x00620132` | 5 | sdk-private-lifetime | 1 instructions; 1 branches; RET tail only; 0 calls | [deque-front-back-origin-evidence.json](../config/deque-front-back-origin-evidence.json) | Private member/outer lifetime or native forwarding declarations. |
| `0x00641FB8` | 11 | floating-or-geometry | 5 instructions; 1 branches; RET 0; 0 calls | [game-switch-policy-origin-evidence.json](../config/game-switch-policy-origin-evidence.json) | Typed operation/owner beyond ordinary math alternatives. |

Totals: 97 pending candidates /3,608 bytes; 97 unknown origins.

R253 resolves the former `0x004065D0` /19 and `0x004065F0` /19 rows as library
lifetimes using [the complete paired global-vector proof](ORIGIN_REVIEW.md#r253--complete-paired-global-vector-library-lifetimes)
and [the immutable evidence manifest](../config/global-vector-lifetime-origin-evidence.json).
Ordinary19-byte cleanup and15-byte global callback source positives are
retained explicitly; they do not establish ownership alone. The accepted
confidence concerns the library family, with original element types and the
precise destructor/clear source alias remaining provisional.

R254 removes three complete vector destructor19 bodies through independent
same-receiver construction states and actual EH cleanup. The three ordinary
clear aliases remain in the matrix, with whole inherited Cleanup19 positives.
See [the R254 review](ORIGIN_REVIEW.md#r254--complete-same-receiver-vector-subobject-destruction)
and [its immutable evidence](../config/member-vector-lifetime-origin-evidence.json).
The original element endpoint40F9F0 /15 and protected40D8E0 /19 remain unknown.
R255 removes four complete vector destructor19 bodies, while the four
ordinary clear aliases remain unknown. Complete ordinary parent93/75 positives
and both original element destruction15 boundaries are retained.
See [the R255 review](ORIGIN_REVIEW.md#r255--complete-neighboring-vector-destruction-and-ordinary-parent-counterexamples)
and [its immutable evidence](../config/neighbor-vector-lifetime-origin-evidence.json).
Current total:107 candidates /3923 bytes, all with unresolved origins.
