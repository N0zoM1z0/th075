# TH075 — active reconstruction handoff (F230)

**Updated 2026-10-28. Read this document before new experiments.**

The latest user instruction is to **continue actually reconstructing TH075**,
tackle both large/core functions and small leaves, distrust historical
hypotheses until checked, handle all dirty work (no concurrent session), and
save substantial verified progress in Git commits beginning `gpt-web: ...`.
Earlier H184 advice to stop is historical and **does not apply**.

## 1. Verified state at handoff

| Item | Current evidence |
| --- | --- |
| Local branch / last exact-code commit | `main` / F230 local acceptance; previous F229 commit `420e74b` |
| Upstream | `origin/main` available locally; F229 `420e74b` and F227/F228 `8736611`; verify current ahead/behind and dirty status |
| Working tree | Clean after F230 commit if successful; inspect every pre-existing modification before editing |
| Native binary | `resources/th075.exe`, SHA256 `bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98` |
| Candidate count | 4,351; origin review: 1,002 authored, 2,671 library, 581 compiler, 97 unknown |
| Accepted functions / units | **547 / 547** |
| Accepted authored CODE | **773,441 bytes** |
| Reviewed authored coverage | 773,441 / 1,973,516 = **39.19%** |
| Conservative coverage | **39.12%** counting 3,608 origin-pending bytes |
| Goal | **98% not reached** |
| Verification | F230 only two new 404/264-byte units cold-exact with all 18/16 fields; F229 prior 1442 CODE+36 table cold-exact; targeted checkpoint/tracking tests passed; NO all-unit cold replay; prior F228 full CI reported 3,613/3,613 passed; no external Oracle receipt |

**Recheck the actual live status immediately**. Local commits are checkpoints,
not evidence of a remote push or external Oracle acceptance. Earlier Git
pushes were blocked by DNS. Preserve all local commits, including F226 `823608c`, F227/F228 `8736611`, and document follow-up `a642620`. Do not
switch to the behind `origin/main`, force-push or reset the worktree.

```bash
git status --short --branch
git log -5 --oneline
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/validate-tracking.py --require-target
scripts/repo-python scripts/report-reconstruction-status.py --summary
scripts/repo-python scripts/ghidra.py check
```

Use `scripts/repo-python`; run all Wine/VC7.1 work **serially and headless**
with the existing `.analysis/vc71-wine` prefix and the pinned toolchain.
No replacement executable, fake owner type, pasted assembly, masked field,
inert variable or arbitrary padding may earn exact credit.

## 2. Latest accepted functions — do not double-count

| Cohort / Git checkpoint | Native address | Whole CODE | Real COFF fields |
| --- | --- | ---: | ---: |
| F222 `65632c3`: MarisaFighter::ResetRound | `00493130` | 780 | 3 |
| F223 `ca81d72`: MarisaFighter::Initialize | `00492FB0` | 243 | 6 |
| F223 `ca81d72`: MarisaFighter::CreateOwnedObject | `004930B0` | 120 | 6 |
| F223 `ca81d72`: YoumuFighter::Initialize | `0052CEE0` | 314 | 11 |
| F224 `417d882`: YoumuFighter::CreateOwnedObject | `0052D090` | 120 | 6 |
| F224 `417d882`: YoumuFighter::ResetRound | `0052D110` | 225 | 2 |
| F225 `5f544f0`: CharacterSelectScene::Initialize | `00432EA0` | 668 | 38 |
| F226 `823608c`: ReplayBrowserScene::UpdateSelection | `0042C670` | 1,005 | 48 |
| F227: ReimuFighter::CreateOwnedObject | `0046D160` | 120 | 6 |
| F227: ReimuFighter::ResetRound | `0046D1E0` | 235 | 1 |
| F227: AliceFighter::CreateOwnedObject | `004E2D90` | 120 | 6 |
| F227: AliceFighter::ResetRound | `004E2E10` | 223 | 1 |
| F227: CharacterSelectScene::UpdatePlayerChoice | `004348E0` | 1,029 | 32 |
| F228 `8736611`: CharacterSelectScene::UpdatePlayerConfirmation | `00434CF0` | 995 | 34 |
| F229 `420e74b`: CharacterSelectScene::Advance | `00433470` | 1,442 (+36 table) | 76 |
| F230: CharacterSelectScene::ProcessPlayerOptions | `00433A40` | 404 | 18 |
| F230: CharacterSelectScene::ProcessSubselection | `00433BE0` | 264 | 16 |

F222 proved signed 32-bit x87 `FILD` divided by the target's 36.0f
(`00659308`), 74 physical animation records and a final call into the
*previously accepted* base reset `00457010`. The correct source loop is
`i <= 36`, not the byte-different `i < 37`. Its three relocations all
match. F223 adds two complete borrowed constructors and a real EH-backed
232-byte `new`; Youmu additionally calls the observed +0xFEC child init.
All seventeen units were independently cold-exact. F224 used a complete, native-EH-backed `new(0xE8)` with the real Youmu constructor at `00536360`, then ordered 16 halfword resets, the accepted base reset `00457010`, and the observed +0xFEC subcomponent reset `00531CE0`. Their nominal C++ classes and
external helper implementations are **not** established by code equality.

F225 additionally accepts an entire 668-byte character-selection constructor (185 native instructions) with actual vtable, three separately allocated texture managers, two deleting destructors, two real configuration loops, and 38 relocation fields. Its first full probe used mistaken pointer-indirect indexing and emitted 677 bytes; the verified this-relative byte arrays restore exact native 668 bytes. The base-scene constructor remains R108 origin-unknown and uncredited.

F226 adds an entire 1,005-byte replay-browser selection state machine. A natural source probe originally emitted 1,016 bytes because of 32-bit promotions and a redundant macro-generated loop. The corrected short prefix increment/decrement and direct transition statements match all 296 native instructions, 813/813 comparable bytes and 48 real relocation fields. Only this affected unit was cold-replayed.

F227/F228 independently cold-replay 6 additional authored units (4 fighter routines, 2 large character-select controllers) for 2,722 more CODE bytes. Two 120-byte factory functions reconstruct genuine EH-backed `new(232)` and individual constructors; two round resets retain character-specific field order. `UpdatePlayerChoice` 1,029 bytes, 245 instructions, and 32 fields; `UpdatePlayerConfirmation` 995 bytes, 242 instructions, and 34 fields. Both include real x87, input and stage transitions. Their unfinished dirty source and unit evidence were investigated and completed, not discarded.

F229 adds the complete 1,442-byte R044 authored scene advancement state machine and its nine-entry 36-byte owned dispatch table. A first natural source emitted 1,429 CODE bytes plus table, but its branch and indexing shapes differed. Correct typed 0x48-stride input frames, true opposite-player indexing and native-first cancel/action dispatch ordering restore 1,442 CODE bytes, 1174/1174 comparable bytes and all 76 physical relocations over the 1,478-byte full comparison extent. Only `character-select-scene-advance-00433470` was cold-replayed, exact. **Do not credit jump-table bytes as CODE.** The nearby `UpdateCancelAnimation` at `00435870` remains **unaccepted** (497-byte object, 438/445 comparable bytes; x87 FLD order mismatch), with all negative natural-source variants retained under `.analysis/f229-character-select/` and `.analysis/f230-selection-helpers/`.

F230 accepts the two real selection-state callees used by F229: 404-byte `ProcessPlayerOptions` (111 native instructions, 18 relocations) and 264-byte `ProcessSubselection` (70 native instructions, 16 relocations). The second compiled exact on the first natural source; the first required preserving native 32-bit boolean-toggle lowering (`flag ? 0 : 1` instead of `!flag`). Both were independently cold-replayed and earned 668 new authored CODE bytes. Call target `00438A60` retains its separate unknown origin and receives no matching credit.

Relevant full native proofs: `config/match-units.toml`,
`config/exact-adoptions.json`, sources `src/*F222.cpp`/`src/*F223.cpp`,
and `docs/KNOWLEDGE_BASE.md`. The cold-replay logs are private in
`.analysis/f222-marisa-reset/`, `.analysis/f223-fighter-ctors/`, and `.analysis/f224-youmu-lifecycle/`, and `.analysis/f225-big-functions/` and `.analysis/f226-replay-browser/`, `.analysis/f227-fighter-recovery/`, `.analysis/f226-player-choice/` and `.analysis/f228-confirmation/` and `.analysis/f229-character-select/` and `.analysis/f230-selection-helpers/`.
Earlier accepted functions remain in the canonical ledgers. **Do not run any all-unit cold replay**; user explicitly requires only newly changed/affected units. Keep builds serialized/headless.

## 3. Unsolved **large** functions — recommended next work

These are **diagnostics, not accepted code**. Each native function needs full
body/owned-table, origin and relocation review before any adoption.

| Function / entry | Target | Best prior compiler evidence | Retained research |
| --- | ---: | --- | --- |
| ReplayRecords::AppendRecord `00413DE0` | 1,252 B | Entire emitted size and 50 field positions; best **1,025/1,052** non-field bytes, iterator stack slots still wrong | `.analysis/f219-append-record/` |
| ReplayRecords::LoadRecord `00413AC0` | 792 B | Entire emitted size, 29 fields, **639/676** non-field bytes; local HANDLE/count slots | `.analysis/f216-archive-record/` |
| MusicRoom::LoadCatalog `00426DD0` | 916 B CODE + 16 B switch table | Natural variants 928/934 vs 932 compared bytes, control flow/layout mismatched | `.analysis/f215-music-catalog/` |
| ReplayRecords::FinalizeFile `004138E0` | 375 B | Natural variants 342/372/384/396 B; pointer lifetimes/frame unknown | `.analysis/f218-replay-file/` |
| BattleScene destructor `0043B0B0` | 248 B | Exact length/flow but 9–11 local-stack field byte differences | `.analysis/f200-battle-dtor/`, `.analysis/f215-battle-release/` |
| Giant actor control `004AC040` | very large | Full baseline still nonexact; many closed tests, avoid repeating blindly | `.analysis/character-move-4ac040/`, archived knowledge |

**Practical approach:** use the now-accepted replay queue and fighter
lifecycle callees to infer *real* iterator/owner lifetimes. The F219/F216
semantically harmless variable-name permutations were already exhausted:
do not repeat 72/57 equivalent compiler probes. Their summarized result
tables are retained, with the best complete source for further diagnosis.

An exact 34-byte scene-base constructor at `004251C0` remains **origin
unknown** (R108); do not classify it authored merely because its COFF body
can match structurally. Preserve all 97 unknown origins and their 3,608
bytes outside accepted authored coverage.

## 4. Acceptance and commit checklist

1. Inspect **all dirty state**, read any prior unfinished source and retain
   meaningful experiments. Never discard someone else's assumed changes;
   the user has confirmed there is no other active session.
2. Independently verify native target SHA, full function boundary,
   decoded instructions, all exits, C++ EH, and owned jump tables.
3. Test natural C++ with exact pinned VC7.1 flags; diagnostic
   `structural-exact` does **not** compare relocation fields.
4. Register **every** true COFF relocation offset, type, symbol and target in
   `config/match-units.toml`, then **cold replay**:
   ```bash
   scripts/repo-python scripts/replay-exact-units.py --unit UNIT_NAME
   ```
5. Only after whole-function `exact`, update `config/functions.csv`,
   `implemented.csv`, `matches.csv`, `reccmp-functions.csv`,
   `known-symbols.csv`, `exact-adoptions.json` and SHA-pinned checkpoint
   tests. Update progress from live ledgers, not remembered counts.
6. Run tracking, affected cold units, checkpoint tests, optional full `scripts/ci.py` (never all-unit cold replay),
   and `git diff --check`. Commit material progress with
   `git commit -m 'gpt-web: <specific completed work>'`.
7. Keep nominal class identities, original layout ownership, unresolved
   origins and Oracle receipts separate from local byte equality.

Detailed commands and examples: `docs/RE_WORKFLOW.md`,
`docs/BUILD_MATCHING.md` and `AGENTS.md`.

## 5. Artifact retention, cleanup and research provenance

**Do not remove:** pinned `resources/th075.exe`; tracked `config/`, source,
tests, matched unit profiles, exact-manifest hashes, `.analysis/vc71-wine/`,
the private `ghidra-project/`, `.tools/`, protected H184 frozen work
objects, and the large-function best negative sources/assemblies. The old
H184 historical no-goal instruction is superseded.

Per-variant COFF objects, repeated compile logs and diagnostic JSON for
already-exhausted **F216Coord**, **F219Coord** and **F218Index** sweeps can
be regenerated. The 2026-10-28 cleanup compacted their result tables,
retained best/representative source and removed only redundant private
temporary variants. Their historical outcomes remain in the private
research directory.

The previous **verbose** handoff is recoverable through
`git show ca81d72:docs/RE_HANDOFF.md`; detailed F-series reasoning
remains in `docs/KNOWLEDGE_BASE.md`. Other historical origin and handoff
archives remain unchanged under `docs/history/`. Reading an older document
never overrides the current target, ledgers, or latest user instructions.
