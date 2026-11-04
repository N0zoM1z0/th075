# F1056 — Real borrowed collision RECT, fighter vital WORDs and position axes

The pinned Japanese TH075 v1.11 original game uses the collision owner
physical offsets **+0x34, +0x38, +0x3C, +0x40** as an adjacent
16-byte `RECT`-shaped bounding window. Original `ClearBounds()` and
`IncludePair()` read/write each real bound with signed 32-bit MOV/CMP
in the native sequence and compare the corresponding two input RECTs.
These values are neither a pointer stored at +0x34 nor an independently
allocated `RECT` object: the complete original collision owner layout
remains unknown.

Before this change, `src/BattleCollision.cpp` expressed the *same*
physical four bounds through 20 raw casts (four `int` native writes,
and sixteen `long` reads/writes), hiding their genuine rectangular
relationship. `F1056_BOUNDS(this)` now exposes the verified borrowed
native Win32 `RECT` at owner+0x34 and uses the corresponding actual
`left/top/right/bottom` fields. `RECT` has precisely the original
four 32-bit signed fields in the pinned 32-bit MSVC/Win32 build.

This same original source object handles combat impact and actor
collision transforms. Its real original native code establishes:

- Signed 16-bit health at fighter+0x324 and adjacent recoverable
  health at +0x326, already independently evidenced by
  [`FighterVitalBorrowedF999`](../src/FighterVitalBorrowedF999.hpp).
  Impact now uses `F999_VITAL(defender)` instead of three separate
  +0x324 casts and a raw +0x326 cast.
- Position X and Y floats at actor+0x44 and +0x48, already verified
  through the separate complete-frame `FrameActorPositionPairF1037`
  source. The original sprite rectangle transform reads X four times
  and Y twice, forwards both to the authentic `CeilCollisionCoordinate`
  game helper and preserves the real facing-dependent bound order.

None of these borrowed views assumes a complete historical fighter,
collision owner or encoded member pointer; all are physically narrow
read/write interfaces with the original scalar type and offset.
Original game call order, x87 source expression form, branch semantics,
global symbols and stack layouts are kept intact. No synthetic locals,
inline asm, copied target machine bytes or fake compile ABI were added.

## Strict original complete-callable evidence

Three successive real normal VC7.1 `/Od /Ob0 /Gy /GR- /GX- /GS /Zi`
source-object rebuilds checked the actual native original after each
change: first the RECT views, then the real adjacent health WORDs,
then the position axes. The final replay rebuilt **only the changed
`BattleCollision.cpp` translation unit** and compared **all five
complete original callables** and their physical COFF field identities.

| Original complete game callable | Previously accepted original CODE |
| --- | ---: |
| ApplyImpact | 304B |
| ClearBounds | 51B |
| IncludePair | 217B |
| TestOverlap | 68B |
| TransformBounds | 215B |
| **Full one-object cold replay** | **5/5 exact, 855/855B** |

Reproduce only this affected source object, not all 979 exact units:

    scripts/repo-python scripts/replay-exact-units.py \
        --unit battle-combat-apply-impact \
        --unit battle-collision-clear-bounds \
        --unit battle-collision-include-pair \
        --unit battle-collision-test-overlap \
        --unit battle-collision-transform-bounds

**No new accepted exact original CODE bytes/functions** were added;
these 855 bytes were already credited. No target PE modification,
relocation mask relaxation or corpus-wide cold replay was performed.
