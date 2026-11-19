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
known giant callers. No ASM, padding, fake returns or target-byte arrays
were introduced. The exact CharacterProjectileAdvanceF379 leaf remains
exact.

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
switch fragments. Meiling's 997/998 boundary has already had 22 natural-C++
variants without improvement. Sakuya's 809/810 gate was also revisited on
2026-11-19; all syntax-only variants were discarded. The best transient
Sakuya form was two bytes too large and failed the frontier size check.
Do not repeat those attempts without new target evidence.

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
