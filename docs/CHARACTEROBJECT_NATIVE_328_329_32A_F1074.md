# F1073/F1074 — Three genuine 1.7–1.8KB projectile states and 48 native unrolled 0x339/0x33A launches

**F1077 corrected actual projectile IDs:** original PE ordinal 209 in `0x328` and ordinal 187 in `0x329/0x32A` each push `0x339`, not `0x33A`; the next 15 unrolled calls push `0x33A`. The first tracked F1074 source mistakenly used 16×`0x33A` even though mnemonics, GPR roles and 107/107 PE external fields matched. [F1077 original scalar-literal audit](CHARACTEROBJECT_SPAWN_IMMEDIATE_PROOF_F1077.md) now detects and prevents this error.

**Historical F1074 checkpoint:** after restoring genuine [F1076 0x346/0x347](CHARACTEROBJECT_NATIVE_346_347_F1076.md), live whole-parent geometry and native coverage are now 38 states. The three F1074 state PE field and opcode proofs are still valid; 36-state compiler dimensions below are the earlier checkpoint.

The independently authored pinned Japanese TH075 v1.11 game has ONE
`CharacterObject::Advance` original callable at **0050A580**:
**81,539 native original CODE B /17,435 x86** with **567 separately
owned afterRET switch DATA bytes**. This work restores three
previously marker-only game-state bodies inside the same tracked
original-shaped natural C++ parent, not three separately callable
original game functions. Original full 81KB remains **NONEXACT**.

## Real three original physical game action handlers

| Original native state | Actual PE handler interval | Original CODE/x86 | Selected emitted C++ case |
| --- | --- | ---: | ---: |
| `0x328` | **0050B821..0050BF41** | **1,824B /435** | 1,458B /435 |
| `0x329` | **0050BF41..0050C602** | **1,729B /413** | 1,379B /413 |
| `0x32A` | **0050C602..0050CCC3** | **1,729B /413** | 1,379B /413 |
| **Three distinct inner states** | — | **5,282B /1,261 x86** | **4,216B /1,261 x86** |

The game native original 329 and 32A independently have **identical
ordered mnemonic, size and GPR-role sequences across 413 x86 each**;
their physical local loop and integer-to-float scratch slots differ.
Critically, original 329 initializes the real X speed to **20.0f**
(`0x41A00000`), whereas 32A initializes it to **10.0f**
(`0x41200000`). They remain distinct physically owned C++ switch
cases instantiated from one repeated authentic gameplay grammar;
no original jump slots are aliased together.

Each authentic state implements a **ten-shot `0x3E4` parent projectile
loop** under parent native action range `(0x31,0x96)`, plus original
parent+0xEFA conditional extra `0x3E3` projectile and timer reset.
Outside that parent branch each checks the four original X/Y arena
bounds against `0065925C/00659258/006583B4/00658374`, sets native
stage-zero motion and actual scale/alpha counters through `0040FBB0`,
reacts to real +0x7C status six, advances signed-facing X velocity,
and spawns a real `0x32B` object with two independently randomised
float coordinates. Both random coordinates use actual `00455580`
plus the actor's live X or Y and subtract original `00657878`.
Original normal VC7.1 argument evaluation actually computes the
**Y random value before X**, placing the original source's float
`FILD/FADD/FSUB` values directly on the caller stack.

On the true state/ground condition, source calls original
`0045B830`, original parent `00453E60(5.0f)` and original parent
`00453D40(1)`, then emits **sixteen separate original native calls
per action** to `00453A70`: the first spawns `0x339`, then
15 spawn `0x33A` objects
with actor X/Y and facing. They are **unrolled in the authentic
native PE, not a runtime for-loop**; the normal C++ source uses a
one explicit `0x339` call and fifteen direct `0x33A` macro
expansions
in each independent switch handler. These are **48 authentic direct
call statements across three cases**, not synthetic stack fillers.

### Original-source distinctions and corrected execution order

Native `0x328` additionally invokes `0040FB70` with original
**13.0f (`0x41500000`)** and the actor+0xC8 **direct bitwise DWORD
angle argument**, and copies the actual +0xC8 DWORD bit value into
+0x30. MSVC7.1 must emit native `MOV/PUSH` for this observed angle
stack argument rather than a regenerated FPU `FLD/FSTP`; source's
narrow raw-DWORD helper declaration records that verified ABI
without claiming a fully known historical method declaration.
It also updates Y motion and performs the actual ground condition
with `TEST AH,0x41; JP`. Native 329/32A do not invoke this angle
initializer or apply that Y-motion/ground branch: their original
X-only motion and `+0x80` action check are represented separately.

The initial natural C++ 328 candidate incorrectly placed the random
`0x32B` spawn *inside* its native ground/state branch. Original PE
shows random calls and spawn **before** the condition, regardless
of subsequent ground state. The resulting genuine full-source C++
emitted only 395/435 matching original mnemonics despite matching
x86 count. Moving the *real gameplay call* to the physical original
place, without adding dummy code, restores **435/435** native
mnemonics and **435/435** GPR roles. The correct current source also
preserves original native `TEST AH,0x41; JP` ground branch.

## Whole-compiled original physical PE proof

The tracked
`scripts/verify-characterobject-current-recovered-f1068.py`
cold compiles the **single entire current partial C++ function**
with pinned MSVC7.1 `/Od /Ob0 /Gy /GR- /GX- /GS /Zi` and
independently SHA-checks the **entire original 81,539B code**,
original 92 physical afterRET DIR32 case-label partitions and
199 original sparse index bytes from the pinned Japanese executable.
It then compares every native original recovered game case x86
ordinal/GPR role against its actual whole-source case, and checks
each original external REL32/DIR32 physical field position, kind,
original PE-derived target and genuine source symbol address.
For the three new game cases, actual original verified evidence:

| Physical source/PE evidence | `0x328` | `0x329` | `0x32A` |
| --- | ---: | ---: | ---: |
| Ordered native original mnemonics | **435/435** | **413/413** | **413/413** |
| Original native GPR-role positions | **435/435** | **413/413** | **413/413** |
| Native original instruction widths matching | 313/435 | 297/413 | 297/413 |
| Genuine PE nonlocal external fields | **37/37** (30 calls, seven globals) | **35/35** (29 calls, six globals) | **35/35** (29 calls, six globals) |
| Individual original `00453A70` spawn CALLs | **19/19** | **19/19** | **19/19** |
| Original native `00455580` random CALLs | **2/2** | **2/2** | **2/2** |
| Actual stage-specific float immediate | **13.0f** | **20.0f** | **10.0f** |

Each action's 19 original spawn calls consist of the real ten-shot
loop's **one** physical `00453A70` call site, **one** extra parent
projectile call, **one** random 0x32B spawn, and **sixteen** separately
unrolled original calls (first `0x339`, then 15 `0x33A`).
Every PE physical field must be at the same
original instruction ordinal as the selected source's relocation:
matching names or first-byte lengths without physical target
verification are insufficient. Original raw angle and float
immediate checks are also asserted, not assumed from old documents.

The live current one-parent proof now checks **36 genuine original
game-state interiors** spanning **30,413 native original CODE B /
6,634 original x86**, with **6,634/6,634 ordered native mnemonics
and GPR roles** and **529/529 physically original external PE
call/global fields**. The present partial whole C++ emits
**25,234 CODE B /6,790 x86**, of which **24,248B** are generated
code for those recovered game case interiors; all original-shaped
567B afterRET native DATA is retained. The true independent original
whole game callable remains **81,539B /17,435 x86** and has
`ESP 0x3A0`, native saved receiver EBP-`0xAC` versus the current
partial C++ `ESP 0x140`, EBP-`0x5C`. It remains **NONEXACT** with
many unrecovered original state markers, stack widths and branch
geometry errors; no new original whole function or original CODE
byte has been accepted exact.

Reproduce **ONLY the affected one whole parent**, not all 979 units:

    scripts/repo-python scripts/verify-characterobject-current-recovered-f1068.py

All former focused native-PE verifier controls for F1044 through
F1071 and twelve whole-parent x87 operand-order C++ variants were
recompiled against the selected current source. Logs, actual
Japanese PE receipts, normal C++/COFF/PDB outputs and rejected
first 328 candidate remain under ignored `.analysis/f1073-object328/`,
`.analysis/f1074-object32932a/` and `.analysis/f1068-boss-live-all-native/`.
No source bytes were grafted from the original PE, no dummy local
was used, and no all-979 unit cold replay was performed.
