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

## R134 — Complete output formatting, dispatch and conversion graph

R134 resolves the six output-format handoff roots and four required existing
callee candidates: ten complete library primaries / 2629 bytes / 50 typed
fields. Replay `scripts/repo-python scripts/verify-output-format-origins.py`;
the manifest is `config/output-format-origin-evidence.json`. Every source owner
retains its entire own COFF AUX from the hash-pinned libcmt.lib, including data
inside that extent. No source, mapping or exact reconstruction credit is added.

| Complete source primary | Address | Whole bytes | Fields |
| --- | --- | ---: | ---: |
| `_sprintf` | `0x006404F0` | 88 | 2 |
| `__scprintf` | `0x00640548` | 49 | 1 |
| `__snprintf` | `0x0064254D` | 87 | 2 |
| `__vsnprintf` | `0x006425C3` | 86 | 2 |
| `__output` | `0x006445C4` | 2042 | 34 |
| `_write_char` | `0x00644517` | 51 | 1 |
| `_write_string` | `0x0064456E` | 55 | 1 |
| `_write_multi_char` | `0x0064454A` | 36 | 1 |
| `_wctomb` | `0x0064F250` | 39 | 4 |
| `___wctomb_mt` | `0x0064F1F0` | 96 | 2 |

**Target behavior and boundaries.** The output owner is 2010 instruction bytes
plus its own 32-byte eight-entry DIR32 table at +2010 / `0x00644D9E`; its complete
extent ends at `0x00644DBD`. The former provisional 2010-byte ledger is expanded
to 2042. The actual unsigned state guard, EAX-times-four indirect jump, local
source table definition, all eight fields and all actual case instruction
starts replay. The table address is data, while its destinations are code
entries inside the complete source owner. No prefix or relocation mask earns
acceptance. All width, precision, flag, string, counted-string, integer, int64,
floating conversion, `%n`, error and return paths remain in the full comparison.

The four wrappers preserve the whole synthetic FILE setup and output call.
Sprintf uses the actual INT_MAX count and WRITE|STRG / 66 flags; bounded
wrappers retain the historic size_t-to-int count conversion and termination
attempt. They can exhaust the count without adding a terminator; modern snprintf
behavior is not substituted. Vsnprintf uses the actual pointer va_list. Scprintf
uses a null-base counting stream; both character and string helpers preserve
that fast path, while ordinary streams retain byte output and complete flsbuf
binding. Source-local helper spelling alone is insufficient: multiple archive
variants exist, and the actual defining output member selects the complete
51-/55-/36-byte bodies. The private optimized character call passes the byte in
AL, FILE in ECX and counter pointer in ESI. The source's local cdecl declaration
does not justify adding an external cdecl prototype for that register contract.
All helper returns retain zero callee stack cleanup.

Wctomb retains thread lookup, actual locale pointer comparison/update and the
complete three-argument conversion call. The converter preserves null-buffer
behavior, C-locale byte conversion, EILSEQ / 42 for an unrepresentable value,
and the actual WideCharToMultiByte IAT binding and default-character rejection.
Its complete source-defined thread locale object is 84 bytes, with codepage
+4, handle array +12, mb_cur_max +40 and pctype +72. The thread object is 140
bytes, with locale pointer +100. Runtime locale/codepage values remain unknown.

**Whole data and callback provenance.** Fifty-six complete defining sections /
2361 bytes / 68 fields retain the entire 89-byte combined character-class/state
lookup, both narrow/wide null-string pointers and literals, complete CTYPE
carrier / 1284, full default-locale carrier / 403, lconv / 56, C time locale /
184 and all recursively bound day/month/time strings. Signed-looking lookup
addends retain their actual 32-bit arithmetic. Defined BSS uses actual loader
zero-fill geometry. No guessed subobject prefix replaces the defining section.

The FP dispatch object at `0x00670120` is exactly six slots / 24 bytes. All six
initial image fields bind the complete R124 fatal stub. The complete R124
initializer's actual stores support the initialized view: cfltcvt, cropzeros,
fassign, forcdecpt, positive, cfltcvt again. Output uses slot offsets 0, 12 and
4. Both initial and initialized views replay; runtime execution/current slot
contents remain unknown. Cropzeros / 75, forcdecpt / 60 and positive / 26 are
three complete non-inventoried auxiliary controls / 161 bytes / five fields,
retaining R124 dependency evidence without inventing new candidates. Fifteen
complete independent anchors / 1195 bytes / 65 fields retain their origins.
The verifier replays the full R133 stream/handle graph and its complete retained
locale, FP, heap, security, import and initialization evidence. Game callers gain
no ownership from these library children.

**Compiler observations and limits.** Two independent natural probes preserve
real vendor types: a 136-byte format layout and a 52-byte SDK/thread/locale
layout. The vendor DOUBLE struct and SDK DOUBLE typedef are kept in separate
translation units, with no macro substitution or ABI misdeclaration. Controls
retain FILE / 32, va_list / 4, complete DOUBLE and LONGDOUBLE carriers / 8,
signed-short counted-string fields / 8 and conversion buffer / 512. The full
53-byte variadic int64 control advances the argument pointer by eight and loads
EDX:EAX; the full 25-byte typed PF0 control pushes five arguments and removes
20 bytes in the caller. Six complete vendor source files and pinned headers
replay. Build 3077 and explicit flags remain reproducibility settings, without
an executable-wide compiler claim or an incomplete game-owner layout.

Thirty-eight regression checks reject truncated output owners, discarded or
misclassified tables, misbound cases, invented auxiliary origin credit, missing
FP slots/initializer stores, incomplete locale/CTYPE/null data, incorrect natural
layouts and changed variadic/PF0 calling contracts. All 659 public checks pass.
Canonical totals are 3337 resolved (919 authored, 1843 library, 575 compiler),
with 1014 pending. Exact/source/mapping remains 60 / 9883 bytes; recorded authored
extents remain 872 / 1952956 bytes and the provisional denominator is 1965299.
One final no-auth public HTTPS MCP acceptance replays R134 and retained graphs,
authored extents, target/project attestation, progress freshness, 659 tests and
whitespace checks. All 60 exact units cold-replay across eleven objects. Local
tools perform investigation and intermediate verification; private evidence
stays untracked and shared tools remain read-only.

## R135 — Complete input scanning, multibyte and NLS query graph

R135 resolves all six input-format/locale handoff roots and four required
existing dependencies: ten complete library primaries / 4801 bytes / 129 typed
fields. Replay `scripts/repo-python scripts/verify-input-format-origins.py`;
the manifest is `config/input-format-origin-evidence.json`. Every primary
retains its entire own AUX from the hash-pinned libcmt.lib, with all source,
code/data/API/SEH fields and full control flow compared. No source, mapping or
exact reconstruction credit is added. Reviewed children alone prove no parent.

| Complete source primary | Address | Whole bytes | Fields |
| --- | --- | ---: | ---: |
| `_sscanf` | `0x00642A2D` | 52 | 2 |
| `__input` | `0x0064993C` | 3452 | 60 |
| `__inc` | `0x006498FC` | 22 | 1 |
| `___mbtowc_mt` | `0x006517CE` | 192 | 3 |
| `_mbtowc` | `0x0065188E` | 43 | 4 |
| `___getlocaleinfo` | `0x006519EE` | 295 | 15 |
| `_isxdigit` | `0x0064283A` | 63 | 4 |
| `_isspace` | `0x00642879` | 58 | 4 |
| `___crtGetLocaleInfoW` | `0x00653B2C` | 304 | 18 |
| `___crtGetLocaleInfoA` | `0x00653C5C` | 320 | 18 |

**Target behavior and complete boundaries.** Sscanf constructs a local stack
FILE / 32 with READ|STRG|MYBUF / 73, original string pointer/base, complete
strlen-derived count and actual pointer va_list at EBP+16. The stale source
comment about static storage does not override the declaration or emitted
stack object. Its entire input call and return replay. The source-local inc
helper belongs to the same actual defining input member, passes FILE in EDX,
loads an unsigned byte on its fast path and calls the full R133 filbuf on
exhaustion. Its private optimized register contract is preserved without
inventing an external cdecl declaration. Both returns have zero callee cleanup.

The complete 3452-byte input owner retains width/length/suppression policies,
whitespace, literal matching, character/string/scanset conversion, decimal,
hex/octal/int64 parsing, floating text, `%n`, pushback, matched-versus-assigned
EOF policy and every final exit. It contains a four-byte exception filter and
its real handler, with no separate inventory candidate or new origin credit.
The narrow scanset is 32 bytes / 256 bits, allocated on the stack with real
resetstkoflw and heap fallback after an exception; fallback allocation failure
and final conditional free remain inside the full extent. Float text storage
is `_CVTBUFSIZE + 1` / 350 bytes, with width limit 349, distinct from the prior
output buffer / 512. The int64 multiplication binds full R006 allmul / 52,
including both actual RET 16 exits. No instruction prefix or masked field earns
acceptance; no game caller gains ownership from this association.

Mbtowc retains thread lookup / locale update and the full four-argument worker
call. The worker handles null/zero-length input, null-character output, optional
destination, C-locale unsigned-byte conversion, lead-byte classification,
signed count comparisons and all actual MultiByteToWideChar calls. Flags are
MB_PRECOMPOSED|MB_ERR_INVALID_CHARS / 9; failures retain the source's distinct
lead-byte validation policy and EILSEQ / 42. Isxdigit/isspace retain actual
thread locale and complete isctype worker bindings, including the single-byte
raw classification masks / 128 and 8. Runtime codepage and allocated locale
state remain unknown.

Getlocaleinfo retains its full string and integer query branches. The string
branch starts with 128 bytes, checks ERROR_INSUFFICIENT_BUFFER / 122, queries
size, allocates a temporary when required, allocates the returned string,
binds the complete strncpy / 292 and frees only its owned temporary on every
success/failure path. The integer branch retains all four wide characters /
eight bytes, low-byte extraction, digit tests and unsigned-byte accumulation.
Both complete A/W wrappers probe the real GetLocaleInfoW API, distinguish
ERROR_CALL_NOT_IMPLEMENTED / 120, retain separate flavor caches, use the
source's default-codepage fallback, and preserve direct and converted queries,
size-only paths, SEH stack allocation, heap fallback and cleanup. Their actual
GetLocaleInfoA/W and multibyte/wide conversion IAT identities replay. API
availability, cached runtime flavors and returned locale values are unknown.

**Whole data, SEH and callback provenance.** Fifty-nine complete defining
sections / 2327 bytes / 72 fields retain the full mb_cur_max/decimal carrier /
12, complete CTYPE / 1284, default locale / 403, full C time/lconv objects and
all recursively bound literals. Complete source-defined BSS retains integer
query storage / 8, distinct W/A flavor caches / 4 each and full locale-handle
carrier / 32, with actual writable PE loader zero-fill geometry.

Three whole twelve-byte scope records retain enclosing level -1 and both actual
filter/handler code pointers. Input's entries are +1578/+1582, W query's are
+184/+188 and A query's are +175/+179. Every filter's four bytes return one;
each handler restores ESP from EBP-24 and calls the real full R123 stack reset.
Source labels, full parent extents and actual instruction starts replay; none
are promoted into invented standalone candidates. All direct source branches,
full returns and indirect calls remain in the complete comparison.

The full six-slot FP table / 24 retains initial fatal stubs and the actual R124
initializer's six supported callback stores. Input's one actual indirect call
uses slot +8 / fassign. All six owners replay; current runtime slot contents
remain unknown. Three non-inventoried FP helper controls / 161 bytes / five
fields retain R124/R134 evidence without new candidate credit. Twenty-three
complete independent anchors / 2021 bytes / 71 fields preserve prior origins.
The verifier replays the entire R134 output/FP graph, R133 streams, R132 handles
and retained locale, heap, security, import and initialization chains.

**Compiler observations and limits.** Two independent natural probes preserve
real types: format / 136 and SDK/thread/locale / 112. Controls verify FILE / 32,
va_list and destination pointers / 4, wchar_t / 2, locale / 84, thread / 140,
actual locale pointer/field offsets, 32-byte scanset and 349/350 float limits.
The full 44-byte variadic pointer control advances by four; the full 26-byte
int64 multiply control emits the actual allmul symbol and its callee cleanup
contract. A full 21-byte typed PF2 control removes twelve caller bytes. The
full 42-byte SDK API control uses the real stdcall import, six arguments and
flags / 9. Vendor FP and SDK DOUBLE contexts remain separate. Nine complete
vendor source files and pinned headers replay. VC7.1 build 3077 and explicit
flags are reproducibility settings, without a global executable compiler claim.

Forty-three regression checks reject truncated owners, invented filter/auxiliary
credit, lost or misbound scope entries, wrong filter/handler execution, incomplete
locale/CTYPE/BSS/FP carriers, conflated NLS caches, unsupported current runtime
claims, incorrect scanset/float/ABI layouts and lost API/error policy. All 702
public checks pass. Canonical totals are 3347 resolved (919 authored, 1853
library, 575 compiler), with 1004 pending. Exact/source/mapping remains 60 /
9883 bytes; recorded authored extents remain 872 / 1952956 bytes and the
provisional denominator is 1965299. One final no-auth public HTTPS MCP request
replays R135 and retained graphs, authored extents, target/project attestation,
progress freshness, 702 tests and whitespace checks. All 60 exact units
cold-replay across eleven objects. Investigation and intermediate verification
use local tools; private evidence stays untracked and shared tools read-only.

## R136 — Complete locale construction, category and enumeration graph

R136 resolves all six locale-construction/category handoff roots and seventeen
required existing dependencies: 23 complete library primaries / 5949 bytes /
421 typed fields. Replay
`scripts/repo-python scripts/verify-locale-construction-origins.py`; its manifest
is `config/locale-construction-origin-evidence.json`. Every primary retains its
entire own AUX from the hash-pinned libcmt.lib. Complete source bodies, actual
code/data/API fields, branches and exits compare without differences. No source,
mapping or exact reconstruction credit is added. Accepted children alone prove
no parent origin.

| Complete source primary | Address | Whole bytes | Fields |
| --- | --- | ---: | ---: |
| `__get_lc_time` | `0x0064C25F` | 871 | 46 |
| `___init_numeric` | `0x0064C847` | 461 | 39 |
| `___init_monetary` | `0x0064CB20` | 575 | 42 |
| `___init_ctype` | `0x0064CD5F` | 490 | 26 |
| `__expandlocale` | `0x00642EE5` | 348 | 24 |
| `__setlocale_set_cat` | `0x00643041` | 655 | 42 |
| `___get_qualified_locale` | `0x0064D853` | 437 | 38 |
| `___lc_lctostr` | `0x00642D9D` | 78 | 5 |
| `_TranslateName` | `0x0064D114` | 96 | 1 |
| `_GetLcidFromLangCountry` | `0x0064D778` | 134 | 16 |
| `_GetLcidFromLanguage` | `0x0064D7FE` | 85 | 11 |
| `_GetLcidFromCountry` | `0x0064D741` | 55 | 7 |
| `_GetLcidFromDefault` | `0x0064D174` | 26 | 4 |
| `_ProcessCodePage` | `0x0064D18E` | 118 | 9 |
| `__stricmp` | `0x00651B15` | 105 | 6 |
| `_GetPrimaryLen` | `0x0064D33A` | 29 | 0 |
| `_crtGetLocaleInfoA@16` | `0x0064D222` | 227 | 10 |
| `_LangCountryEnumProc@4` | `0x0064D45C` | 538 | 49 |
| `__strnicmp` | `0x00651B7E` | 127 | 6 |
| `_TestDefaultCountry` | `0x0064D204` | 30 | 1 |
| `_TestDefaultLanguage` | `0x0064D3EB` | 113 | 8 |
| `_LanguageEnumProc@4` | `0x0064D676` | 203 | 18 |
| `_CountryEnumProc@4` | `0x0064D357` | 148 | 13 |

**Target behavior and source ownership.** Time construction retains allocation,
all abbreviated/full weekday and month names, AM/PM and date/time strings,
locale/calendar fields, refcount initialization and complete failure cleanup.
Numeric and monetary initialization retain the complete lconv / 48, string and
integer queries, source-inlined grouping conversion, allocation/refcounts,
replacement and rollback paths. Grouping converts ASCII digits and semicolons
according to the original source. Complete R122 freeing owners remain separate
independent anchors; no runtime allocation or current locale value is assumed.

CTYPE initialization retains GetCPInfo, the complete CPINFO / 20, lead-byte
ranges, the actual 768-byte classification allocation, 257-byte character
buffer, EOF slot, all 256 classification inputs, lead-byte marker / 32768,
254-byte prefix copy, refcounts and cleanup. Category compatibility compares
128 shorts / 256 bytes, including the defining style terminator. The full
source carrier is 383 bytes: 256 style bytes followed by 127 character bytes.
These historical source paths are preserved without changing their policy or
adding padding. SDK MB_LEN_MAX is 5, established by the pinned natural probe.
The allocated runtime table, selected codepage and resulting classifications
remain unknown.

Expandlocale retains its C-locale shortcut, complete parse/qualification,
131-byte input/output caches, actual 130-character threshold, six-byte LC_ID
copy, four-byte codepage copy, output formatting and all exits. The cache ID
and codepage share a complete twelve-byte defining BSS carrier; LC_ID itself
remains three WORDs / six bytes. The default locale and both caches belong to
the complete 403-byte source carrier, rather than invented separate sections.
Stricmp/strnicmp retain their whole thread/locale update, ASCII fast paths,
count/termination behavior and independently bound lowercase worker.

Qualification retains language/country translation, complete binary-search
name tables, primary/default language policy, ACP/OCP and numeric codepage
selection, real locale/codepage validation, default-LCID lookup and all three
enumeration callbacks. The complete compatibility helper preserves size-only,
string/integer query and fallback-record behavior. The source-defined special
language cases and all full table literals remain evidence; no current system
locale or API result is inferred.

**Actual callbacks and whole defining state.** The category table at
`0x006700B8` retains six complete twelve-byte records / 72 bytes / 17 fields.
All six initializer pointers at +8/+20/+32/+44/+56/+68 bind actual source
owners: dummy, collate, ctype, monetary, numeric and time. The source-local
category helper's real call at `0x0064326A` uses `[ebx + 0x6700c0]`. Dummy and
collate each retain three bytes; time retains 95 bytes / ten fields. These
three non-inventoried controls / 101 bytes / ten fields gain no candidate
credit. The LC_ALL dummy is source-defined and documented unused. Category
bounds validation belongs to the pending parent. The helper retains actual
allocation, compatibility, callback and failure paths; its rollback restores
locale, handle and codepage according to the original source. It does not
establish a more general transaction guarantee.

Three actual EnumSystemLocalesA registrations bind source-local callbacks:
`0x0064D778` to `0x0064D45C`, `0x0064D7FE` to `0x0064D676`, and `0x0064D741` to
`0x0064D357`. Each real push sequence supplies LCID_INSTALLED / 1 and its
actual callback pointer to IAT `0x00657118`. All three complete callbacks
return with RET 4. Country registration schedules INC/MOV between argument
pushes and the API call; acceptance verifies the real argument sequence,
without requiring artificial instruction adjacency. Ordinary Ghidra caller
counts omit these indirect registrations and do not establish unused code.

The query pointer at `0x0068E6B0` is the final DWORD / +32 in the complete
36-byte `_iLcidState` BSS carrier. It starts null. Full qualification selects
raw GetLocaleInfoA at IAT `0x0065711C` on the actual NT platform comparison / 2,
or stores the complete source-local compatibility helper at `0x0064D222`.
All nine real indirect query sites remain inside full source owners. The
helper retains RET 16 and the natural SDK control preserves the same stdcall
contract. Runtime selection and query results remain unknown.

The graph retains 198 whole defining sections / 6378 bytes / 220 typed fields
and five complete four-byte COMMON declarations / 20 bytes. COMMON refcounts
and the ctype pointer require their actual source definitions and writable PE
loader zero-fill geometry. Whole data includes country records / 184, language
records / 520, fallback locale records / 1188, ten nondefault WORD IDs / 20,
all C time strings and the full 184-byte time record, complete CTYPE / 1284,
lconv/default carriers and all recursively bound literals. Names, pointer
fields and mutable-state ownership follow defining source topology, without
claims about post-startup contents.

Twenty-five full independent anchors / 4402 bytes / 215 fields preserve prior
origins. Memcpy retains its full R025 829-byte own AUX: seven actual code
regions / 709 bytes and six embedded tables / 120 bytes. Every complete table,
source label, typed DIR32 field and actual case instruction start replays.
Decoding tables as instructions or accepting a 709-byte prefix is rejected.
Its vendor assembly is archive evidence; no assembly or byte arrays are added
to reconstructed game source. The entire R135 input/NLS graph and all retained
output, stream, handle, locale, heap, security and initialization chains replay.

**Compiler observations and verification.** The single natural probe
`probes/VC7LocaleConstructionLayout.cpp` cold-builds the complete 340-byte layout
array. Pinned CRT/SDK types establish LC_ID / 6, LC_STRINGS / 144, category / 12,
name / 8, fallback record / 44, compatibility / 8, lconv / 48, time / 184,
thread locale / 84, CPINFO / 20 and actual offsets/constants. Source-local
record models do not establish reconstructed game owners. Four complete
45-/17-/8-/24-byte controls preserve real stdcall callback RET 4, SDK enumeration
import/flag, zero-argument cdecl category call and four-argument stdcall query
cleanup. Ten complete vendor sources and eight pinned headers replay. VC7.1
build 3077 and explicit flags provide reproducibility, without an executable-wide
compiler-profile claim.

Thirty-eight regression checks reject shortened owners/carriers, invented
candidate credit, wrong defining callbacks, missing table fields, ABI/flag/API
mistakes, guessed runtime selection, incorrect cache/CTYPE layouts and incomplete
memcpy code/table partitioning. All 740 public checks pass. Canonical totals
are 3370 resolved (919 authored, 1876 library, 575 compiler), with 981 pending.
Exact/source/mapping remains 60 / 9883 bytes; recorded authored extents remain
872 / 1952956 bytes and the provisional denominator is 1965299. One final
no-auth public HTTPS MCP request replays R136 and retained graphs, authored
extents, target/project attestation, progress freshness, tests and whitespace.
All 60 exact units cold-replay across eleven objects. Investigation and
intermediate checks use local tools; private evidence stays untracked and
shared tools read-only.

## R137 — Complete locale parents and time-formatting graph

R137 resolves all six locale/time-parent handoff roots and the required existing
expandtime worker: seven complete library primaries / 3033 bytes / 100 typed
fields. One existing nine-byte finally candidate gains library origin within
its complete 346-byte parent. This resolves eight existing candidates, without
counting overlapping bytes twice. Replay
`scripts/repo-python scripts/verify-locale-time-parent-origins.py`; its manifest
is `config/locale-time-parent-origin-evidence.json`. Every primary retains its
complete own AUX and all source/code/data/API fields, branches and exits. No
source, mapping or exact reconstruction credit is added.

| Complete source primary | Address | Whole bytes | Fields |
| --- | --- | ---: | ---: |
| `__setlocale_get_all` | `0x00642E26` | 191 | 21 |
| `__setlocale_lk` | `0x006432D0` | 473 | 24 |
| `_setlocale` | `0x006434A9` | 346 | 30 |
| `__store_winword` | `0x0064BCB1` | 1162 | 14 |
| `__Strftime_mt` | `0x0064C13B` | 197 | 1 |
| `__Strftime` | `0x0064C200` | 50 | 4 |
| `__expandtime` | `0x0064BA4B` | 614 | 6 |

**Target behavior and boundaries.** Get-all retains allocation and construction
of all category name/value strings and separators, full strcmp/free paths,
same-locale selection and all returns. Its full strcat / 232 anchor retains
its own AUX; the entire 248-byte strcpy/strcat shared carrier remains protected
by independent R116 evidence through the retained graph.

The locked locale interpreter retains category-specific query/set behavior,
LC_ALL compound parsing, known-category matching, ignored unknown categories,
full strpbrk/strncmp/strlen/strcspn/strncpy dependencies, stack locale buffer /
131, locale expansion, category updates and every success/failure exit. Its
source accepts partial category success; it does not establish an all-or-nothing
transaction. Original copy-length behavior is preserved without added bounds
checks or claims about arbitrary caller inputs.

Public setlocale validates categories 0 through 5 and uses the actual
SETLOCALE lock / 12. The entire 346-byte owner retains query-only local unwind,
allocation of threadlocinfo / 84, six handles, locale/codepage/classification,
lconv and time pointer/refcount snapshots, old-object freeing, new-global
pointer installation, thread update, failed-allocation cleanup and both final
returns. The nine-byte existing entry at `0x006435F2` is source label `$L20503`
/ parent +329. Its actual PUSH 12 / unlock / POP / RET is shared by normal
execution and the full finally scope; it is not a standalone source body.
Runtime allocations, reference counts and thread locale remain unknown.

Strftime retains the real thread locale at `_tiddata` +100, comparison with
the independent global locale, update and full six-argument worker call. The
worker / 197 retains explicit-or-thread time locale selection, zero-capacity
exit, percent/hash alternate formatting, inline lead-byte classification,
invalid trailing lead-byte failure, remaining-count tracking and final NUL
termination/zero-on-failure policy. Expandtime / 614 retains all conversion
cases, actual string/number helper contracts, locale day/month/AMPM strings,
numeric year/hour/week behavior, recursion into the full WinWord worker,
timezone initialization/name selection, literal percent, invalid-specifier
exit and all original capacity decisions. The compiler emitted conditional
branches rather than an unaccounted indirect switch table.

WinWord formatting retains all 1162 bytes, including the four-byte exception
filter, handler, API branch and every localized fallback branch after its
ordinary return. Gregorian formatting preserves repetition-based date/time
specifier selection, AM/PM spellings, quoted literals, source-defined alternate
form, multibyte handling, output pointer/count changes and recursive expansion.
No successful decompile or prefix match substitutes for full source comparison.

**SDK dispatch, scopes and defining state.** Non-Gregorian formatting uses
GetDateFormatA at IAT `0x0065714C` or GetTimeFormatA at `0x00657150`, selected
by the actual clock field / 2. The selected pointer is saved at EBP-48. The
real capacity query at `0x0064BD58` passes null output and zero count; the
output call at `0x0064BDCD` uses the saved pointer and allocated buffer/count.
Both actual six-argument sequences and real stdcall @24 imports replay.
SYSTEMTIME is a complete sixteen-byte SDK type. The source writes year +1900,
month +1, day/hour/minute/second and zero milliseconds; no initialization of
its day-of-week field is claimed. Runtime calendar, selected API and returned
values remain unknown. Stack allocation, reset after exception, heap fallback,
conditional freeing, output-copy loop and localized fallback remain complete.

Two full twelve-byte scope records retain enclosing level -1. Finally at
`0x00661180` has a null filter and handler at parent +329. Exception scope at
`0x006626A0` binds actual filter +211 and handler +215 in the WinWord owner.
The filter's entire four-byte body returns one; the handler restores ESP from
EBP-24 and calls the full R123 reset worker. Actual defining COFF labels,
parent field references and instruction starts replay. No new filter/handler
candidate is fabricated.

Seventy whole defining sections / 2582 bytes / 83 typed fields retain the
full six-record category table / 72 / 17 fields, initial locale plus caches /
403, all C time strings and full time record / 184, whole CTYPE / 1284,
lconv/default/locale-handle carriers, two complete scopes and the complete
152-byte timezone carrier with both defining name pointers. Five actual COMMON
pointer/refcount declarations / 20 bytes retain source identities and PE loader
zero-fill geometry. Whole data is compared after independently binding every
field, without carrier prefixes or assumed current mutable values.

Thirty-four full independent anchors / 6576 bytes / 358 fields preserve their
origins. The six actual category callbacks and three non-inventoried controls
/ 101 bytes / ten fields retain R136 evidence without new inventory credit.
The full R136 locale construction/enumeration graph and all retained R135
input/NLS/FP/SEH, output, stream, handle, heap, security and lifetime evidence
replay. Reviewed children alone grant no parent or game-caller origin.

**Compiler observations and local acceptance.** The natural probe
`probes/VC7LocaleTimeParentLayout.cpp` cold-builds a full 260-byte layout array:
tm / 36 and all nine fields, SYSTEMTIME / 16 and all fields, thread locale /
84 and its full snapshot offsets, thread / 140 with locale pointer +100,
time locale / 184 and fields, actual category/cache/lock and private format
selector constants. Complete 19-/35-/39-/66-byte controls preserve two-argument
locale cdecl cleanup / 8, six-argument format cdecl cleanup / 24, seven-argument
expansion cleanup / 28 and real six-argument SDK stdcall / 24 dispatch. Two
whole defining vendor sources and seven pinned headers replay. VC7.1 build
3077 and explicit flags are reproducibility settings, without a global target
compiler-profile claim.

Thirty-one regression checks reject shortened owners, invented interior credit,
missing or misbound scope fields, wrong actual filter/finally/reset execution,
incomplete state and category carriers, ABI/layout/import mistakes, guessed
runtime selection and lost actual API sizing/output contracts. All 771 public
checks pass. Canonical totals are 3378 resolved (919 authored, 1884 library,
575 compiler), with 973 pending. Exact/source/mapping remains 60 / 9883 bytes;
recorded authored extents remain 872 / 1952956 bytes and the provisional
denominator is 1965299. Full new and retained origin evidence, ledger guards,
authored extents, target/project attestation, progress freshness, tests and
whitespace checks pass locally. All 60 exact units cold-replay across eleven
objects. On 2026-10-04 the user waived public MCP acceptance to accelerate
continued review; R137 uses local final verification. Existing no-auth route
and private path remain unchanged. Private evidence stays untracked and shared
tools read-only.

## R138 — Complete locale time snapshots and classification graph

R138 resolves all five locale snapshot/classification handoff candidates:
five complete library primaries / 965 bytes / 54 typed fields. Replay
`scripts/repo-python scripts/verify-locale-snapshot-origins.py`; its manifest
is `config/locale-snapshot-origin-evidence.json`. Every primary retains its
complete own AUX, source member, branches, exits and independently bound fields.
No source, mapping or exact reconstruction credit is added. No new auxiliary,
interior, COMMON or exception-scope inventory entries are fabricated.

| Complete source primary | Address | Whole bytes | Fields |
| --- | --- | ---: | ---: |
| `__Getdays` | `0x0064B635` | 127 | 8 |
| `__Getmonths` | `0x0064B6B4` | 149 | 8 |
| `__Gettnames` | `0x0064B749` | 563 | 30 |
| `_isalpha` | `0x0064274D` | 63 | 4 |
| `_isalnum` | `0x006428ED` | 63 | 4 |

**Target observations and source behavior.** Getdays sizes all seven abbreviated
and full weekday names, adds two separators per pair and one final NUL, then
allocates and assembles the complete colon-delimited result. Getmonths performs
the corresponding complete twelve-month sizing and copy loops. Both preserve
null-allocation returns, real strlen/strcpy dependencies, all separator writes
and final termination. Their runtime strings and resulting allocation lengths
remain unknown. Ordinary Ghidra caller counts for all three time snapshot
owners are zero; this does not establish unused code or callback/export status.

Gettnames sizes all 43 strings: fourteen weekday names, twenty-four month
names, two AM/PM names and three date/time formats, including their terminators.
It allocates the whole time record / 184 plus the complete string storage,
copies all 184 bytes through the real memcpy and retargets every pointer into
that single allocation. All seven/twelve loops, five trailing pointer copies,
allocation failure and final return remain inside its full 563-byte owner.
The record's LCID, calendar type and refcount are copied with the other fields;
no artificial refcount reset or incomplete object copy is introduced. The
source uses a captured pointer to size/copy strings but reads the current global
again for the record copy. This is the original behavior, without a guarantee
of an atomic or coherent snapshot during concurrent locale mutation. Runtime
pointer values, record contents, allocations and ownership consumers are unknown.

Isalpha and isalnum retain their complete 63-byte bodies and both returns.
Each reads the thread's locale at `_tiddata` +100, compares the actual global
locale pointer and calls the complete independent update worker when needed.
For mb_cur_max at locale +40 greater than one, each calls the full isctype_mt
worker with the actual locale, original signed integer input and mask, then
removes twelve caller bytes. Otherwise it uses the locale's pctype at +72,
loads the unsigned short classification indexed by the original integer and
applies the same mask. Alpha uses `_ALPHA` / 259 / 0x103; alnum uses
`_ALPHA | _DIGIT` / 263 / 0x107. These are classification bit results, without
Boolean normalization or added input-range checks. The natural header control
retains EOF / -1; arbitrary invalid input behavior is not redefined. Runtime
locale, byte width and returned classification remain unknown.

**Complete data and independent dependencies.** Forty-eight whole defining
sections / 2191 bytes / 59 typed fields retain the complete C time record /
184 and its 43 original pointer fields at offsets 0 through 168. All original
strings, full initial-locale/cache carrier / 403, whole CTYPE carrier / 1284,
C lconv/default carrier and current-time pointer retain actual defining COFF
identities, source/target hashes, mutability and all recursively bound fields.
The initial locale's full source-defined pointer topology is preserved without
splitting convenient prefixes or claiming post-startup pointer contents.

Seven complete independent anchors / 1284 bytes / 65 fields preserve their
prior origins: strlen, malloc, strcpy, memcpy, getptd, locale update and the
isctype_mt worker. The seven-byte strcpy entry still depends on the entire
248-byte shared strcpy/strcat carrier through independent R116 evidence.
Memcpy retains its full R025 829-byte own AUX, seven code regions / 709 bytes
and six complete embedded tables / 120 bytes. Every defining table label,
actual code case start and typed field replays. Its full partition is retained,
rather than decoding data as instructions or shortening the owner. All new
primaries use direct calls and branches; no unexplained indirect dispatch is
added. The entire R137 locale/time parent graph and retained R136/R135
category, enumeration, SDK, SEH, FP, stream, handle, heap and lifetime chains
replay. Reviewed library children do not grant origin to game parents.

**Compiler observations and local acceptance.** The natural probe
`probes/VC7LocaleSnapshotLayout.cpp` cold-builds a complete 132-byte layout array.
It establishes the full time / 184 and every field/array size, all 43 pointers,
thread locale / 84, thread / 140, actual locale/classification offsets,
unsigned-short width / 2, distinct alpha/alnum masks and EOF / -1. The complete
26-byte copy control passes the real memcpy symbol and 184-byte count and
retains twelve-byte cdecl caller cleanup. Two complete 67-byte controls use
the original header's alpha/alnum macros, actual multibyte worker declaration,
mask, table load and twelve-byte cdecl cleanup. These are type/ABI controls,
without target reconstruction exact credit. Three complete vendor sources and
nine pinned headers replay. VC7.1 build 3077 and explicit flags are per-probe
reproducibility settings, without an executable-wide compiler-profile claim.

Twenty-eight regression checks reject truncated owners, invented scope/interior
credit, incomplete time/locale/CTYPE carriers, missing strings, wrong masks,
EOF/width/offset mistakes, guessed runtime snapshot consistency, incorrect copy
or worker contracts, unexplained indirect calls and incomplete memcpy partitions.
All 799 public checks pass. Canonical totals are 3383 resolved (919 authored,
1889 library, 575 compiler), with 968 pending. Exact/source/mapping remains
60 / 9883 bytes; recorded authored extents remain 872 / 1952956 bytes and the
provisional denominator is 1965299. Complete new and retained origin replay,
canonical ledger guards, target/project/query attestation, authored extents,
progress/scanner freshness, tests and whitespace checks pass locally. All 60
exact units cold-replay across eleven objects. The user's 2026-10-04 waiver of
public MCP acceptance remains in force. Private evidence stays untracked and
shared tools read-only.

## R139 — Complete floating conversion and operation graph

R139 resolves all six floating conversion/operation handoff candidates as
library origin: six complete own-AUX primaries / 1750 bytes / 52 typed fields.
Replay `scripts/repo-python scripts/verify-floating-operation-origins.py` with
`config/floating-operation-origin-evidence.json`. Full defining COFF members,
source/target hashes, every relocation, branch and exit are preserved. No
source, mapping or exact reconstruction credit is added, and no auxiliary,
interior, COMMON or exception-scope inventory entries are fabricated.

| Complete vendor primary | Address | Whole bytes | Fields |
| --- | --- | ---: | ---: |
| `__atoldbl` | `0x0064F7F0` | 62 | 4 |
| `___STRINGTOLD` | `0x00653105` | 76 | 4 |
| `__floor_default` | `0x0064E980` | 211 | 9 |
| `__logb` | `0x00643C38` | 235 | 10 |
| `__nextafter` | `0x00643D23` | 675 | 10 |
| `_ldexp` | `0x0064EA53` | 491 | 15 |

**Target observations.** Both conversion wrappers use the local storage between
EBP-16 and the security cookie at EBP-4. They pass seven stack arguments / 28
bytes to strgtold12, then two / eight bytes to ld12told, and remove the combined
36 caller bytes. Atoldbl passes flag one and a local end-pointer slot, then
returns the converter's status. STRINGTOLD preserves the parser's status and
ORs bit two when the converter returns one. Neither status policy is replaced
with a guessed Boolean result. The retained converter reads input through
word offset ten and writes output DWORDs at zero/four and a WORD at eight:
twelve-byte input storage and ten-byte output span are distinct observations.
Original private record typedefs and signedness remain unknown.

Floor_default saves/restores the raw x87 control word, uses its actual newcw
object, retains all special-value/error paths, and calls the complete frnd
worker. Frnd is an ordinary stack-double / ST0-return worker: it loads the
argument at ESP+12 after two pushes, executes FRNDINT, stores/reloads a double
and returns with no callee cleanup. It is not assigned an invented ST0-input
ABI. Logb, nextafter and ldexp retain raw operation control 0x133F and mask
0xFFFF, complete classification/decomposition/exponent helpers, NaN/error
paths and control restoration. Nextafter retains both exponent scaling paths
(+0x600 and -0x600), sign/mantissa updates and the full two-argument error
policy. Ldexp retains integer-limit and both range paths, copysign, set_exp and
exception handling. All six complete returns are caller cleaned. Runtime
operands, current control/status and error-handler behavior remain unknown.
Attested Ghidra reports no ordinary callers for these six roots; that does
not establish unused code or callback/export status.

**Whole dependencies and data.** Thirteen complete independent anchors / 2184
bytes / 59 fields preserve their existing origins, including the full parser,
converter, cookie checker, x87 controls, decomposition, rounding and error
workers. The parser's own AUX is 1076 bytes: 1028 real code bytes followed by
one 48-byte table with twelve DIR32 cases. Its defining $L1157 label, selector
field, every case definition and actual instruction entry replay. Data is not
decoded as instructions, and the comparison still covers all 1076 bytes and
26 fields. The entire R138 and retained R137/R136/runtime/FP/locale/heap/game
chains replay independently; reviewed children do not grant origin to parents.

Eight whole defining data sections / 88 bytes / zero relocations retain the
complete cookie, four-byte newcw carrier, forty-byte d_inf carrier and folded
double constants. Source newcw initially contains 0x173F; runtime contents
are unknown. Repeated COMDAT constants from separate defining members are
checked separately: 88 is the sum of defining source sections, not unique
target coverage. No eight-byte infinity prefix substitutes for its forty-byte
owner. Source/target hashes, defining symbols and mutability are retained.

**Compiler observations and acceptance.** The natural
`probes/VC7FloatingOperationLayout.cpp` cold-builds a complete 108-byte layout
array using pinned math.h, float.h and fpieee.h. It establishes pointers/int /
four, double and C long double / eight, complete SDK FP80 / ten, exception /
32 with its offsets, and abstract CRT control/status macros. Those macros are
distinct from raw x87 words. Five complete 20-/29-/24-/19-/88-byte natural
function-pointer controls retain unary/binary/scaling caller cleanup of eight,
sixteen/twelve, pointer output, meaningful twelve-byte parser storage and the
status merge. They model ABI/storage and do not assert recovered private C
types. Original private math/conversion C files are absent in the supplied
source tree; ownership rests on pinned full COFF definitions and typed fields,
not invented recovered source. VC7.1 build 3077 and explicit flags remain
per-probe reproducibility settings, without an executable-wide compiler claim.

Thirty-four regression checks reject truncated owners, missing fields/cases,
data entries treated as code, unavailable source claims, incorrect widths,
status/stack/control policies, guessed runtime state and incomplete retained
graphs. All 833 public checks pass. Canonical totals are 3389 resolved (919
authored, 1895 library, 575 compiler), with 962 pending. Exact/source/mapping
remains 60 / 9883 bytes; recorded authored extents remain 872 / 1952956 bytes
and the provisional denominator is 1965299. Full new/retained cold origin
replay, canonical ledger guards, target/project/query attestation, authored
extents, progress/scanner freshness, tests and whitespace checks pass locally.
All 60 exact units cold-replay across eleven objects. The user's 2026-10-04
public MCP acceptance waiver remains in force. Private evidence stays
untracked and shared tools read-only.

## R140 — Complete stream finalization and path-access graph

R140 resolves all four stream finalization/path-access handoff candidates as
library origin: four complete own-AUX primaries / 282 bytes / 11 typed fields.
Replay `scripts/repo-python scripts/verify-stream-finalization-origins.py` with
`config/stream-finalization-origin-evidence.json`. Every defining member,
source/target hash, typed field, complete branch and exit is retained. No
source, mapping or exact reconstruction credit is added, and no auxiliary,
interior, COMMON, data or exception-scope inventory entries are fabricated.

| Complete vendor primary | Address | Whole bytes | Fields |
| --- | --- | ---: | ---: |
| `__freebuf` | `0x00654953` | 43 | 1 |
| `__fclose_lk` | `0x00653E01` | 76 | 4 |
| `__flush` | `0x00652588` | 93 | 1 |
| `__access` | `0x00641B37` | 70 | 5 |

**Target observations and original source.** Freebuf is void and assumes its
caller holds the stream lock. It acts only when inuse / 0x83 and the CRT-owned
buffer bit / eight are both set. It frees the actual base pointer, clears
IOMYBUF and IOSETVBUF / 0x408 (the target uses WORD mask 0xFBF7), and clears
base, current pointer and count. It does not free the user's buffer or add
an invented return value. The complete original `_freebuf.c` is supplied.

Flush checks that the read/write direction bits select writing, bigbuf /
0x108 is set and ptr-minus-base is positive. It passes descriptor, base and
full requested count to the complete write worker, with twelve caller bytes.
Only an equal returned count is success; on a read/write stream success clears
IOWRT, while any unequal result sets IOERR / 0x20 and returns EOF. Every path
resets ptr to base and count to zero, including errors and no-write paths.
No retry, added count normalization or disk-commit policy is introduced.

Fclose_lk initializes its result to EOF. If the stream is in use, it orders
flush, buffer release and low-level close. A negative close result forces EOF;
a nonnegative close frees a non-null temporary filename and clears that pointer.
If close fails, the temporary filename is not freed by this owner. The final
flag reset occurs on every path, and a successful close preserves an earlier
flush error. All original fclose.c/fflush.c branches and exits remain inside
their own 76-/93-byte owners. The helpers assume a caller-held stream lock;
runtime locking, stream/handle validity, buffer/name ownership and IO results
remain unknown. A zero ordinary caller count for fclose_lk is not unused-code
or export/callback evidence.

Access calls the actual GetFileAttributesA import. An invalid attribute result
calls GetLastError and dosmaperr and returns minus one. Otherwise it rejects
the combination of FILE_ATTRIBUTE_READONLY / one and the caller's write-mode
bit / two, setting CRT errno / EACCES / thirteen and DOS error / five. Other
cases return zero. This is the original attribute test, without added ACL or
mode validation. The real caller at `0x00414300` retains its independently
accepted R035 ReplayRecords::FindAvailablePath origin; the library child does
not establish or reclassify caller ownership. Caller paths/modes, ACP and
current error state remain unknown.

**Independent dependency and variant closure.** Six complete anchors / 572
bytes / 42 fields retain free, close, write, dosmaperr, errno and doserrno's
prior R120/R132/R133 origins. Every defining source and typed field replays,
along with the full R139 and older stream/handle/thread/heap/error/FP/game
chains. The new primaries need no standalone data carrier or COMMON definition;
their runtime data belongs to caller-provided streams and retained dependencies.

The complete seventy-byte waccess alternative / five fields has the same code
shape outside relocations. It is retained as a diagnostic rejected variant,
including its own AUX, full defining member, hashes and all typed fields. The
actual PE IAT slot `0x0065718C` imports GetFileAttributesA, whereas its source
requires GetFileAttributesW. That independent contradiction rejects the wide
association even though patching relocation numbers makes its full bytes
congruent. The verifier binds both actual indirect API instruction fields and
all helpers. No masked comparison, convenient prefix or imported database name
supplies acceptance.

**Compiler observations and local acceptance.** The natural
`probes/VC7StreamFinalizationLayout.cpp` cold-builds a complete 112-byte layout
array. It preserves complete FILE / 32 and actual ptr/count/base/flag/file/
tmpfname offsets 0/4/8/12/16/28, char/wchar widths one/two, all ownership/error
masks, DWORD attribute sentinel, distinct CRT/DOS errors and EOF. Five complete
92-/172-/131-/92-/92-byte controls use real pinned declarations and natural
buffer/flush/close/A/W policies. Five full original vendor files and nine
headers replay; available source is not replaced with guessed private types.
These are ownership/type/ABI controls, without exact reconstruction credit.
VC7.1 build 3077 and explicit flags are per-probe reproducibility settings.

Thirty-six regression checks reject incomplete owners, invented scope/data
credit, wrong masks/offsets/ABI, lost short-write/reset/close/error policies,
unexplained dispatch, omitted sources/headers, guessed runtime ownership and
an unsupported wide variant rejection. All 869 public checks pass. Canonical
totals are 3393 resolved (919 authored, 1899 library, 575 compiler), with 958
pending. Exact/source/mapping remains 60 / 9883 bytes; recorded authored
extents remain 872 / 1952956 bytes and the provisional denominator is 1965299.
Full new/retained cold origin replay, canonical guards, target/project/query
attestation, authored extents, progress/scanner freshness, tests and whitespace
checks pass locally. All sixty exact function records and tracked source,
header, build and match inputs are unchanged from R139 `db26a05`; that batch's
60/60 cold exact replay across eleven objects remains applicable. No affected
exact unit needs another replay. The user's 2026-10-04 public MCP acceptance
waiver remains in force. Private evidence stays untracked and shared tools
read-only.

## R141 — Complete exception frame and unwind graph

R141 resolves all six exception frame/unwind handoff roots and their required
callee/parent closure: 27 complete library primaries / 3,502 bytes / 116 typed
fields, plus two existing interior cleanup candidates. Replay
`scripts/repo-python scripts/verify-exception-frame-origins.py` with
`config/exception-frame-origin-evidence.json`. All 29 canonical candidates gain
library origin only. No source, mapping or exact credit is added; three complete
non-inventory auxiliary controls / 123 bytes / four fields gain no invented
candidate rows. The six roots account for 1,503 bytes / 65 fields.

| Root | Address | Previous bytes | Complete own AUX | Fields |
| --- | --- | ---: | ---: | ---: |
| `___FrameUnwindToState` | `0x006455D6` | 173 | 206 | 10 |
| `___DestructExceptionObject` | `0x006456D4` | 52 | 69 | 5 |
| `CallCatchBlock` | `0x0064592D` | 332 | 452 | 16 |
| `BuildCatchObject` | `0x00645AF1` | 368 | 380 | 22 |
| `___CxxExceptionFilter` | `0x00645C6D` | 293 | 293 | 7 |
| `CatchIt` | `0x00645D92` | 103 | 103 | 5 |

**Complete extents and scope entries.** All six roots retain their complete
frame.obj member / 379030 definitions, AUX extents, source/target hashes and
all typed fields. Five canonical extents expand, including the four roots
above and JumpToContinuation / `0x00640721`, 43 to 48 bytes. Its final five
bytes are real POP EBX, LEAVE and RET 8 after JMP EAX, not invented alignment.
CallCatchBlock has three actual INT3 alignment bytes at source offsets
332–334 before its finally entry; its full 452-byte owner includes them.
No first-return or old provisional prefix supplies acceptance.

The existing `0x00645689` / 27-byte and `0x00645A82` / 111-byte candidates
are actual source-defined body labels $L19974 / +179 and $L20060 / +341 inside
complete parents `0x006455D6` and `0x0064592D`. Their real scope handlers start
six bytes earlier, at +173 / `0x00645683` and +335 / `0x00645A7C`. The full
parents include these prologues, body labels, all filters and handler tails.
The two labels gain no standalone function/source/exact interpretation.
Read-only Ghidra helper queries attest the target and complete successfully;
its provisional function inventory does not contain the four queried scope
entries. Raw target mapping, full COFF fields and independent whole decoding
provide extent and callback evidence without database writes.

Five whole readonly source scope tables / 84 bytes contain seven complete
12-byte enclosing/filter/handler records and twelve typed callback fields:
$T19981 / `0x006614E8`, $T20002 / `0x00661500`, $T20075 / `0x00661530`,
$T20094 / `0x00661548` and $T18949 / `0x006615C0`. Every signed enclosing level,
null finally filter, actual non-null handler and filter instruction start is
checked against its complete source parent. The mutable four-byte inconsistency
handler / `0x00670140` has one complete initial pointer to the retained terminate
worker; its current runtime value remains unknown. The full four-byte cookie
at `0x0066FE30` is retained. These are seven whole defining data sections /
92 bytes / thirteen fields, not carrier prefixes or reconstructed private types.

**Dependency and actual ABI closure.** The other 21 complete primaries close
inconsistency, CallSettingFrame, all three member-call trampolines, create/unlink/
destruction frame-chain checks, CallCatchBlock2, abnormal termination, read/write
validators, AdjustPointer, nested unwind, continuation, InternalCxxFrameHandler,
FindHandler, foreign exception handling, try-range selection, SE translation
and TranslatorGuardHandler. Three full non-inventory controls retain
FrameUnwindFilter / 30, CatchGuardHandler / 59 and unwind_handler / 34 bytes.
Eight full anchors / 1,183 bytes / 65 fields retain SEH prolog/epilog, getptd,
terminate, memmove, execute validation, TypeMatch and NLG_Notify1's prior origins.
Memmove's whole 829-byte owner has seven code regions / 709 bytes and six whole
inline tables / 120 bytes; every source-typed case reaches a real code start.
The retained R117 graph still owns NLG_Notify1's shared notification parent.

The nested-unwind REL32 calls the complete six-byte compiler linker thunk at
`0x00654B54`. Its raw IAT slot `0x00657180` independently imports
KERNEL32.dll!RtlUnwind. The thunk retains R030 compiler ownership and its full
hash/extent; the imported implementation gains no library credit. Validator
fields bind actual IsBadReadPtr and IsBadWritePtr imports, without assuming
runtime pointer validity or outcomes. All direct transfers retain either an
actual typed relocation or the same complete defining source section.

Optimized private helpers cannot be declared from their decorated names:
BuildCatchObject copies incoming ECX/EDX to ESI/EDI and reads two stack inputs;
AdjustPointer uses EAX as the base pointer and ECX as adjustment-field storage;
TypeMatch uses ESI/EDI and one stack input; FrameUnwindFilter receives exception
pointer storage in EAX. Canonical calling convention/signature fields stay
unset. The three seven-byte member trampolines pop ECX, exchange the target and
return address on the stack and tail-jump EAX, delegating cleanup to the actual
worker; no fake RET is introduced. CallSettingFrame returns with twelve callee
bytes and switches EBP to the supplied frame plus twelve. Nested unwind and
the continuation epilogue return with eight callee bytes. SE translator calls
use the actual thread field +0x74 and two consecutive caller-cleanup POPs.
The forward-compatible exception handler consumes eight stack arguments / 32
caller bytes. Actual opaque member/funclet/continuation/translator/handler
indirect sites are inventoried completely; current callback targets and results
remain unknown.

**Compiler observations and source limits.** The original private
frame.cpp/ehdata.h/ehhooks.h/trnsctrl.h files are unavailable in the supplied
tree. Full pinned vendor COFF definitions establish ownership, extent, typed
fields and scope provenance; they do not recover complete original private
record identities or source. The real available exsup.inc supports exception
constants. The cold natural `probes/VC7ExceptionFrameLayout.cpp` uses six actual
SDK/CRT headers and a complete 128-byte layout array: EXCEPTION_RECORD / 80,
EXCEPTION_POINTERS / eight, CONTEXT / 716 and _tiddata / 140 bytes, with translator/
current-exception/context/frame-chain offsets 116/124/128/136. Filter results and
handler dispositions are distinguished. Complete independent member classes,
translator/stdcall calls, SEH finally/filter policies and C++ integer throw/catch
produce nine complete 38-/20-/11-/15-/19-/94-/143-/28-/82-byte controls.

All seven generated defining data sections / 167 bytes replay whole, including
the complete 80-byte catch metadata section and all its neighbouring definitions,
not only FuncInfo. The separate ten-byte compiler EH handler has no AUX; its
complete defining code section, full symbol topology, flags and both typed
fields replay. It is a compiler model, not a new target candidate or an invented
private record. Complete generated metadata does not establish TH075's original
private type names/layouts. VC7.1 build 3077 and explicit probe flags remain
per-probe reproducibility settings.

**Local acceptance.** Forty regression checks reject truncated scopes/owners,
wrong enclosing or null-handler records, non-instruction callbacks, invented
source labels, absent tables/dependencies, false private cdecl declarations,
wrong member/translator cleanup, missing SDK facts and descriptor prefixes.
All 909 public checks pass. The new complete origin replay and full retained
R140/older EH/thread/heap/error/stream/FP/game chain cold-replay locally, with
canonical guards, target/project/query attestation, all 872 authored extents,
progress/scanner freshness and whitespace checks. Totals are 3,422 resolved
(919 authored, 1,928 library, 575 compiler), 929 pending and 2,503 excluded.
Source/mapping/exact remains 60 / 9,883 bytes; recorded authored extents remain
872 / 1,952,956 bytes and the provisional denominator is 1,965,299. All exact
function records and source/header/build/match inputs are unchanged from R139
`db26a05`, retaining its 60/60 cold replay across eleven objects. No affected
exact unit needs another replay. Public MCP acceptance remains waived by the
user's 2026-10-04 instruction. Private evidence stays untracked; shared tools
remain read-only. Original private types, current exception/frame/thread state
and opaque callback behavior remain explicitly unknown.

## R142 — Complete C++ throw/frame and standard exception graph

R142 resolves all four C++ throw/frame/standard-exception handoff roots and
the required lifetime/delete closure: eight complete own-AUX library primaries /
331 bytes / twenty typed fields, plus the existing nine-byte type_info finally
entry. Replay `scripts/repo-python scripts/verify-standard-exception-origins.py`
with `config/standard-exception-origin-evidence.json`. Nine candidates gain
library origin only. The thirteen-byte non-inventory what control gains no
invented candidate. Two deleting-destructor controls retain their existing
R038 compiler origins; they are not reclassified as library functions.

| Complete primary | Address | Whole bytes | Fields |
| --- | --- | ---: | ---: |
| `__CxxThrowException@8` | `0x00640C12` | 58 | 2 |
| exception copy constructor | `0x00640C9A` | 74 | 4 |
| type_info destructor | `0x00640E49` | 70 | 7 |
| `___CxxFrameHandler` | `0x006407B8` | 54 | 1 |
| exception default constructor | `0x00640C4C` | 17 | 1 |
| exception assignment | `0x00640DD6` | 31 | 2 |
| exception destructor | `0x00640CE4` | 22 | 2 |
| operator delete | `0x00640F15` | 5 | 1 |

**Complete target extents and behavior.** The type_info destructor expands
from the provisional 61-byte prefix to its whole seventy-byte own AUX. The
existing `0x00640E86` / nine-byte candidate is its actual source-defined
$L19209 finally entry at +61, which pushes lock fourteen, calls the complete
unlock worker, pops the caller argument and returns. The parent acquires that
same lock before checking/freeing cached-name storage at +4, invokes finally
on its normal path and retains the complete scope entry/tail. It does not
reset the dying object's cached pointer. This finally label starts at its
scope callback, unlike R141's six-byte-later body labels. No standalone source,
exact or mapping credit is assigned to it.

The complete frame shim saves incoming EAX as opaque function metadata and
forwards four stack handler inputs, that saved metadata and three zeros to the
whole retained InternalCxxFrameHandler. It cleans 32 caller bytes, restores its
registers and returns the handler result. Zero ordinary Ghidra callers does
not imply unused code: independent compiler EH carriers load metadata in EAX
and transfer to this symbol. Its private ABI cannot be replaced by a five-stack-
argument conventional prototype; canonical declarations remain unset.

Throw copies exactly eight DWORDs from its whole readonly 32-byte template at
`0x00660E74`. Complete values are exception code E06D7363, noncontinuable flag
one, zero record/address, parameter count three, magic 19930520 and two zero
input slots. It fills the object/opaque descriptor slots at template +24/+28,
passes code/flags/count and the three-word parameter address at +20 to the
actual KERNEL32.dll!RaiseException IAT slot `0x00657184`, and retains its real
RET 8. The supplied SDK EXCEPTION_RECORD is eighty bytes, with fifteen maximum
parameters; it does not establish an invented complete private 32-byte type.
Original private throw descriptors and exception delivery outcomes remain
unknown. The 84 observed callers gain no ownership from the reviewed worker;
older unresolved catch/parent extents remain pending.

Exception default construction clears message +4 and ownership flag +8 and
writes the actual exception vtable. Copy construction copies the ownership
flag: an unowned message pointer is borrowed directly; an owned message gets
strlen-plus-one allocation and strcpy only when allocation succeeds. A failed
allocation leaves the copied ownership flag and a null message, matching the
whole original body. Assignment guards self-assignment, destroys the current
object and invokes the complete copy constructor on the same storage. The
ordinary destructor frees +4 only when the ownership flag is nonzero. The
complete thirteen-byte what control returns +4 or the complete original
18-byte literal `Unknown exception`. Copy/assignment return with four callee
bytes. The five-byte operator delete is a source-bound tail transfer to the
independently reviewed free worker, without a fake return or a new allocation
policy. Runtime object/message ownership and allocation outcomes stay unknown.

**Whole vtable, RTTI and weak-reference provenance.** Fifteen complete defining
source data sections / 260 bytes / eighteen fields close both classes' vtables,
locators, descriptors, hierarchy/base graphs, the throw template, finally scope
and fallback literal. The exception vtable address point is +4 inside a whole
12-byte section at `0x00660E94`; type_info's is +4 inside a whole eight-byte
section at `0x00660ED8`. Each prefix is a real typed locator pointer, not omitted
padding. A source anchor at +4 selects the whole section; every definition,
byte and field is compared from its actual base. The two base arrays are five
bytes each, including the real byte after their pointer; four-byte prefixes
are rejected. All initial writable type descriptors and readonly metadata
retain complete source/target extents and actual storage mutability.

The vtable fields reference weak `??_Eexception` / `??_Etype_info` symbols.
Their actual storage-class-105 COFF records each have one AUX, fallback tag 17
and search-characteristics value two. The referenced external scalar symbol
also has a complete strong definition in that same pinned member. The full
archive has no strong definition of the weak E symbol. This evidence is not
rewritten as an unconditional alias/search-mode-three claim. Actual vtable
pointers land on complete 28-byte scalar controls at `0x00640DBA` and
`0x00640E8F`, whose whole defining sections have no function AUX. Their full
COFF topology, flags, bytes and both fields replay, along with the independent
53-body R038 cold compiler control. R038 names/origins remain unchanged.
Original link inputs/search decisions beyond the supplied archive evidence
remain unknown. Every weak callback still requires a real strong source code
entry in the complete catalog, never a guessed same-address label.

Eleven full anchors / 641 bytes / 26 fields retain nine prior library owners
(strlen, malloc, strcpy, SEH prolog/epilog, lock/unlock, free and the complete
internal EH handler) and the two compiler controls. R141 and its full older
EH/thread/heap/error/stream/FP/game chain replay, together with R038. The seven-
byte strcpy entry retains its independently reviewed full shared parent through
that chain. Current RTTI caches and private handler behavior are not inferred
from complete initialized metadata or raw API identity.

**Compiler observations and local acceptance.** The original private
throw.cpp/stdexcpt.cpp/typinfo.cpp/trnsctrl.cpp implementation files are absent
from the supplied tree. Real stdexcpt.h delegates to the supplied complete
exception header; typeinfo.h supplies the real SDK type_info interface. The
natural `probes/VC7StandardExceptionLayout.cpp` cold-builds an 88-byte layout
array and all 81 actual included headers are hash-pinned. SDK exception,
type_info and the RTTI exception classes are twelve bytes; the independent
complete message owner is twelve bytes with its own public +4/+8 fields.
This independent model does not instantiate an incomplete TH075 game owner.
The required /Zc:wchar_t satisfies the actual internal yvals.h requirement;
VC7.1 build 3077 and all flags remain per-probe reproducibility settings,
not an executable-wide compiler profile.

Twenty-two complete SDK/placement/member/delete/raise/ownership/integer-throw/
catch controls / 1,010 bytes / 36 fields replay. Eight complete generated data
sections / 219 bytes / thirteen fields include both the whole 36-byte ownership
EH metadata section and the whole 80-byte catch metadata section. Three no-AUX
code carriers / 81 bytes / seven fields replay whole: a 44-byte independent
scalar control, the complete 27-byte section containing a cleanup funclet and
its following EH handler, and the separate ten-byte integer-catch EH handler.
No cleanup prefix or FuncInfo-only view substitutes for its defining section.
These are compiler/source-family controls without target exact credit.

Forty-two regression checks reject incomplete parents, omitted locator prefixes,
wrong weak AUX tags/search modes, invented source/private ABI, lost ownership/
self-assignment/unlock policies, wrong cleanup/API identity and partial model
metadata/carriers. All 951 public checks pass. Full new/retained cold origin
replays, canonical guards, target/project/query attestation, all 872 authored
extents, progress/scanner freshness and whitespace checks pass locally. Totals
are 3,431 resolved (919 authored, 1,937 library, 575 compiler), 920 pending and
2,512 excluded. Source/mapping/exact remains 60 / 9,883 bytes; recorded authored
extents remain 872 / 1,952,956 bytes and the provisional denominator is
1,965,299. Exact rows and all source/header/build/match inputs are unchanged
from R139 `db26a05`, preserving its 60/60 cold replay across eleven objects.
No affected exact unit needs another replay. The user's public MCP acceptance
waiver remains in force. Private evidence is untracked; shared tools are read-only.

## R143 — Complete derived RTTI-exception lifetime families

R143 resolves the three existing handoff candidates as library origins:
`0x00640D38`, `0x00640D74` and `0x00640DAF`. Each retains its complete
11-byte own-AUX extent and both typed fields: 33 bytes and six fields in all.
Replay `scripts/repo-python scripts/verify-derived-exception-origins.py` with
`config/derived-exception-origin-evidence.json`. No source, mapping or exact
credit is assigned. Original target names remain provisional.

| Provisional source role | Destructor | Constructed vtable address point | Destruction-stage address point | Retained R038 compiler caller |
| --- | --- | --- | --- | --- |
| bad_cast | `0x00640D38` | `0x00660EB8` | `0x00660EB8` | `0x00640DF5` |
| bad_typeid | `0x00640D74` | `0x00660EC4` | `0x00660EC4` | `0x00640E11` |
| __non_rtti_object | `0x00640DAF` | `0x00660ED0` | `0x00660EC4` | `0x00640E2D` |

**Target observations and whole source alternatives.** Each complete
primary writes the destruction-stage vtable through ECX and tail-jumps
straight to the complete R142 base exception destructor `0x00640CE4`.
There is no standalone RET or fabricated intermediate bad_typeid destructor
call. The last two source COFF bodies, including their two source relocation
records, are identical. Their linked target bytes differ in the address-
dependent REL32 tail displacement. This corrects the preceding handoff's
statement that all eleven target bytes were equal. Both full source owners
match both targets after independent relocation; the bad_cast owner matches
only `0x00640D38` when its real vtable object is bound. All three complete
source alternatives are retained and cold-read, with full own AUX extents,
source definitions, every typed field and complete relocated results.
Neither relocation masking nor a short destructor shape chooses class identity.

The paired graph supplies context independently of that equal body. Six
non-inventory message/copy constructors retain their own complete AUX:
`0x00640D07` / 25, `0x00640D20` / 24, `0x00640D43` / 25,
`0x00640D5C` / 24, `0x00640D7F` / 24 and `0x00640D97` / 24 bytes.
The first two classes call complete base exception message/copy constructors;
non-rtti construction calls the complete bad_typeid message/copy pair and
then installs its own constructed vtable. Each preserves RET 4 and ECX member
calling behavior. The whole 61-byte base message constructor at `0x00640C5D`
allocates strlen-plus-one storage, conditionally copies the message and sets
ownership to one even if allocation fails. The complete thirteen-byte what
control at `0x00640CFA` retains the whole fallback literal. These eight
non-inventory bodies / 220 bytes / seventeen fields gain no invented rows.

**Complete defining data and callbacks.** Thirty-one whole vtable/RTTI/literal
sections / 543 bytes / 48 fields close the three derived classes and the
exception/type_info base metadata. The three constructed vtables occupy whole
12-byte sections at `0x00660EB4`, `0x00660EC0` and `0x00660ECC`; their real
address points are +4 and their locator prefixes and both callback slots are
compared. Derived type descriptors preserve all 23, 25 and 32 source bytes and
initial writable state. Base arrays preserve all nine, nine and thirteen bytes,
including the byte after their last pointer. The non-rtti base sequence is
non-rtti, bad_typeid, exception. Every locator, hierarchy, base descriptor,
base-array pointer, type_info vtable and literal retains its actual full
source section, typed fields and storage mutability.

Five actual weak E records retain storage class 105, one AUX, their real
fallback tags and search-characteristics two. Their corresponding G symbols
have strong definitions in complete no-AUX code sections; the supplied whole
archive has no strong E definition. Search mode two is not rewritten as a
forced alias mode three. Actual derived vtable callbacks land on the three
whole 28-byte R038 compiler controls, and each control's full source-bound
REL32 field calls its paired destructor. The complete constructed vtable,
RTTI and constructor graph identifies the source role context even where the
standalone destructor owners remain equal alternatives. Original link inputs
and search decisions beyond this supplied archive remain unknown.

Ten complete anchors / 400 bytes / eighteen fields preserve five existing
library origins (base destructor/copy constructor, strlen, malloc and strcpy)
and five existing R038 compiler origins (the three derived deleting controls,
exception and type_info). R142 replays its entire older dependency chain and
the independent 53-body R038 cold proof. No compiler control is reclassified.

**Compiler observations and acceptance.** The original stdexcpt.cpp is absent.
The real supplied typeinfo.h declares complete SDK bad_cast and bad_typeid
classes deriving from exception, and __non_rtti_object deriving from
bad_typeid. The natural `probes/VC7DerivedExceptionLayout.cpp` uses those actual
complete interfaces and separate complete inheritance models; it does not
instantiate an incomplete reconstructed game owner. A cold 32-byte array
reports four-byte pointers and twelve-byte SDK/model class sizes. All eleven
actual included headers are hash-pinned. The explicit final /GR enables RTTI
for this independent model, while /Zc:wchar_t satisfies the actual header;
these are probe reproducibility settings, not a target-wide compiler profile.

Twenty-three complete natural SDK constructor/copy/destructor/delete/member
controls and model bodies / 1,017 bytes / 33 fields replay. All twenty generated
RTTI/vtable data sections / 406 bytes / 33 fields replay from their complete
bases. All three no-AUX generated scalar code sections / 132 bytes / six fields
also replay. No short scalar, vtable address point or base-array pointer is
substituted for its defining section.

Thirty-one regression checks reject truncated extents, lost compiler ownership,
swapped incoming destructor callbacks, wrong destruction-stage vtables, omitted
locator prefixes/trailing array bytes, false intermediate calls, incorrect
constructor/copy/cleanup ABI, changed weak search semantics, removed full
source alternatives, partial generated sections and invented SDK/runtime
claims. All 982 public checks pass. The full new/retained cold evidence replay
passes once, followed by canonical ledger write/read-back guards; it was not
repeated merely for the ledger update. Target/project/query attestation, all
872 recorded authored extents, exact-input preservation, progress/scanner
freshness and whitespace checks pass locally. Totals are 3,434 resolved
(919 authored, 1,940 library, 575 compiler), 917 pending and 2,515 excluded.
Source/mapping/exact remains 60 / 9,883 bytes; recorded authored extents remain
872 / 1,952,956 bytes and the provisional denominator is 1,965,299. All exact
inputs/rows are unchanged from R139 db26a05, preserving its 60/60 cold proof
across eleven objects. No affected exact unit requires another cold build.
The user's public MCP acceptance waiver remains in force; the no-auth route
and private random path remain unchanged. Private evidence is untracked.

## R144 — Complete longjmp and SEH read-probe graph

R144 resolves both handoff candidates as library origins:
`0x00643604` / complete 121-byte `_longjmp` and `0x0064DC10` / complete
66-byte `__rt_probe_read4@4`. Their eight typed fields retain full code,
actual defining source/absolute/scope/API context and independent SDK controls.
Replay `scripts/repo-python scripts/verify-jump-unwind-origins.py` with
`config/jump-unwind-origin-evidence.json`. No source, mapping or exact credit
is assigned. Original executable names and private declarations remain
provisional even where the supplied source/target bodies agree completely.

**Complete target extents and behavior.** Longjmp's own COFF AUX is 121 bytes,
including the real RET at `0x0064367C` after the indirect saved-return jump.
The provisional 120-byte ledger omitted that byte; its complete extent now
ends at `0x0064367C`. The RET is present in the pinned source and target, not
invented to obtain a match. No existing interior inventory candidate is inside
either complete primary, and no standalone label row is invented.

Longjmp loads the saved EBP and exception registration before comparing the
registration to FS:[0]. When they differ it calls the complete global unwind
worker. For a nonzero registration it probes the cookie at +32; a readable
VC20 cookie (`0x56433230`) permits the opaque +36 UnwindFunc callback, invoked
with the buffer pointer on the stack. A null callback skips local unwind;
a missing/unreadable/wrong cookie takes the complete old local-unwind path
with saved TryLevel +28. The saved EIP +20 is passed in EAX to the complete
NLG notify worker with saved EBP and stack code zero. Longjmp then restores
EBX, EDI, ESI and ESP, adds four to the restored stack and jumps to saved EIP.
CMP-one/ADC-zero maps zero return input to one while preserving every nonzero
input, including negative values. The saved callback identity/ABI, live
registrations, valid saved state and runtime outcomes remain unknown.
The two ordinary callers gain no ownership from this reviewed library child.

The read probe's entire 66-byte own AUX includes its ordinary load/success
path, filter at +29 and exception handler at +49. Ghidra's ordinary flow skips
that filter/handler region; the full source and target decode does not.
Successful DWORD access returns one. Its filter follows the exception-pointer
chain and returns one only for access violation `0xC0000005`; other exception
codes return zero, preserving continue-search semantics. The handler restores
saved ESP and returns zero through the common epilog. The filter has RET 0;
the callable primary has RET 4. The one whole readonly 12-byte `$T19221`
section at `0x006639E8` has enclosing level -1 and typed filter/handler pointers
`0x0064DC2D` / `0x0064DC41`. Both land on actual defining source entries in the
complete primary, with no guessed same-address label or partial callback body.

**Actual ABS and retained dependency provenance.** Longjmp's first field is
DIR32 `__except_list` at +12 in its FS comparison, resolved to zero. This is
not an object at PE virtual address zero. The whole supplied libcmt archive
has one external defining symbol: exsup.obj member 1210238, storage class two,
section -1 (ABS), value zero. The longjmp member retains the actual external
undefined referring record. The verifier rereads the defining member identity,
scans the whole archive for competing strong definitions, checks the exact
symbol record and proves the field is the displacement of the FS instruction.
No undefined/static symbol, guessed zero binding or GS instruction substitutes
for this independent ABS provenance.

Five whole anchors / 236 bytes / five fields preserve prior library origins:
global unwind 32, local unwind 104, NLG notify 24, SEH prolog 59 and SEH epilog
17 bytes. The full R141 replay retains their R117/R025 source owners, actual
shared tails, scope/NLG state and unwind import route through its dependency
chain. Private unwind/NLG register contracts are kept explicit: NLG receives
EAX destination, EBP saved frame and a stack code, rather than an invented
three-stack-argument prototype. Canonical private calling declarations remain
unset. Complete source/body comparisons and every typed code/data/absolute
field are required; relocation masking is never acceptance evidence.

**Compiler observations and acceptance.** Original longjmp.asm/sehsupp.c
implementation files are unavailable. The supplied exsup.inc preserves the
jump-buffer fields and VC20 cookie, while the real SDK setjmp.h supplies a
complete 64-byte x86 `_JUMP_BUFFER`/jmp_buf and cdecl longjmp declaration.
The probed cookie and old-unwind fallback do not establish the version or
extent of a live original saved buffer. The natural `probes/VC7JumpUnwindLayout.cpp` cold-builds an 88-byte layout array
with all eleven buffer offsets, six-word unwind-data size, real NT_TIB FS
exception-list offset and SDK exception/filter constants. All 72 actual
included headers and the complete exsup.inc are hash-pinned. The probe uses
complete actual SDK types and independent behavior controls, without defining
an original game owner or inventing private callback layouts.

Eight complete natural SDK jump/capture/result/member/SEH/filter/finally
controls / 338 bytes / twelve fields replay. Both generated whole scope data
sections / 24 bytes / three fields replay. All generated code sections are
covered by complete own AUX extents; there are no orphan code carriers in
this probe. Debug controls can retain source-emitted returns even under a
noreturn declaration; emitted body observations are recorded faithfully.
VC7.1 build 3077 and all explicit flags remain per-probe reproducibility
settings, not an executable-wide target compiler profile.

Thirty-six regression checks reject omitted final RET/filter/handler code,
wrong cleanup or exception policies, incomplete scopes, lost saved-register/
return/cookie/normalization behavior, invented callback identity and wrong ABS
provenance. Synthetic real COFF records and decoded segment instructions
exercise absent/undefined/static/duplicate/nonzero ABS definitions, referring
record identity, FS-versus-GS and actual displacement placement. All 1,018
public checks pass. The complete new/retained cold evidence replay passes once,
followed by canonical ledger write/read-back guards. Target/project/query
attestation, all 872 recorded authored extents, unchanged exact inputs,
progress/scanner freshness and whitespace checks pass locally. Totals are
3,436 resolved (919 authored, 1,942 library, 575 compiler), 915 pending and
2,517 excluded. Source/mapping/exact remains 60 / 9,883 bytes; recorded authored
extents remain 872 / 1,952,956 bytes and the provisional denominator is
1,965,299. All exact inputs/rows remain unchanged from R139 db26a05, preserving
its 60/60 cold proof across eleven objects. No affected exact unit needs a
repeat build. The public MCP acceptance waiver remains in force; the no-auth
route and private random path remain unchanged. Private evidence is untracked.

## R145 — Complete small-block heap integrity worker

R145 resolves `0x0064AFC5` / complete 793-byte `___sbh_heap_check` as a
library origin. Replay `scripts/repo-python scripts/verify-small-heap-integrity-origins.py`
with `config/small-heap-integrity-origin-evidence.json`. The complete own COFF
AUX agrees with the provisional extent through `0x0064B2DD`: all 61 branches,
both early/shared epilogues and every final error-return tail are retained.
No interior candidate is present, no wrapper is invented and no source,
mapping or exact reconstruction credit is assigned.

**Target and source observations.** The worker checks the full header range,
each REGION, committed groups and their eight pages, entry front/back tags,
allocated counters, 64 free-list size classes, links/counts/closure and final
group/header allocation vectors. Actual supplied winheap.h defines HEADER
20 bytes, REGION 16,836 bytes, GROUP 516 bytes, ENTRY 12 bytes, LISTHEAD eight
bytes and ENTRYEND four bytes. The allocation group spans 32,768 bytes, each
page 4,096 bytes and each region 32 groups. Page entries start at +12; valid
sizes are aligned to 16 bytes with a 16-byte minimum and 4,080-byte maximum.
Allocated entries are limited to 1,024 bytes. A clear most-significant commit
bit selects a committed group; low front-tag bit one marks an allocated entry.
Free-list class is `(size >> 4) - 1`, upper-clamped to 63. Source returns zero,
-1, -2 and -4 through -17; no -3 result is invented. These are static target/
vendor observations, not an assertion that the live game heap is valid.

All eight DIR32 fields have independent complete provenance. Three real
indirect calls target IsBadWritePtr's KERNEL32.dll IAT slot `0x00657154`:
header count times 20, REGION size 16,836 and group range 32,768. Five fields
bind `___sbh_cntHeaderList` / `0x0068FA60` and `___sbh_pHeaderList` /
`0x0068FA64`. Each has one actual external four-byte tentative COMMON record
in the entire pinned archive, sbheap.obj member 827680. The verifier scans
all members for nonzero COMMON/strong alternatives and rereads complete
source/member records. These are not initialized source pointers. Their
actual complete PE storage is in the writable loader zero-fill tail of .data.
Both independent bindings retain R120's already accepted heap provenance and
its full cold dependency replay. Original external linker inputs beyond the
supplied archive, live pointers/counts/contents and API outcomes remain unknown.
The absence of ordinary Ghidra callers grants no ownership or unused-code claim.

**Independent compiler evidence.** The supplied complete read-only sbheap.c
was cold-built with pinned VC7.1 build 3077 using explicit `/O1 /Ob1 /Gy /Zi
/GS /D_CRTBLD /D_MT` and the actual CRT source include path. Its selected
complete own-AUX function reproduces all 793 source bytes and all eight typed
field records from the archive. Both archive and cold C bodies are linked
from the independently resolved COMMON/API destinations and compared against
every target byte, with no masked or prefix acceptance. The other functions
and data emitted by that translation unit gain no reviewed origin credit.
The complete source, winheap.h and all 72 actual included headers are pinned.
These flags are per-control reproducibility settings, not an executable-wide
compiler profile or a claim about original private declarations.

The natural `probes/VC7SmallHeapIntegrityLayout.cpp` independently cold-builds
a complete 152-byte layout array and six complete range/entry/class/commit
controls / 217 bytes / three API fields. Every allocated probe code/data
section is accounted for; no orphan data or no-AUX code carrier is present.
Its complete actual vendor/SDK types do not define a reconstructed game owner.
Thirty regression checks reject shortened extents, missing epilogues/branches/
API calls, wrong COMMON definitions/storage/alternatives, lost retained heap
context, changed vendor reproduction inputs/layout/bit/class semantics and
invented runtime knowledge. Independent linker fixtures exercise actual
addends, full extents, wrong destinations, overlaps and missing provenance.

The complete new/retained cold evidence replay passes, followed by canonical
ledger write/read-back. All 1,048 public checks, authored-extent verification,
target/project/query attestation, progress/scanner freshness and whitespace
checks pass locally. Totals are 3,437 resolved (919 authored, 1,943 library,
575 compiler), 914 pending and 2,518 excluded. Source/mapping/exact remains
60 / 9,883 bytes. All tracked exact inputs and 60 accepted rows remain
unchanged from R139 db26a05, preserving its 60/60 cold proof over eleven
objects; no affected exact unit requires replay. Recorded authored extents
remain 872 / 1,952,956 bytes and the provisional denominator is 1,965,299.
Public MCP acceptance remains waived. The no-auth route and private random
path remain unchanged; private logs/objects/diagnostics remain untracked.

## R146 — Complete power dispatch and both math parents

R146 resolves four existing candidates as library origins: `0x00643770` /
complete 59-byte `__CIpow`, `0x0064DC60` / complete 2,886-byte
`__CIpow_pentium4`, its actual exported `__pow_pentium4` entry at
`0x0064DC79` / +25, and the actual static `start` entry at `0x006437CD` /
+34 inside the full 527-byte `__CIpow_default` parent. The latter extends
through its whole 493-byte shared tail. Replay
`scripts/repo-python scripts/verify-power-math-origins.py` with
`config/power-math-origin-evidence.json`. No source, mapping or exact credit
is assigned; both interior entries remain evidence-backed labels, without
invented independent AUX records or canonical private declarations.

**Complete extent and source-family reconciliation.** The provisional CI
wrapper was 84 bytes, crossing into the fallback's 25-byte CI prelude. Its
own AUX is 59 bytes. The provisional SSE parent was only 25 bytes; its own
AUX is 2,886, containing every exceptional/shared/return tail and the existing
+25 entry. The original 221-byte fallback core candidate is the real source
`start` label at +34; its complete defining parent retains the entire 493-byte
continuation through `0x006439B9`. These reconciliations compare full defining
owners, never convenient truncated extents. The entire 650-byte source code
carrier at `0x00643730` contains a 63-byte C wrapper, one actual NOP with a
zero-length `_$$$00002` AUX, the 59-byte CI wrapper and the 527-byte default
parent. The alignment byte gains no candidate credit. Non-inventory complete
source controls remain controls, including the real C default entry at +25.

The complete atan/log/log10 CI wrappers are each 59 bytes and indistinguishable
outside their two typed fields. Their whole defining code carriers are
282 / 336 / 336 bytes and differ at 106 / 146 / 146 non-field positions.
R146 retains those complete negative alternatives. The actual typed SSE
operation binds the complete pow parent; both default and SSE source owners
match completely with independent fields. This distinguishes pow without
inferring ownership from a library child or a matching wrapper prefix.
Original handwritten math assembly implementations are unavailable; complete
pinned archive COFF and independent real SDK controls supply the evidence.

**Target dispatch and private ABI observations.** The CI wrapper checks the
actual SSE dispatch state, MXCSR exception-mask bits `0x1F80` and x87
exception-mask bits `0x7F`. It restores its eight-byte scratch stack before
tail transfer; disabled or unsuitable states reach the full x87 fallback.
The SSE CI prelude aligns its stack, swaps the x87 pair, stores both doubles
and calls the actual exported +25 stack entry. All sixteen SSE RET sites and
62 branches remain in the full parent. The default CI path marshals its pair,
loads the high argument word in EAX and calls `start` +34; the exported C path
uses the complete fload helper and falls through that same source entry.
Its full default-control-word checks, special values/error routes, four RET
sites and 33 branches remain. SDK public pow/matherr/controlfp controls do
not supply invented private CI/helper prototypes. Live dispatch state,
control words, inputs, numerical accuracy and runtime outcomes remain unknown.

Six whole defining data sections / 14,862 bytes / four fields replay. The
pow constant/table source section is 14,640 bytes at `0x00663A00`, containing
all 21 actual named definitions, complete reciprocal/log/exp tables and masks.
Its SIGMASK anchor is interior at +14,480 / `0x00667290`; comparison starts
at the real whole section base. No single-mask prefix or guessed array count
substitutes for the whole table. Full default-name, fastflag, x87 constants,
return-dispatch pointers and floating adjustment state also replay. Every
code/data pointer reaches its actual complete source owner and instruction
entry. The SSE dispatch state is the unique four-byte tentative COMMON from
cpu_disp.obj at `0x0068FBA0`, with whole-archive alternatives, complete loader
zero-fill and independent retained R130 provenance. Original external linker
inputs and live mutable state are not inferred.

The two own-AUX primaries cover 2,945 bytes / 61 fields. Five whole auxiliary
controls cover 787 bytes / 32 fields. Nine whole independent retained anchors
cover 1,957 bytes / 66 fields, including complete libm error, load/control-word,
argument-error, pow helper and enclosing x87/return-dispatch owners. The two
non-inventory anonymous parents and fast-exit control retain their full R130
source identity; no new inventory credit is invented. Full R130 and its
independent dependency chain cold-replay. All newly reviewed own bodies and
the full carrier are linked from independently defined fields and compared
against every byte, unmasked. Every actual local/shared/direct edge is checked
against complete source and target instruction starts.

**Compiler observations and local acceptance.**
`probes/VC7PowerMathLayout.cpp` uses complete actual SDK/vendor records and
public ABI/intrinsic controls. Its 104-byte layout includes the real 32-byte
_exception, ten-byte FP80, full field offsets and math/exception/control-word
constants. All 77 actual included headers are pinned. Five complete natural
controls / 160 bytes / three fields cold-build; every allocated probe code/
data section is accounted for, with no orphan sections or game-owner layout.
Flags are explicit per-control reproducibility settings under VC7.1 build
3077, not an executable-wide compiler claim. Thirty-nine regression checks
exercise full extents/tables/source alternatives, real shared entries/dispatch
contracts and actual independent DIR32/REL32 arithmetic, typed source symbols,
field ranges, overlaps and complete linked-byte preservation.

The new/retained cold evidence replay passes, followed by canonical ledger
write/read-back. All 1,087 public checks, target/project/query attestation,
authored-extent verification, unchanged exact inputs, progress/scanner freshness
and whitespace checks pass locally. Totals are 3,441 resolved (919 authored,
1,947 library, 575 compiler), 910 pending and 2,522 excluded. Source/mapping/
exact remains 60 / 9,883 bytes. All exact inputs and 60 accepted rows remain
unchanged from R139 db26a05, preserving its 60/60 cold proof across eleven
objects. No affected exact unit requires replay. Recorded authored extents
remain 872 / 1,952,956 bytes; the provisional denominator is 1,965,299.
The public MCP acceptance waiver remains in force. The no-auth route/private
random path remain unchanged; private logs, objects and diagnostics are untracked.

## R147 — Complete acos parent and actual shared core

R147 resolves the two handoff candidates as library origins: `0x00643B10` /
complete 203-byte `__CIacos`, and `0x00643B2D` / actual source static `start`
+29 with its entire 174-byte shared continuation. Replay
`scripts/repo-python scripts/verify-acos-math-origins.py` with
`config/acos-math-origin-evidence.json`. No source, mapping or exact credit is
assigned; original private declarations and executable symbol names remain
provisional. The core is an actual entry in the complete parent, without an
invented independent AUX or complete game-owner layout.

**Extent reconciliation and target behavior.** The provisional parent was a
20-byte CI prefix; its complete own AUX is 203 bytes through `0x00643BDA`.
The real exported `_acos` C entry is +20, and static `start` is +29. The CI
path stores ST0 without popping into twelve-byte scratch space, calls the
complete checkTOS helper, calls static start and restores the scratch stack.
The C entry points EDX at its stack argument, calls the complete fload helper
and falls through the same static entry. The core's former 12,494-byte span
was a provisional Ghidra boundary running through many unrelated contexts.
The actual complete shared continuation is 174 bytes through the parent's
final RET. Exactly these two ledger rows change; every other origin row,
candidate and independently accepted extent is preserved. The complete
203-byte parent is compared, not a shortened selection from the huge span.

Incoming helper EAX/EDX and ZF are part of the actual private protocol.
PUSH EDX / WAIT / FNSTCW preserve the flags before the actual JE special-value
route; no ordinary C prototype is invented for that flags-dependent entry.
The full default-control-word check uses `0x027F`. The observed ordinary path
computes `(1+x)*(1-x)`, takes SQRT, exchanges the x87 pair and uses FPATAN.
Complete high/fraction/sign tests select FLDPI for the -1 endpoint and FLDZ
for +1. NaN conversion calls the actual complete helper, while invalid/range
paths load the extended-precision indefinite constant and retain complete
one-argument error handling. The two fastflag routes reach the same complete
fast-exit owner. Operation code 13 and the actual operation-name context are
preserved. Both RET sites and all fourteen branches replay. These are static
source/target observations; numerical accuracy, live classification/control
state, NaN payloads and runtime matherr/exception outcomes remain unknown.
The lack of ordinary callers grants no unused-code or ownership inference.

**Independent complete ownership and data evidence.** All thirteen typed
fields are linked from independently defined whole code/data owners, then
every relocated source byte is compared unmasked with the target. Seven
whole retained FP anchors / 252 bytes / three fields preserve checkTOS,
fload, load-CW, fast-exit, math-exit, QNaN conversion and one-argument error
owners. Their canonical origins remain unchanged. The non-inventory fast-exit
source retains its actual complete R146/R130 context, without new candidate
credit. Full R146 and its independent math/runtime dependency chain cold-replay.

Three whole defining source data sections / 60 bytes are preserved: the
complete eight-byte loader-zero fastflag storage at `0x0068E2C0`, complete
eight-byte operation-name section at `0x00670110`, and whole 44-byte x87
constant/classification section at `0x00670270`. No four-byte fastflag, name
prefix or single ten-byte indefinite value substitutes for its whole defining
section. Complete initialized bytes, source records, actual writable target
storage and loader zero-fill are checked. Original handwritten acos source is
unavailable; complete pinned archive COFF and independent SDK controls supply
the evidence without claims about original external inputs or live state.

**Compiler controls and acceptance.** `probes/VC7AcosMathLayout.cpp` uses
complete actual SDK math/exception/FP80 records and public acos/matherr/
controlfp declarations. Its 88-byte layout and five complete public ABI/range/
NaN/control-word controls / 157 bytes / five fields cold-build. Both generated
whole eight-byte positive/negative-unit sections are covered; all code/data
sections are accounted for and no orphan code carriers are emitted. All 74
actual included headers are pinned. Private intrinsic/helper declarations
remain unset. Explicit flags under VC7.1 build 3077 are per-control
reproducibility settings, not an executable-wide compiler profile.
Thirty regression checks reject prefix/huge-span acceptance, missing shared
entries/returns, partial state, lost helper flags, wrong endpoint/NaN/error
routes, incomplete generated constants and invented runtime/private ABI claims.

The complete new/retained cold evidence replay passes, followed by canonical
ledger write/read-back and exact two-row/prior-origin preservation guards.
All 1,117 public checks, authored-extent verification, target/project/query
attestation, unchanged exact inputs, progress/scanner freshness and whitespace
checks pass locally. Totals are 3,443 resolved (919 authored, 1,949 library,
575 compiler), 908 pending and 2,524 excluded. Source/mapping/exact remains
60 / 9,883 bytes. All exact inputs and sixty accepted rows remain unchanged
from R139 db26a05, preserving its 60/60 cold proof over eleven objects; no
affected exact unit requires replay. Recorded authored extents remain
872 / 1,952,956 bytes; the provisional denominator remains 1,965,299.
The public MCP acceptance waiver remains in force, with the existing no-auth
route/private random path unchanged. Private logs/objects/diagnostics remain
untracked. The complete-origin objective remains unfinished.

## R148 — Complete floor dispatch and defining source carrier

R148 resolves the existing `0x006439C0` candidate as library origin `_floor`.
Its complete own COFF AUX is 64 bytes through `0x006439FF`; the former
289-byte extent is the entire defining carrier containing the contiguous
225-byte `__floor_pentium4` at `0x00643A00`. The complete 289-byte carrier
is compared without masking or truncation. The SSE owner has no inventory
candidate and earns no additional credit. Replay
`scripts/repo-python scripts/verify-floor-math-origins.py` with
`config/floor-math-origin-evidence.json`. Exactly one existing origin row
changes; every independently accepted owner is preserved. There is no
source, mapping, private ABI or exact credit.

**Whole operation and provenance.** The wrapper checks the actual SSE state,
MXCSR mask `0x1F80` and x87 mask `0x7F`, restores its eight-byte scratch area,
and selects the actual default tail or complete SSE owner. The default
`0x0064E980` / 211-byte `__floor_default` retains R139; the complete 654-byte
libm error owner retains R130. Their combined 865 bytes and 37 fields have
independent retained source evidence. Full R146 and R139 cold controls replay
before acceptance, preserving all prior origins. All ten wrapper/SSE fields
bind independently defined whole code/data/COMMON owners before complete
unmasked comparison. The unique whole-archive SSE COMMON definition remains
the independently retained four-byte CPU-dispatch owner and actual loader
zero-fill region; its original external inputs and live value remain unknown.

The complete SSE control handles positive/negative exponent thresholds,
truncation and negative fractional correction, both signed-zero routes,
NaN classification and operation code 1005 (`0x3ED`) at the actual complete
error worker. All six branches and five RET sites are retained. These are
static source/target observations, not claims about runtime numerical
accuracy, NaN payloads, live rounding state or matherr/exception outcomes.
The two ordinary game callers establish no ownership by themselves.
The complete 80-byte defining constant section begins at `0x00661190`:
One, Bns, NegOne, NegZero and S occupy offsets 0/16/32/48/64. The actual Bns
reference is an interior anchor at +16, not the start of a single-value
comparison. All source definitions and every initialized byte are preserved.

Complete ceil and modf alternatives retain their whole 285-/328-byte source
carriers. Their wrappers have the same non-relocation shape, while their
whole carrier bodies differ at 30/224 non-field positions. The floor identity
therefore requires both the actual whole SSE operation and independently
accepted default owner. A shared wrapper shape or reviewed child alone
cannot substitute for the complete operation/source binding.

**Cold controls and acceptance.** `probes/VC7FloorMathLayout.cpp` uses actual
complete SDK exception/FP80 records and public math/classification/control
word/SSE declarations. The complete 84-byte layout and six natural controls
cover 180 bytes and six fields; all 77 included headers are pinned. Every
emitted code/data section is accounted for, without an orphan carrier.
Per-control VC7.1 build 3077 flags are reproducibility settings, not proof
of an executable-wide compiler profile. Thirty-one regression checks guard
whole extents/carriers/constants, actual masks/dispatch, signed fraction/zero,
NaN/error paths, independent retained owners and unknown runtime/private ABI.

The complete new and retained evidence cold-replay passed before canonical
write/read-back; exactly one row changed and all unrelated rows were checked
against HEAD. All 1,148 public checks, authored-extent verification,
target/project/query attestation, scanner/progress freshness, exact-input
preservation and whitespace checks pass locally. Totals are 3,444 resolved
(919 authored, 1,950 library, 575 compiler), 907 pending and 2,525 excluded.
The 60 source/mapped/exact functions / 9,883 bytes and every exact input
remain unchanged from R139 db26a05, preserving its 60/60 cold replay across
eleven objects; no affected exact unit needs another replay. Recorded
authored extents remain 872 / 1,952,956 bytes, with the provisional exact
coverage denominator 1,965,299. The public MCP waiver remains in force;
the existing no-auth route and private random path remain unchanged.
Private logs, generated objects and diagnostics remain untracked. The
complete-origin objective remains unfinished.

## R149 — Complete deque size families and shared receivers

R149 resolves six library origins / 102 bytes: `0x004094B0`, `0x00414430`,
`0x00414620`, `0x00414810`, `0x0041DD50` and `0x0045BF50`. Each complete
17-byte no-field body compares unmasked with all thirteen actual VC7 deque
size source alternatives. Replay
`scripts/repo-python scripts/verify-deque-size-context-origins.py` with
`config/deque-size-context-origin-evidence.json`. Original element types,
folding/aliasing, private declarations and complete game owner layouts remain
unknown. There is no source, mapping, private ABI or exact credit.

**Independent ownership context.** Identical getter bytes alone are
insufficient. Six complete independently authored parents / 5,610 bytes
retain their full extents, control flow and original ownership. Exact,
uninterrupted receiver-producing instruction sequences bind each candidate
to the same object as a separately complete, independently reviewed library
producer/consumer. Five contexts use their actual fixed global receivers;
the sixth proves equal owner/index/stride/field expressions through two
register variants. The observed twenty-byte container stride and +4 member
position do not establish a complete game class layout. Changing the owner,
index, field, direct destination or receiver-producing sequence invalidates
the proof. No origin follows from a game caller or reviewed child by itself.

The four complete push_back and two complete at anchors retain R072/R078
source and origin records. Their full cold verifiers replay serially, together
with the independent complete R110/R113 source-typed game/deque graphs.
No existing anchor is reclassified, renamed or assigned additional credit.
The target caller observations remain separate from the natural complete
SDK source controls and original-type inference.

**Compiler controls and acceptance.** `probes/VC7DequeSizeContexts.cpp` uses
thirteen real complete SDK deque specializations and natural const-receiver
size calls. All 26 emitted functions / 390 bytes cold-build with their own
complete AUX, source hashes and every typed field retained. The complete
32-byte readonly defining layout section establishes actual SDK container,
iterator and size-type records. Every emitted code/data carrier is accounted
for; all 27 actual included headers are pinned and checked against the cold
compiler include list. Per-probe VC7.1 build 3077 flags remain reproducibility
settings, not an executable-wide compiler inference. Fifteen regression
checks guard the full source family/layout, uninterrupted equal receivers,
independent anchors/cold proofs and pending nested origins.

Exactly six existing canonical rows changed after the complete new and
retained cold proof passed; write/read-back preserves every unrelated row
and all candidate extents. All 1,163 public checks, authored-extent verification,
target/project/query attestation, scanner/progress freshness, unchanged exact
inputs and whitespace checks pass locally. Totals are 3,450 resolved
(919 authored, 1,956 library, 575 compiler), 901 pending and 2,531 excluded.
The 60 source/mapped/exact functions / 9,883 bytes and all exact inputs remain
unchanged from R139 db26a05, preserving its 60/60 cold replay over eleven
objects; no affected exact unit needs replay. Recorded authored extents remain
872 / 1,952,956 bytes; the provisional coverage denominator is 1,965,299.
The public MCP waiver and existing private no-auth route remain unchanged.

**Retained nested uncertainty.** `0x00421550` and `0x0045DD50` remain pending.
A separate private natural nested-deque source control reproduces the entire
66-byte `0x0045DD00` parent and complete 45-byte `0x004215C0` back worker,
then follows a diagnostic graph of 43 complete bodies / 2,562 bytes / 103
fields and nine original external snapshots. This is source association,
not accepted independent provenance: nested/EH code/data bindings still
need complete reconciliation. The parent, back worker and other unknown
iterator controls receive no ownership credit. Their actual complete bodies,
original ledger extents, private declarations and prior owners are preserved.
The complete-origin objective remains unfinished.

## R150 — Complete nested deque code, data and EH provenance

R150 resolves the two complete 17-byte size candidates `0x00421550` and
`0x0045DD50` as library origins / 34 bytes. Replay
`scripts/repo-python scripts/verify-nested-deque-size-origins.py` with
`config/nested-deque-size-origin-evidence.json`. The actual nested SDK source
has a twenty-byte outer container holding complete twenty-byte inner SDK
containers. Original element definitions, folding, private declarations and
complete game owner layouts remain unknown. There is no source, mapping,
private ABI or exact credit; no auxiliary owner is reclassified in this batch.

**Independent actual receivers.** The entire independently authored
2,301-byte R070 parser preserves its observed owner +0x7D0 outer receiver for
back and size. Back-returned EAX is transferred directly into ECX for the
independently cold-replayed complete R072 byte push_back producer. The entire
66-byte count observation follows the signed-short index map, rejects a
negative mapped index, calls the actual outer at owner and transfers its
returned EAX into ECX for the inner size call. The natural source model uses
an observed 1000-short index map and real complete nested SDK containers;
it is a synthetic observation model, not a recovered complete game owner.
Actual uninterrupted receiver/returned-object instructions, full parent
bytes and complete control flow are checked. Identical getter bytes or a
reviewed library child alone establish neither origin.

**Whole independently linked provenance.** Fifty-three complete code owners /
2,980 bytes and all their typed fields are cold-linked through separately
complete source code/data definitions or explicit retained whole controls.
Every relocated byte is compared unmasked; target-derived field solving is
not used by the acceptance linker. Real own AUX extents are distinguished
from the few complete compiler-emitted code sections without AUX. The whole
string _Copy body and actual internal table/catch entries remain intact;
all original interior candidates and ledger extents are preserved.

Seventeen entire defining data sections / 524 bytes retain the complete
27-byte invalid-deque-subscript literal, out_of_range throw/catch information,
three complete type descriptors, two whole virtual tables, npos and all five
EH metadata owners. Five complete EH code carriers / 82 bytes preserve actual
cleanup/handler partitions and independent R020 frame records. FuncInfo is
an interior source anchor: the actual Xran owner is 36 bytes from 0x0066886C,
not a selected 28-byte header; the shared _Copy scope owner is the entire
132-byte section. Code/data callbacks bind actual complete owners, including
the independently emitted 23-byte SDK string destructor. Both actual weak
vector-deleting references retain their complete strong fallback records.
The whole type_info virtual table and runtime exception/frame-handler owners
retain the complete independent R119 source/data evidence; nine original
R113 external snapshots preserve their prior status, including the two
unresolved string throw workers. Live exception/cache outcomes remain unknown.

The existing R032 vector/length-error shape observation at 0x00421B70 is
preserved unchanged. It does not identify the actual operation: the new whole
literal and type/throw data bind out_of_range independently. The existing
library origin remains accepted, with the legacy name/source shape explicitly
separate from the stronger new operation evidence.

**Controls and acceptance.** `probes/VC7NestedDequeSizeContexts.cpp` cold-builds
all 82 ordinary emitted functions and eighteen entire emitted data sections,
including the complete 40-byte SDK/nested/iterator/observed-index-map layout.
All 27 actual included headers are pinned; every code/data carrier is covered.
The VC7.1 build 3077 flags are per-probe reproducibility settings. Full R149
and R119 cold evidence replay preserves prior deque/runtime/exception proofs.
Twenty regression checks guard complete extents/sections, actual nested and
returned-object typing, source/legacy separation and independently linked
unmasked fields, including PC-relative arithmetic, missing owners and overlap.
Pure receiver/producer read-back guards do not change the cold source,
headers, profile, fields or emitted data.

Exactly two existing canonical rows change after the complete cold evidence
passes; write/read-back checks every unrelated row against HEAD. All 1,183
public checks, authored-extent verification, target/project/query attestation,
scanner/progress freshness, exact-input preservation and whitespace checks
pass locally. Totals are 3,452 resolved (919 authored, 1,958 library,
575 compiler), 899 pending and 2,533 excluded. The 60 source/mapped/exact
functions / 9,883 bytes and every exact input remain unchanged from R139
db26a05, preserving its 60/60 cold replay across eleven objects; no affected
exact unit needs replay. Recorded authored extents remain 872 / 1,952,956
bytes; the provisional exact coverage denominator remains 1,965,299.
The public MCP waiver and private no-auth route remain unchanged. Private
logs, exploratory controls and objects remain untracked. The complete-origin
objective remains unfinished.

## R151 — Complete nested deque helper families

R151 resolves four existing library candidates: outer back `0x004215C0`
(45 bytes), mutable iterator dereference `0x00421FC0` (19), iterator
subtraction assignment `0x00422540` (27) and const iterator dereference
`0x00422560` (83). All 174 bytes retain their original complete extents.
Replay `scripts/repo-python scripts/verify-nested-deque-helper-origins.py`
with `config/nested-deque-helper-origin-evidence.json` and the natural SDK
controls in `probes/VC7NestedDequeHelpers.cpp`.

Thirteen real SDK element families preserve four complete positive graphs:
twenty-byte observation records and nested byte, word and pointer deques.
Each graph contains nine independently complete code owners / 368 bytes;
all four graphs / 36 source bodies / 1472 bytes compare unmasked after every
actual typed call is bound through its complete callee. Original element
types and folding remain unknown. Back reaches end, binary iterator minus
and mutable dereference; mutable dereference reaches the actual const owner.
The original five accepted dependency origins and all their extents remain
unchanged. Full R150 code/data/EH/receiver provenance cold-replays, including
the independently authored complete parser and its actual returned-inner
byte producer; a reviewed child alone does not establish a parent origin.

Nine rejected full type graphs retain actual differing const-dereference
owners. Byte/word/dword/pointer and eight-byte record owners have different
complete extents; sixteen-, twenty-four-, thirty-two- and sixty-four-byte
record owners retain the same 83-byte extent but differ in three, one, three
and three actual bytes respectively. Equal-shaped back/mutable/subtraction
operations alone do not identify a complete type family. No prefix or masked
comparison grants acceptance. Source `??Ziterator` is signed subtraction
assignment with a reference return, not iterator decrement; its actual NEG,
addition-assignment callee, stack cleanup and whole control flow are retained.

The pinned VC7.1 build 3077 cold-build covers all 169 ordinary emitted
functions / 5537 bytes, the entire 32-byte SDK layout section and 27 actual
included headers, with no orphan ordinary code/data carriers. Flags are
per-probe reproducibility settings. Eighteen regression checks guard complete
graphs/extents, independently typed callees, actual call sites, signed
overloads, rejected type differences and retained whole provenance.

Exactly four canonical rows change after complete cold acceptance; read-back
checks every unrelated row against R150 HEAD. All 1201 public checks,
authored-extent verification, attested target/project/queries, fresh scanner
and progress, exact-input preservation and whitespace checks pass locally.
Totals are 3456 resolved (919 authored, 1962 library, 575 compiler), 895
pending and 2537 excluded. The 60 source/mapped/exact functions / 9883 bytes
and all exact inputs remain unchanged from R139 db26a05; its 60/60 cold
replay across eleven objects remains applicable. No affected exact unit
needs replay. Authored extents remain 872 / 1952956 bytes and the provisional
exact denominator remains 1965299. No source, mapping, private ABI or exact
credit is added. The synthetic 66-byte count observation remains unknown;
neither its model nor these SDK helpers recover the complete game owner.
Public MCP acceptance remains waived; the private no-auth route is unchanged.
Private logs, generated output and objects remain untracked. The complete
origin objective remains unfinished.

## R152 — Complete script count map policy and independent game context

R152 resolves the complete 66-byte `0x0045DD00` as authored, provisionally
named `FighterScript::CountPatternEntries`. Replay
`scripts/repo-python scripts/verify-script-count-origins.py` with
`config/script-count-origin-evidence.json`. This supersedes the unknown
ownership recorded for the synthetic R150 count observation; that earlier
complete source control and its original metadata remain unchanged.

**Observed target policy.** The actual signed-short argument indexes the
owner's short map. A negative mapped value returns zero in AX. Otherwise
the mapped value is passed to the actual outer at owner +0x7D0; returned
EAX becomes ECX for the complete inner size owner. Both internal branches,
the final RET 4, the full 66-byte extent and fourteen following alignment
bytes are checked. This is a domain-specific missing-entry policy over the
script map, not origin inferred from a reviewed SDK child or matching wrapper
shape. The provisional role describes observed behavior, not an original name.

**Independent producers and consumers.** Six entire previously authored
owners / 5729 bytes preserve their own hashes, complete CFG, original roles,
origin evidence and guarded switch tables: script initializer `0x00420440`
(R076), byte/word accessors `0x00420530` / `0x00420570` (R076), full parser
`0x00420880` (R070), action processor `0x0045CE10` (R065) and pattern chooser
`0x0045D810` (R045). Initializer iteration writes -1 to 1000 actual short
entries. Parser decimal accumulation checks ASCII digits and multiplies the
short label by ten; after appending an outer entry it stores outer size minus
one in that label's map slot. The two complete game parents contain eleven
actual count calls, three and eight respectively. Uninterrupted instructions
preserve their short arguments, the actual fighter owner +0x714 receiver and
signed AX result used in loop/range comparisons. Neither an accepted game
caller alone nor the old natural model decides ownership: the combined
independent producer/domain/consumer policy supports authored classification.

**Compiler observations and unknowns.** Complete R150 cold source/code/data/EH
provenance replays, including its whole natural synthetic Count body and
independently linked actual SDK callees. No new source or compiler profile is
introduced. Ordinary special-member synthesis does not supply this label-map
and missing-entry/count policy. This is a semantic ownership inference from
actual independent game state, not proof of original source spelling. Original
types, folding, declarations and complete game layouts remain unknown. The
count body has no local index bounds guard; the parser's short accumulation
does not prove malformed-input or overflow safety. No complete game owner is
instantiated. The old R150 unknown context is retained as historical evidence,
without rewriting prior accepted sources or origins.

Exactly one existing canonical origin/function row changes, and one complete
authored body/CFG record is appended. Read-back guards preserve every unrelated
row against R151 HEAD and require the unique new authored extent record.
The additional pure registration guard leaves all cold source/profile/fields
unchanged. Twenty regression checks guard complete bodies, real signed ABI,
map sentinel/domain/decimal writes, independent parent ownership, actual
returned-inner receiver, all game uses and unique authored registration.
All 1221 public checks, target/project/query attestation, authored extents,
fresh scanner/progress, exact-input preservation and whitespace checks pass.
Totals are 3457 resolved (920 authored, 1962 library, 575 compiler), 894
pending and 2537 excluded. Recorded authored extents are 873 / 1953022 bytes;
the provisional exact denominator is 1965365 bytes. All 60 source/mapped/exact
functions / 9883 bytes and exact inputs remain unchanged from R139 db26a05,
preserving its 60/60 cold replay across eleven objects. No exact unit needs
replay; no source, mapping, private ABI or exact credit is added. Public MCP
acceptance remains waived and the private no-auth route is unchanged.
Private queries, logs and objects remain untracked. The complete-origin
objective remains unfinished.

## R153 — Complete script record buffer lifetime policy

R153 resolves two authored candidates: `0x00421200` / 24 bytes, provisionally
`FighterScript::InitializeRecordBuffer`, and `0x00421220` / 43 bytes,
provisionally `FighterScript::ReleaseRecordBuffer`. Original extents, all
returns/branches and following alignment remain intact. Replay
`scripts/repo-python scripts/verify-script-buffer-origins.py` with
`config/script-buffer-origin-evidence.json`. The natural source controls in
`probes/VC7ScriptBufferLifetimes.cpp` are complete synthetic observation
records, not recovered game declarations; no game source or exact unit is added.

**Independent game ownership context.** The entire independently authored
R070 parser / 2301 bytes preserves its original guarded switch, CFG and hash.
Eight actual local constructor/copy/release pairs retain the same local
receiver, actual R072 push_back producer and explicit cleanup. The full pointer
producer allocates the quoted text length plus one, stores returned storage
at record +4, reads that same pointer back, copies the substring and writes
the terminating byte. Complete R020 frame metadata and all eight eight-byte
record cleanup entries, plus the entire R037 44-byte scalar-deleting owner,
retain original evidence and extents. Those compiler contexts identify real
lifetime use; they alone do not identify a destructor's source ownership.

The accepted R072 producer is its complete 215-byte `DequeProbeRecord<8>`
control, an eight-byte byte-record model. Earlier "byte producer" wording
must not be taken as an original unsigned-char element declaration. The
actual game pointer/command observations and the synthetic nested R150 size
controls remain separate; those generic size bodies do not recover original
element types. All prior accepted source/control metadata and origins remain
unchanged. The actual buffer lifetime and parser protocol supply the additional
independent game policy evidence in this batch.

**Whole typed source controls.** Four guarded primitive-array constructor /
destructor families agree unmasked across all 67 bytes, totaling eight whole
source bodies / 268 bytes. Each destructor's actual field at +32 binds to
the independently complete five-byte archive array-delete owner at 0x0064169D
(delete2.obj, member 854462), then the unchanged complete accepted R142 scalar
delete owner at 0x00640F15 and R120 free owner / 113 bytes. Both five-byte
source owners compare unmasked through actual typed fields. Whole archive
members, source hashes, original accepted free boundary and every target byte
are read back; unchanged prior runtime inputs do not require another recursive
cold replay. The array-delete auxiliary retains its original unknown ledger
status and receives no new classification in R153.

The 43-byte guarded scalar-delete source has the same relocation-masked shape,
but differs in three actual relocation bytes after its independently typed
scalar-delete field is bound. It is rejected. A standalone 24-byte SDK auto_ptr
constructor differs in fourteen actual bytes; its complete destructor and
both implicit SDK/custom-owned record lifetimes have different extents.
The unguarded array destructor is a complete 34-byte owner, not a 43-byte
prefix match. Eight whole rejected controls preserve these genuine differences.
Raw implicit records emit no owning special-member policy. Under /Ob1 and
/Ob2, the complete emitted source inventories contain no own 24/43-byte
functions; inlined fragments cannot replace an entire target candidate.

The pinned build 3077 cold-builds all three explicit profiles: 90 ordinary
functions / 3897 bytes and all 107 entire ordinary code/data/EH sections /
4458 bytes, including seven complete EH code/data pairs and the full 40-byte
SDK/observation layout. All 24 actual included headers per profile are pinned.
Flags are per-probe reproducibility settings, not an executable-wide compiler
claim. Explicit null initialization and guarded array release, their independent
parser ownership policy and the differing bounded implicit/SDK alternatives
support authored inference. Original source spelling, names, types/folding,
complete game layouts and untested source alternatives remain unknown.

Exactly two existing canonical rows change and two complete authored body/CFG
records are appended; read-back preserves every unrelated row against R152
HEAD. Additional pure inventory/registration guards preserve all already cold
source/profile/field inputs. Twenty-three regression checks guard complete
extents/carriers/layouts, typed array/scalar separation, actual buffer writes,
paired lifetimes and independent original ownership/registration. All 1244
public checks, attested target/project/queries, authored extents, fresh scanner
and progress, exact-input preservation and whitespace checks pass. Totals are
3459 resolved (922 authored, 1962 library, 575 compiler), 892 pending and
2537 excluded. Recorded authored extents are 875 / 1953089 bytes; the exact
coverage denominator remains provisional at 1965432. All 60 source/mapped/exact
functions / 9883 bytes and exact inputs remain unchanged from R139 db26a05,
preserving its 60/60 cold replay across eleven objects. No exact unit needs
replay. No source, mapping, private ABI or exact credit is added. Public MCP
acceptance remains waived; the private no-auth route is unchanged. Private
queries, diagnostics and objects remain untracked. The origin objective remains
unfinished.

## R154 — Complete allocation API provenance

R154 resolves three library owners, preserving their complete original extents:
scalar new at `0x0064159D` / 14 bytes, array delete at `0x0064169D` / 5 bytes,
and array new at `0x006416A2` / 5 bytes. Replay
`scripts/repo-python scripts/verify-allocation-api-origins.py` with
`config/allocation-api-origin-evidence.json`. Complete own-AUX code from the
pinned libcmt.lib new.obj, delete2.obj and new2.obj members compares unmasked
across all 24 bytes, including every actual typed relocation and return/tail.
The matching five-byte shapes alone provide no ownership proof.

Scalar new pushes the observed new-handler flag 1 and original caller size,
calls the independently complete accepted R120 `__nh_malloc` / 44 bytes, then
balances its cdecl stack. Array new's actual source field routes to that full
scalar-new owner; array delete routes to the different independently complete
R142 scalar-delete owner, then the existing whole R120 free owner. All archive
members, full source/target hashes and actual fields are pinned. Original
accepted callee evidence, boundaries and classification remain unchanged.
The full R120 allocation/handler/data/API/EH provenance and its retained cold
source dependencies replay successfully, followed by the complete R153 buffer
lifetime source profiles and independent whole parser/cleanup contexts.

Natural controls in `probes/VC7AllocationCalls.cpp` cold-build eight complete
SDK allocation/release functions / 196 bytes. Three distinct primitive/complete
observation array types route through array operations; explicitly declared
scalar storage operations route through the different scalar owners. All nine
ordinary code/data sections / 212 bytes, their complete definitions and typed
fields, the entire 16-byte observation layout and eight actual included SDK
headers are read back. Build 3077 and explicit /Od /Ob0 flags are probe
reproducibility settings, not an executable-wide compiler claim. Synthetic
observation records do not recover or instantiate incomplete game owners.
Original linker inputs, original game element declarations, user-installed
handlers and live allocation outcomes remain unknown.

Exactly three existing unknown canonical rows become library/excluded;
every unrelated row and authored body record is unchanged against R153 HEAD.
Nineteen regression checks reject incomplete owners/carriers, wrong typed
array/scalar destinations, altered handler/input protocol, skipped independent
provenance and exact credit. All 1263 public workflow tests, local attested
queries, authored extents, fresh scanner/progress, exact-input preservation
and whitespace checks pass. Totals are 3462 resolved (922 authored, 1965
library, 575 compiler), 889 pending and 2540 excluded. Recorded authored
extents remain 875 / 1953089 bytes; provisional exact coverage remains
9883 / 1965432. The 60 source/mapped/exact functions / 9883 bytes, all exact
inputs and R139 db26a05's 60/60 cold replay across eleven objects remain
preserved; no changed exact unit requires replay. No game source, mapping,
private ABI or exact credit is added. Public MCP acceptance remains waived,
and the private no-auth route is unchanged. Private queries, surveys and
objects remain untracked. The complete-origin objective remains unfinished.

A fresh private whole-own-AUX CRT survey identifies full diagnostic controls
for ui64toa / 27 bytes, SEH longjmp unwind / 27, FillZeroMan / 12 and finite /
21. A separate complete atox.obj check identifies the five-byte atoi owner
and its actual typed tail to accepted whole atol / 136 bytes. These five
candidates form the bounded R155 cohort; these diagnostics grant no origin.
Both 11-byte abs-shaped candidates have complete abs/labs source alternatives.
R129 already proves ordinary expression controls can also reproduce the
entire shape; preserve that ownership ambiguity instead of repeating an
acceptance from the new survey.

## R155 — Short CRT provenance and unsupported leaf ownership

R155 reviews five complete candidates / 92 bytes. Three gain library origin:
`0x006426A1` / 5 bytes (`_atoi` source association), `0x0064554E` / 27 bytes
(`__seh_longjmp_unwind@4`), and `0x00651D44` / 27 bytes (`__ui64toa`).
The entire 21-byte `0x00643FC6` finite association and 12-byte `0x0064F513`
FillZeroMan association remain unknown/pending. Replay
`scripts/repo-python scripts/verify-short-crt-origins.py` with
`config/short-crt-origin-evidence.json`. No original executable symbol or
private game declaration is established by these provisional archive names.

Every candidate's complete positive COFF AUX extent is extracted without a
size override. All target bytes agree unmasked with the pinned whole archive
source, including actual typed fields and final return/tail instructions.
The accepted atoi tail routes to independently complete R123 atol / 136 bytes;
the saved-context helper routes to unchanged R025 local unwind / 104 bytes;
the unsigned-wide formatter routes to unchanged R007 x64toa / 109 bytes and
its original typed unsigned division dependency. Whole original runtime
metadata and canonical evidence remain unchanged. Complete codepage/NLS,
jump/unwind, security/EH and runtime verifiers replay successfully, including
retained cold source/layout/data/API/EH dependencies and all 57 original whole
runtime bodies / 5641 bytes with 28 actual bindings.

**Complete SEH source carrier.** The saved-context helper is a positive
27-byte own AUX inside exsup3's larger source section. Its entire 265-byte
carrier compares unmasked: the eight-byte `VC20XC00` source marker, complete
230-byte original handler, full helper at offset 238 and all six actual typed
fields are retained. It reads actual SDK saved Ebp, Registration and TryLevel,
calls full local unwind with the real registration/try-level pair and restores
the frame with four-byte argument cleanup. The SDK saved-context declaration
and the whole source carrier independently corroborate this operation;
a library child or absent direct callers alone supplies no origin proof.

**Bounded pending controls.** The entire twelve-byte FillZeroMan source also
matches an ordinary natural source control clearing a complete three-word
observation with memset. The cold compiler emits all twelve identical bytes,
without any relocation masking. No actual direct caller or independent owning
context distinguishes the two sources, so library origin is withheld. Finite
has a complete 21-byte vendor/SDK association, while the ordinary exponent
expression emits a complete different 20-byte function. Its failed control
must not be compared against a twenty-byte target prefix, and it does not
exclude other original compiler/source variants or prove ownership. It also
has no observed direct caller or independent owning context and remains
pending. Both rows retain their original unknown origin records, empty owner
and proposed-name fields, and full extents; only durable evidence/notes change.

`probes/VC7ShortCrtCalls.cpp` cold-builds all eight complete SDK/source controls /
109 bytes and every one of nine entire ordinary code/data sections / 153 bytes.
The complete 44-byte layout freezes real 64-byte jump buffers, saved-field
offsets, actual primitive/observation sizes, JBLEN and floating exponent range;
all five actual SDK headers are pinned. The synthetic three-word observation
is not an original floating/game structure. Build 3077 and /O1 /Oi /Ob0 are
per-probe reproducibility settings; original flags/linker inputs, source
spelling/types and live decimal/radix/floating/jump outcomes remain unknown.

Exactly three canonical origins and five bounded function evidence rows
change against R154 HEAD; both pending origins, every unrelated row and all
authored records remain unchanged. Additional pure source/carrier registration
guards preserve all already cold inputs. Twenty-two regression checks reject
partial extents/carriers/layouts, wrong fields/SDK operations, altered saved
context and false pending/exact/ABI credit. All 1285 public workflow tests,
local target/project/query attestation, authored extents, fresh scanner/progress,
exact-input preservation and whitespace checks pass. Totals are 3465 resolved
(922 authored, 1968 library, 575 compiler), 886 pending and 2543 excluded.
Authored records remain 875 / 1953089 bytes; exact coverage remains provisionally
9883 / 1965432. All 60 source/mapped/exact functions / 9883 bytes and exact
inputs remain unchanged from R139 db26a05, preserving its 60/60 cold replay
across eleven objects. No affected exact unit needs replay. No source, mapping,
private ABI or exact credit is added. Public MCP acceptance remains waived;
the private no-auth route is unchanged. Private queries, diagnostics and objects
remain untracked. The complete-origin objective remains unfinished.

The next bounded R156 cohort is two previously unreviewed complete 211-byte
deque-like producers and their four 27-/29-byte allocation/construction
callees. Independent full R070 parser and R040 replay-file scanning parents,
plus unchanged full R071 grow-map owners, provide investigation context.
Diagnostic target observations show distinct 20-/60-byte element scales;
these sizes do not recover original element declarations. No next-cohort
classification follows from scanner rank or these source-shape observations.

## R156 — Complete paired deque producers and typed allocation/construction

R156 accepts six library owners / 534 bytes: the complete 211-byte producers
`0x004215F0` and `0x0042DBE0`, their 27-byte element-allocator wrappers
`0x00421EE0` and `0x0042E000`, and their 29-byte construction wrappers
`0x00421F00` and `0x0042E020`. Replay
`scripts/repo-python scripts/verify-paired-deque-producer-origins.py` with
`config/paired-deque-producer-origin-evidence.json`. The provisional names
describe verified SDK source associations, not original executable symbols.
Every accepted owner has its entire positive own COFF AUX extent; the full
branch/return and actual relocation inventory compares without masking.

**Independent original contexts.** The full unchanged R070 parser / 2301 bytes
calls the first producer at `0x00420CE4`, and the full R040 replay-file scan /
613 bytes calls the second at `0x0042D684`. Actual receiver/value instruction
windows and both parents' complete authored CFG/switch evidence are retained.
Both unchanged R071 growth owners / 511 bytes also compare completely. Source
typing distinguishes the element allocator from the separate pointer-map
allocator; calls continue through actual scalar-new and placement-new owners.
R154 allocation and R142 standard-exception verifiers cold-replay their
independently complete source/data/SDK/runtime dependencies. The retained
R150 nested-deque verifier also completes a fresh cold replay in this batch.
A game caller or an accepted library child alone does not establish ownership.

**Entire source and state.** `probes/VC7PairedDequeProducers.cpp` cold-builds
all 187 ordinary emission sections / 11917 bytes. The linked closure contains
162 entire code/EH sections / 11016 bytes and 22 complete data sections /
835 bytes. All 436 genuine typed fields resolve through complete independent
source definitions, source weak fallback metadata, original data owners or
retained external operations; all linked target bytes agree unmasked.
Where implicit SDK constructors or EH carriers have no positive own function
AUX, the entire defining code section is compared instead. Two genuine weak
references retain their complete strong fallback definitions and actual COFF
AUX metadata. RTTI/vtables, strings, exception state and the absolute FS
exception-list offset are kept distinct from ordinary executable functions.
Ten full original R020 registered frames retain unwind/try/catch/parent evidence,
including FuncInfo records inside larger complete data carriers.

The complete 32-byte layout records `[8,20,60,20,20,4,8,8]`; all 27 actual SDK
headers are pinned. The 20-byte observation contains a real SDK deque and the
60-byte observation is a complete synthetic file record. Their declarations
are source controls, not recovered game record types. The eight-byte inner
observation declares destruction through truthful C++ ABI and binds the
independently complete 43-byte authored R153 lifetime policy. Its authored
ownership remains separate from the SDK operations that invoke it. Original
element fields/declarations, spelling, linker inputs and live runtime outcomes
remain unknown. Build 3077 and /Od /Ob0 /Gy /GR- /GX /Zi /GS are explicit
per-probe reproducibility settings, not an executable-wide compiler claim.

**Shared tails and unchanged ledgers.** The SDK copy control at `0x00422A50`
compares its whole 241 bytes, and insertion at `0x00422D70` compares all 1545
bytes, including shared tails. Their historical provisional canonical extents
remain 195 and 1483 bytes, respectively, and both origins remain unknown.
Whole EH carriers likewise include their cleanup/dispatch tails without
altering historical compiler entry extents. These complete auxiliary source
associations grant no new boundary, authored/library/compiler classification,
source, private ABI, mapping or exact credit. Original opaque string-throw
workers and all other auxiliary canonical snapshots remain unchanged.

Exactly six origin rows and their six function evidence rows change against
R155 HEAD 9734107. All unrelated canonical rows and every authored record are
preserved. Twenty-seven regression checks protect entire AUX/code/data/layout
extents, actual typed operations, original parent and policy evidence, weak
fallbacks, whole shared tails and false ABI/exact credit. All 1312 public tests,
local target/project/query attestation, authored extents, fresh scanner/progress,
exact-input preservation and whitespace checks pass. Totals are 3471 resolved
(922 authored, 1974 library, 575 compiler), 880 pending and 2549 excluded.
Authored evidence remains 875 records / 1953089 bytes; provisional exact
coverage remains 9883 / 1965432. All 60 source/mapped/exact functions / 9883
bytes and all exact inputs remain unchanged from R139 db26a05, preserving its
60/60 cold replay across eleven objects. No affected exact unit needs replay.
Public MCP acceptance remains waived and the private no-auth route is unchanged.
Private queries, logs and objects remain untracked. The complete-origin
objective remains unfinished.

The next bounded R157 cohort is four still-unknown lower-level helpers /
213 bytes: `0x004228A0` / 20, `0x004228C0` / 108, `0x0042E4D0` / 20 and
`0x0042E4F0` / 65. R156 already retains their complete source controls, actual
calls and state, but gives them no classification. Use the accepted typed
allocator/construction parents as independent context and explicitly retain
ordinary authored allocation/placement/copy alternatives. Preserve the unknown
record-copy wrapper and full-copy/insertion parents; do not infer their origin
from these operations or treat the observations as recovered element types.

## R157 — Element operations with byte-equal ordinary source alternatives

R157 accepts four complete library owners / 213 bytes: SDK `_Allocate`
associations `0x004228A0` and `0x0042E4D0` / 20 bytes each, plus `_Construct`
associations `0x004228C0` / 108 and `0x0042E4F0` / 65. Replay
`scripts/repo-python scripts/verify-deque-element-origins.py` with
`config/deque-element-origin-evidence.json`. Every SDK owner and ordinary
control has its full positive own COFF AUX extent, without a size override.
All original extents, source/ABI fields and exact percentages remain unchanged.

**Positive provenance and explicit ambiguity.** Each actual original helper
has one observed caller: respectively the complete R156 element allocator
`0x00421EE0`, construction wrapper `0x00421F00`, element allocator
`0x0042E000` and construction wrapper `0x0042E020`. Independent full parent
source fields name the actual SDK element operation, distinguishing it from
the pointer-map allocator. The scalar operations call the unchanged whole
R154 scalar-new owner; construction routes through actual placement-new,
the full original queue-copy dependency and registered exception state, or
the complete fifteen-word file-record copy. Full R156 parent/source/code/data/
EH/runtime evidence cold-replays, including R154/R142 dependencies, unchanged
game/growth context and independently authored R153 inner destruction.

Four ordinary natural allocation and placement-copy controls in
`probes/VC7DequeElementAlternatives.cpp` cold-emit all 213 identical bytes.
Every real field is linked and compared unmasked. Body equality alone thus
cannot determine ownership. Library classification is an inference from
the independently complete accepted SDK parents, their real source-typed
calls and the unchanged full SDK source family, rather than from a short
body, adjacency or a library child alone. No original symbol, spelling or
record declaration is recovered, and untested original source/compiler
alternatives are not excluded. This evidence is stronger than the unrelated
R129/R155 leaf ambiguities that lack independent owning context; those prior
pending rows remain untouched.

**Whole ordinary EH and source.** The ordinary queue construction also
retains its full 27-byte cleanup/dispatch carrier and whole 36-byte exception
data, including unwind storage before its embedded 28-byte FuncInfo.
Together the six complete code/data controls cover 276 bytes and fourteen
genuine typed fields. The entire defining EH carrier is used where an
individual positive own function AUX is unavailable. Source definitions,
local-label offsets, field roles and destinations follow independently whole
retained owners; compiler-local labels belong to their own COFF object and
their generated numbers are not treated as cross-object global identities.
The new cold source freezes all 193 ordinary emission sections / 12193 bytes,
all 27 actual SDK headers and its actual included R156 observation source.
The original full 32-byte layout, 162 whole linked code/EH owners / 11016
bytes, 22 data owners / 835 bytes, 436 actual fields and ten full registered
frames remain protected by the retained cold verifier. These are origin
controls, not new exact units or reconstructed game owner layouts.

**Bounded canonical follow-up.** R156 retains its original immutable manifest.
Its snapshot verifier now permits only these four exact R157 transitions,
requiring the hash-pinned follow-up manifest, exact original snapshots and
exact new function/origin records. It does not skip arbitrary auxiliary
metadata or permit other new classifications. The transition guards and all
auxiliary snapshots are read back after acceptance. Only the final summary
wording changes after the unchanged cold proof; no source/profile/header/
relocation input or comparison behavior changes. Whole shared-tail copy/
insertion controls, record-copy ownership, interior catch rows, opaque throw
workers and authored lifetime policy keep their original classifications and
canonical extents. Ordinary source controls do not classify those owners.

Exactly four origin rows and their four function rows change against R156
HEAD 4608784; all unrelated rows and every authored record remain unchanged.
Twenty-eight regression checks protect full AUX/code/data/emission/header/
layout extents, real parent/operation roles, byte-equal alternatives, exact
bounded follow-up transitions and false source/private ABI/exact credit.
All 1340 public tests, local target/project/query attestation, authored extents,
fresh scanner/progress, exact-input preservation and whitespace checks pass.
Totals are 3475 resolved (922 authored, 1978 library, 575 compiler), 876 pending
and 2553 excluded. Authored evidence remains 875 records / 1953089 bytes;
provisional exact coverage remains 9883 / 1965432. All 60 source/mapped/exact
functions / 9883 bytes and exact inputs are unchanged from R139 db26a05,
preserving its 60/60 cold replay across eleven objects. No affected exact
unit needs replay. Public MCP acceptance remains waived and the private
no-auth route is unchanged. Private logs, queries and objects stay untracked.
The complete-origin objective remains unfinished.

The next bounded R158 cohort is the complete queue copy/insertion source
family and its interior catch/shared-return candidates, plus the unresolved
record-copy wrapper. The original 195-/1483-byte parent candidates must be
reconciled against their whole 241-/1545-byte source owners before acceptance;
the 46-/48-/62-byte catch entries are interior source spans, not independent
whole functions. The 28-byte record-copy wrapper requires genuine implicit
versus ordinary explicit source controls. No classification follows merely
from these existing full source associations or the SDK children.

## R158 — Whole deque copy/insertion, interior catch policy and copy ambiguity

R158 reviews all six handoff candidates. Five gain library origin: the complete
SDK copy owner `0x00422A50` / 241 bytes, insertion owner `0x00422D70` / 1545
bytes, and three interior catch/source-policy candidates `0x00422B13` / 46,
`0x0042308D` / 48 and `0x0042333B` / 62. The complete 28-byte record-copy
wrapper `0x004229D0` remains unknown/pending. Replay
`scripts/repo-python scripts/verify-deque-copy-insert-origins.py` with
`config/deque-copy-insert-origin-evidence.json`. The two whole SDK owners
cover 1786 distinct bytes; the catch spans overlap them and are neither three
new whole functions nor additional source byte credit. Candidate counts and
complete function counts remain distinct.

**Required extent reconciliation.** The copy row's original 195-byte boundary
ended after the normal branch at `0x00422B11`, omitting its return through
`0x00422B24`. The full positive own COFF AUX and defining section cover all
241 bytes through `0x00422B40`. Insertion's old 1483-byte boundary similarly
omitted the final shared normal epilogue at `0x0042335F`; the complete positive
own AUX covers all 1545 bytes through `0x00423378`. The first insertion catch
also branches from `0x004230B8` to that same return. Both full owners decode
completely, end in their real RET and retain every internal branch target.
Canonical size/span_end change only for these two original parent rows.
Observed fifteen-/seven-byte CC alignment after the owners and the following
original candidates remain outside the accepted extents and unchanged.
The private Ghidra project is queried read-only and retains its original
split inventory; accepted canonical extents come from complete target CFG,
source AUX, actual state and byte comparison, not the initial Ghidra boundary.

**Interior library policy and compiler mechanics.** Original full R020 frames
`0x006556B0` / FuncInfo `0x00668930` and `0x006556C0` / `0x006689B4`
retain complete unwind, try, catch and parent registration evidence. Whole
80-/132-byte source data carriers include all state and handler tables.
Their three actual catch-all records name exactly the interior candidates,
with ranges 0/0/1, 0/0/1 and 2/2/3. Each candidate's entire observed span is
verified inside its whole compared parent; the 48-byte insertion span reaches
a shared epilogue beyond its own provisional span, which remains part of the
full 1545-byte owner. No individual full-function AUX is fabricated for a
catch label and no isolated prefix is accepted as a standalone function.

The SDK copy constructor explicitly calls `_Tidy` and rethrows on failure;
the bidirectional insertion source explicitly restores the old size by
`pop_front` or `pop_back` and rethrows. Whole source/body and all typed fields
establish that these are library source policies. Ghidra Catch names, absence
of direct callers and registration alone establish no origin. The compiler
frame/dispatch mechanics retain their independently reviewed compiler evidence;
the source rollback policy is not relabeled compiler-owned merely because
the compiler creates a local catch entry. Original game element destruction
retains its independent authored R153 provenance, with no inferred copy policy
or original record layout. Live success/failure and unwind outcomes remain
unknown.

**Complete implicit/explicit ambiguity.** The entire implicit record-copy
defining code section / 28 bytes agrees unmasked with the target. An ordinary
explicit copy constructor of a complete observation record emits all 28
identical bytes and the same real SDK deque-copy call. The latter has a full
positive own AUX; the implicit source control is compared as its entire
defining section where a complete positive function AUX is unavailable.
Full R157 construction and the whole SDK copy dependency establish operation,
not implicit-versus-authored ownership. The original record declaration and
source ownership therefore remain unknown. Only durable function evidence/
notes change; its origin row, empty name/owner/source/ABI fields and full
extent remain unchanged. Do not revisit it from a library child, scanner rank
or another same-shaped control without new independent ownership evidence.

`probes/VC7DequeCopyAlternatives.cpp` cold-builds all 194 ordinary sections /
12303 bytes and the whole 48-byte SDK/observation layout
`[8,20,60,20,20,4,8,8,20,20,20,8]`. Fourteen complete code/data/EH controls /
2416 bytes and all 104 genuine typed fields compare unmasked. This includes
the two whole SDK owners, full state/dispatch carriers, implicit/explicit
record constructors and complete ordinary placement-copy controls with their
entire exception carriers. All 27 SDK headers and the actual included R156
observation source are pinned. Complete R157/R156 source/code/data/EH/runtime
evidence cold-replays, including independent R154/R142 dependencies. Original
source spelling/compiler/linker choices and game types remain unknown;
build 3077 and the explicit flags are per-probe reproducibility settings.

R156/R157 manifests remain immutable. The R156 snapshot guard now permits
only the existing four exact R157 transitions and six exact hash-pinned R158
transitions, including the pending row's evidence-only update. It requires
exact original snapshots and exact accepted function/origin records; all
other canonical snapshots remain unchanged. These guards read back after
acceptance. A subsequent pure catch-all guard strengthens the already checked
actual handler schema; summary wording changes without altering any source,
profile/header/relocation input or cold comparison. Exactly five origin rows,
six function evidence rows and two parent extents change against R157 HEAD
42e9466. Every unrelated row, authored record, opaque boundary and exact input
remains preserved.

Thirty-four regression checks protect whole parents, actual registered catches,
source policy versus compiler mechanics, shared returns, alignment, entire
state/emission/layout/header evidence, pending ambiguity and exact bounded
follow-up transitions. All 1374 public tests, local target/project/query
attestation, authored extents, fresh scanner/progress, exact-input preservation
and whitespace checks pass. Totals are 3480 resolved (922 authored, 1983
library, 575 compiler), 871 pending and 2558 excluded. Authored evidence remains
875 records / 1953089 bytes; provisional exact coverage stays 9883 / 1965432.
All 60 source/mapped/exact functions / 9883 bytes and exact inputs are unchanged
from R139 db26a05, preserving its 60/60 cold replay across eleven objects.
No affected exact unit needs replay. Public MCP acceptance remains waived;
the private no-auth route is unchanged. Private queries, logs and objects
remain untracked. The complete-origin objective remains unfinished.

The next bounded R159 cohort is eight still-unknown SDK endpoint/dispatch
dependencies / 296 bytes exposed by the complete copy/insertion parents:
const begin/end, insert dispatch, distance/advance wrappers and their actual
category/distance/advance callees. Retain the existing R085 copy/copy-backward
owners unchanged. The eleven-byte category body's shape alone cannot identify
an original tag declaration; use independently whole real overload dispatch
and retain original type/name uncertainty. No next-cohort classification
follows from these already retained source controls or reviewed children.

## R159 — Complete deque endpoints and actual category/operation dispatch

R159 accepts eight library owners / 296 bytes: const begin `0x00422B50` / 35,
const end `0x00422B80` / 41, insert dispatcher `0x00422CB0` / 67, distance
dispatcher `0x00423680` / 55, advance dispatcher `0x004236C0` / 43, category
helper `0x00422D60` / 11, distance operation `0x004237E0` / 27 and advance
operation `0x00423800` / 17. Replay
`scripts/repo-python scripts/verify-deque-endpoint-dispatch-origins.py` with
`config/deque-endpoint-dispatch-origin-evidence.json`. All eight retain their
full positive own COFF AUX extents and canonical size/span_end; all bytes
and genuine typed fields compare without masking. Names remain provisional
SDK source associations, with no recovered original function/type declaration.

The entire R158 copy / 241 bytes actually calls both const endpoints and
insert dispatch; the full R158 insertion / 1545 bytes actually calls distance
and advance dispatch. Those three dispatchers call the actual category helper.
The selected distance/advance operations bind original whole const-iterator
difference `0x004235F0` / 66 (R084) and addition-assignment `0x004239A0` / 31
(R106). Both endpoints bind the unchanged complete R081 const-iterator
constructor `0x00422660` / 33. Independent original source/field/owner records
remain preserved, including R085 copy/copy-backward algorithms. Complete
R158/R157/R156 source/code/data/EH/runtime evidence cold-replays, preserving
original shared tails/interior source policies, opaque boundaries and the
independently authored R153 destruction policy. A library child alone does
not establish any new parent's ownership.

**Category ambiguity and real operations.** Actual SDK category instantiations
for complete forward and bidirectional traits observations emit the same
entire eleven bytes as the target. Input-category source emits a different
complete eleven-byte body, including different return transport in this
compiler's source ABI. No ledger ABI or original tag declaration follows.
The shape of an eleven-byte helper cannot uniquely identify category/type
or ownership; library origin is inferred from the independently complete
accepted SDK parents and their real overload/source relationship. Real SDK
random-access tag inheritance permits the selected bidirectional insertion,
while its distance/advance operations use difference and addition-assignment.
The original category and element declarations remain unknown.

Natural SDK input-distance / 49 bytes and bidirectional-advance / 59 bytes
are full different operation controls, compared as complete source extents,
never against truncated 27-/17-byte target prefixes. Their whole definitions
and actual source fields remain in cold emission evidence. The input-category
control is compared at its complete equal length and fails whole byte equality;
it is not a masked or partial target association. These bounded alternatives
do not exclude every possible original source/compiler variant.

`probes/VC7DequeEndpointDispatch.cpp` cold-builds all 197 ordinary emission
sections / 12245 bytes, twelve complete linked code controls / 2104 bytes and
all 76 actual fields. Every linked owner has full positive own AUX. The entire
72-byte SDK/traits layout is `[8,20,60,20,20,4,8,8,20,8,4,1,1,1,1,1,1,1]`;
all 27 SDK headers and the actual included unchanged R156 observation source
are pinned. Complete observations are source controls, not reconstructed
game records/iterators. Build 3077 and explicit flags are reproducibility
settings per probe; original flags/spelling/linker inputs, live range/offset
values, allocation/lifetime and iterator outcomes remain unknown.

Exactly eight origin rows and eight function evidence rows change against
R158 HEAD c9fe356. All unrelated rows, every authored record, prior R085
algorithm and original extents remain unchanged. R156/R157/R158 manifests
stay immutable. The R156 snapshot guard permits only eight additional exact
hash-pinned R159 transitions. R158's original insert-parent and adjacent
const-begin snapshot checks use that same exact guard, rather than skipping
classification/name/extent metadata; both read back after acceptance. The
final summary wording changes after the unchanged cold proof, without source,
profile/header/relocation or comparison changes. Thirty regression checks
protect whole ownership/dispatch, actual field routes, full differing and
byte-equal controls, layout/header/emission coverage, original algorithms,
bounded parent/alignment follow-ups and false source/private ABI/exact credit.

All 1404 public tests, local target/project/query attestation, authored extents,
fresh scanner/progress, exact-input preservation and whitespace checks pass.
Totals are 3488 resolved (922 authored, 1991 library, 575 compiler), 863 pending
and 2566 excluded. Authored evidence remains 875 records / 1953089 bytes;
provisional exact coverage stays 9883 / 1965432. All 60 source/mapped/exact
functions / 9883 bytes and exact inputs remain unchanged from R139 db26a05,
preserving its 60/60 cold replay across eleven objects. No affected exact
unit needs replay. Public MCP acceptance remains waived; the private no-auth
route is unchanged. Private queries, diagnostics and objects stay untracked.
The complete-origin objective remains unfinished.

The next bounded R160 cohort is five remaining full source-associated unknowns:
file allocator max_size / 44, iterator indexing / 38, iterator subtraction-
assignment / 27, inner element destruction / 15 and placement delete / 5.
Keep the R158 28-byte record-copy ambiguity protected. Source controls and
reviewed children alone grant none of these remaining owners origin credit.
In particular, `_Destroy` calls the complete unchanged R037 generated scalar
deleting wrapper / 44 bytes, which then calls authored R153 destruction;
do not bind its field directly to the authored destructor or conflate origins.
The five-byte placement-delete body needs ordinary no-op alternatives plus
its independent complete SDK placement/construction and EH cleanup protocol.

## R160 — Remaining deque leaves and byte-equal ordinary alternatives

R160 accepts five library owners / 129 bytes: file allocator max_size
`0x0042E3B0` / 44, iterator indexing `0x00423550` / 38, subtraction-assignment
`0x00422480` / 27, element destruction `0x004229B0` / 15 and two-argument
placement delete `0x00412300` / 5. Replay
`scripts/repo-python scripts/verify-deque-leaf-origins.py` with
`config/deque-leaf-origin-evidence.json`. All five have complete positive own
COFF AUX extents and unchanged canonical size/span_end. Every actual field
compares unmasked; no source/private ABI/mapping/exact credit follows. Names
are provisional SDK associations, not recovered original declarations.

**Byte-equal alternatives.** A complete ordinary capacity observation emits
all 44 target bytes, an ordinary explicit destructor call emits all 15 bytes
and a natural two-argument empty function emits all five placement-delete
bytes. None of these leaf shapes proves library ownership or uniquely identifies
original source. The source-level library inference uses the independently
accepted entire typed SDK parent/source relationships and actual protocol:
R074 deque max_size / 22 in complete R071 file growth / 511; entire R158
insertion / 1545 calling indexing; whole R078 iterator subtraction / 57
calling subtraction-assignment; and whole R074 allocator destruction / 25.
Indexing really calls addition `0x00421F40` and dereference `0x00421F20`;
subtraction-assignment negates the supplied offset before actual addition-
assignment `0x00422460`. Every reviewed callee remains independently classified.

Destruction passes zero flags to the unchanged complete R037 generated scalar
deleting wrapper `0x004229F0` / 44. That wrapper calls independently authored
R153 destructor `0x00421220` / 43 and gates R142 scalar delete `0x00640F15`
/ 5 on flag bit one. Its origin is compiler, the actual destruction policy is
authored, and the SDK leaf is library; no call bypasses the intervening wrapper.
No new compiler or authored credit is awarded.

Placement delete follows the independently whole R157 SDK `_Construct`
`0x004228C0` / 108, with actual R005 placement new `0x004063D0` / 8 and
its original complete 27-byte cleanup/frame carrier `0x00655690` and entire
36-byte state-data section `0x006688D8`. Actual cleanup loads the placement
address from `[ebp+8]` and the placement-new result from `[ebp-0x14]`, pushes
both, calls `0x00412300` and removes eight stack bytes. The separate registered
frame entry remains at carrier offset 17. No live constructor failure or
exception outcome is observed. The whole R158 28-byte implicit/ordinary copy
ambiguity remains unknown and unchanged; constructing its record does not
establish the original constructor declaration.

`probes/VC7DequeLeafAlternatives.cpp` cold-builds all 191 ordinary sections
/ 12034 bytes. Seventeen full linked controls contain sixteen code carriers
/ 2532 bytes, entire construction EH data / 36 bytes and 88 actual fields.
All accepted leaves, ordinary alternatives and applicable SDK parents retain
positive own AUX; compiler/EH/data carriers retain their independently whole
defining sections. The full 72-byte observation layout is
`[8,20,60,20,20,4,8,8,8,20,60,20,20,4,8,8,1,1]`.
All 27 SDK headers and the actual unchanged included R156 observation source
are pinned. Complete synthetic observations do not recover game records.
Generated local `$` labels are resolved from this object's actual sections,
including the cleanup's actual state-data field; equal names in a prior object
cannot establish local ownership. Build 3077 and explicit flags are per-probe
reproducibility settings. Original source/type/compiler/linker inputs and live
capacity/index/offset/construction/lifetime outcomes remain unknown.

Exactly five function evidence rows and five origin rows change against
R159 HEAD e8f059e. All unrelated rows, every authored record and protected
copy ambiguity remain unchanged. R156/R157/R158/R159 manifests stay immutable.
The R156 snapshot guard permits only the exact five hash-pinned R160 follow-up
transitions and reads every full original snapshot back after acceptance.
Twenty-five regression checks protect full source/protocol extents, actual
fields/local offsets, ordinary alternatives, distinct compiler/authored roles,
protected copy uncertainty, layout/header/emission coverage and false credit.
The unchanged complete R159/R158/R157/R156/runtime source chain cold-replays
before canonical acceptance; only its final follow-up summary wording changes
after that proof. All 1429 public tests, local target/project/query attestation,
fresh scanner/progress, authored extents, exact-input preservation and whitespace
checks pass. Public MCP acceptance remains waived; no-auth/private route and
untracked private diagnostics remain unchanged.

Totals are 3493 resolved (922 authored, 1996 library, 575 compiler), 858 pending
and 2571 excluded. Authored evidence remains 875 bodies / 1953089 bytes;
provisional exact coverage stays 9883 / 1965432. All 60 source/mapped/exact
functions / 9883 bytes and exact inputs remain unchanged from R139 db26a05,
preserving its 60/60 cold replay across eleven objects. No affected exact unit
needs replay. The complete-origin objective remains unfinished. The closed
R156 primary source graph now has only its protected R158 record-copy owner
remaining unknown; this does not exhaust the wider 858-function backlog.

The next bounded R161 cohort is nine unknown STL source-context candidates / 237 bytes:

| Candidate | Full provisional extent | Actual investigation context |
| --- | ---: | --- |
| `0x00409760`, `0x00409E60` | 31 each | first vector begin/end pair in the unchanged whole R034 assign / 96 and R095 assign-wrapper source family; actual iterator construction `0x0040A120` |
| `0x0040E1F0`, `0x0040E680` | 31 each | second vector begin/end pair in the unchanged whole R034 assign / 96 and R095 wrapper family; actual iterator construction `0x0040E9E0` |
| `0x0040A120`, `0x0040E9E0` | 28 each | corresponding still-unknown iterator constructors; reconcile complete source/extent/type and ordinary constructor alternatives, not a reviewed-child inference |
| `0x0040A190` | 27 | iterator subtraction-assignment in the accepted whole iterator-subtraction parent `0x00409DF0`; actual independently accepted R106 addition-assignment `0x0040A5E0` / 31 |
| `0x0040A830`, `0x0040F9F0` | 15 each | actual SDK destruction in unchanged allocator parents R074 `0x00409D60` / 25 and R033 `0x0040F860` / 25; respective unchanged R037 generated deleting wrappers `0x0040A9F0`, `0x0040FA00` / 44 |

This cohort is a diagnostic investigation scope, not nine promised acceptances.
Build complete natural SDK observation families, retain each entire accepted
parent and every genuine field/source operation, and establish independent
compiler/authored destructor policy before any library decision. Constructor
or destructor shapes and accepted children alone do not identify ownership,
original element kinds/declarations or source. Ordinary byte-equal alternatives
must remain explicit. Keep the R158 record-copy ambiguity and all other protected
lifetime/leaf ambiguities unchanged. Preserve R156/R157/R158/R159/R160 manifests;
any follow-up canonical transition needs its own exact bounded hash-pinned
snapshot evidence. The private route and all 60-function exact inputs remain
preserved. No exact scope or recovered game layout is authorized.

## R161 — Vector endpoints, explicit constructors and genuine deque operation context

R161 reviews all nine candidates / 237 bytes and accepts eight library owners
/ 222 bytes: begin/end pairs `0x00409760`, `0x00409E60`, `0x0040E1F0`,
`0x0040E680` / 31 each; mutable iterator constructors `0x0040A120`,
`0x0040E9E0` / 28 each; deque subtraction-assignment `0x0040A190` / 27; and
SDK destruction `0x0040A830` / 15. SDK/ordinary destruction `0x0040F9F0`
/ 15 remains unknown. Replay
`scripts/repo-python scripts/verify-vector-endpoint-origins.py` with
`config/vector-endpoint-origin-evidence.json`. Every accepted candidate has
its complete positive own COFF AUX extent and unchanged size/span_end. All
bytes and genuine fields compare unmasked. Original declarations remain
unknown; provisional SDK names grant no source/private ABI/mapping/exact credit.

Entire original R034 assignment parents `0x00409780` and `0x0040E210`
/ 96 actually call both endpoint pairs. Their complete R095 assign wrappers
`0x00409470`, `0x0040DF20` / 29, R032 erase contexts / 99 and insert contexts
/ 33 remain independently retained and compare as whole source variants with
all real fields. SDK endpoint constructors call actual independently accepted
R106 const-iterator constructors `0x0040A590`, `0x0040F120` / 24. Source
observations use two complete four-byte records; their matching whole generic
assignment does not recover the original element type or a game container
layout. The actual SDK observations have vector size 16 and mutable/const
iterator sizes four; the offset-deque iterator observation is eight bytes.
These are source/compiler observations, not inferred original declarations.

**Operation refinement without new origin credit.** The original R078
`0x00409DF0` / 57 association used whole SDK deque addition `??Hiterator`,
whose recorded source field `??Yiterator` was bound to the then-unreviewed
`0x0040A190`. That original evidence remains byte-identical and is retained
as source-shape evidence. The actual leaf `0x0040A190` negates its argument
before calling full addition-assignment `0x0040A5E0` / 31. New complete SDK
subtraction `??Giterator` / 57 binds its genuine `??Ziterator` field to that
27-byte leaf and compares unmasked. Full SDK addition / 57 instead binds
its real `??Yiterator` to the independently complete 31-byte addition leaf;
linking that actual operation differs from the target only within the real
four-byte call field. Neither comparison truncates a function or masks an
accepted field. The parent's provisional role/evidence is refined to
subtraction; its R078 library origin, extent and origin credit remain unchanged.
The earlier masked/direct-binding shape alone could not distinguish operations.

Complete ordinary begin/end / 31 each, derived pointer constructor / 28,
base pointer constructor / 24 and two explicit destructor wrappers / 15 each
are fully byte-equal to their corresponding SDK target controls. Those six
ordinary controls / 144 bytes show that endpoint/constructor/destruction
shapes alone cannot identify original ownership or source. Library inference
uses the independent whole typed SDK parents, constructor/base and actual
operation relationships. No incomplete reconstructed game owner is instantiated.

The first destruction leaf compares through full unchanged R074 allocator
destruction `0x00409D60` / 25 and complete R037 generated deleting wrapper
`0x0040A9F0` / 44, with independently authored R017 resource policy
`0x004092F0` / 87 and R142 scalar delete `0x00640F15` / 5. The second
allocator parent is unchanged R033 `0x0040F860` / 25, whose SDK/ordinary
15-byte child calls full R037 wrapper `0x0040FA00` / 44. That wrapper calls
protected R108 lifetime policy `0x0040D8E0` / 19. Its original explicit/implicit
source ambiguity remains unresolved. The complete SDK/ordinary operation and
parent association do not resolve surrounding lifetime declarations; the
second 15-byte candidate remains unknown and receives evidence notes only.
Generated wrappers, authored policy and unknown policy remain separately
classified. No library leaf is bound directly past the intervening wrapper.

`probes/VC7VectorEndpointAlternatives.cpp` cold-builds all 176 ordinary
sections / 9404 bytes. Thirty-one full code controls / 1169 bytes and 41 actual
fields compare unmasked, including four whole original erase/insert variants
and six ordinary controls. Applicable owners have full positive own AUX;
both generated wrappers retain their whole unique defining COMDAT. The entire
68-byte layout is `[4,4,16,16,4,4,4,4,1,1,4,4,16,1,8,1,1]` and all 28 actual
SDK headers are pinned. Fourteen original parent/helper/compiler/policy records
are retained. Source evidence files remain immutable; the growing authored
evidence registry is checked by exact membership of its original R017 record,
not by freezing unrelated future additions. Only declared full selected
controls compare to target bytes; all ordinary emission is cold inventory
coverage, not an executable-wide match. Build 3077 and explicit flags are
per-probe reproducibility settings. Original source/type/compiler/linker inputs
and live count/range/offset/iterator/lifetime outcomes remain unknown.

Exactly eight origin rows and ten function-evidence rows change against
R160 HEAD ea7d1c0: eight library candidates, one pending destruction evidence
update and one retained R078 parent operation refinement. All unrelated and
protected rows, every authored record and previous evidence manifests remain
unchanged. Thirty-five regression checks protect full source/parent extents,
actual constructor/operation fields, immutable historical shape evidence,
whole genuine addition/subtraction controls, ordinary alternatives, independent
compiler/authored/unknown roles, pending-origin conservation and false credit.
Cold comparison precedes canonical acceptance; exact bounded rows read back
afterward. All 1464 public tests, local target/project/query attestation,
fresh scanner/progress, authored extents, exact-input and whitespace checks
pass. Public MCP acceptance remains waived, with the no-auth/private route
unchanged and private diagnostics/objects untracked.

Totals are 3501 resolved (922 authored, 2004 library, 575 compiler), 850 pending
and 2579 excluded. Authored evidence remains 875 bodies / 1953089 bytes;
provisional exact coverage stays 9883 / 1965432. All 60 source/mapped/exact
functions / 9883 bytes and exact inputs remain unchanged from R139 db26a05,
preserving its 60/60 cold replay across eleven objects. No affected exact unit
needs replay. The complete-origin objective remains unfinished. A fresh private
whole own-AUX source survey finds 258 relocation-excluding diagnostic
associations; these are not origin or exact acceptance. Genuine destination,
complete independent parent/context and full extent evidence remain necessary.

The next bounded R162 cohort is fifteen remaining vector endpoint/constructor
source-context candidates / 447 bytes. These are diagnostic associations, not
promised origin acceptances:

| Candidate group | Full provisional extents | Independent context to retain |
| --- | ---: | --- |
| `0x0040DCE0`, `0x0040DD00`, `0x0040E4A0` | 31, 31, 28 | whole R019 game parents `0x0040B280` / 727 and `0x0040B560` / 575; actual const-iterator constructor `0x0040E990`; pending assignment `0x0040E000` / 158 must not be truncated to the R034 96-byte source variant |
| `0x00411CC0`, `0x004121C0` | 31, 28 | whole R035 game parent `0x00411110` / 746; actual const-iterator constructor `0x00412440`; preserve the related still-unknown 42-byte iterator-producing helpers |
| `0x0041D980`, `0x0041EF00` | 31, 28 | whole R052 parent `0x0041D260` / 686 and R053 parent `0x0041D750` / 164; actual const-iterator constructor `0x0041F770`; preserve adjacent 42-byte source contexts |
| `0x00531DD0`, `0x00532300` | 31, 28 | actual const-iterator constructor `0x005323C0`; surrounding 42-byte producers remain unknown, so a source shape or reviewed child alone grants no origin |
| `0x005F8490`, `0x005F8EF0`, `0x005F95B0` | 31, 31, 28 | actual const-iterator constructor `0x005F9DB0`; pending assignment `0x005F84B0` / 167 and its lifetime/EH extent require independent full reconciliation, never a 96-byte prefix match |
| `0x005F8B50`, `0x005F9350`, `0x005F9600` | 31, 31, 28 | unchanged whole R034 assignment `0x005F8B70` / 96; actual const-iterator constructor `0x005F9E00`; freeze every real source/call field and original parent evidence |

Build natural complete SDK and ordinary alternatives, reconcile full own-AUX
or entire defining-source extents, and retain entire independently reviewed
game/library parents. Source parameter/return roles and all actual field
owners matter; the six R161 ordinary controls demonstrate that short endpoint
and constructor shapes alone do not establish original ownership or declarations.
A pending parent is not accepted because its child is library. Original record
sizes/kinds, container layouts and live outcomes remain unknown. Keep all R108
lifetime ambiguities, R158 record-copy ambiguity and R161 second destruction
leaf `0x0040F9F0` / 15 protected. Keep original R078 source-shape evidence and
R161 genuine operation refinement intact. All prior manifests, the private
route and 60-function exact inputs remain preserved; no exact scope is added.

## R162 — Complete vector producer observations and conservative ownership

R162 reviews fifteen short vector endpoint/constructor candidates / 447 bytes.
Only `0x005F8B50` / 31, `0x005F9350` / 31 and `0x005F9600` / 28 gain library
origin, totaling 90 bytes. Their independent whole R034 assignment
`0x005F8B70` / 96, complete R032 erase / 99 and insert / 33, and actual R106
const-iterator constructor / 24 supply a coherent retained SDK source context.
Every byte and actual relocation compares unmasked. Full own positive AUX
extents and canonical size/span_end are unchanged. The inference identifies
library ownership, not original record declarations or an original source file.

The other twelve candidates / 357 bytes remain unknown, as do the two full
assignment parents `0x0040E000` / 158 and `0x005F84B0` / 167. Complete ordinary
begin/end / 31 and derived iterator constructor / 28 are byte-equal to SDK
controls. More significantly, natural ordinary C++ members using a complete
SDK vector base, a real local record, erase and insert reproduce both entire
nontrivial assignment bodies and their complete exception cleanup/state data.
A reviewed game caller or library child does not independently settle ownership
of those original short leaves or parent declarations. Seventeen function rows
receive bounded evidence notes, while exactly three origin rows change; the
fourteen pending records retain their names, ownership and dispositions.

The 158-byte parent copies all 44 bytes of an observed local value; the
167-byte parent copies all 16 bytes. Each registers one unwind state and calls
its actual destructor both normally and through cleanup. Synthetic observation
types declare external destructors; these declarations are probe ABI inputs,
not recovered game declarations. The actual unknown policies `0x0040D8E0`
/ 19 (protected R108 ambiguity) and `0x004588B0` / 43 remain unknown. Existing
copy `0x004229D0` / 28 and destruction `0x0040F9F0` / 15 remain protected.
Neither nontrivial assignment is compared to a convenient 96-byte prefix.

For each SDK and ordinary parent, the whole 18-byte defining EH carrier has an
eight-byte destructor cleanup tail followed by the ten-byte handler entry.
The cleanup jumps to the actual destructor; the handler loads the genuine
FuncInfo and jumps to unchanged full R142 `0x006407B8` / 54. Entire 36-byte
state sections include both unwind records and FuncInfo, with the primary
FuncInfo definition at offset eight. Every local symbol is bound from this
cold object's own section definitions. Original R020 frames at `0x00654F68`
and `0x006566F8`, their owner registration sites, state/cleanup data and actual
field destinations are retained and revalidated. The `__except_list` value
zero is an FS offset, not PE data. Whole cleanup/handler carriers include
both shared tails; no positive own AUX is invented for generated local entries.

The pinned build 3077 rejects `/GS-` with an unknown `/G-` warning. The accepted
probe profile omits `/GS` and emits the full no-cookie 158/167-byte bodies.
A separately cold-built explicit `/GS` negative profile emits entire
174/183-byte SDK alternatives containing genuine cookie load/check fields.
Their lengths differ from target extents; they earn no match or origin credit.
This is a bounded compiler observation, not an executable-wide flag profile.
The short endpoint shapes cannot distinguish those flag choices.

Replay `scripts/repo-python scripts/verify-vector-producer-origins.py` with
`config/vector-producer-origin-evidence.json` and natural complete source
`probes/VC7VectorProducerContexts.cpp`. Forty-three full code/EH/state controls
/ 2039 bytes and 95 genuine fields compare unmasked. The primary cold inventory
covers all 244 ordinary sections / 13520 bytes, and the `/GS` negative inventory
covers all 244 sections / 13616 bytes. All 27 actual SDK headers and the complete
92-byte observation layout are pinned. Observations have record sizes 44, 16
and four, SDK vector sizes 16, and iterator sizes four; complete ordinary bases
are instantiated without declaring or instantiating an incomplete game owner.
Inventory coverage does not claim every emitted section matches the executable.
Original source, game layouts, lifetime declarations, linker choices and live
iterator/value outcomes remain unknown. No source/private ABI/mapping/exact
credit is added.

Five whole previously authored game parents retain all eight actual candidate
call windows: R019 `0x0040B280` / 727 and `0x0040B560` / 575, R035
`0x00411110` / 746, R052 `0x0041D260` / 686 and R053 `0x0041D750` / 164.
These are independently retained game evidence, not proof of callee ownership.
Six surrounding full 42-byte producer helpers and two eight-byte bridges remain
unknown and preserve their whole CFG. They cannot be accepted as 31-byte
endpoint prefixes. Nineteen original SDK/runtime/game records are retained by
immutable evidence files or exact authored-row membership. The growing authored
registry is not frozen against unrelated future additions.

Cold whole comparisons precede canonical acceptance. Exact bounded readback
against R161 HEAD a5c512e confirms three library-origin and seventeen function-
evidence changes; all unrelated rows, all authored evidence, previous manifests,
private route and exact inputs are unchanged. Thirty-four public regression
checks guard complete parents/EH/state/ordinary alternatives, actual fields,
protected unknown ownership and false source/ABI/exact credit. All 1498 public
checks, local target/project/query attestation, fresh scanner/progress, authored
extents, exact-input preservation and whitespace checks pass. Public MCP
acceptance remains waived by the user; private diagnostics and objects remain
untracked.

Totals are 3504 resolved (922 authored, 2007 library, 575 compiler), 847 pending
and 2582 excluded. Authored evidence remains 875 bodies / 1953089 bytes.
The 60 source/mapped/exact functions / 9883 bytes and all exact inputs remain
unchanged from R139 db26a05; its previous 60/60 cold replay across eleven objects
remains applicable. No affected exact unit needs replay. Provisional authored
coverage remains 9883 / 1965432 (0.50%). The full origin-review objective is
unfinished; this batch makes three conservative ownership decisions and retains
complete negative/ambiguous evidence for subsequent review.

The next bounded R163 cohort is twelve string-length wrapper/worker candidates
/ 253 provisional bytes. These are diagnostic associations, not promised origin
acceptances:

| Candidate pair | Full provisional extents | Required independent context |
| --- | ---: | --- |
| `0x0040D900`, `0x0040D920` | 17, 28 | whole source/runtime worker and actual string argument; retain protected R108 lifetime declarations independently |
| `0x0040D940`, `0x0040D960` | 17, 28 | second complete wrapper/worker; byte equality does not establish shared original ownership |
| `0x00412D90`, `0x00412DB0` | 17, 28 | actual complete caller and string/storage roles, not a name-only strlen binding |
| `0x00428D20`, `0x00428D40` | 17, 28 | complete string/source context and every real call/data/import field |
| `0x00438A60`, `0x00641FB8` | 17, 11 | whole independently reviewed game callers and full runtime/import/possible shared-tail extent |
| `0x00449A60`, `0x00449A80` | 17, 28 | whole authored parent `0x004491E0` and actual string arguments, keeping lifetime origins separate |

A fresh R162 full own-AUX survey yields 363 relocation-excluding diagnostic
associations; this does not grant origin or exact credit. The 17-byte shape also
fits an allocation wrapper when its real destination is ignored. Reconcile each
entire worker, source/ABI meaning, imports, CFG, exits, alignment and full own-AUX
or justified defining-source carrier before accepting anything. Compare natural
complete SDK, intrinsic/runtime and ordinary alternatives as applicable; retain
ambiguous user wrappers as unknown. Do not infer a parent from a reviewed child
or infer ownership from a reviewed game caller alone. Protect all prior R108
lifetime, R158 copy and R161 destruction ambiguities, the R161 retained R078
operation refinement, and the fourteen unknown R162 endpoint/assignment records.
All existing evidence and exact inputs remain preserved; no exact scope is added.

## R163 — Real math chains refute the diagnostic string-length label

R163 reviews all twelve candidates / 253 bytes from the R162 shortlist. Actual
full worker instructions and independently reviewed runtime destinations refute
that shortlist's string-length interpretation. Five 17-byte wrappers call whole
28-byte float-operation workers, and the sixth calls a whole eleven-byte integer
absolute-value body. The addresses and extents remain unchanged; the earlier
shortlist was a diagnostic association, never accepted ownership or source proof.

The five actual chains are `0x0040D900` to `0x0040D920` to C cos entry
`0x00641754`; `0x0040D940` to `0x0040D960` to C sin entry `0x00641804`;
`0x00412D90` to `0x00412DB0` to fabs `0x006418CD`; `0x00428D20` to
`0x00428D40` to C sqrt entry `0x00641E54`; and `0x00449A60` to `0x00449A80`
to ceil `0x00642120`. Workers load the four-byte floating argument, store an
eight-byte stack argument, make the real double-operation call, then store a
four-byte result observation before returning through x87. These instructions
and source variants establish a math operation context, not live rounding or
exception outcomes or an original function/type declaration.

The first, second and fourth destinations are source-defined C stack-double
entries at offset 20 inside whole unchanged R128 x87 primaries `0x00641740`
/ 174, `0x006417F0` / 174 and `0x00641E40` / 186. They are not the __CI entry
at offset zero, which receives an x87 register argument. Existing labels retain
their type-zero COFF definitions and overlapping nine-byte target extents;
no standalone AUX or independent source function is invented for them. Full
R129 fabs / 177 and R130 ceil / 64 remain accepted independently. All five
whole runtime primaries / 775 bytes replay from fresh extraction of the pinned
CRT archive, with every original actual field. Existing ceil source/shared-tail
reconciliation remains intact; no enclosing source carrier is redefined here.

`0x00438A60` / 17 calls `0x00641FB8` / 11, whose full signed branch/negation
body returns an integer absolute value. It is not a strlen worker or import
thunk. Fresh whole positive-AUX abs.obj and labs.obj controls both reproduce the
entire body. The prior natural R129 int/long expression source cold-builds both
complete eleven-byte alternatives and also reproduces this new target. The
separate original R129 abs candidate `0x00641DAA` remains unknown and unchanged.
Source spellings, int/long choice, library versus authored ownership and possible
linker folding cannot be inferred from these byte-equal alternatives.

Natural complete `probes/VC7MathOverloadContexts.cpp` emits genuine math.h
float overloads / 17, C float workers / 28 and the long abs overload / 17.
Separate ordinary C++ helpers with explicit double operations and ordinary
outer wrappers reproduce every target byte and real call field in the five
chains. An ordinary long wrapper is also byte-equal. Both entire source chains
are retained; binding a generic 17-byte shape to an assumed strlen or allocation
operation would hide the actual float/integer ABI and callee meaning. Complete
SDK/ordinary equality also leaves original wrapper/worker ownership unresolved.
Previously authored callers alone do not resolve that ambiguity. All twelve
origins therefore remain unknown; twelve function rows receive corrected bounded
evidence notes only, preserving names, extents, ownership and dispositions.

Replay `scripts/repo-python scripts/verify-math-overload-origins.py` with
`config/math-overload-origin-evidence.json`. Twenty-two whole positive-own-AUX
SDK/ordinary controls / 484 bytes and 22 actual unmasked REL32 fields compare.
All 29 cold ordinary sections / 602 bytes, six actual SDK headers and the full
16-byte layout `[4,8,4,4]` are pinned. These are observation/compiler sizes,
not recovered game declarations. The two original CRT abs/labs sections and
two newly cold ordinary expression controls each compare as entire eleven-byte
bodies. Existing source/runtime evidence is retained by exact record membership
and immutable file hashes; no previous origin is reopened or newly accepted.

Five whole authored game contexts / 8610 bytes retain twenty actual call
windows: R011 sprite parent `0x0040CA80` / 1132, R035 camera `0x004126C0`
/ 1520 and opening scene `0x004277A0` / 5339, R041 character selection
`0x00433A40` / 404 and R109 bounds policy `0x004491E0` / 215. Their complete
CFG, switch data where applicable, whole body hashes and argument/return windows
are verified. Exact original authored-row membership permits unrelated future
registry additions. All protected R108 lifetime, R158 copy, R161 destruction,
R162 endpoint/assignment and old R129 abs records remain unchanged.

Cold whole source comparisons precede the canonical evidence update. Readback
against R162 HEAD 6035ba5 confirms exactly twelve function-evidence changes and
zero origin, extent, name, source, ABI or exact changes. All unrelated ledgers,
previous manifests and authored records remain unchanged. Twenty-nine regression
checks guard full source chains, real math/C-entry ABI, complete runtime owners,
ordinary alternatives, pending ownership and false credit. All 1527 public
checks, local target/project/query attestation, fresh scanner, authored extents,
exact-input preservation and whitespace checks pass. Public MCP acceptance
remains waived; private diagnostics/objects and the unchanged no-auth route
remain private.

Totals remain 3504 resolved (922 authored, 2007 library, 575 compiler), 847
pending and 2582 excluded. Authored evidence remains 875 bodies / 1953089 bytes.
All 60 source/mapped/exact functions / 9883 bytes and source/header/build/match
inputs remain unchanged from R139 db26a05; its earlier 60/60 cold replay across
eleven objects remains applicable without affected-unit replay. Provisional
coverage remains 9883 / 1965432 (0.50%). This batch replaces a false semantic
shortlist with reproducible whole math/ordinary evidence and leaves uncertainty
explicit. The full remaining-origin goal is not complete.

The next bounded R164 cohort is five unresolved SDK dependency candidates
/ 504 provisional bytes, each reached from an independently accepted full
library parent. These are diagnostic contexts, not promised acceptances:

| Candidate | Full provisional extent | Independent whole parent to retain |
| --- | ---: | --- |
| `0x00415F60` | 44 | R074 `0x00415A80` / 22, provisionally named `VC7::max_size_00415A80` |
| `0x00422290` | 151 | R072 deque tidy `0x00421DD0` / 177; retain actual children `0x00422270`, `0x00422610` independently |
| `0x0042E120` | 151 | R072 deque tidy `0x0042DEF0` / 177; retain actual children `0x0042E100`, `0x0042E390` independently |
| `0x0045AFB0` | 50 | R033 generic copy `0x0045A7E0` / 51, with actual worker `0x0045AAE0` independently unresolved |
| `0x0045B640` | 108 | R033 construct `0x0045B2B0` / 29; actual `0x004063D0` and `0x004591E0` ownership remains independent |

Read the full actual parent and every source field; original generic names are
not source-type or ABI proof. Build natural complete SDK and ordinary controls,
reconcile full CFG, exits, shared tails, EH/data and own-AUX or defining-section
extents. A library parent supplies independent context but does not automatically
classify a child. Keep original parent evidence immutable. Do not instantiate
an incomplete reconstructed game owner or truncate a comparison to an emitted
source variant. Preserve all prior R108 lifetime, R158 copy, R161 destruction,
R162 endpoint/assignment and R163 math/abs ownership ambiguities, including the
unchanged R129 abs alternative and R161 R078 operation refinement. No exact
scope is added. The full origin-review goal remains active and unfinished.

## R164: SDK dependency ownership with complete independent parents

Five library inferences / 504 bytes now have complete genuine SDK source and
all actual unmasked fields: allocator max_size `0x00415F60` / 44, deque
pop_back `0x00422290` / 151 and `0x0042E120` / 151, forward nonscalar copy
`0x0045AFB0` / 50 and placement construction `0x0045B640` / 108. Independently
accepted full parents are R074 `0x00415A80` / 22, R072 `0x00421DD0` and
`0x0042DEF0` / 177 each, and R033 `0x0045A7E0` / 51 and `0x0045B2B0` / 29.
Their original source records and every real parent field remain unchanged.

The target's forward-copy source/destination advance by 116; the assignment
callee `0x0045AAE0` / 368 remains unknown. A whole genuine backward operation
is 48 bytes with its own actual assignment field and differs from the full
50-byte forward target. Placement new `0x004063D0` / 8 remains R005 library;
record copy `0x004591E0` / 417 remains unknown. The registered placement frame
has cleanup/handler `0x00656380` / `0x00656391` and unwind/FuncInfo
`0x00669C30` / `0x00669C38`. Both SDK and ordinary alternatives emit entire
27-byte cleanup/handler and 36-byte state sections. Their real fields bind
R160 placement delete `0x00412300` / 5 and R142 runtime handler `0x006407B8`
/ 54. The FS exception-list offset zero is not a PE object address.

Replay `scripts/repo-python scripts/verify-sdk-dependency-origins.py` using the
immutable `config/sdk-dependency-origin-evidence.json`. One new cold object
contains all 55 ordinary sections / 2360 bytes, 28 actual SDK headers and a
complete 60-byte observation layout `[2,20,60,116,20,20,20,1,1,1,1,1,20,20,1]`.
Widths, empty-allocator sizes and observer layouts are compiler/probe facts;
they do not recover original class declarations or private layouts. Natural
complete observers declare external real copy/assignment/destruction operations
and do not instantiate incomplete reconstructed owners.

Thirty-nine complete controls / 1988 bytes retain 57 actual fields. Thirty-seven
full positive comparisons / 1686 bytes pass. Five full ordinary alternatives
/ 252 bytes are byte-equal. Two whole 151-byte ordinary deque-pop controls
each differ at eight stack-local displacement bytes; every byte, actual field
and full CFG remains checked, with no masking or positive comparison credit.
Source local names remain unchanged instead of being adjusted for equality.
These alternatives alone do not establish original ownership. Library inference
requires the separate full coherent SDK source and accepted-parent context.

Seventeen retained original records and 41 body/canonical snapshots preserve
all previous independent evidence. Unknown allocator destroy wrappers
`0x00422610` / 25 and `0x0042E390` / 25, their 15-/5-byte children, the 72-byte
`0x004212A0` lifetime policy, opaque record assignment/copy and prior
R108/R158/R161/R162/R163 ambiguities receive no ownership. R037's deleting
wrapper remains compiler generated, and the two R088 map-pointer destruction
helpers remain library. Caller/child relationships do not propagate ownership.

Full cold replay precedes acceptance. R163 HEAD 1923ec1 readback confirms exactly
five origin/function transitions and no unrelated rows, previous manifests,
authored evidence or exact-input changes. Thirty-four new regression guards and
all 1561 public checks pass, as do local target/project/query attestation,
fresh scanning, authored extents, exact preservation and whitespace checks.
Totals are 3509 resolved (922 authored, 2012 library, 575 compiler), 842 pending
and 2587 excluded. Authored evidence remains 875 bodies / 1953089 bytes;
the 60 source/mapped/exact functions / 9883 bytes and all R139 db26a05 exact
inputs remain unchanged. Its earlier cold 60/60 replay across eleven objects
remains applicable. Provisional exact coverage remains 0.50%, with no new
source/private ABI/mapping/exact credit. Public MCP acceptance remains waived.

The next bounded R165 cohort is the two 25-byte allocator destroy wrappers
through the newly accepted full deque-pop parents. Preserve their independently
unknown 15-/5-byte children and the separate 72-byte lifetime policy. Retain
R164's immutable evidence and allow only exact future bounded snapshot
transitions after a complete acceptance. The full remaining-origin goal is active
and unfinished; no exact-reconstruction scope is added.

## R165: Allocator wrappers and independent destruction policies

Two complete 25-byte allocator.destroy wrappers, `0x00422610` and
`0x0042E390`, are now library through genuine full SDK source, every actual
field and the unchanged full R164 deque-pop parents / 151 bytes each.
Actual children `0x004229C0` / 15 and `0x0042E580` / 5 remain independently
unknown. Their scalar-deleting compiler wrapper and its separate 72-byte
game lifetime child retain their original compiler/unknown ownership.
Ghidra's earlier proxy label does not establish the original element type.

Replay `scripts/repo-python scripts/verify-allocator-destroy-origins.py` with
`config/allocator-destroy-origin-evidence.json`. One cold source includes the
unchanged hash-pinned R164 complete observations and adds ordinary allocator
and direct-destruction controls. All 61 ordinary sections / 2472 bytes, 28
SDK headers and the actual original probe include are retained. Both observation
arrays inhabit one whole 68-byte readonly section with definitions at zero
and 60; all seventeen values `[2,20,60,116,20,20,20,1,1,1,1,1,20,20,1,1,1]`
are checked without slicing. These are compiler/probe facts, not original
private game layouts or declarations.

Thirteen whole controls / 536 bytes and twelve actual fields compare unmasked,
with complete own-AUX extents or the entire unique generated-wrapper COMDAT.
Four ordinary controls / 70 bytes are byte-equal. These alternatives alone
do not establish source ownership, original destructor spelling or child policy.
The library inferences require independent coherent full accepted deque parents.
No incomplete reconstructed owner is instantiated. R037's 44-byte deleting
wrapper and R142's five-byte runtime delete remain independently accepted;
the 72-byte `0x004212A0` policy remains unknown.

Four exact original evidence records and 41 canonical/body snapshots retain
all unrelated owners and protected lifetime/copy/math ambiguities. R164's
manifest stays immutable; its verifier allows only the two exact accepted
R165 row transitions after checking the new immutable manifest. Changed
original or unrelated rows remain rejected. Its entire cold source/code/EH/
data replay passes after acceptance. Full cold comparison precedes the canonical
update; R164 HEAD d172412 readback verifies exactly two function/origin changes
and unchanged previous evidence, authored records and exact inputs.

Thirty new regression guards and all 1591 public checks pass. Local target,
project/query completion, fresh scanner, 875 authored extents / 1953089 bytes,
exact preservation and whitespace checks pass. Public MCP acceptance stays
waived. Totals are 3511 resolved (922 authored, 2014 library, 575 compiler),
840 pending and 2589 excluded. The 60 source/mapped/exact functions / 9883
bytes and all R139 db26a05 exact inputs remain unchanged; its earlier cold
60/60 replay across eleven objects remains applicable. Provisional coverage
stays 0.50%, with no new source/private ABI/mapping/exact credit.

The next bounded R166 cohort is four diagnostic game-parent context candidates
/ 600 provisional bytes (`0x00410F30`, `0x0045B760`, `0x0045B920`,
`0x005F7140`) with complete R045/R050/R065 parents listed in the handoff.
Game callers or library children alone grant no origin. Preserve independently
unknown destruction/lifetime/copy/math policies. The full goal remains active
and unfinished, without exact-reconstruction scope.

## R166: Complete custom defaults, queue initialization and pointer release policies

Four whole functions / 600 bytes now have authored origin through complete
custom behavior and independent whole game parents: `0x00410F30` / 104
stores its incoming identifier and defaults flags 15/mode 5 before member
clear; `0x0045B760` / 203 installs the observed vptr after base construction
and writes fifteen sparse scalar defaults; `0x0045B920` / 131 constructs
four 20-byte deque observations then loops over explicit clear calls;
`0x005F7140` / 162 deletes each pointer in two queues and clears each queue
after its loop. Names, original method spelling and full owner layouts remain
provisional. Library children and parent labels alone do not establish origin.

Replay `scripts/repo-python scripts/verify-game-parent-policy-origins.py` using
immutable `config/game-parent-policy-origin-evidence.json`. Three entire natural
C++ policies / 397 bytes compare unmasked with complete own-AUX extents.
The separate 203-byte initializer relies on its whole target CFG, all fifteen
actual default writes and independent complete Reimu initializer. No positive
source match is claimed for it. Whole implicit construction controls / 25,
40 and 31 bytes are negative alternatives, never target prefixes. Their generated
definitions have no primary AUX records, so the verifier checks each complete
unique defining code COMDAT, actual symbol metadata, full source bytes and CFG.

Nineteen complete source/code/EH/state comparisons / 1340 bytes retain 63 real
unmasked fields. Entire 21-/32-byte cleanup/handler carriers and both full
36-byte state sections preserve the original R020 list/array frames and actual
98-/96-byte runtime array helpers. Four unchanged whole authored parents
/ 4897 bytes retain original evidence and actual argument/return call windows;
the battle loader retains both complete guarded switch tables / 64 bytes.
All 146 cold ordinary sections / 6709 bytes, 29 actual SDK headers and complete
36-byte layout `[20,20,84,84,40,4,4,12,20]` are pinned. Unsigned list, float
array-deque and unsigned-pointer observations distinguish genuine source owners
and allocator destinations without claiming original game types or layouts.

SDK clear and destructor source alternatives are fully byte-equal at the relevant
19-byte boundaries. R077's original destructor evidence remains immutable;
original spelling stays unknown. The R073 72-byte deque constructor retains
library ownership. Independent unknown list operations, custom wrapper, base
constructors and lower helpers receive no new ownership. Only one readonly
four-byte virtual slot is observed at `0x00659064`; its full 149-byte target
`0x0045B880` stays unknown. Neither original whole vtable extent nor virtual
declaration ABI is recovered. The complete four-byte synthetic virtual observer
serves only as a negative control and is not an instantiated original owner.

Eleven exact prior records and 88 canonical/body snapshots retain independent
source/runtime owners and every protected lifetime/copy/math/destruction policy.
Original authored-parent records are preserved by exact membership, allowing
unrelated future additions. Complete cold comparison precedes canonical
acceptance. R165 HEAD 646a2f3 readback verifies exactly four function/origin
changes and four new authored extent records; all 875 original authored rows,
headers/order, prior manifests, unrelated records and exact inputs remain intact.
Forty-two new regression checks and all 1633 public checks pass, as do local
target/project/query attestation, fresh scanning, authored extents and whitespace.

Totals are 3515 resolved (926 authored, 2014 library, 575 compiler), 836 pending
and 2589 excluded. Authored evidence is 879 complete bodies / 1953689 bytes.
The 60 source/mapped/exact functions / 9883 bytes and R139 db26a05 exact inputs
remain unchanged; its earlier cold 60/60 replay across eleven objects remains
applicable. Provisional exact coverage is 9883 / 1966032 (0.50%), with no new
reconstructed source/private ABI/mapping/exact credit. Public MCP acceptance
remains waived and the full remaining-origin goal is active and unfinished.

The next bounded R167 cohort is four list-policy dependencies / 250 bytes:
`0x00411C30` / 56, `0x004110F0` / 22, `0x00411D60` / 153 and
`0x00411C70` / 19. Preserve complete R166 parent/wrapper/EH context and all
actual lower node/allocator boundaries; a source association alone does not
identify original element/node types. No exact scope is added.

## R167 complete list graph, node width and catch extent

The bounded four-candidate R167 cohort expands only to its necessary complete
list/allocator dependency graph. One authored wrapper / 22 bytes and eleven
library definitions / 718 bytes are accepted through the unchanged whole R166
custom policy `0x00410F30` / 104 and complete R045 game parent `0x00456B60` /
1186. Caller labels, byte shapes and a compiled method name alone prove no
ownership. Replay `scripts/repo-python scripts/verify-list-policy-dependency-origins.py`
against immutable `config/list-policy-dependency-origin-evidence.json`.

| Address | Accepted complete bytes | Inferred source role | Origin |
| --- | ---: | --- | --- |
| `0x004110F0` | 22 | custom owner clear, delegates to list at receiver +4 | authored |
| `0x00411C30` | 56 | SDK list constructor | library |
| `0x00411C70` | 19 | SDK list destructor, calls complete `_Tidy` | library |
| `0x00411D60` | 153 | SDK list clear, all six real node-operation fields | library |
| `0x00411FE0` | 223 | SDK `_Buynode`, including local catch and shared tail | library |
| `0x004120C0` | 100 | SDK `_Tidy`, clear and sentinel link destruction/deallocation | library |
| `0x00412130` | 53 | SDK `_List_val` constructor | library |
| `0x00412170` | 14 | SDK value allocator constructor | library |
| `0x004121A0` | 25 | SDK node allocator destroy wrapper | library |
| `0x004123E0` | 27 | SDK node allocator allocation wrapper | library |
| `0x00412420` | 25 | SDK node-pointer allocator destroy wrapper | library |
| `0x004125A0` | 23 | SDK `_Allocate`, actual 172-byte node multiplier | library |

Target observation: the old `_Buynode` candidate ends at `0x0041206E`, before
its catch. The actual complete primary is `0x00411FE0..0x004120BE` / 223 bytes.
Both forward catch/shared-tail branches are internal to that full primary; the
complete source's own positive AUX extent is also 223 bytes. A local typed COFF
catch label at +143 corresponds to `0x0041206F`. The complete 80-byte
try/catch/unwind/FuncInfo section at `0x00668194` retains all four real fields,
including the actual catch entry, catch table, unwind array and try map. Original
R020 registrations at `0x0065501B` and `0x00655030` are read back and verified.
The canonical primary extent is reconciled before library acceptance; no 143-byte
prefix earns complete evidence. The independently listed 80-byte catch interior
stays unknown, with the overlap explicit and no separate primary AUX claim.

Compiler/source observation: a complete `std::list` of a synthetic 164-byte
record emits the observed 172-byte node allocation, plus the complete list
constructor, clear, destructor, allocation and destruction graph. All 31 entire
positive controls / 1288 bytes compare unmasked, retaining 62 genuine fields
through one coherent catalog of actual defining code/local EH/data symbols.
Every regular positive has its own full AUX extent. Full EH carriers are 21 and
10 bytes; complete registered state carriers are 36 and 80 bytes. Existing
allocator hierarchy/construct/deallocate records and full R142 frame/throw/delete
and R154 scalar-new boundaries remain independent. Thirteen original records
and 103 full canonical/body snapshots are retained; the growing authored CSV is
checked by exact original-row membership, never an immutable whole-file hash.

An ordinary delegating destructor reproduces the entire 19-byte SDK destructor;
original spelling remains unknown. A full implicit 22-byte owner destructor
calls `0x00411C70`, whereas the actual custom wrapper calls `0x00411D60`.
Their complete real-callee fields differ. The entire unsigned-list node
allocation is 20 bytes and differs from the full 23-byte target allocation; no
prefix or masked comparison is used. These two complete negatives / 42 bytes
retain their actual SDK destinations. The 164-byte payload is an observation,
not original element identity or a reconstructed game layout. No incomplete
original game owner is instantiated.

All 182 cold ordinary sections / 8150 bytes, 29 actual SDK headers plus the
unchanged pinned R166 probe include, and the entire combined 56-byte readonly
layout `[20,20,84,84,40,4,4,12,20,164,20,12,1,16]` are frozen. The full unchanged
104-byte custom policy retains every real field and operation; its independent
1186-byte game anchor retains the original authored record, complete CFG and
actual argument/call window. The original R166 manifest is immutable. Its
verifier permits only these exact R167 original-to-accepted transitions and
cold-replays successfully. Its older 143-byte node snapshot remains historical
context; the new acceptance independently compares the whole 223-byte primary.

Unknowns remain explicit: `0x00411E80` / 8, `0x00411E90` / 11, `0x00412580` /
5 and `0x00412600` / 5 receive no ownership from SDK-shaped pointer/no-op bodies.
The separate catch interior and every prior protected lifetime/copy/math/
destruction policy retain their original rows. Complete cold evidence preceded
canonical changes. Strict R166 HEAD adbe743 readback confirms exactly twelve
function/origin changes, only one primary extent refinement, and one new authored
22-byte record; all 879 old authored rows, original headers/order, previous
manifests and exact source/header/build/ABI/mapping/match inputs remain unchanged.
Thirty-two new regression checks and all 1665 public checks pass, as do fresh
scanning, full authored extents, local attestation and whitespace checks.

Totals are 3527 resolved (927 authored, 2025 library, 575 compiler), 824 pending
and 2600 excluded. Authored evidence is 880 complete bodies / 1953711 bytes.
The exact baseline remains 60 functions / 9883 bytes, with provisional coverage
9883 / 1966054 (0.50%); the earlier R139 60/60 cold replay across eleven objects
remains applicable. No reconstructed source, private ABI, mapping or exact
credit is added. Public MCP acceptance stays waived; the complete-origin goal
is active and unfinished. The next bounded R168 cohort is the seven list-iterator
policies / 233 bytes recorded in the current handoff, with complete independent
game parents and necessary lower operation/EH dependencies.

## R168 complete iterator graph and value-node catch extent

Nineteen library definitions / 1097 bytes are accepted through the complete
seven-candidate iterator cohort and necessary closed dependencies. Replay
`scripts/repo-python scripts/verify-list-iterator-policy-origins.py` with
immutable `config/list-iterator-policy-origin-evidence.json`. Full unchanged R035
custom game parents `0x00411000` / 183 and `0x00411110` / 746 retain original
authored records, complete instructions, CFG and actual argument/value context.
Their field/stack/copy/render policies provide independent game context; ownership
is inferred from the entire defining SDK graph, not those caller labels alone.

| Address | Complete bytes | Inferred SDK role |
| --- | ---: | --- |
| `0x00411C90` | 42 | list begin |
| `0x00411CC0` | 31 | list end |
| `0x00411CE0` | 17 | list size |
| `0x00411D00` | 40 | list pop-front |
| `0x00411D30` | 42 | list push-back |
| `0x00411E00` | 19 | mutable iterator arrow |
| `0x00411E20` | 42 | mutable iterator postincrement |
| `0x004121C0` | 28 | mutable iterator node constructor |
| `0x00411F20` | 186 | list erase |
| `0x00411EA0` | 115 | list insertion |
| `0x004121E0` | 19 | mutable iterator dereference |
| `0x00412200` | 22 | mutable iterator preincrement |
| `0x00412240` | 189 | value-node allocation, catch and shared tail |
| `0x00412310` | 126 | size growth with full length-error path |
| `0x00412460` | 25 | const iterator dereference |
| `0x00412480` | 35 | const iterator preincrement |
| `0x004124D0` | 22 | list maximum size |
| `0x00412510` | 53 | SDK node constructor with whole value copy |
| `0x00412550` | 44 | value allocator maximum size |

Target observation: the old value-node allocation ends at `0x004122C8` before
catch. The complete primary is `0x00412240..0x004122FC` / 189 bytes. It includes
the +137 catch and complete shared tail, all branches/exits, placement allocation,
actual node construction, cleanup/deallocation and rethrow. Own primary source
AUX is 189 bytes. The entire 27-byte placement-cleanup/handler carrier and
88-byte unwind/catch/try/FuncInfo carrier are compared with all real fields.
R020 registration at `0x00655051` remains unchanged. Canonical primary extent
is refined before acceptance; no 137-byte prefix earns evidence. The independent
52-byte catch candidate `0x004122C9` stays unknown with the overlap explicit.

Compiler/source observation: genuine SDK mutable/const iterator, erase, insertion,
node construction and size-growth definitions form one coherent catalog, through
unchanged R167 allocation/destruction, R106 iterator constructor and placement
helpers. The complete synthetic 164-byte value record produces the actual
172-byte node and capacity divisor 164. All 93 whole positive source/code/EH/
throw/RTTI/data controls / 4248 bytes compare unmasked with 210 genuine fields.
This includes the full length-error string, throw descriptors, catchable-type
arrays, type descriptors, exception/string code and every EH/state carrier.
Six original R020 frames are verified against their real owners. R004/R005
exception/string/compiler classifications, R142 exception/frame/throw/delete,
R154 scalar new and R006/R025 string/memory runtime boundaries are retained;
no whole-executable compiler profile or reclassification is inferred.

Ordinary size, arrow and postincrement alternatives reproduce all 17/19/42
bytes / 78 bytes, using the same independent complete real operation boundaries.
They demonstrate source-shape ambiguity; original method spelling and declaration
identity remain unresolved. Regular positives retain full own AUX extents.
The existing 37-/100-byte implicit exception copy constructors lack primary AUX
and are checked as their entire unique defining code COMDATs, preserving their
original compiler ownership. No prefix, fake return, padding, inert local or
conditional source body is used. Complete observers instantiate no incomplete
original game owner. The value width is an observation, not recovered private
layout. One actual readonly four-byte external type-info slot is retained without
claiming a whole vtable extent.

All 225 cold ordinary sections / 10007 bytes, 29 actual SDK headers plus the two
unchanged pinned R166/R167 probe includes, and entire combined 76-byte layout
`[20,20,84,84,40,4,4,12,20,164,20,12,1,16,4,4,12,1,4]` are frozen. Sixteen prior
records and 182 complete canonical/body snapshots preserve all existing ownership.
The R162 manifest remains immutable. For its two pending candidate records,
only the exact R162 accepted-pending to R168 accepted-library rows are allowed;
for the two separate snapshot contexts, only exact original-to-R168 transitions
are allowed. Both old ordinary and cookie-negative source profiles cold-replay.
Its original unresolved decisions remain historical evidence, with later full
acceptance checked separately. All other old ambiguities remain unchanged.

Tiny pointer/node/value accessors at `0x00411E80`, `0x00411E90`, `0x004124B0`
and `0x004124C0`, both empty destruction children and both catch interiors keep
unknown ownership. Earlier unrelated lifetime/copy/math/destruction policies are
preserved. Complete cold evidence precedes canonical changes. Strict R167 HEAD
70876bb readback verifies exactly nineteen function/origin changes, only one
primary extent refinement, and no new authored rows. All 880 original authored
rows/order, prior manifests and exact source/header/build/ABI/mapping/match inputs
are preserved. Thirty-four new regression checks and all 1699 public checks pass,
as do fresh scanning, authored extents, local attestation and whitespace checks.

Totals are 3546 resolved (927 authored, 2044 library, 575 compiler), 805 pending
and 2619 excluded. Authored evidence remains 880 complete bodies / 1953711
bytes. The exact baseline remains 60 functions / 9883 bytes with provisional
coverage 9883 / 1966054 (0.50%); R139's earlier 60/60 cold replay across eleven
objects remains applicable. No source/private ABI/mapping/exact credit is added.
Public MCP acceptance remains waived and the full remaining-origin goal is active
and unfinished. The next bounded R169 cohort is five archive-list dependencies
/ 160 bytes with full R052 write/index policies, recorded in the current handoff.

## R169 archive node width and full allocation/catch graph

Thirteen library definitions / 753 bytes are accepted through the five-candidate
archive-list cohort and necessary complete SDK dependencies. Replay
`scripts/repo-python scripts/verify-archive-list-policy-origins.py` with immutable
`config/archive-list-policy-origin-evidence.json`. Full unchanged R052 archive
write/index policies `0x0041D260` / 686 and `0x0041D510` / 429 retain complete
instructions, actual field/value/argument context, original authored records
and CFG. Their archive-specific behavior provides independent ownership context;
caller labels, mapped types and short byte shapes alone prove no ownership.

| Address | Complete bytes | Inferred SDK role |
| --- | ---: | --- |
| `0x0041D950` | 42 | list begin |
| `0x0041D980` | 31 | list end |
| `0x0041D9A0` | 17 | list size |
| `0x0041D9C0` | 42 | list push-back |
| `0x0041EF00` | 28 | iterator node constructor |
| `0x0041E120` | 115 | list insertion |
| `0x0041EF60` | 186 | complete value-node allocation, catch and shared tail |
| `0x0041F020` | 126 | size growth with full length-error path |
| `0x0041F0F0` | 27 | node allocator allocation |
| `0x0041F980` | 53 | SDK node constructor and whole value copy |
| `0x0041F800` | 22 | list maximum size |
| `0x0041FD90` | 20 | node allocation with actual 116-byte multiplier |
| `0x0041F9C0` | 44 | value allocator maximum size |

Target observation: the archive reader processes an observed 108-byte stride;
actual node placement allocates 116 bytes. This list's capacity calculation uses
value width 108. The complete allocation is `0x0041EF60..0x0041F019` / 186
bytes, including local catch at +134 and shared tail. Its previous provisional
134-byte entry stops before catch. Source primary AUX covers the whole 186
bytes. The complete 27-byte cleanup/handler carrier at `0x006554C0` and 88-byte
unwind/catch/try/FuncInfo carrier at `0x00668690` retain every actual field and
R020 registration `0x006554D1`. The separate 52-byte catch candidate
`0x0041EFE6` remains unknown; no independent primary AUX/ownership is claimed.

Compiler/source observation: a complete synthetic 108-byte record produces the
116-byte node and genuine list/iterator/insertion/allocation graph. All eighty
whole positive source/code/EH/throw/RTTI/data controls / 3752 bytes compare
unmasked with 189 real fields through one coherent actual defining-symbol
catalog. These include full string/length-error, throw/catchable-type/type
metadata and actual exception/runtime boundaries. Existing R106 constructor/
deallocation, R160 placement delete, R004/R005 string/exception/compiler,
R142 exception/frame/throw/delete, R154 scalar new and R006/R025 string/memory
owners remain independent. Six original R020 frames are verified. The existing
37-/100-byte implicit exception copies are checked as complete unique code
COMDATs despite lacking primary AUX; all regular positives have full own AUX.

The entire ordinary size alternative / 17 bytes is byte-equal. Original method
spelling stays unknown. The full previous 164-byte-payload node allocation /
23 bytes is negative against the entire 20-byte target; the full unsigned-node
allocation / 20 bytes differs at its genuine node-width immediate. Together these
two negatives / 43 bytes retain actual scalar new, never compare target prefixes
and earn no positive source/exact credit. Neither the 108-byte observation nor
the complete source emission recovers the original archive entry declaration,
packing, member identity or private game layout. No incomplete original owner
is instantiated and no target byte array, assembly, fake return or inert padding
is used. One actual four-byte readonly external type-info slot establishes no
whole vtable extent.

All 250 cold ordinary sections / 11163 bytes, 29 actual SDK headers plus the
unchanged pinned R166/R167/R168 probe includes, and entire combined 88-byte
layout `[20,20,84,84,40,4,4,12,20,164,20,12,1,16,4,4,12,1,4,108,12,4]` are
frozen. Eleven prior records and 205 complete canonical/body snapshots preserve
existing context. R162's manifest remains immutable; its two relevant pending
candidate records allow only exact accepted-pending to R169 library transitions,
and two separate snapshots allow only exact original-to-R169 transitions.
Both old ordinary and cookie-negative profiles cold-replay. Previous R168
transitions remain exact and intact; all other historical pending decisions and
protected opaque owners stay unchanged.

Link accessors `0x0041E100` / 8 and `0x0041E110` / 11, node getter
`0x0041F7E0` / 16 and the catch interior receive no origin from source-equal
short bodies. Earlier independent getters, empty destruction children and
lifetime/copy/math policies are preserved. Complete cold evidence preceded
canonical changes. Strict R168 HEAD ca7566f readback verifies exactly thirteen
function/origin changes, only one full primary extent refinement and no authored
additions. All 880 original authored rows/order, previous manifests and exact
source/header/build/ABI/mapping/match inputs remain intact. Thirty-six new
regression checks and all 1735 public checks pass, with fresh scanning, full
authored extents, local attestation and whitespace checks.

Totals are 3559 resolved (927 authored, 2057 library, 575 compiler), 792 pending
and 2632 excluded. Authored evidence remains 880 complete bodies / 1953711
bytes. Exact stays 60 functions / 9883 bytes, with provisional coverage
9883 / 1966054 (0.50%); R139's earlier cold 60/60 replay across eleven objects
remains applicable. No source/private ABI/mapping/exact credit is added.
Public MCP acceptance stays waived; the full remaining-origin goal is active
and unfinished. The next bounded R170 cohort is five character-list dependencies
/ 160 bytes through the complete R049 1008-byte game policy, recorded in the
current handoff. Its value width must be established independently.

## R170 — character-list graph with independently observed value width

Twelve complete library definitions / 720 bytes are accepted through the five
character-list roots and necessary complete SDK dependencies. Replay
`scripts/repo-python scripts/verify-character-list-policy-origins.py` with immutable
`config/character-list-policy-origin-evidence.json`. The unchanged independently
authored R049 game policy `0x005301B0` / 1008 bytes retains every instruction,
original authored record, complete CFG and switch records. Actual push-back and
size calls at `0x00530225` / `0x00530233` provide independent argument/value
context. Caller labels, mapped types and short byte shapes alone prove no owner.

| Address | Complete bytes | Inferred SDK role |
| --- | ---: | --- |
| `0x00531DA0` | 42 | list begin |
| `0x00531DD0` | 31 | list end |
| `0x00531C60` | 17 | list size |
| `0x00531CB0` | 42 | list push-back |
| `0x00532300` | 28 | mutable iterator node constructor |
| `0x00531DF0` | 115 | list insertion |
| `0x00532110` | 186 | complete value-node allocation with catch and shared tail |
| `0x005321D0` | 126 | size growth with full length-error path |
| `0x005322A0` | 27 | node allocator allocation |
| `0x005323E0` | 64 | node constructor with complete four-word value copy |
| `0x00532360` | 22 | list maximum size |
| `0x005324A0` | 20 | node allocation with actual 24-byte multiplier |

Target observation: actual node placement requests 24 bytes at `0x0053214D`;
the node constructor copies the complete observed 16-byte value. Capacity uses
value width 16. The complete primary `0x00532110..0x005321C9` is 186 bytes,
including its local catch at +134 and shared tail; the previous 134-byte extent
stops before catch. Source primary AUX independently covers all 186 bytes.
The whole 27-byte cleanup/handler carrier `0x00656520` and 88-byte unwind/catch/
try/FuncInfo carrier `0x00669E5C` retain every real field and R020 registration
`0x00656531`. The separate 52-byte interior `0x00532196` stays unknown; its
local-label membership supplies no separate primary AUX or ownership evidence.

Compiler/source observation: a complete synthetic 16-byte value produces a
24-byte node and the genuine SDK list/iterator/insertion/allocation graph. The
64-byte node constructor differs naturally from the previous larger-record
copy strategy. All eighty complete positive source/code/EH/throw/RTTI/data
controls / 3763 bytes compare unmasked with 189 genuine fields through one
coherent actual defining-symbol catalog. Full string/length-error, throw and
catchable-type/type metadata retain independent exception/runtime boundaries.
Existing R106 const-iterator construction `0x005323C0` / 24 and deallocation,
R032 allocator maximum size `0x00532420` / 44, R160 placement delete,
R004/R005 string/exception/compiler, R142 exception/frame/throw/delete,
R154 scalar new and R006/R025 string/memory records remain unchanged. Six
original R020 frames are verified. Existing 37-/100-byte implicit exception
copies retain their complete unique defining COMDATs despite lacking primary
AUX; every regular positive has its own full primary AUX.

The whole ordinary size alternative / 17 bytes is byte-equal, so original
method spelling remains provisional. Two entire prior-108 and unsigned node
allocation negatives / 20 bytes each compare against the entire 20-byte target,
retaining actual scalar new. Each differs at genuine node-width immediate byte
+8. Neither negatives nor short equivalent shapes earn positive/exact credit.
Widths 16/24 are observations of this list, independent of earlier 164/172 and
108/116 observations; original character-entry declaration, packing, fields and
private game layout remain unknown. The complete synthetic observer establishes
no original owner, and uses no target arrays, assembly, fake returns or inert
padding. One four-byte readonly external type-info slot establishes no whole
vtable extent.

All 275 cold ordinary sections / 12330 bytes, 29 actual SDK headers plus four
unchanged pinned R166/R167/R168/R169 probe includes, and the entire 100-byte
combined layout are frozen. Its 25 words are
`[20,20,84,84,40,4,4,12,20,164,20,12,1,16,4,4,12,1,4,108,12,4,16,12,4]`.
Eleven prior records, including the complete R169 node allocation, and 227
complete canonical/body snapshots preserve existing context. R162's manifest
stays immutable. Only two exact accepted-pending to R170 library transitions
and two exact separate original-to-R170 snapshot transitions are allowed. Both
old ordinary and cookie-negative profiles cold-replay. R168/R169 transitions
remain exact; all unrelated historical pending decisions stay unchanged.

Link accessors `0x00531D80` / 8 and `0x00531D90` / 11, node getter
`0x00532350` / 16 and the catch interior remain unknown. All prior opaque
getters, empty destruction children and lifetime/copy/math policies are preserved.
Full cold evidence preceded canonical changes. Strict R169 HEAD e9ba039 readback
verifies exactly twelve function/origin changes, only the one full primary extent
refinement and no authored additions. All 880 original authored rows/order,
previous manifests and source/header/build/ABI/mapping/match inputs remain
intact. Thirty-six new regression checks and all 1771 public checks pass, with
fresh scanning, full authored extents, local attestation and whitespace checks.

Totals are 3571 resolved (927 authored, 2069 library, 575 compiler), 780 pending
and 2644 excluded. Authored evidence stays 880 complete bodies / 1953711 bytes.
Exact stays 60 functions / 9883 bytes with provisional coverage
9883 / 1966054 (0.50%); the earlier R139 cold 60/60 replay across eleven objects
remains applicable. No source/private ABI/mapping/exact credit is added. Public
MCP acceptance stays waived. The full remaining-origin goal is active and
unfinished; the next bounded cohort is the three complete default deque
const-iterator candidates and their actual whole producer/consumer contexts.

## R171 — complete replay deque iterator graphs

Twelve whole SDK definitions / 381 bytes are accepted through the three default
const-iterator candidates and necessary complete construction/endpoint context.
Replay `scripts/repo-python scripts/verify-replay-deque-iterator-origins.py` with
immutable `config/replay-deque-iterator-origin-evidence.json`. The independently
authored R035 `ReplayRecords::AppendRecord` at `0x00413DE0` / 1252 remains
unchanged, with its original full record, instructions, fourteen branches, one
return and switch rows. Its 26 actual iterator construction/endpoint/step/
comparison/dereference edges are frozen. Default temporaries feed the actual
iteration and write loops; observed stream widths 1/2/4 supply independent
context for the three entire specialization graphs. Caller labels, mapped
names and two zero stores alone are insufficient ownership evidence.

| Address | Complete bytes | Inferred SDK role |
| --- | ---: | --- |
| `0x00414930` | 22 | default iterator |
| `0x004149E0` | 22 | default iterator |
| `0x004145C0` | 35 | begin |
| `0x004145F0` | 41 | end |
| `0x00414A90` | 22 | default iterator |
| `0x004147B0` | 35 | begin |
| `0x004147E0` | 41 | end |
| `0x004155A0` | 33 | default const iterator |
| `0x004156B0` | 33 | default const iterator |
| `0x00415670` | 32 | node iterator constructor |
| `0x004157C0` | 33 | default const iterator |
| `0x00415780` | 32 | node iterator constructor |

Compiler/source observation: complete `std::deque<unsigned char>`,
`std::deque<unsigned short>` and `std::deque<unsigned long>` observers emit
three natural default/endpoint/postfix/prefix/comparison/dereference graphs.
All 36 entire genuine SDK definitions / 1437 bytes retain 21 real call fields
and compare unmasked through one coherent actual defining-symbol catalog.
This includes the already accepted R111 byte endpoints/node construction,
R112 postfix operations, R085/R106 prefix operations and const-node constructors,
R032 inequality, R084 equality and R078 complete dereference bodies. The
three specializations independently retain their actual destinations; widths
and synthetic types do not recover original signedness, declarations, method
spelling or private replay/game owner layout.

Entire ordinary base/default and derived constructors / 33 and 22 bytes are
byte-equal to the byte iterator construction pair, including the one actual
base-construction field. These expose short-shape ambiguity rather than proving
original ownership. With these controls the whole positive comparison is
38 bodies / 1492 bytes and 22 genuine unmasked fields. Every regular positive
has its full own primary AUX extent and complete CFG. No external call or data
field is guessed or masked. No target byte arrays, assembly, fake returns,
inert padding or incomplete original game owner are used.

All 43 cold ordinary sections / 1903 bytes, including complete observer/ordinary
code and readonly layout, and 27 actual SDK headers are frozen. The whole
48-byte layout is `[1,2,4,20,20,20,8,8,8,8,8,8]`. Seventy canonical/body snapshots
preserve all prior protected unknowns and complete existing SDK/game bodies.
The full original R110 and R113 peer records at `0x00445530` / `0x00424500`
and their immutable manifests remain unchanged. Those peers are diagnostic
context and never replace the independent whole R035 parent or genuine new
source graph. The prior R170 manifest is pinned; no historical transition or
relaxed pending-ledger exception is needed for this cohort.

Full cold evidence preceded canonical acceptance. Strict R170 HEAD f68a5d0
readback checks exactly twelve function/origin transitions, unchanged extents,
all 880 original authored rows/order and all prior tracked configuration.
All previous evidence and source/header/build/ABI/mapping/match inputs stay
unchanged. Thirty-two new regression checks and all 1803 public checks pass,
with fresh scanning, full authored extents, local Ghidra attestation and
whitespace checks. Every protected getter, empty destruction child and
catch/lifetime/copy/math policy retains its independent unknown origin.

Totals are 3583 resolved (927 authored, 2081 library, 575 compiler), 768 pending
and 2656 excluded. Authored evidence stays 880 complete bodies / 1953711 bytes.
Exact stays 60 functions / 9883 bytes; provisional coverage remains
9883 / 1966054 (0.50%). The prior R139 cold 60/60 replay across eleven objects
remains applicable. No source/private ABI/mapping/exact credit is added.
Public MCP acceptance stays waived. The full remaining-origin goal is active
and unfinished. The next bounded R172 cohort is three complete front helpers
through these actual SDK graphs and independent full fighter/battle policies.

## R172 — complete front helpers with independent consumer widths

Three complete library front helpers / 96 bytes are accepted: `0x00454D50`,
`0x00454E10` and `0x004464C0`, each 32 bytes. Replay
`scripts/repo-python scripts/verify-replay-deque-front-origins.py` with immutable
`config/replay-deque-front-origin-evidence.json`. Each whole SDK front body calls
its actual begin and then iterator dereference, with both real fields unmasked:
byte `0x004143D0` / `0x00414950`, word `0x004145C0` / `0x00414A00`, and
dword `0x004147B0` / `0x00414AB0`. Full own primary AUX and complete CFG are
verified for every positive source definition.

Independent target context is preserved in three full authored policies:
R045 fighter controls `0x00452F10` / 2815, R109 recorded random selection
`0x00455580` / 139 and R065 battle sequence `0x00445A00` / 1958, totaling 4912
bytes. Their complete original records, instructions, CFG, switches and eight
actual front calls remain unchanged. Actual returned-pointer loads at
`0x00452FBB`, `0x004555B3` and `0x00445A4E` independently observe byte/word/
dword widths 1/2/4. The verifier checks actual decoded memory operand widths,
base EAX and zero index/displacement. This supplies new consumer evidence;
R171's scalar observations and mapped caller names alone are not inherited as
ownership proof. Original scalar declarations, signedness and private owner
layouts remain unknown; later signed use does not recover the original template
argument.

Compiler/source observation: natural SDK front definitions for three complete
scalar specializations close through the full accepted R171 iterator/endpoint/
comparison/step/dereference graph. A complete synthetic class derives naturally
from the byte deque and implements `first()` as `*begin()`. Its entire 32-byte
body is byte-equal with both genuine SDK call fields, so original method spelling
remains provisional. No incomplete original owner is instantiated. No target
arrays, assembly, fake returns, inert padding or guessed ABI are used.

All 42 entire SDK/ordinary controls / 1620 bytes compare unmasked with 30 real
fields through one coherent defining-symbol catalog. All 51 cold ordinary
sections / 2111 bytes and 27 actual SDK headers plus the pinned original R171
probe include are frozen. The whole 76-byte readonly layout is
`[1,2,4,20,20,20,8,8,8,8,8,8,1,2,4,20,20,20,20]`. All 38 prior R171 controls
retain their complete source/body/CFG/field identities. Seventy-six canonical/
body snapshots and fifteen original complete accepted records preserve earlier
SDK/game/peer evidence. The immutable R109 manifest retains its historical
unknown child snapshots; its existing verifier explicitly permits later
independent origin review while checking complete unchanged context. That
verifier passes without changes or new relaxed callbacks. All protected
getters, empty destruction children and catch/lifetime/copy/math owners stay
unknown.

Full cold evidence preceded canonical acceptance. Strict R171 HEAD 63339e6
readback checks exactly three function/origin transitions, all unchanged
extents, all 880 original authored rows/order and every prior tracked manifest/
configuration. Thirty new regression checks and all 1833 public checks pass,
with fresh scanning, full authored extents, local Ghidra attestation and
whitespace checks. All prior source/header/build/ABI/mapping/match inputs stay
unchanged.

Totals are 3586 resolved (927 authored, 2084 library, 575 compiler), 765 pending
and 2659 excluded. Authored evidence stays 880 complete bodies / 1953711 bytes.
Exact stays 60 functions / 9883 bytes; provisional coverage remains
9883 / 1966054 (0.50%). The earlier R139 cold 60/60 replay across eleven objects
remains applicable. No source/private ABI/mapping/exact credit is added. Public
MCP acceptance remains waived. The full remaining-origin goal is active and
unfinished; the next bounded R173 cohort is four complete iterator/index
candidates through the unchanged R019 bitmap-directory policies.

## R173 — complete texture-vector access and erase context

Seven complete library definitions / 235 bytes are accepted through the four
iterator/index roots and necessary full iterator dependencies. Replay
`scripts/repo-python scripts/verify-texture-vector-access-origins.py` with immutable
`config/texture-vector-access-origin-evidence.json`. The complete R019 bitmap
policies `0x0040B280` / 727 and `0x0040B560` / 575 retain all original authored
records, instructions, CFG and switch rows. Their 33 actual size/index/endpoint/
arithmetic/erase calls provide independent complete game value/argument context.
The earlier sprite label in the shortlist was corrected against the original
R019 bitmap-directory records; no origin depends on that temporary label.

| Address | Complete bytes | Inferred SDK role |
| --- | ---: | --- |
| `0x0040DCE0` | 31 | begin |
| `0x0040DD00` | 31 | end |
| `0x0040DD60` | 49 | unchecked index |
| `0x0040DFD0` | 45 | iterator addition |
| `0x0040E4A0` | 28 | mutable pointer iterator constructor |
| `0x0040E4C0` | 19 | mutable iterator dereference |
| `0x0040E4E0` | 32 | mutable iterator addition assignment |

Target observations independently agree on element width 44: the complete
32-byte iterator addition assignment multiplies the offset by `0x2C` at
`0x0040E4EA`, and whole 57-byte size calculation divides the pointer difference
by 44 at `0x0040DD48..0x0040DD4E`. The complete 99-byte erase, real copy and
range-destruction paths preserve that same width. Actual bitmap loading writes
and reads record fields and passes the real index/iterator/erase values; original
record declarations, packing, names and complete private owner layouts remain
unknown. A preliminary 16-byte diagnostic observer was corrected before any
manifest or canonical acceptance and supplies no evidence.

Compiler/source observation: a complete synthetic 44-byte record with an external
lifetime declaration closes the natural SDK vector access/size/erase/copy/
destruction graph. All 22 full SDK/compiler controls / 815 bytes retain 22 real
fields. Existing R032/R033 size/erase/copy/destruction/equality and R106 const
construction remain independent. The entire 44-byte scalar deleting thunk
`0x0040FA00` preserves compiler origin R037, its original full evidence row,
actual opaque destructor and independently reviewed scalar delete. This generated
function has no primary AUX; its entire unique defining code COMDAT is verified.
Every regular positive retains its own full primary AUX and complete CFG.
No source prefix, target array, assembly, fake return, inert padding, masked field
or private ABI misdeclaration is used.

Whole ordinary begin/end/index alternatives / 31,31,49 bytes are byte-equal with
all five actual fields. They preserve the ambiguity of short method bodies.
Library ownership is an inference from the newly complete actual index/stride/
size/erase/copy/destruction graph and whole independent bitmap policies, rather
than mapped names, caller labels or byte equality alone. Original method spelling
stays provisional. With these alternatives, all 25 full controls / 926 bytes
compare unmasked with 27 genuine fields through one coherent defining-symbol
catalog. All 35 cold ordinary sections / 1129 bytes, 27 actual SDK headers and
whole 24-byte layout `[44,16,4,4,16,1]` are frozen. Container/iterator observation
sizes do not recover a complete original game owner.

Fifty-five canonical/body snapshots and five original full pending/runtime/
compiler records preserve previous evidence. Only three exact R162 historical
accepted-pending to R173 accepted-library ledger transitions are added, with
both old source profiles cold-replayed. The immutable R162 manifest and all
R168/R169/R170 transitions remain intact. The original 158-byte assignment
`0x0040E000`, 16-byte const pointer getter `0x0040E9B0`, 15-byte destruction
wrapper `0x0040F9F0` and 19-byte custom lifetime policy `0x0040D8E0` remain
independently unknown, as do all earlier protected opaque owners. Successful
source reproduction of a low-level child grants no separate ownership.

Full cold evidence preceded canonical acceptance. Strict R172 HEAD cfb1d52
readback verifies exactly seven function/origin changes, unchanged extents,
all 880 original authored rows/order and every earlier tracked configuration.
Thirty-four new regression checks and all 1867 public checks pass, with fresh
scanning, complete authored extents, local Ghidra attestation and whitespace
checks. All prior source/header/build/ABI/mapping/match inputs stay unchanged.

Totals are 3593 resolved (927 authored, 2091 library, 575 compiler), 758 pending
and 2666 excluded. Authored evidence remains 880 complete bodies / 1953711 bytes.
Exact stays 60 functions / 9883 bytes with provisional coverage
9883 / 1966054 (0.50%); the earlier R139 cold 60/60 replay across eleven objects
remains applicable. No source/private ABI/mapping/exact credit is added. Public
MCP acceptance remains waived; the full remaining-origin goal is active and
unfinished. The next bounded R174 cohort is the secondary texture-vector index
and mutable dereference candidates through complete R017 resource policies and
independently accepted R161/R095/R034 SDK context.

## R174 — independent secondary texture-vector access

Two complete library definitions / 68 bytes are accepted: unchecked index
`0x0040DEE0` / 49 and mutable iterator dereference `0x0040E530` / 19. Replay
`scripts/repo-python scripts/verify-secondary-texture-access-origins.py` with
immutable `config/secondary-texture-access-origin-evidence.json`. The entire
R017 texture initialization `0x0040AD80` / 177 and resource release `0x0040AE40`
/ 434 preserve their original 611 bytes, authored records, instructions, CFG
and switch evidence. Their five actual index calls and returned-pointer slot
accesses supply independent game argument/value context. Unchanged R034
assignment `0x0040E210` / 96 and full R161 endpoint records remain independent.

Target observation: the actual 32-byte iterator addition assignment
`0x0040EA00` uses `LEA EAX,[ECX+EDX*4]` at `0x0040EA0F`. The full game policies
read and clear four-byte slots through actual index results. This independently
observed width is four, rather than an inherited width from another container.
The original slot type, method names and complete private owner layout remain
unknown. A query initially requested an interior address while locating the
const constructor; only the actual complete `0x0040F120` / 24 target extent
and genuine defining source supply evidence.

Compiler/source observation: a complete synthetic four-byte record closes eight
entire SDK definitions / 244 bytes with seven genuine fields. Actual index calls
the accepted R161 begin, R095 addition and the mutable dereference. Its const
getter and both complete iterator constructors are compared through their own
full primary AUX extents. Whole ordinary begin/index/dereference alternatives
/ 31,49,19 bytes are byte-equal with five fields. They preserve original method
spelling uncertainty. Library ownership is an inference from this complete
typed source graph and the independent entire game policies; neither caller
labels nor byte equality alone is sufficient.

All eleven whole controls / 343 bytes compare without masks using twelve actual
fields and one coherent defining-symbol catalog. All fifteen cold ordinary
sections / 414 bytes, 27 actual SDK headers and whole 24-byte readonly layout
`[4,16,4,4,16,4]` are frozen. Forty-three canonical/body snapshots and two whole
prior R161 records preserve previous evidence. The 16-byte const getter
`0x0040EA20` remains independently unknown, together with all previously protected
opaque getter, destruction, assignment, lifetime, math and catch policies.

Complete cold replay preceded acceptance. Strict R173 HEAD eed679a readback
permits exactly two function/origin changes with unchanged extents, preserves
all 880 original authored evidence rows/order and all earlier tracked
configuration. Thirty new regression checks and all 1897 public checks pass.
Fresh scanning, full authored extent validation, pinned target and local Ghidra
attestation, exact-input preservation and whitespace checks pass. No prior
source/header/build/ABI/mapping/match input changes require an exact replay.

Totals are 3595 resolved (927 authored, 2093 library, 575 compiler), 756 pending
and 2668 excluded. Authored evidence remains 880 complete bodies / 1953711 bytes.
Exact stays 60 functions / 9883 bytes with provisional coverage
9883 / 1966054 (0.50%); the prior R139 cold 60/60 replay across eleven objects
remains applicable. No source/private ABI/mapping/exact credit is added. Public
MCP acceptance remains waived. The full remaining-origin goal remains active
and unfinished. Original R108 full explicit/implicit alternatives already leave
0x00411C10, 0x004251C0 and 0x00449DE0 indistinguishable; they are not repeated
as new acceptance candidates. The next bounded R175 review examines three
resource-release parents, with genuine compiler-generated lifetime alternatives
required wherever ownership remains ambiguous.

## R175 — explicit resource-release policies and whole list cleanup graphs

Three complete authored release policies / 286 bytes and ten complete library
cleanup definitions / 644 bytes are accepted. Replay
`scripts/repo-python scripts/verify-resource-release-policy-origins.py` with
immutable `config/resource-release-policy-origin-evidence.json`. All candidate
extents, returns, internal branches, actual direct/indirect calls and registered
unwind state transitions are reconciled. Original R017 texture release / 434
and R045 fighter release / 588 retain their full 1022 bytes, authored records,
instructions, CFG and switch evidence. Three entire R037 scalar deleting
parents / 132 bytes and their original evidence remain compiler-owned.

| Address | Entire bytes | Origin and inferred role |
| --- | ---: | --- |
| `0x00412E50` | 83 | authored: SharedResource::ReleaseInterfaceAndTexturesAt00412E50 |
| `0x0041D1F0` | 98 | authored: ArchiveResource::CloseHandleAndClearEntriesAt0041D1F0 |
| `0x0052D020` | 105 | authored: CharacterResource::ClearEntriesAndReleaseBaseAt0052D020 |
| `0x0041D9F0` | 153 | library: std::list::clearAt0041D9F0 |
| `0x0041D930` | 19 | library: std::list::destructorAt0041D930 |
| `0x0041E280` | 100 | library: std::list::_TidyAt0041E280 |
| `0x0041E360` | 25 | library: std::list::allocator::destroyNodeAt0041E360 |
| `0x0041F130` | 25 | library: std::list::allocator::destroyNodePointerAt0041F130 |
| `0x00531CE0` | 153 | library: std::list::clearAt00531CE0 |
| `0x00531C40` | 19 | library: std::list::destructorAt00531C40 |
| `0x00532010` | 100 | library: std::list::_TidyAt00532010 |
| `0x005320F0` | 25 | library: std::list::allocator::destroyNodeAt005320F0 |
| `0x005322E0` | 25 | library: std::list::allocator::destroyNodePointerAt005322E0 |

Target observation: the 83-byte shared resource policy invokes the third
interface slot through the pointer at offset zero, then destroys the texture
subobject at +40. The 98-byte archive policy tests its handle, calls the actual
KERNEL32.dll CloseHandle import at `0x00657138`, explicitly clears its list at
+4 and then invokes member destruction. The 105-byte character policy writes
one observed vtable address, explicitly clears its list at +0xFEC, destroys
that member and calls the complete independently authored fighter base release.
Whole original R020 frames preserve complete cleanup tables and registration.
These explicit release/clear operations distinguish the bodies from a generated
sequence that only destroys members and bases. Original class declarations,
method spelling, private owner layouts and the selected virtual target remain
independent and unresolved where previously unresolved.

Compiler/source observation: complete natural archive and shared resource
destructors reproduce all 98 and 83 target bytes, including their genuine
exception registration fields, whole 21-byte cleanup/handler carriers and
36-byte unwind/FuncInfo carriers. Explicitly documented synthetic intervening
scalars test only the observed shared-resource +40 subobject spacing. Complete
compiler-generated alternatives are 22 bytes each and lack the explicit handle
close/list clear or interface release. They retain their entire unique defining
code COMDAT and actual missing primary AUX metadata, rather than receiving an
invented function size or a sliced source prefix.

The character policy is accepted from its whole target CFG and actual explicit
clear-before-member/base destruction. A complete small synthetic base tests
source call order without reproducing the +0xFEC original layout. Its complete
explicit 99-byte and implicit 75-byte destructors show the additional clear call
and subsequent automatic member/base destruction. Neither control is a positive
byte match for the 105-byte target; no authored source-match credit is claimed.
The exact source profile is a reproducibility setting, not an executable-wide
compiler inference.

The two complete SDK list cleanup graphs use independent existing R169/R170
108-/16-byte value-node contexts. Full clear, tidy, list destructor and node/
node-pointer allocator destruction definitions compare with their actual
entire children and real fields. Both whole ordinary 19-byte tidy wrappers are
byte-equal. Library ownership is an inference from the closed typed graph and
whole explicit game policies; short method spelling remains provisional.
Eight-/eleven-byte node-link getters and five-byte destruction children stay
unknown. All other protected opaque ownership stays unchanged.

All 28 entire positive custom/SDK/ordinary/EH/data controls / 1085 bytes compare
unmasked with 56 genuine fields through one coherent defining-symbol catalog.
All 52 cold ordinary sections / 1858 bytes, 28 actual SDK headers and whole
44-byte readonly layout `[108,16,12,12,16,16,44,44,4,16,16]` are frozen.
Four whole compiler/source alternatives preserve 218 bytes of explicit/implicit
emission. Sixty-eight canonical/body snapshots, five full previous node/deleting
records and three whole original registered frames preserve historical evidence.
Only one observed four-byte virtual slot is frozen; no whole vtable extent or
complete original owner is inferred. The actual PE import directory is read back.

Cold full-source replay preceded canonical acceptance. Strict R174 HEAD 4f6a698
readback permits exactly thirteen function/origin changes with unchanged extents
and exactly three new full authored records. All 880 original authored rows/order
and earlier tracked configurations remain unchanged. Thirty-five new guards and
all 1932 public checks pass, together with full authored extent validation, fresh
scanning, pinned target/local Ghidra attestation and whitespace checks. All prior
source/header/build/ABI/mapping/match inputs remain unchanged; no exact replay
is required for this origin-only addition.

Totals are 3608 resolved (930 authored, 2103 library, 575 compiler), 743 pending
and 2678 excluded. Authored evidence is 883 whole bodies / 1953997 bytes.
Exact stays 60 functions / 9883 bytes, with provisional coverage
9883 / 1966340 (0.50%). The earlier R139 cold 60/60 exact replay across eleven
objects remains applicable. No reconstructed source/private ABI/mapping/exact
credit is added. Public MCP acceptance remains waived; the complete-origin
goal remains active and unfinished. The next bounded R176 diagnostic cohort
is four iterator arithmetic wrappers through independent whole R078/R083 SDK
parent/child evidence; derive each actual type-width/argument flow independently.

## R176 — whole deque retreat graphs and real addition destinations

Four complete library iterator subtraction-assignment definitions / 108 bytes
are accepted: `0x0041F650`, `0x0041F6F0`, `0x00455D10` and `0x005F9530`, each
27 bytes. Replay `scripts/repo-python scripts/verify-deque-retreat-origins.py`
with immutable `config/deque-retreat-origin-evidence.json`. Whole accepted
R078 addition/subtraction-shaped callers and R083 addition-assignment bodies
retain their original records, extents, canonical names and ownership.

Target observation: every wrapper negates the incoming signed offset at +10
and calls its entire 31-byte addition-assignment child at +16. Each 57-byte
subtraction caller passes the incoming offset to that wrapper. The separate
real addition caller instead calls the 31-byte child directly. These complete
routes distinguish actual subtraction from the historical addition-shaped
association, even though the 57-byte wrapper shapes are otherwise identical.
Earlier source evidence remains unchanged and historical names remain provisional.
No element access or scaled pointer arithmetic occurs here; original element
width/type and full private container declarations remain unknown.

Compiler/source observation: four complete natural SDK iterator graphs use
synthetic value widths 1,2,4,64. Every corresponding subtraction assignment,
addition assignment, subtraction and genuine addition body has the same
emission across widths. Four complete ordinary derived-iterator retreat methods
/ 27 bytes are also byte-equal. Library ownership is an inference from the
closed typed SDK graph and twelve entire independently accepted parent/child
records, rather than short method shape or caller labels alone. The ordinary
alternatives preserve original method spelling uncertainty.

All twenty entire SDK/ordinary controls / 796 bytes compare unmasked through
one coherent defining-symbol catalog with sixteen genuine fields. Four whole
57-byte real-addition negatives retain their genuine addition-assignment call
destinations; comparison against the subtraction parents differs inside those
actual fields. No field is masked, substituted to the subtraction child, or
omitted. Every positive and negative retains its own complete primary AUX
extent. All 33 cold ordinary sections / 1152 bytes, 27 actual SDK headers and
whole 48-byte layout `[1,2,4,64,8,8,8,8,8,8,8,8]` are frozen. Iterator sizeof 8
is a source observation, not a claim about a complete original owner.

Eighty-four canonical/body snapshots, twelve original full R078/R083 records,
old probe source and entire earlier evidence files remain unchanged. All 37
previously protected opaque lifetime, assignment, math, catch, getter and
destruction owners stay unknown. Earlier R078/R083 proofs cold-replay and the
new whole source proof cold-builds before canonical acceptance.

Strict R175 HEAD f107bcd readback permits exactly four function/origin changes,
unchanged extents, all 883 prior authored rows/order and every earlier tracked
configuration. Twenty-eight new regression guards and all 1960 public checks
pass, together with full authored extent validation, fresh scanning, pinned
target/local Ghidra attestation and whitespace checks. All prior source/header/
build/ABI/mapping/match inputs are unchanged; no exact replay is required.

Totals are 3612 resolved (930 authored, 2107 library, 575 compiler), 739 pending
and 2682 excluded. Authored evidence remains 883 whole bodies / 1953997 bytes.
Exact remains 60 functions / 9883 bytes, with provisional coverage
9883 / 1966340 (0.50%). The earlier R139 cold 60/60 exact replay across eleven
objects remains applicable. No reconstructed source/private ABI/mapping/exact
credit is added. Public MCP acceptance stays waived; the full remaining-origin
goal is active and unfinished. The next bounded R177 diagnostic cohort is
three static resource parent bodies and their direct release helper, preserving
whole original R024/R073/R077 and R017/R166 evidence without granting ownership
from those labels.

## R177 — explicit static resource policies and owned vector cleanup

Eight complete bodies / 701 bytes are accepted: four authored policies / 595
bytes and four library dependencies / 106 bytes. Replay
`scripts/repo-python scripts/verify-static-resource-policy-origins.py` with
immutable `config/static-resource-policy-origin-evidence.json`.

| Address | Complete bytes | Inferred ownership and policy |
| --- | ---: | --- |
| `0x00413650` | 132 | authored: initialize the handle after four deque constructions |
| `0x004136E0` | 161 | authored: clear four queues, guard CloseHandle, zero the handle, then destroy members |
| `0x00413880` | 67 | authored: explicit ascending-order clear of the four queues |
| `0x005F6FF0` | 235 | authored: release queue entries, delete nonnull vector entries and clear the vector before automatic member cleanup |
| `0x005F8380` | 49 | library: pointer-vector unchecked index |
| `0x005F8320` | 19 | library: pointer-vector destructor |
| `0x005F83E0` | 19 | library: pointer-vector clear |
| `0x005F8EA0` | 19 | library: mutable pointer-iterator dereference |

Target observation: the 132-byte constructor constructs deque members at
+0x154, +0x168, +0x17C and +0x190, then explicitly writes zero to the handle at
+0. The 161-byte destructor first calls the entire 67-byte helper, tests that
handle, calls actual KERNEL32.dll CloseHandle through IAT slot `0x00657138`,
and zeros the handle inside the nonzero branch. Automatic deque destruction
then visits +0x190, +0x17C, +0x168 and +0x154. The helper visits those members in
ascending construction order and performs four clear calls. Historical R077
source-shape destructor labels remain unchanged; labels do not establish the
meaning of these explicit clear operations. Whole R024 initializer/finalizer
registrations independently retain the same static object at `0x00671750`.

The whole 235-byte policy starts with authored R166 `0x005F7140` / 162, then
iterates the vector at +0x78 with unsigned indices. Each nonnull pointer slot
is deleted through complete R037 `0x005F7EA0` / 44 with flags 1. Explicit vector
clear precedes automatic vector destruction, R017 texture release and the
whole compiler array-destruction helper for two 20-byte deque members.
The static finalizer independently binds global `0x006716C8`. Complete vector
size and iterator-add bodies establish four-byte pointer slots; that width is
also independently observed in this policy's actual pointer loads.

Source/compiler observation: complete small synthetic owners distinguish
explicit defaults, ascending queue clear, guarded handle release and explicit
owned-pointer deletion from automatic construction/destruction. They preserve
natural member ordering under both /GX and the otherwise identical profile
without /GX. Nine whole operation-order controls total 988 bytes. These are
source-operation observations, not byte-positive comparisons of the four game
roots. Their layouts differ from the unrecovered original layouts. In
particular, the synthetic pointer-owner destructor is also 235 bytes, but its
vector offset is 44 rather than the target's 120; equal size earns no match.
No padding, incomplete original owner, invented ABI or target-byte source is
used. The two 55-byte no-EH queue controls still have different forward-clear
and reverse-destruction call orders. The actual whole constructor/destructor
establish the original member order independently.

Twenty-two complete SDK/compiler/ordinary controls / 724 bytes compare
unmasked with 23 genuine fields through one defining-symbol catalog. Four
ordinary index/begin/dereference/cleanup alternatives / 118 bytes are byte-equal;
original method names remain provisional. Ownership is inferred from the
whole typed vector graph and independent explicit game policy. The 16-byte
const getter `0x005F9640` and separate 72-byte pointed-owner destructor
`0x005F7ED0` remain unknown. The five-byte scalar destruction child
`0x005FA700` retains its previously accepted R087 library evidence.

All 112 primary ordinary sections / 4968 bytes, 96 secondary sections / 3879
bytes, 28 actual SDK headers in each build and the complete 48-byte readonly
layout are frozen. The verifier retains 121 full canonical/body snapshots,
39 protected unknown bodies, five complete prior compiler/deleting records,
three entire registered R020 EH frames and two authored anchors / 596 bytes.
Earlier immutable manifests and all prior authored rows/order are preserved.
Both source profiles cold-build serially. Evidence-only replay passes before
canonical mutation; accepted-state cold replay, old static evidence, full
authored validation, target/tracking, fresh scanning and local Ghidra attestation
pass afterwards. Strict R176 HEAD f81d4f2 readback permits only eight function/
origin changes and four complete new authored records. Thirty-seven new
regression guards and all 1997 public checks pass; progress and whitespace
checks pass. All sixty source/header/build/ABI/mapping/match inputs remain
unchanged from R139 db26a05, so its earlier cold 60/60 replay across eleven
objects remains applicable.

Totals are 3620 resolved (934 authored, 2111 library, 575 compiler), 731 pending
and 2686 excluded. Authored evidence totals 887 whole bodies / 1954592 bytes.
Exact remains 60 functions / 9883 bytes, with provisional coverage
9883 / 1966935 (0.50%). No reconstruction source/private ABI/mapping/exact
credit is added. Public MCP acceptance remains waived. The full remaining-origin
goal remains active and unfinished. Continue with fresh whole lifetime-policy
candidates; a compiler parent alone grants no ownership.

## R178 — remaining explicit construction and raster lifetime policies

Two entire authored policies / 271 bytes are accepted: `0x005F6F60` / 142 and
`0x0041BFD0` / 129. Replay
`scripts/repo-python scripts/verify-remaining-lifetime-policy-origins.py` with
immutable `config/remaining-lifetime-policy-origin-evidence.json`.

Target observation: the constructor first invokes the full 98-byte array
construction helper for two 20-byte deque members, the R017 texture constructor
at +0x28 and R090 vector constructor at +0x78. After all members are constructed,
it explicitly clears the two queues in ascending order and clears the vector.
The historical R077 deque destructor-shaped aliases are preserved; the actual
post-construction operation and complete source controls distinguish explicit
clear from automatic construction. Whole R024 registration binds the same
static object `0x006716C8` as the accepted R177 destructor. The entire original
three-state R020 frame `0x00656629` and all cleanup registrations are retained.

The 129-byte raster lifetime policy guards storage at +0x14, performs scalar
delete and zeros that slot. It restores the selected GDI object through actual
SelectObject, passes the returned object to DeleteObject, releases the DC through
ReleaseDC, then resets fields +8, +12 and +4. All actual import slots are read
back from the PE directory. The complete R037 deleting parent retains flags-1
allocation cleanup; that parent alone supplies no authored evidence. R109's
entire 119-byte independent raster release policy is preserved as context,
including its own two resets rather than this candidate's three. Original
owner identity, field meanings and complete game layout remain unknown.

Compiler/source observation: seven full natural small-owner controls / 457
bytes distinguish explicit constructor clears and raster cleanup from automatic
construction/cleanup. Source constructors are 142/108 bytes; raster explicit
cleanup is 129 bytes and the implicit raw-member observation has no cleanup
operations. These controls grant no target-source positive or reconstruction
credit. The 142-byte synthetic constructor has vector offset 44 rather than
120. The full 129-byte raster source comparison binds all four genuine fields
without masking and differs at offsets 14,23,44 because its storage offset is
16 rather than 20. No unused field or arbitrary padding is added to hide these
differences. Original layouts are not instantiated.

The third candidate `0x004170B0` / 27 remains unknown. Its entire interface
Release through virtual slot +8 is byte-equal to both a complete explicit
interface destructor and an ordinary smart-owner destructor. Both full primary
AUX extents / 54 bytes compare without fields to exclude. A complete generated
19-byte member-owner destructor supplies additional operation context. These
observations preserve game-versus-library ownership uncertainty; the deleting
parent and Release shape alone do not classify the owner.

All 119 ordinary source sections / 5446 bytes, 28 actual SDK headers and the
whole 48-byte readonly layout are frozen. The verifier retains 133 complete
canonical/body snapshots, 40 protected unknowns, three whole authored anchors
/ 531 bytes, five original compiler/policy records and the original full EH
frame. Previous R177 evidence cold-replays unchanged. New evidence-only cold
replay precedes canonical mutation; accepted-state cold replay, full authored
validation, target/tracking, fresh scanning and local Ghidra attestation pass.
Strict R177 HEAD 09fccb7 readback permits only two function/origin changes and
two full new authored records, preserving all 887 prior rows/order and every
previous configuration. Thirty-four new regression guards and all 2031 public
checks pass; progress/whitespace checks pass. The exact-input preservation
check confirms that the earlier R139 cold 60/60 replay remains applicable.

Totals are 3622 resolved (936 authored, 2111 library, 575 compiler), 729 pending
and 2686 excluded. Authored evidence totals 889 bodies / 1954863 bytes. Exact
remains 60 functions / 9883 bytes with provisional coverage
9883 / 1967206 (0.50%). No reconstructed source/private ABI/mapping/exact credit
is added. Public MCP acceptance remains waived; the full remaining-origin goal
is active and unfinished. Continue with fresh whole resource-operation context.

## R179 — music catalog transformation and readable-file registration

Two complete authored policies / 431 bytes are accepted: `0x00427300` / 298 and
`0x0041D6C0` / 133. Replay
`scripts/repo-python scripts/verify-file-resource-policy-origins.py` with
immutable `config/file-resource-policy-origin-evidence.json`.

Target observation: the first policy opens literal `musicroom.csv`, obtains
its size, allocates byte storage, reads and closes the input. It creates
`musicroom.dat`, transforms each byte with an evolving XOR mask initialized to
0x5C and step 0x5A, adds that step to the mask and increments the step by 0x3D,
then writes and closes the output. Both file-open failure branches, the entire
unsigned loop and final array deletion are retained. The independent whole
R066 game catalog loader / 916 bytes reads its own `musicroom.dat` literal at
`0x00657C80` and uses the same mask/step/increment before parsing game records.
This is game resource policy evidence, rather than ownership inferred from
file APIs or a short XOR shape alone. Names remain inferred.

The second policy checks whether the supplied file can be opened, records its
size, copies its name, closes the handle and appends the full record to the
archive list at owner +4. Complete R169 source evidence establishes value/node
widths 108/116. The record pointer passed from stack -0x78 includes the filename
region, size at record +100 and zero-initialized field at +104; these are copied
data, not inert locals. The full original R053 archive registration / 245 and
R052 archive index reader / 429 provide independent project ownership context.
The list insertion, array allocation/deallocation, strcpy and security-cookie
helper retain their separate accepted library origins. Every real import slot
is verified against the PE directory.

Compiler/source observation: complete natural small-owner methods emit 298 and
130 bytes / 428 total. These are operation controls, not target-byte positives.
The whole 298-byte music source negative binds all eleven genuine code/data
fields and retains 33 differences; equal length does not earn a match. Complete
14-byte CSV/DAT source strings compare independently and their exact fields
bind to the two actual target string locations. The 133-byte registration
extent is never truncated to the 130-byte source control. Its complete source
record includes both metadata fields, with sizeof 108 and list sizeof 12 as
source observations. Original full owner layout, original record spelling and
meaning of the zero-initialized field remain unknown; no padding or incomplete
original owner is introduced.

All 86 ordinary source sections / 4266 bytes, 28 actual SDK headers and the whole
16-byte readonly layout are frozen. Both entire methods retain their own full
primary AUX extent. The verifier preserves 143 complete canonical/body
snapshots, 40 protected unknowns, three whole authored anchors / 1590 bytes with
all original guarded switch records, and four full R169 archive/list records.
The earlier R169 80-control / 3752-byte closed source graph with 189 genuine
fields cold-replays unchanged. Evidence-only cold replay precedes canonical
mutation; accepted-state cold replay, complete authored validation, target/
tracking, fresh scanning and local Ghidra attestation pass. Strict R178 HEAD
9f31228 readback permits exactly two function/origin changes and two complete
new authored records, preserving all 889 prior rows/order and every earlier
configuration. Thirty-seven new regression guards and all 2068 public checks
pass; progress and whitespace checks pass. All exact inputs remain unchanged,
so the earlier R139 cold 60/60 replay across eleven objects remains applicable.

Totals are 3624 resolved (938 authored, 2111 library, 575 compiler), 727 pending
and 2686 excluded. Authored evidence totals 891 whole bodies / 1955294 bytes.
Exact remains 60 functions / 9883 bytes with provisional coverage
9883 / 1967637 (0.50%). No reconstructed source/private ABI/mapping/exact credit
is added. Public MCP acceptance remains waived; the full remaining-origin goal
is active and unfinished. The next bounded cohort investigates two directional
binding copies, explicit queue cleanup and archive construction defaults.

## R180 — directional indexed copies and explicit owner policies

Four entire authored policies / 343 bytes are accepted. Replay
`scripts/repo-python scripts/verify-indexed-owner-policy-origins.py` with
immutable `config/indexed-owner-policy-origin-evidence.json`.

| Address | Complete bytes | Inferred operation |
| --- | ---: | --- |
| `0x00416E20` | 84 | store working eight bytes into the selected nested record |
| `0x00416E80` | 85 | load selected nested eight bytes into working storage |
| `0x004204D0` | 84 | explicitly clear the member queue before automatic destruction |
| `0x0041D190` | 90 | initialize the scalar state and clear the constructed archive list |

Target observation: both copies preserve signed byte selectors at owner
+0x16AC4/+0x16AC5 and the incoming signed byte index. The actual bank/category
strides are 0x17F0/0x5FC, the record stride is sixteen and payload base is +0x55C.
Working storage is +0x16A94. Both call the complete R025 memcpy / 829 with length
eight, in opposite directions. Complete R052 replay initializer / 315 and R040
name-entry update / 541 independently supply game context. Original field
meaning and complete owner layout remain unknown; the provisional binding
shortlist title does not recover an input-binding type.

The queue policy at +0x7D0 first performs an explicit clear and then automatic
member destruction. Both complete 19-byte SDK callees share the same entire
177-byte _Tidy; their historical R077 destructor-shaped aliases are unchanged.
Complete natural clear/destruction controls distinguish two explicit/automatic
calls from one automatic call. The whole R045 fighter release / 588 is preserved.
The archive constructor first constructs the list at +4, explicitly sets the
scalar at +0 to zero and calls the entire R175 list clear / 153. Whole R053
archive registration / 245 and the original one-state EH frames independently
preserve owner context. Constructor dependency ownership is not borrowed.

Compiler/source observation: six complete small-owner controls / 268 bytes
observe copy direction, explicit queue clear and explicit archive defaults,
with full generated alternatives. They grant no target-byte positive. The
queue source owner has no original +0x7D0 layout; source queue value width four
is not an original element-type claim. The synthetic archive constructor is
also 90 bytes, but equal length earns no match. Complete source record/list
widths 108/12 and owner sizeof 16 are source observations, not complete original
owner declarations. No padding, incomplete original owner or target byte source
is introduced.

Four separate construction dependencies remain unknown: `0x0041D8F0` / 56,
`0x0041E330` / 14, `0x0041E2F0` / 53 and `0x0041E1A0` / 143. The last provisional
span ends in an external jump at `0x0041E22D` to `0x0041E264`. Its cold source
section is 223 bytes, including local exception cleanup and the shared tail.
The separate `Catch@0041e22f` ledger span / 80 includes subsequent owner code;
its own extent also needs reconciliation. These are pending context observations,
not accepted prefixes or truncated comparisons.

All 61 ordinary source sections / 2497 bytes, 29 actual SDK headers and the
whole 40-byte readonly layout are frozen. Every explicit source body retains
its own full primary AUX extent; generated alternatives retain their unique
whole defining COMDAT. The verifier preserves 157 full canonical/body snapshots,
40 protected unknowns, four whole authored anchors / 1689 bytes with all original
switch records, three entire R025/R175 library records and two original full
R020 EH frames. The unchanged R025 runtime proof passes all three entire vendor
bodies / 1762 bytes with 93 genuine local fields. New evidence-only cold replay
precedes canonical mutation; accepted-state cold replay, full authored checks,
local Ghidra attestation, target/tracking and fresh scanning pass. Strict R179
HEAD 0f62552 readback permits exactly four function/origin changes and four full
new authored records, preserving all 891 prior rows/order and every earlier
configuration. Thirty-eight new regression guards and all 2106 public checks
pass; progress/whitespace checks pass. All sixty exact inputs remain unchanged,
so the earlier R139 cold 60/60 replay across eleven objects remains applicable.

Totals are 3628 resolved (942 authored, 2111 library, 575 compiler), 723 pending
and 2686 excluded. Authored evidence totals 895 whole bodies / 1955637 bytes.
Exact remains 60 functions / 9883 bytes with provisional coverage
9883 / 1967980 (0.50%). No reconstructed source/private ABI/mapping/exact credit
is added. Public MCP acceptance remains waived; the full remaining-origin goal
is active and unfinished. Next reconcile the whole default-list construction
graph, local exception entry and shared tail before assigning any new ownership.

## R181 — complete list construction and source-owned shared exception entry

Four library entries are accepted through cold
`scripts/repo-python scripts/verify-list-construction-origins.py` and immutable
`config/list-construction-origin-evidence.json`.

| Address | Complete ledger bytes | Inferred source owner |
| --- | ---: | --- |
| `0x0041D8F0` | 56 | default list constructor |
| `0x0041E2F0` | 53 | list value-base constructor |
| `0x0041E1A0` | 223, reconciled from 143 | complete default-node allocation, local catch and shared owner exit |
| `0x0041E22F` | 80 | source-local catch entry including shared owner exit |

The four ledger extents total 412 bytes, including 80 overlapping bytes.
Distinct primary code totals 332 bytes. No distinct-byte or exact-reconstruction
credit is inferred from the overlap. Target observation: the old node prefix
ends with JMP at `0x0041E22D` to the owner exit `0x0041E264`. Its complete defining
source function owns 223 bytes through `0x0041E27E`, with the local entry at
+143 and shared exit at +196. The source-local entry has a unique static typed
COFF definition and is named by the actual complete handler table. Full parent
primary AUX/COMDAT metadata, all 223 bytes, both branches and return reconcile
the owner; the entire 80-byte entry view is supported through that owner. No
standalone callback primary AUX or convenient prefix is claimed.

Compiler/source observation: the pinned SDK list header defines the allocation,
link construction, catch cleanup, deallocation and rethrow policy. The original
R020 frame at `0x00655470` registers owner `0x0041E1A0`; the complete 80-byte
readonly EH carrier starts at `0x006685F8`, with FuncInfo at `0x0066862C` and
try map at `0x00668618`. Its actual catch-all handler table points to
`0x0041E22F`. The generated ten-byte handler has its own unique complete COMDAT
and retains its observed static definition without inventing primary AUX.
Full data/code linkage and every genuine field are replayed without masking.
The library inference belongs to the SDK source-defined catch policy;
compiler exception-entry ABI alone would not establish that ownership.

Independent game observations retain the complete R180 archive constructor
/ 90 and R179 file-record append / 133, all prior rows and switch evidence.
The latter's 108-byte record copy and original R169 node-allocation records
supply width context; source value/node widths 108/116 do not identify original
field names or complete game owner layout. The SDK empty allocator constructor
and distinct ordinary empty-class constructor both emit the same entire
14 bytes at `0x0041E330`; this entry remains unknown. Original eight-/eleven-byte
node-link helpers and five-byte no-op destruction also remain unknown.

Evidence-only cold replay precedes canonical mutation; accepted-state cold
replay matches 22 full SDK/code/EH/data/ordinary controls / 795 bytes and all
35 genuine fields. All 65 ordinary sections / 2690 bytes, 29 SDK headers plus
the pinned prior probe include, and the entire coalesced 52-byte readonly layout
are frozen. The verifier preserves 168 canonical/body snapshots, 41 protected
unknowns, two full authored anchors / 223 bytes, four complete R169 records
and the original R020 frame. The old R180 manifest stays byte-for-byte immutable;
its verifier permits only the three exact original-to-R181 row transitions,
including the sole 143-to-223 extent correction. All old 143-byte observations,
external jump and pending source controls remain replayed as historical context,
without prefix acceptance. R180 cold replay passes before and after acceptance.

Strict R180 HEAD 7ab03b1 readback permits exactly four function/origin changes,
only the complete node size/span correction, and no authored additions. All
895 prior authored rows/order and previous configuration evidence are preserved.
Local target/Ghidra preflight, tracking, full authored verification, fresh scan,
44 new regression guards and all 2150 public checks pass. Generated progress
and whitespace checks pass. All sixty exact inputs remain unchanged, retaining
the prior R139 60/60 cold replay across eleven objects. No source/private ABI,
mapping, reconstructed owner layout or exact credit is added.

Totals are 3632 resolved (942 authored, 2115 library, 575 compiler), 719 pending
and 2690 excluded. Authored evidence remains 895 whole bodies / 1955637 bytes.
Exact remains 60 functions / 9883 bytes, with provisional authored denominator
1967980 (0.50%). Public MCP acceptance remains waived; the whole remaining-origin
goal is active and unfinished. Next investigate the complete shared math-table
operations and indexed counter policy with independent game parents.

## R182 — shared math-table policies and signed indexed word counter

Five complete authored policies / 326 bytes are accepted. Replay
`scripts/repo-python scripts/verify-math-table-policy-origins.py` with immutable
`config/math-table-policy-origin-evidence.json`.

| Address | Complete bytes | Inferred operation |
| --- | ---: | --- |
| `0x0041CAE0` | 82 | build the used 3600-entry cosine table |
| `0x0041CB40` | 43 | absolute converted index modulo 3600 into that table |
| `0x0041CB70` | 49 | same table with the actual 900.0f phase subtraction |
| `0x0041CBB0` | 73 | zero-divisor guard, phase lookup and ratio against the ordinary lookup |
| `0x00454D00` | 79 | increment the selected native word counter using signed bank/index selectors |

Target observation: the build iterates indices 0 through 3599, computes
index / 10.0 * 3.1415926535 / 180.0, calls the actual R128 `_cos` C entry and
stores floats at `0x006884C0` with stride four. The two lookups multiply by
10.0f, retain the distinct phase subtraction, call complete R006 `__ftol2`
and the still-unknown 11-byte integer absolute-value helper, then use remainder
3600. The ratio retains the actual x87 equality/zero branch, one phase call
and two ordinary lookup calls. This shared explicit table policy, whole startup
R113 application parent / 2987 and whole R048 character consumer / 43845
support the authored inference. A CRT callee or game caller alone is not used
as ownership proof. All original parent switch records and complete CFG remain
frozen; selected witnesses preserve the actual call sites.

The counter retains signed byte bank/index loads, native bank stride 0x17F0,
word load/add/store with index stride two and counter base +0x394. Actual whole
R109 resource-selection parent / 215 sets ECX to `0x006718F8` before the call.
Whole R052 replay initialization / 315 and immutable R180 indexed-copy evidence
supply independent context. Original field meanings, word signedness and
complete game owner layout remain provisional. The complete small observer
uses two three-word banks and sizeof 14; its entire increment / 67 and caller
/ 17 are operation controls, not an original owner declaration or a target-byte
match. The target's 79-byte body is never shortened to the source model.

Compiler/source observation: three whole natural table functions / 174 bytes
match byte-for-byte with every actual field. The full 73-byte ratio control is
a negative: six bytes at offsets 48–53 differ because the live float store and
argument-stack cleanup exchange instruction order. Both complete bodies retain
the same explicit operations and CFG. All five ratio fields are compared
unmasked; equal length or semantic behavior earns no exact credit. No padding,
inert local, fake return, assembly, conditional source body or invented ABI is
introduced. Ten whole code/constant controls / 283 bytes freeze all 19 genuine
fields; the three positives are not generalized into a four-function match.

The source table is an external complete array declaration. Its 14400-byte
used range fits the loaded virtual `.data` extent, including zero-filled bytes
beyond file-backed data. The verifier reads PE virtual sizes for this writable,
non-executable range, rather than assuming a file-backed span. This is a used
range claim, not the whole original allocation or a runtime-content hash.
All six complete readonly float/double constants / 36 bytes are independently
verified. The complete R128 cosine primary / 174 and its original nine-byte C
entry record, R006 conversion / 117 and R129 abs diagnostic / 11 stay unchanged.
R129 replays before and after acceptance, including vendor abs/labs and cold
ordinary alternatives that preserve the integer helper's unknown ownership.

All 13 cold ordinary sections / 383 bytes, two actual SDK headers and whole
16-byte readonly layout are frozen. Evidence-only cold replay precedes canonical
mutation; accepted-state cold replay passes. The verifier retains 179 complete
canonical/body snapshots, 41 protected unknowns, four entire authored parents
/ 47362 bytes and four original runtime/interior/opaque records. Strict R181
HEAD bf663e0 readback changes exactly five function/origin rows, preserves
all extents and appends five complete authored records while retaining all
895 prior rows/header/order. Full authored verification now covers 900 bodies
/ 1955963 bytes. Local target/tracking/Ghidra query completion, fresh scanning,
47 new regression guards and all 2197 public checks pass; generated progress
and whitespace checks pass. Every prior configuration manifest/record and all
sixty exact inputs are preserved. No source/private ABI/mapping/exact credit
is added; prior R139 cold 60/60 replay across eleven objects remains applicable.

Totals are 3637 resolved (947 authored, 2115 library, 575 compiler), 714 pending
and 2690 excluded. Exact remains 60 functions / 9883 bytes, with provisional
coverage 9883 / 1968306 (0.50%). Public MCP acceptance remains waived; the whole
remaining-origin goal is active and unfinished. Next investigate the complete
font byte-decoding/classification and graphic-resource initialization cohort.

## R183 — complete font byte policy and explicit resource defaults

Two complete authored policies / 149 bytes are accepted through cold
`scripts/repo-python scripts/verify-font-byte-policy-origins.py` and immutable
`config/font-byte-policy-origin-evidence.json`. The 85-byte entry at
`0x0041C9D0` decodes a packed text unit; the 64-byte entry at `0x0041BF90`
stores the incoming window value and explicitly clears resource state.
The 77-byte fixed-range classifier at `0x0041CA30` remains unknown.

Target observation: the double-byte route performs two DWORD loads, masks
0xFF/0xFF00, shifts and combines the first two bytes, writes a full integer
output and returns two. The fallback sign-extends one byte and returns one.
Complete R052 rasterizer / 1766 uses this result to advance text, distinguish
backslash control sequences, parse game formatting through the existing hex
helper and render either pixel-width path. All three original decoder calls,
backslash comparison and full original parent CFG are frozen. These explicit
operations and independent font/texture/music-room game context support the
outer authored inference; callee ownership is kept separate.

The initializer preserves the incoming value at +0 and zero stores at
+4/+8/+0xC/+0x14. The complete R052 texture parent / 398 allocates 0x38 bytes,
passes zero to the constructor and uses the resulting owner in the original
rasterizer. Full R040 music-room text parent / 555 independently calls the same
initializer. Complete R178 release / 129 and R109 release / 119 preserve the
actual guarded storage delete, GDI selection/deletion and DC release, including
three original PE imports. A 56-byte allocation and partial field interface do
not recover the full original owner or license instantiating it.

Compiler/source observation: the natural char-input decoder emits 74 bytes,
against all 85 original bytes. Its one real classifier-call field is linked
unmasked; 44 positions in the shorter source span differ and the original has
11 additional bytes. Both complete CFGs are checked separately. No target prefix
or memory-read equivalence is claimed: the original DWORD reads remain distinct
from the model's byte loads. The complete small resource owner has five live
fields and sizeof 20. Its 64-byte constructor has one difference at offset 50:
source storage offset 0x10 versus original 0x14. Equal length is not a match;
no arbitrary field/padding is added to remove the difference. Generated default
POD construction is retained as a full 25-byte caller with no explicit field
initialization, independently of the explicit constructor/caller controls.

The full 77-byte member classifier and distinct ordinary member classifier are
byte-equal to the original helper. Both implement the actual unsigned ranges
0x81–0x9F and 0xE0–0xFE; their equality does not distinguish ownership or recover
original class/type/charset identity. A complete 25-byte pinned SDK `_ismbblead`
macro observer retains its genuine DIR32 `_mbctype` table field with addend one.
It is source context only, with no invented original table binding. This
negative SDK shape does not prove the other helper is custom authored. The
classifier's original canonical rows remain unchanged and unknown.

Four complete source comparisons / 292 bytes preserve both whole negatives
and two equal opaque-classifier alternatives. Five complete SDK/implicit/caller
controls / 196 bytes retain their own primary AUX extents. All 14 cold ordinary
code/EH/data sections / 588 bytes, ten actual SDK headers and the entire 24-byte
readonly layout are frozen. The verifier preserves 187 complete canonical/body
snapshots, 42 protected unknowns, five entire authored game/release anchors
/ 2967 bytes, two full R178/R109 release records and two original R020 frames.
R178 cold replay passes before and after acceptance; all earlier manifests stay
immutable. Evidence-only cold replay precedes canonical mutation; accepted-state
cold replay passes. No root target-byte-positive claim is made.

Strict R182 HEAD b2c365e readback changes exactly two function/origin rows and
adds two full authored records, preserving every original extent, all 900 prior
rows/header/order and all earlier configuration evidence. Full authored checks
now cover 902 bodies / 1956112 bytes. Local target/tracking/Ghidra attestation
and both query completion markers, fresh scanning, 46 new regression guards
and all 2243 public checks pass; progress and whitespace checks pass. All sixty
exact inputs are unchanged, retaining the earlier R139 cold 60/60 replay across
eleven objects. No source/private ABI/mapping/exact credit is added.

Totals are 3639 resolved (949 authored, 2115 library, 575 compiler), 712 pending
and 2690 excluded. Exact remains 60 functions / 9883 bytes with provisional
coverage 9883 / 1968455 (0.50%). Public MCP acceptance remains waived; the whole
remaining-origin goal is active and unfinished. A fresh read of the pinned
D3DX8 survey finds 291 pending source-body diagnostic associations. Next review
the bounded fifteen-candidate / 7667-byte cohort whose observed fields have
accepted library, actual import or same-member scalar-constant context. Old
masked survey hits are discovery only and never new acceptance evidence.

## R184 — complete D3DX8 file/image objects and independent real fields

Fifteen complete vendor functions / 7667 bytes are classified library/exclude.
The historical masked SDK survey supplied discovery addresses only. Fresh
extraction from the read-only pinned d3dx8.lib archive independently derives
every complete single-function COMDAT extent, reopens each source member and
compares all original bytes after binding every genuine relocation field.
The archive SHA-256 remains
`39a8e21889a7c1f0b966f04a9e7d392de14ddebb3e091dfa1e5ce3e19564fc28`.

| Address | Whole bytes | Vendor operation |
| --- | ---: | --- |
| `0x0061FF67` | 269 | CD3DXStringBuffer::AddString |
| `0x0060BF05` | 272 | CD3DXFile::Open |
| `0x0060C015` | 202 | CD3DXFile::Create |
| `0x0060C0DF` | 65 | CD3DXFile::Close |
| `0x0061FB45` | 110 | CD3DXDwStack::Push |
| `0x0061FC33` | 179 | CD3DXSzStack::Push |
| `0x00618EC7` | 224 | CD3DXCodec_D3DX_A16R16G16B16::Decode |
| `0x006111EA` | 701 | TF_SetupTriangle |
| `0x0060EC42` | 195 | CD3DXImage::Initialize |
| `0x0060ED05` | 1814 | CD3DXImage::LoadDIB |
| `0x0060F41B` | 740 | CD3DXImage::SaveDIB |
| `0x0060F9D1` | 1191 | CD3DXImage::LoadTGA |
| `0x0060FE78` | 646 | CD3DXImage::LoadPPM |
| `0x0063B803` | 993 | D3DX::jpeg_idct_float |
| `0x00629921` | 66 | D3DX::png_create_struct |

All 83 code fields are explicit: 35 REL32 calls to ten independently accepted
complete source records, 20 actual PE IAT fields with exact DLL/name and source
symbol spelling, and 28 complete same-member readonly scalar fields. Nothing
is masked. The shared symbol catalogue forbids inconsistent destinations.
Complete native decoding retains all returns and internal branches, including
the genuine final internal jump, and 24 byte-identical indirect dispatches.
There are no unresolved external jumps, switch transfers or interior inventory
entries in these accepted extents. Indirect callees receive no new credit.

Ten immutable original library records are retained, with every full own source
primary and complete native ledger carrier. `_floor` keeps its original whole
289-byte wrapper/SSE carrier and the independent 64-byte primary plus complete
225-byte SSE owner; no new 64-byte canonical boundary is invented. The actual
`__alloca_probe` alias is freshly proved at the same source section/offset as
the complete 61-byte `__chkstk` primary, with its real untyped external symbol
metadata. The two names are not treated as separate function AUX definitions.
Original new/delete/character-classifier/malloc/helper records, every source
member hash, native carrier hash and prior manifest are frozen.

Replay `scripts/repo-python scripts/verify-sdk-file-image-origins.py`. Its
`--evidence-only` mode passes before acceptance; accepted-state replay reopens
all actual archive members, full bodies, own extents, fields and target CFG.
For a changed retained dependency, `--replay-dependencies` runs the six complete
provenance roots serially. These roots passed in this batch: runtime, runtime
leaves, allocation API, standard exception, floor math and the original SDK
validator. R148 already recursively cold-replays the complete input-format,
floating-point and runtime-cycle graphs; their duplicate second invocation
was stopped after the first complete PASS. A fresh private call-graph readback
records that coverage. No parallel compiler or writable Ghidra session is used.

Strict R183 HEAD a535ae3 readback changes exactly fifteen function/origin rows
and preserves every original extent, all 902 authored records and all previous
configuration/source/ABI/mapping/match inputs. Full authored checks still cover
902 bodies / 1956112 bytes. Target/tracking/project attestation, query completion
marker, fresh scanning, 22 meaningful field/extent/provenance regression checks,
all 2265 public checks, progress and whitespace checks pass. The supplied target
is unchanged. Compiler build/flags for these archived bodies and complete game
class layouts remain unknown. Origin evidence adds no source, ABI, mapping or
exact credit; the prior cold sixty-unit replay remains applicable to unchanged
inputs. Public MCP acceptance remains waived.

Totals are 3654 resolved (949 authored, 2130 library, 575 compiler), 697 pending
and 2705 excluded. Exact remains 60 functions / 9883 bytes, with provisional
coverage 9883 / 1968455 (0.50%). The whole remaining-origin goal is active and
unfinished. The next bounded cohort is six newly anchored D3DX parents/leaves
/ 762 bytes: 0x0060D11A, 0x0060D044, 0x0061FC02, 0x00610F96, 0x0061FE1F and
0x006255A0. Reopen complete source members and bind all seventeen actual calls
through the immutable R184/earlier source bodies; survey hits remain diagnostic.

## R185 — complete D3DX debug parents and typed image/stack/PNG leaves

The bounded six-candidate cohort resolves five complete vendor functions
/ 724 bytes as library/exclude and preserves the sixth candidate as unknown.
Fresh extraction independently derives each entire own code COMDAT from the
same pinned d3dx8.lib. All 16 actual accepted REL32 calls are bound without
masking through six immutable complete source records, including the original
19-byte R026 CD3DXSzStack constructor.

| Address | Whole bytes | Vendor operation |
| --- | ---: | --- |
| `0x0060D11A` | 375 | CD3DXAssembler::UpdateDebugFileLine |
| `0x0060D044` | 214 | CD3DXAssembler::UpdateDebugText |
| `0x0061FC02` | 49 | CD3DXSzStack::~CD3DXSzStack |
| `0x00610F96` | 48 | CD3DXImage::LoadBMP |
| `0x006255A0` | 38 | D3DX::png_create_info_struct |

The two complete assembler operations preserve five/seven genuine calls to the
whole 110-byte R184 CD3DXDwStack::Push body, with their native debug-state and
stack accesses. The full 49-byte string-stack destructor retains its actual
non-null element deletion loop and separate container release, the full vendor
constructor and the unchanged R184 string-stack Push context. The complete
48-byte BMP gate checks the original header size, BM signature and input
length before passing its remainder to the full 1814-byte LoadDIB owner. The
38-byte PNG info allocation operation reaches the complete 66-byte
png_create_struct source body. Names alone and region proximity establish none
of these decisions. Complete source operations, real fields, typed retained
children and all native CFG/exits are frozen.

The full 38-byte `0x0061FE1F` buffer initializer is byte-equal to the whole
CD3DXBuffer::Init vendor COMDAT, including its one actual call to the complete
14-byte operator new owner. It remains unknown: this allocation-and-field-write
body lacks independently confirmed original owning-object/interface context.
The original canonical rows, full native body, own source extent, real field
and complete positive diagnostic comparison are preserved; no prefix, masked
field, inferred complete class or library promotion is introduced.

Replay `scripts/repo-python scripts/verify-sdk-debug-parent-origins.py`. Before
canonical mutation, `--evidence-only` verifies the complete six-candidate
positive/ambiguity result. Accepted-state replay verifies the five new rows
and unchanged pending row. Each invocation reopens the complete immutable R184
archive graph, all 15 bodies and 83 fields, the ten earlier source/native
carriers, and the original SDK validator's 319 bodies / 80421 bytes and typed
short-owner evidence. The six newly retained full own source records total
2028 bytes. Prior source/ABI inputs are unchanged; the already passed R184
cold dependency roots remain applicable without duplicate compiler replays.

Strict R184 HEAD 82be796 readback changes exactly five function/origin rows,
preserving every original extent, all 902 authored records / 1956112 bytes and
all earlier configuration/source/ABI/mapping/match inputs. Target/tracking/
project attestation and query completion, full authored verification, fresh
scanning, eight new meaningful ambiguity/owner/field guards, all 2273 public
checks, progress and whitespace checks pass. No original target or database
write occurs. Source, complete game layouts, ABI, mapping and exact credit
remain independent; exact stays 60 functions / 9883 bytes and provisional
coverage 9883 / 1968455 (0.50%). Public MCP acceptance remains waived.

Totals are 3659 resolved (949 authored, 2135 library, 575 compiler), 692 pending
and 2710 excluded. The whole remaining-origin goal is active and unfinished.
Next investigate the bounded R186 buffer/interface cohort: the unchanged
38-byte initializer and three entire 71-byte QueryInterface candidates at
0x00609F11, 0x0060A1FA and 0x00620093. Their historical masked vendor diagnostic
uses different original GUID addresses; it does not identify the same
interface. Independently prove each complete SDK GUID, retain full negatives
for incompatible interface constants, and reconcile complete owning vtables/
callers/source members before assigning any new owner. Do not infer an IID
from a name, same-shaped COM body or memory region.

## R186 — full SDK GUID identities and D3DX interface-owner context

Four whole candidates / 251 bytes are classified library/exclude. The old
masked CD3DXBuffer QueryInterface survey hid two different interface GUIDs.
The full original values independently identify ID3DXRenderToSurface at
0x0065DDCC, ID3DXRenderToEnvMap at 0x0065DDBC, and ID3DXBuffer at 0x0065DDFC.
Each complete 71-byte query is freshly extracted from its correct original
SDK member, rather than retaining the wrong buffer association.

| Address | Whole bytes | Vendor operation |
| --- | ---: | --- |
| `0x00609F11` | 71 | CD3DXRenderToSurface::QueryInterface |
| `0x0060A1FA` | 71 | CD3DXRenderToEnvMap::QueryInterface |
| `0x00620093` | 71 | CD3DXBuffer::QueryInterface |
| `0x0061FE1F` | 38 | CD3DXBuffer::Init |

The natural probe `probes/VC7D3DXInterfaceGuids.cpp` includes actual initguid
and d3dx8 headers. Cold compilation freezes all 47 ordinary readonly GUID
sections / 752 bytes and all 84 actual included headers. The three entire
interface GUID COMDATs / 48 bytes agree with their complete original readonly
values. IUnknown at 0x00660E58 is independently proved by the entire 16-byte
readonly definition in Uuid.Lib member obj\i386\unknwn_i.obj, offset 328782.
The UUID archive SHA-256 is
`91e2caa3832f1574ee317ca53fe3db8b389856d2da5e138a20805ac1399b4bab`.
Compiler settings describe the GUID observation only, not an original
executable-wide build profile or a reconstructed game layout.

All three owning source/native pointer carriers are retained in full: 36 bytes
at 0x0065D39C, 52 bytes at 0x0065D3C0 and 28 bytes at 0x0065DE1C, totaling
116 bytes / 29 genuine slots. Source pointer definitions, every real field and
every original pointer value are frozen. Thirty-three entire source functions
/ 2693 bytes are compared without masking, with all 25 real code fields bound
through a coherent complete source catalogue, actual GUIDs and complete own
vtables. All native branches/exits and 73 unchanged indirect dispatches remain
explicit. The buffer's genuine weak `_E` deleting-pointer reference is verified
from its real COFF AUX/search/fallback metadata and complete same-member `_G`
primary; no fictitious standalone weak function extent is introduced.

The original full GetDesc/scene/lost-device/Cube/Sphere/Hemisphere/Parabolic
SDK owners and their complete typed records provide independent library peer
context. The full buffer callback/destructor/init graph closes through the
actual seven-slot buffer vtable, its real QueryInterface GUID and full earlier
new/delete owners. This supplies the previously missing owning context for the
whole 38-byte initializer. No full original object layout or private ABI is
declared or instantiated. Non-inventory callback controls receive no new
canonical rows or origin credit. Existing compiler deleting wrappers retain
their original compiler classification.

The entire 35-byte EnvMap Face and 227-byte EnvMap End source/native controls
are read and frozen, including their real unsolved fields and full native CFG.
Their downstream EndScene/filter linkage is unresolved: no positive body/linkage
claim is made, no field is masked and no owner is accepted from those controls.
The full 52-byte owning carrier still retains both slots, rather than dropping
them to compare a convenient prefix. Independently established EnvMap query/
GUID and the complete existing library peers support only the bounded query
decision. All other original anchor rows stay unchanged.

Two entire wrong-buffer QueryInterface comparisons / 142 bytes remain negative:
each has its actual interface pointer difference at code byte 35, plus the
complete sixteen-byte GUID difference. A source IID_ID3DXBuffer field is never
relabelled as another interface merely because solved native fields fit.
Replay `scripts/repo-python scripts/verify-sdk-interface-origins.py`; its
`--evidence-only` cold replay passes before mutation, and accepted-state cold
replay passes. It reopens the complete original R185/R184/SDK graphs serially,
with unchanged already-passed cold dependency inputs. R185's manifest remains
immutable. Its validator permits only the exact new buffer transition, guarded
by frozen whole original/accepted record digest
`84329381c12dbf07a0af4e12a907fba7eb7b03253e21439873e6cf2c3f8b5658`.
R186 also pins the updated R185 validator. All former pending-byte comparisons
and original extent/source facts remain checked.

Strict R185 HEAD 5d6dbb6 readback changes exactly four function/origin rows and
preserves every original extent, all 902 authored records / 1956112 bytes and
all previous configuration manifests. All sixty source/header/build/match
inputs remain unchanged from the prior cold exact replay. Target/tracking/
project/query attestations, full authored replay, fresh scanning, fourteen new
meaningful GUID/table/opaque-field/transition guards, all 2287 public checks,
progress and whitespace checks pass. No target or database write occurs.
No source, ABI, mapping or exact credit is added. Public MCP acceptance is waived.

Totals are 3663 resolved (949 authored, 2139 library, 575 compiler), 688 pending
and 2714 excluded. Exact stays 60 functions / 9883 bytes and provisional
coverage 9883 / 1968455 (0.50%). The whole remaining-origin goal remains active
and unfinished. Next review the three complete source-owner destructors
/ 89 bytes already read as original context: 0x0061FE0A / 21, 0x00609EEF / 34,
and 0x0060A7D2 / 34. Retain the entire R186 GUID/table/callback graph and all
original R038 generated wrapper facts. Apply only an explicitly frozen narrow
anchor transition if new independent destructor evidence is accepted; do not
rewrite the R186 manifest or promote the two opaque EnvMap controls.


## R187 — explicit SDK destructor policy and generated wrapper ownership

Three complete D3DX8 source-owner destructors / 89 bytes are classified
library/exclude, independently of the existing compiler deleting wrappers.

| Address | Whole bytes | Vendor operation |
| --- | ---: | --- |
| `0x0061FE0A` | 21 | CD3DXBuffer::~CD3DXBuffer |
| `0x00609EEF` | 34 | CD3DXRenderToSurface::~CD3DXRenderToSurface |
| `0x0060A7D2` | 34 | CD3DXRenderToEnvMap::~CD3DXRenderToEnvMap |

All three original SDK COMDAT extents, source/native hashes, six actual fields
and complete branches/exits are reopened. Each real vtable write binds its
entire R186 owning pointer carrier and independently proved interface GUID.
The buffer releases its storage through the complete earlier delete owner.
The two render destructors call their distinct complete OnLostDevice owners,
then release the COM member through slot +8 and clear that member. The
same-shaped render source bodies do not merge their distinct source symbols,
vtable definitions or cleanup targets. All fields remain unmasked.

The natural `probes/VC7SDKReleasePolicies.cpp` uses complete observer classes
and real public SDK interfaces, with no incomplete original owner instance.
Cold VC7.1 compilation with `/Od /Ob0 /Gy /GR- /GX /Zi /GS /showIncludes`
retains eight entire ordinary sections / 205 bytes, seven full code controls
/ 193 bytes, 84 actual SDK/CRT headers and the whole twelve-byte observer
layout [4, 4, 4]. Default raw-pointer lifetime end emits no cleanup call.
Explicit Surface/EnvMap observer policies reach the actual public cleanup
slots +28/+44. Their natural generated deleting wrappers are complete
44-byte bodies, including the real destructor and delete fields; they are not
truncated to the original 28-byte wrapper shape. These controls establish the
explicit/default/generated distinction, with no false target-positive claim,
invented original ABI, object layout or reconstructed source presence.

The three original R038 deleting-wrapper records and canonical compiler rows
remain unchanged. All 53 R038 wrappers / 1484 bytes cold-replay successfully.
The entire R186 interface/GUID/owner graph and R185/R184/SDK dependencies also
replay serially. R186's manifest remains immutable; its validator permits only
the three complete hash-pinned original-to-R187 accepted transitions, with
record digests checked against the actual new manifest. The two opaque EnvMap
controls cannot use that transition. Replay
`scripts/repo-python scripts/verify-sdk-destructor-origins.py`.
Manifest SHA-256:
`506e7fac5ff1cc392d381c1e16373fc15f9d0285158793ddfff0d5658262ccd1`.
Both evidence-only cold replay before mutation and accepted-state cold replay
pass. Strict R186 HEAD 0151132 readback changes exactly three function/origin
rows, preserving every original extent, all 902 authored records / 1956112
bytes and every earlier configuration manifest. All sixty exact inputs remain
unchanged from the prior cold replay. Fourteen meaningful source-policy,
interface-field, wrapper and anchor-transition guards bring public checks to
2301. Target/tracking/project/query markers, complete authored verification,
fresh scanning, progress and whitespace checks pass. No target/database write
or new source/ABI/mapping/exact credit occurs. Public MCP acceptance is waived.

Totals are 3666 resolved (949 authored, 2142 library, 575 compiler), 685 pending
and 2717 excluded. Exact stays 60 functions / 9883 bytes and provisional
coverage 9883 / 1968455 (0.50%). The whole origin goal remains active and
unfinished. The next bounded R188 cohort is the full six-byte public
D3DXVec3Normalize dispatcher at 0x0061AF34 and 328-byte D3DXMatrixLookAtRH
at 0x0061CA33. Their actual linkage was freshly reached through the complete
pending EnvMap End/EndScene/Render/Setup graph. Prove the complete runtime
dispatch carrier, its real nonzero +28 field and implementation/initializer
context before accepting either function. Do not treat a relocated pointer
as an independent symbol identity or promote the still-unresolved texture/
lock/codec graph. This discovery does not change any additional canonical row.


## R188 — complete x86 SDK pointer policies, lookup data and registry imports

The planned public Normalize/matrix cohort exposed unresolved CPU selection,
shared source entries and guarded projection tables. Both original public
rows remain unknown. This bounded dependency batch instead accepts three
entire explicit SDK policies / 354 bytes, with no convenient parent promotion.

| Address | Whole bytes | Vendor operation |
| --- | ---: | --- |
| `0x006292BC` | 60 | x86_D3DXInitFastTable |
| `0x006209EF` | 92 | GetD3DRegValue |
| `0x00629081` | 202 | x86_D3DXVec3Normalize |

Ten full own COMDAT source/native comparisons / 1268 bytes bind all fourteen
genuine fields. The initializer writes eight real function pointers, each
bound to its separately complete original x86 implementation. The full 227-
and 142-byte matrix implementations retain their R008 library records; five
other vector implementations remain non-inventory controls. No new canonical
rows are created for them. The complete pointer-writing policy is explicit SDK
selection code, rather than a generated lifetime/template operation.

The normalizer retains its entire x87 zero/unit/lookup/scale paths, all branch
targets and final RET 8. Its indexed data reads use the actual source symbol
_invSqrtTab at 0x0066D2A0 with distinct source addends 0 and +4. The whole
initialized source data section is 4104 bytes, including _invSqrtTab and the
neighboring _a1/_a2 definitions at offsets 4096/4100. All original bytes,
definitions and source permissions agree. This source section is writable:
the observation compares the original file image and does not assert runtime
immutability. The index mask 0xFF8 bounds the paired reads within the first
4096 bytes; the remaining source definitions are still retained and compared.
The public D3DXVec3Normalize dispatcher at 0x0061AF34 is a separate unknown
candidate; this accepted implementation does not grant its wrapper credit.

The registry helper's whole 28-byte readonly source definition is
Software\Microsoft\Direct3D at 0x0065DE70. All three real IAT fields independently
resolve through the actual PE import directory to ADVAPI32 RegOpenKeyA,
RegQueryValueExA and RegCloseKey, with their genuine decorated source symbols.
The complete helper preserves success/error exits and handle cleanup. These
full SDK registry and lookup/implementation source owners establish library
policy independently of auto-analysis names, nearby code or masked similarity.

The entire 460-byte writable original D3DX source pointer carrier / 112 fields
is retained as observed context. Every source definition, source field, actual
pointer and intervening byte remains present. Unrelated pointers receive no
false independently proved linkage claim. The whole 221-byte CPU selector
and public Normalize 6-/LookAtRH 328-byte original/source snapshots likewise
remain unresolved context with their real fields, hashes and unknown rows.
Private discovery identifies unresolved Intel exception/filter paths, local
projection tables and SIMD source aliases/assembly tails. No dynamic CPU
selection or unrelated implementation is inferred from the initial carrier.

Replay `scripts/repo-python scripts/verify-sdk-x86-policy-origins.py`. Its
manifest SHA-256 is
`dfba474686f4032271ad6ba4f2f9fde62ed221590e40c13f354bf7086e2872f1`.
Evidence-only replay before mutation and accepted-state replay pass. Every
source body is freshly extracted from the pinned original archive, with all
fields included; this archive-only origin batch adds no reconstructed source
or exact compilation credit. Strict R187 HEAD 53cd473 readback changes exactly
three function/origin rows and preserves every other extent, all 902 authored
records / 1956112 bytes and every earlier configuration manifest. Source,
headers, flags, ABI, mapping and all sixty exact inputs remain unchanged from
the prior cold replay. Target/tracking/project/query markers, full authored
verification, fresh scanning, twelve meaningful whole-data/addend/import/
pointer/scope guards, all 2313 public checks, progress and whitespace pass.
Public MCP acceptance remains waived. No target/database write occurs.

Totals are 3669 resolved (949 authored, 2145 library, 575 compiler), 682 pending
and 2720 excluded. Exact stays 60 functions / 9883 bytes and provisional
coverage 9883 / 1968455 (0.50%). The whole origin goal remains active and
unfinished. Next review the bounded R189 SSE/SSE2 initializer pair at
0x00628900 / 262 and 0x00628A10 / 266. Each complete source COMDAT carrier is
272 bytes, retaining its actual post-RET LEA alignment. Independently reconcile
the reachable function extent and that alignment; compare the full carriers,
every pointer and each whole source callback including any genuine local $$1
entry/shared body. Do not cut a source section to fit the provisional native
extent or treat its padding as executable function credit.


## R189 — entire SIMD code carriers, real entries and independent alignment

The complete SSE/SSE2 initializer graph closes through 56 entire original SDK
code carriers / 12960 bytes and all 264 genuine fields. Six inventoried
candidates / 1670 function bytes are classified library/exclude; four newly
closed mathematical dependencies join the original two-initializer cohort.

| Address | Complete function bytes | Original source association |
| --- | ---: | --- |
| `0x00628900` | 262 | sse_D3DXInitFastTable |
| `0x00628A10` | 266 | sse2_D3DXInitFastTable |
| `0x00630A90` | 89 | sse_D3DXVec2TransformCoord |
| `0x0063C1C0` | 492 | sse_SinCos4 |
| `0x0063C990` | 329 | sse2_SinCos4 |
| `0x0063C8A0` | 232 | sse2_sincos |

Both initializer COMDAT carriers are 272 bytes. Whole carriers / 544 bytes,
including all 67 real pointer fields and actual post-RET bytes, compare without
masking. Each pointer binds its separately complete correct source callback;
the full graph retains 51 callback owners and three SinCos dependency owners.
The source/native reachable CFG independently ends the two functions at their
real RETs, excluding ten and six original alignment bytes. This is not an
aux-less extraction using target candidate sizes: the entire own source
section is always reopened and compared. None of the 497 independently
decoded alignment bytes across the graph receives function or exact credit.
Complete function extents total 12463 bytes; all former canonical extents stay
unchanged. Alignment includes actual self-MOV and self-LEA instructions.
Register writes, hidden fields and branch targets cannot become padding.

Real local $$1 and TAG_PACKET source entries remain in the exact COFF symbol,
storage, section, offset and AUX records. Every entry participates in complete
CFG reconciliation. They are not removed to satisfy a single-function source
extractor or introduced as fictitious independently inventoried functions.
All native branches/exits and all three direct mathematical callee symbols
remain bound through the complete source catalogue. The prior 64-byte R008
sse_D3DXVec2Transform owner and 49 non-inventory source controls retain their
canonical presence/absence and original records. No extra candidate rows are
created for the callback controls.

Nine whole initialized source data sections / 2816 bytes retain every source
definition, complete original/native image and writable permissions. These
are original file-image observations, with no runtime-immutability claim.
Member/section/symbol-index keys distinguish genuine local .data/.data1 names;
identical textual section names from different objects are not name aliases.
The full 32-byte source BSS allocation and three shared COMMON allocations
/ 36 bytes have separate proofs. Six actual original COFF COMMON declarations
from two source owners preserve the genuine 4-/16-/16-byte allocation sizes.
Their entire ranges lie in independently recorded writable PE virtual
zero-fill storage. They are not initialized file bytes, readonly constants,
guessed addresses or invented private class layouts. Every allocated source
definition is observed by a real field. The full Shadow and PlaneIntersectLine
callbacks remain present instead of dropping unresolved data fields.

Replay `scripts/repo-python scripts/verify-sdk-simd-carrier-origins.py`.
Manifest SHA-256:
`6edf1ccbd7727169fe70054fb036f5bb3d36cc3b44cc77ce036e417425fd7ec1`.
The reusable `scripts/sdk_code_carriers.py` source reader is hash-pinned by the
manifest. Evidence-only replay before mutation and accepted-state replay pass;
each reopens actual complete source members and real allocations from the
pinned archive. Strict R188 HEAD c402756 readback changes exactly six function/
origin rows. Every original extent, all 902 authored records / 1956112 bytes,
all earlier manifests and all sixty source/header/build/match inputs remain
unchanged from the prior cold replay. Target/tracking/project/query markers,
full authored verification, fresh scanning, eighteen meaningful carrier/entry/
alignment/COMMON/data-scope guards, all 2331 public checks, progress and
whitespace pass. No target/database write, reconstructed private layout,
source, ABI, mapping or exact credit is added. Public MCP acceptance is waived.

Totals are 3675 resolved (949 authored, 2151 library, 575 compiler), 676 pending
and 2726 excluded. Exact stays 60 functions / 9883 bytes and provisional
coverage 9883 / 1968455 (0.50%). The whole origin goal remains active and
unfinished. Next reconcile R190's complete Intel CPU probe and its feature
caller. The source IsIntelSSEProcessor extent is 165 bytes, while inventory
splits it at 0x00620B41 / 58, Catch@00620B7B / 12 and 0x00620B87 / 95.
The source's actual resume/catch labels and ten-byte EH frame helper must be
retained with complete C++ EH metadata and prior runtime owners. Resolve the
180-byte D3DXIsProcessorFeaturePresent at 0x00620BE6 only after that whole
parent/label topology and both actual PE imports are proven. Do not accept
the convenient 58-byte prefix or reinterpret catch/resume entries as unrelated
authored functions. The 221-byte CPU optimizer and public math callers remain
unchanged and unknown in R188's immutable context snapshots.

## R190 — whole CPU parent, subordinate catch/resume entries and source ABI

R190 resolves four inventory entries: three library decisions and one compiler
decision. There are two complete library functions / 345 bytes; the catch12
and continuation95 are overlapping subordinate entries, not two additional
independent functions. The primary at `0x00620B41` changes from an incomplete
58-byte inventory prefix to its independently derived complete 165-byte COMDAT.
Only that primary extent changes; all other canonical extents remain unchanged.

| Entry | Accepted span | Origin and source relationship |
| --- | ---: | --- |
| `0x00620B41` | 165 | Library IsIntelSSEProcessor, complete original source parent |
| `0x00620B7B` | 12 | Compiler catch-return/resume entry inside that parent |
| `0x00620B87` | 95 | Library parent continuation, including catch resume at +76 |
| `0x00620BE6` | 180 | Library D3DXIsProcessorFeaturePresent, complete feature policy |

**Target and original-source observations.** The actual archive member is
`obj\i386\cpudetect.obj`, offset 776284. The previous handoff's d3dxinit.obj
label for this cohort was incorrect; actual COFF ownership supplies the name
here. The parent has one real type32/storage3 definition at section14 offset0,
the actual catch `$L48085` at +58 and resume `$L48087` at +76, both type0/storage6.
The normal prefix jumps to +70. All instructions are accounted for from the
independent normal, catch and resume roots; the complete parent ends at its
final RET at `0x00620BE5`. The whole source165 and caller180 compare unmasked
with every genuine field. The caller's two actual Intel-parent calls and its
retained complete isX3Dprocessor56 owner remain distinct.

The complete readonly `GenuineIntel` source literal is 13 bytes. The parent
copies all 13 bytes locally, but contains no vendor-string comparison: the
source name/literal does not establish an Intel-only predicate. It executes
CPUID leaf0, guards leaf availability, then tests leaf1 EDX bits 0x02000000
and 0x04000000 to set return bits4/8. The catch transfers the saved return
value to a temporary and returns the actual resume address in EAX. The explicit
fault-return policy remains part of the SDK parent; generated entry ownership
does not establish a second authored/library function.

The entire separate .text$x helper10 at `0x00656CC6` is an actual source
type0/storage6 label, not an invented standalone function/AUX extent. It binds
FuncInfo at `0x0066A94C` and tail-jumps to the retained CxxFrameHandler54.
All 80 bytes of .xdata$x compare without masking: UnwindMap16, HandlerType16,
TryBlockMap20 and FuncInfo28 retain both state entries, catch-all handler,
try/catch state ranges, magic 0x19930520 and all four source-local pointers.
The zero FS:[0] displacement binds the genuine `__except_list` absolute
section-1/value0 definition in pinned CRT exsup.obj; it is not a fabricated
undefined or PE-data symbol. The retained __EH_prolog31 stays compiler-owned;
CxxFrameHandler54 and InternalCxxFrameHandler162 stay library-owned, with
their complete old source/body/real-field evidence reopened unchanged.

GetVersionExA and IsProcessorFeaturePresent are independently parsed from the
actual KERNEL32 IAT at `0x00657090` and `0x006570C0`. The full old-Windows caller
policy uses feature selectors6/7/10, OSVERSIONINFOA148 and the actual major,
minor, build and platform offsets4/8/12/16. Its build threshold compares the
low 16-bit build field against 1373; this is observed historical policy.

**Compiler observations and inference.** Natural C++ saved-flag and fixed-zero
catch-return controls cold-build with `/O1 /Ob0 /Gy /GR- /GX /Zi /GS /showIncludes`.
All seven ordinary emitted code/EH/data sections / 328 bytes, all actual fields
and definitions, 85 actual included header hashes, and the complete 36-byte
feature/layout observer are retained. Both controls emit a six-byte generated
catch that returns a resume address; their distinct explicit return policies
appear at the respective resume labels. This supports the generated ABI role
of the original anonymous catch entry. It does not byte-match that twelve-byte
entry or establish the original SDK compiler profile. Complete ordinary code
and metadata are retained rather than selecting an equal fragment.

**Acceptance and limits.** Replay
`scripts/repo-python scripts/verify-sdk-cpu-eh-origins.py`; manifest SHA
`9eaa1c1ae5d532e9982f9b582cb77b4f2a98839f5bd88eae078674576e54433c`.
The five full original source sections / 448 bytes retain all16 real fields.
Exactly four function/origin rows change from d004662. The complete 902 authored
bodies / 1956112 bytes and every earlier configuration evidence file remain
unchanged. Twenty new adversarial checks reject incomplete prefixes, hidden
entries, fake absolute symbols, incorrect catch/resume bindings, truncated EH,
changed prior compiler ownership and duplicate/source/ABI/exact credit.

Origin totals are 3679 resolved: 949 authored, 2154 library, 576 compiler;
672 pending and 2730 excluded. The 60 exact/source-present functions, 9883
bytes, 60 units and eleven object inputs remain unchanged. Public MCP
acceptance remains waived. Original private game layouts, the actual original
compiler profile and later CPU/public dispatch candidates remain unknown.
Both the full-origin and 50%-exact milestones remain unfinished.

## R191 — complete 3DNow callback graph and original shared math section

R191 resolves seventeen complete library functions / 7194 bytes. Closing the
550-byte x3d initializer required its original quaternion, matrix, projection
and math dependencies; those complete dependent functions are accepted in the
same bounded graph. The CPU selector and two public dispatch candidates remain
unchanged and unknown until the default mutable-table graph closes.

| Address | Function bytes | Original source association |
| --- | ---: | --- |
| `0x00628BF5` | 550 | x3d_D3DXInitFastTable |
| `0x00633C36` | 179 | x3d_D3DXQuaternionToAxisAngle |
| `0x006341DF` | 108 | x3d_D3DXQuaternionRotationAxis |
| `0x0063424B` | 311 | x3d_D3DXQuaternionSlerp |
| `0x00634382` | 141 | x3d_D3DXQuaternionBaryCentric |
| `0x0063440F` | 146 | x3d_D3DXQuaternionSquad |
| `0x00634505` | 167 | x3d_D3DXQuaternionLn |
| `0x006346F3` | 2649 | x3d_D3DXQuaternionSquadSetup |
| `0x00636B8C` | 421 | x3d_D3DXMatrixRotationYawPitchRoll |
| `0x00637265` | 281 | x3d_D3DXMatrixRotationAxis |
| `0x00639897` | 360 | x3d_D3DXVec3Project |
| `0x00639A1F` | 518 | x3d_D3DXVec3Unproject |
| `0x00639C45` | 307 | x3d_D3DXVec3Unproject_K7 |
| `0x0063CBC0` | 245 | _a_atan2 |
| `0x0063CCC0` | 247 | _a_acos |
| `0x0063D2A0` | 281 | _a_sincos, actual source alias _a_cos |
| `0x0063D3C0` | 283 | _a_sin |

**Target and original-source observations.** All 69 complete original code
carriers / 30525 bytes compare without masking, retaining all 498 genuine
fields, actual definitions and original AUX metadata. There are 68 original
COMDAT carriers / 27269 bytes and one complete non-COMDAT math section / 3256
bytes. The full x3d initializer has one get_feature_flags call and 62 real
callback pointer fields: 57 ordinary assignments and five K7 replacement
fields. Every callback and direct callee is associated with a separately
complete source carrier/entry; no pointer destination is accepted merely from
an observed address or the presence of 3DNow instructions.

The three projection COMDATs have whole extents392/550/339, each including an
actual 32-byte eight-entry local switch table after code360/518/307. These are
switch tables, not exception handlers, code or alignment. The real type0/
storage3 table label, all eight type0/storage6 case labels, every DIR32 field,
decoded unsigned CMP EAX,7 / JA guard and indexed EAX*4 jump are retained.
Every table entry targets an independently decoded instruction in its own
complete parent. Comparison includes all 96 table bytes; canonical function
extents retain their complete code only. The separate five-byte TransformCoord
wrapper preserves its actual external tail to the whole inline implementation.

The original `.\Release\math.obj` at archive offset2074212 has one full 3256-
byte code section, twenty real public source definitions at nineteen unique
entries, and 138 real DIR32 fields into its full writable data344 section.
_a_cos and _a_sincos share source offset1952 and target0x0063D2A0; they do not
create duplicate functions or exact units. All nineteen source-defined regions
are reconciled independently, yielding3002 complete function-span bytes and
254 separately preserved trailing alignment bytes. Internal identity LEAs are
also recorded explicitly. The actual unreachable five-byte ADD EAX,0 after
_a_sin's RET is retained as original alignment; it changes EFLAGS and is not
claimed as an executed no-op. No padding is inserted or edited in source.
The single encoded log10-to-log call is an original same-section direct call
without a COFF relocation; it remains distinct from the 138 genuine fields.

The full readonly _const3dn_NegQuarters8 image and writable math344 initial
image retain original flags, definitions and every source offset. Writable
image equality does not imply runtime immutability. Three prior readonly
source sections /314 bytes retain AuthenticAMD, UnknownVendr and the complete
shared 3DNow constants. All ten old R008 library owners and sixty non-inventory
function entries stay unchanged; no additional canonical candidate is created.

**Inference and limits.** Ownership is library because the complete explicit
policies close through the pinned original SDK source-object graph. Source
symbols remain associations, not recovered original target names. Original
compiler/assembler profiles and runtime-selected callbacks remain unknown.
No reconstructed C++/assembly body, private class/table instance, ABI declaration,
mapping or exact unit is supplied by this batch. No new compiler-emission claim
needs a compiler probe; the acceptance replay freshly reopens the actual pinned
source carriers, data definitions, fields and target bytes.

**Acceptance.** Replay `scripts/repo-python scripts/verify-sdk-x3d-origins.py`.
Manifest SHA `d2a7ef2eeb860ae2e392456a64a59df935f108b95b894a171f8a37a8fa0ca22d`.
Exactly seventeen function/origin rows change from df3ea16; every original
extent, all 902 authored bodies /1956112 bytes, earlier evidence manifests
and all sixty exact inputs remain unchanged. All 2375 public checks pass,
including24 new adversarial guards for omitted K7 callbacks, truncated tables,
false aliases, wrong source/storage keys, changed readonly/writable images,
unsupported padding, hidden fields and false CPU/public/source/exact credit.
Target/tracking/project checks, bounded Ghidra query markers, full independent
source/Capstone reconciliation, fresh655-pending scan, progress and whitespace
checks pass. Ghidra's 500-instruction query limit truncates the large SquadSetup
display; complete code/field/CFG coverage comes from the whole-source verifier,
not that bounded display. Public MCP acceptance remains waived.

Origin totals are3696 resolved:949 authored,2171 library and576 compiler;
655 pending,2747 excluded. Exact remains60 functions /9883 bytes and60 units
across eleven object inputs. Both the full-origin and50%-exact milestones
remain unfinished. Next close the default C table dependencies and then the
remaining CPU selector/public Normalize/LookAtRH cohort.

## R192 — complete default table, CPU selector and runtime dispatch

R192 accepts53 complete library functions /3468 bytes:31 initialization policies
/907 bytes,14 public functions /406 bytes, six C math functions /1913 bytes,
CPU selector221 and CRT finite21. The complete original source graph closes the
R192 handoff cohort and every required default callback dependency. All53 original
canonical extents stay unchanged; no source, ABI, mapping or exact credit is added.

| Key source association | Address | Function bytes |
| --- | --- | ---: |
| D3DXCpuOptimizations | `0x00620C9A` | 221 |
| D3DXVec3Normalize | `0x0061AF34` | 6 |
| D3DXMatrixLookAtRH | `0x0061CA33` | 328 |
| c_D3DXVec3Project | `0x0061E467` | 365 |
| c_D3DXVec3Unproject | `0x0061E5F4` | 390 |
| c_D3DXMatrixShadow | `0x0061EB67` | 218 |
| c_D3DXMatrixReflect | `0x0061EC41` | 191 |
| c_D3DXMatrixTransformation | `0x0061E8B3` | 692 |
| c_D3DXMatrixRotationYawPitchRoll | `0x0061E87A` | 57 |
| __finite | `0x00643FC6` | 21 |

**Target and original-source observations.** All129 original code carriers
/14378 bytes and298 genuine fields compare unmasked. The whole397-/422-byte
C projection carriers include eight-way switch tables32/32 after code365/390.
The actual table/case definitions, unsigned EAX0..7 guards, indexed jumps and all
sixteen original DIR32 entries are retained separately from function code.
No comparison is truncated to the provisional code-only extents.

The full initialized mutable table460 at0x0066D070 retains112 original function
pointer fields and all nonpointer bytes. Source definitions place g_D3DXFastTable
at offset0 and g_D3DXFastTableC at232. The selector's two original REP MOVSD paths
copy57 DWORDs /228 bytes from the C bank. All57 default callbacks have separately
whole source owners. The first bank has55 original pointers; its Ln/Exp slots
at220/224 are genuinely zero initially and are filled by the copy. The four-byte
source gap at228 is preserved. These observations do not establish a complete
private C++ type or authorize instantiating it.

Every indirect call/tail is tied to an actual original table-slot field in that
228-byte bank. The verifier requires absolute memory dispatch and preserves
runtime-selected behavior; a slot is never rewritten as a fixed final callee.
The CPU selector retains its original default/reset state, registry disabling
policy, feature tests, x86 initialization and 3DNow/SSE2/SSE precedence. Seven
independent prior anchors retain their complete R188/R189/R190/R191/R147 source
and target images and immutable dependency evidence. All68 non-inventory entries
and eight previously accepted inventoried owners stay unchanged.

All18 original initialized data sections /544 bytes retain full definitions,
source AUX records, actual fields and source/PE permissions:table460, CPU state8,
DisableD3DXPSGP16 and fifteen readonly scalar sections /60 bytes. Writable image
equality describes initialization only. No BSS/COMMON/virtual zero-fill is
invented or substituted for an initialized image.

Two complete non-inventory SDK callers independently resolve the historical
R155 finite ambiguity: c_MatrixInverse909 at0x0061BE75 has its actual REL32 field
at756 to0x00643FC6; c_PlaneIntersectLine162 at0x0061DD91 has the genuine field
at98 to the same owner. The original ieeemisc.obj member2915526 supplies the
whole21-byte __finite function AUX with no relocations. Its complete byte image,
all branches/returns and source definitions are preserved. R155's natural20-byte
exponent alternative remains different and does not obtain a prefix match.
R155's earlier bounded caller absence remains historical, not a timeless claim.
The separate FillZeroMan12 explicit/ordinary ambiguity stays unknown. Complete
C AxisAngle157 and Ln126 retain actual calls to the independently accepted
whole203-byte __CIacos graph; intrinsic names alone grant no ownership.

**Inference and limits.** The complete explicit SDK initialization/dispatch and
math policies are library-owned through the pinned original COFF graph. The
finite leaf now has two independent whole original SDK callers as corroboration,
beyond its short byte image or source symbol. Source names remain associations;
original target names and compiler/assembler profiles are unknown. No compiler
emission hypothesis, reconstructed C++/assembly body, private layout or new
probe is introduced. The retained natural R155 controls are cold-replayed.

**Acceptance.** Replay `scripts/repo-python scripts/verify-sdk-dispatch-origins.py`.
Manifest SHA `41530c573f88cd39b09d53051ed9c5268f4efbafd53ec92cfeb16c2364416b51`.
Exactly53 function/origin rows change from7e6967f; all previous configuration
evidence files,902 authored bodies /1956112 bytes and sixty exact inputs remain
unchanged. R155/R188/R191 permit only four exact original-to-R192 snapshot
transitions; R189 permits only the exact R188 replacement source hash and new
immutable transition evidence. Older manifests are never rewritten or broadly
relaxed. Thirty new adversarial checks reject omitted callbacks/fields, truncated
data/switch extents, false source/ABI/exact credit, changed historical snapshots,
unbound/out-of-bank dispatch, register calls/tails and hidden fields.

All2405 public checks, local target/tracking/project checks, bounded Ghidra query
markers, full source/CFG replay, affected historical evidence, postaccept R155
canonical readback, fresh602-pending scan, exact-input preservation, progress
and whitespace checks pass. Public MCP acceptance remains waived. Origin totals
are3749 resolved:949 authored,2224 library and576 compiler;602 pending and2800
excluded. Exact stays60 functions /9883 bytes and60 units across eleven objects.
Both the full-origin and50%-exact milestones remain unfinished.

Next review three adjacent public/C companions:0x0061C89D6 (Transformation
runtime slot),0x0061CB7B328 (LookAtLH) and0x0061E85339 (C RotationQuaternion).
They are diagnostic candidates only; reopen their whole original source and
independent accepted dependencies before deciding ownership. Then continue
through the fresh602-pending lanes, preserving all earlier unresolved lifetime,
copy, math, allocator and short-CRT alternatives.

## R193 — complete SDK math companions and corrected operator identity

R193 accepts three complete library companions /373 bytes. Every original
canonical extent remains unchanged. The original d3dxmath.obj at archive
offset684528 supplies three whole COMDATs, actual definitions/AUX metadata and
four genuine fields. Every code byte, full CFG, return and indirect tail compares
without masking. The complete independent R192 default-table/CPU/callback graph
is replayed before accepting the companions; no prior evidence is loosened.

| Address | Whole bytes | Original source association |
| --- | ---: | --- |
| `0x0061C89D` | 6 | _D3DXMatrixTransformation@28 |
| `0x0061CB7B` | 328 | _D3DXMatrixLookAtLH@16 |
| `0x0061E853` | 39 | ??DD3DXQUATERNION@@QBE?AU0@ABU0@@Z, quaternion operator* |

**Target/source observations.** The Transformation wrapper has one genuine
DIR32 field with source addend156 into g_D3DXFastTable at0x0066D070. Its original
absolute indirect tail uses slot0x0066D10C; selection remains mutable at runtime.
The complete228-byte bank and corresponding independently owned default callback
are retained through R192's whole460-byte initialized table. The wrapper does
not establish a fixed final callback or instantiate a private table type.

The complete328-byte LookAtLH matrix policy has130 reachable instructions and
two genuine REL32 fields to the whole accepted Normalize6 entry. Its full
original handedness/vector/matrix policy is retained; adjacency to LookAtRH is
not acceptance evidence. The39-byte quaternion operator has21 instructions and
one original REL32 field to whole accepted QuaternionMultiply6. Its complete
source primary definition is the multiplication operator, not C MatrixRotation-
Quaternion. The prior handoff's tentative association was incorrect and is
superseded here. The actual C MatrixRotationQuaternion carrier is226 bytes.

Two entire original SDK header files are hash-pinned read-only. The exact public
Transformation/LookAtLH declaration region and explicit quaternion multiplication
body region are independently retained by complete region digests. The latter
creates a quaternion result and calls D3DXQuaternionMultiply before returning it;
this is explicit SDK policy rather than a name-only compiler-generated wrapper
claim. Original source objects and public header policy are evidence, not new
reconstructed source. No decompile, target-byte source body or private layout is
introduced and no original compiler profile is inferred.

**Inference and limits.** The three complete explicit SDK companions are
library-owned through their actual pinned source definitions, independent
accepted callees, whole mutable dispatch graph and original header policy.
Original target symbol names and runtime-selected final callbacks remain
unknown. No source presence, ABI declaration, mapping or reconstruction exact
credit is added. No new compiler-emission claim requires a cold probe.

**Acceptance.** Replay
`scripts/repo-python scripts/verify-sdk-companion-origins.py`; manifest SHA
`979517c54be5b7787e8558af22c4d067207619388fe9d20be6ed5d9c3e5d0180`.
Exactly three function/origin rows change from4aad114. All earlier configuration
evidence files,902 authored bodies /1956112 bytes and every exact input remain
unchanged. All2417 public checks pass, including twelve adversarial companion
checks rejecting the wrong historical operator association, truncated policy,
wrong callees/slot, fixed-callee substitution and false source/ABI/exact credit.
Local target/tracking/project/query markers, full original source/CFG and R192
replay, exact guard, fresh599-pending scan, progress and whitespace pass. Public
MCP acceptance remains waived.

Origin totals are3752 resolved:949 authored,2227 library and576 compiler;
599 pending and2803 excluded. Exact remains60 functions /9883 bytes and60 units
across eleven objects. The full origin goal and50%-exact milestone are unfinished.
Next close the distinct original MMX registry/cache policy153 at0x00620A70 and
its previously accepted R008 CPUID helper37 at0x00620A4B. These are diagnostic only;
reopen all genuine fields, complete initial state/literals, actual imported APIs,
CPUID branches/returns and source definitions before deciding ownership.

## R194 — complete MMX registry/cache policy and unchanged R008 helper

R194 accepts one complete153-byte library policy at0x00620A70, associated with
?isMMXprocessor@@YAHXZ in original cpudetect.obj at archive offset776284.
Its full original code section, type32/storage2 primary definition, complete
AUX metadata and all12 genuine fields compare unmasked. The original candidate
extent153 and every other canonical row remain unchanged.

**Target/source observations.** The full policy opens the Direct3D registry path
and checks DisableMMX. A successful query with type4 and nonzero value closes
the handle, writes cache0 and returns0. Other successful-open paths also close
the handle before checking the cached result. A negative cache initializes to0
and calls the whole CPUID helper; a positive helper result executes original
EMMS and sets cache1. The shared complete return path and all guards are retained.
Four actual imported call sites bind independently to three API identities:
RegOpenKeyA, RegQueryValueExA and two RegCloseKey paths. The sole genuine REL32
field at125 targets the complete37-byte helper0x00620A4B.

That helper is previously accepted R008 library evidence, not a non-inventory
entry. The prior handoff mistakenly called it non-inventory; this is corrected
without changing its original R008 function/origin/source-evidence row or giving
it new acceptance credit. Its actual type32/storage2 source definition and all37
bytes are freshly reopened. The observed protocol retains four outer register
saves, original PUSHAL/POPAL, CPUID inputEAX1, TEST EDX,0x800000, SETNE AL and
complete stack/register restoration/RET. No target or source assembly is added.

Three whole initialized data images /47 bytes retain actual original definitions,
AUX metadata and source/PE permissions:shared CPU state8 at0x0066D23C, complete
Software\Microsoft\Direct3D literal28 at0x0065DE70 and complete DisableMMX11
at0x0065DE8C. The scoped type0/storage3 _isMMX field has original signed initial
value-1; it is not BSS/zero-fill and is not claimed runtime-immutable. The whole
8-byte source image also preserves the independent CPU-optimization field.
R188's registry path/import graph and R192's whole dispatch/state graph replay
independently, preserving their immutable manifests and canonical decisions.

**Inference and limits.** The explicit registry disabling, cached processor
policy and complete independently associated original helper support library
ownership. Original source symbols remain associations, not recovered target
names. Original compiler/assembler profiles, runtime environment and later cache
values remain unknown. No compiler-emission claim, reconstructed C++/assembly,
private type instance, ABI declaration, mapping or exact unit is introduced.
The original COFF/source facts are checked directly; no new cold probe is needed.

**Acceptance.** Replay `scripts/repo-python scripts/verify-sdk-mmx-origins.py`;
manifest SHA `1c7a8cae02c86607aa0ce6013e4dad6ad74a8c1e4507069f348c6c4337b79820`.
Exactly one function/origin row changes fromaee5fd3. All prior configuration
evidence files, all902 authored bodies /1956112 bytes, the complete R008 helper
snapshot and sixty exact inputs stay unchanged. All2429 public checks pass,
including twelve guards for duplicate helper acceptance, false non-inventory/
compiler helper classification, truncated policy/CPUID/literal, omitted fields,
wrong helper/API identity and false source/exact credit. Local target/tracking/
project/query markers, complete source/CFG/API/import/data and R188/R192 replay,
exact guard, fresh598-pending scan, progress and whitespace checks pass. Public
MCP acceptance remains waived.

Origin totals are3753 resolved:949 authored,2228 library and576 compiler;
598 pending and2804 excluded. Exact stays60 functions /9883 bytes and60 units
across eleven objects. Full origins and50%-exact milestones remain unfinished.
Next reconcile three graphics SDK gateways /326 provisional bytes at0x00604C82,
0x0060508B and0x00605B61 through whole original source/callee/data/EH graphs and
independent accepted Graphics parents. The private structural discovery is
only a shortlist; every real field must be independently bound before an
unmasked whole comparison can support any new origin decision.

## R195 — complete graphics SDK gateways, shader parser and texture policy

R195 accepts eighteen library candidates /9276 code bytes. Exactly eighteen
function/origin row pairs change from b2a1750; every provisional code extent
stays fixed. Their complete original source sections total9643 bytes, including
367 inline parser jump/selector bytes outside the independently derived code
extents. These tables are compared in full, never masked away or truncated.

| Entry | Code bytes | Original SDK source association |
| --- | ---: | --- |
| `0x00604C82` | 100 | `_D3DXAssembleShader@24` |
| `0x0060508B` | 124 | `_D3DXCreateRenderToSurface@28` |
| `0x00605B61` | 102 | `_D3DXCreateTexture@32` |
| `0x0060E599` | 1219 | `?Assemble@CD3DXAssembler@@QAEJPBXIPBDIKPAPAUID3DXBuffer@@22@Z` |
| `0x00605AE8` | 40 | `_D3DXCheckTextureRequirements@28` |
| `0x0060E0E0` | 1013 | `?d3dxasm_parse@@YAHXZ` |
| `0x0060C263` | 310 | `?Error@CD3DXAssembler@@QAAXPADZZ` |
| `0x0061FD22` | 232 | `?GenerateStringBuffer@CD3DXSzStack@@QAEJPAPAUID3DXBuffer@@@Z` |
| `0x006057BE` | 810 | `?CheckTextureRequirements@@YAJPAUIDirect3DDevice8@@PAI111KPAW4_D3DFORMAT@@W4_D3DPOOL@@W4_D3DRESOURCETYPE@@@Z` |
| `0x0060D291` | 1304 | `?Token@CD3DXAssembler@@QAEHXZ` |
| `0x0060D7A9` | 2188 | `?Production@CD3DXAssembler@@QAEXI@Z` |
| `0x006051B8` | 36 | `?D3DXGetFormatInfo@@YAPBU_D3DXFORMAT_INFO@@W4_D3DFORMAT@@@Z` |
| `0x006052BF` | 226 | `?D3DXFindClosestDeviceFormat@@YA?AW4_D3DFORMAT@@PAUIDirect3DDevice8@@KW4_D3DRESOURCETYPE@@PBU_D3DXFORMAT_INFO@@@Z` |
| `0x0060CF9B` | 169 | `?SetConstant@CD3DXAssembler@@QAEXKPAUD3DXVECTOR4@@@Z` |
| `0x0060CAB0` | 169 | `?DecodeMask@CD3DXAssembler@@QAEKPAD@Z` |
| `0x0060CB59` | 161 | `?DecodeSwizzle@CD3DXAssembler@@QAEKPAD@Z` |
| `0x0060CBFA` | 929 | `?DecodeRegister@CD3DXAssembler@@QAEKPADKH@Z` |
| `0x0060EB24` | 144 | `?D3DXDebugMute@@YAXH@Z` |

**Original source and target observations.** The source graph reopens the pinned
d3dx8.lib, original member names/offsets, full section/AUX/definition metadata,
and every real relocation. Thirty complete code sections /10340 bytes, sixty-six
initialized source data sections /4902 bytes and three complete BSS sections
/3044 bytes retain all bytes, actual source definitions and PE permissions.
These are source-carrier comparison totals, not claims of disjoint native
coverage. All511 genuine fields bind through independently owned complete
source sections, prior accepted anchors, real PE imports or the original
absolute CRT __except_list definition. FS displacement0 is not fabricated
PE data. The full shader parser tables and its original mutable state are
preserved, alongside the full format table1588 and its genuine end-pointer.
No private FORMAT_INFO or assembler object layout is declared or instantiated.

AssembleShader100 calls original assembler constructor169, Assemble1219 and
destructor143. The substantive library policy, tokenizer1304, error reporting310,
production2188, parser1013, register/mask/swizzle decoders929/169/161 and constant
policy169 have complete source-defined call/data graphs. Their normal returns,
shared branches and generated EH cleanup/resume roots are reconciled. Four
whole EH code carriers /240 bytes retain fifteen already accepted interior
compiler candidates unchanged; no duplicate compiler credit is added.
The parser has a guarded EAX0..48 table49 /196 bytes. Production has a guarded
EAX0..46 byte selector47 and full table31 /124 bytes:171 bytes together. CFG
traversal starts at the actual function entry, discovers every switch case,
and verifies every decoded instruction; table labels are not invented roots.

CreateRenderToSurface124 retains argument validation, allocation54, original
constructor39, Init79, deleting wrapper28, failure cleanup and output publication.
CreateTexture102 and the public requirements wrapper40 retain complete standard
COM calls and the full internal requirements810, format lookup36 and closest-
device-format226 policies. The original mutable DebugMute144 preserves its
actual loader/lookup/cache guards, both callback slots and its indirect tail.
Assemble's ValidatePixelShader/ValidateVertexShader lookups and calls remain
dynamic; no final runtime callee or private callback ABI is invented.

Twenty-seven independent full SDK/CRT source anchors are reopened from their
immutable original evidence, with full original primary extents and unmasked
fields. The old complete RenderToSurface36 and Buffer28 owning vtables retain
all actual entries, including previously proved weak fallbacks. Eight actual
import identities are parsed independently. R184/R185 debug, file and buffer
source graphs, R186 full interface/GUID graph, R187 explicit destructor controls
and R190 natural EH evidence replay. Prior library/compiler decisions and all
original evidence files stay fixed. The five original complete authored game
parents at0x00401540,0x00401110,0x004017A0,0x00401B20 and0x00401C20 retain their
whole CFG/body snapshots and actual gateway call sites; they supply context,
not standalone SDK ownership or new game acceptance.

**Compiler observations and limits.** A cold pinned build of
`tests/origin_probes/GraphicsSdkGatewayProbe.cpp` supplies eleven whole natural
public-interface controls /454 bytes and the entire readonly section64, with
all85 actual header hashes. The original public declarations independently
confirm four SDK WINAPI entries. Public COM controls observe Device slots
24/28/32/36/80, Direct3D CheckDeviceFormat40, Buffer pointer/size12/16 and
IUnknown Release8. The complete48-byte observer records real D3DCAPS8 size212,
TextureCaps60, texture/volume maxima88/92/96, display-mode size16/format12,
creation-parameters size16/device-type4 and public resource/capability enums.
A separate guarded cdecl callback control observes GetProcAddress and an
indirect call without fixing any runtime destination. Probe flags are explicit
reproducibility settings; no executable-wide historical compiler profile or
new target byte equality is inferred from these compiler observations.

Seven original unknown snapshots /405 bytes stay unchanged:assembler
constructor169/destructor143, RenderToSurface constructor39, Buffer constructor24,
DwStack destructor14, and the two GetLastError accessors8/8. Whole source
association and a library caller do not resolve their compiler-versus-explicit
lifetime or short-body alternatives. No private owner instance, target patch,
C++ reconstruction, ABI declaration, mapping or exact unit is introduced.

**Acceptance.** Replay `scripts/repo-python scripts/verify-sdk-graphics-origins.py`;
manifest SHA `922cd31ed6c986c5719c42d8a342b38b4ce0e0a722f11e3b6e42ed48e92a5998`.
Original-state evidence replay passed before the bounded canonical write, and
accepted-state full source/callee/data/EH/switch/public-ABI replay passes after
readback. All2444 public checks pass, including fifteen new guards against
partial tables/data, omitted/fabricated fields, false lifetime/source/private-
ABI/exact credit, missing previous interior entries and fixed dynamic callees.
Target/tracking/project/query attestations, the unchanged exact-input guard,
902 authored bodies /1956112 bytes, fresh580-pending scan, progress and whitespace
checks pass. Public MCP acceptance remains waived.

Totals are3771 resolved:949 authored,2246 library and576 compiler;580 pending
and2822 excluded. Exact remains60 functions /9883 bytes /60 units across eleven
objects. The full origin goal and50%-exact milestone remain unfinished.
Next reconcile the five R196 cube/volume/render-to-env SDK gateways identified
in the handoff; their private masked associations are diagnostic only.

## R196 — cube/volume gateways and complete EnvMap initializer

R196 accepts six library candidates /545 bytes. Exactly six function/origin row
pairs change from118e93e; all extents and all earlier evidence remain unchanged.

| Entry | Complete bytes | Original SDK source association |
| --- | ---: | --- |
| `0x00605B10` | 40 | `_D3DXCheckCubeTextureRequirements@24` |
| `0x00605B38` | 41 | `_D3DXCheckVolumeTextureRequirements@32` |
| `0x00605BC7` | 95 | `_D3DXCreateCubeTexture@28` |
| `0x00605C26` | 109 | `_D3DXCreateVolumeTexture@36` |
| `0x00605107` | 126 | `_D3DXCreateRenderToEnvMap@24` |
| `0x00609F9E` | 134 | `?Init@CD3DXRenderToEnvMap@@QAEJPAUIDirect3DDevice8@@IIW4_D3DFORMAT@@H1@Z` |

**Original source and target observations.** Twelve complete original SDK code
sections /1905 bytes, five initialized source sections /1624 bytes and two
whole BSS slots /8 bytes compare unmasked with all39 genuine fields. Actual
source definitions/AUX, section bounds and PE permissions are retained. The
four cube/volume gateways preserve parameter forwarding to the independently
accepted R195 requirements810 and their actual standard device creation slots.
Every return, guard, failure path and instruction is reached from the original
entry; no padding or switch table is invented. Source-carrier totals may share
native data with earlier proof graphs and are not new exact coverage.

CreateRenderToEnvMap126 retains argument validation, allocation, original
constructor104, Init134, generated deleting wrapper28, failure cleanup and output
publication. Init134 performs complete texture-requirements validation before
retaining the device through the actual AddRef protocol and publishing its
original state/descriptor fields. It calls the previously accepted public
CheckTextureRequirements40. The whole EnvMap owning table52 retains all13 actual
source fields, original weak-fallback metadata and prior interface context;
this is initialized-data provenance, not new ownership for every callback.
Operator-new14, deleting wrapper28 and ScoreFormat117 are independent full
original source anchors. Three actual PE imports and both mutable debug slots
retain their original loader/lookup/guard/indirect-tail behavior through R195.

The unchanged R195 manifest and verifier independently replay its full shader,
parser, format and debug graph, prior interface/EH/destructor evidence, and all
old accepted ownership decisions. Its pinned shared replay also checks this
new bounded source graph. The original absolute CRT definition and eleven
natural public controls are retained provenance, not new actual FS fields or
new compiler/ABI credit. All prior configuration evidence stays byte-identical.

**Compiler observations.** The new
`tests/origin_probes/CubeVolumeGatewayProbe.cpp` cold-builds eight whole public
controls /305 bytes and the entire readonly observer28 with85 real header hashes.
Five original declarations confirm SDK WINAPI decoration24/32/28/36/24. Actual
public COM controls confirm CreateCubeTexture slot88, CreateVolumeTexture slot84
and EnvMap GetDesc slot16. The seven original public observer values are
[5,4,16,0,4,8,12]:cube/volume resource enums, complete D3DXRTE_DESC size16 and its
Size/Format/DepthStencil/DepthStencilFormat offsets. This original EnvMap API
has no MipLevels field or extra factory argument. The private Init prototype
and any extra owner fields stay separate from those public declaration facts.
Probe flags are reproducibility settings, not an executable-wide compiler
profile. No private owner is instantiated or embedded.

**Retained unknowns and next dependency graph.** Constructor0x0060B728 /104
stays unknown; a public factory and original vtable do not distinguish automatic
member initialization from explicit lifetime policy. Original R186 Face35 at
0x0060BDED remains non-inventory and End227 at0x0060BE10 remains unknown. Their
original unresolved-callee-context records, source/body fingerprints and
canonical snapshots remain untouched; no partial comparison becomes acceptance.

A separate private diagnostic expanded their source chain through EndScene177
at0x0060BD3C, Render1421 at0x0060B7AF, Setup3892 at0x0060A7F4, FilterTexture740
at0x0060779F, surface/volume loading, blit selection and pixel codecs. The private
`.analysis/r196-filter-discovery.json` retains172 discovered source sections
/27710 bytes and45 unresolved source-owner/binding cases. These totals are
structural discovery only. External GUIDs, real weak vector-deleting fallbacks,
CRT vector-iteration helpers, codec switch tables and existing math aliases need
independent source closure. Do not guess weak aliases, cold-compare an incomplete
owner, or grant End/render/filter/codec origins from a public factory alone.
No origin decision is made for any of this incomplete expanded chain.

**Acceptance.** Replay `scripts/repo-python scripts/verify-sdk-cube-volume-origins.py`;
manifest SHA `1f6e40980b678af117d09e65999e3506b437e7dec4f81c47630a2eefe3d39ad1`.
Original-state evidence replay passes before the bounded write and accepted-state
whole source/CFG/field/data/previous-evidence/public-ABI replay passes after
readback. All2459 public checks pass, including fifteen guards for false
constructor/callback/source/private-ABI/exact credit, incomplete fields/bindings,
wrong requirement target, incomplete table and invented public descriptor fields.
Target/tracking/project/query attestations, exact-input guard,902 original
authored bodies /1956112 bytes, fresh574-pending scan, progress and whitespace
checks pass. Public MCP acceptance remains waived.

Totals are3777 resolved:949 authored,2252 library and576 compiler;574 pending
and2828 excluded. Exact remains60 functions /9883 bytes /60 units across eleven
objects. The full origin goal and50%-exact milestone are unfinished. The next
bounded R197 task closes the software filter/lock/blit/codec prerequisite graph,
retaining all lifetime, weak-reference and callback alternatives until proven.

## R197 — whole resource-lock policies and original public COM/GUID evidence

R197 accepts two library candidates /1902 bytes. Exactly two function/origin
row pairs change from1b51fe7. The immutable manifest is
`config/sdk-resource-lock-origin-evidence.json`, SHA
`18b992174e5b4d8c86ef8e3a37a85c3041dadaf363e8e476fa15e09f1d594751`;
replay with `scripts/repo-python scripts/verify-sdk-resource-lock-origins.py`.

| Target | Whole source/code bytes | Original symbol |
| --- | ---: | --- |
| `0x00614BE7` | 1043 | CD3DXLockSurface::Lock |
| `0x00614FFF` | 859 | CD3DXLockVolume::Lock |

Both complete function COMDATs come from original SDK member1511402, with
actual source definitions/AUX metadata, all11 genuine fields and complete
unmasked source/target equality. All684 instructions are reachable from the
real entries, including every branch and error path. Each method returns with
24-byte cleanup. The source symbols identify thiscall methods; no canonical
ABI or private owner/D3DX_BLT layout is declared or instantiated.

The source graph independently owns three complete16-byte GUID sections from
SDK init.obj member333374:IID_IDirect3DBaseTexture8 at0x0065C3FC,
IID_IDirect3DTexture8 at0x0065C3EC and IID_IDirect3DVolumeTexture8 at0x0065C3CC.
Their full immutable source bytes equal cold INITGUID definitions from the
original public header and the complete readonly native objects. The three
accepted source anchors are UnlockSurface105, UnlockVolume22 and DebugMute144;
all271 original bytes and genuine fields replay independently from existing
records. Both Unlock bodies additionally have complete reachable CFGs65 and
five indirect calls. Original R008 hashes retain their source-hash meaning.
Unchanged R196/R195 full source graphs and ordinary controls replay first.

`tests/origin_probes/ResourceLockProbe.cpp` cold-builds15 whole natural public
COM controls354 bytes,47 complete GUID definitions752 bytes and readonly
layout124 bytes. All63 ordinary emitted sections and84 original included
headers are pinned and compared. Complete public declarations verify
GetDesc32, GetContainer28, GetDevice12, LockRect/LockBox36,
UnlockRect/UnlockBox40, GetLevelCount52, CreateImageSurface108, CopyRects112
and Release8. The actual Lock methods contain17 indirect calls. These are
public slot/type observations; no concrete runtime COM callee is asserted.
GetLevelCount52 is distinct from GetSurfaceLevel/GetVolumeLevel60. Structure
observations include complete32-byte surface/volume descriptors, locked rect8,
locked box12, RECT16 and D3DBOX24 with original field offsets and enum values.
All cold public data is retained even when not a selected target GUID.

The larger filter/blit/codec chain remains unresolved. Private expansion parses
40 actual COFF weak records with same-member scalar-deleting fallback bodies28,
then reaches371 source carriers /43875 bytes with no diagnostic field-image
failures. F2IBegin has two actual source-static storage3 owners and placements;
their scoped identities are preserved. Full CFG discovery succeeds for229
carriers; Codec::Create, BltBox2D and two indirect-tail helpers still need
independent whole switch/EH/dispatch evidence. All original anchor dependencies
must be replayed independently before acceptance. The full CRT ??_L carrier98 and _floor carrier289 must remain
complete; their short primary/provisional extents cannot replace the retained
unwind/shared-entry context. These discovery observations receive no origin
credit. All earlier protected lifetime/getter alternatives remain unchanged.

Original-state and accepted-state complete replays, canonical readback,
attested local Ghidra/query identity, exact/authored guards, all2475 CI checks
including16 provenance guards, fresh triage, generated progress and whitespace
pass before handoff. Public
MCP acceptance remains waived. Totals are3779 resolved:949 authored,2254
library and576 compiler;572 pending and2830 excluded. Exact remains60
functions /9883 bytes /60 units across eleven objects; all902 authored bodies
/1956112 bytes, source/header/build/match inputs and previous evidence remain
unchanged. The full origin goal is active; R198 continues the software chain.

## R198 — complete software blit/codec graph and explicit input constructors

R198 accepts108 library entries:68 complete policies and40 explicit input
constructors. Exactly108 function/origin row pairs change from31117d6. The
immutable manifest is `config/sdk-blit-origin-evidence.json`, SHA
`6d537daa5c3605c37ac3e72ba1d09eba6702689f040f6b34f20ae3ba2a3d3b10`. Replay with
`scripts/repo-python scripts/verify-sdk-blit-origins.py`.

**Whole source and extent observations.** Accepted entries cover36143 code
bytes plus92 actual selector-table bytes. Codec::Create at0x0061A4CC expands
from1824 to1884:the original unsigned EAX<=14 guard owns15 real local-label
DIR32 fields and60 table bytes. BltBox2D at0x006131C5 expands from1027 to1059:
its unsigned ECX<=7 guard owns eight real local labels and32 table bytes. These
are the only canonical extent changes. End227 at0x0060BE10, EndScene177,
Render1421, Setup3892, Filter740, surface/volume loads, software blits, pixel
conversions, DXT policies and helper routines retain their entire original
source bodies, all exits, switch targets and EH roots.

The graph reopens371 complete original source sections /43875 bytes:
233 code carriers41451,135 initialized-data carriers2412 and three BSS
carriers12, with all1363 genuine relocation fields. Complete unmasked images,
actual COFF definitions/AUX metadata and whole reachable CFGs replay for every
code carrier. These are source-carrier counts:two original D3DXCOLOR default
constructor carriers share native0x0060559F, so233 carriers represent232 unique
native bases. This overlap earns no additional acceptance. Forty actual
storage105 weak references preserve AUX search characteristic2 and their
same-member scalar-deleting fallback definitions28; no spelling-derived alias
is substituted. Forty-nine interior compiler rows stay unchanged. All81
independently accepted anchors replay their original source provenance.

Source-static F2IBegin placements0x00615BC6 and0x0062572C each retain35 bytes,
actual storage3 owner/section/symbol-index identity and source hash
`53abbe0cd64d7ead94c4b5bf02740b215e87f8ca636971454d363fe2fbf3b9c8`.
They are distinct source placements; neither a global-name binding nor folding
is inferred. Initial callbacks56/47 at0x00611E9C/0x00611F00 own the complete
initialized8-byte callback carrier0x0066CF68. Full zero/nonzero CPU paths bind
the accepted isMMX policy and actual scalar/packed function fields, stores and
memory/register tails. Both runtime alternatives remain represented; the
runtime CPU result and mutable slot contents are unknown.

**Constructor ownership inference.** Thirty-seven derived constructors /1008
bytes and three base constructors /1334 bytes have complete original source
bodies, genuine fields and whole typed callers. Their source definitions take
an external `D3DX_BLT*` input; the base Codec also takes UINT/DWORD and returns
with12-byte cleanup, while the other39 return with4-byte cleanup. Ownership
is inferred from this combined source/ABI/caller evidence and independent cold
controls, not from a short matching body, symbol spelling or RET4 alone.
`CodecConstructorRoleProbe.cpp` uses complete generic observation classes with
real pointer/format/flag members. Five whole constructor controls distinguish
explicit pointer-base52/RET12 and derived41/RET4 from explicit default33/RET0,
implicit default31/RET0 and implicit copy37/RET4. All23 ordinary emitted
sections,85 original headers and the full28-byte generic observation layout
are retained. These generic sizes16/8 do not declare the private SDK layout.

Six lifetime alternatives remain unknown /438 bytes:EnvMap constructor104,
LockVolume constructor6, TF_Row vector-deleting helper76 and Codec/CodecDXT/
CodecYUV destructors19/160/73. All earlier protected lifetime/getter/game/CRT
alternatives, including R195 seven cases405, retain their accepted evidence.

**Public and retained evidence.** `PixelCodecPolicyProbe.cpp` cold-builds eight
whole public API/COM/cdecl controls332 bytes, the initialized callback carrier8
and readonly public observation layout72. All ten ordinary emitted sections
and85 original headers replay. WINAPI cleanup is16/32/32/40/44 for the five
public functions; EnvMap End is public COM slot40. Ordinary callback controls
retain both function choices and genuine lazy-initialization stores/tails.
Compiler profiles are reproducibility controls, not an executable-wide claim.

Original CRT vector construction/destruction anchors independently replay
whole COMDATs98/96, including real source-internal cleanup entry roots74/72.
Their original provisional ledgers and records remain unchanged. The entire
289-byte floor carrier, including its225-byte SSE entry, and the original
39-byte __ftol source replay independently. Absolute __except_list remains an
actual absolute source symbol, not invented PE data. R186's opaque Face/End
records and every previous evidence manifest stay immutable. Only the exact
frozen End original-to-R198 accepted row pair can pass historical readback;
R198 supplies separate complete positive evidence. Seven reviewed replay-script
content transitions use fixed original/accepted hash pairs, never arbitrary
new digests or broad ownership exceptions.

**Acceptance.** Original-state whole replay passes before the bounded write;
accepted-state whole replay and exact canonical readback pass afterward.
Retained floor, x86 dispatch, MMX and R197/R196/R195 source graphs and cold
controls replay. All2505 CI checks pass, including30 new provenance guards.
Target/project/query attestations,902 original authored bodies /1956112 bytes,
all exact-input guards, fresh464-pending triage, progress and whitespace pass.
Public MCP acceptance remains waived. No reconstructed source, private SDK
owner/layout, canonical ABI, mapping or exact credit is added.

Totals are3887 resolved:949 authored,2362 library and576 compiler;464 pending
and2938 excluded. Exact remains60 functions /9883 bytes /60 units across eleven
objects. The full origin goal is active. R199 next reviews the six image
load/save source candidates and their original dependency graph; the source
survey is diagnostic until every real field/whole owner is independently closed.

## R199 — whole image/JPEG/PNG/zlib policies and state/nonreturn source flow

R199 accepts95 library candidates /24062 whole source bytes:23926 code and
136 genuine state-table bytes. Exactly95 function/origin row pairs change from
863a06a. The immutable manifest is
`config/sdk-image-chain-origin-evidence.json`, SHA
`77ea2fe0c65ac983a29b752f1724a6648a2472021fa474074c80c55fceb5504a`. Replay
`scripts/repo-python scripts/verify-sdk-image-chain-origins.py`.

**Source observations and ownership inference.** Six initial image load/save
methods /4749 bytes from original SDK member1516190 close through89 additional
ordinary source policies:JPEG memory/error/decompression, PNG read/transform/
CRC/allocation and zlib inflate workers. Ninety-five complete source function
definitions, full target images and genuine typed source references establish
library ownership. Namespace/function meanings remain source-based inferences;
SDK archive provenance includes bundled third-party code. Short global C-style
policies retain complete incoming call or initialized function-pointer fields;
an empty/constant-return byte shape alone supplies no ownership. Names remain
provisional; no canonical private signature or object layout is declared.

The graph reopens449 complete original source carriers /62866 bytes:
212 code47056,236 initialized data15802 and one BSS8, with all904 genuine
fields. Every real original section definition/AUX record, scoped static field,
source image, permission and complete unmasked linked image replays. All212
whole normal/EH/state/nonreturn CFGs consume their code/table fields. There are
109 complete independently accepted SDK/CRT anchors /26174 bytes and268 fields,
one actual imported API, no guessed weak aliases and one unchanged R022
interior compiler row8. The complete original JPEG message-pointer/string bank,
zlib fixed tables/masks and initial MMX state remain full source carriers;
writable initial values do not identify runtime state.

**Three complete state tables.** Inflate at0x00629471 expands815 to871,
blocks at0x0063A903 expands1907 to1947 and codes at0x0063D7EC expands1340 to1380.
The full source tables own14/10/10 actual local-label DIR32 fields, totaling
56/40/40 bytes. Full root-to-index path analysis verifies unsigned bounds13/9/9
and actual EAX/EAX/ECX indexes. The blocks dispatcher preserves both separately
reaching bounds. Inflate's nonvolatile EBP has four source push/pop definitions:
13,31,13,13. The31 division constant does not reach the table comparison or
indexed jump; both restoration paths are retained. All paths reaching the
comparison/indexed dispatch carry13. Rewriting the index or flags after a guard
invalidates the proof. No extra label is treated as a root, inferred selector
is introduced, or body is cropped to a code-only extent.

**Whole nonreturn source tails.** The original callbacks at0x0060F6FF /28,
0x00610141 /12 (non-inventory),0x0062245E /27 and0x00622671 /30 bind complete
longjmp121 or exit17 anchors and original public noreturn declarations. Their
complete source suffix is one actual POP ESI or INT3 after the terminal call.
It remains in source/target comparison and instruction counts, separately from
normal reachability; it is not an invented return, alignment or padding.
Exactly three canonical callback extents expand by one byte:27->28,26->27 and
29->30. Together with the three table expansions these are the only six extent
changes. Original setjmp3 /123 from R107 retains its exact old source/relocation
record; its FS:[0] field owns the actual absolute CRT __except_list symbol.

`ImageJumpPolicyProbe.cpp` cold-builds six whole ordinary/public controls132
bytes, all seven ordinary emitted sections,86 original headers and readonly
observation68. Complete generic notify/jump and notify/destroy/exit policies
independently reproduce a saved-register POP ESI source suffix; direct jump
reproduces INT3. Original setjmp lowers to __setjmp3. Public image-info and
surface-save declarations retain WINAPI12/20. Public jmp_buf64 and
D3DXIMAGE_INFO28/its seven offsets are observed independently. The generic
observer68/state offset4 is a complete observation class, not the JPEG/PNG
private layout; actual private pointer/field semantics remain incomplete.
Compiler profiles are reproducibility controls, not executable-wide claims.

**Retained alternatives and acceptance.** CD3DXFile destructor11 at0x0060C120
and CD3DXImage destructor89 at0x0060EBCD remain unknown; whole source/calls alone
do not distinguish explicit from compiler-generated member cleanup. All earlier
protected alternatives, previous manifests/records and prior verifier sources
remain unchanged. Full R198 and R107 replays pass, then both original-state and
accepted-state whole R199 source/CFG/field/public-control replays pass. Canonical
readback, target/project/query attestations,902 authored bodies /1956112 bytes,
all60 exact-input guards, fresh369-pending triage, progress and whitespace pass.
All2541 CI checks pass, including36 new provenance/state/nonreturn guards.
Public MCP acceptance remains waived. No reconstructed source, private owner/
layout, canonical ABI, mapping or exact credit is added.

Totals are3982 resolved:949 authored,2457 library and576 compiler;369 pending
and3033 excluded. Exact remains60 functions /9883 bytes /60 units across eleven
objects. The full origin goal stays active. R200 reviews six remaining SDK
texture/error/text/sprite policies and their complete original dependency graph.

## R200 — whole texture/text/sprite policies and independent UUID/stack/array evidence

R200 accepts11 candidates /5581 bytes:9 library policies5431 and2 compiler
vector-deleting wrappers150. Exactly11 function/origin row pairs change from
777099e, with no extent changes. The immutable manifest is
`config/sdk-presentation-origin-evidence.json`, SHA
`771ae0e2e563cdb35dfbaf46ed752a59f29f15ba6274badb88c621a28a1a4eb1`. Replay
`scripts/repo-python scripts/verify-sdk-presentation-origins.py`.

**Source observations and ownership inference.** The six texture-load/save,
error-text, text-initialize/draw and sprite-draw roots expand to text reset,
sprite creation and sprite QueryInterface policies. Full original SDK source,
genuine typed references and complete policy control flow establish library
ownership; source names do not declare complete private owner layouts.
The two complete original vector-deleting wrappers at0x00605CDF and0x00605D2A
retain array/scalar flag2, optional-free flag1, actual array cookie, whole
vector destructor iterator, destructor pointer/direct call, both delete paths
and thiscall ret4. Their observed stride16/4 is a compiler operand, not a
reconstructed SDK class layout. Natural complete generic virtual/nonvirtual
array classes independently emit the same generated protocol and distinguish
virtual/nonvirtual declarations. Cold wrappers are84 bytes versus original75;
this establishes generated role, without exact credit or forcing byte identity.

The graph reopens70 whole original source sections8745:25 code7777,44 data964
and one BSS4, with all175 genuine fields and25 complete normal/EH/indirect CFGs.
The25 source code carriers map24 native bases:two genuine scalar-deleting
source COMDAT owners fold at0x006049BC, each retained separately. Five whole
non-inventory sprite methods remain source evidence without added candidate
credit. All original definitions/AUX, scoped field owners, full raw images,
permissions and unmasked linked images replay. Thirty-three complete retained
SDK/CRT anchors6911/all93 fields retain their original records. Four interior
R022 compiler rows40 remain unchanged; no source extent hides an inventory row.

**Independent foreign UUID and actual stack alias.** IID_IUnknown16 at0x00660E58
comes from original UUID library member328782/section4, not d3dx8.lib. Its full
source definitions/hash and readonly target bytes reopen independently. The
cold public __uuidof(IUnknown) constant agrees with that source; the whole
public ID3DXSprite GUID also agrees with its SDK source. DrawTextAW's
__alloca_probe binds the actual same-section/same-offset alias of the complete
R006 __chkstk61 at0x00642510. Original primary/alias definitions and the entire
R184 retained record are unchanged. Natural _alloca lowering independently
observes EAX size rounding/alignment and the actual helper relocation; no fake
cdecl stack-helper declaration is introduced.

`PresentationPolicyProbe.cpp` cold-builds all69 ordinary emitted sections,
17 complete code controls727,86 original headers and full public observation40.
Original public error-text/save-texture calls retain WINAPI12/16. Font DrawTextA
uses COM slot24; sprite Draw uses slot20. Complete generic array classes have
observed sizes8/4; GUID16, RECT16, VECTOR2 8 and MATRIX64 remain public facts.
No incomplete SDK owner is declared, instantiated or embedded. The compiler
profile is a reproducibility setting, not an executable-wide compiler claim.

**Retained alternatives and acceptance.** LockVolume constructor6 at0x00614BC6,
Image destructor89 at0x0060EBCD, Sprite constructor30 at0x00609AA4 and Sprite
destructor64 at0x00608F96 remain unknown189. Complete source/calls alone do not
resolve their explicit/implicit lifetime ownership. All earlier protected
alternatives, previous manifests/records and prior verifier sources remain
unchanged. Both original-state and accepted-state complete source/CFG/field/
cold-control replays pass. Prior anchors are reopened directly and their
immutable source/provenance inputs are pinned; unaffected recursive cold trees
are not redundantly rebuilt. Canonical readback, local target/project/query
attestations,902 authored bodies1956112,all60 exact-input guards,358-pending
triage, progress and whitespace pass. All2571 CI tests pass, including30 new
source/field/alias/UUID/compiler preservation guards. Public MCP acceptance
remains waived. No reconstructed source, private layout, canonical ABI,
mapping or exact credit is added.

Totals are3993 resolved:949 authored,2466 library and578 compiler;358 pending
and3044 excluded. Exact remains60 functions /9883 bytes /60 units across eleven
objects. The full origin goal stays active; the next R201 bounded SDK public
shader/error/font entries require independent complete source closure.

## R201 — whole shader/resource/font policies and original public declarations

R201 accepts15 library candidates /1403 bytes. Exactly15 function/origin row
pairs change from6caffec, with no extent changes. The immutable manifest is
`config/sdk-shader-font-origin-evidence.json`, SHA
`ac84edce06f5a9b4381dfe01d3f8f74db3ff087301b77edf7f6a2e484ffed584`. Replay
`scripts/repo-python scripts/verify-sdk-shader-font-origins.py`.

**Source observations and ownership inference.** Six public shader file/
resource A/W, wide error-text and indirect-font entries close through nine
resource/font/text policies. Full original SDK source definitions, complete
normal/EH/indirect control flow and genuine incoming call/vtable fields establish
library ownership. Five short policies12/31/35/38/38 retain their complete typed
incoming source references; matching byte shape alone grants no origin.
Private owner names remain source observations, without reconstructed layouts.

The graph reopens41 complete original sections5781:35 code2497,4 initialized
data244 and2 BSS3040, with all152 genuine fields. Thirty-five complete source
CFGs map34 native bases:two genuine scalar-deleting CD3DXFont source COMDAT
owners fold at0x006049A0, with both retained separately. Seven whole
non-inventory font methods remain source evidence without new candidate credit.
The full font vtable44, two original EH state/data images92 each, Font GUID16,
assembler BSS3036 and text-list BSS4 retain every actual definition, source
image, permission, scoped owner and unmasked comparison. Initial zero-fill
establishes original storage, not its runtime state. Fourteen interior R022
compiler rows154 remain unchanged. Twenty-two independently accepted whole
SDK/CRT anchors4688/all121 fields and12 actual Kernel32/GDI32 imports reopen.

**Independent UUID, alias and public controls.** The entire original UUID
IID_IUnknown16 source/readonly target at0x00660E58 and the full R006 chkstk61/
R184 alloca alias record at0x00642510 retain their original provenance. Actual
same-section/same-offset primary/alias definitions close the genuine field;
no stack-helper ABI is invented. `ShaderFontPolicyProbe.cpp` cold-builds all66
ordinary sections,17 complete controls437,86 original headers and full readonly
public observation88. The public __uuidof(IUnknown) and Font GUID definitions
independently agree with original UUID/SDK data sources.

Original SDK shader file/resource declarations retain WINAPI20/24; wide
error-text and font-create retain12. Original resource API observations retain
FindResourceA/W12, LoadResource/SizeofResource8 and LockResource4. GDI font-create/
delete retain4; original ANSI/WCHAR conversion declarations retain24/32.
Font DrawTextW uses public COM slot28, distinct from DrawTextA24. Natural
WCHAR allocation supplies EAX count*2 and actual alignment/alloca lowering.
Original public WCHAR2 and LOGFONTA60/all14 field offsets, LF_FACESIZE32 and
public enums remain independent header facts. No incomplete SDK owner is
declared, instantiated or embedded. Profiles are reproducibility settings,
not executable-wide compiler claims.

**Retained alternatives and acceptance.** Eight lifetime cases685 remain
unknown:Assembler constructor169/dtor143 at0x0060C12B/0x0060C1D4, File dtor11
at0x0060C120, Resource dtor14 at0x0060EA69, Font constructor27/dtor58 at
0x00608F7B/0x00608D8E, DwStack dtor14 at0x0061FB37 and Text dtor249 at
0x0061F125. Complete source/calls alone do not distinguish explicit policies
from compiler-generated member lifetime. All earlier protected alternatives,
previous manifests/records and prior verifier sources remain unchanged.

Original-state and accepted-state complete source/CFG/field/cold-public
replays pass, together with full R200 regression replay. Shared original
replay reopens all owned sources without populating its catalog from native
relocation destinations; immutable previous inputs remain pinned, without
redundant unaffected recursive cold trees. Canonical readback, local target/
project/query attestations,902 authored bodies1956112, all60 exact-input guards,
fresh343-pending triage, progress and whitespace pass. All2601 CI tests pass,
including30 new provenance/import/alias/UUID/scope guards. Public MCP
acceptance remains waived. No source/private layout/canonical ABI/mapping/
exact credit is added.

Totals are4008 resolved:949 authored,2481 library and578 compiler;343 pending
and3059 excluded. Exact remains60 functions /9883 bytes /60 units across eleven
objects. The full origin goal stays active. R202 next reviews six image-info/
surface/volume source entries and their complete original dependency graph.

## R202 — whole image-entry policies, backward cleanup exits and source peer distinctions

R202 accepts32 library candidates /3121 bytes. Exactly32 function/origin row
pairs change from8499a7e, with no extent changes. The immutable manifest is
`config/sdk-image-entry-origin-evidence.json`, SHA
`8a89de63380fd8916fcede566c1fbf241f775c45db4f5873f7921b623ca2d8a7`. Replay
`scripts/repo-python scripts/verify-sdk-image-entry-origins.py`.

**Source observations and ownership inference.** Six image-info/file/resource
and surface/volume memory-load roots expand through the same complete source
family to image-info-memory, surface/volume-save, file/resource-load and
texture/cube/volume-texture extended creation entries. Full original SDK
function definitions, all genuine fields and complete policy control flow
establish library ownership. Thirty-two initial candidate addresses have one
independently closed source association each. Source names do not declare
private owner layouts or grant byte-match/source/mapping credit.

The graph reopens44 whole original sections5899:41 code5775 and3 EH state/data
carriers124, with all174 genuine fields and41 complete normal/EH/indirect CFGs.
Twenty-three whole retained SDK/CRT anchors5415/all92 fields, the actual GDI
DeleteObject import and absolute CRT __except_list definition reopen. Private
source-static SaveSurface/SaveVolume and CreateTexture/CheckTextureRequirements
identities retain real member/section/symbol-index scope. The latter two whole
library policies1651/810 retain their R200/R195 snapshots. Two interior R022
compiler rows16 remain unchanged. Every source definition/AUX, entire raw
image, permission and unmasked linked comparison replays; no native observed
field destination populates the final source catalog.

**Whole backward cleanup exits.** Surface memory-load184 at0x00607005 ends
with JMP at182 to its internal cleanup instruction116. Volume memory-load188
at0x00607263 ends with JMP at186 to120. Their actual RET36 is earlier, at
130/133. Full source COMDAT extents and all-path CFGs consume every instruction
and field. The authored-only scanner's final-RET diagnostic does not indicate
an invalid SDK boundary:both complete trailing branches reach the original
cleanup/return block. No source tail is cropped, RET inserted or padding added.

**Eight real peer alternatives.** A shape-only survey associated each surface/
volume A/W file/resource wrapper with both public source names. Whole incoming
source fields distinguish the actual surface memory-load at0x00607005 from
volume memory-load at0x00607263. All eight wrong associations reopen their
complete original81/86-byte source and whole native counterpart, rebase every
actual field through independently owned definitions, and fail only in their
real mismatching callee fields. Complete positive and negative bodies remain
retained; masks, callee guesses and convenient cropped comparisons grant no
origin. The source-static namespace does not merge equal names across members.

`ImageEntryPolicyProbe.cpp` cold-builds32 complete original public API controls
1832,all80 ordinary emitted sections,85 original headers and readonly public
observation92. Image-info declarations retain8/12; surface/volume load variants
retain32/36 and public save20. Texture/cube/volume creation distinguishes memory
60/56/64, file56/52/60 and resource60/56/64 cleanup bytes. Original public
image-info28/all seven offsets, RECT16, BOX24, palette4, WCHAR2, GUID16,
resource-type values1/2/3/4/5 and relevant public enums remain independent
header facts. No incomplete SDK class is declared, instantiated or embedded.
Profiles are reproducibility controls, not executable-wide compiler claims.

**Retained alternatives and acceptance.** Image destructor89 at0x0060EBCD,
LockVolume constructor6 at0x00614BC6, File destructor11 at0x0060C120 and Resource
destructor14 at0x0060EA69 remain unknown120. All earlier protected alternatives,
previous manifests/records and prior verifier sources remain unchanged.
Original/accepted complete source/CFG/field/peer/backward-exit/public-control
replays and full R201/R200 regression replays pass. The prior-snapshot audit
finds no earlier exact original function/origin snapshot affected by the32
transitions. Canonical readback, local target/project/query attestations,
902 authored bodies1956112, all60 exact-input guards, fresh311-pending triage,
progress and whitespace pass. All2634 CI tests pass, including33 new guards.
Public MCP acceptance remains waived. No reconstructed source, private layout,
canonical ABI, mapping or exact credit is added.

Totals are4040 resolved:949 authored,2513 library and578 compiler;311 pending
and3091 excluded. Exact remains60 functions /9883 bytes /60 units across eleven
objects. One thousand of the original1311 remaining candidates are now resolved;
the full goal remains active. R203 next reviews six original PNG/read/quantize/
YCbCr conversion policies and their complete dependency/source data graph.

## R203 — whole PNG read/quantization policies and source-scoped packed conversion data

R203 accepts six library policies / 2807 bytes with no extent changes. Replay
`scripts/repo-python scripts/verify-sdk-png-packed-origins.py`; the immutable
`config/sdk-png-packed-origin-evidence.json` SHA-256 is
`c3112e66bfce14d918e18c666ba26220ee70bae92b79875fa02f8ffbbb13d532`.
The pinned original SDK archive and complete member identities reopen; names
and native relocation destinations alone do not establish ownership.

| Address | Whole bytes | Original SDK policy | Member offset |
| --- | ---: | --- | ---: |
| `0x006227F1` | 192 | D3DX::png_read_init | 1828564 |
| `0x00622DFD` | 122 | D3DX::png_read_rows | 1828564 |
| `0x00622EC4` | 256 | D3DX::png_read_end | 1828564 |
| `0x006235B9` | 1619 | D3DX::png_set_dither | 1842088 |
| `0x0062E461` | 302 | D3DX::MYCbCrA2RGBA | 1602398 |
| `0x0062E58F` | 316 | D3DX::MYCbCrA2RGBALegacy | 1602398 |

**Complete source and flow.** Fourteen complete original sections / 3056 bytes
retain six code bodies / 2807, seven initialized data sections / 241 and one
BSS section / 8. Every one of the 72 genuine fields binds through independently
owned definitions and its actual COFF addend, type, member, section and symbol
index. Full unmasked linked code/data bytes and all six complete CFGs replay.
Twenty complete retained SDK anchors / 3376 bytes and 161 fields remain literal
prior records, including the entire 30-byte png_error nonreturn source suffix.
There are no new interior compiler rows, import aliases or lifetime exclusions.
All earlier protected alternatives and accepted evidence remain unchanged.

**Mutable initial data and MMX state.** The whole writable initialized 48-byte
bank at `0x0066E2A8` belongs to original member 1602398, section 2. Source-static
labels retain offsets 0 (_const_sub128), 8 (_const_VUmul), 16 (_const_YVmul),
24 (_const_YUmul), 32 (_mask_highd) and 40 (_const_invert). The unused mask label
remains in the full carrier. Writable BSS / 8 at `0x0068E280` is the same member's
section 3, source-static _const_0. These prove initial images and allocation,
not runtime immutability; label spelling does not change writable source flags.
The complete 121-byte readonly PNG label bank at `0x0065F240`, all version/error
strings and their scoped definitions remain whole. The string 1.1.3 identifies
this zlib source observation, not the game's self-reported version.

Both entire packed kernels retain their original mnemonic observations and
11/13 actual DIR32 fields. Each has six PMADDWD and six PSRAD instructions;
legacy has two actual _const_invert fields at source offset 40, absent from the
other kernel. Neither source kernel contains EMMS; both return with MMX state
retained. A generated clear/reset sequence must not be substituted into either
original body. Pointer argument meanings and private PNG layouts remain unknown.

**Cold interface and intrinsic observations.** `PngPackedPolicyProbe.cpp`
cold-builds all 13 ordinary sections: twelve complete controls / 359 bytes and
the whole readonly scalar observation / 24 bytes. Two original public headers,
mmintrin.h and stddef.h, retain their file hashes. Six complete five-byte JMP
forwarders preserve the actual original COFF free-function signatures. Private
PNG tags stay opaque pointers. png_read_rows retains unsigned long (COFF K),
not unsigned int (I); conversion parameters keep neutral pointer names.
No private owner is instantiated, embedded or assigned a layout.

Six independent generic public-intrinsic controls observe saturated subtraction,
packed multiply-add, a shift-by-one policy, narrowing and interleave, plus the
separate subtraction control preserving MMX state. Five explicit _mm_empty
controls emit EMMS; the preserve-state control emits none. Complete bodies,
actual security-cookie fields, stores, returns and all emitted sections replay.
These controls establish compiler/interface observations, not a reconstructed
conversion implementation or an executable-wide compiler profile.

**Acceptance and preservation.** Original-state and accepted-state complete
source/data/field/CFG/anchor/cold-control replays pass. Full R202 regression and
R199's direct complete source/field/CFG/anchor replay with its own cold controls
pass; unchanged recursive earlier cold trees were not rerun. The prior-snapshot
audit finds no earlier exact original function/origin row affected by these six
transitions. Canonical readback changes exactly six function and origin rows,
with no size changes. Local target/project/query attestations, 902 authored
bodies / 1956112 bytes, all 60 exact-input guards, fresh 305-pending triage,
progress and whitespace checks pass. All 2666 CI tests pass, including 32 new
evidence guards. Public MCP acceptance remains waived by the user.
No reconstructed source, private layout, canonical ABI, mapping or exact credit
is added.

Totals are 4046 resolved: 949 authored, 2519 library and 578 compiler; 305 pending
and 3097 excluded. Exact remains 60 functions / 9883 bytes / 60 units across
11 objects. Of the original 1311 remaining candidates, 1006 are now resolved;
the full origin-review goal remains active. R204 next revisits the bounded six
SDK lifetime/PNG ownership alternatives documented in the handoff, preserving
unknown origin until whole source and independent ownership evidence suffice.

## R204 — whole PNG destruction and explicit/implicit SDK lifetime alternatives

R204 reviews all six SDK roots / 503 bytes. It accepts the entire 38-byte
D3DX::png_destroy_info_struct at `0x006255C6` as library policy and preserves
five lifetime roots / 465 bytes as unknown. The independently reopened 19-byte
base codec destructor also stays unknown. Replay
`scripts/repo-python scripts/verify-sdk-lifetime-alternatives-origins.py`;
`config/sdk-lifetime-alternatives-origin-evidence.json` SHA-256 is
`551ee19c54232b82c06f5c261470dd1b0dc22069a895026c2e108aa2b68b0162`.
No extent, reconstructed source, canonical ABI, mapping or exact state changes.

**Complete original source.** Seventeen whole sections / 762 bytes retain
12 code carriers / 642 and five data carriers / 120, all 54 actual fields and
12 full normal/EH CFGs. Every field binds through actual independently owned
original definitions and complete unmasked source/native comparison. Three
whole codec vtables / 48 and two EH data carriers / 72 remain source-scoped.
Two prior render-interface vtables / 88 retain literal accepted records.
Seventeen complete anchors / 3098 bytes and 70 fields reopen their original
SDK/CRT source and all prior bindings. The original absolute CRT __except_list
is independently retained; native FS zero storage is not a fabricated owner.

Three actual codec vector-deleting weak references reopen their COFF AUX
fallbacks to complete scalar-deleting source sections / 28 each. The R038 DXT
and base wrappers stay compiler-owned with unchanged canonical rows; the YUV
wrapper at `0x0061AC28` has no inventory candidate and earns no function credit.
Two full 18-byte EH code carriers retain complete cleanup and handler roots;
existing eight-byte R022 unwind rows remain unchanged. No source tail is cropped
at a first return or matched against a convenient shorter ledger span.

The accepted PNG policy guards both the info pointer-to-pointer and its value,
clears sixteen DWORDs, calls the independently owned whole png_destroy_struct
and resets the caller's pointer. The 64-byte clearing observation does not
establish a complete private png_info_struct layout. Its original mangled free
function signature is observed by a cold opaque-pointer five-byte JMP forwarder;
no PNG owner is instantiated or embedded.

**Evidence that preserves unknown origin.** Complete original source ownership
identifies the SDK class association, but a constructor/destructor symbol does
not establish explicit source policy versus compiler-generated outer lifetime
machinery. `SdkLifetimeAlternatives.cpp` supplies three independent generic
explicit/implicit outer-owner pairs. Original VC7.1 cold compilation emits
23-byte constructors with identical complete unlinked bodies but different real
owning-vtable symbols, and 10-/21-byte direct/conditional cleanup destructors
with identical whole bodies and actual operator-delete fields. No fields are
masked or cropped, and these generic bodies are never mapped to native owners.
The implicit alternatives contain independently defined member policies; their
outer constructor/destructor is implicit. Cleanup calls and conditional stores
therefore do not alone prove an explicit outer SDK lifetime body.

The target DXT nested cleanup loop, YUV Commit call, image recursive cleanup
and render initialization stores remain full target/source observations.
These generic controls do not reproduce those complete target policies or
prove a particular implicit implementation. Original C++ member declarations
and the corresponding outer lifetime source remain unknown. The five root
lifetimes and base codec destructor retain their canonical unknown rows; the
full six alternatives / 484 bytes and reasons are frozen for later evidence.
Do not infer that original SDK archive ownership settles the library/compiler
boundary, or repeatedly accept the same bodies from their mapped names.

All 27 ordinary cold sections / 470 bytes retain 24 complete emitted functions /
430, two complete generic vtables / 8, eight original public headers and the
full generic layout observation / 32. Placement-new helpers, implicit member
functions and generated deleting wrappers remain in the emission. Probe owners
are generic complete C++ classes, not partial private SDK owners. Compiler flags
are explicit reproducibility settings, not an executable-wide profile claim.

**Acceptance and preservation.** Original and accepted full source/data/field/
CFG/anchor/weak/public-control replays pass. Full R203 regression passes.
The actual accepted PNG transition affects no prior exact original function/
origin snapshot; potential lifetime snapshot impacts remain private audit
records, with no canonical transition for those unknowns. Exactly one function
and origin row changes; all previous manifests, source/ABI/mapping/match inputs,
902 authored bodies / 1956112 bytes and the 60-function exact baseline remain
unchanged. Target/project/query attestations, canonical readback, 304-pending
triage, progress and whitespace checks pass. All 2696 CI tests pass, including
30 new guards. The user continues to waive public MCP acceptance.

Totals are 4047 resolved: 949 authored, 2520 library and 578 compiler; 304 pending
and 3098 excluded. Exact stays 60 functions / 9883 bytes / 60 units across eleven
objects. The original 1311-candidate goal has 1007 resolved and 304 left and
remains active. R205 next investigates four bounded vector access parents and
two actual iterator helpers, with complete cold public-template alternatives;
its diagnostic shortlist grants no origin or target element-type declaration.

## R205 — complete vector bounds and source-scoped iterator policies

R205 expands the six-root / 318-byte shortlist through actual dependencies and
accepts 18 complete public VC7.1 vector/iterator policies / 615 bytes as library.
Replay `scripts/repo-python scripts/verify-vector-at-policy-origins.py`.
`config/vector-at-policy-origin-evidence.json` SHA-256 is
`50d18e8f574de56e427454e9eaaabfd257d0567a4fa9d5c68a463150a4bf635c`.
Exactly 18 function and origin rows change; every extent, original source/ABI/
mapping field and exact state remains unchanged. Generic element observations
do not identify private game types or permit instantiating incomplete owners.

The four whole at70 roots are `0x004093E0`, `0x00442060`, `0x004420B0` and
`0x00445310`. Newly accepted dependencies are mutable dereference19 at
`0x00409D80`, `0x00442280`, `0x004422D0` and `0x00445600`; const dereference16
at `0x0040A160`, `0x00442360`, `0x004423B0` and `0x004456C0`; begin31 at
`0x00442100` and `0x004421C0`; iterator addition45 at `0x004422A0`; iterator
construction28 at `0x00442320` and `0x00442370`; and iterator advancement32 at
`0x00442340`. Proposed names explicitly retain unknown element types.

**Whole source and ownership.** Four independently scoped source graphs retain
52 section instances / 1961 bytes: 44 code / 1705 and eight data / 256, all 92
actual fields and 44 complete normal/EH CFGs. Source section, numeric symbol
index, actual AUX records, definitions and every relocation remain. Identical
generic source symbols for the two stride4 groups do not share a native owner:
scoped local keys and complete owning sections determine addresses. Observed
native call destinations cannot populate the accepted source catalog. Complete
18-byte EH code carriers keep both cleanup and handler roots; existing R022
unwind8 rows remain unchanged. Full 36-byte EH data sections retain the FuncInfo
label at offset8 and unwind-map label at offset0; neither label crops the carrier.
Full bounds-message sections / 28 remain, even where groups share native data.

Three whole string/out_of_range code owners / 118 and full throw-type data / 16
retain literal R150 records and replay their cold original public source against
independently retained owning definitions. Original CRT throw58 and frame54
helpers reopen their hash-pinned archive members and complete own-AUX extents;
the real absolute __except_list definition is also reopened. Full R150 replay,
including its retained R149/R119 controls, passes. Prior accepted evidence is
preserved rather than deriving ownership from these new call observations.

Actual source uses `_Xran`, the invalid vector-subscript message and
`std::out_of_range`. Historical R032 generic `_Xlen` names and helper mappings
remain unchanged provenance records, not proof that these actual bounds-error
routes construct length_error. The new typed graph uses the real complete
out_of_range constructor and throw-type owners. Whole independent game contexts
retain SoundBank::Play142, FighterBase::BindAnimation149 with both actual calls,
and BattleCombat::ResolveBodyContact897 with complete authored CFG/switch proof.

**Cold controls and rejected alternatives.** Natural original public `<vector>`
source supplies mutable/const routes for generic element sizes4/8/16/116. All
130 ordinary sections / 5548, 27 actual original headers and complete generic
layout observations / 36 remain. Explicit flags are reproducibility settings,
not an executable-wide compiler claim. Four complete wrong-stride size bodies
fail whole comparison; the 52-byte alternative cannot replace the native57 by
cropping. Four complete const at70 alternatives retain their distinct typed
begin/add/dereference fields. Direct const dereference16 cannot replace the
native mutable wrapper19 with its actual separate const-dereference call. Raw
parent shape alone is insufficient; complete source policies and independently
owned destinations establish the library classification.

COFF function AUX PointerToLinenumber is debug file metadata: temporary object
placement shifts its absolute file offset. R205 validates that each nonzero
pointer lies on its own complete six-byte line-table entry and identifies its
actual function symbol index, then retains its relative table offset and every
line record. Other AUX values, complete function extents, all symbol indices,
source bytes, real fields and native bytes remain compared without masking.
Tests reject misaligned, foreign-symbol and truncated line tables, and show that
changed line records or function sizes remain observable. This normalization
does not alter earlier immutable evidence or native byte comparisons.

**Acceptance and preservation.** Original and accepted cold full source/field/
CFG/retained-owner/negative-control/game-context replay passes. The accepted
transition affects no prior literal original function/origin snapshot. Canonical
readback preserves all unrelated ledgers and evidence, 902 authored bodies /
1956112 bytes and all source/header/build/match inputs. Target/project/query
attestations, authored/exact guards, fresh 286-pending triage, generated progress
and whitespace checks pass. All 2730 CI tests pass, including 34 new guards.
Public MCP acceptance remains waived by the user.

Totals are 4065 resolved: 949 authored, 2538 library and 578 compiler; 286 pending
and 3116 excluded. Exact remains 60 functions / 9883 bytes / 60 units across
11 objects. The original 1311-candidate goal has 1025 resolved and 286 left and
remains active. R206 next reopens six complete 16-byte leaves under retained
vector dereference and list allocation/insertion contexts. Identical body shape
and reviewed parents are diagnostic only; original typed source and ownership
alternatives must settle each leaf separately.

## R206 — complete public/ordinary vector and list getter alternatives

R206 reviews all six whole 16-byte leaves / 96 bytes and retains unknown origin:
`0x0040E9B0`, `0x0040EA20`, `0x004124B0`, `0x0041F7E0`, `0x00532350` and
`0x005F9640`. No canonical ledger, extent, source, ABI, mapping or exact input
changes. Replay `scripts/repo-python scripts/verify-vector-list-leaf-alternatives-origins.py`.
`config/vector-list-leaf-alternatives-origin-evidence.json` SHA-256 is
`42c0eee2fd8764c7871e8a251c0e0dba789b1c850849a1182493f294cbbe7209`.
The six existing unknown records and their protected historical observations
remain literal evidence. This review supplies alternatives, not six resolved
ownership classifications or exact credit.

**Target and original source observations.** All six complete native bodies are
byte-identical, with one return, no internal branch and no relocation fields.
Three have original public vector const_iterator::operator* source counterparts;
three have public list const_iterator::_Mynode counterparts. The latter returns
a node pointer rather than an element reference. Original source method spelling
and returned types are source observations, not confirmed private target types.

Seven whole retained typed parents / 588 bytes reopen their complete original
source, actual function AUX/definitions and all 34 actual fields: vector mutable
dereference19 at 40E4C0, 40E530 and 5F8EA0; list insertion115 at 411EA0, 41E120
and 531DF0; and list erase186 at 411F20. Every field binds through complete
retained source-owner definitions and frozen independent external evidence,
not newly collected native destinations. All full unmasked parent/leaf byte
comparisons, normal CFGs, permissions, boundaries and unchanged canonical rows
pass. The complete source catalog rejects conflicting owners.

All six original public probes are cold-built again. Their 912 ordinary
code/data/EH/RTTI section instances / 40011 bytes, actual original includes and
complete original observation layouts are retained. The selected parent/leaf
source sections replay against complete current target bodies. This is a fresh
replay of the selected whole source graph and all ordinary compiler emissions,
not a claim that every historical native control or recursive dependency tree
has been rerun. Earlier source probes, manifests and verifiers remain unchanged.

**What the new controls establish.** Natural `<vector>` and `<list>` source
supplies four explicit public getters for independent generic element sizes4
and16. Two ordinary complete C++ classes supply a pointer getter and a reference
getter. Each of these six definitions emits the same complete 16-byte body as
all six native leaves, with no field masking, padding, truncation or fake return.
Their actual defining symbols, AUX records and complete line-table provenance
remain distinct. All 13 ordinary new sections / 206 bytes retain twelve emitted
functions / 174, six real forwarder fields, 29 actual original public headers
and the full generic layout / 32. Generic owner declarations are complete and
are not mapped to private game types. Compiler flags are explicit settings.

The retained parent graphs suggest public collection roles, but the new leaf
controls do not independently determine ownership of these opaque getter bodies.
Neither an identical short body, a historical name, nor a previously reviewed
parent alone resolves that question. The two ordinary getters demonstrate why
source-byte equality does not establish a unique source owner. Preserve the
six original unknown classifications until additional independent ownership
context distinguishes the alternatives; do not mechanically copy classifications
from R205's separate bounds-policy graphs or rewrite prior accepted provenance.

**Checks and continuation.** Complete original/new cold replay and 2751 CI tests
pass, including 21 new guards. Target/project/query attestations, authored/exact
guards, canonical readback and whitespace checks pass. All canonical ledger
records and exact inputs are unchanged from R205; the 902 authored bodies /
1956112 bytes and 60-function / 9883-byte / 60-unit exact baseline remain.
Public MCP acceptance stays waived. Totals remain 4065 resolved: 949 authored,
2538 library and 578 compiler, with 286 pending and 3116 excluded. The original
1311 goal remains active, with 1025 resolved and 286 left. R207 next reopens six
whole list node-link/value helpers / 57 provisional bytes under the retained
list policy graphs, preserving source and ownership alternatives individually.

## R207 — complete list node-link/value source alternatives

R207 expands the six-root /57-byte shortlist to the related character-list
previous-link helper at `0x00531D90`, reviewing seven whole leaves /68 bytes.
All seven retain unknown origin: `0x00411E80`8, `0x00411E90`11,
`0x004124C0`11, `0x0041E100`8, `0x0041E110`11, `0x00531D80`8 and
`0x00531D90`11. Replay
`scripts/repo-python scripts/verify-list-node-link-alternatives-origins.py`;
`config/list-node-link-alternatives-origin-evidence.json` SHA-256 is
`19c05f902093e46d3d85daf6c95ea5d2a477ea66049d9a8398b4e5fe6c4b85db`.
No canonical classification, extent, source, ABI, mapping or exact input changes.

**Complete evidence.** Three original cold list probes retain all750 ordinary
section instances /33500 bytes, actual original includes and full layouts through
literal R206 source references. Five whole typed parents /556 bytes retain all32
actual fields and complete normal CFGs: list insertion115 at411EA0,41E120 and
531DF0, erase186 at411F20 and value-node cleanup25 at412460. Each whole selected
source/field/native/permission/AUX/CFG/unchanged-canonical comparison passes.
Source catalogs derive from complete retained source owners and original
independent externals, not newly observed native field destinations. This replays
the selected whole source graphs and every ordinary compiler emission; it does
not claim to rerun all historical native controls or recursive dependencies.

Natural original public `<list>` const iterators instantiate `_Nextnode`,
`_Prevnode` and `_Myval` for independent generic payload sizes4 and16. Complete
generic intrusive nodes separately supply next-link, previous-link and value
accessors. Twelve real definitions retain whole AUX records, source symbol
indices and full debug-line provenance. Each four-member policy group emits
byte-identical complete bodies: next8, previous11 and value11. The three roles
have distinct bytes; matching one role cannot substitute another. No field is
masked, body cropped, node padding invented or private target node instantiated.
All31 ordinary new sections /526 bytes,30 complete functions /490,28 actual
original headers,18 real forwarder/dependency fields and full generic layout36
remain. The generic node sizes12/24 and member offsets0/4/8 are control
observations, not declarations of private game payload or node layouts.

The original source and retained callers suggest list roles, but ordinary
intrusive-node policies reproduce the complete short helpers. These alternatives
do not independently settle the opaque target helper owners. All seven original
unknown rows and protected prior observations stay unchanged; source-byte
identity does not grant library/compiler ownership or exact credit. The new
proof supplies durable reasons and controls for those decisions.

**Checks and continuation.** Complete cold replay, target/project/query,
canonical readback, authored/exact guards, fresh286-pending triage, generated
progress and whitespace pass. All2771 CI tests pass, including20 new guards.
Prior ledgers, manifests, verifiers and exact inputs remain unchanged. Public MCP
acceptance remains waived. Totals remain4065 resolved:949 authored,2538 library
and578 compiler;286 pending and3116 excluded. Exact stays60 functions /9883
bytes /60 units across eleven objects; all902 authored bodies /1956112 bytes
remain. The original1311 goal has1025 resolved and286 left and remains active.
R208 next investigates six complete vector insertion carriers /4722 provisional
bytes, including their catch entries, shared tails and real EH metadata. Their
known parent mappings are diagnostic; reconcile the complete source/control-flow
extent and independently owned fields before accepting any classification.


## R208 — whole vector insertion carriers and shared exception interiors

The six complete public `std::vector::_Insert_n` carriers establish library
origin for six heads and twelve existing catch/continuation inventory entries.
Two existing 19-byte shared exception-frame/register-restoration epilogues are
compiler generated. These are 20 origin transitions, not 20 independent source
functions. Interior entries have no independent own AUX or additional physical
coverage. Their original inventory spans are preserved.

| Whole head | Provisional bytes | Complete bytes | Source element observation |
| --- | ---: | ---: | --- |
| `0x0040A210` |777|796| scalar/pointer4; original declaration unknown |
| `0x0040EDB0` |777|796| scalar/pointer4; original declaration unknown |
| `0x0045A130` |777|796| scalar/pointer4; original declaration unknown |
| `0x004594B0` |795|814| generic aggregate16; private declaration unknown |
| `0x0040EA30` |800|834| generic cleanup44; private lifetime declaration unknown |
| `0x005F9650` |796|830| generic owned aggregate16; private declaration unknown |

The heads cover 4,866 physical bytes, 144 more than the provisional records.
Complete own AUX/sections, two real local catch symbols per head, all normal,
catch and unwind roots, shared returns, alignment and complete defining data
reconcile the extents. No comparison is cropped to a first RET, catch entry or
old ledger span. The compiler interiors at`0x0045A439` and`0x004597CB` restore
`FS:[0]`,saved registers/frame and return with 12-byte cleanup; they have no
independent source symbol/AUX. Their full 19 bytes remain inside library parents.

Replay `scripts/repo-python scripts/verify-vector-insertion-carrier-origins.py`.
Manifest`config/vector-insertion-carrier-origin-evidence.json` SHA-256 is
`fe3ac742c24edcbdd5d3f5d5f938071edf8eac728c1ef8f3016bf45b0a5468cd`.
The new cold public source supplies 334 ordinary sections / 20,598,27 actual
original headers and complete generic layout 40. The accepted six scoped graphs
retain 263 whole code/data sections / 15,334,all 638 actual fields,209 complete CFGs
and 54 full data carriers / 2,212. All six whole public insert parents also replay
inside these graphs: five count-insert parents 33 and one single-insert parent 114.
Group-local COFF indices, source definitions, actual AUX/debug line records,
permissions and every unmasked native byte are checked. Only a validated debug
line-file pointer is made relative to its own complete COFF line table.

The field catalog comes from complete scoped source owners and independent
retained definitions, not recorded native field destinations. All 15 used R150
owners retain literal original records/current canonical state. Every replay
runs the complete independent R150 cold graph, including its retained R149/R119
proofs. Actual CRT archive member/AUX ownership supplies absolute`__except_list`;
the actual cold standalone weak AUX selects the complete strong length-error
fallback. Its full 18-byte AUX is retained; no archive-selection claim is made.
Full EH state/unwind/try/catch sections and throw/literal/RTTI owners remain.

The generic44-byte cleanup fixture binds a no-stack-argument ECX-receiver call
to the independently reviewed entire authored`0x0041A380` /75 policy. Its R021
record, full native instructions, actual receiver protocol and CFG replay. The
fixture name is an opaque compatible source interface; it does not recover an
original mangled symbol, private class or complete target layout.

Two whole alternative insertion heads 796 are byte-equal before binding, but
that alone is insufficient: a generic aggregate 4 has a complete fill 36 differing
at five bytes from the selected scalar/pointer source. Direct delete 34 also
differs from guarded delete 43. Whole public/ordinary destruction 15 alternatives
retain the same actual private callee; the trivial destruction 5 alternative is
also completely byte-equal. Five canonical entries remain unknown and unchanged:
`0x0045B630` /5,`0x0040F9F0` /15,`0x005FAAD0` /15,`0x0040D8E0` / 19 and
`0x004588B0` /43. Generic fixtures and library parents do not establish their
original private declarations or owner. R108/R161 lifetime ambiguity is preserved.

Four literal protected snapshots remain history: R161 heads40A210/40EDB0 / 777
each and R162 heads40EA30 / 800 and5F9650 / 796. This successor checks all original
bytes and unknown records against the audited full796/796/834/830 transitions.
The historical R161/R162 standalone verifiers expect their old protected ledger
state; use the R208 successor for these four transitions. No old manifest/verifier
or accepted source evidence is rewritten. This does not claim a fresh replay of
all R161/R162 native controls; the new six whole graphs and independent R150
graph are the current cold proof.

Original-state and accepted-state cold replays pass. All 2,810 CI tests pass,
including 39 new provenance/boundary/transition guards. Target/project/query
attestations, complete authored verification, exact preservation, bounded
canonical readback, fresh 266-pending triage, progress and whitespace pass.
Exactly 20 function/origin rows change; only the six head extents change.
All prior authored records, protected unknowns and mapping/source/ABI/exact inputs
remain. Public MCP acceptance stays waived. The checkpoint is 4,085 resolved:
949 authored, 2,556 library, 580 compiler; 266 pending and 3,136 excluded.
The original 1,311 goal has 1,045 classified / 266 left and remains active. Exact
remains 60 functions / 9,883 bytes / 60 units across eleven objects; no exact credit.
