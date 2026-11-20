# TH075 handoff (2026-11-20)

Follow [AGENTS.md](../AGENTS.md) first. This handoff is the live task summary;
[GIANTS.md](GIANTS.md) contains the complete-parent measurements and the
remaining compiler investigation. The user reports no other active sessions.
Inspect Git before editing and continue all work in the registered repository.

## Live state

The current status command is:

    scripts/repo-python scripts/report-reconstruction-status.py --summary

Snapshot checked on 2026-11-20:

- 4,351 candidate functions: 986 mapped/source-present/exact, 1,008 authored,
  90 origin-review candidates, and 3,253 excluded.
- 986 exact functions, 871,717 original CODE bytes, across 986 match units.
- Authored coverage is 44.17% of 1,973,772 bytes. Conservative coverage is
  44.09%, including 3,315 pending-origin bytes.
- The 22 remaining authored functions are all slot-1 Advance methods on the
  11 fighter and 11 character-object vtables. They total 1,102,055 CODE bytes.
- The 98% authored-byte goal is not met.

The historical R263 matrix is not the live origin queue. Its 97 rows /
3,608 bytes remain historical evidence; the current ledger has 90 review
candidates / 3,315 bytes. Use config/function-origins.csv as the authority.

The working tree was clean after four new reconstruction checkpoints on
main; those commits have not been pushed. Recheck Git state before editing.

## Recent reconstruction work

- Marisa fighter boss `0x00486550` now has a tracked typed partial source in
  `probes/MarisaFighterAdvancePartial.cpp`: 158 native action-state bodies,
  inherited named fields/methods, no offset casts or marker placeholders.
  The latest nested handlers `0x12C`, `0x1F4`, and `0x2C2` add 1,147 original
  bytes. All 141 unique top-level Ghidra action labels and all 158 explicit
  in-parent handler groups have source coverage; the shared default handler
  is represented by the source default path. Its 51,924-byte/14,842-
  instruction VC7.1 object is explicitly NONEXACT against the 50,735-byte /
  14,260-instruction original. The 1,189-byte / 582-instruction difference
  remains unaccepted; this is not an exact-credit claim.

Current focused source recoveries (2026-11-20):

- `91951cb2` and `933e13af`: the native 0x54-byte four-deque effect owner now
  has typed advancing and dispatching views. The `Actor` virtual render slots,
  frame pointer at +0x74 and dispatch flags +0x67/+0x68 replace raw pointer
  arithmetic in three complete functions (296, 166 and 207 bytes); 3/3 cold
  comparisons pass with complete relocations.
- `1caedf6b`: Youmu's actual +0xFEC member is a 12-byte VC7.1 `std::list`
  of 16-byte action snapshots, ending at the independently observed +0xFF8
  allocation bound. The class constructor now automatically constructs the
  native member, and reset explicitly clears it. Both exact owners, the
  1,008-byte snapshot writer and all their header-dependent callers replayed
  81/81. The complete 40,464-byte Youmu object `Advance` parent now reads
  `owner->historyQueue` directly; its 938 relocation positions, types,
  addends and destinations and every section byte remain identical. It is
  still nonexact (913 GPR-role and ten instruction-width differences).
- `48dca566`: the complete 859-byte `BattleScene::Update` invokes the effect
  owner's `AdvanceAll` through `fighters[i]->field2EC` instead of raw +0x2EC
  receiver casts. Its four direct relocations retain their target addresses;
  74/74 affected exact units passed the focused cold replay.

- The effect manager now has actual `std::deque<Actor*> entries_[4]`.
  `Spawn` uses native `push_back`, and deletion iterates and clears those
  members directly, without pointer reinterpretations. The five affected
  whole function bodies cold-replay 5/5 and all 58 header-affected exact units
  replay 58/58. The manager's complete 24 source-owned code/EH/data sections,
  46 relocations and two SafeSEH roots verify exact with a fresh 3/3
  constructor/destructor/bind cold receipt. The section evidence changes only
  emitted VC7.1 template symbol names, not target bytes, addresses, sizes or
  resolved relocation destinations.

- The battle effect tick (`0x0045BDB0`, 296 bytes) and both rendering
  dispatchers (`0x0045BC30`, 166 bytes; `0x0045BCE0`, 207 bytes) now
  define methods of `EffectManagerLifetimeF161` itself and iterate its actual
  `std::deque<Actor*>` members. The old F136/F137/F162 borrowed owner classes
  and unused headers were removed. All three whole functions cold-replay
  3/3 exactly, including every VC7.1 typed-deque relocation; no new authored
  bytes are credited because these were already accepted functions.

- The independently exact 31,352-byte `CharacterAuxObject::Advance`
  auxiliary state machine now uses ordinary implicit short assignments at 16
  random-range and decay conversion sites, removing redundant casts. Its
  entire 31,777-byte COFF section and 913 relocations still cold-replay
  exact 1/1, with no change to credited authored bytes.

- Youmu's 16-byte snapshot record now has one natural field vocabulary
  (`action`, `stage`, `x`, `y`, `facing`, `counter`) for both the writer and
  `YoumuObject::Advance`. Six redundant union aliases and the historical
  object-side typedef are gone. The 1,008-byte writer and all 81 header users
  cold-replay exactly; the entire 40,464-byte giant parent and all 938
  relocation offsets/types/addends/targets remain unchanged and NONEXACT.

The latest commits restore natural C++ field types and call expressions in
large research parents. They do not claim new giant exactness:

- dfa7b04b: removed 91 unnecessary short-reference casts for the signed
  Fighter::fieldEFA member across Meiling, Suika, Alice, Reimu and Remilia.
  Five complete COFF bodies and their relocation layouts remained identical.
- 075bb570: typed YoumuObjectHistoryF1211 coordinates at +0x04/+0x08 as
  floats and restored direct coordinate assignments. Its full 40,464-byte
  parent and all 938 relocation positions/types remained identical.
- 30cf0700: unified Youmu's R049 snapshot writer and R243 object-history
  reader on one borrowed +0xFEC list view and one 16-byte record. The
  1,008-byte auxiliary function still replays exact 1/1; the 40,464-byte
  Youmu object COFF remains byte-identical with all 938 relocation
  positions/types. R243's historical canonical verifier currently predates
  the accepted R049 row and stops at that stale snapshot; do not downgrade
  the accepted auxiliary function to make the old snapshot pass.
- 40913af9: removed four redundant byte/word reference casts across the
  complete Youmu, Yuyuko and Suika object Advances. All three complete COFF
  bodies remain byte-identical at 40,464 / 44,331 / 43,972 bytes, with
  938 / 1,043 / 991 relocation positions/types unchanged; all three giant
  frontiers remain explicitly nonexact.
- current work: moved the 30-byte `0x004071A0` held-input clear onto the
  real `Fighter::inputBindings` member (`InputBindingsF171`) and replaced
  the +0x494 receiver cast in `Fighter::ResetRound` with a typed member call.
  The leaf and complete 1,151-byte reset caller both cold-replay exact (2/2);
  the 28-byte `InputState` at block +0x2C is compile-time layout checked.
  Original proposed role/name remains provisional.
- b4c6ead7: removed 27 same-width reference casts from the complete
  `Fighter::ClearAuxiliaryWords` and `Fighter::ResetRound` bodies, restoring
  direct `int`, `unsigned long`, `float` and signed-byte member assignments.
  The 89-byte clear helper and 1,151-byte reset caller remain cold-exact;
  the 30-byte held-count leaf also replays exact after the typed-member move.
- current work: typed `Fighter::field2EC` as the 0x54-byte
  `EffectManagerLifetimeF161` owner and moved `DeleteFourLists` onto that
  actual object. The owner destructor and Fighter reset caller now call the
  member directly. The 221-byte cleanup, 85-byte destructor, 131-byte
  constructor, 21-byte bind method, 1,151-byte reset caller and 30-byte
  held-count leaf all pass focused replay (6/6); the original deque helper
  template instantiations and all relocation positions remain intact.
  The coupled owner object also passes all 24 whole code/EH/data sections,
  237 authored bytes, 46 relocation fields and both SafeSEH roots with a
  fresh canonical receipt.
  The 282-byte `0x0045BB10` spawn routine now belongs to that same owner:
  `EffectManagerLifetimeF161::Spawn` uses the bound Fighter's virtual slot 7,
  the four typed float parameters through `CharacterObject::field0D4`, and
  the actual four deque members. Its 282 bytes / three direct relocations
  replay exact. The 29 exact units depending on `CharacterObject.hpp` replayed
  29/29; the owner lifecycle replayed 3/3 and the 24-section EH/data verifier
  passed with the fresh receipt.
- current follow-up: `Fighter::SpawnBattleEffect` and the existing tracked
  forwarder now call `field2EC->Spawn` directly. Removed the F135/F136
  queue/spawner receiver declarations and the F973 raw byte-view header;
  the two F169 tracked-effect entry points use typed Fighter fields through
  their call-only receiver view. The six Fighter policy functions, both
  tracked-effect helpers and the 282-byte manager Spawn all cold-replay 9/9.
- 1c67b549: restored float types for FighterFrameInfo +0x2C/+0x30 and Actor
  +0x94/+0x98. Reimu's full fighter COFF and 1,824 relocations remained
  identical; the 462 affected exact units cold-replayed 462/462.
- ba650436: restored 22 same-type float assignments in SuikaObject::Advance.
  Its full 43,972-byte COFF and all 991 relocation positions/types remained
  identical.
- 6ab698e5: restored 97 float copies in Sakuya/Youmu/Yukari object parents
  and 93 direct signed-int accesses to Remilia's declared field07C. All four
  complete parent COFF bodies and relocation layouts remained identical.
- 003c377f: restored 31 same-type float copies in SakuyaObject::Advance.
  Its full 42,937-byte COFF and all 929 relocation positions/types remained
  identical.

The shared Fighter::fieldEFA migration is now complete in the remaining
known giant callers. A follow-up removed 61 more signed-short aliases from
29 shared boss-state fragments; complete Patchouli, Reimu, Sakuya, Youmu and
Remilia parent builds retained every code byte and relocation. `fieldEFE` is
also restored as a signed short stage-fade timer; both Meiling/Patchouli
renderers retained all 1,606 bytes and 40 relocations, and the 23 affected
render/init/reset units replayed 23/23 exact. No ASM, padding, fake returns or
target-byte arrays were introduced. The exact CharacterProjectileAdvanceF379
leaf remains exact.

The shared math leaves now have natural C++ source in `src/MathFloatHelpers.cpp`:
R269/R270 recovered the 21-byte authored atan2 wrapper while keeping its 37-byte
VC7.1 inline worker library-owned; R271 recovered the 17-byte fabsf and sqrtf
game wrappers from 30/68 and 3/6 complete authored caller graphs. Their three
whole wrapper units cold-replay 3/3 exact. The 28-byte fabsf/sqrtf workers remain
origin-unknown under the preserved R163 alternatives; no CRT or worker bytes
were double-credited.

- Youmu's +0xFEC action-history queue is now an actual 12-byte
  `std::list<ObservedInputSnapshotF378>` member of the 0xFF8-byte
  `YoumuFighter`. The auxiliary writer uses native `push_back`, `size`,
  `pop_front`; the 39,999-byte object `Advance` uses `front`. The constructor,
  reset and auxiliary units cold-replay 3/3, and all 81 exact users of the
  changed header replayed 81/81. The 40,464-byte object parent and all 938
  relocation locations/types/addends/local destinations remain unchanged;
  its 913-GPR/10-width nonexact frontier is not promoted.

## Giant priorities

There are 13 complete, nonexact research parents and nine without a complete
parent. The current 13-parent measurement table is in GIANTS.md.

The closest complete parents by register-role debt are:

1. Alice object 004EBDA0: 133 GPR differences, zero width differences;
   first divergence 004F344C.
2. Meiling object 005EB520: 135 GPR differences, six width differences;
   first divergence 005F3904.
3. Sakuya object 004CA6E0: 447 GPR differences, 12 width differences.

Start with Alice or Meiling and work from the whole function, not isolated
switch fragments. Alice's complete source has dropped 93 redundant numeric
casts in two accepted passes while retaining all 33,731 COFF bytes and 682
relocation positions/types/addends/local destinations exactly; its 133 GPR
positions remain. Eight casts around integer `RecordedRange` subtraction
were explicitly retained because removing them changes the arithmetic. Meiling's 997/998 boundary
has already had 22 natural-C++ variants without improvement. A separate
source-cleanup pass removed six redundant numeric casts from the whole
Meiling giant while retaining all 34,879 COFF bytes and 806 relocation
positions/types/addends/local targets; its 985-byte / 135-GPR / six-width
frontier remains unchanged. Youmu's 39,999-byte object giant also lost 13
redundant short casts while retaining its full 40,464-byte COFF and 938
relocation positions/types/addends/local targets; its 913-GPR / 10-width
frontier remains unchanged. Sakuya's 809/810
gate was also revisited on 2026-11-19; all syntax-only variants were discarded.
The best transient Sakuya form was two bytes too large and failed the frontier
size check. Do not repeat those attempts without new target evidence.
A separate Sakuya source cleanup removed five redundant angle-result short
casts while preserving all 42,937 COFF bytes and 929 relocation positions,
types, addends and local targets; its 447-GPR / 12-width frontier is unchanged.
Remilia's 28,868-byte object giant also dropped 24 redundant numeric casts
while preserving all 696 relocation positions, types, addends and local
targets; its 726-GPR / six-width frontier is unchanged.
Suika's 43,501-byte object giant also dropped 18 redundant short casts
while preserving all 43,972 COFF bytes and 991 relocation positions/types/
addends/local targets; its 935-GPR / one-width frontier is unchanged.
Yukari's 43,599-byte object giant also dropped six redundant short casts
while preserving all 44,104 COFF bytes and 943 relocation positions/types/
addends/local targets; its 613-GPR / 11-width frontier is unchanged.
Yuyuko's 43,845-byte object giant also dropped two redundant angle-result
short casts while preserving all 44,331 COFF bytes and 1,043 relocation
positions/types/addends/local targets; its 914-GPR / six-width frontier is
unchanged.
Reimu's 60,999-byte fighter giant also dropped two redundant short casts
while preserving all 62,090 COFF bytes and 1,824 relocation positions/types/
addends/local targets; its 6,311-GPR / five-width frontier is unchanged.
Alice's 33,293-byte object giant dropped another 13 redundant short casts
and one redundant float conversion while preserving all 33,731 COFF bytes and
682 relocation positions/types/addends/local targets; its 133-GPR / zero-width
frontier remains unchanged. Float casts protecting integer subtraction and
integer division remain in place.
Alice also loses eight redundant float wrappers around `RecordedRange`
results while retaining the one `0..4 - 2` wrapper whose removal changes
code generation; the full 33,731-byte body and all 682 relocations remain exact.

For a complete parent:

    scripts/repo-python scripts/measure-giant.py 004EBDA0 005EB520
    scripts/repo-python scripts/check-frontier.py alice-object-advance-004ebda0 meiling-object-advance-005eb520

Measure after each substantive change. A frontier check is a nonregression
guard, not exact acceptance. A giant is exact only after a complete replay
unit covers its whole body and relocations.

## Small-leaf follow-up

The 8-byte 00531D80 and 11-byte 00531D90 functions have decorated VC7 list
node symbols (_Nextnode and _Prevnode for the std::list specialization for
CharacterValueObservation) in config/character-list-front-origin-evidence.json
and config/character-list-policy-origin-evidence.json, respectively. They
have many callers but remain unclassified/review in the canonical ledgers.
Treat the decorated symbols and caller graph as leads, then verify the
complete source signature and origin independently.

00411E80 and 00411E90 are another short accessor pair with 13 and nine
observed callers respectively. Their source identity and origin are still
review; do not name or classify them from their tiny bodies alone.

## Working loop

1. Check git status and read the relevant class/source, complete parent,
   frontier and current target evidence.
2. Use Ghidra through scripts/ghidra.py and the existing headless runtime.
   Keep compiler builds serial and invoke repository Python through
   scripts/repo-python.
3. Restore real C/C++ types, member access and control flow. Do not use
   assembly, padding, inert code, invented ABI declarations or source splits
   to imitate progress.
4. Compare the complete affected COFF body and every relocation. If a shared
   header or ABI changes, cold-replay only the affected exact units.
5. Commit substantial progress with the requested prefix: gpt-web: ...

Useful commands:

    scripts/repo-python scripts/validate-tracking.py --require-target
    scripts/repo-python scripts/report-reconstruction-status.py --summary
    scripts/repo-python scripts/measure-giant.py ADDRESS
    scripts/repo-python scripts/check-frontier.py FRONTIER_NAME
    scripts/repo-python scripts/replay-exact-units.py --unit UNIT_NAME

Never run a full cold replay merely for handoff. Documentation-only changes
need git diff --check; ordinary notes do not need compiler replay or full CI.

## Storage state

The generated build scratch tree has been cleared at this handoff; build/
is recreated empty and repository scripts repopulate it as needed. Python
bytecode caches and this session's temporary replay/batch logs were removed.
The active .analysis research contexts, layout-tools, Ghidra project, shared
.tools installation, game-specific Wine prefix, original target and canonical
config ledgers were preserved. See [STORAGE_HYGIENE.md](STORAGE_HYGIENE.md)
before removing any further private research context.

The common Fighter `scriptCounterF00/F02` fields at +0xF00/+0xF02 are now
proper signed `short`s. 813 signed-short reinterpret-reference aliases across
140 source/include files now use the actual members directly; 29 redundant
short casts on assignments were also removed. Reimu/Sakuya/Youmu/Remilia full
fighter `Advance` COFF bodies and relocation maps remain byte-identical
(62,090/1,824; 83,922/2,352; 47,655/1,491; 59,236/1,863). The 12 affected
exact reset/dispatch units replayed 12/12. A follow-up removes six
`static_cast<signed short>` wrappers from three Youmu scripted-state fragments;
the full 47,655-byte Advance body and all 1,491 relocations remain identical.
The shared scripted fragments then lost 16 redundant integer-promotion casts
and 18 float-promotion casts around the now-signed counters. All four full
fighter Advance bodies were rebuilt once more; every byte and relocation
position/type/addend/local target remains identical.
All four giant frontiers are unchanged and remain nonexact.
A further signed-counter cleanup removes 16 redundant int staging casts and
two float casts in six bounce/resource-volley fragments. The four complete
Reimu/Sakuya/Youmu/Remilia fighter `Advance` bodies and all relocation maps
remain identical; the GPR/width frontiers are unchanged.
The signed-counter work also removes 58 unsigned-short reference aliases
from zero-initialization of five already-signed Fighter fields across 19
initialization/reset sources. All 20 affected exact units replayed 20/20.
`Fighter::fieldEF8` (+0xEF8) is now declared `unsigned short`, matching its
per-frame increment and the unsigned phase/modulo reads in Marisa's chain
renderer and the battle HUD. Five affected exact units replayed 5/5.
The reset-field cleanup removes a further 38 unsigned-short aliases around
zero writes to signed `aiWaitTimer/aiStep/aiCardTimer`, `field6FA/field6FC`,
Suika `fieldF28/fieldF2A`, and Yuyuko `fieldF10`. All 20 exact init/reset
units replayed 20/20 again; no unsigned-short reference aliases remain in
tracked source/probe files.
`Fighter::field478` (+0x478) is also a signed short: the native resource
loader sign-extends it before `AllocateSlots`. The declaration and call now
use the natural member directly; the complete 1,186-byte loader body and all
63 relocations remain identical, with the loader plus all eleven character
initializers replayed 12/12.
`Fighter::field6F8` (+0x6F8) is now `signed char`, matching the `movsx`
loads in both Meiling/Patchouli stage renderers. Removing their two
reinterpret-reference views preserves both 1,606-byte bodies and all 40
relocations; the affected exact renderers replayed 2/2.
The five Mode 5 option bytes at `+0x52C..+0x531` (excluding the already-signed
`+0x52F` byte) are now declared `signed char`, matching their native signed
loads and the existing signed direction view. Thirty-nine signed-byte alias
views across five source files were removed. Seven affected exact pause,
debug, options, render, state, frame-action and reset functions replayed 7/7.
`BattleScene::field118` (+0x118) is now `signed char`, matching the pause
menu's negative wrap checks and signed navigation. Thirty-three signed-byte
alias views in four source files were removed. Nine exact pause, debug, end
overlay, Mode 5, state, scene-construction, pause-shortcut and frame-action
functions replayed 9/9 with complete COFF bodies and relocations unchanged.
The character-selection `chosenCharacter` and `alternateCharacter` arrays
(+0xE0/+0xE2) are now signed bytes, matching the controller's negative
wrap/decrement logic. Seventy signed-reference aliases and 29 explicit
signed casts were removed; six exact selection controller, card/background/
options render, subselection and reset functions replayed 6/6 unchanged.
The name-entry `field120` at `+0x120` is now `signed char`, matching the
parallel sprite-name view and the signed editor row-offset calculation. Its
last signed-byte reinterpret cast is gone; `NameEntryScene::UpdatePlayer`
remains byte-identical at 541 bytes with all 11 relocations, replayed 1/1.
`Fighter::field713` (+0x713) is now `signed char`, matching the result
scene's native `movsx` sequence-state tests. The two signed-reference views
were removed. Both full character-sequence giants, the result update and all
eleven fighter initializers retained complete COFF bytes and relocations;
14 affected exact units replayed 14/14.
`Fighter::field3CF` (+0x3CF) is now `unsigned char`, the continuation/status
byte immediately following the one-byte F992 outcome union. Seventeen
signed/unsigned reference aliases across BattleStateMachine and nine fighter
fragments were removed. All four complete Reimu/Sakuya/Youmu/Remilia fighter
parents and relocation maps remain identical; the exact battle-state
function replayed 1/1.
`Fighter::field3CE` (+0x3CE) is now a one-byte `FighterOutcomeByteF992` union
with explicit signed/unsigned views. The 17 signed reinterpret-reference
views and 18 `F992_OUTCOME` borrowed-window macro accesses are now direct
member operations; the old two-byte pointer-arithmetic overlay was removed.
All 56 affected exact functions across six battle/combat/KO/round-end/reset
translation units replayed 56/56 with complete bodies and relocations
unchanged.
Another 45 redundant unsigned-byte aliases around writes to already-signed
members were removed: eleven `field532` character initializers, BattleScene
`field018`, Meiling `sequencePhase`, Fighter `field484/field3AD/noticeState`
and ResultScene `field00C`. Thirty-eight exact functions across twenty
affected translation units, including the 3,797-byte Meiling stage
configuration and hit/KO/notice helpers, replayed 38/38 unchanged.
`ReplayRecords::AppendRecord` now increments its signed-byte `field116`
cursor directly; the complete 1,252-byte body and all 50 relocations remain
identical, replayed 1/1.
Four Youmu stage-two fragments replace twenty signed-byte reinterpret
aliases for opaque color channels with direct unsigned `0xFF` assignments.
The complete 47,655-byte `YoumuFighter::Advance` body and all 1,491
relocations remain identical; frontier drift remains 16,833 bytes, unchanged.
Six further unsigned-byte aliases were removed from round-winner writes,
the round-record signed-byte conversion, projectile direction and notice
render step arguments. The four affected translation units replayed 11/11
exact functions.
Forty-one `char&` aliases of signed `facing` fields were removed from 21
Reimu/Youmu shared fragments. The complete Reimu and Youmu `Advance` bodies
and all relocation maps remain identical; their nonexact frontier counts
remain 42,551 and 16,833 differing bytes, unchanged.
Twenty more byte aliases were removed from five large fighter parents:
ten zero writes to `field3AC`, seven direct signed-byte `field366` decrements
and three owner-facing copies. Complete Reimu/Sakuya/Youmu/Remilia advances
and PatchouliObject advance bodies/relocations remain identical; their
frontier drift counts remain 42,551 / 18,253 / 16,833 / 40,569 / 24,643.
The four selection input counters now use explicit unsigned value casts
instead of reference reinterpretation; all eight aliases are gone and both
selection/update functions replayed 2/2 exactly.
Forty float bit-copy aliases in the PatchouliObject action family and seven
more in CharacterProjectile/CharacterObject initialization were replaced by
ordinary float assignments. The complete 82,109-byte PatchouliObject giant
and all 1,449 relocations remain identical; frontier drift stays 24,643
bytes. Both exact leaf functions replayed 2/2.
Ten redundant const-float reference casts around the already-float
third-boss `velocityX` field were removed. Sakuya's complete 83,922-byte
`Advance` and all 2,352 relocations remain identical; frontier drift remains
18,253 bytes.
Twelve float-member `int&` overlays were replaced with ordinary float
assignments (Reimu `field490`, fighter `rotationZ`, Youmu owner-X and Y), and
the pause-effect `field10C` positive assignment is direct. All eight
`ProgressPauseF174` exact functions replayed 8/8; all four fighter giant
bodies and relocation maps remained identical.
`BattleScene::field010` (+0x010) is now a signed `int` frame/timeline
counter; seventeen signed-reference aliases in frame update and timeline
rectangle math were removed. Eleven more signed-reference overlays around
positive writes to unsigned `field00C` were removed from pause/KO/round-end
transitions without changing its storage type. Twenty-two exact functions
across seven translation units replayed 22/22, including the complete
3,459-byte overlay timeline and 4,764-byte battle-state machine.
Collision body-contact and Actor snapshot paths now copy `field08C`,
`field090`, `savedX` and `savedY` as their declared float members rather than
through unsigned-long reference aliases. All three exact collision functions
replayed 3/3. `BattleScene` construction also initializes float `field08C`
with two direct `0.0f` assignments; the full 922-byte constructor and all 40
relocations remain identical, replayed 1/1.
The three `unsigned long&` aliases around signed `Fighter::score` were
removed from knockout settlement, battle state transitions and pause/debug
reset. Comparisons retain the native unsigned conversion against global score
ceilings, and the score addition explicitly performs unsigned 32-bit
arithmetic. Eight affected exact functions replayed 8/8, including the full
4,824-byte `BattleScene::AdvanceState`.
The replay queue policy no longer uses its `QUEUE` pointer-arithmetic macro;
clear and empty checks are direct member calls. Static queue construction and
destruction now declare the same typed owner prefix, file handle, record
header, and four segmented queue members. The destructor directly closes the
`HANDLE` and lets C++ destroy members in reverse order. Four affected exact
functions replayed 4/4 (67, 35, 132 and 161 bytes).
`ReplayRecords::LoadRecord` now shares the same typed owner and queue layout
as `AppendRecord`: direct file path, record-offset array, serialized header,
and four queue members replace its raw `AT`/`LIST` offset macros. The complete
792-byte reader and 29 relocations remain identical; targeted replay passed
2/2 for append and load.
`ReplayRecords::AppendRecord` now models the native 20-byte segmented
queue members and 8-byte owner/index iterators directly. The ten record file
offsets, serialized header, and four queue objects have explicit typed
members; all 23 raw owner-offset accesses and the `FIELD` macro are gone.
The 1,252-byte body and all 50 relocations remain identical; targeted exact
replay passed 1/1.
`Actor` now models the `+0x080` auxiliary angle as a float overlay beside
the ordinary signed hit-stop words `field080`/`field082`. Four
`reinterpret_cast<float&>` views in `CharacterAuxObject::Advance` were
replaced with the named union member. Complete 31,777-byte body and 913
relocations remain identical; exact replay passed 1/1.
`Fighter::field3A4` (+0x3A4) and `field3A8` (+0x3A8) are now signed
`int` countdown fields, matching decrement, negative-clamp and knockout
settlement semantics. Sixteen signed-reference aliases were removed. Forty-
five exact functions across six affected translation units replayed 45/45;
the four complete fighter `Advance` bodies and relocation maps remain
identical.
Fighter resource pointers now expose their observed alternate views as
unions: `field534` is either the TimelineDrawing renderer view or the
FighterTexture resource view, and `stageDrawing` keeps the general renderer
pointer alongside the F286 stage texture pointer. Redundant pointer-reference
aliases were removed from resource loading, overlay rendering, command
selection, damage flash and opponent gauge paths. Ten exact functions across
six translation units replayed 10/10, including full resource loading and
battle damage-flash rendering.
`Fighter::fieldF06` (+0xF06) and `fieldF08` (+0xF08) are now signed
16-bit members, matching the third-boss arc, cadence and trajectory logic.
Thirty-six signed-short reference overlays across eight boss fragments were
removed. The complete 83,922-byte Sakuya `Advance` and all 2,352 relocations
remain identical; 46 exact functions across eleven reset/shared-action
translation units replayed 46/46. The four fighter giant frontiers remain
unchanged, including Sakuya at 18,253 differing bytes.
Input counter aliasing was cleaned up without changing the Fighter layout:
A/B/C keep their signed 32-bit storage but use explicit unsigned value casts
for native unsigned tests; D uses its declared unsigned value or an explicit
value conversion where required. Twenty-nine exact functions across fifteen
translation units replayed 29/29. All four complete fighter `Advance` bodies
and relocation maps remained identical; frontier drift remains
42,551 / 18,253 / 16,833 / 40,569 bytes.
`Fighter::noticeFirst` (+0x6E8) is now `signed char`, matching the native
signed render test; its render and base-reset functions remain byte-identical.
Four signed-byte views used only to store zero to the unsigned `field39C`
flag and the redundant signed view in the overlay timeline switch were also
removed. Four affected exact functions replayed 4/4.
