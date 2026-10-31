# F992 — Signed/unsigned original result byte and adjacent native continuation flag

In the SHA-pinned Japanese TH075 v1.11 original executable,
fighter **+0x3CE** is physically one byte. Full original battle
combat and battle state code read it with a **signed char**,
while original knockout/round reset writes use **unsigned BYTE**
accesses to the same address. Adjacent **+0x3CF** is an
independently accessed unsigned byte; it must NOT be conflated
with the signed state test at +0x3CE.

The new [bounded two-byte borrowed view](../src/FighterRoundOutcomeBytesF992.hpp)
provides a signed/unsigned union for real +0x3CE and one
unsigned continuation field for +0x3CF, with compiler-checked
2-byte size and 1-byte relative field offset. It is NOT a
complete fighter class or allocated game object; no unknown
actor fields or guessed padding were reconstructed.

The view is now shared across THREE exact original C++
source objects:
[KnockoutProgressF172](../src/KnockoutProgressF172.cpp),
[RoundEndHudF173](../src/RoundEndHudF173.cpp), and
[FighterVirtualActionsF159](../src/FighterVirtualActionsF159.cpp).
Their actual original signedness, byte writes, receiver
ownership and native operation order remain intact.

## Original COFF $L symbol identity negatives and exact preservation

An initial six-source-object normal VC7.1 pilot attempted
the same type view in three additional large original
functions: BattleCombat::ApplyHit (1,982 B),
BattleCombatResponses::ApplyHitResponse (1,185 B)
and BattleFrame::AdvanceState (4,764 B).
Their compiled PE relocations retained the same offsets,
types and external targets, but **internal compiler $L
symbol identities changed** by +30 or +27, so the
canonical strict exact checker correctly rejected all
three. Comparison logs under ignored
`.analysis/f992-original-round-outcome/failures/`
prove the real reason; these are NOT exact.

The three whole large functions were returned to their
already accepted original raw signed-byte C++ grammar,
without changing their natural game logic, and cold
replayed independently:

    Cold replay: 3/3 exact units across 3 objects

The shared view was retained only in the three
independently verified safe source objects, then
**every originally accepted callable function whose
source belongs to those three modified objects**
was cold-built using the canonical pinned VC7.1
compiler and compared with original full native
CODE, COFF field offsets/types/symbol identities
and PE targets.

| Final modified original source object | Whole native exact units | Already accepted native CODE B |
| --- | ---: | ---: |
| FighterVirtualActionsF159.cpp | 36 | 1,957 |
| KnockoutProgressF172.cpp | 5 | 1,356 |
| RoundEndHudF173.cpp | 4 | 878 |
| **Total** | **45/45 exact** | **4,191 B** |

The final canonical targeted receipt states:

    Cold replay: 45/45 exact units across 3 objects

Its transcript lives in ignored
`.analysis/f992-original-round-outcome/affected-45-cold.log`.
The original three large source-control replays are in
`restored-three-controls.log`. No exact manifest entries
were changed, and zero formerly accepted native bytes
were lost.

**All 4,191 B were already exact/accepted before this
source type improvement. No new credited original game
CODE or callable functions. No all-979-unit cold replay.**
