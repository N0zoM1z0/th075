# F655 — seven complete native origin-unknown leaves, genuine whole bytes

Original pinned Japanese TH075 version 1.11 `resources/th075.exe`, SHA256
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
This study **completes original machine-byte source reproductions**, but
**does not identify their historical source owner**. All seven functions
remain `origin=unknown, disposition=review`: neither a native `CALL`
from game-authored code nor a plausible C++ name proves that an original
function was game-authored instead of compiler/library-generated.

## Complete original native extents, cold-built ordinary C++

The tracked normal C++ source
[`GameUnattributedLeavesF655.cpp`](../probes/GameUnattributedLeavesF655.cpp)
compiles with genuine VC7.1 build 3077 `/Od /Ob0 /Gy /GR- /GX- /GS /Zi`.
[`verify-game-unattributed-leaves-f655.py`](../scripts/verify-game-unattributed-leaves-f655.py)
compiles **only this single small TU**, independently decodes the real
original full function extents, verifies every instruction, and links
**only proven physical typed COFF relocation fields**. Nothing was
manually grafted from target bytes into source.

| Original entire function start | Native bytes exact | Original x86 instructions | Typed COFF fields | Ordinary C++ compiler grammar |
| --- | ---: | ---: | ---: | --- |
| `004138D0` | **11/11** | 7 | 0 | Empty receiver member function |
| `004169D0` | **11/11** | 7 | 0 | Separate empty receiver member function |
| `0041F7F0` | **11/11** | 6 | 0 | Free pointer argument plus 8 bytes |
| `00540280` | **11/11** | 6 | 0 | Separate free pointer argument plus 8 bytes |
| `00441FD0` | **5/5** | 4 | 0 | Empty CDECL function |
| `0045B630` | **5/5** | 4 | 0 | Separate empty CDECL function |
| `00409490` | **19/19** | 9 | 1 | `thiscall` member forwards receiver to one member |
| **Seven distinct complete original PE function extents** | **73/73** | **43** | **1** | All provenance unknown |

The native `00409490` linked **whole** original CODE includes a
real original PE `CALL 00409860`. Its compiler COFF has exactly one
`REL32` relocation at function offset 11 to the declared member
`Finish`. The verifier confirms original call instruction target,
true source COFF symbol/type, addend 0, and original physical linked
32-bit displacement before reconstructing the linked bytes; it
then asserts the **entire original 19-byte PE function** matches.
All six other complete original PE functions have **zero relocations**
and equal their new compiler's CODE byte-for-byte without any masking.
The `+8` source arithmetic in the two pointer leaves is compiler
syntax evidence, *not* proof of an original iterator/container type.

## Real native original caller context

Decoding complete instruction streams of the 4,351 registered native
function extents (only for **CALL graph analysis**, **not** compiling
all of them) gives the following direct original call occurrences:

| Original callee | All native direct calls | Calls from currently authored callers | Caller context |
| --- | ---: | ---: | --- |
| `004138D0` | 0 | 0 | No direct `CALL` in currently registered original extents |
| `004169D0` | 1 | 0 | One currently compiler-classified caller `00656ED0` |
| `0041F7F0` | 1 | 0 | One library-classified caller `0041F790` |
| `00540280` | 1 | 0 | One library-classified caller `00540260` |
| `00441FD0` | 0 | 0 | No registered direct `CALL` |
| `0045B630` | 1 | 0 | One library-classified caller `0045B290` |
| `00409490` | 3 | 1 | Callers `004071C0` and `00407270` still unresolved; `004073D0` currently authored |

Caller classification and native ownership remain separate:
indirect, virtual, or jump-based uses are not ruled out by this
**direct `CALL` scan**. None of these observations independently
establishes author-written source vs compiler or STL emission.
The seven original addresses were checked against the previously
source-backed origin-unknown F595/F616–F650 cohort to avoid double
credit. That cohort had **40 complete whole functions /929 native
CODE bytes**. F655 adds **seven distinct originals /73 bytes**, so
**47 complete original source-backed unknown-origin functions /
1,002 bytes** are now independently reproduced but remain uncredited.
The count of source-origin-unknown registered candidates remains **95**.

**Formal accepted authored exact total remains 943 complete functions /
862,726 original CODE bytes (43.71% reviewed)**. All 22 giant fighter
parents and three other authored whole functions remain nonexact.
No 943-unit mass cold replay or external Oracle exact acceptance.

```bash
scripts/repo-python scripts/verify-game-unattributed-leaves-f655.py
scripts/repo-python scripts/validate-tracking.py --require-target
```

Cold compiler object/PDB, original PE whole-byte proof, caller graph,
source SHA256 and compiler log are retained under ignored
`.analysis/f655-unattributed-leaf-source/`.
