# F943 — Third original 82KB fighter's true 0x62 transition selector

The pinned Japanese TH075 v1.11 original giant **004AC040**
is **82,796 complete callable original CODE B/22,721 x86**,
with separate **1,126 afterRET jump-table DATA B**. The
current normal VC7.1 C++ partial father still has numerous
placeholder game actions and an incorrect saved-`this` EBP
slot. **The original complete father is NONEXACT.**

The real original state `0x62` is
**004AE7E2..004AE839**, **87 B /25 native x86**,
with exactly four genuine original typed game-call PE fields:
one action getter at **0040FA30** and three action setters
at **0040FAC0**. This native state is NOT equivalent to the
different 58KB/46KB fighter originals' larger
resource-selection `0x62` handlers.

The independently read original x86 shows the actual
game semantics: on native animation completion
`GetNativeActionAt40FA30()==S16(0x70)`,
transition to action **0x5F**, then if the genuine
signed-short `this+0xF00` selector equals **1**
transition to **0x5D**, and if it equals **2**
transition to **0x5E**. These true branch values
come from native original positional pushes and
CMP immediates, not old source guesses.

New tracked ordinary C++:
[`probes/FighterThirdBossSelector62F943.inc`](../probes/FighterThirdBossSelector62F943.inc).
The [targeted F943 verifier](../scripts/verify-third-fighter-selector-f943.py)
rebuilds **two entire original-shaped normal VC7.1
partial giant parents**: old 0x62 marker and new
genuine selector. The original PE physical
case-index-to-DIR32-label map anchors both sources
rather than assuming a partial stub's instruction ordinal.

| Whole partial parent | Previous marker | F943 |
| --- | ---: | ---: |
| Emitted complete source CODE B | 18,161 | **18,234** |
| Emitted source x86 | 4,832 | **4,855** |
| Real original 0x62 source extent | 15 B/2 x86 | **87 B/25 x86** |
| 0x62 original positional mnemonic and width errors | Not aligned | **0/0** |
| 0x62 original source PE external fields resolved | Stub | **4/4** |
| Original afterRET DATA, local labels, nonfield bytes | 1,126/151/522 | **1,126/151/522** |
| Entire 82KB original callable function exact | NO | **NO** |

The verifier also independently checks all earlier
real 0x58,0x59,0x5D,0x5E,0x5F,0x60,0x61 original
physical action extents, original typed external
PE targets and x86 geometry on the SAME new source,
not cropped into seven fake independent callable
functions. The newly recovered 0x62's GPR roles
and the partial father's receiver EBP−0x10 versus
native EBP−0x64 still differ. Neither four
verified original external PE targets nor a native
87-byte case length constitutes a byte-exact
82KB whole function.

Reproduce with only the two affected partial
original-shaped giant whole C++ compiles:

    scripts/repo-python scripts/verify-third-fighter-selector-f943.py

Machine-local ignored C++/OBJ/PDB and native PE
receipts live under
`.analysis/f943-third-original-selector/`.
No 979-unit cold replay, no new accepted original
whole callable CODE bytes.
