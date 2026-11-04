# F1139 — Five real fighter scale/rotation float fields across 318 uses, whole 31,352B auxiliary original exact

The SHA-pinned Japanese TH075 v1.11 original independently authored `CharacterAuxObject::AdvanceActionAt005FAE30` is one previously complete byte-exact **31,352 CODE B** callable at `005FAE30` with separately accounted afterRET switch DATA. F1139 replaces **318 real scale/rotation float lvalues** in this *entire* C++ function with five physical borrowed field names, retaining full original machine CODE, COFF physical fields and all original `$L` local switch labels. The accepted exact original function remains 1/1, and no other exact units are rebuilt.

The five actual actor fields are anchored in independently verified complete exact fighter transform/render source (`FighterRenderTransformWindowF1094`), not a guessed full historic actor class. The same physical window at actor+0x1C/+0x20 is the signed float scale X/Y pair; actual actor+0x28/+0x2C/+0x30 are the three physical rotation/angle floats. Many different game effects use these angles differently, so the selected aliases use physical offset names where historic effect-specific semantics are uncertain, rather than asserting an undocumented 3D rotation owner.

| Real actor lvalue | Native source borrowing alias | Number of original uses |
| --- | --- | ---: |
| Original `float` at actor+0x1C | `F1139_SCALE_X()` | **123** |
| Original `float` at actor+0x20 | `F1139_SCALE_Y()` | **122** |
| Original `float` at actor+0x28 | `F1139_ROTATE_AT28()` | **13** |
| Original `float` at actor+0x2C | `F1139_ROTATE_AT2C()` | **14** |
| Original `float` at actor+0x30 | `F1139_ROTATE_AT30()` | **46** |
| **Five physically genuine native float fields** | — | **318** |

The source includes no new C++ struct definition: the selected `this`-owner named macros expand to the original exact `FLOAT(0xNN)` grammar used by the VC7.1 compiler. This is critical for a 31KB original switch: F1135 experimentally established that introducing new struct definitions or `<stddef.h>` before the function silently changes the compiler `$L` COFF label numbering, even when all original code bytes and relocation offsets appear correct. Instead, these lvalues preserve the original x87 expression order and complete physical local symbol identity, with all macros `#undef` after the function. No forced stack locals or byte patches are used.

The targeted native original cold replay and independent COFF compare after changing the complete unit returned:

    scripts/repo-python scripts/replay-exact-units.py --unit character-aux-action-005fae30
    scripts/repo-python scripts/compare-coff-function.py --unit character-aux-action-005fae30 --json

**1/1 original entire callable exact, 31,352/31,352 original CODE B retained**, all physical genuine PE fields and `$L` names unchanged. Together with F1135's 531 position/motion float borrows and F1136's 484 signed stage/frame/animation/tick WORD borrows, the same original native code now has **1,333 actually typed original field uses** across these three independent commits. The original game executable and matching manifests are unchanged; the intermediate selected F1136 exact source and fresh native compiler receipts are kept under ignored `.analysis/f1139-auxactor-native-transform/`. **Zero newly accepted whole-original exact CODE bytes, no full 979-function replay.**
