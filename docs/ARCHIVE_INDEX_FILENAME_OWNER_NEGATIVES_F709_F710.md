# F709/F710 — whole 171-byte ArchiveCatalog destructor index/filename lifetime evidence

**Original native/compiler negative controls; no new accepted exact source.**
Pinned user-supplied Japanese TH075 1.11 `resources/th075.exe`, SHA-256
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
The entire authored original nonvirtual `0041CE50` destructor is **171
CODE bytes, 51 real x86 and 14 genuine physical typed PE/COFF fields**.
It conditionally decrements original refcount `[0068BE04]`, runs the
actual index-driven archive-resource `delete` and filename CRT `free`,
and calls both real global container clear methods. No clipped
interior, fake stack memory, EXE patch or non-native compiler ABI.

## Native original slot ownership remains a real three-way rotation

Whole original PE disassembly confirms these *physical* x86 ordinal
stores and corresponding native local object lifetimes:

| Native original x86 ordinal | Real semantic owner | Native EBP | Best previous VC7.1 normal C++ |
| ---: | --- | --- | --- |
| 22 | Borrowed archive resource pointer from `0041DB40` | `−0xC` | `−0x10` |
| 24 | Original scalar-delete receiver | `−0x8` | `−0xC` |
| 38 | Filename pointer from `0041DDC0`, later CRT `free` | `−0x10` | `−0x8` |

The original loop index is `EBP−4`, `this` is `EBP−0x14`, and the
native scalar-delete result is `EBP−0x18`. The selected complete
C++ baseline emits **171 B/51 x86/14 physically typed references**,
but only **108/115 nonrelocation whole-original bytes** match.
The seven differing physical nonrelocation bytes are precisely the
real EBP displacement positions at whole-function offsets
`0x4F,0x52,0x55,0x58,0x60,0x84,0x87`; no branch-target or
COFF byte is being silently excluded. Source CODE length and
relocation-field counts alone never certify byte-exact source.

## F709: simultaneous lifetimes of two *actually used* local values

The earlier F660/F683/F697 experiments mostly changed the filename
local alone. To test a genuinely different compiler lifetime model,
F709 **fresh-compiled eight entire destructor C++ TUs** combining
actual `unsigned index` and `char* filename` declaration order and
scope. Both values are always assigned and used in the original loop;
we tested declarations inside the refcount guard versus before the
guard, plus name-first/index-first and single predeclared-value
controls, keeping the real `delete`, `free`, original calls and
unsigned `index < Names.Size()` comparison intact.

| Meaningful combined source ownership | Complete compiler variants | Original native CODE match |
| --- | ---: | --- |
| Both index and filename predeclared; either lexical order, before or inside guard | **4** | **171 B/51 x86/14 fields; 108/115** nonfield matching, resource/delete/filename still `−0x10/−0xC/−0x8` |
| Only index predeclared, with filename still initialized in loop | **2** | Same **108/115** and wrong original three-way rotation |
| Only filename predeclared; index remains declared in the `for` loop | **2** | **102/115**, worse; filename becomes `EBP−4` and the genuine loop local itself changes |
| **Total** | **8** | **Zero entire native exact** |

Changing two actual local C++ lifetimes together does not naturally
rotate the resource and delete temporary slots to native `−0xC/−8`.
The seemingly promising early filename-only declaration actually
shifts the real index allocation and **regresses** the byte match.

## F710: native cleanup *state* as two genuinely used C++ fields

F710 independently tested **four entire VC7.1 native-shaped
171-B destructor translation units** using
`struct ArchiveCleanupState { unsigned index; char* filename; }`
and the opposite member order. **Both** members are truly read,
written, and used in the original `for`/`delete`/`free` sequence;
there is no inert member, artificial padding or invented extra
operator/call. Declaration before the count guard versus inside
was tested separately for each member ordering.

All four compile to the original-shaped **171 CODE bytes, 51 x86 and
14 physical COFF fields**. `filename,index` member order yields
**108/115** original nonrelocation bytes, with source resource/delete/
filename `EBP−0x10/−0xC/−8`; `index,filename` order regresses to
**102/115** with actual filename at `EBP−4`. The two real fields'
relative placement is not the source of the original compiler's
three-way resource/delete/filename allocation cycle. **0/4 exact**.

All **12 separate, serial VC7.1 `/Od /Ob0 /Gy /GR- /GX- /GS /Zi`
whole C++ translation units** were compiled, their original 171-byte
PE extents re-read through the canonical relocation-aware comparator,
all 14 real fields preserved and all physically comparable bytes
measured. The portable tracked selected-case generator/verifier is
[`scripts/verify-archive-index-filename-lifetimes-f709-f710.py`](../scripts/verify-archive-index-filename-lifetimes-f709-f710.py).
It defaults to **one entire 171-byte C++ build** or can use `--case`
for a named variant and `--all` for just these 12 affected small TUs.
It also asserts the native 51 ordered x86 mnemonics and instruction
widths, all 14 native COFF zero-addend records and the exact seven
actual baseline EBP disagreement positions. Generated complete
CPP/OBJ/log/PE comparison JSON is kept under ignored
`.analysis/f709-f710-archive-full-negative/`.
The first 12 actual source variants, compiler logs and comparison
records also remain **locally** in the ignored directories:

- `.analysis/f709-archive-loop-and-filename/`
- `.analysis/f710-archive-used-iterator-context/`

These private research outputs are not claimed to be tracked in Git
or available on a clean clone. The tracked baseline source and
native-original verifier remain:

```bash
scripts/repo-python scripts/verify-archive-source-types-f609.py --case release-scope-delete
scripts/repo-python scripts/verify-archive-index-filename-lifetimes-f709-f710.py --case F710-index-filename-inside-guard
# Optional ONLY the twelve affected whole destructor sources, never 943 cold units:
scripts/repo-python scripts/verify-archive-index-filename-lifetimes-f709-f710.py --all
scripts/repo-python scripts/validate-tracking.py --require-target
```

**Next evidence direction:** determine a genuine *different original
semantic* resource/delete compiler lifetime or a true object ABI that
naturally explains resource `−0xC`, delete receiver `−8`, filename
`−0x10` **simultaneously**. Repeating normal declarations, plain
`struct` field order, constant casts or artificial unused locals is
not justified by these actual compiler results. The whole original
function is still **NONEXACT**; no new authored exact CODE credit,
no all-943-unit cold replay or external Oracle claim. Official
whole-function ledger remains **943 functions /862,726 native CODE
bytes (43.71% reviewed)**.
