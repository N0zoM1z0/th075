# F828 — Real 171B Archive destructor storage-class and unsigned loop grammar

The pinned Japanese TH075 v1.11 original authored nonvirtual
ArchiveCatalog destructor at 0041CE50 is **171 complete callable
CODE B /51 original x86 /14 real PE/COFF fields**.
The source baseline matches original PE instruction mnemonics,
widths and all 14 physical call/global operand positions
and destinations, but only **108/115 comparable native
nonrelocation bytes**. Seven true stack operand bytes
remain wrong. The original local slots are:

| Actual original native value | Original EBP | Current VC7.1 source EBP |
| --- | --- | --- |
| Loop index | -4 | -4 |
| Returned archive-resource pointer | -0xC | -0x10 |
| Actual scalar-delete receiver | -8 | -0xC |
| Filename released with free | -0x10 | -8 |
| Saved destructor receiver | -0x14 | -0x14 |

F828 compiles **15 independent whole** normal pinned
VC7.1 C++ versions of the exact same real resource-deletion,
filename-free and archive cleanup behavior, without
cropping or synthetic locals. Its source changes only
storage qualifiers of the actual used index/filename,
compatible 32-bit index types, or the unsigned loop
condition/side-effect grammar:

| Normal source family | Compiles | Whole emitted CODE | Original native nonfield equal |
| --- | ---: | --- | --- |
| Baseline, register/volatile/unsigned-long/uint32 index | 5 | All identical 171B/51 x86 | 108/115 |
| Register, volatile, const-pointer/const-pointee/volatile-pointee filename | 5 | All identical 171B/51 x86 | 108/115 |
| Register both, volatile both, postfix index increment | 3 | All identical 171B/51 x86 | 108/115 |
| Reversed but mathematically equivalent unsigned comparison, with/without postfix increment | 2 | 171B/51 x86 | **106/115**, worse |

The compiler-generated **entire COFF CODE byte arrays** for
the first thirteen forms are identical. All fifteen
variants preserve the same 14 actual original
PE relocation field positions, kinds, zero source addends
and resolved native call/global targets; every
comparison checks the complete original function, not
a short local fragment. Reversing the unsigned comparison
changes two genuinely non-relocation machine bytes
rather than fixing the original resource/delete/filename
stack ownership.

Independent experimentation also confirms that the
modern-looking __restrict local keyword is not supported
by this pinned VC7.1 toolchain (native compiler C4235).
Those unsupported spelling controls are documented in
ignored exploratory compiler logs, not asserted to be
valid candidate original source.

Thus the remaining exactness blocker is a **genuine
original source lifetime/category difference** affecting
the three EBP stack slots, not 32-bit size spelling,
register/volatile/const storage qualification,
prefix versus postfix increment or syntactic unsigned
loop operand order. No fake padding, object layout,
ABI coercion, handwritten x86 or target patch was used.

Reproduce only the affected whole authored function:

    scripts/repo-python scripts/verify-archive-storage-class-f828.py

Full generated C++/COFF objects, VC7.1 logs and
physical PE evidence are preserved in ignored
.analysis/f828-archive-storage-types/.
The original 171B authored function remains
NONEXACT. **Zero new accepted authored callable CODE
and no 979-unit cold replay.**
