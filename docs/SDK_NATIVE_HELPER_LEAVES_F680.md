# F680 — five distinct original complete optimized SDK helper bodies, source owner UNKNOWN

Pinned user-supplied Japanese TH075 v1.11 `resources/th075.exe`, SHA256
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
These are five independently registered **complete original PE CODE
function extents**, not excerpts from a large function. Their original
`function-origins.csv` statuses stay `unknown,review`; entire linked
machine-byte identity does **not** determine SDK/compiler/game author.

| Original registered whole function | Genuine original entire CODE B | Entire x86 | Original PE field/target | Natural ABI/semantic role |
| --- | ---: | ---: | --- | --- |
| `0060EA69` | **14/14** | 6 | `DIR32` IAT `0065704C` | Nullable pointer → imported `__stdcall` free |
| `0061FB37` | **14/14** | 7 | `REL32` call `00640F15` | Nullable pointer → `__cdecl` free; actual `POP ECX` cleanup |
| `00614BC6` | **6/6** | 3 | No relocation | `MOV EAX,ECX; AND DWORD [EAX],0; RET`; returned `this` |
| `0060C120` | **11/11** | 4 | `REL32` tail JMP `0060C0DF` | If tag != `−1`, thiscall tail-forward; else return |
| `00620132` | **5/5** | 1 | `REL32` tail JMP `0061FE0A` | Entire native direct thiscall forwarder |
| **Five entirely new complete originals** | **50/50** | **21** | **4 true physical PE/COFF fields** | None accepted game-authored |

The ordinary C++ source
[`SDKNativeHelperLeavesF680.cpp`](../probes/SDKNativeHelperLeavesF680.cpp)
models these **five distinct** native ABI shapes, with only the
observed pointer, flag and tag members. The selected compiler grammar
is pinned VC7.1 `/O1 /Ob0 /Gy /GR- /GX- /GS /Zi`. The original
`0060EA69` uses a real imported standard-call thunk through IAT
`0065704C`, not a direct call with fake caller cleanup. The actual
`0061FB37` calls the original direct native `00640F15`, then really
executes `POP ECX` to remove the CDECL argument. Native `0060C120`
retains an actual **conditional return after an unconditional tail
JMP**, rather than being incorrectly truncated before that return.
The real `00620132` is a complete five-byte `JMP`, not an invented
C++ epilogue; its ordinary C++ member-forwarding source emits exactly
that optimized tail call.

The six-byte `00614BC6` source has an original native *this-result*
ABI: `MOV EAX,ECX`, clear native member DWORD through `AND [EAX],0`,
then `RET`. Natural C++ `ClearReturnMember* Reset() { flags=0;
return this; }` emits the **complete original six bytes** under
VC7.1 `/O1`. Additional independently compiled source controls found
that alternative normal constructors and bitwise-clear member
operations also emit those bytes under `/O1`; their source names
and historical class roles therefore remain unproven. VC7.1 `/O2`
instead emits a nine-byte `MOV [EAX],0` version, not original. No
artificial register-moving statement, dummy stack member, or inline
assembly was inserted to force the match.

[`verify-sdk-native-helper-leaves-f680.py`](../scripts/verify-sdk-native-helper-leaves-f680.py)
**fresh-compiles only this one small TU**. It independently checks
registered original whole function addresses/sizes and real x86
instruction order, prologue/exits, every zero-addend source COFF
`REL32`/`DIR32` field, actual original IAT/callee and linker-relative
displacement; only those physically authenticated fields are linked
into a transient compiler CODE buffer. The verifier then requires
**all 50 original machine CODE bytes** to be identical to the PE.
One separate original direct native x86 CALL graph scans all 4,351
registered CODE function extents, finding direct callers **14, 7, 3,
15, 1** respectively, with **zero currently author-classified direct
caller instructions**. This does not prove vendor authorship, exclude
indirect uses, or establish historical class layouts.

The earlier F595–F677 source-backed whole origin-UNKNOWN cohort
contained **76 distinct functions /1,509 original CODE bytes**.
F680 adds **five new whole native functions /50 original CODE bytes**:
**81 entire original source-backed unknown functions /1,559 bytes**,
all still uncredited. Original provenance inventory remains **95
unknown**; formal accepted game-authored whole exact stays **943
whole functions /862,726 original CODE bytes (43.71% reviewed)**.

```bash
scripts/repo-python scripts/verify-sdk-native-helper-leaves-f680.py
scripts/repo-python scripts/validate-tracking.py --require-target
```

New cold source COFF/PDB, compiler log, complete original PE linked
machine-byte proof and direct caller graph are retained in ignored
`.analysis/f680-sdk-native-helper-leaves/`. Grammar/O1/O2/Od
negative controls are separately preserved under ignored
`.analysis/f680-unknown-native-helpers/`. No all-943-unit cold replay,
original game EXE patch, fake stack locals, or external Oracle
whole-function acceptance.
