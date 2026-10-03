# TH075 function reconstruction handoff

Updated 2026-10-03. Work resumed with origin-review batches R070–R103. The public
repository is [N0zoM1z0/th075](https://github.com/N0zoM1z0/th075) on
`main`. Commit subjects use `gpt-6.1-sol: ...`. Keep documentation in English.

## Verified checkpoint

The pinned target is the supplied Japanese `th075.exe` (reported `ver1.11`),
SHA-256 `bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
The initial Ghidra inventory has 4,351 provisional candidates. Origin review
has resolved 2,993: 878 authored, 1,540 library and 575 compiler generated.
There are 1,358 pending. Candidate count is not authored function count.

The unchanged exact baseline is 42 source-present and exact functions,
covering 8,916 bytes across 42 match units. Exact coverage of the currently
reviewed authored bytes is 8,916 / 1,957,166 (0.46%). This denominator is
provisional because origin review is incomplete. The origin-review batches
added no exact credit; F001–F007 established the existing exact baseline.
The requested order was to finish origin review, then rank core authored
functions by value and dependencies before resuming exact reconstruction.
Both the complete-origin and 50%-exact milestones remain unfinished.

The canonical state lives in `config/functions.csv`,
`config/function-origins.csv`, the origin evidence CSVs and the exact
match-unit manifests. The progress SVG is generated from those ledgers.
[Origin review](ORIGIN_REVIEW.md) records the evidence and boundaries for
R001–R103; the [knowledge base](KNOWLEDGE_BASE.md) records accepted facts.
The former chronological handoff is preserved in
[handoff history](RE_HANDOFF_HISTORY.md); its earlier counts and next-step
notes are historical snapshots.

## Tooling and verification

Run repository Python through `scripts/repo-python`. TH075 has its own
Ghidra project and Bash + Ghidra MCP bridge, with pinned VC7.1/D3D8 tools
reused privately from TH095. The user-requested Tailscale Funnel endpoint
has no bearer authentication. Its random path is private in the ignored
`.tools/mcp_for_gptweb-ghidra/.env`; do not print or commit it. The latest
public HTTPS smoke test passed 15 checks, including Ghidra attestation and a
cold exact-unit replay. See [MCP operations](GHIDRA_MCP.md).

```bash
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/validate-tracking.py --require-target
scripts/repo-python scripts/report-reconstruction-status.py --summary
scripts/repo-python scripts/verify-authored-origins.py
scripts/repo-python scripts/scan-origin-candidates.py
scripts/repo-python scripts/verify-short-game-origins.py
scripts/repo-python scripts/verify-short-game-origins.py --cohort R102
scripts/repo-python scripts/verify-short-game-origins.py --cohort R103
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
scripts/repo-python scripts/update-progress.py --check
scripts/repo-python scripts/ci.py
git diff --check
```

The current session passed 141 public tests, target-required tracking,
complete checks of 831 explicitly recorded authored bodies, and progress
freshness. The new deque algorithm, emptiness, short-helper, cleanup, vector
storage, vector helper, vector operation, vector callee, scalar copy and
vector wrapper, standard exception and battle-end destructor cold verifiers
passed through the no-auth public Funnel MCP.
The complete CRT external-dependency verifier also passed through that endpoint.
The twelve short game policies and full blend-mode context also replayed
successfully through the public MCP.
The eleven effect forwarders/fixed transforms also passed their complete
context and ABI verifier through that endpoint.
The R102 seventeen-function cohort, R103 thirty-three-function cohort and
complete batch origin scanner also passed through the no-auth public HTTPS MCP.
R084 had already replayed the earlier thirteen
deque cold verifiers and the fighter script accessor verifier over that
endpoint. Public GitHub CI through R102 passed.

## Deferred investigations

Use [batch origin review](ORIGIN_BATCH_SCAN.md) and
`scripts/repo-python scripts/scan-origin-candidates.py` to refresh the private
shortlist for all 1,358 pending candidates. The current report groups 47 whole
bodies and isolates 182 extent questions. Start with grouped source/context
witnesses rather than one-address setup. R102 accepted seventeen explicit
game policies through the shared cohort verifier, with 33 independent whole
anchors and 15 complete parent edges; scan hits alone remain diagnostic.
R103 reused that verifier for thirty-three game state/record policies with
22 independent whole parents, 33 parent edges, seven raw PE import bindings,
two unresolved virtual dispatches and four readonly float scalars. The new
batch keeps signed field widths, indexed record strides and state limits
explicit; lifetime-only and generic helper hypotheses remain pending.

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

Nearby destructor-shaped candidates `0x00412E50` and `0x00449D40` remain
pending. Their reviewed game cleanup calls alone do not distinguish an
authored destructor body from implicit member destruction. Preserve that
origin question until the complete lifetime/source-emission context is checked.

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

Complete the 1,391 pending origin decisions before doing further exact
reconstruction. Then derive a priority list from
confirmed authored bytes, core behavior, cross-function dependencies and
likely matching cost. R070's script loader/parser is verified; remaining
adjacent short deque-like helpers still need independent origin review.
