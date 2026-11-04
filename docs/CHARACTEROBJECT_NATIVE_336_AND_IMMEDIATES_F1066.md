# F1066 — Real 0x336 eight-shot action restores GPR phase and corrects the 0x334 float parameter

**Historical F1066 checkpoint:** the live parent now additionally recovers the real [F1068 960B action 0x330](CHARACTEROBJECT_NATIVE_330_LIVE_PROOF_F1068.md). Use its full-current-parent PE verifier for latest source geometry and all 30 game states. The 29-state/17,809B source figures below describe the earlier valid F1066 bounded proof, not current dimensions.

The pinned Japanese TH075 1.11 original has **one** independently
original `CharacterObject::Advance` callable at `0050A580`,
**81,539 original CODE B /17,435 x86**, with separate authentic
567B afterRET sparse switch DATA. The currently selected natural C++
parent remains **NONEXACT**; original switch interiors do not count
as independent complete original callables or new exact CODE credit.

## Recheck the original, do not assume three similar native cases are identical

Earlier F1065 recovered two genuine original actions with **249/249
native mnemonics and GPR roles each**. Comparing only mnemonic/GPR and
physical external PE targets had missed an important fact: the real
original x86 instruction at **ordinal 105** of their authentic action
bodies pushes a different 32-bit float bit-pattern. The original PE
requires three genuinely distinct native motion input values:

| Separate original state | Physical original PE interval | Native x86 #105 | True C++ float input |
| --- | --- | --- | --- |
| `0x333` | `0050D929..0050DDCF` (1,190B) | `push 0x41F00000` | **+30.0f** |
| `0x334` | `0050DDCF..0050E274` (1,189B) | `push 0` | **0.0f** |
| `0x336` | `0050E518..0050E9C0` (1,192B) | `push 0xC1F00000` | **−30.0f** |

The formerly used +30.0f for 0x334 was *semantically incorrect*
despite having the same x86 mnemonic stream and physically matched
14 external COFF fields. F1066 explicitly corrects it to original
0.0f and restores authentic state `0x336` from a previous synthetic
marker. Each real state still has a distinct native switch target
and emits the original eight-shot `0x3E4` loop, the actual parent
`+0xEFA`/`0x3E3` projectile behavior, native scale/opacity and
animation control, and genuine motion/angle, combat status, actor
move and action-completion calls.

In ordinary pinned VC7.1 `/Od` the zero-float source emits the actual
`push 0` and is **three bytes shorter** than the earlier incorrect
+30.0f source case. This is not a byte patch or synthetic codegen
hack: the real original floating argument is represented as real
C++ gameplay. The selected `CharacterObjectBoss333334F1065.inc`
now uses one original gameplay grammar with three truly independent
switch cases and their **genuinely different float expression
parameters**.

## Entire original game and native physical PE target verification

The tracked `verify-characterobject-native-333334-f1065.py` now checks
**all three** real cases against the independently verified original
Japanese PE. It SHA-verifies the actual **entire 81KB original CODE**
and 567B original afterRET DATA, compares all **92 physical original
DIR32 case-label equality partitions** and **199 sparse-index bytes**,
then performs full original x86 ordinal and register-role comparisons
against the three complete codegen case interiors. It checks the
actual **ordinal-105 native/source immediate for +30, zero and −30**;
not merely original call names or source-level equivalence.

Every real original nonlocal COFF field is resolved by original x86
ordinal, actual *original PE physical field-byte address*, typed
REL32/DIR32 native decoder and PE-derived destination. The source
`AtXXXXXXXX` symbol is checked against that independently measured
original target. No relocation mask suppresses differences.

| Real native state | Native CODE/x86 | Source inner CODE/x86 | Ordered mnemonic/GPR | Real native PE fields | Native widths matching |
| --- | ---: | ---: | ---: | ---: | ---: |
| `0x333` | 1,190B /249 | 943B /249 | **249/249 each** | **14/14** | 167/249 |
| `0x334` | 1,189B /249 | 942B /249 | **249/249 each** | **14/14** | **167/249** |
| `0x336` | 1,192B /249 | 945B /249 | **249/249 each** | **14/14** | 167/249 |
| **Three real game states** | **3,571B /747** | 2,830B /747 | **747/747 each** | **42/42** | 501/747 |

These are real game state interiors inside ONE large original
callable, not independently accepted original machine functions.
The full original native source frame remains `ESP 0x3A0` and saved
receiver `EBP-0xAC`; the still-incomplete C++ whole-parent source
emits `ESP 0xE8` with saved receiver `EBP-0x48` and has many missing
states, original stack widths and relative branch distances.

## Actual cross-state source register lifetime

F1065 (correctly) restored `0x335` native GPR from 57/149 to
149/149 when `0x333`/`0x334` became genuine gameplay. However,
while the adjacent `0x336` remained a fake marker, the later original
`0x337` GPR matched only **13/35**, `0x338` **56/175**, and `0x339`
and longer states also regressed. The real `0x336` action and its
actual negative motion init now restore **all** previously recovered
following original state GPR allocation without forced register
variables or fake lifetimes, including `0x337` **35/35**, `0x338`
**175/175**, `0x339` **101/101**, `0x33A` **168/168**, the five
402-instruction long action families **402/402 each**, all five
fade cases **57/57 each** and `0x345` **35/35**.

**Current C++ selected partial parent:** **17,809 generated CODE B /
4,651 x86**, plus 567 real afterRET DATA B. The original remains
81,539 CODE B/17,435 x86. Across **29 genuine source-recovered
original state intervals** the independent original-code ranges
contain **21,001 native original CODE B /4,481 native x86**, with
**4,481/4,481 matching ordered mnemonics and GPR roles** and
**346/346 physically original PE call/global fields**. The normal
source's corresponding current inner case CODE totals **16,721B**;
it does not claim original byte exactness and cannot be promoted to
new accepted authored coverage. Other real game actions remain
marker-only in this partial source.

Reproduce ONLY affected original-shaped game sources, not 979 cold units:

    scripts/repo-python scripts/verify-characterobject-native-333334-f1065.py
    scripts/repo-python scripts/verify-characterobject-native-335-f1064.py
    scripts/repo-python scripts/verify-characterobject-native-338-339-f1062.py
    scripts/repo-python scripts/verify-characterobject-five-long-actions-f1057.py

All genuine C++/OBJ/PDB/compiler/PE receipts are under ignored
`.analysis/f1065-original-333334-proof/` and
`.analysis/f1066-object336/`. No target mutation, register forcing,
original case splitting, mass cold replay or exact-claim masking.
