# F775 — original SpriteDrawing scaled and rotated quad, 970-byte whole cold exact

**Accepted one independently R011-authored entire original game function** at
`0040D2E0..0040D6A9` in the pinned Japanese TH075 v1.11 executable
`resources/th075.exe`, SHA-256
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
The actual original callable CODE contains **970 bytes /257 native x86
instructions /14 physical zero-addend PE/COFF typed relocation fields**.
The ordinary C++ source is
[`src/SpriteScaledDrawF775.cpp`](../src/SpriteScaledDrawF775.cpp),
with an observed borrowed 132-byte quad view. Historical private
class identities/unknown payload fields are not asserted.

## Entire original sprite behavior and true C++ object lifetime

This `thiscall` takes texture index, screen X/Y, color, X/Y pivot,
independent X/Y scale, rotation angle, and a horizontal flip byte.
The original uses the `this+8` texture-record vector, accessing real
original `0040DD60` **twice** to obtain physical width at record `+4`
and height at `+8`. It constructs the true native **132-byte** quad
via `0040D990` and copies the 132-byte temporary returned by native
four-coordinate constructor `0040DA00` using `REP MOVSD` of exactly
33 DWORDs. It constructs a vector swap temporary via native
`0040D980`, then flips first/second and fourth/third position vectors
when flags `&1` is nonzero. The final call uses real texture resolver
`0040C8C0` and original `Graphics::DrawTexturedQuad(004029F0)`.

Its native float policies have three branches: both scales 1.0 and
angle equal to observed zero global `0065782C`; zero angle with
independent scales; or rotated arbitrary-scale geometry using native
radian multiplier at `00657828`, cosine helper `0040D900`, sine
helper `0040D940` and the actual four X/Y vertex formulas. No
unproven SDL/runtime or game behavior is added.

## Correcting two genuine source errors using the actual PE

An initial candidate, composed by *inspecting* related accepted
sprite drawing C++ rather than trusting its historical private layout,
emitted **949 bytes /257 x86 /14 fields**, with quad at
`EBP−0x98`, texture RECT at `EBP−0x10`, and 15 wrong ordered
x87 opcodes. The original is **970 bytes** with quad
**`EBP−0x88`**, texture region **`EBP−0x98`**, actual saved
`this` at `EBP−0x1BC` and two temporary scaled-image integer
values at `EBP−0x90/−0x8C`.

Seven real used-lifetime C++ source controls were freshly compiled.
Simple reverse declaration did **not** change local ownership;
placing the **constructed quad in the outer lifetime** and the
**genuine texture RECT in the inner lifetime** naturally restored
original quad and RECT physical stack addresses, and made the
complete candidate **970 bytes /257 x86**. No fabricated stack
padding, fake unused members or manual assembly was needed.

The remaining **15 opcode/width mismatches** were *not* compiler
cosmetics. The original native PE revealed three actual x87 expression
sequencing requirements:

- `quad.first.x`: evaluate the actor X minus pivot-X times X-scale
  times cosine **first**, then add pivot-Y times sine.
- `quad.fourth.y`: evaluate actor Y minus pivot-X times X-scale times
  sine **first**, then add scaled bottom-relative cosine.
- `quad.third.y`: evaluate scaled right-relative sine plus actor Y
  **first**, then add bottom-relative scaled cosine.

The initial C++ used mathematically commuted additions and caused
MSVC 7.1 to emit an incorrect `FLD/FMUL/FSUBR` order. Reordering
those three **genuinely used arithmetic expressions**, preserving
the actual meaning, restored *all* native 257 x86 instruction
mnemonics, positions and widths. The full 970-byte final object
now has **914/914 identical nonrelocation bytes**.

## Independent PE/COFF physical references and selected cold replay

| Original CODE offset | Type | Original native destination |
| --- | --- | --- |
| `+18` | REL32 | native quad default constructor `0040D990` |
| `+3E`, `+59` | REL32 | texture record `At(0040DD60)` |
| `+7A`, `+DF` | DIR32 | observed zero-angle global `0065782C` |
| `+C5`, `+136` | REL32 | quad four-coordinate constructor `0040DA00` |
| `+153`, `+16E` | DIR32 | observed angle/radians factor `00657828` |
| `+15C`, `+177` | REL32 | native cosine/sine `0040D900` / `0040D940` |
| `+2C8` | REL32 | original vector temporary constructor `0040D980` |
| `+3A3`, `+3BB` | REL32 | real texture lookup `0040C8C0` / draw `004029F0` |

All **14 real original** physical field offsets, original DIR32/REL32
types, source decorated COFF owners, zero addends, and independent
original PE target destinations were checked before acceptance. The
last x86 instruction ends at original `0040D6AA` exclusive; neither
an interior fragment nor after-RET DATA was accepted.

```bash
scripts/repo-python scripts/replay-exact-units.py \
  --unit sprite-drawing-scaled-native-0040d2e0
# sprite-drawing-scaled-native-0040d2e0: exact; 970 coverage bytes
# Cold replay: 1/1 exact units across 1 objects
```

Official whole original-authored CODE coverage advances **975→976 exact
functions** and **866,072→867,042 native CODE bytes**, reviewed
**43.93%**, conservative **43.85%**. Still **22 giant original
functions** and **6 smaller authored whole functions** (**4,607
unmatched small/medium CODE bytes**) remain NONEXACT. The 98% goal
is incomplete. No all-unit cold replay, target executable patch,
credit for vendor functions, or invented origin promotion occurred.
