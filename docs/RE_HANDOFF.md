# TH075 function reconstruction handoff

Updated 2026-10-04. Work resumed with origin-review batches R070–R107, moved to
exact reconstruction for F008 and F009, and has now completed bounded origin
review cohorts R108 through R119. The public
repository is [N0zoM1z0/th075](https://github.com/N0zoM1z0/th075) on
`main`. Commit subjects use `gpt-6.1-sol: ...`. Keep documentation in English.

## Verified checkpoint

The pinned target is the supplied Japanese `th075.exe` (reported `ver1.11`),
SHA-256 `bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
The initial Ghidra inventory has 4,351 provisional candidates. Origin review
has resolved 3,116: 919 authored, 1,622 library and 575 compiler generated.
There are 1,235 pending. Candidate count is not authored function count.

The exact baseline is 60 source-present and exact functions, covering 9,883
bytes across 60 match units. Exact coverage of the currently reviewed authored
bytes is 9,883 / 1,965,299 (0.50%). This denominator is provisional because
origin review is incomplete. F008 adds nine reviewed game leaf helpers / 315
bytes; F009 adds nine game policy and dependency helpers / 652 bytes. The
current strategy is origin review. Preserve the exact baseline while resolving
the bounded R120 lock/error/termination cohort below.
Both the complete-origin and 50%-exact milestones remain unfinished.

The canonical state lives in `config/functions.csv`,
`config/function-origins.csv`, the origin evidence CSVs and the exact
match-unit manifests. The progress SVG is generated from those ledgers.
[Origin review](ORIGIN_REVIEW.md) records the evidence and boundaries for
R001–R119; the [knowledge base](KNOWLEDGE_BASE.md) records accepted facts.
The former chronological handoff is preserved in
[handoff history](RE_HANDOFF_HISTORY.md); its earlier counts and next-step
notes are historical snapshots.

## Next agent objective — R120 lock/error/termination cycle

R108 reviewed all six lifetime candidates. Only `0x00449D40` gained authored
origin: its complete 31-byte explicit virtual destructor differs from the
implicit cleanup controls and binds the game texture destructor and paired
stage lifetime context. The other five have indistinguishable complete
explicit/implicit source alternatives and remain pending. Do not repeatedly
accept or re-review those five based only on scanner rank.

R109 resolved thirteen explicit game policies, including the two pending
scene parents of `0x004251C0`. R110 resolves all six deque dependencies from
that handoff plus the complete 262-byte range-erase callee `0x005F8680`:
seven library bodies / 501 bytes. Its verifier cold-builds 53 complete source
bodies / 3,207 bytes with 85 exact typed calls, rooted in the independently
reviewed 221-/276-byte game loops. The 17-byte getter now has independent
source typing; postfix increment binds the actual prefix increment, not the
equal-shaped postfix decrement. Synthetic game types are probe models, not
reconstructed owner layouts or exact units. The unknown delete tail retains
no origin credit; the already-reviewed range-error boundary retains its
historical library evidence and unresolved original source identity.

R111 resolves those five range erases, four complete single-erase wrappers and
the three required one-byte iterator helpers: twelve library bodies / 1,654
bytes. Its closed graph cold-compares 129 distinct target bodies / 7,958 bytes,
203 typed call fields and 337 whole source alternatives. The four wider graphs
fit unsigned-long, float and `void*` models; the fifth fits the checked byte
model. The original element types and any folding remain unknown. The separate
108-byte parent `0x00455CA0` and 1,459-byte insertion dependency `0x00455E40`
remain pending; no origin follows merely from their library children.

R112 resolves all six postfix increments / 324 bytes through their actual
complete prefix callees. Fifty-two cold overload controls distinguish increment
from equal-shaped decrement. It also resolves the complete 695-byte input
matcher and 273-byte event worker through independent game controls, complete
108-byte switch data, raw imports and the actual CreateThread callback binding.
The existing exact wait-global clamp `0x00423C60` retains R104/F008 evidence,
source and name. Setup/cleanup context does not gain ownership automatically.
Replay `scripts/repo-python scripts/verify-deque-postfix-context-origins.py`.

R113 resolves all six queue-helper handoff candidates, plus their complete
2,987-byte game main-loop parent: five library bodies / 153 bytes and two
authored policies / 3,083 bytes. Its verifier cold-compares 65 complete source
bodies / 4,002 bytes and 150 typed fields. Nine external snapshots retain
independent origins; archive replay owns the complete CRT boundaries and their
embedded tables. Nine complete game contexts retain 234 witnesses, actual
imports, TH075 resource literals and the whole fifteen-entry scene table.
The 65 separate shape controls do not identify original element types.
Replay `scripts/repo-python scripts/verify-event-queue-origins.py`.

R114 resolves four authored policies / 415 bytes: shared queue acquire
`0x004239F0` (155), release `0x00423A90` (143), local acquire/release construction
`0x004239C0` (34) and window callback `0x00603650` (83). Ten complete lifetime
controls / 274 bytes distinguish the 34-byte construction from the implicit
member and persistent-member controls. The 26-byte `0x00423B20` matches both
an ordinary pulse and the compiler-generated copy initializer `_$E3`, with the
whole `.CRT$XCU` registration retained. It remains unknown; do not call it a
destructor or repeatedly choose one source alternative from scanner rank.
The callback has the actual main-loop registration/readiness witnesses and
raw USER32 imports. Cleanup preserves TerminateThread and passes the queued
entry value directly to SetEvent, unlike the worker's first-dword indirection.
Replay `scripts/repo-python scripts/verify-queue-lifetime-origins.py`; it also
cold-replays R077 and R113, preserving their complete dependency graphs.

The supplied PE entry `0x0064232C` has a complete 469-byte `_WinMainCRTStartup`
source body from the hash-pinned libcmt.lib wincrt0.obj member. All non-field
bytes match, but 32 of its 37 code/data/EH bindings remain diagnostically
unresolved. Four raw IAT bindings and the independently reviewed game main
callback are checked. This is a pending candidate, not accepted runtime or
exact evidence. Its internal SEH filter and second return remain inside the
full extent. The 55-node private startup survey is diagnostic only; neither
its names nor its relocation-masked body matches confer ownership.

R115 reviews all six startup candidates and the two required heap callees.
Four gain library origin / 196 bytes: `0x0064544F` (17), `0x00649735` (81),
`0x0064971B` (26) and `0x0064A6CD` (72). The closed heap graph checks all
17 fields, defining COMMON/BSS topology, writable PE loader zero-fill geometry,
raw HeapCreate/HeapAlloc/HeapDestroy identities and independent GetVersionExA
result provenance through a cold SDK layout control. Zero-filled dwords alone
do not prove a global identity; original executable debug names remain unknown.
The SEH epilog has its own complete relocation-free vendor auxiliary extent.
The 61-byte R006 stack probe's `__alloca_probe` label is proved to share the
full `__chkstk` definition's offset and section; no candidate is counted twice.
Replay `scripts/repo-python scripts/verify-startup-dependency-origins.py`.

The prolog `0x00645414` (59), `_fast_error_exit` `0x006422B2` (36),
`__amsg_exit` `0x0064228D` (37) and `__wincmdln` `0x00648FF5` (93) retain
explicit pending reasons. Eight cold-extracted whole source diagnostics /
1,144 bytes preserve their immediate dependencies without ownership credit.
The handler at `0x00645468` has a complete 230-byte vendor source body but no
Ghidra function or ledger candidate; its validation/unwind graph is unresolved.
The existing 47-byte exit candidate's source auxiliary extent includes the
next INT3, for 48 bytes total. Do not truncate comparison to 47 or accept that
extent silently. The command-line parser binds complete 30-/17-byte source
helpers, but their set-codepage/classification graphs and mutable data remain
unresolved. Avoid re-reviewing these four roots until the missing evidence changes.

R116 resolves three library bodies / 304 bytes: the complete exit dispatcher
(48), dynamic message-box dispatcher (249) and shared-copy entry (7).
Replay `scripts/repo-python scripts/verify-runtime-error-origins.py`; it
cold-replays R115 and retained runtime anchors. The exit ledger now includes
its own terminal INT3 at `0x006440D4`; the historical R115 diagnostic snapshot
is retained through a specific accepted-origin reconciliation. The private
database remains unchanged. The copy entry requires the entire 248-byte
strcpy/strcat carrier, including nine-byte LEA/MOV alignment and its real
shared tail. Six dynamic DLL export flows retain actual lookup/store/call
witnesses, whole 20-byte source cache BSS, loader geometry and natural SDK
USEROBJECTFLAGS/service-flag control. Version globals retain R115 provenance.

The writer `0x00648C70` (375), banner `0x00648E11` (57) and fastcall cookie
check `0x00640611` (14) remain unknown. Whole nineteen-entry error table,
all 32 readonly literals / 1,120 bytes, complete mutable state definitions
and three diagnostic contexts / 122 bytes retain their evidence. The failure
helper's source is 49 bytes, including a filter RET and terminal INT3;
its 48-byte candidate is unchanged. Do not repeatedly review these roots
until the missing security/failure/EH bindings change.

R117 resolves six complete library bodies / 779 bytes: cookie initializer
(102), EH validator (553), global unwind (32), prolog (59) and both NLG entries
(9/24). Replay `scripts/repo-python scripts/verify-security-eh-origins.py`; it
cold-replays R116/R115/R006/R025 and all complete PE import thunks. Whole SDK
layout/control array (120), actual validator cache BSS (76), complete NLG
state (16), cookie definition (4), initializer/markers and the full merged
56-byte table retain independent source/data/API provenance. The NLG entry
requires the entire 33-byte shared carrier and actual RET 4.

The two non-inventoried source handlers at `0x00645468` (230) and `0x00640B44`
(34) now have complete source/target/CFG and dependency evidence without new
candidate credit. This closes R115's missing prolog handler binding. Its
historical pending record is retained through a specific R117 origin guard;
its entire source body still replays. Application scope callbacks retain their
observed input-slot ABI and no implementation credit. The private database
remains unchanged.

The failure helper `0x006405E0` (49-byte source; 48-byte candidate), error
handler `0x0064529E` (328) and exit wrapper `0x0064425B` (17) remain unknown.
Complete cinit (106) and doexit (195) contexts and nine whole error literals /
474 bytes stay diagnostic. EH metadata, user callback and termination state/
lock/callback chains remain unresolved. Retain R116 writer/banner/cookie and
remaining R115 error/multibyte roots until their missing evidence changes.

R118 resolves five complete library bodies / 273 bytes: unlock (21), callback
loop (24), static lock initializer (73), dynamic critical-section wrapper (139)
and no-spin fallback (16). Replay
`scripts/repo-python scripts/verify-termination-lock-origins.py`; it
cold-replays R117/R116/R115 and retained runtime/import anchors. Full 288-byte
lock table, 336-byte static critical-section BSS, four-byte API cache, natural
SDK layout/error control and complete scope data retain independent source/
API/loader provenance. The callback loop preserves EAX begin/stack end, and
the fallback preserves RET 8. Three whole merged callback ranges / 52 bytes
and actual source markers/registration retain all observed pointers without
implementation credit. Original debug names/compiler settings remain unknown.

Four roots remain pending: doexit (195), lock (49), lazy lock initializer
(160-byte source; 151-byte candidate) and onexit initializer (40). The lazy
parent includes a nine-byte finally candidate at `0x0064671C`; doexit owns the
fourteen-byte shared cleanup candidate `0x00644236`, with its EH entry five
bytes earlier. Both interiors retain unknown ownership and original extents;
full source parents and label/scope bindings are checked. Do not truncate to
151 or fabricate standalone fragment sources. Six full source contexts /
522 bytes retain thread initialization, cinit, malloc, errno, free and error
policy; seven complete readonly literals / 105 bytes are frozen. Allocator,
TLS and termination chains remain unresolved, and the private database is
unchanged. Preserve all pending security/error roots until evidence changes.

Final acceptance passed in one no-auth public HTTPS MCP request: the full
R118 verifier and retained R117/R116/R115/runtime/import graphs, R114 lifetime
controls, all 872 recorded authored extents, target/tracking/Ghidra attestation,
233 public tests, progress freshness and `git diff --check`. All 60 exact units /
9,883 bytes cold-replayed across eleven objects. Investigation and intermediate
verification used local tools.

R119 resolves six complete library dependencies / 1,818 bytes: small-block
find (43), free (792), allocation (764), new region (183), new-handler callback
(27) and TLS allocation fallback (9). Replay
`scripts/repo-python scripts/verify-allocator-thread-origins.py`; it
cold-replays R118 and all retained runtime/import anchors. All 100 root fields,
168-byte natural CRT heap/thread layout, nine heap COMMON globals, six whole
state sections / 452 bytes and actual API/callee/callback bindings are checked.
Seven old anchors / 1,341 bytes retain full independent evidence, including
memmove's mixed code/switch-data extent and complete group allocation. Five
whole FLS literals / 54 bytes and four contexts / 485 bytes remain diagnostic.

All six handoff roots plus calloc remain pending: malloc (18), nh-malloc (44),
heap allocation (123 source; 111 candidate), free (113), errno (9), getptd (113)
and calloc (187). Three nine-byte existing cleanup candidates also stay unknown.
Heap allocation's EH head is +111 and shared entry +114; calloc's EH head is
+167 and shared entry +170; free's entry is +83. Preserve all full parents,
source labels and whole scopes; never truncate or fabricate standalone fragment
sources. Ghidra currently has no function containing the two earlier EH heads;
the complete verified PE/source comparisons retain them. Database and exact
ledgers are unchanged. The allocator/lazy-lock/thread/error cycle remains open.

Final acceptance passed in one no-auth public HTTPS MCP request: the complete
R119 verifier, retained R118/R117/R116/R115/runtime/import graphs, R114 lifetime
controls, all 872 recorded authored extents, target/tracking/Ghidra attestation,
251 public tests, progress freshness and `git diff --check`. All 60 exact units /
9,883 bytes cold-replayed across eleven objects. Investigation and intermediate
verification used local tools.

The next bounded cohort is six existing lock/error/termination roots:

| Candidate | Provisional bytes | Observed source association | Required next evidence |
| --- | ---: | --- | --- |
| `0x00646725` | 49 | `__lock` | Close actual lazy-lock/error-exit graph and lock pointer/API provenance |
| `0x00646685` | 151 | `__mtinitlocknum` (160 source) | Whole allocator/errno/free cycle and embedded finally; no 151-byte truncation |
| `0x00644187` | 195 | `_doexit` | Full lock/onexit/flag graph, cleanup labels and actual callback ABI |
| `0x0064228D` | 37 | `__amsg_exit` | Actual exit-policy pointer and full banner/writer/termination bindings |
| `0x00648C70` | 375 | `__NMSG_WRITE` | Complete error table/format/import/security-cookie graph |
| `0x00648E11` | 57 | `__FF_MSGBANNER` | Actual mutable policy fields and independent whole writer dependency |

Use R115–R119 manifests and `.analysis/r114-startup-graph.json` diagnostically.
Close the real cycle as a complete source/data/API graph rather than assuming
that a named child or source fingerprint grants ownership. Required cookie
failure (49 source/48 candidate), security-error handler (328), exit wrappers,
onexit initializer, allocator/TLS roots and their data definitions may expand
the graph. Reconcile all full source extents and interior/scope labels first.
Retain actual callback input ABI and independently prove storage/registration;
user callback implementations gain no origin merely from a runtime call.
Keep non-inventoried handlers outside candidate counts. `__c_exit` at
`0x0064427B` remains outside credit until its boundaries/dependencies are
reconciled. PE entry, cinit and thread-startup parent retain pending diagnostics.
Do not repeat the allocator or lifetime ambiguities without new dependencies.

Retain the R108 five lifetime ambiguities, R114 26-byte initializer ambiguity,
unknown external string/throw/allocation contexts and unresolved insertion/
catch spans. Preserve the three interior candidates of the older string
`_Copy` COMDAT and its full enclosing body.

Run the preflight and refresh `.analysis/origin-scan/latest.json`. Query full
bodies, callers and callees locally through the attested Ghidra wrapper.
Cold-build independent VC7 source families serially, bind every relocation
and retain original-type uncertainty. The game caller grants no library or
compiler credit by itself. Keep `0x0040EC8A` as an unresolved interior catch/
tail candidate until its enclosing function and EH extent are reconciled.

The user authorized local investigation and verification for speed, followed
by one public MCP acceptance replay at the end. Preserve the no-auth route,
private path and 60-function exact baseline. R120 adds no exact scope. Update
the origin journal, knowledge base, progress card and handoff after acceptance;
run `scripts/repo-python scripts/ci.py` and `git diff --check` before committing
with `gpt-6.1-sol: ...`.


One final no-auth public HTTPS MCP request passed R114, retained R077/R113
dependency replays and R112 contexts, all 872 recorded authored extents,
target/project attestation, 178 public tests, progress freshness and
`git diff --check`. All 60 exact units / 9,883 bytes cold-replayed across
eleven objects. Investigation and intermediate verification used local
tools; the public acceptance request ran once.


One final no-auth public HTTPS MCP request passed R115, retained R114
including its R077/R113 dependency replays, R006/R025 archive anchors,
all 872 recorded authored extents, target/project attestation, 189 public
tests, progress freshness and `git diff --check`. All 60 exact units /
9,883 bytes cold-replayed across eleven objects. Investigation and
intermediate verification used local tools; the public acceptance request
ran once.

## Tooling and verification

Run repository Python through `scripts/repo-python`. TH075 has its own
Ghidra project and Bash + Ghidra MCP bridge, with pinned VC7.1/D3D8 tools
reused privately from TH095. The user-requested Tailscale Funnel endpoint
has no bearer authentication. Its random path is private in the ignored
`.tools/mcp_for_gptweb-ghidra/.env`; do not print or commit it. The latest
public HTTPS smoke test passed 15 checks, including Ghidra attestation and a
cold exact-unit replay. A separate public MCP request cold-replayed the new
F008 `animation-clear-byte40` unit exact. F009 then cold-replayed all nine new
units / 652 bytes through the same no-auth public route. See
[MCP operations](GHIDRA_MCP.md).

```bash
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/validate-tracking.py --require-target
scripts/repo-python scripts/report-reconstruction-status.py --summary
scripts/repo-python scripts/verify-authored-origins.py
scripts/repo-python scripts/verify-game-lifetime-origins.py
scripts/repo-python scripts/verify-game-context-origins.py
scripts/repo-python scripts/verify-deque-game-dependency-origins.py
scripts/repo-python scripts/verify-vendor-deque-erase-origins.py
scripts/repo-python scripts/verify-deque-postfix-context-origins.py
scripts/repo-python scripts/verify-event-queue-origins.py
scripts/repo-python scripts/verify-queue-lifetime-origins.py
scripts/repo-python scripts/verify-startup-dependency-origins.py
scripts/repo-python scripts/verify-runtime-error-origins.py
scripts/repo-python scripts/verify-security-eh-origins.py
scripts/repo-python scripts/verify-termination-lock-origins.py
scripts/repo-python scripts/scan-origin-candidates.py
scripts/repo-python scripts/verify-short-game-origins.py
scripts/repo-python scripts/verify-short-game-origins.py --cohort R102
scripts/repo-python scripts/verify-short-game-origins.py --cohort R103
scripts/repo-python scripts/verify-short-game-origins.py --cohort R104
scripts/repo-python scripts/verify-short-game-origins.py --cohort R105
scripts/repo-python scripts/verify-vendor-peer-origins.py
scripts/repo-python scripts/verify-effect-fighter-origins.py
scripts/repo-python scripts/verify-effect-forwarder-origins.py
scripts/repo-python scripts/verify-fighter-final-virtual-origins.py
scripts/repo-python scripts/verify-combat-reaction-origins.py
scripts/repo-python scripts/verify-fighter-script-origins.py
scripts/repo-python scripts/verify-vendor-deque-growmap-origins.py
scripts/repo-python scripts/verify-vendor-deque-operation-origins.py
scripts/repo-python scripts/verify-vendor-deque-helper-origins.py
scripts/repo-python scripts/verify-vendor-deque-callee-origins.py
scripts/repo-python scripts/verify-vendor-deque-allocation-origins.py
scripts/repo-python scripts/verify-fighter-script-accessor-origins.py
scripts/repo-python scripts/verify-vendor-deque-destructor-origins.py
scripts/repo-python scripts/verify-vendor-deque-access-origins.py
scripts/repo-python scripts/verify-vendor-deque-begin-origins.py
scripts/repo-python scripts/verify-vendor-deque-iterator-origins.py
scripts/repo-python scripts/verify-vendor-deque-const-iterator-origins.py
scripts/repo-python scripts/verify-vendor-deque-dereference-origins.py
scripts/repo-python scripts/verify-vendor-deque-iterator-advance-origins.py
scripts/repo-python scripts/verify-vendor-deque-comparison-origins.py
scripts/repo-python scripts/verify-vendor-deque-algorithm-origins.py
scripts/repo-python scripts/verify-vendor-deque-empty-origins.py
scripts/repo-python scripts/verify-vendor-deque-leaf-origins.py
scripts/repo-python scripts/verify-vendor-deque-cleanup-origins.py
scripts/repo-python scripts/verify-vendor-vector-storage-origins.py
scripts/repo-python scripts/verify-vendor-vector-helper-origins.py
scripts/repo-python scripts/verify-vendor-vector-operation-origins.py
scripts/repo-python scripts/verify-vendor-vector-callee-origins.py
scripts/repo-python scripts/verify-vendor-vector-copy-origins.py
scripts/repo-python scripts/verify-vendor-vector-wrapper-origins.py
scripts/repo-python scripts/verify-vendor-exception-origins.py
scripts/repo-python scripts/verify-battle-end-destructor-origin.py
scripts/repo-python scripts/verify-runtime-origins.py
scripts/repo-python scripts/verify-runtime-external-origins.py
scripts/repo-python scripts/verify-runtime-leaf-origins.py
scripts/repo-python scripts/replay-exact-units.py --unit sprite-geometry-set-four-dwords --unit animation-reset-primary-counters --unit animation-set-three-counters --unit animation-reset-secondary-counter --unit animation-clear-byte40 --unit game-set-clamped-value --unit battle-effect-clear-field74 --unit fighter-clear-notice-transition --unit aux-effect-clear-field8
scripts/repo-python scripts/replay-exact-units.py --unit sprite-scene-copy-vector --unit sprite-scene-dispatch-global-draw --unit text-rasterizer-decode-hex-digit --unit battle-hud-draw-selected-notice --unit fighter-is-grounded-state-window --unit fighter-configure-notice-text --unit fighter-begin-notice-transition --unit battle-state-start-hit-sequence --unit fighter-initialize-notice
scripts/repo-python scripts/update-progress.py --check
scripts/repo-python scripts/ci.py
git diff --check
```

The R109 session passed 146 public tests, target-required tracking,
complete checks of 864 explicitly recorded authored bodies / 1,948,490 bytes,
and progress freshness. Explicit aliases preserve all eighteen original
R104/R105 reviewed roles after F008/F009 adopted shorter exact names; the old
cohort verifiers now accept those recorded renames and matching states.
R108 cold-replays eleven complete source alternatives and two implicit cleanup
controls; R109 verifies thirteen game policies with mixed-origin dependencies.
The final no-auth public HTTPS MCP acceptance passed both new verifiers,
old R104/R105 replays, target-required tracking and 146 tests. A full cold
replay preserved all 60 exact units across eleven objects / 9,883 bytes.
No callee or dynamic dispatch receives origin credit from these callers.
The earlier deque algorithm, emptiness, short-helper, cleanup, vector
storage, vector helper, vector operation, vector callee, scalar copy and
vector wrapper, standard exception and battle-end destructor cold verifiers
passed through the no-auth public Funnel MCP.

R110 subsequently passed its complete 53-body source graph, retained R108/R109
evidence, all 864 authored extents, target/project attestation, 152 tests,
progress freshness and `git diff --check` through one final public MCP replay.
That request also cold-replayed all 60 exact units across eleven objects /
9,883 bytes. Local tools handled investigation and intermediate acceptance.

R111 passed all 337 complete source alternatives over its closed 129-body
graph, retained R110 evidence, 864 authored extents, target/project attestation,
157 tests, progress freshness and `git diff --check` through one final public
MCP request. It also cold-replayed all 60 exact units / 9,883 bytes across
eleven objects. The separate insertion candidate's provisional span includes
`0x00456137`; retain unknown origin until its enclosing extent and cleanup
tails have independent complete evidence.
One final no-auth public HTTPS MCP request passed R112, retained R111/R110
source graphs, all 866 authored extents, target/project attestation, 162 tests,
progress freshness and `git diff --check`. All 60 exact units / 9,883 bytes
cold-replayed across eleven objects. Investigation and intermediate checks
used local tools; the public acceptance route ran once.

One final no-auth public HTTPS MCP request passed R113, retained R112,
all 868 recorded authored extents, target/project attestation, 169 public
tests, progress freshness and `git diff --check`. All 60 exact units / 9,883
bytes cold-replayed across eleven objects. Investigation and intermediate
verification used local tools; the public acceptance request ran once.

The complete CRT external-dependency verifier also passed through that endpoint.
The twelve short game policies and full blend-mode context also replayed
successfully through the public MCP.
The eleven effect forwarders/fixed transforms also passed their complete
context and ABI verifier through that endpoint.
The R102 seventeen-function, R103 thirty-three-function, R104 sixteen-function
and R105 three-function cohorts passed through the no-auth public HTTPS MCP.
The R106 verifier cold-replayed seven independently reviewed VC7 families and
accepted 24 complete peer bodies through the same public MCP route.
R107 adds four complete pinned-archive runtime leaves / 199 bytes, including an
explicit FS:[0] relocation in `__setjmp3`; its verifier passed locally and
through the public route. The F008 18-byte animation clear helper also
cold-replayed exact through public MCP after the complete 15-check smoke test.
The complete F009 object subsequently cold-replayed 9/9 exact over public MCP.
The complete batch origin scanner also passed through that endpoint during this
F009 handoff and reproduced the then-current 1,311-candidate queues. The R113
refresh now covers 1,263 pending candidates in forty groups and 180 extent
questions; five known ambiguous lifetime wrappers remain in the strongest lane.
R084 had already replayed the earlier thirteen
deque cold verifiers and the fighter script accessor verifier over that
endpoint. Public GitHub CI for F009 passed the same 141-test suite in
[run 37121669326](https://github.com/N0zoM1z0/th075/actions/runs/37121669326).

## Origin backlog and retained evidence

Use [batch origin review](ORIGIN_BATCH_SCAN.md) and
`scripts/repo-python scripts/scan-origin-candidates.py` to refresh the private
shortlist for all 1,263 pending candidates. The current report groups 40 whole
bodies and isolates 180 extent questions. Start with grouped source/context
witnesses rather than one-address setup. R102 accepted seventeen explicit
game policies through the shared cohort verifier, with 33 independent whole
anchors and 15 complete parent edges; scan hits alone remain diagnostic.
R103 reused that verifier for thirty-three game state/record policies with
22 independent whole parents, 33 parent edges, seven raw PE import bindings,
two unresolved virtual dispatches and four readonly float scalars. R104 adds
sixteen small game helpers / 806 bytes using complete parents, callees and
selected policy instructions. R105 closes three dependencies exposed by that
batch / 365 bytes. The batches keep signed field widths, indexed record strides
and state limits explicit; lifetime-only and generic helper hypotheses remain
pending. R106 resolves the former 24-member reviewed-peer lane through seven
source-reviewed VC7 vector/deque families; actual call destinations and RET
cleanup remain part of each comparison. The R109 refreshed scan has five candidates
in the strongest combined game-callee/parent lane, 155 in the game-parent lane
and 182 extent questions. The five strongest candidates have verified lifetime
ambiguity in R108 and cannot gain credit from that ranking.

Twelve repeated 520/517/511-byte bodies are now verified as complete VC7
`std::deque::_Growmap` templates, including all 13 typed relocations per
body and internal control flow. The independently compiled record widths do
not identify the game's original element types. A scan of remaining pending
candidates found no further whole-body matches to these seven probe variants.
The earlier vector hypothesis for these bodies was wrong. Reproduce with
`scripts/repo-python scripts/verify-vendor-deque-growmap-origins.py`.
Forty-six further complete deque push/pop/cleanup bodies, 8,220 bytes,
have their own cold verifier and typed target bindings. The many shorter
STL-like matches remain diagnostic until their ownership is independently
resolved; an identical tiny body alone is insufficient. Another 97 complete
49–72-byte deque constructors and helper templates have 190 typed bindings
and a cold verifier. A 44-byte no-relocation allocator match remains pending.
Another 126 short, 20–29-byte deque helpers have both a complete cold
source match and a same-family call from an independently reviewed parent
template. Their 126 typed relocations and all parent call fields replay.
Short matches without this corroborating parent remain pending.
Twenty-two `std::_Allocate` helpers now have the same complete code and
parent-call chain, including their call from the R074 allocator wrappers.
The fighter script initializer and three byte/word/dword field getters are
now reviewed as authored through their complete bodies and independently
reviewed fighter callers. Twenty-four 19-byte deque destructor templates,
including the script owner's cleanup helpers, call verified VC7 `_Tidy`
functions. The adjacent composite cleanup body remains pending.
An independent seven-width `deque::at` probe now verifies 33 more complete
bounds-checked access and iterator bodies. The two 68-byte helpers used by
the script getters are among the seven verified `deque::at` methods.
Seven 35-byte `begin` helpers are now bound to those reviewed `at` callers;
six similar helpers without that parent witness remain pending.
Those seven reviewed `begin` calls in turn bind seven 32-byte iterator
constructors, which bind seven 33-byte const-iterator constructors. Each
link is checked against its complete parent body and typed call field.
Ten 19-byte iterator dereferences now bind to separately verified
const-iterator dereference bodies; same-shape calls to other functions
remain pending.
Nine 31-byte iterator advances are now backed by the reviewed iterator
addition calls. Seven 27-byte variants do not match the current probe and
remain pending.
The independent iterator-operations probe now verifies 30 complete
comparison, subtraction and `end` bodies, 1,576 bytes. Five `end` helpers
whose typed callee is not the verified iterator constructor remain pending.
The algorithm probe now verifies 54 complete loop, wrapper, pointer-category
and iterator-step bodies, 2,889 bytes with 108 typed relocations. Every short
body has a source-typed parent or callee witness. Three other iterator-step
lookalikes without that witness remain pending. The 85-byte `0x00420050`
script-adjacent helper is one of the verified STL copy loops.
Thirteen 25-byte `deque::empty` bodies now have complete no-relocation
source matches and exact source-typed calls from cold-reverified R072
operation parents. Their original game element types remain unknown.
Another 64 allocator constructors, pointer-category helpers and trivial
destruction-range bodies now have full source matches and source-typed
calls from cold-reverified R073 parents. These 5–16-byte bodies are library
templates; short matches without the caller witness remain pending.
Sixteen converting allocator constructors and twenty-two trivial `_Destroy`
bodies now have whole source matches and exact source-typed calls from
cold-reverified R074 parents. Other nontrivial destruction bodies still
need a complete source/target binding and remain pending.
The vector operation probe now verifies ten complete `_Buy` and eight
complete `_Tidy` bodies, 2,098 bytes with 46 typed relocations. Vector
insertion's complete bodies differ from this probe and remain pending.
Seventy-two short vector/allocator helpers now have full source matches and
typed call chains to those storage bodies. The verifier rejects unanchored
or circular chains; public graph tests also check wrong callee symbols and
missing storage anchors. Original game types remain unknown. The imported
`_String_val` labels on some base constructors are not evidence for their
source identity; the reviewed vector calls support `_Vector_val` here.
Other short matches still need separate complete comparisons and typed
caller/callee witnesses.

Eleven complete construction helpers, four backward-copy helpers and two
vector insertion wrappers now have their own cold comparison: 1,057 bytes
and 26 typed relocations. The construction and copy helpers bind to
independently reverified placement-new and CRT `memmove` bodies. Eight short
vector/iterator callees now have complete source comparisons and rooted
parent calls. Eight copy wrappers also match completely and bind to
independently cold-replayed copy implementations; the wrapper's source
variant is checked against the entire callee even when the earlier probe
used a different synthetic record name. These sixteen bodies total 660
bytes with 21 typed relocations. Equal-shape `begin` and `end` bodies cannot
exchange source identities. The complete `_Insert_n` body remains pending.

Four more complete scalar copy wrappers, 204 bytes and eight relocations,
bind to complete 49-byte copying callees. Those already-reviewed callees
reproduce both `_Uninit_copy` and `_Copy_opt` source variants, including
the single typed `memmove` call. The library origin stays valid, but their
original specialization and whether linker folding occurred remain
unknown. The new verifier passed through the no-auth public Funnel MCP. It
cold-replays the earlier callee evidence and
CRT anchor, then compares the full wrappers and alternative callee bodies.

Four vector assignment wrappers, four iterator additions and three
allocator construction wrappers now have complete same-family callee
witnesses: 383 bytes with eleven typed calls. The verifier passed through
the no-auth public Funnel MCP. The earlier callee evidence
and every new exact source variant cold-replay. The iterator callees use
existing complete no-relocation alias evidence; these calls do not infer
the game's original element type. Three short exception methods now have
complete source, vtable, weak-fallback and named throw-metadata evidence:
the 37-/28-byte `std::out_of_range` message constructor/destructor are
library; its 37-byte implicit copy constructor is compiler generated.
The complete verifier passed through the no-auth public Funnel MCP.
The initial `length_error` shape hypothesis was insufficient: the complete
type descriptor names `out_of_range`, and its CatchableType binds the
actual copy constructor. Ten context bodies, two whole vtables and four
whole type-data COMDATs cold-replay. Same-shaped game scene methods retain
independent ownership and are not library functions.

The remaining 28-byte scene lookalike at `0x00424F40` is now reviewed as
authored. Its complete explicit-destructor source shape binds the vtable
written by the reviewed battle-end scene initializer, two observed virtual
slots, and the reviewed scene-base game cleanup. The implicit destructor
probe emits a distinct 19-byte body. The verifier cold-replays the cleanup
and deleting witnesses and the explicit/implicit source probe; the full
class layout and original destructor spelling remain unknown. The two
checked vtable slots do not establish a complete vtable extent.

Five additional whole CRT functions now have an external-dependency verifier:
`_time`, `___sbh_alloc_new_group`, `__fpclass`, `__decomp` and
`__ms_p5_test_fdiv`. Their twelve typed fields bind four independently replayed
callee bodies, two raw-PE imports and six complete readonly scalar references.
The verifier re-extracts each hash-pinned archive member and uses the function's
own auxiliary extent. Tiny code shapes, guessed IAT labels and zero-value
storage are insufficient ownership evidence. Original archive/link flags
remain unknown.

The same CRT external verifier now includes the complete 220-byte locale
parser `___lc_strtolc`, whose four calls bind reviewed CRT bodies and whose
remaining field binds the entire four-byte readonly delimiter string COMDAT.
The readonly check preserves all section definitions and rejects prefixes.

Twelve complete short game policies are now reviewed across camera, primary
frame capture/compositing, scene input and transitions, HUD defaults, character
sound/bindings and effect loading. Their verifier checks 27 whole independent
game anchors, complete parent calls, explicit fields, raw PE imports, callback
and selected virtual slots. It cold-replays the entire 495-byte blend-mode
unit, including its eight-entry table. Names and object layouts remain
inferred/incomplete; these origin decisions add no source or exact credit.

Eleven further complete effect forwarders and fixed background transforms
now bind eight whole independent game anchors. Preserve the distinct
20-/24-byte RET cleanup of the two similar 57-byte auxiliary forwarders,
including the unused incoming stack argument. The four transforms copy
132 bytes after fixed scale/rotation and choose two observed color words;
the midpoint helper divides signed coordinate sums by the readonly `2.0f`.
These facts do not establish complete game class layouts or original types.

The destructor-shaped candidate `0x00412E50` remains pending. R108 resolved
`0x00449D40` using whole explicit/implicit source controls and paired lifetime
context; its reviewed game cleanup call alone was insufficient. Five other
R108 wrappers remain ambiguous despite complete source/context evidence.

The CRT survey at `.analysis/crt-origin-survey.json` contains 353 historical
relocation-bearing observations. R093 resolved the complete 344-byte
`__ld12cvt` and its 27-/25-byte `__CopyMan` and `__IsZeroMan` helpers from
the pinned CRT archive. All nine direct calls bind to separately complete
vendor bodies, including the previously reviewed rounding and shift
helpers. The runtime verifier now checks 57 complete bodies and 28 typed
calls, plus the three local CRT anchors. The complete runtime verification
also passed through the no-auth public Funnel MCP. Other survey observations remain
diagnostic. A source fingerprint alone does
not establish each relocated callee or data binding. The metadata-vector
and other stream-deque probes likewise remain diagnostic. The 2,301-byte
`0x00420880` script parser was reviewed in R070 using the complete guarded
remap dispatch, even though Ghidra did not recover it. Preserve unknown
classifications until a complete
source/target binding or game-owner witness is available.

Continue the bounded R114 startup/shared-lifetime cohort described above. F008 and F009 remain
the accepted exact baseline; do not infer ownership from scanner hits alone.
The R105 rectangle-corner builder at `0x00427500` remains diagnostic: its
natural source differs at two local stack-slot bytes and has no exact credit.

One final no-auth public HTTPS MCP request passed R116, retained R115 and
R114 including R077/R113 dependency replays, R006/R025 archive anchors,
all 872 recorded authored extents, target/project attestation, 202 public
tests, progress freshness and `git diff --check`. All 60 exact units /
9,883 bytes cold-replayed across eleven objects. Investigation and
intermediate verification used local tools; the public acceptance request
ran once.

One final no-auth public HTTPS MCP request passed R117, retained R116/R115,
R006/R025 runtime anchors and all PE import thunks, retained R114 including
R077/R113 dependency replays, all 872 recorded authored extents, target/project
attestation, 217 public tests, progress freshness and `git diff --check`.
All 60 exact units / 9,883 bytes cold-replayed across eleven objects.
Investigation and intermediate verification used local tools; the public
acceptance request ran once.
