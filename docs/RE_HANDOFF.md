# TH075 — CURRENT reconstruction agent handoff

**Current evidence checkpoint: 2026-10-31, F906.** This is the short
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
- [F909 preceding native 0x58 register-phase experiment](FIGHTER_PRE59_REGISTER_PHASE_F909.md):
  27 whole normal VC7.1 father variants; 26 original-instruction-count
  sources, 1 longer. None fixes the original 0x59 entry EAX/ECX phase
  or improves the first whole GPR mismatch ordinal 2103. Eight
  genuinely different equal-sized emitted CODE alternatives tested;
  the register-phase mismatch is NOT explained by trivial preceding
  ten-shot-burst source grammar.
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

**Next work:** resolve register allocation beginning in
the real case0x59, then the five source/native width
differences in the SAME full compiled father. Verify PE
field offsets, types, addends and original targets, not just
instruction mnemonic/byte totals. Regenerate ignored current
source/OBJ under .analysis/f901-fighter-31b/ with F901 if absent.

## 3. Other genuinely large original functions

The other **20 large original state-advance functions** also remain
unmatched. Important true original callable extents:

| Original start | Native CODE B | Current lead |
| --- | ---: | --- |
| 00543210 | 58,294 + 943 separate afterRET DATA | [F917 selected native signed burst X](FIGHTER_WHOLE_BURST_NATIVE_FSUBR_F917.md): all 16,471 native/source mnemonics now align; 3 genuine width errors remain |
| 004AC040 | 82,796 | Giant state-advance original source reconstruction |
| 0050A580 | 81,539 | Giant state-advance original source reconstruction |
| 0045DD70 | 60,999 | Giant state-advance original source reconstruction |

[F923/F924/F926 full-fighter register-owner controls](FIGHTER_REGISTER_OWNER_GRAMMAR_F926.md):
**38 + 24 complete VC7.1 whole-father sources** test real
actor 0x59 and opponent 0x63 signed-stage/float
lvalue grammars. None improves the first GPR mismatch
at whole ordinal 2198 (original 00545109, nineteen
wrong roles in action0x59) or fixes the three native
0x63 CMP register-width roles. A portable 10-whole-
source bounded verifier records the negative result.
**The 58KB original remains NONEXACT**; no partial
case or total-size credit.

[F916/F917 whole-parent x87 improvement](FIGHTER_WHOLE_BURST_NATIVE_FSUBR_F917.md):
original 00543210's four real projectile-X calculations at
native x86 ordinals 11765/11970/12328/12528 now use a
**borrowed typed +0x44 float lvalue**, positive signed integer
IMUL and genuine original x87 FSUBR. In freshly compiled
58KB whole parents, all **16,471 original instruction mnemonics**
align and the four **six-instruction native projectile sequences
are byte-identical**; exactly eight original-relevant source
opcode/immediate bytes improved. Three original width mismatches
and many real GPR/absolute relocation differences persist;
**no whole exact or extra credited CODE**.

These original functions remain nonexact despite local case
research. Older 58KB parent sizes in the
[frozen full research snapshot](history/RE_HANDOFF_F781_THROUGH_F906_PRE_CLEANUP_2026-10-31.md)
are specific historical compiler contexts, not the latest
whole-function acceptance. The
[physical dispatch map](../config/fighter-boss-dispatch-fingerprints.json)
is evidence for switch structure, not source provenance.

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

[F913 typed stage-counter adjacency](BACKGROUND_COUNTER_TYPED_ADJACENCY_F913.md):
11 independent formerly exact background animation callbacks
(**463 original native CODE B**) now use a naturally typed,
two-member signed 32-bit +0x68/+0x6C borrowed window in
the tracked implementation. The original complete owner layout
remains unknown; *only the affected eleven whole units* were
cold-replayed **11/11 exact**, preserving accepted coverage.

[F919 three real signed-short AnimationState fields](ANIMATION_COUNTERS_TYPED_NATIVE_F919.md):
the original 0040FAC0/0040FB00/0040FB40 physical complete
functions prove a single +0x60/+0x62/+0x64 short-counter
window. Replaced three independent raw casts with a typed
six-byte borrowed view and cold-replayed **only the affected
three whole functions: 3/3 exact, 151 existing native CODE B
preserved**. The full AnimationState owner remains unknown.

[F920 texture entry native borrowed fields](TEXTURE_ENTRY_TYPED_BORROWED_F920.md):
the entire already accepted original 0040C590
`TexturePalette40C8C0::Refresh` now uses typed
member reads at observed offsets +0/+4/+8/+0xC/+0x28
instead of five unrelated raw offset casts. Ten
full VC7.1 C++ variants were tested; the new
tracked whole 340B/125-x86 original leaf remains
**1/1 canonical cold exact** with all 11 existing
actual PE/COFF references verified. No new exact credit.

[F922 common borrowed texture-entry field](TEXTURE_SHARED_NATIVE_ENTRY_F922.md):
independently re-decoded native byte+0x28 palette flag
at 0040C602 (Refresh) and 0040C912 (GetTexture);
both source units now share one offset-checked incomplete
entry view, retaining original source semantics. **Only
the two affected 340B and 162B entire native functions
were freshly cold-replayed, 2/2 exact /502 previously
accepted CODE bytes**. No corpus-wide replay.

[F925 shared native TextureManager element and mode](TEXTURE_MANAGER_SHARED_REAL_ELEMENT_F925.md):
0040B000 and 0040B110 each construct/destruct a
physically observed 44-byte element and read/write
the real byte at receiver+0x4C. Two duplicated
original-shaped type declarations are unified into
a partial borrowed mode/element header, without
guessing full vendor ownership. Canonical **2/2
whole-function exact cold replays /445 existing
CODE bytes**; no all-unit replay.

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
