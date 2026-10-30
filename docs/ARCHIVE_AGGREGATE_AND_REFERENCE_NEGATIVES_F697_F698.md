# F697/F698 — full original ArchiveCatalog destructor aggregate and reference-return controls

**Negative original-target evidence; NO new exact CODE.** The actual pinned
Japanese TH075 1.11 target SHA-256 is
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
Original authored whole `0041CE50` contains **171 CODE bytes, 51 genuine
x86 instructions and 14 original physical PE/COFF references**. Its
true temporary slots at native ordinals `22`, `24`, `38` are resource
`EBP-0xC`, scalar-delete receiver `EBP-0x8` and freed filename
`EBP-0x10`. The baseline natural VC7.1 source instead allocates
**`-0x10`, `-0xC`, `-0x8`**, yielding **108/115** nonrelocation
native CODE bytes equal. A 171-byte same-length source is *not exact*
when seven real bytes still differ.

## F697: 10 meaningful filename value aggregate lifetimes

We freshly compiled the **complete** authored destructor under pinned
VC7.1 `/Od /Ob0 /Gy /GR- /GX- /GS /Zi`, using either a single-field
`struct F697Filename { char* value; };` or a single-field `union`
with the same meaningful filename pointer. The actual used value is
assigned from `Names.At(index)` and freed; these are not fictitious
padding members. Each source varies the live filename object's
placement: inside the free block, declared before resource deletion,
before the loop, before the reference-count guard, or initialized
from the actual names element. **Every source emitted 171 B, 51 x86,
14 authentic original PE/COFF fields**. Results:

| Placement of real used filename aggregate | Variants | Original CODE same nonfield bytes | Compiled actual resource/delete/filename stack slots |
| --- | ---: | ---: | --- |
| At the eventual release, early in loop, or aggregate-init | 6 | **108/115** each | `-0x10/-0xC/-0x8` |
| Before loop or refcount guard | 4 | **102/115** each | `-0x10/-0xC/-0x4` (loop/index role also shifts) |

No source naturally generated the original `-0xC/-0x8/-0x10`
lifetime graph. This independently rechecks the claimed earlier
aggregate-lifetime direction against actual current native bytes,
without treating a struct/union spelling change as progress.

## F698: 8 element-access return-reference interface hypotheses

The baseline uses borrowed `Resource** At(index)` and `char** At(index)`.
We tested all eight nonbaseline combinations in which one or both
methods instead return an equivalent **pointer lvalue reference**
(`Resource*&`, `Resource* const&`, `char*&`, `char* const&`), deleting
or releasing the returned pointer value directly. This is a possible
original C++ container interface, not a new synthetic local variable.

All **eight** emitted the actual **171-B/51-x86/14-field** original
whole-function geometry, but matched only **108/115** original
nonrelocation bytes. The real three generated temporary stack slots
remained **`-0x10/-0xC/-0x8`** in every case. Thus simply changing
`At(index)` from borrowed pointer-to-pointer to a C++ reference return
cannot explain the original allocation order; more fundamental
lifetime/evaluation context is missing.

All **18 full native-profile C++ variants** were recompiled serially
and compared to the **complete** original 171-B PE extent and all
14 physical COFF fields, not a truncated destructor interior. The
source versions, actual compiler output, whole-function comparison
receipts and reproducing research scripts reside in the present
worktree's **ignored**, local-only directories
`.analysis/f697-archive-aggregate-lifetime/` and
`.analysis/f698-archive-return-reference/`; these are not preserved
by Git on a fresh clone. Previously compiled 39 F682/F683 controls
remain distinct from the F697/F698 set. Neither group fixes the
real original three-way slot rotation.

**Next:** determine what original semantic object lifetime or
compiler-generated temporary reservation puts the filename release
value *after* the resource destruction in instruction order but
*before* it in stack allocation order. Do not synthesize an unused
local, claim `structural-exact`, mask EBP bytes, patch executable
CODE, or run an all-943-unit cold replay. Formal exact coverage still
**943 authored whole functions /862,726 CODE bytes, 43.71% reviewed**.
