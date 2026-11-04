# F1067 — Typed native game flash health/position/bar/flags, full 1,081B exact

The Japanese TH075 v1.11 original has one independently authored
**1,081-byte exact** `BattleDamageFlash4406C0::RenderFlash` at
`004406C0`. It renders flash bars for both real actors: checks
collision-frame state, signed current health, valid action range,
vertical position and signed flash bar length, then uses the
original float-to-int geometry, native `SetRect` and two genuine
`Graphics::DrawFilledRectangle` calls for each side.

Before F1067, the complete already-exact C++ source still reached
those native values through unrelated byte-offset casts. The real
source now uses independently established narrow borrowed original
fields from exact other game source objects:

- `F999_VITAL(actor).currentAt324`: the real signed-short actor health
  at original fighter+`0x324`; separate left and right checks are
  preserved, without inventing the entire fighter class.
- `F1037_POSITION(actor).xPosition/yPosition`: actual 32-bit float
  actor physical X/Y at +`0x44/+0x48`, used in both native short-circuit
  guards and *ten* original rectangle-geometry float reads across two
  render branches. Original x87 expression/argument order is unchanged.
- `F1067_FLASH_BAR(actor).barLengthAt3C8`: a real borrowed signed short
  physical original fighter+`0x3C8`, used for the red/orange/yellow
  gradient pulse and actual horizontal bar geometry. There are twelve
  genuine original signed bar-length reads across both sides.
- `F1067_FRAME_FLAGS(frame).flagsAt3C`: the real 32-bit flags at the
  **collision frame+`0x3C`**, reached only after obtaining the native
  frame pointer stored at fighter+`0x74`. It is **not** a member of
  the fighter itself. The original `0x100000` mask and side-specific
  predicate are preserved.

`FlashGaugeBorrowF1067.hpp` enforces the 2B signed flash bar and
4B flags representations with compile-time size checks. These are
**borrowed** field windows: none of the new types is instantiated,
used as a complete historical owner or padded to mimic stack layout.
The original real view and flag pointer owners remain independent.

## Entire original native function retained, no fragile local acceptance

The actual pinned MSVC7.1 `/Od /Ob0 /Gy /GR- /GX- /GS /Zi`
`src/BattleDamageFlash4406C0.cpp` object was cold-compiled and replayed
against the original SHA-pinned Japanese TH075 **after each of four
separate source edits**: first both vitals, then X/Y position views,
then the signed flash bars, then the collision-frame 32-bit flags.
All four **full 1,081B original function** replay attempts passed
strict original whole native CODE and every physical COFF relocation
check (`1/1 exact` each), including real x87 constants, CRT float
conversion, two predicate calls, `SetRect` and rectangle drawing.

This avoids the earlier F1053 source-parens/x87 pitfall: F1067 made no
extra algebraic parentheses or operand-order changes. The direct C++
member views emit the exact original native FPU sequence. Legacy
`LEFT_FLOAT`/`RIGHT_FLOAT` raw pointer macros are now genuinely unused
and are removed, not left as misleading apparent ownership.

Reproduce only the affected **one** complete callable, never a
mass replay of 979 units:

    scripts/repo-python scripts/replay-exact-units.py \
        --unit battle-damage-flash-004406c0

Historical intermediate full C++ controls and compiler logs remain
under ignored `.analysis/f1067-*` and the usual local replay output.
**Original already accepted 1,081B remains exact; zero new game CODE
bytes or new whole functions were credited.** The game EXE and
reconstruction manifest/relocation identity rules were not modified.
