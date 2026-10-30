# F776 — original SpriteDrawing variant/mode draw, complete 994-byte cold exact

**One newly accepted independently R011-authored entire original game
function** `0040CEF0..0040D2D1` in the pinned Japanese TH075 v1.11
`resources/th075.exe` (SHA-256
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`).
The actual original callable CODE is **994 bytes /269 complete x86
instructions /15 authentic zero-addend PE/COFF relocation fields**.
Natural normal VC7.1 C++ source:
[`src/SpriteVariantDrawF776.cpp`](../src/SpriteVariantDrawF776.cpp).
The historical game owner class, borrowed 132-B quad payload members
and texture vector private meanings are not asserted beyond observed
physical positions.

## Entire original game behavior, including distinct mode path

This `thiscall` takes texture index, X/Y, tint, pivots, uniform scale,
rotation angle, flip flags and a final mode byte. Its first native
branch checks **mode == 0**: this path delegates nine original
arguments to `0040CA80`, and jumps to the actual common epilogue.
For nonzero mode, the source constructs an actual **132-byte** quad
through original default ctor `0040D990`, reads physical texture width
and height twice through real texture entry `At(0040DD60)` and
prepares the nested texture-area `RECT`.

The original next branch first chooses unrotated/default-scale quad
construction via real four-coordinate ctor `0040DA00`, then a more
specific unrotated/non-unit-scale constructor branch, or computes a
rotated quad with original radians factor `00657828`, zero-angle
global `0065782C`, cosine helper `0040D900` and sine `0040D940`.
The rotated quad uses its actual four 16-byte X/Y vertex positions
and shared uniform scale; first/second and fourth/third vertices
are swapped through an actual 16-byte `D3DXVECTOR4` local when
flags `&1` is set (real vector temporary ctor `0040D980`).
The final original source calls texture getter `0040C8C0` and graphics
`DrawTexturedQuad(004029F0)` with original region and color. No
invented fallback behavior, additional graphics state or target
machine-byte injection was used.

## Correcting a real branch semantics / x87 unordered comparison error

A first natural candidate directly adapted from the newly exact F775
sprite source and decompiler sketch was **995 bytes /269 x86**,
but failed the original second branch, with genuine x87 `JNP`
when the original PE has **`JP`**. The naive candidate put the
rotated body first:

```cpp
else if (scale == 1.0f || angle != zeroAngle) {
    // rotation
} else {
    // unrotated scaling
}
```

The pinned original actually emits **CMP scale,1; JE rotation;**
then **FUCOMPP/FNSTSW/TEST AH,44h; JP rotation**. The unrotated
scaling body is the fall-through. The correct ordinary C++ source
expresses the genuine conditional with the **unrotated body first**:

```cpp
else if (scale != 1.0f && angle == zeroAngle) {
    // unrotated scaling
} else {
    // rotation
}
```

This is not a purely cosmetic change in the presence of unordered
floating-point status bits; the original branch destination and
x87 status test are essential evidence. Correcting this true
control-flow order naturally restores **all 269 native x86 mnemonic,
size and position matches**, and the complete **994 bytes**.
The quad remains at native `EBP−0x88`, texture region at `EBP−0x98`
and saved receiver at `EBP−0x1BC`, as already independently observed
in F775. No synthetic stack padding or cropped positive subrange.

## Original PE/COFF fields and selected one-unit verification

| Original CODE offset | Kind | Original PE destination |
| --- | --- | --- |
| `+44` | REL32 | base sprite draw `0040CA80` |
| `+54` | REL32 | native quad default constructor `0040D990` |
| `+7A`, `+95` | REL32 | actual texture entry `At(0040DD60)` |
| `+AD`, `+11B` | DIR32 | native zero-angle global `0065782C` |
| `+F8`, `+172` | REL32 | original four-coordinate quad ctor `0040DA00` |
| `+18F`, `+1AD` | DIR32 | original radians factor `00657828` |
| `+198`, `+1B6` | REL32 | cosine `0040D900`, sine `0040D940` |
| `+2E0` | REL32 | 16-byte swap temporary ctor `0040D980` |
| `+3BB`, `+3D3` | REL32 | texture getter `0040C8C0`, draw `004029F0` |

All **15 physical original PE relocation fields** were independently
reread and compared with the new object's exact offsets, typed
`DIR32/REL32` owner instructions, zero addends, decorated symbols
and native PE target destinations. The entire original ends at
`0040D2D2` exclusive. The full cold object has **934/934 identical
nonrelocated original bytes** plus all 15 real source-owned fields.

```bash
scripts/repo-python scripts/replay-exact-units.py \
  --unit sprite-drawing-variant-native-0040cef0
# sprite-drawing-variant-native-0040cef0: exact; 994 coverage bytes
# Cold replay: 1/1 exact units across 1 objects
```

The independently accepted authored ledger advances **976→977
whole functions**, **867,042→868,036 original CODE bytes**,
**43.98% reviewed** and **43.90% conservative** coverage.
Remaining are **22 giant** and **5 smaller original-authored whole
functions** (**3,613 native CODE bytes**). The 98% objective remains
unmet. No full all-unit cold replay, target EXE editing or
separately credited vendor/SDK callable CODE.
