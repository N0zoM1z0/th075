# TH075 — ACTIVE reconstruction agent handoff

**Verified snapshot: 2026-10-30, current F755 exact ledger; F754 maintenance.**
This is the **short working queue**, not the chronological research log.
Original Japanese PE and the live configuration **always outrank historical
prose, old case-level exact labels, class names or inferred layouts**.
Old long F653–F753 handoff: [frozen, link-corrected archive](history/RE_HANDOFF_F653_THROUGH_F753_2026-10-30.md).
Older [F598–F652](history/RE_HANDOFF_F598_THROUGH_F652_2026-10-29.md),
[F540–F596](history/RE_HANDOFF_F540_THROUGH_F596.md), and the
[historical knowledge base](KNOWLEDGE_BASE.md) preserve experiments.

## 1. Live original target and formal exactness

| Evidence / classification | Current live manifest value |
| --- | --- |
| User-supplied Japanese TH075 `resources/th075.exe` v1.11 | SHA-256 `bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98` |
| Provisional original native candidate rows | **4,351** |
| Independently reviewed `origin=authored` candidates | **1,004** |
| Canonical accepted complete exact authored game functions | **969 functions / 969 exact units** |
| Accepted complete original CODE | **864,672 original CODE bytes** |
| Reviewed denominator | **1,973,704** native authored CODE B |
| Exact reviewed coverage | **43.81%** |
| Conservative coverage (includes pending origin bytes) | **43.73%** |
| Authored candidates still NOT exact | **35 authored functions remain nonexact** |
| 35 nonexact breakdown | **22 large original state advances**, **13 other original small/medium whole functions** |
| 22 large original native CODE not accepted | **1,102,055 CODE bytes** (separate after-RET DATA not credited) |
| 13 small/medium native CODE not accepted | **6,977 CODE bytes** |
| Independently origin-unknown candidates | **95 functions / 3,420 CODE bytes**, uncredited |

**Important correction:** the older **25 unfinished** figure only counted
rows flagged both `owner=authored` and `status=unclassified` in
`config/functions.csv` (22 large + WinMain/Scene/Archive). There were
**11 more** candidates whose `function-origins.csv` origin was already
reviewed as authored, but whose provisional `functions.csv` owner is still
blank at that historical checkpoint because they lacked accepted source.
F755 accepted one of them (`00407270`); the **10 remaining** candidates
still lack accepted source and must not be discarded or prematurely labeled
in `functions.csv.owner`.
Use **`config/function-origins.csv` for provenance** and
`config/matches.csv` / `config/match-units.toml` for whole CODE credit.
The **98% whole-authored-byte goal is NOT met**.

### Preflight (read-only, no mass rebuild)

```bash
git status --short --branch
git log -5 --oneline
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/validate-tracking.py --require-target
scripts/repo-python scripts/report-reconstruction-status.py --summary
scripts/repo-python scripts/audit-active-handoff.py
scripts/repo-python scripts/ghidra.py check
```

All dirty tracked/untracked work belongs to this one reconstruction worker;
inspect and continue it, do not skip/reset it. Run the hash-pinned original
`th075.exe`, **not** `th075c.exe`. Use `scripts/repo-python` and the pinned
VC7.1 compiler; compile probes serially under headless Wine. **Never run an
all-969-unit cold replay.** Only newly accepted or affected whole functions
need canonical `scripts/repo-python scripts/replay-exact-units.py --unit NAME`.
Source grammar/byte geometry of an *internal switch case* does **not**
earn credit for the still-NONEXACT enclosing whole callable function.

## 2. Large/giant whole functions — invest real effort here

**`0x00543210` / 58,294 original CODE B, plus 943 after-RET switch DATA B.**
The latest whole-parent source is reproducible from tracked C++ using
`[F752 native borrowed-position checker](FIGHTER_BORROWED_POSITION_F752.md)`:

```bash
scripts/repo-python scripts/verify-fighter-borrowed-position-f752.py
```

Current true native source positives in ONE complete VC7.1 parent:
original saved `this` **`EBP−0x44`** matches naturally from real
`059/060/061` game and ten-shot loop lifetimes. The formerly wrong
original `05D`/`05E` **337 B/101 x86/8 physical PE fields each**
now emit complete native `FLD ACTOR; FCOMP OPPONENT` thanks to
**both borrowed actor/opponent typed `+0x44` float members**. They have
zero mnemonic/width/normalized GPR differences and 301/305 original
nonfield bytes each; only **two shared-tail JMP displacement fields**
per case differ because the whole giant layout remains nonexact.
All **16/16 original PE/COFF relocations**, **27 other selected full
native action contexts**, and the whole **943-B DATA /156 real DIR32
jump labels /319 other native bytes** were rechecked in that parent.
See [F747–F749 original frame proof](FIGHTER_EARLY_RESOURCE_STACK_F747_F749.md)
and [F752 complete corrective comparison](FIGHTER_BORROWED_POSITION_F752.md).

**Next meaningful giant tasks:** resolve the real native `059` **19**
normalized nonfield GPR discrepancies and `060/061` **98/101**;
recheck *in the next newly compiled entire parent* (do not inherit
F737/F744 counts) and restore the remaining genuine deep x87 stack
lifetimes/earlier source actions. Native `190` remains **276 B vs
266 emitted** due to one branch and two real integer-to-x87
scratch widths even though selected parent GPR roles are correct.
Never invent unused EBP padding or isolate a case for byte credit.

**`0x004EBDA0` /33,293 original CODE B, plus 438 after-RET DATA B.**
Ordinary C++ currently emits original **33,293 B/8,789 x86
mnemonic and width positions**, with **682 native typed COFF fields**
and **30,866/31,003 matching native nonfield bytes**. **137 real
register/phase bytes** remain different across actual actions
`38D/38E/3E3`. The F705 real parent/source-lvalue controls and
older F690/F692 controls were NEGATIVE; do not promote this entire
function or keep repeating equivalent `*(&field)` tests.
Recheck only this native owner if you change it:

```bash
scripts/repo-python scripts/verify-characterobject-native-collision-order-f596.py
```

The other **20 large original state-advance functions** also remain
unmatched, including the 82,796-B `004AC040`, 81,539-B `0050A580`
and 60,999-B `0045DD70`. Their complete original extents and origin
classification are in `config/functions.csv` and
`config/function-origins.csv`. Preserve real native per-case source
research without calling it accepted whole CODE. [Giant dispatch
map](../config/fighter-boss-dispatch-fingerprints.json) is a
physical-data lead, not provenance proof.

## 3. All 13 additional nonexact original small/medium functions

These are **authored by `function-origins.csv`** but not canonically
matched (most have blank provisional `functions.csv` owner). This is
the complete **6,977-B** non-giant backlog, NOT just the three
frequently researched ownership functions:

| Native original entire function | CODE | Next evidence/source lead |
| --- | ---: | --- |
| `0x0040CA20` SpriteDrawing projected quad | 92 B | Real 132-B quad copy correct 92B/34 x86 but VC7.1 stack frame `−0x8C` vs native `−0x88`; `.analysis/f751-sprite-draw-probe/` |
| `0x0040C9A0` SpriteDrawing ordinary quad | 115 B | Real quad copy and true Graphics draw callee, original whole function still missing |
| `0x0040D790` SpriteDrawing opaque | 171 B | Full sprite/color forwarding and selection |
| `0x0040D6B0` SpriteDrawing mirrored opaque | 212 B | Real member transform/order and original call ABI |
| `0x0040D2E0` SpriteDrawing scaled XY | 970 B | Native original whole geometry and meaningful transform source |
| `0x0040CEF0` SpriteDrawing variant | 994 B | Complete borrowed quad/rect transformations |
| `0x0040B110` TextureManager texture slots | 184 B | R017 original resource/vector ownership |
| `0x0040B000` TextureManager shared textures | 261 B | R017 original allocation/ownership policy |
| `0x00407A50` AudioStream QueueFile | 289 B | Original `/GX` record/Win32 file lifetime |
| `0x00407B80` AudioStream QueueArchiveEntry | 283 B | Original `/GX` archive record queue source |
| `0x0041CE50` ArchiveCatalog destructor | 171 B | Best native 108/115 nonfield bytes, still seven genuine owner/CFG differences; [F697/F698 negatives](ARCHIVE_AGGREGATE_AND_REFERENCE_NEGATIVES_F697_F698.md) |
| `0x0043B0B0` Scene destructor | 248 B | Best 191/200 native nonfield bytes; used texture owner/stack layout unresolved; [F700](SCENE_TEXTURE_OWNER_LIFETIMES_F700.md) |
| `0x00602A60` WinMain | 2,987 B | Original saved local scene/path frame differs; [F702–F704](WINMAIN_USED_OBJECT_CONTEXT_NEGATIVES_F702_F704.md) |

The paired R015 audio-client destructor `00407270` is now **292-B/82-x86/24-reloc cold exact**
([F755](AUDIO_STREAM_CLIENT_RELEASE_F755.md)); it is no longer pending.
Latest accepted R015 audio-client constructor `004071C0` is already
**161 B cold-exact** ([F753](AUDIO_STREAM_CLIENT_ACQUIRE_F753.md));
do not relist it as pending. Do not recredit its native STL/CRT/OS
callee code. Similarly the previous F750 CharacterAux 101-B
nested collection wrapper is already accepted exact.

## 4. Attribution, validation, research and storage

- **Original authored ≠ compiler/library ≠ unknown**. The 95 unknown
  candidates have 3,420 uncredited CODE bytes; e.g. fully byte-exact
  but origin-unknown `0061F125` remains UNACCEPTED. A plausible name,
  `Ghidra` function boundary or exact source alone cannot change this.
- **Accepted whole-function CODE** requires the entire original PE
  boundary, natural C++ under the actual VC7.1 flags, every zero-addend
  COFF relocation, independent authored origin and targeted cold replay.
  Separate after-RET jump DATA and MSVC EH carrier code/data are never
  double-counted as game CODE. Use `AGENTS.md` and [workflow](RE_WORKFLOW.md).
- **Research files**: keep original native/COFF evidence, negative C++
  grammar controls, `build/matching/`, H184 protected probes, full
  `.analysis/vc71-wine/`, Ghidra and all original files. The history
  archives are **local/ignored**, not Git assets.
- **Space-efficient recovery**: archived frozen f133–f166 giant `.asm/.cod/.log`
  traces and older JSON/PDB/log batches are documented in
  [storage hygiene](STORAGE_HYGIENE.md). Rehydrate an actual old
  original trace with `scripts/repo-python
  scripts/archive-frozen-giant-traces.py --restore ORIGINAL_PATH`;
  independently verify its SHA256 before relying on it. Do not
  delete archive files because they are absent from Git.
- **Required end-of-turn**: verify target/affected native source,
  `validate-tracking.py --require-target`,
  `audit-active-handoff.py`, `update-progress.py --check` when the
  count changes, `git diff --check`, inspect dirty changes and
  commit substantive results using **`gpt-web: ...`**.
  Local Git commits are not remote Oracle acceptance; **do not push**.
