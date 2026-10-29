# F682/F683 — 39 independent whole authored archive destructor source-lifetime controls

Pinned user-supplied Japanese TH075 v1.11 `resources/th075.exe`, SHA256
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
This document **preserves negative original-code evidence**, not a
new exact whole function or an exception to source/provenance rules.
The *original authored whole* nonvirtual `ArchiveCatalog` destructor
`0041CE50` owns **171 entire native CODE B /51 x86 /14 genuine PE/COFF
fields**. Its real native receiver `this` is EBP−0x14, loop index
EBP−4, resource pointer copy EBP−0xC (original ordinal 22), delete
receiver EBP−8 (ordinal 24), return-delete result EBP−0x18,
and released filename EBP−0x10 (ordinal 38). Native classes are
provisional but all those physical PE operands are directly observed.

Current normal pinned VC7.1 `/Od /Ob0 /Gy /GR- /GX- /GS /Zi`
C++ source in
[`ArchiveCatalogNativeLifetimeF584.cpp`](../probes/ArchiveCatalogNativeLifetimeF584.cpp)
reproduces all **171 original byte widths /51 x86 mnemonic positions
and 14 genuine PE/COFF fields**, but gets the source local assignment
**resource −0x10, delete receiver −0xC, filename −8** instead of
original **−0xC, −8, −0x10**, yielding only **108/115** truly matching
nonrelocation CODE bytes. This displacement cycle is *not* a
PE/COFF linking problem and must not be masked or accepted as exact.

## F682: 22 meaningful resource-pointer lifetime and delete-expression experiments

Every variant recompiles the **entire original authored destructor
translation unit**, with the real resource/filename lists, actual
native `delete` and `free`, index loop and both genuine global-list
clears. Unlike the older F660 filename-declaration experiments,
these explicitly vary the genuine **resource pointer**, investigating
whether its source lifetime can reserve the native delete temp slots
*before* the filename value is assigned.

| Distinct normal C++ original-source controls | Count | Full native-like compiler result | Actual original whole acceptance |
| --- | ---: | --- | --- |
| Used resource values, const values, pointer/pointee references, pointer slots, early resource declarations and loop-outer lifetime, scope-blocked resource deletion, resource bit/pointer casting, and combined meaningful filename lifetimes | **21** | **177 compiled CODE B /53 x86 /14 physical fields**; two extra instructions/6 CODE B, so **not** original 171/51 | **NONEXACT** |
| Original resource-expression rvalue with a static cast | **1** | **171 B /51 x86 /14 physical fields**, original mismatch **108/115 nonrelocation bytes**, source slots still `−0x10/−0xC/−8` | **NONEXACT** |

These trials show that **naming the actual resource pointer**
creates genuinely additional VC7.1 lifetime/store-load instructions
rather than the exact original two-delete-temp-plus-filename pattern.
The earliest resource-scope forms can change generated EBP ownership,
but none recovers the original physical **171-B/51-x86** geometry and
three matching real slots together. It would be invalid to delete
those authentic source instructions by patching bytes or adding a
fake declaration with no semantic use. All freshly built source,
COFF/PDB, compiler logs and the result receipts are preserved under
ignored `.analysis/f682-archive-resource-lifetime/`.

## F683: 17 additional filename-storage and register/type hypotheses

These deliberately keep the original *direct resource deletion*
expression and independently alter only a **meaningful filename
value** in the existing original native release/free sequence.
All 17 were cold-compiled or attempted in the **same selected whole
171-byte source TU** under pinned VC7.1 `/Od`.

| Normal C++ controls | Count | Full-original source outcome |
| --- | ---: | --- |
| `register char*`, `register void*`, plain `void*`, `const char*`, volatile filename local variants, meaningful integral pointer-address locals (`int`, `long`, `size_t`, unsigned), register loop/index, const-register pointer and actual typed CRT `free` casts | **14** | All generate **171 CODE B/51 x86/14 original fields**, still **108/115** genuine nonrelocation bytes; all three EBP stack slots remain cyclically wrong |
| Genuine filename pointer or const-pointer reference bound to the list slot | **2** | **171 B/51 x86/14 fields** but original matching worsens to **102/115**; different actual pointer dereference role, reject |
| `__restrict` filename declaration | **1** | **VC7.1 C4235**: source grammar not supported by the pinned original compiler, reject rather than silently alter toolchain |

The result proves that the original genuine EBP allocation blocker
is not resolved by adding a `register` storage hint, a volatile
pointer value, changing filename type/signedness, moving list index
storage, or hiding the pointer in an integer with a real round-trip
free. These 17 complete sources, compiler logs and result receipts
are preserved under ignored `.analysis/f683-archive-name-types/`.

## Targeted reproduction and next remaining original question

These new **39 independent meaningful VC7.1 source variants** were
actually compiled and compared against **the full original native
171-byte extent**, not just partial CODE or one store instruction.
They preserve earlier F625/F660 findings: a **direct no-filename-local
free** produces the original resource/delete slots but only
**165 B/49 native-like instructions**, whereas reserving the named
filename local restores **171/51** but shifts the earlier resource
stack ownership. What historical C++ AST/temporary lifetime
produces **both** exact original delete pointer ownership and the
two genuine named filename store/reload instructions remains open.

```bash
# Older selected whole-function source comparison, one affected control:
scripts/repo-python scripts/verify-archive-source-types-f609.py --case release-scope-delete
scripts/repo-python scripts/validate-tracking.py --require-target
```

New F682/F683 research changes **zero accepted exact game-authored
functions or CODE bytes**. The authored ArchiveCatalog destructor
remains one of three nonexact smaller whole functions (alongside
248-byte Scene destructor and 2,987-byte WinMain). Formal exact
coverage remains **943 complete authored functions /862,726
original CODE bytes (43.71% reviewed)**. Neither original game EXE
patching nor any 943-unit full cold replay was performed.
