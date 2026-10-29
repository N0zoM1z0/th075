# F609 — authentic 171-byte ArchiveCatalog destructor local-ownership negatives

**New selected VC7.1 source-type and lexical variants versus the entire
original pinned Japanese TH075 1.11 PE. No new accepted game CODE.**
Original executable SHA256:
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.

The existing authored nonvirtual destructor `0041CE50` is one of three
still-unmatched smaller whole game functions. The original complete
extent contains **171 CODE bytes, 51 x86 instructions and 14 physical
COFF calls/globals**. Original compiler-owned local slots are:

| Native x86 ordinal | Real original PE EBP local | Present natural VC7.1 C++ |
| --- | --- | --- |
| 22 | resource pointer at `EBP−0xC` | `EBP−0x10` |
| 24 | deletion receiver at `EBP−0x8` | `EBP−0xC` |
| 38 | freed filename pointer at `EBP−0x10` | `EBP−0x8` |

These are genuine code-byte differences, not pointer relocations or
extra afterRET DATA. The baseline original-looking source is
[`ArchiveCatalogNativeLifetimeF584.cpp`](../probes/ArchiveCatalogNativeLifetimeF584.cpp).

## Nineteen new actual compiler tests, all genuinely nonexact

The new independent
[`verify-archive-source-types-f609.py`](../scripts/verify-archive-source-types-f609.py)
generates and compiles each selected real C++ source under pinned VC7.1
`/Od /Ob0 /Gy /GR- /GX- /GS /Zi` (the actual non-EH destructor
profile). It compares the **whole original native function**, x86
instruction count/geometry, and all fourteen real physical typed
COFF fields via the canonical original-PE comparison helper. Every
candidate also must retain the actual three native-versus-generated
EBP owner slots listed above. Failed source/COFF/PDB compiler runs,
full original comparison JSON and a 19-case manifest remain under
ignored `.analysis/f609-archive-source-types/`.

The original-native experiment matrix included actual signed `int`,
`signed long`, `unsigned long`, `size_t` loop index types; explicit
signed-to-unsigned condition conversion; alternative modulo-equivalent
increment syntax; diagnostic `!=` instead of `<` loop termination;
real nested C++ scopes around the delete or filename release; direct
`free` lvalues, pointer identity and C-style/static const conversions;
and full unsigned/parenthesized loop-bound forms. The `!=` termination
is a **diagnostic alternative**, not asserted semantically identical
under all possible dynamically changing container-size behaviors.

| Recompiled original-size alternatives | Whole generated CODE | x86 | Typed COFF | Nonrelocation bytes identical to native |
| --- | ---: | ---: | ---: | ---: |
| 18 selected signedness/scope/cast forms | 171 B each | 51 each | 14 each | **108/115** |
| `index != Names.Size()` diagnostic | 171 B | 51 | 14 | **107/115** |
| **19 whole-function source comparisons** | | | | **0 byte-exact matches** |

None fixes the native temp allocation `−0xC/−0x8/−0x10`; the generated
source stays `−0x10/−0xC/−0x8`. These original-PE negative results
narrow the next source search to *actual destructor resource/ownership
lifetime representation* or other authentic type context, rather than
repeating superficial loop signedness, declaration scopes or casts.

**The complete original 171-byte destructor is still NONEXACT.**
Do not promote any partial `108/115` source to `config/matches.csv`,
count the 14 COFF fields as accepted CODE, invent fake stack locals,
patch the target binary, or declare a new whole exact function. The
official authored whole-function ledger is still **943 exact functions,
862,726 native CODE bytes**. The 33K `004EBDA0` giant separately
remains at 137 nonrelocation byte differences as independently checked
this round. F607/F608's giant case progress is also not independent
whole-function exact credit.

## Targeted reproduction only

```bash
scripts/repo-python scripts/verify-archive-source-types-f609.py --case signed-index
scripts/repo-python scripts/verify-archive-source-types-f609.py --case loop-inequality
# Optional exactly the nineteen new SMALL affected source TUs, not all exact units:
scripts/repo-python scripts/verify-archive-source-types-f609.py
scripts/repo-python scripts/validate-tracking.py --require-target
```

The entire original game target, tracking files, and old accepted
source/match-unit manifests remain untouched. There was no 943-unit
cold replay or remote Oracle acceptance.
