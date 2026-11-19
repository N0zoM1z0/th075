# The 22 remaining giants

Every authored function that is not yet exact is the slot-1 `Advance` of one
of the 11 fighter or 11 character-object vtables: the per-frame state machine,
one big `switch (action)`, 28–83 KB each. Thirteen have a complete research
parent in `probes/` that compiles to the original instruction sequence apart
from register choice. The other nine have no complete parent yet.

Measure a parent with

    scripts/repo-python scripts/measure-giant.py [ADDRESS ...]

It cold-builds the parent with its recorded flags and compares its
`Advance` with the original instruction by instruction: mnemonic and width
differences, and positions whose general-purpose registers differ ("GPR
debt"), with the first such position. It is a diagnostic only. A giant
becomes exact only through a complete replay unit in `config/match-units.toml`.

`config/frontiers.toml` lists the parents (source, flags, symbol, original
extent and its SHA-256) with the byte offsets that still differ after
relocation fields are masked. After editing a parent, run

    scripts/repo-python scripts/check-frontier.py [NAME ...]

It fails if the body size changes or a byte that matched now differs.
Record an improvement with `--update NAME` and commit the file with the
source change.

## Complete research parents (measured 2026-11-15)

All thirteen have the original instruction count, frame, stack slots, branch
targets and mnemonics. What remains is register choice and the few
instruction widths that follow from it.

| Original | Character | Size | Parent | GPR debt | Widths | First GPR difference |
| --- | --- | ---: | --- | ---: | ---: | --- |
| 0045DD70 | Reimu fighter | 60,999 | `FighterWhole0045DD70F1183.cpp` | 6,311 | 5 | 0045FDA9 (#2292) |
| 004AC040 | Sakuya fighter | 82,796 | `FighterWhole004AC040F1020.cpp` (`/GX`) | 6,958 | 12 | 004ADEFA (#2180) |
| 005214B0 | Youmu fighter | 46,755 | `FighterWhole005214B0F1040.cpp` | 2,736 | 5 | 0052327A (#2103) |
| 00543210 | Remilia fighter | 58,294 | `FighterWhole00543210F1041.cpp` | 1,741 | 3 | 00545109 (#2198) |
| 004CA6E0 | Sakuya object | 42,511 | `CharacterObjectActions004CA6E0F1222.cpp` | 447 | 12 | 004CCBD7 (#2526) |
| 004EBDA0 | Alice object | 33,293 | `CharacterObjectActionsF572.cpp` | 133 | 0 | 004F344C (#8076) |
| 0050A580 | Patchouli object | 81,539 | `CharacterObjectWhole0050A580F1044.cpp` | 522 | 5 | 00515C0E (#10128) |
| 00536400 | Youmu object | 39,999 | `CharacterObjectActions00536400F1211.cpp` | 913 | 10 | 005392F8 (#3223) |
| 0055AC80 | Remilia object | 28,432 | `CharacterObjectWhole0055AC80F1194.cpp` | 726 | 6 | 0055F711 (#5225) |
| 0057D580 | Yuyuko object | 43,845 | `CharacterObjectActions0057D580F1237.cpp` | 914 | 6 | 00583489 (#6565) |
| 005A1600 | Yukari object | 43,599 | `CharacterObjectActions005A1600F1231.cpp` | 613 | 11 | 005A88A8 (#7965) |
| 005C9CC0 | Suika object | 43,501 | `CharacterObjectActions005C9CC0F1216.cpp` | 935 | 1 | 005D2558 (#9213) |
| 005EB520 | Meiling object | 34,434 | `CharacterObjectWhole005EB520F1207.cpp` (no `/GS`) | 135 | 6 | 005F3904 (#9200) |

The flags are `/Od /Ob0 /Gy /GR- /GX- /GS /Zi /I src /I probes` unless noted.
Sakuya object `004CA6E0` now defines `SakuyaObject::Advance` directly.
The original 42,511 CODE bytes are still nonexact (447 GPR-role and
12 width differences). Of its 929 COFF relocation records, 52 effect
spawns, 22 sounds and 13 tracked spawns now bind to the real
`Fighter`/`SakuyaFighter` interfaces. The parent body size, every
relocation offset/type and every nonrelocation instruction byte remained
unchanged; 24 header-affected exact units cold-replayed.

The Reimu fighter, Alice object and Meiling object research parents now
directly define `ReimuFighter::Advance`, `AliceObject::Advance`, and
`MeilingObject::Advance`, rather than artificial derived classes. Alice's 33,293-byte parent uses real `owner` and
`owner->opponent` fields (including named Fighter/AliceFighter members) in
place of raw offset macros, while preserving all 575 outstanding differing
bytes in its nonexact ratchet and its first register discrepancy at
`004F344C`. The change also cold-replayed all 24 exact functions affected
by `CharacterObject.hpp`. Native-call helper aliases retain provisional ABI
spelling until the target call signatures have been fully reconciled. The Meiling parent also calls
`Fighter::SpawnBattleEffect` directly through `owner` at all 93 effect-spawn
sites; its 34,434-byte frontier remains 985 differing bytes with 135 GPR
and six instruction-width mismatches in the late state machine. All 24
header-affected exact units cold-replayed.

Yuyuko object `0057D580` now defines `YuyukoObject::Advance`, with
66 effect spawns, eight sounds and four camera-shake calls moved from
borrowed owner declarations to shared game interfaces. Both 44,331-byte
research bodies have exactly 1,043 relocation positions/types and zero
nonrelocation byte differences. The 43,845 original CODE bytes remain
nonexact (914 GPR-role differences and six widths); all 24 affected
exact units cold-replayed. Other parents retain their historical names.


## Without a complete parent

Objects 00476A40 (Reimu, 50,915 B) and 0049C8F0 (Marisa, 46,596 B); fighters
00486550 (Marisa, 50,735 B), 004D7E70 (Alice, 43,601 B), 004F7130
(Patchouli, 44,211 B), 00564BE0 (Yuyuko, 61,872 B), 0058AF60 (Yukari,
49,230 B), 005AEEC0 (Suika, 71,616 B) and 005D73C0 (Meiling, 43,282 B).
`config/fighter-boss-dispatch-fingerprints.json` has their extents and jump
tables. Each fighter shares its switch grammar with the others, so a new
parent starts from the closest complete one plus the native case bodies.

## Why the register debt exists

At `/Od` VC7.1 reloads `this` for every member access and rotates the
scratch register eax → ecx → edx → eax from one load to the next. The
rotation carries across statements and through ordinary joins. Each giant's
debt is this rotation shifted by one or two steps from a single point
onwards, so one cause explains thousands of positions.

The shift starts at a join where the original takes the register state of
the **first** conditional jump into it instead of the fall-through state
(`.analysis/layout-tools/anomalies.py` lists such joins in an original).
Two shapes occur at the first-debt points:

- `if (animationStage < 3) { scaleX = … + g; scaleY = … + g; }` followed by
  `if (animationStage == 4)` (Alice 004F344C, Yuyuko 00586A25);
- `if (animationStage == 0 && animationFrame == 0) { …colours = 255…;
  velocityX = 0; velocityY = 0; }` followed by `if (animationStage == 1)`
  (Remilia object 0055F711, Suika 005D2558, Remilia fighter 0054F906).

The same shapes appear many times in every giant and behave normally
elsewhere (Remilia's object has nine such velocity-reset joins and only one
is anomalous). None of our builds produces such a join. These did not
change the state and are ruled out:

- spelling: `else`, extra braces, `goto`, `do {} while (0)`, comma
  expressions, inverted tests, nesting `if (A) { if (B) … }` instead of
  `A && B`, a one-pass `while`/`for` with `break`, line breaks, and placing
  the code inside a `switch` case;
- flags: `/Z7`, `/RTC1`, `/Oy-` and `/GX`. `/ZI` restarts the rotation at
  every statement but changes thousands of other instructions;
- compiling two giants in one translation unit;
- the join is never a jump-table target, and no shared instruction, label,
  call or `this`-reload count marks the anomalous positions.

Meiling object `005EB520`: 22 additional natural-C++ variants at the
`997`/`998` boundary at `005F3904` (condition polarity, guard/else,
scope, comparison order and facing assignment forms) did not reduce
whole-function differences. A plain `facing = owner->facing` produces
identical native bytes and is retained as the more natural C++ source.

Per-parent attempts that failed, kept so they are not repeated: loop-update,
return, condition and index rewrites in 005A1600; swapping 0057D580's
state-837 equality operands (reads the limit before the frame-progress call,
1,122 GPR); compound-update, bound, `/G7`, comma and indexed-expression
variants in 004CA6E0; chaining, DWORD/array/member/guard and `/Op` variants
in 0055AC80; typed float arguments in 0050A580 (raw DWORD transport of
coordinates and angles is required; typed arguments add 329 instructions).
The deleted per-checkpoint notes with full details remain in Git:
`git show 430a06a4:docs/<NOTE>.md` (list them with
`git ls-tree --name-only 430a06a4 docs/`).

Seven further natural-C++ source experiments at the Alice object join at
`004F344C` (inverse comparison, operand swap, compound assignment, empty
`else`, inverse `else`, explicit boolean, and conditional expression) did
not improve the native byte frontier. The inverse `else`, compound
assignment, and explicit boolean forms introduced new width/instruction
debt. The remaining lead is a construct that makes the join take the
first-jump register state without changing its other instructions.
