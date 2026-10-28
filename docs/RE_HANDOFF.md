# TH075 — active reconstruction handoff (F244)

**Updated 2026-10-28. Read this document before new experiments.**

The latest user instruction is to **continue actually reconstructing TH075**,
tackle both large/core functions and small leaves, distrust historical
hypotheses until checked, handle all dirty work (no concurrent session), and
save substantial verified progress in Git commits beginning `gpt-web: ...`.
Earlier H184 advice to stop is historical and **does not apply**.

## 1. Verified state at handoff

| Item | Current evidence |
| --- | --- |
| Local branch / last exact-code commit | `main` / F244 local acceptance; prior F243 commit `6306ec0` |
| Upstream | `origin/main` tracked locally; verify current ahead/behind and dirty state before further work |
| Working tree | Clean after F244 commit if successful; inspect actual dirty files and continue all pre-existing edits |
| Native binary | `resources/th075.exe`, SHA256 `bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98` |
| Candidate count | 4,351; origin review: 1,002 authored, 2,671 library, 581 compiler, 97 unknown |
| Accepted functions / units | **558 / 558** |
| Accepted authored CODE | **781,627 bytes** |
| Reviewed authored coverage | 781,627 / 1,973,516 = **39.61%** |
| Conservative coverage | **39.53%** counting 3,608 origin-pending bytes |
| Goal | **98% not reached** |
| Verification | F244 whole 1529-byte result scene advance boss plus separately verified 32-byte owned tables, 74 COFF fields, 1265/1265 nonfield bytes, targeted cold exact; F243 ctor 547 and F242 transition 663 separately cold exact; no full cold replay or external Oracle receipt |

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
| F230 `5dd2dcc`: CharacterSelectScene::ProcessPlayerOptions | `00433A40` | 404 | 18 |
| F230 `5dd2dcc`: CharacterSelectScene::ProcessSubselection | `00433BE0` | 264 | 16 |
| F231 `e5aac7f`: ReplayBrowserScene::ScanFiles | `0042D470` | 613 | 31 |
| F234 `21cb1c7`: MusicRoomScene::UpdateSelection | `004259D0` | 675 | 24 |
| F235 `767c540`: MusicRoomScene::RenderTrackCatalogText | `00426670` | 555 | 21 |
| F235 `767c540`: MusicRoomScene::RenderSelectedTitle | `004268A0` | 452 | 16 |
| F238 `d090445`: ResultScene::BuildCounterPage | `00431350` | 664 | 30 |
| F239 `95295a4`: ResultScene::BuildRecordPage | `00431070` | 721 | 26 |
| F240 `3710f61`: ResultScene::RenderCounters | `0042EF10` | 1,344 | 44 |
| F241: ResultScene::DrawDecimalDigits | `0042F530` | 423 | 9 |
| F242 `4b2aa34`: SceneTransition::DispatchMode | `00431F60` | 663 | 27 |
| F243 `6306ec0`: ResultScene::Initialize | `0042E640` | 547 | 33 |
| F244: SceneController::AdvanceAt0042E8F0 | `0042E8F0` | 1,529 (+32 table) | 74 |

F222 proved signed 32-bit x87 `FILD` divided by the target's 36.0f
(`00659308`), 74 physical animation records and a final call into the
*previously accepted* base reset `00457010`. The correct source loop is
`i <= 36`, not the byte-different `i < 37`. Its three relocations all
match. F223 adds two complete borrowed constructors and a real EH-backed
232-byte `new`; Youmu additionally calls the observed +0xFEC child init.
All twenty-eight units were independently cold-exact. F224 used a complete, native-EH-backed `new(0xE8)` with the real Youmu constructor at `00536360`, then ordered 16 halfword resets, the accepted base reset `00457010`, and the observed +0xFEC subcomponent reset `00531CE0`. Their nominal C++ classes and
external helper implementations are **not** established by code equality.

F225 additionally accepts an entire 668-byte character-selection constructor (185 native instructions) with actual vtable, three separately allocated texture managers, two deleting destructors, two real configuration loops, and 38 relocation fields. Its first full probe used mistaken pointer-indirect indexing and emitted 677 bytes; the verified this-relative byte arrays restore exact native 668 bytes. The base-scene constructor remains R108 origin-unknown and uncredited.

F226 adds an entire 1,005-byte replay-browser selection state machine. A natural source probe originally emitted 1,016 bytes because of 32-bit promotions and a redundant macro-generated loop. The corrected short prefix increment/decrement and direct transition statements match all 296 native instructions, 813/813 comparable bytes and 48 real relocation fields. Only this affected unit was cold-replayed.

F227/F228 independently cold-replay 6 additional authored units (4 fighter routines, 2 large character-select controllers) for 2,722 more CODE bytes. Two 120-byte factory functions reconstruct genuine EH-backed `new(232)` and individual constructors; two round resets retain character-specific field order. `UpdatePlayerChoice` 1,029 bytes, 245 instructions, and 32 fields; `UpdatePlayerConfirmation` 995 bytes, 242 instructions, and 34 fields. Both include real x87, input and stage transitions. Their unfinished dirty source and unit evidence were investigated and completed, not discarded.

F229 adds the complete 1,442-byte R044 authored scene advancement state machine and its nine-entry 36-byte owned dispatch table. A first natural source emitted 1,429 CODE bytes plus table, but its branch and indexing shapes differed. Correct typed 0x48-stride input frames, true opposite-player indexing and native-first cancel/action dispatch ordering restore 1,442 CODE bytes, 1174/1174 comparable bytes and all 76 physical relocations over the 1,478-byte full comparison extent. Only `character-select-scene-advance-00433470` was cold-replayed, exact. **Do not credit jump-table bytes as CODE.** The nearby `UpdateCancelAnimation` at `00435870` remains **unaccepted** (497-byte object, 438/445 comparable bytes; x87 FLD order mismatch), with all negative natural-source variants retained under `.analysis/f229-character-select/` and `.analysis/f230-selection-helpers/` and `.analysis/f231-replay-scan/`, `.analysis/f232-append-scope/`, `.analysis/f233-record-scope/`, `.analysis/f234-music-select/` and `.analysis/f235-music-render/`, `.analysis/f236-music-catalog/` and `.analysis/f238-result-page/` (F238 and F239), and `.analysis/f240-result-render/` and `.analysis/f241-result-digits/` and `.analysis/f242-transition/` and `.analysis/f243-result-init/` and `.analysis/f244-result-advance/`.

F230 accepts the two real selection-state callees used by F229: 404-byte `ProcessPlayerOptions` (111 native instructions, 18 relocations) and 264-byte `ProcessSubselection` (70 native instructions, 16 relocations). The second compiled exact on the first natural source; the first required preserving native 32-bit boolean-toggle lowering (`flag ? 0 : 1` instead of `!flag`). Both were independently cold-replayed and earned 668 new authored CODE bytes. Call target `00438A60` retains its separate unknown origin and receives no matching credit.

F231 accepts the entire `ReplayBrowserScene::ScanFiles` at `0042D470` (613 CODE bytes, 155 native instructions, 31 relocation fields). The complete native FindFirst/Next/Close directory loop, two `new char[260]` filenames, real `strcpy`/`strcat` roots, 60-byte header and one-byte status ReadFile calls, queue appenders, and original `/GS` cookie are preserved. First natural probe already emitted 613 bytes, 471/489 comparable bytes. By grounding the actual three nested lifetimes (header/count, flag, index) and ordinary `push_back(static_cast<char*>(0))` temporary pointer references, full 489/489 nonrelocation bytes and 31 real destinations match. Only `--unit replay-browser-scan-files-0042d470` was cold replayed. Adjacent replay-file ownership destructor at `0042C560` remains not yet exact; the library deque functions are not credited.

F232 tested a new meaningful subset of lexical scope alternatives for the **complete** 1252-byte `ReplayRecords::AppendRecord`: all 50 COFF fields and full code length remain valid, but the best still has 1025/1052 nonfield bytes; no exact credit. F233 independently reevaluated the entire 792-byte `ReplayRecords::LoadRecord` (274 instructions, 29 fields), tracing actual native stack-slot differences. Scoped and reordered real `rawWord`/counter/read temporary lifetimes failed to improve the earlier 639/676 nonfield-byte best; no exact credit. Retain `.analysis/f232-append-scope/` and `.analysis/f233-record-scope/` rather than repeating older name sweeps.

F234 cold-accepts the complete 675-byte `MusicRoomScene::UpdateSelection` (179 native instructions, 24 true relocation fields). First natural C++ source gets 579/579 nonfield bytes and all fields, covering actual directional input, 16-byte track-record stride, signed index/scroll, unlocked-card check, highlight, music play/fade, exit, cooldown. Only `--unit music-room-scene-update-selection-004259d0` cold replayed; no all-unit replay.

F235 independently cold-replays the two complete music-room text rasterization calls with native EH, GS, 56-byte glyph allocation, D3D8 LockRect/UnlockRect, and all physical fields: `RenderTrackCatalogText` 555 CODE/136 instructions/21 relocs, `RenderSelectedTitle` 452 CODE/114 instructions/16 relocs. The catalog was cold exact with the first natural source (471/471 comparable bytes). The selected-title first source emitted the exact 452 length but used a wrongly inferred 308-byte local message buffer; original stack/frame measurements prove 300 bytes, fixing all 30 stack operand differences and yielding 388/388 and cold exact. Only the two F235 units were rebuilt. The original glyph class layout remains inferred and caller contexts are call-only.

F236 independently re-checked the 916-byte `MusicRoom::LoadCatalog` boss function and its separately owned 16-byte jump table. Correcting the signed-digit `while` shape and genuine final free-pointer alias yields the correct 932-byte whole comparison size, with 18 resolved fields, but still only 731/860 non-field bytes matched. Tested real variable declaration hoists and preserved every negative result at `.analysis/f236-music-catalog/`. This function **remains unaccepted** and receives no byte credit.

F238 cold-replays the entire `ResultScene::BuildCounterPage` at `00431350` (664 CODE bytes, 167 native instructions, 30 true relocations). The first source emitted 670 bytes despite matching the native frame size, because VC7 placed the real D3DLOCKED_RECT and 200-byte sprintf buffer in the wrong stack slots. Native-faithful nested scopes (outer locked rect, middle 200-byte line, inner 500-byte message) produce all 544/544 comparable bytes, original EH/GS paths and cold exact. Only `--unit result-scene-build-counter-page-00431350` was cold replayed.

F239 also cold-replays the adjacent **721-byte `ResultScene::BuildRecordPage`** (174 x86 instructions, 26 genuine COFF fields) with 617/617 native non-field bytes. It reads the original selected result record and signed 10-row page window, checks the real deque size and accesses original per-entry names, formats both absent/present record paths, and passes a genuine 2000-byte concatenation buffer through the shared 56-byte glyph and D3D8 texture lifecycle. Its first natural whole C++ source matches without guessed padding, and only `--unit result-scene-build-record-page-00431070` was cold replayed.

F240 newly cold-replays the complete **1,344-byte `ResultScene::RenderCounters` boss** (320 instructions, 44 genuine COFF fields), 1168/1168 nonrelocation bytes. The 132-byte SpriteQuad is the existing independently reconstructed physical owner; the 16-byte RECT must live in a meaningful inner C++ scope to restore actual stack offsets -0x88/-0x98. Native `ScaleQuad` receives three raw IEEE754 DWORD patterns, so a call-only facade preserving float bits emits real MOV/PUSH instead of extra x87 temporaries. The last x87 4-byte discrepancy is resolved by a directly observed `this+0x14` float field: compiler naturally loads the 255.0f target global first then multiplies the member. All 6 digit draws, D3D8 mode calls, quad transform, frame capture, selection, actor and EndFrame calls match. Only F240 was cold replayed; its external callees are not separately credited. Research is in `.analysis/f240-result-render/` and `.analysis/f241-result-digits/` and `.analysis/f242-transition/` and `.analysis/f243-result-init/` and `.analysis/f244-result-advance/`.

F241 independently cold-accepts the complete **423-byte `ResultScene::DrawDecimalDigits`** that F240 calls six times (127 x86 instructions, 9 native relocations, 387/387 comparable bytes). It preserves true signed decimal quotient/remainder loops for fixed and variable digit counts, separate 16/15px left shifts, 20px atlas row stride and entire RET 0x18. The first ordinary source emitted 459 bytes and put its real number in a different stack slot. Nested meaningful number/132-byte quad/RECT lifetimes restore EBP-4, -0x90, and -0xA0, and native 423 bytes exactly. Only the F241 unit was cold-replayed, not all existing units. Its own main caller's bytes are not double-counted.

F242 cold-accepts the original entire **663-byte `SceneTransition::DispatchMode`** controller at `00431F60`, 157 native instructions, 27 real relocation fields, 555/555 nonfield bytes. The original `RET 4`, signed transition countdown, mode remapping, two sparse switch decision trees and all six independently accepted callback targets are preserved; previous natural source emitted 674 bytes due to wrong switch-case lexical order and JZ/JLE lowering. Reordering only actual original cases and expressing positive nibble guards reproduces the full 663 bytes. Only this affected unit was cold replayed. Full proof and failed first natural source are under `.analysis/f242-transition/` and `.analysis/f243-result-init/` and `.analysis/f244-result-advance/`.

F243 separately cold-accepts **547-byte `ResultScene::Initialize`** with 127 decoded instructions, 415/415 non-field bytes and 33 real COFF fields. First natural C++ source reproduces genuine EH-backed new(80), physical base ctor and texture manager allocation/load path; all native x87 integer division/addition, score global and actor values, four 900-position/one 1800 animation halfwords, and result stage reset are preserved. Base ctor at `004251C0` retains R108 unknown-origin status, so no independent credit. Only `--unit result-scene-initialize-0042e640` cold replayed.

F244 adds the complete **1,529-byte R065-authored result-scene advancement boss** and both owned four-entry jump tables (32 data bytes, no CODE credit). The first natural C++ source already generated the full 1,561 comparison bytes, all 74 physical fields and 1255/1265 nonfield bytes. Only three real comparison expression orders were different: actor score > saved best, frame >= threshold, pending score > tick step. Reversing their logically equivalent source comparisons reproduces the original register load order, all 1,265/1,265 comparable bytes and both complete switch tables. `--unit result-scene-advance-0042e8f0` cold replayed exact. The existing tracking name `SceneController::AdvanceAt0042E8F0` remains an inferred role, not a proven original class identity. No broad cold replay. Complete evidence is in `.analysis/f244-result-advance/`.

Relevant full native proofs: `config/match-units.toml`,
`config/exact-adoptions.json`, sources `src/*F222.cpp`/`src/*F223.cpp`,
and `docs/KNOWLEDGE_BASE.md`. The cold-replay logs are private in
`.analysis/f222-marisa-reset/`, `.analysis/f223-fighter-ctors/`, and `.analysis/f224-youmu-lifecycle/`, and `.analysis/f225-big-functions/` and `.analysis/f226-replay-browser/`, `.analysis/f227-fighter-recovery/`, `.analysis/f226-player-choice/` and `.analysis/f228-confirmation/` and `.analysis/f229-character-select/` and `.analysis/f230-selection-helpers/` and `.analysis/f231-replay-scan/`, `.analysis/f232-append-scope/`, `.analysis/f233-record-scope/`, `.analysis/f234-music-select/` and `.analysis/f235-music-render/`, `.analysis/f236-music-catalog/` and `.analysis/f238-result-page/` (F238 and F239), and `.analysis/f240-result-render/` and `.analysis/f241-result-digits/` and `.analysis/f242-transition/` and `.analysis/f243-result-init/` and `.analysis/f244-result-advance/`.
Earlier accepted functions remain in the canonical ledgers. **Do not run any all-unit cold replay**; user explicitly requires only newly changed/affected units. Keep builds serialized/headless.

## 3. Unsolved **large** functions — recommended next work

These are **diagnostics, not accepted code**. Each native function needs full
body/owned-table, origin and relocation review before any adoption.

| Function / entry | Target | Best prior compiler evidence | Retained research |
| --- | ---: | --- | --- |
| ReplayRecords::AppendRecord `00413DE0` | 1,252 B | Entire emitted size and 50 field positions; best **1,025/1,052** non-field bytes, iterator stack slots still wrong | `.analysis/f219-append-record/` |
| ReplayRecords::LoadRecord `00413AC0` | 792 B | Entire emitted size, 29 fields, **639/676** non-field bytes; local HANDLE/count slots | `.analysis/f216-archive-record/` |
| MusicRoom::LoadCatalog `00426DD0` | 916 B CODE + 16 B switch table | F236 complete 932-byte source/control and all 18 field locations, best **744/860** non-field bytes; native 0x48 frame vs emitted 0x50 | `.analysis/f215-music-catalog/`, `.analysis/f236-music-catalog/` |
| ReplayRecords::FinalizeFile `004138E0` | 375 B | Natural variants 342/372/384/396 B; pointer lifetimes/frame unknown | `.analysis/f218-replay-file/` |
| BattleScene destructor `0043B0B0` | 248 B | Exact length/flow but 9–11 local-stack field byte differences | `.analysis/f200-battle-dtor/`, `.analysis/f215-battle-release/` |
| Giant actor control `004AC040` | very large | Full baseline still nonexact; many closed tests, avoid repeating blindly | `.analysis/character-move-4ac040/`, archived knowledge |

F236 independently rechecks native 916+16 extent and four original table destinations; a natural condition-first numeric loop plus real cleanup-pointer lifetime restores the complete 932-byte comparison size and 18 field destinations. Seven meaningful lexical scopes and seven real declaration-order variants did not pass exact; best is 744/860 nonrelocation bytes with mismatched native local slot allocation. No accepted source or CODE credit; retain `.analysis/f236-music-catalog/EXPERIMENTS.md`.

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
