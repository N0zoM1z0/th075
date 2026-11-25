# F595 — TextOverlay raster setter and two lifetime controls

The Japanese TH075 v1.11 function at `0x004135F0` writes a byte at
`this+0x24`, then two four-byte values at `this+0x1C` and `this+0x20`.
The original 40-byte body contains 16 x86 instructions, takes three stack
arguments, returns with `RET 0xC`, and has no relocations. The F595
raw-word control reproduced the whole body with VC7.1
`/Od /Ob0 /Gy /GR- /GX- /GS /Zi`. The original call graph audit found
no direct caller or literal pointer to the setter.

R287 identified the fields through the adjacent text renderer, which
writes them in the same order and uses them as a tint byte and two
floating-point raster offsets. The live `TextOverlay` layout uses
those types and passes the complete exact comparison. The original
parameter declaration remains unknown.
[R287 renderer evidence](ORIGIN_PENDING_REVIEW.md#r287--sprite-capacity-and-text-raster-setters)

F595 also inspected two independent lifetime controls. Later comparisons
resolved both origins.

- `0x004588B0` is the 43-byte frame-prefix destructor. F595 counted six
  direct call sites. The allocation and unwind paths identify the owned
  extension at prefix offset `+8`.
  [R274 frame-prefix evidence](ORIGIN_PENDING_REVIEW.md#r274--the-game-frames-optional-extension-cleanup)
- `0x00449DE0` is the 45-byte stage base constructor. F595 found 36
  direct callers in the stage loaders and a vtable with a deleting
  destructor followed by five pure virtual entries. The explicit and
  implicit constructor builds place the full code interval differently.
  [R305 stage-base evidence](ORIGIN_PENDING_REVIEW.md#r305--stage-base-constructor-follows-the-deleting-destructors)

All three functions are authored in the
[origin ledger](../config/function-origins.csv) and exact in the
[comparison manifest](../config/match-units.toml). Cold-replay the setter with

```bash
scripts/repo-python scripts/replay-exact-units.py --unit text-overlay-set-raster-parameters-004135f0
```
