# F765 — original SpriteDrawing opaque quad at 0040D790, complete 171-byte cold exact

**Accepted one complete original R011 independently game-authored
function**, `0040D790..0040D83A`, consisting of **171 native CODE
bytes / 52 x86 instructions / six genuine zero-addend typed original
PE/COFF reference fields**. The target is user-supplied Japanese
TH075 v1.11 `resources/th075.exe`, SHA-256
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.

The single accepted normal VC7.1 C++ source is
[`src/SpriteOpaqueDrawF765.cpp`](../src/SpriteOpaqueDrawF765.cpp).
The historical class name and full private sprite-owner layout are
still provisional borrowed views, not proven class definitions.

## Original complete game source behavior

The native `thiscall` draws an opaque screen sprite from a texture
index, screen X/Y coordinates, and tint. It reads the true original
texture record twice through `this+8` and native vector `At(0040DD60)`:
the record's observed width and height are at `+4` and `+8`.
Its texture `RECT` starts at `(0,0)`, with right and bottom set to
these actual record fields. The destination `RECT` spans
`(x,y)` to `(x+width,y+height)`. The source calls the real
`Graphics::SetBlendMode(0)` (`00401F50`), retrieves the texture
through independently accepted `GetTexture(0040C8C0)`, and draws
via original `Graphics::DrawTexturedQuad(004029F0)`.

It constructs a **132-byte** native drawing quad from the destination
RECT via the separately original-matched native constructor `0040DB50`.
Its true four 16-byte position vectors and separate 68-byte payload are
already physically witnessed by existing source/other original calls.
This new C++ source passes that original quad as a normal constructed
temporary, which causes the genuine MSVC `thiscall` return and graphics
argument order without fabricated ABI assembly.

## Resolving the real VC7.1 stack ownership

Initial used-owner C++ included a redundant `SpriteRecordList*` local;
that altered actual C++ compiler lifetimes. Removing the unnecessary
pointer and accessing the real borrowed `this+8` vector directly
preserved the complete **171 B/52 x86/6 typed COFF** geometry but
still matched only **135/147 nonrelocated native CODE bytes**.

The remaining 12 differences were authentic local EBP displacements,
not missing instructions. The original native frame uses
`SUB ESP,0xA8`, retains this at **`EBP−0xA8`**, and places its
132-byte actual quad at **`EBP−0xA4`**. The texture-area RECT starts
at **`EBP−0x10`**, and the target destination RECT at
**`EBP−0x20`**. A naive single lexical scope for the two RECTs
assigned them in the reverse stack order. Reversing declaration
order alone did NOT fix the used variable placement.

Eight genuine used-lifetime full-function C++ permutations were freshly
compiled: swapped declarations, nested scopes for either rectangle,
both nested, alternate integer backing record views. Only the true
C++ lifetime **outer `textureBounds`, inner `destination`** caused
VC7.1 to assign the two RECTs exactly as original and emit **147/147
identical nonfield machine bytes**. This is original game object
lifetime reconstruction, not synthetic padding or non-executed locals.

## Six independently verified real PE/COFF relocation fields

| Original whole-function CODE field | Kind | Original native PE target |
| --- | --- | --- |
| `+0x2B`, `+0x43` | REL32 | `0040DD60` real indexed sprite rectangle record |
| `+0x6E` | REL32 | `00401F50` graphics blend mode |
| `+0x80` | REL32 | `0040C8C0` texture resolver |
| `+0x98` | REL32 | `0040DB50` real 132-byte quad RECT constructor |
| `+0x9E` | REL32 | `004029F0` original graphics textured draw |

Every one has the original byte-field offset, authentic `REL32` owner,
zero addend, source decorated COFF symbol and independently read original
PE relative-call destination. They are listed in canonical exact unit
`sprite-draw-opaque-native-0040d790` in
[`config/match-units.toml`](../config/match-units.toml).

The final freshly compiled source is a **complete exact whole original
function**, not a cropped favorable fragment: 171/171 native CODE,
52/52 ordered actual x86 and 6/6 physical typed fields. Selected
formal cold replay, **only the newly affected unit**:

```bash
scripts/repo-python scripts/replay-exact-units.py \
  --unit sprite-draw-opaque-native-0040d790
# sprite-draw-opaque-native-0040d790: exact; 171 coverage bytes
# Cold replay: 1/1 exact units across 1 objects
```

Official authored whole-function count is now **972** exact functions,
**865,415 original CODE bytes**, **43.85%** reviewed and **43.77%**
conservative coverage. There remain **22 large authored bosses and 10
small/medium authored whole functions** nonexact. The original 98% goal
remains unachieved. No full 972-unit cold replay, other original PE
modification, independent library/Windows/CRT CODE credit or
unknown-origin promotion occurred. Other original SpriteDrawing
wrappers `0040C9A0` and `0040CA20` remain separate NONEXACT work.
