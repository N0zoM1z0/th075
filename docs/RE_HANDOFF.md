# TH075 — current reconstruction handoff

**Maintained: 2026-10-28, after F366.** Read this document, then check the **live repository**. The current user explicitly wants both large/core bosses and small leaves tackled seriously, tangible progress committed immediately with subject `gpt-web: ...`, and **only changed/new units cold-replayed**. The user reports no other sessions: inspect and finish all dirty work; never skip, reset, overwrite or silently discard it.

## 1. Trusted state and first commands

Canonical evidence is the pinned original PE, `config/function-origins.csv`, `config/functions.csv`, `config/match-units.toml`, `config/exact-adoptions.json`, the source under `src/`, and the result of a **cold replay of the affected unit**. This handoff is a navigational snapshot; generated counts and all per-function names/sizes must be checked from the current ledgers. Older documents and Ghidra names are hypotheses, not authority.

| Item | Verified snapshot |
| --- | --- |
| Git | `main`; pre-F366 reconstruction commit **`f13af21`** (F364), preceded by `0afc5b7` (F363), `0cce233` (F362); F366 commit follows this handoff update |
| Pinned target | user-supplied Japanese `resources/th075.exe` v1.11; SHA256 `bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`; **never** `th075c.exe` |
| Exact and source-present | **661 functions / 661 exact units** |
| Accepted authored CODE | **822,120 bytes / 1,973,516 reviewed bytes = 41.66%** |
| Conservative | **41.58%**, including 3,608 bytes with unresolved origin |
| Origin review | 1,002 authored, 2,671 library, 581 compiler, **97 pending** across 4,351 provisional candidates |
| Goal | **98% not reached**; Git and local cold results are not external Oracle receipts |

```bash
git status --short --branch
git log -5 --oneline
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/validate-tracking.py --require-target
scripts/repo-python scripts/report-reconstruction-status.py --summary
scripts/repo-python scripts/ghidra.py check
```

If **any** dirty source, unit, or manifest is present, first inspect its exact existing content, private `.analysis/` proofs and local cold receipts. Take ownership and finish the work; do not assume another agent/session owns it. In particular, F339 was discovered as uncommitted matching source/unit and successfully adopted in `26ac6fd` rather than discarded.

## 2. Newly closed chains — **not** the backlog

The full register of **all 661** accepted functions is in `config/functions.csv` and `config/match-units.toml`; this table intentionally highlights only the newest, important independent CODE extents. No called function, imported CRT/Win32 code, or owned jump-table bytes are counted twice.

| Unit / accepted address | Whole CODE | Authentic fields | Evidence |
| --- | ---: | ---: | --- |
| F319 `FontSurface::RasterizeText` `0041C2E0` | 1,766 | 15 | `src/FontRasterizeTextF319.cpp`, `.analysis/f319-font-state/` |
| F326 `ReplayRecords::AppendRecord` `00413DE0` | 1,252 | 50 | `src/ReplayAppendRecordF326.cpp`, `.analysis/f326-append-physical/` |
| F328 `ReplayRecords::FinalizeFile` `004138E0` | 375 | 15 | `src/ReplayFinalizeFileF328.cpp`, `.analysis/f328-replay-final/` |
| F334 `EventQueue::RunWorker` `00423B40` | 273 | 19 | `src/EventQueueRunWorkerF334.cpp`, `.analysis/f334-worker-physical/` |
| F335 `EventQueue` acquire/release `004239F0` / `00423A90` | 155 + 143 | 18 + 16 | `src/EventServiceAcquireF335.cpp`, `src/EventServiceReleaseF335.cpp` |
| F337 `BattlePointerQueues::ReleaseEntries` `005F7140` | 162 | 8 | `src/BattlePointerReleaseF337.cpp`, `.analysis/f337-archive-close/` |
| F338 `DataArchive::OpenAndReadIndex` `0041D510` | 429 | 10 | `src/ArchiveOpenReadIndexF338.cpp`, `.analysis/f338-archive-physical/` |
| F339 `DataArchive::Write` `0041D260` | 686 | 28 | `src/ArchiveWriteF339.cpp`, `.analysis/f339-archive-write-frame/` |
| F340 `DataArchive::SeekNamedEntry` `0041D750` | 164 | 9 | `src/ArchiveSeekF340.cpp`, `.analysis/f340-archive-seek/` |
| F341 `ArchiveCatalog::CloseNamed` `0041D080` | 264 | 19 | `src/ArchiveCatalogCloseF341.cpp`, `.analysis/f341-archive-close/` |
| F342 `DataArchive::AppendReadableFile` `0041D6C0` | 133 | 7 | `src/ArchiveAppendFileF342.cpp`, `.analysis/f342-archive-file-add/` |
| F345 `YukariFighter::UpdateSpecialState` `0059B490` | **679** | **11** | `src/YukariSpecialStateF345.cpp`, `.analysis/f345-yukari-boss/` |
| F346 `CharacterSelectScene::UpdateCancelAnimation` `00435870` | **497** | **13** | `src/CharacterSelectCancelF346.cpp`, `.analysis/f346-cancel-macro/` |
| F347 `SpriteSequence::RenderElements` `00411110` | **746** | **33** | `src/SpriteSequenceRenderF347.cpp`, `.analysis/f346-sprite-literal/` |
| F348 `SuikaFighter::UpdateSpecialState` `005C3FB0` | **874** | **20** | `src/SuikaSpecialStateF348.cpp`, `.analysis/f351-suika-constant/` |
| F353 `ArchiveCatalog::OpenAndRegister` `0041CF80` | **245** | **22** | `src/ArchiveOpenRegisterF353.cpp`, `.analysis/f353-archive-register/` |
| F354 `AuxEffectManager::AdvanceAndPruneTwoLists` `005F7D80` | **276** | **10** | `src/AuxEffectPruneF354.cpp`, `.analysis/f354-aux-slots/` |
| F361 `CharacterAux::RunAt00496C60` `00496C60` | **1,027** | **11** | `src/CharacterAuxSpecial00496C60F361.cpp`, `.analysis/f361-character-aux-family/` |
| F362 `CharacterAux::RunAt00470A40` `00470A40` | **1,027** | **11** | `src/CharacterAuxSpecial00470A40F362.cpp`, `.analysis/f361-character-aux-family/` |
| F363 `CharacterAux::RunAt00555530` `00555530` | **1,028** | **11** | `src/CharacterAux00555530F363.cpp`, `.analysis/f363-character-aux-reordered/` |
| F364 `CharacterAux::RunAt00577750` `00577750` | **1,121** | **11** | `src/CharacterAux00577750F364.cpp`, `.analysis/f364-aux-timer/` |
| F366 `BackgroundStage::ApplyBG02a/b/cBlend` `0044B980/0044BEA0/0044C3C0` | **60×3** | **6×3** | `src/BackgroundBlendF366.cpp`, `.analysis/f366-background-blend/` |

**F340:** the companion archive entry seek at `0041D750` is independently cold exact for its whole 164-byte function including every one of its nine external references. It uses genuine iterator and `strcmp` semantics, returns the archive handle after `SetFilePointer` or `INVALID_HANDLE_VALUE` if not found. The original private archive list remains borrowed, not instantiated.

**F341:** completed the neighboring native **cdecl**, rather than guessed thiscall, archive registry close function at `0041D080`. Its two genuine deque iterator types, both initialized end cursors, `strcmp`, native scalar-deleting-destructor call, simultaneous erase paths and postfix increment are all covered by a **264-byte** full physical cold comparison (19/19 relocations). The borrowed 32-byte stack cursor layout preserves all four true iterator positions; its names do not assert complete original owner layouts.

**F342:** full 133-byte archive input file registration reconstructed: native `CreateFileA`, `GetFileSize`, original 100-byte filename/size/offset wire record, `strcpy`, `CloseHandle` and original linked-list `AddEntry`. The original `/GS` security cookie is preserved, all seven actual fields cold exact. The earlier 130-byte negative small-owner control is superseded by this complete original 133-byte result.

**F345:** a real **679-byte boss** is now complete: the entire Yukari-specific special-state handler at `0059B490`, 191 original x86 instructions and all 11 true physical COFF fields, 635/635 non-field bytes, independently cold 1/1 exact. Used accepted F062 character-aux as a **testable expression/codegen control**, but recovered different Yukari-only short timers, effect ID 830, strict action windows, and opponent-relative bounds from the actual target. First trial matched 581/635, fixing a genuine signed 16-bit wrap threshold and retaining the precise original F062 `FLOAT`/`OPPONENT_FLOAT` macro *lexical form* restored native x87 evaluation and every last byte. No old F062 bytes are re-credited.

**F346:** completed the previously pending 497-byte character-select cancel scene update: every native 497 CODE byte (114 instructions) and all 13 actual relocation targets cold exact, 445/445 non-field byte matches. Building on F345, an *unparenthesized lvalue macro only for the final +C0 float equality* naturally reproduces `FLD [global stop]; FLD [indexed field]` while the four earlier animation comparisons retain their original forms. Earlier blanket macro removal was a negative control, not success. Original scene layout and sound callee remain borrowed and are not credited.

**F362:** recovered the second independent 1,027-byte R049-authored character-auxiliary controller at `00470A40`. The separate native 240-instruction function and its actual three fixed-address effect calls, complete branching and all eleven COFF fields were independently verified. Native operations match the already exact F062 source pattern, while `00470A40` owns unique original CODE and solved relocation destinations; shared callee/CRT bytes are not counted again. Single affected F362 cold replay **1/1 exact**.

**F343 (still open):** `ArchiveCatalog::Release` at `0041CE50` was independently redecoded and whole 171-byte C++ codegen achieved **108/115** comparable bytes with all 14 real relocation locations recognized. Seven stack displacements for delete temporaries/name storage differ; exactness remains **unclaimed**, and attempts/probes are retained in `.analysis/f343-archive-release/`. Do not patch arbitrary inert locals to turn this diagnostic into false credit.

**F347:** resolved the former 746-byte sprite sequence render backlog. The native loads **zero first** before each of three x87 `FUCOMPP` tests; expressing the genuine `scale.x/y/z != 0.0f` with the zero literal on the right, instead of the old global-zero-left expression, naturally reproduces the compiler order. The complete 198-instruction native function, all 33 genuine COFF references and the 132-byte sprite-quad construction/draw state cold-match **1/1 exact**. No earlier diagnostic label is treated as proof.

**F348:** the 874-byte complete Suika controller is **now cold exact** rather than pending. The target has 237 real instructions and 20 actual COFF fields. Direct floating-point `FLOAT` and opponent lvalues correct 40 historical x87/actor-relative differences, source `FLOAT(0x50)==0.0f` corrects the initial zero test, and true `OPPONENT_FLOAT(0x44)+20.0f` (constant pool `0065786C`) corrects both projectile X operands. Entire 794/794 non-field bytes and all 20 physical relocations cold-replay exact. This supersedes the F313/F314 742/794 negative probe; it does not credit unrelated random/spawn/sound callees.

**F353:** the full 245-byte R053 cdecl archive registration EH routine now cold matches, all 22 physical relocation references (including native EH handler), both Win32/CRT allocation variants, real `0041D190` constructor and `0041D510` index loader. The original name-list append receives a true null pointer temporary by `const&`; this changes VC7.1 local slots so all 157 nonrelocation bytes align naturally. Borrowed 16-byte allocation carrier does not establish a complete game object layout.

**F354:** the formerly open 276-byte two-side effect queue manager is now **complete cold-exact**. A genuine 20-byte local control record containing the used removed pointer, eight-byte End iterator, index and count precisely recreates the native EBP slots -0x20, -0x1C, -0x14 and -0x10. `EndInto` denotes the original End hidden-sret convention, not a different game function. The complete 93-instruction first-pass Advance / second-pass free-or-erase control matches all 236 comparable bytes and 10 actual physical COFF fields in a single-unit cold replay; the previous 233/236 controls remain private negatives.

**F361:** one additional independently verified **1,027-byte / 240 native instruction** authored character auxiliary special-effect controller at `00496C60` is now exact. The previously exact F062 is a useful compiler-expression reference only; the actual original has effect ID `817`, 1.0f scales, last SpawnTrackedEffect flag `0`, distance policy field +`0xF32` and three separate native spawn windows. These independently checked differences compile to **983/983** identical nonrelocation bytes and all **11** original relocations. Local cold replay only F361 returned **1/1 exact**; original fighter class and private owner name remain provisional.

**F363:** independently cold exact full **1,028-byte** R049-authored character auxiliary special-effect function at `00555530`. In contrast to F062/F361/F362, its native `+0xF0C` opponent-range clamps and short timer come **before** the three one-shot effect-spawn windows. Verified original effect 850, 1.0f scale and 1 linked flag. Reordering the *real* behavior and correcting the per-target values yields native **984/984** nonrelocation bytes, **11/11** true COFF physical references, full 240-instruction 1,028-byte original body, affected-only cold **1/1 exact**.

**F364:** another whole **1,121-byte** R049-authored special-state controller is now cold exact: the original contact update, signed short +0xF0E timer (+2 when +0x3B8==0 and reset if negative or >=360), then genuine effect 899/linked1 at three action windows and original signed +0xF10 distance-policy state. The full source initially matched 1075/1077 bytes; a native-verifiable `>=360` compare instead of the semantically equivalent `>359` restored both remaining original compare bytes. All **1077/1077** nonfield bytes, **11/11** physical relocations and **261** native instructions match, cold replay **1/1 exact**.

**F366:** full 60-byte R231-authored background camera blend callbacks at `0044B980`, `0044BEA0`, and `0044C3C0` are independently exact. Each body really computes two camera-derived integer coordinates via its two original `__ftol2` calls, stores them, then invokes `this+0x18` renderer blend mode 0; no artificial locals were added. Each matches all 36 nonfield bytes and 6 original relocations. Only these three changed functions were cold replayed (**3/3 exact across 1 object**) and jointly contribute **180** original authored CODE bytes.

**Corrections to old notes:** The 686-byte writer and 429-byte reader are both **exact** (F339/F338), not pending F249/F250. The full 1,252-byte replay writer and 375-byte finalizer are both **exact** (F326/F328), not pending F219/F218/F289. The 1,766-byte font rasterizer is **exact** (F319), not pending F299/F302. The 301-byte glyph loader is **exact** (F318), not pending F291. The 916-byte MusicRoom catalog + separately compared 16-byte jump table is **exact in F258** (916 CODE credit only). Other accepted 1,000+ byte bosses include F271 projected quad (1,185), F278 pattern chooser (1,264), F282 resource loader (1,186), F292 overlay text box (1,385), F294 effects catalog (1,722), and F244 scene advance (1,529 CODE). Earlier failures remain useful *historical controls*, but must never be presented as current unaccepted work.

## 3. Active authored targets — investigate **complete functions**

These remain **unclassified/nonexact** in `config/functions.csv`, despite promising probes. Numbers here are *diagnostic* (not adoption or CODE credit). Prioritize at least one boss alongside leaves, and inspect the referenced original native files and failed probes before launching fresh sweeps.

| Function (native start) | Whole CODE | Best known / actual blocker | Retained private evidence |
| --- | ---: | --- | --- |
| `CharacterAux::RunAt00497070` `00497070` | **1,291** | Original native 273-instruction nested 8×36 trigonometric chain; complete natural source now 1,291 bytes, exactly 273 instruction kinds and lengths, but 1043/1167 comparable byte positions, wrong physical stack allocations and at least one float relocation; **not exact**. | `.analysis/f356-character-aux-boss/`, `.analysis/f358-marisa-frame/`, `.analysis/f361-marisa-expression-order/`, `.analysis/f362-marisa-carrier/`, `.analysis/f363-marisa-shorts/` |
| `SpriteScene::RenderMirroredNode` `00410A00` | **1,268** | 324 original instructions; natural 1,279-byte shape still wrong in x87/quad lifetimes. | `.analysis/f254-sprite-boss/`, `.analysis/f289-mirrored/` |
| `SceneObject::ReleaseAt0043B0B0` `0043B0B0` | **248** | Full natural control but nine or more real EBP-slot differences. Name and owner provisional. | `.analysis/f215-battle-release/`, `.analysis/f260-battle-lifetimes/` |
| `ReplayScene::DrawSaveFilename` `0042C270` | **303** | Natural output 341–342 bytes; actual 14-byte prefix, 8-byte glyph bytes and quad scope. | `.analysis/f323-replay-filename/`, `.analysis/f290-replay-filename/` |
| `NameEntryScene::DrawDecimalGlyphLabelAt0042B110` | **169** | Original glyph/quad stack and `/GS` differ; natural 143/170-byte probes fail. | `.analysis/f329-rank-glyphs/`, `.analysis/f330-glyph-packet/` |
| `CharacterMove::AdvanceAt004AC040` | **82,796** | Very large whole R048 control/CFG boss; historical full-function diagnostics, **not exact**. Avoid rerunning old name sweeps. | `.analysis/character-move-4ac040/`, `docs/KNOWLEDGE_BASE.md` |

Keep investigating new major native functions as well. **Do not** retry archived name-only permutations without a new falsifiable physical-slot, expression-order, control-flow or actual lifetime hypothesis. Original object offsets and nominal C++ class names are *borrowed ABI observations*, not reconstructed full private layouts. No asm, byte grafts, inert locals or masks.

## 4. Exact-acceptance procedure — never replay all units

1. Verify original Japanese PE identity, authored-origins evidence and **full native function** including every exit, size, relocations and owned tables (tables compared but not CODE credited). Use `scripts/repo-python scripts/ghidra.py` for read-only decomp and instruction disassembly.
2. Test real semantic C++ source in `.analysis/` against pinned VC7.1. Compile headlessly/serially with the *correct per-function* `/GX` or `/GX-` profile; `scripts/compile-probe.sh` writes regenerable `build/probes/` objects. Use `scripts/repo-python scripts/compare-coff-function.py ... --json` for diagnostics. `structural-exact` alone is **not acceptance** because relocation bytes are separate.
3. When the **whole original CODE** and *all physical COFF relocation offset/type/native solved targets* match, add **one actual unit** in `config/match-units.toml`, then use `scripts/repo-python scripts/replay-exact-units.py --unit UNIT_NAME` (pass multiple `--unit` only for the affected small cohort). **Never** call the no-unit/all-unit cold command.
4. Only after `N/N exact` from affected cold replay: update `config/functions.csv`, `implemented.csv`, `known-symbols.csv`, `reccmp-functions.csv`, `matches.csv`, `exact-adoptions.json`, manifest SHA in `tests/exact_checkpoint.py`, `README.md`, this handoff and progress SVG (`scripts/repo-python scripts/update-progress.py`). Validate tracking with `--require-target`; run `scripts/ci.py` for checkpoint/accounting infrastructure changes; `git diff --check`.
5. Commit tangible, validated progress immediately as `gpt-web: ...`; ensure no unexpected dirty paths remain, and document any genuine blocked experiment in `.analysis/`. All original executable, origin-pending CODE and library/CRT bodies remain uncredited.

Full recipes: [RE_WORKFLOW.md](RE_WORKFLOW.md), `AGENTS.md`, `docs/BUILD_MATCHING.md`. Historical reasoning: [KNOWLEDGE_BASE.md](KNOWLEDGE_BASE.md). Review original native evidence directly rather than trusting those old interpretations.

## 5. Disk/storage hygiene and provenance

**Protect permanently:** `resources/th075.exe`, all `src/`, `config/`, `tests/`, original PE/native listings and best complete negative C++ probes, `.analysis/vc71-wine/`, private `ghidra-project/`, `.tools/`, and H184 explicitly protected original COFF/PDB objects (`.analysis/h184-handoff/active-object-retention.json`). Do not move/truncate the live Wine prefix or re-import Ghidra. `build/matching/` belongs to accepted units; leave it available.

Ignored `build/probes/` contains diagnostic `/Zi` `.pdb` and COFF `.obj` compiled caches. Superseded/unprotected PDBs may be put in **a hash-verified lossless private archive** instead of keeping thousands of loose copies; restore from that archive if native debugging needs one. **Keep original probed `.obj` files and the H184 protected artifacts available**; do not conflate disk cleanup with source cleanup. The **2026-10-28 cleanup** moved 2,031 unprotected historical PDBs (164,417,536 bytes) into the **fully SHA256-verified, lossless 21,768,363-byte** archive
`.analysis/cache-archives/probe-pdb-unprotected-2026-10-28.tar.gz`, then removed only those loose files: **142,295,877 bytes net storage reclaimed** after accounting for archive and inventory. Every original file size, original SHA256 and recovery path is recorded in
`.analysis/cache-archives/probe-pdb-unprotected-2026-10-28-receipt.json`.
Restore a specific PDB from the repository root with
`tar -xzf .analysis/cache-archives/probe-pdb-unprotected-2026-10-28.tar.gz -C . build/probes/<name>.pdb`.
The 15 explicitly H184-protected PDBs and **all COFF `.obj` probes** remain directly available. Cache removal does **not** change tracked exact counts or justify replaying accepted units. Preserve `.analysis/character-move-4ac040/`, which contains active giant-boss evidence, even though its historical JSON snapshots are large.

The old verbose handoff (including its superseded "pending" rows) remains accessible in Git history, e.g. `git show 26ac6fd:docs/RE_HANDOFF.md`. The knowledge base is chronological; an early "nonexact" statement says what was known *then*, never overrides the current ledger or this handoff. Older H184 "stop/no goal" directives are archival and not active.
