# F687 — two entire original 58/64-byte optimized virtual COM owner destructors

Original pinned user-supplied Japanese TH075 v1.11 `resources/th075.exe`,
SHA256 `bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
These are **two distinct complete native registered PE functions**,
not hand-cropped original giant snippets. Their actual original
`config/function-origins.csv` rows stay **`origin=unknown,
disposition=review`**. Native virtual ABI and byte identity do NOT
establish the game's original author, SDK class names or a complete
resource object layout.

| Original whole function | Actual original complete CODE | Native original x86 | PE/COFF source refs | Source C++ program |
| --- | ---: | ---: | ---: | --- |
| `00608D8E` | **58/58 linked native B** | **22** | 4 actual typed fields | Null-checked resource reset/destroy, imported free and COM release |
| `00608F96` | **64/64 linked native B** | **27** | 1 vftable `DIR32` | Two conditional stdcall COM handle releases plus final COM release |
| **Two independent complete original functions** | **122/122 B** | **49** | **5 genuinely typed PE fields** | Source provenance still UNKNOWN |

The original `00608D8E` first saves ESI, loads actual resource at
`this+0x48`, tests for nonnull, writes its genuine vftable
`0065D348` and invokes original real thiscall methods `0061F42F`
and `0061F452`. It then tests the original pointer at `this+8` and,
if nonnull, frees it through original imported `__stdcall` IAT
`0065704C`. Finally it loads actual COM-like pointer `this+0x4C`,
tests nonnull, obtains its real vtable and invokes the authentic
**`__stdcall` virtual call at vtable offset `+8`**, passing the
object via `PUSH` (not `MOV ECX`), before ESI restoration/RET.
The authentic physical PE fields are original `DIR32` vftable at
function `+10`, real `REL32` reset at `+17`, real `REL32` destroy
at `+25`, and original imported free `DIR32` at `+39`.

The original `00608F96` has native resource at `this+8` and real
vftable `0065D374` at source offset `+10`. It conditionally passes
actual handles at `this+0x14` and `this+0x10` into **two genuine
indirect `__stdcall` vtable slot `+0xE0` calls** on the resource,
with the original object pointer pushed as a separate first
argument. It then performs the original final COM vtable offset
`+8` release on that same resource and returns. These indirect
virtual method calls do **not** create fake PE/COFF relocations;
its only genuine source COFF reference is the original zero-addend
vtable `DIR32`.

## Real C++ source and VC7.1 optimization, not manufactured vtables

The tracked ordinary C++ file
[`SDKNativeCOMOwnerDestructorsF687.cpp`](../probes/SDKNativeCOMOwnerDestructorsF687.cpp)
uses *only the observed native member offsets* via explicit typed
pointer accesses, and calls the actually observed native vtable
slots `+8` and `+0xE0` directly using correct `__stdcall` function
pointer types. It **does not invent an entire interface class
with 57 fake virtual declarations** to access slot `0xE0`, nor
allocate imaginary owner members to reach original offsets.
Actual `Reset`/`Destroy` class and owner names are provisional
compiler ABI grammar, not recovered historic names.

A meaningful initial source trial placed these virtual calls in
**noninlined static C++ helper functions**. Under pinned VC7.1
`/O1 /Ob0 /Gy /GR- /GX- /GS /Zi`, that produced a wrong tail jump
and a short 57-byte/20-x86 first destructor, as well as a wrong
58-byte/24-x86 second destructor. This was **not** original behavior.
Replacing the unnecessary wrapper with the *actual virtual callback
expression in each real destructor* gives **58/22 and 64/27 entire
original code** with all genuine native indirect calls naturally
emitted. Both tested `/O1` and `/O2` produce whole native byte
identity for these **particular** two functions; no executable-wide
compiler profile is inferred.

[`verify-sdk-native-com-owner-destructors-f687.py`](../scripts/verify-sdk-native-com-owner-destructors-f687.py)
compiles **one small native C++ translation unit** under pinned
VC7.1 `/O1`. It independently checks the two registered original
complete PE extents, every original x86 instruction width/operand,
original call and virtual slot geometry, and each actual typed
zero-addend compiler COFF field and genuine original PE target.
It temporarily links only the physically authenticated original
`DIR32` vtables, original two real thiscall `REL32` destinations,
and the real original imported free `DIR32` in the new compiler
CODE buffers. It then requires **all 122 original machine CODE
bytes** to match exactly. Independently scanning all 4,351
registered native CODE functions finds **one direct original caller
for each destructor**, each currently classified as `compiler`,
not historically author-attributed. Indirect uses are not excluded.

F595–F686 research had **82 distinct source-backed whole origin-
UNKNOWN functions /1,578 true original CODE bytes**. F687 adds
**two new complete originals /122 B**, raising the still-uncredited
research cohort to **84 distinct complete original functions /
1,700 native CODE bytes**. All **95 historical source-unknown
ledger candidates** retain `unknown,review`; neither of these
functions gets whole game-authored exact credit. Formal accepted
authored whole-game exact stays **943 functions /862,726 original
CODE bytes (43.71% reviewed)**. Fighter internal-case source
research likewise remains separate and uncredited.

```bash
scripts/repo-python scripts/verify-sdk-native-com-owner-destructors-f687.py
scripts/repo-python scripts/validate-tracking.py --require-target
```

The new complete linked original PE/COFF comparison receipt, cold
VC7.1 OBJ/PDB, compiler log, source hash and original direct caller
graph remain in ignored `.analysis/f687-native-com-owner-source/`;
meaningful wrong-wrapper source alternatives and their actual
compiler outputs in ignored `.analysis/f687-sdk-com-lifetimes/`.
No original EXE patch, fake padding, arbitrary machine bytes,
all-943-unit cold replay or external Oracle whole-function
acceptance was performed.
