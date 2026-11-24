# TH075 knowledge base

Reusable findings about the original `th075.exe` (Japanese 1.11) and the
VC7.1 build 3077 compiler that rebuilds it. Current work and blockers are in
the [handoff](RE_HANDOFF.md). [GIANTS.md](GIANTS.md) records the
Advance parents and compiler evidence. Everything here was observed on the original PE
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
- Fighter command-selection state uses `field47C` (+0x47C) and the
  associated sprite-sequence pointer at +0x480. `SetCommandSelection`
  (00454BC0) writes the selection and updates the sequence sampling/color
  policy. The adjacent 24-byte leaf at 00454C00 is now reconstructed as
  `Fighter::ClearField47CAt00454C00`; it is a natural member store of zero
  to +0x47C and cold-replays exactly. Its address-anchored name is retained
  because no static references to this leaf were found.
- `CharacterObject : Actor` (`src/CharacterObject.hpp`, constructor
  0045B760, base table 00659064, `sizeof` 0xE8) is each character's effect
  object: `sequences` at +0xC4, floats +0xC8–0xD0, shorts +0xD8–0xE2 and
  the owning `Fighter*` at +0xE4. Object tables have five slots and no
  destructor. `<Char>Object` constructors are in
  `src/CharacterObjectConstructorsF422.cpp`.

Slot 1 of each character table is the per-character `Advance`.

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

`BattleScene` (`src/BattleScene.hpp`, vtable 00658334: slot 0 the
deleting destructor, 1 `Update` 0043B1B0, 2 `Render` 0043D9D0) owns the
match. Its methods run from 0043AD10 to 00449310, interleaved with a few
  helpers of the progress records and combo counters. Members: +0x08 the
  texture manager, +0x0C frame timer, +0x18 match mode, +0x34 hit bounds,
  +0x44 the two fighters, +0x4C digit atlas, +0x50 the two combo counters,
  +0x58 the active counter, +0x5D/+0x5E winner and quote line, +0x60/+0x64
  notice timer and state, +0x70–0x88 overlay values, +0xA4 each side's saved
  input state, +0xDC–0xF3 per-side status values.

## Layout facts

- Youmu has an independently observed 0xFF8-byte fighter allocation
  (`BattleCharacterLoaderF398`, character 5). The VC7.1 12-byte
  `std::list<ObservedInputSnapshotF378>` member at +0xFEC is the final
  member, after an unobserved +0xFE4..+0xFEB gap. The snapshot is 16 bytes:
  action/stage shorts, float x/y, facing byte and bearing short. Its automatic
  construction, clearing, auxiliary writer and object `Advance` reader retain
  the original method call destinations (00531C00, 00531CE0, 00531CB0,
  00540220). Affected exact units cold-replayed 81/81; the 39,999-byte
  object giant remains nonexact with its full 40,464-byte COFF unchanged.
- The bound fighter's effect manager at +0x2EC occupies 0x54 bytes: its
  bound `Fighter*` and four 20-byte VC7.1 deque members. Effect advance
  (0045BDB0) and both drawing dispatchers (0045BC30, 0045BCE0) now use
  named typed deque members, inherited `Actor` virtual slots and native
  effect flags. `BattleScene::Update` (0043B1B0) invokes all four per-frame
  effect ticks through this manager. The three effect functions cold-replay
  3/3 and the frame/header-dependency set cold-replays 74/74.

- The controller binding block is embedded at +0x494. `SetBindings` copies
  40 bytes at +4 and clears 28 at +0x2C, so the block spans 0x48 bytes and
  ends where `inputX` (+0x4DC) begins. Held input is at +0x4DC–0x4F4 (X, Y,
  ?, A, B, C, D) and a buffered copy at +0x4F8–0x50C. An attack press is
  `inputA == 1 || bufferedA > 0`.
- +0x53A–0x6CC hold the win quote: the line count, two 200-byte lines from
  +0x53B and a notice badge per line from +0x6CB.
- The fighter constructor (`FighterInitF287.cpp`, base `Actor` 00458650)
  constructs embedded objects in this order: a 0x194-byte block at +0x2D4,
  the sequence slots at +0x468 (0x2C bytes), the input object at +0x494
  (0x84 bytes, the bindings are its first 0x48), a 0x1B8-byte history
  deque at +0x518, a sound object at +0x6D0 and the script reader at
  +0x714. The constructor then allocates the object manager at +0x2EC and
  clears +0x04, +0x534 and +0x700. Open question: a 0x44-byte sound object
  would cover +0x6E4–0x713, which other code uses as fighter fields (the
  notice and script words); one of the two readings is wrong.
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
  boxes, +0x64 hit boxes, each a 16-byte vector of RECTs). The
  The hurt/hit members are now declared directly as
  `std::vector<tagRECT>`, so collision dispatch emits the native VC7.1
  `vector::size()` / `vector::at()` symbols at 004452D0 / 00445310.
  `FighterFrameInfo::operator=` at 0045AAE0 cold-replays its
  full 368-byte body and both vector-assignment relocations (0x151/0x163)
  to 0045AC50. The 381-byte `std::vector<RECT>::operator=` at 0045AC50
  also cold-replays with all 17 relocations. These compiler/library-origin
  functions remain excluded from authored exact coverage.
- Fighter gauges: +0x3B0 `spirit` (specials need it, guarding drains it, at
  0 the fighter is guard-crushed into state 143), +0x368 `cardGauge` (float,
  filled by hits, capped at 2000), +0x3C0 `comboRate` (each hit multiplies
  it by the frame's factor), +0x2D0 `score` (100–500 per hit). Older names
  called +0x3B0 a meter.
- In combat functions the attack is an `Actor` (fighter or object) and the
  attacker and defender are `Fighter`s; `Fighter::CalculateDamage(attack)`
  (00455640) is the attacker's damage against its opponent.

## Game progress (save data)

The progress object (`g_BattleRecords`, 26 methods on about 18 alias
classes such as `ProgressRecordsF274`, `CardProgressF172`,
`SelectedProgressF174`) has a regular layout:

- 15 character blocks of 0x17F0 bytes from +0, each 4 difficulty blocks of
  0x5FC bytes. A difficulty block ends with 10 ranked scores of 16 bytes at
  +0x55C (8 name bytes, a DWORD, the score at +0xC; the lowest score sits
  at +0x5F8). `ProgressRankingF375::InsertRankedScore` (00416EE0) works on
  one difficulty block. +0x04 of a block counts selections and +0x556 is
  read by the single-player options.
- +0x16710: a 15×15 int table of mode counters; +0x16A94: 8 bytes (100
  each by default); +0x16A9C: 40 bytes of unlock bits; +0x16AC4/+0x16AC5:
  the selected fighter and difficulty; +0x16AC6: 256 bytes saved with the
  scores.

`src/GameProgress.hpp` declares this layout and 27 of its methods.
Nested indexing `characters[f].difficulties[d].x` compiles exactly like the
left-to-right sum `this + f*0x17F0 + d*0x5FC + off`, but not like
`this + (d*0x5FC + f*0x17F0)`: VC7.1 evaluates a parenthesized offset sum
before adding the base, in a different instruction order.
`IncrementSelectedRecordCount` (0041A270) needs that grouping and keeps it.

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
- In the pinned VC7.1 back end the local scratch search reads its cursor
  at `108A7D0C` and advances it at `10776893`. The Meiling object
  comparison shows that the choice can carry across independent switch
  arms. Removing one real update in action 997 moves the first reload
  in the untouched action 998 from EDX to EAX. Compare the cursor
  before selection alongside the emitted register and follow the case
  entries through the jump table. [Meiling compiler trace and replay](GIANTS.md#2026-11-23--meiling-action-998-inherits-the-scratch-register-cursor)
- VC7.1 can allocate a condition's operands before removing an empty
  branch. Alice action `0x38D` consumes two register choices for its
  empty stage-3 path. Meiling's explicit in-progress stage path in
  997 restores the original EAX at action 998 with the original frame,
  calls, and exits. Both functions cold-replay exactly.
  [Measured controls and complete comparison](GIANTS.md#cross-check-with-alices-eliminated-stage-test)
- A complete object can have multiple independent joins with the same
  symptom. Suika's later startup frames in actions 918, 928 and 929
  restore three successive register choices. The first change exposes
  the second, and the second yields matching table offsets while 106
  instruction bytes still differ in 929. Compare the complete extent
  after each change. [Suika controls](GIANTS.md#2026-11-24--suikas-three-startup-joins-cold-replay-exactly)
- The native dispatch can reveal repeated calls and distinct state
  bodies even when the decompiler flattens their control flow. Marisa
  object action 812 has 13 identical clear effects, and actions
  828–833 each dispatch to their own three-instruction call block.
  Match the call count and switch targets before comparing registers.
  [Marisa object replay](GIANTS.md#2026-11-24--marisas-object-advance-cold-replays-exactly)
- VC7.1's `/FAcs` listing ties otherwise identical epilogue jumps to
  source lines. In Reimu's object Advance, 59 direct jumps to the shared
  return had been routed through individual case tails. Explicit
  returns restore their destinations without changing instruction
  counts. Check the listing build's section and relocations against the
  ordinary object before using its line labels.
  [Reimu object comparison](GIANTS.md#2026-11-24--reimus-object-advance-cold-replays-exactly)
- An eliminated condition can change registers between two consecutive
  statements. Sakuya's explicit later startup frames in action 808
  restore the first reload for the bounds check after a matching
  counter increment. An empty floating-point boundary test at that
  position still emits its x87 comparison.
  [Sakuya controls](GIANTS.md#2026-11-24--sakuyas-arena-bounds-check-cold-replays-exactly)
- A register difference at an action entry can originate in the
  preceding action's completion path. Patchouli's `0x357` and
  `0x3E5` end with a completion check and two matching exits in both
  builds. Explicitly expressing the in-progress path in each restores
  the register choices at the next action entry.
  [Patchouli controls](GIANTS.md#2026-11-24--patchoulis-object-advance-cold-replays-exactly)
- A register change can shorten some instruction encodings and lengthen
  others. Yukari's explicit unfinished-animation path in 908 restores
  eleven instruction widths across the complete object. The matching
  body grows by three bytes with the same instruction count.
  [Yukari comparison](GIANTS.md#2026-11-24--yukaris-object-advance-cold-replays-exactly)
- When two actions have the same stage-change guard, compare the later
  join after correcting the earlier one. Youmu's explicit stage-14
  continuation in action 829 exposes the corresponding join in 906.
  Both changes together reproduce the full function and switch layout.
  [Youmu controls](GIANTS.md#2026-11-24--youmus-object-advance-cold-replays-exactly)
- Recheck similar growth and fade actions after the first register join
  is fixed. Alice's stage-3 hold also matches Yuyuko actions 911 and
  914. Before that pattern surfaced, the ongoing animation path in
  Yuyuko action 837 restored instruction widths and all dispatch offsets.
  [Yuyuko controls](GIANTS.md#2026-11-24--yuyukos-object-advance-cold-replays-exactly)
- An empty stage branch can affect register choices in later cases. In
  Remilia's fighter `Advance`, the preparation branch before the
  descent test in `0x2F0` restores the last 1,203 GPR operands after
  three earlier action joins are fixed. Confirm later cases before
  changing them individually.
  [Remilia controls](GIANTS.md#2026-11-24--remilias-fighter-advance-cold-replays-exactly)
- Track the first differing instruction alongside the byte count while
  recovering adjacent actions. Explicit late landing frames in Youmu's
  `0x5D` move the first difference into `0x5E` even as a width change
  nearly doubles the total. The matching path in `0x5E` recovers the
  affected action.
  [Youmu fighter controls](GIANTS.md#2026-11-24--youmus-fighter-advance-cold-replays-exactly)
- When instruction alignment is lost, pair action bodies through their
  jump-table entries. Reimu's eight consecutive special actions expose
  an inverted firing guard, skipped per-projectile field writes, and
  x87 operand order differences. Fixing those actions restores global
  instruction alignment and lets the launch continuation be tested.
  [Reimu comparison](GIANTS.md#2026-11-24--reimus-fighter-advance-cold-replays-exactly)
- Repeated actions can each need the same continuation branch. In
  Sakuya's fighter `Advance`, expressing the repeat limit in `0x1F8`
  and `0x1F9` affects thousands of later operands. Applying the same
  path at the corresponding join in `0x1FA` closes the entire function.
  [Sakuya fighter controls](GIANTS.md#2026-11-24--sakuyas-fighter-advance-cold-replays-exactly)
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
