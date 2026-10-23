# Historical function reconstruction handoff notes

This file preserves historical checkpoints through R268 and F039. Counts, active
goals and next-step notes below describe their original checkpoints and may
be stale. Use [the current handoff](RE_HANDOFF.md) and the canonical ledgers
for current status.

Updated 2026-10-02. Scope is function reconstruction; the user explicitly
deferred subsequent phases. Write documentation and handoffs in English.

- Target: supplied Japanese `th075.exe`, reporting version 1.11, SHA-256
  `bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
  Official distribution provenance is uncorroborated. Do not substitute the
  localized executable.
- Initial analysis completed in the separate TH075 Ghidra 12.1.3 project.
  There are 4,351 candidates, with 42 mapped, 42 source-present, and 42
  complete exact functions covering 8,916 bytes. Origin review has classified
  788 authored, 792 library and 574 compiler candidates; 2,197 origins remain
  pending. Candidate count is not authored function count; regenerate
  statistics from the ledgers.
- The active goal is all origins reviewed and at least 50% authored bytes
  exact. Finish every origin review before resuming exact reconstruction.
  The current reviewed authored-byte denominator is 1,940,330, with 8,916 exact (0.46%).
  This denominator is provisional; the goal is incomplete. Four public
  accounting regressions prevent pending origins or function counts from
  falsely satisfying it. See `ORIGIN_REVIEW.md` for R001 through R066 evidence.
- F003 accepted three texture/reset functions, 833 bytes and 30 relocations.
  F004 accepted three keyboard/setup functions, 382 bytes and 36 relocations.
  Each batch passed complete cold replay from a fresh independent object.
  The no-auth public Funnel Bash MCP cold-replayed all 36/36 units
  across six objects through scripts/repo-python after F005. Public CI has 87 passing
  target-independent regressions.
  The original GraphicsState/Input translation units remain unchanged.
- F005 accepted six input-lifetime/joystick functions, 1,060 bytes and 84
  relocations, under an independently evidenced GS-enabled profile. R003
  excluded 15 vendor-vector bodies (712 bytes) and reviewed the custom axis
  callback before exact acceptance. See the knowledge base for real SDK
  container types, callback ABI and compiler-generated null temporary.
- R004 reviewed 100 more VC7 container/string/exception bodies (4,497 bytes)
  using fresh vendor-source fingerprints, typed call destinations and complete
  control flow. The public vendor probe and CSV record all extents/symbols and
  159 relocation bindings. Overlapping catch funclets remain separately pending.
- F006 accepted texture copy, line and filled-rectangle drawing: 1,548 bytes
  and 48 relocations, cold-replayed from two new objects. Preserve the copy's
  Width-based pixel indexing, bitwise float multiplier test, RGB byte casts,
  alpha operation, and right/bottom +1 policy. See `KNOWLEDGE_BASE.md`.
  Full no-auth public MCP cold replay then passed 39/39 units across eight
  objects, including all 428 relocations and 6,810 accepted bytes.
- R005 reviewed 25 more candidates, including five complete vendor EH spans
  and six generated/memory helpers. Fourteen retained analysis fragments belong
  to those vendor spans. The length_error copy constructor alias at 0x00405340
  was corrected to compiler ownership using actual throw metadata. The public
  vendor CSV records revalidated all 111 full fingerprints and bindings.
- F007 accepted rectangle outline, textured quad and projected triangle strip,
  adding 2,106 bytes and 69 relocations. Outline closes its five-vertex strip
  with assignment and uses index <= 4. Quad reads unsigned texture dimensions
  and converts a four-record coordinate view without claiming the complete
  132-byte caller owner. Strip mutates input vertices with the verified 3000/2
  projection. Shared ScreenVertex is a complete 28-byte record. See the
  knowledge base for scopes, ABI and full cold replay evidence.
  Full no-auth public MCP cold replay passed 42/42 units across nine fresh
  objects, covering all 8,916 bytes and 497 relocations. CI's 18 regressions,
  target-required tracking validation and progress freshness checks passed.
- R006 reviewed 41 relocation-free static-runtime functions, 4,282 distinct
  bytes. Every target byte equals the complete vendor COFF function, using its
  own definition auxiliary size. All branches/calls resolve to internal
  instruction starts. `scripts/verify-runtime-origins.py` rechecks the pinned
  archive, member identities, complete bytes and CFG. This grants origin
  evidence only, with no source-presence or canonical exact credit.
  The verifier passed locally and through the no-auth public Bash MCP.
- R007 reviewed eleven more complete CRT bodies (813 bytes), binding all 17
  zero-addend direct calls to separately verified vendor bodies. The runtime
  verifier now covers 52 functions / 5,095 bytes. Missing, mismatched or guessed
  callee bindings fail; these are origin records only.
- R008 reviewed 145 complete, relocation-free SDK function COMDATs (29,590
  bytes): 144 D3DX library bodies and one compiler vector-construction helper.
  Extents come from one defined function at section offset zero, not a target
  prefix. Full target bytes and CFG are rechecked by verify-sdk-origins.py.
  Its 194 unchanged indirect calls grant no ownership credit to callees.
  The SDK survey's remaining 434 candidate addresses stay pending.
- R007/R008 verifiers also passed through the no-auth public Funnel Bash MCP
  using scripts/repo-python. Public CI passed all 26 tests, target-required
  tracking validation passed, and the progress SVG is current. Reconstruction
  remains at the published 42-unit / 8,916-byte baseline.
- R009/R010 reviewed 77 more complete SDK bodies, 16,524 bytes, with
  independently evidenced calls, scalar definitions and internal tails.
  verify-sdk-origins.py now covers 222 bodies / 46,114 bytes, all 60 direct-call
  and 128 scalar bindings, and 315 unchanged indirect calls. Seven complete
  members end with internal jumps after earlier RET paths; no truncation.
  The remaining SDK survey addresses number 357, still pending.
- R011 reviewed sixteen custom sprite/geometry/diagnostic functions, 4,941
  authored bytes. Full extents/hashes are in authored-origin-evidence.csv;
  semantic ownership and complete CFG are documented in ORIGIN_REVIEW.md.
  The misleading MFC dialog label at 0x0040D840 is a custom white-sprite wrapper.
  The four-float constructor at 0x0040DB10 stays pending until SDK/custom alias
  evidence is resolved. Complete 132-byte owner types/roles remain unknown.
  These reviews add no source, mapping or exact credit.
- R009/R010 SDK verification and R011 tracking/status checks passed through
  the no-auth public Funnel MCP using scripts/repo-python. Public CI passed
  33 tests; target-required tracking and progress freshness passed. Exact
  remains unchanged at 42 functions / 8,916 bytes. The 51.59% percentage uses
  a provisional denominator and does not satisfy the full goal.
- R012/R013 reviewed 38 further SDK bodies, 26,625 bytes. Complete
  call/scalar bindings and 81 whole readonly vendor data sections (3,843 bytes)
  independently anchor all target fields. The SDK verifier now covers 260
  bodies / 72,739 bytes, 106 direct-call bindings, 158 scalar bindings, 232
  readonly-section fields and 323 unchanged indirect calls. Mutable/relocated
  data, external tails and unresolved dispatch still receive no credit.
- R014 reviewed twelve custom texture/palette/cache/render-wrapper functions,
  1,475 authored bytes, with complete target hashes and internal CFG. Preserve
  the first-use texture-cache behavior and palette transparency/error paths.
  The 44-byte metadata record and complete owner types remain unknown.
  Container/math/conversion callees receive separate review, not inherited
  ownership. See ORIGIN_REVIEW.md and the knowledge base.
- The SDK-size-44 vendor container probe produced 83 diagnostic candidate
  addresses under `.analysis/r015-metadata-vector-*`. It uses genuine
  DIDEVCAPS only to investigate type-neutral vector policy; it makes no claim
  about the game's metadata type and adds no origin/source/exact credit.
- R012/R013 SDK verification, runtime-origin verification and R014
  tracking/status passed through the unchanged no-auth public Funnel MCP.
  Public CI passed all 41 tests and progress is current. The private receipt
  is `.analysis/public-r012-r014-origin-verification.json`. Exact remains
  deferred at 42 functions / 8,916 bytes; the full goal remains incomplete.
- R015/R016/R017 reviewed 42 custom sound/input/stream/texture lifetime
  functions, 12,459 authored bytes. This includes the game's sound-bank file
  format, signed held-input counts, BGM playback/fade/refill and its dedicated
  wave\bgm\59.wav loop-point case. Generic deque/vector helpers remain
  separately pending; source names, ABI and complete owner layouts are unknown.
- verify-authored-origins.py rechecks 70 explicitly recorded bodies / 18,875
  bytes, full target hashes and internal CFG. This rechecks boundaries rather
  than automatically proving semantic ownership, and adds no exact credit.
- The fresh 64-byte D3DMATRIX deque probe produced 76 diagnostic pending
  addresses under `.analysis/r018-stream-deque-*`. The SDK type only probes
  generic size-dependent container policy, not the game stream record type.
  The compiler session is complete; no build/query session remains active.
- R015/R016/R017 authored extent verification and target-required tracking/
  status checks passed through the existing no-auth public Funnel MCP using
  scripts/repo-python. Private receipt:
  `.analysis/public-r015-r017-origin-verification.json`. Public CI passed
  44 tests and the progress SVG is current. Origin review remains incomplete.
- R019 reviewed nine texture directory/pack/palette reader/writer bodies,
  4,337 authored bytes. R021 reviewed twelve bitmap/RLE/upload/progress-record
  bodies, 7,476 authored bytes. Four indirect switches are fully bounded and
  all remaps/tables/case targets are verified. Their 168 outside-code data bytes
  are evidence only, not additional authored or exact credit. Complete owners
  and original ABI/names remain unknown.
- R020 excluded 303 generated exception cleanup bodies / 3,174 bytes using
  fresh independent compiler fixtures and actual metadata/parent registration.
  208 FunctionInfo frames and all their state entries are rechecked by
  verify-compiler-origins.py. Parent/callee ownership stays independent.
  See ORIGIN_REVIEW.md for the two required serial probe-build commands.
- verify-authored-origins.py now rechecks 91 recorded bodies / 30,688 bytes,
  including all four bounded indirect dispatches. Generic scalar deleting
  destructor candidates at 0x0041A110/0x0041A140/0x0041A170 and the initializer
  at 0x0041BF90 remain pending. No build/query session is currently active.
- Accepted F002: 22 shared graphics-state/frame functions plus the input error
  wrapper, adding 2,960 bytes. Complete jump tables and all 228 new relocations
  are included. Public MCP cold replay passed 24/24 units across three objects.
  See `KNOWLEDGE_BASE.md` for boundaries, ABI evidence, and unresolved names.
- Accepted F001: the reference-count constructor at `0x00401000`; see
  `KNOWLEDGE_BASE.md`. Its name and complete owner layout remain provisional.
  Both DIR32 relocations have been verified.
- Private symlinks reuse TH095 tool installations. The bridge checkout,
  target, project, configuration, and build products are independent. Bridge
  pin and machine configuration template live below `config/`.
- Ghidra queries require attestation and operation completion markers. CLI
  and bridge requests share a project lock. `inventory` exports only below
  `.analysis/inventory/`, preserving accepted ledgers.
- The public repository is `https://github.com/N0zoM1z0/th075`, on `main`.
  Commit subjects use `gpt-6.1-sol: ...`. Reference source files and protected
  working-tree files were not changed.
- The enabled `th075-ghidra-bash-mcp.service` listens on `127.0.0.1:8775` and
  is published through a dedicated Tailscale Funnel path on HTTPS 443.
  The user explicitly requested no authentication. Its fixed random path
  lives only in the private `.tools/mcp_for_gptweb-ghidra/.env` (mode 600);
  no Bearer token is configured or needed.
- Public HTTP smoke testing passed 15 checks through a global IPv4 ingress,
  including no-auth access, unrelated-path rejection, two-tool discovery,
  pinned Python/decoder verification, Bash verification, Ghidra
  check/query/decompile, failure rejection, scratch cleanup, and cold exact
  replay. All six earlier Funnel handlers were preserved. The service is
  enabled and user lingering is active. See `GHIDRA_MCP.md`.
  Public initialization and Bash workspace verification also passed after
  restarting the service, using the unchanged private URL without authentication.

Use `scripts/repo-python` for every Python command. The private Python 3.12
environment and Capstone 5.0.6 binding/native hashes are checked on each call.
The deployed Ghidra command uses this entry point; the endpoint and no-auth
settings stayed fixed. Public smoke testing passed after service restart.
Python child processes now also invoke the absolute wrapper, preserving
isolated mode through build, comparison, tracking, Ghidra, progress, and CI
chains. A conflicting `json` module on shell `PYTHONPATH` reproduced the
previous child-process gap; the new local/public regression verifies that the
progress/status chain ignores it from an unrelated working directory.

The compiler/linker hashes and executable banners are checked by
`scripts/check-tools.py`; the SDK supplies D3D8/D3DX8 and DirectInput headers.
CLI and public Bash compiler calls share a compiler lock. The installed tools
remain shared read-only binaries; TH075 owns all objects and debug outputs.
TH105 was reviewed as an engine-structure reference: it uses VC8/LTCG and
D3D9, so retain TH075's proven VC7.1/D3D8 profile. See `REFERENCE_PROJECTS.md`
and `BUILD_MATCHING.md`.

Next origin batch: resolve the 212 remaining runtime archive fingerprint candidates
under `.analysis/crt-origin-survey.json` with complete relocation/callee/data
binding evidence. Review the 319 remaining SDK fingerprint candidates. The
260 reviewed SDK bodies and 81 independently verified readonly sections are
usable anchors; relocated dispatch tables and mutable globals need their own
proof. Continue the private 83-address vendor-container diagnostic from
`.analysis/r015-metadata-vector-hits.json`, using its fresh compiler object
and complete typed call context before crediting a match. No compiler build
is currently active. Neither survey alone grants credit. Also review the fresh 76-address stream-deque diagnostic and its helper bindings
under `.analysis/r018-stream-deque-hits.json`. Then follow
the remaining container/string helpers starting at
`0x004063F0`, then follow the reviewed custom texture-manager family into
the remaining metadata/container helpers at `0x0040D8C0/0x0040DD60` and
the unreviewed family after `0x0041BF90`. Texture loading, bitmap/RLE/upload
and manager lifetimes are now reviewed. Extend compiler EH review only after
independently validating other registration/metadata/pattern forms; 21 static lifetime tail
candidates remain pending in the earlier 422-candidate diagnostic. Review the
math/constructor aliases separately; do not inherit origin from these callers.
Keep vendor
and custom ownership separate. Finish every origin review before resuming
exact reconstruction. Then rank authored functions by core behavior,
dependencies and reconstruction
cost. The unfinished F008 probes and ledger snapshot are preserved privately
under `.analysis/deferred-exact-f008/`; they have no additional published
source or exact credit. Existing accepted units remain unchanged.
Full input decompiles/instructions are private under
`.analysis/origin-input-*`; avoid trusting misleading Ghidra string/back labels
on device containers. F007 caller/layout evidence is under
`.analysis/textured-quad-*`; complete 132-byte owners remain unknown.
Deferred paired cleanup at `0x00401020..0x0040110E`, 239 bytes.
Review interface types, shared pointers, and loop bounds before writing a
natural source probe. The target saves one Release result into a local slot;
the reason is unknown. Do not invent an inert local merely to force emission.
This function has no source-presence or exact credit yet.

```bash
git status --short
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/validate-tracking.py --require-target
scripts/repo-python scripts/report-reconstruction-status.py --summary
scripts/repo-python scripts/ghidra.py check
scripts/repo-python scripts/check-tools.py
scripts/repo-python scripts/replay-exact-units.py
scripts/repo-python scripts/ci.py
scripts/repo-python scripts/test-public-mcp.py
```

R019/R020/R021 checkpoint: all four origin verifiers and target-required
tracking/status passed through the unchanged no-auth public Funnel Bash MCP.
Private receipt: `.analysis/public-r019-r021-origin-verification.json`.
Local CI passed all 57 regressions and the progress SVG is current. No accepted
exact source/header, flags, relocation or unit configuration changed.

R022 adds 60 compiler exclusions / 611 bytes: the independently bounded
libcmt `__EH_prolog` helper and 59 cleanup bodies registered through it.
The verifiers now cover 53 runtime bodies / 5,126 bytes and 362 compiler cleanup
bodies / 3,754 bytes across 236 frames. Thirty-nine positive-slot cleanup forms
and 21 static lifetime wrappers remain pending in the earlier tail diagnostic.
No compiler/query session remains active. Exact reconstruction stays deferred.
R022 verification passed through the unchanged no-auth public Funnel MCP;
private receipt `.analysis/public-r022-origin-verification.json`. Local CI has
59 passing tests and progress is current. R019/R020/R021 published GitHub CI
passed at https://github.com/N0zoM1z0/th075/actions/runs/37003418979.

R023 resolves the 39 previously deferred positive-slot allocation cleanup bodies
(390 bytes) with fresh optimized compiler emission and full actual metadata
bindings. Build `probes/VC7OptimizedEH.cpp` using the command in ORIGIN_REVIEW.md
before running the compiler-origin verifier. It now checks 401 cleanup bodies /
4,144 bytes and all 236 frames. The 21 static lifetime wrappers remain pending
in the original tail survey. No compiler/query session remains active.
R023 compiler/runtime and authored verification plus target-required tracking/
status passed through the no-auth public Funnel MCP; private receipt
`.analysis/public-r023-origin-verification.json`. Local CI passed 60 tests,
progress is current and the accepted exact units remain unchanged. R022 GitHub
CI passed at https://github.com/N0zoM1z0/th075/actions/runs/37003968089.

R024 reviews all 21 remaining static-lifetime wrappers in the earlier EH-tail
diagnostic: 11 startup entries and ten paired finalizers, 468 bytes.
`verify-static-origins.py` checks fresh ordinary compiler emission, complete
target bodies, the executable startup loop/table, callbacks, writable global
addresses, and a pinned vendor exit-registration fingerprint. Build the probe
with the command in ORIGIN_REVIEW.md before running its target verifier. Called
constructor/destructor bodies, vector helpers, global types and startup runner
remain separate origins. Current totals are 1,013 reviewed / 3,338 pending;
Exact remains 42 functions / 8,916 bytes. No query/compiler session is active.
R024 verification passed through the unchanged no-auth public Funnel MCP;
private receipt `.analysis/public-r024-origin-verification.json`. Local CI passed
65 regressions, target-required tracking and progress freshness. R023 GitHub CI
passed at https://github.com/N0zoM1z0/th075/actions/runs/37004206011.

R025 adds four complete CRT origins / 1,881 bytes. The two memory-copy bodies
have 46 independently resolved COFF-local relocations apiece, including all
embedded pointer tables. The local unwind helper has one checked pointer to
a separate, complete 34-byte vendor handler that was not in the initial
candidate inventory. `__fptostr` adds two direct calls bound to reviewed
`_strlen` and `_memmove`. Verify with `verify-runtime-local-origins.py` and
`verify-runtime-origins.py`; the latter now runs the former before accepting
local-body callees. The 212-address prior CRT fingerprint survey has 208
pending addresses; no other direct-call-only observation currently has all
callee origins independently verified. Current origin totals are 1,017 reviewed
and 3,334 pending. Exact remains deferred at 42 functions / 8,916 bytes.
R025 public no-auth Funnel verification passed across the local CRT, linked
runtime, static, compiler, authored and SDK origin verifiers, with target-required
tracking/status. Private receipt `.analysis/public-r025-origin-verification.json`.
Local CI passed 68 regressions; the SVG remains current. R024 GitHub CI passed
at https://github.com/N0zoM1z0/th075/actions/runs/37004893091.

R026 reviewed 31 complete short SDK COMDATs / 630 bytes, each with a separately
checked typed caller witness; the callers themselves remain uncredited.
R027 then reviewed 15 complete JPEG/zlib SDK bodies / 4,129 bytes with 34
independently bound direct calls. The SDK verifier now covers 306 bodies /
77,498 bytes, 140 direct-call fields, 374 unchanged indirect calls, 158 scalar
bindings and 232 readonly-section fields. `verify-sdk-origins.py` also runs
the R026 typed-witness verifier. Current totals are 1,063 reviewed / 3,288
pending; exact remains deferred at 42 functions / 8,916 bytes. Candidate
function-pointer fields, mutable globals and other unbound SDK calls stay
pending. No query or compiler session is active.
R026/R027 public no-auth Funnel verification passed across SDK, runtime,
static, compiler and authored origins, plus target-required tracking/status.
Private receipt `.analysis/public-r026-r027-origin-verification.json`. Local
CI passed 72 regressions and progress is current. R025 GitHub CI passed at
https://github.com/N0zoM1z0/th075/actions/runs/37005233600.

R028 reviews three complete JPEG decoder SDK COMDATs / 830 bytes, with seven
DIR32 function-pointer fields whose symbols resolve to separately verified
complete SDK functions and two independently bound direct calls. The SDK
verifier now covers 309 bodies / 78,328 bytes, 142 direct calls, seven function
pointers, 158 scalars, 232 readonly-section fields and 382 unchanged indirect
calls. `sdk-origin-relocations.csv` has a `target_kind` column; existing
bindings leave it empty, while the seven new pointer rows say `function`.
Current totals are 1,066 reviewed (138 authored, 500 library, 428 compiler),
3,285 pending; exact stays 42 functions / 8,916 bytes. No source or exact credit
comes from R028. Local CI passed 73 tests and the progress SVG is current.
Public no-auth Funnel receipt: `.analysis/public-r028-origin-verification.json`.
R027 published GitHub CI passed at
https://github.com/N0zoM1z0/th075/actions/runs/37005857354.
Next, continue complete origin review; only after every candidate is reviewed,
resume exact work on the core authored functions and their dependencies.

R029 reviews ten more complete PNG/JPEG/zlib SDK functions / 2,093 bytes.
Seven newly matched whole readonly data sections support 12 code fields;
three DIR32 fields contain +256 source addends checked against their source
symbol's position and full section end, including one-past-end pointers.
Thirteen direct calls, five function pointers and one real scalar have their
own evidence. The SDK verifier now covers 319 complete bodies / 80,421 bytes,
155 direct calls, 12 function pointers, 159 scalars, 244 readonly fields from
88 whole sections, and 394 unchanged indirect calls. Current totals are 1,076
reviewed (138 authored, 510 library, 428 compiler) and 3,275 pending; exact
remains 42 functions / 8,916 bytes. Public no-auth Funnel receipt:
`.analysis/public-r029-origin-verification.json`. Local CI passed 74 tests;
progress remains current. R028 GitHub CI passed at
https://github.com/N0zoM1z0/th075/actions/runs/37006188725.

R030 excludes three complete six-byte linker import thunks (18 bytes):
DirectInput8Create, Direct3DCreate8 and RtlUnwind. The new
`verify-import-origins.py` decodes all eight PE import descriptors and 157 IAT
slots from the pinned target, then checks each whole `FF 25` body, target slot,
DLL/name and hash. The fourteen other pending six-byte `FF 25` bodies point to
non-import addresses and remain pending. Totals are 1,079 reviewed (138
authored, 510 library, 431 compiler) and 3,272 pending; exact stays 42 bodies /
8,916 bytes. Local CI passed 77 tests and progress is current. Public no-auth
Funnel receipt: `.analysis/public-r030-origin-verification.json`. R029 GitHub
CI passed at https://github.com/N0zoM1z0/th075/actions/runs/37006586340.

R031 reviews eight complete VC7 STL `_Uninit_fill_n`/`_Uninit_copy` bodies /
1,276 distinct bytes, covering 32 original candidates split into main entries
and three local catch fragments apiece. A fresh pinned VC7 probe instantiates
ordinary `std::vector` on synthetic 16-, 44- and 116-byte aggregates; these
widths do not establish the original game record types. The new cold verifier
checks each complete COFF auxiliary/section extent, all seven typed relocation
fields, complete target bytes, internal control flow and exact four-piece
inventory coverage. Keep helper and EH-handler origins independent. Current
totals are 1,111 reviewed (138 authored, 542 library, 431 compiler) and 3,240
pending. Exact remains 42 bodies / 8,916 bytes. Public no-auth Funnel receipt:
`.analysis/public-r031-origin-verification.json`. Local CI passed 80 tests;
progress remains current. R030 GitHub CI passed at
https://github.com/N0zoM1z0/th075/actions/runs/37007109069.

R032 reviews 129 complete VC7 STL record helpers / 7,545 bytes from the R031
probe. The new cold verifier re-extracts all 72 complete record-related source
definitions >=32 bytes and accepts a target only when its whole-body matches
reduce to one generic STL template family. It checks 398 typed relocation
fields (200 REL32, 198 DIR32), hashes and complete CFG. Ninety-six bodies
have synthetic-width aliases within one family; 33 match one width-specific
definition. Eight `copy`/`copy_backward` dual-family matches stay pending.
No original target record type, callee origin, source or exact credit follows.
Current totals are 1,240 reviewed (138 authored, 671 library, 431 compiler)
and 3,111 pending. Exact remains 42 functions / 8,916 bytes. Public no-auth
Funnel receipt: `.analysis/public-r032-origin-verification.json`. Local CI
passed 83 tests; progress remains current. R031 GitHub CI passed at
https://github.com/N0zoM1z0/th075/actions/runs/37007728822.

R033 reviews 23 short STL helpers / 551 bytes and three 51-byte `copy` aliases
/ 153 bytes. Each whole callee source match has a separately verified complete
R031 or R032 caller with a typed REL32 relocation at the actual CALL field.
The three formerly ambiguous aliases are 0x0040F270, 0x0045A7E0, and
0x005FA170; their complete `erase` callers specifically name `copy`.
Five other `copy`/`copy_backward` dual-family candidates remain pending.
The cold verifier checks the whole callee and caller, all relocations, matched
source-family sets and exact witness destinations. Totals are 1,266 reviewed
(138 authored, 697 library, 431 compiler), 3,085 pending; exact stays 42 /
8,916 bytes. Public no-auth Funnel receipt:
`.analysis/public-r033-origin-verification.json`. Local CI passed 85 tests;
progress remains current. R032 GitHub CI passed at
https://github.com/N0zoM1z0/th075/actions/runs/37008140937.

R034 uses a separate ordinary VC7 `std::vector` probe with fourteen synthetic
record widths. Thirty-one complete helper bodies / 1,685 bytes match exactly
one of six generic STL template families; selected probe widths are 4, 8, 20
and 64 bytes, without asserting original game types. The cold verifier scans
all 336 complete source definitions >=32 bytes, checks both whole-body hashes,
all 26 typed REL32 fields and complete control flow. Five further
`copy`/`copy_backward` dual-family matches remain pending. Totals are 1,297
reviewed (138 authored, 728 library, 431 compiler) and 3,054 pending; exact
remains 42 / 8,916 bytes. Public no-auth Funnel receipt:
`.analysis/public-r034-origin-verification.json`. Local CI passed 87 tests;
progress remains current. R033 GitHub CI passed at
https://github.com/N0zoM1z0/th075/actions/runs/37008617872.

R035 reviews twenty independently observed authored bodies / 17,149 bytes:
sprite-node rendering and four-vertex transforms, shared camera easing,
packed replay record I/O and filename selection, and a timed animated scene.
The window resource initializer also loads the game's window texture pack.
Each full target body
has a SHA-256 and a complete decoded local CFG in
`config/authored-origin-evidence.csv`; semantic observations are listed in
`docs/ORIGIN_REVIEW.md`. Names and original class ownership remain inferred.
This grants origin only, without source or exact credit. Totals are 1,317
reviewed (158 authored, 728 library, 431 compiler), 3,034 pending; exact
remains 42 / 8,916 bytes against a provisional 60,180 authored bytes. Continue
origin review before returning to exact reconstruction.
Local CI passed 87 tests; the unchanged no-auth public Funnel MCP also ran
the authored-origin and target-required checks successfully. Private receipt:
`.analysis/public-r035-origin-verification.json`.

R036 reviews six more game-authored bodies / 2,467 bytes. The opening-scene
initializer at `0x004275D0` loads `data\\system\\opening.dat`, explaining the
inferred `OpeningScene` name for R035's timed renderer; its origin evidence
remains local to its own complete body. R036 also covers scene state advance,
input, resource cleanup and two sprite-node transforms. Totals are 1,323
reviewed (164 authored, 728 library, 431 compiler), 3,028 pending. Exact is
still 42 / 8,916 bytes against a provisional 62,647 authored bytes (14.23%).

R037 excludes 80 complete 44-byte VC7 scalar deleting destructors / 3,520
bytes. The new ordinary C++ probe cold-emits one whole generated COMDAT with
two typed REL32 fields; the verifier checks every source/target byte,
both calls, decoded CFG and terminal RET. All wrappers call their own
candidate destructor and the R005-anchored `operator delete` at `0x00640F15`.
Called bodies retain independent origin decisions. Totals are 1,403 reviewed
(164 authored, 728 library, 511 compiler), 2,948 pending; exact remains 42 /
8,916 bytes. Run `scripts/repo-python scripts/verify-scalar-deleting-origins.py`
for cold evidence replay.
Local CI passed 91 tests and the no-auth public Funnel MCP cold-ran the new
verifier successfully. Private receipt:
`.analysis/public-r037-origin-verification.json`.

R038 excludes 53 more complete VC7 `/O1` scalar deleting destructors /
1,484 bytes from a cold build of the same independent fixture. The optimized
28-byte whole COMDAT has two typed REL32 calls at offsets +4 and +17; every
target body, call destination, return and local CFG is rechecked. Totals are
1,456 reviewed (164 authored, 728 library, 564 compiler), 2,895 pending;
exact remains 42 / 8,916 bytes against provisional 62,647 authored bytes.
Run `scripts/repo-python scripts/verify-optimized-deleting-origins.py` for
cold evidence replay. Callee origins remain independent.
Local CI passed 92 tests, and the unchanged no-auth public Funnel MCP cold-ran
both deleting-destructor verifiers. Private receipt:
`.analysis/public-r038-origin-verification.json`.

R039 reviews 39 complete D3DX8 five-byte forwarding COMDATs / 195 bytes:
30 codec-base, five DXT, two YUV and two lock wrappers. The verifier checks
the pinned archive's whole source sections and typed JMP relocations, every
target JMP/body hash, all matching source aliases, destination body/relocation
fingerprints, and complete readonly codec vtables. The three codec callee
origins remain pending; this batch grants the forwarders' library origin only.
Totals are 1,495 reviewed (164 authored, 767 library, 564 compiler), 2,856
pending; exact remains 42 / 8,916 bytes against provisional 62,647 authored
bytes. Cold replay: `scripts/repo-python scripts/verify-sdk-jump-origins.py`.
Local CI passed 95 tests, and the unchanged no-auth public Funnel MCP ran the
new verifier successfully. Private receipt:
`.analysis/public-r039-origin-verification.json`.

R040 reviews 23 further game-authored menu, replay, result and battle bodies /
36,859 bytes. Every complete target extent has a SHA-256 and local CFG check;
the `ORIGIN_REVIEW.md` table records the behavior supporting each origin.
Inferred names remain provisional. This batch reveals the music-room and
name-entry flows, replay browsing, results pages, character card-list loading,
and paired battle renderers as candidate clusters for later exact work.
Totals are 1,518 reviewed (187 authored, 767 library, 564 compiler), with
2,833 pending. Exact remains 42 / 8,916 bytes against a provisional 99,506
authored bytes (8.96%). Run
`scripts/repo-python scripts/verify-authored-origins.py` for cold extent and
CFG replay. Finish the remaining origins before exact reconstruction.
Local CI passed 95 tests. The unchanged no-auth public Funnel MCP ran the
authored verifier and target-required status checks; private receipt:
`.analysis/public-r040-origin-verification.json`.

R041 reviews 21 complete game-authored card-list, character-selection, title
and battle functions / 18,004 bytes. The complete hash and decoded CFG are
recorded for each; `ORIGIN_REVIEW.md` gives the local behavioral evidence.
Totals are 1,539 reviewed (208 authored, 767 library, 564 compiler), with
2,812 pending. Exact remains 42 / 8,916 bytes against a provisional 117,510
authored bytes (7.59%). Continue all origin review before exact work. R040
GitHub CI passed at https://github.com/N0zoM1z0/th075/actions/runs/37014655658.
Local CI passed 95 tests. The unchanged no-auth public Funnel MCP ran the
authored verifier and target-required status checks; private receipt:
`.analysis/public-r041-origin-verification.json`.

R042 reviews 32 complete battle collision, overlay, HUD and effect-rendering
bodies / 37,531 bytes. Each whole-body hash and direct CFG is cold-checked;
the neutral effect-pattern names remain provisional. Totals are 1,571
reviewed (240 authored, 767 library, 564 compiler), with 2,780 pending.
Exact remains 42 / 8,916 bytes against provisional 155,041 authored bytes
(5.75%). Continue origin review before exact work. R041 GitHub CI passed at
https://github.com/N0zoM1z0/th075/actions/runs/37015090609.
Local CI passed 95 tests. The unchanged no-auth public Funnel MCP ran the
authored verifier and target-required status checks; private receipt:
`.analysis/public-r042-origin-verification.json`.

R043 reviews 37 additional complete authored bodies / 21,846 bytes around
result pages, transition callbacks, character selection, the staff roll and
progress records. Hashes, extents and local CFG are cold-verified; inferred
names remain provisional. Small ambiguous wrappers, empty methods, destructor
bodies and unresolved jump tables stay pending. Totals are 1,608 reviewed
(277 authored, 767 library, 564 compiler), with 2,743 pending. Exact remains
42 / 8,916 bytes against provisional 176,887 authored bytes (5.04%). Finish
origin review before exact work. R042 GitHub CI passed at
https://github.com/N0zoM1z0/th075/actions/runs/37015681021.
Local CI passed 95 tests. The unchanged no-auth public Funnel MCP ran the
authored verifier and target-required status checks; private receipt:
`.analysis/public-r043-origin-verification.json`.

R044 reviews three complete central scene-state functions / 7,479 bytes. A
new cold verifier checks each exact direct jump-table guard, all table bytes,
every in-body destination, and the complete extent and CFG. Character select,
title selection and battle state advance have inferred roles only. Totals are
1,611 reviewed (280 authored, 767 library, 564 compiler), 2,740 pending;
exact remains 42 / 8,916 bytes against provisional 184,366 authored bytes
(4.84%). No exact work resumes until origin review is complete. The unchanged
no-auth public Funnel MCP runs the origin verifier and target-required checks;
private receipt: `.analysis/public-r044-origin-verification.json`.
R043 GitHub CI passed at
https://github.com/N0zoM1z0/th075/actions/runs/37016850140.

R045 reviews 27 complete authored battle-collision, fighter-state, resource
and effect bodies / 21,301 bytes. Each whole-body hash and direct CFG is
cold-checked; `ORIGIN_REVIEW.md` records the observed role for each. Template
copies and container assignments in the same region stay pending. Totals are
1,638 reviewed (307 authored, 767 library, 564 compiler), 2,713 pending;
exact remains 42 / 8,916 bytes against provisional 205,667 authored bytes
(4.34%). Continue all origin review before exact work. Local and public MCP
verification details and the R044 CI result are recorded in the review log.
Private public-MCP receipt: `.analysis/public-r045-origin-verification.json`.

R046 reviews five complete Reimu-specific fighter bodies / 14,840 bytes,
including a 14,141-byte action dispatcher with 749 verified in-body direct
branches. The constructor literal `reimu`, derived vtable and common fighter
calls ground ownership; adjacent forwarding/empty methods remain pending.
Totals are 1,643 reviewed (312 authored, 767 library, 564 compiler), 2,708
pending. Exact remains 42 / 8,916 bytes against provisional 220,507
authored bytes (4.04%). Local CI and the public MCP verification passed;
private receipt:
`.analysis/public-r046-origin-verification.json`. R045 GitHub CI passed at
https://github.com/N0zoM1z0/th075/actions/runs/37018599753.

R047 reviews 31 complete character-specific action and AI bodies / 304,135
bytes. Ten action dispatchers have checked calls to game input/transition
routines; 21 AI-choice functions branch on opponent geometry, fighter state
and action IDs. Vector and math helpers called by them retain independent
origins. Each body is wholly hashed and has in-extent direct CFG.
Neighboring functions with unresolved indirect jumps remain pending. Totals
are 1,674 reviewed (343 authored, 767 library, 564 compiler), 2,677 pending;
exact remains 42 / 8,916 bytes against provisional 524,642 authored bytes
(1.70%). Character identity and original method names remain unresolved.
Local CI and the unchanged no-auth public MCP verification passed; private
receipt: `.analysis/public-r047-origin-verification.json`. R046 GitHub CI
passed at https://github.com/N0zoM1z0/th075/actions/runs/37019016587.

R048 reviews 31 complete character object, timed-sequence and fighter-move
dispatchers / 1,155,910 bytes. A total of 90 guarded jump tables (63 remapped,
27 direct) have fully hashed remaps/tables and checked in-body destinations.
The whole extents and branch counts are replayed by the authored verifier;
character identities remain provisional. Totals are 1,705 reviewed (374
authored, 767 library, 564 compiler), 2,646 pending; exact remains 42 /
8,916 bytes against provisional 1,680,552 authored bytes (0.53%). Continue
all origin review before exact reconstruction.
Local CI and the unchanged no-auth public MCP verification passed; private
receipt: `.analysis/public-r048-origin-verification.json`. R047 GitHub CI
passed at https://github.com/N0zoM1z0/th075/actions/runs/37019902898.

R049 reviews 44 complete medium-sized character functions / 88,471 bytes.
Eleven special-action update/render pairs have 22 fully checked guarded
tables; 22 other helpers handle effects, command strings, fighter state and
custom drawing with complete direct CFG. Address-qualified roles and
character identities remain provisional. Totals are 1,749 reviewed (418
authored, 767 library, 564 compiler), 2,602 pending; exact remains 42 /
8,916 bytes against provisional 1,769,023 authored bytes (0.50%). Continue
all origin review before exact reconstruction.
Local CI and the unchanged no-auth public MCP verification passed; private
receipt: `.analysis/public-r049-origin-verification.json`. R048 GitHub CI
passed at https://github.com/N0zoM1z0/th075/actions/runs/37020738880.

R050 reviews 52 complete named character constructor/factory/object/reset
and special-variant bodies / 9,572 bytes. Ten constructor literals identify
Marisa, Sakuya, Alice, Patchouli, Youmu, Remilia, Yuyuko, Yukari, Suika and
Meiling; Reimu's constructor was reviewed in R046. Eleven complete
ten-case direct jump tables are cold-verified. Generic-looking adjacent
wrappers and the Youmu STL/catch cluster remain pending. Totals are 1,801
reviewed (470 authored, 767 library, 564 compiler), 2,550 pending; exact
remains 42 / 8,916 bytes against provisional 1,778,595 authored bytes
(0.50%). Continue origin review before exact work.
Local CI and the unchanged no-auth public MCP verification passed; private
receipt: `.analysis/public-r050-origin-verification.json`. R049 GitHub CI
passed at https://github.com/N0zoM1z0/th075/actions/runs/37021220821.

R051 excludes 25 complete VC7 STL template aliases / 1,004 bytes by cold
compilation of four independently evidenced whole relocation-free COMDATs.
Their full target bytes and CFG match source; shorter generic matches remain
pending. Totals are 1,826 reviewed (470 authored, 792 library, 564
compiler), 2,525 pending. Exact remains 42 / 8,916 bytes against provisional
1,778,595 authored bytes (0.50%). Run
`scripts/repo-python scripts/verify-vendor-identical-origins.py` to cold replay
this batch before exact work, which remains gated on all origins reviewed.
Local CI and the unchanged no-auth public MCP cold replay passed; private
receipt: `.analysis/public-r051-origin-verification.json`. R050 GitHub CI
passed at https://github.com/N0zoM1z0/th075/actions/runs/37021584341.

R052 reviews 23 complete early game functions / 12,010 bytes: a custom
archive index reader/writer, config.ini pair, text rasterizer, progress
defaults, battle-state snapshots, globals/sound setup and several
music/replay/result scene helpers. All have full target hashes and decoded
CFG; owner layouts and some call-site-specific renderer names remain
provisional. Totals are 1,849 reviewed (493 authored, 792 library, 564
compiler), 2,502 pending. Exact remains 42 / 8,916 bytes against provisional
1,790,605 authored bytes (0.50%). Continue all origin review before exact
work. See ORIGIN_REVIEW.md for address-level evidence and unknowns.
Local CI passed 98 tests; target-required tracking, progress freshness and
the unchanged no-auth public Funnel MCP verification passed. Private receipt:
`.analysis/public-r052-origin-verification.json`. R051 GitHub CI passed at
https://github.com/N0zoM1z0/th075/actions/runs/37022186738.

R053 reviews 22 complete game functions / 5,215 bytes: both `score.dat`
layouts and ranked-score insertion, glyph extraction, archive catalog
operations, and battle-end/loading/logo/replay/result callbacks. Full target
hashes and local CFG are recorded; some iterator and scene-owner names remain
provisional. Totals are 1,871 reviewed (515 authored, 792 library, 564
compiler), 2,480 pending. Exact remains 42 / 8,916 bytes against the
provisional 1,795,820 authored bytes (0.50%). Continue origin review before
exact reconstruction.
Local CI passed 98 tests; target-required tracking, progress freshness and
the unchanged no-auth public Funnel MCP verification passed. Private receipt:
`.analysis/public-r053-origin-verification.json`. R052 GitHub CI passed at
https://github.com/N0zoM1z0/th075/actions/runs/37022645391.

R054 reviews ten complete authored bodies / 2,980 bytes: two scene cleanup
routines, six battle-layer drawing routines, an input-bit packer and a
round-field recorder. The drawing repeats and scene class owners are not
overinterpreted. Totals are 1,881 reviewed (525 authored, 792 library, 564
compiler), 2,470 pending. Exact remains 42 / 8,916 bytes against provisional
1,798,800 authored bytes (0.50%). Continue all origin review before exact
work; see ORIGIN_REVIEW.md for complete target evidence and unknowns.
Local CI passed 98 tests; target-required tracking, progress freshness and
the unchanged no-auth public Funnel MCP verification passed. Private receipt:
`.analysis/public-r054-origin-verification.json`. R053 GitHub CI passed at
https://github.com/N0zoM1z0/th075/actions/runs/37022960028.

R055 reviews 52 complete background-stage functions / 8,527 bytes: 34
constructors with target-resident BG00–BG09 asset paths and 18 paired
sprite drawers. The new background verifier rechecks every full body,
CFG, direct call and literal path. A tampered asset witness was rejected.
R056 reviews 32 complete 91-byte transform/copy bodies / 2,912 bytes;
the transform verifier checks that all non-call bytes and both direct
game-call targets match the first member. Tiny empty virtual methods and
destructor wrappers remain pending. Totals are 1,965 reviewed (609 authored,
792 library, 564 compiler), 2,386 pending. Exact remains 42 / 8,916 bytes
against provisional 1,810,239 authored bytes (0.49%). Finish origin review
before exact reconstruction.
Local CI passed 98 tests; target-required tracking and progress freshness
passed. The unchanged no-auth public Funnel MCP replayed both new background
verifiers, all authored-origin extents and tracking. Private receipt:
`.analysis/public-r055-r056-origin-verification.json`. R054 GitHub CI passed
at https://github.com/N0zoM1z0/th075/actions/runs/37023216064.

R057 reviews 34 complete 28-byte background destructors / 952 bytes. A
cold pinned VC7.1 fixture emits the explicit-source shape and a different
implicit 19-byte shape; the verifier checks whole source COMDATs, both typed
relocations, every target byte and CFG, and each target vtable against an
R055 constructor. Two further BG05b/BG08a constructor/destructor pairs
remain pending. Totals are 1,999 reviewed (643 authored, 792 library, 564
compiler), 2,352 pending. Exact stays 42 / 8,916 bytes against provisional
1,811,191 authored bytes (0.49%). Finish origin review before exact work.
Local CI passed 98 tests; target-required tracking and progress freshness
passed. The unchanged no-auth public Funnel MCP cold-compiled the probe,
verified the destructors and all authored-origin extents, and rechecked
tracking. Private receipt: `.analysis/public-r057-origin-verification.json`.
R055/R056 GitHub CI passed at
https://github.com/N0zoM1z0/th075/actions/runs/37024184101.

R058 reviews 86 complete no-op virtual methods / 946 bytes. A cold VC7.1
source fixture emits the entire 11-byte body; each target address is also
bound to a unique slot 1–3 in a separately verified background constructor's
vtable. Three same-byte methods tied to BG05b/BG08a remain pending.
Totals are 2,085 reviewed (729 authored, 792 library, 564 compiler), 2,266
pending. Exact stays 42 / 8,916 bytes against provisional 1,812,137
authored bytes (0.49%). Complete origin review before exact reconstruction.
Local CI passed 98 tests; target-required tracking and progress freshness
passed. The unchanged no-auth public Funnel MCP cold-verified the no-op
source, the R057 destructors, all authored-origin extents and tracking.
Private receipt: `.analysis/public-r058-origin-verification.json`.
R057 GitHub CI passed at
https://github.com/N0zoM1z0/th075/actions/runs/37024823847.

R059 reviews seven complete larger-background bodies / 441 bytes: BG05b
and BG08a asset constructors, their paired explicit-source-shaped
destructors, and three vtable-bound no-op methods. The existing background
verifiers now cover 36 constructors, 36 destructors, 89 no-op methods and
18 side-pair drawers. Totals are 2,092 reviewed (736 authored, 792 library,
564 compiler), 2,259 pending. Exact remains 42 / 8,916 bytes against
provisional 1,812,578 authored bytes (0.49%). Continue origin review before
exact reconstruction.
Local CI passed 98 tests; target-required tracking and progress freshness
passed. The unchanged no-auth public Funnel MCP cold-replayed the expanded
background verifiers, all authored extents and tracking. Private receipt:
`.analysis/public-r059-origin-verification.json`. R058 GitHub CI passed at
https://github.com/N0zoM1z0/th075/actions/runs/37025220392.

R060 reviews 32 complete fighter virtual methods / 440 bytes across all
eleven verified playable-character vtables: eleven direct base-action
forwards and 21 no-op overrides. A cold VC7.1 source probe checks both
whole code shapes, with typed call relocation for the forward method.
The verifier independently binds every method to its constructor-written
vtable slot and checked target call. Totals are 2,124 reviewed (768
authored, 792 library, 564 compiler), 2,227 pending. Exact remains 42 /
8,916 bytes against provisional 1,813,018 authored bytes (0.49%). Finish
origin review before exact reconstruction. Local CI passed 98 tests;
target-required tracking and `git diff --check` passed. The unchanged
no-auth public Funnel MCP cold-verified the fighter probe, all 721
authored-origin extents and tracking. Private receipt:
`.analysis/public-r060-origin-verification.json`. R059 GitHub CI passed at
https://github.com/N0zoM1z0/th075/actions/runs/37025552912.

R061 reviews ten complete compiler-generated implicit derived destructors /
190 bytes. The cold VC7.1 source has one complete 19-byte method with a
typed base-destructor call; the target methods have the same full shape,
call the reviewed fighter cleanup and are individually called by R037
verified scalar-deleting wrappers. Totals are 2,134 reviewed (768 authored,
792 library, 574 compiler), 2,217 pending. Exact remains 42 / 8,916 bytes
against provisional 1,813,018 authored bytes (0.49%). Continue origin
review before exact reconstruction. R060 GitHub CI passed at
https://github.com/N0zoM1z0/th075/actions/runs/37026362298.
Local CI passed 98 tests; target-required tracking, progress freshness and
`git diff --check` passed. The unchanged no-auth public Funnel MCP cold
verified the implicit source, all R037 deleting wrappers and tracking.
Private receipt: `.analysis/public-r061-origin-verification.json`.

R062 reviews four complete scene-lifetime/presentation bodies / 316 authored
bytes. The verifier binds two destructor vtables to previously reviewed
constructors, checks the shared game-global cleanup and scalar deleting
wrapper calls, requires the Title global-state write, and binds the Battle
presentation hook to the accepted exact graphics routine. Totals are 2,138
reviewed (772 authored, 792 library, 574 compiler), 2,213 pending. Exact
remains 42 / 8,916 bytes against 1,813,334 provisional authored bytes
(0.49%). Continue origin review before exact reconstruction.
Local CI passed 98 tests; target-required tracking, progress freshness and
`git diff --check` passed. The unchanged no-auth public Funnel MCP verified
the scene bindings, all 725 authored-origin extents and tracking. Private
receipt: `.analysis/public-r062-origin-verification.json`. R061 GitHub CI
passed at https://github.com/N0zoM1z0/th075/actions/runs/37026646605.

R063 reviews the complete 60,999-byte Reimu action-state dispatcher at
`0x0045DD70`. Its one-RET body has 1,690 internal branches and six
independently checked guarded jump tables (two direct, four remapped)
stored after the RET. The R046 constructor's vtable slot 1 points to the
function. All eleven fighter vtable slot-1 bodies together cover 613,391
authored bytes (32.7% of the provisional denominator). This adds origin
evidence only; no reconstruction source or exact credit. Totals are 2,139
reviewed (773 authored, 792 library, 574
compiler), 2,212 pending. Exact stays 42 / 8,916 bytes against the
provisional 1,874,333 authored-byte denominator (0.48%). Finish origin
review before exact reconstruction.
Local CI passed 98 tests; target-required tracking, progress freshness and
`git diff --check` passed. The unchanged no-auth public Funnel MCP verified
the Reimu dispatcher, all eleven fighter action slots, all 726 authored
extents and tracking. Private receipt:
`.analysis/public-r063-origin-verification.json`. R062 GitHub CI passed at
https://github.com/N0zoM1z0/th075/actions/runs/37027429693.

R064 reviews three complete authored bodies / 43,868 bytes: a
character-adjacent auxiliary constructor, its 31,352-byte slot-1 action
dispatcher, and a 12,400-byte routine in slot 16 of Meiling's fighter
vtable. Both dispatchers have fully bounded jump tables after their final
RETs. Their original method names and the auxiliary object's exact
identity remain unknown. Totals are 2,142 reviewed (776 authored, 792
library, 574 compiler), 2,209 pending. Exact stays 42 / 8,916 bytes
against 1,918,201 provisional authored bytes (0.46%). Continue origin
review before exact reconstruction.
Local CI passed 98 tests; target-required tracking, progress freshness and
`git diff --check` passed. The unchanged no-auth public Funnel MCP verified
both switches, all 729 authored-origin extents and tracking. Private
receipt: `.analysis/public-r064-origin-verification.json`. R063 GitHub CI
passed at https://github.com/N0zoM1z0/th075/actions/runs/37028175815.

R065 reviews eight complete authored game bodies / 19,028 bytes, including
the literal-marked character/stage loading pair and six scene/battle/fighter
dispatchers. Ten complete guarded switches cover 75 table entries; the
verifier checks the full bodies, table data and target-owned loader logging
calls. Totals are 2,150 reviewed (784 authored, 792 library, 574 compiler),
2,201 pending. Exact stays 42 / 8,916 bytes against 1,937,229 provisional
authored bytes (0.46%). Continue origin review before exact reconstruction.
Local CI passed 98 tests; target-required tracking, progress freshness and
`git diff --check` passed. The unchanged no-auth public Funnel MCP verified
all eight dispatchers, all 737 authored-origin extents and tracking. Private
receipt: `.analysis/public-r065-origin-verification.json`. R064 GitHub CI
passed at https://github.com/N0zoM1z0/th075/actions/runs/37028835995.

R066 reviews four complete authored bodies / 3,101 bytes for options,
music-room catalog loading and progress decisions. Five complete guarded
tables cover 28 entries. The verifier checks the `musicroom.dat` literal,
archive call, option sound call, whole bodies and CFG. Nine nearby repeated
vector routines remain pending cold vendor-source and typed-binding proof.
Totals are 2,154 reviewed (788 authored, 792 library, 574 compiler),
2,197 pending. Exact stays 42 / 8,916 bytes against 1,940,330 provisional
authored bytes (0.46%). Continue origin review before exact reconstruction.
Local CI passed 98 tests; target-required tracking, progress freshness and
`git diff --check` passed. The unchanged no-auth public Funnel MCP verified
the four bodies, all 741 authored-origin extents and tracking. Private
receipt: `.analysis/public-r066-origin-verification.json`. R065 GitHub CI
passed at https://github.com/N0zoM1z0/th075/actions/runs/37029350867.

R067 reviews six complete authored bodies / 5,219 bytes: the effect-pattern
catalog loader, two auxiliary object spawn methods, Suika and Yukari
vtable-slot-19 special-state updates, and a projectile update. The
verifier checks full extents/CFG, the archive literal and call, auxiliary
constructor calls, and both fighter vtable bindings. Totals are 2,160
reviewed (794 authored, 792 library, 574 compiler), 2,191 pending. Exact
stays 42 / 8,916 bytes against 1,945,549 provisional authored bytes
(0.46%). Continue origin review before exact reconstruction. R066 GitHub CI
passed at https://github.com/N0zoM1z0/th075/actions/runs/37029800827.
Local CI passed 98 tests; target-required tracking, full authored extent
verification, progress freshness and `git diff --check` passed. The no-auth
public Funnel passed all 15 HTTPS smoke checks, including Ghidra and a
cold exact-unit replay. The private receipt is under `.analysis/deployment/`.

R068 reviews the two remaining pending entries in the inspected 23-slot
range of the eleven playable-fighter vtables: their shared slot-0
animation binder and Alice's slot-19 special-state updater. Complete
body/CFG and vtable bindings are rechecked by
`scripts/repo-python scripts/verify-fighter-final-virtual-origins.py`.
Totals are 2,162 reviewed (796 authored, 792 library, 574 compiler),
2,189 pending. Exact stays 42 / 8,916 bytes against 1,945,954 provisional
authored bytes (0.46%). Continue origin review first. R067 GitHub CI
passed at https://github.com/N0zoM1z0/th075/actions/runs/37030747665.

R069 reviews two combat hit-response dispatchers / 2,129 bytes. One calls
the other directly; their guarded switches cover a 31-byte remap and 13
complete table entries. `scripts/repo-python
scripts/verify-combat-reaction-origins.py` rechecks body/CFG/table hashes
and the caller edge. Totals are 2,164 reviewed (798 authored, 792 library,
574 compiler), 2,187 pending. Exact stays 42 / 8,916 bytes against
1,948,083 provisional authored bytes (0.46%). Continue origin review
first. R068 GitHub CI passed at
https://github.com/N0zoM1z0/th075/actions/runs/37031049890.


## Archived handoff before F023 finalization (2026-10-23)

The following snapshot preserves the pre-cleanup handoff from `adb173c`,
including historical goal, commit-format and next-step wording. Those statements
are archival; the current handoff and AGENTS.md take precedence. F023 acceptance
and the latest cleanup are recorded in the current handoff and knowledge base.

# TH075 function reconstruction handoff

Updated 2026-10-23. The user explicitly resumed the authored exact-reconstruction
goal after cleanup and handoff, with the prior 95% authored-byte target.
Accepted coverage is **110 functions /52,810 code bytes (2.68%)**.
Preserve all accepted origins and the 97 documented unknowns.

The current commit subject format is `gpt-6.1-sol: ...`.
Keep compiler builds serial and low priority, monitor CPU/memory, and cold-replay
only new/affected units. No accepted source, ABI, flags or relocation changed
in this handoff; accepted units did not need rebuilding.

Start here, then consult `RE_WORKFLOW.md` for acceptance rules and the F021
section at the end of `KNOWLEDGE_BASE.md` for detailed per-state observations.
The historical origin checkpoints below remain evidence, not current tasks.

F020 accepted three complete battle dependencies: body separation at
`0x00449310` /1,861, round-transition update at `0x0043D010` /847 and overlay
timeline at `0x00446D80` /1,461. All three units cold-replay exact across one
new object: 4,169 bytes /101 relocations /16 readonly constants. All 106 prior
units and 46 prior source/header inputs remain unchanged and were not rebuilt.
After F020, exact coverage was 109 functions /38,669 code bytes (1.96%). The
cumulative manifest then froze 49 F010-F020 transitions and twenty-six new inputs.

Body separation uses complete SDK RECT values and existing exact collision
helpers. Two observed edge-result bytes are a bounded local array, not an owner.
The +1 limit result corresponds to the left boundary and -1 to the right;
globals retain player 0/1 or -1. Natural scalar float lvalues preserve native
x87 evaluation and copy instructions; real local naming controls reproduce
stack allocation without padding, inert locals or assembly.
Round-transition and overlay reuse F019 receiver interfaces unchanged. The
2-case overlay switch is a linear decision tree, with no omitted data table.

At the F020 checkpoint, all 3,603 CI tests passed (63.1 seconds), with target-required
tracking, progress freshness and whitespace checks. Serial low-priority
builds kept sampled available memory above 8 GiB. Two obsolete diagnostic
objects were removed (21,918 bytes); final objects and original evidence remain.

The three proposed sprite drawing bodies at `0x0040CA80` /1,132,
`0x0040CEF0` /994 and `0x0040D2E0` /970 instantiate a 132-byte geometry owner.
F011 confirms only its first four 16-byte coordinate records; the call at +64
does not establish a fifth coordinate record or a complete matrix owner.
Those drawing bodies and the related HUD renderers remain deferred. The new
partial `SpriteTransform` interface is only used through existing receivers;
complete SDK point temporaries do not establish the original class identity.
Both empty helpers and the integer abs helper retain their unknown origins.

The sequence policy `0x00445A00` /1,958 remains deferred. Its entire body has
one write to local [ebp-4] at `0x00445A50` after the first deque-front call and
no reads of that local. An original declaration or natural purpose for this
discarded snapshot is unproven; do not add an inert local to obtain a match.

## F021 handoff checkpoint (draft only)

The Reimu action handler at `0x0045DD70` has 60,999 code bytes and 1,090
contiguous switch/remap bytes: **62,089 bytes must be compared**. Seven trailing
INT3 bytes are alignment. All 143 non-default destinations across six switches
(two direct, four remapped) are drafted in `.analysis/reimu/Preview.cpp` and its
18 case includes. These private sources are compiler-only: do not execute,
register or award exact credit to the draft.

The restored draft compiles to 62,090 bytes with 16,837 instructions. It still
has 6,311 physical operand differences, first at `0x0045FDA9` in state 89.
Five accumulator-specific encodings explain the net one-byte size difference;
this is not a single-byte defect. Register-class normalization aligns every
instruction, all 1,684 direct branch destinations and 142 table destinations,
but does not prove register dataflow equivalence or byte equality.

The final diagnostic binds all 1,824 relocations: 1,020 direct calls, 630
readonly-constant references (45 unique constants), 142 switch destinations,
10 switch/remap addresses and 22 references to two writable globals. Callees
cover 20 distinct symbols; six indirect slot-zero calls also agree in static
sequence. These are diagnostics, not acceptance. The full comparison still
reports `size-mismatch`.

| Local artifact | Purpose |
| --- | --- |
| `.analysis/f021-45dd70.asm`, `f021-reimu.c`, `f021-decompile.log` | Original target read and attested decompile |
| `.analysis/f021-dispatch-audit.json`, `f021-switch-map.json` | Complete native extent, CFG and switch evidence |
| `.analysis/f021-draft-progress.json` | Current source hashes, final object hash and unresolved task |
| `.analysis/f021-draft-call-check.json` | Static direct/indirect call sequence |
| `.analysis/f021-alignment-register-classes.json` | Normalized instruction, branch and table diagnostic |
| `.analysis/f021-draft-relocation-bindings.json` | All relocation bindings, with target/object hashes |
| `.analysis/f021-register-probes.json` | Reverted compiler controls and code hashes |
| `.analysis/f021-whole-diagnostic.json` | Failing whole-function size comparison |

All abbreviated artifact names in this table are below `.analysis/`. These
ignored files and the draft are **not in a Git clone**. A local handoff must
retain `.analysis/reimu/`, the F021 evidence/scripts/receipts, the pinned target,
private Ghidra project, and final objects. Shared `.tools` installations remain
read-only and may require provisioning separately on another machine.

To reproduce the checkpoint, run from the repository root, serially:

```bash
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/validate-tracking.py --require-target
scripts/repo-python scripts/report-reconstruction-status.py --summary
scripts/repo-python scripts/ghidra.py check
scripts/repo-python scripts/audit-reimu-dispatch.py --output .analysis/f021-dispatch-audit.json
nice -n 10 scripts/compile-probe.sh .analysis/reimu/Preview.cpp build/probes/F021Preview.obj /Od /Ob0 /Gy /GR- /GX- /Zi /I src
scripts/repo-python .analysis/f021-check-draft-calls.py
scripts/repo-python .analysis/f021-align-diagnostic.py --register-classes
scripts/repo-python .analysis/f021-bind-draft-relocations.py
scripts/repo-python scripts/ci.py
git diff --check
```

A new compile can change debug metadata and the whole-object hash; refresh the
private progress receipt after rebuilding. The current compiled function hash
is `e2b757b2007e18c766a2978cfcab4c03a97fbb05831b04264ad50e9b360fafe6`.
F021 remains pending natural register allocation from state 89, preserving
the full CFG and real local lifetimes. The next bounded draft is F022 below. Rebind relocations
and cold-replay the complete function/tables before updating exact ledgers.
Do not repeat reverted controls without new evidence; see the knowledge base.

## F022 accepted: Reimu action-priority dispatcher

`ReimuFighter::DispatchActions` at `0x0046D300` cold-replays **exact over all
14,141 code bytes**. The following three INT3 bytes are alignment and earn
no credit. The complete R046 origin and target hash remain unchanged.
Canonical source is `src/ReimuActionDispatch.cpp` and its pointer-only partial
interfaces are in `src/ReimuActionDispatch.hpp`; do not instantiate those owners.
All 65 ordered dispatch candidates are implemented, with 3,801 instructions,
749 internal branch destinations and no switch tables.

The manifest binds all 278 relocations: 205 direct calls and 73 references to
nine readonly constants. Both freshly built COFF constant payloads and target
constant bytes were checked. The vector helper retains its library origin and
gets no reconstruction credit. All 109 prior units and their source/header
inputs remain unchanged. The cumulative adoption manifest freezes 50 function
transitions and 28 new inputs since F009; its historical prefixes and origin
records remain guarded.

```bash
scripts/repo-python scripts/replay-exact-units.py --unit reimu-fighter-dispatch-actions
```

Private evidence: `.analysis/f022-46d300.asm`, `f022-dispatch.c`,
`f022-decompile.log`, `f022-dispatch-audit.json`, `f022-relocation-bindings.json`,
`f022-accepted-replay.json` and `f022-draft-progress.json` (all under `.analysis/`).
The private audit and binding scripts reproduce complete diagnostic observations;
acceptance is the canonical cold command above. The old partial source wrapper,
first-cohort snapshot and preview object were removed after acceptance (28,619
bytes); the final matching object and all native evidence remain.

Final F022 verification: all 3,603 CI tests passed in 74.179 seconds, including
retained-history, origin, tracking and progress-card checks. The adoption test
now pins 50 reviewed additions /42,927 bytes above the F009 baseline; no unknown
origin receives credit. Final sampled available memory was 8.7 GiB and CPU was
87% idle, with 16 KiB/s swap-in and no swap-out in that interval. Compiler jobs
remained serial and low priority.

F021 remains the next pending large body. Its complete 143-case draft still
has 6,311 physical operand differences and a size mismatch. F022 confirms a
concrete compiler distinction worth investigating there: parenthesized float
leaf lvalues can change x87 expression evaluation order. The two state-88
C-style short-cast controls reproduce the baseline and were reverted; other
float-expression grouping remains unresolved. Preserve the full F021
extent, ABI, genuine locals and previous negative controls. No exact credit
is granted to that draft.

## Resumed investigation (2026-10-23)

The state-88 void-return-expression control preserves the baseline function
hash. Moving state-89 negation after floating multiplication adds four
normalized instruction differences (FCHS replaces native integer NEG before
FILD) and does not resolve the first register mismatch. Both were reverted;
the final restored preview retains the baseline hash and full diagnostic
bindings. See the latest F021 knowledge-base entry and private
`.analysis/f021-register-probes.json` for bounded results. Exact coverage is
unchanged; the 95% goal remains active and incomplete.

Resume verification: all 3,603 CI tests passed in 60.894 seconds, with
target-required tracking, Ghidra attestation and whitespace checks passing.
Builds were serial and low priority; sampled available memory was 8.6 GiB
and CPU was 87% idle with no swap-in/out.

Further F021 investigation: state-88 case scope, `/Zc:forScope`, separate
counter declaration and `+= 1` all reproduce the baseline function hash.
All controls were reverted. The new private
`.analysis/f021-register-dataflow.py` / `.json` checks byte-lane register-use
relations through the complete syntactic CFG: 16,837 reachable instructions,
64,412 checked reads, zero unproven reads under explicit draft ABI assumptions.
It excludes byte/short argument high bytes and 327 immediately overwritten
float stack-slot values. Two negative controls reject a wrong receiver base
that class normalization misses and an undefined high byte of an AL return.
Moving only the first loop counter to function scope also reproduces the
baseline hash. `.analysis/f021-physical-region-map.json` locates all 6,311
physical operand differences in 70 of 143 non-default case regions; state 89
has 19. See the latest knowledge-base entry for assumptions and limits. This provides
no exact credit; 6,311 physical differences and the size mismatch remain.

Latest verification: all 3,603 CI tests passed in 62.674 seconds. The restored
preview was rebuilt serially; its source/function hashes and complete call,
relocation, branch/table and byte-lane diagnostic receipts were refreshed.
No accepted source or ledger changed, so accepted units were not replayed.
Sampled available memory was 7.0–7.9 GiB; the latest interval CPU sample was
88% idle without swap-in/out. Reverted source snapshots were removed after
hash checking; private probe measurements and final artifacts remain.

## Handoff validation

All 3,603 CI tests passed in 64.924 seconds. Target-required tracking, Ghidra
attestation, the full dispatch audit, restored-draft call/alignment/relocation
checks and `git diff --check` passed. Exact coverage remains 109 functions /
38,669 bytes. No accepted source or acceptance ledger changed.

The final sampled available memory was 8.6 GiB; the sampled CPU interval was
75% idle with no swap-in/out. Preview compilation and CI ran at low priority;
no parallel compiler jobs or additional reconstruction work were started.

## Cleanup and retention

This handoff removed 106,741,455 file bytes (108,679,168 allocated bytes,
about 103.6 MiB) of obsolete outputs. The main item was the clean historical
`build/origin-history/r255-baseline` worktree at
`06a81fd59276ead6ff94a6ab05710627558db330`; its `.tools` symlink was unlinked
without touching the shared target. Restore tracked contents if needed with:

```bash
git worktree add --detach build/origin-history/r255-baseline 06a81fd59276ead6ff94a6ab05710627558db330
ln -s "$PWD/.tools" build/origin-history/r255-baseline/.tools
```

Five reverted/generated F021 control snapshots were also removed after
restoring and hash-checking the final draft. `.analysis/handoff-cleanup.json`
records paths, sizes, hashes or recoverable commit identity. Historical logs
that refer to the removed worktree are retained as observations.

Retain the approximately 1.3 GiB `.analysis/vc71-wine` prefix: the historical
`.analysis/r226-tool-env.sh` explicitly selects it. Current preview builds use
the default Wine prefix, but that alone does not establish historical replay
compatibility. Preserve origin evidence, PDB identity observations, accepted
objects, target/game inputs and the private Ghidra database. Other worktrees
outside this repository were not part of cleanup.

Historical origin checkpoint (2026-10-07): work resumed with batches R070–R107, moved to
exact reconstruction for F008 and F009, and has now completed accepted origin
review cohorts R108 through R246, R253, R254, R255, R256, R257, R260, R261, R262 and R263, with bounded unresolved reviews/audits
R247–R252, R258, R259, R264, R265, R266, R267 and R268. The public
repository is [N0zoM1z0/th075](https://github.com/N0zoM1z0/th075) on
`main`. That checkpoint used `gpt-6.1-sol: ...`; the current required format is
recorded above. Keep documentation in English.

## Verified checkpoint

The pinned target is the supplied Japanese `th075.exe` (reported `ver1.11`),
SHA-256 `bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
The initial Ghidra inventory has 4,351 provisional candidates. Origin review
has resolved 4,254: 1,002 authored, 2,671 library and 581 compiler generated.
There are 97 pending. Candidate count is not authored function count.

The exact total is 109 source-present and exact functions, covering 38,669
bytes across 109 match units. Exact coverage of the currently reviewed authored
bytes is 38,669 / 1,973,516 (1.96%). This denominator is provisional because
origin review is incomplete. F008 adds nine reviewed game leaf helpers / 315
bytes; F009 adds nine game policy and dependency helpers / 652 bytes. The
current strategy is authored exact reconstruction. Preserve this baseline and
the original-declaration uncertainties below. The 95%-exact goal is incomplete;
origin review remains separately incomplete.

The canonical state lives in `config/functions.csv`,
`config/function-origins.csv`, the origin evidence CSVs and the exact
match-unit manifests. The progress SVG is generated from those ledgers.
[Origin review](ORIGIN_REVIEW.md) records the evidence and boundaries for
R001–R268; the [knowledge base](KNOWLEDGE_BASE.md) records accepted facts and
explicitly unresolved observations.
The former chronological handoff is preserved in
[handoff history](RE_HANDOFF_HISTORY.md); its earlier counts and next-step
notes are historical snapshots.

## Retained origin-review blocker — original declaration evidence after R268

R268 closes the supplied-archive route for directly stored original symbols.
All 16 original entries are reconciled: 12 complete file streams /1,682,913,434
bytes, four empty directory entries, full length/CRC/SHA-256 checks and the
Japanese EXE member matching the pinned target. No game file or target is
written. Full cross-chunk scans find no MSF7, Portable PDB, RAR, ZIP, 7z or CAB
signature. The two RSDS/original-GUID occurrences are executable inventory,
not recovered PDBs. All 54 gzip markers reject after 131,072-byte bounded
validation; two initial 4,096-byte gaps are retained and resolved explicitly.

A TH75-specific directory hypothesis from pinned upstream thtk source fits all
four actual DAT tables. Counts are 215/34/122/37, totaling 408 entries. Entire
rolling-XOR tables and fixed-name/size/offset records are decoded read-only;
every payload range exactly covers its parent file after the table, without
gaps, overlap or trailing bytes. Directory extensions are DAT/PAT/SCE/WAV,
with no named symbol/source entry. No resource payload schema is reconstructed.
Arbitrary inner encoding remains outside this symbol-discovery audit; there is
no global symbol-absence conclusion or ownership/exact credit.

`config/supplied-symbol-archive-audit-evidence.json` freezes all sixteen complete
metadata witnesses, file hashes/CRCs, all four whole directory/table digests,
408-row metadata digests, signature coverage and source/parser pins. Private
reports and names stay in `.analysis/`. Reproduce the complete immutable audit:

```bash
scripts/repo-python scripts/audit-supplied-symbol-archive.py --archive '<supplied-rar>' --output .analysis/r268-frozen-complete-replay.json --expected config/supplied-symbol-archive-audit-evidence.json
```

All 3,593 CI checks, the full frozen archive replay, target-required tracking,
all 97 complete unknown bodies/pairs and 3,088 original trails, all 60 exact
pairs/28 unchanged inputs and whitespace pass. No compiler build is needed
because production source, ABI, flags, relocations and exact inputs are intact.
Counts remain 4,254 resolved /97 pending /3,608 pending bytes; original 1,311
progress 1,214/97 and exact 60 /9,883 bytes remain unchanged.

The same missing original declaration/type/compiler-generated-member syntax
has remained explicit through R264, R265, R266, R267 and R268. Whole ordinary,
generated and library alternatives cannot be distinguished by more identical
machine-code comparisons. The available local symbol corpus and actual supplied
archive now yield no original declaration witness. An asynchronous question asks
whether an additional original PDB/source/map path exists; no answer is presumed.
Further canonical ownership transitions require new evidence. The user has now
changed strategy to exact reconstruction of reviewed authored functions;
unresolved origins receive no ownership credit. The former final Web MCP run
after complete origin review remains a historical outstanding request, not an
intermediate exact-batch gate. Pushes are now authorized by the new instruction.

### Historical R267 checkpoint and R268 supplied-archive objective

R267 completes a bounded read-only identity lookup under the local `codex_ida`
workspace, including the resolved shared compiler installation inside that root.
The current inventory has 3,224 named PDBs: 3,203 MSF7 and 21 Portable PDB files.
Every current candidate has identity metadata read; none matches the original
target identity. Fourteen MSF files have surplus physical pages: explicit
identity-only reads remain inside declared pages, retain the discrepancy and
do not establish complete PDB validity. Portable metadata has GUID+stamp and no
native age; unequal GUIDs reject these 21 candidates, while an equal GUID would
remain a conversion question. Initial discovery listed 3,227 paths; three
unrelated temporary build PDBs disappeared before the final inventory and remain
gaps in that initial snapshot. No global absence or ownership conclusion follows.

`config/local-pdb-identity-audit-evidence.json` records format/count coverage,
the complete metadata-witness digest, private report hashes, parser/source pins,
the original required GUID/age and unchanged canonical totals. Candidate paths
and full metadata reports remain in `.analysis/`. Repeat the current lookup with:

```bash
scripts/repo-python scripts/audit-local-pdb-identities.py --root /home/pentester/coding/codex_ida --output .analysis/r267-current-pdb-identity-audit.json
```

This produces a new current report; the frozen R267 manifest is historical and
must not be rewritten to hide later corpus changes. Directory symlink targets
outside the enumerated root, other extensions and nested archives are excluded.
All 15 new regression checks and all 3,584 CI checks pass. Target-required
tracking, all 97 complete unknown bodies/pairs and 3,088 old evidence trails,
all 60 exact pairs and 28 unchanged inputs pass. No compilation/source/ABI/flags
changed and no new exact acceptance is claimed.

The next bounded R268 task is the original supplied RAR's complete 16-entry
content/header audit. R266 verified its Japanese target member and entry names,
but did not inspect renamed PDB or nested-archive content signatures. Read each
entry without replacing the target or writing shared tools. Preserve complete
entry sizes/hashes and identify actual MSF/portable/nested archive framing; a
signature alone is discovery, requiring full bounded identity validation before
any claim. Keep content and paths private and record unresolved nested formats.
Do not repeat ordinary compiler controls without a new discriminatory witness.

Counts remain 4,254 resolved /97 pending /3,608 pending bytes; original 1,311
progress is 1,214/97 and exact remains 60 /9,883 bytes. The original goal is
active and incomplete. One final complete Web MCP acceptance remains due after
the requested remaining review. No push was authorized.

### Historical R266 checkpoint and R267 identity-lookup objective

R266 closes the inline declaration/linkage alternative and retains both original
special members as unknown. Replay
`scripts/repo-python scripts/verify-sdk-inline-special-member-review.py`; see
[R266 review](ORIGIN_REVIEW.md#r266--complete-inline-special-member-alternatives-and-original-pdb-identity).
Both complete cold profiles retain32 ordinary sections672/681,92 header hashes,
all actual definitions/AUX/fields/vtables and layout[16,24,24]. Explicit inline
base ctor24 is a whole positive with ANY2; explicit inline derived dtor11 is a
whole negative with ANY2, while implicit derived dtor5 is a whole ANY2 positive.
Derived ctors26/30 remain whole negatives against22. Source selection alone
therefore cannot identify generated syntax. Original compiler disparity and
all old out-of-line controls remain intact. No canonical or exact credit follows.

The new original-input witness is the pinned Japanese EXE's genuine external
PDB reference. Its whole debug directory28 and RSDS payload78 agree through
both RVA and file-pointer reads. Exact original UTF-8 path:
`D:\nonotaro\works\東方萃夢想\東方萃夢想.pdb`.
Required GUID:`9306058f-6d68-4650-b80b-1e0d05dd1e18`; age:`3`.
All fields, hashes and raw path bytes are frozen in the R266 manifest. Its COFF
symbol table is empty, but the debug reference is present. This is an identity
for a possible external witness, not recovered private declarations or a
classification. Do not infer absence of debug information from an empty COFF
symbol table or confuse generated3077 probe PDBs with this original identity.

The actual supplied RAR at the sibling `game_exe/` path was read with `unrar`;
its Japanese member again hashes to the pinned executable. Private
`.analysis/r266-supplied-archive-symbol-audit.json` retains full archive identity,
all16 entry names and zero named PDB/DBG/MAP/C/C++/header entries. This does not
exclude renamed/nested data. The bounded initial path inventory
`.analysis/r266-symbol-artifact-paths.txt` has12840 local symbol/archive paths
under `/home/pentester/coding/codex_ida`; no Japanese-title PDB was found by name.
It is discovery only:exact PDB GUID/age matching, renamed candidates, uppercase
extensions, controlled symlink targets and metadata formats remain untested.

R267 must inspect local candidate PDB identity streams read-only, regardless of
basename. Use actual MSF/PDB framing, bounded stream/page reads and strict GUID
plus age comparison. Record corpus roots, unique physical files, format coverage
and failures; do not turn skipped/unparsed files into an absence conclusion.
Shared tools stay read-only. Preserve the exact target and all97 unknown pairs.
If a matching file exists, validate its complete identity and inspect actual
DBI/TPI/symbol/source metadata before relying on any type or origin claim; public
and private symbol variants may share an identity. A match alone earns no origin,
source, mapping, ABI or exact credit. Keep any recovered metadata private until
bounded independently checked evidence is ready. No exact scope is added.

R266 current cold replay, all3569 CI checks, target-required tracking, all97
current pairs/full body hashes and3088 original trails, all60 exact pairs/28
unchanged inputs and whitespace pass. Counts remain4254 resolved /97 pending /
3608 pending bytes, original1311 progress1214/97 and exact60 /9883 bytes. The
original goal stays active and incomplete; reviewed-but-unknown completion is
not presumed. One final complete Web MCP acceptance remains due after the
requested remaining review. These commits stay local; no push was authorized.

### Historical R265 checkpoint and R266 inline-control objective

R265 completes the entire original SDK compilation/frame witness audit without
an origin transition. Replay
`scripts/repo-python scripts/verify-sdk-compilation-witness-audit.py`; see
[R265 review](ORIGIN_REVIEW.md#r265--complete-original-sdk-compilationframe-witness-audit).
All146 COFF member identities,136 whole C11 object/compiler streams and the
complete C7 CVTRES resource stream are reconciled. All2751 whole FPO16 records
bind actual same-unit static/external offset0 definitions and match complete
code section sizes, totaling507699 source bytes. Every frame/field is pinned by
per-unit complete-metadata digests and reconstructed on every replay. Nineteen
whole pending SDK members1298 in13 objects,480 original structured alternative
records across15 unchanged manifests and every current unknown pair/body hash
are retained. No private declaration/type record or generated-member marker
exists in this corpus. Resource CVTRES7.0.9111 is not a C++ compiler profile.
Missing source/type metadata and FPO stack fields cannot decide ownership.

A focused original/control AUX readback identifies a precise untested source-
level alternative. Original Buffer constructor24 at6200DA and StringBuffer
destructor5 at620132 use ANY selection2. R264's explicitly written out-of-line
ordinary base constructor24 and explicit derived destructor11 use NODUPLICATES
selection1; its implicit derived destructor5 uses ANY2. These are actual COFF
records, not names or inferred global compiler flags. Do not conclude that ANY2
means compiler generated:an explicitly inline member can also emit an ANY body.

The next bounded action is to add a complete natural explicit-inline declaration
control for this same two-member cohort. Keep all generic owners fully defined,
meaningful fields and truthful public-interface ABI. Retain complete Ob0/Ob1
emission, actual includes, definition/AUX/selection, vtables and every genuine
field. Compare full constructor/destructor bodies and keep any changed inlining
extent as a whole negative; do not crop or introduce noinline/assembly/padding
to restore a convenient size. This is a specific linkage/declaration-control gap,
not a repeat of the unchanged out-of-line family. Original FE13.0.9176/BE13.0.9178
versus pinned3077 disparity remains. No canonical transition or exact scope is
preauthorized by a new ordinary match. Keep both special members unknown until
new independent evidence actually distinguishes original source ownership.

Current counts remain4254 resolved =1002 authored+2671 library+581 compiler,
97 pending /3608 bytes and3252 excluded; original1311 progress1214/97. Exact60 /
9883 bytes /60 units /eleven objects and authored1973516 are unchanged. R265
local replay, all3560 CI checks, target-required tracking, all97 current pairs/
full hashes and3088 original trails, all60 exact pairs/28 unchanged inputs and
whitespace pass. The original goal stays active and incomplete; the unanswered
reviewed-but-unknown end-state question does not authorize shrinking it. Final
complete Web MCP acceptance remains due after the requested remaining review.
These commits stay local; no push was authorized.

### Historical R264 checkpoint and R265 metadata discovery

R264 completes the whole StringBuffer source contribution review while retaining
620132 /5 and6200DA /24 as unknown. Replay
`scripts/repo-python scripts/verify-sdk-string-buffer-review.py`; see
[R264 review](ORIGIN_REVIEW.md#r264--complete-stringbuffer-contribution-with-special-member-ownership-unresolved).
All25 code sections1030, packed primary981, full57 initialized sections1716,
three vtables84, constants8 and54 actual fields compare unmasked with complete
CFGs. Complete new14/delete5/ftol39 providers and independent cold SDK/UUID
GUID identities are retained. Original weak entries have search characteristic2
and real `_G` fallbacks; do not silently reinterpret them as unconditional aliases.

Two cold3077 profiles retain all46 ordinary sections941/975 and92 header hashes.
Both have coherent base ctor24/user-written direct-POD ctor22/implicit dtor5
positives. Whole explicit empty dtor11 and generic base dtor16 stay negatives.
The separate StringState model retains reordered ctor22 /13 differences under
Ob1 and full non-inlined ctor26 under Ob0. No original private layout or source
syntax is recovered by these generic complete owners or genuine field bindings.

The archived Buffer object's entire148-byte C11 debug stream has only object-name
and compiler records:FE13.0.9176/BE13.0.9178 with no debug information, versus
actual cold3077 FE/BE13.10.3077. This is a unit-specific archive observation,
not an executable-wide compiler identification. Different probe-version explicit
negatives cannot settle original explicit/generated source syntax. Do not reopen
this same ordinary family without a genuinely new declaration/compiler witness.

Fresh private `.analysis/r265-sdk-debug-survey.json` inventories all146 original
SDK COFF members:137 `.debug$S` sections and2751 `.debug$F` sections, no `.debug$T`.
136 complete C11 streams have only one object-name and one compiler record each;
all report no debug information. Profiles are134 C++ and one C unit with
FE13.0.9176/BE13.0.9178, plus one C unit with FE/BE13.0.8685. The resource
member2148824 `obj\i386\d3dx.res` has signature1 and remains explicitly unparsed
in this discovery. Reconcile this complete metadata survey, the resource's actual
extent/record format and the19 pending SDK lifetime candidates against their
own defining objects and prior complete ordinary alternatives. This is a bounded
search for new original type/declaration witnesses, not an origin transition.
Absent records do not prove compiler ownership or permit forced classification.
The whole824-member code survey, opaque list-policy alternatives and all97
original pending review trails remain intact. No exact scope is added.

Current counts remain4254 resolved =1002 authored+2671 library+581 compiler,
97 pending /3608 bytes and3252 excluded. Original1311 progress1214 classified
/97 left; exact60 /9883 bytes /60 units /eleven objects and authored1973516 are
unchanged. R264 cold replay, all3551 CI checks, target-required tracking, all97
current pairs/full body hashes and3088 old structured trails, all60 exact pairs/
28 unchanged inputs and whitespace pass. The reviewed-but-unknown end-state
question is still unanswered; do not shrink or falsely complete the original
goal. One final complete Web MCP acceptance remains due after the requested
remaining review. These commits stay local; no push was authorized.

### Historical R263 checkpoint and R264 discovery

R263 accepts only641DAA /11 as inferred library through the complete source-
ordered abs11/abs64 auxiliary28 contribution39 at641DAA..641DD1. Source object
member1282072 `build\intel\mt_obj\abs.obj` retains all eight initialized
sections642, real definitions/AUX/COMDAT and full native CFGs. The auxiliary28
is untracked context and gains no candidate or exact credit. Details:
[R263 review](ORIGIN_REVIEW.md#r263--complete-crt-abs-contribution-with-separate-labs-ambiguity-retained).

The fresh full824-member survey retains both original abs/labs whole11
alternatives. Separate641FB8 /11 stays unknown:the one-function labs object and
nearby complete memcmp alone supply no independent source-owner witness.
New whole ordinary int/long positives11 agree at both addresses. Complete wide
expression28/four branch-order differences and intrinsic public wide22 remain
whole negatives. All five ordinary sections84, actual stdlib include and
layout[4,4,8] are retained. No original declaration or global compiler profile
is inferred. The full unchanged original R129/R128 and R163 graphs cold-replay
in read-only same-length676e346 Git state, preserving every old unknown snapshot,
source/predicate/manifest and complete public controls.

Fresh private `.analysis/r264-contribution-survey.json` compares all97 full
candidate extents against all4400 initialized code sections from824 original
SDK/CRT objects. It retains86 whole-section discoveries covering20 candidates
and complete initialized inventories for39 original source units. Field-free
matches are whole byte comparisons; relocated matches exclude only genuine
four-byte fields and record observed destinations as discovery, never an
independent provider catalog. The77 candidates without a source-section match
gain no authored/compiler conclusion from absence.

One new lead is620132 /5:source member380178 `obj\i386\cd3dxbuffer.obj`,
section52, actually defines `??1CD3DXStringBuffer@@UAE@XZ`, with a genuine REL32
tail to the same member's complete Buffer destructor21 at61FE0A. Earlier R249
had only a whole ordinary forwarding observation without this archived source
association. Private `.analysis/r264-string-buffer-discovery.json` freezes the
actual definition/AUX/field and the full original object inventory. Its25
original whole code sections also include StringBuffer constructor22, Init36,
AddString269, deleting wrapper28 and CreateStringBuffer81. Reconcile every
whole native contribution/data/provider/CFG and original canonical/auxiliary
boundary before relying on this lead. Preserve all compiler-versus-library
special-member alternatives:the source mangling, vtable, parent destructor and
source-unit placement alone do not decide whether this derived destructor was
explicit or compiler generated. No canonical transition or exact credit is
assigned to this discovery.

Do not mechanically promote opaque list node-link/value leaves41E100/41F7F0/
531D80/540280. Fresh prior-record review confirms R207/R229/R242/R243 already
retain full typed construction/insertion/erase/consumer chains and genuine
ordinary/intrusive alternatives; those old complete witnesses are not new
ownership distinctions. The fresh whole-source survey and this source-owned
StringBuffer lead are new evidence to pursue. No exact scope is added.

Current counts:4254 resolved =1002 authored+2671 library+581 compiler,
97 pending /3608 bytes and3252 excluded. Original1311 progress is1214 classified
/97 left. The matrix rereads all97 full hashes/current pairs and3088 original
structured record trails, preserving original R251116-row evidence. The
reviewed-but-unknown end-state question is unanswered; do not shrink or falsely
complete the original goal. Final complete Web MCP acceptance remains due
after the requested remaining review.
Exact60 /9883 bytes /60 units /eleven objects and authored denominator1973516
are unchanged. All3542 CI tests, target-required tracking, current-pair/hash,
exact full-row/input, progress and whitespace guards pass. Complete original/
accepted R263 and full retained R129/R128/R163 cold replays pass. These commits
remain local; no push was authorized. Use unchanged historical Git replays for
old strict unknown snapshots rather than rewriting their verifiers/manifests.

### Historical R251/R252 context before R253 acceptance

R251 completes the [116-row pending review matrix](ORIGIN_PENDING_REVIEW.md).
Every whole target body and original structured record trail/hash was read
back; 114 RET-based CFGs and both complete native tail cases are retained.
This is an evidence/missing-witness report, not an origin transition or full
replay of every historical source proof. The R251 attested global queries for
the coordinate helper's two destinations find only its own writes, supplying
no new consumer identity. Preserve that bounded limitation.

R252 supplies stronger new context for `0x004065D0` /19 and `0x004065F0` /19:
fresh genuine direct-vector global initialization28/finalization15, complete
constructor42 and its allocator children, storage126, destructor19/clear19
alternatives and cleanup103/110 compare unmasked with all selected target
bytes. The four actual static wrappers use the same two globals as the
corresponding accepted library constructor and pending cleanup. Whole natural
single-member implicit/explicit owners instead construct through another22
and destroy through the vector destructor19, not directly through Tidy103.
This is a new ownership-context lead, not merely the old callee association.

Next assess whether this complete same-global source/context chain identifies
the two outer bodies as vendor library lifetimes, accounting for inherited or
ordinary explicit wrappers and the limited per-unit compiler inference. If it
does, freeze a durable whole verifier and original-to-accepted transition,
replay the complete retained static/vector/cleanup provider graph, and run the
required checks before accepting either origin. Do not count the private
comparison as accepted now. Neither original element type nor arbitrary game
owner layout has been recovered. No exact scope is added.

Private `.analysis/r252-global-vector-context.json` retains all213 initialized
sections25,241 bytes including debug records, the separate complete64-byte
BSS section, all definitions/AUX/fields, all27 header hashes and layout
[4,80,16,16,16,16]. Its ordinary initialized code/data subset is117 sections /
4,722 bytes. Twenty whole comparisons /827 bytes include two same-target
clear/destructor alternatives; the distinct target set is18 extents /789
bytes. Unselected source sections are inventories, not invented target
mappings. The entire unchanged R090 CLI cold-replays its retained R089 graph;
this does not replay every R004 or CRT provider. All canonical and exact
inputs remain unchanged. R252 source and objects are private observations.

The full goal remains1195 classified /116 left and active. The pending user
clarification about an end state retaining documented unknowns is unanswered;
do not presume a scope change. The requested final complete Web MCP acceptance
remains due after the remaining-review end state is satisfied.

### Retained R250 and R249 discovery

R250 retains625575 /14 and64F513 /12 as unknown after complete824-member
source-reference coverage,whole mapped PE value scans,attested Ghidra queries,
genuine complete ordinary14/12 equality and unchanged entire R155 cold replay.
All five source incoming fields are debug/FPO records, not code/data references.
FillZeroMan12 was already reviewed in R155; this rediscovery is not new credit.
The full goal remains1195 classified /116 left and active. The user pushed
throughc9b8efa; subsequent commits remain local. Preserve all accepted origins
and exact60. One complete Web MCP acceptance remains due after all remaining
origin review. No scope clarification is presumed.

The complete116-row review matrix records whole observed behavior,
original source/context evidence and each missing independent witness.
Every row is reconciled against the current target/canonical state and old
literal records. Keep ownership unresolved wherever evidence is
non-identifying; snapshots,source equality,library parents and metadata hits do
not themselves establish origin. The user has been asked whether completed
review may retain documented unknowns before final MCP acceptance, or must
resolve all origins. That clarification is pending; do not shrink the goal or
run final MCP as if it had been answered. Continue independent review work.

R250 private `.analysis/r250-reference-survey.json` retains all ordinary source
objects/fields for both function names. Exactly five references are debug/FPO;
35 PNG source sections1121 and38 intrncvt sections6289 are complete source
inventories, not invented target mappings. `.analysis/r250-compare.json` freezes
whole ordinary14/12 controls and layout[64,12,4]; both are source positives only.
The unchanged full R155 CLI cold-replays. `.analysis/r250-remaining-pointers.json`
records raw value occurrences for all116 pending extents; no-candidate-caller
rows have no absolute occurrences in mapped file-backed sections, but computed/
interior/runtime reachability remains unproven. All canonical and exact inputs
stay unchanged. Do not repeat these same zeroing controls as a new distinction.

R249 private `.analysis/r249-evidence-map.json` records all116 current pairs,
full instructions/hashes/CFG limitations, original structured record trails and
documentation locations. Categories9 source-control/decision,50 source-carrier,
71 retention/pending and89 canonical/context overlap.38 have no discovered
structured source/control/retention record beyond snapshots;37 have no address
hit in the two searched review documents. These are discovery limitations,
not proof of no prior investigation. Use the map to choose genuinely new
context after each unresolved outcome. All4351 canonical pairs and exact60
inputs remain unchanged; no ledger transition is authorized merely by coverage.

R248 private `.analysis/r248-diagnostic.json`/log freezes the entire original
constructor25/destructor89/deleting28/public56+176+176/DDS833/Load469 context,
all COFF/AUX/fields and whole linked CFGs. Fresh generic24-byte owners are not
the original84-byte image object. Implicit/empty122 and35 source pairs retain
genuine member/EH fields without invented original providers; entire explicit98
and88 controls keep all88/25 differences to target89. Original private types,
outer default syntax and profiles remain unknown. The entire unchanged R204
main cold-replays. All4351 canonical pairs and exact60 inputs are unchanged.
Fresh `.analysis/origin-scan/r248-triage.json` records116 pending/current hashes.

R247 private `.analysis/r247-diagnostic.json`/log re-read original constructor104
and full13-slot table52 unmasked. Complete factory126 allocates1172 and invokes
constructor then Init134 on the same owner; actual public descriptor is16,
level word+0x1C and viewport24 at+0x474. The original object has debug$S/F but
no private type debug$T or source-file definitions. Complete natural generic
implicit and empty99 constructors are equal and automatically perform refcount1,
null initialization and260-word bulk clearing; both retain all67 differences to
all104 target bytes and full source tables52 compare. Generic layouts/profiles
are observations, not original private layouts/default syntax/compiler flags.
The five paired profiles and grouped/un-grouped helpers remain private diagnostic
data; the original SDK candidate stays unknown. Fresh
`.analysis/origin-scan/r247-triage.json` records116 pending/current ledger hashes.
Move to other eligible candidates rather than repeatedly treating this same
bulk-zeroing observation as a new ownership distinction.

R246's whole original SDK E76 and callback9 reproduce unmasked from pinned
`obj\i386\cd3dxblt.obj`. Genuine fresh compiler E76 has three differences at
39/40/41 because its real array-delete symbol binds64169D and original SDK E
actually uses scalar-delete640F15. This field remains honest; fresh E76 is a
whole negative, while callback9 matches. Full scalar31 and ordinary callers16
retain every difference. Complete SDK parents1140/930 and entire array runtime96
retain context. The new generic12 layout is not an original private SDK layout
or a global compiler profile. The entire unchanged R198 main runs under a
single validated read-only selected historical pair, preserving all original
source/weak/fields/public/constructor/default/copy/layout/predecessor proofs;
old manifests and their two literal selected unknown snapshots stay unchanged.
The five other R198 lifetime candidates remain unknown. Fresh
`.analysis/origin-scan/r246-triage.json` records116 pending/current ledger hashes.

R245 freezes full explicit265, cleanup/handler51, metadata60, observed current
three-slot table12, both deleting wrappers44, SDK size/index/member closures
and genuinely emitted implicit105/empty114 controls. Actual child wrapper425460
calls independently accepted texture cleanup40AE40 / 434, not adjacent LogoScene
initializer425490 / 183. Array-delete64169D and scalar-delete640F15 are distinct
bound entries. Complete initializer395, filename scanner613, selector1005 and
render2246 establish replay ownership; original private ABI, element types,
virtuality and table extent remain unknown. Generic source owner76/child4 do
not recover the original sizes: initializer writes +0x51 and allocates child80.
All old evidence and the entire R072/R077 cold graph remain unchanged. Fresh
`.analysis/origin-scan/r245-triage.json` records117 pending/current ledger hashes.

R244's whole effect-manager destructor85 calls actual owned-pointer cleanup221
before automatic four-deque array destruction. Whole original R166 cold replay
retains twelve literal checked historical successor pairs. Geometry14 at40D980
and40D9F0 remains unknown: complete SDK and ordinary empty construction are
observationally compatible. Earlier R158/R161/R162/R212/R226/R233 protected
copy/assignment, lifetime and cleanup ambiguities remain authoritative. The
60-function exact baseline and all reconstruction inputs remain unchanged.

R243's whole front32 calls independently accepted begin531DA0 /42 and mutable
dereference540240 /19,which calls const dereference540260 /25 and opaque
payload540280 /11. Entire39,999-byte CharacterObject::Advance536400 loads the
same actor+0xFEC list and consumes returned record offsets0/2/4/8/12/14. Original
R170/R049 complete insertion/allocation/context independently establish generic
value16/node24/cursor4. Fresh source closes every call through actual full
defining begin and both iterator constructors. Entire ordinary First32 remains
equivalent; original spelling/private element/layout/ABI/profile remain unknown.
Opaque540280 /11 and531D80 /8 retain unknown. Fresh private
`.analysis/origin-scan/r243-triage.json` records119 pending/current ledger hashes.

R242's whole archive arrow19, mutable dereference19 and const dereference25
form one source-owned chain; postfix42, mutable prefix22 and const prefix35
form the other. Complete archive writing and both named seeks create cursors
from the same owner+4 begin/end and consume actual names, sizes and offsets.
The postfix target retains its hidden result pointer and RET8; Ghidra's missing
argument/return recovery is not an original ABI declaration. Full ordinary
arrow19/postfix42 alternatives remain byte-equal. Opaque nextnode8 at41E100 and
payload11 at41F7F0 stay unknown.

Original R169 standalone CLI retains its historical snapshot rejection. R242
cold-replays that entire unchanged main with exactly eight checked later
successor metadata pairs projected to their literal old rows. All original
source/compiler/object behavior, manifests, registered frames, positives,
node-width negatives and layouts remain unchanged. The historical view does
not describe today's canonical labels. Fresh private
`.analysis/origin-scan/r242-triage.json` records122 pending and current hashes.

R241's immutable proof accepts 45BA10 / 21 only. The complete fighter initializer
allocates 84 bytes, finishes four-queue construction, stores the manager at
fighter+0x2EC and then supplies that same fighter to the manager binding.
Complete effect spawn consumes the bound pointer for virtual allocation and
copies fighter+0xA4. Ordinary/template 21-byte members reproduce, while complete
pointer constructor24, real implicit assignment26, assignment caller15 and
borrowed pointer13 remain distinct. The observed allocation is not a recovered
original private sizeof or class declaration.

Complete 4251C0 / 34 remains unknown. Child GameGlobals::Initialize417210 / 531
returns its receiver; the whole original vtable657B88 contains three purecall
slots. Five complete scene initializers and paired release431F40 / 31 do not
distinguish explicit empty construction from implicit member construction.
The entire original R108 cold proof still checks six candidates, 103 anchors,
98 parent calls and both vtables without changing its source or manifest.

Other private leaf diagnostics are in `.analysis/r241-game-leaf-native.json`.
45B850 / 13 is a no-op RET4;4073A0 and438CF0 / 11 are no-op RET0 bodies.
These shapes alone cannot distinguish hooks, lifetime/member/allocator
operations or ordinary methods. `.analysis/r241-replay-helper-native.json`
likewise shows no-op4138D0 / 11 and no-reference FontSurface-adjacent4135F0 / 40
writing a byte at+0x24 and dwords at+0x1C/+0x20 with RET12. Adjacency is not owner
proof. Do not promote these fingerprints without complete independent context
and source alternatives. Fresh `.analysis/origin-scan/r241-triage.json` records
128 pending with current canonical ledger hashes.

R240 ties primary replay byte queue6718A4 to actual owner671750+0x154, complete
file loading/serialization, live direction/button consumption and battle
completion. It preserves AL-only result use, all four distinct queues and
actual file-backed minimum storage; no fake uint ABI, BSS bytes, private
layout or offset filler is introduced. Its entire ordinary32/borrowed23/
deque25/queue19 alternatives remain negative. R239 independently reopens
complete R213 native game context while the unrelated old vector cold CLI
retains its R211/R227 snapshot rejection; no old plan/runtime is patched.
R238's complete R167/R168 cold views retain exactly checked four/seven later
successor pairs. R236 retains six actual scalar/array-delete differences;
R237 retains R077 destructor-family aliases beside public clear alternatives.

Preserve two no-reference GUID23 candidates608E33/609B1E: both original SDK
and ordinary memcmp forms reproduce, but original archive references are only
.debug$F. Preserve no-reference454C00 /24 and454F70 /31, R108/R198/R204 lifetimes,
R18341CA30 /77, R212455770 /111, five R163 math chains, opaque/node policies and
constructors458650 /31 and458670 /23 as unknown. DwStack61FB37 and codec61A453
retain protected R195/R198 alternatives. Extent questions60C120 /11 and620132
/5 need complete defining source/metadata. Shared tools remain read-only.

## R244 — custom owned-effect cleanup before member destruction

R244 accepts authored `0x0045B9B0` / 85 only, inferred as
BattleEffectManager::DestroyOwnedEffectsAt0045B9B0. The complete CFG[1,0],
original extent and eleven following external INT3 bytes are preserved.
Original name, source/private ABI, mappings and exact state remain unchanged.

Replay `scripts/repo-python scripts/verify-effect-manager-lifetime-origins.py`
with immutable `config/effect-manager-lifetime-origin-evidence.json`, SHA-256
`116da4a1fc4c1bbc5547cb4d84b7dcfa414b579b0c3113b8d4f10b4d462e375e`.
The whole target first calls independently accepted R109 custom cleanup45BA30
/ 221 on its receiver. That policy deletes nonzero pointer entries from four
queues and clears them. It then marks the user body complete and destroys the
member array at+4 with count4, stride20 and genuine deque destructor45BF30 / 19
through the complete96-byte runtime array-destructor helper. The registered
exception frame cleans the same array if the user cleanup throws. Original
scalar deleting wrapper458740 / 44 calls this exact85 and scalar delete640F15
/ 5; the latter's bound jump to whole free642A61 / 113 is preserved rather
than treated as a final-RET body. These are authored ownership observations,
not proof that the original explicit method spelling has been recovered.

Independent whole R166 initialization45B920 / 131 and fighter initialization
4567B0 / 345 retain the same four queues, member offsets and observed84-byte
allocation. Existing R241 binding21 and whole effect spawn282 retain the live
fighter relationship. Eighteen complete anchors / 2,207 bytes and nineteen
canonical pairs are frozen, including original authored/library/compiler
records and three complete registered frames. No earlier owner or extent is
changed. The array destruction helper, EH cleanup and deleting wrapper keep
their independently accepted library/compiler classifications.

Fresh `tests/origin_probes/EffectManagerLifetime.cpp` includes the unchanged
original R166 probe and uses a complete generic84-byte owner with a meaningful
reference word and four genuine SDK deques. Generic float values preserve the
old four-byte payload observation; they are not a claim that original owned
pointers were floats. A compatible external ClearOwned declaration binds only
to the independently verified full221-byte game policy; it is not a recovered
private source declaration. Pinned3077 `/Od /Ob0 /Gy /GR- /GX /Zi /GS /I src
/I probes /showIncludes` emits the entire85-byte explicit cleanup destructor.
The ordinary implicit and explicit-empty destructor alternatives are32 bytes;
each retains all53 missing target tail bytes and every other difference.
Neither contains the observed custom cleanup call.

Seven full comparisons / 280 source bytes and all twenty genuine fields retain
main85, one whole32-byte source EH carrier with cleanup22 and handler10 roots,
one whole36-byte source metadata carrier with unwind8 and FunctionInfo28,
deque destructor19, deleting wrapper44, and both32-byte negatives against the
whole85-byte target. The handler definition at source offset22 and FunctionInfo
at offset8 never justify slicing their original sections. Every actual local
field binds its fresh defining source section/offset; external runtime and
custom-policy bindings retain complete independent original owners. No mask,
source-body patch, fabricated AUX, target byte array or cropped comparison is
used. All155 fresh code/data sections / 7,060 bytes,343 fields,complete COFF/AUX/
line provenance,30 actual include owners,two real weak aliases and the entire
52-byte thirteen-word layout are frozen. The old36-byte layout is literal;
additional current sizes are[84,84,84,20]. They are generic observations, not a
recovered original class size or private layout.

Both-state cold proofs also run the entire unchanged original R166 main with
exactly twelve checked historical successor pairs. Nine belong to R167; two
40E000/5F84B0 belong to R223;45B880 belongs to R222. Each original/accepted pair
is checked against its immutable successor before a read-only projection of
literal historical metadata at the old module-provider seam. All four original
custom policies /600 bytes,three full source positives /397 bytes and the
independent sparse-default203-byte policy,nineteen whole source/code/EH/data
comparisons /1,340 bytes,63 real fields,three complete implicit negatives /
96 bytes,four whole parents /4,897 bytes and both guarded switch tables /
64 bytes,146 old code/data sections /6,709 bytes,29 old SDK include owners,
registered frames and full old36-byte layout replay unchanged. No original
manifest/source/compiler/object,standard-library or subprocess behavior is
patched. The standalone current-state R166 CLI retains its historical snapshot
rejection; the historical view is not a claim about current canonical labels.

Pending40D980 /14 and40D9F0 /14 remain unknown. Full geometry initializers85 /
259 /305 ignore their return values and invoke them at member offsets0/16/32/
48/64 before initializing storage. Private fresh SDK observations reproduce
both14-byte empty constructors and the entire85-byte enclosing initialization;
ordinary empty constructors also reproduce. The original SDK-versus-ordinary
owner/type is not proved, so these diagnostics add no canonical credit and do
not alter the existing exact four-dword helper40DB10 /51.

An empty selected historical audit and strict HEAD16d8007 readback allow exactly
one function/origin pair to change. Original and accepted full cold proofs,
ten new guards,target/tracking,readonly Ghidra attestation and query completion,
fresh118-row triage,progress freshness,all60 exact input preservation and
whitespace checks pass. All 3,416 local CI tests pass.
One complete Web MCP acceptance remains due after all remaining origin review.

Current4,233 resolved =998 authored+2,655 library+580 compiler;118 pending and
3,235 excluded. Original1,311 goal has1,193 classified /118 left and remains
active. Exact60 functions /9,883 bytes /60 units across eleven objects stay
unchanged; authored denominator1,973,300 and provisional0.50%.

## R243 — complete character-list front and dereference closure

R243 accepts library `0x00540220` / 32, `0x00540240` / 19 and
`0x00540260` / 25: three whole methods / 76 bytes. Their inferred operations
are list front, mutable iterator dereference and const iterator dereference.
Original extents, names, source/private ABI, mappings and exact state remain
unchanged. The following external INT3 gaps are0/13/7 bytes; no padding is
credited. Opaque payload540280 / 11 and prior nextnode531D80 / 8 remain unknown.

Replay `scripts/repo-python scripts/verify-character-list-front-origins.py`
with immutable `config/character-list-front-origin-evidence.json`, SHA-256
`2cdf210897cd45171f52cddccd7440d31959ec116356281f435cf39bdd29d818`.
The independently accepted complete R170 character-list begin/end, insertion,
value-node allocation and original R0491008-byte policy establish actor+0xFEC
as the same list with observed value16/node24/cursor4. The complete39,999-byte
CharacterObject::Advance536400 has10,573 instructions, original guarded switch
records and full CFG[1,968]. It loads the actor through receiver+0xE4, adds0xFEC,
calls front32 and consumes the returned record at offsets0/2/4/8/12/14 for
action identifiers, coordinates and direction. All17 whole native anchors /
41,770 bytes and20 canonical pairs are frozen and rechecked. A contextual
instruction window never substitutes for the full owner comparison.

Fresh `tests/origin_probes/CharacterListFront.cpp` includes the unchanged
original character-list policy source and instantiates genuine VC7.1 list
definitions with a complete generic16-byte record. Pinned3077 `/Od /Ob0 /Gy
/GR- /GX /Zi /GS /I src /I probes /showIncludes` emits full front32 calling
genuine begin42 and mutable dereference19; the latter calls const dereference25
and entire opaque payload11. Fresh full begin42, nextnode8 and iterator28 /
const-iterator24 constructors close every real call with its actual defining
source owner. Nine entire unmasked comparisons /221 bytes and nine real fields
include the ordinary First32 spelling, `return *entries.begin()`, which remains
byte-equal. Source-family inference does not prove original method spelling.
Ghidra's void/fastcall recovery for reference-returning methods is not an
original ABI declaration. The original element type, private layout and
executable-wide compiler profile remain unknown; no source or exact credit.

All281 cold code/data sections /12,482 bytes,600 actual fields,complete COFF/AUX/
line provenance,34 actual include owners and three real weak aliases are
frozen. The whole120-byte thirty-word sizeof section preserves all literal
old100-byte arrays and appends[16,12,4,4,12]. The complete ordinary observer
contains a real list member; its size12 is a generic observation, not a recovered
private character type. No incomplete original owner, padding, source byte
arrays, target edits or cropped bodies are introduced.

Both original and accepted cold proofs run the entire unchanged original R170
main with exactly nine checked historical successor pairs. These are
40E000/R223,41206F/4122C9/41EFE6/532196/R218,45B880/R222,5F84B0/R223 and
654ACE/654B0E/R219. Each immutable successor original and accepted pair must
equal its literal old snapshot and today's canonical pair before projection
at the read-only metadata-provider seam. No old manifest/source/compiler/object,
standard-library or subprocess behavior is patched. All twelve old library
dependencies /720 bytes,227 snapshots,80 original source/code/EH/throw/RTTI/data
comparisons /3,763 bytes,189 genuine fields,two whole node-width negatives /
40 bytes,275 old ordinary sections /12,330 bytes,33 old include owners,six
registered frames and whole100-byte layout replay unchanged. The original
standalone current-state CLI still rejects its historical snapshots; the
historical view is not a claim about today's canonical labels.

An empty selected historical audit and strict HEADff7ca2a readback permit only
three canonical pairs to change. All previous origin evidence,protected unknowns
and60 exact inputs remain unchanged. Original/accepted cold proofs,ten new
guards,target/tracking,readonly Ghidra attestation and query completion,fresh
119-row triage,progress freshness and whitespace checks pass. All 3,406 local CI tests pass. One complete Web MCP acceptance
remains due after all remaining review finishes.

Current4,232 resolved =997 authored+2,655 library+580 compiler;119 pending and
3,235 excluded. Original1,311 goal has1,192 classified /119 left and stays
active. Exact60 functions /9,883 bytes /60 units across eleven objects remain
unchanged; authored denominator1,973,300 and provisional0.50%.

## R242 — complete archive iterator access and advancement

R242 accepts library `0x0041E060` / 19, `0x0041E080` / 42,
`0x0041EF20` / 19, `0x0041EF40` / 22, `0x0041F790` / 25 and
`0x0041F7B0` / 35: six whole methods / 162 bytes. Their original extents,
current names, source/ABI, mappings and exact state are unchanged. Their six
following INT3 gaps / 62 bytes remain external. The inferred operations are
mutable iterator arrow, postfix increment, mutable dereference, mutable prefix
increment, const dereference and const prefix increment.

Replay `scripts/repo-python scripts/verify-archive-iterator-operation-origins.py`
with immutable `config/archive-iterator-operation-origin-evidence.json`, SHA-256
`f371d0c970a5a893cd3ce367c8a8a9267af0fb7de3739ed8930bd884ff5a366c`.
The entire independently accepted R169 list begin/end, insertion, allocation,
node and exception graph establishes the archive container and its cursors.
Whole R052 archive writer41D260 / 686 builds108-byte index records, consumes
actual names, sizes and offsets, reads source files and serializes their data.
Full R053 named seeks41D750 / 164 and41D800 / 180 construct begin/end from the
same archive owner+4, compare the actual cursor, use arrow19 for name matching,
read payload+0x68 for file positioning and payload+0x64 for returned size, and
advance through postfix42. Whole R052 index reader41D510 / 429 preserves the
independent record-production context. Twenty complete anchors / 2,264 bytes
and twenty-six scoped canonical pairs are checked with full CFGs/instructions,
original switches and independently accepted authored records.

Fresh `tests/origin_probes/ArchiveIteratorOperations.cpp` instantiates the
original VC7.1 list definitions using the complete generic108-byte archive
observation and pinned3077 `/Od /Ob0 /Gy /GR- /GX /Zi /GS /I src /I probes
/showIncludes`. Full arrow19 calls mutable dereference19, which calls const
dereference25 and the entire payload helper11. Postfix42 calls mutable prefix22,
which calls const prefix35 and the entire nextnode8. Each real field binds its
complete fresh defining owner, coherently across the graph; equal-shaped arrow
and dereference bodies are never interchangeable. Postfix preserves the old
cursor in its hidden output buffer and retains RET8 for that buffer and integer
argument. Ghidra's missing return/argument recovery earns no original ABI claim.

Complete ordinary108-byte arrow19 and postfix42 observations remain byte-equal
after explicitly compatible payload-reference/prefix bindings. Their genuine
external declarations are retained, not claimed as recovered original private
definitions. Ten entire linked source comparisons / 242 bytes and all eight
real call fields are checked unmasked. The8-/11-byte node helpers only supply
whole context and keep their original unknown classifications. Original method
spelling, element type, private layout/compiler profile/ABI remain unknown.
No reconstructed source, mapping or exact credit is added.

All260 fresh ordinary code/data sections / 11,499 bytes,551 actual fields,
complete COFF/AUX/line provenance,33 include owners,three real weak aliases and
the whole108-byte combined27-word sizeof section are frozen. The old88-byte
observer arrays remain literal; the additional generic sizes are[108,4,4,4,4].
No incomplete original owner, padding, target source arrays or cropped bodies
are introduced.

Both-state cold proofs also run the entire unchanged original R169 main with
a guarded historical metadata view. Exactly eight literal unknown snapshot
pairs later accepted by R218/R219/R222/R223 are checked against their immutable
original/accepted successor records before projecting old rows at the existing
metadata-provider seam. No old manifest, source, compiler/artifact, standard
library or subprocess behavior is patched. All13 original library methods /
753 bytes,205 snapshots,80 source/code/EH/throw/RTTI/data comparisons / 3,752
bytes,189 real fields,two complete node-width negatives / 43 bytes,250 original
cold sections / 11,163 bytes,32 original include owners,all six registered
frames and the whole88-byte layout replay. The old standalone current-state
CLI still rejects its historical snapshots; this historical view is not a
claim about current canonical labels.

An empty selected historical audit, strict HEADdeff036 readback and full
unselected-row digests permit exactly six canonical pairs to change. Every
earlier evidence file, protected unknown and all60 exact inputs are unchanged.
Original and accepted cold proofs,seventeen new guards,3,396 local CI tests,
target/tracking,readonly Ghidra attestation/query completion,fresh122-row triage,
progress freshness and whitespace checks pass. Final complete Web MCP acceptance
remains due after all remaining origin review finishes.

Current4,229 resolved =997 authored+2,652 library+580 compiler;122 pending and
3,232 excluded. The original1,311 goal has1,189 classified /122 left and remains
active. Exact60 functions /9,883 bytes /60 units across eleven objects remain
unchanged; authored denominator1,973,300 and provisional0.50%.

## R241 — binding a constructed effect manager to its fighter

R241 accepts authored `0x0045BA10` / 21 only, with its complete CFG [1,0],
incoming pointer store at receiver offset zero, RET4 and eleven following
external INT3 bytes preserved. The inferred name is
BattleEffectManager::BindFighterAt0045BA10. Original name, extent, source/ABI,
mapping and exact state stay unchanged.

Replay `scripts/repo-python scripts/verify-effect-owner-binding-origins.py`
with immutable `config/effect-owner-binding-origin-evidence.json`, SHA-256
`f05fcecfb44b753f2061a0d04b3562941563922e1ddee7f92be525a444b1e0e2`.
Whole R045 FighterState initialization4567B0 / 345 allocates84 bytes, invokes
the independently accepted R166 four-queue initialization45B920 / 131 and
stores its returned manager atfighter+0x2EC. It then pushes that identical
fighter and invokes selected21 on the initialized manager. This is an observed
binding after construction. Whole R045 effect spawn45BB10 / 282 reads the
manager's first field as the fighter receiver, invokes its vtable+0x1C to obtain
an animation object, copies fighter+0xA4 to the created object and appends the
result through a selected20-byte queue. Complete cleanup221, original deque
construction72, release19/19, append217 and exact animation reset52 retain their
previous independent evidence. Seventeen full anchors / 3,217 bytes and eighteen
scoped canonical pairs are checked, including complete switches, exits and
instruction records. Original complete R166131/345 native records and both
actual registered lifetime frames are reopened without patching any historical
source graph; a new full R166 cold replay is not claimed.

Natural `tests/origin_probes/EffectOwnerBinding.cpp` cold-builds with pinned3077
`/Od /Ob0 /Gy /GR- /GX /Zi /GS /I src /showIncludes`. Complete ordinary and
template pointer-binding members each reproduce all21 bytes without fields.
The entire natural pointer constructor24, genuine implicit assignment26,
ordinary assignment caller15 and borrowed pointer write13 remain negative
against the whole target21, including every missing tail byte. The real
member-function pointer forces the compiler's implicit assignment definition;
its actual DIR32 field is retained. All nine ordinary code/data sections /
161 bytes, both real fields, complete COFF/AUX/line provenance, real absence of
includes and weak aliases and the entire20-byte sizeof[4,4,4,4,4] are frozen.
These are complete generic observations, not original private game owners.
The84-byte target allocation does not establish a complete original layout.
Original class/type/spelling/compiler profile/ABI remain unknown; no source,
mapping or exact credit is added.

The investigated scene-base constructor4251C0 / 34 remains unknown. Its whole
GameGlobals child417210 / 531 returns its receiver. The complete readonly
vtable657B88 contains three purecall slots, and five whole independently
accepted scene initializers plus paired release431F40 / 31 preserve the complete
lifetime context. Natural explicit empty and implicit construction remain
indistinguishable. Original and accepted R241 proofs cold-replay the unchanged
entire R108 evidence-only verifier: six complete candidate bodies /176 bytes,
103 whole/candidate anchors,98 parent edges, both vtables and whole typed source
alternatives. All five original lifetime ambiguities remain pending.

An empty selected historical audit, all original unselected-row digests and
strict HEAD530846a bounded readback permit exactly one canonical pair to change.
Every prior evidence file, protected unknown and all60 exact inputs remain
unchanged. Original and accepted cold proofs, twelve new guards,3,379 local CI
tests, target/tracking, readonly Ghidra attestation/query completion, fresh128-row
triage, progress freshness and whitespace checks pass. The final full Web MCP
acceptance remains due after all remaining origin review finishes.

Current4,223 resolved =997 authored+2,646 library+580 compiler;128 pending and
3,226 excluded. The original1,311 goal has1,183 classified /128 left and remains
active. Exact60 functions /9,883 bytes /60 units across eleven objects are
unchanged; authored denominator1,973,300 and provisional0.50%.

## R240 — primary replay-input queue exhaustion

R240 accepts authored `0x004142D0` /35 with its complete CFG, both branches,
AL result and13 following external INT3 bytes preserved. It adjusts the receiver
by0x154, calls the complete public deque size414430 /17 and returns false in AL
when nonempty, true in AL otherwise. The inferred name is
ReplayRecords::IsPrimaryInputQueueEmptyAt004142D0. Ghidra's uint/fastcall recovery
does not establish an original ABI: the upper EAX bytes are not a normalized
Boolean. Current name, extent, source/ABI, mappings and exact state stay unchanged.

Replay `scripts/repo-python scripts/verify-replay-queue-empty-origins.py` using
immutable `config/replay-queue-empty-origin-evidence.json`, SHA-256
`3dbbcaea7887bab375cc8a5f0d37dc6d2746199992ec94058ca78f684deb4cb5`.
Full R035 LoadRecord413AC0 /792 reads replay-file metadata and four distinct
queues atowner+0x154/0x168/0x17C/0x190 with actual1-/2-/1-/4-byte records. The
first queue receives complete one-byte entries after its clear. Full
AppendRecord413DE0 /1252 serializes the same first queue's count and one-byte
entries, retaining its complete iterator loop and real WriteFile calls.
BeginCapture413790 /225, FinalizeFile4138E0 /375 and FindAvailablePath414300 /89
preserve independent custom replay/file provenance. Actual raw-PE imports bind
CreateFileA, ReadFile, WriteFile, CloseHandle and SetFilePointer.

Full R045 FighterState::UpdateControls452F10 /2815 tests and consumes first global
queue6718A4, reads its front byte through complete library454D50 /32 and removes
it through pop_front454D70 /157. Each bit updates actual direction/button
counters. Its recording path appends the produced byte to that identical queue.
Global6718A4 equals owner671750+0x154. Whole R044
BattleScene::AdvanceState43B610 /4764 invokes the selected query on671750 in
observed mode2, explicitly MOVZXes AL and uses true to assign battle state6
under the original guards. It does not consume a presumed uint return.
Twelve complete anchors /10,568 bytes and13 scoped canonical pairs are frozen,
including the whole pop-front empty/destruction children. All original exits,
switches, records, fields and ownership remain literal.

The writable PE section/header and entire actual file-backed420-byte minimum
observed range at671750 are hashed. This is a bounded observed footprint, not
an inferred complete private sizeof/layout or an invented BSS image. No initial
runtime state or extra fields are inferred. Original deque490–493 exposes size;
500–503 exposes empty as a direct _Mysize comparison; queue34–37 forwards empty
to c.empty. Thus the selected custom owner-size policy differs from the genuine
public library operations. Full original R149 size17 and R086 empty25 providers
reproduce, with no source fields and every original typed library record retained.
The unsigned-char size control is one original R149 whole alternative; payload
spelling remains unknown. Genuine queue::empty calls bind the whole original
empty25, never a convenient size17 alias.

Natural `tests/origin_probes/ReplayQueueEmpty.cpp` cold-builds with locked3077
`/Od /Ob0 /Gy /GR- /GX /Zi /GS /I src /showIncludes`. It retains all31 include
owners,9 whole code/data sections /182 bytes,5 actual fields, full COFF/AUX/line
provenance, real absence of weak aliases and entire16-byte sizeof[24,20,20,4].
The compact complete generic owner keeps a meaningful fileHandle and deque at+4.
Its32-byte guard, borrowed23-byte guard, genuine deque::empty25 and
queue::empty19 remain whole negatives against all35 selected bytes, including
trailing missing-source bytes and every real public call field. The actual
original +0x154 offset is never reproduced with filler or a false complete
private owner. Full native replay-byte production, consumption and battle
completion establish the authored source-family inference. Original
owner/type/spelling/layout/compiler profile/ABI remain unknown; there is no
source, mapping or exact credit.

Original and accepted cold proofs also reopen the entire R149 source/context
family, its complete retained R072/R078/R110/R113 graphs, and the entire R086
13-body /325-byte empty family with13 source-typed parent calls. An empty
selected historical audit, original full unselected digests and strict
HEADc9b8efa readback permit exactly one canonical function/origin pair to change.
Every previous accepted evidence file, protected unknown and60 exact input is
unchanged. Both-state cold proofs,12 new guards and3,367 CI tests, target/tracking,
readonly Ghidra identity/query completion, fresh129-row triage, progress freshness
and whitespace pass. Final complete Web MCP acceptance remains due after all
remaining origin review finishes.

Current4,222 resolved =996 authored+2,646 library+580 compiler;129 pending and
3,226 excluded. The original1,311 goal has1,182 classified /129 left and remains
active. Exact60 functions /9,883 bytes /60 units across eleven objects are
unchanged; authored denominator1,972,929 and provisional0.50%.

## R239 — sprite sampling and color-mask parameter writes

R239 accepts authored `0x00410FA0` /22 and `0x00410FE0` /22. Each complete
body writes its incoming byte or dword to the same sprite receiver at+0x10
or+0x14 and retains RET4. Each following ten-byte INT3 gap is external. Names
SpriteSequence::SetSamplingModeAt00410FA0 and SetColorMaskAt00410FE0 are inferred;
current names, extents, source/ABI declarations, mappings and exact state stay
unchanged.

Replay `scripts/repo-python scripts/verify-sprite-render-parameter-origins.py`
with immutable `config/sprite-render-parameter-origin-evidence.json`, SHA-256
`c0045f055de670c4e8f69649ff1f0f31535af4149f547e4ea3f9ad424b218c8c`.
Independent R213 FighterState::SetCommandSelection454BC0 /61 sets actor+0x47C,
then forwards the byte and mask on the same actor+0x480 receiver. Complete
R045 resource installation456B60 /1186 initializes that pointer using the
whole custom R166 constructor410F30 /104. The original constructor assigns
mode5 and limit15, constructs the list at+4 and clears it. Whole
ReimuFighter::AdvanceActionStatesAt0045DD70 /60,999 supplies seven real
selection sequences,
all with selection3, sampling4 and mask0xFF. All seven preserve the identical
actor receiver and three-argument call sequence. The entire action extent,
original guarded switches, all exits/1,690 branches and16,837 decoded
instructions are checked; its full decoded instruction digest avoids storing
a partial disassembly. No comparison crops the action to its call windows.

Full R035 SpriteSequence::RenderElements411110 /746 reads the byte signed,
guards positive sampling and uses signed division/remainder to select records.
It combines the dword at+0x14 by AND with the packet color word at+0x9C, then
ORs the separately computed alpha. Full append411000 /183 produces164-byte
packets on the same list; full fighter draw453F70 /2246 establishes the same
owner pointer and previous R238 removal policy. Twenty complete native anchors
/66,108 bytes and22 scoped canonical pairs are checked. This includes every
original R213 native policy and its four complete game parents /62,405 bytes.
The original short member constructor411C10 /25 and no-reference word setter
410FC0 /24 remain unknown.

The unchanged original R213 pure native game-context verifier is called
independently after its entire original plan/script identities, all complete
native bodies/CFGs, game records and current accepted ownership are checked.
Its four selected historical function/origin snapshots remain literal
unknowns and are compared to the new transitions' original pairs. No old plan,
CSV provider, standard library, subprocess behavior, compiler artifact or
source is patched. The old R213 standalone vector cold CLI still stops in its
R212/R211 chain on three unknown snapshots subsequently accepted by R227;
that actual private failure remains documented. R239 does not claim a new
cold replay of that unrelated vector source graph. Instead, the relevant
whole R238 original sprite/list source proof is cold-replayed, including
unchanged complete R167 and R168 code/EH/data graphs and their explicitly
checked historical views. Every original source and accepted record remains
unchanged.

Natural `tests/origin_probes/SpriteRenderParameters.cpp` cold-builds with
locked3077 `/Od /Ob0 /Gy /GR- /GX /Zi /GS /I src /I probes /showIncludes`.
It reuses the original complete generic R167 model and adds a meaningful
colorMask field. All31 actual include owners,189 emitted code/data sections
/8,309 bytes,392 genuine fields, full COFF/AUX/line provenance and both actual
weak aliases/fallback owners are frozen. Four entire22-byte ordinary and
genuine-template methods /88 bytes reproduce all bytes with zero source
fields. Both complete borrowed-field writes13 remain distinct against all22
target bytes, including their missing-source trailing bytes. The entire
72-byte combined readonly sizeof section preserves both old arrays and new
[20,24,24,1] observations. There is no arbitrary filler or incomplete original
owner. Equality cannot identify original spelling/template, parameter
signedness/type, complete private layout or compiler profile. The independent
custom sampling/color parameter production and consumption establish the
source-family inference; no source/private ABI/mapping or exact credit is
added.

Strict HEAD35ec5f3 readback, original full unselected digests and all22 scoped
pairs allow exactly two canonical function/origin rows to change. All previous
accepted evidence, original snapshots, protected unknowns and60 exact inputs
remain literal. Original and accepted cold proofs,3,355 CI tests including15
new guards, target/tracking, Ghidra identity/query completion, fresh130-row
triage, progress freshness and whitespace pass. One complete Web MCP acceptance
remains due after all remaining origin review finishes.

Current4,221 resolved =995 authored+2,646 library+580 compiler;130 pending and
3,226 excluded. The original1,311 goal has1,181 classified /130 left and remains
active. Exact60 functions /9,883 bytes /60 units across eleven objects remain
unchanged; authored denominator1,972,894 and provisional0.50%.

## R238 — guarded sprite-record list consumption

R238 accepts authored `0x004110C0` /37, preserving its entire CFG, sole
conditional exit and eleven following external INT3 bytes. It tests the list
at receiver+4 using complete public size411CE0 /17, then calls complete public
pop_front411D00 /40 only when nonempty. The inferred name is
SpriteSequence::RemoveFrontIfPresentAt004110C0; current database name, extent,
source/ABI declarations, mappings and exact state remain unchanged.

Replay `scripts/repo-python scripts/verify-guarded-sprite-list-origins.py` with
immutable `config/guarded-sprite-list-origin-evidence.json`, SHA-256
`7928ef70065b69fc93c49265ac3324b6e822cfe3a6a3879e67c6b8fe5d984482`.
The independent whole R035 AppendElement411000 /183 constructs a complete
164-byte packet, including the original132-byte copy, appends it to the same
receiver+4 list and enforces the observed signed-word limit. Full
RenderElements411110 /746 iterates and draws that list. Full R045
FighterState::Render453F70 /2246 appends to owner pointer at actor+0x480 and,
under its original condition, calls the selected removal twice consecutively
on that same receiver. Each call rechecks nonempty. The condition observes
66C237 and actor+0x47C; it does not assign a meaning to the byte or trust its
unrelated Ghidra string alias. Whole R167 ClearEntries4110F0 /22, its complete
R166 parent104 and R045 game anchor1186 retain independent custom ownership.
Thirteen full anchors /4,992 bytes and 21 scoped canonical pairs are frozen.
The complete25-byte member constructor411C10 remains unknown: its forwarding
shape also fits generated member construction.

Original VC7 list429–432 and474–477 retain genuine size/pop_front definitions;
queue69–72 forwards pop unconditionally. Complete new source-owned providers17
and40 reproduce their full target bodies through original typed public
begin411C90 and erase411F20 children, with both genuine fields retained. The
natural complete `tests/origin_probes/GuardedSpriteList.cpp` reuses the immutable
generic R167/R166 model, cold-building with locked3077
`/Od /Ob0 /Gy /GR- /GX /Zi /GS /I src /I probes /showIncludes`. It keeps all34
actual include owners,196 whole emitted code/data sections /8,712 bytes,
all414 genuine fields, complete COFF/AUX/line provenance and both actual weak
aliases with their full fallback ownership. The actual relative probe include
is bound to the fixed repository cwd; no include-log conversion or fallback
parser is used.

The ordinary member guard37 reproduces all bytes and its actual size/pop
fields at14/29. Entire original queue::pop19 and borrowed-list guard25 remain
negative against all37 target bytes; explicit trailing missing-source bytes
are retained. No relocation masking or comparison prefix is used. The entire
72-byte combined readonly sizeof section, including both old arrays and the
new [164,20,20,12] observations, is preserved. These are complete generic
observations, not a recovered private sprite owner/layout. Source equality
alone cannot prove authorship, original spelling/type/template/compiler
profile or ABI. The independent custom packet/render/driver policy supplies
the source-family inference; no original incomplete owner, padding, inert
local, fake return, source/mapping or exact credit is added.

Both original and accepted cold replays reopen the unchanged complete R167
and R168 source proofs, including all182 /8,150 and225 /10,007 emitted
sections/bytes,
31 /1,288 and93 /4,248 whole positive controls, two original R167 negatives,
all genuine call/data fields, full node catch/shared tails, original registered
frames and whole56-/76-byte layout arrays. Their old standalone canonical
checks reject four/seven literal unknown snapshots subsequently accepted by
R218/R219/R222/R223. R238 therefore provides an explicit historical ledger
view only while invoking each unchanged whole verifier in a fresh process.
Every projected pair must equal both the immutable old unknown snapshot and
the successor's original pair; the live pair must exactly equal that
successor's immutable accepted pair. Complete successor manifests/scripts,
plans and transitions are checked. All unrelated rows and other datasets
remain literal. Source bytes, compiler/subprocess behavior and generated
artifacts are never projected or patched. The actual current accepted owners
remain unchanged; old proof summaries describe their historical snapshots.
The earlier standalone rejection remains recorded in private diagnostics.

An empty selected historical-record audit, original full unselected digests
and strict HEAD3985108 readback permit exactly one row in each canonical
function/origin ledger to change. Every previous accepted record/manifest,
protected unknown and sixty exact input remains literal. Original and accepted
cold replays,3,340 CI tests including15 new guards, target/tracking, readonly
Ghidra identity/query completion, fresh132-row triage, generated progress and
whitespace pass. The complete Web MCP acceptance remains due after all
remaining origin review finishes.

Current4,219 resolved =993 authored+2,646 library+580 compiler;132 pending and
3,226 excluded. The original1,311 goal has1,179 classified /132 left and remains
active. Exact60 functions /9,883 bytes /60 units across eleven objects remain
unchanged; authored denominator1,972,850 and provisional0.50%.

## R237 — shared archive catalog first-user policy

R237 accepts authored `0x0041CE10` /56 with its complete CFG, receiver return,
sole conditional branch and eight external INT3 bytes preserved. The function
checks shared count68BE04, tidies both global queues68BE08/68BE1C only for the
first user, then increments the count. Current name, extent, source/ABI,
mappings and exact state remain unchanged.

Replay `scripts/repo-python scripts/verify-archive-catalog-use-origins.py` with
immutable `config/archive-catalog-use-origin-evidence.json`, SHA-256
`33292559e16ded74fa505961ada05d361ccca98edf9a2310a3f6edae52249e2c`.
Independent ArchiveCatalog::Release41CE50 /171 decrements the same count and,
for the last user, deletes registered archive objects, array-deletes stored
names and tidies both same queues. Registration41CF80 /245 appends an object
pointer and copied name to those queues; named closure41D080 /264 searches
names and erases the paired entries. Full object initialization41D190 /90,
file-index loading41D510 /429 and resource cleanup41D1F0 /98 retain their
independent game provenance. Actual raw-PE imports bind CreateFileA, ReadFile
and CloseHandle. Whole main602A60 /2987 uses the identical [EBP-0x35] receiver
for enter/exit and registers the real name/path pairs data/th075.dat,
sound/th075bgm.dat and datab/th075b.dat. Its complete guarded dispatch data,
all exits and original authored records remain literal.

Twenty-eight complete independent anchors total 5,466 bytes; 29 scoped
canonical pairs preserve every accepted owner. Original VC7 deque header
412–415 and 797–800 show both destructor and clear forwarding to _Tidy949–969.
Existing R077 destructor-family aliases and old evidence remain unchanged;
identical 19-byte wrappers do not establish original operation spelling or
object lifetime. Every source field binds its independently recorded _Tidy
owner and typed descendant, rather than inventing a destructor declaration for
clear. The writable PE virtual section/header is checked for shared storage.
These BSS addresses are not file-backed; no raw bytes, initial counter value
or complete private global layout are fabricated.

The complete natural `tests/origin_probes/ArchiveCatalogUse.cpp` cold-builds
with locked3077 `/Od /Ob0 /Gy /GR- /GX /Zi /GS /I src /showIncludes`, retaining
all 27 original includes, 50 whole emitted code/data sections /2,045 bytes,
all 88 actual fields, full COFF/AUX/line provenance and the real absence of
weak aliases. Eight complete unmasked comparisons /542 bytes /28 fields
cover ordinary and genuine template constructors56, four actual public
clear/destructor wrappers19 and both whole _Tidy owners177. The two constructor
forms agree through every real field; source equality cannot determine the
original template spelling or establish authorship without the full independent
custom file/catalog/count context. Genuine implicit two-deque member
construction78 and destruction75 remain distinct, with all their full normal,
exception and data carriers retained. The whole readonly sizeof section
[1,1,20,20,40,4] describes complete compact generic observations only. There is
no incomplete original owner, filler, inert local, fake return, private layout,
original source/type/ABI/compiler-profile claim or exact credit.

Original and accepted cold proofs also reopen the entire retained R077 deque
cleanup and R225 original/manual unchecked-indexing source graphs. An empty
historical selected-record audit, full original unselected digests, 29 scoped
pairs and strict HEAD02ffaf7 readback allow exactly one row in each canonical
function/origin ledger to change. All previous evidence, protected unknowns and
sixty exact inputs remain literal. Local cold proofs, 3,325 CI tests including
12 new guards, target/tracking, Ghidra identity/query completion, fresh133-row
triage, generated progress and whitespace pass. The complete Web MCP acceptance
remains due after all remaining origin review finishes.

Current4,218 resolved =992 authored+2,646 library+580 compiler;133 pending and
3,226 excluded. The original1,311 goal has1,178 classified /133 left and remains
active. Exact60 functions /9,883 bytes /60 units across eleven objects remain
unchanged; authored denominator1,972,813 and provisional0.50%.

## R236 — whole music scene and record lifetime policies

R236 accepts three complete authored origins: scene cleanup `0x004258D0` /244,
record initialization `0x00427430` /50 and record cleanup `0x00427470` /82.
The full 376 bytes retain all exits and external alignment; current names,
source/ABI declarations, mappings and exact state stay unchanged.

Replay `scripts/repo-python scripts/verify-music-scene-lifetime-origins.py` with
immutable `config/music-scene-lifetime-origin-evidence.json`, SHA-256
`3585911a97c2dfb713892494cfb5a7c0b3549bd215f326b3425e24acaa74c09e`.
Independent MusicRoomScene initialization425750 /372 installs the same three
observed readonly table slots, loads `data\system\music.dat`, creates all four
textures and constructs sixty records at sixteen-byte spacing. The complete
original constructor iterator641C78 /98 reads size[EBP+0xC], count[EBP+0x10];
actual pushes60 then16 and full destructor iterator641D4A /96 confirm that
contract. Both helpers retain their normal and exceptional entries and exits.
Whole catalog426DD0 /916 opens `datab` / `musicroom.dat`, sets the byte flag and
separately allocates, copies and NUL-terminates buffers at record+4/+8/+C.
All three complete text renderers426670 /555,4268A0 /452 and426A70 /860 use SHL4
and consume those fields. This independently establishes record spacing and
buffer policy without padding an invented private layout.

The full scene cleanup releases four textures, conditionally deletes its
resource, stops audio407D70 /88, selects track40 through419CB0 /318, restores fade
through419DF0 /27, destroys all sixty records and calls base cleanup431F40 /31.
Twenty-nine whole independent anchors total9,276 bytes. The mixed code/table
_memcpy640F20 /829 is not linearly decoded or cropped: its complete vendor
source record and all46 typed fields are independently replayed by the original
R025 three-body /1,762-byte /93-field proof. Complete ordinary, exception and
readonly carriers remain separate, including whole EH code6557C3 /40 with
roots[0,8,30], two-state map/FuncInfo668B10 /44 and following next-owner bytes.

Cold VC7.1 build3077 with `/Od /Ob0 /Gy /GR- /GX /Zi /GS /I src /showIncludes`
rebuilds `tests/origin_probes/MusicSceneLifetime.cpp` from its tracked path,
checks all73 original included headers,18 complete emitted sections /796 bytes,
all actual source fields, COFF/AUX provenance and three genuine weak deleting
aliases/fallbacks. Seven complete comparisons /548 bytes retain six positive
ordinary/deleting/EH/data carriers /466 and the entire82-byte negative record
cleanup. Natural `delete[] char*` emits scalar ??3 bound to its real640F15 owner;
native calls the distinct array ??_V64169D forwarding to that scalar owner and
whole free642A61 /113. All six different bytes in the three actual call fields
remain explicit. Binding scalar source to the array owner, masking fields or
truncating the comparison is rejected. The superseded private equality diagnostic
used that invalid binding and grants no evidence. Original source type and
compiler lowering remain unknown.

Genuine implicit raw-pointer record and scene lifetimes remain5 and19 bytes,
compared with ordinary50-/82-/244-byte policies. The entire24-byte readonly
sizeof section `[1,16,8,988,16,988]` preserves both definitions, including the
second at offset16. Compact complete generic models use meaningful lifecycle
members and actual public D3D8 releases; no incomplete original owner, filler,
inert local, private tail layout, signature or original compiler profile is
claimed. Whole independent game catalog/render/asset/audio context supports
source-family authorship; normalized source controls add no exact credit.

Every original and accepted cold proof also replays the full retained R130 array,
R154 allocation and R195 graphics dependency graphs. Thirty-two scoped canonical
pairs, original unselected digests, an empty historical selected-record audit and
strict HEADffff98e readback bound the transition to exactly three rows in each
function/origin ledger. All prior evidence, protected uncertainties and sixty
exact inputs remain literal. Local cold proofs,3,313 CI tests including ten new
guards, target/tracking, Ghidra identity, fresh134-row triage, generated progress
and whitespace pass. Full Web MCP acceptance remains due after every remaining
origin review finishes.

Current4,217 resolved =991 authored+2,646 library+580 compiler;134 pending and
3,226 excluded. The original1,311 goal has1,177 classified /134 left and remains
active. Exact60 functions /9,883 bytes /60 units across eleven objects remain
unchanged; authored denominator1,972,757 and provisional0.50%.

## R235 complete options texture/resource cleanup

R235 accepts the complete154-byte authored options scene cleanup428E60. It
conditionally deletes observed resource+8 and releases texture+0xC through
observed virtual slot8 before base cleanup431F40. All four branches, RET0 and
six external INT3 bytes outside428EFA are preserved. The current name, full
extent, source/ABI, mappings and exact state remain unchanged.

Replay `scripts/repo-python scripts/verify-scene-texture-cleanup-origins.py`
with immutable `config/scene-texture-cleanup-origin-evidence.json`, SHA-256
`8f95d8f7c90fbeba274e24cb2ce06be539144b4dbec11e07f6318c0e4108ae19`.
Independent R109 options initializer428D60 /251 installs the same actual table,
clears texture+0xC, constructs/configures resource+8 with the full original
`data\system\option.dat` string and passes the texture field's address to
Graphics::CreateTexture401C20 /340. This complete game producer normalizes
dimensions/formats and calls the whole independently reviewed original
`_D3DXCreateTexture@32` at605B61 /102. Full retained R195 graph cold-replay re-extracts
its pinned original archive and checks every original code/data/API/source field,
all lifetime/getter uncertainties and public ABI controls. An observed virtual
slot alone does not prove a concrete original interface or runtime callee.

All15 complete initializer/table-peer/producer/resource/base/deleting/runtime
anchors total5,385 bytes. Three observed readonly scene table words and following
four bytes retain full paired owner context without recovering a complete class
interface. The original exception/unwind18 and map/FuncInfo36 carriers and their
following next-owner data stay separate. R1084251C0 /34 remains unknown.

The complete natural fixture `tests/origin_probes/SceneTextureCleanup.cpp`
uses the actual pinned public D3D8 declarations and compact generic lifecycle,
resource and scene observations. Cold3077 with `/Od /Ob0 /Gy /GR- /GX /Zi /GS /I
src /showIncludes` checks all73 original included-header hashes,15 whole emitted
code/data sections /522 bytes, all30 actual fields, three genuine weak deleting
aliases/fallbacks, full source COFF/AUX/instructions and readonly `[1,8,16,16]`
sizeof observations. Five complete unmasked comparisons /296 bytes cover the
ordinary154-byte policy, paired deleting44, exception18, data36 and resource
scalar deleting44. The whole raw-pointer implicit destructor19 remains distinct.
The public Release declaration is a natural alternative, not a recovered private
receiver interface. No incomplete game owner is instantiated or padded, and no
original type/name/layout/source spelling/ABI/compiler profile or exact match is
claimed. Authored source-family inference rests on the full independent actual
game asset/texture-production and paired lifetime context.

An empty old selected-snapshot audit,16 scoped canonical pairs, full original
unselected digests and bounded HEADdba4abc readback allow exactly one row in each
function/origin ledger to change. All previous evidence, explicit lifetime/node/
math ambiguities and60 exact inputs remain literal. Original and accepted cold
proofs including the retained whole SDK graph,3,303 local CI tests including
eight new guards, target/tracking, local Ghidra identity, progress, fresh137-row
triage and whitespace pass. Complete Web MCP acceptance remains reserved until
all origin review finishes.

Current4,214 resolved =988 authored+2,646 library+580 compiler;137 pending and
3,226 excluded. The original1,311 goal has1,174 classified /137 left and remains
active. Exact60 functions /9,883 bytes /60 units across eleven objects remain
unchanged; authored denominator1,972,381 and provisional0.50%.

## R234 complete paired scene resource cleanup

R234 accepts five complete127-byte authored policies /635 bytes at4252B0,
425550,42A2C0,42B300 and42E870. Each conditionally deletes the observed
receiver+8 resource and performs base cleanup431F40, preserving all three
branches and RET0. Current names, full extents, source/ABI, mappings and exact
state remain unchanged; proposed scene resource roles are inference.

Replay `scripts/repo-python scripts/verify-scene-resource-cleanup-origins.py`
with immutable `config/scene-resource-cleanup-origin-evidence.json`, SHA-256
`63e3d06ca902c40cfe7fa767639ba697f5705bb4bd048494adac7cab3157ceec`.
Five independently accepted complete initializers /1,486 bytes install the same
actual tables, construct/store the same observed resource field and load actual
`data\system\load.dat`, `logo.dat`, `replay.dat` and `result.dat` assets. The
name-entry initializer's actual directory string is `datab`, preserved literally.
Each observed readonly table retains three original code words, all whole peer
bodies and separately checked following data. The first slot's complete44-byte
compiler deleting wrapper binds the selected cleanup. These observed slots do
not recover a complete original interface or game class layout.

All29 whole independent initializer/table-peer/resource/base/deleting/runtime
anchors total10,482 bytes, including all original switch records and authored
records. The previously ambiguous R1084251C0 /34 remains unknown. Complete
original handler/unwind carriers18 and unwind-map/FuncInfo carriers36 retain
all source fields, actual entry roots and external base/frame destinations.
Following next-owner unwind data stays outside each36-byte extent.

The natural complete fixture `tests/origin_probes/SceneResourceCleanup.cpp`
cold-builds with pinned3077 and `/Od /Ob0 /Gy /GR- /GX /Zi /GS /I src /showIncludes`.
It emits all24 code/data sections /809 bytes. Twenty-one complete unmasked
comparisons /1,169 bytes bind all five ordinary cleanup127, paired deleting44,
exception18 and data36 carriers, plus the shared resource deleting44 carrier.
Actual COFF/AUX, every relocation, four genuine weak deleting aliases/fallbacks,
normal instructions, linked flows and compact readonly `[1,8,12,12]` sizeof
observations are checked. A complete empty lifecycle member models the observed
base-relative lifetime role without adding a fabricated state word or padding.
Natural raw-pointer implicit cleanup19 and owning-member implicit75 differ from
the ordinary cleanup127; the owning member's own63-byte policy remains visible.
These are source alternatives, not a universal proof of original source spelling
or compiler flags. Authored source-family inference rests on independent actual
game asset/paired owner context. No original owner/layout/ABI/source or exact
credit is claimed, and no incomplete game class is instantiated.

An empty prior selected-snapshot audit,34 scoped canonical pairs, full original
unselected digests and bounded HEAD8cffcb1 readback permit exactly five rows in
each function/origin ledger to change. Each external INT3 byte remains outside
its127-byte function. Earlier evidence, lifetime/math/node uncertainties and all
60 exact inputs remain literal. Original and accepted cold proofs,3,295 local CI
tests including eight new guards, target/tracking, local Ghidra identity,
progress, fresh138-candidate triage and whitespace pass. Complete Web MCP
acceptance remains reserved until all origin review finishes.

Current4,213 resolved =987 authored+2,646 library+580 compiler;138 pending and
3,226 excluded. The original1,311 goal has1,173 classified /138 left and remains
active. Exact60 functions /9,883 bytes /60 units across eleven objects remain
unchanged; authored denominator1,972,227 and provisional0.50%.

## R233 complete shared scene-value setter

R233 accepts the whole21-byte authored setter at `0x004557E0`. It stores the
incoming DWORD at writable671628 and returns with RET4; its saved receiver is
unused. The original current name, extent, source/ABI, mappings and exact state
remain unchanged. Proposed scene-value naming is inference.

Replay `scripts/repo-python scripts/verify-scene-shared-value-origins.py` with
immutable `config/scene-shared-value-origin-evidence.json`, SHA-256
`d6d0f4579f374515459d797980f94ff2a8f3d5d868f7c36a396b769f1d5a23fe`.
Independent R044 BattleScene state policy43B610 /4,764 consumes and updates this
same global. Its full body, all158 branches, original authored record and entire
60-byte guarded state table remain pinned. It treats the value as float,
subtracts the original approximately0.01 float at658044 when ordered-positive,
and clamps a negative result to zero against65782C. Complete four-byte data
extents, permissions and float values are checked. The data binding comes from
the independent parent's actual FSTP writer, rather than the selected encoded
address. Local attested Ghidra queries confirm these references; no setter
incoming reference is found, which does not establish dead code.

The natural tracked fixture `tests/origin_probes/SceneSharedValue.cpp` cold-builds
with pinned3077 and `/Od /Ob0 /Gy /GR- /GX /Zi /GS /I src /showIncludes`.
Unsigned and float setter alternatives each emit21 bytes, and each reproduces
all native bytes after its sole actual DIR32 data field binds to the independent
owner. Full source COFF/AUX, normal instructions, linked flow and all four emitted
code/data sections /64 bytes are checked. The ordinary implicit-copy client10
has no shared-state write. The complete compact readonly sizeof observations
are `[1,4,4]`; no private game class is instantiated or padded. Byte-equal type
alternatives leave original type/name/private owner/layout/ABI/compiler profile
and source unrecovered. Authored source-family inference adds no exact credit.

The complete24/31-byte no-reference receiver policies454C00 and454F70 remain
unknown. Five scoped canonical pairs, full original-state unselected digests,
an empty prior selected-snapshot audit and bounded HEAD759d440 readback allow
exactly one origin/function row to change. Eleven external INT3 bytes at4557F5
stay outside the function. All previous evidence, explicit ambiguities and
60 exact source/header/build/match inputs remain literal. Original and accepted
cold proofs,3,287 CI tests including eight new guards, target/tracking, progress,
fresh143-candidate triage and whitespace pass. Full Web MCP acceptance is reserved
until all remaining origin review finishes.

Current4,208 resolved =982 authored+2,646 library+580 compiler;143 pending and
3,226 excluded. The original1,311 goal has1,168 classified /143 left and remains
active. Exact60 functions /9,883 bytes /60 units across eleven objects remain
unchanged; authored denominator1,971,592 and provisional0.50%.

## R232 complete BG05a reverse-cycle callback

R232 accepts the complete45-byte authored callback at `0x0044E3A0`. It decrements
the observed receiver+0x68 counter, resets a signed-negative result to3840 and
returns with RET0. The sole internal branch and full extent are preserved;
current name, source presence, ABI, mappings and exact state remain unchanged.

Replay `scripts/repo-python scripts/verify-background-reverse-cycle-origins.py`
with immutable `config/background-reverse-cycle-origin-evidence.json`, SHA-256
`b14741ea79891926aa530c1c731cab38766524086998fc778114907299f29b86`.
The actual readonly pointer at658AC8 is slot one of the six observed words at
658AC4. Complete independently accepted BG05a loader44E2F0 /161 installs that
table at instruction offset46, clears the same counter at130 and pushes the real
`data\background\BG05a.dat` asset path. Full renderer44E3D0 /872 reads that same
field at270,444 and656 through integer-to-floating conversion. All seven whole
constructor/callback/renderer/peer owners total1,235 bytes, including the selected
callback, with complete hashes, instructions, CFGs and prior authored records.
The six actual callback words and following eight bytes are checked separately;
no complete private table or class layout is inferred. Every other peer retains
its existing origin. Local Ghidra references independently confirm the selected
pointer and both real table-installation sites. The earlier R212 BG05b94-byte
multi-counter decision remains literal.

The natural fixture `tests/origin_probes/BackgroundReverseCycle.cpp` uses a
complete compact one-counter observation and an ordinary implicit-copy client.
Cold build3077 with `/Od /Ob0 /Gy /GR- /GX /Zi /GS /I src /showIncludes` emits all
three code/data sections /63 bytes, two whole41/10-byte functions, no relocation
field and the full12-byte readonly `[4,4,4]` observation. Every ordinary reverse
policy instruction agrees after interpreting the actual receiver-field role and
branch destination index. Native45 and source41 differ in field displacement
encodings; neither is cropped. The implicit-copy client lacks the decrement,
comparison and reset. No game owner is padded or instantiated, and no inert local,
fake return, original source text, private ABI or exact match is claimed.
Initial zero and this update keep the reachable counter in0..3840; a full
3,841-update cycle returns to zero. This describes the observed policy rather
than asserting arbitrary portable signed-overflow behavior.

The old snapshot audit finds no selected canonical pair. All earlier authored
CSVs, manifests, verifiers and explicit ambiguities remain literal. Seven scoped
canonical owners, full original-state unselected digests and bounded HEAD1357715
readback allow exactly one row in each origin/function ledger to change, retaining
the full45-byte extent and every unrelated row. Three external INT3 bytes at
44E3CD stay outside the function. Original and accepted cold replays,3,279 CI tests
including eight new guards, target/tracking, local Ghidra identity and query
completion, unchanged60 exact inputs, fresh144-candidate triage, progress and
whitespace pass.

Current4,207 resolved =981 authored+2,646 library+580 compiler;144 pending and
3,226 excluded. The original1,311 goal has1,167 classified /144 left and remains
active. Exact60 functions /9,883 bytes /60 units across eleven objects are
unchanged; authored denominator1,971,571 and provisional0.50%. Complete Web MCP
acceptance remains required after all remaining origin review finishes.

## R231 complete BG02 blend callbacks and bounded retained canonical view

R231 accepts three complete authored virtual callbacks /180 bytes at44B980,
44BEA0 and44C3C0, each60 bytes. They preserve current Ghidra names, whole extents,
RET0, original calculation/result stores and separate source/ABI/mapping/exact
state. Proposed BG02a/BG02b/BG02c blend roles remain inference.

Replay `scripts/repo-python scripts/verify-background-blend-origins.py` with
immutable `config/background-blend-origin-evidence.json`, SHA-256
`4d8e713940a8f69d4f10bc25a159ddf9e4c550094735cfbd59ffff74a3a82449`.
The actual readonly slot-two words in6586E8,65872C and658768 select the three
callbacks. Complete independently accepted BG02 asset constructors install those
same tables and load resources through observed receiver+0x18; their whole
renderers and other callback peers remain part of the retained R230 graph.
Every original native callback loads671404, adds the readonly160.0f at657834,
converts through6406AC, stores that integer locally, then similarly converts
6713C4 and stores the second integer. Neither result is passed to the final
zero-mode call. The whole final call uses receiver+0x18 and independently accepted
40C7F0 /65 SetBlendMode with its actual render-state calls and RET4. These observed
unused stores are retained as target facts; no inert source locals imitate them.

Complete accepted camera initializer412660 /96 and camera snap412CF0 /146
independently write both671404 and6713C4. Their full bodies/CFGs/old authored
records are reopened, including the actual `FSTP` Y stores. Decoder operand-access
annotations alone missed those x87 writes in preliminary triage; full instruction
semantics establish them. The two four-byte writable owners remain distinct from
the full readonly160 float. All three helper/camera owners total307 bytes. Global
addresses, receiver/resource use and callback installation are actual independent
observations; they do not recover original variable names or a complete class.

Fresh extraction of the pinned original `libcmt.lib` reopens complete `ftol2.obj`
and its `__ftol2` source definition. The whole117-byte, fieldless native/source
body is unmasked byte-equal, with all original COFF/AUX definitions, full CFG and
instructions retained. The function's own auxiliary extent is read again from a
fresh temporary object; no selected section prefix supplies a convenient size.
This remains the original R006 library owner, with no new runtime or exact credit.
Its source identity, camera writes and full game helper establish independent
routes rather than defining owners from selected encoded call fields.

Three literal old unknown function/origin pairs in R230 remain unchanged on disk.
The successor first verifies the full old manifest, source/script hashes, complete
plan and three actual slot-two contexts. Its isolated R230 module receives a
checked current canonical view projecting only the exact three approved original/
accepted pairs back to those literal unknown snapshots. Every other row, source,
field, native body, CFG, double, layout, compiler profile and ordinary control stays
literal. The entire R230 native proof and real cold compiler commands execute
normally; the module-local reader is restored afterwards. No stdlib monkeypatch,
source/hash relaxation, cached build fallback or old artifact write is used.
Standalone R230 canonical checks intentionally retain their historical unknowns;
use this R231 successor to replay that complete graph in the current state.

The natural tracked fixture `tests/origin_probes/BackgroundBlendPolicies.cpp`
returns meaningful coordinate conversions, forwards zero/one blend modes through
a complete compact observation owner and includes an implicit-copy alternative.
Cold build3077 with `/Od /Ob0 /Gy /GR- /GX /Zi /GS /I src /showIncludes` emits all
seven code/data sections /110 bytes /seven actual fields, five whole functions
22/16/21/21/10 and the complete16-byte readonly `[1,1,4,4]` observation. No SDK
header is needed. The real generated conversion fields name `__ftol2`; every call/
data field binds through independently verified owners and has a whole unmasked
source CFG. The whole21-byte zero/one controls differ at byte8, while the10-byte
implicit copy lacks floating/render calls. These are compatible source alternatives,
not original private prototypes or full native source matches. No arbitrary padding,
inert local, fake return or game-owner instantiation is introduced.

All48 scoped canonical pairs and four-byte external INT3 gaps are checked. Original
unselected digests and bounded HEAD f9948e5 before/after readback permit exactly
three rows in each canonical ledger to change, with every extent and unrelated row
preserved. Old authored CSVs/manifests/verifiers and protected ambiguities remain
literal. Original and accepted cold replays,3,271 CI tests including14 new guards,
target/tracking, local Ghidra identity/completion, unchanged60 exact inputs,
fresh145-candidate triage, progress and whitespace pass.

Current4,206 resolved =980 authored+2,646 library+580 compiler;145 pending and
3,226 excluded. The original1,311 goal has1,166 classified /145 left and remains
active. Exact60 functions /9,883 bytes /60 units across eleven objects remain
unchanged; authored denominator1,971,526 and provisional0.50%. Full Web MCP
acceptance is required after all remaining origin review finishes.

## R230 complete background cycle callbacks and independent asset context

R230 accepts six complete authored origins /314 bytes, preserving current names,
original extents and the separate60-function exact baseline:

| Address | Whole bytes | Observed runtime policy and independent asset |
| --- | ---: | --- |
| `0x0044B600` | 48 | BG02a: increment+0x68, signed >360 resets zero |
| `0x0044BB20` | 48 | BG02b: same complete policy with its own asset/table/renderer |
| `0x0044C040` | 48 | BG02c: same complete policy with its own asset/table/renderer |
| `0x0044D5E0` | 55 | BG04a: increment+0x68, ordered x87 >2500 resets zero |
| `0x004503E0` | 55 | BG07a: increment+0x68, ordered x87 >=15360 resets zero |
| `0x00450BD0` | 60 | BG08a: increment+0x68/+0x6C; signed second field >71 resets only that field |

Replay `scripts/repo-python scripts/verify-background-cycle-origins.py` with
immutable `config/background-cycle-origin-evidence.json`, SHA-256
`bc73e46ff1a7ebcb839b61caf3f51917d41b11d9a6d066285222ad06c885033a`.
Each whole callback ends in RET0 and has one internal conditional branch, with
no unresolved shared tail or switch. The three48-byte bodies are byte-equal;
independent game context, rather than that equality, supports their attribution.
The two full readonly double definitions at658960 and658CA8 are2500 and15360,
respectively. Native `TEST AH,0x41` and `TEST AH,1` preserve distinct ordered
strict-greater and greater/equal policies; unordered comparisons retain the
incremented value. Native32-bit ADD observations do not claim portable C++
signed-overflow behavior.

Forty-two whole callback/constructor/renderer/peer owners /7,683 bytes, including
the six selected callbacks, are reopened with complete hashes, instructions,
CFGs and existing switch records. Six independent accepted game asset loaders
/976 and six accepted renderers /4,910 are checked in full. The original loaders
push `data\background\BG02a.dat`, BG02b, BG02c, BG04a, BG07a and BG08a paths,
install their respective tables at instruction offset46 and clear+0x68 at130.
BG08a also clears+0x6C at140. Actual readonly slot-one references point to each
whole selected updater; slot four points to the independently accepted renderer
that consumes the same receiver field. Real receiver accesses exclude unrelated
EBP stack locals whose displacement happens to be0x68/0x6C. All six actual
callback words and the following eight bytes are checked independently; this is
a bounded table observation, not a recovered complete private interface. The
remaining peers retain their own accepted or unknown origin decisions.

The natural fixture `tests/origin_probes/BackgroundCyclePolicies.cpp` contains
four compact ordinary counter policies and two ordinary implicit-copy clients.
Cold build3077 with `/Od /Ob0 /Gy /GR- /GX /Zi /GS /I src /showIncludes` emits
all nine code/data sections /273 bytes /two real double fields, six complete
functions /241 and the whole16-byte readonly `[8,8,4,8]` observation. No SDK header
is needed. The four policy bodies are44/51/51/58; the implicit-copy clients are
24/13 and lack increment/compare/reset branches. Every ordinary policy instruction,
including branch destination indices, stack accesses, field roles, actual
source-defined double owners and RET, agrees with its corresponding complete
native policy after interpreting the two observed receiver fields. Raw bytes
and whole extents differ. No padded game owner, inert local, fabricated return,
private signature or exact comparison is introduced. These natural source
alternatives explain the explicit runtime policy; they do not identify original
type spelling, source text or executable-wide compiler settings.

The exhaustive old snapshot audit finds no selected canonical pair. All old
manifests, authored CSV rows, verifiers and protected ambiguities remain literal;
this new manifest holds the six complete origin-specific records. All42 scoped
canonical pairs are checked. Original-state unselected digests and strict bounded
HEAD ab3d829 readback permit exactly six origin/function-row changes, retaining
all extents and every unrelated row. External INT3 gaps0/0/0/9/9/4 remain outside
the full selected functions. Source presence, ABI, mappings and exact credit stay
unchanged.

Original and accepted cold replays and3,257 CI tests, including14 new guards,
pass. Target/tracking, local Ghidra target/mapping attestation and query completion,
full original body-address readback, unchanged60 exact inputs, fresh148-candidate
triage, progress and whitespace pass. Current4,203 resolved =977 authored+2,646
library+580 compiler;148 pending and3,226 excluded. The original1,311 goal has
1,163 classified /148 left and remains active. Exact60 /9,883 bytes /60 units
across eleven objects are unchanged; authored byte denominator1,971,346 and
provisional0.50%. Complete Web MCP acceptance remains required after all remaining
origin review finishes.

## R229 complete SDK public font and save wrappers

R229 accepts five complete library source-family origins /179 bytes. Current
Ghidra names and original extents are preserved, including the two erroneous
`RFX_Text_Bulk` names; the proposed names identify the independently recovered
SDK definitions without adding source, private ABI, mapping or exact credit.

| Address | Whole bytes | Original SDK definition and independent route |
| --- | ---: | --- |
| `0x00605185` | 51 | `_D3DXCreateFont@12`: named GDI32 `GetObjectA`, then604FB0 FontIndirect |
| `0x006055A2` | 32 | `_D3DXSaveSurfaceToFileA@20`: surface helper6054EF, flag0 |
| `0x006055C2` | 32 | `_D3DXSaveSurfaceToFileW@20`: surface helper6054EF, flag1 |
| `0x0060577E` | 32 | `_D3DXSaveVolumeToFileA@20`: volume helper6056CE, flag0 |
| `0x0060579E` | 32 | `_D3DXSaveVolumeToFileW@20`: volume helper6056CE, flag1 |

Replay `scripts/repo-python scripts/verify-sdk-public-wrapper-origins.py` with
immutable `config/sdk-public-wrapper-origin-evidence.json`, SHA-256
`7995f491ec17ac705a543d8cc32d3ede2e72bf429d47e103d3c4138d2553195c`.
All six genuine fields are bound through three independently retained whole
source owners /463 bytes and the unique named GDI import. Static surface/volume
helper identities use the actual archive member, section and symbol index,
including storage/type/offset metadata; encoded target call destinations do not
create owners. Fresh original archive extraction verifies every complete source
COFF/AUX record, permissions, full unmasked body and normal exit/CFG. The complete
R201 and R202 original source graphs and their public controls cold-replay.
Their lifetime/interior alternatives and all earlier uncertainty remain unchanged.

The natural tracked fixture `tests/origin_probes/SdkPublicWrappers.cpp` includes
original `d3dx8.h`, five real public clients and five compatible ordinary members.
Build3077 with `/O1 /Ob0 /Gy /Oy- /GR- /GX /I src /showIncludes` is a probe
reproducibility profile, not a universal target compiler assertion. Full cold
emission retains11 sections /330 bytes /all11 fields,88 original included headers
and the complete32-byte readonly layout `[60,16,24,4,4,28,4,4]`. All five ordinary
members reproduce whole native bodies, so historical replacement absence remains
unproved. Library attribution is a source-family inference from the independent
original SDK owners and distinct routes. Eight whole32-byte original peer controls
reject the wrong surface/volume helper and wrong A/W flag without masking fields.
The font body retains its real invalid-call error path and full RET12; all save
wrappers retain full RET20. No ignored compiler option, crop or artificial padding
is used for acceptance.

The gap6055E2–6055FA is25 bytes of complete noninventory code, not alignment.
The original same-member section38 defines the full fieldless three-float
`D3DXVECTOR3` constructor, whose whole native bytes and CFG are checked. This
adjacent observation adds no function, origin or reconstructed layout credit and
does not enlarge the32-byte wrapper extent. Other zero-length boundaries are
recorded literally. Eleven scoped canonical owners are checked. The old snapshot
audit finds no selected canonical pair; all older evidence remains literal.
Original-state full unselected digests and bounded before/after readback prove
that only these five rows in each canonical ledger change. Accepted-state replay
checks every owner in the complete scoped graph, permitting independent future
cohorts to progress.

Original and accepted cold replays,3,243 CI tests including14 new guards,
target/tracking, local Ghidra identity/completion markers, unchanged60 exact
inputs, fresh154-candidate triage, progress and whitespace pass. Current4,197
resolved =971 authored+2,646 library+580 compiler;154 pending and3,226 excluded.
The original1,311 goal has1,157 classified /154 left and remains active. Exact60
functions /9,883 bytes /60 units across eleven objects, authored denominator
1,971,032 and provisional0.50% remain unchanged. Complete Web MCP acceptance is
required after all remaining origin review finishes.

## R228 complete integral assignment dispatch and count-value receivers

R228 accepts five complete library source-family origins /185 bytes. Original
extents and current database names are preserved:

| Address | Whole bytes | Source-family role |
| --- | ---: | --- |
| `0x0040A6C0` | 50 | vector integral-template assign dispatch |
| `0x0040AA20` | 11 | xutility integer iterator category |
| `0x0040AA30` | 37 | vector count/value conversion to `_Assign_n` |
| `0x0045A620` | 50 | deque integral-template assign dispatch |
| `0x0045ADD0` | 37 | deque byte-value conversion to `_Assign_n` |

Replay `scripts/repo-python scripts/verify-integral-assignment-dispatch-origins.py`
with immutable `config/integral-assignment-dispatch-origin-evidence.json`, SHA-256
`f95e13955f5707d534f1125fc44d7c4217a1a08744a2a41274ac270b601c2cf7`.
The natural fixture `tests/origin_probes/IntegralAssignmentDispatch.cpp` uses
complete original SDK vector/deque owners and four compatible ordinary members.
Original vector/deque/xutility definitions and all28 included headers are pinned.
Build3077 and `/Od /Ob0 /Gy /GR- /GX /Zi /GS /I src /showIncludes` are explicit
per-probe reproducibility settings, not an executable-wide compiler assertion.

Two scoped graphs retain221 complete code/data sections /13,561 bytes /545 actual
fields and185 full normal/catch/unwind CFGs. Vector scope100 sections5363/236
fields and deque scope121 sections8198/309 fields include every actual defining
COFF/AUX/line/readonly owner. Actual cold-object definitions take precedence over
retained prototypes. Both actual weak references have their own AUX/search tags
and complete current fallback bodies. The initial diagnostic retained a logic_error
weak alias from R150; final acceptance instead includes this object's whole44-byte
fallback and its complete source-owned destructor, without field-derived aliases.
All13 remaining external symbols use independently defined R150 owners, whose
whole retained R149/R119 ancestry cold-replays. The absolute `__except_list` owner
is independently reopened from the pinned original CRT archive. No code/data field
is masked in the final complete source/native comparison.

Full ordinary emission retains204 sections /14,612 bytes /547 fields, all28
included headers and the entire28-byte readonly observation
`[4,4,1,16,20,1,1]`. All four ordinary dispatch/conversion members reproduce the
whole50/37-byte target bodies. Six complete pointer-range controls retain51-byte
assign dispatches,11-byte random-access category bodies and88/100-byte range
policies. All differ from the integral alternatives: the integer and pointer
category bodies have equal lengths but different instructions. Actual pointer
routes have their own defining category/policy symbols and are not resolved through
the integer owner catalog. The eleven-byte integer tag is a genuine SDK empty-class
return; no artificial uninitialized scalar return or ABI declaration is introduced.

Three complete independently accepted authored game callers /996 bytes are reopened
with full hashes, instructions, CFGs, exits, switch records and actual argument
windows. The341-byte407540 and310-byte4076A0 callers pass their read count and zero
value at4075AD/4076F8 into vector dispatch. The345-byte4567B0 caller passes count
0x5A and zero at456875 into its receiver+0x518 deque. Original37-byte adapters pass
whole four-byte or narrowed byte values by reference into the full accepted96-byte
409780 and108-byte455CA0 `_Assign_n` owners. These are included in the complete
source closures, rather than relying on their earlier labels alone.

Attribution is an explicit library-family inference from the original whole
source/category/conversion graph and independent game count/value context.
Compatible ordinary members are byte-equal; historical replacement absence is not
proved. Unsigned-long/unsigned-byte controls do not recover original type spelling,
signedness, private element declarations or complete game owner layouts. The initial
plain-char control's allocator placement conflict is diagnostic, not a reason to
invent an alias. None of the incomplete game owners is instantiated. The five
opaque R206 pointer/reference leaves and all prior lifetime/copy ambiguities remain
unknown. No reconstructed source, private ABI, mapping or exact credit is added.

The exhaustive old snapshot audit finds no selected canonical pair in prior JSON.
All earlier evidence/manifests/verifiers remain literal. All150 canonical owners
inside the complete source scopes and adjacent boundaries are checked; the frozen
unselected ledger digests check the original transition and bounded before/after
readback protects every unrelated row. Accepted-state cold replay checks every
owner in this complete source graph; later independently accepted cohorts outside
these scopes can progress without rewriting historical source evidence. Only the five approved rows in each origin/function ledger change. Observed
INT3 gaps remain outside the selected full extents. Original and accepted cold
replays,3,229 CI tests including14 new guards, target/tracking, local Ghidra identity
and query completion markers, fresh159-candidate triage, unchanged60 exact inputs,
progress and whitespace pass.

Current4,192 resolved =971 authored+2,641 library+580 compiler;159 pending and
3,221 excluded. The original1,311 review goal has1,152 classified /159 left and
remains active. Exact60 functions /9,883 bytes /60 units across eleven objects,
authored denominator1,971,032 and provisional0.50% remain unchanged. Final full
Web MCP acceptance remains required after all remaining origin review finishes.

## R227 complete vector endpoint routes and strict retained cold graphs

Four complete vector endpoints /124 bytes are accepted as library source-family
origins. All31-byte extents and current database names are unchanged:

| Address | Source-family role | Complete constructor closure |
| --- | --- | --- |
| `0x00459890` | mutable vector end | iterator442320 /28; const iterator4423C0 /24 |
| `0x00459A50` | mutable vector end | iterator442370 /28; const iterator4423E0 /24 |
| `0x00459C40` | const vector begin | const iterator4456D0 /24 |
| `0x00459C60` | const vector end | const iterator4456D0 /24 |

The immutable manifest is `config/vector-endpoint-route-origin-evidence.json`,
SHA-256 `f60a3fdfad9c7cf1ffddfe902114059102b9c26d06e4f5c63709a8346af313ec`.
Replay `scripts/repo-python scripts/verify-vector-endpoint-route-origins.py`.
The natural fixture `tests/origin_probes/VectorEndpointRoutes.cpp` uses complete
original SDK owners and ordinary compatible members. The explicit VC7.1 profile
`/Od /Ob0 /Gy /GR- /GX /Zi /GS /I src /showIncludes` is per-probe reproducibility
settings, not an executable-wide compiler assertion. Four original vector header
spans and all27 included headers are retained.

Four original and four compatible ordinary scopes retain20 whole defining
sections /552 bytes /12 actual fields and all20 CFGs. Every field binds through
its actual complete source owner and full COFF/AUX record before unmasked native
comparison. Full ordinary emission retains55 sections /1416 bytes /51 fields and
the whole36-byte readonly layout observation. Source widths4/116/16 are generic
controls, without recovery of original private element declarations or complete
game owner layouts. No incomplete game owner is instantiated.

Eight complete31-byte negative controls preserve distinct first/last fields and
mutable/const constructor routes. Known positive source owners resolve the
first/last and mutable-to-const alternatives before whole comparison; the const-
to-mutable controls retain different defining constructor symbols. All four
compatible ordinary endpoint members are byte-equal. Attribution is an explicit
library-family inference from the complete original source/constructor hierarchy
and coupled assignment/copy receivers, without proof of historical replacement
absence. This does not resolve the five opaque16-byte pointer/reference leaves
studied in R206; their public and ordinary alternatives remain byte-equal.

Three complete independently accepted library receivers /499 bytes and four
actual call windows are reopened. Both const endpoints occur in the full208-byte
459390 vector copy constructor, including its normal/catch/unwind extent; the
scanner omitted this parent. Preserve the reconciled208 extent, without returning
to the initial162. The195-byte458E70 assignment and208-byte459390 copy have full
retained cold source graphs. The96-byte459060 assignment keeps its independently
accepted R034 origin and complete native context; no new cold source comparison
of that parent is claimed. The joint first/last fields and returned iterator
construction remain distinct. All30 scoped canonical rows and15 protected
unknowns are checked; observed one-byte INT3 gaps stay outside the four extents.

Fifteen literal old unknown expectations in R209/R211 remain immutable. Three
later manifests pin the old R211 verifier script, so no old verifier or source
file is edited. The successor first validates each whole old plan and every old
source/script hash. It creates an in-memory current canonical view changing only
the exact four approved function/origin pairs at the exhaustively frozen trails.
Every old source, field, CFG, extent, compiler profile and ordinary-control record
stays literal. The isolated verifier modules route only the declared retained
R211 -> R210 -> R209 calls through the same checked view. Other dependency calls
and all compiler commands run normally; failed compilation has no cached fallback.
The entire mandatory R208/R150 ancestry and original CRT/typed owners still cold-
replay. Use the new successor verifier to reopen these historical source graphs
in the current state; their standalone old canonical checks intentionally expect
the historical unknowns. No old accepted source evidence is reclassified or weakened.

Original and accepted R227 cold replays pass, together with3,215 CI tests including
18 new guards. Target/tracking, local Ghidra identity/query markers, unchanged
60-unit exact inputs, exactly-four-row readback, fresh164-candidate triage,
progress and whitespace pass. Current4,187 resolved =971 authored+2,636 library
+580 compiler;164 pending and3,216 excluded. The original1,311 goal has1,147
classified /164 left and remains active. Exact60 functions /9,883 bytes /60 units
across eleven objects, authored denominator1,971,032 and provisional0.50% stay
unchanged. Final complete Web MCP acceptance remains required after all remaining
origin review finishes. No source/private ABI/mapping/exact or later-phase credit
is added.

## R226 complete deque front/back access and iterator dependencies

Nine complete origins / 365 bytes are accepted as library code. Six front/back
heads cover 257 bytes and their three necessary begin/end/explicit iterator
constructor dependencies cover 108 bytes. All canonical extents are preserved.

| Address | Whole bytes | Source-family role | Observed element width |
| --- | ---: | --- | ---: |
| `0x004094D0` | 32 | `std::deque::front` | 64 |
| `0x004094F0` | 45 | `std::deque::back` | 64 |
| `0x0041DB80` | 45 | `std::deque::back` | 4 |
| `0x0041DE00` | 45 | `std::deque::back` | 4 |
| `0x004213B0` | 45 | `std::deque::back` | 8 |
| `0x005F8180` | 45 | `std::deque::back` | 4 |
| `0x004099E0` | 35 | `std::deque::begin` | 64 |
| `0x00409A10` | 41 | `std::deque::end` | 64 |
| `0x0040A170` | 32 | explicit iterator constructor | 64 |

The immutable evidence is `config/deque-front-back-origin-evidence.json`, SHA-256
`1ac140821d2f2aec5d30ceab655de636f28eff6aa6215d1b8d49b6ffa0764e10`.
Replay with `scripts/repo-python scripts/verify-deque-front-back-origins.py`.
The verifier cold-builds the natural complete generic SDK fixture with the pinned
VC7.1 compiler and explicit `/Od /Ob0 /Gy /GR- /GX /Zi /GS /I src /showIncludes`
profile. These are per-probe reproducibility settings, not an executable-wide
compiler assertion. Five original header definition spans and all 27 included
headers are retained. No incomplete game owner is instantiated.

Six original SDK scopes retain 51 entire defining sections / 2,096 bytes / 45
actual fields. Six ordinary manual member alternatives reproduce the same complete
closures. Together all 12 scopes retain 102 entire sections / 4,192 bytes / 90
fields and all 102 control-flow graphs. Every relocation resolves through its
actual defining source owner and complete COFF/AUX record before unmasked target
comparison. Fresh ordinary emission retains all 88 sections / 2,873 bytes / 105
fields and the whole 40-byte readonly layout observation. No prefix, excluded
relocation field, cached object or fabricated source body earns acceptance.

The observed deque widths 64/4/8 have distinct block sizes 1/4/2 and full const
iterator dereference extents 83/89/87. The back heads pass immediate one through
iterator subtraction before mutable dereference; older plus-shaped mapped names
remain provisional. Six const-route controls preserve distinct defining callees.
Three compatible-member prefix-decrement controls emit whole 41-byte bodies,
different from the 45-byte SDK back route. Three wrong-width controls preserve
whole unequal dereference bodies without cropping. The ordinary first/last
members are byte-equal in all six scopes: library attribution remains an explicit
source-family inference, without claiming absence of historical replacements or
recovering the original game element declaration or complete private layout.

Fourteen independently accepted complete game parents / 6,811 bytes and all 90
actual call windows bind receiver and result use across audio queue/start/stop/
volume/fade/worker policies, archive registration, replay/card loading, fighter
script parsing and effect spawning. Their complete exits, switches and original
authored evidence are reopened. All 84 scoped canonical rows and 16 protected
unknowns are checked. The explicit iterator constructor ends immediately before
`0x0040A190`; its complete `RET 8` needs no added alignment. Other observed INT3
alignment remains outside the accepted extents.

Two selected addresses, `0x0041DB80` and `0x0041DE00`, occur as literal unknown
snapshots in the immutable R225 manifest. Those old records remain unchanged.
The R225 verifier now accepts only these two exact original-to-R226 transitions,
validated through the pinned complete successor plan; unrelated row, ABI, extent
and exact-credit changes remain rejected. The retained R225 cold replay passes.

Original and accepted R226 cold replays pass, as do 3,197 CI tests including 18
new guards. Target/tracking, attested local Ghidra check/query, all earlier 902
authored bodies, all 60 unchanged exact inputs, exactly-nine-row readback, fresh
168-candidate triage, progress and whitespace pass. Current 4,183 resolved = 971
authored + 2,632 library + 580 compiler; 168 pending and 3,212 excluded. The
original 1,311-origin goal has 1,143 classified / 168 remaining and is active.
Exact coverage stays 60 functions / 9,883 bytes / 60 units across eleven objects;
the authored denominator 1,971,032 and provisional 0.50% are unchanged. Final
complete Web MCP acceptance remains outstanding until all origin review finishes.
No source, private ABI, exact-reconstruction or later-phase credit is added.

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
98 bytes. The complete log10/ceil sections are 336/ 285 bytes, including every
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
the 37-/ 28-byte `std::out_of_range` message constructor/destructor are
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


## Archived README origin narrative (R129 checkpoint)

Historical R129 checkpoint: origin review had classified 919 authored,
1,774 library and 575 compiler-generated candidates; 1,083 remain pending.
The reviewed authored-byte slice is 9,883 / 1,965,299 exact (0.50%), with a
provisional denominator. R108 resolved one destructor and retained five
explicit/implicit lifetime ambiguities; R109 resolved thirteen game policies.
R110 resolves six deque dependencies and their complete range-erase callee
through independently reviewed game policies and a cold source-typed graph.
R111 resolves five range erases, four single-erase wrappers and three iterator
helpers through complete, closed source graphs with 337 cold source alternatives.
R112 resolves six postfix increments through their actual typed prefix callees
and two complete game callers. R113 resolves five queue helpers and the
unique enqueue/main-loop policies. R114 resolves four shared-lifetime/callback
policies and retains a complete ordinary/generated initializer ambiguity;
its CRT entry remained pending until the complete R126 graph closed. R115 resolves the
complete heap initialization graph and vendor SEH epilog, retaining unresolved
error, handler and multibyte chains. R116 resolves dynamic exit/message-box
dispatch and the complete shared-copy entry while preserving unresolved cookie
failure chains. R117 resolves the cookie initializer and complete SEH/NLG
dependencies, retaining unresolved user-handler and termination chains.
R118 resolves complete static locks, dynamic critical-section dispatch and
the callback loop, retaining allocator/TLS and shared-cleanup uncertainty.
R119 resolves six complete small-block/new-handler/TLS dependencies while
retaining the allocator/lock/error cycle. R120 closes the complete allocator/
lock/error/termination graph through eighteen whole source bodies and five
existing interior labels. R121 resolves the complete onexit/heap-growth/
teardown graph and retains two startup parents until locale and FP
dependencies close. R122 closes five complete locale/thread roots and the
whole fiber cleanup control, while multibyte initialization remains pending.
R123 closes the six multibyte/codepage roots and nine necessary NLS/locale
callees, including three full cleanup extents and three existing interior labels.
R124 closes 27 complete floating-point conversion/control bodies. R125 closes
all six initializer roots and the necessary exception/signal graph, including
cinit's actual callbacks and one existing raise cleanup label. R126 closes
eleven complete environment/argv/exception/exit bodies, including the full
PE entry and its independently authored game callee. R127 closes nineteen
complete x87 dispatch/IEEE exception primaries and four existing shared entries,
including the full atan2 table and natural vendor layout controls. R128 closes
three whole cos/sin/sqrt primaries and six existing C/shared entries, preserving
the complete 174-/174-/186-byte source extents. R129 closes rand/srand, fabs,
the full math exception/name graph and vector destruction/unwind, retaining an
abs ownership ambiguity against cold ordinary expression controls. The next
handoff targets six R130 vector-construction/two-argument math candidates while preserving
the 60-function exact baseline.
The current 95%-exact goal and separate origin review remain unfinished. See the
[current handoff](RE_HANDOFF.md) and
[origin review journal](ORIGIN_REVIEW.md).


## Archived dispatch handoff F023-F025 before F026 acceptance

These sections preserve the handoff at `4c90d5b` verbatim. Counts, next-step
notes and validation/resource samples describe their historical checkpoints;
use the current handoff and canonical ledgers for current state.

## Latest accepted cohort: F025

`CharacterAction551C00::DispatchActions` at `0x00551C00..0x00555526`
cold-replays exact across all **14,631 code bytes**. Nine following INT3 bytes
are alignment. R047 ownership and complete target body hash remain unchanged.
All 3,944 instructions, 772 internal branches, one return and 67 ordered
candidates are reconciled, with no switch tables or external branch exits.

Canonical source is `src/CharacterActionDispatch551C00.cpp` / `.hpp`. Its
separate pointer-only owner view reuses the unchanged slot-reference ABI in
`ReimuActionDispatch.hpp`. Original character identity and complete layout
remain unknown; no incomplete owner is instantiated or embedded. The mapped
name preserves the original R047 role through the explicit origin-name alias.

Unit `character-action-dispatch-00551c00` binds all **289 relocations**:
208 direct calls and 81 references to nine readonly constants. Actual fresh
COFF constant payloads and original target bytes were checked. Static calls
comprise 67 vector accesses, 44 input packs, 74 primary resets and 23
auxiliary-input clears. Callees receive no additional exact credit here.

```bash
scripts/repo-python scripts/replay-exact-units.py --unit character-action-dispatch-00551c00
```

Profile is pinned VC7.1 build 3077 with `/Od /Ob0 /Gy /GR- /GX- /Zi /I src`.
All 112 prior units and their source/header inputs remain unchanged and were
not rebuilt. Private observations and receipts remain below `.analysis/`:
`f025-551c00.asm`, `f025-native-audit.py` / `.json`, `f025-dispatch.c`,
`f025-decompile.log`, `f025-dispatch-diagnostic.py`, `f025-dispatch-audit.json`,
`f025-bind-relocations.py`, `f025-relocation-bindings.json`,
`f025-accepted-replay.json`, `f025-cold-replay.log` and `f025-progress.json`.

The next bounded R047 cohort is F026 at `0x00493470..0x00496C57` /14,312
bytes. Its completed native audit checks 3,841 instructions, 764 internal
branches, one return and 198 direct calls, without switch tables or external
branch exits. Eight following INT3 bytes are alignment. Retain private
`f026-native-audit.py` / `.json`, `f026-493470.asm`, `f026-dispatch.c`,
`f026-decompile.log` and `f026-progress.json` below `.analysis/`. The read-only
decompile is attested and complete. No source draft or exact credit is registered
for F026. Continue its natural C++ reconstruction, independently of F021.
The 95% objective remains active and incomplete; cleanup/handoff does not stop it.

## Previous accepted cohort: F024

`CharacterAction597660::DispatchActions` at `0x00597660..0x0059B48D`
cold-replays exact across all **15,918 code bytes**. Two following INT3 bytes
are alignment. The R047 origin and complete target hash remain unchanged.
All 4,294 instructions, 840 internal branches, one return and 74 ordered
candidates were reconciled; there are no switch tables or external branch exits.

Canonical source is `src/CharacterActionDispatch597660.cpp` / `.hpp`, with a
separate pointer-only owner view. Original character identity and full layout
remain unknown. The unchanged `ReimuActionDispatch.hpp` supplies the existing
slot-reference ABI view. No incomplete owner is instantiated or embedded.

Unit `character-action-dispatch-00597660` binds all **315 relocations**:
234 direct calls and 81 references to nine readonly constants. Actual fresh
COFF payloads and original target constants were checked. Calls comprise
70 vector accesses, 48 input packs, 81 primary resets, nine three-argument
transform calls, and 26 auxiliary-input clears. The original transform callee
at `0x0040FBB0` retains its R036 origin and earns no new exact credit here.

```bash
scripts/repo-python scripts/replay-exact-units.py --unit character-action-dispatch-00597660
```

Profile: pinned VC7.1 build 3077 with `/Od /Ob0 /Gy /GR- /GX- /Zi /I src`.
The 111 prior units and their inputs remain unchanged and were not rebuilt.
The renamed mapped role preserves the original R047 role through
`config/authored-origin-name-aliases.csv`.

Private evidence remains below `.analysis/`: `f024-597660.asm`,
`f024-native-audit.json`, `f024-dispatch.c`, `f024-decompile.log`,
`f024-dispatch-audit.json`, `f024-relocation-bindings.json`,
`f024-accepted-replay.json`, `f024-cold-replay.log` and `f024-progress.json`.
The native audit, complete diagnostic and binding scripts retain reproducible
checks. See the F024 knowledge-base entry for dispatch differences and limits.

The F025 native observations recorded at this checkpoint are retained in the
latest accepted cohort above and the knowledge base. Historical coverage and
compiler observations for F024 remain unchanged.

## Previous accepted cohort: F023

`CharacterAction::DispatchAt004C0AD0` compares exact across the complete
16,098-byte function at `0x004C0AD0..0x004C49B1`. Fourteen following INT3 bytes
are alignment. R047 ownership and full target body hash are preserved. The
extent contains 4,256 instructions, 830 internal branches, one return and no
switch tables or external branch exits. All 67 dispatch candidates are present.

Canonical source is `src/CharacterActionDispatch.cpp` / `.hpp`. Its pointer-only
interfaces reuse the unchanged slot-reference ABI view in
`src/ReimuActionDispatch.hpp`. Neither the original character identity nor a
complete owner layout is established; do not instantiate or embed these owners.
Names and field roles remain inferred.

Unit `character-action-dispatch-004c0ad0` cold-replays all 16,098 bytes with zero
differences, including all 322 relocations: 240 calls and 82 readonly-constant
references to nine constants. Fresh COFF payloads and original target constants
were checked. Compiler profile is pinned VC7.1 build 3077 with
`/Od /Ob0 /Gy /GR- /GX- /Zi /I src`; this does not establish an executable-wide
original profile. The 110 prior units and their inputs are unchanged and were
not rebuilt.

The already successful acceptance command is:

```bash
scripts/repo-python scripts/replay-exact-units.py --unit character-action-dispatch-004c0ad0
```

The previous F022 unit `reimu-fighter-dispatch-actions` remains accepted over
14,141 bytes /278 relocations. Its full evidence and observations are preserved
in [KNOWLEDGE_BASE.md](KNOWLEDGE_BASE.md).

Private F023 receipts, all below `.analysis/`:

| Artifact | Purpose |
| --- | --- |
| `f023-4c0ad0.asm`, `f023-dispatch.c`, `f023-decompile.log` | Native extent and attested read-only decompile |
| `f023-dispatch-audit.json`, `f023-complete-diagnostic.log` | Full instruction, branch and dispatch observations |
| `f023-relocation-bindings.json`, `f023-bind-relocations.py` | Every relocation and actual constant payload |
| `f023-accepted-replay.json`, `f023-cold-replay.log` | Successful canonical cold acceptance |
| `f023-progress.json` | Accepted source/header and object hashes |
| `f023-cleanup.json` | Earlier superseded preview cleanup: 82,944 file bytes |

## Verification and recovery

Run from the repository root, serially, using the private Python wrapper:

```bash
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/validate-tracking.py --require-target
scripts/repo-python scripts/report-reconstruction-status.py --summary
nice -n 10 scripts/repo-python scripts/ghidra.py check
nice -n 10 scripts/repo-python scripts/ci.py
git diff --check
```

At the preceding cleanup checkpoint, all 3,603 CI tests passed in 76.899 seconds. Target-required tracking, pinned
target identity, read-only Ghidra attestation and whitespace checks passed.
F023 source/header and final-object hashes still agree with its cold receipt;
all removed paired PDBs retain their unchanged COFF objects. The final sampled
available memory was 8.4 GiB and CPU was 76% idle, with 4 KiB/s swap-in and
no swap-out in that interval. CI and Ghidra checks ran at low priority; cleanup
started no compiler builds.

No accepted source/header, ABI, compiler flags or relocation was changed during
cleanup. Existing F023 cold evidence remains valid; no mass replay is needed.
Compiler jobs must remain serial and low priority, with CPU/memory monitoring.
`config/claims.csv` stays header-only. Read [RE_WORKFLOW.md](RE_WORKFLOW.md) and
[AGENTS.md](../AGENTS.md) when continuing reconstruction.

F024 final validation: all 3,603 CI tests passed in 98.647 seconds, including
historical-prefix, complete adoption, name-alias, origin, tracking and progress
freshness checks. The canonical source/header and final-object hashes still
match the successful cold receipt. No prior accepted unit required replay.
Four superseded preview files were removed after canonical-source equality
checks (116,911 bytes); `.analysis/f024-cleanup.json` records paths and hashes.
Original evidence, canonical inputs, final matching output and F021 remain.

Sampled available memory during this work was 6.6–8.8 GiB; the final sample was
6.9 GiB. The latest host CPU interval was 54% idle, with 8 KiB/s swap-in and
548 KiB/s swap-out. Compiler builds and validation ran at low priority, with no
parallel compiler jobs. The 95% goal remains active and incomplete.

F025 final validation: all 3,603 CI tests passed in 71.303 seconds, including
historical-prefix, complete adoption, name-alias, origin, tracking and progress
freshness checks. Canonical source/header and final-object hashes still match
the successful cold receipt. No prior accepted unit required replay.
Four superseded preview files were removed after canonical-source equality
checks (104,149 bytes); `.analysis/f025-cleanup.json` records their paths
and hashes. Original evidence, canonical inputs, final matching output and F021
remain preserved. The latest sampled available memory was 6.9 GiB, with CPU
85% idle and 32 KiB/s swap-in / no swap-out in that host interval. Compiler
builds and validation ran at low priority, without parallel compiler jobs.
Continue reconstruction toward 95%; the goal remains active and incomplete.


## Archived F026 handoff before F027 acceptance

These sections preserve the handoff at `e8081ae` verbatim. Counts, next-step
notes and validation/resource samples describe that historical checkpoint;
use the current handoff and canonical ledgers for current state.

## Latest accepted cohort: F026

`CharacterAction493470::DispatchActions` at `0x00493470..0x00496C57`
cold-replays exact across all **14,312 code bytes**. Eight following INT3 bytes
are alignment. R047 ownership and complete target body hash remain unchanged.
All 3,841 instructions, 764 internal branches, one return and 65 ordered
candidates are reconciled, with no switch tables or external branch exits.

Canonical source is `src/CharacterActionDispatch493470.cpp` / `.hpp`. The
separate pointer-only owner view reuses the unchanged slot-reference ABI in
`ReimuActionDispatch.hpp`. Original character identity and full layout remain
unknown; no incomplete owner is instantiated or embedded. An explicit alias
preserves the original R047 mapped role. All 113 prior units and their inputs
remain unchanged and were not rebuilt.

Unit `character-action-dispatch-00493470` binds all **269 relocations**:
198 calls, 70 references to nine readonly constants, and one writable global
byte reference. Actual fresh COFF constants were checked against target bytes.
The signed byte load at `0x00493A17` reads `0x006714D0` after reset 742 and
before the zero test controlling reset 743. Its target `.data` section is
readable/writable. The inferred name `g_StateRepeatLevelAt006714D0` and its
original declaration remain provisional; the storage earns no exact byte credit.

```bash
scripts/repo-python scripts/replay-exact-units.py --unit character-action-dispatch-00493470
```

Profile: pinned VC7.1 build 3077 with `/Od /Ob0 /Gy /GR- /GX- /Zi /I src`.
Private observations and receipts remain below `.analysis/`:
`f026-493470.asm`, `f026-native-audit.py` / `.json`, `f026-dispatch.c`,
`f026-decompile.log`, `f026-dispatch-diagnostic.py`, `f026-dispatch-audit.json`,
`f026-bind-relocations.py`, `f026-relocation-bindings.json`,
`f026-accepted-replay.json`, `f026-cold-replay.log` and `f026-progress.json`.
Detailed F022-F026 observations are in [KNOWLEDGE_BASE.md](KNOWLEDGE_BASE.md);
previous dispatch handoff sections are preserved in the history archive.

The next bounded R047 cohort is F027 at `0x00502450..0x00505A5E` /13,839 bytes.
The completed native audit checks 3,751 instructions, 734 internal branches,
one return and 200 direct calls, without switch tables or external branch exits.
One following INT3 byte is alignment. Retain private `f027-native-audit.py` /
`.json`, `f027-502450.asm`, `f027-dispatch.c`, `f027-decompile.log` and
`f027-progress.json` below `.analysis/`. The read-only decompile is attested
and complete. No source draft or exact credit is registered for F027. Continue
its full C++ reconstruction independently of F021 and F026 behavior assumptions.
The 95% objective remains active and incomplete; cleanup/handoff does not stop it.

## Verification and recovery

Run from the repository root, serially, using the private Python wrapper:

```bash
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/validate-tracking.py --require-target
scripts/repo-python scripts/report-reconstruction-status.py --summary
nice -n 10 scripts/repo-python scripts/ghidra.py check
nice -n 10 scripts/repo-python scripts/ci.py
git diff --check
```

F026 final validation: all 3,603 CI tests passed in 68.915 seconds, including
historical-prefix, complete adoption, name-alias, origin, tracking and progress
freshness checks. Cold source/header and final-object hashes remain intact.
Four superseded preview files were removed after canonical-source equality
checks (103,520 bytes); `.analysis/f026-cleanup.json` records paths and hashes.
Original evidence, canonical inputs, matching outputs and F021 remain preserved.
The latest sampled available memory was 8.8 GiB, with CPU 84% idle and no
swap-in/out in that host interval. Compiler builds and validation remained
low priority, with no parallel compiler jobs. The 95% goal remains active.

No prior accepted source/header, ABI, compiler flags or relocation changed in
F026; cold-replay only new or affected units. Keep compiler builds serial and
low priority, monitor CPU/memory, and preserve `config/claims.csv` header-only.
Read [RE_WORKFLOW.md](RE_WORKFLOW.md) and [AGENTS.md](../AGENTS.md) when continuing
reconstruction. The goal remains active until the full 95% objective is proved.

## F027 checkpoint before F028 acceptance (2026-10-23)

## Latest accepted cohort: F027

`CharacterAction502450::DispatchActions` at `0x00502450..0x00505A5E`
cold-replays exact across all **13,839 code bytes**. One following INT3 byte
is alignment. R047 ownership and the complete target body hash are unchanged.
All 3,751 instructions, 734 internal branches, one return and 66 ordered
candidates are reconciled, with no switch tables or external branch exits.

Canonical source is `src/CharacterActionDispatch502450.cpp` / `.hpp`. Its
separate pointer-only owner view reuses the unchanged slot-reference ABI in
`ReimuActionDispatch.hpp`. Original character identity and complete layout
remain unknown; no incomplete owner is instantiated or embedded. An explicit
alias preserves the original R047 mapped role. All 114 prior units and their
inputs remain unchanged and were not rebuilt.

Unit `character-action-dispatch-00502450` binds all **270 relocations**:
200 calls and 70 references to 15 readonly constants. Actual fresh COFF
constant payloads were checked against target bytes. No writable global is
referenced by this unit. The first six special policies omit the ordinary
cancellation gate; movement rank 39 is accepted only in five front policies,
not the four final airborne fallbacks. See the knowledge base for the complete
character-specific condition order, distance gates and reset IDs.

```bash
scripts/repo-python scripts/replay-exact-units.py --unit character-action-dispatch-00502450
```

Profile: pinned VC7.1 build 3077 with `/Od /Ob0 /Gy /GR- /GX- /Zi /I src`.
Private observations and receipts remain below `.analysis/`:
`f027-502450.asm`, `f027-native-audit.py` / `.json`, `f027-dispatch.c`,
`f027-decompile.log`, `f027-dispatch-diagnostic.py`, `f027-dispatch-audit.json`,
`f027-bind-relocations.py`, `f027-relocation-bindings.json`,
`f027-accepted-replay.json`, `f027-cold-replay.log` and `f027-progress.json`.
Detailed F022-F027 observations are in [KNOWLEDGE_BASE.md](KNOWLEDGE_BASE.md);
previous dispatch handoff sections are preserved in the history archive.

The next bounded R047 cohort is F028 at `0x00574370..0x0057774D` /13,278 bytes.
Its completed native audit checks 3,578 instructions, 705 internal branches,
one return and 187 direct calls, without switch tables or external branch exits.
Two following INT3 bytes are alignment. Retain private `f028-native-audit.py` /
`.json`, `f028-574370.asm`, `f028-dispatch.c`, `f028-decompile.log` and
`f028-progress.json` below `.analysis/`. The read-only decompile is attested
and complete. No source draft or exact credit is registered for F028. Continue
its full C++ reconstruction independently of F021 and F027 behavior assumptions.
The 95% objective remains active and incomplete; cleanup/handoff does not stop it.

## Verification and recovery

Run from the repository root, serially, using the private Python wrapper:

```bash
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/validate-tracking.py --require-target
scripts/repo-python scripts/report-reconstruction-status.py --summary
nice -n 10 scripts/repo-python scripts/ghidra.py check
nice -n 10 scripts/repo-python scripts/ci.py
git diff --check
```

F027 final validation: all 3,603 CI tests passed in 71.503 seconds, including
historical-prefix, complete adoption, name-alias, origin, tracking and progress
freshness checks. Cold source/header and final-object hashes remain intact.
Four superseded preview files were removed after canonical-source equality
checks (111,302 bytes); `.analysis/f027-cleanup.json` records paths and hashes.
Original evidence, canonical inputs, matching outputs and F021 remain preserved.
The latest sampled available memory was 8.8 GiB, with CPU 90% idle and no
swap-in/out in that host interval. Compiler builds and validation remained
low priority, without parallel compiler jobs. The 95% goal remains active.

No prior accepted source/header, ABI, compiler flags or relocation changed in
F027; cold-replay only new or affected units. Keep compiler builds serial and
low priority, monitor CPU/memory, and preserve `config/claims.csv` header-only.
Read [RE_WORKFLOW.md](RE_WORKFLOW.md) and [AGENTS.md](../AGENTS.md) when continuing
reconstruction. The goal remains active until the full 95% objective is proved.

## F028 checkpoint before F029 acceptance (2026-10-23)

## Latest accepted cohort: F028

`CharacterAction574370::DispatchActions` at `0x00574370..0x0057774D`
cold-replays exact across all **13,278 code bytes**. Two following INT3 bytes
are alignment. R047 ownership and the complete target body hash are unchanged.
All 3,578 instructions, 705 internal branches, one return and 61 ordered
candidates are reconciled, with no switch tables or external branch exits.

Canonical source is `src/CharacterActionDispatch574370.cpp` / `.hpp`. Its
separate pointer-only owner view reuses the unchanged slot-reference ABI in
`ReimuActionDispatch.hpp`. Original character identity and complete layout
remain unknown; no incomplete owner is instantiated or embedded. An explicit
alias preserves the original R047 mapped role. All 115 prior units and their
inputs remain unchanged and were not rebuilt.

Unit `character-action-dispatch-00574370` binds all **258 relocations**:
187 calls and 71 references to nine readonly constants. Actual fresh COFF
constant payloads were checked against target bytes. No writable global is
referenced by this unit. All five leading special policies retain cancellation;
input 200 looks up 730 but resets 731. The six advanced policies start with a
ground test; two retain fresh height reads after their primary reset, and three
repeat the ground test before lookup. Air C requires resource greater than 100.
See the knowledge base for exact condition order, distance gates and reset IDs.

```bash
scripts/repo-python scripts/replay-exact-units.py --unit character-action-dispatch-00574370
```

Profile: pinned VC7.1 build 3077 with `/Od /Ob0 /Gy /GR- /GX- /Zi /I src`.
Private observations and receipts remain below `.analysis/`:
`f028-574370.asm`, `f028-native-audit.py` / `.json`, `f028-dispatch.c`,
`f028-decompile.log`, `f028-dispatch-diagnostic.py`, `f028-dispatch-audit.json`,
`f028-bind-relocations.py`, `f028-relocation-bindings.json`,
`f028-accepted-replay.json`, `f028-cold-replay.log` and `f028-progress.json`.
Detailed F022-F028 observations are in [KNOWLEDGE_BASE.md](KNOWLEDGE_BASE.md);
previous dispatch handoff sections are preserved in the history archive.

The next bounded R047 cohort is F029 at `0x004E2F20..0x004E6291` /13,170 bytes.
Its complete native audit checks 3,565 instructions, 699 internal branches, one
return and 186 direct calls, without switch tables or external branch exits.
Fourteen following INT3 bytes are alignment. Retain private `f029-native-audit.py`
/ `.json`, `f029-4e2f20.asm`, `f029-dispatch.c`, `f029-decompile.log` and
`f029-progress.json` below `.analysis/`. The read-only decompile is attested
and complete. No source draft or exact credit is registered for F029. Continue
its independent C++ reconstruction; do not inherit F028 conditions without review.
The 95% objective remains active and incomplete; cleanup/handoff does not stop it.

## Verification and recovery

Run from the repository root, serially, using the private Python wrapper:

```bash
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/validate-tracking.py --require-target
scripts/repo-python scripts/report-reconstruction-status.py --summary
nice -n 10 scripts/repo-python scripts/ghidra.py check
nice -n 10 scripts/repo-python scripts/ci.py
git diff --check
```

F028 final validation: all 3,603 CI tests passed in 77.082 seconds, including
historical-prefix, complete adoption, name-alias, origin, tracking and progress
freshness checks. Cold source/header and final-object hashes remain intact.
Four superseded preview files were removed after canonical-source equality
checks (99,863 bytes); `.analysis/f028-cleanup.json` records paths and hashes.
Original evidence, canonical inputs, matching outputs and F021 remain preserved.
The latest sampled available memory was 8.9 GiB, with CPU 95% idle and no
swap-in/out in that host interval. Compiler builds and validation remained
low priority, without parallel compiler jobs. The 95% goal remains active.

No prior accepted source/header, ABI, compiler flags or relocation changed in
F028; cold-replay only new or affected units. Keep compiler builds serial and
low priority, monitor CPU/memory, and preserve `config/claims.csv` header-only.

## F029 checkpoint before F030 acceptance (2026-10-23)

## Latest accepted cohort: F029

`CharacterAction4E2F20::DispatchActions` at `0x004E2F20..0x004E6291`
cold-replays exact across all **13,170 code bytes**. Fourteen following INT3
bytes are alignment. R047 ownership and the complete target body hash are
unchanged. All 3,565 instructions, 699 internal branches, one return and 62
ordered candidates are reconciled, without switch tables or external exits.

Canonical source is `src/CharacterActionDispatch4E2F20.cpp` / `.hpp`. Its
separate pointer-only owner view reuses the unchanged slot-reference ABI in
`ReimuActionDispatch.hpp`. Original character identity and complete layout
remain unknown; no incomplete owner is instantiated or embedded. An explicit
alias preserves the original R047 mapped role. All 116 prior units and their
inputs remain unchanged and were not rebuilt.

Unit `character-action-dispatch-004e2f20` binds all **255 relocations**:
186 calls and 69 references to 13 readonly constants. Actual fresh COFF
constant payloads were checked against target bytes. No writable global is
referenced by this unit. Six leading special policies omit cancellation;
choice 1 in both advanced modes checks +F12, and ordinary inputs 22/21/20
repeat resource after flag. Five front movement policies allow rank 39 in
addition to 99/49; the four final air fallbacks retain 99/49 only. See the
knowledge base for condition order, distance gates and reset IDs.

```bash
scripts/repo-python scripts/replay-exact-units.py --unit character-action-dispatch-004e2f20
```

Profile: pinned VC7.1 build 3077 with `/Od /Ob0 /Gy /GR- /GX- /Zi /I src`.
Private observations and receipts remain below `.analysis/`:
`f029-4e2f20.asm`, `f029-native-audit.py` / `.json`, `f029-dispatch.c`,
`f029-decompile.log`, `f029-dispatch-diagnostic.py`, `f029-dispatch-audit.json`,
`f029-bind-relocations.py`, `f029-relocation-bindings.json`,
`f029-accepted-replay.json`, `f029-cold-replay.log` and `f029-progress.json`.
Detailed F022-F029 observations are in [KNOWLEDGE_BASE.md](KNOWLEDGE_BASE.md);
previous dispatch handoff sections are preserved in the history archive.

The next bounded R047 cohort is F030 at `0x005C0D70..0x005C3FA8` /12,857 bytes.
Its completed native audit checks 3,474 instructions, 680 internal branches,
one return and 186 direct calls, without switch tables or external branch exits.
Seven following INT3 bytes are alignment. Retain private `f030-native-audit.py`
/ `.json`, `f030-5c0d70.asm`, `f030-dispatch.c`, `f030-decompile.log` and
`f030-progress.json` below `.analysis/`. The read-only decompile is attested
and complete. No source draft or exact credit is registered for F030. Continue
its independent C++ reconstruction; do not assume F029 conditions apply.
The 95% objective remains active and incomplete; cleanup/handoff does not stop it.

## Verification and recovery

Run from the repository root, serially, using the private Python wrapper:

```bash
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/validate-tracking.py --require-target
scripts/repo-python scripts/report-reconstruction-status.py --summary
nice -n 10 scripts/repo-python scripts/ghidra.py check
nice -n 10 scripts/repo-python scripts/ci.py
git diff --check
```

F029 final validation: all 3,603 CI tests passed in 76.972 seconds, including
historical-prefix, complete adoption, name-alias, origin, tracking and progress
freshness checks. Cold source/header and final-object hashes remain intact.
Four superseded preview files were removed after canonical-source equality
checks (108,812 bytes); `.analysis/f029-cleanup.json` records paths and hashes.
Original evidence, canonical inputs, matching outputs and F021 remain preserved.
The latest sampled available memory was 8.8 GiB, with CPU 90% idle and no
swap-in/out in that host interval. Compiler builds and validation remained
low priority, without parallel compiler jobs. The 95% goal remains active.

No prior accepted source/header, ABI, compiler flags or relocation changed in
F029; cold-replay only new or affected units. Keep compiler builds serial and
low priority, monitor CPU/memory, and preserve `config/claims.csv` header-only.

## F030 checkpoint before F031 acceptance (2026-10-23)

## Latest accepted cohort: F030

`CharacterAction5C0D70::DispatchActions` at `0x005C0D70..0x005C3FA8`
cold-replays exact across all **12,857 code bytes**. Seven following INT3
bytes are alignment. R047 ownership and the complete target body hash are
unchanged. All 3,474 instructions, 680 internal branches, one return and 61
ordered candidates are reconciled, without switch tables or external exits.

Canonical source is `src/CharacterActionDispatch5C0D70.cpp` / `.hpp`. Its
separate pointer-only owner view reuses the unchanged slot-reference ABI in
`ReimuActionDispatch.hpp`. Original character identity and complete layout
remain unknown; no incomplete owner is instantiated or embedded. An explicit
alias preserves the original R047 mapped role. All 117 prior units and their
inputs remain unchanged and were not rebuilt.

Unit `character-action-dispatch-005c0d70` binds all **252 relocations**:
186 calls and 66 references to nine readonly constants. Actual fresh COFF
constant payloads were checked against target bytes. No writable global is
referenced by this unit. Six leading special policies omit cancellation;
input 210 reads height after the priority callback, while 220 omits ground.
Input 103 requires +3A0 ==0; two ordinary 102 policies retain fresh height
reads. All movement rank exceptions remain 99/49. Air A has two separate
input groups, and neutral C omits the repeated vertical-zero read. See the
knowledge base for exact ordering, distance gates and reset IDs.

```bash
scripts/repo-python scripts/replay-exact-units.py --unit character-action-dispatch-005c0d70
```

Profile: pinned VC7.1 build 3077 with `/Od /Ob0 /Gy /GR- /GX- /Zi /I src`.
Private observations and receipts remain below `.analysis/`:
`f030-5c0d70.asm`, `f030-native-audit.py` / `.json`, `f030-dispatch.c`,
`f030-decompile.log`, `f030-dispatch-diagnostic.py`, `f030-dispatch-audit.json`,
`f030-bind-relocations.py`, `f030-relocation-bindings.json`,
`f030-accepted-replay.json`, `f030-cold-replay.log` and `f030-progress.json`.
Detailed F022-F030 observations are in [KNOWLEDGE_BASE.md](KNOWLEDGE_BASE.md);
previous dispatch handoff sections are preserved in the history archive.

The next bounded R047 cohort is F031 at `0x005E2310..0x005E54F8` /12,777 bytes.
Its completed native audit checks 3,428 instructions, 686 internal branches,
one return and 173 direct calls, without switch tables or external branch exits.
Seven following INT3 bytes are alignment. Retain private `f031-native-audit.py`
/ `.json`, `f031-5e2310.asm`, `f031-dispatch.c`, `f031-decompile.log` and
`f031-progress.json` below `.analysis/`. The read-only decompile is attested
and complete. No source draft or exact credit is registered for F031. Continue
its independent C++ reconstruction; do not assume F030 conditions apply.
The 95% objective remains active and incomplete; cleanup/handoff does not stop it.

## Verification and recovery

Run from the repository root, serially, using the private Python wrapper:

```bash
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/validate-tracking.py --require-target
scripts/repo-python scripts/report-reconstruction-status.py --summary
nice -n 10 scripts/repo-python scripts/ghidra.py check
nice -n 10 scripts/repo-python scripts/ci.py
git diff --check
```

F030 final validation: all 3,603 CI tests passed in 73.158 seconds, including
historical-prefix, complete adoption, name-alias, origin, tracking and progress
freshness checks. Cold source/header and final-object hashes remain intact.
Four superseded preview files were removed after canonical-source equality
checks (107,418 bytes); `.analysis/f030-cleanup.json` records paths and hashes.
Original evidence, canonical inputs, matching outputs and F021 remain preserved.
The latest sampled available memory was 8.9 GiB, with CPU 89% idle and no
swap-in/out in that host interval. Compiler builds and validation remained
low priority, without parallel compiler jobs. The 95% goal remains active.

No prior accepted source/header, ABI, compiler flags or relocation changed in
F030; cold-replay only new or affected units. Keep compiler builds serial and
low priority, monitor CPU/memory, and preserve `config/claims.csv` header-only.

## F031 checkpoint before F032 acceptance (2026-10-23)

## Latest accepted cohort: F031

`CharacterAction5E2310::DispatchActions` at `0x005E2310..0x005E54F8`
cold-replays exact across all **12,777 code bytes**. Seven following INT3
bytes are alignment. R047 ownership and the complete target body hash are
unchanged. All 3,428 instructions, 686 internal branches, one return and 55
ordered candidates are reconciled, without switch tables or external exits.

Canonical source is `src/CharacterActionDispatch5E2310.cpp` / `.hpp`. Its
separate pointer-only owner view reuses the unchanged slot-reference ABI in
`ReimuActionDispatch.hpp`. Original character identity and complete layout
remain unknown; no incomplete owner is instantiated or embedded. An explicit
alias preserves the original R047 mapped role. All 118 prior units and their
inputs remain unchanged and were not rebuilt.

Unit `character-action-dispatch-005e2310` binds all **239 relocations**:
173 calls and 66 references to nine readonly constants. Actual fresh COFF
constant payloads were checked against target bytes. No writable global is
referenced by this unit. Input 103 comes first, then six advanced policies,
then the two ordinary input-102 policies. Several attacks clear input before
rereading state: preserve their 300..326 transition branches, immediate returns
and fallthrough into subsequent candidates. Do not cache state across callbacks.
See the knowledge base for exact condition order, distance gates and reset IDs.

```bash
scripts/repo-python scripts/replay-exact-units.py --unit character-action-dispatch-005e2310
```

Profile: pinned VC7.1 build 3077 with `/Od /Ob0 /Gy /GR- /GX- /Zi /I src`.
Private observations and receipts remain below `.analysis/`:
`f031-5e2310.asm`, `f031-native-audit.py` / `.json`, `f031-dispatch.c`,
`f031-decompile.log`, `f031-dispatch-diagnostic.py`, `f031-dispatch-audit.json`,
`f031-bind-relocations.py`, `f031-relocation-bindings.json`,
`f031-accepted-replay.json`, `f031-cold-replay.log` and `f031-progress.json`.
Detailed F022-F031 observations are in [KNOWLEDGE_BASE.md](KNOWLEDGE_BASE.md);
previous dispatch handoff sections are preserved in the history archive.

The next bounded R047 cohort is F032 at `0x0052D230..0x005301A1` /12,146 bytes.
Its completed native audit checks 3,267 instructions, 646 internal branches,
one return and 171 direct calls, without switch tables or external branch exits.
Fourteen following INT3 bytes are alignment. Retain private `f032-native-audit.py`
/ `.json`, `f032-52d230.asm`, `f032-dispatch.c`, `f032-decompile.log` and
`f032-progress.json` below `.analysis/`. The read-only decompile is attested
and complete. No source draft or exact credit is registered for F032. Continue
its independent C++ reconstruction; do not assume F031 conditions apply.
Native F032 has four separate MOVSX byte reads at 0x006714D0, comparing 0/1/2/3
after packing and between possible resets. Reuse the already registered
`g_StateRepeatLevelAt006714D0` signed-byte view, bind writable storage by address,
and preserve fresh reads rather than treating the initial byte as a constant.
Do not duplicate its existing global ledger row. Private
`f032-absolute-memory.json` records the original load instructions.
The 95% objective remains active and incomplete; cleanup/handoff does not stop it.

## Verification and recovery

Run from the repository root, serially, using the private Python wrapper:

```bash
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/validate-tracking.py --require-target
scripts/repo-python scripts/report-reconstruction-status.py --summary
nice -n 10 scripts/repo-python scripts/ghidra.py check
nice -n 10 scripts/repo-python scripts/ci.py
git diff --check
```

F031 final validation: all 3,603 CI tests passed in 76.890 seconds, including
historical-prefix, complete adoption, name-alias, origin, tracking and progress
freshness checks. Cold source/header and final-object hashes remain intact.
Four superseded preview files were removed after canonical-source equality
checks (107,173 bytes); `.analysis/f031-cleanup.json` records paths and hashes.
Private `f030-compiler-control.json` and `f031-compiler-control.json` preserve
hash-verified recipes for the initial rejected comparison/branch variants.
Original evidence, canonical inputs, matching outputs and F021 remain preserved.
The latest sampled available memory was 8.8 GiB, with CPU 94% idle and no
swap-in/out in that host interval. Compiler builds and validation remained
low priority, without parallel compiler jobs. The 95% goal remains active.

No prior accepted source/header, ABI, compiler flags or relocation changed in
F031; cold-replay only new or affected units. Keep compiler builds serial and
low priority, monitor CPU/memory, and preserve `config/claims.csv` header-only.

## F032 checkpoint before F033 acceptance (2026-10-23)

## Latest accepted cohort: F032

`CharacterAction52D230::DispatchActions` at `0x0052D230..0x005301A1`
cold-replays exact across all **12,146 code bytes**. Fourteen following INT3
bytes are alignment. R047 ownership and the complete target body hash are
unchanged. All 3,267 instructions, 646 internal branches, one return and 56
ordered candidates are reconciled, without switch tables or external exits.

Canonical source is `src/CharacterActionDispatch52D230.cpp` / `.hpp`. Its
separate pointer-only owner view reuses the unchanged slot-reference ABI in
`ReimuActionDispatch.hpp` and the existing signed-byte global symbol. Original
character identity, full owner layout and original global declaration remain
unknown; no incomplete owner is instantiated or embedded. An explicit alias
preserves the R047 mapped role. All 119 prior units and their inputs remain
unchanged and were not rebuilt. No duplicate global ledger row was added.

Unit `character-action-dispatch-0052d230` binds all **237 relocations**:
171 calls, 62 references to five readonly constants and four writable-global
loads. Actual fresh COFF constant payloads match their target bytes. The four
MOVSX byte reads at 0x006714D0 compare 0/1/2/3 separately after packing and
between possible resets 746/745/744/743. They remain fresh reads bound to the
writable address, not its initial value. Advanced choice 2 in both modes uses
resource >250 with +F12/+F10 guards. Air A retains its outer flag check and
its distinct inner reads. See the knowledge base for exact policy order.

```bash
scripts/repo-python scripts/replay-exact-units.py --unit character-action-dispatch-0052d230
```

Profile: pinned VC7.1 build 3077 with `/Od /Ob0 /Gy /GR- /GX- /Zi /I src`.
Private observations and receipts remain below `.analysis/`:
`f032-52d230.asm`, `f032-native-audit.py` / `.json`, `f032-dispatch.c`,
`f032-decompile.log`, `f032-absolute-memory.json`, `f032-dispatch-diagnostic.py`,
`f032-dispatch-audit.json`, `f032-bind-relocations.py`,
`f032-relocation-bindings.json`, `f032-accepted-replay.json`,
`f032-cold-replay.log` and `f032-progress.json`. Detailed F022-F032 observations
are in [KNOWLEDGE_BASE.md](KNOWLEDGE_BASE.md); earlier handoffs are archived.

The next bounded R047 cohort is F033 at `0x00472890..0x00474B36` /8,871 bytes,
provisionally mapped as `CharacterAI::ChooseAt00472890`. Its complete native
audit checks 2,274 instructions, 496 internal branches, one return and 109
direct calls, with no switch tables or external exits. Nine following INT3
bytes are alignment. The read-only Ghidra decompile is attested and complete.
Retain private `f033-native-audit.py` / `.json`, `f033-472890.asm`, `f033-ai.c`,
`f033-decompile.log`, `f033-ai-family-survey.json`,
`f033-ai-family-differences.json` and `f033-progress.json` below `.analysis/`.
No source draft or exact credit is registered for F033. Independently inspect
callee ABI and full policy before authoring natural C++.

Five other R047 bodies of the same length at 0x004E7DE0, 0x00579650,
0x0059D240, 0x005C5D10 and 0x005E7370 have individually checked body hashes
and full CFGs. The complete instruction comparison exposes selector offsets,
mode constants and writable-counter addresses that differ. Preserve every
reported difference; do not treat equal length or normalized calls as exact
credit. A shared source body would require explicit, behavior-bearing profiles
and a complete canonical cold replay for each function.
The 95% objective remains active and incomplete; cleanup/handoff does not stop it.

## Verification and recovery

Run from the repository root, serially, using the private Python wrapper:

```bash
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/validate-tracking.py --require-target
scripts/repo-python scripts/report-reconstruction-status.py --summary
nice -n 10 scripts/repo-python scripts/ghidra.py check
nice -n 10 scripts/repo-python scripts/ci.py
git diff --check
```

F032 final validation: all 3,603 CI tests passed in 77.264 seconds, including
historical-prefix, complete adoption, name-alias, origin, tracking and progress
freshness checks. Cold source/header and final-object hashes remain intact.
Four superseded preview files were removed after canonical-source equality
checks (96,373 bytes); `.analysis/f032-cleanup.json` records paths and hashes.
Original evidence, canonical inputs, matching outputs and F021 remain preserved.
The final host sample had 8.7 GiB available memory and CPU 91% idle, with
4 KiB/s swap-in and no swap-out during that interval. Compiler builds and
validation remained low priority without parallel compiler jobs. The 95% goal
remains active. The reproducible private `f033-ai-family-audit.py` retains every
reported difference between the six unaccepted R047 AI bodies.

No prior accepted source/header, ABI, compiler flags or relocation changed in
F032; cold-replay only new or affected units. Keep compiler builds serial and
low priority, monitor CPU/memory, and preserve `config/claims.csv` header-only.

## F033 checkpoint before F034 acceptance (2026-10-23)

## Latest accepted cohort: F033

Six independently reviewed R047 AI policies cold-replay exact from one natural
C++ template body in `src/CharacterAIPolicy.cpp` / `.hpp`. Each complete body
has **8,871 code bytes**, 2,274 instructions, 496 internal branches, one return
and nine following alignment INT3 bytes. There are no switch tables or external
branch exits. Original R047 body hashes and ownership evidence are unchanged.

| Receiver alias | Target address | Writable counter |
| --- | --- | --- |
| `CharacterAI472890` | `0x00472890` | `0x0068D61C` |
| `CharacterAI4E7DE0` | `0x004E7DE0` | `0x0068D634` |
| `CharacterAI579650` | `0x00579650` | `0x0068D654` |
| `CharacterAI59D240` | `0x0059D240` | `0x0068D65C` |
| `CharacterAI5C5D10` | `0x005C5D10` | `0x0068D664` |
| `CharacterAI5E7370` | `0x005E7370` | `0x0068D66C` |

All six `ChooseAction` methods use explicit profiles for the observed selector
offsets, mode value and counter symbol. This source reuse does not establish
original templates, identities, declarations or complete owner layouts. Only
methods are emitted; no incomplete owner object is constructed or embedded.
The two-component local separation value is source-defined. Three observed
command read/store repetitions remain explicit assignment chains. No assembly,
byte arrays, inert locals, padding or alternate conditional bodies are used.

Each unit binds all 225 relocations: 109 calls, 109 readonly references to 22
constants, and seven counter accesses (four reads, three writes). All fresh
COFF payloads and target section permissions were checked; full relocated code
matches every original byte. Counter storage is bound by address, not initial
contents. Calls comprise two float-wrapper calls, 99 CRT rand calls, two exact
state-predicate calls on the opponent, and six thiscall integer-range calls on
the current receiver. Wrapper ownership and original declarations remain
unknown; declaration-only callees earn no new origin or exact credit.

```bash
scripts/repo-python scripts/replay-exact-units.py --unit character-ai-00472890 --unit character-ai-004e7de0 --unit character-ai-00579650 --unit character-ai-0059d240 --unit character-ai-005c5d10 --unit character-ai-005e7370
```

The canonical replay cold-builds one object and checks all **53,226 bytes /
1,350 relocations**. Profile: pinned VC7.1 build 3077 with
`/Od /Ob0 /Gy /GR- /GX- /Zi /I src`. All 120 prior units and inputs remain
unchanged and were not rebuilt. The existing `GameLeafHelpers.hpp` ABI is reused
without modification. Changing the shared AI source/header requires replay of
all six dependent units; avoid rebuilding unrelated accepted units.

Private receipts below `.analysis/`: `f033-native-audit.py` / `.json`,
`f033-472890.asm`, `f033-ai.c`, `f033-decompile.log`,
`f033-ai-family-audit.py`, `f033-ai-family-survey.json`,
`f033-ai-family-differences.json`, `f033-bind-family.py`,
`f033-family-bindings-preview.json`, `f033-family-bindings.json`,
`f033-accepted-replay.json`, `f033-cold-replay.log`, `f033-progress.json` and
retained rejected `f033-probe-*` sources/diagnostics. The family comparison
exposed real per-profile differences; instruction/frame normalization never
earned credit. See [KNOWLEDGE_BASE.md](KNOWLEDGE_BASE.md) for behavior and profiles.

The next bounded R047 AI candidate is F034 at `0x004C6B50..0x004C8CCB`
/8,572 bytes. Its completed native audit checks 2,180 instructions, 480 internal
branches, one return and 116 direct calls, with no switch tables or external
exits. Four following INT3 bytes are alignment. The attested read-only Ghidra
decompile is complete. Retain private `f034-native-audit.py` / `.json`,
`f034-4c6b50.asm`, `f034-ai.c`, `f034-decompile.log` and `f034-progress.json`.
Its 111 CRT rand calls and one range-helper call differ from F033. No source
draft or exact credit is registered. Independently review its full behavior
before extending the shared implementation or authoring another source body. The 95% objective remains active and incomplete;
cleanup/handoff does not stop it. All 97 unknown origins remain unknown.

## Verification and recovery

Run from the repository root, serially, using the private Python wrapper:

```bash
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/validate-tracking.py --require-target
scripts/repo-python scripts/report-reconstruction-status.py --summary
nice -n 10 scripts/repo-python scripts/ghidra.py check
nice -n 10 scripts/repo-python scripts/ci.py
git diff --check
```

F033 final validation: all 3,603 CI tests passed in 95.813 seconds, including
historical-prefix, complete adoption, name-alias, origin, tracking and progress
freshness checks. All six canonical cold reports and source/header/object pins
remain intact. Four superseded previews were removed after canonical-source
equality checks (176,917 bytes); `.analysis/f033-cleanup.json` records paths and
hashes. Seven private control sources and diagnostics remain, with source hashes
and compiler profiles in `f033-control-manifest.json`. The private compose script
regenerates the canonical source byte-for-byte. Original evidence, canonical
inputs, matching outputs and F021 remain preserved. The final host sample had
8.9 GiB available memory and CPU 95% idle, with 4 KiB/s swap-in and no swap-out
in that interval. Builds and validation remained serial and low priority.
The 95% goal remains active.

Keep compiler builds serial and low priority, monitor CPU/memory, and preserve
`config/claims.csv` header-only. Replay the six AI units after a relevant shared
source, ABI, profile or relocation change; preserve every unrelated accepted unit.

## F034 checkpoint before F035 acceptance (2026-10-23)

## Latest accepted cohort: F034

`CharacterAI4C6B50::ChooseAction` at `0x004C6B50..0x004C8CCB` cold-replays
exact from `src/CharacterAI4C6B50.cpp` / `.hpp`: **8,572 code bytes**, 2,180
instructions, 480 internal branches and one return. There are no switch tables
or external branch exits. Four following INT3 bytes are alignment. The original
R047 body hash and ownership evidence remain unchanged.

This is a separate natural source body because its decisions differ from F033.
The receiver interface remains pointer-only; do not construct or embed it.
The two-float local separation record is source-defined, with both components
used. Three command assignment chains preserve observed read/store repetitions.
No assembly, byte arrays, inert locals, padding or alternate bodies are used.

All 218 relocations are bound: 116 direct calls, 95 readonly references to 23
float constants and seven accesses to the signed dword counter at `0x0068D62C`
(four reads, three writes). Fresh COFF payloads and target section permissions
were checked. Calls comprise two float-wrapper calls, 111 CRT rand calls, two
state-predicate calls on the opponent, and one thiscall range-helper call on
the current receiver. Callee declarations do not add origin or exact credit;
the original wrapper declaration and ownership remain unknown. The counter is
bound by address, without claiming data contents or a complete owner layout.

```bash
scripts/repo-python scripts/replay-exact-units.py --unit character-ai-004c6b50
```

The canonical replay cold-builds the object with pinned VC7.1 build 3077,
`/Od /Ob0 /Gy /GR- /GX- /Zi /I src`, then compares all bytes and relocations.
All 126 earlier units and their inputs remain unchanged and were not rebuilt.
The new header includes the unchanged `CharacterAIPolicy.hpp` for observed
callee declarations. Changing that shared header affects F034 and all six F033
units; changing only `CharacterAIPolicy.cpp` affects its six F033 units. Replay
affected units only. Preserve the unchanged `GameLeafHelpers.hpp` ABI.

Private receipts below `.analysis/`: `f034-native-audit.py` / `.json`,
`f034-4c6b50.asm`, `f034-ai.c`, `f034-decompile.log`, `f034-compose.py`,
`f034-ai-diagnostic.py`, `f034-dispatch-audit.json`, `f034-bind.py`,
`f034-family-bindings-preview.json`, `f034-family-bindings.json`,
`f034-accepted-replay.json`, `f034-cold-replay.log` and `f034-progress.json`.
The first source draft already aligned all physical operands and branches;
diagnostics alone earned no credit. Only canonical cold replay accepted it.
See [KNOWLEDGE_BASE.md](KNOWLEDGE_BASE.md) for the observed decision behavior.

The next bounded R047 AI candidate is F035 at `0x0059F4F0..0x005A1555`
/8,294 bytes. Its full native audit checks 2,118 instructions, 429 internal
branches, one return and 113 direct calls (including 14 range-helper calls).
There are no switches or external branch exits; ten following INT3 bytes are
alignment. Attested read-only Ghidra decompilation and private native evidence
are retained in `f035-*`. Independently review the full policy before drafting
source or claiming exact credit. The 95% goal remains active and incomplete;
cleanup and handoff do not pause it. All 97 unknown origins remain unknown.

## Verification and recovery

Run from the repository root, serially, using the private Python wrapper:

```bash
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/validate-tracking.py --require-target
scripts/repo-python scripts/report-reconstruction-status.py --summary
nice -n 10 scripts/repo-python scripts/ghidra.py check
nice -n 10 scripts/repo-python scripts/ci.py
git diff --check
```

F034 final validation: all 3,603 CI tests passed in 85.090 seconds, including
complete adoption, historical-prefix, alias, origin, tracking and progress
freshness checks. The canonical cold source/object pins and both headers remain
intact. Four superseded previews were removed after canonical equality checks
(93,645 file bytes); `f034-cleanup.json` records paths, sizes and hashes. The
first investigative source and receipt remain in `f034-probe-00.cpp` / `.json`,
with its profile and limits in `f034-control-manifest.json`. Original evidence,
canonical inputs, matching outputs and F021 remain preserved. The sampled host
had 8.6 GiB available memory and CPU 88% idle, with no swap-in or swap-out in
that interval. Builds and validation remained serial and low priority.

Keep compiler builds serial and low priority, monitor CPU/memory, and preserve
`config/claims.csv` header-only. Replay only units with relevant source, ABI,
profile or relocation changes. The active 95% goal remains incomplete.

## F035 checkpoint before F036 acceptance (2026-10-23)

## Latest accepted cohort: F035

`CharacterAI59F4F0::ChooseAction` at `0x0059F4F0..0x005A1555` cold-replays
exact from `src/CharacterAI59F4F0.cpp` / `.hpp`: **8,294 code bytes**, 2,118
instructions, 429 internal branches and one return. There are no switch tables
or external branch exits. Ten following INT3 bytes are alignment. The original
R047 body hash and ownership evidence remain unchanged.

The separate natural body preserves signed-byte indexed reads at offset 0x370,
conditional short-timer decrements, command overwrites and two native copies of
the movement/counter policy. The receiver interface remains pointer-only; do
not construct or embed it. The local two-float separation record is source-defined
and fully used. Six command assignment chains preserve observed read/store
repetitions. No assembly, byte arrays, inert locals, padding or alternate bodies
are used. Original identities, declarations and full owner layouts stay unknown.

All 229 relocations are bound: 113 direct calls, 101 readonly references to 22
float constants and 15 writable-global references. The counter at `0x0068D660`
has eight dword reads and six writes across the two paths. The existing global
at `0x006714D0` has one MOVSX byte read, preserving its previously accepted
signed-byte declaration. Fresh COFF payloads, access widths and target section
permissions were checked; writable storage is bound by address, not contents.
Calls comprise two float wrappers, 96 CRT rand calls, one predicate on the
opponent and 14 thiscall range-helper calls on the current receiver. These
declaration-only callees earn no new origin or exact credit.

```bash
scripts/repo-python scripts/replay-exact-units.py --unit character-ai-0059f4f0
```

Canonical replay cold-builds the object with pinned VC7.1 build 3077,
`/Od /Ob0 /Gy /GR- /GX- /Zi /I src`, then compares all bytes and relocations.
All 127 earlier units and inputs remain unchanged and were not rebuilt. The
new header includes unchanged `CharacterAIPolicy.hpp` for observed callee
declarations. Changing that header affects the six F033 units, F034 and F035;
changing only `CharacterAIPolicy.cpp` affects its six F033 units. Replay affected
units only, preserving the unchanged `GameLeafHelpers.hpp` ABI.

Private receipts below `.analysis/`: `f035-native-audit.py` / `.json`,
`f035-59f4f0.asm`, `f035-ai.c`, `f035-decompile.log`, `f035-compose.py`,
`f035-ai-diagnostic.py`, `f035-dispatch-audit.json`, `f035-bind.py`,
`f035-family-bindings-preview.json`, `f035-family-bindings.json`,
`f035-accepted-replay.json`, `f035-cold-replay.log` and `f035-progress.json`.
The rejected first draft omitted the reviewed attack-state group; its source
and diagnostic remain in `f035-probe-00.*`. The corrected full draft aligns all
physical operands and branches, but only canonical cold replay earns credit.
See [KNOWLEDGE_BASE.md](KNOWLEDGE_BASE.md) for the observed behavior.

The next bounded R047 AI candidate is F036 at `0x00532950..0x005349A0`
/8,273 bytes. Its full native audit checks 2,137 instructions, 457 internal
branches, one return and 98 direct calls, with no range-helper calls. There are
no switches or external exits; fifteen following INT3 bytes are alignment.
Attested read-only Ghidra decompilation and private native evidence are retained
in `f036-*`. Full behavior reading and native receiver checks are recorded in
`f036-behavior-review.json`: all three predicate calls use the opponent, and
two late weighted spell writes continue into later decisions. Preserve those
fallthroughs, signed-short checks at 0xF10/0xF12 and random-call ordering when
drafting. No source or exact credit is registered. The 95% goal remains active and incomplete; cleanup and handoff
do not pause it. All 97 unknown origins remain unknown.

## Verification and recovery

Run from the repository root, serially, using the private Python wrapper:

```bash
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/validate-tracking.py --require-target
scripts/repo-python scripts/report-reconstruction-status.py --summary
nice -n 10 scripts/repo-python scripts/ghidra.py check
nice -n 10 scripts/repo-python scripts/ci.py
git diff --check
```

F035 final validation: all 3,603 CI tests passed in 88.236 seconds, including
complete adoption, historical-prefix, alias, origin, tracking and progress
freshness checks. Canonical cold source/object and header pins remain intact.
Four superseded previews were removed after equality and cold-hash checks
(101,634 file bytes); `f035-cleanup.json` records paths, sizes and hashes.
Both investigative source drafts and receipts remain in `f035-probe-00.*` and
`f035-probe-01.*`; `f035-control-manifest.json` records profiles and diagnostic
limits. All original evidence, canonical inputs, matching outputs and F021 are
preserved. A host sample during CI had 8.6 GiB available memory and CPU 72% idle,
with 8 KiB/s swap-in and no swap-out in that interval. Builds and validation
remained serial and low priority.

Keep compiler builds serial and low priority, monitor CPU/memory, and preserve
`config/claims.csv` header-only. Replay only units with relevant source, ABI,
profile or relocation changes. The active 95% goal remains incomplete.

## F036 checkpoint before F037 acceptance (2026-10-23)

## Latest accepted cohort: F036

`CharacterAI532950::ChooseAction` at `0x00532950..0x005349A0` cold-replays
exact from `src/CharacterAI532950.cpp` / `.hpp`: **8,273 code bytes**, 2,137
instructions, 457 internal branches and one return. There are no switches or
external branch exits. Fifteen following INT3 bytes are alignment. The original
R047 body hash and ownership evidence remain unchanged.

The natural body preserves two late command-13 writes that continue into later
decisions, two different zero-choice gates that both test mode 1, signed-short
checks at offsets 0xF10/0xF12 and every random-call/access order. Three command
assignment chains retain native read/store repetitions. The receiver is a
pointer-only view; do not construct or embed it. The two-float local separation
record is source-defined and fully used. No assembly, byte arrays, padding,
inert locals, ABI misdeclarations or alternate bodies are used. Original names,
declarations and full owner layouts remain unknown.

All 217 relocations are bound: 98 direct calls, 112 readonly references to 26
float constants and seven signed-dword counter references at `0x0068D644`
(four reads, three writes). Fresh COFF payloads, access widths and target section
permissions were checked. Writable storage is bound by address, not contents.
Calls comprise two float wrappers, 93 CRT rand calls and three predicates on
the opponent; the third result is negated in a late command-50/51 branch. There
is no range-helper call. Declaration-only callees earn no new origin or exact
credit, and wrapper ownership remains unresolved.

```bash
scripts/repo-python scripts/replay-exact-units.py --unit character-ai-00532950
```

Canonical replay cold-builds one object using pinned VC7.1 build 3077,
`/Od /Ob0 /Gy /GR- /GX- /Zi /I src`, then compares the complete body and every
relocation. All 128 earlier units and inputs remain unchanged and were not
rebuilt. The new header includes unchanged `CharacterAIPolicy.hpp` for callee
declarations. Changing that header affects the six F033 units, F034, F035 and
F036; changing only `CharacterAIPolicy.cpp` affects its six F033 units. Replay
affected units only, preserving the unchanged `GameLeafHelpers.hpp` ABI.

Private receipts below `.analysis/`: `f036-native-audit.py` / `.json`,
`f036-532950.asm`, `f036-ai.c`, `f036-decompile.log`,
`f036-behavior-review.json`, `f036-compose.py`, `f036-ai-diagnostic.py`,
`f036-dispatch-audit.json`, `f036-bind.py`, `f036-family-bindings-preview.json`,
`f036-family-bindings.json`, `f036-accepted-replay.json`,
`f036-cold-replay.log` and `f036-progress.json`. The first full source draft
already aligns every physical operand and branch, but diagnostics alone earn
no credit. Only canonical cold replay accepted it.

The next bounded R047 AI candidate is F037 at `0x00499030..0x0049B06F`
/8,256 bytes. Its complete native audit checks 2,125 instructions, 460 internal
branches, one return and 100 direct calls: two float wrappers, 92 CRT rand,
two predicates and four range helpers. There are no switches, external exits
or trailing alignment bytes. Attested read-only Ghidra decompilation and native
evidence are retained in `f037-*`. Full behavior reading and a complete private
source draft are recorded in `f037-progress.json` and `f037-compose.py`.
The next action is serial probe compilation and complete relocation diagnosis;
no F037 exact credit is registered. The 95% goal remains active and incomplete;
cleanup and handoff do not pause it. All 97 unknown origins remain unknown.

## Verification and recovery

Run from the repository root, serially, using the private Python wrapper:

```bash
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/validate-tracking.py --require-target
scripts/repo-python scripts/report-reconstruction-status.py --summary
nice -n 10 scripts/repo-python scripts/ghidra.py check
nice -n 10 scripts/repo-python scripts/ci.py
git diff --check
```

F036 final validation: all 3,603 CI tests passed in 103.337 seconds, including
complete adoption, historical-prefix, alias, origin, tracking and progress
freshness checks. Canonical cold source/object and header pins remain intact.
Four superseded previews were removed after equality and cold-hash checks
(92,552 file bytes); `f036-cleanup.json` records paths, sizes and hashes. The
first complete investigative source and receipt remain in `f036-probe-00.*`,
with compiler profile and diagnostic limits in `f036-control-manifest.json`.
All original evidence, canonical inputs, matching outputs and F021 are preserved.
A host sample during CI had 8.5 GiB available memory and CPU 84% idle, with no
swap-in or swap-out in that interval. Builds and validation remained serial
and low priority.

Keep compiler builds serial and low priority, monitor CPU/memory, and preserve
`config/claims.csv` header-only. Replay only units with relevant source, ABI,
profile or relocation changes. The active 95% goal remains incomplete.

## F037 checkpoint before F038 acceptance (2026-10-23)

## Latest accepted cohort: F037

`CharacterAI499030::ChooseAction` at `0x00499030..0x0049B06F` cold-replays
exact from `src/CharacterAI499030.cpp` / `.hpp`: **8,256 code bytes**, 2,125
instructions, 460 internal branches and one return. There are no switches,
external branch exits or trailing alignment bytes. The next candidate begins
immediately after the complete return. R047 body hash and ownership are unchanged.

The natural body preserves common exits of the 0xF14-gated command branches,
two pairs of independent late random checks with identical conditions but
different commands 13/23, and the native current-height > opponent-height
comparison. Three assignment chains retain observed command read/store
repetitions. The receiver interface is pointer-only; do not construct or embed
it. The fully used two-float local separation record is source-defined. No
assembly, byte arrays, padding, inert locals, ABI misdeclarations or alternate
bodies are used. Original identities, declarations and complete layouts remain
unknown; the signed-short view at 0xF14 does not establish a full owner layout.

All 207 relocations are bound: 100 direct calls, 100 readonly references to 24
float constants and seven signed-dword counter references at `0x0068D624`
(four reads, three writes). Fresh COFF payloads, access widths and target section
permissions were checked. Writable storage is bound by address, not contents.
Calls comprise two float wrappers, 92 CRT rand calls, two predicates on the
opponent and four thiscall range helpers on the current receiver. Declaration-only
callees earn no additional origin or exact credit; wrapper ownership stays unknown.

```bash
scripts/repo-python scripts/replay-exact-units.py --unit character-ai-00499030
```

Canonical replay cold-builds the object with pinned VC7.1 build 3077,
`/Od /Ob0 /Gy /GR- /GX- /Zi /I src`, then compares the complete function and
every relocation. All 129 earlier units and inputs remain unchanged and were
not rebuilt. The new header includes unchanged `CharacterAIPolicy.hpp` for
callee declarations. Changing that header affects the six F033 units, F034,
F035, F036 and F037; changing only `CharacterAIPolicy.cpp` affects its six F033
units. Replay affected units only; preserve the unchanged `GameLeafHelpers.hpp` ABI.

Private receipts below `.analysis/`: `f037-native-audit.py` / `.json`,
`f037-499030.asm`, `f037-ai.c`, `f037-decompile.log`, `f037-compose.py`,
`f037-branch-review.json`, `f037-ai-diagnostic.py`, `f037-dispatch-audit.json`,
`f037-bind.py`, `f037-family-bindings-preview.json`,
`f037-family-bindings.json`, `f037-accepted-replay.json`,
`f037-cold-replay.log` and `f037-progress.json`. The first draft's 14 extra bytes
were rejected; common exits and comparison operand order were reconciled with
the complete native body. Diagnostics alone earn no exact credit.

The next R047 cohort F038 consists of two independently audited 7,780-byte AI
functions at `0x00474B40..0x004769A3` and `0x005E9620..0x005EB483`.
Each has 1,985 instructions, 391 internal branches, one return, 102 direct calls
and twelve following alignment INT3 bytes, without switches or external exits.
Complete comparison finds only seven non-call instruction differences: counter
references at `0x0068D620` versus `0x0068D670`. All direct call targets agree.
The attested two-function decompile and native/family reports are retained in
`f038-*` / `f038b-*`, with state in `f038-progress.json`. Full first-body
reading and native call-site checks are in `f038-behavior-review.json`; the
complete second-body comparison preserves that behavior. Each has sixteen
range-helper calls on the current receiver and one predicate on the opponent.
Preserve type-3/1/0 command writes that can fall through into ordinary AI, and
type-4/2 paths that bypass it. Independently confirm the source and bind and
cold-replay both complete functions separately. No F038 source or exact credit is registered. The 95%
goal remains active and incomplete; cleanup/handoff does not pause it. All 97
unknown origins remain unknown.

## Verification and recovery

Run from the repository root, serially, using the private Python wrapper:

```bash
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/validate-tracking.py --require-target
scripts/repo-python scripts/report-reconstruction-status.py --summary
nice -n 10 scripts/repo-python scripts/ghidra.py check
nice -n 10 scripts/repo-python scripts/ci.py
git diff --check
```

F037 final validation: all 3,603 CI tests passed in 81.970 seconds, including
complete adoption, historical-prefix, alias, origin, tracking and progress
freshness checks. Canonical cold source/object and header pins remain intact.
Four superseded previews were removed after equality and cold-hash checks
(101,013 file bytes); `f037-cleanup.json` records paths, sizes and hashes. Both
investigative drafts and receipts remain in `f037-probe-00.*` / `f037-probe-01.*`,
with profiles and diagnostic limits in `f037-control-manifest.json`. Original
evidence, canonical inputs, matching outputs and F021 remain preserved. A host
sample during CI had 8.5 GiB available memory and CPU 89% idle, with no interval
swap activity. Builds and validation remained serial and low priority.

Keep compiler builds serial and low priority, monitor CPU/memory, and preserve
`config/claims.csv` header-only. Replay only units with relevant source, ABI,
profile or relocation changes. The active 95% goal remains incomplete.

## F038 checkpoint before F039 acceptance (2026-10-23)

## Latest accepted cohort: F038

Two independently reviewed R047 AI methods cold-replay exact from one natural
template body in `src/CharacterAICardPolicy.cpp` / `.hpp`:

| Receiver alias | Complete target extent | Writable counter |
| --- | --- | --- |
| `CharacterAI474B40` | `0x00474B40..0x004769A3` | `0x0068D620` |
| `CharacterAI5E9620` | `0x005E9620..0x005EB483` | `0x0068D670` |

Each full body has **7,780 code bytes**, 1,985 instructions, 391 internal
branches, one return and twelve following alignment INT3 bytes. Neither has
switches or external branch exits. Original R047 hashes and ownership remain
unchanged. Full native comparison differs only in seven counter-reference
instructions; the source-defined profiles bind those counters independently.
This reuse does not establish original templates, class identities or layouts.
Only methods are emitted; never construct or embed an incomplete receiver.

Signed-byte indexed type policies retain short-timer decrements, directional
choices and command overwrites. Type-3/1/0 writes can continue into ordinary AI;
type-4/2 stock-qualified paths bypass it. Own-x overrides use thresholds 320/960
and the signed facing byte. Three observed command assignment chains and the
fully used source-defined two-float separation record remain explicit. There is
no assembly, target byte array, padding, inert local or alternate body.

Each unit binds all 204 relocations: 102 calls, 95 readonly references to 23
actual float payloads, and seven signed-dword counter accesses (four reads,
three writes). Fresh COFF payloads, zero addends, access widths and target section
permissions were checked. Writable storage is bound by address, not contents.
Each has two float-wrapper calls, 83 CRT rand calls, sixteen range helpers on
the current receiver and one predicate on the opponent. Declaration-only
callees earn no new origin or exact credit; wrapper ownership remains unknown.

```bash
scripts/repo-python scripts/replay-exact-units.py --unit character-ai-00474b40 --unit character-ai-005e9620
```

Canonical replay cold-builds **one object**, then compares both complete units:
15,560 bytes /408 relocations. Profile: pinned VC7.1 build 3077,
`/Od /Ob0 /Gy /GR- /GX- /Zi /I src`. All 130 prior units and inputs remain
unchanged and were not rebuilt. The new source reuses our independently authored
F035 ordinary-policy statements, with full byte verification against both targets.
Changing the shared card source/header affects both F038 units. The included
`CharacterAIPolicy.hpp` affects the six F033 units, F034..F037 and both F038 units;
its source affects its six F033 units. Replay affected units only.

Private receipts below `.analysis/`: `f038-native-audit.py` / `.json`,
`f038b-native-audit.py` / `.json`, `f038-474b40.asm`, `f038b-5e9620.asm`,
combined `f038-ai.c`, `f038-decompile.log`, `f038-ai-family-audit.py`,
`f038-ai-family-differences.json`, `f038-behavior-review.json`,
`f038-compose.py`, `f038-ai-diagnostic.py`, `f038-dispatch-audit.json`,
`f038-bind-family.py`, `f038-family-bindings-preview.json`,
`f038-family-bindings.json`, `f038-accepted-replay.json`,
`f038-cold-replay.log` and `f038-progress.json`. The initial six-byte-longer
draft was rejected; the three left directional expressions were reconciled
with native SUB/NEG/SBB emission. Diagnostics alone earn no exact credit.

The next bounded R047 AI candidate is F039 at `0x005086E0..0x0050A4DB`
/7,676 bytes. Its full audit checks 1,957 instructions, 405 internal branches,
one return and 102 calls: two float wrappers, 83 CRT rand, sixteen range helpers
and one predicate. There are no switches or external exits; four following INT3
bytes are alignment. Retain `f039-*` native evidence and the attested read-only
decompile. Full behavior reading, native receiver checks and a complete private
draft are recorded in `f039-behavior-review.json`, `f039-progress.json` and
`f039-compose.py`. All sixteen range calls use the current receiver and the
predicate uses the opponent. Compile and diagnose the full source before
canonical cold acceptance; no F039 credit is registered. The 95% goal remains active and incomplete; cleanup and
handoff do not pause it. All 97 unknown origins remain unknown.

## Verification and recovery

Run from the repository root, serially, using the private Python wrapper:

```bash
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/validate-tracking.py --require-target
scripts/repo-python scripts/report-reconstruction-status.py --summary
nice -n 10 scripts/repo-python scripts/ghidra.py check
nice -n 10 scripts/repo-python scripts/ci.py
git diff --check
```

F038 final validation: all 3,603 CI tests passed in 84.006 seconds, including
complete adoption, historical-prefix, alias, origin, tracking and progress
freshness checks. Both canonical cold reports and source/object/header pins
remain intact. Four superseded previews were removed after equality and hash
checks (112,727 file bytes); `f038-cleanup.json` records paths, sizes and hashes.
Both investigative sources and first-profile diagnostics remain in
`f038-probe-00.*` / `f038-probe-01.*`, with profiles and diagnostic limits in
`f038-control-manifest.json`. All original evidence, canonical inputs, matching
outputs and F021 remain preserved. A host sample during CI had 8.7 GiB available
memory and CPU 89% idle, without interval swap activity. Builds and validation
remained serial and low priority.

Keep compiler builds serial and low priority, monitor CPU/memory, and preserve
`config/claims.csv` header-only. Replay only units with relevant source, ABI,
profile or relocation changes. The active 95% goal remains incomplete.

## F039 checkpoint before F040 acceptance (2026-10-23)

## Latest accepted cohort: F039

`CharacterAI5086E0::ChooseAction` at `0x005086E0..0x0050A4DB` cold-replays
exact from `src/CharacterAI5086E0.cpp` / `.hpp`: **7,676 code bytes**, 1,957
instructions, 405 internal branches and one return. There are no switches or
external branch exits; four following INT3 bytes are alignment. The complete
R047 body hash and ownership evidence remain unchanged.

The separate natural body preserves signed-byte indexed type-2/1/0 decisions,
short-timer decrements, own-x/facing early exits and a type-0 random command
choice that continues into queued/ordinary behavior. Position gates use 240/1040
and signed facing 1/-1. Three assignment chains retain observed command
read/store repetitions. The receiver interface stays pointer-only; never
construct or embed it. The fully used two-float local separation record is
source-defined. No assembly, target arrays, padding, inert locals, fake returns,
ABI misdeclarations or alternate bodies are used. Original names, declarations
and complete owner layouts remain unknown.

All 206 relocations are bound: 102 calls, 97 readonly references to 24 actual
float payloads and seven dword counter accesses at `0x0068D640` (four reads,
three writes). Fresh COFF payloads, zero addends, access widths and target
section permissions were checked. Writable storage is bound by address, not
contents. Calls comprise two float wrappers, 83 CRT rand, sixteen range helpers
on the current receiver and one predicate on the opponent. Declaration-only
callees earn no additional origin or exact credit; wrapper ownership is unknown.

```bash
scripts/repo-python scripts/replay-exact-units.py --unit character-ai-005086e0
```

Canonical replay cold-builds one object with pinned VC7.1 build 3077,
`/Od /Ob0 /Gy /GR- /GX- /Zi /I src`, then compares the complete body and every
relocation. All 132 earlier units and inputs remain unchanged and were not
rebuilt, including both F038 card policies. Our authored ordinary F035 statements
are reused, with the entire emitted F039 body independently verified. The new
header includes unchanged `CharacterAIPolicy.hpp` for callee declarations; a
change to that header affects the six F033 units, F034..F037, both F038 units
and F039. Its source affects its six F033 units. Replay affected units only.

Private receipts below `.analysis/`: `f039-native-audit.py` / `.json`,
`f039-5086e0.asm`, `f039-ai.c`, `f039-decompile.log`,
`f039-behavior-review.json`, `f039-compose.py`, `f039-ai-diagnostic.py`,
`f039-dispatch-audit.json`, `f039-bind.py`, `f039-family-bindings-preview.json`,
`f039-family-bindings.json`, `f039-accepted-replay.json`,
`f039-cold-replay.log` and `f039-progress.json`. The first full draft aligns
all physical operands and branch destinations; only canonical cold replay
earns credit, not diagnostic alignment.

The next bounded R047 AI candidate is F040 at `0x00558F50..0x0055ABD6`
/7,303 bytes. Its complete native audit checks 1,903 instructions, 351 internal
branches, one return and 106 calls: two float wrappers, 83 CRT rand, twenty range
helpers and one predicate. There are no switches or external exits; nine
following INT3 bytes are alignment. Retain `f040-*` native evidence and the
attested read-only decompile. Full behavior reading and call-site checks are
recorded in `f040-behavior-review.json` / `f040-call-contexts.json`. Twenty range
calls use the current receiver and the predicate uses the opponent. Preserve
the separate type-4 movement/counter path and type-3/2 command fallthroughs;
only queued mode 1 appears in the ordinary path. No source or exact credit is
registered; independently reconstruct the complete body before acceptance. The 95% goal remains active and incomplete;
cleanup/handoff does not pause it. All 97 unknown origins remain unknown.

## Verification and recovery

Run from the repository root, serially, using the private Python wrapper:

```bash
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/validate-tracking.py --require-target
scripts/repo-python scripts/report-reconstruction-status.py --summary
nice -n 10 scripts/repo-python scripts/ghidra.py check
nice -n 10 scripts/repo-python scripts/ci.py
git diff --check
```

F039 final validation: all 3,603 CI tests passed in 90.471 seconds, including
complete adoption, historical-prefix, alias, origin, tracking and progress
freshness checks. Canonical cold source/object/header pins remain intact.
Four superseded previews were removed after equality and hash checks (91,455
file bytes); `f039-cleanup.json` records paths, sizes and hashes. The first
complete investigative source and receipt remain in `f039-probe-00.*`, with
profile and diagnostic limits in `f039-control-manifest.json`. Original evidence,
canonical inputs, matching outputs and F021 remain preserved. A host sample had
8.5 GiB available memory and CPU 89% idle, without interval swap activity.
Builds and validation remained serial and low priority.

Keep compiler builds serial and low priority, monitor CPU/memory, and preserve
`config/claims.csv` header-only. Replay only units with relevant source, ABI,
profile or relocation changes. The active 95% goal remains incomplete.
