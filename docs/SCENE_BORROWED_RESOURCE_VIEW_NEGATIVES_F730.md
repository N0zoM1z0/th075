# F730 — whole original Scene destructor: genuinely borrowed resource-field views

**Ten complete original-source VC7.1 C++ tests; NO exact whole function
accepted.** The target is the pinned user-supplied Japanese TH075 v1.11
`resources/th075.exe`, SHA-256
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
Every candidate keeps the actual original game Scene state update,
conditional TextureManager scalar deletion, all three distinct real
CRT `free()` operations and base destructor. None introduces an
unused stack padding object, manual binary instruction, or executable
byte change.

## Independently re-read original physical EH and resource ownership

Original authored virtual `0043B0B0` is a complete **248-CODE-B /75-x86**
MSVC exception-aware destructor. Its authentic native x86 begins
`PUSH EBP; MOV EBP,ESP; PUSH -1; PUSH 00655B86`, installs
`FS:[0]`, allocates `0x1C` bytes and saves `this` at `EBP−0x24`.
It updates the real scene vtable, adjusts scene state, conditionally
calls the original scalar deleting TextureManager destructor
`00425460`, then calls CRT `00640F15` three times for resources
actually stored at offsets `this+0x4C/0x50/0x54`, followed by
original base destructor `00431F40` and restores the EH chain.
The original real five source-temporary slots, at native x86
ordinals 26,28,42,52,62, are respectively
`EBP−0x14/−0x10/−0x18/−0x1C/−0x20`.
The historical best plain C++ source matches 248B/75x86/12 typed
source references but has only **191/200** native nonrelocation
bytes equal. Its texture/delete scratch uses
`EBP−0x20/−0x1C` instead of original `−0x14/−0x10`.

## New, genuinely used C++ member-borrow hypotheses

Earlier F700/F713/F727 investigated resource *local-value* owners,
small used value aggregates and a three-pointer local array.
F730 instead tests whether the native resource fields are accessed
through a genuine **borrowed view of the original Scene storage**:
one C++ reference/pointer to a contiguous three-pointer struct
at `this+0x4C`, three individually used pointer references to
`FIELD(void*,0x4C/0x50/0x54)`, or a fresh real reference scoped
inside each original conditional cleanup branch. All references
actually read the authentic three members and their values are
actually passed to the three real frees. The struct overlay is a
provisional test of C++ source ownership, not a claim that the
original Scene class layout has been recovered.

| Source alias/lifetime model | Entire VC7.1 `/Od /Ob0 /GX` emitted function | Original result |
| --- | ---: | --- |
| Single genuinely used `CleanupPointers&` or `CleanupPointers*` referring to original `this+0x4C`, declared before or after texture deletion | **4 variants: 255 B/78 x86/12 actual typed COFF fields** | Additional three real instructions and 7 bytes; native 248/75 geometry lost |
| Three individually used mutable/const pointer references, early or late genuine scopes | **4 variants: 269 B/84 x86/12 fields** | Nine extra instructions and 21 bytes; compiler materializes additional real alias operations |
| One genuinely used mutable/const borrowed reference inside each original guarded `free` | **2 variants: 272 B/84 x86/12 fields** | Nine extra instructions and 24 bytes; original reference loading and stack ownership cannot be reproduced |
| **All whole original-shaped TUs** | **10 /10 compiled** | **0** native 248B/75x86 exact |

The genuine native source/COFF symbol sequence stays complete in
all ten: actual MSVC EH handler and `__except_list` fields,
Scene vtable, frame-mode global, clamped scene-state callback,
TextureManager scalar deleting destructor, three `_free` calls,
base virtual destructor and SEH restoration. These are **12
physically typed original-like source references with zero addends**.
Their position in the generated caller changes; **matching count
or symbol identity is NOT original physical relocation-position
exactness**, and none of these differing whole-CODE lengths
is falsely evaluated as a cropped 248-byte match.

The `struct-ref-late` case, for example, puts texture intermediates
at source `EBP−0x24/−0x20`, still wrong versus original
`−0x14/−0x10`. The three independent borrowed-reference source
models go deeper (e.g. `−0x2C/−0x28`) and also change the actual
`free` invocation instruction shapes. These experiments exclude the
simplest borrowed storage alias representation as the missing
native temporary lifetime model; they do not prove a historical
C++ layout or impossible alternate compiler source.

## Reproduce only the whole affected small function

Portable tracked selected-original generator and verifier:
[`scripts/verify-scene-borrowed-resource-f730.py`](../scripts/verify-scene-borrowed-resource-f730.py).
It rereads the pinned entire 248B/75x86 original PE and all five
real EBP slots. It then cold-compiles **one complete normal VC7.1
`/GX` Scene destructor** by default or `--case`, or **only these ten
directly affected complete C++ source TUs** with `--all`, requiring
the expected full source function sizes/x86 counts and all twelve
source EH/texture/free/base COFF field identities, kinds, addends
and actual owning instruction boundaries. The original full
248-byte baseline remains available via the existing F589 checker.

```bash
scripts/repo-python scripts/verify-scene-borrowed-resource-f730.py --case struct-ref-late
scripts/repo-python scripts/verify-scene-borrowed-resource-f730.py --all
scripts/repo-python scripts/verify-scene-texture-delete-f589.py --case paren
scripts/repo-python scripts/validate-tracking.py --require-target
```

Actual original/source evidence, per-variant normal C++/OBJ/PDB,
compiler logs and full source extents remain locally under
Git-ignored `.analysis/f730-scene-borrowed-resource-view/` and
`.analysis/f730-scene-borrowed-resource-verified/`.
No original EXE modification, no entire-function exact adoption,
no invented EBP slots and no all-unit cold replay. The reviewed
whole authored exact ledger stays **943 functions /862,726 original
CODE bytes (43.71%)**.
