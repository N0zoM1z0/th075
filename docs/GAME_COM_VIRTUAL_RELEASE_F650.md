# F650 — two complete original stdcall virtual-dispatch and conditional-free functions

Pinned original Japanese TH075 1.11 `resources/th075.exe`, SHA256 `bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`. Ordinary pinned MSVC VC7.1 `/Od /Ob0 /Gy /GR- /GX- /GS /Zi`. These are **two independently registered complete original native functions**, not partial original giant-fighter switch cases. The full linked **70 original machine CODE bytes /31 original x86 instructions /one real physically typed REL32 CRT free call** are reproduced by one natural C++ source TU. Original author-vs-generated/library provenance remains `unknown/review`; **zero new accepted authored whole-function exact CODE** is claimed.

## Actual original normal C++ source behavior and direct native PE targets

| Complete pinned original native function | Entire linked original CODE | Original complete x86 roles | True physical COFF field | Observed native behavior |
| --- | ---: | ---: | --- | --- |
| `004170B0` | **27/27 B** | 14/14 | **0** | Actual indirect call via virtual-table slot **+8** on an owned pointer at `this+0` |
| `004588B0` | **43/43 B** | 17/17 | **one `REL32 +0x20`** to genuine original native CRT `00640F15` / `_free` | Original `if (this+8 != null)` conditional free, with a real `void*` local saved at native `EBP−4` and native receiver at `EBP−8` |
| **Two newly reproduced complete original functions** | **70/70 B** | **31/31** | **1 real typed target** | Full original function bodies, not excerpts |

The third-virtual-method original PE uses `MOV EAX,[EBP−4]`, `MOV ECX,[EAX]`, `MOV EDX,[EBP−4]`, `MOV EAX,[EDX]`, `MOV ECX,[ECX]`, **`PUSH EAX; CALL dword ptr [ECX+8]`**, and original full frame epilogue. A natural `receiver->table->third(receiver)` stdcall function-pointer hypothesis has the right function size and x86 count, but the compiler **pushes the argument before loading the vtable**, producing **eight incorrect original bytes**. A separate normal C++ hypothesis `receiver->Third()` on a genuine abstract `virtual void __stdcall Third()` at vtable slot +8 instead naturally reproduces **all 27 original native bytes and the correct evaluation order**. The `__stdcall` virtual-call grammar is original byte-backed; the actual historical interface/class name and whether it is a COM type remain unknown. Source: [`GameComVirtualAndConditionalReleaseF650.cpp`](../probes/GameComVirtualAndConditionalReleaseF650.cpp).

The second function is a real 43-byte native resource-lifetime method: compare the pointer at `this+8` against zero, branch around `free` when absent, load the pointer again into a meaningful local **`EBP−4`**, pass it to the actual original `00640F15` CRT `free`, clean the call stack, then return. The initial natural C++ version introduced an additional `char* raw` pointer local and generated **49 bytes** with three EBP slots, rather than original 43 bytes and two locals. Removing that *extra actual source variable* and reading `this+8` directly (while retaining the genuine pointer-to-free local) restores the pinned compiler's original **`EBP−8` receiver / `EBP−4` resource local** and **all 43 original bytes**. No fake locals, assembly, arbitrary padding, source-layout ABI tricks or original EXE modifications were used.

## Original whole PE/COFF verification and independently observed callers

[`verify-game-virtual-release-f650.py`](../scripts/verify-game-virtual-release-f650.py) cold-builds **only the two-function C++ TU** under ordinary pinned VC7.1, retrieves both genuine complete original PE function extents and full x86 instruction roles/bytes, checks the original native conditional `free` and callback calling convention and physical zero-addend source `REL32` at **offset32** to true original `00640F15`, then resolves **only the real original PE field in a temporary comparison buffer**. Both entire original function byte sequences must match. The callback function has no external relocation to mask.

It also independently decodes all original direct `CALL` instructions across **all 4,351 registered native original function CODE extents**:

- `004170B0`: **one** direct caller, currently classified as compiler-generated scalar-deleting destructor `0041A140`; the call does not establish the historical origin of the 27-byte callback method.
- `004588B0`: **six** original direct CALL instructions, including original authored `Effects::LoadPatternCatalogAt005F71F0`, compiler-like deleting destructor, STL vector assignment/insert paths and a provisional intermediate. These prove genuine game use, **not** explicitly authored historical ownership.

Earlier F595 already reconstructed original `004135F0` as a **40/40-byte** source-backed but origin-unknown three-field setter. The F650 experimental source independently confirmed this existing result but **does not count that prior source as newly reconstructed**. F616/F618/F634/F638/F640/F644/F648 previously recorded **37 distinct origin-unknown fully source-backed whole native functions/819 original CODE bytes**. This F650 adds **two /70 bytes**; the combined recent cohort is now **39 original whole functions /889 source-backed native CODE bytes**, excluding the independently prior-known F595 40-byte function. Including the distinct F595 origin-unknown whole source, the broader total is **40 /929 original native CODE bytes**. **All remain uncredited pending source provenance**.

The F598–F647 *large function interior* study separately recorded **570 strictly source-backed original internal game cases /154,011 original native inner CODE bytes**. F650 does not change that strictly matched case count. Official accepted authored whole-function exact ledger remains **943 functions /862,726 original CODE bytes (43.71% reviewed)**; there is no 943-unit cold replay or external Oracle adoption.

```bash
scripts/repo-python scripts/verify-game-virtual-release-f650.py
scripts/repo-python scripts/validate-tracking.py --require-target
```

True native PE-linked receipts, fresh normal VC7.1 COFF/PDB and compiler logs, and original native direct-caller graph are retained under ignored `.analysis/f650-game-virtual-release/`; independent initial compiler source-grammar trials under `.analysis/f650-native-leaves/`.
