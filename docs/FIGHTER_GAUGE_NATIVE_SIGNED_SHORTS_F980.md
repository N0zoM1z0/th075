# F980 — Native five-short fighter gauge window, affected complete functions exact

The pinned Japanese TH075 v1.11 original executable independently
confirms five **signed 16-bit** fighter fields at contiguous offsets
+0x3B0, +0x3B2, +0x3B4, +0x3B6 and +0x3B8. Original instructions
use MOVSX WORD loads and native WORD writes. The source evidence comes
from **FighterEffectPolicies**, **FighterMoveScalarHelpers**,
**CombatTimers**, **FighterOpponentGauge** and the related original
**SelectHitResponse** function. This is evidence for the physical
contiguous word window, not an invented complete fighter class.

The [bounded borrowed field view](../src/FighterGaugeBorrowedF980.hpp)
has only these five signed 16-bit members, with compile-time actual
10-byte size and 2/4/6/8 member offsets. No full object is allocated,
copied, embedded, or assumed.

Four original translation units now use genuine typed window fields:
[effect gauge timer](../src/FighterEffectPolicies.cpp),
[nonnegative word setter](../src/FighterMoveScalarHelpers.cpp),
[1,696-byte native battle timer update](../src/CombatTimers.cpp),
and [opponent gauge adjustment](../src/FighterOpponentGaugeF170.cpp).
These preserve real signed comparisons, postfix/gauge updates, short
loads/writes and the original opponent-receiver pointer.

## Exact symbol-identity sensitivity discovered and preserved

The 944-byte native [SelectHitResponse](../src/FighterHitResponseF164.cpp)
also reads the same original signed 0x3B0 word, but replacing its three
raw signed-short expressions by the new bounded view changed the
**VC7.1 local COFF $L-label symbol numbers** despite unchanged
physical code and external field locations. The strict canonical
manifest requires the genuine original **symbol identity**, not merely
matching values or structural-exact relocation masking. Moving the
new include after standard headers did not restore the original labels.
Rather than weakening the exact checker or accepting a regression, that
single function was returned to its already-proven native source grammar.
A fresh standalone 944-B cold replay confirmed original exactness.

The native value-category negative and build evidence are retained
under ignored .analysis/f980-fighter-gauge/. Four other source objects
were not discarded: their natural typed changes were kept, cold-built
and checked. The complete final affected/cohort regression cold replay
was restricted to **13 entire accepted original callable functions
across 5 source objects**, including SelectHitResponse as a control:

| Full original source object | Whole functions | Native original CODE |
| --- | ---: | ---: |
| FighterEffectPolicies.cpp | 6 | 449 B |
| FighterMoveScalarHelpers.cpp | 2 | 72 B |
| FighterHitResponseF164.cpp (unchanged exact control) | 3 | 1,061 B |
| CombatTimers.cpp | 1 | 1,696 B |
| FighterOpponentGaugeF170.cpp | 1 | 753 B |
| **Total** | **13/13 exact** | **4,031 B** |

The canonical final receipt reads:

    Cold replay: 13/13 exact units across 5 objects

All individual original CODE bytes, PE/COFF relocation offsets,
types/addends, actual original symbol names and destination addresses
match. This is **4,031 B of previously accepted whole native CODE**;
source reconstruction semantics improved, but **zero new accepted CODE
coverage**. The 979-unit corpus-wide replay was not run.
