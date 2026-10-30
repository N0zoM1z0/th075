# F719 — full original ArchiveCatalog destructor: used loop-local lifetime controls

**Twelve new complete C++ source/compiler NEGATIVES, no game exact credit.**
Pinned original is user-supplied Japanese TH075 v1.11
`resources/th075.exe`, SHA-256
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
The actual complete authored nonvirtual ArchiveCatalog destructor
`0041CE50` is **171 CODE bytes, 51 native x86 instructions, 14
real original typed PE/COFF fields**. It performs original shared
refcount decrement, indexed native resource scalar `delete`, filename
CRT `free`, and two global container cleanup calls. Its native loop
index is `EBP−4`, saved receiver at `−0x14`, and real resource/
scalar-delete-receiver/filename owner stores at x86 ordinals
`22/24/38` use respectively **`EBP−0xC/−0x8/−0x10`**.
The prior best actual normal C++ generated **171 B/51 x86/14 fields**
but stores those three used values at **`−0x10/−0xC/−8`**. The
native original mismatch is exactly seven actual nonrelocation
bytes, at whole-function offsets `0x4F/0x52/0x55/0x58/0x60/
0x84/0x87` (108/115 original nonfield bytes match).

## New hypothesis and measured whole-function C++ evidence

F709/F710 previously varied declarations *outside* the loop body
and used two-field aggregates. F719 independently checks a different
source ownership distinction: **a genuine used `filename` pointer
can be declared at the start of the original loop, *before* the
resource `delete`, but still assigned/freed strictly after it**.
This is important because VC7.1 `/Od` often allocates temporaries
based on C++ declaration scope, not dynamic assignment order.

The new actual experiments compile **twelve ENTIRE original-shaped
171-B destructor C++ translation units** using pinned VC7.1
`/Od /Ob0 /Gy /GR- /GX- /GS /Zi`, not just the truncated
loop or a stand-in small function:

| Actual, used source local and evaluation model | Whole VC7.1 resulting CODE | Authentic original PE comparison |
| --- | --- | --- |
| Filename declared before resource deletion *inside the loop*, also separately with real nested block, volatile named pointer, or a real inner resource block | **4 variants: 171 B/51 x86/14 COFF fields** | Each retains **108/115** original nonrelocation bytes; three EBP owners still `−0x10/−0xC/−8` |
| Filename initialized to NULL before actual resource deletion, then assigned from the original names container | **178 B/52 x86/14 fields** | Additional real initializer store/length; not exact |
| Named, actually used `ArchiveResourceF343*` obtained from `Resources.At(index)`, declared before or after filename; also real named `ArchiveResourceF343**` entry-pointer access | **6 variants: 177 B/53 x86/14 fields** | Extra real pointer lifetime instructions; original native is only 171 B/51 x86 |
| Add an actual extra `Resources.At(index)` non-null check before native `delete` | **189 B/57 x86/16 fields** | This changes source control flow and invokes an additional container lookup; **not behaviorally equivalent to original** and not eligible for source adoption |
| **Twelve complete native-profile C++ source controls** | | **Zero original whole functions exact** |

All *genuinely used* pointers are assigned/read and the normal path
retains real native resource deletion followed by filename release.
We explicitly flag the extra-pointer-check candidate and
zero-initialization case as diagnostic, not proof of the original
source's semantics. No fabricated unused local, bogus caller ABI,
manual x86 instruction, original EXE modification or arbitrary
padding was used. Four native-length candidates were checked with
the canonical **whole-function original PE relocation-aware comparator**,
all **14 physical typed fields**, 51 native ordered mnemonic/width
positions and the same seven nonfield mismatching EBP bytes. The
other eight candidates' exact generated **CODE length, x86 count
and 14/16 source COFF fields** were inspected and kept *negative*;
they are not compared via an artificially cropped 171-byte prefix.

## Reproducibility and continuation

The portable tracked complete source generator and checker is
[`verify-archive-loop-local-lifetimes-f719.py`](../scripts/verify-archive-loop-local-lifetimes-f719.py).
It reads/validates the pinned native original 171 B, 51 x86 and
three original stack owners before compiling **only one selected
entire destructor** by default. `--case` selects an individual
hypothesis, and `--all` builds only the twelve affected small
original-shaped C++ sources, not all 943 previously accepted units.
Actual private CPP/OBJ/PDB, compiler transcripts and original PE
comparisons are preserved in ignored local
`.analysis/f719-archive-early-loop-temporaries/` and
`.analysis/f719-archive-early-loop-verified/`; they are not
silently removed or claimed to be Git-tracked artifacts.

```bash
scripts/repo-python scripts/verify-archive-loop-local-lifetimes-f719.py --case name-declared-before-delete
# Optional: only twelve affected entire small native-source experiments
scripts/repo-python scripts/verify-archive-loop-local-lifetimes-f719.py --all
scripts/repo-python scripts/verify-archive-source-types-f609.py --case release-scope-delete
```

Result: the real native **three-way resource/delete/filename EBP
allocation cannot be recovered by early declaration alone**. Future
work should investigate actual original resource-owner construction,
object lifetime and native compiler-generated delete temporaries,
not repeat equivalent declaration/aggregate permutations or
invent inert locals. The entire original 171-byte function remains
**NONEXACT**, with no accepted authored whole-function CODE.
Official coverage stays **943 authored exact whole functions /
862,726 original CODE bytes (43.71% reviewed)**. No full cold replay.
