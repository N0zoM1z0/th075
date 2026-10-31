# F1024 — Native animation stage/frame WORDs; nine exact originals retained

The SHA-pinned Japanese TH075 v1.11 original physically uses
two adjacent signed 16-bit actor animation counters:
**stage at owner+0x62** and **frame at owner+0x64**.
Nine independently accepted complete native callable functions
were disassembled to confirm physical WORD/MOVSX accesses at
the actual offsets. The native-owner pointer is different
in effect and fighter functions; no full actor layout is inferred.

The [new four-byte borrowed subobject](../src/FighterAnimationPhaseBorrowedF1024.hpp)
contains exactly the two signed shorts, with compile-time
size=4 and frame offset=2 checks. Source now borrows these
real fields for the current actor, the separate fighter
owner referenced by auxiliary actors at +0xE4, and
spawned effect children reached through original
ITEMS->back() calls. C++ call order and signed reads,
WORD writes, and real zero initialization are unchanged.

## Canonical affected-unit native cold replay

An initial pilot compared the giant auxiliary state
handler, animation progression, auxiliary actor, projectile
advance and effect creation. Four of five complete
originals were cold exact. The separately authored
31,352B CharacterAuxAction::AdvanceActionAt005FAE30
failed STRICT ORIGINAL COFF identity, despite unchanged
native machine instructions. It was immediately restored
to the exact previously accepted source; no incomplete
or known-nonexact change was retained.

The actual failure was independently isolated with
FOUR ordinary complete VC7.1 31KB C++ controls:

| Full 31,352B source grammar | Physical original 27,980/27,980 nonrelocation CODE bytes | Incorrect COFF field symbols |
| --- | --- | ---: |
| Existing accepted source | **yes** | **0** |
| Existing source with only new header included | **yes** | **72**; local labels +21 |
| Typed borrowed phase struct defined inline, no header | **yes** | **72**; local labels +9 |
| Original primitive pointer expression, no new struct/header | **yes** | **0** |

This proves that neither a byte-level comparison alone
nor a nominal four-byte type is sufficient to preserve
the VC7.1 compiler-local COFF labels of the 31KB function.
Its original source file is unmodified in the committed
result. This is a real strict exactness constraint, not
a reason to mask labels, relax relocation manifests or
double-credit game CODE.

The other EIGHT changed source objects all passed
native full-function strict PE/COFF cold replay:

| Final changed original compilation unit | Full exact native callable units | PREVIOUSLY credited CODE B |
| --- | ---: | ---: |
| ActorAuxiliary.cpp | **2** | **6,935** |
| AnimationProgress40FA30.cpp | **1** | **142** |
| CharacterAux004C49C0F371.cpp | **1** | **1,757** |
| CharacterProjectileAdvanceF379.cpp | **1** | **855** |
| EffectChildCtorF283.cpp | **1** | **116** |
| EffectSpawnF281.cpp | **1** | **602** |
| EffectSpawnF285.cpp | **1** | **487** |
| YukariSpecialStateF345.cpp | **1** | **679** |
| **All final changed source objects** | **9/9** | **11,573** |

Canonical final receipt:

    Cold replay: 9/9 exact units across 8 objects

Original reference and cold replay receipts, exact
giant CODE field masks and the four complete compiler
controls remain in ignored
.analysis/f1024-native-animation-pair/.

**Zero additional accepted game CODE bytes/functions;
11,573 already-accepted bytes remain strict exact.
No corpus-wide 979-unit cold replay.**
