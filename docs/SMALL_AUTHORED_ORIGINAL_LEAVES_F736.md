# F736 — six more independently reviewed authored whole functions cold-exact

**NEW CANONICAL COMPLETE ORIGINAL-GAME EXACT CODE:** six functions,
**302 original CODE bytes**. Target: user-supplied Japanese TH075 ver1.11
`resources/th075.exe`, pinned SHA-256
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
The original whole-function boundaries, individual authored origins,
physical x86, every COFF field and original callee identity were
independently checked. These are NOT giant switch interiors or vendor
library functions. Existing reviewed authored provenance for these
specific functions was present in `config/function-origins.csv`
**before** the normal C++ probes were written: R019, R014, R011,
and R021. No unknown-origin candidate was promoted.

## Newly accepted exact original functions

| Original complete target | Native entire CODE / x86 | Genuine original behavior | Actual typed native PE/COFF |
| --- | --- | --- | --- |
| `0040B250` | **33 B /13 x86** | TextureManager clear two actual container subobjects at `this+8` and `this+0x18` | 2 `REL32` to `0040DE30/0040DF40` |
| `0040C7F0` | **65 B /24 x86** | Route blend modes 2, 3, 6 to depth mode 3; other modes depth 2; then forward actual blend mode | 3 `REL32`, depth `00402250` twice, blend `00401F50` once |
| `0040C970` | **42 B /18 x86** | Resolve actual texture by index via `0040C8C0`, then forward texture/vertices/count to original projected strip draw `00403200` | 2 `REL32` |
| `0040D840` | **35 B /16 x86** | Forward opaque sprite arguments with native default white color `-1` to `0040D790` | 1 `REL32` |
| `0040D870` | **80 B /27 x86** | Zero `RECT.left/top`, read native texture record members `+4/+8` through two actual indexed `At()` calls on `this+8` | 2 `REL32` to `0040DD60` |
| `0041A0E0` | **47 B /17 x86** | Signed byte `% 10`, `remainder < 6` returns true, otherwise query progress global `006718F8` using code+200 | 1 `DIR32` to `006718F8`, 1 `REL32` to `00416DC0` |
| **Total** | **302 original CODE B /115 ordered x86** | Six independently complete real original authored game functions | **12/12 real original typed fields** |

Pinned native x86 and natural VC7.1 C++ match on **all 115 ordered
instruction mnemonic+width positions**, with each function's
complete return and original calling convention. Source also matches
**254/254 nonrelocation original bytes**; all 12 physically authentic
relocation fields have their correct offset, decorated compiler
symbol, `REL32`/`DIR32` type, zero addend and original PE destination.
The 302 complete original CODE bytes are accepted by the canonical
relocation-aware per-unit cold replay, not by a masked comparator
or a handcrafted instruction dump.

## Native C++ and original ownership evidence

The source bodies are tracked as ordinary C++ in only three original
shaped translation units:

- [`src/TexturePolicyLeavesF736.cpp`](../src/TexturePolicyLeavesF736.cpp)
  owns three complete texture policy wrappers; `TextureManagerSlotsF736`
  uses real 16-byte subobjects at native `+8/+0x18`, both actually
  invoked. The `SetBlendMode` branches match exact original
  comparisons and the three distinct game-policy call sites. The
  projected-strip wrapper actually passes the returned texture from
  its own index lookup, not an invented null texture.
- [`src/SpriteDrawLeavesF736.cpp`](../src/SpriteDrawLeavesF736.cpp)
  retains the real three-word original sprite args and the native
  color `-1`. Its rect getter uses a genuine `RECT*`, two actual
  `NativeSpriteRectListF736::At(index)` calls on the same member
  object at +8, and copies exactly the native `+4/+8` record values;
  no guessed entire sprite list allocation or fake local stack.
- [`src/ProgressEncodedItemF736.cpp`](../src/ProgressEncodedItemF736.cpp)
  is a genuine cdecl function with a **signed-char** parameter, not
  an unsigned byte. The compiler reproduces original `MOVSX`,
  `CDQ`, `IDIV ECX` divisor 10, `CMP EDX,6` and exact signed
  branch, then the real record query with `code+200` at physical
  original global address. It does not convert negative values
  to a different unsigned comparison or hide an extra branch.

All names and complete historical object layouts remain inferred;
only the actual observed member offsets and public ABI needed for
these entire method calls are backed by the original PE. The
callees, even when independently exact, receive no additional
credited original CODE from these wrapper acceptances. The
`0040DD60`, `0040DE30`, `0040DF40` C++ declaration names are
source-compatible original-call proxies, not an assertion of full
vendor or original container implementation.

## Canonical targeted cold replay and exact tracking

Each complete original callable function has its own physical unit
in `config/match-units.toml`, with the real source, compiler profile,
decorated COFF symbol, original complete PE size, and every physical
typed relocation. The six authored function rows were updated
without changing the 949 previously accepted exact units, source
provenance, or candidate boundaries. Six entries were added to
`config/reccmp-functions.csv`, `config/implemented.csv`, and
`config/matches.csv` only **after** actual new-unit replay succeeded.

```bash
scripts/repo-python scripts/replay-exact-units.py \
  --unit texture-manager-clear-slots-0040b250 \
  --unit texture-manager-blend-policy-0040c7f0 \
  --unit texture-manager-projected-strip-0040c970 \
  --unit sprite-drawing-white-forward-0040d840 \
  --unit sprite-drawing-texture-rect-0040d870 \
  --unit progress-record-check-encoded-item-0041a0e0
# Cold replay: 6/6 exact units across 3 objects.
```

The actual native target hash, full source placement, object and
COFF reference ownership were rechecked with the pinned compiler.
There was **no all-949-unit cold replay**, no independent old unit
rebuilt for coverage, no original EXE modification or arbitrary
padding. Exact status means the complete generated machine code
and all physical relocations match, not that inferred C++ class
names are historical facts.

**F736 official entire authored ledger:** **955 cold-exact
source-present complete game functions /955 canonical units**,
**863,163 original CODE bytes**, **43.73%** of **1,973,704**
reviewed authored original CODE; conservative **43.66%** with
the 95 provenance-unknown candidates' 3,420 bytes included in the
denominator. The long-running 25 other original complete functions
(22 giants and the three WinMain/Scene/Archive ownership cases)
remain NONEXACT; new source-backed giant internal cases are still
uncredited original CODE. The 98% authored goal remains incomplete.
