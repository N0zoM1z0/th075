# F1006 — Original combo-count/damage short pair, 42 whole native callables exact

The SHA-pinned Japanese TH075 v1.11 original executable
independently shows adjacent **signed 16-bit WORD** fields
at fighter **+0x3C4** (combo count) and **+0x3C6** (combo
damage). Original physical x86 from complete native
BattleActiveCollision, BattleCombat, BattleCombatResponses,
FighterOpponentGauge and FighterResetRound functions
shows real WORD loads/stores and signed MOVSX uses.
These are not presumed from prior reports or invented
complete object layouts.

The [new borrowed four-byte window](../src/FighterComboBorrowedF1006.hpp)
contains only two signed shorts, compile-time sizeof=4
and second offset=2; no full original fighter type is
instantiated or embedded. It is now used in
[BattleActiveCollision](../src/BattleActiveCollision.cpp),
[FighterOpponentGaugeF170](../src/FighterOpponentGaugeF170.cpp)
and [FighterVirtualActionsF159](../src/FighterVirtualActionsF159.cpp).
Existing owner lvalues, native signed comparisons, COFF/PE
relocations and full original callable geometry are preserved.

## Native compiler-local COFF symbol preservation, not masked differences

A five-object trial also typed BattleCombat and
BattleCombatResponses, initially cold-replaying five
large representative original functions: **4/5 exact**.
The full affected 47-unit cold replay showed **45/47**,
with two additional unrelated original functions failing
despite exact machine bytes/relocation locations.

The independent original COFF check demonstrated these
specific failures:
- BattleCombat::ApplyHit, original 1,982B: five physical
  COFF fields retained offsets and types, but compiler
  local symbol identities were shifted (e.g. original
  $L1155 became $L1176).
- BattleCombatResponses::ApplyHitResponse, original
  1,185B, and ApplyReactionMode, original 230B:
  same strict internal $L symbol shift of **+21**.
  The actual attack/guard hit functions remained exact.

The original already accepted source grammar was restored
for both whole BattleCombat and BattleCombatResponses TUs.
The restored entire objects passed independent normal
VC7.1 canonical cold replay **4/4 and 5/5 exact**.
No accepted units, original target metadata, or physical
relocation identities were relaxed or changed.

Then every original callable unit in the three ACTUALLY
modified source translation units was cold-built under
the canonical pinned VC7.1 original comparator:

| Final changed original source object | Complete native exact units | Previously credited original CODE B |
| --- | ---: | ---: |
| BattleActiveCollision.cpp | 5 | 2,045 |
| FighterOpponentGaugeF170.cpp | 1 | 753 |
| FighterVirtualActionsF159.cpp | 36 | 1,957 |
| **All affected final source objects** | **42/42 exact** | **4,755 B** |

Canonical final receipts:

    Cold replay: 42/42 exact units across 3 objects
    Cold replay: 4/4 exact units across 1 objects
    Cold replay: 5/5 exact units across 1 objects

Native PE/COFF diagnostics, the five-source pilot,
the controlled failed 47-unit attempt, two restored
large-object controls and the final affected 42-unit
cold replay are retained under ignored
.analysis/f1006-combo-native/.

The **4,755 native CODE bytes were ALREADY accepted**,
so F1006 improves real fighter field ownership and
source typing without double-counting exact coverage.
**No new entire original callable CODE was credited.
No corpus-wide 979-unit replay was run.**
