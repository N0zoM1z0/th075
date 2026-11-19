# TH075 handoff (2026-11-19)

Follow [AGENTS.md](../AGENTS.md) and the [workflow](RE_WORKFLOW.md). The user
reports no other active sessions: continue any dirty work you find. Keep
compiler builds serial, use `scripts/repo-python`, and replay only affected
units (pass all of them to one `replay-exact-units.py` call so each object is
built once).

## Status

982 exact functions, 871,649 original CODE bytes, 44.16% of authored bytes
(44.09% conservative). The 22 authored functions left are the giant
per-character `Advance` state machines, listed with their measured debt in
[GIANTS.md](GIANTS.md). The 98% goal is not met. Live numbers:
`scripts/repo-python scripts/report-reconstruction-status.py --summary`.

## Current work: readable source, then the giants

The user asked for tech debt to be cleared before the push to 100%:
obsolete files removed, hash pins replaced by cold replay, and raw offsets
replaced by named members of shared classes.

Done so far:

- Result-list browser virtual slot 1 is now `ResultListScene::Advance`
  (1,803 B) and slot 2 is `ResultListScene::Render` (3,314 B), sharing
  its real scene and record/deque members. Both whole native functions
  preserve all relocations; the 10-unit affected-only replay (including
  music-room rendering and lifecycle) was 10/10 exact across 8 objects.
- All four fighter research giant `Advance` functions use the real
  `Actor::ResetPrimaryCounters` at 705 native calls (511 source alias
  sites). Complete COFF sizes/relocation positions and types are unchanged;
  nonrelocation code byte differences = 0. Header-affected exact units
  passed 132/132 targeted cold replay; giant register debt remains.
- At 0040FB70, Sakuya and Remilia fighter giants now call
  `Actor::SetPolarVelocity` directly (12 native relocations); ten
  Sakuya calls now pass the true `float field314` instead of its fake
  integer-bit alias. Whole COFF bytes/relocation offsets were unchanged,
  and 104/104 affected exact functions cold-replayed locally (36/34/34).
- Four fighter giant parents now use `Actor::ResetTransform` at
  0040FBB0 and `Actor::ClearTransformFlag` at 0040FC50 instead of
  provisional helper aliases. The new C++ float arguments preserve
  all four whole-function nonrelocation bytes and original relocation
  positions/types (45 renamed native calls); 132/132 affected-only
  exact cold replay passed. No ASM/PADDING or giant exact credit.
- The native `0040FB40` helper is now `Actor::ResetSecondaryCounter`
  across four fighter giant parents, replacing 351 source aliases and
  462 actual COFF relocation symbols. Four complete parent byte/reloc
  comparisons were unchanged; all 132 affected exact units cold-replayed
  locally in three 44-unit groups. Giant GPR/width debt remains.
- `Actor::ResetPrimaryCounters(short)` at 0040FAC0 now owns all 705
  native action-reset calls in the four complete fighter `Advance`
  research parents (511 source occurrences across 256 files). Full
  parent COFF comparisons preserve all nonrelocation bytes/relocation
  offsets and types. Affected-only cold replay passed 132/132 exact
  units in three groups (44/44 each); no full repository replay.
- The native shared Actor frame-advance helper at 0040FA30 is now
  `Actor::AdvanceNestedFrame` throughout all four complete fighter giant
  research parents: 382 source calls, 552 actual COFF relocations now
  use the truthful inherited API. All four parent COFF bodies remain
  byte-identical outside renamed relocations, and 132/132 affected exact
  units cold replayed without a full repository replay.
- The shared `00453D60` sound caller is now
  `Fighter::PlaySharedSound` across Reimu/Sakuya/Youmu/Remilia giant
  `Advance`: 192 native relocations restored from 147 alias source calls,
  whole objects unchanged outside symbol names, 132/132 affected-only
  exact cold replay passed (44/44 each in three groups).
- The shared 00453D40 sound caller is now `Fighter::PlaySound` in all
  four full fighter `Advance` research parents: 199 source calls and
  257 actual relocations renamed, with zero nonrelocation byte changes,
  no relocation location/type changes and no size changes. The 132/132
  affected-only exact cold replay passed; nonexact frontier debt remains.
- All four full Reimu/Sakuya/Youmu/Remilia Fighter research parents now
  invoke the inherited `Fighter::ClearMotionFields` at 494 actual COFF
  call sites (410 source occurrences across 193 case/parent files).
  Full pre/post COFF byte/relocation audits were unchanged outside
  call names; all 132 header-affected exact units cold-replayed in
  three groups (44/44 each), without a full repository cold replay.
  The four research parents remain nonexact against the original PE.
- The 51-byte `00453E20` motion clear leaf is now
  `Fighter::ClearMotionFields`, using the actual four Actor motion
  members (`velocityX`, `velocityY`, `field058`, `field05C`) instead
  of an offset-only borrowed receiver. Complete leaf cold replay and
  four directly related Fighter helpers passed 5/5. The four fighter
  research giants now also call this inherited method, replacing 410
  source references (494 actual compiled calls). Complete pre/post giant
  COFF body comparisons preserve all nonrelocation bytes and all original
  relocation offsets/types; their 132/132 affected exact units were
  cold-replayed in three groups of 44 without a full cold replay.
- Shared gauge timer `0046D000` is now `Fighter::UpdateGaugeTimer`,
  reflecting its real calls from Youmu, Patchouli and Remilia as well as
  Reimu. The original 126-byte function is cold-replay exact. Eighteen
  directly affected Fighter/character units were locally selected and
  replayed 105/105 exact; the broader Fighter.hpp include graph was not
  exhaustively cold-replayed. The four fighter research giants also now
  call the shared gauge method from 138 native call sites (52 Reimu,
  44 Sakuya, 14 Youmu, 28 Remilia). Complete pre/post 62,090,
  83,922, 47,655, and 59,236-byte COFF bodies preserve every
  nonrelocation byte and every relocation position/type, but still
  remain nonexact against the target PE.
- Result-list rendering helpers now belong to the real scene:
  `DrawCounter` (377 B), `DrawNameGlyphs` (280 B), and `DrawRankLabel`
  (169 B). The rank glyph method calls the real `DrawNameGlyphs` target
  instead of a borrowed alias. All three complete functions, their
  3,314-byte `Render` caller and the separate name-entry rank glyph
  function cold-replay exactly.
- The result-list browser is now separately modeled as `ResultListScene`
  (not the score-tallying `ResultScene`). Its 1,803-byte selection update
  and 343-byte input poll share typed page, character, availability and
  input members. Both cold-replay exactly, along with the shared source's
  selection animation. Its constructor (366 B), destructor (229 B),
  record page (721 B), counter page (664 B), and texture/character
  resource loader (398 B) now use the same named layout and native
  80-byte texture manager and 20-byte deque. The current shared-header
  cohort cold-replays 8/8 exact units with all relocation targets.
  The native `ResultListScene` vtable at 006581D0 confirms slot 1 is
  0042F970 and slot 2 is 00430080. Its 1,803-byte `Advance` and
  3,314-byte `Render` are now the real C++ virtual methods; the latter
  accesses the scene's named texture, record and cursor fields. Ten
  affected exact units, including the separate music-room renderer,
  cold-replayed successfully.
- The character-select scene now owns the exact C++ constructor, main
  `Advance`, reset and five choice/confirmation/option methods. Their shared
  layout covers the 28-byte per-player input records and named animation
  fields; both card and options renderers now belong to `CharacterSelectScene`
  and the 6,404-byte background renderer is now the genuine virtual
  `CharacterSelectScene::DrawCurrent`. The single-player options renderer
  (596 bytes) now uses the same owner and is called directly by the virtual
  render method. All 19 header-affected exact units cold-replayed correctly.
- Remilia's 58,294-byte fighter `Advance` is now
  `RemiliaFighter::Advance` with real actor coordinate members. The
  59,236-byte COFF body is unchanged outside renamed relocation fields
  (all 1,863 offsets/types preserved); 98/98 header-affected exact units
  cold-replayed in three groups. The GPR/width debt is still nonexact.
- Sakuya's complete 82,796-byte fighter `Advance` now belongs to
  `SakuyaFighter` instead of a research subclass. Its 16 state files
  use named real actor X members and the real Actor transform reset.
  The 83,922-byte COFF body has zero nonrelocation differences and all
  2,352 original relocation positions/types; 98/98 locally affected
  exact units cold-replayed. The 6,958 GPR and 12 width differences
  remain unresolved, so no whole giant exact credit was added.
- Remilia Fighter `Advance` (58,294 native CODE bytes) is now the real
  `RemiliaFighter` virtual method, with genuine Actor::x coordinate reads
  instead of the temporary field view. The full 59,236-byte COFF body,
  all 1,863 relocation positions/types and all nonrelocation bytes are
  unchanged. The 98/98 header-affected units replayed exact, grouped to
  avoid full cold replay; 1,741 GPR and three width differences remain.
- Youmu's complete 46,755-byte fighter `Advance` is now on the real
  `YoumuFighter` vtable class. Native-coordinate owner views became
  `x` / `opponent->x` in 13 case source files, and 15 resets use the
  actual Actor API. The 47,655-byte object and all 1,491 relocation
  positions/types remained identical outside renamed relocations.
  All 85 header-affected exact units passed grouped local cold replay.
  The 2,736 GPR mismatches and five widths remain nonexact.
- The 60,999-byte Reimu fighter parent is now `ReimuFighter::Advance` on the
  real vtable class, with its two +F00/+F02 counters named in `Fighter`.
  Its native-byte ratchet is unchanged: 6,311 register-role differences
  beginning at `0045FDA9`; no whole-function exact credit was added.
  All 99 header-affected exact units cold-replayed successfully (33 objects).
- Seven VC7.1 conditional-join variants on Alice object `Advance` at
  `004F344C` failed to improve its nonexact frontier; see GIANTS.md.
- Alice object `Advance` now belongs directly to `AliceObject` in the shared
  class hierarchy, with the owner, opponent, counters, positions and gauge
  accesses expressed through real named members. The 33,293-byte parent
  retained its 575-byte nonexact frontier and 133 GPR mismatches; all 24
  header-affected exact functions cold-replayed successfully.
- Youmu object `Advance` (39,999 CODE B) is now a real `YoumuObject`
  member. Its history-entry view keeps the 16-byte native record and
  Fighter's indexed `field370` without inventing the unknown history
  container layout. All 108 spawns and the 20 effect/sound auxiliaries
  bind to Fighter methods. The 40,464-byte complete COFF and 938
  relocation locations/types are preserved; 24/24 exact units cold
  replayed. Seven 0046D000 gauge calls still require receiver research.
- Suika object `Advance` (43,501 CODE B) now belongs to `SuikaObject`;
  64 spawns, 13 sounds, three shared sounds and five camera shakes use
  the actual Fighter and camera contracts. The 43,972-byte object and
  all 991 relocation positions/types stayed unchanged outside symbol
  renames; 24/24 affected exact units passed cold replay. Its 935 GPR
  role and one width differences remain unresolved.
- Yukari object `Advance` (43,599 native CODE B) is now declared on
  `YukariObject`; its 52 effect, 16 sound, two auxiliary and three shake
  calls are typed through Fighter. A complete 44,104-byte COFF comparison
  retained all 943 relocation offsets/types and zero nonrelocation differences;
  24/24 affected exact units replayed. Nonexact GPR/width debt remains.
- Remilia object `Advance` (28,432 original CODE bytes) now belongs to
  `RemiliaObject`, with its 24 recorded-range, 25 effect, seven sound and
  two shared-sound calls expressed via real classes. Complete 28,868-byte
  COFF body and all 696 relocation offsets/types remain unchanged, with
  zero differences outside relocations; 24 impacted units cold-replayed.
  The 726 GPR and six width mismatches still prevent giant exact credit.
- Patchouli object `Advance` (81,539 bytes) now belongs to `PatchouliObject`.
  The 32 shared sound calls and seven camera-shake calls have typed receivers;
  its complete research byte frontier is unchanged (522 GPR, five width
  differences). Raw coordinate DWORD-to-float transport still requires
  ABI-specific work; 24 affected exact units cold-replayed successfully.
  Another 24 raw coordinate spawn callsites across nine case files now use
  `owner->SpawnBattleEffect(effect, x, y, ...)` with a byte-identical
  82,109-byte VC7.1 output and all 1,449 relocation offsets/types intact.
  A second batch restored 19 more source spawn calls across 12 case
  files with zero nonrelocation-byte difference against the baseline.
  The final 27 coordinate-spawn sites and the auxiliary/tracked spawns
  now use the real Fighter APIs too; only the cross-character
  0046D000 gauge call retains a borrowed receiver. The whole 82,109-byte
  compiler object and 1,449 relocation positions/types remain unchanged.
  Six additional float-argument source sites (seven compiled calls) have
  since moved to the real `Fighter::SpawnBattleEffect` API with all 1,449
  relocation positions/types unchanged and zero altered nonrelocation bytes.
- Sakuya object `Advance` (42,511 bytes) now belongs to `SakuyaObject`
  and uses the real Fighter effect/sound APIs for 87 call sites. Its
  nonexact instruction/register frontier is unchanged; COFF size and
  all 929 relocation positions/types were preserved, with zero changed
  nonrelocation code bytes. All 24 impacted exact units cold-replayed.
- The Meiling object 34,434-byte parent now defines `MeilingObject::Advance`
  and sends 93 effect-spawn calls directly through the actual `Fighter`
  owner. Its 985 differing bytes, 135 GPR roles and six widths remain
  unresolved; all 24 dependent exact functions cold-replayed successfully.
- Yuyuko's 43,845-byte object research body is now
  `YuyukoObject::Advance`; 66 effect spawns, eight sound calls and four
  camera-shake calls use the shared interfaces. The full object body and
  all 1,043 relocation positions/types were unchanged. Its 914 GPR and
  six width differences still prevent exact credit; all 24 affected
  units cold-replayed successfully.
  Ten source-equivalent compiler probes at the first GPR join in case 837
  left its entire giant frontier unchanged or regressed it; details are
  recorded in GIANTS.md.

- The class structure from the PE vtables is in source: `Actor`, `Fighter`,
  one `<Char>Fighter` per character with its overrides under the slot names,
  and `CharacterObject`. See the [knowledge base](KNOWLEDGE_BASE.md).
- All 13 giant research parents use these members; each conversion was
  proven byte-identical with `.analysis/layout-tools/objsig.py`.
- The nine per-character stage setups are now `<Char>Fighter::ConfigureStage`
  (slot 15), like Reimu's and Meiling's.
- The per-checkpoint research notes and the 115 partial-state verifiers were
  removed. Their findings are summarised in GIANTS.md and the knowledge base;
  the full text is in Git history (`git show 430a06a4:docs/<NOTE>.md`).
- Tests and checks follow the factory's cleanup guide: the 174 per-owner
  and origin mutation tests are gone and the tooling tests remain. The 67
  origin verifiers that no longer passed and that nothing loads were
  deleted. The 74 broken ones that working verifiers import stay as shared
  code. The giants have a byte ratchet.
- `Actor` now covers 0x00–0xC3, including the collision snapshot at
  +0xA8 and the frame-record layout; its helpers live in `src/Actor.cpp`.
  The combat code uses `Actor`/`Fighter` pointers instead of the old
  `CombatActor`/`AnimationState` views, and most borrowed-window macros
  (`F999_VITAL`, `F1037_POSITION`, …) became members.
- Classes with real layouts now cover the battle scene (`BattleScene`,
  47 methods from constructor to render), the result, title and options
  scenes, `SceneBase`, the combo counter, the music stream
  (`AudioStream`), the text overlay's definitions (`TextOverlay`) and the
  save data (`GameProgress` plus `ProgressDifficulty`, 27 methods).

Next steps:

1. Remaining raw offsets and alias classes. `grep` for `FIELD(` and
   `reinterpret_cast<...>(this) +` finds about 300 sites each in about 170
   files, and 28 classes still pad from +0 with `unknown000[...]`. The
   biggest groups:
   - the character select scene (16 files; per-player blocks indexed with
     `player * 28` and `[side]` that need a per-player struct);
   - the texture manager (0040AD80–0040D870), whose methods are bound
     under about 25 view classes; their vectors use different element types,
     so unify the layout first;
   - the music room, replay browser, name entry, staff roll, opening, logo,
     loading, battle end and result-list scenes (small);
   - the fighter constructor and destructor (`FighterInitF287`,
     `FighterResourceReleaseF284`), whose embedded objects are listed in the
     knowledge base with one open question;
   - callers that still declare their own copies of `TextOverlay`, sound
     bank, input mapping and other library methods (248 addresses are bound
     under several class names; `relabel.py` makes renaming cheap).
2. Move the remaining research parent classes to their real character
   classes, as now done for `ReimuFighter::Advance` and
   `AliceObject::Advance`, `MeilingObject::Advance` and
   `SakuyaObject::Advance` and `YuyukoObject::Advance`. Resolve provisional
   native-call signatures against the shared base APIs without regressing
   the full giant function.
3. The giants' register debt: find the construct behind the anomalous
   joins described in GIANTS.md.

Workflow for a class merge: write the header, convert the sources
(`sceneize.py`, `scenefields.py`, `shellmerge.py`, `thisize.py`), check
the objects with `objsig.py` against a baseline build, rename the ledger
entries by address (`rename_addr.py`), run one grouped replay of
`affected.py HEAD`, `relabel.py` the units whose symbols changed, replay
those again. Watch for new members shadowed by parameters or locals, and
keep parentheses where a macro expanded to a parenthesized dereference in
x87 arithmetic.

## Tools

- `scripts/measure-giant.py [ADDRESS]`: build a research parent and report
  its debt against the PE.
- `scripts/check-frontier.py [NAME]`: the giants' ratchet over
  `config/frontiers.toml`; fails when a parent loses a matching byte,
  `--update` records improvements.
- `scripts/check-origins.py [SUBSTRING]`: run the origin verifiers against
  the real evidence.
- Unit tests for shared tooling: `scripts/repo-python -m unittest discover
  -s tests` (a few seconds).
- `.analysis/layout-tools/` (private): `affected.py REV` lists units affected
  by changed sources, headers or manifest entries; `replay_each.sh LIST OUT`
  replays them in one grouped call; `objsig.py A.obj B.obj [renames]` proves a
  rewrite byte-identical; `rawize.py`, `objectize.py`, `stageize.py`,
  `fighterize.py`, `combatize.py` and `windows.py` convert raw accessors to
  members; `relabel.py UNIT...` refreshes manifest symbol names after a
  rename (offsets, types and targets must be unchanged); `anomalies.py`
  lists anomalous joins in an original.
