# F602 — genuine 0x46 trajectory action inside nine entire fighter bosses

**PE-attested native action reconstruction; all enclosing giant functions
remain NONEXACT.** The only native executable is the user-provided
Japanese TH075 1.11 `resources/th075.exe` with SHA256
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
This study continues the true 11-game-action, 0x32 singleton and F600
0x33..0x41 second-switch source in the **same** unfinished C++
`Advance()` function, not a disconnected small-function replacement.

## A new complete, nontrivial fighter action in the actual original PE

Original action `0x46` immediately follows the eleven distinct F600
contact actions in the second **compressed sparse-index switch**. Its
complete physical original extent is bounded by the two genuine dense
jump-table DWORDs for `0x46` and `0x47`. The original behavior is
not a simple 58-instruction contact trigger:

- On stage `+0x62 == 0` and frame `+0x64 == 0`, negate live float
  velocity `+0x94` to position `+0x50`, add float `+0x98` to `+0x54`,
  constrain its range with **two actual native float globals**, set
  speed `+0x5C = 0.8f`, and clear integer counter `+0x7C`.
- At a genuine original *actor-specific* stage (1, 2 or 3) and
  `+0x54` less than the original float at `00657480`, issue an
  actor-specific auxiliary action 2, 3 or 4, then exit the case.
- Otherwise subtract speed from `+0x54`, check ground contact with
  `+0x48`, and convert both x87 float velocities to adjacent **signed
  16-bit** trajectory slots via the actual original `__ftol2`
  (`006406AC`). The two true native float multiply references are
  `00657888`, not invented integer multipliers. Then call original
  `ResetAt453E20`, clear `+0x48`, transition to native state `0x61`,
  call `InitTrajectoryAt453E60(2.0f)` and `PrepareActionAt453D60(0x16)`.
- On the normal frame-completion branch, compare the real receiver
  return of `0040FA30` to `+0x70` and send the original per-actor
  auxiliary state (5, 6, 7 or 8) to `0040FB40`.

`00453E20`, `0040FAC0`, `00453E60`, `00453D60`, `0040FA30`
and `0040FB40` remain original borrowed game callee interfaces, not
claimed as part of the reconstructed case. The original PE independently
identifies each actual callee and global destination; no supplied
old decompiler guess substitutes for these identities.

## Natural pinned VC7.1 codegen and the real expression-order solution

Tracked [`FighterTrajectoryContact46F602.inc`](../probes/FighterTrajectoryContact46F602.inc)
is an ordinary C++ case included in the previously verified fighter
switch. During independent exploration, a normal expression for
`POS54 + F32(0x98)` initially produced **104 original-style
instructions / 374 bytes**, but the compiler emitted the wrong
`FLD`, register load and `FADD` ordering. Genuine lvalue expressions
`*(&POS54) + *(&F32(0x98))` naturally restore the original x87
ordering with no inline ASM or opcode patch. Separately, the
ordinary parenthesized `(POS54) * g_ContactProjectionAt00657888`
restores the other original **`FLD member; FMUL global`** ordering
rather than `FLD global; FMUL member`. A matrix of independently
compiled positive/negative natural source variants is retained
privately under `.analysis/f602-giant-trajectory/`.

[`verify-fighter-trajectory46-f602.py`](../scripts/verify-fighter-trajectory46-f602.py)
re-extracts the original per-fighter native case and independently
checks every instruction start, x87/GPR/branch role and byte width,
physical float compare/multiply target, **both real `__ftol2` calls**,
15 genuinely typed, zero-addend native PE/COFF fields, direct game
calls, initial and terminal per-actor state constants and actual
trajectory member offsets. Its full-source build retains all **23
previously reconstructed game actions** and rechecks the whole
original after-RET switch DATA layout in each selected new OBJ.

## Original owner differences, verified in each separate full source TU

| Entire giant (nonexact) | Original 0x46 CODE | X86 roles | COFF fields | Native stage / early / late | Native range globals |
| --- | ---: | ---: | ---: | --- | --- |
| `005D73C0` | 374 B | 104 | 15 | 2 / 3 / 5 | `657480`, `6590C4` |
| `00486550` | 374 B | 104 | 15 | 3 / 4 / 7 | `658290`, `6592A4` |
| `004AC040` | 374 B | 104 | 15 | 3 / 4 / 5 | `658290`, `6592A4` |
| `00543210` | 374 B | 104 | 15 | 1 / 2 / 7 | `658290`, `6592A4` |
| `00564BE0` | **485 B** | 104 | 15 | 1 / 2 / 6 | `658290`, `6592A4` |
| `004D7E70` | 374 B | 104 | 15 | 2 / 3 / 8 | `658290`, `6592A4` |
| `004F7130` | 374 B | 104 | 15 | 3 / 4 / 7 | `658290`, `6592A4` |
| `005AEEC0` | 374 B | 104 | 15 | 3 / 4 / 7 | `658290`, `6592A4` |
| `005214B0` | 374 B | 104 | 15 | 3 / 4 / 7 | `658290`, `6592A4` |
| **Total** | **3,477 original inner bytes** | **936** | **135** | | |

The original `00564BE0` case reads the actual `EBP−0x88` owner,
requiring **37** original widened saved-this loads (111 native
additional displacement bytes) compared with its 374-byte natural
C++ case. The source uses no fake saved-local allocations.
`005AEEC0` has an independently verified **`+0xEFC`** trajectory
base, rather than `+0xF00` in all other eight of these nine
fighters; both 16-bit output words are original member accesses.
The other actor constants are derived from independently decoded
original instruction operands before source generation, not taken
from guessed game type tables.

**The remaining two fighter originals `0045DD70` and `0058AF60`
are NOT represented as this 104-instruction version.** Their physical
original `0x46` cases each contain **131 instructions / 459 bytes**,
including genuine additional stage-one projectile creation. A
104-instruction source must not claim to match those; further real
C++ work is required.

Across these nine fighter parents, F602 brings source-backed whole
inner game action evidence to 262 case subranges / **58,711 internal
original CODE bytes** (prior F598/F600 253 /55,234 plus these nine
new 0x46 cases). This does **not** make even one of the eleven entire
fighter functions byte-exact, nor convert these case subranges to
standalone functions or credit original jump-table DATA. The official
ledger therefore remains **943 exact authored whole functions /
862,726 original CODE bytes**, with no external Oracle acceptance.

## Targeted reproduction (one or only nine new source TUs)

```bash
scripts/repo-python scripts/verify-fighter-trajectory46-f602.py --boss 0x004F7130
scripts/repo-python scripts/verify-fighter-trajectory46-f602.py --boss 0x00564BE0
scripts/repo-python scripts/verify-fighter-trajectory46-f602.py --boss 0x005AEEC0
# The other six affected giant source TUs, but no 943-unit cold replay:
scripts/repo-python scripts/verify-fighter-trajectory46-f602.py
scripts/repo-python scripts/validate-tracking.py --require-target
```

Full original case-native/codegen receipts, all nine newly compiled
C++ sources, objects, PDBs and logs are kept under ignored
`.analysis/f602-fighter-trajectory-source/`; earlier codegen
expression controls are under `.analysis/f602-giant-trajectory/`.
No untracked generated executable, partial case-credit, fake locals,
ASM, original byte graft or all-unit cold replay occurred.
