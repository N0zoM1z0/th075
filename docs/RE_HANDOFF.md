# TH075 function reconstruction handoff

Updated 2026-10-25 for resumed reconstruction, F151.
**The 98% authored-byte objective is active and incomplete.**
The user resumed after the cleanup and handoff checkpoint. Subsequent project
phases remain deferred. Continue the complete function cohort below.

## Verified reconstruction state

| Measure | Value |
| --- | --- |
| Provisional candidates | 4,351 |
| Reviewed authored / library / compiler | 1,002 / 2,671 / 581 |
| Unknown origins | 97 / 3,608 code bytes |
| Source-present / exact functions / exact units | 331 / 331 / 331 |
| Exact code bytes | 716,968 |
| Reviewed authored coverage | 716,968 / 1,973,516 (36.33%) |
| Conservative coverage, including pending bytes | 716,968 / 1,977,124 (36.26%) |
| Canonical objects / accepted source-header inputs | 135 / 209 |

The ledgers and status script are authoritative. The adoption manifest retains
F009 plus 271 additions / 707,085 code bytes / 209 inputs. Origin evidence through
R268 is intact. Every pending code byte remains in the conservative denominator.
CODE `size` determines credit; full `compare_size` also includes owned tables.

Only use the supplied Japanese th075.exe 1.11, SHA-256
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
Identity is pinned to the user's archive, without independent official
provenance corroboration. Never substitute th075c.exe or patch target bytes.

The preceding pushed reconstruction checkpoint is **c2efd6a (F150)**.
The last new exact unit was F146's 51-byte `fighter-motion-clear-00453e20`,
source `src/FighterMotionClear453E20.cpp`, cold51/51 with zero differences.
F147/F148/F150/F151 added incomplete private source, not exact bytes.

## Continue after F151: complete 004AC040

The authoritative private source is **`.analysis/character-move-4ac040/f151/`**.
There are **131/151 nondefault entry fragments**, covering 59,992 contiguous
native investigation bytes 004AC1B9..004BAC10. **20 entries remain**. These
fragments are uncompiled/unaccepted and earn no source-presence/exact credit.

1. Read `native-cohort-proof.json`, `source-transcription-audit.json`,
   `receiver-vtable-proof.json` and `command-selection-native-contract.json`.
2. Copy current inputs to a fresh F152 working directory before editing:
   `Case*.inc`, `Prefix.inc`, `Tail.inc`, `SourceDependencies.inc`, both private
   receiver headers and the full native map. Preserve F148, F150 and F151 unchanged.
   F149 remains the cleanup/handoff receipt identifier.
3. Continue **state 700, 004BAC11..004BAF03**, 755 bytes/199 instructions.
   Following mapped entries are 701,702,703,704,705,706,707,731,741,742...;
   consult the full map rather than assuming numerical adjacency or combining
   labels.
4. Complete all 151 entries, real default/shared paths, ABI, profile and actual
   relocations before compiling a complete source or configuring acceptance.
   Never compile a partial wrapper or accept a case/chunk.

Required comparison remains **83,922 bytes**:82,796 code plus 1,126 owned
switch/remap bytes. Four remapped/two direct guards, five equality states,
ten contiguous owned data segments and 1,933 internal branches are checked.
Code ends 004C03AC; the full owned extent ends 004C0812 exclusive. Preserve
actual default 004C037D, common tail 004C039F, epilogue 004C03A7 and sole RET 004C03AB.
Frame 0x720, saved ESI and ECX at EBP-0x64 are observations: recover genuine locals
and nested packets without artificial storage.

The source audit checks 131 entry hashes, call evaluation order and real exits.
All new named calls use canonical accepted units, including recorded random
range 00455580; seven older calls retain the unaccepted R213 declaration.
Eighteen float-to-short conversions and fifteen real loop counters remain.
This audit does not establish emitted CFG/bytes. There are 926 canonical named
call sites and seven calls to the unaccepted command declaration.
F148 inputs/evidence remain frozen by their original checkpoint. Current
inputs/evidence are frozen by `.analysis/f151-source-checkpoint.json`.
F151 adds 27 entries/24,106 native investigation bytes. The new scalar audit
checks direct float/integer constant-store width, value and order for these
27 entries; calculated expressions/conditions and emitted bytes remain outside
that audit. Keep both 36-site rings in 603/605 explicit and the four real loops
in 607..610. In 607/608 the post-loop F00/F02-to-motion writes precede the
F00 reset/F02 increment. See the knowledge index for additional native details.
Nested random arguments remain audited in native right-to-left evaluation
order; lexical call order alone is insufficient.

## Native contracts and details to retain

- Constructor 004C0820 installs 006594A8 through the actual receiver at 004C0832.
  The used prefix is slot 0=00453D80,slot 1=004AC040. Whole R050/R068 bodies and
  four character slot 1 calls in already-exact 859-byte BattleFrame::UpdateFrame
  support it. The separate draw-dispatcher slot 1 call is excluded. Original
  identifiers/full layouts remain unknown; never instantiate/embed partial owners.
- State 96 uses ordered <=0 landing, state 97 ordered <0. State 89 uses 40.0f
  for field 30,0.0025f horizontal and 0.01f vertical restoration, with integer
  negation before conversion. Keep pre/post-advance reads, strict crossings,
  short-circuit branches, effect argument order and repeated phase guards.
- R213 wrapper 454BC0 is 61 bytes: DWORD selection/low-byte mode/DWORD mask,
  pointer 480 receiver and RET12. Its 22-byte setters 410FA0/410FE0 use RET4 and
  byte at +0x10 / DWORD at +0x14 stores. All three are already authored (R213/R239), unaccepted.
  Old functions.csv notes calling the setters unknown are historical. Do not
  change any current unknown origin on that basis.
- F149 only read states 390..402; no new source was written. State392's actual
  phase 6/tick 0 guard encloses a phase 4/tick 0 sound guard at004B204D..004B2069.
  Preserve those nested tests rather than removing instructions as unreachable;
  original intent is unknown. States 400..402 contain three explicit spawn
  sites and signed-short timers; do not substitute a synthesized runtime loop.

## Preserve the earlier full 0050A580 draft

All 92 entries exist, but the entire function remains unaccepted: 81,539 code
and 82,106 required comparison bytes. Current source SHA-256:
`80ca174bef3d407ec40f159f292765ecb5fd5deb85808f4d17fcf96b364215b0`.
Its whole diagnostic remains 82,109 emitted bytes / 26,719 differences, 522 GPR
differences and 1,449 actual fields. All 801 authored/helper calls use accepted
symbols; 20 CRT and 25 unknown-origin calls remain explicit.

Keep `build/probes/F145CanonicalViews.obj` and older active
`F142WordWindow.obj`, `F139VirtualMain.obj`, `F138CallViews.obj`,
`F136RecordView.obj`, `F134CompleteFinal.obj`. Preserve all 91 older drafts and
F131..F148 evidence. F146 closed width/copy/937-token, /Ob1, visible-callee
and 18-qualifier controls without a supported fix; do not repeat without new
evidence. Older F021/F048/F061/F066/F085 drafts/details remain in history.

## Tools and final checks

Read [AGENTS.md](../AGENTS.md), [workflow](RE_WORKFLOW.md) and
[knowledge index](KNOWLEDGE_BASE.md). Run the four preflight commands in
AGENTS.md. Use `scripts/repo-python` for every repository Python command.
Cold-replay only new/affected whole units with `replay-exact-units.py --unit NAME`.

Everything stays **headless**. Unset DISPLAY/WAYLAND_DISPLAY for Wine/debuggers;
disable graphical drivers per process, for example
`WINEDLLOVERRIDES='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'`.
Use native32 Wine/batch GDB and the existing attested headless Ghidra wrapper,
not REA/interactive WineDbg. Keep compilers serial, bound debugger runs, monitor
RAM/CPU and preserve shared tools/private service settings. Never print/commit
the private service URL. Commit subjects: `gpt-6.1-sol: ...`; commits/pushes
remain authorized.

No fake returns/ABI, inert locals, padding, assembly/target arrays, conditional
game bodies, masks/aliases/rebasing or cropped comparison. Never count partial
source or reclassify origins because a build/source audit succeeds.

Final handoff checks: **3,603 CI tests passed in 165.653 seconds**;
target, tracking, status and diff checks pass. No accepted dependency changed,
so no compiler build or cold replay was needed. Cleanup removed
243 duplicate working files (1,097,307 bytes),
375 reproducible bytecode files (8,285,269 bytes), and
161 empty build directories. Complete retention/cleanup receipts:
`.analysis/f149-handoff-cleanup.json`, `.analysis/f149-duplicate-cleanup.json`
and `.analysis/f149-handoff-source-checkpoint.json`. These historical checks
do not complete the resumed 98% objective.

The complete former documents remain byte-for-byte in
[handoff history](history/RE_HANDOFF_THROUGH_F148.md) and
[knowledge history](history/KNOWLEDGE_BASE_THROUGH_F148.md). Their active-goal
and next-task wording is historical; this document and AGENTS.md govern the
handoff. Historical relative links were authored from docs/: resolve them
there, or use Git at fd82165.

## F150 verification

Public CI passed **3,603 tests in 169.898 seconds**. Target,
tracking, status and diff checks pass. F148's 244 private files and all forty
previously protected groups were hash-verified unchanged, including 331 units,
135 canonical objects, 209 accepted source/header inputs and origin evidence.
No accepted dependency changed; no compiler build or cold replay was needed.
Cleanup removed 375 reproducible bytecode files (8,285,269 bytes).
Source and preservation receipts: `.analysis/f150-source-checkpoint.json`,
`.analysis/f150-preservation-before-ci.json` and `.analysis/f150-cleanup.json`.
The 24 new fragments remain private, uncompiled and unaccepted; exact code
remains 716,968 bytes and conservative coverage remains 36.26%.

## F151 verification

Public CI passed **3,603 tests in 173.573 seconds**. Target,
tracking, status and diff checks pass. F150's 268 private files and 283 checkpoint files and all forty
previously protected groups were hash-verified unchanged, including 331 units,
135 canonical objects, 209 accepted source/header inputs and origin evidence.
No accepted dependency changed; no compiler build or cold replay was needed.
Cleanup removed 375 reproducible bytecode files (8,285,269 bytes).
Source and preservation receipts: `.analysis/f151-source-checkpoint.json`,
`.analysis/f151-preservation-before-ci.json` and `.analysis/f151-cleanup.json`.
The 27 new fragments remain private, uncompiled and unaccepted; exact code
remains 716,968 bytes and conservative coverage remains 36.26%.
