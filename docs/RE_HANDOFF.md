# TH075 function reconstruction handoff

Updated 2026-10-24. The user resumed reconstruction after the cleanup/handoff
checkpoint and set an active **98% authored bytes exact** goal. The objective
is incomplete. Continue the F066 investigation below.
Subsequent project phases remain deferred. Use existing Ghidra/local tools,
without REA; commit subjects must use `gpt-6.1-sol: ...`. Commits and pushes
remain authorized. Keep compiler builds serial and monitor CPU/memory.

## Verified checkpoint

| Measure | Current value |
| --- | --- |
| Provisional candidates | 4,351 |
| Reviewed authored / library / compiler | 1,002 / 2,671 / 581 |
| Unknown origins | 97, totaling 3,608 bytes |
| Source-present / exact functions / exact units | 159 / 159 / 159 |
| Exact code bytes | 523,280 |
| Reviewed authored coverage | 523,280 / 1,973,516 (26.52%) |
| Conservative coverage, including every pending byte | 523,280 / 1,977,124 (26.47%) |

The ledgers and status script are authoritative. Origin evidence through R268
is unchanged. The exact-adoption manifest retains F009 and **99 additions /
513,397 code bytes / 114 new source/header inputs**. F021/F048/F061/F066 remain
unaccepted. Unknown origins receive no credit and do not block independently
reviewed authored functions.

The only target is the supplied Japanese `th075.exe`, reporting version 1.11:
SHA-256 `bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
Identity is pinned to the supplied archive, without independent official
provenance corroboration. Never substitute `th075c.exe` or patch target bytes.

## Latest accepted function: F068

`SpriteTransform40FBB0::ResetNodeTransform` cold-replays exact across all
158 bytes at `0x0040FBB0..0x0040FC4D`: 47 instructions, one fully bound
`memset` relocation, one ret12, no branches/tables. Two following INT3 bytes
are excluded. The R036 role `SpriteScene::ResetNodeTransform` is retained by
alias; ownership, native extent and hash remain fixed.

The declaration-only receiver takes three float words, stores them at
+34/+38/+3C, enables +40, clears exactly 36 bytes at +10, and performs all
actual scale/color/short/byte resets, including duplicate writes after the
clear. The real memset call is cdecl with 12-byte caller cleanup. All 57 F066
sites pass current and the callee returns with 12-byte argument cleanup.
Original declarations/names and full owner layout remain unknown. Never
construct or embed this receiver or the older partial SpriteTransform view.

Preview, independent canonical compile and separate canonical cold replay
match with the existing explicit VC7.1 build 3077 profile. No prior accepted
source/header changed; all 158 earlier units/canonical objects are unchanged
and were not rebuilt. Retain `.analysis/f068-bind.py`, both binding receipts,
`f068-accepted-replay.json`, `f068-cold-replay.log`, `f068-adoption-parent.json`,
`f068-progress.json`, attested transform view/log and private preview inputs.

```bash
scripts/repo-python scripts/replay-exact-units.py --unit sprite-transform-reset-0040fbb0
```

Full CI passes all **3,603 tests in 149.169 seconds**. Tracking, progress-card
and whitespace checks pass. `f068-evidence-check.json` verifies all prior
accepted inputs/objects/origins and active drafts unchanged. The preview object
and generated scripts/tests bytecode were removed after verification, with
hash receipts in `f068-obsolete-output-cleanup.json` and
`f068-bytecode-cleanup.json`.

The next bounded dependency is the complete polar velocity helper at
`0x0040FB70` (57 bytes, R217), then recorded range `0x00455580` and sound/shake
wrappers. F066 remains the active large caller draft. The dependency work
counts only independently cold-accepted authored functions.

## Previous accepted function: F067

`AnimationProgress40FA30::AdvanceNestedFrame`, from
`src/AnimationProgress40FA30.cpp` / `.hpp`, independently cold-replays exact at
`0x0040FA30..0x0040FABD`: **all 142 bytes**, 48 instructions, four internal
branches, two actual virtual slot-zero calls and one ret0. There are no tables
or relocations. Two following INT3 bytes before `0x0040FAC0` are excluded.
The alias preserves R103 `AnimationState::AdvanceNestedFrameAt0040FA30`;
origin classification, extent and native hash remain unchanged.

The method increments the 16-bit tick at +64, compares signed words against
+72, resets the tick and advances phase +62 when due. On wrapping it resets
phase, calls virtual slot zero and returns the **post-callback** +70 word;
on a nonwrapping advance it calls the same slot and returns post-callback +62.
Before the threshold it returns AX zero. Never cache those fields across the
callback. All 58 F066 caller sites use current; 57 consume AX with MOVSX and
the default ignores the result. The four-byte frame saves this at EBP-4.

The callback view passes only this and ignores its result, matching the
existing F008 declaration-only slot-zero view. Original callback targets,
declarations, names and complete owner layout remain unknown. Do not construct
or embed this partial receiver. No existing shared header or accepted source
was changed. All 157 prior units and canonical objects remain unchanged and
were not rebuilt.

Preview, independent canonical compilation and a separate canonical cold replay
match with VC7.1 build 3077 and `/Od /Ob0 /Gy /GR- /GX- /Zi /I src`:

```bash
scripts/repo-python scripts/replay-exact-units.py --unit animation-progress-0040fa30
```

Keep `.analysis/f067-bind.py`, both physical binding receipts,
`f067-abi-review.py` / `.json`, `f067-accepted-replay.json`, `f067-cold-replay.log`,
`f067-adoption-parent.json`, `f067-progress.json`, the private
`animation-progress-40fa30/` sources and the retained canonical cold object.
The full native export and attested view remain in `f066-callee-40fa30.asm`,
`f066-callee-views.c` and `f066-callee-decompile.log`. Historical acceptance
and detailed older investigations are preserved in the
[handoff archive](RE_HANDOFF_HISTORY.md#f065-and-pre-f066-full-draft-handoff-snapshot-2026-10-24).

## Next reconstruction: F066

Continue R048 `0x0055AC80..0x00561B8F`, historical role
`CharacterObject::AdvanceAt0055AC80`. Its **28,432 code bytes** contain 7,653
instructions, 860 internal branches, 394 direct calls to 14 callees and one
ret0. There are no indirect calls or external branch exits. The contiguous
232-byte switch table and 198-byte remap extend comparison through
`0x00561D3D`: compare **all 28,862 bytes**. Exclude only the two following INT3
bytes. The native frame is 0x19C, with ESI saved and this at EBP-24.

All **57/57 states**, entry guards and the real default now have handwritten
natural source in `.analysis/object-action-55ac80/Preview.cpp` / `.hpp` and
`states/*.inc`. `active03/` pins the complete source/header; the live object is
`build/probes/F066Preview.obj`. Never replace these with a partial switch or
blindly rerun the initial one-shot `f066-complete-fragments.py` bootstrap.
The review index pins each fragment's hash, native region and manual behavior
notes. Eight genuine loop indices explain the user locals; add no inert locals,
padding, assembly, fake results or alternate bodies to force a match.

The full caller/14-callee ABI audit checks every native instruction, all 394
calls and stack joins; wrong 16-byte effect cleanup is rejected. Thirty-four
owner-at-E4 calls comprise 25 effects, seven sounds, one gauge update and one
shake; other thiscall receivers are current. Twelve angle calls use cdecl,
two floats and ST0; 11 ftol2 uses are ordinary casts with the actual implicit
ST0-to-EDX:EAX ABI. The gauge argument is a full dword. Shake passes real 3.0f
through a setter to a field independently read by x87. Both angle origins stay
unknown. F067 now accepts only the separate frame helper, not F066 itself.

All **696 relocations** are physically bound: 394 calls, 237 readonly constants,
five existing signed-byte reads at `0x006714D0`, two table/remap addresses and
58 table destinations. Actual COFF/PE payloads, widths, permissions, addends,
operand fields and every branch/table destination are checked. Preserve the
qword double literals 0.85 in state 902 and 998.9 in state 996, exact radian
coefficient `0.01745328866f`, ordered floating comparisons, nested RNG evaluation
order and all real early exits. Original field meanings and full layouts remain
unknown; do not construct or embed any partial owner.

**F066 remains unaccepted.** The complete draft emits 28,868 bytes, six too
many, with the correct instruction count and frame. There are 976 differing
instruction encodings. The first nonbranch difference is `0x0055F711` in state
905: native loads this into ECX, the draft into EAX. Six later accumulator
encoding differences account for the extra bytes. Register classes and temporary
displacements are elided only to locate gaps; correspondence earns no exactness
or unrestricted equivalence. No F066 source-presence entry, canonical descriptor
or exact credit exists.

State 996's positive-3B6 arm must return directly to the epilogue; that genuine
exit correction makes every branch destination correspond. Integer versus
float zero spelling, chained velocity-zero initialization and state 905's
owner-failure return/break control all emit identical whole function bytes and
relocations after that correction. Retain the revision intents and binding
receipts; do not repeat these controls without new native/compiler evidence.
Use current full binding receipts, not cached pre-control diagnostic copies.

Keep `f066-native-audit.py` / `.json`, `f066-55ac80.asm`, the attested action and
callee views/logs, `f066-abi-review.py` / `.json`, dependency/consumer/global-xref
evidence, case/review indexes, `f066-native-constants.json`, state sources,
`f066-source-revisions.json`, diagnostic/binder scripts and receipts, and
`f066-progress.json`. From the repository root, after normal target preflight:

```bash
scripts/repo-python .analysis/f066-whole-diagnostic.py
scripts/repo-python .analysis/f066-bind-draft.py
```

These diagnose the retained object; they do not cold-build or accept it. A new
source revision requires serial compilation with the recorded profile, complete
physical equality and a separate canonical cold replay before any credit.
Continue native/compiler statement and temporary-lifetime investigation at
state 905, preserving all earlier exact units and pending origins.

The resumed session tested controls 04..24 without changing active03.
Nineteen controls emit identical complete patched bytes and all 696 physical
bindings: scale/color chaining, velocity commas, signed/unsigned/long constant
promotions, reversed/negated equality, double zero literals, nested guards,
expanded scale additions, statement scopes and lvalue parentheses. Both
subtract-one forms change the instruction sequence and are rejected. Do not
repeat these controls without new evidence. See `f068-f066-controls.json` and
individual source/header/intent/binding/log inputs. Removed 19 reproducible
objects / 1,119,252 bytes after full equality; five differ only in generated
local switch label names, whose offsets/addends/destinations remain identical.
All inputs, evidence, PDBs and active objects are retained.

## Other active drafts

| Cohort | Complete comparison | Active inputs and first remaining difference |
| --- | ---: | --- |
| F061 | 34,877 bytes | `.analysis/object-action-5eb520/Preview.cpp` / `.hpp`, `active07/`, `build/probes/F061Preview.obj`; draft +2 bytes, 324 instruction encodings, first nonbranch `0x005F3904` in state 998 |
| F048 | 83,922 bytes | `.analysis/character-action-4ac040/Preview.cpp`, active03 evidence, `build/probes/F048Preview.obj`; equal total size, 7,209 encodings, first `0x004ADEFA` in state 89 |
| F021 | 62,089 bytes | `.analysis/reimu/Preview.cpp` and 18 case includes; draft +1 byte, 6,311 physical operand differences, first `0x0045FDA9` in state 89 |

These are diagnostic drafts with no acceptance credit. Full ABI/CFG reviews,
controls, remaining uncertainties and retention paths are preserved verbatim in
the [archived snapshot](RE_HANDOFF_HISTORY.md#f065-and-pre-f066-full-draft-handoff-snapshot-2026-10-24).
Do not regenerate them from older initial-case generators or repeat rejected
controls without new evidence. Their active sources/objects remain unchanged.

## Cleanup and verification

Removed **five redundant objects / 335,907 bytes** after complete COFF equality:
F066 controls 01/02 have the same function and all 696 relocations as retained
active03; the F067 preview matches the canonical cold object after only the
explicit owner rename. The F048 probe-03 and F061 active07 snapshot object files
are entire-file identical copies of their retained live `build/probes/` objects.
Their sources, headers, intents and receipts remain; use the retained object
paths in `.analysis/f067-obsolete-output-cleanup.json` or rebuild a control.

Removed **375 Python bytecode cache files / 8,282,484 bytes** from `scripts/` and
`tests/` after CI. Python sources, tests and the private environment remain;
imports can regenerate caches. See `.analysis/f067-bytecode-cleanup.json`.
Total cleanup reclaimed **8,618,391 bytes (about 8.22 MiB)**. All active sources,
objects, manifests, origin evidence, PDBs and shared tools remain.

The private Wine compiler environment accounts for about 1.3 GiB of the 1.7 GiB
analysis directory. It is required tool state, not disposable game output.
Origin scans and attested exports are evidence. Do not delete either to reduce
size. Only reproducible Python bytecode caches were removed after checks.
Private `.analysis/`, `build/`, `ghidra-project/` and tools are not committed;
a new checkout alone cannot restore unaccepted drafts. Keep this workspace for
handoff. Never commit game binaries/data, archives, generated decompiles,
analysis databases, downloaded tools or secrets.

Run the [AGENTS.md](../AGENTS.md) preflight before reconstruction, then replay
only affected units. Use `scripts/repo-python` for every repository Python
command. Compiler niceness is 15; CI niceness is 10.

Full CI passes **3,603 tests in 135.949 seconds**; tracking, progress-card and
whitespace checks pass. `.analysis/f067-evidence-check.json` verifies all 157
prior unit descriptors and canonical objects, 110 prior manifest source inputs,
4,350 other function rows, 218 origin files and historical prefixes unchanged.
The previous detailed handoff is archived verbatim. F066 active03 and F061/F048
live sources/objects are pinned; F021 remains untouched. Recorded resource
samples show about 8.5 to 9.0 GiB available memory, 81–93% interval CPU idle and
zero interval swap-in/out. No compiler build or CI job remains running.
