# TH075 knowledge base

Reusable findings about the original `th075.exe` (Japanese 1.11) and the
VC7.1 build 3077 compiler that rebuilds it. Current work and blockers are in
the [handoff](RE_HANDOFF.md); the 22 remaining giant functions have their own
page, [GIANTS.md](GIANTS.md). Everything here was observed on the original PE
or in a cold build; checkpoint numbers (Fnnn) point to the commit history.

The journal this page replaces (per-checkpoint notes F179–F1239, about 17,000
lines) is in Git: `git show 430a06a4:docs/KNOWLEDGE_BASE.md`. Most of it
described what each accepted function does, which the source and ledgers now
record. Consult it only for the full history of a specific checkpoint.

## Class structure

The PE vtables give the real hierarchy (`.analysis/layout-tools/vtables.json`
dumps them):

- `Actor` (`src/Actor.hpp`, 0x00–0xC3) is the base of every animated battle
  object; its shared helpers (0040FA30–0040FC50 and 00455500) are in
  `src/Actor.cpp`. Slots: 0 `BindAnimation` (fighters 00453D80), 1 `Advance` (pure),
  2 `Render` (fighters 00453F70), 3 `RenderNode` 00410350, 4
  `RenderMirroredNode` 00410A00. The vtable pointer is at +0.
- `Fighter : Actor` (`src/Fighter.hpp`, up to 0xF0F, `sizeof` 0xF10).
  Constructor 004567B0; the base table at 00658FE8 uses `_purecall`
  00641E19 for pure slots. Slots 5–19: 5 `~Fighter`, 6 `ResetRound` (base
  00457010), 7 `CreateOwnedObject`, 8 `ForwardBaseAction` (base 00451EB0),
  9 `RenderChain`, 10 `DispatchActions`, 11 `ChooseAction`, 12
  `ChooseCardAction`, 13 `PollCommands`, 14 `SelectVariant`, 15
  `ConfigureStage`, 16 `AdvanceSequence`, 17 `RenderStage`, 18
  `NoOpSlot18`, 19 `AdvanceAuxiliary`.
- `<Char>Fighter : Fighter` (`src/<Char>Fighter.hpp`, 11 classes) holds each
  character's overrides and its own members from +0xF10 (shorts in some
  characters, floats in others). The constructors live in
  `src/<Char>Init*.cpp`.
- `CharacterObject : Actor` (`src/CharacterObject.hpp`, constructor
  0045B760, base table 00659064, `sizeof` 0xE8) is each character's effect
  object: `sequences` at +0xC4, floats +0xC8–0xD0, shorts +0xD8–0xE2 and
  the owning `Fighter*` at +0xE4. Object tables have five slots and no
  destructor. `<Char>Object` constructors are in
  `src/CharacterObjectConstructorsF422.cpp`.

Slot 1 of the 22 character tables is the per-character `Advance`. These are
exactly the 22 authored functions still not exact:

| Character | Fighter Advance | Object Advance |
| --- | --- | --- |
| Reimu | 0045DD70 | 00476A40 |
| Marisa | 00486550 | 0049C8F0 |
| Sakuya | 004AC040 | 004CA6E0 |
| Alice | 004D7E70 | 004EBDA0 |
| Patchouli | 004F7130 | 0050A580 |
| Youmu | 005214B0 | 00536400 |
| Remilia | 00543210 | 0055AC80 |
| Yuyuko | 00564BE0 | 0057D580 |
| Yukari | 0058AF60 | 005A1600 |
| Suika | 005AEEC0 | 005C9CC0 |
| Meiling | 005D73C0 | 005EB520 |

Several old labels were wrong: "Boss 0050A580" is Patchouli's object, and
004AC040 is Sakuya's fighter. A correctly named override and a wrongly
attributed one emit the same bytes, so check the vtable slot before naming
a method.

## Layout facts

- The controller binding block is embedded at +0x494. `SetBindings` copies
  40 bytes at +4 and clears 28 at +0x2C, so the block spans 0x48 bytes and
  ends where `inputX` (+0x4DC) begins. Held input is at +0x4DC–0x4F4 (X, Y,
  ?, A, B, C, D) and a buffered copy at +0x4F8–0x50C. An attack press is
  `inputA == 1 || bufferedA > 0`.
- `RecordRoundFields` (004574D0) fills arrays at 0x32A, 0x33E, 0x370 and
  0x384 (20 entries each) and at 0x3D0, 0x400 and 0x430 (12 each), and raises
  +0x39D to the highest index used. +0x39D is therefore not a selected card,
  as an older macro name claimed.
- +0x74/+0x78 point to the current frame record (`flags` at +0x3C; bit 0x20
  gates action changes) and the current sequence record (`priority` at
  +0x12). Candidates from `sequenceSlots.At()` (004420B0) compare
  `targetPriority` at +0x10.
- `ConfigureStage` (slot 15) is the story-mode stage setup. It zeroes four
  per-character bytes right after the shared layout (Reimu, Suika and
  Meiling +0xFF4, Remilia +0xFD8, Patchouli and Yuyuko +0xFDC, Sakuya, Alice
  and Youmu +0xFE0, Marisa and Yukari +0xFFC).
- +0x04 is the sprite drawing context (an object copies its owner's) and
  +0x08 the frame record the node renderers draw; the object renderer
  (0040FC70, `CharacterObject::Render`, object slot 2) and the shared
  `Actor::RenderNode` (00410350) and `RenderMirroredNode` (00410A00, slots
  3–4) read them. The frame record's pose (+0x08 of the frame) holds the
  blend mode, ARGB colour, a 3D offset, scale and rotation.
- +0xA8–0xC3 is a collision snapshot that `Actor::SaveCollisionFields`
  (00455500) copies each frame before hits are resolved: +0x7C, both record
  pointers, the action, x and y (as raw DWORDs) and the facing. Hit tests
  read the snapshot (`savedFrameInfo` etc.), not the live fields. It ends at
  +0xC4, where `Fighter::name` and `CharacterObject::sequences` begin.
- The frame record (`FighterFrameInfo`) holds the sprite origin, texture
  index and a pose pointer (+0x00–0x0C, read by the renderers), the hit data
  (+0x10 damage, +0x14 combo-rate factor, +0x1C/+0x1E attacker and defender
  hit-stop, +0x24 card-gauge gain, +0x36 hit effect, +0x3C defence flags,
  +0x40 attack flags) and the collision boxes (+0x44 body box, +0x54 hurt
  boxes, +0x64 hit boxes, each a 16-byte vector of RECTs).
- Fighter gauges: +0x3B0 `spirit` (specials need it, guarding drains it, at
  0 the fighter is guard-crushed into state 143), +0x368 `cardGauge` (float,
  filled by hits, capped at 2000), +0x3C0 `comboRate` (each hit multiplies
  it by the frame's factor), +0x2D0 `score` (100–500 per hit). Older names
  called +0x3B0 a meter.
- In combat functions the attack is an `Actor` (fighter or object) and the
  attacker and defender are `Fighter`s; `Fighter::CalculateDamage(attack)`
  (00455640) is the attacker's damage against its opponent.

## VC7.1 `/Od` code generation

### x87 operand order

- The compiler orders x87 loads by expression shape. In `x = x * g` with a
  member `x` it loads `g` first; `x = (x) * g` loads the member first. A
  parenthesized operand, or a parenthesized dereference, is evaluated first.
  A bare dereference behaves like a plain member, and member-op-member keeps
  source order. When a converted float expression stops matching, try
  parenthesizing the operand the original loads first [004F4170, 00536400].
- `*(&a) + *(&b)` on float members keeps the original MOV/MOV/FLD/FADD order
  where a plain sum reorders the FLD; `(*(&p))*global` keeps FLD then FMUL
  (fighter research parents).
- `member + 20.0f` with a right-hand literal emits `FLD [member]` then
  `FADD [const]`; hoisting the constant into a variable loads it first.
- Float arguments passed by value add an `FLD/FSTP` pair. Some originals push
  the raw float bits with `MOV/PUSH` instead (sprite call 00453C80). The
  originals' source for that transport is not known; typed float lowering
  was tried in the 0050A580 parent and adds 329 instructions.

### Register rotation and joins

- At `/Od` the compiler reloads `this` from its stack slot for every member
  access and cycles the scratch register eax → ecx → edx → eax from one load
  to the next. The cycle continues across statements and at most joins.
- At a handful of joins the original instead takes the register state of the
  **first** conditional jump into the join (for `A && B`, the state after
  testing `A`). Those joins sit exactly where each giant's register debt
  starts. No source spelling, flag or context reproduces them yet; see
  [GIANTS.md](GIANTS.md).
- `/ZI` (Edit and Continue) restarts the cycle at every statement but changes
  thousands of other instructions, so it is not the originals' setting. `/Z7`,
  `/RTC1`, `/Oy-` and `/GX` do not affect the cycle.

### Conditions and loops

- The compiler keeps comparison constants literally: `i < 37` emits
  `cmp 37 / jge`, while an original `cmp 36 / jg` needs `i <= 36`.
- An unsigned `Count() <= 0` emits `ja`; `Count() == 0` emits `jne`.
- The fall-through branch of an `if` is the first block in the code. To
  reproduce `cmp scale,1; je rotated; …; jp rotated`, write
  `scale != 1 && angle == 0` with the unrotated path first (sprite drawing
  0040D2E0).
- `for (; it != end; ++it) (*it)->Dispatch();` keeps the iterator update at
  the loop end; the `while` form with a named element local adds a slot and
  two bytes.
- A combined short-circuit guard plus `switch (member)` reproduces the
  giants' dispatch prologue; copying the action into an `int` local first
  adds a slot.

### Stack slots and locals

- Local slot order follows declaration and scope, not use. When locals land
  in the wrong slots, reconstruct the original lifetime graph (which
  temporaries live in which nested scopes) instead of renaming variables.
  Scoped lifetimes fixed the 0x24-byte frame of the config reader F259 and
  the quad/RECT order of the scene renderer (outer quad, inner RECT).
- Variable names can change slot assignment, but a name sweep without a
  lifetime model rarely converges.
- Passing a typed null pointer rvalue to a `T* const&` parameter creates the
  original's temporary slot; a named `empty` local does not [F294].
- Root-scope resources and const-reference construction values recover the
  WinMain frame (00602A60, F1171).

### Allocation and deletion

- A CRT destination does not identify the source call: 0064169D and
  00640F15 are bound to scalar and array delete as well as `free`. Pair each
  deallocation with its allocation. `delete[]` of `new char[]` names and
  scalar `delete` of objects fixed the slot rotation in the ArchiveCatalog
  destructor 0041CE50 and the BattleScene destructor 0043B0B0, where `free`
  with named cleanup locals rotated the temporaries.
- A true C++ array of objects with constructors under `/GX` emits
  `_ehvec_ctor` (00641C78) and its unwind entries.

### Integer widths and immediates

- `++shortMember` emits a 16-bit `mov/add`; promoting through an `int`
  temporary emits `movsx`.
- `PUSH 0xFF` (five bytes) comes from an unsigned char 255 argument;
  `PUSH -1` (two bytes) from a signed -1. Match the callee's declared
  parameter type.
- A byte array local triggers a `/GS` cookie that a DWORD array does not
  (audio stream queue 00407A50).
- `reinterpret_cast<signed short&>(m)` on a `short` member is a no-op.

## Conversion pitfalls

- A parameter named like a member shadows it (`BindOpponent` compiled to
  `opponent = opponent`); the replay caught it.
- VC7 `$L`/`$SG` label counters change with unrelated source text, so the
  comparator checks local labels by destination, not name.
- Calls to a base implementation through a cast must be qualified
  (`Fighter::ResetRound()`) to stay direct calls.
- Converting a file is proven by building it before and after and comparing
  every code section and relocation (`.analysis/layout-tools/objsig.py`,
  with a rename map for changed symbols), then cold-replaying the affected
  units.
