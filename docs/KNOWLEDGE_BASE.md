# Accepted function evidence

Target SHA-256:
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
Names may remain inferred after exact byte matching; exactness does not recover
original symbol names.

## F001 — shared D3D resource client constructor

Accepted on 2026-10-02. Address `0x00401000..0x0040101A`, complete size 27 bytes.
The following five INT3 alignment bytes at `0x0040101B..0x0040101F` are excluded.

**Target-observed:** The function saves ECX as this, increments the 32-bit global
at `0x00671210`, returns the saved this in EAX, and executes RET. Its paired
cleanup at `0x00401020` decrements the same count. Only when the count reaches
zero does it release shared interfaces through vtable slot `+8` and clear
their global pointers. Four Ghidra xrefs agree with raw instructions: reads and
writes at `0x00401007/0x0040100F` and `0x00401029/0x00401031`.

The resource creation function at `0x00401110` calls Direct3DCreate8 through
the import thunk at `0x0060499A`, using SDK version 220. Associated Japanese
strings report D3D object creation failure and device information failure.
The caller at `0x0040AD80`, call site `0x0040AD9F`, invokes this function before
member construction and EH state advancement. Its cleanup path calls the
paired destructor at `0x0040AFDF`, supporting a base constructor/destructor
interpretation.

**Inferred:** The reconstructed name is
`GraphicsResourceClient::GraphicsResourceClient`; the global is named
`g_GraphicsResourceClientCount`. This is a client-count protocol for shared D3D
resources. Its origin is recorded as authored because the explicit client
count and D3D release policy belong to this custom code family, rather than an
automatically identified CRT helper.

**Unknown:** The original owner name, complete class layout, and original
counter signedness are unrecovered. The partial declaration is used only to
emit this function; it must not be instantiated, embedded, or used to infer
object size.

**Compiler-observed:** Locked VC7.1 `13.10.3077`, with
`/Od /Ob0 /Gy /GR- /GX- /Zi /I src`. The natural implementation increments the
counter in the constructor. This profile reproduces the bounded function;
several flags are indistinguishable in such a small body and are not claims
about the original executable-wide configuration. `/Zi` provides the function
definition auxiliary record used by diagnostic extraction; the probe without
`/Zi` lacked that record.

**Canonical comparison:** Unit `graphics-resource-client-constructor`, COFF
symbol `??0GraphicsResourceClient@@QAE@XZ`, exact at 27/27 bytes. DIR32
relocations at function offsets `+0x8` and `+0x10` both bind to `0x00671210`.
Neither relocation field is excluded, and adjacent padding is not credited.

```bash
scripts/repo-python scripts/replay-exact-units.py --unit graphics-resource-client-constructor
```

The comparison report records source and object digests. Debug metadata can
change the whole-object hash between builds; function bytes must still replay
with zero differences. Private reports live below `.analysis/replay/`; the
command, reviewed extent, and relocation manifest are the durable evidence.

## F002 — shared graphics state and frame pipeline

Accepted on 2026-10-02: 23 new authored functions, 2,960 complete bytes, and
228 relocations. Aggregate cold replay through the no-auth public Funnel
`run_command` accepted 24/24 units across three freshly built objects, including
F001: **2,987 exact bytes**. Private receipts are in `.analysis/replay/` and
`.analysis/public-batch-replay.json`; reproduce them with the commands below.
Names and source partition remain inferred. These custom rendering policies
and shared-state wrappers are classified as authored; called SDK/library
implementations are not included in that authored credit.

| Complete target extent | Bytes | Inferred function |
| --- | ---: | --- |
| `0x00401A00..0x00401A1C` | 29 | `Graphics::ShowError` |
| `0x00401A20..0x00401A4A` | 43 | `Graphics::SetPresentationDestinationRect` |
| `0x00401A50..0x00401A76` | 39 | `Graphics::SetTargetViewport` |
| `0x00401A80..0x00401AAA` | 43 | `Graphics::SetPresentationSourceRect` |
| `0x00401AB0..0x00401AE5` | 54 | `Graphics::SetClearColor` |
| `0x00401AF0..0x00401AFC` | 13 | `Graphics::SetColorMultiplier` |
| `0x00401B00..0x00401B1E` | 31 | `Graphics::SetDrawTransform` |
| `0x00401F00..0x00401F47` | 72 | `Graphics::LoadTexture` |
| `0x00401F50..0x0040213E` | 495 | `Graphics::SetBlendMode` |
| `0x00402140..0x0040224D` | 270 | `Graphics::SetAlphaMode` |
| `0x00402250..0x004023A7` | 344 | `Graphics::SetDepthMode` |
| `0x004023B0..0x00402531` | 386 | `Graphics::SetTextureFilter` |
| `0x00402540..0x004025E0` | 161 | `Graphics::SetTextureStage` |
| `0x004025F0..0x00402655` | 102 | `Graphics::SetPixelShaderMode` |
| `0x00402660..0x00402683` | 36 | `Graphics::BeginFrame` |
| `0x00402690..0x004027C1` | 306 | `Graphics::BeginTarget` |
| `0x004027D0..0x00402893` | 196 | `Graphics::EndFrame` |
| `0x004028A0..0x004028AC` | 13 | `Graphics::SetPresentCallback` |
| `0x004028B0..0x004028B9` | 10 | `Graphics::GetPrimaryTargetTexture` |
| `0x004028C0..0x004028E4` | 37 | `Graphics::GetTargetTexture` |
| `0x004028F0..0x0040296A` | 123 | `Graphics::Present` |
| `0x00402970..0x004029EF` | 128 | `Graphics::PresentToWindow` |
| `0x00403D00..0x00403D1C` | 29 | `Input::ShowError` |

### State, API, and ABI evidence

All F002 functions use stack arguments, caller cleanup, and ordinary RET;
no body saves or consumes an incoming this pointer. The declarations use
cdecl free functions. Signed-byte indices/modes are supported by MOVSX and
signed branches. `BeginTarget` returns its success flag in AL. Boolean gates
are read with MOVZX and tested for zero. The original spelling of types and
names remains unknown.

The pinned Platform SDK supplies actual Win32, Direct3D8, and D3DX8
interfaces. Target vtable slots and argument order agree with those interfaces:
`BeginScene`/`EndScene`, `Clear`, `Present`, `TestCooperativeLevel`,
`SetTextureStageState`, `SetTexture`, `SetPixelShader`, and texture surface
access. `ID3DXRenderToSurface::BeginScene` uses a `D3DVIEWPORT8`, not a RECT.
The object declarations are external references to SDK interfaces; no custom
class layout or whole-program global owner is invented.

The initialization body at `0x00401110` writes viewport X/Y/Width/Height at
`0x00671180..0x0067118C`, then MinZ=0 and MaxZ=1 at `+0x10/+0x14`.
The accepted setter writes only the first four fields. Present passes
`0x00671200` as its source RECT and `0x006711D8` as its destination RECT;
this confirms the two rectangle roles. Globals and their inferred names are
recorded in `config/known-globals.csv`.

Drawing consumers at `0x004029F0`, `0x00402D50`, and `0x00403200` multiply
vertex X/Y by the float at `0x0066C084`, then add `0x00671220/0x00671224`.
They scale RGB channels with x87 FMUL from the float at `0x0066C080`.
Treating that latter setter as a packed color produces the same simple MOV
instructions but would give the wrong contract; consumer evidence establishes
its float role.

The target-texture and render-to-surface arrays each have one live slot,
corroborated by creation/release loops and index guards. Negative target
indices select the back buffer; zero selects the offscreen surface. Begin
uses the original `clearColor & 0x0FFFFFFF` mask; callback compositing uses
`clearColor | 0xFF000000`. The unusual 28-bit mask is preserved. COM HRESULT
checks retain the target's exact equality/sign tests rather than replacing all
checks with SUCCEEDED. The callback's return value is unused; void is an
inferred interface, and original return-type spelling is unrecovered.

`LoadTexture` preserves the fourteen-argument stdcall call at `0x00608666`.
Its declaration is inferred as `D3DXCreateTextureFromFileExA` from the path,
arguments, texture output, and SDK contract; the callee implementation is not
reconstructed or credited here. Device reset at `0x004017A0` was subsequently
accepted in F003 below. Both error wrappers call the MessageBoxA IAT
slot at `0x0065720C`, with independently verified NUL-terminated captions
`DGraphics-Error` at `0x006573EC` and `DInput-Error` at `0x00657488`.

### Compiler observations and complete switch extents

The profile remains `/Od /Ob0 /Gy /GR- /GX- /Zi /I src`, with pinned VC7.1
13.10.3077. The same single source bodies compile into complete exact functions;
no assembly, inert locals, profile-selected bodies, or copied instruction data
are used. `/Zi` supplies complete function-definition auxiliary extents.
Compiler profiles are per-unit reproducibility evidence, not executable-wide
optimization claims.

Ghidra's imported code bodies omitted three immediately following jump tables:

| Function | Instruction bytes | Table range | Entries | Complete bytes |
| --- | ---: | --- | ---: | ---: |
| SetBlendMode | 463 | `0x0040211F..0x0040213E` | 8 | 495 |
| SetDepthMode | 308 | `0x00402384..0x004023A7` | 9 | 344 |
| SetTextureFilter | 370 | `0x00402522..0x00402531` | 4 | 386 |

Each initial computed dispatch indexes exactly this table, all entries land at
reviewed case starts, all case paths converge on the complete return, and
trailing INT3 bytes are alignment. The ledger was extended to include all 84
table bytes. The database remains read-only and retains its imported code-body
metadata; the reconciled ledger is authoritative for comparison.

Both blend and depth switches emit case 1 before case 0. Restoring that source
order matches VC7's case placement. The three filter-state writes are MIN,
MAG, then MIP; mode 3 preserves the legacy FLATCUBIC value 4. Texture-stage
activation uses D3DTOP_ADD (value 7), not a modulation operator.

The canonical comparator checks every relocation's offset, type, and symbol.
For a symbol defined in the same function section, its manifest destination
must also equal `targetFunctionAddress + actualCoffSymbolOffset`; a pinned
address cannot hide a moved internal case label. Three synthetic regression
checks cover valid local bindings, moved labels, and out-of-function labels.
All relocated table entries and dispatch pointers participate in exact replay.

```bash
scripts/repo-python scripts/check-tools.py
scripts/repo-python scripts/replay-exact-units.py
scripts/repo-python scripts/validate-tracking.py --require-target
scripts/repo-python scripts/report-reconstruction-status.py --summary
```

The accepted batch was cold-built and compared through the public MCP client:

```bash
scripts/repo-python scripts/public-mcp-client.py <<'JSON'
{"name":"run_command","arguments":{"command":"scripts/repo-python scripts/replay-exact-units.py","timeout_ms":120000}}
JSON
```

That client resolves the public Funnel ingress, verifies TLS, omits
Authorization, loads the private URL from the ignored local environment, and
keeps it out of process arguments. Public Ghidra queries supplied decompiles,
xrefs, disassembly, and project attestation for this batch.


## F003 — texture allocation and device reset

Accepted on 2026-10-02 after origin batch R001. Three complete functions add
833 exact bytes; all 30 DIR32/REL32 bindings were reviewed and cold replayed.
The source is `src/GraphicsTexture.cpp`; a separate header avoids changing the
accepted graphics-state translation unit's compiler-generated label names.

| Complete extent | Bytes | Inferred function |
| --- | ---: | --- |
| `0x004017A0..0x00401894` | 245 | `Graphics::ResetDevice` |
| `0x00401B20..0x00401C17` | 248 | `Graphics::Create16BitTexture` |
| `0x00401C20..0x00401D73` | 340 | `Graphics::CreateTexture` |

**Target observations:** All three functions use cdecl stack arguments and
ordinary RET. Both allocation functions return bool in AL. Width/height are
zero-extended 16-bit inputs; their rounded dimensions and shift counters are
32-bit unsigned locals. Width's initial comparison uses integer promotion;
height's comparison uses the unsigned working value. Rounding keeps dimensions
zero/one unchanged and rounds larger inputs upward to a power of two. The byte
at `0x0067123A` enables square dimensions. Preserve these choices rather than
introducing validation or factoring the repeated rounding into a new call.

The eight-argument stdcall call at `0x00605B61` agrees with the SDK's
`D3DXCreateTexture`: one mip level, no usage flags, managed pool. The dedicated
helper uses A1R5G5B5; the general helper selects A8R8G8B8 for depths 32/24 and
A1R5G5B5 for depths 8/16, testing 8 before 16. Other depths report an error.
Both helpers require D3D_OK; the creation HRESULT is used by the failure check.
Error literals are separately verified at `0x006573FC`, `0x00657414`, and
`0x0065742C`, even though their Japanese text is identical.

Reset releases the one texture/renderer pair, passes the 52-byte SDK
D3DPRESENT_PARAMETERS at `0x0067119C` to the device's Reset slot, and reports
the verified failure literal at `0x006573D4`. Success invokes the reviewed
custom default-state body at `0x00401540`, then recreates a 1024-by-1024,
one-level A8R8G8B8 default-pool render target and a render-to-surface helper
with a D16 depth buffer. The seven-argument stdcall destination `0x0060508B`
agrees with `D3DXCreateRenderToSurface`. Resource-call results are discarded
where the target discards them; no fake HRESULT locals were introduced.

**Compiler observations:** Pinned VC7.1 build 3077 with the common explicit
Od/Ob0/Gy/GR-/GX-/Zi profile emits each full extent. Meaningful local identifier
variants affect VC7's stack allocation; declaration reordering alone did not
change the observed slots. Names are inferred and carry no original-symbol
claim. The retained allocation locals are used for sizing and error handling;
there is no assembly, inert local, padding, or conditional matching body.

**Verification:** Cold replay of `graphics-create-16-bit-texture`,
`graphics-create-texture`, and `graphics-reset-device` passed 3/3 from one
fresh object. Every relocation is explicitly bound in `match-units.toml`,
including the previously evidenced shared device/arrays/ShowError and the
reviewed default-state dependency. Full instruction decoding, internal branch
destinations, terminal returns and trailing INT3 alignment agree with R001.
The authored origin classification precedes and is independent of exact credit.


## F004 — DirectInput initialization and keyboard polling

Accepted on 2026-10-02 after origin batch R002. Three complete functions add
382 exact bytes, with all 36 relocations independently reviewed and cold
replayed from `src/InputDevice.cpp`. No input container or class layout is
needed by these three functions.

| Complete extent | Bytes | Inferred function |
| --- | ---: | --- |
| `0x00403D20..0x00403D7E` | 95 | `Input::Initialize` |
| `0x00403D80..0x00403E44` | 197 | `Input::CreateKeyboard` |
| `0x00403E50..0x00403EA9` | 90 | `Input::PollKeyboard` |

**Target observations:** All three use ordinary RET and cdecl stack arguments;
setup returns bool in AL. The decompiler's apparent fastcall/thiscall registers
are unused at entry and are not ABI evidence. Initialize assigns the shared
HWND/HINSTANCE before its already-created check, then calls version 0x0800
DirectInput8Create with the SDK's actual IID_IDirectInput8A and output pointer.
The call destination `0x006036A4` is a JMP through IAT `0x00657010`; independent
PE import-descriptor decoding identifies DINPUT8.dll!DirectInput8Create. This
establishes the SDK's five-argument stdcall call independently of a guessed
Ghidra prototype. R002 records the exact GUID and data-format observations.

CreateKeyboard returns early when the keyboard already exists. It creates the
system keyboard, sets c_dfDIKeyboard, then NONEXCLUSIVE | FOREGROUND |
NOWINKEY cooperation, checking each HRESULT for negativity and reporting its
own verified error literal. Acquire's result is discarded. PollKeyboard reads
the entire 256-byte shared state buffer; failure reacquires and zeros it through
the separately evidenced CRT memset body at `0x00640490`. Pointer/global
addresses and every SDK constant/vtable slot are preserved. The source uses
real SDK interfaces and one live HRESULT variable per function.

**Compiler observations and verification:** The explicit pinned VC7.1 common
profile emits exact complete extents on the first source compile; no artificial
locals, owner layouts, assembly, or matching-only body is required. Canonical
cold replay passed `input-initialize`, `input-create-keyboard`, and
`input-poll-keyboard` 3/3 from one fresh object. Every device/state/error/GUID/
format/ShowError/memset relocation is explicit in the manifest. Classify the
called import thunk, SDK data and CRT body independently; these caller matches
do not grant source or exact credit to their callees. Original function/global
names and pointer declaration spellings remain inferred.


## F005 — input lifetime and joystick protocol

Accepted on 2026-10-02 after R002/R003. Six complete authored functions add
1,060 exact bytes. All 84 new relocations are explicitly reviewed in the
manifest, including vendor container calls, callbacks and compiler security
instrumentation. Cold replay passed 6/6 from one freshly rebuilt object.

| Complete extent | Bytes | Inferred function |
| --- | ---: | --- |
| `0x00403B90..0x00403BDB` | 76 | `InputResourceClient::InputResourceClient` |
| `0x00403BE0..0x00403CF5` | 278 | `InputResourceClient::~InputResourceClient` |
| `0x00403EB0..0x00403F3A` | 139 | `Input::InitializeJoysticks` |
| `0x00403F40..0x00404007` | 200 | `Input::PollJoysticks` |
| `0x00404010..0x00404111` | 260 | `Input::EnumerateJoystickDevice` |
| `0x00404120..0x0040418A` | 107 | `Input::ConfigureJoystickAxis` |

**Target behavior and ABI:** The constructor/destructor use thiscall, while
initializer/polling use cdecl. The two callbacks use the real SDK BOOL stdcall
two-argument interfaces and RET 8. Context arguments are unused, but retained
for the SDK ABI. Last-owner destruction unacquires/releases the keyboard,
iterates and releases nonnull controller entries, clears both vendor vectors,
and releases DirectInput. The shared count's signedness is unknown; its
increment/decrement and zero checks do not distinguish signed and unsigned.
The source's count-only class interface establishes neither original name nor
complete object layout; never instantiate or embed that reconstructed owner.

Joystick setup enumerates attached game controllers, truncates vector size to
the observed unsigned byte, zeroes an 80-byte SDK DIJOYSTATE, and uses the real
vendor vector assign(count, value) interface. There is no inferred resize call.
Polling uses a signed loop index against that byte count, reacquires on negative
Poll results, and reads each 80-byte state without inventing extra checks.
Device enumeration appends a null slot, creates the device from instance GUID,
pops on failure, otherwise sets data format, cooperation, capability size and
axis enumeration. The capability output object has only dwSize initialized;
GetCapabilities fills it. Axis enumeration applies object-ID ranges -1000/+1000
and returns STOP for a negative SetProperty result. R002/R003 establish the
SDK data identities and independently reviewed template callees.

**Compiler observations:** `src/InputJoystick.cpp` uses the explicit common
profile plus `/GS`. Without GS, the initializer emitted 123 bytes; GS produces
the complete 139-byte target, including the cookie load at `0x0066FE30` and
check at `0x00640611`. Independent target decoding shows that checker compares
ECX with the same cookie and jumps to its failure path on mismatch. This is
positive compiler-instrumentation evidence, not a fake local or copied bytes.
The checker/cookie remain separate runtime-origin objects without authored
source/exact credit.

The live Poll HRESULT belongs to the outer function scope and its loop index
to the loop. Enumeration keeps its live HRESULT outside the device branch and
DIDEVCAPS inside it. The null slot is expressed as push_back(0): VC7 generates
the observed four-byte temporary for the SDK const-reference parameter. A
named extra device pointer is unnecessary. Identifier variants alone did not
fix these scope/temporary differences. All retained variables serve real API,
loop or failure handling; there are no inert locals, padding, assembly,
artificial class layouts, or conditional matching bodies.

VC7 emits C4530 warnings in instantiated vendor allocation/exception helpers
with GX disabled. Those helper bodies are not being rebuilt into an executable
or credited as authored exact source. Keep the evidenced function profile;
this checkpoint proves complete authored function bytes, not whole-program
exception or linkage behavior. Constructor, destructor, callbacks and polling
match complete extents under the same per-object profile. All exits and trailing
alignment were reviewed in R002/R003; the security check remains in the
initializer's full extent. Names remain inferred.

## F006 — opaque texture copy and untextured drawing

Accepted 2026-10-02 after origin batch R004, from the authored set reviewed in
R001. Three complete functions add 1,548 exact bytes and 48 explicitly reviewed
relocations. Cold replay passed the two drawing units from one new object and
the copy unit from a second new object. Names remain inferred.

| Complete extent | Bytes | Inferred function |
| --- | ---: | --- |
| `0x00401D80..0x00401EF7` | 376 | `Graphics::CopyTextureOpaque` |
| `0x00403400..0x0040361B` | 540 | `Graphics::DrawLine` |
| `0x00403910..0x00403B87` | 632 | `Graphics::DrawFilledRectangle` |

**Copy behavior and ABI:** The cdecl function takes two pointers to SDK texture
pointers and a const RECT pointer. It obtains level-zero surfaces, calls the
device's CopyRects(source, rectangle, 1, destination, null), locks the
destination texture, and obtains its surface description. Full-surface loops
use unsigned width/height counters; rectangle loops use signed RECT/LONG
coordinates. Each visited DWORD is ORed with 0xFF000000. The target computes
the pixel index with surface Width rather than LockRect's Pitch; the source
preserves this observed behavior without adding validation or pitch correction.
HRESULTs are discarded where the target discards them. Unlock and both COM
Release calls remain in order, using real D3D8 interfaces. The natural SDK
locals and scoped loop counters reproduce the full 64-byte stack frame; their
inferred identifiers are not evidence of recovered original symbols.

**Drawing behavior and representation:** Both cdecl functions take a const
RECT and a packed D3DCOLOR. A complete 28-byte local ScreenVertex contains
x/y/z/rhw, diffuse color, and one u/v pair, matching FVF 0x144 and the actual
DrawPrimitiveUP stride. This local vertex record is independently evidenced;
it establishes no unknown resource-owner layout. Line emits two vertices,
z=0/rhw=1, UV (0,0)/(1,1), and a one-primitive LINELIST. Filled rectangle emits
four vertices and a two-primitive TRIANGLEFAN; right/bottom coordinates add the
verified float 1.0 at `0x0065747C`. All vertex fields are initialized before use.

The multiplier condition compares its float's 32-bit representation with
0x3F800000; a floating comparison would emit different instructions. The
source retains the observed representation test under the pinned MSVC x86
profile. D3DCOLOR_ARGB preserves alpha and scales/truncates each RGB channel
through an unsigned-byte conversion. The compiler supplies the three __ftol2
calls per function at the observed runtime destination `0x006406AC`; no helper
ABI or return value is fabricated. Vertex X/Y then use the previously evidenced
global scale and origin. Line temporarily sets D3DTSS_ALPHAOP to
D3DTOP_SELECTARG2 and restores MODULATE, rather than changing texture filtering.
Both functions clear a nonnull cached texture before untextured drawing and set
the SDK vertex shader/FVF. The textured-quad caller compares and stores the
same texture pointer at `0x00671228`, independently confirming that cache role.

**Complete comparison:** The common explicit VC7.1 profile is
`/Od /Ob0 /Gy /GR- /GX- /Zi /I src`. There are 2 copy, 23 line and 23 filled
rectangle relocations. Shared globals, the compiler conversion helper and the
1.0 constant were individually checked before canonical binding; none of
their four-byte fields is omitted from acceptance. R001 and fresh decoding
confirm internal direct branches, final returns and excluded trailing INT3
alignment, without switches or shared tails. There is one natural source body
per function, with no padding, assembly, inert locals, or conditional layouts.
Full cold replay through the no-auth public Bash MCP subsequently passed
39/39 units across eight fresh objects, including all 428 relocations and
6,810 accepted bytes. The private receipt is `.analysis/public-f006-replay.json`.

```bash
scripts/repo-python scripts/replay-exact-units.py --unit graphics-copy-texture-opaque --unit graphics-draw-line --unit graphics-draw-filled-rectangle
```

The reviewed authored slice is now 6,810/12,343 bytes exact (55.17%). Its
denominator remains provisional: 4,189 origins are still pending, so the
all-origins/50%-authored-byte goal remains incomplete.

## F007 — rectangle outline and textured drawing

Accepted 2026-10-02 after origin batch R005. Three complete authored functions
add 2,106 exact bytes and 69 explicitly reviewed relocations. The outline
cold-replayed with both existing untextured drawing functions after the shared
vertex record moved into `GraphicsVertex.hpp`. Both textured functions then
passed cold replay from a new independent object. Names remain inferred.

| Complete extent | Bytes | Inferred function | Relocations |
| --- | ---: | --- | ---: |
| `0x00403620..0x00403905` | 742 | `Graphics::DrawRectangleOutline` | 23 |
| `0x004029F0..0x00402D48` | 857 | `Graphics::DrawTexturedQuad` | 25 |
| `0x00403200..0x004033FA` | 507 | `Graphics::DrawProjectedTriangleStrip` | 21 |

**Outline:** Four initialized ScreenVertex records describe the RECT corners,
with z=0, rhw=1 and the corresponding unit UV corners. Assignment of the first
record to the fifth closes the strip; the compiler emits a seven-DWORD copy.
The signed loop condition is `index <= 4`, matching CMP 4/JG rather than the
decompiler's normalized `< 5`. The function applies the shared color and
scale/origin policies, selects alpha argument 2, clears the cached texture,
sets FVF 0x144, draws four LINESTRIP primitives and restores alpha modulation.
The right/bottom coordinates have no filled-rectangle +1 adjustment.

**Textured quad input evidence:** Twenty-five target callers include the
attested wrappers at `0x0040C9A0`, `0x0040CA80`, `0x0040CEF0` and `0x0040D2E0`.
They copy 132-byte coordinate owners and rotate or mirror their first four
16-byte records. The geometry builder at `0x0040DA00` fills those records in
top-left, top-right, bottom-right, bottom-left order through `0x0040DB10`.
Those observations prove the accessed coordinate stride and order; they do
not establish the complete 132-byte class. The source takes a const view of
four-float coordinate records and never instantiates that unknown owner.
The complete output/input ScreenVertex record remains 28 bytes, as established
by the actual field accesses, FVF and DrawPrimitiveUP stride.

The quad obtains a level-zero surface, reads the real D3DSURFACE_DESC, converts
unsigned Width/Height to float, and releases the surface before drawing.
Output position order is 0, 1, 3, 2. X/Y subtract the verified float 0.5;
z=0.5 and rhw=1. UV values use the signed RECT coordinates divided by the
texture dimensions. All four vertices then receive the global scale/origin
transform and the same packed color. A changed texture is bound and cached,
and two TRIANGLESTRIP primitives are drawn. The target does not set FVF here.
HRESULTs are discarded where observed.

The source limits dimension/description locals to vertex assembly and the
surface pointer to its acquire/query/release operation. These meaningful
lifetimes reproduce the target's 200-byte frame and local positions without
padding or inert variables. The scopes and identifiers are inferred source
choices, not recovered original debug symbols.

**Projected strip:** The cdecl arguments are a mutable ScreenVertex pointer,
a signed vertex count and an SDK texture pointer. Each vertex receives the
scale/origin transform, followed by
`projection = 3000.0f / (3000.0f - z)`, `rhw = projection` and
`z = 1.0f - projection / 2.0f`. Actual PE bytes independently establish the
constants at `0x00657484` (3000), `0x00657480` (2) and `0x0065747C` (1).
The multiplier condition scales RGB while retaining alpha, using the same
unsigned-byte conversions and three compiler __ftol2 calls as F006. The
function mutates the supplied vertices, binds/caches a changed texture and
draws `count - 2` TRIANGLESTRIP primitives. It adds no input validation or FVF
change. The real projection temporary is consumed by both rhw and z writes.

**Acceptance:** The explicit profile is `/Od /Ob0 /Gy /GR- /GX- /Zi /I src`.
The full ranges decode through their final RET with direct internal branches,
no switch table or external tail, and excluded trailing INT3 padding. Shared
globals, __ftol2 and all four real constants were checked before canonical
binding. All relocation fields are included in exact comparison. Each function
has one natural C++ body, with real D3D8 interfaces and no assembly, arbitrary
padding, inert locals or conditional matching implementation.

```bash
scripts/repo-python scripts/replay-exact-units.py --unit graphics-draw-rectangle-outline --unit graphics-draw-textured-quad --unit graphics-draw-projected-triangle-strip
```

Private full instruction/caller evidence and cold receipts are under
`.analysis/f007-*` and `.analysis/textured-quad-*`. The reviewed authored slice
is 8,916/12,343 bytes exact (72.24%). Its denominator is provisional; 4,164
origins remain pending and the full goal is incomplete.

Full cold replay through the existing no-auth public Bash MCP subsequently
passed 42/42 units across nine freshly compiled objects: all 8,916 bytes and
497 relocation fields matched. The private RPC result is
`.analysis/public-f007-replay.json`; the retained build/comparison receipt is
`.analysis/f007-public-cold-receipt.json`.
## Origin-only observations after R014

R012/R013 establish vendor ownership of 38 more SDK bodies through complete
function and readonly-section evidence; see `ORIGIN_REVIEW.md`. This adds
no source or exact credit. Whole readonly sections anchor named data definitions
and their offsets; mutable globals and relocated dispatch tables remain unresolved.

R014 establishes authored policy in twelve texture-manager functions. The
bitmap palette loader converts 256 entries from file offset 54 into 16-bit
A1R5G5B5 and clears the first entry's alpha bit. Its valid-BMP-branch cleanup
and observed header checks must be retained when reconstruction resumes.
Do not silently fix the target's file/error behavior during byte reconstruction.

The texture resolver's first-use guard initializes the cached handle to the
incoming argument. The special metadata flag then selects texture zero and
uploads only on a cache mismatch. Do not replace this with an imagined
always-upload initialization. Metadata has observed 44-byte container stride;
its complete record and owner layout remain unknown. A real DIDEVCAPS-sized
vendor probe investigates generic vector policy only and provides no evidence
that the target record uses that SDK type. The converter at `0x0041B990`
and container operations remain separately reviewable.

## Origin-only observations after R017

R015/R016/R017 add 42 custom audio/input/texture lifetime bodies and no exact
credit. The sound bank uses its own serialized count/presence/length/18-byte
wave-format/sample layout. Held input has signed directional durations and
five button counts, with joystick thresholds -500 and 500. BGM streaming has
separate load/refill flags, the observed ring-buffer/EOF policies, volume/fade
transitions and a dedicated `wave\bgm\59.wav` loop-point exception. These
behaviors identify useful core candidates after the complete origin review.

The physical worker extent includes its unreachable epilogue. Preserve the
original first-use/cache, queue/thread/resource order and arithmetic rather
than introducing intended behavior. Texture-slot initializers have different
observed format conditions at `0x0040B000/0x0040B110`; their equivalence is not
established. Complete owners, original names and some call ABIs remain unknown.

The stream queue's pop/push/clear policy is consistent with pinned VC7 deque
source and a fresh 64-byte D3DMATRIX probe. Those generic helpers remain
pending until full bindings and alias context are independently verified.
The probe does not identify the application's stream record as D3DMATRIX.
`verify-authored-origins.py` rechecks the 70 recorded manual-review bodies,
their target hashes and full internal CFG; it does not infer ownership from
machine similarity or create source/exact credit.

## Origin-only observations after R021

R019/R021 add 21 custom texture-pack, bitmap/RLE/upload and selected-record
bodies (11,813 bytes). Directory loading uses `%s\\%04d.bmp`; palette selection
and pack records retain signed-byte count/index arithmetic and the observed
width/height/stride/format/compressed-length order. Preserve the repeated height
comparison in shared-texture selection instead of inventing symmetry.

The bitmap loader stores four bytes per 24-bit logical pixel, converts indexed
palettes to A1R5G5B5 and retains observed transparency/error cleanup. RLE encode
and upload use format-specific run counts, row continuation and raw-copy rules,
including the raw 16-bit width>>1 copy. Four complete guarded remap switches
are verified with all case/default targets and 168 bytes of external tables;
those data bytes grant no additional authored or exact credit.

R020 excludes 303 compiler-generated cleanup bodies (3,174 bytes). Independent
VC7 fixtures establish compatible handler/FunctionInfo and placement-cleanup
emission. Actual metadata binds each body to registered parent frames; all
208 complete state maps and body operand patterns are verified. This establishes
compiler ownership of dispatch bodies only. Parent/callee ownership, original
source types and whole parent boundaries remain separate questions.

The origin verifiers now cover 91 manually reviewed authored bodies / 30,688
bytes and the 303 compiler cleanup bodies. They add no reconstruction credit.
Original names, ABI and complete bitmap/texture/progress owner layouts remain
unknown. The three scalar deleting-destructor candidates and 0x0041BF90
initializer still need independent review. Exact work remains deferred until
all candidate origins have been reviewed.

R022 adds the independently bounded 31-byte libcmt `__EH_prolog` and 59 pure
cleanup bodies (580 bytes). Twenty-eight more parent frames register through
MOV EAX, handler / CALL prolog, rather than the inline PUSH/FS:[0] prefix.
Registration is accepted only after whole vendor-helper verification. All 236
frames and 362 recorded cleanup bodies are now rechecked. Thirty-nine positive
argument-slot cleanup forms remain pending; do not generalize negative-frame
acceptance or blanket-classify referenced parents/callees.

R023 resolves the 39 positive-slot cleanup bodies (390 bytes) using a fresh
ordinary optimized std::string-allocation fixture. Its compiler naturally
reuses an argument slot and emits two independently bounded ten-byte dispatch
funclets. The target's complete metadata and observed allocation/state stores
establish the analogous frame role, while source types, parent/callee ownership
and whole parent boundaries remain unknown. All 401 recorded cleanup bodies
and 236 complete frames are now rechecked. Exact source and units are unchanged.

## Origin-only observations after R024

Eleven functions in the executable's startup pointer table are generated
global initializers. Ten register separate finalizers; every pair uses the
same observed global address. One init-only wrapper has no registered
finalizer. A fresh VC7 C++ global-lifetime fixture emits the same complete
wrapper structures and relocation roles. The target's array uses two
72-byte elements; the fixture's string array uses two 28-byte elements.
Neither global type is inferred from the wrapper pattern alone.

The full startup runner, table interval, callback pairing, per-body hashes and
all code fields are rechecked by `verify-static-origins.py`. Its `_atexit`
destination has its own pinned CRT whole-body fingerprint; other callees and
global owner layouts remain separately pending. R024 adds 21 compiler-origin
exclusions / 468 bytes and no authored source or exact credit.

## Origin-only observations after R025

Two complete 829-byte CRT memory-copy bodies match their pinned vendor COFF
members after all 46 member-local pointer/table relocations per body are
resolved. The source members for `_memcpy` and `_memmove` emit identical bytes,
so source alias choice is not proved by the binary match. The 104-byte local
unwind helper similarly matches its vendor member and has a checked 34-byte
preceding handler dependency. The 119-byte floating-point conversion body
now binds both calls to separately verified CRT bodies. All four remain
library-origin exclusions, with no authored source or exact credit.

## Origin-only observations after R027

Thirty-one short D3DX8 functions have complete, relocation-free vendor COMDAT
matches and individually checked typed caller references. The caller bodies
supply symbol/alias context; their own origins remain separate. This added
JPEG, PNG, file/resource/image and stack anchors that the earlier size-filtered
diagnostic missed. Fifteen further JPEG/zlib bodies then passed whole-function
comparison with all 34 direct calls bound to independently verified SDK
functions. Indirect calls in those bodies grant no ownership to their targets.
These batches add no authored source or exact credit.

## Origin-only observations after R028

Three JPEG decoder COMDATs store seven function entrypoints through DIR32
relocations. All seven source symbols and zero addends match independently
verified complete SDK callees at the actual linked addresses. The progressive
decoder also makes two independently bound direct calls. A stored function
pointer establishes the initializer's vendor origin but says nothing about
which later indirect calls execute or who owns a caller. The verifier records
pointer fields separately from scalar and readonly data. All three bodies
remain library-origin exclusions with no authored source or exact credit.

## Origin-only observations after R029

Ten PNG/JPEG/zlib SDK bodies now have complete origin evidence. Their data
references use complete relocation-free readonly sections, a proven scalar,
verified function entrypoints, and exact source addends. A +256 relocation
may identify a position inside a section or its endpoint; the full-section
bound is checked before accepting it. The endpoint records pointer provenance
only, not an accessible element. A JPEG quantizer became eligible only after
its direct callee had a separately verified complete SDK origin. Indirect
calls and other callers remain independently unclassified; none of these ten
bodies gains authored source or exact reconstruction credit.

## Origin-only observations after R030

The pinned executable's PE import descriptors independently identify 157 IAT
slots. Three six-byte `FF 25` entries jump through actual slots for DirectInput,
Direct3D8 and RtlUnwind. They are linker trampolines, separate from the DLL
implementations and from functions that call them. Other indirect jumps of
the same instruction shape address non-import data and remain under review.

## Origin-only observations after R031

Eight complete VC7 `std::_Uninit_fill_n`/`std::_Uninit_copy` template bodies
were split into 32 provisional inventory rows by local catch jumps and
adjustments. Fresh ordinary `std::vector` instantiations with synthetic
16-, 44- and 116-byte aggregates reproduce the complete emission outside
explicitly resolved EH and call relocation fields. The aggregate widths are
observed code strides, not proof of the original target record types. Every
body's full source auxiliary extent, target bytes and internal control flow
are checked; the interior rows cannot become independent authored functions.

## Origin-only observations after R032

The fresh VC7 record probe also produces 129 complete STL helpers whose
target bodies have one unambiguous generic template family after ignoring
synthetic record-name aliases. Their 398 typed code relocations and complete
control flow are checked. Some helpers encode a record width; others emit
the same bytes for 16-, 44- and 116-byte aggregates, so no original target
type or owner layout follows. Eight byte-identical `copy`/`copy_backward`
cases remain pending because the probe alone cannot select their family.

## Origin-only observations after R033

Twenty-three short STL helper bodies have complete source matches and a
separately checked typed call in a complete vendor caller. Three more
byte-identical `copy`/`copy_backward` candidates resolve specifically to
`copy` because complete `erase` callers name that symbol at their actual
REL32 fields. Five dual-family candidates remain unresolved. Typed caller
evidence disambiguates the source family, not the original record type, and
neither caller nor callee gains authored source or exact credit.

## Origin-only observations after R034

An independent VC7 `std::vector` probe across fourteen synthetic aggregate
widths supplies 31 more complete generic STL helper matches. Only widths
4, 8, 20 and 64 contribute accepted bodies, with all 26 direct-call fields
bound and six unambiguous template families. These widths are compiler-oracle
inputs, not recovered game record declarations. Five byte-identical
`copy`/`copy_backward` matches still lack family-level evidence and remain
pending. No source or exact credit changes.

## Origin-only observations after R035

Twenty additional bodies have full target-byte hashes, complete decoded
local control flow and independent game-specific behavior. Four routines
operate on the project's four-vertex sprite geometry; scene-node routines
compose those transforms with sprite color, texture and camera state. Camera
functions clamp and ease shared coordinates, including explicit override and
shake setters. Replay functions use the game's temporary replay path, packed
header, variable-width record arrays and numbered output slots. A window
initializer loads the game's window texture pack. A
large scene renderer selects sprite IDs and fades by fixed time intervals.
`docs/ORIGIN_REVIEW.md` records observations per entry. The inferred names
are aids for navigation; original class identities are still unknown. No
source or exact credit follows from the classification.

## Origin-only observations after R036

The opening-scene initializer explicitly loads `data\\system\\opening.dat`
and stores a `timeGetTime` baseline. The corresponding scene advance routine
uses elapsed time and skip flags, while the R035 renderer contains the timed
sprite/fade schedule. `OpeningScene` is an inferred owner name supported by
that context; each function's origin remains based on its own behavior and
complete bytes. Sprite-node reset and camera-relative render functions also
have local custom field and drawing policy. No source or exact credit changes.

## Origin-only observations after R037

VC7.1 emits a 44-byte scalar deleting destructor with one call to the owning
class destructor and a low-bit-controlled call to `operator delete`. A fresh
synthetic virtual-destructor fixture emits the whole function and its two
typed relocations; 80 remaining target bodies match this entire generated
form with individually bound destinations. The compiler owns each wrapper,
while the called destructor and deallocator retain separate origin decisions.
No authored source or exact credit changes.

## Origin-only observations after R038

The same synthetic virtual-destructor fixture emits a complete 28-byte
scalar deleting destructor under VC7.1 `/O1`. Its two relocated calls and
low-bit deletion policy match 53 additional whole target bodies, including
the CRT-linked `type_info` wrapper. This supports compiler origin for each
wrapper only; it does not assign origin to any called destructor or to the
deallocator and does not prove the target's executable-wide optimization
settings. No authored source or exact credit changes.

## Origin-only observations after R039

The pinned D3DX8 archive defines 39 linked five-byte destructor forwarders
whose complete target bodies and typed jump destinations agree. Thirty-seven
belong to codec alias families and two to the lock wrappers. Whole codec
destination-body fingerprints and four-pointer readonly vtables corroborate
the library symbol grouping, but unresolved external callee dependencies
leave those destination functions pending. Alias multiplicity does not reveal
which target entry belonged to which original codec subclass. No authored
source or exact credit changes.

## Origin-only observations after R040

The music-room list, text-resource builders and selection update share a
track count and ten-row scrolling policy. The two name-entry paths share the
0x5b/0x5c keyboard commands but store characters in different record fields;
their rendering and input routines are independently reviewed. Replay browsing
enumerates `.rep` files and reads metadata before displaying ten entries at a
time. Result panels format selected progress counters. The battle renderer and
HUD use paired player/character fields and fixed sprite geometry. These are
useful clusters for later exact-work prioritization, but inferred names and
class boundaries remain provisional. The 23 complete R040 bodies grant origin
only; they provide no source or exact credit.

## Origin-only observations after R041

Character-selection initialization directly loads three `select*.dat` packs
and resets paired player state. Its input and animation functions use shared
per-player offsets but have distinct transitions and rendering. The title
initializer directly loads `title.dat`, and the battle initializer loads
`battle.dat`; these file references give strong scene context to neighboring
render/update bodies. The battle loop updates both players, handles knockout
and transition state, then renders the camera-adjusted fight and HUD. The
card-list loader and encoder share an evolving XOR stream with separate text
and binary paths. All 21 R041 bodies are origin-only observations with
inferred names; they add no source or exact credit.

## Origin-only observations after R042

The battle loop's collision path gathers separate player hitboxes, transforms
their rectangles, tests attack/body contact and updates health, movement,
combo and impact state. The same region contains explicit pause-menu handling,
debug-key actions and a fixed-frame overlay schedule. A battle HUD initializer
builds multiple digit atlases; its number renderer reads those exact arrays.
Fifteen large effect renderers use project sprite/particle APIs, randomized
offsets, distinct atlas slots and timer-driven geometry. Their neutral
`RenderPattern` labels do not claim original effect names. All 32 R042 bodies
have independent full-body and local CFG evidence for authored origin only;
no source or exact credit follows.

## Origin-only observations after R043

The result page uses the same selected progress/card records as its text
builders, plus a custom eight-glyph, 26-column name atlas. Eleven complete
transition callbacks implement distinct fade, color, rotation, slide and
scale schedules dispatched by the previously reviewed mode routine. The
character-selection scene has paired input records and custom card sprites.
The staff-roll initializer explicitly loads `staffroll.dat`, while its
renderer uses fixed millisecond windows and its advance routine handles skip
transitions. Five small progress-record accessors use game-specific nested
offsets and are independently observed as complete bodies. Tiny wrappers,
empty methods and unresolved jump-table extents remain pending. The 37 R043
decisions grant authored origin only, with no source or exact credit.

## Origin-only observations after R044

The character-select, title and battle advance routines use direct indexed
jump tables with nine, ten and fifteen entries, respectively. Each selector
has an immediately preceding unsigned bound check on the same stack slot.
The tables' complete bytes and all in-body case destinations are now checked
as part of cold origin replay. These central dispatchers connect many of the
already reviewed scene helpers and identify useful candidates for later exact
prioritization. Their class labels are inferred; the three R044 decisions
grant authored origin only, with no source or exact credit.

## Origin-only observations after R045

The battle collision layer and fighter object form a useful later exact-work
cluster. Paired fighter records share side, current pattern, input, animation,
health/gauge and recovery fields. The resource loader names character-specific
sound, `.dat`, `.pat` and numbered stage files, which grounds the nearby
state and drawing routines. The effect manager creates project-specific
records and advances them through virtual callbacks. The 27 reviewed bodies
are complete and hashed, but inferred names and class layouts remain
provisional. They add no source or exact credit.

## Origin-only observations after R046

Reimu's derived fighter initializer writes the literal `reimu` and installs a
character-specific vtable. Her action dispatcher is a single complete
14,141-byte function with 749 direct local branches; it repeatedly chooses
pattern IDs through the project's lookup and transition calls. This is a
potentially central but expensive exact-reconstruction candidate after the
origin-review gate. The five R046 decisions add no source or exact credit.

## Origin-only observations after R047

Ten complete character action dispatchers and 21 complete AI-choice bodies
share game-specific call patterns while encoding many per-character action
IDs and decisions. They add 304,135 bytes to the provisional authored slice,
so later exact-work prioritization must account for these large bodies and
their dependencies. Address-qualified names avoid inventing character
ownership from proximity. Larger neighboring bodies with indirect jumps
still require separate control-flow evidence. The R047 decisions add no
source or exact credit.

## Origin-only observations after R048

Thirty-one more character-specific functions are exceptionally large:
object behavior, timed sequences and fighter move handling total over 1.15 MB.
They use bounded direct and byte-remapped jump tables; all 90 complete tables
and in-body destinations are now replayed from the pinned executable. The
three family labels describe observed data flow, not original class names.
These bodies dominate the provisional authored-byte denominator, so eventual
exact-work planning must consider their size and the common helpers they call.
R048 grants origin only, with no source or exact credit.

## Origin-only observations after R049

Medium character functions contain eleven repeated update/render pairs for
special actions. The update side switches among ten action states; the
render side uses a bounded byte remap. Other complete character helpers
parse explicit fighting-game command patterns, spawn effects and draw
character-specific geometry. Their complete extents and 22 jump tables are
replayed, while adjacent tiny forwarders remain pending. R049 adds origin
only, with no source or exact credit.

## Origin-only observations after R050

Ten derived fighter constructors store literal character keys and distinct
vtables; paired factories call character-specific owned-object initializers,
which in turn call the same project base initializer. The eleven-character
mapping now has direct target evidence rather than address proximity alone.
Small special-variant selectors use ten-case guarded tables; round-reset
bodies call the common fighter reset. These 52 reviewed bodies grant origin
only; names and complete layouts remain inferred, with no source or exact
credit.

## Origin-only observations after R051

Four complete VC7 STL source COMDATs with no relocations recur as 25
byte-identical target candidates: iterator advance, allocator maximum size,
`fill` and `fill_n`. A cold compile, complete source extent, target hash and
local CFG now support their library origin. The same code may arise from
different template arguments, so names remain generic; shorter coincident
bodies were not classified. R051 adds no authored or exact credit.

## Origin-only observations after R052

The early game-code cluster contains a custom data-archive index reader and
writer, config-file read/write pair, text rasterizer with inline color and
newline commands, progress defaults, battle-state snapshots, and scene
initializers. These direct behaviors establish game authorship independently
of neighboring VC7 container functions. Three replay-number drawing bodies
are identical whole functions at separate addresses; call-site-specific
names remain provisional. The archive entry format and full progress owner
layout remain unresolved. R052 adds no source or exact credit.

## Origin-only observations after R053

The score file has two observed read layouts selected by file size; the
writer emits the newer field order. A ranking insertion shifts ten 16-byte
records and stamps a date. A glyph helper calls `GetGlyphOutlineA` twice,
first to get the bitmap size and then to fill an allocated buffer. Archive
catalog lifetime and named-entry seeking are custom game code, while the
adjacent iterator/container helpers remain separately pending. Scene setup
uses literal `load.dat` and `logo.dat` asset paths. R053 adds no source or
exact credit.

## Origin-only observations after R054

Several battle-layer draw helpers are complete and directly call the
project sprite renderer with literal geometry. They repeat whole bodies at
different addresses, but that repetition does not imply ownership of
neighbors. The two scene cleanup bodies release distinct owned resources;
class names remain unresolved. R054 adds no source or exact credit.

## Origin-only observations after R055/R056

The background family has 34 asset-loading constructors with explicit
BG00–BG09 file paths, 18 paired side-sprite drawers, and 32 complete
transform/copy routines. The constructors' full target bodies, literal
paths and direct calls are independently replayed. The transform routines
share every non-call byte and the same two checked game call targets.
Tiny adjacent empty methods and destructor wrappers remain pending because
proximity cannot establish authored versus generated origin. These batches
add no source or exact credit.
