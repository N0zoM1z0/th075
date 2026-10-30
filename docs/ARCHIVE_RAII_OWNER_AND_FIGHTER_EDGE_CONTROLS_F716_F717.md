# F716/F717 — real ArchiveCatalog RAII lifetime and large fighter edge-CFG controls

**All experiments were compiled against the pinned original Japanese TH075
v1.11 target; none is byte-exact or accepted to the authored ledger.**
The user-supplied `resources/th075.exe` SHA-256 is
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
All machine-code comparisons concern the complete original physical
function or internal case, real C++ source, and true PE/COFF fields;
there is no binary graft, invented unused local, arbitrary padding
or all-943-unit cold replay.

## F716: whole 171-byte ArchiveCatalog original destructor, genuine RAII owner

The original authored complete destructor `0041CE50` is **171 CODE B,
51 native x86**, with 14 original typed PE/COFF fields and a direct
CRT `_free` `CALL 0064169D` at real native x86 ordinal 41. Original
resource/delete/filename stack owners are respectively
`EBP−0xC/−0x8/−0x10`; the selected ordinary VC7.1 baseline still
produces **171 B/51 x86/14 native-shaped fields**, but **108/115**
nonrelocation bytes equal and incorrect `−0x10/−0xC/−8` owner slots.
Previous direct filename type, declaration timing, pointer/reference
and simple aggregate hypotheses did not solve that rotation.

F716 tests a genuinely different original C++ lifecycle model:
perhaps a small **actually used class object owns the filename and
calls `free` at scope exit**, or another scoped object really owns
and deletes the archive resource *before* the filename release.
Unlike an unused local intended to force EBP padding, every class
value is loaded from original container `At(index)` and its destructor
or `Release()` performs real CRT free or scalar resource delete.
These source patterns are behavioral candidates only where their
release scope preserves original delete-before-filename-free order;
placing an owner before the loop/guard is a diagnostic counterexample,
**not** a claimed behaviorally identical original program.

**Sixteen complete C++ ownership/scope source objects** were compiled
with pinned VC7.1 `/Od /Ob0`, independently compared to the
original 171-B/51-x86 body, with actual COFF symbols examined:

| Real source-owner/ABI model | Whole compiled original-shaped function | Why it cannot be native byte-exact |
| --- | --- | --- |
| Filename owning destructor/member release method (seven diagnostic + source-valid forms) | **167 B/49 x86/14 source COFF fields** | Original `MOV local; PUSH local; CALL _free; ADD ESP,4` becomes `LEA owner; CALL F716NameRelease::~F716NameRelease` or `Release()`, with two fewer x86 instructions; the 14 fields are not the same original target destinations |
| Early filename owner whose destructor now runs outside the original per-iteration scope (two diagnostic forms) | **163 B/49 x86/14 fields** | Actual cleanup ordering differs from original; cannot infer original lifetime |
| Same filename scope owner, but `/GX` EH-enabled | **212 B/58 x86/18 fields** | Extra actual EH setup and handler shape; original 171-B destructor has no such EH frame |
| Scoped real resource owner destructor or `Release`, at the point before filename `At()` | **141 B/43 x86/14 fields** across six early/scoped variants | Native scalar-deleting-destructor `CALL 0041D8C0` is replaced by another owner helper call; correct temporal release in the local block still does not match native |

In the last row, resource-owner declarations before the loop or count
guard are retained only as **semantic negative controls**, since the
class destructor's lifetime then extends beyond native resource
release. No early-object variation restored native source slots.

Additional **eight complete diagnostic optimizer-profile builds**
tested `/Od /Ob1` and `/Od /Ob2` for real inline filename/resource
owner methods. Unlike the pinned `/Od /Ob0` profile, `/Ob1` naturally
**inlines** the helper into the caller and restores a direct `_free`
call, but still emits **197 B/58 x86/15 fields** for the filename
owner or **203 B/60 x86/15 fields** for the resource owner. `/Ob2`
has the same results. Original 171/51/14 remains unmatched.
Changing the compiler's original profile to manufacture matches is
not permitted; this test isolates a real compiler inlining behavior.

Tracked standalone selected source generator/verifier:
[`scripts/verify-archive-raii-owner-f716.py`](../scripts/verify-archive-raii-owner-f716.py).
It reads the complete original PE and the actual native saved EBP
slots/direct `_free` before serially compiling a single entire C++
object by default, or exactly **seven** representative affected
C++ owner/profile controls via `--all`; it independently checks
source whole CODE size/x86, actual PE-related COFF counts and the
helper-inlining/direct-CRT-free distinction. It **never labels
matching reference count as original-target equivalence**, because
these RAII helpers genuinely change the source symbol destinations.
All sixteen `/Ob0` source alternatives, eight extra profile objects
and PE/COFF evidence remain under Git-ignored local
`.analysis/f716-archive-semantic-release-owner/`. New portable
seven-case verifier output goes to
`.analysis/f716-archive-semantic-release-verified/`.

## F717: whole 58KB fighter C++ contact-wall CFG structure trials

Original authored fighter `00543210` is still **58,294 CODE B** with
separate 943-byte after-RET switch DATA. Newly restored source-backed
internal `0x2DB` (`0054E451`–`0054E851`) owns **1,024 native CODE B,
290 x86, 34 genuine physical typed PE/COFF fields**; its selected
F715 C++ emits **1,032 B/292 x86/34 original destination fields**
with two genuine extra `FLD/FCOMPP` vs original memory `FCOMP`
operations at original x86 ordinals **129 and 141**. The remaining
float/branch behavior, NaN edge handling, GPR and EBP roles are
NONSTRICT, not an exact game function.

Following the nine previously measured equivalent float/boolean
expression controls, F717 independently tested a different original
source hypothesis: explicit **real short-circuit control-flow
structure** for the four actual contact/facing/boundary conditions.
Five whole original-shaped VC7.1 parent builds used genuine branch
chains with common real state-transition labels or nested `if`
statements, with direct, negated or inverse-ordered real boundary
comparisons. All retain the real `2DB` contact predicates and the
**34 physical typed source references**; they are source grammar
controls, not fake x86 JMPs or accepted gameplay source.

All five generate **1,042 B/297 x86**, rather than original
**1,024 B/290 x86** or the prior, closer 1,032/292 source baseline.
The explicit CFG style changes genuine branch instruction shape
and adds other real opcode/width differences. It does **not** remove
the original two extra compare operands or improve byte-exactness;
the F714/F715 tracked C++ baseline is therefore retained unchanged.
Actual source, compiler OBJ/PDB/log and full original-action mnemonic
edit matrices reside under local Git-ignored
`.analysis/f717-fighter-edge-control-flow/`.

## Run only affected whole source targets

```bash
# Original whole ArchiveCatalog destructor: one meaningful RAII control
scripts/repo-python scripts/verify-archive-raii-owner-f716.py --case name-dtor-Ob0
# Optional: only seven selected source owner/profile controls
scripts/repo-python scripts/verify-archive-raii-owner-f716.py --all
# Real original fighter 2DB/2DC full-parent context, one giant TU
scripts/repo-python scripts/verify-fighter-complex-movement-f714-f715.py
scripts/repo-python scripts/validate-tracking.py --require-target
```

No original 171-B full destructor exact match; no complete 58KB
fighter exact match; no function-origin promotion. Formal whole
source-backed authored ledger stays **943 exact functions and
862,726 original CODE bytes (43.71% reviewed)**.
