# F584 — original 171-byte ArchiveCatalog destructor delete-expression controls

**Original Japanese TH075 v1.11 full native function evidence and genuine
pinned VC7.1 C++ negative controls — NOT accepted original exact CODE.**
The whole original PE SHA256 is
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
The entire original ArchiveCatalog nonvirtual RAII destructor at
`0041CE50` is **171 bytes / 51 original x86 instructions** with
14 previously attested physical COFF call/global fields. Its borrowed
natural C++ destructor compiles to the same 51 instructions and the
same entire 171 bytes, but **only 108/115 nonrelocation bytes match**.
This remains a genuine, separate whole-function exactness blocker,
not a partial CODE matching claim.

## Re-evaluate the actual original PE, not older C++ descriptions

The new tracked original-only verifier
[`scripts/verify-archive-delete-expressions-f584.py`](../scripts/verify-archive-delete-expressions-f584.py)
first reads original Japanese executable and independently rechecks
actual original x86 instructions and the concrete saved-local
operand slots in the complete function. It verifies that native
instruction 22 stores resource pointer to **`EBP−0xC`**, instruction
24 stores the destructor receiver to **`EBP−0x8`**, and instruction
38 stores the borrowed filename pointer to **`EBP−0x10`**. Those
three native owner-lifetime local positions are the real difference
from the compiler's usual resource/deletion/filename
`EBP−0x10/−0xC/−0x8`. They are not fake padding or unresolved COFF
placeholders; seven actual nonfield CODE bytes differ.

## Twelve genuinely compiled C++ destructor-expression controls

Using one simple source-only nonexact C++ baseline
[`probes/ArchiveCatalogNativeLifetimeF584.cpp`](../probes/ArchiveCatalogNativeLifetimeF584.cpp),
F584 tests the physical original resource-delete expression under
real compiler variations:

- C++ parentheses, `static_cast`, `reinterpret_cast`, C-style cast,
  `const_cast`, and explicit pointer-to-pointer lvalue casts;
- original-equivalent `&*` pointer identity and C++ reference casts;
- correct `ArchiveResourceF343* const&` alias to the same real pointer;
- two constant conditional expressions, explicitly checked as
  *invalid original-size* negative controls, not proposed fixes.

For each new source TU, the original pinned VC7.1
`/Od /Ob0 /Gy /GR- /GX- /GS /Zi` profile (with **`/GX-`**,
matching the nonvirtual non-EH original) freshly compiles the natural
C++. The tracked script independently runs the **complete 171-byte**
original whole-function PE/COFF comparator on every OBJ, not just a
selected snippet or register-only similarity test. Actual result:

| New natural C++ expression controls | Variants | True source compiler output | Original whole-function outcome |
| --- | ---: | --- | --- |
| Ten type/reference/alias forms | **10** | **171 bytes, 51 instructions** | **10/10 nonexact: 108/115 comparable bytes**, same three wrong EBP slots |
| `true ? ptr : nullptr` | **1** | 198 bytes, 58 instructions | Wrong complete original native CODE extent |
| `false ? nullptr : ptr` | **1** | 193 bytes, 57 instructions | Wrong complete original native CODE extent |
| **Total** | **12** | Fresh separate native-profile C++ objects | **0/12 exact** |

The existing F570/F581 independent probes likewise found no trivial
C++ filename declaration or POD/array/union layout that repairs the
original three-way slot permutation. F584 establishes that *the
surface `delete` expression's pointer type/cast AST* also does not
explain the actual original saved-local allocation. The remaining
proper reverse-engineering task is to reconstruct the surrounding
original lexical lifetime/owner context or call semantics that can
naturally cause VC7.1 to allocate the native pointer locals in
its correct order. **No synthetic saved locals, manual asm, raw
byte grafts or fake original ownership are accepted.**

## Targeted reproducibility and no exact-credit changes

```bash
scripts/repo-python scripts/verify-target.py
# One specifically changed nonexact delete-expression source TU:
scripts/repo-python scripts/verify-archive-delete-expressions-f584.py --case cstyle-cast
# Or this twelve-source negative control matrix (not all-unit replay):
scripts/repo-python scripts/verify-archive-delete-expressions-f584.py
scripts/repo-python scripts/validate-tracking.py --require-target
```

Every newly generated source, compiled COFF/PDB, complete-function
comparison JSON and compiler transcript is under ignored
`.analysis/f584-archive-delete-source/`. The original initial
native codegen diagnostic and independently compiled experiments are
preserved in `.analysis/f584-archive-delete-expression/`.
The **943 already accepted exact whole functions and 862,726
original CODE bytes remain unchanged**. No all-unit cold replay,
new accepted partial/whole CODE or DATA, or external Factory/Oracle
acceptance receipt has occurred.
