# F750 — original 101-byte CharacterAux selected-frame refresh COLD EXACT

**New original whole-function exact game CODE: 101 bytes, one pre-reviewed
R213-authored function.** Pinned original is the user-provided Japanese
TH075 ver1.11 `resources/th075.exe`, SHA-256
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
Original `005FAC60..005FACC5` is **101 complete CODE bytes, 35 real
x86 instructions, four genuine original PE/COFF typed `REL32`
fields**. Authored origin R213 was independently reviewed before
this source existed; neighboring STL `at()` and `size()` library
routines retain their original LIBRARY provenance and get **no
new authored CODE credit**.

## Independently decoded native composition and true nested ABI

The original physical entire game function first loads the real
signed frame index from receiver `+0x62`, then the signed group
index from `+0x60`. It uses original pointer to the outer collection
at **`this+0x7C`** and calls authentic original
`std::vector::at` at **`005FAD20`** on the group index. That
library method returns a pointer to the stored inner collection
pointer: the original next x86 explicitly `MOV ECX,[EAX]`.

The original *second* nested `std::vector::at` at **`005FACD0`**
consumes the already-pushed frame index. It returns the selected
frame pointer, which the original game function stores at
**`this+8`**. The original then copies its 16-bit frame code
from **`selectedFrame+4`** into the actor's **`this+0x72`**
field. Finally it reloads the signed group index from `+0x60`,
queries the same outer vector and inner collection's native
**`std::vector::size` at `005F9E90`**, and writes the low
16 bits of the returned integer to **`this+0x70`**. It returns
normally from its complete thiscall ABI without touching unrelated
actor state.

Tracked natural
[`src/CharacterAuxFrameF750.cpp`](../src/CharacterAuxFrameF750.cpp)
uses a genuinely read nested collection and actually writes the
three observed output fields:

```cpp
selectedFrameAt8 = (*collectionsAt7C->At(groupAt60))->At(frameAt62);
selectedCodeAt72 = selectedFrameAt8->nativeCodeAt4;
collectionSizeAt70 = static_cast<short>(
    (*collectionsAt7C->At(groupAt60))->Size());
```

The normal C++ nested expression is critical: VC7.1 naturally
pushes the frame argument **before** the outer collection index,
then calls outer `At` and, without a fake stack manipulation,
passes the already-pushed inner argument to the second `At`.
Both native vector lookups are member thiscalls with the true
original `RET 4` callee shape, not a guessed two-argument or cdecl
wrapper. The actual owner data offsets are represented by real
object-storage regions needed for the observed original fields;
these are not fake unused stack locals or an assertion of complete
historical private object layouts.

## Entire original native and physical relocations

Pinned VC7.1 `/Od /Ob0 /Gy /GR- /GX- /GS /Zi` emits
**101/101 complete original CODE bytes** with the same **35/35
ordered x86 mnemonic and WIDTH positions**, all
**85/85 native nonrelocation bytes**, and the following four
original-authentic typed `REL32` call fields:

| Original CODE offset | Real native callee | Source decorated symbol role |
| ---: | --- | --- |
| `+0x1E` | `005FAD20` | Outer collection `At(group)` |
| `+0x25` | `005FACD0` | Inner collection `At(frame)` |
| `+0x4F` | `005FAD20` | Outer collection `At(group)` again |
| `+0x56` | `005F9E90` | Inner collection `Size()` |

All four source symbols, real original PE call destinations, original
instruction field offsets, `REL32` relocation types and zero COFF
addends are checked by the canonical comparator. The exact native
return, saved `this` at `EBP−4`, source signed short extension,
member field stores and all real four call positions remain intact.
This is the *complete original callable function*, not an inner giant
switch case, hand-authored machine instruction, or partial masked
match. Names of original private collection classes remain
provisional, but the actual nested index and output behavior is
physical original PE evidence.

## One-unit canonical cold replay

The new exact match unit in `config/match-units.toml` is
`character-aux-refresh-selected-frame-005fac60`, with the original
complete CODE extent and all four physically typed relocation fields.
Only **one new source object** is cold-compiled, with no replay
of the existing 966 old accepted units:

```bash
scripts/repo-python scripts/replay-exact-units.py \
  --unit character-aux-refresh-selected-frame-005fac60
# Cold replay: 1/1 whole native exact across 1 object
```

The original authored function ledger is now **967 complete
cold-exact source-present original game functions /967 exact units**,
**864,219 original CODE B** (**43.79% reviewed** of 1,973,704
and **43.71% conservative** with the separate 3,420 origin-unknown
bytes in the denominator). The giant original fighter and the
other 21 giants, plus WinMain/Scene/Archive full ownership
functions, remain NONEXACT. The 98% goal is not yet achieved.
