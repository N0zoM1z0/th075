# F606 — the remaining four original 0x47/0x48 actions in two giant fighters

**Genuine pinned Japanese TH075 1.11 native PE → ordinary VC7.1 C++
whole-action subranges, but neither enclosing giant is byte-exact.**
Executable SHA256 `bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
F605 reconstructed 18 real 86-instruction action0x47/0x48 bodies
in the nine regular fighter giants. F606 independently reconstructs
the remaining four complete original action subranges from the *other
two real whole fighter functions*, rather than forcing them to a false
86-instruction source shape.

## Original PE source differences are real game semantics

The original native second packed-switch sparse map binds actions
`0x47`/`0x48` to dense slots **12/13**, followed by physical action
`0x49` at slot 14. Independently decoded complete original code:

| Entire giant, still unmatched | Original action | Native complete inner CODE | Native x86 roles | PE/COFF typed refs | Real stage-one projectile |
| --- | --- | ---: | ---: | ---: | --- |
| `0045DD70` | `0x47` | 395 B | 113 | 14 | `0x3B7`, side 1, **before** early-stage check |
| `0045DD70` | `0x48` | 310 B | 86 | 13 | No projectile-spawn guard |
| `0058AF60` | `0x47` | 395 B | 113 | 14 | `0x3E7`, side 0, **before** early-stage check |
| `0058AF60` | `0x48` | 395 B | 113 | 14 | `0x3E7`, side 0, **after** early-stage check |
| **Total: 4 real native interior cases** | | **1,495 B** | **425** | **55** | |

The last row's exact order is crucial: the original `0058AF60`
`0x48` at original x86 ordinal 23 first tests stage 2, compares
`+0x54` with real float `00657480`, and may set auxiliary state 3
and return. **Only after that check** does it test stage 1/frame 0
and the one-shot flag `+0xF0C`, then call the game projectile constructor
`00453A70`. Its `0x47` has the inverse order, spawning before the
stage-2 early transition. These behaviors are *not* interchangeable
just because both complete originals have 113 instructions/395 bytes.
`0045DD70` `0x47` has stage1/aux2 and a real once-only `0x3B7`
spawn; its `0x48` has no native projectile branch at all.

The normal trajectory setup also differs from F602 `0x46`: the
original copy `this+0x98` to `this+0x54` is a raw 32-bit `MOV`, not
floating-point load/store. `0x47` sets 0.8f drag and `0x48` sets
1.3f drag. Both use the real **two separate x87-to-signed-short
`__ftol2`** calls to CRT `006406AC`, genuine adjacent `+0xF00`
velocity fields, the actual game state helpers, the full original
signed stage and frame checks, and a native one-shot stage1
`+0xF0C` flag for each of the three projectile variants.

## Two real source grammar families and complete typed PE/COFF evidence

The two meaningful original C++ game control-flow orders are kept as
**distinct, natural C++ source bodies**:
[`FighterTrajectoryFollowupSpawnF606.inc`](../probes/FighterTrajectoryFollowupSpawnF606.inc)
uses the physical spawn-before-transition order; the distinct
[`FighterTrajectoryFollowupLateSpawnF606.inc`](../probes/FighterTrajectoryFollowupLateSpawnF606.inc)
uses spawn-after-transition. For `0045DD70` action0x48, the true
86-instruction C++ case from [F605](../probes/FighterTrajectoryFollowupsF605.inc)
is reused without changing its behavior. Source parameters are derived
from the actual original case instructions, not a guessed universal
character class: correct case value, true stage/early/late states,
projectile kind/side, 0.8f or 1.3f drag, actual original byte argument
`+0x66`, positions `+0x44/+0x48`, real signed-short output and flag.

A dedicated reproducible verifier
[`verify-fighter-trajectory-followup-spawns-f606.py`](../scripts/verify-fighter-trajectory-followup-spawns-f606.py)
first re-reads every original native physical case extent and sparse
index, the genuine 86/113 x86 instruction geometries and every
native flag/drag/call/global field. It cold-compiles only the selected
**whole giant source translation unit** under pinned VC7.1
`/Od /Ob0 /Gy /GR- /GX- /GS /Zi`, and independently validates:

- All 4 original complete case bodies, every physical instruction
  size and GPR/x87/CFG operand role, and 13/14 physical typed zero-addend
  source COFF relocations at the true original x86 ordinals;
- All genuine native PE target destinations, including the real
  `0x00453A70` 5-argument stage-one spawn and separate `__ftol2` calls;
- The **earlier 23 original case** roles via the existing F600 strict
  comparison, the **entire 131-instruction native `0x46`** source on
  the same newly compiled OBJ, and the complete original physically
  typed after-RET switch DATA layout. No stale old OBJ is an acceptance
  substitute, and no generated case subrange is cut into a fake
  complete function.

F606 adds **425 x86 native roles /1,495 real original internal CODE
bytes /55 actual typed COFF fields** on top of F605. Together,
**all 22 native actions `0x47` and `0x48` in all 11 giant fighters**
are now source-backed: **1,973 original x86 roles, 7,251 original
internal CODE bytes and 289 true COFF fields**. Including F598/F600/
F602/F603's earlier action bodies, each selected fighter has **26
natural C++ game actions inside its still-incomplete `Advance()`**;
that is **286 original interior game case bodies /66,880 original
internal CODE bytes** across the eleven parents, not 286 separate
complete original functions.

**All eleven complete fighter functions remain NONEXACT;** the two
other dozen giant functions and three smaller authored complete
functions also remain unmatched. Official authored exact ledger still
reads **943 whole functions /862,726 original CODE bytes**. No
native game executable/data was altered, no fabricated saved-frame
locals or byte graft used, and no all-unit cold replay or external
Oracle acceptance was claimed.

## Targeted reproduction only

```bash
scripts/repo-python scripts/verify-fighter-trajectory-followup-spawns-f606.py --boss 0x0045DD70
scripts/repo-python scripts/verify-fighter-trajectory-followup-spawns-f606.py --boss 0x0058AF60
# Or these two affected giant source translation units only:
scripts/repo-python scripts/verify-fighter-trajectory-followup-spawns-f606.py
scripts/repo-python scripts/validate-tracking.py --require-target
```

Fresh generated full C++ source, COFF/PDB and original/x86/field
receipts are in ignored `.analysis/f606-trajectory-spawn-source/`;
the independent trial/variant experiments are preserved in
`.analysis/f605-followup/`. The repository match manifests and
original provenance ledger are intentionally unchanged.
