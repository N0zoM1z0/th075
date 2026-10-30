# F818 — Complete authored Scene destructor: authentic typed resource view versus original stack ownership

The original user-supplied Japanese TH075 v1.11 PE contains
the authored scene virtual destructor 0043B0B0: **248 complete
CODE B, 75 original x86, 12 true PE/COFF relocation fields**.
Its effects include actual scene vtable and clock-state updates,
the texture manager conditional scalar delete, three independent
conditional CRT free calls and the real scene-base destructor
under the native VC7.1 exception-handling profile.

Independent original PE disassembly places actual texture
and scalar-delete temporary pointers at **EBP-0x14/-0x10**,
and the three real freed-resource pointers at
**EBP-0x18/-0x1C/-0x20**, in physical order.
The best existing source still has nine unmasked
machine-byte differences from wrongly assigned
temporary stack slots: **191/200** original
nonrelocation bytes match; merely having the
right total CODE length is not exact.

F818 explicitly investigates whether the prior source's
raw FIELD casts — rather than a coherent borrowed
physical owner representation — cause the
compiler's wrong temporary lifetime ordering.
The new borrowed C++ view represents only the
physically observed original scene boundaries:
texture pointer at original +0x08, three void*
release pointers at +0x4C/+0x50/+0x54, and
the real unknown original bytes between those
offsets. The borrowed type is NEVER constructed,
embedded or claimed to be the historical complete
private scene class. It exists only as a typed
access view of the actual real original fields.
No dummy used locals, x86 instruction fragments or
manual native layout padding are inserted.

## Seven fresh complete VC7.1 destructor compilations

| Source variant | Whole compiler CODE/x86 | Original PE result |
| --- | ---: | --- |
| Existing full destructor source baseline | 248 B/75 | 191/200 native nonfield |
| Typed borrowed texture member only | 248 B/75 | Same complete compiler COFF bytes |
| Typed borrowed three free members only | 248 B/75 | Same complete compiler COFF bytes |
| Joint borrowed texture + three free members | 248 B/75 | Same complete compiler COFF bytes |
| Actually used named borrowed reference | 254 B/77 | Wrong whole native extent and frame |
| Actually used named borrowed pointer | 254 B/77 | Wrong whole native extent and frame |
| Actually used named const borrowed pointer | 254 B/77 | Wrong whole native extent and frame |

For the baseline and all three typed-view alternatives,
the verifier proves the **entire generated 248-byte COFF
function and all 12 relocation shapes are byte-identical**
to the existing source, not merely equal mismatches.
It independently checks **all twelve original PE
field offsets, kinds, zero source addends and native
call/global destinations** and preserves the nine
authentic non-relocation stack displacement errors.

For the three real used named borrowed-pointer or reference
owners the compiler emits **two additional instructions
and six additional bytes** and moves saved this to
EBP-0x28. Source COFF still contains twelve fields
but their moved positions are explicitly NOT
claimed to be the true original PE relocations,
and the extra-length source is never cropped
to 248 original bytes for a fake match.

This is a concrete bounded negative conclusion:
recasting original resource members into a typed
borrowed owner is not by itself the cause or
solution for VC7.1's five-way temporary allocation
difference. The next small-function work should
focus on actual construction/destruction lifetime
ordering and the allocation of distinct texture
and CRT-free parameter values, not nominal type
aliasing.

Targeted reproduction:

    scripts/repo-python scripts/verify-scene-borrowed-owner-f818.py

The original 248B authored whole function is STILL
NONEXACT; no new accepted exact function or original
CODE is credited. Generated source, COFF/PDB, logs and
physical original PE comparison are retained in ignored
.analysis/f818-scene-borrowed-owner/. No corpus-wide
979-unit cold replay occurred.
