# F625 — genuine resource-release lifetimes in two incomplete whole destructors

Original Japanese TH075 1.11 SHA256 `bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
This is **negative whole-function evidence**, not a newly accepted authored match. Both destructors are original-classified **authored** and remain NONEXACT. Unlike isolated code snippets, the compiler tests build each **entire native-function source** under the matching ordinary VC7.1 `/Od /Ob0 /Gy /GR- /GS /Zi` profile (`/GX-` archive, `/GX` scene).

| Entire authored original function | Original CODE / x86 | Genuine direct resource-free source result | Original typed source COFF fields | Native delete-local EBP positions restored |
| --- | ---: | ---: | ---: | --- |
| `0041CE50` ArchiveCatalog nonvirtual destructor | 171 bytes / 51 x86 | **165 bytes / 49 x86**, missing two original pointer save/reload instructions | 14 | `−0xC` pointer, `−0x8` delete receiver |
| `0043B0B0` SceneObject virtual EH destructor | 248 bytes / 75 x86 | **230 bytes / 69 x86**, missing six original pointer save/reload instructions, two for each of three CRT frees | 12 | `−0x14` texture pointer, `−0x10` delete receiver |

The normal C++ source in [`ArchiveCatalogDirectFreeF625.cpp`](../probes/ArchiveCatalogDirectFreeF625.cpp) frees the borrowed real filename via the original archive list access *without introducing a named filename local*. This makes the compiler naturally allocate the resource and destructor-receiver slots at the two true original EBP positions. However, `free(*list.At(index))` directly consumes the load result instead of emitting the native `MOV [EBP−0x10],EAX; MOV ECX,[EBP−0x10]` pair: **165/49 is not the native 171/51 whole function**. Reintroducing a meaningful named filename local returns to original length, but shifts the three local slots to the wrong compiler ownership order (`−0x10/−0xC/−0x8`).

Likewise, [`BattleSceneDirectFreeF625.cpp`](../probes/BattleSceneDirectFreeF625.cpp) retains the real pointer nonzero guards and the original three resource `free` calls, but removes all three named temporary pointer stores and reloads. The texture manager's compiler locals **then naturally land at the two correct original native EBP positions**. This is significant evidence that the original source's five temporary allocations depend on the *actual resource release lifetime and declaration graph*, not on arbitrary unused stack padding or misdeclared ABI. But the compiler drops **six** original x86 instructions and 18 bytes, yielding an invalid entire native length. Neither abbreviated candidate gets partial match credit.

The targeted [`verify-destructor-direct-free-f625.py`](../scripts/verify-destructor-direct-free-f625.py) freshly compiles either affected whole TU or both, rereads both actual complete PE functions and x86 boundaries, asserts the original native EBP delete slots, checks all 14/12 source COFF fields and uses the canonical complete original PE comparator to **require `size-mismatch`**. The source and result must remain explicitly nonexact until a true resource/object-lifetime model produces **every** native save/reload and all five original scene EBP slots in one natural source body. No fabricated local, ASM, byte graft, patched target or all-unit cold replay.

Historical F584/F609 archive and F589/F612 scene variants demonstrated that 171-byte and 248-byte source candidates can achieve 108/115 and 191/200 non-relocation byte agreement while allocating the wrong locals. An additional F623 real reference/temporary lifetime matrix (20 complete archive compiler trials) reproduced either 171/51 with 108/115 or 102/115, or 179/54, none exact. Additional F625 scene lifetime tests (19 complete compiler trials) produced 248/75 with 191/200 or 189/200, or shorter/longer native outputs; none exact. Those experimental sources/results remain in ignored `.analysis/f623-archive-rvalue-temporaries/` and `.analysis/f625-scene-lifetime-scopes/`. All relevant source and original comparison JSON receipts for the two selected direct-free cases remain in ignored `.analysis/f625-destructor-direct-free/`.

Reproduce **only the selected affected destructor** (never all 943 accepted units):

```bash
scripts/repo-python scripts/verify-destructor-direct-free-f625.py --which archive
scripts/repo-python scripts/verify-destructor-direct-free-f625.py --which scene
scripts/repo-python scripts/verify-destructor-direct-free-f625.py
scripts/repo-python scripts/validate-tracking.py --require-target
```

**Official authored whole-function coverage is still 943 exact functions / 862,726 original CODE bytes (43.71% reviewed); these 419 original bytes remain NONEXACT.** No new authored match unit, no origin changes, no outside Oracle acceptance.
