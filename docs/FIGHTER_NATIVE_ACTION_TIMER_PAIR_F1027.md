# F1027 — Original action WORD pair +0x80/+0x82, 46/46 full cold exact

The SHA-pinned Japanese TH075 v1.11 original executable
independently uses adjacent actor-relative **signed 16-bit
WORD fields at +0x80 and +0x82**. The first is an
action-associated word used in collision countdown and
character state; the second is a separate state/cooldown
timer used by render, frame counter, and damage state.
Original native MOV/MOVSX WORD instructions and receiver
offsets confirm both fields in multiple complete
already accepted game functions.

The [new four-byte borrowed pair](../src/FighterActionTimerPairF1027.hpp)
contains only two signed shorts, with compile-time
size=4 and second offset=2 checks. It does NOT instantiate
or assert a complete original fighter object layout.
It is now used in the real target owner objects across
[BattleDefaults](../src/BattleDefaultsF300.cpp),
[BattleCollision](../src/BattleCollision.cpp),
[FighterVirtualActions](../src/FighterVirtualActionsF159.cpp),
[ActorEffectDrawing](../src/ActorEffectDrawing.cpp),
[CharacterAux005301B0](../src/CharacterAux005301B0F378.cpp)
and [CombatTimers](../src/CombatTimers.cpp).

## Preserve original strict COFF identity

An eight-object pilot found **6/8 full game callables
cold exact**. The two affected large files
BattleCombat and BattleCombatResponses were not
accepted with the type header. The pinned original
physical x86 relocation offsets and call/global
destinations did not move, but MSVC7.1 renumbered
compiler-local $L labels by **+21**. For the
1,982B native ApplyHit, 5 of 66 strict COFF
field identities changed; for the 1,185B original
ApplyHitResponse, 11 of 34 changed.

These two entire original translation units were
restored to their previously accepted source,
not silently excluded, and no loose COFF-identifier
comparison was substituted. All real source edits
in the resulting six files underwent COMPLETE
affected-unit normal pinned VC7.1 cold replay:

| Actual modified original source group | Exact original whole units | Previously accepted original CODE B |
| --- | ---: | ---: |
| BattleCollision.cpp | 5 | 855 |
| BattleDefaultsF300.cpp | 1 | 203 |
| FighterVirtualActionsF159.cpp | 36 | 1,957 |
| ActorEffectDrawing.cpp | 2 | 4,543 |
| CharacterAux005301B0F378.cpp | 1 | 1,008 |
| CombatTimers.cpp | 1 | 1,696 |
| **All six real modified source objects** | **46/46** | **10,262 B** |

Canonical complete native receipt:

    Cold replay: 46/46 exact units across 6 objects

This retains every native game callable byte, original
PE/COFF field, caller register role, and compiler-local
symbol identity for all six changed source translation
units, not merely semantic C++ equivalence.

The independent original WORD access audit, pilot,
strict two-failure COFF diagnostic and complete affected
cold replay are in ignored
.analysis/f1027-native-action-timer/.

**No new accepted exact original CODE B/functions;
10,262 B were already credited. No mass 979-unit replay.**
