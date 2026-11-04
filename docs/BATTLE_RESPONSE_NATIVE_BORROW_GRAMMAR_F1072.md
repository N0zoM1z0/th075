# F1072 — Preserve five complete native combat response functions with physical borrowed scalar windows

The pinned Japanese TH075 v1.11 original `BattleCombatResponses.cpp`
contains **five separately accepted exact complete game callables**,
including substantial **1,185B `ApplyHitResponse`**, **898B
`ApplyAttackHit`** and **664B `ApplyGuardHit`**, as well as original
**230B `ApplyReactionMode`** and **96B `SpawnMidpointEffect`**.
The whole native source object covers **3,073 previously credited
original CODE B**. F1072 updates meaningful native field names in
that same real source without changing any original game byte,
physical COFF relocation, native jump-table label or ownership.

## Three genuine independent native borrowed field windows

1. The signed **16-bit fighter flash-bar span at +0x3C8** is used in
   seven actual assignments/shifts/round transitions of the complete
   combat response game logic. `FlashBarSpanF1072(actor)` gives these
   physically observed reads and writes a named role without
   claiming the original fighter+0x3C8 is a separately allocated
   2-byte object. Original +0x3C0 combo rate remains independent.
2. The two adjacent **signed WORD fields** at actor+0x80/+0x82
   are the distinct original action-associated WORD and animation
   timer. Actual combat `ApplyAttackHit`/`ApplyGuardHit` uses
   `ActionWordF1072(attack)` for the native decrement and
   `TimerWordF1072(attack/defender)` for four genuinely sourced
   animation timer writes; the old unchecked raw access names
   obscured the real distinct purposes. This is native borrowed
   scalar data, not a proposed full actor layout.
3. The complete original `SpawnMidpointEffect` reads this battle
   collision owner+0x34/+0x38/+0x3C/+0x40 as four consecutive
   **signed 32-bit bound coordinates**, combining left/right and
   top/bottom into a physical center for genuine `g_CombatEffects`.
   The new `CombatBoundsF1072(this)[0..3]` is a **borrowed int[4]
   window beginning at owner+0x34**, never a new owner pointer,
   allocated rectangle or a guessed historical class.

## MSVC7.1 source-grammar negatives were checked rather than ignored

The separate independent native
[`FighterVitalBorrowedF999`](../src/FighterVitalBorrowedF999.hpp)
struct is already a valid physical +0x324/+0x326 signed WORD view
in other accepted functions, but including it in this specific
translation unit changes its VC7.1 compiler-local `$L` labels.
An actual whole-object cold replay with that header gave only
**3/5 exact**; the 1,185B original `ApplyHitResponse` and 230B
`ApplyReactionMode` were **NONEXACT under strict COFF comparison**,
even though all entire emitted game CODE bytes were unchanged.
The failure is physical original jump-table COFF symbol identity,
not merely new named source type metadata. Four complete natural
C++ scope controls (header-only, header after the first original
switch, locally scoped `F999` usage, typed global usage) reproduced
these symbol changes: earlier switch had 2–11 changed synthetic
label strings and the later switch had seven, while all original
CODE bytes remained bitwise identical.

Trying an otherwise physically legitimate new C++ `struct` with
left/top/right/bottom fields also disturbed those original compiler
label identities. None of those sources were accepted or masked by
relaxing relocation comparisons. The selected **scalar borrowed
array** naming creates **no new C++ struct definitions**, preserves
the source C++ game expression ordering and keeps every genuine
original function's compiler labels. The discarded complete source
C++/OBJ/PDB and full switch-label comparisons are retained in
ignored `.analysis/f1072-response-borrows/` for review, not silently
deleted as an assumed obsolete experiment.

## Entire original unit cold replay

Final normal pinned MSVC7.1 `/Od /Ob0 /Gy /GR- /GX- /GS /Zi`
source object was **cold built**, and all five complete original
callables independently checked (code bytes plus exact COFF fields):

| Complete native function | Original CODE B | Result |
| --- | ---: | --- |
| `battle-combat-apply-hit-response` | 1,185 | exact |
| `battle-combat-apply-attack-hit` | 898 | exact |
| `battle-combat-apply-guard-hit` | 664 | exact |
| `battle-combat-apply-reaction-mode` | 230 | exact |
| `battle-combat-spawn-midpoint-effect` | 96 | exact |
| **One affected original translation unit** | **3,073** | **5/5 exact** |

Reproduce ONLY these affected originals, not a 979-unit cold replay:

    scripts/repo-python scripts/replay-exact-units.py \
        --unit battle-combat-apply-hit-response \
        --unit battle-combat-apply-attack-hit \
        --unit battle-combat-apply-guard-hit \
        --unit battle-combat-apply-reaction-mode \
        --unit battle-combat-spawn-midpoint-effect

**Existing 3,073 exact original CODE B remain accepted**, with
**zero** newly credited complete original functions/bytes. The game
EXE, exact-unit manifests, original call targets and strict COFF
identity comparison were not altered. No full corpus replay.
