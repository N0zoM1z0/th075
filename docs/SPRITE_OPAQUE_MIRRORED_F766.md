# F766 — complete original SpriteDrawing mirrored opaque render, 212 native CODE bytes

**One more accepted independently R011-authored whole game function**:
`0040D6B0..0040D783` in the pinned Japanese TH075 v1.11
`resources/th075.exe`, SHA-256
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
It is **212 complete original CODE bytes /66 native x86 instructions
/6 real typed zero-addend PE/COFF fields**, accepted by its own
**1/1 exact canonical cold replay**, not a separate interior case.

## Recovered real branch and data ownership

After reconstructing F765's independent opaque sprite draw, the
original `0040D6B0` is a closely related but **distinct complete
mirrored** function. It reads the same native borrowed vector at
**`this+8`** through `0040DD60` twice, using original record width
at `entry+4` and height at `entry+8`. The texture RECT retains
`left=0, top=0, right=width, bottom=height` at original
**`EBP−0x10`**.

The distinct original byte flag is the fifth stack argument, read
through `(unsigned char)[EBP+0x18] & 1`. It naturally controls two
real render destination paths:

- When set, destination `right=x`, `left=x+width` (reversed
  horizontal coordinates); `top=y`, `bottom=y+height` remain natural.
- Otherwise, destination `left=x`, `right=x+width`, with the same
  actual top and bottom assignments.

In both branches, the destination RECT lives in a genuine nested
C++ lexical scope at original **`EBP−0x20`**, and the real 132-byte
quad temporary is constructed at **`EBP−0xA4`** via native constructor
`0040DB50`. The enclosing sprite object's saved `this` remains at
**`EBP−0xA8`**, with native frame `SUB ESP,0xA8`.

The function always calls real `Graphics::SetBlendMode(0)` at
`00401F50`, obtains the indexed texture at `0040C8C0`, and
invokes the original graphics draw at `004029F0`. The normal C++
source is [`SpriteOpaqueMirroredF766.cpp`](../src/SpriteOpaqueMirroredF766.cpp),
borrowing only physically observed class/record/quad views. Historical
full manager layout, private payload content and owner names remain
provisional; we do **not** introduce fake allocations or extra state.

## Physical whole PE/COFF proof

The entire **212-B/66-x86 original function and the freshly generated
VC7.1 source have 188/188 identical nonfield CODE bytes**. All six
original physical zero-addend `REL32` call fields were independently
reread from the original PE and match the actual compiler COFF
symbol, type, exact offset and linked original destination:

| Original function field | Actual PE destination | Original callee role |
| --- | --- | --- |
| `+0x2B`, `+0x43` | `0040DD60` | genuine record vector `At(index)` |
| `+0x97` | `00401F50` | Graphics blend mode 0 |
| `+0xA9` | `0040C8C0` | previously accepted native texture resolver |
| `+0xC1` | `0040DB50` | original 132-B rect-quad constructor |
| `+0xC7` | `004029F0` | original textured quad rendering |

Canonical unit `sprite-draw-opaque-mirrored-0040d6b0` records
this exact source, all real fields and original 212-B extent.
Selected **only** the new whole-function cold replay:

```bash
scripts/repo-python scripts/replay-exact-units.py \
  --unit sprite-draw-opaque-mirrored-0040d6b0
# sprite-draw-opaque-mirrored-0040d6b0: exact; 212 coverage bytes
# Cold replay: 1/1 exact units across 1 objects
```

No original EXE patch, source-only unused padding, assembly, truncated
matching, full 973-unit replay or unrelated compiler/library CODE
credit. This raises canonical authored complete-function matching
from **972 to 973**, original CODE from **865,415 to 865,627 bytes**,
reviewed coverage to **43.86%** and conservative to **43.78%**.
The incomplete authored backlog now comprises **22 large original
whole bosses and 9 smaller callable functions** (6,022 original
CODE bytes). The 98% authored-byte objective remains incomplete.
