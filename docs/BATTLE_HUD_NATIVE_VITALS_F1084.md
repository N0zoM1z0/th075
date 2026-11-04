# F1084 — Real two-fighter health/recoverable WORDs in the complete 9,841B Battle HUD

The pinned Japanese TH075 1.11 original has one independently
accepted **9,841 original CODE B** `BattleHud43E040::RenderHud`
complete callable at `0043E040`. Its actual game logic renders
both players' health bars, counter banners, attack/detail stats,
mode-specific hit counts and several texture atlas passes, using
real `RECT` and float drawing geometry. It was already whole-function
byte-exact before this work; F1084 is a genuine source field/layout
improvement **preserving** that exactness.

Native original fighter+`0x324` is a signed 16-bit *current health*,
and the adjacent fighter+`0x326` is a signed 16-bit *recoverable
health* field. This relationship is independently established by
five other previously exact complete native source objects.
The original F1084 HUD source previously used many unrelated
`LEFT(short, 0x324/326)` and `RIGHT(short, 0x324/326)` casts,
obscuring the fact that each actor's two health words form a
single real native 4-byte borrowed window.

The selected normal C++ now reuses the independently verified narrow
[`FighterVitalBorrowedF999`](../src/FighterVitalBorrowedF999.hpp)
physical view on the original owner pointers at HUD+`0x44` (left
fighter) and HUD+`0x48` (right fighter):

| Original native field readings | Typed source now | Total uses |
| --- | --- | ---: |
| Left fighter+`0x324` | `F999_VITAL(left).currentAt324` | **4** |
| Left fighter+`0x326` | `F999_VITAL(left).recoverableAt326` | **4** |
| Right fighter+`0x324` | `F999_VITAL(right).currentAt324` | **10** |
| Right fighter+`0x326` | `F999_VITAL(right).recoverableAt326` | **6** |
| **24 distinct real native WORD reads** | **one existing physical type** | **24** |

These are **borrowed original scalar windows**, not a new
complete class layout, synthetic heap owner, function call or
unproven HUD prefix. Every original gauge numerator, signed
arithmetic, mode switch, x87 float argument, original looping
index and sprite submission remains in the exact same natural
C++ gameplay order. The adjacent +0x324/+0x326 field semantics
are not guessed from stale prior experiments.

## Strict original complete-callable cold proof

The one affected original-shaped `src/BattleHud43E040.cpp`
translation unit was actually cold-built under pinned VC7.1
`/Od /Ob0 /Gy /GR- /GX- /GS /Zi`, and the **ENTIRE 9,841B
original game callable** was compared against the SHA-pinned
Japanese PE with exact native machine bytes, full original
function boundaries and real COFF physical call/global fields:

    scripts/repo-python scripts/replay-exact-units.py \
        --unit battle-hud-render-0043e040

**Result: 1/1 complete whole original function exact, 9,841/9,841
CODE B retained.** This is not a cropped gauge expression test.
The original bytes were already accepted as exact; no new authored
CODE byte or whole callable was credited, and no global 979-unit
cold replay, target PE mutation or relaxed source-symbol rule
was used. The unchanged baseline C++ source and local compiler
receipts are under ignored `.analysis/f1084-hud-native-vitals/`.
