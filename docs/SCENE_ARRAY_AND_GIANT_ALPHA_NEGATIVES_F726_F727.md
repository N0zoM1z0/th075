# F726/F727 — complete 33KB fighter typed-alpha source and 248B Scene array-owner negatives

**Actual pinned Japanese TH075 1.11 native PE vs real VC7.1, not original
whole-function byte-exact acceptance.** User-supplied target
`resources/th075.exe` SHA-256:
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
All source variants below compile the entire actual original-shaped
game function, not an isolated snippet, fake local stack padding or
original executable byte graft. None changes the canonical authored
exact-match ledger or requires a full 943-unit cold replay.

## F726: actual 33,293-byte authored giant—two *used* float members

The authored whole `004EBDA0` CharacterObject-type boss owns **33,293
CODE bytes** and **438 separately owned after-RET DATA bytes**, total
**33,731 PE section bytes**, with **8,789 original native x86
instructions** and **682 physically typed original COFF fields**.
The selected natural original-shaped source
[`probes/CharacterObjectActionsF572.cpp`](../probes/CharacterObjectActionsF572.cpp)
retains the original whole instruction and relocation geometry with
exactly **137 wrong nonrelocation bytes**. The first is original
`004F344C` (`MOV EAX,[EBP−0x40]`) versus C++ compiler
`MOV ECX,[EBP−0x40]` in original action `0x38D`, followed by
actual GPR phases in original `0x38E/0x3E3`. These differences
are **real machine-code bytes**, not structural equivalence.

F726 tested **ten additional entire 33,731-B /8,789-x86 /
682-field natural VC7.1 source variants**. They were chosen to
change actual used source data or real stage-control flow, not
invent unused dummy locals: source `+=` on the original two adjacent
float fields `this+0x1C` and `this+0x20`, reversed/negated actual
`stage < 3` condition, and a real two-float
`struct {float first;float second;}` lvalue overlay on those
physically adjacent original actor members. The overlay is an
**unverified original class-type hypothesis** and is used only as a
negative compiler experiment, never as author-attributed source.

| Full native-shaped original C++ hypotheses | Number | Whole machine-code finding |
| --- | ---: | --- |
| Genuine negated or reversed stage-three guard | **2** | Original **33,731 B/8,789 x86**, all **682 typed original field locations and types** unchanged, **137 real nonrelocation bytes still wrong**; original 38D register first mismatch unchanged |
| First/second/both actual used float `+=` | **3** | Whole size, x86 count and **682 COFF count** unchanged, but at least one original field **physically moves by −3 bytes** (e.g. global at original field offset 30352 becomes 30349); original relocation geometry **fails** |
| Real two-float structured member reads/writes and stage-four scale ownership | **5** | Whole size, x86 count and 682 COFF count unchanged; **one or two actual PE/COFF fields move by −3 bytes**. These are **not** valid original relocation layouts and have no legitimate normalized mismatch count |
| **All complete 33KB originals attempted** | **10** | **0** new byte-exact whole game functions |

The last eight results **must not be reported as “0 wrong bytes”**.
Their native relocation masks are not even congruent with the pinned
original, so the earlier comparison's result was correctly recorded
as **invalid geometry**, not as a numerical byte score. The real
`+/=` compiler instruction and source-member grammar control evidence
shows that changing a real C++ lvalue can shift PE field ownership
without changing code length. The previous 137-byte selected source
remains the best physical native-shaped baseline.

Actual whole C++ files, OBJ/PDBs, compiler transcripts, PE byte and
COFF relocation comparison results are preserved locally under
ignored `.analysis/f726-33k-typed-alpha-owner/`, including
`trials.py` and `summary.json`. Recheck the current target and whole
source evidence via tracked
`scripts/verify-characterobject-native-collision-order-f596.py`
and `scripts/verify-characterobject-whole-geometry-f593.py` for their
selected original source contexts. F726 itself does not claim a
new canonical exact result.

## F727: complete original 248-byte Scene virtual EH destructor

The authored original `0043B0B0` is a **complete virtual destructor
with exception handling**: **248 original CODE bytes, 75 original
x86 instructions and 12 genuine typed PE/COFF references**.
It conditionally deletes one original texture manager, then
conditionally CRT-frees each of three actual scene resources and
calls the authentic base destructor. Original physical x86 local
stores at ordinals 26,28,42,52,62 use native
`EBP−0x14/−0x10/−0x18/−0x1C/−0x20`.
The previous source has original mnemonic/width geometry and 12
physical typed fields, but generates texture/delete locals at
`EBP−0x20/−0x1C` instead of the native `−0x14/−0x10`, and the
three free-pointer slots in the wrong source ownership sequence;
**191/200** nonrelocation bytes match at best.

To investigate a real object *ownership type*, F727 freshly compiled
**12 entire C++ Scene destructor TUs** using a **genuinely used
`void* released[3]` array**. Each of the three existing resources
is assigned into one distinct element and the exact element is
subsequently passed to an actual CRT `free` call. All six actual
index permutations were compiled, with the array declared before
or after the real conditional texture `delete` (two genuine lexical
scope possibilities). All source forms preserve the scene state,
base destructor, all three true frees and texture deletion; there
are **no unused array elements or fake padding variables**.

| Complete used-resource array ownership | Fresh VC7.1 `/Od /GX` entire destructor | Pinned original PE comparison |
| --- | ---: | --- |
| Actual original resource 0 in array slot 0; remaining two resources in either other order, early or late array declaration | **4 variants**, 248 B/75 x86/12 original typed fields | **191/200** original nonrelocation bytes equal |
| Original resource 0 in array slot 1 or 2; all other true permutations, early/late | **8 variants**, 248 B/75 x86/12 original typed fields | **189/200** original nonrelocation bytes equal |
| **Twelve full function compiler builds** | **12/12 original mnemonic and instruction-width geometry** | **0/12 native complete functions byte-exact** |

All twelve generated source texture/delete scratch slots remain
`EBP−0x20/−0x1C`; the three used `free` values move between
`−0x18/−0x14/−0x10` according to their actual array indexing,
never the original five-slot ownership graph. Thus array indexing
alone is not an explanation for the original compiler-generated
texture lifetime. The genuine original candidate class layout is
still unresolved; neither physical geometry nor `191/200` is exact.

Portable tracked reproduction:
[`scripts/verify-scene-array-owner-f727.py`](../scripts/verify-scene-array-owner-f727.py)
reads the pinned entire original 248-B PE, native 75 x86, and all five
real EBP scratch slots; serially compiles **one selected whole Scene
C++ destructor by default** (`--case` chooses another), or **only
these 12 directly affected full small functions with `--all`**.
For every variant it verifies the entire 248B/75 x86 source,
12 typed native PE/COFF records through the canonical native
relocation-aware comparator, and the honest **191/200 or 189/200**
raw nonfield-byte mismatch. No original code is cropped.

```bash
scripts/repo-python scripts/verify-scene-array-owner-f727.py --case array-012-after-texture
# Optional only the twelve affected actual Scene source variants
scripts/repo-python scripts/verify-scene-array-owner-f727.py --all
scripts/repo-python scripts/verify-scene-texture-delete-f589.py --case paren
```

All actual private CPP/OBJ/PDB, compiler logs and whole original PE
comparison receipts live under ignored
`.analysis/f727-scene-genuine-array-owner/` and
`.analysis/f727-scene-genuine-array-owner-verified/`.

Neither the 33KB giant nor the 248B authored destructor is
byte-exact; original provenance remains unchanged, no target EXE
edits or 943-unit full cold replay. **Formal authored exact coverage
remains 943 whole game functions and 862,726 original CODE bytes
(43.71% reviewed)**.
