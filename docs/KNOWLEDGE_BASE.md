# TH075 reconstruction knowledge index

Current validation policy (2026-10-28): prioritize exact function reconstruction.
Target identity, complete extents, all relocations, truthful origins and affected
unit cold replay remain the acceptance evidence. The default CI now runs only
the small exact/checkpoint/byte-accounting suite. Per-function robustness tests,
duplicate source/native assertions, hard-coded progress counts and full historical
test runs are not required. Historical test counts below describe past runs;
consult AGENTS.md and RE_WORKFLOW.md for current requirements.

Updated 2026-10-27: the user resumed reconstruction. F184 added two
canonical cold-exact input policies (+538 CODE bytes / 46 relocation fields);
F185 added the 1,273-byte title core state machine plus an owned 40-byte
switch table and 76 relocation fields, all cold exact.
F186 added a separate 951-byte options scene controller, seven-case owned
28-byte switch table and 70 relocations, also fully cold exact.
F187 added the 339-byte Win32 config writer and its 27 actual fields with
independent canonical cold comparison.
F188 adds the options text-resource update with 563 CODE bytes, seven-case
owned table, 34 fields, and natural EH/new/delete path, all cold exact.
F190 adds 604 exact graphics default-state bytes and all 45 relocations.
F191 adds the complete 860-byte music-detail font/texture workflow, all 25
actual relocation fields cold-exact.
F192 accepts the 31-byte authored scene-base cleanup; the 34-byte
source-indistinguishable paired constructor remains R108 unknown/uncredited.
F193 cold-accepts the 531-byte shared game-defaults initializer with all
71 actual relocations and eleven character-name copies.
F194 cold-accepts its 339-byte config.ini reader with all 27 import/global
fields, without granting borrowed storage or generated-source credit.
F195 closes the shared global lifetime with 358 exact authored bytes and
all 18 fields, using only borrowed destructor receiver interfaces.
F196 cold-replays the previously pending 922-byte battle-scene constructor
with the native five-state EH flow and all 40 relocation fields exact.
The F189 'unaccepted' status is historical.
F197 independently cross-verifies the same base8/texture80 physical
contract in the 435-byte title constructor (two EH states, 18 fields), exact.
F198 cold-accepts the 177-byte texture manager constructor and 128-byte
resource-slot initializer, all 20 actual fields; natural five- and one-state
EH policies preserved.
F199 cold-accepts the complete 434-byte texture-manager destructor after
preserving the native COM Release result store; 23 fields verified.
F201 cold-accepts the separately reviewed 904-byte game-mode snapshot
writer, preserving all 131 actual relocations and four game-mode branches.
F202 cold-accepts the reciprocal 880-byte snapshot restoration and its
129 actual fields; an extra unregistered dirty source is preserved privately
and never counted twice.
F203 cold-accepts the 671-byte progress selection with two owned 20-byte
switch tables and all 56 relocations exact (711 compared bytes).
F204 cold-accepts the 318-byte wave track selector (22 fields); F205
cold-accepts the 27-byte transition fade call wrapper (one field).
F206 cold-accepts the complete 727-byte bitmap directory loader with
29 fields and original STL iterator erase on the failed-load path.
F207 independently cold-accepts the 575-byte alternate-format bitmap
directory loader with all 23 fields and the same native iterator lifetime.
F211 cold-accepts the 305-byte sprite rectangle-to-quad constructor
with all nine fields: four distinct 16-byte vertex members recreate
the native compiler call sequence, unlike an array.
F212 cold-accepts the 334-byte global audio/input startup policy
with three-stage EH, all 29 physical relocation fields and real
120/8/20-byte allocations.
F213 cold-accepts two progress record policies, 109 and 90 bytes,
both relocation-free; F214 cold-accepts the complete 910-byte progress
defaults and all 34 actual relocations.
F217 cold-accepts two authentic archive lookup/seek functions (113
and 180 bytes; 19 actual fields), while the paired 792-byte record
loader and 916-byte music catalog remain nonexact private probes.
F218 cold-accepts the 225-byte replay capture, 85-byte snapshot
header read and 89-byte available-path search, 15 real relocations.
The 375-byte replay file finalizer remains a nonexact research target.
F220 cold-accepts two replay queue policies: 67 bytes of four-queue
clearing (four relocations) and 35 bytes of primary queue emptiness
(one relocation). The 1,252-byte appended record writer remains
unaccepted after fully sized natural for-loop compiler controls.
F221 cold-accepts the 569-byte character-selection reset with 11
relocations; F222 cold-accepts the 780-byte Marisa round reset
with 3 real fields, signed native x87 and 74 animation records.
F189 was an earlier noncredit investigation superseded by F196 exact.
The original H184 handoff was historical and is superseded by the current
request. Earlier experiments and names remain hypotheses until tested.
See the current [handoff](RE_HANDOFF.md) for current status.

## Authoritative state

- Supplied Japanese th075.exe 1.11, SHA-256
  `bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
  Archive identity is pinned; official distribution provenance is uncorroborated.
- **534 exact functions/units, 766,591 CODE bytes, 204 canonical objects,
  309 accepted source-header inputs.** Reviewed coverage is 38.84%; conservative
  coverage is 38.77%, including all 97 unknown origins/3,608 pending bytes.
- Ownership, source presence, names, Ghidra types, compilation and reproducible
  exactness remain distinct. Read ledgers and relevant origin evidence before
  relying on any classification or provisional boundary.
- CODE size determines credit; comparisons also include owned tables/remaps.
  Only full canonical cold replay earns credit. Preserve evidence through R268
  and every pending byte in the conservative denominator.
- Original names and complete layouts remain provisional. Never instantiate or
  embed partial owners. The known complete 132-byte packet and SDK RECT16 may
  be instantiated; borrowed scene/drawing/manager views may not.

## Recent reproducible observations

F179..F183 added 16 exact units/9,888 CODE bytes across five pushed commits.
Each new unit passed full native extent/CFG/field review and canonical cold
comparison. Only new units were rebuilt. Each cohort passed 3,612 CI tests;
old canonical inputs, origins and protected evidence stayed unchanged.

| Cohort | Accepted result | Useful observation |
| --- | --- | --- |
| F179 | Background 435A70, 6,404 bytes/235 fields | Genuine two-side tint array and borrowed float windows reproduce native stack/x87/call behavior. |
| F180 | Eleven callbacks, 463 bytes/2 fields | Keep signed counters, strict 2500.0 versus inclusive 15360.0 double thresholds, reverse 3840 wrap and separate 72-frame cycle. |
| F181 | Timed sprite 451A00, 446 bytes/18 fields | cameraX bucket9 to cameraHorizontal bucket12 fixes real X allocation; the old same-bucket control stays closed. |
| F182 | Two name-entry policies, 1,486 bytes/76 fields | Keep actual 72-byte player spacing, signed repeat/modulo6, short INC/DEC, bounds/reset and extra shared toggle. |
| F183 | Title rendering 43A7A0, 1,089 bytes/26 fields | Measured real-local names yield packet-88/RECT-98/index-9C; retain ten stripe/item transforms and native color packing. |

F179's observed float windows cover 0x98..0xBC and 0xCC..0xDC without guessed padding or
owner instances. Member expression treatment changes while actual field widths,
operations and ABI remain. R163 sine 40D940 stays unknown; its existing
float(float)/ST0 view was unchanged. F181 adds no local, scope, type, layout,
precision or ABI workaround; CodeView and complete comparison verify the slots.

Every emitted readonly section and all definitions were checked where used.
No helper/data credit was added. D3DCOLOR masks express actual color semantics;
they are never comparison masks. Source patterns or mapped names alone prove
neither ownership nor exactness.

## F184: cold-accepted input policies

| Function | Native/emitted bytes | Returns / branches | Fields | Differences |
| --- | --- | --- | --- | --- |
| R043 43ABF0 title input | 228 / 228 | 1 / 9 | 19 | 0 |
| R053 429DC0 replay/shared input | 310 / 310 | 1 / 16 | 27 | 0 |

Both full extents have plain RET, no tables and verified alignment; all 18 calls
reuse canonical input/window helpers. Two separate pointer-only synthetic scene
views were compiled anew and registered with all 46 real relocation fields.
The canonical cold replay of both complete extents passed with zero differences.
Keep DWORD versus byte stores, independent direction checks, confirm/cancel,
Escape counter and actual chord placement. Reuse the existing mappings/counts.

The frozen original H184 preview source/object and resumption seed remain
historical evidence and were not reclassified as cold-built canonical objects.
The distinct F184 public source and one fresh canonical object are accepted;
full layouts/names remain unknown.

## F185: title-scene state-machine exactness

The independently measured target 0043A270 has 1,273 CODE bytes and an
immediately following 40-byte owned ten-case switch table. The entire
1,313-byte extent (76 relocation fields, including 11 local jump-table
references) cold-replays byte-for-byte from natural VC7.1 C++, using a genuine
single shared loop-local index and signed attract-mode state. Complete loop,
dispatch, exit and timed attract branches were retained; no cropped table,
comparison mask, padding, fabricated returns, assembly, or fake owner
instantiation was introduced. Native code SHA256:
`f528f379b927bad808eaa0703fa48c798fb8998bbae44ca9a2c96264215928a7`.
Owned table SHA256:
`01b9780b16a3176977d6c14d930d0eb42e860439a880b82435248b8459770254`.

Before success, the natural first probe was 1,312 bytes total (1272 CODE +
40 data) and mismatched the signed flag and time-branch layout. Its retained
variants record the alternative and allow independent replication. Inverting
the terminal time condition into a true attract-mode block reproduced the
native long `jbe` to the tail; changing the attribute to signed matched native
`movsx`. Reversing the ten-item alpha conditional matched the target's
separate highlighted-item store and decay/clear branches. A private duplicate
unit alias was identified and removed after verifying exact equivalence to
the registered unit, restoring exact unit↔ledger 1:1 correspondence and a
new automated check. Full owner layout, names and some global semantic roles
remain conjectural.

## F186: options-scene control-flow and volume policy

R066 00428F00 is 951 CODE bytes with the exact following 28-byte owned switch
table. Native body SHA256
`21e698c0f26cbca4c23286883c7de9a04cf91b1825c1090dfa320b09956f75fa`;
switch table SHA256
`f84e9f643843fc0db5c9ce2278848b8224a99bb915d32538e7d99646afd4f124`.
Independent x86 decoding yielded 269 complete instructions and one plain
RET. VC7.1 cold-compiles the full 979-byte comparison extent, zero byte
differences after all 70 actual relocations (eight local switch labels) are
replayed and verified.

The first valid source probe using `!g_Flag` generated a 982-byte comparison
block and three 8-bit SBB/INC pairs; the target used 32-bit SBB/INC.
`flag = 1 - (flag != 0)` generated 1001 bytes, while both
`static_cast<unsigned int>(flag == 0)` and the natural
`flag = flag ? 0 : 1` yielded zero structural differences across their
complete 979-byte blocks. The last expression was adopted because it retains
simple semantics without a cast chosen to force codegen. Full relocation
replay and canonical cold build then yielded exact, not merely a masked
structural match.

The signed two-axis input, signed-short menu index and sample timer,
modulo-four display selection, three toggles, signed volume adjustments,
explicit audio/stream refreshes, options materialization dependency
00429F00, configuration write helper 00419450, fade and 0x2202/9 returns
were preserved. The referenced callee 00429F00 has independent complexity and
no source/exact credit yet. No owner layout, source class identity, data
ownership or ABI beyond this method is inferred.

## F187: Win32 configuration writer with authentic stack slots

R052 00419450's full 339-byte native body has 116 Capstone-decoded
instructions and plain RET followed by alignment. The natural Win32
`CreateFileA("config.ini")`/`SetFilePointer`/eleven `WriteFile`/
`CloseHandle` sequence cold-compiles exact after all 27 physical DIR32
relocations. The filename literal at 00657A70 in the pinned target is the
exact ASCII `config.ini\0`; it is a source string, not newly credited target
data. All 80-byte bulk settings and ten 1-byte fields are written in the
original observed order, including the single setting explicitly set to 1
*after* writing its persisted value. Original full storage owner is unknown.

The first 339-byte probe with `HANDLE file` declared before `DWORD written`
failed 26 nonrelocation comparisons, entirely due to swapped real EBP slots.
The reversed natural declaration order keeps 339 bytes and matches all
register/stack references. The final namespace shares the already canonical
F186 `OptionsSettingsF186::SaveConfiguration` call target 00419450; F186
was neither edited nor unnecessarily rebuilt. No IAT, literal, or global data
bytes were added to authored-code credit. The native CODE SHA256 is
`4d1027f88999c9085d95ab8c24338439ad7fb2eaf122ac8b6c9f60065fa2d940`.

## F188: EH-backed options font/texture pipeline

The independent native `0x00429F00` body is 563 CODE bytes (137 complete
x86 instructions) and its immediately following switch table is 28 bytes.
Source `src/OptionsSelectionF188.cpp` cold-replays **all 591 bytes** and all
34 COFF fields, including one same-section table pointer plus seven local
case labels. Code SHA256:
`65e7c664f6846ac95a8085eeb2bba5eab32f5ad2c272cb3d2dfa049ad8e2d759`.
Table SHA256:
`3bab5fa7d3230c10ba3afdd6140cc4ddd35837b701713cbff1d0156ffe9a64b2`.

Pinned VC7.1 `/GX` (not `/GX-`) reproduces the native EH frame, cookie and
original allocation/cleanup shape. Native evidence independently anchors
`operator new(0x38)`, the constructor and destructor targets, a
D3D8 `IDirect3DTexture8::LockRect`/UnlockRect pair, a font setup/rasterizer
pair, and the original seven message strings. All 34 actual relocations were
replayed. The EH handler at `0x006558BD` and cleanup code at `0x006558AF`
were inspected as dependencies but earn no separate exact byte credit.

Controls show the 512-byte nominal buffer variant displaces meaningful
stack slots by eight bytes; natural 500/504-byte variants both recreate the
same stack shape, so the precise original declaration length is unknown.
The original function sign-extends the option index; an explicit signed
comparison changes MOVZX to the observed MOVSX without changing the F186
caller ABI. The offset-check typedef control changes VC7 local-label symbol
numbers without changing body semantics; it was not promoted. The ephemeral
56-byte glyph object has physically reviewed total size and supported access
offsets, but one +0x18 word is unobserved and the original class layout and
semantics remain provisional. Do not reuse that allocation carrier elsewhere
or claim a complete original font owner. No manual EH bytes, assembly,
comparison masks, fabricated returns, cropped tables, or other code/data
credits were introduced.

## F190: graphics device default-state initialization

The 604-byte native `Graphics::SetDefaultStates` at 00401540 (178 full x86
instructions, ordinary RET and four following INT3) has SHA256
`d5cff4b102acaa874856d80ff21fd09dcd624731c4775e81d6ea00f4c3d74bac`.
Native Ghidra read-back and independently decoded vtable slots agree with
pinned D3D8/Direct3D8 SDK calls. Natural VC7.1 /GX- source reconstructs the
**whole 604 bytes** with **45 actual DIR32/REL32 fields** after a cold build.

The source uses the actual IDirect3DDevice8 methods to set render/texture
stage states, FVF 0x144, and an optional pixel shader. D3DXAssembleShader
uses the measured source anchor (and `strlen`) and returns a D3DXBUFFER
used to create a pixel shader. Float constants 0.3f, 0.59f, 0.11f and 1.0f
are stored at the target stack offsets before `SetPixelShaderConstant`.
No source, data or exact credit is asserted for the linked D3DX assembler.
The first probe emitted 603 vs 604 bytes: the native device-null check
uses a short conditional to skip an unconditional branch. A semantically
equivalent explicit early return produced this exact layout without fake
locals or padding, then passed full cold replay.

## F189: independently reviewed but unaccepted battle initializer

Historical (superseded by F196 cold exact): the complete
`BattleScene::Initialize` at `0x0043AD10` is 922 code bytes,
230 decoded instructions and one RET. It creates multiple owned subobjects
through four distinct allocation sizes (0x50, 1, 0x14, 0x14) and uses
exception-state transitions. The original full class layouts, nested
ownership, EH unwind and constructor semantics are not established merely by
a Ghidra decompilation or the observed allocation sizes. Preserve the
noncredit native proof in `.analysis/f189-battle-init/`; do not construct
fabricated complete owners or grant exact coverage until a complete natural
source and all relocations cold-replay.

## F191: exact large music-room text and rasterizer pipeline

`MusicRoomScene::RenderSelectedDetails` at 00426A70 has **860 native CODE
bytes, 217 decoded instructions and a RET 4**. The body SHA256 is
`ea9d870e0edd790fe014a723f6a6466ff5867dec44fda5dee483ea856452b7ae`.
Pinned VC7.1 `/GX` cold replay emitted every byte and all **25 actual COFF
relocations** exactly. The two target D3D8 texture lock cycles each construct,
configure, render with and destroy a transient 56-byte GDI font resource.
The real typed 16-byte stride is shared by the selected track's description,
title and artist references; fallbacks and format strings point to original
target data but do not receive source/data exact credit.

Early natural-source prototypes already emitted the correct 860-byte function
size but differed in the two signed track-bound checks. In the emitted x86,
placing the bound on the left of the comparison selects the target's
count-first MOVSX/CMP and JG control flow; using `selected >= count` shifts
register allocation/branch order despite semantic equivalence. Buffer sizes
1996 and 2000 yield identical structural-exact native output, while 2004
and 2008 shift stack offsets and lose equality. The chosen source uses
`char message[2000]` solely as a reproducing, meaningful text buffer;
the original nominal size is not inferred. Borrowed glyph class identity,
+0x18 allocation word semantics, music room's full layout, EH helper
ownership and data literals remain unproven. The complete function is
accepted, not its dependencies or source-level class identity.

## F192: separate authored scene cleanup from origin-unknown constructor

The 31-byte R062 `0x00431F40` is independently authored game-scene cleanup:
the pointer-only destructor source stores the real base vtable anchor
`0x00657B88`, then invokes `0x00417430` on the existing this+4 defaults
receiver. Both relocation fields and the entire native extent cold-replay
exact. Native SHA256
`f0fdc9015cffb6b7194ee2641a8018c52eb7a984d6a68d1f9e8c809b77698cf9`.
No complete original scene/config-owner declaration or instantiation is
introduced.

The adjacent 34-byte R108 `0x004251C0` base constructor was independently
decoded and compiled in a separate private complete probe (two actual fields,
zero non-relocation differences). Its native SHA256 is
`9ff723978ea0aa946f4147ff70aef987da9b3dbd431196873a7dc4fa331eb85f`.
But that evidence cannot distinguish authored source from an implicit
compiler constructor. Both source routes generate the same bytes, and the
original reviewed origin is `unknown`. It therefore stays wholly uncredited
without editing the origin ledger, adding an implemented row or claiming an
exact unit. The private probe and evidence remain under
`.analysis/f192-scene-base/`, and the function remains within all 97 pending
origins and their 3,608 code bytes. This demonstrates the difference between
byte reproduction and proof of original ownership.

## F193: game-global constructor and default settings

`GameGlobals::Initialize` at `0x00417210` is 531 CODE bytes, 92 decoded
instructions, an ordinary return and INT3 alignment. Body SHA256:
`45043cd59354a3a3d1d5525d2c44233786e44e3cbfded0b2c45cd5dbc3a4f7b3`.
Pinned VC7.1 `/Od /Ob0 /Gy /GR- /GX- /GS /Zi` compiled the entire
body byte-for-byte on the first complete natural constructor probe.
All 71 actual DIR32/REL32 fields were registered and cold-replayed.
The source stores the observed keymap words and bytes, initializes
two player slots, copies all eleven original character IDs through
CRT `strcpy` to 20-byte-spaced destinations, sets options and byte
defaults, then invokes the config.ini read helper and increments the
first-use counter. Its double assignment at 00671438 reflects two
observed native stores, not proof of original variable names.
External anchors are borrowed and unsized; no data allocations, SDK
or helper byte credit are introduced. The R108 base constructor
`0x004251C0` that invokes this function remains unknown-origin and
uncredited regardless of its independent structural matching probe.

## F194: exact Win32 config.ini load

The authored reader `GameConfig::LoadIni` at `0x004192F0` contains
339 native bytes, 116 complete x86 instructions, one ordinary RET,
and 27 actual DIR32 relocations. Native SHA256:
`5a76d9c05e369ba111429f3160678f7cd068acbf2942f27f85afcf258dbab4df`.
VC7.1 cold replay reproduces all 339 bytes. It opens the observed
config.ini literal for read, seeks to the beginning, reads the
80-byte config region then ten separate byte settings via ReadFile,
normalizes one byte after its read and closes the handle. This is the
actual source-compatible callee bound from F193.

A correct-length first candidate nevertheless differed in 26 local stack
references: HANDLE at EBP-4 instead of EBP-8, and DWORD byte count in
the other slot. Simply swapping declaration order did not fix it.
Experimenting with meaningful local identifiers changed VC7.1's slot
assignment without adding an artificial local, forced casts or code.
The final normal `readSize` declaration reproduces the original
EBP-8/EBP-4 frame. Exact emitted stack byte layout does not establish
the original identifiers. No Win32 import, source data or static filename
credits accompany this authored function.

## F195: complete shared global shutdown

The reviewed authored `GameGlobals::Release` at 0x00417430 is 358 native
CODE bytes, 99 complete x86 instructions, one normal RET and 18 actual
COFF relocation fields. Native SHA256:
`238163545e5867e5869753fed589643a52634d8107f9fe11486a58a42bd6016b`.
The first normal pointer-only VC7.1 /GX- source compiled to 358 bytes
with all 286 non-relocation bytes identical; fresh cold replay confirmed
all 358 bytes and 18 fields exact. The function retains its native shared
use-count guard, two virtual slot-5 destructor calls and one virtual
slot-0 destructor, three null stores, streaming audio clear, and
three physically distinct compiler scalar-deleting destructor calls.
None of the emitted destructor receiver interfaces is constructed or
embedded; they are only borrowed pointer declarations. The compiler
helper bodies, global data and named class identities receive no
independent credit. This completes the authored release policy, not the
origin-unknown base constructor or the full scene object layouts.

## F196: complete EH-backed battle-scene constructor

The complete reviewed R041 battle-scene constructor `0x0043AD10`
was independently decoded: 922 native CODE bytes, 230 instructions,
RET and INT3, target SHA256
`10d1747c1b0b512f21e4b2cef06c1d00a291e05f0181d19261563e785959d75e`.
A fresh, natural VC7.1 `/GX` constructor source matches the entire
922-byte function and all 40 actual COFF DIR32/REL32 relocations.
The observed EH handler is `00655B74`. Unmodified R020 original
EH metadata proves five states (base + four transient allocations)
and native unwinds `00655B40/48/53/5E/69`. The generated helper
sections remain independent library/compiler evidence without
source or exact-byte credit.

The original source-level complete scene class cannot be inferred from
this isolated constructor. Its source-compatible derived receiver
models only a physically observed base boundary, and is not allocated
or used as a complete owner. The four **native and reproduced allocation
sizes** are 80, 1, 20 and 20 bytes. The texture manager's 80-byte
allocation is supported by its actual constructor: eight-byte
root, three 16-byte vector components at offsets 8/24/40,
a 20-byte deque at 56 and byte at 76, rounded by native alignment.
The empty digit-atlas object has a natural size of one byte and its
known global-only F177 constructor. The two 20-byte combo counter
carriers cover physically observed F173 constructor/member fields.
All their constructor calls, texture resolution and parameter evaluation
order are byte-exact. Original container element types, texture
root word at +0, field names and complete nominal object identities
remain uncertain. The source intentionally credits only the 922
authored bytes; its 40 relocs bind real existing callee/data/SDK
addresses without adopting them. R108 `004251C0` base ctor stays
unknown-origin and no exact credit despite its structurally exact
private source. F189's original native-only investigation is now
superseded for this function by a complete accepted unit, not deleted.

## F197: complete title initialization with independent EH comparison

Target `TitleScene::Initialize` at 0x0043A020 is 435 native CODE bytes,
116 whole instructions, one RET and 18 actual COFF fields. Native SHA256:
`e4c04d16c30c718c2504e389a945d902b5766e687aa45e40123f3e5c8fb5b573`.
A natural /GX source built in a fresh standalone object cold-replays
every byte and field. The original EH handler `0x00655B23` carries
two states with native cleanup addresses 655B10/18, independently
reviewed under immutable R020. Physical source-compatible subobjects
match the separate F196 battle construction: base size8, shared
texture owner size80. The title path has one new(80), rather than
battle's four new's, and reproduces its two timeGetTime calls,
four-slot texture allocation, title asset load, ten menu alpha
stores, user selection and initial shared player state.

The emitted derived constructor is a *call-only receiver view*, never
allocated as a complete TitleScene; original full nominal class layout
and STL container element types are unproved. No compiler EH helper,
vtable, CRT, data or borrowed source receives exact byte credit.
R108 base ctor retains unknown origin; its exact relocation in
these callers cannot be used to reclassify it.

## F198: exact texture-manager constructor and resource slots

The authored TextureManager ctor at 0x0040AD80 contains 177 native CODE
bytes (48 full instructions) and 12 real COFF fields; SHA256
`e0ce84473c5b407a441c88fc5c7485a47547ad48e39abadf4beedd1d41cbf37a`.
Its complete five-state EH frame is independently in the original
R020 metadata, handler 00654ED4. A natural C++ constructor with
nontrivial member ctors at offsets 0/8/24/40/56 reproduces the exact
emitted stack, EH transitions, real reset call order and byte/state
stores. The physical size80 receiver agrees with independent
F196/F197 new(80) callers. Complete native cold replay is exact.

TextureManager::AllocateUnformattedSlots at 0x0040B1D0 is 128 bytes,
37 instructions and eight actual COFF fields, SHA256
`570580110f4777092fba3bb6ca93d760abb364c5dea46998a42e07ad0ed6cac4`.
A true 44-byte automatic temporary with VC7.1 ctor/dtor naturally
produces the one-state EH lifetime and 0x34 stack frame, and two
resource vector operations pass the original count/entry and local
zero value. It also cold-replays exact. Neither source allocates
an original TextureManager via unknown complete class size elsewhere;
this is a source-compatible physical lifetime model only.
Full original class names, component element types and some root
member semantics are unproven. No STL/template, helper, EH data or
other dependency byte credit was granted. The bigger manager
release at 0040AE40 and scene destruction remain open.

## F199: complete destructor and original COM result semantics

The independently authored texture-manager destructor 0x0040AE40 consists
of 434 native CODE bytes, 135 decoded instructions and 23 real relocation
fields; SHA256
`ae20b89ac58429797e1de78f18c5419a216567af8fc3ca11da18c837a14cc3f8`.
A natural /GX source using the physically observed 80-byte allocator carrier
recreates five native EH cleanup states, two pointer-vector traversal loops,
COM resource release, nulling/clearing, and reverse member destruction.
An earlier 431-byte probe dropped the COM Release() result, unlike
the target instruction that stores its `ULONG` return to a stack-local
reference count. Capturing that actual reference count yields the native
0x1C stack allocation and 434-byte body without padding or fabricated
control flow. Fresh cold replay proves all 434 bytes and 23 actual COFF
fields. The source does not establish original STL element types, nominal
original class name, SDK or EH helper authorship, or complete data ownership.

## F201: complete mode-aware game-state snapshot persistence

The reviewed authored native `GameState::SaveSnapshot` at 0x00419920 is
904 CODE bytes, 163 whole instructions, ordinary RET/INT3 and 131 actual
DIR32 relocation fields. Body SHA256:
`23b03c8ccd1fd456027c2536ec3842fdc31cdc7dcb18d140d3ba808f19ad53ad`.
Its legitimate source and unit had been left as uncommitted worktree edits;
they were explicitly read, audited and independently cold-replayed with
F199, not discarded or accepted on historical notes alone. All 904/904
bytes and 131 fields matched again. Four original game modes (1, 2,
4 and 3) copy the real source player, opponent, settings, side/stage
bytes and branch-specific live actor fields to their observed destination
offsets. Destination/source declarations are borrowed byte and DWORD
address views; they do not assert a complete original savegame structure,
buffer extent, type identity or independent global data code credits.
Only the 904 reviewed authored bytes receive new exact credit.

## F202: exact complete snapshot restore, independently replayed

`GameState::RestoreFromSnapshot` at `0x004195B0`: 880 authored
CODE bytes, 163 x86 instructions and 129 actual DIR32/REL32 fields,
original SHA256
`20b5cc4a2deae989f5c72cee1bd0fd27eea7c9be6abdc020b7a82d0156981c17`.
The first full natural VC7.1 /GX- C++ source emitted every byte and
relocation, verified by independent cold replay. Native saved-mode
checks, player and opposing-player updates, record count increments
and genuine archive helper calls are reproduced in their observed
order. No complete source record class or data-owner extent claimed.
Combined with F201 save, this pair now accounts for 1,784 exact
CODE bytes and 260 native relocation fields.

A second, unregistered public source file appeared in the worktree
during registration. It was examined, byte-compared to an identical
older ignored source and preserved byte-for-byte at
`.analysis/f202-snapshot-restore/UnadoptedAlternative-GameRestoreF202.cpp`
(SHA256
`280a70998f702d7529a9879d8a0083e68b488f2d7fa833c594f7bce7d0fd47c1`),
rather than accepted as another function. The canonical source
`src/GameStateRestoreF202.cpp` (SHA256
`912672914ecd95390aecd06a8f8db9ddf80af74f5c4f591805f36888cdfccecc`)
remains the only new source for this unit. Original names, source
ownership and R108 base constructor classification remain provisional.

## F203: exact switch-backed progress completion policy

The authored `GameProgress::CheckSelectionAt00419E10` has 671 native CODE
bytes and two contiguous original five-entry jump tables totaling 40 bytes.
The pinned target contains 202 decoded native instructions with body SHA256
`997d651510426c6dbac11ce4a66f06e2ab20505bcdcf71c3808f026295031b3d`,
and the owned 40-byte table SHA256
`519277b311148216fcb966bd52b680855633a07c101494aa1a2a88fa31588d55`.
Fresh VC7.1 /GX- source cold-replays **711/711 compared bytes** with all
**56 actual COFF relocations** (46 inside code, ten owned table label
words). CODE credit is limited to 671 bytes.

The natural source has signed char selector inputs, unsigned byte result,
two separate switch policies, nonshortcircuit bitwise OR/AND combinations
of the original progress archive queries and two six-element loops.
The target queries progress records through an *uninstantiated borrowed*
`0x006718F8` receiver with callee `0x00416DC0`, not a guessed complete
game record owner. Initial compound assignment source gave correct size
but wrong intermediate register evaluation order, 250/487 comparable bytes.
Explicit ordinary accumulator expressions load the old flag before
evaluating query calls and reproduce the exact EBX/ESI/EDX sequence.
No fake results, padding, shortened switch table or borrowed helper/data
credit were introduced.

## F204/F205: exact music track selection and fade policy

The authored `Music::PlayTrackByIndex` at 0x00419CB0 is exactly 318
CODE bytes, 94 original instructions and 22 actual DIR32/REL32 fields.
Native SHA256
`9ac546b2bca59fe1e3e3d807574400f6bb324c14e0db8e758390a0316d174d88`.
The source handles negative indices, the three ordinary groups of
ten WAV filenames, the two special opening/ending cases, default
format, archive stream category and progress recording only in
permitted clock modes. The first compiler probe's nominal 132-byte
buffer produced nine stack-offset byte differences. Natural 124/128
byte controls emitted the target 0x88 stack frame and each matched
all 230 non-relocation bytes; the 128-byte source was adopted but
the original nominal declaration length remains uncertain.
Pinned /GX- cold replay independently verified all 318 bytes and
22 actual COFF fields; no SDK/data/audio helper or compiled static
literal is credited.

The 27-byte authored `AudioStream::ScheduleTransitionFadeAt00419DF0`
with native SHA256
`43997ef22f85341a11655d92ecc54de7a78a3c916e3f3503e1555c6d15076fd0`
simply forwards the actually observed -6000, -200, 1, 1 fade arguments
to target 0x00407E60. It separately cold-replays 27/27 exact with
one actual call relocation and no owner-layout claim. Both F204
and F205 were rebuilt together and the existing 97 unknown origins
remain uncredited.

## F206: exact 727-byte texture bitmap-directory loading

The complete authored TextureManager::LoadBitmapDirectory at 0040B280
is 727 native CODE bytes, 180 whole x86 instructions, native RET4 and
29 real COFF fields. The body SHA256 is
10539410fb282c0cc58270dc9360a7a11a87d748e519631a2b62c41848b374cc.
An independent pinned VC7.1 /GX- cold build compares all 727 bytes
and all 29 actual relocations exactly.

The source preserves the real bitmap file naming, loaded bitmap
texture sizing, optional indexed palette encoding, sixteen-bit
texture allocation, refresh and memory release. Unlike an earlier
576-byte probe, the failure branch uses native STL vector iterator
objects and end, begin plus index, and erase calls. A 645-byte
natural iterator probe already matched the entire instruction count
but used shorter EBP displacements for two meaningful scalar locals.
Organizing the genuine filename buffer, index and total in a local
working record yielded the native 0x130 stack frame and full match.
Both 260 and 264 byte buffers produce identical exact native output,
so original source array length is not asserted. The native program
compares the same height field against 64 twice; no unproven
width-check correction was introduced. STL/CRT helpers and external
data do not earn extra byte credit, and original owner class
identities remain provisional. Rejected probes and native disassembly
are preserved in .analysis/f206-bitmap-directory/.

## F207: independent exact formatted bitmap directory loading

The native TextureManager::LoadBitmapDirectoryWithFormat at 0040B560
contains 575 CODE bytes, 145 decoded instructions, ordinary RET4
and 23 actual COFF relocations. SHA256:
bdf51c229e4af4379d9bc45b5e816374a5653d5f239b0f97f8a2276e53c092cc.
A fresh source probe using only independently grounded native
entry fields, four-argument CreateTexture, real bitmap loading,
refresh and free/null matched its entire 575-byte extent and all
23 fields on the first complete build. After preserving all
iterator control-flow and data offsets, canonical cold replay
with F206 yielded both full bitmap loaders exact: 575+727=1,302
authored CODE bytes and 23+29=52 actual relocation fields.

The companion uses the native four-byte iterator begin/end/erase
failure protocol and actual local work record, with the same
native stack frame and index/total/name offsets as the separate
F206 routine. The physical evidence supports these call windows
but does not prove original nominal vector/element/source naming.
All SDK, image decoding, STL helper, global data, compiler cookie
and original owner-layout credits remain independent/unclaimed.

## F211: exact four-vertex rectangle geometry

At `0x0040DB50`, the authored
`SpriteGeometry::InitializeRectangleFromRect` contains 305 CODE bytes
and 109 decoded instructions, ending with `RET 4`. Native body SHA256:
`044430cb8da9082f9bac7b8d3a7d0eaa1e908e15cd9e1fff5c90877153897ff0`.
Independent standalone VC7.1 `/GX-` cold replay reproduces the complete
305 bytes and all nine physical call relocations.

The source-compatible receiver declares four independent physical
16-byte vertex members at offsets 0, 16, 32 and 48 and a separate
member ctor call at +64, and passes the original RECT integer coordinates
through the same float construction and four temporary-copy paths.
A first source using `SpriteVertex corners[4]` generated a different
C++ array-construction helper, yielding only 282 bytes and an
unapproved extra runtime helper. Changing the representation to four
independent source members yielded a complete match without hand
written assembly or padding. Actual vertex math/call order is confirmed;
the original nominal class identity, unrelated members, compiler
helper source and original field names are not asserted. F207 and
F211 were re-cold-replayed together with zero differences. Neither
owned data nor external helper bytes receive new code credit.

## F212: exact three-stage EH sound startup

The independently authored `GameGlobals::InitializeSound` at
004175A0 is 334 native CODE bytes with 84 decoded instructions,
one ordinary RET and 29 actual COFF relocations; SHA256
`edabd3cf233ed6befa5b4761245e68d43f798d87ccd4580c60580a8c35c78fa8`.
The original R020 EH handler `006551C1` records three transient
allocations; pinned VC7.1 /GX natural C++ recreates all 334 bytes
and 29 fields in a fresh cold build. The two input binding stores,
three actual `new` allocation sizes 120, 8 and 20, respective
constructor calls and globals, volume forwarding, wave loading and
worker startup match the independently decoded complete function.

Physically sized allocation carriers supply real `sizeof` values
to new and real borrowed ctor methods. They are not invented
reusable original scene/audio class definitions: complete members,
source names, nested owners and ABI outside the observed calls
remain unproven. Compiler EH cleanup code, constructors, wave bank,
SDK calls and static globals receive no additional exact code credit.
The first complete source compiled structural exact; independent
canonical cold replay confirmed full code and every field.

## F213/F214: progress-record leaves and large defaults

Two authored record leaves at 0041A1D0 (109 bytes) and
0041A270 (90 bytes) match completely with zero external relocation
fields; both retain signed selection indices and native record
strides. The adjacent 910-byte `ProgressRecords::InitializeDefaults`
at 00416640, target SHA256
`6038d21f8518f49a355159fde8bd343c224e01c61ddc2ffcd3630cc1a6d3df14`,
also cold-replays exact with 34 native relocation fields.
The natural C++ reconstructs two complete memset clears, ten
genuinely initialized nine-byte fish-name locals, a 15x4x10
record grid, 15x15 counter matrix and eight mode bytes. Block-scoped
loop variables and a true two-dimensional matrix subscript resolve
the native VC7.1 local frame and final x86 SIB byte. These sources
do not assert original complete owner layouts.

## F217: archive registry lookup and named entry seek

`ResourceLookup::FindByNameAt0041CF00` (113 bytes / 9 COFF fields,
body SHA256
`6391a9bbd25ec4b140e9fd14203dda8247ef25cd77891930f15a1ab7067586a1`)
follows the original archive deque Size/At functions, strcmp and
a second paired object deque. An early null return restores native
JB branch placement where an initial ordinary if/else did not.
`DataArchive::SeekNamedEntryWithSize` (180 bytes / 10 COFF fields,
body SHA256
`72ce55c493128e07f8bce2445b2409fc9f041064408f1166d5befd0a45849979`)
naturally reproduces four-byte list iterator begin/end, postfix
increment returning an iterator copy, comparison, entry offsets
+0x64/+0x68 and native SetFilePointer, `RET 8`.
Both independently cold-replayed exact, without importing STL
or external data byte credits.

## F218: replay capture, snapshot header and path search

`ReplayRecords::BeginCapture` at 00413790 is 225 CODE bytes
(67 complete instructions), target SHA256
`8cb535b033a5a3b624a94d83f3e55aeebf6999223c29f50feed7282f8c66b65d`,
and all nine COFF fields exact. `GameState::ReadSnapshotHeaderAt00413A60`
at 00413A60 is 85 bytes, SHA256
`a64e819aca08d030fa6326f31e0ada81334e475ace8089f6cf49f5b6a7468a84`,
and three actual fields exact. Its HANDLE and meaningful DWORD
bytesRead locals reproduce the native EBP slots, unlike earlier
correct-length but mismatching local-name controls.
`ReplayRecords::FindAvailablePath` at 00414300 is 89 bytes,
SHA256 `2d65ab5258cc61702673ad78e3c645fba70d58a6f296ec92559ad868b57a9466`,
and three fields exact. It preserves the original bounded
path formatting and `_access` search. All three separate
functions cold-replayed exact together, adding 399 authored
CODE bytes and 15 true fields.

The adjacent 375-byte `ReplayRecords::FinalizeFile` remains
unaccepted. Natural sources retain the Win32 replay copy,
record header write, original 264-byte path and GS cookie;
full-body probes emit 342, 372, 384 or 396 bytes against 375.
No cropped body, fake stack padding or masked relocations are
counted. The 792-byte ReplayRecords load and 916-byte musicroom
catalog parse also remain nonexact under complete native checks.
Their failed full-body controls are preserved privately.

## F220: two exact replay queue policies; native large writer pending

The authored `StaticResourceQueues::ClearFourQueuesAt00413880`
contains 67 CODE bytes/19 decoded instructions and four genuine
relocations. Its native SHA256 is
`bf53ffaf4b4506f435935937e2e5961e7cfd1965918d7cce285e3bf8ccb3547d`.
The source uses the four physically confirmed 20-byte queue
receiver offsets and matching Clear helper calls; all bytes/fields
were cold replayed exact. The authored
`ReplayRecords::IsPrimaryInputQueueEmptyAt004142D0` contains
35 CODE bytes/15 instructions, SHA256
`72b5bfc6c414a06ad751cb62e2bb8bcf1c40264911c97728d7e22b74ccb339e3`.
The entire code and only relocation to the actual deque Size
callee cold-replay exact. No underlying STL implementation,
archive storage, unknown original owner class or helper body
receives separate exact credit.

The adjacent 1252-byte `ReplayRecords::AppendRecord` at
00413DE0 has 379 independent native decoded instructions.
Complete C++ source reproduces the original six physical 8-byte
iterators, four queue traversals, full four-set WriteFile calls,
queue clearing and record index advance. Natural `for` updates
rather than `while` loops recreate the complete 1252-byte
code size, all 50 external field positions and native loop
control-flow shapes, but compiler local stack assignments
remain different: the best tested meaningful local naming
matches 1025/1052 non-field bytes in the best later control. This is explicitly
**not accepted**; private research in `.analysis/f219-append-record/`
is retained without masked fields, fabricated stack padding,
ABI lies or partial code credit. The 792-byte record reader
and 375-byte finalizer remain separate large-function targets.

## F222: exact Marisa fighter round reset

The independently reviewed MarisaFighter::ResetRound at 00493130
is 780 native CODE bytes/157 complete instructions and three
actual DIR32/REL32 relocations; body SHA256
bfed8d082f3fd36aeb82e8d2694f1b61fd3fc2f1e90b5f53ff7061c31f0ea774.
The natural C++ source preserves 32 halfword clear stores,
one byte clear, 37 pairs of 28-byte animation records,
signed x87 FILD dword and FDIV dword of float 36.0 at 00659308,
and the accepted base reset call 00457010.

The only first-probe mismatches were two bytes in a loop condition:
i<37 compiled CMP 37/JGE instead of native CMP 36/JG.
The same meaningful loop written i<=36 generates all 768/768
nonrelocation bytes exactly. Independent canonical pinned VC7.1
cold replay confirms all 780/780 bytes including both scale
DIR32 fields at offsets 0x222/0x2CB and the actual REL32
base-reset call at 0x304. The receiver is a physical call-only
view, not a recovered full Marisa class; no data, helper,
compiler-generated sections, fake locals, binary masks
or duplicate base-callee code is credited.

## F223: Marisa and Youmu constructors / real EH ownership

Full authored natural-source /GX- or /GX VC7.1 cold replays:
MarisaFighter::Initialize at 00492FB0 (243 CODE bytes, six
relocations), MarisaFighter::CreateOwnedObject at 004930B0
(120 CODE bytes, six relocations, one-stage EH and actual
new(0xE8) allocation) and YoumuFighter::Initialize at
0052CEE0 (314 CODE bytes, eleven relocations, native
EH and actual +0xFEC subcomponent initialization). All
677 CODE bytes and 23 native fields match exactly. Source
carriers express real allocator dimensions and borrowed
callee ABIs; they do not reconstruct a complete player,
subcomponent or library object. Three accepted unit keys
are recorded in match-units.toml, alongside source hashes
in the exact adoption manifest.

## Retained failures and method boundaries

Retain 14 frozen prior objects plus F184, all 14 F157 probes, both F159 traces
and 40 protected groups. Full 004AC040, 0050A580 and 0055AC80 drafts still fail
complete comparison. Their detailed closed controls remain in the archives and
private receipts; read them before another scope/profile/type/name experiment.
The old F176 440-byte probe stays negative evidence even though F181 accepts
the same native function through another complete 446-byte object.

R103 camera 453EB0 remains unaccepted. R231 unread camera stores, R065 445A00's
write-only local and R054 455B30's 28-byte clear need supported source-purpose
explanations; no unused locals, arrays or padding. Options switches need owned-
table comparison. The 43AD10 EH constructor needs real allocation/layout/lifetime
evidence; no pasted EH bytes or invented complete owners.

## Cleanup and historical evidence

Wine lowercases PDB names. Compare paths case-insensitively before treating a
PDB as unpaired or unprotected. H184 losslessly archived 480 old unpaired PDBs,
checked every full member hash, then removed their original outputs. Live object
companions, all objects, sources, profiles and evidence remain. The local archive
manifest permits restoring any individual original path. No frozen origin or
evidence file changed.

The complete former documents are preserved **byte-for-byte** in
[knowledge through F183](history/KNOWLEDGE_BASE_THROUGH_F183.md) and
[handoff through F183](history/RE_HANDOFF_THROUGH_F183.md). Original titles,
filenames, strings, observations and unknowns remain. Archived goal-state and
next-task commands are historical; current user instructions, AGENTS.md and the
handoff govern. Historical relative links were written from docs/. Earlier
[F148 knowledge](history/KNOWLEDGE_BASE_THROUGH_F148.md),
[F148 handoff](history/RE_HANDOFF_THROUGH_F148.md) and origin histories are unchanged.

**Preserve this workspace when switching agents.** Private artifacts, target and
project are not in a Git clone. Preserve shared tools and private service/auth
settings. Stay headless, use scripts/repo-python and the existing Ghidra wrapper
without REA, cold-replay only new/affected units and keep compilers serial.


## F224: independently cold-exact Youmu-owned allocation and round reset

Two **authored**, independently R050-reviewed native extents are fully preserved
without expanding any nominal fighter class: `0052D090` (120 CODE bytes,
34 native instructions, SHA256
`6820c7d36834a8967b2b9c6e099476c47a83a94a0b8edbe4b95f3f6288ba1d2b`) and
`0052D110` (225 CODE bytes, 44 native instructions, SHA256
`7c68b6e70cd26d9f1ae8227d36cb730f26bfb349937f0ff01130473155827fff`).
Ghidra attested the full extents and disassembly. Both natural VC7.1 source
probes produced exact non-relocation bytes: factory 96/96, reset 217/217.

The factory uses normal `new` for the *observed* physical 0xE8 allocation
and the existing constructor call `00536360`; VC7.1 `/GX` reproduces the
full genuine EH frame, return convention, and six relocation fields including
its native handler `006564FD`. No claim is made for generated EH helper
bytes or the complete nominal allocated class. The reset writes 16 observed
halfwords in the native order, calls the previously accepted base reset at
`00457010`, then applies the real +0xFEC subcomponent reset at `00531CE0`.
Its `/GX-` object preserves both original REL32 call relocations.

`replay-exact-units.py --unit youmu-fighter-create-owned-object-0052d090` and
`--unit youmu-fighter-reset-round-0052d110` both cold-built to `exact`, not
merely `structural-exact`. The true symbol/target/offset ledger is in
`config/match-units.toml`, with sources `src/YoumuOwnedF224.cpp` and
`src/YoumuResetF224.cpp`. Original method/class naming and any unobserved
private fields remain provisional; the 97 unknown origins and large pending
function drafts are not made exact by this adoption. The experiments and
assembly remain in `.analysis/f224-youmu-lifecycle/`. Local exactness is not
an accepted external Oracle replay receipt.


## F225: cold-exact complete character-select scene initialization (668 CODE bytes)

The complete R041 authored `CharacterSelectScene::Initialize` at
`00432EA0..0043313B` is 668 bytes / 185 native instructions, SHA256
`d48db16d3f434e97d49368dd441c0434a777afb0c97c949344c05db86568f987`.
Ghidra attested the entire native extent. Native `/GX` EH uses handler
`00655AB9`, unknown-origin base ctor `004251C0` (R108, **not** adopted),
and scene vtable `0065824C`; this constructor also guards and dispatches
two native slot-five deleting destructors through the existing globals
`00671418` and `0067141C`, then clears those pointers.

The three distinct ordinary `new TextureAllocF225` allocations pass the
observed 80-byte physical size and call the already accepted real manager
constructor `0040AD80`. They allocate slot counts 8, 22 and 17 and load
three original texture path/root pairs through `0040BB80`, in native
order. The scene sets three global mode/transition flags, calls actual
configuration load `004192F0`, reads 30 default option bytes and two
15-element control maps via actual cdecl helper calls `0041A0E0` and
`00419E10`, clears the final two scene bytes, and calls the native
`00433230` selection reset. The three 80-byte allocation carriers and
call-only scene/actor receivers do **not** establish their full nominal
original class layouts; the five unobserved virtual actor slots are only
physical placeholders for observed deleting-destructor slot five.

The first natural source wrongly declared this-relative data in the two
config loops as three pointer variables. It produced 677 bytes and extra
loads. The corrected *array bytes within the scene* use `this[base+i]`
and compile to the exact 668-byte whole native control flow with 516/516
non-relocation bytes. All 38 physical COFF fields have exact target
resolution (including EH, vtable, globals, Win32 allocation and real
callee destinations). Independent cold replay of
`character-select-scene-initialize-00432ea0` reports `exact: 668`; the
canonical source is `src/CharacterSelectInitF225.cpp`, and probes/native
assembly remain in `.analysis/f225-big-functions/`. No cropped extent,
synthetic return, invented storage layout, asm or masked fields are used.
This local exact unit does not claim external Oracle acceptance, runtime
behavior validation, base constructor origin or any additional library
bytes. All 97 unknown-origin candidates remain uncredited.


## F226: replay-browser selection machine, complete 1,005-byte cold exact

The independently R040-reviewed `ReplayBrowserScene::UpdateSelection` at
`0042C670..0042CA5C` has 296 native x86 instructions / 1005 CODE bytes,
complete SHA256 `4a126816bcb81b8c7ecc660e844624b5cd501ac8ffdd60c6dac8c84ae7ddfc1d`.
Ghidra read-only verified the whole body, unique RET, all branch exits and
real imports/callees. Source `src/ReplayBrowserSelectionF226.cpp` implements
the input poll, vtable slot-2 draw, input reset, horizontal/vertical repeat
motion, page jumps, signed 16-bit replay indices, queue size and indexed
replay metadata access, replay-variant selection, sound cue calls, selected
pathname copy, scene transitions, and all three distinct result values
(`0x2201`, `0x2202`, and `5`). Only borrowed physical list/record/scene
interfaces appear; none establishes full original container layouts.

The first natural /Od /GX- probe emitted 1,016 bytes. At the full
instruction level, a macro-style `do/while(0)` generated unnecessary
conditional branches, while four short assignments promoted to 32-bit
arithmetic. Replacing the macro wrapper with direct statements and using
genuine `++`/`--` 16-bit lvalue operations precisely reproduces all 296
native instructions, **813/813 non-relocation bytes**, and all **48 true
DIR32/REL32 relocation destinations**. The sole F226 cold replay
`--unit replay-browser-update-selection-0042c670` reports **exact: 1005**
(not structural-only). Private probes and instruction diff analyzer remain
in `.analysis/f226-replay-browser/`. No pre-existing accepted unit was
recompiled; no whole-program cold replay, masked fields, fake locals,
assembly, ABI substitutions, code cropping or external helper credit.
All 97 origin-pending functions remain uncredited.


## F227-F228: Reimu and Alice exact lifecycle; recover two pending character-select boss functions

On the same pinned TH075 1.11 binary, four independent R046/R050 fighter
functions cold-build to `exact` without shared header changes:

* Reimu factory `0046D160`, 120 bytes, 34 native instructions, 6 real COFF
  fields, target SHA256
  `922399edaaa88c66ee9c8095d8d53bb23e1f78163c0d803b9bced866cb884301`;
  ordinary `new(0xE8)` calls actual `004769B0` and genuine EH `0065642B`.
* Reimu round reset `0046D1E0`, 235 bytes, 45 instructions, one REL32
  to accepted base `00457010`, SHA256
  `0e0e300a72c0a9b1cb632014ce4db7f19d300bffab2e56e89664f14ff8da7cfd`;
  the native resets 16 halfwords **before** base reset and two **after**.
* Alice factory `004E2D90`, 120 bytes, 34 instructions, 6 fields, SHA256
  `678cc5d0b2e17603636b0fb955198e91ce0c8c35c6f81b0edc4a9c5f215e70f2`;
  ordinary EH-backed `new(0xE8)` calls actual `004EBD00`, handler `0065648B`.
* Alice round reset `004E2E10`, 223 bytes, 43 instructions, one REL32
  to `00457010`, SHA256
  `353ddb043c35008a7b6d5c7355b432ab6511abd5962bc2c0a5aa16c9ba167360`;
  the native performs 17 halfword writes **before** base reset.

Each natural C++ body in `src/*F227.cpp` independently reproduces the
entire target, including relocation targets. Two recovered unfinished
character-select source/manifest changes were **investigated rather than
discarded**; they were originally left unregistered in the acceptance
ledgers, causing the exact-checkpoint count guard to catch a mismatch. The
source, original binary and all native destinations were independently
reverified before registering those units:

* `CharacterSelectScene::UpdatePlayerChoice` at
  `004348E0..00434CE4`, 1,029 bytes / 245 native instructions, SHA256
  `7caee90598d5bd3f45389a0e5b0852ea679517934ada3f04627594557dbe4872`.
  The natural signed-player source `src/CharacterSelectChoiceF226.cpp` cold
  replays 901/901 comparable bytes plus all 32 physical COFF relocations,
  including float animation constants, native sound/input calls, and CRT rand.
* `CharacterSelectScene::UpdatePlayerConfirmation` at
  `00434CF0..004350D2`, 995 bytes / 242 native instructions, SHA256
  `67e1ce98232d90f7b4dfa9fc781b850672732483a0befd09b54eda9222f64412`.
  The signed player and game-mode source
  `src/CharacterSelectConfirmF228.cpp` independently cold replays 859/859
  comparable bytes plus all 34 native relocations. The native x87 bounded
  animations and signed CRT rand modulo-three logic are retained.

In both controllers, nominal scene identity/layout remains inferred; their
physical signed player strides and actual byte offsets are native-observed.
All six are independent whole-function `exact`, not structural acceptance.
Only these six affected units were cold-replayed: no all-unit cold replay
or class inference from unrelated games. Existing 97 unknown-origin
candidates and original evidence remain unchanged; Git commits are local
checkpoints, not external Oracle receipts. Private proofs are retained in
`.analysis/f226-player-choice/`, `.analysis/f227-fighter-recovery/`,
and `.analysis/f228-confirmation/`.


## F229: complete 1,442-byte character-selection scene state machine and 9-case table

R044 independently classifies the entire `CharacterSelectScene::Advance` body
`00433470..00433A11` authored. Native CODE is **1,442 bytes** and 362
complete x86 instructions with SHA256
`88d95852e72a14f2c4769a778506b382ae586604e6e7ca6db04a718942550a68`.
The **owned table**, not extra CODE, occupies `00433A12..00433A35`: nine
32-bit dispatch destinations (case 0/1/2/4/8 + four default paths) at
`004338E2`, `004338F0`, `004338FE`, `00433926`, `0043390C`,
`00433926` repeated for 5/6/7, and `0043391A`. The full **1,478-byte
comparison extent** has SHA256
`dc3dd8d70688b8abb748c39579d1d997826d09a14f05e6542494f22351d7e679`.

An independently developed, natural C++ source
`src/CharacterSelectAdvanceF229.cpp` reproduces native scene polling,
vtable slot-2 dispatch, screen animation and mode flags, distinct
cancel/return branches for modes 1/5, 3/4, and other modes, two-player
selection/confirmation/animation switch dispatch, the actual replay
state transition and final tick wraparound. Call-only interfaces reuse
actual accepted input/selection/replay callees; they are not recovered
complete original class declarations. The input cancel frames use a
**physically observed 0x48-byte indexing stride** (independent
`SelectionInput4388D0.cpp` evidence); the bytes other than the leading
queried cancel word are deliberately not interpreted or instantiated.

First natural source emitted 1,429 native-shaped CODE bytes plus a 36-byte
table (1,465 total) versus 1,442 + 36 original. Full instruction
alignment independently identified cancel-priority branch placement,
compiler arithmetic for the 0x48 input stride, opposite-player lvalue
addressing and branch order for state dispatch. Restoring the
actual semantics using `if (cancelled) ... else ...`, pointer-relative
player-array indexing and an inverted outer state dispatch caused
ordinary VC7.1 `/Od /GX-` to emit **1,442 CODE + 36 table exactly**. The
comparison is **1174/1174 actual non-field bytes plus 76/76 real COFF
fields**, including nine physical local table relocations with fully
resolved original destinations. `replay-exact-units.py --unit
character-select-scene-advance-00433470` independently cold-built the
new object and returned `exact` (1,442 coverage bytes). The difference
from the native 1,478-byte compared extent is owned table bytes, which
receive **no CODE credit**.

Nearby `CharacterSelectScene::UpdateCancelAnimation` at `00435870` remains
unsolved: the natural full 497-byte body matches 438/445 non-field bytes
with 13 relocations, while VC7.1 repeatedly emits a different x87 load
order for the 60.0f equality test. Source-value and expression-order
experiments remain as private negative controls at
`.analysis/f229-character-select/`; **no matching ledger row, match unit
or byte credit** was assigned for this incomplete function. Full F229
native disassembly, first/best sources and comparison logs are retained.

No literal target bytes, assembly, fake storage allocations, padding,
local-value masking, or cropped comparisons were introduced. This is
local cold-exact replay, not an external Oracle receipt or full game
rebuild. All 97 origin-unknown candidates remain uncredited.


## F230: two complete player-options and submenu callees under the F229 boss

Two distinct R041/R043 authored functions called directly by the F229
`CharacterSelectScene::Advance` were reconstructed in ordinary pinned
VC7.1 `/Od /GX-` C++ and cold-replayed **independently**, without recompiling
any unrelated accepted match unit. Their nominal scene class and input
owner are still physical call-only views, not proven original layouts.

`CharacterSelectScene::ProcessPlayerOptions`, at `00433A40..00433BD3`,
contains 404 CODE bytes / 111 native instructions and 18 physical
relocations, SHA256
`14fa30b51abb4fcd520b51eeab01433d87f8d9f7d30d2921b323d3d8aa4bf3fc`.
The function takes signed `player` with an observed 28-byte action-input
stride, calls the observed input checker at `00438A60`, toggles the scene's
byte at `0xEC+player`, plays game sound cues, toggles per-player option flag
`00671438`, updates signed `00671434` option indices modulo five in both
directions, and clears/sets player cancellation at `0xEA+player`. The first
complete natural source emitted 405 rather than native 404 bytes: VC7.1
lowered plain `!byte` as 8-bit `SBB AL,AL; INC AL`. The **same meaningful
boolean conditional** written `flag ? 0 : 1` emits native 32-bit
`NEG EAX; SBB EAX,EAX; INC EAX`, preserving the original byte stores and
all native branches. That version matches all **332/332 nonfield bytes**
and 18/18 true relocation fields, then cold-replays `exact` (404 bytes).

`CharacterSelectScene::ProcessSubselection` at `00433BE0..00433CE7`
contains 264 CODE bytes / 70 instructions, SHA256
`6f6fbddee5b1d6792e9184fa7df9736f25c8f30bc35a69ee0269313bad2992b9`.
The first ordinary C++ source emits all **200/200 nonfield bytes** and
16/16 relocations, cold `exact` (264 bytes). It preserves signed modulo
arithmetic and the ESI-carried intermediate with two separate authentic
`ProgressCard438A80::GetSelectedValue` calls at `00438A80` using the real
`006718F8` caller-side receiver, sound cues, selected fighter/pad/stage
globals `006714C8/00671620/00671621`, scene state writes, and cancel
cleanup in target order.

Original `00438A60` remains origin-unknown under R163; calls to it in
these two authored functions **do not** reconstruct or credit its body.
No guessed complete object allocation, target-byte grafts, assembly,
artificial unused locals, comparison masks or cropped returns were used.
Private first/negative and final sources plus disassemblies remain at
`.analysis/f230-selection-helpers/`; accepted sources are
`src/CharacterSelectOptionsF230.cpp` and
`src/CharacterSelectSubselectionF230.cpp`. Both are local exact receipts,
not externally verified Oracle submissions; all 97 unknown origins and
unrelated accepted units are preserved.


## F231: whole replay-browser file enumeration, 613-byte cold-exact source

R040 independently reviews `ReplayBrowserScene::ScanFiles` at
`0042D470..0042D6D4` as authored. The complete native function has 613
CODE bytes / 155 decoded instructions ending in RET, SHA256
`5ffba6a61250b27ffe1656bd74db2b75c19b1caf44a278df087cca7ea6177362`.
The original `/GS` cookie and final check are genuine fields, not extra
function credit. The natural `src/ReplayScanF231.cpp` borrowed receiver
keeps the true `this+0x0C` filename deque, `this+0x20` header deque and
`this+0x34` flag deque. It neither instantiates nor asserts a complete
original STL/game class.

Native File API operations are genuinely Win32 FindFirstFileA with
`"replay\\*.rep"` at `00657FD8`, looped FindNextFileA, guarded FindClose,
then CreateFileA/ReadFile/CloseHandle. Two **distinct original string
addresses** `00657FE8` and `00657FF0` contain the same `"replay\\"`
prefix but are retained as separate true relocations. Each matching filename
slot receives a genuine 0x104-byte array new, followed by original strcpy
and strcat. The file decoder reads one physical 60-byte header into the
second deque and a trailing one-byte status into the third; size/count
checks preserve original unsigned branches and the original no-validation
behavior. Callee bodies, SDK imports, CRT, deque implementations, strings
and library bytes receive **no independent authored CODE credit**.

First ordinary C++ source already emitted 613 bytes with 31 fields but only
471/489 non-field bytes matched; all differences except one unsigned
condition were MSVC local-stack slot placements. The native frame shows
WIN32_FIND_DATAA at EBP-0x148, file handle -4, /GS guard -8, file read count
at -0x14c, 60-byte header at -0x188, flag at -0x189, index at -0x190,
first pointer at -0x194, first new[] temporary at -0x198, next pointer at
-0x19c and second new[] temporary at -0x1a0. Rather than inventing padding
or unrelated locals, genuine nested block lifetimes for count/header, flag
and index restore these addresses. Finally, both nullable deque insertions
use normal VC7.1 C++ `push_back(static_cast<char*>(0))`: their genuine
temporary `char* const&` bindings restore the last four different slot
operands. `size()>0` emits the native unsigned JBE.

The complete 613-byte object then compares **489/489 non-field bytes**
with every one of the **31 original COFF relocations** solved. Independent
pinned-toolchain `replay-exact-units.py --unit replay-browser-scan-files-0042d470`
cold built this *only affected unit* and returned **exact: 613**, not just
`structural-exact`. `tests/test_replay_scan_f231.py` independently pins the
full native SHA, original three string extents, all 31 manifest fields and
source hash without rebuilding unrelated objects. All negative and positive
probes, original disassembly, constructor/stack variants, native SHA and cold
log are retained under `.analysis/f231-replay-scan/`. No source body split,
assembly, fake locals, masks, partial extents, external Oracle acceptance
or unproved nominal class layouts. The 97 unknown-origin candidates remain
uncredited, including the separate `00438A60` previously unresolved call.


## F232-F233: negative whole-boss replay tests retain original full extents

R035 independently reviews the authored on-disk replay functions.
`ReplayRecords::AppendRecord` (`00413DE0`) remains 1252 entire CODE bytes
with 50 real relocation fields and **only 1025/1052 nonfield bytes**
matched by the best natural source. In F232 we preserved all six real
8-byte iterator objects, the four 20-byte queues and all native branches,
while checking new lexical lifetime splits rather than repeating exhausted
72 variable-name permutations; no exact result. These 1252-byte controls
and 50 field endpoints are retained in `.analysis/f232-append-scope/`.

The independently reviewed `ReplayRecords::LoadRecord` (`00413AC0`) is
792 complete native CODE bytes /274 x86 instructions and 29 true fields.
F233 independently recompiled the best natural complete source: still
639/676 nonfield bytes. Native comparison identified physical stack slots
for HANDLE (-0x14), record count (-0x10), ReadFile bytesRead (-0x1C),
byte item (-0x15), raw short (-0xC), and stored short (-0x1E), whereas
ordinary VC7.1 naming/declaration order assigns different slots. Tested
meaningful raw short declaration positions, short-item order, and actual
read/record scopes without masking or phantom stack storage; none improves
the best. Every negative source/preview and native-to-object instruction
comparison is retained in `.analysis/f233-record-scope/`. Both functions
remain **unaccepted and receive zero new authored CODE credit**.

## F234: whole music-room selection state machine (675 cold exact)

The R040 independently authored `MusicRoomScene::UpdateSelection`,
`004259D0..00425C72`, has 675 original CODE bytes /179 x86 instructions
and SHA256
`da7be73a54b77cebacf43215e0f5502722393f166bcf2c79ee92326805761c6a`.
Original native mode and input states are actual 32-bit globals
`00671668/006716B0`, `0067166C/006716B4` and exit
`00671670/006716B8`. Borrowed call-only scene state gives the true
`+0x3DE` signed selected index, `+0x3DC` bound, `+0x3DF` ten-row scroll
origin and `+0x3DD` 60-tick cooldown. Each 16-byte track record has an
independently observed signed byte at `this + 0x1C + selected*16`, passed
with +100 to the already-existing global progress-card check at
`00416DC0` with its actual `006718F8` receiver. Original highlight
`00426A70`, choose `004268A0`, music player `00419CB0`, input escape
`00407170` and transition `00407E60` are real callee destinations.

A single natural VC7.1 `/Od /GX-` source probe in
`src/MusicSelectF234.cpp` reproduces **579/579 comparable nonrelocation
bytes, all 24 independently mapped physical COFF relocations** and the
full native function length. An independent cold replay of only
`music-room-scene-update-selection-004259d0` reported **exact: 675**.
`tests/test_music_select_f234.py` protects full native SHA, all 24
relocations, call multiplicities, original `RET`, manifest/source hash,
without broad cold builds. Nominal original source names and full
scene/progress/input layouts remain provisional; no invented classes are
instantiated or embedded, no extra helper/global/data bytes are credited.
This is a local exact replay, not a remote Oracle receipt, and the 97
origin-unknown candidates are unchanged. Complete native evidence and
reproducible probe/cold logs are under `.analysis/f234-music-select/`.


## F235: exact pair of complete music-room text-rasterization functions

Both entire R040 authored text-rendering native extents have been measured
independently against the pinned original PE.

* `MusicRoomScene::RenderTrackCatalogText`, `00426670..0042689A`,
  **555 CODE bytes / 136 native x86 instructions**, SHA256
  `e4fa7a8d0959984efd8330089a6c75c21d33ef3ad7c983ff7d47bc796053ab24`,
  reproduces the target's true 2,000-byte text buffer, complete count loop
  over 16-byte track records, real progress status at `00416DC0` with
  `006718F8`, signed track metadata, original empty/hidden/newline string
  addresses `00657C0A`, `00657C0C`, `00657C20`, and real strcpy/strcat.
  The scene's `this+0x10` D3D8 texture is locked, original 56-byte glyph
  renderer constructed and configured, string rasterized to native locked
  surface dimensions 1024x1024/560-pitch, then deleted and unlocked. Its
  natural `/Od /GX /GS` source first compiled to **471/471** non-field
  bytes with **all 21 original COFF relocations** and cold-replayed `exact`.

* `MusicRoomScene::RenderSelectedTitle`, `004268A0..00426A63`,
  **452 CODE bytes / 114 native instructions**, SHA256
  `a023fd37218cf93c70c7ba2cd13ece2bcd2baafc00df0c1fb00cabedc6ba24ad`,
  tests the genuine signed selected-record index and original missing-title
  versus `sprintf("%s",name)` path. Native strings at `00657C32/00657C34`,
  scene D3D8 texture `+0x14`, glyph font `00657C38`, 512x32/560-pitch
  rasterization, deletion, unlock and native `RET4` remain intact. The
  first complete 452-byte VC7.1 probe had 358/388 comparable bytes because
  a presumed 308-byte local buffer made `SUB ESP,0x168` and shifted all
  physical stack operands eight bytes below the native `SUB ESP,0x160`.
  Native object and char-array addresses confirm the real **300-byte local
  message buffer** (not a fake padding or masking change). That ordinary
  source change matches **388/388** comparable bytes and all **16 real
  relocation fields**, independently cold-replayed `exact`.

Both C++ files `src/MusicListRenderF235.cpp` and
`src/MusicTitleRenderF235.cpp` use only borrowed scene/texture receivers and
previously accepted F191 physical 56-byte glyph receiver observations;
no complete original class layout, embedded incomplete owner or imported
D3D8/font/CRT/helper bytes are claimed. Both real exception frames
(`006557F9` and `00655811`), native `0066FE30` /GS cookie and
`00640611` check, operator new(56), glyph constructor `0041BF90`, font
setup `0041C060`, rasterizer `0041C2E0` and existing deleting destructor
`00413620` are precisely accounted for as **relocations only**. Every
physical original full function extent and all 21+16 relocations are
independently guarded in `tests/test_music_render_f235.py`; original
negative/best probes, target hashes and cold logs are retained in
`.analysis/f235-music-render/`. Only the two changed F235 units were
cold-replayed; no broad rebuild or invented source bytes. The 97 unresolved
origin candidates remain uncredited; Oracle acceptance remains separate.


## F236: verified complete music catalog parse structure, still not exact

The independently authored R066 `MusicRoom::LoadCatalog` at
`00426DD0..00427163` contains **916 CODE bytes** (SHA256
`3df59d06537c81eb8d58af1a193eafdab1035d96204384244e8250b949cf294a`),
followed by its own **16-byte, four-entry** switch table with targets
`00426F55`, `00426FA6`, `00427020`, `0042709A`. Its complete
932-byte comparison has SHA256
`1a5816e578f8af00aa4a14dc6ad0b4c0998c7539e5a46985422793cedf9c3017`.

Earlier F215 C++ hypotheses separately emitted 928/934 bytes and lacked
the full original. Native instructions newly establish **both** the
condition-first numeric parse (`while (begin != end)` in real C++) and a
real cleanup-pointer transfer through original `EBP-0x3C` before `free`.
The combined ordinary source restores the **entire 932-byte emitted
extent, 282 target-shaped instructions and all 18 actual relocation
positions**, including all four jump-table fields. This is an important
structural baseline, but **not an exact match**: only 731/860 comparable
non-field bytes agree. The generated frame is `SUB ESP,0x50`, not the
native `SUB ESP,0x48`; stack offsets of real file size, handle, buffer,
read count, decrypt index, key/delta, CSV parser cursor and field bounds
are different. Seven legitimate read/decrypt/parser lexical scope
variants achieve a best of **744/860**; another seven real-variable
declaration-order changes fail to improve it. No shadow bytes, masks,
fake unused locals, artificial padding, source-body alternate compilation
or incorrect ABI was introduced.

The entire negative study is retained in
`.analysis/f236-music-catalog/EXPERIMENTS.md`, with original Ghidra
read-only analysis, complete native instructions, all natural probe
sources/objects, and mismatched comparisons. The unresolved R066 function
receives **zero source/exact credit**; its native CODE and table must both
match before adoption. All 97 unknown-origin candidates stay unchanged.


## F236: complete music catalog boss, still unaccepted after genuine source fixes

The independently R066-authored `MusicRoom::LoadCatalog` at `00426DD0`
remains **unaccepted**. Native CODE size is 916 bytes, and the physically
owned four-way jump table occupies another 16 contiguous comparison bytes.
The earlier 928-byte natural V3 source incorrectly used a `for` loop
for numeric digit parsing and passed the original archive-buffer pointer
directly to free. F236 rechecked the original full body and decoded a
meaningful while-first iteration form and a genuine final temporary
pointer alias. A combined real-C++ source emits the **entire 932-byte
CODE+table size** with all 18 physical relocation fields solved, but only
**731/860 non-field bytes** match; local stack allocation (including
fileBytes, buffer, parse cursor, quote mode, and three string allocation
slots) remains wrong. Hoisting only actual in-use locals in ten separately
reproducible variants failed to improve 731/860. The complete probes,
original assembly, instruction diff and negative controls live at
`.analysis/f236-music-catalog/`. No byte credit, masks, synthetic stack
objects or external Oracle acceptance were assigned.

## F238: complete result-counter page, 664-byte cold-exact native code

R040 independently classifies `ResultScene::BuildCounterPage` at
`00431350..004315E7` as authored. The complete original 664-byte CODE
body has 167 native instructions and SHA256
`a6d5246bf6f9f3e343e3f991d863080b0937550137b631048a6946982594a86d`.
Natural `src/ResultCounterF238.cpp` uses the actual counter-card global
`006718F8`, selected context `this+0x1C3/+0x1C4`, saved native data pointer
`this+0x14`, four separate original "%%5d\\n" string addresses, four
real sprintf/strcat calls, and the original texture at `this+0x10`.
Authentic font new(56)/ctor/configuration/rasterizer/delete, D3D8
LockRect/UnlockRect, EH handler `00655A83` and GS cookie/check are all
preserved as physical re-targeted calls; their external bodies receive no
additional authored-byte credit.

Initial ordinary C++ declared the correct 500-byte accumulated message
and 200-byte line formatting buffer, but because the D3DLOCKED_RECT sat in
the same scope, VC7.1 placed the rect at EBP-0xE4, the line at EBP-0xDC,
and cookie at EBP-0x10, emitting **670 bytes** rather than original 664.
Native disassembly establishes the actual slots: D3DLOCKED_RECT at
EBP-0x14, cookie EBP-0x18, 200-byte line EBP-0xE4 and 500-byte message
EBP-0x2DC. The *genuine* source lifetime hierarchy is outer lock rect,
inner line, innermost accumulated message, all used in their declared
scopes. Nesting these real variables produces the original 664-byte
control flow: **544/544 comparable non-field bytes and all 30 genuine
COFF DIR32/REL32 relocations** match. Independent single-unit cold replay
`--unit result-scene-build-counter-page-00431350` reports **exact: 664**.
`tests/test_result_counter_f238.py` guards the complete original PE hash,
all 30 physical fields and source hash without a broad cold replay.
The full native disassembly, temporary sources/negative variants,
comparison diagnostics and cold log remain under `.analysis/f238-result-page/`.
No invented padding, fake locals, inline asm, shortened function, masked
fields, complete nominal game class inference or external Oracle credit;
all 97 origin-pending candidates remain unknown.


## F239: complete result record page with real score-deque access and rasterization

The independently R040-authored `ResultScene::BuildRecordPage` at
`00431070..00431340` has **721 complete CODE bytes / 174 original x86
instructions**, SHA256
`fe75efccccafb762e8d16e02634a192d793edf1f2b9acdc0b23ce006009c0e04`.
The first natural C++ source `src/ResultRecordF239.cpp` reproduces the
**entire 721-byte extent, 617/617 non-field bytes, all 26 native COFF
relocation fields**, and real `/GX` handler `00655A6B` plus `/GS`
cookie/check. Only `--unit result-scene-build-record-page-00431070` was
cold-replayed; it independently reports **exact: 721**.

The source keeps the original `006718F8` progress-card selection calls
`0041A1A0` / `0041A240`, signed result-page index at `this+0x1BC`
scaled by ten, two true little-endian 16-bit per-record values at
selected record offsets `0x394` and `0x268`, real `this+0x18` deque
size at `0041DD50` and indexed name access at `0041DD70`. The no-record
branch prints its original missing-entry string and two zero counters;
the populated branch formats the real indexed name and both short
values. Original string/sprintf/strcat address relocations, signed
indices and conditional branches are all preserved.

The actual text buffer is 2000 bytes, the scratch line 200 bytes; the
D3DLOCKED_RECT and these two arrays live in meaningful nested scopes as
independently validated for F238. The genuine D3D8 texture at `this+0x10`
locks and unlocks, while a real 56-byte font object is allocated,
configured with the original font string, rasterizes a 1024x512 surface
with observed pitch 640, and receives its authentic deleting destructor
call. No source/body credit is assigned to the external progress/STL
callees, CRT functions, SDK imports or glyph helper bodies. All source
class names and any complete original parent/deque record layouts remain
inferred and call-only.

`tests/test_result_record_f239.py` guards the full target PE extent, SHA256,
all 26 real relocation positions and destinations, and immutable accepted
source hash. Native assembly, decompiler output, first exact natural
probe, native body SHA and cold log remain in `.analysis/f238-result-page/`.
No masks, fake stack locals, byte grafts, cropped target code, all-unit
cold replay, remote Oracle claims or origin-status promotions were made.
All 97 unknown-origin candidates remain pending.


## F240: original 1,344-byte result-scene render boss completely cold-exact

The independently R040-authored `ResultScene::RenderCounters` at
`0042EF10..0042F44F` is **1,344 complete native CODE bytes / 320 x86
instructions**, SHA256
`4caa7d7d4c0d1f0ea0db8d352f14f744b8cd8474a0146c368d7b5e4624d5c8b1`.
The pinned VC7.1 `/Od /GX- /GS` source in `src/ResultRendererF240.cpp`
emits **1,168/1,168 nonrelocation bytes and all 44 authentic COFF fields**
including real graphic state, transform, frame capture, six numeric draw
functions and end-of-frame calls. The independently targeted
`replay-exact-units.py --unit result-scene-render-counters-0042ef10`
cold-replays **exact: 1344** (not just structural-only).

Original rendering begins with `Graphics::BeginFrameValueAt00402660`,
constructs the already accepted 132-byte `SpriteQuad40CA80` at EBP-0x88,
uses the genuine RECT at EBP-0x98 and borrowed scene at EBP-0x9C.
The first normal source placed the quad at EBP-0x98 and RECT at EBP-0x10,
emitting 1320 instead of 1344 native bytes. The correct ordinary C++
**outer quad / inner RECT** lifetime restores both physical addresses.
It then applies the original texture depth/blend/filter modes, three
real normalized x87 rotations around the same center, scale, D3D color,
frame capture, quad translations, four dynamic result offsets, mode
selection and two final player/actor counts. It invokes the authentic
`DrawDecimalDigits` target `0042F530` six times with native coordinates,
colors and signed counts, then the genuine `Graphics::EndFrame` at
`004027D0`. None of these unchanged external callee bodies earns extra
authored-byte credit.

The accepted `ScaleQuad` callee `004115C0` takes IEEE754 float bit
patterns but the original caller uses **three direct DWORD MOV/PUSH
transfers**, not three x87 stores. A borrowed call-only
`ResultRawScaleF240` facade accepts the same 32-bit bits and preserves
that physical interface. The only remaining code mismatch was 4 bytes
in a native `FLD`/`FMUL` pair: the genuine original loads the 255.0f
constant at `00657CF0` then multiplies a float in `this+0x14`, while
initial sources loaded the field first. Modeling only that observed
partial scene prefix with a direct float member `physicallyObservedAlphaAt0014`
causes MSVC to emit the original exact x87 ordering; no scene owner was
instantiated and no full original class layout is asserted. The native
call-only class names, any unknown private fields and inferred original
identity remain provisional.

`tests/test_result_renderer_f240.py` protects the complete native SHA,
original x87 instruction bytes, all 44 real relocation fields, six digit
call count, pinned source SHA and observed partial physical layout without
recompiling old units. All stepwise failures, source candidates and
independent 320-instruction native listing remain in
`.analysis/f240-result-render/`. No machine byte grafts, inline assembly,
fake locals, masks, arbitrary stack padding, cropped code, whole-project
cold replay or external Oracle receipt are involved. The independently
reviewed 97 origin-unknown candidates stay uncredited.


## F241: complete variable/fixed decimal painter with native stack lifecycle

R040 independently classifies `ResultScene::DrawDecimalDigits` at
`0042F530..0042F6D6` as authored. Native code spans **423 whole bytes /
127 x86 instructions**, SHA256
`2d708f91fbaf060e21a87a4d066200fa0dda614c358a31d6276273b483240c55`.
Its actual `thiscall` has six explicit 4-byte stack arguments and ends
with the original `RET 0x18`, where the callee pops all 24 argument bytes.
The source `src/ResultDigitsF241.cpp` uses the previously accepted
132-byte `SpriteQuad40CA80` four-float constructor at `0040DA00`, native
float glyph width/height constants at `00657CC0/0065786C`, true
Win32 SetRect, two `DrawQuad` calls to `0040C9A0`, and two transforms
at `00411500`. The fixed-count branch divides by signed ten after each
render and translates the quad left 16px. The variable-width branch
keeps rendering until the signed integer becomes -1 and shifts the quad
left 15px. Both preserve the original atlas digit index and vertical
20px style stride, pixel color, texture index 2 and complete exit paths.

The first natural source compiled **459 rather than 423 bytes**, with
actual scene saved at EBP-0xA0, number at EBP-0x8C, quad at EBP-0x88
and rect at EBP-0x9C. The independent Ghidra read establishes original
scene EBP-0xA4, number EBP-4, quad EBP-0x90 and rect EBP-0xA0. A
**genuine outer remaining integer + nested inner SpriteQuad + innermost
RECT** lifetime restores these exact addresses without any invented local
variables, padding or unused storage. Ordinary pinned VC7.1 `/Od /GX-`
then generates **423/423 CODE bytes, 387/387 non-field bytes and all 9
actual COFF relocation fields**, with whole-function cold replay
`--unit result-scene-draw-decimal-digits-0042f530` returning `exact`.

`tests/test_result_digits_f241.py` separately pins original PE hash,
true `RET 0x18`, all nine immutable physical relocations, the native
source hash and genuine field declarations. Both the 459-byte negative
source and complete native/compiled comparisons remain under
`.analysis/f241-result-digits/`. No arbitrary bytes, embedded owner
layouts, fake locals, assembly, masked relocation targets, cropping,
all-unit cold replay or external Oracle receipt was used. The 97
origin-unknown functions and previously accepted F240 source remain
unchanged.


## F242: complete double-nibble scene-transition state machine, exact 663 bytes

R041 independently reviews `SceneTransition::DispatchMode` at
`00431F60..004321F6` as authored. The native whole function contains
**663 original CODE bytes, 157 decoded x86 instructions and genuine RET 4**,
SHA256 `c2548722489fb02941d2068f23f8b9a512fddbc1a373318b88f60b61fb1465c7`.
The ordinary VC7.1 `/Od /GX-` source
`src/SceneTransitionDispatchF242.cpp` faithfully reconstructs the signed
32-bit fade countdown at `0066C240`, game-default mode-remap flag at
`006714D2`, two distinct 0x0F00/0xF000 sparse switch trees, physical
virtual slot-two drawing, Presentation callbacks `004028A0` and
`004028F0`, and the unmodified 16-bit scene-state return. The six actual
callback values `00432360`, `00432200`, `004324D0`, `00432410`,
`004322B0`, `00432660` are **previously accepted authored draw functions**
and receive no new separate CODE credit from this caller.

The first natural code had full logic but emitted **674 rather than 663
bytes**. Independent instruction alignment proved the original code body
order is grouped 0x200/0x400/0x500/0x600/0x700, then 0x100, 0x300,
0xF00, and *only then* case zero with its subordinate high-nibble tree.
The native high tree is grouped 0x2000/0x6000, then 0x1000, 0x3000
and 0xF000. MSVC preserves lexical body ordering while choosing the
identical original sparse compare decision tree. Replacing a zero-check
with an actual positive masked-value test generates the original signed
`JLE` branch rather than `JZ`. Ordinary source compilation then gives
**663/663 full code, 555/555 comparable nonfield bytes and every one
of 27 real COFF relocation fields**. The single-affected-unit replay
`--unit scene-transition-dispatch-mode-00431f60` independently reports
**exact: 663**; no broad cold replay ran.

The nominal parent class name and full scene object fields are not
proven, and the virtual interface is used only as an existing borrowed
receiver; all existing origin unknowns remain unknown. The original
Ghidra listing, full native SHA, both natural C++ versions, byte
comparison and cold log remain under `.analysis/f242-transition/`.
`tests/test_scene_transition_dispatch_f242.py` pins native SHA, the
masking conditions, all original fields/callbacks and source SHA.
No masks, fake locals, omitted branches, machine-byte copying, invented
owner sizeof, extra callee credit or external Oracle claim.


## F243: result-scene constructor with native float scores and EH, cold exact

The independently R052-authored `ResultScene::Initialize` constructor at
`0042E640..0042E862` contains **547 complete native CODE bytes and
127 decoded x86 instructions**, original SHA256
`6fef0a170924d019037ccdb3c264dc8e357dd9c09c0edce3db3af9be94ae786a`.
The natural `src/ResultSceneCtorF243.cpp`, compiled with pinned VC7.1
`/Od /GX`, reproduces **415/415 nonrelocation bytes plus all 33 true
physical DIR32/REL32 COFF fields**. Independent cold replay of *only*
`result-scene-initialize-0042e640` reports **exact: 547**.

It calls the actual scene base constructor at `004251C0`, which is
**still R108 origin-unknown** and receives no separate source/byte credit,
then emits the real result-scene vptr `00658038` and a genuine EH-backed
80-byte texture manager `new` plus constructor `0040AD80`. It allocates
three source slots at `0040B1D0` and loads the actual
`data\\system\\result.dat` under original `data` root using
`0040BB80`. The real C++ caller retains the physical field offsets
for actor globals `00671418/0067141C`, integer score `0067160C`,
bonus `006714C0`, sequence `00671622` and target `006714BC`. The
original FILD/FIDIV, FILD/FDIV, FIADD and FSUB instructions for three
normalized score and bonus fields are reproduced without float-promotion
substitutions, along with the true 10,000-unit bonus composition.
Native zero-initialization, four 900 halfword animation placements and
one 1800 halfword placement, actor score update and two 10,000-valued
actor fields preserve the exact order and complete native EH unwind.
The carrier type's allocation size is independently verified as 80;
neither complete original actor types nor the full result-scene layout is
claimed. No artificial locals, ASM, pasted machine bytes, ignored fields,
small-function cropping, all-unit cold replay, broader origin promotions
or external Oracle receipt occurred.

The complete native Ghidra 127-instruction listing, first natural source,
relocation diagnostic and independent cold log remain at
`.analysis/f243-result-init/`. `tests/test_result_scene_init_f243.py`
guards whole original code SHA, the original EH entry and all 33 native
relocations with accepted source hash. All 97 unresolved origins remain
uncredited.


## F244: full 1,529-byte result-scene score and stage Boss with two native tables

R065 independently classifies `SceneController::AdvanceAt0042E8F0` as authored.
Its actual native extent `0042E8F0..0042EEE8` contains **1,529 CODE bytes
/408 decoded x86 instructions**, code SHA256
`19736e382a7ced3ff5809c4d0f1f791969d7ac7e82bfad3e44f85866dda351f1`.
Two **separate four-entry 32-bit switch jump tables** occupy
`0042EEE9..0042EF08`, adding 32 owned *data* bytes without additional
authored CODE credit. The complete 1,561-byte code+table SHA256 is
`6434768fdb2a0e649341109308e49032782d6166d136b41972aa002e72095eab`.
Both tables point to original case entry addresses
`0042E9C9/0042E9E2/0042E9FB/0042EA14` and
`0042EDA5/0042EDBE/0042EDD7/0042EDF0`.

`src/ResultSceneAdvanceF244.cpp` implements the whole original x86
control flow in natural pinned VC7.1 `/Od /GX-` C++. It does the genuine
result-scene poll `0042F450`, virtual slot-two redraw, already accepted
Graphics::Present, score-accounting paths (including three sequential
integer-times-float FILD/FMUL/ftol conversions), two four-way bonus
multiplier switches with independent native double constants 0.5, 1,
1.5 and doubling, five actual halfword animation resets, scene/global
actor score totals, unsigned best-score comparison and all real replay,
continue and special-stage scene-exit return codes 0x2205/0x2207,
0x1108 and 0x2301. The second half reproduces the original x87 alpha
fades, saturated byte opacity, 30/60/90/120/180/300 tick score phases,
manual 6-step score drain, modulo-three sound ticks and actor updates.
The complete game scene and sound object nominal C++ types are unproven;
all accesses are pointer-only observed offsets. External callee code and
existing exact result renderer functions receive no duplicate credit.

The **first natural whole-code probe** compiled to the correct 1,529
CODE +32 table byte size, all 74 actual COFF fields and 1,255/1,265
non-field bytes. An independent capstone instruction alignment showed
the only different *unmasked* bytes in three compare/test sequences:
(1) unsigned actual actor score > saved best; (2) native signed frame
>= replay threshold; (3) remaining pending result score > per-frame
step. Writing these as the source's equivalent reversed comparisons
restores the native register and operand order, all ten byte differences
and the full 1,561-byte structural proof. **All 1,265/1,265 non-field
bytes and 74/74 COFF relocations match**, including eight DIR32 jump
table entries. The targeted independent cold replay, repeated once after
reconciling `units[].functions` with the existing R065 name, returns
**exact: 1529**. No all-unit cold replay occurred.

`tests/test_result_scene_advance_f244.py` guards whole native code and
comparison SHA256, all eight real table destinations, all 66 code and
eight data relocation positions, preserved original source hash and
existing source role annotation. All native disassembly, first/best
probes, entire instruction diff and cold logs are retained in
`.analysis/f244-result-advance/`. No fake locals, target byte grafts,
assembly, masked fields, truncated function or externally accepted
Oracle receipt is claimed; the 97 unknown-origin cases are unchanged.


## F245: result-list input poll, 220-byte full cold exact

The R053-reviewed `ResultListScene::PollInput` at
`0042F450..0042F52B` is **220 original CODE bytes / 60 decoded x86
instructions**, native SHA256
`c6c63048374ca1109839baa4dce442cd6b38ffa10a8ec2a80cc104d11cae05ea`.
The natural `src/ResultPollF245.cpp` precisely recreates both physical
input initialization calls `00403E50` and `00403F40`, clears the actual
scene+0x0C/+0x0D flags, updates distinct original controllers
`00671638/00671680` through `00406E80`, and handles all four native
pairs of 32-bit button states and exact exit combination of physical
key codes 0x1C, 0x38 and 0xB8 through `00407170/004018A0`.

First normal pinned MSVC7.1 `/Od /GX-` source compiles to **220/220
complete CODE bytes with 136/136 nonrelocation bytes and 21/21 actual
COFF relocations**. The independent single-unit cold replay of only
`result-list-scene-poll-input-0042f450` returns **exact: 220**. It is a
separate native callee of the previously accepted 1,529-byte F244 result
scene main loop, so caller and callee code are not double counted.
`tests/test_result_poll_f245.py` pins original native PE code SHA, all
21 relocation positions, two devices, four global state pairs and the
source hash, without recompiling older units. Complete native disassembly,
first natural source and preview/cold evidence are retained under
`.analysis/f245-call-chain/`. There are no target-byte grafts, masks,
ASM, fake locals, cropped function or external Oracle claims. The 97
unknown-origin entries remain unresolved and uncredited.


## F246: whole character-name entry update with 16-bit cursor math cold exact

R040 classifies `NameEntryScene::UpdatePlayer` at `0042A340..0042A55C` as
authored. It contains **541 CODE bytes /151 original x86 instructions**,
SHA256 `a8e48f26ffb990e03b5420dd7f1be9cac608b81502f89c902c9883f299c955da`.
The natural `src/NameEntryUpdateF246.cpp` uses physically observed input
fields +0x10/+0x12/+0x14/+0x16 and player signed index +0x120, and
original external record storage at this+0x0C. It handles a 26-wide
selection grid, special 0x5B erase and 0x5C confirm actions, actual
8-character field writes in +0x55C/+0x563 per-player blocks (16-byte
stride), sound cues at `004079C0`, native progress-card file save
`004169E0`, reload `00416E80` with original `006718F8` receiver and
flag `006714CE`, and both early return codes 0x2207 and 0x2202. Its
final path invokes the native virtual scene draw slot two, then accepted
Graphics::Present before returning 10.

The first complete source compiled to 539 bytes, otherwise identical at
instruction level, because `FIELD(short,0x14) = FIELD(short,0x14) +/- 1`
promotes to signed 32-bit register arithmetic in VC7.1. Genuine 16-bit
prefix `++FIELD(short,0x14)` and `--FIELD(short,0x14)` compile to native
`MOV DX,word; ADD/SUB DX,1` instead. The full native control flow and
all position offsets then exactly match: **541/541 CODE bytes, 497/497
non-field bytes and all 11 physical COFF fields**. Independent targeted
`replay-exact-units.py --unit name-entry-scene-update-player-0042a340`
reports **exact: 541**. The existing progress-card Save/Load callees
remain separate origin-reviewed but *unmatched*, receiving no additional
source/code credit from their newly accepted caller.

The native instruction listing, original and corrected normal sources,
comparison and independent cold logs live under `.analysis/f246-name-entry/`.
`tests/test_name_entry_update_f246.py` guards whole original PE code,
16-bit arithmetic instructions, 11 actual relocation destinations and
accepted source SHA without broad cold builds. A separately investigated
588-byte `FighterState::ReleaseResources` at `00456910` has genuine
member auto-destruction and VC7.1 EH state transitions; it remains
**unaccepted** because no full natural exact source has yet been proven.
The raw original listing is in `.analysis/f245-call-chain/`. No masks,
target-byte grafts, invented ABI, fake locals, cropped returns or remote
Oracle receipt are claimed, and all 97 unresolved origins stay pending.


## F247: score.dat persistence written in five native segments (297-byte exact)

The original R053 authored `ProgressRecords::SaveScoreFile` at
`004169E0..00416B08` is **297 complete CODE bytes and 97 native x86
instructions**, SHA256
`22aab794c8dac7641616adb23fef3eabc413de8fec2c2e42d624a7a84cde2847`.
The normal C++ source `src/ProgressSaveF247.cpp` owns no invented
record object, but borrows the native `this` pointer and the actual
original `score.dat` string at `006579A8`. It uses Win32 CreateFileA
(GENERIC_WRITE, CREATE_ALWAYS), SetFilePointer, and five real sequential
WriteFile calls, then CloseHandle, preserving original file format:
(1) 0x16710 bytes from record start; (2) eight bytes at +0x16A94;
(3) 900 bytes at +0x16710; (4) 40 bytes at +0x16A9C; and
(5) 256 bytes at +0x16AC6. Prior to writing, 256 actual iterations
conditionally sample `rand() < 4096`; selected bytes at +0x16AC6+i
receive `rand()%256` using VC7.1's original signed remainder correction.
The external Win32 import and CRT rand implementations are **not**
separately credited.

The first natural `/Od /GX-` body compiled to **296** bytes: source
`if (file != INVALID_HANDLE_VALUE) { ... }` chose a single 6-byte
conditional jump. Original target uses the explicit failed-open
`if (file == INVALID_HANDLE_VALUE) return;` form, emitting 7 bytes
(short skip plus long exit). This natural semantic correction gives
**297/297 CODE bytes, 253/253 non-field bytes, all 11 physical COFF
relocations** with their original targets. Targeted, independent
`replay-exact-units.py --unit progress-records-save-score-file-004169e0`
reports **exact: 297**; no other cold units were built.

This completed save function is directly called by the previously exact
F246 541-byte name-entry controller. The earlier F246 note describing
SaveScore as unmatched is now superseded; the two distinct native
function extents are separately and nonoverlappingly credited.
The original complete native disassembly, first failed-source probe,
fixed normal source, relocation diagnostic and targeted cold log live
in `.analysis/f247-progress-save/`. It does not declare the full original
record owner layout, add failure robustness absent in the target,
mask field differences, fabricate locals, or claim external Oracle
acceptance. All 97 origin-pending functions remain uncredited.


## F248: complete short/long score loader and native local-variable scopes

`ProgressRecords::LoadScoreFile` at `00416B10..00416CD7` (R053) is
**456 original authored CODE bytes /154 decoded native x86 instructions**,
SHA256 `7d1129b0368244833fa32b710630cc3e4ed03a5392ea0fe40d2165511f442769`.
Its source `src/ScoreLoadF248.cpp` uses only observed record offsets, native
`score.dat` address `006579B4`, CreateFileA/GetFileSize/SetFilePointer,
10 physical ReadFile code call sites and CloseHandle. For files of size
`<=0x11170`, it reads the old 0xEF60 prefix and separate eight-byte header,
then loops over **10x10 entries**, reading four bytes each into the score
record at `+0x16710 + outer*60 + inner*4`, then 40-byte metadata and
256-byte suffix. Larger files read five native segments (0x16710, 8,
900, 40, 256) corresponding to independently exact F247 SaveScoreFile.
The full record owner type remains unknown and is not instantiated.

The initial normal VC7.1 code had the correct 456-byte extent and all 15
relocation targets, but 371/396 non-field bytes matched; actual `HANDLE`
and DWORD locals landed at incorrect offsets. A genuine scope containing
**DWORD bytesRead and DWORD fileSize** with `HANDLE file` remaining outside
reproduces the native handle EBP-4, output count EBP-8, and file size
EBP-0xC, restoring **396/396** non-field bytes, all **15 real fields**,
and an independent single-unit cold replay **exact: 456**. Variants and
original disassembly are retained in `.analysis/f248-archive-write/`.
No invented stack padding, masking, inline assembly, foreign callee-byte
credit, incomplete code acceptance, or all-unit cold replay occurred.
The 97 origin-pending candidates remain unchanged.


## F249-F251: archive boss negatives and exact whole shared name editor

The R052-authored `DataArchive::Write` at `0041D260..0041D50D` is
686 complete native bytes, with 228 independently decoded instructions
and 28 authentic COFF fields. A natural source models Win32 output/file
handles, true four-byte VC7.1 borrowed list iterators, 108-byte entries,
original rolling XOR index header, file copy and deallocation. It already
produces the **full 686-byte extent** and all 28 relocation targets, but
only **482/574 non-field bytes** matched first. Rewriting source XOR as
true read/modify/write yields 495/574, while real declaration/scope
experiments still leave native MSVC stack slots unmatched. All negative
controls and original 228-instruction listing are retained in
`.analysis/f249-archive-writer/`. No acceptance or authored byte credit.

Similarly R052-authored `DataArchive::OpenAndReadIndex` at `0041D510`
has a genuine 429-byte body with `/GS`, ten relocations, 108-byte wire
record and copy into the physically observed 100-byte name plus two
metadata dwords. The natural C++ source matches the whole function
length and all external destinations. Changing `memcpy` to real `strcpy`
plus retaining the genuinely distinct decoded-buffer pointer reproduces
the full 429 bytes. Sharing the actual XOR/entry iteration index and
expressing byte XOR without promoted compound assignment improves the
nonfield comparison to 366/389. Declaration-order permutations and
real nested lifetime experiments were negative, preserved under
`.analysis/f248-archive-write/`. No exact adoption or source credit.

The independently R040-authored `NameEntryScene::UpdateShared` at
`0042B380..0042B56D` is **494 whole native CODE bytes / 143 instructions**,
original SHA256
`8ba26f2d27a8279ca52a9811ebdb7aa664726253349d2de6255a11f3ca75f1f0`.
The natural `src/NameSharedF251.cpp` preserves original poll at
`0042BCD0`, input short fields +0x0E/+0x10/+0x12/+0x14/+0x16, mode
flag +0x0C, native 26-column selection code, erase 0x5B and save 0x5C,
the two **distinct** physical globals `00671858/0067185F`, genuine
16-bit cursor increments/decrements, original sound and conditional
progress SaveCurrent call at `004138E0` on `00671750`, real virtual
draw dispatch, accepted Graphics::Present and return values 0x2202/7.
The first source emitted 492 bytes because it placed final early-return
branch code before the reset block; the actual positive edit-if with
else return makes VC7.1 emit native JNZ/JMP ordering. The entire 494-byte
function compiles to **430/430 non-field bytes with all 16 COFF fields**
and independent single-unit cold replay
`--unit name-entry-scene-update-shared-0042b380` reports **exact: 494**.
`tests/test_name_shared_f251.py` guards the native SHA, all actual
relocations and accepted source digest without broad cold builds. Source
names and complete original parent layouts are inferred and no external
callee bytes, unknown-origin code or Oracle verification are claimed.


## F252/F253: native cardfile encoder and four decimal painters cold exact

Five independently reviewed authored functions were cold-replayed **one at a
time** against the pinned TH075 PE. All original function extents are whole,
nonoverlapping and retain their own physical COFF relocation fields:

* `CardList::EncodeCharacterFile` (`00431D60`): 432 CODE bytes / 15 COFF
  fields, native SHA256
  `7260a159f1b3d592a52ace497f27a83264ac4b44321806b2681494bff65ea2ab`.
  A previous natural 450-byte source was incorrect; the retained
  `src/CardEncodeF252.cpp` uses the observed 260-byte filename buffer and
  meaningful local scopes. The exact body preserves original pathname
  formatting, Win32 read/write/close, conditional failure branches, the
  full native cumulative 8-bit XOR key/step loop, and the GS cookie check.
  All 432 bytes and 15 relocation destinations cold replay exact.
* `MusicRoomScene::DrawNumber` (`00427180`): 377 bytes / 9 fields, original
  SHA256 `8063f13302db50d2849318f67155f3e7b4a49e5af78a46312814af2c461659c5`.
* `ReplayScene::DrawNumber` (`0042AE70`): 377 bytes / 9 fields, original
  SHA256 `d0861536a0d25c2ad32eeca09c0de0a2d2d0177f0c6702c90309d27b4acb5295`.
* `ReplayScene::DrawSlotNumber` (`0042BFD0`): 377 bytes / 9 fields, original
  SHA256 `d69ae88f62db4d39274c7289cc25a5b9460aca29e7b276272cfc380e15835d04`.
* `ResultScene::DrawCounter` (`004315F0`): 377 bytes / 9 fields, original
  SHA256 `382a5bed703c2eb0ef616aeb08a96edfd4b90c92b8caa4bd768e094d9c4270f6`.

The four digit painters build the real 132-byte SpriteQuad and 16-byte RECT,
have actual 5-argument `thiscall` stack cleanup, preserve both fixed-digit
and variable-digit signed divide-by-ten loops, and retain the original
DrawQuad/TranslateQuad/Win32 SetRect calls. The atlas glyph width is **15 px
for music and 19 px for replay/result**, while the physical region heights
are respectively 16 px and 20 px. The initial independent probes used
heights as width and had six non-field differences each. Correcting these
actual native atlas widths yielded **341/341** comparable nonrelocation
bytes and **9/9** real fields per complete 377-byte function.

All five untracked sources and pre-existing match-unit candidates were
inspected, kept and independently cold-replayed exact, then promoted to
protected ledgers with original authored origin IDs R041/R043/R052.
`tests/test_digit_family_card_f253.py` checks the original full-PE SHA256
and actual relocation positions and source hashes with no all-unit replay.
The exact build logs are in `.analysis/f253-digit-family/`, previous
negative experiments for the encoder in `.analysis/f252-cardfile/`.
Separate larger `DataArchive::Write` (686) and `OpenAndReadIndex` (429)
are **not** exact or credited; all original negative controls remain.
No hand-authored instruction bytes, masks, dummy locals, truncated CODE
extents, additional original class ABI claims, or remote Oracle acceptance.
The 97 pending origins remain unchanged and uncredited.


## F254-F256: exact nonvirtual result-scene resource loader; large sprite negatives

F254 re-opened `SpriteScene::RenderMirroredNode` at `00410A00`, an R035
authored **1,268-byte boss** with 324 complete x86 instructions, two
physical 132-byte SpriteQuad values, RECT, true x87 mirror/rotate/scale,
tinted sprite dispatch and camera offsets. A fresh whole-function C++
source matched its decoded instruction count but initially emitted 1,208
bytes; faithful float-bit call façades and inline coordinate expressions
generated 1,279 bytes, still not exact. Twenty-four permutations of
real SpriteQuad, camera offset, color and tint lifetimes did not restore
the original physical quad stack allocations. All negative sources and
original native listing remain in `.analysis/f254-sprite-boss/`; zero
CODE credit was assigned. F255 independently reproduced the original
429-byte `CardList::LoadCharacterFile` whole 118-instruction control flow
using authentic file APIs, pointer deque operations and line splitting;
real while-style loop lowered 476 to 447 bytes, still not exact. Multiple
real lifetime/decl-position probes stayed 447 bytes, retained in
`.analysis/f255-card-plain/`, also without credit.

F256 accepts the R043-author-authored whole
`ResultScene::LoadSelectedCharacterResources` at `00430EE0..0043106D`:
**398 original CODE bytes / 91 x86 instructions**, full PE SHA256
`5e335e9c40caebccc9c80d2b15cceda1691bda2981fdeec78302ad2992627836`.
The first natural source incorrectly declared the old resource destructor
`virtual`, generating an indirect vtable dispatch, and hoisted the card-list
index into a local ahead of its two branches. Native disassembly showed
**direct nonvirtual scalar deleting destructor `00425460`**, and the two
branches independently form the original signed selected-character index
multiplied by 20 and added to `006714D8`. Reverting to a native
nonvirtual destructor and expressing both actual index calculations
restores **398/398 CODE bytes, 318/318 non-relocation bytes and 20/20
real COFF relocation fields**. It preserves real `/GX` handler `00655A53`,
GS cookie/check, `new(80)` texture carrier/constructor `0040AD80`,
AllocateUnformattedSlots(1) `0040B1D0`, actual `0040BB80` archive load
with original character filename and data root, and both special and
normal encoded-card source paths. A separately pinned cold replay of only
`result-scene-load-selected-character-resources-00430ee0` reports
**exact: 398**. The complete original game class layouts remain
unproven; the called encoded-card reader `00431B60` has no independent
CODE credit yet. One-off original-PE/source guard research was archived privately under
`.analysis/f256-resource-exact/one-off-source-guard-test.py`; canonical unit
replay and manifests now carry acceptance, and the native listing and F256 cold evidence
are retained in `.analysis/f256-scene-lifecycle/` and
`.analysis/f256-resource-exact/`. No masks, fake locals, byte grafts,
truncated function, whole-unit replay or external Oracle receipt.


## F257: exact whole music-catalog file encoder and shared big-loader implications

The R179-authored `MusicRoom::EncodeCatalogFileAt00427300` spans the **complete
298 native CODE bytes** `00427300..00427429`, with **100 independently
decoded original x86 instructions** and the final original RET. Original
SHA256 is `6416b879c7408c9c4fa5e165efc6323dec408f61cf939fa50936bc2daa93aff1`.
No jump table or separate data is owned. This function performs the original
`musicroom.csv` CreateFileA/GetFileSize/read path, closes the source handle,
creates `musicroom.dat`, applies its byte-XOR stream with initial key 0x5C,
delta 0x5A and subsequent delta increment 0x3D, then writes, closes and
frees the allocated buffer. Both original INVALID_HANDLE_VALUE exits remain.
The observed native allocation call is ordinary operator new at `006416A2`,
with a genuine stored allocation pointer at EBP-0x1C and the separately
transferred stored content pointer at EBP-0x10; the observed cleanup is free
at `0064169D` with a distinct native temporary at EBP-0x20.

A first whole natural C++ probe compiled into 298 bytes and all 11 true
relocation locations/targets but matched only **222/254** non-relocated
bytes. Native-guided nested lexical scopes restored `HANDLE` EBP-4, transfer
count EBP-8, file size EBP-0xC, content EBP-0x10, key EBP-0x12, delta
EBP-0x11 and index EBP-0x18. Explicit physical allocation and cleanup
pointer transfers, both actually used, restore the final two original slots
without fake locals. The complete pinned VC7.1 `/Od /GX-` source now
compares **254/254** bytes with all **11** genuine DIR32/REL32 fields and
independently cold-replays **exact: 298** with only
`--unit music-room-encode-catalog-file-00427300`. Source is
`src/MusicCatalogEncodeF257.cpp`, original negative probes and comparisons
remain at `.analysis/f254-music-file/`. Original complete MusicRoom scene
layout and original C++ spellings are still unproven; no allocator or CRT
callee bodies gain authored CODE credit. Local replay is not an external
Oracle acceptance.

The adjacent `MusicRoom::LoadCatalog` boss (`00426DD0`, 916 CODE plus 16
switch-table bytes) also calls operator new and free and has previously been
blocked by significant incorrect local stack slot allocation, even with
a correct total code size and 18 relocations. The F257 observation is an
independently demonstrated compiler scope/temporary-pointer mechanism, **not**
proof of a corresponding original large-loader declaration layout. This was a provisional lead at F257, **not yet accepted** at that point.
F258 independently revisited the full native function and later accepted it
without transplanting F257's exact scope graph as an assumption.


## F258: complete 916-byte MusicRoom catalog parser boss plus exact switch table

Target Ghidra read-only boundary `00426DD0..00427163` is 916 bytes, with a
plain RET at `00427163`. Native CODE SHA256:
`3df59d06537c81eb8d58af1a193eafdab1035d96204384244e8250b949cf294a`.
The post-RET `00427164..00427173` is a genuine 16-byte owned four-entry
switch table targeting `00426F55`, `00426FA6`, `00427020`, `0042709A`.
Original *complete* 932-byte CODE+table SHA256:
`1a5816e578f8af00aa4a14dc6ad0b4c0998c7539e5a46985422793cedf9c3017`.
The four table entries are physically compared and relocated but **not
credited** as authored CODE; 916 bytes is the entire function credit.

The independently R066-authored function is a true high-level controller:
archive directory lookup `0041CF00`, entry open `0041D800`, ReadFile,
byte-XOR decoding with initial key 0x5C and delta 0x5A (delta += 0x3D),
parser cursor with quoted fields, newline/comma handling, numeric byte
accumulation, four 16-byte-stride record-column cases, three allocated
record strings, `memcpy`, and final free. It has 282 original x86
instructions, 14 actual in-code relocation fields and four table-pointer
fields. Library and external archive callees are not independently credited.

Independent historical F236 whole C++ candidate emitted correct code and
table sizes and 18 valid fields but had **744/860** comparable non-field
bytes, owing to an incorrect 0x50-byte frame and many real stack variables
in wrong slots. Instead of guessing previous scopes, F258 built a complete
physical lifetime graph from original signed/unsigned native accesses and
real variable lifetimes (`HANDLE`, read count, file size, parser cursor,
quote, column, numeric bounds, string temporaries, decoded-byte buffer and
free alias). It newly restored the native 0x48-byte frame and **852/860**
comparable bytes without altering real behavior. Precisely eight residual
bytes were four real EBP local offsets, each used twice: first three
string allocations and the final buffer cleanup pointer. Separate
meaningful C++ variables for all three original `operator new` results
(`allocatedName`, `allocatedTitle`, `allocatedExtra`), assigned to their
actual per-column destination fields, reproduced native -0x30, -0x34 and
-0x38 allocation temporaries and the final -0x3C release alias. One-by-one
controls improved 852 to 854, two improved to 856, and all three restored
**860/860** compared bytes in the native **932-byte** comparison extent.
The exact VC7.1 `/Od /GX- /GS /Gy` probe is preserved in
`.analysis/f258-music-catalog-alloc/RecordAlloc-all.cpp`, with the original
negative source, per-variant compiler diagnostics, the fresh Ghidra boundary
query and relocation compare receipt. The accepted translation unit is
`src/MusicCatalogLoadF258.cpp`.

Full canonical unit `music-room-load-catalog-00426dd0` declares
`size = 916` and `compare_size = 932`, covering the complete tail and
all **18 physical COFF fields** including four owned dispatch entries.
A new cold rebuild of **only that affected unit** separately reports
`exact; 916 coverage bytes`, confirming that matching observed C++ structure
and relocation targets persists without reuse of a previous COFF probe.
Original full class identities/record layout and naming remain inferred;
no byte masks, truncated extent, target grafts, artificial stack padding,
unused locals, fake returns, assembly, or whole-unit replay were used.
Local Git/VC7.1 cold replay does not establish external Oracle acceptance.
The 97 unresolved origins remain excluded from authored coverage.


## F259: exact complete replay-record loader and compiler-created short conversion

R035-authored `ReplayRecords::LoadRecord` (`00413AC0..00413DD7`) has
**792 complete CODE bytes**, **274 native x86 instructions**, and RET 4
at `00413DD5`; original full CODE SHA256 is
`9098d7133138719d630e6de50d698ba21db2689223402ac81cc0e4dab6aaac22`.
The target has **29 physical COFF relocation fields**, including real
Windows file APIs, four deque/list `Clear` targets, four typed `Push`
targets, signed record indexing and final CloseHandle. All real control
flow, 11 initial fixed reads, four count reads, signed input slot index,
four independent element iteration loops and native field offsets from
+0x144 through +0x190 are preserved. No extra failure checks are invented.
The source only borrows observed interfaces; complete original types and
record layouts are not asserted or credited.

Historical whole F216/F233 natural C++ controls emitted the correct full
792 bytes and 29 fields but matched only **639/676** comparable bytes.
Instead of repeating 57 variable-name sweeps, F259 first independently
reconciled the native stack: `i` at EBP-4, dword item at EBP-8,
unsigned raw word at EBP-0xC, count at EBP-0x10, file handle at
EBP-0x14, single-byte temporary at EBP-0x15, and ReadFile transfer
count at EBP-0x1C. A nested *real* scope/lifetime graph for those
variables recovered **674/676** comparable bytes, including the entire
0x24-byte frame and correct native `this` at EBP-0x24.

The last two mismatches belonged to the **compiler-produced signed-word
reference temporary**, not a missing synthetic source variable. The PE
reads two bytes into the actual `unsigned short` local at EBP-0x0C,
copies its bits into a distinct `short` at EBP-0x1E and passes its
address to the real `00414640` list helper. Initially declaring a manual
`short shortItem` emitted the same instructions but placed that explicit
local at EBP-0x20. Reconstructing the real operation as
`Push(static_cast<short>(rawWord))`, with the borrowed callee signature
`void Push(const short&)`, produces the original temporary at EBP-0x1E,
without a manually declared fake local or a misdeclared ABI.

The complete natural VC7.1 `/Od /GX- /GS` source
`src/ReplayRecordLoadF259.cpp` matches **676/676** nonrelocated bytes and
**29/29** actual relocation offsets/types/destinations. Only the new
`replay-records-load-record-00413ac0` match unit was independently
cold-rebuilt and reported **exact: 792**. Historical complete controls,
the new meaningful lexical-scope experiments, Ghidra boundary, exact
comparison and cold receipt remain under `.analysis/f216-archive-record/`,
`.analysis/f233-record-scope/` and `.analysis/f259-replay-load-lifetimes/`.
Original class identity and all 97 pending origins remain unknown where
not proven; no extra bytes are credited for library/CRT or neighboring
functions. No target-byte patch, assembly, false padding, fake returns,
truncated extent or all-unit cold replay. A local checkpoint does not
constitute an external Oracle receipt.


## F260: cold-exact complete result scene input polling controller

The independently R043-authored `ResultScene::PollInput` at
`00430D80..00430ED6` is 343 complete CODE bytes and 84 original decoded
x86 instructions with a plain RET at `00430ED6`. Native full CODE SHA256:
`c87ce04c274900402920b1929b3e3c03e079f5124fd0e8e64f0d76f67be35a3e`.
Ghidra read-only function, complete native assembly and decompile are
retained privately under `.analysis/f260-result-poll/`; the instruction
sequence was checked independently of Ghidra's provisional names.

The function calls original game-frame beginning/end `00403E50` and
`00403F40`, zeros scene bytes at `this+0x1BF..0x1C2`, and polls the two
actual global input objects based at `00671638` and `00671680` through
`00406E80`. It compares original signed 32-bit key-axis globals
`00671664/68/6C/70` and `006716AC/B0/B4/B8` against both +1 and -1
as actually present. The four native `00407170` key-state calls receive
original values 1, 0x1C, 0x38 and 0xB8; the final window-mode callback
`004018A0` retains the exact conditional short-circuit structure.
Only a borrowed input-frame interface is declared; neither a fabricated
input object layout nor a complete original scene type is instantiated.

A first complete natural C++ source
`src/ResultPollF260.cpp` with independent global references and the
actual guard structure compiled into the target's **exact 343 bytes**,
**235/235** comparable nonrelocation bytes, and **27/27 genuine
COFF relocation offsets/types/native destinations** under pinned VC7.1
`/Od /GX- /GS`. An independent cold rebuild of **only**
`result-scene-poll-input-00430d80` reports `exact; 343 coverage bytes`.
No source masks, fabricated object ABI, assembly, target byte grafts,
fake locals or extra fault branches were needed. External callees, original
class identities and all 97 origin-pending functions remain uncredited.
No external Oracle receipt is inferred from the local Git checkpoint.

### Rechecked nonexact large-function lead

The prior F219/F232 handoff incorrectly presented **1,025/1,052** as the
whole-repository best for the original **1,252-byte** replay append boss
`00413DE0`. Independent file inspection established a retained full-size
F225 source control `.analysis/f225-big-functions/F219LocWBeforeAll.cpp`
with the same 50 authentic COFF fields and **1,033/1,052** nonfield bytes.
All remaining 19 comparable differences are genuine 8-byte iterator
local slots, including native ByteIterator first/WordIterator first
placements and DwordIterator constructor slots; no exact acceptance or
extra CODE credit follows. The historical first two candidate phases
may report 1,025/1,052 as their *phase-specific* best but should not
override this later actual source/JSON observation. Preserve both
complete negative sources.

The battle scene destructor at `0043B0B0` was also revisited against
the native 248-byte whole function and original 12 relocation fields.
Nested actual cleanup pointer scopes still produce 189/200 bytes; a
real named texture deletion alias emits 254 instead of 248 bytes, and
therefore cannot be exact. These new negative controls are retained at
`.analysis/f260-battle-lifetimes/`. No unverified ownership or
byte credit is claimed for the destructor.


## F261: complete native music-record construction/destruction (2 cold-exact units)

R236-authored music-record helpers at `00427430..00427461` and
`00427470..004274C1` have full Ghidra-reviewed boundaries, with 50 and
82 original CODE bytes respectively, 16 and 30 native instructions, and
no owned jump tables. Constructor full SHA256:
`1d2aef7cb1e15914180d9063cbe3f872c1d108a9237ea596af94ebf396292d12`;
destructor full SHA256:
`2c34ab0bdbe8a9d8c3ebed966343a4cc332572bef47bea23ce7c93c6f01cdb64`.
The original music scene creates/destructs **60 records of stride 16** via
the standard VC7 array lifetime machinery. An actual record has signed
byte count/index at +0, three individually owned character pointers at
+4, +8 and +12, and naturally supplied alignment. The independent 50-byte
constructor initializes precisely these four native fields, returning this.
The destructor resets the count and calls real `_free` 3 times, with
a 16-byte stack frame: distinct real release temporaries at EBP-4, -8
and -C, original `this` at EBP-10. Declaring all three release pointers
up front produced 38/70 comparable bytes due to call/stack ordering.
Meaningful separate release scopes, each preserving actual source pointer
lifetimes, yield the entire **70/70 nonrelocation** bytes and **3/3 physical
REL32** calls to native CRT free at `0064169D`.

One exact shared translation unit `src/MusicCatalogRecordF261.cpp` plus
`src/MusicCatalogRecordF261.hpp` declares a natural 16-byte type, rather
than a padded invented owner; only observed data and behavior is present.
The constructor reproduces **50/50** bytes and has **zero relocations**.
Both complete functions independently cold-replayed exact together as
`music-catalog-record-constructor-00427430` and
`music-catalog-record-destructor-00427470` from one fresh pinned VC7.1
`/Od /GX- /GS` object. These 132 CODE bytes do not credit any array helper
implementation or establish the whole parent MusicRoom scene layout.
The 97 unresolved origins remain uncredited. Native listings and negative
compiler variants remain private at `.analysis/f261-music-record/`. No
target grafts, assembly, invented padding or full cold replay.

The larger R035 `SpriteSequence::RenderElements` target at `00411110`
(746 bytes, real `RET` at `004113F9`) was also independently inspected. Its
actual `0xBC` frame contains a complete 132-byte SpriteQuad, 16-byte RECT,
list iterators, one signed cycling counter, x87 translation and guarded
blend/tint/scale dispatch. A natural whole-function source is retained as
`.analysis/f261-sprite-sequence/SequenceRenderF261.cpp`; the first probe
emitted 717 bytes with a 0xC0 frame, so no exact claim or added CODE
credit. The next investigation must reconcile physical local lifetime and
branch lowering, not merely trust the Ghidra decompile or truncate extent.


## F262: complete exact music scene constructor (372 native bytes)

Original R052-authored `MusicRoomScene::Initialize` at `00425750..004258C3`
contains **372 complete PE CODE bytes**, 105 independently decoded
x86 instructions ending in RET at `004258C3`, and original code SHA256
`1c90a806836924c60ecb3d0ac46e8177975f346538c473c1a3251c5f19223fe2`.
A read-only Ghidra function/decompile/native instruction audit independently
confirmed its full EH-backed scope and own exits. The scene base
constructor `004251C0` is separately R108 origin-unknown and **not**
independently credited merely because the caller's REL32 destination
matches. The original parent class name and complete source declaration
remain provisional.

The original constructor uses a standard VC7 array constructor helper
at `00641C78` on **60 real MusicCatalogRecordF261 entries of size 16**
starting at `this+0x1C`; the constructor and matching destructor
`00427430` and `00427470` are both separately F261 cold-exact. It sets
the native 00657CB0 vtable, retains actual EH states and handler
`006557B9`, and performs genuine `new(80)` with physical temporary and
cleanup for texture object ctor `0040AD80`, original two-slot allocation
`0040B1D0`, and `0040BB80` resource load with native source/root strings
`00657BF4` and `00657BEC`. It issues the four actual graphics surface
allocations at `00401C20` for 512x512, 1024x1024, 512x32, 512x32
with depth 32 and observed `this+0xC/+0x10/+0x14/+0x18` handles. It
zeroes scene byte fields +0x3DE and +0x3DF, calls the separately accepted
MusicRoom catalog loader `00426DD0` plus native catalog text `00426670`,
track setup `00426A70` and selected title `004268A0` (both with 0),
then zeroes +0x3DD. Every original error/unwind path remains.

A first complete natural C++ constructor in `src/MusicRoomInitF262.cpp`
with physically observed 8-byte base boundary, four graphics-resource
handles, a **real** array of already reconstructed 16-byte records, and
observed state fields reproduced the whole target length **372**,
**280/280** comparable bytes, and **23/23 real COFF relocation**
offsets, types and destinations. An independent pinned VC7.1 `/Od /GX`
**single-unit cold rebuild** of
`music-room-scene-initialize-00425750` confirmed `exact; 372 coverage
bytes`. The whole C++ translation is not a claim that unknown private
MusicRoom, base or texture-manager identities/layouts are proven; no
unknown owned child, CRT array helper, base origin, or external callee
gets additional authored byte credit. The 97 pending origins remain
uncredited and the conservative denominator includes them. No target
byte copying, fake exception frames, assembly, arbitrary padding,
unproved virtual table reinterpretations, cropping or all-unit replay.
Private original native listing, source and cold receipt remain under
`.analysis/f261-music-init/`.


## F263: exact full MusicRoom destructor and real COM/record lifetimes

R236-authored `MusicRoomScene::ReleaseTexturesRecordsAndAudioAt004258D0`
is a full **244-byte** native destructor (`004258D0..004259C3`) with 77
original decoded x86 instructions and plain RET. Native CODE SHA256:
`a7845acf43805829124ad1776d22133e05be52feaed5ff72fbd6c4a474be4316`.
Ghidra read-only function and actual physical instructions were checked
independently of its provisional name or older R236 source controls.

The genuine routine installs physical scene vtable 00657CB0 and has
original EH handler 006557E1, then calls the **D3D8 COM Release slot 2**
on four owned handles at scene+0xC, +0x10, +0x14, +0x18. Their native
call sequence reads the vtable pointer, pushes the COM `this` and calls
`[vtable+8]` rather than making an ordinary C++ thiscall, so the natural
IDirect3DTexture8 `Release()` interface is materially important. It
then performs the original nonvirtual scalar deleting destructor
`00425460` on texture pointer scene+8, calls the real game audio
cleanup services `00407D70`, `00419CB0(40)`, `00419DF0`, and lets
VC7.1 automatically generate the **60-element, 16-byte stride** array
destruction on actual `MusicCatalogRecordF261` owned values. The compiler
uses original `_eh_vector_destructor_iterator_` at `00641D4A` with the
previously F261 separately cold-exact record destructor at `00427470`.
Finally the accepted scene base destructor at `00431F40` executes. No
other routine's authored CODE is double-counted, and the independently
origin-unknown base constructor remains uncredited.

The first complete native-grounded natural C++ source
`src/MusicRoomReleaseF263.cpp` generated the entire **244 bytes**, all
**196/196** original nonrelocated byte positions and **12/12** physical
COFF relocation offsets/types/native targets under pinned VC7.1 `/Od /GX`.
The manifest unit `music-room-scene-release-004258d0` was independently
cold-rebuilt and reported `exact; 244 coverage bytes`, without any
full-set replay. Its source and original read-only Ghidra/native/COFF
proof are retained in `.analysis/f263-music-release/`. The observed
physical scene fields and borrowed interfaces do not prove the complete
original scene type identity or any incomplete private owner. All 97
origin-pending functions remain uncredited. No target-byte graft, fake
stack padding, unknown callback implementation, asm, masked fields or
truncated machine-code comparison was used.
