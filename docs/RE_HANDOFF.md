# TH075 active reconstruction status — F186

Updated 2026-10-27. The user explicitly resumed reconstruction and requires
serious treatment of both large/core and small/leaf functions; all historical
assumptions are provisional. Do not avoid or discard dirty work. Use commit
subjects `gpt-web: ...`. The H184 *no-active-goal* handoff below is historical
and superseded by this active request.

F184 input functions were independently reconstructed from the supplied target and accepted
by complete canonical cold replay:

| Function | Extent | Code bytes | Actual relocation fields | Cold replay |
| --- | --- | ---: | ---: | --- |
| TitleScene::PollMenuInput | 0043ABF0..0043ACD3 | 228 | 19 | exact |
| ReplayScene::PollInput | 00429DC0..00429EF5 | 310 | 27 | exact |

Both original extents end in plain RET and are followed by INT3 alignment.
Independent Capstone decoding consumed all 538 native bytes. Ghidra read-back
agrees on boundaries and direct callees; VC7.1 source code independently
recompiled into two complete matching COMDAT bodies in one object. All 46
relocation offsets, types, symbols and resolved native targets are retained in
`config/match-units.toml`. The replay command used:

```bash
scripts/repo-python scripts/replay-exact-units.py --unit title-poll-menu-input-0043abf0 --unit replay-poll-input-00429dc0
```

Distinct synthetic pointer-only receiver interfaces avoid asserting the title
and replay scenes share a complete class layout. DWORD title controls and byte
replay controls, independent signs, ESC behavior and window-toggle key chord
remain separate. Native C++ class names, owner layouts and runtime integration
are still unknown; no imported credit was granted for helpers or data.

F185 added a substantial core state machine, **`TitleScene::Advance` at
`0x0043A270`: 1,273 CODE bytes plus the full 40-byte owned ten-entry switch
table immediately after RET**. Target body and table were independently read
from the pinned executable; native code hash
`f528f379b927bad808eaa0703fa48c798fb8998bbae44ca9a2c96264215928a7`,
table hash `01b9780b16a3176977d6c14d930d0eb42e860439a880b82435248b8459770254`.
All 342 native instructions, table entries, 65 external and 11 local
relocation fields were checked. Cold source replay of the full 1,313-byte
extent returned exact. The code implements two-player menu mode dispatch,
exit/cancel/navigation, per-item fade progress, timed transition and
randomized attract mode with audio fade. The source is a pointer-only borrowed
scene/virtual-slot view: owner layout, original return type/name and broader
runtime identity remain unproven; source/byte credit is only for the 1,273
function CODE bytes. The jump table is compared but adds no CODE credit.

A redundant identical candidate unit alias was independently detected after
registration and reconciled, leaving **one uniquely mapped unit for each
matching function** (496/496). Its private reconciliation receipt is preserved;
new automated coverage rejects unmatched or duplicate extents. No unrelated
source, original object layouts or origin classifications were changed.


F186 additionally cold-reconstructed **`OptionsScene::AdvanceAt00428F00`**,
a 951-byte scene state-machine with an adjacent owned 28-byte / seven-entry
switch table. The complete 979-byte extent, **70 COFF relocations including
eight same-COMDAT local-target fields**, is cold-exact. Independent Capstone
decoding consumed all 269 native code instructions, ending at plain RET
004292B6; the table occupies 004292B7..004292D2 and is followed by INT3.
Native CODE SHA256
`21e698c0f26cbca4c23286883c7de9a04cf91b1825c1090dfa320b09956f75fa`;
table SHA256
`f84e9f643843fc0db5c9ce2278848b8224a99bb915d32538e7d99646afd4f124`.
The reconstruction retains seven menu choices, signed two-axis navigation,
three option toggles, signed wrap/modulo policy, sound/stream volume bounds,
audio-offset application, delayed sample sound, configuration saving and
two early transition exits. The initial ordinary `!flag` source generated
a 982-byte comparison block; a later `1 - (flag != 0)` control gave 1001;
natural `flag ? 0 : 1` reproduced native 32-bit NEG/SBB/INC and all
remaining instruction/branch locations. Failed control objects and proofs
remain under `.analysis/f186-options-advance/`; no structural-only result
was counted as exact. Both call-only scene interfaces and the separate
configuration-saving callee remain provisional: this unit earns only its
own 951 CODE bytes, not helper/table ownership credit.

Current ledger: **497 exact functions, 752,200 CODE bytes / 1,973,516 reviewed
authored bytes = 38.11%**, conservative 38.05% with 3,608 unknown-origin bytes
retained. F184..F186 added four accepted units, three objects and six new
source/header inputs.
Keep R268 origin evidence, all 97 unknown candidates, 493 pre-F184
accepted units and protected private F184/F185 preview/drafts intact.

Next: attack other large scene/battle functions (e.g. 00429F00 options
selection or 0043AD10 battle initialization) with full CFG, branches, call graph,
target writes, lifetime and switch ownership before adopting any source.
Do not claim exact credit for incomplete probes. Record failed approaches and
commit separately when they yield durable discoveries.

## Historical H184 handoff (superseded active-goal and F184 preview statements)


Updated 2026-10-26 for the user-requested cleanup and handoff, H184.

The user cleared the active goal before requesting this handoff. **No goal is
active; no pause action was taken. The 98% authored-byte objective remains
incomplete.** This instruction supersedes historical active-goal commands.
No new reconstruction batch or canonical acceptance was started after the
handoff request. Subsequent project phases remain deferred.

## Continuation command

Use this command when the user requests reconstruction again:

```text
Resume TH075 function reconstruction toward 98% authored-byte exact, using
H184 and the prepared F184 menu-input cohort. Read AGENTS.md, RE_HANDOFF.md,
RE_WORKFLOW.md and KNOWLEDGE_BASE.md; inspect git status and run the four
required target/tracking/status/Ghidra preflight checks. Preserve all accepted
units, origin evidence through R268, all 97 unknown origins, every pending byte
in the conservative denominator, and private inputs/objects. Start with full
F184 previews 43ABF0/228 and 429DC0/310: both have zero differences but no
canonical acceptance. Use the H184 resumption seed against the documentation
handoff commit; preserve the old F184 seed against a306ad6 unchanged. Copy
frozen drafts to a new mutable working directory before editing. Register
complete extents/every actual relocation, then cold-replay only new units
before granting credit. Keep compiler builds serial and everything headless;
use scripts/repo-python, the existing Ghidra wrapper and no REA. Never invent
owner layouts, inert locals, padding, ABIs, assembly, comparison masks, cropped
extents or local-label rebasing. Commit/push bounded progress with subjects
"gpt-6.1-sol: ...". Do not automatically pause an active goal merely because
cleanup, a commit or context handoff finishes.
```

## Verified baseline

| Measure | Value |
| --- | --- |
| Provisional candidates | 4,351 |
| Reviewed authored / library / compiler | 1,002 / 2,671 / 581 |
| Unknown origins | 97 / 3,608 code bytes |
| Source-present / exact functions / exact units | 493 / 493 / 493 |
| Exact CODE bytes | 749,438 |
| Reviewed authored coverage | 749,438 / 1,973,516 (37.97%) |
| Conservative coverage, including pending bytes | 749,438 / 1,977,124 (37.91%) |
| Canonical objects / accepted source-header inputs | 166 / 268 |
| Adoption manifest after F009 | 433 additions / 739,555 CODE bytes |

The ledgers and status script are authoritative. CODE size determines credit;
comparison extents include owned tables/remaps. Every pending byte stays in the
denominator. Unknown origins receive no credit and do not block independently
reviewed authored functions. Names and complete owner layouts remain provisional.

Use only the supplied Japanese th075.exe 1.11, SHA-256
`bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
Identity is pinned to the user's archive, without independent official
provenance corroboration. Never substitute th075c.exe or patch target bytes.

The latest reconstruction commit is **a306ad6 (F183)**. This work added 16
canonical units and 9,888 CODE bytes across five pushed commits:

| Cohort | Commit | Accepted work | CODE bytes |
| --- | --- | --- | --- |
| F179 | 2a697d8 | Complete background renderer 435A70 | 6,404 |
| F180 | 4ecb7fb | Eleven background counter/cycle callbacks | 463 |
| F181 | d13a8e9 | Complete timed-sprite renderer 451A00 | 446 |
| F182 | 9d128c4 | Two name-entry input policies | 1,486 |
| F183 | a306ad6 | Complete title-menu renderer 43A7A0 | 1,089 |

Each cohort cold-replayed only new units and passed 3,612 CI tests. Existing
canonical inputs, origins, headers and protected evidence stayed unchanged.
Detailed proofs/cold reports/checkpoints remain under `.analysis/f179*` through
`.analysis/f183*`.

## Prepared F184: diagnostic previews only

| Native function | Bytes | Returns / branches | Actual fields | Differences |
| --- | --- | --- | --- | --- |
| R043 43ABF0, TitleScene::PollMenuInput | 228 | 1 / 9 | 19 | 0 |
| R053 429DC0, ReplayScene::PollInput | 310 | 1 / 16 | 27 | 0 |

Both full extents have plain RET, no owned tables and checked following INT3
alignment. All 18 calls target canonical input/window helpers. Every one of the
46 fields is included. Neither function has public source, a registered unit,
a canonical cold build, source-presence credit or exact credit.

Keep `.analysis/f184-menu-input/` containing MenuInputF184.cpp/.hpp, profile,
both full diagnostics/relocated bodies/assembly and compiler log; the native
and attested decompile evidence `.analysis/f184-menu-input.c`, `-ghidra.log`,
`-native-proof.json` and `-native.asm`; `.analysis/f184-compare-menu-input.py`;
and `build/probes/F184MenuInput.obj` with its live PDB companion.

The preview was already running when the user cleared the goal. Its completed
results were collected; no further function reconstruction was started.
Preserve DWORD versus byte clears, independent signed direction checks,
confirm/cancel bytes, Escape counter and actual chord placement. A call-only
source interface does not prove shared original owner identity or full layout.

The old preview seed records a306ad6. The H184 documentation commit changes
HEAD without changing accepted code. Use the post-commit
`.analysis/h184-handoff/resumption-seed.json` for a new working directory;
do not rewrite the old seed or relabel an old object as cold evidence. The
handoff-state, retention, source-checkpoint and commit-receipt files in the same
private directory pin all inputs and the new commit. Verify hashes, register
every field and cold-replay each new unit before updating acceptance ledgers.

## Retained investigations

Preserve 14 frozen prior working objects plus F184: 15 total. The private active
retention receipt records their source/header/profile/object hashes. Also retain
all 14 F157 probes, both F159 traces and 40 protected groups. The old F176
440-byte probe is historical negative evidence; F181 independently accepts the
same native function through a complete 446-byte object.

- Complete 004AC040: F156-derived 151-entry baseline, 83,922-byte comparison,
  18,539 differences/all 2,352 fields. Preserve its baseline object and closed
  F153..F166 scope/profile/member/window/word controls; do not blindly repeat.
- Complete 0050A580: 81,539 CODE / 82,106 comparison bytes; emitted 82,109 with
  26,719 differences/all 1,449 fields. Keep F145CanonicalViews and five older
  retained objects. No credit.
- Complete 0055AC80: 28,862-byte comparison; emitted 28,868 with 8,545
  differences/all 696 fields. Preserve F167 physical-flow source/object and the
  closed lexical-scope control. No native-label rebasing.
- R103 453EB0: native 181, retained emitted 185/111 differences. Earlier `/Op`
  and member/window controls are closed; preserve its object.
- R231 unread camera stores, R065 445A00's write-only local and R054 455B30's
  28-byte clear still lack supported source-purpose explanations. No fabricated
  inert locals, arrays or padding.
- Options 428F00/951 and 429F00/563 require their owned-table review. Battle
  initialization 43AD10/922 is an EH constructor with allocations/incomplete
  owner layouts. These remain unaccepted; no fake owners or pasted EH bytes.

F179 showed that borrowed observed float member windows can change x87 operand
order and argument marshalling without changing types/ABI. F181 showed that
meaningful names in distinct measured buckets can explain actual local slots.
Read the precise archived controls before applying either observation elsewhere.

## History and tools

The complete former documents are preserved **byte-for-byte** in
[handoff through F183](history/RE_HANDOFF_THROUGH_F183.md) and
[knowledge through F183](history/KNOWLEDGE_BASE_THROUGH_F183.md). Original titles,
paths, target strings, observations and unknowns remain intact. Archived goal-
state and next-task commands are historical. Earlier F148 archives and origin
histories are unchanged. Historical relative links were written from docs/;
resolve them there or use the original Git version. Current instructions govern.

**Preserve this workspace when switching agents.** Private sources, objects,
receipts, target and Ghidra project are not in a Git clone. Preserve shared tools
and private service/authentication settings; never print/commit the private URL.
Use scripts/repo-python for every repository Python command. Remain headless:
unset DISPLAY/WAYLAND_DISPLAY and disable Wine graphical drivers per process.
Use the existing attested Ghidra wrapper, serial compiler builds and new/affected
cold replay. Claims.csv stays header-only. Commit subjects remain
`gpt-6.1-sol: ...`; commits and pushes remain authorized.

## H184 cleanup and validation

Wine lowercased PDB filenames, so earlier case-sensitive cleanup missed old
outputs. H184 excludes every frozen path and every live object/executable/DLL
companion **case-insensitively**. It losslessly archived 480 unpaired old PDBs,
verified every full round-trip SHA-256, then removed only those original outputs.
All object files and live PDB companions remain. The local archive is
`.analysis/h184-handoff/retired-orphan-pdbs.tar.gz`; its receipt records original
paths/hashes and restoration details. This step reclaimed 32,225,914 bytes net.

No accepted source, header, ABI, flag, relocation, origin or manifest changed
for this handoff; no cold rebuild was needed. No pause action or new goal was
created. Final checks and cleanup receipts follow.

Final CI passed **3,612 tests in 199.877 seconds**. Target,
tracking/status, current documentation links and diff checks pass. All 493 exact
units/166 canonical objects/268 accepted inputs, all origin evidence through
R268, the 15 retained working objects, all 14 F157 probes/both F159 traces and 40
protected groups were hash-verified unchanged. All 859 remaining build
files were also hash-verified unchanged after cleanup. F184 remains two unaccepted
zero-difference previews; no registration, new compiler build or cold replay ran
after the user's handoff request.

Cleanup retained all 628 object files and
231 live PDB files, replaced 480 unpaired PDB outputs with
a lossless verified archive, and removed 377 reproducible bytecode files
(8,312,399 bytes). Total net reclamation is
**40,538,313 bytes**. The former main documents' 231,263 bytes
are preserved exactly in the new F183 archives; current entry documents are
shortened without discarding their evidence. Private receipts and frozen source
checkpoint are under `.analysis/h184-handoff/`; commit receipt and resumption
seed are finalized after the authorized documentation commit is pushed.
The goal remains cleared, and the 98% objective remains incomplete.
