# F1063 — Two genuine actor/HUD pointer windows and exact collision control

Pinned Japanese TH075 v1.11 original `BattleActiveCollision` stores
exactly two 32-bit actor pointers in consecutive native owner fields
**+0x44/+0x48** and two real `ComboDisplay` pointers at
**+0x50/+0x54**. Their positions, their indexed access and original
`CollisionActor::SaveCollisionFields` / `ResolveBodyContact` /
`ResolveAttackHitboxes` call order are independently demonstrated
by complete native `ResolveActiveCollisions()` (1,249 original CODE
bytes), not just former C++ naming. The intervening owner+0x4C
storage remains **unknown**; it is not declared as a fictitious
member, padding for stack layout or a hidden owner pointer.

Before F1063, the whole source used two unrelated raw casts
`reinterpret_cast<CombatActor**>(this+0x44)[index]` and
`reinterpret_cast<ComboDisplay**>(this+0x50)[index]`, hiding the
actual source's two naturally grouped two-player arrays.
`ActiveCollisionActorPairF1063` and
`ActiveCollisionDisplayPairF1063` now represent just the real **8B
borrowed array windows** with two native 32-bit pointers each.
No source allocates, embeds or claims a complete historical
`BattleActiveCollision` owner. Static constraints check both true
8-byte array extents, 32-bit pointer size and original start offset.

The current file also uses two real independently verified fighter
views already backed by other accepted complete original callables:

- `F1027_TIMERS(attack).wordAt80`: exactly the native signed
  action-associated WORD decremented in **six original guard,
  special-contact and body-contact gameplay paths**. The adjacent
  genuine +0x82 state timer is not invented as an extra use.
- `F999_VITAL(ACTOR(i)).currentAt324`: the real fighter current
  signed 16-bit health used by the *actual* nested active actor
  iteration to copy the genuine original snapshot at actor+0x328.
  That snapshot remains an independently observed, directly
  addressed original field, not a falsely declared adjacent vital.

The real iterative C++ `std::deque<CombatActor*>` loops, original
4 active input lists, real used iterators, indexed actor/HUD
selection and all authentic collision calls retain exactly their
original control-flow and source expression order. C++ source uses
native borrowed types only; no forced register lifetimes, padded
structs, byte patches or invented CODE were introduced.

## Original whole-callable local verification

Initial VC7.1 compiler trials found that the pinned MSVC7.1 cannot
constant-evaluate an `offsetof` expression with `actors[1]` as its
member argument. This was corrected as a **real source compatibility**
issue: the member's genuine base offset must be zero, the pointer
must be 4 bytes in the pinned 32-bit profile and C++ arrays guarantee
element 1 begins exactly four bytes after element 0. The header is
not made less strict about the physical 8B native window.

After that compatibility fix, the actor/HUD typed views passed
**full original strict cold exactness**. Further independent
changes to the already demonstrated +0x80 action WORD and
+0x324 health field were each built and replayed against the
**entire affected `src/BattleActiveCollision.cpp` translation
unit**, not just the modified subexpression or loop body.

| Complete original game callable | Native original CODE B | Cold exact |
| --- | ---: | --- |
| Active collision loop | 1,249 | exact |
| Guard collision reaction | 219 | exact |
| Special hit reaction | 280 | exact |
| Contact hit reaction | 239 | exact |
| `FighterState::IsState50To149` | 58 | exact |
| **Complete affected source object** | **2,045** | **5/5 exact** |

The final pinned normal VC7.1 `/Od` source compiler preserved every
accepted original function's full CODE, exact call/global COFF
relocations, original switch/iterator-control data and original
member receiver behavior. The emitted original game byte credit
remains **previously accepted 2,045B**, not new coverage.

Replay exactly the affected complete callables only:

    scripts/repo-python scripts/replay-exact-units.py \
        --unit battle-active-resolve-collisions \
        --unit battle-collision-resolve-guard \
        --unit battle-collision-resolve-special-hit \
        --unit battle-collision-resolve-contact \
        --unit fighter-is-state-50-to-149

No original EXE alteration, COFF identity masking, mass cold replay
or independent new complete game callable acceptance was used.
