# TH075 handoff (2026-11-15)

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
2. Rename the research parent classes to their character classes
   (`FighterSwitchF598_Boss0045DD70::Advance` is `ReimuFighter::Advance`).
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
- `.analysis/layout-tools/` (private): `affected.py REV` lists units affected
  by changed sources, headers or manifest entries; `replay_each.sh LIST OUT`
  replays them in one grouped call; `objsig.py A.obj B.obj [renames]` proves a
  rewrite byte-identical; `rawize.py`, `objectize.py`, `stageize.py`,
  `fighterize.py`, `combatize.py` and `windows.py` convert raw accessors to
  members; `relabel.py UNIT...` refreshes manifest symbol names after a
  rename (offsets, types and targets must be unchanged); `anomalies.py`
  lists anomalous joins in an original.
