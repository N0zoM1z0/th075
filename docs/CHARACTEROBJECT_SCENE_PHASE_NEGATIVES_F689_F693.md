# F689–F693 — actual remaining authored giant/Scene source negatives (NOT accepted exact)

**Verified from the original user-supplied Japanese TH075 1.11 PE,
SHA256 `bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`,
and the complete actual VC7.1 COFF objects preserved in this worktree.**
These are relevant **historical negative experiments from the interrupted
pre-F694 session**. F695 re-read their actual existing OBJ files and
original native PE; it did NOT silently promote precompiled objects to
fresh cold-exact acceptance. All source variants, CPP, OBJ, detailed
logs and machine-byte negative evidence remain in Git-ignored local
`.analysis/` directories; a new clone will not contain them.

## 1. Full original authored giant `004EBDA0` — F690/F692

The original `004EBDA0` owns **33,293 complete CODE bytes,
8,789 actual x86 instructions, 438 separately owned after-RET DATA
bytes and 682 authentic typed PE/COFF relocation fields**.
[`probes/CharacterObjectActionsF572.cpp`](../probes/CharacterObjectActionsF572.cpp)
is still the best selected normal VC7.1 source: **30,866/31,003
nonrelocation bytes** match the entire native CODE+DATA; **137
nonfield bytes across 133 original instructions** still differ,
concentrated in the real `0x38D`, `0x38E`, `0x3E3` GPR phases.
The first wrong native instruction is x86 ordinal 8,076, PE
`004F344C` (`MOV EAX,[EBP−0x40]`), whereas current normal C++
compiles `MOV ECX,[EBP−0x40]` at that same physical offset.

F690/F692 independently compiled **28 actual source alternatives**
targeting real `0x38D` stage-3 float fade, stage-4 branching,
read-only float lvalues, `+=`, signed-short tests, boolean inversions,
and real member access. The F695 audit directly decoded their
**28 complete actual compiled COFF objects**, original PE and
actual field masks. Actual object sizes, native boundaries and
nonfield differences are:

| Distinct complete C++ variants | Entire generated CODE+DATA | Native x86 | Real source PE/COFF refs | Actual full-native mnemonic/width positions wrong | Native nonfield bytes wrong |
| --- | ---: | ---: | ---: | ---: | ---: |
| **16** compiler-equivalent ordinary expressions | **33,731 B** | **8,789** | **682** | **0** | **137** |
| **4** first/second float-lvalue or `+=` forms | **33,731 B** | **8,789** | **682** | **2** each | **138** |
| **3** combined float-lvalue/`+=` forms | **33,731 B** | **8,789** | **682** | **4** each | **139** |
| **1** subtraction-style stage-4 condition | **33,731 B** | **8,789** | **682** | **1** | **137** |
| **4** boolean/range stage-4 conditions | **33,739–33,743 B** | **8,792–8,793** | **682** | **hundreds** from real changed CFG | Not comparable to whole correct-length function |
| **Total: 28 actual tested whole-parent sources** | | | | | **ZERO exact** |

The 137/138/139 mismatch counts are **real native non-COFF
byte differences**, masked only at **physical original and compiler
COFF field spans** when a variant shifts an authentic field. A
matching total x86 count or total output bytes does **not** imply
unchanged x86 ordinal geometry: four plus three variants really
altered the compiler's `FLD`/`MOV`/x87 widths. None can be accepted
as original whole CODE; do not misread 682 source references as
actual 682 linked byte identities when offsets differ.

One exploratory nested-scope C++ generation was initially malformed,
causing an unhelpful compiler timeout. The source braces were
corrected and the **complete 33,731-B/8,789-x86** parent compiled;
it still had **137** original nonfield differences and no geometry
improvement. This invalid original script generation is not a
successful source hypothesis.

Local recoverable research paths:
`.analysis/f690-characterobject-phase/` (fade and evaluation-order
variants) and `.analysis/f692-characterobject-stage4/` (stage-4
branch variants and `native-honest-audit.json`). The formerly
proposed `scripts/verify-giant-phase-and-scene-scope-f693.py`
**was never successfully written or committed** when the native
factory disconnected; do not instruct the next agent to run that
nonexistent file. Existing tracked F596/F635 verifiers remain
canonical for cold re-testing just ONE affected whole native giant.

## 2. Complete authored Scene destructor `0043B0B0` — F689

The true original is **248 complete CODE B /75 native x86 /
12 genuine typed PE/COFF fields**. Original native source slots
for two texture-delete temporaries are `[EBP−0x14]` and
`[EBP−0x10]`; three conditional CRT-free values occupy
`[EBP−0x18]`, `[EBP−0x1C]` and `[EBP−0x20]`.
The current ordinary C++ can reproduce the 248-B/75-x86 geometry
and all 12 physical source fields, but the whole original comparison
is **191/200 nonrelocation bytes**, with five wrongly owned EBP
locals. Do not normalize or ignore these real stack displacements.

F689 compiled **10 full original Scene destructor source
candidates** with actual three-resource conditional cleanup:
**eight** normal used scoped-pointer forms emitted **248/75/12**
but *regressed* to **189/200** original comparable bytes;
**one** meaningful lexically nested aggregate remained at
**191/200**. The tenth early split-aggregate experiment produced
**177/200**, but its extra unused aggregate is *artificial
source-only state* and should **not** be used as a live reconstruction
candidate. No legitimate variant recovered original EBP ownership.
Existing ignored sources/objects/logs and `summary.json` live at
`.analysis/f689-scene-nested-lifetimes/`. The tracked F589 and F612
original-native verifiers remain canonical; no additional exact
function was registered.

## What the next agent should actually try

The whole 33K boss failure now points to a **cross-case register
phase/lifetime choice at native stage-4**, not type-equivalent float
constants, simple `+=`, or equality test spelling. Study the
original instruction roles across the **preceding stage-3 block,
the shared case exit and the next 0x38E native case** in a fresh
complete original-shaped parent; preserve all original case
boundaries, physical COFF fields and after-RET DATA.

For the Scene destructor, investigate real source object/texture
**lifetime allocation order** before the delete and triple-free
sequence, not artificial extra locals or renaming `void*` types.
The 171-byte authored ArchiveCatalog destructor is a separate
unresolved whole native extent; see
[F682/F683 real negative source grammar](ARCHIVE_RESOURCE_FILENAME_LIFETIMES_F682_F683.md).

```bash
# One fresh complete 33KB parent only, not the 943-unit registry:
scripts/repo-python scripts/verify-characterobject-native-collision-order-f596.py
# One alternative true original parent control, if pursuing typed roles:
scripts/repo-python scripts/verify-characterobject-typed-member-f635.py --case 38d-zero-velocity-as-bits
# One 248-byte Scene original control with actual native COFF fields:
scripts/repo-python scripts/verify-scene-texture-delete-f589.py --case paren
# Fast live provenance/byte-accounting checks:
scripts/repo-python scripts/validate-tracking.py --require-target
scripts/repo-python scripts/report-reconstruction-status.py --summary
```

No changes to `config/functions.csv`, original provenance,
`config/matches.csv` or accepted whole-unit ledger; **943 accepted
authored whole functions/862,726 CODE bytes/43.71% reviewed**
remains the correct baseline. **No full cold replay, fake local
padding, masked EBP scratch or original executable patching**.
