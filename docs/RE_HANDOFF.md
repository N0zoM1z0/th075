# TH075 — CURRENT reconstruction agent handoff

**Current evidence checkpoint: 2026-10-31, F960.** This is the short
working queue, NOT a chronological research journal. Native original PE
and live exact/origin manifests outrank historical C++ guesses and
older F-series reports. The former long handoff, with its original
research preserved and links repaired, is the
[frozen pre-cleanup F781–F906 snapshot](history/RE_HANDOFF_F781_THROUGH_F906_PRE_CLEANUP_2026-10-31.md).
Other historical handoffs:
[F653–F753](history/RE_HANDOFF_F653_THROUGH_F753_2026-10-30.md),
[F598–F652](history/RE_HANDOFF_F598_THROUGH_F652_2026-10-29.md),
[F540–F596](history/RE_HANDOFF_F540_THROUGH_F596.md).
The [knowledge base](KNOWLEDGE_BASE.md) contains historical experiments.

## 1. Original native PE and complete-function exactness

| Verified item | Current value |
| --- | --- |
| Native original | Japanese TH075 v1.11 resources/th075.exe |
| SHA-256 | bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98 |
| Provisional candidates / origin unknown | 4,351 / 95 |
| Independently authored originals | **1,004** |
| Accepted exact whole functions | **979 functions / 979 exact units** |
| Accepted native CODE | **868,243 original CODE bytes** |
| Reviewed authored denominator | **1,973,704** |
| Reviewed exact coverage | **43.99%** |
| Conservative coverage | **43.91%** |
| Authored still nonexact | **25 authored functions remain nonexact** |
| Giant backlog | **22 large original state advances**, **1,102,055 CODE bytes** |
| Non-giant authored backlog | **3 other original small/medium whole functions**, **3,406 CODE bytes** |
| Uncredited unknown provenance | 95 candidates, 3,420 CODE B |

**The 98% goal is not met.** The canonical exact ledger accepts only
complete original callable functions, never internal switch cases,
afterRET jump data or origins still marked unknown.
The historical "25 pending plus 11 more" count was superseded by
eleven whole exact acceptances F755–F780. There are **25 total**
remaining authored original functions, not 27 or 36.
Use [independent origins](../config/function-origins.csv),
[original candidates](../config/functions.csv) and
[whole match units](../config/match-units.toml), not old prose.

Fast preflight — no all-unit cold replay:

    git status --short --branch
    git log -5 --oneline
    scripts/repo-python scripts/verify-target.py
    scripts/repo-python scripts/validate-tracking.py --require-target
    scripts/repo-python scripts/report-reconstruction-status.py --summary
    scripts/repo-python scripts/audit-active-handoff.py
    scripts/repo-python scripts/ghidra.py check

One worker owns all dirty edits: inspect and continue them.
Every substantial milestone gets a gpt-web: xxx commit; do several
commits per substantive session. Never replay all 979 exact units.

## 2. Primary large Boss: real original 005214B0

Original: **46,755 callable CODE B/13,230 x86** and five separate
packed afterRET jump tables of **901 DATA B**. Latest selected
complete normal pinned VC7.1 source generates **46,754 CODE B/
13,230 x86**, plus the separate 901 DATA B. **NOT exact.**

[F901 whole-native x86/PE audit](SCRIPTED_FIGHTER_COMPLETE_TAIL_AND_WIDTH_AUDIT_F901.md):
scripts/repo-python scripts/verify-scripted-fighter-tail31b-31c-f901.py

- All 13,230 original instruction mnemonics align by ordinal.
  **Five original instruction widths differ**: whole ordinals
  2885 and 2908 (original action0x63), 8455 (1FD),
  8986 (252), and 9130 (254). The net one-byte shortfall
  does NOT mean only one original machine-code byte is wrong.
- 1,352 generated CODE COFF fields; **909** lie at identical
  original absolute offsets, **443 are shifted**.
  For 79 sourced original case interiors, 797 original
  physical PE call/global targets are verified, yet 424
  source fields move absolutely and twelve also move
  relative to action252/254. Never relocation-mask shifted fields.
- [F932 cross-actor native 0x59 register-phase proof](SCRIPTED_FIGHTER_CROSS_BOSS_LOOP_REGISTER_PHASE_F932.md):
the SAME genuine 32-bit ten-shot
while (burst++<10) source change as F931
improves the other 46KB original 005214B0
action0x59 from **19 wrong original GPR
roles and operand bytes to ZERO**, with
356B/95 original x86/16 true PE fields
verified. All 13,230 original whole source
x86 remain ordinal aligned. However original
action0x58 regresses by **one mnemonic
and two widths**, so F901 remains selected
and the complete function remains NONEXACT.
Full-source, original-target verifier included.
Next: simultaneous native 0x58 + 0x59 grammar.

[F909 0x58 phase negatives](FIGHTER_PRE59_REGISTER_PHASE_F909.md):
27 full VC7.1 parent variations did
not repair 0x59's register phase.

- [F906 first true GPR divergence](FIGHTER_FIRST_GPR_DIVERGENCE_F906.md):
  whole x86 ordinal **2103**, original address **0052327A**,
  case **0x59**. Currently **2,736 instruction GPR-role
  mismatches** in the complete father; 0x59 alone has 19
  GPR-role differences (356B/95 x86/16 real PE fields).
  33 full VC7.1 source variations did not improve them.
  Targeted reproducer:
  scripts/repo-python scripts/verify-scripted-fighter-first-gpr-f906.py
- [F903 0x63](SCRIPTED_FIGHTER_MODE63_TYPED_GPR_F903.md):
  original 417B/109 x86; 29 C++ alternatives failed to
  restore native CMP roles/widths. Source PE field at
  case+184 is originally at case+185. One source makes
  the whole father 46,755 B but incorrectly grows case63
  to 418B. **A matching total length is not exactness.**
- [F902 1FD](SCRIPTED_FIGHTER_1FD_TYPED_OWNER_LVALUES_F902.md):
  fourteen real owner-access models failed to recover
  original six-byte CMP ECX,0x95; source uses five-byte CMP EAX.
- [F905 252/254](SCRIPTED_FIGHTER_BYTE_REG_PHASE_F905.md):
  54 complete-source variations failed to restore original
  SUB DL/CL/AL sequence or twelve native PE field positions.
- F901 recovered actual 31B (248B/74 x86/8 fields),
  31C (219B/63 x86/7 fields) and earlier 2F8
  (1,151B/316 x86/28 fields) including true native
  shared tail jumps; they are still **internal cases**,
  never separate accepted whole callable functions.

**Next work:** the original 0x58 32-bit for-loop is strict
in the current whole 005214B0 parent, yet its next original
0x59 uses 19 wrong GPR roles. F932 demonstrates that real
postincrement-while loop grammar restores ALL 0x59 roles
but regresses 0x58 by one mnemonic/two widths in both
the 46KB and the independent 58KB father. Recover a
genuine original C++ lowering that makes BOTH adjacent
cases native simultaneously, then tackle the remaining
five whole-fighter width differences and shifted PE
relocations. Do not use a nonnative loop only to fix
the next state. Rebuild affected full parents through
the F931/F932 original-backed scripts; if previous
private sources are absent, regenerate with F901/F917.

## 3. Other genuinely large original functions

The other **20 large original state-advance functions** also remain
unmatched. Important true original callable extents:

| Original start | Native CODE B | Current lead |
| --- | ---: | --- |
| 00543210 | 58,294 + 943 separate afterRET DATA | [F917 selected native signed burst X](FIGHTER_WHOLE_BURST_NATIVE_FSUBR_F917.md): all 16,471 native/source mnemonics now align; 3 genuine width errors remain |
| 004AC040 | 82,796 + 1,126 separate afterRET DATA | [F938](THIRD_FIGHTER_REAL_BOUNCE_F938.md): full source probe now includes real 0x59 (356B/95 x86/16 PE targets) instead of a marker; entire 82KB remains NONEXACT |
| 0050A580 | 81,539 | Giant state-advance original source reconstruction |
| 0045DD70 | 60,999 | Giant state-advance original source reconstruction |

[F955 three-state original 82KB CC/CD/CE phase](THIRD_FIGHTER_CE_NATIVE_PHASE_F955.md):
original CE 394B/115x86/9 PE targets
now naturally authored. CE's GPR roles
improve **72 wrong→0** if real
preceding CC+CD C++ is present.
[F956 downstream CF/D0 GPR recovery](THIRD_FIGHTER_POST_CE_GPR_PHASE_F956.md):
unchanged original CF/D0 native x86
roles improve **18/35 wrong→0/0**
when either actual CE or actual
CC+CD predecessor source is compiled
within the same partial father.
[F953 original CC/CD](THIRD_FIGHTER_CC_CD_NATIVE_PHASE_F953.md):
two 435B/128-x86/11 PE target
cases; CD GPR roles likewise
improve **77 wrong→0** when
real CC is present. Original whole
82,796B fighter is NONEXACT;
true saved-this EBP and 0x720
frame are not reconstructed.

[F976 third 82KB native random 1A0 loops](THIRD_FIGHTER_RANDOM_LOOP_F976.md):
TRACKED cumulative partial C++
**34,055B/9,341 x86**. Native
1A0 5/8 real random-shot loops
570B/148x86/12 actual PE
targets now all mnemonic/width
matched after fixing Y-base
before Rand20 source evaluation.
66 original GPR roles remain
wrong. Real parent stack grows
0x144→0x16C, moves saved `this`
EBP−0x10→−0x18 and repairs
**four native x87 widths in
preceding 191** (12 wrong→8);
original parent 0x720 and
EBP−0x64 still absent.
[F975 19D/19E/19F](THIRD_FIGHTER_STAGES19D19F_F975.md)
native 400B/97,475B/128,
478B/128 with 31 PE targets,
0 mnemonic/width errors.
Complete original 82,796B
fighter remains NONEXACT.

[F957 native CA→CB GPR negatives](THIRD_FIGHTER_CA_PRECEDES_CB_GPR_F957.md):
30 complete partial parent trials did
not improve CB's 79 wrong GPR
roles; next focus genuine parent
stack and ownership.

[F952 local CB grammar negatives](THIRD_FIGHTER_CB_REGISTER_PHASE_F952.md):
28 separate natural whole-parent
variants also failed to fix CB GPR.

[F951 CB](THIRD_FIGHTER_FOURWAY_CB_F951.md),
[F950 CA](THIRD_FIGHTER_FOURWAY_CA_F950.md),
[F949 C9](THIRD_FIGHTER_FOURWAY_C9_F949.md),
[F948 C8](THIRD_FIGHTER_FOURWAY_C8_F948.md),
[F947 CF/D0](THIRD_FIGHTER_FALL_REFLECT_F947.md)
and earlier [F943](THIRD_FIGHTER_NATIVE_SELECTOR_F943.md)
remain native PE source-backed.

[F937 58KB strict 0x58 predecessor](FIGHTER_STRICT_PREDECESSOR_LIMIT_F937.md):
49 complete fighter source variants
did not repair the native next-state
register phase without 0x58 regressions.

[F931 58KB original preceding-loop GPR phase](FIGHTER_FOLLOWING_BOUNCE_REGISTER_PHASE_F931.md):
real `while (burst++<10)` moves next
0x59 GPR errors **19→0**, but regresses
original preceding 0x58 by one
mnemonic/two widths. Not an exact
native whole father.

[F926 58KB mode63 register negatives](FIGHTER_REGISTER_OWNER_GRAMMAR_F926.md):
38+24 complete natural source
controls failed to fix native 0x59
and 0x63 GPR roles; no exact credit.

[F917 58KB projectile-X x87 source recovery](FIGHTER_WHOLE_BURST_NATIVE_FSUBR_F917.md):
four real original IMUL/FILD/FSUBR
sequences now byte-correct, and
all 16,471 whole-parent mnemonics
align. Three native width and
many real GPR/PE differences
persist; entire giant NONEXACT.

## 4. All three remaining independent small/medium originals

| Original callable whole function | Native CODE B | Most useful evidence |
| --- | ---: | --- |
| 0041CE50 ArchiveCatalog destructor | 171 | [F900](ARCHIVE_REAL_GROUPED_LIFETIMES_F900.md): 25 complete VC7.1 sources; best 108/115 nonfield original bytes, wrong EBP lifetimes |
| 0043B0B0 Scene virtual destructor | 248 | [F889](SCENE_MIXED_REAL_FREE_POINTER_OWNERS_F889.md): 29 real whole-source layouts; best 191/200 original nonfield bytes |
| 00602A60 WinMain | 2,987 | [F911](WINMAIN_REAL_MAIN_BEFORE_SCENE_F911.md): 32 complete real owner-layout sources; best 2,984 emitted CODE B and 645/654 native x86 widths, but still wrong EBP storage |

Together they are **3,406 CODE bytes**, not exact.
Use the targeted source-only reproductions:

    scripts/repo-python scripts/verify-archive-grouped-live-owners-f900.py
    scripts/repo-python scripts/verify-scene-mixed-owner-slots-f889.py
    scripts/repo-python scripts/verify-winmain-stage-live-context-f904.py
    scripts/repo-python scripts/verify-winmain-leading-live-context-f904.py

[F921/F927 real WinMain used-gap hypothesis](WINMAIN_REAL_USED_GAP_NEGATIVES_F927.md):
66 full normal VC7.1 WinMain sources test a
genuinely used firstScene pointer and the real
event/directory/windowWidth/windowHeight members
ahead of HWND/scene/path. All 66 keep 654 x86
mnemonics and 60B afterRET DATA, but none restores
the original firstScene=-0x19C with actual HWND
=-0x188, scene=-0x184, path=-0x180. A four-full-
source tracked PE verifier confirms 16 actual
constructor mappings and 15 native table entries.
This **negative does not supersede F914's separate
three-slot recovery**. Whole WinMain remains nonexact.

[F935/F936 native Archive pointer owner controls](ARCHIVE_NATIVE_LOOP_VALUE_CATEGORIES_F936.md):
32 independently compiled complete 171B
ArchiveCatalog destructor grammar sources
vary real unsigned index loop, filename
reference/value category and scalar delete.
Twenty-six still match only **108/115**
actual original nonfield bytes and retain
resource/delete/filename EBP **-0x10/
-0x0C/-0x08** rather than native
**-0x0C/-0x08/-0x10**; other candidates
regress. Portable verifier re-checks all 14
native PE call/global fields in seven
complete original-shaped sources. The
171B whole function is NONEXACT.

[F914/F915 original WinMain frame/slot probe](WINMAIN_NATIVE_FRAME_FIRST_SCENE_OWNER_F914.md):
19 full source member models and 30 declaration/member placement controls
tested the genuinely used first scene pointer. A complete alternative
now recovers the **original 0x278 frame and all three original
HWND=-0x188 / currentScene=-0x184 / path=-0x180 EBP slots**.
However its real first-scene pointer temp moves from original
-0x19C to -0x7C, leaving **643/654 matching x86 widths**;
the F911 645/654 alternate remains the best width geometry.
Whole startup is **NONEXACT**.

[F911 live main-before-scene ownership](WINMAIN_REAL_MAIN_BEFORE_SCENE_F911.md):
32 full source live-owner layout variants narrowed the native HWND
adjacency. The selected tracked *whole* WinMain now emits **2,984
CODE B /654 x86** and **645/654 original instruction widths**;
16 original ctor allocations and 15 native switch dispatch targets
remain correct. Nine genuine widths still differ (five graphics,
four cleanup local addresses); all original absolute EBP owner
offsets and full PE fields still need reconstruction.
**WinMain is NONEXACT.**

[F910 physical original scene switch reconstruction](WINMAIN_ORIGINAL_SWITCH_PHYSICAL_ORDER_F910.md):
the native afterRET jump table proves **case 4 is emitted physically
before cases 0–3**, despite numeric dispatch order. A complete new
tracked WinMain source now matches **all 16 original allocation
sizes/constructor pairings**, all 15 case-index/physical-instruction
table mappings, and **637/654 original x86 widths** (up from
F904's 633/654). It still emits **2,960 rather than 2,987 native
CODE B**; the independent full WinMain remains NONEXACT.

Original WinMain has 654 x86, 123 CALLs and a separate
60B afterRET 15-scene table; its native flags require
**/GX-**. /GX wrongly generates extra exception-handling
instructions and must not be used as a native comparison.

## 4a. Exact-preserving source semantics — affected-unit replays ONLY

These changes improve real observed C++ field/owner semantics in
already-accepted whole native functions. **No new exact CODE credit**.
Consult the linked original-PE documentation rather than replaying
all 979 functions:

- [F913 background tick/frame adjacency](BACKGROUND_COUNTER_TYPED_ADJACENCY_F913.md):
  11 complete callbacks, **463 previously accepted native bytes**, 11/11 exact.
- [F919 AnimationState three signed short counters](ANIMATION_COUNTERS_TYPED_NATIVE_F919.md):
  3 complete callbacks, **151 existing bytes**, 3/3 exact.
- [F920/F922 shared texture-entry flag and typed metadata](TEXTURE_SHARED_NATIVE_ENTRY_F922.md):
  2 complete original functions, **502 existing bytes**, 2/2 exact;
  [F920's five-field original entry evidence](TEXTURE_ENTRY_TYPED_BORROWED_F920.md).
- [F925 shared TextureManager 44B element and mode](TEXTURE_MANAGER_SHARED_REAL_ELEMENT_F925.md):
  2 complete original allocators, **445 existing bytes**, 2/2 exact.
- [F933 two real BackgroundStage field grammars](BACKGROUND_STAGE_THREE_NATIVE_FIELDS_F933.md):
  **30 integer-zero / 6 float-initializer complete native constructors**,
  total **5,531 existing bytes**, 36/36 exact, 2 source objects.

[F946 real adjacent fighter AI shorts](FIGHTER_AI_ADJACENT_SHORT_FIELDS_F946.md):
8 already exact AI functions (68,786 CODE B)
retain **8/8 canonical cold exact** after
type-checking signed shorts at +0x512/514/516.
[F940 adjacent +0x511 byte](FIGHTER_COMMAND_BYTE_SHARED_F940.md):
9 affected original functions (69,846 B)
still 9/9 exact; polling input kept unchanged
after evidence of `$SG` symbol renumbering.

[F960 native fighter notice/HUD borrowed fields](FIGHTER_NOTICE_BORROWED_NATIVE_F960.md):
true +0x6E7/6E8/6E9 notice bytes,
+0x6EA/6EC signed motion shorts,
+0x6F0/6F2/6F4/6F6 state shorts;
+0x6F6 render reads LOW BYTE
(not the full 16-bit written field).
**14/14 affected complete original
functions remain cold exact,
1,663 existing original CODE B
across three original source TUs**.
[F954 signed profile selectors](PROGRESS_SELECTION_SIGNED_BYTE_FIELDS_F954.md):
two signed bytes +0x16AC4/5 remain
11/11 cold exact, 1,238 existing B.

[F967 native profile index reuse in six more source objects](PROGRESS_SELECTION_CROSS_OWNER_F967.md):
two genuine signed-byte profile keys
+0x16AC4/5 now shared by record
leaves, knockout/card, progress
counter, memcpy restore and options.
Canonical affected **12/12 whole
functions cold exact, 2,460 existing
CODE B across six source objects**.
F954 previously typed the same
native pair in two other objects.

[F973 real native fighter effect parameter/pointer views](FIGHTER_EFFECT_BORROWED_FIELDS_F973.md):
two independent effect source objects
share genuine pointer +0x2EC,
transform first byte +0x2F0
and float param address +0x314.
Affected **8/8 complete native
functions cold exact, 730 existing
CODE B**. VC7.1 templated
offsetof limitation is documented.

## 5. Exact acceptance, storage, and end-of-session checks

Read [AGENTS.md](../AGENTS.md), [workflow](RE_WORKFLOW.md)
and [storage hygiene](STORAGE_HYGIENE.md). Full original
callable byte equality requires the original PE boundary,
correct native ABI and physical zero-addend COFF relocation
positions/targets, natural pinned VC7.1 C++ source,
and independent authored origin. Whole accepted source
unit replay ONLY when the new/affected whole function
is eligible:

    scripts/repo-python scripts/replay-exact-units.py --unit UNIT_NAME

Keep the original EXE, Wine/VC7.1 prefix, Ghidra,
accepted matching objects, configs, original receipts
and local compressed history archives. The F907 script
scripts/archive-recent-probe-objects-f907.py safely restores
individual SHA256-original F650–F906 research OBJ/PDB copies
from the machine-local archive; 4,712 files were compacted,
reclaiming 220,205,684 bytes net. F908 safe two-week-horizon
Git GC and generated Python bytecode cleanup reclaimed another
129,222,294 bytes; combined measured recovery is 349,427,978 bytes.
The
scripts/archive-frozen-giant-traces.py helper recovers
SHA256-verified archived historical original traces.
Do not remove the only copy of any private research
or treat Git-ignored archives as remotely backed up.

After affected-unit verification, run only the light checks:

    scripts/repo-python scripts/validate-tracking.py --require-target
    scripts/repo-python scripts/audit-active-handoff.py
    scripts/repo-python scripts/update-progress.py --check
    scripts/repo-python scripts/ci.py
    git diff --check
    git status --short --branch

No full exact-unit cold replay, no default push. Commit
substantial work as gpt-web: xxx and handle all dirty files.
