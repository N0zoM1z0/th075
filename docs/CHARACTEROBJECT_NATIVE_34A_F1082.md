# F1082 — Original 486B action 0x34A: real 0x2C0 parent guards, stage fade and two return paths

**Historical F1082 checkpoint:** the current partial C++ parent now adds [F1083 original 0x34B](CHARACTEROBJECT_NATIVE_34B_F1083.md). The native PE 0x34A evidence remains valid, but 41-state/28,148B numbers below refer to the older source snapshot; use the live 42-state verifier for current dimensions.

The independently pinned Japanese TH075 1.11 game has **one** authored
`CharacterObject::Advance` at `0050A580`, original **81,539 CODE B /
17,435 x86**, plus genuine 567 separate afterRET jump/sparse DATA B.
F1082 restores real native action `0x34A` at
**005129C1..00512BA7 (486 original CODE B /102 x86)** as normal
C++ inside the same still-incomplete 81KB whole-parent probe. No
inner game action is an independently accepted original callable.

The actual original 0x34A first copies the **parent X DWORD bits** at
+0x44 without x87 conversion, zeroes own Y at +0x48, and sets its
native +0x8A WORD to 1. On stage/frame (0,0) it calls original
`0040FBB0` and initializes X/Y scale to genuine **2.5f**, the four
opacity bytes to 0xFF, sprite WORD `0x4E2`, real float +0x2C/+0x30
to zero, float +0x28 to **−80.0f** (`0xC2A00000`), then invokes the
parent's actual `00453D40(0x10)`.

During stage 1, original PE checks parent action WORD at +0x60
against **0x2C0**, and then *independently* compares its parent
+0x62 WORD against **0x2C0 and 6** before calling native
`0040FB40(2)` and returning. These repeated original literal
checks may look redundant or contradictory in a simplified gameplay
model, but they are **what the real PE actually executes**. Source
does not silently replace them with a presumed different action
condition. In stage 2, it decreases actual unsigned alpha by 15 or
expires via `0045B830`. It then increases native +0x30 by the actual
float at **0065747C**, checks original `0040FA30` action completion
and performs the original expiry or direct return.

The first ordinary VC7.1 source compile emitted **101** native
mnemonics, one short of the actual original 102, because an
implicit fallthrough merged two genuine original return paths into
one terminal `JMP`. Adding the true explicit `return` in the original
completion branch restores the real **two distinct terminal JMPs**
without extra fictional gameplay. The original source case now has
102 instructions, with 102/102 native mnemonic and GPR matches.

| Original state `0x34A` | Measured normal source |
| --- | ---: |
| Native original CODE/x86 | **486B /102** |
| Emitted inner C++ CODE/x86 | **383B /102** |
| Matching original mnemonic/GPR sequence | **102/102 each** |
| Matching original instruction widths | 68/102 |
| Physically correct original PE fields | **7/7** (6 native calls, one float global) |
| Native +0x28 literal | `0xC2A00000`, matched |
| Parent stage/action literals | `0x2C0` at both native ordinals 53/58, matched |
| Both original trailing return jumps | 100/101, matched |

The live one-parent verifier
`scripts/verify-characterobject-current-recovered-f1068.py`
freshly compiles only the current real original-shaped whole C++
source and independently audits SHA-pinned Japanese PE CODE, 92
original DIR32 jump-label equality partitions, all 199 sparse bytes,
**41 genuine state interiors** covering **34,127 original CODE B /
7,428 x86**, **7,428/7,428 original mnemonics and GPR roles**,
**596/596 actual original physical PE call/global fields**, plus
**1,387/1,387 non-relocated native scalar-immediate positions**.
The selected incomplete C++ emits **28,148 CODE B /7,574 x86**
(27,237 emitted case-interior B) and still has actual saved receiver
EBP-0x60 and `ESP 0x180`, instead of the original game
EBP-0xAC and `ESP 0x3A0`. Many other game cases remain marker-only,
and authentic original x86 widths/branch offsets are nonexact;
**entire original 81KB callable NONEXACT, no new exact CODE credit**.

Reproduce only the changed original-shaped large parent:

    scripts/repo-python scripts/verify-characterobject-current-recovered-f1068.py

The missing-return negative candidate and real VC7.1 COFF/PDB plus
independent original PE receipts remain under ignored
`.analysis/f1082-native34a/` and `.analysis/f1068-boss-live-all-native/`.
No original EXE mutation, assembler, synthetic register lifetimes,
artificial marker replacement or all-979-unit cold replay.
