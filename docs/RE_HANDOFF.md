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

- Nine full object giant Advances now inherit `Actor::RecordedRange`
  instead of nine fake per-character random-range declarations. 414
  compiled calls were audited with zero nonrelocation byte changes across
  nine full COFF bodies and no relocation layout changes. Local exact
  verification: range leaf 1/1, object cohort 24/24, selected Actor/Fighter
  dependency cohort 105/105. No full cold replay was run.
- Four complete fighter giants also now use `Actor::RecordedRange` in
  169 actual compiled call sites (Reimu 29, Sakuya 97, Youmu 16,
  Remilia 27). All four complete COFF bodies preserve original size,
  all relocation offsets/types and every nonrelocation code byte.
  Grouped affected-only exact replay passed 132/132 (44/44 each).
  Giant frontiers remain nonexact against the original PE.
- The mixed 00453A70 X-float/Y-float spawn ABI is also restored at
  92 actual COFF call sites (81 source occurrences) across four fighter
  giants. No integer-bit coordinate transport remains at these sites;
  whole parent bodies are unchanged outside relocation names and
  132/132 affected exact units replayed in three local groups.
- Four fighter giant `Advance` parents now dispatch another 70 native
  effect calls through truthful `Fighter::SpawnBattleEffect`, restoring
  62 C++ source callsites using genuine floating `x/y` instead of
  `reinterpret_cast<int&>` bit transport. All four complete COFF bodies
  and all relocation offsets/types remain identical outside symbol
  labels; 132/132 affected exact units cold-replayed locally.
- Four complete fighter giants also now call the real inherited
  `Actor::RecordedRange(int,int)`: 169 native relocations (Reimu 29,
  Sakuya 97, Youmu 16, Remilia 27). The full functions preserve their
  original COFF bytes outside identically located/type relocations;
  132/132 header-affected exact units cold replayed in local batches.
- Eight complete object giant parents now use the inherited
  `Actor::RecordedRange` for 377 verified native COFF calls, rather than
  speculative duplicate methods: Sakuya 75, Alice 15, Youmu 49,
  Remilia 24, Yuyuko 67, Yukari 17, Suika 73 and Meiling 57.
  Eight full COFF comparisons preserved all function body lengths,
  relocation positions/types and every nonrelocation byte. Local
  cold replay of the 25 header-affected exact units passed 25/25.
  Giant byte/register debt remains NONEXACT.
- The existing complete native 00455580 recorded-range generator is now
  `Actor::RecordedRange(int,int)` instead of the standalone borrowed
  receiver class. It remains 139-byte/11-relocation cold-exact, with
  both 0040FAC0/0040FB40 adjacent Actor helpers 3/3 exact; 24/24
  relevant object and renderer units cold-replayed. This is an inferred
  shared C++ ABI, not a claim of original source class identity. Eight
  object giants will be migrated to the inherited caller separately.

- The nine native object giant parents now inherit that real 0045B860
  sound-bank forwarder, replacing 20 native per-character sound aliases.
  All nine complete COFF bodies and relocation positions/types are
  unchanged outside renamed call symbols, the full giants retain their
  nonexact frontiers, and 28/28 exact header-affected units replayed.
- The existing exact 29-byte 0045B860 sound leaf is now the common
  `CharacterObject::PlaySharedSound(short)` instead of a borrowed fake
  receiver, with both original relocations intact and 28/28 affected
  exact units locally cold-replayed. Its per-character giant call
  declarations will be unified separately.
- Native 0045B850 was recovered as an authentic, 13-byte
  `CharacterObject::NoOpAt0045B850(int)` empty game member with `RET 4`:
  11 original PE direct calls in Yuyuko (3), Yukari (4), Suika (4)
  establish its shared role. Original bytes cold-replay exact 13/13,
  0 relocations. The three complete object giant COFF parents preserve
  all their relocation positions/types and all nonrelocation bytes.
  The five other units from the same source cold replay 6/6 exact.
  Conservative tracking advanced from 982 to 983 exact functions.
  No ASM, padding, synthetic exactness or claim of original method name.

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
- Reimu/Youmu/Remilia giant fighter `Advance` now uses the shared
  `Fighter::SpawnBattleEffect` native float ABI instead of per-character
  borrowed `SpawnFloatXYAt453A70(int,float,float,char,int)` receiver
  variants (133/20/69 real compiled calls). The whole COFF sizes,
  relocation positions/types and nonrelocation bytes are unchanged;
  127/127 header-affected exact units cold replayed locally (43/42/42).
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
- Alice parent and its exact 855-byte projectile leaf now use the true
  `AngleAt00483300(float,float)` ABI, with two raw integer-bit call
  declarations removed. Both complete COFF bodies and all relocation
  locations/types are unchanged; 2/2 focused exact cold replay passed.
  Twelve additional natural-source register-join trials at 004F344C
  failed to improve the 133-GPR mismatch frontier and were discarded.
- Alice object's `0x320`–`0x326` actions now call a separately exact
  native 855-byte `AliceObject::AdvanceProjectileBehavior` (004F4170).
  This leaf's owner uses two typed `Fighter::SpawnBattleEffect` calls;
  both the main giant and leaf retain full COFF byte and relocation
  shapes. The 24/24 header-affected exact units cold-replayed locally.
- Alice's giant source replaces 32 integer-reference bit-puns for float
  rotation/velocity fields with ordinary float assignments. The entire
  33,731-byte VC7.1 COFF and all 682 relocation offsets/types remain
  unchanged; GPR debt is still 133 and no exactness is claimed.
- The Alice `Advance` giant now calls its **real** 004F4170 action-family
  helper as `AliceObject::AdvanceProjectileBehavior` for seven projectile
  states. The 855-byte leaf now uses the real `Fighter::SpawnBattleEffect`
  for its two owner spawn calls rather than a borrowed fake parent.
  Whole 33,731-byte giant and 855-byte leaf COFF comparisons retain all
  original nonrelocation bytes and all relocation positions/types; the
  24 impacted exact units (including the leaf) cold-replayed 24/24.
- Alice giant `Advance` also now calls the real Actor polar-velocity
  helper 19 times (three recovered raw-bit float arguments) plus 15
  recorded-random-range and two shared-sound calls. Full COFF shape
  and 682 relocations unchanged; 24/24 affected exact units replayed.
- Alice object giant 004EBDA0 (33,293 native CODE bytes) now uses
  true Actor / CharacterObject methods in 274 native calls for frame
  advance, reset, transition and clear. Full 33,731-byte COFF body and
  682 relocation offsets/types are preserved with zero nonrelocation
  changes; 24/24 exact header-affected units cold-replayed. It remains
  nonexact against the original PE (133 GPR differences).
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
- Four fighter giants now call `Fighter::SetCommandSelection` (00454BC0)
  using the actual `(int,unsigned char,unsigned int)` ABI instead of
  `ConfigureStormAt454BC0`, preserving 35 native call relocations and
  whole-body code. All 132 affected exact units locally cold-replayed.
- `00453E60` is now the real `Fighter::SetCameraShake(float)` leaf,
  not the partial FighterShake borrowed view. The 25-byte canonical leaf
  remains cold exact; four fighter and five object giant `Advance`
  research parents use the real owner API at 72 compiled call sites.
  Full pre/post COFF audits preserve every nonrelocation byte and every
  relocation offset/type, and nine frontiers did not regress. 103/103
  directly related exact units passed targeted cold replay; the 449-unit
  Fighter.hpp fanout was not exhaustively replayed.
- Reimu/Sakuya/Youmu/Remilia giant fighter states now call shared
  Fighter leaf helpers by real names: 122 horizontal-limit checks,
  29 nonnegative-word setters, nine fade initializers, nine resource
  parameter selectors and six auxiliary spawns. Four whole COFF bodies
  have zero nonrelocation code differences and identical relocation
  positions/types. 132/132 affected-only exact units cold-replayed;
  giant GPR/width debt remains outstanding.
- Sakuya fighter full parent now uses natural effect forwarding:
  153 battle spawns, 104 tracked effect spawns and 13 auxiliary spawns
  bind to the real Fighter methods. All 83,922 COFF bytes outside
  unchanged 2,352 relocation positions are identical to pre-migration;
  nonexact native GPR/width differences are unchanged.
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
- Patchouli object giant now uses 37 recorded-range calls,
  19 Actor polar-velocity calls (recovering 11 source raw float-bit sites),
  and two shared-sound calls through real C++ interfaces. The complete
  82,109-byte COFF, 1,449 relocations and 24 affected exact units were
  locally checked with no regression; native GPR/width debt remains.
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
