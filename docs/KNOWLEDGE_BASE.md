# TH075 reconstruction knowledge base — cumulative historical evidence

**Current status annotation: 2026-10-29, after F652 and the compact
handoff/storage audit.** This is a **chronological experiment log**,
not the live backlog. Consult the [current agent handoff](RE_HANDOFF.md)
and live function/origin/match manifests first. Earlier F-series
sections describe *historical* status; older claims such as "still pending",
"nonexact", or "no credit" are **not active status** after a later exact
adoption. Earlier original 33K giant experiments such as F593
show **historical** 155-byte source differences, superseded by F596
**137 nonrelocation bytes**; all 8,789 original x86 instruction
mnemonics are now in their exact machine ordinal positions.
The former 1,500-line post-F596 active handoff is preserved in the
**frozen [F598–F652 chronology](history/RE_HANDOFF_F598_THROUGH_F652_2026-10-29.md)**;
older F540–F596 notes remain in
[prior historical chronology](history/RE_HANDOFF_F540_THROUGH_F596.md).
The [active handoff](RE_HANDOFF.md) now fits a short task-oriented
checklist. SHA256-verifiable recovered archives of redundant historical
CI/diagnostic logs and old repeated JSON snapshots are documented in
[storage protection](STORAGE_HYGIENE.md); no original PE, Ghidra,
compiler environment, source, COFF or best negative experiment was lost.
Canonical live ledgers and actual native PE outrank all historical prose.

## Current authoritative status and superseded negatives

- **943 cold-exact source-present functions**, **862,726 original authored
  CODE bytes**, **43.71% reviewed authored coverage** and **43.64%
  conservative coverage**. **Only 25 `owner=authored,status=unclassified`
  function rows currently remain:** 22 giant fighter action/advance bosses
  totalling 1,102,055 original CODE bytes, WinMain (2,987), SceneObject
  destructor (248), and ArchiveCatalog nonvirtual destructor (171).
  All remain nonexact. 95 separate origin-pending candidate rows / 3,420
  bytes are not automatically credited. These figures are a snapshot;
  refresh with `scripts/repo-python scripts/report-reconstruction-status.py --summary`.
- The historical **F339-era snapshot was 645 exact /813,859 bytes /
  41.24%**, not the current result. Do not carry these values forward.
- A **746-byte SpriteSequence render** is already exact (F347), as are
  **874-byte Suika special** (F348), **276-byte two-list effect prune**
  (F354), **497-byte character cancel animation** (F346), and the
  **1,268-byte mirrored sprite renderer** (F437). Earlier statements
  claiming these are "truly nonexact" were superseded by complete
  native cold-exact C++ adoptions. Likewise, F504 StaffRoll (208), F514
  Replay filename (303), F516 two rank labels (169 each) and F535 progress
  postfix increment (92) are **not pending**. See current handoff §3.
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
- All 95 origin-pending functions / 3,420 bytes remain outside authored accepted CODE until independently reviewed.
  Do **not** infer full source class definitions from borrowed native
  call boundaries, or count Win32/CRT/VC7 helper code. Cold-replay
  **only new or affected units**, never the entire set.

**Latest F652 giant work is still an internal-case study, not whole
function acceptance:** F598–F652 source-backed **572 native original
inner case bodies /154,461 native internal CODE bytes**, all uncredited
as whole functions. F651/F652 recover strict original D1/D2 in giant
`00543210` (133 x86 /450 B/18 typed fields) while previous CF/D0
remain strict in that *same* newly compiled parent. The original
0xCC case in `005AEEC0` and `00564BE0` has complete 128/126 x86
mnemonic/width geometry, **but 80/78 native non-field GPR/CFG role
mismatches**, and is expressly **NONEXACT**. Recent small whole-function
source-backed origin-unknown cohort totals 39/889 B, plus distinct
F595 40 B, **40/929 B uncredited**. None of these local probes adds
to the formal 943 whole authored accepted functions.

## How to read the historical sections

The older "Current validation policy", "authoritative state" and old
handoff snapshots (e.g. **534 exact / 766,591 bytes**) were milestones,
not the current result. Their historical text remains accessible in Git
history, including `git show 26ac6fd:docs/KNOWLEDGE_BASE.md`.
Consult the accepted unit's `config/match-units.toml` entry and the
single-unit cold logs, or inspect the pinned native PE, to settle any
historical contradiction. Do not repeat a prior negative source-variable
sweep without a new hypothesis supported by original physical slots.

## Older reproducible observations — HISTORICAL chronology

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

### F323 historical Replay filename negative; subsequently resolved by F514 exact

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


## F437: full 1,268-byte mirrored sprite-node rendering boss, real 140-byte stack quad carriers and x87 FSUBR

The long-unaccepted R035-authored original
`SpriteScene::RenderMirroredNode` at `00410A00..00410EF3` is now **1,268
complete original authored CODE bytes / 324 native x86 instructions**,
original PE SHA256
`ef138dbc6864e3a1803c2d1828b83c73e3c6feb8c4a27fc2e7d6ad0fedb2edf2`.
It implements the entire game-specific mirrored sprite rendering path:
actual camera X/Y origins, native camera offset constants, borrowed native
texture rectangle lookup, whole constructed quad/RECT geometry, optional
node scale/rotation/pose, signed-character horizontal facing reflection,
original x87 position arithmetic, camera tint sampling, actual textured
quad combination and both conditional tinted (`0040CA20`) and ordinary
(`0040C9A0`) draw paths bracketed by original filter changes (`0040C860`).
Every branch and original return are included, without masking or
crediting any original geometry or draw callee bytes.

Earlier F254/F289/F355/F381-F383/F433-F434 C++ prototypes matched many
original instruction shapes but not the original stack or exact x87
operations. Independent original x86 disassembly proved actual native
EBP frame size **0x180**, with physical RECT at EBP-0x140, composed quad
at EBP-0x130, sampled tint at EBP-0xA4, X shift at EBP-0x98, color at
EBP-0x94, transformed quad at EBP-0x90 and Y origin at EBP-4. The two
quad *stack carrier footprints* are independently **140 bytes apart
from subsequent native frame fields**: the first 132 bytes of each are
the already established drawable SpriteQuad packet; the last eight
bytes are untyped physically allocated tail slots with no proven original
private field identities or independent code. Correctly grouping the
existing observed 132-byte quad payload with its *observed physical*
140-byte storage carrier, RECT, tint[3] and genuine camera locals
recovers every meaningful EBP address and the exact original 0x180
frame without inventing arbitrary standalone dummy stack locals.

At this stage the entire native source matched 1,268 original CODE bytes
but differed in **39 nonrelocation bytes** inside one mathematical
expression at native offset 0x379. The original evaluates the integer
`facing * nodeX`, writes its real 32-bit x87 conversion temporary at
EBP-0x180, executes `FILD`, loads the original owner address and then
executes **`FSUBR [owner+0x44]`**. The initially plausible C++ expression
`FIELD(float,0x44)-float(intFacing*intNodeX)` (parenthesized FLOAT macro)
instead generated `FLD [owner+0x44]`, integer multiply and `FISUB`.
Rather than hand-authoring x87 instructions, F437 searched **existing
independently cold-exact game renderers** for original native
`FILD; MOV; FSUBR` sequences and found the identical case in accepted
SpriteNode F129 (`00410350`) and FighterRender F126 (`00453F70`).
Their natural unparenthesized float dereference macro is exactly the
missing source-level evaluation distinction. Writing
`FLOAT(0x44)-FIELD(signed char,0x66)*NODE(short,0)` with
`#define FLOAT(off) *reinterpret_cast<float*>(RAW+(off))` (without
extra parentheses around the lvalue) causes pinned VC7.1 to emit the
original `FILD; MOV; FSUBR`, removing all 39 differing bytes, while
C++ results and the rest of the source remain meaningful. A
parenthesized variant remains a negative codegen control.

The complete `src/SpriteMirroredNodeRenderF437.cpp` under pinned VC7.1
`/Od /Ob0 /Gy /GR- /GX- /GS /Zi` matches the full original **1,268 CODE
bytes**, **1164/1164 actual nonrelocation bytes**, and all **26 genuine
native physical COFF DIR32/REL32 relocation fields, targets and original
addends**. This includes both native quad constructors at `0040D990`,
original ScaleQuad/RotateQuad/TranslateQuad references, camera, sprite
filter and both draw methods. Only affected new unit
`sprite-scene-render-mirrored-node-00410a00` was compiled and cold
replayed, **1/1 exact**. The private full scene/sprite types, untyped
quad trailing bytes and callee implementations remain unproved; no
helper/CRT data/CODE double credit, asm or native byte grafts, fabricated
unused local temporaries, masks, cropped extent, full cold replay or
external Oracle acceptance. All historical probes are retained as
private falsifiable controls, not duplicate accepted functions.


## F440: complete 1,291-byte Marisa nested 8×36 projectile chain renderer, 136-byte quad carrier and original x87 Z evaluation

The long-open original R049-authored
`CharacterAux::RunAt00497070`, at `00497070..0049757A`, is **1,291
original authored CODE bytes / 273 original native x86 instructions**,
independently SHA256-verified against the pinned Japanese PE as
`317471d44dd19b5a4aadd99760da7725ef1c549429b3109b7d9e979e57222acf`.
It is a whole specialized Marisa fighter projectile/particle renderer,
not a small borrowed wrapper. When native owner +0x1006 permits drawing,
it establishes the real camera X/Y frame, enables the original texture
blend mode through `0040C7F0`, then loops original i=1..8, each
constructing true signed 16-bit phase A/B, angle and radius states.
The nested original 36-element j loop calculates four physical cosine
and sine coordinates via authentic `0040D900/0040D940` calls, builds
an observed 132-byte SpriteQuad drawable payload, rotates the packet
through real `004116F0`, translates it twice via native `00411500`, and
updates each 28-byte chain particle at `this+0x1018`, including the final
73rd/74th repeated endpoints. Every outer iteration draws 0x4A native
chain elements with original texture ID 0x277 via `0040C970`. The entire
original execution flow, loops, x87 arithmetic, and true float constant
references are reproduced naturally, without copying native instructions
or giving any trig/geometry/texture callee CODE additional credit.

Historical negative F356/F358/F360/F361/F362/F363/F388 sources matched
similar control/float shapes but had an incorrect native `0xE0` stack
frame, dozens of original EBP-slot mismatches, and one real x87
operation-order discrepancy. Re-examining the exact native frame proved
`sub esp,0xE8`, `this` at EBP-0xAC, native outer i at -0xA4, inner
j at -0xA8, phaseA short at -0xA0, camera X shift at -0x9C, and a single
quad carrier at EBP-0x98. The physically allocated quad carrier here is
**136 bytes**, of which **132** bytes are independently decoded as the
real rendered SpriteQuad; the remaining four bytes have *no proven
original private field identities* and are not used or credited as
additional native CODE. This is distinct from the **140-byte** observed
carrier in separately F437-accepted mirrored-node renderer. Compiling
a source with the correctly observed 136-byte carrier recovers the
original 0xE8 stack frame and **1157/1167** nonrelocation bytes.

The real `short radius` is stored in a *4-byte aligned native stack
slot* EBP-4; a natural `__declspec(align(4)) short radius` (not a dummy
local) recovers all five native radius operand displacements, giving
**1162/1167** matching nonfields. The last five differing bytes lie
at original Z/depth calculation around offset 0x1F9. The original
actually loads float `g_MarisaParticleDepthAt006582E0`, multiplies by
actor `this+0x1010`, then divides by native float divisor at
`00657480`. A parenthesized C++ field macro at the actor operand
reorders `FLD`/`FMUL` and was a falsifiable natural negative. Reusing
the separately proven direct unparenthesized float dereference expression
`#define FLOAT(o) *reinterpret_cast<float*>(RAW+(o))` gives the native
`FLD globalDepth; FMUL [owner+0x1010]; FDIV globalDivisor` and removes
all five remaining differences, without changing any data field or
introducing inert locals, padding, asm or target bytes.

`src/MarisaProjectileChainRenderF440.cpp` compiles under pinned VC7.1
`/Od /Ob0 /Gy /GR- /GX- /GS /Zi` to the **complete 1,291 native CODE
bytes** with **1167/1167 original nonrelocation bytes** and **all 31/31
genuine original physical COFF DIR32/REL32 relocations and exact target
addresses**, including actual trig, quad ctor, blend/transform/texture
calls, all original x87 constant pools and native `_ftol2`. The single
affected unit `marisa-auxiliary-projectile-chain-render-00497070` was
independently rebuilt and cold replayed **1/1 exact**. The complete
private fighter/renderer/quad class identity and untyped carrier tail
remain unproved; no external callee or data double-credit, artificial
stack variable, assembler/byte graft, masks, cropped original, all-unit
replay or external Oracle receipt. All F356-F363/F388/F438-F439
negative source experiments are retained in `.analysis` rather than
deleted or re-credited.


## F445: complete native 251-byte OptionsScene constructor, option.dat and D3D canvas

The R109-authored native `OptionsScene::InitializeAt00428D60`, at
`00428D60..00428E5A`, is **251 original authored CODE bytes / 69 native
x86 instructions**, independently original PE SHA256
`6ce1aef1c6f541c98bb666165ff39521010299f29ccfa1bfe0adb40937102a25`.
The natural C++ derived OptionsScene constructor installs the actual
original vtable at `00657F38`, calling the genuine native scene-base
constructor `004251C0` with full VC7.1 `/GX` EH. Its original owner
canvas +0xC is null-initialized. It allocates the real 80-byte texture
manager with original CRT operator new `0064159D`, constructs at
`0040AD80`, allocates the actual three archive slots via `0040B1D0`,
and loads the genuine original game resource `data\system\option.dat`
from physical native constant `00657D80` under root `data` at `00657D78`
through borrowed `0040BB80`. It requests the actual 0x400×0x200 D3D8
canvas with format 0x20 through native `00401C20`, passing output owner
+0xC, sets native mode byte +0x14=5 and original short +0x10/+0x12
selections to zero, and passes the actual low byte of +0x10 to native
thiscall `00429F00`. Full original EH handler `00655893` and its
compiler-managed cleanup states are generated naturally, not grafted.

The first genuinely observed borrowed source in
`src/OptionsSceneInitializeF445.cpp` exactly reproduces **all 251 native
CODE bytes**, **195/195 original nonrelocation byte positions**, and
**14/14 genuine original COFF DIR32/REL32 field positions, ABI symbols
and native PE destinations**, independently checked before registering
the matching unit. Pinned VC7.1 `/Od /Ob0 /Gy /GR- /GX /GS /Zi` cold
replay of **only** new
`options-scene-initialize-00428d60` returned **1/1 exact**. Its
original paired resource destructor F432 is separately independently
exact; those two distinct authored code extents do not double count the
borrowed external scene, D3D, texture/archive or CRT bodies. Complete
private OptionsScene allocation/members beyond observed offsets remain
unproved. No fake locals, raw assembler, native code byte grafts,
masked/cropped comparisons, full cold replay or external Oracle receipt.


## F446: two complete original LoadingScene / LogoScene derived resource constructors

Two separately R053-authored original scene resource initialization functions
are now exact: `LoadingScene::InitializeAt004251F0`, **181 complete original
CODE bytes / 50 native x86 instructions**, PE SHA256
`fe7f071e6914846211bdcbfcc7b3adf86c49042eda3420a7b323f58624d90373`,
and `LogoScene::InitializeAt00425490`, **183 CODE bytes / 50 native
instructions**, native SHA256
`48b8b30745596c5ff11ad9ef190f01c336bf2b989add59c61201b79eae146d78`.
Both C++ derived constructors naturally call real native scene base `004251C0`,
install their own independently verified original vtables `00657BB4`
and `00657BE0`, and use genuine native VC7.1 `/GX` exception frames and
EH handlers `00655743`/`00655773`. Both allocate exactly 80 bytes
for a borrowed resource manager with native operator new `0064159D`,
construct it through native `0040AD80`, reserve **one** genuine archive
slot via `0040B1D0`, and load the correct original asset with
`0040BB80`: `data\system\load.dat` rooted at original `data`
(`00657B9C/00657B94`) for LoadingScene, and
`data\system\logo.dat` from original `00657BC8/00657BC0`
for LogoScene. The LoadingScene native constructor then clears its
physically observed **unsigned byte** state at `this+0xC`; LogoScene
instead clears a native **16-bit short** state at the same offset,
explaining the independent two-byte length difference. The complete
original private scene/texture member allocations beyond observed ABI
are not asserted or constructed.

`src/LoadingLogoSceneConstructorsF446.cpp` expresses both natural
C++ scene constructors independently under pinned VC7.1
`/Od /Ob0 /Gy /GR- /GX /GS /Zi`. They match **133/133** and
**135/135** original nonrelocation bytes respectively, with
**12/12 genuine original physical COFF DIR32/REL32 relocations** and
correct native destinations for each. Only the two new affected units
`loading-scene-initialize-004251f0` and
`logo-scene-initialize-00425490` were cold replayed, **2/2 exact
across one compiled object**, crediting exactly **364 distinct original
authored CODE bytes**. All borrowed base/texture/asset-manager and
compiler EH helper bodies earn zero extra executable credit; no fake
locals/assembly, pasted native code/data, masking/cropping, all-unit cold
replay or external Oracle certification.


## F446 addendum: both native OpeningScene and StaffRollScene resource constructors

Two additional independently R036/R043-authored complete constructors
were recovered in the live dirty worktree and retained: original
`OpeningScene::InitializeAt004275D0` has **219 original CODE bytes, 60
native x86 instructions**, SHA256
`50952c4df29abac45f1bafe3acc661aae27bc4dfeab3c518e89bf7dbdada71b1`;
original `StaffRollScene::InitializeAt00438AC0` has **224 original CODE
bytes, 61 native x86 instructions**, SHA256
`7117528bd9aa7f3ee18aefa934255aed8090603ca57c49f6851ddec786576570`.
The original OpeningScene derives from the genuine 8-byte scene base,
installs the native vtable, creates the actual 80-byte borrowed manager,
allocates **24** texture records from its physical native archive path,
sets original stage **40** via `00419CB0`, reloads stage via `00419DF0`,
then records real WinMM `timeGetTime()` and elapsed values. StaffRollScene
performs original pre-init `00407D70`, selects stage **41**, creates
its own 80-byte manager with **27** texture entries and authentic staff
asset archive, initializes both actual elapsed/time fields through WinMM,
and performs native post-init `00407CC0`. Both have complete VC7.1
`/GX` native exception handling and real per-scene vtables; only the
physically observed 8-byte base, manager footprint and actual scene
fields are represented, no full original private class identity claimed.

The original whole sources are preserved in
`src/SceneSequenceConstructorsF446.cpp` and their canonical existing
unit/ledger entries have been independently verified against the exact
original PE. OpeningScene has **16 genuine original physical COFF
relocations**, StaffRollScene **17**, all offsets/types/addends/destinations
verified; their complete native CODE and source hashes match the frozen
manifest. Both were independently retested in the **four-unit** affected
F446/F447 cold replay (**2/2 exact for these constructors**) with no
all-unit cold run or double credits for WinMM, game stage or texture
constructor callees.

## F447: complete LoadingScene / LogoScene reverse resource destructors

The independently R234-authored original
`LoadingScene::ReleaseSceneResourceAt004252B0` and
`LogoScene::ReleaseSceneResourceAt00425550` each comprise **127 complete
original authored CODE bytes / 36 native x86 instructions**. Their distinct
original PE SHA256 values are
`d1112fa51d0660735d3c6dbe922ff37e6c303ea8e4b2d0e37239df0397197d72`
and `c87eecf9afc7d38e6a0331951bd54977c082c84091d0e25c7412631d56b9c9b1`.
Each C++ virtual destructor installs its own original scene vtable
(`00657BB4` or `00657BE0`), initializes the original `/GX` exception
state and checks the actual borrowed resource-manager pointer at `this+8`.
A genuine `if(texture) delete texture` generates two physically real
compiler-owned pointer temporaries and invokes native scalar deleting
destructor `00425460` with original flag 1. The original scene-base
destructor `00431F40` executes after native EH reset, with distinct native
SEH handlers `00655755`/`00655785`. Both native entire bodies reproduce
**99/99 nonrelocation bytes** and **all seven real COFF fields/destinations**
each, with no fake temporary/padding and no borrowed texture/base callee
CODE credited. Only the four new F446/F447 units were cold rebuilt
together across two objects, returning **4/4 exact** and **254 distinct
CODE bytes** for the two destructors (plus separately 443 for Opening/Staff
constructors). No pasted code/ASM, masks/cropping, full cold replay or
external Oracle receipt.


## F448: complete original 231-byte three-texture scene-derived destructor

The independently R054-authored `SceneObject::ReleaseAt00433140` occupies
**231 complete original authored CODE bytes / 68 x86 native instructions**
at `00433140..00433226`, original native PE SHA256
`9ea0271e34091a5e5493c974540a6705048550e2985f2b0ae6ceccd1328dfcea`.
It is a real original virtual C++ derived scene destructor which assigns
its own vtable `0065824C` and conditionally deletes **three actual
texture/resource pointers** at `this+8`, `this+0x44`, `this+0x48`. Each
source-side C++ `delete` generates the genuine original two native
pointer-ownership temps, tests the correct null pointer, and calls the
original native nonvirtual scalar deleting texture dtor `00425460`.
VC7.1 naturally emits the original `/GX` EH frame and handler at
`00655ACB`, the 0x28 stack frame, three deletion-result temporaries
and final borrowed original base scene destructor `00431F40`.
The intervening `this+0xC..0x43` source carrier is *only a physically
observed layout gap* needed to express the actual later texture pointer
offsets, not a claim to the unknown original full scene private fields.

A new source-level C++ triple-texture destructor
`src/SceneTripleTextureReleaseF448.cpp` matched the complete 231-byte
original native body on its first pinned VC7.1 `/Od /Ob0 /Gy /GR- /GX
/GS /Zi` compile, with **195/195** original nonrelocation bytes and
**9/9 authentic original physical COFF references and resolved PE
destinations**, including actual native derived vtable, EH handler,
three original deleting texture callees and real scene-base dtor. Only
`--unit scene-object-triple-texture-release-00433140` was cold rebuilt
and replayed, **1/1 exact**. No texture/base/CRT CODE double credit,
unknown private layouts promoted to facts, fake locals, assembler/code
bytes copied, masked/truncated comparison, whole-repository cold replay
or external Oracle acceptance. The separately unaccepted
`SceneObject::ReleaseAt0043B0B0` (248 bytes) remains an independent
more complex scene destructor to reconstruct.


## F454: exact 239-byte original global Direct3D resource client last-owner destructor

Original R001-authored `GraphicsResourceClient::~GraphicsResourceClient`
at `00401020..0040110E` is **239 complete native authored CODE bytes
and 60 decoded original x86 instructions**, PE original SHA256
`820329e528fac0d038ac2a800f7547aecb8d1b62b377135928db6053dd1ed813`.
It decrements the actual original shared graphics client counter
`00671210`; only on the transition to zero it releases real original
Direct3D8 resources. It loops exactly one physically indexed element
through independently original global texture and surface pointer arrays
`006711D4` and `006711FC`, calls each actual COM `Release` vtable slot +8,
then sets those pointers to zero. It also releases both real global
singleton resources at `00671230` (texture) and `0067122C` (surface),
clearing their pointers in original order. No imported D3D runtime or
original SDK implementation is counted as authored CODE.

The initially natural source `src/GraphicsResourceGlobalReleaseF454.cpp`
was **236 bytes** because it simply discarded the return of the first
singleton COM `Release`. Independent PE disassembly proved that the
original **stores the actual returned ULONG refcount** in native local
EBP-8 with instruction `mov dword ptr [ebp-8],eax` at original offset
0xBA, even though this debugger-visible original returned value is not
used later in the same function. Preserving that *physically observed
original COM API result* in a legitimate C++ `ULONG remainingRefCount`
local—not inventing an inert dummy or stack pad—recovers the actual
`sub esp,0xC` frame, saved `this` at EBP-0xC and real loop index at
EBP-4 and all original instruction bytes. Full original verification
reports **167/167 nonrelocation bytes**, **18/18 authentic physical COFF
DIR32 relocations** and actual correct original global targets. Only
new unit `graphics-resource-client-release-global-00401020` was rebuilt
and cold replayed **1/1 exact**, without any byte mask, graft, raw
assembly, cropped original, additional SDK/CRT code credit or whole
repository cold replay/remote Oracle receipt. Original private owner
identity and complete D3D implementation are not asserted.


## F458: complete native 96-byte cdecl event queue unique enqueue without early break

The independently original R113-authored `EventQueue::EnqueueUniqueAt00423C80`
at `00423C80..00423CDF` is **96 complete native authored CODE bytes,
32 original x86 instructions**, PE SHA256
`db0643113e771847a47c080e65a31a14bc975429a15ee7edb92c1510b12672ce`.
Its actual ABI is a **cdecl global game queue operation**, with ordinary
`RET` and a 32-bit input event at native EBP+8, not a thiscall receiver.
It initializes native `unsigned char add=1` at original EBP-1 and loops
the genuine 32-bit index at EBP-8 through a shared queue at `0068BE44`.
The original tests every queue element using actual unsigned Size and At
methods `00423D40/00423D60`. On an already present value it sets the
original `add` flag to zero **but does not break or skip the rest of the
original scan**. Only after the full scan it conditionally calls native
PushBack `00423E10` with the address of the original event parameter.
The first plausible thiscall + early-break source incorrectly emitted
103 bytes: both purported ABI and behavior contradicted original RET
and real native `jmp loop-increment` following byte flag assignment.
Using actual cdecl and no early break in natural source
`src/EventQueueAppendUniqueF458.cpp` reproduced the **entire original
96-byte CODE body**, **72/72 genuine nonrelocation bytes** and all
**6/6 independently verified original physical COFF DIR32/REL32 fields,
types and true original PE destinations**. Affected-only
`--unit event-queue-append-unique-00423c80` cold replay gave **1/1 exact**.
The original deque/private global implementation remains borrowed and
is not double-credited. No invented locals, byte padding, source ASM,
cropped source/native extent, masks, full cold replay or remote Oracle.

## F455-F456: real full GameApplication::Run WinMain core boss reconnaissance (not accepted)

The next independently decoded R064-authored `GameApplication::RunAt00602A60`
is a much larger original **2,987 CODE-byte / 654 x86-instruction**
original WinMain-style game startup loop, PE SHA256
`780862e0f784ac2cbd16ed20eaff12c0da49a0c831ce4a9f56e85fc2edb3ffa0`.
Original full Ghidra and native listing evidence are retained in
`.analysis/f423-next-bosses/app-run.c` and trial sources in
`.analysis/f455-game-main-boss/`, `.analysis/f456-game-main-scene-temporaries/`.
The original owns a native 15-case scene selector switch table immediately
after its complete RET at `0060360B`; its native Windows-class registration,
Win32 real `GetModuleFileNameA`, `CreateWindowExA`, `GetMessageA`/
`PeekMessageA`, imported WinMM and COM lifetime, game archive state,
Direct3D/DirectInput/DirectSound setup, true native input event, scene
allocation/deletion and shutdown branches must all be preserved exactly.
Every actual 15 native scene allocation footprint/callee was identified
in the original. A full natural C++ source hypothesis under pinned VC7.1
`/Od /Ob0 /Gy /GR- /GX- /GS /Zi` compiles as **2,831 bytes / 640
instructions**, with stack frame 0x228 vs original 0x278: original
per-scene constructor result locals and early scene-pointer lifetime are
missing. A second source expressing *all 15 real used per-scene new-result
locals* compiles to **3,011 bytes / 670 instructions**, with frame 0x264.
These are genuine whole-program source semantics/control-flow probes and
strong falsifiable negative controls, but **NOT structural exact and no
CODE credit** has been assigned. Pending differences involve native
scene switch case order (real code body case 4 comes first), live early
currentScene initialization and startup window state/stack slots, plus
Win32/COM error exit CFG. No all-unit cold replay or acceptance
without original full code/data/physical COFF exactness.


## F459: complete 168-byte native 640×480 black D3D8 surface initializer

The independently original R053-authored
`GameGlobals::InitializeBlackSurfaceAt00417000` at
`00417000..004170A7` is **168 complete original authored CODE bytes and
58 native x86 instructions**, PE original SHA256
`45d9fa0cfa27b987a3f0e21fc5eb658829518e556b9d1cf16abd1f8d5568982e`.
The native code allocates a real D3D8 black texture/surface with original
borrowed game callee `00401C20`, exactly width **1024**, height **512**,
texture output at real receiver +0 and format 0x20. It locks the actual
`IDirect3DTexture8` through native COM vtable slot +0x40 with an
**eight-byte real `D3DLOCKED_RECT`** at original native EBP-8/-4,
then iterates the genuinely observed x=0..639 and y=0..479 original
nested loops and writes the native 32-bit black ARGB value `0xFF000000`
into the texture memory at DWORD offset `(y*1024+x)`. It invokes the
genuine D3D8 texture `UnlockRect` virtual method at original vtable+0x44,
clears true owner byte+4 and returns the original receiver. The actual
private full D3D8/resource owner layout is **not** inferred, and the
borrowed texture allocator and imported D3D runtime are not CODE credit.

The first natural pinned VC7.1 source
`src/GameGlobalsInitializeBlackSurfaceF459.cpp`, with original real
D3D8 COM ABI and SDK `D3DLOCKED_RECT`, emitted all **168 original bytes**
under `/Od /Ob0 /Gy /GR- /GX- /Zi`. The entire original PE-backed
function is matched **164/164 nonrelocation bytes** and its **single real
physical original COFF REL32** to `00401C20` at native offset 0x1A.
Only affected `--unit game-globals-initialize-black-surface-00417000`
was rebuilt and cold-replayed **1/1 exact**. No raw assembly/target bytes,
masking or truncation, fabricated stack locals, all-unit cold replay,
additional SDK code or external Oracle acceptance claimed.


## F460: full native 65-byte FrameCapture::CapturePrimary and its real 20-byte RECT + buffer state

The independently R100-authored original native
`FrameCapture::CapturePrimaryAt004170D0` occupies **65 complete original
CODE bytes and 24 x86 instructions**, original PE-backed SHA256
`7902e64d0f7be19d52efc5437d13683392c433838d3e986d22a47b9ea7e2a387`.
The method acquires the real source buffer handle through actual native
`004028B0`, stores the result DWORD on the original stack, calls
imported genuine Windows `SetRect` via IAT `00657210` to set the region
left/top=0 and right/bottom=640/480, then invokes native game capture
`00401D80` with the true receiver, address of the real captured buffer
handle and rectangle. The actual native RECT is at EBP-0x14..EBP-0x5
and the 32-bit captured buffer handle is at **EBP-4**; the receiver is
originally saved at EBP-0x18 in the original 0x18 frame.

The first natural source using a standalone DWORD and RECT emitted the
correct **65-byte size** but allocated the two meaningful locals in
the wrong native physical slots, yielding **49/53 comparable original
bytes**. Reordering the declaration alone did not change VC7.1 stack
allocation. Independently grouping the actual 16-byte RECT and actual
returned 4-byte handle into a 20-byte used C++ state struct naturally
restores their real original EBP positions without fake local padding or
unused data. The pinned VC7.1 `/Od /Ob0 /Gy /GR- /GX- /Zi` C++ source
`src/FrameCapturePrimaryF460.cpp` matches the full **65 original CODE
bytes**, **53/53 native nonrelocation bytes** and all **three original
physical COFF REL32/DIR32 fields**, including the original imported
Win32 `SetRect` IAT target and actual game buffer/capture methods.
Only the affected `--unit frame-capture-primary-004170d0` was
cold rebuilt/replayed **1/1 exact**. No fake stack locals, raw ASM,
original-byte graft, masked/partial native body, external helper/Win32
CODE duplicate, full cold replay or remote Oracle acceptance.


## F461: full 98-byte native frame capture presentation with the original 152-byte RECT/quad stack state

The independent original R100-authored `FrameCapture::PresentPrimaryAt00417160`
at `00417160..004171C1` is **98 complete native authored CODE bytes /
30 original x86 instructions**, original PE SHA256
`19f91b5a63ab79eabeca1ea603a548ae3a1180819a0242b57c498cc1d3263bd4`.
Its actual native 0x98-byte stack consists of a real 16-byte Win32 RECT
at EBP-0x98 and a directly adjacent **136-byte physical quad carrier**
at EBP-0x88. Only the first **132** bytes of that quad are understood
as the original drawable sprite geometry; its last four are untyped
physical storage and are *not* asserted to be real private class fields.
These are genuinely used source objects, not inert stack-padding vars.
Natural `struct NativePresentFrameF461 {RECT rectangle; NativeQuadF461
quad;}` preserves both original EBP addresses and the real stack extent
where separately declared locals did not.

The full native function calls imported Win32 `SetRect` through true
IAT `00657210`, setting 640×480 source with zero origin, invokes the
original borrowed quad `InitializeFromRectangle` at `0040DB50`, sets
original game graphics mode to zero via `00401F50`, and calls real
textured quad draw at `004029F0` with the original native quad pointer,
RECT, color `0xffffffff`, and the original dereferenced D3D8 input
texture pointer. The original entire CODE was compared, not a cropped
draw helper, including all 30 native instructions and full RET.

The source `src/FrameCapturePresentPrimaryF461.cpp` compiled under
pinned VC7.1 `/Od /Ob0 /Gy /GR- /GX- /Zi` matches the **entire 98
original CODE bytes**, **82/82 original nonrelocation bytes**, and
**all four original physical COFF DIR32/REL32 references/destinations**:
Win32 SetRect, original quad initializer, graphics mode, and textured
draw. Only new `--unit frame-capture-present-primary-00417160` was cold
replayed, **1/1 exact**. The separate exact F460 65-byte frame source
capture function stays separate, with no double-credit of inherited
graphics/texture, Win32/CRT or draw callee CODE. No invented external
class fields, fake locals, pasted target bytes, ASM, masks, partial
comparison, all-unit cold replay or external Oracle acceptance.


## F463: complete native 152-byte battle-end update and score transition policy

The original independently R053-authored
`BattleEndScene::UpdateAt00424F60`, at `00424F60..00424FF7`, is
**152 complete original native CODE bytes / 45 original x86 instructions**,
PE SHA256
`794308aea60d349bbd4373329f151a92ecf3da1e30e62a89b744e2f96b5cc8f5`.
The true scene receiver calls its borrowed native input reader `004250C0`
and own vtable+8 animation action, advances the actual fighter at native
`00671418` through its original vtable slot+0x40, and invokes original
graphics update `004028F0`. The fighter's actual +0x6EF end flag
gates story completion. Signed character mode at global `0067161E`
selects special character 10 return `0x110B`; otherwise native C++
sets stage **40** through `00419CB0`, sends viewport
**(-10000,-300,1,1)** through `00407E60`, and compares unsigned fighter
score +0x2D0 with global best result `00671420` to return `0x220A`
(new high score) or `0x1102` (normal completed result). The ongoing
scene path returns **8**. The borrowed virtual base declarations are
only original physical ABI slots, not a complete original fighter type.

`src/BattleEndSceneUpdateF463.cpp` is a natural original-like C++ source
under pinned MSVC 7.1 `/Od /Ob0 /Gy /GR- /GX- /Zi`: complete original
**152 authored CODE bytes**, **112/112 original nonrelocation bytes**
and all **10/10 authentic original COFF DIR32/REL32 reference fields,
types and original PE destinations** matched first attempt. Only
`--unit battle-end-scene-update-00424f60` was rebuilt and cold replayed,
**1/1 exact**. No borrowed input, fighter, stage or graphics callee
CODE is double-counted, and no fake locals, assembly, imported original
bytes, masks, truncated original or full-project cold replay credited.

## F462: negative 16-combination complete 2,987-byte GameApplication WinMain CFG experiments

Continuing the whole `GameApplication::RunAt00602A60` R064 native boss
research, the true original remains **2,987 authored CODE bytes / 654
x86 instructions**, with its 60-byte after-RET 15-entry scene dispatch
DATA table to be compared separately and not credited as executable CODE.
The previous complete natural C++ semantic source F456 preserved all
15 actual scene allocation sizes and borrowed constructors but compiled
only 2,951 CODE bytes plus 60 switch DATA, 0x264 stack frame versus
original 0x278. The complete 16 variant `F462` controls in
`.analysis/f462-winmain-branch-shape/` independently combine all eight
true success/failure direction permutations for `RegisterClassExA`,
`CreateWindowExA` and `CoInitialize`, with both natural switch case
orders (including physically original case 4 first). **None** matches:
their entire CODE lengths are 2,948–2,951, and their native frame
remains 0x264. Changing syntax/branch direction alone is insufficient;
the original requires the real missing 20 bytes of physical local
objects and 14 original native instruction effects, not filler locals
or bytes. All original startup failures and Win32 pump teardown remain
part of the unresolved full-function comparison. No F462 cold exact
credit, no cropped match, no forged original byte sequence, no
whole-repository cold replay or external Oracle acceptance.


## F465: complete 180-byte original BattleEndScene native render and overlay policy

The R053-authored original `BattleEndScene::DrawAt00425000` at
`00425000..004250B3` is **180 complete original authored CODE bytes**
and **50 original x86 instructions**, original pinned PE SHA256
`93468d820b3c4dba84785743b1b29f6b983c6838c1c4e33c77f038bdfd38e6b2`.
Its genuine original graphics begin frame call `00402660` gates all draw
work; actor global `00671418` provides a real renderer at receiver+4
whose borrowed native depth mode `0040C840(0)` and blend mode
`0040C7F0(0)` are invoked in order. The original signed character ID
global `0067161E` is loaded through `AL` and sent to the real fighter
virtual method slot +0x44, preserving original byte argument ABI.
If original fighter byte+0x6EE is set, the rendering overlayer at
global `0067143C` is called through genuine **zero-argument** method
`00412EB0`. The original optional positive alpha byte at `006714D1`
causes real imported Win32 `SetRect` at `00657210` for 640×480, then
forms the native overlay color by shifting that byte 24 bits and ORing
original global color `0067149C`, and calls original filled rectangle
`00403910`. The original graphics advance `004027D0` is invoked after
all optional drawing paths.

A first whole native C++ semantic probe declared the overlayer incorrectly
as `SetDepthMode(1)`, which emitted **182 bytes**, including a spurious
`push 1` at original offset 0x60, even though all remaining original
control flow and native mode calls were already structurally aligned.
Independent original full disassembly showed original `00412EB0` method
receives **no arguments**. Correcting that borrowed method interface,
without deleting the real optional overlay branch, produces natural
complete-source VC7.1 **180 native CODE bytes**, **112/112 original
nonrelocation bytes**, and **17/17 original physical COFF DIR32/REL32
reference fields, types and original PE destinations**. Only affected
`--unit battle-end-scene-draw-00425000` was compiled and cold replayed,
**1/1 exact**. The actual full fighter, renderer and overlayer class
layouts remain unasserted; no graphic SDK/callee CODE double-counting,
fake parameters, locals, original bytes/assembler, masking, cropping,
all-unit cold replay or external Oracle receipt. It is a separate
whole-function addition from accepted F463 battle-end policy.


## F467: three complete game-scene native input policies, real OR-key combination

Three independently authored original functions use related but distinct
input update paths. `BattleEndScene::PollInputAt004250C0` (R102) is
**107 complete original CODE bytes / 32 original x86 instructions**,
native PE SHA256
`d40584cce3faeb759ca8e38a514ddee3e532d2471b1a4420a47a6d9ef0bdcc60`.
`SceneInput::PollTwoMappingsAt00426600` (R102) is **106 complete
CODE bytes / 32 original instructions**, SHA256
`17444f033e6174d85536c82954a7c41e81c301bb18e09bd8e601e559a274557e`.
`OpeningScene::ProcessInputAt00428C80` (R036) independently occupies
**106 CODE bytes / 32 original instructions**, SHA256
`d78daec2b5a419e0cc4ff46fda94c0e67693012628a73fe78f65a73f23b2ced7`.
The physically distinct native addresses, original source ownership and
true COFF references were all independently checked before grouping them
in a single natural C++ compilation unit.

Every original native function calls the real input joystick updater
`00403E50`, keyboard updater `00403F40`, then updates the original
shared first key controller at global `00671638` through `00406E80`.
The two 106-byte functions also update the second independent mapping
controller at `00671680` via the same real borrowed method, whereas
BattleEnd input instead invokes the actual current fighter input action
at global `00671418` through native `00452F10`. The rest uses original
scan codes `0x1C`, `0x38`, `0xB8` with real borrowed one-byte `CheckPressed`
method at `00407170`, and the genuine fullscreen mode toggle
`004018A0`. The initial meaningful but **incorrect** first probe used
`Pressed(0x1C) && !Pressed(0x38) && Pressed(0xB8)`, producing a
single wrong branch destination in each function despite otherwise
matching every native instruction. The original actually jumps **to the
mode-toggle call** whenever the 0x38 key succeeds, or else checks 0xB8;
therefore the correct complete behavior is exactly
`Pressed(0x1C) && (Pressed(0x38) || Pressed(0xB8))`. The corrected
source naturally restores all original branch displacements with no
grafted bytes or workaround.

Pinned VC7.1 `/Od /Ob0 /Gy /GR- /GX- /Zi` source
`src/SceneInputPollingFamilyF467.cpp` yields entire native original
**55/55, 54/54 and 54/54 nonrelocation bytes**, plus **13/13 genuine
original physical COFF DIR32/REL32 fields, symbols and targets for each
of the three distinct original functions (39 total)**. Fresh cold
replay targeted **only** `battle-end-scene-poll-input-004250c0`,
`scene-input-poll-two-mappings-00426600` and
`opening-scene-process-input-00428c80`: **3/3 exact across one object**,
crediting exactly **319 distinct authored CODE bytes**. All borrowed
original input engines, actor methods and fullscreen callees remain
external; no duplicate callee CODE, invented private class identities,
source ASM, fake locals, partial-native matching, all-unit replay or
external Oracle receipt. The old F466 AND-conditional version remains
an independent private negative control.


## F468: entire 83-byte original WinMain WindowCallback, true four-argument stdcall WndProc

The independently original R114-authored native
`GameApplication::WindowCallbackAt00603650` at
`00603650..006036A2` consists of **83 complete authored CODE bytes,
32 original x86 instructions**, original PE SHA256
`112890c5c708ce986d72173b6509b3ee782430d10677f7b67c32eb44a79a06a0`.
It is the actual Win32 WndProc registered by the original whole main
loop `GameApplication::RunAt00602A60`, with truthful
`LRESULT CALLBACK(HWND,UINT,WPARAM,LPARAM)` and actual **stdcall
RET 16**, no hidden game owner receiver. Native C++ switch first
materializes the real message UINT at EBP-4. `WM_CREATE (1)` sets the
original application initialized byte at `0068D674` to 1;
`WM_DESTROY (2)` calls the actual imported Win32
`PostQuitMessage(0)` at original IAT `0065723C`; `WM_QUIT (0x12)`
is a no-op; all three switch cases return zero. Other events are
forwarded in original HWND/msg/WPARAM/LPARAM argument order to
`DefWindowProcA` at IAT `00657240`. These exact native branches,
conditional destinations, stack slots and returns are compiler-produced
by natural Win32 C++ source rather than copied bytes.

Pinned VC7.1 `/Od /Ob0 /Gy /GR- /GX- /Zi` compilation of
`src/GameApplicationWindowCallbackF468.cpp` matches the **whole 83
original CODE bytes**, **71/71 original nonrelocation bytes**, and
all **3/3 authentic original physical COFF DIR32** fields/destinations
(the real app initialized byte and both imported Win32 APIs). Only
`--unit game-application-window-callback-00603650` was cold replayed,
**1/1 exact**. The linked 2,987-byte original GameApplication main
loop is **still unclassified**, with no accidental callee/WinMain or
Win32 implementation CODE credit. No invented game class layout, fake
locals, masking, assembly/pasted original bytes, cropped comparison,
full-repository cold replay or external Oracle receipt.


## F469: seven independently exact native 120-byte fighter-owned object factories

The original R050 independently authored fighter object allocation path
contains seven complete **120-byte / 34 native x86 instruction** factories
that allocate distinct original 0xE8-byte character objects and return
the newly owned object pointer through the original thiscall output slot.
Each factory performs a genuine `operator new(0xE8)` at `0064159D`,
returns null if allocation returns null, calls its own actual original
character-specific constructor with the fighter owner as parameter,
preserves MSVC VC7.1 `/GX` SEH cleanup with true unique handler and
valid 0x10-byte local allocations, then assigns the result and executes
original `RET 4`. Each original function was independently disassembled
and its exact constructor address, native PE SHA and original 34
instructions verified before considering family-level code.

Distinct original factory → constructor addresses are: Sakuya
`004C0920` → `004CA640`, Patchouli `005022C0` → `0050A4E0`, Remilia
`00551AA0` → `0055ABE0`, Yuyuko `00574210` → `0057D4E0`, Yukari
`00597480` → `005A1560`, Suika `005C0BB0` → `005C9C20` and Meiling
`005E2170` → `005EB490`. Their actual original PE function SHA256
hashes are individually retained in the corresponding R050 native
tracking rows; each has a separately checked EH handler relocation
address, rather than seven copies of one original address. A minimal
borrowed `0xE8` C++ carrier represents only the actual operator-new
footprint and the already independently accepted F422 constructor ABI,
**not** a claim of complete private object allocation or member layout.

Pinned VC7.1 `/Od /Ob0 /Gy /GR- /GX /GS /Zi` natural source
`src/FighterOwnedObjectFactoriesF469.cpp` matches all seven complete
original bodies on first semantic probe, with **96/96 original nonfield
bytes and all six real physical DIR32/REL32 COFF fields, symbols and
original destinations for each distinct factory**. A single affected-
only cold compiler run targeting the seven new unit names returned
**7/7 exact across one object**, crediting exactly **840 authored CODE
bytes** without double-counting any original F422 fighter object
constructor, the CRT `operator new` or compiler EH helper code.
All historical negative codegen/source tests remain intact; no fake
locals, assembly/pasted PE bytes, masked or truncated native functions,
full cold replay or external Oracle acceptance.


## F474: six full original scene-specific virtual texture resource destructors, with Title's native global state write

Six independently original-authored C++ derived scene destructor functions
were verified directly against the pinned Japanese TH075 executable,
with their individually original SEH handler and virtual table values.
Opening `004276B0` (R036), Replay `0042A2C0` (R234), NameEntry
`0042B300` (R234), Result `0042E870` (R234) and StaffRoll `00438BA0`
(R062) each have **127 original authored CODE bytes / 36 x86
instructions**, **99/99 original nonrelocation bytes**, and **7/7
authentic physical COFF DIR32/REL32 fields and native destinations**.
The separately original R062 Title destructor at `0043A1E0` is **142
whole CODE bytes / 39 instructions**, **110/110 matching nonrelocation
bytes**, and **8/8 physical original relocations**. These are seven
individually read/disassembled ref fields per function, not symbolic
virtual-class matches assumed on names alone. Each unique original PE
SHA256 and handler is retained in its approved `config/functions.csv`
provenance row.

All six independently model the real borrowed 8-byte scene base and
owned texture pointer at `this+8`; each derived class has its own original
virtual table, natural VC7.1 `/GX` exception registration, actual
conditional C++ `delete texture` through native scalar deleting texture
destructor `00425460`, true pointer temporaries, and borrowed original
base-scene destructor at `00431F40`. The **Title** scene has a genuine
additional *behavior* before deletion: sign extend original `signed
char` at receiver +0x38 and write a native 16-bit signed value to global
`00671630`. The physical gap from `this+0xC` to +0x37 is represented
only as untyped observed owner storage; this is not proof of any
particular original class members in that area. Other five destructor
functions must **not** be credited with this Title-specific side effect.

Natural `src/SceneResourceDestructorsF474.cpp` under pinned VC7.1
`/Od /Ob0 /Gy /GR- /GX /GS /Zi` generates each complete body and its
original authentic COFF references first try. Only the six affected
manifest units were freshly rebuilt and cold-replayed **6/6 exact
across one object**, crediting precisely **5×127 + 142 = 777** new
original CODE bytes, with total **43/43 distinct original physical
COFF fields** verified separately. The previously exact F447 Loading
and Logo scene derived destructors and F432 Options scene destructor
remain separate code without any duplicated callee bytes. No full
private original scene identity, external texture/base constructor
implementation, fake local padding, source assembly, target bytes
copied, masks, cropped comparisons, all-unit cold replay or external
Oracle acceptance.

## F473: WinMain original four owned RAII destructors and early-error exits, whole-boss negative controls

The 2,987-original-CODE-byte R064 `GameApplication::RunAt00602A60`
remains **unaccepted**, notwithstanding substantial original native
control-flow research. The original game startup has three separate
early failures of `RegisterClassExA`, `CreateWindowExA` and
`CoInitialize`. At each, original x86 first stores its own real return
code zero to native local EBP-0x190/-0x194/-0x198, then calls the four
*actual destructor functions*, in order `00406650` shared sound,
`00403BE0` input, `00401020` shared graphics and `00423A90` app-mode,
finally reloads that return code and branches to the original common
security-cookie/stack epilogue. Their original destinations were
independently decoded at all three call sites rather than inferred by
source class names. The graphics local also has an actual zero DWORD
store at original EBP-0x184 immediately following the four initial
constructor calls, absent in the earlier natural probe. The original
full function has 654 native instructions, `sub esp,0x278`, and a
separately compared owned post-RET 60-byte scene switch table.

The F456 complete natural WinMain code handled all 15 distinct scene
allocations, Win32 WNDCLASSEXA and game message pump, but emitted
**2,951 CODE bytes / 640 instructions** with native-style frame
0x264, mostly sharing exit cleanup. New F473 whole-source probes in
`.analysis/f473-winmain-native-raii/` instead introduce four actual
C++ automatic destructors and each real failure early return. They
compile to **3,022 CODE bytes / 650 instructions** and real frame
0x274, showing their source-level lifetime modeling is substantially
more faithful—but still not the original full CODE or exact frame.
The compiler also continues to merge three failure paths' destructor
sequences at a common exit rather than preserving original repeated
blocks. A variant using native ArchiveCatalog C++ RAII also remains
3,022 bytes. This is a falsifiable complete-function *negative result*,
not a partial credit or permission to fabricate filler locals or paste
original instructions. Real meaningful window/app/graphics local lifetime,
actual Win32 COM behavior, return destinations, scene-switch-case
ordering and the physical native stack must all be solved prior to
accepting any code or comparing the table. No all-unit cold replay
was run for these diagnostics.


## F479: 36 independent complete 28-byte stage-derived virtual destructors

All **36** remaining separately authored stage-background derived class
virtual destructors from BG00a (`00449DC0`) through BG09x (`00451E90`)
were individually disassembled and origin-checked against the pinned
Japanese original executable before source adoption. Every body is exactly
**28 original native authored CODE bytes / 11 native x86 instructions**.
They share the actual C++ destructor behavior, but **not** the same
original addresses, vtables, source methods, or accepted CODE bytes.
Every native body stores its own original class-specific virtual table
into `this+0` and calls original borrowed `BackgroundBase` destructor
`00449D40`. Its two physical original COFF fields are exactly a DIR32
at native function offset +0x0C for the separately original stage vtable,
and an REL32 call at original offset +0x14 for native `00449D40`.
Every independently returned vtable target is different; stage-specific
addresses range from BG00a `00658434` and BG00b `006584A4` through
BG09a `00658DC0` and BG09x `00658E54`. The unique original target
addresses, vtables, original PE SHA256 of each whole 28-byte body,
and original origin identifiers are frozen in the 36 separate current
`config/functions.csv` and exact-adoption entries, never copied as
a single undifferentiated claim.

Natural `src/BackgroundStageDerivedDestructorsF479.cpp` uses C++
`class BG00aF479 : public NativeBackgroundBaseF479` (and 35 individually
defined other derived classes) with truthful `virtual ~Class()` bodies.
Pinned VC7.1 `/Od /Ob0 /Gy /GR- /GX- /GS /Zi` automatically installs
the correct original derived vtable and emits the genuine base class
destructor call without source-side raw vtable injection, copied native
bytes, unearned inheritance layout claims, or fake locals. All 36
independent full-function diagnostic comparisons are **28/28 native
CODE extent**, **20/20 actual nonrelocation bytes**, **2/2 authentic
original physical COFF relocation types/fields and original PE
destinations**. A single cold compiler object targeted *only* the
36 newly created manifest names; the original whole-CODE replay was
**36/36 exact**, crediting exactly **36×28 = 1,008 original authored
CODE bytes**. No other stage ctor, the shared base destructor, any
vtable DATA or compiler/CRT code is double-counted. No full-project
cold replay, partial exact matching, fake ABI, manual assembly or
external Oracle acceptance. Historical exact F376/F377 stage loading
constructors remain separate authored original code.


## F481: five complete native archive, raster, camera and frame resource policies

Five independently authored original C++ game resource routines were
verified separately against the pinned original PE and compiled from a
single native-equivalent source under
`src/ArchiveRasterCameraFramePoliciesF481.cpp`. Each original function
retains distinct physical ABI, native instruction boundaries and original
COFF references, rather than being counted as a shared skeleton:

- `DataArchive::InitializeStateAndClearListAt0041D190`: original R180
  **90 authored CODE bytes /25 instructions**, original PE SHA256
  `c8680ebc6f18824f37a8121171ae846477969629b0b3b68515f3201d034fc628`,
  genuine list at this+4 constructor `0041D8F0`, owner handle at this+0
  null and list Clear `0041D9F0`. Complete original **66/66 nonfield
  bytes**, **6/6 authentic COFF refs**, true `/GX` native EH.
- `ArchiveResource::CloseHandleAndClearEntriesAt0041D1F0`: R175
  **98 CODE bytes /29 instructions**, PE SHA256
  `bc00c51364b599bfa0b4887220d5566dfe6cf5e711f4e7347b2c6fa3604bae6d`,
  conditionally invokes real Windows imported CloseHandle at `00657138`
  with owner +0 handle, clears actual list `0041D9F0`, then naturally
  invokes borrowed original list destructor `0041D930` through C++
  member lifetime and original `/GX` SEH. **70/70 nonfield, 7/7
  genuine original physical COFF fields**.
- `RasterResources::InitializeSelectedWindowAndEmptyStateAt0041BF90`: R183
  **64 CODE bytes /19 instructions**, PE SHA256
  `ef3f65ed3262399d765864cd003b1a1ad3752e33ac364d684596e38389ded302`,
  assigns real HWND parameter at receiver+0, resets observed +4/+8/
  +0xC/+0x14 fields to zero and returns receiver. **64/64 nonfield
  bytes and zero native relocations** (no fabricated references).
- `CameraMotion::ResetParametersAt00412620`: R103 **64 CODE bytes
  /13 instructions**, SHA256
  `5cbfbb4ed7f9e8380bb4991739067876ee642797a60b3321491128d9e486b77d`,
  directly updates original camera globals `006713EC`, `0067140C`,
  `006713F8`, `00671410`, `006713FC`. The original native DWORD
  immediate at `0067140C` is **`0x41A00000`, IEEE754 20.0f**, not
  5.0f. Natural source correcting the initial wrong constant restores
  **44/44 nonfield bytes and 5/5 genuine DIR32 fields**.
- `FrameCapture::DrawIfEnabledAt004171D0`: R100 **50 CODE bytes /22
  original instructions**, original PE SHA256
  `b9790cfd51266b2262af4ddac9f014e6ad28bfa3b6b15c8e756a2fa3690c968f`,
  tests real receiver enabled byte +4, dereferences physical texture
  field +0 and conditionally forwards the three original caller params
  to borrowed native `DrawTexturedQuad` at `004029F0`, authentic
  native thiscall `RET 0xC`. **46/46 native nonfield, 1/1 true COFF
  REL32**.

Each source was compared over its **complete original CODE extent**,
including all native returns, actual Win32 imports and original physical
relocation types/symbols/resolved destinations. Only affected five new
unit names were cold-built and replayed, **5/5 exact across one object**,
crediting **366 original authored CODE bytes**. The original private
owner allocation and unused fields beyond observed locations remain
unknown; borrowed actual list, camera, D3D, Win32 and CRT callees earn
no duplicate CODE credit. No assembly, embedded target bytes, masked
references, fake padding, cropped body, all-unit cold replay or remote
Oracle acceptance.

## F480: native WinMain real early scene-pointer lifetime hypothesis (nonexact)

The original complete `GameApplication::RunAt00602A60` remains **2,987
CODE bytes / 654 native x86 instructions** with 60 post-RET owned
15-case jump-table DATA bytes. Independent original disassembly at
0x1C documents a real `mov [ebp-0x184],0` immediately after the
app-mode constructor, before other three original automatic resource
client constructions, and the same actual scene pointer later receives
the original first allocated scene at native offset 0x491. This
corrects the F456/F473 C++ source hypothesis that only initialized
`currentScene` late at first scene creation. F480 experiments under
`.analysis/f480-winmain-scene-owning-pointer/` express a **genuine used
scene pointer initialized to NULL** at several live declaration
locations and assign new Scene4 later. With early C++ RAII destructor
semantics this adjusts complete CODE length from prior F473 3022 to
**2963** native-source-generated CODE bytes, and x86 count from 650
to **651**, with compiler frame 0x270 versus original 0x278. The
whole original WinMain/COM/Windows message loop remains nonmatching,
including physical true return/error control flow, native archive
interface and scene switch state. This is a meaningful falsifiable
whole-boss negative control **not accepted or credited**, not a reason
to add fake local variables, paste machine instructions or cold replay
all units.


## F484: seven complete independently authored background, camera, sprite, event and frame helper functions

Seven original native R-origin functions have been independently
verified with their complete original code, original native instruction
boundaries, actual ABI return conventions and every physical COFF
field/type/reference and pinned Japanese PE destination. All compile
naturally with pinned VC7.1 `/Od /Ob0 /Gy /GR- /GX- /Zi` and were
cold replayed **7/7 exact across one changed object**:

- `BackgroundBase::DestroyAt00449D40`, R108: **31 CODE bytes /12
  native instructions, 23/23 nonfield bytes, 2/2 original relocations**,
  PE SHA256 `4fc82ee47ccc2dca5ab8a419fe1d3850280cdde8374698e37a637ccd5083c84c`.
  Genuine C++ virtual base destructor installs its own vtable `0065844C`
  and calls the real native destructor `0040AE40` for the actually owned
  subresource at `this+0x18`. The 36 separate F479 derived destructors
  borrow this original *single* base function and never re-credit it.
- `CameraMotion::SetOverrideAt00412CC0`, R035: **39 bytes /12
  instructions, 23/23 nonfield bytes, 4/4 physical DIR32 refs**,
  PE SHA256 `fb3ed11f9ea0e0a0be27039315f17bf2a54c226718d8fcc971f32f4e6588a93a`.
  This true native cdecl function accepts a one-byte input override
  mode and three raw float arguments, writes them to original globals
  `00671414`, `006713E8`, `006713BC`, `006713F4` and returns without a
  hidden game owner.
- `SpriteSequence::RemoveFrontIfPresentAt004110C0`, R238: **37
  bytes /15 instructions, 29/29 original nonfield bytes, 2/2 REL32
  refs**, PE SHA256
  `6ec43187e7d9285b8129200a0e5f997bf512bdcfd04acf2d48973e67c82e7141`.
  Uses actual deque at `this+4`, unsigned Size `00411CE0` and real
  PopFront `00411D00` only when Size is positive.
- `EventQueue::LocalAcquireReleaseAt004239C0`, R114: **34 bytes /13
  instructions, 26/26 original nonfield bytes and 2/2 real REL32 refs**,
  PE SHA256 `6876552024eae981b549c28d4796a2e33ada0ab05a8f774d95189177da8c04a7`.
  Native code constructs one *actually used* scoped service at EBP-1
  with argument 16 through `004239F0`, invokes its destructor
  `00423A90`, and only **after** this scope ends returns original
  receiver at EBP-8. Writing `return this` from inside the live service
  scope incorrectly creates an extra return-value temp and six nonnative
  bytes; natural explicit C++ scope accurately restores native lifetime.
- `FrameCapture::InstallPresentCallbackAt00417120`, R100: **31 CODE
  bytes /12 instructions, 23/23 nonfield bytes, 2/2 real refs**,
  PE SHA256 `17a30c91963186b27dcf3e041fd84e4c58ba64b588c285b2106abecf874cb660`.
  Correctly registers actual **already exact F461** callback
  `00417160` via game API `004028A0`, then clears receiver byte +4.
- `FrameCapture::EnableDirectDrawAt00417140`, R102: **28 CODE
  bytes /12 instructions, 24/24 nonfield bytes, 1/1 REL32** reference,
  PE SHA256 `7b7b2b1f438308dca72456a613b6d25a9b4be0641d00cce7643042d644f318a6`.
  Registers the null callback through `004028A0` and sets +4 true.
  Both F484 FrameCapture methods are genuinely **void** thiscall;
  inventing a returned receiver adds an invalid `mov eax, this` to
  each.
- `BattleEndScene::DestroyAt00424F40`, R097: **28 CODE bytes /11
  original instructions, 20/20 nonfield bytes, 2/2 native refs**,
  SHA256 `39f5491f34d77924b0337e8214b6683222d78966402b5d6ca2bfae041d1eba9d`.
  Installs original derived vtable `00657B7C` then calls actual original
  borrowed base scene destructor `00431F40`. No invented resource delete
  absent from this exact native member.

The entire `src/BackgroundCameraEventFrameLeavesF484.cpp` compilation
matched all seven functions and **all 15/15 physical original COFF
reference fields**. Only the seven new unit names were cold replayed,
**7/7 exact**, adding exactly **228** original authored CODE bytes;
no borrowed F479 base consumer, F461 callback, original Win32/CRT
callee or unknown private owner layout is double credited. No fake stack
locals, asm, copied target bytes, masks/cropped extent, full repo cold
replay or external Oracle credit.

## F482: full-stage-loader provenance check, already independently accepted as F389

The actual R065 original `BattleLoader::LoadStageAt004183D0` was
re-decompiled under native Ghidra and re-disassembled in F482, preserving
its complete original PE function SHA256
`9d670e4a82fec9987f1785f1d1818aec6677c609cd0d71ba91da8c45406a6076`,
**3,765 original CODE bytes /761 native instructions**, including
36 actual distinct native background stage `new`/constructor choices,
separate originally owned **92-byte** after-RET 23-entry switch DATA
and exact C++ `/GX` exception lifetime. The canonical ledger and
original source were checked immediately after decompile and confirmed
this function **was already accepted and cold replayed in F389** as
`battle-loader-load-stage-004183d0`, with whole `compare_size=3857`,
`3177/3177` nonfield bytes and `170/170` physical COFF relocations.
No new stage-loader code is recredited in F482 or F484; historical
assumptions that this function remains pending are incorrect. The
actual separate 2,987-byte WinMain and 28K-82K character movement
bosses remain outstanding.


## F485: exact complete 156-byte native Loading and Logo sprite draw routines, actual quad ctor receiver

Two independent original R053-authored scene draw functions share a
render path but have distinct real native CODE extents: LoadingScene
`00425390..0042542B`, SHA256
`ccaa339ab8b73f6fa7a037cc608e88d99c810a05a3269ffa78bbde13129495f4`,
and LogoScene `00425620..004256BB`, SHA256
`8fbaa99f4adcc5870bb3d5e50ea9538ed6f7870cf6dbb437e42cec075d807442`.
Each is **156 original authored CODE bytes / 42 x86 instructions**.
The genuine source stack is 0x9C with a 16-byte native RECT at EBP-0x98
and a physically observed 136-byte quad carrier at EBP-0x88, of which
132 geometry bytes are understood; its remaining four physical bytes
are untyped, not a claim of complete private quad fields.

Original graphics begin `00402660` gates scene drawing, then the native
C++ source constructs the actual quad at **EBP-0x88** with original
zero-arg native constructor entrypoint `0040D990`. It sets actual
owner+8 texture renderer Depth mode 0 (`0040C840`) and blend mode 0
(`0040C7F0`), creates a genuine 640×480 Win32 RECT through imported
`SetRect` at IAT `00657210`, invokes borrowed game quad
`BuildQuadFromRect` `00411400`, draws a real texture quad through native
`0040C9A0` with source RECT, quad pointer, texture mode0 and tint
0xffffffff, then advances the graphics frame via `004027D0`.

Prior F470 full 156-byte structural probe used a C++ aggregate with
`struct DrawFrameF470 {RECT rectangle; DrawQuadF470 quad;}`; because
its quad member had a nontrivial default constructor, VC7.1 emitted an
*implicit enclosing aggregate constructor*, calling it with the frame
address EBP-0x98, whereas original PE calls `0040D990` with the quad
member at EBP-0x88. All other native instructions were aligned; this
yielded 123/124 original nonfield bytes and one different true COFF
constructor symbol, so it was correctly not adopted. Separate automatic
quad/RECT sources also changed their *actual* native stack locations
and whole function length to 147 bytes.

The complete natural source in `src/LoadingLogoSceneDrawF485.cpp` instead
represents the borrowed original zero-arg quad constructor as an
explicit named `DrawQuadF470::ConstructNative()` entrypoint on that
**actual used quad member**, which is semantically native construction,
not an invented original private method name or extra CODE. This
corrects the original receiver address, produces the entire **156/156
CODE extent**, **124/124 original nonrelocation bytes**, and **8/8
genuine physical COFF DIR32/REL32 fields, types and native PE targets**
for each distinct source. Only the two affected units
`loading-scene-draw-complete-00425390` and
`logo-scene-draw-complete-00425620` were built and cold replayed, **2/2
exact across one object**. Exactly 312 native authored CODE bytes are
credited, with no original ctor, graphic renderer, D3D, CRT or Win32
callee CODE double-count. No target machine bytes/ASM, fake locals,
masked relocations, cropped body, full cold replay or remote Oracle.


## F488: five complete original native scene advance / keyboard policy functions

Five real independent scene state/input routines were first reverse-
disassembled and individually origin-reviewed, then compiled from natural
source `src/SceneTemporalAndInputPoliciesF488.cpp` with pinned VC7.1
`/Od /Ob0 /Gy /GR- /GX- /Zi`. All native CODE and true COFF physical
references were checked separately, not derived from similarity alone:

- R036 `OpeningScene::AdvanceAt00427730` (`99 CODE bytes /31 original
  x86 instructions`), original PE SHA256
  `9588b47d69649b4ce2ebed5f493b0f7a8a8034aa0107b35ef6f899347e505777`: real
  original Opening scene input, virtual+8 animation and `004028F0`
  graphics; original globals `0067166C` / `006716B4` trigger 0x2202
  next-state, elapsed threshold 0xC15C returns 0xFF02, otherwise native
  WinMM timeGetTime records elapsed DWORD and returns 0xD. Original
  **79/79 nonrelocation bytes, 5/5 physical COFF refs**.
- R100 `LoadingScene::AdvanceAt00425330` (`84 CODE bytes /28
  instructions`), PE SHA256
  `ea4837ccb75e4b02de1fbfd7b1c72f1ceb526bb5b703588ed58e73c9f0f72d87`: actual
  first-frame load gate at receiver+0xC and scene vtable+8 animation,
  original already exact fighter loader `004176F0` and stage boss
  `004183D0`, alternate special return 0x1108 when native signed mode
  `006714B4` equals 3 and original character signed byte `0067161E`
  >=8; otherwise marks the stage loaded and returns 0x2000. The first
  complete 84-byte source differed by exactly **one original nonfield
  byte**: `unsigned char` mode emitted MOVZX versus actual original
  MOVSX. Restoring real `signed char` produces **68/68 original nonfield
  bytes and 4/4 physical COFF fields**.
- R100 `TimedScene::AdvanceAt004255D0` (`78 CODE /26 instructions`),
  SHA256 `69bc7bc7accc0117e35f5d61228af908aa8f191d6d04fc695d662034730ee30e`: exact
  native PollInput `004256C0`, vtable+8 animation and graphic tick,
  real unsigned short timer at native +0xC incremented with original
  16-bit instruction; result >180 returns 0x220D, else 4. Complete
  **70/70 nonfield bytes and 2/2 real original COFF refs**.
- R100 `SceneInput::PollAt004256C0` (`96 CODE /30 instructions`),
  SHA256 `38bb20ed2eb499d59c4a2146e1ec5d809aa8e3455bbeac38055043c1b96f7c7b`,
  and independently R043 `StaffRollScene::PollSkipInputAt00439F90`
  (also `96 CODE /30 instructions`), SHA256
  `37770f7a7d20c1891b83ae1a0be2547964ba3f31cd20cddcd292903e0e80bd80`: independently
  compare all actual joystick `00403E50`/keyboard `00403F40`, native
  one-controller shared input `00671638` Advance and original scan keys
  `0x1C && (0x38 || 0xB8)` with real graphics toggle `004018A0`.
  Both have **52/52 original nonfield bytes and 11/11 authentic physical
  original COFF refs** checked *per original address*.

All five affected units were **fresh cold replayed 5/5 exact in one
compiler object**, crediting **99+84+78+96+96 = 453 distinct original
authored CODE bytes**. No already accepted 3,232-byte fighter loader,
3,765-byte stage loader, Win32/WinMM or shared input callee CODE was
double-counted; original receiver classes remain borrowed ABI views,
not complete private types. No target bytes graft, source ASM, fake
stack fields, masked relocations, shortened original or full cold replay.

## F486-F487: complete but nonexact 208-byte StaffRoll phase-window CFG probes

The R043-authored native `StaffRollScene::Advance` at `00438C20` is
**208 native CODE bytes**, independently disassembled. It advances
controls and animation, and in stage phase 1 only on elapsed <=0x14C08
checks the lower bound 0x13880: the actual original **unsigned JAE**
jumps directly from native function offset 0x4A to the shared WinMM
clock-update block at original offset 0xB6 when elapsed >=0x13880.
Outside the upper window, or after the early stage viewport actions,
the actual fighter/end-mode/best-score dispatch uses distinct original
returns 0x110A/0x1107/0x1102; the clock fallback returns 0xB.
The existing whole natural source F450 initially conflated the two
window directions; F451 fixed true semantics with `goto`, yet pinned
MSVC 7.1 emitted a two-instruction `JB fallthrough; JMP clock` instead
of original single JAE, yielding **210** nonexact bytes. Ten alternative
real phase outer-do/while/for and seven state switch/break variants
under `.analysis/f486-staff-fallthrough-cfg/` and
`.analysis/f487-staff-switch-break/` compiled at **210–230 bytes**,
not original 208. Their original control/predicate assumptions and
actual displacements remain falsifiable private evidence. No partial
CODE credit, invented switch cases, asm, native machine byte patch or
full-repository cold replay was used.


## F489: full 128-byte native window-texture resource constructor and actual exception-safe member lifetime

Original R035-authored `WindowResource::InitializeAt00412DD0` at
`00412DD0..00412E4F` has **128 complete original authored CODE bytes
/36 original x86 instructions**, pinned original PE SHA256
`29fb8e8704dc0dd467d4d8ef153aece891397a9e64fc3325eb55afd66fe56de3`.
This is a genuine VC7.1 `/GX` C++ owner constructor with original
80-byte texture archive member at physical receiver+0x28, not a
standalone Win32 helper or unrelated class base. It calls actual texture
constructor `0040AD80`, initializes exactly one native slot via
`0040B1D0`, loads original resource path global `00657898` and root
`00657890` through `0040BB80`, and constructs a real 1024×512
rendering surface using native `00401C20`, passing `this` and original
format 0x20. The owner bytes +0..+0x27 remain untyped physically
observed storage; their original private member types are unknown.

The initially plausible C++ source declared the real nontrivial texture
*constructor* but **omitted its destructor**. VC7.1 then naturally
emitted only **83 bytes**, with no native SEH registration or exception
state, contrary to the original actual `push -1; push EH; fs:[0]`
prologue. This is falsifiable evidence for *real owned member lifetime*,
not permission to add artificial exception markup. Declaring
`~WindowTextureArchiveF489()` on the actual borrowed member produces
the native `/GX` exception handler `0065508B`, native state 0 to -1
transition, genuine cleanup/SEH epilogue and the exact complete
128-byte original body. Natural pinned VC7.1 source
`src/WindowResourceTextureInitializeF489.cpp` matches **88/88 original
nonrelocation bytes and all 10/10 authentic physical native COFF
DIR32/REL32 references**, including original SEH handler, `__except_list`,
texture ctor/slot/resource and surface draw target. Only affected
`--unit window-resource-initialize-texture-00412dd0` was cold rebuilt
and replayed, **1/1 exact**. Borrowed texture, D3D/Win32/CRT and
compiler EH helper CODE is not double-credited; no assumed private
class layout, fabricated locals, pasted native bytes/ASM, masks,
cropped original function, all-unit cold replay or remote Oracle.


## F490-F492: four complete native card, fighter and shared resource lifetime policies

Four separate original authored C++ methods have been recovered as whole
original CODE extents with independently checked PE native instructions,
relocations and borrowed resource/container ABI. Their actual original
source ownership, PE SHA and exact evidence are frozen in their distinct
function-origins and `config/functions.csv` rows.

**F490 CardList:** original R043 `CardList::ClearEntriesAt00431940`
occupies **112 native CODE bytes /39 original x86 instructions**, native
SHA256 `b592cb1f5747792c46b6d67f443565d12bfeb5e94cf2d7205b57f1363dd5a4be`.
The original list is at owner+0x18, with actual unsigned Size `0041DD50`,
indexed At `0041DD70` and final Clear `0041DF50`. It iterates every
slot, tests its actual owned pointer for null, stores the pointer in
a real 32-bit original EBP-8 temp, calls authentic native deletion
`0064169D` only on nonnull elements, and unconditionally clears the
list. Full **92/92 original nonrelocation bytes** and **5/5 real original
COFF fields** matched natural `src/CardListClearEntriesF490.cpp`.

**F491 FighterResources:** original R180
`FighterResources::ClearMemberBeforeDestructionAt004204D0`, **84 CODE
bytes /22 instructions**, native SHA256
`7289e83a2771ade7d9820b05dd083445ffb32f39fe654554ec84e95e1df29982`.
The actual native C++ owned resource at `this+0x7D0` receives a real
Clear call to `004216D0`, followed by its *automatic C++ member
destructor* `00421530`, with compiler-produced genuine `/GX` EH state
and handler `00655566`. Natural source recovers **60/60 nonfield bytes
and all 6/6 genuine native COFF references**.

**F491 SharedResource:** original R175
`SharedResource::ReleaseInterfaceAndTexturesAt00412E50` consists of
**83 CODE bytes /26 instructions**, SHA256
`66883ae3ca9776a99962cebb1b654a4a718766a5146b9aadb8e61302a43267a2`.
The real owner pointer at `this+0` is a D3D8 COM interface, whose
original vtable+8 `Release` is invoked on the true interface receiver;
then real owned native member at `this+0x28` is destructed through
`0040AE40`, with natural original `/GX` handler `006550A0`. The
**63/63 native nonfield bytes and 5/5 physical COFF fields** match.

**F492 CharacterResources:** original R175
`CharacterResource::ClearEntriesAndReleaseBaseAt0052D020` occupies
**105 authored CODE bytes /27 instructions**, SHA256
`a8909ac886a86da33ed1e9f1cc523d44050e1459db2b5684272d9cce2223e4e0`.
It is an actual derived virtual C++ destructor, installs original class
vtable `006598D0` and first clears physically real child at +0xFEC
through `00531CE0`; the compiler then automatically invokes child
destructor `00531C40` and original borrowed base destructor `00456910`.
Its VC7.1 `/GX` EH state changes from 1 to 0 to -1 naturally, and
original handler `006564E8` is preserved, with **73/73 nonrelocation
bytes and all 8/8 original physical COFF reference types and targets**.
The large untyped bytes ahead of +0xFEC do not imply a recovered full
private fighter layout or additional child objects.

Four affected units and only those units were rebuilt and individually
cold replayed **4/4 exact across three source objects**, crediting
**112+84+83+105 = 384 distinct original authored CODE bytes**. No
borrowed list/actor/COM/Win32/CRT destructor or base callee code is
credited twice, no source assembler/target code bytes, fake stack locals,
masked COFF fields, cropped native bodies, all-unit cold replay or
external Oracle receipt.


## F493: full original 60,999-byte Reimu action-boss dispatch structure and 1,090 post-RET DATA (research, NOT exact)

Independent Ghidra decompilation and original pinned-PE x86 decoding
confirms the R063 `ReimuFighter::AdvanceActionStatesAt0045DD70` is
**60,999 authored CODE bytes** at `0045DD70..0046CBB6`, with **16,837
original x86 instructions and 1,026 actual call instructions**. Its
original code SHA256 is
`b78fa89a709b1cbbafdf4310c6fd81dd68369a9fa528a1852a64bb105ee93bc2`.
The original `this` stack is EBP-0x34, native stack reservation 0x380,
and the action ID is a signed short at owner+0x60 loaded to EBP-0x38,
with two independent real signed-short early guards at owner+0x82 and
`(*(this+0x2E8))+0x3BA`. Five special original action IDs 0x32,
0x8C, 0x12C, 0x186 and 0x25B bypass the six indexed spans.

The **six native indexed-JMP instructions** are at 0045DDCB, 0045DE05,
0045DE42, 0045DE78, 0045DEB8 and 0045DEE2; their tables are contiguous
immediately after the full function RET at `0046CBB7`. The original
dense DWORD slot counts are **11, 26, 32, 10, 32, 31** (142 physical
DIR32-style jump entries, **568 DATA bytes**), and four sparse byte maps
are **49, 68, 212, 193 bytes** (522 additional DATA bytes). The final
map ends at 0046CFF8; original PE then has 7 CC bytes before next
function 0046D000. The **1,090 complete original post-RET DATA bytes**
hash as `12ff143bc7e1263db16b4c6629827a16e70973f339e7cc787c2aed9ee57d98eb`.
All 142 original physical table DWORDs resolve to verified original
instruction boundaries within this one native CODE body, yielding 139
unique targets; all sparse byte map indexes lie in their actual dense
target ranges. The full original Ghidra output has six separate state
`switch(iVar5)` constructs and **138 explicit case labels** (11+25+31+
10+31+30). Dense slots, unique native entry labels and explicit Ghidra
case clauses are distinct quantities and must not be conflated.

A new read-only deterministic script
`scripts/repo-python scripts/verify-reimu-action-dispatch.py` reproduces
all these checks directly from the **pinned original PE**, including
full CODE/data hashes, decoded instruction/RET boundary, six original
indirect x86 jump operands, continuous table/sparse layout and seven
int3 alignment bytes. The complete original evidence and exact per-span
table addresses are recorded at `docs/REIMU_ACTION_BOSS_DISPATCH.md`
and Ghidra output `.analysis/f493-reimu-megaboss/original-native.c`.
These results provide a precise action dispatch contract for a future
whole-function native C++ reconstruction but are **not an exact or
structural match of any reconstructed source**. No CODE coverage is
credited for the 60,999 bytes or any of the 1,090 DATA bytes, no jump
table is pasted into source, no fake stubs, and no all-unit cold replay
was run.


## F494: full native 99-byte original Win32 CreateFontA rasterizer wrapper

Independently reviewed original R103
`TextRasterizer::CreateFontAt0041C060` at `0041C060..0041C0C2`
contains **99 complete authored CODE bytes, 38 original x86 instructions**,
original Japanese PE SHA256
`7787306d92a91e07f5c22dcb0bd14abd54b60853e61fbf0a80f6fc49531dc9c7`.
The real source class saves the caller height DWORD at owner+0x10 and
three actual individual low-byte style/option fields at owner+0x28,
+0x29 and +0x2A. It then passes the caller face name and original
14-argument Win32 font configuration to true imported CreateFontA:
`(height,0,0,0,400,0,0,0,0x80,4,0,2,0x31,faceName)`, and stores
returned HFONT at real owner+8. Those are all physical original
parameter/order facts, not an inferred full original Rasterizer layout.

The C++ member itself has the real name `TextRasterizer::CreateFont`,
which conflicts with Windows `#define CreateFont CreateFontA`. An initial
original-like source compiled with the wrong macro-expanded member name
and failed at the 14-argument call. The correct `#undef CreateFont`
*after* including `windows.h`, and explicit `::CreateFontA(...)`,
restores a natural complete C++ implementation under pinned VC7.1
`/Od /Ob0 /Gy /GR- /GX- /Zi`, matching the entire **99 native CODE
bytes**, **95/95 original nonrelocation bytes** and its sole genuine
physical COFF DIR32 reference at native offset+0x53 to original Win32
IAT address `00657044`. Only affected
`--unit text-rasterizer-create-font-0041c060` was cold rebuilt and
replayed **1/1 exact**. No Win32/GDI implementation code or full
original private class members credited, no padding, asm, copied
native bytes, masks, truncated function, full-project replay or
external Oracle acceptance.


## F496: 89 independently verified 11-byte original Stage background empty virtual callbacks

All **89** remaining separately authored `BackgroundStage::NoOpVirtual`
entries between original PE addresses `00449B40` and `00451DF0` were
individually origin-checked and physically decoded before accepting
them. Each complete native function is exactly **11 original authored
CODE bytes /7 original x86 instructions**, with identical original PE
SHA256 `012a7b6ce927f083ba98a546e3d3f750b2a1d82f350ca27efbd30a9c3c7718a5`
and actual entire x86 instruction bytes:

```
55 8B EC 51 89 4D FC 8B E5 5D C3
```

The genuine native function is only a `thiscall` receiver saved to
EBP-4 and ordinary epilogue/RET; it performs **no game work** and has
**zero physical COFF relocations**. Every function has a separately
addressed independently authored original entry. Unlike arbitrary
compiler stubs or partial body extraction, these are genuine 11-byte
full original game virtual methods. The natural source in
`src/BackgroundStageNoOpVirtualsF496.cpp` defines 89 individually named
`void StageBackgroundNoopF496_NNN::NoOp() {}` methods. Pinned VC7.1
`/Od /Ob0 /Gy /GR- /GX- /GS /Zi` reproduces the entire original byte
stream and **11/11 real nonrelocation bytes per original address**,
with accurately frozen empty relocation list rather than fabricated
callee refs. The 89 affected units were cold rebuilt and independently
replayed **89/89 exact across one object**. Exactly **89 × 11 = 979
original authored CODE bytes** are credited. Historical F376/F377 stage
constructors, F479 stage derived destructors and borrowed native base
classes are not double-counted. No executable patch, source assembly,
extra locals, masks, partial match, all-unit replay or external Oracle.

## F495: historical rank-label `/GS` local-buffer negative controls, subsequently superseded by F516 full exact

Original R075 NameEntry `0042B110` and original R043 Result `00431890`
rank/decimal labels are each **169 complete native CODE bytes**. Both
original physical stack frames are 0x9C, with native this saved
EBP-0x9C, real drawable quad receiver EBP-0x98, all eight rendered
glyph bytes EBP-0xC..-5, and the genuine VC7.1 `/GS` stack canary at
EBP-4. The original eight glyphs encode prefix 13,40,71, signed rank
quotient/remainder base+52 and three terminators 100. Full original
C++ logic matches all native arithmetic and 169-byte whole length but
glyph bytes move to EBP-0x14 if source uses an ordinary 8-byte `char`
array in quad aggregate. Struct-of-eight meaningful fields correctly
positions the actual glyph record at EBP-0xC but loses native /GS,
shrinking the whole code to 153 bytes. New F495 physical quad carrier
experiments in `.analysis/f495-rank-gs-real-quad-buffer/` try native
132/136/140-byte byte-addressable used packet storage, native union
of packet DWORD and char views, and mixed byte/word meaningful carrier
fields. They all remain **negative**, despite some restoring whole
169 CODE bytes and 136/145 comparable original bytes: the actual
rendered glyph stack and native canary semantics are not simultaneously
restored. No inert buffer/canary, unsafe ABI, original-byte patch,
truncated 169-byte comparison, partial exact credit or whole cold
replay. Revisit genuine class member layout/VC7.1 source parse/lifetime
order rather than treating a mere equal instruction count as exact.


## F499: five exact original AuxEffect, sound, command and battle-state forwarders

Five independent R101/R102/R167/R233 original authored game functions
were individually verified against the original Japanese PE, fully
compiled from `src/AuxEffectAudioCommandForwardersF499.cpp` under pinned
VC7.1 `/Od /Ob0 /Gy /GR- /GX- /GS /Zi`, and fresh targeted cold
replayed **5/5 exact** in one compiler object. The two physically distinct
AuxEffect wrappers are `SpawnPeerAt005FAB90` **61 CODE bytes /25 native
instructions** (PE SHA256
`880a5115745e90929d87e33218bb682b72c04dadbbb6e123b6e255f373b59551`)
and `SpawnConfiguredPeerAt005FABD0` **65 CODE bytes /27 native
instructions** (SHA256
`9d49aba514d07edabe5844f72ada9c3fe98970508bccb03b311719a479c75333`).
Their native thiscall receiver owns a real original physical position
record at +0x80 (16 bytes of observed actual offset/extent) and the
original linked effect manager pointer at +0x90; both invoke authentic
borrowed native `005F7AA0` with the original **eight actual arguments**.
Both forward original 16-bit kind and two 32-bit values; the 61-byte
variant sends its two given low-byte modes and two native zero modes,
whereas 65-byte variant forwards all four caller low-byte modes. Source
uses real `short`/`unsigned char` formal parameters and generates native
`MOV low-register, operand; PUSH register`, not invented 32-bit sign
extension, plus original thiscall RET 0x14/0x1C. Each has exactly one
physical COFF REL32 callee field, matched to `005F7AA0`.

`AuxEffect::PlaySharedSoundAt005FAC40` is **29 CODE bytes /11 native
instructions**, SHA256
`647284f43923e5530fcaa34a938784f7f624b44dd22c961a53365dbf64cd9bb9`.
It sign-extends the actual signed 16-bit audio ID to DWORD before calling
shared audio manager native `004079C0` via original sound pointer global
`00671618`, with exactly two genuine physical COFF relocations.
`CommandList::ClearEntriesAt004110F0` is **22 CODE bytes /10 native
instructions**, SHA256
`abfaec9ac3ba4f997aa6ed929f764fd49b19d1a032de683f1aee1202a44f85bb`,
calling original borrowed `00411D60` deque clear on actual owner+4.
`BattleScene::SetSharedValueAt004557E0` is **21 CODE bytes /9 original
instructions**, SHA256
`cbcf37543b27fc26938ab4e3e2855cede6514ca920710f7a5d7181cfd5cbf57f`,
which writes the original input DWORD directly to native global
`00671628` and preserves actual RET 4.

The complete original **57/57, 61/61, 21/21, 18/18, 17/17** nonfield
bytes and all **six authentic physical COFF DIR32/REL32 references**,
including original global-address and shared callee targets, are separately
checked in `config/match-units.toml`. Exactly **198 new original authored
CODE bytes** are credited. No assumed complete private owner/manager
class layouts, no borrowed game/CRT/runtime callee code, false 32-bit
parameter widening, fake locals, source ASM, original-byte graft, masks,
partial native extents, all-unit cold replay or external Oracle receipt.

## F497–F498: historical original 92-byte GameProgress register-order negative controls, solved by F535 exact

The remaining R? `GameProgress::IncrementSelectedRecordAt00425130`
has a 92-byte PE body that loads *signed character* at owner+0x16AC4
and *signed difficulty* at owner+0x16AC5. The native read/increment/
write order computes signed difficulty stride `0x5FC` first in ECX,
then signed character stride `0x17F0` in EAX, **adds this to the
character offset**, and loads the counter DWORD at combined +4. It
then repeats with exactly native register allocation for the store.
The exact observed 2D stride relation is **4 × 0x5FC = 0x17F0**; that
is a genuine native per-character/per-difficulty record count relation,
but its full private record fields remain unknown. Several meaningful
C++ parenthesized pointer expressions, byte-index/subscript alternatives
and physically correct 2D typed rows using two true signed selector
bytes were compiled under pinned VC7.1 in
`.analysis/f497-progress-real-array-index/` and
`.analysis/f498-progress-true-strided-record/`. All correctly produce
full 92-byte CODE size and no real native relocations, but use wrong
*operand computation order* when adding the owner base; the complete
nonfield comparison remains **48/92 to 54/92**, not exact. No source
credit is added for this function, no fake register asm, forced padding,
masked comparison or all-unit cold replay.


## F500-F502: independently verified full original WinMain 15-case switch, four cleanup paths and thiscall scene-policy ABI (NOT exact)

The still-unaccepted R064 `GameApplication::RunAt00602A60` contains
**2,987 whole original native authored CODE bytes / 654 decoded x86
instructions**, original PE SHA256
`780862e0f784ac2cbd16ed20eaff12c0da49a0c831ce4a9f56e85fc2edb3ffa0`.
Its 15-element, **60-byte** original scene jump table begins exactly
after `RET 0x10` at original `0060360B`; the true table SHA256 is
`840a0d5ad8c1d5ad0a26f5ff4beae4c657cb03640df58b0aa1b71abba243fe86`.
All **15 original case targets** were decoded, verified instruction-aligned
and checked to start with the right unique `operator new` footprint
and native new call `0064159D`; physical case **4** is first in the
original switch CODE even though the table indexes cases 0..14.
After table DATA there are exactly nine `CC` alignment bytes before
the independently exact F468 WinMain WindowCallback at `00603650`.
No switch DATA/CC bytes count as CODE.

Original complete x86 provides four separate, identical-order
`00406650` sound → `00403BE0` input → `00401020` graphics →
`00423A90` app mode native destructor call chains, one in each native
startup failure (RegisterClassExA, CreateWindowExA, CoInitialize)
and one in genuine successful shutdown. Original native C++ scene
updates at `00602F0E` and `00602F95` call borrowed scene **thiscall**
`00431F60`, **not** the cdecl free function incorrectly declared
by older F455/F456 whole-source hypotheses. A genuine scene-pointer
local initializes at EBP-0x184, immediately preceding the 260-byte
module-path buffer at EBP-0x180. Original message pump invokes each of
PeekMessageA, GetMessageA, TranslateMessage, DispatchMessageA exactly
once in its authored CODE. These are independently observed original
physical locations and native x86 call targets, not inferred complete
source class layout.

Pinned VC7.1 complete C++ F500 experiments corrected actual scene
instance ABI and state-word branch order; the separate real scene
pointer/path arrangement emits **2,974 native-style CODE bytes /653
instructions /0x270 frame**, not original 2,987/654/0x278. A plausible
physically grouped actual scene pointer+path carrier produces 3,109
CODE bytes rather than matching native stack. F501 tests twelve
separate complete-source forms using one Win32 PeekMessage if/else
event pump, either branch orientation or early continue, and four
actual MSG lifetime declaration positions. All remain nonexact at
**2,947–2,962 CODE bytes /650 instructions, 0x270–0x274 frame**.
The full original WinMain allocation/case/disposer details, proof of
all 15 case CODE destinations, exact callback and table physical
boundaries, and reproducible native validation method are recorded
in `docs/WINMAIN_ORIGINAL_CONTROL_FLOW.md`; read-only script
`scripts/repo-python scripts/verify-winmain-scene-dispatch.py` checks
all independently against the SHA-pinned original PE. All experimental
full source/probe logs survive under `.analysis/f500-winmain-owned-frame/`
and `.analysis/f501-winmain-message-layout/`. Nothing from the full
2,987-byte function is accepted, and no original table DATA or
external callee code is double-credited. No byte masks, target patches,
fake locals, source ASM, truncated CODE, all-unit replay or Oracle
receipt claimed.


## F504: complete exact original 208-byte StaffRoll advancement boss, correcting historical wrong stage/score scope

The long-unaccepted R043 authored original native
`StaffRollScene::AdvanceAt00438C20` at `00438C20..00438CEF` is now
**208 original authored CODE bytes /57 x86 instructions**, original
PE SHA256 `516cf2472968907001946b6e0d3a98291410076f09abdef5ac3eb18ea9fc1132`.
Native nonrelocation comparison was independently **156/156** and
all **13 genuine physical COFF DIR32/REL32 fields and their actual
native destinations** were checked separately. A fresh, isolated
`--unit staffroll-scene-complete-advance-00438c20` cold build and
replay returned **1/1 exact**. The original native function uses only
its true borrowed StaffRoll scene, input/graphic/stage/camera/audio and
WinMM APIs; no external caller/callee CODE was double-counted.

The fundamental error in F450/F451/F486/F487 was **the C++ control-flow
scope and the actual native branch meaning**, not the compiler's inability
to generate an optimized JMP. The original x86 at offsets +0x37..+0x4A
is: test unsigned elapsed+0xC against upper bound `0x14C08`; `JA
0x4C` directly enters stage operation if **above** upper bound; if
not above, compare elapsed against lower bound `0x13880`; `JAE 0xB6`
directly enters time reset if **in** the inclusive bounded window;
otherwise it enters stage operation when **below** lower bound. Thus
the guarded native code implements the source predicate
`elapsed > 0x14C08 || elapsed < 0x13880` and both **SetStage(40)**
and the **following fighter, ending-mode and best-score dispatch**
belong to this **same** condition. Earlier sources either put the
score dispatch outside this condition (untrue native behavior) or
represented the bounded-window skip through an explicit goto, causing
VC7.1 to emit extra `JB skip; JMP time` instructions and 210–235
whole-function bytes.

Natural complete source `src/StaffRollSceneAdvanceF504.cpp` groups both
actual stage setup calls and all real fighter branches **inside** the
original outside-window condition; the time-reset code is then simply
the fall-through when phase is not 1 or elapsed is within the window.
Pinned VC7.1 `/Od /Ob0 /Gy /GR- /GX- /GS /Zi` automatically emits the
correct original `JA` to original offset0x4C and **one `JAE` directly
to original offset0xB6**, without assembly or invented control-flow
labels. Original phase global `0067166C` is checked for 1; score and
fighter globals `00671418`, `00671623`, `006714CE`, `00671420` drive
original three ending returns 0x110A/0x1107/0x1102; stage set
`00419CB0(40)`, viewport `00407E60(-10000,-160,1,1)` and timeGetTime
import `00657264` are individually verified. Normal clock fallback
updates owner+0xC from WinMM time minus owner+0x10 and returns 0xB.
The complete independently correct **208-byte x86 and 13 native COFF
refs** are now frozen, with **zero partial code credit or borrowed
callee duplication**. F450/F451/F486/F487/F503 variants remain
valuable preserved historical *negative controls*, not current pending
reconstruction claims. No fake locals, pasted original native bytes,
assembler, masked references, truncated original or all-unit cold replay.


## F509: original 82,796-byte CharacterMove action megaboss; 1,126 native after-RET switch DATA (research, NOT exact)

The separate R048 authored `CharacterMove::AdvanceAt004AC040` original
function is **82,796 full original PE CODE bytes /22,721 decoded x86
instructions /1,361 call sites**, native original PE SHA256
`4dced8c8583edf4b8234505793e28732e19af2adb311d0d39a755f0036e59cfc`.
Its single `RET` ends at `004C03AC` after original CODE `004AC040..
004C03AB`, followed by **151 genuine 32-bit jump slots (604 bytes)**
in six dense tables and **522 native sparse byte indexes** in four
actual index maps. All 1,126 physical post-RET DATA bytes are contiguous
`004C03AC..004C0811`, SHA256
`bd3fbb666cc78c750efbf154d066c8087cb36225fd34593994240e77ed392377`,
then 14 original `CC` pad bytes before next function `004C0820`.
The 151 original DWORDs resolve to **147 distinct valid original
whole-function x86 instruction boundaries**. Four sparse native maps
have true physical lengths 49,68,205,200. Whole source layout of the
six original state dispatch ranges and all table addresses are in
`docs/CHARACTER_MOVE_ACTION_DISPATCH.md` and checked by new read-only
`scripts/repo-python scripts/verify-character-move-dispatch.py`.

Original real native stack has `sub esp,0x720`, this at EBP-0x64 and
its signed short action ID from owner+0x60 at EBP-0x68, with two early
original state guards at owner+0x82 and nested owner+0x2E8/+0x3BA.
The original full Ghidra decompiler 6,631-line output is retained at
`.analysis/f509-charactermove-megaboss/original-native.c` and has six
state switch blocks with 146 actual `case` labels. **Crucially, the
68-byte original sparse index map `0x08F..0x0D2` is physically
byte-identical** to the map of the separately R063-authored 60,999-byte
Reimu boss at `0046CCFC`, SHA256
`a5a34134b8e8e16d03f131a259adb2621cc4cf6499be28366ab35d452f1f48f6`;
its dense CODE destinations are different. Original CharacterMove
switches later group `0x187..0x253` then `0x255..0x31C`, versus
Reimu's `0x187..0x25A` and `0x25C..0x31C`. Thus shared original
state-lowering byte patterns are real but **not** interchangeable
original code or C++ class layouts. This work yields independently
attested whole-boss dispatch evidence **without any exact CODE credit
for the 82,796 bytes or any DATA/padding**, no source native-byte
graft, no guessed class ABI or full-unit cold replay.

## F505–F508: authentic but nonexact medium-body physical layout trials

Original R054 `SceneObject::ReleaseAt0043B0B0` is 248 CODE bytes.
Existing natural C++ genuine C++ derived destructor sources matched
whole 248 bytes with **191/200 original nonrelocation bytes** but
mismatched nine native EBP offsets: source-generated texture deletion
temporaries landed at -0x20/-0x1C and three freed buffers at
-0x18/-0x14/-0x10; original uses -0x14/-0x10 for texture and
-0x18/-0x1C/-0x20 for the actual three buffers. New F505 source
declaration-scope variants preserve wrong allocation, and F507
explicit used texture-release locals generate 251–256 bytes.
Original 303-byte R? ReplayScene filename label draws once inside
*each* memcmp branch; new F506 nine complete natural C++ variants
with two actual draws, source glyph structs or arrays and real
132/136/140-byte native quad carrier variants all generate 342 bytes
and wrong native locals, not exact. Original R? 92-byte progress counter
uses true signed fighter/difficulty and 0x17F0/0x5FC real native
strides; F508 tests eight real commutative byte-pointer `i[p]`
subscript/pointer expressions, but correct native register evaluation
order is still absent (48/92 nonfield). All negative sources remain
intact under `.analysis/f505-scene-release-248/`,
`.analysis/f506-replay-draw-scope-layout/`,
`.analysis/f507-scene-true-ownership/` and
`.analysis/f508-progress-reversed-subscript/`. No partially matching
CODE or data was credited.


## F514: complete 303-byte original Replay filename glyph renderer now exact, real native `/GS` stack layout

The formerly long-pending R053 authored original
`ReplayScene::DrawSaveFilenameAt0042C270` is now **303 full original
CODE bytes /88 native x86 instructions**, original pinned PE SHA256
`3d024dbba42ae48c3f1b00881cf366e40b38c9c10bb795db174f8d471da48130`.
The complete pinned VC7.1 `/Od /Ob0 /Gy /GR- /GX- /GS /Zi`
source `src/ReplaySceneDrawSaveFilenameF514.cpp` matches all **255/255
original nonrelocation bytes and the exact authentic 12/12 physical
COFF DIR32/REL32 fields/symbols/actual original PE destinations**
(including four actual original constant-prefix addends). The *only*
affected `--unit replay-scene-draw-save-filename-0042c270` was cold
recompiled and replayed **1/1 exact**.

The original full native `/GS` EBP layout is **0xAC**: actual scene
owner at EBP-0xAC, **14 bytes of meaningful replay filename prefix**
plus 2 bytes of ordinary compiler member alignment beginning EBP-0xA8,
real **132-byte drawable quad** at EBP-0x98, and separately *used*
**8-byte glyph array at EBP-0x0C..-0x05**, with true VC7.1 stack
security cookie at -4. The two original source objects have different
C++ lifetimes: **prefix and quad share one meaningful C++ aggregate**
with actual physically 16-byte prefix storage and previously proven
real 132-byte quad packet, while the original glyph buffer is an
**independently declared char[8] local**, not a member of quad. This
forces the original compiler GS buffer placement and native physical
read/write offsets without any artificial filler, guessed 140-byte
packet or hand-inserted cookie.

Natural original prefix copying reads the real observed read-only
`replay\replay` byte string from original PE `00657F9C` in exactly
three DWORDs and one final WORD at physical addends **0,+4,+8,+12**.
The original `memcmp` at `00641F00` compares the first 13 prefix
bytes with the actual caller's signed filename. A matching prefix
yields glyph bytes `13,40,71,(signed filename[13]+4),
(signed filename[14]+4),(signed filename[15]+4),100,100`.
The nonmatching branch yields `20,44,30,43,100,100,100,100`.
**Each branch separately calls actual original DrawCharacters
`0042C150`** with real source x/y floats, tint and glyph bytes; the
compiler produces two physical COFF REL32 calls with independently
verified original PE destinations. The real quad constructor
`0040DA00`, float constants `0065786C`/`00657F78`, `memcmp`, actual
`__security_cookie` at `0066FE30` and `__security_check_cookie` at
`00640611` are all genuine original references.

Historical F323/F424/F425/F441–F444 probes were nonexact and merged
the two real draw branches or placed prefix/glyph arrays at wrong
physical offsets. F506 tested drawing per branch but incorrectly
arranged the three used objects, emitting 342 bytes. F510 combined
quad and glyphs and moved actual glyphs to EBP-0x24. F511/F512 grouped
all three and recovered 303 bytes but only **237/255 nonfield bytes**
were matching, all 18 offending bytes due actual glyph at -0x14 vs
native -0x0C. F513 grouped prefix+quad but separately declared glyph
**scalar fields** and put the genuine /GS cookie at -0x0C, with
glyphs at -0x08, wrong. F514 source instead leaves **both real prefix
/quad aggregate and genuine glyph char[8]** as distinct separately
protected source locals, restoring every original stack slot naturally.
All past probes remain safely retained under ignored `.analysis/`
directories as negative controls; the full original **303 CODE bytes
are now exact and separately credited exactly once**, not any borrowed
external CRT, renderer or quad code. No original bytes/ASM graft,
assumed private owner fields, fake locals, masks, cropped original,
all-unit cold replay or external Oracle receipt.


## F516: independently complete native 169-byte NameEntry and Result rank-glyph draw routines, original `/GS` and two separately real DrawGlyphs targets

Both long-pending independently authored original-game rank/decimal label
functions are now **complete cold exact** in natural pinned MSVC7.1:

- R109 `NameEntryScene::DrawDecimalGlyphLabelAt0042B110` is exactly
  **169 whole original native CODE bytes /53 original x86 instructions**,
  original PE SHA256
  `317ab6d10009cc492ff3603c897cabf0a4336b08a46981e0ab171e76e05ed573`,
  with **145/145 original nonrelocation bytes and all 6 genuine
  physical COFF DIR32/REL32 fields** including its separate borrowed
  native `DrawGlyphs` call at `0042AFF0`.
- R043 `ResultScene::DrawRankLabelAt00431890` is separately exactly
  **169 original CODE bytes /53 original x86 instructions**, native
  PE SHA256
  `078d897d1bb5ef0ec1e167d819a4fd07617a237a48c25f1f7d19b38bb24a3837`,
  with independently checked **145/145 original nonrelocation bytes
  and all 6 genuine physical COFF fields**, including its distinct
  borrowed native `DrawGlyphs` call at `00431770`.

The original C++ meaning is straightforward (float x/y and unsigned
tint, plus original **signed char** rank): construct the native quad
with x/y and actual global width/height constants `00657F78` /
`0065786C`, set original 8 glyph bytes to
`13,40,71,(signed rank / 10+52),(signed rank % 10+52),100,100,100`,
and invoke the scene's original distinct DrawGlyphs method with x/y,
tint and the actual byte array. The rank quotient and remainder use
real original x86 `MOVSX; CDQ; IDIV 10` separately; folding or
unsigned operators would change native byte behavior.

Previously F472/F475/F476/F495/F510 could obtain the complete native
169-byte code and arithmetic but assigned glyph data to EBP-0x14, or
removed the original `/GS` cookie to place glyphs correctly, or
changed actual quad C++ object type/lifetime and generated 196/202
bytes. The key genuine source distinction, discovered after solving
F514 Replay glyph draw, is to represent the actual **132-byte quad as
a member of its own *used* C++ aggregate** with the borrowed native
`ConstructNative` entrypoint (physically original quad constructor
`0040DA00`), but place the meaningful real `unsigned char glyphs[8]`
as a **separately declared live local**. With pinned VC7.1
`/Od /Ob0 /Gy /GR- /GX- /GS /Zi`, this naturally produces the
original complete **0x9C** stack frame, `this` EBP-0x9C, real quad
constructor receiver EBP-0x98, eight glyph values EBP-0x0C..-0x05,
and original `/GS` security cookie EBP-4 with true callback check at
`00640611`. The original 6 authentic physical COFF fields in each
function include global cookie `0066FE30`, actual original float
constants, quad constructor, *separately original* glyph target
and real security check.

The single natural source `src/NameEntryResultRankGlyphLabelsF516.cpp`
generates both separate whole 169-byte bodies in one object, and a
**single changed-only cold replay** of precisely the two unit names
`nameentry-scene-draw-rank-glyphs-0042b110` and
`result-scene-draw-rank-glyphs-00431890` passed **2/2 exact**. Exactly
**338 new original authored CODE bytes** are credited without
counting the borrowed original quad, GDI/game renderer, CRT or
security-check code. No source assembly, pasted native bytes, false
class layout, fake locals/padding, relocation masks, shortened
original CODE, full-project replay or external Oracle acceptance.


## F520: all 22 original fighter-action bosses verified as complete 1,102,055-byte CODE cohort (research, NOT exact)

Pinned original Japanese TH075 PE has exactly 22 still-unaccepted
independently R-origin authored fighter action/advance bosses in the
reviewed 28,432–82,796-byte size class. Their **whole original CODE**
amounts to 1,102,055 bytes, **292,761 original x86 instructions**,
**16,861 original call sites** and **84 genuine native indirect JMP
instructions**, all verified through the full final `RET` per function.
The **2,359 authentic original post-RET DWORD slots (9,436 DATA bytes)**
and **6,687 bytes of original sparse byte-index maps** together form
**16,123 genuine physical switch DATA bytes**, separately validated
and excluded from authored CODE coverage. Eleven CharacterObject-family
bosses each have one indexed jump +198–200-byte native index map.
Eleven CharacterMove/Reimu-family bosses have six (two functions) or
seven (nine functions) native indexed jumps. Complete per-function PE
CODE SHA256, physical after-RET table/mapping SHA256, stack allocation,
instruction/real call counts, exact original native instruction-aligned
DWORD targets and post-RET CC padding have been independently frozen
in `config/fighter-boss-dispatch-fingerprints.json`, checked against
the target by `scripts/repo-python scripts/verify-fighter-boss-family.py`.

Four actual *byte-identical* sparse index groups recur across different
original bosses (original map lengths and copy counts: **49×8, 68×8,
49×3 and 66×2**). The two 49-byte maps are different SHA256 values;
shared byte-index maps do **not** imply shared original native DWORD
CODE destinations. Original physical DWORD tables can intentionally
have duplicate default/epilogue addresses; the new verifier does not
repeat an earlier mistaken uniqueness assumption and instead validates
**every original DWORD target** against the entire original decoded
CODE instruction boundaries. Full audit and exact cohort table are
in `docs/FIGHTER_BOSS_FAMILY_DISPATCH.md`, alongside existing individual
whole Reimu R063 and CharacterMove R048 original reports. Each of the
22 giant functions remains **unreconstructed source and nonexact**;
this is evidence for future whole C++ implementation, **0 new CODE
credit**, no borrowed caller/callee/after-RET DATA double-credit, no
source native byte graft, no synthetic locals, and no full cold replay.


## F525–F531: entire 2,987-byte WinMain C++ lifetime/control reconstruction advances, still NOT exact

Original whole WinMain R113 verified native 2,987 CODE, 654 x86
instructions, 123 calls, stack 0x278 and original 15-scene switch DATA
unchanged. Native original archive catalog has distinct true local ctor
0041CE10 and nonvirtual dtor 0041CE50 at EBP-0x35. Local game-data
resource has ctor 00417210/dtor 00417430 at EBP-0x36. Three original
0041CF80 calls at +0x2C1/+0x2D3/+0x2E5 are native *two-argument
cdecl*, not archive instance thiscalls: every original call takes two
PUSH arguments and an ADD ESP,8. Native global object 006718F8 has
instance methods 00416B10/004169E0, original MOV ECX,006718F8
before each. The first Scene4 ctor result is actually stored to
EBP-0x19C before moving into the live scene pointer EBP-0x184. The
native initial scene state is unsigned short at -0x3C, and original
outer message loop executes literal MOV ECX,1; TEST ECX,ECX; JE
(branch must exist even though while(1) is always true). A single
PeekMessageA if/else pump is nearer original than nested repeats.

Pinned VC7.1 full-function F525 genuine three early failures restore
626/654 original ordered instruction mnemonics; F526 natural flat
message pump 639/654; F527 real archive/game-data C++ automatic lifetime,
three cdecl archive opens and two global Replay thiscalls 649/654. F528
full natural C++ `outer0-firsttmp1-while1.cpp` reproduces **654/654
original instruction mnemonics in exact order, 123/123 calls, and
original 0x278 stack**, but CODE only **2,981 vs original 2,987**.
The per-instruction original operand/size comparison at
`.analysis/f528-winmain-native-initial-scene/detailed-insn-alignment.tsv`
shows just **224/654** fully matching mnemonic+operands+length and
**430 operand/length discrepancies**. Most important originals: app
mode at EBP-0x3D versus source -1, graphics at -0x189 versus -0xD,
input/sound at -0x62/-0x61 versus source -0x15/-0x16, active scene
at -0x184 versus -0xC, module pathname at -0x180 versus -0x158.
F528 another natural source emits 2,987 bytes but 656 instructions
due an extra scene null test, not exact. F529 scopes of actual PODs
and F530 meaningful actual scene+path+HWND aggregate fail to restore
native local stack positions, some aggregate hypotheses generate 3,113
CODE. These are all real complete C++ source probes, **none counted
as native CODE**; original comparisons are not masks or partial cuts.
`scripts/repo-python scripts/verify-winmain-scene-dispatch.py` now
read-only attests the above concrete original PE ctor/dtor/ABI/loop
evidence, along with the previously checked original whole CODE,
15 native switch cases and all four true early/success cleanup chains.
See expanded `docs/WINMAIN_ORIGINAL_CONTROL_FLOW.md`; archived local
evidence `.analysis/f523-winmain-lifetime-structure/` and F525–F530.

## F521–F524: historical progress counter negatives, solved by F535; F531 archive lifetime remains nonexact

Original authored GameProgress::IncrementSelectedRecord at 00425130
is **92 full CODE bytes** and has no COFF relocation fields. Natural
source prefix increment `++SELECTED_COUNT` generates 92 bytes and
**70/92 original nonfield bytes** (versus 48/92 for the earlier
assignment expression). Correct final store uses exactly original
physical registers, but its read still computes fighter+0x16AC4
×0x17F0 before difficulty+0x16AC5 ×0x5FC, whereas native read
computes difficulty FIRST and adds owner to the fighter offset. Thirty
F521 genuine expression/lvalue variants, twelve F522 real member and
qualifier variants, eight F524 physically observed 15 fighter records
plus opaque 0x3B0 owner tail tried under original VC7.1; none restores
whole 92. Several `volatile`/typed variants emit 68 or 100–102 bytes.

Original ArchiveCatalog::ReleaseAt0041CE50 is now independently
confirmed by whole WinMain call/receiver as the actual catalog
*nonvirtual C++ destructor* of local at EBP-0x35, paired with ctor
0041CE10. Eight F531 natural original destructor-source variants under
pinned VC7.1 yield full 171 CODE only for nonvirtual dtor, but
**108/115 original nonrelocation bytes match**, seven EBP-slot errors
in actual resource/delete/filename temp lifetimes remain. Virtual
destructor emits 182 CODE and is false for this original entry.
These remaining functions are still **unaccepted**, no partial source
CODE/borrowed callee credit, no artificial locals or all-unit replay.


## F535: genuine complete 92-byte GameProgress native selected-record postfix increment, 1/1 cold exact

The independently original R103-authored full function
`GameProgress::IncrementSelectedRecordAt00425130` at `00425130..
0042518B` is now **92 original authored CODE bytes /24 genuine x86
instructions**, original PE SHA256
`0fb4c8bcd359efb606e39a0f39282fe764abcb7fbb2c7ebbd38699a100e8dd89`.
Source `src/GameProgressIncrementSelectedRecordF535.cpp` is natural
complete C++ with the two **physically real signed 8-bit selectors**
owned at this+0x16AC4 (fighter) and this+0x16AC5 (difficulty),
actual per-fighter `0x17F0` stride and per-difficulty `0x5FC`
stride. The resulting original DWORD record counter is at
`this + (fighter × 0x17F0) + (difficulty × 0x5FC) + 4`.

**Decisive native source spelling:** the whole original uses source
**POSTFIX `SELECTED_COUNT++`**, not the equivalent-in-result
`++SELECTED_COUNT` or `SELECTED_COUNT=SELECTED_COUNT+1`. Under the
verified pinned VC7.1 `/Od /Ob0 /Gy /GR- /GX- /GS /Zi` profile,
postfix++ generates the original first read evaluation *difficulty
first* (`MOVSX ECX,[this+0x16AC5]`, `IMUL ECX,0x5FC`), then fighter
second (`MOVSX EAX,[this+0x16AC4]`, `IMUL EAX,0x17F0`), then `ADD
EAX,[ebp-4]`, `MOV ECX,[EAX+ECX+4]` and `ADD ECX,1`. The later
store evaluates difficulty in EAX, fighter in EDX, adds the actual
owner to EDX and writes `[EDX+EAX+4]`; the compiler produced both
original read and store exactly. Natural prefix++ generated native
store half correctly but read half in a different order (**70/92
original nonfield bytes**); explicit assignment yielded only 48/92.
The F478/F497/F498/F508/F521/F522/F524 type, real 2D array,
commutative indexing and volatile hypotheses therefore remained
nonexact despite reproducing the same game state semantics. F534
changed real VC7.1 CPU/profile flags (G5/G6/G7/Ob1/Op) without
solving prefix++, and actual O1/O2 optimization shortened the source
to 30 bytes. F535 tested fifteen real C++ statement spellings and
found that either plain postfix++ or `static_cast<void>(...++)`
produces the complete **92/92** original bytes. This is a source
syntax/VC7.1 codegen difference, not a fabricated register or stack
local.

The code contains **zero actual native PE/COFF relocations**, no
borrowed game functions, and its entire source's **92/92 bytes**
were compared as original CODE. A fresh
`scripts/repo-python scripts/replay-exact-units.py --unit
game-progress-increment-selected-record-00425130` returned **1/1
exact**, rebuilding only its own object. The first attempted targeted
compiler run was interrupted, and its actual dirty manifest/source
were preserved and finished on the next call without any reset.
Only **92 newly exact original CODE bytes** are credited, no partial
original, masked relocation bytes, source ASM, native-byte graft,
false full private class layout, full all-unit cold replay or
external Oracle receipt.


## F536: complete 111-byte original game-coordinate transform, 1/1 cold exact

The formerly R263 origin-pending `00455770..004557DE` entire original CODE
(111 bytes, 29 contiguous Capstone instructions, original SHA256
`f32fa773f34571f1d1b95bf812e1f1c7af10337df50d5af02a11cd0ac983573f`)
receives two native floats on the stack and terminates with `RET 8`. It has
no native calls or indexed jump tables; the next function starts at `004557E0`.
Its actual four borrowed receiver float fields are +0x2D8, +0x2DC, +0x2E0,
and +0x2E4. Two genuine local float differences are stored at EBP-8 and
EBP-4, and the receiver at EBP-0xC. It transforms x via `(x - left) /
(right - left)` scaled by original global `00657884`, stores at `006714A8`,
then transforms y via `(top - y) / (top - bottom)` scaled by original
`00657D10`, stores at `0067142C`. Both original outputs have one actual
code reference apiece (these stores); nothing establishes the intended
runtime invocation, full owner type, or original variable names.

This whole custom receiver-bound game-coordinate policy cannot arise from
an ordinary implicit C++ copy/destroy lifecycle or standard library math
wrapper. It was conservatively reclassified as inferred authored F536,
reducing origin review from 97/3,608 to 96/3,497. **The original has no
discovered direct callers or literal function-pointer reference**: do not
claim execution, runtime reachability, or a known class/vtable owner.
`src/CombatCoordinateViewF536.cpp` exposes only a borrowed thiscall interface,
not a manufactured private owner layout or singleton.

Pinned VC7.1 cold compilation of that complete source reproduces all
**95/95 non-relocation bytes** and every authentic physical COFF DIR32 at
relative offsets **0x44, 0x4A, 0x5F, 0x65** resolving to the original
**00657884, 006714A8, 00657D10, 0067142C**. The crucial source form is
an *unparenthesized* float lvalue `FIELD(offset)`; otherwise VC7.1 emits
`fld` before the second native owner load and reverses the first x87
subtraction, producing 69/95 comparable rather than all 95. Original
function extent, all four relocation fields and native x87 order were
independently decoded from the supplied hash-pinned Japanese PE, not from
the legacy inventory or Ghidra guesses.

Acceptance: `scripts/repo-python scripts/replay-exact-units.py --unit
combat-coordinate-view-map-world-to-screen-00455770` returned **1/1 exact**
from a fresh standalone object; there was **no full cold replay**, code
byte copying, manual ASM, masked fields, partial boss credit or external
Oracle acceptance. The ArchiveCatalog real nonvirtual destructor at
`0041CE50` was also investigated: natural resource-pointer locals, comma
expression sequencing, name/reference ABI alternatives and lexical scopes
under the pinned compiler failed to improve the genuine 171-byte,
108/115 nonfield byte baseline. These controls are retained under
`.analysis/f536-archive-and-boss/` and must not be called exact.


## F537: physically resolved action-ID dispatch for all 22 full giant fighter bosses

Previously recorded post-RET DWORD tables and sparse indexes were insufficient
to pick original native handlers for arbitrary action IDs. F537 now independently
decodes the complete native `SUB` base / signed-state local / `CMP` unsigned
bound / `JA` default / sparse `MOVZX` / final indexed `JMP` instructions of
**all 22 full original 28–82K CODE function bodies**, separately checks all
whole-original native CODE and switch DATA SHA256 identities, and uses the real
`CMP [state], action; JE native_target` pairs for nonindexed special actions.
This resolves **7,088 indexed action IDs + 64 singleton actions = 7,152
per-boss native-entry mappings**; the resulting deterministic CSV SHA256 is
`3a265d8d4c44fe0672fb8f8184bce18775d36a80ad4707134ed5b3ccc6e08b08`.
**4,847 of the indexed IDs deliberately route to their boss's actual JA
default entry**, while 2,241 route to other original instruction entries.
Reimu 0045DD70 and CharacterMove 004AC040 each have the same full set of
548 physically tested action IDs, but their singleton/indexed classification
*differs* at IDs 0x254 and 0x25B; never borrow their case-entry addresses
or unverified complete owner types. Source-facing evidence and all 22 per-boss
ranges: `docs/FIGHTER_ACTION_CASE_RESOLUTION.md`, executable verifier:
`scripts/repo-python scripts/report-fighter-action-handlers.py`. Each original
case target is an in-function instruction or native default, not a separately
credited function. There is **no new giant-boss exact C++ or CODE/DATA credit**,
no all-unit cold replay and no external Oracle receipt.


## F538: eleven full native action-zero cases, shared instruction sequence but different encodings

Original CODE inside all eleven *whole* multi-switch fighter bosses was
independently read using each original dense table's first two genuine
handler addresses as boundaries. Every action-zero case comprises the
**same full sequence of 50 native x86 mnemonics**, with 18 x87-related
instructions, three original `00453E20` calls, 14 physical receiver
reloads, and real +0x3AC flag/+0x50 position and x87 constants
`0065782C`, `00657478` and `00658050`. Ten original cases are 180
bytes; the `00564BE0` case is 222 CODE bytes because its native receiver
EBP-0x88 needs disp32 in all fourteen loads, adding exactly 42 bytes.
This is a concrete compiler/layout constraint for subsequent **whole
boss** natural C++ reconstruction. Every real per-boss case SHA256 and
physical original boundary is recorded in
[the F538 eleven-case study](FIGHTER_ACTION_ZERO_NATIVE_LAYOUT.md),
and is verified in the updated
`scripts/repo-python scripts/report-fighter-action-handlers.py` original
PE-only runner. The 7,152-row F537 action index SHA256 is unchanged.
**No whole boss C++ rebuilt, no accepted CODE/DATA credit or all-unit
cold replay.** The existing 942 exact-unit register remains unchanged.


## F539: natural C++ switch recovers native compiler-lowered giant dispatch

This goes beyond F537 raw PE mapping. Using the complete original F537 native
case-ID set, **one** ordinary VC7.1 C++ switch with 143 Reimu /151
CharacterMove nondefault+singleton cases naturally reproduces the **exact
66-instruction/325-byte original control dispatch grammar** of both original
60,999-byte/82,796-byte bosses; this is *not* an actual CODE byte match,
because stack displacements and external branch/code addresses differ. All
**522 native sparse index bytes per boss are exactly repeated** by the
compiler, and the after-RET table layout is 1,090/1,126 native bytes with
142/151 authentic local `DIR32` COFF destination refs. All physical DWORD
slot default/nondefault and equivalence partitions agree with the original.
The codegen hypothesis crucially uses a combined short-circuit guard and
a direct source `switch(I16(0x60))` instead of a redundant `int action`
copy; separate-guard and extra-local alternatives are retained in ignored
`.analysis/f538-fighter-natural-switch/`. The generated case bodies are
*distinct placeholder stores*, not original authored fighter C++ code. The
source/probe generator and its fresh native/compiler verification are in
`scripts/repo-python scripts/verify-fighter-natural-switch-probes.py`,
with full report in `docs/FIGHTER_SWITCH_CODEGEN_RECONSTRUCTION.md`.
The full bosses remain entirely nonexact. No invented CODE/DATA credit, no
all-unit cold replay and no external Oracle receipt.


## F540: first real natural C++ action case inside all 11 giant fighter bosses

F538 fully checked the 50-instruction native action-zero case in eleven giant
originals, and F539 cold-compiled the real single-switch dispatcher for two
of them. F540 builds on that verified original data with a natural VC7.1
C++ **action-0 body**: signed-byte flag at receiver +0x3AC, float position
at +0x50, four real float threshold observations (`0065782C`), one float
subtraction (`00657478`), one **double** rise (`00658050`), three real
`00453E20` thiscall sites, and two distinct sequential float range guards
that preserve x87 `JP`/`JNE` unordered semantics. Reimu and CharacterMove
fresh local compilation each achieve **50/50 complete x86 action-case grammar,
180/180 source-to-original length, identical original register allocation,
9/9 physical COFF reference roles**. Native-only analysis extends this
exact source expression/control graph to **all eleven original 50-insn cases**
with verified register dataflow and 10 ×180-byte vs one true 222-byte
(14 widened owner reloads at EBP-0x88) physical widths. The C++ builds
remain *case probes*, not full 60K/82K originals: their stacks and actual
branch/call relocations do not byte-match and there is **no accepted giant
CODE or split-function credit**. See `docs/FIGHTER_ACTIONZERO_SOURCE_RECONSTRUCTION.md`
and `scripts/repo-python scripts/verify-fighter-actionzero-natural-source.py`.
No full cold replay or external Oracle receipt.


## F541: eleven independently recompiled original-style fighter action-zero cases

The F540 two-source action-zero hypothesis has now been freshly compiled
**separately for every one of the eleven 6/7-table original giant fighter
controllers**, each using its *own* native action-ID case vocabulary rather
than Reimu's switch layout transplanted to other fighters. All eleven
natural C++ compiler outputs achieve **50/50 original action-zero x86
mnemonics, exact real per-fighter EAX/ECX/EDX register allocation,
comparison/x87 operand roles and control-flow edges**; every one retains
**nine genuinely typed case COFF fields**. The complete native bosses
(613,391 CODE bytes total) are independently verified before each
comparison. All 11 individual switch COFF objects additionally match
**1,607 physically real table-slot references**, all original repeated
case-target/default partitions, **4,502/4,502 exact sparse index bytes**
and **10,930 real post-RET DATA-shape bytes**.

The `00564BE0` original action-zero case is **222** vs source-probe
**180** machine bytes because the real parent giant stores receiver at
EBP-0x88: fourteen disp32 reads explain +42 genuine bytes, and the
isolated small probe does not manufacture an owner frame or fake padding.
The natural C++ action-zero source for other ten emits 180 original-length
bytes, still not relocation/stack-exact inside the complete original
fighter. See [F541 eleven-giant case-codegen study](FIGHTER_ACTIONZERO_FAMILY_CODEGEN.md)
and changed-only reproducer
`scripts/repo-python scripts/verify-fighter-actionzero-natural-source.py`.
**No full boss reconstructed, no new exact CODE/DATA credit, no all-unit
cold replay or external Oracle acceptance.**


## F542: real action-one gameplay C++ case, eleven independent complete giant contexts

Each native multi-switch fighter boss's first switch DWORDs physically
bound a **full original 60-instruction action-one case**, 212 CODE bytes
in ten bosses and 263 CODE in the original `00564BE0` case. The 263-byte
variant has seventeen genuine EBP-0x88 owner reloads that widen disp8 to
disp32, exactly 51 additional native bytes. This is *not* a separate
function. In addition to F541's real action-zero x87 control, action one
performs `GetNativeActionAt40FA30()` (returns native signed short), compares
against the real signed 16-bit `this+0x70`, and conditionally invokes
`SetNativeActionAt40FAC0(2)` with natural C++ operand ordering.

A new reproducible verifier fresh-compiles *eleven distinct* natural C++
switch prototypes against each corresponding independently full-PE-checked
boss: **660/660 true action-one mnemonics and real per-fighter register/branch
operand roles, 121/121 physically genuine typed case relocations**,
1,607 correct native-style DWORD COFF refs/whole-table target partitions,
4,502 byte-identical original sparse action indexes and 10,930 original
post-RET DATA-layout bytes. Source semantics and precise per-boss table
are at [F542 action-one study](FIGHTER_ACTIONONE_FAMILY_CODEGEN.md),
replayed *only for selected new probes* with
`scripts/repo-python scripts/verify-fighter-actionone-natural-source.py`.
**No giant whole-function exactness, no credited partial CODE/DATA, no
full cold replay and no external Oracle receipt.**


## F545: all six early action C++ cases across eleven original whole-giant fighters

F545 independently compiles eleven full-native-switch natural C++ probes,
each now implementing **all six complete original actions 0..5** instead
of source-marker placeholders. Each of the 11 giant original functions
is fully SHA-pinned first, and all original first-switch DWORD case
boundaries, CODE and after-RET DATA are checked. The **2,486/2,486**
case instructions and **440/440 actual case COFF fields** have correct
per-fighter x86 GPR selection, native x87 semantics, call arguments,
branch graph, and the genuine native action4/5 immediate float values.
**Do not assume positive and negative action-speed symmetry**: original
`005D73C0` stores +6.0f at action 4 but -4.5f at action 5. Original
`00564BE0` has a 192-byte excess across its original first-six cases
(1006 vs generated 814) caused exactly by 64 physical disp32 owner
reloads at `EBP-0x88`; the source generator never adds fake padding.
All **1,607** original switch DWORD COFF refs, **4,502** literal original
sparse index bytes, 10,930 original after-RET DATA-layout bytes and
handler-partition equivalence also agree. The **9,146** original CODE
bytes of these six-case inner subranges remain part of 613,391 giant
whole-function bytes, **NOT accepted partial function CODE**. Full
per-boss evidence and reproducer:
[the F545 natural six-case source study](FIGHTER_OPENING_SIX_CASES_CODEGEN.md)
and `scripts/repo-python scripts/verify-fighter-opening-actions-natural-source.py`.
No whole boss exact, all-unit cold replay or external Oracle claim.

## F544: bounded new compile-profile controls for nonexact archive destructor

The independently original authored **171-byte ArchiveCatalog nonvirtual
RAII destructor at 0041CE50** still has exactly seven genuine local EBP
slot discrepancies against natural C++ baseline (108/115 nonrelocation
bytes, all 14 correct physical COFF reference locations). F544 freshly
compiled the entire source under pinned VC7.1 with both `/Zc:forScope`
modes, `/GX` versus `/GX-`, `/GS` versus `/GS-`, `/Z7` versus `/Zi`,
`/Za`, `/Zp8`, `/J`, and `/Ob1` controls to test whether the historical
mismatch was just an unjustified profile assumption. All ten
noninlining profiles emitted **the same 171 bytes and same seven
stack-slot differences**; `/Ob1` emitted **197** and cannot be compared
as an exact 171-byte body. The debug-free one emitted no standalone
function symbol and supplies no credit. Detailed cold probe code, full
COFF comparisons and logs remain preserved under
`.analysis/f544-archive-flags/`. No wrong-profile conjecture is accepted,
and no negative probe is counted as new exact coverage. A real source-local
lifetime change, not bitwise patching or artificial stack padding, remains
necessary for this destructor.


## F546: native scene virtual destructor real-lifetime negative controls, still NOT exact

Revisited the original R054 authored `0043B0B0` **complete 248-byte
SceneObject virtual destructor**, without altering its source mapping or
claiming accepted CODE. The native whole function has 75 x86 instructions,
12 real COFF fields and original EH/scene ownership. The best 248-byte
pinned `/GX` VC7.1 natural C++ baseline retains **191/200 true
nonrelocation bytes**, with nine real EBP slot/allocation differences.
Ten additional full-body natural source probes tried meaningful texture
pointer scope/const/type and genuine freed-pointer aggregate array/field
orders, not synthetic padding, fake side effects or code copying. Scoped
texture names yielded 254 or 251 CODE bytes, and the best whole-length
object remained **191/200**. Entire failed sources, native COFF objects
and comparisons are preserved under `.analysis/f546-scene-lifetimes/`.
No 248-byte exact unit or author-byte credit was registered.

## F547: natural 42-instruction fighter action-nine source in all eleven giant contexts

Fresh pinned VC7.1 compiled eleven different original-PE-backed switch
probes, each now including a **full actual native action-nine case** beyond
F545's six opening cases. Original case bounds come from the real tenth
and eleventh DWORD table targets of the *complete original huge fighter*.
Each source emits **42 original instruction kinds, native x87 comparisons,
member offsets/branches/exits and 6 real physical COFF call/global fields**.
Six probe cases also have exact native EAX/ECX/EDX register assignment;
**five still have different real GPR allocation**, so do not call them
register-exact. Original auxiliary helper `0040FB40` gets **1** in the
`00543210` boss but **0** for the other ten; this was physically validated
as native `PUSH 1` and carried into natural C++. Original special
`00564BE0` case length 183, versus 144 source-probe bytes, is accounted
for by 13 genuine widened owner EBP-0x88 loads. The eleven cases contain
**1,623 original CODE bytes**, but these remain inside incomplete full
fighters, with zero separate exact credit. All eleven per-boss original
switch-table equivalence partitions, **1,607 DWORD COFF fields**, 4,502
original sparse index bytes and complete 10,930 after-RET DATA shape
remain checked. Read [F547 codegen evidence](FIGHTER_ACTIONNINE_FAMILY_CODEGEN.md)
and reproduce only affected compiler probes with
`scripts/repo-python scripts/verify-fighter-actionnine-natural-source.py`.
No full cold replay, giant exact CODE or external Oracle receipt.


## F548: native 104-instruction C++ action-six, three whole fighter bosses

The original first switch seventh/eighth native destination DWORDs bound
**362 complete CODE bytes /104 actual instructions** in each of Reimu
`0045DD70`, the `0058AF60` fighter and the `005D73C0` fighter. Their
entire original parent CODE and all post-RET jump DATA are SHA-pinned
and checked separately. Natural C++ reproduces the full signed two-stage
fighter frame policy, x87 motion, two genuine `0040FAC0` calls, two
`00453E20` calls, two authentic physical `0065782C` float references,
and the **true original indirect owner virtual vtbl[0] call**.

These three have genuine per-character behavior differences: Reimu
uses stage2 and `12.5f /0.55f`; `0058AF60` uses stage4 with
`12.5f /0.55f`; `005D73C0` uses stage2 and `14.0f /0.7f`.
Three serially fresh compiled natural C++ probes reproduce
**312/312 original x86 mnemonic/length/real GPR/x87/control roles**,
**18/18 native physical call/constant COFF fields**, and the original
indirect vtbl[0] call sites. Their physical switch data includes
422 valid native-style DWORD COFF fields, 1,323 literal original
sparse index bytes, 3,011 original post-RET DATA-layout bytes and all
destination equivalence partitions. Complete source-based witness:
[F548 fighter action-six study](FIGHTER_ACTION_SIX_FAMILY_CODEGEN.md),
with `scripts/repo-python scripts/verify-fighter-action-six-natural-source.py`
for affected-only native+compiler proof. These are parts of still-unmatched
153,511 giant CODE bytes: **no source-accepted 1,086 internal CODE bytes**,
no arbitrary stack padding, no all-unit cold replay, no external Oracle.


## F549: original fighter action 10 split into 31-/20-instruction natural C++ families

In each original fighter, the physical first-switch case-10 DWORD through
the native singleton action `0x32` entry bounds one full action-10 case.
Nine originals have a real signed-short `this+0x62/+0x64 == 0` gate and
`00453D60(30)` call, followed by `00453E20` reset and original
`0040FA30` state comparison with `this+0x70`, and a zero/nonzero DWORD
`this+0x4E0` branch to `0040FAC0`. Two other entire original cases
(`005214B0`, `00564BE0`) truly omit that preliminary guarded call.
Character-specific native transitions are **0/2** (three), **3/2** (three),
and **0/1** (five). They are actual literal original PUSH arguments, not
assumed uniform metadata. All eleven fresh natural VC7.1 C++ probes have
**319/319 case control/mnemonic structures, 53/53 physical COFF REL32
call fields**, 1,607 authentic native-style DWORD table references and
4,502 byte-identical native sparse bytes. GPR identity only matches 6/11;
all 11 retain receiver/thiscall dataflow and roles. The exceptional
`00564BE0` is 87 versus 69 candidate bytes due to 6 original disp32
EBP-0x88 reads. See [F549 complete native action-ten case study](FIGHTER_ACTIONTEN_NATIVE_CPP.md)
and `scripts/repo-python scripts/verify-fighter-actionten-natural-source.py`.
**1,065 original interior CODE bytes, not a whole boss/function exact
match; no new accepted CODE/DATA, full cold replay or Oracle receipt.**


## F551: three newly reconstructed original action-seven C++ cases

Whole-original PE case 6/7/8 DWORDs delimit complete **362-byte, 104-
instruction** native action 7 in Reimu `0045DD70`, `0058AF60`, and
`005D73C0`. Independent original byte/instruction comparisons show only
three source-policy differences from their previously compiled exact-shape
action 6: unsigned frame-state +0x511 tests 5 rather than 3, native
`0040FAC0` receives 0xCD rather than 0xCC, and `this+0x50` position
initializes 4.0f/4.0f/6.0f. No uniform fighter float is assumed.

Three fresh natural VC7.1 compiles preserve both full native action
6 and 7 **624/624 original GPR/x87/branch instructions**, all **36
physical call/global COFF fields**, true vtable indirect call form,
422 correct native-style jump DWORD refs and 1,323 original sparse bytes.
The two original cases comprise **2,172 interior CODE bytes** inside
still-unmatched 153,511 CODE of the three whole bosses, not three exact
independent functions. Reproduce with
`scripts/repo-python scripts/verify-fighter-action-seven-natural-source.py`;
full native source audit:
[F551 two-case study](FIGHTER_ACTIONSEVEN_NATIVE_CPP.md). No credited CODE,
full cold replay or Oracle receipt.


## F553: real action-eight sources expose missing flag-clear in one fighter

Full original first-table DWORD bounds show 104/104 instructions and
362 bytes for native action 8 in Reimu `0045DD70` and `005D73C0`, but
**only 102 native instructions /352 bytes for `0058AF60`**. All three
perform original byte-state test `this+0x511==4`, pass 0xCE to original
`0040FAC0`, and initialize `this+0x50=-4.0f`; unlike the other two,
`0058AF60` truly omits a `FLAG = 0` write. The natural C++ source omission
reproduces the physical original code without fake padding or ASM.
Three newly rebuilt selected native C++ TUs now check **complete actions
6, 7, 8** together: **934/934 actual native GPR/x87/branch instructions,
54/54 real COFF call/float fields**, 422 physical native-style DWORD
jump refs, 1,323 literal original sparse indexes and full original
3,011 after-RET DATA-shape bytes. The 3,248 inner-case CODE bytes remain
inside the 153,511-byte unmatched original giant functions. See
[F553 whole-native action-eight study](FIGHTER_ACTIONEIGHT_NATIVE_CPP.md)
and `scripts/repo-python scripts/verify-fighter-action-eight-natural-source.py`.
No new exact CODE/DATA, all-unit replay or external Oracle acceptance.


## F555: corrected original-only font classifier provenance, full cold-exact code

The historical R183 frozen original-PE evidence had retained `0041CA30`
(77 CODE, 28 x86 instructions) as *origin unknown*, since both standalone
and member C++ policy observers were 77-byte matches. F555 independently
re-reviewed the **real sole original caller** `0041C9D0`, itself 85-byte
previously exact authored game FontSurface text decoding, and its genuine
`REL32` call to `0041CA30`. Unlike the SDK `_ismbblead` table macro, this
original byte helper uses **hard-coded Shift-JIS ranges** 0x81..0x9F and
0xE0..0xFE, with no actual external COFF relocations. The full native
77-byte original SHA256 is
`ced8af85dcbe5d3260f506a47ab810905d7d2d7fb9cb9d9ca1f623bb4c020655`.
Probable **game-authored** local text policy is now inferred, while the
original exact class/source ownership and possible vendor derivation are
explicitly unresolved. All historical R183 immutable controls/unknown
snapshots are retained as historical evidence, not silently rewritten.

`src/FontLeadByteF555.cpp` uses genuine member ABI already borrowed in the
accepted F293 parent, and pinned VC7.1 /Od compilation naturally emits all
**77/77 complete native bytes**, no relocation fields. Its affected-only
cold replay `--unit font-surface-shift-jis-lead-byte-0041ca30` returned
**1/1 exact**. Current origin review decreases from 96 to 95 functions;
full authored exact accepted units increase from 942 to 943 and CODE from
862,649 to 862,726. No partial code, fake data, all-unit replay or external
Oracle receipt. See [F555 original-provenance review](FONT_SHIFTJIS_LEAD_BYTE_F555.md).


## F556: 117-insn/403-byte native actor cases in two independent fighter giants

The complete `00486550` and `004AC040` whole original fighter bosses
(50,735 and 82,796 native CODE bytes respectively) contain distinct,
physically bounded **403-byte/117-instruction** action 6 and 7 cases.
Each has a real *additional* 13-instruction native guarded branch: checks
signed stage `this+0x62==4`, x87-compares `this+0x54` to native
`00657D14`, and issues actual `0040FB40(5)` on success. This stage-
triggered original code is absent in the 104-instruction F548 fighters.
Genuine per-role stage/float parameters are 4/16.0f/0.75f versus
2/15.0f/0.7f; CharacterMove action 7 truly places the FLAG clear **before**
its position/velocity/speed initialization, the other fighter after.
Two freshly compiled pinned VC7.1 source probes now reproduce **4 ×117
complete original register/x87/control instructions**, all **32 original
physical COFF fields** including genuine extra-stage call/global refs,
314 original-style physical DWORD switch relocations and 934 byte-identical
original sparse indexes. Whole original giant CODE remains unmatched;
1,612 inner-case bytes and 2,190 after-RET DATA-layout bytes are *not*
new accepted CODE/DATA. [Full F556 native C++ study](FIGHTER_EXTRA_STAGE_SOURCE_F556.md),
reproducible one-boss verifier
`scripts/repo-python scripts/verify-fighter-extra-stage-action-source.py`.
No all-unit replay, fake exactness or external Oracle receipt.


## F557: two flag-clear-free 115-instruction giant actor C++ families

Physical original first-switch cases 6 and 7 in `00543210` (58,294 full
original CODE bytes) and `00564BE0` (61,872) contain **115 native
instructions** each, unlike the 117-case F556 family. They have the
original extra 13-instruction stage/x87 threshold-`00657D14` callback,
but **do not clear FLAG** within their stage 3/2 float initialization.
Genuine per-fighter extra-stage/callback pairs are `3/4` then `4/5` for
`00543210`, versus `2/3` then `2/3` for `00564BE0`; all original float
values are independently read from physical MOV immediates. Four new
VC7.1 natural source cases meet **460/460 native register/x87/control
instructions, 32/32 genuine typed COFF references**, all 287 original
switch COFF field partitions and 669 actual compressed index bytes.

The original `00564BE0` cases are 508 bytes vs 393 candidate source
because 37 EBP-0x88 owner reloads grow +3 bytes each and one `JL` grows
+4 bytes in each case; the 115-byte per-case difference is fully measured
without source padding. The four **1,802 inner original CODE bytes** are
still part of 120,166 whole-boss unmatched CODE, not independently exact.
Detailed original native/COFF proof is at
[F557 natural 115-insn study](FIGHTER_STAGE_NO_FLAG_F557.md), reproducible
by `scripts/repo-python scripts/verify-fighter-stage-no-flag-source.py`.
No full cold replay, fabricated byte match or external Oracle receipt.


## F558: full original actor action 8 in two 117-instruction extra-stage giants

Native original `00486550` and CharacterMove `004AC040` first-switch
case 8 is exactly **104 instructions / 362 CODE bytes** each: unlike
original action 6/7 it lacks the 13-instruction stage/x87 bonus helper.
The native state test is +0x511==4, first state call pushes 0xCE, and
the true stage position value is -4.0f. But the original position/FLAG
write **ordering differs**: `00486550` stores position, then clears FLAG,
then stores 16.0f/0.75f velocity/speed; CharacterMove clears FLAG first,
then writes -4.0f position and 15.0f/0.7f velocity/speed.

Two newly compiled VC7.1 natural fighter sources revalidate actual
**actions 6/7/8 together**: six full case structures containing
**676/676 original per-fighter x86 GPR/x87/branch instructions, 44/44 real
physical typed COFF call/global fields**, 314 actual native-style DWORD
jump fields and 934 literal original sparse-byte maps. All **2,336 native
interior CODE bytes** remain part of **133,531 nonexact complete original
fighter CODE bytes**; 2,190 original after-RET DATA bytes remain separate.
Full original evidence and affected-only source reproducer:
[F558 action-eight C++ study](FIGHTER_EXTRA_STAGE_EIGHT_F558.md),
`scripts/repo-python scripts/verify-fighter-extra-stage-action-eight.py`.
No exact credit, full cold replay or external Oracle receipt.


## F559: real 458-byte native action-eight in the wide-frame 00564BE0 fighter

The complete independently SHA-checked `00564BE0` original giant
(61,872 CODE bytes) has physically bounded full action 6/7/8 blocks of
**508/508/458 CODE bytes**, holding **115/115/102 real x86
instructions** respectively. F559 regenerates one ordinary VC7.1 C++
prototype for all three, verifying **332/332 entire original native
GPR/x87/control roles and 22 true typed COFF fields**, plus the full
native 131 DWORD switch-field partitions and 350 exact sparse-index bytes.
Action 8 genuinely **omits the extra-stage bonus call and FLAG clear**
from earlier fighter variants, writes stage-two motion position -4.0f,
velocity 12.0f and speed 0.4f and calls the true virtual
`dword ptr [edx]` method. It has exactly **34 original wide EBP-0x88
receiver loads** (+102 native bytes) and a long JL (+4 native bytes),
explaining the entire **458-versus-352-byte** native/probe difference
without padding. Reproducer:
`scripts/repo-python scripts/verify-fighter-wide-action-eight-source.py`
and [F559 native action-eight study](FIGHTER_WIDE_ACTION_EIGHT_F559.md).
All **1,474 inner original CODE bytes** remain within the giant
nonexact 61,872-byte parent; no split-unit exactness, DATA credit,
full all-unit cold replay or external Oracle acceptance.


## F560: complete native 117-instruction precontact action 8 in 00543210

The entire original 58,294-byte `00543210` fighter giant has first
switch cases 6/7/8 of **115/115/117 native x86 instructions**, bounded
by actual original case DWORD entries, with native CODE sizes
393/393/403 bytes. Previously recovered action 6/7 each compare
`this+0x62` to an extra stage *after* collision; action 8 truly moves
its stage-three x87 `00657D14` check and `0040FB40(4)` **before** the
main x87 contact/collision check. Source then initializes game motion
in native order: -7.0f position, FLAG=0, 18.0f velocity, 0.95f speed.
Two independently generated selected-only pinned VC7.1 C++ probes
confirm **all 347 original case GPR/x87/control instructions, 24 true
physical COFF fields**, complete actual 156 original-style jump DWORD
field partitions and 319 identical original sparse bytes, with separate
943 after-RET DATA-layout bytes. The second independent source generator
and its complete negative-to-positive controls are kept in ignored
`.analysis/f560-543210-action-eight/`; tracked whole original verifier:
`scripts/repo-python scripts/verify-fighter-precontact-stage-action-eight.py`,
[full F560 117-insn study](FIGHTER_PRECONTACT_ACTION_EIGHT_F560.md).
The 1,189 complete inner-case CODE bytes remain part of an unmatched
whole boss, **not independently exact source**. No new exact CODE/DATA,
no all-unit replay or external Oracle acceptance.


## F562: three complete 102/115/102 actor cases inside 004D7E70 original giant

Full original fighter `004D7E70` (43,601 native CODE bytes) has first-
switch action 6/7/8 blocks of **352/393/352 original CODE bytes** and
**102/115/102 real instructions**. Unlike the previous 117-case or
115-case role families, only original action 7 invokes extra-stage
`0040FB40(5)` after genuine `S16(+0x62)==4`/x87 `00657D14` test.
All three stage-motion initializers omit FLAG clear entirely and store
native position 0.0f/+5.0f/−5.0f, velocity 15.0f and speed 0.65f.
Original action 6 virtual dispatches through `dword ptr [eax]`, while
cases 7/8 use `[edx]`. New selected VC7.1 natural C++ source generated
from the real original PE checks **319/319 true per-fighter GPR/x87/
branch instructions**, **20/20 native typed COFF call/global fields**,
140 physical switch DWORD reference partitions and 409 original sparse
index bytes (969 original after-RET DATA-layout bytes separately).
Reproducer `scripts/repo-python scripts/verify-fighter-split-stage-4d7e70.py`,
[F562 original-backed C++ study](FIGHTER_SPLIT_STAGE_F562.md).
The 1,097 native interior CODE bytes remain within one wholly unmatched
43,601-byte original boss; no full or split exact source credit, no
all-unit cold replay or external Oracle receipt.

## F561: independent small-function provenance and destructor stack audit

The intact original 248-byte BattleScene virtual destructor `0043B0B0`
was re-decoded as **75 real contiguous x86 instructions**, with **12
physical original COFF fields**. The best genuine C++ F505 baseline
reproduces the full 248-byte instruction/control geometry but only **191/200
nonrelocation bytes**: texture implicit delete temporaries are source
EBP-0x20/-0x1C versus native EBP-0x14/-0x10, and buffers in source
EBP-0x18/-0x14/-0x10 versus native EBP-0x18/-0x1C/-0x20. The nine
remaining byte mismatches are genuine local-stack-layout differences,
not available to mark as exact. Earlier independent real texture/aggregate
lifetime probes remain under `.analysis/f505-*`, `.analysis/f533-*`,
`.analysis/f546-*` and current read-only native alignment under
`.analysis/f561-scene-local-recovery/`.

Two larger *origin-unknown* `004591E0` (417 native CODE bytes) and
`0045AAE0` (368) were fully decoded as **128 and 118 contiguous
instructions**, dominated by source-to-destination field-wise copies,
member helper invocations and an optional EH frame. They appear to be
class/aggregate copy-construction machinery, **not established original
game-specific authored behavior**, so no provenance reclassification or
CODE credit is claimed. `00449DE0` (45 CODE bytes) is a vtable assign
plus two member construction calls, used by many factory callers;
`004588B0` is a 43-byte conditional `free` of member +8. These are
compiler/lifetime hypotheses only until an independent owner/provider
provenance chain is proven. Original analyses are retained in
`.analysis/f561-origin-review/`, not substituted for authentic source.


## F563: genuine second-stage positive-FLAG motion overrides in two giants

Original complete fighter `004F7130` has physically bounded first-switch
action 6/7/8 lengths **125/127/104 native x86 instructions** and
**441/451/362 CODE bytes**; the separate 71,616-byte `005AEEC0`
original has **125/115/102 instructions** and **441/393/352 bytes**.
The newly decoded source-level logic is an authentic additional
`if (FLAG > 0)` after stage-2 position, velocity and speed writes.
The first fighter's action6 first/secondary triplets are
(0,13,0.4)/(2,10,0.25), action7 (3,13,0.4)/(4.5,10,0.25)
with FLAG cleared **only after** its second conditional override; action8
has -4,13,0.4 plus a FLAG clear between position and velocity.
The second fighter's action6 first/secondary triplets are
(0,16,0.75)/(3,15,1.25), but action7 is a 115-instruction normal
(8,16,0.75) policy and action8 a 102-instruction (-8,16,0.75)
policy without the extra positive-FLAG override or FLAG clear.

Two newly generated and freshly compiled original-PE-backed VC7.1 source
probes independently validate **all 698/698 native instruction GPR/x87/
branch/size roles and 44/44 true typed COFF fields**, the authentic final
virtual method, **305 native-style switch DWORD fields**, repeated/default
handler partitions and **822 literal original compressed index bytes**.
The full 2,042 after-RET DATA-shape bytes are separate from CODE.
Complete native research and reproduction:
[F563 conditional-override study](FIGHTER_FLAG_OVERRIDE_SOURCE_F563.md)
and `scripts/repo-python scripts/verify-fighter-conditional-override-actions.py`.
The **2,440 original internal CODE bytes** are not independently exact
functions and remain within **115,827 unmatched whole-fighter CODE bytes**.
No total cold replay, target assembly graft or external Oracle receipt.

## F564: integrated complete first-eleven action cases in two giant C++ switches

Two **single-TU** source experiments now compile all true original
first-table actions 0..10 together in the complete native contexts of
44,211-byte 004F7130 and 71,616-byte 005AEEC0 fighter controllers.
The entire original giant CODE SHA and after-RET DATA are checked
before each selected compiler invocation. **22 complete native
case structures** (1,296 original x86 per-fighter GPR/x87/branch and
instruction-length roles, 4,558 real inner CODE bytes) match the
new natural VC7.1 source; **146 genuine typed COFF call/global fields**
also match original physical instruction ordinals, along with all
305 original switch DWORD COFF fields, repeated/default handler
partitions, 822 literal sparse map bytes and 2,042 after-RET DATA
layout bytes. Combined action9/10 source now has original GPR
allocations for these two fighters where earlier isolated probes did
not, showing that the enclosing C++ case structure affects compiler
register layout. Later action labels remain diagnostic-only marker
stores: the **115,827 complete original giant CODE bytes are still
unmatched**. [F564 source integration](FIGHTER_INTEGRATED_ELEVEN_CASES_F564.md);
reproducer scripts/repo-python scripts/verify-fighter-integrated-opening-switch.py.
No split/whole CODE credit, all-unit cold replay or external Oracle.

## F565: distinct 96/83/83 action family within 005214B0 original giant

The complete original 46,755-byte 005214B0 fighter has physically
bounded first-switch action 6/7/8 cases containing **96/83/83
native x86 instructions** and **331/290/290 original CODE bytes**.
Unlike the ten previous natural frame-advance fighter source
variants, these case bodies gate the main x87 contact transition
on signed stage >2 and do not increment frame counters or end with
actor virtual frame calls. The new natural VC7.1 C++ source models
real 0040FB40(5) extra stage and 0040FB40(11) current-action
branches in action6, native 0040FAC0(9) in action7 and
0040FB40(13) in action8, with actual conditional 0/+5.5/-5.5f
position stores and 16.0f/0.8f velocity/speed and FLAG clear.
One freshly compiled original-backed TU matches **all 262 actual
case register/x87/branch/length roles**, 23 genuine typed COFF
fields, 139 native-style physical DWORD jump slots and 345
byte-identical sparse index bytes. The 911 native inner CODE bytes
remain part of 46,755 completely unmatched original CODE bytes;
901 after-RET DATA bytes remain separate. Reproducer:
scripts/repo-python scripts/verify-fighter-scripted-stage-actions.py;
[F565 scripted-state source](FIGHTER_SCRIPTED_STAGE_F565.md).
No whole/subfunction exact credit, all-unit replay or external Oracle.

## F566: eleven authentic native game actions integrated in 005214B0

Original complete 46,755-byte fighter giant 005214B0's distinct scripted
frame-state family (F565) has now been naturally compiled in **one C++
Advance() function containing all first-table action cases 0..10 at once**.
The full original PE SHA, genuine separate case0x32 singleton boundary
and entire after-RET jump DATA are independently verified first.
The single fresh VC7.1 COFF object matches **all 550 native
GPR/x87/control instruction roles and lengths** in those eleven case
subranges, **73/73 physically genuine typed COFF calls/globals**,
all 139 original-style DWORD switch fields, real repeated/default
handler destinations and 345 byte-identical original sparse index bytes.
That is **1,938 internal native CODE bytes**, still included in
**46,755 wholly unmatched giant original CODE bytes**, never split/
whole exact credit. Remaining case labels are clearly diagnostic-only
markers. Original after-RET DATA remain 901 separate bytes.
F566 study: [source integration](FIGHTER_INTEGRATED_SCRIPTED_F566.md);
affected-only reproducible command
scripts/repo-python scripts/verify-fighter-integrated-scripted-switch.py.
No full cold replay or external Oracle receipt.

## F567: eleven giant fighter whole-switch source integration, first actions 0..10

F567 freshly builds **eight more entire natural C++ Advance() TUs**,
each implementing all the true original first-table action cases
0..10 in one compiled source function. Full whole native CODE SHA,
all guarded original switches and physical after-RET DATA are
independently verified for each original fighter; real source case
expressions are regenerated from tracked original-backed helpers.
All **88/88 original complete case GPR/x87/control grammars**
match new VC7.1 source, containing **4,989 real x86 instructions and
18,033 original native inner CODE bytes**, with **571/571 typed COFF
fields**, 1,163 physical original-style switch DWORD refs, 3,335
byte-identical original sparse indexes and 7,987 after-RET DATA bytes.

The exceptional 00564BE0 giant has native 585 extra code bytes across
its 11 first-switch cases, independently verified as **191 EBP-0x88
wide owner loads ×3 bytes plus 3 near JL branches ×4 bytes**; native
register/x87/branch grammar remains matching and no fake local
padding has been added. The other seven new fighter sources emit
native-length inner case CODE exactly.

Combining previous F564 two and F566 one with F567 eight, **all 11
original multi-switch giants** now have single-TU natural C++ source
models for first 11 real game actions: **121 complete native cases,
6,835 x86 instruction roles, 24,529 native inner CODE bytes, 790 real
typed COFF fields**, all 1,607 original switch DWORD destinations,
4,502 compressed map bytes and 10,930 separate after-RET DATA-layout
bytes. Their **613,391 entire original giant CODE bytes are still
unmatched**, and all later source action labels remain test-only
markers. Complete live report
[F567 whole cohort integration](FIGHTER_ALL_MULTISWITCH_INTEGRATION_F567.md)
and affected-only repro
scripts/repo-python scripts/verify-fighter-all-multiswitch-opening-cases.py.
No split/whole exact credit, all-unit cold replay or external Oracle.

## F568: independently checked physical COFF addends across F567 giant actors

A separate originally untracked eight-fighter natural VC7.1 source
verifier was freshly executed against all eight complete original
fighter contexts, matching the 88 physical native first-switch
case-control subranges and all original switch DATA. It additionally
proves **all 571 physical typed native case call/global COFF fields
and all 88 original first-direct-table DWORD handler fields have
zero addends**. The canonical tracked F567 source checker now
rejects nonzero candidate COFF addends (re-tested on Reimu and
wide-frame 00564BE0). The previously dirty alternative and its full
source audit logs are preserved under ignored
.analysis/f567-integrated-fighters/ as independently verified controls.
[F568 original-PE addend control](FIGHTER_COFF_ADDEND_CONTROL_F568.md).
No giant whole/split exactness, no full cold replay or Oracle receipt.

## F569: native CharacterObject early guards and entire 11 compressed source switches

All 11 remaining original 28K–82K CharacterObject huge boss
functions (488,664 native original CODE bytes) use one genuine sparse
indexed state jump with action base 0x320, not the CharacterMove
six-/seven-switch dispatch architecture. F569 newly generates and
fresh-compiles one ordinary VC7.1 C++ switch source per whole
original, recreating actual parent +0xE4 -> +0x2E8 -> +0x3BA
signed guard, second parent +0x3BA and own +0x8A guard, signed-short
cooldown -1 at +0x82, and native 0x320-normalized byte-index
first switch. Eleven native guards match real 17-instruction
register/branch grammars and all eleven 10-/11-instruction
cooldown/switch dataflow roles; 10/11 cooldown and 9/11
dispatch sequences have native GPR allocation. Wide original
0050A580 uses EBP-0xAC/-0xB0 and six native disp32 index reloads,
explaining 18 bytes of original-dispatch widening.
Original 00536400 has additional native game behavior before this
switch and different source register rotation, so is not called
register- or CODE-exact. Every natural source probe reproduces
the whole original jump DATA: **752 authentic zero-addend
COFF DWORD handler refs, 2,185 literal native sparse bytes,
5,193 distinct original after-RET layout bytes**.
The 741 unique case IDs are **diagnostic marker stores**, not
real restored game-action bodies. The full 488,664 whole original
CODE bytes remain unmatched, with no extra exact source/bytes.
See [F569 one-switch native original study](CHARACTEROBJECT_SINGLE_SWITCH_F569.md)
and
scripts/repo-python scripts/verify-characterobject-single-switch-source.py.
No full all-unit replay or external Oracle receipt.

## F570/F571: complete original small destructor lifetime counterexamples

The intact original ArchiveCatalog nonvirtual RAII destructor at
0041CE50 (171 bytes, 51 x86 instructions, 14 authentic COFF fields)
still has a real 3-way saved-local stack slot permutation:
native resource-delete temps EBP-0xC/-8 versus small C++ -0x10/-0xC;
native filename -0x10 versus C++ -8. Eighteen new natural C++
lifetime declarations (explicit resource pointers/const, references,
nested scopes, before-loop declaration orders) compiled under the
original VC7.1 /GX- profile. Four 171-byte outputs still matched
only 108/115 or 102/115 nonrelocation bytes, and 14 were 177 bytes.
No exact source or credit.

The original SceneObject virtual destructor at 0043B0B0 (248 bytes,
75 x86 instructions, 12 real COFF fields) still has texture delete
temporary EBP slots -0x14/-0x10 versus C++ -0x20/-0x1C, and real
heap-free local slots -0x18/-0x1C/-0x20 versus C++ aggregate
-0x18/-0x14/-0x10. Ten new VC7.1 /GX source combinations moving the
aggregate ahead of texture delete, reversing aggregate members and
introducing explicit pointer scopes/references produced six 248-byte
mismatches (191/200 or 189/200 comparable bytes) and four
251-/255-byte nonoriginal function lengths. Real owner/lifetime
inference remains necessary, not compiler-byte patching.
Complete independent comparison logs/source remain preserved under
.analysis/f570-archive-cxx-lifetimes/ and
.analysis/f571-scene-aggregate-lifetimes/. See
[F570/F571 destructor negative source matrix](DESTRUCTOR_LIFETIME_CONTROLS_F570_F571.md).
No new exact CODE/DATA or full cold replay.


## F572: 10 genuine original action bodies including 3x271 x86 in CharacterObject

F569 verified the common actual CharacterObject guard/cooldown/sparse
switch but had **only diagnostic case markers**. F572 now recovers
**ten actual complete native game-action bodies** in original
`004EBDA0` (33,293 whole CODE bytes): `0x320..0x326` are seven
independent 13-byte/3-instruction true `004F4170` call cases,
while `0x327`/`0x328`/`0x329` are three full **271-instruction**
effect/spawn/frame-motion/collision game policies (998/999/999
native CODE bytes) with distinct original stage values:
initial `+0xD8` −30/70/−30, initial `+0xDA` 150/150/200,
subsequent +0xD8 updates +3/−2/+4. The source recovers the actual
for-8 effect spawn at original `00453A70`, actual floating-point
motion and native calls `0040FB70`, `0040FBB0`, `0040FB40` and
`0040FA30`; all original GPR/x87/branch and byte-layout roles
now compile naturally in one pinned VC7.1 C++ switch TU.
A crucial real C++ pointer-lvalue expression causes the native owner
load to precede x87 `FLD`; the native effect argument requires a
real char parameter (plain int produces wrong MOVSX). After actual
physical PE call/global COFF verification (rather than blindly
normalizing object `[0]`), all **10 complete case structures,
834/834 original x86 instructions, 3,087 actual native inner CODE
bytes and 61/61 authentic typed COFF fields** match, with 60
original-style dense DWORD switch fields, 198 byte-identical
sparse-index bytes, and separate 438 after-RET DATA-layout bytes.
Tracked natural C++ [F572 source](../probes/CharacterObjectActionsF572.cpp)
and [native study](CHARACTEROBJECT_FIRST_TEN_NATIVE_CASES_F572.md),
affected-only reproducer:
`scripts/repo-python scripts/verify-characterobject-action-family-f572.py`.
**The full 33,293 original boss is nonexact; inner CODE is not new
exact function/coverage credit.** No whole cold replay/Oracle receipt.


## F573: the 248-instruction x87-gated CharacterObject action 0x32A

Original full-giant `004EBDA0` next physical compressed handler
`0x32A` is a **complete 932-byte/248-instruction native x86
body**. It has genuine five-effect parent spawn, staged
actor-field initialization and **six independent original native
FUCOMPP floating comparisons** against constants at 0065782C,
0065747C, 00657480, 00657CF8, 00657D14, 00657874,
selecting ±1/3/5f position and 6/8/10f velocity. The native
stage-2 contact and motion update calls original effect spawn
`00453A70` with arguments 0x32B/0x32D and game state
`0040FAC0(0x33B)`; regular paths query `0040FA30` and call
`0040FB40(1)`. Eleven new natural C++ lvalue/volatile/operand
ordering experiments exposed the real VC7.1 source expression
`*(&F32(0xC8)) == global`: it causes the original float
GLOBAL-before-owner FLD/FUCOMPP order. Source emits all 248
original instructions and 932 bytes with identical register,
CFG and x87 roles **except original MOV EDX [saved_this] /
FLD [ECX+0x48] is reversed** in the C++ output. These two
operations are independent read-only and only that exact pair
is explicitly permitted by the new checker; this is NOT original
machine-order exactness.

Updated [`probes/CharacterObjectActionsF572.cpp`](../probes/CharacterObjectActionsF572.cpp)
with a newly compiled source and tracked
`scripts/repo-python scripts/verify-characterobject-extended-action-f573.py`
now covers 11 complete original internal game-action case
bodies, **1,082 x86 roles / 4,019 original internal CODE bytes**
and **80 genuine typed zero-addend COFF fields**, whole original
60 DWORD source labels and 198 exact compressed index bytes.
These inner bytes remain part of the **33,293 wholly nonexact
giant**; no split/whole CODE credit, full replay or external Oracle.
Full original-source study:
[CharacterObject F573 x87 case](CHARACTEROBJECT_X87_ACTION32A_F573.md).


## F574: further original action 0x32B/0x32C in CharacterObject 004EBDA0

F574 extends tracked `probes/CharacterObjectActionsF572.cpp` with
full original actions `0x32B` (112 native x86 instructions /422 CODE
bytes, nine original typed COFF refs) and `0x32C` (176 instructions
/635 bytes, 13 true typed refs). Action32B authentically creates
stage-zero state and updates two visual scaling float fields using
signed frame `(5 - S16(0x64))`, float global `0065972C`, original
`SETL` Boolean condition compiled as `FIMUL`, and true float
`00658044` and member arithmetic. The normal VC7.1 source is strict
native exact instruction-order geometry. Action32C performs a
five-effect `00453A70` loop, native `0040FBB0` and raw +0xC8
motion call `0040FB70`, an original stage-2 x87 collision
check, effect spawns `0x32B/0x32D`, and action switch
`0040FAC0(0x33B)`. Its native 176 instruction and 635 byte
geometry is exactly matched, except one proven independent read-only
MOV EAX / FLD +0x48 pair is reversed, so NOT byte-order exact.
In the *same newly compiled normal C++ switch*, F572/F573/F574
cover **all 13 original case bodies 0x320..0x32C**, including
**1,370 native instruction roles /5,076 real inner original CODE
bytes, 102 true typed zero-addend original COFF references**, full
60 original physical DWORD handler slots, 198 byte-identical
compressed index bytes and 438 native after-RET DATA-layout bytes.
The complete **33,293-byte giant still is NOT CODE-exact**;
no independent partial function or DATA credit. Verified reproducibly
by `scripts/repo-python scripts/verify-characterobject-following-actions-f574.py`;
[full F574 native case study](CHARACTEROBJECT_STAGE_CURVE_F574.md).
No all-unit replay or external Oracle acceptance.


## F575: native CharacterObject fade actions 0x32D and 0x32E

The complete original action `0x32D` in `004EBDA0` is **229 CODE
bytes/66 native x86 instructions**, implementing the genuine
stage 0 +0x1C/+0x20=0.4f scale state, sprite id +0x1A=0x4E2,
position -75.0f, float global `006583F8` fade addition,
conditional stage>1 byte-alpha decrement 20, and native
`0045B830`/`0040FA30` game state resets. The following actual
original `0x32E` body is **282 bytes/70 instructions**:
initialization is additionally gated by signed +0xD8==1,
its scale starts at 0.5f, uses a **different** float global
`00659428` and unconditionally decrements unsigned byte +0x11
by 10. Original ID `0x32F` maps to the shared default handler:
**the real next physical case is 0x330**, not a made-up 0x32F
CODE range. The new true C++ source with 15 complete original
case bodies now reproduces **1,506 native x86 instruction roles,
5,587 inner real original CODE bytes and 113/113 genuine typed
zero-addend COFF references**, all 60 original-style dense jump
fields, 198 literal compressed map bytes and 438 distinct native
DATA layout bytes; both new cases strictly match original GPR/
x87/order/length. F573/F574 two read-only swaps stay explicitly
not byte-order exact. Detailed [F575 native study](CHARACTEROBJECT_FADE_ACTIONS_F575.md),
local-only reproducer:
`scripts/repo-python scripts/verify-characterobject-fade-actions-f575.py`.
**The giant 33,293-byte original CODE remains NONEXACT**, no
partial function credit, no all-unit cold replay/Oracle.


## F576: complete 274-insn native action0x330/331 source in 004EBDA0

The next two physically bounded original CharacterObject actions
`0x330` and `0x331` each have **274 complete native x86 instructions
and 1,003 original CODE bytes**, with stage-0 x87 motion, native
8-effect spawn, state transitions, native `00455580` random and
parent `00453A70` effect generation. Importantly, source `0x330`
initializes motion `(-4.0f,6.0f)` and subtracts actual original
global `006583FC`, while source `0x331` initializes `(3.0f,16.0f)`
and subtracts **different original floating global `00659090`**.
A single newly compiled VC7.1 C++ TU keeps the same true native
274 GPR/x87/branch roles but emits only 985 bytes per action:
original giant real EBP temporary integer-to-x87 FILD stack slots
are deeper (native 0x330 `-0x84/-0x88/-0x8C`, action0x331
`-0x90/-0x94/-0x98`), causing exactly **six original disp32
MOV/FILD instructions × three additional bytes = 18 native CODE
bytes** per case. No padding, grafted code or split-case exactness.
Both native cases independently have 16 true typed physical
COFF call/global references and verified original targets. The
tracked C++ and verifier now handle **17 real physically bounded
inner game-action cases, 2,054 native source instruction roles,
7,593 original inner CODE bytes and 145 real COFF fields**, all
60 physical jump DWORD slots and 198 exact sparse-map bytes.
Original 0x32F is the default sparse entry, not a real function.
No complete whole `004EBDA0` original CODE credit, no cold all-unit
replay, no external Oracle. Reproducer:
`scripts/repo-python scripts/verify-characterobject-fire-actions-f576.py`;
[F576 original fire-state reconstruction](CHARACTEROBJECT_FIRE_STATES_F576.md).


## F577: original CharacterObject signed facing reversal in action0x332

The complete Japanese original `004EBDA0` giant source has a new
nondefault handler action `0x332` **279 native instructions /
1,019 original CODE bytes**; the next physical game-action target
is `0x335` since original `0x333/0x334` map to shared default.
The real game behavior differs from earlier `0x330/0x331`: stage0
float position +6.0f, velocity +4.5f, stage1 signed direction
`S8(+0x66)=-S8(+0x66)` producing five new real x86
MOVSX/NEG/MOV roles, and parent effect spawn `0x322`. Fresh one-TU
VC7.1 C++ source naturally reproduces all **279 native x86
GPR/x87/CFG instructions** but only 1,013 bytes: the original
integer-FPU temporary `EBP−0x9C` loads at native ordinals 97/98
need disp32 (+6 genuine original width bytes) versus the isolated
source's compact `EBP−0x80` disp8. Sixteen true physical COFF
call/float fields are independently typed and original-PE-backed.
In the same C++ function, F572–F577 now verifies **18 complete
native inner game-action cases, 2,333 original x86 roles, 8,612
original inner CODE bytes and 161 typed physical COFF fields**,
all 60 original DWORD sparse handlers and 198 byte-identical map
bytes; 438 original after-RET DATA bytes stay separate. The entire
33,293-byte giant is not exact; no split original CODE credit,
all-unit cold replay or Oracle receipt. Full study:
[F577 direction reversal](CHARACTEROBJECT_DIRECTION_REVERSAL_F577.md),
reproducer `scripts/repo-python scripts/verify-characterobject-direction-reversal-f577.py`.


## F578: full 269-instruction action0x335 and genuine cross-case EBP expansion

The independently PE-attested original CharacterObject `004EBDA0`
case `0x335` to next true nondefault action `0x338` is a complete
269 native x86 instruction/1,022 CODE-byte game policy. It implements
actual eight-effect parent spawn, genuine stage-0 state reset and
`0040FB70` raw +0xC8 motion (14.0f speed), signed-direction x87
position updates and globals `00657CBC/00657478`, native stage-ten
contact threshold `00657888`, original `0040FB40(11)`, decay and
counter transitions, and an original stage-six `S16(+0xDC)` x87
comparison with global `0065782C + F32(+0xCC)`. Natural C++
`*(&gCompareAt0065782C) + *(&F32(0xCC))` reproduces the native
GLOBAL-first FLD/FADD order, after eleven actual compiled C++
expression controls. The new selected MSVC7.1 TU has all 269 native
GPR/x87/CFG/byte-width instruction roles, authentic 17 typed
zero-addend COFF call/global fields, and exactly one separately
validated independent MOV/FLD read-order swap at ordinals146/147,
which is never asserted as byte-exact CODE.

Importantly this genuine added 269-instruction source case changes
**another** previously verified native action's compact stack layout:
F577 action0x332 was original 279/1,019 vs earlier C++ 279/1,013
from candidate temporary EBP−0x80 (disp8), while the larger F578
single TU places that actual temp at EBP−0x84 (disp32), giving
both 279/1,019 bytes and no synthetic padding. Original temp remains
EBP−0x9C; whole giant still not exact. Its two sibling action0x330/
0x331 cases still each have +18 genuine original EBP width bytes.
Across all **19 truly original game-action bodies 0x320..0x335
excluding default case IDs**, newly compiled single-TU C++ matches
2,602 original instruction roles /9,634 actual native inner CODE
bytes, all 178 authentic typed COFF fields, all 60 physical switch
DWORD labels, 198 literal original compressed bytes and 438
separate after-RET DATA-layout bytes.
Reproducer `scripts/repo-python scripts/verify-characterobject-contact-stage-f578.py`;
[F578 contact-stage source study](CHARACTEROBJECT_CONTACT_STAGE_F578.md).
No standalone split/whole CODE credit, all-unit cold replay or Oracle.


## F579: strict native actor effect/spawn+color actions 0x338 and 0x339

Original 33,293-byte `004EBDA0` CharacterObject giant has two
newly recovered complete physical source case bodies, native
`0x338` **130 instructions/478 CODE bytes** with real
00453E60(10.0f) parent setup, effects 00453A70(0x33A) and
00453A70(0x339), stage-zero scale=1.0f and stage>1 unsigned
color fade by 20; native `0x339` is a different original
**80-instruction/309-byte** stage state with real float scale 1.3f
and color fade by 40. Both actions use genuine x87 global 00659428,
actual state methods 0040FBB0,0040FA30,0045B830 and real original
signed stage/frame fields. Fresh one-TU VC7.1 C++ emits **all 210
original x86 register/x87/branch roles and complete exact native
case instruction lengths/order**, with 15 authentic typed
zero-addend physical COFF call/global fields.
The same C++ implements **21 actual complete original game-action
bodies** with 2,812 original x86 instruction roles, 10,421 native
inner CODE bytes and 193 genuine physical call/global COFF refs,
plus all 60 real native dense switch COFF DWORDs and 198 literal
compressed sparse-index bytes (438 distinct after-RET DATA).
No additional read-only instruction swaps; existing F573/F574/F578
source swap exceptions and F576 EBP frame widths remain explicit.
Reproducer:
`scripts/repo-python scripts/verify-characterobject-fade-spawns-f579.py`;
[F579 native effect/fade source](CHARACTEROBJECT_FADE_SPAWNS_F579.md).
Original **entire 33,293-byte fighter still nonexact**; no
split/whole exact CODE/DATA or all-unit cold replay/Oracle acceptance.


## F580: strict native 0x33A..0x33D actor x87 and third parent guard

The entire original 33,293-byte CharacterObject giant `004EBDA0`
now has four additional truly native game-action case C++ bodies
in the same single-TU switch: `0x33A` 66 instructions/229 original
CODE bytes, `0x33B` 84/301, `0x33C` 127/472, `0x33D` 127/472.
All four newly compiled sources match exact original x86 mnemonic,
register/x87/branch graph and per-instruction byte lengths, with
**31 genuine typed zero-addend COFF call/global fields**.
`0x33A` is an authentic independent 20-step fade based on float
006583FC; `0x33B` performs native 00455580 random motion with
FILD/FSUB 00659728/FADD 006581DC/FCHS, real 0040FB70,
and native threshold comparison against 0065912C.
Ordinary C++ `float < threshold` is required for actual native
`FCOMP; FNSTSW; TEST AH,5; JP` (not a superficially similar
negated `<=` which uses different real x87 flags).
`0x33C/0x33D` have full 127-instruction owner-stage policies
with signed direction times 65, real parent position and native
float global 006590AC. An original PE-only correction:
`0x33D` first two parent-state comparisons are **0x2C1**, but
its third physical comparison at instruction 34 is **0x2BE**;
`0x33C` uses 0x2BE for all three. Natural C++ parent-first
*reference-lvalue* expressions preserve the original GPR/FILD/FADD
operand order, unlike straightforward arithmetic ordering.
Across all 25 complete original nondefault action cases now
**3,216 genuine original x86 instruction roles / 11,895 internal
native CODE bytes /224 authentic physical COFF fields** in the
single selected VC7.1 source, with 60 original dense handler refs,
198 exact native sparse bytes and distinct 438 after-RET DATA.
The whole original giant is still nonexact; internal case CODE
is NOT independently exact/accepted, no full replay/Oracle.
[F580 four full game-action study](CHARACTEROBJECT_FOUR_ACTIONS_F580.md),
reproducer `scripts/repo-python scripts/verify-characterobject-four-next-actions-f580.py`.


## F581: two more full original native parent-state CharacterObject actions

Original whole 33,293-byte CharacterObject giant `004EBDA0`
case `0x33E` is a **127 native x86 instruction /489-byte**
parent-stage source action: signed direction ×140 and parent state
0x2BE, native x87 `006590AC` position, real
`00455580(0,4)` at stage6, authentic `FILD/FMUL` float
`006578C0` plus `006581E0`, stage7 `FMUL 00659094` and
native `0040FB40` callbacks. Distinct original `0x33F` is a
**101-instruction /381-byte** source with parent state 0x2C1,
signed direction ×180 and genuine stage17 callback; its native
scale init is 2.0f/1.5f rather than 0x33E's 1.5f/1.5f.
Both source cases newly compile in the **same normal VC7.1 C++
switch** with exact original 127/101 GPR/x87/branch/byte-width
instruction roles and authentic 10+6 zero-addend COFF call/global
fields; no new machine-order exceptions. F572–F581 now cover
**27 physically entire original game-action case bodies, 3,444
native instruction roles /12,765 original inner CODE bytes,
240 actual typed COFF fields** and the whole 60 DWORD/198-index
original switch DATA (438 separate after-RET layout bytes).
**The whole 33,293 CODE bytes remain nonexact**, with no
independent inner function credit. Reproducer
`scripts/repo-python scripts/verify-characterobject-parent-scatter-f581.py`;
[F581 source study](CHARACTEROBJECT_PARENT_SCATTER_F581.md).

The small 171-byte original `0041CE50` archive RAII destructor
was also retested under pinned VC7.1 /GX- with 14 actual C++
POD/union/one-element array/volatile/void pointer ownership
variants. All 14 still produce a real 171-byte, 51-insn body,
**108/115 comparable nonfield bytes** and the SAME wrong three-way
EBP resource-delete/filename slot positions. This negative control
rules out trivial filename type/scope as the original slot-order
cause, not a standalone exact achievement. Detailed ignored
C++/OBJ/COFF evidence: `.analysis/f581-archive-expr-order/`.
No all-unit replay or external Oracle receipt.


## F582: absolute-motion native cases0x340/341 with strict C++ x87 order

Original `004EBDA0` CharacterObject giant has two next genuine
**159-instruction /597 original CODE-byte** action cases `0x340`
and `0x341`, each with **13 physical COFF typed call/global
refs**. They both implement authentic signed parent direction ×90,
parent `+0x44` minus opponent's `+0x44`, original cdecl float
`00412D90` absolute-value return, FMUL real float 00659724,
clamp threshold 00657D14, native velocity deceleration 00657480
and stage<2 contact threshold 0065782C. Real action0x340
spawns original effects 0x338/0x33A with parent callback
00453D40(8), action0x341 uses 0x342/0x344 and
00453D40(10); each switches to native action0x33B on collision.
Normal VC7.1 source real `*(&PF32(+0x44))` lvalue preloads parent
before signed direction FILD; real `*(&F32(+0x48)) +
*(&F32(+0x54))` produces the exact original MOV/MOV/FLD/FADD
order instead of an independently reordered FLD. Thirteen alternative
C++ expression forms were compiled and checked without machine
patching, artificial padding or fake original stack locals.

Both new complete case bodies match native exact instruction grammar
plus 26 actual typed zero-addend COFF relocations. F572–F582's
same natural C++ now implements **29 real original case bodies,
3,762 authentic original x86 roles /13,959 internal CODE bytes /
266 real physical COFF fields**, original 60 physical dense switch
DWORD refs and 198 literal compressed index bytes plus 438 after-RET
DATA-layout bytes. The 33,293-byte original complete giant still
NOT exact and no internal case earns independent credit.
[F582 original source study](CHARACTEROBJECT_ABSOLUTE_MOTION_F582.md),
reproducer `scripts/repo-python scripts/verify-characterobject-abs-motion-f582.py`.
No all-unit cold replay or external Oracle acceptance.


## F583: three strict native CharacterObject stage and fade action bodies

In original 33,293-byte CharacterObject giant `004EBDA0`, real native
compressed nondefault actions `0x342` (87 x86/338 CODE bytes),
`0x343` (80/309) and `0x344` (66/229) now compile from real
ordinary VC7.1 source in the same switch as F572–F582.
Actual `0x342` stage0 resets native signed D8, real stage state,
scale and position, invokes parent `00453E60(10.0f)`, tracks 7C==6
frame increment and stage3 effect `00453A70(0x343)` with
actual signed direction. Original `0x343` has native float scales
1.7f (`0x3FD9999A`), real x87 float global `0065825C` at two
physical relocation ordinals, signed stage > -1 and color fade 20.
Original `0x344` independently uses native 0x4E2 sprite,
-75.0f offset, real `006583FC` two-x87-add 20-step fade and
`0045B830` reset. All three sources strictly match native x86
GPR/x87/control order and byte widths, no new order exception.
They add **233 native complete x86 instructions /876 inner CODE
bytes /17 original-PE-grounded typed COFF physical fields**.
The unified source now validates **32 complete real native case
bodies, 3,995 native x86 instruction roles, 14,835 actual inner
original CODE bytes and 283 genuine typed physical COFF refs**,
plus all 60 native switch DWORD COFF fields and 198 literal
original sparse bytes, 438 separate after-RET DATA-layout bytes.
Original giant 33,293 whole CODE remains nonexact; the cases are
not independently original exact functions and no all-unit replay
or external Oracle was run. Selected verification script
`scripts/repo-python scripts/verify-characterobject-state-leaves-f583.py`;
[F583 source study](CHARACTEROBJECT_STATE_LEAVES_F583.md).


## F584: original whole archive resource destructor delete-expression controls

The original Japanese TH075 1.11 nonvirtual ArchiveCatalog destructor
`0041CE50` has 171 CODE bytes, 51 complete native x86 instructions
and native physical resource/destructor/filename temp slots
`EBP−0xC/−0x8/−0x10` at native ordinals22/24/38. The best
ordinary VC7.1 `/GX-` C++ destructor has the same 171 bytes and
51 instructions but stores the same real pointers at
`EBP−0x10/−0xC/−0x8`, matching only 108/115 nonfield bytes.
Twelve NEW actual C++ resource deletion expressions using
static/reinterpret/C-style/const pointer casts, explicit pointer
alias, reference casts, address-of-dereference and constant
conditional operators have now been independently compiled and
compared as **entire** original functions. **10/12 still produce
the identical nonexact 171-byte/51-insn output, same EBP slots,
108/115 nonrelocation bytes**. The two constant ternary sources
produce real compiler 193/198-byte whole bodies, not original 171.
No source hack/padding/physical byte graft, no newly exact CODE.
Tracked independent source-only reproducer:
`scripts/repo-python scripts/verify-archive-delete-expressions-f584.py`
with baseline `probes/ArchiveCatalogNativeLifetimeF584.cpp`;
[F584 complete original RAII destructor proof](ARCHIVE_DELETE_EXPRESSION_CONTROLS_F584.md).
The true original lexical owner/automatic lifetime still needs
recovery. Zero full cold replay or external Oracle acceptance.


## F585: five complete original trajectory x87 and parent-sync action bodies

Japanese original CharacterObject giant `004EBDA0` (33,293 whole
CODE bytes) contains complete game actions `0x345` 286/1,144,
`0x346` 111/436, `0x347` 286/1,136, `0x348` 289/1,153,
`0x349` 111/436 (real x86 instruction counts / entire native
inner CODE bytes). Three large ~1.1KB cases implement original
angle ±180 wrap, stage-specific polar motion and three authentic
`__ftol2` external C runtime conversions each, plus real stage
boundary floats 00659248/0065930C/00658E80. Role-specific
speed limit+increment are `0x345` 140/+7, `0x347` 120/+6,
`0x348` 200/+10, with true 0x348 negative polar sign. The two
111-insn source cases sync actual parent `+0xF0C/+0xF0E`
shorts through two original `__ftol2` calls each, then update
floating speed and current actor state.

The 111-insn source cases initially had GPR register rotations
in small source probes, despite correct instruction counts/436
CODE byte lengths. Adding the THREE real larger action source
bodies to the *same* normal C++ switch naturally produced
**all five complete native exact GPR/x87/branch/byte-width
instruction grammars**, with no local fake padding/ASM.
Native original PE and new C++ COFF checks verify **71 true
typed physical zero-addend call/global fields** at original
instruction positions, including actual external CRT 006406AC
and never counting CRT code as authored game CODE.
Across F572–F585 single source: **37 genuine original game-action
bodies, 5,078 native instruction roles, 19,140 internal
original CODE bytes, 354 true typed COFF fields**, 60 native
physical jump-table DWORD fields and 198 exact sparse-index
bytes, 438 separate after-RET native DATA-layout bytes.
Original whole 33,293-byte fighter still not exact; no
standalone inner CODE credit or full all-unit cold replay/Oracle.
[F585 trajectory source study](CHARACTEROBJECT_TRAJECTORY_F585.md),
reproducer `scripts/repo-python scripts/verify-characterobject-five-trajectory-actions-f585.py`.


## F586: native complete action0x34A/34B and genuine cross-case EBP shrink

Original Japanese `004EBDA0` complete 33,293-byte CharacterObject
switch has two more physically bounded real game action bodies:
`0x34A` **295 native x86 instructions /1,093 real CODE bytes**
with extra 0065786C x87 stage-zero contact (FCOMP/TEST AH,0x41/JP),
original stage0 3.0f/-3.0f position, native random(0,60) and
00453A70 effect 0x323; `0x34B` **278/1,012** with true
0040FB70 raw `DWORD,DWORD` position/angle calls (no spurious
FLD/FSTP), float global 00657478 velocity change, native
random(0,15)-60 and effect 0x324. Both compile into native
**strict original GPR/x87/relative branch/per-instruction width
codegen** with **18+17 authentic zero-addend physical COFF fields**.

In the SAME enlarged ordinary C++ TU, earlier native action0x331
still contains 274 instructions/1,003 native bytes, but newly
compiled source now needs 997 rather than previous 985 bytes.
Original native EBP−0x90/−0x94/−0x98 actual integer-to-FPU temps
are now candidate −0x80/−0x84/−0x88: only original MOV/FILD
ordinals 97/98 have +3 native bytes each, while the other four
ops are equally disp32. This is a **12-byte genuine natural
compiler-context improvement**, not artificially padded source.
Native original 0x330 still needs +18 width bytes; source 0x332
now has its temp at −0x8C rather than earlier −0x84, both genuine
disp32 source modes. New shared original-only
`verify-characterobject-native-frame-f586.py` asserts the exact
native real temp EBP slots, per-ordinal register/x87 grammar and
only two physically observed source modes, and historical case
verifiers now accept both rather than inaccurate +18/+18 claims.

F572–F586 now prove **39 distinct whole original native game-action
bodies, 5,651 original x86 instruction roles /21,245 internal
CODE bytes and 389 genuine physical COFF call/global fields**, all
60 native jump-table DWORD COFF slots, 198 literal compressed
index bytes and 438 separate after-RET native DATA layout bytes.
The **whole 33,293 native giant is not exact** and inner bodies
cannot be accepted as standalone functions; no all-unit cold replay
or external Oracle. Reproducer
`scripts/repo-python scripts/verify-characterobject-late-stage-actions-f586.py`;
[F586 original late-stage source audit](CHARACTEROBJECT_LATE_STAGES_F586.md).


## F587: full 397-instruction CharacterObject 0x34C and zero new EBP width gap in action0x331

The original Japanese 33,293-byte CharacterObject whole giant
`004EBDA0` has an authentic 397 x86/1,529-CODE-byte four-state
`0x34C` action with real parent signed states 0x198/0x19C/
0x19A/0x19D, 8-effect spawn loop, position x87 globals
006590A8/00658264, original conditional 0040FB40(5), x87
scale/color decay and original stage3 branch policy. Four
independent real parent states generate **native** 0x322,
0x323,0x324 and 0x325 original game effect IDs, using actual
00455580 random offsets (-5,+30,-5,-random-30), original
00453A70 computed-position spawns and 00453D40(6).
The new normal VC7.1 source case reproduces ALL original 397
register/x87/CFG/per-instruction byte widths and strict
machine-order grammar with **25 actual typed zero-addend native
COFF source fields**, not a partial case prefix. Whole 60-DWORD
sparse switch/data remain authentic.

Adding this real 397-insn C++ case to the same containing switch
naturally changes previously source-compact action0x331's VC7.1
integer-to-FPU temps to `EBP−0x84/−0x88/−0x8C`, all disp32.
Source 0x331 is now **274 x86/1,003 bytes**, identical *width*
to original native, while original native temps still reside at
−0x90/−0x94/−0x98, hence not actual byte-exact CODE. The
strict original-PE helper F586 now recognizes exactly three
real proven source-frame contexts, not arbitrary stack sizes.

In this one natural C++ source, F572–F587 now verify **40 complete
original game-action case bodies, 6,048 native x86 instruction
roles /22,774 internal native CODE bytes /414 true typed physical
COFF fields**, 60 real physical handler DWORD refs, 198 literal
compressed bytes, 438 distinct after-RET DATA-layout bytes.
The entire original **33,293-byte giant remains nonexact**.
No standalone action/whole CODE credit, all-unit replay or Oracle.
Reproducer `scripts/repo-python scripts/verify-characterobject-four-way-event-f587.py`,
[F587 original four-state source study](CHARACTEROBJECT_FOUR_WAY_EVENT_F587.md).


## F588: three strict native game stages and real original EBP temp location identity

Original Japanese entire `004EBDA0` CharacterObject giant (33,293
whole original CODE bytes) has three more genuine complete native
case bodies: `0x34D` 190 x86/697 original CODE bytes with native
five-effect parent loop, real raw DWORD C8/CC bit-preserved copies
into +0x50/+0x54, contact threshold 0065782C, distinct parent
effects 0x32B/0x32D and actor state0x33B; `0x34E` 163/603
with real four-effect loop, signed D8>2 fade, *no* additional
stage0 7C/80 stores, x87 speed floor2.0 and 0040FB40(1)
increment; `0x34F` 161/599 with signed D8>1, real own stage0
7C/80 stores and a direct 0045B830 reset. All three freshly
compiled normal VC7.1 C++ cases match exact native x86
GPR/x87/CFG/per-instruction byte-width source **with
35 total typed zero-addend COFF call/global references**.
Original 0x34F ends at genuine next nondefault `0x370`, not an
invented 0x350 action. Whole native first-switch 60-DWORD/
198-index DATA shape still byte/COFF valid.

The added real source ALSO naturally recovers **original actual
EBP stack-operand offsets**, not only native disp32 width, in
previously verified cases: native 0x330 original `−0x84/−0x88/
−0x8C`, native 0x331 original `−0x90/−0x94/−0x98`, native
0x332 original `−0x9C` are now the **same literal EBP locations
in freshly compiled C++**. The native-specific strict case
verifiers require these complete original PE positions and the
real 274/279 GPR/x87/relative-branch roles. Historical native
surplus JSON is now dynamic and zero in this source, not a false
hard-coded 18 byte difference. No synthetic local padding.

The same original-backed selected source now validates **43 complete
original game-action bodies, 6,562 native x86 instruction roles,
24,673 original internal CODE bytes and 449 genuine typed physical
COFF fields**, plus all 60 original switch DWORD COFF handlers,
198 byte-identical sparse bytes and distinct 438 after-RET DATA.
Original entire giant remains NONEXACT, no independent case CODE
credit or all-unit cold replay/Oracle. Reproducer
`scripts/repo-python scripts/verify-characterobject-three-late-actions-f588.py`;
[F588 full native x87 stage source](CHARACTEROBJECT_THREE_NATIVE_STAGES_F588.md).


## F589: entire 248-byte SceneObject virtual destructor texture-delete controls

Real Japanese original `0043B0B0` SceneObject virtual destructor
is **248 complete native CODE bytes/75 x86 instructions** with
true EH `00655B86`, vtable `00658334`, frame clock global
`0066C238`, real texture scalar delete `00425460`, THREE
real CRT frees `00640F15` and base virtual destructor
`00431F40` among **12 authentic typed zero-addend physical COFF
fields**. The original scene texture/delete EBP temporary slots
are `−0x14/−0x10` while the three free-owned pointers are
`−0x18/−0x1C/−0x20`; ordinary VC7.1 C++ yields native-sized
248/75 but texture locals `−0x20/−0x1C`, frees `−0x18/−0x14/
−0x10`. These are exactly **nine original nonfield bytes**
different in the complete 191/200-byte comparison.

Fourteen NEW real source-only VC7.1 `/GX` texture delete expression
forms, including explicit C++ pointer casts, true lvalue/const
reference/pointer-to-pointer deref, byte-offset alias and three
conditional source controls, were physically compiled and compared
as COMPLETE original functions. Eleven remain **248/75, 191/200
nonfield bytes, 12/12 genuine native PE call/global COFF refs**,
with the same EBP offsets; three instead emit 267/272 bytes.
Zero whole/source exact credit. Reproducer
`scripts/repo-python scripts/verify-scene-texture-delete-f589.py`,
source-only fixture `probes/BattleSceneTextureDeleteF589.cpp`,
[F589 original scene EH/delete study](SCENE_TEXTURE_DELETE_CONTROLS_F589.md).
Original resource ownership/lifetime, not a superficial cast,
remains to be reconstructed. No all-unit replay or Oracle.


## F590: original guarded/selected native cases0x370,371,384

The whole original 33,293-byte Japanese CharacterObject giant
`004EBDA0` now has three more complete game-action C++ sources:
`0x370` **79 native x86/286 CODE bytes** with parent state0x133,
signed direction byte times260 and actual original parent float
global 006590A0, additive global 006583FC, multiplicative
**same float global 00659090** via FMUL and native 20-step fade;
`0x371` **44/156** with literal 0.85f x/y scales, sprite0x4E2,
-65f offset and genuine x87 subtraction global 00659728;
`0x384` **128/473** with parent signed +0x3A0 guard,
real stage-zero FMUL 006590B4 on both velocities, native contact
global 0065782C, real effect0x388 and action0x385, plus
**signed-byte PE global006714D0** conditionally selecting0x38E.
All three newly compiled C++ game case bodies match the entire
original x86 GPR/x87/branch/individual byte-width grammar.
`0x384` alone has actual `MOVSX ECX, BYTE PTR [006714D0]`
versus C++ zero-linked global: the one place is independently
verified by physical `DIR32` symbol/offset/zero addend at original
ordinal102, not waived as arbitrary source discrepancy.
Original 0x371 next physical nondefault handler is0x384, not0x372.

F572–F590's one ordinary MSVC7.1 source now validates **46
complete original game-action bodies, 6,813 x86 native instruction
roles, 25,588 original internal CODE bytes, 474 real typed
original-PE-targeted COFF call/global fields**, all 60 native
first-switch handler DWORD refs and 198 byte-identical native
sparse indexes plus 438 distinct original after-RET DATA-layout
bytes. Complete 33,293-byte boss remains **NONEXACT**, no split
case or whole CODE/DATA credit, no cold all-unit replay/Oracle.
Reproducer:
`scripts/repo-python scripts/verify-characterobject-guarded-stages-f590.py`,
[F590 original guarded cases study](CHARACTEROBJECT_GUARDED_STAGES_F590.md).


## F591: actual 0x385/0x386/0x387 native actor fade branches

Original complete 33,293-byte CharacterObject giant `004EBDA0`
now has true 0x385/0x386/0x387 source bodies recovered in the
same normal VC7.1 function. Real 0x385 is 138 x86/511 original
CODE bytes, initializes 0.75f scale, native parent 00453E60(5f),
parent effects0x387 and stage2 effect0x386, float global
00659724 x2 and stage>1 color fade by 40.
Real 0x386 (84/330) has no parent FX and **ALWAYS fades by 20**
even at stage0; copying 0x385's stage>1 condition generated four
extra x86 instructions. Fixing the true original native stage
condition also gave exact GPR roles in the next source case.
Real 0x387 (74/262) has native 0.75f scales, original sprite
short 0x4E2, -75.0f offset, real global 006583F8 twice,
stage>1 and strictly >20-opacity fade with no forced byte-zero.
All three whole case grammar and byte widths are strictly
original PE-backed; **24 physical typed COFF source refs** are
matched at their native ordinals, zero addend. Across F572–F591,
**49 real original game actions, 7,109 original x86 roles,
26,691 inner original CODE bytes, 498 genuine physical typed
COFF records**, 60 DWORD jump targets and 198 exact sparse byte
indexes, distinct 438 after-RET DATA-layout bytes. Entire giant
still NONEXACT, inner cases do not count as standalone functions,
no all-unit cold replay/Oracle.
Source/verifier:
`scripts/repo-python scripts/verify-characterobject-stage-fades-f591.py`,
[F591 original stage fade study](CHARACTEROBJECT_STAGE_FADES_F591.md).


## F592: five original entire x87 angle/trajectory game states and real external ABI

Japanese original giant `004EBDA0` gets five more complete native
case sources: `0x388` 92 x86/334 CODE bytes (genuine original
45-range float scatter and x87 world threshold), `0x389`
174/627 (native -30/150 signed state, stage4 effect 0x371,
stage8 fade/loop), `0x38A` **234/971** (true 00483300
computed two-float aiming, FIMUL, __ftol2, native byte global
006714D0, TWO independent signed angular correction tests),
`0x38B` **260/953** (native 00455580(-480,960), signed
stage0 opacity ramp, stage8 raw DWORD parent+318/+31C copies
and real effects 0x38C/0x38D), `0x38C` 74/276 (true
00428D20 magnitude of two squared floats, x87 division and
same 00483300 external helper with original raw DWORD arguments).
Natural C++ has all 834 newly verified x86 register/x87/branch
and original byte-width instruction roles with **64 real typed
zero-addend original PE/COFF call/global fields**, including
physical `DIR32` MOVSX of global 006714D0, not an ignored
linker-field difference. Rewriting the 38A two actual angle
corrections as `if/else` is semantically wrong and shortened
native machine code; two independent guards plus an inner
`break` restore the original 234/971. Real subsequent source
cases restore preceding natural compiler near-jump widths.

Only 54 actual complete case source bodies are strict original
GPR/CFG verified; F592 also retains **unverified whole-source
hypotheses 0x38D/0x38E**, which are not counted as exact
or source-verified original inner cases. Cumulative **7,943
whole original native x86 roles /29,852 original internal CODE
bytes /562 native PE typed COFF fields** in one VC7.1 TU;
all 60 original physical first-switch handler DWORDs,
198 byte-identical compressed indexes and distinct 438 afterRET
DATA. The whole original 33,293-byte giant stays nonexact.
Reproducer
`scripts/repo-python scripts/verify-characterobject-five-complex-actions-f592.py`,
[F592 source/physical COFF study](CHARACTEROBJECT_COMPLEX_AIM_F592.md).
No full cold replay, independent CODE credit or external Oracle.


## F593: entire original 33,293 CODE-byte fighter geometry and 682 genuine PE fields

Japanese original `004EBDA0` CharacterObject megaboss now has
natural C++ source in ALL original compressed native action bodies
and a REAL default branch `default: GetStateAt40FA30();`
reproducing native `004F3FA1 MOV ECX,[EBP-0x40]; CALL 0040FA30`
in 8 bytes (not prior 10-byte fabricated marker store).
The entire one-TU MSVC7.1 normal source emits **33,293 CODE
bytes, 8,789 x86 instruction offsets and sizes fully identical
to original native**, 438 separate postRET DATA bytes, and
**682 physical zero-addend genuine original PE-targeted typed
COFF fields**, 622 inside executable CODE and 60 in the dense
switch DWORD DATA table. All 198 native sparse-index bytes remain
literal identical. Genuine PE/COFF original symbol targets are
independently checked from original relocated fields, including
two true local switch labels and true external `__ftol2` call.

An official independent relocation-aware comparison of the FULL
original **33,731-byte CODE+DATA object** confirms
**30,848/31,003 identical nonfield bytes** and **155 residual
nonfield different bytes across exactly 139 x86 instruction
positions**: six in three previously proved independent MOV/FLD
read-order swaps, 45 GPR roles in whole action38D, 64 in action38E,
24 in native action3E3's first31 instructions. The entire
8,789 instruction original/compiled ordered mnemonic sequences
differ in only the 6 previously known read-read swaps; even
individual x86 encoded byte widths/physical offsets are identical.
**These facts DO NOT constitute native CODE byte-exact acceptance.**

New native source-strict physical complete 3E4 is **261 original
x86/1,126 CODE bytes/19 typed native PE fields**, with original
parent-state policy using +0xEFA/+0x3B6/+0x3B0/+0x36C, FCOMP
qword00659228, float00657478, and real x87 parent-first
FLD/FADD from ordinary true lvalue
`PARENT_TARGET_Y + *(&gCollisionAt00657888)`.
Native final action3E5 is **96 x86/396 CODE bytes/5 real typed
PE fields**, with original float(P16(+0x3A0))/S16(+0xD8)*2.0f
producing FILD/FIDIV/FADD ST(0),ST(0) and TWO original
separate short return jumps. An otherwise identical standalone
3E5-only source emits 70 wrong GPR assignments: real adjacent
3E3/3E4 ordinary C++ source is needed to recover native register
allocation context. Strict cumulative game case source evidence
now **56 entire original cases /8,300 native instruction roles /
31,374 original inner CODE bytes /586 typed case COFF refs**;
remaining source 38D/38E/3E3 has native-sized body but still
GPR nonexact. Original 33,293-byte whole giant still NONEXACT,
zero standalone or whole CODE/DATA exact credit, no full cold
all-unit replay/Oracle.
Targeted reproducer
`scripts/repo-python scripts/verify-characterobject-whole-geometry-f593.py`,
[F593 entire original fighter source/COFF study](CHARACTEROBJECT_WHOLE_GEOMETRY_F593.md).


## F594–F595: original giant register-phase negative controls plus fully byte-exact small origin-unknown setter

F594 tested 23 *genuine* pinned VC7.1 normal C++ variants targeting
the actual original giant `004EBDA0` native case38D register
rotation beginning at ordinal91, continuing across 38E into
only first31 instructions of 3E3. Alternatives varied x87
float member assignment, native lvalue reference, stage constant
order/condition, valid ownership field type and counter updates.
None recovered the original whole C++ GPR register phase; the
same original **155 differing nonrelocation whole native bytes**
remain, with source original 8,789/8,789 instruction lengths and
all 682 physical original PE COFF fields still verified in F593.
The 23 actual original-backed compile logs/objects and native
case metrics are retained under `.analysis/f594-register-phase/`.

Separately F595 attacks SMALL original origin-unknown leaf
`004135F0`: actual 40 native CODE bytes/16 x86 instructions,
no COFF references, three literal thiscall field stores at
+0x24/+0x1C/+0x20 and `RET 0xC`. New natural VC7.1 source
`probes/NativeFieldSetterOriginPendingF595.cpp` **exactly
matches all 40/40 native machine bytes** independently
via whole original PE/COFF checker. Full call-graph research
across 4,351 registered native functions finds NO direct
callers or original raw 32-bit literal address references,
so its original authored/vendor owner is **unknown** and it
receives **zero accepted game CODE credit**.
Peer audited pending 45-byte base ctor `00449DE0` has
36 native direct original callers from previously exact
BackgroundStage::LoadBGxx source functions and a 5-purecall
vtable at 0065844C, but still compiler-implicit/explicit
constructor origin ambiguity. Pending destructor 004588B0
has six mixed source callers across authored resource
load and STL vector/runtime contexts; also still unknown.
Reproducer
`scripts/repo-python scripts/verify-native-pending-fieldsetter-f595.py`,
[F595 original small leaf and owner evidence](SMALL_ORIGIN_UNKNOWN_FIELDSETTER_F595.md).
Official 943 original whole exact functions /862,726 authored
CODE bytes unchanged; no all-unit cold replay or Oracle.


## F596: exact original native x87 collision source order throughout a 33K fighter giant

Three original Japanese native cases in whole giant `004EBDA0`
previously had one strictly bounded but byte-wrong independent
`MOV`/`FLD` read-read pair apiece: original action0x32A (native
case ordinals186/187; entire function1062/1063), 0x32C
(114/115; whole1350/1351), and 0x335 (146/147; whole
2521/2522). Their ordinary C++ source `F32(0x48) ± F32(0x54)`
preloaded the second receiver register after reading the first
x87 float; the original had both receiver lvalues loaded
before `FLD`. Changing the three true gameplay expressions to
`*(&F32(0x48)) ± *(&F32(0x54))` causes native VC7.1 to emit
**all SIX exact native original 3-byte MOV/FLD instructions in
original byte-identical order**. No fake locals or ASM and
no changes to original motion/control semantics.

Entire original 33,293 CODE-byte `004EBDA0` now has **all
8,789/8,789 original native x86 instruction mnemonics at the
same ordinal**, every instruction offset/individual byte width
identical, all **622 CODE +60 after-RET native typed PE COFF
references** with original destination/zero addends, 438
original afterRET DATA layout and 198 byte-identical sparse
index bytes. Whole original original-PE nonfield comparison
is **30,866/31,003 bytes identical** (F593 prior
30,848/31,003), leaving **137 residual bytes over 133
instructions** in the three register-rotated cases38D,38E,3E3.
56 full native source case bodies remain strict; whole giant
still byte-NONEXACT. F573–F583 historical PE verifiers now
accept only physical original read order or exact, previously
proven historical harmless swap, and current source reports no
remaining read-swap exceptions.
Original-backed full source proof:
`scripts/repo-python scripts/verify-characterobject-native-collision-order-f596.py`;
[F596 strict native x87 order study](CHARACTEROBJECT_NATIVE_COLLISION_ORDER_F596.md).
The original 943 whole authored exact functions/862,726 CODE
bytes are unchanged, no all-unit replay or Oracle.


## F598: real action50 contact-return source inside eleven unmatched giant fighter controllers

New PE-backed standalone original action50/`0x32` native case is a **58-x86
instruction** interior of each of eleven separate large fighter originals.
The original branch is an independent `CMP state,0x32; JE`, followed by
true `0x33` indexed case boundary. One shared natural C++ singleton
`probes/FighterSingletonContactF598.inc` corrects the originally
misread x87 comparisons to **`POS < zero`** then **`POS > zero`**
and matches the real `00454EE0` signed-byte contact callback, signed
`this+0x3BE`, float×double `006583E8` projection to `this+0x490`,
and `0040FA30` / `0040FAC0(0)` state transition.

All **11/11** original entire SHA-pinned giant contexts were freshly
compiled with the new case included in actual `Advance()` C++ (no ASM
or stubbed inner case). Each case matches **58 original x86 GPR/x87/
branch instruction roles, exactly seven typed COFF call/global fields
with genuine original addresses and zero addends**. Ten cases match
205-byte native length, one wide-frame `00564BE0` native is 256 bytes
against 205 candidate solely because 17 genuine receiver MOVs use
3-byte larger EBP-0x88 displacements. Old 121 case shapes and full
seven-switch COFF/DATA geometry are still verified. Across the eleven
nonexact parent giants: 132 real source-backed internal cases, 7,473
native instruction roles, 26,835 original internal CODE bytes and
867 physical typed case fields. **ZERO** new whole exact function
credit, no after-RET DATA credit, no all-unit cold replay.

Six original-backed candidate C++ changes to giant `004EBDA0`
case38D register-phase, plus six real 171-byte native archive
destructor filename/free lifetime tests, were also compiled and
**negative** (the direct-free tradeoff fixes deletion stack slots but
loses two real instructions). Preserve their ignored negative controls
in `.analysis/f598-native-register-investigation/` and
`.analysis/f598-archive-declaration/`. Targeted original/source
reproducer `scripts/repo-python
scripts/verify-fighter-singleton-contact-f598.py --boss 0x004F7130`;
full detail [F598 giant and small original source study](FIGHTER_SINGLETON_CONTACT_F598.md).


## F599: two entire native record-copy functions match ordinary compiler-generated C++

Independent physical-PE-only comparison plus fresh pinned VC7.1 source
probes reconstructed complete origin-unknown `0045AAE0` (368 CODE
bytes/118 x86/two native `REL32` fields to `0045AC50`) as an implicit
116-byte-record assignment operator and `004591E0` (417 CODE bytes/128
x86/six native `DIR32`/`REL32` fields including `00459390` copy
construction and exception-chain metadata) as an implicit record copy
constructor under `/GX`. **Both fully linked whole original code
functions are byte-for-byte exact**, with 360/360 plus 393/393
nonrelocation byte matches and all eight original destination fields.
Turning `/GX` off instead makes a shorter 368-byte copy constructor
with only two relocations and thus *does not* reproduce the original
417-byte EH code. The 116-byte struct and its two 16-byte original
copy/assign member calls are real compiler-source-shape witnesses,
**not identified original owner/type declarations**. Out-of-line EH
handler metadata is separately unverified and earns no CODE/DATA credit.

Fresh independent original PE CALL graph over all 4,351 function
boundaries found three genuine direct library-classified callers
per unknown special member: constructor from `00458E70`, `00459CB0`,
`0045B640`; assignment from `0045A950`, `0045AFB0`, `0045B0C0`.
Those original call relationships show STL/vector element use but
**do not distinguish authored explicit owner vs compiler implicit**
special members. Both original functions stay `unknown` origin,
`unclassified` CODE and **ZERO official authored exact credit**.
Real C++ source `probes/Record116ImplicitCopyF599.cpp`; targeted
verifier `scripts/repo-python scripts/verify-record116-implicit-copies-f599.py
--with-negative-gxoff`; [full F599 special-member study](RECORD116_IMPLICIT_COPY_ORIGIN_F599.md).
No all-unit cold replay or external Oracle.


## F600: original indexed action0x33, next distinct game case in eleven huge fighters

F600 independently reverified all eleven pinned original multi-switch
Fighter CODE+afterRET DATA and discovered their actual second sparse
switch action51 (`0x33`) physical bounds from real original first
two DWORD slots plus literal first map indices 0,1. All eleven native
blocks have **58 x86**, ten **205 bytes** and wide saved-this
`00564BE0` **256 bytes**. Their actual gameplay differs from F598
singleton0x32 in a `POS = -9.0f` vs `-8.0f` initializer and naturally
rotated VC7.1 GPR cycle. Real C++ inner source
`probes/FighterIndexedContact51F600.inc` independently matches all
**58 original GPR/x87/branch instruction roles** and all **seven
physical typed actual-original-target COFF fields** per giant with
real zero addends. The one 256-byte native case is explained solely
by 17 original EBP-0x88 load displacement +3 widths. All older
11 original cases, complete F598 case50 and original switch COFF/DATA
remain reverified in the new twelve+one-case source build.

New F600 native interior evidence: **11 blocks /638 original x86
/2,306 native CODE bytes /77 typed COFF fields**. Together with
original F567+F598, **143 distinct complete original case subranges
/8,111 x86 roles/29,141 original interior CODE bytes/944 typed
fields** across eleven *still nonexact* huge originals. These are
not 143 whole functions: ZERO new original whole author CODE exact
credit, no split case adoption and no full 943-unit cold replay.
Tracked targeted probe
`scripts/repo-python scripts/verify-fighter-indexed-contact51-f600.py
--boss 0x004F7130`; [F600 original native case](FIGHTER_INDEXED_CONTACT51_F600.md).


## F600: true follow-on contact states across eleven *whole* giant original fighter functions

Original Japanese TH075 1.11 PE was independently redecoded for
all 121 new native complete action cases `0x33/34/35/38/39/3A/3B/3E/3F/40/41`,
with the true compressed *distinct case* second-table order, preserving
all earlier opening case0..10 and F598 action0x32. The tracked natural
C++ source in `probes/FighterAdditionalContactF600.inc` now reproduces
**7,711 original complete GPR/x87/branch roles**, all genuine case
opcodes/widths except exactly the original wide EBP-0x88 receiver
displacements at `00564BE0`, **28,399 original internal CODE bytes**
(10*2,525 + 3,149) and **880 physically typed original PE/COFF
call/global destinations**. Original counter `+0xEFC` is confirmed
for `005AEEC0`; the other ten are `+0xF00`. Three long cases
initially clear and later increment this counter only on original
stage-7 conditions; cases `0x3E/3F/40` push transition state 2,
not 0. Every case is inside its authentic still-incomplete giant.
Together with F598 earlier actions this is 253 PE-backed inner cases/
55,234 noncredited original CODE bytes, **zero newly accepted authored
whole function bytes**, no all-unit cold replay or external Oracle.
Detailed original evidence [F600 second contact switch](FIGHTER_ADDITIONAL_CONTACT_F600.md)
and targeted compiler proof `scripts/repo-python scripts/verify-fighter-additional-contact-f600.py --boss 0x004F7130`.


## F601: derive per-original Fighter contact stage-counter owner directly from three whole native cases

Further original PE recheck disproved the idea that all 11 second-switch
actor owners use one counter offset: actual original `005AEEC0` native
cases `0x35`, `0x3B`, `0x41` access signed 16-bit `this+0xEFC`, while
the ten other fighter originals each access `this+0xF00`. Reusing the
ordinary `+0xF00` source for `005AEEC0` compiles the same 79 original
instruction slots but **fails real native member operands in five
instructions in each stage case**; it is not correct C++ source for
that fighter. The F600 targeted verifier now **attests all three real
original case extents, reads each original member displacement,
requires identical offsets per boss, THEN derives a C++ macro from
the PE** before compiling under VC7.1. No address→guessed-field
exception remains in source generation; full native x86 roles/field
COFF/switch DATA remain verified after each targeted compilation.
Reproducer `scripts/repo-python scripts/verify-fighter-additional-contact-f600.py
--boss 0x005AEEC0`; [F600 original-index source with new F601
owner-attestation](FIGHTER_ADDITIONAL_CONTACT_F600.md). Whole original
giant NONEXACT; zero new official accepted authored CODE, no full cold
replay.


## F601: complete 21+37-byte original atan2 C++ adapters, plus original destructor lifetime negatives

From the pinned Japanese TH075 PE, original complete `00483300`
(21 bytes /10 x86 /one true `REL32` to `00483320`) and original
`00483320` (37 bytes/15 x86/one true `REL32` to genuine CRT `_atan2`
`00642240`) compile naturally under VC7.1 as cdecl float wrapper
and its float→double→float worker. Full **58/58 linked native CODE
bytes** agree after the two original physical relocation fields;
all 25 x86 instruction starts/widths/mnemonics also agree. Fresh
independent scan of 4,351 original registered full function extents
found **211 true CALL instructions across 16 authored game functions**
targeting `00483300` and exactly one direct call of `00483320`
from its wrapper. Those callers prove gameplay use but not original
adapter provenance; both leaf origins remain `unknown` with no new
authored whole-exact CODE credit. The separate out-of-line CRT owner
remains library. Source `probes/FloatAtan2AdaptersF601.cpp`, full
original-backed targeted verifier `scripts/repo-python
scripts/verify-float-atan2-adapters-f601.py`; [F601 whole x86 and
real relocation research](FLOAT_ATAN2_ADAPTERS_F601.md).

New independent whole-native negative resource-lifetime experiments
in ignored `.analysis/f601-archive-reference/`,
`.analysis/f601-archive-sequenced/`, `.analysis/f601-scene-lifetime/`
found no 171-byte original ArchiveCatalog destructor stack-slot fix
(pointer/reference return and comma-sequencing: best 108/115) or
248-byte SceneObject destructor local-slot fix (resource aggregate
reordering: best 191/200). All affected C++ TUs were individually
cold compiled; nonexact branches were not falsely accepted.


## F602: entire original native trajectory action0x46 source across nine giant fighter bosses

Original Japanese TH075 native second-indexed-switch action0x46
was independently bounded from true physical dense DWORDs for case0x46
and next case0x47. Nine complete 104-instruction branches are now
verified in freshly compiled ordinary VC7.1 C++ `Advance()` sources,
including 15 true typed PE/COFF fields per original game case.
The actual x87 order required natural reference-to-member expression
`*(&POS54)+*(&F32(0x98))` for an original `FLD + FADD` and
parenthesized `(POS54) * global` for original `FLD member; FMUL global`.
Physical original per-fighter stage, speed bounds, dynamic state,
float-to-signed-short `__ftol2` with two adjacent native owner fields,
original callee symbols and the genuine wide EBP-0x88 (**33 original
widened receiver `MOV` loads plus three short-to-near `Jcc` expansions**,
exactly 111 original extra bytes) were checked. This corrects the
older mistaken 37-widened-MOV summary with individual original x86
byte widths; game behavior and source case stay unchanged. F602 adds **936 x86 native roles,
3,477 original internal native CODE bytes, 135 typed PE/COFF fields**
on top of prior 253 game case subranges; all nine whole originals
remain nonexact and the two other 131-instruction action0x46 owners
remain undone. Source `probes/FighterTrajectoryContact46F602.inc`,
selected local proof `scripts/repo-python scripts/verify-fighter-trajectory46-f602.py
--boss 0x004F7130`; [F602 original 0x46 study](FIGHTER_TRAJECTORY_ACTION46_F602.md).
No new independent/whole exact authored CODE or all-unit cold replay.


## F603: actual original 131-instruction trajectory + one-shot projectile cases in last two giants

Real second switch native original action0x46 in `0045DD70` and
`0058AF60` contains **131 x86 instructions /459 whole interior CODE
bytes /16 actual typed PE/COFF refs** per original, adding 27 real
stage1 projectile instructions over the shorter F602 104-insn path.
The original source uses signed stage+0x62=1, frame+0x64=0,
new one-shot flag+0xF0C=1 and real `00453A70` receiver call with
actual projectile IDs `0x3B7` vs `0x3E7`, final side 1 vs 0. The
rest retains different native stage2/3 and aux3/4/5 policies,
original per-class float constants, two `__ftol2` to short member
+0xF00/+0xF02, natural C++ x87 evaluation order and full existing
23-case native switch/afterRET table. Freshly compiled ordinary VC7.1
C++ from `probes/FighterTrajectorySpawn46F603.inc` has 131/131
native GPR/x87/CFG roles and 16/16 true PE-targeted fields in both
original fighters. New F603 original internal source: **2 cases,
262 native x86 roles, 918 uncredited game CODE bytes and 32 genuine
fields**. Across F598/F600/F602/F603: **264 inner original action
bodies / 59,629 internal CODE bytes**, all embedded in eleven
still NONEXACT gigantic game functions, zero adopted authored CODE
or full cold replay. [F603 native call/flag/codegen evidence](FIGHTER_TRAJECTORY_SPAWN_F603.md);
targeted `scripts/repo-python scripts/verify-fighter-trajectory-spawn-f603.py --boss 0x0045DD70`.


## F604: true complete 24+31 native game-like source leaves, unsigned bit-test and original owner audit

Independent original Japanese TH075 PE verified two previously
unclassified whole native functions: `00454C00` is 24 bytes/9 x86,
clearing receiver member DWORD `+0x47C`; `00454F70` is 31 bytes/15
x86, testing unsigned `0x20` flag of a state object at `this+0x74` /
`state+0x3C`. One ordinary VC7.1 source TU now emits all **55/55
whole original byte-identical CODE bytes**, no relocations. The exact
31-byte original bit-test uses **unsigned `>0`** (`XOR/CMP/SBB/NEG`),
not equivalent `!=0` (29B/14 x86) or signed `>0` (30B/14 x86).
Neither full class owner has been identified, and an independent
4,351-original-function direct-call scan and full PE literal DWORD
scan found no explicit references to either address; indirect uses
are not ruled out and both origins stay **unknown**. No authored
exact credit or full cold replay. Tracked source:
`probes/SceneFlagAndCounterLeavesF604.cpp`; selected positive and
negative reproducer `scripts/repo-python
scripts/verify-scene-flag-counter-leaves-f604.py --negative-predicate`,
[F604 original bit-test and provenance](SCENE_FLAG_COUNTER_LEAVES_F604.md).

Additional complete 171-byte original archive destructor source-only
trials under ignored `.analysis/f604-archive-compiler-local-layout/`
excluded register/const and alignment variations as explanations
for its seven nonrelocation EBP-ownership mismatches. Native original
stack slots remain unresolved, zero new accepted authored destructor
CODE; no all-unit cold replay.


## F605: complete original 86-instruction trajectory follow-ups in nine huge game fighters

Original Japanese TH075 PE independently verifies true packed second
switch actions `0x47`/`0x48` as 18 complete native internal subranges
across nine giant fighters: **1,548 complete original GPR/x87/CFG
x86 roles, 5,756 original interior CODE bytes and 234 genuine typed
COFF destination fields**. A key source-model correction: native
`this+0x98` → `this+0x54` is a raw DWORD `MOV` not a float
`FLD/FSTP` expression. Genuine `I32(0x54)=I32(0x98)` naturally fixes
the original register cycle from the first differing GPR onward.
Original 0.8f/1.3f drag, per-fighter/per-case stage and auxiliary
states, two real float→short CRT conversions and original `+0xF00`
vs `+0xEFC` owner slot distinctions are independently native-verified.
The special original `00564BE0` 398 vs 310-byte native case includes
28 wide `EBP−0x88` receiver loads and one short-to-near `JP` expansion
per action. All prior 24 game cases and complete original afterRET
switch DATA are preserved in fresh selected VC7.1 C++ objects.
The other original fighters `0045DD70`/`0058AF60` need separate
113-instruction action-specific spawn work; nine full giants still
NONEXACT. Cumulative 282 source-backed original **internal** cases/
65,385 CODE bytes are **not** 282 separate complete-function matches;
official 943/862,726 accepted authored CODE unchanged.
[Full original F605 evidence](FIGHTER_TRAJECTORY_FOLLOWUPS_F605.md),
`probes/FighterTrajectoryFollowupsF605.inc`, targeted
`scripts/repo-python scripts/verify-fighter-trajectory-followups-f605.py
--boss 0x004F7130`. No 943-unit cold replay or Oracle acceptance.


## F606: genuine original 0x47/0x48 staged projectile order in two special giants

Actual original Japanese PE exposes one surprising source-order
difference across the two remaining projectile-spawning game fighters:
`0045DD70` action0x47 has original 113-instruction stage-one
projectile then early auxiliary-state check; its action0x48 is plain
86-instruction trajectory. `0058AF60` action0x47 is also a
113-instruction stage-one projectile **before** the early exit, but
its native action0x48 has the same 113 original x86 count with the
projectile branch **AFTER** the stage-2 early-state return. Two
natural C++ case source bodies explicitly preserve original behavior
using true flag+0xF0C, native x87 motion, real signed-short velocity
conversion and actual 0x3B7/0x3E7 ID+side parameters. Fresh separate
pinned VC7.1 whole-parent source compilations reproduce the complete
native **425 GPR/x87/CFG roles, 1,495 internal CODE bytes and
55 individually typed physical PE/COFF fields** across four original
cases, preserving all previous 24 PE-backed actions and entire afterRET
jump DATA. With F605, all 22 true original 0x47/48 case subranges
(1,973 x86 roles, 7,251 original native CODE bytes, 289 typed fields)
are source-backed; with earlier giant case proofs 286 original
**internal** actions/66,880 original inner CODE bytes, NO whole-giant
exactness or independent case credit. [F606 exact PE/order evidence](FIGHTER_TRAJECTORY_FOLLOWUP_SPAWNS_F606.md),
`probes/FighterTrajectoryFollowupSpawnF606.inc`,
`probes/FighterTrajectoryFollowupLateSpawnF606.inc`; targeted
`scripts/repo-python scripts/verify-fighter-trajectory-followup-spawns-f606.py --boss 0x0058AF60`.
Official 943 whole authored exact functions/862,726 CODE bytes
unchanged; no all-unit cold replay or external Oracle.


## F607: original native 99-instruction landing action0x49 in nine giant fighters

Real second packed-switch native original action0x49 (bounded by
physical dense jump slots 14/15) has been source-reconstructed for
nine original whole fighter C++ bodies. Genuine VC7.1 natural C++
source `probes/FighterTrajectoryLanding49F607.inc` emits all **99
native instruction roles /350 ordinary-source bytes per case**, with
15 original typed COFF call/float destinations including two precise
`FLD`-float relocation operands. A source trial demonstrated that
`*(&POS)==g_ThresholdAt0065782C` plus **two separate switch
`break`s** preserves the actual original x87 `FUCOMPP` ordering and
both end-of-switch `JMP`s, correcting a 347-byte near miss.
Eight real native compact originals have 350 bytes, one `00564BE0`
original has 441 (29 genuinely widened saved receiver MOV plus one
real widened branch). All previous 26 native game action subranges
and full afterRET jump DATA are rechecked on each fresh giant source
object. F607 adds **9 genuine internal cases /891 original x86 roles
/3,241 original interior CODE bytes /135 actual native COFF fields**;
F598–F607 total 295 source-backed inner cases /70,121 original CODE
bytes. These are NOT complete whole-function adoptions; the other
two real 118-instruction action0x49 owner variants and full giant
CODE remain nonexact. [F607 original PE+source proof](FIGHTER_TRAJECTORY_LANDING_F607.md),
targeted `scripts/repo-python scripts/verify-fighter-trajectory-landing-f607.py --boss 0x004F7130`.
No full all-unit cold replay; official 943/862,726 authored exact unchanged.


## F608: real 118-instruction native 0x49 landing + stage-one projectile in two giant fighters

Independent original Japanese PE source evidence proves complete
indexed second-switch 0x49 inner CODE for `0045DD70` and `0058AF60`:
original **118 x86/420 native interior bytes/16 real typed PE/COFF
fields** per character, with original signed short flag `+0xF0C`,
original `00453A70` 5-argument game spawn ID 0x3B7 /0x3E7
and side 1/0, plus both original float `FUCOMPP` equality tests.
Pinned VC7.1 naturally generates the actual 118-instruction original
register/x87/CFG/order and 420-byte physical case, checked with all
16 typed physical COFF original target destinations. Earlier 26
original game action roles and entire physical afterRET switch DATA
remain verified on the newly compiled whole giant source object.
F608 adds **236 native x86 roles/840 uncredited original internal
CODE bytes/32 genuine COFF refs**; with F607 all 11 native action0x49
cases are source-backed (1,127 native roles/4,081 inner CODE/167
fields). F598–F608 total **297 inner cases/70,961 original CODE
bytes** while the entire giants remain NONEXACT and no independent
new authored CODE exactness is granted. [Original F608 physical
study](FIGHTER_TRAJECTORY_LANDING_SPAWN_F608.md),
`probes/FighterTrajectoryLandingSpawnF608.inc`, targeted
`scripts/repo-python scripts/verify-fighter-trajectory-landing-spawn-f608.py --boss 0x0058AF60`.
No all-unit cold replay, no external Oracle receipt.


## F609: independent original 171-byte ArchiveCatalog destructor source-type/loop controls

Full original pinned Japanese PE `0041CE50` is 171 native CODE bytes,
51 x86 instructions and 14 genuine physical typed COFF fields. F609
selected natural VC7.1 `/GX-` compilation of **19 whole source
variants** tried unsigned/signed and size_t loop index, equivalent
C++ increment, actual bracketed deletion and free scopes, meaningful
const/casts and pointer lvalues. Every variant emits the full
171/51 original geometry and 14 original physical fields but remains
**NONEXACT**: 18 at **108/115** original nonfield byte equality,
1 distinct inequality-loop diagnostic at **107/115**. The native
`EBP−0xC/−0x8/−0x10` resource/delete/name temp order remains
`EBP−0x10/−0xC/−0x8` in generated C++. These variants rule out
mere signedness, `for` spelling and simple lexical casts as the
remaining compiler stack-allocation cause; no fabricated locals,
partial acceptance or all-unit cold replay.
[Original F609 analysis](ARCHIVE_DESTRUCTOR_SOURCE_TYPES_F609.md),
selected `scripts/repo-python scripts/verify-archive-source-types-f609.py --case signed-index`.
Official whole authored exact units remain 943/862,726 native CODE bytes.


## F610: native bounce trajectory `0x4A` in nine giant fighters

Independent Japanese TH075 1.11 original PE reanalysis, fresh selected
VC7.1 C++ source and full original second packed-jump table proof
reconstructs nine **119-original-x86 /19-typed-COFF** native action0x4A
inner cases. They introduce original contact trigger `00454EE0`,
float threshold `006590C0`, bounce multiplier `00657F74`, native
action0x4C and action0x61, and real two `__ftol2` trajectory
projections. Original `005D73C0` places a real 0x16 preparation
**after** native 2.0f trajectory initialization; the other 8 regular
owners place it **before** the original x87 projection. The normal
cases are 434 native bytes; the wide-frame original `00564BE0` is
556 (38 genuinely expanded EBP−0x88 receiver MOV loads plus two
4-byte-expanded Jcc). All earlier 27 game cases and afterRET jump
DATA remain verified in each new original-backed source compilation.
F610 adds **9 actual inner cases /1,071 real x86 instruction roles /
4,028 uncredited original interior CODE bytes /171 physical typed
COFF refs**; F598–F610 studied **306** native inner case bodies/
74,989 original interior CODE bytes, not independent complete exact
functions. The other 2 giant action0x4A native 165-instruction spawn
variants remain open. [Original case/PE/codegen F610 study](FIGHTER_TRAJECTORY_BOUNCE_F610.md)
and selected `scripts/repo-python scripts/verify-fighter-trajectory-bounce-f610.py --boss 0x004F7130`.
No all-unit cold replay; authored exact 943/862,726 unchanged.


## F611: real original 165-instruction double-projectile bounce action0x4A in two giants

Original Japanese TH075 PE `0045DD70` and `0058AF60` 0x4A actions
have **165 x86/589 whole inner CODE bytes/21 physical PE/COFF typed
refs** per giant, not the 119-instruction regular F610 variant. An
extra two genuine original stage-one and collision-triggered guarded
`+0xF0C` projectile spawns use real `00453A70` thiscall,
`0x3B7`/`0x3E7` sprite kinds and original side 1/0. Natural pinned
VC7.1 source `probes/FighterTrajectoryBounceSpawn4AF611.inc` emits
all **330 native GPR/x87/CFG roles /1,178 original inner CODE bytes
/42 physical typed PE-targeted COFF fields** in newly compiled giant
source TUs. All prior 27 original cases and full afterRET switch
DATA remain source-verified; both entire fighters are still NONEXACT.
Combined F610/F611: all 11 original action0x4A case interiors are
source-backed, 1,401 true native x86 roles/5,206 original internal CODE
bytes/213 genuine typed fields. Overall F598–F611 studied 308 native
case interiors /76,167 original internal CODE bytes, **zero new whole
exact authored code**, no full cold replay or Oracle acceptance.
[F611 original PE/native source evidence](FIGHTER_TRAJECTORY_BOUNCE_SPAWN_F611.md),
selected `scripts/repo-python scripts/verify-fighter-trajectory-bounce-spawn-f611.py --boss 0x0058AF60`.


## F612: genuine whole 248-byte scene destructor freed-pointer type/array negatives

Independent pinned original Japanese `0043B0B0` SceneObject destructor
remains **248 native CODE/75 x86/12 real physical typed COFF fields**
with original `EBP−0x14/−0x10/−0x18/−0x1C/−0x20` texture/delete
and three resource-free stack positions. Fresh selected VC7.1 `/GX`
C++ controls test **22 actual pointer/aggregate source types**:
16 intact original-shaped candidates emit **248/75 with 191/200**
nonrelocation bytes equal; four true array field orders emit **189/200**;
two reference aliases change whole CODE to **254/78**, not original.
The two missing original texture-delete EBP source positions do not
change in any full-size form, so casts, pointee type, const/volatile
and straightforward free-value array ordering cannot explain the
source allocation mismatch. No fake padding or machine byte graft,
no accepted new authored whole CODE or 943-unit cold replay.
[Native original F612 investigation](SCENE_DESTRUCTOR_POINTER_TYPES_F612.md),
selected `scripts/repo-python scripts/verify-scene-freed-pointer-types-f612.py --case int-pointer`.
Official exact authored ledger remains 943/862,726 original CODE bytes.


## F613: native recovery action0x4C across eleven huge fighters, genuine one-shot versus every-frame CFG

Real Japanese TH075 PE packed second switch action0x4C has a complete
**74-instruction /14 actual typed PE/COFF field** native case in each
of the eleven large original fighting source functions. The crucial
native x86 branch at ordinal3 **skips to ordinal14** when short
`+0xF00/+0xEFC` is already nonzero; initialization of the flag and
actual `0040FBB0(0,95.0f,0)` is skipped, but real float angle
`+0x30 += global 00657878` executes every frame, NOT only on the
first frame. A natural C++ source scope fix restores the actual
74/74 native GPR/x87/CFG instruction grammar without altering byte
size. Original contact calls include `00453D60`, two CRT `__ftol2`,
`00453E20`, `0040FAC0`, `00453E60` and native `0040FC50`.
Native `00564BE0` has 25 real `EBP−0x88` receiver MOVs widened 3B
(360 native vs 285 generated source bytes), while `005AEEC0` uses
native counter `+0xEFC`. All previous 28 native case roles and afterRET
switch DATA are checked in **each fresh whole giant C++ compile**.
F613 adds **11 internal cases /814 native x86 roles/3,210 uncredited
original internal CODE bytes/154 actual physical typed COFF fields**.
F598–F613 cumulatively documents **319 native action interiors/
79,377 source-backed original internal CODE bytes**; all 11 whole
parents NONEXACT, no accepted whole-function authored CODE or full cold
replay. [F613 genuine source/PE proof](FIGHTER_TRAJECTORY_RECOVERY_F613.md),
selected `scripts/repo-python scripts/verify-fighter-trajectory-recovery-f613.py --boss 0x004F7130`.


## F614: original 10-projectile native action0x58 in eleven whole giant fighters

Original Japanese TH075 native packed second switch action0x58 is a
complete **135-x86** 469-byte internal case in eight regular giants,
a genuinely widened 580-byte/135-x86 case in native `00564BE0`
(37 real EBP−0x88 receiver MOVs), and **154-x86/539-byte** inner
case in special `0045DD70` and `0058AF60` (true native additional
stage-one `+0xF0C` guarded 0x3B7/0x3E7 sprite spawn).
All eleven source cases build from ordinary pinned VC7.1 C++, with
actual signed loop counter at EBP−4 for **10 x 0x3E4 sprite calls**,
plus conditional `+0xEFA >25` bonus `0x3E3` call, original float
velocity projections and two exact native float-equality `FUCOMPP`
status checks, real source `*(&POS)` lvalue and physical `0x58`/`0x59`
packed handler slots. Original **17 or 18 genuine PE-targeted COFF
fields per case** are individually checked, including both real typed
`FLD [0065782C]` refs before normalizing source unlinked immediates.
F614 adds **11 real inner source cases /1,523 original x86 roles /
5,410 uncredited original inner CODE bytes /189 true COFF fields**,
retaining all **29 earlier native game cases and afterRET DATA** in
freshly compiled whole-parent source objects. A preliminary probe
harness wrongly set the special-stage macro to zero because of a
Python single-line `if` suite; checking original source compiler
output revealed and fixed this before strict acceptance.
F598–F614 total: **330 real native case interiors /84,787 source-backed
original internal CODE bytes**, still NO whole-giant exact credit,
no all-unit cold replay/Oracle acceptance. [F614 source and real PE
case evidence](FIGHTER_TRAJECTORY_BURST_F614.md),
selected `scripts/repo-python scripts/verify-fighter-trajectory-burst-f614.py --boss 0x0045DD70`.


## F615: 30 complete native 2987-byte WinMain used-local object layout controls

Original Japanese TH075 native authored WinMain/GameApplication startup
`00602A60` is a WHOLE 2,987-byte/654-x86/123-call function with
15 original owned scene case afterRET 60-byte DATA and a real 0x278
stack frame. Tracked full ordinary VC7.1 C++ baseline
`probes/WinMainLocalLayoutF615.cpp` compiles to 2,981 bytes/654 x86
with all native ordered mnemonics but very wrong actual object EBP
locals. F615 independently cold-built **30 complete used-local C++
source alternatives**: genuine 260-byte path and scene-pointer
aggregates/field order, actual MSG/WNDCLASSEX declaration order,
original HWND/event handle and two used window metrics types.
All produce **654/654 original mnemonic order, 60 separate source
jump-table DATA bytes and 173 source physical COFF fields**; their
CODE lengths are **2,930–3,053 bytes, NONE the original 2,987**.
One truly used local combination makes module pathname correctly use
native EBP−0x180, but active scene remains wrongly EBP−0xC and
whole source is 2,930 bytes; another matches 627/654 native x86
instruction widths but source has 3,026 bytes. These prove why
matching isolated physical stack slots or mnemonic sequences is
insufficient. Zero accepted complete authored function CODE, no
invented source padding/all-unit cold replay. [F615 full source
experiment/provenance](WINMAIN_LOCAL_OBJECT_LAYOUT_F615.md),
selected `scripts/repo-python scripts/verify-winmain-local-layout-f615.py --case msg-before-app-plus-all-hwnd-event-int`.


## F616: genuine three complete 88-byte PE constructors, explicit vs implicit source ambiguity

Original Japanese TH075 native game constructors `004251C0`
(34 B/13 x86), `00458670` (23 B/10 x86) and `00458650`
(31 B/12 x86) are independently fully CODE-reproducible under pinned
VC7.1 `/Od /Ob0 /Gy /GR- /GX- /GS /Zi` from BOTH explicit empty
constructors and implicit compiler-generated default constructors
triggered via ordinary C++ placement-new. Their five real native
physical COFF fields resolve to original vtable `00657B88`, member
constructor `00417210`, base/derived virtual tables `0065904C` and
`00659038`, and native base constructor `00458670` respectively.
All **88/88 whole original linked CODE bytes** and **35/35 complete
native x86 instructions** are equal after typed original-target
resolution. An independent 4,351 native original function CALL scan
finds 15 authored scene caller functions, two authored derived
ctor callers, and two actual base ctor callers (one derived, one
authored). **This proves game use but not historical author-vs-
generated source origin**; all three remain 95-member original
`unknown` origin review, no 88-byte authored exact credit or whole
vtable ownership claim. [F616 complete original C++ alternatives
and typed PE/COFF evidence](NATIVE_GAME_CONSTRUCTORS_F616.md),
`probes/NativeGameConstructorsF616.cpp`,
`probes/NativeGameConstructorsImplicitF616.cpp`, targeted
`scripts/repo-python scripts/verify-native-game-constructors-f616.py`.
No all-unit cold replay, no new match ledger credit.


## F617: six strict real native 101-instruction action0x5E fighter interiors; 0x5D negative GPR cycle

Original Japanese TH075 physical packed second-switch actions0x5D/0x5E
are independently full 101-instruction native case subranges in seven
fighter parents. Reconstructing their original meaning under pinned
VC7.1 shows two **independent** horizontal-facing float comparisons,
with genuine lvalue `*(&F32(0x44))` restoring original x87/GPR and
conditional `JNE` to the second comparison. **Six complete action0x5E
inner cases** then match every native x86 GPR/x87/CFG role, width,
real indexed packed 0x5E/0x5F case boundary and 8 original PE-targeted
zero-addend COFF call/global fields each: **606 genuine x86 roles,
2,115 original internal CODE bytes/48 typed fields**, including the
430-native-byte `00564BE0` with 31 real EBP−0x88 receiver MOV widths.
**The original action0x5D remains at 61 GPR-role mismatches even in
those same six new objects** (101 x86 geometry/typed refs match but
not registers), and `00543210` action0x5E has 61 independent GPR-cycle
mismatches as an explicit negative compiler control. Four more fighters
have different original 64/94/96/106-instruction case families.
All 30 previously reconstructed original action cases and afterRET
packed DATA are rechecked in each affected whole-parent source TU.
Cumulative strict interior source study F598–F617: **336 cases /
86,902 native inner CODE bytes**, NOT independent whole exact CODE
and NOT credited authored source. [Actual original F617 source/negative
research](FIGHTER_AIR_TRANSITION_F617.md),
`scripts/repo-python scripts/verify-fighter-air-transition-f617.py --boss 0x0045DD70`,
`--negative-actor`. Official authored whole-exact 943/862,726 unchanged,
no full all-unit cold replay or external Oracle.


## F618: full original native 45-byte background polymorphic constructor, explicit/implicit unknown

Native Japanese TH075 `00449DE0` is a complete 45-byte/16-x86
game background owner default ctor, with physically owned original
vtable `DIR32` `+0xC` → `0065844C`, first member `REL32` `+0x17`
→ actual constructor `00412620` at `this+4`, and second member
`REL32` `+0x22` → actual constructor `0040AD80` at `this+0x18`.
Both an ordinary VC7.1 explicit empty constructor and an independent
**compiler implicit default special-member** C++ placement-new source
naturally generate the entire **45/45 identical original CODE bytes**
after genuine typed PE-target resolution (33/33 non-COFF bytes,
3 real physical zero-addend fields). Fresh independent decode of
4,351 original native whole function extents found **36 direct CALLs
from 36 distinct authored BackgroundStage loading functions**.
This proves game use but not explicitly written-vs-generated source
provenance or whole native vtable DATA contents: the original
`00449DE0` remains `unknown`/`review` and receives no new authored
exact credit. Along with F616, four 133-byte total whole original
constructors are source-backed but uncredited pending provenance.
[F618 actual original background ctor evidence](BACKGROUND_OWNER_CONSTRUCTOR_F618.md),
reproducible `scripts/repo-python scripts/verify-background-owner-constructor-f618.py`.
No full 943-unit cold replay and official 943/862,726 authored exact
unchanged.


## F619/F620: native giant 0x5AEEC0 64/64/44 x86 and genuine original source register-cycle dependency

Original Japanese TH075 PE physical native packed slots 19/20/21/22
bound case0x5D (210 B/64 x86/3 real typed calls), case0x5E
(210 B/64 x86/3 real typed calls), and next case0x5F
(144 B/44 x86/3 true typed PE calls), each inside the SAME still-
nonexact `005AEEC0` fighter giant. Natural C++ for action0x5F,
`probes/FighterFacing5FF620.inc`, is **44/44 actual native x86
GPR/x87/CFG role/size identical**, with all original 3 true
zero-addend PE-targeted call refs to `0040FA30/0040FAC0/0040FAC0`,
when the 5D/E predecessors remain diagnostic placeholders in the
newly built whole-parent source; all 30 prior original native case
roles and afterRET switch DATA remain verified on that same object.
However, replacing those placeholders with real C++ original-
shaped `probes/FighterSimpleAirTransitionF619.inc` generates the
correct 64/64 original x86/210/210 byte geometry and 3 COFF fields
per action BUT remains **42/42 actual native GPR/CFG roles
nonexact**; moreover the 0x5F native roles then shift to 26
mismatches without changing that case source. F620 therefore adds
only **one STRICT source-backed 144-byte original inner game case**
and explicitly preserves the negative multi-case compiler context;
none of the enclosing 005AEEC0 giant is fully native exact.
F598–F620 now 337 strict internal case subranges/87,046 original
inner CODE bytes, NOT whole-function acceptance. [F620 original
native positive+negative source proof](FIGHTER_SIMPLE_AIR_CONTEXT_F620.md),
targeted `scripts/repo-python scripts/verify-fighter-facing5f-f620.py
--negative-context`. Official 943/862,726 authored complete exact
ledger unchanged; no all-unit cold replay/Oracle claim.


## F622: genuine native fighter action0x62 unsigned four-way OR and correction of old switch JA heuristic

Original pinned Japanese TH075 PE independently proves that native
0x62 collision control uses signed direction byte +0x66 × signed
int +0x4DC, and on either sign tests FOUR unsigned 32-bit fields
`+0x4E8/+0x4EC/+0x4F0/+0x4F4` using **logical OR of >0**.
Native early `JA` edges enter the short counter store; the fourth
`JBE` skips it. Initial C++ with three `==0 &&` predicates matched
65-x86/249-byte geometry but got the actual PE branch targets wrong.
Correct native four-way `||` C++ produces strict 65/65 original
GPR/x87/CFG operand roles, 4 real physically typed PE/COFF call
refs each in two newly compiled giant sources: native `00564BE0`
(312 original inner CODE bytes, 21 widened saved-this EBP−0x88
MOVs, short counter +0xF00) and `005AEEC0` (249 bytes, original
counter **+0xEFC**). F622 adds **2 strict original inner cases /
130 x86 roles/561 original internal CODE bytes/8 true call fields**.
Original `0045DD70` still has 40 role mismatches and short
`004AC040` native case 25-x86/87-byte still has 10 role differences.
Old `verify-fighter-actionzero-natural-source.py` had incorrectly
identified every game-action `JA` as the switch-bound dispatch guard;
now only dispatch-region guards BEFORE the last indexed JMP are
identified, with original count, default, afterRET dense/sparse
DATA and case0/F614 selected regressions preserved. F598–F622
strict source-backed interior 339 cases/87,607 original native
CODE bytes; enclosing entire giants NONEXACT, no whole-function
credit, original 943/862,726 exact authored coverage unchanged.
[F622 actual PE semantic and compiler proof](FIGHTER_COUNTER_DISPATCH_F622.md),
selected `scripts/repo-python scripts/verify-fighter-counter-dispatch-f622.py --boss 0x005AEEC0`.


## F624: strict complete original 118-x86 mode/event case0x63 inside two giant fighters

Pinned original Japanese TH075 PE physical second switch action0x63
is real packed dense slot25, while slot26 is common default—not
actual game CODE case end. Real next registered native handler is
0x8C; a distinct source case0x8C COFF-backed marker establishes the
full emitted 0x63 source boundary. Original x86 `MOVSX` at ordinal0
reads genuine signed byte global `006714B4`; ordinal2 JNE targets
ordinal7, ordinal6 JNE targets ordinal27. Correct C++ is
`mode!=3 || member+0x2CD==0`, not the initial semantically wrong
`if(mode==3)`. At ordinal54 genuine native JNE targets exit
ordinal58 even if an additional action bonus is not triggered:
`+0x370` bonus byte flag4/action0x302 on original `00564BE0`,
flag5/action0x31D on `005AEEC0`. Natural source precisely restores
both real CFG semantics and all **118 native GPR/x87/CFG roles,
8 physical typed zero-addend original PE/COFF fields** in each
freshly compiled whole giant. Native CODE extents **552 B** for
`00564BE0` (31 genuinely widened EBP−0x88 MOV receivers and one
JLE near +4 bytes) and **455 B** for `005AEEC0`: two original
strict case interiors /236 x86 roles /1,007 native CODE bytes /
16 actual field targets, all uncredited as whole functions.
All **31** earlier source-backed case bodies and full separately owned
afterRET packed switch DATA are rechecked on each new selected giant
OBJ via strict F622/F614 original PE verifiers. Overall F598–F624
has **341 strictly source-backed original internal action subranges /
88,614 original native inner CODE bytes**, not simultaneously
complete entire giants, no accepted additional whole authored CODE.
[F624 actual original 0x63 source/boundary/typed field proof](FIGHTER_MODE_EVENT_ACTION63_F624.md),
selected `scripts/repo-python scripts/verify-fighter-mode63-f624.py --boss 0x00564BE0`.
Official 943/862,726 authored exact unchanged; no 943-unit cold replay.


## F625: genuine original small authored destructor allocation mechanism, NOT yet whole native exact

Pinned Japanese TH075 real authored whole archive nonvirtual destructor
`0041CE50` 171B/51 native x86/14 physical COFF fields, and battle
SceneObject EH virtual destructor `0043B0B0` 248B/75 native x86/
12 real typed fields, remain NONEXACT. Natural borrowed pointer
**direct free** source forms `probes/ArchiveCatalogDirectFreeF625.cpp`
(165B/49 x86) and `probes/BattleSceneDirectFreeF625.cpp`
(230B/69 x86) cold-compile under actual VC7.1 `/GX-` vs `/GX`
profiles and genuinely recover BOTH original PE deletion EBP
stack slots: archive x86 ordinals22/24 = −0xC/−0x8; scene
ordinals26/28 = −0x14/−0x10. The source however drops actual
original filename free store/reload (2 x86/6 B) or three scene
resource pointer save/reloads (6 x86/18 B). Native original
whole-function compare therefore requires **size-mismatch**,
not partial acceptance. 20 additional real archive materialized
prvalue/reference controls (171/51 with 108/115 or 102/115
nonfield equality, 179/54 size-change), and 19 fresh scene
source lifetime/aggregate controls (248/75 189/200 or 191/200;
254/78,272/84,236/71,230/69 native-size mismatches) do not
recover the actual original simultaneous saved/local allocation.
Original source lifetime/ordering context must be recovered without
fake temps or byte grafts. Reproduce two bounded original source
negative proofs with `scripts/repo-python scripts/verify-destructor-direct-free-f625.py
--which archive` and `--which scene`.
[Full original PE/COFF investigation](DESTRUCTOR_DIRECT_FREE_LIFETIMES_F625.md).
Official authored exact whole CODE 943/862,726 remains unchanged;
no all-unit cold replay or external Oracle acceptance.


## F626: original 109-instruction mode0x63 in five giant fighters, genuine absent bonus branch

Native Japanese TH075 physical real 0x63 is a 109-instruction
regular mode-event action in seven original fighters, unlike F624's
118-instruction versions. Original real native 0x31C transition
**does NOT** execute any extra `+0x370` bonus flag action: it jumps
directly to the common case exit. Natural C++
`probes/FighterMode63BasicF626.inc` source reproduces the complete
native **109/109 GPR/x87/CFG roles, 417/417 original inner CODE
bytes and 7 actual typed zero-addend PE-targeted COFF fields** each
in `004AC040`, `00486550`, `00543210`, `004D7E70`, `005214B0`.
Original mode signed-byte `DIR32` `006714B4` ordinal0 and six
actual game calls (four action setters `0040FAC0`, `0040FA30`
getter and `0040FB40` aux) are independently physically checked.
The full original afterRET compressed second table maps 0x63 to
LAST actual dense slot25, with slot26 COMMON DEFAULT; the real
next native handler is `0x8C`, which bounds original case0x63,
not the default slot. Each of five newly compiled whole-parent
C++ objects preserves the prior **30** source-backed native actions
through F614 and actual dense/sparse original afterRET DATA.
Two original actor owners **fail** strict registers under same
source: `004F7130` original109/416 versus source109/417 has
**67 native GPR/CFG errors** after genuine mode field masking;
`0058AF60` original109/417 also **67 native GPR errors**, and has
26 total second-table native entries (0x63 slot24, real next
code handler `0x89`), not the generic 27-entry/0x8C map.
F626 contributes **5 STRICT original game inner cases /545 true
x86 roles/2,085 original internal native CODE bytes/35 physical
COFF fields**, cum F598–F626 **346 original inner case bodies /
90,699 original native inner CODE bytes**. All containing fighters
and separate authored complete destructors remain NONEXACT.
[F626 actual original PE/multi-case context evidence](FIGHTER_MODE_EVENT_BASIC_F626.md),
targeted `scripts/repo-python scripts/verify-fighter-mode63-basic-f626.py --boss 0x004AC040`,
`--negative-actor 0x0058AF60`. Official authored whole exact
943/862,726 unchanged, no full 943-unit cold replay.


## F627: authentic 138-x86 priority mode0x63 case on fighter 005D73C0

Native Japanese TH075 original `005D73C0` and `0045DD70` expose
a separate real **138-instruction native** second packed-switch
case0x63 grammar: independent early priority path checks indexed
signed byte `+0x370[index] == 5` BEFORE checking `+0x32A[index] ==2`
and transitions to actual game action `0x303`, then exits; a
second independently gated branch still checks indexed `+0x32A ==2`
to transition to normal `0x31C`. This differs both from F624 118-x86
optional bonus **after** action31C and F626 109-x86 no-bonus owners.
Actual native compressed second switch has **26 physical dense
slots, 0x63 at slot24**, common default25, and actual next game CODE
handler `0x8C`. Ordinary fresh pinned VC7.1 C++ source
`probes/FighterMode63PriorityF627.inc` reconstructs all original
**138/138 x86 GPR/x87/CFG roles, 534 original native CODE bytes
and 8 physically verified zero-addend PE/COFF targets** inside
`005D73C0`, retaining the earlier 30 case roles and afterRET jump
DATA. `0045DD70` original source has **533 B/138 x86** and 87
nonmatching native register roles after normalizing the verified
mode global, so is NOT counted. F627 adds **1 true strict native
interior case /138 x86 roles/534 original inner CODE bytes/8 fields**,
cumulative F598–F627 **347 original native case bodies/91,233
internal CODE bytes**, all nested in nonexact giant function sources;
official 943/862,726 whole authored exact unchanged.
[Original F627 source/PE and negative owner evidence](FIGHTER_MODE_PRIORITY_F627.md),
`scripts/repo-python scripts/verify-fighter-mode63-priority-f627.py
--negative-actor`. No all-unit cold replay.


## F628: 24 strictly native 80-x86 fighter jump-landing cases, real qword FMUL and eight simultaneous predecessor 0x63 source matches

Original pinned TH075 PE action0x8C/8F/90 are each true 80 native x86
with eight individually typed PE/COFF game/global target fields:
2 original `FCOMP [0065782C]`, `FADD [00658058]`, real
`ContactAt454EE0` call, **double-precision `FMUL qword [006583E8]`**
followed by FSTP to member+0x490, and true `0040FA30/0040FAC0/
0040FB40` calls. Natural VC7.1 C++ source `probes/FighterJumpLandingF628.inc`
recovers all original GPR/x87/CFG role/physical widths for **three
complete original cases inside each of eight giant fighter C++
parents**, totaling **24 native internal case bodies/1,920 native
x86 roles /7,152 original uncredited internal CODE bytes/192 genuine
zero-addend COFF refs**. Normal original case 289 B, real wide saved
EBP−0x88 actor `00564BE0` original 361 B (24 original receiver MOV
widenings×3 B). Original `005AEEC0` retains counter+0xEFC; stage3
counter limits native 5/7 and initial −11f/−12f are per-case PE-read.
**Each new whole-parent source also reproduces the preceding actual
original `0x63` GPR/typed fields**, including F627 138-x86 priority
`005D73C0`, F624 118-x86 special actors, and F626 109-x86 five
regular actors; prior 30 native case proofs and full packed afterRET
DATA are rechecked in each fresh C++ object. Actual original
`0045DD70`,`0058AF60`,`004F7130` remain **51 GPR/CFG source-role
mismatches per 8C/8F/90** even though size/count/typed COFF agree;
these real negative case contexts are NOT called strict. F598–F628
studied **371 original strict game-case interiors/98,385 original
internal CODE bytes**, still zero accepted new whole-game authored
functions or original executable edits; official exact 943/862,726
unchanged, no full all-unit cold replay or Oracle receipt.
[F628 original native source/x87/negative evidence](FIGHTER_JUMP_LANDINGS_F628.md),
targeted `scripts/repo-python scripts/verify-fighter-jump-landings-f628.py --boss 0x00564BE0`.


## F629: 78-native-x86 arc/trajectory action0x91 in eight huge fighters

Pinned Japanese original action0x91 next physically bounded by case0x96
has **78 x86 /288 native bytes** across seven compact fighter giants
and **363 bytes** in true wide `00564BE0` (25 original `EBP−0x88`
receiver MOVs widen +3 each). Natural normal VC7.1 C++ source
`probes/FighterArcTrajectory91F629.inc` preserves actual stage1/2/3
threshold float `00657480`/x87 JP, signed drag and ground float
comparison `0065782C`, **two genuine CRT `__ftol2 006406AC`
conversions**, original signed-short native trajectory `+0xF00`
or real `005AEEC0 +0xEFC`, and actual `00453E20/0040FAC0/
00453E60/0040FA30/0040FB40` game calls. Eight new whole giant
C++ source builds each match **78/78 original GPR/x87/CFG roles
and 12 true typed zero-addend PE/COFF targets**, and revalidate
all three F628 complete cases, prior 0x63 including 138-x86 priority
source, F614 30 earlier cases and complete afterRET DATA. **8 new
original interior cases /624 native x86 roles /2,379 original inner
CODE bytes/96 typed targets**, no whole-function acceptance.
`004F7130` source has 35 genuine native GPR-role mismatches despite
identical 78-x86 extent and real COFF; two remaining fighter originals
have separately different 105-x86 projectile version. F598–F629
strict research now 379 case interiors/100,764 native original
inner CODE bytes, no newly accepted authored exact units, official
943/862,726 unchanged and no full all-unit cold replay.
[F629 original native case proof](FIGHTER_ARC_ACTION91_F629.md),
`scripts/repo-python scripts/verify-fighter-arc91-f629.py --boss 0x005AEEC0`.


## F630/F631: all eleven original timer action0x96 case interiors fully native GPR/x87/CFG role matched

Pinned Japanese TH075 native case0x96 is **73-x86** in nine fighter
controllers and **75-x86** in native `00543210`/`0058AF60` due to
an authentic extra signed-short `this+0xF0A` reset. Crucial original
PE difference: native `0058AF60` resets it BEFORE native trajectory
counter `+0xF00`, position −9.0f and velocity reset, while original
`00543210` resets it AFTER. Ordinary C++
`probes/FighterLandingTimer96F631.inc` preserves this native ownership
and source order, real float+0x368 accumulation `FADD [0065747C]`,
max `FCOMP [006583B4]` clamp to 1000f, actual ground x87 strict
comparisons, native contact `00454EE0`, double-precision
`FMUL qword [006583E8]` storing member+0x490 and native action
`0040FA30/0040FAC0` calls. All **eleven fresh whole giant C++
source TUs** produce strict original native full 0x96 cases,
**807 genuine GPR/x87/CFG roles /3,126 uncredited original inner
CODE bytes /99 physical typed zero-addend PE/COFF targets**.
Real native wide `00564BE0` has 22 receiver MOVs widened +3B
(342 native bytes instead of 276 compact); `005AEEC0` has short
counter +0xEFC. Same new objects reverify previous F628 three
landing cases, native 0x63 when strict, previous F614 30 native
case grammars and full separately-owned afterRET DATA, plus F629
0x91 78-x86 source in eight original actors. Native `004F7130`
0x91 remains 35 GPR differences. Special previous 105-x86 `0x91`
actors `0045DD70`,`0058AF60` compile natural
`probes/FighterArcSpawn91F630.inc` with correct 373 bytes/13 typed
fields but still **55 real GPR/CFG mismatches per actor**: do not
credit F630. The original 0x91 spawn side is **1 on both actors**;
not the different earlier 0x46 side for `0058AF60`. F598–F631
strict interior source study **390 real action cases /103,890
original native inner CODE bytes**, not independently callable
complete exact function credits. Official 943/862,726 whole-authored
match ledger unchanged; no 943-unit all-unit cold replay.
[F631 actual PE/native timer and predecessor negative case proof](FIGHTER_LANDING_TIMER_F631.md),
targeted `scripts/repo-python scripts/verify-fighter-landing-timer96-f631.py --boss 0x0058AF60`.


## F632: fifteen full original 171/248-byte authored destructor free-argument lifetime controls

Independent pinned Japanese original PE/VC7.1 experiment tests **8
natural ArchiveCatalog source variants** with actual filename pointer
assignment inside the `free` argument, comma sequencing, casts and
real const/void pointer declarations. All are **171B/51 x86/14 true
COFF fields** but **108/115** original nonrelocation byte identity;
original resource/delete/name EBP order `−0xC/−0x8/−0x10` still
not reproduced. **7 complete real SceneObject resource-free source
variants** (four genuine aggregate assignment in arguments and three
individual named-pointer assignment forms) all preserve the real
**248B/75 x86/12 COFF fields** but remain **191/200** or **189/200**
original nonfield bytes; texture/delete EBP locals still wrongly
`−0x20/−0x1C` rather than native `−0x14/−0x10`.
Original whole functions still NONEXACT; this is a negative VC7.1
expression/lifetime constraint, not a new authored match or fake
compiler-stack layout trick. [F632 original full source/PE experiment](DESTRUCTOR_FREE_ASSIGNMENT_F632.md),
selected `scripts/repo-python scripts/verify-destructor-free-assignment-f632.py --case scene-three-assignment-args`.
Official 943/862,726 complete authored exact unchanged; no all-unit
cold replay.


## F633: native complete fighter landing timer siblings 0x97/0x98/0x9A across 11 giants

Original pinned Japanese TH075 PE shows three distinct complete
native sibling case0x97→0x98, case0x98→0x9A, case0x9A→0x9B bodies
per fighter giant, each natural VC7.1 source-backed under F633:
**33 original complete interior cases /2,421 native GPR/x87/CFG
roles /9,378 original uncredited native inner CODE bytes/297 actual
physically typed PE/COFF global/call fields**. Original source
height constants are −10f/−13f/−9f, and original **next action
0/0/2** matters: first naive copy of earlier timer `0x96` wrongly
emitted action0 for 0x9A even though all x86 geometry/refs matched.
The corrected natural C++ reproduces true `0x9A` PUSH 2, native
x87 timer and ground clipping/real game contact, full `FMUL qword
[006583E8]` reflection, signed short `+0xF00` or `005AEEC0
+0xEFC`, and two opposite real native `+0xF0A` reset orders.
`00564BE0` has 22 real widened saved `this` EBP−0x88 MOVs per
342-byte native case; normal compact 276/73 x86 or 288/75 x86.
All **11 newly compiled whole giant C++ source objects** still pass
F631 previous 0x96, F629 0x91 when strict, F628 three landing
cases, native mode63 when strict, F614 thirty earlier cases and
full separately owned afterRET jump DATA. Original preceding 0x91
on `004F7130` still 35 native register-role differences, and two
special 105-x86 sprite 0x91 predecessors still 55 each; none is
silently accepted. F598–F633 total **423 strict source-backed real
original game case interiors/113,268 original inner CODE bytes**,
NOT new fully exact authored whole functions. Official
943/862,726 exact unchanged; no all-unit cold replay/Oracle.
[F633 actual PE, typed COFF and C++ case proof](FIGHTER_LANDING_SIBLINGS_F633.md),
selected `scripts/repo-python scripts/verify-fighter-landing-siblings-f633.py --boss 0x00564BE0`.


## F634: exact full 14/14/13-byte game object this-accessors and no-op leaf, origin UNKNOWN

Real Japanese native TH075 PE `0040D980` and `0040D9F0` each
have an entire **14-byte/8-x86** `return this` leaf, and
`0045B850` is a **13-byte/7-x86** empty receiver method returning
with true native `RET 4`. All three have **zero actual native PE/COFF
fields**, and normal VC7.1 C++ `probes/GameObjectThisAndNoopLeavesF634.cpp`
reproduces **41/41 complete original native machine CODE bytes /
23/23 x86 roles** after one cold compile, no special `DIFFBUILD`,
asm or byte hacks. Independently decoding all 4,351 registered native
PE CODE extents proves 16, 3 and 14 genuine direct CALL sites;
14, 3 and 14 come from currently authored game functions, including
four huge CharacterObject::Advance-like sources for `0045B850`.
Nevertheless, code-generation identity and actual game callers
cannot determine historical explicit-vs-generated class method
origin: all three original `function-origins.csv` rows remain
**unknown/review**, no 41-byte authored exact acceptance or class
layout conjecture. [F634 real whole-function/PE-call proof](GAME_OBJECT_ACCESSOR_LEAVES_F634.md),
targeted `scripts/repo-python scripts/verify-game-object-leaves-f634.py`.
Official 943/862,726 accepted authored whole CODE unchanged,
no all-unit cold replay.


## F635: 25 full original 33,293-byte authored giant typed-member compiler negatives

`004EBDA0` original Japanese TH075 whole original has **33,293
CODE bytes/8,789 native x86 +438 separately owned afterRET jump
DATA bytes**, 682 normal VC7.1 physical source COFF refs (622 CODE
+60 DATA). F635 freshly cold-compiled **25 genuine whole original
C++ source hypotheses** from `probes/CharacterObjectActionsF572.cpp`,
limited to `0x38D/0x38E/0x3E3` real float-member zero/quarter/one
IEEE-754 bit stores, C++ leftvalue/ref/multiply, signed/unsigned
byte writes and stage4 threshold expression alternatives.
23 candidate TUs preserve full original **8,789 x86 start, width,
mnemonic order and same original 137/31,003 nonrelocation byte
mismatches**. Two genuine `*=`/ref-expression source alternatives
also preserve whole bytes and x86 instruction count but change
actual original instruction **start/width** at whole x86 ordinals
8081/8082 and worsen to **140 wrong original nonfield bytes**.
First remaining native mismatch still whole x86 ordinal8076 at
original `0x38D` stage4; the cycle continues into `0x38E` and
first 31 roles of `0x3E3`. Changing float constant writes to an
identical raw integer bit representation did **not** alter native
GPR lifetime allocation under the pinned VC7.1 profile. All 25
are genuinely NONEXACT; tracked F596 best source unchanged.
[F635 entire original PE/COFF compiler study](CHARACTEROBJECT_TYPED_MEMBER_CONTROLS_F635.md),
selected `scripts/repo-python scripts/verify-characterobject-typed-member-f635.py --case 38d-zero-velocity-as-bits`.
No accepted whole/split CODE credit; official 943/862,726 whole
exact unchanged and no all-unit cold replay.


## F636: original native complete two-case landing 0x9B/0x9C source in eleven giants

Original TH075 PE physically bounds native action0x9B→0x9C→0x9E;
no separate action0x9D handler. Authentic original height constants
−10f/−13f and next move **action 2** in both cases differ from
F633 0x97/0x98 action0. Normal VC7.1 C++ reuses the *same real*
`probes/FighterLandingTimerSiblingsF633.inc` actor-specific source
body, and **eleven fresh whole giant source TUs strictly reproduce
22 native complete 0x9B/0x9C case interiors /1,614 GPR/x87/CFG
roles /6,252 original uncredited native inner CODE bytes/198 actual
zero-addend typed PE/COFF calls and globals**. Native `00564BE0`
original saved-this `EBP−0x88` widens exactly 22 receiver MOVs per
342-byte case; native `005AEEC0` uses `+0xEFC` trajectory, and
native `0058AF60` and `00543210` have extra `+0xF0A` reset
BEFORE/AFTER their main stage0 init in genuinely different original
75-x86/288-byte cases. Each new OBJ independently revalidates
F633 three previous native 0x97/0x98/0x9A cases, F631 0x96,
real 0x91 (including unresolved 35/55 GPR-role predecessors),
F628 three landing cases, native mode0x63 if strict, F614 thirty
old source cases and all original afterRET packed switch DATA.
F598–F636 now **445 strictly source-backed original game-case
interiors/119,520 original native inner CODE bytes**, no new whole
fighter exact/accepted authored CODE. [F636 full original PE/native
source study](FIGHTER_LANDING_PAIR_F636.md), targeted
`scripts/repo-python scripts/verify-fighter-landing-pair-f636.py --boss 0x0058AF60`.
Official 943/862,726 exact authored unchanged; no all-unit cold
replay or external Oracle acceptance.


## F637: complete 0x9E native ground boost in eleven giant fighters, strict-vs-nonstrict PE x87 semantics

Pinned original Japanese TH075 native case0x9E→0x9F is complete
66 x86/243 CODE bytes in most fighters, **68/255** in native
`00543210` and `0058AF60` from real additional short `+0xF0A`
AFTER/BEFORE motion initialization, and **66/306 native bytes**
in real wide saved-EBP−0x88 `00564BE0` (21 original receiver MOVs
+3 bytes each). Original stage-zero source initializes position
−6f, velocity 8f, drag .75f; real original x87 ground check
`POS48 >= original float 0065782C` uses `TEST AH,1` in TEN
actors, while native **`005D73C0` uses strict `POS48 > ground`**
with original `TEST AH,0x41` instead. The first source matched
66-x86 count/8 COFFs but was wrong on native ordinal31 for this
actor until the **actual inequality semantics** were corrected.
The native landing path calls true `0040FAC0(0xA)` then clears
vertical displacement and `00453E20` reset; frame-complete path
uses `0040FA30`/`0040FAC0(9)`. Fresh ordinary VC7.1 C++
`probes/FighterGroundBoost9EF637.inc` inside **all eleven whole
giant source objects** strictly reproduces **730 true original
GPR/x87/CFG x86 roles/2,760 original uncredited native inner
CODE bytes/88 physical PE-targeted zero-addend COFF references**.
Each new whole source compilation rechecks strict previous F636
9B/9C, F633 97/98/9A, F631 0x96, real mode0x63 when strict,
F614 thirty earlier native game-case grammars, and complete afterRET
packed switch DATA. Previous original `0x91` GPR-negative source
contexts remain honestly nonexact. F598–F637 bounded study now
**456 strict original internal action case bodies/122,280 original
inner CODE bytes**, NOT accepted complete game functions; official
943/862,726 whole-authored exact unchanged, no full cold replay.
[F637 original PE/x87/COFF source proof](FIGHTER_GROUND_BOOST_F637.md),
selected `scripts/repo-python scripts/verify-fighter-ground-boost-f637.py --boss 0x005D73C0`.


## F638: four full native game constructor bodies exact from explicit and compiler implicit C++ source, origins pending

Actual pinned original Japanese game constructors `00458670`
(23-byte polymorphic base vtable `0065904C`), `00458650`
(31-byte derived constructor calling actual `00458670` and setting
vtable `00659038`), `004251C0` (34-byte virtual owner vtable
`00657B88` and real `this+4` member ctor `00417210`), and
`00411C10` (25-byte nonvirtual owner member `this+4` ctor
`0040D990`) are **FOUR independent complete original registered
whole CODE functions**. Natural pinned VC7.1 C++ compiles BOTH
explicit-empty and separately **compiler implicit/placement-new**
default constructors with identical actual original entire native
**113/113 original machine CODE bytes/46 x86/6 physically typed
zero-addend original PE-targeted COFF references** after resolving
real PE pointer/REL32 bytes. No machine byte graft or ASM.
Independent direct original native CALL decoding across all 4,351
registered function extents proves native 2/2/15/1 true uses,
including 1/2/15/1 CALLs from currently authored game sources.
Game use and whole-byte compiler identity do **not** establish
historical explicitly written-vs-generated source origin: all four
remain `unknown`/`review`, no accepted authored exact CODE credit.
Combined separate F616/F618/F634/F638 fully source-backed
origin-unknown whole originals: **11 distinct functions /287 native
CODE bytes**, all uncredited. [F638 original PE/vtable/constructor
physical target and caller proofs](GAME_INHERITANCE_CONSTRUCTORS_F638.md),
rebuild `scripts/repo-python scripts/verify-game-inheritance-constructors-f638.py`.
Official 943/862,726 whole-authored exact unchanged; no full
all-unit cold replay or external Oracle receipt.


## F639: 33 strict complete 0x9F/A0/A1 original giant fighter landing cases, no false extra F0A stores

Pinned Japanese TH075 PE shows physical original 0x9F→0xA0,
0xA0→0xA1, 0xA1→0xA3 complete landing cases, each **73 original
native x86** across ALL 11 fighter parent giants. Original initial
positions −9f/−10f/−13f and next action **0/0/0**. Each has nine
true typed PE-targeted COFF float/game call refs: original
`0065747C`, `006583B4`, `0065782C` twice, `00658058`,
real `00454EE0`, double `FMUL qword [006583E8]`, true game
`0040FA30` and `0040FAC0`. Natural C++
`probes/FighterLandingTimerSiblingsF633.inc` in eleven NEW whole
VC7.1 giant TU compilations strictly reproduces **33 authentic
complete native inner case bodies, 2,409 GPR/x87/CFG roles,
9,306 original uncredited inner CODE bytes, 297 actual typed
zero-addend PE/COFF fields**. Real wide `00564BE0` has 22
saved EBP−0x88 MOV receiver widenings per 342-byte native case.
`00543210/0058AF60` original native 9F/A0/A1 are genuine 73-x86
**without extra `+0xF0A` reset** despite earlier 75-x86 timer
cases with this extra store: real source stage, not actor universal.
Each new OBJ rechecks F637 native 0x9E (including strict above
on `005D73C0`), F636 pair, F633 trio, F631 action0x96,
F628 three landings, original mode63 when strict, previous F614
30 native game cases and entire separately owned afterRET packed
jump DATA; F629/F630 original register cycles still marked negative.
F598–F639 total **489 strictly source-backed original internal
case bodies/131,586 original native CODE bytes**, no newly accepted
whole giant/whole authored exact code. [F639 actual native PE/whole
source proofs](FIGHTER_LAST_LANDINGS_F639.md), targeted
`scripts/repo-python scripts/verify-fighter-last-landings-f639.py --boss 0x0058AF60`.
Formal whole exact ledger 943/862,726 unchanged, no all-unit cold replay.


## F640: twelve full native C++ thin-call and thiscall game leaves, 203 exact CODE bytes but original source ownership unknown

Normal original Japanese pinned VC7.1 C++ source
`probes/GameCallForwardersF640.cpp` reproduces **12 independently
registered complete original tiny native functions, 203/203 whole
CODE bytes/99/99 x86 and 10 actual zero-addend physically typed
original PE/COFF REL32 fields**. Six source grammar 17-byte
`__cdecl` single-argument float-provisional forwarders map to
`0040D900`,`0040D940`,`00412D90`,`00428D20`,`00449A60`,
`00438A60` and actual PE callees `0040D920`,`0040D960`,`00412DB0`,
`00428D40`,`00449A80`,`00641FB8`. Two 11-byte original thiscall
no-op receivers are `004073A0`,`00438CF0`; three 19-byte source
member call forwards are `0040DE30`,`0040DF40`,`0040D8E0`,
and 22-byte member-ctor receiver source `0040D8C0`. All true native
call operands are independently read and linked into temporary
comparator bytes, not grafted into source or changed original EXE;
full CODE then equals 203/203 original native bytes. Original PE
CALL graph scans all 4,351 registered function extents, with real
game-authored usage in drawing, camera, fighter and texture manager.
Neither actual game calls nor identical wrapper machine-code prove
historical C++ original signature (float vs int) or explicit author
vs generated/library source: **all 12 stay `unknown`/`review`, no
accepted authored exact credit**. Combined F616/F618/F634/F638/F640
origin-unknown full source study **23 native whole functions/
490 original native CODE bytes**, all uncredited. [F640 original
whole PE/C++/call provenance](GAME_CALL_FORWARDERS_F640.md),
selected `scripts/repo-python scripts/verify-game-call-forwarders-f640.py`.
Official authored 943/862,726 whole exact unchanged, no all-unit
cold replay/Oracle.


## F641: three complete counter-free A3/A4/A5 original native landing actions inside each of eleven giants

Real Japanese TH075 original giant fighter action0xA3→0xA4,
0xA4→0xA5, 0xA5→0xA7 physically own **71 x86 each**, original
heights −9f/−10f/−13f and real frame completion native action2.
Unlike earlier F633/F639 source landings, the actual A3/A4/A5
source **omits the native trajectory short zero store** at
`+0xF00/+0xEFC` and even `00543210/0058AF60` have NO extra
`+0xF0A` zero store in these later original cases. Natural C++
`probes/FighterLandingNoCounterF641.inc` restores actual original
71-instruction codegen and all nine typed zero-addend PE/COFF
float/game refs per case. **All 11 freshly compiled whole giant
source TUs** strictly match **33 real original internal case
bodies /2,343 GPR/x87/CFG roles /8,901 original native internal
CODE bytes/297 true typed refs**. Real saved EBP−0x88 wide actor
`00564BE0` has exactly 21 native MOV receiver widenings per
327-byte original case; normal others 264 native bytes each.
Same new objects recheck F639 9F/A0/A1, F637 strict-vs-inclusive
9E, F636 pair, F633 trio, F631 96, earlier mode63 when strict,
F614 thirty previous cases and entire afterRET packed switch DATA,
while previously unmatched original 0x91 register cycles remain
nonexact. F598–F641 strict interior research totals **522 real
original case bodies/140,487 original inner CODE bytes**, not
accepted whole authored exact functions. [F641 native case proof](FIGHTER_NO_COUNTER_LANDINGS_F641.md),
reproducible `scripts/repo-python scripts/verify-fighter-no-counter-landings-f641.py --boss 0x0058AF60`.
Official 943/862,726 whole authored exact unchanged; no full cold replay.


## F642: native complete A7/A8 97-x86 fighter sprite launch cases, x87 operand order and two true stack width families

Original Japanese TH075 giant fighter action0xA7→0xA8→0xB4
owns **97 real x86 per complete physical case**, with 12 genuine
typed zero-addend PE/COFF global/game method fields, spawning real
sprite kind `0x38` side1 after native `0046D000(0xFA)` animation
and `00453D60(0x2C)` preparation, signed direction×30 horizontal
`IMUL/FILD`, true float y `this+0x48 + [00657888]`, ground
correction and signed-short cooldown `0xB4`/decrement10/
`FILD` bounce scaling `[006590B4]`; original 005AEEC0 uses
cooldown member+0xEFC vs others+0xF00. Original next action is
0 for A7 and 2 for A8. First natural C++ `POS48+global` yielded
wrong `FLD global; FADD member` source x87 order at x86 ordinal34/35,
although 97-x86/full-byte length/12 PE-targeted COFF fields
matched. **19 actual whole-parent compiler expression variants**
independently prove genuine C++ `F32(0x48)+global` recovers
native `FLD member; FADD global` roles and widths with no ASM.
Original `004AC040` 362-byte cases have exactly FOUR true wide
signed-int MOV/FILD scratch operands +3B (not receiver frame),
while real `00564BE0` 447-byte cases differ from ordinary 350B
through 27 saved-this EBP−0x88 MOV widenings×3, FOUR signed-int
scratch MOV/FILD widenings×3, and one near JNE +4B.
**Eleven fresh whole VC7.1 giant C++ objects** now strictly
match **22 original complete case interiors/2,134 original native
GPR/x87/CFG roles/7,918 native original inner CODE bytes/264 typed
PE-target COFF fields**, and reverify F641/F639/F637/F636/F633,
original mode63 when strict, thirty preceding real game cases and
complete separately owned afterRET packed jump DATA.
F598–F642 strictly source-backed original game-case interiors
**544/148,405 native original inner CODE bytes**, *not* accepted
whole functions; 943/862,726 whole authored exact remains unchanged,
no 943-unit cold replay. [F642 original PE/natural C++ and real
scratch width evidence](FIGHTER_PROJECTILE_LAUNCH_F642.md),
selected `scripts/repo-python scripts/verify-fighter-projectile-launch-f642.py --boss 0x004AC040`.


## F644: six full 28-byte native x87 float-to-double game math adapters, all original linked bytes

Pinned original Japanese TH075 PE complete registered
`0040D920`,`0040D960`,`00412DB0`,`00428D40`,`00442040`,
`00449A80` functions each have **28 whole CODE bytes/12 genuine
x86/one typed PE-targeted zero-addend `REL32` call at +14** to
original real callee `00641754`,`00641804`,`006418CD`,
`00641E54`,`00641FD0`,`00642120`. Normal MSVC VC7.1
`probes/GameFloatMathAdaptersF644.cpp` C++ `float(float)` adapter
around a native double(double) callee reproduces actual x87
`FLD dword [EBP+8]; SUB ESP,8; FSTP qword [ESP]; CALL target;
ADD ESP,8; FST dword [EBP−4]` and complete whole return ABI.
All **168/168 real original linked native CODE bytes, 72/72
x86, 6/6 actual physical typed PE/COFF call destinations** are
independently verified; true original PE direct CALL scan across
4,351 registered CODE extents has one actual caller each, five
F640 wrappers and one authored round-banner source. Original six
source owners remain `unknown`/`review`: machine-code or game-call
identity cannot establish explicit authored versus generated/library
wrappers. Combined source-backed entire origin-unknown whole functions
F616/F618/F634/F638/F640/F644 are **29/658 actual native CODE
bytes**, all uncredited. [F644 complete native source and original
field/caller proof](GAME_FLOAT_MATH_ADAPTERS_F644.md), targeted
`scripts/repo-python scripts/verify-game-float-math-adapters-f644.py`.
Official authored exact remains 943/862,726; no full cold replay.


## F645: native 60-x86 B4/B5 motion restart, original two final JMPs and true actor-specific aux state

Pinned Japanese TH075 PE authentic next physical game handlers
**B4→B5→C8**, not the B6..C7 common default. Each entire original
native B4/B5 case has **60 x86 /215 CODE bytes** normally, wide
original `00564BE0` **275 B** (20 genuine saved-this `EBP−0x88`
receiver MOVs widened ×3). Original stage-zero game action resets
via `00453E20`, initializes true position +8f/−8f, velocity
12.5f, drag .75f, clears actual +0x30 and calls original
`0040FC50`; strict native `POS48 > ground float [0065782C]`
branches into drag/ground action0xA and reset path. The original
frame-completion auxiliary `0040FB40` argument is actor- and
case-specific: B4/B5 pairs native 7/5, 8/10, 7/7, 6/6, 7/6.
A first natural-C++ source produced **59/60 x86** per full case,
missing the original second **final native JMP**. An additional
ordinary C++ `break` within the auxiliary state conditional, PLUS
final outside `break`, reproduces both original ordinals58/59
without assembly. **11 fresh whole-giant VC7.1 C++ source TUs**
now strictly reproduce **22 complete original native case interiors
/1,320 real GPR/x87/CFG x86 roles /4,850 uncredited original native
inner CODE bytes /176 physically typed zero-addend original PE/COFF
calls/globals**. The same new whole parent objects recheck F642
A7/A8 x87/FILD, F641 A3/A4/A5, F639/F637/F636/F633, earlier
original 30 game action grammars and full separately owned
original afterRET jump DATA, while prior native register negatives
remain honestly nonexact. F598–F645 strict interior study totals
**566 cases/153,255 original native inner CODE bytes**, no accepted
new authored whole-function exact CODE. [F645 original PE and
natural C++ proof](FIGHTER_MOTION_RESTART_F645.md), targeted
`scripts/repo-python scripts/verify-fighter-motion-restart-f645.py --boss 0x00564BE0`.
Official authored whole exact 943/862,726 remains unchanged; no
all-unit cold replay or external Oracle receipt.


## F648: eight exact entire game-facing native state/setter and member forward leaves, original origin unknown

Original Japanese TH075 complete source-backed
`00410FC0` **24B/10x86** (real 16-bit thiscall short field setter at
+0x12, `RET 4`), `0045B6F0` **27B/13x86** (real pointer+16 and
thiscall receiver return), `00458770` **22B/10x86** (real
this+4 member call `00411C70`), `004229D0` **28B/12x86** (native
constructor argument forwarding to `00422A50`, receiver return),
and four **15B/7x86** whole zero-argument forwarding wrappers
`0040F9F0`,`004229C0`,`0045B6B0`,`005FAAD0`. Ordinary VC7.1
`probes/GameStateSetterAndMemberForwardF648.cpp` reproduces all
**161/161 original complete linked native CODE bytes /73/73
original x86/6 genuine zero-addend physical PE-target REL32 call
fields**. Original direct x86 CALL graph across all 4,351 registered
whole native extents finds one real compiler/STL-like call each
except state setter 00410FC0 has no direct registered call; neither
source names nor callers establish original explicit authored vs
compiler/library origin. All eight retain `unknown/review`, zero
new accepted authored CODE. Whole origin-pending source study
F616/F618/F634/F638/F640/F644/F648 now **37 original complete
functions/819 actual native original CODE bytes**, all uncredited.
[F648 original physical full-byte/source and caller evidence](GAME_STATE_FORWARD_LEAVES_F648.md),
selected `scripts/repo-python scripts/verify-game-state-forward-leaves-f648.py`.
Formal 943/862,726 authored exact remains unchanged; no all-unit cold replay.


## F646/F647: native 30-x86 CF and 60-x86 D0 reflected-landing source only in three selected huge fighters

Original pinned Japanese PE actual D0 complete 60-x86 case
negates signed byte direction+0x66, does real `FLD/FCHS/FSTP`
float position reflection, then original global-first
`FLD [0065782C]`, `FLD this+0x5C`, `FUCOMPP`, `TEST AH,0x44`
equality to set 0.6f drag; ground x87 threshold, game action0xA
and reset, otherwise original frame auxiliary action5.
Original complete CF30-x86 case sets motion flag+0x3AC,
subtracts float global `00657478` from position, clamps/clears at
ground `0065782C`, calls original frame and action0.
Ordinary VC7.1 natural source `probes/FighterReflectLandingD0F646.inc`
and `probes/FighterFallStateCFF647.inc` compiled inside actual whole
giant source TUs yields **strict original D0 at `00564BE0`
(60/252 B/6 actual typed fields; 19 native saved EBP−0x88 MOV
+3B), `005214B0` (60/195 B/6), and CF+D0 TOGETHER at
`00543210` (30+60 original x86/114+195 original inner CODE B/
4+6 typed native fields)**. Three newly compiled whole giant
sources each reverify preceding F645 B4/B5, F642 A7/A8,
older source-backed native actions and entire separately owned
original afterRET jump DATA. Other 9 fighter original D0 cases
remain **35/36 genuine GPR-role mismatches** despite identical 60
x86/6 COFF; adding CF shifts register cycle and can regress
previously matching D0 in other parents. Fourteen whole-parent
natural C++ lvalue/float/condition variants failed to resolve it.
**4 newly strict original internal case bodies /210 actual native
x86 roles/756 original uncredited inner CODE B/22 PE/COFF refs**.
F598–F647 bounded case study **570 strict original inner cases /
154,011 original native inner CODE bytes**, NOT accepted whole
functions. [F646/F647 actual original PE and source/negative proof](FIGHTER_FALL_REFLECT_F646_F647.md),
`scripts/repo-python scripts/verify-fighter-fall-reflect-f646.py --boss 0x00543210`.
Official 943/862,726 accepted authored whole CODE unchanged, no
943-unit cold replay or external Oracle.


## F650: original 27-byte stdcall virtual callback and 43-byte real conditional CRT free whole functions

Pinned Japanese native original `004170B0` is a complete 27-B/
14-x86 method with native `MOV ECX,[ECX]` vtable load then `PUSH
receiver; CALL [ECX+8]`. Ordinary `__stdcall` function-pointer
forwarding had the same size but wrong argument evaluation order;
**abstract C++ virtual `__stdcall` Third()** yields all 27/27
original machine bytes and original third-slot vtable sequence,
without ASM. `004588B0` is full 43-B/17-x86 normal C++ destructor-
like conditional free of `this+8`: real native `EBP−8` receiver,
`EBP−4` meaningful free-pointer local and physical zero-addend
`REL32 +32` to real original CRT `00640F15`. Initial source
with separately named `raw` pointer had 49 wrong bytes; direct
pointer member read with a real used `void*` local recovers **43/43
fully linked original native bytes**. Together **two newly full
source-backed original functions/70 whole CODE B/31 x86/one real
physical PE/COFF call**, original direct game callers and original
native branch validated. Both original historical authored/vendor
source origins remain `unknown/review`, ZERO exact authored credit.
Previously F595 independently matched `004135F0` 40/40B field
setter and is NOT counted again as F650. F616/F618/F634/F638/
F640/F644/F648/F650 recent distinct whole unknown study **39
functions/889 original CODE bytes**, or **40/929** including
separate F595, all uncredited. [F650 complete linked native
PE/COFF/VC7.1 and call graph proof](GAME_COM_VIRTUAL_RELEASE_F650.md),
targeted `scripts/repo-python scripts/verify-game-virtual-release-f650.py`.
Formal accepted authored whole exact 943/862,726 unchanged;
no full 943-unit cold replay.


## F651/F652: four consecutive native CF/D0/D1/D2 cases strict in one giant 00543210 whole source, 450 new original inner CODE bytes

Original Japanese TH075 physical giant `00543210` handlers D1→D2→
0x12C include full 59-x86/199 B native D1 and 74-x86/251 B native
D2. Resource signed-short `this+0x3B0` has true decrement3 and
original early state0 or9, stage/frame0 creates kind0x3E6 side1
sprite at game `00453A70` with true raw x and signed orientation
and FPU y `F32(0x48)+[00657888]`. D1 calls reset `00453E20`
and prepare `00453D60(0x2C)` before sprite; D2 spawns before
native speed scaling `POS/ POS54` via global `00657F74` and prepare,
then **applies drag outside the stage0 guard**: real x87
`FLD member+0x5C; FMUL [00657F74]; FSUBR member+0x54`.
Wrong initial C++ nested drag produced 74/74 x86 but wrong
JNE targets at D2 ordinals16/20; moving it out and using real
`F32(0x54)/F32(0x5C)` member expression restores original
physical x87/CFG roles. Full new VC7.1 giant `Advance()` C++ TU
now simultaneously verifies original **CF30 x86/114B/4 COFF,
D0 60/195B/6, D1 59/199B/8, D2 74/251B/10**: four consecutive
true native cases **223 x86/759 internal B/28 real physical refs**,
with only **D1/D2 133 native x86 /450 original internal CODE bytes
/18 real PE/COFF fields newly strict**. Earlier F645/F642/F614
source-backed game cases and entire original afterRET compressed
jump DATA likewise rechecked on same fresh parent C++ object.
Eight other real actor D1/D2 source candidates remain 28 and
42–52 real GPR/x87/CFG mismatches each; native `005AEEC0` and
`00564BE0` lack actual D1/D2 physical handlers. No false credit.
F598–F652 strictly source-backed case study **572 genuine original
interiors/154,461 original inner CODE bytes**, not accepted whole
functions. [F651/F652 native PE, typed COFF and source proof](FIGHTER_RESOURCE_SHOTS_F651_F652.md),
`scripts/repo-python scripts/verify-fighter-resource-shots-f651.py`.
Official 943/862,726 whole-authored exact unchanged; no all-unit replay.


## F649: full original native complex CC collision/stage source x86 grammar, NONEXACT native GPR phase

Original Japanese TH075 physically bounded action0xCC case in
huge `005AEEC0`: **128 native x86 /435 original CODE B**, and
wide `00564BE0`: **126 x86 /542 original native B** from 39
actual widened saved-this EBP−0x88 MOVs (+3 each), normal compiled
source case 425 B. Genuine CC collision `00454BC0(3,4,255)`
requires original five-byte `PUSH 0xFF`, NOT two-byte `PUSH -1`;
16-bit `++I16(+0x64)`/`++I16(+0x62)` produce original 16-bit
MOV/ADD instead of C++ promoted `MOVSX` intermediate. Original
sprite `00453C80(kind0x3C,x,y,side1,1)` uses **raw float member
DWORD MOV/PUSH bit copies**, while source float-by-value generated
extra x87 `FLD/FSTP`; a provisional *raw ABI proxy* is required
for compiler byte-geometry diagnosis, NOT a proven historical
function declaration. **22 attempted whole original giant VC7.1 source variants**
(20 full compiler objects and two genuine C2105 postfix-increment rejects) and fresh typed original PE source
comparison prove all original 128/126 x86 ordinal/mnemonic/width
geometry, complete case native extent, **11 true physically typed
original COFF float/call targets per actor**, complete afterRET
jump DATA shape, but still **80/78 actual non-field GPR/CFG role
mismatches**. These are NOT strict case interiors, not exact
whole-giant CODE, no acceptance or total credit. Bounded strict
F598–F652 remains **572 original native case interiors /154,461
original internal CODE bytes**; accepted authored whole exact
943/862,726 unchanged. [F649 original whole source CC negative
compiler proof](FIGHTER_COMPLEX_STAGE_CC_F649.md),
`scripts/repo-python scripts/verify-fighter-complex-stage-cc-f649.py`.
No all-unit cold replay.


## F653: strict natural C++ native falling-recovery cases in original giant 00543210

A new complete 58,294-CODE-byte fighter giant source probe cold-built under
pinned VC7.1 matches the original **three consecutive 12C/12D/12E
physical inner case extents** (207/219/207 original CODE bytes, 59/61/59
native x86 instructions) with all **18 original PE/COFF fields**,
true GPR/x87 and full CFG roles. Original `12D` uniquely clears its
extra short flag `+0xF00` and triggers animation stage 4; `12C`
prepares `0x1B` at stage 2, while `12E` prepares `0x1D` and sets
action 2. Actual original x87 `FSUB` float `00658058` uses a verified
typed DIR32 relocation; **do not confuse its zero-valued unlinked
COFF operand with an incorrect original float constant**. Strict
F651/F652 CF/D0/D1/D2 and complete after-RET switch DATA were
rechecked in the **same newly compiled** fighter. Net newly strict
**179 native x86 /633 internal original CODE B /18 typed PE/COFF**;
now **575 strict original internal case bodies /155,094 uncredited
native CODE bytes** across giant research. 22 whole giant parents
remain NONEXACT, all 943/862,726 independently accepted whole function
figures unchanged. [Full original proof](FIGHTER_FALLING_RECOVERY_F653.md),
`scripts/repo-python scripts/verify-fighter-falling-recovery-f653.py`.
No 943-unit replay.


## F654: two more original native fighter falling stages and ground-shot exit

A new full giant fighter `00543210` C++ source probe adds real complete
**0x12F (82 x86/288 B/8 native PE fields) and 0x130 (79 x86/261 B/6
real native fields)**. Stage-4 case `12F` subtracts 0.6f/0.9f through
**separate genuine original PE globals** (00658058/00659240), then
initializes 25.0f original vertical movement; `130` has exact x87
ground contact, genuine y/vertical/acceleration clears and original
stage-3 0x339 shot. All real physical REL32/DIR32 call/globals,
addends, 161 instruction roles and full CFG/widths match original
native after verifying the entire freshly compiled parent, prior
seven CF/D0/D1/D2/12C/12D/12E strict cases and all independent
original post-RET jump DATA. F598–F654 **577 strict native case
interiors /155,643 uncredited original CODE bytes**, with **nine
consecutive cases /563 original x86 /1,941 internal CODE B /60 real
PE/COFF fields** in this one giant. No whole giant or new independent
authored function is accepted. [F654 complete proof](FIGHTER_FALLING_FINISH_F654.md),
`scripts/repo-python scripts/verify-fighter-falling-finish-f654.py`.
No 943-unit full cold replay.


## F655: seven new complete source-backed origin-UNKNOWN native game-adjacent leaves

Fresh pinned VC7.1 ordinary C++ compilation reproduces full real
original PE extents `004138D0`/`004169D0` (each 11-byte saved-this
empty method), `0041F7F0`/`00540280` (distinct 11-byte CDECL pointer
+8), `00441FD0`/`0045B630` (distinct 5-byte empty CDECL stubs), and
`00409490` (19-byte genuine thiscall forward to original `00409860`).
**All seven complete original 73 CODE bytes /43 genuine native x86
roles** are proven whole-machine-byte identical. Original forwarder
has exactly **one real zero-addend COFF REL32 field**, linked only to
its independently verified original PE call address. Original native
registered whole CODE direct-caller graph: 0/1/1/1/0/1/3 respectively,
with **one** authored caller of forwarder, not proof of its historical
source origin. These seven source identities remain **unknown**
origin, no authored exact credits. Separate F595 and F616–F655
source-backed unknown research cohort is now **47 distinct complete
original native functions /1,002 CODE bytes**, all uncredited;
95 historical uncertain provenance rows remain unchanged.
[F655 complete original proof](GAME_UNATTRIBUTED_LEAVES_F655.md),
`scripts/repo-python scripts/verify-game-unattributed-leaves-f655.py`.
No all-unit cold replay.


## F656: five further original native fighter stage cases in 00543210

A fresh **entire giant** original selected-parent C++ compile matches
original physical handlers `0x131` (81 x86/280 CODE B/6 fields),
`0x133` (110/370/9), `0x134` (61/219/6), `0x135` (102/349/8),
and `0x136` (80/266/7). Real native `0x132` is a shared **default
handler**, not a separately owned CODE case. The five new complete
actual interior extents total **434 native x86 roles /1,484 original
CODE bytes /36 independent typed PE/COFF fields**. Normal VC7.1
C++ reproduces original x87 ground contact, distinct 006581E0
velocity decay, stage 3/8 kind 0x341/0x342 shots, stage-10/11
subtraction and authentic stage 5/10 sprite shots 0x33E/0x33F.
Every physical original REL32 call and DIR32 x87 global is checked
by source COFF type, real native instruction target, symbol and
addend. Earlier **nine** native CF/D0/D1/D2/12C/12D/12E/12F/130
cases and complete after-RET switch DATA remain strict in the SAME
newly compiled giant. All 14 consecutive physical cases now have
**997 original x86 roles /3,425 real native CODE bytes /
96 PE/COFF fields**. Across F598–F656 the source-backed genuine
strict inner case cohort reaches **582 /157,127 original internal
CODE bytes**, still **zero independently whole-exact giant
function acceptance**. The authored 943/862,726 formal exact ledger
is unchanged. [Native F656 source and proof](FIGHTER_LATE_STAGES_F656.md),
`scripts/repo-python scripts/verify-fighter-late-stages-f656.py`.
No 943-unit all-unit cold replay.


## F657: three more strict fighter native stages, plus real EBP scratch blocker

The original physical native cases 187 (50 x86/181 original B/
5 real typed PE fields), 188 (50/181/5), and 189 (112/405/9)
strictly match a **new selected complete giant `00543210` VC7.1
C++ parent**. Original 187/188 contain stage-zero motion/10f/15f
initialization, signed stage-gated native gravity and action0/2
transitions. Original 189 contains exact original positive 006578C0
float drag, bounded stage7–8 x87 y collision and action9 auxiliary
transition, plus 9.0f/0.9f stage7 motion. Fresh proof includes all
19 real PE/COFF field/source symbols and all original 212 x86 roles.
Actual preceding original native case 186 is **NONEXACT** despite
matching 82 x86 mnemonics and all 8 physical COFF fields: its two
original EBP−0x84 scratch operations compile to EBP−0x20, 284 bytes
vs 290 real native. A separate raw operand verifier protects this
from the historical F598 broad EBP-slot normalization. No fake local
or arbitrary padding. Fourteen previous original native cases plus
full after-RET switch DATA are rechecked in the SAME whole parent.
Net **585 strict original inner action cases /157,894 original
uncredited internal CODE bytes** in giant research; selected 00543210
has **17 strict, not uninterrupted** internal stages (4,192 B /1,209
x86 /115 original fields), because case 186 is a genuine unresolved
gap. All 22 original whole giants remain NONEXACT and formal
943/862,726 original whole authored exact ledger unchanged.
[F657 genuine case proof](FIGHTER_MOTION_CONTINUATION_F657.md),
`scripts/repo-python scripts/verify-fighter-motion-continuation-f657.py`.
No mass replay.


## F658: 19 further entire origin-UNKNOWN native leaves, zero relocation byte masks

New ordinary pinned VC7.1 C++ source for **19 distinct original
registered function extents** yields **181/181 exact complete
original PE CODE bytes /111 whole x86 instruction roles /zero actual
COFF fields**. Seven empty CDECL originals (5 bytes each), three
CDECL argument identities (8 bytes), four pointer+4/8 CDECL returns
(11 bytes), four first-DWORD receiver accessors (16 bytes) and one
14-byte `return this` member form are independently reproducible
from **one** small source translation unit; no fake layout/stack
padding or invented machine-code bytes. Original caller graph over
4,351 registered native CODE extents is saved but **not** an origin
attribution claim: current authored direct callers of these
simple leaves are zero, and other indirect callers are not excluded.
Distinct prior F595–F655 origin-unknown cohort 47 functions/1,002
CODE bytes now grows to **66 independently source-backed complete
original functions /1,183 native CODE bytes**; all **95 historical
origin-unknown native candidate rows remain uncredited** and formal
accepted authored ledger **943 /862,726** is unchanged.
[Full native F658 proof](GAME_UNATTRIBUTED_SIMPLE_LEAVES_F658.md),
`scripts/repo-python scripts/verify-game-unattributed-simple-leaves-f658.py`.
No all-unit cold replay.


## F659/F660: live rechecks and new authentic negative source hypotheses

Original whole 33,293-byte CharacterObject boss `004EBDA0`
still compiles 8,789 native x86 and 682 physical COFF fields but
has **137 original non-COFF byte differences starting at
004F344C**. Fourteen new pinned VC7.1 full-source trials of original
stage4 test syntax, stage3 nested control flow/real arguments,
fade control grammar and stage2 alpha arithmetic prove **12 identical
137-byte register-cycle negatives** and **two `+=` forms regressing
to 141 and erroneous physical native x87 widths**. Independently,
seven whole 171-byte ArchiveCatalog authored destructor C++ filename
lifetime experiments verify five unchanged **108/115** originals and
two degraded **102/115**, with original EBP resource/delete/filename
slots still wrong. None is whole-exact or accepted; no fake C++ locals.
[Giant and destructor original native F659/F660 negative detail](GIANT_REGISTER_AND_ARCHIVE_LIFETIME_NEGATIVES_F659_F660.md).

## F661: source-backed original fighter projectile 18A/18B with physical EBP nonmatches

One **fresh complete** VC7.1 C++ fighter parent source `00543210`
adds authentic original full physical 18A (71 x86/256 CODE B/6 typed
fields) and 18B (99/359/7), recovering real side*151 and side*128
sprite coordinates, original native x87 y offsets and short counter
stages. Both are deliberately **NONSTRICT**: two genuine original
EBP−0x88/−0x8C integer-to-float scratch operand pairs compile at
EBP−0x24/−0x28, giving 250/353 original-sized compiler case bytes
instead of 256/359. Normal GPR/x87/CFG roles and all **13 actual
original typed PE/COFF fields** match, but the four real EBP
operands/widths do not; a new verifier compares raw physical EBP
slots independently of the old broad normalizer. **All 17 preceding
strict original fighter cases and complete after-RET jump DATA** were
rechecked in the **same newly compiled parent**. F598–F661 strictly
backed fighter inner case total remains **585 /157,894 native CODE
bytes** (not including these 615 new nonstrict source-backed bytes).
All 22 original whole giants remain NONEXACT, 943/862,726 authored
whole-function exact unchanged.
[Full F661 original native/source proof](FIGHTER_MOTION_SHOTS_F661.md),
`scripts/repo-python scripts/verify-fighter-motion-shots-f661.py`.
No 943-unit mass replay.
