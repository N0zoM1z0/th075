# F1053 — Preserve native FLD/FCOMP in the exact 130B combat-facing leaf

Pinned Japanese TH075 v1.11 original `CombatActor::UpdateFacingFromOpponent`
reads this actor's real float X at `+0x44`, compares with the opposing
actor's float X reached from the real borrowed pointer `this+0x2E8`,
then writes the actual signed facing byte `+0x66` if X differs. This
full source function is **130 original callable CODE B** and remains
exact only if the original x87 ordered comparison is preserved.

The original authored `BattleCombat.cpp` object also contains three
other separately accepted exact full functions: 1,982B ApplyHit,
1,877B ApplyConditionalHit, and 294B CalculateDamage. Together
all **four original complete callables total 4,283 exact CODE B**.

## Compiler-specific source evidence, not an assumed type cleanup

The original 130B facing method issues the authentic operand order:

- `MOV` the real other-actor pointer from receiver `+0x2E8`
- `FLD` this actor's X, then `FCOMP` the **memory** operand on the
  other actor's `+0x44`, with native `FNSTSW`, `TEST AH` and branch
- Repeat the corresponding check for the opposite facing direction

An initial real borrowed-four-field type refactor across the two
large combat methods left the full callable **machine CODE bytes
unchanged**, but added type declarations that renumbered strict
compiler-local COFF `$L` labels in their real postRET switch tables.
Those exact-unit comparisons **failed**. The earlier recognized F1027
label-shift negative was not ignored; the source was restored and the
failed trial preserved under ignored `.analysis/f1053-combat-borrow/`.
No manifest mask or relaxed label equality was accepted.

Next the exact facing leaf was named with two true local source
borrow expressions, rather than a new aggregate that changes compiler
symbol numbers. An apparently harmless **parenthesized** lvalue macro
turned one native `FLD/FCOMP` comparison into a `FLD/FLD/FCOMPP` pair,
changing actual expression lowering and emitting **134B/48 x86**
instead of the native 130B/46 x86. This is genuine code-generation
evidence: source parentheses can change the VC7.1 `/Od` x87 strategy,
even when the compared float values appear the same.

The final two *unparenthesized*, leaf-local expressions
`F1053_SELF_X` and `F1053_OTHER_X` carry actual observed receiver
fields without inventing a historical actor layout or helper call.
They preserve original source operand AST ordering, and a complete
strict native cold replay now returns:

| Entire native function | Cold exact |
| --- | ---: |
| `battle-combat-apply-hit` (1,982B) | exact |
| `battle-combat-apply-conditional-hit` (1,877B) | exact |
| `combat-actor-calculate-damage` (294B) | exact |
| `combat-actor-update-facing` (130B) | **exact** |
| **One affected translation unit** | **4/4 exact, 4,283/4,283B** |

The final `src/BattleCombat.cpp` source has **no new C++ class
definitions** before either larger function, preserving every real
compiler-local `$L` symbol as well as actual original CODE and call
addresses. The original input fields, player facing semantics and
return value are unchanged.

Reproduce only this complete affected object (all four units, not the
979-unit global corpus):

    scripts/repo-python scripts/replay-exact-units.py \
        --unit battle-combat-apply-hit \
        --unit battle-combat-apply-conditional-hit \
        --unit combat-actor-calculate-damage \
        --unit combat-actor-update-facing

No original exact function or byte count is newly accepted: this is
source-semantic cleanup **preserving existing exactness** and measured
negative compiler controls. No complete cold replay was run.
