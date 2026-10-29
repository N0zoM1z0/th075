# F605 — original 0x47/0x48 trajectory actions in nine huge fighter controllers

**Original-PE-backed native C++ source reconstruction, not whole-function exact
adoption.** Original Japanese TH075 1.11 `th075.exe` SHA256:
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.

F602 and F603 reproduced all eleven complete native action `0x46` *interiors*
of nine 104-instruction and two 131-instruction giant fighter functions.
This study independently rereads the next **two actual actions `0x47`/`0x48`**
in the original second packed switch, then builds real C++ inside each
unfinished *entire* `Advance()` source. No action is treated as an independent
whole function, and the original after-RET switch DATA remains separate.

## Native machine-code discoveries, not historical guesses

The authentic second switch's literal compressed sparse map binds actions
`0x47` and `0x48` to dense DWORD indices **12 and 13** (native `0x49` is
index 14). All nine selected fighters have two complete 86-instruction
native cases. For eight original owners each entire case is **310 CODE
bytes**; `00564BE0` has **398 original CODE bytes** per case because its
real `EBP−0x88` receiver frame widens **28 MOV loads ×3 bytes** and its
single ground-contact `JP` widens **from a short 2-byte branch to a near
6-byte branch** (28×3+4=88 bytes). The source has no artificial frame
locals or guessed padding.

A key native semantic distinction from action `0x46`: on stage/frame zero,
these cases negate float `this+0x94` into `this+0x50`, then **copy the
literal 32-bit word** from `this+0x98` to `this+0x54`. Reproducing that
as a typed float assignment instead makes VC7.1 emit `FLD/FSTP`, changing
28 subsequent GPR/operand roles even when the 86-instruction and 310-byte
code geometry looks equal. The correct natural expression is:

```cpp
I32(0x54) = I32(0x98);
```

Both cases set `this+0x5C` to their *distinct actual original* float
literals: **0.8f** for `0x47`, **1.3f** for `0x48`, and reset the
`+0x7C` counter. Each then checks its genuine original signed stage,
position against the float at `00657480`, and actor-specific auxiliary
state. The descent/contact path subtracts speed, compares height to the
original `0065782C` float, computes **two independent x87 float-to-signed
short conversions** into adjacent genuine `+0xF00` (or actor-specific
`+0xEFC`) velocity fields using the real CRT `__ftol2` at `006406AC`,
and calls actual game functions `00453E20`, `0040FAC0(0x61)`,
`00453E60(2.0f)`, `00453D60(0x16)`, `0040FA30`, and `0040FB40`.
The two real `FLD member; FMUL global` source expressions preserve the
F602 source-order discovery; no manual register assignment or assembly.

**Do not presume the actor's stage and early/late actions match its
previous `0x46` case.** Independent original PE decoding found changes,
including `004AC040` 0x46 stage3/aux4 versus 0x47/48 stage1/aux2;
`005AEEC0` 0x46 stage3/aux4/late7 versus 0x47/48 stage2/aux3/late5;
and `005D73C0` 0x46 late5 versus 0x47/48 late6. The verifier derives
and verifies **each original action's values separately** before emitting
its natural C++ source.

## Genuine full-native source checks in the same enclosing giant

Tracked source: [`FighterTrajectoryFollowupsF605.inc`](../probes/FighterTrajectoryFollowupsF605.inc).
Reproducible verifier:
[`verify-fighter-trajectory-followups-f605.py`](../scripts/verify-fighter-trajectory-followups-f605.py).
It independently verifies both original complete action extents against
native jump-table targets `0x47/0x48/0x49`, all **86 original x86 instruction
starts/sizes/GPR/x87/CFG roles**, all 13 physically typed, zero-addend
compiler COFF fields per action against the *original PE's actual call/global
destinations* (26 per fighter), and both native signed-short motion owners.

Each selected fighter's whole C++ translation unit is **freshly compiled with
pinned VC7.1** `/Od /Ob0 /Gy /GR- /GX- /GS /Zi`. On the *same new object*,
the verifier also reruns the original PE-backed strict F600 verification of
all earlier 23 case grammars, the F602 104-instruction `0x46` action, and
the entire original after-RET packed switch DATA shape and typed jump fields.
Compiler object name, full generated code, compiler logs and original PE
receipts are retained under ignored `.analysis/f605-trajectory-source/`.

| Entire original giant (still NONEXACT) | Native cases 0x47 + 0x48 | X86 roles | Native typed COFF fields |
| --- | ---: | ---: | ---: |
| `005D73C0` | 620 B | 172 | 26 |
| `00486550` | 620 B | 172 | 26 |
| `004AC040` | 620 B | 172 | 26 |
| `00543210` | 620 B | 172 | 26 |
| `00564BE0` | **796 B** | 172 | 26 |
| `004D7E70` | 620 B | 172 | 26 |
| `004F7130` | 620 B | 172 | 26 |
| `005AEEC0` | 620 B | 172 | 26 |
| `005214B0` | 620 B | 172 | 26 |
| **F605 aggregate: 18 real inner cases** | **5,756 B** | **1,548** | **234** |

The other two giant fighters, `0045DD70` and `0058AF60`, are **not
mistakenly accepted** as the 86-instruction source. The former's native
`0x47` has 113 original instructions while `0x48` has 86; the latter
has 113 original instructions in **both** cases, with genuine additional
stage-one projectile spawning and different guards. Their real extra
branch/body must be separately reconstructed in full. The packed second
switch's later actions `0x49` onward also remain undone.

With previous F598/F600/F602/F603 source proofs, this brings the studied
interior source-backed actions to **282 original internal case bodies**
and **65,385 internal native CODE bytes**, all embedded in the eleven
**still-nonexact entire giant functions**. None of these case fragments
is a new whole-function exact adoption. The official completed-authored
ledger remains **943 whole functions / 862,726 original CODE bytes**;
all 95 pending source origins remain pending. There is no remote
Factory/Oracle acceptance receipt, no game binary patching and no full
all-unit cold replay.

## Targeted reproduction

```bash
scripts/repo-python scripts/verify-fighter-trajectory-followups-f605.py --boss 0x004F7130
scripts/repo-python scripts/verify-fighter-trajectory-followups-f605.py --boss 0x00564BE0
scripts/repo-python scripts/verify-fighter-trajectory-followups-f605.py --boss 0x005AEEC0
# Or only the nine affected original giant C++ source TUs:
scripts/repo-python scripts/verify-fighter-trajectory-followups-f605.py
scripts/repo-python scripts/validate-tracking.py --require-target
```
