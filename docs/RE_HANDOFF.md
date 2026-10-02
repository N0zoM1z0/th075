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
  47 authored, 332 library and five compiler candidates; 3,967 origins remain
  pending. Candidate count is not authored function count; regenerate
  statistics from the ledgers.
- The active goal is all origins reviewed and at least 50% authored bytes
  exact. Finish every origin review before resuming exact reconstruction.
  The current reviewed authored-byte denominator is 12,343, with 8,916 exact (72.24%).
  This denominator is provisional; the goal is incomplete. Four public
  accounting regressions prevent pending origins or function counts from
  falsely satisfying it. See `ORIGIN_REVIEW.md` for R001 through R008 evidence.
- F003 accepted three texture/reset functions, 833 bytes and 30 relocations.
  F004 accepted three keyboard/setup functions, 382 bytes and 36 relocations.
  Each batch passed complete cold replay from a fresh independent object.
  The no-auth public Funnel Bash MCP cold-replayed all 36/36 units
  across six objects through scripts/repo-python after F005. Public CI has 26 passing
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
binding evidence. Review the remaining 434 SDK fingerprint candidates, starting
with complete call-only bodies anchored to the R008 set and independently
verified constant/data bindings. Neither survey alone grants credit. Also follow
the remaining container/string helpers starting at
`0x004063F0`, then review the custom geometry builders and textured-quad
callers around `0x0040C9A0..0x0040DB10` from complete control flow. Keep vendor
and custom ownership separate. Finish every origin review before resuming
exact reconstruction. Then rank authored functions by core behavior, dependency leverage and reconstruction
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
