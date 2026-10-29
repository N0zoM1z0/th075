# F648 — eight complete original native 16-bit state, pointer and member-call leaves

Pinned Japanese TH075 1.11 original PE SHA256 `bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`. Genuine normal MSVC VC7.1 `/Od /Ob0 /Gy /GR- /GX- /GS /Zi`. These are **eight independently registered complete original native functions**, not interior fighter cases. Their entire **161 real original machine CODE bytes, all 73 original x86 roles and six physically typed original PE/COFF targets** are reproduced by a single selected ordinary C++ translation unit. Original authored-vs-library-vs-compiler source ownership remains **`unknown`/`review`**; no exact authored match or byte credit is promoted merely from code identity.

## True native semantics and original linked whole CODE

Natural [provisional C++](../probes/GameStateSetterAndMemberForwardF648.cpp) reproduces the actual original entire function geometry and ABI:

| Complete original PE function | Entire linked original CODE | Original native x86 | Actual typed call target |
| --- | ---: | ---: | --- |
| `00410FC0` | **24/24 bytes** | 10/10 | No COFF: real 16-bit setter `this+0x12` from one 16-bit thiscall argument, true `RET 4` |
| `0045B6F0` | **27/27 bytes** | 13/13 | No COFF: real `this+0` pointer advanced **16 bytes**, returns the receiver |
| `00458770` | **22/22 bytes** | 10/10 | `REL32 +0xE` native member `this+4` method `00411C70` |
| `004229D0` | **28/28 bytes** | 12/12 | `REL32 +0xF` native thiscall constructor forwarding its argument to `00422A50`, returns receiver with `RET 4` |
| `0040F9F0` | **15/15 bytes** | 7/7 | `REL32 +0x9` `0040FA00` with zero integer argument |
| `004229C0` | **15/15 bytes** | 7/7 | `REL32 +0x9` `00422A20` with zero argument |
| `0045B6B0` | **15/15 bytes** | 7/7 | `REL32 +0x9` `0045B6C0` with zero argument |
| `005FAAD0` | **15/15 bytes** | 7/7 | `REL32 +0x9` `005FAAE0` with zero argument |
| **Eight independent whole functions** | **161/161 bytes** | **73/73** | **Six** genuinely original typed `REL32` source fields |

`00410FC0` uses an actual original `MOV CX, word ptr [EBP+8]` then 16-bit store at `this+0x12`; no invented class layout is inferred. `0045B6F0` uses actual original `MOV`, `ADD ... 0x10`, writeback and thiscall receiver return, not a fabricated stack slot. The 22/28-byte examples are genuine nontrivial member forwarding/constructor behavior. The four 15-byte wrappers are ordinary natural `__cdecl` entrypoints taking one receiver pointer; each uses the real native `PUSH 0; MOV ECX,[EBP+8]; CALL target; POP EBP; RET`. All native physical fields and their actual original PE relative call operands, C++ symbol type and zero addend are checked, rather than merely masked.

## Rebuild only the affected source, never all accepted units

[`verify-game-state-forward-leaves-f648.py`](../scripts/verify-game-state-forward-leaves-f648.py) cold-compiles **only the single selected eight-function C++ source TU**. It demands full original 15/22/24/27/28-byte native x86 starts, opcodes and normal source extents, checks **six real typed zero-addend `REL32` COFF call fields** at original native offsets and their true PE call targets, links only those six genuine original fields in temporary comparison buffers, then requires **every one of 161 original machine bytes identical**. It independently decodes direct original `CALL`s across **all 4,351 original registered function CODE extents** to check real uses without attributing separately owned after-RET switch DATA to code callers.

Actual direct caller counts: `00410FC0` has **zero registered direct `CALL` sites** (indirect use not excluded); each other function has **one** registered direct caller. The `0045B6F0` pointer iterator is called from an original STL `_Uninit_copy`-like owner; the `00458770` member forwards from an original compiler-labeled deleting destructor; the `004229D0` constructor and four zero-argument wrappers are called from currently library-labeled construct/destroy glue. These *provisional* origin labels are not independent proof of historical compiler/library authorship; all eight original `function-origins.csv` entries remain `unknown/review`. No ABI guess, complete class layout, authored attribution or accepted match manifest is inferred.

F644's source-backed but historically unclassified original complete small functions reached **29 whole functions /658 native original CODE bytes**; F648 adds **8 distinct whole functions /161 bytes**, yielding **37 source-backed yet origin-unclassified whole functions /819 original native CODE bytes**, all **uncredited**. This is separate from the F645 study of **566 strictly source-backed original inner fighter case bodies /153,255 original native CODE bytes**, which are also uncredited because the 22 giant original fighter owners are nonexact. Official accepted authored ledger remains **943 whole native functions /862,726 original CODE bytes (43.71% reviewed)**. No full all-unit cold replay, original EXE patch, manual assembly, fake locals, external Oracle acceptance or ungrounded origin promotion.

```bash
scripts/repo-python scripts/verify-game-state-forward-leaves-f648.py
scripts/repo-python scripts/validate-tracking.py --require-target
```

Fresh original VC7.1 object/PDB/COFF, full linked 161-byte receipts, compiler log and independent actual original caller graph are retained under ignored `.analysis/f648-game-state-forward-verified/`; initial independent source grammar experiments are under `.analysis/f648-small-state/`.
