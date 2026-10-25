# TH075 function reconstruction handoff

Updated 2026-10-25 for resumed reconstruction, F152.
**The 98% authored-byte objective is active and incomplete.**
The user resumed after the cleanup and handoff checkpoint. Subsequent project
phases remain deferred. Continue the complete function cohort below.

## Verified reconstruction state

| Measure | Value |
| --- | --- |
| Provisional candidates | 4,351 |
| Reviewed authored / library / compiler | 1,002 / 2,671 / 581 |
| Unknown origins | 97 / 3,608 code bytes |
| Source-present / exact functions / exact units | 333 / 333 / 333 |
| Exact code bytes | 717,040 |
| Reviewed authored coverage | 717,040 / 1,973,516 (36.33%) |
| Conservative coverage, including pending bytes | 717,040 / 1,977,124 (36.27%) |
| Canonical objects / accepted source-header inputs | 136 / 211 |

The ledgers and status script are authoritative. The adoption manifest retains
F009 plus 273 additions / 707,157 code bytes / 211 inputs. Origin evidence through
R268 is intact. Every pending code byte remains in the conservative denominator.
CODE `size` determines credit; full `compare_size` also includes owned tables.

Only use the supplied Japanese th075.exe 1.11, SHA-256
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
Identity is pinned to the user's archive, without independent official
provenance corroboration. Never substitute th075c.exe or patch target bytes.

The preceding pushed reconstruction checkpoint is **92894f8 (F151)**.
F152 accepts two new whole R103 policies in `src/FighterMoveScalarHelpers.cpp`:
`fighter-set-nonnegative-word-00453e80` (37 bytes) and
`fighter-begin-fade-parameters-00454a70` (35 bytes). Both passed canonical cold
replay, 72/72 bytes with zero differences, across one new object. Both have no
actual relocations. Names and complete owner layout remain provisional.
F146's 51-byte motion helper remains accepted. The large drafts earn no credit.

## Continue after F152: match complete 004AC040

The authoritative private source is **`.analysis/character-move-4ac040/f152/`**.
All **151/151 nondefault entries** now exist, covering 82,372 contiguous native
investigation bytes 004AC1B9..004C037C. `Preview.cpp` composes those entries plus
the real prefix/default/shared tail into one complete body. Source SHA-256:
`24ea3a57edbb6a7e6f28a0ebae10df9252d8141bb2223bf2bc2408ee14549e96`.
The complete draft compiles, but remains unaccepted with no source-presence or
exact credit.

1. Read the native/source/receiver/scalar audits, `complete-source-profile.json`,
   `complete-whole-diagnostic.json`, `complete-dispatch-diagnostic.json` and
   `pending-helper-native-contracts.json`. The source audits predate compilation
   and the two helper acceptances; preserve those snapshots unchanged.
2. Copy current source/control inputs to a fresh F153 directory before editing.
   Preserve F148/F150/F151/F152, the full native map, `build/probes/F152Complete.obj`
   and their evidence. F149 remains the cleanup/handoff receipt identifier.
3. Investigate **state 6, 004AC4E7..004AC679**, first genuine instruction-order
   divergence: two x87 operand loads occur between receiver-address loads in the
   draft but after both receiver-address loads in the target. State 88 is the
   first extent difference (+12 bytes), including native DWORD motion copying
   versus emitted x87 copying. These are observations, not a proven source fix.
4. Keep one complete source body and explicit flags. Recheck used ABI and every
   actual relocation after source changes. Never compile a partial wrapper,
   normalize/rebase bytes for acceptance, or accept a case/chunk.

First whole diagnostic: **84,234 emitted bytes** = 83,108 code + 1,126 owned
data, **74,320 position differences**, 2,352 actual relocation fields. The
emitted code is 312 bytes longer than the target. All four byte remaps match;
all six pointer tables retain their actual entries/widths. The emitted 0x720
frame, saved ESI and EBP-0x64 receiver slot agree with target observations.
These facts do not prove the original locals, types or profile. The diagnostic
replays every real local COFF offset and independently evidenced external
destination without masking, cropping, aliases or native-label rebasing.
Dispatch-local instruction diagnostics only locate differences and earn no
credit. Preserve the separate full unmasked result as authoritative.

Required comparison remains **83,922 bytes**:82,796 code plus 1,126 owned
switch/remap bytes. Four remapped/two direct guards, five equality states,
ten contiguous owned data segments and 1,933 internal branches are checked.
Code ends 004C03AC; the full owned extent ends 004C0812 exclusive. Preserve
actual default 004C037D, common tail 004C039F, epilogue 004C03A7 and sole RET 004C03AB.
Frame 0x720, saved ESI and ECX at EBP-0x64 are observations: recover genuine locals
and nested packets without artificial storage.

The source audit checks all 151 entry hashes, native call evaluation order and
real exits. There are 24 genuine loop counters/25 loop statements and 41
float-to-short conversions. F152 adds 20 entries/22,380 native investigation
bytes; its scalar audit checks direct literal store widths, values and order
in those entries. It does not prove computed expressions or conditions.
The preacceptance call audit had 1,290 canonical named calls, 21 pending named
calls, 41 CRT conversions and six true slot-0 calls. Eleven pending call sites
now have independently cold-exact helper bodies (nine 453E80, two 454A70).
Ten remain without canonical bodies: seven command454BC0, two resource452B30
and one unknown483300. The draft still uses the frozen pending receiver view;
adopting the new canonical declaration belongs to the next complete revision.
Both483300/483320 remain unknown. Do not reclassify ownership from call ABI.

Current source/evidence is frozen by `.analysis/f152-source-checkpoint.json`.
Earlier checkpoints remain immutable. Preserve both explicit 36-site rings in
603/605, four real loops in607..610, repeated signed-global level reads and
all short motion snapshots/restores. Nested random arguments retain native
right-to-left evaluation order. See the knowledge index for further details.

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

## F152 verification

Public CI passed **3,603 tests in 152.063 seconds**. Target,
tracking, status and diff checks pass. Both new helper units passed one canonical
cold build, 72/72 complete bytes exact. All 331 prior unit definitions, 209 prior
accepted source/header inputs, all origin evidence and forty protected groups
were checked; 134 prior objects remain byte-for-byte unchanged. An accidental
default R100 verifier invocation rebuilt the remaining graphics object; its
complete 495-byte canonical replay passed exact. The explicit R103 check passed
and performed no builds. No other accepted unit needed cold replay.

F151's 296 private files and 313 checkpoint files were hash-verified
unchanged. The complete 151-entry draft was compiled once successfully after an
include-macro error; its full 84,234-byte diagnostic remains a failure with 74,320
position differences and earns no credit. All sources, native evidence, active
objects and acceptance manifests are retained. Cleanup removed 375
reproducible bytecode files (8,285,274 bytes). Receipts:
`.analysis/f152-source-checkpoint.json`, `.analysis/f152-preservation-final.json`,
`.analysis/f152-scalar-canonical-replay.json`,
`.analysis/f152-unintended-r100-anchor-replay.json` and `.analysis/f152-cleanup.json`.
Exact code is 717,040 bytes; conservative coverage is 36.27%. The 98% goal remains
active and incomplete.
