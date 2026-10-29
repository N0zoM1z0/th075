# F665 — four new complete original native member-call wrappers, origin UNKNOWN

Pinned Japanese TH075 v1.11 `resources/th075.exe`, SHA256
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
Four distinct registered original functions are reconstructed as
**entire linked native machine CODE**, without falsely claiming that
the historical functions were explicitly authored game C++ rather
than compiler-generated/lifetime or library wrappers. Their original
`function-origins.csv` records remain **`unknown,review`**; the
provisional C++ class names are compiler-grammar probes only.

## Genuine original complete native byte identity

| Registered original entire PE function | Actual original direct callee | Complete linked native CODE | Original x86 instructions | Real physical typed COFF field |
| --- | --- | ---: | ---: | --- |
| `00458A80` | `00458DA0` | **19/19 B** | 9 | 1 `REL32` at +11 |
| `00458B50` | `00458FC0` | **19/19 B** | 9 | 1 `REL32` at +11 |
| `00458C20` | `00459140` | **19/19 B** | 9 | 1 `REL32` at +11 |
| `005F8020` | `005F85E0` | **19/19 B** | 9 | 1 `REL32` at +11 |
| **Four NEW independently registered whole functions** | | **76/76 B** | **36** | **4 true original typed fields** |

Tracked plain source
[`GameNativeForwarderLeavesF665.cpp`](../probes/GameNativeForwarderLeavesF665.cpp)
declares each separate `__thiscall` receiver-forwarding method as a
normal call to a distinct member. All four complete original source
functions compile from **one small translation unit** using pinned
VC7.1 `/Od /Ob0 /Gy /GR- /GX- /GS /Zi` into the *entire* original
19-byte x86 shape (including prologue, `this` saved at EBP−4,
receiver reload, direct `CALL`, and complete native epilogue).

[`verify-game-native-forwarder-leaves-f665.py`](../scripts/verify-game-native-forwarder-leaves-f665.py)
uses the original pinned PE and genuine compiler COFF symbol records;
for every source function, it independently proves the full x86
instruction order, exact native physical original `CALL` target, one
and only one genuine **zero-addend `REL32` field at source offset 11**,
expected source symbol, actual original linked 32-bit displacement,
and all **19 original machine bytes** after linking only that
verified source field in a transient *comparison buffer*. No original
exe patch, code graft, synthetic stack local, relocation mask or
instruction-level partial match is counted. The four original
registered addresses were independently cross-checked with prior
F595–F658 source-backed whole origin-unknown functions to avoid
counting previously reconstructed functions twice. In particular,
nearby F638/F648 constructor and zero-argument wrappers that were
already byte-backed are NOT included in this new cohort.

## Direct native caller context (not proof of authorship)

The selected verifier scans original direct x86 `CALL` instructions
from all **4,351 registered original whole native CODE extents**,
excluding separately owned after-RET table data. The four original
callee CALL counts are **5, 4, 2, 3**, respectively; currently
classified game-authored caller instructions account for **0, 2, 2, 1**.
Even a real authored caller cannot prove whether the callee itself
came from source code written by the game author or compiler-generated
container/lifetime or vendor implementation. All four remain
`unknown,review`, without changing the author-origin inventory of
**95 unresolved candidates**.

The prior research cohort contained **66 distinct complete source-backed
origin-UNKNOWN native functions /1,183 native whole CODE bytes**.
F665 increases that separate, fully uncredited evidence to
**70 complete original functions /1,259 CODE bytes**. None gets
original authored whole-function credit. Formal authored exact
remains **943 whole game functions /862,726 original CODE bytes
(43.71% reviewed)**. The separate F664 giant fighter interior source
research likewise does not gain whole-function credit from this.

```bash
scripts/repo-python scripts/verify-game-native-forwarder-leaves-f665.py
scripts/repo-python scripts/validate-tracking.py --require-target
```

Complete freshly compiled VC7.1 OBJ/PDB, compiler output, genuine
linked PE whole-byte proof and real direct original caller graph are
preserved in ignored `.analysis/f665-native-forwarder-leaves/`.
No full cold replay of 943 units, original EXE modification or
external Oracle acceptance was performed.
