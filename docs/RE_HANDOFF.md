# TH075 — active reconstruction handoff (F271)

**Updated 2026-10-28. Read this document before new experiments.**

The latest user instruction is to **continue actually reconstructing TH075**,
tackle both large/core functions and small leaves, distrust historical
hypotheses until checked, and continue unfinished work within the assigned scope.
Preserve concurrent work reported by the user and use the session's requested
commit prefix (otherwise `gpt-web: ...`).
Earlier H184 advice to stop is historical and **does not apply**.

Validation policy (2026-10-28): focus on exact reconstruction. No per-function
robustness/fault-injection tests or full historical test run is required.
`scripts/ci.py` is for exact/checkpoint/accounting or test infrastructure changes,
not routine acceptance or handoff. Canonical acceptance cold-replays only new
or affected units. Per-function duplicate hash/source-text tests are removed;
keep their data in the canonical manifests. See AGENTS.md and
RE_WORKFLOW.md for the current scope. Historical test counts are observations,
not acceptance requirements.

## 1. Verified state at handoff

| Item | Current evidence |
| --- | --- |
| Local branch / last exact-code commit | `main` / F271 full 1,185-byte projected graphics boss; prior F269 replay scene checkpoint `3c40ebd` |
| Upstream | `origin/main` tracked locally; verify current ahead/behind and dirty state before further work |
| Working tree | Clean after F271 checkpoint if successful; continue rather than avoid every existing dirty edit |
| Native binary | `resources/th075.exe`, SHA256 `bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98` |
| Candidate count | 4,351; origin review: 1,002 authored, 2,671 library, 581 compiler, 97 unknown |
| Accepted functions / units | **584 / 584** |
| Accepted authored CODE | **792,135 bytes** |
| Reviewed authored coverage | 792,135 / 1,973,516 = **40.14%** |
| Conservative coverage | **40.07%** counting 3,608 origin-pending bytes |
| Goal | **98% not reached** |
| Verification | F271 full 1,185-byte Graphics::DrawProjectedTexturedQuad independently cold-exact (1,037/1,037 comparable bytes, all 37 real relocations) after F269 replay scene checkpoint `3c40ebd`. Only new F271 unit cold replayed; no full cold replay or external Oracle receipt |

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
| F244 `808cf44`: SceneController::AdvanceAt0042E8F0 | `0042E8F0` | 1,529 (+32 table) | 74 |
| F245 `af63c54`: ResultListScene::PollInput | `0042F450` | 220 | 21 |
| F246 `08fbb99`: NameEntryScene::UpdatePlayer | `0042A340` | 541 | 11 |
| F247 `00f2f6d`: ProgressRecords::SaveScoreFile | `004169E0` | 297 | 11 |
| F248 `0c4d1f4`: ProgressRecords::LoadScoreFile | `00416B10` | 456 | 15 |
| F251: NameEntryScene::UpdateShared | `0042B380` | 494 | 16 |
| F252: CardList::EncodeCharacterFile | `00431D60` | 432 | 15 |
| F253: MusicRoomScene::DrawNumber | `00427180` | 377 | 9 |
| F253: ReplayScene::DrawNumber | `0042AE70` | 377 | 9 |
| F253: ReplayScene::DrawSlotNumber | `0042BFD0` | 377 | 9 |
| F253: ResultScene::DrawCounter | `004315F0` | 377 | 9 |
| F256: ResultScene::LoadSelectedCharacterResources | `00430EE0` | 398 | 20 |
| F257: MusicRoom::EncodeCatalogFile | `00427300` | 298 | 11 |
| F258: MusicRoom::LoadCatalog | `00426DD0` | 916 (+16 table) | 18 |
| F259: ReplayRecords::LoadRecord | `00413AC0` | 792 | 29 |
| F260: ResultScene::PollInput | `00430D80` | 343 | 27 |
| F261: MusicRoomRecord::Initialize | `00427430` | 50 | 0 |
| F261: MusicRoomRecord::ReleaseBuffers | `00427470` | 82 | 3 |
| F262: MusicRoomScene::Initialize | `00425750` | 372 | 23 |
| F263: MusicRoomScene::ReleaseTexturesRecordsAndAudio | `004258D0` | 244 | 12 |
| F264: ResultListScene::Initialize | `0042F710` | 366 | 17 |
| F265: ResultListScene::Release | `0042F880` | 229 | 10 |
| F266: ReplayPlaybackScene::Initialize | `0042C3D0` | 395 | 24 |
| F267: ReplayBrowserScene::DestroyOwnedReplayFiles | `0042C560` | 265 | 15 |
| F268: ReplayScene::PollPlaybackInput | `0042D330` | 310 | 27 |
| F269: ReplayScene::Initialize | `0042A180` | 315 | 24 |
| F271: Graphics::DrawProjectedTexturedQuad | `00402D50` | 1,185 | 37 |

F222 proved signed 32-bit x87 `FILD` divided by the target's 36.0f
(`00659308`), 74 physical animation records and a final call into the
*previously accepted* base reset `00457010`. The correct source loop is
`i <= 36`, not the byte-different `i < 37`. Its three relocations all
match. F223 adds two complete borrowed constructors and a real EH-backed
232-byte `new`; Youmu additionally calls the observed +0xFEC child init.
All thirty-nine units were independently cold-exact. F224 used a complete, native-EH-backed `new(0xE8)` with the real Youmu constructor at `00536360`, then ordered 16 halfword resets, the accepted base reset `00457010`, and the observed +0xFEC subcomponent reset `00531CE0`. Their nominal C++ classes and
external helper implementations are **not** established by code equality.

F225 additionally accepts an entire 668-byte character-selection constructor (185 native instructions) with actual vtable, three separately allocated texture managers, two deleting destructors, two real configuration loops, and 38 relocation fields. Its first full probe used mistaken pointer-indirect indexing and emitted 677 bytes; the verified this-relative byte arrays restore exact native 668 bytes. The base-scene constructor remains R108 origin-unknown and uncredited.

F226 adds an entire 1,005-byte replay-browser selection state machine. A natural source probe originally emitted 1,016 bytes because of 32-bit promotions and a redundant macro-generated loop. The corrected short prefix increment/decrement and direct transition statements match all 296 native instructions, 813/813 comparable bytes and 48 real relocation fields. Only this affected unit was cold-replayed.

F227/F228 independently cold-replay 6 additional authored units (4 fighter routines, 2 large character-select controllers) for 2,722 more CODE bytes. Two 120-byte factory functions reconstruct genuine EH-backed `new(232)` and individual constructors; two round resets retain character-specific field order. `UpdatePlayerChoice` 1,029 bytes, 245 instructions, and 32 fields; `UpdatePlayerConfirmation` 995 bytes, 242 instructions, and 34 fields. Both include real x87, input and stage transitions. Their unfinished dirty source and unit evidence were investigated and completed, not discarded.

F229 adds the complete 1,442-byte R044 authored scene advancement state machine and its nine-entry 36-byte owned dispatch table. A first natural source emitted 1,429 CODE bytes plus table, but its branch and indexing shapes differed. Correct typed 0x48-stride input frames, true opposite-player indexing and native-first cancel/action dispatch ordering restore 1,442 CODE bytes, 1174/1174 comparable bytes and all 76 physical relocations over the 1,478-byte full comparison extent. Only `character-select-scene-advance-00433470` was cold-replayed, exact. **Do not credit jump-table bytes as CODE.** The nearby `UpdateCancelAnimation` at `00435870` remains **unaccepted** (497-byte object, 438/445 comparable bytes; x87 FLD order mismatch), with all negative natural-source variants retained under `.analysis/f229-character-select/` and `.analysis/f230-selection-helpers/` and `.analysis/f231-replay-scan/`, `.analysis/f232-append-scope/`, `.analysis/f233-record-scope/`, `.analysis/f234-music-select/` and `.analysis/f235-music-render/`, `.analysis/f236-music-catalog/` and `.analysis/f238-result-page/` (F238 and F239), and `.analysis/f240-result-render/` and `.analysis/f241-result-digits/` and `.analysis/f242-transition/` and `.analysis/f243-result-init/` and `.analysis/f244-result-advance/` and `.analysis/f245-call-chain/` and `.analysis/f246-name-entry/` and `.analysis/f247-progress-save/` and `.analysis/f248-archive-write/`, `.analysis/f249-archive-writer/` and `.analysis/f251-name-shared/`.

F230 accepts the two real selection-state callees used by F229: 404-byte `ProcessPlayerOptions` (111 native instructions, 18 relocations) and 264-byte `ProcessSubselection` (70 native instructions, 16 relocations). The second compiled exact on the first natural source; the first required preserving native 32-bit boolean-toggle lowering (`flag ? 0 : 1` instead of `!flag`). Both were independently cold-replayed and earned 668 new authored CODE bytes. Call target `00438A60` retains its separate unknown origin and receives no matching credit.

F231 accepts the entire `ReplayBrowserScene::ScanFiles` at `0042D470` (613 CODE bytes, 155 native instructions, 31 relocation fields). The complete native FindFirst/Next/Close directory loop, two `new char[260]` filenames, real `strcpy`/`strcat` roots, 60-byte header and one-byte status ReadFile calls, queue appenders, and original `/GS` cookie are preserved. First natural probe already emitted 613 bytes, 471/489 comparable bytes. By grounding the actual three nested lifetimes (header/count, flag, index) and ordinary `push_back(static_cast<char*>(0))` temporary pointer references, full 489/489 nonrelocation bytes and 31 real destinations match. Only `--unit replay-browser-scan-files-0042d470` was cold replayed. Adjacent replay-file ownership destructor at `0042C560` remains not yet exact; the library deque functions are not credited.

F232 tested a new meaningful subset of lexical scope alternatives for the **complete** 1252-byte `ReplayRecords::AppendRecord`: all 50 COFF fields and full code length remain valid, but the best still has 1025/1052 nonfield bytes; no exact credit. A separate retained F225 complete source probe gives 1033/1052, independently rechecked from its JSON; the F232-specific 1025 best is not the repository-wide best. F233 independently reevaluated the entire 792-byte `ReplayRecords::LoadRecord` (274 instructions, 29 fields), tracing native stack slots. Its old scoped/reordered temporary variants failed to improve the previous 639/676 best, receiving no credit at F233. F259 subsequently reconstructed and cold-accepted the entire function. Retain `.analysis/f232-append-scope/` and `.analysis/f233-record-scope/` rather than repeating older name sweeps.

F234 cold-accepts the complete 675-byte `MusicRoomScene::UpdateSelection` (179 native instructions, 24 true relocation fields). First natural C++ source gets 579/579 nonfield bytes and all fields, covering actual directional input, 16-byte track-record stride, signed index/scroll, unlocked-card check, highlight, music play/fade, exit, cooldown. Only `--unit music-room-scene-update-selection-004259d0` cold replayed; no all-unit replay.

F235 independently cold-replays the two complete music-room text rasterization calls with native EH, GS, 56-byte glyph allocation, D3D8 LockRect/UnlockRect, and all physical fields: `RenderTrackCatalogText` 555 CODE/136 instructions/21 relocs, `RenderSelectedTitle` 452 CODE/114 instructions/16 relocs. The catalog was cold exact with the first natural source (471/471 comparable bytes). The selected-title first source emitted the exact 452 length but used a wrongly inferred 308-byte local message buffer; original stack/frame measurements prove 300 bytes, fixing all 30 stack operand differences and yielding 388/388 and cold exact. Only the two F235 units were rebuilt. The original glyph class layout remains inferred and caller contexts are call-only.

F236 independently re-checked the 916-byte `MusicRoom::LoadCatalog` boss function and its separately owned 16-byte jump table. Correcting the signed-digit `while` shape and genuine final free-pointer alias yields the correct 932-byte whole comparison size, with 18 resolved fields, but still only 731/860 non-field bytes matched. Tested real variable declaration hoists and preserved every negative result at `.analysis/f236-music-catalog/`. This function was unaccepted at F236 and received no byte credit at that point; F258 subsequently cold-accepted the entire function.

F238 cold-replays the entire `ResultScene::BuildCounterPage` at `00431350` (664 CODE bytes, 167 native instructions, 30 true relocations). The first source emitted 670 bytes despite matching the native frame size, because VC7 placed the real D3DLOCKED_RECT and 200-byte sprintf buffer in the wrong stack slots. Native-faithful nested scopes (outer locked rect, middle 200-byte line, inner 500-byte message) produce all 544/544 comparable bytes, original EH/GS paths and cold exact. Only `--unit result-scene-build-counter-page-00431350` was cold replayed.

F239 also cold-replays the adjacent **721-byte `ResultScene::BuildRecordPage`** (174 x86 instructions, 26 genuine COFF fields) with 617/617 native non-field bytes. It reads the original selected result record and signed 10-row page window, checks the real deque size and accesses original per-entry names, formats both absent/present record paths, and passes a genuine 2000-byte concatenation buffer through the shared 56-byte glyph and D3D8 texture lifecycle. Its first natural whole C++ source matches without guessed padding, and only `--unit result-scene-build-record-page-00431070` was cold replayed.

F240 newly cold-replays the complete **1,344-byte `ResultScene::RenderCounters` boss** (320 instructions, 44 genuine COFF fields), 1168/1168 nonrelocation bytes. The 132-byte SpriteQuad is the existing independently reconstructed physical owner; the 16-byte RECT must live in a meaningful inner C++ scope to restore actual stack offsets -0x88/-0x98. Native `ScaleQuad` receives three raw IEEE754 DWORD patterns, so a call-only facade preserving float bits emits real MOV/PUSH instead of extra x87 temporaries. The last x87 4-byte discrepancy is resolved by a directly observed `this+0x14` float field: compiler naturally loads the 255.0f target global first then multiplies the member. All 6 digit draws, D3D8 mode calls, quad transform, frame capture, selection, actor and EndFrame calls match. Only F240 was cold replayed; its external callees are not separately credited. Research is in `.analysis/f240-result-render/` and `.analysis/f241-result-digits/` and `.analysis/f242-transition/` and `.analysis/f243-result-init/` and `.analysis/f244-result-advance/` and `.analysis/f245-call-chain/` and `.analysis/f246-name-entry/` and `.analysis/f247-progress-save/` and `.analysis/f248-archive-write/`, `.analysis/f249-archive-writer/` and `.analysis/f251-name-shared/`.

F241 independently cold-accepts the complete **423-byte `ResultScene::DrawDecimalDigits`** that F240 calls six times (127 x86 instructions, 9 native relocations, 387/387 comparable bytes). It preserves true signed decimal quotient/remainder loops for fixed and variable digit counts, separate 16/15px left shifts, 20px atlas row stride and entire RET 0x18. The first ordinary source emitted 459 bytes and put its real number in a different stack slot. Nested meaningful number/132-byte quad/RECT lifetimes restore EBP-4, -0x90, and -0xA0, and native 423 bytes exactly. Only the F241 unit was cold-replayed, not all existing units. Its own main caller's bytes are not double-counted.

F242 cold-accepts the original entire **663-byte `SceneTransition::DispatchMode`** controller at `00431F60`, 157 native instructions, 27 real relocation fields, 555/555 nonfield bytes. The original `RET 4`, signed transition countdown, mode remapping, two sparse switch decision trees and all six independently accepted callback targets are preserved; previous natural source emitted 674 bytes due to wrong switch-case lexical order and JZ/JLE lowering. Reordering only actual original cases and expressing positive nibble guards reproduces the full 663 bytes. Only this affected unit was cold replayed. Full proof and failed first natural source are under `.analysis/f242-transition/` and `.analysis/f243-result-init/` and `.analysis/f244-result-advance/` and `.analysis/f245-call-chain/` and `.analysis/f246-name-entry/` and `.analysis/f247-progress-save/` and `.analysis/f248-archive-write/`, `.analysis/f249-archive-writer/` and `.analysis/f251-name-shared/`.

F243 separately cold-accepts **547-byte `ResultScene::Initialize`** with 127 decoded instructions, 415/415 non-field bytes and 33 real COFF fields. First natural C++ source reproduces genuine EH-backed new(80), physical base ctor and texture manager allocation/load path; all native x87 integer division/addition, score global and actor values, four 900-position/one 1800 animation halfwords, and result stage reset are preserved. Base ctor at `004251C0` retains R108 unknown-origin status, so no independent credit. Only `--unit result-scene-initialize-0042e640` cold replayed.

F244 adds the complete **1,529-byte R065-authored result-scene advancement boss** and both owned four-entry jump tables (32 data bytes, no CODE credit). The first natural C++ source already generated the full 1,561 comparison bytes, all 74 physical fields and 1255/1265 nonfield bytes. Only three real comparison expression orders were different: actor score > saved best, frame >= threshold, pending score > tick step. Reversing their logically equivalent source comparisons reproduces the original register load order, all 1,265/1,265 comparable bytes and both complete switch tables. `--unit result-scene-advance-0042e8f0` cold replayed exact. The existing tracking name `SceneController::AdvanceAt0042E8F0` remains an inferred role, not a proven original class identity. No broad cold replay. Complete evidence is in `.analysis/f244-result-advance/` and `.analysis/f245-call-chain/` and `.analysis/f246-name-entry/` and `.analysis/f247-progress-save/` and `.analysis/f248-archive-write/`, `.analysis/f249-archive-writer/` and `.analysis/f251-name-shared/`.

F245 cold-accepts the whole **220-byte `ResultListScene::PollInput`** called by F244. Its first natural C++ source reproduces 60 native instructions, 136/136 non-field bytes and 21 true fields. It updates the two original input devices, evaluates four independent pairs of 32-bit state globals, and tests three physical keys for the native special-menu shortcut. Only this affected unit was cold replayed, exact; its 220 bytes are separate from already accepted F244 caller code. Complete native/source/cold evidence at `.analysis/f245-call-chain/` and `.analysis/f246-name-entry/` and `.analysis/f247-progress-save/` and `.analysis/f248-archive-write/`, `.analysis/f249-archive-writer/` and `.analysis/f251-name-shared/`.

F246 independently cold-accepts the whole **541-byte `NameEntryScene::UpdatePlayer`** with 151 native instructions, 497/497 nonrelocation bytes and 11 true physical fields. Correct signed 8-byte name entry positioning, 26-wide grid codes, erase/confirm keys, progress-file save and reload (called but uncredited), virtual redraw and presentation are all native exact. Initial natural source emitted 539 bytes due to 32-bit promotion of short assignments; using genuine 16-bit prefix ++/-- restores full 541. Only F246 was cold replayed. Research retained under `.analysis/f246-name-entry/`; incomplete 588-byte fighter release remains a genuine EH/member lifetime challenge under `.analysis/f245-call-chain/`, not accepted.

F247 cold-accepts the whole **297-byte `ProgressRecords::SaveScoreFile`** with 97 original instructions, 253/253 nonrelocation bytes and 11 true fields. First natural source was 296 bytes because of different success-guard branching. Expressing the original fail-fast INVALID_HANDLE_VALUE return reproduces original long jump and native 297 bytes. Native five separate WriteFile operations and 256-byte conditional rand modification loop match without synthesizing data. This is the first exact source for the previously unaccepted F246 save callee; there is no double-counting of existing F246 caller code. Only `--unit progress-records-save-score-file-004169e0` was cold replayed. Full evidence under `.analysis/f247-progress-save/` and `.analysis/f248-archive-write/`, `.analysis/f249-archive-writer/` and `.analysis/f251-name-shared/`.

F248 cold-accepts the entire **456-byte `ProgressRecords::LoadScoreFile`** (154 native instructions, 15 physical fields). This native reader chooses the old <=0x11170 format with 10x10 four-byte score reads, or the new 5-section format matching previously accepted F247. First natural VC7.1 probe had exact length but 25 wrong stack operands; nesting the genuine bytes-read and file-size variables restores 396/396 comparable bytes, all native fields and single-unit cold `exact: 456`. Original research and cold receipt in `.analysis/f248-archive-write/`, `.analysis/f249-archive-writer/` and `.analysis/f251-name-shared/`. The 686-byte `DataArchive::Write` remains an active **full-boss** target; do not credit until independently cold exact.

F249 and F250 independently reconstructed full native **686-byte `DataArchive::Write`** and **429-byte `DataArchive::OpenAndReadIndex`** skeletons with 28/10 actual relocation fields and true file/archive loop semantics, but neither is cold-exact due to VC7.1 stack-scope and local alias alignment. F249 best non-field comparison improves 482/574 -> 495/574 via true read-XOR-write semantics; F250 improved to 366/389 by sharing real loop index and explicitly assigning original XOR expression, while 12 declaration reorderings and nested scope experiments remain negatives. No source/exact credit; complete experiments are in `.analysis/f249-archive-writer/` and `.analysis/f248-archive-write/`, `.analysis/f249-archive-writer/` and `.analysis/f251-name-shared/`. Keep pursuing these authentic large functions.

F251 cold-accepts the complete **494-byte `NameEntryScene::UpdateShared`**, 143 instructions, all 16 physical fields and 430/430 non-field bytes. Initial natural source had all correct code except a 2-byte discrepancy in the last branch; positive edit-if with else return exactly reconstructs native JNZ/JMP layout. Only `--unit name-entry-scene-update-shared-0042b380` cold replayed. Full native and source probes in `.analysis/f251-name-shared/`.

F252/F253 independently cold-accepted five complete authored functions. `CardList::EncodeCharacterFile` is the full 432-byte native file converter with 15 authentic relocations, real `cardlist.txt`/`.dat` paths, byte stream XOR and Win32 read/write/close. Four 377-byte decimal painters use the same verified VC7.1 `SpriteQuad`/`RECT` lifetimes but genuinely different original text atlas widths: **15×16** for music and **19×20** for three replay/result routines, matching all 341/341 non-field bytes and 9/9 relocations apiece. The pre-existing dirty source and unit definitions were retained and independently cold-replayed one by one. Native SHA files/diagnostics: `.analysis/f253-digit-family/` and `.analysis/f252-cardfile/`. **F249 686-byte writer and F250 429-byte archive index remain unaccepted**, despite full-function source and repeated physical stack investigations. Do not credit either before cold exact.

F254 investigated the full **1,268-byte `SpriteScene::RenderMirroredNode`**: whole source and original 324 native instructions reconstructed, but natural probes still differ in the two genuine SpriteQuad stack-slot allocations and some x87 expression lowering. Twenty-four explicit real-variable lifetime permutations did not restore the original 1,268-byte extent; **no exact credit**. F255 independently reproduced all 118 native control-flow instructions of the 429-byte `CardList::LoadCharacterFile`, including real deque pointer temporaries and file data, but it still emits 447 bytes. Twenty-two real declaration-order probes failed, so **no byte credit**. Private records live under `.analysis/f254-sprite-boss/` and `.analysis/f255-card-plain/`.

F256 cold-accepted the entire **398-byte `ResultScene::LoadSelectedCharacterResources`**, 91 original x86 instructions, 318/318 comparable non-field bytes and all 20 physical COFF fields. Original destruction is **nonvirtual** at `00425460`, not a vtable dispatch as initially guessed. The native selector is evaluated independently in both special/normal card-list branches; the texture manager genuinely allocates 80 bytes with EH cleanup and loads the original character asset. Only F256 was cold-replayed exact; its encoded-card loading callee at `00431B60` is still unaccepted and uncredited.

F257 independently cold-accepted the complete **298-byte `MusicRoom::EncodeCatalogFile`** at `00427300`, all 100 native instructions, all 254/254 non-relocation bytes and 11/11 real COFF fields. A first full C++ probe had 222/254 comparable bytes due solely to observed stack variable placements. Genuine nested HANDLE, transfer count, file size, buffer, rolling XOR key/delta, index and allocation/free pointer lifetimes restore original local slots, including the native operator new and free transfers. Both `musicroom.csv` read and `musicroom.dat` create/write paths, all real failure branches and original 0x5C/0x5A rolling byte-XOR are preserved. Only `--unit music-room-encode-catalog-file-00427300` was cold-replayed. The separately reviewed 916+16-byte `MusicRoom::LoadCatalog` boss was nonexact at this point; F258 independently closed and accepted its entire native extent. Preserve `.analysis/f254-music-file/` (F257 investigation).

F258 **cold-accepts the complete 916-byte `MusicRoom::LoadCatalog` boss** at `00426DD0`, with the entire 16-byte four-entry switch table compared separately but not counted as CODE. Ghidra confirms the full `00426DD0..00427163` function and the following physical four-target table `00427164..00427173`. Whole target CODE SHA256 `3df59d06537c81eb8d58af1a193eafdab1035d96204384244e8250b949cf294a`, and full 932-byte SHA256 `1a5816e578f8af00aa4a14dc6ad0b4c0998c7539e5a46985422793cedf9c3017`. Existing F236 scope probe previously matched only 744/860 non-field bytes with an incorrect 0x50-byte stack frame. The F257 independently demonstrated allocator lifetime mechanism led to a new complete native-guided lifetime graph matching 852/860 with the correct native 0x48-byte frame; declaring three *actually used* independent string-allocation pointers restores their real temp slots and the separate final free alias, yielding all **860/860** nonfield bytes and **18/18** original physical relocations, including the full four table destinations. Source is `src/MusicCatalogLoadF258.cpp`; only `--unit music-room-load-catalog-00426dd0` cold-replayed and reported exact. This accepts 916 new authored CODE bytes, not 932. Original complete scene/record/archiver classes and independent external callees remain uncredited; all 97 unknown origins stay unknown. Retain `.analysis/f258-music-catalog-alloc/` and F236 negative probes. No artificial padding, fake returns, masks, byte patches, assembly, cropped bodies or all-unit cold replay.

F259 **cold-accepts the complete 792-byte `ReplayRecords::LoadRecord`** at `00413AC0`, all 274 native x86 instructions, 676/676 comparable non-field bytes and all 29 genuine COFF fields. The F216/F233 historical best was only 639/676 with wrong `HANDLE`, record count and `ReadFile` transfer stack slots. Native-grounded nested real source variable lifetimes (record index, dword item, raw word, entry count, handle, byte item, transfer size) fixed 35/37 originally differing comparable bytes, reaching 674/676. The last two bytes were not a manual padding fix: independent native short-word conversion proved the original signed-word `Push(const short&)` call constructs an implicit temporary at EBP-0x1E from an `unsigned short` read at EBP-0x0C. The genuine conversion `Push(static_cast<short>(rawWord))` restores 676/676 bytes and the real 00414640 callee ABI. Pinned VC7.1 cold replay of only `--unit replay-records-load-record-00413ac0` yields exact for all 792 CODE bytes and 29 actual fields. Native file reads and four separate typed list loops remain complete. Preserve `.analysis/f259-replay-load-lifetimes/` and F216/F233 negatives; caller/record layouts and external container bodies remain unproven and uncredited.

F260 **cold-accepts the full 343-byte `ResultScene::PollInput`** controller at `00430D80`, all 84 native x86 instructions, all 235/235 comparable nonrelocation bytes and 27/27 authentic physical COFF fields. The first independently written natural VC7.1 C++ probe matched the entire native extent without compiler-shaping hacks. It preserves the original two input polling calls, four reset scene direction/action bytes, six paired positive/negative direction/action comparisons against the two 0x48-spaced input frames, four real `00407170` key-state queries, and the guarded `004018A0` window-mode call. Only `--unit result-scene-poll-input-00430d80` cold-replayed exact; no external input implementation, unproven scene layout or 97 pending origins credited. Private original Ghidra function/decompile/native assembly and full probe are under `.analysis/f260-result-poll/`.

F261 cold-accepts both **native music catalog record lifetime helpers**: 50-byte 16-instruction constructor `00427430` and 82-byte 30-instruction destructor `00427470`, with 50/50 and 70/70 nonrelocation bytes and 0 and 3 true COFF fields respectively. A naturally aligned `signed char` and three owned `char*` members occupy 16 bytes, matching the independent 60-record array used by MusicRoom initialization. Genuine nested destructor pointer/free scopes restore original EBP-4/-8/-C cleanup temp slots; no synthetic padding or unknown full scene layout is introduced. Both units were cold replayed together as `2/2 exact` from one fresh VC7.1 object, not all units. Retain `.analysis/f261-music-record/` and inspect these accepted record helpers when reconstructing `MusicRoomScene::Initialize` at `00425750` (372-byte EH array ctor boss).

F261 also independently examined the entire 746-byte `SpriteSequence::RenderElements` at `00411110` (R035 authored) and developed a natural complete list/quad/texture/transform source, but its first genuine pinned VC7.1 probe emits **717 bytes** instead of 746 and has a different 0xC0 stack frame vs native 0xBC. It remains a **nonexact boss** with no CODE credit. Full Ghidra function and native assembly and the retained negative source are under `.analysis/f261-sprite-sequence/`; do not infer exactness from conceptual similarity.

F262 **cold-accepts the whole 372-byte native `MusicRoomScene::Initialize`** scene constructor at `00425750` (105 original x86 instructions, 280/280 nonrelocation bytes and 23/23 true physical COFF fields). First natural C++ translation precisely reproduced VC7.1 EH, the standard CRT array constructor for **60** of the separately F261-cold-accepted **16-byte records** at scene+0x1C, 80-byte texture-manager `new`, four 00401C20 graphics surfaces, actual source filenames and music roots, complete F258-cold-accepted catalog loader call plus catalog/track/title controllers and native three music state flags. Inherited base scene constructor `004251C0` remains R108 origin-unknown and uncredited. This is a physically grounded partial scene lifetime only; original nominal layout, parent identity, other callees, and 97 unknown origins remain unproven/uncredited. Only `--unit music-room-scene-initialize-00425750` cold-replayed exact; preserve `.analysis/f261-music-init/` and the F261 record source. The adjacent **244-byte `MusicRoomScene::ReleaseTexturesRecordsAndAudio`** at `004258D0` has now also been cold-exact accepted as F263, using the same genuine 60-record lifetime. Do not re-credit it.

F263 **cold-accepts all 244 CODE bytes of the complete `MusicRoomScene::ReleaseTexturesRecordsAndAudio`** destructor at `004258D0`: 77 original x86 instructions, 196/196 nonrelocation bytes, 12 real COFF fields. A first complete ordinary C++ source generated the identical native EH state, 4 original D3D8 COM `Release` virtual-slot-2 calls, nonvirtual scalar deleting texture manager at `00425460`, three real game-audio calls, and compiler-generated 60-element `MusicCatalogRecordF261` array destruction through native `_eh_vector_destructor_iterator_` (00641D4A), followed by separately authored/exact base destructor `00431F40`. The constructor F262 and both F261 record helpers remain independently accepted; no code credit is duplicated. Only `--unit music-room-scene-release-004258d0` cold-replayed exact. Preserve private `.analysis/f263-music-release/` and prior MusicRoom research. The 97 unknown origins remain uncredited and full nominal scene/texture class layouts are still provisional.

F264 **cold-accepts all 366 bytes of `ResultListScene::Initialize`** at `0042F710`, 96 original x86 instructions, 298/298 nonrelocation bytes, 17/17 native COFF fields and real EH state. Native `004251C0` base ctor (R108 still origin-unknown) and 20-byte physical VC7 deque default constructor `00420320` (library excluded) were preserved without assigning their bytes to authored coverage. The original new(80) texture manager and four-slot texture load, 1024x512 image buffer, signed mode flags, original ten-progress-record loop, separately F256-accepted character loader and F238-accepted result page builder all match. The first whole C++ source emitted the correct 366 length/17 fields but had exactly one byte difference: guessed unsigned index produced `JAE` at offset +0x128 versus native `JGE`; real `int` index restores exact. Only `--unit result-list-scene-initialize-0042f710` independently cold replayed. Preserve `.analysis/f264-result-list-init/` and adjacent 229-byte `ResultListScene::Release` at `0042F880` is now also exact (F265), with no double-counted bytes. This pushes reviewed authored-byte coverage to **40.00%**, still far below the 98% goal; conservative coverage stays 39.93%, and 97 unknown origins are not credited.

F265 **cold-accepts the paired 229-byte `ResultListScene::Release`** at `0042F880`, full 68 decoded instructions, 189/189 comparable bytes and all 10 physical COFF relocations. The first natural C++ translation generated the exact complete native EH destructor, with original ClearEntries `00431940`, two conditional nonvirtual texture deletes on `this+0xC/+0x8`, native D3D8 COM slot-two Release at `this+0x10`, the automatically emitted 20-byte VC7 deque destructor at `this+0x18` through library-only `00420420`, and already accepted base destructor `00431F40`. Only F265 was cold replayed exact; no additional credit for library/CRT, external ClearEntries or origin-unknown R108 base constructor. Preserve `.analysis/f265-result-list-release/`. The matching F264 constructor is independently accepted.

F266 **cold-accepts the complete 395-byte ReplayPlaybackScene::Initialize** scene constructor at `0042C3D0` (106 original instructions, 299/299 nonrelocation bytes, all 24 true COFF fields). Full natural C++ exactly reproduces three separately verified native 20-byte deque constructor calls at scene+0C/+20/+34, an explicit queue Clear at +0C, EH-backed 80-byte texture creation/load from replay.dat, two genuine global actor virtual deleting destructors and null stores, independently F231 accepted replay directory scanner, and original two control/state fields. Its scene base ctor R108 remains unknown-origin and library deque implementations are uncredited. Only `--unit replay-playback-scene-initialize-0042c3d0` cold replayed exact; save the entire native/COFF and source proof at `.analysis/f266-replay-playback-init/`. The original 265-byte `ReplayBrowserScene::DestroyOwnedReplayFiles` at `0042C560` was subsequently cold-exact accepted at F267; do not double-credit it.

F267 **cold-accepts the complete 265-byte `ReplayBrowserScene::DestroyOwnedReplayFiles`** destructor at `0042C560`, 76 native x86 instructions, all 205/205 nonrelocation bytes and 15 genuine physical COFF fields. First native-faithful C++ source reproduces original saved controller word, full unsigned indexed deque size/At loop and actual `free` of each owned replay filename, queue Clear and nonvirtual texture cleanup, then automatic three-member deque destruction in reverse order with native EH states and accepted base scene destructor. All three 20-byte members and their library calls were independently grounded against F266 constructor, not invented. Only `--unit replay-browser-destroy-owned-files-0042c560` cold-replayed exact. Preserve `.analysis/f267-replay-release/`. The independent F231 filename producer/scanner and F266 constructor are accepted but not double-counted; all 97 origin-unknown cases remain pending.

F268 **cold-accepts the full 310-byte native `ReplayScene::PollPlaybackInput`** controller at `0042D330`, 84 original x86 instructions, 202/202 comparable nonrelocation bytes and 27/27 physical COFF fields. The original global input operators, signed 32-bit direction guards, four key-state calls and window-mode shortcut are independently reviewed and also appear in accepted F260. Crucially, the actual replay scene outputs are at +0x4D/+0x4E/+0x4F/+0x50 (not F260's +0x1BF..1C2). Its entire native CFG and all real relocation targets were verified separately before one-unit cold replay exact. Neither other controllers nor common input helper code is double-credited. Preserve `.analysis/f268-replay-input/`.

F268 separately reanalyzed the **full 746-byte `SpriteSequence::RenderElements` boss** at `00411110` (R035 authored). Correcting actual early exit control flow to two native `JNZ/JMP` paths, native floating-point `!=` branch order and nesting the genuine counter gives a **734-byte** complete natural C++ probe with **198/198 decoded x86 instructions** matching the native instruction-sequence shapes; the original is 746 bytes. The remaining 12 bytes are attributable to four observed short versus long EBP local-offset instructions: two uses of the real `end` iterator (native -0x9C, object -0x10), and two uses of the real `x` coordinate (native -0x98, object -0x0C). Correct full frame is now 0xBC and genuine original `this` stack position is recovered. Several meaningful scope, real RECT/tint placement, declaration ordering and signed/float branch controls remain negative; no truncation, masks or fabricated padding. **Do not credit any of these 746 CODE bytes yet**. Best full-size native evidence, all source experiments and operand-shape diff at `.analysis/f261-sprite-sequence/`; focus next on real local lifetime allocation rather than repeating superficial names.

F269 **independently cold-accepts the entire 315-byte `ReplayScene::Initialize`** at `0042A180`, all 84 decoded native x86 instructions, 219/219 comparable nonrelocation bytes, 24 authentic physical COFF fields and true EH constructor/return. One first complete natural C++ source produces the exact native base scene constructor call, 80-byte EH texture allocation and replay.dat asset load, three short resets, real progress selection from two globals, score insertion through actor's +0x2D0 field, one 8-bit result-state storage and replay path selection. R108 origin-unknown base constructor and external score functions have not received duplicated CODE credit. F268's already committed 310-byte input poll at `0042D330` is **not** reaccepted or separately credited: its identical untracked experiment was checked against the tracked unit and archived privately. Only F269 `--unit replay-scene-initialize-0042a180` cold-replayed exact with all authentic EH and relocs. Preserve `.analysis/f268-replay-scene/`.

F271 **cold-accepts the COMPLETE 1,185-byte `Graphics::DrawProjectedTexturedQuad` boss** at `00402D50..004031F0` (291 independently decoded x86 instructions, 1,037/1,037 comparable nonrelocation bytes, all 37 authentic COFF relocation fields). Full original function SHA256 `dcda68d89e3a45c1464d845b321d7228b79a1e7e9290ea0470ed594768553769`. The native D3D8 routine creates four real 28-byte projected vertex records, reads a surface `D3DSURFACE_DESC`, converts actual width/height, computes a reused perspective factor for each vertex, exits early on clipping, preserves full x87 position/depth and UV calculations, scales/translates all vertices, optionally multiplies all three color channels (three original `__ftol2` calls), binds the texture if its cache changes, then draws the original **D3DPT_TRIANGLEFAN** (not triangle strip) with two triangles and stride 28. A first full natural C++ control emitted 1,085 bytes; correcting original early-return branch form and the single real reused projection factor yielded 1,185 bytes and 997/1,037 comparable bytes. The remaining actual EBP-slot mismatches were solved by a genuine nested lifetime for that factor (native `surface` EBP-0x9C, width -0x98, height -0x94, projection -0xA0), while the correct triangle fan fixed another real one-byte semantic error. The final complete C++ matched all 37 field destinations and cold-replayed exact using only `--unit graphics-draw-projected-textured-quad-00402d50`. Preserve original native listing/negative controls and final proof under `.analysis/f271-graphics-projected/`, source at `src/GraphicsProjectedQuadF271.cpp`. This is independent R001-authored CODE; do not credit Direct3D8/CRT `__ftol2` bodies or unrelated library callees; 97 unknown origins remain unresolved. No artificial stack padding, fake locals, copied target machine-code, masked fields or truncated function.

F270 **did not** cold-accept the 497-byte `CharacterSelectScene::UpdateCancelAnimation` at `00435870`. The first full natural C++ retained all 13 original relocations and emitted the full 497-byte source with **438/445** comparable nonrelocation bytes; one physically distinct x87 equality with native constant `60.0f` at `00658264` loads operands in the opposite order to VC7's current source. Actual control/data-flow alternatives (global literal, direction, const/volatile, array indexing, typed accesses and de Morgan) did not improve that genuine seven-byte nonfield mismatch, so no 497 CODE bytes are credited. Keep all negative sources at `.analysis/f270-character-cancel/`; don't substitute assembly or literal target bytes.

Relevant full native proofs: `config/match-units.toml`,
`config/exact-adoptions.json`, sources `src/*F222.cpp`/`src/*F223.cpp`,
and `docs/KNOWLEDGE_BASE.md`. The cold-replay logs are private in
`.analysis/f222-marisa-reset/`, `.analysis/f223-fighter-ctors/`, and `.analysis/f224-youmu-lifecycle/`, and `.analysis/f225-big-functions/` and `.analysis/f226-replay-browser/`, `.analysis/f227-fighter-recovery/`, `.analysis/f226-player-choice/` and `.analysis/f228-confirmation/` and `.analysis/f229-character-select/` and `.analysis/f230-selection-helpers/` and `.analysis/f231-replay-scan/`, `.analysis/f232-append-scope/`, `.analysis/f233-record-scope/`, `.analysis/f234-music-select/` and `.analysis/f235-music-render/`, `.analysis/f236-music-catalog/` and `.analysis/f238-result-page/` (F238 and F239), and `.analysis/f240-result-render/` and `.analysis/f241-result-digits/` and `.analysis/f242-transition/` and `.analysis/f243-result-init/` and `.analysis/f244-result-advance/` and `.analysis/f245-call-chain/` and `.analysis/f246-name-entry/` and `.analysis/f247-progress-save/` and `.analysis/f248-archive-write/`, `.analysis/f249-archive-writer/` and `.analysis/f251-name-shared/`.
Earlier accepted functions remain in the canonical ledgers. **Do not run any all-unit cold replay**; user explicitly requires only newly changed/affected units. Keep builds serialized/headless.

## 3. Unsolved **large** functions — recommended next work

These are **diagnostics, not accepted code**. Each native function needs full
body/owned-table, origin and relocation review before any adoption.

| Function / entry | Target | Best prior compiler evidence | Retained research |
| --- | ---: | --- | --- |
| ReplayRecords::AppendRecord `00413DE0` | 1,252 B | F219 control **1,025/1,052**, but later F225 `F219LocWBeforeAll` correctly yields **1,033/1,052** non-field bytes; remaining true iterator slot differences | `.analysis/f219-append-record/`, `.analysis/f225-big-functions/` |
| ReplayRecords::FinalizeFile `004138E0` | 375 B | Natural variants 342/372/384/396 B; pointer lifetimes/frame unknown | `.analysis/f218-replay-file/` |
| BattleScene destructor `0043B0B0` | 248 B | Exact length/flow but 9–11 local-stack field byte differences | `.analysis/f200-battle-dtor/`, `.analysis/f215-battle-release/` |
| Giant actor control `004AC040` | very large | Full baseline still nonexact; many closed tests, avoid repeating blindly | `.analysis/character-move-4ac040/`, archived knowledge |

F236 unsuccessfully rechecked the native 916+16 extent and four original table destinations. Its best 744/860 nonrelocation bytes and 0x50-frame mismatch are a historical negative control, now superseded by independently cold-exact F258. Retain `.analysis/f236-music-catalog/EXPERIMENTS.md` and the successful F258 probes rather than re-running the old scope sweeps.

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

1. Inspect dirty state and retain meaningful experiments. Continue work within
   the assigned scope and preserve concurrent edits reported by the user.
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
   `known-symbols.csv`, `exact-adoptions.json` and its checkpoint hash.
   Update progress from live ledgers, not remembered counts.
6. Run tracking, affected cold units, and `git diff --check`. Run `scripts/ci.py`
   only for exact/checkpoint/accounting or test infrastructure changes. Commit
   material progress with the commit subject prefix requested for that session.
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
