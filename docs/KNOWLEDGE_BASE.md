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
reconstructed or credited here. Device reset at `0x004017A0` likewise remains
an external, named dependency. Both error wrappers call the MessageBoxA IAT
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
