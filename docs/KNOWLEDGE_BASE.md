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

## Origin-only observations after R057

A pinned VC7.1 probe differentiates an explicitly defined empty derived
virtual destructor from an implicit one: the explicit form writes its
derived vtable before calling the base destructor (28 bytes), while the
implicit form only calls the base destructor (19 bytes). Thirty-four
background destructor bodies match the explicit complete source shape and
bind to the exact vtables of the separately reviewed BG asset constructors.
The base destructor, two further larger-background pairs and adjacent
empty virtual methods remain pending. R057 adds no reconstruction source
or exact credit.

## Origin-only observations after R058

Eighty-six identical 11-byte no-op functions are independently present in
slots 1–3 of verified background-class vtables. A cold VC7.1 source probe
emits the exact complete body for an empty virtual member. The vtable
slot/constructor relationship supplies ownership evidence that the short
body alone cannot provide. Three similar methods in unreviewed BG05b/BG08a
classes remain pending. R058 adds no reconstruction source or exact credit.

## Origin-only observations after R059

The larger BG05b and BG08a constructors use the same asset/base pattern
as the smaller background classes while initializing extra per-scene fields.
Their vtables independently bind two explicit-source-shaped destructors
and three source-shaped no-op members. The checked background cohort now
contains 36 asset constructors, 36 matching destructors, 89 no-op virtual
members and 18 side-pair drawers. R059 adds no reconstruction source or
exact credit.

## Origin-only observations after R060

The eleven playable-character fighter constructors each write a distinct
vtable. Every checked vtable has a virtual method that forwards directly
to the reviewed base action routine, plus an empty method at slot 18.
Ten have a second empty method at slot 9; Marisa has a previously reviewed
nonempty override there. A cold VC7.1 source probe reproduces the complete
forward and empty-method shapes. Vtable binding supplies project ownership
for these otherwise tiny and repetitive methods. Original names and complete
class layouts remain unknown. R060 adds no reconstruction source or exact
credit.

## Origin-only observations after R061

Ten character-adjacent 19-byte methods exactly follow the compiler's
implicit derived-destructor shape: they only call the reviewed shared
fighter cleanup. Their separately verified scalar deleting wrappers call
them. This supports compiler ownership for those ten specific methods;
nearby destructors with different shapes remain separate candidates.
R061 adds no reconstruction source or exact credit.

## Origin-only observations after R062

Staff Roll and Title scene constructors write distinct vtables that their
destructors restore while releasing a member and the common game-global
owner. The Title destructor additionally publishes a selected byte to
global state. A separate small Battle scene hook calls the accepted
graphics-present routine. These relationships establish ownership for four
specific bodies; short adjacent callbacks remain pending. R062 adds no
reconstruction source or exact credit.

## Origin-only observations after R063

Reimu's constructor-written fighter vtable points at a 60,999-byte action
dispatcher in slot 1. Its single code extent contains six guarded switches
whose complete readonly tables and remaps sit after the final RET. Every
recorded case points inside that extent. It handles many numeric action
states and repeatedly calls game movement and attack helpers. All eleven
fighter constructors point to distinct authored action bodies in this
slot, totaling 613,391 bytes. The specific source method name and full
fighter layout remain unknown. R063 adds no
reconstruction source or exact credit.

## Origin-only observations after R064

A character-adjacent auxiliary constructor writes a vtable whose action
slot points to a 31,352-byte state dispatcher. Meiling's independently
verified fighter vtable points to a separate 12,400-byte special-state
dispatcher. Both have complete guarded switch tables after their final
RETs and game-specific state updates. Their original names and the
auxiliary object's exact role remain unresolved. R064 adds no source or
exact credit.

## Origin-only observations after R065

Battle resource loading uses explicit `LoadCharacter...` and
`LoadStage...` diagnostic markers and replaces owned game objects based
on current selection state. Six other reviewed routines draw or advance
scene, battle and fighter state. Their ten complete guarded tables cover
75 entries, all inside their owning code extents. Detailed layouts and
original method names remain unresolved. R065 adds no reconstruction
source or exact credit.

## Origin-only observations after R066

The music-room catalog loader reads `musicroom.dat` from the game archive,
decodes bytes and parses records. Options changes call the game sound
routine, while a progress decision polls a game flag helper. Five guarded
tables cover 28 in-function cases across these four bodies. Nearby repeated
vector routines still need a cold VC7 source/binding witness. R066 adds
no reconstruction source or exact credit.

## Origin-only observations after R067

The effect-pattern catalog loader reads `data\system\effect\effect.pat`
through the archive opener. Two auxiliary spawn routines call the previously
reviewed auxiliary object constructor. Suika and Yukari each place a
character-specific update body in fighter vtable slot 19. A separate
projectile routine advances action and position state. The six complete
bodies add no source or exact credit. Nearby repeated container helpers
remain pending vendor-source verification.

## Origin-only observations after R068

All eleven reviewed playable-fighter vtables use the same slot-0 animation
binding method. Alice's slot-19 method updates a character-specific timer
from relative opponent position. Those two complete bodies close the
remaining pending entries within the inspected 23-slot range of the
eleven playable-fighter vtables. R068 adds no source or exact credit.

## Origin-only observations after R069

A combat selector chooses a hit response from fighter/opponent state and
game options. Its caller applies damage and effects. Their guarded switches
use one complete 31-byte action remap with nine destinations and one direct
four-entry table. Both code bodies and the direct call edge are verified.
R069 adds no source or exact credit.

## Origin-only observations after R070

The fighter resource loader builds a `data\\character\\%s\\%s.sce` path
and selects file or archive loading. Both paths call one parser. Its complete
target body has a guarded 100-byte remap and seven-entry table after the
final RET; all destinations stay inside the owning body. The archive path
applies the observed decode loop before parsing. R070 adds no source or
exact credit.

## VC7 deque map-growth origin after R071

Twelve complete target bodies, 6,210 bytes in total, reproduce VC7.1
`std::deque::_Growmap` emission from independently varied record-width
instantiations. Their full code COMDAT extents, 13 typed relocations per
body and decoded control flow are checked by a cold verifier. Widths of at
least 16 share the same 511-byte emitted shape in this probe; the original
game element types and called-function origins remain unknown. These twelve
are library templates with no authored source or exact credit. The prior
vector hypothesis for them was incorrect.

## VC7 deque operations after R072

Forty-six complete target functions reproduce five VC7 deque methods:
`_Tidy`, `pop_back`, `pop_front`, `push_back` and `push_front`. All 143
typed relocation fields are bound to observed targets; the rest of each
151–226-byte body matches an independently compiled whole COMDAT. These
are library-template origins. Synthetic record widths only test code
generation; original record types and callee ownership remain unknown.

## VC7 deque constructor and helper origins after R073

Ninety-seven complete target bodies reproduce six VC7 deque-related
constructor and STL helper families, with 190 typed relocations and
complete decoded control flow. The source probe spans multiple synthetic
record widths; identical emissions do not identify an original game type.
These are library origins only, with no reconstruction source or exact
credit. A no-relocation 44-byte allocator match remains pending.

## Parent-backed VC7 deque callees after R074

One hundred twenty-six short VC7 deque/allocator helper bodies have two
independent witnesses: a complete cold source/target comparison with one
typed relocation each, and a direct same-family call from a previously
reviewed deque template. The parent body hash and raw call displacement are
rechecked, as are all parent cold verifiers. These library classifications
do not confer origin on the functions they call or identify original game
element types. Short matches lacking a corroborating parent remain pending.

## Parent-backed VC7 allocations after R075

Twenty-two short `std::_Allocate` bodies match complete VC7 source
definitions and are called by reviewed allocator wrappers through
same-family typed calls. The source/target bindings and reviewed parent
chain are cold-reverified. These are library origins only; allocated game
types and the final allocation routine's origin are unresolved.

## Fighter script owner after R076

The script initializer sets 1,000 16-bit slots to `0xFFFF` after calling
a VC7 deque constructor and destructor at owner offset `0x7D0`. The purpose
of that sequence is unresolved. Three field accessors use a
16-bit slot mapping and the same lookup pair, then return 1-, 2- and
4-byte fields at offsets 0, 2 and 4. Reviewed fighter routines call the
initializer and all three accessors. This supports one game-authored script
owner but does not establish its full layout or original method names.
The adjacent cleanup body remains unclassified pending an implicit
destructor analysis. R076 adds no source or exact credit.

## VC7 deque destructor bindings after R077

Twenty-four complete 19-byte VC7 deque destructor bodies call `_Tidy`
functions independently verified in R072. The cold source probe, complete
target bodies, typed call destinations and callee hashes are reproducible.
Other same-shape destructor-like bodies call unrelated or unknown functions
and remain pending. R077 adds library origin only, with no reconstruction
source or exact credit.

## VC7 deque access after R078

Seven `std::deque::at` bodies, sixteen iterator additions and ten
const-iterator dereferences match complete VC7 source COMDATs from an
independent seven-width probe. The 44 typed relocations, full body bytes
and internal control flow are reproducible. The two `at` methods used by
the fighter script accessors support the STL portion of their lookup path;
the script's 1,000-slot mapping is game-authored. Original element types
and callee ownership remain unclaimed, with no exact credit.

## Parent-backed VC7 deque `begin` after R079

Seven complete 35-byte `deque::begin` bodies have a cold VC7 source match,
one typed relocation each, and a same-family direct call from a reviewed
`deque::at` parent. The parent chain and raw call fields replay. Six
same-shape helpers without this caller witness remain pending. R079 grants
library origin only, with no reconstruction source or exact credit.

## VC7 deque iterator constructors after R080–R081

Seven 32-byte deque iterator constructors match complete VC7 source bodies
and are called by reviewed `deque::begin` methods. Each calls a matching
33-byte const-iterator constructor through one typed relocation. Those
seven no-relocation const-iterator bodies also have complete source matches
and reviewed parent calls. The cold verifier chain checks every source
body, target body and call field. Ghidra's imported `_Vector_iterator`
labels on the 32-byte bodies are not origin evidence. The actual game
element types remain unknown; these batches add library origin only.

## VC7 iterator dereferences after R082

Ten complete 19-byte deque iterator dereferences have a VC7 source match
and a typed call to an independently verified const-iterator dereference.
Other same-shape 19-byte bodies target unrelated or unknown functions and
remain pending. R082 grants library origin only; original element types
and reconstruction exactness remain unknown.

## VC7 iterator advance after R083

Nine complete 31-byte deque iterator `operator+=` bodies match the VC7
source probe and have typed same-family calls from independently reviewed
iterator additions. The reviewed parent is cold-replayed. Seven 27-byte
advance-like bodies do not match this profile and remain pending. R083
adds library origin only, with no reconstruction source or exact credit.

## VC7 deque iterator comparison after R084

Thirty complete target bodies reproduce VC7 deque const-iterator equality
and subtraction, iterator subtraction, and `end`. The two const-iterator
families have full no-relocation byte matches; the other 14 bodies have
typed calls bound to separately verified callee families. Five `end`
lookalikes with different or unknown callees remain pending. The accepted
bodies are library templates; original element types and exact
reconstruction remain unresolved.

## VC7 deque algorithm origins after R085

Sixteen complete VC7 template loops reproduce the target's forward and
backward deque copies and one fill, including `0x00420050` near the script
owner. Fifteen 70-byte copy wrappers are distinguished by their typed calls
to those independently verified forward/backward loop bodies. Eight
11-byte pointer-category helpers and fifteen 29-byte iterator increment or
decrement bodies also match complete source COMDATs and have exact
source-typed calls from those reviewed parents. The cold verifier checks
all 54 bodies, 2,889 bytes and 108 relocations with complete control flow.
Seven synthetic record widths and six scalar/pointer variants establish
template emission without identifying the game's original element types.
Other external callees retain their existing origin decisions; R085 adds
no authored source or exact credit.

## VC7 deque emptiness checks after R086

Thirteen complete 25-byte `deque::empty` bodies match all VC7 probe bytes
without source relocations. Each is also called through an exact
source-typed relocation from a separately reviewed R072 deque operation.
The parent operations and child bodies are cold-reverified. The short
body alone would not distinguish another owner with the same field test;
the caller witness supplies the template identity. These are library
origins only; original game element types remain unknown.

## Short VC7 template helpers after R087

Thirty-two allocator constructors, sixteen pointer-category helpers and
sixteen trivial destruction-range bodies reproduce complete VC7 source
COMDATs. The 5-, 11-, 14- and 16-byte bodies have no source relocations.
Each also has an exact source-typed call from a complete R073 template
parent, which the verifier cold-replays before checking the child. All
64 bodies, totaling 742 bytes, are library origins. Identical short code
without this caller witness remains insufficient; original game types and
reconstruction exactness remain unknown.

## VC7 allocator conversions and trivial destruction after R088

Sixteen complete 16-byte converting allocator constructors and twenty-two
complete 5-byte `_Destroy` specializations match the existing VC7 record
probe. Each also has an exact source-typed call from a reviewed R074
allocator/helper body. Both the complete parent chain and child COMDATs
cold-replay; all 366 child bytes match without relocations. The existing
record and record-pointer instantiations supply the exact callee symbols,
so a scalar probe is unnecessary for these accepted bodies. Nontrivial
destruction bodies remain pending. Original game types remain unknown,
with library origin only and no reconstruction source or exact credit.

## VC7 vector storage after R089

Ten complete 126-byte vector `_Buy` bodies and eight complete 103-/110-byte
`_Tidy` bodies match the independent vector operation probe. All 2,098
bytes, 46 typed relocations and full decoded control flow cold-replay.
Ten synthetic record widths and six scalar/pointer variants test template
emission without identifying original game types. Short constructors and
allocator callees still need their own complete comparisons and witnesses.
The pending vector insertion bodies do not match the probe's complete
extents and remain unclassified. R089 adds library origin only, with no
authored source or exact credit.

## VC7 vector helper call chains after R090

Seventy-two complete 14–42-byte vector/allocator helper bodies now have
full source comparisons and typed links to the independently reviewed
R089 storage bodies. Ten vector constructors call verified `_Buy` bodies.
The constructors in turn bind ten `_Vector_val` constructors and twenty
default/copy allocator constructors. Eight maximum-size wrappers, eight
allocation wrappers, eight deallocation wrappers and eight `_Allocate`
helpers also have exact source-typed parent calls. All 1,728 bytes and
72 relocations cold-replay; every short witness chain reaches a reviewed
storage body, and cycles or unrelated source callee symbols are rejected.
Ghidra's `_String_val` aliases on some base constructors do not establish
identity; the typed vector-constructor calls support `_Vector_val` here.
Original game types remain unknown, with library origin only and no source
or exact credit.

## VC7 construction, backward copy and vector wrappers after R091

Seventeen complete bodies match the independent vector operation probe:
eleven construction helpers, four backward-copy helpers and two vector
insertion wrappers. All 1,057 bytes and 26 typed relocations replay. The
construction and copy identities are corroborated by independently
reverified complete placement-new and CRT `memmove` anchors. The vector
wrapper source variants remain consistent along their recorded calls;
they do not identify original game types. Their short iterator callees
and the complete 795-byte `_Insert_n` at `0x004594B0` still require their
own evidence. R091 grants library origin only, with no source or exact
reconstruction credit.

## VC7 vector iterator and copy witnesses after R092

Eight complete vector/iterator callees now match source variants coupled
to their reviewed R091 parent calls. The bodies include the 26-byte
const-iterator subtraction and 32-byte iterator advance; the other probe
variants cannot substitute for these complete, stride-sensitive bodies.
Eight 51-byte copy wrappers also bind to independently cold-reverified
copy implementations. Their exact source callee variants replay against
all target bytes, even where the earlier record probe used different
synthetic type names. All sixteen bodies, 660 bytes and 21 typed
relocations replay. Identical `begin`/`end` shapes are distinguished by the
source-typed parent witness. Original game types remain unknown. R092
adds library origins only; the complete insertion implementation remains
pending and exact reconstruction is unchanged.

## CRT mantissa conversion after R093

The complete `__ld12cvt` body and its two short mantissa helpers reproduce
396 bytes from the pinned CRT archive. All nine conversion calls are
bound to independently complete vendor bodies, including existing
rounding and shift anchors. This resolves the two short helper identities
without relying on their imported names or tiny fingerprints. The
runtime verifier checks all 57 recorded functions and 28 direct-call
relocations, alongside the three local CRT anchors. Identical emission
from the single-threaded archive does not identify the actual linked
archive. Other CRT globals/callees remain unknown; this batch adds library
origin only, with no source or exact credit.

## Scalar copy wrappers and source-family ambiguity after R094

Four complete scalar copy wrappers reproduce 204 bytes with eight typed
relocations. Each has a complete 49-byte copying callee and an independent
CRT `memmove` anchor. These same callee bodies also reproduce the R073
`_Uninit_copy` specializations. The new `_Copy_opt` comparison checks the
entire alternative COMDAT and its typed call; it does not replace the
older evidence with a guessed source identity. Library origin remains
established while the original specialization and linker-folding history
remain unknown. All four wrapper bodies and all callee variants cold-
replay. R094 grants four new library origins only, with no exact or
reconstruction-source credit.

## VC7 vector/allocator wrapper callees after R095

Eleven complete assignment, iterator-addition and allocator-construction
wrappers reproduce 383 bytes and eleven typed calls. Each exact source
callee variant matches the entire independently reviewed same-family
callee. Older synthetic record and DirectInput-pointer probes provide
method-origin evidence, not the game's original element types. Complete
iterator alias/base bodies, vector assignment implementations and
construction implementations cold-replay before the new wrapper/callee
comparison. Other tiny lookalikes and exception methods with unresolved
data/vtable fields remain pending. R095 adds library origins only; source
presence and exact reconstruction are unchanged.

## Named standard exception ownership after R096

The three short exception candidates are `std::out_of_range`, established
by the complete ThrowInfo/CatchableType chain and actual emitted type
name. The initial `length_error` source shape was indistinguishable without
that metadata. Its message constructor and destructor are library methods;
its implicit copy constructor is compiler generated. Ten complete bodies,
two whole vtables and four whole compiler type-data COMDATs cold-replay.
The weak `_E` vtable symbols resolve through actual COFF fallback records
to independently complete `_G` deleting bodies; guessed symbol aliases
are insufficient. A same-shaped 28-byte method near the game scenes uses
a game vtable and a reviewed scene cleanup callee, so the exception byte
shape cannot establish its ownership. R096 adds three origins only, with
no reconstruction source or exact credit.

## Battle-end scene lifetime ownership after R097

The 28-byte `0x00424F40` uses the vtable written by the reviewed battle-end
initializer and calls the reviewed scene-base game cleanup. Its two
checked virtual slots bind the reviewed deleting wrapper and game update;
the deleting wrapper calls this exact destructor. The complete function
matches the natural explicit-destructor probe while the implicit probe
emits 19 bytes. This is authored game lifetime behavior even though the
nonrelocated shape matches standard exception destructors. The role/name
is inferred; the full class layout and vtable extent remain unknown.
R097 adds one authored origin and no source or exact credit. The provisional
authored denominator grows by 28 bytes to 1,950,921.

## CRT scalar and import ownership after R098

Five full CRT archive functions now bind all twelve relocation fields:
four to independently replayed complete callees, two to imports decoded
from the raw PE directory, and six to complete scalar definitions in the
same vendor member. The scalar definitions are whole readonly doubles;
zero-value storage alone is not used to infer a global or class layout.
Import fields must decode as absolute indirect calls to the verified IAT
slots, not merely point somewhere in the import section. Complete body
comparison and control-flow validation distinguish these vendor functions
from short lookalikes. R098 adds five library origins and no source or exact
credit. The pinned archive choice does not establish original linkage flags.

## Whole locale delimiter data after R099

`___lc_strtolc` at `0x00642CC1` is now a reviewed complete 220-byte vendor
function. Its four calls bind separately replayed CRT bodies and its remaining
field binds the entire four-byte readonly `_.,` string COMDAT, including NUL.
The readonly extension requires the full defining section and every symbol
definition, without granting a data origin or original-name proof from an
arbitrary pointer. R099 adds one library origin and no source or exact credit.

## Short custom core policies after R100

Twelve reviewed bodies add camera setup, primary-frame capture/compositing,
scene input and transition logic, HUD defaults, character sound/binding
forwarders and effect resource loading. Their full 780-byte extents use
independently reviewed game behavior and explicit policy fields, rather than
indistinguishable empty constructors or generic template wrappers. Full
game parent bodies corroborate the short methods where direct calls exist;
callback and selected virtual-slot pointers corroborate indirect entrypoints.
The input policy polls both input devices and toggles window mode for Enter
with either Alt scan code. The timed scene increments a word counter and
returns `0x220D` when that counter exceeds 180. Names, complete class layouts and original
transition/type spellings remain unknown.

The `SetRect` fields bind the raw PE import name/DLL. The existing full
`SetBlendMode` unit includes its eight-entry table and is cold-replayed as
495 bytes, without treating the table as code or dropping it from context.
R100 adds twelve authored origins, growing the provisional denominator by
780 bytes to 1,951,701; no reconstruction source or new exact credit is added.

## Effect forwarding contracts after R101

Eleven additional authored bodies combine reviewed game geometry/effect
calls with explicit owner fields, fixed transform/color policy and signed
coordinate arithmetic. The four background policies copy exactly 132 bytes;
this does not recover a complete class layout. The midpoint helper divides
the two observed signed coordinate sums by the complete readonly `2.0f`.
Game manager and argument-owner offsets are observed independently for the
fighter and auxiliary-object forwarders, with their original types unknown.

The two 57-byte auxiliary forwarders have distinct 20-/24-byte RET cleanup
despite otherwise similar argument forwarding. Preserve the unused incoming
argument and separate method contracts in later reconstruction. Full game
caller/callee anchors, selected virtual slots and complete extents verify
ownership; no short-shape match or implicit compiler attribution is used.
R101 adds eleven authored origins / 814 bytes, growing the provisional
denominator to 1,952,515, with no source or exact credit.

## Batch-scanned game policy ownership after R102

The full origin scanner now prioritizes complete body groups and independently
reviewed call context across all pending candidates. It retains actual call
destinations, vtable/data fields and RET cleanup. A scan hit remains a
diagnostic hypothesis; constructor/destructor shapes and vendor helpers still
need independent ownership evidence.

The first shared cohort adds seventeen explicit game policies: input, callback
control, audio/camera forwarding, conditional fighter/effect dispatch, facing
sprite drawing, text width selection and three complete name-glyph renderers.
Their full 2,051 bytes bind thirty-three whole reviewed anchors and fifteen
parent call edges. Four complete game peers corroborate input/glyph policies.
The name renderer draws eight signed glyph indices using 26 columns with
19-by-20 cells and 14-unit spacing; this is project rendering policy. Several
field meanings and original names/types remain unknown. R102 grows the
provisional authored denominator to 1,954,566, with no source or exact credit.

## Batch state/record policies after R103

Thirty-three additional complete bodies / 2,600 bytes now have reviewed game
ownership, each tied to an independent whole parent. The shared cohort
verifier freezes 22 parent bodies, 33 edges and 185 policy instructions.

Game progress uses signed-byte selectors at `+0x16AC4` / `+0x16AC5` and
record strides `0x17F0` / `0x5FC`. Selected dwords at `+8` / `+12` and word
tables at `+0x268` / `+0x394` are accessed in reviewed battle/HUD paths.
The progress bit operations use a signed-word argument, reject values below
0 or above 320 and access the bitmap at `+0x16A9C`. These observed strides
and offsets do not establish the full record/object layout.

Fighter predicates distinguish signed state ranges 50–149, 150–199 and
95–99. The horizontal-limit policy reads four readonly float scalars: 40,
0, 880 and 1280. Relative opponent coordinates drive a facing byte and
camera offsets of 0 / ±50. Selected collision fields are saved with their
original widths. Notice-related mode branches update signed-word levels
with limits 25 and 5. Original state names and time units remain unknown.

The font/snapshot helpers bind seven Windows import calls through the raw
PE and preserve all explicit project parameters; virtual animation dispatch
does not establish dynamic ownership. Camera reset writes explicit nonmember
globals, including 20.0f, rather than proving origin from a constructor-like
return value. R103 grows the provisional authored denominator to 1,957,166;
no source or exact credit is added.

## Small game helpers and dependency closure after R105

R104 records sixteen complete authored helpers / 806 bytes. Observed behavior
includes four-dword sprite-record writes, animation counter resets, a vector
copy at object offset 12, one indirect global draw dispatch, hexadecimal digit
conversion, a nonnegative global clamp, selected HUD text drawing, a grounded
state-window predicate, notice setup/transition updates and small effect-field
clears. The hexadecimal helper maps the observed ASCII digit and letter ranges;
its provisional name does not imply a recovered parser contract. Likewise,
state and field names remain inferred from their complete instruction behavior
and reviewed game context.

R105 closes three dependencies exposed by those helpers. One 204-byte body
builds and copies four 16-byte rectangle-corner records through the R104 setter.
An 88-byte battle transition resets animation fields, forwards a selected byte
and requests sound 0x26. A 73-byte notice initializer writes four observed
fields and calls the reviewed notice-text setup with argument one. Their full
365 bytes bind nine independently reviewed whole anchors and three parent
edges. R104 and R105 grow the provisional authored denominator to 1,958,337;
they add no reconstruction source or exact credit.

## Reviewed VC7 family peers after R106

Twenty-four complete pending bodies / 661 bytes share full structural
signatures with independently source-reviewed VC7 families: vector const-
iterator construction, deque iterator advance/increment/decrement, deque
const-iterator construction, allocator deallocation and vector iterator
advance. Direct-call displacements are normalized only after decoding, while
the exact destination remains in the signature; all other bytes, data fields
and RET cleanup remain unchanged. Existing family verifiers are cold-replayed
before the peer set is accepted. This establishes library ownership without
recovering the original game element types. R106 adds no authored denominator,
reconstruction source or exact credit.

## R107 — pinned VC7 runtime leaves

Four target bodies / 199 bytes reproduce complete COFF functions from the
hash-pinned VC7.1 `libcmt.lib`: `__setjmp3`, `__aullshr`, `__load_CW` and
`__checkTOS_withFB`. Three have no relocations. `__setjmp3` has one explicit
`DIR32` field for `__except_list` in its FS:[0] load. The verifier re-extracts
the original archive members and checks archive identity, member offsets,
symbol extents, relocations, full bytes and control flow. These are library
origins only and add no authored source or exact credit.

## F008 — reviewed game leaf helpers

Nine R104-authored helpers now have natural C++ source and complete cold exact
replay:

| Address | Bytes | Reconstructed function |
| --- | ---: | --- |
| `0x0040DB10` | 51 | `SpriteGeometry::SetFourDwords` |
| `0x0040FAC0` | 52 | `AnimationState::ResetPrimaryCounters` |
| `0x0040FB00` | 56 | `AnimationState::SetThreeCounters` |
| `0x0040FB40` | 43 | `AnimationState::ResetSecondaryCounter` |
| `0x0040FC50` | 18 | `AnimationState::ClearByte40` |
| `0x00423C60` | 32 | `SetClampedGameValue` |
| `0x0045B830` | 21 | `BattleEffect::ClearField74` |
| `0x0045D6F0` | 21 | `FighterState::ClearNoticeTransition` |
| `0x005FAC20` | 21 | `AuxEffect::ClearField8` |

The member functions are relocation-free. `SetClampedGameValue` includes all
three `DIR32` relocations to the observed global at `0x0066C23C`. One cold
compile of `GameLeafHelpers.cpp` replayed all nine units exact, covering 315
bytes. Class, field and method names remain provisional; the partial owner
interfaces are not instantiated or embedded. The exact total is now 51
functions / 9,231 bytes, or 0.47% of the provisional 1,958,337-byte authored
denominator.

## F009 — game policy helpers and dependency closure

Nine R104/R105 authored functions now have natural C++ source and complete
cold exact replay:

| Address | Bytes | Reconstructed function |
| --- | ---: | --- |
| `0x00411BB0` | 38 | `SpriteScene::CopyVector` |
| `0x00411BE0` | 33 | `SpriteScene::DispatchGlobalDraw` |
| `0x0041CA80` | 96 | `TextRasterizer::DecodeHexDigit` |
| `0x00440B00` | 78 | `BattleHud::DrawSelectedNotice` |
| `0x00443FC0` | 88 | `BattleState::StartHitSequence` |
| `0x00455010` | 96 | `FighterState::IsGroundedStateWindow` |
| `0x0045CDC0` | 73 | `FighterState::InitializeNotice` |
| `0x0045D650` | 78 | `FighterState::ConfigureNoticeText` |
| `0x0045D6A0` | 72 | `FighterState::BeginNoticeTransition` |

The batch covers 652 bytes and 17 explicit relocations. The vector copy and
hex decoder are relocation-free. The remaining units bind the observed global
dispatcher, text renderer, zero scalar, notice selector and sound bank, plus
all direct calls to independently reviewed game functions. One cold compile of
`GamePolicyHelpers.cpp` replays all nine complete extents exact.

The related R105 rectangle-corner builder at `0x00427500` remains diagnostic.
Natural source reproduces its full 204-byte extent, four calls and every byte
except two local-object stack displacements. It receives no source or exact
credit; no artificial layout was introduced. Names and partial owner layouts
in F009 remain provisional. The exact total is now 60 functions / 9,883 bytes,
or 0.50% of the provisional 1,958,337-byte authored denominator.

After F009, origin review is active again. Preserve this exact baseline while
reviewing bounded pending cohorts. The scanner's six combined reviewed-game-
callee/parent candidates define the next R108 investigation, but their
constructor/destructor-like shapes and reviewed neighbors do not prove
ownership.

## R108 — lifetime shape can preserve ownership uncertainty

Complete cold VC7 source alternatives reproduce all 176 bytes of the six
handoff candidates, including every call and vtable field. Five functions
remain pending because explicit and implicit source alternatives emit the same
complete bytes. Reviewed game callees and parents establish their runtime
context, not whether their source bodies were authored. These are retained
negative discrimination results, not failed or abandoned reviews.

The stage destructor at `0x00449D40` is authored: its 31-byte vtable-writing
virtual destructor matches explicit source and differs from complete 22-/30-
byte implicit cleanup controls. The paired stage lifetime family and selected
deleting slot corroborate this interpretation. Original names and the complete
stage layout remain unknown. The camera initializer called at `this + 4`
writes globals; it supplies no evidence for five member fields or object size.

`0x0040EC8A` is retained as a 232-byte interior catch/tail candidate. Its bytes
and cleanup call are frozen as bounded context, without accepting a complete
owner extent or inferring compiler/library/authored ownership. The explicit
source/target verifier records 103 context extents, 98 parent edges and nine
selected readonly vtable slots. R108 adds one authored origin / 31 bytes and
no source or exact credit.

## R109 — scene, geometry, replay and list-dispatch policies

Thirteen whole policies add 2,465 authored bytes. The options and name-entry
initializers bind the actual resource paths, texture counts, field widths and
selected reviewed scene slots. Ambiguity in their base constructor does not
hide their own explicit policy. Font cleanup binds SelectObject, DeleteObject
and ReleaseDC through the raw PE imports. Name lookup uses separate observed
global lists; no complete global owner layout is recovered.

The numeric label renderer uses signed quotient/remainder by ten and glyph
index offset 52, with four other fixed glyph values 13, 40, 71 and 100. The
bounds transform selects horizontal arithmetic using the signed byte at
argument offset `+0x66`; six conversion call sites use the existing reviewed
runtime helper, with four executed on each branch path. Resource parameters distinguish the observed mode
branches, word 9999, indexed owner tables, and a float expression with complete
readonly scalars 8800 and 900 plus integer 1201. The range selector distinguishes
queue playback, word generation and recording using observed global modes;
its signed arithmetic divides by 32768 with truncation toward zero. Original
mode names and physical units remain unknown.

Effect policies visit four 20-byte lists or two auxiliary lists. Signed-byte
selectors and element bytes `+0x67/+0x68` control the observed virtual slots;
auxiliary advancement and pruning test element dword `+8`. Generic STL helpers,
unresolved calls and actual dynamic callees receive no ownership credit from
these policies. The complete external tails in the two runtime-looking
contexts remain explicit and independently pending.

The verifier checks 51 bounded context extents, eleven parent edges, 157
policy witnesses, three import bindings, four selected scene slots and four
readonly scalars. R109 adds no source or exact credit. Eighteen explicit name
aliases preserve earlier R104/R105 evidence after F008/F009 renamed functions;
original hashes and roles remain unchanged. The exact baseline is still 60
functions / 9,883 bytes; origin review has 1,297 pending candidates and the
provisional authored denominator is 1,960,833 bytes.

Both R108/R109 verifiers and the retained R104/R105 evidence passed the final
no-auth public MCP acceptance, alongside 146 tests and a full 60/60-unit cold
exact replay across eleven objects. No exact source or manifest was changed.

## R110 — source-typed deque dependencies of the reviewed game policies

Seven complete library bodies / 501 bytes are now accepted through
`scripts/repo-python scripts/verify-deque-game-dependency-origins.py` and
`config/deque-game-dependency-origin-evidence.json`. The new bodies are default
iterator/const-iterator constructors `0x004453C0`/`0x00445530`, postfix iterator
increments `0x00445400`/`0x005F8420`, size getter `0x005F8110`, single erase
`0x005F8290` and complete range erase `0x005F8680`.

Natural VC7 source models reproduce both already-reviewed whole game parents:
the 221-byte four-list delete/clear loop and 276-byte two-list advance/prune
loop. Each parent has ten direct calls. The cold graph compares all 53 source
COMDATs / 3,207 bytes, including 44 prior library anchors and 85 exact typed
calls. All nodes are reachable from the independent game policies. The tiny
size getter is typed by its full parent; the zeroing const-iterator constructor
is typed through the default iterator. The second game loop accesses entries
through `at`, not the unchecked `operator[]` source alternative. Equal parent
bytes cannot distinguish those calls without whole typed callee evidence.

Postfix increment and decrement have equal non-relocation bytes. The exact
prefix call and complete prefix body distinguish them. The two-word return
uses a hidden result buffer and `RET 8`; single/range erase retain `RET 12` and
`RET 20`. The 262-byte range erase compares both copy/pop paths and all thirteen
calls, including result-iterator construction. Preserve these full extents.

Probe element classes and owner fields are explicit synthetic observations,
not recovered game layouts or original element definitions. No reconstructed
source, mapped name or exact match is added. The delete jump remains unknown,
including its external tail. The prior R032 range-error library body is bounded
context; its old vector/`length_error` source-shape alias does not establish its
original family or exception identity and is not rewritten by this review.

The checkpoint is 3,061 reviewed candidates: 911 authored, 1,575 library and
575 compiler generated, with 1,290 pending. Exact stays 60 / 9,883 bytes and the
authored denominator stays 1,960,833 bytes. Local cold acceptance, target-required
tracking and all 152 public tests passed. Six R111 erase candidates are the next
bounded review; their diagnostic shapes do not yet establish ownership.

The single final no-auth public MCP replay passed this complete graph, retained
R108/R109 evidence, 864 authored extents, target/project attestation and 152
tests. All 60 exact units also cold-replayed across eleven objects / 9,883 bytes.

## R111 — five complete erase graphs and four single-erase wrappers

Twelve complete library bodies / 1,654 bytes are accepted by
`scripts/repo-python scripts/verify-vendor-deque-erase-origins.py` and
`config/vendor-deque-erase-origins.json`. The five complete range erases are
`0x0041E380`, `0x0041E800`, `0x00424000`, `0x00455D30` and `0x0045C100`.
Four full single-erase wrappers at `0x0041DC90`, `0x0041DF10`, `0x00423EF0`
and `0x0045C0A0` each bind their actual iterator addition and range-erase body.
The one-byte graph additionally types begin `0x004143D0`, end `0x00414400`
and indexed iterator construction `0x00415560` through complete parent calls.

All five range bodies have 262 bytes and thirteen calls. The source profiles
that fit become distinguishable only through their complete callees. Four
whole graphs reproduce unsigned-long, float and `void*` models; the fifth
reproduces the checked unsigned-byte model. Original element identities,
signedness, game owner layouts and linker folding remain unknown. Source
alternatives are scoped to complete graphs, rather than all short body shapes.

Cold verification covers 129 distinct target bodies / 7,958 bytes and 203 typed
calls, including 117 independently reviewed library anchors. All 337 complete
source alternatives cold-replay. Every call is bound to a complete source-typed
callee inside the graph. Both copy/pop branches, iterator-result construction
and exact `RET 20`/`RET 12` cleanup remain part of the comparisons. The begin/end
helpers retain their distinct 35-/41-byte bodies and complete 32-byte indexed
constructor, which calls the reviewed const-iterator constructor.

The 108-byte parent `0x00455CA0` and 1,459-byte insertion dependency
`0x00455E40` retain unknown origin. A parent calling newly proven library
functions is insufficient ownership evidence. No source or exact credit is
added; exact stays 60 functions / 9,883 bytes. Origin review now has 3,073
resolved candidates (911 authored, 1,587 library, 575 compiler) and 1,278
pending. Target-required tracking, the accepted-state cold replay and all 157
public tests passed locally. R112 starts with six pending postfix candidates;
same-shaped increment/decrement bodies still require exact typed calls.

The single final no-auth public MCP replay passed all 337 whole source
alternatives, retained R110 evidence, 864 authored extents, target/project
attestation and 157 tests. It also cold-replayed every exact unit: 60/60 across
eleven objects / 9,883 bytes. The provisional insertion span still contains
`0x00456137` and must be reconciled with its cleanup tails before review.


## R112 — postfix identity, input matching and the event worker

Six complete 54-byte postfix increment bodies bind six independently reviewed
29-byte prefix increments: `0x00414970→0x00415580`,
`0x00414A20→0x00415690`, `0x00414AD0→0x004157A0`,
`0x0041DF90→0x0041ECA0`, `0x0041E020→0x0041EE00` and
`0x00423F90→0x004244A0`. Complete cold prefix typing distinguishes the
increment from identical-shaped postfix decrement. Thirteen source models
fit each increment; original element identity and folding remain unproved.
The natural probe and verifier retain all 52 overload controls, the full
REL32 field at offset 27, hidden-result copy and `RET 8`.

The complete 695-byte game input matcher at `0x00455800` transforms guarded
pattern characters into direction/button masks, applies facing to L/R and
walks the history deque at `this+0x518`. The complete switch comprises 17
pointers and 40 remap bytes outside the code span. The low/high-nibble tests
and terminal X return behavior are target observations; the inferred name,
complete layout and buffer capacity are not recovered source facts.

The complete 273-byte worker at `0x00423B40` waits on `0x0068BE34`, traverses
`0x0068BE44`, signals the queue front for a nonzero current entry and erases
zero entries. Its callback push is bound to the raw `CreateThread` import.
The independently authored/exact clamp `0x00423C60` controls the same wait
global `0x0066C23C`; R104/F008 source and exact evidence remain unchanged.
Unknown setup, cleanup, default iterator and const-iterator construction
receive context hashes without ownership credit. The unusual front/current
relationship and unreachable return are preserved as observations.

`verify-deque-postfix-context-origins.py` cold-replays independent R085 roots,
checks all complete postfix/prefix alternatives, 22 contexts / 6,407 bytes,
41 parent edges, 112 witnesses and the full 108 bytes of switch data. R112
adds six library bodies / 324 bytes and two authored bodies / 968 bytes.
The checkpoint is 3,081 resolved (913 authored, 1,593 library, 575 compiler),
1,270 pending, and 60 exact functions / 9,883 bytes. Authored exact coverage
is provisionally 9,883 / 1,961,801. The next bounded R113 queue-helper cohort
requires fresh complete source typing; tiny shapes remain insufficient.

One final no-auth public HTTPS MCP request passed R112, retained R111/R110
source graphs, all 866 authored extents, target/project attestation, 162 tests,
progress freshness and `git diff --check`. All 60 exact units / 9,883 bytes
cold-replayed across eleven objects. Investigation and intermediate checks
used local tools; the public acceptance route ran once.


## R113 — queue dependency typing and the main application loop

Five complete deque helpers now have library origin: default iterator
`0x00423F50` (22), default const iterator `0x00424500` (33), size `0x00423D40`
(17), unchecked index `0x00423DB0` (49) and front `0x00423DF0` (32).
The 96-byte enqueue policy at `0x00423C80` scans for equal entries and appends
only if none was found; it continues scanning after a duplicate. Its natural
source probe binds all six relocations to the actual size/at/push_back methods
and global `0x0068BE44`. The worker's two used default iterators and the full
begin/addition/dereference relationships supply independent type context.
Getter shapes and two-field clearing alone remain insufficient.

The complete 2,987-byte game parent at `0x00602A60` creates the main window,
loads the three TH075 archives, initializes graphics/input/sound, dispatches
scenes through a guarded fifteen-entry table and runs the message/event loop.
It queues the address of a local event handle slot. Preserve the observed
indirection and the worker's front/current relationship; synchronization and
original handle types remain unproved. The full 60-byte table follows the
`RET 16` code span and is checked separately from authored code coverage.
The inferred role is `GameApplication::RunAt00602A60`; original interface and
WinMain spelling are not established by this review.

The verifier cold-compares 65 source bodies / 4,002 bytes and 150 typed fields,
retains 65 shape controls, nine external byte snapshots, nine complete game
contexts / 5,063 bytes and 234 witnesses. Its 59 old library anchors retain
independent evidence. Archive replay verifies the complete CRT memory/string
boundaries with embedded tables. Unknown external functions and the three
interior candidates of the already accepted string `_Copy` body receive no
new origin credit. The pointer model fits this whole graph; it does not
identify the original game element type. No new game source or exact unit
is accepted. R104/F008 wait-global clamp evidence remains unchanged.

R113 adds five library bodies / 153 bytes and two authored bodies / 3,083 bytes.
The checkpoint is 3,088 resolved (915 authored, 1,598 library, 575 compiler)
and 1,263 pending. Exact remains 60 / 9,883 bytes; reviewed authored coverage
is provisionally 9,883 / 1,964,884. R114 investigates the remaining shared
lifetime wrappers, registered window callback and startup entry with complete
source controls and independent ownership; no classification follows from
adjacency, use by the game or a previously imported symbol name.

One final no-auth public HTTPS MCP request passed R113, retained R112,
all 868 recorded authored extents, target/project attestation, 169 public
tests, progress freshness and `git diff --check`. All 60 exact units / 9,883
bytes cold-replayed across eleven objects. Investigation and intermediate
verification used local tools; the public acceptance request ran once.


## R114 — queue service lifetime and callback ownership

Four complete policies add 415 authored bytes: acquire `0x004239F0` (155),
release `0x00423A90` (143), local construction/acquire/release `0x004239C0`
(34) and registered window callback `0x00603650` (83). Independent R113 main
and R112 worker contexts bind actual client count, wait/active globals,
handles, worker callback, readiness flag and raw PE APIs. Queue release
calls TerminateThread and passes queue entry values directly to SetEvent;
the worker's first-dword dereference remains a different target observation.
The 19-byte clear source equals the older R077 destructor-shaped body with
its `_Tidy` call; preserve the old evidence/name and method/folding ambiguity.
The synthetic probes establish source controls, not complete game layouts.

Ten complete lifetime controls / 274 bytes distinguish the 34-byte explicit
local-guard construction from implicit/persistent members and the 40-byte
ordinary member returning this. Its original owner/spelling remains provisional
and the target has no observed caller/xref. The separate 26-byte `0x00423B20`
matches an ordinary pulse and compiler-generated copy initializer `_$E3`
exactly outside the same typed calls. Whole `.CRT$XCU` registration and both
generated helper bodies preserve that compiler alternative. It stays unknown;
a destructor guess or ordinary-source-only choice is insufficient.

The window callback's complete message cases set readiness for 1, post quit
for 2, return zero for 0x12 and otherwise return DefWindowProcA. Its RET 16,
actual main-loop registration/readiness fields and raw USER32 imports agree
with the natural full source probe. The replay checks 37 policy fields, fresh
clear/size/index controls, four game contexts / 3,388 bytes and 336 witnesses,
and cold-replays R077/R113 including the whole main-loop scene table.

The PE entry `0x0064232C` remains pending. Its complete 469-byte pinned CRT
source body matches outside all 37 fields, but 32 code/data/EH associations
lack independent binding evidence. Four IAT fields and the game main callback
are checked; structural identity does not earn library or exact credit.
Both returns and the internal SEH filter remain inside the complete extent.
R006 already owns the 61-byte `__chkstk` target; investigate the startup's
`__alloca_probe` association without recounting it. The private startup graph
is a diagnostic survey, not a closed accepted source graph.

The checkpoint is 3,092 resolved (919 authored, 1,598 library, 575 compiler)
and 1,259 pending. Exact remains 60 / 9,883 bytes, with provisional authored
coverage 9,883 / 1,965,299. Recorded authored extents total 872 / 1,952,956 bytes.
R115 targets six unknown startup dependencies; retain both R114 ambiguities
and the five R108 lifetime ambiguities. No new source or exact units are added.

One final no-auth public HTTPS MCP request passed R114, retained R077/R113
dependency replays and R112 contexts, all 872 recorded authored extents,
target/project attestation, 178 public tests, progress freshness and
`git diff --check`. All 60 exact units / 9,883 bytes cold-replayed across
eleven objects. Investigation and intermediate verification used local
tools; the public acceptance request ran once.


## R115 — vendor heap graph and startup boundary evidence

Four complete vendor-library bodies add 196 bytes: SEH epilog `0x0064544F`
(17), heap initializer `0x00649735` (81), heap selector `0x0064971B` (26) and
small-block initializer `0x0064A6CD` (72). The epilog's own complete assembly
source extent has no relocation. The three-function heap graph retains all
17 fields, both failure/success paths, raw HeapCreate/HeapAlloc/HeapDestroy,
actual COMMON definitions and whole 72-byte version-state BSS topology.
Target data uses PE loader zero-fill geometry, not fictitious file bytes.
Zero values alone are insufficient evidence; full API flows and target
instructions bind these reproducible source associations. Original debug
names and executable-wide compiler settings remain unknown.

The natural SDK probe emits the entire 24-byte OSVERSIONINFOA layout array:
148-byte size and offsets 0/4/8/12/16. Whole section, source and header hashes
are checked on a cold build. Seventeen witnesses in the full 469-byte pending
entry prove the raw GetVersionExA buffer and actual platform/major stores.
The selector returns 1 for platform 2 and unsigned major >=5, otherwise 3.
The heap initializer uses selector 3 to initialize the 0x3F8 small-block
threshold; its helper allocates 0x140 bytes for sixteen five-dword vendor
headers. This establishes CRT behavior without inferring game object layouts.

Four roots retain unknown ownership: prolog `0x00645414` (59), fast error
policy `0x006422B2` (36), error policy `0x0064228D` (37) and command-line
parser `0x00648FF5` (93). Their complete vendor source controls and CFGs
are retained, but unresolved handler/error/multibyte chains do not become
accepted callees. Eight diagnostic source bodies / 1,144 bytes retain whole
auxiliary extents and actual fields. The 230-byte `__except_handler3` target
is not inventoried. The exit helper's 48-byte source includes a final INT3
that its 47-byte candidate omits. Neither boundary receives new credit.
The 336-byte set-codepage body includes its entire cleanup helper; no caller
prefix or truncated tail is used.

The 61-byte R006 stack probe's `__alloca_probe` alias is now confirmed from
the complete member's same section/offset definition and all target bytes.
The original `__chkstk` evidence/name remains unchanged. R115 cold-replays
57 old archive bodies and the three local R025 definitions with full tables.
Eight whole readonly literals / 121 bytes retain independent source/target
data comparison. The R114 entry stays pending with its historical diagnostic
record intact.

The checkpoint is 3,096 resolved (919 authored, 1,602 library, 575 compiler)
and 1,255 pending. Exact remains 60 / 9,883 bytes, with provisional authored
coverage 9,883 / 1,965,299. Recorded authored extents remain 872 / 1,952,956.
R116 investigates six runtime error dependencies. Retain all R108 and R114
ambiguities and the four R115 pending roots until their missing evidence changes.

One final no-auth public HTTPS MCP request passed R115, retained R114
including its R077/R113 dependency replays, R006/R025 archive anchors,
all 872 recorded authored extents, target/project attestation, 189 public
tests, progress freshness and `git diff --check`. All 60 exact units /
9,883 bytes cold-replayed across eleven objects. Investigation and
intermediate verification used local tools; the public acceptance request
ran once.


## R116 — dynamic error dispatch and complete shared-copy ownership

Three complete library bodies add 304 bytes: exit dispatcher `0x006440A5`
(48), dynamic message-box dispatcher `0x0064FBFE` (249) and shared-copy entry
`0x00641B80` (7). The exit candidate now includes its own terminal INT3;
R115's historical diagnostic record is preserved with a narrowly checked
R116 reconciliation. The private database is unchanged. The seven-byte copy
entry jumps into the reviewed strcat tail; the whole 248-byte source/target
carrier includes both own extents and nine bytes of LEA/MOV alignment.

Six actual DLL export flows bind complete literals, lookup results, pointer
stores and indirect calls. The five USER32 caches retain their whole 20-byte
source BSS topology and PE loader zero-fill geometry. A cold natural SDK
probe checks USEROBJECTFLAGS size/field and full service flags through the
entire readonly 24-byte array. R115's independent GetVersionExA buffer/store
witnesses establish the actual platform/major policy globals. Original debug
names and compiler/linker settings remain unknown.

The writer (375), banner (57) and fastcall cookie check (14) remain pending:
the actual cookie failure tail's EH/security-handler chain is unresolved.
Their whole source/target controls preserve all fields. Complete nineteen-entry
error table and messages, all 32 readonly literals / 1,120 bytes, mutable
state definitions and three source contexts / 122 bytes are diagnostic;
they do not close the code graph. The failure helper's full source extent is
49 bytes, including its embedded filter and terminal INT3; its 48-byte ledger
candidate remains unchanged. Retained anchors cold-replay independently.

The checkpoint is 3,099 resolved (919 authored, 1,605 library, 575 compiler)
and 1,252 pending. Exact remains 60 / 9,883 bytes; provisional authored
coverage and recorded authored extents remain 9,883 / 1,965,299 and
872 / 1,952,956. Continue the bounded R117 security/failure/EH cohort;
retain all unresolved roots and lifetime ambiguities. No new source or exact
units are added.

One final no-auth public HTTPS MCP request passed R116, retained R115 and
R114 including R077/R113 dependency replays, R006/R025 archive anchors,
all 872 recorded authored extents, target/project attestation, 202 public
tests, progress freshness and `git diff --check`. All 60 exact units /
9,883 bytes cold-replayed across eleven objects. Investigation and
intermediate verification used local tools; the public acceptance request
ran once.


## R117 — complete cookie initialization and SEH/NLG dependencies

Six complete library bodies add 779 bytes: cookie initializer (102), EH
validator (553), global unwind (32), previously pending prolog (59), NLG first
entry (9) and NLG shared body (24). All 65 root fields retain complete cold
source/target comparison. The prolog now binds a fully compared 230-byte
handler with independently checked validation/unwind/NLG children. The
104-byte R025 local unwind's registered handler is also compared as a complete
34-byte source body. These two handlers are not inventoried and receive no
candidate credit; scope input callbacks retain their actual slot/frame ABI
without credit for application implementations. R115's historical prolog
record is preserved through a specific R117 accepted-origin guard.

The entire 33-byte NLG carrier preserves the first entry's shared jump and
RET 4, and binds the complete initialized 16-byte destination/signature state.
Global unwind retains its real local continuation and raw RtlUnwind import
thunk. The validator's complete 76-byte cache BSS has actual defining offsets,
source alignment and loader zero-fill geometry; direct and EBX-mediated
InterlockedExchange calls retain their raw IAT provenance. A cold natural
120-byte SDK array proves all thirty TIB, memory, PE and entropy layout facts.

Cookie initialization binds five actual entropy APIs and its whole default
cookie definition. The entire `.CRT$XCAA` registration and complete startup
boundary objects bind the actual 56-byte merged table; the whole 106-byte
cinit context proves traversal. Other table callbacks and cinit bindings
remain diagnostic. Full original debug names/compiler settings remain unknown.

Failure source (49; candidate 48), user error handler (328) and short exit
wrapper (17) remain pending. Their EH/callback/termination fields retain
actual destinations; nine whole readonly error literals / 474 bytes and the
complete 195-byte doexit context earn no ownership. R116 writer/banner/cookie
roots remain pending. The private database and exact/source ledgers are
unchanged.

The checkpoint is 3,105 resolved (919 authored, 1,611 library, 575 compiler)
and 1,246 pending. Exact stays 60 / 9,883 bytes; provisional authored coverage
and recorded extents remain 9,883 / 1,965,299 and 872 / 1,952,956. Continue
R118 termination/lock dependencies, preserving all outstanding ambiguities.

One final no-auth public HTTPS MCP request passed R117, retained R116/R115,
R006/R025 runtime anchors and all PE import thunks, retained R114 including
R077/R113 dependency replays, all 872 recorded authored extents, target/project
attestation, 217 public tests, progress freshness and `git diff --check`.
All 60 exact units / 9,883 bytes cold-replayed across eleven objects.
Investigation and intermediate verification used local tools; the public
acceptance request ran once.


## R118 — complete static locks, critical-section dispatch and callback loop

Five complete library bodies add 273 bytes: unlock (21), callback loop (24),
static lock initializer (73), dynamic critical-section wrapper (139) and
stdcall no-spin fallback (16). All 64 root fields and entire own source
extents cold-replay. The callback loop preserves its observed EAX begin
and stack end; the fallback keeps RET 8 despite using only its first input.
Neither inferred conventional ABI nor tiny code shape supplies origin.

The full 288-byte lock table has 36 pointer/type entries and fourteen static
flags. All 336 bytes of static critical-section BSS, four-byte API cache and
whole 72-byte CRT state have real source definitions and actual loader
geometry. A natural forty-byte SDK array proves complete 24-byte critical
sections, all field offsets, pointer size and error constants. The full
initializer walks all table records and uses actual 24-byte buffer strides.
The thread-startup parent is frozen diagnostically, retaining its unresolved
FLS/TLS/allocation graph.

The dynamic wrapper binds full DLL/export strings, raw lookup imports, actual
cache stores/call/fallback selection and all twelve bytes of its readonly
scope table. Actual filter/handler labels belong to the entire 139-byte primary,
including the embedded RET, status/error paths, epilog and main RET. R115's
version-global provenance and R117's complete SEH graph independently replay.

Three complete merged callback ranges / 52 bytes retain actual source boundary
objects and markers. The forty-byte onexit initializer and its entire CRT
registration are pending; both four-byte onexit COMMON definitions retain
actual loader storage and pointer flows. Callback registration grants no
implementation origin. Seven full literal controls / 105 bytes and six whole
source contexts / 522 bytes remain independently compared diagnostics.

Lazy lock source is 160 bytes, including a nine-byte finally; the provisional
151-byte main and nine-byte interior candidate remain unknown. The 195-byte
exit parent also owns a fourteen-byte shared cleanup entry whose EH finally
starts five bytes earlier. Whole labels/parents are compared without synthetic
standalone sources or truncation. Four roots / 444 source bytes and both
interior candidates / 23 bytes retain allocator/TLS/termination uncertainty.
The private database, exact and source ledgers are unchanged.

The checkpoint is 3,110 resolved (919 authored, 1,616 library, 575 compiler)
and 1,241 pending. Exact remains 60 / 9,883 bytes; provisional authored coverage
and recorded extents stay 9,883 / 1,965,299 and 872 / 1,952,956. Continue R119
allocator/TLS dependencies, preserving all prior unresolved roots/ambiguities.

Final acceptance passed in one no-auth public HTTPS MCP request: the full
R118 verifier and retained R117/R116/R115/runtime/import graphs, R114 lifetime
controls, all 872 recorded authored extents, target/tracking/Ghidra attestation,
233 public tests, progress freshness and `git diff --check`. All 60 exact units /
9,883 bytes cold-replayed across eleven objects. Investigation and intermediate
verification used local tools.


## R119 — complete small-block heap graph and callback/TLS dependencies

Six library dependencies add 1,818 bytes: small-block find (43), free (792),
allocation (764), new region (183), new-handler callback (27) and TLS allocation
fallback (9). All 100 root fields cold-compare; the accepted graph's 51 fields
bind actual COMMON/state definitions, raw imports and independently replayed
memmove/group-allocation dependencies. Whole coalescing, split, rover, bucket,
decommit/release and list-compaction paths retain their complete extents.
The callback passes the requested size; TLS allocation ignores its callback
argument and preserves RET 4. Neither grants user callback implementation credit.

A natural 168-byte internal CRT layout probe checks complete heap types,
page/group/region constants, API flags and the observed 140-byte thread-data
layout fields. All nine heap COMMON globals have real definitions and loader
geometry. Six defining state sections / 452 bytes include the whole 136-byte
exception table/control section, sixteen-byte FLS cache, initialized TLS index,
mode/callback BSS and 288-byte lock table. Five full readonly FLS literals /
54 bytes retain the actual dynamic/fallback flows in full thread-startup context.
Seven old anchors / 1,341 bytes replay independently; memmove's entire code
and embedded switch-data extent remains under the complete R025 control.

Heap-allocation source is 123 bytes, including a three-byte EH head and nine-byte
shared cleanup after its main return. The 111-byte main candidate and separate
nine-byte interior remain unchanged. Calloc's earlier three-byte EH head and
nine-byte cleanup, and free's nine-byte cleanup, also belong to complete source
parents. Three whole scopes / 36 bytes and all actual label bindings replay;
no synthetic fragment source or database mutation is used.

All six original handoff roots plus calloc remain unknown: seven whole source
bodies / 607 bytes and three existing interior candidates / 27 bytes. Their
lazy-lock/malloc/calloc/errno/getptd/error/termination cycle is still open.
Four complete diagnostic contexts / 485 bytes retain its observed edges.
The next bounded R120 task must close real error/termination dependencies;
accepted small-block callees and correct thread fields alone confer no origin.
Exact/source/mapping ledgers and original pending lifetime alternatives remain.

The checkpoint is 3,116 resolved (919 authored, 1,622 library, 575 compiler)
and 1,235 pending. Exact remains 60 / 9,883 bytes; provisional authored coverage
and recorded extents stay 9,883 / 1,965,299 and 872 / 1,952,956.

Final acceptance passed in one no-auth public HTTPS MCP request: the complete
R119 verifier, retained R118/R117/R116/R115/runtime/import graphs, R114 lifetime
controls, all 872 recorded authored extents, target/tracking/Ghidra attestation,
251 public tests, progress freshness and `git diff --check`. All 60 exact units /
9,883 bytes cold-replayed across eleven objects. Investigation and intermediate
verification used local tools.

## R120 — complete CRT allocator/lock/error/termination cycle

Reviewed against the pinned supplied Japanese TH075 target. The six handoff
roots require twelve further complete source bodies to close their actual
code, data, API and EH graph. All eighteen are library origin, covering 1,928
complete source bytes and 166 typed relocation fields:

| Address | Whole bytes | Vendor source symbol |
| --- | ---: | --- |
| `0x00648C70` | 375 | `__NMSG_WRITE` |
| `0x00648E11` | 57 | `__FF_MSGBANNER` |
| `0x00640611` | 14 | `@__security_check_cookie@4` |
| `0x006405E0` | 49 | `_report_failure` |
| `0x0064529E` | 328 | `___security_error_handler` |
| `0x0064425B` | 17 | `__exit` |
| `0x00644187` | 195 | `_doexit` |
| `0x00646725` | 49 | `__lock` |
| `0x00646685` | 160 | `__mtinitlocknum` |
| `0x0064162B` | 40 | `___onexitinit` |
| `0x00644331` | 18 | `_malloc` |
| `0x00644305` | 44 | `__nh_malloc` |
| `0x0064428A` | 123 | `__heap_alloc` |
| `0x00642A61` | 113 | `_free` |
| `0x00647F98` | 9 | `__errno` |
| `0x00646196` | 113 | `__getptd` |
| `0x00644343` | 187 | `_calloc` |
| `0x0064228D` | 37 | `__amsg_exit` |

Replay `scripts/repo-python scripts/verify-runtime-cycle-origins.py`. The
verifier extracts each complete own function auxiliary extent from its
hash-pinned VC7.1 archive member, compares every source byte and relocation,
rechecks the full instruction inventory and exits, and closes every direct
code edge against another complete root or an independently accepted anchor.
The cookie check's external tail jump is accepted only at its actual typed
REL32 field to the complete failure body. Eighteen independently reviewed
anchors / 3,114 bytes are compared in full; their original control-flow and
shared-tail proofs cold-replay through R119 and the retained R115–R118 chain.
This preserves strcpy's shared carrier, memmove's embedded switch data and
the genuine chkstk/alloca source alias rather than inventing new bodies.

Three canonical boundaries expand to their complete source extents:
`0x00646685` 151 -> 160, `0x0064428A` 111 -> 123, and `0x006405E0` 48 -> 49.
The last byte of report_failure is a terminal INT3 after ExitProcess. The
allocator and lazy-lock extents include their complete cleanup entries; no
comparison stops at the earlier provisional Ghidra boundary. No target or
database write is made.

Five existing candidates are library-owned interior labels, **not five more
complete source functions**: `0x0064671C` / 9, `0x00644236` / 14,
`0x006442FC` / 9, `0x006443ED` / 9 and `0x00642AB4` / 9. Their 50 bytes overlap
reviewed parents. Names remain blank, spans remain unchanged, and exact/source
credit remains zero. Each label is re-read from its parent's actual COFF
section; the earlier EH heads (+170 doexit, +111 heap allocation, +167 calloc)
remain distinct from the later shared entries (+175, +114, +170). Seven whole
12-byte scope tables bind their actual filter/handler labels inside complete
parents, including the two newly replayed security failure scopes.

Defining data comprises fifteen whole sections / 1,048 bytes, eleven genuine
four-byte COMMON definitions, six source CRT range markers, three complete
merged callback ranges / 52 bytes, the actual four-byte onexit initializer
registration, and thirty-eight full readonly literals / 1,513 bytes. The full
152-byte error table retains all nineteen code/message pairs; each pointer
binds a whole defining literal. Writable PE storage, loader zero-fill,
source symbol offsets and every initialized pointer are checked rather than
using arbitrary zero scalars. Retained cold SDK/CRT probes establish the
complete critical-section, exception, heap and thread layouts without adding
any game class layout or source.

The 239-byte MT initializer is diagnostic context only. Its complete code,
export literals, raw fallback API slots, TLS index and FLS cache establish the
provenance of getptd's dynamic API dispatch. Its other startup/free-callback
children remain unaccepted. Optional `_pnhHeap`, `_user_handler` and `__adbgmsg`
callbacks preserve their actual call ABI and genuine whole BSS definitions;
no user callback implementation receives library origin. The security handler
retains both user arguments, caller stack cleanup, its exception filter and
continuation. The onexit callback loop similarly preserves reverse traversal,
flags, source registration and callback ABI without assigning origin to
registered application callbacks.

`origin_reconciliation.py` lets R115–R119 retain their historical pending
snapshots while accepting only the same complete own member, source/target
hashes, field provenance and specific R120 canonical classification. Historical
cold source and data checks still run. Internal labels additionally require
an accepted complete parent and cannot gain an independent name or source
credit. Fifteen new regression checks reject truncation, open graph edges,
changed parent/source identity, registration substitutions and exact credit.
All 266 public checks pass. The 60-function / 9,883-byte exact baseline and
872 recorded authored bodies / 1,952,956 bytes remain unchanged. Origin totals
are 3,139 resolved (919 authored, 1,645 library, 575 compiler), 1,212 pending.

Investigation and intermediate replay use local tools. Final acceptance is
one public no-auth HTTPS MCP request covering this verifier and retained
runtime/import proofs, R114 lifetime evidence, authored extents, target and
Ghidra attestation, all 60 cold exact units, CI, progress freshness and diff
whitespace checks. The private URL and investigation logs stay untracked.

## R121 — complete registration, heap growth and thread teardown

The six handoff roots are reviewed against the pinned supplied Japanese
TH075 target. Four roots and six required dependencies gain library origin;
ten complete source bodies cover 917 bytes and 71 typed relocation fields:

| Address | Whole bytes | Vendor source symbol |
| --- | ---: | --- |
| `0x006422B2` | 36 | `_fast_error_exit` |
| `0x00646603` | 85 | `__mtdeletelocks` |
| `0x00646166` | 29 | `__mtterm` |
| `0x0064168B` | 18 | `_atexit` |
| `0x00641653` | 56 | `__onexit` |
| `0x006415AB` | 128 | `__onexit_lk` |
| `0x00646756` | 429 | `_realloc` |
| `0x00646903` | 118 | `__msize` |
| `0x006440D5` | 9 | `__lockexit` |
| `0x006440DE` | 9 | `__unlockexit` |

Replay `scripts/repo-python scripts/verify-startup-registration-origins.py`.
Each complete own source auxiliary extent is extracted from a hash-pinned
VC7.1 archive member and all target bytes and typed fields are compared.
Control-flow inventories retain every exit, embedded cleanup and external
REL32 tail. Every accepted direct code edge closes against another complete
accepted body or nineteen independent anchors / 4,280 bytes / 162 fields;
R120 and retained R115–R119/runtime/import/layout controls cold-replay their
original CFG and shared-data extents. In particular memcpy's whole 829-byte
code/switch carrier and resize's whole 735-byte region/group logic remain
independent accepted evidence, not convenient linear instruction prefixes.

Fast error exit uses the WINCRT0 member proven by earlier complete startup
context. Narrow and wide Windows helper bodies are identical here; the
console startup members differ at non-relocation bytes 6 and 7. Neither a
first symbol hit nor this small helper alone establishes the entry variant.
The function retains the actual mutable error-mode test, full banner/writer
callees and terminal exit dispatcher. Thread teardown compares all 36 lock
records, frees dynamic critical sections first, then deletes preallocated
ones so the heap lock outlives heap frees. The FLS/TLS free dispatch retains
its actual slot, source defining cache and index reset; the complete 239-byte
MT initializer supplies API lookup/raw fallback provenance without receiving
ownership for its unresolved locale cleanup callback.

The full onexit/atexit graph retains the application callback value, growth
policy, failed first/retry realloc paths, preservation of the end offset,
pointer updates and callback store. Complete msize/realloc bodies close both
small-block and system-heap paths against real heap COMMON definitions,
whole new-mode storage, all API slots, resize/copy/free/new-handler children
and SEH labels. Registered callback implementations gain no origin merely
from registration. The genuine onexit initializer and CRT registration
remain independently replayed R120 evidence.

Canonical source extents expand only for onexit `0x00641653` 50 -> 56 and
msize `0x00646903` 106 -> 118. Three existing candidates become library-owned
interior labels, not extra complete source functions: `0x00641685` / 6,
`0x00646970` / 9 and `0x006468BE` / 9. Their 24 bytes overlap accepted parents;
spans and blank names are preserved. Onexit's finally starts +50, msize's
EH head +106 and shared entry +109, realloc's EH head +352 and shared entry
+360. Every label and scope pointer is re-read from its actual primary COFF
section. Database and target bytes are unchanged; no source or exact credit
is granted.

Defining controls include seven whole sections / 480 bytes, five actual
four-byte COMMON definitions, ten four-byte source range markers, five whole
callback ranges / 116 bytes, the four-byte onexit registration, five scopes /
72 bytes, and seven complete export literals / 89 bytes. Writable storage,
loader zero-fill, full source topology, all initialized pointers and literal
extents are checked. The FP carrier is the whole 20-byte source section:
`__FPinit` is +8, not an invented isolated scalar. The whole RTC terminator
scope and empty eight-byte marker range are diagnostic evidence only.

MT initializer `0x00646389` / 239 and cinit `0x0064411D` / 106 stay pending.
Their complete 345-byte source and 38 fields are frozen. MT init still needs
the non-inventoried 327-byte freefls parent's locale data and complete freeing
dependencies. Cinit still needs the actual FP callback's conversion table,
converter implementations and precision-control chain. Seven full contexts /
748 bytes / 63 fields cover freefls, non-inventoried RTC termination, fpmath,
freetlocinfo, cfltcvt initialization, processor-feature probing and default
precision. These footprints do not grant parent/callee origin. The two
existing freefls cleanup entries `0x00646339` / 9 and `0x00646345` / 9 remain
unknown, preserving earlier EH heads +301/+315 and shared entries +306/+318.
The non-inventoried primary bodies are not added to candidate counts.

R115 preserves its historical fast-exit snapshot through a narrow R121
reconciliation guard: same whole member/source/target identity and every
field are required, followed by the original cold replay. Sixteen new tests
reject convenient extents, console-member substitution, arbitrary TLS zeros,
unclosed parent ownership, fabricated diagnostic candidates and exact credit.
All 282 public checks pass. Current origin totals are 3,152 resolved:
919 authored, 1,658 library and 575 compiler; 1,199 remain pending. The exact
baseline stays 60 functions / 9,883 bytes, and recorded authored extents stay
872 bodies / 1,952,956 bytes. Investigation and intermediate checks use local
tools; final acceptance uses one no-auth public HTTPS MCP request. The private
URL and logs remain untracked.

## R122 — complete locale defaults, thread cleanup and initialization

The six handoff candidates are reviewed against the pinned supplied Japanese
TH075 target. Five complete bodies gain library origin / 1,159 bytes / 120
typed fields: freetlocinfo `0x00642B09` / 208, monetary cleanup `0x0064CA47` /
217, numeric cleanup `0x0064C7E8` / 95, time cleanup `0x0064C5C6` / 400 and MT
initializer `0x00646389` / 239. Replay
`scripts/repo-python scripts/verify-locale-thread-origins.py`.

The verifier also closes the complete non-inventoried fiber callback
`0x00646207`, `__freefls@4` / 327 bytes / 21 fields. This is an independently
checked whole source control, not a newly invented candidate. Its two existing
interior candidates `0x00646339` / 9 and `0x00646345` / 9 gain library origin
as source labels, retain blank names and unchanged extents, and add no separate
source or exact bytes. Their 18 bytes overlap the whole parent. Earlier EH
heads are +301/+315, shared entries +306/+318; every source label and pointer
is re-read inside its complete primary COFF section. No canonical boundaries
or database names/types are changed in this batch.

Every complete source auxiliary extent, source member/hash, byte, typed
relocation, branch, exit, callback and API witness is replayed. All code edges
of accepted candidates and the whole fiber control close against complete
accepted bodies or twelve independent anchors / 636 bytes / 44 fields. The
full R121 and retained R120/R119/R118/R117/R116/R115/runtime/import graphs
cold-replay their earlier code, data and layout controls. A matched prefix,
provisional name or correct field offset does not earn ownership.

The locale graph uses ten complete defining source sections / 2,092 bytes,
five genuine four-byte COMMON definitions, two scopes / 36 bytes and
forty-seven full readonly literals / 313 bytes. All initialized data pointers
resolve to a full source definition or literal. Source mutability and actual
PE writable/readonly storage are checked; every BSS/COMMON object retains real
loader zero-fill geometry. No arbitrary zero scalar is substituted.

Whole defining carriers include lconv's 56-byte source section at
`0x006708C8`: decimal string +0, complete 48-byte lconv +4 and global pointer
+52. The empty string is a genuine separate one-byte BSS definition at
`0x0068E684`. The full 403-byte setlocal source section at `0x0066FF20`
contains the initial 84-byte thread locale at +8, current pointer +92 and
cache/static data; its complete four-field initializer is compared. The
entire 1,284-byte readonly ctype/wctype section at `0x006626B0` is compared,
including the actual +256 pctype addend, not a 514-byte slice. The complete
184-byte C-locale time record at `0x00670808` binds all 43 pointer fields to
42 whole literals (May shares one definition). Together with the five FLS
export/kernel literals these give all 47 readonly controls.

The new natural `VC7LocaleThreadLayout.cpp` probe cold-builds a complete
55-DWORD / 220-byte control using pinned CRT/SDK headers and explicit
reproducibility flags. Whole sizes are `_tiddata` 140, `threadmbcinfo` 544,
`threadlocinfo` 84, `lconv` 48 and `__lc_time_data` 184. The actual thread
pointers are +96 multibyte and +100 locale; guesses at the end of the structure
are false. Time refcount is +180; its 7/7/12/12/2 pointer arrays and three
format fields are retained in full. These are complete vendor layouts,
not game class declarations or evidence of one executable-wide compiler
profile. No source body is reconstructed and the exact baseline is unchanged.

Cleanup retains all six actual allocated thread buffer fields, exception-table
sentinel, multibyte/locale refcounts, default/current pointer exclusions,
monetary/numeric shared-string protections, ctype allocation base adjustment,
time fields and both finally unlocks. MT initialization keeps actual FLS
lookup/fallback slots, the TLS index, calloc(1,140), exception/random/thread
initializers and all failure teardown paths. Owning the runtime callback does
not assign origin to application callbacks registered elsewhere.

The multibyte initializer `0x006504F9` / 30 remains pending: its real child
`0x006503A9` has a complete 336-byte source body but a 327-byte provisional
candidate plus nine-byte cleanup `0x006504F0`. The 400-byte `__setmbcp_lk`
context at `0x00650209` still needs complete codepage table, SBCS/case-map and
NLS binding evidence. Both contexts / 736 bytes / 52 fields and the whole
cleanup/scope are frozen without origin or boundary credit. The actual
initialization flag COMMON definition is proven; that alone cannot classify
the initialization or its children.

R121 retains its old pending MT/fiber snapshots through narrowly checked
same-source reconciliation. Complete member/source/target identity and all
fields still replay; accepting an interior additionally requires the complete
R122 locale/thread graph and all five accepted canonical roots. Eighteen new
regression checks reject convenient source/data prefixes, fabricated primary
candidates, guessed layouts, unresolved codepage ownership and exact credit.
All 300 public tests pass. Origin totals are 3,159 resolved (919 authored,
1,665 library, 575 compiler) and 1,192 pending. The 60-function / 9,883-byte
exact baseline and 872 recorded authored bodies / 1,952,956 bytes are preserved.
Investigation and intermediate verification use local tools; final acceptance
uses one no-auth public HTTPS MCP request. Private URLs and logs stay untracked.

## R123 — complete multibyte/codepage, NLS and locale dependency graph

The six handoff roots and nine necessary callee candidates gain library origin:
fifteen complete own source auxiliary bodies / 3,970 bytes / 209 typed fields.
Replay `scripts/repo-python scripts/verify-codepage-nls-origins.py`. Every byte,
relocation, instruction, branch, exit, indirect call and defining code/data/API
binding is checked against the pinned supplied Japanese TH075 target and pinned
VC7 CRT archive. Complete independent R122 and all retained runtime/import/layout
controls cold-replay. Relocation-masked fingerprints alone earn no credit.

| Complete body | Address | Source bytes |
| --- | --- | ---: |
| `___initmbctable` | `0x006504F9` | 30 |
| `__setmbcp` | `0x006503A9` | 336 |
| `__setmbcp_lk` | `0x00650209` | 400 |
| `_setSBCS` | `0x0064FFE5` | 41 |
| `_setSBUpLow` | `0x0065000E` | 396 |
| `___updatetmbcinfo` | `0x0065019A` | 111 |
| `___crtGetStringTypeA` | `0x0064DA08` | 442 |
| `___crtLCMapStringA` | `0x0065275D` | 956 |
| `__resetstkoflw` | `0x006518B9` | 227 |
| `___ansicp` | `0x00651D5F` | 67 |
| `___convertcp` | `0x00651DA2` | 457 |
| `_atol` | `0x00642619` | 136 |
| `___updatetlocinfo` | `0x00642DEB` | 59 |
| `___isctype_mt` | `0x0064980B` | 119 |
| `___updatetlocinfo_lk` | `0x00642BD9` | 193 |

The provisional setmbcp 327, mbc updater 99 and locale updater 50 extents are
reconciled to full source extents 336, 111 and 59. All contain their final cleanup
and return. Existing interior candidates `0x006504F0`, `0x00650200` and
`0x00642E1D` retain nine-byte extents and blank names; they gain library origin
as labels in the complete accepted parents. Their 27 bytes overlap the parents,
not separate whole source functions. The mbc updater's EH head is +99 while its
shared cleanup entry is +102. All source labels and earlier EH heads are checked.
No Ghidra database writes or target patches are made.

The source graph closes through fourteen whole independent anchors / 1,142 bytes /
60 fields. The stack probe callee `__alloca_probe` is the actual same-offset alias
of the complete `__chkstk` source definition; its entire 61-byte body still
replays. The other R006/R115/R117/R118/R120/R122 anchors retain their independent
ownership. No additional credit follows from their presence or caller names.

Twelve full defining source sections / 2,296 bytes, eight actual COMMON objects /
545 bytes, six complete scope tables / 96 bytes and forty-four readonly literals /
267 bytes are verified. The whole mutable 248-byte mbctype carrier includes
four type flags, source alignment and all five 48-byte records for codepages
932/936/949/950/1361. It is not treated as a readonly table or a convenient
single-record prefix. COMMON arrays are exactly mbctype 257, mbcasemap 256 and
mbulinfo 12 bytes; the copied mbulinfo loop in setmbcp retains the source's five
USHORT iterations although the complete storage has six. Undefined references
are never substituted for actual defining COMMON records. Every zero object
retains whole PE loader zero-fill geometry.

The entire 32-byte lc_handle/codepage carrier and 72-byte crt0dat platform/argv/
termination carrier bind their real interior definitions. Whole initial locale,
lconv, ctype/wctype and time defaults retain all initialized pointers and all
42 time literals. Both NLS flavor caches have their own real four-byte defining
BSS objects, not arbitrary zero values. Each NLS member's complete four-byte
wide empty-string COMDAT is checked, even though target folding shares its
address. Every initialized data pointer resolves to a complete source definition
or literal. Source and target mutability are checked independently.

Natural `VC7CodePageLayout.cpp` cold-builds a 43-DWORD / 172-byte control with
pinned CRT/SDK headers and explicit reproducibility flags. SDK sizes are CPINFO
20 (LeadByte +6, twelve bytes), MEMORY_BASIC_INFORMATION 28 and SYSTEM_INFO 36
(page size +4). Codepage records are 48 bytes, six USHORTs +4 and ranges +16;
five records occupy 240 bytes. Complete CRT structures retain multibyte 544 and
locale 84; locale codepage is +4, handle array +12, max width +40 and pctype +72.
The earlier R122 thread/locale/time layout control still cold-replays. SDK NLS,
conversion, platform and guard-page constants are included in full. These are
vendor controls, not reconstructed game layouts or executable-wide flags.

Both ANSI and wide NLS branches, including flavor detection and GetLastError,
whole count handling, size-only conversion, sort-key output, dynamic stack
allocation, all five exception filter/handler pairs, stack recovery, heap
fallback and every cleanup path are retained. Stack recovery binds actual raw
VirtualQuery/GetSystemInfo/VirtualAlloc/VirtualProtect imports and complete SDK
output structures. ANSI codepage lookup binds the actual GetLocaleInfoA buffer,
locale-aware atol and its complete character-classification/update cycle. The
cycle closes through already accepted locale cleanup and whole codepage data;
no circular name assumption substitutes for any code or state definition.

R115 and R122 keep historical pending snapshots through narrowly bounded
same-source guards: complete member/source/target/field identities still match,
and the new canonical accepted extent and classification are required. The
three old provisional boundaries remain recorded in the new evidence manifest.
Twenty-two regression checks reject truncated parents/data/arrays, unreviewed
NLS children, forged aliases, guessed layouts, changed historical fields and
source/exact credit. All 322 public checks pass. Origin totals are 3,177 resolved
(919 authored, 1,683 library, 575 compiler), with 1,174 pending. Exact/source/
mapping stays 60 functions / 9,883 bytes; recorded authored extents stay 872 /
1,952,956 bytes. Investigation and intermediate verification are local; final
acceptance uses one no-auth public HTTPS MCP request. Private URLs/logs stay
untracked. Floating-point startup and PE entry ownership remain pending.

## R124 — Complete floating-point conversion and control graph

R124 resolves 27 existing library candidates / 4,252 complete source bytes /
142 typed relocation fields. The six handoff roots expand only to the necessary
conversion, parser, locale, digit-output and arithmetic dependencies. `__cinit`
remains unknown: completed FP children do not resolve its actual initializer
callbacks. Replay `scripts/repo-python scripts/verify-floating-point-origins.py`;
the evidence manifest is `config/floating-point-origin-evidence.json`.

| Complete source body | Address | Source bytes |
| --- | --- | ---: |
| `__fpmath` | `0x006405C2` | 30 |
| `__cfltcvt_init` | `0x0064057A` | 56 |
| `__ms_p5_mp_test_fdiv` | `0x0064520F` | 41 |
| `__setdefaultprecision` | `0x006451BD` | 18 |
| `__controlfp` | `0x0064FBE8` | 22 |
| `__cfltcvt` | `0x0064516C` | 81 |
| `__fassign` | `0x00644E5F` | 62 |
| `__cftof` | `0x00645070` | 98 |
| `__cftog` | `0x006450D2` | 154 |
| `__cftoe` | `0x00644F68` | 108 |
| `__atodbl` | `0x0064F7B3` | 61 |
| `__atoflt` | `0x0064F82E` | 61 |
| `_tolower` | `0x0064F3E5` | 34 |
| `_isdigit` | `0x00642800` | 58 |
| `___tolower_mt` | `0x0064F31D` | 200 |
| `__fltout2` | `0x0064F99C` | 108 |
| `__cftof2` | `0x00644FD4` | 156 |
| `__cftoe2` | `0x00644EBA` | 174 |
| `___strgtold12` | `0x00652CD1` | 1076 |
| `__ld12tod` | `0x0064F70B` | 22 |
| `__ld12tof` | `0x0064F721` | 22 |
| `_$I10_OUTPUT` | `0x00653151` | 654 |
| `___mtold12` | `0x00652BF3` | 222 |
| `___multtenpow12` | `0x0065418C` | 134 |
| `__shift` | `0x00644E9D` | 29 |
| `___ld12mul` | `0x00653F5A` | 562 |
| `__fptrap` | `0x0064FA08` | 9 |

Every complete own COFF AUX extent, non-relocation byte, typed field, instruction,
branch, exit and indirect dispatch is compared to the pinned supplied Japanese
TH075 target and pinned VC7 CRT archive. The parser at `0x00652CD1` expands from
its provisional 1,028-byte code prefix to the whole 1,076-byte source extent,
ending at `0x00653104`. All twelve DIR32 entries in its embedded 48-byte table
bind actual instruction starts in the same source definition. The real unsigned
`eax <= 11` guard, table reference and indexed dispatch at `0x00652D34` remain
checked. The table is compared as data, not disassembled as instructions.
There are no interior candidate additions, target patches or database writes.

Five whole non-inventoried library controls / 230 bytes / ten fields close
`__cropzeros` (75), `__forcdecpt` (60), `__positive` (26), `__fpclear` (1) and
`__RTC_Terminate` (68). They earn no candidate credit. The one-byte fpclear is
its complete real vendor RET body. RTC termination retains its complete scope,
handler and actual empty two-entry range. Twenty-four whole independent anchors /
3,732 bytes / 131 fields retain their prior origins and cold R123 dependencies.
The complete 50-byte control87 is additionally decoded with its actual
abstract/hardware control-word children; previously accepted mapping helpers
remain independently verified. Identical CRT error-source alternatives preserve
the accepted R120 source identity and do not establish one executable-wide profile.

Twelve entire defining source sections / 2,744 bytes, one 12-byte RTC scope,
six whole CRT range markers / 24 bytes, three observed callback ranges / 92 bytes
and fifty readonly literals / 334 bytes are verified. There are no COMMON
substitutes. The six-slot conversion table / 24 bytes initially points to the
complete nine-byte trap in every slot; registration writes bind each real
converter/format helper, including the shared conversion slot. The whole
20-byte fpinit carrier binds fpmath and both fpclear callbacks. A weaker COMMON
FPinit reference never replaces the actual strong source definition.

The 700-byte powers carrier includes all positive and negative records and
retains its actual mutable source and target storage. Both complete 24-byte
float/double conversion-format records are retained in the whole 48-byte carrier.
The eight-byte division flags and twelve-byte multibyte/decimal-point carrier
retain all defining symbols. Decimal point is the actual character field, not
a guessed pointer. Whole locale, lconv, ctype and time defaults preserve every
initialized pointer and all 42 time literals. Every data pointer resolves to a
complete code definition, defining data object or readonly literal; whole BSS
objects retain PE loader zero-fill geometry.

Two natural independent translation units cold-build 36-DWORD / 144-byte FP
and 13-DWORD / 52-byte locale/API controls with pinned CRT/SDK headers and explicit
reproducibility flags. This avoids the real SDK/vendor DOUBLE typedef conflict
without modifying either header. DOUBLE, LONGDOUBLE and long double are eight
bytes; STRFLT is 16 with offsets 0/4/8/12. Complete exception, denormal, rounding,
precision and default control masks are retained, including 53-bit precision.
Locale remains 84 bytes with clike +36, handles +12 and pctype +72. These controls
are vendor evidence, not reconstructed game layouts or executable-wide flags.

The MP division test binds whole KERNEL32 and IsProcessorFeaturePresent strings,
actual GetModuleHandleA/GetProcAddress imports and the indirect call at
`0x00645230` with feature 0 and four-byte stack ABI. Its complete 64-byte R098
fallback retains independent evidence. Parser classification closes through
complete locale-aware tolower/isdigit, locale updating and digit/long-double
arithmetic definitions; names and masked fingerprints alone earn no credit.

The complete cinit code / 106 bytes and actual XI/XC ranges remain observations.
SSE2 initialization at `0x00648052`, non-inventoried stdio initialization at
`0x0064F08F` and non-inventoried C++ exception-filter registration at `0x0064659A`
still need their full defining dependency graphs. The latter registers the
actual callback at `0x0064654C` via SetUnhandledExceptionFilter; it is not pointer
encoding. R121's frozen cinit snapshot is retained through a narrow same-source
guard requiring the new canonical unknown R124 record. No parent ownership is
inherited from completed children. PE entry remains pending independently.

Twenty-five regression checks reject code-only parser truncation, omitted table
entries, invented local labels/candidates, carrier prefixes, unreviewed children,
guessed masks/layouts/API provenance, changed historical source fields and
source/exact credit. All 347 public checks pass. Origin totals are 3,204 resolved
(919 authored, 1,710 library, 575 compiler), with 1,147 pending. Exact/source/
mapping remains 60 functions / 9,883 bytes; recorded authored extents remain
872 / 1,952,956 bytes. Investigation and intermediate verification are local;
one final no-auth public HTTPS MCP acceptance replay passed R124, retained
runtime/import/layout and R114 dependency graphs, all 872 authored extents,
target/project attestation, 347 tests and all 60 exact units across eleven objects.
A narrow public follow-up confirms corrected documentation EOF whitespace and
progress/status; the complete cold acceptance replay ran once. Private URLs and
logs remain untracked.

## R125 — Complete initializer, IO, exception and signal graph

R125 resolves all six initializer/startup handoff roots and five necessary
exception/signal callees: eleven complete library bodies / 1,545 bytes /
77 typed relocation fields. Existing raise cleanup candidate `0x0065378A` also
receives library origin as a 13-byte overlapping label in its complete parent.
Twelve candidates are resolved, with no standalone cleanup function or invented
inventory entry. Replay `scripts/repo-python scripts/verify-initializer-startup-origins.py`;
whole evidence is in `config/initializer-startup-origin-evidence.json`.

| Complete body | Address | Source bytes |
| --- | --- | ---: |
| `__cinit` | `0x0064411D` | 106 |
| `___sse2_available_init` | `0x00648052` | 206 |
| `_has_osfxsr_set` | `0x0064801D` | 53 |
| `?__CxxUnhandledExceptionFilter@@YGJPAU_EXCEPTION_POINTERS@@@Z` | `0x0064654C` | 78 |
| `__RTC_Initialize` | `0x00649693` | 68 |
| `__ioinit` | `0x00649449` | 510 |
| `?terminate@@YAXXZ` | `0x00646478` | 53 |
| `?_ValidateExecute@@YAHP6GHXZ@Z` | `0x0064FF58` | 24 |
| `_abort` | `0x00650517` | 24 |
| `_raise` | `0x0065364F` | 377 |
| `_siglookup` | `0x0065346E` | 46 |

Every own source COFF AUX extent, source/target byte, typed relocation,
instruction, branch, return, trap, tail and indirect call is retained against
the pinned supplied Japanese TH075 target and pinned VC7 CRT archive.
All provisional primary extents already equal their full source definitions;
none is truncated to improve a comparison. Abort retains its own terminal INT3.
Raise retains the earlier EH head at +307 and actual shared cleanup entry +315,
including the internal call to that entry and whole finally path. The existing
13-byte label keeps a blank proposed name and does not become a standalone body.
No game source/header, exact ledger, target or Ghidra database is changed.

The complete 106-byte cinit is now library-owned through its actual closed
FP/XI/XC/RTC graph. Six whole source registration cells / 24 bytes bind onexit,
SSE2, stdio, multibyte, C++ exception-filter and security-cookie callbacks.
Whole XI/XC and both RTC ranges / 100 bytes retain their actual pointers;
eight complete source range markers / 32 bytes preserve CRT subsection identity.
Both RTC ranges have only their two null marker cells. Seventeen full prior
vendor anchors / 1,286 bytes / 98 fields retain independent cold R124 evidence.
The whole FPinit carrier retains its real strong source definition and both
fpclear pointers. Parent credit follows from the completed graph, not names,
registration pointers or relocation-masked fingerprints alone.

Two newly closed non-inventoried controls are initstdio `0x0064F08F` / 169 bytes /
13 fields and C++ filter registration `0x0064659A` / 19 bytes / three fields.
Two earlier R124 controls, fpclear / one byte and RTC termination / 68 bytes /
five fields, also replay completely. These four controls / 257 bytes / 21 fields
add no inventory candidates. Registration binds actual SetUnhandledExceptionFilter
and its returned prior-handler storage. The complete 78-byte callback verifies
C++ exception code, three parameters and both observed magic values before
terminate, then validates and dispatches to any previous handler. Optional
external handler implementations retain unknown ownership.

All eleven XC compiler wrappers / 309 bytes retain their exact R024 evidence
rows and independently reviewed compiler origins. The established natural
VC7StaticLifetime fixture cold-builds with its original explicit profile and
source/header hashes. Its complete emitted wrapper families and every actual
startup/registration/object/callee field replay through verify-static-origins.
The generic CRT runner does not classify those wrappers' game callees or
establish original object types. No existing compiler or authored origin credit
is changed or counted again.

Six entire defining source sections / 824 bytes, seven actual COMMON objects /
4,372 bytes, five whole EH scopes / 60 bytes and the complete 13-byte AuthenticAMD
literal close the graph. The whole twenty-record iob carrier / 640 bytes keeps
both stdin buffer pointers and all initial flags/file fields. The real stdin
buffer COMMON is 4,096 bytes; the complete pioinfo COMMON has 64 pointers /
256 bytes. Separate four-byte SSE2 COMMON definitions remain separate objects.
Every COMMON has its actual defining record and complete PE loader zero-fill
geometry, not an undefined reference or arbitrary zero region. The whole
20-byte signal-action section includes all four actions and its control-handler
installation flag. The entire 136-byte exception-action carrier includes ten
12-byte records and four count/size/FPE-index fields; no record-only prefix is
accepted. All initialized pointers bind complete definitions.

Natural VC7InitializerLayout cold-builds 73 DWORDs / 292 bytes with pinned
CRT/SDK headers and explicit reproducibility flags. IOINFO is 36 bytes with
handle +0, flags +4, pipe character +5, lock-init +8 and critical section +12;
32 records occupy 1,152 bytes and the maximum handle count is 2,048. FILE is
32 bytes with file +16; twenty records occupy 640 bytes. STARTUPINFOA is 68
with reserved count +50 and buffer +52. Full file, stream, signal and SDK
constants retain their vendor values. Thread data is 140 bytes with terminate
+108 and exception table/info/FPE fields +84/+88/+92. Exception actions are
12 bytes; EXCEPTION_RECORD is 80 with parameter count +16 and information +20,
and EXCEPTION_POINTERS is eight bytes. These are vendor controls, not game
layouts or executable-wide compiler settings.

IO initialization retains every inherited-handle allocation, bounded copy,
pipe/API guard, standard-handle lookup, type flag, critical-section path,
allocation failure and cleanup exit. Stdio initialization retains the 512-stream
allocation, 20-stream fallback, failure result and all initial stream/handle
bindings. SSE2 detection retains CPUID availability, its actual feature bit,
OSFXSR movapd probe and local exception filter/handler, full AMD comparison
and family policy. Terminate retains the actual thread callback and caught
exception path before its abort tail. Raise preserves global/per-thread actions,
signal-lock finally cleanup, default/ignore cases, FPE two-argument dispatch,
other one-argument handlers and temporary exception/FPE-state restoration.

R121 and R124 preserve frozen pending cinit observations through narrowly bounded
same-source guards requiring the new complete canonical R125 library record.
Every original member, extent, byte and typed field identity remains checked;
the earlier evidence manifests are not rewritten. Twenty-five regression checks
reject truncated functions/carriers/COMMON, missing callbacks, invented cleanup
credit, guessed offsets, changed historical fields and exact credit. All 372
public checks pass. Origin totals are 3,216 resolved (919 authored, 1,722 library,
575 compiler), with 1,135 pending. Exact/source/mapping stays 60 / 9,883 bytes;
recorded authored extents stay 872 / 1,952,956 bytes. One final no-auth public
HTTPS MCP acceptance replay passed R125 and all retained runtime/compiler/import/
layout graphs, R114 dependencies, authored extents, target/project attestation,
372 tests, progress freshness and git diff whitespace. All 60 exact units
cold-replayed across eleven objects. Investigation and intermediate verification
are local. PE entry remains pending until environment, argv, exception filtering
and other actual startup bindings close. Private URLs/logs remain untracked.

## R126 — Complete environment, command-line and PE startup graph

R126 resolves the six environment/PE-startup handoff roots and five necessary
parser, multibyte and exit wrappers: eleven complete library candidates /
2,033 bytes / 100 typed relocation fields. The supplied executable's entire
469-byte PE entry is now library-owned. Replay
`scripts/repo-python scripts/verify-environment-startup-origins.py`; the whole
manifest is `config/environment-startup-origin-evidence.json`.

| Complete source body | Address | Bytes |
| --- | --- | ---: |
| `_WinMainCRTStartup` | `0x0064232C` | 469 |
| `___crtGetEnvironmentStringsA` | `0x00649327` | 290 |
| `__setargv` | `0x00649285` | 162 |
| `__setenvp` | `0x00649052` | 199 |
| `__wincmdln` | `0x00648FF5` | 93 |
| `__XcptFilter` | `0x00648E76` | 356 |
| `_parse_cmdline` | `0x00649119` | 364 |
| `__ismbblead` | `0x006515F3` | 17 |
| `_exit` | `0x0064424A` | 17 |
| `__cexit` | `0x0064426C` | 15 |
| `_x_ismbbtype` | `0x0065152C` | 51 |

Every accepted primary retains its complete own COFF AUX extent, all source and
target bytes, typed fields, instructions, branches, exits, local exception
filter/handler and indirect calls. All provisional extents already equal their
full source definitions; no comparison is shortened. The whole 15-byte c_exit
at `0x0064427B` has no independent inventory candidate and adds no origin count.
Nineteen complete independently reviewed vendor anchors / 2,675 bytes / 173
fields replay through the retained R125 chain. The stack-probe call retains the
actual same-source chkstk/alloca alias. Identical archive alternatives for
amsg_exit and fast_error_exit preserve the previously selected wincrt0 member;
this does not establish one executable-wide compilation profile.

The startup entry validates both PE32 and PE32+ managed-image paths. Its actual
GetModuleHandleA import is loaded into EDI before both register calls; DOS/NT
signatures, optional-header magic, directory count and CLR directory address
checks remain complete. All heap/thread/RTC/IO/cinit/environment/argv children
and normal/managed/exception exit paths close independently. The actual
WinMain@16 call binds `0x00602A60`: its full 2,987-byte game-policy body, scene
switch and stdcall return of 16 bytes retain independent R113 authored evidence
through R114. A generic CRT entry does not grant vendor ownership to that game
callee, determine the game's original types or create exact reconstruction.

Environment acquisition retains the four-byte flavor cache, double-null wide
and ANSI extents, ERROR_CALL_NOT_IMPLEMENTED fallback, both WideCharToMultiByte
passes and every allocation/API cleanup exit. Raw import names remain exact,
including GetEnvironmentStrings without an A suffix. Setenvp preserves skipped
'=' entries, the complete pointer array, each copied string, allocation-failure
paths, environment initialization and source-buffer cleanup. Setargv retains
its full 261-byte program-name buffer, two calls to the complete standard
364-byte parse_cmdline, counts, argv/string allocation and null terminator.
The alternative 405-byte wildcard parser is independently re-read and rejected
for differing non-relocation bytes; its prefix earns no credit. The parser
keeps quoted program names, backslash/quote parity, doubled quotes, DBCS lead
bytes and both count-only/output modes. Lead-byte helpers retain the whole
257-byte mbctype object, its +1 indexing and mask 4.

Seven complete defining sections / 1,777 bytes include the 72-byte startup state,
12-byte environment-pointer/error-mode BSS, four-byte flavor cache, 261-byte
program-name BSS, eight-byte ctype pointers, entire 1,284-byte narrow/wide ctype
carrier and 136-byte exception-action/count carrier. Four actual COMMON objects /
269 bytes retain their defining records and complete loader zero-fill geometry.
Acmdln's selected COMMON and aenvptr's selected strong section belong to the
complete matching wincrt0 member; all actual context alternatives are enumerated
and verified. No four-byte environment prefix, undefined COMMON reference or
arbitrary zero region substitutes for a defining object. All ctype pointers
retain their actual symbols and addends. Startup's full 12-byte scope binds
both local filter and handler labels; the complete one-byte empty command-line
literal is also checked.

The full exception filter scans all ten 12-byte actions using the thread's
actual +84 table pointer and the carrier's count/size/index fields. It retains
default UnhandledExceptionFilter dispatch, ignore/die cases, all seven FPE
mappings, one-/two-argument handler ABI, clearing actions and restoration of
thread exception-information/FPE state at +88/+92. Optional installed handler
implementations remain unknown; generic dispatch does not assign their origins.

Natural VC7EnvironmentStartupLayout cold-builds 55 DWORDs / 220 bytes with
pinned CRT/SDK headers and explicit reproducibility flags. Controls include
32-bit pointer and two-byte wchar_t, 260-character API limit with a 261-byte
buffer, CP_ACP/120 fallback, OSVERSIONINFOA / 148 and STARTUPINFOA / 68 with
flags +44/show +48. DOS e_lfanew is +60; NT optional headers start +24.
PE32/PE32+ directory counts are +116/+132 and CLR addresses +232/+248.
Both magic values, signatures, directory index 14, thread/action layouts,
FPE constants and exception results retain vendor definitions. The public
mbctype header is incomplete; its 257-element bound comes from the independently
verified whole COMMON definition, not sizeof an incomplete declaration.

Frozen R114 PE-entry and R115 command-line/context observations remain intact.
Narrow guards require their original complete bytes, extents, source identities,
fields and instruction provenance plus the new canonical R126 library record.
Twenty-four regression checks reject truncated paths/data/COMMON, fabricated
c_exit credit, missing source aliases, guessed PE32+ offsets, changed historical
fields, substituted parser versions and ownership inferred from a WinMain name.
All 396 public checks pass. Canonical totals are 3,227 resolved (919 authored,
1,733 library, 575 compiler), with 1,124 pending. Exact/source/mapping remains
60 / 9,883 bytes; authored extents remain 872 / 1,952,956 recorded bytes.
One final no-auth public HTTPS MCP acceptance replays R126, retained R125 and
R114/runtime/compiler/game/import/layout graphs, all recorded authored extents,
project attestation, progress freshness, 396 tests and git diff whitespace.
All 60 exact units cold-replay across eleven objects. Investigation and
intermediate checks are local. Target/database/tool installations and game
source/headers are unchanged; private URLs, logs and vendor bytes stay untracked.

## R127 — Complete x87 dispatch and IEEE exception graph

R127 resolves all six floating-point dispatch handoff candidates and their
necessary graph: nineteen complete library primaries / 2,608 bytes / 56 typed
fields, plus four existing interior candidates / 350 overlapping bytes. Replay
`scripts/repo-python scripts/verify-fp-dispatch-origins.py`; the complete manifest
is `config/fp-dispatch-origin-evidence.json`. No source, mapping or exact units
are added. All source members come from the pinned VC7 libcmt.lib archive.

| Complete source body | Address | Bytes |
| --- | --- | ---: |
| `__trandisp1` | `0x00646980` | 103 |
| `__trandisp2` | `0x006469E7` | 140 |
| `__convertTOStoQNaN` | `0x00646B7C` | 25 |
| `__math_exit` | `0x00646BFB` | 42 |
| `__startTwoArgErrorHandling` | `0x00646CE0` | 23 |
| `__87except` | `0x006505CA` | 248 |
| `__startOneArgErrorHandling` | `0x00646CF7` | 60 |
| `__cintrindisp2` | `0x006489F0` | 62 |
| `__cintrindisp1` | `0x00648A2E` | 61 |
| `__ctrandisp1` | `0x00648C01` | 51 |
| `__ctrandisp2` | `0x00648A6B` | 406 |
| `__handle_exc` | `0x00646FD8` | 548 |
| `__raise_exc` | `0x00646D33` | 677 |
| `__set_errno` | `0x006471FC` | 40 |
| `__matherr` | `0x006506C2` | 3 |
| `__set_statfp` | `0x00647722` | 86 |
| `__statfp` | `0x006476E7` | 11 |
| `__clrfp` | `0x006476F2` | 12 |
| `_atan2` | `0x00642240` | 10 |

Each primary keeps its own complete COFF AUX extent, all source/target bytes,
typed fields, instruction starts, local branches, external transfers, indirect
jumps, exits and x86 ABI. The provisional 72-byte ctrandisp2 extent expands to
its full 406-byte source definition; it includes both existing shared exits.
Seven independently reviewed whole anchors / 462 bytes / 17 fields retain
original R006/R098/R120 origins and replay through the complete R126 chain.

Three necessary full auxiliary controls / 393 bytes / eight fields have no
independent inventory candidate: CIatan2 at `0x0064224A` / 10, the NaN/numeric
primitive owner at `0x00646A73` / 215, and the atan/trig primitive owner at
`0x00648940` / 168. They earn no candidate count. Four existing candidates gain
interior-entry origin only: rtchsifneg `0x00646B43` / 7 at primitive offset 208,
ctranexit `0x00648AB3` / 7 at ctrandisp2 offset 72, cintrinexit `0x00648ABA` / 327
at offset 79, and rtpiby2 `0x006489AC` / 9 at atan-owner offset 108. Their names
remain blank and overlapping bytes earn no standalone reconstruction credit.

Both actual atan2 callers load EDX with the complete 80-byte OP_ATAN2 table
before typed REL32 tails to the C/intrinsic dispatchers. Its operation is 16,
argument count is two and all sixteen DIR32 code entries retain actual defining
source labels, member/section/offset and complete owners. The 16-byte XAM tag
classifier, FXAM/control-word/status handling, XLAT, signed index conversion,
two-argument AH-shift/AL combination and both actual JMP [EBX] tails remain
complete. Same-section shared branches bind their own source-relative target
and actual full owner; they are not invented relocation fields. The two-argument
error entry shares the one-argument owner's offset-nine tail. Generic caller
supplied tables do not classify hypothetical custom callees or game types.

Eleven complete defining data sections / 336 source bytes retain all definitions
and fields. Two distinct eight-byte zero COMDAT definitions fold to one actual
target, leaving 328 unique target bytes; source identities remain distinct.
Controls include the 44-byte indefinite/pi/one/tag carrier, 68-byte common math
constants, 48-byte C-dispatch constants, 40-byte exception constants, 24-byte
over/underflow constants, four-byte security cookie, four-byte matherr flag,
eight-byte fastflag/adjust_fdiv BSS and complete atan2 table. Member-local One
symbols in different archive members remain distinct. Initialized sections
compare completely with typed code pointers; readonly/writable PE geometry and
BSS loader zero-fill provenance are checked. No zero prefix identifies a state.

The full exception graph preserves status/mask, precision/rounding, domain/range/
inexact paths, the default zero matherr flag and zero-return handler, errno,
thread state, IEEE operand/result records and restored control state. The actual
RaiseException import at `0x00657184` retains its complete 16-byte API argument
ABI and exception-code/parameter provenance. Optional user handlers remain
unknown; generic matherr dispatch grants no ownership to their implementations.

Natural VC7FPDispatchLayout cold-builds one whole 352-byte readonly section with
hash-pinned CRT/SDK headers and explicit reproduction flags. It emits 49 DWORD
layout/constants controls, a four-byte flags object, a 32-byte value and a
112-byte IEEE record. The compiler's eight-byte alignment gap after the flags
object is verified as emitted storage, not source padding or a twelve-byte type.
Controls retain four-byte pointers, FP80 / 10, FP128 / 16, exception structure /
32, IEEE Cause/Enable/Status at +4/+8/+12 and Operand1/Operand2/Result at
+16/+48/+80. Natural aggregate initializers verify exception flags, valid/format
bitfields, 53-bit precision and atan2 operation bits against emitted bytes.
These vendor layouts do not establish a game class or original compiler flags.

Thirty-one regression checks reject truncated shared owners, fabricated
auxiliary candidates, wrong source entries, substituted tables/classifiers,
incorrect argument/index protocol, missing data carriers, member-local symbol
confusion, undefined data references and guessed IEEE layouts. All 427 public
checks pass. Canonical totals are 3,250 resolved (919 authored, 1,756 library,
575 compiler), with 1,101 pending. Exact/source/mapping remains 60 / 9,883 bytes;
authored extents remain 872 / 1,952,956 recorded bytes.
One final no-auth public HTTPS MCP acceptance replays R127, retained R126 and
its complete runtime/compiler/game/import/layout graphs, all authored extents,
project attestation, progress freshness, 427 tests and git diff whitespace.
All 60 exact units cold-replay across eleven objects. Investigation and
intermediate checks are local. Private evidence stays untracked; target,
database, shared tool installations and game source/headers are unchanged.

## R128 — Complete elementary math parents and shared entries

R128 resolves all six trigonometric/square-root handoff candidates and the
three necessary existing C entries: three complete library primaries / 534
bytes / 41 typed fields and six interior candidates / 474 overlapping bytes.
Replay `scripts/repo-python scripts/verify-elementary-math-origins.py`; the
manifest is `config/elementary-math-origin-evidence.json`. All definitions come
from the hash-pinned VC7 libcmt.lib archive. No source, mapping or exact credit
is added.

| Complete source primary | Address | Original bytes | Whole AUX bytes | Fields |
| --- | --- | ---: | ---: | ---: |
| `__CIcos` | `0x00641740` | 20 | 174 | 14 |
| `__CIsin` | `0x006417F0` | 20 | 174 | 14 |
| `__CIsqrt` | `0x00641E40` | 20 | 186 | 13 |

Each twenty-byte provisional prefix expands to its full own COFF AUX extent.
All target/source bytes, typed fields, instructions, branches, exits and ABI
are verified. Intrinsic entries reserve twelve stack bytes, save ST(0), call
the independently reviewed classification helper and call their shared
computation at owner +29; they then release twelve bytes and return. The
C entries at owner +20 load EDX from ESP+4, call the independently reviewed
fload_withFB and fall through to the same computation. EFLAGS/EAX from those
complete helpers remain part of the input protocol.

| Existing entry | Address | Overlapping bytes | Whole owner offset |
| --- | --- | ---: | ---: |
| C cos | `0x00641754` | 9 | 20 |
| Shared cos computation | `0x0064175D` | 145 | 29 |
| C sin | `0x00641804` | 9 | 20 |
| Shared sin computation | `0x0064180D` | 145 | 29 |
| C sqrt | `0x00641E54` | 9 | 20 |
| Shared sqrt computation | `0x00641E5D` | 157 | 29 |

The three C entries have actual global source definitions at offset 20.
The shared computation entries have no independent COFF symbol; their
provenance comes from the full source primary's actual relative call at +11,
the target's corresponding call, C-entry fallthrough and instruction starts.
No invented definition or shortened comparison replaces this evidence.
All six proposed names remain blank and overlap adds no standalone source or
exact bytes. The complete thirteen-byte fast_exit at `0x00646BEE` has no
inventory candidate and earns no origin count. It preserves its actual
control-word restoration and return from the saved stack state.

Cos/sin preserve both FCOS/FSIN paths, the entire FPREM1 range-reduction loop,
status/control-word handling, NaN conversion and invalid-input handling.
Sqrt preserves the full sign, exponent/mantissa and low-word checks, signed
zero, positive infinity, NaN and invalid negative paths. All three retain
both actual fastflag dispatches, normal math_exit and complete one-argument
error handling. Normal and error paths pass operation 18 (cos), 30 (sin) or
5 (sqrt). No indirect call/jump is introduced; every external transfer binds
its actual typed source relocation and whole independent callee.

Six complete defining data sections / 136 bytes include the 68-byte common
constant carrier, eight-byte fastflag/adjust_fdiv BSS, 44-byte indefinite/pi/
classifier carrier and the three member-local name sections. Cos and sin
names are four bytes each; sqrt's complete defining section is eight bytes,
including its compiler-emitted zero suffix. The identical `_NAME_` spellings
retain distinct archive members and actual addresses `0x0066FED0`,
`0x0066FEE0`, `0x0066FEF0`. Default control word binds the common carrier +8;
the full ten-byte pi_by_2_to_61 starts +10. All initialized bytes, symbol
definitions, readonly/writable target geometry and loader BSS are verified.
A two-byte word or string prefix does not substitute for its whole section.

Six independent complete anchors / 239 bytes / three fields preserve original
R006, R107 and R127 ownership. The verifier retains the full R127 dispatch/
exception/runtime/game/import graph and independently replays R107's complete
runtime leaves. Original archive/compiler profiles remain unknown.

Natural VC7ElementaryMathLayout cold-builds twelve DWORDs / 48 bytes with
pinned vendor/SDK headers and explicit reproduction flags. It verifies pointer
4, double 8, FP80 10, exception structure 32 with type/arg1/arg2/retval at
+0/+8/+16/+24, domain value 1 and all three actual operation codes. This probe
contains complete vendor types only and establishes no game class layout.
The x87 control word 0x027f is independently observed in full source, the
actual common constant definition and target instructions; it is not inferred
from the public floating-point control API's differently encoded flags.

Twenty-six regression checks reject truncated primaries/data, fabricated
fast-exit credit, wrong parents/entries, guessed names/operation codes/stack
sizes, removed range/sign paths, lost source-call/fallthrough evidence and
member-local name confusion. All 453 public checks pass. Canonical totals
are 3,259 resolved (919 authored, 1,765 library, 575 compiler), with 1,092
pending. Exact/source/mapping remains 60 / 9,883 bytes; recorded authored
extents remain 872 / 1,952,956 bytes.
One final no-auth public HTTPS MCP acceptance replays R128, retained R127/R107
and complete runtime/compiler/game/import/layout graphs, authored extents,
project attestation, progress freshness, 453 tests and git diff whitespace.
All 60 exact units cold-replay across eleven objects. Local investigation
precedes one final public acceptance request. Target, database, shared tools
and game source/headers remain unchanged; private evidence stays untracked.

## R129 — Complete short runtime, FP exception and array destruction graph

R129 reviews all six handoff candidates. Five gain library origin; abs remains
unknown because complete vendor and ordinary expression alternatives are
indistinguishable. Four necessary complete callees also gain library origin:
eight primaries / 839 bytes / 38 typed fields and one existing interior cleanup /
24 overlapping bytes. Replay `scripts/repo-python scripts/verify-short-runtime-origins.py`;
the manifest is `config/short-runtime-origin-evidence.json`. No source, mapping
or exact credit is added. All vendor definitions come from pinned libcmt.lib.

| Complete source primary | Address | Whole bytes | Fields |
| --- | --- | ---: | ---: |
| `_srand` | `0x0064189E` | 13 | 1 |
| `_rand` | `0x006418AB` | 34 | 1 |
| `_fabs` | `0x006418CD` | 177 | 8 |
| `??_M@YGXPAXIHP6EX0@Z@Z` | `0x00641D4A` | 96 | 4 |
| `?__ArrayUnwind@@YGXPAXIHP6EX0@Z@Z` | `0x00641CEC` | 94 | 4 |
| `__except1` | `0x006473C1` | 184 | 9 |
| `__handle_qnan1` | `0x0064730F` | 83 | 4 |
| `__umatherr` | `0x00647271` | 158 | 7 |

Seven primaries retain their entire own COFF AUX extents. The vector destructor
has no function-definition AUX record: its sole global function starts at zero
in a complete 96-byte defining code section. The verifier derives that extent
from the actual source header, requires executable/readable/non-writable code,
checks every definition and rejects a second global function or fabricated AUX.
The original 72-byte prefix expands to include its full cleanup. All code,
fields, instructions, local/external branches, exits and callback sites are
compared. ArrayUnwind expands from its provisional 47 bytes to its own full
94-byte AUX body, including filter/termination paths; neither comparison is
shortened. The existing 24-byte candidate `0x00641D92` is the vector owner's
source-defined local cleanup at +72. Its name remains blank and overlap earns
no standalone source or exact bytes.

Rand/srand both bind the complete independently reviewed getptd return and its
vendor holdrand field at +20. The generator updates the same unsigned 32-bit
state with multiplier 214013 and increment 2531011, shifts right 16 and masks
32767. The complete vendor thread layout is 140 bytes. Seed stores, calling
convention and returns remain complete; a thread-field guess alone is insufficient.

Fabs retains normal, special-value, quiet/signaling NaN and exception exits,
all control-word changes/restoration, its entire double-one constant and both
operation-21 transfers. Except1, handle_qnan1 and umatherr close through the
full reviewed status/raise/errno/default-matherr graph. The complete 29-entry
operation/name table is 232 bytes with all 29 DIR32 string pointers. Every whole
string COMDAT is verified: 29 definitions / 151 bytes. The full table scan,
matched/unmatched operation paths, exception record, default handler and errno
policy remain intact. No table prefix, guessed name or undefined reference
substitutes for its defining object.

Thirty-five complete data sections / 423 bytes / 32 typed fields include that
table and all strings, two full twelve-byte SEH scopes, double-one, security
cookie and matherr flag. The scopes bind the vector cleanup at +72 and actual
ArrayUnwind filter/handler labels at +47/+83. Readonly geometry is checked
after every typed field is linked; unrelocated scope bytes are not scalar
literals. Each field retains its own defining source member/section/offset.
Fourteen independent whole anchors / 1,762 bytes / 43 fields preserve original
runtime origins through the complete retained R128 graph.

Both array helpers preserve signed reverse-count traversal, element-address
updates, ECX receiver and the incoming callback at EBP+20. The vector normal
path marks completion before its local finally; the exceptional path invokes
the complete ArrayUnwind over the remaining elements. ArrayUnwind's full
exception filter/termination path and stdcall cleanup of sixteen bytes remain
inside its own source definition. Arbitrary incoming destructor implementations
and original game element types remain unknown and gain no origin credit.

Natural VC7ShortRuntimeLayout cold-builds twenty DWORDs / 80 bytes using pinned
complete vendor/SDK types. Controls include pointer/int/long / four bytes,
thread size/seed offset 140/20, RAND_MAX, exception structure / 32, FP80 / 10,
fabs operation 21 and SEH results. The eight-byte operation/name pair is an
explicit synthetic layout control, not an asserted private vendor type. A
complete synthetic single-inheritance class and member pointer emit a full
thirteen-byte callback control: ECX receiver, actual indirect call and stdcall
cleanup eight. No game owner is instantiated or embedded; this verifies the
calling protocol without claiming an original callback type or class layout.

The eleven-byte `0x00641DAA` remains unknown. Both entire abs/labs AUX definitions
match every target byte with no fields. Natural VC7AbsOriginAlternatives at
explicit /O1 emits the same complete eleven bytes from ordinary int and long
absolute-value expressions. Even whole independently reviewed runtime neighbors
and actual game callers do not distinguish authored versus library ownership,
original spelling, int/long selection or folding. The canonical pending record
retains that evidence and gains no name, source, mapping or exact credit.
The verifier cold-builds both full expressions on every replay; a masked hit
or library-neighbor name cannot erase this ownership ambiguity.

Thirty regression checks reject truncated code/data/scopes, invented AUX or
cleanup credit, wrong table fields, seed/operation/callback provenance and
promoting the abs lookalike. All 483 public checks pass. Canonical totals are
3,268 resolved (919 authored, 1,774 library, 575 compiler), with 1,083 pending.
Exact/source/mapping remains 60 / 9,883 bytes; recorded authored extents remain
872 / 1,952,956 bytes. One final no-auth public HTTPS MCP acceptance replays
R129 and the complete retained R128/runtime/compiler/game/import/layout chain,
all authored extents, project attestation, progress freshness, 483 tests and
git diff whitespace. All 60 exact units cold-replay across eleven objects.
Investigation and intermediate checks are local. Private evidence stays
untracked; target, database, shared tools and game source/headers are unchanged.

## R130 — Complete vector construction and multi-entry math parents

R130 resolves all six handoff candidates and eight necessary existing dependencies:
eleven complete library primaries / 2,511 bytes / 99 typed fields, plus three
existing interior entries / 644 overlapping bytes. Replay
`scripts/repo-python scripts/verify-vector-math-parent-origins.py`; the manifest
is `config/vector-math-parent-origin-evidence.json`. This is origin evidence,
with no new source, mapped function or exact unit. Source associations identify
hash-pinned libcmt.lib definitions; they do not recover executable debug names.

| Complete source primary | Address | Whole bytes | Fields |
| --- | --- | ---: | ---: |
| `??_L@YGXPAXIHP6EX0@Z1@Z` | `0x00641C78` | 98 | 4 |
| `__handle_qnan2` | `0x00647362` | 95 | 4 |
| `__except2` | `0x00647479` | 201 | 9 |
| `_log10` | `0x00641FD0` | 63 | 2 |
| `_ceil` | `0x00642120` | 64 | 3 |
| `__CIlog10_pentium4` | `0x00648140` | 644 | 21 |
| `___libm_error_support` | `0x006485D7` | 654 | 28 |
| `__ceil_default` | `0x00648865` | 211 | 9 |
| `__powhlp` | `0x0064E81E` | 354 | 15 |
| `__d_inttype` | `0x0064E7B0` | 110 | 4 |
| `__frnd` | `0x0065151B` | 17 | 0 |

**Target and source extents.** Ten primaries retain their own full COFF AUX
extents. The vector constructor lacks a function-definition AUX record; its
sole global function owns a complete 98-byte executable/readable/non-writable
section. All source definitions and four fields are verified. Its provisional
74-byte prefix expands through the actual local cleanup at +74, including the
normal finally call and exceptional unwind. The existing 24-byte cleanup
`0x00641CC2` binds actual source label `$L322`, the full twelve-byte scope at
`0x00660F00`, and independently replayed 94-byte ArrayUnwind. It gains no
standalone function name, source or exact bytes.

The mathematical prefixes are accepted only after comparing their entire
emitted code sections, every complete constituent AUX body and all alignment.
The log10 section is 336 bytes: C entry / 63, source-emitted NOP / 1,
`__CIlog10` / 59 and `__CIlog10_default` / 213. The vendor alignment marker
`_$$$00002` has a zero-length AUX; it is not invented as a one-byte function.
The default body includes actual global entry `__log10_default` at +20.
The complete ceil section is 285 bytes: C entry / 64 and SSE body
`__ceil_pentium4` / 221. Both entire sections and all eighteen/ten fields replay
before the canonical C extents are reconciled from provisional 152/285 to
own-AUX 63/64. No prefix-only match earns origin. The target FID cos association
at `0x00641FD0` is rejected; the actual whole LOG10 data definition at
`0x0066FF00` and full shared code identify the log10 source family.

Whole alternatives retain distinguishing evidence: atan / 282 has 74
non-field differences, log / 336 has three, modf / 328 has 223, and floor / 289
has 33. Equal-shaped C prefixes cannot substitute for complete source bodies.
Their fields remain excluded only for this negative diagnostic comparison;
accepted source bodies compare every typed field against independent actual
code/data provenance.

**Shared entries and ABI.** The log10 SSE intrinsic expands from 24 provisional
bytes to its own complete 644-byte AUX, including all computation and error
paths. Existing C entry `0x00648158` / 6 binds global `__log10_pentium4` at +24.
The existing unnamed 614-byte core `0x0064815E` starts at +30: the intrinsic's
actual same-section call at +17 targets it, and the six-byte MOVLPD C-entry
instruction falls through to it. No source symbol is invented for this core.
Both entries retain blank proposed names and overlap adds no standalone bytes.
All intra-body branch destinations and all external typed/shared transfers
must reach instruction starts in complete defining owners.

The vector constructor uses ECX as the element receiver, callback at EBP+20,
signed count at EBP+16 and stride at EBP+12. Its exceptional cleanup passes the
current element pointer, completed-element count and separate incoming destructor
at EBP+24 to reverse unwind; normal completion suppresses that work. RET 20
retains its five-argument stdcall protocol. Arbitrary incoming callbacks and
original game element types remain unknown. Qnan2 retains both double operands
at EBP+12/+20 and the control word at +28. Except2 retains operands +16/+24,
result +32 and control word +40, including every mask/raise/errno/restoration
path. Their full exception/name/default-handler graph is retained through R129.

**Dependency closure.** Nine complete auxiliary bodies / 2,723 bytes / 51 fields
include both log10 intrinsic/default entries, the ceil SSE body, fast_exit,
complete x87 primitives / 215, exponential dispatch / 519, safe_fdivr / 21,
fdiv_main_routine / 279 and adj_fdiv_r / 1,183. These unlisted source controls
do not invent inventory candidates. The existing seven-byte `__rtchsifneg`
entry `0x00646B43` retains its original R127 acceptance at primitive +208;
it is replayed without being counted again. Twenty-one independent complete
anchors / 2,430 bytes / 57 fields retain their historical origins and the full
R129/runtime/compiler/game/import chain.

Twenty-nine whole defining data sections / 3,133 bytes / 70 typed fields
include the complete 2,336-byte log10 coefficient carrier, 72-byte ceil constants,
full literals, scope, cookie, fast flags and initialized default callback.
`__pmatherr` at `0x0067064C` contains the actual DIR32 pointer to complete
three-byte `__matherr` at `0x006506C2`; it is not null loader state. All three
indirect libm error calls use that slot. Later installed callbacks remain
unknown. The full 90-byte infinity/EXP carrier has four code pointers and
requires the complete exponential owner and pow helpers. The full 352-byte
fdiv carrier retains all 64 DIR32 dispatch entries to actual labels inside
complete adj_fdiv_r; the safe wrapper's unrelocated same-section call retains
complete fdiv_main_routine. A ten-byte infinity or 21-byte safe-wrapper hit
alone is insufficient. One four-byte SSE2-enable COMMON has its complete source
definition and actual loader zero-fill geometry; no guessed initial value or
truncated table substitutes for the defining storage.

**Compiler observations and limits.** Natural VC7VectorMathParentLayout
cold-builds thirteen DWORDs / 52 bytes from complete pinned vendor/SDK types:
pointer/int / 4, double / 8, exception / 32 with both operand/result offsets,
FP80 / 10, member pointer / 4 and SEH results. Its complete synthetic class
emits a thirteen-byte member-call control with ECX receiver and RET 8. No
incomplete game owner is instantiated or embedded. Explicit probe flags and
VC7.1 build 3077 are reproducibility settings, not an executable-wide compiler
profile. Vendor assembly COFF bodies supply archive origin evidence; no
assembly, target byte arrays or conditional matching bodies are added to game
source.

Thirty-four regression checks reject missing whole carriers/default bodies,
false alignment credit, truncated tables, wrong callback/operand/control-word
slots, invented shared symbols, lost COMMON/default-handler bindings and
recounting the R127 entry. All 517 public checks pass. Canonical totals are
3,282 resolved (919 authored, 1,788 library, 575 compiler), with 1,069 pending.
Exact/source/mapping remains 60 / 9,883 bytes; recorded authored extents remain
872 / 1,952,956 bytes and the provisional denominator remains 1,965,299.
Local investigation and verification are followed by one final no-auth public
HTTPS MCP acceptance covering R130 and retained graphs, all authored extents,
project attestation, progress freshness, 517 tests and whitespace checks.
All 60 exact units cold-replay across eleven objects. Private evidence stays
untracked; target, private database, shared tools and game source are preserved.

## R131 — Complete localtime, time-zone and environment dependency graph

R131 resolves all six handoff candidates and fourteen necessary existing
entries: seventeen complete library primaries / 4,384 bytes / 237 typed fields
and three existing nine-byte cleanup entries. Replay
`scripts/repo-python scripts/verify-time-zone-origins.py`; the manifest is
`config/time-zone-origin-evidence.json`. No source, mapping or exact credit is
added. Source associations come from the hash-pinned libcmt.lib archive, not
from Ghidra names or the presence of reviewed callees.

| Complete source primary | Address | Whole bytes | Fields |
| --- | --- | ---: | ---: |
| `_localtime` | `0x0064197E` | 384 | 13 |
| `__tzset_lk` | `0x00647778` | 680 | 62 |
| `__isindst_lk` | `0x00647BD8` | 391 | 30 |
| `___tzset` | `0x00647D5F` | 76 | 9 |
| `__isindst` | `0x00647DE0` | 62 | 6 |
| `_gmtime` | `0x00647E1E` | 263 | 5 |
| `_cvtdate` | `0x00647A20` | 440 | 15 |
| `__getenv_lk` | `0x006506C5` | 129 | 8 |
| `___wtomb_environ` | `0x00653816` | 144 | 6 |
| `__mbsnbicoll` | `0x006537C8` | 78 | 4 |
| `___crtsetenv` | `0x00654660` | 469 | 27 |
| `___crtCompareStringA` | `0x0065422E` | 900 | 38 |
| `__mbschr` | `0x0065497E` | 123 | 4 |
| `_copy_environ` | `0x006545FF` | 97 | 3 |
| `_findenv` | `0x006545B2` | 77 | 4 |
| `_strncnt` | `0x00654212` | 28 | 0 |
| `__strdup` | `0x00642AD2` | 43 | 3 |

**Complete extents and shared cleanup.** Every primary retains its whole own
COFF AUX extent. The two lock wrappers expand from provisional 67/53 bytes to
76/62, including all finally instructions. Their existing cleanup entries
`0x00647DA2` and `0x00647E15` bind actual source labels at +67/+53. The existing
`0x00647993` entry is the time-zone reader's normal cleanup subentry at +539;
its scope points to the complete exceptional entry at +534, including the
five-byte frame adjustment before that subentry. The verifier preserves both
actual source labels, complete parents and instruction starts. All three
names remain blank; overlapping cleanup bytes gain no standalone credit.

The old 336-byte `0x0065497E` span merges different source owners. Reconciliation
retains every old byte: its own MBCS search AUX / 123, seven observed INT3
alignment bytes, and an entire separate strchr section / 206. That section
contains a sixteen-byte static success entry at `0x00654A00` and `_strchr` /
190 at `0x00654A10`; both have actual complete AUX records. The sixteen-byte
AUX includes eleven source-emitted alignment bytes after RET. The strchr
conditional branch reaches the preceding success entry in the same defining
section, so comparing only the 190-byte entry is insufficient. All 206 source
bytes replay. Only after that coverage is established is the canonical MBCS
extent reconciled to 123. Neither unlisted source control becomes an invented
inventory candidate, and the seven target alignment bytes earn no credit.

**Target-observed time and storage protocol.** Localtime rejects negative
signed epoch values and preserves both paths around the actual three-day
margins 259,200 and 2,147,224,447. It retains timezone and DST adjustments,
near-limit updates to the existing tm fields and actual tm_isdst at +32.
Gmtime uses the getptd return's +68 buffer slot, allocates a complete 36-byte tm,
and falls back to its whole static tm when allocation fails. All calendar,
leap-year, month/day, weekday and time-of-day arithmetic stays inside its full
263-byte AUX; both complete thirteen-element month tables replay together.
The original time representation is the observed 32-bit signed CRT model;
this is not a claim about current operating-system time APIs.

The initializer uses time lock 6, while its TZ environment read uses lock 7.
The first-time flag, cached lastTZ pointer, Windows API path, environment path,
failed allocations/conversions, cache invalidation, default names and both
cleanup paths remain intact. The transition converter and DST tester retain
both start/end records, year caching, relative/absolute Windows transition
forms and both orderings of the start/end dates. The full Windows timezone
object is 172 bytes; SYSTEMTIME is sixteen with WORD fields. No Japanese-zone
value is inferred merely from the executable's language. Writable values,
OS/environment inputs and the runtime locale remain unknown.

**Environment, NLS and API closure.** Getenv's conversion branch invokes the
entire wide-to-multibyte environment converter, which in turn reaches the
whole crtsetenv parent and its real local copy/find helpers. Allocation,
duplication, environment-vector updates, failures and SetEnvironmentVariableA
remain source-typed. Name comparison reaches complete mbsnbicoll and the
900-byte crtCompareStringA, including ANSI/wide API selection, both conversions,
stack/heap allocation, both stack-overflow filters/handlers and cleanup. All
raw IAT fields bind their actual descriptor names; register-indirect calls
retain complete source instructions and the actual loaded IAT value. The
existing chkstk owner retains its source-defined alloca_probe alias; an alias
without its own function AUX is not treated as a separate function.

Two complete vendor alternatives remain explicit. Copy_environ / 97 also
has a wide-family source body with equal non-field bytes and a different
duplication symbol. Strncnt / 28 occurs in another complete NLS member. The
selected narrow environment/CompareStringA parents actually define and call
their own local symbols; all selected fields bind complete defining owners.
Equivalent shapes alone do not identify a source unit, original spelling or
folding. Natural narrow/wide duplication call controls both emit seventeen
bytes, retaining distinct REL32 symbols `__strdup`/`__wcsdup`; symbolic calls
cannot be merged merely because their unlinked bodies are equal.

Fifteen whole defining data sections / 679 bytes / nine typed fields include
all time-zone defaults and name pointers / 152, the full timezone/cache/once
BSS carrier / 184, both transition records / 24, both month tables / 104,
static tm / 36, complete environment and locale carriers, cookie, literal TZ,
NLS flag and four full SEH scope definitions. The three time-zone scopes are
twelve bytes each; CompareStringA's complete two-record scope is 24 with all
four filter/handler pointers. Both environment-initialized and MBCS-info
COMMON definitions retain their full four-byte declarations and loader
zero-fill geometry. No table or writable-carrier prefix substitutes for a
complete defining object. Twenty-one independent anchors / 2,607 bytes / 108
fields retain historical origins and the entire R130/runtime/compiler/game
chain; no new origin is inherited from those anchors.

**Compiler observations and limits.** Natural VC7TimeZoneLayout cold-builds
53 DWORDs / 212 bytes using complete pinned CRT/SDK types and a synthetic
three-int transition control. It verifies time_t/pointer/int/long / 4,
wchar_t / 2, tm / 36 and all nine fields, thread / 140 with gmtime/MBCS slots
+68/+96, complete MBCS info / 544, SYSTEMTIME / 16, timezone / 172 and all
relevant offsets, transition / 12, locks and epoch constants. Eleven complete
vendor source files and nine headers are hash-pinned privately by the manifest.
The synthetic transition model is a layout control, not a recovered game
owner. No incomplete game object is instantiated or embedded. Explicit probe
flags and VC7.1 build 3077 are reproducibility settings; no executable-wide
compiler profile is inferred. Vendor strchr assembly COFF is archive evidence;
no assembly or target-byte arrays are added to game source.

Thirty-eight regression checks reject truncated parents/scopes/tables,
misbound cleanup or COMMON, lost thread/time/SDK layouts, conflated narrow/wide
calls, wrong local source parents and discarding/recounting the old MBCS span.
All 555 public checks pass. Canonical totals are 3,302 resolved (919 authored,
1,808 library, 575 compiler), with 1,049 pending. Exact/source/mapping remains
60 / 9,883 bytes; recorded authored extents remain 872 / 1,952,956 bytes and
the provisional denominator remains 1,965,299. One final no-auth public HTTPS
MCP acceptance replays R131 and retained graphs, all authored extents, project
attestation, progress freshness, 555 tests and whitespace checks. All 60 exact
units cold-replay across eleven objects. Investigation and intermediate checks
are local; private evidence stays untracked and shared tools remain read-only.

## R132 — Complete low-level file I/O, handle locking and error graph

R132 resolves all six handoff roots and twelve necessary existing entries:
fourteen complete library primaries / 2,338 bytes / 109 typed fields and four
existing cleanup entries / 33 overlapping bytes. Replay
`scripts/repo-python scripts/verify-low-io-origins.py`; the manifest is
`config/low-io-origin-evidence.json`. Every primary uses its complete own COFF
AUX from the hash-pinned libcmt.lib. No source, mapping or exact credit is added.

| Complete source primary | Address | Whole bytes | Fields |
| --- | --- | ---: | ---: |
| `__lseek_lk` | `0x0064EC83` | 116 | 6 |
| `__lseek` | `0x0064ECF7` | 171 | 12 |
| `__lseeki64_lk` | `0x006523AC` | 131 | 6 |
| `__write` | `0x0064EF70` | 171 | 12 |
| `__read` | `0x00653A81` | 171 | 12 |
| `__close_lk` | `0x00654835` | 131 | 9 |
| `__get_osfhandle` | `0x00652066` | 65 | 4 |
| `__dosmaperr` | `0x00647FAA` | 115 | 7 |
| `__lock_fhandle` | `0x006520A7` | 160 | 10 |
| `___doserrno` | `0x00647FA1` | 9 | 1 |
| `__unlock_fhandle` | `0x00652147` | 34 | 2 |
| `__write_lk` | `0x0064EDA2` | 462 | 13 |
| `__read_lk` | `0x006538A6` | 475 | 9 |
| `__free_osfhnd` | `0x00651FE7` | 127 | 6 |

**Complete extent and EH observations.** The lock initializer expands the old
148-byte provisional span to its entire 160-byte AUX. Its exceptional cleanup
includes three stack-adjustment bytes at +148 before the existing nine-byte
entry `0x0065213E` / +151 / `$L20250`. The three 171-byte lseek/write/read
wrappers each retain both error paths, the normal return and the cleanup at
+135. Their existing eight-byte entries are `0x0064ED7E` / `$L20662`,
`0x0064EFF7` / `$L20376` and `0x00653B08` / `$L20375`. The complete twelve-byte
scopes point at +132, before the three-byte stack adjustment; the scope entry
and normal cleanup subentry must remain distinct. All cleanup names stay
blank. Their bytes overlap full owners and gain no standalone exact credit.
The verifier reads back actual source definitions, complete target instructions,
all branches/exits and every typed field. Library children alone confer no
origin on remaining stream parents.

**Target operations and ABI.** Handle validation uses unsigned bounds against
_nhandle, group selection by shift 5 / mask 31, and 36-byte ioinfo stride. The
FOPEN flag lives at +4, pipech at +5, lock initialization at +8 and the complete
24-byte CRITICAL_SECTION at +12. Lock creation preserves its double check,
lock-table guard, failure return, finally release and eventual handle lock.
Unlock uses the same actual critical-section field. The complete thread object
is 140 bytes; errno and OS errno occupy +8/+12. The nine-byte OS-errno accessor
returns the actual getptd result plus twelve.

Both seeks bind actual SetFilePointer and GetLastError IAT slots, retain the
all-ones low-word sentinel plus OS-error check, and clear FEOFLAG on success.
The 64-bit seek uses a truthful eight-byte low/high union, passes the high-word
address to SetFilePointer and returns EDX:EAX. The complete write parent retains
append seek, text CRLF conversion, binary write, short writes, device/control-Z
and error mapping. The read parent retains pipe lookahead, CRLF translation,
control-Z EOF, broken-pipe behavior, one-byte lookahead/seek restoration and
all failure/success paths. Close preserves stdout/stderr handle alias handling,
CloseHandle failure, handle release, flag clearing and OS-error mapping. The
free-handle helper resets standard handles only for application type 1;
the observed target has initial GUI application type 2. Runtime handles,
buffer contents and file/device state remain unknown; no game I/O is executed.

**Whole data and definition provenance.** Seven complete defining sections /
420 bytes / five DIR32 fields retain all four scopes / 48, the whole 45-entry
OS-error map / 360, cookie / 4 and application-state/exit-pointer carrier / 8.
The ordered error map retains both occurrences of OS code 6, including the
second source entry whose comment says 124. The source definition and target
bytes govern acceptance; the table is not silently repaired. Both access-error
and execution-error fallback ranges and default EINVAL stay in the whole
115-byte error mapper. The complete source COMMON declarations retain all
64 handle-array pointers / 256 and nhandle / 4 in their actual writable loader
zero-fill region. Runtime allocated arrays are not guessed from initial zeros.

Application state has five strong archive definitions. The retained full
469-byte GUI entry at `0x0064232C` independently binds R126's wincrt0 source
member. That same member defines the entire two-word carrier, with app_type at
+4 and a typed exit pointer at +0 to the independently reviewed __exit owner.
All five actual definitions remain recorded and are read back from the whole
archive. Selection does not use the first masked match and does not establish
original source spelling, source-unit identity or folding. Eleven complete
anchors / 1,011 bytes / 72 fields retain independent origins; their complete
code/data/EH dependencies replay through the full R131 chain, including R125
I/O initialization. No new origin is inherited from these anchors.

**Compiler observations and limits.** Natural VC7LowIoLayout cold-builds
48 DWORDs / 192 bytes with complete pinned CRT/SDK types. It verifies pointer,
int and long / 4, int64 / 8, ioinfo / 36 and all actual fields, critical section
/ 24, handle geometry, whole pointer/group storage sizes, thread offsets,
error-entry layout and file/error/standard-handle constants. The independent
11-byte cdecl file-offset identity body loads low/high into EAX/EDX and returns
without callee argument cleanup. Its full AUX and all instructions replay.
The offset union and error-entry pair are synthetic layout controls, not
reconstructed game objects. Nine vendor source files and eight headers remain
hash-pinned. Probe flags and VC7.1 build 3077 are reproducibility settings;
no executable-wide compiler profile is inferred.

Thirty-three regression checks reject truncated owners, conflated cleanup
entries, incomplete error/handle/application carriers, wrong thread/SDK/int64
layouts, missing text/EOF policies and arbitrary application-state definitions.
All 588 public checks pass. Canonical totals are 3,320 resolved (919 authored,
1,826 library, 575 compiler), with 1,031 pending. Exact/source/mapping remains
60 / 9,883 bytes; recorded authored extents remain 872 / 1,952,956 bytes and
the provisional denominator remains 1,965,299. One final no-auth public HTTPS
MCP acceptance replays R132 and retained graphs, authored extents, project
attestation, progress freshness, 588 tests and whitespace checks. All 60 exact
units cold-replay across eleven objects. Investigation and intermediate checks
use local tools; private evidence stays untracked and shared tools read-only.

## R133 — Complete stream buffering, character pushback and close wrapper

R133 resolves all six stream buffer/close handoff roots and one existing cleanup
entry: six complete library primaries / 879 bytes / 29 typed fields and an
eight-byte overlapping cleanup. Replay
`scripts/repo-python scripts/verify-stream-buffer-origins.py`; the whole manifest
is `config/stream-buffer-origin-evidence.json`. Every primary retains its entire
own COFF AUX from the hash-pinned libcmt.lib. No source, mapping or exact credit
is added. Reviewed low-level callees alone establish none of these origins.

| Complete source primary | Address | Whole bytes | Fields |
| --- | --- | ---: | ---: |
| `__filbuf` | `0x0065163C` | 225 | 4 |
| `__flsbuf` | `0x006443FE` | 281 | 9 |
| `__getbuf` | `0x0064F01B` | 68 | 2 |
| `__isatty` | `0x0064F05F` | 42 | 2 |
| `__ungetc_lk` | `0x0065171D` | 108 | 1 |
| `__close` | `0x006548B8` | 155 | 11 |

**Target behavior and complete boundaries.** The refill parent retains stream
access/string checks, allocation/reuse, read count, EOF/error distinction,
control-Z policy, small-buffer restoration, unsigned narrow-byte return and
both complete returns. Its safe-handle branch uses the entire badioinfo object
when FILE._file is -1. The flush parent retains read-to-write switching only at
EOF, stdout/stderr device handling, buffer allocation, buffered write, append
seek for an empty buffer, single-character output, short-write error and the
unsigned-byte return. Both paths bind the actual complete R132 read/write/seek
parents. Neither formatting caller gains origin through this association.

Getbuf increments the actual cflush state, requests 4096 bytes from the complete
reviewed malloc wrapper and preserves its allocation-failure branch. The
fallback points at FILE._charbuf / +20, with runtime buffer size two; the
underlying integer field occupies four bytes. Isatty uses unsigned bounds,
shift 5 / mask 31 and 36-byte handle stride. It returns raw FDEV / 0x40 or zero,
not a normalized boolean and not an errno-setting invalid-handle failure.
Pushback rejects EOF and incompatible stream modes, allocates when needed,
preserves buffer-limit checks, compares and rolls back pointers for a string
stream without writing that source buffer, and writes the character only on
the ordinary-buffer branch. Success increments count, clears EOF, sets READ
and returns the unsigned byte.

The whole 155-byte close wrapper retains validation, locking, second FOPEN
check, close_lk call, error cases, finally cleanup and complete SEH epilog.
Its existing eight-byte cleanup `0x0065492F` is the actual `$L20316` label at
+119; the complete twelve-byte scope points at `$L20314` / +116, including
three bytes that reload the handle before the label. Both source definitions
and actual instruction starts replay. The initial invalid-handle branch clears
OS errno; the post-lock FOPEN failure sets EBADF and preserves the distinct
source behavior. Cleanup names remain blank and overlapping bytes earn no
standalone source or exact credit. Every branch, exit, indirect instruction,
code/data/EH field and direct external edge is checked against the full source.

**Whole data, loader and retained graph.** Four complete defining sections /
692 bytes / three DIR32 fields comprise badioinfo / 36, all twenty FILE records
/ 640, cflush / 4 and the close scope / 12. Both stdin pointer/base fields bind
the entire input-buffer COMMON / 4096. Stdout/stderr comparisons bind actual
__iob addends +32/+64. The source's stale stderr index comment does not override
the observed third record / index two. Initial FILE flags, handles, buffer size,
pointers and all seventeen unused records replay; runtime stream state remains
unknown. Badioinfo preserves handle -1, FTEXT / 128, pipe lookahead / 10 and
complete lock/padding storage. Cflush is a full defining BSS section, correcting
the prior diagnostic COMMON association; its actual loader zero-fill geometry
replays. The source explains its link retention of stdio termination, while
complete initializer/terminator registrations retain R125 evidence.

Three complete COMMON declarations / 4356 bytes retain the input buffer / 4096,
all 64 handle-array pointers / 256 and nhandle / 4. All loader-zero spans remain
in the actual writable PE region; runtime allocated handle arrays are unknown.
Eleven complete anchors / 950 bytes / 62 fields retain independent origins and
replay the entire R132 code/data/API/EH/ABI chain, including R125 initialization.
These anchors and their existing cleanup entries receive no new origin credit.
No table prefix, guessed pointer or shape-only library name replaces complete
source definition and actual target binding.

**Compiler observations and limits.** Natural VC7StreamBufferLayout cold-builds
53 DWORDs / 212 bytes with complete pinned FILE / 32 and all eight fields,
20-record array / 640, char / 1, wchar_t / 2, buffer sizes, flags, complete
ioinfo / 36, critical section / 24, thread / 140 and error slots +8/+12. Its
13-byte narrow-byte load control uses MOVZX from one byte through FILE._ptr;
its 21-byte pushback call control preserves the actual __ungetc_lk REL32
symbol, parameter order and eight-byte caller cleanup. Both whole own AUX
bodies and every instruction replay. Eight vendor source files and eight
headers remain hash-pinned. These controls do not instantiate any incomplete
game owner or earn reconstruction exact credit. Explicit flags and VC7.1 build
3077 remain reproducibility settings, without an executable-wide profile claim.

Thirty-three regression checks reject truncated source owners, misbound cleanup,
incomplete FILE/input/handle/BSS objects, lost stdin fields or stdout/stderr
addends, wide-byte substitutions, incorrect pushback ABI and changed initial
records. All 621 public checks pass. Canonical totals are 3,327 resolved
(919 authored, 1,833 library, 575 compiler), with 1,024 pending. Exact/source/
mapping remains 60 / 9,883 bytes; recorded authored extents remain 872 /
1,952,956 bytes and the provisional denominator remains 1,965,299. One final
no-auth public HTTPS MCP acceptance replays R133 and retained graphs, authored
extents, target/project attestation, progress freshness, 621 tests and whitespace
checks. All 60 exact units cold-replay across eleven objects. Investigation
and intermediate verification use local tools; private evidence stays
untracked and shared tools remain read-only.
