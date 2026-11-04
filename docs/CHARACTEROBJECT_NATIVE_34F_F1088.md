# F1088 — Original 0x34F 1,216B action, real 0x363 shots and distinct parent-stage guards

The SHA-pinned Japanese TH075 v1.11 original contains ONE independently
authored `CharacterObject::Advance` at `0050A580`: **81,539 CODE B /
17,435 native x86**, plus its separately owned 567B afterRET sparse
switch DATA. It remains a **NONEXACT whole original game callable**.

Original action **`0x34F`** occupies `00513B88..00514048` and
contains **1,216 native CODE B / 263 ordered x86**. Its actual
source is now a distinct real C++ case in the same parent, not a
standalone callable or synthetic register-allocation marker.
The genuine original controls reset motion/status/scale/opacity on
stage/frame zero, preserve timer 140 if already set, use the signed
parent+0xF0C and actor+0xC8 trajectory with real `0065989C`, advance
X/Y using native `00657F74` and `0065835C`, and gate the state
against the grandparent+0x324, parent+0x324 and parent+0x3A0 original
health/resource windows. It handles authentic action `0x2C1`/parent
stage 2, fades alpha, updates the parent+0x36C float and transitions
through original `0040FB40`, `00453D40`, `0040FA30` and `0045B830`.

The similar preceding original **`0x34E`** is NOT the same state:

| Original distinct state | Parent action/phase combinations | Native 8-shot projectile |
| --- | --- | --- |
| `0x34E` | `0x195/4`, `0x1F4/14`, `0x1F5/14` | **`0x362`** |
| `0x34F` | **`0x194/4`, `0x263/5`, `0x264/5`** | **`0x363`** |

The two actual original 263-instruction states have identical
mnemonic patterns but differ at original parent literal sites
**127/137/147**, spawn-ID literal **179** and in physical GPR/local
stack-slot allocation. In state 0x34F, the genuine eight-shot loop
stores `float(shot*45)` to parent+0x314, then passes real projectile
ID **`0x363`** through parent `00453A70`. No call-site byte graft,
synthetic padding, forced x86 registers or false merged switch entry
was added. The correctly typed native float-first x87 expression and
real original native call identities are preserved.

A fresh normal pinned VC7.1 `/Od /Ob0 /Gy /GR- /GX- /GS /Zi`
compile of the **entire one-switch original-shaped partial parent**
was compared against the independent full original Japanese PE,
including all 92 original DIR32 jump-table equality partitions and
199 true sparse literal data bytes. For this new action:

| Native original 0x34F evidence | Verified current source |
| --- | ---: |
| Original native CODE /x86 | **1,216B /263** |
| Source emitted case CODE /x86 | **1,004B /263** |
| Original ordered mnemonic matches | **263/263** |
| Original GPR-role matches | **263/263** |
| Original width matches | 193/263 |
| Authentic original PE external field positions/targets | **18/18** |
| Parent action and projectile literal checks | **4/4** |

The live `verify-characterobject-current-recovered-f1068.py` now
audits **46 real original case interiors**, spanning **39,408
original CODE B /8,565 original x86**, **8,565/8,565 original
mnemonic/GPR-role positions**, **674/674 physical original PE
REL32/DIR32 fields** and **1,588 source-vs-original non-relocated
scalar-immediate positions**, including distinct real projectile
IDs. The entire *partial* current parent emits **32,425 CODE B /
8,701 x86**, of which 31,589B are emitted recovered state bodies,
with `ESP 0x1C4` and saved receiver EBP-0x70 versus the original
`ESP 0x3A0` /EBP-0xAC. Many original states remain markers and
machine widths/branch displacements remain nonexact. No original
whole game callable or original CODE byte is newly accepted exact.

Reproduce just the changed parent, never all 979 exact units:

    scripts/repo-python scripts/verify-characterobject-current-recovered-f1068.py

The normal C++/OBJ/PDB/compiler and actual native PE receipts are
retained under ignored `.analysis/f1068-boss-live-all-native/`.
No original executable mutation or cropped callable acceptance.
