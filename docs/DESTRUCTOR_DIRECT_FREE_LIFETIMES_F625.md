# F625 — genuine original destructor pointer lifetimes: two source shapes with correct deletion EBP slots, but wrong entire CODE length

**Original pinned Japanese TH075 1.11 native PE; real MSVC VC7.1
whole authored function comparisons; NO whole-function exact acceptance.**
Target SHA256:
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
Both original functions are separately classified **authored** in
`config/function-origins.csv`; these are not game cases inside a giant
or tiny unknown-origin constructor wrappers. They remain among the
**three currently unmatched small original whole game functions**.

## What original native CODE really requires

| Complete original authored destructor | Original full native CODE and x86 | Authentic original PE physically typed COFF refs | Natural named-free VC7.1 source |
| --- | ---: | ---: | --- |
| `0041CE50` ArchiveCatalog nonvirtual destructor | **171 B /51 x86** | 14 | **171 B /51 x86**, but 108/115 nonrelocation bytes match |
| `0043B0B0` battle SceneObject virtual EH destructor | **248 B /75 x86** | 12 | **248 B /75 x86**, but 191/200 nonrelocation bytes match |

For original `0041CE50` original native resource-pointer and
resource-destruction receiver stack slots are **EBP−0xC** at original
x86 ordinal22 and **EBP−0x8** at ordinal24. The actual released
filename owner is stored at **EBP−0x10** at ordinal38. The ordinary
named-pointer C++ source in
[`ArchiveCatalogNativeLifetimeF584.cpp`](../probes/ArchiveCatalogNativeLifetimeF584.cpp)
instead assigns `−0x10/−0xC/−0x8` to these three real values.
The wrong EBP displacements are genuine native nonrelocation CODE
bytes; they cannot be counted as COFF uncertainty.

For `0043B0B0`, actual native original texture-resource pointer at
x86 ordinal26 uses **EBP−0x14** and delete receiver at ordinal28
uses **EBP−0x10**. The subsequent three CRT free values occupy
original EBP−0x18, −0x1C and −0x20. The named-pointer aggregate
in [`BattleSceneTextureDeleteF589.cpp`](../probes/BattleSceneTextureDeleteF589.cpp)
gets the first two wrong (`−0x20/−0x1C`) despite preserving the full
248 native-sized CODE geometry and 12 original physical typed fields.

## An important real VC7.1 compiler-allocation mechanism

F625 newly tracks TWO ordinary C++ whole-destructor alternatives:

- [`ArchiveCatalogDirectFreeF625.cpp`](../probes/ArchiveCatalogDirectFreeF625.cpp)
  keeps the real list-index loop, actual native resource deletion,
  pointer provenance and global list lifetime, but directly passes
  the borrowed filename pointer to CRT `free` without a named
  filename local. The full natural VC7.1 `/GX-` result is **165 B
  /49 x86/14 typed COFF fields**, **not** the required 171/51.
  Nevertheless, both original destructor-related EBP operands at
  x86 ordinals22/24 are **now genuinely identical** to the original
  `−0xC/−0x8`, because an earlier named filename pointer no longer
  preempts the compiler's stack allocation. The original filename
  value's independent store/reload at original ordinals38/39 is
  absent, dropping exactly two instructions /6 native CODE bytes.
- [`BattleSceneDirectFreeF625.cpp`](../probes/BattleSceneDirectFreeF625.cpp)
  keeps original EH `/GX`, scene-state transition, the same texture
  delete, all original three borrowed game resource field accesses
  and actual CRT `free` calls. Each field is freed directly, rather
  than saving its value to a separate named source pointer. Natural
  VC7.1 emits **230 B /69 x86/12 physical COFF fields**, not the
  original 248/75. Yet its two genuine native texture/delete EBP
  operands at x86 ordinals26/28 now exactly match original
  `−0x14/−0x10`. The three original free calls no longer each have
  their separate two-instruction C++ save/reload, leaving precisely
  **six missing x86 instructions /18 native CODE bytes**.

The two independent, complete game destructor comparisons show a
reproducible compiler allocator dependency: a source's real named
later free-values can change the *earlier* deletion-expression temp
slot positions under genuine VC7.1 `/Od`, even without any change to
what source pointer is eventually freed. This explains why merely
forcing the compiler to produce a new `char*` alias or changing a
source cast is insufficient. It does **not** reconstruct the actual
original combined lifetime expression/temporary ownership needed to
reproduce both correct original delete slots **and** every original
free-value store/reload instruction at once.

## Independent full-original native source experiments retained

Earlier F609/F612 controls tested loop type, pointer casts and
aggregate declaration order. This F625 investigation additionally
cold-compiled **20 genuine archive rvalue/pointer-reference source
variants**, under ignored `.analysis/f623-archive-rvalue-temporaries/`:
three emit 171/51 with **108/115** nonfield bytes, eleven genuine
reference/slot-access alternatives remain 171/51 but regress to
**102/115**, and six `void* const&` materialized temporary forms
emit **179/54**, not original. None fixes the original lifetime
allocation.

The separate **19 scene resource release-lifetime experiments** under
`.analysis/f625-scene-lifetime-scopes/` include individual declared
pointer locals, reversed declaration order, inline local
lifetimes, C++ reference and materialized-rvalue forms, and full
three-field direct release, without fabricated or unused C++ local
padding. The original 248/75 source-like grammar remains
**191/200** or **189/200** nonfield bytes, source reference variants
change full CODE to **254/78** or **272/84**, and partially direct
release source is **236/71**; only fully direct free produces
**230/69** with both native original texture/delete EBP slots.
This is actual negative PE evidence, not a known-to-be-correct
original source declaration.

The tracked verifier
[`verify-destructor-direct-free-f625.py`](../scripts/verify-destructor-direct-free-f625.py)
independently reads **both entire original native function extents**,
checks each original complete x86 count and exact physical deletion
slot operands, cold-compiles **only the selected one** new plain C++
whole TU using the correct pinned VC7.1 profile, checks all 14 or 12
actual physical typed source COFF fields, and invokes the canonical
whole-function original-PE comparator. The **expected result is
strictly `size-mismatch`**, not an invented native CODE acceptance.
The original full 171/248-byte comparisons are mandatory: neither
candidate truncates the native function or masks stack displacements.

## Accounting and bounded commands

Together the two original authored whole destructors contain **419
original CODE bytes**, none yet exact; this is **not** a 419-byte
partial credit. The source evidence independently proves correct
physical delete EBP ownership but not the complete original code.

**F625 adds zero accepted complete original authored game functions
and zero original accepted CODE bytes.** The official source
reconstruction ledger stays **943 complete exact functions /
862,726 original CODE bytes**. These two functions remain open
alongside the separate 2,987-byte original authored startup. F622
and F624 concurrently added original fighter giant *internal* case
source proofs, which also do not represent new exact whole functions.
No game binary edit, original PE patch, synthetic frame filler,
manual assembly, full all-unit cold replay or remote Oracle acceptance.

```bash
scripts/repo-python scripts/verify-destructor-direct-free-f625.py --which archive
scripts/repo-python scripts/verify-destructor-direct-free-f625.py --which scene
# Optional exactly these two newly affected complete authored C++ TUs:
scripts/repo-python scripts/verify-destructor-direct-free-f625.py
scripts/repo-python scripts/validate-tracking.py --require-target
```

Reproducible new original byte comparisons, actual selected compiler
COFF/PDB, source compiler logs and original native x86 EBP evidence
are preserved in ignored `.analysis/f625-destructor-direct-free/`.
The independent 20+19 compiler-source experiment matrices above
remain in the respective ignored trial directories, not in match
manifest or synthetic accepted source folders.
