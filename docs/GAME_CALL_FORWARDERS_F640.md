# F640 — twelve entire native game-facing thin-call and receiver leaf functions

**Original pinned Japanese TH075 1.11** `resources/th075.exe` SHA256 `bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`; ordinary true MSVC VC7.1 `/Od /Ob0 /Gy /GR- /GX- /GS /Zi`. These are **twelve independently registered complete native PE CODE functions**, not inner cases of the unfinished huge fighters. Their exact actual original 203 machine CODE bytes and 99 x86 instruction roles are reproduced under normal VC7.1 C++. However all twelve original functions remain historical **`unknown`/`review`**: machine-code identity and game use cannot distinguish compiler-generated wrappers, special members, library adapters or explicitly authored C++ and do not confer new authored acceptance.

## Actual original whole function source grammar and typed PE fields

Tracked ordinary source [`GameCallForwardersF640.cpp`](../probes/GameCallForwardersF640.cpp) provides independent natural `__cdecl` single-argument function forwards, two empty ordinary `__thiscall` receiver methods, three genuine nonvirtual `this` receiver member calls, and one ordinary object whose nontrivial first member has its own constructor. The C++ type spellings and proposed float argument/return signatures are **provisional compiler grammar hypotheses**, not a determination of historical float-vs-integer types or source object ownership. Under the genuine pinned compiler and normal ABI, each exact original-sized function naturally emits the original full prologue, call argument placement, caller cleanup, callee forwarding and epilogue, or its real `this` member access.

| Registered complete original native function | Complete original CODE identity | Original x86 | Physically typed original PE/COFF fields | Actual original native call target |
| --- | ---: | ---: | ---: | --- |
| `0040D900` | **17/17 B** | 8 | 1 `REL32` at `+0x8` | `0040D920` |
| `0040D940` | **17/17 B** | 8 | 1 `REL32` at `+0x8` | `0040D960` |
| `00412D90` | **17/17 B** | 8 | 1 `REL32` at `+0x8` | `00412DB0` |
| `00428D20` | **17/17 B** | 8 | 1 `REL32` at `+0x8` | `00428D40` |
| `00449A60` | **17/17 B** | 8 | 1 `REL32` at `+0x8` | `00449A80` |
| `00438A60` | **17/17 B** | 8 | 1 `REL32` at `+0x8` | `00641FB8` |
| `004073A0` | **11/11 B** | 7 | 0 | Real empty receiver method, no call |
| `00438CF0` | **11/11 B** | 7 | 0 | Real empty receiver method, no call |
| `0040DE30` | **19/19 B** | 9 | 1 `REL32` at `+0xB` | `0040E150` |
| `0040DF40` | **19/19 B** | 9 | 1 `REL32` at `+0xB` | `0040E2F0` |
| `0040D8E0` | **19/19 B** | 9 | 1 `REL32` at `+0xB` | `0041A380` |
| `0040D8C0` | **22/22 B** | 10 | 1 `REL32` at `+0xB` | `0041A2D0` first-member constructor |
| **Twelve distinct whole original native functions** | **203/203 B** | **99/99** | **10** | All independently original PE-targeted |

The six 17-byte wrappers all have genuine native `PUSH EBP; MOV EBP,ESP; MOV EAX,[EBP+8]; PUSH EAX; CALL target; ADD ESP,4; POP EBP; RET` roles. The no-op methods are actual 11-byte `thiscall` prologue/spill and frame epilogue; they are not conflated with earlier 13-byte `RET 4` special cases. The three 19-byte methods genuinely save/load the receiver before an ordinary member CALL. The native 22-byte owner constructor calls its **actual first-member** constructor and returns its receiver. All are full original PE registered CODE intervals, not truncated assembly fragments or invented function splits.

## Physically linked native byte identity and independently observed game callers

[`verify-game-call-forwarders-f640.py`](../scripts/verify-game-call-forwarders-f640.py) cold-compiles **only this single twelve-function C++ TU**. It compares all complete original native x86 instruction starts, lengths and mnemonics; verifies **all ten actual physical zero-addend typed `REL32` source COFF records** against their independently decoded original PE `CALL` instruction and true destination at the actual whole-function `+0x8/+0xB` field; and patches only each original native PE call field into a temporary *comparison buffer*, not game source or the original EXE, requiring **all 203 linked original machine bytes equal**. For the two 11-byte no-call originals, no relocation is used or masked. No arbitrary native byte graft, nonstandard compiler setting, fake locals, compiler ASM or partial-prefix comparison occurs.

Separately the verifier scans actual original **direct `CALL` x86 instructions** in all **4,351 registered original whole native CODE extents**, not guessed Ghidra XREF or separately owned after-RET jump DATA. Original PE direct call counts are:

| Native small function | All original direct CALL instructions | From currently authored original game CODE |
| --- | ---: | ---: |
| `0040D900`, `0040D940` | 7, 14 | 5, 12 |
| `00412D90`, `00428D20` | 68, 6 | 68, 6 |
| `00449A60`, `00438A60` | 6, 14 | 6, 14 |
| `004073A0`, `00438CF0` | 1, 1 | 1, 1 |
| `0040DE30`, `0040DF40`, `0040D8E0`, `0040D8C0` | 3, 5, 7, 3 | 2, 4, 1, 1 |

These actual callers include sprite drawing, camera updates, collision transformation, scene animation, fighter initialization and texture manager operations. They establish game use, **not** whether the wrapper was explicitly authored rather than compiler-generated or what the original class names/signatures were. The twelve original `config/function-origins.csv` classifications remain `unknown` with disposition `review`; nothing in the exact acceptance manifests was changed.

**F640 adds 12 complete independently source-backed original functions /203 original native CODE bytes /99 full native x86 roles /10 actual typed PE/COFF calls, but ZERO new accepted authored whole-function CODE bytes.** Together with F616/F618/F634/F638's eleven origin-ambiguous whole sources/287 native CODE bytes, the distinct source-backed but origin-unclassified whole function research totals **23 original whole functions /490 native CODE bytes**, still **all uncredited**. This whole-function evidence is distinct from F639's 33 original giant **inner case bodies**; none of their containing giants is yet entirely exact. Official authored exact ledger remains **943 whole native functions /862,726 original CODE bytes (43.71% reviewed)**, with 25 authored whole functions still nonexact. No all-unit cold replay, original EXE modification or outside Oracle acceptance.

```bash
scripts/repo-python scripts/verify-game-call-forwarders-f640.py
scripts/repo-python scripts/validate-tracking.py --require-target
```

Fresh true VC7.1 source/COFF/PDB, direct original PE caller graph and complete 12-function linked native byte receipts are retained under ignored `.analysis/f640-game-call-forwarders-verified/`; first independent physical byte/compiler grammar trials remain in `.analysis/f640-game-leaf-trials/`.
