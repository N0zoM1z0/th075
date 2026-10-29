# F566: integrate eleven real game-action C++ cases in the scripted fighter giant

**Original whole-function evidence and one new natural VC7.1 compilation,
not complete-function exactness.** Original Japanese TH075 1.11 SHA256
bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98.

F565 recovered distinct 96/83/83-instruction scripted-state cases
inside original 005214B0 (46,755 CODE bytes). F566 builds the further
source-integration experiment: **one newly compiled ordinary C++
Advance() function with eleven actual native game-action cases
0 through 10**. The source is regenerated from the pinned original PE
and tracked F545/F565/F547/F549 helpers, not stitched from previously
compiled object-code snippets. Other still-unreconstructed actions
remain explicitly diagnostic marker stores.

## Original-specific control and composition

The action6/7/8 real state logic remains separate from the
frame-advance actor families: signed stage >2 gates x87 collision;
native 0040FB40(5) and 0040FB40(11) appear in action6,
native 0040FAC0(9) in action7 and 0040FB40(13) in action8.
Their original conditional position/velocity/speed stores are
(0/16/0.8), (+5.5/16/0.8) and (-5.5/16/0.8) with native
FLAG clear. Cases0-5 retain their individually original-verified
reset/x87/control behavior, action9 has the authentic early return
and action10 the genuine 20-instruction native state transition,
without a fabricated initial-frame call.

The reproducer explicitly verifies the original **entire 46,755-byte
fighter CODE SHA256**, the *actual* first-table physical DWORD entries,
the independently JE-guarded action0x32 singleton bounding case10, and
all native post-RET jump DATA before source acceptance. All original
source ABI and method names remain provisional.

## New single-TU VC7.1 native/COFF evidence

[The tracked F566 integrated native source verifier](../scripts/verify-fighter-integrated-scripted-switch.py)
freshly compiles only one affected ordinary C++ TU with pinned VC7.1
/Od /Ob0 /Gy /GR- /GX- /GS /Zi. Each entire native case and its
corresponding compiled code must agree in instruction count and
length, actual per-fighter register/x87/branch grammar, and individual
real call/global typed physical COFF field identity.

| Original action | Complete native x86 instructions | Original internal CODE bytes |
| --- | ---: | ---: |
| 0 | 50 | 180 |
| 1 | 60 | 212 |
| 2 | 50 | 180 |
| 3 | 60 | 212 |
| 4 | 3 | 15 |
| 5 | 3 | 15 |
| 6 | 96 | 331 |
| 7 | 83 | 290 |
| 8 | 83 | 290 |
| 9 | 42 | 144 |
| 10 | 20 | 69 |

All **11/11 complete original internal cases** reproduce **550/550
genuine original x86 instruction/size/register/x87/branch roles**,
covering 1,938 real native *internal* CODE bytes, and **73/73 actual
per-case typed physical COFF call/global relocation fields**.
The candidate also preserves all **139 actual native-style physical
DWORD jump COFF fields**, repeated/default handler partitions,
**345/345 byte-identical original sparse index bytes**, and the full
**901-byte after-RET DATA-shape**. These original DATA bytes are
not CODE. The whole source candidate remains much shorter than the
46,755-byte native original because other game actions are not yet
reconstructed; no whole-function exactness is asserted.

### Reproduce with one affected TU, never the full cold replay

    scripts/repo-python scripts/verify-target.py
    scripts/repo-python scripts/verify-fighter-boss-family.py
    scripts/repo-python scripts/verify-fighter-integrated-scripted-switch.py

The source/COFF/PDB and JSON summary reside in ignored
.analysis/f566-integrated-scripted-source/; initial native/C++
exploration in .analysis/f566-scripted-integrated/.
No original byte grafting, fabricated stack frame, cropped
subfunction exact credit, full all-unit cold replay or external
Factory/Oracle receipt.
