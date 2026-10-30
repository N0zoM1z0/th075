# TH075 — ACTIVE reconstruction agent handoff

**Verified snapshot: 2026-10-30, current F765 exact ledger; F754 maintenance.**
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
| Canonical accepted complete exact authored game functions | **972 functions / 972 exact units** |
| Accepted complete original CODE | **865,415 original CODE bytes** |
| Reviewed denominator | **1,973,704** native authored CODE B |
| Exact reviewed coverage | **43.85%** |
| Conservative coverage (includes pending origin bytes) | **43.77%** |
| Authored candidates still NOT exact | **32 authored functions remain nonexact** |
| 32 nonexact breakdown | **22 large original state advances**, **10 other original small/medium whole functions** |
| 22 large original native CODE not accepted | **1,102,055 CODE bytes** (separate after-RET DATA not credited) |
| 10 small/medium native CODE not accepted | **6,234 CODE bytes** |
| Independently origin-unknown candidates | **95 functions / 3,420 CODE bytes**, uncredited |

**Important correction:** the older **25 unfinished** figure only counted
rows flagged both `owner=authored` and `status=unclassified` in
`config/functions.csv` (22 large + WinMain/Scene/Archive). There were
**11 more** candidates whose `function-origins.csv` origin was already
reviewed as authored, but whose provisional `functions.csv` owner is still
blank at that historical checkpoint because they lacked accepted source.
F755 (`00407270`), F758 (`00407A50`), F760 (`00407B80`) and F765 (`0040D790`) accepted four; the **7 remaining** candidates
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
all-972-unit cold replay.** Only newly accepted or affected whole functions
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

**F759 historical full-parent correction (before F760):** the previously placeholder `C8–CB`
original actions now have **1,804 B/532 x86/54 genuinely typed COFF
fields** of original source-backed case geometry. All **1,540/1,540**
nonfield original bytes outside 54 relocation and 12 external parent-tail
JMP fields match; the 12 real tail displacements are NOT exact. Four
meaningful native `EBP−0x74/−0x78/−0x7C/−0x80` FILD temporaries
recover the missing 16B stack lifetime across downstream `18A/18B/190`
and later contexts. Native `190` is now **276 B/75 x86 versus 276
compiled B/75 x86**, but still has authentic GPR/CFG differences and
shared-tail nonexact bytes. The whole giant still emits **56,954**
versus **58,294 native CODE B**; `CC/CD/CE` remain placeholders
(435/435/394 native B). Reproduce only the affected entire parent:

```bash
scripts/repo-python scripts/verify-fighter-four-directional-c8-f759.py
```

[Full F759 native physical proof](FIGHTER_C8_CB_WHOLE_PARENT_F759.md).
No new independently exact whole original CODE was credited.

**F759 further historical whole-parent evidence:** original four C8–CB actions now
recovered as 1,804 real internal CODE B /532 original x86/54 authentic
PE fields, with 1,540 byte-identical other nonfield bytes and 12
real shared-parent JMP displacement differences. The extra genuine
source *also* restores nine downstream MOV/FILD EBP scratch pairs
(18A/18B, 190–195, 2D0, 302), including original 190 `EBP−0x90`.
The enclosing 58,294-B original remains NONEXACT: 56,954 emitted
CODE B, 1,340-B deficit; 943-B afterRET DATA remains separately
verified. [F759 physical full-parent evidence](FIGHTER_FOUR_DIRECTIONAL_NATIVE_F759.md),
`scripts/repo-python scripts/verify-fighter-four-directional-c8-f759.py`.

**F760 historical whole-parent result (before F762; supersedes F759 GPR negatives):**
three more real CC/CD/CE source actions reproduce 1,264 original CODE B,
371 original x86, 31 genuine PE/COFF fields, and 1,116/1,116
nonfield/non-tail bytes. Correcting the real unconditional virtual call
after the short stage-count conditional fixed three actual `JL` bytes.
Eight downstream source-backed actions 18A/18B/190/191/192/194/195/2D0
now have **zero mismatches outside actual COFF and parent-tail JMP**
including original 190 `276/276 B` and original GPR role. The full
58,294-B native boss emits 58,173 B, a remaining 121-B CODE deficit.
The original 943-B afterRET DATA is still independently verified;
whole game callable function remains NONEXACT.
[Original complete F760 evidence](FIGHTER_COMPLEX_STAGE_CC_CE_F760.md);
`scripts/repo-python scripts/verify-fighter-complex-stage-cc-ce-f760.py`.

**F762 historical full-parent correction (before F763):**
`05F` now has genuine native-shaped source **144 B/44 x86/3 fields**,
but its GPR phase remains NONEXACT. More importantly, original complete
`1F6/1F7/1F8` now emit **3,833 original CODE B /1,118 x86 /115
actual typed PE/COFF fields** with zero nonfield byte mismatches except
true still-nonmatching parent-shared JMP displacements. The original
`ContactAt454EE0` gate applies only to the first two side-edge
predicates, not the independent actor/opponent position comparisons.
Borrowed typed actor/opponent `+0x44` float lvalues restore real x87
FCOMP and the 1F8 native MOV/FLD order. The WHOLE 58,294-B boss emits
**58,277 B**, a remaining **17-B length deficit** plus genuine
register/other-code bytes; **not exact**. Original 943-B afterRET DATA
remains separately verified. [F762 entire native evidence](FIGHTER_TYPED_RETURN_CROSS_CASE_F762.md);
`scripts/repo-python scripts/verify-fighter-typed-returns-f762.py`.

**F763 historical full-parent result (before F764):** original 2DB now reproduces
**1,024 native CODE B, 290 x86 and 34 real PE/COFF fields**, with
zero other nonfield bytes outside the genuine shared-parent tail JMPs.
Original `actorX < sideEdge`, `abs(actorX−opponentX) < threshold`
and real actor/opponent float `+0x44` lvalues restore the correct
x87 TEST AH status flags and MOV/FLD register order. The formerly
extra 8 B/two x86 in 2DB have been removed naturally; the full
58,294-B boss candidate now emits **58,269 B**, 25-B deficit and
still NONEXACT. Original 2FA still emits 979 B vs native 971 B;
that is the next targeted x87/branch/GPR task. Original 943-B
afterRET switch DATA separately verified, no accepted CODE credit.
[Complete F763 native evidence](FIGHTER_APPROACH_NATIVE_F763.md);
`scripts/repo-python scripts/verify-fighter-approach-native-f763.py`.

**F764 latest original 2FA state research:** all six real floating
predicates/borrowed actor-opponent `+0x44` X member reads corrected
inside the same complete 58KB C++ parent. Actual native action 2FA
now emits **971 B/279 x86/31 genuine typed PE/COFF fields** and
has **zero original opcode or instruction-width differences**.
However **156 real GPR/operand nonfield bytes remain WRONG**; this
is NOT whole-case or whole-function exact. Recovered 2DB and
1F6/1F7/1F8 native source bodies stay strict (except parent-tail
JMPs), and original afterRET jump DATA remains 943 B/156 real
DIR32/319 sparse bytes. Whole original `00543210` now emits
**58,261/58,294 CODE B** (33-B deficit plus genuine wrong bytes);
zero new accepted CODE. [F764 original whole-case proof](FIGHTER_APPROACH_VOLLEY_NATIVE_F764.md);
`scripts/repo-python scripts/verify-fighter-approach-volley-native-f764.py`.

**Next meaningful giant tasks:** resolve the real native `059` **19**
normalized nonfield GPR discrepancies and `060/061` **98/101**;
recheck *in the next newly compiled entire parent* (do not inherit
F737/F744 counts) and restore the remaining genuine deep x87 stack
lifetimes/earlier source actions. F759 had **40/40/34** real wrong register ordinals in 190/191/192,
but **F760 repairs all three to zero other nonfield differences** in the
new whole parent. This is a compiler-context/lifetime effect; full
boss CODE and parent-tail JMP layout remain nonexact.
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

## 3. All 10 additional nonexact original small/medium functions

These are **authored by `function-origins.csv`** but not canonically
matched (most have blank provisional `functions.csv` owner). This is
the complete **6,234-B** non-giant backlog, NOT just the three
frequently researched ownership functions:

| Native original entire function | CODE | Next evidence/source lead |
| --- | ---: | --- |
| `0x0040CA20` SpriteDrawing projected quad | 92 B | Real 132-B quad copy correct 92B/34 x86 but VC7.1 stack frame `−0x8C` vs native `−0x88`; `.analysis/f751-sprite-draw-probe/` |
| `0x0040C9A0` SpriteDrawing ordinary quad | 115 B | Real quad copy and true Graphics draw callee, original whole function still missing |
| `0x0040D6B0` SpriteDrawing mirrored opaque | 212 B | Real member transform/order and original call ABI |
| `0x0040D2E0` SpriteDrawing scaled XY | 970 B | Native original whole geometry and meaningful transform source |
| `0x0040CEF0` SpriteDrawing variant | 994 B | Complete borrowed quad/rect transformations |
| `0x0040B110` TextureManager texture slots | 184 B | R017 original resource/vector ownership |
| `0x0040B000` TextureManager shared textures | 261 B | R017 original allocation/ownership policy |
| `0x0041CE50` ArchiveCatalog destructor | 171 B | Best native 108/115 nonfield bytes, still seven genuine owner/CFG differences; [F697/F698 negatives](ARCHIVE_AGGREGATE_AND_REFERENCE_NEGATIVES_F697_F698.md) |
| `0x0043B0B0` Scene destructor | 248 B | Best 191/200 native nonfield bytes; used texture owner/stack layout unresolved; [F700](SCENE_TEXTURE_OWNER_LIFETIMES_F700.md) |
| `0x00602A60` WinMain | 2,987 B | Original saved local scene/path frame differs; [F702–F704](WINMAIN_USED_OBJECT_CONTEXT_NEGATIVES_F702_F704.md) |

The R011 SpriteDrawing opaque draw `0040D790` is now **171-B/52-x86/6-field whole cold exact**,
with 147/147 authentic nonfield bytes and real native RECT lifetimes
([F765](SPRITE_OPAQUE_NATIVE_F765.md)); no longer in the pending queue.
The R016 audio archive-entry queue `00407B80` is now **283-B/76-x86/27-COFF cold exact**
([F760](AUDIO_QUEUE_ARCHIVE_ENTRY_F760.md)), with original valid-handle
conditional 64-byte record lifetime. It is no longer on the pending queue.
The R016 audio file-queue `00407A50` is now **289-B/77-x86/26-reloc cold exact**
([F758](AUDIO_QUEUE_FILE_F758.md)); its recovered 64-B native record
corrects the previously guessed 68-B lifetime and is no longer pending.
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
