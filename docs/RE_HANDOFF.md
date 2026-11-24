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

### Yuyuko fighter Advance partial reconstruction

`0x00564BE0` (61,872 original CODE bytes) now has a natural C++ partial
parent in `probes/YuyukoFighterAdvancePartial.cpp`, declared as
`YuyukoFighter::Advance` in `src/YuyukoFighter.hpp`. The current 62,043-byte
VC7.1 body covers actions `0..10`, the observed `0x32..0x41` cases,
`0x46..0x4A`, `0x4C`, `0x58..0x59`, `0x5D..0x63`, `0x12C..0x136`
special-move phases, `0x186..0x18B`, `0x191..0x192`, `0x194`, `0x196..0x198`,
`0x19A`, `0x19C`, `0x19E`, `0x1A0`, `0x1F4..0x1F5`, `0x252..0x256`, `599`,
`600`, `0x259..0x25A`, `0x25F..0x265`, action `700`, `0x2BD..0x2C3`,
`0x2DA`, `0x2DB`, `0x2E4`, `0x2EE..0x2EF`, `0x2F8..0x2F9`,
`0x302..0x303`, `0x31B..0x31C`, `0x8F..0x90`, `0x96..0x98`,
`0x9A..0x9E`, `0x9F..0xA1`, `0xA3..0xA5`, `0xA7..0xA8`, `0xB4..0xB5`,
actions `0x91`, `200`, `0xC9..0xD0`, `400`, and `0x8C`: horizontal drift,
bounce/landing
transitions, projected velocity, direction-sensitive recovery, input-driven
follow-ups, repeated barrage and resource/effect bursts, hit-stop/counter
resets, and the shared animation advance path. Action `0x2F9` now contains only
its original repeat-level `0x38C` radial and `0x38D` random-position burst
patterns; a copied `0x394..0x396` fan volley and its countdown reset were removed
because those belong exclusively to action `0x303`. The `0x303` fan keeps its
three independent countdown branches and paired 20-shot loops, while reusing
three C++ loop counters in the same pairs as the original `local_80`,
`local_84`, and `local_88` lifetimes.
Action 0x192 now restores its original 50-unit facing-dependent X offset for
effect 800; action 0x2E4 keeps separate stage-7 and stage-8 0x388 emissions.
All 39 original signed-char facing products are accounted for: 38 reuse
one natural C++ integer scratch, while action 0x18A retains its direct
integer-promotion 0x97 product because that form emits the target instruction
sequence. Action 0x91 now retains its two float-to-short velocity projections:
the apparent calls to 0x006406AC are VC7.1 __ftol2 conversions, not random
number calls. Its ground-contact path clears motion, resets primary counters
to 0x61, applies camera shake and emits no extra shared sound; the shared-sound
call inventory now matches the original exactly. Fifteen targeted animation,
movement, range, reset, battle/aux-effect,
sound, gauge, camera and word-helper leaf units replay 15/15 exact. The source
uses one flat natural-C++ switch; VC7.1 already lowers it into the target's
seven-range dispatch tree and six singleton-boundary checks. An explicit
seven-switch source rewrite was tested but not retained: it compiled to
62,204 bytes (+332), 52,560 direct differences and a 0x240 frame, all worse
than the flat-switch candidate.

All 125 original switch case labels across the seven ranges have explicit
natural-C++ handlers, along with the six singleton boundaries `0x32`, `0x8C`,
`0x12C`, `0x186`, `0x1F4` and `0x2BC` (131 distinct action values total). The
original x87 inclusive ground-contact edge is preserved in the audited `0x91`,
`0x9E`, `0xB4..0xB5`, `0xC9..0xCE` and `0xD0` actions. Actions `0x60` and
`0x61` now have separate natural-C++ bodies, retaining their distinct original
input-test grouping, effect burst, landing transition and velocity follow-up.
Actions `0x8F` and `0x90` are also separate handlers rather than one shared
branch, matching the original per-action dispatch layout. One decompiler label
needs care: `Concurrency::details::ContextBase::ClearCancel` at the Yuyuko
fighter actions `0`, `2`, `0x5D`, and `0x5E` resolves in target machine code to
`0x00453E20`, the exact `Fighter::ClearMotionFields` leaf. The existing C++
call is correct; do not invent a separate `ClearCancel` helper from that label.
The 5D/5E duplicated-body experiment grew the object by 357 bytes without
improving the direct byte comparison, so the shared source arm remains.
The horizontal
gauge-drift actions `0x96..0x98`, `0x9F..0xA1`, and `0x9A..0x9C` now retain
separate handlers with their original per-action velocities and counter targets.
Actions `0xA3..0xA5`, `0xA7..0xA8`, and `0xB4..0xB5` are now separate
handlers as well, retaining their per-action launch velocities and reset paths.
Actions `0x252`, `0x253`, and `0x254` are also separate; only `0x252/0x253`
perform the spirit-recovery check, matching the original action-specific flow.
Effect actions `0x259`, `0x25A`, `0x25F`, `0x260`, `0x261`, and `0x262` now
retain separate handlers and their original per-action effect/timer constants;
`0x25A` also restores the target sound-before-gauge call order. Three direct
boundary actions that were absent from the source now have explicit handlers:
`0x12C` (conditional motion clear, horizontal decay, effect `0x34C` and shared
sound `0x1C`), `0x186` (initial horizontal launch, decay and effect `0x334`),
and `0x1F4` (the timed `0x343` trail, auxiliary `0x7F` effect and its staged
counter/sound transitions). The fourth direct boundary, `0x2BC`, was already
implemented as decimal `case 700`, including its 48-effect stage burst; no
duplicate case was added. The source now reproduces the target dispatch's
singleton boundaries at `0x12C`, `0x186`, `0x1F4` and `0x2BC`. Their eight
shared animation, motion-clear, battle/aux-effect and sound leaf units replay
8/8 exact across three objects. The separate 37-byte `Fighter::SetNonnegativeWord`
leaf used by action `700` / `0x2BC` also replays 1/1 exact. Action `0x19E`
now restores its missing stage-3 barrage: `PlaySound(0)`, captures both velocity
components through the original `0x657888` projection, starts the 300-frame
gauge timer, emits five angles (`10 + 15*i`) with three layers (`0x320`, `0x321`,
`0x322`) at `field318` values 2/6/10, then restores the saved velocity using
`0x658044`. This replaces the incorrect `PlaySharedSound(0x1D)` placeholder.
The affected animation, counter, motion-clear, timer, battle-effect and sound
leaves replayed 7/7 exact. Low actions `1` and `3` retain separate handlers and
their distinct primary-counter destinations (`2` and `0`). Low actions `6..9` retain their
separate command gates, gravity/contact branches, per-action stage velocities
and original secondary-counter behavior;
the remaining common/default path and code-generation differences are still
under investigation, so this is not a whole-function exactness claim.
The latest shared-scratch VC7.1 body is 62,043 bytes versus the 61,872-byte
target (+171), with 51,920 direct non-relocation byte differences and a
0x224 stack frame. Reusing one integer scratch across 38 facing products
reduced the previous 62,271-byte body by 211 bytes; removing action 0x91's
unsupported shared-sound call then reduced it by another 17 bytes and brought
direct differences down by another 17, with the frame unchanged. The prior
corrections remain: removing the misplaced action-303 volley restored its
three original loop-counter lifetimes, and preserving the target's double
contact-scale multiply at all 27 call sites removed 27 conversion temporaries.
Fifteen targeted animation, movement, range, reset, battle/aux-effect, sound,
gauge, camera and word-helper leaf units replay 15/15 exact; the five directly
affected animation/reset/motion/camera leaves replayed 5/5 after the 0x91 fix.
The whole-function layout remains non-exact and needs further code-generation
work.

After adding the virtual slot declaration, the 13 exact Yuyuko header
consumer units were cold-replayed individually: 13/13 exact across 11
objects. The complete Yuyuko object `Advance` parent still builds with its
existing 1,697-byte frontier and no regression. Continue from the remaining
Yuyuko move cases in `.analysis/yuyuko-fighter-decompile.c`; do not replace
the partial body with decompiler text or count its partial extent as a
complete function.

## Remaining giant parents

The remaining functions have partial or unstarted parents.

- Object: Marisa `0049C8F0` (46,596 bytes).
- Fighters: Marisa `00486550` (50,735 bytes), Alice `004D7E70`
  (43,601 bytes), Patchouli `004F7130` (44,211 bytes), Yuyuko `00564BE0`
  (61,872 bytes), Yukari `0058AF60` (49,230 bytes), Suika `005AEEC0`
  (71,616 bytes), Meiling `005D73C0` (43,282 bytes).

`docs/GIANTS.md` records the full sources, original extents and
previous experiments.

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


An additional orphaned Actor-state leaf at 00454F70 now has a natural C++
source candidate (`src/ActorFrameFlagPredicate454F70.cpp`). The pinned VC7.1
probe reproduces all 31 bytes with no relocations: an ECX Actor pointer reaches
`frameInfo->flags` and returns whether bit 0x20 is set. Ghidra reports no static
callers, so the original owner, semantic role and authored/compiler origin
remain unknown. It is deliberately left unclassified and receives no exact
match credit.


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


The orphaned 40-byte setter at `004135F0` now has a second natural-C++
alternative in `probes/UnknownParameterStoreAt004135F0.cpp`. Its pinned VC7.1
probe matches all 40 original bytes with zero relocations: one byte is stored
at receiver +0x24 and two raw DWORD arguments at +0x1C/+0x20. The receiver's
preceding 0x1C bytes are deliberately untyped; the evidence's FontSurface
context does not yet prove the owner or whether the DWORDs are floats or raw
integer bit patterns. It remains unclassified and receives no exact credit.


The 16-byte getter at `004124B0` now has a natural C++ pointer-holder
alternative in `probes/UnknownPointerHolderGetterAt004124B0.cpp`. It cold-compiles
byte-for-byte with zero relocations. Its two callers (`00411EA0` and `00411F20`)
are container/proxy-management paths, including a call to the VC7
`allocator<std::_Container_proxy>::destroy`; this narrows the context but does
not prove the original receiver type or STL/game ownership boundary. It remains
unclassified and receives no exact credit.


Marisa fighter `Advance` (`00486550`) now retains its 158 recovered action
bodies in the original six inclusive action bands instead of one flat switch.
The low `0x00..0x0A` switch, the `0x32` branch, and the five boundary actions
`0x8C`, `0x12C`, `0x186`, `0x1F4`, and `0x2C2` are separated; the normal
high-range cases share the original nested-frame fallback. Range-crossing case
includes were split into ordinary C++ source units so each switch covers only
its native range. The pinned VC7.1 probe compiles and tracking validation passes;
this is a control-flow/source-organization advance, not an exact-byte claim.
The large function still needs stack-frame, register-allocation and byte-level
work. No full cold replay was run.


The random-offset effect paths now reuse `actionSnapshot` as the shared integer
scratch after the `switch` has already selected its case. This mirrors the
original decompiler's reuse of `iVar5`, avoids introducing extra floating-point
locals, and keeps the Y random draw before the X random draw. The change remains
a natural C++ candidate and is validated by the targeted VC7.1 probe only.


The low Marisa actions `0x04` and `0x05` now branch to one shared
`advanceNestedAndReturn` C++ tail rather than emitting duplicate calls. The
pinned VC7.1 candidate places that tail at `00492B2E`; its body is the same
three-instruction shape as the original `00492B73` tail (load `this`, call
`Actor::AdvanceNestedFrame`, return). Their two handler bodies now end in a
jump to that shared tail, matching the original control-flow sharing. The
remaining stack-base offset and call-relocation differences are still open.


The low Marisa dispatch now lays out the `0x32` special edge as the positive
`JE` arm, with the ordinary `0x00..0x0A` switch on the fallthrough path. This
replaces the previous `JNE` plus unconditional jump sequence and matches the
original branch polarity at `00486597`. The source-coverage verifier now counts
natural `goto` edges to the out-of-line boundary bodies, so action `0x32` stays
covered without a fake switch case. The current candidate still has a different
local layout (`this` at `EBP-0x1C`, action at `EBP-4`, plus a switch temporary at
`EBP-0x20`); the original uses `this` at `EBP-0x18` and one action local at
`EBP-0x1C`. No exact-byte claim is made.


The late card-tail case order was checked against the original handler-address
map rather than inferred from numeric action IDs. The original PE emits
`0x2BC`, `0x2BD`, `0x2BF`, `0x2C0`, then `0x2C1` (addresses `0048FA35`,
`0048FC34`, `0048FD1C`, `004901AA`, `004904C0`). An intermediate reorder that
moved `0x2C1` ahead of `0x2BF`/`0x2C0` was therefore reversed. The source order
now follows the verified PE handler layout; the focused VC7.1 build and the
158-action coverage check pass.


The Marisa source-coverage verifier now also enforces the `0x2BC..0x2C1` card
tail's source order against the original PE handler addresses. This catches a
case reorder that preserves action coverage but changes emitted handler layout.
The validator reports the source/PE order separately from its 158-action
coverage result.


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
