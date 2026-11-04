# F1079 — Native 2-player collision dispatch action WORD, frame flags and in-place RECT

The pinned Japanese TH075 v1.11 original source object
`BattleCollisionDispatch.cpp` contains **three independently accepted
complete exact game callables**, not cropped switch cases:

| Complete native original function | Original exact CODE B |
| --- | ---: |
| `BattleCollisionDispatch::ResolveAttackHitboxes` | **975** |
| `BattleCollisionDispatch::ResolveBodyContact` | **897** |
| `CollisionActor::SaveCollisionFields` | **118** |
| **One entire affected source-object proof** | **1,990** |

F1079 gives actual independently original PE-backed field uses
correct narrow borrowed names, without changing their native types,
owner pointers or original control-flow ordering:

- The real actor+`0x80` signed **action-associated WORD** is already
  independently established by the [`F1027` action/timer pair](../src/FighterActionTimerPairF1027.hpp).
  Original ResolveAttackHitboxes tests it and ResolveBodyContact
  independently checks/decrements both real actors' WORDs in response
  to genuine body contact. Selected source now borrows
  `F1027_TIMERS(actor).wordAt80` directly, no dummy state timer use.
- The real collision **frame flag DWORDs** at frame+`0x40` and +`0x3C`
  are reached through actual actor+`0xAC` frame pointer. Named
  `F1079_ATTACK_FLAGS` and `F1079_DEFENSE_FLAGS` preserve their
  independent owner (the frame, not the actor), original masks
  `0x400000`, `0x80`, `0x2000`, `0x800`, `0x1000` and the native
  repeated predicate order. They do not speculate on other frame
  fields or a complete historical frame structure.
- The battle collision owner's **four adjacent signed 32-bit bounds**
  at `this+0x34..0x40` are a real in-place native **16-byte RECT**
  window. `F1079_BOUNDS(this).left/right/top/bottom` replaces four
  unrelated raw integer casts in the authentic contact midpoint X/Y
  computation; it neither allocates nor introduces a pointer stored
  at `this+0x34`.

The actual 4×5 attack/defense collision rectangles, 6×6 body-contact
rectangles, legitimate loop index lifetimes, 20-element collision
matrix and exact original hit/contact dispatch remain native-shaped.
No cast on actual game-visible byte addresses was widened, and no
assembler, artificial register lifetime, byte patch or relocation
mask was used. Compile-time MSVC7.1 existing Win32 `RECT` and the
already-proven F1027 borrowed view are reused, not guessed owners.

## Strict original full-callable cold replay

Two consecutive normal pinned VC7.1 object rebuilds were performed
*only* for the affected source translation unit: first introducing
the verified action WORD and then the frame-flag/RECT borrowed
windows. After each step, `replay-exact-units.py` checked **all three
complete original functions**, not just the edited subexpressions.
Both full replays returned **3/3 exact**, with all original native
machine CODE bytes and actual COFF field identities unchanged.

Reproduce only this one changed source object:

    scripts/repo-python scripts/replay-exact-units.py \
        --unit battle-collision-resolve-attack-hitboxes \
        --unit battle-collision-resolve-body-contact \
        --unit collision-actor-save-collision-fields

There are **zero new original whole exact game bytes or functions**;
the prior **1,990 accepted exact original CODE B** remain intact.
No complete 979-unit cold replay, Japanese original EXE mutation,
manifest relaxation, cropped-code acceptance or invented source owner.
