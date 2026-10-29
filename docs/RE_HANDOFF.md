# TH075 — current agent handoff

**Maintained: 2026-10-29, after F536; this is the active handoff, not a research diary.** Start by checking the *live repository*; the figures below are a snapshot. The user requires serious work on **whole large boss functions and smaller leaves**, natural C++, independently checked original bytes, and immediate commits using `gpt-web: ...`. **All dirty changes belong to this one work session:** inspect, continue and finish them; never skip/reset/discard them. **Never run a full all-unit cold replay**—only the new or affected `--unit` entries.

## 1. Current authoritative state (not historical hypotheses)

| Item | Verified as of this handoff |
| --- | --- |
| Pinned original | user-supplied **Japanese** `resources/th075.exe` ver1.11; SHA256 `bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`; **never** localized `th075c.exe` |
| Whole exact C++ source | **942 functions / 942 exact units**, **862,649 original CODE bytes** |
| Reviewed original authored coverage | **43.71%** of **1,973,627** reviewed bytes; conservative **43.63%** with pending-origin bytes |
| Origin review | 4,351 provisional candidates; **1,003** origin-classified authored, **96** origin-pending, 3,497 origin-pending bytes |
| Current `owner=authored,status=unclassified` | **25 complete functions**: 22 large fighter bosses + 3 other originals below |
| Goal | **98% original authored bytes NOT attained**; local Git/Cold checks are **not** external Oracle receipts |

```bash
git status --short --branch
git log -5 --oneline
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/validate-tracking.py --require-target
scripts/repo-python scripts/report-reconstruction-status.py --summary
scripts/repo-python scripts/audit-active-handoff.py
scripts/repo-python scripts/ghidra.py check
```

**Trust, in this order:** the pinned original Japanese PE and its physical instructions, `config/function-origins.csv`, live `config/functions.csv`, whole physical COFF comparisons, *targeted* cold replay, `config/match-units.toml`, `config/exact-adoptions.json` and SHA-pinned source files. The provisional class/method names and decompiler locals are **not** authoritative original source declarations. Historical documents can be wrong; recheck against the PE. The complete 941-function accepted register is in `config/functions.csv`, not in this handoff.

## 2. Actual unresolved whole-function authored backlog

**The 22 giant fighter action/advance bosses are the principal coverage barrier.** All are separate, original authored function extents totaling **1,102,055 CODE bytes**; none has an accepted whole C++ source. Together they decode to **292,761 native x86 instructions, 16,861 calls and 84 physical indirect switch instructions**. Their **16,123 separate after-RET DATA bytes** (2,359 DWORD slots and 6,687 sparse index bytes) are *never CODE credit*. Follow [the full fighter cohort audit](FIGHTER_BOSS_FAMILY_DISPATCH.md), its frozen original manifest `config/fighter-boss-dispatch-fingerprints.json`, and read-only `scripts/repo-python scripts/verify-fighter-boss-family.py`. The 11 CharacterObject-family bosses each have one compressed switch; the 11 CharacterMove/Reimu-family bosses have 6–7. Four actual shared byte-index patterns occur, but **identical indices do not mean shared native destinations** and duplicate DWORD destinations are legitimate. For source work, inspect the verified whole [60,999-byte Reimu](REIMU_ACTION_BOSS_DISPATCH.md) and [82,796-byte CharacterMove](CHARACTER_MOVE_ACTION_DISPATCH.md) as starting points, not as “already restored” functions. Full original decompilation and meaningful probes live under `.analysis/f493-reimu-megaboss/`, `.analysis/f509-charactermove-megaboss/` and `.analysis/character-move-4ac040/`.

**Three other authored functions remain nonexact (all require full CODE):**

| Original function / PE address | Size | Best meaningful current evidence / precise blocker |
| --- | ---: | --- |
| `GameApplication::RunAt00602A60` / `00602A60` | **2,987** | **654** original instructions, **123** calls, actual **0x278** frame and **15** scene switch cases. F528 complete native-like C++ `outer0-firsttmp1-while1.cpp` has **2,981 bytes /654 instructions /123 calls /0x278**, all **654/654 ordered x86 mnemonics** but only **224/654 identical complete operands+lengths**, so **not exact**. Most important true EBP locals: scene -0x184 vs candidate -0xC, pathname -0x180 vs -0x158, AppMode -0x3D vs -1, graphics -0x189 vs -0xD. Fix real C++ owner layout and lifetimes, not instruction counts or synthetic padding. See [full native WinMain audit](WINMAIN_ORIGINAL_CONTROL_FLOW.md), `scripts/repo-python scripts/verify-winmain-scene-dispatch.py`, `.analysis/f525-*` through `.analysis/f530-*`, `.analysis/f528-winmain-native-initial-scene/detailed-insn-alignment.tsv`. Original 60-byte after-RET scene table is DATA. |
| `SceneObject::ReleaseAt0043B0B0` / `0043B0B0` | **248** | Genuine virtual destructor with original EH and three owned heap frees. Full natural `/GX` C++ reaches **191/200** original nonrelocation bytes, but physical native texture/delete temporaries at EBP -0x14/-0x10 and actual heap pointers -0x18/-0x1C/-0x20 disagree with compiler allocation order. `.analysis/f215-battle-release/struct0.cpp`, `.analysis/f449-scene-texture-heap-release/`, `.analysis/f533-scene-native-separate-pointers/`. No 248-byte credit. |
| `ArchiveCatalog::Release` / `0041CE50` | **171** | Actually the **nonvirtual local RAII destructor** of the archive catalog, paired with `0041CE10`, as established from WinMain original call/receiver EBP -0x35. Genuine C++ destructor yields complete **171 bytes, 108/115** nonrelocation bytes (14 COFF fields), but physical resource/delete/filename locals at -0xC/-8/-0x10 differ from source -0x10/-0xC/-8. `.analysis/f343-archive-release/`, `.analysis/f531-archive-real-raii-destructor/` and `.analysis/f517-archive-true-name-record/`. Virtual destructor form is wrong (182 bytes). No 171-byte credit. |

**No other `owner=authored,status=unclassified` function is currently in the live ledger.** The **96 pending origins** are a separate provenance classification problem; do not silently count them as authored. The full original authored-byte goal remains distant, even though many smaller game bosses are already exact.

## 3. Important *already solved* functions: do not redo old “pending” experiments

| Previously disputed | Current correct result | Canonical source / batch |
| --- | --- | --- |
| Combat-coordinate transform `00455770` | **111 full CODE, 29 instructions, 4 native DIR32; 1/1 cold exact**. Source uses genuine VC7.1 unparenthesized float lvalues; provisional owner has no observed direct callers. Distinct from all 22 large bosses and the 3 other nonexact originals | `src/CombatCoordinateViewF536.cpp` / F536 |
| GameProgress selected-record increment `00425130` | **92 CODE, 24 insns, no COFF fields, 1/1 cold exact**; actual native codegen requires **postfix** `SELECTED_COUNT++`, not prefix `++` | `src/GameProgressIncrementSelectedRecordF535.cpp` / F535 |
| NameEntry/Result rank labels `0042B110`, `00431890` | **169 + 169 CODE; 2/2 cold exact**; real 132-byte quad member in used local aggregate, separate glyph[8], real `/GS` | `src/NameEntryResultRankGlyphLabelsF516.cpp` / F516 |
| Replay filename glyph draw `0042C270` | **303 CODE, 1/1 cold exact**; correct prefix+132-byte quad aggregate and separate real glyph[8] | `src/ReplaySceneDrawSaveFilenameF514.cpp` / F514 |
| StaffRoll state/timing `00438C20` | **208 CODE, 1/1 cold exact**; real fighter/score branches *inside* outside-time-window guarded scope | `src/StaffRollSceneAdvanceF504.cpp` / F504 |
| Fighter and stage loading bosses `004183D0` and F407 fighter load | **3,765** and **3,232** original CODE already exact in F389/F407; do not double count | `src/BattleStageLoadBossF389.cpp`, `src/BattleCharacterLoadBossF407.cpp` |
| DataArchive writer/reader, replay finalizer, font rasterizer | 686/429, 375, 1,766 CODE **already exact** | F339/F338, F328, F319 |
| Original WinMain window callback `00603650` | **83 CODE already exact**, *not* the adjacent 2,987-byte WinMain | F468 |

Earlier F323/F424/F425/F450/F475/F478/F495/F503/F506/F510–F513/F521–F524 probes are **historical negative controls**. A statement such as “rank labels/Replay/StaffRoll/progress counter remain unclassified” in older research means **then**, not **now**. The chronological [KNOWLEDGE_BASE](KNOWLEDGE_BASE.md) and Git history retain those tests; current status comes exclusively from the live ledgers.

## 4. Required exact acceptance and commit procedure

1. Check `git status --short --branch` and **take ownership of all dirty work**. Verify Japanese original hash and authored origin for the complete function. Do not accept a plausible decompiler signature or a borrowed class size as proof of original layout.
2. Reconstruct the *whole* original natural C++ function including all return paths, genuine x87/scalar behavior, automatic object lifetimes and after-RET jump DATA bounds. Use ignored `.analysis/` for complete source hypotheses and pinned MSVC VC7.1 (`scripts/compile-probe.sh`; right `/GX` or `/GX-` profile), with `scripts/repo-python scripts/compare-coff-function.py ... --json` for diagnostics.
3. `structural-exact` alone is insufficient. Independently check **all** real physical COFF `REL32`/`DIR32` offsets, types, original PE destinations and object addends. Only whole original CODE counts; original jump DATA and external CRT/SDK/callee CODE never count.
4. Add affected units to `config/match-units.toml`, then cold replay **only** those units: `scripts/repo-python scripts/replay-exact-units.py --unit YOUR-NEW-UNIT` (multiple named `--unit` only when needed). **NEVER** launch an all-unit cold replay.
5. Only on `N/N exact`, update `config/functions.csv`, `implemented.csv`, `known-symbols.csv`, `reccmp-functions.csv`, `matches.csv`, `exact-adoptions.json`, the SHA256 in `tests/exact_checkpoint.py`, progress SVG via `scripts/repo-python scripts/update-progress.py`, README and this handoff. Use `scripts/repo-python scripts/validate-tracking.py --require-target`, `scripts/repo-python scripts/update-progress.py --check` and **light** `scripts/repo-python scripts/ci.py` (no whole-build cold replay). `git diff --check`; promptly `git commit -m 'gpt-web: ...'`; check tree again.

See [RE_WORKFLOW.md](RE_WORKFLOW.md), [BUILD_MATCHING.md](BUILD_MATCHING.md), root `AGENTS.md` and the original-only verification scripts for complete commands. A real and valuable research milestone can be documented and committed **without** dishonest CODE credit (e.g. F520 22-boss cohort).

## 5. Storage, protected artifacts and recovery

The active original PE, `src/`, `config/`, `tests/`, `.analysis/vc71-wine/` (about 1.3 GiB: actual VC7.1 environment), private `ghidra-project/`, `.tools/`, **all** `build/probes/*.obj`, `build/matching/` and the **15 H184 SHA256-protected PDB/COFF source pairs** are protected. Never reset/remove them to save space. Protected entries: `.analysis/h184-handoff/active-object-retention.json`. Keep the current **large-boss decompilations, negative C++ source and meaningful comparison results** in `.analysis/`, which is intentionally Git-ignored and not available on a fresh clone without local state.

Older, redundant parent/adoption **JSON snapshots** are now **individually SHA256-verified, losslessly archived** as adjacent `.json.zst`, indexed in `.analysis/cache-archives/snapshot-compaction-index.json`; they are *restorable*, not irrecoverably lost. Their historical registration scripts expected old commits anyway. To recover a specific old input or verify all archived evidence:

```bash
scripts/repo-python scripts/archive-historical-analysis.py --restore .analysis/f180-background-counters/parent-and-seed.json
scripts/repo-python scripts/archive-historical-analysis.py --verify
```

Old unprotected `/Zi` probe `.pdb` caches are retained in **independently hash-verified** archives `.analysis/cache-archives/probe-pdb-unprotected-2026-10-28.tar.gz` and `probe-pdb-unprotected-2026-10-29.tar.gz`, each with a per-file receipt. To restore **one** old PDB (no all-unit builds):

```bash
tar -xzf .analysis/cache-archives/probe-pdb-unprotected-2026-10-29.tar.gz -C . build/probes/FILE.pdb
```

Check the per-file SHA256 in the adjacent receipt. See [STORAGE_HYGIENE.md](STORAGE_HYGIENE.md) for exact storage savings, protected paths and recovery. **Do not delete original or generated matching COFF `.obj`, negative source, frozen manifest, native research or local tools.**

## 6. History and next agent orientation

Start from **§2** above, always work on at least one *whole* large boss alongside smaller outstanding code. Repeated brute-force variable renames, inert locals or cropped CODE are not progress. F536 completed an independently reviewed 111-byte origin-pending game-specific coordinate transform (now 96 origin-pending); F535 completed the 92-byte progress leaf; the meaningful smaller remaining are the **171/248-byte real destructors**. The 22 massive controllers dominate unaccepted authored CODE. Detailed older attempts are in [KNOWLEDGE_BASE.md](KNOWLEDGE_BASE.md) and `git show 8da230b:docs/RE_HANDOFF.md` (the earlier verbose 338-line handoff), while the prior ancient handoff is explicitly archival `docs/RE_HANDOFF_HISTORY.md`. **Never treat a historical “pending” claim as live status.**
