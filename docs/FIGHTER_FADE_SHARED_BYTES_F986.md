# F986 — Real native fade bytes shared across five original source objects

The SHA-pinned Japanese TH075 v1.11 executable contains independently
observed original fighter **unsigned BYTE** fields **+0x538 and +0x539**.
Five separate original compiled translation units confirm the actual
physical field widths and the 2-byte adjacency: fade initialization
sets 0x538=0xF0, 0x539=mode; per-frame counters subtract 3 from
0x538 while positive; original renderer uses both bytes in sprite
position and texture mode; BattleRender reads +0x538 from two original
actor pointers before invoking the fade overlay; FighterBaseActions
resets 0x538 at round start.

The [two-byte borrowed native view](../src/FighterFadeBorrowedF986.hpp)
defines only the genuine unsigned byte fields and strictly constrains
its C++ sizeof=2, second offset=1. It is not a complete historical
fighter object, is never embedded or allocated, and does not infer
unobserved state.

Five actual source translation units now use this borrowed member
view: [small fade setter](../src/FighterMoveScalarHelpers.cpp),
[1,696-B original frame counter](../src/CombatTimers.cpp),
[effect drawing](../src/FighterOverlayDrawingF163.cpp),
[1,637-B full battle renderer](../src/BattleRender43D9D0.cpp),
and [original fighter round reset](../src/FighterVirtualActionsF159.cpp).
They preserve original signedness, receiver ownership, argument/call
order and all native PE/COFF relocation field identities; nothing
is inserted to force the compiler.

## Complete original affected-unit cold validation

The first canonical replay built five representative ENTIRE original
functions, including both large render/counter functions, and reported
**5/5 exact**. Then the canonical per-unit replay was run ONLY on
ALL exact manifest units whose source object is one of the five changed
translation units. The locked VC7.1 compiler built each changed source
object serially and checked each WHOLE original callable CODE range,
including **all original PE/COFF typed relocation offsets, symbols,
addends and destinations**.

| Real original source object | Whole exact units | Original CODE B |
| --- | ---: | ---: |
| BattleRender43D9D0.cpp | 1 | 1,637 |
| CombatTimers.cpp | 1 | 1,696 |
| FighterMoveScalarHelpers.cpp | 2 | 72 |
| FighterOverlayDrawingF163.cpp | 3 | 823 |
| FighterVirtualActionsF159.cpp | 36 | 1,957 |
| **All affected original source objects** | **43/43** | **6,185** |

Canonical local transcript:

    Cold replay: 43/43 exact units across 5 objects

The full targeted native receipt is retained in ignored
.analysis/f986-fade-native/full-affected-cold.log. Unit IDs come
directly from the five source entries in config/match-units.toml,
not from a duplicated hardcoded mini-ledger.

All **6,185 original CODE bytes were already accepted exact** before
this work. F986 improves real source field consistency and independent
native actor ownership; **zero new original CODE was credited**.
No all-979-unit cold replay was run.
