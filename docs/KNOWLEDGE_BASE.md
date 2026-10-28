# TH075 reconstruction knowledge base — cumulative historical evidence

**Current snapshot: 2026-10-28, after F339.** This document is a
**chronological experiment log**, not the active backlog. Older F-series
sections describe observations *at that stage*; many statements such as
"still unaccepted" or "remain nonexact" were true **then**, but have
since been superseded. Do not use them as present-tense status. The
current compact [handoff](RE_HANDOFF.md), original pinned native
`resources/th075.exe`, and canonical ledgers outrank historical prose.

## Current authoritative status and superseded negatives

- **645 cold-exact authored functions**, **813,859 authored CODE bytes**,
  **41.24% reviewed coverage**, **41.16% conservative coverage**.
  These are a dated snapshot: always run
  `scripts/repo-python scripts/report-reconstruction-status.py --summary`.
- The original Japanese target version 1.11 SHA256 is
  `bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
  Review the source/origin/extent and original relocation evidence for
  each target. Local cold comparison is **not remote Oracle acceptance**.
- **F339 `DataArchive::Write` (686 CODE)** and **F338
  `DataArchive::OpenAndReadIndex` (429 CODE)** are both exact;
  F249/F250 negative results are historical.
- **F326 `ReplayRecords::AppendRecord` (1,252 CODE)**, **F328
  `ReplayRecords::FinalizeFile` (375 CODE)** and **F259
  `ReplayRecords::LoadRecord` (792 CODE)** are exact;
  F218/F219/F232/F272/F289 negative descriptions are historical.
- **F319 `FontSurface::RasterizeText` (1,766 CODE)** and **F318
  `FontSurface::LoadGlyphOutline` (301 CODE)** are exact;
  F291/F299/F302 negatives are historical. The 916-byte F258
  MusicRoom catalog boss and 1,722-byte F294 Effects catalog boss
  are also accepted at their *original complete CODE extents*;
  independently compared jump tables do not add CODE credit.
- Truly **nonexact** current work includes 746-byte
  `SpriteSequence::RenderElements` (best 599/614 nonfield bytes,
  33 real fields, three x87 load-order mismatches), 874-byte Suika
  special state (742/794), 276-byte two-side effect pruner
  (233/236), 497-byte character-cancel animation (438/445),
  1,268-byte mirrored sprite, and the 82,796-byte character move boss.
  Exact original addresses, proof directories and entry points
  are indexed in the [current handoff](RE_HANDOFF.md).
- All 97 origin-pending functions / 3,608 bytes are still uncredited.
  Do **not** infer full source class definitions from borrowed native
  call boundaries, or count Win32/CRT/VC7 helper code. Cold-replay
  **only new or affected units**, never the entire set.

## How to read the historical sections

The older "Current validation policy", "authoritative state" and old
handoff snapshots (e.g. **534 exact / 766,591 bytes**) were milestones,
not the current result. Their historical text remains accessible in Git
history, including `git show 26ac6fd:docs/KNOWLEDGE_BASE.md`.
Consult the accepted unit's `config/match-units.toml` entry and the
single-unit cold logs, or inspect the pinned native PE, to settle any
historical contradiction. Do not repeat a prior negative source-variable
sweep without a new hypothesis supported by original physical slots.

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

At the **F218 stage**, the adjacent 375-byte `ReplayRecords::FinalizeFile`
was unaccepted; **F328 later cold-accepted the complete function**.
The earlier natural sources retained the Win32 replay copy,
record header write, original 264-byte path and GS cookie;
full-body probes emit 342, 372, 384 or 396 bytes against 375.
No cropped body, fake stack padding or masked relocations are
counted. The 792-byte ReplayRecords load and 916-byte MusicRoom catalog parse
were likewise nonexact **at F218**, but were later independently
cold-accepted as **F259** and **F258**, respectively.
Their failed full-body controls are preserved privately.

## F220: two exact replay queue policies; large writer pending at F220

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
`ReplayRecords::AppendRecord` (`00413DE0`) was a complete
1,252-CODE-byte nonexact boss **at F232** (50 real relocation fields;
that stage best 1025/1052 nonfield bytes). The entire function is
**now independently cold-exact in F326**. In F232 we preserved all six real
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


## F236: music catalog full-function negative controls (later accepted in F258)

The independently R066-authored `MusicRoom::LoadCatalog` at `00426DD0`
was **unaccepted at the F236 stage**; its complete function was later
independently cold-accepted as **F258**. Native CODE size is 916 bytes, and the physically
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
and 28 authentic COFF fields. A natural source modeled Win32 output/file handles, true four-byte
VC7.1 borrowed list iterators, 108-byte entries, the original rolling
XOR header and file copy. **At F249**, its full 686-byte extent and
28 relocation targets matched but only **482/574** nonfield bytes;
the now-complete F339 cold-exact proof supersedes this negative. Rewriting source XOR as
true read/modify/write yields 495/574, while real declaration/scope
experiments still leave native MSVC stack slots unmatched. All negative controls and original 228-instruction listing remain
in `.analysis/f249-archive-writer/`. **No credit was taken at F249;
full independent credit was later earned in F339.**

Similarly R052-authored `DataArchive::OpenAndReadIndex` at `0041D510`
has a genuine 429-byte body with `/GS`, ten relocations, 108-byte wire
record and copy into the physically observed 100-byte name plus two
metadata dwords. The natural C++ source matches the whole function
length and all external destinations. Changing `memcpy` to real `strcpy`
plus retaining the genuinely distinct decoded-buffer pointer reproduces
the full 429 bytes. Sharing the actual XOR/entry iteration index and
expressing byte XOR without promoted compound assignment improves the
nonfield comparison to 366/389. Declaration-order permutations and
real nested lifetime experiments were negative **at F250**, preserved
under `.analysis/f248-archive-write/`. **F338 later independently
cold-accepted the entire 429-byte index reader.**

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
The separate `DataArchive::Write` (686) and `OpenAndReadIndex` (429)
were **not exact at the F253 checkpoint**, but are now independently
cold-exact as **F339 and F338**. All original negative controls remain.
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


## F264: exact 366-byte result-list scene constructor; signed loop guard

The independent R052-authored `ResultListScene::Initialize` has original
`0042F710..0042F87D` extent, **366 full CODE bytes**, 96 native x86
instructions ending in RET and PE-backed SHA256
`a14c5c094036156369be76dcb3d289928101271c4f068a1a56bf13fa98e0c49c`.
Ghidra read-only function, full native instruction listing, original
complete natural source and negative first comparison are retained under
`.analysis/f264-result-list-init/`.

The function invokes base scene ctor `004251C0` (R108 origin-unknown;
no independent authored credit) and the real 20-byte VC7 deque
constructor `00420320` on `this+0x18` (STL/library, also no authored
credit). It installs vtable `006581D0` with real exception handler
`00655A1E`, zeroes two resource pointers and EH-allocates one original
80-byte texture manager `0040AD80`, calls `0040B1D0(4)`, and loads
texture file/root strings at `00658064/0065805C` through `0040BB80`.
It allocates the 1024x512, 32-bit graphics surface via `00401C20`,
zeros observed scene flags +0x1C5/+0x1C3/+0x1C4 and short +0x1BC,
sets +0x1BE to five, and loops over exactly ten real progress selectors
calling the previously separately accepted authored `00419E10(
static_cast<unsigned char>(index), 1)` to write +0x1C6..+0x1CF.
It calls the independently F256-cold-exact character asset loader
`00430EE0` and F238-cold-exact result counter page builder `00431350`.
All original EH cleanup, resource and call ordering remain.

The first complete native-faithful pinned VC7.1 `/Od /GX /GS` source
`src/ResultListInitF264.cpp` emitted the entire **366 bytes**, all
**17 physical COFF fields** at correct offsets/targets, and **297/298**
nonrelocated matching bytes. At branch +0x128 the native target uses
**signed JGE** (`0x7D`) but the initial C++ guessed an unsigned 32-bit
loop counter and emitted **JAE** (`0x73`). Changing this genuine
program-logic interpretation to `for (int index = 0; index < 10; ++index)`
restored **298/298** bytes. This is an actual signedness correction,
not byte patching or artificial compiler control. A fresh cold build
of **only** unit `result-list-scene-initialize-0042f710` independently
reported `exact; 366 coverage bytes`.

The 20-byte deque carrier and borrowed 80-byte texture interface reflect
physical native allocations only; they do not establish unknown original
private owner/source declarations. All 97 pending origins remain unknown
and uncredited. The authored-byte count is now **789,436/1,973,516
(40.00%)**, while conservative pending-inclusive coverage remains
**39.93%**. The 98% goal is unfinished; no library/base/CRT extra bytes,
all-unit cold replay, truncated code, fake locals, assembly, relocation
masks or external Oracle receipts are claimed.


## F265: complete exact 229-byte ResultList scene destructor

The original R053-authored `ResultListScene::Release` at
`0042F880..0042F964` is **229 full PE-backed CODE bytes** with 68
independently decoded native instructions and a genuine plain RET at
`0042F964`. Original complete CODE SHA256 is
`18e1a2f05e860b1a87e7404f7ac454e867a31f74b60018e1f59f063c6e6ef998`.
Read-only Ghidra function/decompile and original physical assembly
remain under `.analysis/f265-result-list-release/`.

The real EH-backed scene destructor installs native vtable `006581D0`,
uses handler `00655A3B`, invokes original ClearEntries `00431940`,
conditionally deletes scene pointers +0xC and +0x8 through native
nonvirtual scalar deleting destructor `00425460`, and conditionally
performs a proper D3D8 COM slot-two Release for surface at +0x10.
Automatic VC7.1 member destruction emits the original **20-byte deque**
destructor at `00420420` for the physically observed member at +0x18,
then calls the previously independently accepted base scene destructor
`00431F40`. All original EH cleanup-state transitions are preserved.

The first complete native-faithful C++ source
`src/ResultListReleaseF265.cpp` (borrowed scene/texture interfaces, real
20-byte deque size, no copied target bytes) compiled into the **entire
229 bytes**, **189/189 comparable nonrelocation bytes**, and **10/10
authentic physical COFF relocation offsets/types/native destinations**
under pinned VC7.1 `/Od /GX`. The canonical unit
`result-list-scene-release-0042f880` was then independently rebuilt cold
without any full-set replay and reported `exact; 229 coverage bytes`.
Its paired F264 constructor is independently accepted, but this does
not establish complete original private scene, deque or texture source
layouts. The library deque destructor, game ClearEntries implementation,
CRT and origin-unknown R108 base constructor are **not separately**
credited. All 97 unresolved origins remain excluded; source uses no
masks, arbitrary padding, assembly, target grafts or truncated bodies.

The cumulative tracked whole-function exact state is **579 functions,
789,665 authored CODE bytes (40.01% of 1,973,516 reviewed)**, with
39.94% conservative pending-inclusive coverage. The 98% objective is
far from complete and local cold replay is not an external Oracle
verification receipt.


## F266: complete 395-byte ReplayPlayback scene constructor with three native deque lifetimes

R052-authored `ReplayPlaybackScene::Initialize` at `0042C3D0..0042C55A`
is **395 complete native CODE bytes**, 106 independently decoded x86
instructions ending RET at `0042C55A`, with original SHA256
`15f366e7ffebe90d8259e016606642e843753a37ebc324d1143eead1f0205160`.
Read-only Ghidra function, entire native instructions, decompile and
first full natural C++ source are retained under
`.analysis/f266-replay-playback-init/`. Its actual origin R052 is
independently reviewed authored; the invoked base constructor `004251C0`
remains separately R108 **unknown origin**, without new CODE credit.

The real scene vtable is at `00658008`, EH handler `00655964`, and three
physically distinct, naturally 20-byte VC7 deque owners start at +0x0C,
+0x20 and +0x34. Original constructor bodies `00420320`, `0042DB30`,
`00414360` are each independently classified **library**, not authored.
The explicit early deque Clear uses original `0041DF50`. The genuine
EH-backed `new(80)` texture manager calls constructor `0040AD80`,
`AllocateSlots(3)` at `0040B1D0` and default resource load `0040BB80`
using original replay.dat and datab strings at `00657FC0/00657FB8`.
The original two global actors at `00671418` and `0067141C` are each
conditionally deleted through true virtual deleting destructor slot
`vtable+0x14` and nulled, then the separately F231-cold-exact replay
directory scanner `0042D470` is called. It zeroes field +0x51, stores
the actual controller halfword from `0067162C` to +0x48, and sets
mode +0x4C to 5. All original EH states, nested conditional calls,
branch ordering, and unwind paths are retained.

The first complete ordinary VC7.1 `/Od /GX /GS` C++ source
`src/ReplayPlaybackInitF266.cpp` naturally compiles into **all 395
original bytes**, **299/299** nonrelocation byte positions, and **24/24
authentic COFF relocations**. One independently fresh cold replay of
unit `replay-playback-scene-initialize-0042c3d0` reported
`exact; 395 coverage bytes`. The three 20-byte owners and 80-byte
texture allocation carriers are native observed bounds, not a claim
of complete private original game class identity. External C runtime,
STL and unproven child implementations remain uncredited and all 97
origin-pending functions remain unknown. No byte masks, fake locals,
source-padding, assembly, copied target bytes or truncated compare.
The local checkpoint is not an external Oracle receipt.


## F267: cold-exact whole replay-owned filename destructor (265 bytes)

The R245-authored `ReplayBrowserScene::DestroyOwnedReplayFiles` at
`0042C560..0042C668` has **265 complete original CODE bytes**,
76 independently decoded original x86 instructions and plain RET at
`0042C668`. Entire native code SHA256:
`244c00ec00b86db59d8b7de103206a258cf97d91d89329a67c16c14cc070ea50`.
Its read-only Ghidra function/decompile and entire native instruction
listing were independently reviewed and retained under
`.analysis/f267-replay-release/`.

The function installs real replay scene vtable `00658008` and native EH
handler `00655997`, copies the actual 16-bit selected controller from
scene+0x48 to global `0067162C`, then iterates the owned filename
deque at scene+0x0C from `unsigned int index=0` while `index < Size()`
using native `0041DD50`. It calls actual element accessor `0041DDC0`,
fetches the owned `char*` from its result, materializes the real cleanup
local at EBP-0x14, and passes it to native `_free` at `0064169D` for
**every** file. It clears the deque using real `0041DF50`, conditionally
deletes texture manager at scene+8 through the nonvirtual scalar deleting
destructor `00425460`, and automatically calls the three original deque
destructors in reverse member order: `004143B0` at +0x34, `0042DB80`
at +0x20, and `00420420` at +0x0C, before the independently accepted
scene base destructor `00431F40`. The entire original EH cleanup state
sequence (3,2,1,0,-1) and return are preserved.

The first ordinary C++ translation unit
`src/ReplayPlaybackReleaseF267.cpp` (three naturally 20-byte member
objects, borrowed virtual scene/texture interfaces, no invented scene
layout) matched **all 265 bytes**, **205/205 nonrelocated bytes**, and
**15/15 real physical COFF relocation fields** under pinned VC7.1
`/Od /GX`. Canonical unit `replay-browser-destroy-owned-files-0042c560`
was independently rebuilt cold and reported `exact; 265 coverage bytes`.
The F266 395-byte constructor and separately accepted F231 file scanner
prove native companion calls but **do not** credit their CODE twice.
The true VC7 STL destructor/calculators, CRT, unknown R108 base constructor,
and unproven original game class layouts are not authored credit;
all 97 origin-pending cases remain excluded. No byte masking, assembly,
artificial padding, target grafts, cropped extents or all-unit replay.
Local Git commits are checkpoints rather than external Oracle receipts.


## F268: exact complete replay input controller and native sprite boss scope research

R053-authored `ReplayScene::PollPlaybackInput` at
`0042D330..0042D465` is **310 complete CODE bytes**, 84 original
x86 instructions ending plain RET, original SHA256
`1765a941c4f230bfe3b8627e5c0c9b84e9444d45fe7710e32ccade7f210ec2d6`.
Its actual observed four signed scene outputs live at +0x4D..+0x50.
It calls frame services `00403E50` and `00403F40`, original paired
input Poll `00406E80` for `00671638` and `00671680`, and six original
signed comparison groups on globals 00671664/68/6C/70 and
006716AC/B0/B4/B8. It uses four native `00407170` key-state polls
with arguments 1, 0x1C, 0x38, 0xB8, and only then the conditional
`004018A0` window-mode callback. All native short circuit branches,
negative-one bytes and original exception-free RET remain intact.
The shared underlying input behavior resembles separately F260-accepted
`ResultScene::PollInput`, but **its scene field offsets and native full
extent are independently distinct**; no blind duplicate label or code
credit was made. Source `src/ReplayInputF268.cpp`, canonical unit
`replay-scene-poll-playback-input-0042d330`. First full natural VC7.1
`/Od /GX-` source matches **202/202** nonrelocation bytes and **27/27**
original physical COFF fields. Only this affected unit was cold-replayed
and returned `exact; 310 coverage bytes`; all other already accepted
units and CRT/input helper implementations were not rebuilt or credited.
R053 origin evidence remains independently authored, with all 97 pending
origins excluded and no external Oracle receipt claimed. Private original
native, decompile, source and cold proof under `.analysis/f268-replay-input/`.

### F268 complete SpriteSequence boss: exact opcode flow but wrong locals

The R035-authored original `SpriteSequence::RenderElements` at
`00411110` is **746 complete native CODE bytes** and 198 instructions,
including a 132-byte SpriteQuad, 16-byte RECT, genuine 0xBC stack frame,
list traversal, blend switch, float translate, signed cycling counter,
three guarded x87 floating-point comparisons and scale/tint draw paths.
F261's earliest complete C++ probe emitted only 717 bytes and a 0xC0
frame. The separately reviewed native paths begin with two positive
condition checks followed by their own early `JNZ; JMP` returns; the
three scale tests are naturally expressed as short-circuit inequality
with original x87 global-left comparisons and a final JNP for the
unscaled draw. Explicitly scoping the **genuine iteration counter**
recovers native frame 0xBC. Combined, a subsequent full native-guided
source `.analysis/f261-sprite-sequence/Variant-GuardFloatReversed.cpp`
now emits **734 bytes, with 198/198 native-shaped instructions**.
No cropped body, target-byte insertion, fake locals or assembly was used.
The exact remaining 12-byte *size deficit* occurs at four original
6-byte EBP operand accesses which VC7 currently emits as 3-byte
short locals: native `end` iterator at EBP-0x9C versus current -0x10,
and native `x` coordinate at EBP-0x98 versus current -0x0C, each used
twice. The object already reproduces native `this` at EBP-0xB8, frame
0xBC, original iterator `it` at EBP-4 and real postfix iterator temp
at EBP-0xB4. Further meaningful lifetime scopes for end, x, y, quad,
counter, RECT and tint, including early declarations with unchanged
operation order, either retained 734 or worsened to 725/719/716/710
bytes. These negative controls and full instruction-shape report are
retained under `.analysis/f261-sprite-sequence/`. No source match unit
was registered and **zero additional authored CODE bytes** are credited
for this still-unaccepted large function. Next approach should reproduce
the true original end/x lifetimes through natural VC7 source structure
rather than masking four EBP offsets or inventing padding.


## F269: cold-exact whole replay scene constructor, score and path handoff

R052-authored `ReplayScene::Initialize` at `0042A180..0042A2BA`
contains **315 complete PE-backed CODE bytes**, 84 original decoded
x86 instructions and plain RET at `0042A2BA`, with native full SHA256
`ceff174afda54e83c640d523728a32defab2d3321ce070c20b7e4c2a70c5ab33`.
The original full Ghidra function/decompile/native x86 listing, initial
whole-source probe and independent cold acceptance are retained at
`.analysis/f268-replay-scene/` (the final source/artifact is numbered F269).

The real EH scene constructor uses handler `006558E3`, vtable `00657F64`,
original base constructor at `004251C0` (R108 origin **unknown**, no
authored CODE credit) and a genuine `new(80)` texture manager allocation
with native EH cleanup plus `0040AD80` ctor, `0040B1D0(3)` and archive
load `0040BB80` from original file/root strings `00657F4C/00657F44`.
It resets actual scene shorts +0x10/+0x12/+0x14, uses native two 8-bit
selection globals `006714C8/D0` to call `0041A1A0` on progress table
`006718F8`, retrieves selected working record via `0041A240` to scene
+0x0C, and calls `00416EE0` on that record using the original fighter
state field +0x2D0 from actor global `00671418`. It stores the returned
8-bit status at scene+0x120 and passes that to original profile selection
write at `00416E20`. Finally it invokes `ReplayRecords::FindAvailablePath`
`00414300` on authentic manager `00671750`, with output path buffer at
scene+0x1C and resulting selection index at +0x18. Full original call
ordering, genuine stack values and EH unwinds are preserved.

The first complete natural C++ probe compiled to **315 native bytes**,
**219/219** comparable nonrelocation bytes and **24/24 physical COFF
relocation fields** (correct native offsets/types and destinations),
under pinned VC7.1 `/Od /GX /GS`. After independently renaming only this
new source to `src/ReplaySceneInitF269.cpp` to avoid duplicate F268
acceptance, its full 315 bytes and all native fields remained exact;
canonical cold replay of *only* `replay-scene-initialize-0042a180`
reported `exact; 315 coverage bytes`.

F268 already separately accepted the matching 310-byte replay input
controller at `0042D330`. Its duplicate private natural-source probe
was content-checked against the prior experimental source and not re-added
to accepted authored coverage. Other game/library callees, unknown nominal
scene/actor/progress/texture layouts and the 97 unresolved origins
remain uncredited. Neither truncated code, target byte graft, arbitrary
layout padding, relocation masks, asm nor all-unit cold replay was used.
Local Git commits are not an external Oracle verification receipt.


## F271: cold-exact complete 1,185-byte projected D3D8 graphics boss

The independent R001-authored game-specific graphics function
`Graphics::DrawProjectedTexturedQuad` occupies original PE-backed CODE
`00402D50..004031F0`, **1,185 bytes** and **291 fully decoded x86
instructions**, ending in native `RET` at `004031F0`. Its original full
CODE SHA256 is
`dcda68d89e3a45c1464d845b321d7228b79a1e7e9290ea0470ed594768553769`.
Original read-only Ghidra whole-function/decompile/disassembly, complete
VC7.1 source experiments, instruction-shape and physical stack-slot diffs,
and cold receipt remain at `.analysis/f271-graphics-projected/`.

The routine takes a borrowed four-by-four-float source rectangle packet,
integer pixel rectangle, x/y/depth projection parameters, 32-bit tint
and original D3D8 texture pointer. It calls texture's actual COM
`GetSurfaceLevel(0, &surface)`, surface `GetDesc` to obtain original
`D3DSURFACE_DESC` dimensions, converts unsigned width and height to
floats (observed VC7.1 `FILD qword` sequence), releases the surface,
then handles **all four** original 28-byte `ScreenVertex` records. For
each vertex it computes a shared **actual `float projection` variable**,
tests its native less-than-two clipping condition and leaves the entire
function when clipping fails, calculates x/y and projected z from the
original x87 expressions and stores the real `rhw`, then computes the
rectangle's exact UV assignment. It applies native screen scale and
origin globals to both x/y for all four vertices. Optional tint
multiplication preserves source alpha, multiplies all three RGB lanes
using native global color scale, and invokes the real three per-lane
`__ftol2` conversions at `006406AC`. It sets all four vertex colors,
checks cached texture vs provided texture, calls real D3D8 device
`SetTexture` only when changed, then draws **D3DPT_TRIANGLEFAN (6)**,
two triangles of source stride **28** with `DrawPrimitiveUP`. The fan
is not D3DPT_TRIANGLESTRIP (5), despite a plausible first C++ draft.

First complete meaningful C++ source with inline per-vertex rhw had
**1,085** generated bytes, not 1,185. Changing the four native
clip conditions to genuine early returns (`if (projection >= 2)
return;`) restored the native JNE/JMP branch shape. More importantly
the original calculates projection into one **reused local** before
calculating/storing each vertex's rhw, instead of overwriting that
member immediately. Reconstructing this true data flow restored the
**entire 1,185 bytes and 291 instruction sequence**. A first fully
sized natural source reached **997/1,037** comparable nonrelocation
bytes, with 37/37 real COFF relocation locations and native targets.
Correcting the actual graphics primitive from strip to fan resolved
one genuine one-byte difference. The other 39 compared differences
were four original EBP-local slots, not extra work or hidden logic.
The native surface pointer lives at EBP-0x9C, converted width at
EBP-0x98, height at EBP-0x94 and shared projection at EBP-0xA0.
A nested **real** lexical scope delimiting the projection lifetime
after the genuine COM surface scope naturally made VC7.1 reuse these
exact native slots; no fake/padded locals were declared.

Final natural source `src/GraphicsProjectedQuadF271.cpp` with pinned
VC7.1 `/Od /Ob0 /Gy /GR- /GX- /GS /Zi` compiled to **all 1,185 bytes**,
**1,037/1,037** comparable nonrelocation bytes and **37/37 true COFF
relocations**, including all native graphics/draw origin globals and
three real `__ftol2` REL32 calls. Canonical unit
`graphics-draw-projected-textured-quad-00402d50` was independently
rebuilt from source cold and reported **`exact; 1185 coverage bytes`**
with only that new unit, **no all-unit cold replay**. Direct3D8, CRT
and SDK helper bodies are not separately authored credit, nor are
related already-accepted Graphics::DrawTexturedQuad and
Graphics::DrawProjectedTriangleStrip doubly counted. The 97 origin
unknown candidates and 3,608 bytes remain excluded from authored
credit. This is local complete-function source/COFF/VC7.1 evidence,
not a remote Oracle receipt. No disassembly-as-source, byte grafts,
manual assembly, artificial padding, masked relocations or truncated
function matching.

### F270 negative large-character cancellation controller retained

An independently reviewed **497-byte** original R041-authored
`CharacterSelectScene::UpdateCancelAnimation` at `00435870` produced
a full 497-byte natural C++ probe, retaining all 13 real relocation
fields but only **438/445** comparable bytes. The seven contiguous
mismatches involve operand ordering at a true x87 `FUCOMPP` comparison
between the source scene's indexed float and a 60.0f constant at
`00658264`; the native loads constant first, whereas the natural
source emits the field first. Real candidate expression/order/type
changes including global `const`, `volatile`, C++ indexed array,
typed pointer, flipped operands, float literal and negated comparison
all retained the same mismatch or broke size. The entire native code
is not accepted and gets **zero** new authored CODE credit. Preserve
`.analysis/f270-character-cancel/` and its original/native and
negative probe reports. Do not fake the branch or stack layout to
claim exactness; return to actual source-type evidence later.


## F272: complete encoded CardList file loader, original while parser and genuine pointers

`CardList::LoadEncodedCharacterFile` is independently R041-authored and
occupies the entire native PE extent `00431B60..00431D56`: **503 CODE
bytes**, **137 native x86 instructions**, actual `RET 8` at `00431D54`,
and original full SHA256
`dee41adcf9b1bdf69dce0ce4544d0b4e498ba72c39db43fbbcc84ef00c386711`.
It owns no post-RET table; comparison is the entire function. The Ghidra
read-only function/decompile and **complete** native instruction listing
were independently audited; Ghidra's STL-like autogenerated name for the
list's `back` accessor is provisional and not assumed to be the actual
source owner type. Original native sources and all C++ negative controls
remain in `.analysis/f272-card-encoded/`.

The function calls original ClearEntries `00431940`, formats the
`data\\character\\%s\\cardlist.dat` resource path at `00658170` in
a native-compatible **260-byte pathname** local, uses archive directory
lookup `0041CF00` on its second argument and the returned archive's
`OpenEntry` `0041D800`, then returns for the original -1 handle case.
It allocates exactly the native file size via `operator new` `006416A2`,
retains the original separate buffer-allocation and content pointers,
performs the native `ReadFile`, and decodes bytes using initial XOR key
0x60, delta 0x61, and delta += 0x41 on each byte. It does not close the
input handle because the original body does not. A separate unsigned
`index` loop scans newline bytes using a **while loop**, pushes a null
pointer to the physical character deque through `0041DE30`, allocates
`(index-begin+1)` bytes through the actual operator new, assigns the
record using original `0041DE00` `back()` calls, copies exactly
`index-begin` bytes using `memcpy`, and performs the observed unusual
terminating store at `[index-begin-1]`, then advances the begin index.
Finally it calls original `free` at `0064169D` on the completed buffer
and does the native `/GS` cookie check `00640611`. No invented
robustness, handle-close, STL identity or defensive guards were added.

The first complete natural C++ candidate emitted 515 bytes, not 503.
Grounded native nested scope/lifetime layout restored actual HANDLE
at EBP-4, delta byte at -5, transferred byte count at -0xC, begin at
-0x10, file size at -0x14, buffer at -0x18, parser index at -0x1C
and key byte at -0x1D. Distinct used raw allocation and deque-entry
allocation temporaries, a genuine final release-pointer transfer,
VC7 `/GS` security cookie, and a native-compatible 260-byte path
recovered the original 0x14C frame. Changing guessed `for` parser
control to native `while (index < fileBytes) { ...; ++index; }` removed
an extra 2-byte entry jump, producing the full 503 code bytes with
**438/443** comparable nonrelocation positions already matching and
all 15 true native COFF relocations. The remaining **five** compare
positions were the two actual buffer allocator pointer uses (native
EBP-0x13C) and the three actual deque-appended pointer uses (native
EBP-0x138). Adding one genuine lexical lifetime for the **used**
appended `char*` enclosing the parsed data scope, after the existing
real decoder index, naturally made VC7 reuse those two correct EBP
slots, producing **443/443** comparable bytes and 15/15 physical
DIR32/REL32 destinations. No artificial local or pointer was created.

Source `src/CardLoadEncodedF272.cpp` compiled under pinned VC7.1
`/Od /Ob0 /Gy /GR- /GX- /GS /Zi`, then canonical matching unit
`card-list-load-encoded-character-file-00431b60` was rebuilt **cold
by itself** and reported `exact; 503 coverage bytes`. The independently
accepted F252 card-file encoder at `00431D60` is a distinct complete
432-byte *writer*; the separate 429-byte plain CardList reader at
`004319B0` was nonexact **at F272**, but was then cold-accepted
independently as **F273**. Do not conflate any of
these three workflows. Library deque/CRT/archive callees and all 97
unknown origins receive no extra authored CODE credit. Local cold
verification is not an external Oracle receipt; no byte patches,
masked fields, manual x86 assembly or cropped function were used.


## F273: full 429-byte plain CardList reader cold-exact, independent of encoded loader

The independent **R040-authored** `CardList::LoadCharacterFile` at
`004319B0..00431B5C` is **429 original native CODE bytes** and **118
original x86 instructions**, ending in `RET 4` at `00431B5A`. Its full
PE-backed native body SHA256 is
`0a1beba269423c6147c122a84cce0c4d6c2ee7b08722424db61ea57053886fcc`.
The origin evidence is **R040** for this function; the adjacent F272
encoded reader at `00431B60` has separately reviewed **R041** origin.
The original Ghidra full function/decompile, all native machine-code
instructions and the final entire C++ probe/cold receipt reside at
`.analysis/f273-card-plain/`. Historical complete negative controls
under `.analysis/f254-card-reader/` and `.analysis/f255-card-plain/`
are preserved rather than treated as authoritative.

The plain reader genuinely calls game ClearEntries at `00431940`,
formats the path from `00658150` with a native-compatible **260-byte
pathname** (rather than assuming older Ghidra `char[268]`), opens with
Win32 CreateFileA, checks the original invalid handle, calls GetFileSize,
allocates the actual file length through operator new at `006416A2`,
performs ReadFile and **calls CloseHandle** on its file handle. It then
executes an unsigned newline-parser `while(index < size)`, pushes an
actual null `char*` through native deque push_back `0041DE30`, allocates
`index-begin+1` bytes for each encountered line, stores it using real
`0041DE00` deque back accesses, calls native memcpy for `index-begin`
bytes, and writes its original unusual terminator at
`appended[index-begin-1]` without correction. It moves begin forward,
increments index at the loop bottom and finishes with the native free
and `/GS` check. No XOR decode/archive manager is invoked by this
plaintext routine, unlike the separate F272 encoded reader; no IO
branches or cleanup absent from the target are invented.

The older natural controls emitted 459/447 bytes and the prior best
complete 429-byte probe matched only **339/365** nonrelocation bytes;
22 reordering experiments remained negative. F273 checked the target's
actual physical slots anew: HANDLE EBP-4, transferred readBytes -8,
line begin -0xC, size -0x10, data -0x14, scan index -0x18, cookie
-0x1C; filename in its genuine stack frame of 0x140, with distinct
physical allocated-content, queued-null, allocated-entry, appended
result and release-alias lifetimes. Native-guide nested *real* C++
scopes, informed by F272's independently accepted encoded loader but
retested against this separate R040 original, naturally restored the
compiler's real buffer and deque record pointer locations. The first
new meaningful source `src/CardLoadPlainF273.cpp` compiled the **full
429 bytes**, all **365/365** nonrelocation positions and **16/16
physical native COFF relocations** under pinned VC7.1
`/Od /Ob0 /Gy /GR- /GX- /GS /Zi`. Canonical unit
`card-list-load-plain-character-file-004319b0` was cold-rebuilt
**alone** and reported **`exact; 429 coverage bytes`**. No all-unit
replay, byte patches, masked fields, artificial padding or assembly.

All three authored CardList file flows are now separately exact:
plain loader F273 429 bytes, encoded loader F272 503 bytes and encoded
writer F252 432 bytes. They are not conflated or double-counted, and
this verifies neither library deque implementations nor full private
owner class naming. The 97 origin-pending functions are uncredited;
local Git checkpoint and canonical cold replay are **not** external
Oracle receipts.


## F274: three independent native score selector/address/working-copy leaves cold-exact

One physically borrowed source translation unit
`src/ProgressSelectionF274.cpp` reconstructs three full game-specific
functions with native 32-bit thiscall entrypoints, *without* allocating
or inventing the original private score matrix class. The original
whole PE bodies were independently extracted and decoded, not guessed
from prior C++ declarations.

| Original function | Full native CODE | Native instructions | Genuine physical COFF fields | Complete original SHA256 |
| --- | ---: | ---: | ---: | --- |
| ProgressRecords::SetSelection `0041A1A0` | 37 | 13 | 0 | `0f99eec904b581eede37af1b5192943bfc5cec8a79584a529a755548d4d0d6d6` |
| ProgressRecords::GetSelectedRecordAddress `0041A240` | 48 | 15 | 0 | `a85d7a9d446d15bbf1c2b14ab8f49e180fa42c6b9a5e1fea3a95ab0e52c73dfb` |
| ProfileSelection::StoreWorkingEightBytes `00416E20` | 84 | 25 | 1 | `0af4d8ab0264b631bc1fb818b7757108ad1385d5e3f2a85abd7ca91f4ff4a3ed` |

Both R021 selector leaves were independently accepted as **authored**
in `config/function-origins.csv` and documented under `docs/ORIGIN_REVIEW.md`
long before this reconstruction. However their historical provisional
rows in `config/functions.csv` had an **empty owner**, not `authored`.
F274 did not assume that an empty owner was correct or avoid the
inconsistent tracking state: it checked the live R021 evidence, the
actual complete native game behavior and source contracts, then set
`functions.csv` owner to `authored` for the two exact accepted rows.
The separate R180 helper already had `owner=authored`; no origin
classification was changed, and all 97 still-pending origins remain
untouched and uncredited. Original nominal private owner names are
not independently proven.

`SetSelection` writes the two **signed char** argument bytes directly
to observed owner+0x16AC4 and owner+0x16AC5 and finishes with RET 8.
`GetSelectedRecordAddress` sign-extends both stored bytes and computes
`this + 0x17F0 * fighter + 0x5FC * difficulty` using the exact original
x86 arithmetic, returning the real selected working-record pointer.
`StoreWorkingEightBytes` sign-extends a signed stack slot parameter,
computes destination `this + fighter*0x17F0 + difficulty*0x5FC +
0x55C + slot*0x10`, and calls the genuine original `memcpy` at
`00640F20` to copy **exactly eight bytes** from owner+0x16A94.
No otherwise-unobserved record structure, array length, allocation,
or accessor is represented. The 84-byte source has precisely one
physical REL32 field targeting native memcpy; the 37/48-byte leaves
have **zero** actual relocation fields.

All three ordinary pinned VC7.1 `/Od /Ob0 /Gy /GR- /GX- /GS /Zi`
source functions first compiled to full 37/48/84-byte originals
respectively, with **37/37**, **48/48**, **80/80** comparable
nonrelocation bytes and all **0/0, 0/0, 1/1** native relocation
offsets/types/destinations. Canonical units
`progress-records-set-selection-0041a1a0`,
`progress-records-selected-address-0041a240`, and
`profile-selection-store-working-eight-00416e20` were then
independently cold rebuilt **only as this affected three-unit group**
and reported **`3/3 exact` across one object**. Original native
function listings, natural source and cold receipts are retained
in `.analysis/f274-progress-leaves/`. The already accepted F269
ReplayScene caller and independent game/CRT callees receive no CODE
credit here. No byte graft, fake storage, masks, assembly, cropped
original function or all-unit cold replay was used; local Git checkpoint
is not remote Oracle acceptance.

### F274 independently revisited large, still nonexact bosses

The original R035-authored 1,252-byte ReplayRecords::AppendRecord has
**1,033/1,052** nonrelocated matching bytes in best retained complete
F225 C++ source, all 50 authentic physical COFF fields, with 19
residual differences confined to actual six 8-byte iterator stack
slots. New F272 bounded declaration-order controls retained exact
size/fields but did not produce an exact body; full diagnostics are
archived in `.analysis/f272-append-investigation/`. Do not credit.

For the 746-byte `SpriteSequence::RenderElements`, the independently
reviewed source reproduces all 198 native instruction classes and
true 0xBC stack frame but remains **734 bytes** due to distinct real
end-iterator/x/quad/tint slots. F274 eight new meaningful nested
Quad/RECT/counter/tint lifetime variants still emitted 734/719 and
failed exact; retain `.analysis/f274-sprite-scope/` and earlier
`.analysis/f261-sprite-sequence/`, **zero** new CODE credit.

Original complete 1,722-byte `Effects::LoadPatternCatalog` at
`005F71F0` was independently re-queried via read-only Ghidra. Its
actual custom effect pattern and archive calls, EH-owned container
cleanup and nested per-entry parsing make it a genuine large authored
controller; a mere plausible decompile is not an exact C++ source.
The full original function/decompile and read-only listing are kept
in `.analysis/f274-effects-catalog/` for later native-guided probes.
No byte credit is claimed.


## F278: cold-exact entire 1,264-byte FighterState weighted-pattern selection boss

The native R045-authored `FighterState::ChoosePatternSequence` entry
`0045D810` has the **complete 1,264 CODE bytes** ending with a plain
RET at `0045DCFF`, **342 independently decoded original x86 instructions**,
and original full PE-backed CODE SHA256
`f3038d921b723ed8d71379d697003141faba9653a6017da1eb83002f9a948e5c`.
It is a substantial game-specific two-phase algorithm rather than a
leaf or a fragment. Its source lives in `src/FighterPatternChoiceF278.cpp`;
reproducible full target analysis, compiler variants, original native
branch matching, final original COFF comparison and independent cold
receipt live in `.analysis/f277-fighter-pattern/` and
`.analysis/f278-pattern-lifetime/`. All negative probes are preserved.

The function obtains a random target weight through `rand` at
`006418AB` with native signed `% 256` lowering, resets a 16-bit
accumulator and the chosen pattern count byte `this+0x53A`, selects
the opposing fighter character from game globals at `006714C8` using
the actual signed player side `this+0x2CC` and adds 200 to the first
pattern sequence number. The borrowed native pattern catalogue begins
at `this+0x714` and its original helpers are `Count` `0045DD00`,
`Weight` `00420570`, `Flag` `00420530`, and `Name` `004205B0`.
The first phase iterates real weighted pattern entries, accumulates
signed short weights, and when the random threshold is reached,
records the actual entry-kind byte at `this+0x6CB+(signed count)`,
copies the corresponding pattern name using native `strcpy` `00641B80`
into `this+0x53B + 200*(signed count)`, and may append one following
pattern if the actual sequence length and zero-flag guards permit it.
Otherwise it scans actual CR-delimited neighbouring records until
an entry or the sequence boundary is reached. On no selection, it
uses a second real `rand` call and fallback sequence **300**, performs
the full analogous weighted pattern scan, and finally writes the
original default name from `00659078` and zero kind when nothing
is eligible. This preserves both complete loops, signed/unsigned
source semantics, native arithmetic and all original exits. None of
these game helper, CRT or library callee implementations is credited
as extra authored CODE.

A first full native-informed ordinary C++ translation emitted **1,311
bytes**, too many. Independent rechecking showed the real cursor is
incremented twice on the selected-first-entry path, rather than an
old pre-call cursor copy; the second fallback sequence is physically
stored in one short local rather than passed as an immediate at every
call. Native branch observations favoured positive Count/Flag guards
with one common exit, and native first/fallback scanning used actual
while conditions, not synthetic break branches. These real semantic
changes progressively narrowed the output to **1,275**, **1,265**,
then the complete original **1,264 bytes**, including all **31
original physical COFF relocation fields**, but the first full-size
version matched only **1,104/1,140** nonrelocation bytes.

Those last 36 bytes were physically concentrated in three signed
16-bit stack-local slots, not missing control-flow instructions. A
large set of declaration-order tests was negative because VC7.1
determines stack placement using actual variable lifetime, not
nominal name order. An independently grounded *meaningful* lifetime
reconstruction declares the real unsigned 32-bit scan index `cursor`
and the real signed short accumulated weight in the outer scope, and
then declares the real signed short random threshold and pattern
sequence inside a nested lifetime scope enclosing both selection
phases. This yields exact native stack slots `cursor` EBP-4,
`accumulated` EBP-8, `target` EBP-0x10 and `sequence` EBP-0x0C.
Two alternative genuine declaration orders demonstrated the same
compiler result with **1,140/1,140** byte comparison; final adopted
source is `finish-accum-before-target-inner.cpp` from private
`.analysis/f278-pattern-lifetime/`. There are **no dummy locals or
fake owner layout members**.

The pinned VC7.1 `/Od /Ob0 /Gy /GR- /GX- /GS /Zi` source
reconstructs the **entire 1,264-byte** machine-code extent, all
**1,140/1,140 nonrelocation bytes**, and all **31/31 genuine COFF
relocation offsets/types/solved native destinations**. The canonical
`fighter-state-choose-pattern-sequence-0045d810` unit was compiled
from source independently as the **only affected cold-replay unit**
and reported **`exact; 1264 coverage bytes`**. The game pattern
helper types and original private fighter parent layout remain
provisional, and all 97 unresolved origins remain uncredited.
No target-byte grafting, truncated function, manual assembly, masked
fields, artificial stack padding, full-set cold replay or remote
Oracle acceptance is claimed.


## F279: independently cold-exact four FighterScript pattern-deque field/size helpers

Four complete R076/R152-authored game-specific pattern helper functions
called by the now accepted F278 1,264-byte fighter selection boss are
independently accepted as entire machine-code functions, not grafted
from the caller. Their full original native CODE boundaries and SHA256
values were checked against the pinned Japanese PE and their instruction
counts verified using independent read-only decoding:

| Address / inferred role | Full CODE | X86 instructions | Nonrelocation bytes | Authentic COFF fields | Original full SHA256 |
| --- | ---: | ---: | ---: | ---: | --- |
| `0045DD00` CountPatternEntries | 66 | 23 | 58/58 | 2 | `e6f1e1b8184a86b0f8cd69748c64d476a20c96d4c775c26de855a6755b42373d` |
| `00420530` GetByteField | 53 | 19 | 45/45 | 2 | `e6f22dad1a3f05bb485a4955bfe4e38aa127c813611a7a09b623c75dd7514348` |
| `00420570` GetWordField | 55 | 19 | 47/47 | 2 | `5eaf1f97f52a513b12be919cef877afa523dcfba8c712a884b8b738f575556bb` |
| `004205B0` GetDwordField | 54 | 19 | 46/46 | 2 | `bb0395642b31cb755ce373801aa94b9dda9582ed801cbb37e1981c519788c7a1` |

The original catalogue indexing uses an actually **signed 16-bit
sequence index** to read a `short` row mapping at `this+2*sequence`.
The row collection is physically addressed at `this+0x7D0`, and
all these game-specific helpers dispatch to the *native VC7 library*
row access routine at `00421570`. `CountPatternEntries` returns a
short zero (original `XOR AX,AX`) for a negative row value; otherwise
it calls the existing native library row `Size` at `0045DD50`. The
three field readers obtain a row via the same native deque `At`,
then call the second existing VC7 container `At` at `00421360` with
a signed 16-bit item index. They extract respectively the original
8-bit signed flag at entry+0, 16-bit word at entry+2, and 32-bit
name pointer at entry+4. No original private enclosing class object
layout is claimed beyond these specific real member offsets; the
container implementation and its SDK/CRT bodies are **not authored
credit**. The originating R076/R152 classifications and all 97
unknown origins remain unchanged.

The complete natural C++ source was independently constructed as
`src/PatternCountF279.cpp` and `src/PatternAccessorsF279.cpp`; the
first pinned VC7.1 `/Od /Ob0 /Gy /GR- /GX- /GS /Zi` probes matched
all four original x86 extents structurally, all **196/196 combined
comparable bytes** (58+45+47+46), and **8/8 actual COFF
relocation fields** (two in each game method). The four canonical
units `fighter-script-count-pattern-entries-0045dd00`,
`fighter-script-get-byte-field-00420530`,
`fighter-script-get-word-field-00420570`, and
`fighter-script-get-dword-field-004205b0` were freshly rebuilt cold
**only as those four affected units**, from exactly two compiled
objects, and reported `4/4 exact`. Raw read-only Ghidra function and
native assembly evidence and full probe/cold receipts are retained
at `.analysis/f279-pattern-counter/` and
`.analysis/f279-pattern-accessors/`. No real native source code or
assembly was pasted into the authored files. All 228 combined CODE
bytes are separately credited once, not duplicated from the
previously accepted F278 caller or library deque callees. No full
all-unit cold replay, artificial offsets/padding, relocation masks,
uncertified input or remote Oracle verification is claimed.


## F281: full 602-byte Effects::SpawnConfiguredAuxObject cold-exact

The R067-authored `Effects::SpawnConfiguredAuxObjectAt005F7AA0` is a
complete native **602-byte** game-specific effect-spawning controller at
`005F7AA0..005F7CF9` with **175 independently decoded original x86
instructions** and a native `RET 0x20` at `005F7CF7`. Original full
PE-backed CODE SHA256 is
`2d065ef4cb07d47f8002eb5ea4f201ecabc9592721697767e882ab27ea3816c3`.
The original Ghidra read-only function/decompile/entire physical assembly,
whole natural VC7.1 source probes, native branch-shape comparisons and cold
receipt are retained in `.analysis/f281-effects-spawn/`.

The full original operation looks up a signed short pattern through the
actual config vector at `this+0x78` with original indexed access
`005F8380`. It requires that the slot contains a nonzero pointer and
that the pattern is nonzero; a separate signed `side` byte must be in
[0,1]. On accepted inputs, it pushes a zero pointer to the native
side-selected list at `this + 0x14*side` through the real native
`005F81B0` call. Genuine VC7.1 EH-backed `new(0x94)` at `0064159D`
constructs one aux effect through its original ctor `005FAB10`, retaining
all actual return-transfer stack lifetimes and exception states. It then
uses *each* original `005F8180` `back()` invocation (not a cached or
reused fabricated reference) to store pattern word +0x60, zero words
+0x62/+0x64, source x/y DWORD +0x44/+0x48, three flag bytes at
+0x66/+0x67/+0x68, zero +0x40, and four original caller DWORDs at
+0x80/+0x84/+0x88/+0x8C. The routine finally performs the original
virtual calls in slots zero and +4 through the newly created object.

The first complete plausible C++ probe (same actual 24 native COFF
fields and native EH frame) generated **603 bytes**, while the original
has 602. Its only instruction-shape differences were the genuinely
distinct branch-lowering sequence: native nonnull-pattern and nonzero-ID
guards each use a short JNZ followed by a long JMP to the exit; their
C++ analogues are separate early-return checks. The native side bounds
are **one combined** invalid-side test, so a negative signed byte jumps
to the same long exit used by a byte greater than one (native short JL
and JLE followed by one shared JMP). Independent `/Od` probes confirmed
that four separate returns generated 607 bytes and a fully combined
condition generated 603, whereas two real early returns plus **one**
combined signed-side out-of-range return produce the entire **602-byte**
target without compiler hints, fake locals or padding.

Final complete natural C++ at `src/EffectSpawnF281.cpp` emits all
**602 bytes**, all **506/506** comparable nonrelocation bytes and all
**24/24 actual physical COFF relocation offsets/types/solved native
destinations**. One pinned VC7.1 `/Od /Ob0 /Gy /GR- /GX /GS /Zi`
**single-unit cold build** `effects-spawn-configured-aux-object-005f7aa0`
reports `exact; 602 coverage bytes`, with no all-unit replay. The
borrowed side list, effect subclass and configuration vector interfaces
are observed call/physical-allocation boundaries, not proved complete
original nominal class layouts. Their runtime/library implementations
(including real effect-child ctor at `005FAB10`) are not separately
credited; nor is the independently unresolved 1,722-byte Effects
catalogue loader at `005F71F0`. All 97 pending origin-unknown functions
remain uncredited. No target code graft, manual assembly, cropped
function, masked relocation, invented branches or remote Oracle acceptance.


## F282: cold-exact complete 1,186-byte FighterState::LoadResources boss

Original R045-authored `FighterState::LoadResources` at
`00456B60..00457001` is **1,186 full native CODE bytes**, 272
independently decoded x86 instructions with native RET at `00457001`
and exact original PE-backed SHA256
`b32d8ac0cfeccf13aeca2a12a628276b5efa4cfae78689ced2b321ed14bc85bb`.
The true complete game resource initializer is not simply a texture
leaf. It logs the sound/pattern/picture stages, formats an original
character-specific sound `.dat` name, dispatches to game sound loader
`004076A0` on the physically observed sound archive at `this+0x6D0`
with a Meiling-specific alternative archive, calls the independently
previously accepted large native `FighterPattern::Load` at `00457660`,
and EH-allocates two **80-byte native texture managers** at fighter+4
and fighter+0x534 through original game TextureManager ctor `0040AD80`.
It supplies the original fighter+0x478 signed slot count, fighter
+0x2CE signed stage page selector, and fighter+0x532 signed count
through native slot allocator `0040B1D0` and multi-archive image loader
`0040BBA0`; the primary archive is selected on original Alice/Meiling
checks. The complete secondary load path tests six real character
strings in native order (Patchouli, Yuyuko, Remilia, Yukari, Youmu,
Meiling) and uses `0040BB80` with the original alternative/default
archive roots. The source then constructs an actual fighter `.sce`
script resource path, calls native script reader `004206D0` and
`004205F0` on the original script manager at `this+0x714`,
EH-allocates the real **24-byte** command-list object at `this+0x480`
through native ctor `00410F30`, initializing it from the primary texture
manager, calls native mode setter `0045CD50(0)` and finally dispatches
the authentic fighter virtual slot +0x18. Its three native `new`
operations, all original EH states and security-cookie check at
`00640611` are preserved, with no invented file guards.

The read-only Ghidra decompile misleadingly suggested `char[532]` for
the local pathname. Independently checking the original complete
`0x240` native stack allocation and `LEA` pathname at `EBP-0x224`
showed a natural **524-byte C++ filename buffer** is the physical
layout that actually produces those native values under VC7.1 `/GS`;
the first source with 532 bytes emitted a different 0x248 frame.
Once corrected, the first complete natural source emitted 1,190 bytes
with the same 272 instruction classes and all physical resource
references. Comparison proved the remaining 4-byte size divergence
was the secondary texture archive branch. The native six independent
character tests use early short `JE` to the matched-character archive
and final short `JNE` to the other archive. Reversing a logically
equivalent but incorrectly shaped `!=0 && ...` condition into the
actual `==0 || ...` condition restored the *real control-flow branch
geometry* and compiled **all 1,186 bytes exactly** without fake
instructions or padding. Both source conditions have the same meaning,
but not the same unoptimized VC7.1 instruction shape.

Final natural full source `src/FighterLoadResourcesF282.cpp` compiles
under pinned VC7.1 `/Od /Ob0 /Gy /GR- /GX /GS /Zi` with
**934/934 exact comparable nonrelocation bytes**, **63/63 genuine
physical COFF relocation offsets/types/native destinations**, and all
**1,186 original CODE bytes**, preserving real native exception frames
and full cookie/CRT calls. The canonical matching unit
`fighter-state-load-resources-00456b60` was rebuilt **cold by itself**
and reports `exact; 1186 coverage bytes`; no full-set replay.
Original Ghidra native/decompile/full disassembly, all failed
size/buffer/branch alternatives and acceptance receipt are retained
privately under `.analysis/f281-fighter-resources/` and
`.analysis/f282-fighter-loader/`. The physical resource receivers
and sizes are borrowed call/allocation interfaces, not claims of
complete original FighterState or private TextureManager class layouts.
The original other child constructors `00410F30`, native resource
callees, VC7 library and 97 pending origins are not independently
credited here. The paired 588-byte fighter resource destructor
`00456910` was still nonexact **at F282**, but later full-native
source/COFF was cold-accepted separately as **F284**. Local Git
checkpoints and cold replay are not remote Oracle verification. No assembly, byte grafts,
masked comparisons, fake locals or cropped function.


## F283: three complete fighter resource and auxiliary object helpers cold-exact

Three additional independently authored functions immediately downstream
of the separately accepted F281/F282 larger controllers are now exact
as **whole functions**. Their native full PE boundaries, independent
instruction counts, source and physical COFF relocations were verified:

| Original authored function | Complete CODE | Original instructions | Nonrelocation matches | Physical COFF fields | Full PE CODE SHA256 |
| --- | ---: | ---: | ---: | ---: | --- |
| FighterState::SetNoticeModeByte `0045CD50` (R103) | 25 | 10 | 25/25 | 0 | `1befd85338f3c8ffc00f6405c71bae0adf10cc1d0bd3d5899dac76aca0d95984` |
| CommandList::InitializeDefaults `00410F30` (R166) | 104 | 29 | 80/80 | 6 | `1695850c6e7e19cd8dfb6d7bb5255221a2012d24b7df5412baa466bd63d32b32` |
| CharacterAuxObject::Initialize `005FAB10` (R064) | 116 | 33 | 104/104 | 3 | `f7edb6015289b9d61fbcebcdfe17fc253623dd6737a0375365bad54a907b36b0` |

The notice method receives a byte (native thiscall) and stores precisely
it to fighter+`0x6E4`, returning `RET 4` without side effects. The
complete command-list constructor naturally constructs its original
real queue subobject at `this+4` via `00411C30` and emits the genuine
VC7.1 exception handler at `0065501B`. It stores the input texture
manager at `this+0`, a short capacity 15 at +`0x12`, mode byte 5
at +`0x10`, and calls the original `004110F0` reset. The complete
auxiliary effect constructor naturally calls base constructor `00458670`,
sets the actual new child vtable `0065A0E0`, stores the supplied owner
pointer at `this+0x90` and derived owner pointers (+`0x78` and +`0x28`)
at `this+0x7C` and `this+4`, zeroes three actual shorts at
`this+0x60/0x62/0x64`, and invokes original child reset `005FAC60`.
The borrowed view types reflect only observed data or subobject-size
boundaries, not a claim to have recovered full original owner layouts.

All three *first complete* pinned VC7.1 natural-source probes exactly
matched their respective entire CODE lengths and authentic physical
relocations. Canonical units
`fighter-state-set-notice-mode-0045cd50`,
`command-list-initialize-defaults-00410f30`, and
`character-aux-object-initialize-005fab10` were independently rebuilt
**cold only for this affected three-unit group**, reporting `3/3 exact`
on three source objects with normal `/GX` enabled only for the EH
command-list constructor. Source files are `src/NoticeModeF283.cpp`,
`src/CommandListCtorF283.cpp` and `src/EffectChildCtorF283.cpp`. Native
function/assembly/decompile reviews, COFF previews and local cold proof
are retained at `.analysis/f283-fighter-helpers/` and
`.analysis/f283-resource-helper-probes/`. The F282 1,186-byte fighter
loader and F281 602-byte effects spawn controller were separately
accepted earlier and are not double-counted. Library queue, original
base/child reset methods and all 97 pending-origin functions remain
uncredited. No target bytes or assembly were inserted, no arbitrary
source padding/masked relocation/truncated function or all-unit cold
replay was used; local Git checkpoint is not an Oracle receipt.


## F284: 588-byte FighterState resource destructor exactly reconstructs five physical member lifetimes

The native R045-authored `FighterState::ReleaseResources` has the
**complete** `00456910..00456B5B` PE-backed CODE extent (588 bytes,
159 independently decoded x86 instructions, original plain RET at
`00456B5B`) with original SHA256
`bae6c2e827a51042738bfd0bc44fc5ba2b9b2af16fa0ad293a22c67085d4af50`.
Read-only full native function/disassembly and actual original native
receiver offsets are preserved at `.analysis/f281-fighter-resources/`;
the complete first natural C++ source, whole COFF comparison and cold
receipt are at `.analysis/f284-fighter-release/`, with adopted source
`src/FighterReleaseResourcesF284.cpp`.

The real destructor installs original FighterState vtable `00658FE8`
and native EH handler `00656121`, allocates the exact 0x50 native
cleanup frame and initializes original EH state 4. It uses an unsigned
index and the **actual fighter+0x468 vector** with native size
`004421E0`, element `At` `00458BC0`, null test, child preparation
`00458B50`, subsequent actual scalar deleting destructor `00458690`,
then calls the authentic vector clear `00458C20`. The physical fighter
entry deque at +0x518 has separate native clear `00414530`. It deletes
original individually owned pointers at fighter+0x480 (command-list
scalar deleting destructor `00458710`), +0x2EC (special scalar deleting
destructor `00458740`), and the real texture manager pointers +4,
+0x534, +0x700 (`00425460`) retaining native outer/inner null checks
and *real* deletion return lifetimes.

The original native EH cleanup sequence is **not hand-written** in
source. True C++ member object destruction automatically invokes
script owner at fighter+0x714 (`004204D0`), sound archive at +0x6D0
(`00407270`), fighter deque at +0x518 (`004143B0`), input mapper at
+0x494 (`00406DF0`), then fighter actor vector at +0x468 (`00458BA0`).
The pinned VC7.1 compiler naturally reproduces the original EH
state updates **4 -> 3 -> 2 -> 1 -> 0 -> -1**. The physical
carrier declarations put each genuine observed destructor-bearing
subobject at its original address; unknown private bytes between
those observed boundaries are not treated as known game state,
nor are they passed as extra arguments, credited as CODE, or claimed
to prove original parent class definitions. Their byte spans are
**strictly grounded in actual original receiver offsets** rather
than guessed unobserved subobject behavior. No artificial *stack*
locals, compiler macros to force instruction bytes, masked fields or
manual EH are used.

The first complete natural C++ source for this independent original
function, `src/FighterReleaseResourcesF284.cpp`, compiled with pinned
VC7.1 `/Od /Ob0 /Gy /GR- /GX /GS /Zi` into **all 588 original
CODE bytes**, **496/496 comparable nonrelocation bytes**, and
**23/23 real physical COFF relocation offsets/types/native targets**
without iterative fake-local tuning. Canonical affected unit
`fighter-state-release-resources-00456910` was rebuilt cold by itself
and reports **`exact; 588 coverage bytes`**. Previous F282 full
1,186-byte initialization of these fighter resources and separately
F283 accepted command-list ctor are independent, not double-counted.
No original VC7 container runtime or child deleting-destructor body
receives new authored credit from this call chain. All 97 unknown
origins remain uncredited and the local Git checkpoint is not an
external Oracle acceptance receipt. TH075's tracked exact totals
reach **600 whole functions, 797,349 authored CODE bytes**, still
only **40.40%** of the reviewed authored-code denominator. The 98%
reconstruction goal remains unfinished.


## F285: cold-exact 487-byte ordinary effects spawner, distinct from F281 configured form

The R067-authored native `Effects::SpawnAuxObjectAt005F78B0` is
**487 complete PE-backed CODE bytes** from `005F78B0..005F7A96`,
143 independently decoded original x86 instructions ending with a
`RET 0x1C` at `005F7A94`. Original full PE body SHA256:
`862675bf727d13772549cb9542d745a593f2e28cae1e112d7751e68a8c4806c8`.
Read-only Ghidra function/decompile/native assembly, pinned VC7.1 source,
COFF comparison and single-unit cold result are at
`.analysis/f285-effects-spawn-neighbor/`; final source is
`src/EffectSpawnF285.cpp`.

This original routine is **not** the same function as the already
F281-accepted 602-byte `Effects::SpawnConfiguredAuxObject` at `005F7AA0`.
It is its ordinary form without an eighth configuration-pointer argument
and without four 32-bit data writes to new object+0x80/+0x84/+0x88/+0x8C.
The actual native control flow independently confirms separate early
returns for a missing effect config and zero short sequence ID, then a
single combined signed side-byte guard requiring 0 or 1. It uses the
real game config vector indexed by native `005F8380` from owner+0x78,
side deque at `this+0x14*side` via native `005F81B0`, pushes a genuinely
null pointer, allocates a **0x94-byte** EH-backed game effect object
via native operator new and the separately F283-cold-accepted complete
child constructor `005FAB10`, and repeatedly calls native deque
`back()` `005F8180` rather than caching a fabricated child pointer.
It stores true fields +0x60 (sequence), +0x62/+0x64 (zero shorts),
+0x44/+0x48 (x/y), +0x66/+0x67/+0x68 (mode/status byte arguments) and
+0x40 (zero), and dispatches the real original two virtual methods.

A first independently compiled full-source variant, using the
F281-accepted native-EH control shape only as a hypothesis and removing
the four actual absent data copies and argument, emitted the **entire
487 original CODE bytes**, **407/407** comparable nonrelocation
bytes and **20/20 genuine physical COFF fields**. The pinned VC7.1
`/Od /Ob0 /Gy /GR- /GX /GS /Zi` unit
`effects-spawn-aux-object-005f78b0` was freshly rebuilt **cold only
for this affected function** and reported `exact; 487 coverage bytes`.
F281 and F283 were independently cold-accepted previously and receive
no duplicate CODE credit here. The native 1,722-byte Effects catalog
loader at `005F71F0` was unaccepted in historical F285; it is now independently **F294 cold-exact**, while all 97 origin-unknown
functions. No target byte grafting, assembly, synthetic filler, masked
relocations, cropped function, all-unit cold replay or external Oracle
verification is claimed.


## F286: cold-exact 374-byte fighter stage texture resource loader

R045-authored `FighterState::LoadStageResource` is complete PE-backed
`004584D0..00458645` CODE, **374 bytes**, 79 independently decoded
original x86 instructions, real plain RET at `00458645`, full SHA256
`109507f8ab77b1660a4602546cffc1e859acbf9bdfc5a134355316bd24a9b8c6`.
The original read-only Ghidra function/decompiler/entire disassembly,
first 373-byte negative VC7.1 source and final exact COFF/cold proof
remain at `.analysis/f286-fighter-init-stage/`; adopted source
`src/FighterStageResourceF286.cpp` uses only borrowed native fighter
and texture interfaces, not a guessed complete private class layout.

The real original stage global is a **signed byte** at `0067161E`.
If nonpositive it leaves the function; otherwise it checks native
texture pointer fighter+`0x700`, conditionally calls the real scalar
deleting destructor `00425460`, allocates an 80-byte manager through
`0064159D` with the authentic EH-backed constructor `0040AD80`,
stores it to fighter+`0x700`, and allocates its stage-specific pages
with `0040B1D0` using the original signed byte at
`fighter+0x704+stage`. It formats the true path using native format
string `00658FC0`, fighter name at +0xC4 and the stage byte, then
loads the original image archive `00658FE0` through `0040BB80`.
All original EH states and the `/GS` cookie/check at `00640611` are
retained. The pinned VC7.1 `/Od /GX /GS` source with an actual
260-byte pathname produces native frame size `0x12C` and original
`EBP-0x11C` path address; the Ghidra candidate `char[268]` was not
assumed correct.

The initial natural whole-function source used `if (stage > 0) { ... }`
and produced 373 bytes, one less than native, with otherwise correct
physical data and calls. Original machine code explicitly uses native
`JG short +5; JMP near return` at function entry. Expressing the
actual branch as `if (stage <= 0) return;` naturally restores that
7-byte form under unoptimized VC7.1, yielding **all 374 bytes**,
**306/306** comparable nonrelocation bytes and **17/17 authentic
COFF relocation fields** (actual offsets/types/native targets).
The canonical unit `fighter-state-load-stage-resource-004584d0` was
recompiled **cold by itself**, reporting `exact; 374 coverage bytes`.
Already accepted full F282 fighter resource loader and F284 destructor
are independent and not double counted; their library helpers and all
97 pending unknown origins are not credited. No byte graft, assembly,
masking, artificial local source padding, truncation or all-unit cold
replay. Local Git checkpoint is not external Oracle verification.


## F287: full 345-byte fighter construction reproduces real polymorphism and native EH order

R045-authored `FighterState::Initialize` occupies full PE CODE
`004567B0..00456908` (**345 bytes**, **86 independently decoded
original x86 instructions**, original RET `00456908`). Full pinned
Japanese PE body SHA256:
`f3de21648341293bf8058450b5425bf659e733a0cd41c6cbb11789bd2d80ef13`.
Original read-only Ghidra function/decompile/full assembly and complete
VC7.1 positive/negative source comparisons reside at
`.analysis/f286-fighter-init-stage/`. Adopted source is
`src/FighterInitializeF287.cpp` with borrowed physical owner boundaries
only (not a reconstructed complete original fighter private layout).

Actual source/member initialization order from native: fighter base
constructor `00458650`; install original vtable `00658FE8`; construct
original actor properties at fighter+0x2D4 through `00412620`; vector
at +0x468 through `00458B70`; input mapping at +0x494 through
`00406DB0`; replay deque at +0x518 through `00414360`; sound archive
at +0x6D0 through `004071C0`; script resource at +0x714 via
`00420440`; configure original audio at +0x6D0 through `004073A0`;
zero **exactly the original observed 28-byte local memory** with
native `memset` `00640490` (local at EBP-0x28), then initialize the
replay deque at +0x518 with original `0045A620(90,0)`. Real
EH-backed `new(0x54)` then constructs a special owner via native
`0045B920`, stores the result to fighter+0x2EC and invokes true
`0045BA10` Bind(this); finally zeroes three native texture pointers
+4/+0x534/+0x700. All actual exception transitions (0..5..-1),
original EH handler `006560D1`, native 0x2C stack frame and exits
remain intact.

A provisional first C++ implementation assumed a base virtual
destructor despite lacking independent native evidence, so VC7.1
inserted an extra base EH state and incorrectly shifted subsequent
member states, generating 380 bytes. Merely removing polymorphism
caused the compiler to pass a shifted base subobject pointer; native
requires a **polymorphic base with a virtual method but no separate
virtual base destructor**. The original really has a 28-byte memset
call to stack memory, not the multiple unoptimized assignment
instructions generated by `char scratch[28]={0}`. Reconstructing the
actual observed 28-byte memory area as an `unsigned int[7]` local and
calling the true C runtime `memset` yields precisely that native call
without inventing any other local byte operations or making claims
about the unused original memory's private type. No local size is
added beyond the observed original 28 bytes.

Pinned VC7.1 `/Od /Ob0 /Gy /GR- /GX /GS /Zi` then emits the
complete original 345 CODE bytes, **273/273** comparable nonfield
bytes, and **18/18 original physical COFF relocation offsets/types
and solved native destinations**. The single affected canonical unit
`fighter-state-initialize-004567b0` was rebuilt cold and reported
`exact; 345 coverage bytes`; no all-unit replay. F282/F284/F286
fighter resource flows are independently accepted and not double
counted. Complete game object layout, library/CRT subroutine bodies
and all 97 origin-pending functions remain uncredited. No target
code graft, hand assembly, masking, cropped function or artificial
extra stack padding was used. Local Git checkpoints are not remote
Oracle verification.


## F288: exact complete 308-byte BattleEnd scene initialization

R053-authored `BattleEndScene::Initialize` is all **308 native CODE
bytes** `00424E00..00424F33`, with **73 independently decoded x86
instructions**, actual plain RET at `00424F33` and original PE body
SHA256 `4680497f7bf07f1e6e75d282ee5a75994ca784cb795238c5efb4a4519aa93780`.
The first native-faithful C++ source `src/BattleEndInitF288.cpp`,
original read-only Ghidra/native full assembly under
`.analysis/f286-fighter-init-stage/`, complete COFF compare and cold
receipt `.analysis/f288-battle-end/` were all independently checked.

The real game scene base ctor at `004251C0` is separately origin
**unknown** R108 and is not independently granted authored credit.
The scene installs actual vtable `00657B7C` with EH handler `00655718`,
configures the genuine global font renderer at `0067143C` using
original 35.0f and 360.0f and one flag through `00413420`, then draws
real title resource at `00657B7B` with native 120,120,255,16,1,0
parameters through `00413460`. It zeroes the actual actor+`0x6EE`
flag, moves native actor stage field +`0x713` to signed global
`0067161E`, invokes the authentic fighter virtual method slot
+`0x3C` on global `00671418`, then calls the independently F286
cold-exact `FighterState::LoadStageResource` at `004584D0`.

The original three-way stage dispatch is fully preserved: stage=8
and stage=9 both zero global `006714CE`, and call actual progress
selection `00416CE0` on owner `006718F8` using the signed fighter
byte `006714C8` plus 0 or 20 respectively. For all other stages it
sets status to `0xFF`, calls the real `00425130` progress reset and
selects fighter+40. The original special short-sized signed promotion
of the fighter byte in the stage=8 path is reproduced automatically
by real method `void SelectRecord(short)` and natural VC7.1 ABI.

The first whole source built under pinned VC7.1 `/Od /GX` produced
the complete **308 bytes**, **172/172** comparable nonfield bytes,
and **34/34 true native COFF relocation offsets/types/destinations**.
The canonical `battle-end-scene-initialize-00424e00` unit was cold
recompiled **alone**, reporting `exact; 308 coverage bytes`, with
no all-unit replay. Native scene/fighter/font/score interfaces are
borrowed physical call ABIs, not claims of complete original private
owner definitions, and their external game/CRT/VC7 implementations
receive no duplicate source credit. All 97 origin-pending functions
remain excluded. No target-byte graft, assembly, fake locals, masked
relocation fields, cropped body, or external Oracle receipt.


## F292: full cold-exact 1,385-byte OverlayText game text box renderer boss

The original R035-authored `OverlayText::DrawBox` at
`00412EB0..00413418` contains **1,385 complete PE-backed native CODE
bytes**, **359 independently decoded original x86 instructions** ending
in an original plain RET at `00413418`, and original full SHA256
`4c8c94555d1fafb8a9d3b9be723f1bef621c2a2dd7b9aa2c2f6d5f939923d185`.
Its complete native Ghidra function/decompile/physical instruction
listing, preliminary whole-source variants, actual native instruction
shape/stack comparison, and final native COFF/cold acceptance remain
under `.analysis/f292-overlay-boss/`; the naturally authored complete
C++ is `src/OverlayTextDrawBoxF292.cpp`.

The original function has one 16-byte RECT local and one **136-byte
actual transformed quad** on the native stack, and keeps its `this`
pointer at EBP-0x9C in a genuine 0x9C stack frame, **without** a
spurious `/GS` cookie. The first source incorrectly modeled this
opaque 136-byte borrowed quad as `char[136]`, causing VC7.1 `/GS` to
insert an unwarranted security cookie. A physically equivalent
`unsigned int[34]` local is the original borrowed 136-byte object
**carrier**, without claiming to know the object's actual private
interior field semantics or causing extra instructions. Source helpers
remain native game methods (quad BuildRect/Scale/Translate; texture
mode `this+0x28`, device drawing) rather than fabricated implementations.
The actual native scale call passes **39.0f** (`0x421C0000`, not the
misread 38.0f) with another existing float field's native 32-bit
bit pattern, and primitive translation forwards the raw x/y float
bits using the original calling convention without x87 conversions.

After the initial background rectangle `0,0,571,78`, the text box
checks a real byte-mode at `this+0x25`, invokes original texture
helper `0040C9A0` on game subobject `this+0x28` or initializes
scale at `this+0x10`. Its actual float scale test determines whether
to render immediately or increase scale via the original `006578C0`
float global. The positive rendering path computes original panel
height `(unsigned byte(this+0x24)+6)*signed char(this+0x15)`, then
renders a dynamically sized backing rectangle with original scale,
translation and five physical offset passes at black `0xFF000000`
and white `0xFFFFFFFF`. It reconstructs another true rectangle
from that height to 128, and renders **another five offset passes**
with an original unsigned byte alpha at this+`0xC`. The native source
compares `unsigned alpha < 255` rather than testing a signed byte
against -1, and adds 10 before drawing when nonterminal. For each
alpha DrawQuad, native code visibly executes `MOVZX byte; AND 0xFF;
SHL 24`; all **five** `AND 0xFF` instructions must be expressed in
real source math, rather than relying on a possibly optimized
zero-extended byte. The final DrawQuad also performs three separate
native OR operations for RGB `0xFF0000`, `0xFF00`, `0xFF`, not a single
collapsed 24-bit literal. The true float scale update loads the
field first then performs `FADD` with original float constant, not
the opposite operand order. All ten original sprite DrawQuad calls
and all scale/translation calls remain, with no missing outline pass.

First full meaningful source emitted 1,370 bytes but had a spurious
security frame, incorrectly typed texture-mode helper and wrong
39.0f scale constant. Correcting genuine 34-DWORD quad carrier, raw
DWORD float forwarding, thiscall owner and field-first early-exit
shape recovered a 1,340-byte complete control flow and original 0x9C
frame. An independent **full instruction-sequence diff** showed the
remaining 45 bytes reflected actual alpha masks, bitwise RGB color
combination and unsigned 255 threshold. Restoring these exact
*semantics* naturally emits **all 1,385 original bytes**, **359 original
instructions**, all **1,213/1,213** nonrelocation positions and
**43/43 real physical COFF relocation offsets/types/native targets**
under pinned VC7.1 `/Od /Ob0 /Gy /GR- /GX- /GS /Zi`. Only the
new `overlay-text-draw-box-00412eb0` unit was independently rebuilt
**cold** and reported `exact; 1385 coverage bytes`, without any
full-set replay or truncated extent. No owned post-RET table is
separately counted; borrowed Win32 `SetRect` and other graphics/CRT
callees have not earned additional authored CODE credit. All 97
origin-unknown candidates remain excluded, the complete original
private game quad layout remains provisional and the Git checkpoint
is not a remote Oracle verification receipt.

### F289-F291 negative controls retained (no CODE credit)

F289 independently rechecked whole `ReplayRecords::FinalizeFile` at
`004138E0` (**375 native CODE**, 105 original instructions), tested
original transferred/file output/path/index/size and allocation
lifetimes. Existing natural source controls 342/372/384/396 bytes
are nonexact; recent physical triple DWORD grouping yields 408, also
nonexact. Retain native assembly/shape diff/private controls in
`.analysis/f289-replay-finalize/`, do not credit.

F290 read original whole 303-byte `ReplayScene::DrawSaveFilename`
`0042C270`, with 144-byte rendered background, 14-byte original replay
prefix literal, 8-byte runtime tint and two native caption branches.
Natural whole-function source/variable scope and physical object
size controls emitted 287/288/342/357 bytes, not exact. Retain
`.analysis/f290-replay-filename/` and no CODE credit.

F291 reviewed complete 301-byte `FontSurface::LoadGlyphOutline`
`0041C1B0` including original Win32 GetGlyphOutlineA twice, 20-byte
GLYPHMETRICS, 16-byte MAT2 affine identity, authentic original
free/new buffers and glyph metrics. A corrected meaningful source
with a 16-byte real matrix initialization temporary and actual old/new
buffer pointers emits **all 301 bytes and all five physical COFF
fields**, but native local stack ownership differs at 30 of 281
nonrelocation byte positions, so no exact claim. Five real
declaration-order controls failed to resolve the positions; retain
`.analysis/f291-font-glyph/`, zero CODE credit.

F289 also independently compared the 1,268-byte
`SpriteScene::RenderMirroredNode` old F254 1,279-byte/324-instruction
clone against all original 324 instructions, exposing not just local
EBP-slot differences but genuine x87 operation-shape differences.
Private `.analysis/f289-mirrored/` and
`.analysis/f254-sprite-boss/` retain the negative. No source/byte
credit for this boss until complete exact reconstruction.


## F293: cold-exact four original font/effects helpers in two large control call chains

Four complete originally authored game-specific functions downstream
of the separately F292-accepted entire 1,385-byte overlay boss and
the then-unaccepted (now separately F294 cold-exact) 1,722-byte Effects resource catalog were
independently reviewed via the pinned Japanese PE. Original native
functions and machine-code evidence live in `.analysis/f293-graphics-leaves/`;
pinned VC7.1 negative/positive source comparisons and full affected
4-unit cold replay at `.analysis/f293-leaf-probes/`.

| Function/address and reviewed origin | Entire original CODE | Native x86 instructions | Exact nonfield bytes | Native COFF fields | Full PE CODE SHA256 |
| --- | ---: | ---: | ---: | ---: | --- |
| FontSurface::ConfigureText `00413420` R103 | 64 | 22 | 64/64 | 0 | `b2168041d4e4d9617977f8a28a3e2aa97a11f72188c8261f782e97216415b651` |
| Effects::LoadResources `005F70E0` R100 | 84 | 25 | 48/48 | 9 | `26e3b771cd9296a4ac17f1b9d423fa34ff0e09a7de53a31633ff5c0153dcf5eb` |
| FontSurface::DecodePackedTextUnit `0041C9D0` R183 | 85 | 33 | 81/81 | 1 | `fb8963ee9d3b043a87b7024e0b292e8982e35274343e149140007788a69c86a3` |
| FontSurface::ReleaseRasterResources `0041C130` R109 | 119 | 39 | 103/103 | 4 | `7b848e9c7fe4570cdf2f900e6efc549ac363354fad64446ca0c56594b0f4e2a8` |

The original 64-byte font configuration method writes two actual
32-bit fields at this+4/+8, zeroes DWORD +0x10 and bytes +0x15/+0x14,
then copies a real unsigned mode byte at +0x25. Its true thiscall
`RET 0x0C` has no physical relocations. The original 84-byte Effects
load helper *first* calls the much larger resource catalog loader
`005F71F0` (nonexact **at F293**, but independently cold-accepted
by **F294**), then prints its two distinct native log
messages from `0065A078/0065A0A8`, and configures a genuine texture
receiver at this+0x28 through `0040B110(0x90,0x10)` and
`0040BB80(0065A090,0065A088)`. An early plausible source stored a
source-level pointer to the texture member and emitted 89 bytes,
**five too many**; reevaluating the pointer at each actual native call
recovers the entire 84-byte original, without an unused local alias.
The 85-byte two-byte packed font decoder's native return count is
**one byte in AL**. An initial integer-return C++ variant emitted
91 bytes, incorrectly generating `MOV EAX,1/2`; the actual return is
`unsigned char` with `MOV AL,1/2`, exactly matching the real 85-byte
function. It uses the actual native caller's `IsDoubleByte` at
`0041CA30` and the original `(word & 0xFF)<<8 |
(int)(word & 0xFF00)>>8` data conversion.
The complete 119-byte raster resource release helper frees a real
previous glyph buffer at +0x14 through native `00640F15` and clears
the field. Its actual old-buffer alias is stored at EBP-4, and its
original selected font call is **nested**
`DeleteObject(SelectObject(hdc, savedObject))`, not a separate local
variable; the original subsequently releases the window/DC and
zeroes saved HGDIOBJ/DC fields. Using real pointer alias lifetime
rather than fictional return caching recovered all native operations
and original 4 native relocation targets.

Final natural C++ sources are `src/FontConfigureF293.cpp`,
`src/EffectsLoadF293.cpp`, `src/FontDecodeF293.cpp` and
`src/FontReleaseF293.cpp`; all use pinned VC7.1
`/Od /Ob0 /Gy /GR- /GX- /GS /Zi`. The matching units
`font-surface-configure-text-00413420`,
`effects-load-resources-005f70e0`,
`font-surface-decode-packed-text-0041c9d0`,
`font-surface-release-raster-0041c130` were cold rebuilt
**only as the affected four-unit group**, with **4/4 exact**.
A private historical FontConfig probe incorrectly supplied an old
`?Configure@FontConfigF293@@QAEXMME@Z` *symbol name* to the
first match-unit manifest despite the genuinely correct full
64-byte new source, so the first cold replay was **3/4**. The failure
was audited, the manifest symbol fixed to the actually compiled
`?ConfigureText@FontConfigureF293@@QAEXKKE@Z`, and the same four
affected units rebuilt **4/4 exact**, not silently accepted on
probe evidence. No all-unit cold replay, manual byte patch, asm,
field mask, fake locals, truncated target or remote Oracle receipt.
All underlying Win32/CRT/VC7 helpers and 97 pending origin-unknown
functions remain uncredited; no private whole class definition is
asserted.


## F294: complete cold-exact 1,722-byte Effects::LoadPatternCatalog archive boss

The full original R067-authored game-specific pattern resource catalog
loader `Effects::LoadPatternCatalogAt005F71F0` at
`005F71F0..005F78A9` consists of **1,722 original native CODE bytes**
and **582 independently decoded complete x86 instructions** ending in
a real RET at `005F78A9`. Original full pinned PE CODE SHA256:
`6fc11b0e9aec650d60b8e4d00bca85e26a026d4dce9bed0d3a5a46bd6adb526d`.
The entire original Ghidra function/decompiler and full native physical
disassembly are at `.analysis/f274-effects-catalog/` and
`.analysis/f294-effects-catalog/`; the final natural C++ is
`src/EffectsLoadPatternCatalogF294.cpp`. The Ghidra decompiler's
opaque `TaskStack` type labels are *not* treated as proof of the
original private class names; only its real observed 16-byte
constructor/destructor at `00458880`/`004588B0` and scoped EH lifetime
are represented in source.

The original operation finds and opens the real
`data\system\effect\effect.pat` entry through game archive
lookup `0041CF00` and `0041D750`, and uses a genuine real 16-byte
stack scratch object, native exception frame and EH handler
`00656679`. It traverses the actual effect slot collection at
`this+0x78`, clears/deletes previously owned non-null sequences through
original game sequence `Clear`, indexed `At` and scalar deleting
destructor, and clears then resizes the physical slot collection from
its native file count. It reads each sequence ID and row count through
the original `ReadFile` IAT `0065712C`; on absent rows it performs
EH-backed native new(16) via `0064159D` and native `005F7F20`
constructor, retains real C++ conditional pointer results and original
EH state transition, then calls real `005F8000` resize with an actual
16-byte scratch object. Its full nested record loop uses original
`005F7FC0` access and actual four two-byte reads into the four
observed native per-item offsets. Native record-kind bytes 0 and 1
set the original opposite `record+0xC` flags. Kind 2 calls native
`00458790` graphics initialization, reads the original texture
record, all original one-byte components and shorts, and converts
one actual signed short three times with native `FMUL` against game
float global `00658044`, then converts three more signed shorts to
float without the scale. No invented end-of-file check, CloseHandle,
extra file read, or member destruction absent from original control
flow was added. The native C++ cleanup restores the entire EH frame.

The first entire natural C++ source generated **all 1,722 bytes** and
all **582 original x86 instruction forms and 91 physical COFF
relocations** on pinned VC7.1 `/Od /Ob0 /Gy /GR- /GX /GS /Zi`, but
matched only **1,244/1,358** nonrelocation bytes. The difference was
actual compiler local storage, not missing gameplay. Many genuine
C++ declaration/lexical-scope permutations failed. Combining the
**nine actually used parser values** (short scratch numeric conversion,
row count, signed flag storage, row index, sequence ID, file row count,
real Win32 file handle, transferred-byte count, outer file index)
into an ordinary typed physical parser state struct
`EffectVarsGroupF294` restored **1,347/1,358** bytes without any
additional locals, allocation or source-level side effects. The
original C++ call to resize slots uses a **typed null pointer rvalue
bound to `EffectSequenceF294* const&`**; using such an actual reference
argument instead of a preallocated named `empty` variable produces
exactly native EBP-0x4C temporary null pointer and the original
compiler `delete`-expression aliases at EBP-0x48 and EBP-0x44,
reducing mismatches to four.

The final four mismatches all referred to the same **single-byte
file record kind at native EBP-0x25**, where the compiler allocates
a real **four-byte stack storage slot** at EBP-0x28..-0x25. A plain
C++ `signed char kind` inside the physical struct put the same
input in the first byte (EBP-0x28), but native `ReadFile` and all
three subsequent signed `MOVSX` operations read the *last* byte of
that existing storage. The final source models the exact
compiler-allocated four-byte input region as one genuine `DWORD
kindStorage` and passes/accesses the observed signed byte at
byte offset 3 through ordinary typed C++ member byte-address
operations (`R(signed char,&values.kindStorage,3)`). The extra
three byte positions were **already part of the original stack slot**,
are never initialized or accessed as gameplay state, and do not
allocate a separate dummy field, increase the original stack frame,
or add any machine instructions. This is a borrowed physical
original-input storage carrier, not evidence of the unobserved
original author's preferred local type.

This final whole source reproduces **all 1,722/1,722 original CODE
bytes**, all **1,358/1,358 nonrelocation byte positions** and
**91/91 genuine physical native COFF relocation offsets/types and
solved destinations**, including original EH/Win32 and all real
game vector/record calls, without masked/missing fields or copying
original machine bytes. Only the **one changed canonical unit**
`effects-load-pattern-catalog-005f71f0` was cold rebuilt from source
and reported `exact; 1722 coverage bytes` / **1/1 exact**. All
failed controls and the local full acceptance receipt are retained
privately in `.analysis/f294-effects-catalog/`, rather than being
discarded or treated as authoritative hypotheses. F293's original
84-byte resource loader directly calling the now accepted boss,
F281/F285 native effect spawners and F283 child constructor were
previously cold accepted independently, with no duplicate CODE
credit. Full original private effect catalog owner and STL/CRT
implementations remain separately unproven, and all 97 origin-pending
functions remain excluded. No all-unit cold replay, byte grafts,
manual assembly, artificial padding, cropped original function or
remote Oracle acceptance was claimed.


## F300: 203-byte BattleObject default native constructor cold exact

The R166-authored game-specific `BattleObject::InitializeDefaultsAt0045B760`
occupies **all 203 original PE-backed CODE bytes** at `0045B760..0045B82A`,
with **42 independently decoded x86 instructions** and actual native plain
RET `0045B82A`. Full pinned Japanese PE body SHA256 is
`be111ce8814061e291a70639e4ffd1bf9dff77a6f14385c16882f2594c704550`.
The original physical disassembly, 1/1 native structural-exact first natural
source, canonical physical COFF comparison and affected-unit cold receipt
are preserved in `.analysis/f300-battle-leaves/` and
`.analysis/f300-battle-probes/`. Authored whole source is
`src/BattleDefaultsF300.cpp`, using a borrowed polymorphic game-base call ABI
rather than an invented complete hidden BattleObject class layout.

The native constructor calls exactly the true game base constructor
`00458650`, then installs the real derived virtual table `00659064`.
It sets 15 real fields to zero in the original native source order: short
+0x80, DWORD +0x7C, short +0x82, DWORDs +0x8C/+0x90/+0x94/+0x98,
DWORDs +0x50/+0x54/+0x58/+0x5C/+0x4C, and shorts +0x84/+0x86/+0x88.
The compiler naturally generates the exact original ordinary `thiscall`
register return and no unnecessary EH frame. The **first full natural C++
probe** in pinned VC7.1 `/Od /Ob0 /Gy /GR- /GX- /GS /Zi` emitted **all
203 original machine bytes**, **195/195** comparable nonrelocation byte
positions and **both** authentic physical COFF fields: one REL32 for base
constructor at source offset +0xB and one DIR32 for the actual derived vtable
at source offset +0x14. No guessed game member layout, copied target bytes,
manual assembly or padding was necessary.

Only canonical matching unit `battle-object-initialize-defaults-0045b760`
was built **cold by itself**, reporting `exact; 203 coverage bytes`. The
underlying real base constructor and 97 still-unresolved origin candidates
receive no additional authorship/CODE coverage. Local Git source checkpoint
is not external Oracle verification; no all-unit replay, truncated extent or
relocation masks were used.

### F297-F299 retained evidence for unresolved bosses and two-list pruning

The full original 1,766-byte `FontSurface::RasterizeText` core at
`0041C2E0` (551 complete original x86 instructions) was independently
re-reviewed. The first source models native 4-byte/2-byte raster output,
inline text `\c`, `\e`, `\n` controls, glyph spacing, per-scanline
RGB gradients and signed glyph/bitmap addressing; real shared output
codepoint/advance/index lifetimes restore the native `0x38` frame.
Grounded switch/case ordering and signed branch operands narrowed original
source emission from 1,717 to 1,712 bytes but **not exact**; control-flow
and integer signed division differ. Retain `.analysis/f297-font-boss/` and
`.analysis/f299-font-raster/`, zero CODE credit.

The game-specific 276-byte two-side effect queue manager at `005F7D80`
reproduces entire control instruction shapes and all 10 native COFF fields,
but native iterator End return temporary and real freed object pointer
occupy different physical EBP slots. Scoped real index/count lifetimes
raise comparison from **222/236 to 233/236** nonrelocation bytes.
Genuine alternative loop-source, iterator receiver, used-free-pointer scope
and typed aggregate controls remain negative in `.analysis/f297-aux-prune/`
and `.analysis/f298-aux-lifetimes/`, zero coverage credit.

The full 1,252-byte `ReplayRecords::AppendRecord` had 19 unresolved
stack slot bytes (1,033/1,052) **at the F296 stage**; the later
**F326 entire-function cold-exact proof below** resolves them via
true observed 56-byte iterator/record storage and constructor order.
Retain the genuine failed typed iterator/count/written controls under
`.analysis/f296-append-interleave/` as historical evidence.


## F301: cold-exact 247-byte FighterState notice state machine

Original R103-authored game-specific `FighterState::AdvanceNoticeLevelsAt0045D710`
comprises **all 247 PE-backed CODE bytes** at `0045D710..0045D806`,
**64 independently decoded x86 instructions** and an authentic plain RET
at `0045D806`. Full original CODE SHA256:
`a76adeb47b34c648d3d1e0d274297fe54aa83d4bfc50442649bbd1a977b3453a`.
The complete physical disassembly, original decompile, first 253-byte
negative natural source and the accepted 247-byte entire C++ probe/cold
receipt are retained at `.analysis/f300-battle-leaves/` and
`.analysis/f300-battle-probes/`; final source
`src/FighterNoticeLevelsF301.cpp` represents only the three real physical
FighterState fields, not a made-up complete game object.

The original switch uses a signed character mode at fighter+0x6E6 and
updates only the two actual signed short counters at +0x6EA and +0x6EC.
Mode 0 increments first only below 25, mode 1 independently decreases
both counters only above zero, and mode 2 decreases first if positive
and increases second if below 5. Cases 0/1/2 have the complete
original long/short exit branches and per-field signed extensions.
The first natural source emitted 253 bytes with a 0xC stack frame
because `signed char mode=FIELD(...); switch(mode)` required an extra
6-byte load/store to a distinct unoptimized switch temporary.
Original native uses one direct signed byte switch expression, with
only one local at EBP-8, a genuine 0x8 frame and no extra copy. Using
`switch(FIELD(signed char,0x6E6))` naturally reconstructs exactly the
**full 247 CODE bytes and all 247/247 nonfield positions** under pinned
VC7.1 `/Od /Ob0 /Gy /GR- /GX- /GS /Zi`; it has **zero actual COFF
relocation fields**. Only the new unit
`fighter-state-advance-notice-levels-0045d710` was cold rebuilt and
reported `exact; 247 coverage bytes`. Original private FighterState
class identity/layout, library/CRT implementations and all 97 unknown
origins remain uncredited. No artificial code, byte graft, assembly,
relocation mask, truncated function, all-unit cold replay or remote
Oracle receipt.


## F303: exact 260-byte battle direction/button input packer

Original R054-authored `BattleInput::PackDirectionBits` is the entire
original native PE extent `00455B30..00455C33` (**260 CODE bytes**,
**79 independent original x86 instructions**, authentic RET at
`00455C33`); pinned Japanese PE body SHA256
`810198e55fb195f65720b36989c66a223a3acc69da1d6ee66d6773f042eafa76`.
Read-only original function/decompiler/native assembly, initial 253-byte
full C++ control probe, positive alternative expression controls and
COFF/cold proof remain under `.analysis/f303-battle-input/`; final
whole-function source is `src/BattleInputPackDirectionF303.cpp`.

The actual fighter native signed 32-bit direction axes at +`0x4DC`
and +`0x4E0` generate the low four bits using signed `<0` and `>0`
conditions. Four real unsigned 32-bit button fields at +`0x4E8`,
+`0x4EC`, +`0x4F0`, +`0x4F4` generate the other four bits, using
original unsigned `>0` conditions. All eight actual original native
`SETL`/`SETG`/`SETA`, `MOVZX`/`SHL` and successive per-byte `OR`
instructions are reproduced. The byte local is physically EBP-`0x1D`;
exactly the original next 28 stack bytes are cleared through the
authentic C runtime `memset` call (not fabricated scratch padding).
The complete code then passes the real native argument `90` and a pointer
to that actual packed byte into the game command queue at fighter
+`0x518` through original `00455C40`. Its class interior is borrowed
only as that physically observed call boundary.

A first natural C++ with implicit integer promotions for seven boolean
bit-shift expressions generated **253 bytes**, replacing the native
byte-sized `SETcc -> MOVZX` with different `XOR`/`SBB` or zero-init
lowering. Explicitly converting each genuine comparison to
`unsigned char` before left-shift reproduces the entire **260 bytes**,
**252/252** nonrelocation byte positions and **2/2 authentic native
physical COFF fields**, at offsets +`0xE5` (real `memset` target
`00640490`) and +`0xFC` (real game queue call `00455C40`). Pinned
VC7.1 `/Od /Ob0 /Gy /GR- /GX- /GS /Zi` rebuilt only canonical
`battle-input-pack-direction-bits-00455b30` as **one affected cold
unit**, reporting `exact; 260 coverage bytes`. No original queue
implementation, unknown private fighter layout, CRT, 97 pending
origins or nonnative padding is credited. Local Git commit is not
remote Oracle verification; no all-unit replay or source byte graft.

### F302 large font rasterizer and F298 effect-list negative controls

The complete 1,766-byte/551-original-instruction `FontSurface::RasterizeText`
giant at `0041C2E0` has been reexamined, not dismissed. Reconstructed
real 4-byte color and 2-byte pixel paths, signed font spacing, actual
embedded `\c`, `\e`, `\n` byte controls and native Win32/CRT
behavior in `.analysis/f299-font-raster/`. The best whole-function
source emits exactly **1,766 bytes and 551 x86 instructions** with
**15 genuine native COFF relocations**, but only **1,626/1,706**
nonfield bytes match. Multiple ordinary source field-local grouping
and source-order hypotheses in `.analysis/f302-font-lifetimes/`
improve to **1,647/1,706** but do not solve all stack slots.
The two-side 276-byte `AuxEffectManager::AdvanceAndPruneTwoLists`
function at `005F7D80` also compiles its entire original 276 bytes
and authentic 10 native fields but currently matches **233/236**
nonfield bytes; the final three are original `End()` iterator return
and actual freed-object pointer lifetimes. Do not credit either incomplete
function, introduce artificial fields, or claim external Oracle success.


## F304: 235-byte native Effects resource destructor cold-exact

The R177-authored static Effects catalogue/resource release routine at
`005F6FF0..005F70DA` is one **whole 235-byte PE CODE function**,
**70 original decoded x86 instructions**, authentic RET at `005F70DA`,
full PE body SHA256
`1f53e7d10f210480c80997e41e95e0e5a4d2e34c6bdc86684da27fcb1857a17c`.
Physical source and native call evidence are retained at
`.analysis/f304-static-resources/` with canonical adopted file
`src/StaticEffectReleaseF304.cpp`. The source only models borrowed
physical actual game receiver offsets and real member destruction;
it does not claim a recovered complete original private class layout.

This native destructor calls original `005F7140` graphics cleanup,
walks the true effect collection at owner+0x78 with actual unsigned
`Size` `005F8340` and **two** original `At` `005F8380` calls per
non-null entry, invokes authentic scalar deleting destructor
`005F7EA0`, and finally calls native collection Clear `005F83E0`.
Pinned VC7.1 naturally emits **the original EH handler `0065665C`**,
0x14 frame, and states **2,1,0,-1**. In actual reverse physical
member-lifetime order it destroys collection +0x78 through
`005F8320`, native 80-byte texture at +0x28 through `0040AE40`, and
**exactly two** original 20-byte side-list members at owner+0
through the authentic native vector destructor iterator `00641D4A`
with callback `005F8090`. The physical 20- and 80-byte carriers are
anchored in original receiver/allocation boundaries, not padded to
force an instruction sequence or credited as authored CODE.

The **first complete grounded natural C++ source** compiled all
235 original bytes and **179/179** nonfield bytes exactly under pinned
VC7.1 `/Od /Ob0 /Gy /GR- /GX /GS /Zi`, with **all 14/14 physical
COFF DIR32/REL32 fields** exactly matching original offsets, types
and native solved targets, including the actual EH/exception-list
fields. The canonical unit
`static-battle-resources-release-owned-005f6ff0` was rebuilt **cold
only alongside new F303**, reporting `2/2 exact` across two source
objects, never an all-unit cold replay. Existing F294 effect catalogue
loader and original F293 wrapper or effect-child code receive no
additional CODE credit from a call; 97 origin-pending functions and
VC7 runtime helpers remain uncredited. Original private class names
remain provisional, and local Git is not remote Oracle verification.


## F309: five complete 243-byte fighter initialization constructors cold-exact

Five separate R050-authored native game-specific constructors were audited
as whole functions, then modeled in **five distinct natural C++ files**
using pinned VC7.1 `/Od /Ob0 /Gy /GR- /GX- /GS /Zi`. Their boundaries,
bytes and genuine COFF refs are separately compared, not credited merely
because they share a common recognizable initialization pattern:

| Constructor / PE start | Whole native CODE | Original instructions | Nonfield bytes | Authentic COFF fields | Full original CODE SHA256 |
| --- | ---: | ---: | ---: | ---: | --- |
| Sakuya `004C0820` | 243 | 56 | 219/219 | 6 | `77f91bdb5bbf1353961e5b9c43dc7ff28d4a6ba335291356c3decb39caf4c4a9` |
| Alice `004E2C90` | 243 | 56 | 219/219 | 6 | `e46aa70683e81564fed1706a02d9f39ecd3b5cdd061ef0b5cf94514d57c1daf2` |
| Patchouli `005021C0` | 243 | 56 | 219/219 | 6 | `0b9d6066a0d350a47f1f85e36f2bf9f3e0ff57a52674a6894f1eb4ea7edf1835` |
| Yukari `00597380` | 243 | 56 | 219/219 | 6 | `5b20eb04a0ec250846f6f9ba325daff1cb10fcfc30e6a55bebfc5d80aed24e76` |
| Suika `005C0AB0` | 243 | 56 | 219/219 | 6 | `daedd072f8948e057332e71073670494103d9f48958dd0b7c18449ef952b9611` |

All five truly call the independently F287-accepted native fighter base
constructor `004567B0`, install their **different** game vtables, and
zero real game-specific short counters (Sakuya, Alice, Patchouli, Yukari
at +0xEFC/+0xEFE; Suika at +0xF28/+0xF2A). They set original byte
+0x713=1, write unique native character resource names and tags to
this+0xC4 and this+0x1C8 through actual native `strcpy` `00641B80`,
set real stage/pattern +0x478 (respectively `0x27D`, `0x2AD`, `0x32C`,
`0x25E`, `0x2A6`), texture slot count at +0x532 (Yukari **12**,
others 10), original `-10.0f` at +0x6C and all ten exact native
image/page flag bytes +0x705..+0x70E in unchanged original order.
The already F223-accepted native Marisa constructor was used only as
a first C++ hypothesis template, not as proof that any of the five
other functions matched. Each independently emits the complete 243
original native bytes, 56 original x86 instructions, all 219/219
nonrelocation bytes, plus six authentic physical COFF relocation
offsets/types/solved native destinations. The full five-unit affected
**cold replay returned 5/5 exact**.

Direct pinned PE relocation and string extraction also corrected a
misleading prior Patchouli name estimate: the actual target
`00659754` contains `patchouli`, while `00659758` contains only its
suffix `houli`; the new independently built source correctly references
`g_PatchouliNameAt00659754`. The five files are
`src/SakuyaInitF309.cpp`, `src/AliceInitF309.cpp`,
`src/PatchouliInitF309.cpp`, `src/YukariInitF309.cpp`,
`src/SuikaInitF309.cpp`. Private target Ghidra/decompile, independent
COFF previews, corrected string checks, and cold replay receipt are in
`.analysis/f309-fighter-inits/`. These are five **different full game
functions** and earn 1,215 newly authored CODE bytes, with no credit
for already accepted F223/F287 base implementations, imported CRT or
any of the 97 origin-pending candidates. Private complete class layouts
are not asserted by their borrowed inherited constructor interfaces;
there was no machine byte graft, asm, fake locals, arbitrary filler,
relocation mask, full-set replay or external Oracle receipt.


## F311: four additional entire fighter constructors with independent native proof

Reimu, Meiling, Remilia, and Yuyuko each contain their own original
authored and newly cold-exact game-specific fighter initialization
function. Unlike assuming a single shared library clone, each entire
native PE extent, control instruction count, relocation field and unique
character-specific data was independently verified before acceptance:

| Game fighter / start | Reviewed origin | Original CODE | Native x86 instructions | Exact nonfield bytes | Native COFF fields | Full original CODE SHA256 |
| --- | --- | ---: | ---: | ---: | ---: | --- |
| Reimu `0046D080` | R046 authored | 218 | 52 | 194/194 | 6 | `d4b174f2bd88e27b24d50bcad45c3c14f47e1ec0209c38cacc83502187da8376` |
| Meiling `005E2090` | R050 authored | 218 | 52 | 194/194 | 6 | `d6ef52ad4c4830182c8e3ad563eab5b4e31ef1cb1b1fb77f369932744ed0fd81` |
| Remilia `00551980` | R050 authored | 277 | 62 | 253/253 | 6 | `150d9c7c5277eac1ef6de663d531e70ed1e37134569913c217c6616c1fcca214` |
| Yuyuko `00574100` | R050 authored | 266 | 60 | 242/242 | 6 | `0742421646749819f30609107921e3da0db7e0b3999841de2a155661d56eb149` |

All four call true native fighter base `004567B0`, install their
separate original vtables and load original character name/data strings
through exactly two actual native `strcpy` targets `00641B80`, into
this+0xC4/+0x1C8. They initialize real byte stage flag +0x713=1,
pattern counters at +0x478 (Reimu `0x287`, Meiling `0x264`, Remilia
`0x2A0`, Yuyuko `0x21C`), slots byte +0x532 (Remilia **11**,
others 10), float `-10.0f` at +0x6C and all ten observed page-byte
flags +0x705..+0x70E. Reimu and Meiling deliberately do **not**
initialize the two high-offset short counters present in F309, matching
their full 218-byte native code instead of grafting the template.
Remilia additionally clears two exact shorts at +0x6FA/+0x6FC, then
byte +0x6F8; Yuyuko clears two shorts at +0xEFA/+0xF10, preserving
each true native write width and order.

The direct PE/COFF evidence corrected an initial Remilia resource
string hypothesis from `00659A30` to the true native `00659A34`, the
start of `remilia`. This correction was made **before** acceptance
and the four individual whole source files were rebuilt and compared:
`src/ReimuInitF311.cpp`, `src/MeilingInitF311.cpp`,
`src/RemiliaInitF311.cpp`, `src/YuyukoInitF311.cpp`. The five F309
243-byte constructor sources were a first natural-code reference only,
not proof of these four different 218/266/277-byte complete functions.
Each pinned VC7.1 `/Od /Ob0 /Gy /GR- /GX- /GS /Zi` object matches
its **entire native CODE span**, all nonfield bytes and all six
relocations. The affected four-unit-only serial cold replay reports
**4/4 exact**, adding 979 new authored CODE bytes without double credit
for prior F287/F309/Marisa/F223 sources. Full Ghidra original evidence,
PE resource strings, positive COFF and local cold receipt are retained
at `.analysis/f311-fighter-variants/`. All 97 unknown-origin functions,
CRT and other helper implementation bytes remain uncredited; no
assembly, copying target machine bytes, inert padding, masked COFF
fields or all-unit replay was used. This local checkpoint is not a
remote Oracle acceptance receipt.


## F315: two complete fighter round resets cold-exact (295 + 261 bytes)

Two R050-authored complete game fighter round reset functions were
independently decoded across their actual original Japanese PE extents:

| Function, native start/end | Original CODE | Native x86 instructions | Nonrelocation bytes | Authentic physical COFF fields | Complete original CODE SHA256 |
| --- | ---: | ---: | ---: | ---: | --- |
| YukariFighter::ResetRound `00597500..00597626` | 295 | 55 | 291/291 | 1 (native `00457010`) | `524ad563a04a58001bcc5d56ce3c09a0fd89e28ebd7780758947758b2d67fc8c` |
| SuikaFighter::ResetRound `005C0C30..005C0D34` | 261 | 49 | 249/249 | 3 (two globals, native `00457010`) | `edc6787d3634e9baaf52dbf596228022973b2c3d081a454bb02a49b30aee8d16` |

Full independent original Ghidra decompilation/native machine code, first
meaningful complete VC7.1 C++ sources, COFF exact proof and only-two-unit
serial cold replay receipt are preserved in `.analysis/f315-fighter-round/`;
final native-faithful C++ sources `src/YukariResetRoundF315.cpp` and
`src/SuikaResetRoundF315.cpp`. Neither original class has a fabricated
private layout: the source represents only independently observed game
16-bit state flags and actual inherited reset call.

Yukari resets 21 separately observed word fields: +0xF00..+0xF1A in
2-byte native steps, +0xEFA, genuine second write to +0xF0A, +0xF32
and +0xF30, and +0x512/+0x514/+0x516. It then calls the true
inherited FighterState::ResetBaseRound `00457010` **before** resetting
its two other high shorts +0xEFC and +0xEFE. Suika resets original
words +0xEFC/+0xEFE and +0xF00..+0xF06, +0xEFA, a genuine second
write to +0xF06, +0xF26, +0xF1C..+0xF24 and shared input statuses
+0x512/+0x514/+0x516. It then sets two actual absolute global
byte flags at `0066C23A` and `0066C239` to `0xFF`, calls the original
inherited reset `00457010`, and finally clears original +0xF28 and
+0xF2A. The two global bytes are **not** assumed to be fighter fields,
and Suika's short assignments are not conflated with Yukari's.

Both were accepted at whole original native boundaries under pinned VC7.1
`/Od /Ob0 /Gy /GR- /GX- /GS /Zi`: **all 556 original CODE bytes**,
**540/540** comparable bytes and **4/4 physical COFF relocation fields**.
Only `yukari-fighter-reset-round-00597500` and
`suika-fighter-reset-round-005c0c30` were cold rebuilt **together as
the affected two-unit group**, reporting **2/2 exact**, never a
full replay. Previously accepted inherited FighterState reset bodies
are not double counted, nor are 97 origin-unknown candidates, CRT
or external game implementation bytes. No byte grafting, assembly,
spurious padding, or Oracle verification is claimed.

### Additional independently reviewed nonexact large bosses

F313 reexamined the **whole 874-byte** `SuikaFighter::UpdateSpecialState`
`005C3FB0`, **237 original x86 instructions, 20 genuine COFF fields**
with complete native disassembly and source, including actual random
projectile spawning, distance-based meter response and game action
behaviour. The first complete 874-byte source used two side-effect comma
expressions for shot positions, generating the wrong native argument
evaluation order and `0x44` frame, only 549/794 nonfield bytes matching.
Substituting simple genuine C++ expression arguments reproduces the
real original RTL push/float/Rand interleaving (672/794), then removing
eight *actually unused*, purely speculative source locals restores the
original real **0x24 stack frame** and **742/794** nonfield byte matches,
retaining all 20 physical COFF fields. The remaining mismatch is not
a missing script path: original `FLD` zero-comparison order and four
original opponent pointer evaluation/`FSUB` patterns differ from VC7
source lowering, even though semantic source expressions are equivalent.
Retain `.analysis/f313-suika-boss/` and `.analysis/f314-suika-shots/`,
**zero CODE credit until whole exact**; do not use fake temporaries,
manual x86, masked relocations or target-byte grafting.

F312 reexamined 1,252-byte `ReplayRecords::AppendRecord` using **12
genuine nested iterator lexical scopes** on the complete source while
retaining all six observed constructors and 50 native relocations.
The best original all-functions full-source probe remains **1033/1052**
nonrelocation bytes; 19 bytes still reflect true different physical
iterator layouts. No result from the 12 experiments is credited.
The full 1,766-byte font rasterizer and incomplete two-side Effects
pruner are likewise retained as independent unaccepted native
experiments, not included in authored CODE coverage.


## F314: four independent whole 211/175/175/235-byte fighter round resets exact

Separate R050-authored full original native CODE functions:

| Character/function | Original native span | Entire CODE bytes | Independent native x86 instructions | Exact comparable bytes | Original COFF fields | Whole native original SHA256 |
| --- | --- | ---: | ---: | ---: | ---: | --- |
| PatchouliFighter::ResetRound | `00502340..00502412` | 211 | 41 | 207/207 | 1 | `9f1aeec9014c80d64512c2031507d8af436851db94cd5a6e90d42322b6712d61` |
| RemiliaFighter::ResetRound | `00551B20..00551BCE` | 175 | 35 | 171/171 | 1 | `6e842229549d57ec86e02d4a7d0c2f18ea039c128abe8a533791d49081936e7c` |
| YuyukoFighter::ResetRound | `00574290..0057433E` | 175 | 35 | 171/171 | 1 | `628c0ac2f579878379986a9852bc23558a9ab7fd4eb141e280f53ffd951b27e8` |
| MeilingFighter::ResetRound | `005E21F0..005E22DA` | 235 | 45 | 231/231 | 1 | `8158cc21587aedeb1e6596dc903654f9e330d9a0cd27214a5dcd4740b42f994a` |

These four real game-specific procedures reset **distinct, physical
original unsigned-short fields** at individually observed FighterState
offsets in the full native ordering, without replacing them with broad
memset that would alter the original instruction code. They then invoke
the original inherited `FighterState::ResetRound` at `00457010`, already
accepted separately as a whole 1,151-byte parent and never
double-credited. The native R050 author provenance and entire original
PE code boundaries are checked for each function; the first full
natural VC7.1 C++ source for each already reproduced the authentic
`/Od /Ob0 /Gy /GR- /GX- /GS /Zi` machine code, all nonrelocation byte
positions and exactly **one authentic REL32 field** to parent reset.
Original native Ghidra/decompiler/complete source, COFF comparisons
and 4/4 *affected-only* cold replay are under
`.analysis/f314-reset-specials/`. Adopted sources
`src/PatchouliResetF314.cpp`, `src/RemiliaResetF314.cpp`,
`src/YuyukoResetF314.cpp`, `src/MeilingResetF314.cpp`; all four
whole original functions earn **796** newly authored CODE bytes,
without claiming private original FighterState source layout.

The persisted worktree already contained noncommitted F315 Yukari
(295 bytes, 291/291 nonfield, 1 genuine REL32) and Suika (261 bytes,
249/249 nonfield, 2 true original global DIR32 and 1 base-reset REL32)
source/tracking from the same reconstruction workflow. Instead of
ignoring/abandoning them or rewriting them blindly, independently
rechecked their complete original native original PE 55/49 instructions
and hashes, native COFF relocation layout, exact natural C++ source
bytes and canonical manifest hashes. Their **2/2 exact affected-unit
cold replay** from `.analysis/f315-fighter-round/` is preserved, as
are their authored files `src/YukariResetRoundF315.cpp` and
`src/SuikaResetRoundF315.cpp`. F314 added *only* four other unique
native functions and tracked them without F315 double-counting.
Six full originals total **1,352 CODE bytes**: no source
padding, added dummy locals, inline assembly, byte grafting, masked
relocations, cropped comparisons, CRT/VC7 authored credit, or full-unit
cold replay. This local Git checkpoint is not an external Oracle receipt.


## F317: full native 398-byte FontSurface::RenderTextToTexture exact

Original R052-authored `FontSurface::RenderTextToTexture` starts at
`00413460` and ends at native RET `004135ED`. The pinned target PE
contains **398 complete CODE bytes**, **128 independently decoded native
x86 instructions**, and original body SHA256
`f879de336a20a85f1062eef0a7e18a6a0a69b3fa3ad72461ace01a194ea2599c`.
Full read-only original Ghidra/decompiler/disassembly, initial negative
406/397-byte source comparisons, exact 398-byte pinned VC7.1 object,
relocation details and single-unit cold acceptance are at
`.analysis/f317-font-texture/`. Final naturally authored source is
`src/FontRenderTextureF317.cpp`.

This native function conditionally copies this+0x14 byte mode to
this+0x15 according to the last caller flag; otherwise sets +0x15=0.
It calls the original **D3D8 texture vtable +0x40 LockRect** on actual
texture owner at `this+0`, saving the original 8-byte D3DLOCKED_RECT
with `pBits` at real EBP-0x10, and proceeds only on D3D_OK. It
clamps signed 8-bit raster output depth to at most 5, stores the actual
colour mode at +0x24, zeroes float +0x1C and writes 6.0f at +0x20.
It allocates exactly **0x38 bytes** of real glyph raster owner through
original new `0064159D` under **native automatic `/GX` exception
handler `006550B5`**, invokes genuine raster constructor `0041BF90`
with one zero and stores the result at +0x18. It calls true raster
`ConfigureTint` `0041C060` with original source float pointer
`006578B0`, native 32-bit zero-extended mode from +0x24 and caller
RGB bytes. It then converts the two actual float fields via authentic
VC7 `_ftol` `006406AC` twice, and invokes the real nine-argument
`FontSurface::RasterizeText` core `0041C2E0` with original caller
text pointer, real `D3DLOCKED_RECT::pBits`, dimensions 0x400×0x100,
max width 0x230, native converted x/y and the original 4/depth.
The source naturally follows native C++ `delete` semantics through the
original scalar deleting destructor `00413620`, **without clearing the
original owner pointer behind the programmer's back**. It then calls
true D3D8 vtable +0x44 UnlockRect, saves native depth at this+0x14,
and on all paths finally writes 5 to this+0xC.

First complete real-source probe emitted 406 bytes, but a separate
`if (member)` check wrapped normal C++ `delete`, adding 9 instructions
bytes the target never has. Removing the redundant guard emits 397
bytes, and original native assembly showed a distinct `MOVZX` from
one unsigned mode byte into a **32-bit zero-extended parameter** for
`ConfigureTint`, where the provisional source incorrectly declared
`unsigned char` and generated a shorter `MOV DL`. Correcting the
callee's *genuine calling-convention parameter type* restores the one
byte, for **398/398 complete original native CODE**, all **350/350
nonfield bytes** and **12/12 authentic native COFF relocation offsets,
types and solved destinations**, including original EH handler,
Win32/CRT new, two ftol helpers, font ctor/delete and raster draw call.
Pinned VC7.1 `/Od /Ob0 /Gy /GR- /GX /GS /Zi` built only canonical
`font-surface-render-text-to-texture-00413460` from clean C++ source
and accepted via **1/1 affected-unit cold replay**, never a full
replay. The invoked 1,766-byte rasterizer was nonexact at this F317 checkpoint,
but was later independently F319-cold-accepted and does not inherit exact credit; D3D/Win32, CRT/VC7 code and all 97 pending
origins are also uncredited. Native borrowed owner sizes are not claims
of complete original class layout, and local Git is not Oracle proof.

### F316: 746-byte SpriteSequence source-lifetime boss still nonexact

The entire original R035-authored 746-byte
`SpriteSequence::RenderElements` at `00411110` has **198 original
x86 instruction forms and authentic 0xBC frame**. The best prior
semantically meaningful original C++ source also emits 198 forms, but
734 total bytes: original `end` iterator and `x` float are genuine
8-bit-vs-32-bit EBP displacement differences (native -0x9C/-0x98,
provisional -0x10/-0xC), four occurrences of three extra bytes each.
The quad, rectangle, tint, counter and iterator have a distinct actual
physical lifetime layout, not evidence of synthetic filler. 62 further
real scope/declaration permutations of existing used RECT/tint/iterator
/x/counter under `.analysis/f316-sequence-scope/` generated 716, 725
or 734 bytes, none exact. Additional genuinely motivated 132-byte
physical quad placement-construction experiments produced 793/799
bytes with extra C++ placement runtime and are not accepted. All
negative sources/COFF/logs remain privately available; no guessed
text owner layouts, padding instructions, manual assembly, cropped
original extent, masked fields or authored CODE credit is claimed.


## F318: exact 301-byte FontSurface glyph outline loader from a real 64-byte frame

The original R053-authored `FontSurface::LoadGlyphOutline` is exactly
**301 native CODE bytes** across `0041C1B0..0041C2DC`, with **102
independently decoded original x86 instructions** ending in native
`RET 4` at `0041C2DA`. The complete Japanese PE CODE SHA256 is
`85ed2a07060abf35523608a7b6a33bd45fb52a5364e781aa669074ee0a510948`.
Native read-only Ghidra/decompile and previous negative F291 source
experiments are at `.analysis/f291-font-glyph/`. Final accepted natural
C++ `src/FontLoadGlyphOutlineF318.cpp`, full original PE/COFF compare
and only-affected-unit cold proof at `.analysis/f318-font-stack/`.

The whole routine first checks the real HDC at this+4 and mandatory
font pointer at this+8, then clears exactly 20 bytes of native Win32
`GLYPHMETRICS` with `memset` `00640490`. It initializes four real
source DWORDs for the original identity `MAT2`, copies their values
in its original physical order into a separate 16-byte Win32 `MAT2`,
then calls real `GetGlyphOutlineA` IAT at `0065703C` to measure the
glyph. If the prior bitmap pointer at this+0x14 exists it frees it
through original CRT `00640F15`, clears that field, allocates exactly
the measured glyph bytes through original operator new `0064159D`,
and calls `GetGlyphOutlineA` again to fill the output buffer. It
stores the native glyph black-box width at this+0x20, height +0x1C,
actual aligned row stride +0x24 from glyph-size / glyph-height, and
the original X/Y origin offsets +0x30/+0x34. These are original
observed semantics; no invented error branch or fallback was added.

The previous F291 natural whole C++ source emitted all **301 bytes**
and all five physical COFF fields, but mismatched 30 of 281 nonfield
byte positions because independent unoptimized local allocations
selected the wrong physical EBP slots. Re-reading the **full original
0x44-byte stack frame**, we found that after `this` at EBP−0x44,
the following **64 physically observed bytes** are all used:

| Actual original EBP slots | Native source value / size |
| --- | --- |
| −0x40, −0x3C | new glyph output pointer and old glyph output pointer; 4 bytes each |
| −0x38..−0x25 | actual 20-byte `GLYPHMETRICS` |
| −0x24 | returned glyph byte count; 4 bytes |
| −0x20..−0x11 | actual 16-byte `MAT2` |
| −0x10, −0xC, −0x8, −0x4 | four real initialization words, including both `0x00010000` diagonal entries |

Putting these **actual used fields**, in the independently observed
order, into one natural `GlyphFrameF318` struct of exactly 64 bytes
lets pinned VC7.1 `/Od /Ob0 /Gy /GR- /GX- /GS /Zi` assign the exact
original stack operands, rather than inserting any fake padding.
Its first complete C++ probe consequently reconstructs the entire
**301/301 original CODE bytes, all 281/281 comparable positions and
5/5 true COFF relocation offsets/types/solved native targets**:
`memset` (REL32), two real `GetGlyphOutlineA` calls (DIR32 IAT),
native free (REL32), and native operator new (REL32). The canonical
new unit `font-surface-load-glyph-outline-0041c1b0` was recompiled
**cold alone**, with `1/1 exact; 301 coverage bytes`. Separate
F317 398-byte FontSurface text-to-texture controller was accepted
independently; it does not cause extra CODE credit for this function
or the then-**nonexact** 1,766-byte FontSurface::RasterizeText,
subsequently independently F319-cold-accepted.
Original full private class types, Win32/CRT/VC7 callee bodies and all
97 origin-pending candidates remain uncredited. No machine byte
graft, manual x86, fake stack locals/pads, cropped original CODE,
masked relocation fields, all-unit replay or remote Oracle receipt.


## F319: cold-exact entire 1,766-byte FontSurface::RasterizeText major boss

The original R052-authored full `FontSurface::RasterizeText` occupies
**1,766 complete Japanese PE-backed CODE bytes** at
`0041C2E0..0041C9C5` with native `RET 0x24` at `0041C9C3` and
**551 independently decoded original x86 instructions**. Original
whole PE body SHA256 is
`2eb1e53bbddcc11a3e9aa0c3f1a9cab200fe7d09d154448fb7cc0dc18980a6d7`.
Its full native Ghidra/disassembly and negative structural probes
remain at `.analysis/f297-font-boss/`, `.analysis/f299-font-raster/`,
`.analysis/f302-font-lifetimes/`, `.analysis/f305-font-reconcile/`,
`.analysis/f307-font-native-slots/`; the final direct native slot
reconstruction, original complete object/COFF and local cold proof
are at `.analysis/f319-font-state/`. The adopted clean natural source
is `src/FontRasterizeTextF319.cpp`.

The entire original 551-instruction flow is independently grounded
in native evidence, including actual `memset` and `strlen`, two text
packing formats (32-bit ARGB and 16-bit output), true signed
Japanese two-byte decoder logic, in-band ASCII backslash controls
`\c` for real RGB hex override, `\e` for color reset, `\n` for
line progression, wrap/spacing/counters/last-line termination and
two independent actual glyph pixel scan loops. The 32-bit path
composes native alpha and red/green/blue per-scanline gradient
through real signed arithmetic and fixed packing shifts; the 16-bit
path builds the original 0x8000/0x421 per-alpha word. It calls the
original game font preparation at `0041C0D0`, native 8-bit packed
decoder `0041C9D0` **three times**, nibble decoder `0041CA80`
**six times**, the separately F318-accepted entire glyph outline
loader `0041C1B0` **twice**, then the independently F293-cold-exact
119-byte raster-resource release `0041C130` once. **All 15** genuine
original COFF REL32 fields, not only their abstract targets, are
compared with the complete native body. The already independently
F317-accepted 398-byte font texture controller calls this function;
no CODE credit for any of these callees or callers is transferred.

### Root cause: original 48-byte font parser/pixel state lifetime

The first complete natural VC7.1 `/Od` C++ source had already
reproduced all **1,766 bytes and 551 instruction forms**, but got
only **1,626/1,706** nonfield bytes because the compiler allocated
otherwise genuine text/parser/pixel/RGB locals to different stack
positions. Ordinary declaration/lexical scope and separate partial
value groupings improved only to 1,647/1,706. Rechecking the
**original complete 0x38-byte stack frame** instead of trusting
Ghidra local variable suggestions revealed a **48-byte physically
used native state group** immediately above actual `this` at
EBP−0x34, plus the native compiler-generated code-switch temporary
at EBP−0x38. Native source value slots, in their exact observed
order, are:

| Physical original slot | Actually accessed native value |
| --- | --- |
| EBP−0x30, −0x2C | Separate actual 16-bit and 32-bit output pointer values |
| EBP−0x28 | Inner glyph pixel-row index |
| EBP−0x24 | One shared decoded text-unit byte length (including the control escape's second decode) |
| EBP−0x20 | Source text offset |
| EBP−0x1C | Remaining source length |
| EBP−0x18..−0x15 | Already allocated 4-byte color storage; **red byte at −0x16** (lane 2) and **blue byte at −0x15** (lane 3) |
| EBP−0x14 | Actual decoded codepoint/source switch value |
| EBP−0x10 | Outer glyph pixel-column index |
| EBP−0xC, −0x8 | Pixel output x/y |
| EBP−0x4..−0x1 | Real low 4-byte color storage, **green at −0x1** (lane 3) |

No extra byte/word is allocated beyond these original native
physical ranges. The original assembler never reads or initializes
the unused lanes of the two real dword color-storage regions; our
C++ likewise accesses only the actual observed byte lanes, through
typed character pointers into `DWORD redBlueStorage` and
`DWORD greenStorage`. The natural `NativeTextStateF319` has exactly
**48 bytes** and is checked at compile time with `sizeof == 48`:
`output16`, `output32`, `iy`, `unitSize`, `offset`, `length`,
`redBlueStorage`, `code`, `ix`, `x`, `y`, `greenStorage`. The same
`unitSize` variable handles both actual native text-decoder calls
rather than allocating an unused second variable. A first physically
grounded 48-byte structure with separate `red/green/blue` and
`extra` locals matched **1,692/1,706**. Replacing only those
actual native color-slot types and reusing the real decoded-unit
count removed the remaining **12 genuine byte-lane access differences
and two genuine `DecodeUnit` result-slot differences**, without
adding any instruction, fake local, unobserved field usage or inert
source padding.

The final whole-source pinned VC7.1
`/Od /Ob0 /Gy /GR- /GX- /GS /Zi` compilation reproduces
**ALL 1,766/1,766 complete original CODE bytes**, all
**1,706/1,706** nonrelocation positions and **15/15 authentic COFF
relocation offsets/types/solved native destinations**. Only the
new canonical unit `font-surface-rasterize-text-0041c2e0` was
rebuilt cold and reported **`exact; 1766 coverage bytes` / 1/1
exact**, never any all-unit cold replay. This now closes the
separately accepted F317 398-byte texture controller, F318
301-byte glyph loader, and F293 character decoder/resource release
chain without double counting source CODE. The rest of the game
remains very far from the 98% objective; 97 pending origin cases,
private game class layouts, and original GDI/CRT/VC7 helper bodies
are still uncredited. No target-byte graft, asm, masks, truncated
native extent, artificial fields or external Oracle confirmation.


## F320: exact native 83-byte TextRasterizer::SelectFont GDI leaf

The original R103-authored TextRasterizer font selection helper at
`0041C0D0..0041C122` comprises **all 83 original native CODE bytes**
and **31 complete original x86 instructions**, full pinned Japanese
PE SHA256 `e24b2a690079d62be41af03135640adb47899f3ecaa2cfeef65c4a956ddad65a`.
Actual native GDI call and game-owned pointer evidence is in
`.analysis/f320-font-leaves/`: Windows HWND at this+0, HDC at +4,
selected HGDIOBJ at +8, old selected HGDIOBJ at +0xC, and real
font ascent LONG at +0x2C. A natural, complete `TEXTMETRICA`
stack instance is passed through native imported `GetTextMetricsA`,
whose `tmAscent` field is copied to the observed font metric field.
The original call order is authentic `GetDC` IAT `00657218`,
`SelectObject` IAT `00657048`, `GetTextMetricsA` IAT `00657040`.

The first grounded C++ `src/FontSelectF320.cpp`, compiled with
pinned VC7.1 `/Od /Ob0 /Gy /GR- /GX- /GS /Zi`, produces
**83/83 original CODE bytes, 71/71 nonrelocation positions and
3/3 genuine native physical COFF DIR32 offsets/types/solved GDI
import destinations**, without padding, asm or machine-code graft.
Only new canonical unit `text-rasterizer-select-font-0041c0d0`
was cold rebuilt alone, returning `exact; 83 coverage bytes` and
**1/1 exact**. This is independently counted as a new function
rather than attributing already F319 accepted 1,766-byte rasterization
caller CODE or earlier GDI/FontSurface routines to it. All imported
Win32/CRT/VC7 implementation CODE, 97 origin-pending functions and
unproven original private font layout are excluded. No all-unit
replay or external Oracle verification is claimed.


## F324: three independent full 280-byte game glyph-atlas draw functions cold-exact

Three separate authored game functions occupy independent native
PE address intervals, despite having the same verified atlas-draw
logic. They are *separately compiled, COFF compared and cold-replayed*,
not counted as a single file duplicated across one original address:

| Original native glyph renderer | Review | Full CODE | Original x86 instructions | Nonfield bytes | Physical COFF fields | Full original PE CODE SHA256 |
| --- | --- | ---: | ---: | ---: | ---: | --- |
| `SceneText::DrawNameGlyphsAt0042AFF0` | R102 authored | 280 | 81 | 256/256 | 6 | `582cae75647df937c4e306dda7493cf48bd5303d510141016b824d97e313e313` |
| `SceneText::DrawNameGlyphsAt0042C150` | R102 authored | 280 | 81 | 256/256 | 6 | `e131b61d5b6b6d93de2e86e0c41281b447e9a3af1265a48634f654de22643a25` |
| `ResultScene::DrawNameGlyphs` at `00431770` | R043 authored | 280 | 81 | 256/256 | 6 | `f15d10c289d027c00a5516530b66741d2e4c7d09862f9ed5974de5dcc5849f81` |

All three native functions set up one real 132-byte object by
calling original quad constructor `0040DA00` on the original two
float coordinates and upper right from native glyph width/height
constants `00657F78`, `0065786C`. A real 8-iteration loop treats
each glyph index as **signed char**, performs original signed
remainder/division by 26, constructs actual atlas rectangles with
19-pixel glyph width/20-pixel height via imported Win32 `SetRect`
`00657210`, invokes the original 132-byte quad renderer `0040C9A0`
at receiver this+8 using texture index 2 and original caller tint,
then invokes original `SpriteTransform::TranslateQuad` `00411500`
with x step 14.0f before the next glyph. Each function has six
authentic COFF fields: two global float constants, quad constructor,
GDI SetRect IAT, game DrawQuad and game TranslateQuad calls.
The original stack frame is exactly `0xA0` with saved this at
EBP−0xA0, real signed index at EBP−0x9C, actual `RECT` at EBP−0x98
and full borrowed 132-byte SpriteQuad at EBP−0x88.

The first natural complete C++ source emitted only **256 bytes**
because its separately declared loop index was assigned EBP−4,
producing 8 shorter 3-byte index references. The real `RECT` was
therefore also displaced. A **single 20-byte plain used-data struct
`GlyphIndexRectF324`** containing only the actually read/written
index and Win32 RECT, rather than a fabricated pad/unused field,
lets pinned VC7.1 `/Od /Ob0 /Gy /GR- /GX- /GS /Zi` naturally
place both at the original native EBP locations. The entire natural
quad constructor and gameplay rendering statement order is preserved.
Thus **each** of three independent original target functions emits
all **280/280 CODE bytes**, every **256/256** comparable position
and every **6/6** genuine COFF offset/type/native solved destination.
Accepted sources are `src/SceneEntryGlyphsF324.cpp`,
`src/ReplayBrowserGlyphsF324.cpp`, `src/ResultSceneGlyphsF324.cpp`;
private read-only Ghidra originals, 256-byte negative source, full
C++/COFF positives and new-unit-only cold receipts are at
`.analysis/f324-name-glyphs/`. Only the three affected units
`scene-entry-name-glyphs-0042aff0`,
`replay-browser-name-glyphs-0042c150` and
`result-scene-name-glyphs-00431770` were cold rebuilt
**3/3 exact**. All six-field targets were independently audited
against their own original PE bytes, not inferred from a common
helper. 840 independently authored CODE bytes are newly covered;
original quad constructor/renderer/transform and GDI imported code,
full private UI scene layouts and all 97 unresolved origin candidates
remain uncredited. No assembly, target-byte copying, unused fake
stack fields, masked relocations, partial native extent, all-unit
cold replay or external Oracle receipt.

### Adjacent F323 complete replay filename renderer remains nonexact

`ReplayScene::DrawSaveFilename` at `0042C270` has a **303-byte**
original GDI/UI function that first constructs the same real quad,
compares a 13-byte replay path prefix, then renders one of two
8-byte glyph sequences. Native source locals include a 14-byte
`replay/replay` prefix, real 132-byte quad, and actual 8 glyph bytes
in a different natural VC7.1 `/GS` vulnerable-array layout. A full
semantic source and twelve independent genuinely changed C++
const-vs-mutable and declaration-order controls compiled 341–342
bytes, not the original 303, due 8-bit/32-bit EBP displacement
differences. Retain all negatives and PE disassembly under
`.analysis/f323-replay-filename/`; no premature CODE acceptance
or artificial padding.


## F325: whole 183-byte SpriteSequence::AppendElement cold-exact

`SpriteSequence::AppendElement` at `00411000..004110B6` is one
R035-authored, completely bounded original native function of
**183 CODE bytes**, **48 actual x86 instructions**, actual
`RET 0xA4` (the real by-value 164-byte caller parameter packet)
and full original PE SHA256
`4cb93c31e32196534a5f739b4ee7ed1de39dacf9f0a495301db63e9f08cb51de`.
Original full Ghidra/control disassembly and the two whole C++
source/COFF comparisons and only-one-unit cold proof are preserved
at `.analysis/f325-sprite-append/`. Source
`src/SpriteSequenceAppendF325.cpp` models only a genuinely observed
**164-byte SpriteHistoryElementF325** with original native fields,
not the opaque library's entire private element/allocator layout.

The original element constructor at `00411C10` initializes the
physical 164-byte stack object at EBP−0xA8. The source then copies
actual short texture, the complete **132-byte SpriteQuad** by
33-dword `REP MOVSD` from the by-value caller packet, three actual
D3DVECTOR coordinate words, signed byte blend mode, x/y game
positions and DWORD tint in the precise original native order.
It passes a pointer to the real element to the native history list
`Append` call `00411D30` at this+4, fetches native `Size` from
`00411CE0`, compares with true signed short max history capacity
at this+0x12, and conditionally invokes real `RemoveFront`
`00411D00`. Every call is a physical COFF REL32 field; **all
four genuine target relocations match**. The original whole native
0xAC stack frame holds this at EBP−0xAC and the complete genuine
164-byte temporary immediately above, with no additional compiler
locals.

A first complete semantic C++ unnecessarily cached the actual
this+4 history-list receiver into its own local pointer. It generated
177 bytes with an erroneous 0xB4 frame and lost the original member
receiver reevaluation. Removing that *unobserved pointer cache*
while directly taking the same true this+4 member on each real
call produces **183/183 CODE bytes, 167/167 comparable positions,
and 4/4 native physical COFF fields** naturally with pinned VC7.1
`/Od /Ob0 /Gy /GR- /GX- /GS /Zi`. Only canonical
`sprite-sequence-append-element-00411000` was cold rebuilt,
`1/1 exact`, never an all-unit replay. The FighterRender caller,
actual original list constructor/Append/Size/RemoveFront functions,
SpriteQuad constructor, CRT/VC7 and 97 origin-unknown cases do not
receive duplicate authored CODE.

The adjacent major boss `SpriteSequence::RenderElements` at
`00411110` (746 original CODE, 198 x86 instructions, real 0xBC
frame) is **still nonexact**. Additional independently compiled
meaningful stack aggregate/quad alignment hypotheses in
`.analysis/f316-sequence-scope/` and
`.analysis/f321-sequence-aligned/` emitted 711/733/745/754 bytes
or changed native iterator ABI. None is credited as complete. No
artificial stack alignment filler, machine-byte patch, manual x86,
truncated function, masked original relocations, or remote Oracle
acceptance is claimed.


## F326: exact full 1,252-byte ReplayRecords::AppendRecord writing boss

`ReplayRecords::AppendRecord` is independently confirmed as one
complete original R035-authored `00413DE0..004142C3` PE CODE
function of **1,252 bytes**, **379 decoded original x86 instructions**
and real plain `RET` under a native `0x9C` unoptimized stack frame.
Pinned Japanese PE full code SHA256 is
`f39de667fe840de794dcfc5fc2862e6cdefad400df8654206cad736561dc361c`.
Its native original disassembly/Ghidra and older negative hypotheses
are retained in `.analysis/f218-replay-file/`,
`.analysis/f219-append-record/`, `.analysis/f225-big-functions/`,
`.analysis/f232-append-scope/`, `.analysis/f272-append-investigation/`,
`.analysis/f296-append-interleave/` and `.analysis/f312-append-scopes/`;
the final real-layout C++ source/positive COFF/full cold acceptance
are `src/ReplayAppendRecordF326.cpp` and
`.analysis/f326-append-physical/`.

This game-specific controller verifies the true file handle, saves
its current native position at a per-record file-offset DWORD
`this+0x11C+4*(signed char(this+0x116))`, and writes the original
ten header fields with exact one/two/four-byte widths via imported
`WriteFile` and real `SetFilePointer` IAT targets. It traverses
four native queue receivers of actual 20-byte stride at this+
`0x154`, `0x168`, `0x17C`, `0x190` and writes their true 32-bit
count and each element's native width (byte, short, byte, DWORD),
using actual six 8-byte iterator objects, real Begin/End/Size,
`operator!=`, dereference and postfix increment calls, and
original cleanup `ClearQueues` and record index advance. All
Win32/game C++ call behavior and original 50 physical COFF fields
are retained without borrowed implementation credit, invented file
operations or altering native error handling.

The real complete original stack has a **56-byte contiguous state
region** occupied by exactly **six actually used 8-byte iterator
instances plus DWORD `written` and count**. Their original native
physical address order, independently observed from constructor
receivers *and all later uses*, is:

| Native EBP location | Actually used original field |
| --- | --- |
| −0x38 .. −0x31 | byte iterator begin (8 bytes) |
| −0x30 | `written` DWORD output count |
| −0x2C .. −0x25 | byte iterator end (8 bytes) |
| −0x24 .. −0x1D | word iterator end (8 bytes) |
| −0x1C .. −0x15 | word iterator begin (8 bytes) |
| −0x14 | record `count` DWORD |
| −0x10 .. −0x09 | DWORD iterator end (8 bytes) |
| −0x08 .. −0x01 | DWORD iterator head (8 bytes) |

Importantly, actual constructor calls happen **in a different order
from physical member order**: byteBegin at −0x38, byteEnd at −0x2C,
wordBegin at −0x1C, wordEnd at −0x24, DWORD head at −0x08, DWORD end
at −0x10. The original C++ type and allocator member names cannot
be inferred solely from codegen. We therefore model the *actual*
complete used state as one ordinary, layout-checked
`NativeAppendFrameF326` struct, and use direct borrowed native
iterator-constructor **ABI entry calls** at `00414930` (byte),
`004149E0` (word), `00414A90` (DWORD), in the actual native order.
In the source these direct C++ thiscall entrypoints are named
`.Initialize()` solely as a caller-side ABI alias for the real
constructor entry (not evidence that the original had separately
named Initialize methods). The contents remain the same real eight
used values, no hidden pad, no synthesized extra code or pretense of
reconstructing the constructor *bodies*.

The longstanding complete 1,252-byte natural source compiled 50
correct COFF relocation fields but only **1,033/1,052** original
nonrelocation bytes (19 real mismatched EBP slots). Many genuine
lexical declaration, nested iterator scope, typed pair and source
variable interleaving variants failed. The F326 physical used-state
layout with direct genuine constructor ABI entry calls recovers
**1,044/1,052**; ordering the DWORD data members correctly while
checking all six construction targets yields **1,050/1,052**. The
final two bytes are the fifth and sixth **real DWORD constructor
call receiver positions**: the native initializes the *head at
EBP−0x08* then *end at EBP−0x10*, not vice versa. Calling these
actual ctor entries in that exact observed order yields **the entire
1,252/1,252 original CODE bytes**, **1,052/1,052 comparable bytes**
and all **50/50 genuine COFF relocation offsets/types/solved native
destinations** under pinned VC7.1 `/Od /Ob0 /Gy /GR- /GX- /GS /Zi`.

Only canonical `replay-records-append-record-00413de0` was cold built
independently (`1/1 exact; 1252 coverage bytes`) and its whole source
SHA tracked in the adoption manifest. All earlier source probes
remain available as **negative evidence**, not accepted code, and
no full all-unit replay, byte graft, manual assembly, fake stack
padding, masked relocation or truncated function was used. Existing
ReplayRecords read functions, Win32/CRT implementation, and all 97
origin-pending functions are not double counted. Local exact
checkpoint is **not** a remote Oracle acceptance receipt.


## F328: complete original 375-byte ReplayRecords file finalizer cold-exact

`ReplayRecords::FinalizeFile` at `004138E0..00413A56` is a complete
R035-authored original Japanese PE function of **375 CODE bytes**,
**105 independent native x86 instructions**, original `/GS` stack
security cookie/prologue/epilogue and `0x12C` native frame. Full
original native CODE SHA256 is
`8deb7f0df2e205313ed2f0ded219a968465133d19c8c5b4aeb4dc67d7809f3b1`.
The previously F218-attempted complete semantic source/negative tests
remain under `.analysis/f218-replay-file/`, with new 280-byte/12-byte
physical grouped C++ negative controls, exact whole COFF and
**one-unit-only cold replay** under `.analysis/f328-replay-final/`.
Accepted real C++ source `src/ReplayFinalizeFileF328.cpp`.

Its native behavior constructs the output replay filename via original
`00414300` into a 264-byte path buffer, calls imported CreateFileA
(GENERIC_WRITE/CREATE_ALWAYS) and writes the original 0x3C-byte
record header at owner+0x108 with actual WriteFile. It closes its
prior input handle, reopens original data path `replay\replay.tmp`
from game global `00657904` as GENERIC_READ/OPEN_EXISTING, gets
its actual GetFileSize, allocates the requested byte count through
original `006416A2`, and loops over all original unsigned byte indexes,
calling native ReadFile(input,byteBuffer,1) then
WriteFile(output,byteBuffer,1) with the correct original `written`
DWORD and Win32 IATs. Afterwards it frees the real allocated pointer
through original native `0064169D`, closes and clears the input
handle, closes the output and checks original `/GS` cookie via
native `00640611`. No source-invented error branch, file close or
allocator fallback is added. All 15 actual COFF relocation fields
(including real cookie, game path builder, Win32 IATs, allocation and
free, and security check) are compared in their physical original
positions and solved native destinations.

The old whole natural C++ source compiled 384 bytes rather than 375
with an incorrect 0x134 frame and wrongly allocated original locals.
The original source storage contains **exactly these used values**:

| Native EBP stack location | Real meaningful original field |
| --- | --- |
| −0x128 | pointer passed to native free |
| −0x124 | actual allocated pointer returned by native new |
| −0x120 | actual byte copy pointer used by ReadFile and WriteFile |
| −0x11C | actual `written` DWORD passed to all original file I/O |
| −0x118..−0x11 | actual 264-byte output archive path |
| −0x10 | native `/GS` cookie (compiler-managed, not modeled as a source field) |
| −0xC | real output file HANDLE |
| −0x8 | real input file byte count from GetFileSize |
| −0x4 | real unsigned per-byte loop index |

A **280-byte `NativeFinalizeWorkF328`** plain C++ struct groups
only the three genuinely used pointer aliases, byte count and path.
With the actual native `/GS` cookie, the pinned VC7.1 compiler
then naturally generated the complete **375-byte CODE extent,
308/315 nonrelocation byte matches and all 15 actual COFF targets**.
The last seven nonfield mismatches were entirely different EBP
positions for the *three other real values*. Ordinary independent
variables assigned the output HANDLE EBP−0x8 and file size EBP−0xC,
opposite native. A **12-byte `ActualFileStateF328`** grouping only
real output HANDLE, file size DWORD and unsigned index in precisely
that original physical order restores native EBP−0xC/−0x8/−0x4
without any additional code/data/padding. The resulting source
compiles exactly **375/375 original CODE bytes, 315/315 original
comparable byte positions and 15/15 physical COFF relocations**
under pinned VC7.1 `/Od /Ob0 /Gy /GR- /GX- /GS /Zi`. Only the
affected unit `replay-records-finalize-file-004138e0` was cold rebuilt,
reporting **1/1 exact**.

This is independent authored CODE from F326's complete 1,252-byte
`AppendRecord`, F259's separately accepted `LoadRecord`, and the
other replay-file methods; there is **no duplicate CODE credit** for
any originally accepted game callee, imported Win32/CRT/VC7 code or
the 97 origin-unknown candidates. Borrowed owner/allocator interface
identities remain provisional; the complete original class layout
is not inferred solely from the machine-code match. No manual x86,
masked relocations, fake source locals/padding, byte graft, cropped
original function, all-unit cold replay or remote Oracle acceptance.


## F334: complete native 273-byte EventQueue worker cold-exact

`EventQueue::RunWorkerAt00423B40` is one complete R112-authored
Win32/game queue-worker function at `00423B40..00423C50`,
**273 original CODE bytes** and **84 independent original x86
instructions**, with a genuine `0x44` native stack frame and
`RET 4` on the unreachable original exit. Full pinned PE body
SHA256 `c953583969d6b7574aa88650dadce4e7ca69ea30dce1b809482df02d741e1ca9`.
Original Win32/game Ghidra decomp and full native physical x86
assembly at `.analysis/f329-rank-glyphs/` and
`.analysis/f333-event-worker/`, final natural C++ under
`src/EventQueueRunWorkerF334.cpp`, original full 19-field COFF
comparison and **single-affected-unit cold 1/1 exact** receipt
under `.analysis/f334-worker-physical/`.

The real worker waits through original imported WaitForSingleObject
`00657120` using the genuine queue-ready event HANDLE global
`0068BE34` and timeout global `0066C23C`. The original game event
queue at `0068BE44` supplies native Begin (`00423CE0`) and End
(`00423D10`) checked vector iterators; the real compare method
`00423FD0` controls a complete inner loop. The current element
dereference `00423F70` yields an actual pointer to an event-entry
record. If its first int is zero, original `Erase` `00423EF0`
returns a new iterator, assigned to the current iterator, then
End is refreshed. Otherwise the original current-event method
`00423DF0` returns the event HANDLE through two actual pointer
indirections. The worker invokes imported SetEvent `0065705C`, then
uses real iterator postfix increment `00423F90` with the actual
8-byte returned old iterator. The outer worker is an original
infinite loop, including the native compiler-generated `mov eax,1`
test and unreachable return; no invented stop or error handling.

Original local stack **28 bytes of live checked iterator state**
contain three *actually written* tracking DWORDs and two actual
8-byte vector-iterator core values. The tracking dwords have
original initializations at EBP−0xC, −0x18 and −0x1C, all zeroed
**in that order before native iterator constructor calls**.
The first iterator core occupies EBP−0x8..−0x1 and second at
−0x14..−0xD. The original five 8-byte iterator-return temporaries
occupy EBP−0x24, −0x2C, −0x34, −0x3C, −0x44. A first natural
253-byte C++ worker had saved a non-existent this receiver and
omitted those three genuine tracking stores. A normal used-data
`LiveWorkerIteratorsF334` struct of exactly 28 bytes plus a borrowed
*direct original constructor ABI* alias `.Initialize()` at
`00423F50`, and a static stdcall with original `RET 4` (private
function identity still provisional), reproduces the exact
original 273-byte native opcode layout. Its `if` branches and
SetEvent dereference are source-faithful rather than forced with
manual instructions.

Pinned VC7.1 `/Od /Ob0 /Gy /GR- /GX- /GS /Zi` compiles
**273/273 original machine CODE bytes, 197/197 comparable original
nonfield bytes and all 19/19 physical COFF relocations**. Only
`event-queue-run-worker-00423b40` was cold replayed, reporting
`exact; 273 coverage bytes` / **1/1 exact**. This does not prove
the original private queue class source definitions, borrowed
constructor method names, or native code inside event/iterator
callees. Win32, CRT/VC7 and 97 origin-pending functions remain
excluded. No code byte patch, asm, fake padding, all-unit replay
or external Oracle acceptance.

### F331/F332: entire 746-byte SpriteSequence boss close but nonexact

New tests used only the independently observed original stack
region of the complete `SpriteSequence::RenderElements`
`00411110`, including true counter, RECT, iterator end, x float,
tint DWORD and 132-byte quad. Modeling the real quad carrier as
33 copied DWORDs (the native `REP MOVSD` form), rather than a
spurious `unsigned char[132]` buffer that wrongly triggers `/GS`,
with a borrowed direct original quad-constructor entry call
restores the full **746 original CODE-byte length and 198 native
instruction shapes**. All **33 original COFF fields** match.
A fully occupied real state layout is at **599/614 comparable
bytes**, only 15 remaining nonfield bytes mismatch: in each of
three source glyph scale float comparisons, original x87 loads
the constant `0065782C` first and record float (+0x90,+0x94,+0x98)
second, whereas VC7.1 emits the reverse two native `FLD` operand
loads for the current C++ expression. Simple C++ operand swap,
const/volatile/ref/equal/inequal/bool variants have failed without
changing any gameplay. Do not hide three five-byte mismatches,
use manual asm or accept partial whole boss as exact. Private
evidence `.analysis/f331-sprite-nativeframe/`,
`.analysis/f332-sequence-x87/` retained, zero new CODE credit.


## F335: independently exact EventQueue service acquire/release lifetime

Two complete R114-authored Win32/game event-queue service methods
operate on distinct fully backed original Japanese PE CODE ranges:

| Native method | Full CODE | Original x86 instructions | Nonfield exact | Actual COFF fields | Complete original PE SHA256 |
| --- | ---: | ---: | ---: | ---: | --- |
| `EventQueue::AcquireSharedServiceAt004239F0` | 155 | 41 | 83/83 | 18 | `d3cbe2979e99f5ee856459ce2dc812928f7a83c2297aaeefb2a40c757baf8700` |
| `EventQueue::ReleaseSharedServiceAt00423A90` | 143 | 41 | 79/79 | 16 | `1bc97f316393be5b671899f9e570faac27eef7078e6486a813f11f7210d50331` |

Acquire performs the native refcount check at `0068BE30` and stores
the caller-provided delay at `0066C23C`, resetting that global
only if negative. It invokes imported `timeBeginPeriod(1)` at
`00657268`, original queue Reset `00423F30` on true global queue
`0068BE44`, creates actual worker event via imported CreateEventA
`00657054` and stores `0068BE34`, calls imported CreateThread
`0065713C` with the independently F334-reconstructed original
worker entry `00423B40`, actual thread ID address `0068BE3C`,
and stores worker HANDLE `0068BE38`. It uses imported
SetThreadPriority `00657140` with native priority 15, sets the
running byte at `0068BE40` and increments true user refcount.
Native `thiscall` returns its real receiver as original C++ code.

Release decrements that same original refcount, checks for zero,
clears running flag, calls native TerminateThread `00657134`,
iterates exactly the actual queue count from `00423D40` through
original per-item indexing `00423DB0`, signals every actual event
HANDLE through imported SetEvent `0065705C`, then calls the same
queue Reset and closes ready/worker HANDLEs through authentic
CloseHandle IAT `00657138` twice. No implied waiting for thread
shutdown or safety check absent from the target is added.

A first complete natural C++ source models these actual original
Win32/global service side effects, not the unknown queue class
implementation. It was split into **two independent C++ source
files and two actual COFF objects** `src/EventServiceAcquireF335.cpp`
and `src/EventServiceReleaseF335.cpp` before acceptance. Pinned VC7.1
`/Od /Ob0 /Gy /GR- /GX- /GS /Zi` reproduces every physical original
CODE byte, all comparable bytes and **all 34 independently checked
COFF relocation positions, types and native solved destinations**.
Cold replay was restricted to the **two newly affected units**
`event-service-acquire-shared-004239f0` and
`event-service-release-shared-00423a90`, both **2/2 exact**.
Original Ghidra/decompiler, separate positive full source/COFF and
local cold receipts are retained at `.analysis/f335-event-service/`.
The native worker (separate F334 complete 273 CODE), external
Win32/CRT/VC7 call targets, opaque original EventService class and
97 unknown origins receive no duplicated CODE credit. No target
byte graft, assembly, artificial padding, truncated extent, masked
original COFF fields, full all-unit replay or remote Oracle proof.


## F337: entire 162-byte two-side BattlePointerQueues release cold-exact

R166-authored `BattlePointerQueues::ReleaseEntriesAt005F7140` at
`005F7140..005F71E1` has **all 162 original pinned Japanese PE CODE
bytes**, 54 complete original x86 instructions, native `0x10` stack
frame and PE body SHA256
`a6e281ee48d96a55d56a6e3f26545b454a48091274d2032a49e1e63e090ff232`.
Original native Ghidra/decompiler, complete first natural C++/COFF
probe, meaningful native-state grouped C++ exact and one-unit cold
receipt are retained at `.analysis/f337-archive-close/`; canonical
accepted source `src/BattlePointerReleaseF337.cpp`.

Original gameplay cleanup traverses two genuine 20-byte physical
queue members at owner+0 and owner+0x14. For each, it loops over
the actual unsigned 32-bit item index until native Size `005F8110`,
fetches a real owned pointer with original At `005F8130`, frees it
via native C runtime `00640F15`, and invokes original Clear
`005F82D0`. It uses the same unsigned index in both loops and
**two distinct actually used** freed-pointer locals, preserving
both original full iteration/cleanup orders. The genuine `0x10`
frame holds this at EBP−0x10, second freed pointer at −0xC,
first freed pointer at −0x8 and unsigned index at −0x4.

First complete source under pinned VC7.1 `/Od /Ob0 /Gy /GR-
/GX- /GS /Zi` emitted **162 native CODE bytes** and all eight
real COFF fields but placed first freed pointer and index in wrong
EBP slots, causing 12/130 nonfield mismatches. The native pointer
locations were independently confirmed. A plain, actual **12-byte
`PointerQueueStateF337`** containing only these three genuinely
used values in the original physical member order `second`,
`first`, `i` lets MSVC emit exactly **162/162 original CODE,
130/130 comparable byte positions and 8/8 original physical COFF
REL32 fields** (two each to native Size, At, free, Clear).
Only newly affected canonical
`battle-pointer-queues-release-entries-005f7140` was cold compiled
and accepted **1/1 exact**. Separate F304 original resource
release owner calls this helper but never duplicates these 162
CODE bytes. Win32/CRT/VC7 and other game containers' source
implementations, full private class layouts, and all 97 pending
origins remain uncredited. No byte graft, manual x86, artificial
stack padding, masked relocation, cropped native extent, full
replay or remote Oracle receipt.


## F338: full 429-byte DataArchive::OpenAndReadIndex boss cold-exact

The R052-authored original native archive-index file loading
function `DataArchive::OpenAndReadIndex` at `0041D510..0041D6BC`
contains **429 complete pinned PE CODE bytes**, **130 independently
decoded x86 instructions**, native `0x9C` frame and real `/GS`
stack cookie. Entire original pinned Japanese PE body SHA256:
`caf7adaed6de06f3fbeb7d4e0335476498c7507342ad40f0411ad438c1cb4a49`.
Read-only Ghidra/native and all old complete 429-byte natural C++
failed scopes/typed decode controls are preserved at
`.analysis/f248-archive-write/`; new actual 28-byte source-state
controls and final exact C++/COFF/cold proof at
`.analysis/f338-archive-physical/`. Canonical adopted full source
`src/ArchiveOpenReadIndexF338.cpp`.

The actual native archive loader checks and closes any old archive
HANDLE at this+0, calls original imported CreateFileA with true
GENERIC_READ/OPEN_EXISTING, checks INVALID_HANDLE_VALUE, reads one
original 16-bit little-endian entry count, allocates `count*108`
raw wire-table bytes with original native new[] at `006416A2`,
and reads that complete encrypted table using real Win32 ReadFile.
Two actually used unsigned 8-bit codepoint decoder values begin at
100: each wire byte is XORed with `key`; then `key += step` and
`step += 77`, wrapping naturally at 8 bits. The same genuine
unsigned index is reset and reused in the following record loop.
Each true 108-byte archive record contains exactly 100 filename
bytes and two DWORD fields at offsets 100/104. The loader copies
those two ints and original source filename via real native
`strcpy` at `00641B80` into an actual 108-byte temporary entry,
then calls the original game `ArchiveIndexList::AddEntry`
`0041D9C0` on receiver this+4. It deletes the native raw buffer
and completes actual VC7.1 `/GS` security cookie check `00640611`.
No invented error branch or added file close changes native flow.

Older 429-byte natural source experiments under F248/F250 had all
**10 original genuine COFF relocations** but a best of only
**366/389** comparable bytes, due to compiler physical local
allocation. The full original stack frame supports exactly these
**28 bytes of genuine parser state**:

| Native EBP locations | Actually used original state |
| --- | --- |
| −0x1C..−0x19 | real key-byte storage, only final byte −0x19 accessed |
| −0x18 | decoded base pointer |
| −0x14 | unsigned short entry count (native aligned slot) |
| −0x10..−0xD | real step-byte storage, only final byte −0xD accessed |
| −0xC | genuine shared unsigned index DWORD |
| −0x8 | genuine ReadFile transferred bytes DWORD |
| −0x4 | actual raw allocation pointer |

A plain typed `ArchiveReadStateF338` groups *only this actually used
native data*; two DWORD-sized carriers model preexisting physical
stack storage, whose final bytes are the only observed key and
step, without constructing dummy locals, allocating extra bytes
or accessing unrelated regions. The original private source authors'
preferred field/byte types are not inferred. The complete natural
C++ source under pinned VC7.1 `/Od /Ob0 /Gy /GR- /GX- /GS /Zi`
now generates **429/429 original CODE, 389/389 nonfield bytes and
10/10 real physical COFF relocation offset/type/native solved
destinations**. Only `archive-open-and-read-index-0041d510` was
rebuilt cold **alone**, reporting `exact; 429 coverage bytes` and
`1/1 exact`. The larger **686-byte `DataArchive::Write`** is a separate whole
original native function: it was nonexact **at F338** (old best
495/574), but was later independently cold-accepted as **F339**.
Neither function inherits any CODE credit from the other.

External Win32/CRT/VC7 implementation bytes, private complete
archive owner/list implementation, other already accepted callees
and all 97 pending-origin candidates are excluded. No byte graft,
asm, artificial stack padding, missing/masked COFF, cropped native
function, full replay or remote Oracle acceptance.


## F339: exact original 686-byte DataArchive::Write full file writer

F339 fully cold-accepts the original R052-authored `DataArchive::Write`
at `0041D260..0041D50D` as **686 CODE bytes**, **228 native x86
instructions**, **574/574 comparable bytes** and **28/28 genuine
original COFF relocation offsets/types/native solved destinations**.
Original PE body SHA256:
`80e6e36f8489bdd62975eb418514e49b4724ae36daadbb4e90447279294cb4b1`.
The actual native routine creates an output archive file, builds a
16-bit-record-count header and exact 108-byte filename/size/offset
records through native 4-byte iterators, encrypts the table with the
original rolling byte XOR and writes both table and complete source
file payloads via original Win32/CRT calls, preserving all native
exit paths and pointer lifetimes. The source groups **only the 60
actually used bytes** of native iterator/file/decoder state in
`NativeArchiveWriteStateF339`; borrowed direct `BeginInto` and
`EndInto` names are caller-side hidden-sret ABI aliases for original
Begin/End entries, not proof of the native author's C++ names.

The older 686-byte F249 natural source was nonexact at 495/574
comparable bytes. F339 resolved its physical native EBP storage
and file-buffer aliases, producing a complete pinned VC7.1 natural
C++ object with **all 686 original CODE bytes**, 574/574 comparable
nonfield bytes and all 28 native original relocations. Only
`data-archive-write-0041d260` was cold replayed (**1/1 exact**).
Source `src/ArchiveWriteF339.cpp`; evidence and earlier negatives
`.analysis/f249-archive-writer/`, `.analysis/f339-archive-write-frame/`.
The separately F338-accepted 429-byte archive index reader is a
different CODE range; neither counts original imported Win32/CRT
or 97 origin-pending functions. Earlier claims that either of the
686/429 archive functions was **currently unaccepted** are obsolete.


## F340: complete 164-byte archive name seek, verified native iterator ABI

The previously unclassified R053-authored `DataArchive::SeekNamedEntry` at
`0041D750..0041D7F3` consists of **164 original CODE bytes** (PE SHA-256
`b0f65cb3e5a968f5875d430cbcaa38afc8a54e3861028d50d01a00cb187516c8`).
Unlike the independently exact 180-byte `SeekNamedEntryWithSize` at `0041D800`,
this one takes only a name and returns a borrowed archive HANDLE or -1. The
original body invokes real list Begin/End at `0041D950`/`0041D980`, iterator
`!=`, postfix increment, `Entry`, and `==` at their original verified addresses,
uses `strcmp`, and calls `SetFilePointer` with the record's genuine byte offset
+104. It has a single `RET 4` and no independently owned after-return code or
post-return table. The original private iterator, list, archive context and
class names are **not fully recovered**; this probe declares only the observed
four-byte borrowed iterator and caller interface.

`src/ArchiveSeekF340.cpp` reproduces the complete natural C++ routine with
VC7.1 `/Od /Ob0 /Gy /GR- /GX- /GS /Zi`. The original 164-byte extent and all
**nine** physically present COFF relocations independently agree, including
all target destinations; nonrelocated instruction bytes match **128/128**.
Canonical cold replay of only
`data-archive-seek-named-entry-0041d750` yields **1/1 exact**,
with no unrelated existing unit replayed. This is original CODE credit only,
not compiler-generated iterator, CRT or Win32 callee credit, and not a public
Factory Oracle acceptance.


## F341: native archive catalog dual deque erase/close, cdecl and full 264-byte function

The original R053-authored `0041D080..0041D187` body is a **264-byte**
function with 89 complete independently decoded native instructions, original
PE SHA256 `94e34263881bb6cf3867513ce1c6e64a0b79a775b944e52c7fbf2f4ec39b461d`.
The `RET` is plain `C3`, not a member-function `RET 4`; the name
`ArchiveCatalog::CloseNamed` remains provisional and is represented as a
namespace-scoped cdecl entry. The real native source creates both name and
object deque begin/end iterators. Its only loop condition compares the name
iterators. It compares each name through `strcmp` and either erases the
matching name and resource elements in lockstep (after genuine C++ `delete` of
the resource), or postfix increments both live cursors. The genuine original
scalar-deleting destructor `0041D8C0` is compiler-origin and remains excluded
from authored coverage; this function merely calls it.

A simple natural source showed the correct 264-byte whole body and all
19 relocations but differed at 16 EBP displacements. The original local stack
slots are **name begin -0x20**, **resource end -0x18**, **name end -0x10** and
**resource begin -0x08**. These form one meaningful 32-byte live cursor
record, not artificial padding. Modeling the natural record and using
borrowed `BeginInto`/`EndInto` caller-side hidden-sret equivalents to the
original 0041DCF0/0041DD20 and 0041DA90/0041DAC0 addresses recovered every
original stack displacement without inventing locals. The final source is
`src/ArchiveCatalogCloseF341.cpp`; VC7.1 exact unit
`archive-catalog-close-named-0041d080` matches all **188/188 nonrelocation
bytes**, all **19** physical original COFF relocation fields/destinations,
and the full exact **264-byte** native function in a single-unit cold replay.
External deque/CRT calls and compiler thunk bytes are not duplicated.
Original private class/record names and complete layouts remain open. No
assembly, masks, byte grafts, disassembly pasted as source, or full cold replay.


## F342: complete native 133-byte archive readable file insertion

The R179-authored `0041D6C0..0041D744` function has **133 bytes**, **44 native
x86 instructions**, original PE SHA256
`2972a34fbe5f525ed19797c45c09a0b4e7dddc185833d9f324fd3d370a45e2f6`.
It opens the requested name with the original Win32 `CreateFileA` packet,
returns early on `INVALID_HANDLE_VALUE`, then fills a genuine **108-byte**
archive wire record. This record has `filename[100]`, `fileSize` at byte
100, `fileOffset` at byte 104 initialized to zero. `GetFileSize` fills the
size, `strcpy` fills the filename, `CloseHandle` releases the probe handle,
and original `0041D9C0` `AddEntry` appends the copied wire record. The full
native `/GS` security cookie and `__security_check_cookie` remain in code.

`src/ArchiveAppendFileF342.cpp` models only the independently observed record
and borrowed list caller ABI, not a complete archive owner class. The first
complete natural VC7.1 `/Od /Ob0 /Gy /GR- /GX- /GS /Zi` probe reproduced
all **105/105** comparable bytes and all **7** genuine original physical
COFF fields/destinations. Independent cold replay of only
`data-archive-append-readable-file-0041d6c0` returned **1/1 exact**. This
supersedes the old 130-byte nonexact control in historical file policy
notes; no target bytes/assembly, fake locals or partial-function credit.


## F345: full 679-byte Yukari special-state boss, VC7.1 macro-sensitive x87 reconstruction

The R067-authored `YukariFighter::UpdateSpecialStateAt0059B490` at
`0059B490..0059B736` is a complete **679-byte**, **191-instruction** native
function (original PE SHA256
`0529bb313498e1b6d0af591a2c6e47bf03d739398b76b1114de8e950e3b71f34`).
The target's `thiscall` receiver stores ECX at EBP-4 and has 0x10 bytes of
original scratch space. Real signed-short state +F12 advances by 2 only if
+3B8 is zero, wraps to -180 when reaching 180, and +3AC clears when grounded.
A three-way conditional requires +62/+64/+F0A all zero before dispatching
three separate actions (+60 in 150..153, 154..157 or exactly 158) to the
**already accepted** `00453AC0` tracked effect with effect ID **830**, real
facing-dependent X, and Y+94/60/100. The action one-shot +F0A is set on each
trigger. Two distinct actor-relative X difference tests compare actual
+44 and opponent (+2E8)->+44 with +/-540 and +/-320, updating the signed
+F32 limit counter at 60. The three integer-to-float intermediates occupy
actual scratch offsets EBP-8/-0xC/-0x10. No original 16-byte owner or private
parent/derived fighter layout is newly claimed.

A first **complete** source probe `YukariSpecialF345.cpp` emitted 679 bytes
and all 11 physical fields, but only 581/635 non-field byte matches. The
comparison `>179` compiled a native `cmp 179; jle` while the verified target
requires `cmp 180; jl`, so the source uses `>= 180`. The remaining 52
byte differences concerned `FLD` ordering for the exact 0.0f equality and
four opponent-distance evaluations. Swapping operands, using direct global
constants and merely parenthesizing an equivalent nested `FIELD(float, ...)`
macro **did not help**. Inspecting the already independently exact F062
`CharacterAux5E5500.cpp`, whose tracked-effects/distance algebra is related,
revealed the *precise unparenthesized macro expressions* as a falsifiable
code-generation control:

```cpp
#define FLOAT(offset) *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(this) + (offset))
#define OPPONENT_FLOAT(offset) *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(FIELD(void*, 0x2E8)) + (offset))
```

With these authentic F062-style expression forms and the independently
verified Yukari-specific logic, natural VC7.1 `/Od /Ob0 /Gy /GR- /GX- /GS
/Zi` produced **635/635** nonrelocation matches and **11/11** original
physical DIR32/REL32 bytes/references at their authentic 679-byte locations.
Cold replaying **only** `yukari-fighter-update-special-state-0059b490`
returned **1/1 exact**. The F062 1,027 bytes and their external callee
bodies are not double counted. Source `src/YukariSpecialStateF345.cpp`;
ignored diagnostic controls `.analysis/f345-yukari-boss/`. No artificial
padding, assembly, bogus locals, byte masks, truncated functions or remote
Factory receipt are asserted. The complete original fighter layout and
private class name remain provisional.

## F343: still-unmatched 171-byte archive registry reference-release control

The R053-authored `0041CE50..0041CEFA` native reference count/cleanup
function was independently decoded (original SHA256
`558f79a85d376b77e258f05eb4bd8020d61b14bf893eaa9cd06d060ed0174975`).
A natural 171-byte source matches 108/115 nonfield bytes. It decrements
+0068BE04, deletes resource pointers through original `0041D8C0`, frees
owned names, clears two original registry collections, and retains all 14
real code references. Seven EBP local displacements remain unmatched, in
the native scalar deletion/filename temporaries. Experiments with variable
declaration order, lexical scopes, direct vs named pointer, and meaningful
filename aggregates did not match. Diagnostic sources/results are retained
in `.analysis/f343-archive-release/`; this function is **NOT accepted**.


## F346: 497-byte character-select cancel animation, select-only x87 lvalue macro

The full R089-authored `00435870..00435A60` function,
`CharacterSelectScene::UpdateCancelAnimation`, has **497 original CODE
bytes**, **114 native x86 instructions**, and PE SHA256
`914eacb92c8142897df62d92a9a403daafeeeaae3264ff6724f1474b06d6ba9c`.
Native thiscall receives a signed-char player index at +8, steps four
position floats (+A0/+A8/+B0/+B8), subtracts from the progress at +C0,
compares that value with original +00658264 stop constant, and upon the
observed mode (+18 +1C*player) plays sound 40 and resets four screen floats
and independent flags. Every actual signed byte extension, field offset,
float constant, sound receiver, and native return extent was inspected.

Historical F270 complete probes emitted the correct 497-byte length and
13 genuine reference fields but **438/445** nonrelocation bytes; at offset
`0x140` the compiler loaded the indexed float before stop constant, whereas
native loads the constant first. Broadly removing outer parentheses from
*every* float lvalue macro worsens the result (only 408/445 comparable).
After F345 demonstrated the concrete VC7.1 expression-form sensitivity, a
more precise hypothesis proved correct: retain the earlier `FLOAT(off,i)`
for the four movement comparisons, but use exactly one unparenthesized
`STOP_FLOAT(i)` lvalue for the final +C0 equality. With `STOP_FLOAT(player)
== g_ChoiceCancelStopAt00658264` (not its operand-reversed equivalent),
the compiler naturally emits the original global-first x87 comparison.
The 497-byte native original then matches **445/445 nonfield bytes** and
**13/13 independently decoded, physical original relocation fields**.

`src/CharacterSelectCancelF346.cpp` is complete natural C++ (no original
byte copying, assembly, fake locals, or truncation). Targeted cold replay of
**only** `character-select-update-cancel-animation-00435870` returned
**1/1 exact**. Private scene owner and original sound routine remain borrowed
only; neither target extent is double credited. The old F270 "one x87
comparison pending" is now obsolete, though all negative controls remain in
`.analysis/f270-character-cancel/` and `.analysis/f346-cancel-macro/`.


## F347: complete 746-byte sprite sequence render, native x87 scale operand order

`SpriteSequence::RenderElements` at `00411110..004113F9` is a full original
**746-CODE-byte**, **198-instruction** R046-authored render function, with
PE-backed original SHA256
`ac21e238be71c4675b81ee5b7a2b7c0ae128406ffba4880b9650846718727cfe`.
The source `src/SpriteSequenceRenderF347.cpp` reconstructs the entire guarded
list traversal, signed timing/spacing, counter, texture RECT, blend selection,
132-byte quad object construction and copied quad, original alpha/tint
computation, 3-axis translate, and either direct quad or projected quad draw.
Its borrowed iterator, render backend and nominal quad interfaces are *not*
claims to complete private object layouts. The full native function has a
final `RET` and no post-RET owned table.

Historical F331/F332/F336 complete 746-byte probes were only 599/614 comparable
nonrelocation bytes: three separate x87 scale comparisons each differed in
five genuine native bytes. Previous attempts varied `volatile`, pointer/ref
types, field accessor, named scale triple, and equality forms with a symbolic
global zero on the **left**; none matched the *whole* original body. F347
retested independent natural C++ alternatives. A nonzero scale condition
expressed as `scale.x != 0.0f || scale.y != 0.0f || scale.z != 0.0f` (with
float zero **on the right**) emits the native `FLD [0065782C]` followed by
`FLD [original scale field]` at all three points. Zero-first, named zero-left
and double-precision literals remain negative controls. The matching literal
is a genuine VC7.1 compiler float constant, not a copied target blob.

The resulting 746-byte object matches **614/614** nonrelocation bytes and
**33/33** genuine physical DIR32/REL32 COFF fields, including each exact
callee target and the three `0x0065782C` zero references. Full native
instruction extents and all fields independently checked; only new unit
`sprite-sequence-render-elements-00411110` was cold replayed, **1/1 exact**.
No truncated body, compiler/list callee credit, assembly, invented data
padding, or remote Oracle receipt.


## F348: complete 874-byte Suika special-state boss, three x87 order corrections

The R067-authored `SuikaFighter::UpdateSpecialStateAt005C3FB0` entire native
`005C3FB0..005C4319` extent is **874 CODE bytes**, **237 original x86
instructions**, original PE SHA256
`3c6dd4c37824d3c79bc986c961905f1676647166439db4483f70a36849a8c73a`.
Its source in `src/SuikaSpecialStateF348.cpp` implements the original contact
reset; descending signed shot counter at +0xF1C; parent sound Play(3), two
actual 0x336/0x337 projectile launches with the true `Rand(0,100)` guard and
`Rand(0,40)` plus 20.0f horizontal offset; signed 0x3B6/0x3B0 guard/reaction
logic; charge state at 0xF1E and signed 0x324/0x3A0 checks; and opponent
relative distance-state clamping at 0xF26. Native control returns and the
real `RET` after the 874-byte body are preserved. The original full fighter
class remains unknown; its borrowed method/interface declarations are
not constructed, embedded or claimed as original owner source.

The F313/F314 full 874-byte probes retained **742/794** comparable bytes
and 20 real references, with unresolved x87/actor pointer lowering. Fresh F348
changes only experimentally justified source expressions. Using the known
`F345`-style direct scalar `FLOAT()` and `OPPONENT_FLOAT()` lvalues improved
all repeated actor-relative field-load orderings, reaching 782/794. The
initial exact float-zero comparison is naturally `FLOAT(0x50)==0.0f`
(physical constant at `0065782C`), resolving four bytes, reaching 786/794.
The remaining two projectile X position expressions are the actual
`OPPONENT_FLOAT(0x44)+20.0f`: the target's original 20.0f constant is at
`0065786C`. A genuine right-hand literal emits original `FLD [actorX]` then
`FADD [0065786C]`, instead of globally loading 20.0f first. This recovers
the final eight bytes, giving **794/794** complete nonrelocation match.
The separate Y offset 40.0f remains the actual original external constant
with all its physical relocations. No arbitrary padding or asm is used.

All **20** physical original COFF DIR32/REL32 fields, including both
`__real@41a00000` addresses, zero constant, sound/random/spawn direct calls,
original Y offset and four distance constants, resolve to their exact native
Destinations. Only the affected
`suika-fighter-update-special-state-005c3fb0` was cold-built with pinned
VC7.1 `/Od /Ob0 /Gy /GR- /GX- /GS /Zi` and reported **1/1 exact**, all
874 CODE bytes. Earlier failed experiments remain in ignored F313/F314 and
F349-F351 evidence; this supersedes their pending claim. No extra byte credit
for external callees, unknown original class layout, or external Oracle receipt.


## F353: complete 245-byte archive registry open/registration with native EH

The R053-authored `0041CF80..0041D074` native routine consists of **245
CODE bytes** and 69 complete independently decoded x86 instructions. Its
original PE-backed SHA256 is
`a4aab60a6b8d367c1779da30e8a4ba340e81e5838029e0d38a98865eac05dcc3`.
It is a **cdecl** two-argument function with the original VC7 exception
registration and cleanup-state frame (`0065543B` handler). It appends a
null pointer to the resource deque, constructs a genuine **16-byte** archive
instance through native `0041D190` after operator new, stores it at the
original deque back and invokes the previously exact `0041D510` index loader.
It then appends a null name to the name deque, uses `strlen + 1`, native
second array allocation and `strcpy` to register the supplied name. Neither
external deque code nor constructor/CRT/EH callee code is separately credited.
The 16-byte allocation footprint is observed, not a claim to complete source
for that class or deque representation.

The initial natural source was 257 bytes, adding two pointer-name transfers.
Direct natural new expressions at the two actual back-pointer assignments
restored the complete original **245 bytes**, but the first probe had 9 true
EBP slot-byte differences (148/157 comparable). Rechecking actual native
relative slot positions showed the original name deque null value is passed
through a genuine temporary to a `const&` pointer parameter, not a named
`char*` with the same lexical lifetime as the archive null. Replacing only
`char* emptyName=0; Append(emptyName)` with
`Append(static_cast<char*>(0))` preserves real C++ semantics and lets VC7.1
reproduce every original stack offset: **157/157 nonfield bytes**, all
**22** real DIR32/REL32 COFF references and solved physical destinations,
including EH registration and both distinct operator-new call sites.
`src/ArchiveOpenRegisterF353.cpp` was independently cold-rebuilt with pinned
VC7.1 `/Od /Ob0 /Gy /GR- /GX /GS /Zi`; only affected unit
`archive-catalog-open-and-register-0041cf80` returned **1/1 exact**. No
external Oracle assertion, asm, copied bytes, fake locals, truncated body or
masking of relocation references.


## F354: complete two-side auxiliary effects update and prune with real iterator state

The R109-authored native `AuxEffectManager::AdvanceAndPruneTwoLists` at
`005F7D80..005F7E93` is **276 full original CODE bytes**, **93 original x86
instructions**, with original PE SHA256
`b23cb9469c9501989cd48500296650b521e9edc094c651e5a790c1d41c776b2b`.
It drives both side-indexed lists at the actual 20-byte receiver stride,
iterates a count/index pair to call the original virtual Advance method,
then traverses genuine 8-byte iterators, tests each child pointer's +8 state,
frees ended child entries using original CRT free, erases them from the list
through native `005F8290`, or invokes native postfix++ for continuing items.
The original `RET` is included, and all related list, virtual dispatch,
operator!=, operator*, End and Begin calls preserve native behavior.

Earlier whole 276-byte F298/F327 sources produced 233/236 nonrelocation
matching bytes and had *three physically different stack references*: native
End writes to EBP-0x1C while removed child pointers occupy EBP-0x20,
not compiler-chosen -0x20 and -0x18 respectively. Whole native analysis
identified four contiguous meaningful control values in the original
frame: `removed` pointer at -0x20, 8-byte `end` iterator starting -0x1C,
`index` at -0x14 and `count` at -0x10. Modeling those values in their
true order as a 20-byte `IndexCountF298` physical control struct and
passing its `end` to the original 8-byte hidden-sret End call reproduces
those native slots naturally. `EndInto` is only a caller-side alias for the
*real* `005F80E0` End entry and does not assert original source spelling
or an extra method. Other tested orders produced 226/236 or retained the
old 233/236 negative results and earned no credit.

`src/AuxEffectPruneF354.cpp` with VC7.1 `/Od /Ob0 /Gy /GR- /GX- /GS
/Zi` reproduces **236/236** nonrelocation bytes and **10/10** physical
COFF REL32 destinations over the **entire 276-byte native function**. Only
new unit `aux-effect-manager-advance-prune-two-lists-005f7d80` was cold
replayed, yielding **1/1 exact**. Borrowed deque/iterator interfaces are
not an asserted complete private layout, and no CRT, runtime, external
callee or compiler-generated body bytes were additionally credited. No
assembly, arbitrary padding, artificial inert local, masks, truncated
function or external Oracle acceptance is claimed.


## F361: independent whole 1,027-byte character auxiliary special-effect controller

Original R049-authored `CharacterAux::RunAt00496C60` at `00496C60..00497062`
contains 1,027 **entire** native CODE bytes and **240 decoded original x86
instructions**, original PE SHA256
`8e5055e414cb2c3bd4a8eab29ac0cf7b4a7c49ef8968d48ae8720c2a01ddc3ec`.
The native method clears grounded/inactive contact flags, then responds to three
separate signed action windows (0x96..0x99, 0x9a..0x9d, 0x9e). Each branch
resets the original +0x2F6..+0x310 transform, 1.0f scales, 255 color,
float motion values, spawns a tracked effect through the authentic inherited
`00453AC0` at unique Y offsets 94/60/100 and marks the one-shot +0xF0A.
Unlike an already exact F062 auxiliary controller, this native code uses
**effect 817** (0x331), `linked=0`, and tracks opponent-relative distance
in signed short +`0xF32`, not effect 998 / linked 1 / field +0xF2A.
The actual original `RET`, original 1027-byte CFG and all branches were
independently reviewed; no other emitted callee or private class code is
claimed.

The independently exact 1,027-byte F062 source was an expression-shape
starting point, **not** an assumed identical body. We extracted only the
genuinely shared declaration-only inherited ABI and C++ macro expression
form, then separately replaced every target-specific effect/scale/flag and
distance field using the actual native original. The very first native-correct
F361 probe compiled as a full **1,027-byte** function, matched **983/983**
nonrelocated bytes and the complete **11** original genuine COFF relocation
fields/destinations including all three original tracked-effect calls and
eight distinct float constants. The standalone unit
`character-aux-special-00496c60` under pinned VC7.1
`/Od /Ob0 /Gy /GR- /GX- /Zi` cold replay was **1/1 exact**. The original
whole fighter layout and exact nominal C++ method name remain unknown, with
no assembly, byte grafts, fake locals, masked references, cropped CODE,
full-repo cold replay or external Oracle receipts.


## F362: second independently original 1,027-byte auxiliary state controller

The R049-authored function `00470A40..00470E42` is **1,027 entire original
CODE bytes**, 240 independently decoded x86 instructions, with original
PE SHA256 `3778ba85e4a5bf91f1cb8dc0a9bfb67df547dc839dc14d0426d659589608dec3`.
It implements the original player-side zero/contact flag reset, 3 independent
action windows with the original effect ID 998, three distinct 94.0f/60.0f/
100.0f vertical offsets and exact 57×signed-facing X calculation, side
effect texture/channel resets and the original 540/320-distance f2a timer.
The exact body structure can be compared with separately already accepted
F062 `CharacterAux5E5500::AdvanceAuxiliary` (at `005E5500`), but the complete
original C++ source is not proven to be the same original class or original
nominal method; this target's address and its three physical REL32 call
placements remain independent original evidence. Its original body is
not credited by copying F062's address/bytes or duplicating any CRT/SDK/callee
credit.

The natural, self-contained source `src/CharacterAuxSpecial00470A40F362.cpp`
compiles with native VC7.1 `/Od /Ob0 /Gy /GR- /GX- /Zi` into **983/983**
nonrelocation bytes, and all **eleven** genuine DIR32/REL32 fields/destinations
(three direct calls to `00453AC0` and eight independent original float
constant entries) match the actual target. Single newly affected F362 unit
`character-aux-special-00470a40` returned **1/1 exact** on independently
recompiled cold source. It is complete original authored CODE credit only;
private full receiver/class layouts and original naming remain provisional.

## Post-F362 negative large-boss probes: native Marisa auxiliary particle chain

Independently decoded complete R049-authored `00497070..0049757A` is **1,291
CODE bytes** with **273 x86 instructions**, original PE SHA256
`317471d44dd19b5a4aadd99760da7725ef1c549429b3109b7d9e979e57222acf`.
The native function is a nested eight-stage / 36-sample particle ribbon
renderer with genuine 132-byte quad, 28-byte particle records, signed phase
and directional short words, four cosine/sine lookups per sample, original
32-bit and x87 signed integer conversions, two quad transforms, and 74-vertex
draw calls. It is *not* part of F362 and has no exact credit.

Fresh complete semantic probes under `.analysis/f356-character-aux-boss/` and
`.analysis/f358-marisa-frame/` corrected a formerly guessed second quad
corner (the original uses the fourth vertex at quad byte +48). Tests of
meaningful local-state layouts reached a full 1,284-byte compiled routine
(270 instructions), but still mismatched stack placements. Crucially, reading
the real original `004116F0` six-float call ABI and putting the three zero
angles **first** and computed phase angles **last** in natural C++ matches
the original right-to-left argument evaluation. Putting the integral float
offsets on the left of the two phase sine/cosine sums, and reversing the
arguments inside the trigonometric phase expressions to match actual target
x87 loads, yields **the whole original 1,291-byte length, identical 273
mnemonics and instruction lengths**, and a diagnostic **1043/1167**
nonrelocation byte match. All 31 compiler-generated COFF relocation sites
were listed; the target native particle-depth field at `006582E0` still
requires expression-order correction, and most remaining difference bytes
are authentic EBP local displacements. None is masked or accepted. The
original 0xE8 stack frame contrasts with the currently best 0xE0 compile
frame; a real C++ source type/lexical layout must explain the missing eight
bytes rather than adding arbitrary padding.

The current `src` tree has **no** adopted `00497070` source; the complete
meaningful experiments and failed variants remain in `.analysis/f356-*`,
`.analysis/f358-*`, `.analysis/f359-*`, `.analysis/f360-*`, `.analysis/f361-marisa-expression-order/`,
`.analysis/f362-marisa-carrier/` and `.analysis/f363-marisa-shorts/` as private
lossless negative evidence. Existing document guesses or identical instruction
counts never establish exactness. No partial CODE credit, full cold replay,
manual assembly or target-byte grafts.


## F363: complete distance-first 1,028-byte character auxiliary policy at 00555530

The independently authored R049 `CharacterAux::RunAt00555530` has exactly
**1,028 original native CODE bytes**, 240 complete original x86 instructions
ending in the native `RET`, original PE SHA256
`e6460e8bb4113ca1fb20e8024adafdb0e6c589331e698129c758d90b2b67cb34`.
It is *not* identical to the 1,027-byte F062/F361/F362 auxiliary helpers.
Original Ghidra/PE evidence shows the ground/contact `0x50/0x3AC` reset
first, then two independent opponent-relative distance clamps and reset
on signed short `+0xF0C` (**before** effect spawning), and finally the
three guarded action windows with original effect 850 (`0x352`), 1.0f
scale, actual 3 Y offsets 94/60/100, 255 byte colors and the true
`+0xF0A` one-shot effect bit. All 3 authentic inherited effect call
references target `00453AC0`; the original complete fighter private owner
and C++ spelling are still not independently recovered.

Instead of blindly adopting a prior C++ reconstruction, F363 used the
independently native-confirmed codegen/field macro shape as an experimental
control, changed original field and literal values, and **physically moved**
the real distance guards ahead of the action block as in the complete
native 1,028-byte control flow. Pinned VC7.1 `/Od /Ob0 /Gy /GR- /GX-
/Zi` then reproduced every one of the original **984/984 nonrelocated
bytes** and **11/11 physical original COFF DIR32/REL32 destinations**.
Only affected unit `character-aux-effect-distance-first-00555530` was
cold-built and returned **1/1 exact**, including the entire original body.
No F062 call/helper bytes are counted, no fabricated padding/locals, asm,
masking, cropped comparison, external Oracle claim or all-unit cold replay.


## F364: full 1,121-byte timed character auxiliary special policy at 00577750

The R049-authored original `CharacterAux::RunAt00577750`,
`00577750..00577BB0`, is **1,121 complete original CODE bytes** and
**261 independently decoded native x86 instructions**, original PE SHA256
`01c37dade91b7b7c9d0b9a5ba90c5f1efc092304af2473cd305dd34fe834ea2e`.
It first clears grounded/inactive state at +0x50/+0x3AC. The separately
observed signed-short +0xF0E state advances by two when +0x3B8 is zero,
resets if negative, and wraps when it reaches **360**. It then has the
three distinct +0xF0A one-shot action-state effect-spawn windows using
original inherited `00453AC0`, effect 899 (0x383), signed facing
multiplied by 57, original Y offsets 94/60/100, 1.0f scale and linked
flag 1. Final signed short +0xF10 tracks opponent-relative distance
540/320 clamps. Names/owner layouts remain provisional, not asserted.

The F364 natural source began with experimentally validated shared
F062/F361 field/compiler shapes, but used only target-observed distinct
fields/values and added the three genuine timer guards from original
Ghidra and native x86. First complete 1,121-byte probe matched
**1075/1077** comparable original bytes, all 11 physical relocation
positions, but emitted `CMP 359; JLE` where native uses `CMP 360; JL`.
Expressing the exact native condition as `FIELD(short,0xF0E)>=360`
reproduces both byte positions: **1077/1077** comparable code and all
**11** genuine DIR32/REL32 physical relocation destinations, with three
real calls to `00453AC0`. Independent affected-only cold replay of unit
`character-aux-timed-special-00577750` under pinned VC7.1
`/Od /Ob0 /Gy /GR- /GX- /Zi` returned **1/1 exact** across all original
1,121 CODE bytes. This credits no generated/library/callee bytes or
unknown class layouts, uses no masked/patched bytes, fake locals, assembly,
cropped function, all-unit replay or external Oracle claim.


## F366: three genuine stage background blend callbacks, 60 CODE bytes each

Original R231-authored `BackgroundStage::ApplyBG02aBlendAt0044B980`,
`ApplyBG02bBlendAt0044BEA0`, and `ApplyBG02cBlendAt0044C3C0` are three
**distinct, independently reviewed original** 60-byte functions, each 18
original x86 instructions ending at their native `RET`. Each computes and
stores two real camera coordinates: it loads original global X at `00671404`
and adds physical original X offset constant `00657834`, converts with
`__ftol2` at `006406AC` and writes an actual local; then reads global Y at
`006713C4`, converts through the second `__ftol2` and writes the other
actual local. It passes zero to the existing stage-local renderer at
`this+0x18` and calls original `SetBlendMode` at `0040C7F0`. These x/y locals
are genuinely present in the original CODE even though the function makes no
further reads; their source equivalents model native behavior, not inert
fake padding. The original complete stage private owner class remains
unknown, so the render backend is a pointer-only borrowed interface.

The three original independent PE body hashes are, respectively,
`d840c9b1051ac3549ef7c72fc342a4f6cc6f3444ec22bbaa007d38530ddfa095`,
`49bfa3ecf1fbb5a65682807edc82a21174533deeadc36a288c3b463952129f38`,
and `eab49a1a72fbed66caeb0170f2b4ceb91c315fee4517fd5176f1a7eb620737c6`.
A single natural C++ source `src/BackgroundBlendF366.cpp` declares three
separate method bodies with genuine camera X/Y computations and sets blend
mode 0. Pinned VC7.1 `/Od /Ob0 /Gy /GR- /GX- /Zi` emits all three as exact
60-byte individual functions: **36/36** nonfield bytes and **6/6** real
physical COFF relocations per target, all destinations independently solved.
Only the three affected units were independently cold replayed together,
yielding **3/3 exact across one object** and 180 total distinct authored
CODE bytes. Neither crt `__ftol2` nor the renderer callee is double counted.
No fake or obsolete variables, source-dependent masks, assembly, truncated
function, full-project cold replay or Oracle certification.


## F365: complete 1,576-byte extended character auxiliary with native compound timer and signed projectiles

The independently reviewed R049-authored native `CharacterAux::RunAt00505A60` at
`00505A60..00506087` is **1,576 full original CODE bytes**, **386 original
x86 instructions**, original PE SHA256
`290a5ead5da248b3d3476ee0d1dd45b75a902fd73bcab3b5c17d960c915e9b96`.
It resets ground/contact flags, advances and wraps two signed angular timers
(`+0xF0E` facing×5 and `+0xF0C` +2), implements the real active `+0xF10`
directional random projectile policy including signed opponent-facing
comparison, original strength at `+0x490`, Rand(0,100) and Rand(0,640)
through `00455580`, and two directional effect 908 projectile spawns via
`00453A70`. It then updates the genuine three effect 817/linked-1 one-shot
action windows through the inherited `00453AC0` and the original signed
`+0xF12` opponent distance clamp. These are native-specific policies, not
generalized promises about any complete original class.

The first complete semantic natural C++ emitted 1,592 bytes: its unsigned
comparison flag triggered a nonnative 64-bit x87 integer conversion. An
actual signed comparison restored normal integer `FIMUL`, but a named
comparison temporary still emitted 1,583 bytes. Inlining that meaningful
signed condition restored the original 1,576-byte/386-instruction shape
with residual compiler register differences. The original +F0E timer
is naturally expressed as `FIELD(short,0xF0E) += FIELD(signed char,0x66)*5`:
this genuine compound assignment lets VC7.1 preserve EAX across the original
loop timer, short comparisons and subsequent actor pointer uses, instead of
the equivalent `FIELD = facing*5 + FIELD` form, recovering every remaining
nonrelocation byte with **1504/1504** original nonfield matches. All
**18** native DIR32/REL32 physical COFF references and original solved
destinations (real float constants and both projectile+tracked-effect
spawners) were independently checked. Only the affected
`character-aux-extended-composite-00505a60` unit was independently cold
replayed, **1/1 exact**. After a connector failure interrupted canonical
adoption, source and match-unit dirty changes were inspected and retained,
then completed in canonical ledgers and checkpoint without resets. No whole
project replay, cropped CFG, fake locals, ABI lies, assembly, byte copying
or external Oracle certification.


## F370: full 1,060-byte 27-pattern character-input priority chain

The independently reviewed R049 original authored `CharacterAux::RunAt00532520`
at `00532520..00532943` is **1,060 native CODE bytes**, **305 native x86
instructions**, original PE SHA256
`3e8c264e7cd987f4c13faf1f44cb0d419616fad6237260decb925fcd77a3d68c`.
It resets the original per-character action byte at `+0x511` and tries 27
distinct original ordered input patterns by calling the real game input matcher
`00455800`: 4 five-char patterns with limit 15, 12 four-char patterns with
limit 15, 9 three-char patterns with limit 10, and 2 trailing four-char
patterns with limit 15. The records at `00659920..006599CC` are independently
observed original constant pool addresses; complete string storage and actual
original input matcher implementation are borrowed, not credited. The action
priority values are target-specific and each checked against the real native
conditions before source adoption. Every matched pattern writes a distinct
original action-value byte (with some intentionally grouped repeats) and
short-circuits later checks. This native shape is a natural C++ `if/else if`
priority chain, not a loop, table-based reduction, or pasted disassembly.

A fresh natural 27-condition implementation in
`src/CharacterInputPriorityF370.cpp` compiled with the pinned VC7.1
`/Od /Ob0 /Gy /GR- /GX- /Zi` flags into the *whole* exact original
**1,060-byte** function on its first attempt: all **844/844 nonrelocation
bytes** and all **54 physical COFF DIR32/REL32 references** matched the
original targets. These are the 27 independent real native pattern addresses
and 27 references to the real game `00455800` callee. Independent
`--unit character-input-priority-controller-00532520` cold replay
returned **1/1 exact**. No pattern bytes or external callee code,
unused sentinel locals, manual assembly, cropped function, masked refs,
whole-set replay or external Oracle receipt is asserted. The original
receiver class name and complete layout remain provisional.


## F371: complete 1,757-byte character active/borrowed-opponent controller boss

The native R049-authored `CharacterAux::RunAt004C49C0` is an independently
reviewed **1,757 original CODE bytes** at `004C49C0..004C509C`, with
**413 original x86 instructions** ending in a real RET and original PE SHA256
`e12a32537b16bf75c5c458d44a73efdf1282c60b7b18a1bc99d040c4d7e1fad5`.
Its substantial game-specific policy starts with grounded/contact reset;
if original signed short +F0C is positive, it maintains a 0.75f movement
scale with a genuine +F0E short countdown or native inherited sound action
call `00453E80`, synchronizes +F0C to actual +3B0 action time, and
conditionally interrupts two modes 1 and 2 through real `0046D000`
with the original mode thresholds. When not active it instead selects 1.0f.
Another branch for +F12 active ties +84/+88 and +F10 to opponent-owned
+3BC and +10 state, and invokes original borrowed opponent action routine
`0040FBB0` through the real +2E8 receiver pointer. Three separately
guarded action-window effects use authentic +0x60, +0x62, +0x64 and +F0A
flags, repeat the genuine 0x2F6..0x310 native transform/byte-color writes,
and spawn effect 817 through original `00453AC0`: their original X facing
factors are **30, 70 and 57** (not always 57), and Y offsets 94/60/100.
Original opponent-relative 540/320 distance checks clamp +F16. Borrowed
opponent/method interfaces do not assert a whole original game class layout.

An independent natural source constructed from native CFG and original
role-specific field/constants initially emitted 1,754 bytes. The native
condition at +F0C has positive-active fallthrough, unlike a semantically
equivalent <=0-first source. Two nested mode guards also use native
`if(actionTime>limit) InterruptSpecial; else clear` branch ordering rather
than a reversed <=-first version. Correcting these real branch directions
restored the native unconditional/conditional jump layout. Expressing the
actual 16-bit +F0E countdown with `--FIELD(short,0xF0E)` rather than an
ordinary int-promoted `FIELD(short,...) = FIELD(short,...)-1` restores
original 16-bit short operations. Those changes generate the **complete
1,757-byte** source code with **1689/1689** authentic nonrelocation bytes
and **17/17** authentic DIR32/REL32 COFF physical fields/destinations,
including four mode-interrupt calls, one native sound, one opponent call
and three tracked effects. Only new unit
`character-aux-active-opponent-special-004c49c0` was pinned VC7.1
`/Od /Ob0 /Gy /GR- /GX- /Zi` cold replayed, yielding **1/1 exact**. No
other game callee/CRT/owner byte credit, invented source locals, masks,
manual assembly, cropped extent, full cold replay or external Oracle receipt.


## F374: eleven complete 130-byte fighter special-variant switches with 40-byte native jump tables

The R049-authored original game has separate 130-CODE-byte / 36-instruction
methods selecting each character's move/FX variant for the original
signed global `0067161E` mode byte. These are located at: Reimu `00470E50`,
Marisa `00497580`, Sakuya `004C50A0`, Alice `004E63A0`, Patchouli
`00506090`, Youmu `005305A0`, Remilia `00555940`, Yuyuko `00577BC0`,
Yukari `0059B740`, Suika `005C4320`, and Meiling `005E5910`. Every complete
method uses a native ten-way `switch` for global modes 1..10 and stores
**seven** distinct game role-dependent case action IDs to true byte
`this+0x6E5` (modes 7/8/9/10 intentionally share the last case branch).
Each original code extent finishes at `entry+129` with a real RET; directly
**after** it lies an original **40-byte owned switch table** with ten native
absolute pointers to original distinct case labels. Those tables are data,
not separately authored executable CODE. Neither the F374 source nor the
byte counts claim any complete original fighter owner allocation/layout.

The natural source `src/FighterSpecialVariantsF374.cpp` contains eleven
distinct separately named C++ `switch` policies, whose seven *semantic action
values* were independently decoded and checked from each original native
body (not copied raw machine instructions or an invented generic table).
VC7.1 pinned `/Od /Ob0 /Gy /GR- /GX- /Zi` compiled all eleven exact
functions in a single object. Diagnostic comparison across the **full 170
original bytes** of each method plus immediately owned switch table gives
**122/122** nonrelocation byte matches, plus **12/12 original COFF DIR32
fields** per method: signed global at `0067161E`, local switch table at
`entry+130`, and ten local case pointers at true relative native labels.
Canonical units record `size = 130`, `compare_size = 170`; local symbol
origins and *every* original native physical table pointer are bound, so
the jump-table addresses cannot silently shift. All eleven affected units
were cold-replayed in one command: **11/11 exact across 1 object**. Only
**11 × 130 = 1,430 distinct authored original CODE bytes** are credited;
**11 × 40 = 440 matched table DATA bytes** are compared but not credited.
No cropped table, masks, fake switch returns or table bytes in SOURCE,
manual assembly, whole-repository cold replay, claimed unknown class
layout or remote Oracle acceptance.


## F375: complete 281-byte score ranking insertion and genuine date-frame lifetime

Original `ProgressRecords::InsertRankedScore` at `00416EE0..00416FF8` is
**281 original authored CODE bytes**, **85 original native x86 instructions**
with real `RET 4`, original PE SHA256
`f0d0e52b7834073511cc55e54606d944a8c4e07ab1f2720626750830f8cde1a3`.
The native method rejects a score no greater than the original low-score
threshold at owner +0x5F8 (returning byte 255), otherwise starts at rank 9
and repeatedly copies the original physical 16-byte rank record from the
previous slot while scores should move down. The `unsigned` rank comparison,
original 16-byte four-DWORD natural struct assignment, break before index
underflow, current date acquisition via `time`/`localtime`, true month/day
bytes +0x564/+0x565, score DWORD at +0x568, eight character bytes of value
100 and final unsigned-char rank value are all preserved. The observed
record layout includes genuinely copied but otherwise untyped bytes 10..11;
no private full record class/owner is asserted.

The initial entire natural source was 280 bytes because of a differently
arranged early return and two-branch do-while, not an incomplete function.
Changing to the real top early-reject test and a natural `while` copy with
`if(--index==0) break` recreated the **whole 281-byte / 85-instruction**
code shape, leaving actual original stack displacements unmatched. Native
index lives at EBP-4, `tm*` at EBP-8, `time_t` at EBP-C and name-loop int at
EBP-10. An eight-byte natural date record whose **real used fields** are
`time_t timestamp` then `tm* today` reproduces exactly those stack slots
without inert locals or padding. This yields **273/273 original nonrelocation
bytes** and **2/2 genuine runtime COFF REL32 references**, with native
`time` at `00641AFE` and `localtime` at `0064197E`. The whole source in
`src/ProgressRankInsertF375.cpp` was independently cold-rebuilt under
VC7.1 `/Od /Ob0 /Gy /GR- /GX- /Zi` as only affected unit
`progress-records-insert-ranked-score-00416ee0`, **1/1 exact**. No library
callee credit, copied machine code, fake ABI/layout, masks, cropped original
CODE, whole cold replay or external Oracle receipt.


## F376: complete native stage background 00a/00b load constructors with original EH

The R055-authored original stage background load entries
`BackgroundStage::LoadBG00a` at `00449AA0..00449B36` (**151 native CODE
bytes**, 39 original instructions, PE SHA256
`d45a2d51fe47f942c82e292bbe4c150f8ba28f32082148c4e3a50016845f05d7`)
and `BackgroundStage::LoadBG00b` at `00449E10..00449EB0`
(**161 CODE bytes**, 41 original instructions, PE SHA256
`f84917e5088d10f58f1de4be9fc9d76e087bc40adb7566ab0522ca96e2499798`)
are independent full original 32-bit VC7.1 `/GX` exception-protected
derived C++ constructors. Each calls the real borrowed base constructor
`00449DE0`, installs its own original vtable (`00658434` or `006584A4`),
initializes a native stage camera data packet with real `0040D990` at
`this+0x68` or `this+0x6C`, allocates genuine resource slots via
`0040B1D0` at `this+0x18` (3 or 4 slots), loads its own exact original
background directory/data via `0040BB80`, and clears the three original
DWORDs `this+0xC/+0x10/+0x14`. BG00b additionally clears `this+0x68`.
The real C++ EH entries and their distinct native handler references
`00655BF8/00655C18`, as well as SEH activation/deactivation, are
reproduced *by the compiler* from actual derived constructor source; no
manual assembler or forged EH output. No complete original stage class
allocation/field layout is asserted: base, camera and resource objects are
borrowed callable interfaces.

`src/BackgroundLoadPairF376.cpp` compiles both original 151/161-byte
constructor bodies naturally under pinned VC7.1 `/Od /Ob0 /Gy /GR- /GX
/GS /Zi` with genuine C++ base inheritance and destructor ABI. The two
complete originals match **107/107 and 117/117 nonrelocation bytes** and
**11/11 true original COFF DIR32/REL32 physical references** per body,
including the correct native EH handler, original vtable, base constructor,
asset strings and actual callees. Only the two changed units
`background-stage-load-bg00a-00449aa0` and
`background-stage-load-bg00b-00449e10` were cold replayed together: **2/2
exact across 1 object**, crediting 312 distinct original authored CODE bytes.
Other stage-specific loader variations remain unverified until independently
compared, and their similarly structured implementation is **not** counted
yet. No bytes from the base constructor, CRT, archive, vtables, jump data
or compiler-generated EH callees are double counted. No fake local padding,
assembly, raw byte graft, cropped comparison or full cold replay.


## F377: independently native-reconstructed 34-member stage background load-constructor family

All **34 remaining independently origin-reviewed R055 authored**
`BackgroundStage::LoadBG*` constructors (from `0044A230` through `00451C70`)
are now matched over their **entire true native CODE extents**. These are
separate original stage-specific functions and not imagined compiler thunks:
**five 140-byte**, **eighteen 151-byte**, **nine 161-byte**, **one 171-byte**,
and **one 181-byte** functions, totaling **5,219 distinct original authored
CODE bytes**, with actual native `RET` and every original VC7.1 `/GX`
exception-handler transition preserved. All 34 original `function-origins.csv`
rows were individually checked as authored before any CODE credit.

Each original was *independently* disassembled and source facts extracted: its
genuine `00449DE0` inherited base call; stage-specific vtable absolute
address and unique SEH handler reference; presence or absence of the real
`0040D990` native camera initializer and the independently observed camera
offset (`this+0x68`, `+0x6C`, `+0x70` or `+0x74`); exact original
`0040B1D0` allocation size (2, 3, 4, 5, 18, 26 or 54 slots); real background
directory/filename pool addresses and original `0040BB80` archive-load
call; actual three initialized DWORD material fields (`this+0xC/+0x10/+0x14`,
including real 0.0f / 640.0f / 100.0f cases); and any additional genuinely
initialized +0x68/+0x6C/+0x70 fields. There are **29 constructors with a
camera init call and 5 without one**. The 34 distinct original input addresses,
hexdumps/disassembly-derived observations, and per-target original complete
comparison JSONs are preserved privately under `.analysis/f377-bg-family/`.
The generation step is a way of spelling independently observed **natural
C++ source semantics** with real inheritance and field accesses; it does
not paste executable bytes or claim a complete original owner layout.

`src/BackgroundLoadFamilyF377.cpp` contains 34 separate stage-specific
constructor definitions under real C++ borrowed base, vtable, camera and
pack API declarations, no stage owner instantiation. Under pinned VC7.1
`/Od /Ob0 /Gy /GR- /GX /GS /Zi`, each full original native function
is structurally identical without manually written EH or branch code.
The complete 34-member object has **369** actual COFF physical
DIR32/REL32 references and all per-function positions, external native
addresses, vtable destinations and per-function EH handlers were
individually checked against the exact original PE. The canonical match
manifest has 34 separate units, each full real native CODE extent and
all physical relocation bindings; only those 34 newly affected units
were cold-rebuilt/replayed in one request: **34/34 exact across one object**.
No full-repository cold replay was performed. The initial two separately
accepted F376 background constructors remain unchanged and exact, so the
**36 original authored R055 LoadBG constructors** are all source-present and
exact. No game CRT, base constructor, vtable, archived assets, camera/pack
callee, compiler thunk or other nonoriginal CODE is double counted, and no
ASM, fake locals, byte grafts, masked relocation data, truncated function
or remote Oracle receipt is claimed.


## F378: full 1,008-byte command snapshot queue and special-mode character controller

The independently observed original R049-authored `CharacterAux::RunAt005301B0`
occupies **1,008 full native CODE bytes** at `005301B0..0053059F`,
**266 original x86 instructions**, original PE SHA256
`38e28c551c8935639a34b28022c1f920d75632522a5fe38a01d77bcf14bb6376`.
Its first genuinely owned value is a 16-byte stack command snapshot at EBP-10,
formed from two action shorts at +0x60/+0x62, the original x/y floats at
+0x44/+0x48, signed facing +0x66 and bearing short +0x80 with the natural
C++ alignment between those members. When +0x82 and +0x3B8 both vanish,
it calls the real borrowed queue methods at `00531CB0` (append with
snapshot pointer), `00531C60` (count), and `00531C80` (prune if >10)
through the real +0xFEC receiver. It then decrements signed +0xF10,
resets grounded +0x3AC if native zero float and positive flag, and when
+0xF0E is zero resets native effect transform/color fields. The latter
condition branches on the original signed global `006714B4`: mode other
than 3 always launches effect ID 810 through real inherited `00453AC0`;
mode 3 conditionally launches that same effect for action +0xF0C==1,
linked opponent/local active flags at +0x2CD and opponent +0x6EF, or local
+0x6EF. Four distinct original references to that effect spawner and their
actual state increment/write paths are included. Finally opponent-relative
540/320 checks clamp signed short +0xF14. The complete fighter and queue
owner classes remain explicitly borrowed, not inferred from a snapshot.

A new entire natural implementation started at 992 bytes because ordinary
`if(mode!=3) ... else ...` incorrectly collapses a redundant but physically
present second mode check. Comparing the full original x86 streams showed
**three native instructions and 16 bytes** for the second `mode==3` re-test.
The semantically faithful `else if(g_CharacterSpecialModeAt006714B4==3)`
emits those bytes and correct native jump targets under pinned VC7.1
`/Od /Ob0 /Gy /GR- /GX- /Zi`. The resulting entire 1,008-byte function
matches **936/936 nonrelocation bytes** and all **18/18 original physical
COFF DIR32/REL32 fields/destinations**, including three queue calls, four
real effect spawns, float constants, and both references to global mode.
Only affected unit `character-aux-queue-and-mode-effects-005301b0` was
independently cold replayed, **1/1 exact**. This credits no queue/effect
callee bytes, no unknown class layout, cropped body, fake locals/ASM,
byte masks, full cold replay or external Oracle verification.


## F379: complete 855-byte native character projectile lifecycle boss at 004F4170

The original R067-authored `CharacterProjectile::AdvanceAt004F4170`
is **855 complete native CODE bytes**, **243 original x86 instructions** at
`004F4170..004F44C6`, original PE SHA256
`6363210641192f26be157df6d995a88ed84882943871dca37ca72a45f56b2e3c`.
It owns a complete game-specific projectile state machine, not an animation
leaf: if its own +0x7C state is 5, it invokes native `0045B830` destroy;
otherwise it tests its parent fighter at +0xE4 action range 50..149 and
its own +0x62 motion mode, invokes the original destruction followed by a
one-iteration projectile 996 spawn via parent `00453A70`, and optionally
clears the parent +0xEFA timer and launches projectile 995. Outside that
branch it converts two observed float positions at +0xC8 and +0xCC to
signed shorts +0xDA/+0xDC using authentic `__ftol2` at `006406AC`,
calls original interaction `0040FBB0`, resets action state, sets true
polar velocity via original `0040FB70` with the native ratio constant,
resets scale/color fields, and computes native angle through `00483300`
with original radian divisor at `00657828`. Other modes either cancel
motion via `0040FB40` or advance physical X/Y with original signed facing
and apply stage-specific float scale decay. Bounds at native constants
`00659424`, `006595EC` and `006583B4` and original collision query
`0040FA30` govern destruction. Private parent/projectile layouts and
original C++ method names are borrowed, not asserted.

A first whole natural C++ source emitted 873 bytes, because two native
projectile-owner calls and an angle calculation physically push the
**unchanged 32-bit float bit patterns** through the borrowed caller ABI.
Declaring these parameters as float made VC7.1 generate extraneous x87
FLD/FSTP sequences. Correct caller-side raw-DWORD arguments and direct
original +0x1C->+0x20 bitwise scale copy restored the original full
**855-byte** extent. The last six nonrelocation byte differences at the
original Y motion calculation came solely from compiler register lowering:
the source form `FLOAT(0x48)=FLOAT(0x48)-FLOAT(0x54)` loads a pointer
after FLD, while the native original first loads **both** EDX/EAX actor
addresses and then does FLD/FSUB. Using one genuine unparenthesized
`*reinterpret_cast<float*>(RAW+0x48)` lvalue expression (the exact same
meaning without wrapper macro parentheses) reproduced the native evaluation
order, yielding all **767/767** comparable bytes plus every one of the
**22** real COFF DIR32/REL32 references and original solved destinations,
including lifetime, motion, collision, CRT and parent-spawn calls. The
whole natural source `src/CharacterProjectileAdvanceF379.cpp` under pinned
VC7.1 `/Od /Ob0 /Gy /GR- /GX- /Zi` cold replayed only affected
`character-projectile-advance-004f4170`, **1/1 exact**. No owner class
construction, external callee credit, unused fabricated locals, masks,
assembly, pasted native code, cropped function, whole cold replay or
remote Oracle certification.


## F386: full 1,958-byte battle input/replay state boss and its physical jump table

The R065-authored original `BattleState::ApplySequenceAt00445A00` occupies
**1,958 complete original CODE bytes** at `00445A00..004461A5`, with **504
fully decoded original x86 instructions**, original PE-backed SHA256
`7481c0bf597fa2ae5d9f36047fd145e539f51ad697f11af0e54f2291573e1ab2`.
Immediately following its complete RET lies a **separately owned 28-byte
original absolute jump table** for the seven cases of the replay switch,
`004461A6..004461C1`; the canonical `compare_size = 1986` covers **all
seven original physical table references**, and `size = 1958` correctly
credits **zero CODE** for its DATA table.

This is a genuinely large original game-specific input dispatcher, not
a generic CRT or compiler template. It handles battle mode 5 via native
`004480D0`; otherwise it consults the real replay queue object at
`006718E0` (Count `00414810`, Peek `004464C0`, Pop `004464E0`, Append
`00414830`). In replay mode 2 it sequentially consumes events, checks the
recorded frame and dispatches seven original control actions through the
real native `switch`: it updates the two distinct fighter states at
`this+0x44/+0x48` (character +0x324/+0x39D), local +0x1C mode,
positive/negative changes to both fighter +0x36C with native float
thresholds and boundary clamps. Outside replay it polls the genuine
key-scanner object at `00671638` through *thiscall* `00407170`, records
the original 2..7 actions when game mode requests it, updates native
+0x110 hold counter, two fighter +0x39D modes and both +0x36C levels.
The final direction-key branch invokes original `00423C60` with exact
physical priority actions and updates game input-enabled flag at
`00671632` using the true original unsigned DWORD gate `00671678`.
The Ghidra symbol names, full private battle/fighter/keyboard/queue layouts
and inferred roles remain provisional and are not embedded in source.

First fresh whole C++ source emitted 1,984 bytes **including** its generated
28-byte switch table, but had a 4-byte extra key local, an incorrect
`cdecl` signed-char scanner, and a signed gate comparison; those errors
produced extra stack allocation and repeated `add esp,4`/`movsx` sequences.
The original call ABI is a borrowed scanner method `CheckKey(int)` with
real `thiscall` object `00671638` and unsigned-byte result, eliminating
that local and restoring the genuine -0x28 frame. The native record
switch's character mode decrements are actual char predecrements.
A native `while(frame==Peek())` with real unsigned `Count()<=0` exit
reproduces both branches and the 1,986-byte full comparison extent; a
plain `Count()==0` was just 7 nonfield bytes away because it selected
`jne` instead of original `ja`. The last action-allowed control checks
key 0x1D/0x9D **or** unsigned input gate >5, writing one on true and
zero on false, preserving the native `cmp 5; jbe` and two branch targets.

The resulting `src/BattleStateApplySequenceF386.cpp` under pinned VC7.1
`/Od /Ob0 /Gy /GR- /GX- /Zi` structurally matches **1506/1506 original
nonrelocation bytes** and all **120 genuine original physical COFF DIR32/REL32
fields** in the *full 1,986-byte comparison extent*, including every
input/replay native callee, original game global, and all seven original
post-RET table targets. Native instruction limits, caller ABIs and all
physical relocations were reviewed independently. Affected-only canonical
`--unit battle-state-apply-sequence-00445a00` cold replay produced
**1/1 exact**, crediting **1,958 authored CODE bytes** only. No unknown
class allocations, borrowed helper/CRT/table data bytes, fake locals,
assembly, masks, cropped comparison, all-unit replay or remote Oracle receipt.


## F389: complete 3,765-byte battle stage loader with original 36 allocations and 23-case jump table

The independently reviewed R065-authored native
`BattleLoader::LoadStageAt004183D0`, at `004183D0..00419284`, is
**3,765 original CODE bytes** and **761 original x86 instructions**,
original PE SHA256
`9d670e4a82fec9987f1785f1d1818aec6677c609cd0d71ba91da8c45406a6076`.
Its complete `RET` is followed by the actually owned **92-byte** jump table
`00419285..004192E0`, 23 native absolute pointer entries (18 distinct
valid case labels and five native default-case references). All table
entries are physically compared and relocated, yet **none** are credited as
authored CODE. Canonical `size=3765` and `compare_size=3857` preserve both
those boundaries.

This is the original full battle stage loader, not a thin wrapper. It logs
the stage load via the original game logger `0041CC50`, conditionally
destroys the old global stage at `00671424` through the native virtual
scalar deleting destructor, and enters a **23-entry native switch** on
original signed stage ID `0067161D`. Its **18 meaningful stage cases**
0..15, 20 and 22 each have two distinct branches based on the real
unsigned stage-variant selector `00671604`, covering **36 actual native
`new` allocations and 36 original constructor calls** with genuinely
observed sizes `0x68`, `0xEC`, `0xF0`, `0xF4`, `0xF8` and `0x1D28`.
The 36 actual constructors at `00449AA0..00451C70` were already
**independently** cold exact in F376/F377, but **no bytes** from their
C++ bodies are counted again here: only the caller's own 3,765 CODE bytes.
Its VC7.1 `/GX` native EH frame and all 36 branch-specific exception
state transitions are preserved. The final battle-mode global `006714B4`
conditionally calls original `00419CB0`, and replay-mode global `0066C238`
gates the original audio/stage call `00416CE0` via receiver `006718F8`.
Native logger strings `00657A4C/00657A5C` retain their original addresses.

The source `src/BattleStageLoadBossF389.cpp` contains 36 **size-only
opaque carriers** for C++ `new` expressions, each with a verified physical
allocation footprint but **no asserted private stage member names, field
layout or method bodies**. The common virtual base exists solely to express
the original native deleting-destructor ABI. The first natural source
under pinned VC7.1 `/Od /Ob0 /Gy /GR- /GX /GS /Zi` already had the
correct **3,857-byte full comparison length** (3,765 CODE + 92 switch
DATA), 170 genuine COFF relocation positions and native SEH stack frame,
but was only 2754/3177 nonfield bytes because its semantically equivalent
`if(variant==0) base; else special;` generated each *base* body first.
Original disassembly proved the opposite fallthrough arrangement for
**every** stage ID: `if(variant!=0) special; else base;` writes the special
constructor first and conditional-jumps into the base one. Correcting
**only** these 18 native source control-flow directions recovered all
**3177/3177** remaining original nonrelocation bytes, including every
independent allocation, pointer store, destructor path and EH handler.
All **170/170** genuine original physical COFF DIR32/REL32 references
(including exactly 23 native switch-table pointers) were independently
checked against true PE relocation destinations. Only affected unit
`battle-loader-load-stage-004183d0` was cold-replayed, **1/1 exact**.
The 36 background constructor bodies, compiler/EH helpers, external
logger/audio/CRT methods and 92 jump table DATA bytes earn **zero duplicate
CODE credit**. No manual assembly, pasted machine bytes, arbitrary local
padding, masked refs, cropped function, all-unit cold replay or external
Oracle acceptance is claimed.


## F391: complete original 256-byte Alice special-state guard and opponent distance policy

The separately R068-authored original Alice fighter update at
`004E62A0..004E639F` comprises **256 complete original CODE bytes**,
**72 native x86 instructions**, PE-backed SHA256
`308c23d0e223bbfc2416e2444bcb26aeacbf569b5b93b3dcae58e85949ec1143`.
The actual game code clears signed contact byte `+0x3AC` when float +0x50
equals native 0.0f and flag is positive; it independently compares native
relative X against its true opponent pointer +0x2E8, using 540/-540 and
320/-320 boundaries and signed +0xF14 clamp/reset at 60. The Ghidra class
name and full private Alice fighter layout remain provisional; this source
declares only the independently observed borrowed field ABI.

`src/AliceSpecialStateF391.cpp` uses the same independently tested VC7.1
float lvalue expression shape as other accepted game-specific fighters, but
all original source fields and this independent physical extent were checked
against the R068 original, not copied as native bytes. Complete independent
original x86 comparison produces **236/236** matching nonrelocation bytes
and **5/5 genuine native COFF DIR32 constant-pool relocation fields**. Only
this affected unit was cold replayed, **1/1 exact**, as part of a two-unit
local F391/F392 replay. No private class instance, external callee credit,
assembly, fake locals, masked/cropped function, all-unit replay or Oracle receipt.

## F392: complete 56-byte original archive BeginUse reference-count and first-use policy

The R237-authored original `ArchiveCatalog::BeginUse` at `0041CE10..0041CE47`
has **56 complete native authored CODE bytes**, **17 x86 instructions**,
original PE SHA256
`d1535bcfaedd01fd759aace0acfcf125dc453f5705be4f2ac4339e7210de4fad`.
The actual source checks original catalog count `0068BE04` for zero; on
first use, calls the true container clear methods `0041DCD0` and `0041DF50`
for physical global resource/name registries `0068BE08`/`0068BE1C`,
then increments the original count and returns the caller's receiver
(`this`). This is not a constructor, and neither complete container owner
layout nor separate external list/CRT implementation is credited.

The natural `src/ArchiveBeginUseF392.cpp` compiled at exact native
length on its first reviewed trial, reproducing all **28/28 original
nonrelocation bytes** and **7/7 genuine physical COFF references** and
true destinations. Only the affected `archive-catalog-begin-use-0041ce10`
unit was independently cold replayed in the two-unit F391/F392 scope,
**1/1 exact**. No extra invented locals, assembly, code/data grafts,
masked references, truncated original or remote Oracle acceptance.


## F393: original independent 44-byte signed character and AI random-range helpers

Two separately reviewed authored original game functions,
`CharacterAuxObject::ChooseIntegerRangeAt00410F00` and
`CharacterAI::ChooseIntegerRangeAt00455610`, each occupy **44 complete
original CODE bytes / 18 native instructions** and have a single genuine
original `_rand` call at physical target `006418AB`. Their respective native
PE SHA256 values are
`bc5371baf16b8819fc51db20175a88ae5cf9ad95425c376a104dd5f4be3648bb`
and `32166d7d9655dc227f3f5a2c1623c07231e295f53a83f9d6b33d0ae615025d04`.
Both use the original signed lower bound, upper bound and original CRT
rand result to select an integer offset. The true native sequence computes
`maximum - minimum` **before** calling rand, keeps that range in the
callee-saved `ESI`, multiplies the return value, uses `CDQ`, `AND 0x7FFF`,
`ADD` and signed arithmetic shift right by 15 to round a division by 32768,
then adds original minimum and returns with `RET 8`. This precise signed
rounding is real game behavior, not a compiler/library function given
authored credit. The private receiver C++ classes remain borrowed ABI views.

The first semantically equivalent source `minimum+rand()*(maximum-minimum)/
32768` emitted only 42 bytes, putting rand before the range subtraction and
not preserving ESI, so it is a native **negative control**. Merely writing
the genuine source evaluation order as `(maximum-minimum)*rand()/32768 +
minimum` generates all native push/pop ESI and identical full original 44
CODE bytes. Both independently reviewed functions under pinned VC7.1
`/Od /Ob0 /Gy /GR- /GX- /Zi` matched **40/40** original nonrelocation
bytes and their one authentic physical COFF REL32 `_rand` field/destination.
Only the two affected F393 units were cold replayed together (**2/2 exact
across 1 object**) and credit **88** distinct authored CODE bytes; native
CRT rand itself is not credited. No byte graft, assembly, fake temporary,
truncated comparison, full cold replay or external Oracle receipt.


## F394: complete native signed progress unlock bitset set/test with correct 32-bit boolean lowering

Two independent R103-authored game-progress functions are fully reconstructed:
`GameProgress::SetUnlockBitAt00416CE0`, **108 original CODE bytes / 39 native x86
instructions** (PE SHA256
`957dee189131c6559bde1a9a5715e4176e5cc8404e4b1132e349321a7f3b23e6`),
and `GameProgress::TestUnlockBitAt00416DC0`, **93 original CODE bytes / 35
native instructions** (PE SHA256
`df52c9a7f30a5580c76056b8fdc2620d96b436bd89d50ab9d708189cef7cab29`).
Both are genuine native game policy that range checks the originally signed
16-bit input selector `0..320` and accesses physical owner bitset DWORDs
at native +`0x16A9C`. They use signed C++ `/32` and `%32`, causing the
original VC7.1 `CDQ`, remainder bias and signed shift sequence even though
the range guard makes negative values unobservable in the index expression.
No complete progress class layout or other GameProgress routine is credited.

The source setter has a real empty invalid-selector branch:
`if(selected>320 || selected<0) {} else bitset[index] |= mask`; the naive
valid-index-first equivalent omitted two original branch bytes. The test
returns 0 for invalid indexes, and its native final five-instruction
`XOR EAX,EAX; CMP EAX,EDX; SBB EAX,EAX; NEG EAX` performs an **unsigned
32-bit relational comparison converted to the return byte**. A direct
C++ boolean return or `setne` expression incorrectly emits a shorter
88-byte function. The native-faithful scalar-return form
`(int)(0u < (BITSET[index] & (1 << (selected%32))))` reproduces the
original full 93-byte function; an independent natural explicit ternary
`(0u < maskedBits) ? 1 : 0` was also experimentally **93-byte exact**,
with the alternate source retained under private research as a
negative/positive codegen control.

The original functions contain **no physical COFF relocations**; their
actual complete PE bodies are compared byte-for-byte with **108/108** and
**93/93** native bytes, no masking, and their canonical TOML units
explicitly declare `relocations = []` so a missing audit cannot be confused
with a verified absence of relocations. The existing in-progress F394
canonical source and two registry entries found dirty in the live worktree
were inspected and retained; only the missing explicit empty relocation
fields and corresponding frozen checkpoint SHA were repaired. Affected-only
`--unit game-progress-set-unlock-bit-00416ce0` and
`--unit game-progress-test-unlock-bit-00416dc0` cold replay returned
**2/2 exact across one object**, crediting **201 distinct original authored
CODE bytes**. No extra runtime/helper bytes, duplicate F397 credit, fake
local, assembly, cropped compare, full cold replay or external Oracle claim.


## F395: complete original selected auxiliary effect dispatcher, genuine 8-byte iterator and for loop

The R109-authored `AuxEffectManager::DispatchSelectedListAt005F7D00` is
**114 full original CODE bytes**, **41 native x86 instructions** ending in
its actual `RET 4`, PE SHA256
`77905fa4b9e3546107eeb0869d37a743fb08186907ad5ed134e7ccb84cd7ff1b`.
Its signed-char side selector chooses one of the authentic per-side linked
effect lists at owner `this + side*20`, borrowing the original physical
20-byte list ABI. The body constructs **two genuine 8-byte iterator
values** via native Begin at `005F80B0` and End at `005F80E0` (original
caller-side hidden-sret return slots). The actual control is a *for loop*:
first it jumps to the original comparator, then calls postfix increment
`005F8420` with real 8-byte returned temporary; `operator!=` at `005F8460`
compares to end and `operator*` at `005F8400` returns actual child address,
which is immediately dispatched via the real child vtable method offset +8.
The game-created child object, its private member layout, and the actual
list/iterator class implementation are only borrowed interfaces, never
constructed or credited here.

First semantic source `while(current!=end) { Child* p=*current;
p->Dispatch(); current++; }` generated 112 instead of 114 bytes and used
the wrong EBP slots: `while` starts by comparing and storing the child
in a named local before incrementing. Re-expressing the genuine original
control as `for(;current!=end;current++) { (*current)->Dispatch(); }`
reproduced the complete original 114-byte frame/CFG and the actual
borrowed child's temporary stack position *without fake locals*.
It matched **94/94 nonrelocation bytes** and all **5/5 original physical
COFF REL32 references and solved native destinations** (Begin, End,
postfix++, operator!=, dereference). The original virtual child call
remains naturally indirect at vtable +8. The sole affected unit
`aux-effect-dispatch-selected-list-005f7d00` cold replayed with pinned
VC7.1 `/Od /Ob0 /Gy /GR- /GX- /Zi`, **1/1 exact**, crediting just the
114 authored game CODE bytes. No hidden callee credit, forged ABI, asm,
byte grafts, fake padding, truncated body, all-unit cold replay or remote
Oracle receipt.


## F403: complete 85-byte signed profile selection copy into working record buffer

The independently R180-authored original
`ProfileSelection::LoadWorkingEightBytesAt00416E80`, at
`00416E80..00416ED4`, is **85 complete original CODE bytes / 25
native x86 instructions**, original PE SHA256
`4b44537c5945a10ab61e6120113072c537f016735350bdd39d05bf765b156182`.
Native code pushes the genuinely observed 8-byte length to CRT memcpy,
uses the original signed-byte fighter choice at `this+0x16AC4` multiplied
by original fighter-record stride 0x17F0 and signed difficulty at
`this+0x16AC5` multiplied by 0x5FC, then adds signed slot times 16
and physical per-record +0x55C offset. It copies from that selected
record *into* the game-progress working buffer at `this+0x16A94`.
This differs in genuine memory direction from the independently exact
accepted F274 store; neither function inherits credit for the other's
code or for the CRT itself. The private complete game-progress class
remains unasserted.

The natural source `src/ProfileSelectionLoadWorkingF403.cpp`, with only
borrowed signed owner-field expressions, matches the complete target
**81/81 original nonrelocation bytes** and its single physical original
COFF REL32 call to `memcpy` at `00640F20`. Original 85-byte CODE extent
and entire RET 4 are checked, no masking/truncation. The VC7.1
`/Od /Ob0 /Gy /GR- /GX- /Zi` affected-only
`--unit profile-selection-load-working-eight-00416e80` cold replay
returned **1/1 exact**. No extra record allocation, callee/CRT bytes,
fake slots/locals, assembly, full cold replay or external Oracle claim.


## F407: complete 3,232-byte battle LoadCharacters core with 11 native fighter allocations, real story RNG and both jump tables

The R065-authored original `BattleLoader::LoadCharactersAt004176F0`
at `004176F0..0041838F` is now complete **3,232 original native
CODE bytes / 678 decoded original x86 instructions**, original PE SHA256
`6acdbe6fd9efb49eaeb8a42bd7586d00648753d39894e6317a002105ddf1507a`.
After the real `RET` lie **64 bytes of separately owned switch-table DATA**:
the first 11 physical DWORDs dispatch the selected fighter type
0..10, the second 5 DWORDs select the current fighter difficulty 0..4.
Canonical unit `size = 3232, compare_size = 3296` compares every one of
those after-RET data fields but credits **only** 3,232 original CODE bytes.

The complete native game story and battle controller handles the real
replay-mode loader, sequential unique roster selection in story mode using
`_rand` and a 6-character used-bit mask, explicit C++ signed mode and
selector bytes, stage character and special-variant selection, and 11
separate original fighter allocations. Genuine `operator new` physical
footprint sizes are `0x1000`, `0x1830`, `0xFEC`, `0xFEC`, `0xFE8`, `0xFF8`,
`0xFE4`, `0xFE8`, `0x1008`, `0x1000`, and `0x1000`, each calling its own
original fighter constructor (without re-crediting any of those callee
bodies). The native virtual fighter *scalar deleting destructor* lives at
original vtable +0x14, followed by resource/motion initialization methods
at `00456B60`/`00457490`, actual two-side enemy/facing state, real
per-player difficulty and skin effects, mode-dependent fighter virtual
special selection and action initialization, linkage to the opponent,
camera attachment, persistent story score/round/rank controller records,
and final FX-queue clear and battle logging. All branches, including
replay-only score assignments and nonstory HP state reset, are reproduced.
Original complete private fighter class/size/ownership is **not** asserted:
source only contains observed opaque `new` byte-footprint carriers and
borrowed method declarations to reproduce native call ABIs.

The first whole semantic C++ probe already produced genuine VC7.1 `/GX`
exception-frame code and all game-specific calls but had the wrong stack
slots, virtual-deletion implementation, and random story bonus ordering.
The original uses `delete fighter` through a true virtual deleting
destructor at +0x14; expressing the legitimate C++ `delete` (not a manual
`ReleaseOwned(1)` substitute) restored both checked pointer stores and
original EH transitions. The story bonus is an inline source Boolean
`(rand()<0x4000 || firstFighter==6) ? 1 : 0` multiplied by ten; VC7.1
genuinely materializes an original 32-bit Boolean temporary at EBP-0x88.
The true story counter at global `006714C0` is **16 bit**, and the
original `(!g_StoryFlagsAt006714D0)` calculation must first retain its
32-bit intermediate, not lower an 8-bit `SBB/INC` directly.

The last full-extent probe was only **six nonrelocation bytes away**.
Those came from two *real* used, contiguous story-accumulator fields:
`seen` bit mask at EBP-0x10 and successful selection `count` at
EBP-0x14. Natural struct `SelectionTrackerF408 {int count; unsigned int
seen;}` places the count lower and seen higher; initializing seen
before count preserves the original initialization instruction order.
That restores **all 2360/2360** original nonrelocation bytes across the
whole original **3,296-byte** CODE+DATA comparison extent. All **234**
genuine original physical COFF fields/destinations were individually
reviewed: **218** within native CODE, **16** original owned post-RET
table references, including **18** real nonzero `+4` symbol addends for
references to original second fighter pointer global `0067141C`. The
checks use native field bytes and the actual relocation addend, not just
base symbol names; those are correctly represented in the manifest through
unchanged COFF object addends.

Pinned VC7.1 `/Od /Ob0 /Gy /GR- /GX /GS /Zi` cold replay of only the
affected unit `battle-loader-load-characters-004176f0` returned **1/1
exact**. No borrowed fighter constructor, game/CRT callee or vtable
code, no 64 DATA bytes, and no compiler EH helper code earns duplicate
CODE credit. No fake locals/padding, target-byte copying, raw assembly,
masked relocations, cropped function, full cold replay or external Oracle
acceptance claim. The old F398-F402 mismatches remain private negative
controls, not accepted alternate functions.


## F414: full original 132-byte static replay queue constructor and four native C++ member lifetimes

The independently R177-reviewed original authored constructor at
`00413650..004136D3` is **132 complete native CODE bytes** and
**33 native x86 instructions**, original PE SHA256
`d2429a68b58c626c9ef3fff2539dadcabe761aee24f8cc3b66dc96ed9b331b25`.
The native method constructs four genuine 20-byte replay queue views
at `this+0x154`, `+0x168`, `+0x17C`, `+0x190`, calling
`00414360`, `00414550`, `00414360`, `00414740` respectively; after
those source-order constructions it zeros the actual root handle DWORD at
`this+0x0`. Genuine VC7.1 `/GX` C++ constructor EH states 0/1/2 and
handler `006550EA` are compiler-generated naturally from the real four
member constructor/destructor declarations, not hand-inserted SEH bytes.
Only physical 20-byte member extents and the overall borrowed prefix
allocation placement are modeled; their hidden queue fields and exact
original private owner class are not asserted.

`src/StaticReplayQueueCtorF414.cpp` under VC7.1 `/Od /Ob0 /Gy /GR- /GX
/GS /Zi` matches all **100/100 native nonrelocation bytes** and
all **8 authentic COFF physical relocations**, including four native
real queue constructors, two exception-list slots, original EH handler
and final restore. Affected-only
`--unit static-resource-queues-initialize-handle-00413650` replay was
**1/1 exact**. The live dirty worktree also exposed a second unit name
for the **same original address, source, mangled symbol and identical 8
relocations**. Both were inspected and the redundant alias reconciled into
a single canonical accepted unit; no duplicate original 132-byte credit
and all actual source/evidence remained intact. No CRT/queue callee CODE
credit, fake alignment locals, raw bytes, manual assembly or full replay.

## F415: complete native notice byte-state setter and fighter notice renderer pair

Two independent, previously unclassified, game-specific originals are
`FighterState::SetNoticeFieldsAt0045CD70`: **75 complete native bytes**,
**24 original instructions**, PE SHA256
`23ab2cd62ba92da2751e03dd49870c08865e466a8201535bdca65ebf934b4ee3`,
and `FighterState::RenderNoticeAt0045D5D0`: **113 complete native CODE
bytes**, **43 original instructions**, PE SHA256
`2060c9380d73c4760fd35727e78904580ae461559d482c794c9b0553fc9e573e`.
The first only updates native state byte at fighter +0x6E7 when the
signed notice argument is nonnegative and no greater than original
+0x532; the original two color/flag bytes +0x6E8/+0x6E9 are written
**unconditionally**, not incorrectly hidden behind this same guard. It
has **zero genuine native COFF relocations**, explicitly declared
`relocations=[]`, and matches **75/75 native machine-code bytes**.
The renderer tests original signed global byte `0067161E` for fewer than
eight characters, selecting genuine depth **24** or **16** and calling
real borrowed notice renderer at `0067143C`, through `00413460`, with
actual unsigned-byte RGB, step and highlighted parameters. The true
VC7.1 unsigned-byte argument ABI is needed for the complete
**93/93 nonrelocation bytes** and **5/5 native physical COFF fields**
over its entire 113-byte CODE span. The two methods are naturally
compiled in `src/FighterNoticeSetDrawF415.cpp` under pinned VC7.1
`/Od /Ob0 /Gy /GR- /GX- /Zi`; affected-only cold replay yielded
**2/2 exact across one object**. Original fighter private layouts
and renderer implementation remain borrowed, not source-defined or
credited. Neither function used fake locals, ASM, patched byte arrays,
masked/cropped comparisons or a full-project cold replay.


## F421: complete 1,926-byte fighter script/action boss with true 15-byte command remap data

R065-authored original `FighterState::ProcessActionAt0045CE10` occupies
**1,926 complete native CODE bytes** at `0045CE10..0045D595`, with **491
original x86 instructions** and PE SHA256
`467e3f11c8654967f96ffc628ef2001207aa11c13db8226cc08226946f8865e6`.
A native post-RET 36-byte switch table (9 absolute case targets) followed
by the actual 15-byte case-remap table for command kinds 0..14 occupy
`0045D596..0045D5C8`. The canonical matching unit has `size=1926` and
`compare_size=1977`, compares all 51 original DATA bytes but does not
credit any post-RET data as authored CODE. The original complete private
FighterState type, script-container layout, and method names remain
provisional; the source declares only borrowed observed field/call ABIs.

The real method first validates current script index `+0x6F4` against
original script count at `0045DD00` and clears genuine previous index/bit
globals `0066C24F/0066C24E` at the EOF/end states. Changed script
state invokes native byte accessor `00420530` and the genuine 9-branch
switch whose cases include first player's and opponent's notice transitions,
actual game text drawing via the now separately exact F415 notice callee
`0045D5D0`, native byte/word/DWORD script reads `00420570/004205B0`,
scene selection calls `00419CB0/00419DF0`, and actual native event mask
state at +0x6F2. The mode-14 case processes the first set event bit via
real signed-char mask shifts, and the active-input path implements the
native `this+0x4E4`/global `00671632` gate, actual remaining bit masks,
index advance, and same full EOF clearing. Opponent notices are borrowed
through the actual pointer at +0x2E8; no external script reader, renderer,
CRT, target game method or other CODE is double counted.

The first independent whole semantic C++ attempts were 2,072+ bytes with
invalid guesses about the borrowed notice ABI, a redundant switch-bound
local, and incorrect 32-bit notice arguments. Reusing the separately
independently verified F415 actual `SetNoticeFields(signed char,uchar,uchar)`
and `RenderNotice(void*,uchar,uchar,uchar,uchar)` caller ABIs removes
spurious sign-/zero-extensions. The real switch expression is direct, not
a synthesized named int, and original source loop orientation places
`if(BITMASK>0)` first for case 14 and `if(command>=10)` before active
keyboard handling. Genuine source `while` loops update the script step,
byte mask and byte count in the original arithmetic/shift sequence.
These changes recovered the complete **1,926 CODE plus 51 DATA** physical
comparison length and exact 491 native instruction shape.

The last subtle discrepancy was physical stack allocation: native original
signed one-byte mask, bit and count at EBP-1/-2/-3 precede the saved
receiver at EBP-8 and native action kind at EBP-C; the five independent
notice-highlighting byte temporaries occupy EBP-D..-11 *after* those slots.
Declaring explicit highlighted byte locals causes VC7.1 to allocate those
five variables *before* the receiver and switch kind, producing hundreds
of wrong stack bytes despite correct semantics. Expressing each genuine
highlight Boolean directly in its original notice rendering call as
`static_cast<unsigned char>(lastBit!=step && lastIndex==index)` naturally
materializes the **five native compiler-generated byte temporaries in
their original positions**. The three actually used signed mask, number
and bit locals remain natural source variables. This produces **all
1721/1721 original nonrelocation bytes** across the full 1,977 original
bytes, with **64/64 authentic physical COFF relocations**, including all
9 original native switch table addresses and the exact original symbolic
addends and destinations. Pinned VC7.1 `/Od /Ob0 /Gy /GR- /GX- /Zi`
rebuild/replay of only `fighter-state-process-action-0045ce10` returned
**1/1 cold exact**. No fake stack locals, assembly, pasted target bytes,
masked fields, cropped function, full repository cold replay or external
Oracle acceptance. F410-F420 alternative complete probes are retained
as negative research controls under private `.analysis`.


## F422: 11 complete R050 character auxiliary object native derived constructors

Every original character has a distinct whole authored C++ object constructor
which invokes the same already-borrowed native base constructor `0045B760`
but installs **its own** original vtable and clears physical character-
specific state. All eleven independent PE function boundaries, sizes,
call references, original vtable addresses, instruction sequences and
original PE SHA256 bodies were separately checked before source adoption.
Reimu at `004769B0` and Meiling at `005EB490` each have **134 complete
original CODE bytes / 33 x86 instructions**; the other nine constructors,
Marisa `0049C850`, Sakuya `004CA640`, Alice `004EBD00`, Patchouli
`0050A4E0`, Youmu `00536360`, Remilia `0055ABE0`, Yuyuko `0057D4E0`,
Yukari `005A1560` and Suika `005C9C20`, each have **146 original CODE
bytes / 35 native instructions**. Their physical vtables, respectively,
are `00659210`, `006593D4`, `006595B8`, `0065970C`, `00659870`,
`006599D4`, `00659B34`, `00659C88`, `00659DDC`, `00659F14`,
and `0065A04C`, each read from and verified against its distinct original
PE target at its real physical relocation field.

All eleven native functions copy the actually observed parent receiver
pointer to `this+0xE4`, parent DWORD at +4 to `this+4`, and point their
local +0xC4 to actual `parent+0x468`. They then clear exactly the five
original short values at `this+0xD8/+0xDA/+0xDC/+0xDE/+0xE0`. The nine
146-byte constructors genuinely also clear a sixth short at +0xE2; Reimu
and Meiling **do not**, explaining the original exact 12-byte difference.
The explicit per-character C++ source under
`src/CharacterObjectConstructorsF422.cpp` expresses true derived
construction and actual source field expressions while declaring only the
borrowed base constructor and virtual destructor ABI. It does **not** claim
a complete private character object allocation or member layout, nor does
it reconstruct/re-credit any executable bytes belonging to the actual base
constructor.

A fresh original-source-level probe for both native length variants matched
all nonrelocation bytes on the first attempt, so a separate single compiler
object was generated containing all eleven distinct natural constructors.
Pinned VC7.1 `/Od /Ob0 /Gy /GR- /GX- /Zi` generates each function's own
original virtual table relocation and borrowed base ctor call. All eleven
whole-native comparisons then returned **126/126 or 138/138 original
nonrelocation bytes**, with **2/2 true original physical COFF DIR32/REL32
references** and independently verified native destinations. Local cold
replay targeted **only** the eleven new unit names, returning **11/11
exact across 1 compiled object**, crediting exactly **2 × 134 + 9 × 146
= 1,582** originally authored distinct CODE bytes. No base-class callee
credit, fake byte padding/ASM, target code bytes embedded in source,
masked relocations, truncated comparison, full cold replay or external
Oracle acceptance.


## F427: full R177 161-byte static queue reverse destructor and CloseHandle policy

The original static replay/resource queue aggregate destructor at
`004136E0..00413780` is **161 complete original native CODE bytes**,
**42 native x86 instructions**, original target PE SHA256
`af821e67477e837a51bf52b014b54aee9703cd9214fcfd467aee0a716a4c6682`.
Its source-correct behavior first invokes real aggregate-owned cleanup
`00413880`, then checks its true handle at receiver +0 and calls original
imported Win32 `CloseHandle` at physical IAT `00657138`, clearing the
handle. The remaining four 20-byte aggregate members are destroyed in the
genuine reverse C++ order: +0x190 dword queue destructor `00414790`,
+0x17C byte queue `004143B0`, +0x168 word queue `004145A0`, and +0x154
byte queue `004143B0`. The whole native VC7.1 `/GX` exception handling
frame and original state transitions 3,2,1,0,-1 are compiler-produced
from an actual C++ derived aggregate destructor. That source-side receiver
interface is only a borrowed offset/size container, **not** a claim to
the actual private aggregate class layout or queue implementations.

A new original-source-level destructor in
`src/StaticResourceQueuesDtorF427.cpp` naturally reproduces the full code,
provided it accesses `*reinterpret_cast<HANDLE*>(this)` directly. A
seemingly harmless local `HANDLE& handle` introduced an unnecessary pointer
local, increased the native frame and changed the function to 169 bytes;
this nonmatching version is retained privately as a negative control.
All complete **121/121** nonrelocation bytes and **10/10** genuine original
physical DIR32/REL32 relocations match, including original EH handler,
three `__except_list` references, four native member-destruction calls,
the real cleanup callee and physical CloseHandle import. Only the
`static-resource-queues-release-close-handle-004136e0` unit was rebuilt
and cold replayed, **1/1 exact**. The neighboring accepted F414 132-byte
constructor remains separate native CODE credit, whereas its member
constructors/destructors and Win32 callee code are not double counted.
No masking, assembler/target-byte graft, fake pad/local, cropped native
extent, full-project cold replay or external Oracle acceptance.


## F428: native 129-byte GDI/CRT raster bitmap and device-context release

The independently authored R178 original
`RasterResources::ReleaseAndResetAt0041BFD0` at `0041BFD0..0041C050`
consists of **129 native original CODE bytes / 41 x86 instructions**,
original PE SHA256
`e69251b4328d2108f697aa3bcddbd27a7632620782abbe136a7dd7d73461968d`.
It conditionally frees a real pointer at owner +0x14 using the original
borrowed CRT `_free` at `00640F15` and a *genuine* local freed pointer
at EBP-4, then sets +0x14 to zero. It calls native GDI `SelectObject`
on the original owner HDC at +4 and saved GDI selection at +0xC, passes
its actual return to `DeleteObject`, and invokes `ReleaseDC` for the
original HWND +0 and HDC +4. The three imported Win32 functions are
identified by their actual original IAT relocations `00657048`,
`0065704C`, `00657214`. Finally it clears the genuinely written +8,
+0xC and +4 resource fields. The complete owner allocation and other
private raster class attributes are not inferred.

Natural source `src/RasterResourcesReleaseF428.cpp` with the borrowed
correct Win32 handles, owner fields and real used buffer pointer matches
the **entire original 129-byte CODE body**, **113/113 nonrelocation
bytes** and all **4/4 genuine original COFF REL32/DIR32 physical
references and exact native destinations**. Pinned VC7.1
`/Od /Ob0 /Gy /GR- /GX- /Zi` affected-only cold replay of
`raster-resources-release-reset-0041bfd0` returned **1/1 exact**. This
credits 129 authored CODE bytes, no additional Win32, GDI or CRT callee
bytes. No fake local/ABI, raw native byte graft, manual assembler,
masked fields, cropped function, all-unit cold replay or external Oracle
acceptance.


## F429: complete 146-byte native camera snap with real two-mode global positions

The R035-authored original `CameraMotion::SnapAt00412CF0` occupies
`00412CF0..00412D81`, **146 complete native CODE bytes / 30 x86
instructions**, SHA256
`e08b5cc06d6429ce014407d34d97c3bd4a0014c880bda3157df532f1481e46d4`.
The actual camera selector byte at global `00671414` chooses which of the
two separately stored original camera positions to snap into the real
active camera globals: current X/Y/Z at `006713E8/006713BC/006713F4`
or alternate at `006713F0/00671400/006713C0`. The source writes active
X `00671404`, active Y `006713C4` with the true original float offset
constant at `0065784C`, mirror initial X/Y at `006713E4/00671408`, and
active Z at `006713DC`. Exact native DWORD copies stay DWORD copies.
A complete natural C++ with physically observed global types under pinned
VC7.1 `/Od /Ob0 /Gy /GR- /GX- /Zi` emitted the full original extent
on its initial probe: **54/54 comparable bytes** and all **23/23 genuine
physical COFF DIR32 references/destinations** matched. Only the F429
unit was cold replayed, **1/1 exact**. No complete camera class assumption,
borrowed callee CODE, padding, assembly, byte-mask or Oracle claim.

## F430: complete 130-byte fighter script initialization with genuine 1000 signed index slots

R076 original `FighterScript::InitializeAt00420440` is **130 complete
native CODE bytes / 34 original x86 instructions**, physical SHA256
`42ef4e8e415d46a938315badeba79f0a940203ed5261bcf52403554f897ade2e`.
The actual C++-constructed script-entry container starts at `this+0x7D0`,
after precisely **1,000 actual signed 16-bit per-pattern indices** at
`this+0..0x7CF`. Native code invokes real container constructor at
`004214E0`, clears it through native `004216D0`, then loops over all
1,000 slots and stores signed short -1, preserving native `for` loop
branch ordering. Real VC7.1 `/GX` exception handler at `0065554E`,
SEH registration and teardown, and correct compiler-managed destructor
state are generated by a natural member constructor and member with a
borrowed destructor ABI. The class's complete private script entry
container representation is **not** asserted beyond observed placement.
Source `src/FighterScriptInitializeF430.cpp` under pinned `/GX /GS`
VC7.1 emits full 130 original bytes, matches **106/106 nonrelocation
bytes** and all **6/6 genuine original COFF physical EH/container
references and solved destinations**. Only the affected F430 unit was
independently cold-replayed, **1/1 exact**, in a two-unit F429/F430 call.
Borrowed container ctor/clear/dtor code and compiler/EH helper bytes are
not credited. No assembly, arbitrary pad, truncated function, masks,
full cold replay or external Oracle acceptance claim.


## F431: complete 142-byte static battle effects resource array constructor

Original R178-authored `StaticBattleResources::ConstructAndClearContainersAt005F6F60`
occupies **142 complete native CODE bytes, 40 original x86 instructions**,
original PE SHA256
`e97540483ba2b0cb9683de4c1fb1d218a9abb670cf72cd86c9e46ee1e0130552`.
The source has two actually constructed borrowed 20-byte effect lists at
`this+0x00/+0x14`; they are a true C++ array, so pinned VC7.1 `/GX`
compiler emits the original `_ehvec_ctor` helper at `00641C78` with
original list ctor `005F8040`, destructor `005F8090`, and native
exception-frame registration and cleanup. The real graphics/texture owner
at `this+0x28` occupies its 80-byte observed native constructor extent
(`0040AD80`), and the separate native auxiliary owner at +0x78 invokes
`005F82F0`. The constructor body genuinely clears both lists through
`005F82D0` and resets the +0x78 auxiliary through `005F83E0`. These are
borrowed actual source-call and member-footprint interfaces, not claims
of complete original private type layouts.

A fresh independent natural C++ constructor
`src/StaticBattleResourcesConstructF431.cpp` compiled to **all 142 native
CODE bytes on its first probe**, with **94/94** matching nonrelocation
bytes and all **12/12 genuine original COFF DIR32/REL32 field types,
positions, symbol references and PE destinations** (including native
EH handler `00656629`). Only changed unit
`static-battle-resources-construct-and-clear-005f6f60` was cold rebuilt,
**1/1 exact**. No borrowed array-iterator/compiler, graphics, list or
texture external callee code is double counted; no fake unused locals,
assembly/byte grafts, cropped original, full cold replay or external
Oracle receipt.


## F432: complete 154-byte native options-scene virtual resource destructor

Original R235-authored `OptionsScene::ReleaseSceneTextureAndResourceAt00428E60`
at `00428E60..00428EF9` is **154 complete native CODE bytes, 46 original
x86 instructions**, PE SHA256
`04dc13582724d517c476050e7a6137a9e686f0f7cb2f518c1fc80e9af66d3947`.
A real C++ derived-scene virtual destructor installs native options
virtual table `00657F38`, conditionally `delete`s the resource at
physical owner `this+8` through the original texture deleting-destructor
entry `00425460` (with actual C++ pointer temporaries), and conditionally
releases the D3D8 texture at `this+0xC` through actual COM vtable slot +8.
It then invokes the genuine base-scene virtual destructor `00431F40`.
The VC7.1 `/GX` EH frame, native SEH handler `006558A5`, reset of EH
state, and all conditional branches result from natural C++ inheritance
and `delete`, not copied machine code. Only the real observed 8-byte
scene-base ABI and actual +8/+C resources are represented, **not** a
complete private OptionsScene layout or external D3D/scene implementation.

`src/OptionsSceneReleaseF432.cpp` matches the entire original body
**126/126 nonrelocation bytes** and all **7/7 original physical COFF
DIR32/REL32 relocations**, including true vtable, EH/SEH, original
texture deleter and base destructor references. Pinned VC7.1
`/Od /Ob0 /Gy /GR- /GX /GS /Zi` affected-only cold replay of
`options-scene-release-texture-resource-00428e60` returned **1/1 exact**.
No imported D3D resources, texture/scene callee CODE, fake local padding,
masked/cropped comparison, assembly, byte grafts, full replay or remote
Oracle acceptance credited.


## F435: complete 260-byte native NameEntry scene and replay archive constructor

R109-authored original `NameEntryScene::InitializeAt0042B1F0` occupies
**260 original authored CODE bytes / 71 native x86 instructions** at
`0042B1F0..0042B2F3`, native PE SHA256
`0e8571ffc4d9d443fe4dee4449d9640c406dc8b8b8aa097dcf0a697c52c71877`.
A true derived scene C++ constructor invokes native base `004251C0`,
installs its original vtable at `00657FAC`, creates an actual 80-byte
resource manager (`operator new` at `0064159D`, manager ctor `0040AD80`)
and allocates 3 archive slots via `0040B1D0`. Original `0040BB80` archive
load reads the physical path `data\system\replay.dat` from `00657F84`
and root `datab` from `00657F7C` (independently verified original bytes).
The source initializes all four genuine short scene selection states at
+0xE/+0x10/+0x12/+0x14 to zero, derives its +0xC byte from signed global
`006714CE`, and stores the original returned selection reader object from
`00414300`, receiver global `00671750` with output +0x1C, at +0x18.
The original VC7.1 `/GX` SEH handler, transaction states and all return
paths are compiler produced, not pasted.

Natural `src/NameEntrySceneInitializeF435.cpp` reproduces the *whole*
original **260-byte CODE extent, 200/200 nonrelocation bytes and all
15/15 genuine native COFF relocation fields/destinations**, including
original handler `00655913`, scene vtable, exact archive strings and
all native callees. Pinned VC7.1 `/Od /Ob0 /Gy /GR- /GX /GS /Zi` cold
replay targeted only the affected
`name-entry-scene-initialize-0042b1f0` unit and returned **1/1 exact**.
The complete unknown original private class members, external scene
constructor, texture manager, archive and selection callee CODE remain
borrowed and uncredited. No fake padding, ASM, raw original bytes,
masked/cropped comparison, full cold replay or Oracle receipt.
