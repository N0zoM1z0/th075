# F960 — Typed actual fighter notice/HUD native fields, fourteen whole units exact

The SHA-pinned Japanese TH075 v1.11 native original
independently accesses a family of genuine **fighter
notice/HUD byte and signed-short fields** in three
separate original compiled translation units.
The original physical fields are not inferred from
old source comments or guessed complete classes:

| Actual native owner offset | Observed physical native value width | Independently witnessed original uses |
| --- | --- | --- |
| **+0x6E6** | 8-bit transition byte | FighterState::BeginNoticeTransition 0045D6A0 |
| **+0x6E7** | signed 8-bit notice index | FighterNoticePair::SetNoticeFields 0045CD70; BattleHud::DrawSelectedNotice 00440B00; FighterOverlay::RenderSideEffect 00454840 |
| **+0x6E8/+0x6E9** | two unsigned 8-bit notice fields | SetNoticeFields; +0x6E9 native render color in RenderSideEffect |
| **+0x6EA/+0x6EC** | two genuine signed 16-bit motion/extent fields | BeginNoticeTransition; RenderSideEffect |
| **+0x6EE** | 8-bit enable flag | ConfigureNoticeText 0045D650 |
| **+0x6F0/+0x6F2/+0x6F4/+0x6F6** | four adjacent 16-bit signed state fields | FighterState::InitializeNotice 0045CDC0 |
| **+0x6F6 (low byte)** | 8-bit rendering step | FighterNoticePair::RenderNotice 0045D5D0, two actual BYTE loads |

An essential native observation is the **overlapping,
not contradictory** access at +0x6F6: the initializer
stores a 16-bit word, while the renderer reads only
its *low byte*. Reinterpreting the renderer's actual
BYTE load as a signed short would change native x86
width, signedness and gameplay behavior.

The new [borrowed header](../src/FighterNoticeBorrowedF960.hpp)
declares only the actually observed, bounded windows:
three contiguous notice bytes at +0x6E7,
two signed shorts at +0x6EA, four shorts at +0x6F0,
and isolated byte views at +0x6E6, +0x6EE and
the original +0x6F6 low byte. All natural C++
struct sizes/offsets are compile-time constrained.
No class is allocated, embedded or claimed as a full
native historical fighter layout; unobserved bytes
(including +0x6EF) remain unknown.

Real source modifications use these actual borrowed
members in **three independently original-shaped game
translation units**:

- [GamePolicyHelpers.cpp](../src/GamePolicyHelpers.cpp):
  notice transition, enable byte, four short counters,
  and the *actual selected fighter pointer's* signed
  +0x6E7 notice field in BattleHud drawing.
- [FighterNoticeSetDrawF415.cpp](../src/FighterNoticeSetDrawF415.cpp):
  three distinct signed/unsigned 8-bit notice values
  and original 8-bit render step at +0x6F6.
- [FighterOverlayDrawingF163.cpp](../src/FighterOverlayDrawingF163.cpp):
  native signed notice, unsigned color byte,
  and two signed short motion/extent fields.

This does not alter original notice guard semantics,
actor selection, animation arguments, record ownership,
sprite color calculation or external call ABI.
No inert padding, fake locals, assembler or target
machine bytes were used.

## Complete canonical affected-source cold replay

Two pilot runs independently verified 3/3 and a
selected nested-BattleHud 1/1 exact original units.
All **14 independently accepted whole native functions**
across the three changed actual source objects were then
fresh-built serially under their own original per-unit
pinned VC7.1 compiler profiles. The canonical
comparison checked each **entire original callable
function CODE range and every original PE/COFF
relocation type, addend, symbol and destination**:

| Changed original source TU | Whole original units | Original CODE bytes |
| --- | ---: | ---: |
| GamePolicyHelpers.cpp | 9 | 652 B |
| FighterNoticeSetDrawF415.cpp | 2 | 188 B |
| FighterOverlayDrawingF163.cpp | 3 | 823 B |
| **Total** | **14/14 exact** | **1,663 B** |

Canonical cold receipt:

    Cold replay: 14/14 exact units across 3 objects

The complete affected-unit replay is reproducible with
`scripts/repo-python scripts/replay-exact-units.py`
and exactly the fourteen unit IDs whose `source`
field is one of these three changed files in
`config/match-units.toml`. The native compiler
and original PE receipt is retained in ignored
`.analysis/f960-notice-shared/all-14-cold.log`.

All **1,663 original bytes were ALREADY accepted exact**
before F960. These are source semantics/type improvements,
not newly accepted native CODE or whole functions;
the 979-unit corpus cold replay was NOT run.
