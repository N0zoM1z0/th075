# TH075 — active reconstruction handoff (2026-10-31, F1029)

**Use this document for the live queue.** Read [AGENTS.md](../AGENTS.md),
[the build/evidence workflow](RE_WORKFLOW.md) and
[storage recovery instructions](STORAGE_HYGIENE.md). Original Japanese PE,
the live origin/exact manifests, and freshly rebuilt normal VC7.1 objects
**override old F-series prose**. No simultaneous agent owns dirty files:
inspect, finish and commit the current worktree.

Long research and failed intermediate snapshots are historical, not current:
[frozen F781–F906 handoff](history/RE_HANDOFF_F781_THROUGH_F906_PRE_CLEANUP_2026-10-31.md),
[F653–F753](history/RE_HANDOFF_F653_THROUGH_F753_2026-10-30.md),
[F598–F652](history/RE_HANDOFF_F598_THROUGH_F652_2026-10-29.md),
[F540–F596](history/RE_HANDOFF_F540_THROUGH_F596.md),
and the [chronological knowledge base](KNOWLEDGE_BASE.md).
Keep these evidence records; do not silently rewrite historical measurements.

## 1. Original native PE and complete-function exactness

| Verified live status | Original evidence |
| --- | --- |
| Pinned original | Japanese TH075 v1.11, `resources/th075.exe` |
| SHA-256 | `bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98` |
| Original candidates / unresolved provenance | **4,351 / 95** (3,420 uncredited original CODE B) |
| Independently authored original functions | **1,004** |
| Accepted complete exact callables | **979 functions / 979 exact units** |
| Accepted exact CODE | **868,243 original CODE bytes** |
| Reviewed original authored denominator | **1,973,704** CODE B |
| Reviewed / conservative exact coverage | **43.99%** / **43.91%** |
| Authored backlog | **25 authored functions remain nonexact** |
| Large original backlog | **22 large original state advances**, **1,102,055 CODE bytes** |
| Other entire original backlog | **3 other original small/medium whole functions**, **3,406 CODE bytes** |

**98% is not achieved.** Original owner decisions come from
[function-origins.csv](../config/function-origins.csv), not provisional
`functions.csv.owner` or old “25 plus 11 more” counts.
The 11 newly attributed complete functions were accepted in F755–F780.
The 95 still-unknown origins cannot be credited from identical emitted
bytes without independent historical source attribution.

**Strict acceptance:** byte-identical *entire original callable* plus
all genuine physical COFF PE fields and native authored provenance,
then targeted `scripts/repo-python scripts/replay-exact-units.py --unit NAME`.
A matching internal switch case, 16,471/22,721 mnemonic stream, source
CODE length, afterRET DATA, or successful compiler build is **not** exact.

## 2. Primary large Boss — original 005214B0 (46KB)

Original **46,755 callable CODE B /13,230 x86**, with **seven**
physical jump dispatches and **901 separately owned afterRET DATA B**
(139 DIR32 labels, 345 literal nonfield B). The F901
complete C++ source `.analysis/f901-fighter-31b/Boss005214B0-F901-whole.cpp`
is a **local research file**, not accepted source; normal pinned VC7.1
emits **46,754B /13,230 x86** and all original mnemonic positions,
but **five native widths** remain wrong (whole ordinals
2885/2908 action0x63, 8455 action1FD, 8986 action252, 9130 action254).
Source physical COFF and GPR allocations still differ.

- [F1026 entire original PE audit](FIGHTER_46KB_ALL_NATIVE_PE_TARGETS_F1026.md):
  **1,341/1,341 true external destinations**, including 30 `__ftol2`,
  plus 11 CODE-local and all afterRET DATA fields. Reproduce only
  `scripts/repo-python scripts/verify-fighter-whole-46kb-pe-targets-f1026.py`.
- [F901 13,230-instruction/physical width audit](SCRIPTED_FIGHTER_COMPLETE_TAIL_AND_WIDTH_AUDIT_F901.md):
  five real width errors, 443 source absolute nonoriginal COFF offsets.
- [F906 first GPR divergence](FIGHTER_FIRST_GPR_DIVERGENCE_F906.md),
  [F903 real mode63 controls](SCRIPTED_FIGHTER_MODE63_TYPED_GPR_F903.md),
  [F932 cross-actor ten-shot loop negative](SCRIPTED_FIGHTER_CROSS_BOSS_LOOP_REGISTER_PHASE_F932.md):
  a postincrement loop restores next0x59 GPR phase but *regresses*
  preceding0x58. Never adopt it solely for the next state.

**Next:** recover native two-case register phase without losing original
0x58 code, then five widths and *physical* COFF sites.
Do not mistake correct external destinations for correct source offsets.

## 3. Other large Boss functions — current priority

| Native whole function | Original CODE/x86, separate DATA | Latest complete, independently checked baseline |
| --- | --- | --- |
| `004AC040` | **82,796B /22,721 x86**, 1,126 afterRET B | [F1020 native full-frame owner](THIRD_FIGHTER_SHARED_REAL_RING_LOCAL_F1020.md); [F1028 entire PE fields](THIRD_FIGHTER_WHOLE_82KB_PE_TARGETS_F1028.md) |
| `00543210` | **58,294B /16,471 x86**, 943 afterRET B | [F917 genuine projectile-X](FIGHTER_WHOLE_BURST_NATIVE_FSUBR_F917.md); [F1025 entire PE fields](FIGHTER_58KB_ALL_NATIVE_PE_TARGETS_F1025.md) |
| `0050A580` | **81,539B /17,435 x86**, 567 afterRET B | [F569 genuine sparse-switch guard](CHARACTEROBJECT_SINGLE_SWITCH_F569.md); full body not exact |
| `0045DD70` | **60,999B** | Still pending original full-source reconstruction |

The other giant originals remain open too; do not focus exclusively
on these four. [Original giant/dispatch manifest](../config/fighter-boss-dispatch-fingerprints.json)
and [actual function provenance](../config/function-origins.csv)
are authoritative for each CODE extent and owned afterRET DATA.

**82KB original 004AC040:** selected tracked original-shaped
[normal C++ F1020 parent](../probes/FighterWhole004AC040F1020.cpp)
emits **82,796B /22,721 x86**, genuine frame `0x720`,
saved receiver `EBP-0x64`, and *all original mnemonic positions*.
The true source fix was ONE shared 2DB 36-shot loop counter, not
a dummy local. [F1028](THIRD_FIGHTER_WHOLE_82KB_PE_TARGETS_F1028.md)
checks **2,191/2,191 original external PE targets**,
10 CODE-local and 151 afterRET DIR32 fields and 522 literal DATA B.
**Still NONEXACT:** 12 widths, **6,958 GPR-role positions** and
physical relocation/branch geometry remain wrong. Known focused leads:
[F1021 original 0x58/0x59 strict-loop controls](THIRD_FIGHTER_NATIVE_58_59_FULL_GPR_CONTROLS_F1021.md),
[F1023 2BC/2BD/2BE GPR allocation](THIRD_FIGHTER_2BC_2BE_GPR_GRAMMARS_F1023.md),
[F1029 0x259 five-shot angle expression negatives](THIRD_FIGHTER_NATIVE_259_ANGLE_GPR_F1029.md).
All used *entire* normal 82KB source compilations; avoid repeating
their ruled-out C++ spellings. The next meaningful advance is source
lifetime/register phase simultaneously compatible with neighboring
native states, not case marker proliferation. The original afterRET
table and game actions remain one giant callable, never independent
accepted functions.

**58KB original 00543210:** F917 selected local
`.analysis/f917-native-burst-x87-verified/F917-borrowed-real-X.cpp`
emits **58,293B /16,471 x86**, preserves native frame `0x218`
and all original mnemonic positions. [F1025](FIGHTER_58KB_ALL_NATIVE_PE_TARGETS_F1025.md)
rechecks **1,697/1,697 physical external PE targets**,
156 actual afterRET DIR32 labels and 319 nonfield bytes.
**Still NONEXACT:** original 0x63 has three mismatched widths
(whole ordinals 2934,2977,3000), **1,741 GPR-role errors**.
[F1025 58KB mode63 whole-parent controls](SECOND_GIANT_NATIVE_MODE63_GPR_F1025.md)
tested 10 normal VC7.1 variants without fixing the true native CMP
roles; check the original PE, not stale hypotheses.

**81KB single-switch 0050A580:** the F569 one-switch diagnostic
verifies the original 17-instruction parent guard, signed cooldown,
92 physical DIR32 table slots and 199 sparse bytes, **not** the
81,539B full body. Targeted entrypoint:
`scripts/repo-python scripts/verify-characterobject-single-switch-source.py --boss 0x0050A580`.
Old F13x–F148 full drafting/source traces are preserved under
`.analysis/character-move-4ac040/`, the frozen history and the
restorable native archives; they are **not** a newly accepted
82KB or 81KB whole game function.

## 4. All three remaining independent small/medium originals

| Original native full callable | Real size | Current truth and best next lead |
| --- | ---: | --- |
| `0041CE50` ArchiveCatalog destructor | **171B/51 x86** | [F936 real index/delete/filename control](ARCHIVE_NATIVE_LOOP_VALUE_CATEGORIES_F936.md); 14 physical PE fields, **108/115 nonfield bytes** matched; three real EBP temp slots permuted. [F900 live-owner controls](ARCHIVE_REAL_GROUPED_LIFETIMES_F900.md) negative |
| `0043B0B0` Scene virtual destructor | **248B/75 x86** | [F1015 three genuine free-owner slot controls](SCENE_THREE_FREE_DECLARATION_ORDER_F1015.md); 12 real PE fields, **191/200 nonfield bytes** matched, original texture/delete EBP owners still different |
| `00602A60` WinMain | **2,987B/654 x86** | [F911 selected live-source grammar](WINMAIN_REAL_MAIN_BEFORE_SCENE_F911.md) emits **2,984B /654 x86**; **645/654 original widths** correct. [F914 slot recovery](WINMAIN_NATIVE_FRAME_FIRST_SCENE_OWNER_F914.md) recovers native frame/three EBP slots but regresses width matches; [F927 used-gap controls](WINMAIN_REAL_USED_GAP_NEGATIVES_F927.md) negative. Original 60B afterRET scene table is NOT CODE |

All **3,406 original CODE B remain nonexact**. Work on full
171/248/2,987-byte native callables, not cropped snippets.
The WinMain original compiler flag is `/GX-`; `/GX`
changes EH machinery and is not original. For Archive/Scene
the genuine C++ pointer lifetimes, not branch-byte patches,
must fix their still-wrong EBP assignments.

## 5. Exact-preserving C++ type/owner work

These are **previously credited bytes**, not new acceptance.
When modifying any translation unit or header, replay **ALL**
already exact units in that affected source object; COFF `$L`
and `$SG` numbering can change merely from an include.

| Current source/ABI evidence | Targeted native whole-unit replay |
| --- | --- |
| [F1022 actor script WORDs +0xF00/+0xF02](FIGHTER_SCRIPT_COUNTER_ADJACENT_NATIVE_F1022.md) | **46/46** in 11 objects, 4,772 previously accepted B |
| [F1024 signed stage/frame WORDs +0x62/+0x64](FIGHTER_ANIMATION_PHASE_WINDOW_F1024.md) | **9/9** in 8 objects, 11,573 previously accepted B; giant 31KB TU explicitly restored after `$L` renumbering |
| [F1027 action/timer WORDs +0x80/+0x82](FIGHTER_NATIVE_ACTION_TIMER_PAIR_F1027.md) | **46/46** in 6 objects, 10,262 previously accepted B; two large combat TUs restored |
| [F946 AI adjacent signed shorts +0x512/514/516](FIGHTER_AI_ADJACENT_SHORT_FIELDS_F946.md) | **8/8** real whole AI functions, 68,786 previously accepted B |
| [F999 native health signed WORDs](FIGHTER_NATIVE_VITAL_SHORT_WINDOW_F999.md) | **47/47**, 6,640 previously accepted B |
| [F1006 native combo signed WORDs](FIGHTER_COMBO_NATIVE_SHORTS_F1006.md) | **42/42**, 4,755 previously accepted B |
| [F992 native fighter result bytes](FIGHTER_ROUND_RESULT_BYTE_WINDOW_F992.md) | **45/45**, 4,191 previously accepted B |

Older accepted field/ABI controls remain in
[the historical experiment index](KNOWLEDGE_BASE.md).
A header-looking improvement that changes a compiler-local
COFF symbol is not exact even if every nonrelocation byte matches.

## 6. Agent operating checklist / storage

**Preflight, no whole corpus replay:**

    git status --short --branch
    scripts/repo-python scripts/verify-target.py
    scripts/repo-python scripts/validate-tracking.py --require-target
    scripts/repo-python scripts/report-reconstruction-status.py --summary
    scripts/repo-python scripts/audit-active-handoff.py
    scripts/repo-python scripts/ghidra.py check

Use `scripts/repo-python` and the pinned original SHA;
run Wine/VC7.1 headless and serial. Only
`scripts/repo-python scripts/replay-exact-units.py --unit NAME`
for **affected or newly accepted whole callables**.
Do not run a 979-function cold replay.
Do not assume historical source or naming establishes authorship,
or import/patch the original Ghidra project. Save substantial
verified work in **several `gpt-web: ...` commits** and deal with
dirty files directly. `git diff --check`, source/manifest
consistency and a clean final worktree matter.

**Storage:** preserve the user-supplied original EXE,
`build/matching/`, existing Wine/VC7.1/Ghidra,
source and target/COFF evidence. The SHA256-verified
`.analysis/cache-archives/` archives are local, **not Git-backed**:
retain both archive and index; restore only the individual
historical OBJ/PDB/ASM/LOG needed by a targeted verifier.
See [storage hygiene and restore commands](STORAGE_HYGIENE.md):
for frozen F133–F166 native compiler traces use
`scripts/repo-python scripts/archive-frozen-giant-traces.py --verify`
and `--restore ORIGINAL_RELATIVE_PATH`. Historical F650–F906
research OBJ/PDB are individually restorable through
`scripts/repo-python scripts/archive-recent-probe-objects-f907.py --family binaries --restore ORIGINAL_RELATIVE_PATH`.
Never assume an ignored archive is backed up by a Git commit.
Never delete unrecognized ignored research or the only
copy of original native/compiler evidence.
