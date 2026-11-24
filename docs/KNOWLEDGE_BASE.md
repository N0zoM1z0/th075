# TH075 knowledge base

Reusable findings about the original `th075.exe` (Japanese 1.11) and the
VC7.1 build 3077 compiler that rebuilds it. Current work and blockers are in
the [handoff](RE_HANDOFF.md). [GIANTS.md](GIANTS.md) records the
Advance parents and compiler evidence. Everything here was observed on the original PE
or in a cold build; checkpoint numbers (Fnnn) point to the commit history.

The journal this page replaces (per-checkpoint notes F179–F1239, about 17,000
lines) is in Git: `git show 430a06a4:docs/KNOWLEDGE_BASE.md`. Most of it
described what each accepted function does, which the source and ledgers now
record. Consult it only for the full history of a specific checkpoint.

## Windows link

WinMain at `0x00602A60` reads the same byte its window callback at
`0x00603650` sets on `WM_CREATE`. The byte at `0x0068D674` lies beyond the
raw contents of the target's writable `.data` section, so the callback
translation unit defines it with zero-initialized storage. WinMain's
existing relocations to `0x0041CAE0`, `0x0041CC00`, and `0x0041CC50`
bind to the cosine table builder and the shared diagnostic log functions.

The consecutive zero-filled allocations at `0x006884C0` and `0x0068BD00`
hold the 3,600-float lookup table and the diagnostic path. The table
ends at the path. The `MAX_PATH` buffer ends at the archive use count
at `0x0068BE04`. WinMain and the title update share the initially null
`HWND` at `0x00671608`. The result, replay and scene input callers now
use the existing keyboard poll at `0x00403E50`, joystick poll at
`0x00403F40` and window mode toggle at `0x004018A0`.

The D3D8, DirectInput and DirectSound state between `0x00671180` and
`0x0067139F` starts as zero-filled data. The nonzero graphics defaults
live at `0x0066C080`, `0x0066C084`, `0x0066C088` and `0x0066C1B8`.
The graphics teardown at `0x00401020` now releases the pointers set
by the initialization and reset routines, including the render-to-surface
array at `0x006711FC`, the device at `0x00671230` and the D3D8 interface
at `0x0067122C`. VC7.1 constructs the two DirectInput joystick vectors
in the order recorded by the target's R024 startup records.

WinMain reads the same three one-byte display flags as the config loader,
writer and defaults. The `bool` display flags and
the unsigned-short dimensions in `Graphics::Initialize` preserve WinMain's
call and comparison bytes. The presentation aliases at `0x004028F0` and
filled-rectangle aliases at `0x00403910` now use the existing graphics APIs.

The config loader owns the initially zeroed 80-byte key binding block at
`0x00671440` and the ten following serialized setting bytes. The defaults
and the configuration writer use the same storage. A headless executable
linked from the aggregate library saved a 90-byte `config.ini`, cleared
the test state and loaded the stored key bytes, display flags and volumes.

The options setting at `0x006714D0` has one signed byte definition and
still occupies one byte in `config.ini`. The combat mode at `0x006714B4`,
stage byte at `0x0067161E`, fade byte at `0x006714D1`, and transition
counter at `0x0067149C` each have one zero-initialized definition. The
2,166 COFF references in the comparison units use zero addends for
these locations. `ConfigLoadF194.cpp` defines all five variables and
lets archive consumers access them independently of resource initialization.
A headless archive-linked smoke test verified all five startup zeros
and the round trip from signed `-91` to byte `0xA5` at offset `0x56` and back.
The loading scene calls the existing character loader at `0x004176F0`.
Loading and sequence dispatch call the same stage loader at `0x004183D0`.

`BattleSessionState.hpp` declares the shared presentation, replay,
selection and continue state. The four bytes at `0x0066C237` through
`0x0066C23A` each start at one. The remaining nine definitions in the
same header are zero-initialized. The config loader, saver, input-binding
callers and settings display share the key and volume bytes declared in
`GameConfigStorage.hpp`. The display reads volume as signed, while the
serialized format preserves the raw byte. An archive-linked test checked
all 13 startup values and saved and reloaded high-bit key and volume
bytes in the 90-byte configuration file.

The character loader stores the roster selection at `0x006714C9` and
copies it to the stage byte at `0x0067161D`. Its next comparison reads
the stage byte. The former manifest mapped the symbol for `0x006714C9`
to both addresses in the same function. The comparison now uses the
shared stage symbol and the other references still use the roster byte.
The clamping helper writes the worker's wait time at `0x0066C23C`.

When reusing a cold-replayed object in the aggregate build, route it by
the translation unit's filename stem. The configured comparison object
`RemiliaObjectAdvance.obj` is archived as `CharacterObjectWhole0055AC80F1194.obj`.

The AI policy templates inherit the `Fighter` integer range at
`0x00455610`. `CharacterAuxObject` keeps a separate entry at `0x00410F00`.
Both entries still compare over 44 bytes with their CRT `rand` relocation.
The existing `Fighter` notice setter writes `sequencePhase` at `0x6E4`.
The floating-point call sites share the VC7.1 wrappers declared in
`MathFloatHelpers.hpp`, and character loading uses the same snapshot
entry points as the replay code.

`FloatConstants.hpp` lets callers share nineteen read-only scalars whose
values already appear as VC7.1 literal definitions. The Japanese 1.11 image
stores them in `.rdata`. Separate definitions in `MathFloatHelpers.cpp`
preserve the memory operands, including 4,328 zero-addend `DIR32` fields
that previously referred to 147 different extern names. The shared type
tracks each operand width, including the single- and double-precision
halves and three quarters. Include the declarations at the translation
unit's top level so switch fragments can use them inside function bodies.
A headless consumer linked against the library and checked all nineteen
values alongside the existing absolute-value and square-root wrappers.

`GeometryConstants.hpp` declares 51 single-precision values used in
coordinates, bounds and angle calculations. Each definition matches the
existing VC7.1 literal and the original `.rdata` bytes at its relocation
target. The angle conversion uses the program's stored single-precision
value for radians per degree. The new declarations preserve 2,265
`DIR32` fields across 286 previous extern names.

The projected quad uses the shared half, one and two values for its
pixel offset and depth calculation. Camera snap and other position
calculations share the existing 300.0f value. Callers of
`Fighter::RecordRoundFields` use signed byte and integer parameters.
Compiling the implementation with that declaration preserves its
389-byte body at `0x004574D0` and resolves the existing callers.

The loader and lifetime methods share all 36 stage class declarations.
The base constructor at `0x00449DE0` calls the camera constructor at
`+0x04` and the texture manager constructor at `+0x18`. The first stage
member begins at `+0x68`. The native `SpriteQuad40CA80` placement varies
from `+0x68` to `+0x74`. The BG09a renderer accesses 130 28-byte
vertices beginning at `+0xF0` within the observed `0x1D28` allocation.
The complete six-slot tables bind the existing callbacks, and the
constructor unwind records call the base destructor at `0x00449D40`.

Loading, frame updates, rendering, and shutdown use the same initially
null stage pointer at `0x00671424`. The final virtual slot receives the
destination quad, color and source quad in that order. The mirrored
renderer copies the three stage parameters at `+0x0C`.

Battle teardown emits the same 44-byte texture-manager deleting wrapper
at `0x00425460`, including calls to `0x0040AE40` and `0x00640F15`.
A standalone link against the archive reached seven unresolved graphics
data definitions after adding the program's Windows SDK libraries. Six
are diagnostic strings and one is the pixel shader.

The replay reader and input handlers share `g_ReplayRecords` at
`0x00671750`. The 0x1A4-byte owner holds four 20-byte VC7.1 deques at
`+0x154`, `+0x168`, `+0x17C`, and `+0x190`. Their element types are
`unsigned char`, `short`, `unsigned char`, and `unsigned int`.
The constructor and destructor retain native exception cleanup. The
public VC7.1 `deque::clear()` and its destructor both use `_Tidy`, which
accounts for their identical wrappers at the original call sites.
A headless archive consumer loaded a test record into all four queues,
checked the signed sample and high-bit values, cleared the queues, and
confirmed that destruction closed the owned Windows handle.

The owner has a 260-byte path at `+0x04` and a 60-byte file header at
`+0x108`. The header holds the name, date and ten record offsets. Capture,
snapshot loading, finalization and both path-selection callers use the
same owner. A headless archive consumer read the header and one record
from a single test file.

The snapshot code uses the first player's fields in the file header and
the second player's fields in the record header at `+0x144`. The replay
limit read by the battle and result scenes is the same signed byte as
`fileHeader.recordCount` at `+0x116`. The name screen reads the name and
date from that file header. The battle loader reads two bytes at `+0x14C`
and four at `+0x150` from the loaded record. The headless file test
preserved high-bit values in the named snapshot fields.

The result-list scene owns a 20-byte VC7.1 `std::deque<char*>` at
`+0x18`. Both card loaders append a null entry with `push_back(0)`,
then allocate its name with array new. Passing the null literal places the
temporary in the native stack slot under `/Od /GX- /GS`. A named null
pointer swapped that slot with the file buffer allocation in both loaders.
The defaults constructor and the encoded loader share eleven resource name
rows with a 20-byte stride at `0x006714D8`.

The VC7.1 `abs(long)` overload binds all fourteen selection input calls
at `0x00438A60`, with `labs` as its worker. The round banner uses the
SDK's `log10f` at `0x00442040`. The collision wrapper at `0x00449A60`
calls `ceilf`, whose float-to-double conversion and call to `ceil` match
at `0x00449A80`. The compiled wrappers and workers match the complete
native bodies and their call relocations. The origin ledger retains the
alternative declarations from R163, R308 and R310.

Suika's auxiliary action uses the same typed fighter effect call as
Patchouli. In the Suika translation unit, the `40.0f` literal in the
vertical argument preserves the native x87 load order. Passing the same
value through `GeometryConstants::Forty` makes VC7.1 load the constant
before the opponent's position.

The battle HUD and status renderer access the existing sequence and
frame vectors through `at()`. The entries at `0x004420B0` and
`0x00442060` match the complete VC7.1 instantiations for
`FighterSequenceInfo*` and `FighterFrameInfo`. The direction-bit writer
uses the input history deque's `assign(90, bits)` at `0x00455C40`.

The battle loader writes ten roster bytes from `0x00671490`.
Reading the one-based stage as `roster[stage - 1]` emits a minus-one
relocation addend to the same array. The apparent base at `0x0067148F`
is the last byte of the preceding key bindings, so it does not define a
second roster. The coordinate output floats at `0x0067142C` and
`0x006714A8` both start at zero.

`PlayerState.hpp` declares the six byte pairs shared by selection, the
battle loader and snapshot I/O. A direct reference to the second player
uses the pair symbol with an addend of one. The record sequence at
`0x006714A4` is a separate 16-bit value. The loader writes the two fighter
pointers at `0x00671418` and `0x0067141C`, and the scene constructors,
display and cleanup paths use the same slots. The cleanup calls retain
the deleting destructor in fighter vtable slot five. A headless consumer
saved a two-player snapshot, cleared both players' state, and restored
all twelve bytes and the stage selection from the test file.

`BattleResultState.hpp` declares the shared score, combo and scene-flow
storage. The battle code accumulates the value at `0x0067160C` as an
unsigned 32-bit integer and the result constructor interprets it as
signed before the floating-point conversion. The title scene writes the
16-bit cursor at `0x00671630` on exit and reads its low byte on entry.
The four signed boundary and action sentinels at `0x0066C24C` through
`0x0066C24F` start at minus one. The remaining definitions in this batch
start at zero.

Replay append uses the shared byte, short, and unsigned-int deques.
The six named VC7.1 iterators match all 1,252 bytes and 50 relocations.
Declaration order gives the constructor call order, while local names
can change the stack slots at that same order. The matched iterator
offsets are `-0x38`, `-0x2C`, `-0x1C`, `-0x24`, `-0x08`, and
`-0x10` from EBP under `/Od /Ob0 /GX- /GS`. The three deque families
also reproduce the complete 21 SDK entry points called by the writer.
The unsigned byte queue supplies both byte runs, and the shared clear
method empties all four queues once the record is written.

`Graphics::BeginFrame` returns the status from `BeginTarget` on both
branches. The native caller tests AL, and the bool declaration preserves
all 36 bytes of the wrapper. The application and scene drawing callers
share that interface.

WinMain uses the shared event, input, sound, archive and game-default
lifetime functions. All fifteen scene types have compile-time checks for the
native allocation sizes. The comparison covers the complete WinMain
body and its 15-entry scene table.

WinMain and those scene types share the eight-byte `SceneBase`.
Its constructor and destructor call the defaults lifetime at offset four.
All three slots in the base vtable at `0x00657B88` resolve to `_purecall`.
Derived tables use the deleting destructor, unsigned 16-bit update, and
render slots. Character selection releases its three texture managers
through the same class that constructs them. The base constructor at
`0x004251C0` remains in origin review.
[Constructor origin evidence](ORIGIN_PENDING_REVIEW.md#r314--omitting-function-packaging-restores-the-native-scene-order)

Loading and logo scenes share an allocation size of 16 bytes. Their
state at offset 12 is an unsigned byte for loading and an unsigned
short for elapsed logo frames. Opening and staff-roll scenes share the
20-byte allocation size and keep their elapsed time and initial ticks
at offsets 12 and 16. Battle-end uses a 12-byte allocation. For all
five types, both the constructor and the destructor objects emit the
same three virtual table entries and the native 44-byte deleting
destructor. Exception cleanup calls the shared base destructor.

The two name-entry scenes share their rendering, input and allocation
layouts through `NameEntryScenes.hpp`. The player name editor selects a
`ProgressScore` in the existing difficulty record. The shared editor
uses the player name in the replay file header. The music room's four
texture pointers precede 60 catalog records of 16 bytes each. Its
selection counters follow the catalog at offsets `0x3DC` through
`0x3DF`. Named member accesses preserve the original array strides
and all three scenes' virtual table targets.

The 84-byte replay browser owns 20-byte VC7.1 deques at offsets
`0x0C`, `0x20` and `0x34` for filenames, 60-byte replay file headers
and secondary mode bytes. The scanner, selection and renderer use
the same containers. Selection writes to `g_ReplayRecords.filePath`
with a four-byte relocation addend. The scanner uses the CRT array
allocation entry at `0x006416A2` and retains the native file-header local
and stack-cookie layout.

The progress object occupies `0x16BC8` bytes from `0x006718F8` to the cosine
table. Its startup and registered exit wrappers match the native code.
WinMain and the progress callers share the same object. A headless
executable linked from the library checked the startup defaults and saved
and reloaded a disposable `0x16BC4`-byte score file.

WinMain registers the address of its event handle with the startup queue.
The enqueue, acquire, worker, and release code uses the same VC7.1
`std::deque<HANDLE*>` at `0x0068BE44`. The worker and lifecycle code also
share the ready event and wait interval, which starts at 16 milliseconds.
The worker's loop dereferences the queued address before calling
`SetEvent`. The release path passes the queued address itself, as shown
by the different native load chain. A headless library consumer verified
that enqueuing the same handle address twice leaves one entry.

The worker's ordinary iterator declarations reproduce all 273 bytes
and 19 relocations with the three native zero-initialized locals and
the explicit zero return. A headless library consumer queued an empty
handle followed by a live event and verified that the worker signaled
the live event.

Archive registration, lookup and release use the two VC7.1 deques at
`0x0068BE08` and `0x0068BE1C`. The registered object is 16 bytes and
contains a Windows handle followed by a list of 108-byte index records.
The reader and the two lifetime functions share one translation unit.
With `/GX`, all three preserve their complete native bytes and relocations.
A headless library consumer registered a synthetic empty archive, found it
by name, released its handle and deleted the file.

The archive lookup now returns the typed object. Audio, script, texture,
and other loaders call its two seek methods, which use the index record's
named size and offset fields. A headless consumer opened a synthetic
archive containing one encoded index record, sought to its payload with
both methods and read the expected bytes.

Appending a readable file uses the same 108-byte index record as the
reader. Named close uses the registered-name and object deques directly.
VC7.1 placed the four iterator locals at different offsets under the
first set of names. The current names reproduce the 264-byte function
and all 19 relocation fields with ordinary iterator initialization.
A headless library consumer appended an entry, closed the first of two
registered archives and found the remaining archive by name.

The archive writer constructs its two index iterators directly from
`begin()` and `end()`, then reassigns them before writing payloads.
Declaring the output handle before the input handle restores their
native VC7.1 stack slots. The 686-byte writer and all 28 relocations
match. A headless library consumer wrote a synthetic archive, reopened
its index and read back the original payload.

The 20-byte sound bank starts with a VC7.1 vector of DirectSound buffer
pointers. Its count field is at `+0x10`. Startup and fighter initialization
call the same constructor. Playback uses unchecked indexing for the null
test, then checked indexing for the buffer it plays. Teardown uses
unchecked indexing and releases the same vector. The stream worker and
the bank lifetime share the playback flag and event handle. The bank and
stream volume bytes start at 100. Options retain signed byte arithmetic
when reading and updating the configuration volume bytes.

The call at `0x00419CB0` selects a music track, and `0x00407E60` schedules
a fade using two signed 32-bit values and two byte flags. Several scene
callers formerly labeled these operations as stage or viewport changes.
The complete caller comparisons preserve the original destinations.
[Sound vector evidence](ORIGIN_PENDING_REVIEW.md#r286--sound-buffer-and-replay-and-script-deque-helpers)

The 20-byte deque at `0x006713A0` holds 64-byte `AudioStream` records.
File and archive loading push records into it. Playback reads the front,
and the sound bank clears it at the first and last client. VC7.1 emits
the same 19-byte `_Tidy` caller for `clear()` and the destructor. Native
startup and exit use the separate construction and destruction entries
at `0x0040AC80` and `0x0040AD60`. Both wrappers and the queue operations
were compared with the actual record type.

The initializer at `0x00656D60` constructs two 72-byte input mappings
at `0x00671638`. Each holds a 40-byte key configuration at `+0x04` and
seven signed held counts at `+0x2C`. Scene callers read the shared array
with the observed COFF addends. `/GX` gives VC7.1 the same constructor
and destructor iterators at startup and exit. The fighter also uses those
mapping lifetime methods for its input member at `+0x494`.

The font surface allocates 56 bytes. Its GDI context, font, previous
selection, glyph bitmap and color fields are shared by the constructor,
rasterizer and both cleanup paths. The font argument at `0x006578B0`
is the CP932 GDI face name, the same name used by the menu and results
callers. The compiler-emitted deleting destructor calls the full cleanup
at `0x0041BFD0`.

The shared text overlay at `0x0067143C` allocates 120 bytes, with the
canvas at offset zero and the embedded texture manager at `+0x28`.
Its outline drawing uses the SDK-backed RECT quad. Direct construction
of that quad reproduced the complete draw function, including the
native RECT and quad stack locations.

Camera initialization, motion, and drawing share the initially zeroed
camera state at `0x006713BC` through `0x00671414`. The combat view offsets
at `0x00671404` and `0x006713C4` are written by the camera and read by the
renderers. The pinned VC7.1 `cosf` and `sinf` wrappers also supply the two
float entry points called by the camera and scaled sprite routines.
The override entry at `0x00412CC0` takes an enabled byte and three
floats. The reset path passes zero for each argument. Scene callers use
that entry and the snap routine at `0x00412CF0`.

The renderer reads the frame flag at `FighterFrameInfo+0x0C` as a byte.
The frame assignment copies the entire 16-byte header, including the
three bytes following the flag. Both operations use the same layout.

The music, options, results, and window constructors allocate their
canvases through `Graphics::CreateTexture` at `0x00401C20`. Its output
is an `IDirect3DTexture8**`. The window resource constructor passes the
address of its first member, which precedes the archive member at `+0x28`.

Transition dispatch and drawing share the countdown at `0x0066C240`,
which starts at -1. The two direction fields start at 1.0. The 640-float
column table and the amplitude and phase fields are zero-filled in the
writable section's virtual tail. Transition dispatch and frame capture
register their callbacks through `Graphics::SetPresentCallback`.

The eight-byte frame texture owner has a D3D8 texture at offset zero and
a direct-draw flag at `+4`. Its pointer at `0x006714C4` starts null.
Startup, cleanup, and the battle and result callers share the owner.
Capture at `0x004170D0` passes its texture member to
`Graphics::CopyTextureOpaque` and reads the source texture through
`Graphics::GetPrimaryTargetTexture`.

The rectangle and default quad constructors use four `D3DXVECTOR4`
members, a `D3DXMATRIX` at `+0x40`, and an unknown dword at `+0x80`.
The rectangle constructor was exercised by a headless library consumer.
The capture callback still uses a borrowed rectangle constructor binding.
A trial with separate C++ locals placed the RECT at `[ebp-0x10]`. The
native function places it at `[ebp-0x98]`.
[SDK matrix evidence](ORIGIN_PENDING_REVIEW.md#r293--sprite-matrix-constructor-selection)

The HUD and timeline callers use the shared quad translation, scaling, and
rotation methods. The loading and logo draws also use the shared rectangle
transform and `Graphics::EndFrame`. Declaring the quad and RECT separately
made VC7.1 place the RECT at `[ebp-0x10]` in both declaration orders. The
156-byte native draws use `[ebp-0x98]`; their constructor call still relies
on the existing combined stack carrier.

The battle digit atlas takes a one-byte allocation. Its constructor
initializes three texture pointers and fourteen sets of glyph rectangles,
dimensions and advances. The HUD reads those same zero-initialized tables.
The results renderer uses the shared `SpriteTransform::ScaleQuad` float
interface.

The static effect owner at `0x006716C8` holds two 20-byte VC7.1 deques, an
80-byte texture manager at `+0x28`, and a vector of pattern pointers at
`+0x78`. The pattern sequences hold 16-byte frame headers. The CRT
initialization and teardown stubs and the sequence deleting destructor
match. The typed catalog loader needs its per-unit profile to omit
`/GS` to match the original exception frame. VC7.1 interprets `/GS-`
as `/GS` followed by the unrecognized `/G-` option.
The two spawn paths allocate a 148-byte `CharacterAuxObject` with a
116-byte shared rendering base. The effect stores its pattern vector
pointer at `+0x7C`, spawn parameters at `+0x80` and owner at `+0x90`.
The update and release loops use scalar `delete` for objects with
trivial destructors. VC7.1 emits a pointer temporary for the delete expression,
which places the deque's end iterator and deletion temporary at the
native stack offsets.
The four shared D3D interface pointers are defined in the graphics
teardown translation unit. The archive consumer for the atlas and effect
lifetimes links with that cleanup and runs headless.

The texture manager stores a VC7.1 vector of 44-byte entries at `+0x08`
and two vectors of texture pointers at `+0x18` and `+0x28`. Both bitmap
directory loaders use those vectors along with pack I/O, texture lookup,
and release. Bitmap load, encode, and upload use the entry's named fields.
The entry constructor and destructor each call the bitmap lifetime
routine at offset zero. The source models the observed 44-byte slot as
shared storage. The historical bitmap subobject's extent remains open.

The serialized bitmap loader calls the scalar allocator entry at
`0x0064159D` for byte arrays under its original VC7.1 profile. Pulling
the texture-manager templates into its translation unit changed those
three COFF relocations to the array allocator. The smaller shared record
header restores the scalar binding and the complete 326-byte comparison.
A headless library consumer loaded a synthetic 8-bit BMP and checked
its palette colors before and after encoding.

WinMain's graphics client occupies a standalone byte and both lifetime
methods update a shared count. A client member at manager offset zero
preserves the native palette offset and 80-byte extent. VC7.1 eliminated
the client storage when declared as an empty base. The deque at `+0x38`
uses four-byte entries with trivial destruction. Its constructor,
destructor, cleanup, and back removal match with the pinned VC7.1 deque.
The texture-manager draw state methods retain their native thiscall
interface. The blend method selects depth state before forwarding the
blend mode, and the depth, filter, shader, and color methods forward
to the shared graphics state.

Texture lookup, sprite drawing, and projected triangle strips use the
same 80-byte texture manager as allocation. The stage renderers pass its
member at offset `0x18`, while the static effect resource loader uses the
member at `0x28`. The fighter loader constructs both texture managers
with the shared constructor and passes a signed byte to archive loading.
The lookup keeps one palette index cache across the drawing paths.

The ordinary draw at `0x0040C9A0` and projected draw at `0x0040CA20`
copy all 132 bytes of the sprite quad before calling the graphics
renderer. The ordinary draw also stores a texture lookup and the size
of the entry vector in its local frame before the second lookup. Using
the SDK-backed quad directly for local copy storage changed the ordinary
draw's stack layout under VC7.1. The entry points accept that shared
quad by reference and preserve the observed local copy layout. The
four-float constructor at `0x0040DA00` uses the same quad layout as
the default constructor at `0x0040D990`.

The loading and logo renderers match with a named quad outside the
inner `RECT` scope. Rank rendering matches with the named `rankQuad`
and `glyphCodes` locals in one scope. A discarded temporary retained
the full code size and relocation offsets, but placed the quad eight
bytes closer to the frame pointer. Frame capture matches using
`RECT region` and `SpriteRectF211 spriteQuad` in one scope. The save
filename renderer uses the browser's existing character-array prefix.
The fourteen readonly bytes match at both native locations, and the
save renderer copies them through the original four relocation addends.

The options, result and title scene vtables resolve the weak vector
deleting entry to each scalar deleting destructor. Their texture
cleanup calls the 44-byte manager deleting wrapper at `0x00425460`,
which calls the manager destructor at `0x0040AE40`.

At `819f57a4`, linking the archive with WinMain and the seven
`.CRT$XCU` objects omitted 34 externals from the full-object link
diagnostic. Twenty-two came from the replay append object and seven
from the sprite history renderer. The archive link helps prioritize
missing definitions by translation unit.

Naming the entry's byte arrays caused VC7.1 to emit a stack cookie in
the three slot allocators with `/GS`. Omitting that option for those
three units reproduced the native prologues and their full unwind
records with the typed vectors.

The six-argument tracked effect helper at `0x00453AC0` is a
`Fighter` overload shared by the character callers. Mode 5 input at
`0x00454C20` uses the fighter's input fields and calls virtual slot 11
through `ChooseAction`. The Youmu callers use the signed-byte pattern
arguments and the existing command selection and direction packers.
Fighter resource loading uses the parser's two stream methods on the
script object at `+0x714`.

The script resource spans `+0x714..+0xEF7` in the fighter. Its first
1,000 shorts map script IDs to a VC7.1 deque of 20-byte sequences.
Each sequence holds a deque of 8-byte records. The constructor, parser,
field accessors and destructor use those types directly. R296 identifies
the sequence copy as compiler-generated.
[Script copy evidence](ORIGIN_PENDING_REVIEW.md#r296--script-sequence-copy-emission-order)

The action table at `Fighter+0x468` is a VC7.1 vector of sequence
pointers. The 20-byte sequence holds a vector of 116-byte animation
frames followed by two priority words. Fighter and character object
slot 0 use the same typed vector accessors. The fighter's slot-7
factory returns a `CharacterObject*` through its output parameter,
and the owned effect manager stores that type in all four deques.

VC7.1 accepts multi-source response files with one output directory and a
PDB per compiler profile. Keep two-token switches such as `/I src` on the
same line. Splitting the switch from its argument across lines produces
`D2004`. Pass `link.exe /lib` before the response file because VC7.1
selects librarian mode before it expands the file. The pinned D3DX8 archive
requests the VC6 library `libci.lib`, which the VC7.1 install lacks.
`/NODEFAULTLIB:libci.lib` bypasses that directive. A headless PE32 smoke
called the rebuilt window callback and allocated a D3DX8 buffer successfully.

The first strict link reported 677 missing symbols whose unique manifest
target already has an accepted function definition. The address gives a
place to check the ABI and source owner. Keep the full link diagnostics in
`build/program/link.log`.

## Class structure

The PE vtables give the real hierarchy (`.analysis/layout-tools/vtables.json`
dumps them):

- `Actor` (`src/Actor.hpp`, 0x00–0xC3) is the base of every animated battle
  object; its shared helpers (0040FA30–0040FC50 and 00455500) are in
  `src/Actor.cpp`. Slots: 0 `BindAnimation` (fighters 00453D80), 1 `Advance` (pure),
  2 `Render` (fighters 00453F70), 3 `RenderNode` 00410350, 4
  `RenderMirroredNode` 00410A00. The vtable pointer is at +0.
- `Fighter : Actor` (`src/Fighter.hpp`, up to 0xF0F, `sizeof` 0xF10).
  Constructor 004567B0; the base table at 00658FE8 uses `_purecall`
  00641E19 for pure slots. Slots 5–19: 5 `~Fighter`, 6 `ResetRound` (base
  00457010), 7 `CreateOwnedObject`, 8 `ForwardBaseAction` (base 00451EB0),
  9 `RenderChain`, 10 `DispatchActions`, 11 `ChooseAction`, 12
  `ChooseCardAction`, 13 `PollCommands`, 14 `SelectVariant`, 15
  `ConfigureStage`, 16 `AdvanceSequence`, 17 `RenderStage`, 18
  `NoOpSlot18`, 19 `AdvanceAuxiliary`.
- `<Char>Fighter : Fighter` (`src/<Char>Fighter.hpp`, 11 classes) holds each
  character's overrides and its own members from +0xF10 (shorts in some
  characters, floats in others). The constructors live in
  `src/<Char>Init*.cpp`.
- Fighter command-selection state uses `field47C` (+0x47C) and the
  associated sprite-sequence pointer at +0x480. `SetCommandSelection`
  (00454BC0) writes the selection and updates the sequence sampling/color
  policy. The adjacent 24-byte leaf at 00454C00 is now reconstructed as
  `Fighter::ClearField47CAt00454C00`; it is a natural member store of zero
  to +0x47C and cold-replays exactly. Its address-anchored name is retained
  because no static references to this leaf were found.
- `CharacterObject : Actor` (`src/CharacterObject.hpp`, constructor
  0045B760, base table 00659064, `sizeof` 0xE8) is each character's effect
  object: `sequences` at +0xC4, floats +0xC8–0xD0, shorts +0xD8–0xE2 and
  the owning `Fighter*` at +0xE4. Object tables have five slots and no
  destructor. `<Char>Object` constructors are in
  `src/CharacterObjectConstructorsF422.cpp`.

Slot 1 of each character table is the per-character `Advance`.

| Character | Fighter Advance | Object Advance |
| --- | --- | --- |
| Reimu | 0045DD70 | 00476A40 |
| Marisa | 00486550 | 0049C8F0 |
| Sakuya | 004AC040 | 004CA6E0 |
| Alice | 004D7E70 | 004EBDA0 |
| Patchouli | 004F7130 | 0050A580 |
| Youmu | 005214B0 | 00536400 |
| Remilia | 00543210 | 0055AC80 |
| Yuyuko | 00564BE0 | 0057D580 |
| Yukari | 0058AF60 | 005A1600 |
| Suika | 005AEEC0 | 005C9CC0 |
| Meiling | 005D73C0 | 005EB520 |

Several old labels were wrong: "Boss 0050A580" is Patchouli's object, and
004AC040 is Sakuya's fighter. A correctly named override and a wrongly
attributed one emit the same bytes, so check the vtable slot before naming
a method.

`BattleScene` (`src/BattleScene.hpp`, vtable 00658334: slot 0 the
deleting destructor, 1 `Update` 0043B1B0, 2 `Render` 0043D9D0) owns the
match. Its methods run from 0043AD10 to 00449310, interleaved with a few
  helpers of the progress records and combo counters. Members: +0x08 the
  texture manager, +0x0C frame timer, +0x18 match mode, +0x34 hit bounds,
  +0x44 the two fighters, +0x4C digit atlas, +0x50 the two combo counters,
  +0x58 the active counter, +0x5D/+0x5E winner and quote line, +0x60/+0x64
  notice timer and state, +0x70–0x88 overlay values, +0xA4 each side's saved
  input state, +0xDC–0xF3 per-side status values.

## Layout facts

- The 164-byte sprite history element at `0x00411C10` constructs its
  quad at `+4`. Omitting `/Gy` makes the implicit and explicit
  definitions occupy the same native slot after the draw and
  transform methods. VC7.1 warns about `/G-` when passed `/Gy-`.
  [Sprite history constructor comparison](ORIGIN_PENDING_REVIEW.md#r314--omitting-function-packaging-restores-the-native-scene-order)

- The Actor constructor at `0x00458650` calls the rendering base
  constructor and installs the five-slot Actor vtable. In the
  20-slot Fighter table the destructor slot is pure virtual.
  With that declaration and `/Gy` omitted, an implicit Actor
  constructor occupies its native slot after the loader.
  [Linked loader comparison](ORIGIN_PENDING_REVIEW.md#r315--the-complete-fighter-vtable-permits-an-implicit-actor-constructor)

- The stage base constructor at `0x00449DE0` installs its six-slot
  vtable, then constructs the camera at `+4` and texture manager at
  `+0x18`. The precompiled derived destructor defers its deleting
  wrapper, making the first constructor-order difference observable
  through the complete BG00a interval.
  [Stage lifetime order](ORIGIN_PENDING_REVIEW.md#r305--stage-base-constructor-follows-the-deleting-destructors)

- The texture entry constructed by `0x0040B000`, `0x0040B110`, and
  `0x0040B1D0` occupies 44 bytes. Its lifetime methods call the
  bitmap lifetime at offset zero. Both implicit and explicit
  definitions match when `/Gy` is omitted. The bitmap
  methods establish fields through the pixel pointer at `+0x1C`.
  Texture loaders access a separate byte at entry offset `+0x28`.
  The bitmap extent within that entry remains open.
  [Linked lifetime evidence](ORIGIN_PENDING_REVIEW.md#r316--omitting-function-packaging-leaves-both-texture-lifetimes-at-the-native-offsets)

- Youmu has an independently observed 0xFF8-byte fighter allocation
  (`BattleCharacterLoaderF398`, character 5). The VC7.1 12-byte
  `std::list<ObservedInputSnapshotF378>` member at +0xFEC is the final
  member, after an unobserved +0xFE4..+0xFEB gap. The snapshot is 16 bytes:
  action/stage shorts, float x/y, facing byte and bearing short. Its automatic
  construction, clearing, auxiliary writer and object `Advance` reader retain
  the original method call destinations (00531C00, 00531CE0, 00531CB0,
  00540220). Affected exact units cold-replayed 81/81; the 39,999-byte
  object giant remains nonexact with its full 40,464-byte COFF unchanged.
- The bound fighter's effect manager at +0x2EC occupies 0x54 bytes: its
  bound `Fighter*` and four 20-byte VC7.1 deque members. Effect advance
  (0045BDB0) and both drawing dispatchers (0045BC30, 0045BCE0) now use
  named typed deque members, inherited `Actor` virtual slots and native
  effect flags. `BattleScene::Update` (0043B1B0) invokes all four per-frame
  effect ticks through this manager. The three effect functions cold-replay
  3/3 and the frame/header-dependency set cold-replays 74/74.

- The controller binding block is embedded at +0x494. `SetBindings` copies
  40 bytes at +4 and clears 28 at +0x2C, so the block spans 0x48 bytes and
  ends where `inputX` (+0x4DC) begins. Held input is at +0x4DC–0x4F4 (X, Y,
  ?, A, B, C, D) and a buffered copy at +0x4F8–0x50C. An attack press is
  `inputA == 1 || bufferedA > 0`. The battle and ending scenes both call
  `Fighter::UpdateControls` at `0x00452F10`. It reads the embedded
  physical input counts and uses virtual slots 11, 12 and 13 for AI
  selection and command polling.
- +0x53A–0x6CC hold the win quote: the line count, two 200-byte lines from
  +0x53B and a notice badge per line from +0x6CB.
- `Fighter::Fighter` at `0x004567B0` constructs the rendering and Actor
  bases, then the 8-byte camera state at `+0x2D4`, 16-byte sequence
  vector at `+0x468`, 72-byte input mapping at `+0x494`, 20-byte input
  history deque at `+0x518`, 20-byte sound bank at `+0x6D0`, and script
  resource at `+0x714`. The remaining fields between the constructor
  call addresses belong to the fighter. Its destructor frees the same
  sequence, history and texture owners. Native slot 5 of the Fighter
  base table is pure while the class supplies the base destructor body
  for derived teardown.
- The battle loader at `0x004176F0` allocates eleven concrete fighter
  types and stores them in the two shared `Fighter*` entries. Its
  complete allocation switch and unwind records match. Each fighter
  table has twenty slots, including action and card choice at 11 and 12
  and stage rendering at 17. Their 22 independent AI countdowns occupy
  zero-initialized storage from `0x0068D61C` through `0x0068D670`.
- The 24-byte command history owner begins with its texture pointer.
  Its 12-byte VC7.1 list at `+0x04` stores 164-byte sprite records.
  The constructor, append, trim, reset and deleting destructor now
  share that class. The renderer still uses a borrowed iterator view.
  [Command history destructor evidence](ORIGIN_PENDING_REVIEW.md#r299--fighter-cleanup-and-paired-base-construction)
- `RecordRoundFields` (004574D0) fills arrays at 0x32A, 0x33E, 0x370 and
  0x384 (20 entries each) and at 0x3D0, 0x400 and 0x430 (12 each), and raises
  +0x39D to the highest index used. +0x39D is therefore not a selected card,
  as an older macro name claimed.
- +0x74/+0x78 point to the current frame record (`flags` at +0x3C; bit 0x20
  gates action changes) and the current sequence record (`priority` at
  +0x12). Candidates from `sequenceSlots.At()` (004420B0) compare
  `targetPriority` at +0x10.
- `ConfigureStage` (slot 15) is the story-mode stage setup. It zeroes four
  per-character bytes right after the shared layout (Reimu, Suika and
  Meiling +0xFF4, Remilia +0xFD8, Patchouli and Yuyuko +0xFDC, Sakuya, Alice
  and Youmu +0xFE0, Marisa and Yukari +0xFFC).
- +0x04 is the sprite drawing context (an object copies its owner's) and
  +0x08 the frame record the node renderers draw; the object renderer
  (0040FC70, `CharacterObject::Render`, object slot 2) and the shared
  `Actor::RenderNode` (00410350) and `RenderMirroredNode` (00410A00, slots
  3–4) read them. The frame record's pose (+0x08 of the frame) holds the
  blend mode, ARGB colour, a 3D offset, scale and rotation.
- +0xA8–0xC3 is a collision snapshot that `Actor::SaveCollisionFields`
  (00455500) copies each frame before hits are resolved: +0x7C, both record
  pointers, the action, x and y (as raw DWORDs) and the facing. Hit tests
  read the snapshot (`savedFrameInfo` etc.), not the live fields. It ends at
  +0xC4, where `Fighter::name` and `CharacterObject::sequences` begin.
- The frame record (`FighterFrameInfo`) holds the sprite origin, texture
  index and a pose pointer (+0x00–0x0C, read by the renderers), the hit data
  (+0x10 damage, +0x14 combo-rate factor, +0x1C/+0x1E attacker and defender
  hit-stop, +0x24 card-gauge gain, +0x36 hit effect, +0x3C defence flags,
  +0x40 attack flags) and the collision boxes (+0x44 body box, +0x54 hurt
  boxes, +0x64 hit boxes, each a 16-byte vector of RECTs). The
  The hurt/hit members are now declared directly as
  `std::vector<tagRECT>`, so collision dispatch emits the native VC7.1
  `vector::size()` / `vector::at()` symbols at 004452D0 / 00445310.
  `FighterFrameInfo::operator=` at 0045AAE0 cold-replays its
  full 368-byte body and both vector-assignment relocations (0x151/0x163)
  to 0045AC50. The 381-byte `std::vector<RECT>::operator=` at 0045AC50
  also cold-replays with all 17 relocations. These compiler/library-origin
  functions remain excluded from authored exact coverage.
- Fighter gauges: +0x3B0 `spirit` (specials need it, guarding drains it, at
  0 the fighter is guard-crushed into state 143), +0x368 `cardGauge` (float,
  filled by hits, capped at 2000), +0x3C0 `comboRate` (each hit multiplies
  it by the frame's factor), +0x2D0 `score` (100–500 per hit). Older names
  called +0x3B0 a meter.
- In combat functions the attack is an `Actor` (fighter or object) and the
  attacker and defender are `Fighter`s; `Fighter::CalculateDamage(attack)`
  (00455640) is the attacker's damage against its opponent.

## Game progress (save data)

The progress object `g_GameProgress` at `0x006718F8` serves battle combo
records, mode counters, the status display and character selection.
Combo count and damage use fields `+0x008` and `+0x00C` of the selected
difficulty. The status display reads the words at `+0x268` and `+0x394`
from difficulty zero for the selected character. The layout is:

- 15 character blocks of 0x17F0 bytes from +0, each 4 difficulty blocks of
  0x5FC bytes. A difficulty block ends with 10 ranked scores of 16 bytes at
  +0x55C (8 name bytes, a DWORD, the score at +0xC; the lowest score sits
  at +0x5F8). `ProgressRankingF375::InsertRankedScore` (00416EE0) works on
  one difficulty block. +0x04 of a block counts selections and +0x556 is
  read by the single-player options.
- +0x16710: a 15×15 int table of mode counters; +0x16A94: 8 bytes (100
  each by default); +0x16A9C: 40 bytes of unlock bits; +0x16AC4/+0x16AC5:
  the selected fighter and difficulty; +0x16AC6: 256 bytes saved with the
  scores.

`src/GameProgress.hpp` declares this layout and 27 of its methods.
Nested indexing `characters[f].difficulties[d].x` compiles exactly like the
left-to-right sum `this + f*0x17F0 + d*0x5FC + off`, but not like
`this + (d*0x5FC + f*0x17F0)`: VC7.1 evaluates a parenthesized offset sum
before adding the base, in a different instruction order.
`IncrementSelectedRecordCount` (0041A270) needs that grouping and keeps it.

The selected-record accessors and mode counter live with the other
record methods in `ProgressSelectionF274.cpp`. A headless consumer
linked their archive member and exercised separate difficulty fields,
zero extension of both card counters, mode counter writes and the
selection check.

## VC7.1 `/Od` code generation

### Lifetime declarations and typed callers

The same 11-byte empty receiver body can be a live scene hook or an
explicit destructor. Follow the actual receiver across the call.
The progress global's matching constructor and registered finalizer
establish its destructor, and the implicit trivial control omits the
registration. A nontrivial implicit member lifetime can instead emit
the same calls as an explicit empty destructor, as the sprite list
owner demonstrates. [Comparisons and replay](ORIGIN_PENDING_REVIEW.md#r285--empty-sound-and-staff-roll-hooks-and-the-progress-destructor)

An ordinary scope and a compiler-generated global initializer can
have the same body. The initializer also emits a `.CRT$XCU` pointer.
Link both controls and check the full original startup table.
For the event service pulse, the pointer survives both linker
retention settings in the generated control and is absent from
the original PE. [Registration evidence](ORIGIN_PENDING_REVIEW.md#r290--event-service-pulse-and-startup-registration)

### x87 operand order

- The compiler orders x87 loads by expression shape. In `x = x * g` with a
  member `x` it loads `g` first; `x = (x) * g` loads the member first. A
  parenthesized operand, or a parenthesized dereference, is evaluated first.
  A bare dereference behaves like a plain member, and member-op-member keeps
  source order. When a converted float expression stops matching, try
  parenthesizing the operand the original loads first [004F4170, 00536400].
- `*(&a) + *(&b)` on float members keeps the original MOV/MOV/FLD/FADD order
  where a plain sum reorders the FLD; `(*(&p))*global` keeps FLD then FMUL
  (fighter research parents).
- `member + 20.0f` with a right-hand literal emits `FLD [member]` then
  `FADD [const]`; hoisting the constant into a variable loads it first.
- Float arguments passed by value add an `FLD/FSTP` pair. Some originals push
  the raw float bits with `MOV/PUSH` instead (sprite call 00453C80). The
  originals' source for that transport is not known; typed float lowering
  was tried in the 0050A580 parent and adds 329 instructions.

### Register rotation and joins

- At `/Od` the compiler reloads `this` from its stack slot for every member
  access and cycles the scratch register eax → ecx → edx → eax from one load
  to the next. The cycle continues across statements and at most joins.
- In the pinned VC7.1 back end the local scratch search reads its cursor
  at `108A7D0C` and advances it at `10776893`. The Meiling object
  comparison shows that the choice can carry across independent switch
  arms. Removing one real update in action 997 moves the first reload
  in the untouched action 998 from EDX to EAX. Compare the cursor
  before selection alongside the emitted register and follow the case
  entries through the jump table. [Meiling compiler trace and replay](GIANTS.md#2026-11-23--meiling-action-998-inherits-the-scratch-register-cursor)
- VC7.1 can allocate a condition's operands before removing an empty
  branch. Alice action `0x38D` consumes two register choices for its
  empty stage-3 path. Meiling's explicit in-progress stage path in
  997 restores the original EAX at action 998 with the original frame,
  calls, and exits. Both functions cold-replay exactly.
  [Measured controls and complete comparison](GIANTS.md#cross-check-with-alices-eliminated-stage-test)
- A complete object can have multiple independent joins with the same
  symptom. Suika's later startup frames in actions 918, 928 and 929
  restore three successive register choices. The first change exposes
  the second, and the second yields matching table offsets while 106
  instruction bytes still differ in 929. Compare the complete extent
  after each change. [Suika controls](GIANTS.md#2026-11-24--suikas-three-startup-joins-cold-replay-exactly)
- A sibling action can carry a continuation that compensates for an
  earlier mismatch in the new function. In Meiling's fighter Advance,
  restoring the stage-1 continuation in `0x186` fixes the entry of
  `0x187`. The borrowed stage-4 continuation in `0x190` then moves the
  first difference to `0x192`. Keep changes isolated and check the
  subsequent entries in the full switch.
  [Meiling fighter controls](GIANTS.md#2026-11-24--meilings-fighter-advance-cold-replays-exactly)
- The native dispatch can reveal repeated calls and distinct state
  bodies even when the decompiler flattens their control flow. Marisa
  object action 812 has 13 identical clear effects, and actions
  828–833 each dispatch to their own three-instruction call block.
  Match the call count and switch targets before comparing registers.
  [Marisa object replay](GIANTS.md#2026-11-24--marisas-object-advance-cold-replays-exactly)
- VC7.1's `/FAcs` listing ties otherwise identical epilogue jumps to
  source lines. In Reimu's object Advance, 59 direct jumps to the shared
  return had been routed through individual case tails. Explicit
  returns restore their destinations without changing instruction
  counts. Check the listing build's section and relocations against the
  ordinary object before using its line labels.
  [Reimu object comparison](GIANTS.md#2026-11-24--reimus-object-advance-cold-replays-exactly)
- An eliminated condition can change registers between two consecutive
  statements. Sakuya's explicit later startup frames in action 808
  restore the first reload for the bounds check after a matching
  counter increment. An empty floating-point boundary test at that
  position still emits its x87 comparison.
  [Sakuya controls](GIANTS.md#2026-11-24--sakuyas-arena-bounds-check-cold-replays-exactly)
- A register difference at an action entry can originate in the
  preceding action's completion path. Patchouli's `0x357` and
  `0x3E5` end with a completion check and two matching exits in both
  builds. Explicitly expressing the in-progress path in each restores
  the register choices at the next action entry.
  [Patchouli controls](GIANTS.md#2026-11-24--patchoulis-object-advance-cold-replays-exactly)
- A register change can shorten some instruction encodings and lengthen
  others. Yukari's explicit unfinished-animation path in 908 restores
  eleven instruction widths across the complete object. The matching
  body grows by three bytes with the same instruction count.
  [Yukari comparison](GIANTS.md#2026-11-24--yukaris-object-advance-cold-replays-exactly)
- When two actions have the same stage-change guard, compare the later
  join after correcting the earlier one. Youmu's explicit stage-14
  continuation in action 829 exposes the corresponding join in 906.
  Both changes together reproduce the full function and switch layout.
  [Youmu controls](GIANTS.md#2026-11-24--youmus-object-advance-cold-replays-exactly)
- Recheck similar growth and fade actions after the first register join
  is fixed. Alice's stage-3 hold also matches Yuyuko actions 911 and
  914. Before that pattern surfaced, the ongoing animation path in
  Yuyuko action 837 restored instruction widths and all dispatch offsets.
  [Yuyuko controls](GIANTS.md#2026-11-24--yuyukos-object-advance-cold-replays-exactly)
- An empty stage branch can affect register choices in later cases. In
  Remilia's fighter `Advance`, the preparation branch before the
  descent test in `0x2F0` restores the last 1,203 GPR operands after
  three earlier action joins are fixed. Confirm later cases before
  changing them individually.
  [Remilia controls](GIANTS.md#2026-11-24--remilias-fighter-advance-cold-replays-exactly)
- Track the first differing instruction alongside the byte count while
  recovering adjacent actions. Explicit late landing frames in Youmu's
  `0x5D` move the first difference into `0x5E` even as a width change
  nearly doubles the total. The matching path in `0x5E` recovers the
  affected action.
  [Youmu fighter controls](GIANTS.md#2026-11-24--youmus-fighter-advance-cold-replays-exactly)
- When instruction alignment is lost, pair action bodies through their
  jump-table entries. Reimu's eight consecutive special actions expose
  an inverted firing guard, skipped per-projectile field writes, and
  x87 operand order differences. Fixing those actions restores global
  instruction alignment and lets the launch continuation be tested.
  [Reimu comparison](GIANTS.md#2026-11-24--reimus-fighter-advance-cold-replays-exactly)
- Repeated actions can each need the same continuation branch. In
  Sakuya's fighter `Advance`, expressing the repeat limit in `0x1F8`
  and `0x1F9` affects thousands of later operands. Applying the same
  path at the corresponding join in `0x1FA` closes the entire function.
  [Sakuya fighter controls](GIANTS.md#2026-11-24--sakuyas-fighter-advance-cold-replays-exactly)
- `/ZI` (Edit and Continue) restarts the cycle at every statement but changes
  thousands of other instructions, so it is not the originals' setting. `/Z7`,
  `/RTC1`, `/Oy-` and `/GX` do not affect the cycle.

- Marisa action `0x208` separates two ways to express the drift guard.
  Combining the update with a short-circuit condition preserves the GPR
  difference. Expressing the later frames of stage 6 before the drift
  begins restores EAX after `AdvanceNestedFrame`. A control with an
  extra x87 comparison emits 14 additional bytes.
  [Marisa fighter controls](GIANTS.md#2026-11-24--marisas-fighter-advance-cold-replays-exactly)

- Alice and Marisa have the same emitted bounce body in action `0x59`.
  Alice's following entries match when the continuation is expressed
  in `0x5E`, at the frame after its speed reset. Transferring Marisa's
  continuation in `0x59` preserves the bounce bytes but changes the next
  two action entries. [Alice's paired comparisons](GIANTS.md#2026-11-24--alices-fighter-advance-cold-replays-exactly)

- In Patchouli's fighter `Advance`, the startup continuation in
  `0x2BC` affects the register used after the next call within the same
  action. The landing continuation in `0x5E` affects the next case entry.
  Compare the first register mismatch with both the preceding condition
  and the preceding action before rewriting the differing instruction.
  [Patchouli's complete comparison](GIANTS.md#2026-11-24--patchoulis-fighter-advance-cold-replays-exactly)

### Conditions and loops

- Yukari's `0x19F` has a stage gate and an x87 comparison with no
  status-word read before the next source condition. The decompiled
  case omits that guard. The instruction interval between contact and
  firing provides the evidence needed to restore it.
  [Yukari's complete comparison](GIANTS.md#2026-11-24--yukaris-fighter-advance-cold-replays-exactly)

- In Suika's `0x2EF`, the three-shot and two-shot loops are allocated
  consecutive locals in emitted block order. The signed difficulty
  test puts the three-shot arm first. Check both loop counts and their
  stack slots when a decompiler reverses the arms.
  [Suika's complete comparison](GIANTS.md#2026-11-24--suikas-fighter-advance-cold-replays-exactly)

- The compiler keeps comparison constants literally: `i < 37` emits
  `cmp 37 / jge`, while an original `cmp 36 / jg` needs `i <= 36`.
- An unsigned `Count() <= 0` emits `ja`; `Count() == 0` emits `jne`.
- The fall-through branch of an `if` is the first block in the code. To
  reproduce `cmp scale,1; je rotated; …; jp rotated`, write
  `scale != 1 && angle == 0` with the unrotated path first (sprite drawing
  0040D2E0).
- `for (; it != end; ++it) (*it)->Dispatch();` keeps the iterator update at
  the loop end; the `while` form with a named element local adds a slot and
  two bytes.
- A combined short-circuit guard plus `switch (member)` reproduces the
  giants' dispatch prologue; copying the action into an `int` local first
  adds a slot.

### Stack slots and locals

- Local slot order follows declaration and scope, not use. When locals land
  in the wrong slots, reconstruct the original lifetime graph (which
  temporaries live in which nested scopes) instead of renaming variables.
  Scoped lifetimes fixed the 0x24-byte frame of the config reader F259 and
  the quad/RECT order of the scene renderer (outer quad, inner RECT).
- In Yuyuko fighter action `0x303`, three countdown branches each use a
  counter across two loops. Declaring each counter inside its own branch
  recovers all three native offsets after reordering the case-level
  declarations failed. [Yuyuko fighter comparison](GIANTS.md#2026-11-24--yuyukos-fighter-advance-cold-replays-exactly)
- Variable names can change slot assignment, but a name sweep without a
  lifetime model rarely converges.
- Passing a typed null pointer rvalue to a `T* const&` parameter creates the
  original's temporary slot; a named `empty` local does not [F294].
- Root-scope resources and const-reference construction values recover the
  WinMain frame (00602A60, F1171).

### Allocation and deletion

- A CRT destination does not identify the source call: 0064169D and
  00640F15 are bound to scalar and array delete as well as `free`. Pair each
  deallocation with its allocation. `delete[]` of `new char[]` names and
  scalar `delete` of objects fixed the slot rotation in the ArchiveCatalog
  destructor 0041CE50 and the BattleScene destructor 0043B0B0, where `free`
  with named cleanup locals rotated the temporaries.
- A true C++ array of objects with constructors under `/GX` emits
  `_ehvec_ctor` (00641C78) and its unwind entries.

### Integer widths and immediates

- `++shortMember` emits a 16-bit `mov/add`; promoting through an `int`
  temporary emits `movsx`.
- `PUSH 0xFF` (five bytes) comes from an unsigned char 255 argument;
  `PUSH -1` (two bytes) from a signed -1. Match the callee's declared
  parameter type.
- A byte array local triggers a `/GS` cookie that a DWORD array does not
  (audio stream queue 00407A50).
- `reinterpret_cast<signed short&>(m)` on a `short` member is a no-op.

## Conversion pitfalls

- A parameter named like a member shadows it (`BindOpponent` compiled to
  `opponent = opponent`); the replay caught it.
- VC7 `$L`/`$SG` label counters change with unrelated source text, so the
  comparator checks local labels by destination, not name.
- Calls to a base implementation through a cast must be qualified
  (`Fighter::ResetRound()`) to stay direct calls.
- Converting a file is proven by building it before and after and comparing
  every code section and relocation (`.analysis/layout-tools/objsig.py`,
  with a rename map for changed symbols), then cold-replaying the affected
  units.
