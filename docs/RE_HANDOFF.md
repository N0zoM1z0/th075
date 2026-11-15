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

Next steps:

1. Remaining raw offsets in `src/` (about 1,400 sites in 207 files). The
   combat code (`BattleCombat*.cpp`, `BattleCollision*.cpp`,
   `CharacterSpecial5E68C0.cpp`, …) uses pointer views such as
   `CombatActor`, `AnimationState` and `StageOpponent5E59C0` that are really
   `Actor` or `Fighter`; merge them, which also renames the helpers at
   0040FAC0 onward to `Actor` members. +0xAC is an `Actor`-level copy of
   the frame record taken at a hit (`FighterFrameInfo*`; damage at +0x10,
   hit-stop shorts at +0x1C/+0x1E). Scene and HUD classes (result, title,
   battle constructor, menus) need their own layouts from all of their
   methods' accesses.
2. Rename the research parent classes to their character classes
   (`FighterSwitchF598_Boss0045DD70::Advance` is `ReimuFighter::Advance`).
3. The giants' register debt: find the construct behind the anomalous
   joins described in GIANTS.md.

## Tools

- `scripts/measure-giant.py [ADDRESS]`: build a research parent and report
  its debt against the PE.
- `.analysis/layout-tools/` (private): `affected.py REV` lists units affected
  by changed sources, headers or manifest entries; `replay_each.sh LIST OUT`
  replays them in one grouped call; `objsig.py A.obj B.obj [renames]` proves a
  rewrite byte-identical; `rawize.py`, `objectize.py`, `stageize.py` and
  `fighterize.py` convert raw accessors to members; `anomalies.py` lists
  anomalous joins in an original.
