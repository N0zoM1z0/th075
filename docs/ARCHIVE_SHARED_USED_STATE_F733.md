# F733 — 22 complete ArchiveCatalog resource/filename/index lifetime controls

**New original-native compiler research, ALL whole-function NONEXACT.**
Target: user-supplied Japanese TH075 v1.11 `resources/th075.exe`,
pinned SHA-256
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
The actual authored nonvirtual ArchiveCatalog destructor
`0041CE50` owns **171 native CODE B, 51 physical x86 instructions
and 14 real typed original PE/COFF fields**. It decrements a native
shared refcount, iterates native unsigned-indexed resource/name
containers, conditionally uses the real scalar-delete helper
`0041D8C0`, calls CRT `_free` at `0064169D` on the true filename,
and clears both original global containers. No original EXE edits,
manually inserted machine bytes or fake padding locals.

## Original three-way temporary allocation and new source hypothesis

The physical native original has these actual, independently read
`MOV` stores and *used* C++ temporary owners:

| Original native x86 ordinal | Meaningful C++ owner | Original EBP slot | Previous best compiler-only source |
| ---: | --- | --- | --- |
| 22 | Pointer returned by real resource `At(index)` | `−0xC` | `−0x10` |
| 24 | Scalar-delete receiver temporary | `−0x8` | `−0xC` |
| 38 | Pointer returned by filename `At(index)` and passed to CRT free | `−0x10` | `−0x8` |

The earlier actual 171-B/51-x86 normal C++ matched **108/115**
original nonrelocation bytes and all 14 original physical PE/COFF
references but not those three EBP operand bytes. Prior F697/F698,
F709/F710, F716 and F719 tested *filename-only* aggregates,
index+filename objects, direct C++ reference return types, actual
RAII destructor ownership, and early single-variable declarations.
F733 instead tests **one genuinely used original resource+filename
state object**, or an actual three-field **index+resource+filename
state** with every member assigned and subsequently used in the
real source operations. This can affect MSVC `/Od` stack allocation
without inventing any unused local.

In addition, resource and name lifetimes do not overlap: the
resource pointer is consumed by scalar `delete` *before* the filename
pointer is obtained. F733 tests whether a genuine C++
`union { Resource* resource; char* filename; }` or one real
`void*` value, reused for both actual operations, can explain an
original source having only a single local storage owner.

## Actual complete 22-target VC7.1 experiment results

All sources compile the ENTIRE original-shaped destructor, with the
pinned VC7.1 profile `/Od /Ob0 /Gy /GR- /GX- /GS /Zi` and
its original (non-EH) destructor shape.

| Source model, every value genuinely used | Source variants | Actual whole emitted result |
| --- | ---: | --- |
| Resource+filename two-field struct, both field orders and declaration within the real loop or its shared refcount guard | **4** | **177 B/53 x86/14 source fields** |
| Index+resource+filename three-field struct, all 6 field permutations, declaration within or before the guard | **12** | **177 B/53 x86/14 source fields** |
| Union of genuinely sequential resource and filename pointer members, both field orders and loop/guard lifetimes | **4** | **177 B/53 x86/14 source fields** |
| One actual `void*` value reused for the native scalar `delete` and later `free`, loop/guard declaration | **2** | **177 B/53 x86/14 source fields** |
| **Total** | **22 whole C++ translation units** | **0 original complete functions exact** |

Every one of the 22 real source objects has exactly the same
**14 PE/COFF type+decorated-symbol+zero-addend identities in the
native call/global sequence**, including `Resources.At`, the
scalar deleting destructor, `Names.At`, CRT `_free`, and both
container `Clear` calls. However, compared to native 171/51, MSVC
reliably emits **two extra genuine `MOV` instructions immediately
after the real resource `At()` pointer dereference (original x86
ordinal 21)**, creating **6 extra CODE bytes**. Therefore the
full source has 53 x86, not the original 51.

The 14 actual, normalized native/source *physical relocation offsets*
show precisely what went wrong:

| Typed field owner | Original actual native CODE offset | New complete source CODE offset |
| --- | ---: | ---: |
| First 6 authentic count/index/resource container references | `10,18,47,52,66,71` | **same** |
| Scalar deleting destructor | **98** | **104** |
| Name container address and `At` call | **119,124** | **125,130** |
| `_free` call | **138** | **144** |
| Two real container `Clear` targets and their object-address fields | **148,153,158,163** | **154,159,164,169** |

Thus **8 of 14 native typed fields move by +6 bytes**, even though
their names, types, and zero addends are correct. Matching COFF
field *counts* or recognizing a native pointer slot at source
`EBP−0xC` in some candidates **does not imply** matching native
whole-function bytes. For example, the actually used
`pair-resource-filename-loop` struct does place its initial source
store at `−0xC`, matching native x8622 as a single occurrence,
but the next source operations allocate an additional used
resource copy and extra MOVs. It is not original CODE geometry.

The two originally non-overlapping semantic owner lifetimes are
interesting evidence about original possible C++ structure, but
no simple resource/name union or aggregate explains the authentic
`−0xC / −0x8 / −0x10` stack allocation *and* native instruction
count simultaneously. This is a **negative conclusion**, not
proof of what historical original C++ looked like.

## Reproducible target-only verifier and next research

Portable tracked
[`scripts/verify-archive-shared-state-f733.py`](../scripts/verify-archive-shared-state-f733.py)
reads the complete original 171-B PE and all three original owner
slots, plus the real native `0041D8C0` / `0064169D` calls. It
serially cold-compiles **one chosen entire 171-byte target-source
candidate by default**, another with `--case`, or **only these 22
affected whole small C++ source TUs** with `--all`. Every generated
object is tested for the genuine **177 B/53 x86/14 typed field
source result**, the two extra native-order MOV operations and the
exact original-versus-compiled 14-field position and symbol/type
mapping. It does **not** crop a 177-byte candidate to the original
171-byte extent or pass it through the canonical exact matcher
with an invented source interval.

```bash
scripts/repo-python scripts/verify-archive-shared-state-f733.py --case pair-resource-filename-loop
scripts/repo-python scripts/verify-archive-shared-state-f733.py --all
scripts/repo-python scripts/verify-archive-source-types-f609.py --case release-scope-delete
```

Actual C++/OBJ/PDB/compiler logs, original physical comparison
receipts and exploratory generators remain in Git-ignored
`.analysis/f733-archive-full-state-owner/` and
`.analysis/f733-archive-shared-state-verified/`. The portable
verifier and this native result are tracked in Git. No fabricated
compiler frame, original source-origin reassignment, target patch,
new accepted CODE or all-943-unit cold replay.

The formal authored whole-function exact ledger remains
**943 matched complete game functions /862,726 original CODE bytes
(43.71% reviewed)**. The `0041CE50` full destructor is **NONEXACT**.
