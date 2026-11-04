# F1135 — 31,352-byte complete CharacterAuxObject exact: 531 native X/Y position and motion borrows

The SHA-pinned Japanese TH075 v1.11 original has a previously accepted independently whole-byte-exact `CharacterAuxObject::AdvanceActionAt005FAE30` at `005FAE30`, **31,352 original callable CODE bytes** followed by separately accounted original afterRET jump data. F1135 changes its real C++ source, replacing **531 actually used float lvalues** with descriptive native-position/motion borrows while preserving the exact original machine code, the complete physically attributed COFF relocation list and **all original `$L` local jump-table symbols**.

| Real native actor memory window | Original source occurrences |
| --- | ---: |
| X position, actor+`0x44` (`F1135_POSITION_X()`) | **243** |
| Y position, actor+`0x48` (`F1135_POSITION_Y()`) | **244** |
| X motion, actor+`0x50` (`F1135_MOTION_X()`) | **20** |
| Y motion, actor+`0x54` (`F1135_MOTION_Y()`) | **24** |
| **All genuine source lvalues** | **531** |

Each accessor is a narrow, native-typed float-lvalue alias to **the exact original `FLOAT(0xNN)` macro expansion in this member function**. This is intentional: the source accesses always target the same `this` owner, so the aliases take **no receiver argument** and do not silently ignore an arbitrary passed pointer. The actual actor position and motion field offsets were independently corroborated by other previously full-original-exact frame/movement functions (F1037). The original `SpawnPeer` argument evaluation order, x87 expression grammar, exact first/last effect state and native input signedness are unchanged. No guessed whole owner class, extra local, struct allocation, runtime helper or target EXE patch is introduced.

## Why two apparently equivalent C++ refactors were rejected

The first genuine C++ attempt included `FrameActorMotionPairsF1037.hpp`, which introduces named structural types. The resulting *complete original* CODE/afterRET physical field positions remained consistent, but pinned VC7.1 renumbered **72 native jump-table/local COFF `$L` symbol references** (in the original 913-entry physical relocation list). Strict whole native COFF verification therefore correctly rejected it, even when its disassembled instruction mnemonics looked identical. A second attempt used four new float pointer dereference macros plus an unnecessary `<stddef.h>` header: the additional header changed the same native `$L` identities by six. Adding extra parentheses to a dereference also changed VC7.1 expression parsing and the generated function extent. These are actual rejected compiler tests preserved under ignored `.analysis/f1135-native-auxaction-31kb/`.

The selected solution keeps the original `FLOAT(offset)` expansion, adds only four macro aliases with meaningful native ownership, and **does not include `<stddef.h>` or any new struct declaration** in this exact translation unit. It preserves the complete original x87, GPR, branch and local COFF identity. This is not a relaxation of original-symbol acceptance: the entire exact unit was cold-compiled and the independent original COFF comparison returned `exact`.

Reproduce **only this affected complete original game callable**, not all 979 exact units:

    scripts/repo-python scripts/replay-exact-units.py --unit character-aux-action-005fae30
    scripts/repo-python scripts/compare-coff-function.py --unit character-aux-action-005fae30 --json

The final result was **1/1 whole exact, 31,352/31,352 previously accepted original CODE bytes preserved**, including every physical original relocation and `$L` identity; zero newly accepted entire original CODE bytes. The original executable hash and matching manifests are unchanged. Earlier failed source variants and serial normal VC7.1 COFF/PDB/build evidence are kept in ignored `.analysis/f1135-native-auxaction-31kb/`.
