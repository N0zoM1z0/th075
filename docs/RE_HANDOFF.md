# TH075 handoff (2026-11-19)

Follow [AGENTS.md](../AGENTS.md) first. This handoff is the live task summary;
[GIANTS.md](GIANTS.md) contains the complete-parent measurements and the
remaining compiler investigation. The user reports no other active sessions.
Inspect Git before editing and continue all work in the registered repository.

## Live state

The current status command is:

    scripts/repo-python scripts/report-reconstruction-status.py --summary

Snapshot on 2026-11-19:

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

The working tree is clean. Main has local documentation commits relative to
origin/main; no push was performed in this cleanup session. Recheck git status
and git log before starting.

## Recent reconstruction work

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
