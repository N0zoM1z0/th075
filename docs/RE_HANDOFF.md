# TH075 function reconstruction handoff

Updated 2026-10-05. Work resumed with origin-review batches R070–R107, moved to
exact reconstruction for F008 and F009, and has now completed bounded origin
review cohorts R108 through R175. The public
repository is [N0zoM1z0/th075](https://github.com/N0zoM1z0/th075) on
`main`. Commit subjects use `gpt-6.1-sol: ...`. Keep documentation in English.

## Verified checkpoint

The pinned target is the supplied Japanese `th075.exe` (reported `ver1.11`),
SHA-256 `bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
The initial Ghidra inventory has 4,351 provisional candidates. Origin review
has resolved 3,608: 930 authored, 2,103 library and 575 compiler generated.
There are 743 pending. Candidate count is not authored function count.

The exact baseline is 60 source-present and exact functions, covering 9,883
bytes across 60 match units. Exact coverage of the currently reviewed authored
bytes is 9,883 / 1,966,340 (0.50%). This denominator is provisional because
origin review is incomplete. F008 adds nine reviewed game leaf helpers / 315
bytes; F009 adds nine game policy and dependency helpers / 652 bytes. The
current strategy is origin review. Preserve the exact baseline while resolving
the bounded R176 iterator-wrapper cohort below.
Both the complete-origin and 50%-exact milestones remain unfinished.

The canonical state lives in `config/functions.csv`,
`config/function-origins.csv`, the origin evidence CSVs and the exact
match-unit manifests. The progress SVG is generated from those ledgers.
[Origin review](ORIGIN_REVIEW.md) records the evidence and boundaries for
R001–R175; the [knowledge base](KNOWLEDGE_BASE.md) records accepted facts.
The former chronological handoff is preserved in
[handoff history](RE_HANDOFF_HISTORY.md); its earlier counts and next-step
notes are historical snapshots.

## Next agent objective — R176 iterator arithmetic wrappers

R175 accepts three whole explicit resource-release policies / 286 bytes and
ten whole SDK list cleanup definitions / 644 bytes. Replay
`scripts/repo-python scripts/verify-resource-release-policy-origins.py`.
Full R017/R045 policies / 1022 bytes, three original R020 frames and three
whole R037 deleting parents preserve independent context. Two complete custom
destructors reproduce all 98/83 target bytes; the entire 105-byte character
policy is reviewed from target control flow and complete small 99/75-byte
source call-order alternatives, with no source-byte-match credit. All 28 whole
positive controls / 1085 bytes compare unmasked with 56 real fields. All 52 cold
ordinary sections / 1858 bytes, 28 SDK headers, whole 44-byte layout, 68 canonical/
body snapshots and five prior records are frozen. Opaque node-link getters,
five-byte destruction children and all previously protected owners remain
independently unknown. All 1932 public checks pass; 883 authored bodies and all
60 exact functions are preserved. Public MCP acceptance remains waived; the
full remaining-origin goal remains active and unfinished.

The fresh `.analysis/origin-scan/r175-triage.json` has 743 pending. The next
bounded diagnostic cohort is four iterator wrappers / 108 provisional bytes:

| Candidate | Entire provisional bytes | Whole original R078 parent / R083 child |
| --- | ---: | --- |
| `0x0041F650` | 27 | `0x0041ED00` / 57 and `0x0041F630` / 31 |
| `0x0041F6F0` | 27 | `0x0041EE60` / 57 and `0x0041F6D0` / 31 |
| `0x00455D10` | 27 | `0x00455C60` / 57 and `0x0042E2D0` / 31 |
| `0x005F9530` | 27 | `0x005F8D70` / 57 and `0x005F9510` / 31 |

These are candidates, not promised acceptances. Inspect complete CFG, actual
arithmetic/argument propagation and full existing evidence before selecting
SDK and ordinary alternatives. Parent/child classifications or shared shapes
alone do not establish origin. Derive each vector/deque family and element
width from its own entire source and target graph; do not inherit widths from
adjacent review cohorts. Compare entire source extents with every genuine field
and preserve all earlier manifests, opaque ownership and exact inputs. Continue
origin review; exact credit remains 60.

## R165 checkpoint and the completed R166 shortlist

R165 accepts the two complete allocator destroy wrappers / 50 bytes through
the unchanged R164 deque-pop parents. Replay
`scripts/repo-python scripts/verify-allocator-destroy-origins.py`. Its new cold
object supplies 13 full controls / 536 bytes and 12 real unmasked fields;
four ordinary alternatives / 70 bytes are byte-equal. The actual 15-/5-byte
destruction children and separate 72-byte lifetime policy remain unknown.
All 61 ordinary sections / 2472 bytes, 28 SDK headers plus the original pinned
R164 probe include, and the complete combined 68-byte readonly layout are
retained. The R164 manifest stays immutable; its verifier permits only the two
exact R165 original-to-accepted snapshot transitions and cold-replays successfully.
All 1591 public checks pass. No source/private ABI/mapping/exact credit is added.

The fresh `.analysis/origin-scan/r165-triage.json` has 840 pending candidates.
The next bounded R166 cohort is four unresolved game-parent context candidates
/ 600 provisional bytes. Scanner associations are diagnostic, not acceptances:

| Candidate | Full provisional extent | Independent whole authored parent to retain |
| --- | ---: | --- |
| `0x00410F30` | 104 | R045 fighter resource loader `0x00456B60` / 1186, actual call `0x00456F92` |
| `0x0045B760` | 203 | R050 Reimu object initializer `0x004769B0` / 134, actual call `0x004769BA`; other character callers remain independent |
| `0x0045B920` | 131 | R045 fighter state initializer `0x004567B0` / 345, actual call `0x00456894` |
| `0x005F7140` | 162 | R065 battle character loader `0x004176F0` / 3232, actual call `0x0041835F`; retain its full guarded switch data |

Read whole candidate CFG, every call/data/virtual field, and full independent
parents. Distinguish explicit game policy from SDK and compiler-generated
alternatives using natural complete source controls where needed. A game parent
or reviewed library child alone grants no ownership. Do not instantiate an
incomplete game owner. Preserve all accepted evidence and protected
R108/R158/R161/R162/R163/R165 lifetime/copy/math/destruction ambiguities.
The full origin-review goal is active and unfinished; no exact scope is added.

## R164 checkpoint and the completed R165 shortlist

R164 accepts five complete SDK dependencies / 504 bytes through unchanged
whole R074/R072/R033 library parents. Replay
`scripts/repo-python scripts/verify-sdk-dependency-origins.py` with the immutable
`config/sdk-dependency-origin-evidence.json`. Its one cold source object supplies
39 complete code/EH/data controls / 1988 bytes and 57 actual unmasked fields:
37 whole positive comparisons / 1686 bytes and two whole ordinary-pop negative
comparisons / 302 bytes. Five ordinary controls / 252 bytes are byte-equal;
each complete ordinary pop differs at eight local-stack displacement bytes.
The entire backward-copy alternative is 48 bytes versus the actual forward
worker's 50 bytes. These alternatives alone do not identify original ownership.
All 55 ordinary sections / 2360 bytes, 28 actual SDK headers, full 60-byte
observation layout and complete placement cleanup/handler/state are retained.
Only the five bounded origins/function rows change. All previous evidence,
unknown record/lifetime/copy/math policies and the exact baseline are preserved.

The fresh `.analysis/origin-scan/r164-triage.json` has 842 pending candidates.
The next bounded R165 cohort is two unresolved allocator destruction wrappers
/ 50 provisional bytes:

| Candidate | Complete provisional extent | Independent whole accepted parent | Actual child, independently unresolved |
| --- | ---: | --- | --- |
| `0x00422610` | 25 | R164 deque pop `0x00422290` / 151 | `0x004229C0` / 15 |
| `0x0042E390` | 25 | R164 deque pop `0x0042E120` / 151 | `0x0042E580` / 5 |

These are diagnostic candidates, not promised acceptances. Cold-build complete
SDK and ordinary source controls; reconcile every actual field and whole own
extent. Preserve the 15-/5-byte child ownership and the separate 72-byte
`0x004212A0` lifetime ambiguity. The latter is reached through the retained R037
compiler deleting wrapper; that relationship does not classify the game policy.
Retain the original R164 snapshot/manifest and exact accepted parent rows. If a
new bounded transition is accepted, permit only that exact original-to-new row
transition in earlier snapshot readback; do not loosen unrelated preservation.
Do not instantiate an incomplete game class or add exact scope. The full
remaining-origin goal remains active and unfinished.

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

R120 closes the complete allocator/lock/error/termination cycle: eighteen
complete library source bodies / 1,928 bytes / 166 typed fields, plus five
existing interior labels / 50 overlapping bytes. Replay
`scripts/repo-python scripts/verify-runtime-cycle-origins.py`. It compares the
complete own source and every field, genuine defining state / COMMON storage,
full literals and all seven EH scopes, then cold-replays R119 and retained
runtime/import/layout controls. Canonical extents expand only for lazy-lock
151 -> 160, heap allocation 111 -> 123 and report_failure 48 -> 49. Historical
R115–R119 snapshots retain their earlier decisions through narrowly checked
same-source reconciliation. Internal labels remain unnamed and receive no
standalone-source or exact credit. Target and Ghidra database are unchanged.

Final acceptance passed in one no-auth public HTTPS MCP request: the full
R120 verifier and retained R119/R118/R117/R116/R115/runtime/import graphs,
R114 lifetime evidence, all 872 recorded authored extents, target/tracking/
Ghidra attestation, 266 public tests, progress freshness and diff whitespace.
All 60 exact units / 9,883 bytes cold-replayed across eleven objects.
Investigation and intermediate verification used local tools.

The whole MT initializer remains diagnostic; its API lookup/fallback context
supports getptd without accepting its other children. Optional new-handler,
user security handler and debug-message callbacks retain actual source storage
and call ABI without classifying their implementations. Callback registration
also grants no application origin. PE entry, cinit and other startup parents
remain pending until every binding has independent evidence.

R121 resolves ten complete library bodies / 917 bytes / 71 typed fields:
fast error exit, lock deletion, MT teardown, atexit/onexit and its mutation
helper, realloc, msize and the paired exit-lock wrappers. Three existing
interior candidates / 24 overlapping bytes are library source labels only.
Replay `scripts/repo-python scripts/verify-startup-registration-origins.py`;
it cold-replays R120 and all retained runtime/import/layout graphs. Onexit
expands 50 -> 56 and msize 106 -> 118. Complete EH heads and later shared
entries remain distinct. No database, target, source or exact state changes.

Final acceptance passed in one no-auth public HTTPS MCP request: the full
R121 verifier and retained R120/R119/R118/R117/R116/R115/runtime/import graphs,
R114 lifetime evidence, all 872 recorded authored extents, target/tracking/
Ghidra attestation, 282 public tests, progress freshness and diff whitespace.
All 60 exact units / 9,883 bytes cold-replayed across eleven objects.
Investigation and intermediate verification used local tools.

Two complete startup parents / 345 bytes remain pending: mtinit needs the
327-byte non-inventoried fiber-cleanup parent's locale ownership graph;
cinit needs complete FP conversion/precision children. Seven full diagnostic
contexts / 748 bytes preserve the actual next dependencies. The two existing
fiber-cleanup interior candidates stay unknown. Whole FP carrier / 20 bytes,
RTC scope and empty marker range are frozen diagnostics, not parent credit.

R122 resolves five complete locale/thread library candidates / 1,159 bytes /
120 typed fields and two existing fiber-cleanup source labels / 18 overlapping
bytes. The complete 327-byte fiber callback / 21 fields is independently
closed without inventing a primary candidate. Replay
`scripts/repo-python scripts/verify-locale-thread-origins.py`; it cold-replays
R121 and all retained runtime/import/layout graphs. No candidate extents,
database, target, authored source or exact ledgers are changed.

The complete defining graph includes 2,092 source data bytes, five actual
COMMON objects, two full scopes and 47 readonly literals / 313 bytes. Natural
CRT layout control / 220 bytes proves thread 140, multibyte 544, locale 84,
lconv 48 and time 184; thread pointers are +96/+100. Whole 403-byte initial
locale/cache data, 56-byte lconv carrier, 1,284-byte ctype/wctype source and
184-byte time default bind every initialized field to actual full definitions.
R121 keeps its historical pending snapshots through narrow same-source guards.

One final no-auth public HTTPS MCP request passed R122, cold-retained R121
and all R120/R119/R118/R117/R116/R115/runtime/import/layout dependencies,
retained R114 including R077/R113 replays, all 872 recorded authored extents,
target/project attestation, 300 public tests, progress freshness and
`git diff --check`. All 60 exact units / 9,883 bytes cold-replayed across
eleven objects. Investigation and intermediate verification used local tools;
the final public acceptance request ran once.

R123 closes all six multibyte/codepage handoff roots plus nine necessary NLS/
locale callees: fifteen complete bodies / 3,970 bytes / 209 fields and three
existing interior labels / 27 overlapping bytes. Replay
`scripts/repo-python scripts/verify-codepage-nls-origins.py`; it cold-retains
R122 and all earlier runtime/import/layout controls. Candidate extents 327/ 99/50
are reconciled to source 336/111/59, preserving every cleanup and return.

The complete defining graph includes twelve sections / 2,296 bytes, eight
COMMON objects / 545 bytes, six scopes / 96 bytes and forty-four literals /
267 bytes. Full 248-byte source codepage carrier and 257-/256-/12-byte arrays
are independently bound. Natural SDK/CRT control / 172 bytes proves CPINFO 20,
MEMORY_BASIC_INFORMATION 28, SYSTEM_INFO 36, record 48, locale handle +12 and
all conversion/guard constants. The two NLS flavor branches, five exception
filter/handler pairs, stack recovery, heap fallback and entire locale cycle close.
R115/R122 retain frozen pending snapshots through strict source identity guards.
No game source/header, exact ledger or database changes are made.

One final no-auth public HTTPS MCP request passed R123, cold-retained R122
and every earlier runtime/import/layout graph, retained R114 including R077/
R113 replays, all 872 recorded authored extents, target/project attestation,
322 public tests, progress freshness and `git diff --check`. All 60 exact
units / 9,883 bytes cold-replayed across eleven objects. Investigation and
intermediate verification used local tools; the final public request ran once.

R124 closes 27 complete library candidates / 4,252 bytes / 142 fields, five
whole non-inventoried controls / 230 bytes / ten fields, and the actual FP
conversion/control dependency graph. Replay
`scripts/repo-python scripts/verify-floating-point-origins.py`. The parser's
provisional 1,028-byte code prefix becomes its whole 1,076-byte source extent:
all twelve embedded table entries, unsigned guard and actual indexed jump close.
Six-slot initial trap and registration pointers, whole 20-byte FPinit carrier,
700-byte mutable powers, 48-byte formats, division flags and every locale/data
pointer are independently verified. Complete natural FP and locale/API layouts
cold-build 196 bytes; twenty-four prior anchors and the full R123 chain replay.
The MP API provenance and R098 fallback remain explicit. No exact scope is added.

Cinit / 106 remains unknown. Its three unresolved XI callbacks are SSE2 init,
stdio init and C++ unhandled-exception filter registration. Complete FP children
and empty RTC termination range do not grant parent credit. The two latter
initializers have no primary inventory entry and must close without invented
candidates. R121 preserves its old pending cinit source through a narrow guard.

The final no-auth public HTTPS MCP replay passed R124, retained R123 and every
earlier runtime/import/layout graph, retained R114 including R077/R113 controls,
all 872 recorded authored extents, target/project attestation, 347 public tests
and progress freshness. All 60 exact units / 9,883 bytes cold-replayed across
eleven objects. A narrow public follow-up confirms corrected documentation EOF
whitespace, `git diff --check` and final progress/status. The complete cold
acceptance replay ran once; investigation and intermediate checks were local.

R125 resolves all six initializer handoff roots plus five necessary exception/
signal callees: eleven complete library bodies / 1,545 bytes / 77 fields and
one existing raise cleanup label / 13 overlapping bytes. Replay
`scripts/repo-python scripts/verify-initializer-startup-origins.py`. All actual
XI callbacks and source registration cells, full XC compiler evidence and FP/RTC
ranges now close cinit / 106. The two newly closed non-inventoried initializers /
188 bytes and two retained R124 controls / 69 bytes add no inventory candidates.

Whole defining data / 824 bytes, COMMON / 4,372 bytes, scopes / 60 bytes,
CRT markers / 32 bytes, registrations / 24 bytes and all actual callback ranges /
100 bytes are checked. Full twenty-record iob, 64-pointer pioinfo, 4,096-byte
stdin buffer, signal-action section and 136-byte exception-action/count carrier
retain actual source and loader geometry. Natural IO/thread/exception/SDK layout
cold-builds 292 bytes. Complete CPUID/OSFXSR, IO failure, callback validation,
terminate/abort/raise, FPE dispatch and finally paths are preserved. The earlier
EH head +307 and shared cleanup +315 are distinct. R121/R124 pending cinit
snapshots retain strict same-source guards; canonical cinit is now library.

The final no-auth public HTTPS MCP acceptance passed R125, the full retained
R124/runtime/import/layout chain, cold R024 static emissions, retained R114
including R077/R113 controls, all 872 authored extents, target/project attestation,
372 public tests, progress freshness and git diff whitespace. All 60 exact units /
9,883 bytes cold-replayed across eleven objects. Investigation and intermediate
verification were local; the full public acceptance replay ran once.

R126 resolves those six environment/startup roots and five necessary parser,
lead-byte and exit wrappers: eleven complete library candidates / 2,033 bytes /
100 typed fields. The full 469-byte supplied PE entry closes through every
actual child, both PE32/PE32+ paths, its complete local filter/handler and the
independently authored R113 WinMain callee / 2,987 bytes / stdcall cleanup 16.
Replay `scripts/repo-python scripts/verify-environment-startup-origins.py`.
The complete 15-byte c_exit has no inventory candidate and earns no count.

Seven whole defining sections / 1,777 bytes, four actual COMMON / 269 bytes,
whole EH scope / 12 bytes and empty literal / one byte retain source and loader
provenance. Program-name BSS is 261 bytes, mbctype COMMON is 257, aenvptr's
complete selected startup section is 12. The standard parser / 364 is fully
reviewed; the 405-byte wildcard source is rejected. All exception/FPE/optional
handler and environment/API failure/cleanup paths remain complete. Nineteen
independent vendor anchors / 2,675 bytes / 173 fields retain original evidence.
Natural SDK/vendor controls cold-build 220 bytes, including both managed-image
layouts. R114/R115 snapshots retain narrowly bounded original-identity guards.

The final public HTTPS MCP acceptance passes R126 and retained R125/R114
runtime/compiler/game/import/layout graphs, authored extents, project attestation,
396 public checks and progress/whitespace checks. All 60 exact units / 9,883
bytes cold-replay across eleven objects. Investigation and intermediate checks
are local; the public acceptance replay runs once.

R127 resolves all six dispatch roots and necessary dependencies: nineteen full
library primaries / 2,608 bytes / 56 fields and four existing shared entries /
350 overlapping bytes. Replay `scripts/repo-python scripts/verify-fp-dispatch-origins.py`.
The 72-byte ctrandisp2 provisional extent now retains its entire 406-byte source
owner. Three auxiliary controls / 393 bytes / eight fields have no inventory
candidate. Seven independent anchors / 462 bytes / 17 fields retain their origins.

Both complete actual atan2 callers supply the whole 80-byte, sixteen-entry table.
Every DIR32 entry binds an actual source label within a whole reviewed owner;
the complete FXAM tag classifier and both JMP [EBX] tails retain provenance.
Same-section shared tails require original source-relative offsets. Eleven full
data sections / 336 source bytes retain member-local constants, folded zero
COMDATs, state, loader BSS and typed pointers. The full IEEE/matherr/RaiseException
graph and natural 352-byte SDK/CRT controls retain 112-byte IEEE record layout
and real bitfields. No incomplete game layout, new source or exact scope follows.

The final public HTTPS MCP acceptance passes R127 and retained R126 runtime/
compiler/game/import/layout graphs, authored extents, project attestation,
427 public checks, progress freshness and git diff whitespace. All 60 exact
units / 9,883 bytes cold-replay across eleven objects. Local investigation and
intermediate checks precede one final public acceptance replay.

R128 resolves those six roots and three existing C entries: three complete
library primaries / 534 bytes / 41 fields, plus six existing overlapping entries /
474 bytes. Replay `scripts/repo-python scripts/verify-elementary-math-origins.py`.
The 20-byte cos/sin/sqrt prefixes expand to complete AUX extents 174/174/186.
Named C entries are +20; unnamed computation entries are +29, proved by full
source/target calls at +11, C-entry fallthrough and instruction starts. They
earn no standalone source/exact bytes or fabricated COFF definitions.

The complete thirteen-byte fast_exit has no independent candidate. Six whole
data sections / 136 bytes preserve actual common constants, fastflag BSS,
indefinite carrier and three distinct member-local names. Complete trigonometric
range reduction, sqrt sign/zero/NaN/invalid paths, saved control state and every
normal/fast/error dependency close through six independent anchors / 239 bytes /
three fields. Natural 48-byte vendor controls verify ABI and operation 18/30/5.
Retain complete R127 and independent R107 controls. The final public HTTPS MCP
acceptance passes 453 tests, attestation, authored extents, progress/whitespace
and all 60 exact units / 9,883 bytes cold across eleven objects.

R129 reviews all six roots: five gain library origin, abs remains unknown, and
four necessary callees also gain library origin. Eight complete primaries / 839
bytes / 38 fields and one existing vector cleanup / 24 overlapping bytes close
through fourteen whole independent anchors / 1,762 bytes / 43 fields. Replay
`scripts/repo-python scripts/verify-short-runtime-origins.py`. The vector's whole
96-byte sole defining code section has no function AUX and expands its original
72-byte prefix; ArrayUnwind expands 47 to its full 94-byte own AUX extent.

Thirty-five full defining sections / 423 bytes / 32 fields include the entire
29-entry operation/name carrier, every whole string COMDAT and both SEH scopes.
Thread seed +20, full rand update/result, fabs normal/NaN/error, umatherr table
scan and complete vector traversal/callback/exception paths retain provenance.
Natural 80-byte vendor/synthetic controls and a full thirteen-byte member-call
control verify layouts and callback ABI. The original callback implementations
and game element types remain unknown. Final public acceptance passes 483 tests,
attestation, authored extents, progress/whitespace and all 60 exact units /
9,883 bytes cold across eleven objects through the complete retained R128 chain.

The eleven-byte `0x00641DAA` remains pending. Both whole abs/labs definitions
and cold ordinary int/long expressions emit identical bytes. Actual game calls
and complete runtime neighbors cannot identify source ownership, type, spelling
or folding. Do not promote it from archive/scanner rank; replay its frozen
negative controls with the R129 verifier. The separate eleven-byte `0x00641FB8`
has the same diagnostic vendor alternatives and remains unreviewed/pending.

R130 resolves all six vector/two-argument math candidates and eight existing
callees: eleven library primaries / 2,511 bytes / 99 fields and three shared
entries / 644 overlapping bytes. The constructor's full sole code section is
98 bytes. The complete log10/ceil sections are 336/285 bytes, including every
own-AUX body and log10's source-emitted one-byte NOP. Canonical C extents are
63/64 only after whole-section replay; the old FID cos association is rejected.
The SSE log10 owner is 644 bytes with actual C/core entries at +24/+30. Its
whole coefficient carrier is 2,336 bytes. Nine complete auxiliary controls,
full EXP/fdiv tables and all 64 dispatch pointers close the actual graph.
The existing R127 `0x00646B43` entry retains its prior origin. Replay
`scripts/repo-python scripts/verify-vector-math-parent-origins.py`.

R131 resolves all six localtime/time-zone roots and fourteen necessary existing
entries: seventeen complete library primaries / 4,384 bytes / 237 fields and
three nine-byte cleanup entries. Both lock wrappers retain their full 76/62
bytes. The TZ reader's normal cleanup +539 and scope entry +534 remain distinct.
Its getenv branch closes through complete environment conversion/update and
NLS comparison parents. All 336 old MBCS-search bytes are reconciled through
own AUX / 123, seven target alignment bytes and a whole separate strchr section
/ 206. No auxiliary inventory candidate or padding credit is invented. Full
time/locale/environment carriers, four complete scopes and both COMMON definitions
replay. Cold layout controls verify tm/thread/MBCS/Windows timezone and all
actual offsets. Replay `scripts/repo-python scripts/verify-time-zone-origins.py`.

R132 resolves all six low-level file I/O roots and twelve existing dependencies:
fourteen complete primaries / 2,338 bytes / 109 fields and four cleanup entries
/ 33 overlapping bytes. Handle locking retains its entire 160-byte AUX, including
stack adjustment +148 and cleanup +151. The three wrappers retain +132 scope
entries and +135 cleanup subentries. Whole handle COMMON / 260, all 45 error
records, four scopes and the full application/exit carrier replay. The GUI
entry's actual source defines app_type; all five strong alternatives stay
explicit. Cold natural controls establish ioinfo / 36, lock / 24, thread error
offsets +8/+12 and cdecl EDX:EAX return. Replay
`scripts/repo-python scripts/verify-low-io-origins.py`. All 588 public checks and
one final public MCP acceptance pass; all 60 exact units cold-replay across
eleven objects. The R132 checkpoint was 3,320 resolved, with 1,031 pending.

R133 resolves all six stream buffer/close roots and one existing eight-byte
cleanup: six complete primaries / 879 bytes / 29 fields. Close retains its full
155-byte AUX, actual +116 scope entry and +119 cleanup label. All twenty FILE
records / 640, badioinfo / 36, defining cflush BSS / 4 and full scope / 12 replay.
Three COMMON declarations cover input buffer / 4096, handle pointers / 256 and
nhandle / 4. Natural controls verify complete FILE / 32, field offsets, inline
fallback, narrow-byte return and typed cdecl pushback call. Eleven complete
anchors retain the whole R132/R125 code/data/API/EH graph. Replay
`scripts/repo-python scripts/verify-stream-buffer-origins.py`. All 621 public
checks and one final public MCP acceptance pass; all 60 exact units cold-replay
across eleven objects. Canonical totals are 3,327 resolved, with 1,024 pending.

R134 resolves all six output-format roots and four required existing dependencies:
ten full primaries / 2629 bytes / 50 fields. Output retains its own complete
2042-byte AUX, comprising 2010 code bytes and a 32-byte eight-case dispatch.
Three non-inventoried FP helpers / 161 bytes receive no candidate credit.
Fifty-six whole data sections / 2361 bytes / 68 fields and fifteen independent
anchors / 1195 bytes / 65 fields retain complete source/data/callback provenance.
Both initial six-fatal-stub FP slots and the complete R124 initializer's six
writes replay. Separate 136-/52-byte natural format/locale layouts preserve
real vendor types and actual private helper register contracts. Replay
`scripts/repo-python scripts/verify-output-format-origins.py`. All 659 public
checks and one final public MCP acceptance pass; all 60 exact units cold-replay
across eleven objects. Canonical totals are 3337 resolved, with 1014 pending.

R135 resolves all six input-format/locale roots and four required existing
classification/NLS dependencies: ten full primaries / 4801 bytes / 129 fields.
Input retains all 3452 bytes, including its filter and allocation handler.
Three full SEH records bind actual -1/filter/handler entries, stack restoration
and the full R123 reset worker. Fifty-nine whole data sections / 2327 bytes /
72 fields and twenty-three independent anchors / 2021 bytes / 71 fields replay.
The six-slot FP view retains initial stubs and actual initialized callbacks;
input uses +8 / fassign. Natural format/SDK layouts / 136 and 112 and complete
44-/26-/21-/42-byte ABI controls preserve pointer-varargs, real RET 16 multiply,
PF2 and SDK multibyte declarations. Replay
`scripts/repo-python scripts/verify-input-format-origins.py`. All 702 public
checks and one final public MCP acceptance pass; all 60 exact units cold-replay
across eleven objects. Canonical totals are 3347 resolved, with 1004 pending.

R136 resolves all six locale construction/category roots and seventeen required
existing dependencies: 23 complete primaries / 5949 bytes / 421 fields. The
six-record category table binds all actual initializer owners, with three
non-inventoried controls / 101 bytes / ten fields. All three installed-locale
registrations retain their real callbacks and RET 4. The complete 36-byte BSS
carrier retains the actual null/NT/API/fallback query pointer and nine call
sites; runtime selection remains unknown. The full stdcall fallback has RET 16.
There are 198 whole defining sections / 6378 bytes / 220 fields, five complete
COMMON declarations / 20 bytes and twenty-five independent anchors / 4402 bytes /
215 fields. Memcpy retains its entire 829-byte own AUX, seven code regions and
six whole tables. Replay
`scripts/repo-python scripts/verify-locale-construction-origins.py`. Natural
340-byte layouts and full 45-/17-/8-/24-byte callback/API controls preserve real
types. All 740 public checks and one final public MCP acceptance pass; all 60
exact units cold-replay across eleven objects. Totals are 3370 resolved and
981 pending. No source, mapping or exact credit is added.

R137 resolves all six locale/time-parent roots and the complete expandtime
worker: seven primaries / 3033 bytes / 100 fields. The existing nine-byte
finally entry remains within its full 346-byte setlocale parent; eight existing
candidates gain library origin with no source/mapping/exact credit. Both full
finally/exception scopes, actual unlock/filter/reset execution and date/time
API selection, capacity query and output calls replay. Seventy whole data
sections / 2582 bytes / 83 fields, five complete COMMON declarations / 20 bytes
and thirty-four independent anchors / 6576 bytes / 358 fields remain complete.
Natural 260-byte layouts and full 19-/35-/39-/66-byte call controls preserve
real tm/SYSTEMTIME/thread/locale types and cdecl/stdcall contracts. Replay
`scripts/repo-python scripts/verify-locale-time-parent-origins.py`. All 771
public checks, target/project attestation and local final acceptance pass;
all 60 exact units cold-replay across eleven objects. Totals are 3378 resolved
and 973 pending. The user waived public MCP acceptance on 2026-10-04.

R138 resolves all five locale snapshot/classification roots: five full primaries
/ 965 bytes / 54 fields. Gettnames retains all 184 record bytes and retargets all
43 strings in one allocation; concurrent snapshot consistency remains unknown.
Alpha/alnum preserve masks 259/263, actual thread locale +100, classification
pointer +72, signed input and full multibyte worker. Forty-eight whole defining
sections / 2191 bytes / 59 fields and seven independent anchors / 1284 bytes /
65 fields replay. Memcpy keeps its complete 829-byte code/table partition and
strcpy its independently retained shared carrier. Natural 132-byte layouts and
full 26-/67-/67-byte controls preserve real record, copy and classification
contracts. Replay `scripts/repo-python scripts/verify-locale-snapshot-origins.py`.
All 799 public checks and local final acceptance pass; all 60 exact units
cold-replay across eleven objects. Totals are 3383 resolved and 968 pending.
No source/mapping/exact credit is added. The public MCP acceptance waiver applies.

R139 resolves all six floating conversion/operation roots: six full own-AUX
primaries / 1750 bytes / 52 fields, thirteen independently retained anchors /
2184 bytes / 59 fields and eight whole defining data sections / 88 bytes /
zero fields. The parser keeps all 1076 bytes, split into 1028 code bytes and
one 48-byte twelve-case table, with every actual defining case entry. Natural
108-byte SDK layouts and complete 20-/29-/24-/19-/88-byte controls distinguish
the twelve-byte parser storage, ten-byte output/SDK FP80 and eight-byte C long
double. Original private C sources/typedefs are unavailable; complete pinned
COFF definitions and typed fields prove ownership, without a guessed private
type or ST0-input ABI. Replay
`scripts/repo-python scripts/verify-floating-operation-origins.py`.
All 833 public checks and local acceptance pass; all 60 exact units cold-replay
across eleven objects. Totals are 3389 resolved and 962 pending. No source,
mapping or exact credit is added. Public MCP acceptance remains waived.

R140 resolves all four stream finalization/path-access roots: four complete
own-AUX primaries / 282 bytes / 11 fields, six independent anchors / 572 bytes /
42 fields and the complete rejected waccess alternative / 70 bytes / five
fields. Actual GetFileAttributesA import identity rejects the equal-shaped
wide source. Full free/flush/close/error policies, five original vendor files,
nine headers, 112-byte FILE/SDK layouts and complete 92-/172-/131-/92-/92-byte
natural controls replay. Runtime stream/lock/path/error state remains unknown.
Replay `scripts/repo-python scripts/verify-stream-finalization-origins.py`.
All 869 public checks and local acceptance pass. Exact records and every tracked
source/header/build/match input are unchanged from R139 `db26a05`, preserving
that batch's 60/60 cold exact replay across eleven objects. No affected exact
unit requires another replay. Totals are 3393 resolved and 958 pending.
Public MCP acceptance remains waived; no source/mapping/exact credit is added.

R141 resolves all six exception frame/unwind roots and the required closure:
27 complete own-AUX primaries / 3,502 bytes / 116 fields, two existing interior
cleanup labels, three non-inventory auxiliary controls / 123 bytes / four
fields, eight full anchors / 1,183 bytes / 65 fields and seven whole defining
data sections / 92 bytes / thirteen fields. Five whole scope tables contain
seven records; existing cleanup labels start six bytes after actual handler
prologues. Five extents expand to include real tails. Private helpers retain
observed register contracts and unset canonical declarations. The six-byte
RtlUnwind linker thunk retains R030 compiler ownership and actual PE IAT
identity. Cold 128-byte SDK/thread layouts, nine independent natural controls,
all seven generated model data sections and the entire ten-byte no-AUX EH
handler replay. Original private frame source/types remain unavailable and
current opaque callback behavior is unknown. Replay
`scripts/repo-python scripts/verify-exception-frame-origins.py`.
All 909 public checks pass; totals are 3422 resolved and 929 pending. Exact
inputs/records remain unchanged from R139 `db26a05`, preserving its 60/60 cold
replay across eleven objects. Public MCP acceptance remains waived.

R142 resolves all four C++ throw/frame/standard-exception roots and their
required closure: eight whole own-AUX primaries / 331 bytes / twenty fields,
one existing nine-byte finally entry, a thirteen-byte non-inventory what
control, eleven whole anchors / 641 bytes / 26 fields and fifteen complete
template/vtable/RTTI/scope/literal data sections / 260 bytes / eighteen fields.
Two scalar controls retain R038 compiler origin. Complete vtable locator
prefixes, actual weak AUX/search/fallback records, full five-byte base arrays
and the 32-byte throw template replay; no private throw type or conventional
EAX-metadata shim ABI is invented. Cold 88-byte layouts, 22 whole natural
controls and every complete generated model data/code section replay with
R141's entire older chain and the independent R038 compiler proof. Replay
`scripts/repo-python scripts/verify-standard-exception-origins.py`.
All 951 public checks pass. Totals are 3431 resolved and 920 pending; the
60-function exact inputs/records preserve R139's 60/60 cold proof across eleven
objects. Public MCP acceptance remains waived.

R143 resolves all three derived RTTI-exception destructor candidates: complete
11-byte own-AUX bodies / 33 bytes / six fields. Eight non-inventory complete
constructor/what bodies, ten whole retained anchors and 31 whole defining
vtable/RTTI/literal sections close the paired family graph. Five compiler
anchors retain R038 ownership. Bad_typeid and non-rtti source COFF bodies are
identical alternatives; their linked target REL32 bytes differ by address.
Full independently relocated comparisons retain both source owners, while
whole constructed vtables, RTTI, constructors and incoming compiler callback
fields support provisional source roles. The non-rtti destructor writes the
bad_typeid destruction-stage vtable and tail-jumps straight to exception.
Cold real SDK layouts, all natural model code/data sections and the full
R142/R038 chain pass. Replay
`scripts/repo-python scripts/verify-derived-exception-origins.py`.
All 982 public checks pass. Totals are 3434 resolved and 917 pending; the exact
baseline and R139's 60/60 cold proof remain unchanged. Public MCP is waived.

R144 resolves both longjmp/read-probe roots / complete 187 bytes / eight fields.
Longjmp's extent expands from 120 to its full 121-byte AUX, including the real
final RET after its saved-EIP jump. The read probe retains all filter/handler
code and its whole 12-byte scope with both actual defining source entries.
The FS zero field has a real external ABS definition in whole exsup.obj,
checked against the full archive and actual segment/displacement. Five whole
retained unwind/NLG/SEH anchors, real SDK jump-buffer/SEH layouts and all
natural code/scope sections replay with R141's complete dependency chain.
Private saved callbacks, live registrations and original declarations remain
unknown. Replay `scripts/repo-python scripts/verify-jump-unwind-origins.py`.
All 1018 public checks pass. Totals are 3436 resolved and 915 pending; the
exact baseline and R139's 60/60 cold proof remain unchanged. MCP is waived.

R145 resolves the complete 793-byte small-block heap integrity worker, with
all 61 branches, both epilogues, eight independent fields and all final error
tails. Its two COMMON globals retain unique whole-archive tentative records,
complete loader zero-fill and independently accepted R120 bindings; three
real API calls bind IsBadWritePtr. Cold supplied full sbheap.c reproduces the
selected entire own AUX and every relocated target byte. Actual winheap.h/SDK
layout and six whole natural controls replay with the full R120 dependency
chain. Other emitted vendor functions/data gain no review credit. Live heap
state, runtime outcomes and original private declarations remain unknown.
Replay `scripts/repo-python scripts/verify-small-heap-integrity-origins.py`.
All 1048 public checks pass. Totals are 3437 resolved and 914 pending; the
60-function exact baseline and unchanged R139 cold proof remain preserved.

R146 resolves all three power handoff entries and the necessary existing
x87 fallback core candidate: four library origins. The CI wrapper reconciles
84 to its complete 59-byte own AUX; the SSE parent reconciles 25 to its whole
2886-byte AUX with the real exported +25 entry. The full 527-byte default
parent retains static start +34 and its entire 493-byte continuation, expanding
the original 221-byte candidate. A whole 650-byte wrapper/default carrier,
actual zero-AUX NOP, six whole data sections / 14862 bytes (including the
entire 14640-byte pow table from its real base), unique independently retained
SSE COMMON and all actual source/code/data fields replay. Three same-shaped
atan/log/log10 wrappers retain their complete rejected defining source carriers.
Five whole auxiliary controls, nine complete independent anchors, real SDK/
public ABI/intrinsic controls and full R130 dependency replay pass. Original
private declarations and live numerical/runtime outcomes remain unknown.
Replay `scripts/repo-python scripts/verify-power-math-origins.py`.
All 1087 public checks pass. Totals are 3441 resolved and 910 pending; the
60-function exact baseline and unchanged R139 cold proof remain preserved.

R147 resolves both acos handoff candidates. The entire 203-byte own AUX
replaces the 20-byte intrinsic prefix, preserving exported C +20 and actual
static start +29. The core's provisional 12494-byte span is reconciled to
its complete 174-byte shared continuation, preserving every unrelated prior
candidate/origin row. All thirteen independent fields, fourteen branches,
both RET sites and complete endpoint/NaN/error/flags-dependent routes replay.
Seven complete independent FP anchors, three whole defining data sections,
real SDK/public ABI/range/NaN controls and full R146 dependency replay pass.
Original private declarations and live numerical/runtime state remain unknown.
Replay `scripts/repo-python scripts/verify-acos-math-origins.py`.
All 1117 public checks pass. Totals are 3443 resolved and 908 pending; the
60-function exact baseline and unchanged R139 cold proof remain preserved.

R148 resolves the floor handoff candidate as a complete 64-byte wrapper,
retaining the entire original 289-byte defining carrier and contiguous
225-byte non-inventory SSE owner. All ten fields, full signed/zero/NaN/error
routes, whole 80-byte five-constant section, independent SSE COMMON and
complete default/error owners replay. Full ceil/modf alternative carriers
prevent the equal-shaped wrapper alone from proving operation identity.
Six natural SDK controls, all generated sections and full retained R146/R139
cold evidence pass. Exactly one origin row changed; prior owners remain
unchanged. Replay `scripts/repo-python scripts/verify-floor-math-origins.py`.
All 1148 public checks pass. Totals are 3444 resolved and 907 pending;
the 60-function exact baseline and R139 cold proof remain preserved.

R149 resolves six of the eight deque-size candidates through their complete
thirteen-member source family and six independent whole shared-receiver
contexts / 5610 bytes. The four push_back and two at owners retain complete
R072/R078 provenance; full R110/R113 cold source/context evidence also replays.
All 26 natural controls / 390 bytes, actual 32-byte SDK layout and 27 included
headers cover every emitted code/data carrier. Exactly six existing rows
change; all extents/prior owners remain preserved. Replay
`scripts/repo-python scripts/verify-deque-size-context-origins.py`.
All 1163 public checks pass. Totals are 3450 resolved and 901 pending;
the 60-function exact baseline and R139 cold proof remain preserved.

R150 resolves both nested size handoff candidates / 34 bytes. Fifty-three
complete code controls / 2980 bytes, seventeen whole data owners / 524 bytes,
five complete EH carriers / 82 bytes, actual weak fallback records and
independent original frames cold-replay. All source fields link through
independently complete owners before unmasked comparison; the full parser,
natural complete count observation and actual outer/returned-inner receivers
retain original ownership/uncertainty. R032's earlier vector/length-error
shape is preserved separately from the new whole invalid-subscript literal
and out_of_range type/throw context. No auxiliary owner or extent changes.
All 82 emitted functions, eighteen whole emitted data sections and 27 actual
headers are covered. Full R149/R119 cold evidence passes. Replay
`scripts/repo-python scripts/verify-nested-deque-size-origins.py`.
All 1183 public checks pass. Totals are 3452 resolved and 899 pending;
the 60-function exact baseline and R139 cold proof remain preserved.

R151 resolves all four nested deque helpers / 174 bytes through four complete
source-typed graphs / 36 bodies / 1472 bytes. Thirteen SDK element families
retain four complete positive graphs and nine rejected whole const owners;
equal-sized differing owners remain rejected and original types/folding
remain unknown. All 169 emitted functions / 5537 bytes, entire 32-byte SDK
layout, 27 actual headers and complete R150 cold provenance pass. Signed
iterator subtraction assignment retains its actual argument/reference return,
not a decrement overload. No original extent or prior anchor origin changes.
Replay `scripts/repo-python scripts/verify-nested-deque-helper-origins.py`.
All 1201 public checks pass. Totals are 3456 resolved and 895 pending;
the 60-function exact baseline and R139 cold proof remain preserved.

R152 resolves `0x0045DD00` / 66 bytes as authored script count policy.
Six complete independent authored owners / 5729 bytes preserve their original
switch/CFG proofs. The actual 1000-short missing-map initializer and decimal
label-to-outer-index producer independently supply the domain; eleven complete
game receiver/argument/result windows show its use as a signed count bound.
Full R150 cold code/data/EH and synthetic count source replay. Original
types, game layouts and malformed-input/overflow safety remain unknown;
there is no local count-index bounds guard. Exactly one canonical row and
one authored evidence record change; all prior owners/extents are preserved.
Replay `scripts/repo-python scripts/verify-script-count-origins.py`.
All 1221 public checks pass. Totals are 3457 resolved and 894 pending;
the 60-function exact baseline and R139 cold proof remain preserved.

R153 resolves both script record lifetime candidates / 67 bytes as authored.
Four full guarded-array source families agree unmasked; actual independent
array/scalar delete owners reject the equal-sized wrong scalar shape. Three
cold profiles cover 90 functions / 3897 bytes and 107 whole ordinary code/data/
EH sections / 4458 bytes with 24 actual headers. The entire original parser,
eight local constructor/copy/release pairs, real buffer producer and complete
original frame/cleanup/deleting contexts establish game buffer policy. R072's
producer is an eight-byte byte-record control; neither it nor R150's generic
nested size observation recovers original element declarations. All prior
origins/extents remain unchanged and auxiliary runtime controls gain no origin.
Replay `scripts/repo-python scripts/verify-script-buffer-origins.py`.
All 1244 public checks pass. Totals are 3459 resolved and 892 pending;
the 60-function exact baseline and R139 cold proof remain preserved.

R154 resolves all three allocation API candidates / 24 bytes as library.
Complete new.obj, delete2.obj and new2.obj own-AUX bodies compare unmasked
through every actual typed field and complete independent runtime owner.
Eight natural SDK call controls / 196 bytes and nine whole ordinary code/data
sections / 212 bytes, including a complete 16-byte observation layout and
eight actual headers, cold-build. Complete R120 allocation/handler/data/API/EH
provenance and retained source dependencies replay, followed by full R153
buffer lifetime source profiles and game contexts. Existing accepted owners
retain original evidence and boundaries. Replay
`scripts/repo-python scripts/verify-allocation-api-origins.py`.
All 1263 public workflow checks pass. Totals are 3462 resolved and 889 pending;
all 60 exact functions and R139 cold proof remain preserved.

R155 reviews all five short CRT candidates / 92 bytes. Three owners / 59 bytes
become library through complete own-AUX source, independent whole callees and
actual SDK operations. The SEH helper's entire 265-byte source carrier, including
the eight-byte source marker, full original 230-byte handler and all six fields,
compares unmasked. Complete original codepage/NLS, jump/unwind, security/EH and
runtime provenance replay; eight cold SDK/source controls / 109 bytes and nine
whole code/data sections / 153 bytes preserve the entire real 44-byte layout.
Replay `scripts/repo-python scripts/verify-short-crt-origins.py`.
All 1285 public workflow checks pass. Totals are 3465 resolved and 886 pending;
all 60 exact functions and R139 cold proof remain preserved.

Preserve the two R155 unsupported leaves: `0x0064F513` / 12 bytes has an
entire byte-equal ordinary memset control, and `0x00643FC6` / 21 bytes has
full SDK/vendor source but no independent owning context. Its ordinary
20-byte expression control is genuinely different, not a partial target match.
Both have no observed direct caller; absence alone proves no runtime property.
Do not revisit either from scanner rank, adjacent CRT names or new same-shaped
controls without new independent source ownership evidence. Preserve all R129
abs/labs versus ordinary expression ambiguity, including `0x00641FB8` / 11.

R156 accepts both complete 211-byte deque producers and all four 27-/29-byte
element-allocator/construction wrappers: six library owners / 534 bytes.
Replay `scripts/repo-python scripts/verify-paired-deque-producer-origins.py`.
The cold source retains all 187 ordinary sections / 11917 bytes, 162 entire
linked code/EH carriers / 11016 bytes, 22 whole data owners / 835 bytes,
436 actual unmasked fields, 27 headers and the entire 32-byte layout.
Two complete original authored parents, two unchanged R071 growth owners,
ten full original EH frames and independently authored R153 inner destruction
retain their original evidence. R154/R142 complete dependencies and the
retained R150 nested-deque source cold-replay. All 1312 public checks pass;
totals are 3471 resolved and 880 pending, with all 60 exact functions and
R139 cold proof preserved. See the R156 knowledge-base entry for boundaries.

At R156, the whole copy and insertion controls at `0x00422A50` / 241 bytes and
`0x00422D70` / 1545 bytes include shared tails. Their original unknown
canonical rows retained their provisional 195-/1483-byte extents. R158 reconciles
those parent extents and interior source policy below. Full EH source
carriers do not revise old compiler entry extents. Source/data/typed-call
association alone grants none of these auxiliary parents origin credit.

R157 accepts the four complete lower-level SDK element allocation/construction
owners / 213 bytes. Replay
`scripts/repo-python scripts/verify-deque-element-origins.py`.
Their ordinary natural allocation/placement-copy controls emit all 213
identical bytes; complete ordinary EH/data carriers expand those controls to
276 bytes with fourteen actual unmasked fields. Library origin is inferred
from independently complete R156 typed parents and the whole retained SDK
source family; body equality alone is explicitly insufficient. The source
freezes all 193 ordinary sections / 12193 bytes, 27 SDK headers and its actual
included observation source. Full R156 and R154/R142 dependencies cold-replay.
R156's immutable original snapshots permit only the four exact hash-pinned
R157 transitions; all other original rows remain unchanged. All 1340 public
checks pass. Totals are 3475 resolved and 876 pending; all 60 exact functions
and R139 cold proof remain preserved. No game element declaration is recovered.

R158 reviews all six copy/insertion candidates. Five gain library origin:
two whole SDK owners / 1786 distinct bytes and three overlapping interior
catch/source-policy candidates. Canonical copy/insertion extents are now
241 and 1545 bytes, reconciling the former 195-/1483-byte prefixes with
required shared normal returns. The interior spans retain their original
46-/48-/62-byte candidate extents; they are not standalone whole functions
or additional source byte credit. Source rollback/rethrow policy is library
evidence, while original compiler dispatch/frame provenance remains unchanged.
Replay `scripts/repo-python scripts/verify-deque-copy-insert-origins.py`.
Fourteen entire code/data/EH controls / 2416 bytes, 104 actual unmasked fields,
all 194 ordinary cold sections / 12303 bytes and the whole 48-byte layout
retain complete R157/R156 and independent runtime/policy/source evidence.
All 1374 public checks pass. Totals are 3480 resolved and 871 pending;
all 60 exact functions and R139 cold proof remain preserved.

Preserve `0x004229D0` / 28 bytes as unknown: ordinary explicit and implicit
record-copy controls emit all 28 identical bytes and the same full SDK child.
Actual R157 construction context establishes operation, not original source
ownership. Only its durable function evidence/notes change. Preserve its
unknown origin and empty name/owner/source/ABI fields; do not re-review it
from a library child or another same-shaped control without independent
ownership evidence. Preserve the prior R129/R155/lifetime ambiguities too.

R159 accepts all eight endpoint/category/operation dependencies / 296 bytes.
Replay `scripts/repo-python scripts/verify-deque-endpoint-dispatch-origins.py`.
Twelve complete code controls / 2104 bytes, 76 actual unmasked fields, all 197
ordinary cold sections / 12245 bytes and the full 72-byte SDK/traits layout
retain entire R158 copy/insertion parents and R157/R156/runtime evidence.
Forward and bidirectional category controls agree in all eleven bytes; input
category differs at the same full size. Complete input-distance / 49 and
bidirectional-advance / 59 are different operations, never truncated target
matches. Library inference uses complete real SDK parent/overload relationships;
original category/element declarations remain unknown. Existing R085 algorithms
and R081/R084/R106 iterator operations remain unchanged. Exact hash-pinned
R159 transitions preserve the immutable original R156/R158 parent/alignment
snapshots without skipping unrelated evidence. All 1404 public checks pass;
totals are 3488 resolved and 863 pending, with all 60 exact functions and
R139 cold proof preserved.

R160 accepts the five remaining deque leaves / 129 bytes. Replay
`scripts/repo-python scripts/verify-deque-leaf-origins.py`. Complete SDK max_size,
indexing/subtraction/destruction parents and actual whole placement construction
/EH cleanup supply ownership context. Full ordinary capacity / 44, explicit
destruction / 15 and two-argument no-op / 5 are byte-equal, so shapes alone
identify none of their original sources. The unchanged R037 generated wrapper
and R153 authored destruction remain separately classified. Seventeen full
controls / 2568 bytes and 88 fields include the entire 27-byte construction
cleanup/frame carrier and 36-byte state data. All 191 cold ordinary sections
/ 12034 bytes, full 72-byte layout and 28 actual source/SDK includes are pinned.
Only five new exact hash-pinned transitions are permitted; original R156–R159
manifests and the 28-byte record-copy ambiguity remain unchanged. The R156
primary graph now has only that protected unknown; the full backlog remains
858. All 1429 public checks pass; totals are 3493 resolved, with unchanged
60-function exact inputs and preserved R139 cold proof.

R161 reviews all nine candidates, accepting eight library origins / 222 bytes
and keeping second destruction `0x0040F9F0` / 15 unknown with its independently
protected R108 surrounding lifetime policy. Replay
`scripts/repo-python scripts/verify-vector-endpoint-origins.py`. Whole vector
assignment/endpoint/constructor and allocator/compiler/policy source contexts,
31 complete code controls / 1169 bytes and 41 genuine unmasked fields retain
original R034/R095/R032/R074/R033/R037/R017/R106 evidence and protected R108
policy. Full ordinary endpoint/constructor/destructor controls / 144 bytes
are byte-equal, so source shapes alone grant no ownership. Whole actual deque
subtraction / 57 matches; genuine addition / 57 differs through its complete
addition-assignment / 31. R078's original addition-shaped association remains
immutable, while the parent's provisional operation/evidence is refined without
new origin credit. All 176 cold ordinary sections / 9404 bytes, 28 actual SDK
headers and full 68-byte observation layout are pinned. Exactly eight origin
rows and ten function-evidence rows change. All 1464 public checks pass; totals
are 3501 resolved and 850 pending, with the 60-function exact baseline preserved.

R162 reviews all fifteen short candidates / 447 bytes and accepts only three
library endpoints/constructor / 90 bytes through unchanged whole R034 assignment
`0x005F8B70` / 96, complete R032 erase/insert and actual R106 base. Twelve short
candidates and both complete nontrivial assignment parents / 158,167 remain
unknown. Whole ordinary C++ alternatives are byte-equal through all parent and
cleanup/state bytes, so reviewed game callers or library children alone do not
settle ownership. Replay
`scripts/repo-python scripts/verify-vector-producer-origins.py`: 43 whole controls
/ 2039 bytes, 95 unmasked actual fields, all 244 cold ordinary sections / 13520
bytes, complete 92-byte layout and 27 SDK headers. Complete `/GS` negative
parents / 174,183 and all 244 sections / 13616 bytes are retained. Full original
R020 frame registration, five authored game contexts and protected unknown
lifetime/copy/destruction records remain preserved. Exactly three origin rows
and seventeen function-evidence rows change. All 1498 public checks pass; totals
are 3504 resolved and 847 pending, with the 60-function exact baseline intact.

R163 reviews all twelve candidates / 253 bytes and refutes the prior diagnostic
string-length label. Five whole float math overload/worker chains use the actual
cos/sin/fabs/sqrt/ceil C stack-double entries; the sixth calls a full eleven-byte
integer absolute-value body. Complete SDK and ordinary chains are byte-equal,
including every real field. Full abs/labs and cold ordinary int/long expressions
also match the entire worker. All twelve origins remain unknown; exactly twelve
function-evidence rows change, and all origin/extent/name/ABI/exact state remains
unchanged. Replay `scripts/repo-python scripts/verify-math-overload-origins.py`:
22 whole source controls / 484 bytes and 22 genuine fields, all 29 cold ordinary
sections / 602 bytes, six SDK headers and full 16-byte layout. Five whole runtime
primaries / 775 bytes and their actual existing C shared entries replay from the
pinned archive. Five whole authored game contexts / 8610 bytes and twenty call
windows remain independent; neither game callers nor byte-equal source shapes
prove original wrapper ownership. The original R129 abs ambiguity and all other
protected policies remain unchanged. All 1527 public checks pass; totals stay
3504 resolved and 847 pending. Preserve the complete negative/ambiguous evidence
and do not repeat this shortlist as a string-length or import-thunk hypothesis.

The next bounded R164 cohort is five unresolved SDK dependency candidates
/ 504 provisional bytes, each reached from an independently accepted full
library parent. These are diagnostic contexts, not promised acceptances:

| Candidate | Full provisional extent | Independent whole parent to retain |
| --- | ---: | --- |
| `0x00415F60` | 44 | R074 `0x00415A80` / 22, provisionally named `VC7::max_size_00415A80` |
| `0x00422290` | 151 | R072 deque tidy `0x00421DD0` / 177; retain actual children `0x00422270`, `0x00422610` independently |
| `0x0042E120` | 151 | R072 deque tidy `0x0042DEF0` / 177; retain actual children `0x0042E100`, `0x0042E390` independently |
| `0x0045AFB0` | 50 | R033 generic copy `0x0045A7E0` / 51, with actual worker `0x0045AAE0` independently unresolved |
| `0x0045B640` | 108 | R033 construct `0x0045B2B0` / 29; actual `0x004063D0` and `0x004591E0` ownership remains independent |

Read the full actual parent and every source field; original generic names are
not source-type or ABI proof. Build natural complete SDK and ordinary controls,
reconcile full CFG, exits, shared tails, EH/data and own-AUX or defining-section
extents. A library parent supplies independent context but does not automatically
classify a child. Keep original parent evidence immutable. Do not instantiate
an incomplete reconstructed game owner or truncate a comparison to an emitted
source variant. Preserve all prior R108 lifetime, R158 copy, R161 destruction,
R162 endpoint/assignment and R163 math/abs ownership ambiguities, including the
unchanged R129 abs alternative and R161 R078 operation refinement. No exact
scope is added. The full origin-review goal remains active and unfinished.

The unrelated 75/72-byte `0x00421250` / `0x004212A0` and 84-byte
`0x004204D0` lifetime contexts remain non-accepting diagnostics. Preserve
existing lifetime ambiguities and do not expand into exact-reconstruction scope.

The two original string throw workers `0x00654ACE` / `0x00654B0E` remain
unresolved external snapshots; R150 gives them no additional source or origin
credit. The prior math/source diagnostic surveys remain exhausted for their
bounded associations; do not reopen accepted owners or known lifetime ambiguities.

A bounded scan of the supplied rtti.obj member 423098 found no complete
relocation-masked associations for its exported RTtypeid (156 bytes),
RTCastToVoid (93) or RTDynamicCast (224). This private diagnostic in
`.analysis/r143-next-rtti-survey.json` grants no origin and does not exclude
other original source/compiler variants. Do not force these source owners
onto the separate string-throw workers below.

The two existing 64-byte workers `0x00654ACE` / `0x00654B0E` are separate
standard string/exception throw contexts, not bad_cast/bad_typeid evidence.
Their read-only attested diagnostic query is
`.analysis/r142-next-rtti-disassemble.txt`. They construct through `0x004053E0`
and `0x00404B40`, write whole exception/EH context and call the reviewed throw
worker; their origins and full parent/EH extents remain unaccepted. Do not
classify them from that library child or force an association to rtti.obj.
No `_Xlength_error`/`_Xout_of_range` whole source association was found in the
supplied libcpmt diagnostic; this is bounded negative evidence, not a claim
that no original source exists. Preserve these contexts for a later complete
string/exception source-family review.

The broader `.analysis/r138-next-crt-survey.json` preserves other diagnostic
full-AUX associations, including conflicting floating wrappers and substantial
provisional-extent mismatches. R146–R148 resolve the power, acos and floor families with complete enclosing
carriers and operation fields. Do not reopen those accepted owners from
earlier scanner diagnostics alone.
Preserve R129's abs ambiguity and earlier explicit/implicit lifetime
alternatives. Do not infer parent origin from reviewed children.

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

On 2026-10-04 the user authorized local investigation and final acceptance,
waiving public MCP replay to accelerate origin review. Preserve the existing
no-auth route, private path and 60-function exact baseline. R167 adds no exact scope. Update
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
scripts/repo-python scripts/verify-allocator-thread-origins.py
scripts/repo-python scripts/verify-runtime-cycle-origins.py
scripts/repo-python scripts/verify-startup-registration-origins.py
scripts/repo-python scripts/verify-locale-thread-origins.py
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

Continue the bounded R139 floating conversion/operation cohort described above. F008 and F009 remain
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
