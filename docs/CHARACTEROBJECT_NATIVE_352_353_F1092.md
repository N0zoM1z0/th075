# F1091/F1092 — Genuine original 0x352 288B fade, 0x353 155B terminal animation

**Historical F1092 checkpoint:** current parent now also restores [F1093 0x354](CHARACTEROBJECT_NATIVE_354_F1093.md). The earlier 50-state/34,615B source metrics below are historical; original 352/353 PE fields still verify.

The SHA-pinned Japanese TH075 1.11 original has ONE authored
`CharacterObject::Advance` callable at `0050A580` with **81,539
original CODE B /17,435 native x86** and independent original 567B
afterRET jump/sparse DATA. F1091 and F1092 restore two genuine
original *game-state interiors*, NOT separate complete original
callables, in the same normal MSVC7.1 partial parent.

Original `0x352` is `0051497A..00514A9A`, **288 original CODE B /
64 native x86**. It resets native `0040FBB0` motion at stage/frame
zero, initializes both scale floats to **0.5f** (original DWORD
`0x3F000000`), four opacity bytes to `0xFF` and signed +0xD8 to zero.
Each frame it adds the real original global **0065747C** to both
scales. At native animation stages above 1, it reduces actual unsigned
alpha by **20** or expires through authentic `0045B830` when alpha
cannot be reduced. Actual `0040FA30` animation completion also
triggers original expiry.

Original `0x353` is `00514A9A..00514B35`, **155 original CODE B /
35 native x86**. It resets motion at stage/frame zero, both float
scales to **1.0f** and all four opacity bytes to `0xFF`, then invokes
native `0040FA30` to check its original current action and conditionally
calls `0045B830`. Both are actual distinct switch entries from the
original dense/sparse table, not invented helper functions.

| Original native case evidence | `0x352` | `0x353` |
| --- | ---: | ---: |
| Original native CODE B /x86 | **288 /64** | **155 /35** |
| Normal compiled current C++ case CODE B /x86 | **222 /64** | **119 /35** |
| Matching ordered original mnemonic/GPR roles | **64/64** | **35/35** |
| Native instruction widths matching | 42/64 | 23/35 |
| Real original physical PE call/global relocations | **6/6** | **3/3** |
| Real float initializers | 0.5f/0.5f | 1.0f/1.0f |

The source was compiled **inside the entire currently changed
original-shaped one-switch parent** under pinned ordinary VC7.1
`/Od /Ob0 /Gy /GR- /GX- /GS /Zi`. All original PE physical REL32/
DIR32 destinations and instruction ordinals, authentic 92 afterRET
DIR32 label-equivalence partitions and 199 literal sparse bytes were
verified without masking. Earlier accepted, originally recovered
`0x351` and older game states were rechecked for regression.

The one-parent live source verifier now covers **50 genuine original
state interiors**, **42,205 original native CODE B /9,183 x86**, with
**9,183/9,183 original ordered mnemonic and GPR-role positions**,
**716/716 physical original nonlocal PE targets**, and **1,707/1,707
nonrelocated native scalar-immediate positions**. Current selected
partial C++ emits **34,615 CODE B /9,311 x86** plus 567 afterRET
DATA; the original entire game is still **81,539 B /17,435 x86**
and has original ESP frame `0x3A0` and receiver EBP-`0xAC` versus
the incomplete parent's `ESP 0x1DC` and EBP-`0x74`.
Many other original cases, stack and branch widths remain unresolved.
**Original complete game callable remains NONEXACT; newly accepted
whole original CODE = 0 B.**

Reproduce only the affected one-switch partial parent:

    scripts/repo-python scripts/verify-characterobject-current-recovered-f1068.py

Complete normal C++/OBJ/PDB/compiler evidence and independently original
PE receipts retained under ignored `.analysis/f1092-native352353/`
and `.analysis/f1068-boss-live-all-native/`. No original PE mutation,
invented callable split or full 979-function cold replay.
