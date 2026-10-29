# F655 — seven independent whole native leaf bodies, original source attribution UNKNOWN

Original supplied Japanese TH075 version 1.11 `th075.exe`, SHA256
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
This is **seven newly source-backed entire registered original native
function extents**, not seven newly attributed game-authored functions.
Their provisional Ghidra names and any presumed class ownership are
NOT historical source evidence. `function-origins.csv` stays
`unknown,disposition=review` for every one.

## Whole original PE versus freshly compiled normal VC7.1 C++

The only affected C++ translation unit is
[`GameUnattributedLeavesF655.cpp`](../probes/GameUnattributedLeavesF655.cpp),
cold-compiled with genuine pinned VC7.1
`/Od /Ob0 /Gy /GR- /GX- /GS /Zi`. The independent original full
function extents, genuine complete x86 and physical typed COFF field
count were decoded from the original PE. There are no partial source
fragments, fake stack locals, arbitrary padding or manually copied
machine code.

| Complete original PE function | Full identical original CODE | Native x86 | Original typed PE/COFF fields | Actual recovered source *shape* (historical identity uncertain) |
| --- | ---: | ---: | ---: | --- |
| `004138D0` | 11/11 B | 7 | 0 | Empty `__thiscall` receiver method, compiler still saves `this` at EBP−4 |
| `004169D0` | 11/11 B | 7 | 0 | Distinct original empty receiver method |
| `0041F7F0` | 11/11 B | 6 | 0 | CDECL function returning pointer argument plus 8 bytes |
| `00540280` | 11/11 B | 6 | 0 | Distinct original pointer-plus-8 function |
| `00441FD0` | 5/5 B | 4 | 0 | Empty CDECL function with a genuine complete prologue/RET |
| `0045B630` | 5/5 B | 4 | 0 | Distinct original empty CDECL function |
| `00409490` | 19/19 B | 9 | **1 REL32** | `__thiscall` wrapper that delegates to real original `00409860` |
| **Total seven independent whole original functions** | **73/73 B** | **43** | **1** | **Proven original machine CODE; uncertain authored-vs-compiler source** |

The original `00409490` native `CALL` at `0040949A` targets
`00409860`. In the cold-compiled source, the physical COFF
**REL32 field at offset 11** has genuine zero addend and the
compiler-generated `?Finish@DelegateMember_F655@@QAEXXZ` target
symbol; the independent complete original linked PE displacement is
`target - (field_address + 4)`. The verifier links **only this
physically justified one field**, checks the true native call target
and compares **all 19 original machine bytes**, not just a relocation-
masked structural comparison. All other six original complete CODE
functions compare directly without any relocation or normalization.

## Original direct CALL graph — evidence versus source origin

The verifier independently decodes every complete registered native
function in the original 4,351-function PE extent ledger, excluding
non-CODE after-RET switch DATA. The exact native original **direct**
call counts (indirect calls are *not* inferred) are:

| Native function | Real original direct CALL instructions | Currently authored direct-caller instructions |
| --- | ---: | ---: |
| `004138D0` | 0 | 0 |
| `004169D0` | 1 | 0 |
| `0041F7F0` | 1 | 0 |
| `00540280` | 1 | 0 |
| `00441FD0` | 0 | 0 |
| `0045B630` | 1 | 0 |
| `00409490` | 3 | 1 |

Even an authored original direct caller at `00409490` does **not**
prove its target was historically a game-written function rather
than a compiler-generated method or a standard-library/vendor
special member. Full byte reproducibility and source-origin attribution
are independent questions. No names, unknown origin dispositions,
accepted whole-function matches or authored numerator were modified.

Previous F595 + F616/F618/F634/F638/F640/F644/F648/F650
experiments had **40 distinct source-backed, origin-unknown full
functions /929 original whole CODE bytes**. These **seven new distinct
functions /73 bytes** raise that *uncredited* research cohort to
**47 original functions /1,002 original native CODE bytes**. All
**95 origin-unknown candidates** remain pending provenance review,
and the official authored exact total stays **943 independent whole
functions /862,726 original CODE bytes**. The F654 giant interior
progress is also separate, not whole-function authored acceptance.

## Selected cold reproduction

```bash
scripts/repo-python scripts/verify-game-unattributed-leaves-f655.py
scripts/repo-python scripts/validate-tracking.py --require-target
```

The new full VC7.1 object, PDB, compiler log, complete original PE
linked-byte proofs and actual native direct-caller graph are preserved
under ignored `.analysis/f655-unattributed-leaf-source/`. No other
accepted unit was changed or cold-replayed and no 943-unit all-code
replay was performed. This is not external Oracle acceptance.
