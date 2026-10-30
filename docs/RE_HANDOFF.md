# TH075 — ACTIVE reconstruction agent handoff

**Verified snapshot: 2026-10-30, current F780 exact ledger; F790 giant source controls.**
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
| Canonical accepted complete exact authored game functions | **979 functions / 979 exact units** |
| Accepted complete original CODE | **868,243 original CODE bytes** |
| Reviewed denominator | **1,973,704** native authored CODE B |
| Exact reviewed coverage | **43.99%** |
| Conservative coverage (includes pending origin bytes) | **43.91%** |
| Authored candidates still NOT exact | **25 authored functions remain nonexact** |
| 25 nonexact breakdown | **22 large original state advances**, **3 other original small/medium whole functions** |
| 22 large original native CODE not accepted | **1,102,055 CODE bytes** (separate after-RET DATA not credited) |
| 3 small/medium native CODE not accepted | **3,406 CODE bytes** |
| Independently origin-unknown candidates | **95 functions / 3,420 CODE bytes**, uncredited |

**Important correction:** the older **25 unfinished** figure only counted
rows flagged both `owner=authored` and `status=unclassified` in
`config/functions.csv` (22 large + WinMain/Scene/Archive). There were
**11 more** candidates whose `function-origins.csv` origin was already
reviewed as authored, but whose provisional `functions.csv` owner is still
blank at that historical checkpoint because they lacked accepted source.
F755 (`00407270`), F758 (`00407A50`), F760 (`00407B80`), F765 (`0040D790`), F766 (`0040D6B0`), F769 (`0040B110`), F770 (`0040B000`), F775 (`0040D2E0`), F776 (`0040CEF0`), F779 (`0040CA20`) and F780 (`0040C9A0`) accepted all eleven. The remaining three
small/medium functions were already separately owner-marked authored.
Do not credit them until complete independent cold exact matches.
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
all-979-unit cold replay.** Only newly accepted or affected whole functions
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

**F764 historical original 2FA state research (before F767):** all six real floating
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

**F767 historical 2F9 physical source advance (before F768):** a real source correction of
borrowed opponent/actor X `+0x44` float members and read-only opponent Y
`+0x48`/actor Y lvalues restores all 381 original 2F9 mnemonics and
instruction widths within its entire 1,367 original CODE B and 34
original zero-addend PE/COFF fields. Eleven true whole-parent compiler
variants cut nonfield wrong bytes **265→249**, fixing all eight wrong
original 2F9 opcode positions without ASM/padding or target bytes. The
remaining 249 genuine register/operand bytes **are NOT exact**. The
whole 58,294-B fighter still compiles to 58,261 B, 2FA still has 156
real wrong operand bytes; true after-RET 943-B separate DATA reverified.
[F767 original PE and source proof](FIGHTER_STORM_ANGLE_TYPED_F767.md);
`scripts/repo-python scripts/verify-fighter-angle-storm-typed-f767.py`.

**F768 historical 2F8 integer-FPU source recovery (before F771):** actual C++ actor
`this+0x44` borrowed float member changes the real native actor-X
minus signed-direction×3 operation from nonnative `FLD/FISUB` to
original `MOVSX/IMUL/MOV/FILD/FSUBR`. In one newly compiled full
58KB parent, all **928 CODE B/252 native x86/23 PE fields** of 2F8
have exact original opcode and width positions; real nonfield
mismatching bytes fall **182→166**, with all five wrong x86 opcodes
eliminated. Those **166 operand bytes remain NONEXACT**. Same parent
rechecks F767 2F9 (249 wrong bytes), F764 2FA (156 wrong bytes),
and separate 943-B original afterRET DATA. The whole native function
still compiles 58,261/58,294 CODE B and is NOT exact.
[F768 full PE/COFF source proof](FIGHTER_STORM_VOLLEY_TYPED_F768.md);
`scripts/repo-python scripts/verify-fighter-storm-volley-typed-f768.py`.

**F771 historical 2FB whole-parent source result (before F777):** the original
`00550D97..0055101E` 647-B/181-x86/17-PE-field state now uses real
borrowed actor/opponent float `+0x44` X and opponent `+0x48` Y.
Eleven full 58KB VC7.1 source variants show all four wrong original
MOV/FLD instruction ordinals repaired and wrong real operand bytes
**119→111**, with 111 still explicitly **NONEXACT**. Previous full
2F8 166, 2F9 249 and 2FA 156 real operand-byte negatives remain;
the whole boss still emits 58,261 of original 58,294 CODE B and
943-B afterRET jump DATA remains independently correct. No case CODE
is accepted as an independent callable function. [F771 original
physical evidence](FIGHTER_GROUNDED_VOLLEY_TYPED_F771.md);
`scripts/repo-python scripts/verify-fighter-grounded-volley-typed-f771.py`.

**F777 historical 58KB register audit (before F778):**
Rebuilt the entire tracked F771 parent and independently confirmed its
real native `058` complete **469-B/135-x86/17-PE-field** case is
nonfield-exact outside legitimate external shared-tail JMPs, while
adjacent complete `059` has **19** actual wrong GPR operand bytes,
`060/061` **98/101**. Crucially *current-parent* native `063` is
**706 B/189 x86 /15 PE fields** but source emits **705 B/189 x86**:
real `CMP ...,0x96` ordinals **18/61/84** choose original
EDX/EAX/EDX (6/5/6 B) versus generated EAX/ECX/EAX (5/6/5 B).
Historical F626 `063` "strict" applies to a different old parent,
**not this one**. All **68** true PE/COFF source references in the
five native complete cases, plus original 943-B afterRET DATA, are
revalidated by
[`verify-fighter-current-register-phases-f777.py`](../scripts/verify-fighter-current-register-phases-f777.py).
Thirteen actual C++ 059 stage/float/short conversions and eight R015
`004EBDA0` typed-color/stage variants were negative; don't repeat
them without a new source hypothesis.
[Original physical evidence and negative bounds](FIGHTER_CURRENT_REGISTER_PHASE_AUDIT_F777.md).

**F778 historical full-parent default-handler repair (before F781):** independent
physical native dispatcher reading proves **239 original action IDs**
map to the real `00551598` shared default, not a source marker.
Its actual `0040FA30` state getter / `+0x70` compare / conditional
`0040FAC0(0)` transition is now normal whole-parent C++ with
**32 original CODE B, 10 native x86 and two genuine PE/COFF call
fields**; only four real EAX/ECX/EDX operand bytes in this guard
remain wrong. Recovered source **58,261→58,283 CODE B**, now only
**11 B/3 x86** shorter than original **58,294 B/16,471 x86**:
10 B of separately observed tail JMP/getter CODE plus one real
`0x63` CMP-width byte. "Near-exact-length" source controls that
route other cases through an extra getter were explicitly REJECTED
as nonnative control flow. Same fresh source verifies earlier
C8–CE/1F6–1F8/2DB/2F8–2FB and all 943 B/156 DIR32/319 sparse
nonfield original after-RET DATA. **Giant still NONEXACT, zero
whole-function CODE credit**. [F778 full native control-flow proof](FIGHTER_NATIVE_DEFAULT_F778.md),
`scripts/repo-python scripts/verify-fighter-native-default-f778.py`.

**F781 latest full-parent shared-getter recovery:** independently decoded
original native `005515BA` is the real **8-B getter call**, reached
by **exactly four direct physical JMPs** from action 0/2/4/5
(`00543462`, `005435EA`, `005436CD`, `005436DC`).
Those four source actions now use a shared post-switch getter entry,
while other normal breaks still return directly; the original default
guard retains its authentic short JMP over the getter. The whole
compiled 58KB parent now emits **58,293 of 58,294 CODE B** and
**16,471 of 16,471 original x86**, restoring the complete **46-B/16-x86
native suffix** with three genuine target-attested PE calls (default
`0040FA30/0040FAC0`, shared `0040FA30`). All four default GPR
bytes remain wrong and the **one real length byte deficit in 0x63**
persists, along with the original 059/060/061 GPR discrepancies.
The 943-B afterRET DATA and 68 native physical references across
058/059/060/061/063 are independently rechecked in the same parent.
**No entire 00543210 exact CODE credit.**
[Full F781 source/PE evidence](FIGHTER_EARLY_SHARED_GETTER_F781.md);
`scripts/repo-python scripts/verify-fighter-shared-getter-f781.py`.

**F782 targeted native 0x63 hypothesis rejection:** four actual
full F781 58KB VC7.1 compiled parents compared the original borrowed
expressions with typed opponent `+0x60`, actor `+0x39D`, and
both. Their **entire COFF CODE/DATA and all 1,863 typed relocation
shapes are identical**; real CMP width positions [18,61,84] remain
wrong, leaving original 0x63 706B vs generated 705B.
Simply adding typed borrowed views does not solve this GPR phase;
this is *negative evidence*, not exact credit.
[Reproducible F782 controls](FIGHTER_MODE63_BORROWED_VIEWS_F782.md);
`scripts/repo-python scripts/verify-fighter-mode63-borrowed-f782.py`.

**F790 renewed full 58KB boss native mode-63 control-flow study:**
seven full VC7.1 C++ parent rebuilds independently test
`150>stage`, signed-int conversion, negated comparison,
`<=149`, swapped short-circuit evaluation and genuine
boolean normalization against the pinned native PE.
The first three are codegen-identical to F781's still-nonexact
**58,293/58,294 CODE B**; the other variants either change
native Jcc semantics or produce a **712-B** instead of
706-B mode-63 case. Real CMP register-width ordinals
**18/61/84** remain unresolved; F790 rechecks original
mode-63 15 PE fields, 58/59/60/61 predecessor native
register negatives, the original 46-B common suffix and
all 943 native afterRET switch DATA in complete parents.
**Zero whole original fighter CODE credited.**
[Original native/VC7.1 evidence](FIGHTER_MODE63_CONTROLFLOW_F790.md);
`scripts/repo-python scripts/verify-fighter-mode63-controlflow-f790.py`.

**Next meaningful giant tasks:** resolve the real native `059` **19**
normalized nonfield GPR discrepancies and `060/061` **98/101**;
recheck *in the next newly compiled entire parent* (do not inherit
F737/F744 counts) and restore the remaining genuine deep x87 stack
lifetimes/earlier source actions. Recheck 0x63 CMP native
register widths [18,61,84] before attempting the last length byte. F759 had **40/40/34** real wrong register ordinals in 190/191/192,
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

## 3. All 3 additional nonexact original small/medium functions

These are **authored by `function-origins.csv`** but not canonically
matched (most have blank provisional `functions.csv` owner). This is
the complete **3,406-B** non-giant backlog, NOT just the three
frequently researched ownership functions:

| Native original entire function | CODE | Next evidence/source lead |
| --- | ---: | --- |
| `0x0041CE50` ArchiveCatalog destructor | 171 B | Best native 108/115 nonfield bytes, still seven genuine owner/CFG differences; [F697/F698 negatives](ARCHIVE_AGGREGATE_AND_REFERENCE_NEGATIVES_F697_F698.md) |
| `0x0043B0B0` Scene destructor | 248 B | Best 191/200 native nonfield bytes; used texture owner/stack layout unresolved; [F700](SCENE_TEXTURE_OWNER_LIFETIMES_F700.md) |
| `0x00602A60` WinMain | 2,987 B | Original saved local scene/path frame differs; [F702–F704](WINMAIN_USED_OBJECT_CONTEXT_NEGATIVES_F702_F704.md) |

The R011 ordinary-quad `0040C9A0` is now **115-B/37-x86/4-PE-field
whole cold exact** ([F780](SPRITE_ORDINARY_QUAD_NATIVE_F780.md)).
Two original calls prime/capture a texture pointer and real VC7 vector
size at stack `EBP−8`/`EBP−4`; the 132-B quad at `EBP−0x8C`
is copied before the final textured draw. The native 140-B grouped
scratch view matches the complete original 115 CODE bytes with all
four true physical REL32 fields; original historical C++ class layout
is not claimed. No double credit for the VC7 STL size() helper.
The R011 projected-quad `0040CA20` is now **92-B/34-x86/2-PE-field
whole cold exact** ([F779](SPRITE_PROJECTED_QUAD_NATIVE_F779.md)).
The observed 132-B quad needs explicit 4-B alignment, yielding real
`EBP−0x84` copy and `EBP−0x88` saved owner, with no invented frame padding.
It is no longer pending.
The R011 SpriteDrawing mode variant `0040CEF0` is now **994-B/269-x86/15-field whole cold exact**,
with original base-delegation and true rotated/unrotated `JP` branch
([F776](SPRITE_VARIANT_NATIVE_F776.md)); no longer pending.
The R011 scaled/rotated sprite `0040D2E0` is now **970-B/257-x86/14-field whole cold exact**,
with actual 132-B quad/RECT lifetimes and native x87 evaluation order
([F775](SPRITE_SCALED_NATIVE_F775.md)). It is no longer pending.
The R011 mirrored SpriteDrawing `0040D6B0` is now **212-B/66-x86/6-field complete cold exact**
with 188/188 authentic nonfield bytes and real mirrored RECT branch
([F766](SPRITE_OPAQUE_MIRRORED_F766.md)); no longer pending.
The R017 shared-texture allocator `0040B000` is **261-B/79-x86/11-PE-field whole cold exact**,
with original vector zero and loop index lexical lifetimes
([F770](TEXTURE_MANAGER_SHARED_NATIVE_F770.md)). It is no longer pending.
The R017 texture slot allocator `0040B110` is now **184-B/56-x86/8-PE-field cold exact**,
with genuine 44-B native VC7 used element lifetime
([F769](TEXTURE_MANAGER_SLOTS_NATIVE_F769.md)). It is no longer pending.
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

**F789 source-origin counterexample:** two separately explicit
user-defined normal C++ copy methods also reproduce *exactly*
the original 417B/128-x86 + 368B/118-x86 full machine code
and **all 8 authentic PE/COFF fields**. F787/F788's
compiler-implicit implementations independently reproduce the
same whole source geometry. This **proves provenance ambiguity
from byte evidence**; neither original candidate should be
prematurely reclassified as authored or excluded.
[Independent full explicit-source comparison](COMPOSITE_COPY_PROVENANCE_AMBIGUITY_F789.md);
`scripts/repo-python scripts/verify-composite-source-ambiguity-f789.py`.

**F788 whole original 417B implicit composite copy constructor
with genuine EH:** source probe `CompositeImplicitAssignmentF787.cpp`
also reproduces independently reviewed unknown-origin
`004591E0` **417/417 CODE B**, **128 original x86**,
393/393 nonrelocation bytes and **all six** PE fields
(including native `00656273` handler and two true
`00459390` library-owned nested constructor calls).
The actual first 16B header's **nontrivial destructor** creates
native EH state 0 at source +38h; first nested construction
sets byte-sized state 1 at +171h. It simultaneously preserves
F787's entire 368-B assignment match. Both remain
**provenance unknown**, no formal authored CODE credit.
[Complete F788 native constructor/EH proof](COMPOSITE_IMPLICIT_CONSTRUCTOR_F788.md);
`scripts/repo-python scripts/verify-composite-implicit-constructor-f788.py`.

**F787 original unknown-origin composite assignment source recovery:**
original `0045AAE0` /368 CODE B /118 native x86 has an entire
VC7.1 compiler-implicit C++ assignment source with all 360/360
nonrelocation CODE bytes and both real `0045AC50` nested
sequence calls at true offsets `151/163`; actual COFF section
extent is independently checked (not cropped).
The natural provisional 116B composite has genuinely observed
16B POD blocks at `+0x00/+0x44` and nested values at
`+0x54/+0x64`. **Provenance stays UNKNOWN**: equivalent
codegen from an explicit historical assignment remains possible.
Not accepted or credited to authored bytes.
[Full F787 physical evidence](COMPOSITE_IMPLICIT_ASSIGNMENT_F787.md);
`scripts/repo-python scripts/verify-composite-implicit-assignment-f787.py`.

**F791 reviewed entire authored Archive and Scene teardown owners:**
selected real 3-member and 2-member resource/filename grouped
locals for `0041CE50` (original 171B/51 x86) still emit
**183B/55 x86 or 177B/53 x86** under VC7.1.
Real used freed-pointer aggregate field order and lexical
timing for `0043B0B0` (original 248B/75 x86) preserve
all **12** genuine original physical PE/COFF refs but
match only **191/200** nonfield bytes best (some
permutations 189/200). Original resource/delete/filename
and texture/free stack slots have been independently decoded,
not normalized away. Ten newly reproduced *whole* targeted
C++ controls are nonexact; no authored credit.
[F791 original native teardown owner controls](ARCHIVE_SCENE_RESOURCE_OWNER_LIFETIMES_F791.md);
`scripts/repo-python scripts/verify-resource-teardown-ownership-f791.py`.

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
