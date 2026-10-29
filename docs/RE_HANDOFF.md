# TH075 — current agent handoff

**Maintained: 2026-10-29, after F564; this is the active handoff, not a research diary.** Start by checking the *live repository*; the figures below are a snapshot. The user requires serious work on **whole large boss functions and smaller leaves**, natural C++, independently checked original bytes, and immediate commits using `gpt-web: ...`. **All dirty changes belong to this one work session:** inspect, continue and finish them; never skip/reset/discard them. **Never run a full all-unit cold replay**—only the new or affected `--unit` entries.

## 1. Current authoritative state (not historical hypotheses)

| Item | Verified as of this handoff |
| --- | --- |
| Pinned original | user-supplied **Japanese** `resources/th075.exe` ver1.11; SHA256 `bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`; **never** localized `th075c.exe` |
| Whole exact C++ source | **943 functions / 943 exact units**, **862,726 original CODE bytes** |
| Reviewed original authored coverage | **43.71%** of **1,973,704** reviewed bytes; conservative **43.64%** with pending-origin bytes |
| Origin review | 4,351 provisional candidates; **1,004** origin-classified authored, **95** origin-pending, 3,420 origin-pending bytes |
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

**Trust, in this order:** the pinned original Japanese PE and its physical instructions, `config/function-origins.csv`, live `config/functions.csv`, whole physical COFF comparisons, *targeted* cold replay, `config/match-units.toml`, `config/exact-adoptions.json` and SHA-pinned source files. The provisional class/method names and decompiler locals are **not** authoritative original source declarations. Historical documents can be wrong; recheck against the PE. The complete 943-function accepted register is in `config/functions.csv`, not in this handoff.

## 2. Actual unresolved whole-function authored backlog

**The 22 giant fighter action/advance bosses are the principal coverage barrier.** All are separate, original authored function extents totaling **1,102,055 CODE bytes**; none has an accepted whole C++ source. Together they decode to **292,761 native x86 instructions, 16,861 calls and 84 physical indirect switch instructions**. Their **16,123 separate after-RET DATA bytes** (2,359 DWORD slots and 6,687 sparse index bytes) are *never CODE credit*. Follow [the full fighter cohort audit](FIGHTER_BOSS_FAMILY_DISPATCH.md), its frozen original manifest `config/fighter-boss-dispatch-fingerprints.json`, and read-only `scripts/repo-python scripts/verify-fighter-boss-family.py`. The 11 CharacterObject-family bosses each have one compressed switch; the 11 CharacterMove/Reimu-family bosses have 6–7. Four actual shared byte-index patterns occur, but **identical indices do not mean shared native destinations** and duplicate DWORD destinations are legitimate. For source work, inspect the verified whole [60,999-byte Reimu](REIMU_ACTION_BOSS_DISPATCH.md) and [82,796-byte CharacterMove](CHARACTER_MOVE_ACTION_DISPATCH.md) as starting points, not as “already restored” functions. **F537 has now independently resolved 7,152 original per-ID action entries across all 22 whole bosses (7,088 indexed, 64 singleton; 4,847 indexed inputs jump to each boss's native shared default).** See [the physical action/handler mapping](FIGHTER_ACTION_CASE_RESOLUTION.md) and the reproducible read-only `scripts/repo-python scripts/report-fighter-action-handlers.py --csv .analysis/f537-fighter-actions/whole-original-action-handlers.csv` (create its output directory first). This is a serious native whole-function dispatch milestone, but no giant has been C++ rebuilt or claimed exact. **F539 then established a real VC7.1 *natural single-switch* source generator for both 60,999-byte Reimu and 82,796-byte CharacterMove native dispatches: 66/66 x86 instruction grammars, exactly 325 bytes of dispatch geometry, all 522 sparse-index bytes, every 142/151 COFF DWORD slot and complete case-target equivalence partitions; see [the source-codegen experiment](FIGHTER_SWITCH_CODEGEN_RECONSTRUCTION.md) and `scripts/repo-python scripts/verify-fighter-natural-switch-probes.py`. This remains a *nonexact whole-boss* probe.** [F538 original action-zero audit](FIGHTER_ACTION_ZERO_NATIVE_LAYOUT.md) separately proves the same **50-instruction x87 case-zero sequence** inside all 11 multi-switch whole bosses (ten 180-byte cases, one 222-byte disp32 case), without claiming new exact CODE. Full original decompilation and meaningful probes live under `.analysis/f493-reimu-megaboss/`, `.analysis/f509-charactermove-megaboss/` and `.analysis/character-move-4ac040/`.

**F540 now verifies a genuine first giant-boss action-body C++ source hypothesis**:
[the 50-instruction action-zero native C++ proof](FIGHTER_ACTIONZERO_SOURCE_RECONSTRUCTION.md),
reproducible with `scripts/repo-python scripts/verify-fighter-actionzero-natural-source.py`.
The 180-byte Reimu/CharacterMove case and all nine authentic call/data
references emerge from normal VC7.1 C++, and its instruction/branch/x87
structure generalizes to all eleven 180/222-byte original case-zero blocks.
All remain **parts of unmatched whole fighters, not independently exact units**. **F541 expands the natural action-zero source experiment to all 11 independently compiled multi-switch bosses**: each reproduces 50/50 original instruction and *per-fighter real register-choice* grammar and nine genuine case references, plus all 1,607 original-style DWORD table COFF fields, 4,502 identical sparse index bytes and 10,930 after-RET DATA-shape bytes. See [the eleven-fighter C++ codegen study](FIGHTER_ACTIONZERO_FAMILY_CODEGEN.md) and `scripts/repo-python scripts/verify-fighter-actionzero-natural-source.py --boss 0x00486550`. No giant exact CODE credit. **F542 also reconstructs the full original 60-instruction action-1 native control/x87 case as natural C++ and compiles 11/11 fighter-specific switch probes.** All 11 have 60/60 native register/operand/branch grammars, 11/11 typed COFF references each, all 1,607 DWORD table fields and all 4,502 native sparse index bytes. Original case 1 is 212 bytes for ten fighters, 263 for EBP-0x88 due to 17 widened receiver loads. See [F542 action-one source/codegen evidence](FIGHTER_ACTIONONE_FAMILY_CODEGEN.md) and `scripts/repo-python scripts/verify-fighter-actionone-natural-source.py --boss Reimu`. Still zero full-boss exact CODE credit. **F545 now independently compiles all six opening actions (0..5) of each of the eleven multi-table fighter bosses**: 2,486/2,486 real original per-fighter register/branch/x87 instructions, 440 real case COFF roles, original table partitions and true individual action-4/5 float constants (notably 005D73C0 is +6.0/-4.5). Ten originals have 814 CODE bytes in these six cases; 00564BE0 has 1,006 due to 64 EBP-0x88 widened loads. See [the eleven-fighter six-case source proof](FIGHTER_OPENING_SIX_CASES_CODEGEN.md) and the new `scripts/repo-python scripts/verify-fighter-opening-actions-natural-source.py --boss 0x005D73C0`. No exact whole giant or split-case CODE credit. **F547 now adds the entire original 42-instruction action-9 C++ case across eleven newly compiled fighter-specific probes** (66 genuine typed case references, complete per-fighter sparse/index/table COFF partitions). `00543210` uniquely pushes `1` rather than `0` to `0040FB40`; six generated case-9 instances match exact original GPR allocation, five match native field/x87/control grammar but have different free-register assignments. Ten native cases have 144 CODE bytes; original `00564BE0` has 183 due to 13 wide receiver loads. See [F547 native C++ action-nine evidence](FIGHTER_ACTIONNINE_FAMILY_CODEGEN.md) and `scripts/repo-python scripts/verify-fighter-actionnine-natural-source.py --boss 0x00543210`. **No giant whole-function CODE credit.** **F548 now independently compiles a new complete 104-instruction, 362-byte native action-six C++ case in three whole giant original contexts** (`0045DD70`, `0058AF60`, `005D73C0`). It reproduces the 5-call native policy including the genuine virtual vtbl[0] method and 18 authentic typed COFF fields, 422 jump-table DWORD COFF refs and 1,323 original sparse bytes; each original character has distinct stage/float initialization. See [F548 action-six source audit](FIGHTER_ACTION_SIX_FAMILY_CODEGEN.md) and `scripts/repo-python scripts/verify-fighter-action-six-natural-source.py --boss 0x0058AF60`. The other eight case-six functions are different 96–125-instruction native families and remain for complete source investigation. **No giant exact CODE credit.** **F549 adds eleven separately compiled complete action-10 C++ cases**: 9 regular 31-instruction bodies and 2 genuine 20-instruction variants (the real EBP-0x88 fighter expands to 87 bytes). All 53 genuine case COFF call positions, 1,607 jump-table fields and per-character `0/2`, `3/2`, `0/1` state arguments are checked. Six actual GPR allocations match, five differ. See [F549 natural action-ten study](FIGHTER_ACTIONTEN_NATIVE_CPP.md) and `scripts/repo-python scripts/verify-fighter-actionten-natural-source.py --boss Reimu`. No full boss exact credit.

**F551 additionally reconstructs the entire 104-instruction action 7** within
three original giant fighters, while retaining independent action-6 source
verification. All **624/624** real two-case GPR/x87/control instructions and
**36/36** genuine call/global COFF references are verified under fresh
selected-only VC7.1 compilation. The original action-7 guard changes to 5,
callback to 0xCD, and per-role float position to 4.0f or 6.0f; the native
virtual calls remain exact in source shape. See [F551 action-six/seven family
source study](FIGHTER_ACTIONSEVEN_NATIVE_CPP.md) and
`scripts/repo-python scripts/verify-fighter-action-seven-natural-source.py
--boss 0x005D73C0`. **No whole giant or split-case CODE credit.**

**F553 additionally recovers actual original action 8** in three native
fighters through newly compiled natural C++. Reimu and `005D73C0` retain
104/104 native instructions; `0058AF60` has a *real* 102-instruction
variant omitting `FLAG = 0`, with 352 CODE bytes rather than 362. Each
character's C++ switch now independently validates complete actions
6, 7, 8: **934/934 per-fighter native instruction roles, 54 authentic
COFF references** plus full source-native switch-table layout. See
[F553 action-eight source proof](FIGHTER_ACTIONEIGHT_NATIVE_CPP.md) and
`scripts/repo-python scripts/verify-fighter-action-eight-natural-source.py
--boss 0x0058AF60`. No split/whole giant exact CODE credit.

**F556 independently reconstructs the harder 117-instruction/403-byte
action 6 and 7 original variants** inside `00486550` and CharacterMove
`004AC040` (82,796 original CODE bytes). Four original cases each compile
with full **117/117 original register/x87/branch instructions and 8/8 true
COFF call/global fields**, including a formerly absent guarded native
`0040FB40(5)` invocation and original float threshold `00657D14`.
The actual stage and float initializers differ between the fighters, and
CharacterMove's action 7 clears FLAG **before** float stores, unlike the
other original. Full description:
[F556 original 117-insn case source](FIGHTER_EXTRA_STAGE_SOURCE_F556.md);
targeted compiler command:
`scripts/repo-python scripts/verify-fighter-extra-stage-action-source.py --boss CharacterMove`.
**All 1,612 case bytes remain inside two whole unmatched giant functions**;
no split/whole CODE exactness credit.

**F557 adds two more entire 115-instruction original action-six/seven
source families** (`00543210`, `00564BE0`) with truly **no FLAG clear**.
Four new complete native C++ cases verify **460/460 original per-fighter
GPR/x87/branch instructions and 32/32 authentic COFF fields**, plus all
287 DWORD table slots and 669 original sparse bytes. The unusual 508-byte
source parent is explained by **37 wide native EBP-0x88 reloads + one
extra-long JL** per case, not padded C++. See
[F557 115-instruction source/codegen proof](FIGHTER_STAGE_NO_FLAG_F557.md)
and `scripts/repo-python scripts/verify-fighter-stage-no-flag-source.py
--boss 0x00564BE0`. These 1,802 native interior bytes are **not** full-
function exact CODE credit.

**F558 additionally reconstructs entire action 8** in both the 50,735-byte
`00486550` and 82,796-byte CharacterMove `004AC040` giants, while preserving
the earlier real action 6/7 C++ cases. Their complete original case sizes
are 403/403/362 bytes, with **676/676 actual native instruction roles**
and **44 genuine COFF fields** in the two newly compiled diagnostic source
objects. Critically `00486550` action 8 clears `FLAG` *between* position
and velocity initialization, whereas CharacterMove clears `FLAG` first.
See [F558 original action 8 study](FIGHTER_EXTRA_STAGE_EIGHT_F558.md) and
`scripts/repo-python scripts/verify-fighter-extra-stage-action-eight.py
--boss CharacterMove`. No full giant or independent case CODE credit.

**F559 additionally rechecks and reconstructs the complete native action
8** of the unusual wide-frame 61,872-byte fighter giant `00564BE0`,
while independently re-verifying its complete actions 6 and 7. Its new
102-instruction action-8 C++ source produces 352 bytes vs **458 native**;
exactly **34 long EBP-0x88 receiver reloads plus one long JL** account for
the native extra 106 bytes, with **no fake source padding**. The three
real action cases together have **332/332 original GPR/x87/branch roles,
22 genuine COFF call/float fields**, all original 131 DWORD jump slots
and 350 original sparse bytes. See
[F559 wide-frame action-eight native source proof](FIGHTER_WIDE_ACTION_EIGHT_F559.md)
and `scripts/repo-python scripts/verify-fighter-wide-action-eight-source.py`.
These 1,474 original inner bytes remain part of **unmatched whole giant
CODE** with zero independent/split-case exactness credit.

**F560 now reconstructs the full native action-8 source of giant
`00543210` (58,294 complete original CODE bytes)** in a newly compiled
VC7.1 C++ probe, retaining its action 6 and 7. Its real action-8
**117 instructions / 403 CODE bytes** place auxiliary stage-three
`0040FB40(4)` **before** contact/x87 comparison, then write native
-7.0f position, clear FLAG, and initialize 18.0f/0.95f motion on
transition. Two independent original-backed new source builds confirm
**347/347 full case x86 instruction roles, 24 true COFF fields, 156
physical switch DWORD fields and 319 byte-identical original sparse
bytes**. See [F560 full original action-eight case C++ study](FIGHTER_PRECONTACT_ACTION_EIGHT_F560.md)
and affected-only verifier
`scripts/repo-python scripts/verify-fighter-precontact-stage-action-eight.py`.
Its 1,189 inner original CODE bytes remain within **unmatched whole
giant source**; zero split/whole exact CODE credit.

**F562 separately reconstructs the full original action 6/7/8 C++
in the 43,601-byte fighter giant `004D7E70`**. Its three physical native
cases contain **102/115/102 x86 instructions and 352/393/352 CODE bytes**
respectively; only action 7 has the extra x87 stage condition and
`0040FB40(5)` callback. Newly compiled ordinary VC7.1 C++ matches all
**319 original GPR/x87/control instruction roles, 20 real COFF
call/constant fields**, the real action-6 `[eax]` versus action-7/8
`[edx]` virtual dispatch and all **140 native-style switch DWORD fields
and 409 exact original sparse indexes**. Actual role speed is 0.65f;
no source stage branch is fabricated in action 6/8. Reproducer:
`scripts/repo-python scripts/verify-fighter-split-stage-4d7e70.py`;
[F562 native original three-case source study](FIGHTER_SPLIT_STAGE_F562.md).
The **1,097 inner CODE bytes remain inside the nonexact giant**, not
independent exact function/CODE credit.

**F563 now reconstructs two previously unmodeled original
`FLAG > 0` secondary-motion giant-boss policies**, independently
within `004F7130` (44,211 original CODE) and `005AEEC0`
(71,616 original CODE). Six separate original action 6/7/8 cases are
fully modeled in normal C++, for **698/698 native real GPR/x87/branch
instruction roles**, **44 genuine COFF call/global fields**, real
fighter-specific two-stage motion constants, all **305** physical jump
DWORD fields and **822** exact sparse map bytes. Critically `004F7130`
performs a secondary override in both action 6/7 and clears `FLAG` only
at the end of the action-7 override, while `005AEEC0` overrides only
its action 6 and never clears FLAG in its three cases. See
[F563 native conditional-override source proof](FIGHTER_FLAG_OVERRIDE_SOURCE_F563.md)
and targeted reproducer
`scripts/repo-python scripts/verify-fighter-conditional-override-actions.py
--boss 0x004F7130`. The 2,440 original internal CODE bytes remain
inside **two unaccepted whole giant bosses**; zero split/whole exact
CODE credit.

**F564 integrates all eleven actual native actions 0..10 into one
newly compiled natural C++ Advance() function per whole original fighter**
for 004F7130 (44,211 CODE) and 005AEEC0 (71,616 CODE). Two fresh VC7.1
source builds verify **all 22 complete original action cases, 1,296 real
GPR/x87/branch/length instruction roles and 146 genuine typed COFF fields**
plus the full 305 physical switch DWORD fields, default/repeated
destinations, 822 exact sparse bytes and 2,042 after-RET DATA-shape
bytes. With real action6-8 source in the same function, action9/10
register allocation also reaches the native grammar. See
[F564 eleven-case integrated source study](FIGHTER_INTEGRATED_ELEVEN_CASES_F564.md)
and scripts/repo-python scripts/verify-fighter-integrated-opening-switch.py
--boss 0x004F7130. All 4,558 original inner CODE bytes remain inside
**two nonexact giant functions**, with later action cases/owner frame
not reconstructed and no whole/split CODE exact credit.

**Three other authored functions remain nonexact (all require full CODE):**

| Original function / PE address | Size | Best meaningful current evidence / precise blocker |
| --- | ---: | --- |
| `GameApplication::RunAt00602A60` / `00602A60` | **2,987** | **654** original instructions, **123** calls, actual **0x278** frame and **15** scene switch cases. F528 complete native-like C++ `outer0-firsttmp1-while1.cpp` has **2,981 bytes /654 instructions /123 calls /0x278**, all **654/654 ordered x86 mnemonics** but only **224/654 identical complete operands+lengths**, so **not exact**. Most important true EBP locals: scene -0x184 vs candidate -0xC, pathname -0x180 vs -0x158, AppMode -0x3D vs -1, graphics -0x189 vs -0xD. Fix real C++ owner layout and lifetimes, not instruction counts or synthetic padding. See [full native WinMain audit](WINMAIN_ORIGINAL_CONTROL_FLOW.md), `scripts/repo-python scripts/verify-winmain-scene-dispatch.py`, `.analysis/f525-*` through `.analysis/f530-*`, `.analysis/f528-winmain-native-initial-scene/detailed-insn-alignment.tsv`. Original 60-byte after-RET scene table is DATA. |
| `SceneObject::ReleaseAt0043B0B0` / `0043B0B0` | **248** | Genuine virtual destructor with original EH and three owned heap frees. Full natural `/GX` C++ reaches **191/200** original nonrelocation bytes, but physical native texture/delete temporaries at EBP -0x14/-0x10 and actual heap pointers -0x18/-0x1C/-0x20 disagree with compiler allocation order. `.analysis/f215-battle-release/struct0.cpp`, `.analysis/f449-scene-texture-heap-release/`, `.analysis/f533-scene-native-separate-pointers/`. No 248-byte credit. |
| `ArchiveCatalog::Release` / `0041CE50` | **171** | Actually the **nonvirtual local RAII destructor** of the archive catalog, paired with `0041CE10`, as established from WinMain original call/receiver EBP -0x35. Genuine C++ destructor yields complete **171 bytes, 108/115** nonrelocation bytes (14 COFF fields), but physical resource/delete/filename locals at -0xC/-8/-0x10 differ from source -0x10/-0xC/-8. `.analysis/f343-archive-release/`, `.analysis/f531-archive-real-raii-destructor/` and `.analysis/f517-archive-true-name-record/`. Virtual destructor form is wrong (182 bytes). No 171-byte credit. |

**No other `owner=authored,status=unclassified` function is currently in the live ledger.** The **95 pending origins** are a separate provenance classification problem; do not silently count them as authored. The full original authored-byte goal remains distant, even though many smaller game bosses are already exact.

## 3. Important *already solved* functions: do not redo old “pending” experiments

| Previously disputed | Current correct result | Canonical source / batch |
| --- | --- | --- |
| Font Shift-JIS lead-byte range helper `0041CA30` | **77 whole CODE; 28 native instructions, 0 COFF relocations, 1/1 targeted cold exact**, four exact byte-boundary comparisons (0x81, 0xA0, 0xE0, 0xFF); sole native caller is already-exact authored `0041C9D0`. R183 originally kept authorship unknown; F555 re-reviewed probable game-local authored policy. No private original class identity, library/vendor provenance certainty or SDK table is invented | `src/FontLeadByteF555.cpp` / F555 |
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

Start from **§2** above, always work on at least one *whole* large boss alongside smaller outstanding code. Repeated brute-force variable renames, inert locals or cropped CODE are not progress. F555 completed a newly re-reviewed, whole 77-byte Shift-JIS byte-range helper (now 95 origins pending), preserving the historical R183 unknown-owner snapshot and its independent ordinary member alternative. F536 previously completed the 111-byte coordinate transform; F535 completed the 92-byte progress leaf; the meaningful smaller remaining are the **171/248-byte real destructors**. The 22 massive controllers dominate unaccepted authored CODE. Detailed older attempts are in [KNOWLEDGE_BASE.md](KNOWLEDGE_BASE.md) and `git show 8da230b:docs/RE_HANDOFF.md` (the earlier verbose 338-line handoff), while the prior ancient handoff is explicitly archival `docs/RE_HANDOFF_HISTORY.md`. **Never treat a historical “pending” claim as live status.**

F538 adds [eleven independent native action-zero case bounds, 50-instruction signatures and 14 stack-reload observations](FIGHTER_ACTION_ZERO_NATIVE_LAYOUT.md). All 22 full fighter bosses remain nonexact pending complete natural C++ source, while F537 retains the original 7,152-entry action map.
