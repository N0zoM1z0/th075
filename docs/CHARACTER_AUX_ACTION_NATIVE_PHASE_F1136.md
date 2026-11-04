# F1136 — 484 native signed-short stage/frame/animation/timer borrows, 31,352B whole original exact preserved

The Japanese TH075 v1.11 original has one already accepted complete `CharacterAuxObject::AdvanceActionAt005FAE30` at `005FAE30`: **31,352 original CODE bytes** and separately accounted native afterRET jump DATA. The F1135 source retains all 531 genuinely observed native X/Y position and motion float lvalues. F1136 now adds **484 source uses of four genuine signed-short native game fields**, preserving the original complete byte-exact machine function and all real COFF/local `$L` jump-table identities.

| Actually used original native actor WORD | Meaning and borrowed C++ alias | Original source uses |
| --- | --- | ---: |
| `actor+0x62` | Signed animation phase/stage, `F1136_ACTION_STAGE()` | **116** |
| `actor+0x64` | Signed animation frame, `F1136_ACTION_FRAME()` | **89** |
| `actor+0x70` | Signed completed animation/action WORD, `F1136_ANIMATION_ACTION()` | **69** |
| `actor+0x74` | Independent signed elapsed action-tick count, `F1136_ACTION_TICK()` | **210** |
| **Four native WORD owners** | **484 original source reads/writes** | **484** |

These have real native widths and roles verified across entire exact fighter animation, auxiliary action and frame-state callables; they are deliberately four borrowed fields, **not an invented whole historic C++ owner**. The aliases reuse the function's original `FIELD(short,0xNN)` expansion and are defined as parameterless `this`-owner lvalues, with explicit `#undef` after the function. No new C++ struct declaration, stack local, runtime call or target byte substitution is introduced. The original `switch` action cases, signed comparisons, shot loops, native x87 float/WORD conversions and both animation completion and timer-increment semantics are unchanged.

A first programmatic substitution accidentally replaced a macro's own right-hand side, yielding an invalid recursive `#define`. This was immediately diagnosed from the real VC7.1 compiler errors; correcting the four macro definitions and recompiling the **whole source object** gives:

    scripts/repo-python scripts/replay-exact-units.py --unit character-aux-action-005fae30
    scripts/repo-python scripts/compare-coff-function.py --unit character-aux-action-005fae30 --json

**1/1 original full callable cold exact, 31,352/31,352 previously credited CODE B unchanged**. The independent original COFF comparison returns `exact`, including the physical game call/global relocations and all native `$L` local symbols. Only this affected source unit was rebuilt; no full 979-unit replay. Intermediate compiler failures and last accepted F1135 source snapshot are retained under ignored `.analysis/f1136-auxactor-native-phase/`. **Zero newly accepted whole exact original CODE bytes.**
