# F1078 — Twenty fresh whole-original ArchiveCatalog destructor value/lifetime experiments

The pinned Japanese TH075 1.11 game has one original **171 CODE B /
51-x86 nonvirtual ArchiveCatalog destructor at 0041CE50**. It
remains **NONEXACT**, unlike the independently accepted 979 whole
original authored callables. This research compiled **20 new complete,
normal original-shaped MSVC7.1 C++ destructor candidates**, never
cropped functions, patched original bytes or standalone loop bodies.
It directly tests whether the original loop's local stack-slot
rotation could come from true **indexed list element ownership**, a
mutable/const/volatile reference category or a different real
resource destructor/delete lvalue form.

## Native PE facts verified again

The independent pinned original PE has `ESP-0x18` frame, and its
actual used values are stored in these native local slots:

| Native original used local | Native EBP | Selected baseline VC7.1 C++ EBP |
| --- | --- | --- |
| Resource pointer from original resource list `.At(index)` | `-0x0C` | `-0x10` |
| Scalar-delete receiver copy | `-0x08` | `-0x0C` |
| Filename from native names `.At(index)` passed to CRT `free` | `-0x10` | `-0x08` |
| Unsigned original indexed iteration | `-0x04` | `-0x04` |
| Genuine deleting destructor return temporary | `-0x18` | `-0x18` |

The source must preserve the native decrement-count guard,
`unsigned int` resource/name loop, **both actual `.At(index)` calls**,
real deleting destructor call at `0041D8C0`, CRT `free` at `0064169D`
and both original list `Clear()` operations. There are **14 actual
independently typed PE external call/global fields** in the original
entire 171 bytes, occupying 56 bytes of relocation; the remaining
**115 actual non-relocation bytes** decide byte-exactness.

The tracked `scripts/verify-archive-true-element-owners-f1078.py`
re-reads all of these original pinned PE field offsets, types and
destinations and freshly cold-compiles the 20 entire C++ variants.
It includes actual indexed mutable/const/volatile filename references,
indexed element address pointers, direct element dereferences with
reference/const casts, resource pointer-value casts, real pointer-to-
pointer resource/delete ownership and a combined pair of actual used
resource/filename references. No dummy locals, fake padding,
compiler register variables, assembler or byte grafts are used.

| Whole-original-shaped source result | Candidates | Original assessment |
| --- | ---: | --- |
| 171B /51 x86; 108/115 native nonfield byte equality | **6** | Correct 14 PE fields, wrong three EBP owners |
| 171B /51 x86; 102/115 | **5** | Correct 14 PE fields, worse filename-reference EBP flow |
| 165B /49 x86 | **5** | Missing real original CODE instructions; not exact |
| 177B /53 x86 | **1** | Extra genuine pointer lifetime; not exact |
| 179B /54 x86 | **1** | Actual const reference creates extra source instructions |
| 185B /56 x86 | **2** | Two real used reference owners add instructions |
| **20 complete normal VC7.1 source variants** | **20** | **0 original whole exact** |

In every source that retains the authentic 171B/51-x86 shape, the
**entire original 14 physical COFF field positions/kinds and game PE
calculated destinations** still match the original executable; the
remaining differences are true unrelocated EBP stack displacements.
The source's unchanged 108/115 candidate does **not** justify
claiming the other seven bytes exact by masking EBP differences.

The new evidence also refutes the assumption that simply treating
`char**` as a C++ element reference would recover the filename at
native EBP-0x10: its source actually becomes 102/115 nonfield bytes,
with a different real load order. The original full delete receiver
slot remains the same wrong source allocation. Separate native
return-value categories, loop grammar and aggregate-lifetime tests
were previously done; their documents are historical experiments,
not proof of the original C++ declaration syntax.

The original 171-byte authored callable is still NONEXACT with
**zero new accepted exact original code**. A promising next line
is genuine resource-and-filename lifetime interference or compiler
return-object ownership across the deleting destructor, not
rearranging cosmetic loop variable declarations. No all-979 cold
replay was executed, and original PE bytes were never modified.

Reproduce only this one original destructor:

    scripts/repo-python scripts/verify-archive-true-element-owners-f1078.py

Full normal C++/COFF/PDB compiler logs, failed and successful-sized
candidates, original PE physical field positions, and machine-byte
comparisons reside under ignored `.analysis/f1078-archive-element-lifetimes/`.
