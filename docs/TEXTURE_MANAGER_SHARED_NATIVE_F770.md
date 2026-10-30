# F770 — shared TextureManager allocation, complete 261-byte cold exact

**Accepted one complete independently R017-authored game function:**
`0040B000..0040B104` (inclusive) from the pinned Japanese TH075
v1.11 `resources/th075.exe`, SHA-256
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
Original **261 native CODE bytes, 79 x86 instructions, 11 genuine typed
zero-addend PE/COFF relocation fields**. Real normal VC7.1 C++ source:
[`src/TextureSharedF770.cpp`](../src/TextureSharedF770.cpp).
Historical complete TextureManager/element classes remain provisional.

## Original game behavior and physical object ownership

The real `thiscall` takes an element count, extra shared-texture count and
one-byte texture mode. It first constructs the same physically witnessed
**44-byte VC7 element** as the independently accepted F769 allocator,
through original ctor `0040D8C0`. It stores the mode at `this+0x4C`,
normalizes modes other than `0x10`, `0x18` and `0x20` to `0x10`, then
fills the original `this+8` vector via `0040DDA0` with the constructed
record, and fills `this+0x18` and `this+0x28` vectors via `0040DF20`
with null/zero pointer values. It creates one **256×256** 16-bit texture
per extra slot, using original vector `At(0040DEE0)` and independently
matched graphics texture creator `00401B20`. It finally destructs the
real local element via `0040D8E0`, restoring native VC7 `/GX`
`FS:[0]` exception state. None of these separate SDK/library callees
are newly credited as authored game CODE.

The original saves `this` at **`EBP−0x48`**, uses an original
`SUB ESP,0x3C` frame, retains first vector zero at `EBP−0x40`,
uses third vector zero at **`EBP−0x44`**, and stores the actual
loop counter at **`EBP−0x10`**. This stack layout comes from
independent original PE bytes, not guessed data-member names.

## Finding the real lexical lifetime, not artificial padding

The initial candidate was already the native **261 B /79 x86
/11 field** geometry, with **210/217** original nonfield bytes
matching. Its seven real differences were EBP offsets:
third-vector zero at `−0x10` (original `−0x44`) and loop index at
`−0x44` (original `−0x10`). Changing all declarations' order,
blind scopes, the `DWORD` zero into a real null texture pointer,
using a temporary bound to `const&`, and replacing unsigned index
with signed index **did not** fix the original physical roles.

A 26-variant normal entire-function C++ lexical-lifetime sweep found
one specific authentic layout: the first vector zero is used outside;
**declare the real unsigned loop index before the third vector's
zero temporary, then construct/use that zero in its own nested scope**,
and use the already-declared index in the subsequent actual
`Create16BitTexture` loop. The compiler naturally assigns the
native `−0x44/−0x10` slots and emits **217/217** identical
nonrelocated machine bytes. Both variables are genuinely used; no
padding-only local, assembly, target byte graft or cropped-function
comparison was involved.

## Native PE, original COFF and one-unit acceptance

| Original CODE offset | Original type | Real original PE target |
| --- | --- | --- |
| `+06`, `+0C`, `+14`, `+FB` | DIR32 | compiler EH handler `00654F24` and `__except_list` fields |
| `+22`, `+F1` | REL32 | real texture element ctor `0040D8C0`, dtor `0040D8E0` |
| `+70` | REL32 | initial 44-byte texture element vector `Assign`, `0040DDA0` |
| `+8A`, `+A4` | REL32 | second and third vector `Assign`, `0040DF20` |
| `+CD` | REL32 | shared vector slot `At`, `0040DEE0` |
| `+DD` | REL32 | native `Graphics::Create16BitTexture`, `00401B20` |

All **11 physical original relocation fields** were independently
reread from the pinned PE and matched against their exact source
COFF offset, DIR32/REL32 owner type, original decorated symbol,
zero addend and resolved PE destination. Original whole function
**261/261 CODE bytes /79 x86 /217/217 nonfield bytes** were compared.

```bash
scripts/repo-python scripts/replay-exact-units.py \
    --unit texture-manager-allocate-shared-native-0040b000
# texture-manager-allocate-shared-native-0040b000: exact; 261 coverage bytes
# Cold replay: 1/1 exact units across 1 object
```

Formal whole-authored ledger advances **974→975 exact functions**,
**865,811→866,072 native CODE bytes**, reviewed **43.88%**, and
conservative **43.80%**. Still **22 giant originals +7 small/medium
originals** (5,577 small/medium CODE bytes) nonexact; 98% objective
not reached. No mass cold replay or original PE modification.
