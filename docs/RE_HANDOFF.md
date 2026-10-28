# TH075 — current reconstruction handoff

**Maintained: 2026-10-28, after F339.** Read this document, then check the **live repository**. The current user explicitly wants both large/core bosses and small leaves tackled seriously, tangible progress committed immediately with subject `gpt-web: ...`, and **only changed/new units cold-replayed**. The user reports no other sessions: inspect and finish all dirty work; never skip, reset, overwrite or silently discard it.

## 1. Trusted state and first commands

Canonical evidence is the pinned original PE, `config/function-origins.csv`, `config/functions.csv`, `config/match-units.toml`, `config/exact-adoptions.json`, the source under `src/`, and the result of a **cold replay of the affected unit**. This handoff is a navigational snapshot; generated counts and all per-function names/sizes must be checked from the current ledgers. Older documents and Ghidra names are hypotheses, not authority.

| Item | Verified snapshot |
| --- | --- |
| Git | `main`; latest reconstruction commit **`26ac6fd`** (F339), preceded by `a8a4496` (F338), `3a16048` (F337), `18f19d6` (F335), `c9e0a1f` (F334) |
| Pinned target | user-supplied Japanese `resources/th075.exe` v1.11; SHA256 `bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`; **never** `th075c.exe` |
| Exact and source-present | **645 functions / 645 exact units** |
| Accepted authored CODE | **813,859 bytes / 1,973,516 reviewed bytes = 41.24%** |
| Conservative | **41.16%**, including 3,608 bytes with unresolved origin |
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

The full register of **all 645** accepted functions is in `config/functions.csv` and `config/match-units.toml`; this table intentionally highlights only the newest, important independent CODE extents. No called function, imported CRT/Win32 code, or owned jump-table bytes are counted twice.

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

**Corrections to old notes:** The 686-byte writer and 429-byte reader are both **exact** (F339/F338), not pending F249/F250. The full 1,252-byte replay writer and 375-byte finalizer are both **exact** (F326/F328), not pending F219/F218/F289. The 1,766-byte font rasterizer is **exact** (F319), not pending F299/F302. The 301-byte glyph loader is **exact** (F318), not pending F291. The 916-byte MusicRoom catalog + separately compared 16-byte jump table is **exact in F258** (916 CODE credit only). Other accepted 1,000+ byte bosses include F271 projected quad (1,185), F278 pattern chooser (1,264), F282 resource loader (1,186), F292 overlay text box (1,385), F294 effects catalog (1,722), and F244 scene advance (1,529 CODE). Earlier failures remain useful *historical controls*, but must never be presented as current unaccepted work.

## 3. Active authored targets — investigate **complete functions**

These remain **unclassified/nonexact** in `config/functions.csv`, despite promising probes. Numbers here are *diagnostic* (not adoption or CODE credit). Prioritize at least one boss alongside leaves, and inspect the referenced original native files and failed probes before launching fresh sweeps.

| Function (native start) | Whole CODE | Best known / actual blocker | Retained private evidence |
| --- | ---: | --- | --- |
| `SpriteSequence::RenderElements` `00411110` | **746** | Full 746-byte / 33-field C++ probe **599/614** comparable. Only three x87 `FLD` comparisons remain, 15 mismatched bytes. Different const/volatile/ref/inequality operands did not fix native load order. | `.analysis/f261-sprite-sequence/`, `.analysis/f331-sprite-nativeframe/`, `.analysis/f332-sequence-x87/`, `.analysis/f336-sprite-accessor/` |
| `SpriteScene::RenderMirroredNode` `00410A00` | **1,268** | 324 original instructions; natural 1,279-byte shape still wrong in x87/quad lifetimes. | `.analysis/f254-sprite-boss/`, `.analysis/f289-mirrored/` |
| `SuikaFighter::UpdateSpecialState` `005C3FB0` | **874** | Full original length, 20 fields, **742/794** comparable; native x87 comparison/actor-relative evaluation differs. | `.analysis/f313-suika-boss/`, `.analysis/f314-suika-shots/` |
| `CharacterSelectScene::UpdateCancelAnimation` `00435870` | **497** | Full original length, 13 fields, **438/445** comparable; one seven-byte x87 operand order. | `.analysis/f270-character-cancel/` |
| `AuxEffectManager::AdvanceAndPruneTwoLists` `005F7D80` | **276** | Full original length, ten fields, **233/236** comparable; freed pointer/end-iterator stack placement. | `.analysis/f298-aux-lifetimes/`, `.analysis/f327-aux-end-freed/` |
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
