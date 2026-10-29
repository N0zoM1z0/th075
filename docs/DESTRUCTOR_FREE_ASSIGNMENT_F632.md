# F632 — complete original authored destructors: fifteen real free-argument assignment controls

**Pinned Japanese TH075 1.11** original PE SHA256 `bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`; actual MSVC VC7.1 `/Od /Ob0 /Gy /GR- /GS /Zi` native-source compiler. The two source functions below are **complete original authored whole functions** and remain **NONEXACT**, despite retaining their complete original length and original number of physical COFF fields. No partial comparison, fake local, inline assembly, target-byte graft or accepted match unit.

## What was experimentally re-evaluated

F625 showed a genuine original compiler stack allocation dependency: if the C++ source directly passes a borrowed resource pointer to CRT `free`, the native resource-delete temporaries occupy the right EBP stack slots, but the compiler **removes** one original pointer save/reload pair in the ArchiveCatalog destructor or three in the SceneObject destructor. Conversely, ordinary meaningful named pointer variables retain the original number of x86 instructions but allocate the original live local variables in a different order.

F632 tests a distinct source hypothesis: a meaningful named pointer is **assigned inside the actual argument expression** of `free`, rather than assigned in a prior independent C++ statement. Under VC7.1 `/Od` the C++ AST may influence the lifetime and stack allocator of the original filename/free values, so the original complete native CODE—not an expression cutout—must decide. Eight actual archive variants include assignment-in-argument, comma-in-argument, assignment-then-call comma sequencing, discarded-but-used assignment, cast, lvalue identity, named `void*`, and `const` owning pointer. Seven actual scene variants perform the same transformations on all three game resource free values, both in the original real three-field aggregate and three genuinely named pointer variables. Every variant frees the **same actual original pointer** and preserves the genuine game method/CRT calls; none adds unused variables or alters the original ABI.

[`verify-destructor-free-assignment-f632.py`](../scripts/verify-destructor-free-assignment-f632.py) compiles **only one chosen complete source TU** with `--case`, or only the 15 tested small original-source candidates when run without an option (never 943-unit cold replay), then uses the repository's canonical **whole-original native PE/COFF comparator**. The verifier independently checks each original 171/248-byte x86 function extent, 51/75 real instruction count, correct 14/12 physical source COFF field count and the entire original 115/200 nonrelocation byte comparison. It explicitly rejects exact adoption unless fresh native source proof changes.

| Original complete authored function | New actual VC7.1 source alternatives | All complete generated CODE/x86 | Real COFF refs | Original nonrelocation bytes equal | Entire source exact? |
| --- | ---: | --- | ---: | --- | --- |
| `0041CE50`, archive nonvirtual destructor | **8** | **171 B /51 x86** | **14** | **108/115** in every case | **No** |
| `0043B0B0`, scene virtual EH destructor | **4** real aggregate assignment-expression variants | **248 B /75 x86** | **12** | **191/200** in every case | **No** |
| `0043B0B0`, scene virtual EH destructor | **3** real individually named-pointer variants | **248 B /75 x86** | **12** | **189/200** in every case | **No** |
| **F632 fifteen whole-original source controls** | **15** | Original-sized source functions, all nonexact | Real native code source fields preserved | No corrected physical local ownership | **Zero acceptance** |

The original physical archive delete EBP slots require resource `−0xC`, delete receiver `−0x8`, released filename `−0x10`; all eight F632 archive source forms still put them at `−0x10/−0xC/−0x8`. The original scene texture/delete locals require `−0x14/−0x10`, followed by first/second/third free values `−0x18/−0x1C/−0x20`. All seven F632 scene source variants still put the first two at `−0x20/−0x1C`. Moving a genuine assignment across the `free(...)` argument boundary changes neither original frame allocation class nor x86 geometry. Merely obtaining **51/51** or **75/75** complete x86 instruction counts is therefore not enough to claim byte exactness.

This is bounded **negative evidence** that F625's missing original-pointer local allocation order cannot be solved by surface-level C++ `free` argument/assignment/comma syntax alone. Future source work must recover the actual class lifetime, implicit temporaries and deleted-object ownership and be checked against the entire original PE, not manufacture byte matches by padding EBP slots. All fifteen compiler source/object/PDB logs, the full original PE comparison receipts and slot details are retained under ignored `.analysis/f632-real-free-assignment/` and `.analysis/f632-real-free-assignment/verified/`; the same entire source variants are recreated by the tracked verifier.

## Bounded repro and official accounting

```bash
scripts/repo-python scripts/verify-destructor-free-assignment-f632.py --case archive-ptr-in-free-arg
scripts/repo-python scripts/verify-destructor-free-assignment-f632.py --case scene-three-assignment-args
scripts/repo-python scripts/verify-destructor-free-assignment-f632.py --case scene-three-local-free-assignment
# Optional all fifteen affected small destructor TUs ONLY:
scripts/repo-python scripts/verify-destructor-free-assignment-f632.py
scripts/repo-python scripts/validate-tracking.py --require-target
```

**F632 adds zero new exact whole authored functions or accepted CODE bytes.** The exact authored ledger remains **943 complete functions /862,726 original CODE bytes (43.71% reviewed)**, while these two authored destructors and the separate full `00602A60` WinMain startup remain incomplete. Concurrent F629/F631 original fighter *interior* source roles do not change complete-function acceptance. No complete all-unit cold replay, binary patch or external Oracle receipt.
