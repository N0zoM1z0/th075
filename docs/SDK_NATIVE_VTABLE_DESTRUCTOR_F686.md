# F686 — entire original 19-byte virtual destructor with genuine vftable and CRT free

Pinned user-supplied Japanese TH075 v1.11 `resources/th075.exe`, SHA256
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
This is a genuinely **complete original source-UNKNOWN native whole
function**, not a new accepted game-authored match unit. Original
`function-origins.csv` remains `origin=unknown, disposition=review`;
historical class names and original SDK ownership are unproven.

| Original registered PE function | Complete native CODE | Whole native x86 | Real vtable `DIR32` | Real CDECL free `REL32` |
| --- | ---: | ---: | --- | --- |
| `0061535A`–`0061536D` | **19/19 B** | **5** | Compiler field at `+8`, real original vtable `0065DA54` | Compiler field at `+13`, genuine original callee `00640F15` |

The actual original machine code pushes one resource-pointer value
**directly** from `this+0x104C`, stores the original virtual table
at `this+0`, calls the original normal CRT CDECL `free`, pops the
caller's argument off the stack via `POP ECX`, and returns. There is
no extra null check, stack frame, class object padding, borrowed
pointer wrapper, or hidden exception prologue in this complete native
function. The original full bounds and every final instruction are
independently read from the pinned original PE.

The ordinary C++ source
[`SDKNativeVtableDestructorF686.cpp`](../probes/SDKNativeVtableDestructorF686.cpp)
is a real virtual destructor that frees precisely the actually
observed `this+0x104C` pointer. Normal pinned MSVC VC7.1
**`/O1 /Ob0 /Gy /GR- /GX- /GS /Zi`** emits the same **five x86
instructions and all 19 original machine CODE bytes** after linking
only its actual zero-addend source vftable `DIR32` and native CRT
`free` `REL32` fields to the independently observed PE destinations.
The linker comparison uses a temporary in-memory byte buffer; it
does **not** patch the original game executable.

The compiler profile is evidence rather than guesswork. Under `/O2`,
the same natural destructor introduces a separate `MOV EAX,[member]`
and `PUSH EAX` pair (**20 bytes/6 x86**), not original native. Under
`/Od`, its complete original function source instead emits a 38-byte
stack frame/14 x86 instructions. The virtual class spelling in the
probe is provisional only: no inferred historical class layout is
instantiated, and no fake padding or unused locals are used.

[`verify-sdk-native-vtable-destructor-f686.py`](../scripts/verify-sdk-native-vtable-destructor-f686.py)
cold-compiles **only this small original-like C++ TU**. It checks the
complete registered native 19-byte function, true ABI/instruction
boundaries, each genuine zero-addend typed compiler COFF field and
original vtable/CRT target, and **every one of the original 19
PE-linked machine bytes**. Independently scanning all 4,351
registered original complete native CODE functions finds **three
actual direct callers**. This does not prove source ownership or
exclude indirect uses.

F595–F680 research contained **81 distinct source-backed whole
native origin-UNKNOWN functions /1,559 original CODE bytes**. F686
adds this **one previously unverified complete 19-byte original**:
the uncredited whole-native cohort is now **82 distinct original
functions /1,578 original CODE bytes**. Original **95 provenance-
unknown** candidate ledger entries remain unchanged. Official
accepted whole game-authored exact remains **943 complete functions
/862,726 original CODE bytes (43.71% reviewed)**; no giant inner
case or SDK-like source can earn authored credit without provenance.

```bash
scripts/repo-python scripts/verify-sdk-native-vtable-destructor-f686.py
scripts/repo-python scripts/validate-tracking.py --require-target
```

New true whole original PE/COFF receipt, source hash, original direct
caller graph and cold compiler OBJ/PDB/log are preserved under
ignored `.analysis/f686-sdk-native-vtable-destructor/`; tested `/O1`,
`/O2` and `/Od` alternatives under ignored
`.analysis/f686-native-vtable-dtor/`. No all-943-unit cold replay,
original EXE modification or false exact authored credit occurred.
