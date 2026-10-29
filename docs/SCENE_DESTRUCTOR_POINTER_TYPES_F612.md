# F612 — original 248-byte SceneObject destructor: 22 freed-pointer type controls

**Pinned Japanese TH075 1.11 native whole-function PE evidence and ordinary
VC7.1 compiler negatives, not whole function exact source.** Original target
SHA256 `bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
The actual full nonexact authored virtual destructor `0043B0B0`
contains **248 original CODE bytes, 75 native x86 instructions and
12 genuine typed PE/COFF fields**. It performs original game-state
handling, texture object scalar delete, three independent CRT frees,
base destructor, and compiler-managed FS exception cleanup.

## Native EBP local ownership is not cosmetic

Original source requires these actual compiler temporary stack slots:

| Complete native x86 ordinal | Genuine original PE owner | Current natural C++ |
| --- | --- | --- |
| 26 | Texture resource at `EBP−0x14` | `EBP−0x20` |
| 28 | Texture delete receiver at `EBP−0x10` | `EBP−0x1C` |
| 42 | First free value at `EBP−0x18` | `EBP−0x18` |
| 52 | Second free value at `EBP−0x1C` | `EBP−0x14` |
| 62 | Third free value at `EBP−0x20` | `EBP−0x10` |

An independently correct lifetime/aggregate type model must naturally
restore all five original locations. It cannot simply mask the nine
physical nonrelocation EBP displacement byte differences or count
matched COFF fields as byte-exact CODE.

## 22 fully rebuilt C++ type, ownership and aggregate variants

The new reproducible
[`verify-scene-freed-pointer-types-f612.py`](../scripts/verify-scene-freed-pointer-types-f612.py)
generates each selected *complete* C++ destructor from
[`BattleSceneTextureDeleteF589.cpp`](../probes/BattleSceneTextureDeleteF589.cpp)
and freshly compiles only that source translation unit with original
MSVC VC7.1 `/Od /Ob0 /Gy /GR- /GX /GS /Zi` (real exception-enabled
profile). Every candidate is compared against the pinned whole native
248-byte original and all **12 genuine source COFF references**.
All `reloc` fields for whole-length candidates have physical types
and originals checked through the canonical native-PE comparator.
These are normal pointer ownership or index choices, not fake saved
locals, assembly, or postprocessor byte substitutions.

| Actual source trials | Variant count | Real compiler entire output | Original whole PE result |
| --- | ---: | --- | --- |
| `void*`, `char*`, signed/unsigned char, `short*`, `int*`, integer pointer bits, const and volatile qualifier, and trivially wrapped single-pointer fields | **14** | 248 bytes /75 x86 | **191/200** non-COFF bytes |
| Real three-pointer array with natural ordering, and a second array index permutation | **2** | 248 bytes /75 x86 | **191/200** non-COFF bytes |
| Four other meaningful three-pointer array orderings | **4** | 248 bytes /75 x86 | **189/200** non-COFF bytes |
| Actual `void*&` and `void* const&` lvalue aliases to game-owned resources | **2** | **254 bytes /78 x86** | Whole original-size mismatch |
| **Total** | **22** | Only selected small C++ translation units | **Zero complete native function exact matches** |

All twenty 248/75 outputs retain **the same wrong two texture-delete
EBP positions**. Changing true freed-pointer type leaves the resource
slots unchanged, and permuting the actual three resources only
reassigns their already-wrong later slots. Actual references increase
source CODE to 254 bytes and cannot be counted as the original
248-byte function. This is bounded negative evidence that pointer
cast/constness and obvious three-field container indexing do not
explain original compiler lifetime-allocation order. Future work
must recover the genuine resource-object/scene lifetime context,
not invent unused fillers to massage stack offsets.

**This is NOT a new accepted complete authored function.** Official
complete exact source stays 943 functions /862,726 original CODE
bytes. F610 and F611 simultaneously expanded fighter giant *internal*
case reconstruction, but those whole giant parents also remain
NONEXACT and are not added to this ledger. No full all-unit cold
replay or external Oracle exact acceptance occurred.

## Run only a changed small source control

```bash
scripts/repo-python scripts/verify-scene-freed-pointer-types-f612.py --case int-pointer
scripts/repo-python scripts/verify-scene-freed-pointer-types-f612.py --case array-order-210
scripts/repo-python scripts/verify-scene-freed-pointer-types-f612.py --case referenceptr
# Optional just these 22 affected scene-destructor TUs, not all 943 units:
scripts/repo-python scripts/verify-scene-freed-pointer-types-f612.py
scripts/repo-python scripts/validate-tracking.py --require-target
```

All original compiler outputs, full PE/COFF comparison JSON, PDBs,
transcripts and the complete 22-source negative manifest are retained
under ignored `.analysis/f612-scene-types/`.
