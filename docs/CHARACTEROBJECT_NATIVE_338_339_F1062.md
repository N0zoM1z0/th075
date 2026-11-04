# F1061/F1062 — Native 13-shot `0x338` and 101-x86 `0x339` restore their adjacent Boss GPR cycle

The independently original Japanese TH075 1.11 game has **one**
81,539 original CODE B /17,435-x86 `CharacterObject::Advance` callable
at `0050A580`, with 567 separate afterRET sparse-switch DATA bytes.
It is still **NONEXACT**. This work reconstructs **two genuine missing
interior game states**, not separate callable functions, from the
actual original SHA-pinned PE.

## Real original gameplay and physical intervals

- **Action `0x338`**: original `0050EA5B..0050ED70`, **789 native
  CODE B /175 x86**. If the real parent action lies in (0x45,0x96),
  call the authentic `0045B830` and execute a genuine **13-shot
  `0x3E4` loop** through actual parent `00453A70`, plus conditional
  parent +0xEFA reset and `0x3E3` projectile. Independently reject
  true parent action `0x25C` at parent stage 0. On native own
  animation stage/frame (0,0), reset native motion, both float scales,
  four opacity bytes, action-state and timer WORDs. On stage 1,
  advance both scales with genuine game float `006583F8`. At stage
  2/frame 0, spawn authentic action `0x337`. The real `0040FA30`
  action completion increments the +0xD8 retry count if below 5 with
  positive +0x80, uses real `0040FB40(2)` and conditionally exits,
  else calls `0045B830`. A second stage 2/frame 0 condition uses the
  real parent `00453D40(8)`.
- **Action `0x339`**: original `0050ED70..0050EF5F`, **495 native
  CODE B /101 x86**. Its stage-zero animation initializes real
  motion, X/Y scale `0.5f`, opacity and the action-associated WORD
  `0x4E2`, sets true float +0x28 to `-30.0f`, computes signed-facing
  +0x2C at `-45` times facing, and clears the +0xD8 timer. It then
  applies the real two-axis float expression using native constants
  `0065972C`, `006583FC`, `00658354`, signed short +0xD8 and its
  genuine `(timer < 10)` integer mask. That produces the actual x87
  `FILD/FMUL/FIMUL/FSUBR/FADD/FADD` sequence. Later original
  animation stages reduce opacity by 20 or expire the actor and
  finish through native `0040FA30` and `0045B830`.

The source fragments
`probes/CharacterObjectBoss338F1062.inc` and
`probes/CharacterObjectBoss339F1061.inc` are ordinary game C++
inserted **inside the one actual original-shaped `0x0050A580`
switch**, with their real case IDs, native actual fields/calls and
true integer/float expressions. No assembly, fake registers, dummy
locals, binary byte grafting or postRET fabricated game data was used.

## Complete original-byte and physical-field verification

`verify-characterobject-native-338-339-f1062.py` freshly compiles the
**entire** selected normal MSVC7.1 partial C++ parent and independently
reads the original PE SHA hash for the **full 81,539B original game
callable**, all 92 authentic original DIR32 jump-table equality
partitions and 199 true sparse-index literal bytes. It recovers the
physical source case index from those original bytes, and audits
actual original x86 instruction ordinal, field displacement byte,
REL32 call/DIR32 global kind, actual PE-derived destination, zero
source addend and source `AtXXXXXXXX` symbol for every nonlocal
external field.

| Authentic state | Native CODE/x86 | Current inner source CODE/x86 | Original mnemonic +GPR roles | Original physical nonlocal PE targets |
| --- | ---: | ---: | ---: | ---: |
| `0x338` | **789B/175** | 638B/175 | **175/175 each** | **12/12** (10 calls, two globals) |
| `0x339` | **495B/101** | 367B/101 | **101/101 each** | **10/10** (four calls, six globals) |
| **Both real original states** | **1,284B /276 x86** | 1,005B /276 x86 | **276/276 each** | **22/22** |

Their remaining actual native instruction widths still differ: source
`0x338` is **125/175** width-correct, source `0x339` **59/101**.
The full original whole source owner has native ESP frame **0x3A0**
and saved receiver **EBP-0xAC**, whereas the current incomplete C++
prototype emits ESP frame **0xBC** and saved receiver **EBP-0x38**.
A matching original game state mnemonic/GPR stream is *not* byte
exact and cannot be accepted as a separate callable.

## Cross-state register phase: the real loop matters

Compiling just the real `0x339` with an earlier marker at `0x338`
matched its original 101 x86 mnemonics, but **only 30/101 real GPR
roles**; next `0x33A` fell to **68/168**, with the following long
state `0x33B` at **325/402**. These are measured **true entire
partial-parent** source comparisons, not cropped independent object
functions. Merely keeping a previous source that made some local
cases look good was not acceptable.

Restoring the original `0x338` 13-projectile C++ loop and authentic
parent/action control now gives **175/175 native GPR for `0x338`,
101/101 for `0x339`, 168/168 for `0x33A`, all 402/402 for the
following five big states, all 57/57 for the five fade states and
35/35 for `0x345`**. The actual native jump-table identities,
source data slots and real external targets are preserved across the
whole parent. This demonstrates a genuine **C++ register-lifetime
coupling across full game states**, not a forced register fix.

The current selected **partial** C++ parent compiles to **14,437 CODE
B /3,763 x86** plus original 567B afterRET data. Its **25
source-recovered authentic original state interiors** span **16,754
real original CODE B /3,585 native x86**; the selected emitted C++
source case interiors occupy **13,286 CODE B**. Across those 25
states, full original mnemonic and GPR-role match is **3,585/3,585**
each, and **292/292 original physical nonlocal call/global targets**
are independently verified. These numbers include the prior 17
smaller, five 1,908B long and 0x33A states: do not count the same
case twice.

**No original complete 81KB game callable is newly exact, no new
accepted original CODE bytes**. Source has many unresolved marker
states; the original whole function and its large stack/byte widths
still require genuine source reconstruction. Exact origin credit remains
979 accepted complete functions, not incremented by case interiors.

Scoped reproduction, without all-979 cold replay:

    scripts/repo-python scripts/verify-characterobject-native-338-339-f1062.py
    scripts/repo-python scripts/verify-characterobject-native-33a-f1059.py
    scripts/repo-python scripts/verify-characterobject-five-long-actions-f1057.py
    scripts/repo-python scripts/verify-characterobject-multi-state-f1047.py

Fresh normal C++ source/COFF/PDB and genuine native PE proofs are under
ignored `.analysis/f1062-native-338-339-proof/`, with the first
`0x338/0x339` experiments retained at `.analysis/f1061-object339/`
and `.analysis/f1062-object338/`. No complete 979-unit cold replay.
