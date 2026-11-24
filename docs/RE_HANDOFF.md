# TH075 reconstruction handoff

Follow [AGENTS.md](../AGENTS.md) first. This file is the concise live
handoff; [GIANTS.md](GIANTS.md) keeps the complete-parent table, detailed
compiler investigations and rejected hypotheses. The user reports no other
active sessions. Continue in the registered `th075` repository and inspect
Git before every change.

## Live reconstruction state

Run this command for authoritative current counts:

    scripts/repo-python scripts/report-reconstruction-status.py --summary

The report includes pending-origin bytes in the conservative coverage
denominator. `config/function-origins.csv` is the live origin authority.

Target: the user-supplied Japanese TH075 v1.11 executable
`resources/th075.exe`, SHA-256
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.

## Exact Advance units

### Meiling object Advance is exact

`meiling-object-advance-005eb520` cold-replays 34,877 bytes with all 806
relocations. The in-progress animation path in action 997 restores EAX
at the first reload of action 998 and preserves the original stack,
rotation update and exits. Coverage increases by 34,434 authored bytes.
[Compiler evidence and replay command](GIANTS.md#meiling-now-cold-replays-exactly)

### Suika object Advance is exact

`suika-object-advance-005c9cc0` cold-replays 43,971 bytes with all 991
relocations. Explicit later frames of the startup stage in actions
918, 928 and 929 restore all three register joins. The replay adds
43,501 authored code bytes. [Whole-function controls and replay](GIANTS.md#2026-11-24--suikas-three-startup-joins-cold-replay-exactly)

### Sakuya object Advance is exact

`sakuya-object-advance-004ca6e0` cold-replays 42,933 bytes with all 929
relocations. Explicitly handling later startup frames in action 808
restores the original registers at the arena bounds check and adds
42,511 authored code bytes. [Comparison and replay](GIANTS.md#2026-11-24--sakuyas-arena-bounds-check-cold-replays-exactly)

### Patchouli object Advance is exact

`patchouli-object-advance-0050a580` cold-replays 82,106 bytes with all
1,449 relocations. The in-progress animation paths in actions `0x357`
and `0x3E5` restore the following action entries and add 81,539 authored
code bytes. [Comparison and replay](GIANTS.md#2026-11-24--patchoulis-object-advance-cold-replays-exactly)

### Yukari object Advance is exact

`yukari-object-advance-005a1600` cold-replays 44,107 bytes with all 943
relocations. The unfinished animation path in action 908 restores the
register choices across 909–917 and adds 43,599 authored code bytes.
[Comparison and replay](GIANTS.md#2026-11-24--yukaris-object-advance-cold-replays-exactly)

### Youmu object Advance is exact

`youmu-object-advance-00536400` cold-replays 40,466 bytes with all
938 relocations. The later-stage paths in 829 and 906 restore both
register joins. The typed history reader binds to the native list
front and the ledger credits 39,999 bytes.
[Comparison and replay](GIANTS.md#2026-11-24--youmus-object-advance-cold-replays-exactly)

### Yuyuko object Advance is exact

`yuyuko-object-advance-0057d580` cold-replays 44,327 bytes with all
1,043 relocations and credits 43,845 CODE bytes. The ongoing animation
paths in 837 and 903 and the stage-3 holds in 911 and 914 restore the
register choices and complete switch layout.
[Comparison and replay](GIANTS.md#2026-11-24--yuyukos-object-advance-cold-replays-exactly)

### Remilia fighter Advance is exact

`remilia-fighter-advance-00543210` cold-replays 59,237 bytes, including
all seven jump tables, three remap arrays and 1,863 relocations. The
stage paths in actions `0x58`, `0x5E`, `0x61` and `0x2F0` restore the
register joins. The ledger credits 58,294 CODE bytes.
[Comparison and replay](GIANTS.md#2026-11-24--remilias-fighter-advance-cold-replays-exactly)

### Youmu fighter Advance is exact

`youmu-fighter-advance-005214b0` cold-replays 47,656 bytes with all
seven jump tables, four remap arrays and 1,491 relocations. The
`0x58` continuation fixes the same entry join as Remilia, and the
`0x136` and `0x201` animation paths close the later register differences.
The ledger credits 46,755 CODE bytes.
[Comparison and replay](GIANTS.md#2026-11-24--youmus-fighter-advance-cold-replays-exactly)

### Marisa object Advance is exact

`marisa-object-advance-0049c8f0` cold-replays 47,099 bytes with all
1,021 relocations. The 75 independent actions and the default match
every dispatch offset. Actions 828–833 call the typed
`MarisaObject::UpdateTrackingNode`. The ledger credits 46,596 CODE bytes.
[Comparison and replay](GIANTS.md#2026-11-24--marisas-object-advance-cold-replays-exactly)

### Reimu object Advance is exact

`reimu-object-advance-00476a40` cold-replays 51,378 bytes with all
1,152 relocations. The dispatch separates 65 behavior-specific actions
from the shared animation handler. Action 997's in-progress path
restores the entry register in 998. The ledger credits 50,915 CODE bytes.
[Comparison and replay](GIANTS.md#2026-11-24--reimus-object-advance-cold-replays-exactly)

### Reimu fighter Advance is exact

`reimu-fighter-advance-0045dd70` cold-replays 62,089 bytes with six
jump tables, four remap arrays and all 1,824 relocations. The special
attacks in `0x258`–`0x25F` recover the original firing guards and
per-shot parameter writes. The ledger credits 60,999 CODE bytes.
[Comparison and replay](GIANTS.md#2026-11-24--reimus-fighter-advance-cold-replays-exactly)

### Sakuya fighter Advance is exact

`sakuya-fighter-advance-004ac040` cold-replays 83,922 bytes with all
six jump tables, four remap arrays and 2,352 relocations. The repeat-limit
paths in `0x1F8` through `0x1FA` restore the final register differences.
The ledger credits 82,796 CODE bytes.
[Comparison and replay](GIANTS.md#2026-11-24--sakuyas-fighter-advance-cold-replays-exactly)

### Yuyuko fighter Advance is exact

`yuyuko-fighter-advance-00564be0` cold-replays 62,746 bytes with seven
jump tables, five remaps and 1,438 relocations. The landing and launch
continuations close the register joins in `0x5E`, `0x5F` and `0x62`.
The three loop counters scoped to the countdown branches in `0x303`
restore the native stack slots. The ledger credits 61,872 CODE bytes.
[Comparison and replay](GIANTS.md#2026-11-24--yuyukos-fighter-advance-cold-replays-exactly)

### Marisa fighter Advance is exact

`marisa-fighter-advance-00486550` cold-replays 51,799 bytes with seven
jump tables, four remaps and 1,683 relocations. A single switch restores
the native dispatch and stack slots. The drift continuation in `0x208`
and the firing continuation in `0x2BF` close the final register joins.
The ledger credits 50,735 CODE bytes.
[Comparison and replay](GIANTS.md#2026-11-24--marisas-fighter-advance-cold-replays-exactly)

### Alice fighter Advance is exact

`alice-fighter-advance-004d7e70` cold-replays 44,570 bytes with seven
jump tables, four remaps and 1,427 relocations. The original stage-8
path in `0x5E` restores the entry state of `0x5F`. The ledger credits
43,601 CODE bytes.
[Comparison and replay](GIANTS.md#2026-11-24--alices-fighter-advance-cold-replays-exactly)

### Patchouli fighter Advance is exact

`patchouli-fighter-advance-004f7130` cold-replays 45,186 bytes with seven
jump tables, four remaps and 1,418 relocations. The landing continuation
in `0x5E`, the startup continuation in `0x2BC` and the repeat continuation
in `0x31B` restore the original register choices. The ledger credits
44,211 CODE bytes.
[Comparison and replay](GIANTS.md#2026-11-24--patchoulis-fighter-advance-cold-replays-exactly)

### Yukari fighter Advance is exact

`yukari-fighter-advance-0058af60` cold-replays 50,196 bytes with seven
jump tables, five remaps and 1,576 relocations. The explicit return
and stage-14 recovery path in `0x2DB` restore the exit and following
action entry. The ledger credits 49,230 CODE bytes.
[Comparison and replay](GIANTS.md#2026-11-24--yukaris-fighter-advance-cold-replays-exactly)

### Suika fighter Advance is exact

`suika-fighter-advance-005aeec0` cold-replays 72,683 bytes with the
original seven jump tables, four remaps and 2,120 relocations. Its four
calls to the flagged effect helper use the typed `SuikaFighter`
receiver. The ledger credits 71,616 CODE bytes.
[Comparison and replay](GIANTS.md#2026-11-24--suikas-fighter-advance-cold-replays-exactly)

### Meiling fighter Advance is exact

`meiling-fighter-advance-005d73c0` cold-replays 44,237 bytes with
seven tables, six remaps, and 1,377 relocations. The stage-1
continuation in `0x186` restores the following action entry. The
ledger credits 43,282 CODE bytes.
[Comparison and replay](GIANTS.md#2026-11-24--meilings-fighter-advance-cold-replays-exactly)

## Authored coverage and pending origin review

Coverage exceeds the 98% goal even with the pending origin candidates
in the denominator. The R304 texture entry lifetimes and R305 stage
base constructor await exact source adoption. Use the live report
for current counts and `config/function-origins.csv` for the remaining
provenance decisions.

R274 identifies the guarded extension cleanup at `0x004588B0` through
the game pattern parser, the original prefix lifetime calls, and the
same-receiver unwind entry. The new destructor cold-replays 43 bytes
and its scalar deallocation relocation. R275 identifies two RECT vector
cleanup leaves through the cold-exact vector assignment and its typed
call chain. R276 identifies the RECT const iterator increment through
the complete vector copy path and its exception sections. R277
identifies five VC7.1 list helpers through the typed Youmu history
writer, reset and member lifetime. R278 identifies the matching
value accessor through the object Advance's history read. R279
identifies seven archive list helpers through the concrete 108-byte
entry in the complete append and lookup functions and member lifetime.
R280 identifies six sprite history list helpers through the existing
164-byte sprite element and the complete typed append and render paths.
R282 identifies the D3DXVECTOR4 constructor through the exact quad
constructors and scaled draw. R283 identifies five texture vector
helpers through the concrete slot and interface pointer types. R284
identifies five pattern and effect vector cleanup helpers through
the complete typed loader and sequence lifetime calls. R285
cold-matches the empty sound and staff-roll hooks and the progress
destructor through their respective live receivers and startup lifetime.
R286 identifies the sound buffer vector clear and the replay header
and script sequence deque destruction helpers. R287 cold-matches
two setters through the existing sprite and text rendering layouts.

R288 lists the current unresolved addresses and their missing
evidence. The remaining short lifetimes and math workers retain
complete byte-equal alternatives. The publisher's Japanese 1.11 patch
contains the pinned executable and game data already present in the
supplied archive. The PE's RSDS record remains the only original debug
record found in either package.
[Remaining origin evidence](ORIGIN_PENDING_REVIEW.md#r288--remaining-origin-evidence)
[Publisher patch check](ORIGIN_PENDING_REVIEW.md#r300--publisher-patch-reproduces-the-pinned-executable)

R305 identifies the stage base constructor through the complete BG00a
code interval and both adjacent vtables. For the scene, precompiling
the destructor moves it along with the deleting wrapper. The original
places those two functions on opposite sides of the authored methods.
[Precompiled constructor controls](ORIGIN_PENDING_REVIEW.md#r305--stage-base-constructor-follows-the-deleting-destructors)

R303 reproduces the full banner interval with the genuine `log10f`
definition deferred past the progress accessors and with a late
ordinary wrapper. Both link at the native offset.
[Banner link controls](ORIGIN_PENDING_REVIEW.md#r303--standard-log10f-can-occupy-the-native-banner-slot)

R294 identifies `0x00641FB8` as the inferred CRT `labs` contribution
from the native request order and the full 1,140-byte linked interval.
The outer wrapper remains unresolved.
[CRT request order](ORIGIN_PENDING_REVIEW.md#r294--crt-absolute-value-archive-request-order)

R290 uses the original C++
startup table to distinguish the event service pulse at
`0x00423B20`, which cold-replays all 26 bytes and both relocations.
R292 identifies four inner float workers as VC7.1 header code
through the original retention of unreferenced D3DX8 COMDATs and
the absence of the four competing SDK bodies.
[Worker selection evidence](ORIGIN_PENDING_REVIEW.md#r292--vc71-float-worker-selection)
R293 identifies the sprite quad's `D3DXMATRIX` constructor at
`0x0040D9F0` through four full SDK code windows. The ordinary
payload adds three bytes in the original sprite interval.
[Matrix selection evidence](ORIGIN_PENDING_REVIEW.md#r293--sprite-matrix-constructor-selection)

R304 identifies the two texture entry lifetime definitions through the
complete allocation and drawing interval. The implicit declarations
move both leaves ahead of the second allocator.
[Texture lifetime order](ORIGIN_PENDING_REVIEW.md#r304--texture-entry-lifetime-definitions-follow-the-drawing-methods)

R296 distinguishes the implicit copy at
`0x004229D0` by its position in the complete linked script deque
window.
[Copy emission evidence](ORIGIN_PENDING_REVIEW.md#r296--script-sequence-copy-emission-order)
R297 uses the ordered 688-byte vector window to identify the implicit
frame copy at `0x004591E0`.
[Frame emission evidence](ORIGIN_PENDING_REVIEW.md#r297--fighter-frame-copy-emission-order)

R272 and R273 attribute the
R265 SDK lifetime cohort through complete original D3DX8 archive sections,
typed caller references, and unmasked target comparisons.
[Evidence and replay](ORIGIN_PENDING_REVIEW.md#current-follow-up)

## Recent source checkpoints

Inspect `git log -10 --oneline` for the checkpoint sequence. Use the
requested `gpt-6.2-sol: ...` prefix for new commits.

A 2026-11-20 leaf pass recovered the 0x74-byte `FighterFrameInfo` layout and
its memberwise assignment at 0045AAE0 as natural C++. The hurt/hit members
are direct `std::vector<RECT>` fields; collision dispatch now emits the native
VC7.1 `vector::size()` / `vector::at()` symbols at 004452D0 / 00445310.
The 368-byte frame assignment and 381-byte vector assignment replay exactly
with 2/2 and 17/17 relocations. The affected collision dispatch, frame
dependency and Actor helper objects replayed 13/13 exact units after the
shared-layout change (15/15 including the two assignment units). The compiler
and STL functions retain their compiler/library origin classifications and
do not increase authored exact coverage.

## Next-agent working loop

1. Read `AGENTS.md`, this handoff, the relevant section of `GIANTS.md`, and
   the complete source/target context for the selected parent.
2. Measure the whole function with `scripts/repo-python
   scripts/measure-giant.py ADDRESS`; use Ghidra through
   `scripts/repo-python scripts/ghidra.py` and the existing headless runtime.
3. Work on complete boss control flow and natural C++ types/expressions.
   Do not substitute ASM, padding, inert statements, byte arrays, fake ABI
   declarations or source splits for reconstruction.
4. Build and compare only the selected parent. Run
   `scripts/repo-python scripts/check-frontier.py FRONTIER_NAME` after a
   substantive parent change; update its ratchet only when the improvement
   has been reviewed.
5. Cold-replay only newly accepted or affected exact units, including shared
   header consumers when relevant. Never run the full cold replay merely for
   a handoff or progress check.
6. Commit each substantive checkpoint promptly with `gpt-6.2-sol: ...`; make
   multiple coherent commits during a productive session rather than stopping
   after the first one.

Useful commands:

    git status --short --branch
    scripts/repo-python scripts/verify-target.py
    scripts/repo-python scripts/validate-tracking.py --require-target
    scripts/repo-python scripts/report-reconstruction-status.py --summary
    scripts/repo-python scripts/measure-giant.py ADDRESS
    scripts/repo-python scripts/check-frontier.py FRONTIER_NAME
    scripts/repo-python scripts/replay-exact-units.py --unit UNIT_NAME

For documentation-only changes, `git diff --check` is sufficient. Do not run
full CI or full cold replay without a demonstrated need.

## Storage handoff

The 202 MB generated `build/` tree has been cleared; the directory remains and
repository scripts recreate its outputs. Rejected Yuyuko/Suika trial sources,
completed replay scratch, superseded match-unit snapshots, one duplicate
native-target JSON and Python bytecode cache were removed, saving about
218 MB. The 134 MB `.analysis/` tree was retained because it contains active
whole-function, original-PE, Ghidra and layout research. Preserve it rather
than deleting it wholesale. Also preserve `.tools/`, `ghidra-project/`, the
original executable and tracked resources. See
[STORAGE_HYGIENE.md](STORAGE_HYGIENE.md) before further cleanup.


A focused Fighter leaf pass also recovered the unreferenced 24-byte method at
00454C00 as `Fighter::ClearField47CAt00454C00`. Its complete body is the
natural member operation `field47C = 0`, cold-replayed byte-for-byte with no
relocations. The address-anchored name deliberately avoids claiming a stronger
semantic role because Ghidra reports no static xrefs; the neighboring
00454BC0 setter and +0x480 sequence receiver provide the bounded Fighter
context.


R281 identifies `0x00454F70` through the Actor frame pointer and the
same flag test in the exact Meiling action dispatcher. The predicate
cold-replays all 31 bytes and has no relocations. Its source takes the
observed ECX receiver, and the original declaration remains unknown.


A new natural-C++ source alternative is retained for the unresolved lifetime
leaf at `004170B0` in `probes/UnknownOwnerReleaseAt004170B0.cpp`. A one-pointer
owner whose destructor invokes the third `__stdcall` virtual slot of its
resource interface cold-compiles to all 27 original bytes. A probe-only `delete`
expression also emits the 44-byte scalar-deleting COMDAT at `0041A140`: every
nonrelocation byte matches, and its two REL32 fields resolve to `004170B0` and
`00640F15`. This narrows the source shape but does not identify the original
owner or interface; the existing explicit-interface-destructor alternative
remains byte-equivalent. Both functions therefore retain their prior origin and
exactness dispositions.


Yukari object `005A1600` action `900` remains at its committed baseline. A
speculative stage-2 proximity gate was rejected after checking the original
case-900 decompile and target code: that action has no 100-unit distance test
or `0045B850(8)` transition. Do not reintroduce that trial without new target
evidence; the Yukari object remains a separate partial reconstruction.

### Latest Yuyuko source follow-up

Action 0x192 restores its original 50-unit facing-dependent X offset for
effect 800. Action 0x2E4 retains separate stage-7 and stage-8 0x388 emissions.
Facing-based X offsets now preserve signed-char integer multiplication
before conversion to float. The current VC7.1 body is 62,271 bytes versus the
61,872-byte target (+399), with 51,948 direct non-relocation byte differences
and a 0x2B8 frame. Relative to the prior double-contact-scale checkpoint
(62,254 bytes, 51,620 direct differences, 0x2B0 frame), these source-level
semantic corrections add 17 body bytes, 328 direct differences and 8 frame
bytes; this is not a whole-function exactness claim. Fifteen targeted
animation, movement, range, reset, battle/aux-effect, sound, gauge, camera
and word-helper leaf units replay 15/15 exact. A natural-C++ seven-range/
switch dispatch rewrite was compiled but not retained because VC7.1 created
per-switch temporary slots and a larger frame than the current flat-switch
baseline.
