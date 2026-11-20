# TH075 handoff (2026-11-20)

Follow [AGENTS.md](../AGENTS.md) first. This file is the concise live
handoff; [GIANTS.md](GIANTS.md) keeps the complete-parent table, detailed
compiler investigations and rejected hypotheses. The user reports no other
active sessions. Continue in the registered `th075` repository and inspect
Git before every change.

## Live reconstruction state

Run this command for authoritative current counts:

    scripts/repo-python scripts/report-reconstruction-status.py --summary

Snapshot checked on 2026-11-20:

- 4,351 candidate functions: 1,008 authored, 90 origin-review candidates,
  and 3,253 excluded.
- 988 accepted exact functions cover 933,442 authored CODE bytes.
- The authored denominator is 1,973,772 bytes: 47.29% exact, or 47.21%
  conservative when the 3,315 pending-origin bytes are included.
- 20 authored functions remain, totaling 1,040,330 CODE bytes. All are
  slot-1 `Advance` methods: 11 fighter vtables and nine character-object
  vtables.
- Thirteen whole-function parents are available: 11 remain nonexact and
  two object parents are already exact (Alice `004EBDA0`, Remilia
  `0055AC80`). Nine remaining functions do not yet have a complete parent.
- The 98% authored-byte goal is not met.

`config/function-origins.csv` is the live origin authority. The 97-row /
3,608-byte R263 review matrix is historical; the live queue is 90 candidates /
3,315 bytes. Do not use the historical count as the current backlog.

The reconstruction baseline before this documentation pass was
`43a36a53` (`gpt-web: align Yuyuko object case dispatch`); the worktree was
clean and `main` matched `origin/main`. Recheck `git status --short --branch`
and `git log` before editing.

Target: the user-supplied Japanese TH075 v1.11 executable
`resources/th075.exe`, SHA-256
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.

## Recently remeasured object frontiers

These four complete object parents were measured against the current source
on 2026-11-20. `section` is the rebuilt COFF function size; the original CODE
extent is the comparison target.

| Character | Address | Original CODE | COFF section | Mnemonic differences | Width differences | GPR differences | First GPR difference |
| --- | ---: | ---: | ---: | ---: | ---: | ---: | --- |
| Meiling | `005EB520` | 34,434 | 34,879 | 0 | 6 | 135 | `005F3904` (#9200) |
| Yuyuko | `0057D580` | 43,845 | 44,327 | 23 | 28 | 897 | `00583489` (#6565) |
| Yukari | `005A1600` | 43,599 | 44,104 | 0 | 11 | 613 | `005A88A8` (#7965) |
| Suika | `005C9CC0` | 43,501 | 43,972 | 0 | 1 | 935 | `005D2558` (#9213) |

The complete set of 11 nonexact parents and their compiler flags is in
`config/frontiers.toml`. The other parent measurements are summarized in
[GIANTS.md](GIANTS.md). A passing `check-frontier.py` is a nonregression
result, not whole-function exactness.

### Latest Yuyuko improvement

In `probes/CharacterObjectActions0057D580F1237.cpp`, state 838's condition
now evaluates the `animationStage == 0` / owner-action 611–613 arm before the
independent `field080` / owner-action exclusions. The expression is
Boolean-equivalent to the previous one; it only reorders plain field reads
and lets VC7.1 choose a different natural register layout. No assembly,
padding or machine-code literals were added.

- The COFF section shrank from 44,331 to 44,327 bytes.
- The frontier fell from 17,739 to 1,697 differing bytes: 16,120 formerly
  differing bytes now match, with 78 previously matching offsets displaced.
- All 198 switch-table entries for actions 800–997 now point to the same
  relative state-entry offsets as the original.
- The current instruction diagnostic is 23 mnemonic, 28 width and 897 GPR
  differences; the first GPR mismatch is `00583489` (#6565).

This is substantial progress in a complete boss function, not an exactness
claim. The next useful Yuyuko investigation starts at `00583489`; inspect the
surrounding state-837/838 join and original control flow rather than assuming
the first mismatch lies inside the state-838 entry itself.

### Yuyuko fighter Advance partial reconstruction

`0x00564BE0` (61,872 original CODE bytes) now has a natural C++ partial
parent in `probes/YuyukoFighterAdvancePartial.cpp`, declared as
`YuyukoFighter::Advance` in `src/YuyukoFighter.hpp`. The current 26,266-byte
VC7.1 body covers actions `0..10`, the observed `0x32..0x41` cases,
`0x46..0x4A`, `0x4C`, `0x58..0x59`, `0x5D..0x63`, selected `0x12D..0x136`
special-move phases, `0x187..0x18B`, `0x191..0x192`, `0x194`, `0x196..0x198`,
`0x19A`, `0x19C`, `0x19E`, `0x1A0`, `0x1F5`, `0x252..0x256`, `599`,
`600`, `0x259..0x25A`, `0x25F..0x265`, action `700`, `0x2BD..0x2C0`,
and `0x8C`: horizontal drift,
bounce/landing
transitions, projected velocity, direction-sensitive recovery, input-driven
follow-ups, repeated barrage and resource/effect bursts, hit-stop/counter
resets, and the shared animation advance path. Unimplemented action families
still use the observed common default transition only as a research fallback;
this is not a complete parent and receives no whole-function exactness credit.
The structural comparison is expected to report a size mismatch (26,266 vs.
61,872 bytes).

After adding the virtual slot declaration, the 13 exact Yuyuko header
consumer units were cold-replayed individually: 13/13 exact across 11
objects. The complete Yuyuko object `Advance` parent still builds with its
existing 1,697-byte frontier and no regression. Continue from the remaining
Yuyuko move cases in `.analysis/yuyuko-fighter-decompile.c`; do not replace
the partial body with decompiler text or count its partial extent as a
complete function.

## Remaining giant parents

The 11 complete but nonexact parents are:

- Fighters: Reimu `0045DD70`, Sakuya `004AC040`, Youmu `005214B0`,
  Remilia `00543210`.
- Objects: Sakuya `004CA6E0`, Patchouli `0050A580`, Youmu `00536400`,
  Yuyuko `0057D580`, Yukari `005A1600`, Suika `005C9CC0`, Meiling
  `005EB520`.

The nine remaining functions without a complete parent are:

- Objects: Reimu `00476A40` (50,915 bytes), Marisa `0049C8F0`
  (46,596 bytes).
- Fighters: Marisa `00486550` (50,735 bytes), Alice `004D7E70`
  (43,601 bytes), Patchouli `004F7130` (44,211 bytes), Yuyuko `00564BE0`
  (61,872 bytes), Yukari `0058AF60` (49,230 bytes), Suika `005AEEC0`
  (71,616 bytes), Meiling `005D73C0` (43,282 bytes).

`docs/GIANTS.md` records the full sources, original extents, previous
experiments and useful negative results. In particular, do not repeat the
22 already-tried Meiling 997/998 source variants at `005F3904` or the
rejected Sakuya 809/810 variants without new target evidence.

## Recent source checkpoints

The latest commit improves Yuyuko's complete object `Advance` parent. The
preceding checkpoints also replace raw Fighter/NameEntry offset access with
shared typed members for result state, command bytes, snapshot score/health,
result and staff-roll score reads, and the NameEntry texture/state prefix.
Inspect `git log -10 --oneline` for the exact checkpoint sequence; each uses
the requested `gpt-web: ...` prefix.

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
6. Commit each substantive checkpoint promptly with `gpt-web: ...`; make
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
