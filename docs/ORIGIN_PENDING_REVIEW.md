# Origin evidence after R263

The [remaining origin evidence](#r288--remaining-origin-evidence) table
tracks open cases against the live origin ledger. The R263 matrix at the
end records the starting inventory.

## Frame copy groundwork

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
vector cleans up through `0x004589F0`. R297 distinguishes the forms
through their linked order inside the typed vector code.

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

### R278 — Youmu history list value accessor

The exact `YoumuObject::Advance` reads the same queue through its
typed `front()` call at `0x005365FF`. The cold build covers all 40,466
bytes of the comparison, including the switch table. That object
also emits the complete R243 front chain through mutable and const
iterator dereference. The latter calls the 11-byte `_Myval` at
`0x00540280` from `0x0054026D`. The branch through `begin` rejoins
the same constructor and next-link sections seen in the writer.
All eight sections in the front chain match 189 original bytes and
all seven relocations with the concrete snapshot type.

    scripts/repo-python scripts/replay-exact-units.py --unit youmu-object-advance-00536400
    scripts/repo-python .analysis/pending-origin-2026-11-24/compare-youmu-front.py

### R279 — Archive entry list helpers

The append routine at `0x0041D6C0` builds a 108-byte entry with a
100-byte filename and two DWORDs. The lookup at `0x0041D800` reads
those same fields through the iterator. The typed scratch build uses
`std::list<ArchiveWireEntryF342>` at `this+4` in both methods. It
reproduces all 313 bytes of the two complete functions and all 17
relocations, including the original `push_back` at `0x0041D9C0`,
`begin` at `0x0041D950` and iterator arrow at `0x0041E060`.

The archive constructor and destructor cold-replay their calls on
that same member, including `clear` at `0x0041D9F0`. Compiling
construction and destruction of the concrete list also reaches the
allocator constructor and both `std::_Destroy` specializations. In
total, 28 library sections match all 978 original bytes and 39
relocations. The chain attributes seven helpers and 70 library bytes.
The typed build uses the wire layout already observed by the game
callers. The generic source alternatives in R169, R175, R181 and R242
remain useful for comparing ambiguous bodies in isolation.

    scripts/repo-python scripts/replay-exact-units.py --unit data-archive-initialize-state-0041d190 --unit data-archive-close-entries-0041d1f0
    scripts/compile-probe.sh .analysis/pending-origin-2026-11-24/archive-list.cpp build/probes/ArchiveListOrigin.obj /Od /Ob0 /Gy /GR- /GX- /GS /Zi /I src
    scripts/repo-python .analysis/pending-origin-2026-11-24/compare-archive.py

### R280 — Sprite history list helpers

The 164-byte `SpriteHistoryElementF325` accounts for the fields read
by the render loop and written by the append routine. Substituting the
concrete `std::list` at `this+4` reproduces all 183 bytes of the
append routine at `0x00411000`, including all four relocations. Its
typed push and pop calls reach insertion and erase through the same
node links. The cold-exact render loop calls the same list's
iterator arrow, which reaches the complete value accessor.

Three existing caller units cold-replay. The typed list's 28 complete
sections reproduce 1,146 original bytes and all 50 relocation fields.
The six newly attributed helpers account for 56 library bytes. The
same object also emits the complete 25-byte element constructor at
`0x00411C10`, including its quad constructor call. This establishes
the element lifetime and allows a separate comparison of implicit and
explicit declaration forms.

    scripts/repo-python scripts/replay-exact-units.py --unit sprite-sequence-render-elements-00411110 --unit command-list-initialize-defaults-00410f30 --unit command-list-clear-entries-004110f0
    scripts/compile-probe.sh .analysis/final-origin-review/sprite-list.cpp build/probes/SpriteHistoryListOrigin.obj /Od /Ob0 /Gy /GR- /GX- /GS /Zi /I src
    scripts/repo-python .analysis/final-origin-review/compare-sprite.py

### R281 — Actor frame flag predicate

The 31-byte predicate at `0x00454F70` follows the animation frame
pointer at `Actor+0x74`, reads the DWORD at frame offset `0x3C` and
returns whether bit `0x20` is set. The exact Meiling action dispatcher
independently follows the same pointer and tests the same bit at
`0x005E248B` before taking the action branch. This identifies the
predicate as game-specific frame logic. The original symbol and C++
declaration remain unknown.

The existing natural source uses the shared Actor layout and takes the
only observed argument in ECX. It cold-replays all 31 bytes with zero
relocation fields.

    scripts/repo-python scripts/replay-exact-units.py --unit actor-frame-flag20-predicate-00454f70 --unit character-action-dispatch-005e2310

### R282 — D3DXVECTOR4 default constructor

The pinned D3DX8 header emits the complete 14-byte constructor at
`0x0040D980` in three cold-exact objects. The scaled draw calls it
for a temporary coordinate vector at `0x0040D5A7`. The default quad
and atlas constructors call the same symbol for four 16-byte
members, independently identifying the SDK type. The complete
14-byte COMDAT has zero relocations and zero differences in all
three objects. The separate empty constructor at `0x0040D9F0`
receives the quad payload at offset `0x40`, whose original type
and declaration remain open.

    scripts/repo-python scripts/replay-exact-units.py --unit sprite-drawing-scaled-native-0040d2e0 --unit sprite-quad-clear-0040d990 --unit atlas-quad-rectangle-constructor-0040da00
    scripts/repo-python .analysis/final-origin-review/compare-d3dx-vector.py

### R283 — Texture vector clear, dereference and destruction

The texture slot reset at `0x0040B250` and texture resolution at
`0x0040C8C0` exactly reproduce their complete 33- and 162-byte bodies
with the real vectors at `this+8` and `this+0x18`. The first
vector holds 44-byte entries. The second holds texture interface
pointers, and the resolver returns an element of that type. A local
reference to the entry adds a stack store and changes the resolver
to 169 bytes. Reading the field directly matches the native body.

The typed `clear` sections reach the two different `_Tidy` sections.
The two index functions reach the const dereference specializations.
The 44-byte entry's cleanup also follows `_Destroy_range` and the
allocator method to `std::_Destroy` at `0x0040F9F0`. Its complete
scalar-deleting target calls the entry destructor at `0x0040D8E0`
with the proper lifetime semantics. Whether the entry destructor
was declared explicitly remains open.

Eighteen complete sections, including the two game callers,
reproduce all 820 bytes and 35 relocations. This attributes five
helpers and 85 library bytes.

    scripts/compile-probe.sh .analysis/final-origin-review/texture-vectors.cpp build/probes/TextureVectorsOriginDirect.obj /Od /Ob0 /Gy /GR- /GX- /Zi /I src
    scripts/repo-python .analysis/final-origin-review/compare-textures.py

### R284 — Pattern and effect vector cleanup

The typed fighter pattern loader matches the complete 3,696-byte
function and all 171 relocations. It clears the 116-byte record
vector at `0x00458B50` before deleting each sequence, then clears
the pointer vector at `0x00458C20`. Their `_Tidy` sections dispatch
to the nontrivial and scalar pointer range paths respectively.
The typed frame allocator reaches `std::_Destroy` at
`0x0045B6B0`, whose scalar-deleting callee calls the independently
known record destructor at `0x004588E0`.

The cold-exact effect loader parses the 16-byte prefix record and
calls the sequence clear at `0x005F8020`. The same concrete record in
the typed sequence constructor and destructor reproduces the full
vector cleanup through `std::_Destroy` at `0x005FAAD0` and the
prefix destructor at `0x004588B0`. The two typed objects reproduce
32 complete functions, 4,990 bytes and 226 relocations. The five
newly attributed helpers account for 87 library bytes.

    scripts/repo-python scripts/replay-exact-units.py --unit fighter-pattern-load-00457660 --unit record16-construct-clear-005f7f20 --unit record16-clear-then-destroy-005f7ed0 --unit effects-load-pattern-catalog-005f71f0
    scripts/compile-probe.sh .analysis/final-origin-review/fighter-pattern-vectors.cpp build/probes/FighterPatternVectorsOrigin.obj /Od /Ob0 /Gy /GR- /GX /GS /Zi /I src
    scripts/compile-probe.sh .analysis/final-origin-review/effect-pattern-vectors.cpp build/probes/EffectPatternVectorsOrigin.obj /Od /Ob0 /Gy /GR- /GX /GS /Zi /I src
    scripts/repo-python .analysis/final-origin-review/compare-pattern-vectors.py

### R285 — Empty sound and staff-roll hooks and the progress destructor

The fighter constructor constructs the sound member at `this+0x6D0`
at `0x0045682F` and calls the empty `0x004073A0` on that same live
member at `0x00456853`. Its explicit constructor and destructor are
already known. The staff-roll advance calls the empty `0x00438CF0`
on its live scene at `0x00438C42` and then continues the scene's time
and result logic. Both original call sites identify game hooks.

The startup table at `0x0066C024` invokes the initializer at
`0x00656DE0`, which constructs the progress records at `0x006718F8`
and registers `0x00656ED0` with `atexit`. The finalizer packs the
same receiver into ECX and calls `0x004169D0`. With a user-defined
empty destructor the pinned compiler produces the complete 28-byte
initializer, 15-byte finalizer and 11-byte destructor with matching
bytes and all six fields. The otherwise identical control with a
trivial implicit destructor emits only the 15-byte initializer and
constructor call.

All three new 11-byte functions and both modified caller units
cold-replay exactly. The historical spellings of the hook and
destructor declarations are unknown.

    scripts/repo-python scripts/replay-exact-units.py --unit fighter-sound-configure-004073a0 --unit progress-records-destructor-004169d0 --unit staffroll-advance-hook-00438cf0 --unit fighter-state-initialize-004567b0 --unit staffroll-scene-complete-advance-00438c20
    scripts/compile-probe.sh .analysis/final-origin-review/global-destructor.cpp build/probes/ProgressDestructor-0.obj /Od /Ob0 /Gy /GR- /GX- /Zi /DEXPLICIT_DTOR=0
    scripts/compile-probe.sh .analysis/final-origin-review/global-destructor.cpp build/probes/ProgressDestructor-1.obj /Od /Ob0 /Gy /GR- /GX- /Zi /DEXPLICIT_DTOR=1
    scripts/repo-python .analysis/final-origin-review/compare-global-destructor.py

### R286 — Sound buffer and replay and script deque helpers

The complete 367-byte wave directory loader matches with a typed
`std::vector<IDirectSoundBuffer8*>`. It releases each buffer, then
calls the 19-byte vector clear at `0x00409490`. The complete clear,
`_Tidy`, range destruction dispatch and deallocator match.

The 613-byte replay file scan matches with a deque of the 60-byte
file header it reads, then pushes. The independently cold-replayed
scene destructor supplies the lifetime call. The typed deque's
destructor and pop path reach the five-byte header destruction at
`0x0042E580`.

The typed script parser matches its 2,429-byte extent, including the
switch table and all 119 relocations. Its push of the 20-byte script
sequence identifies the deque whose cleanup reaches `0x004229C0`.
The complete scalar-deleting callee calls the verified script
sequence destructor at `0x004212A0`. With that same concrete type,
both the implicit sequence copy constructor and the explicit
member-copy form reproduce `0x004229D0` and its deque copy call.
R296 distinguishes the two forms by the order of their linked
code.

    scripts/compile-probe.sh .analysis/final-origin-review/sound-vector.cpp build/probes/sound-vector.obj /Od /Ob0 /Gy /GR- /GX- /GS /Zi /I src
    scripts/compile-probe.sh .analysis/final-origin-review/replay-deque.cpp build/probes/replay-deque.obj /Od /Ob0 /Gy /GR- /GX- /GS /Zi /I src
    scripts/repo-python scripts/replay-exact-units.py --unit replay-browser-destroy-owned-files-0042c560
    scripts/repo-python .analysis/final-origin-review/compare-sound-replay.py
    scripts/compile-probe.sh .analysis/final-origin-review/script-deques.cpp build/probes/ScriptDequeOrigin.obj /Od /Ob0 /Gy /GR- /GX /GS /Zi /I src
    scripts/compile-probe.sh .analysis/final-origin-review/script-deques-explicit.cpp build/probes/ScriptDequeExplicitCopy.obj /Od /Ob0 /Gy /GR- /GX /GS /Zi /I src
    scripts/repo-python .analysis/final-origin-review/compare-script-deque.py

### R287 — Sprite capacity and text raster setters

The sprite sequence constructor writes the signed short at `this+0x12`
at `0x00410F69`. The append routine reads it as the list limit at
`0x00411099`, and the render routine divides by it when computing
fade at `0x004112C0`. The setter at `0x00410FC0` reproduces all 24
bytes using the already named capacity field in the constructor's
class.

The complete text renderer writes the color byte and raster offsets
at `0x004134D0`, `0x004134D6` and `0x004134E0`. It consumes the color
in the tint call and loads both offsets with x87 for rasterization.
The adjacent setter at `0x004135F0` writes the same three fields in
the same order. Keeping the two offsets as floats in the shared
TextOverlay layout reproduces all 40 bytes. The standalone raw-word
control also matches. The game context identifies the fields, and
the original parameter declaration remains unknown.

Both setters have zero relocations. The constructor and every source
unit using the shared TextOverlay header cold-replay exactly.

    scripts/repo-python scripts/replay-exact-units.py --unit sprite-sequence-set-capacity-00410fc0 --unit command-list-initialize-defaults-00410f30 --unit text-overlay-set-raster-parameters-004135f0 --unit overlay-text-draw-box-00412eb0 --unit font-surface-configure-text-00413420 --unit font-surface-render-text-to-texture-00413460

### R288 — Remaining origin evidence

The remaining complete native bodies and their incoming calls were
checked against the current ledger. The two empty functions with no
recorded callers were also queried in the read-only Ghidra project.
The current direct-call scan is in
`.analysis/final-origin-review/residual-inbounds.log`.

| Candidates | Evidence gap |
| --- | --- |
| `0x0040D8C0`, `0x0040D8E0` | R316 reproduces all 10,483 linked bytes and three exception records with both lifetime forms in a single compile unit without `/Gy`. |
| `0x0040D900`, `0x0040D940` | R308 matches the complete sprite drawing interval with the precompiled standard overloads and ordinary wrappers. R303 rules out the x87 bodies in the older SDK shape archive. |
| `0x00411C10` | R314 reproduces the full 3,113-byte linked interval with implicit and explicit constructors by omitting `/Gy`. |
| `0x004138D0`, `0x00441FD0` | R313 reproduces both complete surrounding intervals with ordinary functions and template instantiations. Neither body has a direct caller or an absolute pointer literal. |
| `0x004251C0` | R314 reproduces the complete 1,189-byte Battle End and LoadingScene constructor interval and the 68-byte readonly interval with both base definitions by omitting `/Gy`. |
| `0x00438A60` | R310 preserves all 14 native caller edges with a deferred standard overload and a late ordinary wrapper. Both call the `labs` body identified by R294. |
| `0x00442040` | R303 matches the full 444-byte banner window with both the pinned `log10f` and an ordinary float wrapper when their definitions follow the two progress accessors. |
| `0x00449A60`, `0x00449A80` | R308 matches the complete collision interval with the precompiled header, two ordinary functions, and an ordinary function calling the header worker. |
| `0x00458650` | R315 matches the complete loader interval and all three vtables with implicit and explicit Actor definitions when `/Gy` is omitted. |
| `0x00458670` | The R306 linked resource-loader interval matches with both implicit and explicit rendering base constructors. |
| `0x00458770` | R308 matches the complete cleanup interval with implicit, late inline and separately defined list owner destructors. |

The pinned PE has an RSDS record for `東方萃夢想.pdb` with GUID
`9306058f-6d68-4650-b80b-1e0d05dd1e18` and age 3. Its COFF symbol
table is empty. The supplied archive listing contains the original
PE and no matching PDB, map or object file. A matching PDB or the
original build objects could identify contributions whose distinct
C++ forms produce identical code.

    scripts/repo-python .analysis/pending-origin-2026-11-24/inbounds.py
    scripts/repo-python scripts/ghidra.py query .analysis/final-origin-review/004138d0-xrefs.txt xrefs_to 30 0x004138D0
    scripts/repo-python scripts/ghidra.py query .analysis/final-origin-review/00441fd0-xrefs.txt xrefs_to 30 0x00441FD0
    scripts/repo-python .analysis/final-origin-review/empty-hooks/archive.py
    scripts/compile-probe.sh .analysis/final-origin-review/lifetime-alternatives.cpp build/probes/LifetimeFinal-0.obj /Od /Ob0 /Gy /GR- /GX- /Zi /I src /DEXPLICIT_MEMBERS=0
    scripts/compile-probe.sh .analysis/final-origin-review/lifetime-alternatives.cpp build/probes/LifetimeFinal-1.obj /Od /Ob0 /Gy /GR- /GX- /Zi /I src /DEXPLICIT_MEMBERS=1
    scripts/compile-probe.sh .analysis/final-origin-review/sprite-list-explicit.cpp build/probes/SpriteHistoryListExplicitCtor.obj /Od /Ob0 /Gy /GR- /GX- /GS /Zi /I src
    scripts/compile-probe.sh .analysis/final-origin-review/log10-controls.cpp build/probes/Log10OriginControls.obj /Od /Ob0 /Gy /GR- /GX- /Zi
    scripts/repo-python scripts/replay-exact-units.py --unit battle-round-banner-00441ea0
    scripts/repo-python .analysis/final-origin-review/check-residual-controls.py
    scripts/repo-python .analysis/frame-copy-origin/compare.py

### R289 — Link order and the CRT absolute-value candidate

The native window at `0x00641F00` contains the full 184-byte `memcmp`,
the 11-byte candidate at `0x00641FB8`, 13 alignment bytes, and the
complete 336-byte `log10.obj` code section. The pinned VC7.1 linker
places the CRT `labs.obj` body at the same relative offset when the
probe links against `libcmt.lib`. The scratch and native 544-byte
windows match their source objects with all 18 `log10` relocation
fields bound separately in each image.

Linking the same ordinary 11-byte function as a separate object before
the library, or in a separate archive on either side of it, moves it
outside the interval. Supplying the original `memcmp.obj` and
`log10.obj` as explicit inputs around the ordinary function restores
all 544 bytes and fields in the same relative layout. The result
holds in fresh links with and without `/DEBUG`, using the linker's
automatic alignment. The original input order is
unknown, so the interval alone cannot identify the 11-byte body as
`labs.obj`. R294 compares the larger request sequence.

In `.analysis/final-origin-review/crt-link-order/`, the two entry
objects use `/MT /Od /Ob0 /Oi- /Gy /GR- /GX- /Zl` and
`/DORDINARY=0` or `/DORDINARY=1`. The ordinary function uses
`/MT /O1 /Ob0 /Gy /GR- /GX- /Zl`. The `crt-*.obj` files are the
unchanged members `memcmp.obj`, `labs.obj`, `log10.obj` and
`abs.obj` from the pinned `libcmt.lib`.

    bash .analysis/final-origin-review/crt-link-order/link.sh
    scripts/repo-python .analysis/final-origin-review/crt-link-order/compare.py
    bash .analysis/final-origin-review/crt-link-order/link.sh debug
    scripts/repo-python .analysis/final-origin-review/crt-link-order/compare.py release-debug

### R290 — Event service pulse and startup registration

`0x00423B20` constructs a local event service with the argument 16
and destroys it on return. The ordinary scope and the generated
initializer both reproduce its complete 26 bytes and both calls.
The generated object also has a four-byte `.CRT$XCU` contribution
that relocates to the initializer. The linker carries that pointer
into the C++ initialization table with both `/OPT:REF` and
`/OPT:NOREF`. The ordinary control with `/OPT:NOREF` retains the
same body without a registration.

The original table from `0x0066C000` through `0x0066C034` has 14
slots including its boundaries. None points to `0x00423B20`, and
the whole PE contains no absolute pointer to that address. A scan
of mapped executable bytes finds no raw rel32 reference into the
26-byte extent. The registration distinguishes the R114 alternatives
and supports the ordinary game function. Its original name remains
unknown.

The shared game source uses the same local event-service type as
`0x004239C0`. All eight units from that source cold-replay exactly.
The control source uses `/MT /Od /Ob0 /Gy /GR- /GX /GS /Zl` and
`/DGENERATE_STARTUP=0` or `/DGENERATE_STARTUP=1`, producing
`ordinary.obj` and `startup.obj` in the control directory.

    bash .analysis/final-origin-review/event-pulse-registration/link.sh
    scripts/repo-python .analysis/final-origin-review/event-pulse-registration/compare.py
    scripts/repo-python .analysis/final-origin-review/crt-link-order/scan-unowned-entries.py
    scripts/repo-python scripts/replay-exact-units.py --unit event-service-pulse-00423b20 --unit background-base-virtual-destroy-00449d40 --unit camera-motion-set-override-00412cc0 --unit sprite-sequence-remove-front-if-present-004110c0 --unit event-queue-local-acquire-release-004239c0 --unit frame-capture-install-present-callback-00417120 --unit frame-capture-enable-direct-draw-00417140 --unit battle-end-scene-destroy-00424f40

### R291 — Sprite quad payload layout

The native background transform copies 33 dwords at `0x00449D28`.
The sprite history append copies the same width at `0x00411035`, and
its next argument starts at `[ebp+0x98]`, 132 bytes past the quad
argument. The default constructor clears all 132 bytes. The textured
and projected draw entries at `0x004029F0` and `0x00402D50` read
the coordinates of the first four vertices.

Two scratch layouts preserve the observed size and the constructor
receiver at `+0x40`. One has an ordinary empty constructor for a
17-dword member. The other uses the pinned D3DX8 `D3DXMATRIX` and
a separate dword at `+0x80`. The same sources build with each
unit's canonical VC7.1 profile. Each layout reproduces the complete
14-byte leaf, its three caller constructors, the 1,132-byte sprite
draw and both copies. All 2,069 bytes and 46 relocation operands
compare per layout. The three constructor calls bind to the
corresponding COFF symbol at the same native entry. R293 uses
the original linker layout to distinguish the two types.

All eight `D3DXMATRIX` default constructor definitions in the pinned
D3DX8 archive contain the same three bytes as several other default
constructors. The archive has no code relocation naming the matrix
constructor, so its optimized copies supply no typed call to this leaf.

    scripts/repo-python .analysis/final-origin-review/quad-payload/replay.py
    scripts/repo-python .analysis/final-origin-review/quad-payload/archive.py

### R292 — VC7.1 float worker selection

The original `CD3DXSprite::GetDevice` and `CD3DXSprite::End` match
all 38 and 43 bytes of their defining sections in pinned
`cd3dxsprite.obj`. The nine bytes between them contain three
`mov eax, ecx; ret` bodies. The intervening source sections supply
these three-byte constructors as inline COMDATs. A scan of the
native PE finds no direct transfer or absolute pointer to the
three entries.

Pinned VC7.1 links with ordinary float workers and `/OPT:NOREF`
retain the unreferenced sprite constructors and four seven-byte
SDK COMDATs, one each for `_cosf`, `_sinf`, `_fabsf` and `_sqrtf`.
Using the standard header workers replaces those four SDK bodies
with the 28-byte VC7.1 header definitions. The ordinary and header
workers match the same original bytes and their actual CRT call
operands. With `/OPT:REF`, both forms lose every intervening
constructor, and the ordinary form also loses the four SDK
workers. The original retains the constructor contributions and
contains none of the four seven-byte bodies. This combination
supports selection of the header workers under the observed
retention behavior. Only the four inner workers receive a
VC71CRT exclusion.

With the probe's archive input order, the two retained sprite
constructors occupy six bytes and the ordinary control adds the
seven-byte `_cosf` at the same site. Omitting the explicit retention
flag under `/DEBUG` gives the same selection as `/OPT:NOREF`.

| Native entry | Header worker | CRT callee |
| --- | --- | --- |
| `0x0040D920` | `cosf` | `0x00641754` |
| `0x0040D960` | `sinf` | `0x00641804` |
| `0x00412DB0` | `fabsf` | `0x006418CD` |
| `0x00428D40` | `sqrtf` | `0x00641E54` |

    bash .analysis/final-origin-review/sdk-math-selection/link.sh
    scripts/repo-python .analysis/final-origin-review/sdk-math-selection/compare.py

### R293 — Sprite matrix constructor selection

The R291 constructor bodies and their three callers match for both
payload layouts. The archived `D3DXMATRIX` symbol supplies a
separate observation. In the native image, `d3dx8tex.obj` code
precedes `cd3dxsprite.obj` and `d3dxmath.obj`. The two vector default
constructors retained in the texture code remove duplicate vector
sections from the sprite interval. The earlier 14-byte
`D3DXVECTOR4` constructor is independently identified by R282.

Links starting from the public texture and sprite APIs retain the
same packed SDK code. With the matrix member, the earlier
14-byte definition supersedes the three-byte archived matrix
constructor. The 90-byte sprite interval contains the
two sprite vertex constructors and the quaternion constructor.
The aligned matrix and plane constructors occupy the two
three-byte intervals in the math code. With the ordinary member,
the archive contributes an extra three-byte matrix constructor
at the start of the sprite interval, just after `GetDevice`.

The four complete windows start at `0x006053D2`, `0x00609058`,
`0x0061B158` and `0x0061B263`. The matrix control reproduces all
506 bytes with 14 relocation operands bound to the actual symbols
in each image. The ordinary control reproduces three windows and
adds three bytes to the fourth. The result holds under explicit
`/OPT:NOREF` and the retention default under `/DEBUG`.
This identifies `0x0040D9F0` as the D3DX8 `D3DXMATRIX` default
constructor. The role of the final dword at `+0x80` remains unknown.

    bash .analysis/final-origin-review/quad-comdat-selection/link.sh
    scripts/repo-python .analysis/final-origin-review/quad-comdat-selection/compare.py

### R294 — CRT absolute-value archive request order

The earliest native direct transfers to `abs`, `strncmp`, `sqrt`,
`memcmp`, the 11-byte absolute-value candidate, `log10`, `ceil`,
and `atan2` occur in that order. The scene constructor at
`0x004251C0` stores the vtable whose three entries request
`_purecall` between the first `strncmp` and `sqrt` requests.
The `purevirt.obj` contribution includes the adjacent 16-byte
handler setter and its two real data fields. The earlier R263
`abs.obj` contribution still compares separately as all 39 bytes.

The pinned linker extracts the unmodified `libcmt.lib` members in
this order when a C++ object issues those same requests, including
the pure virtual requests through an actual vtable. The complete
`0x00641DE0` through `0x00642254` interval, ending immediately
after the two `atan2` entries, matches all 1,140 bytes and 49
relocation operands. Code and data symbols bind separately in the
native and probe images. Swapping only the two request positions
moves `log10.obj` ahead of `labs.obj`.

With the ordinary byte-equal function in a separate object or a
regular archive on either side of `libcmt.lib`, the linker places
the leaf outside the interval. The span from `memcmp` to `log10`
loses 16 bytes. R289's explicit-object input can still reproduce
the smaller interval. The larger native request order supports
the inferred `labs.obj` association at `0x00641FB8`. The caller
at `0x00438A60` has both R163 declarations and remains unresolved.

    bash .analysis/final-origin-review/crt-request-order/link.sh
    scripts/repo-python .analysis/final-origin-review/crt-request-order/compare.py

### R295 — Texture entry construction and unwind

The three texture allocators at `0x0040B000`, `0x0040B110` and
`0x0040B1D0` construct and destroy one 44-byte entry. The bitmap
constructor and destructor receive that entry at offset zero. The
explicit inline and implicit outer declarations each reproduce
the three complete allocator bodies, all three handlers and their
unwind maps. Both also reproduce the 22-byte constructor and
19-byte destructor. The comparison covers 776 bytes and 44
relocation operands per layout.

Placement `new T` and `new T()` each emit 62 bytes and the same
two relocation operands for both declarations on VC7.1. The
scratch layout separates the last four bytes to observe whether
the compiler zeroes a scalar outside the modeled bitmap subobject.
Neither placement form emits a distinct zeroing operation.

Both declarations use selection ANY for the two lifetime COMDATs.
The explicit inline form emits function auxiliary records under
the caller's `/Zi` profile. The implicit form has no function
auxiliary record. The PE has no COFF symbol table to retain this
distinction.

    scripts/repo-python .analysis/final-origin-review/texture-lifetime/replay.py

### R296 — Script sequence copy emission order

The full linked window from `0x004229B0` through `0x00422B40`
matches with the implicit sequence copy. It
contains the two typed `_Destroy` dispatchers, the 28-byte sequence
copy, the two scalar-deleting destructors and the 241-byte deque
copy, in that order. The pinned linker selects the earlier
`_Allocate<char>` definition in the probe. The original allocator
at `0x00405B00` calls the same 17-byte helper at `0x00405F60`.

Explicit inline definitions in the class and at the end of the
same source each cause VC7.1 to emit the sequence and deque copies
before both `_Destroy` dispatchers. The out-of-line definition in
that source moves them earlier again. At the native sequence
copy's relative slot, those three links place the record deleting
destructor. With the explicit copy in its own input object, linking
that object first moves the copy ahead of both dispatchers. Linking
it last puts the copy after both deleting destructors.

All six links reproduce the individual code bodies, the 108-byte
`_Construct` caller and both full exception frames. The
comparison binds all 36 relocation operands in the PE and in
each link. Only the implicit form reproduces the ordered
401-byte window. This supports compiler origin for `0x004229D0`.

    bash .analysis/final-origin-review/script-copy-order/build.sh
    bash .analysis/final-origin-review/script-copy-order/link.sh
    bash .analysis/final-origin-review/script-copy-order/split.sh
    scripts/repo-python .analysis/final-origin-review/script-copy-order/compare.py

### R297 — Fighter frame copy emission order

The cold VC7.1 probe uses the 116-byte frame with its destructible
prefix, rectangle vectors and the explicit cleanup already observed
at `0x004588E0`. The native `vector<Frame>::assign` and default
constructor compare completely. The default constructor binds the
two allocator helpers at `0x004591B0` and `0x004591D0`. The 195-byte
`_Assign_n` calls the frame copy and reproduces its full handler and
unwind map.

The implicit copy and all four explicit links reproduce the
individual code and exception sections with 53 bound relocation
operands. The implicit link reproduces the complete 688-byte
native window from `0x004591B0` through `0x0045945F`, including the
allocator helpers, the 417-byte frame copy, and the 208-byte
rectangle-vector copy. In-class and out-of-line explicit copies in
the same object emit both copies before the two allocator helpers.
Putting the explicit definition in a separate object moves both
copies before or after the vector object's contributions according
to the input order. The whole native window distinguishes
`0x004591E0` as an implicit compiler-generated copy.

    bash .analysis/final-origin-review/frame-copy-order/build.sh
    bash .analysis/final-origin-review/frame-copy-order/link.sh
    scripts/repo-python .analysis/final-origin-review/frame-copy-order/compare.py

### R298 — Sprite history constructor emission order

The non-inline constructor definition moves ahead of
`AppendElement` in the R280 translation unit. An explicit
constructor in the class and an inline definition outside the class
both follow `AppendElement` at the same position as the implicit
constructor. The latter three builds produce the same 89 ordered
code sections, bytes and relocation records. The comparison checks
local labels through their defining offsets.

All four builds reproduce the complete append and element
constructor functions and the 28 typed list helpers. The native
list context therefore allows either inline form or the implicit
form. In this case the first construction is in a game function
that creates a local entry. The two template-led copy cases in
R296 and R297 placed explicit definitions at different positions.

    bash .analysis/final-origin-review/sprite-constructor-order/replay.sh
    scripts/repo-python .analysis/final-origin-review/sprite-constructor-order/order.py

### R299 — Fighter cleanup and paired base construction

The typed fighter cleanup at `0x00456910` reproduces all 588 code
bytes, 148 bytes of exception and unwind data, and the four
44-byte scalar-deleting destructors. The list owner destructor at
`0x00458770` reproduces its full 22 bytes and the library destructor
call. These checks bind 45 relocation operands in every build.

An explicit destructor defined in the class moves ahead of the
next deleting destructor at `0x00458740`. An explicit inline
definition outside the class and an out-of-line definition after
the fighter cleanup body both follow that deleting destructor.
The implicit declaration has the same order as those two explicit
forms.

The fighter initialization probe at `0x004567B0` matches all 345
bytes. Its two base constructors match the 31-byte
`0x00458650` and 23-byte `0x00458670`. The five slots at
`0x00659038` and `0x0065904C` contain two pure calls and the same
three render functions. The probe emits two separate vtable
sections and matches all 31 operands across the constructor and
vtable sections. The implicit, in-class, inline and derived-first
out-of-line forms all emit the derived constructor and its table
first, as in the PE. A base-first out-of-line definition reverses
both orders. The retained explicit forms leave the three
declarations unresolved.

    bash .analysis/final-origin-review/history-dtor-order/build.sh
    scripts/repo-python .analysis/final-origin-review/history-dtor-order/compare.py
    bash .analysis/final-origin-review/actor-ctor-order/build.sh
    scripts/repo-python .analysis/final-origin-review/actor-ctor-order/compare.py

### R300 — Publisher patch reproduces the pinned executable

The Japanese 1.11 patch passes the publisher's MD5 check
(`bcde4f88a50e720c0f14f28441965106`). Its LHa payload passes all three
archive checks. The streamed `th075.exe` has the same SHA-256 as the
repository target, and `th075b.dat` has the same SHA-256 as the R268
archive member. The third file is `readme.txt`. The original RSDS
record is the only target GUID occurrence in the three decoded streams
and the installer stub. The DAT directory contains 37 game-resource
entries and no separately named symbol, map or object file.
[Publisher release and digest](https://tasofro.net/arc/index.html#tf012-p)

    7z l -slt /path/to/th075_111s.exe
    7z t /path/to/th075_111s.exe
    7z x -so /path/to/th075_111s.exe th075.exe | sha256sum
    scripts/repo-python .analysis/final-origin-review/official-patch-symbols/audit.py /path/to/th075_111s.exe

### R301 — Uncalled empty functions survive debug link retention

An out-of-line destructor and a template member each emit all 11
bytes at `0x004138D0`. An ordinary function, a static member and
the pinned STL `_Destroy<unsigned long>` each emit all five bytes
at `0x00441FD0`. The `_Destroy` instance takes a pointer, so the
five-byte body also leaves the argument list ambiguous. None of the
five complete code sections has relocations.

The VC7.1 linker retains all five at distinct addresses with `/DEBUG`
and `/OPT:NOICF`, both at the default retention setting and with
`/OPT:NOREF`. `/OPT:REF` removes them all. R292 observes unreferenced
COMDAT retention in the same target image. The absence of callers
therefore leaves both ordinary and template origins possible.

    bash .analysis/final-origin-review/empty-hooks/build.sh
    scripts/repo-python .analysis/final-origin-review/empty-hooks/compare.py

### R302 — Scene and stage constructor order through the first derived class

The first scene caller is the Battle End constructor at `0x00424E00`.
The probe includes every complete code body from that entry through the
next derived constructor at `0x004251F0`, all three vtables and both
complete exception records. Five base declaration forms reproduce
1,289 bytes and bind 113 relocation operands to the native destinations.
The original scene base table has three `_purecall` slots. A pure
virtual destructor reproduces that table while the exception paths
call the separate destructor body at `0x00431F40`.

The stage probe includes every complete code body from the first BG00a
constructor at `0x00449AA0` through the base constructor at `0x00449DE0`,
both six-slot vtables and the complete BG00a exception record. The five
declaration forms reproduce 927 bytes and bind 59 relocation operands.
The pinned linker resolves the weak vector-deleting names in the
vtables to the corresponding scalar-deleting functions.

The scratch links use unresolved externals solely to read section order
from the maps. Byte comparisons bind the object relocations separately.
In both windows the implicit constructor moves ahead of the next native
derived method. A late explicit definition puts it back at the native
relative offset (`+0x3C0` in Scene and `+0x340` in Stage). The first code
order mismatch in those links is the slot immediately after the first
derived constructor. Each link puts a deleting destructor there. The
native windows start that slot with the Battle End destructor and the
BG00a no-op virtual, respectively. `/Z7` preserves these offsets.
R314 records the effect of omitting `/Gy`; the earlier `/Gy-` trial
raised warning D4002 and left function packaging enabled.

    bash .analysis/final-origin-review/scene-ctor-order/build.sh
    scripts/repo-python .analysis/final-origin-review/scene-ctor-order/compare.py
    bash .analysis/final-origin-review/stage-ctor-order/build.sh
    bash .analysis/final-origin-review/stage-ctor-order/build.sh packed
    bash .analysis/final-origin-review/stage-ctor-order/build.sh embedded
    scripts/repo-python .analysis/final-origin-review/stage-ctor-order/compare.py

### R303 — Standard log10f can occupy the native banner slot

The pinned header and an ordinary wrapper both reproduce the full
444-byte interval `0x00441EA0..0x0044205B`. The interval contains the
303-byte banner, the five-byte uncalled body, two 44-byte progress
accessors, and the 28-byte worker. Comparisons include the inter-function
alignment and all eight relocations. The linker resolves the internal
call to the worker. The compare binds the external operands to the
known PE destinations after checking their physical COFF fields.

Including `<math.h>` before the banner emits `_log10f` immediately
after it. Moving that include below the banner while retaining the
existing rendering header still makes the definition visible before
the caller through a transitive include. With a narrow view of the
same 132-byte render packet, the unchanged banner call can use a
forward declaration and see the real header definition only after
both progress accessors. That link and the late ordinary definitions
place the worker at the original `+0x1A0`. Both a plain and an inline
forward declaration of `_log10f` preserve the full native interval.

A direct transfer scan of the current 4,351 function extents found
no second wrapper body for any of the five checked `cos`, `sin`,
`labs`, `log10` and `ceil` chains. The older `d3dx.lib` and
`d3dxd.lib` each define the decorated C++ cosine and sine overloads
in `shapes.obj`. Their full seven- and ten-byte bodies execute
`fcos` or `fsin` directly and have no relocations. The native outer
overloads are 17 bytes and call the independently attributed header
workers. The archive definitions leave the two outer declarations
unresolved.

    scripts/repo-python .analysis/final-origin-review/math-wrapper-order/scan.py
    bash .analysis/final-origin-review/math-wrapper-order/build-banner.sh
    scripts/repo-python .analysis/final-origin-review/math-wrapper-order/compare-banner.py

### R304 — Texture entry lifetime definitions follow the drawing methods

Explicit definitions of the texture entry constructor and destructor
reproduce the complete 10,483-byte interval `0x0040B000..0x0040D8F2`.
The linked window covers all 35 bodies, inter-function alignment and
308 code relocation operands. The three allocators' complete exception
handlers and unwind maps compare through their object sections. The
three draw methods retain the native call to the separate `D3DXVECTOR4` constructor at `0x0040D980`.
Their scratch header exposes that constructor's declaration so the
link window only contains the functions owned by the interval. The
comparison checks the physical object fields and binds the external
operands to the original PE destinations.

The implicit variant emits both leaves after the first allocator.
Its first mismatch is `0x0040B110`, where the second allocator moves
from `+0x110` to `+0x150`. Public inheritance and template specialization
keep that same early placement. VC7.1 also emits the implicit template
members in the caller under `extern template`. With the genuine
`std::vector` assignment and its complete exception context, both
versions match 1,165 body and EH bytes and 65 fields, while the implicit
variant still moves the allocation block. `std::pair` controls store
zero at `+0x28` and produce 32- and 38-byte constructors.

Precompiling the header with `/Yc` and consuming it with `/Yu` defers
the explicit inline definitions past the drawing methods. The implicit
members remain early. Folding two independently named 44-byte types
moves the selected constructor past the third allocator and leaves the
destructor before the second. The independent D3DX8 link shows that
this `/OPT:ICF` setting collapses seven separate native SDK entries and
shrinks the original 90-byte sprite interval to 81 bytes.

The linked order in these builds initially supported authored
origin for `0x0040D8C0` and `0x0040D8E0`. R316 restores both to
review using a complete implicit compile without `/Gy`. The
entry occupies 44 bytes and calls the native bitmap lifetime at
offset zero. The bitmap's extent inside the entry remains open.

    scripts/repo-python .analysis/final-origin-review/texture-lifetime/replay.py
    bash .analysis/final-origin-review/texture-emission-order/build.sh
    bash .analysis/final-origin-review/texture-emission-order/build.sh implicit-pch header-inline-pch implicit-vector inline-last-vector implicit-inherited implicit-template implicit-template-caller implicit-template-definition pair-scalar pair-tag
    scripts/repo-python .analysis/final-origin-review/texture-emission-order/compare.py
    scripts/repo-python .analysis/final-origin-review/texture-emission-order/build-spine.py --cold
    scripts/repo-python .analysis/final-origin-review/texture-emission-order/compare-spine.py
    bash .analysis/final-origin-review/quad-comdat-selection/link.sh
    bash .analysis/final-origin-review/texture-emission-order/link-folding.sh
    bash .analysis/final-origin-review/texture-emission-order/link-sdk-icf.sh
    scripts/repo-python .analysis/final-origin-review/texture-emission-order/check-alternatives.py

### R305 — Stage base constructor follows the deleting destructors

The VC7.1 split build reproduces the full 877-byte code interval
`0x00449AA0..0x00449E0C`, including BG00a's virtuals and both deleting
destructors. It also reproduces the 76-byte readonly interval
`0x00658434..0x0065847F` with the two adjacent six-slot vtables,
alignment and three double constants. The comparison binds 59
operands across the complete code bodies, tables, BG00a handler
and unwind map. Named readonly definitions in the second object
keep the draw constants after the vtables while preserving their
values and every reference in the original draw body.

With the derived destructor definition in a `/Yc` header, `/Yu`
defers the generated wrapper until after the authored virtuals.
The base destructor and its deleting wrapper then precede the
derived wrapper and destructor. Defining the base constructor in
the second object places it at the original `+0x340`. Removing the
explicit declaration and definition from otherwise identical inputs
keeps the readonly interval exact and inserts the implicit constructor
at `+0xA0`, the original slot of the first BG00a virtual. The full
code and data comparison supports authored origin for `0x00449DE0`.
The original source partition remains open.

The same precompiled destructor control for Battle End defers its
deleting wrapper and ordinary destructor together. The native
ordinary destructor immediately follows the derived constructor.
An inline declaration alone keeps the deleting wrapper early. The
scene constructor at `0x004251C0` remains unresolved.

    scripts/repo-python .analysis/final-origin-review/stage-ctor-order/make.py
    scripts/repo-python .analysis/final-origin-review/scene-ctor-order/make.py
    bash .analysis/final-origin-review/ctor-pch-order/build.sh stage-split-constants stage-implicit-dtor-constants scene-late scene-header-dtor scene-inline-declaration
    scripts/repo-python .analysis/final-origin-review/ctor-pch-order/compare.py stage-split-constants stage-implicit-dtor-constants scene-late scene-header-dtor scene-inline-declaration

### R306 — Actor constructor follows the stage resource loader

VC7.1 reproduces the complete 439-byte interval `0x004584D0..0x00458686`
with an out-of-line Actor constructor and either an implicit or an
out-of-line rendering base constructor. The loader calls the scalar
deleting destructor supplied by the earlier LoadingScene object in
both the native executable and the scratch link. With that binding,
the two constructors land at `+0x180` and `+0x1A0` from the loader.

The separate comparison of the full Fighter constructor, both base
constructors, both five-slot vtables, the exception handler and the
unwind map matches 606 bytes with 46 relocation fields. The already
exact CharacterObject constructor also calls the Actor constructor.
Making Actor implicit emits its constructor at `-0x20` from the
loader. The same displacement occurs when the Fighter constructor
and loader share a compile unit with a precompiled header. The
linked order initially supported authored origin for `0x00458650`.
Both rendering base definitions survive the full comparison.
R315 supersedes the Actor decision with a byte-equal implicit
control that omits `/Gy` and includes the complete Fighter vtable.

The Battle End control retains the early deleting destructor with
`/Z7` and with linked `/GL /LTCG` code. The `/Z7` bodies and
exception sections account for 1,289 bytes and 113 relocation
fields. `/ZI` changes seven or more function bodies. An inferred
ordinary destructor is 19 bytes and omits the original vtable
store. The native 28-byte body still has no control that places
the ordinary destructor early and the deleting destructor late.

    bash .analysis/final-origin-review/actor-base-split/build.sh
    scripts/repo-python .analysis/final-origin-review/actor-base-split/compare.py
    bash .analysis/final-origin-review/actor-base-split/link-stage-tail.sh
    bash .analysis/final-origin-review/actor-base-split/build-pch-control.sh
    scripts/repo-python .analysis/final-origin-review/actor-base-split/compare-tail.py
    bash .analysis/final-origin-review/scene-emission-profiles/build.sh
    scripts/repo-python .analysis/final-origin-review/scene-emission-profiles/compare.py

### R307 — Sprite history element follows the drawing and transform methods

An explicit constructor at `0x00411C10` reproduces the complete
3,113-byte interval `0x00411000..0x00411C28`. The comparison covers
eleven bodies, their alignment, and all 57 COFF operands. The
out-of-line definition also matches with the pinned
`std::list<SpriteHistoryElementF325>`. That build independently
matches the complete `push_back`, `size` and `pop_front` bodies.
The SDK vector constructors preceding the interval are external
in the probe. Their call operands retain the native bindings.

In the R298 append-only context an implicit constructor followed
`AppendElement`, as did both explicit inline forms. Adding the
intervening functions leaves the implicit constructor at `+0xC0`,
where the native interval starts `RemoveFrontIfPresent`. The
implicit build shifts that method to `+0xE0` with the typed list
and with precompiled declarations under `/Gy`. A late explicit inline
definition also matches the full interval. Moving the inline
definition into the precompiled header with the real list defers
it past the native slot. The explicit matches and consistent
implicit displacement originally supported authored origin for the
constructor. R314 supersedes that decision with a corrected
compiler flag control.

    bash .analysis/final-origin-review/sprite-constructor-spine/build.sh explicit implicit inline pch-implicit pch-inline typed-implicit typed-explicit no-gy-implicit no-gy-typed-implicit no-gy-explicit pch-typed-implicit pch-typed-inline
    scripts/repo-python .analysis/final-origin-review/sprite-constructor-spine/compare.py explicit implicit inline pch-implicit pch-inline typed-implicit typed-explicit no-gy-implicit no-gy-typed-implicit no-gy-explicit pch-typed-implicit pch-typed-inline

### R308 — Complete math and cleanup intervals retain multiple origins

VC7.1 links the standard `cos(float)` and `sin(float)` overloads at
their native offsets when their original header is precompiled.
Late ordinary wrappers around `cosf` and `sinf` also match the
whole 3,836-byte interval `0x0040CA80..0x0040D97B`. It contains
all three original calling draw bodies, the remaining drawing
methods, both texture entry lifetimes and all four math bodies.
The comparison verifies 66 relocation operands and the referenced
compiler floating-point constants. Without the precompiled header,
the overloads appear after the first draw method and move
`0x0040CEF0` forward by 128 bytes.

The precompiled standard `ceil(float)` and `ceilf` reproduce the
complete 2,236-byte interval `0x004491E0..0x00449A9B`. So do two
late ordinary functions and an ordinary function that calls the
header worker. The comparison covers all three collision methods,
both math functions, the two constants and 53 relocation operands.
An early header include puts both math bodies before `TestOverlap`.

The fighter cleanup produces the complete 481-byte interval
`0x00458690..0x00458870` with an implicit list owner destructor,
a late inline destructor, or an out-of-line destructor in the next
object. The genuine auxiliary record destructor fills its slot
between the first two deleting wrappers. The earlier LoadingScene
object supplies the texture deleting wrapper. The comparison also
checks the full Fighter destructor, its exception records, the
exception records of both neighboring lifetimes and the native
`std::list` destructor body. Defining the list owner destructor
inside the class moves it ahead of `0x00458740`. The other three
forms preserve the original offsets and all bytes.

    bash .analysis/final-origin-review/ceil-link-order/build.sh header-early header-pch ordinary-late header-worker header-deferred
    scripts/repo-python .analysis/final-origin-review/ceil-link-order/compare.py header-early header-pch ordinary-late header-worker header-deferred
    bash .analysis/final-origin-review/trig-link-order/build.sh header-early header-pch ordinary-late header-deferred
    scripts/repo-python .analysis/final-origin-review/trig-link-order/compare.py header-early header-pch ordinary-late header-deferred
    bash .analysis/final-origin-review/history-dtor-spine/build.sh implicit inline out-of-line in-class
    scripts/repo-python .analysis/final-origin-review/history-dtor-spine/compare.py implicit inline out-of-line in-class

### R309 — Explicit scene template instantiation keeps the implicit constructor early

The Scene base template emits its implicit constructor at `+0x170`
from the Battle End constructor. It stays there when the caller
declares `extern template` and the explicit instantiation is in a
separate object. The two builds match all 1,289 body, vtable and
exception bytes with 113 relocation fields.

An in-class Battle End destructor also preserves all those bytes.
Its deleting wrapper still occupies `+0x140`, the original ordinary
destructor slot. The implicit and explicit base constructors land
at `+0x190` and the native `+0x3C0`, respectively. With `/Ob1` the
explicit inline base constructor disappears as a standalone body
and both derived constructor extents change. The unresolved
comparison is the native order of the two Battle End destructors.

    bash .analysis/final-origin-review/scene-ctor-variants/build.sh inclass-dtor inclass-dtor-implicit inline-ob1 template-implicit template-extern
    scripts/repo-python .analysis/final-origin-review/scene-ctor-variants/compare.py inclass-dtor inclass-dtor-implicit inline-ob1 template-implicit template-extern

### R310 — Absolute-value declarations share all fourteen caller edges

Twelve complete character selection methods reproduce the 20,458-byte
linked interval `0x00433A40..0x00438A29` when the standard `abs(long)`
definition is visible after the methods. An ordinary out-of-line
wrapper around the same `labs` reproduces that interval and the whole
17-byte wrapper. The two comparisons bind 582 real COFF fields,
including the wrapper's call to the R294 CRT body.

The standard overload and ordinary wrapper also preserve the separate
`0x004483F0` caller, including its six-entry jump table and all 28
relocation fields. The scratch linker resolves all fourteen calls from
both objects to the same implementation with folding disabled. In the
native image, a scalar deleting destructor lies between the selection
methods and the wrapper. Its 48-byte aligned slot accounts for the
displacement of the wrapper in the scratch link.

An early include emits the overload before `ProcessSubselection`.
With the original header precompiled it instead appears just before
`UpdatePlayerChoice`. Both controls retain the individual bodies.
The declaration-only header control delays just the pinned overload
definition and recovers the complete selection interval.

    bash .analysis/final-origin-review/abs-caller-order/build.sh header-early header-pch ordinary-late header-deferred
    scripts/repo-python .analysis/final-origin-review/abs-caller-order/compare.py header-early header-pch ordinary-late header-deferred

### R311 — Scene constructor suffix matches across object boundaries

Building LoadingScene in a separate object with its two actual
archive strings reproduces the complete 68-byte readonly interval
`0x00657B7C..0x00657BBF`. It includes all three vtables, both strings,
and their alignment. The complete constructors and both unwind
records still match. Both the implicit and explicit base declarations
preserve this data order.

Two explicit definitions, one in the Battle End object and one
in a separate object, reproduce all 229 bytes from the base
constructor through the LoadingScene constructor. The implicit
form emits the base constructor in the earlier Battle End caller
and breaks that interval. The explicit builds still produce the
Battle End deleting wrapper at `+0x140` instead of `+0x390`.

Explicit member specializations on the derived class place the
ordinary destructor at its native `+0x140`. This reproduces the
complete 348-byte prefix, the 556-byte run of methods at a shifted
address, and the original readonly interval and constructor suffix.
The first full-interval difference is now `+0x160`, where the
deleting wrapper occupies the native `Update` slot. An external
class instantiation and precompiled declarations preserve that
order. Precompiling the ordinary destructor definition moves both
destructors after the authored methods. A member instantiation
moves the ordinary destructor late while leaving the wrapper early.
Neither arrangement recovers the full native order.

    bash .analysis/final-origin-review/scene-data-order/build.sh implicit defined-late separate separate-dtor-pch
    scripts/repo-python .analysis/final-origin-review/scene-data-order/compare.py implicit defined-late separate separate-dtor-pch
    bash .analysis/final-origin-review/scene-derived-template/build.sh specialized extern-deferred specialized-implicit specialized-decl-pch specialized-dtor-pch member-dtor
    scripts/repo-python .analysis/final-origin-review/scene-derived-template/compare.py specialized extern-deferred specialized-implicit specialized-decl-pch specialized-dtor-pch member-dtor

### R312 — The constructor object supplies the Battle End deleting wrapper

The isolated Battle End constructor object emits the complete
44-byte deleting wrapper and both call relocations even when the
ordinary destructor is defined later. A separate destructor object
emits another byte-equal wrapper with the same pick-any COMDAT name.
The pinned linker chooses the constructor object's definition at
`+0x140`. Reversing the two input objects chooses the destructor
object's definition and moves both destructors before the constructor.

Sharing the inline ordinary destructor in a precompiled header
still puts both bodies in the constructor object. The positive
comparisons include both complete derived constructors, the virtual
methods, all three vtables and both unwind records. The 68-byte
readonly span matches in all the splits. The implicit base
constructor in the precompiled split appears at `+0x140` and breaks
the 229-byte constructor suffix.

    bash .analysis/final-origin-review/scene-wrapper-owner/build.sh split-ctor split-dtor split-pch split-pch-implicit
    bash .analysis/final-origin-review/scene-wrapper-owner/relink.sh
    scripts/repo-python .analysis/final-origin-review/scene-wrapper-owner/compare.py split-ctor split-dtor split-pch split-pch-implicit split-dtor-reversed

### R313 — Uncalled functions retain byte-equal linked alternatives

The ordinary destructor and the template member at `0x004138D0`
both reproduce the full 711-byte replay interval
`0x00413790..0x00413A56` with 28 relocation fields. It includes
`BeginCapture`, the four-queue clear, the uncalled body and
`FinalizeFile`. The two uncalled functions occupy the same
aligned slot under debug retention.

The complete 444-byte banner interval `0x00441EA0..0x0044205B`
matches with an ordinary empty function and with the pinned
`std::_Destroy<unsigned long>` instantiation. Both use the same
banner, accessors, log worker and eight relocation fields. With
the instantiation in the same object as those bodies, VC7.1 emits
it at `+0x1B0` instead of `+0x130`. A separate instantiation
object in the input sequence reproduces the native order.

An updated local scan found 3,279 readable PDB identities that differ
from the native RSDS record. The remaining three named files
have program database 2.0 headers from the older VC4 runtime
installation and do not contain the target GUID in either byte order.

    bash .analysis/final-origin-review/empty-hook-windows/build.sh
    scripts/repo-python .analysis/final-origin-review/empty-hook-windows/compare.py
    scripts/repo-python scripts/audit-local-pdb-identities.py --root /home/pentester/coding/codex_ida --output .analysis/final-origin-review/current-pdb-identities.json

### R314 — Omitting function packaging restores the native Scene order

VC7.1 build 3077 warns about `/G-` when passed `/Gy-`. The old
probe passed that spelling after `/Gy`, leaving the original flag
in effect. Omitting `/Gy` places the ordinary methods in a shared
`.text` section. Generated deleting wrappers retain their own
COMDATs, which follow that section in the link.

For LoadingScene, this restores both deleting wrappers after
`Draw`. All 668 linked code bytes and the full 44-byte string and
vtable interval match. The two complete exception records also
match. Applying the same flag omission to the preceding Battle End
object gives the complete 1,189-byte interval
`0x00424E00..0x004252A4`, including the original deleting wrapper,
and all 68 readonly bytes. Both an implicit base constructor and
an explicit definition in a subsequent object reproduce the
entire comparison, including both exception records.

The corrected SpriteHistory control places the implicit
constructor at its native `+0xC10` and matches all 3,113 linked
bytes and 57 code relocations. The real typed list build retains
that match and the three compared list helpers. The out-of-line
constructor still matches. This reopens the origin of
`0x00411C10`. The R307 code and ownership record is in commit
`c1680891`.

With the flag omitted, the R305 precompiled stage builds still
distinguish the stage base constructor. The explicit form gives
all 877 linked code bytes, the 76-byte readonly interval and
the complete exception record with 59 relocation fields. The
implicit constructor moves to `+0x2C0`, the native base deleting
wrapper slot, instead of its target `+0x340`.

    bash .analysis/final-origin-review/loading-wrapper-order/build.sh ordinary packed
    scripts/repo-python .analysis/final-origin-review/loading-wrapper-order/compare.py ordinary packed
    bash .analysis/final-origin-review/scene-no-gy/build.sh separate implicit
    scripts/repo-python .analysis/final-origin-review/scene-no-gy/compare.py separate implicit
    bash .analysis/final-origin-review/sprite-constructor-spine/build.sh no-gy-implicit no-gy-typed-implicit no-gy-explicit
    scripts/repo-python .analysis/final-origin-review/sprite-constructor-spine/compare.py no-gy-implicit no-gy-typed-implicit no-gy-explicit
    bash .analysis/final-origin-review/ctor-pch-order/build-no-gy.sh stage-split-constants stage-implicit-dtor-constants
    scripts/repo-python .analysis/final-origin-review/ctor-pch-order/compare-no-gy.py stage-split-constants stage-implicit-dtor-constants

### R315 — The complete Fighter vtable permits an implicit Actor constructor

The Fighter constructor and stage resource loader share the
ordinary `.text` section when compiled without `/Gy`. The
earlier partial Fighter declaration added a deleting wrapper
between the loader and the Actor constructor. The native
20-slot Fighter table has `_purecall` at the destructor slot.
Declaring that slot pure and restoring the remaining observed
virtuals removes the extra wrapper.

An implicit Actor constructor and the out-of-line definition then
both reproduce the 439-byte linked loader and constructor interval
`0x004584D0..0x00458686`, with the Actor and rendering base at
`+0x180` and `+0x1A0`. Both comparisons include all 120 linked
vtable bytes, the complete earlier Fighter caller and all three
exception records. The linker binds the same earlier texture
wrapper. This reopens the origin of `0x00458650`; commit
`3651617b` records the earlier decision.

    bash .analysis/final-origin-review/actor-no-gy/build.sh
    scripts/repo-python .analysis/final-origin-review/actor-no-gy/compare.py both-explicit implicit-actor

### R316 — Omitting function packaging leaves both texture lifetimes at the native offsets

All 35 texture methods compile in one translation unit after
their shared declarations are consolidated. Without `/Gy`,
the implicit lifetime functions are the first two COMDATs
after the shared ordinary code section, at the native
`0x0040D8C0` and `0x0040D8E0`. The out-of-line definitions
remain in the ordinary code section at those same offsets.

Both forms reproduce the complete 10,483-byte code interval
`0x0040B000..0x0040D8F2` and all 308 code relocation fields.
Each also matches all 162 bytes and 15 relocation fields in
the three allocator exception records. This reopens both
origins. The earlier linked comparison and ownership decision
remain in commit `2f07989c`.

    bash .analysis/final-origin-review/texture-no-gy/build.sh implicit out-of-line-last
    scripts/repo-python .analysis/final-origin-review/texture-no-gy/compare.py implicit out-of-line-last

### R317 — The implicit sequence and frame copy matches survive without function packaging

Removing `/Gy` preserves the R296 implicit script copy's complete
401-byte window and 36 relocation fields. The in-class explicit
copy still appears before both destroy dispatchers. The R297
implicit frame copy retains its complete 688-byte window and 53
relocation fields. Its explicit control still places both copies
before the allocator anchors. The complete code and exception
comparisons preserve both prior compiler origin decisions.

    bash .analysis/final-origin-review/copy-no-gy/build.sh
    scripts/repo-python .analysis/final-origin-review/copy-no-gy/compare-script.py
    scripts/repo-python .analysis/final-origin-review/copy-no-gy/compare-frame.py

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
