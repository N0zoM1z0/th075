# F999 — True native current/recoverable health short pair, 47 whole functions exact

The pinned original Japanese TH075 v1.11 executable independently
uses signed **16-bit WORD** fields at fighter **+0x324**
(current health) and adjacent **+0x326** (recoverable health).
Fresh x86 disassembly of five separate complete original functions
confirms actual original MOVSX WORD loads, signed WORD writes and
the independent native storage locations. No historical report alone
was used to assign types.

The new [bounded borrowed native view](../src/FighterVitalBorrowedF999.hpp)
contains only these two signed shorts, compile-time sizeof=4 and
offset=2. It never allocates, embeds or claims a complete historical
fighter object. Actual owner pointers are retained in five original
source translation units, preserving the exact native receiver,
lvalue mutation and integer signedness:

[Opponent gauge update](../src/FighterOpponentGaugeF170.cpp),
[knockout resolution](../src/KnockoutProgressF172.cpp),
[round-end HUD](../src/RoundEndHudF173.cpp),
[full frame counters](../src/CombatTimers.cpp), and
[character virtual actions](../src/FighterVirtualActionsF159.cpp).

**Two levels of canonical cold verification** were run using
the pinned VC7.1 compiler and original full-function PE/COFF
manifest. The pilot tested five substantial, independently sourced
complete original functions: 753B, 1,150B, 599B, 1,696B
and 1,151B; all **5/5 exact**. The final canonical replay
then rebuilt **every accepted original callable unit** in the
five touched source objects, including the small leaf functions.

| Modified original source object | Original whole exact units | Already accepted CODE B |
| --- | ---: | ---: |
| FighterOpponentGaugeF170.cpp | 1 | 753 |
| KnockoutProgressF172.cpp | 5 | 1,356 |
| RoundEndHudF173.cpp | 4 | 878 |
| CombatTimers.cpp | 1 | 1,696 |
| FighterVirtualActionsF159.cpp | 36 | 1,957 |
| **Entire affected cohort** | **47/47 exact** | **6,640 B** |

Canonical transcript:

    Cold replay: 47/47 exact units across 5 objects

The comparison includes the **entire native original CODE** for
each function and all original typed PE/COFF relocation offsets,
symbols and targets, including C++ compiler-local labels where
applicable. Original target metadata comes from
config/match-units.toml; no new exact manifest units or
relocation masking were introduced. The private receipts are
under .analysis/f999-fighter-vital/five-pilot.log and
.analysis/f999-fighter-vital/all-affected-cold.log.

**All 6,640 CODE bytes were ALREADY accepted exact.**
This is a better-grounded native source type/ownership
reconstruction, not a new accepted full-function coverage
increase. No 979-unit cold replay was run.
