# F735 — six newly canonical cold-exact complete authored small functions

**New accepted original authored whole-function CODE: six functions,
135 original CODE bytes.** The pinned original target is the user's
Japanese TH075 v1.11 `resources/th075.exe`, SHA-256
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
This is the **independently reviewed R014/R015 authored provenance**
cohort, not unknown-original or CRT/SKD callee source promotion.

## Actual entire native PE and true ordinary VC7.1 C++

| Original function start | Original complete CODE / x86 | Actual original native callee | Source / canonical unit |
| --- | ---: | --- | --- |
| `0040C7E0` TextureManager Present | **16 B /8 x86** | `Graphics::Present` at `004028F0` | `src/TextureManagerForwardersF735.cpp`; `texture-manager-present-forward-0040c7e0` |
| `00406DF0` InputMapping ReleaseClient | **19 B /9 x86** | `InputResourceClient::~InputResourceClient` at `00403BE0` | `src/InputMappingReleaseF735.cpp`; `input-mapping-release-client-forward-00406df0` |
| `0040C840` TextureManager SetDepthMode | **25 B /11 x86** | `Graphics::SetDepthMode` at `00402250` | `src/TextureManagerForwardersF735.cpp`; `texture-manager-depth-forward-0040c840` |
| `0040C860` TextureManager SetTextureFilter | **25 B /11 x86** | `Graphics::SetTextureFilter` at `004023B0` | `src/TextureManagerForwardersF735.cpp`; `texture-manager-filter-forward-0040c860` |
| `0040C880` TextureManager SetPixelShaderMode | **25 B /11 x86** | `Graphics::SetPixelShaderMode` at `004025F0` | `src/TextureManagerForwardersF735.cpp`; `texture-manager-shader-forward-0040c880` |
| `0040C8A0` TextureManager SetColorMultiplier | **25 B /11 x86** | `Graphics::SetColorMultiplier` at `00401AF0` | `src/TextureManagerForwardersF735.cpp`; `texture-manager-color-forward-0040c8a0` |
| **Total actual original source** | **135 CODE B /61 x86** | Six previously original-authored exact calls | **6 canonical exact units, 2 source/COFF objects** |

All six original PE function extents were independently reread through
the pinned target decoder. Every original whole body includes its
real `PUSH EBP/MOV EBP,ESP/PUSH ECX`, original unused but saved
`this` at native `EBP−4`, original call and actual `RET`/`RET 4`.
The ordinary C++ `thiscall` source reproduces each entire x86 body
with pinned VC7.1 `/Od /Ob0 /Gy /GR- /GX- /GS /Zi` and the
existing project header declarations. There are **61/61 original
ordered instruction mnemonics and widths** and **111/111
nonrelocation original bytes** equal. All six physically real
`REL32` call fields match target PE address, decorated source symbol,
zero addend and native instruction offset. No masked bytes, aliases,
truncated functions, invented stack slots or original EXE modification.

The four parameter forwarders retain their real original calling
conventions and ABI types: depth/filter `int` use `MOV EAX,[EBP+8]`,
the signed-byte shader mode uses original `MOV AL,[EBP+8]`
(*not* an invented `MOVZX`), and color multiplier is a genuine
`float` passed as a full DWORD bit-pattern without unnecessary
x87 conversion. All four use caller `ADD ESP,4` after their actual
`Graphics` cdecl call and finish with thiscall `RET 4`. The
zero-parameter Present and InputMapping wrappers finish with
`RET` and do not claim the callee's original CODE as newly
reconstructed. The InputMapping wrapper explicitly calls the
already source-backed `InputResourceClient` native destructor
on the unadjusted receiver at base offset zero; this is grounded by
the original ECX+`00403BE0` call, without assuming a complete
historical InputMapping object definition.

## Real per-unit native cold replay, no full replay

The six units were added with their **complete actual original
physical `REL32` relocation targets** in `config/match-units.toml`,
with independent corresponding entries in functions, reccmp,
implemented, and matches manifests. The pinned toolchain then
**cold-built only two C++ objects and canonical-replayed exactly
six new units**:

```bash
scripts/repo-python scripts/replay-exact-units.py \
  --unit texture-manager-present-forward-0040c7e0 \
  --unit texture-manager-depth-forward-0040c840 \
  --unit texture-manager-filter-forward-0040c860 \
  --unit texture-manager-shader-forward-0040c880 \
  --unit texture-manager-color-forward-0040c8a0 \
  --unit input-mapping-release-client-forward-00406df0
# Cold replay: 6/6 exact units across 2 objects.
```

The six original authored provenance determinations were already
recorded in `config/function-origins.csv`: five TextureManager
forwarders are **R014**, and InputMapping ReleaseClient is **R015**.
The complete original Graphics and InputResourceClient callees are
previously accepted units and are **not** re-credited. Class names
and the full original object layout remain provisional; the
exact emitted method ABI is verified, not a proof of historical
C++ declaration names.

**New official status following F735:** **949 exact complete authored
functions /949 source-present /949 canonical units**, **862,861
original CODE bytes**, **43.72%** of 1,973,704 reviewed original
authored CODE bytes, conservative **43.64%** with the separate 3,420
unknown-origin CODE bytes in the denominator. The 25 previously
in-depth open authored functions (22 giants, the 2,987-B WinMain,
248-B Scene destructor and 171-B ArchiveCatalog destructor) are
still NONEXACT. Thirty additional previously R014/R015-style
reviewed-authored functions remain not yet adopted; those should
be tackled as independently bounded whole functions, not by
misattributing compiler/library/unknown-origin bytes.

No existing 943-unit cold replay was run. The repository's
verification is on the six *new* whole functions only, along with
target SHA-256, tracking and handoff audits.
