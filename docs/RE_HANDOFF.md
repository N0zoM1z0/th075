# Current function reconstruction handoff

Updated 2026-10-02. Scope is function reconstruction; the user explicitly
deferred subsequent phases. Write documentation and handoffs in English.

- Target: supplied Japanese `th075.exe`, reporting version 1.11, SHA-256
  `bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98`.
  Official distribution provenance is uncorroborated. Do not substitute the
  localized executable.
- Initial analysis completed in the separate TH075 Ghidra 12.1.3 project.
  There are 4,351 candidates, with 42 mapped, 42 source-present, and 42
  complete exact functions covering 8,916 bytes. Origin review has classified
  525 authored, 792 library and 564 compiler candidates; 2,470 origins remain
  pending. Candidate count is not authored function count; regenerate
  statistics from the ledgers.
- The active goal is all origins reviewed and at least 50% authored bytes
  exact. Finish every origin review before resuming exact reconstruction.
  The current reviewed authored-byte denominator is 1,798,800, with 8,916 exact (0.50%).
  This denominator is provisional; the goal is incomplete. Four public
  accounting regressions prevent pending origins or function counts from
  falsely satisfying it. See `ORIGIN_REVIEW.md` for R001 through R054 evidence.
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
