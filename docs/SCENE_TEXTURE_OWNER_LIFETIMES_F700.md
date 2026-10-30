# F700 — genuine Scene texture owner / freed-pointer lifetime controls (negative)

This is **whole-function native codegen research, NOT byte-exact
acceptance**. The target is the pinned user-supplied Japanese TH075
v1.11 executable, SHA-256
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.

## Original 248-byte virtual destructor, not an arbitrary `free()` leaf

The original authored `0043B0B0` owns **248 CODE B /75 x86**, 12 real
zero-addend typed PE/COFF fields and genuine EH setup/restoration,
scene-vtable assignment, state update, conditional texture scalar
`delete`, three separate CRT `free()` calls and base destructor.
The original complete original PE machine operands at x86 ordinals
**26/28/42/52/62** are respectively `EBP-0x14/-0x10/-0x18/-0x1C/-0x20`.
Re-read live native PE; do not rely only on the old F589/F612 prose.

The previously selected meaningful source, with actual `CleanupPointers`
three-field aggregate and original game-owned texture delete, still
fresh-compiles under pinned VC7.1 `/Od /Ob0 /Gy /GR- /GX /GS /Zi`
(**exception handling enabled**, as in native) to **248 B /75 x86
and 12 physical fields**, matching **191/200 original nonrelocation
bytes**, not the entire original function. This baseline was rechecked
using just the F589 `--case paren` cold compiler control; nine machine
bytes remain genuinely different and are not COFF relocation fields.

## Ten new fully used texture/resource lifetime models

Instead of repeating the earlier simple casts and field-type changes,
F700 reconstructed **ten further complete, meaningful Scene destructor
translation units**. Every proposed local texture pointer is actually
conditionally `delete`d, and all three real scene resources are actually
freed; there are **no unused variables for artificial EBP padding**.
The sources deliberately vary true ownership timing and *aggregate vs
scalar* resource representation:

| Real source model | Variants | Actual pinned VC7.1 whole function |
| --- | ---: | --- |
| Named texture pointer / const pointer, declared before or after conditional and with aggregate before/after | 5 | Four variants **251 B/76 x86**, one **254 B/77 x86**, all 12 true COFF records; incorrect entire native CODE |
| Texture `TextureManager*&` reference bound to actual scene member | 1 | **255 B/78 x86**, all 12 source COFF records; incorrect native extent |
| Three **separately used** freed pointer locals, declared in the individual resource guards or before texture deletion | 2 | Both **248 B/75 x86/12 true PE/COFF**; **189/200** original nonrelocation bytes; original five temporary slots not recovered |
| Four-field local resource aggregate, with actually used texture pointer before or after three freed pointers | 2 | Both **251 B/76 x86**, all 12 fields; incorrect entire native extent |
| **Ten full source compiles** | **10** | **0** native byte-exact complete functions |

For the two 248-byte scalar-local variants, the real compiled texture
and delete temporaries remain `EBP-0x20/-0x1C`, not original
`-0x14/-0x10`. Freed locals occur at `-0x10/-0x14/-0x18` or
`-0x10/-0x18/-0x14` depending on used source scope; both differ
from original `-0x18/-0x1C/-0x20`. The 189/200 result is a
**regression** from the best 191/200 aggregate source, not progress
toward exactness. For the other eight sources, the compiler emits
*additional genuine instructions* and cannot be compared as if they
were 75 x86/248 B. The source declarations, actual compiled COFFs,
PDBs, compiler diagnostics and 248-B complete original PE comparison
JSON are preserved under ignored `.analysis/f700-scene-texture-owner/`.
They are local workspace artifacts, not tracked in Git.

This makes a straightforward original-source explanation involving a
named texture pointer, texture lvalue reference, or single four-field
ownership aggregate less likely. The remaining original lifetime
problem is the **five-way compiler-generated temporary-slot order**,
not texture cast spelling. Neither source-level semantic equivalence
nor all 12 relocations proves full machine-code exactness. Future
work should investigate real EH/object construction and release
ordering without inventing inert locals, swallowing nonrelocation
stack differences or patching original binary bytes.

Reproduce just the affected small function, not all accepted units:

```bash
scripts/repo-python scripts/verify-scene-texture-delete-f589.py --case paren
scripts/repo-python .analysis/f700-scene-texture-owner/research.py
```

**The Scene authored 248-B function remains NONEXACT.** No accepted
function-count or CODE-byte increase: **943 whole authored exact
functions /862,726 original CODE bytes (43.71% reviewed)**. No
all-943-unit cold replay or external Oracle acceptance.
