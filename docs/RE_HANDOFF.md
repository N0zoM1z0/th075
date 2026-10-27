# TH075 active reconstruction status — F198

Updated 2026-10-27. The user explicitly resumed reconstruction and requires
serious treatment of both large/core and small/leaf functions; all historical
assumptions are provisional. Do not avoid or discard dirty work. Use commit
subjects `gpt-web: ...`. The H184 *no-active-goal* handoff below is historical
and superseded by this active request.

F184 input functions were independently reconstructed from the supplied target and accepted
by complete canonical cold replay:

| Function | Extent | Code bytes | Actual relocation fields | Cold replay |
| --- | --- | ---: | ---: | --- |
| TitleScene::PollMenuInput | 0043ABF0..0043ACD3 | 228 | 19 | exact |
| ReplayScene::PollInput | 00429DC0..00429EF5 | 310 | 27 | exact |

Both original extents end in plain RET and are followed by INT3 alignment.
Independent Capstone decoding consumed all 538 native bytes. Ghidra read-back
agrees on boundaries and direct callees; VC7.1 source code independently
recompiled into two complete matching COMDAT bodies in one object. All 46
relocation offsets, types, symbols and resolved native targets are retained in
`config/match-units.toml`. The replay command used:

```bash
scripts/repo-python scripts/replay-exact-units.py --unit title-poll-menu-input-0043abf0 --unit replay-poll-input-00429dc0
```

Distinct synthetic pointer-only receiver interfaces avoid asserting the title
and replay scenes share a complete class layout. DWORD title controls and byte
replay controls, independent signs, ESC behavior and window-toggle key chord
remain separate. Native C++ class names, owner layouts and runtime integration
are still unknown; no imported credit was granted for helpers or data.

F185 added a substantial core state machine, **`TitleScene::Advance` at
`0x0043A270`: 1,273 CODE bytes plus the full 40-byte owned ten-entry switch
table immediately after RET**. Target body and table were independently read
from the pinned executable; native code hash
`f528f379b927bad808eaa0703fa48c798fb8998bbae44ca9a2c96264215928a7`,
table hash `01b9780b16a3176977d6c14d930d0eb42e860439a880b82435248b8459770254`.
All 342 native instructions, table entries, 65 external and 11 local
relocation fields were checked. Cold source replay of the full 1,313-byte
extent returned exact. The code implements two-player menu mode dispatch,
exit/cancel/navigation, per-item fade progress, timed transition and
randomized attract mode with audio fade. The source is a pointer-only borrowed
scene/virtual-slot view: owner layout, original return type/name and broader
runtime identity remain unproven; source/byte credit is only for the 1,273
function CODE bytes. The jump table is compared but adds no CODE credit.

A redundant identical candidate unit alias was independently detected after
registration and reconciled, leaving **one uniquely mapped unit for each
matching function** (496/496). Its private reconciliation receipt is preserved;
new automated coverage rejects unmatched or duplicate extents. No unrelated
source, original object layouts or origin classifications were changed.


F186 additionally cold-reconstructed **`OptionsScene::AdvanceAt00428F00`**,
a 951-byte scene state-machine with an adjacent owned 28-byte / seven-entry
switch table. The complete 979-byte extent, **70 COFF relocations including
eight same-COMDAT local-target fields**, is cold-exact. Independent Capstone
decoding consumed all 269 native code instructions, ending at plain RET
004292B6; the table occupies 004292B7..004292D2 and is followed by INT3.
Native CODE SHA256
`21e698c0f26cbca4c23286883c7de9a04cf91b1825c1090dfa320b09956f75fa`;
table SHA256
`f84e9f643843fc0db5c9ce2278848b8224a99bb915d32538e7d99646afd4f124`.
The reconstruction retains seven menu choices, signed two-axis navigation,
three option toggles, signed wrap/modulo policy, sound/stream volume bounds,
audio-offset application, delayed sample sound, configuration saving and
two early transition exits. The initial ordinary `!flag` source generated
a 982-byte comparison block; a later `1 - (flag != 0)` control gave 1001;
natural `flag ? 0 : 1` reproduced native 32-bit NEG/SBB/INC and all
remaining instruction/branch locations. Failed control objects and proofs
remain under `.analysis/f186-options-advance/`; no structural-only result
was counted as exact. Both call-only scene interfaces and the separate
configuration-saving callee remain provisional: this unit earns only its
own 951 CODE bytes, not helper/table ownership credit.

F187 cold-reconstructed **`GameConfig::SaveIni`** at 00419450: 339 native
CODE bytes / 116 complete instructions, one plain RET at 004195A2 and
following INT3. The full 339 bytes and **27 actual DIR32 relocation fields**
(including the verified native filename anchor 00657A70 and four Win32
imports) pass canonical cold replay with zero differences. Its real C++
source calls `CreateFileA("config.ini",...)`, `SetFilePointer`, exactly
eleven `WriteFile` operations of 80-byte config storage and observed individual
bytes, and `CloseHandle`. The third write precedes a real byte store of 1;
no invented struct layout, ignored return check, Win32 shortcuts or data-byte
credit. The original source's namespace and full storage ownership remain
unknown. The first ordinary /Od source (same 339 bytes) used a different
HANDLE/DWORD stack order, giving 26 nonrelocation byte differences; declaring
the real `DWORD written` ahead of `HANDLE file` reproduced the native local
slot assignments and complete compiler output. F187 implements the *same*
`OptionsSettingsF186::SaveConfiguration` COFF name already called by F186;
the accepted F186 body/source/relocations were not modified.

F188 independently cold-reconstructed `OptionsScene::ApplySelectionAt00429F00`:
**563 CODE bytes** plus the following owned **28-byte seven-entry switch
jump table**, 591/591 full comparison bytes and **34 actual COFF relocation
fields**, of which eight are local to this COMDAT. The native body is 137
x86 instructions ending in RET 4 at 0042A130; the native code SHA256 is
`65e7c664f6846ac95a8085eeb2bba5eab32f5ad2c272cb3d2dfa049ad8e2d759`,
and the following table SHA256 is
`3bab5fa7d3230c10ba3afdd6140cc4ddd35837b701713cbff1d0156ffe9a64b2`.
The complete owned 591-byte comparison, including all relocations, passed
fresh /GX cold replay. Ghidra/dependency inspection independently confirmed
Direct3D8 LockRect/UnlockRect slots, the 56-byte `operator new` size,
FontSurface constructor, CreateFont, Rasterize, generated scalar deleting
destructor and EH/cookie recovery. Native handler 006558BD and its
006558AF cleanup remain external compiler-generated dependencies; they are
**not** independently counted as matching source or data. The source
uses exactly the existing F186 caller COFF method symbol, with signed
menu-index comparison reflecting native MOVSX.

The unoptimized /GX- probe gave a different non-EH 534-byte body; /GX
reconstructed the EH prologue and typed allocation. A nominal 512-byte text
buffer caused an 8-byte stack-window displacement. Natural 500- and
504-byte text buffers both gave the same native frame; the original nominal
buffer size remains unknown. The original unsigned switch expression
emitted MOVZX, and a signed comparison restored native MOVSX. A later
source-only offset-check experiment renumbered compiler-local jump labels;
that control was rejected and the original field/target mapping cold-replayed
again. All experiments remain private under
`.analysis/f188-options-selection/`. The 56-byte temporary rasterizer
allocation is physically anchored to native constructor/method offsets and
allocation size, but member +0x18 and complete original class semantics are
unproven. Do not transplant that type or infer other owners. There is no
claim of exactness for borrowed text rendering, D3D or EH helpers.

F190 independently cold-reconstructed `Graphics::SetDefaultStates`
`0x00401540`: **604 CODE bytes / 178 native x86 instructions**, with
**45 genuine COFF relocations** and no owned switch table. The entire 604
bytes were recreated by pinned VC7.1 /GX- from natural D3D8 API calls.
Native code SHA256:
`d5cff4b102acaa874856d80ff21fd09dcd624731c4775e81d6ea00f4c3d74bac`.
The source preserves all four initial render-state changes, three accepted
blend/depth/filter helper calls, eight texture-stage states, later cull/lighting
states, FVF `0x144`, feature-gated D3DXAssembleShader of the observed shader
source at 0066C090, pixel shader creation and buffer release, the four real
floating-point grayscale weights, SetPixelShaderConstant, and the accepted
pixel-mode state setter. No data, D3DX SDK/library helper or global bytes
receive separate credit. Initial ordinary `if (g_Device)` generated a
603-byte structurally mismatching body: it used one long conditional jump.
Writing the equivalent but native-observed `if (g_Device == 0) return;`
restored the short conditional plus long unconditional branch and all
604 bytes matched, with 45 fields replayed. Private negative controls are
under `.analysis/f190-graphics-defaults/`.

F189 separately investigated the large `BattleScene::Initialize`
`0x0043AD10`: its complete 922 bytes decode into 230 instructions, one
RET and original EH constructor frame. The native contains four nested
allocation extents (0x50, 1, 0x14, 0x14 bytes) and dependencies that lack a
proven complete source-level owner layout. Its native disassembly is retained
in `.analysis/f189-battle-init/native.asm`, **without accepting or crediting
unconstructed objects**. That large function remains a live target, not a
reason to ignore the worktree or to fabricate layouts.

F191 cold-reconstructed the other major music-room text routine
`MusicRoomScene::RenderSelectedDetails`, `0x00426A70`. Its full native
**860 CODE bytes** decode into **217 complete x86 instructions**, ending in
`RET 4` at 00426DC9 with following INT3 alignment. Target body SHA256:
`ea9d870e0edd790fe014a723f6a6466ff5867dec44fda5dee483ea856452b7ae`.
The full function and **25 actual COFF DIR32/REL32 fields** pass fresh
canonical VC7.1 `/GX` cold replay with zero differences. No owned jump
table is attached to this extent. It performs two independent
`IDirect3DTexture8::LockRect/UnlockRect` passes, each with native
`new(56)`, rasterizer constructor/font setup, render and generated deleting
destructor, and has original EH/GS cookie handling. The first pass copies the
selected or fallback track description through the original CRT `_strcpy`
callee; the second formats the track number, title and artist through
`_sprintf`. The target uses *signed* track bounds and a real 16-byte
per-record stride.

Independent compiler controls caught a meaningful order distinction:
`selected >= trackCount` emitted an alternate register/branch sequence
(matching 722/760 non-relocation bytes), whereas
`trackCount <= selected` produced the target's count-first comparison and
all 760 nonrelocation bytes. Literal 1,996- and 2,000-byte text buffers both
reproduced the same measured code, whereas 2,004 and 2,008 displaced
stack slots by eight bytes; the precise original buffer declaration remains
unknown. The physically 56-byte glyph allocation carrier is observed from
the native allocation and actual constructor/method accesses, not proof of a
complete reusable original font owner; +0x18 remains unresolved. No
additional byte credit for the GDI helpers, SDK, game-data strings or EH
helper. Private cold evidence and rejected probes are preserved under
`.analysis/f191-music-details/`.

F192 followed the actual base-scene lifecycle into a small but independently
reviewed destructor. The complete 31-byte `SceneBase::ReleaseGameGlobalsAt00431F40`
has 13 decoded native instructions and two COFF fields: the observed vtable
anchor `0x00657B88` and the true `0x00417430` config cleanup callee.
Its native body hash is
`f0fdc9015cffb6b7194ee2641a8018c52eb7a984d6a68d1f9e8c809b77698cf9`.
A standalone call-only `SceneBaseReleaseF192::~SceneBaseReleaseF192`
cold-builds to **31/31 exact** with both relocation fields fully replayed.

The paired scene base constructor `0x004251C0` was independently decoded
(34 bytes, 13 instructions, native hash
`9ff723978ea0aa946f4147ff70aef987da9b3dbd431196873a7dc4fa331eb85f`)
and a **private full 34-byte structural-exact compiler probe** was built,
including its vtable anchor and separate `0x00417210` defaults initializer.
However R108's original explicit-vs-compiler-generated ownership ambiguity
cannot be resolved just by that match. It remains **unknown origin, no source
mapping, no match unit, no exact byte credit**, and is still counted in the
conservative pending denominator. This was deliberately not hidden or
force-reclassified to inflate the count.

F193 follows the previously identified scene-base global-configuration
constructor dependency. The authored `GameGlobals::Initialize` body at
`0x00417210` contains **531 CODE bytes / 92 native x86 instructions** and
**71 actual COFF relocation fields**. Target SHA256:
`45043cd59354a3a3d1d5525d2c44233786e44e3cbfded0b2c45cd5dbc3a4f7b3`.
Natural VC7.1 `/GX-` source cold-replayed all **531/531** bytes, including
every field. The source preserves first-use gating at 00671614, each observed
byte/DWORD keymap/default store, two player selections, eleven string copies
to physically 20-byte-spaced character-name slots, mode flags, and the
`0x004192F0` Win32 configuration-load dependency. It preserves the
two native stores to one setting byte at 00671438; that byte's original
source-level variable grouping remains uncertain. The source declares
only borrowed global anchors; it allocates no settings storage, imports
no helper/data credit and does not assert the original globals' nominal
array extents. The `0x004251C0` constructor that calls it remains
**origin unknown** and is not added to exact coverage.

F194 closes the actual F193 config.ini *read* dependency at
`0x004192F0`: **339 native CODE bytes**, **116 fully decoded x86
instructions**, **27 actual Win32/data relocations**, whole
canonical /GX- cold replay **339/339 exact**. Target native body SHA256:
`5a76d9c05e369ba111429f3160678f7cd068acbf2942f27f85afcf258dbab4df`.
The Win32 sequence is CreateFileA("config.ini", GENERIC_READ,
OPEN_EXISTING), SetFilePointer, one 80-byte + ten single-byte ReadFile
calls, one observed flag normalization after its own read, CloseHandle
and normal RET. The original HANDLE and meaningful DWORD read-count
locals occupy EBP-8 / EBP-4, unlike the already accepted save policy.
Initial natural 339-byte controls mismatched 26 nonrelocation bytes
despite equal size; independent local-name and declaration controls
showed the compiler's physical local slot allocation depends on
meaningful symbol identities. The adopted `readSize` is a genuine
bytes-transferred output. Original source-level variable spelling
remains unproved. Readonly filename/data storage and imported APIs
earn no extra byte credit, and the separately accepted F193 caller
is unchanged.

F195 follows the other end of the shared scene/global lifetime:
the **358-byte `GameGlobals::Release` at `0x00417430`**, 99 native
instructions and 18 actual relocations, complete canonical /GX- cold replay
**358/358 exact**. Native target SHA256:
`238163545e5867e5869753fed589643a52634d8107f9fe11486a58a42bd6016b`.
Natural source retains the reference-count decrement and zero gate;
three different borrowed virtual-destructor paths (slot +0x14 for two
combat actors, slot0 for a third), three real pointer null stores,
streaming audio shutdown through accepted `ClearPlayback`, and three
distinct scalar-deleting-destructor call targets 0041A110/41A140/41A170
for separate heap-owned resources. The body was full byte-exact on the
first normal source probe, using only call-only pointer views; no
complete unknown heap classes were instantiated, no code/data credit
was given for the generated destructor thunks or audio helper, and
no ownership classification was changed. The authored F193 initializer
and F194 read helper are separate accepted functions. Base constructor
`004251C0` remains unknown-origin and uncredited.

F196 is the first complete exact reconstruction of the previously
unaccepted `BattleScene::Initialize` at `0x0043AD10`. Independent
target decoding gives **922 CODE bytes, 230 original x86 instructions,
no owned jump table, a normal RET, followed by INT3 alignment**;
native SHA256:
`10d1747c1b0b512f21e4b2cef06c1d00a291e05f0181d19261563e785959d75e`.
A natural C++ derived constructor compiled with pinned VC7.1 `/GX`
**cold-replays all 922/922 bytes and 40/40 actual relocation fields**,
including the external base ctor call, exact native derived vtable
pointer at 00658334, imported timeGetTime, real texture pack and two
HUD constructor chains, sound/graphics state, actor addresses,
float/byte initialization, and EH frame references. The recorded R020
original EH metadata independently confirms **five cleanup states**
for native handler 00655B74 and four transient allocation states
following the base. Generated EH helper, vtable bytes, SDK/CRT and
all borrowed subconstructor bodies receive **no independent byte credit**.

The source-compatible allocation carriers were built from independent
physical evidence: base vtable at offset0 and one-byte globals
subobject at +4 yield the observed eight-byte base boundary;
TextureManager's real ctor `0x0040AD80` calls nested vector
constructors at +8,+0x18,+0x28 (three 16-byte regions), deque at
+0x38 (20 bytes), and sets byte +0x4C. Together with its observed
root storage this physically accounts for exactly **80 bytes**.
The `new(1)` digit atlas constructor `0x00446590` has no object
fields and the actual `new(20)` combo-counter constructors
`0x0043D490` use the offsets independently accepted in F173.
Original vector element types, the texture root word at +0, original
class identities/nominal full scene layout and whether R108 base
constructor `0x004251C0` was authored or generated remain unknown.
The latter gets no new source or exact credit. These carriers are
local to the observed new/ctor call sites; the derived scene is not
instantiated, embedded or measured as a complete original type.
No false padding fields/locals, inline assembly, conditional acceptance,
masked relocation bytes, EH code grafts or cropped extent were used.
The earlier unaccepted F189 disassembly remains historical negative
evidence; do not read its old 'unaccepted' statement as current status.

F197 independently cross-tested those scene-base/texture physical
contracts on another complete constructor: `TitleScene::Initialize` at
`0x0043A020`, **435 native CODE bytes**, 116 native x86 instructions,
**18 actual COFF relocation fields**, normal RET at 43A1D2 and INT3
alignment. Native SHA256:
`e4c04d16c30c718c2504e389a945d902b5766e687aa45e40123f3e5c8fb5b573`.
It independently cold-replays **435/435 exact** from natural /GX C++.
The original independent R020 `00655B23` EH handler reports exactly
**two cleanup states** (base and one temporary allocation, native
unwinds `00655B10/18`) rather than the battle constructor's five.
The source reproduces the actual base ctor dependency `4251C0`, the
title vtable anchor `658308`, both timeGetTime imports, new(80)
TextureManager `40AD80`, slot allocation count4, original
`data\system\title.dat` pack load, all menu alpha/selection
byte stores, two selected-player bytes and sequence-state clear.
No full nominal TitleScene object size or original container element
types have been asserted or used to allocate a TitleScene. The
paired R108 base constructor remains origin-unknown and uncredited.
Matching the 8/80-byte physical contracts independently in F196 and
F197 strengthens their byte/layout evidence, not proof of original C++
names or independent acceptance of borrowed constructors.

F198 independently follows the shared texture-manager dependency called
from the complete F196/F197 battle/title constructors. **TextureManager::
Initialize at 0x0040AD80** consists of **177 native CODE bytes**, 48
whole x86 instructions, 12 real DIR32/REL32 relocation fields and a
five-state original VC7.1 EH frame. Native body SHA256
`e0ce84473c5b407a441c88fc5c7485a47547ad48e39abadf4beedd1d41cbf37a`.
A source-compatible natural constructor using the observed physical
80-byte receiver, reference-count base, three 16-byte sequence-storage
regions at offsets 8/24/40 and one 20-byte queue at 56 compiled exact
on the first full ordinary probe; the native member constructor and
reset order, offset+4 state and offset+76 byte are preserved. The
original R020 handler `00654ED4` has the expected five cleanup states,
which are target evidence, not separate new exact helper credits.

**TextureManager::AllocateUnformattedSlots at 0x0040B1D0** is
**128 native CODE bytes**, 37 complete x86 instructions, eight
actual relocation fields and the independent original one-state EH
handler `00654F48`; SHA256
`570580110f4777092fba3bb6ca93d760abb364c5dea46998a42e07ad0ed6cac4`.
A meaningful 44-byte local entry object with real ctor 0040D8C0
and destructor 0040D8E0 naturally reproduces the exact 0x34 stack
frame. The two slot initialization calls target receivers at
this+8 and this+24 and consume the real count, entry and initialized
zero value. The first natural probe also matched every byte.
Both methods passed the pinned canonical cold compiler/replay as
**2/2 exact, 305 new CODE bytes and 20 real fields**.

Member storage widths derive from independent F196/F197 native allocation
sizes, actual ctor/dtor call offsets, original EH transitions and whole
byte comparisons. Source-compatible names and container *element*
types remain provisional, as does the nominal original class identity;
neither source file defines external data or claims other helper, SDK
or generated EH byte credits. The related larger 0x0040AE40 texture
manager release remains to reconstruct.

Current ledger: **509 exact functions, 757,487 CODE bytes / 1,973,516 reviewed
authored bytes = 38.38%**, conservative 38.31% with 3,608 unknown-origin bytes
retained. F184..F198 added sixteen accepted units, fifteen objects and eighteen new
source/header inputs.
Keep R268 origin evidence, all 97 unknown candidates, 493 pre-F184
accepted units and protected private F184/F185 preview/drafts intact.

Next: attack the full 0x0040AE40 texture-manager release function
and the 0x0043B0B0 battle-scene destructor, alongside small helpers;
retain R108 origin ambiguity and the original EH metadata. with full CFG, branches, call graph,
target writes, lifetime and switch ownership before adopting any source.
Do not claim exact credit for incomplete probes. Record failed approaches and
commit separately when they yield durable discoveries.

## Historical H184 handoff (superseded active-goal and F184 preview statements)


Updated 2026-10-26 for the user-requested cleanup and handoff, H184.

The user cleared the active goal before requesting this handoff. **No goal is
active; no pause action was taken. The 98% authored-byte objective remains
incomplete.** This instruction supersedes historical active-goal commands.
No new reconstruction batch or canonical acceptance was started after the
handoff request. Subsequent project phases remain deferred.

## Continuation command

Use this command when the user requests reconstruction again:

```text
Resume TH075 function reconstruction toward 98% authored-byte exact, using
H184 and the prepared F184 menu-input cohort. Read AGENTS.md, RE_HANDOFF.md,
RE_WORKFLOW.md and KNOWLEDGE_BASE.md; inspect git status and run the four
required target/tracking/status/Ghidra preflight checks. Preserve all accepted
units, origin evidence through R268, all 97 unknown origins, every pending byte
in the conservative denominator, and private inputs/objects. Start with full
F184 previews 43ABF0/228 and 429DC0/310: both have zero differences but no
canonical acceptance. Use the H184 resumption seed against the documentation
handoff commit; preserve the old F184 seed against a306ad6 unchanged. Copy
frozen drafts to a new mutable working directory before editing. Register
complete extents/every actual relocation, then cold-replay only new units
before granting credit. Keep compiler builds serial and everything headless;
use scripts/repo-python, the existing Ghidra wrapper and no REA. Never invent
owner layouts, inert locals, padding, ABIs, assembly, comparison masks, cropped
extents or local-label rebasing. Commit/push bounded progress with subjects
"gpt-6.1-sol: ...". Do not automatically pause an active goal merely because
cleanup, a commit or context handoff finishes.
```

## Verified baseline

| Measure | Value |
| --- | --- |
| Provisional candidates | 4,351 |
| Reviewed authored / library / compiler | 1,002 / 2,671 / 581 |
| Unknown origins | 97 / 3,608 code bytes |
| Source-present / exact functions / exact units | 493 / 493 / 493 |
| Exact CODE bytes | 749,438 |
| Reviewed authored coverage | 749,438 / 1,973,516 (37.97%) |
| Conservative coverage, including pending bytes | 749,438 / 1,977,124 (37.91%) |
| Canonical objects / accepted source-header inputs | 166 / 268 |
| Adoption manifest after F009 | 433 additions / 739,555 CODE bytes |

The ledgers and status script are authoritative. CODE size determines credit;
comparison extents include owned tables/remaps. Every pending byte stays in the
denominator. Unknown origins receive no credit and do not block independently
reviewed authored functions. Names and complete owner layouts remain provisional.

Use only the supplied Japanese th075.exe 1.11, SHA-256
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
Identity is pinned to the user's archive, without independent official
provenance corroboration. Never substitute th075c.exe or patch target bytes.

The latest reconstruction commit is **a306ad6 (F183)**. This work added 16
canonical units and 9,888 CODE bytes across five pushed commits:

| Cohort | Commit | Accepted work | CODE bytes |
| --- | --- | --- | --- |
| F179 | 2a697d8 | Complete background renderer 435A70 | 6,404 |
| F180 | 4ecb7fb | Eleven background counter/cycle callbacks | 463 |
| F181 | d13a8e9 | Complete timed-sprite renderer 451A00 | 446 |
| F182 | 9d128c4 | Two name-entry input policies | 1,486 |
| F183 | a306ad6 | Complete title-menu renderer 43A7A0 | 1,089 |

Each cohort cold-replayed only new units and passed 3,612 CI tests. Existing
canonical inputs, origins, headers and protected evidence stayed unchanged.
Detailed proofs/cold reports/checkpoints remain under `.analysis/f179*` through
`.analysis/f183*`.

## Prepared F184: diagnostic previews only

| Native function | Bytes | Returns / branches | Actual fields | Differences |
| --- | --- | --- | --- | --- |
| R043 43ABF0, TitleScene::PollMenuInput | 228 | 1 / 9 | 19 | 0 |
| R053 429DC0, ReplayScene::PollInput | 310 | 1 / 16 | 27 | 0 |

Both full extents have plain RET, no owned tables and checked following INT3
alignment. All 18 calls target canonical input/window helpers. Every one of the
46 fields is included. Neither function has public source, a registered unit,
a canonical cold build, source-presence credit or exact credit.

Keep `.analysis/f184-menu-input/` containing MenuInputF184.cpp/.hpp, profile,
both full diagnostics/relocated bodies/assembly and compiler log; the native
and attested decompile evidence `.analysis/f184-menu-input.c`, `-ghidra.log`,
`-native-proof.json` and `-native.asm`; `.analysis/f184-compare-menu-input.py`;
and `build/probes/F184MenuInput.obj` with its live PDB companion.

The preview was already running when the user cleared the goal. Its completed
results were collected; no further function reconstruction was started.
Preserve DWORD versus byte clears, independent signed direction checks,
confirm/cancel bytes, Escape counter and actual chord placement. A call-only
source interface does not prove shared original owner identity or full layout.

The old preview seed records a306ad6. The H184 documentation commit changes
HEAD without changing accepted code. Use the post-commit
`.analysis/h184-handoff/resumption-seed.json` for a new working directory;
do not rewrite the old seed or relabel an old object as cold evidence. The
handoff-state, retention, source-checkpoint and commit-receipt files in the same
private directory pin all inputs and the new commit. Verify hashes, register
every field and cold-replay each new unit before updating acceptance ledgers.

## Retained investigations

Preserve 14 frozen prior working objects plus F184: 15 total. The private active
retention receipt records their source/header/profile/object hashes. Also retain
all 14 F157 probes, both F159 traces and 40 protected groups. The old F176
440-byte probe is historical negative evidence; F181 independently accepts the
same native function through a complete 446-byte object.

- Complete 004AC040: F156-derived 151-entry baseline, 83,922-byte comparison,
  18,539 differences/all 2,352 fields. Preserve its baseline object and closed
  F153..F166 scope/profile/member/window/word controls; do not blindly repeat.
- Complete 0050A580: 81,539 CODE / 82,106 comparison bytes; emitted 82,109 with
  26,719 differences/all 1,449 fields. Keep F145CanonicalViews and five older
  retained objects. No credit.
- Complete 0055AC80: 28,862-byte comparison; emitted 28,868 with 8,545
  differences/all 696 fields. Preserve F167 physical-flow source/object and the
  closed lexical-scope control. No native-label rebasing.
- R103 453EB0: native 181, retained emitted 185/111 differences. Earlier `/Op`
  and member/window controls are closed; preserve its object.
- R231 unread camera stores, R065 445A00's write-only local and R054 455B30's
  28-byte clear still lack supported source-purpose explanations. No fabricated
  inert locals, arrays or padding.
- Options 428F00/951 and 429F00/563 require their owned-table review. Battle
  initialization 43AD10/922 is an EH constructor with allocations/incomplete
  owner layouts. These remain unaccepted; no fake owners or pasted EH bytes.

F179 showed that borrowed observed float member windows can change x87 operand
order and argument marshalling without changing types/ABI. F181 showed that
meaningful names in distinct measured buckets can explain actual local slots.
Read the precise archived controls before applying either observation elsewhere.

## History and tools

The complete former documents are preserved **byte-for-byte** in
[handoff through F183](history/RE_HANDOFF_THROUGH_F183.md) and
[knowledge through F183](history/KNOWLEDGE_BASE_THROUGH_F183.md). Original titles,
paths, target strings, observations and unknowns remain intact. Archived goal-
state and next-task commands are historical. Earlier F148 archives and origin
histories are unchanged. Historical relative links were written from docs/;
resolve them there or use the original Git version. Current instructions govern.

**Preserve this workspace when switching agents.** Private sources, objects,
receipts, target and Ghidra project are not in a Git clone. Preserve shared tools
and private service/authentication settings; never print/commit the private URL.
Use scripts/repo-python for every repository Python command. Remain headless:
unset DISPLAY/WAYLAND_DISPLAY and disable Wine graphical drivers per process.
Use the existing attested Ghidra wrapper, serial compiler builds and new/affected
cold replay. Claims.csv stays header-only. Commit subjects remain
`gpt-6.1-sol: ...`; commits and pushes remain authorized.

## H184 cleanup and validation

Wine lowercased PDB filenames, so earlier case-sensitive cleanup missed old
outputs. H184 excludes every frozen path and every live object/executable/DLL
companion **case-insensitively**. It losslessly archived 480 unpaired old PDBs,
verified every full round-trip SHA-256, then removed only those original outputs.
All object files and live PDB companions remain. The local archive is
`.analysis/h184-handoff/retired-orphan-pdbs.tar.gz`; its receipt records original
paths/hashes and restoration details. This step reclaimed 32,225,914 bytes net.

No accepted source, header, ABI, flag, relocation, origin or manifest changed
for this handoff; no cold rebuild was needed. No pause action or new goal was
created. Final checks and cleanup receipts follow.

Final CI passed **3,612 tests in 199.877 seconds**. Target,
tracking/status, current documentation links and diff checks pass. All 493 exact
units/166 canonical objects/268 accepted inputs, all origin evidence through
R268, the 15 retained working objects, all 14 F157 probes/both F159 traces and 40
protected groups were hash-verified unchanged. All 859 remaining build
files were also hash-verified unchanged after cleanup. F184 remains two unaccepted
zero-difference previews; no registration, new compiler build or cold replay ran
after the user's handoff request.

Cleanup retained all 628 object files and
231 live PDB files, replaced 480 unpaired PDB outputs with
a lossless verified archive, and removed 377 reproducible bytecode files
(8,312,399 bytes). Total net reclamation is
**40,538,313 bytes**. The former main documents' 231,263 bytes
are preserved exactly in the new F183 archives; current entry documents are
shortened without discarding their evidence. Private receipts and frozen source
checkpoint are under `.analysis/h184-handoff/`; commit receipt and resumption
seed are finalized after the authorized documentation commit is pushed.
The goal remains cleared, and the 98% objective remains incomplete.
