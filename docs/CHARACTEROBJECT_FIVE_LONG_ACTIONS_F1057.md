# F1057 — Five independently native 1,908B/402-x86 CharacterObject game states

The pinned Japanese TH075 v1.11 original has **one** authored
CharacterObject::Advance game callable at `0050A580`: **81,539 original
CODE B /17,435 x86** followed by 567 separately owned sparse switch
DATA bytes. It is still **NONEXACT**. Its incomplete C++ source now
reconstructs five larger true game state bodies which were previously
marker placeholders, rather than trying to game register allocation
by modifying only smaller leaves.

## Independently verify the original five physical state owners

Each genuine original action **`0x33B/0x33D/0x33F/0x341/0x343`** is
**1,908 original CODE B /402 x86 /33 external call/global fields**:

| Action | Original native original PE extent | Native next projectile |
| --- | --- | --- |
| `0x33B` | `0050F25A..0050F9CE` | `0x33C` |
| `0x33D` | `0050FACA..0051023E` | `0x33E` |
| `0x33F` | `0051033A..00510AAE` | `0x340` |
| `0x341` | `00510BAA..0051131E` | `0x342` |
| `0x343` | `0051141A..00511B8E` | `0x344` |

Before constructing a repeated C++ template, the original PE was
compared **across all 402 native instruction ordinals of each case**.
Their original mnemonics, widths, register roles, original call
DESTINATIONS and real global addresses are identical in all five.
Exactly **15 original physical non-branch operand differences** appear
between the first and every following case: fourteen are the actual
changing loop/signed-int-to-x87 scratch stack EBP offsets, and the
remaining one is the real next-projectile ID. In particular, the
original loop's index stack locals progress from EBP-0x34 to -0x38,
-0x3C, -0x40, -0x44: this is actual C++ lifetime evidence, not a
pretext to synthesize inert padding fields. Genuine native saved
receiver is EBP-0xAC in every case, while the whole original frame
remains ESP-0x3A0.

## C++ gameplay restored, not binary-body substitution

The selected `CharacterObjectBossLongF1057.inc` contains real original
C++ gameplay once, instantiated into five **independent switch cases**
with the authentic case ID and subsequent projectile ID for each.
Each original state genuinely:

- Tests four real actor X/Y arena bounds; invalid coordinates call
  `0045B830` and exit.
- In genuine parent action range, executes **three actual `0x3E4`
  projectiles** at `00453A70`, plus a conditional original `0x3E3`
  and parent +0xEFA timer reset.
- Checks original +0x7C/animation stage/frame, initializes real
  motion, scale, opacity and state WORDs, and converts actual float
  +0xC8 into the native signed +0xDC angle.
- Uses the actual `00483300` float atan2 wrapper, target player at
  parent+0x2E8, real float `00657888` offset, original angle scale
  `00657828`, signed short angle tracking/clamp, authentic native
  `0040FB70` motion and a second, state-specific projectile at
  `00453A70`.
- Uses real `00455580` randomness and the original two **double**
  constants at `00658A20/00657D00`, then true +0xC8 vertical
  adjustments, facing-dependent X velocity, and Y motion subtraction.
- Preserves original status 0/4/5/6 guards, `0040FB40` action
  transitions, fade scaling via `006598A4`, alpha fade/expiry,
  and original `0040FA30` final action completion.

A first full normal-VC7.1 C++ source emitted **398/402 native mnemonics**
per case. Independently re-reading the native physical x86 identified
and corrected two real source mistakes: the `Y -= motion` expression's
`FLD/FSUB` lowering, and the +0x7C status check that had mistakenly
used `==4` instead of native `!=4`. After the fixes, the selected C++
compiles to **402/402 original mnemonics** in all five long states.
This is not opcode grafting and it preserves genuine whole-source
control flow. No byte arrays or assembler instructions were used.

## 165 independently physical original PE target checks

Native original x87 at state ordinals **262/263 and 277/278** first
loads **target player Y** and then adds the real PE `00657888` offset.
The apparently natural `F1037_POSITION(...).yPosition + global`
expression compiled with VC7.1 in the **opposite order**: it emitted
`FLD global` at ordinal 262, so two source COFF fields per long state
were in genuinely wrong original physical instructions. This was
measured as **31/33** true native physical PE fields per state even
though C++ and original mnemonics were the same. Such symbols cannot
simply be masked away.

The selected explicitly borrowed lvalue expression, retaining the
real `F1037_POSITION(PARENT_GRANDPARENT).yPosition` and dereferencing
its address as used (`*(&...)`), restores the original `FLD playerY`
then `FADD [00657888]` order. All five original states now produce
**33/33 physically verified external PE relocations per case**:
original x86 ordinal, field byte offset, DIR32/REL32 type, actual
Japanese PE destination and source `AtXXXXXXXX`/real `__ftol2` target.
The tracked F1057 verifier freshly SHA-checks the original complete
81KB CODE, all 92 afterRET original DIR32 label equality partitions
and 199 real sparse literal bytes as well. All **165/165 original
physical PE targets** are verified, not assumed from declarations.

| Five large original game actions | Authentic result |
| --- | ---: |
| Combined original native CODE | **9,540 B** |
| Combined native x86 ordinals | **2,010** |
| Normal compiled source case x86 | **2,010** |
| Correct native x86 mnemonics | **2,010/2,010** |
| Correct physically located original external PE targets | **165/165** |
| Correct original GPR roles | **665/2,010** |
| Compiler source case byte extents | 1,524B ×3, 1,530B, 1,548B |
| Original individual exact whole callables | **0** (one nonexact giant) |

The large original frame remains `ESP 0x3A0`, but the incomplete
whole C++ parent currently emits `ESP 0x94`; hence much of the native
GPR/stack EBP geometry still disagrees. The five states increase real
native source coverage without solving entire function exactness.
Adding these genuine large cases also changes the later x86 register
phase: `0x33E/0x344/0x345` return to **17/57, 17/57, 13/35** source
GPR roles respectively, instead of the better earlier, smaller
source-only phase. Those regressions are explicitly reported by
the current native verifiers; we do not avoid restoring genuine
large game logic merely to keep a favorable cropped state metric.

**Current selected partial parent:** 12,836 source CODE B /3,325 x86
plus the original 567B afterRET table. The previous 17 real states
and these five large ones form **22 original case intervals**, totaling
**14,707 native CODE B /3,141 native x86 /252 physically verified
external PE targets** and 11,640 generated original-shaped C++ case
CODE B. Native original GPR roles currently match **1,574/3,141**
across these intervals. The remaining switch states are real missing
game source and still contain diagnostic markers.

Reproduce ONLY the affected current whole source (not 979 cold units):

    scripts/repo-python scripts/verify-characterobject-five-long-actions-f1057.py
    scripts/repo-python scripts/verify-characterobject-multi-state-f1047.py

Fresh source, normal VC7.1 OBJ/PDB/compiler logs and original PE
receipts are retained under ignored `.analysis/f1057-five-long-native/`.
The experimental lvalue/operand-order controls and their independently
verified negative original fields are recorded separately under F1058.
**Zero new accepted whole original exact CODE bytes.**
